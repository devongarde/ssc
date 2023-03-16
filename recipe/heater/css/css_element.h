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
#include "main/enum.h"
#include "element/elem.h"
#include "css/decoration.h"
#include "css/arguments.h"

class css_element
{   elem e_;
    vcd_t decore_;
public:
    DEFAULT_CONSTRUCTORS (css_element);
    explicit css_element (const elem& e) : e_ (e) { }
    explicit css_element (const e_element e) : e_ (e) { }
    explicit css_element (nitpick& nits, const html_version& v, const namespaces_ptr& ns, const ::std::string& x) : e_ (nits, v, ns, x) { }
    css_element (arguments& args, const int from, const int to, const bool knotted = false)
    {   parse (args, from, to, knotted); }
    void parse (arguments& args, const int from, const int to, const bool knotted = false);
    bool bef_aft () const;
    const element_bitset get_elements () const { return element_bitset (e_.get ()); }
    void validate (arguments& args);
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    ::std::string rpt () const; };

typedef ::std::vector < css_element > vcel_t;
