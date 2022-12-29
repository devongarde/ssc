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
#include "css/selector.h"

class selectors
{   vsel_t sel_;
public:
    DEFAULT_CONSTRUCTORS (selectors);
    explicit selectors (const e_element e) { sel_.emplace_back (e); }
    selectors (nitpick& nits, arguments& args, const ::std::string& s)
    {   parse (nits, args, s); }
    void swap (selectors& r) noexcept
    {  sel_.swap (r.sel_); }
    void reset ()
    {   selectors s;
        swap (s); }
    void parse (nitpick& nits, arguments& args, const ::std::string& s);
    void init (const e_element e) { sel_.clear (); sel_.emplace_back (e); }
    const element_bitset get_elements () const
    {   element_bitset res;
        for (auto r : sel_) res |= r.get_elements ();
        return res; }
    void accumulate (stats_t* s) const;
    ::std::string rpt () const; };