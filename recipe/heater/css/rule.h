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
#include "css/properties.h"

class rule
{   selectors sel_;
    properties prop_;
public:
    DEFAULT_CONSTRUCTORS (rule);
    rule (v_np& ticks, const int loc, arguments& args, const ::std::string& s)
    {   parse (ticks, loc, args, s); }
    void swap (rule& r) noexcept
    {   prop_.swap (r.prop_);
        sel_.swap (r.sel_); }
    void reset ()
    {   rule r;
        swap (r); }
    void parse (v_np& ticks, const int loc, arguments& args, const ::std::string& s);
    const element_bitset get_elements () const
    {   return sel_.get_elements (); }
    void accumulate (stats_t* s) const;
    ::std::string rpt () const; };

typedef ::std::vector < rule > vrule_t;
