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
#include "css/typed_property.h"
#include "css/arguments.h"
#include "css/weight.h"

class property
{   property_v_ptr prop_;
    weight w_;
public:
    DEFAULT_CONSTRUCTORS (property);
    property (nitpick& nits, arguments& args, const ::std::string& s)
    {   parse (nits, args, s); }
    void swap (property& p) noexcept
    {   prop_.swap (p.prop_);
        w_.swap (p.w_); }
    void reset ()
    {   property p;
        swap (p); }
    void parse (nitpick& nits, arguments& args, const ::std::string& s);
    void accumulate (stats_t* s) const;
    ::std::string rpt () const; };

typedef ::std::vector < property > vpr_t;
