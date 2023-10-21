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
#include "simple/type_numeric.h"
#include "compound/type_compound.h"

template < > struct type_master < t_0_more > : n_or_more < 0 >
{   static bool is_numeric () { return true; }
    using n_or_more < 0 > :: n_or_more; };

template < > struct type_master < t_1_more > : n_or_more < 1 >
{   static bool is_numeric () { return true; }
    using n_or_more < 1 > :: n_or_more; };

template < > struct type_master < t_2x_integer > : type_one_two < t_2x_integer, t_integer, t_integer, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two < t_2x_integer, t_integer, t_integer, sz_space_char > :: type_one_two; };

template < > struct type_master < t_2x_unsigned > : type_one_two < t_2x_unsigned, t_unsigned, t_unsigned, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two < t_2x_unsigned, t_unsigned, t_unsigned, sz_space_char > :: type_one_two; };

template < > struct type_master < t_3x_integer > : type_one_two_three < t_3x_integer, t_integer, t_integer, t_integer, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three < t_3x_integer, t_integer, t_integer, t_integer, sz_space_char > :: type_one_two_three; };

template < > struct type_master < t_3x_real > : type_one_two_three < t_3x_real, t_real, t_real, t_real, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three < t_3x_real, t_real, t_real, t_real, sz_space_char > :: type_one_two_three; };

template < > struct type_master < t_3x_unsigned > : type_one_two_three < t_3x_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three < t_3x_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char > :: type_one_two_three; };

template < > struct type_master < t_4x_0_to_6 > : type_one_two_three_four < t_4x_0_to_6, t_0_to_6, t_0_to_6, t_0_to_6, t_0_to_6, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three_four < t_4x_0_to_6, t_0_to_6, t_0_to_6, t_0_to_6, t_0_to_6, sz_space_char > :: type_one_two_three_four; };

template < > struct type_master < t_4x_unsigned > : type_one_two_three_four < t_4x_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three_four < t_4x_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char > :: type_one_two_three_four; };

template < > struct type_master < t_5x_unsigned > : type_one_two_three_four_five < t_5x_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three_four_five < t_5x_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, t_unsigned, sz_space_char > :: type_one_two_three_four_five; };

template < > struct type_master < t_a_b_c_d > : type_one_two_three_four < t_a_b_c_d, t_0_to_255, t_0_to_255, t_0_to_255, t_0_to_255, sz_dot_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three_four < t_a_b_c_d, t_0_to_255, t_0_to_255, t_0_to_255, t_0_to_255, sz_dot_char > :: type_one_two_three_four; };

template < > struct type_master < t_integer_ai > : type_or_either_string < t_integer_ai, t_integer, sz_auto, sz_inherit >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_integer_ai, t_integer, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_integer_i > : type_or_string < t_integer_i, t_integer, sz_inherit >
{    static bool is_numeric () { return true; }
    using type_or_string < t_integer_i, t_integer, sz_inherit > :: type_or_string; };

template < > struct type_master < t_integer_is > : type_or_either_string < t_integer_is, t_integer, sz_increment, sz_same >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_integer_is, t_integer, sz_increment, sz_same > :: type_or_either_string; };

template < > struct type_master < t_integer_ln > : type_or_either_string < t_integer_ln, t_integer, sz_last, sz_none >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_integer_ln, t_integer, sz_last, sz_none > :: type_or_either_string; };

template < > struct type_master < t_integer_nl > : type_or_string < t_integer_nl, t_integer, sz_no_limit >
{    static bool is_numeric () { return true; }
    using type_or_string < t_integer_nl, t_integer, sz_no_limit > :: type_or_string; };

template < > struct type_master < t_integer_oo > : type_or_either_string < t_integer_oo, t_integer, sz_off, sz_on >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_integer_oo, t_integer, sz_off, sz_on > :: type_or_either_string; };

template < > struct type_master < t_integers > : type_at_least_one < t_integers, sz_space_char, t_integer >
{   static bool is_numeric () { return true; }
    using type_at_least_one < t_integers, sz_space_char, t_integer > :: type_at_least_one; };

template < > struct type_master < t_integers_a > : type_range < t_integers_a, sz_space_char, t_integer_ai, 1, 3 >
{   static bool is_numeric () { return true; }
    using type_range < t_integers_a, sz_space_char, t_integer_ai, 1, 3 > :: type_range; };

template < > struct type_master < t_positive_1_2 > : type_range < t_positive_1_2, sz_commaspace, t_0_more, 1, 2 >
{   static bool is_numeric () { return true; }
    using type_range < t_positive_1_2, sz_commaspace, t_0_more, 1, 2 > :: type_range; };

template < > struct type_master < t_rational > : type_one_two < t_rational, t_integer, t_integer, sz_slash >
{   static bool is_numeric () { return true; }
    using type_one_two < t_rational, t_integer, t_integer, sz_slash > :: type_one_two; };

template < > struct type_master < t_rationals > : type_at_least_one < t_rationals, sz_space_char, t_rational >
{   static bool is_numeric () { return true; }
    using type_at_least_one < t_rationals, sz_space_char, t_rational > :: type_at_least_one; };

template < > struct type_master < t_real_i > : type_or_string < t_real_i, t_real, sz_inherit >
{   static bool is_numeric () { return true; }
    using type_or_string < t_real_i, t_real, sz_inherit > :: type_or_string; };

template < > struct type_master < t_real_ai > : type_or_either_string < t_real_ai, t_real, sz_auto, sz_inherit >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_real_ai, t_real, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_real_n > : type_or_string < t_real_n, t_real, sz_none >
{   static bool is_numeric () { return true; }
    using type_or_string < t_real_n, t_real, sz_none > :: type_or_string; };

template < > struct type_master < t_real_ni > : type_or_either_string < t_real_ni, t_real, sz_none, sz_inherit >
{   static bool is_numeric () { return true; }
    using type_or_either_string < t_real_ni, t_real, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_reals > : type_at_least_one < t_reals, sz_commaspace, t_real >
{   static bool is_numeric () { return true; }
    using type_at_least_one < t_reals, sz_commaspace, t_real > :: type_at_least_one; };

template < > struct type_master < t_unsigned_1_more > : type_integer_between < t_unsigned_1_more, unsigned, 1, 0 >
{   static bool is_numeric () { return true; }
    using type_integer_between < t_unsigned_1_more, unsigned, 1, 0 > :: type_integer_between; };

template < > struct type_master < t_unsigned_1_more_a > : type_or_string < t_unsigned_1_more_a, t_unsigned_1_more, sz_auto >
{   static bool is_numeric () { return true; }
    using type_or_string < t_unsigned_1_more_a, t_unsigned_1_more, sz_auto > :: type_or_string; };

template < > struct type_master < t_unsigned_1_or_2 > : type_range < t_unsigned_1_or_2, sz_commaspace, t_unsigned, 1, 2 >
{   static bool is_numeric () { return true; }
    using type_range < t_unsigned_1_or_2, sz_commaspace, t_unsigned, 1, 2 > :: type_range; };

template < > struct type_master < t_unsigned_n > : type_or_string < t_unsigned_n, t_unsigned, sz_none >
{ using type_or_string < t_unsigned_n, t_unsigned, sz_none > :: type_or_string; };

template < > struct type_master < t_unsigneds > : type_at_least_one < t_unsigneds, sz_space_char, t_unsigned >
{   static bool is_numeric () { return true; }
    using type_at_least_one < t_unsigneds, sz_space_char, t_unsigned > :: type_at_least_one; };

template < > struct type_master < t_urational > : type_one_two < t_urational, t_unsigned, t_unsigned, sz_slash >
{   static bool is_numeric () { return true; }
    using type_one_two < t_urational, t_unsigned, t_unsigned, sz_slash > :: type_one_two; };

template < > struct type_master < t_urationals > : type_at_least_one < t_urationals, sz_space_char, t_urational >
{   static bool is_numeric () { return true; }
    using type_at_least_one < t_urationals, sz_space_char, t_urational > :: type_at_least_one; };

template < > struct type_master < t_3x_urational > : type_one_two_three < t_3x_urational, t_urational, t_urational, t_urational, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three < t_3x_urational, t_urational, t_urational, t_urational, sz_space_char > :: type_one_two_three; };

template < > struct type_master < t_4x_urational > : type_one_two_three_four < t_4x_urational, t_urational, t_urational, t_urational, t_urational, sz_space_char >
{   static bool is_numeric () { return true; }
    using type_one_two_three_four < t_4x_urational, t_urational, t_urational, t_urational, t_urational, sz_space_char > :: type_one_two_three_four; };

template < > struct type_master < t_x_dot_y > : type_one_two < t_x_dot_y, t_integer, t_integer, sz_dot_char >
{   using type_one_two < t_x_dot_y, t_integer, t_integer, sz_dot_char > :: type_one_two; };

template < > struct type_master < t_reals_1_up > : type_some_of < t_reals_1_up, sz_space_char, 1, 3, t_real_1_up >
{ using type_some_of < t_reals_1_up, sz_space_char, 1, 3, t_real_1_up > :: type_some_of; };

template < > struct type_master < t_resolution > : type_number_unit_4 < t_resolution, t_0_more, sz_dpi, sz_dpcm, sz_dppx, sz_x >
{ using type_number_unit_4 < t_resolution, t_0_more, sz_dpi, sz_dpcm, sz_dppx, sz_x > :: type_number_unit_4; };

template < > struct type_master < t_zero_to_ones > : type_at_least_one < t_zero_to_ones, sz_commaspace, t_zero_to_one >
{    static bool is_numeric () { return true; }
    using type_at_least_one < t_zero_to_ones, sz_commaspace, t_zero_to_one > :: type_at_least_one; };
