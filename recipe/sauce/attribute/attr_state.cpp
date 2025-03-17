/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "attribute/attr_state.h"
#include "attribute/attr.h"

const attribute_bitset empty_attribute_bitset;
attribute_bitset aria_attribute_bitset = empty_attribute_bitset;

void as_init ()
{   aria_attribute_bitset = empty_attribute_bitset | a_aria_atomic | a_aria_autocomplete | a_aria_braillelabel |
        a_aria_brailleroledescription | a_aria_busy | a_aria_checked | a_aria_colcount | a_aria_colindex | a_aria_colindextext | a_aria_colspan | a_aria_controls |
        a_aria_current | a_aria_describedby | a_aria_description | a_aria_details | a_aria_disabled | a_aria_dropeffect | a_aria_errormessage | a_aria_expanded |
        a_aria_flowto | a_aria_grabbed | a_aria_haspopup | a_aria_hidden | a_aria_invalid | a_aria_keyshortcuts | a_aria_label | a_aria_labelledby | a_aria_level |
        a_aria_live | a_aria_modal | a_aria_multiline | a_aria_multiselectable | a_aria_orientation | a_aria_owns | a_aria_placeholder | a_aria_posinset |
        a_aria_pressed | a_aria_readonly | a_aria_relevant | a_aria_required | a_aria_roledescription | a_aria_rowcount | a_aria_rowindex | a_aria_rowindextext | a_aria_rowspan |
        a_aria_selected | a_aria_setsize | a_aria_sort | a_aria_valuemax | a_aria_valuemin | a_aria_valuenow | a_aria_valuetext; }

::std::string nameset (const attribute_bitset& bs)
{   ::std::string res;
    for (::std::size_t i = 0; i < last_attribute; ++i)
        if (bs.test (i))
        {   if (! res.empty ()) res += ", ";
            res += attr::name (static_cast < e_attribute > (i)); }
    return res; }
