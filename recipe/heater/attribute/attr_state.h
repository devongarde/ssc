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
#include "main/enum.h"
#include "utility/common.h"
#include "utility/bitset.h"

typedef ssc_bitset < e_attribute, last_attribute > attribute_bitset;
extern const attribute_bitset empty_attribute_bitset;

inline bool any (const attribute_bitset& lhs, const attribute_bitset& rhs)
{   const attribute_bitset tst (lhs & rhs);
    return tst.any (); }

inline bool all (const attribute_bitset& lhs, const attribute_bitset& rhs)
{   const attribute_bitset tst (lhs & rhs);
    return tst == rhs; }

::std::string nameset (const attribute_bitset& bs);
