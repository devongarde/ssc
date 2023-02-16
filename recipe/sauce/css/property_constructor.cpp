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

#include "main/standard.h"
#include "feedback/nitpick.h"
#include "css/typed_property.h"
#include "css/property_classes.h"

template < class PROPERTY, class ... X > struct property_constructor : public property_constructor < X ... >
{   static property_v_ptr make (nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   if (p != PROPERTY :: whoami ()) return property_constructor < X... > :: make (nits, p, s, t);
        auto ptr = property_v_ptr (new PROPERTY ());
        ptr -> set_value (nits, s);
        return ptr; } };

template < class ... X > struct property_constructor < prop_text_align, X ... > : public property_constructor < X ... >
{   static property_v_ptr make (nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   if (p != prop_text_align :: whoami ()) return property_constructor < X... > :: make (nits, p, s, t);
        if ((context.html_ver ().is_css_2_0 ()) && (t == ct_string))
        {   auto ptr = property_v_ptr (new prop_context ());
            ptr -> set_value (nits, s);
            return ptr; } 
        auto ptr = property_v_ptr (new prop_text_align ());
        ptr -> set_value (nits, s);
        return ptr; } };

template < > struct property_constructor < prop_unknown >
{   static property_v_ptr make (nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   auto ptr = property_v_ptr (new prop_unknown ());
        ptr -> set_value (nits, s);
        return ptr; } };

property_v_ptr make_property_v_ptr (nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   return property_constructor < PROPERTIES > :: make (nits, p, s, t); }
