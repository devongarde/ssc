/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "webpage/directory.h"
#include "element/element.h"
#include "webpage/page.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "type/type.h"
#include "attribute/avm.h"
#include "parser/text.h"
#include "webpage/crosslink.h"

#define DOCTYPE "<!DOCTYPE"
#define DOCTYPE_LC "<!doctype"
#define DOCDOT DOCTYPE " ... >"

page::page (const ::std::string& name, ::std::string& content, const fileindex_t x, directory* d, const e_charcode encoding)
    :   name_ (name), schema_version_ (context.schema_ver ())
{   assert (d != nullptr);
    ids_.ndx (x);
    directory_ = d;
    parse (content, encoding); }

page::page (nitpick& nits, const ::std::string& name, ::std::string& content, directory* d, const e_charcode encoding)
    :   name_ (name), schema_version_ (context.schema_ver ())
{   assert (d != nullptr);
    ids_.ndx (get_fileindex (d -> get_disk_path (nits, name)));
    directory_ = d;
    parse (content, encoding); }

void page::reset ()
{   page p;
    swap (p); }

void page::reset (const page& p)
{   page tmp (p);
    swap (tmp); }

void page::swap (page& p) NOEXCEPT
{   ids_.swap (p.ids_);
    access_.swap (p.access_);
    document_.swap (p.document_);
    nodes_.swap (p.nodes_);
    name_.swap (p.name_);
    mf_export_.swap (p.mf_export_);
    md_export_.swap (p.md_export_);
    schema_version_.swap (p.schema_version_);
    ssi_.swap (p.ssi_);
    nits_.swap (p.nits_);
    ::std::swap (directory_, p.directory_);
    ::std::swap (has_title_, p.has_title_);
    ::std::swap (euid_, p.euid_); }

bool page::parse (::std::string& content, const e_charcode )
{   nits_.reset ();
    assert (directory_ != nullptr);
    ssi_.filename_ = name_;
    html_version v (html_5_3);
    content = parse_ssi (nits_, v, *directory_, ssi_, content);
    bool res = nodes_.parse (nits_, content);
    context.mark_file (static_cast < unsigned > (content.size ()));
    return res; }

void page::examine (const directory& d)
{   if ((! document_) && ! nodes_.invalid () && nodes_.version ().known ())
    {   if (context.md_export ()) md_export_.init (get_export_root ());
        document_.reset (new element (name_, nodes_.top (), nullptr, ids_, &access_, *this));
        context.mark (version ());
        assert (document_ -> tag () == elem_faux_document);
        document_ -> examine_self (d);
        document_ -> verify_document ();
        if (context.md_export ()) md_export_.write (nits_, get_export_path ());
        ids_.cover_arse (); } }

::std::string page::get_export_root () const
{   return get_disk_path ().stem ().string (); }

void page::itemscope (const itemscope_ptr itemscope)
{   assert (itemscope.get () != nullptr);
    itemscope_ = itemscope;
    if (itemscope_ -> export_path ().empty ())
        itemscope_ -> set_exporter (md_export (), md_export_.append_path (get_export_root (), null_itemprop, true)); }

::std::string page::find_webmention () const
{   assert (document_);
    return document_ -> find_webmention (); }

::std::string page::find_mention_info (const url& u, bool text, bool anything)
{   assert (document_);
    return document_ -> find_mention_info (u, text, anything); }

::std::string page::load_url (nitpick& nits, const url& u) const
{   assert (directory_ != nullptr);
    return directory_ -> load_url (nits, u); }

::boost::filesystem::path page::absolute_member (nitpick& nits, const ::boost::filesystem::path& file) const
{   if (file.string ().find_first_of (":\\/") != ::std::string::npos) return file;
    assert (directory_ != nullptr);
    return directory_ -> get_disk_path (nits, local_path_to_nix (file.string ())); }

::std::string page::report ()
{   ::std::ostringstream res;
    if (document_.get () != nullptr)
        res << document_ -> report ();
    if (context.stats_page ()) res << stats_.report (false);
    return res.str () ; }

::std::string get_page_url (const ::std::string& url)
{   ::std::string res (sanitise (url));
    ::std::size_t pc = res.find_first_of ("?#=");
    if (pc != ::std::string::npos)
        res = res.substr (0, pc);
    return res; }

const ::std::string page::get_site_path () const
{   assert (directory_ != nullptr);
    return join_site_paths (directory_ -> get_site_path (), name ()); }

const ::boost::filesystem::path page::get_disk_path () const
{   assert (directory_ != nullptr);
    return (directory_ -> get_disk_path () / name ()); }

const ::boost::filesystem::path page::get_export_path () const
{   if (! context.export_defined ()) return get_disk_path ();
    assert (directory_ != nullptr);
    return directory_ -> get_export_path () / name (); }

bool page::verify_url (nitpick& nits, const ::std::string& s, const attribute_bitset& state, const vit_t& itemtypes) const
{   assert (directory_ != nullptr);
    return directory_ -> verify_url (nits, version (), url (nits, version (), s), state, itemtypes); }

void page::lynx ()
{   if (! context.crosslinks ()) return;
    declare_crosslinks (get_disk_path (), ids_); }

uid_t page::euid ()
{   if (euid_ < uid_max) ++euid_;
    return euid_; }

void page::shadow (nitpick& nits, const ::boost::filesystem::path& s)
{   ::std::stringstream ss;
    bool changed = false;
    try
    {   if (::boost::filesystem::exists (s))
        {   ::boost::filesystem::file_status stat = ::boost::filesystem::status (s);
            if ((stat.permissions () & ::boost::filesystem::perms::owner_write) == 0)
            {   ::boost::filesystem::permissions (s, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::add_perms);
                changed = true; } }
        ::boost::filesystem::ofstream f (s, ::std::ios_base::trunc | ::std::ios_base::out);
        if (f.fail ())
            nits.pick (nit_cannot_create_file, es_catastrophic, ec_shadow, "cannot create ", s.string ());
        else
        {   document_ -> shadow (ss, version ());
            f << ss.str ();
            f.close ();
            if (changed) ::boost::filesystem::permissions (s, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::remove_perms); } }
    catch (...)
    {   nits.pick (nit_shadow_failed, es_catastrophic, ec_shadow, "error writing ", s.string ());
        throw; } }
