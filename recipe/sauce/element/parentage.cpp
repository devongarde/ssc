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
#include "element/parentage.h"
#include "main/context.h"

struct parentage
{   html_version first_, last_;
    e_element parent_;
    e_element child_;
    uint64_t flags_, categories_;
    parentage (const html_version& first, const html_version& last, const e_element parent, const e_element child, const uint64_t flags = 0, const uint64_t categories = 0)
        : first_ (first), last_ (last), parent_ (parent), child_ (child), flags_ (flags), categories_ (categories) { } };

inline bool operator == (const parentage& lhs, const parentage& rhs)
{   return (lhs.child_ == rhs.child_) && (lhs.parent_ == rhs.parent_) && (lhs.first_ == rhs.first_) && (lhs.last_ == rhs.last_); }

inline bool operator != (const parentage& lhs, const parentage& rhs)
{   return ! (lhs == rhs); }

inline bool operator < (const parentage& lhs, const parentage& rhs)
{   if (lhs.parent_ < rhs.parent_) return true;
    if (lhs.parent_ > rhs.parent_) return false;
    return (lhs.child_ < rhs.child_); }

inline bool operator <= (const parentage& lhs, const parentage& rhs)
{   if (lhs < rhs) return true;
    return (lhs == rhs); }

inline bool operator > (const parentage& lhs, const parentage& rhs)
{   return ! (lhs <= rhs); }

inline bool operator >= (const parentage& lhs, const parentage& rhs)
{   return ! (lhs < rhs); }

inline uint64_t parent_key (const e_element parent, const e_element child)
{   return (static_cast <uint64_t> (parent) << 32) + static_cast <uint64_t> (child); }

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
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_a, elem_undefined, 0, EF_S_G },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_a, elem_undefined, DENY, EF_5_INTERACTIVE },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_altglyphdef },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_foreignobject },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_text },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_view },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_a, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_abbr, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_abbr, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_abbr, elem_undefined, 0, EF_5_PHRASE },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_address, elem_address, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_address, elem_footer, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_address, elem_header, DENY },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_address, elem_undefined, 0, EF_HEAD | EF_5_SECTION | DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_address, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyph, elem_undefined },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyphdef, elem_glyphref },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyphdef, elem_altglyphitem },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyphitem, elem_glyphref },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_altglyphitem, elem_altglyphitem },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animation, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animation, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animation, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animation, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animate, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animate, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_animate, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatecolour, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatecolour, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatecolour, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatemotion, elem_handler },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatemotion, elem_mpath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatemotion, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatemotion, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatetransform, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatetransform, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_animatetransform, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_annotation_xml, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_2 }, { HTML_UNDEF }, elem_applet, elem_param },
    { { HTML_3_2 }, { HTML_3_2 }, elem_applet, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_applet, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_applet, elem_undefined },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_apply, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_PLUS }, { HTML_PLUS }, elem_arg, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_array },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_item },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, elem_row },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_sub },
    { { HTML_PLUS }, { HTML_PLUS }, elem_array, elem_sup },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_article, elem_main, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_article, elem_undefined, 0, EF_5_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_aside, elem_main, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_aside, elem_undefined, 0, EF_5_FLOW },
    { { HTML_3_0 }, { HTML_3_0 }, elem_au, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_audio, elem_audio, DENY },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_audio, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_audio, elem_handler },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_audio, elem_track },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_audio, elem_source },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_audio, elem_switch },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_audio, elem_video, DENY },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_audio, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_PLUS }, { HTML_PLUS }, elem_b, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_b, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_b, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_b, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_b, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_b, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_banner, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_bdi, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_bdo, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_bdo, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_below, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_big, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_big, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_big, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_big, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, elem_credit },
    { { HTML_1_0 }, { HTML_1_0 }, elem_blockquote, elem_img },
    { { HTML_1_0 }, { HTML_2_0 }, elem_blockquote, elem_p },
    { { HTML_1_0 }, { HTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_EMPH },
    { { HTML_PLUS }, { HTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_TEXT | EF_MISC },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_blockquote, elem_undefined, 0, EF_32_BLOCK },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_blockquote, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_blockquote, elem_undefined, 0, EF_X2_FLOWLIST },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_blockquote, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_blockcode, elem_undefined, 0, EF_X2_FLOWLIST },
    { { HTML_1_0 }, { HTML_1_0 }, elem_body, elem_a },
    { { HTML_2_0, HV_NOT30 }, { HTML_3_2 }, elem_body, elem_address },
    { { HTML_3_0 }, { HTML_3_0 }, elem_body, elem_banner },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_body, elem_del },
    { { HTML_2_0 }, { HTML_2_0 }, elem_body, elem_dl },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_body, elem_undefined, 0, EF_5_FLOW },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_button, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_bvar, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_PLUS }, { HTML_PLUS }, elem_byline, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_byline, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_caption, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_caption, elem_undefined, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_caption, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_caption, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_caption, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_caption, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_caption, elem_table, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_caption, elem_undefined, 0, EF_5_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_canvas, elem_undefined },
    { { HTML_3_2 }, { HTML_UNDEF }, elem_centre, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_centre, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_centre, elem_undefined },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ci, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_circle, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_circle, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_circle, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_circle, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_circle, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_cite, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_cite, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_cite, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_cite, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_cite, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_cite, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_cite, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_a, DENY },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_g, DENY },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_image, DENY },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_svg, DENY },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_switch, DENY },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_clippath, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, elem_text },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, elem_use },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_clippath, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM | EF_SVG_SHAPE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, elem_sep },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, elem_undefined, 0, EF_M_PRESINCONTENT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_cmd, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_PLUS }, { HTML_PLUS }, elem_code, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_code, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_code, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_code, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_code, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_code, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_code, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_colgroup, elem_col },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_colgroup, elem_template },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_colourprofile, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_condition, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_cursor, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_3_0 }, { HTML_3_0 }, elem_credit, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_data, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_datalist, elem_option },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_datalist, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_datalist, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_PLUS }, { HTML_2_0 }, elem_dd, elem_p },
    { { HTML_PLUS }, { HTML_2_0 }, elem_dd, elem_dl },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dd, elem_ol },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dd, elem_ul },
    { { HTML_2_0 }, { HTML_2_0 }, elem_dd, elem_undefined, 0, EF_LIST | EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dd, elem_undefined, 0, EF_3_FLOW },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dd, elem_undefined, 0, EF_32_FLOW },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dd, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dd, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dd, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_declare, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_defs, elem_a, DENY },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_1 | HE_SVG_2_0 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_canvas },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_cursor },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_defs, elem_defs },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_foreignobject },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_defs, elem_g },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_image },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_defs, elem_lineargradient },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_marker },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_mask },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_defs, elem_pattern },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_defs, elem_radialgradient },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_script },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_defs, elem_solidcolour },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_1 | HE_SVG_2_0 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_text },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_defs, elem_symbol },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_defs, elem_use },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_video },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_defs, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_defs, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_defs, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_degree, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_del, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_del, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_desc, elem_undefined },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_details, elem_summary },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_details, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dfn, elem_dfn, DENY },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dfn, elem_undefined, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_dfn, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dfn, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dfn, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dfn, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dfn, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dfn, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_di, elem_dd },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_di, elem_dt },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_dialogue, elem_undefined, 0, EF_5_FLOW },
    { { HTML_TAGS }, { HTML_1_0 }, elem_dir, elem_a },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dir, elem_img },
    { { HTML_TAGS, HV_NOTPLUS }, { HTML_UNDEF }, elem_dir, elem_li },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_discard, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_discard, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_discard, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_div, elem_dd },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_div, elem_dt },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dir, elem_undefined, 0, EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_div, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_div, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_div, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_div, elem_undefined, 0, EF_5_FLOW },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_a },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_caption },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_dl, elem_dd },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_di },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_dl, elem_div },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_dl, elem_dt },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_img },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dl, elem_lh },
    { { HTML_1_0 }, { HTML_PLUS }, elem_dl, elem_p },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dl, elem_title },
    { { HTML_1_0 }, { HTML_1_0 }, elem_dl, elem_undefined, 0, EF_EMPH },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dl, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dt, elem_footer, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dt, elem_header, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_dt, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_dt, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_dt, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dt, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dt, elem_undefined, DENY, EF_HEAD | EF_5_SECTION },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_dt, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_defs },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_prototype },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_script },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_traitdef },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_transformer },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_elementdef, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_ellipse, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_ellipse, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_ellipse, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_ellipse, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_ellipse, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_em, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_em, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_em, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_em, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_em, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_em, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_em, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_script },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_elementdef },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_extensiondefs, elem_defs },
    { { HTML_1_0, HV_NOTPLUS }, { HTML_UNDEF }, elem_faux_document, elem_html },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_faux_document, elem_faux_xml },
    { { HTML_PLUS }, { HTML_PLUS }, elem_faux_document, elem_htmlplus },
    { { HTML_TAGS }, { HTML_TAGS }, elem_faux_document, elem_undefined },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feblend, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feblend, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecolourmatrix, elem_set },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefunca },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncb },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncg },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomponenttransfer, elem_fefuncr },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomposite, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fecomposite, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feconvolvematrix, elem_set },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fedistantlight },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fepointlight },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fediffuselighting, elem_fespotlight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fediffuselighting, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fedistantlight, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fedistantlight, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fedisplacementmap, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feflood, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feflood, elem_animatecolour },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feflood, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefunca, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefunca, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncb, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncb, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncg, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncg, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncr, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fefuncr, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fegaussianblur, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fegaussianblur, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feimage, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feimage, elem_animatetransform },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feimage, elem_set },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_femerge, elem_femergenode },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_femergenode, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_femergenode, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_femorphology, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_femorphology, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feoffset, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feoffset, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fepointlight, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fepointlight, elem_set },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fedistantlight },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fepointlight },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespecularlighting, elem_fespotlight },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespecularlighting, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespotlight, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fespotlight, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fetile, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fetile, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feturbulence, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_feturbulence, elem_set },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_fieldset, elem_legend },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { XHTML_2_0 }, elem_fieldset, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_fieldset, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_fig, elem_caption },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_credit },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_fig, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_img, DENY },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_overlay },
    { { HTML_PLUS }, { HTML_PLUS }, elem_fig, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_fig, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_figcaption, elem_undefined, 0, EF_5_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_figure, elem_figcaption },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_figure, elem_undefined, 0, EF_5_FLOW },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_feblend },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fecolour },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fecolourmatrix },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fecomposite },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fediffuselighting },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fedisplacementmap },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fegaussianblur },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_feimage },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_femerge },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_femorphology },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_feoffset },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fespecularlighting },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_fetile },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_filter, elem_feturbulence },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_filter, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_filter, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_filter, elem_undefined, 0, EF_SVG_FILTER | EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowdiv, elem_flowpara },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowdiv, elem_flowregionbreak },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowimage, elem_g },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowimage, elem_flowimage },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowimage, elem_undefined, 0, EF_SVG_SHAPE },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowimage },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowline },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowregionbreak },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowline, elem_flowspan },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowimage },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowline },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowregionbreak },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowspan },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowpara, elem_flowtref },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowregion, elem_flowregionexclude },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowregion, elem_use },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowregion, elem_undefined, 0, EF_SVG_SHAPE },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowregionexclude, elem_use },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowregionexclude, elem_undefined, 0, EF_SVG_SHAPE },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowdiv },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowregion },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowregionexclude },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowroot, elem_flowpara },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowimage },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowline },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowregionbreak },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_flowspan, elem_flowspan },
    { { HTML_3_0, HV_NOT4 }, { HTML_UNDEF }, elem_fn, elem_undefined, 0, EF_3_BODYIN | EF_M_CONTENTEXPR },
    { { HTML_3_2 }, { HTML_3_2 }, elem_font, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_font, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_glyph },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_hkern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_missingglyph },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_font, elem_vkern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_font, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_font, elem_undefined },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontface, elem_fontfacesrc },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontface, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontface, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontface, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontfaceformat, elem_fontfaceformat },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontfacesrc, elem_fontfacename },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontfacesrc, elem_fontfaceuri },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontfacesrc, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontfacesrc, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_fontfaceuri, elem_fontfaceformat },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontfaceuri, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_fontfaceuri, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_footer, elem_footer, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_footer, elem_header, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_footer, elem_main, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_footer, elem_undefined, 0, EF_5_FLOW },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_footnote, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_margin, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_footnote, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_foreignobject, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_foreignobject, elem_svg },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_foreignobject, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_foreignobject, elem_undefined },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_form, elem_undefined, 0, EF_5_FLOW },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_frame },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_frameset },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_frameset, elem_noframes },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_canvas },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_cursor },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_g, elem_defs },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_foreignobject },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_g, elem_g },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_g, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_script },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_g, elem_solidcolour },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_text },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_g, elem_use },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_video },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_g, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_g, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_g, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_altglyph },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_foreignobject },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_text },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_view },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyph, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_glyph, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyphref, elem_glyphref },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_glyphref, elem_altglyphitem },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_h, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h1, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h1, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h1, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h1, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h1, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h1, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h2, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h2, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h2, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h2, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h2, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h2, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h3, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h3, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h3, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h3, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h3, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h3, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h4, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h4, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h4, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h4, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h4, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h4, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h5, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h5, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h5, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h5, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h5, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h5, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_h6, elem_undefined, 0, EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_h6, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_h6, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_h6, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_h6, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_h6, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_head, elem_access },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_head, elem_action },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_head, elem_listener },
    { { HTML_3_0 }, { HTML_3_0 }, elem_head, elem_range },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_head, elem_undefined, 0, EF_METADATA },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_header, elem_footer, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_header, elem_header, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_header, elem_main, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_header, elem_undefined, 0, EF_5_FLOW },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h1 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h2 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h3 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h4 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h5 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_h6 },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_script },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_hgroup, elem_template },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_hkern, elem_undefined, 0, EF_SVG_DESC },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_i, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_iframe, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_iframe, elem_script, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_iframe, elem_undefined, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_image, elem_a },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_image, elem_clippath },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_image, elem_desc },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_image, elem_title },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_image, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_image, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_image, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_image, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_image, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_image, elem_switch },
    { { HTML_PLUS }, { HTML_PLUS }, elem_image, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_image, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_kbd, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_lambda, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_UNDEF }, elem_lang, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_PLUS }, { HTML_PLUS }, elem_l, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_label, elem_label, DENY },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_label, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_label, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_legend, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_legend, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_legend, elem_undefined, 0, EF_HEAD },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_li, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_line, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_line, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_line, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_line, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_line, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_animatetransform },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_lineargradient, elem_discard },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_set },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, elem_lineargradient, elem_stop },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_lineargradient, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_lineargradient, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_lineargradient, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_list, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_listing, elem_undefined },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_listing, elem_form },
    { { HTML_PLUS }, { HTML_PLUS }, elem_lit, elem_tab },
    { { HTML_PLUS }, { HTML_PLUS }, elem_lit, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_lowlimit, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_logbase, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_maction, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_main, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_map, elem_area },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_map, elem_undefined, 0, EF_4_BLOCK },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_footnote },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_margin },
    { { HTML_PLUS }, { HTML_PLUS }, elem_margin, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_mark, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_marker, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_a },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_audio },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_canvas },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_foreignobject },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_text },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_video },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_marker, elem_view },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_marker, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_STR | EF_SVG_SHAPE | EF_SVG_PSGRAD },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_mask, elem_undefined, 0, EF_S_G },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_atop },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_choose },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_left },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_over },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_right },
    { { HTML_PLUS }, { HTML_PLUS }, elem_math, elem_undefined, 0, EF_MATH | EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_math, elem_undefined, 0, EF_3_MATHIN },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_math, elem_undefined, 0, EF_M_MATH },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_matrix, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_matrixrow, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_TAGS }, { HTML_1_0 }, elem_menu, elem_a },
    { { HTML_5_1 }, { HTML_5_1 }, elem_menu, elem_hr },
    { { HTML_1_0 }, { HTML_1_0 }, elem_menu, elem_img },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_menu, elem_li },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, elem_li },
    { { HTML_5_1 }, { HTML_5_1 }, elem_menu, elem_menu },
    { { HTML_5_1 }, { HTML_5_1 }, elem_menu, elem_menuitem },
    { { HTML_1_0 }, { HTML_1_0 }, elem_menu, elem_undefined, 0, EF_EMPH },
    { { HTML_5_1 }, { HTML_5_1 }, elem_menu, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_merror, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_metadata, elem_undefined },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_meter, elem_meter, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_meter, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfenced, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mfrac, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mi, elem_malignmark },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_altglyph },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_foreignobject },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_text },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_view },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_missingglyph, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_missingglyph, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mmultiscripts, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mn, elem_malignmark },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mo, elem_malignmark },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mover, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mpadded, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_mpath, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mphantom, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mroot, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mrow, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msqrt, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mstyle, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ms, elem_malignmark },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msub, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msubsup, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_msup, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtable, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtext, elem_malignmark },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtd, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_mtr, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_munder, elem_undefined, 0, EF_M_PRESEXPR },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_munderover, elem_undefined, 0, EF_M_PRESEXPR },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_nav, elem_main, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_nav, elem_undefined, 0, EF_5_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_caption },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_title },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_li },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_nl, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noembed, elem_undefined },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noframes, elem_body },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noframes, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noframes, elem_undefined },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_noscript, elem_undefined, 0, EF_4_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noscript, elem_link },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noscript, elem_style },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noscript, elem_meta },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_noscript, elem_undefined },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_ol, elem_script },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_ol, elem_template },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_ol, elem_title },
    { { HTML_PLUS }, { HTML_2_0 }, elem_ol, elem_ul },
    { { HTML_1_0 }, { HTML_1_0 }, elem_ol, elem_undefined, 0, EF_EMPH },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_ol, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_online, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_optgroup, elem_option },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_optgroup, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_output, elem_undefined, 0, EF_5_PHRASE },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_p, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_page, elem_undefined, 0, EF_SVG_GRAPH },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_pageset, elem_page },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_canvas },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_foreignobject },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_pattern, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_text },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_video },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_view },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_pattern, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_pattern, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_clippath },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_path, elem_data },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_path, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_path, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_path, elem_switch },
    { { HTML_4_0, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_path, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_path, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_person, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_person, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_picture, elem_source },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_picture, elem_img },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_picture, elem_script },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_picture, elem_template },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_plaintext, elem_undefined },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polyline, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polyline, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polyline, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_polyline, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polyline, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polygon, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polygon, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_polygon, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_polygon, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_polygon, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_pre, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_prefetch, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_prefetch, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_PLUS }, { HTML_PLUS }, elem_printed, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_progress, elem_progress, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_progress, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_q, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_2 }, elem_q, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_q, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_q, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_q, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_quote, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_quote, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_radialgradient, elem_stop, 0 },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rb, elem_ruby, DENY },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rb, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_rb, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rbc, elem_rb },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_animatetransform },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_radialgradient, elem_discard },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_set },
    { { HTML_4_0, 0, HE_SVG }, { HTML_UNDEF }, elem_radialgradient, elem_stop },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_radialgradient, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_radialgradient, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_radialgradient, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_rect, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_rect, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_rect, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_rect, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_rect, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_PSGRAD },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_refcontent, elem_param },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_refcontent, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_reln, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_PLUS }, { HTML_PLUS }, elem_removed, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_root, elem_of },
    { { HTML_3_0 }, { HTML_3_0 }, elem_root, elem_undefined, 0, EF_3_MATHIN },
    { { HTML_3_0 }, { HTML_3_0 }, elem_row, elem_item },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rp, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_rp, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rt, elem_ruby, DENY },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rt, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_rt, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_rtc, elem_rp },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_rtc, elem_rp },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_rtc, elem_rt },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_rtc, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1 }, { HTML_5_3 }, elem_ruby, elem_rb },
    { { XHTML_1_1 }, { XHTML_2_0 }, elem_ruby, elem_rbc },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_ruby, elem_rp },
    { { XHTML_1_1 }, { HTML_UNDEF }, elem_ruby, elem_rt },
    { { XHTML_1_1 }, { HTML_5_3 }, elem_ruby, elem_rtc },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_ruby, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_s, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_s, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_s, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_s, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_samp, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_samp, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_samp, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_samp, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_samp, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_samp, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_samp, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_section, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_section, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0 }, { HTML_2_0 }, elem_select, elem_input, DENY },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_select, elem_option },
    { { HTML_2_0 }, { HTML_2_0 }, elem_select, elem_textarea, DENY },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_select, elem_optgroup },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_select, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_semantics, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_set, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_set, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_set, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_small, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_small, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_small, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_small, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_solidcolour, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_solidcolour, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_solidcolour, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_solidcolour, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_span, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_span, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_span, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sqrt, elem_undefined, 0, EF_3_MATHIN },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_standby, elem_undefined, 0, EF_X2_TEXT },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_stop, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_stop, elem_animatecolour },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_stop, elem_switch },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_stop, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_stop, elem_set },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_stop, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_stop, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { HTML_2_0 }, { HTML_2_0 }, elem_strike, elem_undefined },
    { { HTML_3_2 }, { HTML_3_2 }, elem_strike, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_strike, elem_undefined, 0, EF_4_INLINE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_strong, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_strong, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_strong, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_strong, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_strong, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_strong, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_strong, elem_undefined, 0, EF_5_PHRASE },
    // style is a special case handled in code (dratted CSS)
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_summary, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_summary, elem_undefined, 0, EF_HEAD | EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, elem_text },
    { { HTML_PLUS }, { HTML_PLUS }, elem_sub, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sub, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_sub, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_sub, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_sub, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_sub, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, elem_text },
    { { HTML_PLUS }, { HTML_PLUS }, elem_sup, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_sup, elem_undefined, 0, EF_3_TEXTIN | EF_3_MATHIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_sup, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_sup, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_sup, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_sup, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_canvas },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_cursor },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_svg, elem_defs },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_foreignobject },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_svg, elem_g },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_svg, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_script },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_svg, elem_solidcolour },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_text },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_svg, elem_use },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_video },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_view },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_svg, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_svg, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_svg, elem_undefined, 0, EF_SVG_DESC },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_switch, elem_foreignobject },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_a },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_canvas },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_foreignobject },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_switch, elem_g },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_svg },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_text },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_switch, elem_use },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_video },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_switch, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_switch, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_switch, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_SHAPE },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_switch, elem_undefined },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_altglyphdef },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_audio },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_canvas },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_clippath },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_colourprofile },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_cursor },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_filter },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_font },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_fontface },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_foreignobject },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_iframe },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_image },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_marker },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_mask },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_symbol, elem_pattern },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_text },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_video },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_2 }, { HTML_UNDEF }, elem_symbol, elem_undefined, 0, EF_S_G },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_symbol, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_PSGRAD | EF_SVG_STR },
    { { HTML_3_0 }, { HTML_3_0 }, elem_t, elem_undefined, 0, EF_3_MATHIN },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_table, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tbody, elem_tr },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_tbody, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_PLUS }, { HTML_PLUS }, elem_td, elem_p },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_td, elem_td, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_td, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH | EF_HEAD | EF_LIST },
    { { HTML_2_0 }, { HTML_2_0 }, elem_td, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_td, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_td, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_td, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_td, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_td, elem_undefined, 0, EF_5_FLOW },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_col },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_figcaption },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_legend },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_li },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_option },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_optgroup },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_param },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_rb },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_rp },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_rt },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_rtc },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_source },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_track },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_colgroup },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_tbody },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_tfoot },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_thead },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_tr },
    { { HTML_5_0 }, { HTML_5_1 }, elem_template, elem_undefined, 0, EF_METADATA | EF_5_FLOW | EF_5_SCRIPT },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_template, elem_undefined },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_text, elem_textpath },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_text, elem_tspan },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_a },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_clippath },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_text, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_text, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_text, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_TEXT },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_text, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_TEXT | EF_SVG_PSGRAD },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_textarea, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_textarea, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_textarea, elem_tspan },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_textarea, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_textarea, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_4_0, 0, HE_SVG_1_0 | HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, elem_tspan },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, elem_altglyph },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, elem_animatecolour },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_clippath },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_marker },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_set },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, elem_tref },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_tspan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_textpath, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_textpath, elem_undefined, 0, EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tfoot, elem_tr },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_tfoot, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_th, elem_footer, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_th, elem_header, DENY },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_th, elem_th, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, elem_p },
    { { HTML_PLUS }, { HTML_PLUS }, elem_th, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH | EF_HEAD | EF_LIST },
    { { HTML_2_0 }, { HTML_2_0 }, elem_th, elem_undefined },
    { { HTML_3_0 }, { HTML_3_0 }, elem_th, elem_undefined, 0, EF_3_BODYIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_th, elem_undefined, 0, EF_32_BODY },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_th, elem_undefined, 0, EF_4_FLOW },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_th, elem_undefined, 0, EF_X2_FLOW },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_th, elem_undefined, DENY, EF_HEAD | EF_5_SECTION },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_th, elem_undefined, 0, EF_5_FLOW },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_thead, elem_tr },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_thead, elem_undefined, 0, EF_5_SCRIPT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_time, elem_undefined, 0, EF_5_PHRASE },
    { { HTML_PLUS }, { HTML_PLUS }, elem_title, elem_undefined, 0, EF_EMPH },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_title, elem_undefined },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_title, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_tr, DENY },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_td },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_tr, elem_th },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_tr, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_transformer, elem_param },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_transformer, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tref, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tref, elem_animatecolour },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tref, elem_set },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tref, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_a },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, elem_altglyph },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_animate },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, elem_animatecolour },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_tspan, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_tspan, elem_handler },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_script },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_set },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_style },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_tspan, elem_switch },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_tspan, elem_tbreak },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, elem_tref },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_tspan, elem_tspan },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_tspan, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_tspan, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { XHTML_2_0, 0, HE_SVG_2_0  }, { HTML_UNDEF }, elem_tspan, elem_undefined, 0, EF_SVG_DESC | EF_SVG_PSGRAD },
    { { HTML_PLUS }, { HTML_PLUS }, elem_tt, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_tt, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_tt, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_tt, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_tt, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_tt, elem_undefined },
    { { HTML_PLUS }, { HTML_PLUS }, elem_u, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_3_0 }, { HTML_3_0 }, elem_u, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_u, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_u, elem_undefined, 0, EF_4_INLINE },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_u, elem_undefined, 0, EF_5_PHRASE },
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
    { { HTML_5_0 }, { HTML_UNDEF }, elem_ul, elem_undefined, 0, EF_5_SCRIPT },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_uplimit, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_use, elem_clippath },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_use, elem_desc },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_use, elem_mask },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_use, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_use, elem_style },
    { { HTML_4_0, 0, HE_SVG_1_0 }, { HTML_UNDEF }, elem_use, elem_title },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_use, elem_handler },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_use, elem_switch },
    { { XHTML_1_0, 0, HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 }, { HTML_UNDEF }, elem_use, elem_undefined, 0, EF_SVG_ANIM | EF_SVG_DESC },
    { { HTML_PLUS }, { HTML_PLUS }, elem_var, elem_undefined, 0, EF_TEXT | EF_MISC | EF_EMPH },
    { { HTML_2_0 }, { HTML_2_0 }, elem_var, elem_undefined, 0, EF_TEXT | EF_PHRASE | EF_FONT },
    { { HTML_3_0 }, { HTML_3_0 }, elem_var, elem_undefined, 0, EF_3_TEXTIN },
    { { HTML_3_2 }, { HTML_3_2 }, elem_var, elem_undefined, 0, EF_32_TEXTIN },
    { { HTML_4_0 }, { XHTML_1_1 }, elem_var, elem_undefined, 0, EF_4_INLINE },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_var, elem_undefined, 0, EF_X2_TEXT },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_var, elem_undefined, 0, EF_5_PHRASE },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_vector, elem_undefined, 0, EF_M_CONTENTEXPR },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veaffine },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veexclude },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vefill },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veintersect },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vejoin },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vemarker },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vemarkerpath },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vepath },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vereverse },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vesetback },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vestroke },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_vestrokepath },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vectoreffect, elem_veunion },
    { { XHTML_1_1, 0, HE_SVG_1_2_FULL }, { HTML_UNDEF }, elem_vepath, elem_vepathref },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_video, elem_audio, DENY },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_video, elem_track },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_video, elem_discard },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_video, elem_handler },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_video, elem_source },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_video, elem_switch },
    { { HTML_5_0 }, { HTML_UNDEF }, elem_video, elem_video, DENY },
    { { XHTML_1_1, 0, HE_SVG_1_2 }, { HTML_UNDEF }, elem_video, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_view, elem_script },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_view, elem_style },
    { { XHTML_1_0, 0, HE_SVG_1_1 }, { HTML_UNDEF }, elem_view, elem_undefined, 0, EF_SVG_DESC },
    { { XHTML_2_0, 0, HE_SVG_2_0 }, { HTML_UNDEF }, elem_view, elem_undefined, 0, EF_SVG_DESC | EF_SVG_ANIM },

    { { HTML_3_2 }, { HTML_UNDEF }, elem_undefined, elem_area, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_document, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_asp },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_comment },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_doctype, DENY },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_php },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_ssi },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_stylesheet },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_whitespace },
    { { HTML_TAGS }, { HTML_1_0 }, elem_undefined, elem_faux_text, EF_LIT | EF_LL | EF_BODY },
    { { HTML_TAGS }, { HTML_1_0 }, elem_undefined, elem_faux_text, DENY },
    { { HTML_PLUS }, { HTML_PLUS }, elem_undefined, elem_faux_text, EF_TEXT | EF_MISC | EF_EMPH | EF_PARA | EF_LIST | EF_BLOK | EF_TABLE | EF_MATH },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, elem_faux_text, EP_SIMPLE },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_undefined, elem_html } };

typedef ::std::multimap < uint64_t, parentage > parentage_t;
parentage_t parents;

void parentage_init (nitpick& nits)
{   for (::std::size_t i = 0; (parent_table [i].parent_ != elem_undefined) || (parent_table [i].child_ != elem_undefined); ++i)
    {   if (context.tell (e_splurge)) nits.pick (nit_splurge, es_splurge, ec_element, "parentage: inserting ", parent_table [i].parent_, ", ", parent_table [i].child_);
        parents.emplace (parent_key (parent_table [i].parent_, parent_table [i].child_), parent_table [i]); } }

bool is_permitted_parent_child (nitpick& nits, const html_version& v, const elem& self, const e_element seek, const elem& parent)
{   parentage_t::const_iterator i = parents.find (parent_key (parent.get (), seek));
    if (i != parents.cend ())
        for ( ; (i != parents.cend ()) && (i -> second.parent_ == parent); ++i)
            if (i -> second.child_ == seek)
                if (does_apply (v, i -> second.first_, i -> second.last_))
                    if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
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
                if (does_apply (v, i -> second.first_, i -> second.last_))
                    if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
                    {   if (i -> second.flags_ == 0) return true;
                        if ((i -> second.flags_ & DENY) != 0) return false;
                        if (! parent.is_unclosed (v)) return true;
                        break; }
    return false; }

bool is_permitted_parent (nitpick& nits, const html_version& v, const elem& self, const elem& parent)
{   if (is_error_element (self.get ()) || is_undefined_element (self.get ()) || is_error_element (parent.get ()) || is_undefined_element (parent.get ())) return true;
    if ((self.flags () & EP_IGNORE) != 0) return true;
    if (parent.is_closed (v))
    {   if (is_faux_element (self.get ())) return true;
        nits.pick (nit_sterile, es_error, ec_element, "<", parent.name (), "> cannot have child elements");
        return false; }
    if ((self.flags () & EP_TOP) != 0)
    {   if (parent.get () == elem_faux_document) return true;
        nits.pick (nit_orphan, es_error, ec_element, "<", self.name (), "> cannot have parent elements");
        return false; }
    if (is_permitted_parent_child (nits, v, self, self.get (), parent)) return true;
    if (is_permitted_parent_child (nits, v, self, elem_undefined, parent)) return true;
    for (parentage_t::const_iterator i = parents.find (parent_key (elem_undefined, self.get ())); (i != parents.cend ()) && (i -> second.child_ == self); ++i)
        if (does_apply (v, i -> second.first_, i -> second.last_))
            if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
            {   if ((i -> second.flags_ & DENY) == 0) return true;
                nits.pick (nit_wrong_parent, es_error, ec_element, "<", self.name (), "> cannot have <", parent.name (), "> as a parent");
                return false; }
    return false; }

bool is_permitted_parent (const html_version& v, const elem& self, const elem& parent)
{   if (is_error_element (self.get ()) || is_undefined_element (self.get ()) || is_error_element (parent.get ()) || is_undefined_element (parent.get ())) return true;
    if (! does_apply (v, self.first (), self.last ())) return true; // version error reported later
    if (! does_apply (v, parent.first (), parent.last ())) return false;
    if ((self.flags () & EP_IGNORE) != 0) return true;
    if (parent.is_closed (v)) return false;
    if ((self.flags () & EP_TOP) != 0) return (parent == elem_faux_document);
    if (is_permitted_parent_child (v, self, self.get (), parent)) return true;
    if (is_permitted_parent_child (v, self, elem_undefined, parent)) return true;
    for (parentage_t::const_iterator i = parents.find (parent_key (elem_undefined, self.get ())); (i != parents.cend ()) && (i -> second.child_ == self); ++i)
        if (does_apply (v, i -> second.first_, i -> second.last_))
            if ((i -> second.categories_ == 0) || ((self.categories () & i -> second.categories_) != 0))
                return ((i -> second.flags_ & DENY) == 0);
    return false; }

e_element default_parent (const html_version& v, const elem& self)
{   if (v.major () == 0) return elem_faux_document;
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
        case elem_merror :
        case elem_mfenced :
        case elem_mfrac :
        case elem_mi :
        case elem_mmultiscripts :
        case elem_mn :
        case elem_mo :
        case elem_mover :
        case elem_mpadded :
        case elem_mphantom :
        case elem_mroot :
        case elem_mrow :
        case elem_ms :
        case elem_msqrt :
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
        case elem_t :
        case elem_tilde :
        case elem_vec :
        case elem_vector :
            return elem_math;
        case elem_abs :
        case elem_arccos :
        case elem_arcsin :
        case elem_arctan :
        case elem_and :
        case elem_annotation :
        case elem_annotation_xml :
        case elem_bvar :
        case elem_condition :
        case elem_conjugate :
        case elem_cos :
        case elem_cosh :
        case elem_cot :
        case elem_coth :
        case elem_csc :
        case elem_csch :
        case elem_declare :
        case elem_degree :
        case elem_determinant :
        case elem_diff :
        case elem_divide :
        case elem_eq :
        case elem_exists :
        case elem_exp :
        case elem_factorial :
        case elem_forall :
        case elem_gcd :
        case elem_geq :
        case elem_gt :
        case elem_ident :
        case elem_implies :
        case elem_in :
        case elem_int :
        case elem_intersect :
        case elem_inverse :
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
        case elem_mprescripts :
        case elem_neq :
        case elem_none :
        case elem_not :
        case elem_notin :
        case elem_notsubset :
        case elem_notprsubset :
        case elem_or :
        case elem_partialdiff :
        case elem_plus :
        case elem_power :
        case elem_product :
        case elem_prsubset :
        case elem_quotient :
        case elem_rem :
        case elem_sdev :
        case elem_sec :
        case elem_sech :
        case elem_selector :
        case elem_sep :
        case elem_setdiff :
        case elem_sin :
        case elem_sinh :
        case elem_subset :
        case elem_sum :
        case elem_tan :
        case elem_tanh :
        case elem_tendsto :
        case elem_times :
        case elem_transpose :
        case elem_union :
        case elem_uplimit :
        case elem_variance :
        case elem_xor :
            return elem_apply;
        case elem_altglyph :
            return elem_glyph;
        case elem_altglyphdef :
        case elem_altglyphitem :
        case elem_glyphref :
            return elem_altglyph;
        case elem_animate :
        case elem_animatecolour :
        case elem_animatemotion :
        case elem_animatetransform :
        case elem_animation :
        case elem_circle :
        case elem_colourprofile :
        case elem_defs :
        case elem_desc :
        case elem_discard :
        case elem_ellipse :
        case elem_extensiondefs :
        case elem_flowref :
        case elem_flowroot :
        case elem_g :
        case elem_hint :
        case elem_line :
        case elem_loc :
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
        case elem_view :
        case elem_use :
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
        case elem_elementdef :
        case elem_traitdef :
        case elem_transformer :
            return elem_extensiondefs;
        case elem_feblend :
        case elem_fecomposite :
        case elem_fecolour :
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
        case elem_flowdiv :
        case elem_flowimage :
        case elem_flowline :
        case elem_flowpara :
        case elem_flowregion :
        case elem_flowregionbreak :
        case elem_flowregionexclude :
        case elem_flowspan :
            return elem_flowroot;
        case elem_flowtref :
            return elem_flowpara;
        case elem_fontface :
        case elem_glyph :
        case elem_hkern :
        case elem_missingglyph :
        case elem_vkern :
            return elem_font;
        case elem_fontfaceformat :
            return elem_fontfaceuri;
        case elem_fontfacename :
        case elem_fontfaceuri :
            return elem_fontfacesrc;
        case elem_fontfacesrc :
            return elem_fontface;
        case elem_foreignobject :
            return elem_filter;
        case elem_handler :
            return elem_use;
        case elem_image :
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
        case elem_mtr:
            return elem_mtable;
        case elem_col :
            if (v.major () >= 5) return elem_colgroup;
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
        case elem_page :
            return elem_pageset;
        case elem_param :
            if (v.major () == 3) return elem_applet;
            return elem_object;
        case elem_prototype :
            return elem_elementdef;
        case elem_rb :
        case elem_rbc :
        case elem_rp :
        case elem_rt :
        case elem_rtc :
            return elem_ruby;
        case elem_td :
        case elem_th :
            return elem_tr;
        case elem_tr :
            if (v.major () == 3) return elem_table;
            return elem_tbody;
        case elem_row :
            return elem_array;
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
