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

hav_t havt_mpadded [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_mpadded, a_lspace },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mpadded, a_voffset },
    MATH_SIZEINFO_ATTRIBUTES (elem_mpadded),
    MATH4_PRES_ATTRIBUTES (elem_mpadded),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mpadded),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mpath [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mpath, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_mpath, a_href },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_mpath, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_mpath),
    SVG_XLINK_ATTRIBUTES_EX (elem_mpath, HE_SVG_1),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mphantom [] =
{   MATH4_PRES_ATTRIBUTES (elem_mphantom),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mphantom),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mprescripts [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_mprescripts, a_xmlns },
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mprescripts),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mroot [] =
{   MATH4_PRES_ATTRIBUTES (elem_mroot),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mroot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrow [] =
{   MATH4_PRES_ATTRIBUTES (elem_mrow),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mrow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ms [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_ms, a_lquote },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ms, a_rquote },
    MATH4_PRES_ATTRIBUTES (elem_ms),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_ms),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mscarries [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_crossout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_location },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_scriptsizemultiplier },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarries, a_position },
    MATH4_PRES_ATTRIBUTES (elem_mscarries),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mscarry [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarry, a_crossout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mscarry, a_location },
    MATH4_PRES_ATTRIBUTES (elem_mscarry),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msgroup [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_msgroup, a_position },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msgroup, a_shift },
    MATH4_PRES_ATTRIBUTES (elem_msgroup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msline [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_leftoverhang },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_length },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_mslinethickness },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_position },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_msline, a_position },
    MATH4_PRES_ATTRIBUTES (elem_msline),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mspace [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_mspace, a_linebreak },
    MATH3_TOKEN_ATTRIBUTES (elem_mspace),
    MATH3_LINEINDENT_ATTRIBUTES (elem_mspace),
    MATH_SIZEINFO_ATTRIBUTES (elem_mspace),
    MATH4_PRES_ATTRIBUTES (elem_mspace),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mspace),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msqrt [] =
{   MATH4_PRES_ATTRIBUTES (elem_msqrt),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msqrt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msrow [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_msrow, a_position },
    MATH4_PRES_ATTRIBUTES (elem_msrow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mstack [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_align },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_charalign },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_charspacing },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_mstack, a_stackalign },
    MATH4_PRES_ATTRIBUTES (elem_mstack),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mstyle [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, a_accentunder },
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
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mstyle),
    MATH_OPINFO_ATTRIBUTES (elem_mstyle),
    MATH3_TABLE_ATTRIBUTES (elem_mstyle),
    MATH4_PRES_ATTRIBUTES (elem_mstyle),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mstyle),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msub [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_msub, a_subscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msub),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msub),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msubsup [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_msubsup, a_subscriptshift },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msubsup, a_superscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msubsup),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msubsup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msup [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_msup, a_superscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msup),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtable [] =
{   MATH3_TABLE_ATTRIBUTES (elem_mtable),
    MATH4_PRES_ATTRIBUTES (elem_mtable),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtable),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtd [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_columnalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_columnspan },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_groupalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_rowalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_rowspan },
    MATH4_PRES_ATTRIBUTES (elem_mtd),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtd),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtext [] =
{   MATH4_PRES_ATTRIBUTES (elem_mtext),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtext),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtr [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_columnalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_groupalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtr, a_rowalign },
    MATH4_PRES_ATTRIBUTES (elem_mtr),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_munder [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_munder, a_accentunder },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_munder, a_align },
    MATH4_PRES_ATTRIBUTES (elem_munder),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_munder),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_munderover [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accent },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accentunder },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_munderover, a_align },
    MATH4_PRES_ATTRIBUTES (elem_munderover),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_munderover),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
