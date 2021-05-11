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
#include "symbol/symbol.h"
#include "attribute/namespace.h"
#include "feedback/nitpick.h"

#define AP_NAMESPACE_MASK   0x00000000000000FF

struct attr : symbol < html_version, e_attribute >
{   static e_attribute parse (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string& x, ::std::string& decl);
    static void init (nitpick& nits);
    static e_namespace ns (const uint64_t f)
    {   return static_cast < e_namespace > (f & AP_NAMESPACE_MASK); }
    e_namespace ns () const
    {   return ns (symbol < html_version, e_attribute > :: flags ()); }
    attr () {}
    attr (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string& x, ::std::string& ns)
    {   set (v, parse (nits, v, nss, x, ns)); } };

inline bool is_custom_attribute (const e_attribute a) { return (a == a_custom); }
inline bool is_error_attribute (const e_attribute a) { return (a == a_illegal); }
inline bool is_unknown_attribute (const e_attribute a) { return (a == a_unknown); }
void add_attributes (const vstr_t& v);
