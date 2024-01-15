/*
ssc (static site checker)
File Info
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
#include "css/css.h"
#include "css/global.h"
#include "css/media.h"

class page;
typedef ::std::map < ::std::string, css_ptr > mcss_t;

class css_group
{   friend struct arguments;
    smsid_t elements_;
    bool merged_ = false, told_ = false;
    element_bitset bs_;
    page& page_;
    mcss_t mcss_;
    dst_ptr snippets_, transforms_;
    namespaces_ptr ns_;
    media_t media_; 
    bool note_class (const ::std::string& s);
    bool note_element_class (const ::std::string& s);
    bool note_element_id (const ::std::string& s);
    bool note_id (const ::std::string& s);
    css_ptr parse ( dst_ptr dst, const ::std::string& content, const html_version& v, const namespaces_ptr& namespaces, bool sv, bool snippet, const ::std::string& abs, const element_bitset eb,
                    int line = 0, const e_element e = elem_undefined, const ::boost::filesystem::path dp = ::boost::filesystem::path ());
public:
    DELETE_CONSTRUCTORS (css_group);
    explicit css_group (page& p);
    css_ptr parse (const ::std::string& content, const html_version& v, bool sv, int line = 0, const e_element e = elem_undefined);
    bool parse (const ::std::string& content, const html_version& v, const namespaces_ptr& namespaces, const element_bitset eb, bool sv,
                int line = 0, const e_element e = elem_undefined, const ::boost::filesystem::path dp = ::boost::filesystem::path ());
    bool parse_file (nitpick& nits, const namespaces_ptr& ns, const url& u, const bool state_version = false, const bool local = true, const bool reparse = false, const bool xxx = false);
    css_ptr parse_media_queries (   const ::std::string& content, const html_version& v, page& p, const namespaces_ptr& namespaces, const element_bitset eb, bool sv,
                                    int line = 0, const e_element e = elem_undefined);
    bool parse_transform (  const ::std::string& content, const html_version& v, const namespaces_ptr& namespaces, const element_bitset eb, bool sv,
                            int line = 0, const e_element e = elem_undefined);
    bool note_class (const e_element e, const ::std::string& s);
    bool note_id (const e_element e, const ::std::string& s);
    bool note_element (const e_element e);
    bool has_class (const ::std::string& id) const;
    bool has_id (const ::std::string& id) const;
    void validate ();
    void accumulate (nitpick& nits) const;
    void accumulate (stats_t* s) const;
    bool has_custom_prop (const ::std::string& name) const;
    void note_custom_prop (const ::std::string& name);
    bool has_custom_media (const ::std::string& name) const;
    void note_custom_media (const ::std::string& name, const ::std::string& def);
    const page& get_page () const { return page_; }
    page& get_page () { return page_; }
    bool note_str (const e_gsstr g, const ::std::string& s);
    bool has_str (const e_gsstr g, const ::std::string& id) const;
    sstr_t get_strs (const e_gsstr g) const;
    const media_t& media () const { return media_; }
    media_t& media () { return media_; }
    const namespaces_ptr namespaces () const { return ns_; }
    bool told () const { return told_; }
    void told (const bool b) { told_ = b; }
    const smsid_t& get_elements () const noexcept { return elements_; }
    ::std::string review (mmac_t& mac, const ::std::string& sp, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const; };
