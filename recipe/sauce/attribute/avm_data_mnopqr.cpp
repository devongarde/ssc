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

hav_t havt_mnopqr [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_m),

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

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_line, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerheight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_markerwidth },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_orient },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_marker, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, a_viewbox },
    SVG_BOX_ATTRIBUTES (elem_marker),
    SVG_REF_XY_ATTRIBUTES (elem_marker),
    SVG_HTML_ATTRIBUTES (elem_marker),
    SVG_PRESENTATION_ATTRIBUTES (elem_marker),

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

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mask, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, a_maskcontentunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, a_maskunits },
    SVG_BOX_ATTRIBUTES (elem_mask),
    SVG_CONDITIONAL_ATTRIBUTES (elem_mask),
    SVG_HTML_ATTRIBUTES (elem_mask),
    SVG_PRESENTATION_ATTRIBUTES (elem_mask),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_altimg },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_height },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_altimg_width },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_alttext },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_baseline },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_cdgroup },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_definitionurl },
    { { HTML_MATH2, 0, HE_MATH_2 }, { HTML_UNDEF }, elem_math, a_display },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_height },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_macros },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_math, a_maxwidth },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_mode },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_overflow },
    { { HTML_MATH1, HV_NOTPROD }, { HTML_UNDEF }, elem_math, a_style },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_type },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, a_width },
    MATH3_TOKEN_ATTRIBUTES (elem_math),
    MATH3_LINEINDENT_ATTRIBUTES (elem_math),
    MATH3_PRES_ATTRIBUTES (elem_math),
    HTML3_CLID_ATTRIBUTES (elem_math),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_math),

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

    SVG_HTML_ATTRIBUTES (elem_metadata),

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
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_height },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mglyph, a_index },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_src },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_mglyph, a_width },

    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_action },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_hidden },
    { { HTML_PLUS }, { HTML_PLUS }, elem_mh, a_method },
    HTMLPLUS_ATTRIBUTES (elem_mh),

    MATH3_FONT_ATTRIBUTES (elem_mi),
    MATH3_PRES_ATTRIBUTES (elem_mi),

    MATH3_DEFS_ATTRIBUTES (elem_min),

    MATH3_DEFS_ATTRIBUTES (elem_minus),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_missingglyph, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_missingglyph, a_horizadvx },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_adv_y },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, a_vert_origin_y },
    SVG_HTML_ATTRIBUTES (elem_missingglyph),
    SVG_PRESENTATION_ATTRIBUTES (elem_missingglyph),

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

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mover, a_accent },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_mover, a_align },
    MATH3_PRES_ATTRIBUTES (elem_mover),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mpadded, a_lspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mpadded, a_voffset },
    MATH_SIZEINFO_ATTRIBUTES (elem_mpadded),
    MATH3_PRES_ATTRIBUTES (elem_mpadded),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mpath, a_externalresourcesrequired },
    SVG_XLINK_ATTRIBUTES (elem_mpath),
    SVG_HTML_ATTRIBUTES (elem_mpath),

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

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msub, a_subscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msub),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msubsup, a_subscriptshift },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msubsup, a_superscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msubsup),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msup, a_superscriptshift },
    MATH3_PRES_ATTRIBUTES (elem_msup),

    MATH3_TABLE_ATTRIBUTES (elem_mtable),
    MATH3_PRES_ATTRIBUTES (elem_mtable),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_columnalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_columnspan },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_groupalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_rowalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_rowspan },
    MATH3_PRES_ATTRIBUTES (elem_mtd),

    MATH3_FONT_ATTRIBUTES (elem_mtext),
    MATH3_PRES_ATTRIBUTES (elem_mtext),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_columnalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_groupalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_rowalign },
    MATH3_PRES_ATTRIBUTES (elem_mtr),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munder, a_accentunder },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_munder, a_align },
    MATH3_PRES_ATTRIBUTES (elem_munder),

    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accent },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accentunder },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_munderover, a_align },
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

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_path, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_path, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_path, a_flatness },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_path, a_marker },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_path, a_nominallength },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_path, a_pathlength },
    SVG10_G_ATTRIBUTES(elem_path),
    SVG_CONDITIONAL_ATTRIBUTES (elem_path),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_path),
    SVG_HTML_ATTRIBUTES (elem_path),
    SVG_PRESENTATION_ATTRIBUTES (elem_path),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_pattern, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patterncontentunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patterntransform },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_patternunits },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_pattern, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, a_viewbox },
    SVG_BOX_ATTRIBUTES (elem_pattern),
    SVG_REF_XY_ATTRIBUTES (elem_pattern),
    SVG_CONDITIONAL_ATTRIBUTES (elem_pattern),
    SVG_HTML_ATTRIBUTES (elem_pattern),
    SVG_XLINK_ATTRIBUTES (elem_pattern),
    SVG_PRESENTATION_ATTRIBUTES (elem_pattern),

    HTMLPLUS_ATTRIBUTES (elem_person),
    HTML23_CLID_ATTRIBUTES (elem_person),

    MATH3_DEFS_ATTRIBUTES (elem_pi),

    STANDARD_HTML5_ATTRIBUTES (elem_picture),

    MATH3_STANDARD_ATTRIBUTES (elem_piece),

    MATH3_STANDARD_ATTRIBUTES (elem_piecewise),

    MATH3_DEFS_ATTRIBUTES (elem_plus),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polygon, a_externalresourcesrequired },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_polygon, a_marker },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_polygon, a_points },
    SVG10_G_ATTRIBUTES (elem_polygon),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_polygon),
    SVG_CONDITIONAL_ATTRIBUTES (elem_polygon),
    SVG_HTML_ATTRIBUTES (elem_polygon),
    SVG_PRESENTATION_ATTRIBUTES (elem_polygon),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_polyline, a_externalresourcesrequired },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_polyline, a_marker },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_polyline, a_points },
    SVG10_G_ATTRIBUTES (elem_polyline),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_polyline),
    SVG_CONDITIONAL_ATTRIBUTES (elem_polyline),
    SVG_HTML_ATTRIBUTES (elem_polyline),
    SVG_PRESENTATION_ATTRIBUTES (elem_polyline),

    MATH3_DEFS_ATTRIBUTES (elem_power),

    { { HTML_3_0 }, { HTML_3_0 }, elem_pre, a_clear },
    { { HTML_2_0, HV_NOT30, HE_MOZILLA | HE_NETSCAPE }, { HTML_3_2 }, elem_pre, a_cols },
    { { HTML_1_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_pre, a_width },
    { { HTML_2_0, 0, HE_MOZILLA | HV_NOT30 }, { HTML_UNDEF }, elem_pre, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_pre),
    HTML23_CLID_ATTRIBUTES (elem_pre),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_pre),

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_bandwidth },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediacharacterencoding },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediacontentencodings },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediasize },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, a_mediatime },
    SVG_HTML_ATTRIBUTES (elem_prefetch),
    SVG_XLINK_ATTRIBUTES (elem_prefetch),

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

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_radialgradient, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, a_cx },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, a_cy },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_radialgradient, a_fr },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_fx },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_fy },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, a_r },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, a_spreadmethod },
    SVG10_GRAD_ATTRIBUTES (elem_radialgradient),
    SVG_XLINK_ATTRIBUTES (elem_radialgradient),
    SVG_HTML_ATTRIBUTES (elem_radialgradient),
    SVG_PRESENTATION_ATTRIBUTES (elem_radialgradient),

    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_range, a_from },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_range, a_until },
    HTML_CID_ATTRIBUTES (elem_range, MAJOR_3_0, MINOR_3_0, MAJOR_3_0, MINOR_3_0),

    MATH3_DEFS_ATTRIBUTES (elem_rationals),

    STANDARD_HTML5_ATTRIBUTES (elem_rb),

    MATH3_DEFS_ATTRIBUTES (elem_real),

    MATH3_DEFS_ATTRIBUTES (elem_reals),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_rect, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_rect, a_rx },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_rect, a_ry },
    SVG_BOX_ATTRIBUTES (elem_rect),
    SVG10_G_ATTRIBUTES (elem_rect),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_rect),
    SVG_CONDITIONAL_ATTRIBUTES (elem_rect),
    SVG_HTML_ATTRIBUTES (elem_rect),
    SVG_PRESENTATION_ATTRIBUTES (elem_rect),

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

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
