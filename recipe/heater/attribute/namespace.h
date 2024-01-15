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
#include "parser/parse_abb.h"

typedef ::std::size_t ns_id;
class element_node;

ns_id examine_namespace (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, ::std::string& s, ::std::string& n);
e_status declare_namespace (nitpick& nits, const html_version& v, const ::std::string& key, const ::std::string& value, const namespaces_ptr& namespaces, const bool vrai);
