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
#include "feedback/nitpick.h"
#include "css/css_element.h"

class selector
{   vcel_t ve_;
public:
    DEFAULT_CONSTRUCTORS (selector);
    explicit selector (const e_element e) { ve_.emplace_back (e); }
    selector (arguments& args, const int from, const int to, const bool knotted = false)
    {   parse (args, from, to, knotted); }
    void parse (arguments& args, const int from, const int to, const bool knotted = false);
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    const element_bitset get_elements () const
    {   element_bitset res;
        for (auto r : ve_) res |= r.get_elements ();
        return res; }
    void validate (arguments& args);
    bool bef_aft () const;
    ::std::string rpt () const; };

typedef ::std::vector < selector > vsel_t;
