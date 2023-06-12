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
#include "type/type.h"
#include "css/arguments.h"
#include "css/properties.h"
#include "utility/quote.h"

void properties::parse (arguments& args, const int from, const int to)
{   PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < len) || (to < 0), __FILE__, __LINE__);
    int b = -1; int prev = -1, brack = 0;
    fiddlesticks < properties > f (&args.ps_, this);
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (b == -1) b = i;
        switch (args.t_.at (i).t_)
        {   case ct_semicolon :
                if (brack == 0)
                {   if (b != i) prop_.emplace_back (args, b, prev);
                    b = -1; }
                break;
            case ct_round_brac :
            case ct_square_brac :
            case ct_curly_brac :
                ++brack;
                break;
            case ct_round_ket :
            case ct_square_ket :
            case ct_curly_ket :
                if (brack > 0) --brack;
                break;
            default :
                break; }
        prev = i; }
    if (b != -1) prop_.emplace_back (args, b, to); }

void properties::accumulate (stats_t* s, const element_bitset& e) const
{   for (auto p : prop_)
        p.accumulate (s, e); }

::std::string properties::rpt () const
{   ::std::string res ("{ ");
    for (auto s : prop_)
    {   if (! res.empty ()) res += "; ";
        res += s.rpt (); }
    res += " }";
    return res; }
  
void properties::validate (arguments& args)
{   fiddlesticks < properties > f (&args.ps_, this);
    for (auto i : prop_)
        i.validate (args); }

void properties::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
