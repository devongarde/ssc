/*
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "feedback/nitpick.h"

void ontology_name_init (nitpick& nits);
::std::string ontology_property_name (const e_ontology_property p);
e_ontology_property get_ontology_property (const ::std::string& n, const e_ontology s = s_none);
vsp_t get_ontology_properties (const ::std::string& n, const e_ontology s = s_none);
e_ontology get_property_root (const ::std::string& s);
e_ontology get_property_root (const e_ontology_property sp);
