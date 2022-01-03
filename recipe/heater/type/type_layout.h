/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

template < > struct type_master < t_border > : public tidy_string < t_border >
{   using tidy_string < t_border > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_border > :: set_value (nits, v, s);
        ::std::string arg = string_value < t_border > :: get_string ();
        switch (v.mjr ())
        {   case 1 :
            case 3 :    if (s.empty ())
                        {   tidy_string < t_border > :: status (s_good); return; }
                        if ((v.mnr () == 2) && (arg.find_first_not_of (DENARY) == ::std::string::npos))
                        {   tidy_string < t_border > :: status (s_good); return; }
                        break;
            case 2 :    if (s.empty ()) tidy_string < t_border > :: status (s_good);
                        else
                        {   type_master < t_measure > val;
                            val.set_value (nits, v, arg);
                            tidy_string < t_border > :: status (val.status ()); }
                        return;
            default :   break; }
        if (v.is_5 () && (arg != "1"))
        {   tidy_string < t_border > :: status (s_invalid);
            nits.pick (nit_bad_border, es_error, ec_type, "a BORDER value must be \"1\""); } } };

template < > struct type_master < t_sizex > : type_base < ::std::string, t_sizex >
{   bool any_ = false;
    int x_ = 0, y_ = 0;
    using type_base < ::std::string, t_sizex > :: type_base;
    void swap (type_master < t_sizex >& t) noexcept
    {   ::std::swap (any_, t.any_);
        ::std::swap (x_, t.x_);
        ::std::swap (y_, t.y_);
        type_base < ::std::string, t_sizex >::swap (t); }
    bool parse (nitpick& nits, const html_version& , const ::std::string& s)
    {   any_ = (s == "any");
        if (any_) return true;
        const ::std::size_t sep = s.find_first_of ("Xx");
        if (sep == s.npos) return false;
        if ((sep < 1) || (sep >= (s.length () - 1))) return false;
        if ((s.at (0) == '0') || (s.at (sep + 1) == '0'))
            nits.pick (nit_sizes, ed_52, "4.2.4. The link element", es_warning, ec_type, quote (s), ": no integer can start with a '0'");
        else if ((s.at (0) < '1') || (s.at (1) > '9') || (s.at (sep + 1) < '1') || (s.at (sep + 1) > '9'))
            nits.pick (nit_sizes, ed_52, "4.2.4. The link element", es_warning, ec_type, quote (s), " is not two unsigned positive integers separated by 'x'");
        bool b = false;
        x_ = lexical < int > :: cast2 (s.substr (0, sep), b);
        if (b) y_ = lexical < int > :: cast2 (s.substr (sep + 1), b);
        return b; }
    ::std::string get_string () const
    {   if (any_) return "any";
        ::std::string s (::boost::lexical_cast < ::std::string > (x_));
        s += "x";
        s = ::boost::lexical_cast < ::std::string > (y_);
        return s; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) type_base < ::std::string, t_sizex > :: status (s_good);
        else
        {   nits.pick (nit_sizes, es_error, ec_type, quote (s), " is neither 'any' nor a pair of positive integers separated by 'x'");
            type_base < ::std::string, t_sizex > :: status (s_invalid); } }
    void reset () noexcept { any_ = false; x_ = y_ = 0; type_base < ::std::string, t_sizex > :: reset (); }
    static ::std::string default_value () noexcept { return ::std::string (); }
    ::std::string get () const { return get_string (); } };

template < > struct type_master < t_wxhs > : type_base < ::std::string, t_wxhs >
{   typedef ::std::vector < type_master < t_sizex > > vx_t;
    vx_t value_;
    using type_base < ::std::string, t_wxhs > :: type_base;
    void swap (type_master < t_wxhs >& t) noexcept
    {   value_.swap (t.value_);
        type_base < ::std::string, t_wxhs >::swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   nits.pick (nit_sizes, es_error, ec_type, "a sizes attribute cannot be empty");
            return false; }
        vstr_t xs (split_by_space (ss));
        value_.resize (xs.size ());
        bool res = true;
        for (::std::size_t n = 0; n < xs.size (); ++n)
        {   ::gsl::at (value_, n).set_value (nits, v, ::gsl::at (xs, n));
            if (::gsl::at (value_, n).invalid ()) res = false; }
        return res; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) type_base < ::std::string, t_wxhs > :: status (s_good);
        else
        {   nits.pick (nit_sizes, es_error, ec_type, "SIZES takes a space separated sequence of values, each of which are 'any' or two positive integers separated by an 'x'");
            type_base < ::std::string, t_wxhs > :: status (s_invalid); } }
    void reset () noexcept
    {   value_.clear ();
        type_base < ::std::string, t_wxhs > :: reset (); }
    static ::std::string default_value () { return "any"; }
    ::std::string get () const noexcept { return get_string (); } };
