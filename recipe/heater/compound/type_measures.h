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
#include "simple/type_measure.h"
#include "compound/type_compound.h"

template < > struct type_master < t_measures > : type_at_least_none < t_measures, sz_space_comma, t_measure >
{ using type_at_least_none < t_measures, sz_space_comma, t_measure > :: type_at_least_none; };

template < > struct type_master < t_measure_4 > : type_range < t_measure_4, sz_space_char, t_measure, 1, 4 >
{ using type_range < t_measure_4, sz_space_char, t_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_measure_i > : type_either_or < t_measure_i, t_measure, t_css_inherit >
{ using type_either_or < t_measure_i, t_measure, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_measure_in > : either_type_or_string < t_measure_in, t_measure, t_css_inherit, sz_none >
{ using either_type_or_string < t_measure_in, t_measure, t_css_inherit, sz_none > :: either_type_or_string; };

template < > struct type_master < t_measure_a > : type_or_string < t_measure_a, t_measure, sz_auto >
{ using type_or_string < t_measure_a, t_measure, sz_auto > :: type_or_string; };

template < > struct type_master < t_measure_ai > : either_type_or_string < t_measure_ai, t_measure, t_css_inherit, sz_auto >
{ using either_type_or_string < t_measure_ai, t_measure, t_css_inherit, sz_auto > :: either_type_or_string; };

template < > struct type_master < t_measure_ni > : either_type_or_string < t_measure_ni, t_measure, t_css_inherit, sz_normal >
{ using either_type_or_string < t_measure_ni, t_measure, t_css_inherit, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_measures_a > : type_range < t_measures_a, sz_space_char, t_measure_a, 1, 4 >
{ using type_range < t_measures_a, sz_space_char, t_measure_a, 1, 4 > :: type_range; };

template < > struct type_master < t_measures_all > : type_or_string < t_measures_all, t_measures, sz_all >
{ using type_or_string < t_measures_all, t_measures, sz_all > :: type_or_string; };

template < > struct type_master < t_measures_i > : type_either_or < t_measures_i, t_measure_4, t_css_inherit >
{ using type_either_or < t_measures_i, t_measure_4, t_css_inherit > :: type_either_or; };

template < > struct type_master < t_refx > : type_or_any_string < t_refx, t_measure, sz_left, sz_centre, sz_right >
{ using type_or_any_string < t_refx, t_measure, sz_left, sz_centre, sz_right > :: type_or_any_string; };

template < > struct type_master < t_refy > : type_or_any_string < t_refy, t_measure, sz_top, sz_centre, sz_bottom >
{ using type_or_any_string < t_refy, t_measure, sz_top, sz_centre, sz_bottom > :: type_or_any_string; };
