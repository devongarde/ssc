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
#include "type/enum.h"
#include "attribute/attr.h"
#include "css/arguments.h"

class css_attribute
{   attr a_;
    bool has_value_ = false;
    ::std::string name_, value_;
    e_css_attribute_value eat_ = eat_any;
    explicit css_attribute (nitpick& nits, const html_version& v, const namespaces_ptr& ns, const ::std::string& s)
        : a_ (nits, v, ns, s, name_) { }
public:
    DEFAULT_CONSTRUCTORS (css_attribute);
    css_attribute (arguments& args, const int from, const int to = -1)
    {   parse (args, from, to); }
    void parse (arguments& args, const int from, const int to = -1);
    void validate (arguments& ) const { }
    void accumulate (stats_t* s, const e_element e) const;
   ::std::string rpt () const; };

typedef ::std::shared_ptr < css_attribute > pcs_t;
