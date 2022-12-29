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
#include "css/css_element.h"
#include "css/arguments.h"
#include "type/enum.h"
#include "type/type_enum.h"
#include "element/state.h"

#define SEL_SEPS ":.#["

void css_element::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    const ::std::string sep = SEL_SEPS;
    const vstr_t argles (uq2 (s, UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_SEP | UQ_ROUND | UQ_TRIM, sep));
    const ::std::size_t len = argles.size ();
    PRESUME (len > 0, __FILE__, __LINE__);
    const bool all = (argles.at (0).length () == 1) && (sep.find_first_of (argles.at (0).at (0)) != ::std::string::npos);
    if (all)
    {   css_element e (elem_css_all);
        swap (e); }
    else
    {   css_element e (nits, args.v_, args.ns_, argles.at (0));
        swap (e); }
    const unsigned ko = (all ? 0 : 1);
    if (len > ko)
        if (faux_bitset.test (e_.get ()) && (e_.get () != elem_css_all))
            nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, e_.name (), " cannot be decorated");
        else
        {   ::std::string ss;
            for (vstr_t::size_type x = ko; x < len; ++x)
            {   const ::std::string ssss (argles.at (x));
                if (! ssss.empty ())
                    if ((ssss.length () == 1) && (sep.find_first_of (ssss.at (0)) != ::std::string::npos)) ss = ssss;
                    else
                        decore_.emplace_back (nits, args, ss, ssss); } } }

void css_element::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (e_);
    for (auto d : decore_)
        d.accumulate (s, e_.get ()); }

::std::string css_element::rpt () const
{   ::std::string res (e_.name ());
    for (auto d : decore_)
        res += d.rpt ();
    return res; }
