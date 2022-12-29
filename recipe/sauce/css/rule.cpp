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

void rule::parse (v_np& ticks, const int loc, arguments& args, const ::std::string& s)
{   nitpick nits, knots;
    PRESUME (! s.empty (), __FILE__, __LINE__);
    PRESUME (s.at (0) != '@', __FILE__, __LINE__);
    const ::std::string::size_type pos = s.find ("{");
    if (pos == ::std::string::npos)
    {   nits.set_context (loc, s);
        nits.pick (nit_css_syntax, es_error, ec_css, "Expecting {");
        ticks.push_back (nits); }
    else
    {   const ::std::string sels (trim_the_lot_off (s.substr (0, pos)));
        const ::std::string props = trim_the_lot_off (s.substr (pos+1));
        knots.set_context (loc, sels);
        if (sels.empty ()) sel_.init (elem_css_all);
        else sel_.parse (knots, args, sels);
        if (! knots.empty ()) ticks.push_back (knots);
        if (props.empty ())
        {   nits.pick (nit_css_syntax, es_error, ec_css, "missing properties");
            ticks.push_back (nits); }
        else prop_.parse (ticks, loc, args, props); } }

void rule::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    sel_.accumulate (s);
    prop_.accumulate (s); }

::std::string rule::rpt () const
{   ::std::string res (sel_.rpt ());
    return res; }  
