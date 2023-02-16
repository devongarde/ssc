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
#include "element/elem.h"
#include "main/context.h"
#include "utility/quote.h"
#include "type/type.h"

struct symbol_entry < html_version, e_element > elem_symbol_table [] =
{   { { HTML_PLUS }, { HTML_UNDEF }, "!doctype", elem_faux_doctype, ns_default, EP_CLOSED | EP_TOP },
    { { HTML_TAGS }, { HTML_UNDEF }, "(*ERROR*)", elem_error, ns_default, EP_CLOSED | EP_IGNORE },
    { { HTML_2_0 }, { HTML_UNDEF }, "(asp)", elem_faux_asp, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "(CDATA)", elem_faux_cdata, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "&...;", elem_faux_char, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "&#...;", elem_faux_code, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "(comment)", elem_faux_comment, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_TAGS }, { HTML_UNDEF }, "(document)", elem_faux_document, ns_default, EP_HOLDS_ALL, EF_FAUX | EF_DOCUMENT },
    { { HTML_2_0 }, { HTML_UNDEF }, "(php)", elem_faux_php, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_2_0 }, { HTML_UNDEF }, "(ssi)", elem_faux_ssi, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_3_0 }, { HTML_UNDEF }, "(stylesheet)", elem_faux_stylesheet, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX },
    { { HTML_TAGS }, { HTML_UNDEF }, "(text)", elem_faux_text, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "(undefined)", elem_undefined, ns_default, EP_CLOSED | EP_IGNORE },
    { { HTML_TAGS }, { HTML_UNDEF }, "(whitespace)", elem_faux_whitespace, ns_default, EP_CLOSED | EP_IGNORE, EF_FAUX | EF_5_FLOW | EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, "(xml)", elem_faux_xml, ns_default, EP_CLOSED | EP_IGNORE | EP_TOP, EF_FAUX },
    { { HTML_TAGS }, { HTML_UNDEF }, "(custom)", elem_custom, ns_default, EP_5_TRANSPARENT, EF_CUSTOM },

    { { HTML_CSS }, { HTML_UNDEF }, "*", elem_css_all, ns_default, EP_IGNORE, EF_FAUX | EF_CSS },
    { { HTML_CSS }, { HTML_UNDEF }, "||", elem_css_cell, ns_default, EP_IGNORE, EF_FAUX | EF_CSS },
    { { HTML_CSS }, { HTML_UNDEF }, ">", elem_css_child, ns_default, EP_IGNORE, EF_FAUX | EF_CSS },
    { { HTML_CSS }, { HTML_UNDEF }, "~", elem_css_precede, ns_default, EP_IGNORE, EF_FAUX | EF_CSS },
    { { HTML_CSS }, { HTML_UNDEF }, "+", elem_css_precede_immediate, ns_default, EP_IGNORE, EF_FAUX | EF_CSS },

    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_1", elem_rdf_1, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_2", elem_rdf_2, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_3", elem_rdf_3, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_4", elem_rdf_4, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_5", elem_rdf_5, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_6", elem_rdf_6, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_7", elem_rdf_7, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_8", elem_rdf_8, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "_9", elem_rdf_9, ns_rdf, 0, EF_RDF },
    { { HTML_TAGS, 0, HE_ANIM_10_11_2 }, { HTML_UNDEF }, "a", elem_a, ns_default, EP_LAZY | EP_5_TRANSPARENT, EF_TEXT | EF_PRE | EF_SPECIAL | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_S_G | EF_SVG_CONTAIN },
    { { HTML_4_0 }, { HTML_UNDEF }, "abbr", elem_abbr, ns_default, EP_SIMPLE, EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "abbrev", elem_abbrev, ns_default, 0, EF_EMPH | EF_3_MISC },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "about", elem_rdf_about, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF_DEP }, { HTML_UNDEF }, "aboutEach", elem_rdf_abouteach, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF_DEP }, { HTML_UNDEF }, "aboutEachPrefix", elem_rdf_abouteachprefix, ns_rdf, 0, EF_RDF },
    { { HTML_3_0 }, { HTML_3_0 }, "above", elem_above, ns_default, 0, EF_MATH },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "abs", elem_abs, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, "abstract", elem_abstract, ns_default, 0, EF_BLOK },
    { { XHTML_2_0 }, { XHTML_2_0 }, "access", elem_access, ns_default, EP_CLOSED, EF_METADATA },
    { { HTML_PLUS, HV_NOT2 }, { XHTML_1_1 }, "acronym", elem_acronym, ns_default, 0, EF_EMPH | EF_3_MISC | EF_4_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, "action", elem_action, ns_default, 0, EF_X2_STRUCT },
    { { HTML_PLUS }, { HTML_PLUS }, "added", elem_added, ns_default, 0, EF_EMPH },
    { { XHTML_2_0 }, { XHTML_2_0 }, "addeventlistener", elem_addeventlistener, ns_default, EP_CLOSED },
    { { HTML_TAGS }, { HTML_UNDEF }, "address", elem_address, ns_default, 0, EF_BODY | EF_3_BODY | EF_4_BLOCK | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "Alt", elem_rdf_alt, ns_rdf, 0, EF_RDF },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "altGlyph", elem_altglyph, ns_default, EP_SET_XLINKCAT (se_glyph_alt), EF_SVG_TEXT },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "altGlyphDef", elem_altglyphdef },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "altGlyphItem", elem_altglyphitem },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "and", elem_and, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "animate", elem_animate, ns_default, EP_SET_XLINKCAT (se_animation), EF_SVG_ANIM },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "animateColor", elem_animatecolour, ns_default, EP_SET_XLINKCAT (se_animation), EF_SVG_ANIM },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "animateMotion", elem_animatemotion, ns_default, EP_SET_XLINKCAT (se_animation), EF_SVG_ANIM },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "animateTransform", elem_animatetransform, ns_default, EP_SET_XLINKCAT (se_animation), EF_SVG_ANIM },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "animation", elem_animation },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "annotation", elem_annotation, ns_default, 0, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "annotation-xml", elem_annotation_xml, ns_default, 0, EF_M_CONTENT },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, "applet", elem_applet, ns_default, 0, EF_SPECIAL | EF_4_SPECIAL },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "apply", elem_apply, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "approx", elem_approx, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "arccos", elem_arccos, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arccosh", elem_arccosh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arccot", elem_arccot, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arccoth", elem_arccoth, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arccsc", elem_arccsc, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arccsch", elem_arccsch, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arcsec", elem_arcsec, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arcsech", elem_arcsech, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "arcsin", elem_arcsin, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arcsinh", elem_arcsinh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "arctan", elem_arctan, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arctanh", elem_arctanh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_2_0, HV_RFC_1980 | HV_NOT30 }, { HTML_UNDEF }, "area", elem_area, ns_default, EP_CLOSED, EF_5_FLOW | EF_5_PHRASE },
    { { HTML_PLUS, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "arg", elem_arg, ns_default, EP_CLOSED | EP_ARGS_1, EF_EMPH | EF_M_CONTENT },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "array", elem_array, ns_default, 0, EF_MATH },
    { { HTML_JAN05 }, { HTML_UNDEF }, "article", elem_article, ns_default, 0, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_JUL05 }, { HTML_UNDEF }, "aside", elem_aside, ns_default, EP_SIMPLE, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_3_0 }, { HTML_3_0 }, "atop", elem_atop, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { HTML_3_0 }, "au", elem_au, ns_default, 0, EF_3_MISC },
    { { HTML_SVG12 }, { HTML_UNDEF }, "audio", elem_audio, ns_default, EP_5_TRANSPARENT, EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_SVG2_GRAPH },
    { { HTML_1_0 }, { HTML_UNDEF }, "b", elem_b, ns_default, 0, EF_EMPH | EF_FONT | EF_3_TEXT | EF_3_MATHVC | EF_32_FONT | EF_4_FONT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "Bag", elem_rdf_bag, ns_rdf, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF_DEP }, { HTML_UNDEF }, "bagID", elem_rdf_bagid, ns_rdf, 0, EF_RDF },
    { { HTML_3_0 }, { HTML_3_0 }, "banner", elem_banner },
    { { HTML_3_0 }, { HTML_3_0 }, "bar", elem_bar, ns_default, 0, EF_3_MATHVC },
    { { HTML_TAGS, HV_NOTXX }, { HTML_UNDEF }, "base", elem_base, ns_default, EP_CLOSED, EF_METADATA },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_1_1 }, "basefont", elem_basefont, ns_default, EP_CLOSED, EF_SPECIAL | EF_4_SPECIAL },
    { { HTML_JUL08 }, { HTML_DEC09 }, "bb", elem_bb, ns_default, 0, EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_FLOW },
    { { HTML_JAN11 }, { HTML_UNDEF }, "bdi", elem_bdi, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_2_0, HV_RFC_2070 }, { HTML_UNDEF }, "bdo", elem_bdo, ns_default, 0, EF_PRE | EF_TEXT | EF_4_SPECIAL | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_3_0 }, { HTML_3_0 }, "below", elem_below, ns_default, 0, EF_MATH },
    { { HTML_2_0, 0, HE_IE }, { HTML_4_01 }, "bgsound", elem_bgsound, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { XHTML_1_1 }, "big", elem_big, ns_default, 0, EF_3_FONT | EF_32_FONT | EF_4_FONT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "bind", elem_bind, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_4_01 }, "blink", elem_blink, ns_default, EP_SIMPLE },
    { { XHTML_2_0 }, { XHTML_2_0 }, "blockcode", elem_blockcode, ns_default, 0, EF_X2_STRUCT },
    { { HTML_1_0, HV_DEPRECATED30 }, { HTML_UNDEF }, "blockquote", elem_blockquote, ns_default, 0, EF_3_BQ | EF_BODY | EF_32_BLOCK | EF_4_BLOCK | EF_5_FLOW | EF_X2_STRUCT | EF_5_PALPABLE | EF_5_SECTION },
    { { HTML_1_0 }, { HTML_UNDEF }, "body", elem_body, ns_default, EP_LAZY },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "box", elem_box, ns_default, 0, EF_MATH },
    { { HTML_3_0, HV_DEPRECATED30 }, { HTML_3_0 }, "bq", elem_bq, ns_default, 0, EF_3_BQ },
    { { HTML_1_0 }, { HTML_UNDEF }, "br", elem_br, ns_default, EP_CLOSED, EF_TEXT | EF_PRE | EF_SPECIAL | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, "bt", elem_bt, ns_default, 0, EF_3_MATHVC },
    { { HTML_4_0, HV_NOTX2 }, { HTML_UNDEF }, "button", elem_button, ns_default, 0, EF_4_FORM | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "bvar", elem_bvar, ns_default, 0, EF_M_CONTENT | EF_M_DQ },
    { { HTML_PLUS }, { HTML_PLUS }, "byline", elem_byline, ns_default, 0, EF_BLOK },
    { { HTML_JAN05 }, { HTML_DEC06 }, "calendar", elem_calendar, ns_default, 0, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_JAN07 }, { HTML_UNDEF }, "canvas", elem_canvas, ns_default, EP_5_TRANSPARENT, EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_PALPABLE | EF_SVG2_GRAPH },
    { { HTML_PLUS, HV_RFC_1942 }, { HTML_UNDEF }, "caption", elem_caption, ns_default, 0, EF_X2_STRUCT | EF_X2_LIST },
    { { XHTML_1_0 }, { HTML_UNDEF }, "card", elem_card, ns_default, EP_CLOSED | EP_ARGS_1 | EP_5_OPEN, EF_M_CONTENT | EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "cartesianproduct", elem_cartesianproduct, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "cbytes", elem_cbytes, ns_default, EP_SIMPLE, EF_M_CONTENT },
    { { HTML_2_0, HV_DEPRECATED23 }, { HTML_2_0 }, "cdata", elem_cdata },  // mentioned in RFC 2070
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "ceiling", elem_ceiling, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_3_2 }, { XHTML_1_1 }, "center", elem_centre, ns_default, 0, EF_32_BLOCK | EF_4_BLOCK },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "cerror", elem_cerror, ns_default, 0, EF_M_CONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, "changed", elem_changed, ns_default, EP_CLOSED, EF_TEXT },
    { { HTML_3_0 }, { HTML_3_0 }, "choose", elem_choose, ns_default, EP_CLOSED },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "ci", elem_ci, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM}, { HTML_UNDEF }, "circle", elem_circle, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_1_0 }, { HTML_UNDEF }, "cite", elem_cite, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 | HE_ANIM }, { HTML_UNDEF }, "clipPath", elem_clippath, ns_default, EP_SET_XLINKCAT (se_clippath) },
    { { HTML_PLUS }, { HTML_PLUS }, "cmd", elem_cmd, ns_default, 0, EF_EMPH },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "cn", elem_cn, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_1_0 }, { HTML_UNDEF }, "code", elem_code, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "codomain", elem_codomain, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, "col", elem_col, ns_default, EP_CLOSED },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, "colgroup", elem_colgroup },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "color-profile", elem_colour_profile, ns_default, EP_SET_XLINKCAT (se_icc_profile) },
    { { HTML_JAN05 }, { HTML_DEC12 }, "command", elem_command, ns_default, EP_CLOSED, EF_METADATA | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_JAN05 }, { HTML_DEC05 }, "commandset", elem_commandset, ns_default, 0, EF_METADATA | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_1_0, HV_DEPRECATEDX10 | HE_IE | HE_NETSCAPE }, { HTML_1_0 }, "comment", elem_comment, ns_default, EP_XMP, EF_LIT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "complexes", elem_complexes, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "compose", elem_compose, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "condition", elem_condition, ns_default, 0, EF_M_CONTENT | EF_M_DQ },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "conjugate", elem_conjugate, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_JAN05, 0, HE_WEBCOMP }, { HTML_UNDEF }, "content", elem_content, ns_default, EP_CLOSED },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "cos", elem_cos, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "cosh", elem_cosh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "cot", elem_cot, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "coth", elem_coth, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_3_0 }, { HTML_3_0 }, "credit", elem_credit },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "cs", elem_cs, ns_default, EP_SIMPLE, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "csc", elem_csc, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "csch", elem_csch, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "csymbol", elem_csymbol, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "curl", elem_curl, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "cursor", elem_cursor, ns_default, EP_SET_XLINKCAT (se_image_file) },
    { { HTML_JAN12 }, { HTML_UNDEF }, "data", elem_data, ns_default, EP_CLOSED | EP_5_OPEN, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JUL05 }, { HTML_DEC09 }, "datagrid", elem_datagrid, ns_default, 0, EF_5_FLOW },
    { { HTML_JAN07 }, { HTML_UNDEF }, "datalist", elem_datalist, ns_default, 0, EF_5_FLOW | EF_5_PHRASE },
    { { HTML_JAN08 }, { HTML_DEC08 }, "datatemplate", elem_datatemplate, ns_default, 0, EF_METADATA | EF_5_FLOW },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "datatype", elem_rdf_datatype, ns_rdf, 0, EF_RDF },
    { { HTML_TAGS }, { HTML_UNDEF }, "dd", elem_dd, ns_default, EP_LAZY | EP_UNCLOSED1T,  EF_X2_STRUCT | EF_X2_LIST },
    { { HTML_3_0 }, { HTML_3_0 }, "ddot", elem_ddot, ns_default, 0, EF_3_MATHVC },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3_4_20 | H2_M3_DEPRECAT | H2_M4_DEPRECAT }, { HTML_UNDEF }, "declare", elem_declare, ns_default, 0, EF_M_CONTENT /*  | EF_M_CONTINPRES */ },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "definition-src", elem_definition_src, ns_default },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "defs", elem_defs, ns_default, 0, EF_S_G | EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_3_0, HV_NOT32 }, { HTML_UNDEF }, "del", elem_del, ns_default, EP_5_TRANSPARENT, EF_3_MISC | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "degree", elem_degree, ns_default, 0, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "desc", elem_desc, ns_default, 0, EF_S_G | EF_SVG_DESC },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "Description", elem_rdf_description, ns_rdf , 0, EF_RDF },
    { { HTML_JAN07, HV_NOT50 }, { HTML_UNDEF }, "details", elem_details, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "determinant", elem_determinant, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_1_0 }, { HTML_UNDEF }, "dfn", elem_dfn, ns_default, 0, EF_EMPH | EF_3_MISC | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JAN10 }, { HTML_JUN11 }, "device", elem_device, ns_default, EP_CLOSED, EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "deviceColor", elem_devicecolour, ns_default, EP_CLOSED, EF_S_G | EF_SVG_STR },
    { { XHTML_2_0 }, { XHTML_2_0 }, "di", elem_di, ns_default, 0, EF_X2_STRUCT | EF_X2_LIST },
    { { HTML_JAN07, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "dialog", elem_dialogue, ns_default, 0, EF_5_FLOW },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "diff", elem_diff, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_TAGS, HV_DEPRECATED30 | HV_DEPRECATED4 }, { HTML_4_01 }, "dir", elem_dir, ns_default, EP_ONLYELEMENTS, EF_3_LIST | EF_LL | EF_LIST | EF_32_BLOCK | EF_4_BLOCK },
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, "discard", elem_discard, ns_default, EP_SET_XLINKCAT (se_animation), EF_SVG_ANIM },
    { { XHTML_2_0 }, { XHTML_2_0 }, "dispatchevent", elem_dispatchevent, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { HTML_UNDEF }, "div", elem_div, ns_default, 0, EF_3_BODY | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "divergence", elem_divergence, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "divide", elem_divide, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_TAGS }, { HTML_UNDEF }, "dl", elem_dl, ns_default, EP_ONLYELEMENTS, EF_BODY | EF_LIST | EF_3_BLOCK | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_X2_LIST | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "domain", elem_domain, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "domainofapplication", elem_domainofapplication, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_DQ },
    { { HTML_3_0 }, { HTML_3_0 }, "dot", elem_dot, ns_default, 0, EF_3_MATHVC },
    { { HTML_TAGS }, { HTML_UNDEF }, "dt", elem_dt, ns_default, EP_UNCLOSED1T | EP_LAZY, EF_X2_STRUCT | EF_X2_LIST },
    { { HTML_JAN05, 0, HE_WEBCOMP }, { HTML_UNDEF }, "element", elem_element, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "elementDef", elem_elementdef },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "ellipse", elem_ellipse, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_1_0 }, { HTML_UNDEF }, "em", elem_em, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JAN07 }, { HTML_UNDEF }, "embed", elem_embed, ns_default, EP_CLOSED | EP_5_WILDATTR, EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "emptyset", elem_emptyset, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "eq", elem_eq, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "equivalent", elem_equivalent, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "eulergamma", elem_eulergamma, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_JAN05 }, { HTML_JUN08 }, "event-source", elem_event_source, ns_default, EP_CLOSED, EF_METADATA | EF_4_BLOCK | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_JUL08 }, { HTML_JUN09 }, "eventsource", elem_eventsource, ns_default, EP_CLOSED, EF_METADATA | EF_4_BLOCK | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "exists", elem_exists, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "exp", elem_exp, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "exponentiale", elem_exponentiale, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "extensionDefs", elem_extensiondefs, ns_default, 0, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "factorial", elem_factorial, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "factorof", elem_factorof, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "false", elem_false, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_1_0 }, { HTML_UNDEF }, "fe", elem_fe, ns_default, EP_5_TRANSPARENT, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feBlend", elem_feblend, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feColorMatrix", elem_fecolourmatrix, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feComponentTransfer", elem_fecomponenttransfer, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feComposite", elem_fecomposite, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feConvolveMatrix", elem_feconvolvematrix, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feDiffuseLighting", elem_fediffuselighting, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feDisplacementMap", elem_fedisplacementmap, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feDistantLight", elem_fedistantlight, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "feDropShadow", elem_fedropshadow, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feFlood", elem_feflood, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feFuncA", elem_fefunca, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feFuncB", elem_fefuncb, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feFuncG", elem_fefuncg, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feFuncR", elem_fefuncr, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feGaussianBlur", elem_fegaussianblur, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feImage", elem_feimage, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feMerge", elem_femerge, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feMergeNode", elem_femergenode, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feMorphology", elem_femorphology, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feOffset", elem_feoffset, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "fePointLight", elem_fepointlight, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feSpecularLighting", elem_fespecularlighting, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feSpotLight", elem_fespotlight, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feTile", elem_fetile, ns_default, 0, EF_SVG_FILTER },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "feTurbulence", elem_feturbulence, ns_default, 0, EF_SVG_FILTER },
    { { HTML_4_0, HV_NOTX2 }, { HTML_UNDEF }, "fieldset", elem_fieldset, ns_default, 0, EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "fig", elem_fig, ns_default, 0, EF_PARA | EF_3_BLOCK },
    { { HTML_JUL10 }, { HTML_UNDEF }, "figcaption", elem_figcaption },
    { { HTML_JAN07 }, { HTML_UNDEF }, "figure", elem_figure, ns_default, 0, EF_5_FLOW | EF_5_PALPABLE | EF_5_SECTION },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "filter", elem_filter, ns_default, EP_SET_XLINKCAT (se_filter), EF_S_G },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "floor", elem_floor, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowDiv", elem_flowdiv },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowImage", elem_flowimage },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowLine", elem_flowline },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowPara", elem_flowpara },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowRef", elem_flowref, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowRegion", elem_flowregion },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowRegionBreak", elem_flowregionbreak, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowRegionExclude", elem_flowregionexclude },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowRoot", elem_flowroot, ns_default, 0, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowSpan", elem_flowspan },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "flowTref", elem_flowtref, ns_default, EP_CLOSED },
    { { HTML_3_0, HV_NOT4 | HV_NOT32, 0, H2_MATH_1_2_3_4_20 | H2_M3_DEPRECAT | H2_M4_DEPRECAT }, { HTML_UNDEF }, "fn", elem_fn, ns_default, 0, EF_3_BLOCK | EF_X_MATH | EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_3_2, HV_DEPRECATED4, HE_SVG_OLD_H | HE_SVG_1 }, { HTML_UNDEF }, "font", elem_font, ns_default, 0, EF_SPECIAL | EF_4_SPECIAL | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "font-face", elem_font_face },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "font-face-format", elem_font_face_format, ns_default, EP_CLOSED },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "font-face-name", elem_font_face_name, ns_default, EP_CLOSED },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "font-face-src", elem_font_face_src },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "font-face-uri", elem_font_face_uri },
    { { HTML_JAN05 }, { HTML_UNDEF }, "footer", elem_footer, ns_default, 0, EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_PLUS }, { HTML_PLUS }, "footnote", elem_footnote, ns_default, 0, EF_MISC },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "forall", elem_forall, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_PLUS, HV_NOT2L1 | HV_NOTX2 }, { HTML_UNDEF }, "form", elem_form, ns_default, 0, EF_BLOK | EF_3_BLOCK | EF_32_FORM | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "foreignObject", elem_foreignobject, ns_default, EP_HOLDS_ALL, EF_SVG2_GRAPH },
    { { HTML_4_0 }, { XHTML_1_1 }, "frame", elem_frame, ns_default, EP_CLOSED },
    { { HTML_4_0, HV_FRAMESET }, { HTML_4_01 }, "frameset", elem_frameset },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "g", elem_g, ns_default, 0, EF_S_G | EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_JAN05 }, { HTML_JUN06 }, "gauge", elem_gauge, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "gcd", elem_gcd, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "geq", elem_geq, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "glyph", elem_glyph, ns_default, 0, EF_SVG_CONTAIN },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "glyphRef", elem_glyphref },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "grad", elem_grad, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "gt", elem_gt, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { XHTML_2_0 }, { XHTML_2_0 }, "h", elem_h, ns_default, 0, EF_HEAD },
    { { HTML_TAGS }, { HTML_UNDEF }, "h1", elem_h1, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "h2", elem_h2, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "h3", elem_h3, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "h4", elem_h4, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "h5", elem_h5, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_TAGS }, { HTML_UNDEF }, "h6", elem_h6, ns_default, 0, EF_HEAD | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_SVG12, 0, HE_SVG_12 | HE_SVG_X2 }, { HTML_UNDEF }, "handler", elem_handler, ns_default, EP_SIMPLE },
    { { HTML_3_0 }, { HTML_3_0 }, "hat", elem_hat, ns_default, 0, EF_3_MATHVC },
    { { HTML_1_0 }, { HTML_UNDEF }, "head", elem_head, ns_default, EP_LAZY },
    { { HTML_JAN05 }, { HTML_UNDEF }, "header", elem_header, ns_default, 0, EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_JUL09, HV_WHATWG }, { HTML_UNDEF }, "hgroup", elem_hgroup, ns_default, 0, EF_HEAD | EF_5_FLOW },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "hint", elem_hint, ns_default, EP_SIMPLE, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "hkern", elem_hkern, ns_default, EP_CLOSED | EP_UNCLOSEDSVG12 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp1", elem_hp1 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp2", elem_hp2 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp3", elem_hp3 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp4", elem_hp4 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp5", elem_hp5 },
    { { HTML_TAGS, HV_DEPRECATEDX10 }, { HTML_1_0 }, "hp6", elem_hp6 },
    { { HTML_1_0 }, { HTML_UNDEF }, "hr", elem_hr, ns_default, EP_CLOSED, EF_PRE | EF_BLOK | EF_3_BODY | EF_32_BLOCK | EF_4_BLOCK | EF_5_FLOW },
    { { HTML_1_0, HV_NOTPLUS }, { HTML_UNDEF }, "html", elem_html, ns_default, EP_TOP | EP_LAZY },
    { { HTML_PLUS }, { HTML_PLUS }, "htmlplus", elem_htmlplus, ns_default, EP_TOP | EP_LAZY },
    { { HTML_1_0 }, { HTML_UNDEF }, "i", elem_i, ns_default, 0, EF_EMPH | EF_FONT | EF_3_FONT | EF_32_FONT | EF_4_FONT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "ID", elem_rdf_id, ns_rdf, 0, EF_RDF },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "ident", elem_ident, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_4_0 }, { HTML_UNDEF }, "iframe", elem_iframe, ns_default, 0, EF_4_SPECIAL | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_SVG2_GRAPH },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, "ilayer", elem_ilayer },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32, HE_ANIM }, { HTML_UNDEF }, "image", elem_image, ns_default, EP_CLOSED | EP_4_OPEN | EP_5_OPEN, EF_TEXT | EF_S_G | EF_SVG_GRAPH | EF_SVG_STR | EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "imaginary", elem_imaginary, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "imaginaryi", elem_imaginaryi, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_1_0 }, { HTML_UNDEF }, "img", elem_img, ns_default, EP_CLOSED | EP_X2_OPEN | EP_5_DYNAMIC, EF_TEXT  | EF_SPECIAL | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "implies", elem_implies, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "in", elem_in, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "infinity", elem_infinity, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_PLUS, HV_NOT2L1 | HV_NOTX2 }, { HTML_UNDEF }, "input", elem_input, ns_default, EP_CLOSED | EP_LAZY, EF_MISC | EF_4_FORM | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_3_0, HV_NOT32 }, { HTML_UNDEF }, "ins", elem_ins, ns_default, EP_5_TRANSPARENT, EF_3_MISC | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "int", elem_int, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "integers", elem_integers, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "intersect", elem_intersect, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "interval", elem_interval, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "inverse", elem_inverse, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_TAGS, HV_DEPRECATED4 }, { XHTML_1_1 }, "isindex", elem_isindex, ns_default, EP_CLOSED, EF_32_BLOCK | EF_METADATA | EF_3_BLOCK | EF_4_BLOCK },
    { { HTML_PLUS, HV_NOT2 }, {3, 0 }, "item", elem_item, ns_default, EP_CLOSED },
    { { HTML_1_0 }, { HTML_UNDEF }, "kbd", elem_kbd, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JUL09, HV_NOT52 | HV_NOT53 }, { HTML_JUN17 }, "keygen", elem_keygen, ns_default, EP_CLOSED, EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_PLUS, HV_NOT234 | HV_NOTX1 }, { XHTML_2_0 }, "l", elem_l, ns_default, EP_CLOSED | EP_X2_OPEN, EF_X2_TEXT },
    { { HTML_4_0 }, { HTML_UNDEF }, "label", elem_label, ns_default, 0, EF_4_FORM | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "lambda", elem_lambda, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_3_0 }, { HTML_3_0 }, "lang", elem_lang, ns_default, 0, EF_3_MISC },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "laplacian", elem_laplacian, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_3_2 }, "layer", elem_layer },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "lcm", elem_lcm, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_3_0 }, { HTML_3_0 }, "left", elem_left, ns_default, EP_CLOSED },
    { { HTML_4_0 }, { HTML_UNDEF }, "legend", elem_legend },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "leq", elem_leq, ns_default, EP_CLOSED| EP_ARGS_2| EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_3_0 }, { HTML_3_0 }, "lh", elem_lh },
    { { HTML_TAGS }, { HTML_UNDEF }, "li", elem_li, ns_default, EP_UNCLOSED1T, EF_X2_STRUCT | EF_X2_LIST },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "li", elem_rdf_li, ns_rdf, 0, EF_RDF },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "limit", elem_limit, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "line", elem_line, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "linearGradient", elem_lineargradient, ns_default, EP_SET_XLINKCAT (se_gradient), EF_SVG_PSGRAD },
    { { HTML_1_0 }, { HTML_UNDEF }, "link", elem_link, ns_default, EP_CLOSED, EF_METADATA | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "list", elem_list, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG12 }, { HTML_UNDEF }, "listener", elem_listener, ns_default, EP_CLOSED, EF_X2_STRUCT },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "listener", elem_listener, ns_xmlevents, EP_CLOSED },
    { { HTML_TAGS, HV_DEPRECATED123 }, { HTML_3_2 }, "listing", elem_listing, ns_default, 0, EF_LIT },
    { { HTML_PLUS }, { HTML_PLUS }, "lit", elem_lit, ns_default, 0, EF_PARA },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "ln", elem_ln, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "loc", elem_loc },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "log", elem_log, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "logbase", elem_logbase, ns_default, 0, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "lowlimit", elem_lowlimit, ns_default, 0, EF_M_CONTENT | EF_M_DQ },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "lt", elem_lt, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_JUL05 }, { HTML_JUN08 }, "m", elem_m, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE | EF_SVG_CONTAIN },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "maction", elem_maction, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_JUL13 }, { HTML_UNDEF }, "main", elem_main, ns_default, 0, EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "maligngroup", elem_maligngroup, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "malignmark", elem_malignmark, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_2_0, HV_RFC_1980 | HV_NOT30  }, { HTML_UNDEF }, "map", elem_map, ns_default, EP_5_TRANSPARENT, EF_TEXT | EF_SPECIAL | EF_4_SPECIAL | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_PLUS }, { HTML_PLUS }, "margin", elem_margin, ns_default, 0, EF_MISC },
    { { HTML_JUL08 }, { HTML_UNDEF }, "mark", elem_mark, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE | EF_SVG_CONTAIN },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "marker", elem_marker, ns_default, 0, EF_SVG_CONTAIN },
    { { HTML_2_0, 0, HE_IE }, { HTML_3_2 }, "marquee", elem_marquee, ns_default, EP_CLOSED },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 | HE_ANIM }, { HTML_UNDEF }, "mask", elem_mask },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 | HV_NOT4, 0, H2_MATH }, { HTML_UNDEF }, "math", elem_math, ns_default, 0, EF_BLOK | EF_SPECIAL | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_X_MATH },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "matrix", elem_matrix, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "matrixrow", elem_matrixrow, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "max", elem_max, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "mean", elem_mean, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "median", elem_median, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "menclose", elem_menclose, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_TAGS, HV_DEPRECATED30 | HV_DEPRECATED4 | HV_NOTX2 | HV_NOT50 | HV_NOT52 | HV_NOT53 }, { HTML_UNDEF }, "menu", elem_menu, ns_default, EP_ONLYELEMENTS, EF_3_LIST | EF_LL | EF_LIST | EF_32_BLOCK | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_JAN05 }, { HTML_DEC05 }, "menubar", elem_menubar, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JAN13 }, { HTML_JUN17 }, "menuitem", elem_menuitem, ns_default, EP_CLOSED },
    { { HTML_JAN05 }, { HTML_DEC05 }, "menulabel", elem_menulabel, ns_default, 0, EF_3_LIST | EF_LL | EF_LIST | EF_32_BLOCK | EF_4_BLOCK | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "merror", elem_merror, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_2_0 }, { HTML_UNDEF }, "meta", elem_meta, ns_default, EP_CLOSED | EP_X2_OPEN, EF_METADATA | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "metadata", elem_metadata, ns_default, 0, EF_SVG_DESC },
    { { HTML_JUL06 }, { HTML_UNDEF }, "meter", elem_meter, ns_default, EP_SIMPLE, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "mfenced", elem_mfenced, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mfrac", elem_mfrac, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "mglyph", elem_mglyph, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, "mh", elem_mh, ns_default, EP_SIMPLE },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mi", elem_mi, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "min", elem_min, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "minus", elem_minus, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "missing-glyph", elem_missingglyph, ns_default, 0, EF_SVG_CONTAIN },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "mlabeledtr", elem_mlabeledtr, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "mlongdiv", elem_mlongdiv, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mmultiscripts", elem_mmultiscripts, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mn", elem_mn, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mo", elem_mo, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "mode", elem_mode, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "moment", elem_moment, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "momentabout", elem_momentabout, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mover", elem_mover, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mpadded", elem_mpadded, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "mpath", elem_mpath },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mphantom", elem_mphantom, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mprescripts", elem_mprescripts, ns_default, EP_CLOSED, EF_M_PRES },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mroot", elem_mroot, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mrow", elem_mrow, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "ms", elem_ms, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "mscarries", elem_mscarries },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "mscarry", elem_mscarry, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "msgroup", elem_msgroup, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "msline", elem_msline, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mspace", elem_mspace, ns_default, EP_CLOSED, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "msqrt", elem_msqrt, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "msrow", elem_msrow, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "mstack", elem_mstack, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mstyle", elem_mstyle, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "msub", elem_msub, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "msubsup", elem_msubsup, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "msup", elem_msup, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mtable", elem_mtable, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mtd", elem_mtd, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mtext", elem_mtext, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "mtr", elem_mtr, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_4_01 }, "multicol", elem_multicol },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "munder", elem_munder, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "munderover", elem_munderover, ns_default, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "naturalnumbers", elem_naturalnumbers, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_JUL05 }, { HTML_UNDEF }, "nav", elem_nav, ns_default, 0, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_JAN05 }, { HTML_JUN05 }, "navigation", elem_navigation, ns_default, 0, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "neq", elem_neq, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_JAN08 }, { HTML_DEC08 }, "nest", elem_nest, ns_default, EP_CLOSED, EF_METADATA | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE },
    { { HTML_TAGS, HV_DEPRECATED23 }, { HTML_3_0 }, "nextid", elem_nextid, ns_default, EP_CLOSED, EF_METADATA },
    { { XHTML_2_0 }, { XHTML_2_0 }, "nl", elem_nl, ns_default, 0, EF_X2_STRUCT | EF_X2_LIST }, // riffing; the XHTML2 spec is inconsistent re nl
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_2_0 }, "nobr", elem_nobr, ns_default, 0, EF_EMPH },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "nodeID", elem_rdf_nodeid, ns_rdf, 0, EF_RDF },
    { { HTML_JAN05, HV_DEPRECATED50 }, { HTML_JAN05 }, "noembed", elem_noembed },
    { { HTML_4_0 }, { HTML_4_01 }, "noframes", elem_noframes, ns_default, 0, EF_4_BLOCK },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "none", elem_none, ns_default, EP_CLOSED, EF_M_PRES },
    { { HTML_4_0, HV_NOTX5 }, { HTML_UNDEF }, "noscript", elem_noscript, ns_default, EP_5_TRANSPARENT, EF_METADATA | EF_4_BLOCK | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "not", elem_not, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "notanumber", elem_notanumber, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "note", elem_note, ns_default, 0, EF_BLOK | EF_3_BLOCK },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "notin", elem_notin, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "notprsubset", elem_notprsubset, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "notsubset", elem_notsubset, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_4_0 }, { HTML_UNDEF }, "object", elem_object, ns_default, EP_5_TRANSPARENT, EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_3_0 }, { HTML_3_0 }, "of", elem_of, ns_default, EP_CLOSED },
    { { HTML_1_0, HV_DEPRECATED30 }, { HTML_UNDEF }, "ol", elem_ol, ns_default, EP_ONLYELEMENTS | EP_5_DYNAMIC, EF_3_LIST | EF_LL | EF_LIST | EF_32_BLOCK | EF_4_BLOCK | EF_X2_LIST | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_PLUS }, { HTML_PLUS }, "online", elem_online, ns_default, 0, EF_EMPH },
    { { HTML_4_0, HV_NOTX2 }, { HTML_UNDEF }, "optgroup", elem_optgroup },
    { { HTML_PLUS, HV_NOT2L1 | HV_NOTX2 }, { HTML_UNDEF }, "option", elem_option, ns_default, EP_SIMPLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "or", elem_or, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "otherwise", elem_otherwise, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "outerproduct", elem_outerproduct, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_JAN07 }, { HTML_UNDEF }, "output", elem_output, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "over", elem_over, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { HTML_3_0 }, "overlay", elem_overlay, ns_default, EP_CLOSED },
    { { HTML_TAGS }, { HTML_UNDEF }, "p", elem_p, ns_default, EP_UNCLOSED1T | EP_LAZY, EF_BODY | EF_TABLE | EF_PARA | EF_3_BLOCK | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_3_2 }, { HTML_JUN22 }, "param", elem_param, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "page", elem_page },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "pageSet", elem_pageset, ns_default, 0, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "parseType", elem_rdf_parsetype, ns_rdf, 0, EF_RDF },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "partialdiff", elem_partialdiff, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_X_MATH | EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "path", elem_path, ns_default, 0, EF_S_G | EF_SVG_GRAPH | EF_SVG_SHAPE | EF_SVG2_GRAPH },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "pattern", elem_pattern, ns_default, EP_SET_XLINKCAT (se_pattern), EF_S_G | EF_SVG_CONTAIN | EF_SVG_PSGRAD },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, "person", elem_person, ns_default, 0, EF_EMPH | EF_3_MISC },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "pi", elem_pi, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "piece", elem_piece, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "piecewise", elem_piecewise, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, "picture", elem_picture, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_PALPABLE },
    { { HTML_TAGS, HV_DEPRECATED123 }, { HTML_3_2 }, "plaintext", elem_plaintext, ns_default, EP_CLOSED | EP_XMP },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "plus", elem_plus, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "polygon", elem_polygon, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "polyline", elem_polyline, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "power", elem_power, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_1_0, HV_DEPRECATED23 }, { HTML_UNDEF }, "pre", elem_pre, ns_default, 0, EF_BODY | EF_PARA | EF_3_BLOCK | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "prefetch", elem_prefetch },
    { { XHTML_2_0 }, { XHTML_2_0 }, "preventdefault", elem_preventdefault, ns_default, EP_CLOSED },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "primes", elem_primes, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_PLUS }, { HTML_PLUS }, "printed", elem_printed, ns_default, 0, EF_EMPH },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "product", elem_product, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_JUL06 }, { HTML_UNDEF }, "progress", elem_progress, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "prototype", elem_prototype },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "prsubset", elem_prsubset, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_PLUS, HV_RFC_2070 | HV_NOT32 }, { HTML_UNDEF }, "q", elem_q, ns_default, 0, EF_TEXT | EF_EMPH | EF_3_MISC | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_PLUS }, { HTML_PLUS }, "quote", elem_quote, ns_default, 0, EF_BLOK },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "quotient", elem_quotient, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "radialGradient", elem_radialgradient, ns_default, EP_SET_XLINKCAT (se_gradient), EF_SVG_PSGRAD },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "rationals", elem_rationals, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_3_0 }, { HTML_3_0 }, "range", elem_range, ns_default, EP_CLOSED },
    { { XHTML_1_1, HV_W3 }, { HTML_UNDEF }, "rb", elem_rb },
    { { XHTML_1_1 }, { XHTML_2_0 }, "rbc", elem_rbc },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "RDF", elem_rdf_rdf, ns_rdf, 0, EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_RDF | EF_METADATA },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "real", elem_real, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "reals", elem_reals, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "rect", elem_rect, ns_default, 0, EF_S_G | EF_SVG_SHAPE | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "refContent", elem_refcontent, ns_default, 0, EF_SVG_DESC },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3_4_20 | H2_M2_DEPRECAT | H2_M3_DEPRECAT | H2_M4_DEPRECAT }, { HTML_UNDEF }, "reln", elem_reln, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "rem", elem_rem, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, "removed", elem_removed, ns_default, 0, EF_EMPH },
    { { XHTML_2_0 }, { XHTML_2_0 }, "removeeventlistener", elem_removeeventlistener, ns_default, EP_CLOSED },
    { { HTML_PLUS }, { HTML_PLUS }, "render", elem_render, ns_default, EP_CLOSED, EF_MISC | EF_METADATA },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "resource", elem_rdf_resource, ns_rdf, 0, EF_RDF },
    { { HTML_3_0 }, { HTML_3_0 }, "right", elem_right, ns_default, EP_CLOSED },
    { { HTML_3_0, HV_NOT4 | HV_NOT32 }, { HTML_UNDEF }, "root", elem_root, ns_default, EP_CLOSED | EP_PRE_X_OPEN | EP_ARGS_1 | EP_ARGS_2, EF_MATH | EF_M_CONTENT },
    { { HTML_3_0 }, { HTML_3_0 }, "row", elem_row },
    { { XHTML_1_1 }, { HTML_UNDEF }, "rp", elem_rp },
    { { XHTML_1_1 }, { HTML_UNDEF }, "rt", elem_rt },
    { { XHTML_1_1, HV_W3 }, { HTML_UNDEF }, "rtc", elem_rtc },
    { { XHTML_1_1 }, { HTML_UNDEF }, "ruby", elem_ruby, ns_default, 0, EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_JAN08 }, { HTML_DEC08 }, "rule", elem_rule },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 | HV_DEPRECATED4 | HV_NOTXX }, { HTML_UNDEF }, "s", elem_s, ns_default, 0, EF_EMPH | EF_3_FONT | EF_4_FONT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_1_0 }, { HTML_UNDEF }, "samp", elem_samp, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_1_0 }, { HTML_UNDEF }, "sarcasm", elem_sarcasm, ns_default, EP_5_TRANSPARENT, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "scalarproduct", elem_scalarproduct, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_3_2 }, { HTML_UNDEF }, "script", elem_script, ns_default, EP_SET_XLINKCAT (se_script), EF_METADATA | EF_SPECIAL | EF_4_SPECIAL | EF_X2_STRUCT | EF_5_FLOW | EF_5_PHRASE | EF_5_SCRIPT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sdev", elem_sdev, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sec", elem_sec, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sech", elem_sech, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { XHTML_2_0 }, { HTML_UNDEF }, "section", elem_section, ns_default, 0, EF_X2_STRUCT | EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_PLUS, HV_NOT2L1 | HV_NOTX2 }, { HTML_UNDEF }, "select", elem_select, ns_default, 0, EF_MISC | EF_32_FORM | EF_4_FORM | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "selector", elem_selector, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, "semantics", elem_semantics, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sep", elem_sep, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, "Seq", elem_rdf_seq, ns_rdf, 0, EF_RDF },
    { { XHTML_2_0 }, { XHTML_2_0 }, "separator", elem_separator, ns_default, EP_CLOSED, EF_X2_STRUCT },
    { { HTML_MATH1, 0, HE_SVG, H2_MATHML }, { HTML_UNDEF }, "set", elem_set, ns_default, EP_CLOSED | EP_SET_XLINKCAT (se_animation), EF_M_CONTENT | EF_M_CONTINPRES | EF_SVG_ANIM },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "setdiff", elem_setdiff, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_JAN05, 0, HE_WEBCOMP }, { HTML_UNDEF }, "shadow", elem_shadow },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, "share", elem_share, ns_default, EP_CLOSED, EF_M_CONTENT },
    { { HTML_JAN05 }, { HTML_JUN05 }, "sidebar", elem_sidebar, ns_default, 0, EF_5_FLOW | EF_5_SECTION | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sin", elem_sin, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sinh", elem_sinh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_JUL16, HV_WHATWG }, { HTML_UNDEF }, "slot", elem_slot, ns_default, EP_5_TRANSPARENT, EF_5_FLOW | EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_UNDEF }, "small", elem_small, ns_default, 0, EF_3_FONT | EF_32_FONT | EF_4_FONT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "solidColor", elem_solidcolour },
    { { HTML_JUL07 }, { HTML_UNDEF }, "source", elem_source, ns_default, EP_CLOSED },
    { { HTML_2_0, 0, HE_NETSCAPE }, { HTML_4_01 }, "spacer", elem_spacer, ns_default, EP_SIMPLE },
    { { HTML_2_0, HV_RFC_2070 | HV_NOT3 }, { HTML_UNDEF }, "span", elem_span, ns_default, 0, EF_TEXT | EF_PRE | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_3_0 }, { HTML_3_0 }, "spot", elem_spot, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { HTML_3_0 }, "sqrt", elem_sqrt, ns_default, 0, EF_MATH },
    { { XHTML_2_0 }, { XHTML_2_0 }, "standby", elem_standby },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "stop", elem_stop },
    { { XHTML_2_0 }, { XHTML_2_0 }, "stoppropagation", elem_stoppropagation, ns_default, EP_CLOSED },
    { { HTML_3_2, HV_DEPRECATED4 }, { HTML_4_01 }, "strike", elem_strike, ns_default, 0, EF_32_FONT | EF_4_FONT },
    { { HTML_1_0 }, { HTML_UNDEF }, "strong", elem_strong, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_3_0 }, { HTML_UNDEF }, "style", elem_style, ns_default, EP_SIMPLE, EF_METADATA | EF_X2_STRUCT | EF_5_FLOW },
    { { HTML_PLUS, HV_RFC_2070 }, { HTML_UNDEF }, "sub", elem_sub, ns_default, 0, EF_TEXT | EF_MATH | EF_EMPH | EF_3_TEXT | EF_32_FONT | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "subset", elem_subset, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "sum", elem_sum, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { XHTML_2_0, HV_NOT50 }, { HTML_UNDEF }, "summary", elem_summary },
    { { HTML_PLUS, HV_RFC_2070 }, { HTML_UNDEF }, "sup", elem_sup, ns_default, 0, EF_TEXT | EF_MATH | EF_EMPH | EF_3_TEXT | EF_32_FONT | EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM_11_2 }, { HTML_UNDEF }, "svg", elem_svg, ns_default, 0, EF_4_SPECIAL | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_S_G | EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "switch", elem_switch, ns_default, EP_SVG_12_TRANS, EF_S_G | EF_SVG_CONTAIN },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "symbol", elem_symbol, ns_default, 0, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_3_0, HV_NOT324XX }, { HTML_DEC06 }, "t", elem_t, ns_default, 0, EF_3_MATHVC | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 | HV_NOT4 }, { HTML_UNDEF }, "tab", elem_tab, ns_default, EP_CLOSED, EF_SPECIAL | EF_X_MATH },
    { { HTML_JAN05 }, { HTML_DEC06 }, "tabbox", elem_tabbox, ns_default, 0, EF_5_FLOW | EF_5_PHRASE },
    { { HTML_PLUS, HV_RFC_1942 }, { HTML_UNDEF }, "table", elem_table, ns_default, 0, EF_BLOK | EF_3_BLOCK | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "tan", elem_tan, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "tanh", elem_tanh, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, "tbody", elem_tbody },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "tbreak", elem_tbreak, ns_default, EP_CLOSED },
    { { HTML_PLUS, HV_RFC_1942 }, { HTML_UNDEF }, "td", elem_td, ns_default, EP_LAZY | EP_UNCLOSEDPLUS },
    { { HTML_JUL13 }, { HTML_UNDEF }, "template", elem_template, ns_default, 0, EF_METADATA | EF_5_FLOW | EF_5_PHRASE | EF_5_SCRIPT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "tendsto", elem_tendsto, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_3_0, HV_NOT32, HE_SVG | HE_SVG_OLD_H | HE_ANIM }, { HTML_UNDEF }, "text", elem_text, ns_default, 0, EF_S_G | EF_SVG_GRAPH | EF_SVG_TEXT | EF_SVG2_GRAPH },
    { { HTML_PLUS, HV_NOT2L1 | HV_NOTX2 }, { HTML_UNDEF }, "textarea", elem_textarea, ns_default, EP_NO_WHINGE, EF_MISC | EF_32_FORM | EF_4_FORM | EF_5_FLOW | EF_5_PHRASE | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_5_FORM },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "textPath", elem_textpath, ns_default, EP_SET_XLINKCAT (se_path), EF_SVG_TEXT | EF_SVG2_GRAPH },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, "tfoot", elem_tfoot },
    { { HTML_PLUS, HV_RFC_1942 }, { HTML_UNDEF }, "th", elem_th, ns_default, EP_LAZY | EP_UNCLOSEDPLUS },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, "thead", elem_thead },
    { { HTML_3_0 }, { HTML_3_0 }, "tilde", elem_tilde, ns_default, 0, EF_3_MATHVC },
    { { HTML_JAN07 }, { HTML_UNDEF }, "time", elem_time, ns_default, 0, EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "times", elem_times, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_TAGS }, { HTML_UNDEF }, "title", elem_title, ns_default, EP_SIMPLE, EF_METADATA | EF_X2_STRUCT | EF_X2_LIST | EF_X2_TEXT | EF_S_G | EF_SVG_DESC },
    { { HTML_PLUS, HV_RFC_1942 }, { HTML_UNDEF }, "tr", elem_tr, ns_default, EP_UNCLOSEDPLUS },
    { { HTML_JUL10 }, { HTML_UNDEF }, "track", elem_track, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "traitDef", elem_traitdef, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "transition", elem_transition, ns_default, EP_CLOSED, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "transformer", elem_transformer },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "transpose", elem_transpose, ns_default, EP_CLOSED | EP_ARGS_1, EF_M_CONTENT },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "tref", elem_tref, ns_default, EP_SET_XLINKCAT (se_svg), EF_SVG_TEXT },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "true", elem_true, ns_default, EP_CLOSED, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "tspan", elem_tspan, ns_default, EP_SVG_12_TRANS, EF_SVG_TEXT | EF_SVG2_GRAPH },
    { { HTML_1_0 }, { XHTML_1_1 }, "tt", elem_tt, ns_default, 0, EF_EMPH | EF_FONT | EF_3_FONT | EF_32_FONT | EF_4_FONT },
    { { HTML_1_0, HV_DEPRECATED4 | HV_NOTX2 }, { HTML_UNDEF }, "u", elem_u, ns_default, 0, EF_EMPH | EF_3_FONT | EF_32_FONT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_TAGS, HV_DEPRECATED30 }, { HTML_UNDEF }, "ul", elem_ul, ns_default, EP_ONLYELEMENTS | EP_5_DYNAMIC, EF_3_LIST | EF_LL | EF_LIST | EF_32_BLOCK | EF_4_BLOCK | EF_X2_STRUCT | EF_X2_LIST | EF_5_FLOW | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "union", elem_union, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "uplimit", elem_uplimit, ns_default, 0, EF_M_CONTENT | EF_M_DQ },
    { { HTML_SVG10, 0, HE_SVG | HE_ANIM }, { HTML_UNDEF }, "use", elem_use, ns_default, 0, EF_S_G | EF_SVG_STR | EF_SVG_GRAPH | EF_SVG2_GRAPH },
    { { HTML_1_0 }, { HTML_UNDEF }, "var", elem_var, ns_default, 0, EF_EMPH | EF_PHRASE | EF_4_PHRASE | EF_X2_TEXT | EF_5_FLOW | EF_5_PHRASE | EF_5_PALPABLE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "variance", elem_variance, ns_default, EP_CLOSED | EP_ARGS_1 | EP_ARGS_MORE, EF_M_CONTENT },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veAffine", elem_veaffine, ns_default, EP_CLOSED },
    { { HTML_3_0 }, { HTML_3_0 }, "vec", elem_vec, ns_default, 0, EF_3_MATHVC },
    { { HTML_MATH1, 0, 0, H2_MATHML | H2_M2_DEPRECAT }, { HTML_UNDEF }, "vector", elem_vector, ns_default, 0, EF_M_CONTENT | EF_M_CONTINPRES },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "vectorEffect", elem_vectoreffect, ns_default, 0, EF_SVG_STR | EF_SVG_CONTAIN },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, "vectorproduct", elem_vectorproduct, ns_default, EP_CLOSED | EP_ARGS_2, EF_M_CONTENT },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veExclude", elem_veexclude, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veFill", elem_vefill, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veIntersect", elem_veintersect, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veJoin", elem_vejoin, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veMarker", elem_vemarker, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veMarkerPath", elem_vemarkerpath, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "vePath", elem_vepath },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "vePathRef", elem_vepathref, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veReverse", elem_vereverse, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veSetback", elem_vesetback, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veStroke", elem_vestroke, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veStrokePath", elem_vestrokepath, ns_default, EP_CLOSED },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "veUnion", elem_veunion, ns_default, EP_CLOSED },
    { { HTML_SVG12 }, { HTML_UNDEF }, "video", elem_video, ns_default, EP_5_TRANSPARENT, EF_5_FLOW | EF_5_PHRASE | EF_5_EMBEDDED | EF_5_INTERACTIVE | EF_5_PALPABLE | EF_SVG2_GRAPH },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "view", elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "vkern", elem_vkern, ns_default, EP_CLOSED },
    { { HTML_2_0, HV_NOT324XX }, { HTML_UNDEF }, "wbr", elem_wbr, ns_default, EP_CLOSED, EF_EMPH | EF_5_FLOW | EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "xa", elem_xa, ns_default, EP_SVG_12_TRANS, EF_S_G | EF_SVG_CONTAIN },
    { { HTML_2_0, 0, HE_IE }, { HTML_4_01 }, "xml", elem_xml, ns_default, EP_SIMPLE },
    { { HTML_TAGS, HV_DEPRECATED123 }, { HTML_3_2 }, "xmp", elem_xmp, ns_default, EP_SIMPLE | EP_XMP, EF_LIT },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, "xor", elem_xor, ns_default, EP_CLOSED | EP_ARGS_2 | EP_ARGS_MORE, EF_M_CONTENT } };

e_element max_tag = last_element_tag;
element_bitset elem::ignored_;

elem :: elem (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x)
{   parse (nits, v, namespaces, x); }

void elem::init (nitpick& nits)
{   symbol < html_version, e_element > :: init (nits, elem_symbol_table, sizeof (elem_symbol_table) / sizeof (symbol_entry < html_version, e_element >), true); }

bool elem::under_parse (nitpick& nits, const html_version& v, const ::std::string& el, const ident_t n)
{   return symbol < html_version, e_element > :: parse (nits, v, el, n); }

bool elem::parse (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x)
{   PRESUME (! x.empty (), __FILE__, __LINE__);
    ::std::string el (x), n;
    ns (examine_namespace (nits, v, namespaces, el, n));
    if (el.empty ()) return false;
    nitpick knits;
    if (under_parse (knits, v, el, ns ()))
    {   nits.merge (knits); return true; }
    if ((ns () == ns_svg) || (ns () == ns_math))
    {   elem e;
        nitpick nuts;
        if (e.under_parse (nuts, v, el, ns_default))
            switch (ns ())
            {   case ns_svg :
                    if (e.is_svg ())
                    {   under_parse (nits, v, el, ns_default); return true; }
                    break;
                case ns_math :
                    if (e.is_math ())
                    {   under_parse (nits, v, el, ns_default); return true; }
                    break;
		default : break; } }
    nits.merge (knits);
    check_identifier_spelling (nits, v, el);
    return false; }

bool elem::is_unclosed (const html_version& v) const noexcept
{   if (v.unknown ()) return false;
    if (((flags () & EP_UNCLOSEDSVG12) == EP_UNCLOSEDSVG12) && v.is_svg_12 ()) return true;
    if ((flags () & (EP_IGNORE | EP_CLOSED)) != 0) return false;
    switch (v.mjr ())
    {   case 0 : return ((flags () & EP_UNCLOSEDTAGS) == EP_UNCLOSEDTAGS);
        case 1 : if (v.mnr () == 0) return ((flags () & EP_UNCLOSED1) == EP_UNCLOSED1);
                 return ((flags () & EP_UNCLOSEDPLUS) == EP_UNCLOSEDPLUS);
        case 2 : return ((flags () & EP_UNCLOSED2) == EP_UNCLOSED2);
        default : break; }
    return false; }

bool elem::is_lazy (const html_version& v) const noexcept
{   if ((categories () & EF_DOCUMENT) == EF_DOCUMENT) return false;
    if ((flags () & EP_IGNORE) != 0) return true;
    switch (v.mjr ())
    {   case 0 : return false;
        case 1 : if (v.mnr () == 1)
                    return ((flags () & (EP_LAZY)) | (categories () & (EF_EMPH))) != 0;
                 return false;
        default : break; }
    return false; }

bool elem::is_closed (const html_version& v) const noexcept
{   if ((flags () & EP_CLOSED) == 0) return false;
    switch (v.mjr ())
    {   case 0 :
        case 1 :
        case 2 :
        case 3 : return ((flags () & EP_PRE_X_OPEN) == 0);
        case 4 :
            if ((flags () & EP_4_OPEN) != 0) return false;
            switch (v.mnr ())
            {   case 0 :
                case 1 : return ((flags () & EP_PRE_X_OPEN) == 0);
                case 4 : return ((flags () & EP_X2_OPEN) == 0);
                default : break; }
            break;
        default : return ((flags () & EP_5_OPEN) == 0); }
    return true; }

bool elem::is_transparent (const html_version& v) const noexcept
{   if (v < xhtml_1_0) return false;
    if (v.is_5 () && ((flags () & EP_5_TRANSPARENT) == EP_5_TRANSPARENT)) return true;
    return (v.is_svg_12 () && ((flags () & EP_SVG_12_TRANS) == EP_SVG_12_TRANS)); }

void add_elements (const vstr_t& v)
{   nitpick nuts;
    for (auto e : v)
    {   vstr_t args (split_by_charset (e, ","));
        ::std::size_t x = args.size ();
        if (x > 4)
        {   x = 4;
            outstr.err ("ignoring extra arguments for '", args.at (0), "'\n"); }
        e_namespace ns = ns_default;
        flags_t flags = NOFLAGS, flags2 = NOFLAGS;
        switch (x)
        {   case 4 :
                flags2 = lexical < flags_t > :: cast (args.at (3));
                FALLTHROUGH;
            case 3 :
                flags = lexical < flags_t > :: cast (args.at (2));
                FALLTHROUGH;
            case 2 :
                ns = examine_value < t_namespace > (nuts, context.html_ver (), args.at (1));
                FALLTHROUGH;
            case 1 :
                elem::extend (::boost::to_lower_copy (args.at (0)), elem_custom, ns, context.html_ver (), html_0, flags, flags2);
                FALLTHROUGH;
            default : break; } } }

bool elem::fits_link_category (const html_version& v, const e_element e, const e_sought_category cat)
{   switch (cat)
    {   case se_any : return true;
        case se_clippath : return (e == elem_clippath);
        case se_colour_profile : return (e == elem_colour_profile);
        case se_filter : return (e == elem_filter);
        case se_glyph_alt : return (e == elem_glyph) || (e == elem_altglyphdef);
        case se_gradient : return (e == elem_lineargradient) || (e == elem_radialgradient);
        case se_animation : return elem :: first_version (e).svg_anim (v.svg_version ());
        case se_icc_profile :
        case se_image_file :
        case se_script : return false;
        case se_marker : return (e == elem_marker);
        case se_mask : return (e == elem_mask);
        case se_paint_server :
            switch (e)
            {   case elem_lineargradient :
                case elem_radialgradient :
                case elem_pattern :
                    return true;
                default : break; }
            return false;
        case se_path : return (e == elem_path);
        case se_pattern : return (e == elem_pattern);
        case se_svg :
            switch (e)
            {   case elem_a :
                case elem_font :
                case elem_image :
                case elem_script :
                case elem_style :
                case elem_text :
                case elem_title :
                    return true;
                default : break; }
            return (first_version (e).svg_version () != sv_none);
        default : break; }
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }
