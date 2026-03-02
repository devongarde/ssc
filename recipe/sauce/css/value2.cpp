/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

#include "main/standard.h"
#include "feedback/nitpick.h"
#include "type/type.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/typed_property.h"
#include "css/value.h"

template < e_type TYPE, e_type... TYPES > struct property_by_type : public property_by_type < TYPES... >
{   static int check (arguments& args, const int start, const int to, nitpick& nits, e_type e)
    {   if (e != TYPE) return property_by_type < TYPES... > :: check (args, start, to, nits, e);
        int i = start;
        if (typed_property < TYPE, ec_unknown > :: check_fn (args, i, to, nits, true)) return to;
        return start; } };

template < e_type TYPE > struct property_by_type < TYPE >
{   static int check (arguments& , const int , const int , nitpick& , e_type )
    {   GRACEFUL_CRASH ( __FILE__, __LINE__); } };

int check_typed_identifier (arguments& args, nitpick& nits, const int start, const int to, const e_type t)
{   PRESUME ((args.t_.at (start).t_ == ct_keyword) || (args.t_.at (start).t_ == ct_identifier) || (args.t_.at (start).t_ == ct_number), __FILE__, __LINE__);
#ifdef LIMITED_META_COMPLEXITY // am presuming optimiser will optimise these...
    if (t <= SSC_TYPES_0_1_MAX) return property_by_type < SSC_TYPES_0_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_2_9_MAX) return property_by_type < SSC_TYPES_2_9, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_1_MAX) return property_by_type < SSC_TYPES_A_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_2_MAX) return property_by_type < SSC_TYPES_A_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_3_MAX) return property_by_type < SSC_TYPES_A_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_4_MAX) return property_by_type < SSC_TYPES_A_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_5_MAX) return property_by_type < SSC_TYPES_A_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_B_1_MAX) return property_by_type < SSC_TYPES_B_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_B_2_MAX) return property_by_type < SSC_TYPES_B_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_1_MAX) return property_by_type < SSC_TYPES_C_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_2_MAX) return property_by_type < SSC_TYPES_C_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_3_MAX) return property_by_type < SSC_TYPES_C_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_4_MAX) return property_by_type < SSC_TYPES_C_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_5_MAX) return property_by_type < SSC_TYPES_C_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_A_1_MAX) return property_by_type < SSC_TYPES_CSS_A_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_A_2_MAX) return property_by_type < SSC_TYPES_CSS_A_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_A_3_MAX) return property_by_type < SSC_TYPES_CSS_A_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_1_MAX) return property_by_type < SSC_TYPES_CSS_B_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_2_MAX) return property_by_type < SSC_TYPES_CSS_B_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_3_MAX) return property_by_type < SSC_TYPES_CSS_B_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_4_MAX) return property_by_type < SSC_TYPES_CSS_B_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_1_MAX) return property_by_type < SSC_TYPES_CSS_C_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_2_MAX) return property_by_type < SSC_TYPES_CSS_C_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_3_MAX) return property_by_type < SSC_TYPES_CSS_C_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_4_MAX) return property_by_type < SSC_TYPES_CSS_C_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_D_MAX) return property_by_type < SSC_TYPES_CSS_D, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_E_MAX) return property_by_type < SSC_TYPES_CSS_E, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_F_1_MAX) return property_by_type < SSC_TYPES_CSS_F_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_F_2_MAX) return property_by_type < SSC_TYPES_CSS_F_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_F_3_MAX) return property_by_type < SSC_TYPES_CSS_F_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_FN_1_MAX) return property_by_type < SSC_TYPES_CSS_FN_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_FN_2_MAX) return property_by_type < SSC_TYPES_CSS_FN_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_G_H_MAX) return property_by_type < SSC_TYPES_CSS_G_H, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_I_1_MAX) return property_by_type < SSC_TYPES_CSS_I_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_I_2_MAX) return property_by_type < SSC_TYPES_CSS_I_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_J_K_MAX) return property_by_type < SSC_TYPES_CSS_J_K, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_L_1_MAX) return property_by_type < SSC_TYPES_CSS_L_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_L_2_MAX) return property_by_type < SSC_TYPES_CSS_L_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_L_3_MAX) return property_by_type < SSC_TYPES_CSS_L_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_M_N_MAX) return property_by_type < SSC_TYPES_CSS_M_N, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_O_MAX) return property_by_type < SSC_TYPES_CSS_O, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_P_1_MAX) return property_by_type < SSC_TYPES_CSS_P_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_P_Q_MAX) return property_by_type < SSC_TYPES_CSS_P_Q, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_R_MAX) return property_by_type < SSC_TYPES_CSS_R, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_S_1_MAX) return property_by_type < SSC_TYPES_CSS_S_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_S_2_MAX) return property_by_type < SSC_TYPES_CSS_S_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_S_3_MAX) return property_by_type < SSC_TYPES_CSS_S_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_1_MAX) return property_by_type < SSC_TYPES_CSS_T_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_2_MAX) return property_by_type < SSC_TYPES_CSS_T_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_3_MAX) return property_by_type < SSC_TYPES_CSS_T_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_4_MAX) return property_by_type < SSC_TYPES_CSS_T_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_U_MAX) return property_by_type < SSC_TYPES_CSS_U, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_V_MAX) return property_by_type < SSC_TYPES_CSS_V, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_W_Z_MAX) return property_by_type < SSC_TYPES_CSS_W_Z, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_D_1_MAX) return property_by_type < SSC_TYPES_D_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_D_2_MAX) return property_by_type < SSC_TYPES_D_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_E_MAX) return property_by_type < SSC_TYPES_E, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_F_1_MAX) return property_by_type < SSC_TYPES_F_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_F_2_MAX) return property_by_type < SSC_TYPES_F_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_F_3_MAX) return property_by_type < SSC_TYPES_F_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_G_MAX) return property_by_type < SSC_TYPES_G, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_H_MAX) return property_by_type < SSC_TYPES_H, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_I_1_MAX) return property_by_type < SSC_TYPES_I_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_I_2_MAX) return property_by_type < SSC_TYPES_I_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_I_3_MAX) return property_by_type < SSC_TYPES_I_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_J_K_MAX) return property_by_type < SSC_TYPES_J_K, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_L_1_MAX) return property_by_type < SSC_TYPES_L_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_L_2_MAX) return property_by_type < SSC_TYPES_L_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_L_3_MAX) return property_by_type < SSC_TYPES_L_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_1_MAX) return property_by_type < SSC_TYPES_M_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_2_MAX) return property_by_type < SSC_TYPES_M_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_3_MAX) return property_by_type < SSC_TYPES_M_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_4_MAX) return property_by_type < SSC_TYPES_M_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_5_MAX) return property_by_type < SSC_TYPES_M_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_6_MAX) return property_by_type < SSC_TYPES_M_6, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_N_MAX) return property_by_type < SSC_TYPES_N, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_O_MAX) return property_by_type < SSC_TYPES_O, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_1_MAX) return property_by_type < SSC_TYPES_P_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_2_MAX) return property_by_type < SSC_TYPES_P_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_3_MAX) return property_by_type < SSC_TYPES_P_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_4_MAX) return property_by_type < SSC_TYPES_P_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_1_MAX) return property_by_type < SSC_TYPES_R_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_2_MAX) return property_by_type < SSC_TYPES_R_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_3_MAX) return property_by_type < SSC_TYPES_R_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_4_MAX) return property_by_type < SSC_TYPES_R_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_5_MAX) return property_by_type < SSC_TYPES_R_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_R_6_MAX) return property_by_type < SSC_TYPES_R_6, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_1_MAX) return property_by_type < SSC_TYPES_S_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_2_MAX) return property_by_type < SSC_TYPES_S_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_3_MAX) return property_by_type < SSC_TYPES_S_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_4_MAX) return property_by_type < SSC_TYPES_S_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_5_MAX) return property_by_type < SSC_TYPES_S_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_6_MAX) return property_by_type < SSC_TYPES_S_6, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_T_1_MAX) return property_by_type < SSC_TYPES_T_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_T_2_MAX) return property_by_type < SSC_TYPES_T_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_U_1_MAX) return property_by_type < SSC_TYPES_U_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_U_2_MAX) return property_by_type < SSC_TYPES_U_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_V_1_MAX) return property_by_type < SSC_TYPES_V_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_V_2_MAX) return property_by_type < SSC_TYPES_V_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_W_MAX) return property_by_type < SSC_TYPES_W, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_X_1_MAX) return property_by_type < SSC_TYPES_X_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_X_2_MAX) return property_by_type < SSC_TYPES_X_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_Y_Z_MAX) return property_by_type < SSC_TYPES_Y_Z, t_unknown > :: check (args, start, to, nits, t);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
    return property_by_type < SSC_TYPES, t_unknown > :: check (args, start, to, nits, t); }
#endif // LIMITED_META_COMPLEXITY 
