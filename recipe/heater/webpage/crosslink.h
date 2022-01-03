/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "utility/common.h"
#include "webpage/fileindex.h"
#include "webpage/id.h"

void declare_crosslinks (const fileindex_t sought, const ids_t& ids);
void declare_crosslinks (const ::boost::filesystem::path& sought, const ids_t& ids);
void add_sought (const fileindex_t seeker, const ::std::size_t line, const fileindex_t sought, const ::std::string& id, const bool hidden, const vit_t& itemtypes, const e_element e);
void add_sought (const ::boost::filesystem::path& seeker, const ::std::size_t line, const ::boost::filesystem::path& sought, const ::std::string& id, const bool hidden, const vit_t& itemtypes, const e_element e);
void reconcile_crosslinks (nitpick& nits);
