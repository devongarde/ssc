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
#include "type/type_enum.h"

template < > struct type_master < t_dosh > : tidy_string < t_dosh >
{   typedef double value_type, base_type;
    double value_ = 0.0;
    e_currency unit_ = e_iso_context;
    type_master () = default;
    void swap (type_master < t_dosh >& t) NOEXCEPT
    {   ::std::swap (value_, t.value_);
        ::std::swap (unit_, t.unit_);
        tidy_string < t_dosh > :: swap (t); }
    bool parse (const html_version& v, const ::std::string& s) // see http://microformats.org/wiki/h-listing
    {   const vstr_t args (split_by_space (s));
        if (args.size () > 2) return false;
        ::std::string amount;
        if (args.size () == 1) amount = trim_the_lot_off (args [0]);
        if (args.size () == 2)
        {   const ::std::string c (args [0]);
            if (symbol < e_currency > :: find (v, args [0], unit_)) amount = trim_the_lot_off (args [1]);
            else if (! symbol < e_currency > :: find (v, amount, unit_)) return false; }
        if (amount.empty ()) return false;
        bool res = false;
        value_ = lexical < double > :: cast2 (amount, res);
        return res; }
    bool has_value (const base_type& d) const { return d == value_; }
    int get_int () const { return static_cast < int > (value_ + 0.5); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_dosh > :: set_value (nits, v, s);
        const ::std::string& val (tidy_string < t_dosh > :: get_string ());
        if (! parse (v, val))
        {   nits.pick (nit_bad_money, es_error, ec_type, quote (val), " is not a valid amount of money, for example 'EUR 3.14' (see ISO 4217)");
            tidy_string < t_dosh > :: status (s_invalid); } } };

template < > struct type_master < t_unsigned_dosh > : type_master < t_dosh >
{    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_dosh > :: set_value (nits, v, s);
        if (type_master < t_dosh > :: good ())
            if (type_master < t_dosh > :: value_ < 0.0)
            {   nits.pick (nit_negative_dosh, es_warning, ec_type, quote (s), " is negative");
                type_master < t_dosh > :: status (s_invalid); } } };
