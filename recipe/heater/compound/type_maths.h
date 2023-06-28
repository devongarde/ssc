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
#include "simple/type_math.h"
#include "compound/type_compound.h"

template < > struct type_master < t_mathvertauto > : type_or_string < t_mathvertauto, t_vunit, sz_auto >
{ using type_or_string < t_mathvertauto, t_vunit, sz_auto > :: type_or_string; };

template < > struct type_master < t_vunits > : type_at_least_none < t_vunits, sz_space_char, t_vunit >
{ using type_at_least_none < t_vunits, sz_space_char, t_vunit > :: type_at_least_none; };

template < > struct type_master < t_intent > : type_one_of_four < t_intent, t_intent_conlit, t_real, t_intent_ref, t_intent_app >
{ using type_one_of_four < t_intent, t_intent_conlit, t_real, t_intent_ref, t_intent_app > :: type_one_of_four; };
