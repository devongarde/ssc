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
{ using n_or_more < 0 > :: n_or_more; };

template < > struct type_master < t_1_more > : n_or_more < 1 >
{ using n_or_more < 1 > :: n_or_more; };

template < > struct type_master < t_integer_ai > : type_or_either_string < t_integer_ai, t_integer, sz_auto, sz_inherit >
{ using type_or_either_string < t_integer_ai, t_integer, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_integer_i > : type_or_string < t_integer_i, t_integer, sz_inherit >
{ using type_or_string < t_integer_i, t_integer, sz_inherit > :: type_or_string; };

template < > struct type_master < t_positive_1_2 > : type_range < t_positive_1_2, sz_commaspace, t_0_more, 1, 2 >
{ using type_range < t_positive_1_2, sz_commaspace, t_0_more, 1, 2 > :: type_range; };

template < > struct type_master < t_real_i > : type_or_string < t_real_i, t_real, sz_inherit >
{ using type_or_string < t_real_i, t_real, sz_inherit > :: type_or_string; };

template < > struct type_master < t_real_ai > : type_or_either_string < t_real_ai, t_real, sz_auto, sz_inherit >
{ using type_or_either_string < t_real_ai, t_real, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_real_ni > : type_or_either_string < t_real_ni, t_real, sz_none, sz_inherit >
{ using type_or_either_string < t_real_ni, t_real, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_reals > : type_at_least_one < t_reals, sz_commaspace, t_real >
{ using type_at_least_one < t_reals, sz_commaspace, t_real > :: type_at_least_one; };

template < > struct type_master < t_unsigned_1_or_2 > : type_range < t_unsigned_1_or_2, sz_commaspace, t_unsigned, 1, 2 >
{ using type_range < t_unsigned_1_or_2, sz_commaspace, t_unsigned, 1, 2 > :: type_range; };

template < > struct type_master < t_zero_to_ones > : type_at_least_one < t_zero_to_ones, sz_commaspace, t_zero_to_one >
{ using type_at_least_one < t_zero_to_ones, sz_commaspace, t_zero_to_one > :: type_at_least_one; };
