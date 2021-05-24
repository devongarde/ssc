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

hav_t havt_stuvwxyz [] =
{   HTMLPLUS_ATTRIBUTES (elem_s),
    HTML3_CLID_ATTRIBUTES (elem_s),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_s),

    HTMLPLUS_ATTRIBUTES (elem_samp),
    HTML23_CLID_ATTRIBUTES (elem_samp),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_samp),

    MATH3_DEFS_ATTRIBUTES (elem_scalarproduct),

    { { HTML_JUL06 }, { HTML_UNDEF }, elem_script, a_async },
    { { HTML_JUL08 }, { HTML_JUN17 }, elem_script, a_charset },
    { { HTML_5_2, HV_W3 }, { HTML_5_2 }, elem_script, a_charset },
    { { HTML_JAN13 }, { HTML_UNDEF }, elem_script, a_crossorigin },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_script, a_defer },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_script, a_defer },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_script, a_event },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_script, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_script, a_href },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_script, a_implements },
    { { HTML_JAN17, HV_NOT52 }, { HTML_UNDEF }, elem_script, a_integrity },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_script, a_language },
    { { HTML_JUL17, HV_NOT52 }, { HTML_UNDEF }, elem_script, a_nomodule },
    { { HTML_JAN16 }, { HTML_JUN17 }, elem_script, a_numberonce },
    { { HTML_JUL18 }, { HTML_UNDEF }, elem_script, a_referrerpolicy },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_script, a_src },
    { { HTML_4_0, REQUIRED }, { XHTML_2_0 }, elem_script, a_type },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_script, a_type },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_script),
    SVG_XLINK_ATTRIBUTES (elem_script),
    SVG_HTML_ATTRIBUTES (elem_script),

    MATH3_DEFS_ATTRIBUTES (elem_sdev),

    MATH3_DEFS_ATTRIBUTES (elem_sec),

    MATH3_DEFS_ATTRIBUTES (elem_sech),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_section, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_section, a_cite },
    STANDARD_HTML5_ATTRIBUTES (elem_section),

    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_align },
    { { HTML_JUL14, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, elem_select, a_autocomplete },
    { { HTML_JUL09 }, { HTML_DEC19 }, elem_select, a_autofocus },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_select, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_select, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_select, a_datasrc },
    { { HTML_3_0, HV_NOT32 | HV_NOT4 }, { HTML_UNDEF }, elem_select, a_disabled },
    { { HTML_PLUS }, { HTML_PLUS }, elem_select, a_error },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_error },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_select, a_form },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_md },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_select, a_multiple },
    { { HTML_PLUS }, { HTML_PLUS }, elem_select, a_name },
    { { HTML_2_0, REQUIRED }, { XHTML_2_0 }, elem_select, a_name },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_select, a_name },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_select, a_required },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_select, a_size },
    { { HTML_PLUS }, { HTML_PLUS }, elem_select, a_several },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_units },
    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_width },
    HTMLPLUS_ATTRIBUTES (elem_select),
    HTML23_CLID_ATTRIBUTES (elem_select),
    HTML4_FORM_ATTRIBUTES (elem_select),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_select),

    MATH3_DEFS_ATTRIBUTES (elem_selector),

    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_cd },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_definitionurl },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_encoding },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_name },
    MATH3_DEFS_ATTRIBUTES (elem_semantics),

    { { HTML_MATH1, 0, HE_MATH_1_2 }, { HTML_UNDEF }, elem_sep, a_xmlns },

    XHTML2_ATTRIBUTES (elem_separator),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_set, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_set, a_to },
    { { XHTML_1_0, 0, HE_MATH_2 }, { HTML_UNDEF }, elem_set, a_type },
    SVG11_ANAT_ATTRIBUTES (elem_set),
    SVG11_ANEV_ATTRIBUTES (elem_set),
    SVG_ANTIME_ATTRIBUTES (elem_set),
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_set),
    SVG_XLINK_ATTRIBUTES (elem_set),
    SVG_CONDITIONAL_ATTRIBUTES (elem_set),
    SVG_HTML_ATTRIBUTES (elem_set),
    MATH3_STANDARD_ATTRIBUTES (elem_set),

    MATH3_DEFS_ATTRIBUTES (elem_setdiff),

    STANDARD_HTML5_ATTRIBUTES (elem_shadow),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_share, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_share),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_sidebar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_sidebar),

    MATH3_DEFS_ATTRIBUTES (elem_sin),

    MATH3_DEFS_ATTRIBUTES (elem_sinh),

    { { HTML_JUL16, HV_WHATWG }, { HTML_UNDEF }, elem_slot, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_slot),

    HTML3_CLID_ATTRIBUTES (elem_small),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_small),

    SVG_HTML_ATTRIBUTES (elem_solidcolour),
    SVG_PRESENTATION_ATTRIBUTES (elem_solidcolour),

    { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_height },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_media },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_sizes },
    { { HTML_JUL07, REQUIRED }, { HTML_JUN14 }, elem_source, a_src },
    { { HTML_JUL14 }, { HTML_UNDEF }, elem_source, a_src },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_srcset },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_type },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_width },
    STANDARD_HTML5_ATTRIBUTES (elem_source),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datasrc },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    HTML2_CLID_ATTRIBUTES (elem_span),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_span),

    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_spot, a_id },

    HTML3_CLID_ATTRIBUTES (elem_sqrt),

    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_stop, a_offset },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_stop, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_stop),
    SVG_PRESENTATION_ATTRIBUTES (elem_stop),

    XHTML2_ATTRIBUTES (elem_stoppropagation),

    COMMON_HTML4_ATTRIBUTES (elem_strike),

    HTMLPLUS_ATTRIBUTES (elem_strong),
    HTML23_CLID_ATTRIBUTES (elem_strong),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_strong),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_style, a_disabled },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_style, a_media },
    { { HTML_JAN16 }, { HTML_DEC17 }, elem_style, a_numberonce },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_style, a_notation },
    { { HTML_4_0, 0, HE_CHROME }, { XHTML_2_0 }, elem_style, a_scoped },
    { { HTML_JUN06 }, { HTML_DEC15 }, elem_style, a_scoped },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_style, a_title },
    { { HTML_4_0 }, { HTML_DEC17 }, elem_style, a_type },
    { { HTML_JAN18, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_style, a_type },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_style, a_xmlspace },
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_style, HTML_2005, 0),
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_style, HTML_2005, 0),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_style, HE_SVG_2),
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_style),
    SVG_HTML_ATTRIBUTES (elem_style),

    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sub),
    HTML23_CLID_ATTRIBUTES (elem_sub),
    STANDARD_HTML5_ATTRIBUTES (elem_sub),

    MATH3_DEFS_ATTRIBUTES (elem_subset),

    MATH3_DEFS_ATTRIBUTES (elem_sum),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_summary),

    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sup),
    HTML23_CLID_ATTRIBUTES (elem_sup),
    STANDARD_HTML5_ATTRIBUTES (elem_sup),

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_svg, a_allow_zoom_and_pan },
    { { HTML_SVG11, 0, HE_SVG_11_12 }, { HTML_UNDEF }, elem_svg, a_baseprofile },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_svg, a_contentscripttype },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_svg, a_contentstyletype },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onabort },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, a_onafterprint },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, a_onbeforeprint },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onerror },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onscroll },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onunload },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, a_onzoom },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, a_phase },
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, elem_svg, a_playbackorder },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, a_preserveaspectratio },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, a_snapshottime },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_svg, a_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, a_syncbehaviourdefault },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, a_synctolerancedefault },
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, elem_svg, a_timelinebegin },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, a_transform },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, a_version },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, a_viewbox },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_svg, a_xmlns },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, a_zoomandpan },
    SVG_BOX_ATTRIBUTES (elem_svg),
    SVG_CONDITIONAL_ATTRIBUTES (elem_svg),
    SVG_HTML_ATTRIBUTES (elem_svg),
    SVG_DOCUMENT_EVENT_ATTRIBUTES (elem_svg),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_svg),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_svg),
    SVG_PRESENTATION_ATTRIBUTES (elem_svg),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_switch, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_switch, a_transform },
    SVG_CONDITIONAL_ATTRIBUTES (elem_switch),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_switch, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_switch),
    SVG_HTML_ATTRIBUTES (elem_switch),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_svg),
    SVG_PRESENTATION_ATTRIBUTES (elem_switch),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_class },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, a_viewbox },
    SVG_HTML_ATTRIBUTES (elem_symbol),
    SVG_BOX_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_symbol),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_symbol),
    SVG_PRESENTATION_ATTRIBUTES (elem_symbol),
    SVG_REF_XY_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),

    { { HTML_3_0 }, { HTML_3_0 }, elem_t, a_class },
    { { HTML_JAN06 }, { HTML_JUN06 }, elem_t, a_datetime },
    STANDARD_HTML5_ATTRIBUTES (elem_t),

    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_tab, a_align },
    { { HTML_PLUS }, { HTML_PLUS }, elem_tab, a_at },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_id },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_indent },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_to },

    STANDARD_HTML5_ATTRIBUTES (elem_tabbox),

    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_table, a_align },
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

    MATH3_DEFS_ATTRIBUTES (elem_tan),

    MATH3_DEFS_ATTRIBUTES (elem_tanh),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tbody, a_align },
    { { HTML_2_0, 0, HE_IE | HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3}, { XHTML_2_0 }, elem_tbody, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tbody, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tbody),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tbody),

    SVG_CONDITIONAL_ATTRIBUTES (elem_tbreak),
    SVG_HTML_ATTRIBUTES (elem_tbreak),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_abbr },
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

    STANDARD_HTML5_ATTRIBUTES (elem_template),

    { { HTML_MATH2, 0, HE_MATH_2_3_4 }, { HTML_UNDEF }, elem_tendsto, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_tendsto),

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, a_editable },
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

    { { HTML_3_0 }, { HTML_3_0 }, elem_textarea, a_align },
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
//    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_textarea),
    SVG_CONDITIONAL_ATTRIBUTES (elem_textarea),
    SVG_HTML_ATTRIBUTES (elem_textarea),
    SVG_PRESENTATION_ATTRIBUTES (elem_textarea),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_textpath, a_externalresourcesrequired },
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

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tfoot, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_tfoot, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tfoot, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tfoot),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_th, a_abbr },
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

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_thead, a_align },
    { { HTML_2_0, HV_NOT3 | HV_RFC_1942, HE_IE }, { XHTML_2_0 }, elem_thead, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_thead, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_thead, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_thead),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_thead),

    HTML3_CLID_ATTRIBUTES (elem_tilde),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_time, a_datetime },
    { { HTML_JAN10 }, { HTML_JUN12 }, elem_time, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_time),

    MATH3_DEFS_ATTRIBUTES (elem_times),

    HTMLPLUS_ATTRIBUTES (elem_title),
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_title),
    SVG_HTML_ATTRIBUTES (elem_title),

    { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tr, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_tr, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_charoff },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_nowrap },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tr, a_row },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_tr, a_valign },
    HTML23_CLID_ATTRIBUTES (elem_tr),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tr),

    { { HTML_JAN11 }, { HTML_UNDEF }, elem_track, a_default },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_kind },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_label },
    { { HTML_JUL10, REQUIRED }, { HTML_UNDEF }, elem_track, a_src },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_srclang },
    STANDARD_HTML5_ATTRIBUTES(elem_track),

    MATH3_DEFS_ATTRIBUTES (elem_transpose),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, a_externalresourcesrequired },
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

    MATH3_DEFS_ATTRIBUTES (elem_true),

    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, a_hyphens },
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

    HTMLPLUS_ATTRIBUTES (elem_tt),
    HTML23_CLID_ATTRIBUTES (elem_tt),

    HTMLPLUS_ATTRIBUTES (elem_u),
    HTML3_CLID_ATTRIBUTES (elem_u),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_u),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_ul, a_align },
    { { HTML_3_0, HV_NOT32 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_clear },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_compact },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_dingbat },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_plain },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_md },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_src },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_type },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_ul),
    HTML23_CLID_ATTRIBUTES (elem_ul),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ul),

    MATH3_DEFS_ATTRIBUTES (elem_union),

    MATH3_STANDARD_ATTRIBUTES (elem_uplimit),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_use, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_use, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, a_will_change },
    SVG_BOX_ATTRIBUTES(elem_use),
    SVG_CONDITIONAL_ATTRIBUTES (elem_use),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_use, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_use),
    SVG_HTML_ATTRIBUTES (elem_use),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_use),
    SVG_PRESENTATION_ATTRIBUTES (elem_use),
    SVG_XLINK_ATTRIBUTES (elem_use),

    HTMLPLUS_ATTRIBUTES (elem_var),
    HTML23_CLID_ATTRIBUTES (elem_var),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_var),

    MATH3_DEFS_ATTRIBUTES (elem_variance),

    HTML3_CLID_ATTRIBUTES (elem_vec),

    MATH3_STANDARD_ATTRIBUTES (elem_vector),

    MATH3_DEFS_ATTRIBUTES (elem_vectorproduct),

    { { HTML_JAN11 }, { HTML_JUN11 }, elem_video, a_audio },
    { { HTML_JUL09 }, { HTML_JUN10 }, elem_video, a_autobuffer },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_autopictureinpicture },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_autoplay },
    { { HTML_JUL07, 0, HE_MOZILLA | HE_OPERA }, { HTML_UNDEF }, elem_video, a_buffered },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_controls },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_controlslist },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_crossorigin },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_currenttime },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_disablepictureinpicture },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_video, a_disableremoteplayback },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_duration },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_end },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_externalresourcesrequired },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_height },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_initialvisibility },
    { { HTML_JUL07, 0, HE_CHROME | HE_OPERA }, { HTML_UNDEF }, elem_video, a_intrinsicsize },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_video, a_loop },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopcount },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopend },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopstart },
    { { HTML_JUL11 }, { HTML_JUN16 }, elem_video, a_mediagroup },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_muted },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_overlay },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_video, a_playcount },
    { { HTML_JAN17, HV_NOT5W3 }, { HTML_UNDEF }, elem_video, a_playsinline },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_poster },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_video, a_preload },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_preserveaspectratio },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_src },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_start },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_transformbehaviour },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_type },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_width },
    SVG_ANTIME_ATTRIBUTES (elem_video),
    SVG_BOX_ATTRIBUTES (elem_video),
    SVG_CONDITIONAL_ATTRIBUTES (elem_video),
    SVG_HTML_ATTRIBUTES (elem_video),
    SVG_PRESENTATION_ATTRIBUTES (elem_video),
    SVG_SYNC_ATTRIBUTES (elem_video),
    SVG_XLINK_ATTRIBUTES (elem_video),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_view, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_view, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_view, a_viewbox },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_view, a_viewtarget },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_view, a_zoomandpan },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_view),
    SVG_HTML_ATTRIBUTES (elem_view),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_g1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_g2 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_k },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_u1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_u1 },
    SVG_HTML_ATTRIBUTES (elem_vkern),

    STANDARD_HTML5_ATTRIBUTES(elem_wbr),

    HTML23_CLID_ATTRIBUTES (elem_xmp),

    MATH3_DEFS_ATTRIBUTES (elem_xor),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
