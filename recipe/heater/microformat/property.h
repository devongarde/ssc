/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "microformat/prop.h"
#include "microformat/property_value.h"

template < e_type TYPE, e_property IDENTITY > struct typed_mf_value
        :   typed_value < e_property, TYPE, IDENTITY >
{   typedef typed_value < e_property, TYPE, IDENTITY > base_t;
    static e_type property ()
    {   return TYPE; }
    static ::std::string name ()
    {   return prop :: name (IDENTITY); }
    void set_mf_value (nitpick& nits, const html_version& v, element& e)
    {   ::std::string s (find_value < TYPE > (e));
        if (context.naughty_test (IDENTITY, s))
        {   const ::std::string alt (context.naughty_sub (IDENTITY));
            if (! amend_value < TYPE > (v, e, alt)) naughty_fix (e, s, alt);
            nits.pick (nit_naughty_microformat, es_info, ec_naughty, "ignorance is strength: concealing ", quote (s));
            s = alt; }
        base_t :: set_value (nits, v, s); }
    ::std::string report () const
    {   return base_t :: report (name ()); } };
