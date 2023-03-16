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
#include "css/css_attribute.h"

class css_element;
class selector;
typedef ::std::shared_ptr < css_element > csp_t;
typedef ::std::shared_ptr < selector > csl_t;

class css_fn
{   e_css_fn fn_ = efn_none;
    vstr_t params_;
    ::std::vector < csp_t > ve_;
    ::std::vector < csl_t > vsl_;
public:
    DEFAULT_CONSTRUCTORS (css_fn);
    css_fn (arguments& args, const int from, const int to, const bool coco = false, const bool knotted = false)
    {   parse (args, from, to, coco, knotted); }
    e_css_fn get () const { return fn_; }
    void parse (arguments& args, const int from, const int to, const bool coco = false, const bool knotted = false);
    void validate (arguments& args);
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    ::std::string rpt () const; };
