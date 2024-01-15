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
#include "utility/common.h"
#include "utility/bitset.h"

typedef ssc_bitset < e_css_property, ec_error > property_bitset;
extern const property_bitset empty_property_bitset;

inline bool any (const property_bitset& lhs, const property_bitset& rhs)
{   const property_bitset tst (lhs & rhs);
    return tst.any (); }

inline bool all (const property_bitset& lhs, const property_bitset& rhs)
{   const property_bitset tst (lhs & rhs);
    return tst == rhs; }

::std::string nameset (const property_bitset& bs);
