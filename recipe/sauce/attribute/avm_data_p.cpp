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

hav_t havt_p [] =
{   { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_2070 }, { XHTML_2_0 }, elem_p, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_p, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_p, a_nowrap },
    HTMLPLUS_ATTRIBUTES (elem_p),
    HTML23_CLID_ATTRIBUTES (elem_p),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_p),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_page [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, a_orientation },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, a_preserveaspectratio },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, a_transin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, a_transout },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, a_viewbox },
    SVG_HTML_ATTRIBUTES (elem_page),
    SVG_PRESENTATION_ATTRIBUTES (elem_page),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_pageset [] =
{   SVG_HTML_ATTRIBUTES (elem_pageset),
    SVG_PRESENTATION_ATTRIBUTES (elem_pageset),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_param [] =
{   { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_id },
    { { HTML_3_2, REQUIRED }, { HTML_UNDEF }, elem_param, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_type },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_param, a_value },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_param, a_value },
    { { HTML_JAN05, REQUIRED }, { HTML_UNDEF }, elem_param, a_value },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_valuetype },
    HTML4_ATTRIBUTES_BASE (elem_param),
    EXTRA_HTML5_ATTRIBUTES (elem_param),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_partialdiff [] =
{   MATH3_DEFS_ATTRIBUTES (elem_partialdiff),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_path [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_path, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_path, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_path, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_path, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_path),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_path, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_path),
    SVG_HTML_ATTRIBUTES (elem_path),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_path),
    SVG_PRESENTATION_ATTRIBUTES (elem_path),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_pattern [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_pattern, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_pattern, a_href },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patterncontentunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patterntransform },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patternunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_viewbox },
    SVG_BOX_ATTRIBUTES (elem_pattern),
    SVG_CONDITIONAL_ATTRIBUTES (elem_pattern),
    SVG_HTML_ATTRIBUTES (elem_pattern),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_pattern),
    SVG_PRESENTATION_ATTRIBUTES (elem_pattern),
    SVG_XLINK_ATTRIBUTES (elem_pattern),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_person [] =
{   HTMLPLUS_ATTRIBUTES (elem_person),
    HTML23_CLID_ATTRIBUTES (elem_person),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_pi [] =
{   MATH3_DEFS_ATTRIBUTES (elem_pi),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_picture [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_picture),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_piece [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_piece),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_piecewise [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_piecewise),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_plus [] =
{   MATH3_DEFS_ATTRIBUTES (elem_plus),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_polygon [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polygon, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_polygon, a_points },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polygon, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_polygon),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_polygon, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_polygon),
    SVG_HTML_ATTRIBUTES (elem_polygon),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_polygon),
    SVG_PRESENTATION_ATTRIBUTES (elem_polygon),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_polyline [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polyline, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_polyline, a_points },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polyline, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_polyline),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_polyline, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_polyline),
    SVG_HTML_ATTRIBUTES (elem_polyline),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_polyline),
    SVG_PRESENTATION_ATTRIBUTES (elem_polyline),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_power [] =
{   MATH3_DEFS_ATTRIBUTES (elem_power),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_pre [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_pre, a_clear },
    { { HTML_2_0, HV_NOT30, HE_MOZILLA | HE_NETSCAPE }, { HTML_3_2 }, elem_pre, a_cols },
    { { HTML_1_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_pre, a_width },
    { { HTML_2_0, 0, HE_MOZILLA | HV_NOT30 }, { HTML_UNDEF }, elem_pre, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_pre),
    HTML23_CLID_ATTRIBUTES (elem_pre),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_pre),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_prefetch [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_bandwidth },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediacharacterencoding },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediacontentencodings },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediasize },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediatime },
    SVG_HTML_ATTRIBUTES (elem_prefetch),
    SVG_XLINK_ATTRIBUTES (elem_prefetch),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_preventdefault [] =
{   XHTML2_ATTRIBUTES (elem_preventdefault),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_primes [] =
{   MATH3_DEFS_ATTRIBUTES (elem_primes),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_product [] =
{   MATH3_DEFS_ATTRIBUTES (elem_product),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_progress [] =
{   { { HTML_JAN10 }, { HTML_JUN11 }, elem_progress, a_form },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, a_max },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, a_value },
    STANDARD_HTML5_ATTRIBUTES (elem_progress),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_prototype [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_prototype, a_type },
    SVG_HTML_ATTRIBUTES (elem_prototype),
    SVG_XLINK_ATTRIBUTES (elem_prototype),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_prsubset [] =
{   MATH3_DEFS_ATTRIBUTES (elem_prsubset),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
