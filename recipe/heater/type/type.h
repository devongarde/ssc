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
#include "type/type_base.h"
#include "type/type_core.h"
#include "type/type_master.h"
#include "type/type_basic.h"
#include "type/type_misc.h"
#include "type/type_measure.h"
#include "type/type_layout.h"
#include "type/type_id.h"
#include "type/type_math.h"
#include "type/type_microdata.h"
#include "type/type_microformat.h"
#include "type/type_numeric.h"
#include "type/type_svg.h"
#include "type/type_enum.h"
#include "type/type_enum_vec.h"
#include "type/type_case.h"
#include "type/type_1.h"
#include "type/type_2.h"
#include "type/type_3.h"
#include "type/type_4.h"
#include "type/type_aria.h"
#include "type/type_autocomplete.h"
#include "type/type_class.h"
#include "type/type_colour.h"
#include "type/type_cookie.h"
#include "type/type_country.h"
#include "type/type_currency.h"
#include "type/type_httpequiv.h"
#include "type/type_lang.h"
#include "type/type_media.h"
#include "type/type_mime.h"
#include "type/type_rdf.h"
#include "type/type_reals.h"
#include "type/type_rel.h"
#include "type/type_relational.h"
#include "type/type_time.h"
#include "type/type_url.h"
#include "type/type_van.h"
#include "type/type_varied.h"
#include "type/type_xmlns.h"

template < class CATEGORY, e_type TYPE, CATEGORY IDENTITY > struct typed_value : public type_master < TYPE >
{   using type_master < TYPE > :: type_master;
    constexpr static CATEGORY whoami () { return IDENTITY; }
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
