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
#include "feedback/nitpick.h"
#include "type/type.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/value.h"

template < e_css_val_fn T > int split_fn_params (t_params& params, arguments& args, const int start, const int to, nitpick& nits)
{   int round = 0, p = start;
    bool spaced_out = false;
    css_token last = ct_error, prev = ct_error;
    for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i <= to)); ++i)
    {   switch (args.t_.at (i).t_)
        {   case ct_keyword :
            case ct_identifier :
            case ct_comment :
            case ct_number :
            case ct_string :
                break;
            case ct_whitespace :
                if ((round == 0) && in_list < T, cvf_colour, cvf_device_cmyk, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_oklab, cvf_oklch, cvf_rgb, cvf_rgba > :: yes ())
                    if (last != ct_whitespace)
                    {   add_param (args, params, p, i);
                        prev = last = ct_error; }
                    else if (spaced_out) nits.pick (nit_multiple_spaces, es_warning, ec_css, "multiple spaces between parameters");
                    else nits.pick (nit_multiple_spaces, es_warning, ec_css, PROG " presumes multiple spaces between parameters do not represent omitted arguments with default values");
                break;
            case ct_round_brac :
                ++round;
                break;
            case ct_round_ket :
                if (--round < 0)
                {   add_param (args, params, p, i);
                    prev = last = ct_error;
                    i = -1; }
                break;
            case ct_comma :
                if ((round == 0) && ! in_list < T, cvf_colour, cvf_device_cmyk, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_mix, cvf_oklab, cvf_oklch, cvf_rgba > :: yes ())
                    add_param (args, params, p, i);
                prev = last = ct_error;
                break;
            case ct_semicolon :
                if ((round == 0) && in_list < T, cvf_mix > :: yes ()) add_param (args, params, p, i);
                prev = last = ct_error;
                break;
            case ct_root :
            case ct_error :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                break;
            case ct_plus :
            case ct_dash :
                if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
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
                if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
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
                i = -1;
                break;
            default :
                if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
                    nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_));
                break; }
        prev = last;
        if ((i > 0) && ((to < 0) || (i < to)))
            last = args.t_.at (i).t_; }
    if (round > 1)
        nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": missing ')' after ", quote (args.t_.at (start).val_));
    return to; } 

template < e_type T > inline bool maybe_animatable (nitpick& nits)
{   if ((type_master < T > :: animation_type () != at_none) && (type_master < T > :: animation_type () != at_other)) return true;
    nits.pick (nit_css_value_fn, es_error, ec_css, "requires an animatable property");
    return false; }

template < > inline bool maybe_animatable < t_unknown > (nitpick& )
{   return true; }

template < e_type T > inline bool maybe_colour (nitpick& nits)
{   if (type_master < T > :: animation_type () == at_colour) return true;
    nits.pick (nit_css_value_fn, es_error, ec_css, "not a colour property");
    return false; }

template < > inline bool maybe_colour < t_unknown > (nitpick& )
{   return true; }

template < e_type TYPE > inline int check_typed_property (arguments& args, nitpick& nits, const int start, const int to)
{   nitpick nuts;
    ::std::string s;
    for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i <= to)); i = next_non_whitespace (args.t_, i, to))
        switch (args.t_.at (i).t_)
        {   case ct_number :
                s = assemble_unit (args.t_, i, to);
                if (! test_value < TYPE > (nuts, args.v_, s))
                    if (! type_master < TYPE > :: is_numeric ())
                    {   nitpick nets;
                        if ((! s.empty ()) && ((s.size () > 1) || (s.at (0) != '-')))
                            if (test_value < t_real > (nets, args.v_, s))
                            {   nits.merge (nets); break; }
                        i = first_non_whitespace (args.t_, i, to);
                        const int j = check_typed_identifier (args, nits, i, to, TYPE);
                        if (j > i) return j; }                   
                nits.merge (nuts);
                return to;
            case ct_keyword :
            case ct_identifier :
                s = assemble_string (args.t_, i, to, true);
                if (! test_value < TYPE > (nuts, args.v_, s))
                {   const int j = check_typed_identifier (args, nits, i, to, TYPE);
                    if (j > i) return j; }
                nits.merge (nuts);
                return to; 
            default :
                break; }
    return to; }

template < > inline int check_typed_property < t_css_var > (arguments& args, nitpick& nits, const int start, const int to)
{   if (examine_custom_property (args, nits, start, to)) return to;
    return start; }

template < > inline int check_typed_property < t_url > (arguments& args, nitpick& nits, const int start, const int to)
{   const int i = start;
    url u (nits, args.v_, assemble_string (args.t_, i, to, true));
    if (u.valid ()) return i;
    return start; }

template < > inline int check_typed_property < t_css_feature_annotation > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_annotation, "annotation"); }

template < > inline int check_typed_property < t_css_feature_character_variant > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_character_variant, "character-variant"); }

template < > inline int check_typed_property < t_css_feature_historical_forms > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_historical_forms, "historical-form"); }

template < > inline int check_typed_property < t_css_feature_ornaments > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_ornaments, "ornament"); }

template < > inline int check_typed_property < t_css_feature_styleset > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_styleset, "styleset"); }

template < > inline int check_typed_property < t_css_feature_stylistic > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_stylistic, "stylistic"); }

template < > inline int check_typed_property < t_css_feature_swash > (arguments& args, nitpick& nits, const int start, const int to)
{   return check_typed_feature (args, nits, start, to, css_swash, "swash"); }

template < e_type TYPE, e_css_val_fn T, e_type PARAM, int MAX >
    struct fancy_max
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n)
    {   check_typed_property < PARAM > (args, nits, p.at (n).first, p.at (n).second); 
        if (p.size () > stp (n))
            if ((p.size () != 5) || (! in_list < T, cvf_rgb > :: yes ())) // for the ****ic change of separators
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
    {   if (n < p.size ())
            fancy_max < TYPE, T, PARAM, MAX > :: check (args, nits, p, n);
        else if (n+1 < MIN) nits.pick (nit_css_value_param, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": parameter ", n+1, " missing or invalid"); } };

template < e_type TYPE, e_css_val_fn T, class A, class SZ, class B > struct fn_keyworded
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   const int maximum = (to >= 0) ? to : static_cast < int > (args.t_.size ());
        for (int i = 0; i < maximum; ++i)
            if ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier))
                if (compare_no_case (args.t_.at (i).val_, SZ::sz ()))
                {   if (i > 0) A :: check (args, 0, i-1, nits);
                    if (i < maximum - 1) B :: check (args, i+1, to, nits);
                    return to; }
        return A :: check (args, start, to, nits); } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type... PARAMS > struct value_fn
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   t_params params;
        const int res = split_fn_params < T > (params, args, start, to, nits);
        fn_params < TYPE, T, MIN, MAX, PARAMS... > :: check (args, nits, params);
        return res; } };

template < e_type TYPE, e_css_val_fn T > struct common_colour
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& ref)
    {   if (! maybe_colour < TYPE > (nits)) return start;
        if (args.v_.css_colour () < 5)
            return value_fn < TYPE, T, 3, 3, t_real, t_percent, t_percent > :: check (args, start, to, nits); 
        nitpick nuts, nets, nots;
        int i = value_fn < TYPE, T, 1, 5, t_real_n, t_percent_n, t_percent_n, t_slash, t_css_alpha_n > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, T, 2, 7, t_from, t_css_colour, t_real_n, t_percent_n, t_percent_n, t_slash, t_css_alpha_n > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, ref, es_error, ec_css, "invalid ", type_master < t_css_val_fn > :: name (T), " ()");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

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

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        if (args.v_.css_colour () < 5)
            return value_fn < TYPE, cvf_colour, 4, 4, t_css_rgb_xyz, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nits);
        nitpick nuts, nets, nots;
        int i = value_fn < TYPE, cvf_colour, 4, 6, t_css_rgb_xyz, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_colour, 5, 7, t_from, t_css_colour, t_css_rgb_xyz, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        i = value_fn < TYPE, cvf_colour, 1, 9, t_css_var, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nots);
        if (nots.worst () > es_error) { nits.merge (nots); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, "4. Specifying Custom Color Spaces: the color() Function", es_error, ec_css, "invalid color()");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets);
            nits.merge (nots); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_annotation >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_annotation, 1, 1, t_css_feature_annotation > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_character_variant >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_character_variant, 1, -1, t_css_feature_character_variant > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_circle >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_circle,
                                value_fn < TYPE, cvf_circle, 1, 1, t_css_shape_radius >,
                                sz_at,
                                value_fn < TYPE, cvf_circle, 1, 1, t_css_shape_position > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_colour_mix, 1, 3, t_css_colour_interpolation, t_css_colour_percent, t_css_colour_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_cubic_bezier >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_cubic_bezier, 4, 4, t_zero_to_one, t_real, t_zero_to_one, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_device_cmyk >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_device_cmyk, 4, 6, t_real_percent, t_real_percent, t_real_percent, t_real_percent, t_slash, t_css_alpha > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ease >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ease_in >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ease_in_out >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ease_out >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ellipse >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_ellipse,
                                value_fn < TYPE, cvf_ellipse, 2, 2, t_css_shape_radius >,
                                sz_at,
                                value_fn < TYPE, cvf_ellipse, 1, 1, t_css_shape_position > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_format >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_format, 1, 1, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_historical_forms >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_historical_forms, 1, 1, t_css_feature_historical_forms > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hsl >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_hsl > :: check (args, start, to, nits, "3.2. Relative HSL Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hsla >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_hsla, 4, 4, t_real, t_percent, t_percent, t_zero_to_one > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hwb >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_hwb > :: check (args, start, to, nits, "3.3. Relative HWB Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hypot >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_hypot, 1, -1, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_inset >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_lab,
                                value_fn < TYPE, cvf_lab, 1, 4, t_css_length >,
                                sz_round,
                                value_fn < TYPE, cvf_lab, 1, 1, t_css_border_radius > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_lab >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_lab > :: check (args, start, to, nits, "3.4. Relative Lab Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_lch >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_lch > :: check (args, start, to, nits, "3.6. Relative LCH Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_local >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_local, 1, 1, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_log >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_log, 1, 2, TYPE, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_linear >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

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
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_mix, 3, 3, t_percent, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_mod >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_mod, 2, 2, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_oklab >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_oklab > :: check (args, start, to, nits, "3.5. Relative OKLab Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_oklch >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_oklch > :: check (args, start, to, nits, "3.7. Relative OKLCH Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ornaments >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_ornaments, 1, 1, t_css_feature_ornaments > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_path >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_path, 1, 2, t_css_shape_fillrule, t_d > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_polygon >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_polygon, 1, 999, t_css_shape_fillrule, t_css_length > :: check (args, start, to, nits); } };

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

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rgb >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        if (args.v_.css_colour () < 5)
            return value_fn < TYPE, cvf_rgb, 3, 3, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nits); 
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_rgb, 3, 5, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_rgb, 5, 7, t_from, t_css_colour, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, "3.1. Relative sRGB Colors", es_error, ec_css, "invalid rgb");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rgba >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_rgba, 4, 4, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_zero_to_one > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rect >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_rect,
                                value_fn < TYPE, cvf_rect, 4, 4, t_css_length_a >,
                                sz_round,
                                value_fn < TYPE, cvf_rect, 1, 1, t_css_border_radius > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_src >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_src, 1, 2, t_url, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_step_end >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_step_start >
{   static int check (arguments& , const int , const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return to; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_steps >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_steps, 1, 2, t_integer, t_step_position > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_styleset >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_styleset, 1, -1, t_css_feature_styleset > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_stylistic >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_stylistic, 1, 1, t_css_feature_stylistic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_swash >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_swash, 1, 1, t_css_feature_swash > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_tech >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_tech, 1, -1, t_css_font_tech > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_url >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_url, 1, 2, t_url, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_var >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_var, 1, 2, t_css_var, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_xywh >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_xywh,
                                value_fn < TYPE, cvf_xywh, 2, 2, t_css_length >,
                                sz_round,
                                value_fn < TYPE, cvf_xywh, 1, 1, t_css_border_radius > > :: check (args, start, to, nits); } };

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
