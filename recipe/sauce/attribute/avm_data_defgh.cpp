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

hav_t havt_defgh [] =
{   { { HTML_JAN12 }, { HTML_UNDEF }, elem_data, a_value },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_data),

    { { HTML_JUL05 }, { HTML_DEC09 }, elem_datagrid, a_disabled },
    { { HTML_JUL05 }, { HTML_DEC09 }, elem_datagrid, a_multiple },
    STANDARD_HTML5_ATTRIBUTES (elem_datagrid),

    STANDARD_HTML5_ATTRIBUTES (elem_datalist),

    STANDARD_HTML5_ATTRIBUTES (elem_datatemplate),

    { { HTML_3_0 }, { HTML_3_0 }, elem_dd, a_clear },
    HTML23_CLID_ATTRIBUTES (elem_dd),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dd),

    HTML3_CLID_ATTRIBUTES (elem_ddot),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, a_nargs },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, a_occurrence },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, a_scope },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_declare),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_definition_src, a_xlinkhref },
    SVG11_XLINK_ATTRIBUTES (elem_definition_src),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_definition_src),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_defs, a_externalresourcesrequired },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_defs, a_transform },
    SVG12_CONDGRAPH_ATTRIBUTES (elem_defs),
    SVGx_CONDPROC_ATTRIBUTES (elem_defs),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_defs),
    SVG11_GREV_ATTRIBUTES (elem_defs),
    SVGx_PRES_ATTRIBUTES (elem_defs),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_defs),

    MATH3_STANDARD_ATTRIBUTES (elem_degree),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_del, a_cite },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_del, a_datetime },
    HTML3_CLID_ATTRIBUTES (elem_del),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_del),

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_desc, a_systemrequired },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_desc),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_desc),

    { { HTML_JAN07, HV_NOT50 }, { HTML_UNDEF }, elem_details, a_open },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_details),

    MATH3_DEFS_ATTRIBUTES (elem_determinant),

    { { HTML_JAN10 }, { HTML_JUN11 }, elem_device, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_device),

    HTMLPLUS_ATTRIBUTES (elem_dfn),
    HTML3_CLID_ATTRIBUTES (elem_dfn),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dfn),

    XHTML2_ATTRIBUTES (elem_di),

    { { HTML_JUL12 }, { HTML_UNDEF }, elem_dialogue, a_open },
    STANDARD_HTML5_ATTRIBUTES (elem_dialogue),

    MATH3_DEFS_ATTRIBUTES (elem_diff),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_dir, a_align },
    { { HTML_3_2 }, { HTML_3_0 }, elem_dir, a_clear },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_dir, a_compact },
    HTMLPLUS_ATTRIBUTES (elem_dir),
    HTML2_CLID_ATTRIBUTES (elem_dir),
    COMMON_HTML4_ATTRIBUTES (elem_dir),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_discard),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dispatchevent, a_bubbles },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dispatchevent, a_cancelable },
    XHTML2_ATTRIBUTES (elem_dispatchevent),

    { { HTML_3_0 }, { XHTML_2_0 }, elem_div, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, a_clear },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_datasrc },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, a_nowrap },
    HTML3_CLID_ATTRIBUTES (elem_div),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_div),

    MATH3_DEFS_ATTRIBUTES (elem_divergence),

    MATH3_DEFS_ATTRIBUTES (elem_divide),

    { { HTML_3_0 }, { HTML_3_0 }, elem_dl, a_clear },
    { { HTML_1_0 }, { HTML_3_2 }, elem_dl, a_compact },
    HTMLPLUS_ATTRIBUTES (elem_dl),
    HTML23_CLID_ATTRIBUTES (elem_dl),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dl),

    MATH3_DEFS_ATTRIBUTES (elem_domain),

    MATH3_DEFS_ATTRIBUTES (elem_domainofapplication),

    HTML3_CLID_ATTRIBUTES (elem_dot),

    { { HTML_3_0 }, { HTML_3_0 }, elem_dt, a_clear },
    HTML23_CLID_ATTRIBUTES (elem_dt),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dt),

    STANDARD_HTML5_ATTRIBUTES (elem_element),

    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_ellipse, a_cx },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_ellipse, a_cy },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_ellipse, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_ellipse, a_rx },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_ellipse, a_ry },
    SVG10_G_ATTRIBUTES(elem_ellipse),
    SVG11_GREV_ATTRIBUTES (elem_ellipse),
    SVG12_CONDGRAPH_ATTRIBUTES (elem_ellipse),
    SVGx_CONDPROC_ATTRIBUTES (elem_ellipse),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_ellipse),
    SVGx_PRES_ATTRIBUTES (elem_ellipse),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ellipse),

    HTMLPLUS_ATTRIBUTES (elem_em),
    HTML3_CLID_ATTRIBUTES (elem_em),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_em),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_height },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_src },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_type },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_width },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_align },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_hspace },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_name },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_vspace },
    STANDARD_HTML5_ATTRIBUTES (elem_embed),

    MATH3_DEFS_ATTRIBUTES (elem_emptyset),

    MATH3_DEFS_ATTRIBUTES (elem_eq),

    MATH3_DEFS_ATTRIBUTES (elem_equivalent),

    MATH3_DEFS_ATTRIBUTES (elem_eulergamma),

    { { HTML_JAN05 }, { HTML_JUN08 }, elem_event_source, a_onevent },
    { { HTML_JAN05 }, { HTML_JUN08 }, elem_event_source, a_src },
    STANDARD_HTML5_ATTRIBUTES (elem_event_source),

    { { HTML_JUL08 }, { HTML_JUN09 }, elem_eventsource, a_src },
    STANDARD_HTML5_ATTRIBUTES (elem_eventsource),

    MATH3_DEFS_ATTRIBUTES (elem_exists),

    MATH3_DEFS_ATTRIBUTES (elem_exp),

    MATH3_DEFS_ATTRIBUTES (elem_exponentiale),

    MATH3_DEFS_ATTRIBUTES (elem_factorial),

    MATH3_DEFS_ATTRIBUTES (elem_factorof),

    MATH3_DEFS_ATTRIBUTES (elem_false),

    // faux_doctype and faux_xml processed before getting here,

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feblend, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feblend, a_mode },
    SVG10_FILTER_ATTRIBUTES (elem_feblend),
    SVG11_FILTER_ATTRIBUTES (elem_feblend),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feblend),
    SVGx_PRES_ATTRIBUTES (elem_feblend),
    STANDARD_HTML5_ATTRIBUTES (elem_feblend),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 | REQUIRED }, { HTML_UNDEF }, elem_fecolourmatrix, a_type },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecolourmatrix, a_values },
    SVG10_FILTER_ATTRIBUTES (elem_fecolourmatrix),
    SVG11_FILTER_ATTRIBUTES (elem_fecolourmatrix),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fecolourmatrix),
    SVGx_PRES_ATTRIBUTES (elem_fecolourmatrix),
    STANDARD_HTML5_ATTRIBUTES (elem_fecolourmatrix),

    SVG10_FILTER_ATTRIBUTES (elem_fecomponenttransfer),
    SVG11_FILTER_ATTRIBUTES (elem_fecomponenttransfer),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fecomponenttransfer),
    SVGx_PRES_ATTRIBUTES (elem_fecomponenttransfer),
    STANDARD_HTML5_ATTRIBUTES (elem_fecomponenttransfer),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 | REQUIRED }, { HTML_UNDEF }, elem_fecomposite, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecomposite, a_k1 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecomposite, a_k2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecomposite, a_k3 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecomposite, a_k4 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fecomposite, a_operator },
    SVG10_FILTER_ATTRIBUTES (elem_fecomposite),
    SVG11_FILTER_ATTRIBUTES (elem_fecomposite),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fecomposite),
    SVGx_PRES_ATTRIBUTES (elem_fecomposite),
    STANDARD_HTML5_ATTRIBUTES (elem_fecomposite),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_bias },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_divisor },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_edgemode },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_in },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelmatrix },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_order },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_preservealpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targetx },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targety },
    SVG11_FILTER_ATTRIBUTES (elem_feconvolvematrix),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feconvolvematrix),
    SVGx_PRES_ATTRIBUTES (elem_feconvolvematrix),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_feconvolvematrix),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fediffuselighting, a_diffuseconstant },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fediffuselighting, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fediffuselighting, a_lighting_colour },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fediffuselighting, a_surfacescale },
    SVG10_FILTER_ATTRIBUTES (elem_fediffuselighting),
    STANDARD_HTML5_ATTRIBUTES (elem_fediffuselighting),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedisplacementmap, a_in2 },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedisplacementmap, a_scale },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedisplacementmap, a_xchannelselector },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedisplacementmap, a_ychannelselector },
    SVG10_FILTER_ATTRIBUTES (elem_fedisplacementmap),
    SVG11_FILTER_ATTRIBUTES (elem_fedisplacementmap),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fedisplacementmap),
    SVGx_PRES_ATTRIBUTES (elem_fedisplacementmap),
    STANDARD_HTML5_ATTRIBUTES (elem_fedisplacementmap),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedistantlight, a_azimuth },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fedistantlight, a_elevation },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fedistantlight),
    STANDARD_HTML5_ATTRIBUTES (elem_fedistantlight),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fedropshadow),

    SVG11_FILTER_ATTRIBUTES (elem_feflood),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feflood),
    SVGx_PRES_ATTRIBUTES (elem_feflood),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_feflood),

    SVG10_COMP_ATTRIBUTES (elem_fefunca),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fefunca),
    STANDARD_HTML5_ATTRIBUTES (elem_fefunca),

    SVG10_COMP_ATTRIBUTES (elem_fefuncb),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fefuncb),
    STANDARD_HTML5_ATTRIBUTES (elem_fefuncb),

    SVG10_COMP_ATTRIBUTES (elem_fefuncg),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fefuncg),
    STANDARD_HTML5_ATTRIBUTES (elem_fefuncg),

    SVG10_COMP_ATTRIBUTES (elem_fefuncr),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fefuncr),
    STANDARD_HTML5_ATTRIBUTES (elem_fefuncr),

    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_fegaussianblur, a_edgemode },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fegaussianblur, a_stddeviation },
    SVG10_FILTER_ATTRIBUTES (elem_fegaussianblur),
    SVG11_FILTER_ATTRIBUTES (elem_fegaussianblur),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fegaussianblur),
    SVGx_PRES_ATTRIBUTES (elem_fegaussianblur),
    STANDARD_HTML5_ATTRIBUTES (elem_fegaussianblur),

    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_feimage, a_crossorigin },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_feimage, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_feimage, a_nodeid },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_feimage, a_preserveaspectratio },
    SVG10_REPL_ATTRIBUTES (elem_feimage),
    SVG11_FILTER_ATTRIBUTES (elem_feimage),
    SVG11_XLINK_ATTRIBUTES (elem_feimage),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feimage),
    SVGx_PRES_ATTRIBUTES (elem_feimage),
    STANDARD_HTML5_ATTRIBUTES (elem_feimage),

    SVG10_FILTER_ATTRIBUTES (elem_femerge),
    SVG11_FILTER_ATTRIBUTES (elem_femerge),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_femerge),
    SVGx_PRES_ATTRIBUTES (elem_femerge),
    STANDARD_HTML5_ATTRIBUTES (elem_femerge),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_femergenode, a_in },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_femergenode),
    STANDARD_HTML5_ATTRIBUTES (elem_femergenode),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_femorphology, a_operator },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_femorphology, a_radius },
    SVG10_FILTER_ATTRIBUTES (elem_femorphology),
    SVG11_FILTER_ATTRIBUTES (elem_femorphology),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_femorphology),
    SVGx_PRES_ATTRIBUTES (elem_femorphology),
    STANDARD_HTML5_ATTRIBUTES (elem_femorphology),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feoffset, a_in },
    SVG10_DXY_ATTRIBUTES (elem_feoffset),
    SVG10_FILTER_ATTRIBUTES (elem_feoffset),
    SVG11_FILTER_ATTRIBUTES (elem_feoffset),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feoffset),
    SVGx_PRES_ATTRIBUTES (elem_feoffset),
    STANDARD_HTML5_ATTRIBUTES (elem_feoffset),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fepointlight, a_x },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fepointlight, a_y },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fepointlight, a_z },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fepointlight),
    STANDARD_HTML5_ATTRIBUTES (elem_fepointlight),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespecularlighting, a_kernelunitlength },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespecularlighting, a_lighting_colour },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularconstant },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularexponent },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespecularlighting, a_surfacescale },
    SVG10_FILTER_ATTRIBUTES (elem_fespecularlighting),
    SVG11_FILTER_ATTRIBUTES (elem_fespecularlighting),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fespecularlighting),
    SVGx_PRES_ATTRIBUTES (elem_fespecularlighting),
    STANDARD_HTML5_ATTRIBUTES (elem_fespecularlighting),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_limitingconeangle },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatx },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_pointsaty },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatz },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_specularexponent },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_x },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_y },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_fespotlight, a_z },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fespotlight),
    STANDARD_HTML5_ATTRIBUTES (elem_fespotlight),

    SVG10_FILTER_ATTRIBUTES (elem_fetile),
    SVG11_FILTER_ATTRIBUTES (elem_fetile),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fetile),
    SVGx_PRES_ATTRIBUTES (elem_fetile),
    STANDARD_HTML5_ATTRIBUTES (elem_fetile),

    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feturbulence, a_basefrequency },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feturbulence, a_numoctaves },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feturbulence, a_seed },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_feturbulence, a_stitchtiles },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_feturbulence, a_type },
    SVG10_FILTER_ATTRIBUTES (elem_feturbulence),
    SVG11_FILTER_ATTRIBUTES (elem_feturbulence),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feturbulence),
    SVGx_PRES_ATTRIBUTES (elem_feturbulence),
    STANDARD_HTML5_ATTRIBUTES (elem_feturbulence),

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

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_animate },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dh },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dw },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dx },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_filter, a_dy },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_filter, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_fecolourmatrix },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_fecomposite },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_fegaussianblur },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_femorphology },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_filter, a_fetile },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_filter, a_filterres },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_filter, a_filterunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_filter, a_primitiveunits },
    SVG10_BOX_ATTRIBUTES (elem_filter),
    SVG11_XLINK_ATTRIBUTES (elem_filter),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_filter),
    SVGx_PRES_ATTRIBUTES (elem_filter),
    STANDARD_HTML5_ATTRIBUTES (elem_filter),

    MATH3_DEFS_ATTRIBUTES (elem_floor),

    HTML23_CLID_ATTRIBUTES (elem_fn),
    MATH2_DEFS_ATTRIBUTES (elem_fn),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_colour },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_externalresourcesrequired },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_face },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_horizadvx },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, a_horizoriginx },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font, a_horizoriginy },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_size },
    { { HTML_JUL07, HV_NOTPROD }, { HTML_JUN08 }, elem_font, a_style },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_font, a_vert_adv_y },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_font, a_vert_origin_x },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_font, a_vert_origin_y },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_font),
    SVGx_PRES_ATTRIBUTES (elem_font),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_font),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_accentheight },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_ascent },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_bbox },
    { { HTML_SVG11, 0, HE_SVG_11_12 }, { HTML_UNDEF }, elem_fontface, a_capheight },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_descent },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_family },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_size },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_stretch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_style, },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_variant },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_font_weight },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_hanging },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_ideographic },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_mathematical },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_overline_position },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_overline_thickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_panose1 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_fontface, a_slope },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_stemh },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_stemv },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_strikethroughposition },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_strikethroughthickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_underline_position },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_underline_thickness },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_unicode_range },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_units_per_em },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_v_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_v_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_v_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_fontface, a_v_mathematical },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_widths },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_fontface, a_x_height },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontface),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontface),

    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_fontfaceformat, a_string },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontfaceformat),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontfaceformat),

    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_fontfacename, a_name },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontfacename),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontfacename),

    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontfacesrc),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontfacesrc),

    SVG11_XLINK_ATTRIBUTES (elem_fontfaceuri),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontfaceuri),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontfaceuri),

    STANDARD_HTML5_ATTRIBUTES (elem_footer),

    HTMLPLUS_ATTRIBUTES (elem_footnote),

    MATH3_DEFS_ATTRIBUTES (elem_forall),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_foreignobject, a_externalresourcesrequired },
    SVG10_BOX_ATTRIBUTES (elem_foreignobject),
    SVG10_G_ATTRIBUTES (elem_foreignobject),
    SVGx_CONDPROC_ATTRIBUTES (elem_foreignobject),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_foreignobject),
    SVGx_PRES_ATTRIBUTES (elem_foreignobject),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_foreignobject),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_form, a_acceptcharset },
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

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_g, a_allow_zoom_pan },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_g, a_externalresourcesrequired },
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, elem_g, a_transform },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_g, a_xmlns },
    SVG10_BOX_ATTRIBUTES (elem_g),
    SVG10_FIT_ATTRIBUTES (elem_g),
    SVG10_G_ATTRIBUTES (elem_g),
    SVG11_GREV_ATTRIBUTES (elem_g),
    SVG12_CONDGRAPH_ATTRIBUTES (elem_g),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_g),
    SVGx_CONDPROC_ATTRIBUTES (elem_g),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_g),
    SVGx_PRES_ATTRIBUTES (elem_g),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_g),

    STANDARD_HTML5_ATTRIBUTES (elem_gauge),

    MATH3_DEFS_ATTRIBUTES (elem_gcd),

    MATH3_DEFS_ATTRIBUTES (elem_geq),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_arabicform },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_glyphname },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_horizadvx },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_lang },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_orientation },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_unicode },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_adv_y },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_origin_y },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_glyph),
    SVGx_PRES_ATTRIBUTES (elem_glyph),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_glyph),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyphref, a_format },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyphref, a_glyphref },
    SVG10_XY_ATTRIBUTES(elem_glyphref),
    SVG10_DXY_ATTRIBUTES(elem_glyphref),
    SVG11_XLINK_ATTRIBUTES(elem_glyphref),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_glyphref),
    SVGx_PRES_ATTRIBUTES (elem_glyphref),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_glyphref),

    MATH3_DEFS_ATTRIBUTES (elem_grad),

    MATH3_DEFS_ATTRIBUTES (elem_gt),

    XHTML2_ATTRIBUTES (elem_h),
    STANDARD_H_ATTRIBUTES (elem_h1),
    STANDARD_H_ATTRIBUTES (elem_h2),
    STANDARD_H_ATTRIBUTES (elem_h3),
    STANDARD_H_ATTRIBUTES (elem_h4),
    STANDARD_H_ATTRIBUTES (elem_h5),
    STANDARD_H_ATTRIBUTES (elem_h6),

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, a_evevent },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_handler),

    HTML3_CLID_ATTRIBUTES (elem_hat),

    { { HTML_4_0 }, { HTML_DEC06 }, elem_head, a_profile },
    HTML2_CLID_ATTRIBUTES (elem_head),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_head, MAJOR_4_0, MINOR_4_0),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_head, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_head),

    STANDARD_HTML5_ATTRIBUTES (elem_header),

    STANDARD_HTML5_ATTRIBUTES (elem_hgroup),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_g1 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_g2 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_k },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_u1 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_u1 },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_hkern),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_hkern),

    { { HTML_2_0, HV_DEPRECATED4 | HV_RFC_2070 | HV_NOT30 }, { XHTML_2_0 }, elem_hr, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_clear },
    { { HTML_2_0, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_hr, a_colour },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_md },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_noshade },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_size },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_width },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_src },
    HTMLPLUS_ATTRIBUTES (elem_hr),
    HTML3_CLID_ATTRIBUTES (elem_hr),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_hr),

    { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_html, a_dir },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_html, a_lang },
    { { HTML_JAN08, HV_DEPRECATED51 }, { HTML_DEC16 }, elem_html, a_manifest },
    { { HTML_JAN17, HV_DEPRECATED52x }, { HTML_DEC20 }, elem_html, a_manifest },
    { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_role },
    { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_urn },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_html, a_version },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_html, a_xsischemaloc },
    HTML2_CLID_ATTRIBUTES (elem_html),
    XHTML1_STANDARD_ATTRIBUTES (elem_html, MAJOR_X1_0, MINOR_X1_0),
    EXTRA_HTML5_ATTRIBUTES (elem_html),

    { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, a_forms },
    { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, a_version },

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
