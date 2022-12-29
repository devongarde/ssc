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
#include "symbol/symbol.h"
#include "feedback/nitpick.h"
#include "schema/schema_version.h"

#define SF_ENUMERATION          0x10000000
#define SF_EXTERNAL_ENUMERATION 0x20000000
#define SF_NO_ITEMID            0x40000000
#define SF_DEPRECATED           0x80000000
#define SF_SIMPLE_MASK          0x0FFFFFFF
#define SF_NO_SIMPLE_TYPE       0

typedef ::std::vector < e_schema_type > vsch_t;
typedef ::std::set < e_schema_type > ssch_t;

struct sch : symbol < schema_version, e_schema_type, e_schema, s_schema, sz_true >
{   static e_schema_type parse (nitpick& nits, const html_version& v, const ::std::string& x, const e_schema root = s_schema);
    static void init (nitpick& nits);
    bool unknown () const noexcept
    {   return (symbol < schema_version, e_schema_type, e_schema, s_schema, sz_true > :: unknown ()) ||
        (symbol < schema_version, e_schema_type, e_schema, s_schema, sz_true > :: get () == sty_illegal); }
    sch () {}
    sch (nitpick& nits, const html_version& v, const ::std::string& x, const e_schema root = s_schema);
    bool enumerated () const noexcept;
    bool has_simple_type () const noexcept;
    bool external_enumerated () const noexcept;
    e_schema root () const noexcept;
    static e_schema root (const e_schema_type st);
    e_type get_simple_type () const noexcept; };

CONSTEXPR inline bool enumerated_schema_type (const flags_t flags) noexcept
{ return (flags & SF_ENUMERATION) == SF_ENUMERATION; }

CONSTEXPR inline bool has_simple_schema_type (const flags_t flags) noexcept
{ return (flags & SF_SIMPLE_MASK) != 0; }

CONSTEXPR inline bool external_enumerated_schema_type (const flags_t flags) noexcept
{ return (flags & SF_EXTERNAL_ENUMERATION) == SF_EXTERNAL_ENUMERATION; }

CONSTEXPR inline e_type get_simple_schema_type (const flags_t flags) noexcept
{ return static_cast < e_type > (flags & SF_SIMPLE_MASK); }

CONSTEXPR inline bool is_itemid_ok (const flags_t flags) noexcept
{ return (flags & SF_NO_ITEMID) == 0; }
