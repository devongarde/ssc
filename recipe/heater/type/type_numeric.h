/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

template < > struct type_master < t_fixedpoint > : type_base < double, t_fixedpoint >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_fixedpoint >& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        type_base < double, t_fixedpoint >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (DECIMAL) == ::std::string::npos) && (lexical < double > :: test (s)))
            type_base < double, t_fixedpoint > :: status (s_good);
        else
        {   nits.pick (nit_sunk, es_error, ec_type, quote (s), " is not a decimal number consisting of denary digit(s) and maybe an anglophone decimal point ('.' not ',')");
            type_base < double, t_fixedpoint > :: status (s_invalid); } }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_  + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_integer > : numeric_value < t_integer, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_integer, int > :: set_value (nits, v, s);
        if (numeric_value < t_integer, int > :: invalid ())
            nits.pick (nit_not_an_integer, es_error, ec_type, quote (s), " is not an integer"); } };

template < > struct type_master < t_negative > : numeric_value < t_negative, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_negative, int > :: set_value (nits, v, s);
        if (! numeric_value < t_negative, int > :: good () || (value_ > 0))
        {   nits.pick (nit_positive, es_error, ec_type, quote (s), " is neither zero nor a negative integer");
            numeric_value < t_negative, int > :: status (s_invalid); } } };

template < > struct type_master < t_positive > : numeric_value < t_positive, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_positive, int > :: set_value (nits, v, s);
        if (! numeric_value < t_positive, int > :: good () || (value_ <= 0))
        {   nits.pick (nit_positive, es_error, ec_type, quote (s), " is not an integer greater than zero");
            numeric_value < t_positive, int > :: status (s_invalid); } } };

template < > struct type_master < t_real > : type_base < double, t_real >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_real >& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        type_base < double, t_real >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (REAL) == ::std::string::npos) && (lexical < double > :: test (s)))
            type_base < double, t_real > :: status (s_good);
        else
        {   nits.pick (nit_sunk, ed_50, "2.4.4.3 Floating-point numbers", es_error, ec_type, quote (s), " is not a floating point number");
            type_base < double, t_real > :: status (s_invalid); } }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_ + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_normalised > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > ::value_ >= 0.0) &&
                (type_master < t_real > ::value_ <= 1.0)) return;
            nits.pick (nit_0_1, es_error, ec_type, "a normalised value must lie between 0 and 1 inclusive");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_1_more > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > ::value_ >= 1.0)) return;
            nits.pick (nit_1_more, es_error, ec_type, "a limit must equal or exceed 1.0");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_unsigned > : public numeric_value < t_unsigned, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_unsigned, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_unsigned, unsigned int > :: good ())
        {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is not an unsigned integer");
            numeric_value < t_unsigned, unsigned int > :: status (s_invalid); } } };

template < > struct type_master < t_un_ex > : public numeric_value < t_un_ex, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (s.empty ()) numeric_value < t_un_ex, unsigned int > :: status (s_good);
        else
        {   numeric_value < t_un_ex, unsigned int > :: set_value (nits, v, s);
            if (! numeric_value < t_un_ex, unsigned int > :: good ())
            {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is not an unsigned integer, or completely omitted");
                numeric_value < t_un_ex, unsigned int > :: status (s_invalid); } } } };

template < > struct type_master < t_1_to_7 > : public numeric_value < t_1_to_7, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_1_to_7, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_1_to_7, unsigned int > :: good () || (value_ < 1) || (value_ > 7))
        {   nits.pick (nit_1_to_7, es_error, ec_type, quote (s), " does not lie between 1 and 7 (inclusive)");
            numeric_value < t_1_to_7, unsigned int > :: status (s_invalid); } } };

template < > struct type_master < t_plus_1_7 > : public numeric_value < t_plus_1_7, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string arg (trim_the_lot_off (s));
        numeric_value < t_plus_1_7, unsigned int > :: set_value (nits, v, arg);
        if (numeric_value < t_plus_1_7, unsigned int > :: good ())
        {   unsigned n = 0;
            numeric_value < t_plus_1_7, unsigned int > :: get_number (n);
            if ((n > 0) && (n <= 99)) return;
            nits.pick (nit_plus_1_7, es_error, ec_type, quote (s), " does not lie between 1 and 99 (inclusive)");
            numeric_value < t_plus_1_7, unsigned int > :: status (s_invalid); } } };

template < > struct type_master < t_reals > : type_at_least_one < t_reals, sz_commaspace, t_real > { };
