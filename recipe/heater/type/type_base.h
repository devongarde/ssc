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
    element* box_ = nullptr;
public:
    typedef VALUE_TYPE value_type;
    typedef VALUE_TYPE base_type;
    typedef false_type has_int_type;
    type_base () = default;
    explicit type_base (element* box) noexcept : box_ (box) { }
    static e_type get_type () noexcept { return E; }
    static bool is_relational () noexcept { return false; }
    static bool is_url () noexcept { return false; }
    static bool is_existential () noexcept { return false; }
    static e_animation_type animation_type () noexcept { return at_none; }
    void swap (type_base& t) noexcept
    {   id_.swap (t.id_);
        ::std::swap (box_, t.box_);
        ::std::swap (status_, t.status_); }
    void reset () noexcept { status_ = s_unset; id_.clear (); }
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) noexcept { }
    bool verify_url (nitpick& , const html_version& , element& ) noexcept { return true; }
    ::std::string get_string () const noexcept { return ::std::string (); }
    ::std::string original () const noexcept { return get_string (); }
    void set_value (nitpick& , const html_version& , const ::std::string& ) { status_ = s_empty; }
    ::std::string get_id () const { return id_; }
    void set_id (const ::std::string& s) { id_ = s; }
    ::std::string& id () noexcept { return id_; }
    const ::std::string& id () const { return id_; }
    bool invalid_id (nitpick& , const html_version& , ids_t& , element* ) noexcept { return false; }
    bool invalid_access (nitpick& , const html_version& , sstr_t* ) noexcept { return false; }
    bool has_id () const noexcept { return ! id_.empty (); }
    bool empty () const noexcept { return status_ == s_empty; }
    bool good () const noexcept { return status_ == s_good; }
    bool bad () const noexcept { return ! good (); }
    bool invalid () const noexcept { return status_ == s_invalid; }
    void verify_id (element& ) noexcept { }
    e_status status () const noexcept { return status_; }
    void status (const e_status s) noexcept { status_ = s; }
    bool unknown () const noexcept { return status_ == s_unset; }
    ::std::size_t type () const noexcept { return 0; }
    vurl_t get_urls () const noexcept { return vurl_t (); }
    static VALUE_TYPE default_value ()
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return VALUE_TYPE ()); }
    VALUE_TYPE get () const { return default_value (); }
    int get_int () const noexcept { return 0; }
    bool has_value (const VALUE_TYPE ) const { return false; }
    ::std::size_t size () const noexcept { return 1; }
    void shadow (::std::stringstream& , const html_version& , element* ) noexcept { }
    element* box () noexcept { return box_; }
    element* box () const noexcept { return box_; }
    void box (element* b) noexcept { box_ = b; }
    ::std::string report () const
    {   ::std::string s;
        if (status_ == s_invalid) s = "x";
        if (has_id ())
        {   s += "(";
            s += id_;
            s += ")"; } return s; } };
