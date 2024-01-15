/*
ssc (static site checker)
File Info
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
#include "enum/type_lang.h"
#include "compound/type_compound.h"

template < > struct type_master < t_langs > : type_at_least_one < t_langs, sz_comma, t_lang >
{ using type_at_least_one < t_langs, sz_comma, t_lang > :: type_at_least_one; };

// t_lang_n
template < > struct type_master < t_lang_n > : type_or_string < t_lang_n, t_lang, sz_normal >
{ using type_or_string < t_lang_n, t_lang, sz_normal > :: type_or_string; };

template < > struct type_master < t_langq > : type_one_or_both < t_langq, t_lang, sz_semicolon, t_q >
{ using type_one_or_both < t_langq, t_lang, sz_semicolon, t_q > :: type_one_or_both; };

template < > struct type_master < t_langqs > : type_at_least_one < t_langqs, sz_comma, t_langq >
{ using type_at_least_one < t_langqs, sz_comma, t_langq > :: type_at_least_one; };
