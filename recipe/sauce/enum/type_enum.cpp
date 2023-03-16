/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "css/flags.h"

#define STANDARD_COLOURS(PREFIX) \
    { { HTML_SVG10 }, { HTML_UNDEF }, "aliceblue", PREFIX ## aliceblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "antiquewhite", PREFIX ## antiquewhite }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "aqua", PREFIX ## aqua }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "aquamarine", PREFIX ## aquamarine }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "azure", PREFIX ## azure }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "beige", PREFIX ## beige }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "bisque", PREFIX ## bisque }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "black", PREFIX ## black }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "blanchedalmond", PREFIX ## blanchedalmond }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "blue", PREFIX ## blue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "blueviolet", PREFIX ## blueviolet }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "brown", PREFIX ## brown }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "burlywood", PREFIX ## burlywood }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "cadetblue", PREFIX ## cadetblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "chartreuse", PREFIX ## chartreuse }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "chocolate", PREFIX ## chocolate }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "coral", PREFIX ## coral }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "cornflowerblue", PREFIX ## cornflowerblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "cornsilk", PREFIX ## cornsilk }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "crimson", PREFIX ## crimson }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "cyan", PREFIX ## cyan }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkblue", PREFIX ## darkblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkcyan", PREFIX ## darkcyan }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkgoldenrod", PREFIX ## darkgoldenrod }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkgray", PREFIX ## darkgray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkgreen", PREFIX ## darkgreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkgrey", PREFIX ## darkgrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkkhaki", PREFIX ## darkkhaki }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkmagenta", PREFIX ## darkmagenta }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkolivegreen", PREFIX ## darkolivegreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkorange", PREFIX ## darkorange }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkorchid", PREFIX ## darkorchid }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkred", PREFIX ## darkred }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darksalmon", PREFIX ## darksalmon }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkseagreen", PREFIX ## darkseagreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkslateblue", PREFIX ## darkslateblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkslategray", PREFIX ## darkslategray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkslategrey", PREFIX ## darkslategrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkturquoise", PREFIX ## darkturquoise }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "darkviolet", PREFIX ## darkviolet }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "deeppink", PREFIX ## deeppink }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "deepskyblue", PREFIX ## deepskyblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "dimgray", PREFIX ## dimgray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "dimgrey", PREFIX ## dimgrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "dodgerblue", PREFIX ## dodgerblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "firebrick", PREFIX ## firebrick }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "floralwhite", PREFIX ## floralwhite }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "forestgreen", PREFIX ## forestgreen }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "fuchsia", PREFIX ## fuchsia }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "gainsboro", PREFIX ## gainsboro }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "ghostwhite", PREFIX ## ghostwhite }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "gold", PREFIX ## gold }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "goldenrod", PREFIX ## goldenrod }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "gray", PREFIX ## grey }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "green", PREFIX ## green }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "greenyellow", PREFIX ## greenyellow }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "honeydew", PREFIX ## honeydew }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "hotpink", PREFIX ## hotpink }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "indianred", PREFIX ## indianred }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "indigo", PREFIX ## indigo }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "ivory", PREFIX ## ivory }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "khaki", PREFIX ## khaki }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lavender", PREFIX ## lavender }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lavenderblush", PREFIX ## lavenderblush }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lawngreen", PREFIX ## lawngreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lemonchiffon", PREFIX ## lemonchiffon }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightblue", PREFIX ## lightblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightcoral", PREFIX ## lightcoral }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightcyan", PREFIX ## lightcyan }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightgoldenrodyellow", PREFIX ## lightgoldenrodyellow }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightgray", PREFIX ## lightgray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightgreen", PREFIX ## lightgreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightgrey", PREFIX ## lightgrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightpink", PREFIX ## lightpink }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightsalmon", PREFIX ## lightsalmon }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightseagreen", PREFIX ## lightseagreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightskyblue", PREFIX ## lightskyblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightslategray", PREFIX ## lightslategray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightslategrey", PREFIX ## lightslategrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightsteelblue", PREFIX ## lightsteelblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "lightyellow", PREFIX ## lightyellow }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "lime", PREFIX ## lime }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "limegreen", PREFIX ## limegreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "linen", PREFIX ## linen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "magenta", PREFIX ## magenta }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "maroon", PREFIX ## maroon }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumaquamarine", PREFIX ## mediumaquamarine }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumblue", PREFIX ## mediumblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumorchid", PREFIX ## mediumorchid }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumpurple", PREFIX ## mediumpurple }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumseagreen", PREFIX ## mediumseagreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumslateblue", PREFIX ## mediumslateblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumspringgreen", PREFIX ## mediumspringgreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumturquoise", PREFIX ## mediumturquoise }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mediumvioletred", PREFIX ## mediumvioletred }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "midnightblue", PREFIX ## midnightblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mintcream", PREFIX ## mintcream }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "mistyrose", PREFIX ## mistyrose }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "moccasin", PREFIX ## moccasin }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "navajowhite", PREFIX ## navajowhite }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "navy", PREFIX ## navy }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "oldlace", PREFIX ## oldlace }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "olive", PREFIX ## olive }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "olivedrab", PREFIX ## olivedrab }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "orange", PREFIX ## orange }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "orangered", PREFIX ## orangered }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "orchid", PREFIX ## orchid }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "palegoldenrod", PREFIX ## palegoldenrod }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "palegreen", PREFIX ## palegreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "paleturquoise", PREFIX ## paleturquoise }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "palevioletred", PREFIX ## palevioletred }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "papayawhip", PREFIX ## papayawhip }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "peachpuff", PREFIX ## peachpuff }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "peru", PREFIX ## peru }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "pink", PREFIX ## pink }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "plum", PREFIX ## plum }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "powderblue", PREFIX ## powderblue }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "purple", PREFIX ## purple }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "rebeccapurple ", PREFIX ## rebeccapurple  }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "red", PREFIX ## red }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "rosybrown", PREFIX ## rosybrown }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "royalblue", PREFIX ## royalblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "saddlebrown", PREFIX ## saddlebrown }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "salmon", PREFIX ## salmon }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "sandybrown", PREFIX ## sandybrown }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "seagreen", PREFIX ## seagreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "seashell", PREFIX ## seashell }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "sienna", PREFIX ## sienna }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "silver", PREFIX ## silver }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "skyblue", PREFIX ## skyblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "slateblue", PREFIX ## slateblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "slategray", PREFIX ## slategray }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "slategrey", PREFIX ## slategrey }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "snow", PREFIX ## snow }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "springgreen", PREFIX ## springgreen }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "steelblue", PREFIX ## steelblue }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "tan", PREFIX ## tan }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "teal", PREFIX ## teal }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "thistle", PREFIX ## thistle }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "tomato", PREFIX ## tomato }, \
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, "transparent", PREFIX ## transparent }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "turquoise", PREFIX ## turquoise }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "violet", PREFIX ## violet }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "wheat", PREFIX ## wheat }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "white", PREFIX ## white }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "whitesmoke", PREFIX ## whitesmoke }, \
    { { HTML_2_0 }, { HTML_UNDEF }, "yellow", PREFIX ## yellow }, \
    { { HTML_SVG10 }, { HTML_UNDEF }, "yellowgreen", PREFIX ## yellowgreen }

struct symbol_entry < html_version, e_accrual_method > accrual_method_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:deposit", am_deposit },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:donation", am_donation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:purchase", am_purchase },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:loan", am_loan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:license", am_licence },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:itemcreation", am_item_creation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/deposit", am_deposit },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/donation", am_donation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/purchase", am_purchase },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/loan", am_loan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/license", am_licence },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/itemcreation", am_item_creation } };

struct symbol_entry < html_version, e_accrual_periodicity > accrual_periodicity_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "freq:triennial", ap_triennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:biennial", ap_biennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:annual", ap_annual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semiannual", ap_semiannual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAYear", ap_thriceyearly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:quarterly", ap_quarterly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:bimonthly", ap_bimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:monthly", ap_monthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semimonthly", ap_semimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:biweekly", ap_biweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAMonth", ap_thricemonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:weekly", ap_weekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semiweekly", ap_semiweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAWeek", ap_thriceweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:daily", ap_daily },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:continuous", ap_continuous },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:irregular", ap_irregular },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/triennial", ap_triennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/biennial", ap_biennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/annual", ap_annual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semiannual", ap_semiannual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAYear", ap_thriceyearly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/quarterly", ap_quarterly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/bimonthly", ap_bimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/monthly", ap_monthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semimonthly", ap_semimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/biweekly", ap_biweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAMonth", ap_thricemonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/weekly", ap_weekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semiweekly", ap_semiweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAWeek", ap_thriceweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/daily", ap_daily },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/continuous", ap_continuous },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/irregular", ap_irregular } };

struct symbol_entry < html_version, e_accrual_policy > accrual_policy_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:closed", ap_closed },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:passive", ap_active },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:active", ap_passive },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:partial", ap_partial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/closed", ap_closed },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/passive", ap_active },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/active", ap_passive },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/partial ", ap_partial } };

struct symbol_entry < html_version, e_action > action_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "sell", av_sell },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rent", av_rent },
    { { HTML_UNDEF }, { HTML_UNDEF }, "trade", av_trade },
    { { HTML_UNDEF }, { HTML_UNDEF }, "meet", av_meet },
    { { HTML_UNDEF }, { HTML_UNDEF }, "announce", av_announce },
    { { HTML_UNDEF }, { HTML_UNDEF }, "offer", av_offer },
    { { HTML_UNDEF }, { HTML_UNDEF }, "wanted", av_wanted },
    { { HTML_UNDEF }, { HTML_UNDEF }, "event", av_event },
    { { HTML_UNDEF }, { HTML_UNDEF }, "service", av_service } };

struct symbol_entry < html_version, e_align3 > align3_symbol_table [] =
{   { { HTML_3_0 }, { HTML_UNDEF }, "top", a3_top },
    { { HTML_3_0 }, { HTML_UNDEF }, "middle", a3_middle },
    { { HTML_3_0 }, { HTML_UNDEF }, "bottom", a3_bottom },
    { { HTML_3_0 }, { HTML_UNDEF }, "left", a3_left },
    { { HTML_3_0 }, { HTML_UNDEF }, "right", a3_right } };

struct symbol_entry < html_version, e_alignment_baseline > alignment_baseline_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "after-edge", ab_afteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "alphabetic", ab_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "auto",  ab_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "baseline", ab_baseline },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "before-edge", ab_beforeedge },
    { { HTML_SVG10, 0, HE_SVG_10 | HE_SVG_DEPR_10 }, { HTML_UNDEF }, "bottom", ab_bottom },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "central", ab_central },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "hanging", ab_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "ideographic", ab_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "inherit", ab_inherit },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "mathematical", ab_mathematical },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "middle", ab_middle },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "text-after-edge", ab_textafteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "text-before-edge", ab_textbeforeedge },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "text-bottom", ab_textbottom },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "text-top", ab_texttop },
    { { HTML_SVG10, 0, HE_SVG_10 | HE_SVG_DEPR_10 }, { HTML_UNDEF }, "top", ab_top } };

struct symbol_entry < html_version, e_alignplus > alignplus_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "center", ap_centre },
    { { HTML_PLUS }, { HTML_PLUS }, "indent", ap_indent },
    { { HTML_PLUS }, { HTML_PLUS }, "justify", ap_justify },
    { { HTML_PLUS }, { HTML_PLUS }, "left", ap_left },
    { { HTML_PLUS }, { HTML_PLUS }, "right", ap_right } };

struct symbol_entry < html_version, e_as > as_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "audio", as_audio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "document", as_document },
    { { HTML_JAN05 }, { HTML_UNDEF }, "embed", as_embed },
    { { HTML_JAN05 }, { HTML_UNDEF }, "fetch", as_fetch },
    { { HTML_JAN05 }, { HTML_UNDEF }, "font", as_font },
    { { HTML_JAN05 }, { HTML_UNDEF }, "image", as_image },
    { { HTML_JAN05 }, { HTML_UNDEF }, "object", as_object },
    { { HTML_JAN05 }, { HTML_UNDEF }, "script", as_script },
    { { HTML_JAN05 }, { HTML_UNDEF }, "style", as_style },
    { { HTML_JAN05 }, { HTML_UNDEF }, "track", as_track },
    { { HTML_JAN05 }, { HTML_UNDEF }, "video", as_video },
    { { HTML_JAN05 }, { HTML_UNDEF }, "worker", as_worker } };

struct symbol_entry < html_version, e_as_units > as_units_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "cm", asu_cm },
    { { HTML_JAN05 }, { HTML_UNDEF }, "feet", asu_feet },
    { { HTML_JAN05 }, { HTML_UNDEF }, "asu_inches", asu_inches },
    { { HTML_JAN05 }, { HTML_UNDEF }, "km", asu_km },
    { { HTML_JAN05 }, { HTML_UNDEF }, "m", asu_m },
    { { HTML_JAN05 }, { HTML_UNDEF }, "miles", asu_miles } };

struct symbol_entry < html_version, e_autocapitalise > autocapitalise_symbol_table [] =
{   { { HTML_5_3 }, { HTML_UNDEF }, "characters", ac4_characters },
    { { HTML_JUL20 }, { HTML_UNDEF }, "default", ec4_default },
    { { HTML_JUL20 }, { HTML_UNDEF }, "none", ac4_none },
    { { HTML_5_3 }, { HTML_UNDEF }, "sentences", ac4_sentences },
    { { HTML_5_3 }, { HTML_UNDEF }, "words", ac4_words } };

struct symbol_entry < html_version, e_autocomplete > autocomplete_symbol_table [] =
{   { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "additional-name", aco_additional_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level1", aco_address_level1 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level2", aco_address_level2 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level3", aco_address_level3 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level4", aco_address_level4 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line1", aco_address_line1 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line2", aco_address_line2 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line3", aco_address_line3 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday", aco_bday },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-day", aco_bday_day },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-month", aco_bday_month },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-year", aco_bday_year },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "billing", aco_billing },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-additional-name", aco_cc_additional_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-csc", aco_cc_csc },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp", aco_cc_exp },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp-month", aco_cc_exp_month },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp-year", aco_cc_exp_year },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-family-name", aco_cc_family_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-given-name", aco_cc_given_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-name", aco_cc_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-number", aco_cc_number },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-type", aco_cc_type },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "country", aco_country },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "country-name", aco_country_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "current-password", aco_current_password },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "email", aco_email },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "family-name", aco_family_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "fax", aco_fax },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "given-name", aco_given_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "home", aco_home },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "honorific-prefix", aco_honorific_prefix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "honorific-suffix", aco_honorific_suffix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "impp", aco_impp },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "language", aco_language },
    { { HTML_JAN13 }, { HTML_DEC14 }, "locality", aco_locality },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "mobile", aco_mobile },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "name", aco_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "new-password", aco_new_password },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "nickname", aco_nickname },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "off", aco_off },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "on", aco_on },
    { { HTML_JAN20 }, { HTML_UNDEF }, "one-time-code", aco_one_time_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "organization", aco_organization },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "organization-title", aco_organization_title },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "pager", aco_pager },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "photo", aco_photo },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "postal-code", aco_postal_code },
    { { HTML_JAN13 }, { HTML_DEC14 }, "region", aco_region },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "sex", aco_sex },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "shipping", aco_shipping },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "street-address", aco_street_address },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel", aco_tel },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-area-code", aco_tel_area_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-country-code", aco_tel_country_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-extension", aco_tel_extension },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local", aco_tel_local },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local-prefix", aco_tel_local_prefix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local-suffix", aco_tel_local_suffix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-national", aco_tel_national },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "transaction-amount", aco_transaction_amount },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "transaction-currency", aco_transaction_currency },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "url", aco_url },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "username", aco_username },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "work", aco_work } };

struct symbol_entry < html_version, e_baselineshift > baselineshift_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "baseline", bsb_baseline },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "bottom", bsb_bottom },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "center", bsb_centre },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "top", bsb_top },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "sub", bsb_sub },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "super", bsb_super },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", bsb_inherit } };

struct symbol_entry < html_version, e_cachekey > cachekey_symbol_table [] =
{   { { HTML_JAN15 }, { HTML_UNDEF }, "max-age", ck_maxage },
    { { HTML_JAN15 }, { HTML_UNDEF }, "max-stale", ck_maxstale },
    { { HTML_JAN15 }, { HTML_UNDEF }, "min-fresh", ck_minfresh },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-cache", ck_nocache },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-store", ck_nostore },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-transform", ck_notransform },
    { { HTML_JAN15 }, { HTML_UNDEF }, "only-if-cached", ck_onlyifcached } };

struct symbol_entry < html_version, e_citype > citype_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "integer", ci_integer },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rational", ci_rational },
    { { XHTML_1_0 }, { HTML_UNDEF }, "real", ci_real },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-polar", ci_complexpolar },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-cartesian", ci_complexcartesian },
    { { XHTML_1_0 }, { HTML_UNDEF }, "constant", ci_constant },
    { { HTML_5_2 }, { HTML_UNDEF }, "complex", ci_complex },
    { { HTML_5_2 }, { HTML_UNDEF }, "function", ci_function },
    { { HTML_5_2 }, { HTML_UNDEF }, "vector", ci_vector },
    { { HTML_5_2 }, { HTML_UNDEF }, "list", ci_list },
    { { HTML_5_2 }, { HTML_UNDEF }, "set", ci_set },
    { { HTML_5_2 }, { HTML_UNDEF }, "matrix", ci_matrix } };

struct symbol_entry < html_version, e_colour_interpolation > colour_interpolation_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", ci_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "sRGB", ci_srgb },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "linearRGB", ci_linearrgb },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", ci_inherit } };

struct symbol_entry < html_version, e_colour_rendering > colour_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", cr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", cr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimiseQuality", cr_optimisequality },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", cr_inherit } };

struct symbol_entry < html_version, e_cookieid > cookieid_symbol_table [] =
{   { { HTML_JAN15 }, { HTML_UNDEF }, "expires", coo_expires },
    { { HTML_JAN15 }, { HTML_UNDEF }, "max-age", coo_maxage },
    { { HTML_JAN15 }, { HTML_UNDEF }, "domain", coo_domain },
    { { HTML_JAN15 }, { HTML_UNDEF }, "path", coo_path },
    { { HTML_JAN15 }, { HTML_UNDEF }, "secure", coo_secure },
    { { HTML_JAN15 }, { HTML_UNDEF }, "httponly", coo_httponly } };

struct symbol_entry < html_version, e_comp_op > comp_op_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "clear",  cop_clear },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src", cop_src },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst", cop_dst },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-over", cop_src_over },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-over", cop_dst_over },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-in", cop_src_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-in", cop_dst_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-out", cop_src_out },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-out", cop_dst_out },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-atop", cop_src_atop },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-atop", cop_dst_atop },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "xor", cop_xor },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "plus", cop_plus },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "multiply", cop_multiply },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "screen", cop_screen },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "overlay", cop_overlay },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "darken", cop_darken },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "lighten", cop_lighten },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "color-dodge", cop_colour_dodge },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "color-burn", cop_colour_burn },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "hard-light", cop_hard_light },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "soft-light", cop_soft_light },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "difference", cop_difference },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "inherit", cop_inherit } };

struct symbol_entry < html_version, e_composite_operator > composite_operator_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "arithmetic",  co_arithmetic },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "atop", co_atop },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "in", co_in },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "lighter", co_lighter },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "out", co_out },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "over", co_over },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "xor", co_xor } };

struct symbol_entry < html_version, e_cntype > cntype_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "double", cn_double },
    { { XHTML_1_0 }, { HTML_UNDEF }, "e-notation", cn_enotation },
    { { HTML_5_2 }, { HTML_UNDEF }, "hexdouble", cn_hexdouble },
    { { XHTML_1_0 }, { HTML_UNDEF }, "integer", cn_integer },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rational", cn_rational },
    { { XHTML_1_0 }, { HTML_UNDEF }, "real", cn_real },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-polar", cn_complexpolar },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-cartesian", cn_complexcartesian },
    { { XHTML_1_0 }, { HTML_UNDEF }, "constant", cn_constant } };

struct symbol_entry < html_version, e_crossout > crossout_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "none", co_none },
    { { HTML_5_2 }, { HTML_UNDEF }, "updiagonalstrike", co_updiagonalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "downdiagonalstrike", co_downdiagonalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "verticalstrike", co_verticalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "horizontalstrike", co_horizontalstrike } };

struct symbol_entry < html_version, e_css_aaalri > css_aaalri_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "always", caa_always },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "auto", caa_auto },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "avoid", caa_avoid },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", caa_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "left", caa_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "right", caa_right } };

struct symbol_entry < html_version, e_css_absolute_size > css_absolute_size_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecas_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "xx-small", eca_xx_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "x-small", eca_x_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "small", eca_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "medium", eca_medium },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "large", eca_large },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "x-large", eca_x_large },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "xx-large", eca_xx_large } };

struct symbol_entry < html_version, e_css_azimuth_e > css_azimuth_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "center", cae_centre },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "center-left", cae_centre_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "center-right", cae_centre_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "far-left", cae_far_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "far-right", cae_far_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "left", cae_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "left-side", cae_left_side },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "right", cae_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "right-side", cae_right_side } };

struct symbol_entry < html_version, e_css_background_attachment > css_background_attachment_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecba_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "fixed", ecba_fixed },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "scroll", ecba_scroll } };

struct symbol_entry < html_version, e_css_background_repeat > css_background_repeat_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecbr_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "no-repeat", ecbr_no_repeat },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat", ecbr_repeat },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat-x", ecbr_repeat_x },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat-y", ecbr_repeat_y } };

struct symbol_entry < html_version, e_css_border_style > css_border_style_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecbs_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "dashed", ecb_dashed },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "dotted", ecb_dotted },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "double", ecb_double },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "groove", ecb_groove },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hidden", ecb_hidden },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inset", ecb_inset },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecb_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "outset", ecb_outset },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "ridge", ecb_ridge },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "solid", ecb_solid } };

struct symbol_entry < html_version, e_css_border_width > css_border_width_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecb_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "medium", ecb_medium },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "thick", ecb_thick },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "thin", ecb_thin } };

struct symbol_entry < html_version, e_css_clear > css_clear_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecc_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "both", ecc_both },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecc_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecc_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecc_right } };

struct symbol_entry < html_version, e_css_colour > css_colour_symbol_table [] =
{   STANDARD_COLOURS (csc_),
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "activeborder", csc_activeborder },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "activecaption", csc_activecaption },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "appworkspace", csc_appworkspace },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "background", csc_background },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "buttonface", csc_buttonface },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "buttonhighlight", csc_buttonhighlight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "buttonshadow", csc_buttonshadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "buttontext", csc_buttontext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "captiontext", csc_captiontext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "graytext", csc_graytext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "highlight", csc_highlight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "highlighttext", csc_highlighttext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inactiveborder", csc_inactiveborder },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inactivecaption", csc_inactivecaption },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inactivecaptiontext", csc_inactivecaptiontext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "infobackground", csc_infobackground },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "infotext", csc_infotext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "menu", csc_menu },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "menutext", csc_menutext },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scrollbar", csc_scrollbar },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "threeddarkshadow", csc_threeddarkshadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "threedface", csc_threedface },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "threedhighlight", csc_threedhighlight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "threedlightshadow", csc_threedlightshadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "threedshadow", csc_threedshadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "window", csc_window },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "windowframe", csc_windowframe },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "windowtext", csc_windowtext } };

struct symbol_entry < html_version, e_css_content_enum > css_content_enum_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "attr", econ_attr },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "close-quote", econ_close_quote },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "counter", econ_counter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "counters", econ_counters },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", econ_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "open-quote", econ_open_quote },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "no-close-quote", econ_no_close_quote },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "no-open-quote", econ_no_open_quote },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "url", econ_url } };

struct symbol_entry < html_version, e_css_cursor_e > css_cursor_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "auto", ece_auto },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "crosshair", ece_crosshair },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "default", ece_default },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "help", ece_help },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "move", ece_move },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "pointer", ece_pointer },
    { { HTML_CSS, 0, 0, H2_CSS_21_PLUS }, { HTML_UNDEF }, "progress", ece_progress },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text", ece_text },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wait", ece_wait },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "e-resize", ece_e_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "ne-resize", ece_ne_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "nw-resize", ece_nw_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "n-resize", ece_n_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "se-resize", ece_se_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "sw-resize", ece_sw_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "s-resize", ece_s_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "w-resize", ece_w_resize } };

struct symbol_entry < html_version, e_css_display > css_display_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "block", ecd_block },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "compact", ecd_compact },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecd_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inline", ecd_inline },
    { { HTML_CSS, 0, 0, H2_CSS_21_PLUS }, { HTML_UNDEF }, "inline-block", ecd_inline_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inline-table", ecd_inline_table },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-item", ecd_list_item },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "marker", ecd_marker },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecd_none },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "run-in", ecd_run_in },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table", ecd_table },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-caption", ecd_table_caption },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-cell", ecd_table_cell },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-column", ecd_table_column },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-column-group", ecd_table_column_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-footer-group", ecd_table_footer_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-header-group", ecd_table_header_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-row", ecd_table_row },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-row-group", ecd_table_row_group } };

struct symbol_entry < html_version, e_css_elevation_e > css_elevation_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "above", cee_above },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "below", cee_below },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "higher", cee_higher },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", cee_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "level", cee_level },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "lower", cee_lower } };

struct symbol_entry < html_version, e_css_float > css_float_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecf_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecf_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecf_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecf_right } };

struct symbol_entry < html_version, e_css_font_weight > css_font_weight_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "all",  ecfw_all },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "normal",  ecfw_normal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bold", ecfw_bold },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bolder", ecfw_bolder },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lighter", ecfw_lighter },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "100", ecfw_100 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "200", ecfw_200 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "300", ecfw_300 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "400", ecfw_400 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "500", ecfw_500 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "600", ecfw_600 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "700", ecfw_700 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "800", ecfw_800 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "900", ecfw_900 },
    { { HTML_CSS, 0, 0, H2_CSS_2_PLUS }, { HTML_UNDEF }, "inherit", ecfw_inherit } };

struct symbol_entry < html_version, e_css_fn > css_fn_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "(unknown)", efn_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "active", efn_active },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "after", efn_after },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "any-link", efn_any_link },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "autofill", efn_autofill },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "backdrop", efn_backdrop },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "before", efn_before },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "blank", efn_blank },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "checked", efn_checked },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "cue", efn_cue },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "cue-region", efn_cue_region },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "current", efn_current },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "default", efn_default },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "defined", efn_defined },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "dir", efn_dir },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "disabled", efn_disabled },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "empty", efn_empty },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "enabled", efn_enabled, },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "file-selector-button", efn_file_selector_button },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "first", efn_first, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "first-child", efn_first_child },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "first-letter", efn_first_letter },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "first-line", efn_first_line },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "first-of-type", efn_first_of_type },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "focus", efn_focus },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "focus-visible", efn_focus_visible },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "focus-within", efn_focus_within },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "fullscreen", efn_fullscreen },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "future", efn_future },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "grammar-error", efn_grammar_error },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "has", efn_has },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "host", efn_host },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "host-context", efn_host_context },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "hover", efn_hover, },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "indeterminate", efn_indeterminate },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "in-range", efn_in_range },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "invalid", efn_invalid },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "is", efn_is },
    { { HTML_CSS, 0, 0, H2_CSS_1_2_ARGS }, { HTML_UNDEF }, "lang", efn_lang },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "last-child", efn_last_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "last-of-type", efn_last_of_type },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", efn_left, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "link", efn_link },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "local_link", efn_local_link },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "marker", efn_marker },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "modal", efn_modal },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "not", efn_not },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-child", efn_nth_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-col", efn_nth_col, },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-child", efn_nth_last_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-col", efn_nth_last_col },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-of-type", efn_nth_last_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-of-type", efn_nth_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "only-child", efn_only_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "only-of-type", efn_only_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "optional", efn_optional },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "out-of-range", efn_out_of_range },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "paused", efn_paused },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "part", efn_part },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "past", efn_past },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "picture-in-picture", efn_picture_in_picture },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "placeholder", efn_placeholder },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "placeholder-shown", efn_placeholder_shown },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "playing", efn_playing },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "read-only", efn_read_only },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "read-write", efn_read_write },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "required", efn_required },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", efn_right, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "root", efn_root },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "scope", efn_scope },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "selection", efn_selection },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "slotted", efn_slotted },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "spelling-error", efn_spelling_error },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "state", efn_state },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "target", efn_target },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "target-text", efn_target_text },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "target-within", efn_target_within },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "user-invalid", efn_user_invalid, },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "valid", efn_valid },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "visited", efn_visited },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "where", efn_where } };

struct symbol_entry < html_version, e_css_generic_family > css_generic_family_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecgf_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "cursive", ecf_cursive },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "fantasy", ecf_fantasy },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "monospace", ecf_monospace },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "sans-serif", ecf_sans_serif },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "serif", ecf_serif } };

struct symbol_entry < html_version, e_css_list_style_position > css_list_style_position_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", eclp_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inside", ecp_inside },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "outside", ecp_outside } };

struct symbol_entry < html_version, e_css_list_style_type > css_list_style_type_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecls_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "circle", ecl_circle },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "decimal", ecl_decimal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "disc", ecl_disc },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lower-alpha", ecl_lower_alpha },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lower-roman", ecl_lower_roman },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecl_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "square", ecl_square },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "upper-alpha", ecl_upper_alpha },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "upper-roman", ecl_upper_roman },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hebrew", ecl_hebrew },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "armenian", ecl_armenian },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "georgian", ecl_georgian },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "cjk-ideographic", ecl_cjk_ideographic },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hiragana", ecl_hiragana },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "katakana", ecl_katakana },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hira-gana-iroha", ecl_hira_gana_iroha },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "katakana-iroha", ecl_katakana_iroha } };

struct symbol_entry < html_version, e_css_overflow > css_overflow_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "auto", eco_auto },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hidden", eco_hidden },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", eco_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll", eco_scroll },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "visible", eco_visible } };

struct symbol_entry < html_version, e_css_pitch_e > css_pitch_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "high", epi_high },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", epi_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "low", epi_low },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "medium", epi_medium },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-high", epi_x_high },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-low", epi_x_low } };

struct symbol_entry < html_version, e_css_position > css_position_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "absolute", ecp_absolute },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "fixed", ecp_fixed },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecp_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "relative", ecp_relative },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "static", ecp_static } };

struct symbol_entry < html_version, e_css_property > css_property_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "accent-color", ec_accent_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "align-content", ec_align_content },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "align-items", ec_align_items },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "align-self", ec_align_self },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "alignment-baseline", ec_alignment_baseline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "and", ec_and },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation", ec_animation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-composition", ec_animation_composition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-delay", ec_animation_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-delay-end", ec_animation_delay_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-delay-start", ec_animation_delay_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-direction", ec_animation_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-duration", ec_animation_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-fill-mode", ec_animation_fill_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-iteration-count", ec_animation_iteration_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-name", ec_animation_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-play-state", ec_animation_play_state },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-range", ec_animation_range },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-timeline", ec_animation_timeline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "animation-timing-function", ec_animation_timing_function },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "ascent", ec_ascent, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "aspect-ratio", ec_aspect_ratio },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "azimuth", ec_azimuth, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "backface-visibility", ec_backface_visibility },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background", ec_background, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background-attachment", ec_background_attachment, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background-color", ec_background_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background-image", ec_background_image, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background-position", ec_background_position, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "background-repeat", ec_background_repeat, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "baseline", ec_baseline, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "baseline-shift", ec_baseline_shift },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "baseline-source", ec_baseline_source },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "bbox", ec_bbox, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-ellipsis", ec_block_ellipsis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-step", ec_block_step },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-step-align", ec_block_step_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-step-insert", ec_block_step_insert },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-step-round", ec_block_step_round },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "block-step-size", ec_block_step_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "bookmark-label", ec_bookmark_label },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "bookmark-level", ec_bookmark_level },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "bookmark-state", ec_bookmark_state },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border", ec_border, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-bottom", ec_border_bottom, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-bottom-color", ec_border_bottom_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-bottom-style", ec_border_bottom_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-bottom-width", ec_border_bottom_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-boundary", ec_border_boundary },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-collapse", ec_border_collapse, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-color", ec_border_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-left", ec_border_left, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-left-color", ec_border_left_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-left-style", ec_border_left_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-left-width", ec_border_left_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-right", ec_border_right, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-right-color", ec_border_right_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-right-style", ec_border_right_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-right-width", ec_border_right_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-spacing", ec_border_spacing, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-style", ec_border_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-top", ec_border_top, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-top-color", ec_border_top_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "border-top-style", ec_border_top_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-top-width", ec_border_top_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "border-width", ec_border_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "bottom", ec_bottom, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "box-decoration-break", ec_box_decoration_break },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "box-sizing", ec_box_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "box-snap", ec_box_snap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "break-after", ec_break_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "break-before", ec_break_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "break-inside", ec_break_inside },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "cap-height", ec_cap_height, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "caption-side", ec_caption_side, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "caret", ec_caret },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "caret-color", ec_caret_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "caret-shape", ec_caret_shape },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "center-line", ec_centre_line, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "chains", ec_chains },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "clear", ec_clear, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "clip", ec_clip, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "clip-path", ec_clip_path },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "clip-rule", ec_clip_rule },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "color", ec_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "color-adjust", ec_colour_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "color-interpolation-filters", ec_colour_interpolation_filters },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "color-scheme", ec_colour_scheme },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-count", ec_column_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-fill", ec_column_fill },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-gap", ec_column_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-rule", ec_column_rule },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-rule-color", ec_column_rule_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-rule-style", ec_column_rule_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-rule-width", ec_column_rule_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-span", ec_column_span },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "column-width", ec_column_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "columns", ec_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain", ec_contain },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain-intrinsic-block-size", ec_contain_intrinsic_block_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain-intrinsic-height", ec_contain_intrinsic_height },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain-intrinsic-inline-size", ec_contain_intrinsic_inline_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain-intrinsic-size", ec_contain_intrinsic_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "contain-intrinsic-width", ec_contain_intrinsic_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "container", ec_container },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "container-name", ec_container_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "container-type", ec_container_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "content", ec_content, ns_default, CF_BEF_AFT },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "content-visibility", ec_content_visibility },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "continue", ec_continue },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "counter-increment", ec_counter_increment, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "counter-reset", ec_counter_reset, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "cue", ec_cue, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "cue-after", ec_cue_after, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "cue-before", ec_cue_before, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "cursor", ec_cursor, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "definition-src", ec_definition_src, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "descent", ec_descent, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "direction", ec_direction, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "display", ec_display, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "dominant-baseline", ec_dominant_baseline },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "elevation", ec_elevation, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "empty-cells", ec_empty_cells, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "filter", ec_filter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex", ec_flex },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-basis", ec_flex_basis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-direction", ec_flex_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-flow", ec_flex_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-grow", ec_flex_grow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-shrink", ec_flex_shrink },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flex-wrap", ec_flex_wrap },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "float", ec_float, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "float-defer", ec_float_defer },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "float-offset", ec_float_offset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "float-reference", ec_float_reference },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flood-color", ec_flood_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flood-opacity", ec_flood_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flow", ec_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flow-from", ec_flow_from },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "flow-into", ec_flow_into },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font", ec_font },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font-family", ec_font_family, ns_default, CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-feature-settings", ec_font_feature_settings },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-kerning", ec_font_kerning },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-language-override", ec_font_language_override },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-optical-sizing", ec_font_optical_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-palette", ec_font_palette },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font-size", ec_font_size, ns_default, CF_NOT_STRING | CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2 }, { HTML_UNDEF }, "font-size-adjust", ec_font_size_adjust, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2 }, { HTML_UNDEF }, "font-stretch", ec_font_stretch, ns_default, CF_EXPECT_KEYWORDS | CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font-style", ec_font_style, ns_default, CF_EXPECT_KEYWORDS | CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-synthesis", ec_font_synthesis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-synthesis-small-caps", ec_font_synthesis_small_caps },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-synthesis-style", ec_font_synthesis_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-synthesis-weight", ec_font_synthesis_weight },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font-variant", ec_font_variant, ns_default, CF_EXPECT_KEYWORDS | CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-alternates", ec_font_variant_alternates },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-caps", ec_font_variant_caps },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-east-asian", ec_font_variant_east_asian },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-emoji", ec_font_variant_emoji },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-ligatures", ec_font_variant_ligatures },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-numeric", ec_font_variant_numeric },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variant-position", ec_font_variant_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "font-variation-settings", ec_font_variation_settings },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "font-weight", ec_font_weight, ns_default, CF_EXPECT_KEYWORDS | CF_MAY_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "for", ec_for },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "forced-color-adjust", ec_forced_colour_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "gap", ec_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "glyph-orientation-vertical", ec_glyph_orientation_vertical },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid", ec_grid },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-area", ec_grid_area },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-auto-columns", ec_grid_auto_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-auto-flow", ec_grid_auto_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-auto-rows", ec_grid_auto_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-column", ec_grid_column },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-column-end", ec_grid_column_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-column-start", ec_grid_column_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-row", ec_grid_row },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-row-end", ec_grid_row_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-row-start", ec_grid_row_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-template", ec_grid_template },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-template-areas", ec_grid_template_areas },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-template-columns", ec_grid_template_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "grid-template-rows", ec_grid_template_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hanging-punctuation", ec_hanging_punctuation },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "height", ec_height, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphenate-character", ec_hyphenate_character },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphenate-limit-chars", ec_hyphenate_limit_chars },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphenate-limit-last", ec_hyphenate_limit_last },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphenate-limit-lines", ec_hyphenate_limit_lines },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphenate-limit-zone", ec_hyphenate_limit_zone },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "hyphens", ec_hyphens },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "image-orientation", ec_image_orientation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "image-rendering", ec_image_rendering },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "image-resolution", ec_image_resolution },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "initial-letter", ec_initial_letter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "initial-letter-align", ec_initial_letter_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "initial-letter-wrap", ec_initial_letter_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inline-sizing", ec_inline_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset", ec_inset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-block", ec_inset_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-block-end", ec_inset_block_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-block-start", ec_inset_block_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-inline", ec_inset_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-inline-end", ec_inset_inline_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inset-inline-start", ec_inset_inline_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "justify-content", ec_justify_content },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "justify-items", ec_justify_items },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "justify-self", ec_justify_self },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "leading-trim", ec_leading_trim },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "left", ec_left, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "letter-spacing", ec_letter_spacing, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "lighting-color", ec_lighting_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-break", ec_line_break },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-clamp", ec_line_clamp },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-grid", ec_line_grid },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "line-height", ec_line_height, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-height-step", ec_line_height_step },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-padding", ec_line_padding },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "line-snap", ec_line_snap },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-style", ec_list_style, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-style-image", ec_list_style_image, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-style-position", ec_list_style_position, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-style-type", ec_list_style_type, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "margin", ec_margin, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "margin-bottom", ec_margin_bottom, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "margin-break", ec_margin_break },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "margin-left", ec_margin_left, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "margin-right", ec_margin_right, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "margin-top", ec_margin_top, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "margin-trim", ec_margin_trim },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker", ec_marker },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-end", ec_marker_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-knockout-left", ec_marker_knockout_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-knockout-right", ec_marker_knockout_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-mid", ec_marker_mid },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-pattern", ec_marker_pattern },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-segment", ec_marker_segment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "marker-start", ec_marker_start },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "marks", ec_marks, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask", ec_mask },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border", ec_mask_border },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-mode", ec_mask_border_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-outset", ec_mask_border_outset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-repeat", ec_mask_border_repeat },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-slice", ec_mask_border_slice },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-source", ec_mask_border_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-border-width", ec_mask_border_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-clip", ec_mask_clip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-composite", ec_mask_composite },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-image", ec_mask_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-mode", ec_mask_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-origin", ec_mask_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-position", ec_mask_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-repeat", ec_mask_repeat },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-size", ec_mask_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mask-type", ec_mask_type },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "mathline", ec_mathline, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "max-height", ec_max_height, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "max-lines", ec_max_lines },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "max-width", ec_max_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "min-height", ec_min_height, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "min-intrinsic-sizing", ec_min_intrinsic_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "min-width", ec_min_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "nav-down", ec_nav_down },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "nav-left", ec_nav_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "nav-right", ec_nav_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "nav-up", ec_nav_up },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "object-fit", ec_object_fit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "object-position", ec_object_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset", ec_offset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset-anchor", ec_offset_anchor },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset-distance", ec_offset_distance },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset-path", ec_offset_path },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset-position", ec_offset_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "offset-rotate", ec_offset_rotate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "opacity", ec_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "order", ec_order },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "orphans", ec_orphans, ns_default, CF_PAGE | CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "outline", ec_outline, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "outline-color", ec_outline_colour, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "outline-offset", ec_outline_offset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "outline-style", ec_outline_style, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "outline-width", ec_outline_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow", ec_overflow, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-anchor", ec_overflow_anchor },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-block", ec_overflow_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin", ec_overflow_clip_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-block", ec_overflow_clip_margin_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-block-end", ec_overflow_clip_margin_block_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-block-start", ec_overflow_clip_margin_block_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-bottom", ec_overflow_clip_margin_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-inline", ec_overflow_clip_margin_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-inline-end", ec_overflow_clip_margin_inline_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-inline-start", ec_overflow_clip_margin_inline_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-left", ec_overflow_clip_margin_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-right", ec_overflow_clip_margin_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-margin-top", ec_overflow_clip_margin_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-inline", ec_overflow_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-wrap", ec_overflow_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-x", ec_overflow_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-y", ec_overflow_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overscroll-behavior", ec_overscroll_behavior },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overscroll-behavior-block", ec_overscroll_behavior_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overscroll-behavior-inline", ec_overscroll_behavior_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overscroll-behavior-x", ec_overscroll_behavior_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overscroll-behavior-y", ec_overscroll_behavior_y },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "padding", ec_padding, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "padding-bottom", ec_padding_bottom, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "padding-left", ec_padding_left, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "padding-right", ec_padding_right, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "padding-top", ec_padding_top, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "page-break-after", ec_page_break_after, ns_default, CF_EXPECT_KEYWORDS | CF_PAGE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "page-break-before", ec_page_break_before, ns_default, CF_EXPECT_KEYWORDS | CF_PAGE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "page-break-inside", ec_page_break_inside, ns_default, CF_EXPECT_KEYWORDS | CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "page", ec_page_property, ns_default, CF_PAGE_NAME },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "panose-1", ec_panose_1, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "pause", ec_pause, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "pause-after", ec_pause_after, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "pause-before", ec_pause_before, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "perspective", ec_perspective },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "perspective-origin", ec_perspective_origin },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "pitch", ec_pitch, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "pitch-range", ec_pitch_range, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "place-content", ec_place_content },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "place-items", ec_place_items },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "place-self", ec_place_self },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "play-during", ec_play_during, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "position", ec_position, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "print-color-adjust", ec_print_colour_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "quotes", ec_quotes },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "region-fragment", ec_region_fragment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "resize", ec_resize },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "rest", ec_rest },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "rest-after", ec_rest_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "rest-before", ec_rest_before },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "richness", ec_richness, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "right", ec_right, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "rotate", ec_rotate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "row-gap", ec_row_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "ruby-align", ec_ruby_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "ruby-merge", ec_ruby_merge },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "ruby-overhang", ec_ruby_overhang },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "ruby-position", ec_ruby_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scale", ec_scale },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-behavior", ec_scroll_behavior },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin", ec_scroll_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-block", ec_scroll_margin_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-block-end", ec_scroll_margin_block_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-block-start", ec_scroll_margin_block_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-bottom", ec_scroll_margin_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-inline", ec_scroll_margin_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-inline-end", ec_scroll_margin_inline_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-inline-start", ec_scroll_margin_inline_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-left", ec_scroll_margin_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-right", ec_scroll_margin_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-margin-top", ec_scroll_margin_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding", ec_scroll_padding },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-block", ec_scroll_padding_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-block-end", ec_scroll_padding_block_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-block-start", ec_scroll_padding_block_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-bottom", ec_scroll_padding_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-inline", ec_scroll_padding_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-inline-end", ec_scroll_padding_inline_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-inline-start", ec_scroll_padding_inline_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-left", ec_scroll_padding_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-right", ec_scroll_padding_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-padding-top", ec_scroll_padding_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-snap-align", ec_scroll_snap_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-snap-stop", ec_scroll_snap_stop },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-snap-type", ec_scroll_snap_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-timeline", ec_scroll_timeline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-timeline-axis", ec_scroll_timeline_axis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scroll-timeline-name", ec_scroll_timeline_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scrollbar-color", ec_scrollbar_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scrollbar-gutter", ec_scrollbar_gutter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "scrollbar-width", ec_scrollbar_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "shape-image-threshold", ec_shape_image_threshold },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "shape-inside", ec_shape_inside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "shape-margin", ec_shape_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "shape-outside", ec_shape_outside },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "size", ec_size, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "slope", ec_slope, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "spatial-navigation-action", ec_spatial_navigation_action },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "spatial-navigation-contain", ec_spatial_navigation_contain },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "spatial-navigation-function", ec_spatial_navigation_function },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "speak", ec_speak, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "speak-as", ec_speak_as },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "speak-header", ec_speak_header, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "speak-numeral", ec_speak_numeral, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "speak-punctuation", ec_speak_punctuation, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "speech-rate", ec_speech_rate, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2 }, { HTML_UNDEF }, "src", ec_src, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "stemh", ec_stemh, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "stemv", ec_stemv, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "stress", ec_stress, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "string-set", ec_string_set },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke", ec_stroke },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-alignment", ec_stroke_alignment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-dashadjust", ec_stroke_dashadjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-dasharray", ec_stroke_dasharray },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-dashcorner", ec_stroke_dashcorner },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-dashoffset", ec_stroke_dashoffset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-linecap", ec_stroke_linecap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-linejoin", ec_stroke_linejoin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-miterlimit", ec_stroke_miterlimit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-opacity", ec_stroke_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "stroke-width", ec_stroke_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "tab-size", ec_tab_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "table-layout", ec_table_layout, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-align", ec_text_align, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-align-all", ec_text_align_all },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-align-last", ec_text_align_last },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-autospace", ec_text_autospace },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-combine-upright", ec_text_combine_upright },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-decoration", ec_text_decoration, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-color", ec_text_decoration_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-line", ec_text_decoration_line },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip", ec_text_decoration_skip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip-box", ec_text_decoration_skip_box },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip-ink", ec_text_decoration_skip_ink },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip-inset", ec_text_decoration_skip_inset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip-self", ec_text_decoration_skip_self },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-skip-spaces", ec_text_decoration_skip_spaces },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-style", ec_text_decoration_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-decoration-thickness", ec_text_decoration_thickness },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-edge", ec_text_edge },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-emphasis", ec_text_emphasis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-emphasis-color", ec_text_emphasis_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-emphasis-position", ec_text_emphasis_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-emphasis-skip", ec_text_emphasis_skip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-emphasis-style", ec_text_emphasis_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-group-align", ec_text_group_align },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-indent", ec_text_indent, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-justify", ec_text_justify },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-orientation", ec_text_orientation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-overflow", ec_text_overflow },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "text-shadow", ec_text_shadow, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-space-trim", ec_text_space_trim },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-spacing", ec_text_spacing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-spacing-trim", ec_text_spacing_trim },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-transform", ec_text_transform, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-underline-offset", ec_text_underline_offset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-underline-position", ec_text_underline_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-wrap", ec_text_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "top", ec_top, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "topline", ec_topline, ns_default, CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transform", ec_transform },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transform-box", ec_transform_box },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transform-origin", ec_transform_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transform-style", ec_transform_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transition", ec_transition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transition-delay", ec_transition_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transition-duration", ec_transition_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transition-property", ec_transition_property },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "transition-timing-function", ec_transition_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "translate", ec_translate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "unicode-bidi", ec_unicode_bidi, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "unicode-range", ec_unicode_range, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "units-per-em", ec_units_per_em, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "user-select", ec_user_select },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "vertical-align", ec_vertical_align, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "view-timeline", ec_view_timeline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "view-timeline-axis", ec_view_timeline_axis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "view-timeline-inset", ec_view_timeline_inset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "view-timeline-name", ec_view_timeline_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "view-transition-name", ec_view_transition_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "visibility", ec_visibility, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-balance", ec_voice_balance },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-duration", ec_voice_duration },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "voice-family", ec_voice_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-pitch", ec_voice_pitch },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-range", ec_voice_range },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-rate", ec_voice_rate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-stress", ec_voice_stress },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "voice-volume", ec_voice_volume },
    { { HTML_CSS, 0, 0, H2_CSS_2_0_1 }, { HTML_UNDEF }, "volume", ec_volume, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "white-space", ec_white_space, ns_default, CF_EXPECT_KEYWORDS },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "white-space-collapse", ec_white_space_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "widows", ec_widows, ns_default, CF_PAGE | CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "width", ec_width, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "widths", ec_widths, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "will-change", ec_will_change },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "word-boundary-detection", ec_word_boundary_detection },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "word-boundary-expansion", ec_word_boundary_expansion },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "word-break", ec_word_break },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "word-spacing", ec_word_spacing, ns_default, CF_NOT_STRING },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "word-wrap", ec_word_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wrap-after", ec_wrap_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wrap-before", ec_wrap_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wrap-flow", ec_wrap_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wrap-inside", ec_wrap_inside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "wrap-through", ec_wrap_through },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "writing-mode", ec_writing_mode },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "x-height", ec_x_height, ns_default, CF_NOT_STRING | CF_MUST_FONT_FACE },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "z-index", ec_z_index, ns_default, CF_NOT_STRING },

    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "text-rendering", ec_text_rendering },

    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-apple-dashboard-region", ec_apple_dashboard_region },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-caption-side", ec_epub_caption_side },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-hyphens", ec_epub_hyphens },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-combine", ec_epub_text_combine },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-decoration", ec_epub_text_decoration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-emphasis", ec_epub_text_emphasis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-emphasis-color", ec_epub_text_emphasis_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-emphasis-style", ec_epub_text_emphasis_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-orientation", ec_epub_text_orientation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-text-transform", ec_epub_text_transform },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-word-break", ec_epub_word_break },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-epub-writing-mode", ec_epub_writing_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation", ec_moz_animation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-delay", ec_moz_animation_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-direction", ec_moz_animation_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-duration", ec_moz_animation_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-fill-mode", ec_moz_animation_fill_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-iteration-count", ec_moz_animation_iteration_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-name", ec_moz_animation_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-play-state", ec_moz_animation_play_state },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-animation-timing-function", ec_moz_animation_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-appearance", ec_moz_appearance },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-backface-visibility", ec_moz_backface_visibility },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-background-clip", ec_moz_background_clip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-background-inline-policy", ec_moz_background_inline_policy },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-background-origin", ec_moz_background_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-background-size", ec_moz_background_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-binding", ec_moz_binding },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-bottom-colors", ec_moz_border_bottom_colours },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-end", ec_moz_border_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-end-color", ec_moz_border_end_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-end-style", ec_moz_border_end_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-end-width", ec_moz_border_end_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-image", ec_moz_border_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-left-colors", ec_moz_border_left_colours },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-right-colors", ec_moz_border_right_colours },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-start", ec_moz_border_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-start-color", ec_moz_border_start_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-start-style", ec_moz_border_start_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-start-width", ec_moz_border_start_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-border-top-colors", ec_moz_border_top_colours },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-align", ec_moz_box_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-direction", ec_moz_box_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-flex", ec_moz_box_flex },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-ordinal-group", ec_moz_box_ordinal_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-orient", ec_moz_box_orient },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-pack", ec_moz_box_pack },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-box-sizing", ec_moz_box_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-count", ec_moz_column_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-fill", ec_moz_column_fill },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-gap", ec_moz_column_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-rule", ec_moz_column_rule },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-rule-color", ec_moz_column_rule_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-rule-style", ec_moz_column_rule_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-rule-width", ec_moz_column_rule_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-column-width", ec_moz_column_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-context-properties", ec_moz_context_properties },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-float-edge", ec_moz_float_edge },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-font-feature-settings", ec_moz_font_feature_settings },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-font-language-override", ec_moz_font_language_override },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-force-broken-image-icon", ec_moz_force_broken_image_icon },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-hyphens", ec_moz_hyphens },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-image-region", ec_moz_image_region },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-margin-end", ec_moz_margin_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-margin-start", ec_moz_margin_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-opacity", ec_moz_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-orient", ec_moz_orient },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-osx-font-smoothing", ec_moz_osx_font_smoothing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline", ec_moz_outline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-color", ec_moz_outline_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-offset", ec_moz_outline_offset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-radius", ec_moz_outline_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-radius-bottomleft", ec_moz_outline_radius_bottomleft },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-radius-bottomright", ec_moz_outline_radius_bottomright },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-radius-topleft", ec_moz_outline_radius_topleft },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-radius-topright", ec_moz_outline_radius_topright },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-style", ec_moz_outline_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-outline-width", ec_moz_outline_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-padding-end", ec_moz_padding_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-padding-start", ec_moz_padding_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-perspective", ec_moz_perspective },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-perspective-origin", ec_moz_perspective_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-stack-sizing", ec_moz_stack_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-tab-size", ec_moz_tab_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-text-align-last", ec_moz_text_align_last },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-text-decoration-color", ec_moz_text_decoration_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-text-decoration-line", ec_moz_text_decoration_line },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-text-decoration-style", ec_moz_text_decoration_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-text-size-adjust", ec_moz_text_size_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transform", ec_moz_transform },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transform-origin", ec_moz_transform_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transform-style", ec_moz_transform_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transition", ec_moz_transition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transition-delay", ec_moz_transition_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transition-duration", ec_moz_transition_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transition-property", ec_moz_transition_property },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-transition-timing-function", ec_moz_transition_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-user-focus", ec_moz_user_focus },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-user-input", ec_moz_user_input },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-user-modify", ec_moz_user_modify },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-user-select", ec_moz_user_select },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-window-dragging", ec_moz_window_dragging },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-moz-window-shadow", ec_moz_window_shadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation", ec_ms_animation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-delay", ec_ms_animation_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-direction", ec_ms_animation_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-duration", ec_ms_animation_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-fill-mode", ec_ms_animation_fill_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-iteration-count", ec_ms_animation_iteration_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-name", ec_ms_animation_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-play-state", ec_ms_animation_play_state },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-animation-timing-function", ec_ms_animation_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-block-progression", ec_ms_block_progression },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-chaining", ec_ms_content_zoom_chaining },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-limit", ec_ms_content_zoom_limit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-limit-max", ec_ms_content_zoom_limit_max },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-limit-min", ec_ms_content_zoom_limit_min },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-snap", ec_ms_content_zoom_snap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-snap-points", ec_ms_content_zoom_snap_points },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zoom-snap-type", ec_ms_content_zoom_snap_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-content-zooming", ec_ms_content_zooming },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-align", ec_ms_flex_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-item-align", ec_ms_flex_item_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-line-pack", ec_ms_flex_line_pack },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-negative", ec_ms_flex_negative },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-order", ec_ms_flex_order },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-pack", ec_ms_flex_pack },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-positive", ec_ms_flex_positive },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-flex-preferred-size", ec_ms_flex_preferred_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-font-feature-settings", ec_ms_font_feature_settings },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-grid-columns", ec_ms_grid_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-grid-rows", ec_ms_grid_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-high-contrast-adjust", ec_ms_high_contrast_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-hyphenate-limit-chars", ec_ms_hyphenate_limit_chars },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-hyphenate-limit-lines", ec_ms_hyphenate_limit_lines },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-hyphenate-limit-zone", ec_ms_hyphenate_limit_zone },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-ime-align", ec_ms_ime_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-interpolation-mode", ec_ms_interpolation_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-chaining", ec_ms_scroll_chaining },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-limit", ec_ms_scroll_limit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-limit-x-max", ec_ms_scroll_limit_x_max },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-limit-x-min", ec_ms_scroll_limit_x_min },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-limit-y-max", ec_ms_scroll_limit_y_max },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-limit-y-min", ec_ms_scroll_limit_y_min },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-rails", ec_ms_scroll_rails },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-snap-points-x", ec_ms_scroll_snap_points_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-snap-points-y", ec_ms_scroll_snap_points_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-snap-type", ec_ms_scroll_snap_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-snap-x", ec_ms_scroll_snap_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-snap-y", ec_ms_scroll_snap_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-scroll-translation", ec_ms_scroll_translation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-text-combine-horizontal", ec_ms_text_combine_horizontal },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-touch-action", ec_ms_touch_action },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-touch-select", ec_ms_touch_select },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-transition", ec_ms_transition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-transition-delay", ec_ms_transition_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-transition-duration", ec_ms_transition_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-transition-property", ec_ms_transition_property },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-transition-timing-function", ec_ms_transition_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-ms-wrap-margin", ec_ms_wrap_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-border-image", ec_o_border_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-device-pixel-ratio", ec_o_device_pixel_ratio },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-focus-opacity", ec_o_focus_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-link", ec_o_link },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-link-source", ec_o_link_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-mini-fold", ec_o_mini_fold },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-object-fit", ec_o_object_fit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-object-position", ec_o_object_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-tab-size", ec_o_tab_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-table-baseline", ec_o_table_baseline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-text-overflow", ec_o_text_overflow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transform", ec_o_transform },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transform-origin", ec_o_transform_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transition", ec_o_transition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transition-delay", ec_o_transition_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transition-duration", ec_o_transition_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transition-property", ec_o_transition_property },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-o-transition-timing-function", ec_o_transition_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-accesskey", ec_wap_accesskey },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-input-format", ec_wap_input_format },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-input-required", ec_wap_input_required },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-marquee-dir", ec_wap_marquee_dir },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-marquee-loop", ec_wap_marquee_loop },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-marquee-speed", ec_wap_marquee_speed },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-wap-marquee-style", ec_wap_marquee_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-align-content", ec_webkit_align_content },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-align-items", ec_webkit_align_items },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-align-self", ec_webkit_align_self },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-alt", ec_webkit_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation", ec_webkit_animation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-delay", ec_webkit_animation_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-direction", ec_webkit_animation_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-duration", ec_webkit_animation_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-fill-mode", ec_webkit_animation_fill_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-iteration-count", ec_webkit_animation_iteration_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-name", ec_webkit_animation_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-play-state", ec_webkit_animation_play_state },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-timing-function", ec_webkit_animation_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-animation-trigger", ec_webkit_animation_trigger },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-app-region", ec_webkit_app_region },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-appearance", ec_webkit_appearance },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-aspect-ratio", ec_webkit_aspect_ratio },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-backdrop-filter", ec_webkit_backdrop_filter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-backface-visibility", ec_webkit_backface_visibility },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-background-clip", ec_webkit_background_clip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-background-composite", ec_webkit_background_composite },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-background-origin", ec_webkit_background_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-background-size", ec_webkit_background_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-after", ec_webkit_border_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-after-color", ec_webkit_border_after_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-after-style", ec_webkit_border_after_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-after-width", ec_webkit_border_after_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-before", ec_webkit_border_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-before-color", ec_webkit_border_before_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-before-style", ec_webkit_border_before_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-before-width", ec_webkit_border_before_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-bottom-left-radius", ec_webkit_border_bottom_left_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-bottom-right-radius", ec_webkit_border_bottom_right_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-end", ec_webkit_border_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-end-color", ec_webkit_border_end_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-end-style", ec_webkit_border_end_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-end-width", ec_webkit_border_end_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-fit", ec_webkit_border_fit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-horizontal-spacing", ec_webkit_border_horizontal_spacing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-image", ec_webkit_border_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-radius", ec_webkit_border_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-start", ec_webkit_border_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-start-color", ec_webkit_border_start_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-start-style", ec_webkit_border_start_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-start-width", ec_webkit_border_start_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-top-left-radius", ec_webkit_border_top_left_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-top-right-radius", ec_webkit_border_top_right_radius },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-border-vertical-spacing", ec_webkit_border_vertical_spacing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-align", ec_webkit_box_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-decoration-break", ec_webkit_box_decoration_break },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-direction", ec_webkit_box_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-flex", ec_webkit_box_flex },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-flex-group", ec_webkit_box_flex_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-lines", ec_webkit_box_lines },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-ordinal-group", ec_webkit_box_ordinal_group },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-orient", ec_webkit_box_orient },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-pack", ec_webkit_box_pack },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-reflect", ec_webkit_box_reflect },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-shadow", ec_webkit_box_shadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-box-sizing", ec_webkit_box_sizing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-clip-path", ec_webkit_clip_path },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-color-correction", ec_webkit_colour_correction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-axis", ec_webkit_column_axis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-break-after", ec_webkit_column_break_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-break-before", ec_webkit_column_break_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-break-inside", ec_webkit_column_break_inside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-count", ec_webkit_column_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-fill", ec_webkit_column_fill },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-gap", ec_webkit_column_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-progression", ec_webkit_column_progression },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-rule", ec_webkit_column_rule },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-rule-color", ec_webkit_column_rule_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-rule-style", ec_webkit_column_rule_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-rule-width", ec_webkit_column_rule_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-span", ec_webkit_column_span },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-column-width", ec_webkit_column_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-columns", ec_webkit_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-cursor-visibility", ec_webkit_cursor_visibility },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-dashboard-region", ec_webkit_dashboard_region },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-device-pixel-ratio", ec_webkit_device_pixel_ratio },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-filter", ec_webkit_filter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex", ec_webkit_flex },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-basis", ec_webkit_flex_basis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-direction", ec_webkit_flex_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-flow", ec_webkit_flex_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-grow", ec_webkit_flex_grow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-shrink", ec_webkit_flex_shrink },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flex-wrap", ec_webkit_flex_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flow-from", ec_webkit_flow_from },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-flow-into", ec_webkit_flow_into },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-font-feature-settings", ec_webkit_font_feature_settings },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-font-kerning", ec_webkit_font_kerning },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-font-size-delta", ec_webkit_font_size_delta },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-font-smoothing", ec_webkit_font_smoothing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-font-variant-ligatures", ec_webkit_font_variant_ligatures },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid", ec_webkit_grid },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-area", ec_webkit_grid_area },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-auto-columns", ec_webkit_grid_auto_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-auto-flow", ec_webkit_grid_auto_flow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-auto-rows", ec_webkit_grid_auto_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-column", ec_webkit_grid_column },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-column-end", ec_webkit_grid_column_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-column-gap", ec_webkit_grid_column_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-column-start", ec_webkit_grid_column_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-columns", ec_webkit_grid_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-gap", ec_webkit_grid_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-row", ec_webkit_grid_row },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-row-end", ec_webkit_grid_row_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-row-gap", ec_webkit_grid_row_gap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-row-start", ec_webkit_grid_row_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-rows", ec_webkit_grid_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-template", ec_webkit_grid_template },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-template-areas", ec_webkit_grid_template_areas },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-template-columns", ec_webkit_grid_template_columns },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-grid-template-rows", ec_webkit_grid_template_rows },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-highlight", ec_webkit_highlight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphenate-character", ec_webkit_hyphenate_character },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphenate-charset", ec_webkit_hyphenate_charset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphenate-limit-after", ec_webkit_hyphenate_limit_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphenate-limit-before", ec_webkit_hyphenate_limit_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphenate-limit-lines", ec_webkit_hyphenate_limit_lines },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-hyphens", ec_webkit_hyphens },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-image-set", ec_webkit_image_set },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-initial-letter", ec_webkit_initial_letter },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-justify-content", ec_webkit_justify_content },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-justify-items", ec_webkit_justify_items },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-justify-self", ec_webkit_justify_self },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-align", ec_webkit_line_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-box-contain", ec_webkit_line_box_contain },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-break", ec_webkit_line_break },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-clamp", ec_webkit_line_clamp },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-grid", ec_webkit_line_grid },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-line-snap", ec_webkit_line_snap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-locale", ec_webkit_locale },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-logical-height", ec_webkit_logical_height },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-logical-width", ec_webkit_logical_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-after", ec_webkit_margin_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-after-collapse", ec_webkit_margin_after_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-before", ec_webkit_margin_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-before-collapse", ec_webkit_margin_before_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-bottom-collapse", ec_webkit_margin_bottom_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-collapse", ec_webkit_margin_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-end", ec_webkit_margin_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-start", ec_webkit_margin_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-margin-top-collapse", ec_webkit_margin_top_collapse },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee", ec_webkit_marquee },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee-direction", ec_webkit_marquee_direction },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee-increment", ec_webkit_marquee_increment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee-repetition", ec_webkit_marquee_repetition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee-speed", ec_webkit_marquee_speed },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-marquee-style", ec_webkit_marquee_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask", ec_webkit_mask },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-attachment", ec_webkit_mask_attachment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image", ec_webkit_mask_box_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image-outset", ec_webkit_mask_box_image_outset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image-repeat", ec_webkit_mask_box_image_repeat },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image-slice", ec_webkit_mask_box_image_slice },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image-source", ec_webkit_mask_box_image_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-box-image-width", ec_webkit_mask_box_image_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-clip", ec_webkit_mask_clip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-composite", ec_webkit_mask_composite },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-image", ec_webkit_mask_image },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-origin", ec_webkit_mask_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-position", ec_webkit_mask_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-position-x", ec_webkit_mask_position_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-position-y", ec_webkit_mask_position_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-repeat", ec_webkit_mask_repeat },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-repeat-x", ec_webkit_mask_repeat_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-repeat-y", ec_webkit_mask_repeat_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-size", ec_webkit_mask_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-mask-source-type", ec_webkit_mask_source_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-match-nearest-mail-blockquote-color", ec_webkit_match_nearest_mail_blockquote_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-max-logical-height", ec_webkit_max_logical_height },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-max-logical-width", ec_webkit_max_logical_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-media-text-track-container", ec_webkit_media_text_track_container },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-min-logical-height", ec_webkit_min_logical_height },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-min-logical-width", ec_webkit_min_logical_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-nbsp-mode", ec_webkit_nbsp_mode },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-opacity", ec_webkit_opacity },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-order", ec_webkit_order },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-overflow-scrolling", ec_webkit_overflow_scrolling },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-padding-after", ec_webkit_padding_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-padding-before", ec_webkit_padding_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-padding-end", ec_webkit_padding_end },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-padding-start", ec_webkit_padding_start },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-perspective", ec_webkit_perspective },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-perspective-origin", ec_webkit_perspective_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-perspective-origin-x", ec_webkit_perspective_origin_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-perspective-origin-y", ec_webkit_perspective_origin_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-print-color-adjust", ec_webkit_print_colour_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-region-break-after", ec_webkit_region_break_after },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-region-break-before", ec_webkit_region_break_before },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-region-break-inside", ec_webkit_region_break_inside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-region-fragment", ec_webkit_region_fragment },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-rtl-ordering", ec_webkit_rtl_ordering },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-ruby-position", ec_webkit_ruby_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-scroll-snap-type", ec_webkit_scroll_snap_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-shape-image-threshold", ec_webkit_shape_image_threshold },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-shape-inside", ec_webkit_shape_inside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-shape-margin", ec_webkit_shape_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-shape-outside", ec_webkit_shape_outside },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-svg-shadow", ec_webkit_svg_shadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-tap-highlight-color", ec_webkit_tap_highlight_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-color-decoration", ec_webkit_text_colour_decoration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-combine", ec_webkit_text_combine },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-decoration-line", ec_webkit_text_decoration_line },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-decoration-skip", ec_webkit_text_decoration_skip },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-decoration-style", ec_webkit_text_decoration_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-decorations-in-effect", ec_webkit_text_decorations_in_effect },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-emphasis", ec_webkit_text_emphasis },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-emphasis-color", ec_webkit_text_emphasis_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-emphasis-position", ec_webkit_text_emphasis_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-emphasis-style", ec_webkit_text_emphasis_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-fill-color", ec_webkit_text_fill_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-justify", ec_webkit_text_justify },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-orientation", ec_webkit_text_orientation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-security", ec_webkit_text_security },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-size-adjust", ec_webkit_text_size_adjust },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-stroke", ec_webkit_text_stroke },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-stroke-color", ec_webkit_text_stroke_colour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-stroke-width", ec_webkit_text_stroke_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-underline-position", ec_webkit_text_underline_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-text-zoom", ec_webkit_text_zoom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-touch-callout", ec_webkit_touch_callout },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform", ec_webkit_transform },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-2d", ec_webkit_transform_2d },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-3d", ec_webkit_transform_3d },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-origin", ec_webkit_transform_origin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-origin-x", ec_webkit_transform_origin_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-origin-y", ec_webkit_transform_origin_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-origin-z", ec_webkit_transform_origin_z },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transform-style", ec_webkit_transform_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transition", ec_webkit_transition },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transition-delay", ec_webkit_transition_delay },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transition-duration", ec_webkit_transition_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transition-property", ec_webkit_transition_property },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-transition-timing-function", ec_webkit_transition_timing_function },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-user-drag", ec_webkit_user_drag },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-user-modify", ec_webkit_user_modify },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-webkit-user-select", ec_webkit_user_select },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-interpret-as", ec_xv_interpret_as },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-phonemes", ec_xv_phonemes },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-balance", ec_xv_voice_balance },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-duration", ec_xv_voice_duration },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-pitch", ec_xv_voice_pitch },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-pitch-range", ec_xv_voice_pitch_range },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-rate", ec_xv_voice_rate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-stress", ec_xv_voice_stress },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "-xv-voice-volume", ec_xv_voice_volume },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "background-origin-x", ec_background_origin_x },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "background-origin-y", ec_background_origin_y },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ansi-font-size", ec_mso_ansi_font_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ansi-font-style", ec_mso_ansi_font_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ansi-font-weight", ec_mso_ansi_font_weight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ansi-language", ec_mso_ansi_language },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-arabic-font-family", ec_mso_arabic_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-armenian-font-family", ec_mso_armenian_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ascii-font-family", ec_mso_ascii_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ascii-theme-font", ec_mso_ascii_theme_font },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-background-source", ec_mso_background_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bengali-font-family", ec_mso_bengali_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-font-family", ec_mso_bidi_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-font-size", ec_mso_bidi_font_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-font-style", ec_mso_bidi_font_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-font-weight", ec_mso_bidi_font_weight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-language", ec_mso_bidi_language },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bidi-theme-font", ec_mso_bidi_theme_font },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bookmark", ec_mso_bookmark },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-bopomofo-font-family", ec_mso_bopomofo_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-alt", ec_mso_border_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-bottom-alt", ec_mso_border_bottom_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-color-alt", ec_mso_border_colour_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-insideh", ec_mso_border_insideh },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-insidev", ec_mso_border_insidev },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-left-alt", ec_mso_border_left_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-right-alt", ec_mso_border_right_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-shadow", ec_mso_border_shadow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-style-alt", ec_mso_border_style_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-top-alt", ec_mso_border_top_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-border-width-alt", ec_mso_border_width_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-break-type", ec_mso_break_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-cell-special", ec_mso_cell_special },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-cellspacing", ec_mso_cellspacing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-char-indent-count", ec_mso_char_indent_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-char-indent-size", ec_mso_char_indent_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-char-tracking", ec_mso_char_tracking },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-char-type", ec_mso_char_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-char-wrap", ec_mso_char_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-color-alt", ec_mso_colour_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-color-index", ec_mso_colour_index },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-column-margin", ec_mso_column_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-currency-font-family", ec_mso_currency_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-cyrillic-font-family", ec_mso_cyrillic_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-data-placement", ec_mso_data_placement },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-default-font-family", ec_mso_default_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-default-props", ec_mso_default_props },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-devanagari-font-family", ec_mso_devanagari_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-displayed-decimal-separator", ec_mso_displayed_decimal_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-displayed-thousand-separator", ec_mso_displayed_thousand_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element", ec_mso_element },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-anchor-horizontal", ec_mso_element_anchor_horizontal },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-anchor-vertical", ec_mso_element_anchor_vertical },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-frame-height", ec_mso_element_frame_height },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-frame-hspace", ec_mso_element_frame_hspace },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-frame-width", ec_mso_element_frame_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-left", ec_mso_element_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-top", ec_mso_element_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-element-wrap", ec_mso_element_wrap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-endnote-continuation-separator", ec_mso_endnote_continuation_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-endnote-numbering-style", ec_mso_endnote_numbering_style },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-endnote-separator", ec_mso_endnote_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-eudc-font-family", ec_mso_eudc_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-even-footer", ec_mso_even_footer },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-fareast-font-family", ec_mso_fareast_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-fareast-language", ec_mso_fareast_language },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-fareast-theme-font", ec_mso_fareast_theme_font },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-field-code", ec_mso_field_code },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-alt", ec_mso_font_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-charset", ec_mso_font_charset },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-format", ec_mso_font_format },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-kerning", ec_mso_font_kerning },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-pitch", ec_mso_font_pitch },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-signature", ec_mso_font_signature },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-font-width", ec_mso_font_width },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-footer", ec_mso_footer },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-footer-margin", ec_mso_footer_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-footnote-continuation-separator", ec_mso_footnote_continuation_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-footnote-id", ec_mso_footnote_id },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-footnote-separator", ec_mso_footnote_separator },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-generic-font-family", ec_mso_generic_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-georgian-font-family", ec_mso_georgian_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-gram-e", ec_mso_gram_e },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-greek-font-family", ec_mso_greek_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-gurmukhi-font-family", ec_mso_gurmukhi_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-halfwidthkana-font-family", ec_mso_halfwidthkana_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-han-font-family", ec_mso_han_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hangul-font-family", ec_mso_hangul_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hansi-font-family", ec_mso_hansi_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hansi-theme-font", ec_mso_hansi_theme_font },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-header", ec_mso_header },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-header-margin", ec_mso_header_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hebrew-font-family", ec_mso_hebrew_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-height-rule", ec_mso_height_rule },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-height-source", ec_mso_height_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hide", ec_mso_hide },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-highlight", ec_mso_highlight },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-hyphenate", ec_mso_hyphenate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-ignore", ec_mso_ignore },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-kana-font-family", ec_mso_kana_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-kannada-font-family", ec_mso_kannada_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-kinsoku-overflow", ec_mso_kinsoku_overflow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-lao-font-family", ec_mso_lao_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-latin-font-family", ec_mso_latin_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-latinext-font-family", ec_mso_latinext_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-layout-grid-align", ec_mso_layout_grid_align },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-font-family", ec_mso_level_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-indent", ec_mso_level_indent },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-legacy", ec_mso_level_legacy },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-legacy-indent", ec_mso_level_legacy_indent },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-legacy-space", ec_mso_level_legacy_space },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-number-format", ec_mso_level_number_format },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-number-position", ec_mso_level_number_position },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-size", ec_mso_level_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-start-at", ec_mso_level_start_at },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-style-link", ec_mso_level_style_link },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-tab-stop", ec_mso_level_tab_stop },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-level-text", ec_mso_level_text },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-line-height-alt", ec_mso_line_height_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-line-height-rule", ec_mso_line_height_rule },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-line-spacing", ec_mso_line_spacing },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-linked-frame", ec_mso_linked_frame },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-list", ec_mso_list },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-list-id", ec_mso_list_id },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-list-template-ids", ec_mso_list_template_ids },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-list-type", ec_mso_list_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-malayalam-font-family", ec_mso_malayalam_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-margin-bottom-alt", ec_mso_margin_bottom_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-margin-left-alt", ec_mso_margin_left_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-margin-top-alt", ec_mso_margin_top_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-no-proof", ec_mso_no_proof },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-number-format", ec_mso_number_format },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-oriya-font-family", ec_mso_oriya_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-outline-level", ec_mso_outline_level },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-padding-alt", ec_mso_padding_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-page-border-surround-footer", ec_mso_page_border_surround_footer },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-page-border-surround-header", ec_mso_page_border_surround_header },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-page-orientation", ec_mso_page_orientation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-pagination", ec_mso_pagination },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-paper-source", ec_mso_paper_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-para-margin", ec_mso_para_margin },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-para-margin-bottom", ec_mso_para_margin_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-para-margin-left", ec_mso_para_margin_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-para-margin-right", ec_mso_para_margin_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-para-margin-top", ec_mso_para_margin_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-pattern", ec_mso_pattern },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-position-horizontal", ec_mso_position_horizontal },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-position-horizontal-relative", ec_mso_position_horizontal_relative },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-position-vertical", ec_mso_position_vertical },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-position-vertical-relative", ec_mso_position_vertical_relative },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-protection", ec_mso_protection },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-rotate", ec_mso_rotate },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-row-margin-left", ec_mso_row_margin_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-row-margin-right", ec_mso_row_margin_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-shading", ec_mso_shading },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-spacerun", ec_mso_spacerun },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-special-character", ec_mso_special_character },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-special-format", ec_mso_special_format },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-spl-e", ec_mso_spl_e },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-id", ec_mso_style_id },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-link", ec_mso_style_link },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-locked", ec_mso_style_locked },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-name", ec_mso_style_name },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-next", ec_mso_style_next },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-noshow", ec_mso_style_noshow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-parent", ec_mso_style_parent },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-priority", ec_mso_style_priority },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-qformat", ec_mso_style_qformat },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-type", ec_mso_style_type },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-unhide", ec_mso_style_unhide },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-style-update", ec_mso_style_update },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-symbol-font-family", ec_mso_symbol_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-syriac-font-family", ec_mso_syriac_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-tab-count", ec_mso_tab_count },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-anchor-horizontal", ec_mso_table_anchor_horizontal },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-anchor-vertical", ec_mso_table_anchor_vertical },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-layout-alt", ec_mso_table_layout_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-left", ec_mso_table_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-lspace", ec_mso_table_lspace },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-overlap", ec_mso_table_overlap },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-rspace", ec_mso_table_rspace },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-table-top", ec_mso_table_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-tamil-font-family", ec_mso_tamil_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-telugu-font-family", ec_mso_telugu_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-text-animation", ec_mso_text_animation },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-text-raise", ec_mso_text_raise },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-thaana-font-family", ec_mso_thaana_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-thai-font-family", ec_mso_thai_font_family },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-themecolor", ec_mso_themecolour },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-themeshade", ec_mso_themeshade },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-title-page", ec_mso_title_page },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-tstyle-colband-size", ec_mso_tstyle_colband_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-tstyle-rowband-size", ec_mso_tstyle_rowband_size },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-width-alt", ec_mso_width_alt },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-width-source", ec_mso_width_source },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-wrap-distance-bottom", ec_mso_wrap_distance_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-wrap-distance-left", ec_mso_wrap_distance_left },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-wrap-distance-right", ec_mso_wrap_distance_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-wrap-distance-top", ec_mso_wrap_distance_top },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-wrap-edited", ec_mso_wrap_edited },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-yfti-firstrow", ec_mso_yfti_firstrow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-yfti-irow", ec_mso_yfti_irow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-yfti-lastrow", ec_mso_yfti_lastrow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "mso-yfti-tbllook", ec_mso_yfti_tbllook },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-box", ec_overflow_clip_box },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-box-block", ec_overflow_clip_box_block },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "overflow-clip-box-inline", ec_overflow_clip_box_inline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "pointer-events", ec_pointer_events } };

struct symbol_entry < html_version, e_css_speech_rate_e > css_speech_rate_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "fast", esr_fast },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "faster", esr_faster },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", esr_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "medium", esr_medium },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "slow", esr_slow },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "slower", esr_slower },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-fast", esr_x_fast },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-slow", est_x_slow } };

struct symbol_entry < html_version, e_css_relative_size > css_relative_size_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecr_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "larger", ecr_larger },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "smaller", ecr_smaller } };

struct symbol_entry < html_version, e_css_statement > css_statement_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "charset", css_charset },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "document", css_document },
    { { HTML_CSS, 0, 0, H2_CSS_2 }, { HTML_UNDEF }, "font-face", css_font_face },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "import", css_import },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "keyframes", css_keyframes },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "media", css_media },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "namespace", css_namespace },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "page", css_page },
    { { HTML_JAN22, 0, 0, H2_CSS_6 }, { HTML_UNDEF }, "scope", css_scope },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "supports", css_supports },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "viewport", css_viewport } };

struct symbol_entry < html_version, e_css_text_align > css_text_align_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "center", ecta_centre },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecta_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "justify", ecta_justify },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecta_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecta_right } };

struct symbol_entry < html_version, e_css_text_decoration > css_text_decoration_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ectd_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ectd_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "underline", ectd_underline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "overline", ectd_overline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "line-through", ectd_linethrough },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "blink", ectd_blink } };

struct symbol_entry < html_version, e_css_text_transform > css_text_transform_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ect_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "capitalize", ect_capitalise },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lowercase", ect_lowercase },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ect_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "uppercase", ect_uppercase } };

struct symbol_entry < html_version, e_css_vertical_align > css_vertical_align_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecva_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "baseline", ecv_baseline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bottom", ecv_bottom },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "middle", ecv_middle },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "sub", ecv_sub },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "super", ecv_super },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-bottom", ecv_text_bottom },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-top", ecv_text_top },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "top", ecv_top } };

struct symbol_entry < html_version, e_css_volume_e > css_volume_e_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", cve_inherit },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "loud", cve_loud },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "medium", cve_medium },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "silent", cve_silent },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "soft", cve_soft },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-loud", cve_x_loud },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "x-soft", cve_x_soft } };

struct symbol_entry < html_version, e_css_whitespace > css_whitespace_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", ecwh_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "normal", ecwh_normal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "nowrap", ecwh_nowrap },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "pre", ecwh_pre },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "pre-line", ecwh_preline },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "pre-wrap", ecwh_prewrap } };

struct symbol_entry < html_version, e_cursor > cursor_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "auto",  cu_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "crosshair", cu_crosshair },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "default", cu_default },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "pointer", cu_pointer },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "move", cu_move },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "e-resize", cu_eresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "ne-resize", cu_neresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "nw-resize", cu_nwresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "n-resize", cu_nresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "se-resize", cu_seresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "sw-resize", cu_swresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "s-resize", cu_sresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "w-resize", cu_wresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "text", cu_text },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "wait", cu_wait },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "help", cu_help },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "progress", cu_progress } };

struct symbol_entry < html_version, e_dcmitype > dcmitype_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "Collection", dt_collection },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Dataset", dt_dataset },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Event", dt_event },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Image", dt_image },
    { { XHTML_1_0 }, { HTML_UNDEF }, "InteractiveResource", dt_interactiveresource },
    { { XHTML_1_0 }, { HTML_UNDEF }, "MovingImage", dt_movingimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "PhysicalObject", dt_physicalobject },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Service", dt_service },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Software", dt_software },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Sound", dt_sound },
    { { XHTML_1_0 }, { HTML_UNDEF }, "StillImage", dt_stillimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Text", dt_text },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Collection", dt_collection },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Dataset", dt_dataset },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Event", dt_event },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Image", dt_image },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/InteractiveResource", dt_interactiveresource },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/MovingImage", dt_movingimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/PhysicalObject", dt_physicalobject },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Service", dt_service },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Software", dt_software },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Sound", dt_sound },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/StillImage", dt_stillimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Text", dt_text } };

struct symbol_entry < html_version, e_decalign > decalign_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "left", dec_left },
    { { HTML_2_0 }, { HTML_UNDEF }, "center", dec_center },
    { { HTML_2_0 }, { HTML_UNDEF }, "right", dec_right },
    { { HTML_2_0 }, { HTML_UNDEF }, "justify", dec_justify },
    { { HTML_2_0 }, { HTML_UNDEF }, "decimal", dec_decimal } };

struct symbol_entry < html_version, e_determiner > determiner_symbol_table [] =
{   { { HTML_OG_2012 }, { HTML_UNDEF }, "a", dt_a },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "an", dt_an },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "the", dt_the },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "auto", dt_auto } };

struct symbol_entry < html_version, e_dingbat > dingbat_symbol_table [] =
{   { { HTML_3_0 }, { HTML_3_0 }, "ftp", db_ftp },
    { { HTML_3_0 }, { HTML_3_0 }, "gopher", db_gopher },
    { { HTML_3_0 }, { HTML_3_0 }, "telnet", db_telnet },
    { { HTML_3_0 }, { HTML_3_0 }, "archive", db_archive },
    { { HTML_3_0 }, { HTML_3_0 }, "filing.cabinet", db_filing_cabinet },
    { { HTML_3_0 }, { HTML_3_0 }, "folder", db_folder },
    { { HTML_3_0 }, { HTML_3_0 }, "fixed.disk", db_fixed_disk },
    { { HTML_3_0 }, { HTML_3_0 }, "disk.drive", db_disk_drive },
    { { HTML_3_0 }, { HTML_3_0 }, "document", db_document },
    { { HTML_3_0 }, { HTML_3_0 }, "unknown.document", db_unknown_document },
    { { HTML_3_0 }, { HTML_3_0 }, "text.document", db_text_document },
    { { HTML_3_0 }, { HTML_3_0 }, "binary.document", db_binary_document },
    { { HTML_3_0 }, { HTML_3_0 }, "binhex.document", db_binhex_document },
    { { HTML_3_0 }, { HTML_3_0 }, "audio", db_audio },
    { { HTML_3_0 }, { HTML_3_0 }, "film", db_film },
    { { HTML_3_0 }, { HTML_3_0 }, "image", db_image },
    { { HTML_3_0 }, { HTML_3_0 }, "map", db_map },
    { { HTML_3_0 }, { HTML_3_0 }, "form", db_form },
    { { HTML_3_0 }, { HTML_3_0 }, "mail", db_mail },
    { { HTML_3_0 }, { HTML_3_0 }, "parent", db_parent },
    { { HTML_3_0 }, { HTML_3_0 }, "next", db_next },
    { { HTML_3_0 }, { HTML_3_0 }, "previous", db_previous },
    { { HTML_3_0 }, { HTML_3_0 }, "home", db_home },
    { { HTML_3_0 }, { HTML_3_0 }, "toc", db_toc },
    { { HTML_3_0 }, { HTML_3_0 }, "glossary", db_glossary },
    { { HTML_3_0 }, { HTML_3_0 }, "index", db_index },
    { { HTML_3_0 }, { HTML_3_0 }, "summary", db_summary },
    { { HTML_3_0 }, { HTML_3_0 }, "calculator", db_calculator },
    { { HTML_3_0 }, { HTML_3_0 }, "caution", db_caution },
    { { HTML_3_0 }, { HTML_3_0 }, "clock", db_clock },
    { { HTML_3_0 }, { HTML_3_0 }, "compressed.document", db_compressed_document },
    { { HTML_3_0 }, { HTML_3_0 }, "diskette", db_diskette },
    { { HTML_3_0 }, { HTML_3_0 }, "display", db_display },
    { { HTML_3_0 }, { HTML_3_0 }, "fax", db_fax },
    { { HTML_3_0 }, { HTML_3_0 }, "mail.in", db_mail_in },
    { { HTML_3_0 }, { HTML_3_0 }, "mail.out", db_mail_out },
    { { HTML_3_0 }, { HTML_3_0 }, "mouse", db_mouse },
    { { HTML_3_0 }, { HTML_3_0 }, "printer", db_printer },
    { { HTML_3_0 }, { HTML_3_0 }, "tn3270", db_tn3270 },
    { { HTML_3_0 }, { HTML_3_0 }, "trash", db_trash } };

struct symbol_entry < html_version, e_dir > dir_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "auto",  di_auto },
    { { XHTML_2_0 }, { XHTML_2_0 }, "lro", di_lro },
    { { XHTML_2_0 }, { XHTML_2_0 }, "rlo", di_rlo },
    { { HTML_2_0 }, { HTML_UNDEF }, "ltr", di_ltr },
    { { HTML_2_0 }, { HTML_UNDEF }, "rtl", di_rtl },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "forward", di_forward },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "reverse", di_reverse } };

struct symbol_entry < html_version, e_display_align > display_align_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "auto",  da_auto },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "before", da_before },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "center", da_centre },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "after", da_after },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "inherit", da_inherit } };

struct symbol_entry < html_version, e_dominantbaseline > dominantbaseline_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "auto",  db_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "use-script", db_usescript },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "no-change", db_nochange },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "reset-size", db_resetsize },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "ideographic", db_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "alphabetic", db_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hanging", db_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "mathematical", db_mathematical },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "central", db_central },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "middle", db_middle },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "text-after-edge", db_textafteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "text-before-edge", db_textbeforeedge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "inherit", db_inherit } };

struct symbol_entry < html_version, e_enterkeyhint > enterkeyhint_symbol_table [] =
{   { { HTML_JUL20 }, { HTML_UNDEF }, "done", ekh_done },
    { { HTML_JUL20 }, { HTML_UNDEF }, "enter", ekh_enter },
    { { HTML_JUL20 }, { HTML_UNDEF }, "go", ekh_go },
    { { HTML_JUL20 }, { HTML_UNDEF }, "next", ekh_next },
    { { HTML_JUL20 }, { HTML_UNDEF }, "previous", ekh_previous },
    { { HTML_JUL20 }, { HTML_UNDEF }, "search", ekh_search },
    { { HTML_JUL20 }, { HTML_UNDEF }, "send", ekh_send } };

struct symbol_entry < html_version, e_figalign > figalign_symbol_table [] =
{   { { HTML_3_0 }, { HTML_3_0 }, "bleedleft", fa_bleedleft },
    { { HTML_3_0 }, { HTML_3_0 }, "left", fa_left },
    { { HTML_3_0 }, { HTML_3_0 }, "center", fa_centre },
    { { HTML_3_0 }, { HTML_3_0 }, "right", fa_right },
    { { HTML_3_0 }, { HTML_3_0 }, "bleedright", fa_bleedright },
    { { HTML_3_0 }, { HTML_3_0 }, "justify", fa_justify } };

struct symbol_entry < html_version, e_filter_in > filter_in_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "SourceGraphic", fi_sourcegraphic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "SourceAlpha", fi_sourcealpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "BackgroundImage", fi_backgroundimage },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "BackgroundAlpha", fi_backgroundalpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "FillPaint", fi_fillpaint },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "StrokePaint", fi_strokepaint } };

struct symbol_entry < html_version, e_fixedcolour > fixedcolour_symbol_table [] =
{    STANDARD_COLOURS (fc_) };

struct symbol_entry < html_version, e_font_enum > font_enum_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "caption",  fe_caption },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "icon",  fe_icon },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "menu", fe_menu },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "message-box", fe_message_box },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "small-caption", fe_small_caption },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "status-bar", fe_status_bar },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", fe_inherit } };

struct symbol_entry < html_version, e_fontname > fontname_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "serif", fn_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "sans-serif", fn_sans_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "cursive", fn_cursive },
    { { HTML_2_0 }, { HTML_UNDEF }, "fantasy", fn_fantasy },
    { { HTML_2_0 }, { HTML_UNDEF }, "monospace", fn_monospace },
    { { HTML_2_0 }, { HTML_UNDEF }, "Arial Narrow", fn_arial_narrow },
    { { HTML_2_0 }, { HTML_UNDEF }, "Arial", fn_arial },
    { { HTML_2_0 }, { HTML_UNDEF }, "Courier New", fn_courier_new },
    { { HTML_2_0 }, { HTML_UNDEF }, "Courier", fn_courier },
    { { HTML_2_0 }, { HTML_UNDEF }, "Georgia", fn_georgia },
    { { HTML_2_0 }, { HTML_UNDEF }, "Helvetica", fn_helvetica },
    { { HTML_2_0 }, { HTML_UNDEF }, "Times New Roman", fn_times_new_roman },
    { { HTML_2_0 }, { HTML_UNDEF }, "Times", fn_times_new_roman },
    { { HTML_2_0 }, { HTML_UNDEF }, "Verdana", fn_verdana } };

struct symbol_entry < html_version, e_font_variant_2 > font_variant_2_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "none", fv2_none },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "common", fv2_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "no_common-ligatures", fv2_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "discretionary-ligatures", fv2_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "no_discretionary-ligatures", fv2_no_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "historical-ligatures", fv2_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "no_historical-ligatures", fv2_no_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "contextual-ligatures", fv2_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "no_contextual-ligatures", fv2_no_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "jis78", fv2_jis78 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "jis83", fv2_jis83 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "jis90", fv2_jis90 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "jis04", fv2_jis04 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "simplified", fv2_simplified },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5) }, { HTML_UNDEF }, "traditional", fv2_traditional },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (6) }, { HTML_UNDEF }, "full-width", fv2_full_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (6) }, { HTML_UNDEF }, "proportional-width", fv2_proportional_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (7) }, { HTML_UNDEF }, "lining-numbers", fv2_lining_numbers },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (7) }, { HTML_UNDEF }, "old-style-numbers", fv2_old_style_numbers },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (8) }, { HTML_UNDEF }, "proportional-nums", fv2_proportional_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (8) }, { HTML_UNDEF }, "tabular-nums", fv2_tabular_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (9) }, { HTML_UNDEF }, "diagonal-fractions", fv2_diagonal_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (9) }, { HTML_UNDEF }, "stacked-fractions", fv2_stacked_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "normal", fv2_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "small-caps", fv2_small_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "all-small-caps", fv2_all_small_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "petite-caps", fv2_petite_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "all-petite-caps", fv2_all_petite_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "unicase", fv2_unicase },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10) }, { HTML_UNDEF }, "titling-caps", fv2_titling_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (11) }, { HTML_UNDEF }, "sub", fv2_sub },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (11) }, { HTML_UNDEF }, "super", fv2_super },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "ordinal", fv2_ordinal },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "slashed-zero", fv2_slashed_zero },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "ruby", fv2_ruby } };

struct symbol_entry < html_version, e_font_variant_caps > font_variant_caps_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "normal", fvc_normal },
    { { HTML_SVG20 }, { HTML_UNDEF }, "small-caps", fvc_small_caps },
    { { HTML_SVG20 }, { HTML_UNDEF }, "all-small-caps", fvc_all_small_caps },
    { { HTML_SVG20 }, { HTML_UNDEF }, "petite-caps", fvc_petite_caps },
    { { HTML_SVG20 }, { HTML_UNDEF }, "all-petite-caps", fvc_all_petite_caps },
    { { HTML_SVG20 }, { HTML_UNDEF }, "unicase", fvc_unicase },
    { { HTML_SVG20 }, { HTML_UNDEF }, "titling-caps", fvc_titling_caps } };

struct symbol_entry < html_version, e_font_variant_east_asian > font_variant_east_asian_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "normal", fvea_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "jis78", fvea_jis78 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "jis83", fvea_jis83 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "jis90", fvea_jis90 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "jis04", fvea_jis04 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "simplified", fvea_simplified },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "traditional", fvea_traditional },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "full-width", fvea_full_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "proportional-width", fvea_proportional_width },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "ruby", fvea_ruby } };

struct symbol_entry < html_version, e_font_variant_ligature > font_variant_ligature_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "normal", fvl_normal },
    { { HTML_SVG20 }, { HTML_UNDEF }, "none", fvl_none },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "common", fvl_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "no_common-ligatures", fvl_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "discretionary-ligatures", fvl_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "no_discretionary-ligatures", fvl_no_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "historical-ligatures", fvl_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "no_historical-ligatures", fvl_no_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "contextual-ligatures", fvl_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "no_contextual-ligatures", fvl_no_contextual } };

struct symbol_entry < html_version, e_font_variant_numeric > font_variant_numeric_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "normal", fvn_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "lining-numbers", fvn_lining_numbers },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "old-style-numbers", fvn_old_style_numbers },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "proportional-nums", fvn_proportional_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2) }, { HTML_UNDEF }, "tabular-nums", fvn_tabular_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "diagonal-fractions", fvn_diagonal_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3) }, { HTML_UNDEF }, "stacked-fractions", fvn_stacked_fractions },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "ordinal", fvn_ordinal },
    { { HTML_SVG20, 0, HE_COMBINES }, { HTML_UNDEF }, "slashed-zero", fvn_slashed_zero } };

struct symbol_entry < html_version, e_formaturi > formaturi_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/JSON-LD", furi_json_ld },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N3", furi_n3 },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N-Triples", furi_n_triples },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N-Quads", furi_n_quads },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/LD_Patch", furi_ldpatch },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/microdata", furi_microdata },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_XML", furi_owlxmlserialization },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_Functional", furi_owlfunctionalsyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_Manchester", furi_owlmanchestersyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/POWDER", furi_powder },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/POWDER-S", furi_powder_s },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/PROV-N", furi_prov_n },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/PROV-XML", furi_prov_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDFa", furi_rdfa },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDF_JSON", furi_rdf_json },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDF_XML", furi_rdf_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RIF_XML", furi_rifxmlsyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_XML", furi_sparqlresultsinxml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_JSON", furi_sparqlresultsinjson },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_CSV", furi_sparqlresultsincsv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_TSV", furi_sparqlresultsintsv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/Turtle", furi_turtle },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/TriG", furi_trig } };

struct symbol_entry < html_version, e_halign > halign_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "left", al_left },
    { { HTML_2_0 }, { HTML_UNDEF }, "center", al_center },
    { { HTML_2_0 }, { HTML_UNDEF }, "right", al_right },
    { { HTML_2_0 }, { HTML_UNDEF }, "justify", al_justify },
    { { HTML_2_0 }, { HTML_UNDEF }, "char", al_char } };

struct symbol_entry < html_version, e_icalfreq > icalfreq_symbol_table [] =
{   { { HTML_RDF10 }, { HTML_UNDEF }, "secondly", if_sec },
    { { HTML_RDF10 }, { HTML_UNDEF }, "minutely", ical_min }, // not that it means minutely!!
    { { HTML_RDF10 }, { HTML_UNDEF }, "hourly", ical_hour },
    { { HTML_RDF10 }, { HTML_UNDEF }, "daily", ical_day },
    { { HTML_RDF10 }, { HTML_UNDEF }, "weekly", ical_week },
    { { HTML_RDF10 }, { HTML_UNDEF }, "monthly", ical_month },
    { { HTML_RDF10 }, { HTML_UNDEF }, "yearly", ical_year } };

struct symbol_entry < html_version, e_icc > icc_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/GRACoL TR006 2007", icc_CGATS_GRACoL_TR006_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SNAP TR002 2007", icc_CGATS_SNAP_TR002_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SWOP TR003 2007", icc_CGATS_SWOP_TR003_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SWOP TR005 2007", icc_CGATS_SWOP_TR005_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC1", icc_CGATS21_2_CRPC1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC2", icc_CGATS21_2_CRPC2 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC3", icc_CGATS21_2_CRPC3 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC4", icc_CGATS21_2_CRPC4 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC5", icc_CGATS21_2_CRPC5 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC6", icc_CGATS21_2_CRPC6 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC7", icc_CGATS21_2_CRPC7 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA39", icc_FOGRA39 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA40", icc_FOGRA40 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA47", icc_FOGRA47 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA51", icc_FOGRA51 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA52", icc_FOGRA52 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA54", icc_FOGRA54 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "Japan Color 2011", icc_Japan_Color_2011 } };

struct symbol_entry < html_version, e_image_rendering > image_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", ir_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", ir_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeQuality", ir_optimisequality },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", ir_inherit } };

struct symbol_entry < html_version, e_indentalign > indentalign_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "left", ia_left },
    { { HTML_5_2 }, { HTML_UNDEF }, "center", ia_centre },
    { { HTML_5_2 }, { HTML_UNDEF }, "right", ia_right },
    { { HTML_5_2 }, { HTML_UNDEF }, "auto", ia_auto },
    { { HTML_5_2 }, { HTML_UNDEF }, "id", ia_id } };

struct symbol_entry < html_version, e_inky > inky_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "sourcegraphic", ink_sourcegraphic },
    { { HTML_2_0 }, { HTML_UNDEF }, "sourcealpha", ink_sourcealpha },
    { { HTML_2_0 }, { HTML_UNDEF }, "backgroundimage", ink_backgroundimage },
    { { HTML_2_0 }, { HTML_UNDEF }, "backgroundalpha", ink_backgroundalpha },
    { { HTML_2_0 }, { HTML_UNDEF }, "fillpaint", ink_fillpaint },
    { { HTML_2_0 }, { HTML_UNDEF }, "strokepaint", ink_strokepaint } };

struct symbol_entry < html_version, e_inputmode > inputmode_symbol_table [] =
{   { { HTML_JAN18 }, { HTML_UNDEF }, "decimal", im_decimal },
    { { HTML_JAN13, HV_NOT52 }, { HTML_UNDEF }, "email", im_email },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "full-width-latin", im_fullwidthlatin },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "katakana", im_katakana },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "kana", im_kana },
    { { HTML_JAN15, HV_NOT52 }, { HTML_DEC17 }, "kana-name", im_kananame },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin", im_latin },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin-name", im_latinname },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin-prose", im_latinprose },
    { { HTML_JAN18 }, { HTML_UNDEF }, "none", im_none },
    { { HTML_JAN13 }, { HTML_UNDEF }, "numeric", im_numeric  },
    { { HTML_JAN18 }, { HTML_UNDEF }, "search", im_search },
    { { HTML_JAN13 }, { HTML_UNDEF }, "tel", im_tel },
    { { HTML_JAN18 }, { HTML_UNDEF }, "text", im_text },
    { { HTML_JAN13 }, { HTML_UNDEF }, "verbatim", im_verbatim },
    { { HTML_JAN13 }, { HTML_UNDEF }, "url", im_url } };

struct symbol_entry < html_version, e_inputplus > inputplus_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "audio", ip_audio },
    { { HTML_PLUS }, { HTML_PLUS }, "checkbox", ip_checkbox },
    { { HTML_PLUS }, { HTML_PLUS }, "date", ip_date },
    { { HTML_PLUS }, { HTML_PLUS }, "float", ip_float },
    { { HTML_PLUS }, { HTML_PLUS }, "image", ip_image },
    { { HTML_PLUS }, { HTML_PLUS }, "int", ip_int },
    { { HTML_PLUS }, { HTML_PLUS }, "radio", ip_radio },
    { { HTML_PLUS }, { HTML_PLUS }, "range", ip_range },
    { { HTML_PLUS }, { HTML_PLUS }, "reset", ip_reset },
    { { HTML_PLUS }, { HTML_PLUS }, "scribble", ip_scribble },
    { { HTML_PLUS }, { HTML_PLUS }, "submit", ip_submit },
    { { HTML_PLUS }, { HTML_PLUS }, "text", ip_text },
    { { HTML_PLUS }, { HTML_PLUS }, "url", ip_url } };

struct symbol_entry < html_version, e_inputtype > inputtype_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", it_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", it_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", it_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", it_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", it_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", it_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", it_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", it_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", it_text } };

struct symbol_entry < html_version, e_inputtype3 > inputtype3_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i3_checkbox },
    { { HTML_2_0, HV_RFC_1867 }, { HTML_UNDEF }, "file", i3_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i3_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i3_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i3_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i3_radio },
    { { HTML_3_0 }, { HTML_3_0 }, "range", i3_range },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i3_reset },
    { { HTML_3_0 }, { HTML_3_0 }, "scribble", i3_scribble },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i3_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i3_text } };

struct symbol_entry < html_version, e_inputtype32 > inputtype32_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i2_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", i2_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i2_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i2_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i2_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i2_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i2_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i2_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i2_text } };

struct symbol_entry < html_version, e_inputtype4 > inputtype4_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "button", i4_button },
    { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i4_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", i4_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i4_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i4_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i4_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i4_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i4_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i4_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i4_text } };

struct symbol_entry < html_version, e_inputtype5 > inputtype5_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "button", i5_button },
    { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i5_checkbox },
    { { HTML_JAN05 }, { HTML_UNDEF }, "color", i5_colour },
    { { HTML_JAN05 }, { HTML_UNDEF }, "date", i5_date },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "datetime", i5_datetime },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "datetime-local", i5_datetime_local },
    { { HTML_JAN05 }, { HTML_UNDEF }, "email", i5_email },
    { { 2, 1 }, { HTML_UNDEF }, "file", i5_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i5_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i5_image },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "month", i5_month },
    { { HTML_JAN05 }, { HTML_UNDEF }, "number", i5_number },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i5_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i5_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i5_reset },
    { { HTML_3_0 }, { HTML_UNDEF }, "range", i5_range },
    { { HTML_JAN05 }, { HTML_UNDEF }, "search", i5_search },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i5_submit },
    { { HTML_JAN05 }, { HTML_UNDEF }, "tel", i5_tel },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i5_text },
    { { HTML_JAN05 }, { HTML_UNDEF }, "time", i5_time },
    { { HTML_JAN05 }, { HTML_UNDEF }, "url", i5_url },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "week", i5_week } };

struct symbol_entry < html_version, e_jtoken > jtoken_symbol_table [] =
{   { { HTML_JAN14 }, { HTML_UNDEF }, "@base", jt_base },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@container", jt_container },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@context", jt_context },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@direction", jt_direction },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@graph", jt_graph },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@id", jt_id },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@import", jt_import },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@included", jt_included },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@index", jt_index },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@json", jt_json },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@language", jt_language },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@list", jt_list },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@nest", jt_nest },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@none", jt_none },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@prefix", jt_prefix },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@propagate", jt_propagate },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@protected", jt_protected },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@reverse", jt_reverse },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@set", jt_set },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@type", jt_type },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@value", jt_value },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@version", jt_version },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@vocab", jt_vocab } };

struct symbol_entry < html_version, e_kind > kind_symbol_table [] =
{   { { HTML_JUL10 }, { HTML_UNDEF }, "subtitles", k_subtitles },
    { { HTML_JUL10 }, { HTML_UNDEF }, "captions", k_captions },
    { { HTML_JUL10 }, { HTML_UNDEF }, "descriptions", k_descriptions },
    { { HTML_JUL10 }, { HTML_UNDEF }, "chapters", k_chapters },
    { { HTML_JUL10 }, { HTML_UNDEF }, "metadata", k_metadata } };

struct symbol_entry < html_version, e_length_absolute > length_absolute_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "cm", l_cm },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "mm", l_mm },
    { { HTML_JUL19, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "q", l_q }, // with CSS 3
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "in", l_in },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "pc", l_pc },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "pt", l_pt },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "px", l_px } };

struct symbol_entry < html_version, e_length_relative > length_relative_symbol_table [] =
{   { { HTML_3_2, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "%", l_percent },
    { { HTML_4_0 }, { HTML_4_01 }, "*", l_star },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "em", l_em },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "ex", l_ex },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "cap", l_cap },
    { { HTML_JUL19, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "ch", l_ch },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "ic", l_ic },
    { { HTML_JUL19, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "rem", l_rem },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "lh", l_lh },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "rlh", l_rlh },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vw", l_vw },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vh", l_vh },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vi", l_vi },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vb", l_vb },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vmin", l_vmin },
    { { HTML_JAN21, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "vmax", l_vmax } };

struct symbol_entry < html_version, e_linebreak > linebreak_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "auto", lb_auto },
    { { XHTML_1_0 }, { HTML_UNDEF }, "newline", lb_newline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "indentingnewline", lb_indentingnewline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "nobreak", lb_nobreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "goodbreak", lb_goodbreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "badbreak", lb_badbreak } };

struct symbol_entry < html_version, e_linkparam > linkparam_symbol_table [] =
{   { { HTML_NOV17 }, { HTML_UNDEF }, "anchor", lp_anchor },
    { { HTML_NOV17 }, { HTML_UNDEF }, "hreflang", lp_hreflang },
    { { HTML_NOV17 }, { HTML_UNDEF }, "media", lp_media },
    { { HTML_NOV17 }, { HTML_UNDEF }, "rel", lp_rel },
    { { HTML_NOV17 }, { HTML_UNDEF }, "rev", lp_rev },
    { { HTML_NOV17 }, { HTML_UNDEF }, "title", lp_title },
    { { HTML_NOV17 }, { HTML_UNDEF }, "title*", lp_titlestar },
    { { HTML_NOV17 }, { HTML_UNDEF }, "type", lp_type } };

struct symbol_entry < html_version, e_listtype > listtype_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "1", li_1 },
    { { HTML_UNDEF }, { HTML_UNDEF }, "a", li_a },
    { { HTML_UNDEF }, { HTML_UNDEF }, "A", li_A },
    { { HTML_UNDEF }, { HTML_UNDEF }, "i", li_i },
    { { HTML_UNDEF }, { HTML_UNDEF }, "I", li_I } };

struct symbol_entry < html_version, e_longdivstyle > longdivstyle_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "lefttop", ls_lefttop },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedrightright", ls_stackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "mediumstackedrightright", ls_mediumstackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "shortstackedrightright", ls_shortstackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "righttop", ls_righttop },
    { { HTML_5_2 }, { HTML_UNDEF }, "left/\\right", ls_leftslashright },
    { { HTML_5_2 }, { HTML_UNDEF }, "left)(right", ls_leftketbraright },
    { { HTML_5_2 }, { HTML_UNDEF }, ":right=right", ls_rightequalright },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedleftleft", ls_stackedleftleft },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedleftlinetop", ls_stackedleftlinetop } };

struct symbol_entry < html_version, e_mah > mah_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "go", mah_go },
    { { HTML_UNDEF }, { HTML_UNDEF }, "done", mah_done },
    { { HTML_UNDEF }, { HTML_UNDEF }, "next", mah_next },
    { { HTML_UNDEF }, { HTML_UNDEF }, "search", mah_search },
    { { HTML_UNDEF }, { HTML_UNDEF }, "send", mah_send } };

struct symbol_entry < html_version, e_mathalign > mathalign_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "axis", ma_axis },
    { { XHTML_1_0 }, { HTML_UNDEF }, "baseline", ma_baseline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bottom", ma_bottom },
    { { XHTML_1_0 }, { HTML_UNDEF }, "center", ma_centre },
    { { XHTML_1_0 }, { HTML_UNDEF }, "top", ma_top } };

struct symbol_entry < html_version, e_mathlocation > mathlocation_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "w", ml_w },
    { { HTML_5_2 }, { HTML_UNDEF }, "nw", ml_nw },
    { { HTML_5_2 }, { HTML_UNDEF }, "n", ml_n },
    { { HTML_5_2 }, { HTML_UNDEF }, "ne", ml_ne },
    { { HTML_5_2 }, { HTML_UNDEF }, "e", ml_e },
    { { HTML_5_2 }, { HTML_UNDEF }, "se", ml_se },
    { { HTML_5_2 }, { HTML_UNDEF }, "s", ml_s },
    { { HTML_5_2 }, { HTML_UNDEF }, "sw", ml_sw } };

struct symbol_entry < html_version, e_mathoverflow > mathoverflow_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "elide", ov_elide },
    { { HTML_5_2 }, { HTML_UNDEF }, "linebreak", ov_linebreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "scale", ov_scale },
    { { XHTML_1_0 }, { HTML_UNDEF }, "scroll", ov_scroll },
    { { XHTML_1_0 }, { HTML_UNDEF }, "truncate", ov_truncate } };

struct symbol_entry < html_version, e_mathnotation > mathnotation_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "longdiv", mn_longdiv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "actuarial", mn_actuarial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "radical", mn_radical },
    { { XHTML_1_0 }, { HTML_UNDEF }, "box", mn_box },
    { { XHTML_1_0 }, { HTML_UNDEF }, "roundedbox", mn_roundedbox },
    { { XHTML_1_0 }, { HTML_UNDEF }, "circle", mn_circle },
    { { XHTML_1_0 }, { HTML_UNDEF }, "left", mn_left },
    { { XHTML_1_0 }, { HTML_UNDEF }, "right", mn_right },
    { { XHTML_1_0 }, { HTML_UNDEF }, "top", mn_top },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bottom", mn_bottom },
    { { XHTML_1_0 }, { HTML_UNDEF }, "updiagonalstrike", mn_updiagonalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "downdiagonalstrike", mn_downdiagonalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verticalstrike", mn_verticalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "horizontalstrike", mn_horizontalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "phasorangle", mn_phasorangle },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_uparrow", mn_uparrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_rightarrow", mn_rightarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_downarrow", mn_downarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_leftarrow", mn_leftarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northwestarrow", mn_northwestarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_southwestarrow", mn_southwestarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_southeastarrow", mn_southeastarrow },
    { { HTML_5_2 }, { HTML_UNDEF }, "northeastarrow", mn_northeastarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_updownarrow", mn_updownarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_leftrightarrow", mn_leftrightarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northwestsoutheastarrow", mn_northwestsoutheastarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northeastsouthwestarrow", mn_northeastsouthwestarrow },
    { { HTML_5_2 }, { HTML_UNDEF }, "madruwb", mn_madruwb } };

struct symbol_entry < html_version, e_mathvariant > mathvariant_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "normal", mv_normal },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold", mv_bold },
    { { XHTML_1_0 }, { HTML_UNDEF }, "italic", mv_italic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-italic", mv_bolditalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "double-struck", mv_doublestruck },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-fraktur", mv_boldfraktur },
    { { XHTML_1_0 }, { HTML_UNDEF }, "script", mv_script },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-script", mv_boldscript },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fraktur", mv_fraktur },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif", mv_sansserif },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-sans-serif", mv_boldsansserif },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif-italic", mv_sansserifitalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif-bold-italic", mv_sansserifbolditalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "monospace", mv_monospace },
    { { HTML_5_2 }, { HTML_UNDEF }, "initial", mv_initial },
    { { HTML_5_2 }, { HTML_UNDEF }, "tailed", mv_tailed },
    { { HTML_5_2 }, { HTML_UNDEF }, "looped", mv_looped },
    { { HTML_5_2 }, { HTML_UNDEF }, "stretched", mv_stretched } };

struct symbol_entry < html_version, e_matrixtype > matrixtype_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "matrix", mt_matrix },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "saturate", mt_saturate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hueRotate", mt_huerotate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "luminanceToAlpha", mt_luminancetoalpha } };

struct symbol_entry < html_version, e_media > media_symbol_table [] =
{   { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "all", md_all },
    { { HTML_4_0, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "aural", md_aural },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "braille", md_braille },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "embossed", md_embossed },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "handheld", md_handheld },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "print", md_print },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "projection", md_projection },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "screen", md_screen },
    { { HTML_4_0, 0, 0, H2_CSS_21_PLUS }, { HTML_UNDEF }, "speech", md_speech },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "tty", md_tty },
    { { HTML_4_0, 0, 0 }, { HTML_UNDEF }, "tv", md_tv } };

struct symbol_entry < html_version, e_mediafeature > mediafeature_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "any-hover", mef_any_hover },
    { { HTML_JAN05 }, { HTML_UNDEF }, "any-pointer", mef_any_pointer },
    { { HTML_JAN05 }, { HTML_UNDEF }, "aspect-ratio", mef_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "color", mef_colour },
    { { HTML_JAN05 }, { HTML_UNDEF }, "color-gamut", mef_colour_gamut },
    { { HTML_JAN05 }, { HTML_UNDEF }, "color-index", mef_colour_index },
    { { HTML_JAN05 }, { HTML_UNDEF }, "device-aspect-ratio", mef_device_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "device-height", mef_device_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "device-width", mef_device_width },
    { { HTML_JUL21 }, { HTML_UNDEF }, "display-mode", mef_display_mode },
    { { HTML_JUL21 }, { HTML_UNDEF }, "forced-colors", mef_forced_colours },
    { { HTML_JAN05 }, { HTML_UNDEF }, "grid", mef_grid },
    { { HTML_JAN05 }, { HTML_UNDEF }, "height", mef_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "hover", mef_hover },
    { { HTML_JUL21 }, { HTML_UNDEF }, "inverted-colors", mef_inverted_colours },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-aspect-ratio", mef_max_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-color", mef_max_colour },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-color-index", mef_max_colour_index },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-device-aspect-ratio", mef_max_device_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-device-height", mef_max_device_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-device-width", mef_max_device_width },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-height", mef_max_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-monochrome", mef_max_monochrome },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-resolution", mef_max_resolution },
    { { HTML_JAN05 }, { HTML_UNDEF }, "max-width", mef_max_width },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-aspect-ratio", mef_min_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-color", mef_min_colour },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-color-index", mef_min_colour_index },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-device-aspect-ratio", mef_min_device_aspect_ratio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-device-height", mef_min_device_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-device-width", mef_min_device_width },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-height", mef_min_height },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-monochrome", mef_min_monochrome },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-resolution", mef_min_resolution },
    { { HTML_JAN05 }, { HTML_UNDEF }, "min-width", mef_min_width },
    { { HTML_JAN05 }, { HTML_UNDEF }, "monochrome", mef_monochrome },
    { { HTML_JAN05 }, { HTML_UNDEF }, "orientation", mef_orientation },
    { { HTML_JAN05 }, { HTML_UNDEF }, "overflow-block", mef_overflow_block },
    { { HTML_JAN05 }, { HTML_UNDEF }, "overflow-inline", mef_overflow_inline },
    { { HTML_JAN05 }, { HTML_UNDEF }, "pointer", mef_pointer },
    { { HTML_JUL21 }, { HTML_UNDEF }, "prefers-color-scheme", mef_prefers_colour_scheme },
    { { HTML_JUL21 }, { HTML_UNDEF }, "prefers-contrast", mef_prefers_contrast },
    { { HTML_JUL21 }, { HTML_UNDEF }, "prefers-reduced-motio", mef_prefers_reduced_motion },
    { { HTML_JAN05 }, { HTML_UNDEF }, "resolution", mef_resolution },
    { { HTML_JAN05 }, { HTML_UNDEF }, "scan", mef_scan },
    { { HTML_JAN05 }, { HTML_UNDEF }, "scripting", mef_scripting },
    { { HTML_JAN05 }, { HTML_UNDEF }, "update", mef_update },
    { { HTML_JAN05 }, { HTML_UNDEF }, "width", mef_width } };

struct symbol_entry < html_version, e_mediakeyword > mediakeyword_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "and", mk_and },
    { { HTML_JAN05 }, { HTML_UNDEF }, "=", mk_eq },
    { { HTML_JAN05 }, { HTML_UNDEF }, ">=", mk_ge },
    { { HTML_JAN05 }, { HTML_UNDEF }, ">", mk_gt },
    { { HTML_4_0 }, { HTML_UNDEF }, "ident", mk_ident },
    { { HTML_JAN05 }, { HTML_UNDEF }, "<=", mk_le },
    { { HTML_JAN05 }, { HTML_UNDEF }, "<", mk_lt },
    { { HTML_JAN05 }, { HTML_UNDEF }, "or", mk_or },
    { { HTML_4_0 }, { HTML_UNDEF }, "not", mk_not },
    { { HTML_4_0 }, { HTML_UNDEF }, "only", mk_only } };

struct symbol_entry < html_version, e_method > method_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "delete", md_delete },
    { { HTML_JUL12, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "dialog", md_dialogue },
    { { HTML_PLUS }, { HTML_UNDEF }, "get", md_get },
    { { HTML_PLUS }, { HTML_UNDEF }, "post", md_post },
    { { HTML_PLUS }, { HTML_PLUS }, "put", md_put } };

struct symbol_entry < html_version, e_mf_identifier > mf_identifier_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "model", mfi_model },
    { { HTML_4_0 }, { HTML_UNDEF }, "mpn", mfi_mpn },
    { { HTML_4_0 }, { HTML_UNDEF }, "upc", mfi_upc },
    { { HTML_4_0 }, { HTML_UNDEF }, "isbn", mfi_isbn },
    { { HTML_4_0 }, { HTML_UNDEF }, "issn", mfi_issn },
    { { HTML_4_0 }, { HTML_UNDEF }, "ean", mfi_ean },
    { { HTML_4_0 }, { HTML_UNDEF }, "jan", mfi_jan },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfi_sn },
    { { HTML_4_0 }, { HTML_UNDEF }, "mvin", mfi_vin },
    { { HTML_4_0 }, { HTML_UNDEF }, "msku", mfi_sku } };

struct symbol_entry < html_version, e_mf_itemtype > mf_itemtype_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "opening", mfit_opening },
    { { HTML_4_0 }, { HTML_UNDEF }, "housing", mfit_housing },
    { { HTML_4_0 }, { HTML_UNDEF }, "product", mfit_product },
    { { HTML_4_0 }, { HTML_UNDEF }, "business", mfit_business },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfit_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "person", mfit_person },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfit_place },
    { { HTML_4_0 }, { HTML_UNDEF }, "website", mfit_website },
    { { HTML_4_0 }, { HTML_UNDEF }, "url", mfit_url } };

struct symbol_entry < html_version, e_mf_listing_action > mf_listing_action_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "sell", mfla_sell },
    { { HTML_4_0 }, { HTML_UNDEF }, "rent", mfla_rent },
    { { HTML_4_0 }, { HTML_UNDEF }, "trade", mfla_trade },
    { { HTML_4_0 }, { HTML_UNDEF }, "meet", mfla_meet },
    { { HTML_4_0 }, { HTML_UNDEF }, "announce", mfla_announce },
    { { HTML_4_0 }, { HTML_UNDEF }, "offer", mfla_offer },
    { { HTML_4_0 }, { HTML_UNDEF }, "wanted", mfla_wanted },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfla_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "service", mfla_service } };

struct symbol_entry < html_version, e_mf_method > mf_method_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "publish", mfm_publish },
    { { HTML_4_0 }, { HTML_UNDEF }, "request", mfm_request },
    { { HTML_4_0 }, { HTML_UNDEF }, "reply", mfm_reply },
    { { HTML_4_0 }, { HTML_UNDEF }, "add", mfm_add },
    { { HTML_4_0 }, { HTML_UNDEF }, "cancel", mfm_cancel },
    { { HTML_4_0 }, { HTML_UNDEF }, "refresh", mfm_refresh },
    { { HTML_4_0 }, { HTML_UNDEF }, "counter", mfm_counter },
    { { HTML_4_0 }, { HTML_UNDEF }, "declinecounter", mfm_declinecounter } };

struct symbol_entry < html_version, e_mf_reviewtype > mf_reviewtype_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "product", mfr_product },
    { { HTML_4_0 }, { HTML_UNDEF }, "business", mfr_business },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfr_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "person", mfr_person },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfr_place },
    { { HTML_4_0 }, { HTML_UNDEF }, "website", mfr_website },
    { { HTML_4_0 }, { HTML_UNDEF }, "url", mfr_url } };

struct symbol_entry < html_version, e_myersbriggs > myersbriggs_symbol_table [] =
        // why not the astrology stuff too?
{   { { XHTML_1_0 }, { HTML_UNDEF }, "INFP", mb_INFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESFP", mb_ESFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INTJ", mb_INTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESFJ", mb_ESFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INTP", mb_INTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENFP", mb_ENFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISTJ", mb_ISTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESTP", mb_ESTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INFJ", mb_INFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENFJ", mb_ENFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISTP", mb_ISTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENTJ", mb_ENTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISFP", mb_ISFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENTP", mb_ENTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISFJ", mb_ISFJ } };

struct symbol_entry < html_version, e_namedspace > namedspace_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "negativeveryverythinmathspace", nd_negativeveryverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeverythinmathspace", nd_negativeverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativethinmathspace", nd_negativethinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativemediummathspace", nd_negativemediummathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativethickmathspace", nd_negativethickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeverythickmathspace", nd_negativeverythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeveryverythickmathspace", nd_negativeveryverythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "veryverythinmathspace", nd_veryverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verythinmathspace", nd_verythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "thinmathspace", nd_thinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "mediummathspace", nd_mediummathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "thickmathspace", nd_thickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verythickmathspace", nd_verythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "veryverythickmathspace", nd_veryverythickmathspace } };

struct symbol_entry < html_version, e_namespace > namespace_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "bibo", ns_bibo },
    { { XHTML_1_0 }, { HTML_UNDEF }, "cc", ns_cc },
    { { XHTML_1_0 }, { HTML_UNDEF }, "crs", ns_crs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbp", ns_dbp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbp_owl", ns_dbp_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbr", ns_dbr },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dc", ns_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dcterms", ns_dcterms },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dt", ns_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ebuttm", ns_ebuttm },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ebutts", ns_ebutts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ex", ns_ex },
    { { XHTML_1_0 }, { HTML_UNDEF }, "exsl", ns_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fn", ns_fn },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fo", ns_fo },
    { { XHTML_1_0 }, { HTML_UNDEF }, "foaf", ns_foaf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "html", ns_html },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ims", ns_ims },
    { { XHTML_1_0 }, { HTML_UNDEF }, "its", ns_its },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittm", ns_ittm },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittp", ns_ittp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "itts", ns_itts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittx", ns_ittx },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittxi", ns_ittxi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittxt", ns_ittxt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "math", ns_math },
    { { XHTML_1_0 }, { HTML_UNDEF }, "odd", ns_odd },
    { { XHTML_1_0 }, { HTML_UNDEF }, "oex", ns_oex },
    { { XHTML_1_0 }, { HTML_UNDEF }, "owl", ns_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "owlxml", ns_owlxml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rddl", ns_rddl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdf", ns_rdf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdfa", ns_rdfa },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdfs", ns_rdfs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "saxon", ns_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, "smil", ns_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, "smpte", ns_smpte },
    { { XHTML_1_0 }, { HTML_UNDEF }, "svg", ns_svg },
    { { XHTML_1_0 }, { HTML_UNDEF }, "tt", ns_tt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ttf", ns_ttf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ttp", ns_ttp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "tts", ns_tts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "v", ns_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, "vcard", ns_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xalan", ns_xalan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xf", ns_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xhtml", ns_xhtml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xhv", ns_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xi", ns_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xlink", ns_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xmlevents", ns_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xmlns", ns_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xs", ns_xs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xsi", ns_xsi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xslt", ns_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xtm", ns_xtm } };

struct symbol_entry < html_version, e_nit_macro > nit_macro_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "class-count", nm_class_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-decl-count", nm_class_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-decl-int", nm_class_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-int", nm_class_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-name", nm_class_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-title", nm_class_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "compile-time", nm_compile_time },
    { { HTML_TAGS }, { HTML_UNDEF }, "config", nm_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-article", nm_context_article },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-body", nm_context_body },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-build", nm_context_build },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-case", nm_context_case },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-cgi", nm_context_cgi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-classic", nm_context_classic },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-clear", nm_context_clear },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-config", nm_context_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-copy", nm_context_copy },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-corpus", nm_context_corpus },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-crosslinks", nm_context_crosslinks },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css", nm_context_css },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-cascade", nm_context_css_cascade },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-extension", nm_context_css_extension },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-selector", nm_context_css_selector },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-version", nm_context_css_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-custom-elements", nm_context_custom_elements },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-dc", nm_context_dc },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-example", nm_context_example },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-export-root", nm_context_export_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-exports", nm_context_exports },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-extensions", nm_context_extensions },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ext-css", nm_context_ext_css },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-foaf", nm_context_foaf },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-forward", nm_context_forward },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-thread", nm_context_fred },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-info", nm_general_info },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-icu", nm_context_icu },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ignore", nm_context_ignore },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-info", nm_context_info },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-index", nm_context_index },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld", nm_context_jsonld },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld-extension", nm_context_jsonld_extension },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld-version", nm_context_jsonld_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-lang", nm_context_lang },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-links", nm_context_links },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-local", nm_context_local },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-main", nm_context_main },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-math", nm_context_math },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-max-file-size", nm_context_max_file_size },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-md-export", nm_context_md_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-meta", nm_context_meta },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-export", nm_context_mf_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-verify", nm_context_mf_verify },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-version", nm_context_mf_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-microdata", nm_context_microdata },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-msg", nm_context_msg },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-no-ex-check", nm_context_no_ex_check },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-once", nm_context_once },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-output", nm_context_output },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-persisted", nm_context_persisted },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rdfa", nm_context_rdfa },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rdf-version", nm_context_rdf_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rel", nm_context_rel },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-report", nm_context_report },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1867", nm_context_rfc_1867 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1942", nm_context_rfc_1942 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1980", nm_context_rfc_1980 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-2070", nm_context_rfc_2070 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-root", nm_context_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-schema", nm_context_schema },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-schema-version", nm_context_schema_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-comment", nm_context_shadow_comment },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-changed", nm_context_shadow_changed },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-enable", nm_context_shadow_enable },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-ignore", nm_context_shadow_ignore },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-persist", nm_context_shadow_persist },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-root", nm_context_shadow_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-ssi", nm_context_shadow_ssi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-space", nm_context_shadow_space },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadows", nm_context_shadows },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-site", nm_context_site },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-slob", nm_context_slob },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spec", nm_context_spec },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spell", nm_context_spell },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spell-path", nm_context_spell_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spellings", nm_context_spellings },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ssi", nm_context_ssi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-export", nm_context_stats_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-page", nm_context_stats_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-summary", nm_context_stats_summary },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-svg-version", nm_context_svg_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-tags", nm_context_tags },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-test", nm_context_test },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-title", nm_context_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-virtuals", nm_context_virtuals },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-xsd", nm_context_xsd },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-addr", nm_copy_addr },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-html", nm_copy_html },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-text", nm_copy_text },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-output", nm_general_output },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-path", nm_general_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-title", nm_grand_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "html-snippet", nm_html_snippet },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-count", nm_id_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-decl-count", nm_id_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-decl-int", nm_id_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-int", nm_id_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-name", nm_id_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-title", nm_id_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-line", nm_itemid_line },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-name", nm_itemid_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-page", nm_itemid_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-title", nm_itemid_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "level-name", nm_level_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "level-symbol", nm_level_symbol },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-after", nm_nit_after },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-before", nm_nit_before },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-code", nm_nit_code },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-doc", nm_nit_doc },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-long", nm_nit_doc_long },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-explanation", nm_nit_explanation },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-id", nm_nit_id },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-line", nm_nit_line },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-mote", nm_nit_mote },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-ns", nm_nit_ns },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-ref", nm_nit_ref },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-format", mn_nits_format },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-lost", mn_nits_lost },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-error", nm_page_error },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-name", nm_page_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-disk-path", nm_page_disk_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-site-path", nm_page_site_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-abbrev", nm_prog_abbrev },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-build", nm_prog_build },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-fullname", nm_prog_fullname },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-version", nm_prog_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-addr", nm_prog_webaddr },
    { { HTML_TAGS }, { HTML_UNDEF }, "query", nm_query },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-args", nm_run_args },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-catastrophe", nm_run_catastrophe },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-environment", nm_run_environment },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-count", nm_stat_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-detail", nm_stat_detail },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-int", nm_stat_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-name", nm_stat_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subname", nm_stat_subname },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subcount", nm_stat_subcount },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subdetail", nm_stat_subdetail },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subint", nm_stat_subint },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subtitle", nm_stats_subtitle },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-title", nm_stats_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-total", nm_stats_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-count", nm_tally_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-decl-count", nm_tally_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-decl-int", nm_tally_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-int", nm_tally_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-name", nm_tally_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-sum", nm_tally_sum },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-title", nm_tally_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-total", nm_tally_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-count", nm_tally_use_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-int", nm_tally_use_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-sum", nm_tally_use_sum },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-total", nm_tally_use_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-duration", nm_time_duration },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-finish", nm_time_finish },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-start", nm_time_start } };

struct symbol_entry < html_version, e_nit_section > nit_section_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "class", ns_class },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-foot", ns_class_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-head", ns_class_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "config", ns_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "config-foot", ns_config_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "config-head", ns_config_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "doc-foot", ns_doc_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "doc-head", ns_doc_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "export", ns_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "export-foot", ns_export_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "export-head", ns_export_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-foot", ns_grand_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-head", ns_grand_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "id", ns_nsid },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-foot", ns_id_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-head", ns_id_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid", ns_itemid },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-foot", ns_itemid_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-head", ns_itemid_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "init", ns_init },
    { { HTML_TAGS }, { HTML_UNDEF }, "init-foot", ns_init_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "init-head", ns_init_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "link", ns_link },
    { { HTML_TAGS }, { HTML_UNDEF }, "link-foot", ns_link_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "link-head", ns_link_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit", ns_nit },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-foot", ns_nits_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-head", ns_nits_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-page", ns_nits_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-foot", ns_page_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-head", ns_page_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow", ns_shadow },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow-foot", ns_shadow_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow-head", ns_shadow_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat", ns_stat },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-foot", ns_stats_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-head", ns_stats_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-sub", ns_substat },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subfoot", ns_stats_subfoot },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subhead", ns_stats_subhead },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally", ns_tally },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-foot", ns_tally_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-head", ns_tally_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "update", ns_update },
    { { HTML_TAGS }, { HTML_UNDEF }, "update-foot", ns_update_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "update-head", ns_update_head } };

struct symbol_entry < html_version, e_ogtype > ogtype_symbol_table [] =
{   { { HTML_OG_2010 }, { HTML_DEC11 }, "activity", og_activity },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "actor", og_actor },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "album", og_album },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "article", og_article },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "athlete", og_athlete },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "author", og_author },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "band", og_band },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "bar", og_bar },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "blog", og_blog },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "book", og_book },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "cafe", og_cafe },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "cause", og_cause },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "company", og_company },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "city", og_city },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "country", og_country },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "director", og_director },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "drink", og_drink },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "food", og_food },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "game", og_game },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "government", og_government },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "hotel", og_hotel },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "landmark", og_landmark },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "movie", og_movie },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "musician", og_musician },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.song", og_musicsong },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.album", og_musicalbum },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.playlist", og_musicplaylist },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.radio_station", og_musicradiostation },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "product", og_product },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "non_profit", og_non_profit },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "politician", og_politician },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "profile", og_profile },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "public_figure", og_public_figure },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "restaurant", og_restaurant },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "school", og_school },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "song", og_song },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sport", og_sport },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sports_league", og_sports_league },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sports_team", og_sports_team },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "state_province", og_state_province },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "tv_show", og_tv_show },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "university", og_university },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.movie", og_videomovie },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.episode", og_videoepisode },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.tv_show", og_videotvshow },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.other", og_videoother },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "website", og_website } };

struct symbol_entry < html_version, e_page_orientation > page_orientation_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-270", po_270 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-180", po_180 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-90-fill", po_90  },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "0", po0 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "90", po90 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "180", po180 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "270", po270 } };

struct symbol_entry < html_version, e_paintkeyword > paintkeyword_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", pk_none },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "child", pk_child },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "context-fill", pk_contextfill  },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "context-stroke", pk_contextstroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "currentColor", pk_currentcolour },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inherit", pk_inherit },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "icc-colour", pk_icccolour },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "url", pk_url } };

struct symbol_entry < html_version, e_plusstyle > plusstyle_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "b", ps_b },
    { { HTML_UNDEF }, { HTML_UNDEF }, "i", ps_i },
    { { HTML_UNDEF }, { HTML_UNDEF }, "p", ps_p },
    { { HTML_UNDEF }, { HTML_UNDEF }, "s", ps_s },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sub", ps_sub },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sup", ps_sup },
    { { HTML_UNDEF }, { HTML_UNDEF }, "tt", ps_tt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "u", ps_u } };

struct symbol_entry < html_version, e_pointer_events > pointer_events_symbol_table [] =
{   { { HTML_SVG21, 0, HE_SVG_21 }, { HTML_UNDEF }, "auto", pe_auto },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "boundingBox", pe_boundingbox },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "bounding-box", pe_bounding_box },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visiblePainted", pe_visiblepainted },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visibleFill", pe_visiblefill },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visibleStroke", pe_visiblestroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visible", pe_visible },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "painted", pe_painted },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "fill", pe_fill },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "stroke", pe_stroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "all", pe_all },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", pe_none },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", pe_inherit } };

// a couple of these are only defined in the HTML+ text, not the DTD
struct symbol_entry < html_version, e_print > print_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "footnote", pt_footnote },
    { { HTML_UNDEF }, { HTML_UNDEF }, "reference", pt_reference },
    { { HTML_UNDEF }, { HTML_UNDEF }, "section", pt_section },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sidebar", pt_sidebar },
    { { HTML_UNDEF }, { HTML_UNDEF }, "silent", pt_silent } };

struct symbol_entry < html_version, e_quote_style > quote_style_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "none", qs_none },
    { { HTML_UNDEF }, { HTML_UNDEF }, "c", qs_c },
    { { HTML_UNDEF }, { HTML_UNDEF }, "csv", qs_csv },
    { { HTML_UNDEF }, { HTML_UNDEF }, "double", qs_double },
    { { HTML_UNDEF }, { HTML_UNDEF }, "html", qs_html },
    { { HTML_UNDEF }, { HTML_UNDEF }, "single", qs_single } };

struct symbol_entry < html_version, e_referrer > referrer_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "no-referrer", rf_no },
    { { HTML_UNDEF }, { HTML_UNDEF }, "no-referrer-when-downgrade", rf_downgrade },
    { { HTML_UNDEF }, { HTML_UNDEF }, "same-origin", rf_same },
    { { HTML_UNDEF }, { HTML_UNDEF }, "origin", rf_origin },
    { { HTML_UNDEF }, { HTML_UNDEF }, "strict-origin", rf_strict },
    { { HTML_UNDEF }, { HTML_UNDEF }, "strict-origin-when-cross-origin", rf_strictcross },
    { { HTML_UNDEF }, { HTML_UNDEF }, "origin-when-cross-origin", rf_cross },
    { { HTML_UNDEF }, { HTML_UNDEF }, "unsafe-url", rf_unsafe } };

struct symbol_entry < html_version, e_rendering_in_tents > rendering_in_tents_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "auto", ri_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "perceptual", ri_perceptual },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "relative-colorimetric", ri_relativecolourimetric },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "saturation", ri_saturation },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "absolute-colorimetric", ri_absolutecolourimetric } };

struct symbol_entry < html_version, e_rules > rules_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "none", ru_none },
    { { HTML_2_0 }, { HTML_UNDEF }, "groups", ru_groups },
    { { HTML_2_0 }, { HTML_UNDEF }, "rows", ru_rows },
    { { HTML_2_0 }, { HTML_UNDEF }, "cols", ru_cols },
    { { HTML_2_0 }, { HTML_UNDEF }, "all", ru_all } };

struct symbol_entry < html_version, e_sandbox > sandbox_symbol_table [] =
{   { { HTML_JUL20, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, "allow-downloads-without-user-activation", sand_adwua },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-forms", sand_forms },
    { { HTML_JAN16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-modals", sand_modals },
    { { HTML_JUL16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-orientation-lock", sand_orientation },
    { { HTML_JAN13, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-pointer-lock", sand_pointer },
    { { HTML_JUL12, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-popups", sand_popups },
    { { HTML_JAN16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-popups-to-escape-sandbox", sand_popupescape },
    { { HTML_JUL16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-presentation", sand_presentation },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-same-origin", sand_origin },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-scripts", sand_scripts },
    { { HTML_JUL20, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-storage-access-by-user-activation", sand_asabua },
    { { HTML_JAN11, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation", sand_navigation },
    { { HTML_JUL17, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation-by-user-activation", sand_atnbua },
    { { HTML_APR22, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation-to-custom-protocols", sand_atntcp },
    { { HTML_JUL20 }, { HTML_UNDEF }, "allow-downloads", sand_ad } };

struct symbol_entry < html_version, e_scei > scei_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL  }, { HTML_UNDEF }, "after", scei_after },
    { { HTML_SVG12, 0, HE_SVG_12_FULL  }, { HTML_UNDEF }, "before", scei_before },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "center", scei_centre },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "end", scei_end },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "start", scei_start },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", scei_inherit } };

struct symbol_entry < html_version, e_severity > severity_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, CATASTROPHE, es_catastrophic },
    { { HTML_TAGS }, { HTML_UNDEF }, ERR, es_error },
    { { HTML_TAGS }, { HTML_UNDEF }, WARNING, es_warning },
    { { HTML_TAGS }, { HTML_UNDEF }, INFO, es_info },
    { { HTML_TAGS }, { HTML_UNDEF }, COMMENT, es_comment },
    { { HTML_TAGS }, { HTML_UNDEF }, DBG, es_debug },
    { { HTML_TAGS }, { HTML_UNDEF }, VARIABLE, es_variable },
    { { HTML_TAGS }, { HTML_UNDEF }, STRUCTURE, es_structure },
    { { HTML_TAGS }, { HTML_UNDEF }, DETAIL, es_detail },
    { { HTML_TAGS }, { HTML_UNDEF }, SPLURGE, es_splurge },
    { { HTML_TAGS }, { HTML_UNDEF }, ALL, es_all } };

struct symbol_entry < html_version, e_shadow > shadow_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "no", sh_no },
    { { HTML_TAGS }, { HTML_UNDEF }, "pages", sh_pages },
#ifndef NOLYNX
    { { HTML_TAGS }, { HTML_UNDEF }, "hard", sh_hard },
    { { HTML_TAGS }, { HTML_UNDEF }, "soft", sh_soft },
#endif // NOLYNX
    { { HTML_TAGS }, { HTML_UNDEF }, "all", sh_copy },
    { { HTML_TAGS }, { HTML_UNDEF }, "dedu", sh_dedu },
    { { HTML_TAGS }, { HTML_UNDEF }, "report", sh_report } };

struct symbol_entry < html_version, e_shape7 > shape7_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "circle", s7_circ },
    { { HTML_JAN05 }, { HTML_UNDEF }, "circ", s7_circ },
    { { HTML_JAN05 }, { HTML_UNDEF }, "default", s7_default },
    { { HTML_JAN05 }, { HTML_UNDEF }, "poly", s7_poly },
    { { HTML_JAN05 }, { HTML_UNDEF }, "polygon", s7_poly },
    { { HTML_JAN05 }, { HTML_UNDEF }, "rect", s7_rect },
    { { HTML_JAN05 }, { HTML_UNDEF }, "rectangle", s7_rect } };

struct symbol_entry < html_version, e_shape_rendering > shape_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", sr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", sr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "crispEdges", sr_crispedges },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometricPrecision", sr_geometricprecision },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", sr_inherit } };

 struct symbol_entry < html_version, e_smei > smei_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "start", smei_start },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "middle", smei_middle },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "end", smei_end },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", smei_inherit } };

struct symbol_entry < html_version, e_ssi > ssi_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "comment", ssi_comment },
    { { HTML_UNDEF }, { HTML_UNDEF }, "config", ssi_config },
    { { HTML_UNDEF }, { HTML_UNDEF }, "echo", ssi_echo },
    { { HTML_UNDEF }, { HTML_UNDEF }, "elif", ssi_elif },
    { { HTML_UNDEF }, { HTML_UNDEF }, "else", ssi_else },
    { { HTML_UNDEF }, { HTML_UNDEF }, "endif", ssi_endif },
    { { HTML_UNDEF }, { HTML_UNDEF }, "exec", ssi_exec },
    { { HTML_UNDEF }, { HTML_UNDEF }, "fsize", ssi_fsize },
    { { HTML_UNDEF }, { HTML_UNDEF }, "flastmod", ssi_flastmod },
    { { HTML_UNDEF }, { HTML_UNDEF }, "if", ssi_if },
    { { HTML_UNDEF }, { HTML_UNDEF }, "include", ssi_include },
    { { HTML_UNDEF }, { HTML_UNDEF }, "printenv", ssi_printenv },
    { { HTML_UNDEF }, { HTML_UNDEF }, "set", ssi_set } };

struct symbol_entry < html_version, e_ssi_comparison > ssi_comparison_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "&&", ssi_comparison_and },
    { { HTML_UNDEF }, { HTML_UNDEF }, "=", ssi_comparison_eq },
    { { HTML_UNDEF }, { HTML_UNDEF }, "==", ssi_comparison_eq },
    { { HTML_UNDEF }, { HTML_UNDEF }, ">=", ssi_comparison_ge },
    { { HTML_UNDEF }, { HTML_UNDEF }, ">", ssi_comparison_gt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<=", ssi_comparison_le },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<", ssi_comparison_lt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "!=", ssi_comparison_ne },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<>", ssi_comparison_ne },
    { { HTML_UNDEF }, { HTML_UNDEF }, "||", ssi_comparison_or } };

struct symbol_entry < html_version, e_ssi_encoding > ssi_encoding_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "base64", ssi_encoding_base64 },
    { { HTML_UNDEF }, { HTML_UNDEF }, "entity", ssi_encoding_entity },
    { { HTML_UNDEF }, { HTML_UNDEF }, "none", ssi_encoding_none },
    { { HTML_UNDEF }, { HTML_UNDEF }, "url", ssi_encoding_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, "urlencoded", ssi_encoding_urlencoded } };

struct symbol_entry < html_version, e_ssi_env > ssi_env_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "date_gmt", ssi_DATE_GMT },
    { { HTML_UNDEF }, { HTML_UNDEF }, "date_local", ssi_DATE_LOCAL },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_args", ssi_DOCUMENT_ARGS },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_name", ssi_DOCUMENT_NAME },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_path_info", ssi_DOCUMENT_PATH_INFO },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_uri", ssi_DOCUMENT_URI },
    { { HTML_UNDEF }, { HTML_UNDEF }, "last_modified", ssi_LAST_MODIFIED },
    { { HTML_UNDEF }, { HTML_UNDEF }, "query_string_unescaped", ssi_QUERY_STRING_UNESCAPED },
    { { HTML_UNDEF }, { HTML_UNDEF }, "user_name", ssi_USER_NAME } };

struct symbol_entry < html_version, e_svg_align > svg_align_symbol_table [] =
{   { { HTML_SVG10 }, { HTML_UNDEF }, "none", sa_none },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMin", sa_xmin_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMin", sa_xmid_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMin", sa_xmax_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMid", sa_xmin_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMid", sa_xmid_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMid", sa_xmax_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMax", sa_xmin_ymax },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMax", sa_xmid_ymax },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMax", sa_xmax_ymax } };

struct symbol_entry < html_version, e_svg_display > svg_display_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inline",  ds_inline },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "block", ds_block },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "list-item", ds_listitem },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "run-in", ds_runin },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "compact", ds_compact },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "marker", ds_marker },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table", ds_table },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inline-table", ds_inlinetable },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-row-group", ds_tablerowgroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-header-group", ds_tableheadergroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-footer-group", ds_tablefootergroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-row", ds_tablerow },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-column-group", ds_tablecolumngroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-column", ds_tablecolumn },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-cell", ds_tablecell },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-caption", ds_tablecaption },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", ds_none },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inherit", ds_inherit } };

struct symbol_entry < html_version, e_svg_fontstretch > svg_fontstretch_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "all",  fst_all },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fst_normal },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "wider",  fst_wider },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "narrower",  fst_narrower },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "ultra-condensed", fst_ultracondensed },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "extra-condensed", fst_extracondensed },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "condensed", fst_condensed },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "semi-condensed", fst_semicondensed },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "semi-expanded", fst_semiexpanded },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "expanded", fst_expanded },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "extra-expanded", fst_extraexpanded },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "ultra-expanded", fst_ultraexpanded },
    { { HTML_4_0, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", fst_inherit } };

struct symbol_entry < html_version, e_svg_fontstretch_ff > svg_fontstretch_ff_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fff_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "ultra-condensed",  fff_ultracondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "extra-condensed", fff_extracondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "condensed", fff_condensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "semi-condensed", fff_semicondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "semi-expanded", fff_semiexpanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "expanded", fff_expanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "extra-expanded", fff_extraexpanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "ultra-expanded", fff_ultraexpanded } };

struct symbol_entry < html_version, e_svg_fontstyle > svg_fontstyle_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  sfs_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "italic",  sfs_italic },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "oblique",  sfs_oblique },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", sfs_inherit } };

struct symbol_entry < html_version, e_svg_fontweight > svg_fontweight_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fsw_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bold", fsw_bold },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bolder", fsw_bolder },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "lighter", fsw_lighter },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "100", fsw_100 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "200", fsw_200 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "300", fsw_300 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "400", fsw_400 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "500", fsw_500 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "600", fsw_600 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "700", fsw_700 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "800", fsw_800 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "900", fsw_900 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", fsw_inherit } };

struct symbol_entry < html_version, e_svg_fontweight_ff > svg_fontweight_ff_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fsf_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bold", fsf_bold },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "100", fsf_100 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "200", fsf_200 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "300", fsf_300 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "400", fsf_400 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "500", fsf_500 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "600", fsf_600 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "700", fsf_700 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "800", fsf_800 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "900", fsf_900 } };

struct symbol_entry < html_version, e_svg_mode > svg_mode_symbol_table [] =
{   { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "color", sm_colour },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "colour-burn", sm_colour_burn },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "colour-dodge", sm_colour_dodge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "darken", sm_darken },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "difference", sm_difference },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "exclusion", sm_exclusion },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "hard-light", sm_hard_light },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "hue", sm_hue },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "lighten", sm_lighten },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "luminosity", sm_luminosity },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "multiply", sm_multiply },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "normal", sm_normal },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "saturation", sm_saturation },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "screen", sm_screen },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "soft-light", sm_soft_light } };

struct symbol_entry < html_version, e_svg_overflow > svg_overflow_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "visible", sov_visible },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hidden", sov_hidden },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "scroll", sov_scroll },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "auto", sov_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "inherit", sov_inherit } };

struct symbol_entry < html_version, e_svg_type > svg_type_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "discrete", tsz_discrete },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "gamma", tsz_gamma },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "identity", tsz_identity },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "linear", tsz_linear },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "table", tsz_table } };

struct symbol_entry < html_version, e_svg_version > svg_version_symbol_table [] =
{   { { HTML_SVG10 }, { HTML_UNDEF }, "1.0", sv_1_0 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.1", sv_1_1 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2", sv_1_2_tiny },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2/tiny", sv_1_2_tiny },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2/full", sv_1_2_full },
    { { HTML_SVG10 }, { HTML_UNDEF }, "2.0", sv_2_0 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "2.1", sv_2_1 } };

struct symbol_entry < html_version, e_svg_version_grand > svg_version_grand_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, HTTP_W3 "/tr/rec-mathml-19980407", svg_1_0 }, // MathML ??
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "http:s//www.w3.org/tr/rec-mathml-19980407", svg_1_0 },
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, HTTP_W3 "/graphics/svg/svg-19990706.dtd", svg_1_1 },
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, HTTPS_W3 "/graphics/svg/svg-19990706.dtd", svg_1_1 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000, svg_2_0 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000, svg_2_0 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000 "/tiny", svg_1_2_tiny },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000 "/tiny", svg_1_2_tiny },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000 "/full", svg_1_2_full },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000 "/full", svg_1_2_full } };

struct symbol_entry < html_version, e_tableframe > tableframe_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "void", fr_void },
    { { HTML_2_0 }, { HTML_UNDEF }, "above", fr_above },
    { { HTML_2_0 }, { HTML_UNDEF }, "below", fr_below },
    { { HTML_2_0 }, { HTML_UNDEF }, "hsides", fr_hsides },
    { { HTML_2_0 }, { HTML_UNDEF }, "lhs", fr_lhs },
    { { HTML_2_0 }, { HTML_UNDEF }, "rhs", fr_rhs },
    { { HTML_2_0 }, { HTML_UNDEF }, "vsides", fr_vsides },
    { { HTML_2_0 }, { HTML_UNDEF }, "box", fr_box },
    { { HTML_2_0 }, { HTML_UNDEF }, "border", fr_border } };

struct symbol_entry < html_version, e_tblri > tblri_symbol_table [] =
{   { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "bottom", etb_bottom },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "inherit", etb_inherit },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "left", etb_left },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "right", etb_right },
    { { HTML_CSS, 0, 0 }, { HTML_UNDEF }, "top", etb_top } };

struct symbol_entry < html_version, e_text_decoration > text_decoration_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "none", td_none },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "underline", td_underline },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "overline", td_overline },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "line-through", td_linethrough },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "blink", td_blink },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "inherit", td_inherit } };

struct symbol_entry < html_version, e_text_rendering > text_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", tr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", tr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeLegibility", tr_optimiselegibility },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometricPrecision", tr_geometricprecision },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", tr_inherit } };

struct symbol_entry < html_version, e_transform_anim > transform_anim_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "translate", ta_translate },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "scale", ta_scale },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "rotate", ta_rotate },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "skewX", ta_skewx },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "skewY", ta_skewy } };

struct symbol_entry < html_version, e_transformbehaviour > transformbehaviour_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometric", tb_geometric },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned", tb_pinned },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned90", tb_pinned90 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned180", tb_pinned180 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned170", tb_pinned270 } };

struct symbol_entry < html_version, e_transform_fn > transform_fn_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (6) | HE_MAXARGS (6) }, { HTML_UNDEF }, "matrix", tr_matrix },
    { { HTML_SVG12, 0, HE_SVG_12 | HE_MINARGS (1) | HE_MAXARGS (3) }, { HTML_UNDEF }, "ref", tr_ref },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (2) }, { HTML_UNDEF }, "translate", tr_translate },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "translateX", tr_translatex },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "translateY", tr_translatey },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (2) }, { HTML_UNDEF }, "scale", tr_scale },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "scaleX", tr_scalex },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "scaleY", tr_scaley },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (3) }, { HTML_UNDEF }, "rotate", tr_rotate },
    { { HTML_SVG20, HV_DEPRECATED45, HE_SVG_2 | HE_MINARGS (2) | HE_MAXARGS (4) }, { HTML_UNDEF }, "skew", tr_skew },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "skewX", tr_skewx },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "skewY", tr_skewy } };

struct symbol_entry < html_version, e_turbulence_type > turbulence_type_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "fractalNoise", tu_fractal_noise },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "turbulence", tu_turbulence } };

struct symbol_entry < html_version, e_unicode_bidi > unicode_bidi_symbol_table [] =
 {  { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "bidi-override", ub_bidioverride },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "embed", ub_embed },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "inherit", ub_inherit },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "isolate", ub_isolate },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, "normal", ub_normal },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "plaintext", ub_plaintext } };

struct symbol_entry < html_version, e_unit > unit_symbol_table [] =
{   { { HTML_JAN21 }, { HTML_UNDEF }, "cap", eu_cap },
    { { HTML_JUN19 }, { HTML_UNDEF }, "ch", eu_ch },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "cm", eu_cm },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "em", eu_em },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "ex", eu_ex },
    { { HTML_JAN21 }, { HTML_UNDEF }, "ic", eu_ic },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "in", eu_in },
    { { HTML_JAN21 }, { HTML_UNDEF }, "lh", eu_lh },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "mm", eu_mm },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "pc", eu_pc },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "pt", eu_pt },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "px", eu_px },
    { { HTML_JUN19 }, { HTML_UNDEF }, "Q", eu_q },
    { { HTML_JUN19 }, { HTML_UNDEF }, "rem", eu_rem },
    { { HTML_JAN21 }, { HTML_UNDEF }, "rlh", eu_rlh },
    { { HTML_JAN21 }, { HTML_UNDEF }, "vb", eu_vb },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vh", eu_vh },
    { { HTML_JAN21 }, { HTML_UNDEF }, "vi", eu_vi },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vmin", eu_vmin },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vmax", eu_vmax },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vw", eu_vw } };

struct symbol_entry < html_version, e_vector_effect_2 > vector_effect_2_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "fixed-position", v2_fixedposition },
    { { HTML_SVG20 }, { HTML_UNDEF }, "none", v2_none },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-rotation", v2_nonrotation },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-scaling-stroke", v2_nonscalingstroke },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-scaling-size", v2_nonscalingsize } };

struct symbol_entry < html_version, e_vertical_align_enum > vertical_align_enum_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "baseline", eva_baseline },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "sub", eva_sub },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "super", eva_super },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "text-top", eva_text_top },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "middle", eva_middle },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "bottom", eva_bottom },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "text-bottom", eva_text_bottom },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "inherit", eva_inherit } };

struct symbol_entry < html_version, e_vgender > vgender_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "female", vg_female },
    { { HTML_VCARD }, { HTML_UNDEF }, "male", vg_male },
    { { HTML_VCARD }, { HTML_UNDEF }, "none", vg_none },
    { { HTML_VCARD }, { HTML_UNDEF }, "other", vg_other },
    { { HTML_VCARD }, { HTML_UNDEF }, "unknown", vg_unknown } };

struct symbol_entry < html_version, e_vrel > vrel_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "acquaintance", vr_acquaintance },
    { { HTML_VCARD }, { HTML_UNDEF }, "agent", vr_agent },
    { { HTML_VCARD }, { HTML_UNDEF }, "child", vr_child },
    { { HTML_VCARD }, { HTML_UNDEF }, "colleague", vr_colleague },
    { { HTML_VCARD }, { HTML_UNDEF }, "contact", vr_contact },
    { { HTML_VCARD }, { HTML_UNDEF }, "coresident", vr_coresident },
    { { HTML_VCARD }, { HTML_UNDEF }, "coworker", vr_coworker },
    { { HTML_VCARD }, { HTML_UNDEF }, "crush", vr_crush },
    { { HTML_VCARD }, { HTML_UNDEF }, "date", vr_date },
    { { HTML_VCARD }, { HTML_UNDEF }, "emergency", vr_emergency },
    { { HTML_VCARD }, { HTML_UNDEF }, "friend", vr_friend },
    { { HTML_VCARD }, { HTML_UNDEF }, "kin", vr_kin },
    { { HTML_VCARD }, { HTML_UNDEF }, "me", vr_me },
    { { HTML_VCARD }, { HTML_UNDEF }, "met", vr_met },
    { { HTML_VCARD }, { HTML_UNDEF }, "muse", vr_muse },
    { { HTML_VCARD }, { HTML_UNDEF }, "neighbor", vr_neighbor },
    { { HTML_VCARD }, { HTML_UNDEF }, "parent", vr_parent },
    { { HTML_VCARD }, { HTML_UNDEF }, "sibling", vr_sibling },
    { { HTML_VCARD }, { HTML_UNDEF }, "spouse", vr_spouse },
    { { HTML_VCARD }, { HTML_UNDEF }, "sweetheart", vr_sweetheart } };

struct symbol_entry < html_version, e_vtt > vtt_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "cell", vt_mobile },
    { { HTML_VCARD }, { HTML_UNDEF }, "mobile", vt_mobile },
    { { HTML_VCARD }, { HTML_UNDEF }, "fax", vt_fax },
    { { HTML_VCARD }, { HTML_UNDEF }, "pager", vt_pager },
    { { HTML_VCARD }, { HTML_UNDEF }, "text", vt_sms },
    { { HTML_VCARD }, { HTML_UNDEF }, "sms", vt_sms },
    { { HTML_VCARD }, { HTML_UNDEF }, "textphone", vt_textphone },
    { { HTML_VCARD }, { HTML_UNDEF }, "video", vt_video },
    { { HTML_VCARD }, { HTML_UNDEF }, "voice", vt_voice } };

struct symbol_entry < html_version, e_whitespace > whitespace_symbol_table [] =
{   { { HTML_JAN19 }, { HTML_UNDEF }, "normal", ws_normal },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre", ws_pre },
    { { HTML_JAN19 }, { HTML_UNDEF }, "nowrap", ws_nowrap },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre-wrap", ws_pre_wrap },
    { { HTML_JAN19 }, { HTML_UNDEF }, "break-spaces", ws_break_spaces },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre-line", ws_pre_line } };

struct symbol_entry < html_version, e_writingmode > writingmode_symbol_table [] =
{   { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "horizontal-tb", wm_htb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "lr-tb", wm_lrtb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "rl-tb", wm_rltb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "tb-rl", wm_tbrl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "lr", wm_lr },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "rl", wm_rl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "tb", wm_tb },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "vertical-lr", wm_vlr },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "vertical-rl", wm_vrl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "inherit", wm_inherit } };

struct symbol_entry < html_version, e_xmlns > xmlns_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, HTTP PURL_ORG "g/ontology/bibo/", x_bibo },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "g/ontology/bibo/", x_bibo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xhtml", x_xhtml_1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xhtml", x_xhtml_1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/strict", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/strict", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/transitional", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/transitional", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/frameset", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/frameset", x_xhtml_1_superseded },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2000/xhtml", x_xhtml_11 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2000/xhtml", x_xhtml_11 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTP_W3 "/2004/xhtml", x_xhtml_2 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTPS_W3 "/2004/xhtml", x_xhtml_2 },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP CC "/ns#", x_cc },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS CC "/ns#", x_cc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP OGC "/crs", x_crs },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS OGC "/crs", x_crs },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/property/", x_dbp },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/property/", x_dbp },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/ontology/", x_dbp_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/ontology/", x_dbp_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/resource/", x_dbr },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/resource/", x_dbr },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/dc/terms/", x_dc_terms },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/dc/terms/", x_dc_terms },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DEFAULT_DOMAIN "/", x_ex },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DEFAULT_DOMAIN "/", x_ex },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP XCOM "/foaf/0.1/", x_foaf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS XCOM "/foaf/0.1/", x_foaf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1998/math/mathml", x_mathml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1998/math/mathml", x_mathml },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2002/07/owl/#", x_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2002/07/owl/#", x_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "www.rddl.org/", x_rddl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "www.rddl.org/", x_rddl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/02/22-rdf-syntax-ns#", x_rdf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/02/22-rdf-syntax-ns#", x_rdf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/ns/rdfa#", x_rdfa },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/ns/rdfa#", x_rdfa },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2000/01/rdf-schema#", x_rdfs },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2000/01/rdf-schema#", x_rdfs },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP SVG_2000, x_svg },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS SVG_2000, x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/tr/rec-mathml-19980407", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/tr/rec-mathml-19980407", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/graphics/svg/svg-19990706.dtd", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/graphics/svg/svg-19990706.dtd", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/vcard-rdf/3.0#", x_vcard1 },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/vcard-rdf/3.0#", x_vcard1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "rdf.data-vocabulary.org/#", x_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "rdf.data-vocabulary.org/#", x_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2006/vcard/ns#", x_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2006/vcard/ns#", x_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xhtml/vocab#", x_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xhtml/vocab#", x_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xlink", x_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xlink", x_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/XML/1998/namespace", x_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/XML/1998/namespace", x_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2000/xmlns/", x_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2000/xmlns/", x_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema#", x_xsd },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema#", x_xsd },

    // many examples, including the living standard
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/html", x_html },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/html", x_html },

    // https://www.informit.com/articles/article.aspx?p=31837&seqNum=10
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XInclude", x_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XInclude", x_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/XSL/Transform/1.0", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/XSL/Transform/1.0", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/WD-xsl", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/WD-xsl", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "icl.com/saxon", x_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "icl.com/saxon", x_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "xml.apache.org/xslt", x_lxslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "xml.apache.org/xslt", x_lxslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "common", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "common", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "functions", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "functions", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "math", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "math", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "sets", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "sets", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema-datatypes", x_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema-datatypes", x_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/08/xquery-operators", x_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/08/xquery-operators", x_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/SMIL20", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/SMIL20", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/REC-smil", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/REC-smil", x_smil },

    // https://metacpan.org/pod/XML::CommonNS
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTP_W3 "/2006/06/xhtml", x_xhtml_2 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTPS_W3 "/2006/06/xhtml", x_xhtml_2 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/xml-events", x_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/xml-events", x_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/dc/elements/1.1/", x_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/dc/elements/1.1/", x_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/vocab/relationship/", x_rel },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/vocab/relationship/", x_rel },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/rss/1.0/", x_rss },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/rss/1.0/", x_rss },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/net/rssmodules/blogcomments/", x_comments },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/net/rssmodules/blogcomments/", x_comments },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/rss/1.0/modules/syndication/", x_syn },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/rss/1.0/modules/syndication/", x_syn },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "relaxng.org/ns/structure/1.0/", x_rng },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "relaxng.org/ns/structure/1.0/", x_rng },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema", x_xsd },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema", x_xsd },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema-instance", x_xsi },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema-instance", x_xsi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/XSL/Transform", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/XSL/Transform", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/XSL/Format", x_xslfo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/XSL/Format", x_xslfo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/soap/encoding/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/soap/encoding/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/soap/envelope/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/soap/envelope/", x_soapenc11 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2003/05/soap-encoding", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2003/05/soap-encoding", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2003/05/soap-envelope", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2003/05/soap-envelope", x_soapenc12 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/wsdl/", x_wsdl11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/wsdl/", x_wsdl11 } };

#define INIT_ENUM(XX) \
    type_master < t_##XX > :: init (nits, XX##_symbol_table, sizeof (XX##_symbol_table) / sizeof (symbol_entry < html_version, e_##XX >)); \
    context.validation ().add_options () (VALIDATION #XX, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid '" #XX "'.")

void init_1 ()
{   type_master < t_bb > :: init ();
    type_master < t_blocking > :: init ();
    type_master < t_cc_prohibits > :: init ();
    type_master < t_css_azimuth_be > :: init ();
    type_master < t_css_earnest > :: init ();
    type_master < t_html_boolean > :: init ();
    type_master < t_keygentype > :: init ();
    type_master < t_svg_content > :: init ();
    type_master < t_svg_phase > :: init ();
    type_master < t_xmllink > :: init (); }

void init_2 ()
{   type_master < t_10 > :: init ();
    type_master < t_accumulate > :: init ();
    type_master < t_additive > :: init ();
    type_master < t_bool > :: init ();
    type_master < t_capture > :: init ();
    type_master < t_compositing > :: init ();
    type_master < t_connect > :: init ();
    type_master < t_coordinatesystem > :: init ();
    type_master < t_cors > :: init ();
    type_master < t_css_mark > :: init ();
    type_master < t_dataformatas > :: init ();
    type_master < t_defaultaction > :: init ();
    type_master < t_editable > :: init ();
    type_master < t_fill_ve > :: init ();
    type_master < t_fillanim > :: init ();
    type_master < t_focushighlight > :: init ();
    type_master < t_gender > :: init ();
    type_master < t_hidden > :: init ();
    type_master < t_hv > :: init ();
    type_master < t_initialvisibility > :: init ();
    type_master < t_js_version > :: init ();
    type_master < t_layout > :: init ();
    type_master < t_lengthadjust > :: init ();
    type_master < t_loading > :: init ();
    type_master < t_lralign > :: init ();
    type_master < t_markerunits > :: init ();
    type_master < t_mathdisplay > :: init ();
    type_master < t_mathfontstyle > :: init ();
    type_master < t_mathfontweight > :: init ();
    type_master < t_mathmode > :: init ();
    type_master < t_mathorder > :: init ();
    type_master < t_mathscope > :: init ();
    type_master < t_meetslice > :: init ();
    type_master < t_morphology_operator > :: init ();
    type_master < t_notations > :: init ();
    type_master < t_onoff > :: init ();
    type_master < t_orientation > :: init ();
    type_master < t_overlay > :: init ();
    type_master < t_propagate > :: init ();
    type_master < t_settype > :: init ();
    type_master < t_spacing > :: init ();
    type_master < t_ssi_f > :: init ();
    type_master < t_ssi_sizefmt > :: init ();
    type_master < t_startend > :: init ();
    type_master < t_stitchtiles > :: init ();
    type_master < t_streamedcontents > :: init ();
    type_master < t_ltr_rtl > :: init ();
    type_master < t_svg_fontvariant_ff > :: init ();
    type_master < t_svg_method > :: init ();
    type_master < t_svg_playbackorder > :: init ();
    type_master < t_svg_side > :: init ();
    type_master < t_svg_timelinebegin > :: init ();
    type_master < t_svg_units > :: init ();
    type_master < t_tbalign > :: init ();
    type_master < t_tfn > :: init ();
    type_master < t_transp > :: init ();
    type_master < t_truefalseempty > :: init ();
    type_master < t_viewportscreen > :: init ();
    type_master < t_vtype > :: init ();
    type_master < t_workertype > :: init ();
    type_master < t_wrap > :: init ();
    type_master < t_wrap3 > :: init ();
    type_master < t_xlinkshow_a > :: init ();
    type_master < t_xmlspace > :: init ();
    type_master < t_xorder > :: init ();
    type_master < t_yesno > :: init ();
    type_master < t_yesnoempty > :: init ();
    type_master < t_zoompan > :: init (); }

void init_3 ()
{   type_master < t_aria_live > :: init ();
    type_master < t_attributetype > :: init ();
    type_master < t_behaviour > :: init ();
    type_master < t_button > :: init ();
    type_master < t_cc_permits > :: init ();
    type_master < t_command > :: init ();
    type_master < t_controlslist > :: init ();
    type_master < t_corp > :: init ();
    type_master < t_css_aai > :: init ();
    type_master < t_css_azimuth_lri > :: init ();
    type_master < t_css_border_collapse > :: init ();
    type_master < t_css_empty_cells > :: init ();
    type_master < t_css_speak_header > :: init ();
    type_master < t_css_speak_numeral > :: init ();
    type_master < t_css_speak_punctuation > :: init ();
    type_master < t_css_table_layout > :: init ();
    type_master < t_csvw_direction > :: init ();
    type_master < t_decoding > :: init ();
    type_master < t_dsc > :: init ();
    type_master < t_edgemode > :: init ();
    type_master < t_edi > :: init ();
    type_master < t_enctype > :: init ();
    type_master < t_fill_rule > :: init ();
    type_master < t_font_variant_position > :: init ();
    type_master < t_fontnia > :: init ();
    type_master < t_importance > :: init ();
    type_master < t_infixlinebreakstyle > :: init ();
    type_master < t_keytype > :: init ();
    type_master < t_lcralign > :: init ();
    type_master < t_lraalign > :: init ();
    type_master < t_lrnalign > :: init ();
    type_master < t_mathform > :: init ();
    type_master < t_mathframe > :: init ();
    type_master < t_mathoccurence > :: init ();
    type_master < t_menuitem > :: init ();
    type_master < t_menutype > :: init ();
    type_master < t_mf_class > :: init ();
    type_master < t_mf_status > :: init ();
    type_master < t_nsd > :: init ();
    type_master < t_nuf > :: init ();
    type_master < t_preload5 > :: init ();
    type_master < t_restart > :: init ();
    type_master < t_scrolling > :: init ();
    type_master < t_shape_rcp > :: init ();
    type_master < t_spacer > :: init ();
    type_master < t_spreadmethod > :: init ();
    type_master < t_ssi_echo > :: init ();
    type_master < t_ssi_include > :: init ();
    type_master < t_svg_direction > :: init ();
    type_master < t_svg_fontvariant > :: init ();
    type_master < t_tendstotype > :: init ();
    type_master < t_tfa > :: init ();
    type_master < t_tfi > :: init ();
    type_master < t_tfu > :: init ();
    type_master < t_units > :: init ();
    type_master < t_valign_tmb > :: init ();
    type_master < t_valuetype > :: init ();
    type_master < t_vector_effect_12 > :: init ();
    type_master < t_visibility10 > :: init (); }

void init_4 ()
{   type_master < t_actiontype2 > :: init ();
    type_master < t_align2070 > :: init ();
    type_master < t_aligndec > :: init ();
    type_master < t_alignfig > :: init ();
    type_master < t_arabicenum > :: init ();
    type_master < t_aria_autocomplete > :: init ();
    type_master < t_aria_invalidity > :: init ();
    type_master < t_aria_sort > :: init ();
    type_master < t_buffered_rendering > :: init ();
    type_master < t_calcmode > :: init ();
    type_master < t_captionalign > :: init ();
    type_master < t_cc_requires > :: init ();
    type_master < t_channelselector > :: init ();
    type_master < t_content_encoding > :: init ();
    type_master < t_css_font_style_e > :: init ();
    type_master < t_css_orientation > :: init ();
    type_master < t_css_speak > :: init ();
    type_master < t_device > :: init ();
    type_master < t_edit > :: init ();
    type_master < t_effect > :: init ();
    type_master < t_frame4 > :: init ();
    type_master < t_intent_hint > :: init ();
    type_master < t_larnalign > :: init ();
    type_master < t_lcrd > :: init ();
    type_master < t_lcrnalign > :: init ();
    type_master < t_linebreakstyle > :: init ();
    type_master < t_linecap > :: init ();
    type_master < t_linejoin > :: init ();
    type_master < t_lrnialign > :: init ();
    type_master < t_mathclosure > :: init ();
    type_master < t_mathside > :: init ();
    type_master < t_mf_availability > :: init ();
    type_master < t_mf_category > :: init ();
    type_master < t_paint_order > :: init ();
    type_master < t_phase_x > :: init ();
    type_master < t_rsvp > :: init ();
    type_master < t_shadowinherit > :: init ();
    type_master < t_shape4 > :: init ();
    type_master < t_size3 > :: init ();
    type_master < t_ssi_config > :: init ();
    type_master < t_ssi_set > :: init ();
    type_master < t_svg_baseprofile > :: init ();
    type_master < t_syncbehaviour > :: init ();
    type_master < t_syncbehaviourdefault > :: init ();
    type_master < t_tdscope > :: init ();
    type_master < t_tfmu > :: init ();
    type_master < t_uplr > :: init ();
    type_master < t_valign3 > :: init ();
    type_master < t_visibility11 > :: init ();
    type_master < t_vkind > :: init ();
    type_master < t_xsdbool > :: init (); };

void enum_init (nitpick& nits)
{   init_1 ();
    init_2 ();
    init_3 ();
    init_4 ();
    INIT_ENUM (accrual_method);
    INIT_ENUM (accrual_periodicity);
    INIT_ENUM (accrual_policy);
    INIT_ENUM (action);
    INIT_ENUM (align3);
    INIT_ENUM (alignment_baseline);
    INIT_ENUM (alignplus);
    INIT_ENUM (as);
    INIT_ENUM (as_units);
    INIT_ENUM (autocapitalise);
    INIT_ENUM (autocomplete);
    INIT_ENUM (baselineshift);
    INIT_ENUM (cachekey);
    INIT_ENUM (citype);
    INIT_ENUM (colour_interpolation);
    INIT_ENUM (colour_rendering);
    INIT_ENUM (cookieid);
    INIT_ENUM (cntype);
    INIT_ENUM (comp_op);
    INIT_ENUM (composite_operator);
    INIT_ENUM (css_aaalri);
    INIT_ENUM (css_absolute_size);
    INIT_ENUM (css_absolute_size);
    INIT_ENUM (css_azimuth_e);
    INIT_ENUM (css_background_attachment);
    INIT_ENUM (css_background_repeat);
    INIT_ENUM (css_border_style);
    INIT_ENUM (css_border_width);
    INIT_ENUM (css_clear);
    INIT_ENUM (css_colour);
    INIT_ENUM (css_content_enum);
    INIT_ENUM (css_cursor_e);
    INIT_ENUM (css_display);
    INIT_ENUM (css_elevation_e);
    INIT_ENUM (css_font_weight);
    INIT_ENUM (css_fn);
    INIT_ENUM (css_generic_family);
    INIT_ENUM (css_list_style_position);
    INIT_ENUM (css_list_style_type);
    INIT_ENUM (css_overflow);
    INIT_ENUM (css_pitch_e);
    INIT_ENUM (css_position);
    INIT_ENUM (css_property);
    INIT_ENUM (css_relative_size);
    INIT_ENUM (css_statement);
    INIT_ENUM (css_speech_rate_e);
    INIT_ENUM (css_text_align);
    INIT_ENUM (css_text_decoration);
    INIT_ENUM (css_text_transform);
    INIT_ENUM (css_vertical_align);
    INIT_ENUM (css_volume_e);
    INIT_ENUM (css_whitespace);
    INIT_ENUM (crossout);
    INIT_ENUM (cursor);
    INIT_ENUM (decalign);
    INIT_ENUM (determiner);
    INIT_ENUM (dingbat);
    INIT_ENUM (dir);
    INIT_ENUM (display_align);
    INIT_ENUM (dominantbaseline);
    INIT_ENUM (enterkeyhint);
    INIT_ENUM (figalign);
    INIT_ENUM (filter_in);
    INIT_ENUM (fixedcolour);
    INIT_ENUM (fontname);
    INIT_ENUM (font_enum);
    INIT_ENUM (font_variant_2);
    INIT_ENUM (font_variant_caps);
    INIT_ENUM (font_variant_east_asian);
    INIT_ENUM (font_variant_ligature);
    INIT_ENUM (font_variant_numeric);
    INIT_ENUM (formaturi);
    INIT_ENUM (halign);
    INIT_ENUM (icalfreq);
    INIT_ENUM (image_rendering);
    INIT_ENUM (icc);
    INIT_ENUM (indentalign);
    INIT_ENUM (inky);
    INIT_ENUM (inputmode);
    INIT_ENUM (inputplus);
    INIT_ENUM (inputtype);
    INIT_ENUM (inputtype3);
    INIT_ENUM (inputtype32);
    INIT_ENUM (inputtype4);
    INIT_ENUM (inputtype5);
    INIT_ENUM (jtoken);
    INIT_ENUM (kind);
    INIT_ENUM (length_absolute);
    INIT_ENUM (length_relative);
    INIT_ENUM (linebreak);
    INIT_ENUM (linkparam);
    INIT_ENUM (listtype);
    INIT_ENUM (longdivstyle);
    INIT_ENUM (mah);
    INIT_ENUM (mathalign);
    INIT_ENUM (mathlocation);
    INIT_ENUM (mathnotation);
    INIT_ENUM (mathoverflow);
    INIT_ENUM (mathvariant);
    INIT_ENUM (matrixtype);
    INIT_ENUM (media);
    INIT_ENUM (mediafeature);
    INIT_ENUM (mediakeyword);
    INIT_ENUM (method);
    INIT_ENUM (mf_identifier);
    INIT_ENUM (mf_itemtype);
    INIT_ENUM (mf_listing_action);
    INIT_ENUM (mf_method);
    INIT_ENUM (mf_reviewtype);
    INIT_ENUM (myersbriggs);
    INIT_ENUM (namedspace);
    INIT_ENUM (namespace);
    INIT_ENUM (nit_macro);
    INIT_ENUM (nit_section);
    INIT_ENUM (ogtype);
    INIT_ENUM (page_orientation);
    INIT_ENUM (paintkeyword);
    INIT_ENUM (plusstyle);
    INIT_ENUM (pointer_events);
    INIT_ENUM (print);
    INIT_ENUM (quote_style);
    INIT_ENUM (referrer);
    INIT_ENUM (rendering_in_tents);
    INIT_ENUM (rules);
    INIT_ENUM (sandbox);
    INIT_ENUM (scei);
    INIT_ENUM (severity);
    INIT_ENUM (shadow);
    INIT_ENUM (shape7);
    INIT_ENUM (shape_rendering);
    INIT_ENUM (smei);
    INIT_ENUM (ssi);
    INIT_ENUM (ssi_comparison);
    INIT_ENUM (ssi_encoding);
    INIT_ENUM (ssi_env);
    INIT_ENUM (svg_align);
    INIT_ENUM (svg_display);
    INIT_ENUM (svg_fontstretch);
    INIT_ENUM (svg_fontstretch_ff);
    INIT_ENUM (svg_fontstyle);
    INIT_ENUM (svg_fontweight);
    INIT_ENUM (svg_fontweight_ff);
    INIT_ENUM (svg_mode);
    INIT_ENUM (svg_overflow);
    INIT_ENUM (svg_type);
    INIT_ENUM (svg_version);
    INIT_ENUM (svg_version_grand);
    INIT_ENUM (tableframe);
    INIT_ENUM (tblri);
    INIT_ENUM (text_decoration);
    INIT_ENUM (text_rendering);
    INIT_ENUM (transform_anim);
    INIT_ENUM (transformbehaviour);
    INIT_ENUM (transform_fn);
    INIT_ENUM (turbulence_type);
    INIT_ENUM (unit);
    INIT_ENUM (unicode_bidi);
    INIT_ENUM (vector_effect_2);
    INIT_ENUM (vertical_align_enum);
    INIT_ENUM (vgender);
    INIT_ENUM (vrel);
    INIT_ENUM (vtt);
    INIT_ENUM (whitespace);
    INIT_ENUM (writingmode);
    INIT_ENUM (xmlns); }
