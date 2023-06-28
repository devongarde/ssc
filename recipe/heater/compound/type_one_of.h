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

template < e_type T, bool EMPTY > struct emptiness
{   static bool could_be_empty (const e_status ) { return false; }
    static e_status content_status (nitpick& nits, const ::std::string& s)
    {   if (! s.empty ()) return s_good;   
        nits.pick (nit_empty, es_error, ec_type, "values of ", type_name (T), " may be neither empty nor blank");
        return s_invalid; }
    static e_status content_status (nitpick& nits, const vstr_t& s)
    {   if (! s.empty ()) return s_good;   
        nits.pick (nit_empty, es_error, ec_type, "values of ", type_name (T), " may be neither empty nor blank");
        return s_invalid; } };

template < e_type T > struct emptiness < T, true > 
{   constexpr static bool could_be_empty (const e_status s) { return s == s_empty; }
    static e_status content_status (nitpick& , const ::std::string& s)
    {   if (! s.empty ()) return s_good;
        return s_empty; }
    static e_status content_status (nitpick& , const vstr_t& s)
    {   if (! s.empty ()) return s_good;
        return s_empty; } };

template < e_type T, bool EMPTY, e_type A, e_type... B > struct type_one_of : type_one_of < T, EMPTY, B... >
{   using type_one_of < T, EMPTY, B... > :: type_one_of;
    type_master < A > val_;
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   nitpick nuts, nets;
        if (type_one_of < T, EMPTY, B... > :: inner_set_value (nuts, v, s)) 
        {   nits.merge (nuts); return true; }
        val_.set_value (nets, v, s);
        if (val_.good ())
        {   type_one_of < T, EMPTY, B... > :: status (s_good);
            nits.merge (nets);
            return true; }
        if (emptiness < T, EMPTY > :: could_be_empty (val_.status ()))
        {   type_one_of < T, EMPTY, B... > :: status (s_empty);
            nits.merge (nets);
            return true; }
        return false; }
    e_status content_status (nitpick& nits, const ::std::string& s)
    {   return type_one_of < T, EMPTY, B... > :: content_status (nits, s); }
    ::std::string entart (nitpick& nits, const html_version& v, const ::std::string& s)
    {   return type_one_of < T, EMPTY, B... > :: entart (nits, v, s); }
    void reset ()
    {   val_.reset ();
        type_one_of < T, EMPTY, B... > :: reset (); }
    void swap (type_one_of < T, EMPTY, A, B... >& t) noexcept
    {   val_.swap (t.val_);
        type_one_of < T, EMPTY, B... > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return type_one_of < T, EMPTY, B... > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return type_one_of < T, EMPTY, B... > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static bool is_numeric () noexcept
    {   if ( type_master < A > :: is_numeric ()) return true;
        return type_one_of < T, EMPTY, B... > :: is_numeric (); }
    static e_animation_type animation_type () noexcept
    {   const e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return type_one_of < T, EMPTY, B... > :: animation_type (); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        else type_one_of < T, EMPTY, B... > :: verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) return val_.verify_url (nits, v, e);
        return type_one_of < T, EMPTY, B... > :: verify_url (nits, v, e); }
    ::std::string get_string () const
    {   if (! val_.unknown ()) return val_.get_string ();
        return type_one_of < T, EMPTY, B... > :: get_string (); }
    ::std::string original () const
    {   return type_one_of < T, EMPTY, B... > :: original (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (tart (s));
        nitpick nuts;
        if (content_status (nits, ss) != s_invalid)
            if (inner_set_value (nuts, v, ss)) nits.merge (nuts);
            else
            {   nits.pick (nit_unrecognised_value, es_error, ec_type, quote (ss), " is invalid for all possible values (", type_name (T), ")");
                if (context.tell (es_debug)) nits.merge (nuts); } }
    void set_id (const ::std::string& s)
    {   type_one_of < T, EMPTY, B... > :: set_id (s); }
    ::std::string& id () noexcept
    {   return type_one_of < T, EMPTY, B... > :: id (); }
    const ::std::string& id () const
    {   return type_one_of < T, EMPTY, B... > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) return val_.invalid_id (nits, v, i, e);
        return type_one_of < T, EMPTY, B... > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) return val_.invalid_access (nits, v, s);
        return type_one_of < T, EMPTY, B... > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) return val_.has_id ();
        return type_one_of < T, EMPTY, B... > :: has_id (); }
    bool empty () const noexcept
    {   if (val_.empty ()) return true;
        if (! val_.unknown ()) return false;
        return type_one_of < T, EMPTY, B... > :: empty (); }
    bool good () const noexcept
    {   if (val_.good ()) return true;
        if (! val_.unknown ()) return false;
        return type_one_of < T, EMPTY, B... > :: good (); }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept
    {   if (val_.invalid ()) return true;
        if (! val_.unknown ()) return false;
        return type_one_of < T, EMPTY, B... > :: invalid (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) return val_.verify_id (e);
        else type_one_of < T, EMPTY, B... > :: verify_id (e); }
    e_status status () const noexcept
    {   if (! val_.unknown ()) return val_.status ();
        return type_one_of < T, EMPTY, B... > :: status (); }
    void status (const e_status s) noexcept
    {   if (! val_.unknown ()) val_.status (s);
        else type_one_of < T, EMPTY, B... > :: status (s); }
    bool unknown () const noexcept
    {   if (! val_.unknown ()) return false;
        return type_one_of < T, EMPTY, B... > :: unknown (); }
    ::std::size_t type () const noexcept
    {   if (! val_.unknown ()) return val_.type ();
        return tidy_string < T > :: type (); }
    vurl_t get_urls () const
    {   if (! val_.unknown ()) return val_.get_urls ();
        return type_one_of < T, EMPTY, B... > :: get_urls (); }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const
    {   if (! val_.unknown ()) return val_.get_int ();
        return type_one_of < T, EMPTY, B... > :: get_int (); }
    ::std::size_t size () const noexcept
    {   if (! val_.unknown ()) return val_.size ();
        return type_one_of < T, EMPTY, B... > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        else type_one_of < T, EMPTY, B... > :: shadow (ss, v, e); }
    element* box () noexcept
    {   if (! val_.unknown ()) return val_.box ();
        return type_one_of < T, EMPTY, B... > :: box (); }
    element* box () const noexcept
    {   if (! val_.unknown ()) return val_.box ();
        return type_one_of < T, EMPTY, B... > :: box (); }
    void box (element* b) noexcept
    {   if (! val_.unknown ()) val_.box (b);
        else type_one_of < T, EMPTY, B... > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        else type_one_of < T, EMPTY, B... > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        else type_one_of < T, EMPTY, B... > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st, e);
        else type_one_of < T, EMPTY, B... > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st, e);
        else type_one_of < T, EMPTY, B... > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   if (! val_.unknown ()) return val_.report ();
        return type_one_of < T, EMPTY, B... > :: report (); } };

template < e_type T, bool EMPTY, e_type A > struct type_one_of < T, EMPTY, A > : tidy_string < T >
{   using tidy_string < T > :: tidy_string;
    type_master < A > val_;
    bool inner_set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   val_.set_value (nits, v, s);
        if (val_.good ()) tidy_string < T > :: status (s_good);
        else if (emptiness < T, EMPTY > :: could_be_empty (val_.status ()))
            tidy_string < T > :: status (s_empty);
        else { tidy_string < T > :: status (s_invalid); return false; }
        return true; }
    e_status content_status (nitpick& nits, const ::std::string& s)
    {   return emptiness < T, EMPTY > :: content_status (nits, s); }
    ::std::string entart (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < T > :: set_value (nits, v, s);
        return tidy_string < T > :: get_string (); }
    void reset ()
    {   val_.reset ();
        tidy_string < T > :: reset (); }
    void swap (type_one_of < T, EMPTY, A >& t) noexcept
    {   val_.swap (t.val_);
        tidy_string < T > :: swap (t); }
    static e_type get_type () noexcept
    {   return T; }
    static bool is_relational () noexcept
    {   if ( type_master < A > :: is_relational ()) return true;
        return tidy_string < T > :: is_relational (); }
    static bool is_url () noexcept
    {   if ( type_master < A > :: is_url ()) return true;
        return tidy_string < T > :: is_url (); }
    static bool is_existential () noexcept
    {   return false; }
    static e_animation_type animation_type () noexcept
    {   const e_animation_type a = type_master < A > :: animation_type ();
        if (a != at_none) return a;
        return tidy_string < T > :: animation_type (); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
    {   if (! val_.unknown ()) val_.verify_attribute (nits, v, e, p, s);
        else tidy_string < T > ::verify_attribute (nits, v, e, p, s); }
    bool verify_url (nitpick& nits, const html_version& v, element& e)
    {   if (! val_.unknown ()) return val_.verify_url (nits, v, e);
        return tidy_string < T > ::verify_url (nits, v, e); }
    ::std::string get_string () const
    {   if (! val_.unknown ()) return val_.get_string ();
        return tidy_string < T > :: get_string (); }
    ::std::string original () const
    {   return tidy_string < T > :: original (); }
   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (tart (s));   
        if (content_status (nits, s) != s_invalid)
        {   nitpick nuts;
            if (inner_set_value (nuts, v, ss)) nits.merge (nuts);
            else
            {   nits.pick (nit_unrecognised_value, es_error, ec_type, quote (ss), " is invalid for all possible values (", type_name (T), ")");
                if (context.tell (es_debug)) nits.merge (nuts); } } }
    void set_id (const ::std::string& s)
    {   tidy_string < T > :: set_id (s); }
    ::std::string& id () noexcept
    {   return tidy_string < T > :: id (); }
    const ::std::string& id () const
    {   return tidy_string < T > :: id (); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   if (! val_.unknown ()) return val_.invalid_id (nits, v, i, e);
        return tidy_string < T > :: invalid_id (nits, v, i, e); }
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* s)
    {   if (! val_.unknown ()) return val_.invalid_access (nits, v, s);
        return tidy_string < T > :: invalid_access (nits, v, s); }
    bool has_id () const
    {   if (! val_.unknown ()) return val_.has_id ();
        return tidy_string < T > :: has_id (); }
    bool empty () const noexcept
    {   if (val_.empty ()) return true;
        if (! val_.unknown ()) return false;
        return tidy_string < T > :: empty (); }
    bool good () const noexcept
    {   if (val_.good ()) return true;
        if (! val_.unknown ()) return false;
        return EMPTY && empty (); }
    bool bad () const noexcept
    {   return ! good (); }
    bool invalid () const noexcept
    {   if (val_.invalid ()) return true;
        if (! val_.unknown ()) return false;
        return bad (); }
    void verify_id (element& e)
    {   if (! val_.unknown ()) return val_.verify_id (e);
        else tidy_string < T > :: verify_id (e); }
    e_status status () const noexcept
    {   if (! val_.unknown ()) return val_.status ();
        return tidy_string < T > :: status (); }
    void status (const e_status s) noexcept
    {   if (! val_.unknown ()) val_.status (s);
        else tidy_string < T > :: status (s); }
    bool unknown () const noexcept
    {   return val_.unknown (); }
    ::std::size_t type () const noexcept
    {   if (! val_.unknown ()) return val_.type ();
        return tidy_string < T > :: type (); }
    vurl_t get_urls () const
    {   if (! val_.unknown ()) return val_.get_urls ();
        return tidy_string < T > :: get_urls (); }
    template < e_type X > static type_master < X > default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    int get_int () const
    {   if (! val_.unknown ()) return val_.get_int ();
        return tidy_string < T > :: get_int (); }
    ::std::size_t size () const noexcept
    {   if (! val_.unknown ()) return val_.size ();
        return tidy_string < T > :: size (); }
    void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (! val_.unknown ()) val_.shadow (ss, v, e);
        else tidy_string < T > :: shadow (ss, v, e); }
    element* box () noexcept
    {   if (! val_.unknown ()) return val_.box ();
        return tidy_string < T > :: box (); }
    element* box () const noexcept
    {   if (! val_.unknown ()) return val_.box ();
        return tidy_string < T > :: box (); }
    void box (element* b) noexcept
    {   if (! val_.unknown ()) val_.box (b);
        else tidy_string < T > :: box (b); }
    void validate ()
    {   if (! val_.unknown ()) val_.validate ();
        else tidy_string < T > :: validate (); }
    void accumulate (stats_t* st) const
    {   if (! val_.unknown ()) val_.accumulate (st);
        else tidy_string < T > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   if (! val_.unknown ()) val_.accumulate (st, e);
        else tidy_string < T > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   if (! val_.unknown ()) val_.accumulate (st, e);
        else tidy_string < T > :: accumulate (st, e); }
    static void accumulate (stats_t* , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); }
    ::std::string report () const
    {   if (! val_.unknown ()) return val_.report ();
        return tidy_string < T > :: report (); } };
 