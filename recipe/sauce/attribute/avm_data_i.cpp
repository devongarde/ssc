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

hav_t havt_i [] =
{   HTMLPLUS_ATTRIBUTES (elem_i),
    HTML23_CLID_ATTRIBUTES (elem_i),
    STANDARD_HTML5_ATTRIBUTES (elem_i),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ident [] =
{   MATH3_DEFS_ATTRIBUTES (elem_ident),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_iframe [] =
{   { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_align },
    { { HTML_JUL18, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_iframe, a_allow },
    { { HTML_JAN13, 0, HV_NOT50 }, { HTML_UNDEF }, elem_iframe, a_allowfullscreen },
    { { HTML_JAN17 }, { HTML_DEC20 }, elem_iframe, a_allowpaymentrequest },
    { { HTML_JUL16, 0, HV_NOT51 | HV_NOT52 }, { HTML_DEC18 }, elem_iframe, a_allowusermedia },
    { { HTML_JUL20, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_iframe, a_csp },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_frameborder },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_height },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_iframe, a_height },
    { { HTML_JUL20, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_iframe, a_importance },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_iframe, a_loading },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_longdesc },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_marginheight },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_marginwidth },
    { { HTML_JAN05, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_iframe, a_mozbrowser },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_name },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_iframe, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_noresize },
    { { HTML_JUL16, 0, HV_NOT51 }, { HTML_UNDEF }, elem_iframe, a_referrerpolicy },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_iframe, a_sandbox },
    { { HTML_JUL08, 0, HV_NOT50 }, { HTML_DEC15 }, elem_iframe, a_seamless },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_scrolling },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_iframe, a_src },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_iframe, a_srcdoc },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_width },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_iframe, a_width },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_iframe),
    SVG_HTML_ATTRIBUTES (elem_iframe),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ilayer [] =
{   { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_above },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_background },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_below },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_bgcolour },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_class },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_clip },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_height },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_id },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_left },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_name },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_pagex },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_pagey },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_src },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_style },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_top },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_visibility },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_zindex },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_image [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_image, a_align },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, a_crossorigin },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_image, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_image, a_preserveaspectratio },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_image, a_shadowinherit },
    { { HTML_PLUS, REQUIRED }, { HTML_PLUS }, elem_image, a_src },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_image, a_transform },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_image, a_transin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_image, a_transout },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, a_will_change },
    HTMLPLUS_ATTRIBUTES (elem_image),
    MATH3_DEFS_ATTRIBUTES (elem_image),
    SVG_BOX_ATTRIBUTES (elem_image),
    SVG_CONDITIONAL_ATTRIBUTES (elem_image),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_image, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_image),
    SVG_HTML_ATTRIBUTES (elem_image),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_image),
    SVG_PRESENTATION_ATTRIBUTES (elem_image),
    SVG_XLINK_ATTRIBUTES (elem_image),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_imaginary [] =
{   MATH3_DEFS_ATTRIBUTES (elem_imaginary),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_imaginaryi [] =
{   MATH3_DEFS_ATTRIBUTES (elem_imaginaryi),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_img [] =
{   { { HTML_1_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_img, a_align },
    { { HTML_1_0 }, { XHTML_2_0 }, elem_img, a_alt },
    { { HTML_JAN05, REQUIRED }, { HTML_EOJ21 }, elem_img, a_alt },
    { { HTML_FEB21 }, { HTML_UNDEF }, elem_img, a_alt },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_img, a_border },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_img, a_crossorigin },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_img, a_decoding },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_img, a_height },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_img, a_hspace },
    { { HTML_JAN05, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_img, a_importance },
    { { HTML_4_01, 0, HE_CHROME }, { HTML_UNDEF }, elem_img, a_intrinsicsize },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_img, a_ismap },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, a_loading },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_img, a_longdesc },
    { { HTML_5_2, HV_W3 }, { HTML_5_3 }, elem_img, a_longdesc },
    { { HTML_3_0 }, { HTML_3_0 }, elem_img, a_md },
    { { HTML_4_01 }, { XHTML_2_0 }, elem_img, a_name },
    { { HTML_JUL16, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, elem_img, a_referrerpolicy },
    { { HTML_PLUS }, { HTML_PLUS }, elem_img, a_seethru },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_img, a_sizes },
    { { HTML_1_0, REQUIRED }, { HTML_UNDEF }, elem_img, a_src },
    { { HTML_JAN12, HV_NOT50 }, { HTML_UNDEF }, elem_img, a_srcset },
    { { HTML_3_0 }, { HTML_3_0 }, elem_img, a_units },
    { { HTML_2_0, HV_RFC_1980 | HV_NOT30 }, { HTML_UNDEF }, elem_img, a_usemap },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_img, a_valign },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_img, a_vspace },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_img, a_width },
    HTMLPLUS_ATTRIBUTES (elem_img),
    HTML23_CLID_ATTRIBUTES (elem_img),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_img),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_implies [] =
{   MATH3_DEFS_ATTRIBUTES (elem_implies),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_in [] =
{   MATH3_DEFS_ATTRIBUTES (elem_in),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_infinity [] =
{   MATH3_DEFS_ATTRIBUTES (elem_infinity),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_input [] =
{   { { HTML_2_0, HV_RFC_1867 | HV_NOT32 }, { HTML_UNDEF }, elem_input, a_accept },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_input, a_action },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_input, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_input, a_alt },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_input, a_autocapitalise },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_autocomplete },
    { { HTML_JAN09, 0, HE_SAFARI }, { HTML_UNDEF }, elem_input, a_autocorrect },
    { { HTML_JAN09 }, { HTML_DEC19 }, elem_input, a_autofocus },
    { { HTML_5_3 }, { HTML_5_3 }, elem_input, a_capture },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_checked },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_input, a_command },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_datasrc },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_input, a_dirname },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { HTML_UNDEF }, elem_input, a_disabled },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_input, a_enctype },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_input, a_error },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_form },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_input, a_formaction },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_input, a_formenctype },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_input, a_formmethod },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_input, a_formnovalidate },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_input, a_formtarget },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_height },
    { { HTML_JAN09, 0, HE_SAFARI | HE_OPERA | HE_CHROME }, { HTML_UNDEF }, elem_input, a_incremental },
    { { HTML_JAN13, HV_NOT52 | HV_NOT53 }, { HTML_DEC17 }, elem_input, a_inputmode },
    { { HTML_4_01 }, { XHTML_2_0 }, elem_input, a_ismap },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_list },
    { { HTML_PLUS, HV_NOT4 | HV_NOT32 }, { HTML_UNDEF }, elem_input, a_max },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_maxlength },
    { { HTML_3_0 }, { HTML_3_0 }, elem_input, a_md },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_input, a_method },
    { { HTML_PLUS, HV_NOT4 | HV_NOT32 }, { HTML_UNDEF }, elem_input, a_min },
    { { HTML_JAN14 }, { HTML_UNDEF }, elem_input, a_minlength },
    { { HTML_JAN09, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_input, a_mozactionhint },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_multiple },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_input, a_name },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_input, a_novalidate },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_onchange },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_onfocus },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_onselect },
    { { HTML_JAN05, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_input, a_orient },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_pattern },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_placeholder },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_input, a_readonly },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_required },
    { { HTML_JAN20, 0, HE_SAFARI }, { HTML_UNDEF }, elem_input, a_results },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_size },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_src },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_step },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_input, a_target },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_type },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_input, a_usemap },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_input, a_value },
    { { HTML_JAN09, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_input, a_webkitdirectory },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_input, a_width },
    HTMLPLUS_ATTRIBUTES (elem_input),
    HTML23_CLID_ATTRIBUTES (elem_input),
    HTML4_FORM_ATTRIBUTES (elem_input),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_input),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ins [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_ins, a_cite },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_ins, a_datetime },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_id },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_lang },
    HTML3_CLID_ATTRIBUTES (elem_ins),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ins),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_int [] =
{   MATH3_DEFS_ATTRIBUTES (elem_int),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_integers [] =
{   MATH3_DEFS_ATTRIBUTES (elem_integers),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_intersect [] =
{   MATH3_DEFS_ATTRIBUTES (elem_intersect),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_interval [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_interval, a_closure },
    MATH3_STANDARD_ATTRIBUTES (elem_interval),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_inverse [] =
{   MATH3_DEFS_ATTRIBUTES (elem_inverse),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_isindex [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_dir },
    { { HTML_3_0 }, { HTML_3_0 }, elem_isindex, a_href },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_id },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_lang },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_isindex, a_prompt },
    { { HTML_4_0, HV_NOTPROD }, { HTML_UNDEF }, elem_isindex, a_style },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_title },
    HTML2_CLID_ATTRIBUTES (elem_isindex),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_item [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_rowspan },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
