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
#include "feedback/nitpick.h"
#include "type/type.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/value.h"

typedef ::std::pair < int, int > t_param;
typedef ::std::vector < t_param > t_params;

void add_param (const arguments& args, t_params& params, int& from, const int i)
{   params.emplace_back (from, i-1);
    from = next_non_whitespace (args.t_, i, -1); }

int split_fn_params (t_params& params, arguments& args, const int start, const int to, nitpick& nits, const bool semi, const ::std::string& name)
{   int round = 0, p = start;
    css_token last = ct_error, prev = ct_error;
    for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i <= to)); i = next_non_whitespace (args.t_, i, to))
    {   switch (args.t_.at (i).t_)
        {   case ct_keyword :
            case ct_identifier :
            case ct_comment :
            case ct_number :
            case ct_string :
                break;
            case ct_round_brac :
                ++round;
                break;
            case ct_round_ket :
                if (--round < 0)
                {   params.emplace_back (p, i - 1);
                    prev = last = ct_error;
                    i = -1; }
                break;
            case ct_comma :
                if ((round == 0) && ! semi) add_param (args, params, p, i);
                prev = last = ct_error;
                break;
            case ct_semicolon :
                if ((round == 0) && semi) add_param (args, params, p, i);
                prev = last = ct_error;
                break;
            case ct_root :
            case ct_whitespace :
            case ct_error :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                break;
            case ct_plus :
            case ct_dash :
                switch (last)
                {   case ct_plus :
                    case ct_dash :
                        switch (prev)
                        {   case ct_plus :
                            case ct_dash :
                            case ct_slash :
                            case ct_splat :
                                nits.pick (nit_css_value_fn, es_error, ec_css,
                                    name, ": unexpected ", quote (tkn_rpt (prev)), " ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                                prev = last = ct_error;
                                break;
                            default :
                                break; }
                        break;
                    default :
                        break; }
                break;
            case ct_slash :
            case ct_splat :
                switch (last)
                {   case ct_plus :
                    case ct_dash :
                    case ct_slash :
                    case ct_splat :
                        nits.pick (nit_css_value_fn, es_error, ec_css,
                            name, ": unexpected ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                        prev = last = ct_error;
                        break;
                    default :
                        break; }
                break;
            case ct_eof :
                i = -1;
                break;
            default :
                nits.pick (nit_css_value_fn, es_error, ec_css, name, ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                break; }
        prev = last;
        if ((i > 0) && ((to < 0) || (i < to)))
            last = args.t_.at (i).t_; }
    if (round > 0)
        nits.pick (nit_css_value_fn, es_error, ec_css, name, ": missing ')' after ", quote (args.t_.at (start).val_));
    return to; } 

bool maybe_math (nitpick& nits, const e_css_property id)
{   const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & (CF_EXPECT_STRING | CF_EXPECT_KEYWORDS)) == 0) return true;
    nits.pick (nit_css_value_fn, ed_css_value_4, "10 Mathematical Expressions", es_error, ec_css, "not a numeric property");
    return false; }

template < e_type TYPE > int check_typed_property (arguments& args, nitpick& nits, const int start, const int to)
{   for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i < to)); i = next_non_whitespace (args.t_, i, to))
        switch (args.t_.at (i).t_)
        {   case ct_keyword :
            case ct_identifier :
                {   nitpick nuts;
                    if (! test_value < TYPE > (nuts, args.v_, args.t_.at (i).val_))
                        return check_typed_identifier (args, nits, i, to, TYPE); 
                    nits.merge (nuts); } 
                break;
            case ct_number :
                {   ::std::string s (assemble_unit (args.t_, i, to));
                    if ((! s.empty ()) && ((s.size () > 1) || (s.at (0) != '-')))
                    {   nitpick nuts;
                        if (! test_value < t_real > (nuts, args.v_, s))
                            test_value < TYPE > (nits, args.v_, s); } }
                break;
            default :
                break; }
    return to; }

template < e_type TYPE, e_css_val_fn T, e_type PARAM, int MAX >
    struct fancy_max
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n)
    {   check_typed_property < PARAM > (args, nits, p.at (n).first, p.at (n).second); 
        if (p.size () > stp (n))
            nits.pick (nit_css_value_param, es_error, ec_css, "too many parameters for ", type_master < t_css_val_fn > :: name (T));} };

template < e_type TYPE, e_css_val_fn T, e_type PARAM >
    struct fancy_max < TYPE, T, PARAM, -1 >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n)
    {   for (unsigned x = n; x < p.size (); ++x)
            check_typed_property < PARAM > (args, nits, p.at (x).first, p.at (x).second); } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type PARAM, e_type... PARAMS >
    struct fn_params : public fn_params < TYPE, T, MIN, MAX, PARAMS... >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n = 0)
    {   if (n >= p.size ())
        {   if (n+1 < MIN) nits.pick (nit_css_value_param, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": parameters ", n+1, " onwards missing or invalid"); }
        else
        {   check_typed_property < PARAM > (args, nits, p.at (n).first, p.at (n).second);
            fn_params < TYPE, T, MIN, MAX, PARAMS... > :: check (args, nits, p, n+1); } } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type PARAM >
    struct fn_params < TYPE, T, MIN, MAX, PARAM >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n = 0)
    {   if (n < p.size ()) fancy_max < TYPE, T, PARAM, MAX > :: check (args, nits, p, n);
        else if (n+1 < MIN) nits.pick (nit_css_value_param, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": parameter ", n+1, " missing or invalid"); } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type... PARAMS > struct value_fn
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   t_params params;
        const int res = split_fn_params (params, args, start, to, nits, (T == cvf_mix), type_master < t_css_val_fn > :: name (T));
        fn_params < TYPE, T, MIN, MAX, PARAMS... > :: check (args, nits, params);
        return res; } }; 

template < e_type TYPE, e_css_val_fn T > struct value_fn_params
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, T, 1, 1, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_none >
{   static int check (arguments& , const int , const int , nitpick& , const e_css_property )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_clamp >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_clamp, 3, 3, TYPE, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_colour_mix, 3, 3, t_css_colour_interpolation, t_css_colour_percent, t_css_colour_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hypot >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_hypot, 1, -1, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_log >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_log, 1, 2, TYPE, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_max >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_max, 1, -1, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_min >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_min, 1, -1, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if ((type_master < TYPE > :: animation_type () != at_none) && (type_master < TYPE > :: animation_type () != at_other))
            return value_fn < TYPE, cvf_mix, 3, 3, t_percent, TYPE, TYPE > :: check (args, start, to, nits);
        nits.pick (nit_css_value_fn, es_error, ec_css, "mix () requires an animatable property");
        return -1; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_mod >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_mod, 2, 2, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rem >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_rem, 2, 2, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_round >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_round, 3, 3, t_css_fn_round_t, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_pow >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_pow, 2, 2, TYPE, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_src >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_src, 1, 2, t_url, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_url >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_url, 1, 2, t_url, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE, e_css_val_fn T, e_css_val_fn ... U > struct value_fns : public value_fns < TYPE, U... >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c, const e_css_property id)
    {   if (c == T) return value_fn_params < TYPE, T > :: check (args, start, to, nits, id);
        return value_fns < TYPE, U... > :: check (args, start, to, nits, c, id); } };  

template < e_type TYPE, e_css_val_fn T > struct value_fns < TYPE, T >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c, const e_css_property id)
    {   PRESUME (c == T, __FILE__, __LINE__);
        return value_fn_params < TYPE, T > :: check (args, start, to, nits, id); } };  

template < e_type T, e_type... TS > struct value_types : public value_types < TS... >
{   static int check (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
    {   if (t != T) return value_types < TS... > :: check (args, start, to, nits, t, fn, id);
        return value_fns < T, CSS_VAL_FN > :: check (args, start, to, nits, fn, id); } };

template < e_type T > struct value_types < T >
{   static int check (arguments& , int& , const int , nitpick& , const e_type , const e_css_val_fn , const e_css_property )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); } };

int test_value_fns (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
#ifdef LIMITED_META_COMPLEXITY
{   if (t <= SSC_TYPE_1_MAX) return value_types < SSC_TYPES_1, t_unknown > :: check (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_2_MAX) return value_types < SSC_TYPES_2, t_unknown > :: check (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_3_MAX) return value_types < SSC_TYPES_3, t_unknown > :: check (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPE_4_MAX) return value_types < SSC_TYPES_4, t_unknown > :: check (args, start, to, nits, t, fn, id);
    return value_types < SSC_TYPES_5, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#else // LIMITED_META_COMPLEXITY
{   return value_types < SSC_TYPES_1, SSC_TYPES_2, SSC_TYPES_3, SSC_TYPES_4, SSC_TYPES_5, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#endif // LIMITED_META_COMPLEXITY 
