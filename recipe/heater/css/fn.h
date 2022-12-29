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
#include "element/elem.h"
#include "css/css_attribute.h"

class css_element;
typedef ::std::shared_ptr < css_element > csp_t;

class css_fn
{   e_css_fn fn_ = efn_none;
    vstr_t params_;
    ::std::vector < csp_t > ve_;
public:
    DEFAULT_CONSTRUCTORS (css_fn);
    css_fn (nitpick& nits, arguments& args, const ::std::string& s)
    {   parse (nits, args, s); }
    void swap (css_fn& f) noexcept
    {   ::std::swap (fn_, f.fn_);
        params_.swap (f.params_);
        ve_.swap (f.ve_); }
    void reset ()
    {   css_fn f;
        swap (f); }
    void parse (nitpick& nits, arguments& args, const ::std::string& s);
    void accumulate (stats_t* s) const;
    ::std::string rpt () const; };
