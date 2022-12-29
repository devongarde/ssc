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

void selectors::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   vstr_t ss (uq2 (trim_the_lot_off (s), UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_TRIM, ","));
    for (auto sss : ss)
        if (! sss.empty ())
        {   sel_.emplace_back (nits, args, sss);
            const ::std::size_t len = sel_.size ();
            PRESUME (len > 0, __FILE__, __LINE__);
            const ::std::string r (sel_.at (len - 1).rpt ());
            if (! r.empty () && (len > 1))
                for (::std::size_t n = 0; n < len - 2; ++n)
                    if (sel_.at (n).rpt () == r)
                        nits.pick (nit_css_syntax, es_warning, ec_css, quote (sss), " is repeated"); } }

void selectors::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto se : sel_)
        se.accumulate (s); }

::std::string selectors::rpt () const
{   ::std::string res;
    for (auto s : sel_)
    {   if (! res.empty ()) res += ",";
        res += s.rpt (); }
    return res; }  
