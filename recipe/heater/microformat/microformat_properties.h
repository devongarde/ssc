/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "microformat/property_classes.h"
#include "utility/tuple.h"

template < class PROPERTY, class TUPLE, bool B > struct get_property_imp
{   static void get (TUPLE& , PROPERTY** ) { }
    static void get (const TUPLE& , PROPERTY** ) { }
    static void get (const TUPLE& , ::std::string& ) { }
    static bool has () noexcept { return false; } };

template < class PROPERTY, class TUPLE > struct get_property_imp < PROPERTY, TUPLE, true >
{   static void get (TUPLE& t, PROPERTY** p) { VERIFY_NOT_NULL (p, __FILE__, __LINE__); *p = & ::std::get < PROPERTY > (t); }
    static void get (const TUPLE& t, const PROPERTY** p) { VERIFY_NOT_NULL (p, __FILE__, __LINE__); *p = & ::std::get < PROPERTY > (t); }
    static void get (const TUPLE& t, ::std::string& s) { s = ::std::get < PROPERTY > (t).get_string (); }
    static bool has () noexcept { return true; } };

template < class PROPERTY, class... PROPERTIES > void get_property (::std::tuple < PROPERTIES...> & t, PROPERTY** p)
{   get_property_imp < PROPERTY, ::std::tuple < PROPERTIES... >, has_type < PROPERTY, PROPERTIES... >::value > :: get (t, p); }

template < class PROPERTY, class... PROPERTIES > void get_property (const ::std::tuple < PROPERTIES...>& t, const PROPERTY** p)
{   get_property_imp < PROPERTY, ::std::tuple < PROPERTIES... >, has_type < PROPERTY, PROPERTIES... >::value > :: get (t, p); }

template < class PROPERTY, class... PROPERTIES > bool has_property ()
{   return get_property_imp < PROPERTY, ::std::tuple < PROPERTIES... >, has_type < PROPERTY, PROPERTIES... >::value > :: has (); }
