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

hav_t havt_m2 [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_mpadded, a_lspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mpadded, a_voffset },
    MATH_SIZEINFO_ATTRIBUTES (elem_mpadded),
    MATH3_PRES_ATTRIBUTES (elem_mpadded),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mpath, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_mpath, a_href },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_mpath, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_mpath),
    SVG_XLINK_ATTRIBUTES_EX (elem_mpath, HE_SVG_1),

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

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
