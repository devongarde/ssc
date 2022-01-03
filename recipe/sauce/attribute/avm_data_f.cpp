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

hav_t havt_f [] =
{   MATH3_DEFS_ATTRIBUTES (elem_factorial),

    MATH3_DEFS_ATTRIBUTES (elem_factorof),

    MATH3_DEFS_ATTRIBUTES (elem_false),

    // faux_doctype and faux_xml processed elsewhere

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feblend, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feblend, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feblend, a_mode },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feblend, a_no_composite },
    SVG_FILTER_ATTRIBUTES (elem_feblend),
    SVG_HTML_ATTRIBUTES (elem_feblend),
    SVG_PRESENTATION_ATTRIBUTES (elem_feblend),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecolourmatrix, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecolourmatrix, a_type },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecolourmatrix, a_values },
    SVG_FILTER_ATTRIBUTES (elem_fecolourmatrix),
    SVG_HTML_ATTRIBUTES (elem_fecolourmatrix),
    SVG_PRESENTATION_ATTRIBUTES (elem_fecolourmatrix),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, a_in },
    SVG_FILTER_ATTRIBUTES (elem_fecomponenttransfer),
    SVG_HTML_ATTRIBUTES (elem_fecomponenttransfer),
    SVG_PRESENTATION_ATTRIBUTES (elem_fecomponenttransfer),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 | REQUIRED }, { HTML_UNDEF }, elem_fecomposite, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_k1 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_k2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_k3 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_k4 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, a_operator },
    SVG_FILTER_ATTRIBUTES (elem_fecomposite),
    SVG_HTML_ATTRIBUTES (elem_fecomposite),
    SVG_PRESENTATION_ATTRIBUTES (elem_fecomposite),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_bias },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_divisor },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_edgemode },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelmatrix },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_order },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_preservealpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targetx },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targety },
    SVG_FILTER_ATTRIBUTES (elem_feconvolvematrix),
    SVG_HTML_ATTRIBUTES (elem_feconvolvematrix),
    SVG_PRESENTATION_ATTRIBUTES (elem_feconvolvematrix),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, a_diffuseconstant },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, a_surfacescale },
    SVG_FILTER_ATTRIBUTES (elem_fediffuselighting),
    SVG_HTML_ATTRIBUTES (elem_fediffuselighting),
    SVG_PRESENTATION_ATTRIBUTES (elem_fediffuselighting),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, a_scale },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, a_xchannelselector },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, a_ychannelselector },
    SVG_FILTER_ATTRIBUTES (elem_fedisplacementmap),
    SVG_HTML_ATTRIBUTES (elem_fedisplacementmap),
    SVG_PRESENTATION_ATTRIBUTES (elem_fedisplacementmap),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedistantlight, a_azimuth },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedistantlight, a_elevation },
    SVG_HTML_ATTRIBUTES (elem_fedistantlight),

    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, a_in },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, a_stddeviation },
    SVG_DXY_ATTRIBUTES (elem_fedropshadow),
    SVG_FILTER_ATTRIBUTES (elem_fedropshadow),
    SVG_HTML_ATTRIBUTES (elem_fedropshadow),
    SVG_PRESENTATION_ATTRIBUTES (elem_fedropshadow),

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_feflood, a_in },
    SVG_FILTER_ATTRIBUTES (elem_feflood),
    SVG_HTML_ATTRIBUTES (elem_feflood),
    SVG_PRESENTATION_ATTRIBUTES (elem_feflood),

    SVG_COMP_ATTRIBUTES (elem_fefunca),
    SVG_HTML_ATTRIBUTES (elem_fefunca),

    SVG_COMP_ATTRIBUTES (elem_fefuncb),
    SVG_HTML_ATTRIBUTES (elem_fefuncb),

    SVG_COMP_ATTRIBUTES (elem_fefuncg),
    SVG_HTML_ATTRIBUTES (elem_fefuncg),

    SVG_COMP_ATTRIBUTES (elem_fefuncr),
    SVG_HTML_ATTRIBUTES (elem_fefuncr),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fegaussianblur, a_in },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fegaussianblur, a_edgemode },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fegaussianblur, a_stddeviation },
    SVG_FILTER_ATTRIBUTES (elem_fegaussianblur),
    SVG_HTML_ATTRIBUTES (elem_fegaussianblur),
    SVG_PRESENTATION_ATTRIBUTES (elem_fegaussianblur),

    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feimage, a_crossorigin },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_feimage, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feimage, a_href },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_feimage, a_preserveaspectratio },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_feimage, a_shadowinherit },
    SVG_FILTER_ATTRIBUTES_EX (elem_feimage, HTML_SVG11),
    SVG_XLINK_ATTRIBUTES (elem_feimage),
    SVG_HTML_ATTRIBUTES (elem_feimage),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_feimage),
    SVG_PRESENTATION_ATTRIBUTES (elem_feimage),

    SVG_FILTER_ATTRIBUTES (elem_femerge),
    SVG_HTML_ATTRIBUTES (elem_femerge),
    SVG_PRESENTATION_ATTRIBUTES (elem_femerge),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femergenode, a_in },
    SVG_HTML_ATTRIBUTES (elem_femergenode),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femorphology, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femorphology, a_operator },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femorphology, a_radius },
    SVG_FILTER_ATTRIBUTES (elem_femorphology),
    SVG_HTML_ATTRIBUTES (elem_femorphology),
    SVG_PRESENTATION_ATTRIBUTES (elem_femorphology),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feoffset, a_in },
    SVG_DXY_ATTRIBUTES (elem_feoffset),
    SVG_FILTER_ATTRIBUTES (elem_feoffset),
    SVG_HTML_ATTRIBUTES (elem_feoffset),
    SVG_PRESENTATION_ATTRIBUTES (elem_feoffset),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fepointlight, a_z },
    SVG_HTML_ATTRIBUTES (elem_fepointlight),
    SVG_XY_ATTRIBUTES (elem_fepointlight),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularconstant },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularexponent },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, a_surfacescale },
    SVG_FILTER_ATTRIBUTES (elem_fespecularlighting),
    SVG_HTML_ATTRIBUTES (elem_fespecularlighting),
    SVG_PRESENTATION_ATTRIBUTES (elem_fespecularlighting),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_limitingconeangle },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatx },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_pointsaty },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatz },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_specularexponent },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, a_z },
    SVG_HTML_ATTRIBUTES (elem_fespotlight),
    SVG_XY_ATTRIBUTES (elem_fespotlight),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fetile, a_in },
    SVG_FILTER_ATTRIBUTES (elem_fetile),
    SVG_HTML_ATTRIBUTES (elem_fetile),
    SVG_PRESENTATION_ATTRIBUTES (elem_fetile),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, a_basefrequency },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, a_numoctaves },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, a_seed },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, a_stitchtiles },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, a_type },
    SVG_FILTER_ATTRIBUTES (elem_feturbulence),
    SVG_HTML_ATTRIBUTES (elem_feturbulence),
    SVG_PRESENTATION_ATTRIBUTES (elem_feturbulence),

    { { HTML_JAN09 }, { HTML_UNDEF }, elem_fieldset, a_disabled },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_fieldset, a_form },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_fieldset, a_name },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fieldset),

    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_fig, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_imagemap },
    { { HTML_PLUS }, { HTML_PLUS }, elem_fig, a_ismap },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_md },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_noflow },
    { { HTML_PLUS }, { HTML_PLUS }, elem_fig, a_src },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_fig, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_units },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, a_width },
    HTMLPLUS_ATTRIBUTES (elem_fig),
    HTML3_CLID_ATTRIBUTES (elem_fig),

    STANDARD_HTML5_ATTRIBUTES (elem_figcaption),

    STANDARD_HTML5_ATTRIBUTES (elem_figure),

    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dh },
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

    SVG_HTML_ATTRIBUTES (elem_flowdiv),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowdiv),

    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, a_height },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, a_width },
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowline),

    SVG_HTML_ATTRIBUTES (elem_flowline),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowline),

    SVG_HTML_ATTRIBUTES (elem_flowpara),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowpara),

    SVG_HTML_ATTRIBUTES (elem_flowref),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowref),
    SVG_XLINK_ATTRIBUTES (elem_flowref),

    SVG_HTML_ATTRIBUTES (elem_flowregion),

    SVG_HTML_ATTRIBUTES (elem_flowregionbreak),

    SVG_HTML_ATTRIBUTES (elem_flowregionexclude),

    SVG_HTML_ATTRIBUTES (elem_flowroot),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowroot),

    SVG_HTML_ATTRIBUTES (elem_flowspan),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowspan),

    SVG_HTML_ATTRIBUTES (elem_flowtref),
    SVG_PRESENTATION_ATTRIBUTES_12 (elem_flowtref),
    SVG_XLINK_ATTRIBUTES (elem_flowtref),

    MATH3_DEFS_ATTRIBUTES (elem_floor),

    HTML23_CLID_ATTRIBUTES (elem_fn),
    MATH2_DEFS_ATTRIBUTES (elem_fn),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_colour },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_externalresourcesrequired },
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

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, a_accent_height },
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

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_format, a_string },
    SVG_HTML_ATTRIBUTES (elem_font_face_format),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_name, a_name },
    SVG_HTML_ATTRIBUTES (elem_font_face_name),

    SVG_HTML_ATTRIBUTES (elem_font_face_src),

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_name, a_externalresourcesrequired },
    SVG_XLINK_ATTRIBUTES (elem_font_face_uri),
    SVG_HTML_ATTRIBUTES (elem_font_face_uri),

    STANDARD_HTML5_ATTRIBUTES (elem_footer),

    HTMLPLUS_ATTRIBUTES (elem_footnote),

    MATH3_DEFS_ATTRIBUTES (elem_forall),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_foreignobject, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_foreignobject, a_transform },
    SVG_BOX_ATTRIBUTES (elem_foreignobject),
    SVG_CONDITIONAL_ATTRIBUTES (elem_foreignobject),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_foreignobject, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_foreignobject),
    SVG_HTML_ATTRIBUTES (elem_foreignobject),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_foreignobject),
    SVG_PRESENTATION_ATTRIBUTES (elem_foreignobject),
    SVG_XLINK_ATTRIBUTES_EX (elem_foreignobject, HE_SVG_12),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_form, a_accept_charset },
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

    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_frameborder },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_longdesc },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_marginheight },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_marginwidth },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_name },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_noresize },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_scrolling },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frame, a_src },
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_frame, MAJOR_4_0, MINOR_4_0),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_cols },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_onload },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_onunload },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, a_rows },
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_frameset, MAJOR_4_0, MINOR_4_0),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
