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
#include "microdata/microdata_itemtype.h"

typedef uint32_t itemprop_index;
typedef ::std::vector < itemprop_index > itemprop_indices;
CONSTEXPR itemprop_index illegal_itemprop = 0xFFFFFFFF;
CONSTEXPR itemprop_index null_itemprop = 0;

void init_itemprop ();
itemprop_index make_itemprop_index (const e_schema_property p);
itemprop_indices make_itemprop_indices (const e_schema_property p);
itemprop_indices make_itemprop_indices (const vsp_t& vsp);
itemprop_index make_itemprop_index (const e_property p);
itemprop_indices make_itemprop_indices (const e_property p);

CONSTEXPR inline e_itemprop_category prop_category (const itemprop_index ii) noexcept
{   return static_cast < e_itemprop_category> (GSL_NARROW_CAST < uint32_t > (ii) >> uint32_category_shift); }

::std::string bespoke_itemprop_name (const itemprop_index ii);
itemprop_index find_itemprop_index (nitpick& nits, const html_version& v, const ::std::string& name, bool bespoke_permitted);
itemprop_indices find_itemprop_indices (nitpick& nits, const html_version& v, const ::std::string& name, bool bespoke_permitted);
::std::string itemprop_index_name (const itemprop_index ndx);
bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const ::std::string& value, const bool is_link);
bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const itemtype_index value);
