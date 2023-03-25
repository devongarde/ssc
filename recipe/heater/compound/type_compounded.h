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
#include "simple/type_cookie.h"
#include "simple/type_misc.h"
#include "compound/type_compound.h"

template < > struct type_master < t_cookies > : type_at_least_one < t_cookies, sz_semicolon, t_cookie >
{ using type_at_least_one < t_cookies, sz_semicolon, t_cookie > :: type_at_least_one; };

template < > struct type_master < t_css_all_2 > : public type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset >
{   using type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset > :: type_sz; };

template < > struct type_master < t_css_caret > : type_some_of < t_css_caret, sz_space, 0, 2, t_css_colour_a, t_css_caret_shape >
{ using type_some_of < t_css_caret, sz_space, 0, 2, t_css_colour_a, t_css_caret_shape > :: type_some_of; };

template < > struct type_master < t_current_colour_sz > : type_string < t_current_colour_sz, sz_currentcolour >
{ using type_string < t_current_colour_sz, sz_currentcolour > :: type_string; };

template < > struct type_master < t_hslafn > : type_function_all < t_hslafn, sz_hsla, t_hue, t_percent, t_percent, t_zero_to_one >
{ using type_function_all < t_hslafn, sz_hsla, t_hue, t_percent, t_percent, t_zero_to_one > :: type_function_all; };

template < > struct type_master < t_hslfn > : type_function_all < t_hslfn, sz_hsl, t_hue, t_percent, t_percent >
{ using type_function_all < t_hslfn, sz_hsl, t_hue, t_percent, t_percent > :: type_function_all; };

template < > struct type_master < t_integer_or_percent > : type_either_or < t_integer_or_percent, t_percent, t_0_to_255 >
{ using type_either_or < t_integer_or_percent, t_percent, t_0_to_255 > :: type_either_or; };

template < > struct type_master < t_rgbafn > : type_function_all < t_rgbafn, sz_rgba, t_integer_or_percent, t_integer_or_percent, t_integer_or_percent, t_zero_to_one >
{ using type_function_all < t_rgbafn, sz_rgba, t_integer_or_percent, t_integer_or_percent, t_integer_or_percent, t_zero_to_one > :: type_function_all; };

template < > struct type_master < t_transparentsz > : type_string < t_transparentsz, sz_transparent >
{ using type_string < t_transparentsz, sz_transparent > :: type_string; };

template < > struct type_master < t_svg_src > : public either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit >
{   using either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit > :: either_type_or_either_string; };

template < > struct type_master < t_xlinktype > : type_string < t_xlinktype, sz_simple >
{ using type_string < t_xlinktype, sz_simple > :: type_string; };
