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
#include "simple/type_misc.h"
#include "compound/type_compound.h"

template < > struct type_master < t_angle_n > : type_or_string < t_angle_n, t_angle, sz_none >
{ using  type_or_string < t_angle_n, t_angle, sz_none > :: type_or_string; };

template < > struct type_master < t_angle_p > : public type_either_or < t_angle_p, t_angle, t_percent >
{   using type_either_or < t_angle_p, t_angle, t_percent > :: type_either_or; };

template < > struct type_master < t_hue_n > : either_type_or_string < t_hue_n, t_angle, t_hue, sz_none >
{ using  either_type_or_string < t_hue_n, t_angle, t_hue, sz_none > :: either_type_or_string; };

template < > struct type_master < t_real_percent > : public type_either_or < t_real_percent, t_percent, t_real >
{   using type_either_or < t_real_percent, t_percent, t_real > :: type_either_or; };

template < > struct type_master < t_real_percent_n > : public either_type_or_string < t_real_percent_n, t_percent, t_real, sz_none >
{   using either_type_or_string < t_real_percent_n, t_percent, t_real, sz_none > :: either_type_or_string; };

template < > struct type_master < t_real_perflex > : public type_either_or < t_real_perflex, t_percent_flexible, t_real >
{   using type_either_or < t_real_perflex, t_percent_flexible, t_real > :: type_either_or; };

template < > struct type_master < t_colourfn > : type_function_1_4_5 < t_colourfn, sz_color, t_css_rgb_xyz, t_percent_flexible, t_percent_flexible, t_percent_flexible, t_zero_to_one >
{ using type_function_1_4_5 < t_colourfn, sz_color, t_css_rgb_xyz, t_percent_flexible, t_percent_flexible, t_percent_flexible, t_zero_to_one > :: type_function_1_4_5; };

template < > struct type_master < t_colour_schemes > : type_at_least_one < t_colour_schemes, sz_space_char, t_colour_scheme >
{ using type_at_least_one < t_colour_schemes, sz_space_char, t_colour_scheme > :: type_at_least_one; };

template < > struct type_master < t_colour_schemes_o > : type_and_maybe_string < t_colour_schemes_o, t_colour_scheme, sz_space_char, sz_only >
{ using type_and_maybe_string < t_colour_schemes_o, t_colour_scheme, sz_space_char, sz_only > :: type_and_maybe_string; };

template < > struct type_master < t_colour_schemes_n > : type_or_string < t_colour_schemes_n, t_colour_schemes_o, sz_normal >
{ using type_or_string < t_colour_schemes_n, t_colour_schemes_o, sz_normal > :: type_or_string; };

template < > struct type_master < t_scale_down > : type_string < t_scale_down, sz_scale_down >
{ using type_string < t_scale_down, sz_scale_down > :: type_string; };

template < > struct type_master < t_contain_cover_sd > : type_either_or_both < t_contain_cover_sd, t_contain_cover, sz_space_char, t_scale_down >
{ using type_either_or_both < t_contain_cover_sd, t_contain_cover, sz_space_char, t_scale_down > :: type_either_or_both; };

template < > struct type_master < t_cookies > : type_at_least_one < t_cookies, sz_semicolon, t_cookie >
{ using type_at_least_one < t_cookies, sz_semicolon, t_cookie > :: type_at_least_one; };

template < > struct type_master < t_css_all_2 > : public type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset >
{   using type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset > :: type_sz; };

template < > struct type_master < t_css_caret > : type_some_of < t_css_caret, sz_space_char, 0, 2, t_css_colour_a, t_css_caret_shape >
{ using type_some_of < t_css_caret, sz_space_char, 0, 2, t_css_colour_a, t_css_caret_shape > :: type_some_of; };

template < > struct type_master < t_current_colour_sz > : type_string < t_current_colour_sz, sz_currentcolour >
{ using type_string < t_current_colour_sz, sz_currentcolour > :: type_string; };

template < > struct type_master < t_decibel > : type_number_unit < t_decibel, t_real, sz_db, true >
{ using type_number_unit < t_decibel, t_real, sz_db, true > :: type_number_unit; };

template < > struct type_master < t_duration_a > : type_or_string < t_duration_a, t_duration, sz_auto >
{ using type_or_string < t_duration_a, t_duration, sz_auto > :: type_or_string; };

template < > struct type_master < t_fontnias > : type_one_or_both < t_fontnias, t_fontnia, sz_comma, t_fontnia >
{ using type_one_or_both < t_fontnias, t_fontnia, sz_comma, t_fontnia > :: type_one_or_both; };

template < > struct type_master < t_fill > : type_string < t_fill, sz_fill >
{ using type_string < t_fill, sz_fill > :: type_string; };

template < > struct type_master < t_fr > : type_number_unit < t_fr, t_real, sz_fr, true >
{ using type_number_unit < t_fr, t_real, sz_fr, true > :: type_number_unit; };

template < > struct type_master < t_frequency_abs > : type_then_string < t_frequency_abs, t_frequency, sz_absolute >
{ using type_then_string < t_frequency_abs, t_frequency, sz_absolute > :: type_then_string; };

template < > struct type_master < t_from_angle > : string_then_type < t_from_angle, t_angle, sz_from >
{ using string_then_type < t_from_angle, t_angle, sz_from > :: string_then_type; };

template < > struct type_master < t_frp > : type_either_or < t_frp, t_fr, t_css_length >
{ using type_either_or < t_frp, t_fr, t_css_length > :: type_either_or; };

template < > struct type_master < t_hslafn > : type_function_all < t_hslafn, sz_hsla, t_hue, t_percent, t_percent, t_zero_to_one >
{ using type_function_all < t_hslafn, sz_hsla, t_hue, t_percent, t_percent, t_zero_to_one > :: type_function_all; };

template < > struct type_master < t_hslfn > : type_function_all < t_hslfn, sz_hsl, t_hue, t_percent, t_percent >
{ using type_function_all < t_hslfn, sz_hsl, t_hue, t_percent, t_percent > :: type_function_all; };

template < > struct type_master < t_hslfn4 > : type_function_3_4 < t_hslfn4, sz_hsl, t_hue_n, t_percent_n, t_percent_n, t_css_alpha >
{ using type_function_3_4 < t_hslfn4, sz_hsl, t_hue_n, t_percent_n, t_percent_n, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_hwbfn > : type_function_3_4 < t_hwbfn, sz_hwb, t_hue_n, t_percent_n, t_percent_n, t_css_alpha >
{ using type_function_3_4 < t_hwbfn, sz_hwb, t_hue_n, t_percent_n, t_percent_n, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_integer_or_percent > : type_either_or < t_integer_or_percent, t_percent, t_0_to_255 >
{ using type_either_or < t_integer_or_percent, t_percent, t_0_to_255 > :: type_either_or; };

template < > struct type_master < t_labfn > : type_function_3_4 < t_labfn, sz_lab, t_real_percent_n, t_percent_flexible, t_percent_flexible, t_css_alpha >
{ using type_function_3_4 < t_labfn, sz_lab, t_real_percent_n, t_percent_flexible, t_percent_flexible, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_lchfn > : type_function_3_4 < t_lchfn, sz_lch, t_real_percent_n, t_percent_flexible, t_hue_n, t_css_alpha >
{ using type_function_3_4 < t_lchfn, sz_lch, t_real_percent_n, t_percent_flexible, t_hue_n, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_linear_colour_stop > : type_ab_ba < t_linear_colour_stop, sz_space_char, t_css_col, t_css_length >
{ using type_ab_ba < t_linear_colour_stop, sz_space_char, t_css_col, t_css_length > :: type_ab_ba; };

template < > struct type_master < t_linear_colour_more > : type_either_or < t_linear_colour_more, t_linear_colour_stop, t_css_length >
{ using type_either_or < t_linear_colour_more, t_linear_colour_stop, t_css_length > :: type_either_or; };

template < > struct type_master < t_linear_colour_stops > : type_some_of < t_linear_colour_stops, sz_comma, 1, 0, t_linear_colour_stop, t_linear_colour_more, t_linear_colour_stop >
{ using type_some_of < t_linear_colour_stops, sz_comma, 1, 0, t_linear_colour_stop, t_linear_colour_more, t_linear_colour_stop > :: type_some_of; };

template < > struct type_master < t_angular_colour_stop > : type_ab_ba < t_angular_colour_stop, sz_space_char, t_css_col, t_angle_p >
{ using type_ab_ba < t_angular_colour_stop, sz_space_char, t_css_col, t_angle_p > :: type_ab_ba; };

template < > struct type_master < t_angular_colour_more > : type_either_or < t_angular_colour_more, t_angular_colour_stop, t_angle_p >
{ using type_either_or < t_angular_colour_more, t_angular_colour_stop, t_angle_p > :: type_either_or; };

template < > struct type_master < t_lrtb > : type_either_or_both < t_lrtb, t_lralign, sz_space_char, t_tbalign >
{ using type_either_or_both < t_lrtb, t_lralign, sz_space_char, t_tbalign > :: type_either_or_both; };

template < > struct type_master < t_to_lrtb > : string_then_type < t_to_lrtb, t_lrtb, sz_to >
{ using string_then_type < t_to_lrtb, t_lrtb, sz_to > :: string_then_type; };

template < > struct type_master < t_oklabfn > : type_function_3_4 < t_oklabfn, sz_oklab, t_real_percent_n, t_percent_flexible, t_percent_flexible, t_css_alpha >
{ using type_function_3_4 < t_oklabfn, sz_oklab, t_real_percent_n, t_percent_flexible, t_percent_flexible, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_oklchfn > : type_function_3_4 < t_oklchfn, sz_oklch, t_real_percent_n, t_percent_flexible, t_hue_n, t_css_alpha >
{ using type_function_3_4 < t_oklchfn, sz_oklch, t_real_percent_n, t_percent_flexible, t_hue_n, t_css_alpha > :: type_function_3_4; };

template < > struct type_master < t_percent_n > : type_or_string < t_percent_n, t_percent, sz_none >
{ using type_or_string < t_percent_n, t_percent, sz_none > :: type_or_string; };

template < > struct type_master < t_percents_flexible > : type_one_or_both < t_percents_flexible, t_percent_flexible, sz_space_char, t_percent_flexible >
{ using type_one_or_both < t_percents_flexible, t_percent_flexible, sz_space_char, t_percent_flexible > :: type_one_or_both; };

template < > struct type_master < t_percents_n > : type_or_string < t_percents_n, t_percents_flexible, sz_none >
{ using type_or_string < t_percents_n, t_percents_flexible, sz_none > :: type_or_string; };

template < > struct type_master < t_percents_nf > : type_or_either_string < t_percents_nf, t_percents_flexible, sz_from_font, sz_normal >
{ using type_or_either_string < t_percents_nf, t_percents_flexible, sz_from_font, sz_normal > :: type_or_either_string; };

template < > struct type_master < t_at_pos > : string_then_type < t_at_pos, t_css_background_0, sz_at >
{ using string_then_type < t_at_pos, t_css_background_0, sz_at > :: string_then_type; };

template < > struct type_master < t_position_tb_len > : type_opt_then_must < t_position_tb_len, t_tbalign, sz_space_char, t_css_length >
{ using type_opt_then_must < t_position_tb_len, t_tbalign, sz_space_char, t_css_length > :: type_opt_then_must; };

template < > struct type_master < t_position_lr_len > : type_opt_then_must < t_position_lr_len, t_lralign, sz_space_char, t_css_length >
{ using type_opt_then_must < t_position_lr_len, t_lralign, sz_space_char, t_css_length > :: type_opt_then_must; };

template < > struct type_master < t_position_lrtb_len > : type_ab_ba < t_position_lrtb_len, sz_space_char, t_position_lr_len, t_position_tb_len >
{ using type_ab_ba < t_position_lrtb_len, sz_space_char, t_position_lr_len, t_position_tb_len > :: type_ab_ba; };

template < > struct type_master < t_position_lcr_len > : public type_either_or < t_position_lcr_len, t_lcralign, t_css_length >
{   using type_either_or < t_position_lcr_len, t_lcralign, t_css_length > :: type_either_or; };

template < > struct type_master < t_position_tcb_len > : public type_either_or < t_position_tcb_len, t_tcbalign, t_css_length >
{   using type_either_or < t_position_tcb_len, t_tcbalign, t_css_length > :: type_either_or; };

template < > struct type_master < t_position_lcrtcb > : type_either_or_both < t_position_lcrtcb, t_lcralign, sz_space_char, t_tcbalign >
{ using type_either_or_both < t_position_lcrtcb, t_lcralign, sz_space_char, t_tcbalign > :: type_either_or_both; };

template < > struct type_master < t_position > : type_one_of < t_position, false, t_position_lcrtcb, t_position_lcrtcb_len, t_position_lrtb_len >
{ using type_one_of < t_position, false, t_position_lcrtcb, t_position_lcrtcb_len, t_position_lrtb_len > :: type_one_of; };

template < > struct type_master < t_positions > : type_some_of < t_positions, sz_comma, 1,999, t_position >
{ using type_some_of < t_positions, sz_comma, 1, 999, t_position > :: type_some_of; };

template < > struct type_master < t_radial_size > : type_one_or_both < t_radial_size, t_css_radial_size, sz_space_char, t_css_length >
{ using type_one_or_both < t_radial_size, t_css_radial_size, sz_space_char, t_css_length > :: type_one_or_both; };
 
template < > struct type_master < t_radial_ending > : type_one_or_both < t_radial_ending, t_circle_ellipse, sz_space_char, t_radial_size >
{ using type_one_or_both < t_radial_ending, t_circle_ellipse, sz_space_char, t_radial_size > :: type_one_or_both; };
 
template < > struct type_master < t_radial_1 > : type_none_one_two < t_radial_1, sz_space_char, t_radial_ending, t_at_pos >
{ using type_none_one_two < t_radial_1, sz_space_char, t_radial_ending, t_at_pos > :: type_none_one_two; };

template < > struct type_master < t_rgbfn > : type_function_3_4 < t_rgbfn, sz_rgb, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_zero_to_one >
{ using type_function_3_4 < t_rgbfn, sz_rgb, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_zero_to_one > :: type_function_3_4; };

template < > struct type_master < t_rgbafn > : type_function_all < t_rgbafn, sz_rgba, t_integer_or_percent, t_integer_or_percent, t_integer_or_percent, t_zero_to_one >
{ using type_function_all < t_rgbafn, sz_rgba, t_integer_or_percent, t_integer_or_percent, t_integer_or_percent, t_zero_to_one > :: type_function_all; };

template < > struct type_master < t_snap > : type_string < t_snap, sz_snap >
{ using type_string < t_snap, sz_snap > :: type_string; };

template < > struct type_master < t_startends > : either_string_or_both < t_startends, sz_start, sz_end, sz_space_char >
{ using either_string_or_both < t_startends, sz_start, sz_end, sz_space_char > :: either_string_or_both; };

template < > struct type_master < t_stripe > : type_either_or_both < t_stripe, t_css_col, sz_space_char, t_frp >
{ using type_either_or_both < t_stripe, t_css_col, sz_space_char, t_frp > :: type_either_or_both; };

template < > struct type_master < t_svg_src > : public either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit >
{   using either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit > :: either_type_or_either_string; };

template < > struct type_master < t_text_2 > : type_one_or_both < t_text_2, t_text, sz_space_char, t_text >
{ using type_one_or_both < t_text_2, t_text, sz_space_char, t_text > :: type_one_or_both; };

template < > struct type_master < t_texts > : type_at_least_one < t_texts, sz_space_char, t_text >
{ using type_at_least_one < t_texts, sz_space_char, t_text > :: type_at_least_one; };

template < > struct type_master < t_texts_n > : type_or_string < t_texts_n, t_texts, sz_none >
{ using type_or_string < t_texts_n, t_texts, sz_none > :: type_or_string; };

template < > struct type_master < t_transparentsz > : type_string < t_transparentsz, sz_transparent >
{ using type_string < t_transparentsz, sz_transparent > :: type_string; };

template < > struct type_master < t_type_fn > : type_function < t_type_fn, sz_type, t_mime >
{ using type_function < t_type_fn, sz_type, t_mime > :: type_function; };

template < > struct type_master < t_under_ff > : public type_either_string < t_under_ff, sz_under, sz_from_font >
{   using type_either_string < t_under_ff, sz_under, sz_from_font > :: type_either_string; };

template < > struct type_master < t_unit_abs_per > : type_or_string < t_unit_abs_per, t_unit_abs_len, sz_per_cent >
{ using type_or_string < t_unit_abs_per, t_unit_abs_len, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_unit_angle_per > : type_or_string < t_unit_angle_per, t_unit_angle, sz_per_cent >
{ using type_or_string < t_unit_angle_per, t_unit_angle, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_unit_freq_per > : type_or_string < t_unit_freq_per, t_unit_freq, sz_per_cent >
{ using type_or_string < t_unit_freq_per, t_unit_freq, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_unit_rel_per > : type_or_string < t_unit_rel_per, t_unit_rel_len, sz_per_cent >
{ using type_or_string < t_unit_rel_per, t_unit_rel_len, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_unit_res_per > : type_or_string < t_unit_res_per, t_unit_res, sz_per_cent >
{ using type_or_string < t_unit_res_per, t_unit_res, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_unit_time_per > : type_or_string < t_unit_time_per, t_unit_time, sz_per_cent >
{ using type_or_string < t_unit_time_per, t_unit_time, sz_per_cent > :: type_or_string; };

template < > struct type_master < t_urifn_xy > : type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 >
{ using type_must_then_opt < t_urifn_xy, t_urifn, sz_space_char, t_integer, 0, 2 > :: type_must_then_opt; };

template < > struct type_master < t_xlinktype > : type_string < t_xlinktype, sz_simple >
{ using type_string < t_xlinktype, sz_simple > :: type_string; };

template < bool REQ > struct tnu_properties
{   static bool required (nitpick& , const ::std::string& )
    { return false; } }; 

template < > struct tnu_properties < true >
{   static bool required (nitpick& nits, const ::std::string& ss)
    {   nits.pick (nit_bad_units, es_error, ec_type, quote (ss), ": units required");
        return true; } }; 
