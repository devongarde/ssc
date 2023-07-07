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
#include "css/ffv.h"

class font_features
{   vffv_t ff_;
public:
    DEFAULT_CONSTRUCTORS (font_features);
    font_features (arguments& args, const e_css_statement cs, const int from, const int to = -1)
    {   parse (args, cs, from, to); }
    void parse (arguments& args, const e_css_statement cs, const int from, const int to = -1);
    void validate  (arguments& args, const sstr_t& valid, const char* const r);
    void accumulate (stats_t* s, const element_bitset& e) const;
    void shadow (::std::stringstream& ss, arguments& args);
   ::std::string rpt () const; };
