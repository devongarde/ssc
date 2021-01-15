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
#include "feedback/nitpick.h"

#define AP_NAMESPACE_MASK   0x00000000000000FF

struct attr : symbol < e_attribute >
{   static e_attribute parse (nitpick& nits, const html_version& v, const ::std::string& x);
    static void init (nitpick& nits);
    static e_namespace ns (const uint64_t f)
    {   return static_cast < e_namespace > (f & AP_NAMESPACE_MASK); }
    e_namespace ns () const
    {   return ns (symbol < e_attribute > :: flags ()); }
    attr () {}
    attr (nitpick& nits, const html_version& v, const ::std::string& x) { set (v, parse (nits, v, x)); } };
