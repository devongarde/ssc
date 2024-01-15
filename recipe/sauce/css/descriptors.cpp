/*
ssc (static site checker)
File Info
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
#include "css/descriptors.h"
#include "utility/quote.h"

void descriptors::parse (arguments& args, const e_css_statement cs, const int from, const int to)
{   PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < len) || (to < 0), __FILE__, __LINE__);
    int b = -1; int prev = -1;
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (args.t_.at (i).t_ == ct_semicolon)
        {   if (b != i) dsc_.emplace_back (args, cs, b, prev);
            b = -1; }
        else if (b == -1) b = i;
        prev = i; }
    if (b != -1) dsc_.emplace_back (args, cs, b, to); }

void descriptors::accumulate (stats_t* s, const element_bitset& e) const
{   for (auto p : dsc_)
        p.accumulate (s, e); }

::std::string descriptors::rpt () const
{   ::std::string res ("{ ");
    for (auto s : dsc_)
    {   if (! res.empty ()) res += "; ";
        res += s.rpt (); }
    res += " }";
    return res; }
  
void descriptors::validate (arguments& args)
{   for (auto i : dsc_)
        i.validate (args); }

void descriptors::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
