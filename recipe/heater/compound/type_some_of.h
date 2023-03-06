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
#include "compound/type_one_of.h"

template < e_type T, ::std::size_t MAX, ::std::size_t MIN > struct range_ok
{   static bool ok (nitpick& nits, const ::std::size_t vs)
    {   if ((vs >= MIN) && (vs <= MAX)) return true;
        nits.pick (nit_range, es_error, ec_type, vs, " values found, but between ", MIN, " and ", MAX, " value expected (", type_name (T), ")");
        return false; } };

template < e_type T, ::std::size_t MAX > struct range_ok < T, MAX, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs)
    {   if (vs <= MAX) return true;
        nits.pick (nit_at_most, es_error, ec_type, vs, " values found, but at most ", MAX, " value(s) expected (", type_name (T), ")");
        return false; } };
 
template < e_type T, ::std::size_t MIN, ::std::size_t MAX, ::std::size_t DIFF > struct precisely_ok : range_ok < T, MAX, MIN >
{   using range_ok < T, MAX, MIN > :: range_ok; };

template < e_type T, ::std::size_t MIN, ::std::size_t MAX > struct precisely_ok < T, MIN, MAX, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs)
    {   if (vs == MIN) return true;
        nits.pick (nit_precisely, es_error, ec_type, vs, " values found, but ", MIN, " value(s) expected (", type_name (T), ")");
        return false; } };
 
template < e_type T, ::std::size_t MIN, ::std::size_t MAX > struct min_max_ok : precisely_ok < T, MIN, MAX, MAX-MIN >
{   using precisely_ok < T, MIN, MAX, MAX-MIN > :: precisely_ok; };
 
template < e_type T, ::std::size_t MIN > struct min_max_ok < T, MIN, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs)
    {   if (vs >= MIN) return true;
        nits.pick (nit_at_least, es_error, ec_type, vs, " values found, but at least ", MIN, " value(s) required (", type_name (T), ")");
        return false; } };

template < e_type T > struct min_max_ok < T, 0, 0 >
{   static bool ok (nitpick& , const ::std::size_t ) { return true; } };

 
template < e_type T, class SZ, int MIN, int MAX, e_type... A > struct type_some_of : string_vector < T, SZ > 
{   using string_vector < T, SZ > :: string_vector;
    typedef ::std::vector < type_one_of < T, MIN==0, A... > > voo;
    voo voo_;
    void reset () noexcept
    {   voo_.clear ();
        string_vector < T, SZ > :: reset (); }
    void swap (type_some_of < T, SZ, MIN, MAX, A... >& t) noexcept
    {   voo_.swap (t.voo_);
        string_vector < T, SZ > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   return type_one_of < T, MIN==0, A... > :: is_relational (); }   
    static bool is_url () noexcept
    {   if (type_one_of < T, MIN==0, A... > :: is_url ()) return true;
        return string_vector < T, SZ > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static typename string_vector < T, SZ > :: value_type default_value ()
    {   return string_vector < T, SZ > :: default_value (); }
    static e_animation_type animation_type () noexcept
    {   e_animation_type a = type_one_of < T, MIN==0, A... > :: animation_type ();
        if (a != at_none) return a;
        return string_vector < T, SZ > :: animation_type (); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.verify_attribute (nits, v, e, p, s);
        string_vector < T, SZ > :: verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.verify_url (nits, v, e))
                    return true;
        return string_vector < T, SZ > :: verify_url (nits, v, e); }
    ::std::string get_string () const
    {   ::std::string res;
        for (auto oo : voo_)
            if (! oo.unknown ())
            {   if (! res.empty ()) res += SZ::sz ();
                res += oo.get_string (); }
        if (! res.empty ()) return res;
        return string_vector < T, SZ > :: get_string (); }
    ::std::string original () const
    {   return string_vector < T, SZ > :: original (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s);
        if (string_vector < T, SZ > :: empty ())
        {   string_vector < T, SZ > :: status (emptiness < T, MIN==0 > :: content_status (nits, string_vector < T, SZ > :: get ()));
            return; }
//        {   if (emptiness < T, MIN==0 > :: could_be_empty (string_vector < T, SZ > :: status ()))
//            {   string_vector < T, SZ > :: status (s_empty);
//                return; } }
        bool ok = true;
        for (::std::string ss : string_vector < T, SZ > :: value_)
        {   type_one_of < T, MIN==0, A... > one;
            one.set_value (nits, v, ss);
            if (! one.good ()) ok = false;
            voo_.push_back (one); }
        if (! min_max_ok < T, MIN, MAX > :: ok (nits, voo_.size ())) ok = false;
        if (ok)
        {   string_vector < T, SZ > :: status (s_good);
            return; }
        string_vector < T, SZ > :: status (s_invalid); }
    void set_id (const ::std::string& s)
    {   string_vector < T, SZ > :: set_id (s); }
    ::std::string& id () noexcept
    {   return string_vector < T, SZ > :: id (); }
    const ::std::string& id () const
    {   return string_vector < T, SZ > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   bool res = false;
        for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.invalid_id (nits, v, i, e))
                    res = true;
        return res; }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   bool res = false;
        for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.invalid_access (nits, v, s))
                    res = true;
        return res; }
    bool has_id () const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.has_id ())
                    return true;
        return string_vector < T, SZ > :: has_id (); }
    bool empty () const noexcept
    {   if (voo_.empty ()) return true;
        return string_vector < T, SZ > :: empty (); }
    bool good () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (! oo.good ()) return false;
        return string_vector < T, SZ > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.invalid ()) return true;
        return string_vector < T, SZ > :: invalid (); }
    void verify_id (element& e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.verify_id (e); }
    e_status status () const noexcept
    {   return string_vector < T, SZ > :: status (); }
    void status (const e_status s) noexcept
    {   string_vector < T, SZ > :: status (s); }
    bool unknown () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ()) return false;
        return string_vector < T, SZ > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return T; }
    vurl_t get_urls () const noexcept
    {   vurl_t res;
        for (auto oo : voo_)
            if (! oo.unknown ())
                for (auto ou : oo.get_urls ())
                    res.emplace_back (ou);
        for (auto ou : string_vector < T, SZ > :: get_urls ())
            res.emplace_back (ou);
        return res; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
//    template < e_type X > type_master < X > get () const
//    {   if (voo_.has_value < X > (X ())) return voo_.get < X > ();
//        return string_vector < T, SZ > :: get < X > (); }
    int get_int () const noexcept
    {   return string_vector < T, SZ > :: get_int (); }
//    template < e_type X > bool has_value (const X x) const
//    {   if (voo_.has_value < X > (x)) return true;
//        return string_vector < T, SZ > :: has_value < X > (x); }
    ::std::size_t size () const noexcept
    {   return voo_.size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.shadow (ss, v, e);
        string_vector < T, SZ > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return string_vector < T, SZ > :: box (); }
    element* box () const noexcept
    {   return string_vector < T, SZ > :: box (); }
    void box (element* b) noexcept
    {   string_vector < T, SZ > :: box (b); }
    void validate ()
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.validate ();
        string_vector < T, SZ > :: validate (); }
    void accumulate (stats_t* st) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st);
        string_vector < T, SZ > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st, e);
        string_vector < T, SZ > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st, e);
        string_vector < T, SZ > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   ::std::string res;
        for (auto oo : voo_)
            if (! oo.unknown ())
                res += oo.report ();
        return res + string_vector < T, SZ > :: report (); } };
