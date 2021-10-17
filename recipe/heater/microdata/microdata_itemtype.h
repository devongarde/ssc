/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "feedback/nitpick.h"
#include "parser/html_version.h"

typedef uint32_t itemtype_index;
const itemtype_index invalid_itemtype = 0;
typedef ::std::vector < itemtype_index > vit_t;

itemtype_index make_itemtype_index (const e_schema_type p);
itemtype_index make_itemtype_index (const e_property p);
e_itemtype_category type_category (const itemtype_index ii);
e_schema_type type_itself (const itemtype_index ii);
itemtype_index find_itemtype_index (nitpick& nits, const html_version& v, const ::std::string& name, const bool propped = true);
::std::string itemtype_index_name (const itemtype_index ndx);
