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
#include "symbol/symbol.h"
#include "attribute/namespace.h"
#include "feedback/nitpick.h"

#define AF_NOT_NAMESPACED   0x0000000000000001
#define AF_PROPERTY         0x0000000000000002
#define AF_SVG2_PROPERTY    0x0000000000000004
#define AF_SPELT            0x0000000000000008

#define AP_XLINKCAT_MASK    0x000000000000FF00
#define AP_XLINK_TYPE_SHIFT 8

#define AP_SET_XLINKCAT(XXX)  ((flags_t) (XXX) << AP_XLINK_TYPE_SHIFT)
#define AP_GET_XLINKCAT(XXX)  (((XXX) & AP_XLINKCAT_MASK) >> AP_XLINK_TYPE_SHIFT)

#define AF_REVERSIONER      0x0000001000000000

struct attr : symbol < html_version, e_attribute >
{   attr (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x, ::std::string& ns)
    {   set (v, parse (nits, v, namespaces, x, ns)); }
    static e_attribute parse (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& key, ::std::string& decl);
    static void init (nitpick& nits);
    static bool is_versioner (const e_attribute a) { return (symbol < html_version, e_attribute > :: flags (a) & AF_REVERSIONER) == AF_REVERSIONER; }
    static bool spellcheck (const e_attribute a) { return (symbol < html_version, e_attribute > :: flags (a) & AF_SPELT) == AF_SPELT; }
    CONSTEXPR static e_sought_category link_category_sought (const flags_t f) noexcept
    {   return static_cast < e_sought_category > (AP_GET_XLINKCAT (f)); }
    e_sought_category link_category_sought () const noexcept
    {   return static_cast < e_sought_category > (AP_GET_XLINKCAT (flags ())); }
    bool spellcheck () const noexcept { return (symbol < html_version, e_attribute > :: flags () & AF_SPELT) == AF_SPELT; }
    bool is_versioner () const noexcept { return (symbol < html_version, e_attribute > :: flags () & AF_REVERSIONER) == AF_REVERSIONER; } };

CONSTEXPR inline bool is_custom_attribute (const e_attribute a) noexcept { return (a == a_custom); }
CONSTEXPR inline bool is_error_attribute (const e_attribute a) noexcept { return (a == a_illegal); }
CONSTEXPR inline bool is_unknown_attribute (const e_attribute a) noexcept { return (a == a_unknown); }
void add_attributes (const vstr_t& v);
