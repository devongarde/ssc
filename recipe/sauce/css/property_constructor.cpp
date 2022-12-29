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
{   static property_v_ptr make (nitpick& nits, const html_version& v, e_css_property p, const ::std::string& s)
    {   if (p != PROPERTY :: whoami ()) return property_constructor < X... > :: make (nits, v, p, s);
        auto ptr = property_v_ptr (new PROPERTY ());
        ptr -> set_value (nits, v, s);
        return ptr; } };

template < > struct property_constructor < prop_unknown >
{   static property_v_ptr make (nitpick& nits, const html_version& v, e_css_property p, const ::std::string& s)
    {   auto ptr = property_v_ptr (new prop_unknown ());
        ptr -> set_value (nits, v, s);
        return ptr; } };

property_v_ptr make_property_v_ptr (nitpick& nits, const html_version& v, e_css_property p, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    return property_constructor < PROPERTIES > :: make (nits, v, p, s); }
