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
#include "css/selectors.h"
#include "css/arguments.h"
#include "utility/quote.h"

void selectors::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = -1; int prev = -1;
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (b == -1) b = i;
        if (args.t_.at (i).t_ == ct_comma)
        {   if (b != i) sel_.emplace_back (args, b, prev);
            b = -1; }
        prev = i; }
    if (b != -1)
        sel_.emplace_back (args, b, to);
    if (! sel_.empty ())
    {   nitpick& nits = args.t_.at (from).nits_;
        len = GSL_NARROW_CAST < int > (sel_.size ());
        const ::std::string r (sel_.at (len - 1).rpt ());
        if (! r.empty () && (len > 1))
            for (int n = 0; n < len - 2; ++n)
                if (sel_.at (n).rpt () == r)
                    nits.pick (nit_selector, es_warning, ec_css, quote (r), " is repeated"); } }

bool selectors::bef_aft () const
{   for (auto se : sel_)
        if (se.bef_aft ()) return true;
    return false; }

void selectors::accumulate (stats_t* s) const
{   for (auto se : sel_)
        se.accumulate (s); }

::std::string selectors::rpt () const
{   ::std::string res;
    for (auto s : sel_)
    {   if (! res.empty ()) res += ",";
        res += s.rpt (); }
    return res; }  

void selectors::validate (arguments& args)
{   for (auto i : sel_)
        i.validate (args); }

void selectors::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : sel_)
        i.shadow (ss, args); }
