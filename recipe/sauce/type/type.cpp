/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "type/type.h"

extern void type_name_init ();

void types_init (nitpick& nits)
{   void charset_init (nitpick& nits);
    void class_init (nitpick& nits);
    void colour_init (nitpick& nits);
    void conlit_init (nitpick& nits);
    void country_init (nitpick& nits);
    void currency_init (nitpick& nits);
    void httpequiv_init (nitpick& nits);
    void lang_init (nitpick& nits);
    void media_init (nitpick& nits);
    void metaname_init (nitpick& nits);
    void mime_init (nitpick& nits);
    void property_init (nitpick& nits);
    void rel_init (nitpick& nits);
    void role_init (nitpick& nits);
    void sgml_init (nitpick& nits);
    void enum_init (nitpick& nits);

    type_name_init ();

    charset_init (nits);
    class_init (nits);
    colour_init (nits);
    conlit_init (nits);
    country_init (nits);
    currency_init (nits);
    httpequiv_init (nits);
    lang_init (nits);
    media_init (nits);
    metaname_init (nits);
    mime_init (nits);
    property_init (nits);
    rel_init (nits);
    role_init (nits);
    sgml_init (nits);

    enum_init (nits); }

::std::string status_rpt (const e_status status, const bool existential, const ::std::string& gv, const bool has_id, const ::std::string& id, const e_type e)
{   ::std::string res;
    switch (status)
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
    if (! existential)
    {   res += ": ";
        res += quote (gv);
        if (context.tell (es_comment) && (gv.length () >= def_quote_cut))
            res += ::std::string (" [") + ::boost::lexical_cast < ::std::string > (gv.length ()) + "]"; }
    if (has_id)
    {   res += " #";
        res += id; }
    if (context.tell (es_variable))
    {   res += " (";
        res += ::boost::lexical_cast < ::std::string > (static_cast <int> (e));
        res += ")"; }
    return res; }

template < e_type TYPE, e_type... TYPES > struct test_typed_value : public test_typed_value < TYPES... >
{   static bool test (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s)
    {   if (t == TYPE) return test_value < TYPE > (nits, v, s); 
        return test_typed_value < TYPES... > :: test (nits, v, t, s); } };

template < e_type TYPE > struct test_typed_value < TYPE >
{   static bool test (nitpick& , const html_version& , const e_type , const ::std::string& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__); } };

bool test_value (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s)
#ifdef LIMITED_META_COMPLEXITY
{   if (t <= SSC_TYPE_1_MAX) return test_typed_value < SSC_TYPES_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPE_2_MAX) return test_typed_value < SSC_TYPES_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPE_3_MAX) return test_typed_value < SSC_TYPES_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPE_4_MAX) return test_typed_value < SSC_TYPES_4, t_unknown > :: test (nits, v, t, s);
    return test_typed_value < SSC_TYPES_5, t_unknown > :: test (nits, v, t, s); }
#else // LIMITED_META_COMPLEXITY
{   return test_typed_value < SSC_TYPES_1, SSC_TYPES_2, SSC_TYPES_3, SSC_TYPES_4, SSC_TYPES_5, t_unknown > :: test (nits, v, t, s); }
#endif // LIMITED_META_COMPLEXITY
