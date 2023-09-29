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

#include "main/standard.h"
#include "css/value.h"
#include "css/flags.h"

void add_param (const arguments& args, t_params& params, int& from, const int i)
{   params.emplace_back (from, i-1);
    from = next_non_whitespace (args.t_, i, -1); }

bool maybe_math (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & (CF_EXPECT_STRING | CF_EXPECT_KEYWORDS)) == 0) return true;
    nits.pick (nit_css_value_fn, ed_css_value_4, "10 Mathematical Expressions", es_error, ec_css, "not a numeric property");
    return false; }

bool maybe_image (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_IMAGE) == CF_IMAGE) return true;
    nits.pick (nit_css_value_fn, ed_css_image_3, "2. Image Values: the <image> type", es_error, ec_css, "not an image property");
    return false; }

int check_typed_feature (arguments& args, nitpick& nits, const int start, const int to, const e_css_statement cs, const char* const sz)
{   ::std::string name (assemble_string (args.t_, start, to, true));
    if (name.empty ()) return to;
    if (args.font_feature (cs).find (name) != args.font_feature (cs).cend ()) return to;
    if (name.find_first_not_of (DENARY) == ::std::string::npos) return to;
    else nits.pick (nit_css_font_feature, es_error, ec_css, quote (name), ": unknown @", sz);
    return start; }

int test_value_fns (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
#ifdef LIMITED_META_COMPLEXITY
{   int test_value_fns_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_6 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_7 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_8 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_9 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_10 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_11 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_12 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    
    if (t <= SSC_TYPE_1_MAX) return test_value_fns_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_2_MAX) return test_value_fns_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_3_MAX) return test_value_fns_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_4_MAX) return test_value_fns_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_5_MAX) return test_value_fns_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_6_MAX) return test_value_fns_6 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_7_MAX) return test_value_fns_7 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_8_MAX) return test_value_fns_8 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_9_MAX) return test_value_fns_9 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_10_MAX) return test_value_fns_10 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_11_MAX) return test_value_fns_11 (args, start, to, nits, t, fn, id);
    return test_value_fns_12 (args, start, to, nits, t, fn, id); }
#else // LIMITED_META_COMPLEXITY
{   return value_types <    SSC_TYPES_1, SSC_TYPES_2, SSC_TYPES_3, SSC_TYPES_4, SSC_TYPES_5, SSC_TYPES_6,
                            SSC_TYPES_7, SSC_TYPES_8, SSC_TYPES_9, SSC_TYPES_10, SSC_TYPES_11, SSC_TYPES_12, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#endif // LIMITED_META_COMPLEXITY 
