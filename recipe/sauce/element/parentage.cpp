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
#include "element/parentage.h"
#include "main/context.h"

struct parentage
{   html_version first_, last_;
    e_element parent_;
    e_element child_;
    flags_t flags_, categories_;
    parentage (const html_version& first, const html_version& last, const e_element parent, const e_element child, const flags_t flags = 0, const flags_t categories = 0) noexcept
        : first_ (first), last_ (last), parent_ (parent), child_ (child), flags_ (flags), categories_ (categories) { } };

inline bool operator == (const parentage& lhs, const parentage& rhs) noexcept
{   return (lhs.child_ == rhs.child_) && (lhs.parent_ == rhs.parent_) && (lhs.first_ == rhs.first_) && (lhs.last_ == rhs.last_); }

inline bool operator != (const parentage& lhs, const parentage& rhs) noexcept
{   return ! (lhs == rhs); }

inline bool operator < (const parentage& lhs, const parentage& rhs) noexcept
{   if (lhs.parent_ < rhs.parent_) return true;
    if (lhs.parent_ > rhs.parent_) return false;
    return (lhs.child_ < rhs.child_); }

inline bool operator <= (const parentage& lhs, const parentage& rhs) noexcept
{   if (lhs < rhs) return true;
    return (lhs == rhs); }

inline bool operator > (const parentage& lhs, const parentage& rhs) noexcept
{   return ! (lhs <= rhs); }

inline bool operator >= (const parentage& lhs, const parentage& rhs) noexcept
{   return ! (lhs < rhs); }

inline flags_t parent_key (const e_element parent, const e_element child) noexcept
{   return (static_cast <flags_t> (parent) << 32) + static_cast <flags_t> (child); }

parentage parent_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_a, elem_em },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, elem_embed },
    { { HTML_1_0 }, { HTML_PLUS }, elem_a, elem_img },
    { { HTML_TAGS }, { HTML_2_0 }, elem_a, elem_a, DENY },
    { { XHTML_1_0 }, { XHTML_2_0 }, elem_a, elem_a, DENY },
    { { HTML_2_0 }, { HTML_2_0 }, elem_a, elem_undefined, 0, EF_HEAD | EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_a, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_a, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_a, elem_undefined, 0, EF_4_INLINE | EF_S_G },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_a, elem_undefined, 0, EF_X2_TEXT | EF_S_G },
    { { HTML_JAN16 }, { HTML_UNDEF }, elem_a, elem_a, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, elem_undefined, DENY, EF_5_INTERACTIVE },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_a, elem_a, DENY },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_a, elem_altglyphdef },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_a, elem_foreignobject },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_a, elem_iframe },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_a, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { HTML_SVG12, 0, HE_SVG_12 }, { XHTML_2_0 }, elem_a, elem_undefined, EP_5_TRANSPARENT },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_abbr, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_abbr, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_abbr, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_abbrev, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_abbrev, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_above, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_PLUS }, { HTML_PLUS }, elem_abstract, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_abstract, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_acronym, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_acronym, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_acronym, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_action },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_dispatchevent },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_addeventlistener },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_removeeventlistener },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_stoppropagation },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, elem_preventdefault },
    { { HTML_PLUS }, { HTML_PLUS }, elem_added, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_address, elem_address, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_address, elem_footer, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_address, elem_header, DENY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_address, elem_img },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_address, elem_main, DENY },
    { { HTML_1_0 }, { XHTML_2_0 }, elem_address, elem_p },
    { { HTML_1_0 }, { HTML_PLUS }, elem_address, elem_undefined, 0, EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_address, elem_undefined, 0, EF_TEXT | EF_MISC },
    { { HTML_2_0 }, { HTML_2_0 }, elem_address, elem_undefined, 0, EF_PHRASE | EF_FONT | EF_TEXT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_address, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_address, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_address, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_address, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_address, elem_undefined, 0, EF_HEAD | EF_5_SECTION | DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_address, elem_undefined, 0, EF_5_FLOW },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_altglyph, elem_undefined },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyphdef, elem_glyphref },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyphdef, elem_altglyphitem },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyphitem, elem_glyphref },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, elem_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animate, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animate, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animate, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animate, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatecolour, elem_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatecolour, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_animatecolour, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatemotion, elem_handler },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, elem_mpath },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animatemotion, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatemotion, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatetransform, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animatetransform, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animatetransform, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatetransform, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_annotation_xml, elem_undefined },
    { { HTML_3_2 }, { HTML_JUN22 }, elem_applet, elem_param },
    { { HTML_3_2 }, { HTML_3_2 }, elem_applet, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_applet, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_applet, elem_undefined },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_apply, elem_degree },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_apply, elem_logbase },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_apply, elem_momentabout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_apply, elem_undefined, 0, EF_M_DQ },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_apply, elem_undefined, 0, EF_M_CONTENTEXPR  },
    { { HTML_PLUS }, { HTML_PLUS }, elem_arg, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_array },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_item },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, elem_row },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_sub },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_sup },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_article, elem_main, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_article, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JUL13 }, { HTML_JUN18 }, elem_aside, elem_main, DENY },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_aside, elem_undefined, 0, EF_5_FLOW },
    { { HTML_3_0 }, { HTML_3_0 }, elem_au, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_handler },
    { { HTML_JUL10, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_track },
    { { HTML_JUL07, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_source },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_PLUS }, { HTML_PLUS }, elem_b, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_b, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_b, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_b, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_b, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_b, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_JUL08 }, { HTML_DEC09 }, elem_bb, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_banner, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_bdi, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_bdo, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_bdo, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_below, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_big, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_big, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_big, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_bind, elem_degree },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_bind, elem_logbase },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_bind, elem_momentabout },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_bind, elem_undefined, 0, EF_M_DQ },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_bind, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, elem_credit },
    { { HTML_1_0 }, { HTML_1_0 }, elem_blockquote, elem_img },
    { { HTML_1_0 }, { HTML_2_0 }, elem_blockquote, elem_p },
    { { HTML_1_0 }, { HTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_EMPH },
    { { HTML_PLUS }, { HTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_TEXT | EF_MISC },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_blockquote, elem_undefined, 0, EF_32_BLOCK },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_blockquote, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_X2_FLOWLIST },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_blockquote, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_blockcode, elem_undefined, 0, EF_X2_FLOWLIST },
    { { HTML_1_0 }, { HTML_1_0 }, elem_body, elem_a },
    { { HTML_2_0, HV_NOT30 }, { HTML_3_2 }, elem_body, elem_address },
    { { HTML_3_0 }, { HTML_3_0 }, elem_body, elem_banner },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_body, elem_del },
    { { HTML_2_0 }, { HTML_2_0 }, elem_body, elem_dl },
    { { HTML_1_0 }, { HTML_PLUS }, elem_body, elem_faux_char },
    { { HTML_1_0 }, { HTML_PLUS }, elem_body, elem_faux_code },
    { { HTML_1_0 }, { HTML_PLUS }, elem_body, elem_faux_text },
    { { HTML_2_0 }, { HTML_2_0 }, elem_body, elem_hr },
    { { HTML_1_0 }, { HTML_1_0 }, elem_body, elem_img },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_body, elem_ins },
    { { XHTML_1_0 }, { XHTML_2_0 }, elem_body, elem_math },
    { { HTML_2_0 }, { HTML_2_0 }, elem_body, elem_p },
    { { HTML_3_0 }, { HTML_3_0 }, elem_body, elem_spot },
    { { HTML_1_0 }, { HTML_1_0 }, elem_body, elem_undefined, 0, EF_EMPH | EF_HEAD | EF_PRE | EF_BODY | EF_LL },
    { { HTML_PLUS }, { HTML_PLUS }, elem_body, elem_undefined, 0, EF_HEAD | EF_BLOK | EF_LIST | EF_PARA | EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_body, elem_undefined, 0, EF_HEAD | EF_TEXT | EF_PHRASE | EF_FONT | EF_BLOK | EF_BODY | EF_LIT | EF_LIST },
    { { HTML_3_0 }, { HTML_3_0 }, elem_body, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_body, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_body, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_body, elem_undefined, 0, EF_X2_STRUCT | EF_HEAD | EF_X2_LIST | EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_body, elem_undefined, 0, EF_5_FLOW },
    { { HTML_3_0 }, { HTML_3_0 }, elem_box, elem_atop },
    { { HTML_3_0 }, { HTML_3_0 }, elem_box, elem_choose },
    { { HTML_3_0 }, { HTML_3_0 }, elem_box, elem_left },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_box, elem_over },
    { { HTML_3_0 }, { HTML_3_0 }, elem_box, elem_right },
    { { HTML_PLUS }, { HTML_PLUS }, elem_box, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_box, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, elem_form },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, elem_credit },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bt, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, elem_a, DENY },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_button, elem_button, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, elem_fieldset, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, elem_form, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, elem_iframe, DENY },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_button, elem_input, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, elem_isindex, DENY },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_button, elem_label, DENY },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_button, elem_select, DENY },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_button, elem_textarea, DENY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_button, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_bvar, elem_ci },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_bvar, elem_degree },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_bvar, elem_semantics },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_bvar, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_PLUS }, { HTML_PLUS }, elem_byline, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_byline, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_card, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_calendar, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS }, { HTML_PLUS }, elem_caption, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_caption, elem_undefined, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_caption, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_caption, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_caption, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_caption, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_caption, elem_table, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_caption, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, elem_undefined },
    { { HTML_3_2 }, { HTML_UNDEF }, elem_centre, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_centre, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_cerror, elem_csymbol },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_cerror, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_ci, elem_mglyph },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ci, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_circle, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_circle, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_circle, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_circle, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_cite, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_cite, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_cite, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_cite, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_cite, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_cite, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_cite, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_clippath, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, elem_use },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM | EF_SVG_SHAPE },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_ci, elem_mglyph },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_ci, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_cn, elem_mglyph },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_cn, elem_sep },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_cn, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_cmd, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_code, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_code, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_code, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_code, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_code, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_code, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_code, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_colgroup, elem_col },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_colgroup, elem_template },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_JUL05 }, { HTML_DEC05 }, elem_commandset, elem_command },
    { { HTML_JUL05 }, { HTML_DEC05 }, elem_commandset, elem_commandset },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_condition, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_condition, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_cursor, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_3_0 }, { HTML_3_0 }, elem_credit, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_custom, elem_undefined },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_csymbol, elem_mglyph },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_csymbol, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_data, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_JUL05 }, { HTML_DEC09 }, elem_datagrid, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_datalist, elem_option },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_datalist, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_JAN15 }, { HTML_UNDEF }, elem_datalist, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_datatemplate, elem_rule },
    { { HTML_PLUS }, { HTML_2_0 }, elem_dd, elem_p },
    { { HTML_PLUS }, { HTML_2_0 }, elem_dd, elem_dl },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dd, elem_ol },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dd, elem_ul },
    { { HTML_2_0 }, { HTML_2_0 }, elem_dd, elem_undefined, 0, EF_LIST | EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dd, elem_undefined, 0, EF_3_FLOW },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dd, elem_undefined, 0, EF_32_FLOW },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dd, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dd, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dd, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_defs, elem_xa },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_defs, elem_altglyphdef },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_animation },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_SVG20 }, elem_defs, elem_audio },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_SVG20 }, elem_defs, elem_canvas },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_defs, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_defs, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_defs },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_defs, elem_font },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_defs, elem_font_face },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_defs, elem_foreignobject, DENY },
    { { HTML_SVG11, 0, HE_SVG_11_12_2 }, { HTML_UNDEF }, elem_defs, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_12 }, { HTML_UNDEF }, elem_defs, elem_g },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_handler },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_defs, elem_iframe },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_listener },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_mask },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_prefetch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_solidcolour },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_style },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_switch },
    { { HTML_SVG20, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_svg },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_text },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_defs, elem_textarea },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_SVG20 }, elem_defs, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_defs, elem_view },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_degree, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_del, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_del, elem_undefined, 0, EF_4_FLOW },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_desc, elem_undefined },
    { { HTML_JAN10 }, { HTML_JUN10 }, elem_details, elem_dt },
    { { HTML_JAN10 }, { HTML_JUN10 }, elem_details, elem_dd },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_details, elem_summary },
    { { HTML_JUL07 }, { HTML_DEC09 }, elem_details, elem_legend },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_details, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_dfn, elem_dfn, DENY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dfn, elem_undefined, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dfn, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dfn, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dfn, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dfn, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dfn, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dfn, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_di, elem_dd },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_di, elem_dt },
    { { HTML_JAN07 }, { HTML_DEC09 }, elem_dialogue, elem_dd },
    { { HTML_JAN07 }, { HTML_DEC09 }, elem_dialogue, elem_dt },
    { { HTML_JUL12 }, { HTML_UNDEF }, elem_dialogue, elem_undefined, 0, EF_5_FLOW },
    { { HTML_TAGS }, { HTML_1_0 }, elem_dir, elem_a },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dir, elem_img },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dir, elem_undefined, 0, EF_EMPH },
    { { HTML_TAGS, HV_NOTPLUS }, { HTML_UNDEF }, elem_dir, elem_li },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_discard, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_discard, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_discard, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, elem_discard, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_div, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_div, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_div, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_div, elem_dt },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_div, elem_dd },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_div, elem_undefined, 0, EF_5_FLOW },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_a },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_caption },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_dl, elem_dd },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_di },
    { { HTML_JAN17 }, { HTML_UNDEF }, elem_dl, elem_div },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_dl, elem_dt },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_img },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dl, elem_lh },
    { { HTML_1_0 }, { HTML_PLUS }, elem_dl, elem_p },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_title },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_undefined, 0, EF_EMPH },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_dl, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_domainofapplication, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dt, elem_footer, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dt, elem_header, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dt, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dt, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dt, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dt, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JUL12 }, { HTML_JUN13 }, elem_dt, elem_dialogue },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dt, elem_undefined, DENY, EF_HEAD | EF_5_SECTION },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dt, elem_undefined, 0, EF_5_FLOW },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_defs },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_prototype },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_traitdef },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_transformer },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_elementdef, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_ellipse, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_ellipse, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_ellipse, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_ellipse, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_em, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_em, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_em, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_em, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_em, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_em, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_em, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_elementdef },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_defs },
    { { HTML_1_0, HV_NOTPLUS }, { HTML_UNDEF }, elem_faux_document, elem_html },
    { { HTML_RDF10 }, { HTML_UNDEF }, elem_faux_document, elem_rdf_rdf },
    { { HTML_SVG10 }, { HTML_UNDEF }, elem_faux_document, elem_svg },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_faux_document, elem_math },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_faux_document, elem_faux_xml },
    { { HTML_PLUS }, { HTML_PLUS }, elem_faux_document, elem_htmlplus },
    { { HTML_TAGS }, { HTML_TAGS }, elem_faux_document, elem_undefined },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feblend, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feblend, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feblend, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feblend, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefunca },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncb },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncg },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncr },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecomposite, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fecomposite, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fecomposite, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fediffuselighting, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fediffuselighting, elem_animatecolour },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fedistantlight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fepointlight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fespotlight },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fediffuselighting, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fediffuselighting, elem_set },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_fediffuselighting, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedistantlight, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedistantlight, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedistantlight, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedistantlight, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fedropshadow, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feflood, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_feflood, elem_animatecolour },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feflood, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feflood, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feflood, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefunca, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefunca, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefunca, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefunca, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncb, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncb, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncb, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncb, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncg, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncg, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncg, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncg, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncr, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncr, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fefuncr, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fefuncr, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fegaussianblur, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fegaussianblur, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fegaussianblur, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fegaussianblur, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feimage, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feimage, elem_animatetransform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feimage, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feimage, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feimage, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femerge, elem_femergenode },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femerge, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femerge, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femergenode, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femergenode, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femergenode, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femergenode, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femorphology, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femorphology, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_femorphology, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_femorphology, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feoffset, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feoffset, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feoffset, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feoffset, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fepointlight, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fepointlight, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fepointlight, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fepointlight, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fespecularlighting, elem_animatecolour },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fespecularlighting, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fedistantlight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fepointlight },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fespotlight },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fespecularlighting, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_fespecularlighting, elem_set },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_fespecularlighting, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fespotlight, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fespotlight, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fespotlight, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fetile, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fetile, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_fetile, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_fetile, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feturbulence, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_feturbulence, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_feturbulence, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_fieldset, elem_legend },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_fieldset, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_fieldset, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_fig, elem_caption },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_credit },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_fig, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_img, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_overlay },
    { { HTML_PLUS }, { HTML_PLUS }, elem_fig, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_figcaption, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN10 }, { HTML_JUN10 }, elem_figure, elem_dd },
    { { HTML_JAN10 }, { HTML_JUN10 }, elem_figure, elem_dt },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_figure, elem_figcaption },
    { { HTML_JUL07 }, { HTML_DEC09 }, elem_figure, elem_legend },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_figure, elem_undefined, 0, EF_5_FLOW },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_filter, elem_animate },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_filter, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_filter, elem_set },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_filter, elem_undefined, 0, EF_SVG_FILTER | EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowdiv, elem_flowpara },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowdiv, elem_flowregionbreak },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, elem_g },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, elem_image },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowimage, elem_undefined, 0, EF_SVG_SHAPE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowimage },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowline },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowregionbreak },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowspan },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowimage },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowline },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowregionbreak },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowspan },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowtref },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowregion, elem_flowregionexclude },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowregion, elem_use },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowregion, elem_undefined, 0, EF_SVG_SHAPE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowregionexclude, elem_use },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowregionexclude, elem_undefined, 0, EF_SVG_SHAPE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowdiv },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowref },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowregion },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowregionexclude },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowimage },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowline },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowregionbreak },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowspan },
    { { HTML_3_0, HV_NOT4 }, { HTML_UNDEF }, elem_fn, elem_undefined, 0, EF_3_BODYIN | EF_M_CONTENTEXPR },
    { { HTML_3_2 }, { HTML_3_2 }, elem_font, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_font, elem_undefined, 0, EF_4_INLINE },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_font_face },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_glyph },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_hkern },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_missingglyph },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_vkern },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_font, elem_undefined },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_font_face, elem_definition_src },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face, elem_font_face_src },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_src, elem_font_face_name },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_font_face_src, elem_font_face_uri },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_src, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_src, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_font_face_uri, elem_font_face_format },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_uri, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_font_face_uri, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_footer, elem_footer, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_footer, elem_header, DENY },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_footer, elem_main, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_footer, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_footnote, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_margin, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_foreignobject, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_foreignobject, elem_svg },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_foreignobject, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_foreignobject, elem_undefined }, // the SVG 1.2 examples contradict the element appendix
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_2 }, elem_form, elem_form, DENY },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_form, elem_form, DENY },
    { { HTML_2_0 }, { HTML_3_2 }, elem_form, elem_input },
    { { HTML_PLUS }, { HTML_PLUS }, elem_form, elem_mh },
    { { HTML_2_0 }, { HTML_3_2 }, elem_form, elem_select },
    { { HTML_2_0 }, { HTML_3_0 }, elem_form, elem_textarea },
    { { HTML_PLUS }, { HTML_PLUS }, elem_form, elem_undefined, 0, EF_HEAD | EF_BLOK | EF_LIST | EF_PARA | EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_form, elem_undefined, 0, EF_HEAD | EF_TEXT | EF_PHRASE | EF_FONT | EF_BLOK | EF_BODY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_form, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_form, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_form, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_form, elem_undefined, 0, EF_5_FLOW },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_frame },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_frameset },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_noframes },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_g, elem_xa },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, elem_altglyphdef },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_animation },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_SVG20 }, elem_g, elem_audio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_g, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_defs },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_discard },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11_12_2 }, { HTML_UNDEF }, elem_g, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_g, elem_g },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_handler },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_g, elem_iframe },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_listener },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_mask },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_prefetch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_solidcolour },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_style },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_switch },
    { { HTML_SVG20, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_svg },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_text },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, elem_textarea },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_SVG20 }, elem_g, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_g, elem_view },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_altglyph },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_glyph, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_style },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_glyph, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_glyphref, elem_glyphref },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyphref, elem_altglyphitem },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_h, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h1, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h1, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h1, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h1, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h1, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h1, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h2, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h2, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h2, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h2, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h2, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h2, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h3, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h3, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h3, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h3, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h3, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h3, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h4, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h4, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h4, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h4, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h4, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h4, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h5, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h5, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h5, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h5, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h5, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h5, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h6, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h6, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h6, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h6, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h6, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h6, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h6, elem_undefined, 0, EF_4_INLINE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_head, elem_action },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_head, elem_listener },
    { { HTML_3_0 }, { HTML_3_0 }, elem_head, elem_range },
    { { HTML_JAN05 }, { HTML_OCT07 }, elem_head, elem_noscript, DENY },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_head, elem_undefined, 0, EF_METADATA },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_header, elem_footer, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_header, elem_header, DENY },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_header, elem_main, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_header, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h1 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h2 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h3 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h4 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h5 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_h6 },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, elem_script },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_hgroup, elem_template },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_hkern, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_hkern, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp1, elem_undefined },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp2, elem_undefined },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp3, elem_undefined },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp4, elem_undefined },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp5, elem_undefined },
    { { HTML_TAGS }, { HTML_TAGS }, elem_hp6, elem_undefined },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_html, elem_body },
    { { HTML_4_0 }, { HTML_4_01 }, elem_html, elem_frameset },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_html, elem_head },
    { { HTML_TAGS }, { HTML_TAGS }, elem_html, elem_undefined, 0, EF_BODY | EF_METADATA },
    { { HTML_1_0 }, { HTML_1_0 }, elem_html, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, elem_body },
    { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, elem_head },
    { { HTML_1_0 }, { HTML_1_0 }, elem_i, elem_undefined, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_i, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_i, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_i, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_i, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_i, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_i, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_iframe, elem_script, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_iframe, elem_undefined, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_image, elem_a },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_image, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_image, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_image, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_image, elem_switch },
    { { HTML_PLUS }, { HTML_PLUS }, elem_image, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_image, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_img, elem_caption },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_img, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ins, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_ins, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_interval, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_item, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_PLUS }, { HTML_PLUS }, elem_kbd, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_kbd, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_kbd, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_kbd, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_kbd, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_kbd, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_kbd, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_lambda, elem_undefined, 0, EF_M_DQ },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_lambda, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_lang, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_PLUS }, { HTML_PLUS }, elem_l, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_label, elem_label, DENY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_label, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_label, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_legend, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_legend, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_2, HV_W3 }, { HTML_5_3 }, elem_legend, elem_undefined, 0, EF_HEAD },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_legend, elem_undefined, 0, EF_HEAD },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_l, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_PLUS }, { HTML_2_0 }, elem_li, elem_dl },
    { { HTML_PLUS }, { HTML_2_0 }, elem_li, elem_p },
    { { HTML_TAGS }, { HTML_1_0 }, elem_li, elem_undefined, EP_UNCLOSED12 },
    { { HTML_PLUS }, { HTML_PLUS }, elem_li, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_li, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT | EF_LIST | EF_BLOK },
    { { HTML_3_0 }, { HTML_3_0 }, elem_li, elem_undefined, 0, EF_3_FLOW },
    { { HTML_3_2 }, { HTML_3_2 }, elem_li, elem_undefined, 0, EF_32_FLOW },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_li, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_li, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_li, elem_undefined, 0, EF_5_FLOW },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_line, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_line, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_line, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_line, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_line, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_lineargradient, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_lineargradient, elem_animatetransform },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_lineargradient, elem_discard },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_lineargradient, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_lineargradient, elem_set },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, elem_stop },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_lineargradient, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_lineargradient, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_lineargradient, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_lineargradient, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_list, elem_undefined, 0, EF_M_DQ },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_list, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_listing, elem_undefined },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_listing, elem_form },
    { { HTML_PLUS }, { HTML_PLUS }, elem_lit, elem_tab },
    { { HTML_PLUS }, { HTML_PLUS }, elem_lit, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_loc, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_loc, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_lowlimit, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_logbase, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_JUL05 }, { HTML_JUN08 }, elem_mark, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_maction, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_main, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_map, elem_area },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_map, elem_undefined, 0, EF_4_BLOCK },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_footnote },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_margin },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_mark, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_a },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_marker, elem_audio },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_marker, elem_altglyphdef },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_marker, elem_canvas },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_clippath },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_marker, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_marker, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_marker, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_marker, elem_foreignobject },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_marker, elem_iframe },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_marker, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_marker, elem_symbol },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_text },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_marker, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_marker, elem_view },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_marker, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_mask, elem_altglyphdef },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_mask, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_mask, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_mask, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_mask, elem_font_face },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_switch},
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_mask, elem_symbol },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_mask, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_atop },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_choose },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_left },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_over },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_right },
    { { HTML_PLUS }, { HTML_PLUS }, elem_math, elem_undefined, 0, EF_MATH | EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_math, elem_declare },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_math, elem_undefined, 0, EF_M_MATH },
    { { HTML_JUL22, 0, 0, H2_MATH_4_22 }, { HTML_UNDEF }, elem_math, elem_undefined, 0, EF_M_MATH | EF_M_CONTENTEXPR  },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_matrix, elem_undefined, 0, EF_M_DQ },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_matrix, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_matrixrow, elem_undefined, 0, EF_M_DQ },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_matrixrow, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_menclose, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_TAGS }, { HTML_1_0 }, elem_menu, elem_a },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menu, elem_hr },
    { { HTML_1_0 }, { HTML_1_0 }, elem_menu, elem_img },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_menu, elem_li },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menu, elem_menu },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menu, elem_menuitem },
    { { HTML_1_0 }, { HTML_1_0 }, elem_menu, elem_undefined, 0, EF_EMPH },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_menu, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JUL13, HV_NOT50 }, { HTML_JUN17 }, elem_menu, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_a },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_button },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_command },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_commandset },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_hr },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_input },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_li },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_menu },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_menulabel },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_option },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menubar, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menulabel, elem_li },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_menulabel, elem_undefined, 0, EF_5_FLOW },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_merror, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_metadata, elem_undefined },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, elem_meter, DENY },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_meter, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mfenced, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mfrac, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mi, elem_malignmark },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mi, elem_mglyph },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_altglyph },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_missingglyph, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_style },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_missingglyph, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_missingglyph, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_missingglyph, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlabeledtr, elem_mtd },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mlabeledtr, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mlongdiv, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_C }, { HTML_UNDEF }, elem_mmultiscripts, elem_none },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mmultiscripts, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mn, elem_malignmark },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_mn, elem_mglyph },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mo, elem_malignmark },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_mo, elem_mglyph },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_momentabout, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mover, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mpadded, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_mpath, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_mpath, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_mpath, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mphantom, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mroot, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mrow, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_ms, elem_malignmark },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_ms, elem_mglyph },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, elem_mscarry },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarry, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msgroup, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msqrt, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msrow, elem_none },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msrow, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, elem_mscarries },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, elem_msgroup },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, elem_msline },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, elem_msrow },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mstyle, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msub, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msubsup, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_msup, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mtable, elem_mlabeledtr },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_C }, { HTML_UNDEF }, elem_mtable, elem_mtr },
    { { HTML_MATH4_C, 0, 0, H2_MATH_C }, { HTML_UNDEF }, elem_mtable, elem_mtd },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mtable, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mtext, elem_malignmark },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_mtext, elem_mglyph },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_C }, { HTML_UNDEF }, elem_mtext, elem_undefined },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_C }, { HTML_UNDEF }, elem_mtr, elem_mtd },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mtr, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munder, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_nav, elem_main, DENY },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_nav, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JAN05 }, { HTML_JUN05 }, elem_navigation, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_caption },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_title },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_li },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noembed, elem_undefined },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noframes, elem_body },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noframes, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noframes, elem_undefined },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noscript, elem_undefined, 0, EF_4_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noscript, elem_link },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noscript, elem_style },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noscript, elem_meta },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_noscript, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_note, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_note, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_note, elem_undefined, 0, EF_3_BODYIN },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_object, elem_caption },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, elem_param },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_object, elem_standby },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_object, elem_title },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_object, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_object, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_1_0 }, { HTML_1_0 }, elem_ol, elem_a },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_ol, elem_caption },
    { { HTML_1_0 }, { HTML_1_0 }, elem_ol, elem_img },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_ol, elem_li },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, elem_lh },
    { { HTML_1_0 }, { HTML_PLUS }, elem_ol, elem_p },
    { { HTML_PLUS }, { HTML_2_0 }, elem_ol, elem_ol },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, elem_script },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_ol, elem_template },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_ol, elem_title },
    { { HTML_PLUS }, { HTML_2_0 }, elem_ol, elem_ul },
    { { HTML_1_0 }, { HTML_1_0 }, elem_ol, elem_undefined, 0, EF_EMPH },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_ol, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_online, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_optgroup, elem_option },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_optgroup, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_otherwise, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_output, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_p, elem_blockcode },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_p, elem_blockquote },
    { { HTML_2_0 }, { HTML_3_0 }, elem_p, elem_form },
    { { HTML_PLUS }, { HTML_PLUS }, elem_p, elem_l },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_p, elem_pre },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_p, elem_table },
    { { HTML_TAGS }, { HTML_1_0 }, elem_p, elem_undefined, EP_UNCLOSED1T },
    { { HTML_PLUS }, { HTML_PLUS }, elem_p, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_p, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_p, elem_undefined, 0, EF_3_LIST | EF_3_TEXTIN | EF_3_BQ },
    { { HTML_3_2 }, { HTML_3_2 }, elem_p, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_p, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_p, elem_undefined, 0, EF_X2_TEXT | EF_X2_LIST },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_p, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_page, elem_undefined, 0, EF_SVG_GRAPH },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_pageset, elem_page },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_pattern, elem_altglyphdef },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_pattern, elem_audio },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_pattern, elem_canvas },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_pattern, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_pattern, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_pattern, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_pattern, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_pattern, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_pattern, elem_pattern },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_text },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_pattern, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_view },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_pattern, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_path, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_path, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_path, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_path, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_path, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_person, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_person, elem_undefined, 0, EF_3_TEXTIN },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_piece, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_piecewise, elem_otherwise },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_piecewise, elem_piece },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_picture, elem_source },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_picture, elem_img },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_picture, elem_script },
    { { HTML_JUL14, HV_NOT50 }, { HTML_UNDEF }, elem_picture, elem_template },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_plaintext, elem_undefined },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polyline, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polyline, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polyline, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_polyline, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polyline, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polygon, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polygon, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_polygon, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_polygon, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_polygon, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_1_0 }, { HTML_2_0 }, elem_pre, elem_a },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_pre, elem_applet, DENY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_pre, elem_basefont, DENY },
    { { HTML_3_0 }, { XHTML_2_0 }, elem_pre, elem_big, DENY },
    { { HTML_2_0 }, { HTML_2_0 }, elem_pre, elem_br },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_pre, elem_font, DENY },
    { { HTML_2_0 }, { HTML_2_0 }, elem_pre, elem_form },
    { { HTML_2_0 }, { HTML_2_0 }, elem_pre, elem_hr },
    { { HTML_1_0 }, { HTML_PLUS }, elem_pre, elem_p },
    { { HTML_3_0 }, { XHTML_2_0 }, elem_pre, elem_img, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_pre, elem_math, DENY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_pre, elem_object, DENY },
    { { HTML_3_0 }, { XHTML_2_0 }, elem_pre, elem_small, DENY },
    { { HTML_3_0 }, { XHTML_2_0 }, elem_pre, elem_sub, DENY },
    { { HTML_3_0 }, { XHTML_2_0 }, elem_pre, elem_sup, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_pre, elem_tab },
    { { HTML_3_0 }, { HTML_3_0 }, elem_pre, elem_tab, DENY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_pre, elem_undefined, 0, EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_pre, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_pre, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_pre, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_pre, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_pre, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_prefetch, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_PLUS }, { HTML_PLUS }, elem_printed, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, elem_progress, DENY },
    { { HTML_JUL06 }, { HTML_UNDEF }, elem_progress, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_prototype, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_q, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_2 }, elem_q, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_q, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_q, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_q, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_quote, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_quote, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_radialgradient, elem_stop, 0 },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rb, elem_ruby, DENY },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rb, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rb, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rbc, elem_rb },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, elem_animatetransform },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_radialgradient, elem_discard },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_radialgradient, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, elem_set },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, elem_stop },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_radialgradient, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_radialgradient, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_radialgradient, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_radialgradient, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_1, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_2, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_3, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_4, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_5, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_6, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_7, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_8, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_9, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_about, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_abouteach, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_abouteachprefix, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_alt, elem_undefined, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_bag, elem_undefined, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_bagid, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_datatype, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_description, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_id, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_li, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_nodeid, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_parsetype, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_rdf, elem_undefined, 0, EF_RDF },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_resource, elem_undefined },
    { { HTML_RDF10, 0, HE_RDF }, { HTML_UNDEF }, elem_rdf_seq, elem_undefined, 0, EF_RDF },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_rect, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_rect, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_rect, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_rect, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_rect, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_refcontent, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_reln, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_PLUS }, { HTML_PLUS }, elem_removed, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_root, elem_of },
    { { HTML_3_0 }, { HTML_3_0 }, elem_root, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_row, elem_item },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rp, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rp, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rt, elem_ruby, DENY },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rt, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rt, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rtc, elem_rp },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_rtc, elem_rp },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_rtc, elem_rt },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rtc, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1, HV_W3 }, { HTML_UNDEF }, elem_ruby, elem_rb },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_ruby, elem_rbc },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_ruby, elem_rp },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_ruby, elem_rt },
    { { XHTML_1_1, HV_W3 }, { HTML_UNDEF }, elem_ruby, elem_rtc },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_ruby, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_rule, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_s, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_s, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_s, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_s, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_samp, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_samp, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_samp, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_samp, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_samp, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_samp, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_samp, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_script, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_section, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0 }, { HTML_2_0 }, elem_select, elem_input, DENY },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_select, elem_option },
    { { HTML_2_0 }, { HTML_2_0 }, elem_select, elem_textarea, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_select, elem_optgroup },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_select, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_semantics, elem_annotation },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_semantics, elem_annotation_xml },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_semantics, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_set, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_set, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_set, elem_switch },
    { { HTML_5_2, 0, HE_NOT_SVG }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_M_DQ },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_NOT_SVG }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_JAN05 }, { HTML_JUN05 }, elem_sidebar, elem_undefined, 0, EF_5_FLOW },
    { { HTML_3_0 }, { HTML_3_0 }, elem_small, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_small, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_small, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_small, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_solidcolour, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_solidcolour, elem_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_solidcolour, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_span, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_span, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_span, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sqrt, elem_undefined, 0, EF_3_MATHIN },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_standby, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_stop, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_stop, elem_animatecolour },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_stop, elem_switch },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_stop, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_stop, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_stop, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_stop, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_2_0 }, { HTML_2_0 }, elem_strike, elem_undefined },
    { { HTML_3_2 }, { HTML_3_2 }, elem_strike, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_strike, elem_undefined, 0, EF_4_INLINE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_strong, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_strong, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_strong, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_strong, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_strong, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_strong, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_strong, elem_undefined, 0, EF_5_PHRASE },
    // style is a special case handled in code (dratted CSS)
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_summary, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JUL10, HV_NOT50 }, { HTML_UNDEF }, elem_summary, elem_undefined, 0, EF_HEAD | EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, elem_text },
    { { HTML_PLUS }, { HTML_PLUS }, elem_sub, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_sub, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_sub, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_sub, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_sub, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, elem_text },
    { { HTML_PLUS }, { HTML_PLUS }, elem_sup, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_sup, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_sup, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_sup, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_sup, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_svg, elem_xa },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_svg, elem_altglyphdef },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_animation },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_UNDEF }, elem_svg, elem_audio },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, elem_base },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_svg, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_svg, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_defs },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_svg, elem_extensiondefs },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, elem_font },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_svg, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11_12_2 }, { HTML_UNDEF }, elem_svg, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_g },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_handler },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_svg, elem_iframe },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, elem_link },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_listener },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_svg, elem_meta },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_prefetch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_script },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_solidcolour },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_style },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_switch },
    { { HTML_SVG20, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_svg },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_text },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_svg, elem_textarea },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_svg, elem_view },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_UNDEF }, elem_svg, elem_video },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_svg, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_switch, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_UNDEF }, elem_switch, elem_audio },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_switch, elem_canvas },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_switch, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_switch, elem_g },
    { { HTML_SVG20, 0, HE_SVG_20 }, { HTML_UNDEF }, elem_switch, elem_iframe },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_switch, elem_image },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_switch, elem_svg },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_switch, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_switch, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_switch, elem_use },
    { { HTML_SVG12, 0, HE_SVG_12_20 }, { HTML_UNDEF }, elem_switch, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_switch, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_switch, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_SHAPE },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_switch, elem_undefined },
    { { HTML_SVG20 }, { HTML_DEC06 }, elem_switch, elem_undefined, 0, EF_5_SECTION },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, elem_altglyphdef },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_symbol, elem_audio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_clippath },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, elem_colour_profile },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, elem_symbol, elem_cursor },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_defs },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_filter },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, elem_font },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_symbol, elem_font_face },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_symbol, elem_foreignobject },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_g },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, elem_symbol, elem_iframe },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_marker },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_mask },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_switch },
    { { HTML_SVG20, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_svg },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_text },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_view },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_symbol, elem_video },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_symbol, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_t, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_JUL06 }, { HTML_DEC06 }, elem_t, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_tabbox, elem_a },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_tabbox, elem_fieldset },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_tabbox, elem_section },
    { { HTML_JAN05 }, { HTML_DEC06 }, elem_tabbox, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_table, elem_caption },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_table, elem_colgroup },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_table, elem_col },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_table, elem_summary },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_table, elem_tbody },
    { { HTML_PLUS }, { HTML_PLUS }, elem_table, elem_td },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_table, elem_tfoot },
    { { HTML_PLUS }, { HTML_PLUS }, elem_table, elem_th },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_table, elem_thead },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_table, elem_title },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_2 }, elem_table, elem_tr },
    { { XHTML_2_0 }, { HTML_UNDEF }, elem_table, elem_tr },
    { { HTML_PLUS }, { HTML_PLUS }, elem_table, elem_undefined, 0, EF_HEAD | EF_HEAD | EF_TEXT | EF_LIST | EF_EMPH | EF_MISC },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_table, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tbody, elem_tr },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_tbody, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_td, elem_p },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_td, elem_td, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_td, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH | EF_HEAD | EF_LIST },
    { { HTML_2_0 }, { HTML_2_0 }, elem_td, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_td, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_td, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_td, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_td, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_td, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_col },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_figcaption },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_legend },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_li },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_option },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_optgroup },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_param },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_rb },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_rp },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_rt },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_rtc },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_source },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_track },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_colgroup },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_tbody },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_tfoot },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_thead },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_tr },
    { { HTML_JUL13 }, { HTML_DEC16 }, elem_template, elem_undefined, 0, EF_METADATA | EF_5_FLOW | EF_5_SCRIPT },
    { { HTML_JAN17 }, { HTML_UNDEF }, elem_template, elem_undefined },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_text, elem_a },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_text, elem_xa },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, elem_handler },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, elem_switch },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_text, elem_text, DENY },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_text, elem_tspan },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_TEXT },
    { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_TEXT | EF_SVG_PSGRAD },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, elem_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, elem_tspan },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, elem_switch },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_textarea, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10 | HE_SVG_11 }, { HTML_UNDEF }, elem_textpath, elem_tspan },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_textpath, elem_altglyph },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_textpath, elem_animatecolour },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_clippath },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_marker },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_textpath, elem_tref },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, elem_tspan },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_textpath, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_textpath, elem_undefined, 0, EF_SVG_PSGRAD },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tfoot, elem_tr },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_tfoot, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_th, elem_footer, DENY },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_th, elem_header, DENY },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_th, elem_th, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH | EF_HEAD | EF_LIST },
    { { HTML_2_0 }, { HTML_2_0 }, elem_th, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_th, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_th, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_th, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_th, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_JUL12 }, { HTML_JUN13 }, elem_th, elem_dialogue },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_th, elem_undefined, DENY, EF_HEAD | EF_5_SECTION },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_th, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_thead, elem_tr },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_thead, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_time, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_title, elem_undefined, 0, EF_EMPH },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, elem_title, elem_undefined },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_title, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_tr, DENY },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_td },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_th },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_tr, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_JUN22 }, elem_transformer, elem_param },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_transformer, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, elem_animatecolour },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, elem_set },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tref, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_tspan, elem_a },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tspan, elem_altglyph },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, elem_animate },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tspan, elem_animatecolour },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, elem_script },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, elem_set },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_tspan, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tspan, elem_tref },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_tspan, elem_tspan },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_tspan, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_tspan, elem_undefined }, // transparent
    { { HTML_SVG20, 0, HE_SVG_2  }, { HTML_UNDEF }, elem_tspan, elem_undefined, 0, EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_tt, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_tt, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tt, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_tt, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_tt, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_tt, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_u, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_u, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_u, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_u, elem_undefined, 0, EF_4_INLINE },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_u, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_TAGS }, { HTML_1_0 }, elem_ul, elem_a },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_ul, elem_caption },
    { { HTML_1_0 }, { HTML_1_0 }, elem_ul, elem_img },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, elem_lh },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_ul, elem_li },
    { { HTML_PLUS }, { HTML_2_0 }, elem_ul, elem_ol },
    { { HTML_1_0 }, { HTML_PLUS }, elem_ul, elem_p },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_ul, elem_title },
    { { HTML_PLUS }, { HTML_2_0 }, elem_ul, elem_ul },
    { { HTML_PLUS }, { HTML_PLUS }, elem_ul, elem_undefined, 0, EF_EMPH },
    { { HTML_JUL13 }, { HTML_UNDEF }, elem_ul, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_uplimit, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, elem_clippath },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_use, elem_discard },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, elem_mask },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, elem_style },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_use, elem_handler },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_use, elem_switch },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_use, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_PLUS }, { HTML_PLUS }, elem_var, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_var, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_var, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_var, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_var, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_var, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_var, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_vector, elem_undefined, 0, EF_M_DQ },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_vector, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veaffine },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veexclude },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vefill },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veintersect },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vejoin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vemarker },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vemarkerpath },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vepath },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vereverse },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vesetback },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vestroke },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vestrokepath },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veunion },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vepath, elem_vepathref },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, elem_discard },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, elem_handler },
    { { HTML_JUL07, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, elem_video, elem_source },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, elem_switch },
    { { HTML_JUL10, 0, HE_NOT_SVG_12 }, { HTML_UNDEF }, elem_video, elem_track },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_view, elem_script },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_view, elem_style },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_view, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_view, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_xa, elem_loc },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_xa, elem_undefined, EP_SVG_12_TRANS },

    { { HTML_3_2 }, { HTML_UNDEF }, elem_undefined, elem_area, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_document, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_asp },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_comment },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_doctype, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_php },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_ssi },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_stylesheet },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_whitespace },
    { { HTML_1_0 }, { HTML_1_0 }, elem_undefined, elem_faux_char, EF_LIT | EF_LL | EF_BODY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_undefined, elem_faux_char, DENY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_undefined, elem_faux_code, EF_LIT | EF_LL | EF_BODY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_undefined, elem_faux_code, DENY },
    { { HTML_TAGS }, { HTML_1_0 }, elem_undefined, elem_faux_text, EF_LIT | EF_LL | EF_BODY },
    { { HTML_TAGS }, { HTML_1_0 }, elem_undefined, elem_faux_text, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_undefined, elem_faux_text, EF_TEXT | EF_MISC | EF_EMPH | EF_PARA | EF_LIST | EF_BLOK | EF_TABLE | EF_MATH },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_undefined, elem_faux_cdata, EP_SIMPLE },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_undefined, elem_faux_char, EP_SIMPLE },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_undefined, elem_faux_code, EP_SIMPLE },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_text, EP_SIMPLE },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_undefined, elem_html } };

typedef ::std::multimap < uint64_t, parentage > parentage_t;
parentage_t parents;

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26482)
// Doing as suggested breaks the compilation, and ::std::array, bless its little cotton socks,
// can't be length initialised by the initialiser.
#endif // _MSC_VER

void parentage_init (nitpick& nits)
{   for (::std::size_t i = 0; (parent_table [i].parent_ != elem_undefined) || (parent_table [i].child_ != elem_undefined); ++i)
    {   if (context.tell (es_splurge)) nits.pick (nit_splurge, es_splurge, ec_element, "parentage: inserting ", parent_table [i].parent_, ", ", parent_table [i].child_);
        parents.emplace (parent_key (parent_table [i].parent_, parent_table [i].child_), parent_table [i]); } }

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

bool is_permitted_parent_child (nitpick& nits, const html_version& v, const elem& self, const e_element seek, const elem& parent)
{   parentage_t::const_iterator i = parents.find (parent_key (parent.get (), seek));
    if (i != parents.cend ())
        for ( ; (i != parents.cend ()) && (i -> second.parent_ == parent); ++i)
            if (i -> second.child_ == seek)
                if (does_apply < html_version > (v, i -> second.first_, i -> second.last_))
                    if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0) || ((i -> second.categories_ & H2_MATH_C) != 0))
                        if (    (! i -> second.first_.has_math_not_core ()) ||
                                ((i -> second.first_.ext () & self.first ().ext () & context.html_ver ().ext ()) != 0) ||
                                ((i -> second.first_.ext2 () & self.first ().ext2 () & context.html_ver ().ext2 ()) != 0))
                        {   if (i -> second.flags_ == 0) return true;
                            if ((i -> second.flags_ & DENY) != 0)
                            {   nits.pick (nit_wrong_parent, es_error, ec_element, "<", parent.name (), "> cannot have a child <", self.name (), "> element"); return false; }
                            if (! parent.is_unclosed (v)) return true;
                            if ((i -> second.first_ > html_tags) || i -> second.last_.known ())
                                nits.pick (nit_wrong_parent, es_error, ec_element, "<", self.name (), "> does not go inside <", parent.name (), "> in ", v.report ());
                            else nits.pick (nit_wrong_parent, es_error, ec_element, "<", self.name (), "> does not go inside <", parent.name (), ">");
                            break; }
    return false; }

bool is_permitted_parent_child (const html_version& v, const elem& self, const e_element seek, const elem& parent)
{   parentage_t::const_iterator i = parents.find (parent_key (parent.get (), seek));
    if (i != parents.cend ())
        for ( ; (i != parents.cend ()) && (i -> second.parent_ == parent); ++i)
            if (i -> second.child_ == seek)
                if (does_apply < html_version > (v, i -> second.first_, i -> second.last_))
                    if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0) || ((i -> second.categories_ & H2_MATH_C) != 0))
                        if (    (! i -> second.first_.has_math_not_core ()) ||
                                ((i -> second.first_.ext () & self.first ().ext () & context.html_ver ().ext ()) != 0) ||
                                ((i -> second.first_.ext2 () & self.first ().ext2 () & context.html_ver ().ext2 ()) != 0))
                        {   if (i -> second.flags_ == 0) return true;
                            if ((i -> second.flags_ & DENY) != 0) return false;
                            if (! parent.is_unclosed (v)) return true;
                            break; }
    return false; }

bool is_permitted_parent (nitpick& nits, const html_version& v, const elem& self, const elem& parent)
{   if (    is_error_element (self.get ()) || is_undefined_element (self.get ()) || is_custom_element (self.get ()) ||
            is_error_element (parent.get ()) || is_undefined_element (parent.get ()) || is_custom_element (parent.get ())) return true;
    if ((self.flags () & EP_IGNORE) != 0) return true;
    if (parent.is_closed (v))
    {   if (is_faux_element (self.get ())) return true;
        nits.pick (nit_sterile, es_error, ec_element, "<", parent.name (), "> cannot have child elements");
        return false; }
    if ((self.flags () & EP_TOP) != 0)
    {   if ((parent.flags () & EP_HOLDS_ALL) != 0) return true;
        nits.pick (nit_orphan, es_error, ec_element, "<", self.name (), "> cannot have parent elements");
        return false; }
    if (is_permitted_parent_child (nits, v, self, self.get (), parent)) return true;
    if (is_permitted_parent_child (nits, v, self, elem_undefined, parent)) return true;
    for (parentage_t::const_iterator i = parents.find (parent_key (elem_undefined, self.get ())); (i != parents.cend ()) && (i -> second.child_ == self); ++i)
        if (does_apply < html_version > (v, i -> second.first_, i -> second.last_))
            if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
            {   if ((i -> second.flags_ & DENY) == 0) return true;
                nits.pick (nit_wrong_parent, es_error, ec_element, "<", self.name (), "> cannot have <", parent.name (), "> as a parent");
                return false; }
    return false; }

bool is_permitted_parent (const html_version& v, const elem& self, const elem& parent)
{   if (    is_error_element (self.get ()) || is_undefined_element (self.get ()) || is_custom_element (self.get ()) ||
            is_error_element (parent.get ()) || is_undefined_element (parent.get ()) || is_custom_element (parent.get ())) return true;
    if (! does_apply < html_version > (v, self.first (), self.last ())) return true; // version error reported later
    if (! does_apply < html_version > (v, parent.first (), parent.last ())) return false;
    if ((self.flags () & EP_IGNORE) != 0) return true;
    if (parent.is_closed (v)) return false;
    if ((self.flags () & EP_TOP) != 0) return ((parent.flags () & EP_HOLDS_ALL) != 0);
    if (is_permitted_parent_child (v, self, self.get (), parent)) return true;
    if (is_permitted_parent_child (v, self, elem_undefined, parent)) return true;
    for (parentage_t::const_iterator i = parents.find (parent_key (elem_undefined, self.get ())); (i != parents.cend ()) && (i -> second.child_ == self); ++i)
        if (does_apply < html_version > (v, i -> second.first_, i -> second.last_))
            if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
                return ((i -> second.flags_ & DENY) == 0);
    return false; }

e_element default_parent (const html_version& v, const elem& self) noexcept
{   if (v.mjr () == 0) return elem_faux_document;
    switch (self.get ())
    {   case elem_html :
        case elem_htmlplus :
            return elem_faux_document;
        case elem_head :
        case elem_body :
            if (v == html_plus) return elem_htmlplus;
            return elem_html;
        case elem_a :
            return elem_p;
        case elem_above :
        case elem_apply :
        case elem_array :
        case elem_bt :
        case elem_bar :
        case elem_below :
        case elem_box :
        case elem_ci :
        case elem_cn :
        case elem_cs :
        case elem_csymbol :
        case elem_dot :
        case elem_ddot :
        case elem_fn :
        case elem_hat :
        case elem_lambda :
        case elem_reln :
        case elem_interval :
        case elem_list :
        case elem_maction :
        case elem_maligngroup :
        case elem_malignmark :
        case elem_matrix :
        case elem_matrixrow :
        case elem_menclose :
        case elem_merror :
        case elem_mfenced :
        case elem_mfrac :
        case elem_mglyph :
        case elem_mi :
        case elem_mlongdiv :
        case elem_mmultiscripts :
        case elem_mn :
        case elem_mo :
        case elem_mover :
        case elem_mpadded :
        case elem_mphantom :
        case elem_mroot :
        case elem_mrow :
        case elem_ms :
        case elem_mscarries :
        case elem_mscarry :
        case elem_msgroup :
        case elem_msline :
        case elem_msqrt :
        case elem_msrow :
        case elem_mstack :
        case elem_mspace :
        case elem_msub :
        case elem_msup :
        case elem_msubsup :
        case elem_mtable :
        case elem_mtext :
        case elem_munder :
        case elem_munderover :
        case elem_root :
        case elem_set :
        case elem_semantics :
        case elem_sqrt :
        case elem_tilde :
        case elem_vec :
        case elem_vector :
            return elem_math;
        case elem_abs :
        case elem_and :
        case elem_approx :
        case elem_arccos :
        case elem_arccosh :
        case elem_arccot :
        case elem_arccoth :
        case elem_arccsc :
        case elem_arccsch :
        case elem_arcsec :
        case elem_arcsech :
        case elem_arcsin :
        case elem_arcsinh :
        case elem_arctan :
        case elem_arctanh :
        case elem_bind :
        case elem_bvar :
        case elem_card :
        case elem_cartesianproduct :
        case elem_cbytes :
        case elem_cerror :
        case elem_ceiling :
        case elem_codomain :
        case elem_complexes :
        case elem_condition :
        case elem_conjugate :
        case elem_cos :
        case elem_cosh :
        case elem_cot :
        case elem_coth :
        case elem_csc :
        case elem_csch :
        case elem_curl :
        case elem_declare :
        case elem_degree :
        case elem_determinant :
        case elem_diff :
        case elem_divergence :
        case elem_divide :
        case elem_domain :
        case elem_domainofapplication :
        case elem_emptyset :
        case elem_eq :
        case elem_equivalent :
        case elem_eulergamma :
        case elem_exists :
        case elem_exponentiale :
        case elem_exp :
        case elem_factorial :
        case elem_factorof :
        case elem_false :
        case elem_floor :
        case elem_forall :
        case elem_gcd :
        case elem_geq :
        case elem_grad :
        case elem_gt :
        case elem_ident :
        case elem_imaginary :
        case elem_imaginaryi :
        case elem_implies :
        case elem_in :
        case elem_infinity :
        case elem_int :
        case elem_integers :
        case elem_intersect :
        case elem_inverse :
        case elem_laplacian :
        case elem_lcm :
        case elem_leq :
        case elem_limit :
        case elem_ln :
        case elem_log :
        case elem_logbase :
        case elem_lowlimit :
        case elem_lt :
        case elem_max :
        case elem_mean :
        case elem_median :
        case elem_min :
        case elem_minus :
        case elem_mode :
        case elem_moment :
        case elem_momentabout :
        case elem_mprescripts :
        case elem_naturalnumbers :
        case elem_neq :
        case elem_none :
        case elem_not :
        case elem_notanumber :
        case elem_notin :
        case elem_notsubset :
        case elem_notprsubset :
        case elem_or :
        case elem_outerproduct :
        case elem_partialdiff :
        case elem_pi :
        case elem_plus :
        case elem_power :
        case elem_primes :
        case elem_product :
        case elem_prsubset :
        case elem_quotient :
        case elem_rationals :
        case elem_real :
        case elem_reals :
        case elem_rem :
        case elem_scalarproduct :
        case elem_sdev :
        case elem_sec :
        case elem_sech :
        case elem_selector :
        case elem_sep :
        case elem_setdiff :
        case elem_share :
        case elem_sin :
        case elem_sinh :
        case elem_subset :
        case elem_sum :
        case elem_tan :
        case elem_tanh :
        case elem_tendsto :
        case elem_times :
        case elem_transpose :
        case elem_true :
        case elem_union :
        case elem_uplimit :
        case elem_variance :
        case elem_vectorproduct :
        case elem_xor :
            return elem_apply;
        case elem_annotation :
        case elem_annotation_xml :
            return elem_semantics;
        case elem_altglyph :
            return elem_glyph;
        case elem_altglyphdef :
            return elem_altglyph;
        case elem_altglyphitem :
        case elem_glyphref :
            return elem_altglyphdef;
        case elem_animate :
        case elem_animatecolour :
        case elem_animatemotion :
        case elem_animatetransform :
        case elem_animation :
        case elem_circle :
        case elem_colour_profile :
        case elem_desc :
        case elem_discard :
        case elem_ellipse :
        case elem_extensiondefs :
        case elem_flowroot :
        case elem_g :
        case elem_hint :
        case elem_line :
        case elem_metadata :
        case elem_mpath :
        case elem_path :
        case elem_pageset :
        case elem_polyline :
        case elem_polygon :
        case elem_prefetch :
        case elem_rect :
        case elem_refcontent :
        case elem_solidcolour :
        case elem_switch :
        case elem_transition :
        case elem_vectoreffect :
        case elem_view :
        case elem_use :
        case elem_xa :
            return elem_svg;
        case elem_clippath :
        case elem_filter :
        case elem_lineargradient :
        case elem_marker :
        case elem_mask :
        case elem_pattern :
        case elem_radialgradient :
        case elem_symbol :
            return elem_defs;
        case elem_definition_src :
            return elem_font_face;
        case elem_elementdef :
        case elem_defs :
            return elem_extensiondefs;
        case elem_feblend :
        case elem_fecomposite :
        case elem_fecolourmatrix :
        case elem_fecomponenttransfer :
        case elem_feconvolvematrix :
        case elem_fediffuselighting :
        case elem_fedisplacementmap :
        case elem_fedropshadow :
        case elem_feflood :
        case elem_fegaussianblur :
        case elem_feimage :
        case elem_femerge :
        case elem_femorphology :
        case elem_feoffset :
        case elem_fespecularlighting :
        case elem_fetile :
        case elem_feturbulence :
            return elem_filter;
        case elem_fefunca :
        case elem_fefuncb :
        case elem_fefuncg :
        case elem_fefuncr :
            return elem_fecomponenttransfer;
        case elem_fedistantlight :
        case elem_fepointlight :
        case elem_fespotlight :
            return elem_fediffuselighting;
        case elem_femergenode :
            return elem_femerge;
        case elem_figcaption :
            return elem_figure;
        case elem_flowimage :
        case elem_flowline :
        case elem_flowregionbreak :
        case elem_flowspan :
        case elem_flowtref :
            return elem_flowpara;
        case elem_flowpara :
            return elem_flowdiv;
        case elem_flowdiv :
        case elem_flowref :
        case elem_flowregion :
        case elem_flowregionexclude :
            return elem_flowroot;
        case elem_font_face :
        case elem_glyph :
        case elem_hkern :
        case elem_missingglyph :
        case elem_vkern :
            return elem_font;
        case elem_font_face_format :
            return elem_font_face_uri;
        case elem_font_face_name :
        case elem_font_face_uri :
            return elem_font_face_src;
        case elem_font_face_src :
            return elem_font_face;
        case elem_foreignobject :
            return elem_filter;
        case elem_handler :
            return elem_use;
        case elem_image :
            if (v.has_math ()) return elem_apply;
            if (v.has_svg ()) return elem_svg;
            break;
        case elem_loc :
            return elem_xa;
        case elem_text :
            if (v.has_svg ()) return elem_svg;
            break;
        case elem_tspan :
        case elem_textpath :
            return elem_text;
        case elem_dispatchevent :
        case elem_addeventlistener :
        case elem_removeeventlistener :
        case elem_stoppropagation :
        case elem_preventdefault :
            return elem_action;
        case elem_area :
            return elem_map;
        case elem_atop :
        case elem_choose :
        case elem_left :
        case elem_over :
        case elem_right :
            return elem_box;
        case elem_mtd:
            return elem_mtr;
        case elem_mtr:
        case elem_mlabeledtr :
            return elem_mtable;
        case elem_col :
            if (v.is_5 ()) return elem_colgroup;
            return elem_table;
        case elem_colgroup :
        case elem_tbody :
        case elem_tfoot :
        case elem_thead :
            return elem_table;
        case elem_legend :
            return elem_fieldset;
        case elem_caption :
        case elem_of :
            return elem_root;
        case elem_option :
            return elem_select;
        case elem_input :
        case elem_select :
        case elem_textarea :
            return elem_form;
        case elem_item :
            return elem_row;
        case elem_li :
            return elem_ul;
        case elem_mh :
            return elem_form;
        case elem_nest :
            return elem_rule;
        case elem_noframes :
            return elem_frameset;
        case elem_noscript :
        case elem_script :
            if (v.is_5 ()) return elem_body;
            return elem_head;
        case elem_page :
            return elem_pageset;
        case elem_param :
            if (v.is_3 ()) return elem_applet;
            return elem_object;
        case elem_prototype :
        case elem_traitdef :
        case elem_transformer :
            return elem_elementdef;
        case elem_rb :
        case elem_rbc :
        case elem_rp :
        case elem_rt :
        case elem_rtc :
            return elem_ruby;
        case elem_rdf_about :
        case elem_rdf_abouteach :
        case elem_rdf_abouteachprefix :
        case elem_rdf_bagid :
        case elem_rdf_datatype :
        case elem_rdf_description :
        case elem_rdf_id :
        case elem_rdf_li :
        case elem_rdf_nodeid :
        case elem_rdf_parsetype :
        case elem_rdf_resource :
            return elem_rdf_rdf;
        case elem_td :
        case elem_th :
            return elem_tr;
        case elem_tr :
            if (v.is_3 ()) return elem_table;
            return elem_tbody;
        case elem_row :
            return elem_array;
        case elem_rule :
            return elem_datatemplate;
        case elem_source :
            return elem_video;
        case elem_t :
            if (v.is_5 ()) return elem_body;
            return elem_math;
        case elem_tbreak :
        case elem_tref :
            return elem_tspan;
        case elem_title :
            if (v == xhtml_2) return elem_p;
            break;
        case elem_vepathref :
            return elem_vepath;
        case elem_veaffine :
        case elem_veexclude :
        case elem_vefill :
        case elem_veintersect :
        case elem_vejoin :
        case elem_vemarker :
        case elem_vemarkerpath :
        case elem_vepath :
        case elem_vereverse :
        case elem_vesetback :
        case elem_vestroke :
        case elem_vestrokepath :
        case elem_veunion :
            return elem_vectoreffect;
        default : break; }
    if ((self.categories () & EF_METADATA) == EF_METADATA) return elem_head;
    if (v == html_plus)
        if ((self.categories () & (EF_EMPH | EF_MISC | EF_TEXT)) != 0) return elem_p;
    return elem_body; }
