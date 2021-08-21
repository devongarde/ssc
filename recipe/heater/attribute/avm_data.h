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
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_activedescendant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_atomic }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_autocomplete }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_busy }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_checked }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_controls }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_describedby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_disabled }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_dropeffect }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_expanded }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_flowto }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_grabbed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_haspopup }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_hidden }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_invalid }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_label }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_labelledby }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_level }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_live }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_multiline }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_multiselectable }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_orientation }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_owns }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_posinset }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_pressed }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_readonly }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_relevant }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_required }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_selected }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_setsize }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_sort }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_valuemax }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_valuemin }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_valuenow }, \
    { { MAJOR_FROM, MINOR_FROM, FLAG, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_valuetext }

#define ADDITIONAL_ARIA_ATTRIBUTES(ELEM) \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_colcount }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_colindex }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_colspan }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_current }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_details }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_errormessage }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_modal }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_placeholder }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_roledescription }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_rowcount }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_rowindex }, \
    { { HTML_APR21, 0, HE_NOT_SVG_1 }, { HTML_UNDEF }, ELEM, a_aria_rowspan }

#define CC_ATTRIBUTES(ELEM) \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_attribution_name }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_attribution_url }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_more_permissions }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_licence }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_permits }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_prohibits }, \
    { { HTML_CC }, { HTML_UNDEF }, ELEM, a_cc_requires }

#define DC_ATTRIBUTES(ELEM) \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_contributor }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_coverage }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_creator }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_date }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_description }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_format }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_identifier }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_language }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_publisher }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_relation }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_rights }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_source }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_subject }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_title }, \
    { { HTML_DC }, { HTML_UNDEF }, ELEM, a_dc_type }

#define DCTERMS_ATTRIBUTES(ELEM) \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_abstract }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_accessrights }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_accrualmethod }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_accrualperiodicity }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_accrualpolicy }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_alternative }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_audience }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_available }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_bibliographiccitation }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_conformsto }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_contributor }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_coverage }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_created }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_creator }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_date }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_dateaccepted }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_datecopyrighted }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_datesubmitted }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_description }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_educationlevel }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_extent }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_format }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_hasformat }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_haspart }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_hasversion }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_identifier }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_instructionalmethod }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_isformatof }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_ispartof }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_isreferencedby }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_isreplacedby }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_isrequiredby }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_issued }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_isversionof }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_language }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_licence }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_mediator }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_medium }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_modified }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_provenance }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_publisher }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_references }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_relation }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_replaces }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_requires }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_rights }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_rightsholder }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_source }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_spatial }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_subject }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_tableofcontents }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_temporal }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_title }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_type }, \
    { { HTML_DCTERMS }, { HTML_UNDEF }, ELEM, a_dct_valid }

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

#define RDF_ATTRIBUTES(ELEM) \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_about }, \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_datatype }, \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_id }, \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_nodeid }, \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_parsetype }, \
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, ELEM, a_rdf_resource }

#define RDFA_ATTRIBUTES_EX(ELEM,FLAGS) \
    RDF_ATTRIBUTES (ELEM), \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_about }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_content }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_datatype }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_property }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_rel }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_resource }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_rev }, \
    { { HTML_RDF10, 0, FLAGS }, { HTML_UNDEF }, ELEM, a_typeof }

#define RDFA_STANDARD_ATTRIBUTES(ELEM) \
    RDF_ATTRIBUTES (ELEM), \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_about }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_content }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_datatype }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_inlist }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_instanceof }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_prefix }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_property }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_rel }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_resource }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_rev }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_src }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_typeof }, \
    { { HTML_RDF10, 0, HE_RDFA | HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_vocab }

#define SVG_ANIMATION_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onbegin }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onend }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_onload }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onrepeat }

#define SVG_ANIMATION_EVENT_ATTRIBUTES(ELEM) \
    SVG_ANIMATION_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_2)

#define SVG_ANIMATION_ADD_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_additive }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_accumulate }

#define SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_attributename }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_attributetype }

#define SVG_ANIMATION_VALUE_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_by }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_calcmode }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_from }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_keysplines }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_keytimes }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_to }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_values }

#define SVG_ANIMATION_TIMING_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_begin }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_dur }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_end }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_min }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_max }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_restart }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_repeatcount }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_repeatdur }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill }

#define SVG_BASE_ATTRIBUTES(ELEM) \
    RDFA_ATTRIBUTES_EX (ELEM, HE_RDFA | HE_SVG_12), \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_role }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xmlbase }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_xmlid }

#define SVG_COMP_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_amplitude }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_exponent }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_intercept }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_offset }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_type }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_slope }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_tablevalues }

#define SVG_CONDITIONAL_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_min_unit_scale }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_max_unit_scale }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_requiredextensions }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_requiredfeatures }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_requiredfonts }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_requiredformats }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_systemlanguage }

#define SVG_CONDITIONAL_ATTRIBUTES(ELEM) \
    SVG_CONDITIONAL_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG_CXY_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_cx }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_cy }

#define SVG_DOCUMENT_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onabort }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onerror }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onresize }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onscroll }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onunload }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_onzoom }

#define SVG_DOCUMENT_EVENT_ATTRIBUTES(ELEM) \
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11)

#define SVG_DXY_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_dx }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_dy }

#define SVG_DXY_ATTRIBUTES(ELEM) \
    SVG_DXY_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_2)

#define SVG_GRAPHICAL_EVENT_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_2 }, { HTML_UNDEF }, ELEM, a_onactivate }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_21 }, { HTML_UNDEF }, ELEM, a_onfocusin }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_21 }, { HTML_UNDEF }, ELEM, a_onfocusout }, \
    { { HTML_SVG10, 0, VER | HE_NOT_SVG_2 }, { HTML_UNDEF }, ELEM, a_onload }

#define SVG_GRAPHICAL_EVENT_ATTRIBUTES(ELEM) \
    SVG_GRAPHICAL_EVENT_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_20)

#define SVG_LANGSPACE_ATTRIBUTES_10(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmllang }, \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_xmlspace }

#define SVG_RXY_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_rx }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_ry }

#define SVG_PRESENTATION_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_alignment_baseline }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_audio_level }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_background_fill }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_baseline_shift }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_buffered_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_cache }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_clip }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_clip_path }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_clip_rule }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_clip_to_self }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation_filters }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_colour_profile }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_comp_op }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, ELEM, a_cursor }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_display }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_display_align }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_dominant_baseline }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_enable_background }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_filter }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_flood_colour }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_flood_opacity }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focushighlight }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focusable }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_feature_settings }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_kerning }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font_size_adjust }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_font_stretch }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_caps }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_east_asian }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_ligatures }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_numeric }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_position }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_weight }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_vertical }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_horizontal }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_image_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_isolation }, \
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, ELEM, a_kerning }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_knock_out }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_letter_spacing }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_lighting_colour }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_line_increment }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_marker }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_end }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_mid }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_marker_start }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_mask }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_down }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_downleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_downright }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_left }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_next }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_prev }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_right }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_up }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_upleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_upright }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_overflow }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_overlay_host }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_page_orientation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_paint_order }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_pointer_events }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_rendering_colour_space }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_shape_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_snap }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_colour }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_opacity }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_static }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_width }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_text_align }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_align_last }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_anchor }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_text_decoration }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_fill }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_line }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_stroke }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_style }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_indent }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_orientation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_overflow }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_tooltip }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform }, /* 8.5 */ \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform_box }, /* 8.5 */ \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_transform_host }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_unicode_bidi }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_vertical_align }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_viewport_fill }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_viewport_fill_opacity }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_visibility }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_white_space }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_writing_mode }, \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_word_spacing }

#define SVG_PRESENTATION_ATTRIBUTES_11_2(ELEM) \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_alignment_baseline }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_baseline_shift }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_clip }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_clip_path }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_clip_rule }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation_filters }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_colour_profile }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_colour_rendering }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_cursor }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_display }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_dominant_baseline }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_enable_background }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_filter }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_flood_colour }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_flood_opacity }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_feature_settings }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_kerning }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_size_adjust }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_stretch }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_caps }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_east_asian }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_ligatures }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_numeric }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_position }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_font_weight }, \
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_vertical }, \
    { { HTML_SVG11, 0, HE_SVG_11_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_horizontal }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_image_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_isolation }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_kerning }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_letter_spacing }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_lighting_colour }, \
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, ELEM, a_marker }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_marker_end }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_marker_mid }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_marker_start }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_mask }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_overflow }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_paint_order }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_pointer_events }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_shape_rendering }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stop_opacity }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_stroke_width }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_align }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_align_last }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_text_anchor }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_text_decoration }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_fill }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_line }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_stroke }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_style }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_indent }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_orientation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_overflow }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_text_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform }, /* 8.5 */ \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform_box }, /* 8.5 */ \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_unicode_bidi }, \
    { { HTML_SVG12, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_vertical_align }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_viewport_fill }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_visibility }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_white_space }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_writing_mode }, \
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, ELEM, a_word_spacing }

#define SVG_PRESENTATION_ATTRIBUTES_12(ELEM) \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_audio_level }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_background_fill }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_buffered_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_cache }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_clip_to_self }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_colour_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_comp_op }, \
    { { HTML_SVG12, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, ELEM, a_cursor }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_display }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_display_align }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focushighlight }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_focusable }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_feature_settings }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_kerning }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_caps }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_east_asian }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_ligatures }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_numeric }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_position }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_font_weight }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_image_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_isolation }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_knock_out }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_line_increment }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_down }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_downleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_downright }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_left }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_next }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_prev }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_right }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_up }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_upleft }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_nav_upright }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_overlay_host }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_page_orientation }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_pointer_events }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_rendering_colour_space }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_shape_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_snap }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_colour }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_solid_opacity }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_static }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stop_opacity }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_stroke_width }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_text_align }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_anchor }, \
    { { HTML_SVG12, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_text_decoration }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_text_rendering }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_tooltip }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_transform_host }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_unicode_bidi }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, ELEM, a_viewport_fill }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_viewport_fill_opacity }, \
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_visibility }

#define SVG_PRESENTATION_ATTRIBUTES_2(ELEM) \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_alignment_baseline }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_baseline_shift }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_clip_path }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_clip_rule }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_colour_interpolation_filters }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_colour_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_direction }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_display }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_dominant_baseline }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_fill }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_fill_opacity }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_fill_rule }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_filter }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_flood_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_flood_opacity }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_family }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_feature_settings }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_kerning }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_size }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_size_adjust }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_stretch }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_style }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_caps }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_east_asian }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_ligatures }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_numeric }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_variant_position }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_font_weight }, \
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_vertical }, \
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, ELEM, a_glyph_orientation_horizontal }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_image_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_isolation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_letter_spacing }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_lighting_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_marker_end }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_marker_mid }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_marker_start }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_mask }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_opacity }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_overflow }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_paint_order }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_pointer_events }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_shape_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stop_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stop_opacity }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_dasharray }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_dashoffset }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_linecap }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_linejoin }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_miterlimit }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_opacity }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_stroke_width }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_align }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_align_last }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_anchor }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_colour }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_fill }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_line }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_stroke }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_decoration_style }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_indent }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_orientation }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_overflow }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_text_rendering }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform }, /* 8.5 */ \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_transform_box }, /* 8.5 */ \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_unicode_bidi }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_vertical_align }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_visibility }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_vector_effect }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_viewport_fill }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_white_space }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_word_spacing }, \
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, ELEM, a_writing_mode }

#define SVG_REF_XY_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_refx }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_refy }

#define SVG_REF_XY_ATTRIBUTES(ELEM) \
    SVG_REF_XY_ATTRIBUTES_EX (ELEM, HE_SVG_10_11_2)

#define SVG_SYNC_ATTRIBUTES(ELEM) \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_syncbehaviour }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_syncmaster }, \
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, ELEM, a_synctolerance }

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

#define SVG_XLINK_ATTRIBUTES_EX(ELEM,VER) \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_onloadprogress }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_onpostload }, \
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, ELEM, a_onpreload }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkactuate }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkarcrole }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_xlinkhref }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkrole }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinkshow }, \
    { { HTML_SVG10, 0, VER }, { HTML_UNDEF }, ELEM, a_xlinktitle }, \
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, ELEM, a_xlinktype }

#define SVG_XLINK_ATTRIBUTES(ELEM) \
    SVG_XLINK_ATTRIBUTES_EX (ELEM, HE_SVG)

#define SVG10_FIT_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_preserveaspectratio }

#define SVG10_G_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, ELEM, a_onselect }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_transform }

#define SVG_GRAD_ATTRIBUTES(ELEM) \
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_gradienttransform }, \
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_gradientunits }

#define SVG_FILTER_ATTRIBUTES_EX(ELEM,FROM) \
    { { FROM, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_height }, \
    { { FROM, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, ELEM, a_result }, \
    { { FROM, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_width }, \
    { { FROM, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_x }, \
    { { FROM, 0, HE_SVG }, { HTML_UNDEF }, ELEM, a_y }

#define SVG_FILTER_ATTRIBUTES(ELEM) \
    SVG_FILTER_ATTRIBUTES_EX (ELEM, HTML_SVG10)

#define XHTML1_STANDARD_ATTRIBUTES(ELEM) \
    CC_ATTRIBUTES (ELEM), \
    DC_ATTRIBUTES (ELEM), \
    DCTERMS_ATTRIBUTES (ELEM), \
    RDF_ATTRIBUTES (ELEM), \
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
    { { XHTML_1_0, 0, HE_NOT_SVG_20 }, { HTML_UNDEF }, ELEM, a_xmlbase }, \
    { { XHTML_2_0, 0, HE_NOT_SVG_10_11_20 }, { HTML_UNDEF }, ELEM, a_xmlid }
// note: xml:base was backported to XML 1.0 & 1.1, apparently. ( https://www.w3.org/TR/xmlbase/ )

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
    { { HTML_5_0, HV_W3, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_accept_charset }, \
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
    { { HTML_5_3, 0, HE_NOT_SVG }, { HTML_UNDEF }, ELEM, a_xmlns }, \
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
