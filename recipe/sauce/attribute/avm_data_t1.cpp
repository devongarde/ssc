/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

hav_t havt_t [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_t, a_class },
    { { HTML_JAN06 }, { HTML_JUN06 }, elem_t, a_datetime },
    STANDARD_HTML5_ATTRIBUTES (elem_t),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tab [] =
{   { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_tab, a_align },
    { { HTML_PLUS }, { HTML_PLUS }, elem_tab, a_at },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_id },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_indent },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_to },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tabbox [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_tabbox),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_table [] =
{   { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_table, a_align },
    { { HTML_3_2, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_table, a_background },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_table, a_bgcolour },
    { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_2070 }, { XHTML_2_0 }, elem_table, a_border },
    { { HTML_JUL11 }, { HTML_DEC12 }, elem_table, a_border },
    { { HTML_5_0, HV_W3 }, { HTML_5_3 }, elem_table, a_border },
    { { HTML_2_0, HV_NOT30 }, { XHTML_2_0 }, elem_table, a_cellspacing },
    { { HTML_2_0, HV_NOT30 }, { XHTML_2_0 }, elem_table, a_cellpadding },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_clear },
    { { HTML_2_0 }, { HTML_3_0 }, elem_table, a_cols },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_colspec },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_datasrc },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_dp },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_table, a_frame },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_table, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_noflow },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_nowrap },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_table, a_rules },
    { { HTML_JAN13 }, { HTML_DEC15 }, elem_table, a_sortable },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_summary },
    { { HTML_JAN10 }, { HTML_JUN11 }, elem_table, a_summary },
    { { HTML_2_0 }, { HTML_3_0 }, elem_table, a_units },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_table, a_width },
    HTMLPLUS_ATTRIBUTES (elem_table),
    HTML23_CLID_ATTRIBUTES (elem_table),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_table),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tan [] =
{   MATH3_DEFS_ATTRIBUTES (elem_tan),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tanh [] =
{   MATH3_DEFS_ATTRIBUTES (elem_tanh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tbody [] =
{   { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tbody, a_align },
    { { HTML_2_0, 0, HE_IE | HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3}, { XHTML_2_0 }, elem_tbody, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tbody, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tbody),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tbody),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tbreak [] =
{   SVG_CONDITIONAL_ATTRIBUTES (elem_tbreak),
    SVG_HTML_ATTRIBUTES (elem_tbreak),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_td [] =
{   { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_abbr },
    { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_1942 }, { XHTML_2_0 }, elem_td, a_align },
    { { HTML_2_0 }, { HTML_3_0 }, elem_td, a_axes },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_td, a_axis },
    { { HTML_3_2, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_td, a_background },
    { { HTML_2_0, 0, HE_IE }, { HTML_2_0 }, elem_td, a_bgcolour },
    { { HTML_4_0, HV_DEPRECATED4, HE_IE }, { XHTML_2_0 }, elem_td, a_bgcolour },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_td, a_cell },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_td, a_char },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_char },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_td, a_charoff },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_charoff },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_td, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_td, a_dp },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_headers },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_td, a_headers },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_height },
    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_nowrap },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_td, a_rowspan },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_scope },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_td, a_valign },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_width },
    HTML23_CLID_ATTRIBUTES (elem_td),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_td),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_template [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_template),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_tendsto [] =
{   { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_tendsto, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_tendsto),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_text [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, a_editable },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_text, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_hyphens },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_inline_size },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_text, a_lengthadjust },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_line_break },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_line_height },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_overflow_wrap },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_text, a_rotate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_shape_image_threshold },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_shape_inside },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_shape_margin },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_shape_padding },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_shape_subtract },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_text_justify },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_text, a_textlength },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_text, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_word_break },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, a_word_wrap },
    HTML3_CLID_ATTRIBUTES (elem_text),
    SVG_CONDITIONAL_ATTRIBUTES (elem_text),
    SVG_DXY_ATTRIBUTES (elem_text),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_text, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_text),
    SVG_HTML_ATTRIBUTES (elem_text),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_text),
    SVG_PRESENTATION_ATTRIBUTES (elem_text),
    SVG_XY_ATTRIBUTES (elem_text),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_textarea [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_textarea, a_align },
    { { HTML_5_3 }, { HTML_5_3 }, elem_textarea, a_autocapitalise },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, elem_textarea, a_autocomplete },
    { { HTML_JAN09 }, { HTML_DEC19 }, elem_textarea, a_autofocus },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_cols },
    { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_textarea, a_cols },
    { { XHTML_1_0 }, { XHTML_2_0 }, elem_textarea, a_cols },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_textarea, a_cols },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_datasrc },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_textarea, a_dirname },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { HTML_UNDEF }, elem_textarea, a_disabled },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, a_editable },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_textarea, a_error },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_form },
    { { HTML_JAN13, HV_NOT52 | HV_NOT53 }, { HTML_DEC17 }, elem_textarea, a_inputmode },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_maxlength },
    { { HTML_JAN14 }, { HTML_UNDEF }, elem_textarea, a_minlength },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_name },
    { { HTML_2_0, REQUIRED }, { HTML_3_2 }, elem_textarea, a_name },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_textarea, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onchange },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onfocus },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onselect },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_textarea, a_placeholder },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_textarea, a_readonly },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_required },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, a_rotate },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_rows },
    { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_textarea, a_rows },
    { { XHTML_1_0 }, { XHTML_2_0 }, elem_textarea, a_rows },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_textarea, a_rows },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, a_transform },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_textarea),
    HTML23_CLID_ATTRIBUTES (elem_textarea),
    HTML4_FORM_ATTRIBUTES (elem_textarea),
    SVG_BOX_ATTRIBUTES (elem_textarea),
    SVG_CONDITIONAL_ATTRIBUTES (elem_textarea),
    SVG_HTML_ATTRIBUTES (elem_textarea),
    SVG_PRESENTATION_ATTRIBUTES (elem_textarea),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_textpath [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_textpath, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, a_href },
    { { HTML_SVG10, 0, HE_SVG_10_2 }, { HTML_UNDEF }, elem_textpath, a_lengthadjust },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, a_method },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, a_path },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, a_side },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, a_spacing },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, a_startoffset },
    { { HTML_SVG10, 0, HE_SVG_10_2 }, { HTML_UNDEF }, elem_textpath, a_textlength },
    SVG_CONDITIONAL_ATTRIBUTES (elem_textpath),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_textpath, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_textpath),
    SVG_HTML_ATTRIBUTES (elem_textpath),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_textpath),
    SVG_PRESENTATION_ATTRIBUTES (elem_textpath),
    SVG_XLINK_ATTRIBUTES (elem_textpath),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
