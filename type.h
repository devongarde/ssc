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
#include "type_base.h"
#include "type_core.h"
#include "type_master.h"
#include "type_enum.h"
#include "type_enum_vec.h"
#include "type_1.h"
#include "type_2.h"
#include "type_3.h"
#include "type_4.h"
#include "type_aria.h"
#include "type_autocomplete.h"
#include "type_class.h"
#include "type_colour.h"
#include "type_currency.h"
#include "type_httpequiv.h"
#include "type_lang.h"
#include "type_media.h"
#include "type_mime.h"
#include "type_rdf.h"
#include "type_reals.h"
#include "type_rel.h"
#include "type_relational.h"
#include "type_time.h"
#include "type_url.h"
#include "type_van.h"
#include "type_varied.h"
#include "type_xmlns.h"

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > struct typed_value : public type_master < TYPE >
{   constexpr static CATEGORY whoami () { return IDENTITY; }
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
        if (context.tell (e_comment) && (gv.length () >= def_quote_cut))
            res += ::std::string (" [") + ::boost::lexical_cast < ::std::string > (gv.length ()) + "]"; }
    if (type_master < TYPE > :: has_id ())
    {   res += " #";
        res += type_master < TYPE > :: get_id (); }
    if (context.tell (e_variable))
    {   res += " (";
        res += ::boost::lexical_cast < ::std::string > (static_cast <int> (type_master < TYPE > :: get_type ()));
        res += ")"; }
    return res; }

void types_init (nitpick& nits);
bool test_value (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s);
