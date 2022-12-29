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

void rules::parse (v_np& ticks, arguments& args, const ::std::string& s, const int line)
{   vint_t lines;
    vstr_t ss (uq2 (s, UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_BRACE | UQ_TRIM | UQ_16 | UQ_UNIFY, "}", &lines, &ticks));
    unsigned count = 0;
    for (auto sss : ss)
    {   PRESUME (count < lines.size (), __FILE__, __LINE__);
        rule r;
        r.parse (ticks, lines.at (count++) + line, args, sss);
        rules_.push_back (r); } }

void rules::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto r : rules_)
        r.accumulate (s); }

::std::string rules::rpt () const
{   ::std::string res;
    for (auto r : rules_)
        res += r.rpt () + "\n";
    return res; }  
