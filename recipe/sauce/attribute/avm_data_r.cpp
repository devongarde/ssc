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
#include "attribute/avm_data.h"

hav_t havt_radialgradient [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_radialgradient, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_radialgradient, a_fr },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_fx },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_fy },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_radialgradient, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, a_r },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_spreadmethod },
    SVG_CXY_ATTRIBUTES (elem_radialgradient),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_radialgradient, HE_SVG_2),
    SVG_GRAD_ATTRIBUTES (elem_radialgradient),
    SVG_HTML_ATTRIBUTES (elem_radialgradient),
    SVG_PRESENTATION_ATTRIBUTES (elem_radialgradient),
    SVG_XLINK_ATTRIBUTES (elem_radialgradient),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_range [] =
{   { { HTML_3_0, HV_REQUIRED }, { HTML_3_0 }, elem_range, a_from },
    { { HTML_3_0, HV_REQUIRED }, { HTML_3_0 }, elem_range, a_until },
    HTML_CID_ATTRIBUTES (elem_range, MAJOR_3_0, MINOR_3_0, MAJOR_3_0, MINOR_3_0),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rationals [] =
{   MATH3_DEFS_ATTRIBUTES (elem_rationals),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rb [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_rb),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_real [] =
{   MATH3_DEFS_ATTRIBUTES (elem_real),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_reals [] =
{   MATH3_DEFS_ATTRIBUTES (elem_reals),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rect [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_rect, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_rect, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, a_will_change },
    SVG_BOX_ATTRIBUTES (elem_rect),
    SVG_CONDITIONAL_ATTRIBUTES (elem_rect),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_rect, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_rect),
    SVG_HTML_ATTRIBUTES (elem_rect),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_rect),
    SVG_PRESENTATION_ATTRIBUTES (elem_rect),
    SVG_RXY_ATTRIBUTES (elem_rect),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_refcontent [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_refcontent, a_select },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_refcontent, a_transform },
    SVG_XLINK_ATTRIBUTES (elem_refcontent),
    SVG_HTML_ATTRIBUTES (elem_refcontent),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_reln [] =
{   MATH2_STANDARD_ATTRIBUTES (elem_reln),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rem [] =
{   MATH3_DEFS_ATTRIBUTES (elem_rem),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_removed [] =
{   HTMLPLUS_ATTRIBUTES (elem_removed),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_removeeventlistener [] =
{   XHTML2_ATTRIBUTES (elem_removeeventlistener),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_render [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_render, a_style },
    { { HTML_PLUS }, { HTML_PLUS }, elem_render, a_tag },
    HTMLPLUS_ATTRIBUTES (elem_render),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_root [] =
{   HTML3_CLID_ATTRIBUTES (elem_root),
    MATH3_DEFS_ATTRIBUTES (elem_root),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rp [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_rp),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl, a_xmlns },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_amount [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_amount, a_rsl_currency },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_content [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_content, a_rsl_encrypted },
    { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_content, a_rsl_lastmod },
    { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_content, a_rsl_server },
    { { HTML_RSL, HV_REQUIRED }, { HTML_UNDEF }, elem_rsl_content, a_rsl_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_copyright [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_copyright, a_rsl_contactemail },
    { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_copyright, a_rsl_contacturl },
    { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_copyright, a_rsl_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_legal [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_legal, a_rsl_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_payment [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_payment, a_rsl_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_permits [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_permits, a_rsl_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rsl_prohibits [] =
{   { { HTML_RSL }, { HTML_UNDEF }, elem_rsl_prohibits, a_rsl_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss [] =
{   { { HTML_RSS, HV_REQUIRED }, { HTML_UNDEF }, elem_rss, a_rss_version },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss, a_xmlns },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss_category [] =
{   { { HTML_RSS }, { HTML_UNDEF }, elem_rss_category, a_rss_domain },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss_cloud [] =
{   { { HTML_RSS }, { HTML_UNDEF }, elem_rss_cloud, a_rss_domain },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_cloud, a_rss_path },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_cloud, a_rss_port },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_cloud, a_rss_protocol },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_cloud, a_rss_registerprocedure },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss_enclosure [] =
{   { { HTML_RSS }, { HTML_UNDEF }, elem_rss_enclosure, a_rss_length },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_enclosure, a_rss_type },
    { { HTML_RSS }, { HTML_UNDEF }, elem_rss_enclosure, a_rss_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss_guid [] =
{   { { HTML_RSS }, { HTML_UNDEF }, elem_rss_guid, a_rss_ispermalink },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rss_source [] =
{   { { HTML_RSS, HV_REQUIRED }, { HTML_UNDEF }, elem_rss_source, a_rss_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rt [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_rt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rtc [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_rtc),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ruby [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_ruby),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_rule [] =
{   { { HTML_JAN08 }, { HTML_DEC08 }, elem_rule, a_condition },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_rule, a_mode },
    STANDARD_HTML5_ATTRIBUTES (elem_rule),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
