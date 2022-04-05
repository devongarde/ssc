/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

vstr_t url::standard_image_extensions_, url::standard_text_extensions_;

bool url::operator == (const url& rhs) const
{   return (current_ == rhs.current_) && (protocol_ == rhs.protocol_) && (params_ == rhs.params_); }

void url::init (nitpick& )
{   standard_text_extensions_.resize (3);
    ::gsl::at (standard_text_extensions_, 0) = "html";
    ::gsl::at (standard_text_extensions_, 1) = "shtml";
    ::gsl::at (standard_text_extensions_, 2) = "htm";
    standard_image_extensions_.resize (4);
    ::gsl::at (standard_image_extensions_, 0) = "jpg";
    ::gsl::at (standard_image_extensions_, 1) = "jpeg";
    ::gsl::at (standard_image_extensions_, 2) = "gif";
    ::gsl::at (standard_image_extensions_, 3) = "png"; }

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
        if (pr.parse (nits, v, decode (trim_the_lot_off (url)), current))
        {   if (has_component (es_query))
            {   parameters pa (v, pr.get_component (es_query));
                params_.swap (pa); } }
        protocol_.swap (pr);
        valid_ = protocol_.is_valid (); } }

vurl_t split_urls_by_space (nitpick& nits, const html_version& ver, const ::std::string& s)
{   vstr_t v (split_by_space (s));
    vurl_t res;
    for (auto z : v)
        res.push_back (url (nits, ver, z));
    return res; }

bool url::sanity_test () const
{   // only http: & https: processed for now
    if (empty ()) return false;
    if (! has_protocol ()) return true; // presume internal link.
    return is_usable (); }

bool url::standard_extension (const e_mime_category mime) const
{   ::std::string ext (filename ());
    if (! ext.empty ())
    {   const ::std::string::size_type pos = ext.find ('.');
        if ((pos != ::std::string::npos) && (pos < ext.length ()))
        {   ext = ext.substr (0, pos + 1);
            switch (mime)
            {   case mc_text :
                    return is_one_of (ext, standard_text_extensions_);
                case mc_image :
                    return is_one_of (ext, standard_image_extensions_);
                default: break; } } }
    return false; }

bool url::verify (nitpick& nits, const html_version& v, element& e)
{   if (! context.links ()) return true;
    if (is_simple_id ()) return true; // verify_id will check the id is valid
    if (is_local () && ! e.get_page ().check_links ()) return true;
    const directory* d = e.get_page ().get_directory ();
    if (d != nullptr) if (! d -> verify_url (nits, v, *this)) return false;
    if (is_local ())
    {   nitpick nuts;
        ::boost::filesystem::path target (d -> get_disk_path (nuts, *this));
        e.get_page ().note_lynx (get_fileindex (target));
        if (context.crosslinks () && has_id () && (has_path () || has_file ()))
        {   if (target.empty ()) return false;
            if (get_fileindex (e.get_page ().get_disk_path ()) != get_fileindex (target))
                add_sought (e.get_page ().get_disk_path (), e.node ().line (), target, id (), e.own_attributes ().test (a_hidden), e.own_itemtype (), e.node ().id ()); } }
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
    ss << original (); }

void wombats (nitpick& nits, const html_version& v, const ::std::string& u)
{   if (u.find ("//") == ::std::string::npos) check_identifier_spelling (nits, v, u);
    else if (u.find ("//wwww") != ::std::string::npos)
        nits.pick (nit_wwww, es_info, ec_namespace, "four 'w's? the world wide web for wombats?!"); }
