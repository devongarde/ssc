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

#pragma once
#include "base/type_master.h"
#include "microdata/microdata_itemtype.h"
#include "ontology/ontology_type.h"
#include "enum/type_enum.h"

class directory;
class url;

template < > struct type_master < t_url > : type_base < url, t_url >
{   typedef url base_type, value_type;
    url value_;
    using type_base < url, t_url > :: type_base;
    static bool is_url () noexcept { return true; }
    static e_animation_type animation_type () noexcept { return at_url; }
    ::std::string get_string () const { return value_.get (); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   nits.pick (nit_empty_link, es_warning, ec_link, "empty link");
            type_base < url, t_url > :: status (s_empty); }
        else
        {   value_.reset (nits, ss);
            if (value_.valid ())
            {   type_base < url, t_url > :: status (s_good);
                if (value_.is_local () && (value_.has_file () || value_.has_path ()) && (! value_.has_absolute_path ()) && (type_base < url, t_url > :: box () != nullptr))
                {   ::boost::filesystem::path c (type_base < url, t_url > :: get_site_path ());
                    c /= value_.path ();
                    value_.set_component (es_path, c.string ());
                    value_.deduced_path (true); } } } }
    void swap (type_master < t_url >& t) noexcept
    {   value_.swap (t.value_);
        type_base < url, t_url >::swap (t); }
    void reset () noexcept
    {   value_.reset ();
        type_base < url, t_url > :: reset (); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! context.links ()) return true;
        if (! type_base < url, t_url > :: good ()) return true;
        return value_.verify (nits, v, e); }
    void verify_id (element& e)
    {   value_.verify_id (e); }
    vurl_t get_urls () const
    {   return vurl_t (1, value_); }
    static url default_value () noexcept { return url (); }
    bool has_value (const url& b) const { return good () && (value_ == b); }
    url get () const { return value_; }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   ss << "=\""; value_.shadow (ss, v, e); ss << '"'; }
    ::std::string original () const { return get_string (); } };

template < > struct type_master < t_local_url > : type_master < t_url >
{   using type_master < t_url > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good ())
            if (value_.has_domain () || value_.has_absolute_path ())
                if (! value_.deduced_path ())
                {   nits.pick (nit_relative_path, es_error, ec_type, quote (s), " must be a relative path to a local file");
                    type_base < url, t_url > :: status (s_invalid); } } };

template < > struct type_master < t_absolute_url > : type_master < t_url >
{   using type_master < t_url > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good ())
            if (value_.deduced_path () || ! value_.has_domain () || ! value_.has_absolute_path () || ! value_.has_protocol ())
            {   nits.pick (nit_relative_path, es_error, ec_type, quote (s), " must be an absolute url (including domain and absolute path)");
                type_base < url, t_url > :: status (s_invalid); } } };

template < > struct type_master < t_root_url > : type_master < t_url >
{   using type_master < t_url > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good ())
            if (value_.has_file () || value_.has_id () || value_.has_query () || value_.has_args ())
                nits.pick (nit_bad_root, es_error, ec_type, quote (s), " must only contain protocol, address, and optionally port");
            else if (value_.has_path () && ((value_.path () != "/") || (s.at (s.length ()-1) == '/')) && ! value_.deduced_path ())
                nits.pick (nit_bad_root, es_error, ec_type, quote (s), " must not contain a path");
            else return;
            type_base < url, t_url > :: status (s_invalid); } };

template < > struct type_master < t_urls > : type_base < url, t_urls >
{   typedef url base_type;
    typedef vurl_t value_type;
    vurl_t value_;
    using type_base < url, t_urls > :: type_base;
    static e_animation_type animation_type () noexcept { return at_url; }
    ::std::string get_string () const
    {   ::std::string s;
        for (auto& u : value_)
        {   if (! s.empty ()) s += ",";
            s += u.original (); }
        return s; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   nits.pick (nit_empty_link, es_warning, ec_link, "empty link");
            type_base < url, t_urls > :: status (s_empty);
            return; }
        value_ = split_urls_by_space (nits, v, ss);
        for (auto& u : value_)
            if (u.invalid ())
            {   type_base < url, t_urls > :: status (s_invalid);
                return; }
        type_base < url, t_urls > :: status (s_good); }
    void swap (type_master < t_urls >& t) noexcept
    {   value_.swap (t.value_);
        type_base < url, t_urls > :: swap (t); }
    void reset () noexcept
    {   value_.clear ();
        type_base < url, t_urls > :: reset (); }
    static bool is_url () noexcept { return true; }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! context.links ()) return true;
        bool res = true;
        for (auto& u : value_)
            if (! u.verify (nits, v, e))
                res = false;
        return res; }
    void verify_id (element& e)
    {   for (auto& u : value_)
            u.verify_id (e); }
    static vurl_t default_value () noexcept { return vurl_t (); }
    vurl_t get () const { return value_; }
    bool has_value (const base_type& b) const
    {   for (auto u : value_)
            if (u == b) return true;
        return false; }
    vurl_t get_urls () const
    {   return value_; } };

template < > struct type_master < t_xmlurl > : type_master < t_url >
{   using type_master < t_url > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good () && ! v.xhtml ())
        {   nits.pick (nit_requires_xhtml, es_error, ec_type, quote (s), " is only valid in XHTML");
            type_base < url, t_url > :: status (s_invalid); } } };

// TBD: t_urltemplate, re RFC 6570
