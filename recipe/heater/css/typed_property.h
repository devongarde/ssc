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

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440)
#endif // _MSC_VER

struct property_base
{   DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR (property_base);
    virtual void set_value (nitpick& , const html_version& , const ::std::string& ) { }
    virtual e_css_property get () const { return ec_unknown; }
    virtual void accumulate (stats_t* ) const { }
    virtual ::std::string rpt () const { return ::std::string (); } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435)
#endif // _MSC_VER

template < e_type TYPE, e_css_property IDENTITY > struct typed_property : public property_base, public type_master < TYPE >
{   static ::std::string name () { return type_master < t_css_property > :: name (IDENTITY); }
    CONSTEXPR static e_css_property whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    virtual e_css_property get () const override { return whoami (); }
    bool empty () const noexcept { return type_master < TYPE > :: empty (); }
    bool good () const noexcept { return type_master < TYPE > :: good (); }
    bool bad () const noexcept { return type_master < TYPE > :: bad (); }
    bool invalid () const noexcept { return type_master < TYPE > :: invalid (); }
    virtual void accumulate (stats_t* s) const override { type_master < TYPE > :: accumulate (s); }
    virtual void set_value (nitpick& nits, const html_version& v, const ::std::string& s) override
    {   type_master < TYPE > :: set_value (nits, v, s); }
    virtual ::std::string rpt () const override
    {   return name () + ": " + type_master < TYPE > :: get_string (); } };

typedef ::std::shared_ptr < property_base > property_v_ptr;
property_v_ptr make_property_v_ptr (nitpick& nits, const html_version& v, e_css_property p, const ::std::string& s);

inline property_v_ptr make_property_v_ptr (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value)
{   return make_property_v_ptr (nits, v, examine_value < t_css_property > (nits, v, name), value); }

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
