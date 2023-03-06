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
#include "css/selectors.h"
#include "css/rule.h"
#include "css/arguments.h"

class page;

class rules
{   friend class statements;
    vrule_t rule_;
public:
    DEFAULT_CONSTRUCTORS (rules);
    rules (arguments& args, const int from, const int to)
    {   parse (args, from, to); }
    void parse (arguments& args, const int from, const int to);
    void clear () noexcept { rule_.clear (); }
    const element_bitset get_elements () const
    {   element_bitset res;
        for (auto r : rule_) res |= r.get_elements ();
        return res; }
    void validate (arguments& args);
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    ::std::string rpt () const; };

typedef ::std::vector < rules > vrs_t;
