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
#ifdef LIMITED_META_COMPLEXITY
    if (t <= SSC_TYPES_0_9_MAX) return property_by_type < SSC_TYPES_0_9, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_A_MAX) return property_by_type < SSC_TYPES_A, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_B_MAX) return property_by_type < SSC_TYPES_B, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_C_MAX) return property_by_type < SSC_TYPES_C, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_A_MAX) return property_by_type < SSC_TYPES_CSS_A, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_1_MAX) return property_by_type < SSC_TYPES_CSS_B_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_B_2_MAX) return property_by_type < SSC_TYPES_CSS_B_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_1_MAX) return property_by_type < SSC_TYPES_CSS_C_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_C_2_MAX) return property_by_type < SSC_TYPES_CSS_C_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_D_E_MAX) return property_by_type < SSC_TYPES_CSS_D_E, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_F_1_MAX) return property_by_type < SSC_TYPES_CSS_F_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_F_2_MAX) return property_by_type < SSC_TYPES_CSS_F_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_G_I_MAX) return property_by_type < SSC_TYPES_CSS_G_I, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_J_L_MAX) return property_by_type < SSC_TYPES_CSS_J_L, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_M_N_MAX) return property_by_type < SSC_TYPES_CSS_M_N, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_O_P_MAX) return property_by_type < SSC_TYPES_CSS_O_P, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_R_MAX) return property_by_type < SSC_TYPES_CSS_R, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_S_MAX) return property_by_type < SSC_TYPES_CSS_S, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_1_MAX) return property_by_type < SSC_TYPES_CSS_T_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_T_2_MAX) return property_by_type < SSC_TYPES_CSS_T_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_CSS_U_Z_MAX) return property_by_type < SSC_TYPES_CSS_U_Z, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_D_E_MAX) return property_by_type < SSC_TYPES_D_E, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_F_MAX) return property_by_type < SSC_TYPES_F, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_G_H_MAX) return property_by_type < SSC_TYPES_G_H, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_I_MAX) return property_by_type < SSC_TYPES_I, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_J_L_MAX) return property_by_type < SSC_TYPES_J_L, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_1_MAX) return property_by_type < SSC_TYPES_M_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_M_2_MAX) return property_by_type < SSC_TYPES_M_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_N_O_MAX) return property_by_type < SSC_TYPES_N_O, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_1_MAX) return property_by_type < SSC_TYPES_P_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_P_2_MAX) return property_by_type < SSC_TYPES_P_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_Q_R_MAX) return property_by_type < SSC_TYPES_Q_R, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_S_MAX) return property_by_type < SSC_TYPES_S, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_SVG_MAX) return property_by_type < SSC_TYPES_SVG, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_T_MAX) return property_by_type < SSC_TYPES_T, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_U_MAX) return property_by_type < SSC_TYPES_U, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_V_W_MAX) return property_by_type < SSC_TYPES_V_W, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPES_X_Z_MAX) return property_by_type < SSC_TYPES_X_Z, t_unknown > :: check (args, start, to, nits, t);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
    return property_by_type < SSC_TYPES, t_unknown > :: check (args, start, to, nits, t); }
#endif // LIMITED_META_COMPLEXITY 
