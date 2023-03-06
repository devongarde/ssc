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
#include "simple/type_httpequiv.h"
#include "compound/type_compound.h"

template < > struct type_master < t_csp_ancestor > : type_or_string < t_csp_ancestor, t_csp_sauce, sz_self >
{ using type_or_string < t_csp_ancestor, t_csp_sauce, sz_self > :: type_or_string; };

template < > struct type_master < t_csp_source > : type_either_or < t_csp_source, t_csp_keyword, t_csp_sauce >
{ using type_either_or < t_csp_source, t_csp_keyword, t_csp_sauce > :: type_either_or; };

template < > struct type_master < t_linkargs > : type_at_least_one < t_linkargs, sz_semicolon, t_linkarg >
{ using type_at_least_one < t_linkargs, sz_semicolon, t_linkarg > :: type_at_least_one; };

template < > struct type_master < t_link > : type_one_or_both < t_link, t_linkitself, sz_semicolon, t_linkargs >
{ using type_one_or_both < t_link, t_linkitself, sz_semicolon, t_linkargs > :: type_one_or_both; };

template < > struct type_master < t_links > : type_at_least_one < t_links, sz_comma, t_link >
{ using type_at_least_one < t_links, sz_comma, t_link > :: type_at_least_one; };

template < > struct type_master < t_x_content_type_options > : type_string < t_x_content_type_options, sz_nosniff >
{ using type_string < t_x_content_type_options, sz_nosniff > :: type_string; };
