/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

#ifdef NO_JSONIC
#else // NO_JSONIC
class jsonic
{   ::boost::json::value value_;
    static ::std::string rpt_base (const ::boost::json::value& val, const int indent);
public:
    jsonic () = default;
    jsonic (const jsonic& j) = delete;
    void reset () noexcept
    {   value_.emplace_null (); }
    const ::boost::json::value& val () const noexcept { return value_; }
    ::boost::json::value& val () noexcept { return value_; }
    bool parse (nitpick& nits, const ::std::string& s, const e_charcode encoding);
    static ::std::string rpt (const ::boost::json::value& val, const int indent = 0)
    {   return ::std::string (indent*2, ' ') + rpt_base (val, indent); } };
#endif // NO_JSONIC
