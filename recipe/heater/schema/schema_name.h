/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "main/standard.h"
#include "type/enum.h"
#include "feedback/nitpick.h"

void schema_name_init (nitpick& nits);
::std::string schema_property_name (const e_schema_property p);
e_schema_property get_schema_property (const ::std::string& n);
vsp_t get_schema_properties (const ::std::string& n, const e_schema s = s_none);
e_schema get_property_root (const ::std::string& s);
e_schema get_property_root (const e_schema_property sp);
