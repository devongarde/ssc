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
#include "css/rules.h"
#include "utility/quote.h"

void rules::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < 0) || (to < len), __FILE__, __LINE__);
    int i = first_non_whitespace (args.t_, from, to);
    while (i >= 0)
    {   const int brac = token_find (args.t_, ct_curly_brac, i, to);
        rule_.emplace_back (args, i, brac);
        if (brac < 0) break;
        i = next_non_whitespace (args.t_, brac, to); } }

void rules::accumulate (stats_t* s) const
{   for (auto r : rule_)
        r.accumulate (s); }

::std::string rules::rpt () const
{   ::std::string res;
    for (auto r : rule_)
        res += r.rpt () + "\n";
    return res; }  

void rules::validate (arguments& args)
{   for (auto i : rule_)
        i.validate (args); }

void rules::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : rule_)
        i.shadow (ss, args); }
