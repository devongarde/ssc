/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "url/url.h"
#include "main/context.h"
#include "url/url_protocol.h"
#include "url/url_sanitise.h"
#include "webpage/directory.h"
#include "webpage/page.h"
#include "utility/quote.h"
#include "webpage/crosslink.h"
#include "element/element.h"
#include "webpage/external.h"

sstr_t url::standard_image_extensions_, url::standard_text_extensions_;

bool url::operator == (const url& rhs) const
{   return (current_ == rhs.current_) && (protocol_ == rhs.protocol_) && (params_ == rhs.params_); }

void url::init (nitpick& )
{   standard_text_extensions_.insert (HTML_EXT);
    standard_text_extensions_.insert ("shtml");
    standard_text_extensions_.insert ("htm");
    standard_text_extensions_.insert (XHTML_EXT);
    standard_image_extensions_.insert ("jpg");
    standard_image_extensions_.insert ("jpeg");
    standard_image_extensions_.insert ("gif");
    standard_image_extensions_.insert ("png"); }

void url::swap (url& u) noexcept
{   ::std::swap (valid_, u.valid_);
    ::std::swap (current_, u.current_);
    v_.swap (u.v_);
    protocol_.swap (u.protocol_);
    params_.swap (u.params_); }

void url::parse (nitpick& nits, const html_version& v, const ::std::string& url, const e_protocol current)
{   if (url.empty ())
        valid_ = false;
    else
    {   protocol pr;
        pr.set_component (es_original, url);
        ::std::string s (trim_the_lot_off (uq3 (url)));
        if (context.analysis () >= anal_aug25)
            if (! process_url_templates (nits, v, s))
                valid_ = false;
        pr.set_component (es_template, s);
        if (! pr.parse (nits, v, decode (s), current)) valid_ = false;
        if (valid_)
            if (has_component (es_query))
            {   parameters pa (v, pr.get_component (es_query));
                params_.swap (pa); }
        protocol_.swap (pr);
        valid_ = valid_ && protocol_.is_valid (); } }

vurl_t split_urls_by_space (nitpick& nits, const html_version& ver, const ::std::string& s)
{   vstr_t v (split_by_space (s));
    vurl_t res;
    for (auto z : v)
        res.push_back (url (nits, ver, z));
    return res; }

bool url::sanity_test () const
{   if (empty ()) return false;
    if (! has_protocol ()) return true; // presume internal link.
    return is_usable (); }

bool url::is_potentially_naughty () const
{   if (empty () || is_self () || ! has_protocol () || ! has_domain ()) return false;
    return (! is_lan_domain (*this) && ! is_example_domain (*this)); }

bool url::standard_extension (const e_mime_category mime) const
{   ::std::string ext (filename ());
    if (! ext.empty ())
    {   const ::std::string::size_type pos = ext.find ('.');
        if ((pos != ::std::string::npos) && (pos < ext.length ()))
        {   ext = ext.substr (0, pos + 1);
            switch (mime)
            {   case mc_text :
                    return standard_text_extensions_.find (ext) != standard_text_extensions_.cend ();
                case mc_image :
                    return standard_image_extensions_.find (ext) != standard_image_extensions_.cend ();
                default: break; } } }
    return false; }

bool url::verify (nitpick& nits, const html_version& v, const directory* const d)
{   VERIFY_NOT_NULL (d, __FILE__, __LINE__);
    if (! context.links ()) return true;
    if (is_simple_id ()) return true; // verify_id will check the id is valid
    if (is_local_reference () && ! has_absolute_path ()) return false;
    return d -> verify_url (nits, v, *this); }

bool url::verify (nitpick& nits, const html_version& v, element& e)
{   if (! context.links ()) return true;
    if (is_simple_id ()) return true; // verify_id will check the id is valid
    if (is_local_reference () && ! e.get_page ().check_links ()) return true;
    const directory* d = e.get_page ().get_directory ();
    if (d != nullptr)
    {   if (! d -> verify_url (nits, v, *this)) return false;
        if (is_local_reference ())
        {   nitpick nuts;
            ::boost::filesystem::path target (d -> get_disk_path (nuts, *this));
            e.get_page ().note_lynx (get_fileindex (target));
            if (context.crosslinks () && has_id () && (has_path () || has_file ()))
            {   if (target.empty ()) return false;
                if (get_fileindex (e.get_page ().get_disk_path ()) != get_fileindex (target))
                    add_sought (e.get_page ().get_disk_path (), e.node ().line (), target, id (), e.own_attributes ().test (a_hidden), e.own_itemtype (), e.node ().id ()); } } }
    return true; }

void url::verify_id (element& e)
{   if (! empty ())
        if (! fragment ().empty ())
        {   bool is_me = ! has_file () && ! has_path ();
            if (! is_me)
            {   const fileindex_t host_ndx = e.get_ids ().ndx ();
                ::boost::filesystem::path host_path (get_disk_path (host_ndx));
                if (! has_path ())
                {   is_me = (filename () == host_path.filename ().string ());
                    if (! is_me)
                    {   ::boost::filesystem::path sought (host_path.parent_path ());
                        sought /= filename ();
                        add_sought (host_path, e.get_ids ().data (), sought, fragment (), e.ancestral_attributes ().test (a_hidden), e.vit (), e.node ().id ()); } }
                else
                {   ::std::string fp (get_filepath ());
                    if (fp.at (0) == '/')
                    {   const fileindex_t ndx = get_fileindex (fp);
                        is_me = (host_ndx == ndx);
                        if (! is_me)
                            add_sought (host_path, e.get_ids ().data (), get_disk_path (ndx), fragment (), e.ancestral_attributes ().test (a_hidden), e.vit (), e.node ().id ()); } } }
            if (is_me)
                ids_t::is_good_id (e, fragment (), ec_url, nit_url_id_unfound, true); } }

::std::string url::get_filepath () const
{   ::std::string fn, pt;
    if (! has_file ()) fn = context.index ();
    else fn = filename ();
    if (! has_domain ())
        pt = path ();
    else
    {   pt = "/";
        if (has_path ())
            if (path ().at (0) == '/') pt = path ();
            else pt += path (); }
    if (pt.empty ()) return fn;
    if (pt.at (pt.length () - 1) != '/') pt += "/";
    pt += fn;
    return sanitise (pt); }

void url::shadow (::std::stringstream& ss, const html_version& v, element* e)
{   if ((context.copy () >= c_deduplicate) && is_local () && has_file ())
    {   ::std::string f (get_filepath ());
        PRESUME (! f.empty (), __FILE__, __LINE__);
        if (f.at (0) != '/')
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            const directory* const d = e -> get_page ().get_directory ();
            VERIFY_NOT_NULL (d, __FILE__, __LINE__);
            f = join_and_sanatise_site_paths (d -> get_site_path (), f); }
        const fileindex_t ndx = get_fileindex (f);
        if ((ndx != nullfileindex) && isdu (ndx))
        {   url u2 (*this);
            nitpick nits;
            u2.reset (nits, get_site_path (du (ndx)));
            if (nits.worst () > es_error) // e.g. no error
            {   u2.shadow (ss, v, e); return; } } }
    ss << temple (); }

bool url::is_local_reference () const
{   if (rc_) return ref_;
    rc_ = ref_ = true;
    if (is_local ()) return true;
    if (! has_domain ()) return true;
    const sstr_t& site = context.site ();
    const ::std::string& dom = domain ();
    if (site.find (dom) != site.cend ()) return true;
    const ::std::string::size_type dl = dom.length ();
    for (auto s : site)
    {   const ::std::string::size_type sl = s.length ();
        if ((dl > sl) && compare_no_case (s, dom.substr (dl-sl)))
            return true; }
    ref_ = false;
    return false; }

::std::string mong_var_val (nitpick& nits, const ::std::string& s, const bool sauce, const bool zeq)
{   ::std::string::size_type mx = s.size ();
    if (mx == 0) return ::std::string ();
    ::std::string var (s);
    bool splat = false;
    if (s.at (mx - 1) == '*')
        if (mx == 1)
        {   nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, quote (var), " is malformed");
            return ::std::string (); }
        else
        {   var = s.substr (0, --mx - 1);
            splat = true; }
    const ::std::string::size_type colon = var.find (':');
    if (colon == ::std::string::npos) return context.url_var_value (nits, var, sauce, zeq);
    if ((colon == 0) || (colon == var.size () - 1))
    {   nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, quote (var), " is malformed");
        return ::std::string (); }
    const ::std::string zz = var.substr (0, colon);
    const int n = lexical < int > :: cast (var.substr (colon+1));
    if (n < 0)
        nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, quote (var), " is malformed");
    if (n <= 0)
        return ::std::string ();
    if (splat)
        nits.pick (nit_unimplemented, ed_rfc_6570, "1.2. Levels and Expression Types", es_info, ec_url, quote (var), ": regretfully, " PROG " does not support explode (*)");
    const ::std::string val (context.url_var_value (nits, zz, sauce, zeq));
    if (val.size () <= static_cast < ::std::string::size_type > (n)) return val;
    return val.substr (0, n); }

::std::string limited_expand (nitpick& nits, const vstr_t& com, const ::std::string& front, const ::std::string& mid, const bool sauce = false, const bool zeq = false)
{   ::std::string s (front);
    s += desanitise (mong_var_val (nits, com.at (0), sauce, zeq), true);
    for (::std::size_t i = 1; i < com.size (); ++i)
    {   s += mid; s += desanitise (mong_var_val (nits, com.at (i), sauce, zeq), true); }
    return s; }

::std::string full_expand (nitpick& nits, const vstr_t& com, const ::std::string& front, const ::std::string& mid, const bool sauce = false, const bool zeq = false)
{   ::std::string s (front);
    s += desanitise (mong_var_val (nits, com.at (0), sauce, zeq));
    for (::std::size_t i = 1; i < com.size (); ++i)
    {   s += mid; s += desanitise (mong_var_val (nits, com.at (i), sauce, zeq)); }
    return s; }

bool url::process_url_template (nitpick& nits, const html_version& v, ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, "an empty RFC 6570 url template is naughty");
    else
    {   nitpick nuts;
        vstr_t com;
        const e_url_temp_exp ute = examine_value < t_url_temp_exp > (nuts, v, s.substr (0, 1));
        if (ute == ute_unknown) com = split_by_comma (s);
        else if (s.size () == 1) 
        {   nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, quote (s), " is malformed");
            return false; }
        else com = split_by_comma (s.substr (1));
        PRESUME (com.size () > 0, __FILE__, __LINE__);
        switch (ute)
        {   case ute_continuation :
                s = full_expand (nits, com, "&", "&", true, true);
                break;
            case ute_form :
                s = full_expand (nits, com, "?", "&", true, true);
                break;
            case ute_fragment :
                s = limited_expand (nits, com, "#", ",");
                break;
            case ute_labelled :
                s = full_expand (nits, com, ".", ".");
                break;
            case ute_parameter :
                s = full_expand (nits, com, ";", ";", true);
                break;
            case ute_reserved :
                s = limited_expand (nits, com, "", ",");
                break;
            case ute_segment :
                s = full_expand (nits, com, "/", "/");
                break;
            case ute_unknown :
                s = full_expand (nits, com, "", ",");
                break;
            default :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                return false; } }
    return true; }

bool url::process_url_templates (nitpick& nits, const html_version& v, ::std::string& s)
{   bool res = true, subbed = false;
    const ::std::string nice_template (URL_TEMPLATE_VAR ",&?#;+/*:");
    ::std::string::size_type bra = 0, ket = 0, twas = 0;
    ::std::string s2;
    for (;;)
    {   bra = s.find_first_of ("{", twas);
        if (bra == ::std::string::npos)
        {   s2 += s.substr (twas); break; }
        if (bra > twas)
        {   s2 += s.substr (twas, bra - twas);
            twas = bra; }
        ket = s.find_first_of ("}", twas + 1);
        if (ket == ::std::string::npos)
        {   s2 += s.substr (twas); break; }
        const ::std::string bitz (s.substr (bra+1, ket-bra-1));
        if (bitz.find_first_not_of (nice_template) != ::std::string::npos)
        {   nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_error, ec_url, quote (bitz), " is malformed");
            break; }
        subbed = true;
        twas = ket+1;
        ::std::string sub (bitz);
        if (! process_url_template (nits, v, sub)) res = false;
        s2 += sub; }
    if (subbed && (s != s2))
    {   if (res && context.tell (es_info))
            nits.pick (nit_url_template, ed_rfc_6570, "1.2. Levels and Expression Types", es_info, ec_url, "Replaced ", quote (s), " with ", quote (s2));
        s = s2; }
    return res; }

void world_wide_wombat_web (nitpick& nits, const html_version& v, const ::std::string& u)
{   if (u.find ("//") == ::std::string::npos) check_identifier_spelling (nits, v, u);
    else if (u.find ("//wwww") != ::std::string::npos)
        nits.pick (nit_wwww, es_info, ec_namespace, "four 'w's? the world wide wombat web?!"); }
