/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "utility/quote.h"
#include "webpage/crosslink.h"

vstr_t url::standard_image_extensions_, url::standard_text_extensions_;

bool url::operator == (const url& rhs) const
{   return (current_ == rhs.current_) && (protocol_ == rhs.protocol_) && (params_ == rhs.params_); }

void url::init (nitpick& )
{   standard_text_extensions_.resize (3);
    standard_text_extensions_ [0] = "html";
    standard_text_extensions_ [1] = "shtml";
    standard_text_extensions_ [2] = "htm";
    standard_image_extensions_.resize (4);
    standard_image_extensions_ [0] = "jpg";
    standard_image_extensions_ [1] = "jpeg";
    standard_image_extensions_ [2] = "gif";
    standard_image_extensions_ [2] = "png"; }

void url::swap (url& u) NOEXCEPT
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
    {   ::std::string::size_type pos = ext.find ('.');
        if ((pos != ::std::string::npos) && (pos < ext.length ()))
        {   ext = ext.substr (0, pos + 1);
            switch (mime)
            {   case mc_text :
                    return is_one_of (ext, standard_text_extensions_);
                case mc_image :
                    return is_one_of (ext, standard_image_extensions_);
                default: break; } } }
    return false; }

bool url::verify (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& state, const vit_t& itemtypes)
{   if (! context.links ()) return true;
    if (is_simple_id ()) return true; // verify_id will check the id is valid
    if (! d.verify_url (nits, v, *this, state, itemtypes)) return false;
    if (context.crosslinks () && is_local () && has_id () && (has_path () || has_file ()))
    {   ::boost::filesystem::path target (d.get_disk_path (nits, *this));
        if (target.empty ()) return false;
        if (get_fileindex (pagename) != get_fileindex (target))
            add_sought (pagename, line, target, id (), state.test (a_hidden), itemtypes); }
    return true; }

::std::string url::verify_id (nitpick& nits, const html_version& , const ids_t& ids, const attribute_bitset& state, const vit_t& itemtypes)
{   if (! empty ())
        if (! fragment ().empty ())
        {   bool is_me = ! has_file () && ! has_path ();
            if (! is_me)
            {   fileindex_t host_ndx = ids.ndx ();
                ::boost::filesystem::path host_path (get_disk_path (host_ndx));
                if (! has_path ())
                {   is_me = (filename () == host_path.filename ().string ());
                    if (! is_me)
                    {   ::boost::filesystem::path sought (host_path.parent_path ());
                        sought /= filename ();
                        add_sought (host_path, ids.data (), sought, fragment (), state.test (a_hidden), itemtypes); } }
                else
                {   ::std::string fp (get_filepath ());
                    if (fp.at (0) == '/')
                    {   fileindex_t ndx = get_fileindex (fp);
                        is_me = (host_ndx == ndx);
                        if (! is_me)
                            add_sought (host_path, ids.data (), get_disk_path (ndx), fragment (), state.test (a_hidden), itemtypes); } } }
            if (is_me)
                if (! ids.has_id (fragment ()))
                    nits.pick (nit_url_id_unfound, es_error, ec_url, "id(s) ", quote (fragment ()), " not found");
                else if (! compatible_id_state (state.test (a_hidden), ids.is_hidden (fragment ())))
                    nits.pick (nit_id_hidden, es_error, ec_url, "id(s) ", quote (fragment ()), " hidden"); }
    return ::std::string (); }

::std::string url::get_filepath () const
{   ::std::string fn, pt;
    if (! has_file ()) fn = context.index ();
    else fn = filename ();
    if (! has_domain ())
    {   pt = path ();
        if (pt.empty ()) pt = "/"; }
    else
    {   pt = "/";
        if (has_path ())
            if (path ().at (0) == '/') pt = path ();
            else pt += path (); }
    if (pt.empty ()) return fn;
    if (pt.at (pt.length () - 1) != '/') pt += "/";
    pt += fn;
    return sanitise (pt); }

void url::shadow (::std::stringstream& ss, const html_version& v)
{   if ((context.copy () >= c_deduplicate) && is_local () && has_file ())
    {   fileindex_t ndx = get_fileindex (get_filepath ());
        if ((ndx != nullfileindex) && isdu (ndx))
        {   url u2 (*this);
            nitpick nits;
            u2.reset (nits, get_site_path (du (ndx)));
            if (nits.worst () > es_error)
            {   u2.shadow (ss, v); return; } } }
    ss << original (); }
