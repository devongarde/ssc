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
#include "base/type_master.h"

bool within_integer_limits (nitpick& nits, const html_version& v, const int val);
bool within_unsigned_limits (nitpick& nits, const html_version& v, const int val);
bool within_real_limits (nitpick& nits, const html_version& , const double val);

template < e_type T, typename BASE, BASE FROM, BASE TO > struct type_integer_between : numeric_value < T, BASE >
{   BOOST_STATIC_ASSERT (FROM < TO);
    using numeric_value < T, BASE > :: numeric_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < T, BASE > :: set_value (nits, v, s);
        if (numeric_value < T, BASE > :: good ())
        {   const long n = numeric_value < T, BASE > :: get ();
            if ((n >= FROM) && (n <= TO)) return; }
        nits.pick (nit_not_n, es_error, ec_type, quote (s), ": an integer betwee ", FROM, " and ", TO, " expected");
        numeric_value < T, BASE > :: status (s_invalid); } };

template < > struct type_master < t_base > : public numeric_value < t_base, unsigned int >
{   typedef true_type has_int_type;
    using numeric_value < t_base, unsigned int > :: numeric_value;
    static e_animation_type animation_type () noexcept { return at_integer; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_base, unsigned int > :: set_value (nits, v, s);
        if (numeric_value < t_base, unsigned int > :: empty ())
            nits.pick (nit_empty, es_error, ec_attribute, "value expected (", type_name (t_base), ")");
        else if (numeric_value < t_base, unsigned int > :: good ())
        {   if (v.math_version () < math_2) return;
            if ((value_ >= 2) && (value_ <= 36)) return;
            if (v.math_version () >= math_4_22)
            {   nits.pick (nit_base, ed_math_4_22, "4.2.1.3 Non-Strict uses of <cn>", es_warning, ec_type, "rendering of a value of BASE greater than 36 is browser dependent");
                return; } }
        nits.pick (nit_base, ed_math_2, "4.4.1.1 Number (cn)", es_error, ec_type, quote (s), " is not between 2 and 36 (inclusive)");
        numeric_value < t_base, unsigned int > :: status (s_invalid); } };

template < > struct type_master < t_fixedpoint > : type_base < double, t_fixedpoint >
{   double value_ = 0.0;
    using type_base < double, t_fixedpoint > :: type_base;
    static e_animation_type animation_type () noexcept { return at_number; }
    void swap (type_master < t_fixedpoint >& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < double, t_fixedpoint >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        value_ = lexical < double > :: cast (ss, 0.0);
        if ((ss.find_first_not_of (SIGNEDDECIMAL) == ::std::string::npos) && (lexical < double > :: test (ss)))
            type_base < double, t_fixedpoint > :: status (s_good);
        else
        {   nits.pick (nit_sunk, ed_so_11 , "Number (https://" SCHEMA_ORG "/Number)", es_error, ec_type, quote (ss), " contains unexpected characters, not just denary digit(s) and maybe a decimal point");
            type_base < double, t_fixedpoint > :: status (s_invalid); } }
    static double default_value () noexcept { return 0.0; }
    bool has_value (const double& b) const noexcept { return good () && (value_ == b); }
    int get_int () const noexcept { return static_cast < int > (value_  + 0.5); }
    double get () const noexcept { return value_; } };

template < > struct type_master < t_percent > : type_master < t_fixedpoint >
{   using type_master < t_fixedpoint > :: type_master;
    static e_animation_type animation_type () noexcept { return at_percentage; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        const ::std::string::size_type len (ss.length ());
        if (len > 1)
            if (ss.at (len - 1) == '%')
            {   type_master < t_fixedpoint > :: set_value (nits, v, ss.substr (0, len - 2));
                if (type_master < t_fixedpoint > :: good ())
                    if ((type_master < t_fixedpoint > :: value_ >= 0.0) && (type_master < t_fixedpoint > :: value_ <= 100.0)) return; }
        nits.pick (nit_percent, es_error, ec_type, "expecting a value between 0.0 and 100.0, followed by '%'");
        type_base < double, t_fixedpoint > :: status (s_invalid); }
    ::std::string get_string () const
    {   return ::boost::lexical_cast < ::std::string > (value_) + "%"; }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); } };

template < > struct type_master < t_percent_flexible > : type_master < t_fixedpoint >
{   using type_master < t_fixedpoint > :: type_master;
    static e_animation_type animation_type () noexcept { return at_percentage; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "none"))
        {   type_master < t_fixedpoint > :: status (s_good);
            return; }
        const ::std::string::size_type len (ss.length ());
        if (len > 1)
            if (ss.at (len - 1) == '%')
            {   type_master < t_fixedpoint > :: set_value (nits, v, ss.substr (0, len - 2));
                if (type_master < t_fixedpoint > :: good ()) return; }
        nits.pick (nit_percent, es_error, ec_type, "expecting a number followed by '%'");
        type_base < double, t_fixedpoint > :: status (s_invalid); }
    ::std::string get_string () const
    {   return ::boost::lexical_cast < ::std::string > (value_) + "%"; }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); } };

template < > struct type_master < t_integer > : numeric_value < t_integer, int >
{   typedef true_type has_int_type;
    using numeric_value < t_integer, int > :: numeric_value;
    static e_animation_type animation_type () noexcept { return at_integer; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_integer, int > :: set_value (nits, v, s);
        if (! numeric_value < t_integer, int > :: good ())
            nits.pick (nit_not_an_integer, es_error, ec_type, quote (s), " is no integer");
        else if (within_integer_limits (nits, v, numeric_value < t_integer, int > :: get ())) return;
        numeric_value < t_integer, int > :: status (s_invalid); } };

template < > struct type_master < t_negative > : type_master < t_integer >
{   typedef true_type has_int_type;
    using type_master < t_integer > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_integer > :: set_value (nits, v, s);
        if (type_master < t_integer > :: good ())
            if (value_ <= 0) return;
            else
            {   nits.pick (nit_positive, es_error, ec_type, quote (s), " must be zero or negative");
                type_master < t_integer > :: status (s_invalid); } } };

template < > struct type_master < t_positive > : type_master < t_integer >
{   typedef true_type has_int_type;
    using type_master < t_integer > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_integer > :: set_value (nits, v, s);
        if (type_master < t_integer > :: good ())
            if (value_ > 0) return;
            else
            {   nits.pick (nit_positive, es_error, ec_type, quote (s), " must be greater than zero");
                type_master < t_integer > :: status (s_invalid); } } };

template < > struct type_master < t_real > : type_base < double, t_real >
{   double value_ = 0.0;
    using type_base < double, t_real > :: type_base;
    static e_animation_type animation_type () noexcept { return at_number; }
    void swap (type_master < t_real >& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < double, t_real >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        value_ = lexical < double > :: cast (ss, 0.0);
        if ((ss.find_first_not_of (REAL) == ::std::string::npos) && (lexical < double > :: test (ss)))
        {   if (within_real_limits (nits, v, value_))
            {   type_base < double, t_real > :: status (s_good);
                return; } }
        else nits.pick (nit_sunk, ed_50, "2.4.4.3 Floating-point numbers", es_error, ec_type, quote (ss), " is not a floating point number");
        type_base < double, t_real > :: status (s_invalid); }
    static double default_value () noexcept { return 0.0; }
    bool has_value (const double& b) const noexcept { return good () && (value_ == b); }
    int get_int () const noexcept { return static_cast < int > (value_ + 0.5); }
    double get () const noexcept { return value_; } };

template < e_type T, long FROM, long TO > struct type_number_between : type_master < t_real >
{   BOOST_STATIC_ASSERT (FROM < TO);
    const double from = static_cast < double > (FROM);
    const double to = static_cast < double > (TO);
    using type_master < t_real > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   const double d = type_master < t_real > :: get ();
            if ((d >= from) && (d <= to)) return; }
        nits.pick (nit_not_n, es_error, ec_type, quote (s), ": a number between ", FROM, " and ", TO, " expected");
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_unsigned > : public numeric_value < t_unsigned, unsigned int >
{   typedef true_type has_int_type;
    using numeric_value < t_unsigned, unsigned int > :: numeric_value;
    static e_animation_type animation_type () noexcept { return at_integer; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_unsigned, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_unsigned, unsigned int > :: good ())
            nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is no unsigned integer");
        else if (within_unsigned_limits (nits, v, numeric_value < t_unsigned, unsigned int > :: get ())) return;
        numeric_value < t_unsigned, unsigned int > :: status (s_invalid); } };

template < > struct type_master < t_un_ex > : public type_master < t_unsigned >
{   typedef true_type has_int_type;
    using type_master < t_unsigned > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (s.empty ()) type_master < t_unsigned > :: status (s_good);
        else
        {   type_master < t_unsigned > :: set_value (nits, v, s);
            if (! type_master < t_unsigned > :: good ())
            {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is neither an unsigned integer nor completely omitted");
                type_master < t_unsigned > :: status (s_invalid); } } } };

template < > struct type_master < t_plus_1_7 > : public type_master < t_unsigned >
{   typedef true_type has_int_type;
    using type_master < t_unsigned > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string arg (trim_the_lot_off (s));
        type_master < t_unsigned > :: set_value (nits, v, arg);
        if (! type_master < t_unsigned > :: good () || (value_ < 1) || (value_ > 7))
        if (type_master < t_unsigned > :: good ())
        {   nits.pick (nit_plus_1_7, es_error, ec_type, quote (s), " does not lie between 1 and 7 (inclusive)");
            type_master < t_unsigned > :: status (s_invalid); } } };

template < > struct type_master < t_not_0 > : type_master < t_real >
{   using type_master < t_real > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if (type_master < t_real > :: value_ != 0.0) return;
            nits.pick (nit_not_0, es_error, ec_type, "cannot be zero");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_zero_to_one > : type_master < t_real >
{   using type_master < t_real > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > :: value_ >= 0.0) && (type_master < t_real > :: value_ <= 1.0)) return;
            nits.pick (nit_zero_to_one, es_error, ec_type, quote (type_master < t_real > :: get_string ()), " is not between 0.0 and 1.0 (inclusive)");
            type_master < t_real > :: status (s_invalid); } } };

template < int N > struct n_or_more : type_master < t_real >
{   using type_master < t_real > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > :: value_ >= static_cast < double > (N))) return;
            nits.pick (nit_1_more, es_error, ec_type, quote (s), " must equal or exceed ", N, ".0");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_not_neg > : type_integer_between < t_not_neg, long, 0, INT_MAX >
{ using  type_integer_between < t_not_neg, long, 0, INT_MAX > :: type_integer_between; };

template < > struct type_master < t_not_pos > : type_integer_between < t_not_pos, long, INT_MIN, 0 >
{ using  type_integer_between < t_not_pos, long, INT_MIN, 0 > :: type_integer_between; };

template < > struct type_master < t_short > : type_integer_between < t_short, int, -32768, 32767 >
{ using type_integer_between < t_short, int, -32768, 32767 > :: type_integer_between; };

template < > struct type_master < t_unsigned_byte > : type_integer_between < t_unsigned_byte, short, 0, 255 >
{ using type_integer_between < t_unsigned_byte, short, 0, 255 > :: type_integer_between; };

template < > struct type_master < t_unsigned_short > : type_integer_between < t_unsigned_short, int, 0, 65535 >
{ using type_integer_between < t_unsigned_short, int, 0, 65535 > :: type_integer_between; };

template < > struct type_master < t_1_to_7 > : type_integer_between < t_1_to_7, short, 1, 7 >
{ using  type_integer_between < t_1_to_7, short, 1, 7 > :: type_integer_between; };

template < > struct type_master < t_1_to_20 > : type_integer_between < t_1_to_20, short, 1, 20 >
{ using  type_integer_between < t_1_to_20, short, 1, 20 > :: type_integer_between; };

template < > struct type_master < t_1_to_99 > : type_integer_between < t_1_to_99, short, 1, 99 >
{ using  type_integer_between < t_1_to_99, short, 1, 99 > :: type_integer_between; };

template < > struct type_master < t_0_to_255 > : type_integer_between < t_0_to_255, short, 0, 255 >
{ using  type_integer_between < t_0_to_255, short, 0, 255 > :: type_integer_between; };

template < > struct type_master < t_hue > : type_number_between < t_hue, 0, 360 >
{ using  type_number_between < t_hue, 0, 360 > :: type_number_between; };

template < > struct type_master < t_zero_or_one > : type_integer_between < t_zero_or_one, short, 0, 1 >
{ using  type_integer_between < t_zero_or_one, short, 0, 1 > :: type_integer_between; };
