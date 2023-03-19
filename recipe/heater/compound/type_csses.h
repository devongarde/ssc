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

template < > struct type_master < t_css_attr > : type_function_n < t_css_attr, t_text, sz_attr, 1 >
{ using type_function_n < t_css_attr, t_text, sz_attr, 1 > :: type_function_n; };

template < > struct type_master < t_css_azimuth_eb > : type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e >
{ using type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e > :: type_either_or; };

template < > struct type_master < t_css_azimuth_es > : type_at_least_one < t_css_azimuth_es, sz_space, t_css_azimuth_eb >
{ using type_at_least_one < t_css_azimuth_es, sz_space, t_css_azimuth_eb > :: type_at_least_one; };

template < > struct type_master < t_css_azimuth > : type_one_of < t_css_azimuth, false, t_angle, t_css_azimuth_lri, t_css_azimuth_es >
{ using type_one_of < t_css_azimuth, false, t_angle, t_css_azimuth_lri, t_css_azimuth_es > :: type_one_of; };

template < > struct type_master < t_css_background > : type_range < t_css_background, sz_space, t_css_backval, 1, 5 >
{ using type_range < t_css_background, sz_space, t_css_backval, 1, 5 > :: type_range; };

template < > struct type_master < t_css_background_position > : type_one_two < t_css_background_position, t_refy, t_refx, sz_space >
{ using type_one_two < t_css_background_position, t_refy, t_refx, sz_space > :: type_one_two; };

template < > struct type_master < t_css_border_measure > : type_one_of < t_css_border_measure, false, t_css_inherit, t_css_border_width, t_css_length >
{ using type_one_of < t_css_border_measure, false, t_css_inherit, t_css_border_width, t_css_length > :: type_one_of; };

template < > struct type_master < t_css_borders_measure > : type_range < t_css_borders_measure, sz_space, t_css_border_measure, 1, 4 >
{ using type_range < t_css_borders_measure, sz_space, t_css_border_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_css_borders_measure_i > : type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit >
{ using type_either_or < t_css_borders_measure_i, t_css_borders_measure, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_spacing_2 > : type_range < t_css_border_spacing_2, sz_space, t_css_length, 1, 2 >
{ using type_range < t_css_border_spacing_2, sz_space, t_css_length, 1, 2 > :: type_range; };

template < > struct type_master < t_css_border_spacing > : type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit >
{ using type_either_or < t_css_border_spacing, t_css_border_spacing_2, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_styles > : type_range < t_css_border_styles, sz_space, t_css_border_style, 1, 4 >
{ using type_range < t_css_border_styles, sz_space, t_css_border_style, 1, 4 > :: type_range; };

template < > struct type_master < t_css_border_style_i > : type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit >
{ using type_either_or < t_css_border_style_i, t_css_border_style, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_border_width_i > : type_either_or < t_css_border_width_i, t_css_border_width, t_css_inherit >
{ using type_either_or < t_css_border_width_i, t_css_border_width, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_counter > : type_function_2_opt < t_css_counter, sz_counter, t_text, t_css_list_style_type >
{ using type_function_2_opt < t_css_counter, sz_counter, t_text, t_css_list_style_type > :: type_function_2_opt; };

// not clear from spec where counter identifiers are defined in CSS
template < > struct type_master < t_css_counter_ii > : type_either_or < t_css_counter_ii, t_text, t_integer >
{ using type_either_or < t_css_counter_ii, t_text, t_integer > :: type_either_or; };

template < > struct type_master < t_css_counter_iin > : type_at_least_one < t_css_counter_iin, sz_space, t_css_counter_ii >
{ using type_at_least_one < t_css_counter_iin, sz_space, t_css_counter_ii > :: type_at_least_one; };

template < > struct type_master < t_css_counter_set > : either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_counters > : type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type >
{ using type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type > :: type_function_3_opt; };

template < > struct type_master < t_css_content_fn > : type_one_of < t_css_content_fn, false, t_css_attr, t_css_counter, t_css_counters >
{ using type_one_of < t_css_content_fn, false, t_css_attr, t_css_counter, t_css_counters > :: type_one_of; };

template < > struct type_master < t_css_content_base > : type_one_of < t_css_content_base, false, t_text, t_css_content_fn, t_urifn >
{ using type_one_of < t_css_content_base, false, t_text, t_css_content_fn, t_urifn > :: type_one_of; };

template < > struct type_master < t_css_content_twice > : type_at_least_none < t_css_content_twice, sz_space, t_css_content_base >
{ using type_at_least_none < t_css_content_twice, sz_space, t_css_content_base > :: type_at_least_none; };

template < > struct type_master < t_css_content > : type_either_neither < t_css_content, t_css_content_twice, t_css_inherit >
{ using type_either_neither < t_css_content, t_css_content_twice, t_css_inherit > :: type_either_neither; };

template < > struct type_master < t_css_cue > : either_type_or_string < t_css_cue, t_urifn, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_cue, t_urifn, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_cues > : type_range < t_css_cues, sz_space, t_css_cue, 1, 2 >
{ using type_range < t_css_cues, sz_space, t_css_cue, 1, 2 > :: type_range; };

template < > struct type_master < t_css_cursor_url > : type_many_then_must < t_css_cursor_url, t_urifn, sz_comma, t_css_cursor_e >
{ using type_many_then_must < t_css_cursor_url, t_urifn, sz_comma, t_css_cursor_e > :: type_many_then_must; };

template < > struct type_master < t_css_cursor > : type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit >
{ using type_either_or < t_css_cursor, t_css_cursor_url, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_elevation > : type_either_or < t_css_elevation, t_angle, t_css_elevation_e >
{ using type_either_or < t_css_elevation, t_angle, t_css_elevation_e > :: type_either_or; };

template < > struct type_master < t_css_font_size > : type_one_of_five < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_all, t_css_inherit >
{ using type_one_of_five < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure, t_css_all, t_css_inherit > :: type_one_of_five; };

template < > struct type_master < t_css_font_style > : type_either_or < t_css_font_style, t_css_all, t_css_font_style_e >
{ using type_either_or < t_css_font_style, t_css_all, t_css_font_style_e > :: type_either_or; };

template < > struct type_master < t_css_image > : type_or_string < t_css_image, t_css_url, sz_none >
{ using type_or_string < t_css_image, t_css_url, sz_none > :: type_or_string; };

template < > struct type_master < t_css_length_a > : type_or_string < t_css_length_a, t_css_length, sz_auto >
{ using type_or_string < t_css_length_a, t_css_length, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_length_ai > : either_type_or_string < t_css_length_ai, t_css_inherit, t_css_length, sz_auto >
{ using either_type_or_string < t_css_length_ai, t_css_inherit, t_css_length, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_css_length_twice > : type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space >
{ using type_one_two < t_css_length_twice, t_css_length, t_css_length, sz_space > :: type_one_two; };

template < > struct type_master < t_css_line_height > : either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal >
{ using either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_css_ls_val > : type_one_of < t_css_ls_val, false, t_css_list_style_type, t_css_list_style_position, t_css_url >
{ using type_one_of < t_css_ls_val, false, t_css_list_style_type, t_css_list_style_position, t_css_url > :: type_one_of; };

template < > struct type_master < t_css_list_style > : type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 >
{ using type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_margins > : type_either_or < t_css_margins, t_measures_a, t_css_inherit >
{ using type_either_or < t_css_margins, t_measures_a, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_marks > : type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space >
{ using type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space > :: type_one_two; };

template < > struct type_master < t_css_marx > : either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_nth_oe > : public type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n >
{ using type_or_any_string < t_css_nth_oe, t_css_nth, sz_even, sz_odd, sz_n > :: type_or_any_string; };

template < > struct type_master < t_css_outline > : type_one_of < t_css_outline, false, t_css_border_measure, t_css_border_style, t_colour_ii >
{ using type_one_of < t_css_outline, false, t_css_border_measure, t_css_border_style, t_colour_ii > :: type_one_of; };

template < > struct type_master < t_css_outlines > : type_range < t_css_outlines, sz_space, t_css_outline, 1, 3 >
{ using type_range < t_css_outlines, sz_space, t_css_outline, 1, 3 > :: type_range; };

template < > struct type_master < t_css_outline_i > : type_either_or < t_css_outline_i, t_css_inherit, t_css_outlines >
{ using type_either_or < t_css_outline_i, t_css_inherit, t_css_outlines > :: type_either_or; };

template < > struct type_master < t_css_pause > : type_number_unit_3 < t_css_pause, t_real, sz_ms, sz_s, sz_per_cent >
{ using type_number_unit_3 < t_css_pause, t_real, sz_ms, sz_s, sz_per_cent > :: type_number_unit_3; };

template < > struct type_master < t_css_pause_i > : type_either_or < t_css_pause_i, t_css_pause, t_css_inherit >
{ using type_either_or < t_css_pause_i, t_css_pause, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_pauses > : type_range < t_css_pauses, sz_space, t_css_pause_i, 1, 2 >
{ using type_range < t_css_pauses, sz_space, t_css_pause_i, 1, 2 > :: type_range; };

template < > struct type_master < t_css_pitch > : type_either_or < t_css_pitch, t_real, t_css_pitch_e >
{ using type_either_or < t_css_pitch, t_real, t_css_pitch_e > :: type_either_or; };

template < > struct type_master < t_css_play_during > : either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none >
{ using either_type_or_either_string < t_css_play_during, t_css_play_during_mr, t_css_inherit, sz_auto, sz_none > :: either_type_or_either_string; };

template < > struct type_master < t_css_rect_fn > : type_function_n < t_css_rect_fn, t_measure, sz_rect, 4 >
{ using type_function_n < t_css_rect_fn, t_measure, sz_rect, 4 > :: type_function_n; };

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

template < > struct type_master < t_css_wsc_val > : type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_colour >
{ using type_one_of < t_css_wsc_val, false, t_css_border_measure, t_css_border_style, t_colour > :: type_one_of; };

template < > struct type_master < t_css_border_wsc > : type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 >
{ using type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_border_wsc_i > : type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit >
{ using type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_backval > : type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position >
{ using type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position > :: type_one_of_five; };

template < > struct type_master < t_css_play_during_mr > : type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space, sz_mix, sz_repeat >
{ using type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space, sz_mix, sz_repeat > :: type_and_maybe_strings; };


template < > struct type_master < t_css_src > : tidy_string < t_css_src >
{   using tidy_string < t_css_src > :: tidy_string;
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
