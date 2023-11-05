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
#include "css/css_state.h"

class css_element;
typedef ::std::shared_ptr < css_element > pel_t;
typedef ::std::vector < pel_t > vpel_t;

class property;
typedef ::std::shared_ptr < property > ppr_t;
typedef ::std::vector < ppr_t > vpr_t;

class properties;
typedef ::std::shared_ptr < properties > pp_t;
typedef ::std::vector < pp_t > vpp_t;

class selector;
typedef ::std::shared_ptr < selector > psel_t;
typedef ::std::vector < psel_t > vpsel_t;

class statement;
typedef ::std::shared_ptr < statement > ps_t;
typedef ::std::vector < ps_t > vps_t;

class statements;
typedef ::std::shared_ptr < statements > pst_t;
typedef ::std::vector < pst_t > vpst_t;
