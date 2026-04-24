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
#include "css/css.h"

void distilled::reset ()
{   dcl_.clear ();
    use_.clear ();
    ticks_.clear ();
    cp_.reset ();
    in_progress_ = false; }

void distilled::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto c = dcl_.cbegin (); c != dcl_.cend (); ++c)
        s -> dcl (c -> second.cic_, c -> second.s_, c -> second.count_);
    for (auto c = use_.cbegin (); c != use_.cend (); ++c)
        s -> use (c -> second.cic_, c -> second.s_, c -> second.count_);
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
{   ::std::string res ("distilled:\ndcl:\n");
    res += dcl_.rpt ();
    res += "use:\n";
    res += use_.rpt ();
    res += "media:\n";
    for (auto i = custom_media_.cbegin (); i != custom_media_.cend (); ++i)
        res += i -> first + ":" + i -> second + "\n";
    if (cp_.get () != nullptr) res += cp_ -> rpt ();
    res += ::boost::lexical_cast < ::std::string > (ticks_.size ()) + " ticks\n";
    return res; }
