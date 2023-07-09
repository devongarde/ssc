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

template < e_type T, class SZ, int F, e_type A, e_type... B > struct type_all_flagged_of : type_all_flagged_of < T, SZ, F, B... >
{   using type_all_flagged_of < T, SZ, F, B... > :: type_all_flagged_of;
    type_master < A > val_;
    const vstr_t& get_vv () const
    {   return type_all_flagged_of < T, SZ, F, B... > :: get_vv (); }
    vstr_t& get_vv ()
    {   return type_all_flagged_of < T, SZ, F, B... > :: get_vv (); }
    void set_vv (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_all_flagged_of < T, SZ, F, B... > :: set_vv (nits, v, s); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::size_t i)
    {   bool res = true;
        if (i < get_vv ().size ()) 
        {   val_.set_value (nits, v, get_vv ().at (i));
            res = val_.good (); }
        return type_all_flagged_of < T, SZ, F, B... > :: inner_set_value (nits, v, i+1) && res; }
    void reset () noexcept
    {   val_.reset ();
        type_all_flagged_of < T, SZ, F, B... > :: reset (); }
    void swap (type_all_flagged_of < T, SZ, F, A, B... >& t) noexcept
    {   val_.swap (t.val_);
        type_all_flagged_of < T, SZ, F, B... > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static bool is_numeric () noexcept
    {   if ( type_master < A > :: is_numeric ()) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: is_numeric (); }
    static e_animation_type animation_type () noexcept
    {   const e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return type_all_flagged_of < T, SZ, F, B... > :: animation_type (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   set_vv (nits, v, s);   
        inner_set_value (nits, v, 0); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        type_all_flagged_of < T, SZ, F, B... > :: verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) if (val_.verify_url (nits, v, e)) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: verify_url (nits, v, e); }
    ::std::string get_string () const
    {   return maybe_enquote (val_.get_string ()) + SZ::sz () + type_all_flagged_of < T, SZ, F, B... > :: get_string (); }
    ::std::string original () const
    {   return type_all_flagged_of < T, SZ, F, B... > :: original (); }
    void set_id (const ::std::string& s)
    {   type_all_flagged_of < T, SZ, F, B... > :: set_id (s); }
    ::std::string& id () noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: id (); }
    const ::std::string& id () const
    {   return type_all_flagged_of < T, SZ, F, B... > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) if (! val_.invalid_id (nits, v, i, e)) return false;
        return type_all_flagged_of < T, SZ, F, B... > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) if (! val_.invalid_access (nits, v, s)) return false;
        return type_all_flagged_of < T, SZ, F, B... > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) if (val_.has_id ()) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: has_id (); }
    bool empty () const noexcept
    {   if ((! val_.unknown ()) && (! val_.empty ())) return false;
        return type_all_flagged_of < T, SZ, F, B... > :: empty (); }
    bool good () const noexcept
    {   if ((! val_.unknown ()) && (! val_.good ())) return false;
        return type_all_flagged_of < T, SZ, F, B... > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if ((! val_.unknown ()) && val_.invalid ()) return true;
        if (! val_.unknown ()) return false;
        return type_all_flagged_of < T, SZ, F, B... > :: invalid (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) val_.verify_id (e);
        type_all_flagged_of < T, SZ, F, B... > :: verify_id (e); }
    e_status status () const noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: status (); }
    void status (const e_status s) noexcept
    {   type_all_flagged_of < T, SZ, F, B... > :: status (s); }
    bool unknown () const noexcept
    {   if (val_.unknown ()) return true;
        return type_all_flagged_of < T, SZ, F, B... > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: type (); }
    void get_urls (vurl_t& vu) const noexcept
    {   const vurl_t& vv (val_.get_urls ());
        for (auto u : vv) vu.push_back (u);
        type_all_flagged_of < T, SZ, F, B... > :: get_urls (vu); }
    vurl_t get_urls () const
    {   vurl_t vu;
        get_urls (vu);
        return vu; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: get_int (); }
    ::std::size_t size () const noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        type_all_flagged_of < T, SZ, F, B... > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: box (); }
    element* box () const noexcept
    {   return type_all_flagged_of < T, SZ, F, B... > :: box (); }
    void box (element* b) noexcept
    {   type_all_flagged_of < T, SZ, F, B... > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        else type_all_flagged_of < T, SZ, F, B... > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_flagged_of < T, SZ, F, B... > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_flagged_of < T, SZ, F, B... > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        type_all_flagged_of < T, SZ, F, B... > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   ::std::string res;
        if (! val_.unknown ()) res += val_.report ();
        res += type_all_flagged_of < T, SZ, F, B... > :: report ();
        return res; } };

template < e_type T, class SZ, int F, e_type A > struct type_all_flagged_of < T, SZ, F, A > : string_vector < T, SZ, F >
{   using string_vector < T, SZ, F > :: string_vector;
    type_master < A > val_;
    const vstr_t& get_vv () const
    {   return string_vector < T, SZ, F > :: get (); }
    vstr_t& get_vv ()
    {   return string_vector < T, SZ, F > :: value_; }
    void set_vv (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < T, SZ, F > :: set_value (nits, v, s); }
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::size_t i)
    {   const vstr_t& vv = get_vv (); 
        if (i >= vv.size ())
        {   if (vv.size () == 0) nits.pick (nit_precisely, es_error, ec_type, "no values provided when ", i+1, " expected (", type_name (T), ")");
            else nits.pick (nit_precisely, es_warning, ec_type, "possibly only ", vv.size (), " values provided (such as ", quote (vv.at (0)), ") when ", i+1, " expected (", type_name (T), ")");
            string_vector < T, SZ, F > :: status (s_invalid);
            return false; }
        if (i + 1 < vv.size ())
            nits.pick (nit_precisely, es_warning, ec_type, "too many (", vv.size (), ") values provided, only ", i+1, " expected (", type_name (T), ")");
        val_.set_value (nits, v, vv.at (i));
        return val_.good (); }
    void reset () noexcept
    {   val_.reset ();
        string_vector < T, SZ, F > :: reset (); }
    void swap (type_all_flagged_of < T, SZ, F, A >& t) noexcept
    {   val_.swap (t.val_);
        string_vector < T, SZ, F > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return string_vector < T, SZ, F > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return string_vector < T, SZ, F > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static e_animation_type animation_type () noexcept
    {  const e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return string_vector < T, SZ, F > :: animation_type (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   set_vv (nits, v, s);   
        inner_set_value (nits, v, 0); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        string_vector < T, SZ, F > ::verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) if (val_.verify_url (nits, v, e)) return true;
        return string_vector < T, SZ, F > ::verify_url (nits, v, e); }
    ::std::string get_string () const
    {   return maybe_enquote (val_.get_string ()); }
    ::std::string original () const
    {   return string_vector < T, SZ, F > :: original (); }
    ::std::string& id () noexcept
    {   return string_vector < T, SZ, F > :: id (); }
    const ::std::string& id () const
    {   return string_vector < T, SZ, F > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) if (! val_.invalid_id (nits, v, i, e)) return false;
        return string_vector < T, SZ, F > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) if (! val_.invalid_access (nits, v, s)) return false;
        return string_vector < T, SZ, F > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) if (val_.has_id ()) return true;
        return string_vector < T, SZ, F > :: has_id (); }
    bool empty () const noexcept
    {   if ((! val_.unknown ()) && (! val_.empty ())) return false;
        return string_vector < T, SZ, F > :: empty (); }
    bool good () const noexcept
    {   if ((! val_.unknown ()) && (! val_.good ())) return false;
        return string_vector < T, SZ, F > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if ((! val_.unknown ()) && val_.invalid ()) return true;
        return string_vector < T, SZ, F > :: invalid (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) val_.verify_id (e);
        string_vector < T, SZ, F > :: verify_id (e); }
    e_status status () const noexcept
    {   return string_vector < T, SZ, F > :: status (); }
    void status (const e_status s) noexcept
    {   string_vector < T, SZ, F > :: status (s); }
    bool unknown () const noexcept
    {   if (val_.unknown ()) return true;
        return string_vector < T, SZ, F > :: unknown (); }
    ::std::size_t type () const noexcept
    {   return string_vector < T, SZ, F > :: type (); }
    void get_urls (vurl_t& vu) const
    {   vu = val_.get_urls ();
        for (auto ou : string_vector < T, SZ, F > :: get_urls ())
            vu.emplace_back (ou); }
    vurl_t get_urls () const
    {   vurl_t vu;
        get_urls (vu);
        return vu; }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const
    {   return string_vector < T, SZ, F > :: get_int (); }
    ::std::size_t size () const noexcept
    {   return string_vector < T, SZ, F > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        string_vector < T, SZ, F > :: shadow (ss, v, e); }
    element* box () noexcept
    {   return string_vector < T, SZ, F > :: box (); }
    element* box () const noexcept
    {   return string_vector < T, SZ, F > :: box (); }
    void box (element* b) noexcept
    {   string_vector < T, SZ, F > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        string_vector < T, SZ, F > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        else string_vector < T, SZ, F > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        string_vector < T, SZ, F > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        string_vector < T, SZ, F > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   if (! val_.unknown ()) return val_.report ();
        return string_vector < T, SZ, F > :: report (); } };

template < e_type T, class SZ, e_type... A > struct type_all_of : type_all_flagged_of < T, SZ, BS_FN, A... >
{   using type_all_flagged_of < T, SZ, BS_FN, A... > :: type_all_flagged_of; };
