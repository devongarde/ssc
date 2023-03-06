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
#include "type/type_csp.h"
#include "base/base.h"
#include "enum/enumerated.h"
#include "simple/simple.h"
#include "compound/compound.h"

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > struct typed_value : public type_master < TYPE >
{   using type_master < TYPE > :: type_master;
    CONSTEXPR static CATEGORY whoami () { return IDENTITY; }
    ::std::string report (const ::std::string& name) const; };

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > ::std::string typed_value < CATEGORY, TYPE, IDENTITY > :: report (const ::std::string& name) const
{   ::std::string res (name);
    switch (type_master < TYPE > :: status ())
    {   case s_unset:
            res += ": (unknown)";
            return res;
        case s_empty:
            res += ": (empty)";
            return res;
        case s_invalid:
            res += ": (invalid)";
            return res;
        case s_good:
            break;
        default:
            res += ": (internal error: " PROG " shouldn't get here)";
            return res; }
    if (! type_master < TYPE > :: is_existential ())
    {   res += ": ";
        ::std::string gv (type_master < TYPE > :: get_string ());
        res += quote (gv);
        if (context.tell (es_comment) && (gv.length () >= def_quote_cut))
            res += ::std::string (" [") + ::boost::lexical_cast < ::std::string > (gv.length ()) + "]"; }
    if (type_master < TYPE > :: has_id ())
    {   res += " #";
        res += type_master < TYPE > :: get_id (); }
    if (context.tell (es_variable))
    {   res += " (";
        res += ::boost::lexical_cast < ::std::string > (static_cast <int> (type_master < TYPE > :: get_type ()));
        res += ")"; }
    return res; }

void types_init (nitpick& nits);
bool test_value (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s);
