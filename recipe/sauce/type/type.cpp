/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

extern void type_name_init (nitpick& nits);

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

    type_name_init (nits);

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
            res += ": " UNKNOWN;
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
{   if (t <= SSC_TYPES_0_1_MAX) return test_typed_value < SSC_TYPES_0_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_2_9_MAX) return test_typed_value < SSC_TYPES_2_9, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_A_1_MAX) return test_typed_value < SSC_TYPES_A_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_A_2_MAX) return test_typed_value < SSC_TYPES_A_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_A_3_MAX) return test_typed_value < SSC_TYPES_A_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_A_4_MAX) return test_typed_value < SSC_TYPES_A_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_A_5_MAX) return test_typed_value < SSC_TYPES_A_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_B_1_MAX) return test_typed_value < SSC_TYPES_B_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_B_2_MAX) return test_typed_value < SSC_TYPES_B_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_1_MAX) return test_typed_value < SSC_TYPES_C_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_2_MAX) return test_typed_value < SSC_TYPES_C_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_3_MAX) return test_typed_value < SSC_TYPES_C_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_4_MAX) return test_typed_value < SSC_TYPES_C_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_C_5_MAX) return test_typed_value < SSC_TYPES_C_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_A_1_MAX) return test_typed_value < SSC_TYPES_CSS_A_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_A_2_MAX) return test_typed_value < SSC_TYPES_CSS_A_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_A_3_MAX) return test_typed_value < SSC_TYPES_CSS_A_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_B_1_MAX) return test_typed_value < SSC_TYPES_CSS_B_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_B_2_MAX) return test_typed_value < SSC_TYPES_CSS_B_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_B_3_MAX) return test_typed_value < SSC_TYPES_CSS_B_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_B_4_MAX) return test_typed_value < SSC_TYPES_CSS_B_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_1_MAX) return test_typed_value < SSC_TYPES_CSS_C_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_2_MAX) return test_typed_value < SSC_TYPES_CSS_C_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_3_MAX) return test_typed_value < SSC_TYPES_CSS_C_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_4_MAX) return test_typed_value < SSC_TYPES_CSS_C_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_C_5_MAX) return test_typed_value < SSC_TYPES_CSS_C_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_D_MAX) return test_typed_value < SSC_TYPES_CSS_D, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_E_1_MAX) return test_typed_value < SSC_TYPES_CSS_E_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_E_2_MAX) return test_typed_value < SSC_TYPES_CSS_E_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_F_1_MAX) return test_typed_value < SSC_TYPES_CSS_F_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_F_2_MAX) return test_typed_value < SSC_TYPES_CSS_F_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_F_3_MAX) return test_typed_value < SSC_TYPES_CSS_F_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_FN_1_MAX) return test_typed_value < SSC_TYPES_CSS_FN_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_FN_2_MAX) return test_typed_value < SSC_TYPES_CSS_FN_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_FN_3_MAX) return test_typed_value < SSC_TYPES_CSS_FN_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_G_H_MAX) return test_typed_value < SSC_TYPES_CSS_G_H, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_I_1_MAX) return test_typed_value < SSC_TYPES_CSS_I_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_I_2_MAX) return test_typed_value < SSC_TYPES_CSS_I_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_J_K_MAX) return test_typed_value < SSC_TYPES_CSS_J_K, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_L_1_MAX) return test_typed_value < SSC_TYPES_CSS_L_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_L_2_MAX) return test_typed_value < SSC_TYPES_CSS_L_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_L_3_MAX) return test_typed_value < SSC_TYPES_CSS_L_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_M_1_MAX) return test_typed_value < SSC_TYPES_CSS_M_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_M_2_MAX) return test_typed_value < SSC_TYPES_CSS_M_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_N_O_MAX) return test_typed_value < SSC_TYPES_CSS_N_O, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_P_1_MAX) return test_typed_value < SSC_TYPES_CSS_P_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_P_Q_MAX) return test_typed_value < SSC_TYPES_CSS_P_Q, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_R_1_MAX) return test_typed_value < SSC_TYPES_CSS_R_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_R_2_MAX) return test_typed_value < SSC_TYPES_CSS_R_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_S_1_MAX) return test_typed_value < SSC_TYPES_CSS_S_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_S_2_MAX) return test_typed_value < SSC_TYPES_CSS_S_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_S_3_MAX) return test_typed_value < SSC_TYPES_CSS_S_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_1_MAX) return test_typed_value < SSC_TYPES_CSS_T_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_2_MAX) return test_typed_value < SSC_TYPES_CSS_T_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_3_MAX) return test_typed_value < SSC_TYPES_CSS_T_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_4_MAX) return test_typed_value < SSC_TYPES_CSS_T_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_T_5_MAX) return test_typed_value < SSC_TYPES_CSS_T_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_U_MAX) return test_typed_value < SSC_TYPES_CSS_U, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_V_MAX) return test_typed_value < SSC_TYPES_CSS_V, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_CSS_W_Z_MAX) return test_typed_value < SSC_TYPES_CSS_W_Z, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_D_1_MAX) return test_typed_value < SSC_TYPES_D_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_D_2_MAX) return test_typed_value < SSC_TYPES_D_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_E_MAX) return test_typed_value < SSC_TYPES_E, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_F_1_MAX) return test_typed_value < SSC_TYPES_F_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_F_2_MAX) return test_typed_value < SSC_TYPES_F_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_F_3_MAX) return test_typed_value < SSC_TYPES_F_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_G_MAX) return test_typed_value < SSC_TYPES_G, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_H_MAX) return test_typed_value < SSC_TYPES_H, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_I_1_MAX) return test_typed_value < SSC_TYPES_I_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_I_2_MAX) return test_typed_value < SSC_TYPES_I_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_I_3_MAX) return test_typed_value < SSC_TYPES_I_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_J_K_MAX) return test_typed_value < SSC_TYPES_J_K, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_L_1_MAX) return test_typed_value < SSC_TYPES_L_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_L_2_MAX) return test_typed_value < SSC_TYPES_L_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_L_3_MAX) return test_typed_value < SSC_TYPES_L_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_1_MAX) return test_typed_value < SSC_TYPES_M_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_2_MAX) return test_typed_value < SSC_TYPES_M_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_3_MAX) return test_typed_value < SSC_TYPES_M_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_4_MAX) return test_typed_value < SSC_TYPES_M_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_5_MAX) return test_typed_value < SSC_TYPES_M_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_M_6_MAX) return test_typed_value < SSC_TYPES_M_6, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_N_MAX) return test_typed_value < SSC_TYPES_N, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_O_MAX) return test_typed_value < SSC_TYPES_O, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_P_1_MAX) return test_typed_value < SSC_TYPES_P_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_P_2_MAX) return test_typed_value < SSC_TYPES_P_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_P_3_MAX) return test_typed_value < SSC_TYPES_P_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_P_4_MAX) return test_typed_value < SSC_TYPES_P_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_1_MAX) return test_typed_value < SSC_TYPES_R_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_2_MAX) return test_typed_value < SSC_TYPES_R_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_3_MAX) return test_typed_value < SSC_TYPES_R_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_4_MAX) return test_typed_value < SSC_TYPES_R_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_5_MAX) return test_typed_value < SSC_TYPES_R_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_R_6_MAX) return test_typed_value < SSC_TYPES_R_6, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_1_MAX) return test_typed_value < SSC_TYPES_S_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_2_MAX) return test_typed_value < SSC_TYPES_S_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_3_MAX) return test_typed_value < SSC_TYPES_S_3, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_4_MAX) return test_typed_value < SSC_TYPES_S_4, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_5_MAX) return test_typed_value < SSC_TYPES_S_5, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_S_6_MAX) return test_typed_value < SSC_TYPES_S_6, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_T_1_MAX) return test_typed_value < SSC_TYPES_T_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_T_2_MAX) return test_typed_value < SSC_TYPES_T_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_U_1_MAX) return test_typed_value < SSC_TYPES_U_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_U_2_MAX) return test_typed_value < SSC_TYPES_U_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_V_1_MAX) return test_typed_value < SSC_TYPES_V_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_V_2_MAX) return test_typed_value < SSC_TYPES_V_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_W_MAX) return test_typed_value < SSC_TYPES_W, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_X_1_MAX) return test_typed_value < SSC_TYPES_X_1, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_X_2_MAX) return test_typed_value < SSC_TYPES_X_2, t_unknown > :: test (nits, v, t, s);
    if (t <= SSC_TYPES_Y_Z_MAX) return test_typed_value < SSC_TYPES_Y_Z, t_unknown > :: test (nits, v, t, s);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
{   return test_typed_value < SSC_TYPES, t_unknown > :: test (nits, v, t, s); }
#endif // LIMITED_META_COMPLEXITY
