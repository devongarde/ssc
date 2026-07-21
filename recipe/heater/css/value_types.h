/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
{   int round = 0, square = 0, p = start;
    e_token last = ct_error, prev = ct_error;
    ::std::string k;
    for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i <= to)); ++i)
    {   switch (args.t_.at (i).t_)
        {   case ct_keyword :
            case ct_identifier :
            case ct_comment :
            case ct_number :
            case ct_string :
            case ct_dot :
                break;
            case ct_whitespace :
                if ((round == 0) && (square == 0) && in_list < T, cvf_colour, cvf_device_cmyk, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_oklab, cvf_oklch, cvf_rect, cvf_repeat, cvf_rgb, cvf_rgba, cvf_xywh > :: yes ())
                    if (last != ct_whitespace)
                    {   add_param (args, params, p, i);
                        prev = last = ct_error; }
                    else nits.pick (nit_multiple_spaces, es_warning, ec_css, PROG " presumes multiple spaces between parameters do not represent omitted arguments with default values");
                break;
            case ct_lt :
                break;
            case ct_bar :
            case ct_gt :
            case ct_hash :
                if (! in_list < T, cvf_type, cvf_attr, cvf_media, cvf_if > :: yes ())
                {   nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_), "(1a)");
                    prev = last = ct_error; }
                break;
            case ct_eq :
                if (! in_list < T, cvf_media, cvf_if > :: yes ())
                {   nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_), "(1b)");
                    prev = last = ct_error; }
                break;
            case ct_square_brac :
                if (in_list < T, cvf_repeat > :: yes ()) ++square;
                else if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
                    nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected '[' when checking ", quote (args.t_.at (start).val_), "(4)");
                break;
            case ct_square_ket :
                if (in_list < T, cvf_repeat > :: yes ())
                {   if (--square < 0)
                    {   add_param (args, params, p, i+1);
//                    {   add_param (args, params, p, i);
                        prev = last = ct_error;
                        i = -1; } }
                else if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
                    nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ']' when checking ", quote (args.t_.at (start).val_), "(4)");
                break;
            case ct_round_brac :
                ++round;
                break;
            case ct_round_ket :
                if (--round < 0)
//                {   add_param (args, params, p, i+1);
                {   add_param (args, params, p, i);
                    prev = last = ct_error;
                    i = -1; }
                break;
            case ct_comma :
                if ((round == 0) && (square == 0) && ! in_list < T, cvf_if, cvf_mix > :: yes ())
                {   if (in_list < T, cvf_colour, cvf_device_cmyk, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_oklab, cvf_oklch, cvf_path, cvf_rect, cvf_rgba, cvf_xywh > :: yes ())
                        nits.pick (nit_css_value_fn, ed_mdn, "CSS Reference", es_comment, ec_css, type_master < t_css_val_fn > :: name (T), ": separate arguments with spaces, not commas");
                    add_param (args, params, p, i); }
                prev = last = ct_error;
                break;
            case ct_semicolon :
                if ((round == 0) && (square == 0) && in_list < T, cvf_mix, cvf_if > :: yes ()) add_param (args, params, p, i);
                prev = last = ct_error;
                break;
            case ct_root :
            case ct_error :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                break;
            case ct_plus :
            case ct_dash :
                if ((square == 0) && ! in_list < T, cvf_format, cvf_local, cvf_url, cvf_type, cvf_attr > :: yes ())
                    switch (last)
                    {   case ct_plus :
                        case ct_dash :
                            switch (prev)
                            {   case ct_plus :
                                case ct_dash :
                                case ct_slash :
                                case ct_splat :
                                    nits.pick (nit_css_value_fn, es_error, ec_css,
                                        type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (prev)), " ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_), "(2)");
                                    prev = last = ct_error;
                                    break;
                                default :
                                    break; }
                            break;
                        default :
                            break; }
                break;
            case ct_slash :
                if ((square == 0) && ! in_list < T, cvf_format, cvf_local, cvf_url, cvf_type, cvf_attr, cvf_rgb > :: yes ())
                    switch (last)
                    {   case ct_plus :
                        case ct_dash :
                        case ct_slash :
                        case ct_splat :
                            nits.pick (nit_css_value_fn, es_error, ec_css,
                                type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (tkn_rpt (args.t_.at (start))), "(3a)");
                            prev = last = ct_error;
                            break;
                        default :
                            break; }
                break;
            case ct_splat :
                if ((square == 0) && ! in_list < T, cvf_format, cvf_local, cvf_url, cvf_type, cvf_attr > :: yes ())
                    switch (last)
                    {   case ct_plus :
                        case ct_dash :
                        case ct_slash :
                        case ct_splat :
                            nits.pick (nit_css_value_fn, es_error, ec_css,
                                type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (last)), " ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (tkn_rpt (args.t_.at (start))), "(3b)");
                            prev = last = ct_error;
                            break;
                        default :
                            break; }
                break;
            case ct_eof :
                i = -1;
                break;
            case ct_colon :
                if (in_list < T, cvf_if, cvf_style, cvf_supports, cvf_media > :: yes ()) break;
                FALLTHROUGH;
            default :
                if (! in_list < T, cvf_format, cvf_local, cvf_url > :: yes ())
                    nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": unexpected ", quote (tkn_rpt (args.t_.at (i))), " when checking ", quote (args.t_.at (start).val_), "(4)");
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

template < e_type T > inline bool maybe_colour (nitpick& nits, const int n = 0)
{   if ((type_master < T > :: animation_type () == at_paint ) || (type_master < T > :: animation_type () == at_colour)) return true;
    if (type_master < T > :: is_colourful ()) return true;
    nits.pick (nit_css_value_fn, es_error, ec_css, "not a colour property (", n, ")");
    return false; }

template < > inline bool maybe_colour < t_unknown > (nitpick& , const int )
{   return true; }

template < e_type TYPE > inline int check_typed_property (arguments& args, nitpick& nits, const int start, const int to)
{   nitpick nuts;
    ::std::string s;
    for (int i = first_non_whitespace (args.t_, start, to); (i > 0) && ((to < 0) || (i <= to)); i = next_non_whitespace (args.t_, i, to))
        switch (args.t_.at (i).t_)
        {   case ct_number :
                s = assemble_unit (args.t_, i, to);
                if (! test_value < TYPE > (nuts, args.v_, s, args.get_document ()))
                    if (! type_master < TYPE > :: is_numeric ())
                    {   nitpick nets;
                        if ((! s.empty ()) && ((s.size () > 1) || (s.at (0) != '-')))
                            if (test_value < t_real > (nets, args.v_, s, args.get_document ()))
                            {   nits.merge (nets); break; }
                        i = first_non_whitespace (args.t_, i, to);
                        const int j = check_typed_identifier (args, nits, i, to, TYPE);
                        if (j > i) return j; }
                nits.merge (nuts);
                return to;
            case ct_lt :
            case ct_identifier :
            case ct_keyword :
                s = assemble_string (args.t_, i, to, true);
                if (! test_value < TYPE > (nuts, args.v_, s, args.get_document ()))
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

template < e_type TYPE, e_css_val_fn T, e_type PARAM, int MAX > struct fancy_max
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n)
    {   check_typed_property < PARAM > (args, nits, p.at (n).first, p.at (n).second); 
        if ((p.size () > stp (n)) && (p.size () > MAX))
            if ((p.size () != 5) || (! in_list < T, cvf_rgb > :: yes ())) // for the ****ic change of separators
                nits.pick (nit_css_value_param, es_error, ec_css, "too many parameters for ", type_master < t_css_val_fn > :: name (T)); } };

template < e_type TYPE, e_css_val_fn T, e_type PARAM > struct fancy_max < TYPE, T, PARAM, -1 >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n)
    {   for (unsigned x = n; x < p.size (); ++x)
            check_typed_property < PARAM > (args, nits, p.at (x).first, p.at (x).second); } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type PARAM, e_type... PARAMS >
    struct fn_params : public fn_params < TYPE, T, MIN, MAX, PARAMS... >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n = 0)
    {   if (n >= p.size ())
        {   if (n+1 < MIN) nits.pick (nit_css_value_param, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": parameters ", n+1, " onwards missing or invalid (", p.size (), ")"); }
        else
        {   check_typed_property < PARAM > (args, nits, p.at (n).first, p.at (n).second);
            fn_params < TYPE, T, MIN, MAX, PARAMS... > :: check (args, nits, p, n+1); } } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type PARAM > struct fn_params < TYPE, T, MIN, MAX, PARAM >
{   static void check (arguments& args, nitpick& nits, const t_params& p, const unsigned n = 0)
    {   if (n < p.size ())
            fancy_max < TYPE, T, PARAM, MAX > :: check (args, nits, p, n);
        else if (n+1 < MIN) nits.pick (nit_css_value_param, es_error, ec_css, type_master < t_css_val_fn > :: name (T), ": parameter ", n+1, " missing or invalid (", p.size (), ")"); } };

template < e_type TYPE, e_css_val_fn T, class A, class SZ, class B > struct fn_keyworded
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   const int maximum = (to >= 0) ? to : GSL_NARROW_CAST < int > (args.t_.size ());
        for (int i = start; i < maximum; ++i)
            if ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier))
                if (compare_no_case (args.t_.at (i).val_, SZ::sz ()))
                {   if (i > 0) A :: check (args, start, i-1, nits);
                    if (i < maximum - 1) B :: check (args, i+1, to, nits);
                    return to; }
        return A :: check (args, start, to, nits); } };

template < e_type TYPE, e_css_val_fn T, int MIN, int MAX, e_type... PARAMS > struct value_fn
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   t_params params;
        const int res = split_fn_params < T > (params, args, start, to, nits);
        fn_params < TYPE, T, MIN, MAX, PARAMS... > :: check (args, nits, params);
        return res; } };

template < e_type TYPE, e_css_val_fn T, e_type... PARAMS > struct value_fn_one
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   t_params params;
        const int res = split_fn_params < T > (params, args, start, to, nits);
        fn_params < TYPE, T, 1, 1, PARAMS... > :: check (args, nits, params);
        return res; } };

template < e_type TYPE, e_css_val_fn T, e_type... PARAMS > struct value_fn_one_or_more
{   static int check (arguments& args, const int start, const int to, nitpick& nits)
    {   t_params params;
        const int res = split_fn_params < T > (params, args, start, to, nits);
        fn_params < TYPE, T, 1, -1, PARAMS... > :: check (args, nits, params);
        return res; } };

template < e_type TYPE, e_css_val_fn T > struct common_colour
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& ref)
    {   if (! maybe_colour < TYPE > (nits, 1)) return start;
        if (args.v_.css_module (c_colour) < 5)
            return value_fn < TYPE, T, 3, 4, t_real, t_percent, t_percent, t_css_alpha_n > :: check (args, start, to, nits); 
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
        return value_fn_one < TYPE, T, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_none >
{   static int check (arguments& , const int , const int , nitpick& , const e_css_property )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_clamp >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_clamp, 3, 3, TYPE, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_abs >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_abs, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_annotation >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_annotation, t_css_feature_annotation > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_acos >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_acos, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_asin >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_asin, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_atan >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_atan, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_atan2 >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_atan2, 2, 2, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_attr >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   nitpick gnats, nuts;
        int i = value_fn < TYPE, cvf_attr, 2, 2, t_attr_unit, t_attr > :: check (args, start, to, gnats);
        if (gnats.worst () > es_error) { nits.merge (gnats); return i; }
        i = value_fn < TYPE, cvf_attr, 1, 2, t_css_attr_type, t_generic > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "attr ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (gnats);
            nits.merge (nuts); }
        return i; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_auto >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_text_4 (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_auto, t_lang > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_blur >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_blur, 0, 1, t_css_length_abs > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_brightness >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_brightness, 0, 1, t_real_perflex > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_calc >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_calc, 0, 1, t_css_fn_calc_args > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_calc_size >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_calc_size, 2, 2, t_css_calc_size_fn, t_css_length_size > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_character_variant >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_character_variant, 1, -1, t_css_feature_character_variant > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_circle >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_circle,
                                value_fn_one < TYPE, cvf_circle, t_css_shape_radius >,
                                sz_at,
                                value_fn_one < TYPE, cvf_circle, t_css_shape_position > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 2)) return -1;
        if (args.v_.css_module (c_colour) < 5)
            return value_fn < TYPE, cvf_colour, 4, 4, t_css_rgb_xyz, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nits);
        nitpick nuts, nets, nots;
        int i = value_fn < TYPE, cvf_colour, 4, 6, t_css_rgb_xyz, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_colour, 6, 8, t_from, t_css_col, t_css_rgb_xyz, t_real_percent_n_rx, t_real_percent_n_gy, t_real_percent_n_bz, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        i = value_fn < TYPE, cvf_colour, 1, 9, t_css_var, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nots);
        if (nots.worst () > es_error) { nits.merge (nots); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, "4. Specifying Custom Color Spaces: the color() Function", es_error, ec_css, "invalid color()"); // dialect
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets);
            nits.merge (nots); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour_layers >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn_one_or_more < TYPE, cvf_colour_layers, t_css_blend_colour > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_colour_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_colour_mix, 1, 3, t_css_colour_interpolation, t_css_colour_percent, t_css_colour_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_conic_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_conic_gradient, t_conic_2, t_css_angular_colour_stop_list > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_contrast >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_contrast, 0, 1, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_contrast_colour >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits)) return -1;
        return value_fn_one_or_more < TYPE, cvf_contrast_colour, t_css_target_contrast, t_css_colour_4 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_content >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_content, t_abfmt > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_cos >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_cos, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_counter >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_counter, 2, 2, t_css_content_name, t_css_counter_ss > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_counters >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_counters, 2, 3, t_css_content_name, t_text, t_css_counter_ss > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_cross_fade >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_cross_fade, t_css_cross_fade > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_cubic_bezier >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_cubic_bezier, 4, 4, t_zero_to_one, t_real, t_zero_to_one, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_custom >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_custom, 1, 5, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_device_cmyk >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 3)) return -1;
        return value_fn < TYPE, cvf_device_cmyk, 4, 6, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_double_rainbow >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn < TYPE, cvf_double_rainbow, 1, 2, t_position, t_css_double_rainbow > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_drop_shadow >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        nitpick gnats, nuts;
        int i = value_fn < TYPE, cvf_drop_shadow, 2, 3, t_css_col, t_css_length > :: check (args, start, to, gnats);
        if (gnats.worst () > es_error) { nits.merge (gnats); return i; }
        i = value_fn < TYPE, cvf_drop_shadow, 1, 3, t_css_length, t_css_length, t_css_col > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "drop-shadow ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (gnats);
            nits.merge (nuts); }
        return i; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_dynamic_range_limit_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_dynamic_range_limit_mix, 1, 3, t_conic_2, t_css_angular_colour_stop_list > :: check (args, start, to, nits); } };

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

template < e_type TYPE > struct value_fn_params < TYPE, cvf_element >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_element, t_text > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ellipse >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_ellipse,
                                value_fn_one < TYPE, cvf_ellipse, t_css_shape_ellipse >,
                                sz_at,
                                value_fn_one < TYPE, cvf_ellipse, t_css_shape_position > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_env >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_env, 1, 2, t_css_env_vars, t_text > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_exp >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_exp, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_fade >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_text_overflow (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_fade, t_css_length > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_filter >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        nitpick gnats, nuts;
        int i = value_fn < TYPE, cvf_filter, 1, 999, t_css_fn_trans_args > :: check (args, start, to, gnats);
        if (i >= 0) { nits.merge (gnats); return i; }
        i = value_fn < TYPE, cvf_filter, 2, 999, t_css_image, t_css_fn_trans_args > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "filter ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (gnats);
            nits.merge (nuts); }
        return i; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_format >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_format, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_greyscale >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_greyscale, 0, 1, t_real_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_historical_forms >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_historical_forms,  t_css_feature_historical_forms > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hsl >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 4)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_hsl, 3, 5, t_real_angle_n, t_percent_n, t_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_hsl, 5, 7, t_from, t_css_col, t_real_angle_h, t_percent_s, t_percent_l, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "hsl ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        ::std::cout << nuts.worst () << ":" << nuts.size () << ", " << nets.worst () << ":" << nets.size () << "\n";
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hsla >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return common_colour < TYPE, cvf_hsla > :: check (args, start, to, nits, "3.2. Relative HSL Colors"); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hue_rotate >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_hue_rotate, 0, 1, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hwb >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 5)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_hwb, 3, 5, t_real_angle_n, t_percent_n, t_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_hwb, 5, 7, t_from, t_css_col, t_real_angle_h, t_percent_w, t_percent_b, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "hwb ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_hypot >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_hypot, 1, 999, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_if >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_if, t_css_if > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_image >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_image, t_css_image > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_image_set >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_image_set, t_css_image_set > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_inset >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return fn_keyworded <   TYPE, cvf_lab,
                                value_fn < TYPE, cvf_lab, 1, 4, t_css_length >,
                                sz_round,
                                value_fn_one < TYPE, cvf_lab, t_css_border_radius > > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_invert >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_invert, 0, 1, t_real_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_lab >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 6)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_lab, 3, 5, t_real_percent_100, t_real_percent_125, t_real_percent_125, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_lab, 5, 7, t_from, t_css_col, t_real_percent_n_L, t_real_percent_n_a, t_real_percent_n_b125, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "lab ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_lch >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 7)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_lch, 3, 5, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_lch, 5, 7, t_from, t_css_col, t_real_percent_n_l, t_real_percent_n_c, t_real_percent_n_h, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "lch ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_leader >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_leader, t_dsss > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_light_dark >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_light_dark, 2, 2, t_css_colour_ld > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_local >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_local, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_log >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_log, 1, 2, t_real, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_linear >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_linear, 2, -1, t_real_percents > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_linear_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_linear_gradient, t_angle_lrtb_col, t_css_colour_stop_list > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_matrix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn < TYPE, cvf_matrix, 1, 6, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_matrix3d >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn < TYPE, cvf_matrix3d, 1, 16, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_max >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_max, 2, -1, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_min >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_min, 2, -1, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_minmax >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_minmax, 2, 2, t_css_length_minmax > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_mix >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_animatable < TYPE > (nits)) return -1;
        return value_fn < TYPE, cvf_mix, 3, 3, t_percent, TYPE, TYPE > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_mod >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_mod, 2, 2, t_css_calc_value, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_moz_image_rect >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_moz_image_rect, 5, 5, t_url, t_css_length_a, t_css_length_a, t_css_length_a, t_css_length_a > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_oklab >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 6)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_oklab, 3, 5, t_real_percent_100, t_real_percent_04, t_real_percent_04, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_oklab, 5, 7, t_from, t_css_col, t_real_percent_n_L, t_real_percent_n_a04, t_real_percent_n_b04, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "lab ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_oklch >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 7)) return -1;
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_oklch, 3, 5, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_oklch, 5, 7, t_from, t_css_col, t_real_percent_n_l, t_real_percent_n_c, t_real_percent_n_h, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "lch ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_opacity >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_opacity, 0, 1, t_real_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ornaments >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_ornaments, t_css_feature_ornaments > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_paint >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_paint, t_css_worklet, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_param >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_param, 1, 2, t_generic, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_path >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (maybe_offset_path (nits, id))  return value_fn_one < TYPE, cvf_path, t_d > :: check (args, start, to, nits);
        return value_fn_one < TYPE, cvf_path, t_css_fn_path_args > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_perspective >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_perspective, t_css_length_n > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_pointer >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_pointer, t_css_pointer_args > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_polygon >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_polygon, 1, 999, t_css_length_2 > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_polygon, 1, 999, t_css_shape_fillrule, t_css_length_2 > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "polygon ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_pow >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_pow, 2, 2, t_real, t_real > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_progress >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_progress, 3, 3, t_css_calc_value, t_css_calc_value, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_radial_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_radial_gradient, t_radial_4 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_ray >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_offset_path (nits, id)) return -1;
        return value_fn < TYPE, cvf_ray, 2, 3, t_angle, t_css_ray_size, t_contain > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_repeating_conic_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_repeating_conic_gradient, t_conic_2, t_css_angular_colour_stop_list > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_repeating_linear_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_repeating_linear_gradient, t_angle_lrtb, t_css_colour_stop_list > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_repeating_radial_gradient >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_repeating_radial_gradient, t_radial_4 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rem >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        return value_fn < TYPE, cvf_rem, 2, 2, t_css_calc_value, t_css_calc_value > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_repeat >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   nitpick nuts;
        if (maybe_grid (nuts, id, CF_REPEAT_GRID)) return value_fn_one_or_more < TYPE, cvf_repeat, t_integer_1_up_inf_aa, t_css_track_list > :: check (args, start, to, nits);
        if (maybe_gap (nuts, id, CF_REPEAT_COLOUR)) return value_fn_one_or_more < TYPE, cvf_repeat, t_integer_1_up_inf_a, t_css_border_wsc > :: check (args, start, to, nits);
        if (maybe_gap (nuts, id, CF_REPEAT_STYLE)) return value_fn_one_or_more < TYPE, cvf_repeat, t_integer_1_up_inf_a, t_css_border_style > :: check (args, start, to, nits);
        if (maybe_gap (nuts, id, CF_REPEAT_WIDTH)) return value_fn_one_or_more < TYPE, cvf_repeat, t_integer_1_up_inf_a, t_css_length_inf_mtt > :: check (args, start, to, nits);
        nits.merge (nuts);
        return -1; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_round >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_math (nits, id)) return -1;
        nitpick gnats, nuts;
        int i = value_fn < TYPE, cvf_round, 2, 3, t_css_fn_round_t, t_css_calc_value, t_css_calc_value > :: check (args, start, to, gnats);
        if (gnats.worst () > es_error) { nits.merge (gnats); return i; }
        i = value_fn < TYPE, cvf_round, 1, 2, t_css_calc_value, t_css_calc_value > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        nits.pick (nit_css_value_fn, ed_mdn, "round ()", es_error, ec_css, "invalid");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (gnats);
            nits.merge (nuts); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rgb >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 8)) return -1;
        if (args.v_.css_module (c_colour) < 5)
            return value_fn < TYPE, cvf_rgb, 3, 3, t_real_percent_n, t_real_percent_n, t_real_percent_n > :: check (args, start, to, nits); 
        nitpick nuts, nets;
        int i = value_fn < TYPE, cvf_rgb, 3, 5, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_css_alpha > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        i = value_fn < TYPE, cvf_rgb, 5, 7, t_from, t_css_col, t_real_percent_n_r, t_real_percent_n_g, t_real_percent_n_b, t_slash, t_css_alpha > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, "3.1. Relative sRGB Colors", es_error, ec_css, "invalid rgb");
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rgba >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (! maybe_colour < TYPE > (nits, 9)) return -1;
        nitpick nuts;
        const int i = value_fn < TYPE, cvf_rgba, 5, 5, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_slash, t_real_percent_n > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nuts); return i; }
        return value_fn < TYPE, cvf_rgba, 4, 4, t_real_percent_n, t_real_percent_n, t_real_percent_n, t_zero_to_one > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_anchor >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_anchor (nits, id)) return -1;
        return value_fn < TYPE, cvf_anchor, 1, 2, t_css_anchor, t_css_length_n > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_anchor_size >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_anchor_size (nits, id)) return -1;
        return value_fn < TYPE, cvf_anchor_size, 0, 2, t_css_anchored, t_css_length_n > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rect >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   nitpick nuts, nets, nots, gnats;
        int i = value_fn < TYPE, cvf_rect, 4, 15,
            t_css_length_a, t_css_length_a, t_css_length_a, t_css_length_a,
            t_round, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_slash,
            t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf > :: check (args, start, to, nets);
        if (nets.worst () > es_error) { nits.merge (nets); return i; }
        i = value_fn < TYPE, cvf_rect, 4, 11,
            t_css_length_a, t_css_length_a, t_css_length_a, t_css_length_a,
            t_round, t_css_length_percent_inf, t_slash,
            t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf > :: check (args, start, to, nuts);
        if (nuts.worst () > es_error) { nits.merge (nets); return i; }
        i = value_fn < TYPE, cvf_rect, 5, 10, t_round, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf,
            t_slash, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf > :: check (args, start, to, nots);
        if (nots.worst () > es_error) { nits.merge (nots); return i; }
        i = value_fn < TYPE, cvf_rect, 4, 7, t_round, t_css_length_percent_inf, 
            t_slash, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf, t_css_length_percent_inf > :: check (args, start, to, gnats);
        if (gnats.worst () > es_error) { nits.merge (gnats); return i; }
        nits.pick (nit_css_value_fn, ed_css_colour_5, "3.1. Relative sRGB Colors", es_error, ec_css, "invalid rgb");
        {   nits.merge (nets);
            nits.merge (nuts);
            nits.merge (nots);
            nits.merge (gnats); }
        return start; } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rotate >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_rotate, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rotate3d >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn < TYPE, cvf_rotate3d, 1, 4, t_real, t_real, t_real, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rotatex >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn_one < TYPE, cvf_rotatex, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rotatey >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn_one < TYPE, cvf_rotatey, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_rotatez >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn_one < TYPE, cvf_rotatez, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_saturate >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_saturate, 0, 1, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_scale >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        if (context.css_module (c_transform) == 3) return value_fn < TYPE, cvf_scale, 1, 2, t_real > :: check (args, start, to, nits);
        return value_fn < TYPE, cvf_scale, 1, 2, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_scale3d >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn < TYPE, cvf_scale3d, 1, 3, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_scalex >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        if (context.css_module (c_transform) == 3) return value_fn_one < TYPE, cvf_scalex, t_real > :: check (args, start, to, nits);
        return value_fn_one < TYPE, cvf_scalex, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_scaley >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        if (context.css_module (c_transform) == 3) return value_fn_one < TYPE, cvf_scaley, t_real > :: check (args, start, to, nits);
        return value_fn_one < TYPE, cvf_scaley, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_scalez >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn_one < TYPE, cvf_scalez, t_real_percentish > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_sepia >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_filter (nits, id)) return -1;
        return value_fn < TYPE, cvf_sepia, 0, 1, t_real_percent > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_shape >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_shape, t_conic_2, t_css_angular_colour_stop_list > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_sin >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_sin, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_skew >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn < TYPE, cvf_skew, 1, 2, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_skewx >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_skewx, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_skewy >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_skewy, t_angle_0 > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_snap_block >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_float (nits, id)) return -1;
        return value_fn < TYPE, cvf_snap_block, 1, 2, t_css_length, t_ens > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_snap_inline >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_float (nits, id)) return -1;
        return value_fn < TYPE, cvf_snap_inline, 1, 2, t_css_length, t_lnr > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_sqrt >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_sqrt, t_css_length_real > :: check (args, start, to, nits); } };

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
        return value_fn < TYPE, cvf_steps, 1, 2, t_unsigned, t_step_position > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_string >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_string, 1, 2, t_css_content_name, t_ffls > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_stripes >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_image (nits, id)) return -1;
        return value_fn_one_or_more < TYPE, cvf_stripes, t_stripe > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_styleset >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_styleset, t_css_feature_styleset > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_stylistic >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_stylistic, t_css_feature_stylistic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_superellipse >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_corner (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_superellipse, t_real_infinity > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_swash >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_swash, t_css_feature_swash > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_tan >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_tan, t_css_angle > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_target_counter >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_target_counter, 2, 3, t_urifn_str, t_css_content_name, t_css_counter_style > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_target_counters >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_target_counters, 3, 4, t_urifn_str, t_css_content_name, t_text, t_css_counter_style > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_target_text >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_content (nits, id)) return -1;
        return value_fn < TYPE, cvf_target_text, 2, 2, t_urifn_str, t_abcfl > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_tech >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_tech, t_css_font_tech > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_translate >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn < TYPE, cvf_translate, 1, 2, t_css_length > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_translate3d >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn < TYPE, cvf_translate3d, 1, 3, t_css_length, t_css_length, t_css_length_abs > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_translatex >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_translatex, t_css_length > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_translatey >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id)) return -1;
        return value_fn_one < TYPE, cvf_translatey, t_css_length > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_translatez >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property id)
    {   if (! maybe_transform (nits, id, true)) return -1;
        return value_fn_one < TYPE, cvf_translatez, t_css_length_abs > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_type >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one_or_more < TYPE, cvf_type, t_css_fn_type_args > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_url >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_url, 1, 2, t_url, t_css_fn_param > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_url_pattern >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn_one < TYPE, cvf_url_pattern, t_text > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_var >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   return value_fn < TYPE, cvf_var, 1, 2, t_css_var, t_generic > :: check (args, start, to, nits); } };

template < e_type TYPE > struct value_fn_params < TYPE, cvf_xywh >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_property )
    {   if (args.v_ >= html_dec25)
            return fn_keyworded <   TYPE, cvf_xywh,
                                    value_fn < TYPE, cvf_xywh, 4, 4, t_css_length_percent, t_css_length_percent, t_css_length_inf, t_css_length_inf >,
                                    sz_round,
                                    value_fn < TYPE, cvf_xywh, 1, 4, t_css_length_inf > > :: check (args, start, to, nits);
        else return fn_keyworded <  TYPE, cvf_xywh,
                                    value_fn < TYPE, cvf_xywh, 2, 2, t_css_length >,
                                    sz_round,
                                    value_fn_one < TYPE, cvf_xywh, t_css_border_radius > > :: check (args, start, to, nits); } };

template < e_type TYPE, e_css_val_fn T, e_css_val_fn ... U > struct value_fns : public value_fns < TYPE, U... >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c, const e_css_property id)
    {   if (c != T) return value_fns < TYPE, U... > :: check (args, start, to, nits, c, id);
        args.use (cic_fn_name, type_master < t_css_val_fn > :: name (c));
        return value_fn_params < TYPE, T > :: check (args, start, to, nits, id); } };  

template < e_type TYPE, e_css_val_fn T > struct value_fns < TYPE, T >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c, const e_css_property id)
    {   PRESUME (c == T, __FILE__, __LINE__);
        return value_fn_params < TYPE, T > :: check (args, start, to, nits, id); } };  

template < e_type T, e_type... TS > struct value_types : public value_types < TS... >
{   static int check (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
    {   if (t != T) return value_types < TS... > :: check (args, start, to, nits, t, fn, id);
        return value_fns < T, CSS_VAL_FN > :: check (args, start, to, nits, fn, id); } };

template < e_type T > struct value_types < T >
{   static int check (arguments& , int& , const int to, nitpick& , const e_type , const e_css_val_fn , const e_css_property )
    {   return to; } };
