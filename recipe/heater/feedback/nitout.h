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
#include "type/enum.h"

typedef ssc_map < e_nit_macro, ::std::string > mmac_t;

class nitpick;
class html_version;

void init_nit_macros ();
bool is_template_loaded ();
bool load_template (nitpick& nits, const html_version& v);
void dump_nits (nitpick& nits, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot);
::std::string nit_content (const ::std::string& s);
::std::string apply_macros (const e_nit_section& section);
::std::string apply_macros (const e_nit_section& section, const mmac_t& values);
::std::string apply_macros (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2);
::std::string apply_macros (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3);
::std::string apply_macros (const e_nit_section& section, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3, const mmac_t& values4);
