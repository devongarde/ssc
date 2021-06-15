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

hav_t havt_c [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_calendar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_calendar),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_height },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_width },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_canvas),
    SVG_HTML_ATTRIBUTES (elem_canvas),

    { { HTML_2_0, HV_DEPRECATED4 | HV_RFC_1942 }, { XHTML_2_0 }, elem_caption, a_align },
    { { HTML_3_2 }, { HTML_3_2 }, elem_caption, a_valign },
    HTMLPLUS_ATTRIBUTES (elem_caption),
    HTML23_CLID_ATTRIBUTES (elem_caption),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_caption),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_card, a_active },
    MATH3_DEFS_ATTRIBUTES (elem_card),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_card),

    MATH3_DEFS_ATTRIBUTES (elem_cartesianproduct),

    MATH3_STANDARD_ATTRIBUTES (elem_cbytes),

    MATH3_DEFS_ATTRIBUTES (elem_ceiling),

    MATH3_STANDARD_ATTRIBUTES (elem_cerror),

    { { HTML_PLUS }, { HTML_PLUS }, elem_changed, a_idref },
    HTMLPLUS_ATTRIBUTES (elem_changed),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ci, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_ci),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_circle, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_circle, a_r },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_circle, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_circle),
    SVG_CXY_ATTRIBUTES (elem_circle),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_circle, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_circle),
    SVG_HTML_ATTRIBUTES (elem_circle),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_circle),
    SVG_PRESENTATION_ATTRIBUTES (elem_circle),

    HTMLPLUS_ATTRIBUTES (elem_cite),
    HTML23_CLID_ATTRIBUTES (elem_cite),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_cite),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_clippathunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_transform },
    SVG_CONDITIONAL_ATTRIBUTES (elem_clippath),
    SVG_HTML_ATTRIBUTES (elem_clippath),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_clippath),
    SVG_PRESENTATION_ATTRIBUTES (elem_clippath),

    HTMLPLUS_ATTRIBUTES (elem_cmd),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_base },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_cn),

    HTMLPLUS_ATTRIBUTES (elem_code),
    HTML23_CLID_ATTRIBUTES (elem_code),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_code),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_col, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_col, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_col, a_span },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_valign },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_width },
    HTML2_CLID_ATTRIBUTES (elem_col),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_col),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_colgroup, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_colgroup, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_char },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_char },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_4_0, 0, HE_IE }, { XHTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_colgroup, a_span },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_width },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_width },
    HTML2_CLID_ATTRIBUTES (elem_colgroup),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_colgroup),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_local },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_name },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_rendering_in_tents },
    SVG_HTML_ATTRIBUTES (elem_colour_profile),
    SVG_XLINK_ATTRIBUTES (elem_colour_profile),

    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_checked },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_command },
    { { HTML_JAN05 }, { HTML_JUN09 }, elem_command, a_default },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_disabled },
    { { HTML_JAN05 }, { HTML_DEC08 }, elem_command, a_hidden },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_icon },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_label },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_radiogroup },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_command),

    STANDARD_HTML5_ATTRIBUTES (elem_commandset),

    MATH3_DEFS_ATTRIBUTES (elem_complexes),

    MATH3_DEFS_ATTRIBUTES (elem_compose),

    MATH3_STANDARD_ATTRIBUTES (elem_condition),

    { { HTML_2_0 }, { HTML_4_01 }, elem_comment, a_data },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_comment, MAJOR_4_0, MINOR_4_0),

    MATH3_DEFS_ATTRIBUTES (elem_conjugate),

    { { HTML_JAN05 }, { HTML_UNDEF }, elem_content, a_select },
    STANDARD_HTML5_ATTRIBUTES (elem_content),

    MATH3_DEFS_ATTRIBUTES (elem_cos),

    MATH3_DEFS_ATTRIBUTES (elem_cosh),

    MATH3_DEFS_ATTRIBUTES (elem_cot),

    MATH3_DEFS_ATTRIBUTES (elem_coth),

    HTML3_CLID_ATTRIBUTES (elem_credit),

    MATH3_DEFS_ATTRIBUTES (elem_cs),

    MATH3_DEFS_ATTRIBUTES (elem_csc),

    MATH3_DEFS_ATTRIBUTES (elem_csch),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_csymbol, a_cd },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_csymbol, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_csymbol),

    MATH3_DEFS_ATTRIBUTES (elem_curl),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_cursor, a_externalresourcesrequired },
    SVG_CONDITIONAL_ATTRIBUTES (elem_cursor),
    SVG_HTML_ATTRIBUTES (elem_cursor),
    SVG_XLINK_ATTRIBUTES (elem_cursor),
    SVG_XY_ATTRIBUTES (elem_cursor),

    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_disabled },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_form },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_name },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_readonly },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_custom),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
