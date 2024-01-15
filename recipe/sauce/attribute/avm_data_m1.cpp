/*
ssc (static site checker)
File Info
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

hav_t havt_m [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_m),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_maction [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_maction, a_actiontype },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_maction, a_selection },
    MATH4_PRES_ATTRIBUTES (elem_maction),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_maction),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_maligngroup [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_maligngroup, a_groupalign },
    MATH4_PRES_ATTRIBUTES (elem_maligngroup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_malignmark [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_malignmark, a_edge },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_main [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_main),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_map [] =
{   { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_map, a_name },
    { { XHTML_1_0, HV_DEPRECATEDX1 }, { XHTML_2_0 }, elem_map, a_name },
    { { HTML_JAN05, REQUIRED }, { HTML_UNDEF }, elem_map, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_map),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_margin [] =
{   HTMLPLUS_ATTRIBUTES (elem_margin),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mark [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_mark),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_marker [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_marker, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerheight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerwidth },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_orient },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_marker, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_viewbox },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_marker, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_marker),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_marker),
    SVG_PRESENTATION_ATTRIBUTES (elem_marker),
    SVG_REF_XY_ATTRIBUTES (elem_marker),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_marquee [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, elem_marquee, a_behaviour },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mask [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mask, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, a_maskcontentunits },
    { { HTML_SVG10, 0, HE_SVG, 0, H3_CSS_MASKING }, { HTML_UNDEF }, elem_mask, a_masktype },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, a_maskunits },
    SVG_BOX_ATTRIBUTES (elem_mask),
    SVG_CONDITIONAL_ATTRIBUTES (elem_mask),
    SVG_HTML_ATTRIBUTES (elem_mask),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_mask),
    SVG_PRESENTATION_ATTRIBUTES (elem_mask),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_math [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_altimg },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_height },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_width },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_alttext },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_baseline },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_cdgroup },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_definitionurl },
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_MATH4_C }, elem_math, a_display },
    { { HTML_MATH4_C, 0, 0 }, { HTML_UNDEF }, elem_math, a_display },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_height },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_macros },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_maxwidth },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_mode },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_overflow },
    { { HTML_MATH1, HV_NOTPROD }, { HTML_UNDEF }, elem_math, a_style },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_type },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_width },
    MATH3_TOKEN_ATTRIBUTES (elem_math),
    MATH3_LINEINDENT_ATTRIBUTES (elem_math),
    MATH4_PRES_ATTRIBUTES (elem_math),
    HTML3_CLID_ATTRIBUTES (elem_math),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_math),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_math),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_matrix [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_matrix),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_matrixrow [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_matrixrow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_max [] =
{   MATH3_DEFS_ATTRIBUTES (elem_max),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mean [] =
{   MATH3_DEFS_ATTRIBUTES (elem_mean),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_median [] =
{   MATH3_DEFS_ATTRIBUTES (elem_median),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_menclose [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_menclose, a_notation },
    MATH4_PRES_ATTRIBUTES (elem_menclose),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_menu [] =
{   { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_menu, a_align },
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
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_menubar [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_menubar),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_menuitem [] =
{   { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_checked },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_default },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_disabled },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_icon },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_label },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_radiogroup },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_menuitem),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_menulabel [] =
{   { { HTML_JAN05 }, { HTML_DEC05 }, elem_menulabel, a_label },
    STANDARD_HTML5_ATTRIBUTES (elem_menulabel),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_merror [] =
{   MATH4_PRES_ATTRIBUTES (elem_merror),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_merror),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_meta [] =
{   { { HTML_JUL07 }, { HTML_UNDEF }, elem_meta, a_charset },
    { { HTML_2_0, REQUIRED }, { XHTML_1_1 }, elem_meta, a_content },
    { { XHTML_2_0 }, { HTML_UNDEF }, elem_meta, a_content },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_dir },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_meta, a_httpequiv },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_lang },
    { { HTML_JUL21 }, { HTML_UNDEF }, elem_meta, a_media },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_meta, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_meta, a_scheme },
    HTML23_CLID_ATTRIBUTES (elem_meta),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_meta),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_metadata [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_metadata, a_requiredextensions },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_metadata, a_requiredfeatures },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_metadata, a_requiredfonts },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_metadata, a_requiredformats },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_metadata, a_systemlanguage },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_metadata, HE_SVG_2),
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_metadata),
    SVG_HTML_ATTRIBUTES (elem_metadata),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_meter [] =
{   { { HTML_JUL10 }, { HTML_JUN11 }, elem_meter, a_form },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_high },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_low },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_max },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_min },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, a_optimum },
    { { HTML_JUL06 }, { HTML_DEC09 }, elem_meter, a_value },
    { { HTML_JAN10, REQUIRED }, { HTML_UNDEF }, elem_meter, a_value },
    STANDARD_HTML5_ATTRIBUTES (elem_meter),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mfenced [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfenced, a_close },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfenced, a_open },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfenced, a_separators },
    MATH4_PRES_ATTRIBUTES (elem_mfenced),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mfrac [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfrac, a_bevelled },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfrac, a_denomalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mfrac, a_linethickness },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfrac, a_numalign },
    MATH4_PRES_ATTRIBUTES (elem_mfrac),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mfrac),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mglyph [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mglyph, a_alt },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mglyph, a_fontfamily },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_height },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mglyph, a_index },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_src },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_width },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mh [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_action },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_hidden },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_method },
    HTMLPLUS_ATTRIBUTES (elem_mh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mi [] =
{   MATH4_PRES_ATTRIBUTES (elem_mi),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mi),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_min [] =
{   MATH3_DEFS_ATTRIBUTES (elem_min),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_minus [] =
{   MATH3_DEFS_ATTRIBUTES (elem_minus),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_missingglyph [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_missingglyph, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_missingglyph, a_horiz_adv_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_adv_y },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_origin_y },
    SVG_HTML_ATTRIBUTES (elem_missingglyph),
    SVG_PRESENTATION_ATTRIBUTES (elem_missingglyph),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mlabeledtr [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mlabeledtr, a_columnalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mlabeledtr, a_groupalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mlabeledtr, a_rowalign },
    MATH4_PRES_ATTRIBUTES (elem_mlabeledtr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mlongdiv [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, a_align },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, a_charalign },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, a_charspacing },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, a_longdivstyle },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, a_stackalign },
    MATH4_PRES_ATTRIBUTES (elem_mlongdiv),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mmultiscripts [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mmultiscripts, a_subscriptshift },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mmultiscripts, a_superscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_mmultiscripts),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mmultiscripts),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mn [] =
{   MATH3_LINEINDENT_ATTRIBUTES (elem_mn),
    MATH4_PRES_ATTRIBUTES (elem_mn),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mn),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mo [] =
{   MATH3_LINEINDENT_ATTRIBUTES (elem_mo),
    MATH_OPINFO_ATTRIBUTES (elem_mo),
    MATH4_PRES_ATTRIBUTES (elem_mo),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mo),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mode [] =
{   MATH3_DEFS_ATTRIBUTES (elem_mode),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_moment [] =
{   MATH3_DEFS_ATTRIBUTES (elem_moment),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_momentabout [] =
{   MATH3_DEFS_ATTRIBUTES (elem_momentabout),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mover [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_mover, a_accent },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mover, a_align },
    MATH4_PRES_ATTRIBUTES (elem_mover),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mover),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
