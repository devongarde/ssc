/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "base/type_master.h"
#include "base/type_case.h"
#include "spell/spell.h"

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 > class four_value : public type_base < base_type, TYPE >
{   base_type value_ = static_cast < base_type > (0);
    static ::std::string a_, b_, c_, d_;
public:
    typedef true_type has_int_type;
    using type_base < base_type, TYPE > :: type_base;
    static void init ();
    static e_animation_type animation_type () noexcept { return at_other; }
    ::std::string get_string () const;
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void swap (four_value& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < base_type, TYPE >::swap (t); }
    static base_type default_value () { return static_cast <base_type> (0); }
    base_type get () const noexcept { return value_; }
    int get_int () const { return static_cast < int > (value_); }
    ::std::size_t type () const noexcept { return static_cast < ::std::size_t > (get ()); }
    bool has_value (const base_type& b) const { return type_base < base_type, TYPE > :: good () && (value_ == b); } };

template < > struct type_master < t_actiontype2 > : four_value < t_actiontype2, e_actiontype, sz_toggle, sz_statusline, sz_tooltip, sz_highlight >
{ using four_value < t_actiontype2, e_actiontype, sz_toggle, sz_statusline, sz_tooltip, sz_highlight > :: four_value; };

template < > struct type_master < t_align2070 > : four_value < t_align2070, e_align2070, sz_centre, sz_justify, sz_left, sz_right >
{ using four_value < t_align2070, e_align2070, sz_centre, sz_justify, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_aligndec > : four_value < t_aligndec, e_aligndec, sz_centre, sz_decimal, sz_left, sz_right >
{ using four_value < t_aligndec, e_aligndec, sz_centre, sz_decimal, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_alignfig > : four_value < t_alignfig, e_alignfig, sz_centre, sz_float, sz_left, sz_right >
{ using four_value < t_alignfig, e_alignfig, sz_centre, sz_float, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_arabicenum > : four_value < t_arabicenum, e_arabicenum, sz_initial, sz_medial, sz_terminal, sz_isolated >
{ using four_value < t_arabicenum, e_arabicenum, sz_initial, sz_medial, sz_terminal, sz_isolated > :: four_value; };

template < > struct type_master < t_aria_autocomplete > : four_value < t_aria_autocomplete, e_aria_autocomplete, sz_both, sz_inline, sz_list, sz_none >
{ using four_value < t_aria_autocomplete, e_aria_autocomplete, sz_both, sz_inline, sz_list, sz_none > :: four_value; };

template < > struct type_master < t_aria_invalidity > : four_value < t_aria_invalidity, e_aria_invalidity, sz_false, sz_grammar, sz_spelling, sz_true >
{ using four_value < t_aria_invalidity, e_aria_invalidity, sz_false, sz_grammar, sz_spelling, sz_true > :: four_value; };

template < > struct type_master < t_aria_sort > : four_value < t_aria_sort, e_aria_sort, sz_ascending, sz_descending, sz_none, sz_other >
{ using four_value < t_aria_sort, e_aria_sort, sz_ascending, sz_descending, sz_none, sz_other> :: four_value; };

template < > struct type_master < t_bens > : four_value < t_bens, e_bens, sz_both, sz_end, sz_none, sz_start >
{ using four_value < t_bens, e_bens, sz_both, sz_end, sz_none, sz_start > :: four_value; };

template < > struct type_master < t_buffered_rendering > : four_value < t_buffered_rendering, e_buffered_rendering, sz_auto, sz_dynamic, sz_static, sz_inherit >
{ using four_value < t_buffered_rendering, e_buffered_rendering, sz_auto, sz_dynamic, sz_static, sz_inherit > :: four_value; };

template < > struct type_master < t_calcmode > : four_value < t_calcmode, e_calcmode, sz_discrete, sz_linear, sz_paced, sz_spline >
{ using four_value < t_calcmode, e_calcmode, sz_discrete, sz_linear, sz_paced, sz_spline > :: four_value; };

template < > struct type_master < t_captionalign > : four_value < t_captionalign, e_captionalign, sz_bottom, sz_left, sz_right, sz_top >
{ using four_value < t_captionalign, e_captionalign, sz_bottom, sz_left, sz_right, sz_top > :: four_value; };

template < > struct type_master < t_cc_requires > : four_value < t_cc_requires, e_cc_requires, sz_cc_attribution, sz_cc_notice, sz_cc_sharealike, sz_cc_sourcecode >
{ using four_value < t_cc_requires, e_cc_requires, sz_cc_attribution, sz_cc_notice, sz_cc_sharealike, sz_cc_sourcecode > :: four_value; };

template < > struct type_master < t_cens > : four_value < t_cens, e_cens, sz_centre, sz_end, sz_none, sz_start >
{ using four_value < t_cens, e_cens, sz_centre, sz_end, sz_none, sz_start > :: four_value; };

template < > struct type_master < t_channelselector > : four_value < t_channelselector, e_channelselector, sz_a, sz_b, sz_g, sz_r >
{ using four_value < t_channelselector, e_channelselector, sz_a, sz_b, sz_g, sz_r > :: four_value; };

template < > struct type_master < t_content_encoding > : four_value < t_content_encoding, e_content_encoding, sz_gzip, sz_compress, sz_deflate, sz_identity >
{ using four_value < t_content_encoding, e_content_encoding, sz_gzip, sz_compress, sz_deflate, sz_identity > :: four_value; };

template < > struct type_master < t_crs_tonecurvename > : four_value < t_crs_tonecurvename, e_crs_tonecurvename, sz_custom, sz_linear, sz_mediumcontrast, sz_strongcontrast >
{ using four_value < t_crs_tonecurvename, e_crs_tonecurvename, sz_custom, sz_linear, sz_mediumcontrast, sz_strongcontrast > :: four_value; };

template < > struct type_master < t_css_anim_dir > : four_value < t_css_anim_dir, e_css_anim_dir, sz_alternate, sz_alternate_reverse, sz_normal, sz_reverse >
{ using four_value < t_css_anim_dir, e_css_anim_dir, sz_alternate, sz_alternate_reverse, sz_normal, sz_reverse > :: four_value; };

template < > struct type_master < t_css_anim_fill_mode > : four_value < t_css_anim_fill_mode, e_anim_fill_mode, sz_backwards, sz_both, sz_forwards, sz_none >
{ using four_value < t_css_anim_fill_mode, e_anim_fill_mode, sz_backwards, sz_both, sz_forwards, sz_none > :: four_value; };

template < > struct type_master < t_css_border_image_repeat > : four_value < t_css_border_image_repeat, e_css_border_image_repeat, sz_repeat, sz_round, sz_space_word, sz_stretch >
{ using four_value < t_css_border_image_repeat, e_css_border_image_repeat, sz_repeat, sz_round, sz_space_word, sz_stretch > :: four_value; };

template < > struct type_master < t_css_box_orient > : four_value < t_css_box_orient, e_css_box_orient, sz_block_axis, sz_horizontal, sz_inline_axis, sz_vertical >
{ using four_value < t_css_box_orient, e_css_box_orient, sz_block_axis, sz_horizontal, sz_inline_axis, sz_vertical > :: four_value; };

template < > struct type_master < t_css_composite > : four_value < t_css_composite, e_css_composite, sz_add, sz_exclude, sz_intersect, sz_subtract >
{ using four_value < t_css_composite, e_css_composite, sz_add, sz_exclude, sz_intersect, sz_subtract > :: four_value; };

template < > struct type_master < t_css_display_legacy > : four_value < t_css_display_legacy, e_css_display_legacy, sz_inline_block, sz_inline_flex, sz_inline_grid, sz_inline_table >
{ using four_value < t_css_display_legacy, e_css_display_legacy, sz_inline_block, sz_inline_flex, sz_inline_grid, sz_inline_table > :: four_value; };

template < > struct type_master < t_css_flex_direction > : four_value < t_css_flex_direction, e_css_flex_direction, sz_column, sz_column_reverse, sz_row, sz_row_reverse >
{ using four_value < t_css_flex_direction, e_css_flex_direction, sz_column, sz_column_reverse, sz_row, sz_row_reverse > :: four_value; };

template < > struct type_master < t_css_fn_round_t > : four_value < t_css_fn_round_t, e_css_fn_round_t, sz_down, sz_nearest, sz_to_zero, sz_up >
{ using four_value < t_css_fn_round_t, e_css_fn_round_t, sz_down, sz_nearest, sz_to_zero, sz_up > :: four_value; };

template < > struct type_master < t_css_font_style_e > : four_value < t_css_font_style_e, e_css_font_style_e, sz_normal, sz_italic, sz_oblique, sz_inherit >
{ using four_value < t_css_font_style_e, e_css_font_style_e, sz_normal, sz_italic, sz_oblique, sz_inherit > :: four_value; };

template < > struct type_master < t_css_hue_interpolation > : four_value < t_css_hue_interpolation, e_css_hue_interpolation, sz_decreasing, sz_increasing, sz_longer, sz_shorter >
{ using four_value < t_css_hue_interpolation, e_css_hue_interpolation, sz_decreasing, sz_increasing, sz_longer, sz_shorter > :: four_value; };

template < > struct type_master < t_css_initial_letter_align > : four_value < t_css_initial_letter_align, e_css_initial_letter_align, sz_alphabetic, sz_hanging, sz_ideographic, sz_leading >
{ using four_value < t_css_initial_letter_align, e_css_initial_letter_align, sz_alphabetic, sz_hanging, sz_ideographic, sz_leading > :: four_value; };

template < > struct type_master < t_css_initial_letter_wrap_e > : four_value < t_css_initial_letter_wrap_e, e_css_initial_letter_wrap_e, sz_all, sz_first, sz_grid, sz_none >
{ using four_value < t_css_initial_letter_wrap_e, e_css_initial_letter_wrap_e, sz_all, sz_first, sz_grid, sz_none > :: four_value; };

template < > struct type_master < t_css_margin_trim_inner > : four_value < t_css_margin_trim_inner, e_css_margin_trim_inner, sz_block_end, sz_block_start, sz_inline_end, sz_inline_start >
{ using four_value < t_css_margin_trim_inner, e_css_margin_trim_inner, sz_block_end, sz_block_start, sz_inline_end, sz_inline_start > :: four_value; };

template < > struct type_master < t_css_mask_border_repeat > : four_value < t_css_mask_border_repeat, e_css_mask_border_repeat, sz_repeat, sz_round, sz_space_word, sz_stretch >
{ using four_value < t_css_mask_border_repeat, e_css_mask_border_repeat, sz_repeat, sz_round, sz_space_word, sz_stretch > :: four_value; };

template < > struct type_master < t_css_orientation > : four_value < t_css_orientation, e_css_orientation, sz_auto, sz_inherit, sz_landscape, sz_portrait >
{ using four_value < t_css_orientation, e_css_orientation, sz_auto, sz_inherit, sz_landscape, sz_portrait > :: four_value; };

template < > struct type_master < t_css_polar > : four_value < t_css_polar, e_css_polar, sz_hsl, sz_hwb, sz_lch, sz_oklch >
{ using four_value < t_css_polar, e_css_polar, sz_hsl, sz_hwb, sz_lch, sz_oklch > :: four_value; };

template < > struct type_master < t_css_radial_size > : four_value < t_css_radial_size, e_css_radial_size, sz_closest_corner, sz_closest_side, sz_farthest_corner, sz_farthest_side >
{ using four_value < t_css_radial_size, e_css_radial_size, sz_closest_corner, sz_closest_side, sz_farthest_corner, sz_farthest_side > :: four_value; };

template < > struct type_master < t_css_shape_box > : four_value < t_css_shape_box, e_css_shape_box, sz_border_box, sz_content_box, sz_margin_box, sz_padding_box >
{ using four_value < t_css_shape_box, e_css_shape_box, sz_border_box, sz_content_box, sz_margin_box, sz_padding_box > :: four_value; };

template < > struct type_master < t_css_speak_2 > : four_value < t_css_speak_2, e_css_speak_2, sz_inherit, sz_none, sz_normal, sz_spell_out >
{ using four_value < t_css_speak_2, e_css_speak_2, sz_inherit, sz_none, sz_normal, sz_spell_out > :: four_value; };

template < > struct type_master < t_css_textemph_skip > : four_value < t_css_textemph_skip, e_css_textemph_skip, sz_narrow, sz_punctuation, sz_spaces, sz_symbols >
{ using four_value < t_css_textemph_skip, e_css_textemph_skip, sz_narrow, sz_punctuation, sz_spaces, sz_symbols > :: four_value; };

template < > struct type_master < t_css_text_justify > : four_value < t_css_text_justify, e_css_text_justify, sz_auto, sz_inter_character, sz_inter_word, sz_none >
{ using four_value < t_css_text_justify, e_css_text_justify, sz_auto, sz_inter_character, sz_inter_word, sz_none > :: four_value; };

template < > struct type_master < t_css_val_con > : four_value < t_css_val_con, e_css_val_con, sz_e, sz_infinity, sz_nan, sz_pi >
{ using four_value < t_css_val_con, e_css_val_con, sz_e, sz_infinity, sz_nan, sz_pi > :: four_value; };

template < > struct type_master < t_css_word_break > : four_value < t_css_word_break, e_css_word_break, sz_break_all, sz_break_word, sz_keep_all, sz_normal >
{ using four_value < t_css_word_break, e_css_word_break, sz_break_all, sz_break_word, sz_keep_all, sz_normal > :: four_value; };

template < > struct type_master < t_device > : four_value < t_device, e_device, sz_media, sz_fs, sz_rs232, sz_usb >
{ using four_value < t_device, e_device, sz_media, sz_fs, sz_rs232, sz_usb > :: four_value; };

template < > struct type_master < t_edit > : four_value < t_edit, e_edit, sz_changed, sz_deleted, sz_inserted, sz_moved >
{ using four_value < t_edit, e_edit, sz_changed, sz_deleted, sz_inserted, sz_moved > :: four_value; };

template < > struct type_master < t_effect > : four_value < t_effect, e_effect, sz_embed, sz_overlay, sz_replace, sz_new >
{ using four_value < t_effect, e_effect, sz_embed, sz_overlay, sz_replace, sz_new > :: four_value; };

template < > struct type_master < t_font_variant_emoji > : four_value < t_font_variant_emoji, e_font_variant_emoji, sz_auto, sz_emoji, sz_text, sz_unicode >
{ using four_value < t_font_variant_emoji, e_font_variant_emoji, sz_auto, sz_emoji, sz_text, sz_unicode > :: four_value; };

template < > struct type_master < t_frame4 > : four_value < t_frame4, e_frame4, sz__blank, sz__parent, sz__self, sz__top >
{ using four_value < t_frame4, e_frame4, sz__blank, sz__parent, sz__self, sz__top > :: four_value; };

template < > struct type_master < t_intent_hint > : four_value < t_intent_hint, e_intent_hint, sz_infix, sz_postfix, sz_prefix, sz_silent >
{ using four_value < t_intent_hint, e_intent_hint, sz_infix, sz_postfix, sz_prefix, sz_silent > :: four_value; };

template < > struct type_master < t_larnalign > : four_value < t_larnalign, e_larnalign, sz_left, sz_all, sz_right, sz_none >
{ using four_value < t_larnalign, e_larnalign, sz_left, sz_all, sz_right, sz_none > :: four_value; };

template < > struct type_master < t_lcrnalign > : four_value < t_lcrnalign, e_lcrnalign, sz_left, sz_centre, sz_right, sz_none >
{ using four_value < t_lcrnalign, e_lcrnalign, sz_left, sz_centre, sz_right, sz_none > :: four_value; };

template < > struct type_master < t_lcrd > : four_value < t_lcrd, e_lcrd, sz_left, sz_centre, sz_right, sz_decimalpoint >
{ using four_value < t_lcrd, e_lcrd, sz_left, sz_centre, sz_right, sz_decimalpoint > :: four_value; };

template < > struct type_master < t_linebreakstyle > : four_value < t_linebreakstyle, e_linebreakstyle, sz_before, sz_after, sz_duplicate, sz_infixlinebreakstyle >
{ using four_value < t_linebreakstyle, e_linebreakstyle, sz_before, sz_after, sz_duplicate, sz_infixlinebreakstyle > :: four_value; };

template < > struct type_master < t_linecap > : four_value < t_linecap, e_linecap, sz_butt, sz_round, sz_square, sz_inherit >
{ using four_value < t_linecap, e_linecap, sz_butt, sz_round, sz_square, sz_inherit > :: four_value; };

template < > struct type_master < t_linejoin > : four_value < t_linejoin, e_linejoin, sz_miter, sz_round, sz_bevel, sz_inherit >
{ using four_value < t_linejoin, e_linejoin, sz_miter, sz_round, sz_bevel, sz_inherit > :: four_value; };

template < > struct type_master < t_mathclosure > : four_value < t_mathclosure, e_mathclosure, sz_open, sz_closed, sz_openclosed, sz_closedopen >
{ using four_value < t_mathclosure, e_mathclosure, sz_open, sz_closed, sz_openclosed, sz_closedopen > :: four_value; };

template < > struct type_master < t_mathside > : four_value < t_mathside, e_mathside, sz_left, sz_right, sz_leftoverlap, sz_rightoverlap >
{ using four_value < t_mathside, e_mathside, sz_left, sz_right, sz_leftoverlap, sz_rightoverlap > :: four_value; };

template < > struct type_master < t_media_display_mode > : four_value < t_media_display_mode, e_media_display_mode, sz_browser, sz_fullscreen, sz_minimal_ui, sz_standalone >
{ using four_value < t_media_display_mode, e_media_display_mode, sz_browser, sz_fullscreen, sz_minimal_ui, sz_standalone > :: four_value; };

template < > struct type_master < t_media_prefers_2 > : four_value < t_media_prefers_2, e_media_prefers_2, sz_custom, sz_less, sz_no_preference, sz_more >
{ using four_value < t_media_prefers_2, e_media_prefers_2, sz_custom, sz_less, sz_no_preference, sz_more > :: four_value; };

template < > struct type_master < t_mf_availability > : four_value < t_mf_availability, e_mf_availability, sz_out_of_stock, sz_in_stock, sz_instore_only, sz_preorder >
{ using four_value < t_mf_availability, e_mf_availability, sz_out_of_stock, sz_in_stock, sz_instore_only, sz_preorder > :: four_value; };

template < > struct type_master < t_mf_category > : four_value < t_mf_category, e_mf_category, sz_meeting, sz_appointment, sz_conference, sz_expo >
{ using four_value < t_mf_category, e_mf_category, sz_meeting, sz_appointment, sz_conference, sz_expo > :: four_value; };

template < > struct type_master < t_paint_order > : four_value < t_paint_order, e_paint_order, sz_normal, sz_fill, sz_stroke, sz_markers >
{ using four_value < t_paint_order, e_paint_order, sz_normal, sz_fill, sz_stroke, sz_markers > :: four_value; };

template < > struct type_master < t_pam_status > : four_value < t_pam_status, e_pam_status, sz_a, sz_c, sz_d, sz_u >
{ using four_value < t_pam_status, e_pam_status, sz_a, sz_c, sz_d, sz_u > :: four_value; };

template < > struct type_master < t_phase_x > : four_value < t_phase_x, e_phase_x, sz_bubble, sz_capture, sz_default, sz_target >
{ using four_value < t_phase_x, e_phase_x, sz_bubble, sz_capture, sz_default, sz_target > :: four_value; };

template < > struct type_master < t_pri_img_season > : four_value < t_pri_img_season, e_pri_img_season, sz_fall, sz_spring, sz_summer, sz_winter >
{ using four_value < t_pri_img_season, e_pri_img_season, sz_fall, sz_spring, sz_summer, sz_winter > :: four_value; };

template < > struct type_master < t_prism_tablet_ad > : four_value < t_prism_tablet_ad, e_prism_tablet_ad, sz_dfp, sz_efp, sz_sfp, sz_sfpplus >
{ using four_value < t_prism_tablet_ad, e_prism_tablet_ad, sz_dfp, sz_efp, sz_sfp, sz_sfpplus > :: four_value; };

template < > struct type_master < t_prs_duty > : four_value < t_prs_duty, e_prs_duty, sz_compensate, sz_credit, sz_include, sz_inform >
{ using four_value < t_prs_duty, e_prs_duty, sz_compensate, sz_credit, sz_include, sz_inform > :: four_value; };

template < > struct type_master < t_recipe_skill > : four_value < t_recipe_skill, e_recipe_skill, sz_children, sz_easy, sz_expert, sz_moderate >
{ using four_value < t_recipe_skill, e_recipe_skill, sz_children, sz_easy, sz_expert, sz_moderate > :: four_value; };

template < > struct type_master < t_rsvp > : four_value < t_rsvp, e_rsvp, sz_yes, sz_no, sz_maybe, sz_interested >
{ using four_value < t_rsvp, e_rsvp, sz_yes, sz_no, sz_maybe, sz_interested > :: four_value; };

template < > struct type_master < t_tdscope > : four_value < t_tdscope, e_tdscope, sz_row, sz_col, sz_rowgroup, sz_colgroup >
{ using four_value < t_tdscope, e_tdscope, sz_row, sz_col, sz_rowgroup, sz_colgroup > :: four_value; };

template < > struct type_master < t_shadowinherit > : four_value < t_shadowinherit, e_shadowinherit, sz_ondefine, sz_onuse, sz_none, sz_inherit >
{ using four_value < t_shadowinherit, e_shadowinherit, sz_ondefine, sz_onuse, sz_none, sz_inherit > :: four_value; };

template < > struct type_master < t_shape4 > : four_value < t_shape4, e_shape4, sz_circle, sz_default, sz_poly, sz_rect >
{ using four_value < t_shape4, e_shape4, sz_circle, sz_default, sz_poly, sz_rect > :: four_value; };

template < > struct type_master < t_size3 > : four_value < t_size3, e_size3, sz_normal, sz_medium, sz_large, sz_huge >
{ using four_value < t_size3, e_size3, sz_normal, sz_medium, sz_large, sz_huge > :: four_value; };

template < > struct type_master < t_ssi_config > : four_value < t_ssi_config, e_ssi_config, sz_echomsg, sz_errmsg, sz_sizefmt, sz_timefmt >
{ using four_value < t_ssi_config, e_ssi_config, sz_echomsg, sz_errmsg, sz_sizefmt, sz_timefmt > :: four_value; };

template < > struct type_master < t_ssi_set > : four_value < t_ssi_set, e_ssi_set, sz_decoding, sz_encoding, sz_value, sz_var >
{ using four_value < t_ssi_set, e_ssi_set, sz_decoding, sz_encoding, sz_value, sz_var > :: four_value; };

template < > struct type_master < t_svg_baseprofile > : four_value < t_svg_baseprofile, e_svg_baseprofile, sz_basic, sz_full, sz_none, sz_tiny >
{ using four_value < t_svg_baseprofile, e_svg_baseprofile, sz_basic, sz_full, sz_none, sz_tiny > :: four_value; };

template < > struct type_master < t_syncbehaviour > : four_value < t_syncbehaviour, e_syncbehaviour, sz_canslip, sz_locked, sz_independent, sz_default >
{ using four_value < t_syncbehaviour, e_syncbehaviour, sz_canslip, sz_locked, sz_independent, sz_default > :: four_value; };

template < > struct type_master < t_syncbehaviourdefault > : four_value < t_syncbehaviourdefault, e_syncbehaviourdefault, sz_canslip, sz_locked, sz_independent, sz_inherit >
{ using four_value < t_syncbehaviourdefault, e_syncbehaviourdefault, sz_canslip, sz_locked, sz_independent, sz_inherit > :: four_value; };

template < > struct type_master < t_tfmu > : four_value < t_tfmu, e_tfmu, sz_false, sz_mixed, sz_true, sz_undefined >
{ using four_value < t_tfmu, e_tfmu, sz_false, sz_mixed, sz_true, sz_undefined > :: four_value; };

template < > struct type_master < t_uplr > : four_value < t_uplr, e_uplr, sz_down, sz_left, sz_right, sz_up >
{ using four_value < t_uplr, e_uplr, sz_down, sz_left, sz_right, sz_up > :: four_value; };

template < > struct type_master < t_user_modify > : four_value < t_user_modify, e_user_modify, sz_read_only, sz_read_write, sz_read_write_plaintext_only, sz_write_only >
{ using four_value < t_user_modify, e_user_modify, sz_read_only, sz_read_write, sz_read_write_plaintext_only, sz_write_only > :: four_value; };

template < > struct type_master < t_valign3 > : four_value < t_valign3, e_valign3, sz_top, sz_middle, sz_bottom, sz_baseline >
{ using four_value < t_valign3, e_valign3, sz_top, sz_middle, sz_bottom, sz_baseline > :: four_value; };

template < > struct type_master < t_visibility11 > : four_value < t_visibility11, e_visibility11, sz_visible, sz_hidden, sz_collapse, sz_inherit >
{ using four_value < t_visibility11, e_visibility11, sz_visible, sz_hidden, sz_collapse, sz_inherit > :: four_value; };

template < > struct type_master < t_vkind > : four_value < t_vkind, e_vkind, sz_individual, sz_organisation, sz_group, sz_location >
{ using four_value < t_vkind, e_vkind, sz_individual, sz_organisation, sz_group, sz_location > :: four_value; };

template < > struct type_master < t_xmpdm_type > : four_value < t_xmpdm_type, e_xmpdm_type, sz_audio, sz_custom, sz_movie, sz_still >
{ using four_value < t_xmpdm_type, e_xmpdm_type, sz_audio, sz_custom, sz_movie, sz_still > :: four_value; };

template < > struct type_master < t_xmpdm_scaletype > : four_value < t_xmpdm_scaletype, e_xmpdm_scaletype, sz_both, sz_major, sz_minor, sz_neither >
{ using four_value < t_xmpdm_scaletype, e_xmpdm_scaletype, sz_both, sz_major, sz_minor, sz_neither > :: four_value; };

template < > struct type_master < t_xsdbool > : four_value < t_xsdbool, e_xsdbool, sz_0, sz_1, sz_false, sz_true >
{ using four_value < t_xsdbool, e_xsdbool, sz_0, sz_1, sz_false, sz_true > :: four_value; };


template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: get_string () const
{   if (! type_base < base_type, TYPE > :: unknown ())
        switch (static_cast <int> (value_))
        {   case 0 : return SZ0::sz ();
            case 1 : return SZ1::sz ();
            case 2 : return SZ2::sz ();
            case 3 : return SZ3::sz ();
            default : break; }
    return ::std::string (); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    void four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: init ()
{   a_ = ::boost::to_lower_copy (::std::string (SZ0::sz ()));
    b_ = ::boost::to_lower_copy (::std::string (SZ1::sz ()));
    c_ = ::boost::to_lower_copy (::std::string (SZ2::sz ()));
    d_ = ::boost::to_lower_copy (::std::string (SZ3::sz ())); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    void four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string pret (trim_the_lot_off (s));
    ::std::string t (case_must_match < false >::lower (pret));
    type_base < base_type, TYPE > :: status (s_good);
    PRESUME (! a_.empty (), __FILE__, __LINE__);
    if (t == a_) value_ = static_cast <base_type> (0);
    else if (t == b_) value_ = static_cast <base_type> (1);
    else if (t == c_) value_ = static_cast <base_type> (2);
    else if (t == d_) value_ = static_cast <base_type> (3);
    else
    {   if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "attribute cannot have an empty value (", type_name (TYPE), ")");
        else if (! check_identifier_spelling (nits, v, t))
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid; it can be ", quote (SZ0::sz ()), ", ", quote (SZ1::sz ()), ", ", quote (SZ2::sz ()), ", or ", quote (SZ3::sz ()));
        type_base < base_type, TYPE > :: status (s_invalid);
        return; }
    compare_validate (nits, v, get_string (), pret); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: a_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: b_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: c_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: d_;
