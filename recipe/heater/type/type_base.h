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
#include "utility/common.h"
#include "css/css.h"
#include "url/url.h"
#include "feedback/nitpick.h"

class directory;
class html_version;
class elem;
class element;

typedef bool mono;

template < typename VALUE_TYPE, e_type E > class type_base
{   ::std::string id_;
    e_status status_ = s_unset;
public:
    typedef VALUE_TYPE value_type;
    typedef VALUE_TYPE base_type;
    typedef false_type has_int_type;
    type_base () = default;
    static e_type get_type () { return E; }
    static bool is_relational () { return false; }
    static bool is_url () { return false; }
    static bool is_existential () { return false; }
    static e_animation_type animation_type () { return at_none; }
    void swap (type_base& t) NOEXCEPT { id_.swap (t.id_); ::std::swap (status_, t.status_); }
    void reset () { status_ = s_unset; id_.clear (); }
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
    bool verify_url (nitpick& , const html_version& , const element& ) { return true; }
    ::std::string get_string () const { return ::std::string (); }
    ::std::string original () const { return get_string (); }
    void set_value (nitpick& , const html_version& , const ::std::string& ) { status_ = s_empty; }
    ::std::string get_id () const { return id_; }
    void set_id (const ::std::string& s) { id_ = s; }
    ::std::string& id () { return id_; }
    const ::std::string& id () const { return id_; }
    bool invalid_id (nitpick& , const html_version& , ids_t& , element* ) { return false; }
    bool invalid_access (nitpick& , const html_version& , sstr_t* ) { return false; }
    bool has_id () const { return ! id_.empty (); }
    bool empty () const { return status_ == s_empty; }
    bool good () const { return status_ == s_good; }
    bool bad () const { return ! good (); }
    bool invalid () const { return status_ == s_invalid; }
//    void verify_id (nitpick& , const html_version& , ids_t& , const attribute_bitset& , const vit_t& , const e_sought_category ) { }
    void verify_id (element& ) { }
    e_status status () const { return status_; }
    void status (const e_status s) { status_ = s; }
    bool unknown () const { return status_ == s_unset; }
    ::std::size_t type () const { return 0; }
    vurl_t get_urls () const { return vurl_t (); }
    static VALUE_TYPE default_value () { GRACEFUL_CRASH (__FILE__, __LINE__); return VALUE_TYPE (); }
    VALUE_TYPE get () const { return default_value (); }
    int get_int () const { return 0; }
    bool has_value (const VALUE_TYPE ) const { return false; }
    ::std::size_t size () const { return 1; }
    void shadow (::std::stringstream& , const html_version& , element* ) { }
    ::std::string report () const
    {   ::std::string s;
        if (status_ == s_invalid) s = "x";
        if (has_id ())
        {   s += "(";
            s += id_;
            s += ")"; } return s; } };
