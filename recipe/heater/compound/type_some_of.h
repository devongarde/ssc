/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
{   static bool ok (nitpick& nits, const ::std::size_t vs, const ::std::string& s)
    {   if ((vs >= MIN) && ((MAX == 0) || (vs <= MAX))) return true;
        nits.pick (nit_range, es_error, ec_type, quoted_limited_string (s, short_quote_cut), ": ", vs, " value/s found, but between ", MIN, " and ", MAX, " value expected (", type_name (T), ")");
        return false; } };

template < e_type T, ::std::size_t MAX > struct range_ok < T, MAX, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs, const ::std::string& s)
    {   if ((MAX == 0) || (vs <= MAX)) return true;
        nits.pick (nit_at_most, es_error, ec_type, quoted_limited_string (s, short_quote_cut), ": ", vs, " value/s found, but at most ", MAX, " value/s expected (", type_name (T), ")");
        return false; } };
 
template < e_type T, ::std::size_t MIN, ::std::size_t MAX, ::std::size_t DIFF > struct precisely_ok : range_ok < T, MAX, MIN >
{   using range_ok < T, MAX, MIN > :: range_ok; };

template < e_type T, ::std::size_t MIN, ::std::size_t MAX > struct precisely_ok < T, MIN, MAX, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs, const ::std::string& s)
    {   if (vs == MIN) return true;
        nits.pick (nit_precisely, es_error, ec_type, quoted_limited_string (s, short_quote_cut), ": ", vs, " value/s found, but ", MIN, " value/s expected (", type_name (T), ")");
        return false; } };
 
template < e_type T, ::std::size_t MIN, ::std::size_t MAX > struct min_max_ok : precisely_ok < T, MIN, MAX, MAX-MIN >
{   using precisely_ok < T, MIN, MAX, MAX-MIN > :: precisely_ok; };
 
template < e_type T, ::std::size_t MIN > struct min_max_ok < T, MIN, 0 >
{   static bool ok (nitpick& nits, const ::std::size_t vs, const ::std::string& s)
    {   if (vs >= MIN) return true;
        nits.pick (nit_at_least, es_error, ec_type, quoted_limited_string (s, short_quote_cut), ": ", vs, " value/s found, but at least ", MIN, " value/s expected (", type_name (T), ")");
        return false; } };

template < e_type T > struct min_max_ok < T, 0, 0 >
{   static bool ok (nitpick& , const ::std::size_t , const ::std::string& ) { return true; } };

 
template < e_type T, class SZ, int F, int MIN, int MAX, e_type... A > struct type_some_flagged_of : string_vector < T, SZ, F > 
{   BOOST_STATIC_ASSERT ((MAX == 0) || (MIN <= MAX));
    using string_vector < T, SZ, F > :: string_vector;
    typedef ::std::vector < type_one_of < T, MIN==0, A... > > voo;
    voo voo_;
    void reset () noexcept
    {   voo_.clear ();
        string_vector < T, SZ, F > :: reset (); }
    void swap (type_some_flagged_of < T, SZ, F, MIN, MAX, A... >& t) noexcept
    {   voo_.swap (t.voo_);
        string_vector < T, SZ, F > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   return type_one_of < T, MIN==0, A... > :: is_relational (); }   
    static bool is_url () noexcept
    {   if (type_one_of < T, MIN==0, A... > :: is_url ()) return true;
        return string_vector < T, SZ, F > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static bool is_numeric ()
    {   if (type_one_of < T, MIN==0, A... > :: is_numeric ()) return true;
        return string_vector < T, SZ, F > :: is_numeric (); }
    static typename string_vector < T, SZ, F > :: value_type default_value ()
    {   return string_vector < T, SZ, F > :: default_value (); }
    static e_animation_type animation_type () noexcept
    {   const e_animation_type a = type_one_of < T, MIN==0, A... > :: animation_type ();
        if (a != at_none) return a;
        return string_vector < T, SZ, F > :: animation_type (); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.verify_attribute (nits, v, e, p, s);
        string_vector < T, SZ, F > :: verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.verify_url (nits, v, e))
                    return true;
        return string_vector < T, SZ, F > :: verify_url (nits, v, e); }
    ::std::string get_string () const
    {   ::std::string res;
        for (auto oo : voo_)
            if (! oo.unknown ())
            {   if (! res.empty ()) res += SZ::sz ();
                res += oo.get_string (); }
        if (! res.empty ()) return res;
        return string_vector < T, SZ, F > :: get_string (); }
    ::std::string original () const
    {   return string_vector < T, SZ, F > :: original (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ, F > :: set_value (nits, v, s);
        if (string_vector < T, SZ, F > :: empty ())
        {   string_vector < T, SZ, F > :: status (emptiness < T, MIN==0 > :: content_status (nits, string_vector < T, SZ, F > :: get ()));
            return; }
        bool good = true;
        nitpick nuts, awful, great;
        for (::std::string ss : string_vector < T, SZ, F > :: value_)
        {   nitpick knots;
            type_one_of < T, MIN==0, A... > one;
            one.set_value (knots, v, ss);
            if (! one.good ()) { awful.merge (knots); good = false; }
            else if (good) great.merge (knots);
            voo_.push_back (one); }
        if (! min_max_ok < T, MIN, MAX > :: ok (nuts, voo_.size (), s))
        {   awful.merge (nuts); good = false; }
        else if (good) great.merge (nuts);
        if (good)
        {   string_vector < T, SZ, F > :: status (s_good);
            nits.merge (great);
            return; }
        nits.merge (awful);
        string_vector < T, SZ, F > :: status (s_invalid); }
    void set_id (const ::std::string& s)
    {   string_vector < T, SZ, F > :: set_id (s); }
    ::std::string& id () noexcept
    {   return string_vector < T, SZ, F > :: id (); }
    const ::std::string& id () const
    {   return string_vector < T, SZ, F > :: id (); }
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
        return string_vector < T, SZ, F > :: has_id (); }
    bool empty () const noexcept
    {   if (voo_.empty ()) return true;
        return string_vector < T, SZ, F > :: empty (); }
    bool good () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (! oo.good ()) return false;
        return string_vector < T, SZ, F > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                if (oo.invalid ()) return true;
        return string_vector < T, SZ, F > :: invalid (); }
    void verify_id (element& e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.verify_id (e); }
    e_status status () const noexcept
    {   return string_vector < T, SZ, F > :: status (); }
    void status (const e_status s) noexcept
    {   string_vector < T, SZ, F > :: status (s); }
    bool unknown () const noexcept
    {   for (auto oo : voo_)
            if (! oo.unknown ()) return false;
        return string_vector < T, SZ, F > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return T; }
    vurl_t get_urls () const
    {   vurl_t res;
        for (auto oo : voo_)
            if (! oo.unknown ())
                for (auto ou : oo.get_urls ())
                    res.emplace_back (ou);
        for (auto ou : string_vector < T, SZ, F > :: get_urls ())
            res.emplace_back (ou);
        return res; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const
    {   return string_vector < T, SZ, F > :: get_int (); }
    ::std::size_t size () const noexcept
    {   return voo_.size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.shadow (ss, v, e);
        string_vector < T, SZ, F > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return string_vector < T, SZ, F > :: box (); }
    element* box () const noexcept
    {   return string_vector < T, SZ, F > :: box (); }
    void box (element* b) noexcept
    {   string_vector < T, SZ, F > :: box (b); }
    void argue (nitpick& nits, arguments* a)
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.argue (nits, a);
        string_vector < T, SZ, F > :: argue (nits, a); }
    void validate ()
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.validate ();
        string_vector < T, SZ, F > :: validate (); }
    void accumulate (stats_t* st) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st);
        string_vector < T, SZ, F > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st, e);
        string_vector < T, SZ, F > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   for (auto oo : voo_)
            if (! oo.unknown ())
                oo.accumulate (st, e);
        string_vector < T, SZ, F > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   ::std::string res;
        for (auto oo : voo_)
            if (! oo.unknown ())
                res += oo.report ();
        return res + string_vector < T, SZ, F > :: report (); } };

template < e_type T, class SZ, int MIN, int MAX, e_type... A > struct type_some_of : type_some_flagged_of < T, SZ, BS_FN, MIN, MAX, A... >
{   using type_some_flagged_of < T, SZ, BS_FN, MIN, MAX, A... > :: type_some_flagged_of; };
