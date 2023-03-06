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

void state_init ();

typedef ssc_bitset < e_element, last_element_tag > element_bitset;
typedef ::std::vector < element_bitset > v_eb;

extern const element_bitset empty_element_bitset;
extern element_bitset autocapitalise_bitset;
extern element_bitset faux_bitset;
extern element_bitset form_bitset;
extern element_bitset header_bitset;
extern element_bitset interactive_bitset;
extern element_bitset label_bitset;
extern element_bitset listed_bitset;
extern element_bitset media_bitset;
extern element_bitset non_standard_bitset;
extern element_bitset sectioning_bitset;
extern element_bitset block_bitset;
extern element_bitset script_bitset;
extern element_bitset block_replaced_bitset;
extern element_bitset inline_bitset;
extern element_bitset css_block_bitset;
extern element_bitset css_nonblock_bitset;
extern element_bitset css_noninline_bitset;

inline bool any (const element_bitset& lhs, const element_bitset& rhs)
{   const element_bitset tst (lhs & rhs);
    return tst.any (); }

inline bool all (const element_bitset& lhs, const element_bitset& rhs)
{   const element_bitset tst (lhs & rhs);
    return tst == rhs; }

::std::string nameset (const element_bitset& bs);
void merge_smsid (smsid_t& a, const element_bitset& b, const int n = 0);
