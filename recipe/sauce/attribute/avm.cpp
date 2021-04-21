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
#include "attribute/avm.h"
#include "main/context.h"
#include "element/elem.h"
#include "type/type.h"

struct hav_t
{   html_version first_, last_;
    e_element tag_;
    e_attribute a_; };

#define HTMLPLUS_ATTRIBUTES(ELEM) \
    { { HTML_PLUS }, { HTML_PLUS }, ELEM, a_id }, \
    { { HTML_PLUS }, { HTML_PLUS }, ELEM, a_index }, \
    { { HTML_PLUS }, { HTML_PLUS }, ELEM, a_lang }

#define HTML_CID_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM, MAJOR_TO, MINOR_TO) \
    { { MAJOR_FROM, MINOR_FROM, HV_RFC_1942 | HV_RFC_2070 }, { MAJOR_TO, MINOR_TO }, ELEM, a_class }, \
    { { MAJOR_FROM, MINOR_FROM, HV_RFC_1942 | HV_RFC_2070 }, { MAJOR_TO, MINOR_TO }, ELEM, a_id }

#define HTML_LANG_ATTRIBUTES(ELEM, MAJOR_TO, MINOR_TO) \
    { { HTML_2_0, HV_RFC_1942 | HV_RFC_2070 }, { HTML_2_0 }, ELEM, a_dir }, \
    { { HTML_2_0, HV_RFC_1942 | HV_RFC_2070 }, { MAJOR_TO, MINOR_TO }, ELEM, a_lang }

#define HTML2_CLID_ATTRIBUTES(ELEM) \
    HTML_LANG_ATTRIBUTES (ELEM, MAJOR_2_0, MINOR_2_0), \
    HTML_CID_ATTRIBUTES (ELEM, MAJOR_2_0, MINOR_2_0, MAJOR_2_0, MINOR_2_0)

#define HTML3_CLID_ATTRIBUTES(ELEM) \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_lang }, \
    HTML_CID_ATTRIBUTES (ELEM, MAJOR_3_0, MINOR_3_0, MAJOR_3_0, MINOR_3_0)

#define HTML23_CLID_ATTRIBUTES(ELEM) \
    HTML_LANG_ATTRIBUTES (ELEM, MAJOR_3_0, MINOR_3_0), \
    HTML_CID_ATTRIBUTES (ELEM, MAJOR_2_0, MINOR_2_0, MAJOR_3_0, MINOR_3_0)

#define STANDARD_HTML_23_H_ATTRIBUTES(ELEM) \
    { { HTML_2_0, HV_RFC_2070 }, { HTML_3_2 }, ELEM, a_align }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_clear }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_dingbat }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_md }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_nowrap }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_seqnum }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_skip }, \
    { { HTML_3_0 }, { HTML_3_0 }, ELEM, a_src },  \
    HTML23_CLID_ATTRIBUTES (ELEM)

#define HTML4_STANDARD_SCRIPT_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onclick },\
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_ondblclick }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onkeydown }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onkeypress }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onkeyup }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onmousedown }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onmousemove }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onmouseout }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onmouseover }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_onmouseup }

#define HTML4_STANDARD_LANG_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    { { MAJOR_FROM, MINOR_FROM, 0 }, { HTML_UNDEF }, ELEM, a_dir }, \
    { { MAJOR_FROM, MINOR_FROM, 0 }, { HTML_UNDEF }, ELEM, a_lang }

#define HTML4_STANDARD_CI_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_class }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_id }

#define HTML4_ARIA_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM, FLAG) \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaactivedescendant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaatomic }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaautocomplete }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariabusy }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariachecked }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariacontrols }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariadescribedby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariadisabled }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariadropeffect }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaexpanded }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaflowto }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariagrabbed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariahaspopup }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariahidden }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariainvalid }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_arialabel }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_arialabelledby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_arialevel }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_arialive }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariamultiline }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariamultiselectable }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaorientation }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaowns }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaposinset }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariapressed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariareadonly }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariarelevant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariarequired }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariaselected }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariasetsize }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariasort }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariavaluemax }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariavaluemin }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariavaluenow }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG }, { HTML_UNDEF }, ELEM, a_ariavaluetext }

#define RDFA_STANDARD_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_about }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_content }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_datatype }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_inlist }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_prefix }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_property }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_rel }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_resource }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_rev }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_src }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_typeof }, \
    { { HTML_4_0, 0, HE_RDF_1_0 }, { HTML_UNDEF }, ELEM, a_vocab }

#define SVG10_XY_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_x }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_y }

#define SVG10_DXY_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_dx }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_dy }

#define SVG10_BOX_ATTRIBUTES(ELEM) \
    SVG10_XY_ATTRIBUTES (ELEM), \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_fitbbox }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_height }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_width }

#define SVG10_COMP_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_amplitude }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_exponent }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_intercept }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_offset }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | REQUIRED }, { HTML_UNDEF }, ELEM, a_type }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_slope }, \
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_tablevalues }

#define SVG10_FILTER_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_in }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_nodeid }

#define SVG10_FIT_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_fitboxtoviewport }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_preserveaspectratio }

#define SVG10_G_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG }, { XHTML_2_0 }, ELEM, a_onload }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { XHTML_2_0 }, ELEM, a_onselect }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_transform }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_systemrequired }

#define SVG10_GRAD_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_gradienttransform }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_gradient_units }, \
    { { HTML_4_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_gradientunits }

#define SVG10_REF_XY_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_refx }, \
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_refy }

#define SVG10_REPL_ATTRIBUTES(ELEM) \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_actuate }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_href }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_show }, \
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, ELEM, a_xmllink }

#define SVG11_ANADD_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_additive }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_accumulate }

#define SVG11_ANAT_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_attributename }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_attributetype }

#define SVG11_ANEV_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onbegin }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onend }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onrepeat }

#define SVG11_ANTIME_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_begin }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_dur }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_end }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_min }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_max }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_restart }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_repeatcount }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_repeatdur }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_fill }

#define SVG11_ANVAL_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_calcmode }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_values }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_keytimes }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_keysplines }

#define SVG11_FILTER_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_x }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_y }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_height }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_result }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_width }

#define SVG11_GREV_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onactivate }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onfocusin }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_onfocusout }

#define SVG11_XLINK_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinkactuate }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinkarcrole }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinkhref }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinkrole }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinkshow }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinktitle }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_xlinktype }

#define SVGx_CONDPROC_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_requiredextensions }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, ELEM, a_requiredfeatures }, \
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, ELEM, a_requiredfonts }, \
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, ELEM, a_requiredformats }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_systemlanguage }

// FFS, SVG 1.2 Tiny does not define WTF a core attribute is. I'll have to presume 1.1 covers it.
#define SVGx_XTRA_CORE_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_xmlspace }

#define SVGx_PRES_ATTRIBUTES(ELEM) \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_alignmentbaseline }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_baselineshift }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_clip }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_clip_path }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_clip_rule }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation_filters }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_colour_profile }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_colour_rendering }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_cursor }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_display }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_dominantbaseline }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_enablebackground }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_filter }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_flood_colour }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_flood_opacity }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_font }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_size_adjust }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_stretch }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_font_weight }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_vertical }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_glyphorientation_horizontal }, \
    { { XHTML_1_0, 0, HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, ELEM, a_imagerendering }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_kerning }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_letter_spacing }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_lighting_colour }, \
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, ELEM, a_marker }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_marker_end }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_marker_mid }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_marker_start }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_mask }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_overflow }, \
    { { XHTML_1_0, 0, HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, ELEM, a_paint_order }, \
    { { XHTML_1_0, 0, HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, ELEM, a_pointerevents }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_shaperendering }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stop_opacity }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_stroke_width }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_textanchor }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_textdecoration }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_textrendering }, \
    { { XHTML_1_0, 0, HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, ELEM, a_transform }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_unicodebidi }, \
    { { XHTML_1_0, 0, HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_visibility }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_word_spacing }, \
    { { XHTML_1_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, ELEM, a_writingmode }

#define MATH1_STANDARD_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_class }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_id }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_other }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_style }

#define MATH1_STANDARD_ATTRIBUTES(ELEM) \
    MATH1_STANDARD_ATTRIBUTES_EX (ELEM, 0)

#define MATH1_FONT_ATTRIBUTES(ELEM) \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_fontfamily }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_fontsize }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_fontstyle }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_fontweight }

#define MATH_OPINFO_ATTRIBUTES(ELEM) \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_accent }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_form }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_fence }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_largeop }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_lspace }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_maxsize }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_minsize }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_movablelimits }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_rspace }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_separator }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_stretchy }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_symmetric }

#define MATH_SIZEINFO_ATTRIBUTES(ELEM) \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_depth }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_height }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_width }

#define MATH1_TABLE_ATTRIBUTES(ELEM) \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_align }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_alignmentscope }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_columnalign }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_columnlines }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_columnspacing }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_displaystyle }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_equalcolumns }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_equalrows }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_frame }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_framespacing }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_groupalign }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_rowalign }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_rowlines }, \
    { { XHTML_1_0 }, { HTML_UNDEF }, ELEM, a_rowspacing }

#define MATH2_STANDARD_ATTRIBUTES_EX(ELEM, FLAGS) \
    MATH1_STANDARD_ATTRIBUTES_EX (ELEM, ( FLAGS | HE_MATH_2 ) ), \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xlinkhref }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xlinktype }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xmlns }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xref }

#define MATH2_STANDARD_ATTRIBUTES(ELEM) \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, 0)

#define MATH2_DEFS_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_1 | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_definitionurl }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_encoding }, \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH2_DEFS_ATTRIBUTES(ELEM) \
    MATH2_DEFS_ATTRIBUTES_EX (ELEM, 0)

#define MATH2_FONT_ATTRIBUTES_EX(ELEM, FLAGS) \
    MATH1_FONT_ATTRIBUTES (ELEM), \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathbackground }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathcolour }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathsize }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathvariant }

#define MATH2_FONT_ATTRIBUTES(ELEM) \
    MATH2_FONT_ATTRIBUTES_EX (ELEM,0) \

#define MATH2_TABLE_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_columnwidth }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_minilabelspacing }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_side }, \
    { { XHTML_1_0, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_width }, \
    MATH1_TABLE_ATTRIBUTES (ELEM)

#define MATH2_TABLE_ATTRIBUTES(ELEM) \
    MATH2_TABLE_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_STANDARD_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_5_2, 0, ( FLAGS | MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_href }, \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, ( FLAGS | MATH_3_4 ) )

#define MATH3_STANDARD_ATTRIBUTES(ELEM) \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_DEFS_ATTRIBUTES_EX(ELEM, FLAGS) \
    MATH2_DEFS_ATTRIBUTES_EX (ELEM, ( FLAGS | MATH_3_4 ) ), \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH3_DEFS_ATTRIBUTES(ELEM) \
    MATH3_DEFS_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_FONT_ATTRIBUTES(ELEM) \
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, ELEM, a_dir }, \
    MATH2_FONT_ATTRIBUTES_EX (ELEM, MATH_3_4)

#define MATH3_TABLE_ATTRIBUTES(ELEM) \
    MATH2_TABLE_ATTRIBUTES_EX (ELEM, MATH_3_4)

#define MATH3_PRES_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_5_2, 0, ( FLAGS | MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_mathbackground }, \
    { { HTML_5_2, 0, ( FLAGS | MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_mathcolour }, \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH3_PRES_ATTRIBUTES(ELEM) \
    MATH3_PRES_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_TOKEN_ATTRIBUTES(ELEM) \
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, ELEM, a_dir }, \
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, ELEM, a_mathsize }, \
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, ELEM, a_mathvariant }

#define MATH3_LINEINDENT_ATTRIBUTES(ELEM) \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentalign }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentalignfirst }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentalignlast }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentshift }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentshiftfirst }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indentshiftlast }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_indenttarget }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_linebreak }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_linebreakmultichar }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_linebreakstyle }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_lineleading }

#define XHTML1_STANDARD_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    RDFA_STANDARD_ATTRIBUTES (ELEM), \
    { { MAJOR_FROM, MINOR_FROM }, { XHTML_2_0 }, ELEM, a_xmlns }, \
    { { HTML_JAN07 }, { HTML_UNDEF }, ELEM, a_xmlns }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_xmllang }

#define XHTML2_COMMON_ATTRIBUTES(ELEM) \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_cite }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_class }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_coords }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_defaultaction }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_dir }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_edit }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_event }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_eventtarget }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_encoding }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_function }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_handler }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_href }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_hreflang }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_hrefmedia }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_hreftype }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_id }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_ismap }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_itstranslate }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_layout }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_media }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_nextfocus }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_observer }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_phase }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_prevfocus }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_propagate }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_role }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_shape }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_srctype }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_style }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_target }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_title }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_usemap }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_xmlbase }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_xmlid }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_xmllang }

#define XHTML2_STANDARD_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    XHTML2_COMMON_ATTRIBUTES(ELEM), \
    XHTML1_STANDARD_ATTRIBUTES(ELEM, MAJOR_X2_0, MINOR_X2_0)

#define XHTML2_ATTRIBUTES(ELEM) \
    XHTML2_STANDARD_ATTRIBUTES(ELEM, MAJOR_X2_0, MINOR_X2_0)

#define HTML4_STANDARD_CIS_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_CI_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    { { MAJOR_FROM, MINOR_FROM, HV_NOTPROD }, { HTML_UNDEF }, ELEM, a_style }

#define HTML4_STANDARD_CIST_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_CIS_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_title }

#define HTML4_STANDARD_TSL_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_LANG_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    HTML4_STANDARD_CIST_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM)

#define HTML4_ATTRIBUTES_BASE(ELEM) \
    HTML4_STANDARD_TSL_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0), \
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0), \
    HTML4_ARIA_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0, HV_ARIA)

#define COMMON_HTML4_ATTRIBUTES(ELEM) \
    HTML4_ATTRIBUTES_BASE (ELEM), \
    XHTML2_STANDARD_ATTRIBUTES (ELEM, MAJOR_X1_0, MINOR_X1_0)

#define HTML4_FORM_ATTRIBUTES_V(ELEM) \
    { { HTML_4_0 }, { HTML_UNDEF }, ELEM, a_accesskey }, \
    { { HTML_4_0 }, { HTML_UNDEF }, ELEM, a_tabindex }

#define HTML4_FORM_ATTRIBUTES(ELEM) \
    HTML4_FORM_ATTRIBUTES_V (ELEM)

#define EXTRA_HTML5_ATTRIBUTES(ELEM) \
    { { HTML_5_0, HV_W3 }, { HTML_UNDEF }, ELEM, a_acceptcharset }, \
    { { HTML_JAN18 }, { HTML_UNDEF }, ELEM, a_autocapitalise }, \
    { { HTML_JAN20 }, { HTML_UNDEF }, ELEM, a_autofocus }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariacolcount }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariacolindex }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariacolspan }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariacurrent }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariadetails }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariaerrormessage }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariamodal }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariaplaceholder }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariaroledescription }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariarowcount }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariarowindex }, \
    { { HTML_APR21 }, { HTML_UNDEF }, ELEM, a_ariarowspan }, \
    { { HTML_JAN07 }, { HTML_UNDEF }, ELEM, a_contenteditable }, \
    { { HTML_JAN06, HV_NOT50 | HV_NOT52 | HV_NOT53 }, { HTML_UNDEF }, ELEM, a_contextmenu }, \
    { { HTML_JAN07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_draggable }, \
    { { HTML_JAN11, HV_NOT50 }, { HTML_DEC16, HV_NOT52 | HV_NOT53 }, ELEM, a_dropzone }, \
    { { HTML_JUL18, HV_NOT53 }, { HTML_UNDEF }, ELEM, a_enterkeyhint }, \
    { { HTML_5_0, HV_W3 }, { HTML_UNDEF }, ELEM, a_generator_unable }, \
    { { HTML_JAN09 }, { HTML_UNDEF }, ELEM, a_hidden }, \
    { { HTML_JUL12 }, { HTML_JUN14 }, ELEM, a_inert }, \
    { { HTML_JUL18 }, { HTML_UNDEF }, ELEM, a_inputmode }, \
    { { HTML_JUL07 }, { HTML_DEC08 }, ELEM, a_irrelevant }, \
    { { HTML_JUL16, HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, ELEM, a_is }, \
    { { HTML_JUL09 }, { HTML_DEC09 }, ELEM, a_item }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemid }, \
    { { HTML_JUL09, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemprop }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemref }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemscope }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemtype }, \
    { { HTML_5_2 }, { HTML_UNDEF }, ELEM, a_numberonce }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onabort }, \
    { { HTML_JUL14, HV_WHATWG }, { HTML_UNDEF }, ELEM, a_onautocomplete }, \
    { { HTML_JUL14, HV_WHATWG }, { HTML_UNDEF }, ELEM, a_onautocompleteerror }, \
    { { HTML_JAN17 }, { HTML_UNDEF }, ELEM, a_onauxclick }, \
    { { HTML_JUL07 }, { HTML_JUN09 }, ELEM, a_onbeforeunload }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onblur }, \
    { { HTML_JUL12 }, { HTML_UNDEF }, ELEM, a_oncancel }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_oncanplay }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_oncanplaythrough }, \
    { { HTML_JAN05 }, { HTML_UNDEF }, ELEM, a_onchange }, \
    { { HTML_JUL12, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_onclose }, \
    { { HTML_JUL07, HV_NOT50 | HV_NOT52 | HV_NOT53 }, { HTML_UNDEF }, ELEM, a_oncontextmenu }, \
    { { HTML_5_1 }, { HTML_5_1 }, ELEM, a_oncopy }, \
    { { HTML_JUL19 }, { HTML_UNDEF }, ELEM, a_oncopy }, \
    { { HTML_JUL10 }, { HTML_UNDEF }, ELEM, a_oncuechange }, \
    { { HTML_5_1 }, { HTML_5_1 }, ELEM, a_oncut }, \
    { { HTML_JUL19 }, { HTML_UNDEF }, ELEM, a_oncut }, \
    { { HTML_JAN05 }, { HTML_UNDEF }, ELEM, a_datawild }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondrag }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondragend }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondragenter }, \
    { { HTML_JUL13 }, { HTML_DEC20 }, ELEM, a_ondragexit }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondragleave }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondragover }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondragstart }, \
    { { HTML_JUL07, HV_NOT50 }, { HTML_UNDEF }, ELEM, a_ondrop }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_ondurationchange }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onemptied }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onended }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onerror }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onfocus }, \
    { { HTML_JUL09 }, { HTML_JUN11 }, ELEM, a_onformchange }, \
    { { HTML_JUL19 }, { HTML_UNDEF }, ELEM, a_onformdata }, \
    { { HTML_JUL09 }, { HTML_JUN11 }, ELEM, a_onforminput }, \
    { { HTML_JAN09 }, { HTML_JUN09 }, ELEM, a_onhashchange }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_oninput }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_oninvalid }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onload }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onloadeddata }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onloadedmetadata }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onloadstart }, \
    { { HTML_JUL16 }, { HTML_5_3 }, ELEM, a_onloadend }, \
    { { HTML_JUL07 }, { HTML_JUN09 }, ELEM, a_onmessage }, \
    { { HTML_JUL13 }, { HTML_UNDEF }, ELEM, a_onmouseenter }, \
    { { HTML_JUL13 }, { HTML_UNDEF }, ELEM, a_onmouseleave }, \
    { { HTML_JUL07 }, { HTML_JUN15 }, ELEM, a_onmousewheel }, \
    { { HTML_5_1 }, { HTML_5_1 }, ELEM, a_onpaste }, \
    { { HTML_JUL19 }, { HTML_UNDEF }, ELEM, a_onpaste }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onpause }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onplay }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onplaying }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onprogress }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onratechange }, \
    { { HTML_JUL09 }, { HTML_DEC11 }, ELEM, a_onreadystatechange }, \
    { { HTML_JAN11 }, { HTML_UNDEF }, ELEM, a_onreset }, \
    { { HTML_JUL07 }, { HTML_JUN09 }, ELEM, a_onresize }, \
    { { HTML_JAN14 }, { HTML_UNDEF }, ELEM, a_onresize }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onscroll }, \
    { { HTML_JAN18, HV_NOT53 }, { HTML_UNDEF }, ELEM, a_onsecuritypolicyviolation }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onseeking }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onselect }, \
    { { HTML_JUL09 }, { HTML_JUN17 }, ELEM, a_onshow }, \
    { { HTML_JUL20 }, { HTML_UNDEF }, ELEM, a_onslotchange }, \
    { { HTML_JAN13 }, { HTML_UNDEF }, ELEM, a_onsort }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onsought }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onstalled }, \
    { { HTML_JUL08 }, { HTML_JUN09 }, ELEM, a_onstorage }, \
    { { HTML_JUL07 }, { HTML_UNDEF }, ELEM, a_onsubmit }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onsuspend }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_ontimeupdate }, \
    { { HTML_JAN14 }, { HTML_UNDEF }, ELEM, a_ontoggle }, \
    { { HTML_JUL07 }, { HTML_JUN09 }, ELEM, a_onunload }, \
    { { HTML_JUL09 }, { HTML_JUN13 }, ELEM, a_onvolumechange }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_onwaiting }, \
    { { HTML_JUL15 }, { HTML_UNDEF }, ELEM, a_onwheel }, \
    { { HTML_JAN08 }, { HTML_DEC08 }, ELEM, a_ref }, \
    { { HTML_JAN08 }, { HTML_DEC08 }, ELEM, a_registrationmark }, \
    { { HTML_JAN10 }, { HTML_UNDEF }, ELEM, a_role }, \
    { { HTML_JUL16, HV_NOT51 | HV_NOT52 | HV_NOT53 }, { HTML_UNDEF }, ELEM, a_slot }, \
    { { HTML_JUL09 }, { HTML_UNDEF }, ELEM, a_spellcheck }, \
    { { HTML_JUL09, 0, HE_NOT_SVG }, { HTML_DEC09 }, ELEM, a_subject }, \
    { { HTML_JAN08 }, { HTML_DEC08 }, ELEM, a_template }, \
    { { HTML_JUL12 }, { HTML_UNDEF }, ELEM, a_translate }, \
    { { HTML_5_3 }, { HTML_5_3 }, ELEM, a_xmlns }, \
    { { HTML_5_0, HV_W3 }, { HTML_UNDEF }, ELEM, a_xmlspace }

#define STANDARD_HTML5_ATTRIBUTES(ELEM) \
    EXTRA_HTML5_ATTRIBUTES (ELEM), \
    HTML4_ATTRIBUTES_BASE (ELEM), \
    HTML4_FORM_ATTRIBUTES_V (ELEM)

#define STANDARD_HTMLS_4_5_ATTRIBUTES(ELEM) \
    COMMON_HTML4_ATTRIBUTES (ELEM), \
    HTML4_FORM_ATTRIBUTES_V (ELEM), \
    EXTRA_HTML5_ATTRIBUTES (ELEM)

#define STANDARD_H_ATTRIBUTES(ELEM) \
    HTMLPLUS_ATTRIBUTES (ELEM), \
    STANDARD_HTML_23_H_ATTRIBUTES (ELEM), \
    STANDARD_HTMLS_4_5_ATTRIBUTES (ELEM)

hav_t havt [] =
{   { { HTML_2_0, HV_RFC_2070 | HV_NOT3 }, { XHTML_2_0 }, elem_a, a_charset },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_a, a_command },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_coords },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_a, a_download },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_effect },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, a_externalresourcesrequired },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_a, a_href },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_a, a_hreflang },
    { { HTML_3_0 }, { HTML_3_0 }, elem_a, a_md },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_a, a_media },
    { { HTML_1_0 }, { HTML_3_0 }, elem_a, a_methods },
    { { HTML_TAGS, HV_DEPRECATED30 | HV_DEPRECATEDX1 }, { XHTML_1_1 }, elem_a, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_onfocus },
    { { HTML_JAN06, HV_NOT50 | HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, elem_a, a_ping },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_print },
    { { HTML_JUL16 }, { HTML_UNDEF }, elem_a, a_referrerpolicy },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_a, a_rel },
    { { HTML_1_0, HV_NOT50 | HV_W3 }, { HTML_5_3 }, elem_a, a_rev },
    { { HTML_2_0, 0, HE_MOZILLA | HE_NETSCAPE }, { HTML_3_2 }, elem_a, a_shape },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { XHTML_2_0 }, elem_a, a_shape },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_size },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_style },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_target },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_a, a_target },
    { { HTML_1_0, HV_NOT30 }, { HTML_3_2 }, elem_a, a_title },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, a_transform },
    { { HTML_TAGS, HV_NOT10 | HV_NOT2 | HV_NOT3 }, { HTML_UNDEF }, elem_a, a_type },
    { { HTML_1_0 }, { HTML_2_0 }, elem_a, a_urn },
    HTMLPLUS_ATTRIBUTES (elem_a),
    HTML23_CLID_ATTRIBUTES (elem_a),
    HTML4_FORM_ATTRIBUTES (elem_a),
    SVG10_REPL_ATTRIBUTES (elem_a),
    SVG11_XLINK_ATTRIBUTES (elem_a),
    SVG11_GREV_ATTRIBUTES (elem_a),
    SVGx_CONDPROC_ATTRIBUTES (elem_a),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_a),
    SVGx_PRES_ATTRIBUTES (elem_a),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_a),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_abbr, a_full },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_abbr),

    HTMLPLUS_ATTRIBUTES (elem_abbrev),
    HTML3_CLID_ATTRIBUTES (elem_abbrev),

    { { HTML_3_0 }, { HTML_3_0 }, elem_above, a_sym },

    MATH3_DEFS_ATTRIBUTES (elem_abs),

    HTMLPLUS_ATTRIBUTES (elem_abstract),

    HTMLPLUS_ATTRIBUTES (elem_acronym),
    HTML3_CLID_ATTRIBUTES (elem_acronym),
    COMMON_HTML4_ATTRIBUTES (elem_acronym),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_activate },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_key },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_media },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_order },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetid },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetrole },
    XHTML2_ATTRIBUTES (elem_access),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_declare },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_if },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_while },
    XHTML2_ATTRIBUTES (elem_action),

    HTMLPLUS_ATTRIBUTES (elem_added),

    XHTML2_ATTRIBUTES (elem_addeventlistener),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_address, a_align },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_address, a_clear },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_address, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_address),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_address),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyph, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyph, a_format },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyph, a_glyphref },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyph, a_rotate },
    SVG10_XY_ATTRIBUTES (elem_altglyph),
    SVG10_DXY_ATTRIBUTES (elem_altglyph),
    SVG11_XLINK_ATTRIBUTES (elem_altglyph),
    SVG11_GREV_ATTRIBUTES (elem_altglyph),
    SVGx_CONDPROC_ATTRIBUTES (elem_altglyph),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_altglyph),
    SVGx_PRES_ATTRIBUTES (elem_altglyph),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_altglyph),

    SVGx_XTRA_CORE_ATTRIBUTES (elem_altglyphdef),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_altglyphdef),

    SVGx_XTRA_CORE_ATTRIBUTES (elem_altglyphitem),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_altglyphitem),

    MATH3_DEFS_ATTRIBUTES (elem_and),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animate, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animate, a_from },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animate, a_to},
    SVG11_ANADD_ATTRIBUTES (elem_animate),
    SVG11_ANAT_ATTRIBUTES (elem_animate),
    SVG11_ANEV_ATTRIBUTES (elem_animate),
    SVG11_ANTIME_ATTRIBUTES (elem_animate),
    SVG11_ANVAL_ATTRIBUTES (elem_animate),
    SVG11_XLINK_ATTRIBUTES (elem_animate),
    SVGx_CONDPROC_ATTRIBUTES (elem_animate),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_animate),
    SVGx_PRES_ATTRIBUTES (elem_animate),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_animate),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatecolour, a_externalresourcesrequired },
    SVG11_ANADD_ATTRIBUTES (elem_animatecolour),
    SVG11_ANAT_ATTRIBUTES (elem_animatecolour),
    SVG11_ANEV_ATTRIBUTES (elem_animatecolour),
    SVG11_ANTIME_ATTRIBUTES (elem_animatecolour),
    SVG11_ANVAL_ATTRIBUTES (elem_animatecolour),
    SVG11_XLINK_ATTRIBUTES (elem_animatecolour),
    SVGx_CONDPROC_ATTRIBUTES (elem_animatecolour),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_animatecolour),
    SVGx_PRES_ATTRIBUTES (elem_animatecolour),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_animatecolour),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatemotion, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatemotion, a_keypoints },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatemotion, a_origin },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatemotion, a_path },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatemotion, a_rotate },
    SVG11_ANADD_ATTRIBUTES (elem_animatemotion),
    SVG11_ANEV_ATTRIBUTES (elem_animatemotion),
    SVG11_ANTIME_ATTRIBUTES (elem_animatemotion),
    SVG11_ANVAL_ATTRIBUTES (elem_animatemotion),
    SVG11_XLINK_ATTRIBUTES (elem_animatemotion),
    SVGx_CONDPROC_ATTRIBUTES (elem_animatemotion),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_animatemotion),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_animatemotion),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatetransform, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatetransform, a_from },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatetransform, a_to },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_animatetransform, a_type },
    SVG11_ANADD_ATTRIBUTES (elem_animatetransform),
    SVG11_ANAT_ATTRIBUTES (elem_animatetransform),
    SVG11_ANEV_ATTRIBUTES (elem_animatetransform),
    SVG11_ANTIME_ATTRIBUTES (elem_animatetransform),
    SVG11_ANVAL_ATTRIBUTES (elem_animatetransform),
    SVG11_XLINK_ATTRIBUTES (elem_animatetransform),
    SVGx_CONDPROC_ATTRIBUTES (elem_animatetransform),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_animatetransform),
    SVGx_PRES_ATTRIBUTES (elem_animatetransform),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_animatetransform),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_animation),

    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_cd },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_definitionurl },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_annotation, a_encoding },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_name },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation),

    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_cd },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_definitionurl },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_annotation_xml, a_encoding },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_name },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation_xml),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_align },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_alt },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_archive },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_class },
    { { HTML_3_2, HV_DEPRECATED4 | REQUIRED }, { XHTML_2_0 }, elem_applet, a_code },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_codebase },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_height },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_id },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_hspace },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_name },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_object },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_style },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_title },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_vspace },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_width },

    MATH3_STANDARD_ATTRIBUTES (elem_apply),

    MATH3_DEFS_ATTRIBUTES (elem_approx),

    MATH3_DEFS_ATTRIBUTES (elem_arccos),

    MATH3_DEFS_ATTRIBUTES (elem_arccosh),

    MATH3_DEFS_ATTRIBUTES (elem_arccot),

    MATH3_DEFS_ATTRIBUTES (elem_arccoth),

    MATH3_DEFS_ATTRIBUTES (elem_arccsc),

    MATH3_DEFS_ATTRIBUTES (elem_arccsch),

    MATH3_DEFS_ATTRIBUTES (elem_arcsec),

    MATH3_DEFS_ATTRIBUTES (elem_arcsech),

    MATH3_DEFS_ATTRIBUTES (elem_arcsin),

    MATH3_DEFS_ATTRIBUTES (elem_arcsinh),

    MATH3_DEFS_ATTRIBUTES (elem_arctan),

    MATH3_DEFS_ATTRIBUTES (elem_arctanh),

    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_DEC06 }, elem_area, a_alt },
    { { HTML_JAN07, REQUIRED }, { HTML_JUN07 }, elem_area, a_alt },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_area, a_alt },
    { { HTML_2_0, HV_RFC_1980 | HV_NOT30 | REQUIRED }, { HTML_DEC06 }, elem_area, a_coords },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_area, a_coords },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_area, a_download },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_area, a_href },
    { { HTML_JAN07 }, { HTML_DEC15 }, elem_area, a_hreflang },
    { { HTML_5_1, HV_W3 }, { HTML_5_3 }, elem_area, a_hreflang },
    { { HTML_JAN07 }, { HTML_DEC12 }, elem_area, a_media },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_name },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { XHTML_2_0 }, elem_area, a_nohref },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_onfocus },
    { { HTML_JAN07, HV_NOT50 | HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, elem_area, a_ping },
    { { HTML_JAN17 }, { HTML_UNDEF }, elem_area, a_referrerpolicy },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_area, a_rel },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_area, a_shape },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_target },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_area, a_target },
    { { HTML_JAN07 }, { HTML_DEC15 }, elem_area, a_type },
    { { HTML_5_1, HV_W3 }, { HTML_5_3 }, elem_area, a_type },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_usemap },
    HTML4_FORM_ATTRIBUTES (elem_area),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_area),

    MATH3_DEFS_ATTRIBUTES (elem_arg),
    HTMLPLUS_ATTRIBUTES (elem_arg),

    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_array, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_coldef },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_labels },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_ldelim },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_rdelim },

    HTML3_CLID_ATTRIBUTES (elem_array),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_article, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_cite },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_article),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_aside, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_aside),

    { { HTML_JUL09 }, { HTML_JUN10 }, elem_audio, a_autobuffer },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_autoplay },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_controls },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_audio, a_crossorigin },
    { { HTML_JUL07, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_audio, a_currenttime },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_audio, a_disableremoteplayback },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_end },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_audio, a_loop },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopcount },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopend },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopstart },
    { { HTML_JUL11 }, { HTML_JUN16 }, elem_audio, a_mediagroup },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_audio, a_muted },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_audio, a_preload },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_src },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_start },
    STANDARD_HTML5_ATTRIBUTES(elem_audio),

    HTML3_CLID_ATTRIBUTES (elem_au),

    HTMLPLUS_ATTRIBUTES (elem_b),
    HTML23_CLID_ATTRIBUTES (elem_b),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_b),

    { { HTML_JUL08 }, { HTML_DEC09 }, elem_bb, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_bb),

    HTML3_CLID_ATTRIBUTES (elem_banner),

    HTML3_CLID_ATTRIBUTES (elem_bar),

    { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_base, a_href },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_base, a_href },
    { { HTML_3_0 }, { HTML_3_0 }, elem_base, a_id },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_base, a_target },
    STANDARD_HTML5_ATTRIBUTES (elem_base),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_colour },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_face },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_size },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_basefont, MAJOR_4_0, MINOR_4_0),

    { { HTML_JAN11 }, { HTML_UNDEF }, elem_bdi, a_dir },
    STANDARD_HTML5_ATTRIBUTES (elem_bdi),

    { { HTML_2_0, HV_RFC_2070 | REQUIRED }, { HTML_2_0 }, elem_bdo, a_dir },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_bdo, a_dir },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_bdo, a_lang },
    HTML2_CLID_ATTRIBUTES (elem_bdo),
    STANDARD_HTML5_ATTRIBUTES (elem_bdo),

    { { HTML_3_0 }, { HTML_3_0 }, elem_below, a_sym },

    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_balance },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_loop },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_src },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_volume },

    HTML3_CLID_ATTRIBUTES (elem_big),
    COMMON_HTML4_ATTRIBUTES (elem_big),

    MATH3_STANDARD_ATTRIBUTES (elem_bind),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_blockquote, a_active },
    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_blockquote, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_blockquote, a_cite },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_blockquote),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_blockquote),

    XHTML2_ATTRIBUTES (elem_blockcode),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_alink },
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

    { { HTML_3_0 }, { HTML_3_0 }, elem_box, a_size },

    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_nowrap },
    HTML3_CLID_ATTRIBUTES (elem_bq),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_id },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_class },
    { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_br, a_clear },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_title },
    { { HTML_4_0, HV_NOTPROD }, { HTML_UNDEF }, elem_br, a_style },
    HTMLPLUS_ATTRIBUTES (elem_br),
    HTML3_CLID_ATTRIBUTES (elem_br),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_br, HTML_2005, 0),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_br, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_br),

    { { HTML_3_0 }, { HTML_3_0 }, elem_bt, a_class },

    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_action },
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
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_target },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_type },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_value },
    HTML4_FORM_ATTRIBUTES (elem_button),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_button),

    MATH3_STANDARD_ATTRIBUTES (elem_bvar),

    HTMLPLUS_ATTRIBUTES (elem_byline),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_calendar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_calendar),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_height },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_width },
    STANDARD_HTML5_ATTRIBUTES (elem_canvas),

    { { HTML_2_0, HV_DEPRECATED4 | HV_RFC_1942 }, { XHTML_2_0 }, elem_caption, a_align },
    { { HTML_3_2 }, { HTML_3_2 }, elem_caption, a_valign },
    HTMLPLUS_ATTRIBUTES (elem_caption),
    HTML23_CLID_ATTRIBUTES (elem_caption),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_caption),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_card, a_active },
    MATH3_DEFS_ATTRIBUTES (elem_card),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_card),

    MATH3_DEFS_ATTRIBUTES (elem_cartesianproduct),

    MATH3_STANDARD_ATTRIBUTES (elem_cbytes),

    MATH3_DEFS_ATTRIBUTES (elem_ceiling),

    MATH3_STANDARD_ATTRIBUTES (elem_cerror),

    { { HTML_PLUS }, { HTML_PLUS }, elem_changed, a_idref },
    HTMLPLUS_ATTRIBUTES (elem_changed),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ci, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_ci),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_circle, a_cx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_circle, a_cy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_circle, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_circle, a_r },
    SVG10_G_ATTRIBUTES(elem_circle),
    SVG11_GREV_ATTRIBUTES (elem_circle),
    SVGx_CONDPROC_ATTRIBUTES (elem_circle),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_circle),
    SVGx_PRES_ATTRIBUTES (elem_circle),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_circle),

    HTMLPLUS_ATTRIBUTES (elem_cite),
    HTML23_CLID_ATTRIBUTES (elem_cite),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_cite),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, a_clippathunits },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, a_transform },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_clippath),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_clippath),
    SVGx_PRES_ATTRIBUTES (elem_clippath),
    STANDARD_HTML5_ATTRIBUTES (elem_clippath),

    HTMLPLUS_ATTRIBUTES (elem_cmd),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_base },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_cn),

    HTMLPLUS_ATTRIBUTES (elem_code),
    HTML23_CLID_ATTRIBUTES (elem_code),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_code),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_col, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_col, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_col, a_span },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_valign },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_width },
    HTML2_CLID_ATTRIBUTES (elem_col),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_col),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_colgroup, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_colgroup, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_char },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_char },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_4_0, 0, HE_IE }, { XHTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_colgroup, a_span },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_width },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_width },
    HTML2_CLID_ATTRIBUTES (elem_colgroup),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_colgroup),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_colourprofile, a_local },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_colourprofile, a_renderingintent },
    SVG11_XLINK_ATTRIBUTES (elem_colourprofile),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_colourprofile),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_colourprofile),

    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_checked },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_command },
    { { HTML_JAN05 }, { HTML_JUN09 }, elem_command, a_default },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_disabled },
    { { HTML_JAN05 }, { HTML_DEC08 }, elem_command, a_hidden },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_icon },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_label },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_radiogroup },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_command),

    STANDARD_HTML5_ATTRIBUTES (elem_commandset),

    MATH3_DEFS_ATTRIBUTES (elem_complexes),

    MATH3_DEFS_ATTRIBUTES (elem_compose),

    MATH3_STANDARD_ATTRIBUTES (elem_condition),

    { { HTML_2_0 }, { HTML_4_01 }, elem_comment, a_data },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_comment, MAJOR_4_0, MINOR_4_0),

    MATH3_DEFS_ATTRIBUTES (elem_conjugate),

    { { HTML_JAN05 }, { HTML_UNDEF }, elem_content, a_select },
    STANDARD_HTML5_ATTRIBUTES (elem_content),

    MATH3_DEFS_ATTRIBUTES (elem_cos),

    MATH3_DEFS_ATTRIBUTES (elem_cosh),

    MATH3_DEFS_ATTRIBUTES (elem_cot),

    MATH3_DEFS_ATTRIBUTES (elem_coth),

    HTML3_CLID_ATTRIBUTES (elem_credit),

    MATH3_DEFS_ATTRIBUTES (elem_cs),

    MATH3_DEFS_ATTRIBUTES (elem_csc),

    MATH3_DEFS_ATTRIBUTES (elem_csch),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_csymbol, a_cd },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_csymbol, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_csymbol),

    MATH3_DEFS_ATTRIBUTES (elem_curl),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_cursor, a_externalresourcesrequired },
    SVG10_XY_ATTRIBUTES (elem_cursor),
    SVG11_XLINK_ATTRIBUTES (elem_cursor),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_cursor),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_cursor),

    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_disabled },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_form },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_name },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_readonly },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_custom),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_data, a_d },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_data, a_value },
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

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, a_transform },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_desc, a_systemrequired },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_ellipse, a_cx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_ellipse, a_cy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_ellipse, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_ellipse, a_rx },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_ellipse, a_ry },
    SVG10_G_ATTRIBUTES(elem_ellipse),
    SVG11_GREV_ATTRIBUTES (elem_ellipse),
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feblend, a_in2 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feblend, a_mode },
    SVG10_FILTER_ATTRIBUTES (elem_feblend),
    SVG11_FILTER_ATTRIBUTES (elem_feblend),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feblend),
    SVGx_PRES_ATTRIBUTES (elem_feblend),
    STANDARD_HTML5_ATTRIBUTES (elem_feblend),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecolour, a_colour },
    SVG10_FILTER_ATTRIBUTES (elem_fecolour),
    STANDARD_HTML5_ATTRIBUTES (elem_fecolour),

    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_fecolourmatrix, a_type },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecolourmatrix, a_values },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecomposite, a_operator },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecomposite, a_k1 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecomposite, a_k2 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecomposite, a_k3 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fecomposite, a_k4 },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_fecomposite, a_in2 },
    SVG10_FILTER_ATTRIBUTES (elem_fecomposite),
    SVG11_FILTER_ATTRIBUTES (elem_fecomposite),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fecomposite),
    SVGx_PRES_ATTRIBUTES (elem_fecomposite),
    STANDARD_HTML5_ATTRIBUTES (elem_fecomposite),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_bias },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_divisor },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_edgemode },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_in },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelmatrix },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_kernelunitlength },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_order },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_preservealpha },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targetx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, a_targety },
    SVG11_FILTER_ATTRIBUTES (elem_feconvolvematrix),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feconvolvematrix),
    SVGx_PRES_ATTRIBUTES (elem_feconvolvematrix),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_feconvolvematrix),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fediffuselighting, a_diffuseconstant },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fediffuselighting, a_lightcolour },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fediffuselighting, a_resultscale },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fediffuselighting, a_surfacescale },
    SVG10_FILTER_ATTRIBUTES (elem_fediffuselighting),
    STANDARD_HTML5_ATTRIBUTES (elem_fediffuselighting),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedisplacementmap, a_xchannelselector },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedisplacementmap, a_ychannelselector },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedisplacementmap, a_in2 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedisplacementmap, a_scale },
    SVG10_FILTER_ATTRIBUTES (elem_fedisplacementmap),
    SVG11_FILTER_ATTRIBUTES (elem_fedisplacementmap),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fedisplacementmap),
    SVGx_PRES_ATTRIBUTES (elem_fedisplacementmap),
    STANDARD_HTML5_ATTRIBUTES (elem_fedisplacementmap),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedistantlight, a_azimuth },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fedistantlight, a_elevation },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fegaussianblur, a_stddeviation },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_fegaussianblur, a_std_deviation },
    SVG10_FILTER_ATTRIBUTES (elem_fegaussianblur),
    SVG11_FILTER_ATTRIBUTES (elem_fegaussianblur),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fegaussianblur),
    SVGx_PRES_ATTRIBUTES (elem_fegaussianblur),
    STANDARD_HTML5_ATTRIBUTES (elem_fegaussianblur),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feimage, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feimage, a_nodeid },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feimage, a_preserveaspectratio },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_femergenode, a_in },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_femergenode),
    STANDARD_HTML5_ATTRIBUTES (elem_femergenode),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_femorphology, a_operator },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_femorphology, a_radius },
    SVG10_FILTER_ATTRIBUTES (elem_femorphology),
    SVG11_FILTER_ATTRIBUTES (elem_femorphology),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_femorphology),
    SVGx_PRES_ATTRIBUTES (elem_femorphology),
    STANDARD_HTML5_ATTRIBUTES (elem_femorphology),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feoffset, a_in },
    SVG10_DXY_ATTRIBUTES (elem_feoffset),
    SVG10_FILTER_ATTRIBUTES (elem_feoffset),
    SVG11_FILTER_ATTRIBUTES (elem_feoffset),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_feoffset),
    SVGx_PRES_ATTRIBUTES (elem_feoffset),
    STANDARD_HTML5_ATTRIBUTES (elem_feoffset),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fepointlight, a_x },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fepointlight, a_y },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fepointlight, a_z },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fepointlight),
    STANDARD_HTML5_ATTRIBUTES (elem_fepointlight),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespecularlighting, a_kernelunitlength },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespecularlighting, a_lightcolour },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularconstant },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespecularlighting, a_specularexponent },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespecularlighting, a_surfacescale },
    SVG10_FILTER_ATTRIBUTES (elem_fespecularlighting),
    SVG11_FILTER_ATTRIBUTES (elem_fespecularlighting),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fespecularlighting),
    SVGx_PRES_ATTRIBUTES (elem_fespecularlighting),
    STANDARD_HTML5_ATTRIBUTES (elem_fespecularlighting),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_x },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_y },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_z },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_ellipse, a_limitingconeangle },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_pointsaty },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_pointsatz },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fespotlight, a_specularexponent },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fespotlight),
    STANDARD_HTML5_ATTRIBUTES (elem_fespotlight),

    SVG10_FILTER_ATTRIBUTES (elem_fetile),
    SVG11_FILTER_ATTRIBUTES (elem_fetile),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fetile),
    SVGx_PRES_ATTRIBUTES (elem_fetile),
    STANDARD_HTML5_ATTRIBUTES (elem_fetile),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feturbulence, a_basefrequency },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feturbulence, a_numoctaves },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feturbulence, a_seed },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feturbulence, a_stitchtiles },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_feturbulence, a_type },
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

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_ellipse, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, a_filterres },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, a_filter_units },
    { { HTML_4_0, 0, HE_SVG_1x2 }, { HTML_UNDEF }, elem_filter, a_filterunits },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_filter, a_primitiveunits },
    SVG10_BOX_ATTRIBUTES (elem_filter),
    SVG11_XLINK_ATTRIBUTES (elem_filter),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_filter),
    SVGx_PRES_ATTRIBUTES (elem_filter),
    STANDARD_HTML5_ATTRIBUTES (elem_filter),

    MATH3_DEFS_ATTRIBUTES (elem_floor),

    HTML23_CLID_ATTRIBUTES (elem_fn),
    MATH2_DEFS_ATTRIBUTES (elem_fn),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_colour },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_externalresourcesrequired },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_face },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_horizadvx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_horizoriginx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_horizoriginy },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_font, a_size },
    { { HTML_JUL07, HV_NOTPROD }, { HTML_JUN08 }, elem_font, a_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_vertadvy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_vertoriginx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, a_vertoriginy },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_font),
    SVGx_PRES_ATTRIBUTES (elem_font),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_font),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_accentheight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_alphabetic },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_ascent },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_accentheight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_ascent },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_bbox },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_capheight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_descent },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_family },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_size },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_stretch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_style, },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_variant },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_font_weight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_hanging },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_ideographic },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_mathematical },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_overlineposition },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_overlinethickness },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_panose1 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_slope },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_stemh },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_stemv },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_strikethroughposition },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_strikethroughthickness },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_underlineposition },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_underlinethickness },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_unicoderange },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_unitsperem },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_valphabetic },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_vhanging },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_videographic },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_vmathematical },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_widths },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, a_xheight },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontface),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontface),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontfaceformat, a_string },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_fontfaceformat),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_fontfaceformat),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontfacename, a_name },
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

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_foreignobject, a_externalresourcesrequired },
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

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_g, a_allow_zoom_pan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_g, a_onzoom },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, a_transform },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_g, a_version },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_g, a_xmlns },
    SVG10_BOX_ATTRIBUTES (elem_g),
    SVG10_FIT_ATTRIBUTES (elem_g),
    SVG10_G_ATTRIBUTES (elem_g),
    SVG11_GREV_ATTRIBUTES (elem_g),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_g),
    SVGx_CONDPROC_ATTRIBUTES (elem_g),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_g),
    SVGx_PRES_ATTRIBUTES (elem_g),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_g),

    STANDARD_HTML5_ATTRIBUTES (elem_gauge),

    MATH3_DEFS_ATTRIBUTES (elem_gcd),

    MATH3_DEFS_ATTRIBUTES (elem_geq),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_arabicform },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_d },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_glyphname },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_horizadvx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_orientation },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_unicode },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_vertadvy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_vertoriginx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, a_vertoriginy },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_glyph),
    SVGx_PRES_ATTRIBUTES (elem_glyph),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_glyph),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyphref, a_glyphref },
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

    HTML3_CLID_ATTRIBUTES (elem_hat),

    { { HTML_4_0 }, { HTML_DEC06 }, elem_head, a_profile },
    HTML2_CLID_ATTRIBUTES (elem_head),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_head, MAJOR_4_0, MINOR_4_0),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_head, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_head),

    STANDARD_HTML5_ATTRIBUTES (elem_header),

    STANDARD_HTML5_ATTRIBUTES (elem_hgroup),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_handler),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_hkern, a_g1 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_hkern, a_g2 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_hkern, a_k },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_hkern, a_u1 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_hkern, a_u1 },
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

    HTMLPLUS_ATTRIBUTES (elem_i),
    HTML23_CLID_ATTRIBUTES (elem_i),
    STANDARD_HTML5_ATTRIBUTES (elem_i),

    MATH3_DEFS_ATTRIBUTES (elem_ident),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, a_align },
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
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_iframe),

    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, elem_ilayer, a_above },
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

    { { HTML_PLUS }, { HTML_PLUS }, elem_image, a_align },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_image, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_image, a_preserveaspectratio },
    { { HTML_PLUS, REQUIRED }, { HTML_PLUS }, elem_image, a_src },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_image, a_xlinkhref },
    HTMLPLUS_ATTRIBUTES (elem_image),
    MATH3_DEFS_ATTRIBUTES (elem_image),
    SVG10_BOX_ATTRIBUTES (elem_image),
    SVG10_G_ATTRIBUTES (elem_image),
    SVG10_REPL_ATTRIBUTES (elem_image),
    SVG11_GREV_ATTRIBUTES (elem_image),
    SVGx_CONDPROC_ATTRIBUTES (elem_image),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_image),
    SVGx_PRES_ATTRIBUTES (elem_image),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_image),

    MATH3_DEFS_ATTRIBUTES (elem_imaginary),

    MATH3_DEFS_ATTRIBUTES (elem_imaginaryi),

    { { HTML_1_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_img, a_align },
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

    MATH3_DEFS_ATTRIBUTES (elem_implies),

    MATH3_DEFS_ATTRIBUTES (elem_in),

    MATH3_DEFS_ATTRIBUTES (elem_infinity),

    { { HTML_2_0, HV_RFC_1867 | HV_NOT32 }, { HTML_UNDEF }, elem_input, a_accept },
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

    { { HTML_4_0 }, { HTML_UNDEF }, elem_ins, a_cite },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_ins, a_datetime },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_id },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, a_lang },
    HTML3_CLID_ATTRIBUTES (elem_ins),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ins),

    MATH3_DEFS_ATTRIBUTES (elem_int),

    MATH3_DEFS_ATTRIBUTES (elem_integers),

    MATH3_DEFS_ATTRIBUTES (elem_intersect),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_interval, a_closure },
    MATH3_STANDARD_ATTRIBUTES (elem_interval),

    MATH3_DEFS_ATTRIBUTES (elem_inverse),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_dir },
    { { HTML_3_0 }, { HTML_3_0 }, elem_isindex, a_href },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_id },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_lang },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_isindex, a_prompt },
    { { HTML_4_0, HV_NOTPROD }, { HTML_UNDEF }, elem_isindex, a_style },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_isindex, a_title },
    HTML2_CLID_ATTRIBUTES (elem_isindex),

    { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_item, a_rowspan },

    HTMLPLUS_ATTRIBUTES (elem_kbd),
    HTML23_CLID_ATTRIBUTES (elem_kbd),
    STANDARD_HTML5_ATTRIBUTES (elem_kbd),

    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_autofocus },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_challenge },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_disabled },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_form },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_keytype },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_keygen),

    { { HTML_PLUS }, { HTML_PLUS }, elem_l, a_align },
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

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_line, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_line, a_x1 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_line, a_x2 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_line, a_y1 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_line, a_y2 },
    SVG10_G_ATTRIBUTES (elem_line),
    SVG11_GREV_ATTRIBUTES (elem_line),
    SVGx_CONDPROC_ATTRIBUTES (elem_line),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_line),
    SVGx_PRES_ATTRIBUTES (elem_line),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_line),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_lineargradient, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_lineargradient, a_spreadmethod },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_lineargradient, a_x1 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_lineargradient, a_x2 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_lineargradient, a_y1 },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_lineargradient, a_y2 },
    SVG10_GRAD_ATTRIBUTES (elem_lineargradient),
    SVG11_XLINK_ATTRIBUTES (elem_lineargradient),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_lineargradient),
    SVGx_PRES_ATTRIBUTES (elem_lineargradient),
    STANDARD_HTML5_ATTRIBUTES (elem_lineargradient),

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

    XHTML2_ATTRIBUTES (elem_listener),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_listener),

    HTML23_CLID_ATTRIBUTES (elem_listing),

    HTMLPLUS_ATTRIBUTES (elem_lit),

    MATH3_DEFS_ATTRIBUTES (elem_ln),

    MATH3_DEFS_ATTRIBUTES (elem_log),

    MATH3_STANDARD_ATTRIBUTES (elem_logbase),

    MATH3_STANDARD_ATTRIBUTES (elem_lowlimit),

    MATH3_DEFS_ATTRIBUTES (elem_lt),

    STANDARD_HTML5_ATTRIBUTES (elem_m),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_maction, a_actiontype },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_maction, a_selection },
    MATH3_PRES_ATTRIBUTES (elem_maction),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_maligngroup, a_groupalign },
    MATH3_PRES_ATTRIBUTES (elem_maligngroup),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_malignmark, a_edge },

    STANDARD_HTML5_ATTRIBUTES (elem_main),

    { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_map, a_name },
    { { XHTML_1_0, HV_DEPRECATEDX1 }, { XHTML_2_0 }, elem_map, a_name },
    { { HTML_JAN05, REQUIRED }, { HTML_UNDEF }, elem_map, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_map),

    HTMLPLUS_ATTRIBUTES (elem_margin),

    STANDARD_HTML5_ATTRIBUTES (elem_mark),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_line, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_marker, a_orient },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_marker, a_markerheight },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_marker, a_markerunits },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_marker, a_markerwidth },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, a_preserveaspectratio },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, a_viewbox },
    SVG10_BOX_ATTRIBUTES (elem_marker),
    SVG10_FIT_ATTRIBUTES (elem_marker),
    SVG10_REF_XY_ATTRIBUTES (elem_marker),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_marker),
    SVGx_PRES_ATTRIBUTES (elem_marker),
    STANDARD_HTML5_ATTRIBUTES (elem_marker),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_behaviour },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_bgcolour },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_direction },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_height },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_hspace },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_loop },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_scrollamount },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_scrolldelay },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_truespeed },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_vspace },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_width },

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_mask, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_mask, a_maskcontentunits },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_mask, a_mask_units },
    { { HTML_4_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_mask, a_maskunits },
    SVG10_BOX_ATTRIBUTES (elem_mask),
    SVGx_CONDPROC_ATTRIBUTES (elem_mask),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_mask),
    SVGx_PRES_ATTRIBUTES (elem_mask),
    STANDARD_HTML5_ATTRIBUTES (elem_mask),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_altimg },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_height },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_width },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_alttext },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_baseline },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_math, a_cdgroup },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_definitionurl },
    { { XHTML_1_0, 0, HE_MATH_2 }, { HTML_UNDEF }, elem_math, a_display },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_height },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_macros },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_math, a_maxwidth },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_mode },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_overflow },
    { { XHTML_1_0, HV_NOTPROD }, { HTML_UNDEF }, elem_math, a_style },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_type },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, a_width },
    MATH3_TOKEN_ATTRIBUTES (elem_math),
    MATH3_LINEINDENT_ATTRIBUTES (elem_math),
    MATH3_PRES_ATTRIBUTES (elem_math),
    HTML3_CLID_ATTRIBUTES (elem_math),

    MATH3_STANDARD_ATTRIBUTES (elem_matrix),

    MATH3_STANDARD_ATTRIBUTES (elem_matrixrow),

    MATH3_DEFS_ATTRIBUTES (elem_max),

    MATH3_DEFS_ATTRIBUTES (elem_mean),

    MATH3_DEFS_ATTRIBUTES (elem_median),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_menclose, a_notation },
    MATH3_PRES_ATTRIBUTES (elem_menclose),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_menu, a_align },
    { { HTML_JAN05 }, { HTML_DEC08 }, elem_menu, a_autosubmit },
    { { HTML_3_2 }, { HTML_3_2 }, elem_menu, a_clear },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_menu, a_compact },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_3_2 }, elem_menu, a_label },
    { { HTML_JAN05, HV_NOT50 | HV_NOT52 | HV_NOT53 }, { HTML_JUN17 }, elem_menu, a_label },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_3_2 }, elem_menu, a_type },
    { { HTML_JAN06, HV_NOT50 | HV_NOT52 | HV_NOT53 }, { HTML_JUN17 }, elem_menu, a_type },
    HTMLPLUS_ATTRIBUTES (elem_menu),
    HTML2_CLID_ATTRIBUTES (elem_menu),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_menu),

    STANDARD_HTML5_ATTRIBUTES (elem_menubar),

    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_checked },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_default },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_disabled },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_icon },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_label },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_radiogroup },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_menuitem),

    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menulabel, a_label },
    STANDARD_HTML5_ATTRIBUTES (elem_menulabel),

    MATH3_PRES_ATTRIBUTES (elem_merror),

    { { HTML_JUL07 }, { HTML_UNDEF }, elem_meta, a_charset },
    { { HTML_2_0, REQUIRED }, { XHTML_1_1 }, elem_meta, a_content },
    { { XHTML_2_0 }, { HTML_UNDEF }, elem_meta, a_content },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_dir },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_meta, a_httpequiv },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_lang },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_meta, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_scheme },
    HTML23_CLID_ATTRIBUTES (elem_meta),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_meta),

    SVGx_XTRA_CORE_ATTRIBUTES (elem_metadata),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_metadata),

    { { HTML_JUL10 }, { HTML_JUN11 }, elem_meter, a_form },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_high },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_low },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_max },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_min },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_optimum },
    { { HTML_JUL06 }, { HTML_DEC09 }, elem_meter, a_value },
    { { HTML_JAN10, REQUIRED }, { HTML_UNDEF }, elem_meter, a_value },
    STANDARD_HTML5_ATTRIBUTES (elem_meter),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfenced, a_close },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfenced, a_open },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfenced, a_separators },
    MATH3_PRES_ATTRIBUTES (elem_mfenced),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfrac, a_bevelled },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfrac, a_denomalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfrac, a_linethickness },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfrac, a_numalign },
    MATH3_PRES_ATTRIBUTES (elem_mfrac),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mglyph, a_alt },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mglyph, a_fontfamily },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_height },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mglyph, a_index },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_src },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_width },

    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_action },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_hidden },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_method },
    HTMLPLUS_ATTRIBUTES (elem_mh),

    MATH3_FONT_ATTRIBUTES (elem_mi),
    MATH3_PRES_ATTRIBUTES (elem_mi),

    MATH3_DEFS_ATTRIBUTES (elem_min),

    MATH3_DEFS_ATTRIBUTES (elem_minus),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, a_d },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, a_horizadvx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, a_vertadvy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, a_vertoriginx },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, a_vertoriginy },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_missingglyph),
    SVGx_PRES_ATTRIBUTES (elem_missingglyph),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_missingglyph),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mlabeledtr, a_columnalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mlabeledtr, a_groupalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mlabeledtr, a_rowalign },
    MATH3_PRES_ATTRIBUTES (elem_mlabeledtr),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_mlongdiv, a_align },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mlongdiv, a_charalign },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mlongdiv, a_charspacing },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mlongdiv, a_longdivstyle },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mlongdiv, a_stackalign },
    MATH3_PRES_ATTRIBUTES (elem_mlongdiv),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mmultiscripts, a_subscriptshift },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mmultiscripts, a_superscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_mmultiscripts),

    MATH3_LINEINDENT_ATTRIBUTES (elem_mn),
    MATH3_FONT_ATTRIBUTES (elem_mn),
    MATH3_PRES_ATTRIBUTES (elem_mn),

    MATH3_LINEINDENT_ATTRIBUTES (elem_mo),
    MATH3_FONT_ATTRIBUTES (elem_mo),
    MATH_OPINFO_ATTRIBUTES (elem_mo),
    MATH3_PRES_ATTRIBUTES (elem_mo),

    MATH3_DEFS_ATTRIBUTES (elem_mode),

    MATH3_DEFS_ATTRIBUTES (elem_moment),

    MATH3_DEFS_ATTRIBUTES (elem_momentabout),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mover, a_accent },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_mover, a_align },
    MATH3_PRES_ATTRIBUTES (elem_mover),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mpadded, a_lspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mpadded, a_voffset },
    MATH_SIZEINFO_ATTRIBUTES (elem_mpadded),
    MATH3_PRES_ATTRIBUTES (elem_mpadded),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_mpath, a_externalresourcesrequired },
    SVG11_XLINK_ATTRIBUTES (elem_mpath),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_mpath),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_mpath),

    MATH3_PRES_ATTRIBUTES (elem_mphantom),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mprescripts, a_xmlns },

    MATH3_PRES_ATTRIBUTES (elem_mroot),

    MATH3_PRES_ATTRIBUTES (elem_mrow),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ms, a_lquote },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ms, a_rquote },
    MATH3_FONT_ATTRIBUTES (elem_ms),
    MATH3_PRES_ATTRIBUTES (elem_ms),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_crossout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_location },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_scriptsizemultiplier },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_position },
    MATH3_PRES_ATTRIBUTES (elem_mscarries),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarry, a_crossout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarry, a_location },
    MATH3_PRES_ATTRIBUTES (elem_mscarry),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_msgroup, a_position },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msgroup, a_shift },
    MATH3_PRES_ATTRIBUTES (elem_msgroup),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_leftoverhang },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_length },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_mslinethickness },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_position },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_position },
    MATH3_PRES_ATTRIBUTES (elem_msline),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mspace, a_linebreak },
    MATH3_TOKEN_ATTRIBUTES (elem_mspace),
    MATH3_LINEINDENT_ATTRIBUTES (elem_mspace),
    MATH_SIZEINFO_ATTRIBUTES (elem_mspace),
    MATH3_PRES_ATTRIBUTES (elem_mspace),

    MATH3_PRES_ATTRIBUTES (elem_msqrt),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_msrow, a_position },
    MATH3_PRES_ATTRIBUTES (elem_msrow),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_align },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_charalign },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_charspacing },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_stackalign },
    MATH3_PRES_ATTRIBUTES (elem_mstack),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_accentunder },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_background },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_bevelled },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_charalign },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_charspacing },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_close },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_columnspan },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_crossout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_decimalpoint },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_denomalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_depth },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_edge },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_height },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_infixlinebreakstyle },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_leftoverhang },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_length },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_linethickness },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_location },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_longdivstyle },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_lquote },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_mediummathspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_mslinethickness },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_notation },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_numalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_open },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_position },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_rightoverhang },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_rowspan },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_rquote },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_scriptlevel },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_scriptminsize },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_scriptsizemultiplier },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_selection },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_separators },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_shift },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_stackalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_subscriptshift },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_superscriptshift },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_thickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_thinmathspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstyle, a_valign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_verythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_verythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_veryverythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_veryverythinmathspace },
    MATH3_LINEINDENT_ATTRIBUTES (elem_mstyle),
    MATH3_FONT_ATTRIBUTES (elem_mstyle),
    MATH_OPINFO_ATTRIBUTES (elem_mstyle),
    MATH3_TABLE_ATTRIBUTES (elem_mstyle),
    MATH3_PRES_ATTRIBUTES (elem_mstyle),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msub, a_subscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msub),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msubsup, a_subscriptshift },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msubsup, a_superscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msubsup),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msup, a_superscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msup),

    MATH3_TABLE_ATTRIBUTES (elem_mtable),
    MATH3_PRES_ATTRIBUTES (elem_mtable),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, a_columnalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, a_columnspan },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, a_groupalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, a_rowalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, a_rowspan },
    MATH3_PRES_ATTRIBUTES (elem_mtd),

    MATH3_FONT_ATTRIBUTES (elem_mtext),
    MATH3_PRES_ATTRIBUTES (elem_mtext),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtr, a_columnalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtr, a_groupalign },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtr, a_rowalign },
    MATH3_PRES_ATTRIBUTES (elem_mtr),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_munder, a_accentunder },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_munder, a_align },
    MATH3_PRES_ATTRIBUTES (elem_munder),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_munderover, a_accent },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_munderover, a_accentunder },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_munderover, a_align },
    MATH3_PRES_ATTRIBUTES (elem_munderover),

    MATH3_DEFS_ATTRIBUTES (elem_naturalnumbers),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_nav, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_nav),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_navigation, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_navigation),

    MATH3_DEFS_ATTRIBUTES (elem_neq),

    { { HTML_JAN08 }, { HTML_DEC08 }, elem_nest, a_filter },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_nest, a_mode },
    STANDARD_HTML5_ATTRIBUTES (elem_nest),

    { { HTML_TAGS }, { HTML_1_0 }, elem_nextid, a_n },
    { { HTML_1_0, REQUIRED }, { HTML_3_0 }, elem_nextid, a_n },

    XHTML2_ATTRIBUTES (elem_nl),

    COMMON_HTML4_ATTRIBUTES (elem_noframes),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_none, a_xmlns },

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_noscript),

    MATH3_DEFS_ATTRIBUTES (elem_not),

    { { HTML_3_0 }, { HTML_3_0 }, elem_note, a_clear },
    { { HTML_PLUS, HV_NOT2 }, { HTML_PLUS }, elem_note, a_role },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_note, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_note, a_md },
    HTMLPLUS_ATTRIBUTES (elem_note),
    HTML3_CLID_ATTRIBUTES (elem_note),

    MATH3_DEFS_ATTRIBUTES (elem_notanumber),

    MATH3_DEFS_ATTRIBUTES (elem_notin),

    MATH3_DEFS_ATTRIBUTES (elem_notprsubset),

    MATH3_DEFS_ATTRIBUTES (elem_notsubset),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_archive },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_align },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_border },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_classid },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_codebase },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_codetype },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_data },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_datasrc },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_declare },
    { { HTML_JAN09, HV_NOT53 }, { HTML_5_2 }, elem_object, a_form },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_height },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_hspace },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_name },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_object, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_standby },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_type },
    { { HTML_JAN11 }, { HTML_JUN19 }, elem_object, a_typemustmatch },
    { { HTML_4_0, HV_NOT5123 }, { HTML_MAR21 }, elem_object, a_usemap },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_vspace },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_width },
    HTML4_FORM_ATTRIBUTES (elem_object),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_object),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_ol, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_clear },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ol, a_compact },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_continue },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_ol, a_reversed },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_seqnum },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ol, a_type },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_ol, a_type },
    { { HTML_3_2, HV_DEPRECATED4 }, { HTML_UNDEF }, elem_ol, a_start },
    HTMLPLUS_ATTRIBUTES (elem_ol),
    HTML23_CLID_ATTRIBUTES (elem_ol),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ol),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_optgroup, a_disabled },
    { { HTML_4_0, REQUIRED }, { HTML_UNDEF }, elem_optgroup, a_label },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_optgroup),

    { { HTML_JAN05 }, { HTML_DEC05 }, elem_option, a_command },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { HTML_UNDEF }, elem_option, a_disabled },
    { { HTML_3_0 }, { HTML_3_0 }, elem_option, a_error },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_option, a_label },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_option, a_selected },
    { { HTML_3_0 }, { HTML_3_0 }, elem_option, a_shape },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_option, a_value },
    HTML23_CLID_ATTRIBUTES (elem_option),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_option),

    MATH3_DEFS_ATTRIBUTES (elem_or),

    MATH3_STANDARD_ATTRIBUTES (elem_otherwise),

    MATH3_DEFS_ATTRIBUTES (elem_outerproduct),

    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_for },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_form },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_output),

    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_imagemap },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_md },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_overlay, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_units },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_width },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_x },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_y },

    { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_2070 }, { XHTML_2_0 }, elem_p, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_p, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_p, a_nowrap },
    HTMLPLUS_ATTRIBUTES (elem_p),
    HTML23_CLID_ATTRIBUTES (elem_p),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_p),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_id },
    { { HTML_3_2, REQUIRED }, { HTML_UNDEF }, elem_param, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_type },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_param, a_value },
    { { HTML_JAN05, REQUIRED }, { HTML_UNDEF }, elem_param, a_value },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_param, a_valuetype },
    HTML4_ATTRIBUTES_BASE (elem_param),
    EXTRA_HTML5_ATTRIBUTES (elem_param),

    MATH3_DEFS_ATTRIBUTES (elem_partialdiff),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_path, a_d },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_path, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_path, a_flatness },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_path, a_nominallength },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_path, a_pathlength },
    SVG10_G_ATTRIBUTES(elem_path),
    SVGx_CONDPROC_ATTRIBUTES (elem_path),
    SVG11_GREV_ATTRIBUTES (elem_path),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_path),
    SVGx_PRES_ATTRIBUTES (elem_path),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_path),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, a_patterncontentunits },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_pattern, a_patterntransform },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_pattern, a_pattern_units },
    { { HTML_4_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, a_patternunits },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, a_viewbox },
    SVG10_BOX_ATTRIBUTES (elem_pattern),
    SVG10_FIT_ATTRIBUTES (elem_pattern),
    SVG10_REF_XY_ATTRIBUTES (elem_pattern),
    SVGx_CONDPROC_ATTRIBUTES (elem_pattern),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_pattern),
    SVG11_XLINK_ATTRIBUTES (elem_pattern),
    SVGx_PRES_ATTRIBUTES (elem_pattern),
    STANDARD_HTML5_ATTRIBUTES (elem_pattern),

    HTMLPLUS_ATTRIBUTES (elem_person),
    HTML23_CLID_ATTRIBUTES (elem_person),

    MATH3_DEFS_ATTRIBUTES (elem_pi),

    STANDARD_HTML5_ATTRIBUTES (elem_picture),

    MATH3_STANDARD_ATTRIBUTES (elem_piece),

    MATH3_STANDARD_ATTRIBUTES (elem_piecewise),

    MATH3_DEFS_ATTRIBUTES (elem_plus),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_polygon, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_polygon, a_points },
    SVG10_G_ATTRIBUTES (elem_polygon),
    SVG11_GREV_ATTRIBUTES (elem_polygon),
    SVGx_CONDPROC_ATTRIBUTES (elem_polygon),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_polygon),
    SVGx_PRES_ATTRIBUTES (elem_polygon),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_polygon),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_polyline, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_polyline, a_points },
    SVG10_G_ATTRIBUTES (elem_polyline),
    SVG11_GREV_ATTRIBUTES (elem_polyline),
    SVGx_CONDPROC_ATTRIBUTES (elem_polyline),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_polyline),
    SVGx_PRES_ATTRIBUTES (elem_polyline),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_polyline),

    MATH3_DEFS_ATTRIBUTES (elem_power),

    { { HTML_3_0 }, { HTML_3_0 }, elem_pre, a_clear },
    { { HTML_2_0, HV_NOT30, HE_MOZILLA | HE_NETSCAPE }, { HTML_3_2 }, elem_pre, a_cols },
    { { HTML_1_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_pre, a_width },
    { { HTML_2_0, 0, HE_MOZILLA | HV_NOT30 }, { HTML_UNDEF }, elem_pre, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_pre),
    HTML23_CLID_ATTRIBUTES (elem_pre),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_pre),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_prefetch),

    XHTML2_ATTRIBUTES (elem_preventdefault),

    MATH3_DEFS_ATTRIBUTES (elem_primes),

    MATH3_DEFS_ATTRIBUTES (elem_product),

    { { HTML_JAN10 }, { HTML_JUN11 }, elem_progress, a_form },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, a_max },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, a_value },
    STANDARD_HTML5_ATTRIBUTES (elem_progress),

    MATH3_DEFS_ATTRIBUTES (elem_prsubset),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_q, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_q, a_cite },
    HTMLPLUS_ATTRIBUTES (elem_q),
    HTML23_CLID_ATTRIBUTES (elem_q),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_q),

    HTMLPLUS_ATTRIBUTES (elem_quote),

    MATH3_DEFS_ATTRIBUTES (elem_quotient),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_radialgradient, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, a_cx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, a_cy },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, a_fx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, a_fy },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, a_r },
    SVG10_GRAD_ATTRIBUTES (elem_radialgradient),
    SVG11_XLINK_ATTRIBUTES (elem_radialgradient),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_radialgradient),
    SVGx_PRES_ATTRIBUTES (elem_radialgradient),
    STANDARD_HTML5_ATTRIBUTES (elem_radialgradient),

    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_range, a_from },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_range, a_until },
    HTML_CID_ATTRIBUTES (elem_range, MAJOR_3_0, MINOR_3_0, MAJOR_3_0, MINOR_3_0),

    MATH3_DEFS_ATTRIBUTES (elem_rationals),

    STANDARD_HTML5_ATTRIBUTES (elem_rb),

    MATH3_DEFS_ATTRIBUTES (elem_real),

    MATH3_DEFS_ATTRIBUTES (elem_reals),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_rect, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_rect, a_rx },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_rect, a_ry },
    SVG10_BOX_ATTRIBUTES (elem_rect),
    SVG10_G_ATTRIBUTES (elem_rect),
    SVG11_GREV_ATTRIBUTES (elem_rect),
    SVGx_CONDPROC_ATTRIBUTES (elem_rect),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_rect),
    SVGx_PRES_ATTRIBUTES (elem_rect),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rect),

    MATH2_STANDARD_ATTRIBUTES (elem_reln),

    MATH3_DEFS_ATTRIBUTES (elem_rem),

    HTMLPLUS_ATTRIBUTES (elem_removed),

    XHTML2_ATTRIBUTES (elem_removeeventlistener),

    { { HTML_PLUS }, { HTML_PLUS }, elem_render, a_style },
    { { HTML_PLUS }, { HTML_PLUS }, elem_render, a_tag },
    HTMLPLUS_ATTRIBUTES (elem_render),

    HTML3_CLID_ATTRIBUTES (elem_root),
    MATH3_DEFS_ATTRIBUTES (elem_root),

    STANDARD_HTML5_ATTRIBUTES (elem_rp),

    STANDARD_HTML5_ATTRIBUTES (elem_rt),

    STANDARD_HTML5_ATTRIBUTES (elem_rtc),

    STANDARD_HTML5_ATTRIBUTES (elem_ruby),

    { { HTML_JAN08 }, { HTML_DEC08 }, elem_rule, a_condition },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_rule, a_mode },
    STANDARD_HTML5_ATTRIBUTES (elem_rule),

    HTMLPLUS_ATTRIBUTES (elem_s),
    HTML3_CLID_ATTRIBUTES (elem_s),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_s),

    HTMLPLUS_ATTRIBUTES (elem_samp),
    HTML23_CLID_ATTRIBUTES (elem_samp),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_samp),

    MATH3_DEFS_ATTRIBUTES (elem_scalarproduct),

    { { HTML_JUL06 }, { HTML_UNDEF }, elem_script, a_async },
    { { HTML_JUL08 }, { HTML_JUN17 }, elem_script, a_charset },
    { { HTML_5_2, HV_W3 }, { HTML_5_2 }, elem_script, a_charset },
    { { HTML_JAN13 }, { HTML_UNDEF }, elem_script, a_crossorigin },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_script, a_defer },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_script, a_defer },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_script, a_event },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_script, a_externalresourcesrequired },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_script, a_implements },
    { { HTML_JAN17, HV_NOT52 }, { HTML_UNDEF }, elem_script, a_integrity },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_script, a_language },
    { { HTML_JUL17, HV_NOT52 }, { HTML_UNDEF }, elem_script, a_nomodule },
    { { HTML_JAN16 }, { HTML_JUN17 }, elem_script, a_numberonce },
    { { HTML_JUL18 }, { HTML_UNDEF }, elem_script, a_referrerpolicy },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_script, a_src },
    { { HTML_4_0, REQUIRED }, { XHTML_2_0 }, elem_script, a_type },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_script, a_type },
    SVG10_REPL_ATTRIBUTES (elem_script),
    SVG11_XLINK_ATTRIBUTES (elem_script),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_script),
    STANDARD_HTML5_ATTRIBUTES (elem_script),

    MATH3_DEFS_ATTRIBUTES (elem_sdev),

    MATH3_DEFS_ATTRIBUTES (elem_sec),

    MATH3_DEFS_ATTRIBUTES (elem_sech),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_section, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_section, a_cite },
    STANDARD_HTML5_ATTRIBUTES (elem_section),

    { { HTML_3_0 }, { HTML_3_0 }, elem_select, a_align },
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

    MATH3_DEFS_ATTRIBUTES (elem_selector),

    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_cd },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_definitionurl },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_encoding },
    { { HTML_5_2, 0, MATH_3_4 }, { HTML_UNDEF }, elem_semantics, a_name },
    MATH3_DEFS_ATTRIBUTES (elem_semantics),

    { { XHTML_1_0, 0, HE_MATH_1 | HE_MATH_2 }, { HTML_UNDEF }, elem_sep, a_xmlns },

    XHTML2_ATTRIBUTES (elem_separator),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_set, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_set, a_to },
    { { XHTML_1_0, 0, HE_MATH_2 }, { HTML_UNDEF }, elem_set, a_type },
    SVG11_ANAT_ATTRIBUTES (elem_set),
    SVG11_ANEV_ATTRIBUTES (elem_set),
    SVG11_ANTIME_ATTRIBUTES (elem_set),
    SVG11_XLINK_ATTRIBUTES (elem_set),
    SVGx_CONDPROC_ATTRIBUTES (elem_set),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_set),
    MATH3_STANDARD_ATTRIBUTES (elem_set),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_set),

    MATH3_DEFS_ATTRIBUTES (elem_setdiff),

    STANDARD_HTML5_ATTRIBUTES (elem_shadow),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_share, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_share),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_sidebar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_sidebar),

    MATH3_DEFS_ATTRIBUTES (elem_sin),

    MATH3_DEFS_ATTRIBUTES (elem_sinh),

    { { HTML_JUL16, HV_WHATWG }, { HTML_UNDEF }, elem_slot, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_slot),

    HTML3_CLID_ATTRIBUTES (elem_small),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_small),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_solidcolour),

    { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_height },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_media },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_sizes },
    { { HTML_JUL07, REQUIRED }, { HTML_JUN14 }, elem_source, a_src },
    { { HTML_JUL14 }, { HTML_UNDEF }, elem_source, a_src },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_source, a_srcset },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_source, a_type },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_source, a_width },
    STANDARD_HTML5_ATTRIBUTES (elem_source),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_span, a_datasrc },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_span, a_align },
    HTML2_CLID_ATTRIBUTES (elem_span),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_span),

    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_spot, a_id },

    HTML3_CLID_ATTRIBUTES (elem_sqrt),

    { { HTML_4_0, 0, HE_SVG_1_0 | REQUIRED }, { HTML_UNDEF }, elem_stop, a_offset },
    SVGx_PRES_ATTRIBUTES (elem_stop),
    STANDARD_HTML5_ATTRIBUTES (elem_stop),

    XHTML2_ATTRIBUTES (elem_stoppropagation),

    COMMON_HTML4_ATTRIBUTES (elem_strike),

    HTMLPLUS_ATTRIBUTES (elem_strong),
    HTML23_CLID_ATTRIBUTES (elem_strong),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_strong),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_style, a_disabled },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_style, a_media },
    { { HTML_JAN16 }, { HTML_DEC17 }, elem_style, a_numberonce },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_style, a_notation },
    { { HTML_4_0, 0, HE_CHROME }, { XHTML_2_0 }, elem_style, a_scoped },
    { { HTML_JUN06 }, { HTML_DEC15 }, elem_style, a_scoped },
    { { HTML_4_0 }, { HTML_DEC17 }, elem_style, a_type },
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_style, HTML_2005, 0),
    HTML4_STANDARD_CIST_ATTRIBUTES (elem_style, HTML_2005, 0),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_style),
    EXTRA_HTML5_ATTRIBUTES (elem_style),

    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sub),
    HTML23_CLID_ATTRIBUTES (elem_sub),
    STANDARD_HTML5_ATTRIBUTES (elem_sub),

    MATH3_DEFS_ATTRIBUTES (elem_subset),

    MATH3_DEFS_ATTRIBUTES (elem_sum),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_summary),

    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, a_align },
    HTMLPLUS_ATTRIBUTES (elem_sup),
    HTML23_CLID_ATTRIBUTES (elem_sup),
    STANDARD_HTML5_ATTRIBUTES (elem_sup),

    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_svg, a_allow_zoom_pan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, a_baseprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, a_externalresourcesrequired },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_svg, a_onzoom },
    { { HTML_4_0, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, a_version },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, a_viewbox },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_svg, a_xmlns },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, a_zoomandpan },
    SVG10_BOX_ATTRIBUTES (elem_svg),
    SVG10_FIT_ATTRIBUTES (elem_svg),
    SVG10_G_ATTRIBUTES (elem_svg),
    SVG11_GREV_ATTRIBUTES (elem_svg),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_svg),
    SVGx_CONDPROC_ATTRIBUTES (elem_svg),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_svg),
    SVGx_PRES_ATTRIBUTES (elem_svg),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_svg),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_switch, a_externalresourcesrequired },
    SVG10_G_ATTRIBUTES (elem_switch),
    SVGx_CONDPROC_ATTRIBUTES (elem_switch),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_switch),
    SVG11_GREV_ATTRIBUTES (elem_switch),
    SVGx_PRES_ATTRIBUTES (elem_switch),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_switch),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, a_preserveaspectratio },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_symbol, a_orient },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_symbol, a_markerheight },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_symbol, a_markerunits },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_symbol, a_markerwidth },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, a_viewbox },
    SVG10_BOX_ATTRIBUTES (elem_symbol),
    SVG10_FIT_ATTRIBUTES (elem_symbol),
    SVG10_REF_XY_ATTRIBUTES (elem_symbol),
    SVG11_GREV_ATTRIBUTES (elem_symbol),
    SVGx_CONDPROC_ATTRIBUTES (elem_symbol),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_symbol),
    SVGx_PRES_ATTRIBUTES (elem_symbol),
    STANDARD_HTML5_ATTRIBUTES (elem_symbol),

    { { HTML_3_0 }, { HTML_3_0 }, elem_t, a_class },
    { { HTML_JAN06 }, { HTML_JUN06 }, elem_t, a_datetime },
    STANDARD_HTML5_ATTRIBUTES (elem_t),

    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_tab, a_align },
    { { HTML_PLUS }, { HTML_PLUS }, elem_tab, a_at },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_id },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_indent },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tab, a_to },

    STANDARD_HTML5_ATTRIBUTES (elem_tabbox),

    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_table, a_align },
    { { HTML_3_2, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_table, a_background },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_table, a_bgcolour },
    { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_2070 }, { XHTML_2_0 }, elem_table, a_border },
    { { HTML_JUL11 }, { HTML_DEC12 }, elem_table, a_border },
    { { HTML_5_0, HV_W3 }, { HTML_5_3 }, elem_table, a_border },
    { { HTML_2_0, HV_NOT30 }, { XHTML_2_0 }, elem_table, a_cellspacing },
    { { HTML_2_0, HV_NOT30 }, { XHTML_2_0 }, elem_table, a_cellpadding },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_clear },
    { { HTML_2_0 }, { HTML_3_0 }, elem_table, a_cols },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_colspec },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_datasrc },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_dp },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_table, a_frame },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_table, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_noflow },
    { { HTML_3_0 }, { HTML_3_0 }, elem_table, a_nowrap },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_table, a_rules },
    { { HTML_JAN13 }, { HTML_DEC15 }, elem_table, a_sortable },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_table, a_summary },
    { { HTML_JAN10 }, { HTML_JUN11 }, elem_table, a_summary },
    { { HTML_2_0 }, { HTML_3_0 }, elem_table, a_units },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_table, a_width },
    HTMLPLUS_ATTRIBUTES (elem_table),
    HTML23_CLID_ATTRIBUTES (elem_table),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_table),

    MATH3_DEFS_ATTRIBUTES (elem_tan),

    MATH3_DEFS_ATTRIBUTES (elem_tanh),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tbody, a_align },
    { { HTML_2_0, 0, HE_IE | HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3}, { XHTML_2_0 }, elem_tbody, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tbody, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tbody, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tbody),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tbody),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tbreak),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_abbr },
    { { HTML_PLUS, HV_DEPRECATED4 | HV_RFC_1942 }, { XHTML_2_0 }, elem_td, a_align },
    { { HTML_2_0 }, { HTML_3_0 }, elem_td, a_axes },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_td, a_axis },
    { { HTML_3_2, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_td, a_background },
    { { HTML_2_0, 0, HE_IE }, { HTML_2_0 }, elem_td, a_bgcolour },
    { { HTML_4_0, HV_DEPRECATED4, HE_IE }, { XHTML_2_0 }, elem_td, a_bgcolour },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_td, a_cell },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_td, a_char },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_char },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_td, a_charoff },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_charoff },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_td, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_td, a_dp },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_headers },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_td, a_headers },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_height },
    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_nowrap },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_td, a_rowspan },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_td, a_scope },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_td, a_valign },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_td, a_width },
    HTML23_CLID_ATTRIBUTES (elem_td),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_td),

    STANDARD_HTML5_ATTRIBUTES (elem_template),

    { { XHTML_1_0, 0, HE_MATH_2 }, { HTML_UNDEF }, elem_tendsto, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_tendsto),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_text, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_text, a_lengthadjust },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_text, a_rotate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_text, a_textlength },
    HTML3_CLID_ATTRIBUTES (elem_text),
    SVG10_XY_ATTRIBUTES(elem_text),
    SVG10_DXY_ATTRIBUTES (elem_text),
    SVG10_G_ATTRIBUTES(elem_text),
    SVG11_GREV_ATTRIBUTES (elem_text),
    SVGx_CONDPROC_ATTRIBUTES (elem_text),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_text),
    SVGx_PRES_ATTRIBUTES (elem_text),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_text),

    { { HTML_3_0 }, { HTML_3_0 }, elem_textarea, a_align },
    { { HTML_5_3 }, { HTML_5_3 }, elem_textarea, a_autocapitalise },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, elem_textarea, a_autocomplete },
    { { HTML_JAN09 }, { HTML_DEC19 }, elem_textarea, a_autofocus },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_cols },
    { { HTML_2_0, REQUIRED }, { XHTML_2_0 }, elem_textarea, a_cols },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_textarea, a_cols },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_datasrc },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_textarea, a_dirname },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { HTML_UNDEF }, elem_textarea, a_disabled },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_textarea, a_error },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_form },
    { { HTML_JAN13, HV_NOT52 | HV_NOT53 }, { HTML_DEC17 }, elem_textarea, a_inputmode },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_maxlength },
    { { HTML_JAN14 }, { HTML_UNDEF }, elem_textarea, a_minlength },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_name },
    { { HTML_2_0, REQUIRED }, { HTML_3_2 }, elem_textarea, a_name },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_textarea, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onchange },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onfocus },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_textarea, a_onselect },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_textarea, a_placeholder },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_textarea, a_readonly },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_required },
    { { HTML_PLUS }, { HTML_PLUS }, elem_textarea, a_rows },
    { { HTML_2_0, REQUIRED }, { XHTML_2_0 }, elem_textarea, a_rows },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_textarea, a_rows },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_textarea, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_textarea),
    HTML23_CLID_ATTRIBUTES (elem_textarea),
    HTML4_FORM_ATTRIBUTES (elem_textarea),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_textarea),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, a_method },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, a_spacing },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_textpath, a_spreadmethod },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, a_startoffset },
    SVG10_REPL_ATTRIBUTES(elem_textpath),
    SVG11_XLINK_ATTRIBUTES (elem_textpath),
    SVG11_GREV_ATTRIBUTES (elem_textpath),
    SVGx_CONDPROC_ATTRIBUTES (elem_textpath),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_textpath),
    SVGx_PRES_ATTRIBUTES (elem_textpath),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_textpath),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tfoot, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_tfoot, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tfoot, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tfoot, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_tfoot),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tfoot),

    { { HTML_4_0 }, { XHTML_2_0 }, elem_th, a_abbr },
    { { HTML_JAN13 }, { HTML_UNDEF }, elem_th, a_abbr },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_align },
    { { HTML_2_0 }, { HTML_3_0 }, elem_th, a_axes },
    { { HTML_2_0, HV_NOT32 }, { XHTML_2_0 }, elem_th, a_axis },
    { { HTML_2_0, 0, HE_IE }, { HTML_2_0 }, elem_th, a_bgcolour },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_bgcolour },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_char },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_charoff },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_th, a_colspan },
    { { HTML_3_0 }, { HTML_3_0 }, elem_th, a_dp },
    { { HTML_2_0, HV_NOT3 }, { XHTML_2_0 }, elem_th, a_headers },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_th, a_headers },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_height },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, a_lang },
    { { HTML_2_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_nowrap },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_th, a_rowspan },
    { { HTML_2_0, HV_NOT32 }, { HTML_UNDEF }, elem_th, a_scope },
    { { HTML_JAN13 }, { HTML_DEC15 }, elem_th, a_sorted },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_th, a_valign },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_th, a_width },
    HTML23_CLID_ATTRIBUTES (elem_th),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_th),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_thead, a_align },
    { { HTML_2_0, HV_NOT3 | HV_RFC_1942, HE_IE }, { XHTML_2_0 }, elem_thead, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_thead, a_charoff },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_thead, a_rowgroup },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_thead, a_valign },
    HTML2_CLID_ATTRIBUTES (elem_thead),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_thead),

    HTML3_CLID_ATTRIBUTES (elem_tilde),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_time, a_datetime },
    { { HTML_JAN10 }, { HTML_JUN12 }, elem_time, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_time),

    MATH3_DEFS_ATTRIBUTES (elem_times),

    HTMLPLUS_ATTRIBUTES (elem_title),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_title),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_title),

    { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_tr, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_tr, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_tr, a_charoff },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_dp },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tr, a_nowrap },
    { { HTML_5_2, HV_W3 }, { HTML_UNDEF }, elem_tr, a_row },
    { { HTML_2_0, HV_RFC_1942 }, { XHTML_2_0 }, elem_tr, a_valign },
    HTML23_CLID_ATTRIBUTES (elem_tr),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tr),

    { { HTML_JAN11 }, { HTML_UNDEF }, elem_track, a_default },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_kind },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_label },
    { { HTML_JUL10, REQUIRED }, { HTML_UNDEF }, elem_track, a_src },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_track, a_srclang },
    STANDARD_HTML5_ATTRIBUTES(elem_track),

    MATH3_DEFS_ATTRIBUTES (elem_transpose),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, a_externalresourcesrequired },
    SVG11_XLINK_ATTRIBUTES (elem_tref),
    SVG10_XY_ATTRIBUTES (elem_tref),
    SVG10_DXY_ATTRIBUTES (elem_tref),
    SVG10_REPL_ATTRIBUTES (elem_tref),
    SVG11_GREV_ATTRIBUTES (elem_tref),
    SVGx_CONDPROC_ATTRIBUTES (elem_tref),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_tref),
    SVGx_PRES_ATTRIBUTES (elem_tref),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tref),

    MATH3_DEFS_ATTRIBUTES (elem_true),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, a_lengthadjust },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, a_rotate },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_tspan, a_systemrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, a_textlength },
    SVG10_XY_ATTRIBUTES(elem_tspan),
    SVG10_DXY_ATTRIBUTES (elem_tspan),
    SVG10_REPL_ATTRIBUTES(elem_tspan),
    SVG11_GREV_ATTRIBUTES (elem_tspan),
    SVGx_CONDPROC_ATTRIBUTES (elem_tspan),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_tspan),
    SVGx_PRES_ATTRIBUTES (elem_tspan),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_tspan),

    HTMLPLUS_ATTRIBUTES (elem_tt),
    HTML23_CLID_ATTRIBUTES (elem_tt),

    HTMLPLUS_ATTRIBUTES (elem_u),
    HTML3_CLID_ATTRIBUTES (elem_u),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_u),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_ul, a_align },
    { { HTML_3_0, HV_NOT32 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_clear },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_compact },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_dingbat },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_plain },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_md },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_src },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_type },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_ul),
    HTML23_CLID_ATTRIBUTES (elem_ul),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ul),

    MATH3_DEFS_ATTRIBUTES (elem_union),

    MATH3_STANDARD_ATTRIBUTES (elem_uplimit),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_use, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_use, a_xlinkhref },
    SVG10_REPL_ATTRIBUTES(elem_use),
    SVG10_BOX_ATTRIBUTES(elem_use),
    SVG10_G_ATTRIBUTES(elem_use),
    SVG11_GREV_ATTRIBUTES (elem_use),
    SVGx_CONDPROC_ATTRIBUTES (elem_use),
    SVGx_XTRA_CORE_ATTRIBUTES (elem_use),
    SVGx_PRES_ATTRIBUTES (elem_use),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_use),

    HTMLPLUS_ATTRIBUTES (elem_var),
    HTML23_CLID_ATTRIBUTES (elem_var),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_var),

    MATH3_DEFS_ATTRIBUTES (elem_variance),

    HTML3_CLID_ATTRIBUTES (elem_vec),

    MATH3_STANDARD_ATTRIBUTES (elem_vector),

    MATH3_DEFS_ATTRIBUTES (elem_vectorproduct),

    { { HTML_JAN11 }, { HTML_JUN11 }, elem_video, a_audio },
    { { HTML_JUL09 }, { HTML_JUN10 }, elem_video, a_autobuffer },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_autopictureinpicture },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_autoplay },
    { { HTML_JUL07, 0, HE_MOZILLA | HE_OPERA }, { HTML_UNDEF }, elem_video, a_buffered },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_controls },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_controlslist },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_crossorigin },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_currenttime },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_disablepictureinpicture },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_video, a_disableremoteplayback },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_duration },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_end },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_height },
    { { HTML_JUL07, 0, HE_CHROME | HE_OPERA }, { HTML_UNDEF }, elem_video, a_intrinsicsize },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_video, a_loop },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopcount },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopend },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopstart },
    { { HTML_JUL11 }, { HTML_JUN16 }, elem_video, a_mediagroup },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_muted },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_video, a_playcount },
    { { HTML_JAN17, HV_NOT5W3 }, { HTML_UNDEF }, elem_video, a_playsinline },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_poster },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_video, a_preload },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_src },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_start },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_width },
    STANDARD_HTML5_ATTRIBUTES(elem_video),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, a_externalresourcesrequired },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, a_preserveaspectratio },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, a_viewbox },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, a_viewtarget },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, a_zoomandpan },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_view),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_view),

    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_vkern, a_g1 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_vkern, a_g2 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_vkern, a_k },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_vkern, a_u1 },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_vkern, a_u1 },
    SVGx_XTRA_CORE_ATTRIBUTES (elem_vkern),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_vkern),

    STANDARD_HTML5_ATTRIBUTES(elem_wbr),

    HTML23_CLID_ATTRIBUTES (elem_xmp),

    MATH3_DEFS_ATTRIBUTES (elem_xor)
};

typedef ::std::multimap < uint64_t, hav_t > avm_t;
avm_t avm;

inline uint64_t avm_key (const e_element tag, const e_attribute a)
{   return (static_cast < uint64_t > (tag) << 32) + static_cast < uint64_t > (a); }

void avm_init (nitpick& )
{   for (int index = 0; havt [index].tag_ != a_unknown; ++index)
        avm.insert (avm_t::value_type (avm_key (havt [index].tag_, havt [index].a_), havt [index])); }

bool is_invalid_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (avm_t::const_iterator i = avm.find (avm_key (tag, a)); i != avm.cend () && (i -> second.tag_ == tag) && (i -> second.a_ == a); ++i)
        if (may_apply (v, i -> second.first_, i -> second.last_)) return false;
    for (avm_t::const_iterator i = avm.find (avm_key (elem_undefined, a)); i != avm.cend () && (i -> second.tag_ == elem_undefined) && (i -> second.a_ == a); ++i)
        if (may_apply (v, i -> second.first_, i -> second.last_)) return false;
    return true; }

bool is_deprecated_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (avm_t::const_iterator i = avm.find (avm_key (tag, a)); i != avm.cend () && (i -> second.tag_ == tag) && (i -> second.a_ == a); ++i)
        if (may_apply (v, i -> second.first_, i -> second.last_)) return i -> second.first_.deprecated (v);
    for (avm_t::const_iterator i = avm.find (avm_key (elem_undefined, a)); i != avm.cend () && (i -> second.tag_ == elem_undefined) && (i -> second.a_ == a); ++i)
        if (may_apply (v, i -> second.first_, i -> second.last_)) return i -> second.first_.deprecated (v);
    return false; }

bool not_production_attribute (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && v.is_5 () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (avm_t::const_iterator i = avm.find (avm_key (tag, a)); i != avm.cend () && (i -> second.tag_ == tag) && (i -> second.a_ == a); ++i)
            if (may_apply (v, i -> second.first_, i -> second.last_)) return i -> second.first_.not_production ();
    return false; }

bool is_attribute_required (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (avm_t::const_iterator i = avm.find (avm_key (tag, a)); i != avm.cend () && (i -> second.tag_ == tag) && (i -> second.a_ == a); ++i)
            if (may_apply (v, i -> second.first_, i -> second.last_)) return i -> second.first_.required ();
    return false; }

bool is_attribute_rejected (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (avm_t::const_iterator i = avm.find (avm_key (tag, a)); i != avm.cend () && (i -> second.tag_ == tag) && (i -> second.a_ == a); ++i)
            if (may_apply (v, i -> second.first_, i -> second.last_)) return i -> second.first_.reject ();
    return false; }
