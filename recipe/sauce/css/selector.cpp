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
#include "css/selector.h"
#include "css/arguments.h"
#include "utility/quote.h"

void selector::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = -1; int prev = -1;
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (b == -1) b = i;
        if ((args.t_.at (i).t_ == ct_whitespace) || (args.t_.at (i).t_ == ct_comment))
        {   if (b != i) ve_.emplace_back (args, b, prev);
            b = -1; }
        prev = i; }
    if (b != -1)
        ve_.emplace_back (args, b, to); }

bool selector::bef_aft () const
{   for (auto e : ve_)
        if (e.bef_aft ()) return true;
    return false; }

void selector::accumulate (stats_t* s) const
{   for (auto e : ve_)
        e.accumulate (s); }

::std::string selector::rpt () const
{   ::std::string res;
    for (auto el : ve_)
    {   if (! res.empty ()) res += " ";
        res += el.rpt (); }
    return res; }  

void selector::validate (arguments& args)
{   for (auto i : ve_)
        i.validate (args); }

void selector::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
