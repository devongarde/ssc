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

class element;

bool test_many (const vtype_t& vty, nitpick& nits, const html_version& v, const vstr_t& vs);

template < e_type TYPE > struct type_master : public string_value < TYPE >
{   using string_value < TYPE > :: string_value; };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440) // By the same logic: dalmations are dogs, dalmations have spots, therefore all dogs have spots.
#endif // _MSC_VER
template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    return t.good (); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& id)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return false;
    id = t.get_id ();
    return true; }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return static_cast < typename type_master < T > :: value_type > (type_master < T > :: default_value ());
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }

template < e_type T > e_animation_type grab_animation_type () noexcept
{   type_master < T > t;
    return t.animation_type (); }
