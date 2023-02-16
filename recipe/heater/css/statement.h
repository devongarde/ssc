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
#include "type/type.h"
#include "css/properties.h"
#include "css/rules.h"

class statements;
typedef ::std::shared_ptr < statements > pst_t;
typedef ::std::vector < pst_t > vpst_t;

class statement
{   type_master < t_css_statement > st_;
    properties prop_;
    rules rules_;
    vpst_t vst_;
public:
    DEFAULT_CONSTRUCTORS (statement);
    statement (arguments& args, const int from, const int to)
    {   parse (args, from, to); }
    e_css_statement get () const;
    void parse (arguments& args, const int from, const int to);
    void validate (arguments& args);
    void accumulate (stats_t* s) const;
    ::std::string rpt () const; };

typedef ::std::vector < statement > vst_t;
