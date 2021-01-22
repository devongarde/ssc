/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_master.h"
#include "microdata/microdata_itemtype.h"
#include "schema/schema_type.h"

class directory;
class url;

::std::string load_reference (nitpick& nits, const directory& d, const url& u);

template < > struct type_master < t_url > : type_base < url, t_url >
{   typedef url base_type, value_type;
    url value_;
    type_master () = default;
    static bool is_url () { return true; }
    ::std::string get_string () const { return value_.get (); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   nits.pick (nit_empty_link, es_warning, ec_link, "empty link");
            type_base < url, t_url > :: status (s_empty); }
        else
        {   value_.reset (nits, ss);
            type_base < url, t_url > :: status (s_good); } }
    void swap (type_master < t_url >& t) NOEXCEPT
    {   value_.swap (t.value_);
        type_base < url, t_url >::swap (t); }
    void reset ()
    {   value_.reset ();
        type_base < url, t_url > :: reset (); }
    bool verify_url (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& flags, const vit_t& itemtypes)
    {   if (! context.links ()) return true;
        if (! type_base < url, t_url > :: good ()) return true;
        return value_.verify (nits, v, d, pagename, line, flags, itemtypes); }
    void verify_id (nitpick& nits, const html_version& v, ids_t& ids, const attribute_bitset& flags, const vit_t& itemtypes)
    {   value_.verify_id (nits, v, ids, flags, itemtypes); }
    vurl_t get_urls () const
    {   return vurl_t (1, value_); }
    static url default_value () { return url (); }
    bool has_value (const url& b) const { return good () && (value_ == b); }
    url get () const { return value_; }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   ss << "=\""; value_.shadow (ss, v, e); ss << '"'; }
    ::std::string original () const { return get_string (); } };

template < > struct type_master < t_local_url > : type_master < t_url >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good ())
            if (value_.has_domain () || value_.has_absolute_path ())
            {   nits.pick (nit_relative_path, es_error, ec_type, quote (s), " must be a relative path to a local file");
                type_base < url, t_url > :: status (s_invalid); } } };

template < > struct type_master < t_absolute_url > : type_master < t_url >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good ())
            if (! value_.has_domain () || ! value_.has_absolute_path () || ! value_.has_protocol ())
            {   nits.pick (nit_relative_path, es_error, ec_type, quote (s), " must be an absolute url (including domain and absolute path)");
                type_base < url, t_url > :: status (s_invalid); } } };

template < > struct type_master < t_schema > : type_master < t_url >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   html_version sv (context.schema_ver ());
        type_master < t_url > :: set_value (nits, sv, s);
        if (type_master < t_url > :: good ())
            if (! value_.has_domain () || ! value_.has_absolute_path () || ! value_.has_protocol ())
            {   nits.pick (nit_schema_url, ed_jul20, "5.2.2 Items", es_error, ec_type, quote (s), " must be an absolute URL identifying a standard microdata type (for example, those that start with 'http://schema.org/')");
                type_base < url, t_url > :: status (s_invalid); }
            else if (! is_schema_domain (value_.domain ()))
            {   nits.pick (nit_schema_domain, es_error, ec_type, quote (s), " is a microdata domain unknown to " PROG);
                type_base < url, t_url > :: status (s_invalid); }
            else if (! value_.is_http () && ! value_.is_https ())
            {   nits.pick (nit_schema_url, es_error, ec_type, quote (s), " should be https (it's an identifier, not a link)");
                type_base < url, t_url > :: status (s_invalid); }
            else if (sch :: parse (nits, v, value_.get_filepath ()) == sch_illegal)
            {   nits.pick (nit_unrecognised_schema, es_warning, ec_type, quote (s), " is unrecognised by " PROG);
                type_base < url, t_url > :: status (s_invalid); } }
    static bool is_url () { return false; }
    vurl_t get_urls () const
    {   return vurl_t (); } };

template < > struct type_master < t_urls > : type_base < url, t_urls >
{   typedef url base_type;
    typedef vurl_t value_type;
    vurl_t value_;
    type_master () = default;
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
    void swap (type_master < t_urls >& t) NOEXCEPT
    {   value_.swap (t.value_);
        type_base < url, t_urls > :: swap (t); }
    void reset ()
    {   value_.clear ();
        type_base < url, t_urls > :: reset (); }
    static bool is_url () { return true; }
    bool verify_url (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& flags, const vit_t& itemtypes)
    {   if (! context.links ()) return true;
        bool res = true;
        for (auto& u : value_)
            if (! u.verify (nits, v, d, pagename, line, flags, itemtypes))
                res = false;
        return res; }
    void verify_id (nitpick& nits, const html_version& v, ids_t& ids, const attribute_bitset& flags, const vit_t& itemtypes)
    {   for (auto& u : value_)
            u.verify_id (nits, v, ids, flags, itemtypes); }
    static vurl_t default_value () { return vurl_t (); }
    vurl_t get () const { return value_; }
    bool has_value (const base_type& b) const
    {   for (auto u : value_)
            if (u == b) return true;
        return false; }
    vurl_t get_urls () const
    {   return value_; } };

template < > struct type_master < t_xmlurl > : type_master < t_url >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_url > :: set_value (nits, v, s);
        if (type_master < t_url > :: good () && ! v.xhtml ())
        {   nits.pick (nit_requires_xhtml, es_error, ec_type, quote (s), " is only valid in XHTML");
            type_base < url, t_url > :: status (s_invalid); } } };
