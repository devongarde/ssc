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

hav_t havt_b [] =
{   HTMLPLUS_ATTRIBUTES (elem_b),
    HTML23_CLID_ATTRIBUTES (elem_b),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_b),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bb [] =
{   { { HTML_JUL08 }, { HTML_DEC09 }, elem_bb, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_bb),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_banner [] =
{   HTML3_CLID_ATTRIBUTES (elem_banner),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bar [] =
{   HTML3_CLID_ATTRIBUTES (elem_bar),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_base [] =
{   { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_base, a_href },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_base, a_href },
    { { HTML_3_0 }, { HTML_3_0 }, elem_base, a_id },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_base, a_target },
    STANDARD_HTML5_ATTRIBUTES (elem_base),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_basefont [] =
{   { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_colour },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_face },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_size },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_basefont, MAJOR_4_0, MINOR_4_0),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bdi [] =
{   { { HTML_JAN11 }, { HTML_UNDEF }, elem_bdi, a_dir },
    STANDARD_HTML5_ATTRIBUTES (elem_bdi),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bdo [] =
{   { { HTML_2_0, HV_RFC_2070 | REQUIRED }, { HTML_2_0 }, elem_bdo, a_dir },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_bdo, a_dir },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_bdo, a_lang },
    HTML2_CLID_ATTRIBUTES (elem_bdo),
    STANDARD_HTML5_ATTRIBUTES (elem_bdo),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_below [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_below, a_sym },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bgsound [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_balance },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_loop },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_src },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_volume },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_big [] =
{   HTML3_CLID_ATTRIBUTES (elem_big),
    COMMON_HTML4_ATTRIBUTES (elem_big),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bind [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_bind),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_blockquote [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_blockquote, a_active },
    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_blockquote, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_blockquote, a_cite },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_blockquote),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_blockquote),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_blockcode [] =
{   XHTML2_ATTRIBUTES (elem_blockcode),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_body [] =
{   { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_alink },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_background },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_bgcolour },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { XHTML_2_0 }, elem_body, a_bottommargin },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { XHTML_2_0 }, elem_body, a_leftmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_link },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onafterprint },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onbeforeprint },
    { { HTML_JAN13 }, { HTML_JUN13 }, elem_body, a_onfullscreenchange },
    { { HTML_JAN13 }, { HTML_JUN13 }, elem_body, a_onfullscreenerror },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onhashchange },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_body, a_onlanguagechange },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_body, a_onload },
    { { HTML_JAN05 }, { HTML_JUN13 }, elem_body, a_onmessage },
    { { HTML_JAN05 }, { HTML_JUN13 }, elem_body, a_onmessage },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_body, a_onmessageerror },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onoffline },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_ononline },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_body, a_onpagehide },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_body, a_onpageshow },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onpopstate },
    { { HTML_JUL09 }, { HTML_DEC11 }, elem_body, a_onredo },
    { { HTML_JAN16 }, { HTML_UNDEF }, elem_body, a_onrejectionhandled },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onstorage },
    { { HTML_JUL09 }, { HTML_DEC11 }, elem_body, a_onundo },
    { { HTML_JAN16 }, { HTML_UNDEF }, elem_body, a_onunhandledrejection },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_body, a_onunload },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { HTML_3_2 }, elem_body, a_rightmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_text },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { HTML_3_2 }, elem_body, a_topmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_vlink },
    HTML23_CLID_ATTRIBUTES (elem_body),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_body),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_box [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_box, a_size },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bq [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_nowrap },
    HTML3_CLID_ATTRIBUTES (elem_bq),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_br [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_id },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_class },
    { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_br, a_clear },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_title },
    { { HTML_4_0, HV_NOTPROD }, { HTML_UNDEF }, elem_br, a_style },
    HTMLPLUS_ATTRIBUTES (elem_br),
    HTML3_CLID_ATTRIBUTES (elem_br),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_br, HTML_2005, 0),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_br, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_br),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bt [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_bt, a_class },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_button [] =
{   { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_action },
    { { HTML_JAN20, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_button, a_autocomplete },
    { { HTML_JAN09 }, { HTML_DEC19 }, elem_button, a_autofocus },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_button, a_command },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_datasrc },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_disabled },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_enctype },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_button, a_form },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formaction },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formenctype },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formmethod },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formnovalidate },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formtarget },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_button, a_menu },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_method },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_name },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_novalidate },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_onfocus },
    { { HTML_APR23 }, { HTML_UNDEF }, elem_button, a_popovertarget },
    { { HTML_APR23 }, { HTML_UNDEF }, elem_button, a_popovertargetaction },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_target },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_type },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_value },
    HTML4_FORM_ATTRIBUTES (elem_button),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_button),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_bvar [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_bvar),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_byline [] =
{   HTMLPLUS_ATTRIBUTES (elem_byline),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
