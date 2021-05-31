/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software:you can redistribute it and/or modify
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
#include "attribute/attribute.h"
#include "attribute/attribute_classes.h"

template < class ATTRIBUTE, class ... X > struct attribute_constructor : public attribute_constructor < X ... >
{   static attribute_v_ptr make (nitpick& nits, const html_version& v, const attribute_node& node)
    {   if (node.id () != ATTRIBUTE :: whoami ()) return attribute_constructor < X... > :: make (nits, v, node);
        auto ptr = attribute_v_ptr (new ATTRIBUTE ());
        ptr -> parse (nits, v, node);
        return ptr; }
    static e_animation_type animation_type (const e_attribute ea)
    {   if (ea == ATTRIBUTE :: whoami ()) return ATTRIBUTE :: animation_type ();
        return attribute_constructor < X... > :: animation_type (ea); } };

template < > struct attribute_constructor < attr_unknown >
{   static attribute_v_ptr make (nitpick& nits, const html_version& v, const attribute_node& node)
    {   auto ptr = attribute_v_ptr (new attr_unknown ());
        ptr -> parse (nits, v, node);
        return ptr; }
    static e_animation_type animation_type (const e_attribute ) { return at_none; } };

attribute_v_ptr make_attribute_v_ptr (nitpick& nits, const html_version& v, const attribute_node& node)
{   if (node.id () <= last_am) return attribute_constructor < ATTRIBUTESAM > :: make (nits, v, node);
    else return attribute_constructor < ATTRIBUTESNZ > :: make (nits, v, node); }

e_animation_type get_animation_type (const e_attribute ea)
{   if (ea <= last_am) return attribute_constructor < ATTRIBUTESAM > :: animation_type (ea);
    else return attribute_constructor < ATTRIBUTESNZ > :: animation_type (ea); }
