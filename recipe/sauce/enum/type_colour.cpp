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
#include "type/type.h"

#define STANDARD_COLOURS(PREFIX,VERSION) \
    { { VERSION }, { HTML_UNDEF }, "aliceblue", PREFIX ## aliceblue }, \
    { { VERSION }, { HTML_UNDEF }, "antiquewhite", PREFIX ## antiquewhite }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "aqua", PREFIX ## aqua }, \
    { { VERSION }, { HTML_UNDEF }, "aquamarine", PREFIX ## aquamarine }, \
    { { VERSION }, { HTML_UNDEF }, "azure", PREFIX ## azure }, \
    { { VERSION }, { HTML_UNDEF }, "beige", PREFIX ## beige }, \
    { { VERSION }, { HTML_UNDEF }, "bisque", PREFIX ## bisque }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "black", PREFIX ## black }, \
    { { VERSION }, { HTML_UNDEF }, "blanchedalmond", PREFIX ## blanchedalmond }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "blue", PREFIX ## blue }, \
    { { VERSION }, { HTML_UNDEF }, "blueviolet", PREFIX ## blueviolet }, \
    { { VERSION }, { HTML_UNDEF }, "brown", PREFIX ## brown }, \
    { { VERSION }, { HTML_UNDEF }, "burlywood", PREFIX ## burlywood }, \
    { { VERSION }, { HTML_UNDEF }, "cadetblue", PREFIX ## cadetblue }, \
    { { VERSION }, { HTML_UNDEF }, "chartreuse", PREFIX ## chartreuse }, \
    { { VERSION }, { HTML_UNDEF }, "chocolate", PREFIX ## chocolate }, \
    { { VERSION }, { HTML_UNDEF }, "coral", PREFIX ## coral }, \
    { { VERSION }, { HTML_UNDEF }, "cornflowerblue", PREFIX ## cornflowerblue }, \
    { { VERSION }, { HTML_UNDEF }, "cornsilk", PREFIX ## cornsilk }, \
    { { VERSION }, { HTML_UNDEF }, "crimson", PREFIX ## crimson }, \
    { { VERSION }, { HTML_UNDEF }, "cyan", PREFIX ## cyan }, \
    { { VERSION }, { HTML_UNDEF }, "darkblue", PREFIX ## darkblue }, \
    { { VERSION }, { HTML_UNDEF }, "darkcyan", PREFIX ## darkcyan }, \
    { { VERSION }, { HTML_UNDEF }, "darkgoldenrod", PREFIX ## darkgoldenrod }, \
    { { VERSION }, { HTML_UNDEF }, "darkgray", PREFIX ## darkgray }, \
    { { VERSION }, { HTML_UNDEF }, "darkgreen", PREFIX ## darkgreen }, \
    { { VERSION }, { HTML_UNDEF }, "darkgrey", PREFIX ## darkgrey }, \
    { { VERSION }, { HTML_UNDEF }, "darkkhaki", PREFIX ## darkkhaki }, \
    { { VERSION }, { HTML_UNDEF }, "darkmagenta", PREFIX ## darkmagenta }, \
    { { VERSION }, { HTML_UNDEF }, "darkolivegreen", PREFIX ## darkolivegreen }, \
    { { VERSION }, { HTML_UNDEF }, "darkorange", PREFIX ## darkorange }, \
    { { VERSION }, { HTML_UNDEF }, "darkorchid", PREFIX ## darkorchid }, \
    { { VERSION }, { HTML_UNDEF }, "darkred", PREFIX ## darkred }, \
    { { VERSION }, { HTML_UNDEF }, "darksalmon", PREFIX ## darksalmon }, \
    { { VERSION }, { HTML_UNDEF }, "darkseagreen", PREFIX ## darkseagreen }, \
    { { VERSION }, { HTML_UNDEF }, "darkslateblue", PREFIX ## darkslateblue }, \
    { { VERSION }, { HTML_UNDEF }, "darkslategray", PREFIX ## darkslategray }, \
    { { VERSION }, { HTML_UNDEF }, "darkslategrey", PREFIX ## darkslategrey }, \
    { { VERSION }, { HTML_UNDEF }, "darkturquoise", PREFIX ## darkturquoise }, \
    { { VERSION }, { HTML_UNDEF }, "darkviolet", PREFIX ## darkviolet }, \
    { { VERSION }, { HTML_UNDEF }, "deeppink", PREFIX ## deeppink }, \
    { { VERSION }, { HTML_UNDEF }, "deepskyblue", PREFIX ## deepskyblue }, \
    { { VERSION }, { HTML_UNDEF }, "dimgray", PREFIX ## dimgray }, \
    { { VERSION }, { HTML_UNDEF }, "dimgrey", PREFIX ## dimgrey }, \
    { { VERSION }, { HTML_UNDEF }, "dodgerblue", PREFIX ## dodgerblue }, \
    { { VERSION }, { HTML_UNDEF }, "firebrick", PREFIX ## firebrick }, \
    { { VERSION }, { HTML_UNDEF }, "floralwhite", PREFIX ## floralwhite }, \
    { { VERSION }, { HTML_UNDEF }, "forestgreen", PREFIX ## forestgreen }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "fuchsia", PREFIX ## fuchsia }, \
    { { VERSION }, { HTML_UNDEF }, "gainsboro", PREFIX ## gainsboro }, \
    { { VERSION }, { HTML_UNDEF }, "ghostwhite", PREFIX ## ghostwhite }, \
    { { VERSION }, { HTML_UNDEF }, "gold", PREFIX ## gold }, \
    { { VERSION }, { HTML_UNDEF }, "goldenrod", PREFIX ## goldenrod }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "gray", PREFIX ## grey }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "green", PREFIX ## green }, \
    { { VERSION }, { HTML_UNDEF }, "greenyellow", PREFIX ## greenyellow }, \
    { { VERSION }, { HTML_UNDEF }, "honeydew", PREFIX ## honeydew }, \
    { { VERSION }, { HTML_UNDEF }, "hotpink", PREFIX ## hotpink }, \
    { { VERSION }, { HTML_UNDEF }, "indianred", PREFIX ## indianred }, \
    { { VERSION }, { HTML_UNDEF }, "indigo", PREFIX ## indigo }, \
    { { VERSION }, { HTML_UNDEF }, "ivory", PREFIX ## ivory }, \
    { { VERSION }, { HTML_UNDEF }, "khaki", PREFIX ## khaki }, \
    { { VERSION }, { HTML_UNDEF }, "lavender", PREFIX ## lavender }, \
    { { VERSION }, { HTML_UNDEF }, "lavenderblush", PREFIX ## lavenderblush }, \
    { { VERSION }, { HTML_UNDEF }, "lawngreen", PREFIX ## lawngreen }, \
    { { VERSION }, { HTML_UNDEF }, "lemonchiffon", PREFIX ## lemonchiffon }, \
    { { VERSION }, { HTML_UNDEF }, "lightblue", PREFIX ## lightblue }, \
    { { VERSION }, { HTML_UNDEF }, "lightcoral", PREFIX ## lightcoral }, \
    { { VERSION }, { HTML_UNDEF }, "lightcyan", PREFIX ## lightcyan }, \
    { { VERSION }, { HTML_UNDEF }, "lightgoldenrodyellow", PREFIX ## lightgoldenrodyellow }, \
    { { VERSION }, { HTML_UNDEF }, "lightgray", PREFIX ## lightgray }, \
    { { VERSION }, { HTML_UNDEF }, "lightgreen", PREFIX ## lightgreen }, \
    { { VERSION }, { HTML_UNDEF }, "lightgrey", PREFIX ## lightgrey }, \
    { { VERSION }, { HTML_UNDEF }, "lightpink", PREFIX ## lightpink }, \
    { { VERSION }, { HTML_UNDEF }, "lightsalmon", PREFIX ## lightsalmon }, \
    { { VERSION }, { HTML_UNDEF }, "lightseagreen", PREFIX ## lightseagreen }, \
    { { VERSION }, { HTML_UNDEF }, "lightskyblue", PREFIX ## lightskyblue }, \
    { { VERSION }, { HTML_UNDEF }, "lightslategray", PREFIX ## lightslategray }, \
    { { VERSION }, { HTML_UNDEF }, "lightslategrey", PREFIX ## lightslategrey }, \
    { { VERSION }, { HTML_UNDEF }, "lightsteelblue", PREFIX ## lightsteelblue }, \
    { { VERSION }, { HTML_UNDEF }, "lightyellow", PREFIX ## lightyellow }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "lime", PREFIX ## lime }, \
    { { VERSION }, { HTML_UNDEF }, "limegreen", PREFIX ## limegreen }, \
    { { VERSION }, { HTML_UNDEF }, "linen", PREFIX ## linen }, \
    { { VERSION }, { HTML_UNDEF }, "magenta", PREFIX ## magenta }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "maroon", PREFIX ## maroon }, \
    { { VERSION }, { HTML_UNDEF }, "mediumaquamarine", PREFIX ## mediumaquamarine }, \
    { { VERSION }, { HTML_UNDEF }, "mediumblue", PREFIX ## mediumblue }, \
    { { VERSION }, { HTML_UNDEF }, "mediumorchid", PREFIX ## mediumorchid }, \
    { { VERSION }, { HTML_UNDEF }, "mediumpurple", PREFIX ## mediumpurple }, \
    { { VERSION }, { HTML_UNDEF }, "mediumseagreen", PREFIX ## mediumseagreen }, \
    { { VERSION }, { HTML_UNDEF }, "mediumslateblue", PREFIX ## mediumslateblue }, \
    { { VERSION }, { HTML_UNDEF }, "mediumspringgreen", PREFIX ## mediumspringgreen }, \
    { { VERSION }, { HTML_UNDEF }, "mediumturquoise", PREFIX ## mediumturquoise }, \
    { { VERSION }, { HTML_UNDEF }, "mediumvioletred", PREFIX ## mediumvioletred }, \
    { { VERSION }, { HTML_UNDEF }, "midnightblue", PREFIX ## midnightblue }, \
    { { VERSION }, { HTML_UNDEF }, "mintcream", PREFIX ## mintcream }, \
    { { VERSION }, { HTML_UNDEF }, "mistyrose", PREFIX ## mistyrose }, \
    { { VERSION }, { HTML_UNDEF }, "moccasin", PREFIX ## moccasin }, \
    { { VERSION }, { HTML_UNDEF }, "navajowhite", PREFIX ## navajowhite }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "navy", PREFIX ## navy }, \
    { { VERSION }, { HTML_UNDEF }, "oldlace", PREFIX ## oldlace }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "olive", PREFIX ## olive }, \
    { { VERSION }, { HTML_UNDEF }, "olivedrab", PREFIX ## olivedrab }, \
    { { VERSION }, { HTML_UNDEF }, "orange", PREFIX ## orange }, \
    { { VERSION }, { HTML_UNDEF }, "orangered", PREFIX ## orangered }, \
    { { VERSION }, { HTML_UNDEF }, "orchid", PREFIX ## orchid }, \
    { { VERSION }, { HTML_UNDEF }, "palegoldenrod", PREFIX ## palegoldenrod }, \
    { { VERSION }, { HTML_UNDEF }, "palegreen", PREFIX ## palegreen }, \
    { { VERSION }, { HTML_UNDEF }, "paleturquoise", PREFIX ## paleturquoise }, \
    { { VERSION }, { HTML_UNDEF }, "palevioletred", PREFIX ## palevioletred }, \
    { { VERSION }, { HTML_UNDEF }, "papayawhip", PREFIX ## papayawhip }, \
    { { VERSION }, { HTML_UNDEF }, "peachpuff", PREFIX ## peachpuff }, \
    { { VERSION }, { HTML_UNDEF }, "peru", PREFIX ## peru }, \
    { { VERSION }, { HTML_UNDEF }, "pink", PREFIX ## pink }, \
    { { VERSION }, { HTML_UNDEF }, "plum", PREFIX ## plum }, \
    { { VERSION }, { HTML_UNDEF }, "powderblue", PREFIX ## powderblue }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "purple", PREFIX ## purple }, \
    { { VERSION }, { HTML_UNDEF }, "rebeccapurple ", PREFIX ## rebeccapurple  }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "red", PREFIX ## red }, \
    { { VERSION }, { HTML_UNDEF }, "rosybrown", PREFIX ## rosybrown }, \
    { { VERSION }, { HTML_UNDEF }, "royalblue", PREFIX ## royalblue }, \
    { { VERSION }, { HTML_UNDEF }, "saddlebrown", PREFIX ## saddlebrown }, \
    { { VERSION }, { HTML_UNDEF }, "salmon", PREFIX ## salmon }, \
    { { VERSION }, { HTML_UNDEF }, "sandybrown", PREFIX ## sandybrown }, \
    { { VERSION }, { HTML_UNDEF }, "seagreen", PREFIX ## seagreen }, \
    { { VERSION }, { HTML_UNDEF }, "seashell", PREFIX ## seashell }, \
    { { VERSION }, { HTML_UNDEF }, "sienna", PREFIX ## sienna }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "silver", PREFIX ## silver }, \
    { { VERSION }, { HTML_UNDEF }, "skyblue", PREFIX ## skyblue }, \
    { { VERSION }, { HTML_UNDEF }, "slateblue", PREFIX ## slateblue }, \
    { { VERSION }, { HTML_UNDEF }, "slategray", PREFIX ## slategray }, \
    { { VERSION }, { HTML_UNDEF }, "slategrey", PREFIX ## slategrey }, \
    { { VERSION }, { HTML_UNDEF }, "snow", PREFIX ## snow }, \
    { { VERSION }, { HTML_UNDEF }, "springgreen", PREFIX ## springgreen }, \
    { { VERSION }, { HTML_UNDEF }, "steelblue", PREFIX ## steelblue }, \
    { { VERSION }, { HTML_UNDEF }, "tan", PREFIX ## tan }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "teal", PREFIX ## teal }, \
    { { VERSION }, { HTML_UNDEF }, "thistle", PREFIX ## thistle }, \
    { { VERSION }, { HTML_UNDEF }, "tomato", PREFIX ## tomato }, \
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, "transparent", PREFIX ## transparent }, \
    { { VERSION }, { HTML_UNDEF }, "turquoise", PREFIX ## turquoise }, \
    { { VERSION }, { HTML_UNDEF }, "violet", PREFIX ## violet }, \
    { { VERSION }, { HTML_UNDEF }, "wheat", PREFIX ## wheat }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "white", PREFIX ## white }, \
    { { VERSION }, { HTML_UNDEF }, "whitesmoke", PREFIX ## whitesmoke }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "yellow", PREFIX ## yellow }, \
    { { VERSION }, { HTML_UNDEF }, "yellowgreen", PREFIX ## yellowgreen }

struct symbol_entry < html_version, e_css_colour > css_colour_symbol_table [] =
{   STANDARD_COLOURS (csc_, HTML_4_0),

    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "activeborder", csc_activeborder },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "activecaption", csc_activecaption },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "appworkspace", csc_appworkspace },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "background", csc_background },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "buttonface", csc_buttonface },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "buttonhighlight", csc_buttonhighlight },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "buttonshadow", csc_buttonshadow },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 | H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "buttontext", csc_buttontext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "captiontext", csc_captiontext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 | H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "graytext", csc_greytext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 | H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "highlight", csc_highlight },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 | H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "highlighttext", csc_highlighttext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "inactiveborder", csc_inactiveborder },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "inactivecaption", csc_inactivecaption },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "inactivecaptiontext", csc_inactivecaptiontext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "infobackground", csc_infobackground },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "infotext", csc_infotext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "menu", csc_menu },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "menutext", csc_menutext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "scrollbar", csc_scrollbar },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "threeddarkshadow", csc_threeddarkshadow },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "threedface", csc_threedface },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "threedhighlight", csc_threedhighlight },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "threedlightshadow", csc_threedlightshadow },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "threedshadow", csc_threedshadow },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "window", csc_window },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "windowframe", csc_windowframe },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_3 }, { HTML_UNDEF }, "windowtext", csc_windowtext },

    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "accentcolor", csc_accentcolour },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "accentcolortext", csc_accentcolourtext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "activetext", csc_activetext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "buttonborder", csc_buttonborder },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "canvas", csc_canvas },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "canvastext", csc_canvastext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "field", csc_field },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "fieldtext", csc_fieldtext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "linktext", csc_linktext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "mark", csc_mark },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "marktext", csc_marktext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "selecteditem", csc_selecteditem },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "selecteditemtext", csc_selecteditemtext },
    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "visitedtext", csc_visitedtext },

    { { HTML_CSS, 0, 0, 0, 0, H4_CSS_COLOUR_4 }, { HTML_UNDEF }, "currentcolor", csc_currentcolour } };

struct symbol_entry < html_version, e_fixedcolour > fixedcolour_symbol_table [] =
{    STANDARD_COLOURS (fc_, HTML_SVG10) };

void colour_init (nitpick& nits)
{   type_master < t_css_colour > :: init (nits, css_colour_symbol_table, sizeof (css_colour_symbol_table) / sizeof (symbol_entry < html_version, e_css_colour >));
    type_master < t_fixedcolour > :: init (nits, fixedcolour_symbol_table, sizeof (fixedcolour_symbol_table) / sizeof (symbol_entry < html_version, e_fixedcolour >)); }
