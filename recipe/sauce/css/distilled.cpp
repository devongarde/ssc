/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
{   //class_.clear ();
    //id_.clear ();
    //element_class_.clear ();
    //element_id_.clear ();
    //font_.clear ();
    cat_.clear ();
    ticks_.clear ();
    cp_.reset ();
    in_progress_ = false; }

bool distilled::has_element_class (const e_element e, const ::std::string& s) const
{   const ::std::string l (elem::name (e) + "." + s);
    return (cat_.find (l) != oops_a_daisy); }

bool distilled::has_element_id (const e_element e, const ::std::string& s) const
{   const ::std::string l (elem::name (e) + "#" + s);
    return (cat_.find (l) != oops_a_daisy); }

void distilled::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto c = cat_.cbegin (); c != cat_.cend (); ++c)
        switch (c -> second.cic_)
        {   case cic_class :        s -> dcl_class (c -> second.s_, c -> second.count_); break;
            case cic_custom_prop :  s -> dcl_custom_prop (c -> second.s_, c -> second.count_); break;
            case cic_id :           s -> dcl_id (c -> second.s_, c -> second.count_); break;
            case cic_element_class :s -> dcl_element_class (c -> second.s_, c -> second.count_); break;
            case cic_element_id :   s -> dcl_element_id (c -> second.s_, c -> second.count_); break;
            case cic_font :         s -> mark_font (c -> second.s_, c -> second.count_); break;
                // add for functions
            default : break; }
    for (int i = 0; i < gst_max; ++i)
        for (auto c : str_.at (i))
            s -> mark_str (static_cast < e_gsstr > (i), c); }

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
