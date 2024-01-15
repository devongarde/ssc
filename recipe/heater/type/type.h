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
#include "type/type_csp.h"
#include "base/base.h"
#include "enum/enumerated.h"
#include "simple/simple.h"
#include "compound/compound.h"

::std::string status_rpt (const e_status status, const bool existential, const ::std::string& s, const bool has_id, const ::std::string& id, const e_type e);

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > struct typed_value : public type_master < TYPE >
{   using type_master < TYPE > :: type_master;
    CONSTEXPR static CATEGORY whoami () { return IDENTITY; }
    ::std::string report (const ::std::string& name) const; };

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > ::std::string typed_value < CATEGORY, TYPE, IDENTITY > :: report (const ::std::string& name) const
{   return  name +
            status_rpt (type_master < TYPE > :: status (), type_master < TYPE > :: is_existential (), type_master < TYPE > :: get_string (),
            type_master < TYPE > :: has_id (), type_master < TYPE > :: get_id (), type_master < TYPE > :: get_type ()); }

void types_init (nitpick& nits);
bool test_value (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s);
