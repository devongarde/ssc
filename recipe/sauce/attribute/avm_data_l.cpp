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

hav_t havt_l [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_l, a_align },
    HTMLPLUS_ATTRIBUTES (elem_l),
    XHTML2_ATTRIBUTES (elem_l),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_label, a_for },
    { { HTML_JAN09, HV_NOT51 }, { HTML_DEC16 }, elem_label, a_form },
    HTML3_CLID_ATTRIBUTES (elem_label),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_label),

    MATH3_STANDARD_ATTRIBUTES (elem_lambda),

    MATH3_DEFS_ATTRIBUTES (elem_laplacian),

    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_above },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_background },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_below },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_bgcolour },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_class },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_clip },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_height },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_id },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_left },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_name },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_pagex },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_pagey },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_src },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_style },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_top },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_visibility },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_layer, a_zindex },

    MATH3_DEFS_ATTRIBUTES (elem_lcm),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_legend, a_align },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_legend),

    MATH3_DEFS_ATTRIBUTES (elem_leq),

    HTML3_CLID_ATTRIBUTES (elem_lh),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_li, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_li, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_li, a_dingbat },
    { { HTML_3_0 }, { HTML_3_0 }, elem_li, a_md },
    { { HTML_3_0 }, { HTML_3_0 }, elem_li, a_skip },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_li, a_src },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_li, a_type },
    { { HTML_3_2, HV_DEPRECATED4 }, { HTML_UNDEF }, elem_li, a_value },
    HTMLPLUS_ATTRIBUTES (elem_li),
    HTML23_CLID_ATTRIBUTES (elem_li),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_li),

    MATH3_DEFS_ATTRIBUTES (elem_limit),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_line, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_line, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, a_will_change },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_line, a_x1 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_line, a_x2 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_line, a_y1 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_line, a_y2 },
    SVG_BOX_ATTRIBUTES (elem_line),
    SVG_CONDITIONAL_ATTRIBUTES (elem_line),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_line, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_line),
    SVG_HTML_ATTRIBUTES (elem_line),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_line),
    SVG_PRESENTATION_ATTRIBUTES (elem_line),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_lineargradient, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_lineargradient, a_href },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_lineargradient, a_spreadmethod },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, a_x1 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, a_x2 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, a_y1 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, a_y2 },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_lineargradient, HE_SVG_2),
    SVG_GRAD_ATTRIBUTES (elem_lineargradient),
    SVG_HTML_ATTRIBUTES (elem_lineargradient),
    SVG_PRESENTATION_ATTRIBUTES (elem_lineargradient),
    SVG_XLINK_ATTRIBUTES (elem_lineargradient),

    { { HTML_JUL16 }, { HTML_UNDEF }, elem_link, a_as },
    { { HTML_2_0, HV_RFC_2070 | HV_NOT3 }, { XHTML_2_0 }, elem_link, a_charset },
    { { HTML_JUL17 }, { HTML_UNDEF }, elem_link, a_colour },
    { { HTML_JAN13 }, { HTML_UNDEF }, elem_link, a_crossorigin },
    { { HTML_JAN05, 0, HE_MOZILLA }, { HTML_5_3 }, elem_link, a_disabled },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_link, a_disabled },
    { { HTML_PLUS, REQUIRED }, { XHTML_2_0 }, elem_link, a_href },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_link, a_href },
    { { HTML_JAN07, REQUIRED }, { HTML_JUN19 }, elem_link, a_href },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_link, a_href },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_link, a_hreflang },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_link, a_imagesizes },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_link, a_imagesrcset },
    { { HTML_JUL20, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_link, a_importance },
    { { HTML_JAN17 }, { HTML_UNDEF }, elem_link, a_integrity },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_link, a_media },
    { { HTML_PLUS }, { HTML_3_0 }, elem_link, a_methods },
    { { HTML_2_0 }, { HTML_2_0 }, elem_link, a_name },
    { { HTML_JAN17 }, { HTML_5_2 }, elem_link, a_numberonce },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_link, a_ping },
    { { HTML_4_0, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_link, a_prefetch },
    { { HTML_PLUS }, { HTML_DEC06 }, elem_link, a_rel },
    { { HTML_JAN07, REQUIRED }, { HTML_DEC09 }, elem_link, a_rel },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_link, a_rel },
    { { HTML_JUL16 }, { HTML_UNDEF }, elem_link, a_referrerpolicy },
    { { HTML_PLUS, HV_NOT50 }, { HTML_5_3 }, elem_link, a_rev },
    { { HTML_JUL17 }, { HTML_DEC17 }, elem_link, a_scope },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_link, a_sizes },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_link, a_target },
    { { HTML_2_0 }, { HTML_3_2 }, elem_link, a_title },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_link, a_type },
    { { HTML_JUL17 }, { HTML_DEC17 }, elem_link, a_updateviacache },
    { { HTML_2_0 }, { HTML_2_0 }, elem_link, a_urn },
    { { HTML_JUL17 }, { HTML_DEC17 }, elem_link, a_workertype },
    HTML23_CLID_ATTRIBUTES (elem_link),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_link),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_list, a_order },
    MATH3_STANDARD_ATTRIBUTES (elem_list),

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_defaultaction },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_event },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_observer },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_phase },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_listener, a_propagate },
    XHTML2_ATTRIBUTES (elem_listener),
    SVG_HTML_ATTRIBUTES (elem_listener),

    HTML23_CLID_ATTRIBUTES (elem_listing),

    HTMLPLUS_ATTRIBUTES (elem_lit),

    MATH3_DEFS_ATTRIBUTES (elem_ln),

    SVG_HTML_ATTRIBUTES (elem_loc),
    SVG_XLINK_ATTRIBUTES (elem_loc),

    MATH3_DEFS_ATTRIBUTES (elem_log),

    MATH3_STANDARD_ATTRIBUTES (elem_logbase),

    MATH3_STANDARD_ATTRIBUTES (elem_lowlimit),

    MATH3_DEFS_ATTRIBUTES (elem_lt),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
