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
#include "type/type.h"
#include "css/arguments.h"

typedef ::std::pair < int, int > t_param;
typedef ::std::vector < t_param > t_params;

void add_param (const arguments& args, t_params& params, int& from, const int i);
int check_typed_identifier (arguments& args, nitpick& nits, const int start, const int to, const e_type t);
int check_typed_feature (arguments& args, nitpick& nits, const int start, const int to, const e_css_statement cs, const char* const sz);
bool maybe_content (nitpick& nits, const e_css_property id);
bool maybe_filter (nitpick& nits, const e_css_property id);
bool maybe_float (nitpick& nits, const e_css_property id);
bool maybe_image (nitpick& nits, const e_css_property id);
bool maybe_math (nitpick& nits, const e_css_property id);
bool maybe_offset_path (nitpick& nits, const e_css_property id);
bool maybe_text_4 (nitpick& nits, const e_css_property id);
bool maybe_text_overflow (nitpick& nits, const e_css_property id);
bool maybe_transform (nitpick& nits, const e_css_property id, const bool t4 = false);
int test_value_fns (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
