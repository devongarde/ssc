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

hav_t havt_s [] =
{   HTMLPLUS_ATTRIBUTES (elem_s),
    HTML3_CLID_ATTRIBUTES (elem_s),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_s),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_samp [] =
{   HTMLPLUS_ATTRIBUTES (elem_samp),
    HTML23_CLID_ATTRIBUTES (elem_samp),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_samp),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_scalarproduct [] =
{   MATH3_DEFS_ATTRIBUTES (elem_scalarproduct),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_script [] =
{   { { HTML_JUL06 }, { HTML_UNDEF }, elem_script, a_async },
    { { HTML_APR22 }, { HTML_UNDEF }, elem_script, a_blocking },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sdev [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sdev),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_search [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_search),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sec [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sec),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sech [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sech),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_section [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_section, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_section, a_cite },
    STANDARD_HTML5_ATTRIBUTES (elem_section),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_select [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_align },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_selector [] =
{   MATH3_DEFS_ATTRIBUTES (elem_selector),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_semantics [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_cd },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_20 }, { HTML_UNDEF }, elem_semantics, a_definitionurl },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_20 }, { HTML_UNDEF }, elem_semantics, a_encoding },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_name },
    MATH3_DEFS_ATTRIBUTES (elem_semantics),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_semantics),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sep [] =
{   { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_sep, a_xmlns },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_separator [] =
{   XHTML2_ATTRIBUTES (elem_separator),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_set [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_set, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_set, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_set, a_to },
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, elem_set, a_type },
    MATH3_STANDARD_ATTRIBUTES (elem_set),
    SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES (elem_set),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_set),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_set),
    SVG_CONDITIONAL_ATTRIBUTES (elem_set),
    SVG_HTML_ATTRIBUTES (elem_set),
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_set),
    SVG_XLINK_ATTRIBUTES_EX (elem_set, HE_SVG_1_20),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_setdiff [] =
{   MATH3_DEFS_ATTRIBUTES (elem_setdiff),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_shadow [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_shadow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_share [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_share, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_share),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sidebar [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_sidebar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_sidebar),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sin [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sin),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sinh [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sinh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_slot [] =
{   { { HTML_JUL16, HV_WHATWG }, { HTML_UNDEF }, elem_slot, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_slot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_small [] =
{   HTML3_CLID_ATTRIBUTES (elem_small),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_small),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_solidcolour [] =
{   SVG_HTML_ATTRIBUTES (elem_solidcolour),
    SVG_PRESENTATION_ATTRIBUTES (elem_solidcolour),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_source [] =
{   { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_height },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_media },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_sizes },
    { { HTML_JUL07, REQUIRED }, { HTML_JUN14 }, elem_source, a_src },
    { { HTML_JUL14 }, { HTML_UNDEF }, elem_source, a_src },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_srcset },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_type },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_width },
    STANDARD_HTML5_ATTRIBUTES (elem_source),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_span [] =
{   { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datasrc },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    HTML2_CLID_ATTRIBUTES (elem_span),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_span),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_spot [] =
{   { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_spot, a_id },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sqrt [] =
{   HTML3_CLID_ATTRIBUTES (elem_sqrt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_stop [] =
{   { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_stop, a_offset },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_stop, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_stop),
    SVG_PRESENTATION_ATTRIBUTES (elem_stop),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_stoppropagation [] =
{   XHTML2_ATTRIBUTES (elem_stoppropagation),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_strike [] =
{   COMMON_HTML4_ATTRIBUTES (elem_strike),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_strong [] =
{   HTMLPLUS_ATTRIBUTES (elem_strong),
    HTML23_CLID_ATTRIBUTES (elem_strong),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_strong),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_style [] =
{   { { HTML_APR22 }, { HTML_UNDEF }, elem_style, a_blocking },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_style, a_disabled },
    { { HTML_JUL22 }, { HTML_UNDEF }, elem_style, a_disabled },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sub [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_sub, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sub),
    HTML23_CLID_ATTRIBUTES (elem_sub),
    STANDARD_HTML5_ATTRIBUTES (elem_sub),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_subset [] =
{   MATH3_DEFS_ATTRIBUTES (elem_subset),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sum [] =
{   MATH3_DEFS_ATTRIBUTES (elem_sum),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_summary [] =
{   STANDARD_HTMLS_4_5_ATTRIBUTES (elem_summary),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_sup [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_sup, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sup),
    HTML23_CLID_ATTRIBUTES (elem_sup),
    STANDARD_HTML5_ATTRIBUTES (elem_sup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_svg [] =
{   { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_svg, a_allow_zoom_and_pan },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, a_baseprofile },
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
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_svg, a_streamedcontents },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_switch [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_switch, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_switch, a_transform },
    SVG_CONDITIONAL_ATTRIBUTES (elem_switch),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_switch, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_switch),
    SVG_HTML_ATTRIBUTES (elem_switch),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_switch),
    SVG_PRESENTATION_ATTRIBUTES (elem_switch),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_symbol [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_class },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, a_preserveaspectratio },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_symbol, a_shadowinherit },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, a_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, a_viewbox },
    SVG_HTML_ATTRIBUTES (elem_symbol),
    SVG_BOX_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_symbol),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_symbol),
    SVG_PRESENTATION_ATTRIBUTES (elem_symbol),
    SVG_REF_XY_ATTRIBUTES_EX (elem_symbol, HE_SVG_2),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
