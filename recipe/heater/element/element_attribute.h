/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "attribute/attribute_classes.h"
#include "utility/tuple.h"

class context;
class directory;

template < class ATTRIBUTE, class TUPLE, bool B > struct get_attribute_imp
{   static void get (TUPLE& , ATTRIBUTE** ) { }
    static void get (const TUPLE& , const ATTRIBUTE** ) { }
    static void get_string (const TUPLE& , ::std::string& ) { }
    static void get_urls (const TUPLE& , vurl_t& ) { }
    static void set_value (TUPLE& , const html_version& , const ::std::string& ) { }
    static bool has () { return false; } };

template < class ATTRIBUTE, class TUPLE > struct get_attribute_imp < ATTRIBUTE, TUPLE, true >
{   static void get (TUPLE& t, ATTRIBUTE** p)
    {   assert (p != nullptr);
        *p = & ::std::get < ATTRIBUTE > (t); }
    static void get (const TUPLE& t, const ATTRIBUTE** p)
    {   assert (p != nullptr);
        *p = & ::std::get < ATTRIBUTE > (t); }
    static void get_string (const TUPLE& t, ::std::string& s)
    {   s = ::std::get < ATTRIBUTE > (t).get_string (); }
    static void get_urls (const TUPLE& t, vurl_t& v)
    {   v = ::std::get < ATTRIBUTE > (t).get_urls (); }
    static void set_value (TUPLE& t, const html_version& v, const ::std::string& s)
    {   ::std::get < ATTRIBUTE > (t).set_value (v, s); }
    static bool has () { return true; } };

template < class ATTRIBUTE, class... ATTRIBUTES >
void get_attribute (::std::tuple < ATTRIBUTES... >& t, ATTRIBUTE** p)
{   get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: get (t, p); }

template < class ATTRIBUTE, class... ATTRIBUTES >
void get_attribute (const ::std::tuple < ATTRIBUTES... >& t, const ATTRIBUTE** p)
{   get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: get (t, p); }

template < class ATTRIBUTE, class... ATTRIBUTES >
void get_attribute_value (const ::std::tuple < ATTRIBUTES... >& t, ::std::string& s)
{  get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: get_string (t, s); }

template < class ATTRIBUTE, class... ATTRIBUTES >
void get_attribute_urls (const ::std::tuple < ATTRIBUTES... >& t, vurl_t& v)
{  get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: get_urls (t, v); }

template < class ATTRIBUTE, class... ATTRIBUTES >
void set_attribute_value (::std::tuple < ATTRIBUTES... >& t, const html_version& v, const ::std::string& s)
{   get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: set_value (t, v, s); }

template < class ATTRIBUTE, class... ATTRIBUTES >
bool has_attribute ()
{   return get_attribute_imp < ATTRIBUTE, ::std::tuple < ATTRIBUTES... >, has_type < ATTRIBUTE, ATTRIBUTES... >::value > :: has (); }
