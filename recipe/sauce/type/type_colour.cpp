/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type/type_colour.h"

struct symbol_entry < e_fixedcolour > fixedcolour_symbol_table [] =
{   { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "aliceblue", fc_aliceblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "antiquewhite", fc_antiquewhite },
    { { HTML_3_2 }, { HTML_UNDEF }, "aqua", fc_aqua },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "aquamarine", fc_aquamarine },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "azure", fc_azure },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "beige", fc_beige },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "bisque", fc_bisque },
    { { HTML_3_2 }, { HTML_UNDEF }, "black", fc_black },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "blanchedalmond", fc_blanchedalmond },
    { { HTML_3_2 }, { HTML_UNDEF }, "blue", fc_blue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "blueviolet", fc_blueviolet },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "brown", fc_brown },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "burlywood", fc_burlywood },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "cadetblue", fc_cadetblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "chartreuse", fc_chartreuse },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "chocolate", fc_chocolate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "coral", fc_coral },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "cornflowerblue", fc_cornflowerblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "cornsilk", fc_cornsilk },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "crimson", fc_crimson },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "cyan", fc_cyan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkblue", fc_darkblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkcyan", fc_darkcyan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkgoldenrod", fc_darkgoldenrod },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkgray", fc_darkgray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkgreen", fc_darkgreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkgrey", fc_darkgrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkkhaki", fc_darkkhaki },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkmagenta", fc_darkmagenta },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkolivegreen", fc_darkolivegreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkorange", fc_darkorange },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkorchid", fc_darkorchid },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkred", fc_darkred },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darksalmon", fc_darksalmon },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkseagreen", fc_darkseagreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkslateblue", fc_darkslateblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkslategray", fc_darkslategray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkslategrey", fc_darkslategrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkturquoise", fc_darkturquoise },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "darkviolet", fc_darkviolet },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "deeppink", fc_deeppink },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "deepskyblue", fc_deepskyblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "dimgray", fc_dimgray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "dimgrey", fc_dimgrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "dodgerblue", fc_dodgerblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "firebrick", fc_firebrick },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "floralwhite", fc_floralwhite },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "forestgreen", fc_forestgreen },
    { { HTML_3_2 }, { HTML_UNDEF }, "fuchsia", fc_fuchsia },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "gainsboro", fc_gainsboro },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "ghostwhite", fc_ghostwhite },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "gold", fc_gold },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "goldenrod", fc_goldenrod },
    { { HTML_3_2 }, { HTML_UNDEF }, "gray", fc_grey },
    { { HTML_3_2 }, { HTML_UNDEF }, "green", fc_green },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "greenyellow", fc_greenyellow },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "honeydew", fc_honeydew },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "hotpink", fc_hotpink },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "indianred", fc_indianred },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "indigo", fc_indigo },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "ivory", fc_ivory },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "khaki", fc_khaki },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lavender", fc_lavender },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lavenderblush", fc_lavenderblush },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lawngreen", fc_lawngreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lemonchiffon", fc_lemonchiffon },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightblue", fc_lightblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightcoral", fc_lightcoral },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightcyan", fc_lightcyan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightgoldenrodyellow", fc_lightgoldenrodyellow },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightgray", fc_lightgray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightgreen", fc_lightgreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightgrey", fc_lightgrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightpink", fc_lightpink },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightsalmon", fc_lightsalmon },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightseagreen", fc_lightseagreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightskyblue", fc_lightskyblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightslategray", fc_lightslategray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightslategrey", fc_lightslategrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightsteelblue", fc_lightsteelblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "lightyellow", fc_lightyellow },
    { { HTML_3_2 }, { HTML_UNDEF }, "lime", fc_lime },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "limegreen", fc_limegreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "linen", fc_linen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "magenta", fc_magenta },
    { { HTML_3_2 }, { HTML_UNDEF }, "maroon", fc_maroon },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumaquamarine", fc_mediumaquamarine },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumblue", fc_mediumblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumorchid", fc_mediumorchid },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumpurple", fc_mediumpurple },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumseagreen", fc_mediumseagreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumslateblue", fc_mediumslateblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumspringgreen", fc_mediumspringgreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumturquoise", fc_mediumturquoise },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mediumvioletred", fc_mediumvioletred },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "midnightblue", fc_midnightblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mintcream", fc_mintcream },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "mistyrose", fc_mistyrose },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "moccasin", fc_moccasin },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "navajowhite", fc_navajowhite },
    { { HTML_3_2 }, { HTML_UNDEF }, "navy", fc_navy },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "oldlace", fc_oldlace },
    { { HTML_3_2 }, { HTML_UNDEF }, "olive", fc_olive },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "olivedrab", fc_olivedrab },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "orange", fc_orange },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "orangered", fc_orangered },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "orchid", fc_orchid },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "palegoldenrod", fc_palegoldenrod },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "palegreen", fc_palegreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "paleturquoise", fc_paleturquoise },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "palevioletred", fc_palevioletred },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "papayawhip", fc_papayawhip },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "peachpuff", fc_peachpuff },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "peru", fc_peru },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "pink", fc_pink },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "plum", fc_plum },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "powderblue", fc_powderblue },
    { { HTML_3_2 }, { HTML_UNDEF }, "purple", fc_purple },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "rebeccapurple ", fc_rebeccapurple  },
    { { HTML_3_2 }, { HTML_UNDEF }, "red", fc_red },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "rosybrown", fc_rosybrown },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "royalblue", fc_royalblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "saddlebrown", fc_saddlebrown },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "salmon", fc_salmon },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "sandybrown", fc_sandybrown },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "seagreen", fc_seagreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "seashell", fc_seashell },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "sienna", fc_sienna },
    { { HTML_3_2 }, { HTML_UNDEF }, "silver", fc_silver },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "skyblue", fc_skyblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "slateblue", fc_slateblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "slategray", fc_slategray },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "slategrey", fc_slategrey },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "snow", fc_snow },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "springgreen", fc_springgreen },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "steelblue", fc_steelblue },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "tan", fc_tan },
    { { HTML_3_2 }, { HTML_UNDEF }, "teal", fc_teal },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "thistle", fc_thistle },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "tomato", fc_tomato },
    { { XHTML_1_0, 0, HE_MATH_2 }, { HTML_UNDEF }, "transparent", fc_transparent },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "turquoise", fc_turquoise },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "violet", fc_violet },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "wheat", fc_wheat },
    { { HTML_3_2 }, { HTML_UNDEF }, "white", fc_white },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "whitesmoke", fc_whitesmoke },
    { { HTML_3_2 }, { HTML_UNDEF }, "yellow", fc_yellow },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, "yellowgreen", fc_yellowgreen } };

void fixedcolour_init (nitpick& nits)
{   type_master < t_fixedcolour > :: init (nits, fixedcolour_symbol_table, sizeof (fixedcolour_symbol_table) / sizeof (symbol_entry < e_fixedcolour >)); }