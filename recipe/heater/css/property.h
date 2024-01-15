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
#include "css/typed_property.h"
#include "css/arguments.h"
#include "css/weight.h"
#include "css/css_pre.h"

class property
{   property_v_ptr prop_;
    weight w_;
    ::std::string name_, val_;
    flags_t flags_ = NOFLAGS;
    int from_ = 0;
    ps_t duff_;
    vpst_t st_;
    psel_t sel_;
    pp_t pp_;
public:
    DEFAULT_CONSTRUCTORS (property);
    property (arguments& args, const int from, const int to)
    {   parse (args, from, to); }
    void parse (arguments& args, const int from, const int to);
    void validate (arguments& args);
    void accumulate (stats_t* s, const element_bitset& e) const;
    void shadow (::std::stringstream& ss, arguments& args);
    const ::std::string name () const { return name_; } 
    void name (arguments& args, const ::std::string& n);
    ::std::string rpt () const; };
