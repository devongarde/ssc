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

#include "main/standard.h"
#include "css/distilled.h"
#include "utility/common.h"
#include "element/elem.h"
#include "stats/stats.h"
#include "css/arguments.h"

void distilled::reset ()
{   class_.clear ();
    id_.clear ();
    element_class_.clear ();
    element_id_.clear ();
    font_.clear ();
    ticks_.clear ();
    cp_.reset ();
    in_progress_ = false; }

bool distilled::has_element_class (const e_element e, const ::std::string& s) const
{   const ::std::string l (elem::name (e) + "." + s);
    return (element_class_.find (l) != element_class_.cend ()); }

bool distilled::has_element_id (const e_element e, const ::std::string& s) const
{   const ::std::string l (elem::name (e) + "#" + s);
    return (element_id_.find (l) != element_id_.cend ()); }

void distilled::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto c : class_)
        s -> dcl_class (c.first, c.second);
    for (auto c : id_)
        s -> dcl_id (c.first, c.second);
    for (auto c : element_class_)
        s -> dcl_element_class (c.first, c.second);
    for (auto c : element_id_)
        s -> dcl_element_id (c.first, c.second);
    for (auto c : font_)
        s -> mark_font (c.first, c.second); }

::std::string distilled::review (const mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered)
{   // here, cp_ is borked
    ::std::string res;
    for (auto n : ticks_)
        res += n.review (mac, entry, head, foot, page_head, unfiltered);
    ticks_.clear ();
    return res; }

::std::string distilled::report () const
{   ::std::string res;

    return res; }
