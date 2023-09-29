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

hav_t havt_filter [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dh },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dw },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dx },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dy },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_filter, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_filter, a_filterres },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_filter, a_filterunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_filter, a_primitiveunits },
    SVG_BOX_ATTRIBUTES (elem_filter),
    SVG_HTML_ATTRIBUTES (elem_filter),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_filter),
    SVG_PRESENTATION_ATTRIBUTES (elem_filter),
    SVG_XLINK_ATTRIBUTES (elem_filter),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowdiv [] =
{   SVG_HTML_ATTRIBUTES (elem_flowdiv),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowdiv),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowimage [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, a_height },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, a_width },
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowimage),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowline [] =
{   SVG_HTML_ATTRIBUTES (elem_flowline),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowline),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowpara [] =
{   SVG_HTML_ATTRIBUTES (elem_flowpara),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowpara),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowref [] =
{   SVG_HTML_ATTRIBUTES (elem_flowref),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowref),
    SVG_XLINK_ATTRIBUTES (elem_flowref),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowregion [] =
{   SVG_HTML_ATTRIBUTES (elem_flowregion),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowregionbreak [] =
{   SVG_HTML_ATTRIBUTES (elem_flowregionbreak),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowregionexclude [] =
{   SVG_HTML_ATTRIBUTES (elem_flowregionexclude),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowroot [] =
{   SVG_HTML_ATTRIBUTES (elem_flowroot),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowroot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowspan [] =
{   SVG_HTML_ATTRIBUTES (elem_flowspan),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowspan),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_flowtref [] =
{   SVG_HTML_ATTRIBUTES (elem_flowtref),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowtref),
    SVG_XLINK_ATTRIBUTES (elem_flowtref),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_floor [] =
{   MATH3_DEFS_ATTRIBUTES (elem_floor),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_fn [] =
{   HTML23_CLID_ATTRIBUTES (elem_fn),
    MATH2_DEFS_ATTRIBUTES (elem_fn),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font [] =
{   { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_colour },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_externalresourcesrequired },
    { { HTML_3_2, 0, HE_IE }, { HTML_3_2 }, elem_font, a_face },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_face },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_horiz_adv_x },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_horiz_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font, a_horiz_origin_y },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_size },
    { { HTML_JUL07, HV_NOTPROD }, { HTML_JUN08 }, elem_font, a_style },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font, a_vert_adv_y },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font, a_vert_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font, a_vert_origin_y },
    SVG_HTML_ATTRIBUTES (elem_font),
    SVG_PRESENTATION_ATTRIBUTES (elem_font),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font_face [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_accent_height },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_ascent },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_bbox },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_cap_height },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_descent },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_family },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_size },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_stretch },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_style, },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_variant },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_font_weight },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_hanging },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_ideographic },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_mathematical },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_overline_position },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_overline_thickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_panose_1 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_slope },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_stemh },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_stemv },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_strikethrough_position },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_strikethrough_thickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_underline_position },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_underline_thickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_unicode_range },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_units_per_em },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face, a_v_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face, a_v_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face, a_v_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face, a_v_mathematical },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_widths },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_x_height },
    SVG_HTML_ATTRIBUTES (elem_font_face),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font_face_format [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_format, a_string },
    SVG_HTML_ATTRIBUTES (elem_font_face_format),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font_face_name [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_name, a_name },
    SVG_HTML_ATTRIBUTES (elem_font_face_name),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font_face_src [] =
{   SVG_HTML_ATTRIBUTES (elem_font_face_src),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_font_face_uri [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_uri, a_externalresourcesrequired },
    SVG_XLINK_ATTRIBUTES (elem_font_face_uri),
    SVG_HTML_ATTRIBUTES (elem_font_face_uri),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_footer [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_footer),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_footnote [] =
{   HTMLPLUS_ATTRIBUTES (elem_footnote),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_forall [] =
{   MATH3_DEFS_ATTRIBUTES (elem_forall),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_foreignobject [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_foreignobject, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_foreignobject, a_transform },
    SVG_BOX_ATTRIBUTES (elem_foreignobject),
    SVG_CONDITIONAL_ATTRIBUTES (elem_foreignobject),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_foreignobject, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_foreignobject),
    SVG_HTML_ATTRIBUTES (elem_foreignobject),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_foreignobject),
    SVG_PRESENTATION_ATTRIBUTES (elem_foreignobject),
    SVG_XLINK_ATTRIBUTES_EX (elem_foreignobject, HE_SVG_12),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_form [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_form, a_accept_charset },
    { { HTML_PLUS }, { HTML_2_0 }, elem_form, a_action },
    { { HTML_3_0, REQUIRED }, { HTML_DEC08 }, elem_form, a_action },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_form, a_action },
    { { HTML_JAN09, 0, HE_SAFARI }, { HTML_UNDEF }, elem_form, a_autocapitalise },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_form, a_autocomplete },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_form, a_enctype },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_form, a_method },
    { { HTML_4_01 }, { HTML_UNDEF }, elem_form, a_name },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_form, a_novalidate },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_form, a_onreset },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_form, a_onsubmit },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_form, a_rel },
    { { HTML_3_0 }, { HTML_3_0 }, elem_form, a_script },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_form, a_target },
    HTMLPLUS_ATTRIBUTES (elem_form),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_form),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_frame [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_frameborder },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_longdesc },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_marginheight },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_marginwidth },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_name },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_noresize },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_scrolling },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_src },
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_frame, MAJOR_4_0, MINOR_4_0),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_frameset [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_cols },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_onload },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_onunload },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_rows },
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_frameset, MAJOR_4_0, MINOR_4_0),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
