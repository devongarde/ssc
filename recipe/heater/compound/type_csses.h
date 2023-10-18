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
#include "simple/type_css.h"
#include "compound/type_compound.h"

e_status set_css_background_attachments_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_background_position_3_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_background_repeat_3_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_background_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_col_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_container_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_display_1_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_size_4_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_size_adjust_value (nitpick& nits, const html_version& v, const vstr_t& vs);
e_status set_css_lang_value (nitpick& nits, const html_version& v, const vstr_t& vs);
e_status set_css_mask_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_mask_border_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_style_a_value (nitpick& nits, const html_version& v, const vstr_t& vs);
e_status set_css_list_style_type_cs_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_speak_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_src_value (nitpick& nits, const html_version& v, const ::std::string& s);

template < > struct type_master < t_css_url > : type_either_or < t_css_url, t_url, t_urifn >
{ using type_either_or < t_css_url, t_url, t_urifn > :: type_either_or; };

template < > struct type_master < t_css_local_url > : type_one_of < t_css_local_url, false, t_url, t_urifn, t_localfn >
{ using type_one_of < t_css_local_url, false, t_url, t_urifn, t_localfn > :: type_one_of; };

template < > struct type_master < t_urifn_db > : type_one_or_both < t_urifn_db, t_urifn, sz_space_char, t_decibel >
{ using type_one_or_both < t_urifn_db, t_urifn, sz_space_char, t_decibel > :: type_one_or_both; };

template < > struct type_master < t_css_align_items_a > : type_or_string < t_css_align_items_a, t_css_align_items, sz_auto >
{ using type_or_string < t_css_align_items_a, t_css_align_items, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_alpha > : type_either_or < t_css_alpha, t_zero_to_one, t_percent >
{ using type_either_or < t_css_alpha, t_zero_to_one, t_percent > :: type_either_or; };

template < > struct type_master < t_css_alpha_n > : type_or_string < t_css_alpha_n, t_css_alpha, sz_none >
{ using type_or_string < t_css_alpha_n, t_css_alpha, sz_none > :: type_or_string; };

template < > struct type_master < t_css_angular_colour_stop_list > : type_at_least_one < t_css_angular_colour_stop_list, sz_comma, t_angular_colour_more >
{ using type_at_least_one < t_css_angular_colour_stop_list, sz_comma, t_angular_colour_more > :: type_at_least_one; };

template < > struct type_master < t_css_animation > : type_some_of < t_css_animation, sz_space_char, 1, 9, t_datetime, t_css_easing_fn, t_datetime, t_unsigned, t_css_anim_dir, t_css_anim_fill_mode, t_css_anim_play_state, t_css_anim_name, t_css_anim_timeline >
{ using type_some_of < t_css_animation, sz_space_char, 1, 9, t_datetime, t_css_easing_fn, t_datetime, t_unsigned, t_css_anim_dir, t_css_anim_fill_mode, t_css_anim_play_state, t_css_anim_name, t_css_anim_timeline > :: type_some_of; };

template < > struct type_master < t_css_anim_name > : type_or_string < t_css_anim_name, t_css_anim_base, sz_none >
{ using type_or_string < t_css_anim_name, t_css_anim_base, sz_none > :: type_or_string; };

template < > struct type_master < t_css_attr > : type_function_all < t_css_attr, sz_attr, t_text >
{ using type_function_all < t_css_attr, sz_attr, t_text > :: type_function_all; };

template < > struct type_master < t_css_azimuth_eb > : type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e >
{ using type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e > :: type_either_or; };

template < > struct type_master < t_css_azimuth_es > : type_at_least_one < t_css_azimuth_es, sz_space_char, t_css_azimuth_eb >
{ using type_at_least_one < t_css_azimuth_es, sz_space_char, t_css_azimuth_eb > :: type_at_least_one; };

template < > struct type_master < t_css_azimuth > : type_one_of < t_css_azimuth, false, t_angle, t_css_azimuth_lri, t_css_azimuth_es >
{ using type_one_of < t_css_azimuth, false, t_angle, t_css_azimuth_lri, t_css_azimuth_es > :: type_one_of; };

template < > struct type_master < t_css_background_0 > : type_range < t_css_background_0, sz_space_char, t_css_backval, 1, 5 >
{ using type_range < t_css_background_0, sz_space_char, t_css_backval, 1, 5 > :: type_range; };

template < > struct type_master < t_css_background_1 > : type_many_then_must < t_css_background_1, t_css_background_2, sz_comma, t_css_background_3 >
{ using type_many_then_must < t_css_background_1, t_css_background_2, sz_comma, t_css_background_3 > :: type_many_then_must; };

template < > struct type_master < t_css_background_2 > : type_some_of < t_css_background_2, sz_space_char, 1, 999,
    t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachments, t_css_visual_box, t_css_visual_box >
{ using type_some_of < t_css_background_2, sz_space_char, 1, 999,
    t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachments, t_css_visual_box, t_css_visual_box > :: type_some_of; };

template < > struct type_master < t_css_background_3 > : type_some_of < t_css_background_3, sz_space_char, 1, 999,
    t_css_colour, t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachment, t_css_visual_box, t_css_visual_box >
{ using type_some_of < t_css_background_3, sz_space_char, 1, 999,
    t_css_colour, t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachment, t_css_visual_box, t_css_visual_box > :: type_some_of; };

template < > struct type_master < t_css_background_attachment_3 > : type_at_least_one < t_css_background_attachment_3, sz_comma, t_css_background_attachment >
{ using type_at_least_one < t_css_background_attachment_3, sz_comma, t_css_background_attachment > :: type_at_least_one; };

template < > struct type_master < t_css_background_boxes > : type_at_least_one < t_css_background_boxes, sz_comma, t_css_visual_box >
{ using type_at_least_one < t_css_background_boxes, sz_comma, t_css_visual_box > :: type_at_least_one; };

template < > struct type_master < t_css_background_position > : type_one_or_both < t_css_background_position, t_refy, sz_space_char, t_refx >
{ using type_one_or_both < t_css_background_position, t_refy, sz_space_char, t_refx > :: type_one_or_both; };

template < > struct type_master < t_css_background_position_1 > : type_or_any_string_5 < t_css_background_position_1, t_css_length, sz_bottom, sz_centre, sz_left, sz_right, sz_top >
{ using type_or_any_string_5 < t_css_background_position_1, t_css_length, sz_bottom, sz_centre, sz_left, sz_right, sz_top > :: type_or_any_string_5; };

template < > struct type_master < t_css_background_position_2 > : type_at_least_one < t_css_background_position_2, sz_space_char, t_css_background_position_1 >
{ using type_at_least_one < t_css_background_position_2, sz_space_char, t_css_background_position_1 > :: type_at_least_one; };

template < > struct type_master < t_css_background_positions > : type_at_least_one < t_css_background_positions, sz_comma, t_css_background_position_2 >
{ using type_at_least_one < t_css_background_positions, sz_comma, t_css_background_position_2 > :: type_at_least_one; };

template < > struct type_master < t_css_background_repeat_2 > : type_one_or_both < t_css_background_repeat_2, t_css_background_repeat, sz_space_char, t_css_background_repeat >
{ using type_one_or_both < t_css_background_repeat_2, t_css_background_repeat, sz_space_char, t_css_background_repeat > :: type_one_or_both; };

template < > struct type_master < t_css_background_repeats > : type_at_least_one < t_css_background_repeats, sz_comma, t_css_background_repeat_2 >
{ using type_at_least_one < t_css_background_repeats, sz_comma, t_css_background_repeat_2 > :: type_at_least_one; };

template < > struct type_master < t_css_background_size > : type_or_either_string < t_css_background_size, t_css_length_a2, sz_contain, sz_cover >
{ using type_or_either_string < t_css_background_size, t_css_length_a2, sz_contain, sz_cover > :: type_or_either_string; };

template < > struct type_master < t_css_background_sizes > : type_at_least_one < t_css_background_sizes, sz_comma, t_css_background_size >
{ using type_at_least_one < t_css_background_sizes, sz_comma, t_css_background_size > :: type_at_least_one; };

template < > struct type_master < t_css_base_palette > : type_or_either_string < t_css_base_palette, t_unsigned, sz_dark, sz_light >
{ using type_or_either_string < t_css_base_palette, t_unsigned, sz_dark, sz_light > :: type_or_either_string; };

template < > struct type_master < t_css_baseline_position > : maybe_type_then_string < t_css_baseline_position, t_first_last, sz_baseline >
{ using maybe_type_then_string < t_css_baseline_position, t_first_last, sz_baseline > :: maybe_type_then_string; };

template < > struct type_master < t_css_border_image > : type_some_of < t_css_border_image, sz_space_char, 1, 0,
    t_css_border_image_src, t_css_border_image_slice, t_slash, t_css_lengths_a, t_slash, t_css_lengths_a, t_slash, t_css_length, t_css_border_image_repeat >
{ using type_some_of < t_css_border_image, sz_space_char, 1, 0,
    t_css_border_image_src, t_css_border_image_slice, t_slash, t_css_lengths_a, t_slash, t_css_lengths_a, t_slash, t_css_length, t_css_border_image_repeat > :: type_some_of; };

template < > struct type_master < t_css_border_images_repeat > : type_one_or_both < t_css_border_images_repeat, t_css_border_image_repeat, sz_space_char, t_css_border_image_repeat >
{ using type_one_or_both < t_css_border_images_repeat, t_css_border_image_repeat, sz_space_char, t_css_border_image_repeat > :: type_one_or_both; };

template < > struct type_master < t_css_border_image_slice > : type_and_maybe_string < t_css_border_image_slice, t_css_lengths, sz_space_char, sz_fill >
{ using type_and_maybe_string < t_css_border_image_slice, t_css_lengths, sz_space_char, sz_fill > :: type_and_maybe_string; };

template < > struct type_master < t_css_border_image_src > : either_type_or_string < t_css_border_image_src, t_css_url, t_css_gradient, sz_inherit >
{ using either_type_or_string < t_css_border_image_src, t_css_url, t_css_gradient, sz_inherit > :: either_type_or_string; };

template < > struct type_master < t_css_border_measure > : type_one_of < t_css_border_measure, false, t_css_inherit, t_css_border_width, t_css_length >
{ using type_one_of < t_css_border_measure, false, t_css_inherit, t_css_border_width, t_css_length > :: type_one_of; };

template < > struct type_master < t_css_borders_measure_2 > : type_range < t_css_borders_measure_2, sz_space_char, t_css_border_measure, 1, 2 >
{ using type_range < t_css_borders_measure_2, sz_space_char, t_css_border_measure, 1, 2 > :: type_range; };

template < > struct type_master < t_css_borders_measure > : type_range < t_css_borders_measure, sz_space_char, t_css_border_measure, 1, 4 >
{ using type_range < t_css_borders_measure, sz_space_char, t_css_border_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_css_borders_measure_i > : type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit >
{ using type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_borders_measure_l > : maybe_logical_type < t_css_borders_measure_l, t_css_borders_measure >
{ using maybe_logical_type < t_css_borders_measure_l, t_css_borders_measure > :: maybe_logical_type; };

template < > struct type_master < t_css_border_radius > : type_some_of < t_css_border_radius, sz_space_char, 1, 9,
    t_css_length, t_css_length, t_css_length, t_css_length, t_slash, t_css_length, t_css_length, t_css_length, t_css_length >
{ using type_some_of < t_css_border_radius, sz_space_char, 1, 9,
    t_css_length, t_css_length, t_css_length, t_css_length, t_slash, t_css_length, t_css_length, t_css_length, t_css_length > :: type_some_of; };

template < > struct type_master < t_css_border_spacing_2 > : type_range < t_css_border_spacing_2, sz_space_char, t_css_length, 1, 2 >
{ using type_range < t_css_border_spacing_2, sz_space_char, t_css_length, 1, 2 > :: type_range; };

template < > struct type_master < t_css_border_spacing > : type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit >
{ using type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_styles_2 > : type_range < t_css_border_styles_2, sz_space_char, t_css_border_style, 1, 2 >
{ using type_range < t_css_border_styles_2, sz_space_char, t_css_border_style, 1, 2 > :: type_range; };

template < > struct type_master < t_css_border_style_i > : type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit >
{ using type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_styles > : type_range < t_css_border_styles, sz_space_char, t_css_border_style, 1, 4 >
{ using type_range < t_css_border_styles, sz_space_char, t_css_border_style, 1, 4 > :: type_range; };

template < > struct type_master < t_css_border_styles_l > : maybe_logical_type < t_css_border_styles_l, t_css_border_styles >
{ using maybe_logical_type < t_css_border_styles_l, t_css_border_styles > :: maybe_logical_type; };

template < > struct type_master < t_css_border_width_i > : type_either_or < t_css_border_width_i, t_css_border_width, t_css_inherit >
{ using type_either_or < t_css_border_width_i, t_css_border_width, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_box_overflow > : type_opt_then_must < t_css_box_overflow, t_safe_unsafe, sz_space_char, t_css_content_position >
{ using type_opt_then_must < t_css_box_overflow, t_safe_unsafe, sz_space_char, t_css_content_position > :: type_opt_then_must; };

template < > struct type_master < t_css_box_content > : type_one_of < t_css_box_content, false, t_css_baseline_position, t_css_content_position, t_css_align_content, t_css_box_overflow >
{ using type_one_of < t_css_box_content, false, t_css_baseline_position, t_css_content_position, t_css_align_content, t_css_box_overflow > :: type_one_of; };

template < > struct type_master < t_css_box_content_n > : type_or_string < t_css_box_content_n, t_css_box_content, sz_normal >
{ using type_or_string < t_css_box_content_n, t_css_box_content, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_box_alignitems > : type_one_of < t_css_box_alignitems, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position >
{ using type_one_of < t_css_box_alignitems, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position > :: type_one_of; };

template < > struct type_master < t_css_box_alignitems_ns > : type_or_either_string < t_css_box_alignitems_ns, t_css_box_alignitems, sz_normal, sz_stretch >
{ using type_or_either_string < t_css_box_alignitems_ns, t_css_box_alignitems, sz_normal, sz_stretch > :: type_or_either_string; };

template < > struct type_master < t_css_box_alignself > : type_one_of < t_css_box_alignself, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position >
{ using type_one_of < t_css_box_alignself, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position > :: type_one_of; };

template < > struct type_master < t_css_box_alignself_acs > : type_either_or < t_css_box_alignself_acs, t_css_box_alignself, t_css_box_alignself_mess >
{ using type_either_or < t_css_box_alignself_acs, t_css_box_alignself, t_css_box_alignself_mess > :: type_either_or; };

template < > struct type_master < t_css_box_legacy > : string_then_maybe_type < t_css_box_legacy, t_lcralign, sz_space_char, sz_legacy >
{ using string_then_maybe_type < t_css_box_legacy, t_lcralign, sz_space_char, sz_legacy > :: string_then_maybe_type; };

template < > struct type_master < t_css_box_justify > : type_one_of < t_css_box_justify, false, t_css_content_position, t_css_align_content, t_css_box_overflow, t_lralign >
{ using type_one_of < t_css_box_justify, false, t_css_content_position, t_css_align_content, t_css_box_overflow, t_lralign > :: type_one_of; };

template < > struct type_master < t_css_box_justify_n > : type_or_string < t_css_box_justify_n, t_css_box_justify, sz_normal >
{ using type_or_string < t_css_box_justify_n, t_css_box_justify, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_box_justitems > : type_one_of < t_css_box_justitems, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position, t_lralign, t_css_box_legacy >
{ using type_one_of < t_css_box_justitems, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position, t_lralign, t_css_box_legacy > :: type_one_of; };

template < > struct type_master < t_css_box_justitems_ns > : type_or_either_string < t_css_box_justitems_ns, t_css_box_justitems, sz_normal, sz_stretch >
{ using type_or_either_string < t_css_box_justitems_ns, t_css_box_justitems, sz_normal, sz_stretch > :: type_or_either_string; };

template < > struct type_master < t_css_box_justself > : type_one_of < t_css_box_justself, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position, t_lralign >
{ using type_one_of < t_css_box_justself, false, t_css_baseline_position, t_css_box_overflow, t_css_self_position, t_lralign > :: type_one_of; };

template < > struct type_master < t_css_box_justself_ans > : type_or_any_string < t_css_box_justself_ans, t_css_box_justself, sz_auto, sz_normal, sz_stretch >
{ using type_or_any_string < t_css_box_justself_ans, t_css_box_justself, sz_auto, sz_normal, sz_stretch > :: type_or_any_string; };

template < > struct type_master < t_css_box_shadow > : type_some_of < t_css_box_shadow, sz_space_char, 1, 6, t_css_col, t_css_length, t_css_length, t_css_length, t_css_length, t_inset >
{ using type_some_of < t_css_box_shadow, sz_space_char, 1, 6, t_css_col, t_css_length, t_css_length, t_css_length, t_css_length, t_inset > :: type_some_of; };

template < > struct type_master < t_css_box_shadows > : type_at_least_one < t_css_box_shadows, sz_comma, t_css_box_shadow >
{ using type_at_least_one < t_css_box_shadows, sz_comma, t_css_box_shadow > :: type_at_least_one; };

template < > struct type_master < t_css_box_shadows_n > : type_or_string < t_css_box_shadows_n, t_css_box_shadows, sz_none >
{ using type_or_string < t_css_box_shadows_n, t_css_box_shadows, sz_none > :: type_or_string; };

template < > struct type_master < t_css_clip_path_shape > : type_either_or < t_css_clip_path_shape, t_css_clip_path_box, t_css_shape_box >
{ using type_either_or < t_css_clip_path_shape, t_css_clip_path_box, t_css_shape_box > :: type_either_or; };

template < > struct type_master < t_css_clip_path > : one_of_three_or_string < t_css_clip_path, t_fn, t_urifn, t_css_clip_path_shape, sz_none >
{ using one_of_three_or_string < t_css_clip_path, t_fn, t_urifn, t_css_clip_path_shape, sz_none > :: one_of_three_or_string; };

template < > struct type_master < t_css_coin3 > : type_opt_then_must < t_css_coin3, t_css_hue_interpolation, sz_space_char, t_css_hue >
{ using type_opt_then_must < t_css_coin3, t_css_hue_interpolation, sz_space_char, t_css_hue > :: type_opt_then_must; };

template < > struct type_master < t_css_coin2 > : type_must_then_opt < t_css_coin2, t_css_polar, sz_space_char, t_css_coin3 >
{ using type_must_then_opt < t_css_coin2, t_css_polar, sz_space_char, t_css_coin3 > :: type_must_then_opt; };

template < > struct type_master < t_css_coin1 > : type_either_or < t_css_coin1, t_css_rect, t_css_coin2 >
{ using type_either_or < t_css_coin1, t_css_rect, t_css_coin2 > :: type_either_or; };

template < > struct type_master < t_css_colour_3 > : type_one_of < t_css_colour_3, false, t_css_colour, t_colour_i, t_transparentsz, t_current_colour_sz, t_hslfn, t_hslafn, t_rgbafn >
{ using type_one_of < t_css_colour_3, false, t_css_colour, t_colour_i, t_transparentsz, t_current_colour_sz, t_hslfn, t_hslafn, t_rgbafn > :: type_one_of; };

template < > struct type_master < t_css_colour_4 > : type_one_of < t_css_colour_4, false, t_css_colour, t_colour, t_transparentsz, t_current_colour_sz,
    t_colourfn, t_hslfn4, t_hwbfn, t_labfn, t_lchfn, t_oklabfn, t_oklchfn, t_rgbfn, t_hslfn, t_hslafn, t_rgbafn >
{ using type_one_of < t_css_colour_4, false, t_css_colour, t_colour, t_transparentsz, t_current_colour_sz,
    t_colourfn, t_hslfn4, t_hwbfn, t_labfn, t_lchfn, t_oklabfn, t_oklchfn, t_rgbfn, t_hslfn, t_hslafn, t_rgbafn > :: type_one_of; };

template < > struct type_master < t_css_colour_a > : type_or_string < t_css_colour_a, t_css_col, sz_auto >
{ using type_or_string < t_css_colour_a, t_css_col, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_colour_interpolation > : string_then_type < t_css_colour_interpolation, t_css_coin1, sz_in >
{ using string_then_type < t_css_colour_interpolation, t_css_coin1, sz_in > :: string_then_type; };

template < > struct type_master < t_css_colour_percent > : type_one_or_both < t_css_colour_percent, t_css_colour, sz_space_char, t_percent, BS_FN >
{ using type_one_or_both < t_css_colour_percent, t_css_colour, sz_space_char, t_percent, BS_FN > :: type_one_or_both; };

template < > struct type_master < t_css_colour_percent_n > : type_or_string < t_css_colour_percent_n, t_css_colour_percent, sz_none >
{ using type_or_string < t_css_colour_percent_n, t_css_colour_percent, sz_none > :: type_or_string; };

template < > struct type_master < t_css_colour_stop_list > : type_at_least_one < t_css_colour_stop_list, sz_comma, t_linear_colour_more >
{ using type_at_least_one < t_css_colour_stop_list, sz_comma, t_linear_colour_more > :: type_at_least_one; };

template < > struct type_master < t_css_cols > : type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col >
{ using type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col > :: type_some_of; };

template < > struct type_master < t_css_cols_2 > : type_some_of < t_css_cols_2, sz_space_char, 1, 2, t_css_col >
{ using type_some_of < t_css_cols_2, sz_space_char, 1, 2, t_css_col > :: type_some_of; };

template < > struct type_master < t_css_cols_2_a > : type_or_string < t_css_cols_2_a, t_css_cols_2, sz_auto >
{ using type_or_string < t_css_cols_2_a, t_css_cols_2, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_cols_l > : maybe_logical_type < t_css_cols_l, t_css_cols >
{ using maybe_logical_type < t_css_cols_l, t_css_cols > :: maybe_logical_type; };

template < > struct type_master < t_css_column_rule > : type_some_of < t_css_column_rule, sz_space_char, 1, 3, t_css_border_measure, t_css_border_style, t_css_col >
{ using type_some_of < t_css_column_rule, sz_space_char, 1, 3, t_css_border_measure, t_css_border_style, t_css_col > :: type_some_of; };

template < > struct type_master < t_css_columns > : type_ab_ba < t_css_columns, sz_space_char, t_measure_a, t_unsigned_1_more_a >
{ using type_ab_ba < t_css_columns, sz_space_char, t_measure_a, t_unsigned_1_more_a > :: type_ab_ba; };

template < > struct type_master < t_css_composites > : type_some_of < t_css_composites, sz_comma, 1, 999, t_css_composite >
{ using type_some_of < t_css_composites, sz_comma, 1, 999, t_css_composite > :: type_some_of; };

template < > struct type_master < t_css_contain_slp > : type_some_of < t_css_contain_slp, sz_space_char, 1, 3, t_css_contain_e >
{ using type_some_of < t_css_contain_slp, sz_space_char, 1, 3, t_css_contain_e > :: type_some_of; };

template < > struct type_master < t_css_contain > : type_or_any_string < t_css_contain, t_css_contain_slp, sz_content, sz_none, sz_strict >
{ using type_or_any_string < t_css_contain, t_css_contain_slp, sz_content, sz_none, sz_strict > :: type_or_any_string; };

template < > struct type_master < t_css_container_name > : type_or_string < t_css_container_name, t_text, sz_none >
{ using type_or_string < t_css_container_name, t_text, sz_none > :: type_or_string; };

template < > struct type_master < t_css_container_type > : type_either_or_both < t_css_container_type, t_normal, sz_space_char, t_size_inlinesize >
{ using type_either_or_both < t_css_container_type, t_normal, sz_space_char, t_size_inlinesize > :: type_either_or_both; };

template < > struct type_master < t_css_counter > : type_function_2_opt < t_css_counter, sz_counter, t_text, t_css_list_style_type >
{ using type_function_2_opt < t_css_counter, sz_counter, t_text, t_css_list_style_type > :: type_function_2_opt; };

// not clear from spec where counter identifiers are defined in CSS
template < > struct type_master < t_css_counter_ii > : type_either_or < t_css_counter_ii, t_text, t_integer >
{ using type_either_or < t_css_counter_ii, t_text, t_integer > :: type_either_or; };

template < > struct type_master < t_css_counter_iin > : type_at_least_one < t_css_counter_iin, sz_space_char, t_css_counter_ii >
{ using type_at_least_one < t_css_counter_iin, sz_space_char, t_css_counter_ii > :: type_at_least_one; };

template < > struct type_master < t_css_counter_set > : either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_counters > : type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type >
{ using type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type > :: type_function_3_opt; };

template < > struct type_master < t_css_content_fn > : type_one_of < t_css_content_fn, false, t_css_attr, t_css_counter, t_css_counters >
{ using type_one_of < t_css_content_fn, false, t_css_attr, t_css_counter, t_css_counters > :: type_one_of; };

template < > struct type_master < t_css_content_base > : type_one_of < t_css_content_base, false, t_text, t_css_content_fn, t_urifn >
{ using type_one_of < t_css_content_base, false, t_text, t_css_content_fn, t_urifn > :: type_one_of; };

template < > struct type_master < t_css_content_twice > : type_at_least_none < t_css_content_twice, sz_space_char, t_css_content_base >
{ using type_at_least_none < t_css_content_twice, sz_space_char, t_css_content_base > :: type_at_least_none; };

template < > struct type_master < t_css_content > : type_either_neither < t_css_content, t_css_content_twice, t_css_inherit >
{ using type_either_neither < t_css_content, t_css_content_twice, t_css_inherit > :: type_either_neither; };

template < > struct type_master < t_css_clip_coord_box > : type_or_string < t_css_clip_coord_box, t_css_coord_box, sz_no_clip >
{ using type_or_string < t_css_clip_coord_box, t_css_coord_box, sz_no_clip > :: type_or_string; };

template < > struct type_master < t_css_clip_coord_boxen > : type_some_of < t_css_clip_coord_boxen, sz_comma, 1, 999, t_css_clip_coord_box >
{ using type_some_of < t_css_clip_coord_boxen, sz_comma, 1, 999, t_css_clip_coord_box > :: type_some_of; };

template < > struct type_master < t_css_coord_boxen > : type_some_of < t_css_coord_boxen, sz_comma, 1, 999, t_css_coord_box >
{ using type_some_of < t_css_coord_boxen, sz_comma, 1, 999, t_css_coord_box > :: type_some_of; };

template < > struct type_master < t_css_cue > : either_type_or_string < t_css_cue, t_urifn_db, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_cue, t_urifn_db, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_cues > : type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 >
{ using type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 > :: type_range; };

template < > struct type_master < t_css_cursor_url > : type_many_then_must < t_css_cursor_url, t_urifn_xy, sz_comma, t_css_cursor_e >
{ using type_many_then_must < t_css_cursor_url, t_urifn_xy, sz_comma, t_css_cursor_e > :: type_many_then_must; };

template < > struct type_master < t_css_cursor > : type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit >
{ using type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_display_listitem > : both_types_then_string < t_css_display_listitem, t_css_display_outside, t_css_display_flow, sz_list_item >
{ using both_types_then_string < t_css_display_listitem, t_css_display_outside, t_css_display_flow, sz_list_item > :: both_types_then_string; };

template < > struct type_master < t_css_display_3 > : type_some_of < t_css_display_3, sz_space_char, 1, 6,
    t_css_display_outside, t_css_display_inside, t_css_display_listitem, t_css_display_internal, t_css_display_box, t_css_display_legacy >
{ using type_some_of < t_css_display_3, sz_space_char, 1, 6,
    t_css_display_outside, t_css_display_inside, t_css_display_listitem, t_css_display_internal, t_css_display_box, t_css_display_legacy > :: type_some_of; };

template < > struct type_master < t_css_durations > : type_at_least_one < t_css_durations, sz_comma, t_svg_duration >
{ using type_at_least_one < t_css_durations, sz_comma, t_svg_duration > :: type_at_least_one; };

template < > struct type_master < t_css_easing_fns > : type_at_least_one < t_css_easing_fns, sz_comma, t_css_easing_fn >
{ using type_at_least_one < t_css_easing_fns, sz_comma, t_css_easing_fn > :: type_at_least_one; };

template < > struct type_master < t_css_elevation > : type_either_or < t_css_elevation, t_angle, t_css_elevation_e >
{ using type_either_or < t_css_elevation, t_angle, t_css_elevation_e > :: type_either_or; };

template < > struct type_master < t_css_filter > : type_either_or < t_css_filter, t_urifn, t_fn >
{ using type_either_or < t_css_filter, t_urifn, t_fn > :: type_either_or; };

template < > struct type_master < t_css_filters > : type_some_of < t_css_filters, sz_space_char, 1, 999, t_css_filter >
{ using type_some_of < t_css_filters, sz_space_char, 1, 999, t_css_filter > :: type_some_of; };

template < > struct type_master < t_css_filters_n > : type_or_string < t_css_filters_n, t_css_filters, sz_none >
{ using type_or_string < t_css_filters_n, t_css_filters, sz_none > :: type_or_string; };

template < > struct type_master < t_css_flex_basis > : type_or_either_string < t_css_flex_basis, t_measure, sz_auto, sz_content >
{ using type_or_either_string < t_css_flex_basis, t_measure, sz_auto, sz_content > :: type_or_either_string; };

template < > struct type_master < t_css_flex > : type_some_of < t_css_flex, sz_space_char, 1, 3, t_fixedpoint, t_fixedpoint, t_css_flex_basis >
{ using type_some_of < t_css_flex, sz_space_char, 1, 3, t_fixedpoint, t_fixedpoint, t_css_flex_basis > :: type_some_of; };

template < > struct type_master < t_css_flex_flow > : type_either_or_both < t_css_flex_flow, t_css_flex_direction, sz_space_char, t_css_flex_wrap >
{ using type_either_or_both < t_css_flex_flow, t_css_flex_direction, sz_space_char, t_css_flex_wrap > :: type_either_or_both; };

template < > struct type_master < t_css_flex_n > : type_or_string < t_css_flex_n, t_css_flex, sz_none >
{ using type_or_string < t_css_flex_n, t_css_flex, sz_none > :: type_or_string; };

template < > struct type_master < t_css_fn_annotation > : type_function < t_css_fn_annotation, sz_annotation, t_css_ffv >
{ using type_function < t_css_fn_annotation, sz_annotation, t_css_ffv > :: type_function; };

template < > struct type_master < t_css_fn_character_variant > : type_function_some < t_css_fn_character_variant, sz_character_variant, 1, 0, t_css_ffv >
{ using type_function_some < t_css_fn_character_variant, sz_character_variant, 1, 0, t_css_ffv > :: type_function_some; };

template < > struct type_master < t_css_fn_fit_content > : type_function < t_css_fn_fit_content, sz_fit_content, t_css_length >
{ using type_function < t_css_fn_fit_content, sz_fit_content, t_css_length > :: type_function; };

template < > struct type_master < t_css_fn_ornaments > : type_function < t_css_fn_ornaments, sz_ornaments, t_css_ffv >
{ using type_function < t_css_fn_ornaments, sz_ornaments, t_css_ffv > :: type_function; };

template < > struct type_master < t_css_fn_styleset > : type_function_some < t_css_fn_styleset, sz_styleset, 1, 0, t_css_ffv >
{ using type_function_some < t_css_fn_styleset, sz_styleset, 1, 0, t_css_ffv > :: type_function_some; };

template < > struct type_master < t_css_fn_stylistic > : type_function < t_css_fn_stylistic, sz_stylistic, t_css_ffv >
{ using type_function < t_css_fn_stylistic, sz_stylistic, t_css_ffv > :: type_function; };

template < > struct type_master < t_css_fn_swash > : type_function < t_css_fn_swash, sz_swash, t_css_ffv >
{ using type_function < t_css_fn_swash, sz_swash, t_css_ffv > :: type_function; };

template < > struct type_master < t_css_column_width > : either_type_or_either_string < t_css_column_width, t_measure_a, t_css_fn_fit_content, sz_max_content, sz_min_content >
{ using either_type_or_either_string < t_css_column_width, t_measure_a, t_css_fn_fit_content, sz_max_content, sz_min_content > :: either_type_or_either_string; };

template < > struct type_master < t_css_font_feature_tag > : type_must_then_opt < t_css_font_feature_tag, t_css_font_feature, sz_space_char, t_integer_oo >
{ using type_must_then_opt < t_css_font_feature_tag, t_css_font_feature, sz_space_char, t_integer_oo > :: type_must_then_opt; };

template < > struct type_master < t_css_font_feature_tags > : type_at_least_one < t_css_font_feature_tags, sz_comma, t_css_font_feature_tag >
{ using type_at_least_one < t_css_font_feature_tags, sz_comma, t_css_font_feature_tag > :: type_at_least_one; };

template < > struct type_master < t_css_font_feature_settings > : type_or_string < t_css_font_feature_settings, t_css_font_feature_tags, sz_normal >
{ using type_or_string < t_css_font_feature_settings, t_css_font_feature_tags, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_font_named_instance > : type_or_string < t_css_font_named_instance, t_text, sz_auto >
{ using type_or_string < t_css_font_named_instance, t_text, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_font_size > : type_one_of_four < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_inherit >
{ using type_one_of_four < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_inherit > :: type_one_of_four; };

template < > struct type_master < t_css_font_style > : type_either_or < t_css_font_style, t_css_all, t_css_font_style_e >
{ using type_either_or < t_css_font_style, t_css_all, t_css_font_style_e > :: type_either_or; };

template < > struct type_master < t_css_font_style_2 > : type_or_string < t_css_font_style_2, t_fontnias, sz_all >
{ using type_or_string < t_css_font_style_2, t_fontnias, sz_all > :: type_or_string; };

template < > struct type_master < t_css_font_synthesis > : type_some_of < t_css_font_synthesis, sz_space_char, 1, 3, t_auto_none >
{ using type_some_of < t_css_font_synthesis, sz_space_char, 1, 3, t_auto_none > :: type_some_of; };

template < > struct type_master < t_css_font_synthesis_n > : type_or_string < t_css_font_synthesis_n, t_css_font_synthesis, sz_none >
{ using type_or_string < t_css_font_synthesis_n, t_css_font_synthesis, sz_none > :: type_or_string; };

template < > struct type_master < t_font_synthesis > : either_string_or_both < t_font_synthesis, sz_style, sz_weight, sz_space_char >
{ using either_string_or_both < t_font_synthesis, sz_style, sz_weight, sz_space_char > :: either_string_or_both; };

template < > struct type_master < t_font_synthesis_n > : type_or_string < t_font_synthesis_n, t_font_synthesis, sz_none >
{ using type_or_string < t_font_synthesis_n, t_font_synthesis, sz_none > :: type_or_string; };

template < > struct type_master < t_css_font_techs > : type_at_least_one < t_css_font_techs, sz_comma, t_css_font_tech >
{ using type_at_least_one < t_css_font_techs, sz_comma, t_css_font_tech > :: type_at_least_one; };

template < > struct type_master < t_css_font_variation_tag > : type_must_then_opt < t_css_font_variation_tag, t_css_font_variation, sz_space_char, t_fixedpoint >
{ using type_must_then_opt < t_css_font_variation_tag, t_css_font_variation, sz_space_char, t_fixedpoint > :: type_must_then_opt; };

template < > struct type_master < t_css_font_variation_tags > : type_at_least_one < t_css_font_variation_tags, sz_comma, t_css_font_variation_tag >
{ using type_at_least_one < t_css_font_variation_tags, sz_comma, t_css_font_variation_tag > :: type_at_least_one; };

template < > struct type_master < t_css_font_variation_settings > : type_or_string < t_css_font_variation_settings, t_css_font_variation_tags, sz_normal >
{ using type_or_string < t_css_font_variation_settings, t_css_font_variation_tags, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_font_weight_4 > : type_or_any_string_5 < t_css_font_weight_4, t_0_to_1000, sz_bold, sz_bolder, sz_lighter, sz_normal, sz_inherit  >
{ using type_or_any_string_5 < t_css_font_weight_4, t_0_to_1000, sz_bold, sz_bolder, sz_lighter, sz_normal, sz_inherit > :: type_or_any_string_5; };

template < > struct type_master < t_css_format > : type_function_all < t_css_format, sz_format, t_css_font_format >
{ using type_function_all < t_css_format, sz_format, t_css_font_format > :: type_function_all; };

template < > struct type_master < t_css_gap > : type_must_then_opt < t_css_gap, t_measure_ni, sz_space_char, t_measure_ni >
{ using type_must_then_opt < t_css_gap, t_measure_ni, sz_space_char, t_measure_ni > :: type_must_then_opt; };

template < > struct type_master < t_css_grid_auto_flow > : type_and_maybe_string < t_css_grid_auto_flow, t_row_column, sz_space_char, sz_dense >
{ using type_and_maybe_string < t_css_grid_auto_flow, t_row_column, sz_space_char, sz_dense > :: type_and_maybe_string; };

template < > struct type_master < t_css_grid_lines > : type_at_least_one < t_css_grid_lines, sz_slash, t_css_grid_line >
{ using type_at_least_one < t_css_grid_lines, sz_slash, t_css_grid_line > :: type_at_least_one; };

template < > struct type_master < t_css_grid_template > : either_type_or_string < t_css_grid_template, t_css_track_list, t_css_track_list_auto, sz_none >
{ using either_type_or_string < t_css_grid_template, t_css_track_list, t_css_track_list_auto, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_grid_track_sizes > : type_at_least_one < t_css_grid_track_sizes, sz_space_char, t_css_grid_track_size >
{ using type_at_least_one < t_css_grid_track_sizes, sz_space_char, t_css_grid_track_size > :: type_at_least_one; };

template < > struct type_master < t_css_hang_punct > : type_or_either_string < t_css_hang_punct, t_allow_force, sz_first, sz_last >
{ using type_or_either_string < t_css_hang_punct, t_allow_force, sz_first, sz_last > :: type_or_either_string; };

template < > struct type_master < t_css_hangs_punct > : type_some_of < t_css_hangs_punct, sz_space_char, 1, 3, t_css_hang_punct >
{ using type_some_of < t_css_hangs_punct, sz_space_char, 1, 3, t_css_hang_punct > :: type_some_of; };

template < > struct type_master < t_css_hang_punct_n > : type_or_string < t_css_hang_punct_n, t_css_hangs_punct, sz_none >
{ using type_or_string < t_css_hang_punct_n, t_css_hangs_punct, sz_none > :: type_or_string; };

template < > struct type_master < t_css_hue > : type_either_or < t_css_hue, t_angle, t_real >
{ using type_either_or < t_css_hue, t_angle, t_real > :: type_either_or; };

template < > struct type_master < t_css_hue_n > : type_or_string < t_css_hue_n, t_css_hue, sz_none >
{ using type_or_string < t_css_hue_n, t_css_hue, sz_none > :: type_or_string; };

template < > struct type_master < t_css_image > : one_of_three_or_string < t_css_image, t_css_url, t_ltr_rtl, t_fn, sz_none >
{ using one_of_three_or_string < t_css_image, t_css_url, t_ltr_rtl, t_fn, sz_none > :: one_of_three_or_string; };

template < > struct type_master < t_css_image_resolution_from > : type_or_either_string < t_css_image_resolution_from, t_resolution, sz_snap, sz_from_image >
{ using type_or_either_string < t_css_image_resolution_from, t_resolution, sz_snap, sz_from_image > :: type_or_either_string; };

template < > struct type_master < t_css_image_resolution > : type_either_or_both < t_css_image_resolution, t_css_image_resolution_from, sz_space_char, t_css_image_resolution_from >
{ using type_either_or_both < t_css_image_resolution, t_css_image_resolution_from, sz_space_char, t_css_image_resolution_from > :: type_either_or_both; };

template < > struct type_master < t_css_image_set_rhs > : type_one_or_both < t_css_image_set_rhs, t_type_fn, sz_space_char, t_resolution >
{ using type_one_or_both < t_css_image_set_rhs, t_type_fn, sz_space_char, t_resolution > :: type_one_or_both; };

template < > struct type_master < t_css_image_set > : type_either_or < t_css_image_set, t_css_url, t_css_image_set_rhs >
{ using type_either_or < t_css_image_set, t_css_url, t_css_image_set_rhs > :: type_either_or; };

template < > struct type_master < t_css_initial_letter > : type_ab_ba < t_css_initial_letter, sz_space_char, t_reals_1_up, t_drop_raise >
{ using type_ab_ba < t_css_initial_letter, sz_space_char, t_reals_1_up, t_drop_raise > :: type_ab_ba; };

template < > struct type_master < t_css_initial_letter_n > : type_or_string < t_css_initial_letter_n, t_css_initial_letter, sz_normal >
{ using type_or_string < t_css_initial_letter_n, t_css_initial_letter, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_initial_letter_align_bb > : type_or_string < t_css_initial_letter_align_bb, t_css_initial_letter_align, sz_border_box >
{ using type_or_string < t_css_initial_letter_align_bb, t_css_initial_letter_align, sz_border_box > :: type_or_string; };

template < > struct type_master < t_css_initial_letter_wrap > : type_either_or < t_css_initial_letter_wrap, t_css_initial_letter_wrap_e, t_css_length >
{ using type_either_or < t_css_initial_letter_wrap, t_css_initial_letter_wrap_e, t_css_length > :: type_either_or; };

template < > struct type_master < t_css_inline_bem > : type_must_then_opt < t_css_inline_bem, t_css_inline_bem_1, sz_space_char, t_css_inline_bem_2 >
{ using type_must_then_opt < t_css_inline_bem, t_css_inline_bem_1, sz_space_char, t_css_inline_bem_2 > :: type_must_then_opt; };

template < > struct type_master < t_css_inline_bem_l > : type_or_string < t_css_inline_bem_l, t_css_inline_bem, sz_leading >
{ using type_or_string < t_css_inline_bem_l, t_css_inline_bem, sz_leading > :: type_or_string; };

template < > struct type_master < t_css_kbd_lhs > : type_or_string < t_css_kbd_lhs, t_css_id, sz_auto >
{ using type_or_string < t_css_kbd_lhs, t_css_id, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_kbd_rhs > : type_or_either_string < t_css_kbd_rhs, t_css_frame, sz_current, sz_root >
{ using type_or_either_string < t_css_kbd_rhs, t_css_frame, sz_current, sz_root > :: type_or_either_string; };

template < > struct type_master < t_css_kdb_nav > : type_one_or_both < t_css_kdb_nav, t_css_kbd_lhs, sz_space_char, t_css_kbd_rhs >
{ using type_one_or_both < t_css_kdb_nav, t_css_kbd_lhs, sz_space_char, t_css_kbd_rhs > :: type_one_or_both; };

template < > struct type_master < t_css_length_2 > : type_one_or_both < t_css_length_2, t_css_length, sz_space_char, t_css_length >
{ using type_one_or_both < t_css_length_2, t_css_length, sz_space_char, t_css_length > :: type_one_or_both; };

template < > struct type_master < t_css_length_3 > : type_either_or < t_css_length_3, t_css_length, t_css_fn_fit_content >
{ using type_either_or < t_css_length_3, t_css_length, t_css_fn_fit_content > :: type_either_or; };

template < > struct type_master < t_css_length_a > : type_or_string < t_css_length_a, t_css_length, sz_auto >
{ using type_or_string < t_css_length_a, t_css_length, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_length_a2 > : type_one_or_both < t_css_length_a2, t_css_length_a, sz_space_char, t_css_length_a >
{ using type_one_or_both < t_css_length_a2, t_css_length_a, sz_space_char, t_css_length_a > :: type_one_or_both; };

template < > struct type_master < t_css_length_amm > : type_or_any_string < t_css_length_amm, t_css_length_3, sz_auto, sz_max_content, sz_min_content >
{ using type_or_any_string < t_css_length_amm, t_css_length_3, sz_auto, sz_max_content, sz_min_content > :: type_or_any_string; };

template < > struct type_master < t_css_length_ai > : either_type_or_string < t_css_length_ai, t_css_inherit, t_css_length, sz_auto >
{ using either_type_or_string < t_css_length_ai, t_css_inherit, t_css_length, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_length_n > : type_or_string < t_css_length_n, t_css_length, sz_none >
{ using type_or_string < t_css_length_n, t_css_length, sz_none > :: type_or_string; };

template < > struct type_master < t_css_length_twice > : type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space_char >
{ using type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space_char > :: type_one_two; };

template < > struct type_master < t_css_lengths > : type_some_of < t_css_lengths, sz_space_char, 1, 4, t_css_length >
{ using type_some_of < t_css_lengths, sz_space_char, 1, 4, t_css_length > :: type_some_of; };

template < > struct type_master < t_css_lengths_a > : type_some_of < t_css_lengths_a, sz_space_char, 1, 4, t_css_length_a >
{ using type_some_of < t_css_lengths_a, sz_space_char, 1, 4, t_css_length_a > :: type_some_of; };

template < > struct type_master < t_css_lengths_a_l > : maybe_logical_type < t_css_lengths_a_l, t_css_lengths_a >
{ using maybe_logical_type < t_css_lengths_a_l, t_css_lengths_a > :: maybe_logical_type; };

template < > struct type_master < t_css_lengths_l > : maybe_logical_type < t_css_lengths_l, t_css_lengths >
{ using maybe_logical_type < t_css_lengths_l, t_css_lengths > :: maybe_logical_type; };

template < > struct type_master < t_css_line_height > : one_of_three_or_string < t_css_line_height, t_css_length, t_measure, t_real, sz_normal >
{ using one_of_three_or_string < t_css_line_height, t_css_length, t_measure, t_real, sz_normal > :: one_of_three_or_string; };

template < > struct type_master < t_css_ls_val > : type_one_of < t_css_ls_val, false, t_css_list_style_type, t_css_list_style_position, t_css_url >
{ using type_one_of < t_css_ls_val, false, t_css_list_style_type, t_css_list_style_position, t_css_url > :: type_one_of; };

template < > struct type_master < t_css_list_style > : type_range < t_css_list_style, sz_space_char, t_css_ls_val, 1, 3 >
{ using type_range < t_css_list_style, sz_space_char, t_css_ls_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_margins_trim_inner > : type_some_of < t_css_margins_trim_inner, sz_space_char, 1, 4, t_css_margin_trim_inner >
{ using type_some_of < t_css_margins_trim_inner, sz_space_char, 1, 4, t_css_margin_trim_inner > :: type_some_of; };

template < > struct type_master < t_css_margin_trim > : type_or_any_string < t_css_margin_trim, t_css_margins_trim_inner, sz_block, sz_inline, sz_none >
{ using type_or_any_string < t_css_margin_trim, t_css_margins_trim_inner, sz_block, sz_inline, sz_none > :: type_or_any_string; };

template < > struct type_master < t_css_margins > : type_either_or < t_css_margins, t_measures_a, t_css_inherit >
{ using type_either_or < t_css_margins, t_measures_a, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_margins_l > : maybe_logical_type < t_css_margins_l, t_css_margins >
{ using maybe_logical_type < t_css_margins_l, t_css_margins > :: maybe_logical_type; };

template < > struct type_master < t_css_marks > : type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char >
{ using type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char > :: type_one_two; };

template < > struct type_master < t_css_marx > : either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_length_abs_r > : type_either_or < t_css_length_abs_r, t_real, t_css_length_abs >
{ using type_either_or < t_css_length_abs_r, t_real, t_css_length_abs > :: type_either_or; };

template < > struct type_master < t_css_mask_border_outsets > : type_some_of < t_css_mask_border_outsets, sz_space_char, 1, 4, t_css_length_abs_r >
{ using type_some_of < t_css_mask_border_outsets, sz_space_char, 1, 4, t_css_length_abs_r > :: type_some_of; };

template < > struct type_master < t_css_mask_border_repeats > : type_some_of < t_css_mask_border_repeats, sz_space_char, 1, 2, t_css_mask_border_repeat >
{ using type_some_of < t_css_mask_border_repeats, sz_space_char, 1, 2, t_css_mask_border_repeat > :: type_some_of; };

template < > struct type_master < t_css_mask_border_slice > : type_some_of < t_css_mask_border_slice, sz_space_char, 1, 5, t_real_percent, t_real_percent, t_real_percent, t_real_percent, t_fill >
{ using type_some_of < t_css_mask_border_slice, sz_space_char, 1, 5, t_real_percent, t_real_percent, t_real_percent, t_real_percent, t_fill > :: type_some_of; };

template < > struct type_master < t_css_mask_border_width > : either_type_or_string < t_css_mask_border_width, t_real, t_css_length, sz_auto >
{ using either_type_or_string < t_css_mask_border_width, t_real, t_css_length, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_mask_border_widths > : type_some_of < t_css_mask_border_widths, sz_space_char, 1, 4, t_css_mask_border_width >
{ using type_some_of < t_css_mask_border_widths, sz_space_char, 1, 4, t_css_mask_border_width > :: type_some_of; };

template < > struct type_master < t_css_masking_modes > : type_some_of < t_css_masking_modes, sz_comma, 1, 999, t_css_masking_mode >
{ using type_some_of < t_css_masking_modes, sz_comma, 1, 999, t_css_masking_mode > :: type_some_of; };

template < > struct type_master < t_css_mask_ref > : either_type_or_string < t_css_mask_ref, t_urifn, t_css_image, sz_none >
{ using either_type_or_string < t_css_mask_ref, t_urifn, t_css_image, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_mask_refs > : type_some_of < t_css_mask_refs, sz_comma, 1, 999, t_css_mask_ref >
{ using type_some_of < t_css_mask_refs, sz_comma, 1, 999, t_css_mask_ref > :: type_some_of; };

template < > struct type_master < t_css_mask > : tidy_string < t_css_mask >
{   using tidy_string < t_css_mask > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_mask > :: set_value (nits, v, s);
        tidy_string < t_css_mask > :: status (set_css_mask_value (nits, v, tidy_string < t_css_mask > :: get_string ())); } };

template < > struct type_master < t_css_mask_border > : tidy_string < t_css_mask_border >
{   using tidy_string < t_css_mask_border > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_mask_border > :: set_value (nits, v, s);
        tidy_string < t_css_mask_border > :: status (set_css_mask_border_value (nits, v, tidy_string < t_css_mask_border > :: get_string ())); } };

template < > struct type_master < t_css_masks > : type_some_of < t_css_masks, sz_comma, 1, 999, t_css_mask >
{ using type_some_of < t_css_masks, sz_comma, 1, 999, t_css_mask > :: type_some_of; };

template < > struct type_master < t_css_nth_oe > : public type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n >
{ using type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n > :: type_or_any_string; };

template < > struct type_master < t_css_object_fit > : type_or_either_string < t_css_object_fit, t_contain_cover_sd, sz_fill, sz_none >
{ using type_or_either_string < t_css_object_fit, t_contain_cover_sd, sz_fill, sz_none > :: type_or_either_string; };

template < > struct type_master < t_css_outline_style > : type_or_string < t_css_outline_style, t_css_border_style_i, sz_auto >
{ using type_or_string < t_css_outline_style, t_css_border_style_i, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_outline > : type_one_of < t_css_outline, false, t_css_border_measure, t_css_outline_style, t_colour_ii >
{ using type_one_of < t_css_outline, false, t_css_border_measure, t_css_outline_style, t_colour_ii > :: type_one_of; };

template < > struct type_master < t_css_outlines > : type_range < t_css_outlines, sz_space_char, t_css_outline, 1, 3 >
{ using type_range < t_css_outlines, sz_space_char, t_css_outline, 1, 3 > :: type_range; };

template < > struct type_master < t_css_outline_i > : type_either_or < t_css_outline_i, t_css_inherit, t_css_outlines >
{ using type_either_or < t_css_outline_i, t_css_inherit, t_css_outlines > :: type_either_or; };

template < > struct type_master < t_css_overflows > : type_one_or_both < t_css_overflows, t_css_overflow, sz_space_char, t_css_overflow >
{ using type_one_or_both < t_css_overflows, t_css_overflow, sz_space_char, t_css_overflow > :: type_one_or_both; };

template < > struct type_master < t_css_palette_nld > : type_or_any_string < t_css_palette_nld, t_css_palette, sz_dark, sz_light, sz_normal >
{ using type_or_any_string < t_css_palette_nld, t_css_palette, sz_dark, sz_light, sz_normal > :: type_or_any_string; };

template < > struct type_master < t_css_pause_2 > : type_number_unit_3 < t_css_pause_2, t_real, sz_ms, sz_s, sz_per_cent >
{ using type_number_unit_3 < t_css_pause_2, t_real, sz_ms, sz_s, sz_per_cent > :: type_number_unit_3; };

template < > struct type_master < t_css_pause > : type_either_or < t_css_pause, t_css_pause_2, t_css_pause_3 >
{ using type_either_or < t_css_pause, t_css_pause_2, t_css_pause_3 > :: type_either_or; };

template < > struct type_master < t_css_pause_i > : type_either_or < t_css_pause_i, t_css_pause, t_css_inherit >
{ using type_either_or < t_css_pause_i, t_css_pause, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_pauses > : type_range < t_css_pauses, sz_space_char, t_css_pause_i, 1, 2 >
{ using type_range < t_css_pauses, sz_space_char, t_css_pause_i, 1, 2 > :: type_range; };

template < > struct type_master < t_css_pitch > : type_either_or < t_css_pitch, t_real, t_css_pitch_e >
{ using type_either_or < t_css_pitch, t_real, t_css_pitch_e > :: type_either_or; };

template < > struct type_master < t_css_place_content > : type_must_then_opt < t_css_place_content, t_css_align_content, sz_space_char, t_css_justify_content >
{ using type_must_then_opt < t_css_place_content, t_css_align_content, sz_space_char, t_css_justify_content > :: type_must_then_opt; };

template < > struct type_master < t_css_place_items > : type_must_then_opt < t_css_place_items, t_css_box_alignitems, sz_space_char, t_css_box_justitems >
{ using type_must_then_opt < t_css_place_items, t_css_box_alignitems, sz_space_char, t_css_box_justitems > :: type_must_then_opt; };

template < > struct type_master < t_css_place_self > : type_must_then_opt < t_css_place_self, t_css_box_alignself, sz_space_char, t_css_box_justself >
{ using type_must_then_opt < t_css_place_self, t_css_box_alignself, sz_space_char, t_css_box_justself > :: type_must_then_opt; };

template < > struct type_master < t_css_play_during > : either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none >
{ using either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none > :: either_type_or_either_string; };

template < > struct type_master < t_css_rect_fn > : type_function_all < t_css_rect_fn, sz_rect, t_measure, t_measure, t_measure, t_measure >
{ using type_function_all < t_css_rect_fn, sz_rect, t_measure, t_measure, t_measure, t_measure > :: type_function_all; };

template < > struct type_master < t_css_rect_ai > : either_type_or_string < t_css_rect_ai, t_css_rect_fn, t_css_inherit, sz_auto >
{ using either_type_or_string < t_css_rect_ai, t_css_rect_fn, t_css_inherit, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_scrollbar_gutter > : type_and_maybe_string < t_css_scrollbar_gutter, t_auto_stable, sz_space_char, sz_both_edges >
{ using type_and_maybe_string < t_css_scrollbar_gutter, t_auto_stable, sz_space_char, sz_both_edges > :: type_and_maybe_string; };

template < > struct type_master < t_css_image_processing > : type_either_or < t_css_image_processing, t_css_image_proc_e, t_angle >
{ using type_either_or < t_css_image_processing, t_css_image_proc_e, t_angle > :: type_either_or; };

template < > struct type_master < t_css_shape_outside > : one_of_three_or_string < t_css_shape_outside, t_css_shape_box, t_url, t_measure, sz_none >
{ using one_of_three_or_string < t_css_shape_outside, t_css_shape_box, t_url, t_measure, sz_none > :: one_of_three_or_string; };

template < > struct type_master < t_css_shape_position > : type_must_then_opt < t_css_shape_position, t_refx, sz_space_char, t_refy >
{ using type_must_then_opt < t_css_shape_position, t_refx, sz_space_char, t_refy > :: type_must_then_opt; };

template < > struct type_master < t_css_shape_radius > : type_or_either_string < t_css_shape_radius, t_css_length, sz_closest_side, sz_farthest_side >
{ using type_or_either_string < t_css_shape_radius, t_css_length, sz_closest_side, sz_farthest_side > :: type_or_either_string; };

template < > struct type_master < t_css_size > : type_either_or < t_css_size, t_css_orientation, t_css_length_twice >
{ using type_either_or < t_css_size, t_css_orientation, t_css_length_twice > :: type_either_or; };

template < > struct type_master < t_css_rotate_xyz > : type_or_any_string < t_css_rotate_xyz, t_3x_real, sz_x, sz_y, sz_z >
{ using type_or_any_string < t_css_rotate_xyz, t_3x_real, sz_x, sz_y, sz_z > :: type_or_any_string; };

template < > struct type_master < t_css_rotate_angle > : type_either_or < t_css_rotate_angle, t_angle, t_css_rotate_xyz >
{ using type_either_or < t_css_rotate_angle, t_angle, t_css_rotate_xyz > :: type_either_or; };

template < > struct type_master < t_css_rotate_angles > : type_either_or_both < t_css_rotate_angles, t_css_rotate_angle, sz_space_char, t_angle >
{ using type_either_or_both < t_css_rotate_angles, t_css_rotate_angle, sz_space_char, t_angle > :: type_either_or_both; };

template < > struct type_master < t_css_rotate > : type_or_string < t_css_rotate, t_css_rotate_angles, sz_none >
{ using type_or_string < t_css_rotate, t_css_rotate_angles, sz_none > :: type_or_string; };

template < > struct type_master < t_css_scale_3 > : type_some_of < t_css_scale_3, sz_space_char, 1, 3, t_real_percent, t_real_percent, t_real_percent >
{ using type_some_of < t_css_scale_3, sz_space_char, 1, 3, t_real_percent, t_real_percent, t_real_percent > :: type_some_of; };

template < > struct type_master < t_css_scale > : type_or_string < t_css_scale, t_css_scale_3, sz_none >
{ using type_or_string < t_css_scale, t_css_scale_3, sz_none > :: type_or_string; };

template < > struct type_master < t_css_speech_rate_p > : type_either_or_both < t_css_speech_rate_p, t_css_speech_rate_e, sz_space_char, t_percent_flexible >
{ using type_either_or_both < t_css_speech_rate_p, t_css_speech_rate_e, sz_space_char, t_percent_flexible > :: type_either_or_both; };

template < > struct type_master < t_css_speech_rate > : type_either_or < t_css_speech_rate, t_css_speech_rate_p, t_real >
{ using type_either_or < t_css_speech_rate, t_css_speech_rate_p, t_real > :: type_either_or; };

template < > struct type_master < t_css_ss_align > : type_one_or_both < t_css_ss_align, t_cens, sz_space_char, t_cens >
{ using type_one_or_both < t_css_ss_align, t_cens, sz_space_char, t_cens > :: type_one_or_both; };

template < > struct type_master < t_css_ss_type > : type_some_of < t_css_ss_type, sz_space_char, 0, 2, t_css_ss_type_e, t_mand_prox >
{ using type_some_of < t_css_ss_type, sz_space_char, 0, 2, t_css_ss_type_e, t_mand_prox > :: type_some_of; };

template < > struct type_master < t_css_ss_type_n > : type_or_string < t_css_ss_type_n, t_css_ss_type, sz_none >
{ using type_or_string < t_css_ss_type_n, t_css_ss_type, sz_none > :: type_or_string; };

template < > struct type_master < t_css_tech > : type_function_all < t_css_tech, sz_format, t_css_font_techs >
{ using type_function_all < t_css_tech, sz_format, t_css_font_techs > :: type_function_all; };

template < > struct type_master < t_css_text_combine_upright_d > : string_then_maybe_type < t_css_text_combine_upright_d, t_integer, sz_space_char, sz_digits >
{ using string_then_maybe_type < t_css_text_combine_upright_d, t_integer, sz_space_char, sz_digits > :: string_then_maybe_type; };

template < > struct type_master < t_css_text_combine_upright > : type_or_either_string < t_css_text_combine_upright, t_css_text_combine_upright_d, sz_all, sz_none >
{ using type_or_either_string < t_css_text_combine_upright, t_css_text_combine_upright_d, sz_all, sz_none > :: type_or_either_string; };

template < > struct type_master < t_css_text_decorations > : type_at_least_one < t_css_text_decorations, sz_space_char, t_css_text_decoration >
{ using type_at_least_one < t_css_text_decorations, sz_space_char, t_css_text_decoration > :: type_at_least_one; };

template < > struct type_master < t_css_textdec_line > : type_either_or < t_css_textdec_line, t_css_textdec_line_e, t_css_text_decorations >
{ using type_either_or < t_css_textdec_line, t_css_textdec_line_e, t_css_text_decorations > :: type_either_or; };

template < > struct type_master < t_css_textdec_short > : type_some_of < t_css_textdec_short, sz_space_char, 1, 4, t_css_textdec_line, t_css_textdec_thickness, t_css_textdec_style, t_css_colour >
{ using type_some_of < t_css_textdec_short, sz_space_char, 1, 4, t_css_textdec_line, t_css_textdec_thickness, t_css_textdec_style, t_css_colour > :: type_some_of; };

template < > struct type_master < t_css_textdec_skip_space > : type_or_either_string < t_css_textdec_skip_space, t_startends, sz_none, sz_all >
{ using type_or_either_string < t_css_textdec_skip_space, t_startends, sz_none, sz_all > :: type_or_either_string; };

template < > struct type_master < t_css_textdec_thickness > : either_type_or_either_string < t_css_textdec_thickness, t_css_length, t_percent, sz_auto, sz_from_font >
{ using either_type_or_either_string < t_css_textdec_thickness, t_css_length, t_percent, sz_auto, sz_from_font > :: either_type_or_either_string; };

template < > struct type_master < t_css_textdec_underline_offset > : either_type_or_string < t_css_textdec_underline_offset, t_css_length, t_percent, sz_auto >
{ using either_type_or_string < t_css_textdec_underline_offset, t_css_length, t_percent, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_textdec_underline_lru > : type_either_or_both < t_css_textdec_underline_lru, t_under_ff, sz_space_char, t_lralign >
{ using type_either_or_both < t_css_textdec_underline_lru, t_under_ff, sz_space_char, t_lralign > :: type_either_or_both; };

template < > struct type_master < t_css_textdec_underline > : type_or_string < t_css_textdec_underline, t_css_textdec_underline_lru, sz_auto >
{ using type_or_string < t_css_textdec_underline, t_css_textdec_underline_lru, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_textemph_pos > : type_must_then_opt < t_css_textemph_pos, t_over_under, sz_space_char, t_lralign >
{ using type_must_then_opt < t_css_textemph_pos, t_over_under, sz_space_char, t_lralign > :: type_must_then_opt; };

template < > struct type_master < t_css_textemph_substyle > : type_either_or_both < t_css_textemph_substyle, t_filled_open, sz_space_char, t_css_textemph_shape >
{ using type_either_or_both < t_css_textemph_substyle, t_filled_open, sz_space_char, t_css_textemph_shape > :: type_either_or_both; };

template < > struct type_master < t_css_textemph_style > : either_type_or_string < t_css_textemph_style, t_css_textemph_substyle, t_char, sz_none >
{ using either_type_or_string < t_css_textemph_style, t_css_textemph_substyle, t_char, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_text_emphasis > : type_either_or_both < t_css_text_emphasis, t_css_textemph_style, sz_space_char, t_css_col >
{ using type_either_or_both < t_css_text_emphasis, t_css_textemph_style, sz_space_char, t_css_col > :: type_either_or_both; };

template < > struct type_master < t_css_text_spacing > : type_ab_ba < t_css_text_spacing, sz_space_char, t_css_tst, t_css_text_autospaces >
{ using type_ab_ba < t_css_text_spacing, sz_space_char, t_css_tst, t_css_text_autospaces > :: type_ab_ba; };

template < > struct type_master < t_css_text_spacing_nan > : type_or_any_string < t_css_text_spacing_nan, t_css_text_spacing, sz_auto, sz_none, sz_normal >
{ using type_or_any_string < t_css_text_spacing_nan, t_css_text_spacing, sz_auto, sz_none, sz_normal > :: type_or_any_string; };

template < > struct type_master < t_css_text_transform_3 > : type_range < t_css_text_transform_3, sz_space_char, t_css_text_transform, 1, 5 >
{ using type_range < t_css_text_transform_3, sz_space_char, t_css_text_transform, 1, 5 > :: type_range; };

template < > struct type_master < t_css_text_transform_n > : type_or_string < t_css_text_transform_n, t_css_text_transform_3, sz_none >
{ using type_or_string < t_css_text_transform_n, t_css_text_transform_3, sz_none > :: type_or_string; };

template < > struct type_master < t_css_text_indent > : type_or_either_string < t_css_text_indent, t_css_length, sz_hanging, sz_each_line >
{ using type_or_either_string < t_css_text_indent, t_css_length, sz_hanging, sz_each_line > :: type_or_either_string; };

template < > struct type_master < t_css_texts_indent > : type_some_of < t_css_texts_indent, sz_space_char, 1, 3, t_css_text_indent >
{ using type_some_of < t_css_texts_indent, sz_space_char, 1, 3, t_css_text_indent > :: type_some_of; };

template < > struct type_master < t_css_trans_prop_a > : type_or_string < t_css_trans_prop_a, t_css_property, sz_all >
{ using type_or_string < t_css_trans_prop_a, t_css_property, sz_all > :: type_or_string; };

template < > struct type_master < t_css_trans_prop_n > : type_or_string < t_css_trans_prop_n, t_css_property, sz_none >
{ using type_or_string < t_css_trans_prop_n, t_css_property, sz_none > :: type_or_string; };

template < > struct type_master < t_css_trans_props > : type_at_least_one < t_css_trans_props, sz_comma, t_css_trans_prop_a >
{ using type_at_least_one < t_css_trans_props, sz_comma, t_css_trans_prop_a > :: type_at_least_one; };

template < > struct type_master < t_css_trans_props_n > : type_or_string < t_css_trans_props_n, t_css_trans_props, sz_none >
{ using type_or_string < t_css_trans_props_n, t_css_trans_props, sz_none > :: type_or_string; };

template < > struct type_master < t_css_transform > : type_some_of < t_css_transform, sz_space_char, 1, 999, t_fn >
{ using type_some_of < t_css_transform, sz_space_char, 1, 999, t_fn > :: type_some_of; };

template < > struct type_master < t_css_transform_origin > : type_one_of < t_css_transform_origin, false, t_lcralign, t_tbalign, t_css_length >
{ using type_one_of < t_css_transform_origin, false, t_lcralign, t_tbalign, t_css_length > :: type_one_of; };

template < > struct type_master < t_css_transform_origins > : type_at_least_one < t_css_transform_origins, sz_space_char, t_css_transform_origin >
{ using type_at_least_one < t_css_transform_origins, sz_space_char, t_css_transform_origin > :: type_at_least_one; };

template < > struct type_master < t_css_transforms > : type_at_least_one < t_css_transforms, sz_space_char, t_css_transform >
{ using type_at_least_one < t_css_transforms, sz_space_char, t_css_transform > :: type_at_least_one; };

template < > struct type_master < t_css_transform_n > : type_or_string < t_css_transform_n, t_css_transforms, sz_none >
{ using type_or_string < t_css_transform_n, t_css_transforms, sz_none > :: type_or_string; };

template < > struct type_master < t_css_transition > : type_some_of < t_css_transition, sz_space_char, 1, 4, t_css_trans_prop_n, t_duration, t_css_easing_fn, t_duration >
{ using type_some_of < t_css_transition, sz_space_char, 1, 4, t_css_trans_prop_n, t_duration, t_css_easing_fn, t_duration > :: type_some_of; };

template < > struct type_master < t_css_transitions > : type_at_least_one < t_css_transitions, sz_comma, t_css_transition >
{ using type_at_least_one < t_css_transitions, sz_comma, t_css_transition > :: type_at_least_one; };

template < > struct type_master < t_css_translate > : type_some_of < t_css_translate, sz_space_char, 1, 3, t_css_length, t_css_length, t_css_length_abs >
{ using type_some_of < t_css_translate, sz_space_char, 1, 3, t_css_length, t_css_length, t_css_length_abs > :: type_some_of; };

template < > struct type_master < t_css_translate_n > : type_or_string < t_css_translate_n, t_css_translate, sz_none >
{ using type_or_string < t_css_translate_n, t_css_translate, sz_none > :: type_or_string; };

template < > struct type_master < t_css_vertal > : type_one_of_three < t_css_vertal, t_css_length, t_percent_flexible, t_css_vertical_align >
{ using type_one_of_three < t_css_vertal, t_css_length, t_percent_flexible, t_css_vertical_align > :: type_one_of_three; };

template < > struct type_master < t_css_vertal_inline > : type_some_of < t_css_vertal_inline, sz_space_char, 1, 3, t_first_last, t_alignment_baseline, t_svg_baselineshift >
{ using type_some_of < t_css_vertal_inline, sz_space_char, 1, 3, t_first_last, t_alignment_baseline, t_svg_baselineshift > :: type_some_of; };

template < > struct type_master < t_css_voice_pitch > : type_one_of < t_css_voice_pitch, false, t_css_pitch_e, t_frequency, t_frequency_abs, t_semitone, t_percent >
{ using type_one_of < t_css_voice_pitch, false, t_css_pitch_e, t_frequency, t_frequency_abs, t_semitone, t_percent > :: type_one_of; };

template < > struct type_master < t_css_voice_volume > : type_either_or_both < t_css_voice_volume, t_css_volume_e, sz_space_char, t_decibel >
{ using type_either_or_both < t_css_voice_volume, t_css_volume_e, sz_space_char, t_decibel > :: type_either_or_both; };

template < > struct type_master < t_css_volume > : type_one_of < t_css_volume, false, t_css_volume_e, t_percent, t_fixedpoint >
{ using type_one_of < t_css_volume, false, t_css_volume_e, t_percent, t_fixedpoint > :: type_one_of; };

template < > struct type_master < t_css_wsc_val > : type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_css_colour_a >
{ using type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_css_colour_a > :: type_one_of; };

template < > struct type_master < t_css_wbd > : type_one_of_three < t_css_wbd, t_manual_normal, t_css_val_fn, t_fn >
{ using type_one_of_three < t_css_wbd, t_manual_normal, t_css_val_fn, t_fn > :: type_one_of_three; };

template < > struct type_master < t_css_border_wsc > : type_range < t_css_border_wsc, sz_space_char, t_css_wsc_val, 1, 3 >
{ using type_range < t_css_border_wsc, sz_space_char, t_css_wsc_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_border_wsc_i > : type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit >
{ using type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_backval > : type_one_of_five < t_css_backval, t_css_colour_a, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position >
{ using type_one_of_five < t_css_backval, t_css_colour_a, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position > :: type_one_of_five; };

template < > struct type_master < t_css_play_during_mr > : type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space_char, sz_mix, sz_repeat >
{ using type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space_char, sz_mix, sz_repeat > :: type_and_maybe_strings; };

template < > struct type_master < t_css_range > : type_or_string < t_css_range, t_integer, sz_infinite >
{ using type_or_string < t_css_range, t_integer, sz_infinite > :: type_or_string; };

template < > struct type_master < t_css_ranges > : type_one_or_both < t_css_ranges, t_css_range, sz_space_char, t_css_range >
{ using type_one_or_both < t_css_ranges, t_css_range, sz_space_char, t_css_range > :: type_one_or_both; };

template < > struct type_master < t_css_range_a > : type_or_string < t_css_range_a, t_css_ranges, sz_auto >
{ using type_or_string < t_css_range_a, t_css_ranges, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_speak_as_2 > : type_either_or < t_css_speak_as_2, t_css_speak_as_e, t_css_counter_style_name >
{ using type_either_or < t_css_speak_as_2, t_css_speak_as_e, t_css_counter_style_name > :: type_either_or; };

template < > struct type_master < t_css_speak_as_3 > : type_some_of < t_css_speak_as_3, sz_space_char, 1, 3, t_normal_spell, t_digits, t_literal_or_not >
{ using type_some_of < t_css_speak_as_3, sz_space_char, 1, 3, t_normal_spell, t_digits, t_literal_or_not > :: type_some_of; };

template < > struct type_master < t_css_speak_as > : type_either_or < t_css_speak_as, t_css_speak_as_2, t_css_speak_as_3 >
{ using type_either_or < t_css_speak_as, t_css_speak_as_2, t_css_speak_as_3 > :: type_either_or; };

template < > struct type_master < t_css_src_2 > : type_some_of < t_css_src_2, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_text >
{   static e_animation_type animation_type () noexcept { return at_url; }
    using type_some_of < t_css_src_2, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_text > :: type_some_of; };

template < > struct type_master < t_css_src_3 > : type_some_of < t_css_src_3, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_text >
{   static e_animation_type animation_type () noexcept { return at_url; }
    using type_some_of < t_css_src_3, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_text > :: type_some_of; };

template < > struct type_master < t_css_src_4 > : type_some_of < t_css_src_4, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_css_tech, t_text >
{   static e_animation_type animation_type () noexcept { return at_url; }
    using type_some_of < t_css_src_4, sz_space_char, 1, 0, t_css_local_url, t_css_format, t_css_tech, t_text > :: type_some_of; };

template < > struct type_master < t_css_system_ext > : string_then_type < t_css_system_ext, t_css_counter_style_name, sz_extends >
{ using string_then_type < t_css_system_ext, t_css_counter_style_name, sz_extends > :: string_then_type; };

template < > struct type_master < t_css_system_fix > : string_then_maybe_type < t_css_system_fix, t_integer, sz_space_char, sz_fixed >
{ using string_then_maybe_type < t_css_system_fix, t_integer, sz_space_char, sz_fixed > :: string_then_maybe_type; };

template < > struct type_master < t_css_system > : type_one_of_three < t_css_system, t_css_system_e, t_css_system_ext, t_css_system_fix >
{ using type_one_of_three < t_css_system, t_css_system_e, t_css_system_ext, t_css_system_fix > :: type_one_of_three; };

template < > struct type_master < t_css_text_autospaces > : type_some_of < t_css_text_autospaces, sz_space_char, 1, 5, t_css_text_autospace >
{ using type_some_of < t_css_text_autospaces, sz_space_char, 1, 5, t_css_text_autospace > :: type_some_of; };

template < > struct type_master < t_css_text_autospaces_na > : type_or_either_string < t_css_text_autospaces_na, t_css_text_autospaces, sz_auto, sz_normal >
{ using type_or_either_string < t_css_text_autospaces_na, t_css_text_autospaces, sz_auto, sz_normal > :: type_or_either_string; };

template < > struct type_master < t_css_text_justify_nc > : type_then_maybe_string < t_css_text_justify_nc, t_css_text_justify, sz_no_compress >
{ using type_then_maybe_string < t_css_text_justify_nc, t_css_text_justify, sz_no_compress > :: type_then_maybe_string; };

template < > struct type_master < t_css_tst > : type_or_any_string < t_css_tst, t_aesfs, sz_auto, sz_space_all, sz_trim_auto >
{ using type_or_any_string < t_css_tst, t_aesfs, sz_auto, sz_space_all, sz_trim_auto > :: type_or_any_string; };

template < > struct type_master < t_css_unicode_range > : type_either_or < t_css_unicode_range, t_css_unicode_from_to, t_css_unicode_wildcard >
{ using type_either_or < t_css_unicode_range, t_css_unicode_from_to, t_css_unicode_wildcard > :: type_either_or; };

template < > struct type_master < t_css_unicode_ranges > : type_at_least_one < t_css_unicode_ranges, sz_comma, t_css_unicode_range >
{ using type_at_least_one < t_css_unicode_ranges, sz_comma, t_css_unicode_range > :: type_at_least_one; };

template < > struct type_master < t_css_val_fn_n > : type_or_string < t_css_val_fn_n, t_css_val_fn, sz_none >
{ using type_or_string < t_css_val_fn_n, t_css_val_fn, sz_none > :: type_or_string; };

template < > struct type_master < t_css_voice_balance > : type_either_or < t_css_voice_balance, t_css_voice_balance_e, t_m100_to_100r >
{ using type_either_or < t_css_voice_balance, t_css_voice_balance_e, t_m100_to_100r > :: type_either_or; };

template < > struct type_master < t_css_voice_family_desc > : type_some_of < t_css_voice_family_desc, sz_space_char, 1, 3, t_css_voice_age, t_css_voice_gender, t_unsigned_1_more >
{ using type_some_of < t_css_voice_family_desc, sz_space_char, 1, 3, t_css_voice_age, t_css_voice_gender, t_unsigned_1_more > :: type_some_of; };

template < > struct type_master < t_css_voice_family > : type_one_of_three < t_css_voice_family, t_css_voice_family_desc, t_id, t_text >
{ using type_one_of_three < t_css_voice_family, t_css_voice_family_desc, t_id, t_text > :: type_one_of_three; };

template < > struct type_master < t_css_voice_families > : type_at_least_one < t_css_voice_families, sz_comma, t_css_voice_family >
{ using type_at_least_one < t_css_voice_families, sz_comma, t_css_voice_family > :: type_at_least_one; };

template < > struct type_master < t_css_voice_families_p > : type_or_either_string < t_css_voice_families_p, t_css_voice_families, sz_inherit, sz_preserve >
{ using type_or_either_string < t_css_voice_families_p, t_css_voice_families, sz_inherit, sz_preserve > :: type_or_either_string; };

template < > struct type_master < t_css_wc > : type_either_or < t_css_wc, t_css_wc_e, t_css_property >
{ using type_either_or < t_css_wc, t_css_wc_e, t_css_property > :: type_either_or; };

template < > struct type_master < t_css_wcs > : type_some_of < t_css_wcs, sz_comma, 1, 999, t_css_wc >
{ using type_some_of < t_css_wcs, sz_comma, 1, 999, t_css_wc > :: type_some_of; };

template < > struct type_master < t_css_wcs_a > : type_or_string < t_css_wcs_a, t_css_wcs, sz_auto >
{ using type_or_string < t_css_wcs_a, t_css_wcs, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_ws_wsc > : type_either_or < t_css_ws_wsc, t_css_whitespace, t_css_wcs >
{ using type_either_or < t_css_ws_wsc, t_css_whitespace, t_css_wcs > :: type_either_or; };

template < > struct type_master < t_css_wsts > : type_some_of < t_css_wsts, sz_space_char, 1, 3, t_css_wst >
{ using type_some_of < t_css_wsts, sz_space_char, 1, 3, t_css_wst > :: type_some_of; };

template < > struct type_master < t_css_whitespace_4 > : type_some_of < t_css_whitespace_4, sz_space_char, 1, 3, t_css_ws_wsc, t_css_wsts, t_css_text_wrap >
{ using type_some_of < t_css_whitespace_4, sz_space_char, 1, 3, t_css_ws_wsc, t_css_wsts, t_css_text_wrap > :: type_some_of; };

template < > struct type_master < t_css_langs > : string_vector < t_css_langs, sz_comma >
{   using string_vector < t_css_langs, sz_comma > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_langs, sz_comma > :: set_value (nits, v, s);
        string_vector < t_css_langs, sz_comma > :: status (set_css_lang_value (nits, v, string_vector < t_css_langs, sz_comma > :: get ())); } };

template < > struct type_master < t_css_col > : tidy_string < t_css_col >
{   using tidy_string < t_css_col > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_col > :: set_value (nits, v, s);
        tidy_string < t_css_col > :: status (set_css_col_value (nits, v, tidy_string < t_css_col > :: get_string ())); } };

template < > struct type_master < t_css_background_attachments > : tidy_string < t_css_background_attachments >
{   using tidy_string < t_css_background_attachments > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_attachments > :: set_value (nits, v, s);
        tidy_string < t_css_background_attachments > :: status (set_css_background_attachments_value (nits, v, tidy_string < t_css_background_attachments > :: get_string (), box ())); } };

template < > struct type_master < t_css_background > : tidy_string < t_css_background >
{   using tidy_string < t_css_background > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background > :: set_value (nits, v, s);
        tidy_string < t_css_background > :: status (set_css_background_value (nits, v, tidy_string < t_css_background > :: get_string (), box ())); } };

template < > struct type_master < t_css_background_position_3 > : tidy_string < t_css_background_position_3 >
{   using tidy_string < t_css_background_position_3 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_position_3 > :: set_value (nits, v, s);
        tidy_string < t_css_background_position_3 > :: status (set_css_background_position_3_value (nits, v, tidy_string < t_css_background_position_3 > :: get_string (), box ())); } };

template < > struct type_master < t_css_background_repeat_3 > : tidy_string < t_css_background_repeat_3 >
{   using tidy_string < t_css_background_repeat_3 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_repeat_3 > :: set_value (nits, v, s);
        tidy_string < t_css_background_repeat_3 > :: status (set_css_background_repeat_3_value (nits, v, tidy_string < t_css_background_repeat_3 > :: get_string (), box ())); } };

template < > struct type_master < t_css_display_1 > : tidy_string < t_css_display_1 >
{   using tidy_string < t_css_display_1 > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_display_1 > :: set_value (nits, v, s);
        tidy_string < t_css_display_1 > :: status (set_css_display_1_value (nits, v, tidy_string < t_css_display_1 > :: get_string ())); } };

template < > struct type_master < t_css_font_size_4 > : tidy_string < t_css_font_size_4 >
{   using tidy_string < t_css_font_size_4 > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_size_4 > :: set_value (nits, v, s);
        tidy_string < t_css_font_size_4 > :: status (set_css_font_size_4_value (nits, v, tidy_string < t_css_font_size_4 > :: get_string ())); } };

template < > struct type_master < t_css_font_size_adjust > : string_vector < t_css_font_size_adjust, sz_space_char >
{   using string_vector < t_css_font_size_adjust, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_font_size_adjust, sz_space_char > :: set_value (nits, v, s);
        string_vector < t_css_font_size_adjust, sz_space_char > :: status (set_css_font_size_adjust_value (nits, v, string_vector < t_css_font_size_adjust, sz_space_char > :: get ())); } };

template < > struct type_master < t_css_font_style_a > : string_vector < t_css_font_style_a, sz_space_char >
{   using string_vector < t_css_font_style_a, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_font_style_a, sz_space_char > :: set_value (nits, v, s);
        string_vector < t_css_font_style_a, sz_space_char > :: status (set_css_font_style_a_value (nits, v, string_vector < t_css_font_style_a, sz_space_char > :: get ())); } };

template < > struct type_master < t_css_list_style_type_cs > : tidy_string < t_css_list_style_type_cs >
{   using tidy_string < t_css_list_style_type_cs > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_list_style_type_cs > :: set_value (nits, v, s);
        tidy_string < t_css_list_style_type_cs > :: status (set_css_list_style_type_cs_value (nits, v, tidy_string < t_css_list_style_type_cs > :: get_string ())); } };

template < > struct type_master < t_css_speak > : tidy_string < t_css_speak >
{   using tidy_string < t_css_speak > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_speak > :: set_value (nits, v, s);
        tidy_string < t_css_speak > :: status (set_css_speak_value (nits, v, tidy_string < t_css_speak > :: get_string (), box ())); } };

template < > struct type_master < t_css_src > : tidy_string < t_css_src >
{   using tidy_string < t_css_src > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_src > :: set_value (nits, v, s);
        tidy_string < t_css_src > :: status (set_css_src_value (nits, v, tidy_string < t_css_src > :: get_string ())); } };

template < > struct type_master < t_css_cross_fade_colour > : type_either_or < t_css_cross_fade_colour, t_css_col, t_css_image >
{ using type_either_or < t_css_cross_fade_colour, t_css_col, t_css_image > :: type_either_or; };

template < > struct type_master < t_css_cross_fade > : type_opt_then_must < t_css_cross_fade, t_percent, sz_space_char, t_css_cross_fade_colour >
{ using type_opt_then_must < t_css_cross_fade, t_percent, sz_space_char, t_css_cross_fade_colour > :: type_opt_then_must; };

template < > struct type_master < t_font_variant_4 > : type_some_of < t_font_variant_4, sz_space_char, 1, 0,
    t_font_variant_2, t_css_fn_annotation, t_css_fn_character_variant, t_css_fn_ornaments, t_css_fn_styleset, t_css_fn_stylistic, t_css_fn_swash >
{ using type_some_of < t_font_variant_4, sz_space_char, 1, 0,
    t_font_variant_2, t_css_fn_annotation, t_css_fn_character_variant, t_css_fn_ornaments, t_css_fn_styleset, t_css_fn_stylistic, t_css_fn_swash > :: type_some_of; };

template < > struct type_master < t_css_font_variant_4 > : type_or_either_string < t_css_font_variant_4, t_font_variant_4, sz_none, sz_normal >
{ using type_or_either_string < t_css_font_variant_4, t_font_variant_4, sz_none, sz_normal > :: type_or_either_string; };

template < > struct type_master < t_css_override_colour > : type_either_or < t_css_override_colour, t_unsigned, t_css_col >
{ using type_either_or < t_css_override_colour, t_unsigned, t_css_col > :: type_either_or; };

template < > struct type_master < t_css_override_colours > : type_some_of < t_css_override_colours, sz_comma, 1, 0, t_css_override_colour >
{   static e_animation_type animation_type () noexcept { return at_colour; }
    using type_some_of < t_css_override_colours, sz_comma, 1, 0, t_css_override_colour > :: type_some_of; };

template < > struct type_master < t_css_srcs > : type_at_least_one < t_css_srcs, sz_comma, t_css_src >
{ using type_at_least_one < t_css_srcs, sz_comma, t_css_src > :: type_at_least_one; };

template < > struct type_master < t_css_sym > : type_either_or < t_css_sym, t_css_image, t_text >
{ using type_either_or < t_css_sym, t_css_image, t_text > :: type_either_or; };

template < > struct type_master < t_css_addsym > : type_either_or_both < t_css_addsym, t_unsigned, sz_space_char, t_css_sym >
{ using type_either_or_both < t_css_addsym, t_unsigned, sz_space_char, t_css_sym > :: type_either_or_both; };

template < > struct type_master < t_css_addsyms > : type_some_flagged_of < t_css_addsyms, sz_comma, UQ_TRIM, 1, 0, t_css_addsym >
{ using type_some_flagged_of < t_css_addsyms, sz_comma, UQ_TRIM, 1, 0, t_css_addsym > :: type_some_flagged_of; };

template < > struct type_master < t_conic_1 > : type_either_or < t_conic_1, t_to_lrtb, t_from_angle >
{ using type_either_or < t_conic_1, t_to_lrtb, t_from_angle > :: type_either_or; };

template < > struct type_master < t_conic_2 > : type_either_or_both < t_conic_2, t_conic_1, sz_space_char, t_css_coin1 >
{ using type_either_or_both < t_conic_2, t_conic_1, sz_space_char, t_css_coin1 > :: type_either_or_both; };

template < > struct type_master < t_angle_lrtb > : type_one_of_four < t_angle_lrtb, t_angle, t_to_lrtb, t_css_coin1, t_empty >
{ using type_one_of_four < t_angle_lrtb, t_angle, t_to_lrtb, t_css_coin1, t_empty > :: type_one_of_four; };

template < > struct type_master < t_radial_4 > : type_one_or_both < t_radial_4, t_radial_1, sz_space_char, t_css_coin1 >
{ using type_one_or_both < t_radial_4, t_radial_1, sz_space_char, t_css_coin1 > :: type_one_or_both; };

template < > struct type_master < t_css_container > : tidy_string < t_css_container >
{   using tidy_string < t_css_container > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_container > :: set_value (nits, v, s);
        tidy_string < t_css_container > :: status (set_css_container_value (nits, v, tidy_string < t_css_container > :: get_string ())); } };
