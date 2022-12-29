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


template < > struct type_master < t_css_backval > : type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position >
{ using type_one_of_five < t_css_backval, t_colour, t_css_image, t_css_background_repeat, t_css_background_attachment, t_css_background_position > :: type_one_of_five; };

template < > struct type_master < t_css_background > : type_range < t_css_background, sz_space, t_css_backval, 1, 5 >
{ using type_range < t_css_background, sz_space, t_css_backval, 1, 5 > :: type_range; };

template < > struct type_master < t_css_background_position > : type_one_two < t_css_background_position, t_refy, t_refx, sz_space >
{ using type_one_two < t_css_background_position, t_refy, t_refx, sz_space > :: type_one_two; };

template < > struct type_master < t_css_border_measure > : type_either_or < t_css_border_measure, t_css_border_width, t_css_length >
{ using type_either_or < t_css_border_measure, t_css_border_width, t_css_length > :: type_either_or; };

template < > struct type_master < t_css_borders_measure > : type_range < t_css_borders_measure, sz_space, t_css_border_measure, 1, 4 >
{ using type_range < t_css_borders_measure, sz_space, t_css_border_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_css_border_styles > : type_range < t_css_border_styles, sz_space, t_css_border_style, 1, 4 >
{ using type_range < t_css_border_styles, sz_space, t_css_border_style, 1, 4 > :: type_range; };

template < > struct type_master < t_css_font_size > : type_one_of_three < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure >
{ using type_one_of_three < t_css_font_size, t_css_absolute_size, t_css_relative_size, t_measure > :: type_one_of_three; };

template < > struct type_master < t_css_image > : type_or_string < t_css_image, t_css_url, sz_none >
{ using type_or_string < t_css_image, t_css_url, sz_none > :: type_or_string; };

template < > struct type_master < t_css_length_auto > : type_or_string < t_css_length_auto, t_css_length, sz_auto >
{ using type_or_string < t_css_length_auto, t_css_length, sz_auto > :: type_or_string; };

template < > struct type_master < t_css_line_height > : either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal >
{ using either_type_or_string < t_css_line_height, t_measure, t_real, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_css_ls_val > : type_one_of_three < t_css_ls_val, t_css_list_style_type, t_css_list_style_position, t_css_url >
{ using type_one_of_three < t_css_ls_val, t_css_list_style_type, t_css_list_style_position, t_css_url > :: type_one_of_three; };

template < > struct type_master < t_css_list_style > : type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 >
{ using type_range < t_css_list_style, sz_space, t_css_ls_val, 1, 3 > :: type_range; };

template < > struct type_master < t_css_margins > : type_range < t_css_margins, sz_space, t_measure_a, 1, 4 >
{ using type_range < t_css_margins, sz_space, t_measure_a, 1, 4 > :: type_range; };

template < > struct type_master < t_css_spacing > : type_or_string < t_css_spacing, t_css_length, sz_normal >
{ using type_or_string < t_css_spacing, t_css_length, sz_normal > :: type_or_string; };

template < > struct type_master < t_css_url > : type_either_or < t_css_url, t_urifn, t_url >
{ using type_either_or < t_css_url, t_urifn, t_url > :: type_either_or; };

template < > struct type_master < t_css_wsc_val > : type_one_of_three < t_css_wsc_val, t_css_border_measure, t_css_border_style, t_colour >
{ using type_one_of_three < t_css_wsc_val, t_css_border_measure, t_css_border_style, t_colour > :: type_one_of_three; };

template < > struct type_master < t_css_border_wsc > : type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 >
{ using type_range < t_css_border_wsc, sz_space, t_css_wsc_val, 1, 3 > :: type_range; };
