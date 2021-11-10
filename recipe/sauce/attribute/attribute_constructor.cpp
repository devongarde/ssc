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
{   static attribute_v_ptr make (nitpick& nits, const html_version& v, element* box, const attribute_node& node)
    {   if (node.id () != ATTRIBUTE :: whoami ()) return attribute_constructor < X... > :: make (nits, v, box, node);
        auto ptr = attribute_v_ptr (new ATTRIBUTE (box));
        ptr -> parse (nits, v, node);
        return ptr; }
    static e_animation_type animation_type (const e_attribute ea) noexcept
    {   if (ea == ATTRIBUTE :: whoami ()) return ATTRIBUTE :: animation_type ();
        return attribute_constructor < X... > :: animation_type (ea); } };

template < > struct attribute_constructor < attr_unknown >
{   static attribute_v_ptr make (nitpick& nits, const html_version& v, element* box, const attribute_node& node)
    {   auto ptr = attribute_v_ptr (new attr_unknown (box));
        ptr -> parse (nits, v, node);
        return ptr; }
    static e_animation_type animation_type (const e_attribute ) noexcept { return at_none; } };

attribute_v_ptr make_attribute_v_ptr (nitpick& nits, const html_version& v, element* box, const attribute_node& node)
{   if (node.id () <= last_1) return attribute_constructor < ATTRIBUTES_1 > :: make (nits, v, box, node);
    else if (node.id () <= last_2) return attribute_constructor < ATTRIBUTES_2 > :: make (nits, v, box, node);
    else return attribute_constructor < ATTRIBUTES_3 > :: make (nits, v, box, node); }

e_animation_type get_animation_type (const e_attribute ea)
{   if (ea <= last_1) return attribute_constructor < ATTRIBUTES_1 > :: animation_type (ea);
    else if (ea <= last_2) return attribute_constructor < ATTRIBUTES_2 > :: animation_type (ea);
    else return attribute_constructor < ATTRIBUTES_3 > :: animation_type (ea); }
