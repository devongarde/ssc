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
#include "type/type_case.h"
#include "type/type_core.h"
#include "utility/quote.h"
#include "parser/parse_elements.h"
#include "main/args.h"

class element;

template < e_type TYPE > class type_master : public string_value < TYPE > { };

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    return t.good (); }

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& id)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return false;
    id = t.get_id ();
    return true; }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return type_master < T > :: default_value ();
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }

template < e_type T > e_animation_type grab_animation_type ()
{   type_master < T > t;
    return t.animation_type (); }

template < e_type T, e_type P, class SZ > struct string_then_type : tidy_string < T >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            const ::std::size_t len = strlen (SZ :: sz ());
            if (! compare_complain (nits, v, SZ :: sz (), ss.substr (0, len)))
                nits.pick (nit_syntax, es_error, ec_type, "here, ", quote (ss), " should start with ", quote (SZ :: sz ()));
            else if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type F, e_type P > struct type_function : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            ::std::string::size_type bra = ss.find ('(');
            if (bra == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, bra)));
                test_value < F > (nits, v, fn);
                ::std::string::size_type ket = ss.find (')');
                if (ket == ::std::string::npos)
                    nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                else
                {   bool ok = true;
                    ::std::string args (trim_the_lot_off (ss.substr (bra+1, ket-bra)));
                    if (ket < ss.length () - 1)
                    {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                        if (! post.empty ())
                        {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                            ok = false; } }
                    if (! args.empty ())
                    {   vstr_t params (split_by_charset (args, ","));
                        for (auto arg : params)
                            if (! test_value < P > (nits, v, arg)) ok = false; }
                    if (ok) return; } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class NAME, int N > struct type_function_n : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "function expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            ::std::string::size_type bra = ss.find ('(');
            if (bra == ::std::string::npos)
                nits.pick (nit_function, es_error, ec_type, "'(' expected in ", quote (ss));
            else
            {   ::std::string fn (trim_the_lot_off (ss.substr (0, bra)));
                if (compare_complain (nits, v, NAME :: sz (), fn))
                {   ::std::string::size_type ket = ss.find (')');
                    if (ket == ::std::string::npos)
                        nits.pick (nit_function, es_error, ec_type, "')' expected in ", quote (ss));
                    else
                    {   bool ok = true;
                        ::std::string args (trim_the_lot_off (ss.substr (bra+1, ket-bra)));
                        if (ket < ss.length () - 1)
                        {   ::std::string post (trim_the_lot_off (ss.substr (ket+1)));
                            if (! post.empty ())
                            {   nits.pick (nit_function, es_error, ec_type, "unexpected characters '", post, "' after ')' in ", quote (ss));
                                ok = false; } }
                        if (! args.empty ())
                        {   vstr_t params (split_by_charset (args, ","));
                            if (params.size () != N) ok = false;
                            for (auto arg : params)
                                if (! test_value < P > (nits, v, arg)) ok = false; }
                        if (ok) return; } } } }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class SZ > struct type_must_be : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            nits.pick (nit_isnt, es_error, ec_type, quote (SZ :: sz ()), " expected, not ", quote (ss)); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, class SZ1, class SZ2 > struct either_string : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            nits.pick (nit_isnt, es_error, ec_type, quote (SZ1 :: sz ()), " or ", quote (SZ2 :: sz ()), "expected, not ", quote (ss)); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type A, e_type B > struct type_either_or : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) nits.merge (nuts);
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) nits.merge (knots);
            else
            {   nits.merge (nuts); nits.merge (knots); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, e_type A, e_type B, e_type C > struct type_one_of_three : tidy_string < T > // if more alternatives are needed, generalise with template metaprogramming
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   nitpick nuts, knots, knits;
            const ::std::string ss (tidy_string < T > :: get_string ());
            if (test_value < A > (nuts, v, ss, tidy_string < T > :: id ())) nits.merge (nuts);
            else if (test_value < B > (knots, v, ss, tidy_string < T > :: id ())) nits.merge (knots);
            else if (test_value < C > (knits, v, ss, tidy_string < T > :: id ())) nits.merge (knits);
            else
            {   nits.merge (nuts); nits.merge (knots); nits.merge (knits); }
        tidy_string < T > :: status (s_invalid); } } };

template < e_type T, class SZ, e_type P > struct type_at_least_one : string_vector < T, SZ >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
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
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            if (string_vector < T, SZ > :: size () != N)
                nits.pick (nit_not_n, es_error, ec_type, quote (s), ": precisely ", N, " values expected");
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, class SZ, e_type P, int FROM, int TO > struct type_range : string_vector < T, SZ >
{   BOOST_STATIC_ASSERT (FROM < TO);
    static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ()) return;
        else if (string_vector < T, SZ > :: good ())
        {   bool ok = true;
            const int n = static_cast < int > (string_vector < T, SZ > :: size ());
            if ((n < FROM) || (n > TO))
                nits.pick (nit_not_n, es_error, ec_type, quote (s), ": between ", FROM, " and ", TO, " values expected");
            for (auto arg : string_vector < T, SZ > :: get ())
                if (! test_value < P > (nits, v, arg)) ok = false;
            if (ok) return; }
        string_vector < T, SZ > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ > struct type_or_string : tidy_string < T >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, e_type Q, class SZ > struct either_type_or_string : tidy_string < T >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ :: sz (), ss)) return;
            nitpick nuts;
            if (test_value < P > (nuts, v, ss, tidy_string < T > :: id ())) return;
            if (test_value < Q > (nuts, v, ss, tidy_string < T > :: id ())) return;
            nits.merge (nuts); }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2 > struct type_or_either_string : tidy_string < T >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type P, class SZ1, class SZ2, class SZ3 > struct type_or_any_string : tidy_string < T >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: good () || tidy_string < T > :: empty ())
        {   const ::std::string ss (tidy_string < T > :: get_string ());
            if (compare_complain (nits, v, SZ1 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ2 :: sz (), ss)) return;
            if (compare_complain (nits, v, SZ3 :: sz (), ss)) return;
            if (test_value < P > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); } };

template < e_type T, e_type U, class SZ, e_type P > struct type_one_or_both : tidy_string < T >
{   bool both_ = false;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
        else if (tidy_string < T > :: good ())
        {   ::std::string ss (tidy_string < T > :: get_string ());
            PRESUME (SZ :: sz () != nullptr, __FILE__, __LINE__);
            ::std::string::size_type pos = ss.find_first_of (SZ :: sz ());
            if (pos != ::std::string::npos)
            {   if (! test_value < P > (nits, v, ss.substr (pos+1), tidy_string < T > :: id ())) tidy_string < T > :: status (s_invalid);
                else both_ = true;
                ss = ss.substr (0, pos); }
            if (test_value < U > (nits, v, ss, tidy_string < T > :: id ())) return; }
        tidy_string < T > :: status (s_invalid); }
    ::std::size_t size () const { return both_ ? 2 : 1; } };

template < e_type T, e_type A, class SZ, e_type B > struct type_opt_then_must : tidy_string < T >
{   bool both_ = false;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
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
            nits.pick (nit_empty, es_error, ec_type, "value expected");
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
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        if (tidy_string < T > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "value expected");
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

template < e_type T, e_type P, class SZ1, class SZ2 > struct id_or_either_string : type_or_either_string < T, P, SZ1, SZ2 >
{   static e_animation_type animation_type () { return grab_animation_type < P > (); }
    void verify_id (element& e)
    {   if (! type_or_either_string < T, P, SZ1, SZ2 > :: good ()) return;
        if (! type_or_either_string < T, P, SZ1, SZ2 > :: has_id ()) return;
        if (! ids_t::is_good_id (e, type_or_either_string < T, P, SZ1, SZ2 > :: get_id (), ec_type, nit_unknown, true))
            type_or_either_string < T, P, SZ1, SZ2 > :: status (s_invalid); } };
