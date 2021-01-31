/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_core.h"
#include "symbol/symbol.h"
#include "utility/quote.h"
#include "parser/parse_elements.h"
#include "main/args.h"

class element;

template < e_type TYPE > class type_master : public string_value < TYPE > { };

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    return t.good (); }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return type_master < T > :: default_value ();
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }

template < e_type T, class SZ > struct type_must_be : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (tidy_string < T > :: good ())
        {   if (compare_no_case (tidy_string < T > :: get_string (), SZ :: sz ())) return;
            nits.pick (nit_isnt, es_error, ec_type, quote (SZ :: sz ()), " expected"); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B > struct type_either_or : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss)) nits.merge (nuts);
            else if (test_value < B > (knots, v, ss)) nits.merge (knots);
            else
            {   nits.merge (nuts); nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, class SZ, e_type P > struct type_at_least_one : string_vector < T, SZ >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P > struct type_at_least_none : string_vector < T, SZ >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ > struct type_or_string : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_no_case (SZ :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss)) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2 > struct type_or_either_string : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_no_case (SZ1 :: sz (), ss) || compare_no_case (SZ2 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss)) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2, class SZ3 > struct type_or_any_string : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_no_case (SZ1 :: sz (), ss) || compare_no_case (SZ2 :: sz (), ss) || compare_no_case (SZ3 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss)) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type U, class SZ, e_type P > struct type_one_or_both : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            assert (SZ :: sz () != nullptr);
            ::std::string::size_type pos = ss.find (SZ :: sz ());
            if (pos != ::std::string::npos)
            {   if (! test_value < P > (nits, v, ss.substr (pos+1))) tidy_string < T > :: status (s_invalid);
                ss = ss.substr (0, pos); }
            if (test_value < U > (nits, v, ss)) return; }
        tidy_string < T > :: status (s_invalid); } };

