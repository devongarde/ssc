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

void selector::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   vstr_t ss (uq2 (s, UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_TRIM, " "));
    for (auto sss : ss)
        if (! sss.empty ())
            ve_.emplace_back (nits, args, sss); }

void selector::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto e : ve_)
        e.accumulate (s); }

::std::string selector::rpt () const
{   ::std::string res;
    for (auto el : ve_)
    {   if (! res.empty ()) res += " ";
        res += el.rpt (); }
    return res; }  
