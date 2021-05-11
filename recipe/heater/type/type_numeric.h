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
#include "type/type_master.h"

bool within_integer_limits (nitpick& nits, const html_version& v, const int val);
bool within_unsigned_limits (nitpick& nits, const html_version& v, const int val);
bool within_real_limits (nitpick& nits, const html_version& , const double val);

template < > struct type_master < t_base > : public numeric_value < t_base, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_base, unsigned int > :: set_value (nits, v, s);
        if (numeric_value < t_base, unsigned int > :: empty ())
            nits.pick (nit_empty, es_error, ec_attribute, "value expected");
        else if (numeric_value < t_base, unsigned int > :: good ())
        {   if (v.math_version () < math_2) return;
            if ((value_ >= 2) && (value_ <= 36)) return;
            nits.pick (nit_base, ed_math_2, "4.4.1.1 Number (cn)", es_error, ec_type, quote (s), " is not between 2 and 36 (inclusive)"); }
        numeric_value < t_base, unsigned int > :: status (s_invalid); } };

template < > struct type_master < t_fixedpoint > : type_base < double, t_fixedpoint >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_fixedpoint >& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        type_base < double, t_fixedpoint >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (DECIMAL) == ::std::string::npos) && (lexical < double > :: test (s)))
            type_base < double, t_fixedpoint > :: status (s_good);
        else
        {   nits.pick (nit_sunk, ed_so_11 , "Number (https://" SCHEMA_ORG "/Number)", es_error, ec_type, quote (s), " contains unexpected characters, not just denary digit(s) and maybe a decimal point");
            type_base < double, t_fixedpoint > :: status (s_invalid); } }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_  + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_percent > : type_master < t_fixedpoint >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        ::std::string::size_type len (ss.length ());
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

template < > struct type_master < t_integer > : numeric_value < t_integer, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_integer, int > :: set_value (nits, v, s);
        if (! numeric_value < t_integer, int > :: good ())
            nits.pick (nit_not_an_integer, es_error, ec_type, quote (s), " is no integer");
        else if (within_integer_limits (nits, v, numeric_value < t_integer, int > :: get ())) return;
        numeric_value < t_integer, int > :: status (s_invalid); } };

template < > struct type_master < t_negative > : type_master < t_integer >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_integer > :: set_value (nits, v, s);
        if (type_master < t_integer > :: good ())
            if (value_ <= 0) return;
            else
            {   nits.pick (nit_positive, es_error, ec_type, quote (s), " must be zero or negative");
                type_master < t_integer > :: status (s_invalid); } } };

template < > struct type_master < t_positive > : type_master < t_integer >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_integer > :: set_value (nits, v, s);
        if (type_master < t_integer > :: good ())
            if (value_ > 0) return;
            else
            {   nits.pick (nit_positive, es_error, ec_type, quote (s), " must be greater than zero");
                type_master < t_integer > :: status (s_invalid); } } };

template < > struct type_master < t_real > : type_base < double, t_real >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_real >& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        type_base < double, t_real >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (REAL) == ::std::string::npos) && (lexical < double > :: test (s)))
        {   if (within_real_limits (nits, v, value_))
            {   type_base < double, t_real > :: status (s_good);
                return; } }
        else nits.pick (nit_sunk, ed_50, "2.4.4.3 Floating-point numbers", es_error, ec_type, quote (s), " is not a floating point number");
        type_base < double, t_real > :: status (s_invalid); }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_ + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_unsigned > : public numeric_value < t_unsigned, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_unsigned, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_unsigned, unsigned int > :: good ())
            nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is no unsigned integer");
        else if (within_unsigned_limits (nits, v, numeric_value < t_unsigned, unsigned int > :: get ())) return;
        numeric_value < t_unsigned, unsigned int > :: status (s_invalid); } };

template < > struct type_master < t_un_ex > : public type_master < t_unsigned >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (s.empty ()) type_master < t_unsigned > :: status (s_good);
        else
        {   type_master < t_unsigned > :: set_value (nits, v, s);
            if (! type_master < t_unsigned > :: good ())
            {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is neither an unsigned integer nor completely omitted");
                type_master < t_unsigned > :: status (s_invalid); } } } };

template < > struct type_master < t_1_to_7 > : public type_master < t_unsigned >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_unsigned > :: set_value (nits, v, s);
        if (! type_master < t_unsigned > :: good () || (value_ < 1) || (value_ > 7))
        {   nits.pick (nit_1_to_7, es_error, ec_type, quote (s), " does not lie between 1 and 7 (inclusive)");
            type_master < t_unsigned > :: status (s_invalid); } } };

template < > struct type_master < t_plus_1_7 > : public type_master < t_unsigned >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string arg (trim_the_lot_off (s));
        type_master < t_unsigned > :: set_value (nits, v, arg);
        if (! type_master < t_unsigned > :: good () || (value_ < 1) || (value_ > 99))
        if (type_master < t_unsigned > :: good ())
        {   nits.pick (nit_plus_1_7, es_error, ec_type, quote (s), " does not lie between 1 and 99 (inclusive)");
            type_master < t_unsigned > :: status (s_invalid); } } };

template < > struct type_master < t_zero_to_one > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > :: value_ >= 0.0) && (type_master < t_real > :: value_ <= 1.0)) return;
            nits.pick (nit_zero_to_one, es_error, ec_type, quote (type_master < t_real > :: get_string ()), " is not between 0.0 and 1.0 (inclusive)");
            type_master < t_real > :: status (s_invalid); } } };

template < int N > struct n_or_more : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > :: value_ >= static_cast < double > (N))) return;
            nits.pick (nit_1_more, es_error, ec_type, "a limit must equal or exceed ", N, ".0");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_0_more > : n_or_more < 0 > { };
template < > struct type_master < t_1_more > : n_or_more < 1 > { };
template < > struct type_master < t_real_i > : type_or_string < t_real_i, t_real, sz_inherit > { };
template < > struct type_master < t_real_ai > : type_or_either_string < t_real_ai, t_real, sz_auto, sz_inherit > { };
template < > struct type_master < t_reals > : type_at_least_one < t_reals, sz_commaspace, t_real > { };
template < > struct type_master < t_zero_to_ones > : type_at_least_one < t_zero_to_ones, sz_commaspace, t_zero_to_one > { };
