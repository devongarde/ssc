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
    if (t <= SSC_TYPE_1_MAX) return property_by_type < SSC_TYPES_1, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_2_MAX) return property_by_type < SSC_TYPES_2, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_3_MAX) return property_by_type < SSC_TYPES_3, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_4_MAX) return property_by_type < SSC_TYPES_4, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_5_MAX) return property_by_type < SSC_TYPES_5, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_6_MAX) return property_by_type < SSC_TYPES_6, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_7_MAX) return property_by_type < SSC_TYPES_7, t_unknown > :: check (args, start, to, nits, t);
    if (t <= SSC_TYPE_8_MAX) return property_by_type < SSC_TYPES_8, t_unknown > :: check (args, start, to, nits, t);
    return property_by_type < SSC_TYPES_9, t_unknown > :: check (args, start, to, nits, t); }
#else // LIMITED_META_COMPLEXITY
    return property_by_type < SSC_TYPES_1, SSC_TYPES_2, SSC_TYPES_3, SSC_TYPES_4, SSC_TYPES_5, SSC_TYPES_6, SSC_TYPES_7, SSC_TYPES_8, SSC_TYPES_9, t_unknown > :: check (args, start, to, nits, t); }
#endif // LIMITED_META_COMPLEXITY 
