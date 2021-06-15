/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "attribute/avm_data.h"

hav_t havt_q [] =
{   { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_q, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_q, a_cite },
    HTMLPLUS_ATTRIBUTES (elem_q),
    HTML23_CLID_ATTRIBUTES (elem_q),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_q),

    HTMLPLUS_ATTRIBUTES (elem_quote),

    MATH3_DEFS_ATTRIBUTES (elem_quotient),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
