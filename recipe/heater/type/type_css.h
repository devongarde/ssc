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
#include "type/type_numeric.h"
#include "type/type_master.h"

// t_css_font

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e) noexcept;

template < > struct type_master < t_css > : public tidy_string < t_css >
{   using tidy_string < t_css > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css > :: set_value (nits, v, s);
        if (tidy_string < t_css > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic style"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e) noexcept
    {   if (! tidy_string < t_css > :: good ()) return true;
        return ! process_css (nits, v, tidy_string < t_css > :: get_string (), e); } };

template < > struct type_master < t_css_all > : public tidy_string < t_css_all >
{   using tidy_string < t_css_all > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_all > :: set_value (nits, v, s);
        if (tidy_string < t_css_all > :: good ())
            if (! compare_no_case (tidy_string < t_css_all > :: get_string (), "all"))
            {   if (v.css_version () == css_2_0)
                    nits.pick (nit_unrecognised_value, es_comment, ec_type, quote (s), ": is not 'all'"); }
            else if (v.css_version () != css_2_0)
                nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'all' requires CSS 2.0 (only)");
            else return;
        tidy_string < t_css_all > :: status (s_invalid); } };

template < > struct type_master < t_css_inherit > : public tidy_string < t_css_inherit >
{   using tidy_string < t_css_inherit > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_inherit > :: set_value (nits, v, s);
        if (tidy_string < t_css_inherit > :: good ())
            if (! compare_no_case (tidy_string < t_css_inherit > :: get_string (), "inherit"))
            {   if (v.css_version () >= css_2_0)
                    nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), ": is not 'inherit'"); }
            else if (v.css_version () < css_2_0)
                nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'inherit' requires CSS 2.0 or later");
            else return;
        tidy_string < t_css_inherit > :: status (s_invalid); } };

template < > struct type_master < t_css_font > : tidy_string < t_css_font >
{   using tidy_string < t_css_font > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& sss)
    {   tidy_string < t_css_font > :: set_value (nits, v, sss);
        if (tidy_string < t_css_font> :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font specification cannot be empty");
        else if (tidy_string < t_css_font> :: good ())
        {   nitpick gnats;
            ::std::string gs (tidy_string < t_css_font > :: get_string ());
            if (test_value < t_font_enum > (gnats, v, gs))
            {   nits.merge (gnats);
                return; }
            vstr_t ss (split_by_space (gs));
            PRESUME (! ss.empty (), __FILE__, __LINE__);
            bool res = true;
            typedef enum { fs_style, fs_variant, fs_weight, fs_size, fs_family, fs_done } font_state;
            font_state state = fs_style;
            for (auto s : ss)
            {   nitpick nuts, knits;
                ::std::string::size_type pos = ::std::string::npos;
                if (test_value < t_font_enum > (nuts, v, s))
                {   nits.merge (nuts);
                    if (ss.size () > 1)
                    {   nits.pick (nit_font_enum, es_error, ec_type, quote (s), " cannot be combined with other values");
                        res = false; break; } }
                else switch (state)
                {   case fs_style :
                        if (test_value < t_css_font_style > (knits, v, s))
                        {   state = fs_variant; break; }
                        FALLTHROUGH;
                    case fs_variant :
                        if (test_value < t_svg_fontvariant > (knits, v, s))
                        {   state = fs_weight; break; }
                        FALLTHROUGH;
                    case fs_weight :
                        if (test_value < t_css_font_weight > (knits, v, s))
                        {   state = fs_size; break; }
                        FALLTHROUGH;
                    case fs_size :
                        pos = s.find ('/');
                        if (pos == ::std::string::npos)
                        {   if (test_value < t_fontsize > (knits, v, s))
                            {   state = fs_family; break; }
                            if (v.has_css () && test_value < t_css_font_size > (knits, v, s))
                            {   state = fs_family; break; } }
                        else if (test_value < t_fontsize > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        else if (v.has_css () && 
                                 test_value < t_css_font_size > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        FALLTHROUGH;
                    case fs_family :
                        if (test_value < t_font_family > (knits, v, s))
                        {   if (! v.has_css ()) state = fs_done;
                            break; }
                        if (v.has_css () && test_value < t_css_generic_family > (knits, v, s))
                            break;
                        FALLTHROUGH;
                    default :
                        nits.pick (nit_font_enum, es_error, ec_type, quote (s), " is not a known CSS FONT property");
                        res = false; break; }
                if (! res) break; }
            if (res) return; }
        tidy_string < t_css_font > :: status (s_invalid); } };

template < > struct type_master < t_css_attr > : type_function_n < t_css_attr, t_text, sz_attr, 1 >
{ using type_function_n < t_css_attr, t_text, sz_attr, 1 > :: type_function_n; };

template < > struct type_master < t_css_azimuth_eb > : type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e >
{ using type_either_or < t_css_azimuth_eb, t_css_azimuth_be, t_css_azimuth_e > :: type_either_or; };

template < > struct type_master < t_css_azimuth_es > : type_at_least_one < t_css_azimuth_es, sz_space, t_css_azimuth_eb >
{ using type_at_least_one < t_css_azimuth_es, sz_space, t_css_azimuth_eb > :: type_at_least_one; };

template < > struct type_master < t_css_azimuth > : type_one_of_three < t_css_azimuth, t_angle, t_css_azimuth_lri, t_css_azimuth_es >
{ using type_one_of_three < t_css_azimuth, t_angle, t_css_azimuth_lri, t_css_azimuth_es > :: type_one_of_three; };

template < > struct type_master < t_css_backval > : type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position >
{ using type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position > :: type_one_of_five; };

template < > struct type_master < t_css_background > : type_range < t_css_background, sz_space, t_css_backval, 1, 5 >
{ using type_range < t_css_background, sz_space, t_css_backval, 1, 5 > :: type_range; };

template < > struct type_master < t_css_background_position > : type_one_two < t_css_background_position, t_refy, t_refx, sz_space >
{ using type_one_two < t_css_background_position, t_refy, t_refx, sz_space > :: type_one_two; };

template < > struct type_master < t_css_border_measure > : type_one_of_three < t_css_border_measure, t_css_inherit, t_css_border_width, t_css_length >
{ using type_one_of_three < t_css_border_measure, t_css_inherit, t_css_border_width, t_css_length > :: type_one_of_three; };

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
template < > struct type_master < t_css_counter_ii > : type_either_or < t_css_counter_ii, t_integer, t_text >
{ using type_either_or < t_css_counter_ii, t_integer, t_text > :: type_either_or; };

template < > struct type_master < t_css_counter_iin > : type_at_least_one < t_css_counter_iin, sz_space, t_css_counter_ii >
{ using type_at_least_one < t_css_counter_iin, sz_space, t_css_counter_ii > :: type_at_least_one; };

template < > struct type_master < t_css_counter_set > : either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_counter_set, t_css_counter_ii, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_counters > : type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type >
{ using type_function_3_opt < t_css_counters, sz_counters, t_text, t_text, t_css_list_style_type > :: type_function_3_opt; };

template < > struct type_master < t_css_content_fn > : type_one_of_three < t_css_content_fn, t_css_attr, t_css_counter, t_css_counters >
{ using type_one_of_three < t_css_content_fn, t_css_attr, t_css_counter, t_css_counters > :: type_one_of_three; };

template < > struct type_master < t_css_content_base > : type_one_of_three < t_css_content_base, t_css_content_fn, t_urifn, t_text >
{ using type_one_of_three < t_css_content_base, t_css_content_fn, t_urifn, t_text > :: type_one_of_three; };

template < > struct type_master < t_css_content_twice > : type_at_least_one < t_css_content_twice, sz_space, t_css_content_base, true >
{ using type_at_least_one < t_css_content_twice, sz_space, t_css_content_base, true > :: type_at_least_one; };

template < > struct type_master < t_css_content > : type_either_or < t_css_content, t_css_content_twice, t_css_inherit >
{ using type_either_or < t_css_content, t_css_content_twice, t_css_inherit > :: type_either_or; };

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

template < > struct type_master < t_css_ls_val > : type_one_of_three < t_css_ls_val, t_css_list_style_type, t_css_list_style_position, t_css_url >
{ using type_one_of_three < t_css_ls_val, t_css_list_style_type, t_css_list_style_position, t_css_url > :: type_one_of_three; };

template < > struct type_master < t_css_list_style > : type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 >
{ using type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_margins > : type_either_or < t_css_margins, t_measures_a, t_css_inherit >
{ using type_either_or < t_css_margins, t_measures_a, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_css_marks > : type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space >
{ using type_one_two < t_css_marks, t_css_mark, t_css_mark, sz_space > :: type_one_two; };

template < > struct type_master < t_css_marx > : either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none >
{ using either_type_or_string < t_css_marx, t_css_marks, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_css_outline > : type_one_of_three < t_css_outline, t_css_border_width, t_css_border_style, t_colour_ii >
{ using type_one_of_three < t_css_outline, t_css_border_width, t_css_border_style, t_colour_ii > :: type_one_of_three; };

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

template < > struct type_master < t_css_play_during_mr > : type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space, sz_mix, sz_repeat >
{ using type_and_maybe_strings < t_css_play_during_mr, t_css_url, sz_space, sz_mix, sz_repeat > :: type_and_maybe_strings; };

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

template < > struct type_master < t_css_url > : type_either_or < t_css_url, t_urifn, t_url >
{ using type_either_or < t_css_url, t_urifn, t_url > :: type_either_or; };

template < > struct type_master < t_css_volume > : type_one_of_three < t_css_volume, t_css_volume_e, t_percent, t_fixedpoint >
{ using type_one_of_three < t_css_volume, t_css_volume_e, t_percent, t_fixedpoint > :: type_one_of_three; };

template < > struct type_master < t_css_wsc_val > : type_one_of_three < t_css_wsc_val, t_css_border_measure, t_css_border_style, t_colour >
{ using type_one_of_three < t_css_wsc_val, t_css_border_measure, t_css_border_style, t_colour > :: type_one_of_three; };

template < > struct type_master < t_css_border_wsc > : type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 >
{ using type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_border_wsc_i > : type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit >
{ using type_either_or < t_css_border_wsc_i, t_css_border_wsc, t_css_inherit > :: type_either_or; };
