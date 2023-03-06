/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "webpage/directory.h"
#include "element/element.h"
#include "webpage/page.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "type/type.h"
#include "attribute/avm.h"
#include "parser/text.h"
#include "webpage/crosslink.h"
#include "webpage/corpus.h"
#include "icu/charset.h"
#include "schema/jsonld.h"
#include "spell/spell.h"
#include "coop/lox.h"

#define DOCTYPE "<!DOCTYPE"
#define DOCTYPE_LC "<!doctype"
#define DOCDOT DOCTYPE " ... >"

void page::init (const ::std::string& name, ::std::string& content, const fileindex_t x)
{   ids_.ndx (x);
    names_.ndx (x, false);
    if (is_css (name))
    {   dot_css_ = true;
        if (context.load_css () && (context.css_version () >= css_1))
        {   css_.parse_file (nits_, namespaces_ptr (), url (nits (), context.html_ver (), get_site_path ()), true);
            stats_.mark (context.html_ver ()); }
        stats_.mark_file (GSL_NARROW_CAST < unsigned > (content.size ())); }
    else parse (content); }

page::page (const ::std::string& name, const ::std::time_t updated, ::std::string& content, const fileindex_t x, const directory* d)
    :   name_ (name), directory_ (d), updated_ (updated), css_ (*this)
{   VERIFY_NOT_NULL (d, __FILE__, __LINE__);
    init (name, content, x); }

page::page (nitpick& nits, const ::std::string& name, const ::std::time_t updated, ::std::string& content, const directory* d)
    :   name_ (name), directory_ (d), updated_ (updated), css_ (*this)
{   VERIFY_NOT_NULL (d, __FILE__, __LINE__);
    fileindex_t x (get_fileindex (d -> get_disk_path (nits, name)));
    directory_ = d;
    init (name, content, x); }

page::page (const ::std::string& content, const bool outsider)
    :   css_ (*this)
{   if (outsider) outsider_ = true;
    else snippet_ = true;
    ::std::string x (content);
    parse (x); }

void page::swap (page& p)
{   abbrs_.swap (p.abbrs_);
    access_.swap (p.access_);
    author_.swap (p.author_);
    base_.swap (p.base_);
    charset_.swap (p.charset_);
    ::std::swap (check_links_, p.check_links_);
    corpus_.swap (p.corpus_);
    description_.swap (p.description_);
    dfns_.swap (p.dfns_);
    ::std::swap (directory_, p.directory_);
    ::std::swap (document_, p.document_);
    ::std::swap (euid_, p.euid_);
    glyphs_.swap (p.glyphs_);
    ::std::swap (has_title_, p.has_title_);
    ids_.swap (p.ids_);
    itemscope_.swap (p.itemscope_);
    jsonld_.swap (p.jsonld_);
    lang_.swap (p.lang_);
    keywords_.swap (p.keywords_);
    md_export_.swap (p.md_export_);
    mf_export_.swap (p.mf_export_);
    name_.swap (p.name_);
    names_.swap (p.names_);
    nits_.swap (p.nits_);
    nodes_.swap (p.nodes_);
    ::std::swap (outsider_ , p.outsider_);
    ::std::swap (phrase_, p.phrase_);
    profiles_.swap (p.profiles_);
    ::std::swap (snippet_ , p.snippet_);
    ssi_.swap (p.ssi_);
    stats_.swap (p.stats_);
    ::std::swap (style_css_, p.style_css_);
    title_.swap (p.title_);
    ::std::swap (updated_, p.updated_); }

void page::cleanup () noexcept
{   if (document_ != nullptr)
    {   document_ -> cleanup ();
        delete document_;
        document_ = nullptr; } }

void page::lang (nitpick& nits, const html_version& , const ::std::string& l)
{   if (! lang_.empty ())
        if (! compare_no_case (l, lang_))
            nits.pick (nit_lang_redefined, es_warning, ec_page, "lang defined as ", l, ", but previously defined as ", lang_);
    lang_ = l; }

void page::charset (nitpick& nits, const html_version& v, const ::std::string& cs)
{   if (charset_defined ())
        if (! compare_no_case (cs, charset_))
            nits.pick (nit_charset_redefined, es_warning, ec_attribute, "charset defined as ", cs, ", but previously defined as ", charset_);
    if ((v.is_5 ()))
        if (! compare_no_case (cs, UTF_8))
            nits.pick (nit_not_utf_8, es_error, ec_attribute, v.report (), " requires the " UTF_8 " charset");
    charset_ = cs; }

bool page::parse (::std::string& content)
{   if (! snippet_ && ! outsider_)
    {   PRESUME (directory_ != nullptr, __FILE__, __LINE__);
        ssi_.filename_ = name_;
        const html_version v (html_5_3);
        content = parse_ssi (nits_, v, *this, ssi_, content, updated_); }
    const bool res = nodes_.parse (nits_, content);
    stats_.mark_file (GSL_NARROW_CAST < unsigned > (content.size ()));
    return res; }

void page::examine ()
{   if ((document_ == nullptr) && (! nodes_.invalid ()) && nodes_.version ().known ())
    {   if ((! snippet_ && ! outsider_) && context.md_export ())
            md_export_.init (get_export_root ());
        try
        {   document_ = new element (name_, nodes_.top (), nullptr, this);
            stats_.mark (version ());
            VERIFY_NOT_NULL (document_, __FILE__, __LINE__);
            PRESUME (document_ -> tag () == elem_faux_document, __FILE__, __LINE__);
            document_ -> reconstruct (&access_);
            ::std::string s = document_ -> make_children (0);
            if (context.tell (es_structure) && ! s.empty ()) nits_.pick (nit_debug, es_detail, ec_page, s);
            document_ -> examine_self (lingo (nits_, context.lang ()));
            document_ -> verify_document ();
            if (! snippet_ && ! outsider_)
            {   if (has_corpus ())
                    extend_corpus (nits_, title_, get_site_path (), corpus_, author_, keywords_, description_);
                if (context.md_export ()) md_export_.write (nits_, get_export_path ()); }
            if (! jsonld_.empty ()) parse_json_ld (nits_, version (), jsonld_);
            ids_.cover_arse ();
            document_ -> accumulate (&stats_); }
        catch (...)
        {   cleanup ();
            throw; } } }

void page::verify_locale (const ::boost::filesystem::path& p)
{   if (lang_.empty ())
    {   lang_ = context.lang ();
        if (lang_.empty ()) lang_ = STANDARD_ENGLISH; }
    verify_file_charset (nits_, version (), p, charset_); }

::std::string page::get_export_root () const
{   return get_disk_path ().stem ().string (); }

void page::itemscope (const itemscope_ptr itemscope)
{   PRESUME (itemscope.get () != nullptr, __FILE__, __LINE__);
    itemscope_ = itemscope;
    VERIFY_NOT_NULL (itemscope_, __FILE__, __LINE__);
    if (itemscope_ -> export_path ().empty ())
        itemscope_ -> set_exporter (md_export (), md_export_.append_path (get_export_root (), null_itemprop, true)); }

::std::string page::load_url (nitpick& nits, const url& u) const
{   if (snippet_ || outsider_) return ::std::string ();
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    return directory_ -> load_url (nits, u); }

::boost::filesystem::path page::absolute_member (nitpick& nits, const ::boost::filesystem::path& file) const
{   if (snippet_ || outsider_) return ::std::string ();
    if (file.string ().find_first_of (":\\/") != ::std::string::npos) return file;
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    return directory_ -> get_disk_path (nits, local_path_to_nix (file.string ())); }

::std::string page::report ()
{   ::std::ostringstream res;
    if (document_ != nullptr)
        res << document_ -> report ();
    nits_.accumulate (&stats_);
    css ().accumulate (&stats_);
    {   lox curly (lox_stats);
        stats_.accumulate (); }
    if (context.stats_page ())
        res << stats_.report (false);
    return res.str (); }

::std::string get_page_url (const ::std::string& url)
{   ::std::string res (sanitise (url));
    const ::std::size_t pc = res.find_first_of ("?#=");
    if (pc != ::std::string::npos)
        res = res.substr (0, pc);
    return res; }

const ::std::string page::get_site_path () const
{   if (snippet_ || outsider_) return ::std::string ();
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    return join_site_paths (directory_ -> get_site_path (), name ()); }

const ::boost::filesystem::path page::get_disk_path () const
{   if (snippet_ || outsider_) return ::std::string ();
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    return (directory_ -> get_disk_path () / name ()); }

const ::boost::filesystem::path page::get_export_path () const
{   if (snippet_ || outsider_) return ::std::string ();
    if (! context.export_defined ()) return get_disk_path ();
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    return directory_ -> get_export_path () / name (); }

bool page::verify_url (nitpick& nits, const ::std::string& s) const
{   if (! check_links () || snippet_ || outsider_) return true;
    VERIFY_NOT_NULL (directory_, __FILE__, __LINE__);
    url u (nits, version (), s);
    if (u.is_local () && ! check_links_) return true;
    return directory_ -> verify_url (nits, version (), u); }

void page::lynx ()
{   if (snippet_ || outsider_) return;
    if (! context.crosslinks ()) return;
    declare_crosslinks (get_disk_path (), ids_); }

uid_t page::euid () noexcept
{   if (euid_ < uid_max) ++euid_;
    return euid_; }

void page::shadow (nitpick& nits, const ::boost::filesystem::path& s)
{   if (snippet_ || outsider_) return;
    ::std::stringstream ss;
    bool changed = false;
    try
    {   if (file_exists (s))
        {   if (context.shadow_changed ())
            {   if (updated_ == 0) updated_ = get_last_write_time (get_disk_path ());
                const ::std::time_t target = get_last_write_time (s);
                if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_shadow, get_disk_path (), " last updated ", updated_, ", ", s, " last updated ", target);
                if (target >= updated_) return; }
            const ::boost::filesystem::file_status stat = file_data (s);
#ifndef NO_PERMS
            if ((stat.permissions () & ::boost::filesystem::perms::owner_write) == 0)
            {   file_permissions (s, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::add_perms);
                changed = true; } 
#endif // NO_PERMS
        }
        BOOST_FSTREAM_CNSTRO (f, s, ::std::ios_base::trunc | ::std::ios_base::out);
        if (f.fail ())
            nits.pick (nit_cannot_create_file, es_catastrophic, ec_shadow, "cannot create ", s.string ());
        else
        {   PRESUME (! dot_css_, __FILE__, __LINE__);
            if (document_ != nullptr) document_ -> shadow (ss, version ());
            f << ss.str ();
            f.close ();
#ifndef NO_PERMS
            if (changed) file_permissions (s, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::remove_perms);
#endif // NO_PERMS
        } }
    catch (...)
    {   nits.pick (nit_shadow_failed, es_catastrophic, ec_shadow, "error writing ", s.string ());
        throw; } }

const url& page::base () const noexcept
{ return base_; }

void page::base (const url& s)
{ base_ = s; }

::std::string page::get_absolute_url (const ::std::string& s) const
{   // if called before BASE is processed, result will be a lie
    PRESUME ((s.find (':') == ::std::string::npos), __FILE__, __LINE__);
    ::std::string arg;
    if (! base_.empty ()) arg = base_.absolute ();
    else
    {   VERIFY_NOT_NULL (get_directory (), __FILE__, __LINE__);
        arg = context.make_absolute_url (get_directory () -> get_site_path ()); }
    if ((s.length () > 0) && (s.at (0) != '/'))
        if (arg.length () == 0) arg = "/";
        else if (arg.at (arg.length () - 1) != '/') arg += '/';
    arg += s; return arg; }

void page::append_jsonld (const ::std::string& j)
{   jsonld_ += j + "\n"; }

::std::string page::css_review (mmac_t& mac) const
{   nitpick gnats;
    url u (gnats, context.html_ver (), get_site_path ());
    return css ().review (mac, u.absolute ()); }
