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
#include "parser/parse_elements.h"
#include "main/args.h"
#include "base/type_master.h"

template < e_type T, class SZ, class... SZs > struct type_sz : type_sz < T, SZs... >
{   using type_sz < T, SZs... > :: type_sz;
    bool val_ = false;
    void reset () noexcept
    {   val_ = false;
        type_sz < T, SZs... > :: reset (); }
    void swap (type_sz < T, SZ, SZs... >& t) noexcept
    {   ::std::swap (t.val_, val_);
        type_sz < T, SZs... > :: swap (t); }
    ::std::string get_string () const
    {   if (val_) return SZ::sz ();
        return type_sz < T, SZs... > :: get_string (); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& err)
    {   nitpick nuts;
        if (compare_complain (nuts, v, s, SZ::sz ()))
        {   nits.merge (nuts);
            status (s_good);
            val_ = true;
            return true; }
        else if (type_sz < T, SZs... > :: inner_set_value (nits, v, s, err))
            return true;
        err = quote (SZ::sz ()) + ", " + err;
        return false; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string err, ss (tart (s));
        if (! inner_set_value (nits, v, ss, err))
             nits.pick (nit_unrecognised_value, es_error, ec_type, quote (ss), " is invalid; possible values are: ", err); }
    void set_id (const ::std::string& s)
    {   type_sz < T, SZs... > :: set_id (s); }
    ::std::string& id () noexcept
    {   return type_sz < T, SZs... > :: id (); }
    const ::std::string& id () const
    {   return type_sz < T, SZs... > :: id (); }
    bool good () const noexcept
    {   if (val_) return true;
        return type_sz < T, SZs... > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if (val_) return false;
        return type_sz < T, SZs... > :: invalid (); }
    e_status status () const noexcept
    {   return type_sz < T, SZs... > :: status (); }
    void status (const e_status s) noexcept
    {   type_sz < T, SZs... > :: status (s); }
    bool unknown () const noexcept
    {   if (val_) return false;
        return type_sz < T, SZs... > :: unknown (); }
    int get_int () const noexcept
    {   if (val_) return 1;
        return type_sz < T, SZs... > :: get_int (); }
    ::std::size_t size () const noexcept
    {   if (val_) return 1;
        return type_sz < T, SZs... > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (val_) ss << SZ::sz ();
        else type_sz < T, SZs... > :: shadow (ss, v, e); }
    ::std::string report () const
    {   if (val_) return SZ::sz ();
        else type_sz < T, SZs... > :: report (); } };

template < e_type T, class SZ > struct type_sz < T, SZ > : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    bool val_ = false;
    void reset () noexcept
    {   val_ = false;
        tidy_string < T > :: reset (); }
    void swap (type_sz < T, SZ >& t) noexcept
    {   ::std::swap (val_, t.val_);
        tidy_string < T > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   return false; }
    static bool is_url () noexcept
    {   return false; }
    static bool is_existential () noexcept
    {   return false; }
    static e_animation_type animation_type () noexcept
    {   return at_none; }
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
    bool verify_url (nitpick& , const html_version& , element& )
    {   return true; }
    ::std::string get_string () const
    {   if (val_) return SZ::sz ();
        return tidy_string < T > :: get_string (); }
    ::std::string original () const
    {   return tidy_string < T > :: original (); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& err)
    {   if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "attribute cannot have an empty value (", type_name (T), ")");
            status (s_invalid);
            return true; }
        nitpick nuts;
        if (compare_complain (nuts, v, s, SZ::sz ()))
        {   nits.merge (nuts);
            status (s_good);
            val_ = true;
            return true; }
        status (s_invalid);
        err = quote (SZ::sz ());
        return false; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string err, ss (tart (s));
        if (! inner_set_value (nits, v, ss, err))
             nits.pick (nit_unrecognised_value, es_error, ec_type, quote (ss), " is invalid; the only possible value is ", err); }
    ::std::string& id () noexcept
    {   return tidy_string < T > :: id (); }
    const ::std::string& id () const
    {   return tidy_string < T > :: id (); }
    bool good () const noexcept
    {   return val_; }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   return val_; }
    void verify_id (element& ) { }
    e_status status () const noexcept
    {   return tidy_string < T > :: status (); }
    void status (const e_status s) noexcept
    {   tidy_string < T > :: status (s); }
    bool unknown () const noexcept
    {   return ! val_; }
    ::std::size_t type () const noexcept
    {   return tidy_string < T > :: type (); }
    vurl_t get_urls () const noexcept
    {   return vurl_t (); }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const noexcept
    {   return val_ ? 1 : 0; }
    ::std::size_t size () const noexcept
    {   return val_ ? 1 : 0; }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   if (val_) ss << SZ::sz (); }
    element* box () noexcept
    {   return tidy_string < T > :: box (); }
    element* box () const noexcept
    {   return tidy_string < T > :: box (); }
    void box (element* b) noexcept
    {   tidy_string < T > :: box (b); }
    void validate () { }
    void accumulate (stats_t* ) const { }
    void accumulate (stats_t* , const e_element ) const { }
    void accumulate (stats_t* , const element_bitset& ) const { }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   if (val_) return SZ::sz ();
        return tidy_string < T > :: report (); } };
