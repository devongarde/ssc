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
#include "attribute/attr.h"
#include "type/type.h"
#include "element/elem.h"

void avm_init (nitpick& nits);
bool is_attribute_required (const html_version& v, const e_element tag, const e_attribute a);
bool is_attribute_rejected (const html_version& v, const e_element tag, const e_attribute a);
bool is_invalid_attribute_version (const html_version& v, const e_element tag, const e_attribute a);
bool is_deprecated_attribute_version (const html_version& v, const e_element tag, const e_attribute a);
bool not_production_attribute (const html_version& v, const e_element tag, const e_attribute a);

#ifdef DEBUG
void avm_elem_crosscheck ();
#endif
