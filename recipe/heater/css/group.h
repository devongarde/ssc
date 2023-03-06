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
#include "css/css.h"
#include "css/global.h"

typedef ::std::map < ::std::string, css_ptr > mcss_t;

class css_group
{   friend struct arguments;
    smsid_t elements_;
    bool merged_ = false, told_ = false;
    element_bitset bs_;
    page& page_;
    mcss_t mcss_;
    dst_ptr snippets_;
    sstr_t page_name_;
    bool note_class (const ::std::string& s);
    bool note_element_class (const ::std::string& s);
    bool note_element_id (const ::std::string& s);
    bool note_id (const ::std::string& s);
    css_ptr parse (dst_ptr dst, const ::std::string& content, const html_version& v, const namespaces_ptr& namespaces, bool sv, bool snippet, const ::std::string& abs, int line = 0);
public:
    DELETE_CONSTRUCTORS (css_group);
    explicit css_group (page& p);
    bool parse (const ::std::string& content, const html_version& v, const namespaces_ptr& namespaces, bool sv, int line = 0);
    bool parse_file (nitpick& nits, const namespaces_ptr& ns, const url& u, bool state_version = false, bool local = true);
    bool note_class (const e_element e, const ::std::string& s);
    bool note_id (const e_element e, const ::std::string& s);
    bool note_element (const e_element e);
    bool has_class (const ::std::string& id) const;
    bool has_id (const ::std::string& id) const;
    void validate ();
    void accumulate (nitpick& nits) const;
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    const page& get_page () const { return page_; }
    page& get_page () { return page_; }
    const sstr_t& page_name () const { return page_name_; }
    sstr_t& page_name () { return page_name_; }
    bool told () const { return told_; }
    void told (const bool b) { told_ = b; }
    const smsid_t& get_elements () const noexcept { return elements_; }
    ::std::string review (mmac_t& mac, const ::std::string& sp, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const; };
