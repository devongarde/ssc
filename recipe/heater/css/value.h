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

int check_typed_identifier (arguments& args, nitpick& nits, const int start, const int to, const e_type t);
int split_fn_params (t_params& params, arguments& args, const int start, const int to, nitpick& nits, const bool semi, const ::std::string& name);
bool maybe_math (nitpick& nits, const e_css_property id);

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
        if (p.size () > n+1)
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
