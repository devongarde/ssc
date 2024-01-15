/*
ssc (static site checker)
File Info
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

hav_t havt_tfoot [] =
{   { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tfoot, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_tfoot, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tfoot, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tfoot),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tfoot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_th [] =
{   { { HTML_4_0 }, { XHTML_2_0 }, elem_th, a_abbr },
    { { HTML_JAN13 }, { HTML_UNDEF }, elem_th, a_abbr },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_align },
    { { HTML_2_0 }, { HTML_3_0 }, elem_th, a_axes },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_th, a_axis },
    { { HTML_2_0, 0, HE_IE }, { HTML_2_0 }, elem_th, a_bgcolour },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_bgcolour },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_char },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_charoff },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_th, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_th, a_dp },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_headers },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_th, a_headers },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_height },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, a_lang },
    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_nowrap },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_th, a_rowspan },
    { { HTML_2_0, HV_NOT32 }, { HTML_UNDEF }, elem_th, a_scope },
    { { HTML_JAN13 }, { HTML_DEC15 }, elem_th, a_sorted },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_th, a_valign },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_width },
    HTML23_CLID_ATTRIBUTES (elem_th),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_th),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_thead [] =
{   { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_thead, a_align },
    { { HTML_2_0, HV_NOT3 | HV_RFC_1942, HE_IE }, { XHTML_2_0 }, elem_thead, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_thead, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_thead, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_thead),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_thead),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tilde [] =
{   HTML3_CLID_ATTRIBUTES (elem_tilde),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_time [] =
{   { { HTML_JAN07 }, { HTML_UNDEF }, elem_time, a_datetime },
    { { HTML_JAN10 }, { HTML_JUN12 }, elem_time, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_time),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_times [] =
{   MATH3_DEFS_ATTRIBUTES (elem_times),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_title [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_title, a_systemlanguage },
    HTMLPLUS_ATTRIBUTES (elem_title),
    SVG_PRESENTATION_ATTRIBUTES (elem_title),
    SVG_HTML_ATTRIBUTES (elem_title),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tr [] =
{   { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tr, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_tr, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_charoff },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_nowrap },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tr, a_row },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_tr, a_valign },
    HTML23_CLID_ATTRIBUTES (elem_tr),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_track [] =
{   { { HTML_JAN11 }, { HTML_UNDEF }, elem_track, a_default },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_kind },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_label },
    { { HTML_JUL10, REQUIRED }, { HTML_UNDEF }, elem_track, a_src },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_srclang },
    STANDARD_HTML5_ATTRIBUTES(elem_track),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_traitdef [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_traitdef, a_name },
    { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_traitdef, a_namespace },
    { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_traitdef, a_type },
    { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_traitdef, a_valuetype },
    SVG_BOX_ATTRIBUTES (elem_traitdef),
    SVG_HTML_ATTRIBUTES (elem_traitdef),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_transformer [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transformer, a_type },
    SVG_HTML_ATTRIBUTES (elem_transformer),
    SVG_XLINK_ATTRIBUTES (elem_transformer),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_transition [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transition, a_dur },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transition, a_fadecolour },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transition, a_endprogress},
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transition, a_startprogress },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transition, a_subtype },
    { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_transition, a_type },
    SVG_HTML_ATTRIBUTES (elem_transition),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_transpose [] =
{   MATH3_DEFS_ATTRIBUTES (elem_transpose),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tref [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_tref, a_rotate },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_tref, a_textlength },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_tref, a_lengthadjust },
    SVG_DXY_ATTRIBUTES_EX (elem_tref, HE_SVG_10),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_tref),
    SVG_CONDITIONAL_ATTRIBUTES (elem_tref),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_tref),
    SVG_HTML_ATTRIBUTES (elem_tref),
    SVG_PRESENTATION_ATTRIBUTES (elem_tref),
    SVG_XLINK_ATTRIBUTES (elem_tref),
    SVG_XY_ATTRIBUTES_EX (elem_tref, HE_SVG_10),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_true [] =
{   MATH3_DEFS_ATTRIBUTES (elem_true),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tspan [] =
{   { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_hyphens },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tspan, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, a_lengthadjust },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_line_break },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_overflow_wrap },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, a_rotate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_text_justify },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, a_textlength },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_word_break },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_word_wrap },
    SVG_CONDITIONAL_ATTRIBUTES (elem_tspan),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_tspan, HE_SVG_2),
    SVG_DXY_ATTRIBUTES (elem_tspan),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_tspan),
    SVG_HTML_ATTRIBUTES (elem_tspan),
    SVG_PRESENTATION_ATTRIBUTES (elem_tspan),
    SVG_XY_ATTRIBUTES_EX (elem_tspan, HE_SVG_10_11_2),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tt [] =
{   HTMLPLUS_ATTRIBUTES (elem_tt),
    HTML23_CLID_ATTRIBUTES (elem_tt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
