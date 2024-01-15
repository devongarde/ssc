/*
ssc (static site checker)
File Info
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
#include "ontology/ontology_type.h"
#include "ontology/ontology_name.h"
#include "microdata/microdata_itemtype.h"

typedef ::std::vector < e_type > vt_t;

void ontology_property_init (nitpick& nits);
e_ontology_property identify_ontology_property (const ::std::string& name, const e_ontology root = s_none);
vsp_t identify_ontology_properties (const ::std::string& name, const e_ontology root = s_none);
bool check_ontology_property_version (const ontology_version& from, const ontology_version& to, const e_ontology_property prop, bool& found);
::std::string ontology_property_name (const e_ontology_property prop);
bool is_valid_ontology_property (nitpick& nits, const html_version& v, const e_ontology_type schema, const e_ontology_property prop, const ::std::string& value, const bool is_link);
bool is_valid_ontology_property (nitpick& nits, const html_version& v, const e_ontology_type schema, const e_ontology_property prop, const e_ontology_type value);
vit_t sought_ontology_types (const e_ontology_property prop);
vit_t sought_ontology_types (const ontology_version& sv, const e_ontology_property prop);
vt_t sought_types (const ontology_version& sv, const e_ontology_property prop);
e_ontology property_root (const e_ontology_property prop);
bool does_property_apply (const ontology_version& sv, const e_ontology_property prop);
