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
#include "base/type_case.h"
#include "base/type_core.h"
#include "utility/quote.h"
#include "base/type_master.h"
#include "compound/type_some_of.h"
#include "compound/type_all_of.h"

template < class NAME > bool function_name (nitpick& nits, const html_version& v, const ::std::string& ss, ::std::string& p)
{   ::std::string::size_type brac = ss.find ('(');
    if (brac == ::std::string::npos)
        nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
    else
    {   ::std::string fn (trim_the_lot_off (ss.substr (0, brac)));
        if (! compare_complain (nits, v, NAME :: sz (), fn))
            nits.pick (nit_isnt, es_error, ec_type, quote (NAME :: sz ()), "() sought, not ", quote (fn));
        else
        {   ::std::string::size_type ket = ss.find (')');
            if (ket == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
            else
            {   ::std::string args (trim_the_lot_off (ss.substr (brac+1, ket-brac-1)));
                if (ket < ss.length () - 1)
                {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                    if (! post.empty ())
                    {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                        return false; } }
                p = args;
                return true; } } }
    return false; }

template < e_type T, class NAME, e_type... P > struct type_function_all : type_all_of < T, sz_comma, P... >
{   using type_all_of < T, sz_comma, P... > :: type_all_of;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string args;
        if (function_name < NAME > (nits, v, trim_the_lot_off (s), args))
        {   type_all_of < T, sz_comma, P... > :: set_value (nits, v, args);
            if (type_all_of < T, sz_comma, P... > :: good ())
                return; }
        type_all_of < T, sz_comma, P... > :: status (s_invalid); } };

template < e_type T, class NAME, int MIN, int MAX, e_type... P > struct type_function_some : type_some_of < T, sz_comma, MIN, MAX, P... >
{   using type_some_of < T, sz_comma, MIN, MAX, P... > :: type_some_of;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string args;
        if (function_name < NAME > (nits, v, trim_the_lot_off (s), args))
        {   type_some_of < T, sz_comma, MIN, MAX, P... > :: set_value (nits, v, args);
            if (type_some_of < T, sz_comma, MIN, MAX, P... > :: good ())
                return; }
        type_some_of < T, sz_comma, MIN, MAX, P... > :: status (s_invalid); } };

template < e_type T, class NAME, e_type P > struct type_function : type_function_all < T, NAME, P >
{   using type_function_all < T, NAME, P > :: type_function_all; };

template < e_type T, class NAME, e_type P, e_type Q > struct type_function_2_opt : type_function_some < T, NAME, 0, 2, P, Q >
{   using type_function_some < T, NAME, 0, 2, P, Q > :: type_function_some; };

template < e_type T, class NAME, e_type P, e_type Q, e_type R > struct type_function_3_opt : type_function_some < T, NAME, 0, 3, P, Q, R >
{   using type_function_some < T, NAME, 0, 3, P, Q, R > :: type_function_some; };
