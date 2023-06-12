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
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/value.h"


void add_param (const arguments& args, t_params& params, int& from, const int i)
{   params.emplace_back (from, i-1);
    from = next_non_whitespace (args.t_, i, -1); }

/*
int round = 0, p = start;
        css_token last = ct_error, prev = ct_error;
        t_params params;
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
                    if (round == 0)
                        fn_separator < T > :: comma (args, params, p, i);
                    prev = last = ct_error;
                    break;
                case ct_semicolon :
                    if (round == 0)
                        fn_separator < T > :: semicolon (args, params, p, i);
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
                                        type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (prev)), " ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
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
                                type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                            prev = last = ct_error;
                            break;
                        default :
                            break; }
                    break;
                case ct_eof :
                    return -1;
                default :
                    nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                    break; }
            prev = last;
            if ((i > 0) && ((to < 0) || (i < to)))
                last = args.t_.at (i).t_; }
        fn_params < TYPE, IDENTITY, T, MIN, MAX, PARAMS... > :: check (args, nits, params);
        if (round > 0)
            nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": missing ')' after ", quote (args.t_.at (start).val_));
        return to; } };
*/

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

template < e_type TYPE, e_type... TYPES > struct property_by_type : public property_by_type < TYPES... >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, e_type e)
    {   if (e != TYPE) return property_by_type < TYPES... > :: check (args, start, to, nits, e);
        int i = start;
        if (typed_property < TYPE, ec_unknown > :: check_fn (args, i, to, nits)) return i;
        return start; } };

template < e_type TYPE > struct property_by_type < TYPE >
{   static int check (arguments& , const int , const int , nitpick& , e_type )
    {   GRACEFUL_CRASH ( __FILE__, __LINE__); } };

int check_typed_identifier (arguments& args, nitpick& nits, const int start, const int to, const e_type t)
{   PRESUME ((args.t_.at (start).t_ == ct_keyword) || (args.t_.at (start).t_ == ct_identifier), __FILE__, __LINE__);
#ifdef LIMITED_META_COMPLEXITY
    if (t <= SSC_TYPE_1_MAX) return property_by_type < SSC_TYPES_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_2_MAX) return property_by_type < SSC_TYPES_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_3_MAX) return property_by_type < SSC_TYPES_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_4_MAX) return property_by_type < SSC_TYPES_4, t_unknown > :: check (args, start, to, nits, t);
    return property_by_type < SSC_TYPES_5, t_unknown > :: check (args, start, to, nits, t); }
#else // LIMITED_META_COMPLEXITY
    return property_by_type < SSC_TYPES_1, SSC_TYPES_2, SSC_TYPES_3, SSC_TYPES_4, SSC_TYPES_5, t_unknown > :: check (args, start, to, nits, t); }
#endif // LIMITED_META_COMPLEXITY 
