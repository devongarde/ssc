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
#include "type/type.h"
#include "type/type_master.h"
#include "css/arguments.h"

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440)
#endif // _MSC_VER

struct property_base
{   DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR (property_base);
    virtual void set_value (nitpick& , const ::std::string& ) { }
    virtual e_css_property get () const { return ec_unknown; }
    virtual void verify (nitpick& nits, const elem& e) { }
    virtual void validate (arguments& ) { }
    virtual void accumulate (stats_t* ) const { }
    virtual ::std::string rpt () const { return ::std::string (); } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435)
#endif // _MSC_VER

template < e_type TYPE, e_css_property IDENTITY > struct typed_property : public property_base, public type_master < TYPE >
{   typedef type_master < TYPE > base_type;
    static ::std::string name () { return type_master < t_css_property > :: name (IDENTITY); }
    CONSTEXPR static e_css_property whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    virtual e_css_property get () const override { return whoami (); }
    bool empty () const noexcept { return type_master < TYPE > :: empty (); }
    bool good () const noexcept { return type_master < TYPE > :: good (); }
    bool bad () const noexcept { return type_master < TYPE > :: bad (); }
    bool invalid () const noexcept { return type_master < TYPE > :: invalid (); }
    virtual void verify (nitpick& nits, const elem& e) override
    {   type_master < TYPE > :: verify_attribute (nits, context.html_ver (), e, nullptr, name ()); }
    virtual void validate (arguments& ) override { type_master < TYPE > :: validate (); }
    virtual void accumulate (stats_t* s) const override { type_master < TYPE > :: accumulate (s); }
    virtual void set_value (nitpick& nits, const ::std::string& s) override
    {   type_master < TYPE > :: set_value (nits, context.html_ver (), s); }
    virtual ::std::string rpt () const override
    {   return name () + ": " + type_master < TYPE > :: get_string (); } };

typedef ::std::shared_ptr < property_base > property_v_ptr;
property_v_ptr make_property_v_ptr (nitpick& nits, e_css_property p, const ::std::string& s, const css_token t);

inline property_v_ptr make_property_v_ptr (nitpick& nits, const ::std::string& name, const ::std::string& value, const css_token t)
{   return make_property_v_ptr (nits, examine_value < t_css_property > (nits, context.html_ver (), name), value, t); }

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
