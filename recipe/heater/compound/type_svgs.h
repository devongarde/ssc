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
#include "simple/type_svg.h"
#include "compound/type_compound.h"

template < > struct type_master < t_audio_level > : type_or_string < t_audio_level, t_real, sz_inherit >
{ using type_or_string < t_audio_level, t_real, sz_inherit > :: type_or_string; };

template < > struct type_master < t_angle_i > : type_or_string < t_angle_i, t_angle, sz_inherit >
{ using type_or_string < t_angle_i, t_angle, sz_inherit > :: type_or_string; };

template < > struct type_master < t_angle_a > : type_or_string < t_angle_a, t_angle, sz_auto >
{ using type_or_string < t_angle_a, t_angle, sz_auto > :: type_or_string; };

template < > struct type_master < t_angle_ai > : type_or_either_string < t_angle_ai, t_angle, sz_auto, sz_inherit >
{ using type_or_either_string < t_angle_ai, t_angle, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_beginvalues > : type_at_least_one < t_beginvalues, sz_semicolon, t_beginvalue >
{   using type_at_least_one < t_beginvalues, sz_semicolon, t_beginvalue > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_beginvaluelist > : type_or_string < t_beginvaluelist, t_beginvalues, sz_indefinite >
{ using type_or_string < t_beginvaluelist, t_beginvalues, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_colour_profile > : type_or_any_string < t_colour_profile, t_colour_profile_name_or_uri, sz_auto, sz_inherit, sz_srgb >
{ using type_or_any_string < t_colour_profile, t_colour_profile_name_or_uri, sz_auto, sz_inherit, sz_srgb > :: type_or_any_string; };

template < > struct type_master < t_cursor_i > : type_or_string < t_cursor_i, t_cursor_f, sz_inherit >
{ using type_or_string < t_cursor_i, t_cursor_f, sz_inherit > :: type_or_string; };

template < > struct type_master < t_dashes > : type_or_either_string < t_dashes, t_measures, sz_none, sz_inherit >
{ using type_or_either_string < t_dashes, t_measures, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_dur > : type_or_either_string < t_dur, t_svg_time, sz_media, sz_indefinite >
{ using type_or_either_string < t_dur, t_svg_time, sz_media, sz_indefinite > :: type_or_either_string; };

template < > struct type_master < t_dur_repeat > : type_or_string < t_dur_repeat, t_svg_duration, sz_indefinite >
{ using type_or_string < t_dur_repeat, t_svg_duration, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_fontsize > : type_or_string < t_fontsize, t_measure, sz_inherit >
{ using type_or_string < t_fontsize, t_measure, sz_inherit > :: type_or_string; };

template < > struct type_master < t_fontsizeadjust > : type_or_either_string < t_fontsizeadjust, t_real, sz_none, sz_inherit >
{ using type_or_either_string < t_fontsizeadjust, t_real, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_hash_ref > : string_then_type < t_hash_ref, t_idref, sz_hash >
{   using string_then_type < t_hash_ref, t_idref, sz_hash > :: string_then_type;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_hash_fn > : type_function < t_hash_fn, sz_url, t_hash_ref >
{   using type_function < t_hash_fn, sz_url, t_hash_ref > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_keyspline > : type_exactly_n < t_keyspline, sz_commaspace, t_real, 4 >
{ using type_exactly_n < t_keyspline, sz_commaspace, t_real, 4 > :: type_exactly_n; };

template < > struct type_master < t_keysplines > : type_at_least_one < t_keysplines, sz_semicolon, t_keyspline >
{ using type_at_least_one < t_keysplines, sz_semicolon, t_keyspline > :: type_at_least_one; };

template < > struct type_master < t_keytimes > : type_at_least_one < t_keytimes, sz_semicolon, t_zero_to_one >
{   using type_at_least_one < t_keytimes, sz_semicolon, t_zero_to_one > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_time; } };

template < > struct type_master < t_line_height > : either_type_or_string < t_line_height, t_measure, t_real, sz_normal >
{ using either_type_or_string < t_line_height, t_measure, t_real, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_localfn > : type_function < t_localfn, sz_local, t_text >
{   using type_function < t_localfn, sz_local, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_marker > : type_id_or_either_string < t_marker, t_hash_fn, sz_none, sz_inherit >
{   using type_id_or_either_string < t_marker, t_hash_fn, sz_none, sz_inherit > :: type_id_or_either_string;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_navigation > : type_id_or_either_string < t_navigation, t_hash_fn, sz_auto, sz_self >
{   using type_id_or_either_string < t_navigation, t_hash_fn, sz_auto, sz_self > :: type_id_or_either_string;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_opacity > : type_or_string < t_opacity, t_zero_to_one, sz_inherit >
{ using type_or_string < t_opacity, t_zero_to_one, sz_inherit > :: type_or_string; };

template < > struct type_master < t_panose1 > : type_exactly_n < t_panose1, sz_space, t_integer, 10 >
{ using type_exactly_n < t_panose1, sz_space, t_integer, 10 > :: type_exactly_n; };

template < > struct type_master < t_repeatcount > : type_or_string < t_repeatcount, t_0_more, sz_indefinite >
{ using type_or_string < t_repeatcount, t_0_more, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_preserveaspectratio10 > : type_one_or_both < t_preserveaspectratio10, t_svg_align, sz_space, t_meetslice >
{   using type_one_or_both < t_preserveaspectratio10, t_svg_align, sz_space, t_meetslice > :: type_one_or_both;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_preserveaspectratio12 > : type_or_string < t_preserveaspectratio12, t_preserveaspectratio10, sz_defer >
{ using type_or_string < t_preserveaspectratio12, t_preserveaspectratio10, sz_defer > :: type_or_string; };

template < > struct type_master < t_rotate_anim > : type_or_either_string < t_rotate_anim, t_angle, sz_auto, sz_autoreverse >
{ using type_or_either_string < t_rotate_anim, t_angle, sz_auto, sz_autoreverse > :: type_or_either_string; };

template < > struct type_master < t_setback_offset > : type_range < t_setback_offset, sz_commaspace, t_measure, 1, 4 >
{ using type_range < t_setback_offset, sz_commaspace, t_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_shape_fn_circle > : type_function < t_shape_fn_circle, sz_circle, t_text >
{   using type_function < t_shape_fn_circle, sz_circle, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_ellipse > : type_function < t_shape_fn_ellipse, sz_ellipse, t_text >
{   using type_function < t_shape_fn_ellipse, sz_ellipse, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_polygon > : type_function < t_shape_fn_polygon, sz_polygon, t_text >
{   using type_function < t_shape_fn_polygon, sz_polygon, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn > : type_one_of < t_shape_fn, false, t_shape_fn_circle, t_shape_fn_ellipse, t_shape_fn_polygon >
{   using type_one_of < t_shape_fn, false, t_shape_fn_circle, t_shape_fn_ellipse, t_shape_fn_polygon > :: type_one_of;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_none_uri > : type_or_string < t_shape_none_uri, t_shape_uri, sz_none >
{ using type_or_string < t_shape_none_uri, t_shape_uri, sz_none > :: type_or_string; };

template < > struct type_master < t_svg_baselineshift > : type_either_or < t_svg_baselineshift, t_baselineshift, t_measure >
{   using type_either_or < t_svg_baselineshift, t_baselineshift, t_measure > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_length; } };

template < > struct type_master < t_svg_clip > : type_or_either_string < t_svg_clip, t_svg_shape, sz_auto, sz_inherit >
{ using type_or_either_string < t_svg_clip, t_svg_shape, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_svg_shape > : type_function < t_svg_shape, sz_rect, t_real >
{   using type_function < t_svg_shape, sz_rect, t_real > :: type_function;
    static e_animation_type animation_type () noexcept { return at_number; } };

template < > struct type_master < t_svg_host > : type_either_string < t_svg_host, sz_svg, sz_host >
{ using type_either_string < t_svg_host, sz_svg, sz_host > :: type_either_string; };

template < > struct type_master < t_svg_svg > : type_string < t_svg_svg, sz_svg >
{ using type_string < t_svg_svg, sz_svg > :: type_string; };

template < > struct type_master < t_svg_transform > : type_or_string < t_svg_transform, t_transform, sz_none >
{ using type_or_string < t_svg_transform, t_transform, sz_none > :: type_or_string; };

template < > struct type_master < t_svg_time_default > : type_or_string < t_svg_time_none, t_svg_time, sz_default >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_default > :: type_or_string; };

template < > struct type_master < t_svg_time_inherit > : type_or_string < t_svg_time_none, t_svg_time, sz_inherit >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_inherit > :: type_or_string; };

template < > struct type_master < t_svg_time_none > : type_or_string < t_svg_time_none, t_svg_time, sz_none >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_none > :: type_or_string; };

template < > struct type_master < t_svg_values > : type_at_least_one < t_svg_values, sz_semicolon, t_real >
{ using type_at_least_one < t_svg_values, sz_semicolon, t_real > :: type_at_least_one; };

template < > struct type_master < t_vector_effect_2s > : type_at_least_one < t_vector_effect_2s, sz_space, t_vector_effect_2 >
{ using type_at_least_one < t_vector_effect_2s, sz_space, t_vector_effect_2 > :: type_at_least_one; };

template < > struct type_master < t_vector_effect_20 > : type_many_then_maybe < t_vector_effect_20, t_vector_effect_2, sz_space, t_viewportscreen >
{   using type_many_then_maybe < t_vector_effect_20, t_vector_effect_2, sz_space, t_viewportscreen > :: type_many_then_maybe;
    static e_animation_type animation_type () noexcept { return at_list; } };

template < > struct type_master < t_svg_viewboxrect > : type_exactly_n < t_svg_viewboxrect, sz_commaspace, t_real, 4 >
{   using type_exactly_n < t_svg_viewboxrect, sz_commaspace, t_real, 4 > :: type_exactly_n;
    static e_animation_type animation_type () noexcept { return at_coordinate; } };

template < > struct type_master < t_urange > : type_at_least_one < t_urange, sz_comma, t_text >
{   using type_at_least_one < t_urange, sz_comma, t_text > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_urifn > : type_function < t_urifn, sz_url, t_url >
{   using type_function < t_urifn, sz_url, t_url > :: type_function;
    static e_animation_type animation_type () noexcept { return at_url; } };

template < > struct type_master < t_urifn_ni > : type_id_or_either_string < t_urifn_ni, t_urifn, sz_none, sz_inherit >
{   using type_id_or_either_string < t_urifn_ni, t_urifn, sz_none, sz_inherit > :: type_id_or_either_string;
    static e_animation_type animation_type () noexcept { return at_url; } };

template < > struct type_master < t_vertical_align > : type_either_or < t_vertical_align, t_vertical_align_enum, t_measure >
{   using type_either_or < t_vertical_align, t_vertical_align_enum, t_measure > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_svg_viewbox > : tidy_string < t_svg_viewbox >
{   using tidy_string < t_svg_viewbox > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        tidy_string < t_svg_viewbox > :: set_value (nits, v, ss);
        if (v.is_svg_12 () && compare_complain (nits, v, QNONE, ss))
            type_master < t_svg_viewbox > :: status (s_good);
        else
        {   type_master < t_svg_viewboxrect > vb;
            vb.set_value (nits, v, ss);
            if (vb.good ())
                if (vb.size () != 4)
                    nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX expects four numbers: x, y, width and height (or '", QNONE "')");
                else
                {   const double width = lexical < double > :: cast (vb.at (2));
                    const double height = lexical < double > :: cast (vb.at (3));
                    if ((width >= 0.0) && (height >= 0.0)) return;
                    if (width < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX width cannot be negative");
                    if (height < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX height cannot be negative"); }
            else if (v.is_svg_12 ()) nits.pick (nit_viewbox, es_error, ec_type, quote (ss), ": '", QNONE "' or four numbers (x y width height) expected");
            else nits.pick (nit_viewbox, es_error, ec_type, quote (ss), ": four numbers (x y width height) expected");
            tidy_string < t_svg_viewbox > :: status (s_invalid); } } };


template < > struct type_master < t_clip_path_rule > : type_or_either_string < t_clip_path_rule, t_urifn, sz_none, sz_inherit >
{ using type_or_either_string < t_clip_path_rule, t_urifn, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_rendering_colour_space > : type_one_of < t_rendering_colour_space, false, t_colour_interpolation, t_colour_profile_name, t_urifn >
{ using type_one_of < t_rendering_colour_space, false, t_colour_interpolation, t_colour_profile_name, t_urifn > :: type_one_of; };

template < > struct type_master < t_colour_profile_name_or_uri > : type_either_or < t_colour_profile_name_or_uri, t_urifn, t_colour_profile_name >
{   using type_either_or < t_colour_profile_name_or_uri, t_urifn, t_colour_profile_name > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_colour; } };

template < > struct type_master < t_shape_uri > : type_either_or < t_shape_uri, t_shape_fn, t_urifn >
{   using type_either_or < t_shape_uri, t_shape_fn, t_urifn > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_cursor_f > : type_many_then_must < t_cursor_f, t_urifn, sz_comma, t_cursor >
{   using type_many_then_must < t_cursor_f, t_urifn, sz_comma, t_cursor > :: type_many_then_must;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_svg_profile_name > : tidy_string < t_svg_profile_name > // check against SVG colour profile statements
{   using tidy_string < t_svg_profile_name > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_svg_name_iri > : type_either_or < t_svg_name_iri, t_url, t_svg_profile_name >
{   using type_either_or < t_svg_name_iri, t_url, t_svg_profile_name > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_svg_colour_profile > : type_or_any_string < t_svg_colour_profile, t_svg_name_iri, sz_auto, sz_inherit, sz_srgb >
{   using type_or_any_string < t_svg_colour_profile, t_svg_name_iri, sz_auto, sz_inherit, sz_srgb > :: type_or_any_string;
    static e_animation_type animation_type () noexcept { return at_other; } };
