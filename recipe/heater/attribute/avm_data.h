/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "type/type.h"
#include "element/elem.h"

struct hav_t
{   html_version first_, last_;
    e_element tag_;
    e_attribute a_; };

extern hav_t havt_abc [], havt_defgh [], havt_ijkl [], havt_mnopqr [], havt_stuvwxyz [];

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
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onclick },\
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_12 }, { HTML_UNDEF }, ELEM, a_ondblclick }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_12 }, { HTML_UNDEF }, ELEM, a_onkeydown }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_12 }, { HTML_UNDEF }, ELEM, a_onkeypress }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_12 }, { HTML_UNDEF }, ELEM, a_onkeyup }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onmousedown }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onmousemove }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onmouseout }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onmouseover }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, ELEM, a_onmouseup }

#define HTML4_STANDARD_LANG_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_dir }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_lang }

#define HTML4_STANDARD_CI_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_class }, \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_class }, \
    { { MAJOR_FROM, MINOR_FROM }, { HTML_UNDEF }, ELEM, a_id }

#define HTML4_ARIA_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM, FLAG) \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaactivedescendant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaatomic }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaautocomplete }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariabusy }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariachecked }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariacontrols }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariadescribedby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariadisabled }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariadropeffect }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaexpanded }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaflowto }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariagrabbed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariahaspopup }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariahidden }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariainvalid }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_arialabel }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_arialabelledby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_arialevel }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_arialive }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariamultiline }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariamultiselectable }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaorientation }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaowns }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaposinset }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariapressed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariareadonly }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariarelevant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariarequired }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaselected }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariasetsize }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariasort }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariavaluemax }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariavaluemin }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariavaluenow }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariavaluetext }

#define ADDITIONAL_ARIA_ATTRIBUTES(ELEM) \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariacolcount }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariacolindex }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariacolspan }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariacurrent }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariadetails }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaerrormessage }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariamodal }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaplaceholder }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariaroledescription }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariarowcount }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariarowindex }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ariarowspan }

#define RDFA_SVG12_ATTRIBUTES(ELEM,FLAGS) \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_about }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_content }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_datatype }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_property }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_rel }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_resource }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_rev }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_typeof }

#define RDFA_STANDARD_ATTRIBUTES(ELEM) \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_about }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_content }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_datatype }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_inlist }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_prefix }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_property }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_rel }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_resource }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_rev }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_src }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_typeof }, \
    { { HTML_RDF10, 0, HE_RDF_1_0 | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_vocab }

#define SVG_ANIMATION_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onbegin }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onend }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_onload }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onrepeat }

#define SVG_ANIMATION_EVENT_ATTRIBUTES(ELEM) \
    SVG_ANIMATION_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_2)

#define SVG_CONDITIONAL_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_requiredextensions }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_requiredfeatures }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_requiredfonts }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_requiredformats }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_systemlanguage }

#define SVG_CONDITIONAL_ATTRIBUTES(ELEM) \
    SVG_CONDITIONAL_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG_BASE_ATTRIBUTES(ELEM) \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_role }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xmlbase }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_xmlid }

#define SVG_DOCUMENT_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onabort }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onerror }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onresize }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onscroll }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onunload }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onzoom }

#define SVG_DOCUMENT_EVENT_ATTRIBUTES(ELEM) \
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11)

#define SVG_GRAPHICAL_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_2 }, { HTML_UNDEF }, ELEM, a_onactivate }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_21 }, { HTML_UNDEF }, ELEM, a_onfocusin }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_21 }, { HTML_UNDEF }, ELEM, a_onfocusout }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_2 }, { HTML_UNDEF }, ELEM, a_onload }

#define SVG_GRAPHICAL_EVENT_ATTRIBUTES(ELEM) \
    SVG_GRAPHICAL_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_20)

#define SVG_COLOUR_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour_rendering }

#define SVG_CONTAINER_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_enable_background }

#define SVG_FILL_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_width }

#define SVG_FILTER_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation_filters }

#define SVG_FLOOD_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_flood_colour }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_flood_opacity }

#define SVG_FONT_ATTRIBUTES(ELEM) \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_font }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font_size_adjust }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font_stretch }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_weight }

#define SVG_GRAPHICS_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_clip_path }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_clip_rule }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_cursor }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_display }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_filter }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_image_rendering }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_mask }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_pointer_events }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_shape_rendering }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_rendering }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_visibility }

#define SVG_IMAGE_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_colour_profile }

#define SVG_LIGHTING_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_lighting_colour }

#define SVG_MARKER_ATTRIBUTES(ELEM) \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_marker }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_end }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_mid }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_start }

#define SVG_STOP_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_opacity }

#define SVG_TEXT_CONTENT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_alignmentbaseline }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_baselineshift }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_dominant_baseline }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_vertical }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_horizontal }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_kerning }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_letter_spacing }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_anchor }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_text_align }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_text_decoration }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_overflow }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_unicode_bidi }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_word_spacing }

#define SVG_TEXT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_writing_mode }

#define SVG_VIEWPORT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_clip }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_overflow }

#define SVG_PRESENTATION_ATTRIBUTES_12(ELEM) \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_audio_level }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_buffered_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_display_align }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focushighlight }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focusable }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_line_increment }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navdown }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navdownleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navdownright }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navnext }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navprev }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navright }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navup }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navupleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_navupright }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_colour }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_opacity }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_viewport_fill }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_viewport_fill_opacity }

#define SVG_PRESENTATION_ATTRIBUTES_20(ELEM) \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_paint_order }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_white_space }

#define SVG_PRESENTATION_ATTRIBUTES(ELEM) \
    SVG_COLOUR_ATTRIBUTES (ELEM), \
    SVG_CONTAINER_ATTRIBUTES (ELEM), \
    SVG_FILL_ATTRIBUTES (ELEM), \
    SVG_FILTER_ATTRIBUTES (ELEM), \
    SVG_FLOOD_ATTRIBUTES (ELEM), \
    SVG_FONT_ATTRIBUTES (ELEM), \
    SVG_GRAPHICS_ATTRIBUTES (ELEM), \
    SVG_IMAGE_ATTRIBUTES (ELEM), \
    SVG_LIGHTING_ATTRIBUTES (ELEM), \
    SVG_MARKER_ATTRIBUTES (ELEM), \
    SVG_STOP_ATTRIBUTES (ELEM), \
    SVG_TEXT_CONTENT_ATTRIBUTES (ELEM), \
    SVG_TEXT_ATTRIBUTES (ELEM), \
    SVG_VIEWPORT_ATTRIBUTES (ELEM), \
    SVG_PRESENTATION_ATTRIBUTES_12 (ELEM), \
    SVG_PRESENTATION_ATTRIBUTES_20 (ELEM)

#define SVG_REF_XY_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_refx }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_refy }

#define SVG_REF_XY_ATTRIBUTES(ELEM) \
    SVG_REF_XY_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_2)

#define SVG_XY_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_x }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_y }

#define SVG_XY_ATTRIBUTES(ELEM) \
    SVG_XY_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG_BOX_ATTRIBUTES_EX(ELEM,VER) \
    SVG_XY_ATTRIBUTES_EX (ELEM, VER), \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_height }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_width }

#define SVG_BOX_ATTRIBUTES(ELEM) \
    SVG_BOX_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG_LANGSPACE_ATTRIBUTES_10(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmllang }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmlspace }

#define SVG_XLINK_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkactuate }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkarcrole }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_xlinkhref }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkrole }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkshow }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_xlinktitle }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinktype }

#define SVG_XLINK_ATTRIBUTES(ELEM) \
    SVG_XLINK_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG10_DXY_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_dx }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_dy }

#define SVG10_COMP_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_amplitude }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_exponent }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_intercept }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_offset }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 | REQUIRED }, { HTML_UNDEF }, ELEM, a_type }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_slope }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 | HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_tablevalues }

#define SVG10_FILTER_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_in }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_nodeid }

#define SVG10_FIT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_preserveaspectratio }

#define SVG10_G_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_onselect }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_transform }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_systemrequired }

#define SVG10_GRAD_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_gradienttransform }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_gradientunits }

#define SVG10_REPL_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_actuate }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_href }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_show }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmllink }

#define SVG10_ANADD_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_accumulate }

#define SVG11_ANADD_ATTRIBUTES(ELEM) \
    { { HTML_SVG11, 0, HE_SVG_11_12_2 }, { HTML_UNDEF }, ELEM, a_additive }, \
    SVG10_ANADD_ATTRIBUTES(ELEM)

#define SVG11_ANAT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_attributename }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_attributetype }

#define SVG11_ANEV_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_onbegin }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_onend }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_onrepeat }

#define SVG11_ANTIME_ATTRIBUTES(ELEM) \
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_begin }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_dur }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_end }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_min }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_max }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_restart }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_repeatcount }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_repeatdur }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill }

#define SVG_ANVAL_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_by }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_calcmode }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_values }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_keysplines }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_keytimes }

#define SVG11_FILTER_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_height }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_result }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_width }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_x }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_y }

#define SVG12_CONDGRAPH_ATTRIBUTES(ELEM)

#define MATH1_STANDARD_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_MATH1, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_class }, \
    { { HTML_MATH1, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_id }, \
    { { HTML_MATH1, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_other }, \
    { { HTML_MATH1, 0, ( FLAGS | HE_MATH_1 ) }, { HTML_UNDEF }, ELEM, a_style }

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
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xlinkhref }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xlinktype }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xmlns }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_xref }

#define MATH2_STANDARD_ATTRIBUTES(ELEM) \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, 0)

#define MATH2_DEFS_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_MATH1, 0, ( FLAGS | HE_MATH_1_2 ) }, { HTML_UNDEF }, ELEM, a_definitionurl }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_encoding }, \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH2_DEFS_ATTRIBUTES(ELEM) \
    MATH2_DEFS_ATTRIBUTES_EX (ELEM, 0)

#define MATH2_FONT_ATTRIBUTES_EX(ELEM, FLAGS) \
    MATH1_FONT_ATTRIBUTES (ELEM), \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathbackground }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathcolour }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathsize }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_mathvariant }

#define MATH2_FONT_ATTRIBUTES(ELEM) \
    MATH2_FONT_ATTRIBUTES_EX (ELEM,0) \

#define MATH2_TABLE_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_columnwidth }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_minlabelspacing }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_side }, \
    { { HTML_MATH2, 0, ( FLAGS | HE_MATH_2 ) }, { HTML_UNDEF }, ELEM, a_width }, \
    MATH1_TABLE_ATTRIBUTES (ELEM)

#define MATH2_TABLE_ATTRIBUTES(ELEM) \
    MATH2_TABLE_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_STANDARD_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_MATH3, 0, ( FLAGS | HE_MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_href }, \
    MATH2_STANDARD_ATTRIBUTES_EX (ELEM, ( FLAGS | HE_MATH_3_4 ) )

#define MATH3_STANDARD_ATTRIBUTES(ELEM) \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_DEFS_ATTRIBUTES_EX(ELEM, FLAGS) \
    MATH2_DEFS_ATTRIBUTES_EX (ELEM, ( FLAGS | HE_MATH_3_4 ) ), \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH3_DEFS_ATTRIBUTES(ELEM) \
    MATH3_DEFS_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_FONT_ATTRIBUTES(ELEM) \
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, ELEM, a_dir }, \
    MATH2_FONT_ATTRIBUTES_EX (ELEM, HE_MATH_3_4)

#define MATH3_TABLE_ATTRIBUTES(ELEM) \
    MATH2_TABLE_ATTRIBUTES_EX (ELEM, HE_MATH_3_4)

#define MATH3_PRES_ATTRIBUTES_EX(ELEM, FLAGS) \
    { { HTML_MATH3, 0, ( FLAGS | HE_MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_mathbackground }, \
    { { HTML_MATH3, 0, ( FLAGS | HE_MATH_3_4 ) }, { HTML_UNDEF }, ELEM, a_mathcolour }, \
    MATH3_STANDARD_ATTRIBUTES_EX (ELEM, FLAGS)

#define MATH3_PRES_ATTRIBUTES(ELEM) \
    MATH3_PRES_ATTRIBUTES_EX (ELEM, 0)

#define MATH3_TOKEN_ATTRIBUTES(ELEM) \
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, ELEM, a_dir }, \
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, ELEM, a_mathsize }, \
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, ELEM, a_mathvariant }

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

#define XHTML1_STANDARD_ATTRIBUTES(ELEM) \
    RDFA_STANDARD_ATTRIBUTES (ELEM), \
    { { XHTML_1_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_xmlns }, \
    { { HTML_JAN07, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_xmlns }, \
    { { XHTML_1_0, 0, HE_NOT_SVG_10_12 }, { HTML_UNDEF }, ELEM, a_xmllang }

#define XHTML2_COMMON_ATTRIBUTES(ELEM) \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_about }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_content }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_datatype }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_property }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_rel }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_resource }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_rev }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_typeof }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_cite }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11 }, { XHTML_2_0 }, ELEM, a_class }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_coords }, \
    { { HTML_SVG12, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_defaultaction }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_dir }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_edit }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_event }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_eventtarget }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_encoding }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_function }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_handler }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_href }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_hreflang }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_hrefmedia }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_hreftype }, \
    { { XHTML_2_0 }, { XHTML_2_0 }, ELEM, a_id }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_ismap }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_itstranslate }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_layout }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_media }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_nextfocus }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_observer }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_phase }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_prevfocus }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_propagate }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_role }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_shape }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_srctype }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_1 }, { XHTML_2_0 }, ELEM, a_style }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_target }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_title }, \
    { { XHTML_2_0, 0, HE_NOT_SVG }, { XHTML_2_0 }, ELEM, a_usemap }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_20 }, { XHTML_2_0 }, ELEM, a_xmlbase }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { XHTML_2_0 }, ELEM, a_xmlid }

#define XHTML2_STANDARD_ATTRIBUTES(ELEM) \
    XHTML2_COMMON_ATTRIBUTES(ELEM), \
    XHTML1_STANDARD_ATTRIBUTES(ELEM)

#define XHTML2_ATTRIBUTES(ELEM) \
    XHTML2_STANDARD_ATTRIBUTES(ELEM)

#define HTML4_STANDARD_CIS_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_CI_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    { { MAJOR_FROM, MINOR_FROM, HV_NOTPROD, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_style }

#define HTML4_STANDARD_CIST_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_CIS_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    { { MAJOR_FROM, MINOR_FROM, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_title }

#define HTML4_STANDARD_TSL_ATTRIBUTES(ELEM, MAJOR_FROM, MINOR_FROM) \
    HTML4_STANDARD_LANG_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM), \
    HTML4_STANDARD_CIST_ATTRIBUTES (ELEM, MAJOR_FROM, MINOR_FROM)

#define HTML4_ATTRIBUTES_BASE(ELEM) \
    HTML4_STANDARD_TSL_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0), \
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0), \
    HTML4_ARIA_ATTRIBUTES (ELEM, MAJOR_4_0, MINOR_4_0, HV_ARIA)

#define COMMON_HTML4_ATTRIBUTES(ELEM) \
    HTML4_ATTRIBUTES_BASE (ELEM), \
    XHTML2_STANDARD_ATTRIBUTES (ELEM)

#define HTML4_FORM_ATTRIBUTES_V(ELEM) \
    { { HTML_4_0, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_accesskey }, \
    { { HTML_4_0, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_tabindex }

#define HTML4_FORM_ATTRIBUTES(ELEM) \
    HTML4_FORM_ATTRIBUTES_V (ELEM)

#define EXTRA_HTML5_ATTRIBUTES(ELEM) \
    ADDITIONAL_ARIA_ATTRIBUTES(ELEM), \
    { { HTML_5_0, HV_W3, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_acceptcharset }, \
    { { HTML_JAN18, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_autocapitalise }, \
    { { HTML_JAN20, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_autofocus }, \
    { { HTML_JAN07, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_contenteditable }, \
    { { HTML_JAN06, HV_NOT50 | HV_NOT52 | HV_NOT53, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_contextmenu }, \
    { { HTML_JAN07, HV_NOT50, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_draggable }, \
    { { HTML_JAN11, HV_NOT50, HE_NOT_SVG }, { HTML_DEC16, HV_NOT52 | HV_NOT53 }, ELEM, a_dropzone }, \
    { { HTML_JUL18, HV_NOT53, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_enterkeyhint }, \
    { { HTML_5_0, HV_W3, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_generator_unable }, \
    { { HTML_JAN09, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_hidden }, \
    { { HTML_JUL12, 0, HE_NOT_SVG }, { HTML_JUN14 }, ELEM, a_inert }, \
    { { HTML_JUL18, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_inputmode }, \
    { { HTML_JUL07, 0, HE_NOT_SVG }, { HTML_DEC08 }, ELEM, a_irrelevant }, \
    { { HTML_JUL16, HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, ELEM, a_is }, \
    { { HTML_JUL09, 0, HE_NOT_SVG }, { HTML_DEC09 }, ELEM, a_item }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemid }, \
    { { HTML_JUL09, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemprop }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemref }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemscope }, \
    { { HTML_JAN10, HV_WHATWG, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_itemtype }, \
    { { HTML_5_2, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_numberonce }, \
    { { HTML_JUL14, HV_WHATWG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onautocomplete }, \
    { { HTML_JUL14, HV_WHATWG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onautocompleteerror }, \
    { { HTML_JAN17, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onauxclick }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onbeforeunload }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onblur }, \
    { { HTML_JUL12, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncancel }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncanplay }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncanplaythrough }, \
    { { HTML_JAN05, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onchange }, \
    { { HTML_JUL12, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onclose }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 | HV_NOT52 | HV_NOT53 }, { HTML_UNDEF }, ELEM, a_oncontextmenu }, \
    { { HTML_5_1, 0, HE_NOT_SVG_1 }, { HTML_5_1 }, ELEM, a_oncopy }, \
    { { HTML_JUL19, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncopy }, \
    { { HTML_JUL10, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncuechange }, \
    { { HTML_5_1, 0, HE_NOT_SVG_1 }, { HTML_5_1 }, ELEM, a_oncut }, \
    { { HTML_JUL19, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oncut }, \
    { { HTML_JAN05, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_datawild }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondrag }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondragend }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondragenter }, \
    { { HTML_JUL13, 0, HE_NOT_SVG_1 }, { HTML_DEC20 }, ELEM, a_ondragexit }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondragleave }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondragover }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondragstart }, \
    { { HTML_JUL07, HV_NOT50, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondrop }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ondurationchange }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onemptied }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onended }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onerror }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onfocus }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_JUN11 }, ELEM, a_onformchange }, \
    { { HTML_JUL19, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onformdata }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_JUN11 }, ELEM, a_onforminput }, \
    { { HTML_JAN09, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onhashchange }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oninput }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_oninvalid }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onload }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onloadeddata }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onloadedmetadata }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onloadstart }, \
    { { HTML_JUL16, 0, HE_NOT_SVG_1 }, { HTML_5_3 }, ELEM, a_onloadend }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onmessage }, \
    { { HTML_JUL13, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onmouseenter }, \
    { { HTML_JUL13, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onmouseleave }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_JUN15 }, ELEM, a_onmousewheel }, \
    { { HTML_5_1, 0, HE_NOT_SVG_1 }, { HTML_5_1 }, ELEM, a_onpaste }, \
    { { HTML_JUL19, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onpaste }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onpause }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onplay }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onplaying }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onprogress }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onratechange }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_DEC11 }, ELEM, a_onreadystatechange }, \
    { { HTML_JAN11, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onreset }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onresize }, \
    { { HTML_JAN14, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onresize }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onscroll }, \
    { { HTML_JAN18, HV_NOT53, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onsecuritypolicyviolation }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onseeking }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onselect }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_JUN17 }, ELEM, a_onshow }, \
    { { HTML_JUL20, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onslotchange }, \
    { { HTML_JAN13, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onsort }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onsought }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onstalled }, \
    { { HTML_JUL08, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onstorage }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onsubmit }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onsuspend }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ontimeupdate }, \
    { { HTML_JAN14, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_ontoggle }, \
    { { HTML_JUL07, 0, HE_NOT_SVG_1 }, { HTML_JUN09 }, ELEM, a_onunload }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_JUN13 }, ELEM, a_onvolumechange }, \
    { { HTML_JUL09, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onwaiting }, \
    { { HTML_JUL15, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_onwheel }, \
    { { HTML_JAN08, 0, HE_NOT_SVG }, { HTML_DEC08 }, ELEM, a_ref }, \
    { { HTML_JAN08, 0, HE_NOT_SVG }, { HTML_DEC08 }, ELEM, a_registrationmark }, \
    { { HTML_JAN10, 0, HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_role }, \
    { { HTML_JUL16, HV_NOT51 | HV_NOT52 | HV_NOT53, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_slot }, \
    { { HTML_JUL09, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_spellcheck }, \
    { { HTML_JUL09, 0, HE_NOT_SVG }, { HTML_DEC09 }, ELEM, a_subject }, \
    { { HTML_JAN08, 0, HE_NOT_SVG }, { HTML_DEC08 }, ELEM, a_template }, \
    { { HTML_JUL12, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_translate }, \
    { { HTML_5_3, 0, HE_NOT_SVG }, { HTML_5_3 }, ELEM, a_xmlns }, \
    { { HTML_SVG11, 0, HE_NOT_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmlspace }

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

#define SVG_HTML_ATTRIBUTES(ELEM) \
    SVG_BASE_ATTRIBUTES (ELEM), \
    STANDARD_HTMLS_4_5_ATTRIBUTES (ELEM)
