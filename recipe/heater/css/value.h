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

// in typed_property.h, which loads value.h
template < e_type TYPE, e_css_property IDENTITY > struct check_typed_property
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s); };

template < e_css_property IDENTITY, e_type TYPE, int PARAM > struct value_param
{   static int check (arguments& args, const int start, const int , nitpick& nits)
    {   nits.pick (nit_css_syntax, es_error, ec_css, "too many parameters at ", quote (args.t_.at (start).val_), " (1)");
        return -1; } };

template < e_css_property IDENTITY, e_type TYPE > struct value_param < IDENTITY, TYPE, 0 >
{   static int check (arguments& args, const int i, const int to, nitpick& nits)
    {   int j = next_non_whitespace (args.t_, i, to);
        if ((j > 0) && ((to < 0) || (j <= to)) && (args.t_.at (j).t_ == ct_round_brac))
            return check_typed_property < TYPE, IDENTITY > :: check (args, i, to, nits, args.t_.at (i).val_);
        type_master < TYPE > tm;
        tm.set_value (nits, args.v_, args.t_.at (i).val_);
        return i + 1; } };

#define MAX_PARAMS 3

template < e_css_property IDENTITY, e_type TYPE, int PARAM > struct value_params : public value_params < IDENTITY, TYPE, PARAM-1 >
{   static int check (const int param, arguments& args, const int start, const int to, nitpick& nits)
    {   if (param == PARAM) return value_param < IDENTITY, TYPE, PARAM > :: check (args, start, to, nits);
        PRESUME (param < PARAM, __FILE__, __LINE__);
        return value_params < IDENTITY, TYPE, PARAM-1 > :: check (param, args, start, to, nits); } };  

template < e_css_property IDENTITY, e_type TYPE > struct value_params < IDENTITY, TYPE, 0 >
{   static int check (const int param, arguments& args, const int start, const int to, nitpick& nits)
    {   PRESUME (param == 0, __FILE__, __LINE__);
        return value_param < IDENTITY, TYPE, 0 > :: check (args, start, to, nits); } };  

template < e_type TYPE, e_css_property IDENTITY, e_css_val_fn T > struct value_fn
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   const int k = next_non_whitespace (args.t_, start, to);
        if ((k < 0) || ((to >= 0) && (k > to))) return k;
        if (args.t_.at (k).t_ != ct_round_brac)
        {   nits.pick (nit_css_syntax, es_error, ec_css, "'(' expected after ", quote (args.t_.at (start).val_));
            return k; }
        int round = 0, param = 0;
        css_token last = ct_error, prev = ct_error;
        for (int i = next_non_whitespace (args.t_, k, to); (i > 0) && ((to < 0) || (i <= to)); i = next_non_whitespace (args.t_, i, to))
        {   switch (args.t_.at (i).t_)
            {   case ct_keyword :
                case ct_identifier :
                    i = value_params < IDENTITY, TYPE, MAX_PARAMS > :: check (param, args, i, to, nits);
                    if ((i > 0) && ((to < 0) || (i <= to)))
                        if (args.t_.at (i).t_ == ct_round_ket)
                            if (round > 0) --round;
                    break;
                case ct_round_brac :
                    ++round;
                    break;
                case ct_round_ket :
                    if ((round > 0) && (--round == 0))
                        return next_non_whitespace (args.t_, i, to);
                    break;
                case ct_comma :
                    if (++param > MAX_PARAMS)
                    {   nits.pick (nit_css_syntax, es_error, ec_css, "too many parameters at ", quote (args.t_.at (start).val_), " (2)");
                        i = -1; }
                    prev = last = ct_error;
                    break;
                case ct_root :
                case ct_whitespace :
                case ct_error :
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    break;
                case ct_comment :
                case ct_number :
                    break;
                case ct_string :
                    nits.pick (nit_css_syntax, es_error, ec_css, "CSS formulae do not work with strings");
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
                                    nits.pick (nit_css_syntax, es_error, ec_css,
                                        "unexpected ", quote (tkn_rpt (prev)), " ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
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
                            nits.pick (nit_css_syntax, es_error, ec_css,
                                "unexpected ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                            prev = last = ct_error;
                            break;
                        default :
                            break; }
                    break;
                case ct_eof :
                    return -1;
                default :
                    nits.pick (nit_css_syntax, es_error, ec_css, "unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                    break; }
            prev = last;
            if ((i > 0) && ((to < 0) || (i < to)))
                last = args.t_.at (i).t_; }
        if (round > 0)
            nits.pick (nit_css_syntax, es_error, ec_css, "missing ')' after ", quote (args.t_.at (start).val_));
        return to; } };

#ifdef LIMITED_META_COMPLEXITY
template < e_type TYPE, e_css_property IDENTITY > struct value_fns
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c)
    {   switch (c)
        {   case cvf_none : return start;
            case cvf_abs : return value_fn < TYPE, IDENTITY, cvf_abs > :: check (args, start, to, nits);
            case cvf_acos : return value_fn < TYPE, IDENTITY, cvf_acos > :: check (args, start, to, nits);
            case cvf_asin : return value_fn < TYPE, IDENTITY, cvf_asin > :: check (args, start, to, nits);
            case cvf_atan : return value_fn < TYPE, IDENTITY, cvf_atan > :: check (args, start, to, nits);
            case cvf_atan2 : return value_fn < TYPE, IDENTITY, cvf_atan2 > :: check (args, start, to, nits);
            case cvf_calc : return value_fn < TYPE, IDENTITY, cvf_calc > :: check (args, start, to, nits);
            case cvf_clamp : return value_fn < TYPE, IDENTITY, cvf_clamp > :: check (args, start, to, nits);
            case cvf_cos : return value_fn < TYPE, IDENTITY, cvf_cos > :: check (args, start, to, nits);
            case cvf_exp : return value_fn < TYPE, IDENTITY, cvf_exp > :: check (args, start, to, nits);
            case cvf_hypot : return value_fn < TYPE, IDENTITY, cvf_hypot > :: check (args, start, to, nits);
            case cvf_log : return value_fn < TYPE, IDENTITY, cvf_log > :: check (args, start, to, nits);
            case cvf_max : return value_fn < TYPE, IDENTITY, cvf_max > :: check (args, start, to, nits);
            case cvf_min : return value_fn < TYPE, IDENTITY, cvf_min > :: check (args, start, to, nits);
            case cvf_mod : return value_fn < TYPE, IDENTITY, cvf_mod > :: check (args, start, to, nits);
            case cvf_pow : return value_fn < TYPE, IDENTITY, cvf_pow > :: check (args, start, to, nits);
            case cvf_rem : return value_fn < TYPE, IDENTITY, cvf_rem > :: check (args, start, to, nits);
            case cvf_round : return value_fn < TYPE, IDENTITY, cvf_round > :: check (args, start, to, nits);
            case cvf_sign : return value_fn < TYPE, IDENTITY, cvf_sign > :: check (args, start, to, nits);
            case cvf_sin : return value_fn < TYPE, IDENTITY, cvf_sin > :: check (args, start, to, nits);
            case cvf_sqrt : return value_fn < TYPE, IDENTITY, cvf_sqrt > :: check (args, start, to, nits);
            case cvf_tan : return value_fn < TYPE, IDENTITY, cvf_tan > :: check (args, start, to, nits);
            default : break; }
        GRACEFUL_CRASH (__FILE__, __LINE__); } };
#else // LIMITED_META_COMPLEXITY
template < e_type TYPE, e_css_property IDENTITY, e_css_val_fn T, e_css_val_fn ... U > struct value_fns : public value_fns < TYPE, IDENTITY, U... >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c)
    {   if (c == T) return value_fn < TYPE, IDENTITY, T > :: check (args, start, to, nits);
        return value_fns < TYPE, IDENTITY, U... > :: check (args, start, to, nits, c); } };  

template < e_type TYPE, e_css_property IDENTITY, e_css_val_fn T > struct value_fns < TYPE, IDENTITY, T >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c)
    {   PRESUME (c == T, __FILE__, __LINE__);
        return value_fn < TYPE, IDENTITY, T > :: check (args, start, to, nits); } };  
#endif // LIMITED_META_COMPLEXITY