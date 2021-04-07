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
#include "schema/schema_type.h"
#include "schema/schema_name.h"
#include "microdata/microdata_itemtype.h"

void schema_property_init (nitpick& );
e_schema_property identify_schema_property (nitpick& nits, const schema_version& v, const ::std::string& name);
vsp_t identify_schema_properties (nitpick& nits, const schema_version& v, const ::std::string& name);
bool check_schema_property_version (const schema_version& from, const schema_version& to, const e_schema_property prop, bool& found);
::std::string schema_property_name (const e_schema_property prop);
bool is_valid_schema_property (nitpick& nits, const html_version& v, const e_schema_type schema, const e_schema_property prop, const ::std::string& value, const bool is_link);
bool is_valid_schema_property (nitpick& nits, const html_version& v, const e_schema_type schema, const e_schema_property prop, const e_schema_type value);
vit_t sought_schema_itemtypes (const e_schema_property prop);
