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
{   smsid_t elements_;
    bool merged_ = false;
    element_bitset bs_;
    page* page_ = nullptr;
    mcss_t mcss_;
    dst_ptr snippets_;
    bool note_class (const ::std::string& s);
    bool note_element_class (const ::std::string& s);
    bool note_element_id (const ::std::string& s);
    bool note_id (const ::std::string& s);
    bool parse (nitpick& nits, arguments& args, dst_ptr cp, const ::std::string& content, int line = 0);
public:
    DEFAULT_CONSTRUCTORS_NO_EMPTY (css_group);
    explicit css_group (page& p);
    void swap (css_group& g) noexcept;
    bool parse (nitpick& nits, arguments& args, const ::std::string& content, int line = 0);
    bool parse_file (nitpick& nits, const namespaces_ptr& ns, page& p, const url& u, bool state_version = false);
    bool note_class (const e_element e, const ::std::string& s);
    bool note_id (const e_element e, const ::std::string& s);
    bool note_element (const e_element e);
    bool has_class (const ::std::string& id) const;
    bool has_id (const ::std::string& id) const;
    void accumulate (nitpick& nits) const;
    void accumulate (stats_t* s) const;
    const smsid_t& get_elements () const noexcept { return elements_; }
    ::std::string review (mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const; };
