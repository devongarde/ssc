/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "rdf/rdfa_type.h"

typedef uint32_t prop_index;
typedef ::std::vector < prop_index > prop_indices;
constexpr prop_index illegal_prop = 0xFFFFFFFF;
constexpr prop_index null_prop = 0;

inline prop_index make_prop_index (const e_schema_property p)
{   PRESUME (p <= sp_illegal, __FILE__, __LINE__);
    return static_cast < prop_index> (p); }

prop_indices make_prop_indices (const prop_index p);
prop_indices make_prop_indices (const e_schema_property p);
prop_indices make_prop_indices (const vsp_t& vsp);
::std::string bespoke_prop_name (const prop_index ii);
prop_indices find_prop_indices (nitpick& nits, const html_version& v, const vsh_t& vs, const ::std::string& name, bool bespoke_permitted);
::std::string prop_index_name (const prop_index ndx);
bool is_valid_prop (nitpick& nits, const html_version& v, const type_index t, const prop_index ndx, const ::std::string& value, const bool is_link);
bool is_valid_prop (nitpick& nits, const html_version& v, const type_index t, const prop_index ndx, const type_index value);
