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
#include "main/enum.h"

typedef ssc_map < e_nit_macro, ::std::string > mmac_t;

class nitpick;
class html_version;

class macro_t
{   mmac_t mmac_;
    bool load_template_int (nitpick& nits, const html_version& v, const ::std::string& config);
    ::std::string apply_macros_int (const ::std::string& tpl, const mmac_t& values);
public:
    void init ();
    const mmac_t& macros () const noexcept { return mmac_; }
    void set (const e_nit_macro m, const ::std::string& s);
    void set (const e_nit_macro m, ::std::string&& s);
    bool is_template_loaded ();
    bool load_template (nitpick& nits, const html_version& v);
    void dump_nits (nitpick& nits, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot);
    static ::std::string nit_content (const ::std::string& s);
    ::std::string apply (const e_nit_section& section);
    ::std::string apply (const e_nit_section& section, const mmac_t& values);
    ::std::string apply (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2);
    ::std::string apply (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3);
    ::std::string apply (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3, const mmac_t& values4); };

void reset_macro ();

typedef ::std::unique_ptr < macro_t > macro_uptr;
extern macro_uptr macro;
