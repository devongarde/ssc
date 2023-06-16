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
#include "css/rule.h"

void rule::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < 0) || (to < len), __FILE__, __LINE__);
    const int b = first_non_whitespace (args.t_, from, to);
    if (b < 0) return;
    nitpick nits = args.t_.at (b).nits_;
    int prev = -1;
    int p = token_find (args.t_, ct_curly_brac, b, to, &prev);
    const int q = p;
    if (p < 0) nits.pick (nit_rule, es_error, ec_css, "properties expected");
    else p = prev;
    if ((p >= 0) && (b >= p))    
        nits.pick (nit_rule, es_error, ec_css, "selector(s) expected");
    else sel_.parse (args, b, p);
    if ((q > 0) && (args.t_.at (q).child_ > 0))
    {   fiddlesticks < selectors > f (&args.ss_, &sel_);
        prop_.parse (args, args.t_.at (q).child_);
        args.had_rule_ = true; } }

void rule::accumulate (stats_t* s) const
{   sel_.accumulate (s);
    prop_.accumulate (s, sel_.get_elements ()); }

::std::string rule::rpt () const
{   ::std::string res (sel_.rpt ());
    res += prop_.rpt ();
    return res; }  

void rule::validate (arguments& args)
{   sel_.validate (args);
    prop_.validate (args); }

void rule::shadow (::std::stringstream& ss, arguments& args)
{   sel_.shadow (ss, args);
    prop_.shadow (ss, args); }
