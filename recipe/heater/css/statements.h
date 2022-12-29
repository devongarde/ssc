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
#include "css/rules.h"
#include "css/statement.h"
#include "css/arguments.h"

class page;

class statements
{   vrs_t rules_;
    vst_t statements_;
    v_np ticks_;
public:
    DEFAULT_CONSTRUCTORS (statements);
    statements (arguments& args, const ::std::string& s)
    {   parse (args, s); }
    void parse (arguments& args, const ::std::string& s);
    void swap (statements& r) noexcept
    {   rules_.swap (r.rules_); }
    void reset ()
    {   statements st;
        swap (st); }
    void clear () noexcept { rules_.clear (); }
    const element_bitset get_elements () const
    {   element_bitset res;
        for (auto r : rules_) res |= r.get_elements ();
        return res; }
    void merge (nitpick& nits) const
    {   for (auto n : ticks_)
            nits.merge (n); } 
    bool nitted () const
    {   return ! ticks_.empty (); }
    void accumulate (nitpick& nits) const;
    void accumulate (stats_t* s) const;
    ::std::string review (const mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
    {   ::std::string res;
        for (auto n : ticks_)
            res += n.review (mac, entry, head, foot, page_head, unfiltered);
        return res; }
    ::std::string rpt () const; };
