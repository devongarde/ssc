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
#include "simple/type_jsonic.h"
#include "compound/type_compound.h"

template < > struct type_master < t_js_lang > : type_or_null < t_js_lang, t_lang >
{ using type_or_null < t_js_lang, t_lang > :: type_or_null; };

template < > struct type_master < t_js_type > : type_either_neither < t_js_type, t_text, t_url >
{ using type_either_neither < t_js_type, t_text, t_url > :: type_either_neither; };

template < > struct type_master < t_js_value > : type_one_of_three < t_js_value, t_text, t_tfn, t_fixedpoint >
{ using type_one_of_three < t_js_value, t_text, t_tfn, t_fixedpoint > :: type_one_of_three; };
