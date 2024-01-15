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

class font_feature
{   ::std::string name_, val_;
    ::std::size_t n_ = 0;
public:
    DEFAULT_CONSTRUCTORS (font_feature);
    font_feature (arguments& args, const e_css_statement cs, const int from, const int to)
    {   parse (args, cs, from, to); }
    void parse (arguments& args, const e_css_statement cs, const int from, const int to);
    void validate (arguments& args, const sstr_t& valid, const char* const r);
    void accumulate (stats_t* , const element_bitset& ) const { }
    void shadow (::std::stringstream& ss, arguments& args);
    const ::std::string name () const { return name_; } 
    ::std::string rpt () const; };

typedef ::std::vector < font_feature > vffv_t;
