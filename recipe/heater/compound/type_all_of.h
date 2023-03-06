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

template < e_type T, class SZ, e_type A, e_type... B > struct type_all_of : type_all_of < T, SZ, B... >
{   using type_all_of < T, SZ, B... > :: type_all_of;
    type_master < A > val_;
    const vstr_t& get_vv () const
    {   return type_all_of < T, SZ, B... > :: get_vv (); }
    vstr_t& get_vv ()
    {   return type_all_of < T, SZ, B... > :: get_vv (); }
    void set_vv (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_all_of < T, SZ, B... > :: set_vv (nits, v, s); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::size_t i)
    {   bool res = true;
        if (i < get_vv ().size ()) 
        {   val_.set_value (nits, v, get_vv ().at (i));
            res = val_.good (); }
        return type_all_of < T, SZ, B... > :: inner_set_value (nits, v, i+1) && res; }
    void reset () noexcept
    {   val_.reset ();
        type_all_of < T, SZ, B... > :: reset (); }
    void swap (type_all_of < T, SZ, A, B... >& t) noexcept
    {   val_.swap (t.val_);
        type_all_of < T, SZ, B... > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return type_all_of < T, SZ, B... > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return type_all_of < T, SZ, B... > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static e_animation_type animation_type () noexcept
    {   e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return type_all_of < T, SZ, B... > :: animation_type (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   set_vv (nits, v, s);   
        inner_set_value (nits, v, 0); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        type_all_of < T, SZ, B... > :: verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) if (val_.verify_url (nits, v, e)) return true;
        return type_all_of < T, SZ, B... > :: verify_url (nits, v, e); }
    ::std::string get_string () const
    {   return maybe_enquote (val_.get_string ()) + SZ::sz () + type_all_of < T, SZ, B... > :: get_string (); }
    ::std::string original () const
    {   return type_all_of < T, SZ, B... > :: original (); }
    void set_id (const ::std::string& s)
    {   type_all_of < T, SZ, B... > :: set_id (s); }
    ::std::string& id () noexcept
    {   return type_all_of < T, SZ, B... > :: id (); }
    const ::std::string& id () const
    {   return type_all_of < T, SZ, B... > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) if (! val_.invalid_id (nits, v, i, e)) return false;
        return type_all_of < T, SZ, B... > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) if (! val_.invalid_access (nits, v, s)) return false;
        return type_all_of < T, SZ, B... > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) if (val_.has_id ()) return true;
        return type_all_of < T, SZ, B... > :: has_id (); }
    bool empty () const noexcept
    {   if ((! val_.unknown ()) && (! val_.empty ())) return false;
        return type_all_of < T, SZ, B... > :: empty (); }
    bool good () const noexcept
    {   if ((! val_.unknown ()) && (! val_.good ())) return false;
        return type_all_of < T, SZ, B... > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if ((! val_.unknown ()) && val_.invalid ()) return true;
        if (! val_.unknown ()) return false;
        return type_all_of < T, SZ, B... > :: invalid (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) val_.verify_id (e);
        type_all_of < T, SZ, B... > :: verify_id (e); }
    e_status status () const noexcept
    {   return type_all_of < T, SZ, B... > :: status (); }
    void status (const e_status s) noexcept
    {   type_all_of < T, SZ, B... > :: status (s); }
    bool unknown () const noexcept
    {   if (val_.unknown ()) return true;
        return type_all_of < T, SZ, B... > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return type_all_of < T, SZ, B... > :: type (); }
    void get_urls (vurl_t& vu) const noexcept
    {   const vurl_t& vv (val_.get_urls ());
        for (auto u : vv) vu.push_back (u);
        type_all_of < T, SZ, B... > :: get_urls (vu); }
    vurl_t get_urls () const noexcept
    {   vurl_t vu;
        get_urls (vu);
        return vu; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
//    template < e_type X > type_master < X > get () const
//    {   if (val_.has_value < X > (X ())) return val_.get < X > ();
//        return type_all_of < T, SZ, B... > :: get < X > (); }
    int get_int () const noexcept
    {   return type_all_of < T, SZ, B... > :: get_int (); }
//    template < e_type X > bool has_value (const X x) const
//    {   if (val_.has_value < X > (x)) return true;
//        return type_all_of < T, SZ, B... > :: has_value < X > (x); }
    ::std::size_t size () const noexcept
    {   return type_all_of < T, SZ, B... > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        type_all_of < T, SZ, B... > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return type_all_of < T, SZ, B... > :: box (); }
    element* box () const noexcept
    {   return type_all_of < T, SZ, B... > :: box (); }
    void box (element* b) noexcept
    {   type_all_of < T, SZ, B... > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        else type_all_of < T, SZ, B... > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_of < T, SZ, B... > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_of < T, SZ, B... > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_of < T, SZ, B... > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   ::std::string res;
        if (! val_.unknown ()) res += val_.report ();
        res += type_all_of < T, SZ, B... > :: report ();
        return res; } };

template < e_type T, class SZ, e_type A > struct type_all_of < T, SZ, A > : string_vector < T, SZ >
{   using string_vector < T, SZ > :: string_vector;
    type_master < A > val_;
    const vstr_t& get_vv () const
    {   return string_vector < T, SZ > :: get (); }
    vstr_t& get_vv ()
    {   return string_vector < T, SZ > :: value_; }
    void set_vv (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ > :: set_value (nits, v, s); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::size_t i)
    {   const vstr_t& vv = get_vv (); 
        if (i >= vv.size ())
        {   nits.pick (nit_precisely, es_error, ec_type, "too few (", vv.size (), ") values provided, but ", i+1, " expected (", type_name (T), ")");
            string_vector < T, SZ > :: status (s_invalid);
            return false; }
        if (i + 1 < vv.size ())
            nits.pick (nit_precisely, es_warning, ec_type, "too many (", vv.size (), ") values provided, only ", i+1, " expected (", type_name (T), ")");
        val_.set_value (nits, v, vv.at (i));
        return val_.good (); }
    void reset () noexcept
    {   val_.reset ();
        string_vector < T, SZ > :: reset (); }
    void swap (type_all_of < T, SZ, A >& t) noexcept
    {   val_.swap (t.val_);
        string_vector < T, SZ > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return string_vector < T, SZ > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return string_vector < T, SZ > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static e_animation_type animation_type () noexcept
    {   e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return string_vector < T, SZ > :: animation_type (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   set_vv (nits, v, s);   
        inner_set_value (nits, v, 0); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        string_vector < T, SZ > ::verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) if (val_.verify_url (nits, v, e)) return true;
        return string_vector < T, SZ > ::verify_url (nits, v, e); }
    ::std::string get_string () const
    {   return maybe_enquote (val_.get_string ()); }
    ::std::string original () const
    {   return string_vector < T, SZ > :: original (); }
    ::std::string& id () noexcept
    {   return string_vector < T, SZ > :: id (); }
    const ::std::string& id () const
    {   return string_vector < T, SZ > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) if (! val_.invalid_id (nits, v, i, e)) return false;
        return string_vector < T, SZ > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) if (! val_.invalid_access (nits, v, s)) return false;
        return string_vector < T, SZ > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) if (val_.has_id ()) return true;
        return string_vector < T, SZ > :: has_id (); }
    bool empty () const noexcept
    {   if ((! val_.unknown ()) && (! val_.empty ())) return false;
        return string_vector < T, SZ > :: empty (); }
    bool good () const noexcept
    {   if ((! val_.unknown ()) && (! val_.good ())) return false;
        return string_vector < T, SZ > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if ((! val_.unknown ()) && val_.invalid ()) return true;
        return string_vector < T, SZ > :: invalid (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) val_.verify_id (e);
        string_vector < T, SZ > :: verify_id (e); }
    e_status status () const noexcept
    {   return string_vector < T, SZ > :: status (); }
    void status (const e_status s) noexcept
    {   string_vector < T, SZ > :: status (s); }
    bool unknown () const noexcept
    {   if (val_.unknown ()) return true;
        return string_vector < T, SZ > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return string_vector < T, SZ > :: type (); }
    void get_urls (vurl_t& vu) const noexcept
    {   const vurl_t& vv (val_.get_urls ());
        for (auto u : vv) vu.push_back (u);
        string_vector < T, SZ >  :: get_urls (vu); }
    vurl_t get_urls () const noexcept
    {   vurl_t vu;
        get_urls (vu);
        return vu; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
//    template < typename X > type_master < X > get () const
//    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const noexcept
    {   return string_vector < T, SZ > :: get_int (); }
//    template < typename X > bool has_value (const X x) const
//    {   return string_vector < T, SZ > :: has_value (x); }
    ::std::size_t size () const noexcept
    {   return string_vector < T, SZ > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        string_vector < T, SZ > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return string_vector < T, SZ > :: box (); }
    element* box () const noexcept
    {   return string_vector < T, SZ > :: box (); }
    void box (element* b) noexcept
    {   string_vector < T, SZ > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        string_vector < T, SZ > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        else string_vector < T, SZ > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        string_vector < T, SZ > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        string_vector < T, SZ > :: accumulate (st, e); }
    static void accumulate (stats_t* st, const ::std::string& s)
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   if (! val_.unknown ()) val_.report ();
        else string_vector < T, SZ > :: report (); } };
 
