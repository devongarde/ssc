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
#include "utility/common.h"
#include "url/url_protocol.h"
#include "url/url_parameters.h"
#include "webpage/id.h"
#include "element/state.h"

class directory;

class url
{   bool valid_ = false;  // indicates url appears to be correctly formatted, NOT that the target exists
    e_protocol current_ = pr_other;
    protocol protocol_;
    parameters params_;
    html_version v_;
    static vstr_t standard_image_extensions_, standard_text_extensions_;
    void parse (nitpick& nits, const html_version& v, const ::std::string& url, const e_protocol current);
    void clear ()
    {   url e;
        swap (e); }
    void set (nitpick& nits, const html_version& v, const ::std::string& u, const e_protocol current)
    {   parse (nits, v, u, current); }
public:
    url () : valid_ (true), current_ (pr_http) { }
    url (nitpick& nits, const html_version& v, const ::std::string& u, const e_protocol current = pr_http)
        :   valid_ (true), current_ (current), v_ (v)
    {   set (nits, v, u, current); }
	url(const url&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	url (url&&) = default;
#endif // VS
	url& operator = (const url&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	url& operator = (url&&) = default;
#endif // VS
	bool operator == (const url& rhs) const;
    void reset (const url& u)
    {   url f (u);
        swap (f); }
    void reset (nitpick& nits, const ::std::string& u) // note current protocol & html version carries over as default
    {   e_protocol current = current_;
        clear ();
        set (nits, v_, u, current); }
    void reset ()
    {   clear (); }
    void swap (url& u) NOEXCEPT;
    static void init (nitpick& nits);
    void shadow (::std::stringstream& ss, const html_version& v, element* e);
    bool empty () const { return ! has_component (es_original); }
    int compare (const url& u) const { return get ().compare (u.get ()); }
    bool has_component (const e_component c) const { return ! get_component (c).empty (); }
    ::std::string get_component (const e_component c) const { return protocol_.get_component (c); }
    void reset_component (const e_component c) { return protocol_.reset_component (c); }
    bool is_protocol (const e_protocol p) const { return (get_protocol () == p); }
    e_protocol get_protocol () const { return protocol_.get_protocol (); }
    e_scheme get_scheme () const { return protocol_.scheme (); }
    bool has_args () const { return ! params_.empty (); }
    bool has_domain () const { return has_component (es_server); }
    bool has_file () const { return has_component (es_file); }
    bool has_extension () const { return has_component (es_extension); }
    bool has_id () const { return has_component (es_fragment); }
    bool has_path () const { return has_component (es_path); }
    bool has_query () const { return has_component (es_query); }
    bool has_absolute_path () const
    {   if (has_protocol ()) return true;
        if (! has_path ()) return false;
        auto ch = get_component (es_path).at (0);
        return (ch == '/'); }
    bool has_protocol () const { return ! protocol_.defaulted (); }
    bool is_http () const { return is_protocol (pr_http); }
    bool is_https () const { return is_protocol (pr_https); }
    bool is_local () const { return protocol_.defaulted () && ! empty (); }
    bool is_usable () const { return is_protocol (pr_http) || is_protocol (pr_https); }
    bool is_simple_id () const { return is_local () && ! has_path () && ! has_file () && has_id (); }
    bool invalid () const { return ! valid_; }
    bool tismoi (const url& u) const
    {   return (valid_ && u.valid_ && (protocol_ == u.protocol_)); }
    ::std::size_t arg_count () const { return params_.size (); }
    bool exists (const ::std::string& key) const
    {   return params_.exists (key); }
    ::std::string value (const ::std::string& key) const
    {   return params_.value (key); }
    ::std::string domain () const { return get_component (es_server); }
    ::std::string id () const { return get_component (es_fragment); }
    ::std::string fragment () const { return get_component (es_fragment); }
    ::std::string filename () const { return get_component (es_file); }
    ::std::string extension () const { return get_component (es_extension); }
    ::std::string original () const { return protocol_.original (); }
    ::std::string get () const
    {   if (invalid ()) return ::std::string (); return protocol_.get (); }
    ::std::string absolute (bool can_use_index = false) const
    {   if (invalid ()) return ::std::string (); return protocol_.absolute (can_use_index); }
    ::std::string page () const { return get_component (es_authority); }
    ::std::string path () const { return get_component (es_path); }
    ::std::string password () const { return get_component (es_password); }
    ::std::string get_filepath () const;
    bool sanity_test () const;
    bool standard_extension (const e_mime_category mime = mc_text) const;
    bool verify (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& flags, const vit_t& itemtypes);
    ::std::string verify_id (nitpick& nits, const html_version& v, const ids_t& ssi, const attribute_bitset& flags, const vit_t& itemtypes); };

typedef ::std::vector < url > vurl_t;
vurl_t split_urls_by_space (nitpick& nits, const html_version& v, const ::std::string& s);
