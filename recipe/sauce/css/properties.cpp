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
#include "type/type_enum.h"
#include "css/arguments.h"
#include "css/properties.h"
#include "utility/quote.h"

void properties::parse (v_np& ticks, const int loc, arguments& args, const ::std::string& s)
{   vstr_t ss (uq2 (s, UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_BRACE | UQ_TRIM, ";"));
    for (auto sss : ss)
        if (! sss.empty ())
        {   nitpick nits;
            nits.set_context (loc, sss);
            property p;
            p.parse (nits, args, sss);
            prop_.push_back (p);
            if (! nits.empty ()) ticks.push_back (nits); } }

void properties::accumulate (stats_t* s) const
{  VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto p : prop_)
        p.accumulate (s); }

::std::string properties::rpt () const
{   ::std::string res ("{ ");
    for (auto s : prop_)
    {   if (! res.empty ()) res += "; ";
        res += s.rpt (); }
    res += " }";
    return res; }  
