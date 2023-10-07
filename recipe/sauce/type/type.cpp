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
{
   if (t <= SSC_TYPES_A_MAX) return test_typed_value < SSC_TYPES_A, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_B_C_MAX) return test_typed_value < SSC_TYPES_B_C, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_A_MAX) return test_typed_value < SSC_TYPES_CSS_A, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_B_MAX) return test_typed_value < SSC_TYPES_CSS_B, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_MAX) return test_typed_value < SSC_TYPES_CSS_C, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_D_E_MAX) return test_typed_value < SSC_TYPES_CSS_D_E, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_F_MAX) return test_typed_value < SSC_TYPES_CSS_F, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_G_L_MAX) return test_typed_value < SSC_TYPES_CSS_G_L, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_M_P_MAX) return test_typed_value < SSC_TYPES_CSS_M_P, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_R_S_MAX) return test_typed_value < SSC_TYPES_CSS_R_S, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_MAX) return test_typed_value < SSC_TYPES_CSS_T, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_U_Z_MAX) return test_typed_value < SSC_TYPES_CSS_U_Z, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_E_MAX) return test_typed_value < SSC_TYPES_C_E, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_F_MAX) return test_typed_value < SSC_TYPES_F, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_G_I_MAX) return test_typed_value < SSC_TYPES_G_I, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_J_L_MAX) return test_typed_value < SSC_TYPES_J_L, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_MAX) return test_typed_value < SSC_TYPES_M, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_N_O_MAX) return test_typed_value < SSC_TYPES_N_O, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_P_MAX) return test_typed_value < SSC_TYPES_P, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_Q_R_MAX) return test_typed_value < SSC_TYPES_Q_R, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_MAX) return test_typed_value < SSC_TYPES_S, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_T_U_MAX) return test_typed_value < SSC_TYPES_T_U, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_V_Z_MAX) return test_typed_value < SSC_TYPES_V_Z, t_unknown > :: test (nits, v, t, s);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
{   return test_typed_value < SSC_TYPES, t_unknown > :: test (nits, v, t, s); }
#endif // LIMITED_META_COMPLEXITY
