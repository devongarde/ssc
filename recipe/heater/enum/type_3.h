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

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE = false > class three_value : public type_base < base_type, TYPE >
{   base_type value_ = static_cast < base_type > (0);
    static ::std::string a_, b_, c_;
public:
    typedef true_type has_int_type;
    using type_base < base_type, TYPE > :: type_base;
    static void init ();
    static e_animation_type animation_type () noexcept
    {   return at_other; }
    ::std::string get_string () const;
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void swap (three_value& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < base_type, TYPE >::swap (t); }
    static base_type default_value ()
    {   return static_cast <base_type> (0); }
    base_type get () const noexcept
    {   return value_; }
    int get_int () const noexcept
    {   return static_cast < int > (value_); }
    bool has_value (const base_type& b) const
    {   return type_base < base_type, TYPE > :: good () && (value_ == b); }
    ::std::size_t type () const noexcept
    {   return static_cast < ::std::size_t > (get ()); } };

template < > struct type_master < t_aria_live > : three_value < t_aria_live, e_aria_live, sz_assertive, sz_off, sz_polite >
{ using three_value < t_aria_live, e_aria_live, sz_assertive, sz_off, sz_polite > :: three_value; };

template < > struct type_master < t_attributetype > : three_value < t_attributetype, e_attributetype, sz_auto, sz_CSS, sz_XML >
{ using three_value < t_attributetype, e_attributetype, sz_auto, sz_CSS, sz_XML > :: three_value; };

template < > struct type_master < t_behaviour > : three_value < t_behaviour, e_behaviour, sz_alternate, sz_scroll, sz_slide >
{ using three_value < t_behaviour, e_behaviour, sz_alternate, sz_scroll, sz_slide > :: three_value; };

template < > struct type_master < t_button > : three_value < t_button, e_button, sz_button, sz_submit, sz_reset >
{ using three_value < t_button, e_button, sz_button, sz_submit, sz_reset > :: three_value; };

template < > struct type_master < t_cc_permits > : three_value < t_cc_permits, e_cc_permits, sz_cc_derivativeworks, sz_cc_distribution, sz_cc_reproduction >
{ using three_value < t_cc_permits, e_cc_permits, sz_cc_derivativeworks, sz_cc_distribution, sz_cc_reproduction > :: three_value; };

template < > struct type_master < t_command > : three_value < t_command, e_command, sz_command, sz_checkbox, sz_radio >
{ using three_value < t_command, e_command, sz_command, sz_checkbox, sz_radio > :: three_value; };

template < > struct type_master < t_colour_space > : three_value < t_colour_space, e_colour_space, sz_cmyk, sz_rgb, sz_lab >
{ using three_value < t_colour_space, e_colour_space, sz_cmyk, sz_rgb, sz_lab > :: three_value; };

template < > struct type_master < t_controlslist > : three_value < t_controlslist, e_controlslist, sz_nodownload, sz_nofullscreen, sz_noremoteplayback >
{ using three_value < t_controlslist, e_controlslist, sz_nodownload, sz_nofullscreen, sz_noremoteplayback > :: three_value; };

template < > struct type_master < t_corp > : three_value < t_corp, e_corp, sz_same_origin, sz_same_site, sz_cross_origin, true >
{ using three_value < t_corp, e_corp, sz_same_origin, sz_same_site, sz_cross_origin, true > :: three_value; };

template < > struct type_master < t_css_aai > : three_value < t_css_aai, e_css_aai, sz_auto, sz_avoid, sz_inherit >
{ using three_value < t_css_aai, e_css_aai, sz_auto, sz_avoid, sz_inherit > :: three_value; };

template < > struct type_master < t_css_anim_comp > : three_value < t_css_anim_comp, e_css_anim_comp, sz_accumulate, sz_add, sz_replace >
{ using three_value < t_css_anim_comp, e_css_anim_comp, sz_accumulate, sz_add, sz_replace > :: three_value; };

template < > struct type_master < t_css_azimuth_lri > : three_value < t_css_azimuth_lri, e_css_azimuth_lri, sz_leftwards, sz_inherit, sz_rightwards >
{ using three_value < t_css_azimuth_lri, e_css_azimuth_lri, sz_leftwards, sz_inherit, sz_rightwards > :: three_value; };

template < > struct type_master < t_css_border_collapse > : three_value < t_css_border_collapse, e_css_border_collapse, sz_collapse, sz_inherit, sz_separate >
{ using three_value < t_css_border_collapse, e_css_border_collapse, sz_collapse, sz_inherit, sz_separate > :: three_value; };

template < > struct type_master < t_css_column_fill > : three_value < t_css_column_fill, e_css_column_fill, sz_auto, sz_balance, sz_balance_all >
{ using three_value < t_css_column_fill, e_css_column_fill, sz_auto, sz_balance, sz_balance_all > :: three_value; };

template < > struct type_master < t_css_display_outside > : three_value < t_css_display_outside, e_css_display_outside, sz_block, sz_inline, sz_run_in >
{ using three_value < t_css_display_outside, e_css_display_outside, sz_block, sz_inline, sz_run_in > :: three_value; };

template < > struct type_master < t_css_empty_cells > : three_value < t_css_empty_cells, e_css_empty_cells, sz_hide, sz_inherit, sz_show >
{ using three_value < t_css_empty_cells, e_css_empty_cells, sz_hide, sz_inherit, sz_show > :: three_value; };

template < > struct type_master < t_css_flex_wrap > : three_value < t_css_flex_wrap, e_css_flex_wrap, sz_nowrap, sz_wrap, sz_wrap_reverse >
{ using three_value < t_css_flex_wrap, e_css_flex_wrap, sz_nowrap, sz_wrap, sz_wrap_reverse > :: three_value; };

template < > struct type_master < t_css_font_kerning > : three_value < t_css_font_kerning, e_css_font_kerning, sz_auto, sz_none, sz_normal >
{ using three_value < t_css_font_kerning, e_css_font_kerning, sz_auto, sz_none, sz_normal > :: three_value; };

template < > struct type_master < t_css_margin_break > : three_value < t_css_margin_break, e_css_margin_break, sz_auto, sz_discard, sz_keep >
{ using three_value < t_css_margin_break, e_css_margin_break, sz_auto, sz_discard, sz_keep > :: three_value; };

template < > struct type_master < t_css_speak_header > : three_value < t_css_speak_header, e_css_speak_header, sz_always, sz_inherit, sz_once >
{ using three_value < t_css_speak_header, e_css_speak_header, sz_always, sz_inherit, sz_once > :: three_value; };

template < > struct type_master < t_css_speak_numeral > : three_value < t_css_speak_numeral, e_css_speak_numeral, sz_continuous, sz_digits, sz_inherit >
{ using three_value < t_css_speak_numeral, e_css_speak_numeral, sz_continuous, sz_digits, sz_inherit > :: three_value; };

template < > struct type_master < t_css_speak_punctuation > : three_value < t_css_speak_punctuation, e_css_speak_punctuation, sz_code, sz_inherit, sz_none >
{ using three_value < t_css_speak_punctuation, e_css_speak_punctuation, sz_code, sz_inherit, sz_none > :: three_value; };

template < > struct type_master < t_css_table_layout > : three_value < t_css_table_layout, e_css_table_layout, sz_auto, sz_fixed, sz_inherit >
{ using three_value < t_css_table_layout, e_css_table_layout, sz_auto, sz_fixed, sz_inherit > :: three_value; };

template < > struct type_master < t_css_text_orientation > : three_value < t_css_text_orientation, e_css_text_orientation, sz_mixed, sz_sideways, sz_upright >
{ using three_value < t_css_text_orientation, e_css_text_orientation, sz_mixed, sz_sideways, sz_upright > :: three_value; };

template < > struct type_master < t_csvw_direction > : three_value < t_csvw_direction, e_csvw_direction, sz_ltr, sz_rtl, sz_auto >
{ using three_value < t_csvw_direction, e_csvw_direction, sz_ltr, sz_rtl, sz_auto > :: three_value; };

template < > struct type_master < t_decoding > : three_value < t_decoding, e_decoding, sz_auto, sz_sync, sz_async >
{ using three_value < t_decoding, e_decoding, sz_auto, sz_sync, sz_async > :: three_value; };

template < > struct type_master < t_dsc > : three_value < t_dsc, e_dsc, sz_disc, sz_square, sz_circle >
{ using three_value < t_dsc, e_dsc, sz_disc, sz_square, sz_circle > :: three_value; };

template < > struct type_master < t_edgemode > : three_value < t_edgemode, e_edgemode, sz_duplicate, sz_wrap, sz_none >
{ using three_value < t_edgemode, e_edgemode, sz_duplicate, sz_wrap, sz_none > :: three_value; };

template < > struct type_master < t_edi > : three_value < t_edi, e_edi, sz_enable, sz_disable, sz_inherit >
{ using three_value < t_edi, e_edi, sz_enable, sz_disable, sz_inherit > :: three_value; };

template < > struct type_master < t_enctype > : three_value < t_enctype, e_enctype, sz_app_urlencoded, sz_multipart_form_data, sz_text_plain >
{ using three_value < t_enctype, e_enctype, sz_app_urlencoded, sz_multipart_form_data, sz_text_plain > :: three_value; };

template < > struct type_master < t_environment_blending > : three_value < t_environment_blending, e_environment_blending, sz_additive, sz_opaque, sz_subtractive >
{ using three_value < t_environment_blending, e_environment_blending, sz_additive, sz_opaque, sz_subtractive > :: three_value; };

// typedef enum { eii_r03, eii_r98, eii_thm } e_exif_intind;
template < > struct type_master < t_exif_intind > : three_value < t_exif_intind, e_exif_intind, sz_r03, sz_r98, sz_thm >
{ using three_value < t_exif_intind, e_exif_intind, sz_r03, sz_r98, sz_thm > :: three_value; };

template < > struct type_master < t_fill_rule > : three_value < t_fill_rule, e_fill_rule, sz_nonzero, sz_evenodd, sz_inherit >
{ using three_value < t_fill_rule, e_fill_rule, sz_nonzero, sz_evenodd, sz_inherit > :: three_value; };

template < > struct type_master < t_fontnia > : three_value < t_fontnia, e_fontnia, sz_normal, sz_italic, sz_oblique >
{ using three_value < t_fontnia, e_fontnia, sz_normal, sz_italic, sz_oblique > :: three_value; };

template < > struct type_master < t_font_variant_position > : three_value < t_font_variant_position, e_font_variant_position, sz_normal, sz_sub, sz_super >
{ using three_value < t_font_variant_position, e_font_variant_position, sz_normal, sz_sub, sz_super > :: three_value; };

template < > struct type_master < t_gamut > : three_value < t_gamut, e_gamut, sz_p3, sz_rec2020, sz_srgb >
{ using three_value < t_gamut, e_gamut, sz_p3, sz_rec2020, sz_srgb > :: three_value; };

template < > struct type_master < t_importance > : three_value < t_importance, e_importance, sz_auto, sz_high, sz_low >
{ using three_value < t_importance, e_importance, sz_auto, sz_high, sz_low > :: three_value; };

template < > struct type_master < t_infixlinebreakstyle > : three_value < t_infixlinebreakstyle, e_infixlinebreakstyle, sz_before, sz_after, sz_duplicate >
{ using three_value < t_infixlinebreakstyle, e_infixlinebreakstyle, sz_before, sz_after, sz_duplicate > :: three_value; };

template < > struct type_master < t_k_m_n > : three_value < t_k_m_n, e_k_m_n, sz_k, sz_m, sz_n >
{ using three_value < t_k_m_n, e_k_m_n, sz_k, sz_m, sz_n > :: three_value; };

template < > struct type_master < t_keytype > : three_value < t_keytype, e_keytype, sz_dsa, sz_ec, sz_rsa >
{ using three_value < t_keytype, e_keytype, sz_dsa, sz_ec, sz_rsa > :: three_value; };

template < > struct type_master < t_lcralign > : three_value < t_lcralign, e_lcralign, sz_left, sz_centre, sz_right >
{ using three_value < t_lcralign, e_lcralign, sz_left, sz_centre, sz_right > :: three_value; };

template < > struct type_master < t_lrnalign > : three_value < t_lrnalign, e_lrnalign, sz_left, sz_right, sz_none >
{ using three_value < t_lrnalign, e_lrnalign, sz_left, sz_right, sz_none > :: three_value; };

template < > struct type_master < t_lraalign > : three_value < t_lraalign, e_lraalign, sz_left, sz_right, sz_all >
{ using three_value < t_lraalign, e_lraalign, sz_left, sz_right, sz_all > :: three_value; };

template < > struct type_master < t_mathform > : three_value < t_mathform, e_mathform, sz_infix, sz_postfix, sz_prefix >
{ using three_value < t_mathform, e_mathform, sz_infix, sz_postfix, sz_prefix > :: three_value; };

template < > struct type_master < t_mathframe > : three_value < t_mathframe, e_mathframe, sz_dashed, sz_none, sz_solid >
{ using three_value < t_mathframe, e_mathframe, sz_dashed, sz_none, sz_solid > :: three_value; };

template < > struct type_master < t_mathoccurence > : three_value < t_mathoccurence, e_mathoccurence, sz_prefix, sz_infix, sz_functionmodel >
{ using three_value < t_mathoccurence, e_mathoccurence, sz_prefix, sz_infix, sz_functionmodel > :: three_value; };

template < > struct type_master < t_media_overflow > : three_value < t_media_overflow, e_media_overflow, sz_none, sz_scroll, sz_paged >
{ using three_value < t_media_overflow, e_media_overflow, sz_none, sz_scroll, sz_paged > :: three_value; };

template < > struct type_master < t_media_pointer > : three_value < t_media_pointer, e_media_pointer, sz_coarse, sz_fine, sz_none >
{ using three_value < t_media_pointer, e_media_pointer, sz_coarse, sz_fine, sz_none > :: three_value; };

template < > struct type_master < t_media_scripting > : three_value < t_media_scripting, e_media_scripting, sz_enabled, sz_initial_only, sz_none >
{ using three_value < t_media_scripting, e_media_scripting, sz_enabled, sz_initial_only, sz_none > :: three_value; };

template < > struct type_master < t_media_update > : three_value < t_media_update, e_media_update, sz_fast, sz_none, sz_slow >
{ using three_value < t_media_update, e_media_update, sz_fast, sz_none, sz_slow > :: three_value; };

template < > struct type_master < t_menuitem > : three_value < t_menuitem, e_menuitem, sz_command, sz_checkbox, sz_radio >
{ using three_value < t_menuitem, e_menuitem, sz_command, sz_checkbox, sz_radio > :: three_value; };

template < > struct type_master < t_menutype > : three_value < t_menutype, e_menutype, sz_context, sz_popup, sz_toolbar >
{ using three_value < t_menutype, e_menutype, sz_context, sz_popup, sz_toolbar > :: three_value; };

template < > struct type_master < t_mf_class > : three_value < t_mf_class, e_mf_class, sz_public, sz_private, sz_confidential >
{ using three_value < t_mf_class, e_mf_class, sz_public, sz_private, sz_confidential > :: three_value; };

template < > struct type_master < t_mf_status > : three_value < t_mf_status, e_mf_status, sz_tentative, sz_confirmed, sz_cancelled >
{ using three_value < t_mf_status, e_mf_status, sz_tentative, sz_confirmed, sz_cancelled > :: three_value; };

template < > struct type_master < t_nsd > : three_value < t_nsd, e_nsd, sz_none, sz_spaced, sz_dashed >
{ using three_value < t_nsd, e_nsd, sz_none, sz_spaced, sz_dashed > :: three_value; };

template < > struct type_master < t_nuf > : three_value < t_nuf, e_nuf, sz_refurbished, sz_new, sz_used >
{ using three_value < t_nuf, e_nuf, sz_refurbished, sz_new, sz_used > :: three_value; };

template < > struct type_master < t_onetwothree > : three_value < t_onetwothree, e_onetwothree, sz_one, sz_two, sz_three >
{ using three_value < t_onetwothree, e_onetwothree, sz_one, sz_two, sz_three > :: three_value; };

template < > struct type_master < t_popovertargetaction > : three_value < t_popovertargetaction, e_popovertargetaction, sz_hide, sz_show, sz_toggle >
{ using three_value < t_popovertargetaction, e_popovertargetaction, sz_hide, sz_show, sz_toggle > :: three_value; };

template < > struct type_master < t_preload5 > : three_value < t_preload5, e_preload, sz_auto, sz_metadata, sz_none >
{ using three_value < t_preload5, e_preload, sz_auto, sz_metadata, sz_none > :: three_value; };

template < > struct type_master < t_pri_img_setting > : three_value < t_pri_img_setting, e_pri_img_setting, sz_indoor, sz_outdoor, sz_studio >
{ using three_value < t_pri_img_setting, e_pri_img_setting, sz_indoor, sz_outdoor, sz_studio > :: three_value; };

template < > struct type_master < t_restart > : three_value < t_restart, e_restart, sz_always, sz_whennotactive, sz_never >
{ using three_value < t_restart, e_restart, sz_always, sz_whennotactive, sz_never > :: three_value; };

template < > struct type_master < t_scrolling > : three_value < t_scrolling, e_scrolling, sz_auto, sz_no, sz_yes >
{ using three_value < t_scrolling, e_scrolling, sz_auto, sz_no, sz_yes > :: three_value; };

template < > struct type_master < t_shape_rcp > : three_value < t_shape_rcp, e_shape_rcp, sz_circle, sz_poly, sz_rect >
{ using three_value < t_shape_rcp, e_shape_rcp, sz_circle, sz_poly, sz_rect > :: three_value; };

template < > struct type_master < t_spacer > : three_value < t_spacer, e_spacer, sz_block, sz_horizontal, sz_vertical >
{ using three_value < t_spacer, e_spacer, sz_block, sz_horizontal, sz_vertical > :: three_value; };

template < > struct type_master < t_spreadmethod > : three_value < t_spreadmethod, e_spreadmethod, sz_reflect, sz_repeat, sz_pad >
{ using three_value < t_spreadmethod, e_spreadmethod, sz_reflect, sz_repeat, sz_pad > :: three_value; };

template < > struct type_master < t_ssi_echo > : three_value < t_ssi_echo, e_ssi_echo, sz_decoding, sz_encoding, sz_var >
{ using three_value < t_ssi_echo, e_ssi_echo, sz_decoding, sz_encoding, sz_var > :: three_value; };

template < > struct type_master < t_ssi_include > : three_value < t_ssi_include, e_ssi_include, sz_file, sz_onerror, sz_virtual >
{ using three_value < t_ssi_include, e_ssi_include, sz_file, sz_onerror, sz_virtual > :: three_value; };

template < > struct type_master < t_svg_direction > : three_value < t_svg_direction, e_svg_direction, sz_ltr, sz_rtl, sz_inherit >
{ using three_value < t_svg_direction, e_svg_direction, sz_ltr, sz_rtl, sz_inherit > :: three_value; };

template < > struct type_master < t_svg_fontvariant > : three_value < t_svg_fontvariant, e_svg_fontvariant, sz_normal, sz_smallcaps, sz_inherit >
{ using three_value < t_svg_fontvariant, e_svg_fontvariant, sz_normal, sz_smallcaps, sz_inherit > :: three_value; };

template < > struct type_master < t_tendstotype > : three_value < t_tendstotype, e_tendstotype, sz_above, sz_below, sz_twosided >
{ using three_value < t_tendstotype, e_tendstotype, sz_above, sz_below, sz_twosided > :: three_value; };

template < > struct type_master < t_tfa > : three_value < t_tfa, e_tfa, sz_auto, sz_false, sz_true >
{ using three_value < t_tfa, e_tfa, sz_auto, sz_false, sz_true > :: three_value; };

template < > struct type_master < t_tfi > : three_value < t_tfi, e_tfi, sz_false, sz_true, sz_inherit >
{ using three_value < t_tfi, e_tfi, sz_false, sz_true, sz_inherit > :: three_value; };

template < > struct type_master < t_tfu > : three_value < t_tfu, e_tfu, sz_false, sz_true, sz_undefined >
{ using three_value < t_tfu, e_tfu, sz_false, sz_true, sz_undefined > :: three_value; };

template < > struct type_master < t_units > : three_value < t_units, e_units, sz_en, sz_pixels, sz_relative >
{ using three_value < t_units, e_units, sz_en, sz_pixels, sz_relative > :: three_value; };

template < > struct type_master < t_valign_tmb > : three_value < t_valign_tmb, e_valign_tmb, sz_top, sz_middle, sz_bottom >
{ using three_value < t_valign_tmb, e_valign_tmb, sz_top, sz_middle, sz_bottom > :: three_value; };

template < > struct type_master < t_valuetype > : three_value < t_valuetype, e_valuetype, sz_data, sz_object, sz_ref >
{ using three_value < t_valuetype, e_valuetype, sz_data, sz_object, sz_ref > :: three_value; };

template < > struct type_master < t_vector_effect_12 > : three_value < t_vector_effect_12, e_vector_effect_12, sz_inherit, sz_none, sz_nonscalingstroke >
{ using three_value < t_vector_effect_12, e_vector_effect_12, sz_inherit, sz_none, sz_nonscalingstroke > :: three_value; };

template < > struct type_master < t_visibility10 > : three_value < t_visibility10, e_visibility11, sz_visible, sz_hidden, sz_inherit >
{ using three_value < t_visibility10, e_visibility11, sz_visible, sz_hidden, sz_inherit > :: three_value; };

template < > struct type_master < t_xmpdm_quality > : three_value < t_xmpdm_quality, e_xmpdm_quality, sz_high, sz_low, sz_medium >
{ using three_value < t_xmpdm_quality, e_xmpdm_quality, sz_high, sz_low, sz_medium > :: three_value; };

template < > struct type_master < t_xmpdm_video_alphamode > : three_value < t_xmpdm_video_alphamode, e_xmpdm_video_alphamode, sz_none, sz_premultiplied, sz_straight >
{ using three_value < t_xmpdm_video_alphamode, e_xmpdm_video_alphamode, sz_none, sz_premultiplied, sz_straight > :: three_value; };

template < > struct type_master < t_xmpdm_video_colourspace > : three_value < t_xmpdm_video_colourspace, e_xmpdm_video_colourspace, sz_ccir601, sz_ccir709, sz_srgb >
{ using three_value < t_xmpdm_video_colourspace, e_xmpdm_video_colourspace, sz_ccir601, sz_ccir709, sz_srgb > :: three_value; };

template < > struct type_master < t_xmpdm_video_fieldorder > : three_value < t_xmpdm_video_fieldorder, e_xmpdm_video_fieldorder, sz_lower, sz_progressive, sz_upper >
{ using three_value < t_xmpdm_video_fieldorder, e_xmpdm_video_fieldorder, sz_lower, sz_progressive, sz_upper > :: three_value; };

template < > struct type_master < t_xmpdm_video_videoframerate > : three_value < t_xmpdm_video_videoframerate, e_xmpdm_video_videoframerate, sz_24, sz_ntsc, sz_pal >
{ using three_value < t_xmpdm_video_videoframerate, e_xmpdm_video_videoframerate, sz_24, sz_ntsc, sz_pal > :: three_value; };


template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    ::std::string three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: get_string () const
{   if (! type_base < base_type, TYPE > :: unknown ())
        switch (static_cast <int> (value_))
        {   case 0 : return SZ0::sz ();
            case 1 : return SZ1::sz ();
            case 2 : return SZ2::sz ();
            default : break; }
    return ::std::string (); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    void three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: init ()
{   a_ = ::boost::to_lower_copy (::std::string (SZ0::sz ()));
    b_ = ::boost::to_lower_copy (::std::string (SZ1::sz ()));
    c_ = ::boost::to_lower_copy (::std::string (SZ2::sz ())); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    void three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string pret (trim_the_lot_off (s));
    ::std::string t (case_must_match < CASE >::lower (pret));
    type_base < base_type, TYPE > :: status (s_good);
    PRESUME (! a_.empty (), __FILE__, __LINE__)
    if (t == a_) value_ = static_cast <base_type> (0);
    else if (t == b_) value_ = static_cast <base_type> (1);
    else if (t == c_) value_ = static_cast <base_type> (2);
    else
    {   if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "attribute cannot have an empty value (", type_name (TYPE), ")");
        else if (! check_identifier_spelling (nits, v, t))
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid; it can be ", quote (SZ0::sz ()), ", ", quote (SZ1::sz ()), ", or ", quote (SZ2::sz ()));
        type_base < base_type, TYPE > :: status (s_invalid);
        return; }
    case_must_match < CASE > :: validate (nits, v, get_string (), pret); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    ::std::string three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: a_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    ::std::string three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: b_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, bool CASE >
    ::std::string three_value < TYPE, base_type, SZ0, SZ1, SZ2, CASE > :: c_;
