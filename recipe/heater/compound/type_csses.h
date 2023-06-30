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
    t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachments, t_css_background_box, t_css_background_box >
{ using type_some_of < t_css_background_2, sz_space_char, 1, 999,
    t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachments, t_css_background_box, t_css_background_box > :: type_some_of; };

template < > struct type_master < t_css_background_3 > : type_some_of < t_css_background_3, sz_space_char, 1, 999,
    t_css_colour, t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachment, t_css_background_box, t_css_background_box >
{ using type_some_of < t_css_background_3, sz_space_char, 1, 999,
    t_css_colour, t_css_image, t_css_background_positions, t_slash, t_css_background_size, t_css_background_repeat, t_css_background_attachment, t_css_background_box, t_css_background_box > :: type_some_of; };

template < > struct type_master < t_css_background_attachment_3 > : type_at_least_one < t_css_background_attachment_3, sz_comma, t_css_background_attachment >
{ using type_at_least_one < t_css_background_attachment_3, sz_comma, t_css_background_attachment > :: type_at_least_one; };

template < > struct type_master < t_css_background_boxes > : type_at_least_one < t_css_background_boxes, sz_comma, t_css_background_box >
{ using type_at_least_one < t_css_background_boxes, sz_comma, t_css_background_box > :: type_at_least_one; };

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

template < > struct type_master < t_css_box_shadow > : type_some_of < t_css_box_shadow, sz_space_char, 1, 6, t_css_col, t_css_length, t_css_length, t_css_length, t_css_length, t_inset >
{ using type_some_of < t_css_box_shadow, sz_space_char, 1, 6, t_css_col, t_css_length, t_css_length, t_css_length, t_css_length, t_inset > :: type_some_of; };

template < > struct type_master < t_css_box_shadows > : type_at_least_one < t_css_box_shadows, sz_comma, t_css_box_shadow >
{ using type_at_least_one < t_css_box_shadows, sz_comma, t_css_box_shadow > :: type_at_least_one; };

template < > struct type_master < t_css_box_shadows_n > : type_or_string < t_css_box_shadows_n, t_css_box_shadows, sz_none >
{ using type_or_string < t_css_box_shadows_n, t_css_box_shadows, sz_none > :: type_or_string; };

template < > struct type_master < t_css_colour_3 > : type_one_of < t_css_colour_3, false, t_css_colour, t_colour_i, t_transparentsz, t_current_colour_sz, t_hslfn, t_hslafn, t_rgbafn >
{ using type_one_of < t_css_colour_3, false, t_css_colour, t_colour_i, t_transparentsz, t_current_colour_sz, t_hslfn, t_hslafn, t_rgbafn > :: type_one_of; };

template < > struct type_master < t_css_colour_4 > : type_one_of < t_css_colour_4, false, t_css_colour, t_colour, t_transparentsz, t_current_colour_sz,
    t_colourfn, t_hslfn4, t_hwbfn, t_labfn, t_lchfn, t_oklabfn, t_oklchfn, t_rgbfn, t_hslfn, t_hslafn, t_rgbafn >
{ using type_one_of < t_css_colour_4, false, t_css_colour, t_colour, t_transparentsz, t_current_colour_sz,
    t_colourfn, t_hslfn4, t_hwbfn, t_labfn, t_lchfn, t_oklabfn, t_oklchfn, t_rgbfn, t_hslfn, t_hslafn, t_rgbafn > :: type_one_of; };

template < > struct type_master < t_css_colour_a > : type_or_string < t_css_colour_a, t_css_col, sz_auto >
{ using type_or_string < t_css_colour_a, t_css_col, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_coin3 > : type_opt_then_must < t_css_coin3, t_css_hue_interpolation, sz_space_char, t_css_hue >
{ using type_opt_then_must < t_css_coin3, t_css_hue_interpolation, sz_space_char, t_css_hue > :: type_opt_then_must; };

template < > struct type_master < t_css_coin2 > : type_must_then_opt < t_css_coin2, t_css_polar, sz_space_char, t_css_coin3, 0, 1 >
{ using type_must_then_opt < t_css_coin2, t_css_polar, sz_space_char, t_css_coin3, 0, 1 > :: type_must_then_opt; };

template < > struct type_master < t_css_coin1 > : type_either_or < t_css_coin1, t_css_rect, t_css_coin2 >
{ using type_either_or < t_css_coin1, t_css_rect, t_css_coin2 > :: type_either_or; };

template < > struct type_master < t_css_colour_interpolation > : string_then_type < t_css_colour_interpolation, t_css_coin1, sz_in >
{ using string_then_type < t_css_colour_interpolation, t_css_coin1, sz_in > :: string_then_type; };

template < > struct type_master < t_css_colour_percent > : type_one_or_both < t_css_colour_percent, t_css_colour, sz_space_char, t_percent, BS_FN >
{ using type_one_or_both < t_css_colour_percent, t_css_colour, sz_space_char, t_percent, BS_FN > :: type_one_or_both; };

template < > struct type_master < t_css_colour_percent_n > : type_or_string < t_css_colour_percent_n, t_css_colour_percent, sz_none >
{ using type_or_string < t_css_colour_percent_n, t_css_colour_percent, sz_none > :: type_or_string; };

template < > struct type_master < t_css_cols > : type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col >
{ using type_some_of < t_css_cols, sz_space_char, 1, 4, t_css_col > :: type_some_of; };

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

template < > struct type_master < t_css_cue > : either_type_or_string < t_css_cue, t_urifn, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_cue, t_urifn, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_cues > : type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 >
{ using type_range < t_css_cues, sz_space_char, t_css_cue, 1, 2 > :: type_range; };

template < > struct type_master < t_urifn_xy > : type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 >
{ using type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 > :: type_must_then_opt; };

template < > struct type_master < t_css_cursor_url > : type_many_then_must < t_css_cursor_url, t_urifn_xy, sz_comma, t_css_cursor_e >
{ using type_many_then_must < t_css_cursor_url, t_urifn_xy, sz_comma, t_css_cursor_e > :: type_many_then_must; };

template < > struct type_master < t_css_cursor > : type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit >
{ using type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_elevation > : type_either_or < t_css_elevation, t_angle, t_css_elevation_e >
{ using type_either_or < t_css_elevation, t_angle, t_css_elevation_e > :: type_either_or; };

template < > struct type_master < t_css_font_size > : type_one_of_five < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_all, t_css_inherit >
{ using type_one_of_five < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_all, t_css_inherit > :: type_one_of_five; };

template < > struct type_master < t_css_font_style > : type_either_or < t_css_font_style, t_css_all, t_css_font_style_e >
{ using type_either_or < t_css_font_style, t_css_all, t_css_font_style_e > :: type_either_or; };

template < > struct type_master < t_font_synthesis > : either_string_or_both < t_font_synthesis, sz_style, sz_weight, sz_space_char >
{ using either_string_or_both < t_font_synthesis, sz_style, sz_weight, sz_space_char > :: either_string_or_both; };

template < > struct type_master < t_font_synthesis_n > : type_or_string < t_font_synthesis_n, t_font_synthesis, sz_none >
{ using type_or_string < t_font_synthesis_n, t_font_synthesis, sz_none > :: type_or_string; };

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

template < > struct type_master < t_css_length_a > : type_or_string < t_css_length_a, t_css_length, sz_auto >
{ using type_or_string < t_css_length_a, t_css_length, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_length_a2 > : type_one_or_both < t_css_length_a2, t_css_length_a, sz_space_char, t_css_length_a >
{ using type_one_or_both < t_css_length_a2, t_css_length_a, sz_space_char, t_css_length_a > :: type_one_or_both; };

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

template < > struct type_master < t_css_margins > : type_either_or < t_css_margins, t_measures_a, t_css_inherit >
{ using type_either_or < t_css_margins, t_measures_a, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_marks > : type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char >
{ using type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space_char > :: type_one_two; };

template < > struct type_master < t_css_marx > : either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none > :: either_type_or_string; };

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

template < > struct type_master < t_css_pause > : type_number_unit_3 < t_css_pause, t_real, sz_ms, sz_s, sz_per_cent >
{ using type_number_unit_3 < t_css_pause, t_real, sz_ms, sz_s, sz_per_cent > :: type_number_unit_3; };

template < > struct type_master < t_css_pause_i > : type_either_or < t_css_pause_i, t_css_pause, t_css_inherit >
{ using type_either_or < t_css_pause_i, t_css_pause, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_pauses > : type_range < t_css_pauses, sz_space_char, t_css_pause_i, 1, 2 >
{ using type_range < t_css_pauses, sz_space_char, t_css_pause_i, 1, 2 > :: type_range; };

template < > struct type_master < t_css_pitch > : type_either_or < t_css_pitch, t_real, t_css_pitch_e >
{ using type_either_or < t_css_pitch, t_real, t_css_pitch_e > :: type_either_or; };

template < > struct type_master < t_css_play_during > : either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none >
{ using either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none > :: either_type_or_either_string; };

template < > struct type_master < t_css_rect_fn > : type_function_all < t_css_rect_fn, sz_rect, t_measure, t_measure, t_measure, t_measure >
{ using type_function_all < t_css_rect_fn, sz_rect, t_measure, t_measure, t_measure, t_measure > :: type_function_all; };

template < > struct type_master < t_css_rect_ai > : either_type_or_string < t_css_rect_ai, t_css_rect_fn, t_css_inherit, sz_auto >
{ using either_type_or_string < t_css_rect_ai, t_css_rect_fn, t_css_inherit, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_size > : type_either_or < t_css_size, t_css_orientation, t_css_length_twice >
{ using type_either_or < t_css_size, t_css_orientation, t_css_length_twice > :: type_either_or; };

template < > struct type_master < t_css_spacing > : either_type_or_string < t_css_spacing, t_css_length, t_css_inherit, sz_normal >
{ using either_type_or_string < t_css_spacing, t_css_length, t_css_inherit, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_css_speech_rate > : type_either_or < t_css_speech_rate, t_real, t_css_speech_rate_e >
{ using type_either_or < t_css_speech_rate, t_real, t_css_speech_rate_e > :: type_either_or; };

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

template < > struct type_master < t_css_src > : tidy_string < t_css_src >
{   using tidy_string < t_css_src > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_url; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_src > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_css_src > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
            tidy_string < t_css_src > :: status (s_invalid); }
        else if (good ())
        {   if (v.svg_version () > sv_none)
            {   type_master < t_css_local_url > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_svg_src > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            tidy_string < t_css_src > :: status (s_invalid); } } };

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
            nits.pick (nit_css_colour, es_error, ec_css, "CSS colour error");
            if (context.tell (es_debug))
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
