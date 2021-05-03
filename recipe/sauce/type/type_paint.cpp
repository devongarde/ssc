/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "type/type.h"

// this check is incomplete :-(

bool parse_paint (nitpick& nits, const html_version& v, const ::std::string& d, bool recheck)
{   vstr_t args (split_by_charset (d, " ("));
    if (args.empty ()) return false;
    nitpick nuts, knits;
    e_paintkeyword k = examine_value < t_paintkeyword > (nuts, v, args.at (0));
    switch (k)
    {   case pk_none :
        case pk_contextfill :
        case pk_contextstroke :
        case pk_currentcolour :
            nits.merge (nuts); return true;
        case pk_child :
            if (args.size () == 1) return true;
            if (args.size () > 2) nits.pick (nit_paint, ed_svg_2_0, "13.2. Specifying paint", es_error, ec_type, "child can take at most one parameter");
            return test_value < t_unsigned > (nits, v, args.at (1));
        case pk_inherit :
            nits.merge (nuts);
            if (! recheck) return true;
            nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "'inherit' cannot follow 'url'");
            return false;
        default :
            break; }
    if (test_value < t_colour > (knits, v, d))
    {   nits.merge (knits); return true; }
    ::std::string::size_type bra = d.find_first_of ("(");
    ::std::string::size_type ket = d.find_last_of (")");
    if ((bra != ::std::string::npos) && (ket != ::std::string::npos))
        if (++bra < ket)
            if (test_value < t_colour > (knits, v, args.at (0)))
            {   if (args.at (1).size () >= 9)
                if (compare_complain (nits, v, args.at (1).substr (0, 9), "icc-color"))
                {   ::std::string tmp = trim_the_lot_off (d.substr (bra, ket-bra));
                    if (tmp.at (0) == '#')
                    {   ::std::string::size_type cwsp = tmp.find_first_of (", ");
                        ::std::string n;
                        if (cwsp != ::std::string::npos)
                        {   n = trim_the_lot_off (tmp.substr (cwsp));
                            tmp = tmp.substr (0, cwsp); }
                        if (test_value < t_colour > (knits, v, tmp))
                            if (n.empty () || test_value < t_real > (knits, v, n))
                            {   nits.merge (knits); return true; } } } }
    if ((! recheck) && (d.size () > 2))
        if (compare_complain (nits, v, d.substr (0, 3), "url"))
            if ((bra != ::std::string::npos) && (ket != ::std::string::npos))
                if (++bra < ket)
                {   if (! test_value < t_url > (nits, v, d.substr (bra, ket-bra))) return false;
                    if ((ket + 1 >= d.length ()) || trim_the_lot_off (d.substr (ket + 1)).empty ()) return true;
                    return parse_paint (nits, v, d.substr (ket + 1), true); }
    nits.merge (nuts);
    nits.merge (knits);
    nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "bad paint specification");
    return false; }
