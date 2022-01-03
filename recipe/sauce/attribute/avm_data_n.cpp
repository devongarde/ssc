/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

hav_t havt_n [] =
{   MATH3_DEFS_ATTRIBUTES (elem_naturalnumbers),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_nav, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_nav),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_navigation, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_navigation),

    MATH3_DEFS_ATTRIBUTES (elem_neq),

    { { HTML_JAN08 }, { HTML_DEC08 }, elem_nest, a_filter },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_nest, a_mode },
    STANDARD_HTML5_ATTRIBUTES (elem_nest),

    { { HTML_TAGS }, { HTML_1_0 }, elem_nextid, a_n },
    { { HTML_1_0, REQUIRED }, { HTML_3_0 }, elem_nextid, a_n },

    XHTML2_ATTRIBUTES (elem_nl),

    COMMON_HTML4_ATTRIBUTES (elem_noframes),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_none, a_xmlns },

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_noscript),

    MATH3_DEFS_ATTRIBUTES (elem_not),

    { { HTML_3_0 }, { HTML_3_0 }, elem_note, a_clear },
    { { HTML_PLUS, HV_NOT2 }, { HTML_PLUS }, elem_note, a_role },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_note, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_note, a_md },
    HTMLPLUS_ATTRIBUTES (elem_note),
    HTML3_CLID_ATTRIBUTES (elem_note),

    MATH3_DEFS_ATTRIBUTES (elem_notanumber),

    MATH3_DEFS_ATTRIBUTES (elem_notin),

    MATH3_DEFS_ATTRIBUTES (elem_notprsubset),

    MATH3_DEFS_ATTRIBUTES (elem_notsubset),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
