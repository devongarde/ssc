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

hav_t havt_f1 [] =
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

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
