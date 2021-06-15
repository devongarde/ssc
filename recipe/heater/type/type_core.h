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
#include "type/type_base.h"
#include "main/context.h"
#include "utility/lexical.h"
#include "utility/quote.h"
#include "type/sz.h"

::std::string make_tidy (nitpick& nits, const html_version& v, const ::std::string& s);

template < e_type TYPE > struct string_value : public type_base < ::std::string, TYPE >
{   ::std::string value_;
    static ::std::string default_value () { return ::std::string (); }
    string_value () = default;
    void swap (string_value& t) NOEXCEPT
    {   value_.swap (t.value_);
        type_base < ::std::string, TYPE >::swap (t); }
    ::std::string get_string () const
    {   return value_; }
    ::std::string get () const
    {   return value_; }
    void set_value (nitpick& , const html_version& , const ::std::string& s)
    {   value_.assign (s);
        if (value_.empty ()) type_base < ::std::string, TYPE > :: status (s_empty);
        else type_base < ::std::string, TYPE > :: status (s_good); }
    bool has_value (const ::std::string& s) const { return type_base < ::std::string, TYPE > :: good () && (value_ == s); }
    int get_int () const { return lexical < int > :: cast (value_); }
    void shadow (::std::stringstream& ss, const html_version& v, element* )
    {   if (! v.xhtml () && (value_.find_first_not_of (ALPHADDD "+") == ::std::string::npos)) ss << '=' << value_;
        else if (value_.find_first_of ('\"') == ::std::string::npos) ss << '=' << '"' << value_ << '"';
        else if (value_.find_first_of ("'") == ::std::string::npos) ss << "='" << value_ << "'";
        else ss << '=' << enquote (value_); }
    void reset ()
    {   value_.clear ();
        type_base < ::std::string, TYPE > :: reset (); } };

template < e_type TYPE > struct tidy_string : public string_value < TYPE >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (s.empty ()) string_value < TYPE > :: status (s_empty);
        else string_value < TYPE > :: set_value (nits, v, make_tidy (nits, v, s)); } };

template < e_type TYPE > struct string_vector_base : public tidy_string < TYPE >
{   typedef vstr_t value_type;
    value_type value_;
    void swap (string_vector_base& t) NOEXCEPT
    {   value_.swap (t.value_);
        tidy_string < TYPE >::swap (t); }
    ::std::string get_string () const
    {   return tidy_string < TYPE > :: get_string (); }
    ::std::size_t size () const { return value_.size (); }
    static value_type default_value () { return value_type (); }
    void reset ()
    {   value_.clear ();
        tidy_string < TYPE > :: reset (); }
    const ::std::string& at (const ::std::size_t n) const
    {   PRESUME (n < value_.size (), __FILE__, __LINE__);
        return value_.at (n); }
    ::std::string& at (const ::std::size_t n)
    {   PRESUME (n < value_.size (), __FILE__, __LINE__);
        return value_.at (n); }
    value_type get () const
    {   return value_; } };

template < e_type TYPE, class SZ > struct string_vector : public string_vector_base < TYPE >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector_base < TYPE > :: set_value (nits, v, s);
        if (string_vector_base < TYPE > :: good ())
        {   vstr_t tmp = split_by_charset (string_vector_base < TYPE > :: get_string (), SZ :: sz ());
#ifndef FUDDYDUDDY
            string_vector_base < TYPE > :: value_.reserve (tmp.size ());
#endif // FUDDYDUDDY
            for (auto ss : tmp)
                string_vector_base < TYPE > :: value_.emplace_back (make_tidy (nits, v, ss)); } }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << "=\""; bool first = true;
        for (auto s : string_vector_base < TYPE > :: value_)
        {   if (! first) ss << SZ :: sz () [0];
            first = false;
            ss << s; }
        ss << '"'; } };

template < e_type TYPE > struct string_vector < TYPE, sz_space > : public string_vector_base < TYPE >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector_base < TYPE > :: set_value (nits, v, s);
        if (string_vector_base < TYPE > :: good ())
            string_vector_base < TYPE > :: value_ = split_by_space (string_vector_base < TYPE > :: get_string ()); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << "=\""; bool first = true;
        for (auto s : string_vector_base < TYPE > :: value_)
        {   if (! first) ss << ' ';
            first = false;
            ss << s; }
        ss << '"'; } };

template < e_type TYPE, typename NUMERIC_TYPE, NUMERIC_TYPE def = 0 > struct numeric_value : public type_base < NUMERIC_TYPE, TYPE >
{   NUMERIC_TYPE value_ = def;
    static NUMERIC_TYPE default_value () { return def; }
    numeric_value () = default;
    void swap (numeric_value& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        type_base < NUMERIC_TYPE, TYPE >::swap (t); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << value_; }
    void get_number (NUMERIC_TYPE& i) const
    {   i = value_; }
    NUMERIC_TYPE get () const { return value_; }
    void set_number (const NUMERIC_TYPE& i)
    {   value_ =  i;
        type_base < NUMERIC_TYPE, TYPE > :: status (s_good); }
    ::std::string get_string () const
    {   return ::boost::lexical_cast < ::std::string > (value_); }
    int get_int () const { return static_cast < int > (value_); }
    bool has_value (const NUMERIC_TYPE& n) const { return type_base < NUMERIC_TYPE, TYPE > :: good () && (value_ == n); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   bool b = false;
        value_ = lexical < NUMERIC_TYPE > :: cast2 (trim_the_lot_off (s), b);
        if (b) type_base < NUMERIC_TYPE, TYPE > :: status (s_good);
        else
        {   nits.pick (nit_not_an_integer, es_error, ec_type, quote (s), " is not a number");
            type_base < NUMERIC_TYPE, TYPE > :: status (s_invalid); } } };
