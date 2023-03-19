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
#include "simple/type_cookie.h"
#include "simple/type_misc.h"
#include "compound/type_compound.h"

template < > struct type_master < t_cookies > : type_at_least_one < t_cookies, sz_semicolon, t_cookie >
{ using type_at_least_one < t_cookies, sz_semicolon, t_cookie > :: type_at_least_one; };

template < > struct type_master < t_xlinktype > : type_string < t_xlinktype, sz_simple >
{ using type_string < t_xlinktype, sz_simple > :: type_string; };

template < > struct type_master < t_css_all_2 > : public type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset >
{   using type_sz < t_css_all_2, sz_initial, sz_inherit, sz_unset > :: type_sz; };

template < > struct type_master < t_svg_src > : public either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit >
{   using either_type_or_either_string < t_svg_src, t_css_local_url, t_svg_two_profile, sz_srgb, sz_inherit > :: either_type_or_either_string; };
