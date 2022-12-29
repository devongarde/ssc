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
#include "feedback/nitpick.h"
#include "parser/html_version.h"
#include "schema/schema_version.h"

typedef uint32_t type_index;
CONSTEXPR type_index invalid_type = 0;
typedef ::std::vector < type_index > vty_t;

inline CONSTEXPR type_index make_type_index (const e_schema_type p) noexcept
{   return static_cast < uint32_t > (p); }

inline e_schema_type type_schema (const type_index ii) noexcept
{   if (ii <= sty_illegal) return static_cast < e_schema_type > (ii);
    return sty_context; }

::std::string type_index_name (const type_index ndx);
type_index find_type_index (nitpick& nits, const html_version& v, const ::std::string& name);

inline type_index find_type_index (nitpick& nits, const html_version& v, const ::std::string& vocab, const ::std::string& name)
{   return find_type_index (nits, v, vocab + name); }
