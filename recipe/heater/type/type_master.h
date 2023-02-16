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
#include "type/type_case.h"
#include "type/type_core.h"
#include "utility/quote.h"
#include "parser/parse_elements.h"
#include "main/args.h"

class element;

bool test_many (const vtype_t& vty, nitpick& nits, const html_version& v, const vstr_t& vs);

template < e_type T, bool B > struct null_string_ok
{   static bool test_value (nitpick& , const ::std::string& s) { return s.empty (); } }; 

template < e_type T > struct null_string_ok < T, false >
{   static bool test_value (nitpick& nits, const ::std::string& s)
    {   if (s.empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        return false; } };

template < e_type TYPE > struct type_master : public string_value < TYPE >
{   using string_value < TYPE > :: string_value; };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440) // By the same logic: dalmations are dogs, dalmations have spots, therefore all dogs have spots.
#endif // _MSC_VER
template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    return t.good (); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& id)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return false;
    id = t.get_id ();
    return true; }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return static_cast < typename type_master < T > :: value_type > (type_master < T > :: default_value ());
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }

template < e_type T > e_animation_type grab_animation_type () noexcept
{   type_master < T > t;
    return t.animation_type (); }

template < e_type T, class SZ > struct type_string : public tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, quote (SZ::sz ()), " expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   if (compare_no_case (tidy_string < T > :: get_string (), SZ::sz ())) return;
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (SZ::sz ()), " expected"); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ > struct string_then_type : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void accumulate (stats_t* s) const
    {   if (tidy_string < T > :: good ()) type_master < P > :: accumulate (s, tidy_string < T > :: get_string ()); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            const ::std::size_t len = strlen (SZ :: sz ());
            if (! compare_complain (nits, v, SZ :: sz (), ss.substr (0, len)))
                nits.pick (nit_syntax, es_error, ec_type, "here, ", quote (ss), " should start with ", quote (SZ :: sz ()));
            nitpick nuts;
            if (test_value < P > (nuts, v, ss, tidy_string < T > :: id ())) return;
            nits.merge (nuts); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type F, e_type P > struct type_function : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            const ::std::string::size_type brac = ss.find ('(');
            if (brac == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, brac)));
                test_value < F > (nits, v, fn);
                const ::std::string::size_type ket = ss.find (')');
                if (ket == ::std::string::npos)
                    nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                else
                {   bool ok = true;
                    ::std::string args (trim_the_lot_off (ss.substr (brac+1, ket-brac)));
                    if (ket < ss.length () - 1)
                    {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                        if (! post.empty ())
                        {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                            ok = false; } }
                    if (! args.empty ())
                    {   vstr_t params (split_by_charset (args, ","));
                        for (auto arg : params)
                            if (! test_value < P > (nits, v, uq3 (arg))) ok = false; }
                    if (ok) return; } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class NAME, int N > struct type_function_n : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            ::std::string::size_type brac = ss.find ('(');
            if (brac == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, brac)));
                if (compare_complain (nits, v, NAME :: sz (), fn))
                {   ::std::string::size_type ket = ss.find (')');
                    if (ket == ::std::string::npos)
                        nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                    else
                    {   bool ok = true;
                        ::std::string args (trim_the_lot_off (ss.substr (brac+1, ket-brac-1)));
                        if (ket < ss.length () - 1)
                        {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                            if (! post.empty ())
                            {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                                ok = false; } }
                        if (! args.empty ())
                        {   vstr_t params (split_by_charset (args, ","));
                            if (params.size () != N) ok = false;
                            for (auto arg : params)
                                if (! test_value < P > (nits, v, uq3 (arg))) ok = false; }
                        if (ok) return; } } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class NAME, e_type P, e_type Q > struct type_function_2_opt : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            ::std::string::size_type brac = ss.find ('(');
            if (brac == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, brac)));
                if (compare_complain (nits, v, NAME :: sz (), fn))
                {   ::std::string::size_type ket = ss.find (')');
                    if (ket == ::std::string::npos)
                        nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                    else
                    {   bool ok = true;
                        ::std::string args (trim_the_lot_off (ss.substr (brac+1, ket-brac)));
                        if (ket < ss.length () - 1)
                        {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                            if (! post.empty ())
                            {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                                ok = false; } }
                        if (! args.empty ())
                        {   vstr_t params (split_by_charset (args, ","));
                            if ((params.size () == 0) || (params.size () > 2))
                            {   nits.pick (nit_function, es_error, ec_type, "one or two parameters expected");
                                ok = false; }
                            if (params.size () > 0) if (! test_value < P > (nits, v, uq3 (params.at (0)))) ok = false;
                            if (params.size () > 1) if (! test_value < Q > (nits, v, uq3 (params.at (1)))) ok = false; }
                        if (ok) return; } } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class NAME, e_type P, e_type Q, e_type R > struct type_function_3_opt : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            ::std::string::size_type brac = ss.find ('(');
            if (brac == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, brac)));
                if (compare_complain (nits, v, NAME :: sz (), fn))
                {   ::std::string::size_type ket = ss.find (')');
                    if (ket == ::std::string::npos)
                        nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                    else
                    {   bool ok = true;
                        ::std::string args (trim_the_lot_off (ss.substr (brac+1, ket-brac)));
                        if (ket < ss.length () - 1)
                        {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                            if (! post.empty ())
                            {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                                ok = false; } }
                        if (! args.empty ())
                        {   vstr_t params (split_by_charset (args, ","));
                            if ((params.size () < 2) || (params.size () > 3))
                            {   nits.pick (nit_function, es_error, ec_type, "two or three parameters expected");
                                ok = false; }
                            if (params.size () > 0) if (! test_value < P > (nits, v, uq3 (params.at (0)))) ok = false;
                            if (params.size () > 1) if (! test_value < Q > (nits, v, uq3 (params.at (1)))) ok = false;
                            if (params.size () > 2) if (! test_value < R > (nits, v, uq3 (params.at (2)))) ok = false; }
                        if (ok) return; } } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class SZ > struct type_must_be : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            nits.pick (nit_isnt, es_error, ec_type, quote (SZ :: sz ()), " expected, not ", quote (ss)); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class SZ1, class SZ2 > struct type_either_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            nits.pick (nit_isnt, es_error, ec_type, quote (SZ1 :: sz ()), " or ", quote (SZ2 :: sz ()), "expected, not ", quote (ss)); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B > struct type_either_or : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (nuts); return; }
            if (test_value < B > (knots, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (knots); return; }
            nits.merge (nuts);
            nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B > struct type_either_neither : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
        {   tidy_string < T > :: status (s_good);
            return; }
        if (tidy_string < T > :: good ())
        {   nitpick nuts, knots;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) { nits.merge (nuts); return; }
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) { nits.merge (knots); return; }
            else
            {   nits.merge (nuts); nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, e_type A, e_type B, e_type C > struct type_one_of_three : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots, knits;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) { nits.merge (nuts); return; }
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) { nits.merge (knots); return; }
            else if (test_value < C > (knits, v, ss, tidy_string < T > :: id ())) { nits.merge (knits); return; }
            else
            {   nits.merge (nuts); nits.merge (knots); nits.merge (knits); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, e_type A, e_type B, e_type C, e_type D > struct type_one_of_four : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots, knits, knats;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) { nits.merge (nuts); return; }
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) { nits.merge (knots); return; }
            else if (test_value < C > (knits, v, ss, tidy_string < T > :: id ())) { nits.merge (knits); return; }
            else if (test_value < D > (knats, v, ss, tidy_string < T > :: id ())) { nits.merge (knats); return; }
            else
            {   nits.merge (nuts); nits.merge (knots); nits.merge (knits); nits.merge (knats); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, e_type A, e_type B, e_type C, e_type D, e_type E > struct type_one_of_five : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots, knits, knats, nets;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) { nits.merge (nuts); return; }
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) { nits.merge (knots); return; }
            else if (test_value < C > (knits, v, ss, tidy_string < T > :: id ())) { nits.merge (knits); return; }
            else if (test_value < D > (knats, v, ss, tidy_string < T > :: id ())) { nits.merge (knats); return; }
            else if (test_value < E > (nets, v, ss, tidy_string < T > :: id ())) { nits.merge (nets); return; }
            else
            {   nits.merge (nuts); nits.merge (knots); nits.merge (knits); nits.merge (knats); nits.merge (nets); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, e_type A, e_type B, class SZ > struct type_one_two : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "values expected (", type_name (T), ")");
        else if (string_vector < T, SZ > :: good ())
        {   vtype_t vty = { A, B };
            if (test_many (vty, nits, v, string_vector < T, SZ > :: get ())) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B, e_type C, class SZ > struct type_one_two_three : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "values expected (", type_name (T), ")");
        else if (string_vector < T, SZ > :: good ())
        {   vtype_t vty = { A, B, C };
            if (test_many (vty, nits, v, string_vector < T, SZ > :: get ())) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B, e_type C, e_type D, class SZ > struct type_one_two_three_four : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "values expected (", type_name (T), ")");
        else if (string_vector < T, SZ > :: good ())
        {   vtype_t vty = { A, B, C, D };
            if (test_many (vty, nits, v, string_vector < T, SZ > :: get ())) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B, e_type C, e_type D, e_type E, class SZ > struct type_one_two_three_four_five : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "values expected (", type_name (T), ")");
        else if (string_vector < T, SZ > :: good ())
        {   vtype_t vty = { A, B, C, D, E };
            if (test_many (vty, nits, v, string_vector < T, SZ > :: get ())) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P, bool B = false > struct type_at_least_one : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void accumulate (stats_t* s) const
    {   if (string_vector < T, SZ > :: good ())
        {   for (auto arg : string_vector < T, SZ > :: get ())
                type_master < P > :: accumulate (s, arg); } }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (null_string_ok < T, B > :: test_value (nits, s)) return;
        string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: size () > 0)
        {    bool ok = true;
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P > struct type_at_least_none : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P, int N > struct type_exactly_n : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = (string_vector < T, SZ > :: size () == N);
            if (! ok) nits.pick (nit_not_n, es_error, ec_type, quote (s), ": precisely ", N, " values expected");
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P, int FROM, int TO > struct type_range : string_vector < T, SZ >
{   BOOST_STATIC_ASSERT (FROM < TO);
    using string_vector < T, SZ > :: string_vector;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            const int n = GSL_NARROW_CAST < int > (string_vector < T, SZ > :: size ());
            if ((n < FROM) || (n > TO))
                nits.pick (nit_not_n, es_error, ec_type, quote (s), ": between ", FROM, " and ", TO, " values expected");
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ > struct type_or_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, e_type Q, class SZ > struct either_type_or_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            nitpick nuts, knots;
            if (test_value < P > (nuts, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (nuts); return; }
            if (test_value < Q > (knots, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (knots); return; }
            nits.merge (nuts); nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, e_type Q, e_type R, class SZ > struct one_of_three_or_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            nitpick nuts, knots, gnats;
            if (test_value < P > (nuts, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (nuts); return; }
            if (test_value < Q > (knots, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (knots); return; }
            if (test_value < R > (gnats, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (gnats); return; }
            nits.merge (nuts); nits.merge (knots); nits.merge (gnats); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2 > struct type_or_either_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, e_type Q, class SZ1, class SZ2 > struct either_type_or_either_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            nitpick nuts, knots;
            if (test_value < P > (nuts, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (nuts); return; }
            if (test_value < Q > (knots, v, ss, tidy_string < T > :: id ()))
            {   nits.merge (knots); return; }
            nits.merge (nuts); nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2, class SZ3 > struct type_or_any_string : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ3 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return;
            nits.merge (nits); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type U, class SZ, e_type P > struct type_one_or_both : tidy_string < T >
{   bool both_ = false;
    using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            PRESUME (SZ :: sz () != nullptr, __FILE__, __LINE__);
            const ::std::string::size_type pos = ss.find_first_of (SZ :: sz ());
            if (pos != ::std::string::npos)
            {   if (! test_value < P > (nits, v, ss.substr (pos+1), tidy_string < T > :: id ())) tidy_string < T > :: status (s_invalid);
                else both_ = true;
                ss = ss.substr (0, pos); }
            if (test_value < U > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); }
    ::std::size_t size () const noexcept { return both_ ? 2 : 1; } };

template < e_type T, e_type A, class SZ, e_type B > struct type_opt_then_must : tidy_string < T >
{   bool both_ = false;
    using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            PRESUME (SZ :: sz () != nullptr, __FILE__, __LINE__);
            ::std::string::size_type pos = ss.find_first_of (SZ :: sz ());
            if (pos != ::std::string::npos)
            {   if (! test_value < A > (nits, v, ss.substr (0, pos), tidy_string < T > :: id ())) tidy_string < T > :: status (s_invalid);
                else both_ = true;
                ss = ss.substr (pos+1); }
            if (test_value < B > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); }
    ::std::size_t size () const { return both_ ? 2 : 1; } };

template < e_type T, e_type A, class SZ, e_type B > struct type_many_then_must : tidy_string < T >
{   ::std::size_t count_ = 1;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            PRESUME (SZ :: sz () != nullptr, __FILE__, __LINE__);
            ::std::string::size_type pos = ss.find_first_of (SZ :: sz ());
            while (pos != ::std::string::npos)
            {   if (! test_value < A > (nits, v, ss.substr (0, pos), tidy_string < T > :: id ())) tidy_string < T > :: status (s_invalid);
                else ++count_;
                ss = ss.substr (pos+1);
                pos = ss.find_first_of (SZ :: sz ()); }
            if (test_value < B > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); }
    ::std::size_t size () const { return count_; } };

template < e_type T, e_type U, class SZ, e_type P > struct type_many_then_maybe : tidy_string < T >
{   ::std::size_t size_ = 0;
    using tidy_string < T > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   PRESUME (SZ :: sz () != nullptr, __FILE__, __LINE__);
            vstr_t ss (split_by_charset (tidy_string < T > :: get_string (), SZ::sz ()));
            PRESUME (! ss.empty (), __FILE__, __LINE__);
            size_ = ss.size ();
            bool res = true;
            ::std::string peed;
            for (auto sss : ss)
            {   nitpick nuts;
                if (! peed.empty ())
                {   nits.pick (nit_many_maybe, es_error, ec_type, quote (sss), " follows ", quote (peed), ", which should be the final value");
                    res = false; break; }
                if (test_value < U > (nuts, v, sss)) nits.merge (nuts);
                else
                {   nitpick knits;
                    if (! test_value < P > (knits, v, sss))
                    {   res = false;
                        nits.pick (nit_many_maybe, es_error, ec_type, quote (sss), " is not expected here"); }
                    else
                    {   nits.merge (knits);
                        peed = sss; } } }
            if (res) return; }
        tidy_string < T > :: status (s_invalid); }
    ::std::size_t size () const { return size_; } };

template < e_type T, e_type P, class SZ1, class SZ2 > struct type_id_or_either_string : type_or_either_string < T, P, SZ1, SZ2 >
{   using type_or_either_string < T, P, SZ1, SZ2 > :: type_or_either_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void verify_id (element& e)
    {   if (! type_or_either_string < T, P, SZ1, SZ2 > :: good ()) return;
        if (! type_or_either_string < T, P, SZ1, SZ2 > :: has_id ()) return;
        if (! ids_t::is_good_id (e, type_or_either_string < T, P, SZ1, SZ2 > :: get_id (), ec_type, nit_unknown, true))
            type_or_either_string < T, P, SZ1, SZ2 > :: status (s_invalid); } };

template < e_type T, e_type P, class SZSEP, class SZ1, class SZ2 > struct type_and_maybe_strings : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    static e_animation_type animation_type () noexcept { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected (", type_name (T), ")");
        else if (tidy_string < T > :: good ())
        {   vstr_t params (uq2_sep (tidy_string < T > :: get_string (), UQ_TRIM | UQ_ROUND | UQ_DQ | UQ_SQ, SZSEP :: sz ()));
            PRESUME (params.size () > 0, __FILE__, __LINE__);
            bool nice = test_value < P > (nits, v, params.at (0));
            nitpick nuts;
            for (::std::size_t i = 1; i < params.size (); ++i)
                if (! compare_complain (nuts, v, SZ1 :: sz (), params.at (i)) &&
                    ! compare_complain (nuts, v, SZ2 :: sz (), params.at (i)))
                    nice = false;
            if (nice) return;
            nits.merge (nuts); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P > struct type_or_null : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    void accumulate (stats_t* s) const
    {   if (tidy_string < T > :: good ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (! ss.empty ()) type_master < P > :: accumulate (s, ss); } }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
        {   tidy_string < T > :: status (s_good);
            return; }
        if (tidy_string < T > :: good ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

// would be better with various unit types and a concatenated type
template < e_type T, e_type N, class SZ1, class SZ2 > struct type_number_unit_2 : type_master < N >
{   using type_master < N > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a number with units expected (", type_name (T), ")");
        else
        {   vstr_t sz = { SZ1::sz (), SZ2::sz () };
            bool found = false;
            for (auto sss : sz)
            {   if (sss.length () >= ss.length ()) continue;
                if (compare_complain (nits, v, ss.substr (ss.length () - sss.length ()), sss.c_str ()))
                {   found = true;
                    ss = ss.substr (0, ss.length () - sss.length ());
                    break; } }
            if (! found)
                nits.pick (nit_bad_units, es_error, ec_type, "Units expected: '", SZ1::sz (), "' or '", SZ2::sz (), "'");
            else
            {   type_master < N > :: set_value (nits, v, ss);  
                return; } }
        type_master < N > :: status (s_invalid); } };

template < e_type T, e_type N, class SZ1, class SZ2, class SZ3 > struct type_number_unit_3 : type_master < N >
{   using type_master < N > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a number with units expected (", type_name (T), ")");
        else
        {   vstr_t sz = { SZ1::sz (), SZ2::sz (), SZ3::sz () };
            bool found = false;
            for (auto sss : sz)
            {   if (sss.length () >= ss.length ()) continue;
                if (compare_complain (nits, v, ss.substr (ss.length () - sss.length ()), sss.c_str ()))
                {   found = true;
                    ss = ss.substr (0, ss.length () - sss.length ());
                    break; } }
            if (! found)
                nits.pick (nit_bad_units, es_error, ec_type, "Units expected: '", SZ1::sz (), "', '", SZ2::sz (), "' or '", SZ3::sz (), "'");
            else
            {   type_master < N > :: set_value (nits, v, ss);  
                return; } }
        type_master < N > :: status (s_invalid); } };
