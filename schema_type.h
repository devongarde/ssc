/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "symbol.h"
#include "nitpick.h"
#include "schema_version.h"

typedef ::std::vector < e_schema > vsch_t;
bool is_schema_domain (const ::std::string& d);

struct sch : symbol < e_schema >
{   static e_schema parse (nitpick& nits, const html_version& v, const ::std::string& x);
    static void init (nitpick& nits);
    bool unknown () const { return (symbol < e_schema > :: unknown ()) || (symbol < e_schema > :: get () == sch_illegal); }
    sch () {}
    sch (nitpick& nits, const html_version& v, const ::std::string& x);
    bool enumerated () const;
    bool has_simple_type () const;
    bool external_enumerated () const;
    e_type get_simple_type () const; };

bool enumerated_schema_type (const uint64_t flags);
bool has_simple_schema_type (const uint64_t flags);
bool external_enumerated_schema_type (const uint64_t flags);
e_type get_simple_schema_type (const uint64_t flags);
