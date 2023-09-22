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

template < > struct type_master < t_css_borders_measure > : type_range < t_css_borders_measure, sz_space_char, t_css_border_measure, 1, 4 >
{ using type_range < t_css_borders_measure, sz_space_char, t_css_border_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_css_borders_measure_i > : type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit >
{ using type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_radius > : type_some_of < t_css_border_radius, sz_space_char, 1, 9,
    t_css_length, t_css_length, t_css_length, t_css_length, t_slash, t_css_length, t_css_length, t_css_length, t_css_length >
{ using type_some_of < t_css_border_radius, sz_space_char, 1, 9,
    t_css_length, t_css_length, t_css_length, t_css_length, t_slash, t_css_length, t_css_length, t_css_length, t_css_length > :: type_some_of; };

template < > struct type_master < t_css_border_spacing_2 > : type_range < t_css_border_spacing_2, sz_space_char, t_css_length, 1, 2 >
{ using type_range < t_css_border_spacing_2, sz_space_char, t_css_length, 1, 2 > :: type_range; };

template < > struct type_master < t_css_border_spacing > : type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit >
{ using type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_styles > : type_range < t_css_border_styles, sz_space_char, t_css_border_style, 1, 4 >
{ using type_range < t_css_border_styles, sz_space_char, t_css_border_style, 1, 4 > :: type_range; };

template < > struct type_master < t_css_border_style_i > : type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit >
{ using type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit > :: type_either_or; };

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

template < > struct type_master < t_css_cols > : type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col >
{ using type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col > :: type_some_of; };

template < > struct type_master < t_css_column_rule > : type_some_of < t_css_column_rule, sz_space_char, 1, 3, t_css_border_measure, t_css_border_style, t_css_col >
{ using type_some_of < t_css_column_rule, sz_space_char, 1, 3, t_css_border_measure, t_css_border_style, t_css_col > :: type_some_of; };

template < > struct type_master < t_css_columns > : type_ab_ba < t_css_columns, sz_space_char, t_measure_a, t_unsigned_1_more_a >
{ using type_ab_ba < t_css_columns, sz_space_char, t_measure_a, t_unsigned_1_more_a > :: type_ab_ba; };

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

template < > struct type_master < t_css_cue > : either_type_or_string < t_css_cue, t_urifn_db, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_cue, t_urifn_db, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_cues > : type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 >
{ using type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 > :: type_range; };

template < > struct type_master < t_urifn_xy > : type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 >
{ using type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 > :: type_must_then_opt; };

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

template < > struct type_master < t_css_hue > : type_either_or < t_css_hue, t_angle, t_real >
{ using type_either_or < t_css_hue, t_angle, t_real > :: type_either_or; };

template < > struct type_master < t_css_hue_n > : type_or_string < t_css_hue_n, t_css_hue, sz_none >
{ using type_or_string < t_css_hue_n, t_css_hue, sz_none > :: type_or_string; };

template < > struct type_master < t_css_image > : type_or_string < t_css_image, t_css_url, sz_none >
{ using type_or_string < t_css_image, t_css_url, sz_none > :: type_or_string; };

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

template < > struct type_master < t_css_length_twice > : type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space_char >
{ using type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space_char > :: type_one_two; };

template < > struct type_master < t_css_lengths > : type_some_of < t_css_lengths, sz_space_char, 1, 4, t_css_length >
{ using type_some_of < t_css_lengths, sz_space_char, 1, 4, t_css_length > :: type_some_of; };

template < > struct type_master < t_css_lengths_a > : type_some_of < t_css_lengths_a, sz_space_char, 1, 4, t_css_length_a >
{ using type_some_of < t_css_lengths_a, sz_space_char, 1, 4, t_css_length_a > :: type_some_of; };

template < > struct type_master < t_css_line_height > : either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal >
{ using either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal > :: either_type_or_string; };

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

template < > struct type_master < t_css_marks > : type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char >
{ using type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char > :: type_one_two; };

template < > struct type_master < t_css_marx > : either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_font_named_instance > : type_or_string < t_css_font_named_instance, t_text, sz_auto >
{ using type_or_string < t_css_font_named_instance, t_text, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_nth_oe > : public type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n >
{ using type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n > :: type_or_any_string; };

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

template < > struct type_master < t_css_shape_outside > : one_of_three_or_string < t_css_shape_outside, t_css_shape_box, t_url, t_measure, sz_none >
{ using one_of_three_or_string < t_css_shape_outside, t_css_shape_box, t_url, t_measure, sz_none > :: one_of_three_or_string; };

template < > struct type_master < t_css_shape_position > : type_must_then_opt < t_css_shape_position, t_refx, sz_space_char, t_refy >
{ using type_must_then_opt < t_css_shape_position, t_refx, sz_space_char, t_refy > :: type_must_then_opt; };

template < > struct type_master < t_css_shape_radius > : type_or_either_string < t_css_shape_radius, t_css_length, sz_closest_side, sz_farthest_side >
{ using type_or_either_string < t_css_shape_radius, t_css_length, sz_closest_side, sz_farthest_side > :: type_or_either_string; };

template < > struct type_master < t_css_size > : type_either_or < t_css_size, t_css_orientation, t_css_length_twice >
{ using type_either_or < t_css_size, t_css_orientation, t_css_length_twice > :: type_either_or; };

template < > struct type_master < t_css_spacing > : either_type_or_string < t_css_spacing, t_css_length, t_css_inherit, sz_normal >
{ using either_type_or_string < t_css_spacing, t_css_length, t_css_inherit, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_css_speech_rate_p > : type_either_or_both < t_css_speech_rate_p, t_css_speech_rate_e, sz_space_char, t_percent_flexible >
{ using type_either_or_both < t_css_speech_rate_p, t_css_speech_rate_e, sz_space_char, t_percent_flexible > :: type_either_or_both; };

template < > struct type_master < t_css_speech_rate > : type_either_or < t_css_speech_rate, t_css_speech_rate_p, t_real >
{ using type_either_or < t_css_speech_rate, t_css_speech_rate_p, t_real > :: type_either_or; };

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

template < > struct type_master < t_css_trans_prop_a > : type_or_string < t_css_trans_prop_a, t_css_property, sz_all >
{ using type_or_string < t_css_trans_prop_a, t_css_property, sz_all > :: type_or_string; };

template < > struct type_master < t_css_trans_prop_n > : type_or_string < t_css_trans_prop_n, t_css_property, sz_none >
{ using type_or_string < t_css_trans_prop_n, t_css_property, sz_none > :: type_or_string; };

template < > struct type_master < t_css_trans_props > : type_at_least_one < t_css_trans_props, sz_comma, t_css_trans_prop_a >
{ using type_at_least_one < t_css_trans_props, sz_comma, t_css_trans_prop_a > :: type_at_least_one; };

template < > struct type_master < t_css_trans_props_n > : type_or_string < t_css_trans_props_n, t_css_trans_props, sz_none >
{ using type_or_string < t_css_trans_props_n, t_css_trans_props, sz_none > :: type_or_string; };

template < > struct type_master < t_css_transition > : type_some_of < t_css_transition, sz_space_char, 1, 4, t_css_trans_prop_n, t_duration, t_css_easing_fn, t_duration >
{ using type_some_of < t_css_transition, sz_space_char, 1, 4, t_css_trans_prop_n, t_duration, t_css_easing_fn, t_duration > :: type_some_of; };

template < > struct type_master < t_css_transitions > : type_at_least_one < t_css_transitions, sz_comma, t_css_transition >
{ using type_at_least_one < t_css_transitions, sz_comma, t_css_transition > :: type_at_least_one; };

template < > struct type_master < t_css_vertal > : type_one_of_three < t_css_vertal, t_css_length, t_percent_flexible, t_css_vertical_align >
{ using type_one_of_three < t_css_vertal, t_css_length, t_percent_flexible, t_css_vertical_align > :: type_one_of_three; };

template < > struct type_master < t_css_voice_pitch > : type_one_of < t_css_voice_pitch, false, t_css_pitch_e, t_frequency, t_frequency_abs, t_semitone, t_percent >
{ using type_one_of < t_css_voice_pitch, false, t_css_pitch_e, t_frequency, t_frequency_abs, t_semitone, t_percent > :: type_one_of; };

template < > struct type_master < t_css_voice_volume > : type_either_or_both < t_css_voice_volume, t_css_volume_e, sz_space_char, t_decibel >
{ using type_either_or_both < t_css_voice_volume, t_css_volume_e, sz_space_char, t_decibel > :: type_either_or_both; };

template < > struct type_master < t_css_volume > : type_one_of < t_css_volume, false, t_css_volume_e, t_percent, t_fixedpoint >
{ using type_one_of < t_css_volume, false, t_css_volume_e, t_percent, t_fixedpoint > :: type_one_of; };

template < > struct type_master < t_css_wsc_val > : type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_css_colour_a >
{ using type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_css_colour_a > :: type_one_of; };

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

template < > struct type_master < t_css_unicode_range > : type_either_or < t_css_unicode_range, t_css_unicode_from_to, t_css_unicode_wildcard >
{ using type_either_or < t_css_unicode_range, t_css_unicode_from_to, t_css_unicode_wildcard > :: type_either_or; };

template < > struct type_master < t_css_unicode_ranges > : type_at_least_one < t_css_unicode_ranges, sz_comma, t_css_unicode_range >
{ using type_at_least_one < t_css_unicode_ranges, sz_comma, t_css_unicode_range > :: type_at_least_one; };

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

template < > struct type_master < t_css_langs > : string_vector < t_css_langs, sz_comma >
{   using string_vector < t_css_langs, sz_comma > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_langs, sz_comma > :: set_value (nits, v, s);
        if (string_vector < t_css_langs, sz_comma > :: empty ())
            nits.pick (nit_bad_itemprop, es_error, ec_type, "lang() requires a parameter");
        else if (string_vector < t_css_langs, sz_comma > :: good ())
        {   bool ok = true;
            for (auto t : string_vector < t_css_langs, sz_comma > :: get ())
                if (! test_value < t_css_lang > (nits, v, t))
                    ok = false;
            if (ok) return; }
       tidy_string < t_css_langs > :: status (s_invalid); } };

template < > struct type_master < t_css_col > : tidy_string < t_css_col >
{   using tidy_string < t_css_col > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_col > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_col > :: get_string ();
        if (s.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a colour expected");
        else if (good ())
        {   nitpick nuts, nets, nots, nats;
            const ::std::string ss (tidy_string < t_css_col > :: get_string ());
            switch (v.css_colour ())
            {   case 5 :
                case 4 :
                    if (test_value < t_css_colour_4 > (nuts, v, arg))
                    {   nits.merge (nuts);
                        tidy_string < t_css_col > :: status (s_good);
                        return; }
                    FALLTHROUGH;
                case 3 :
                    if (test_value < t_css_colour_3 > (nets, v, arg))
                    {   nits.merge (nets);
                        tidy_string < t_css_col > :: status (s_good);
                        return; }
                    FALLTHROUGH;
                default :
                    if (test_value < t_css_colour > (nots, v, arg))
                    {   nits.merge (nots);
                        tidy_string < t_css_col > :: status (s_good);
                        return; }
                    if (test_value < t_colour > (nats, v, arg))
                    {   nits.merge (nats);
                        tidy_string < t_css_col > :: status (s_good);
                        return; }
                    if (compare_no_case (ss, "inherit"))
                    {   tidy_string < t_css_col > :: status (s_good);
                        return; }
                    break; }
            nits.pick (nit_css_colour, es_error, ec_css, quote (ss), " is invalid in CSS ", v.long_css_version_name ());
            if (context.extra () || context.tell (es_debug))
            {   nits.merge (nuts);
                nits.merge (nets);
                nits.merge (nots);
                nits.merge (nats); } }
        tidy_string < t_css_col > :: status (s_invalid); } };

template < > struct type_master < t_css_background_attachments > : tidy_string < t_css_background_attachments >
{   using tidy_string < t_css_background_attachments > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_attachments > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_background_attachments > :: get_string ();
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
        else if (good ())
        {   if (v.css_background () < 3)
            {   type_master < t_css_background_attachment > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_css_background_attachment_3 > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; } }
        tidy_string < t_css_background_attachments > :: status (s_invalid); } };

template < > struct type_master < t_css_background > : tidy_string < t_css_background >
{   using tidy_string < t_css_background > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_background > :: get_string ();
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
        else if (good ())
        {   if (v.css_background () < 3)
            {   type_master < t_css_background_0 > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_svg_src > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; } }
        tidy_string < t_css_background > :: status (s_invalid); } };

template < > struct type_master < t_css_background_position_3 > : tidy_string < t_css_background_position_3 >
{   using tidy_string < t_css_background_position_3 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_position_3 > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_background_position_3 > :: get_string ();
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
        else if (good ())
        {   if (v.css_background () < 3)
            {   type_master < t_css_background_position > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_css_background_positions > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; } }
        tidy_string < t_css_background_position_3 > :: status (s_invalid); } };

template < > struct type_master < t_css_background_repeat_3 > : tidy_string < t_css_background_repeat_3 >
{   using tidy_string < t_css_background_repeat_3 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_background_repeat_3 > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_background_repeat_3 > :: get_string ();
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
        else if (good ())
        {   if (v.css_background () < 3)
            {   type_master < t_css_background_repeat > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_css_background_repeats > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; } }
        tidy_string < t_css_background_repeat_3 > :: status (s_invalid); } };

template < > struct type_master < t_css_display_1 > : tidy_string < t_css_display_1 >
{   using tidy_string < t_css_display_1 > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_display_1 > :: set_value (nits, v, s);
        if (tidy_string < t_css_display_1 > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "display cannot be empty");
        else if (tidy_string < t_css_display_1 > :: good ())
            if (v.css_display () == 0)
            {   if (test_value < t_css_display > (nits, v, s)) return; }
            else if (test_value < t_css_display_3 > (nits, v, s)) return;
        tidy_string < t_css_display_1 > :: status (s_invalid); } };

template < > struct type_master < t_css_font_size_4 > : tidy_string < t_css_font_size_4 >
{   using tidy_string < t_css_font_size_4 > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_size_4 > :: set_value (nits, v, s);
        if (tidy_string < t_css_font_size_4 > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "font-size cannot be empty");
        else if (tidy_string < t_css_font_size_4 > :: good ())
        {   const ::std::string& ss (tidy_string < t_css_font_size_4 > :: get_string ());
            if ((context.css_font () >= 4) && compare_no_case (ss, "math")) return;
            if (test_value < t_css_font_size > (nits, v, s)) return; }
        tidy_string < t_css_font_size_4 > :: status (s_invalid); } };

template < > struct type_master < t_css_font_size_adjust > : string_vector < t_css_font_size_adjust, sz_space_char >
{   using string_vector < t_css_font_size_adjust, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_font_size_adjust, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_css_font_size_adjust, sz_space_char > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "font-size-adjust cannot be empty");
        else if (string_vector < t_css_font_size_adjust, sz_space_char > :: good ())
        {   const vstr_t& vs (string_vector < t_css_font_size_adjust, sz_space_char > :: get ());
            const ::std::size_t len (vs.size ());
            PRESUME (len > 0, __FILE__, __LINE__);  
            if (v.css_font () < 5)
            {   if (len > 1) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (0))); 
                if (test_value < t_real_ni > (nits, v, vs.at (0))) return; }
            else if (compare_no_case (vs.at (0), "none"))
            {   if (len > 1) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (0))); 
                return; }
            else
            {   ::std::size_t pos = 0;
                nitpick nuts;
                if (test_value < t_css_font_size_adjust_e > (nuts, v, vs.at (0)))
                {   nits.merge (nuts);
                    ++pos; }
                if ((vs.size () > pos) && compare_no_case (vs.at (pos), "from-font")) ++pos;
                if ((vs.size () > pos) && test_value < t_real > (nits, v, vs.at (pos)))
                {   if (len > pos) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (pos))); 
                    return; }
                if (pos >= vs.size ()) nits.pick (nit_css_syntax, es_error, ec_css, "number expected"); } }
        string_vector < t_css_font_size_adjust, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_css_font_style_a > : string_vector < t_css_font_style_a, sz_space_char >
{   using string_vector < t_css_font_style_a, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_font_style_a, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_css_font_style_a, sz_space_char > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "font-style cannot be empty");
        else if (string_vector < t_css_font_style_a, sz_space_char > :: good ())
        {   const vstr_t& vs (string_vector < t_css_font_style_a, sz_space_char > :: get ());
            type_master < t_css_font_style > cf;
            cf.set_value (nits, v, vs.at (0));
            if (cf.good ())
            {   if (vs.size () == 1) return;
                if (compare_no_case (cf.original (), "oblique"))
                {   if (vs.size () > 2) nits.pick (nit_css_syntax, es_warning, ec_css, "junk found after ", quote (vs.at (1)));
                    if (test_value < t_angle > (nits, v, vs.at (1))) return; }
                else nits.pick (nit_css_syntax, es_warning, ec_css, "junk found after ", quote (vs.at (0))); } }
        string_vector < t_css_font_style_a, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_css_list_style_type_cs > : tidy_string < t_css_list_style_type_cs >
{   using tidy_string < t_css_list_style_type_cs > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   nitpick nuts;
        if (test_value < t_css_list_style_type > (nuts, v, s))
        {   tidy_string < t_css_list_style_type_cs > :: status (s_good);
            nits.merge (nuts);
            return; }
        if (v.css_counter_style () >= 3)
        {   if (! test_value < t_css_counter_style_name > (nuts, v, s))
                nits.pick (nit_counter_style, es_comment, ec_css, quote (s), ": not a recognised counter style");
            tidy_string < t_css_list_style_type_cs > :: status (s_good);
            return; }
        tidy_string < t_css_list_style_type_cs > :: status (s_invalid); } };

template < > struct type_master < t_css_speak > : tidy_string < t_css_speak >
{   using tidy_string < t_css_speak > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_speak > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_speak > :: get_string ();
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
        else if (good ())
        {   if (v.css_speech () >= 3)
            {   type_master < t_css_speak_3 > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else if ((v.css_version () == css_2_1) || (v.css_version () == css_2_2))
            {   type_master < t_css_speak_2 > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else nits.pick (nit_css_version, es_error, ec_css, "CSS Speak requires CSS 2.1, 2.2, or CSS Speech"); }
        tidy_string < t_css_speak > :: status (s_invalid); } };
template < > struct type_master < t_css_src > : tidy_string < t_css_src >
{   using tidy_string < t_css_src > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_src > :: status (s_good);
        if (context.css_font () >= 4)
        {   if (test_value < t_css_src_4 > (nits, v, s)) return; }
        else if (context.css_font () == 3)  
        {   if (test_value < t_css_src_3 > (nits, v, s)) return; }
        else if (context.css_version () == css_2_0)
        {   if (test_value < t_css_src_2 > (nits, v, s)) return; }
        else nits.pick (nit_css_version, es_error, ec_css, "@font-face requires CSS Fonts or CSS 2.0"); 
        tidy_string < t_css_src > :: status (s_invalid); } };

template < > struct type_master < t_css_srcs > : type_at_least_one < t_css_srcs, sz_comma, t_css_src >
{ using type_at_least_one < t_css_srcs, sz_comma, t_css_src > :: type_at_least_one; };

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

template < > struct type_master < t_css_sym > : type_either_or < t_css_sym, t_css_image, t_text >
{ using type_either_or < t_css_sym, t_css_image, t_text > :: type_either_or; };

template < > struct type_master < t_css_addsym > : type_either_or_both < t_css_addsym, t_unsigned, sz_space_char, t_css_sym >
{ using type_either_or_both < t_css_addsym, t_unsigned, sz_space_char, t_css_sym > :: type_either_or_both; };

template < > struct type_master < t_css_addsyms > : type_some_flagged_of < t_css_addsyms, sz_comma, UQ_TRIM, 1, 0, t_css_addsym >
{ using type_some_flagged_of < t_css_addsyms, sz_comma, UQ_TRIM, 1, 0, t_css_addsym > :: type_some_flagged_of; };
