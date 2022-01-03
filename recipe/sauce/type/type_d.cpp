/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "type/type_master.h"

typedef enum {
    d_nowt, d_a_moveto, d_r_moveto, d_closepath, d_a_lineto, d_r_lineto, d_a_horz, d_r_horz,
    d_a_vert, d_r_vert, d_a_curve, d_r_curve, d_a_smooth, d_r_smooth, d_a_qbc, d_r_qbc,
    d_a_sqbc, d_r_sqbc, d_a_ea, d_r_ea } e_d;

bool checkargs (nitpick& nits, const html_version& , const e_d cmd, const vdbl_t& args, const bool xpt, const char last)
{   bool res = true;
    switch (cmd)
    {   case d_a_horz :
        case d_r_horz :
        case d_a_vert :
        case d_r_vert :
            if (xpt) nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_info, ec_type, "a sequence of '", last, "' is a bit off");
            break;
        case d_a_ea :
        case d_r_ea :
            if (args.size () > 5)
            {   if ((args.at (3) != 1.0) && (args.at (3) != 0.0))
                {   nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a third value of '", last, "' is a large arc flag; it must be one or zero");
                    res = false; }
                if ((args.at (4) != 1.0) && (args.at (4) != 0.0))
                {   nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a fourth value of '", last, "' is a sweep flag; it must be one or zero");
                    res = false; } }
            break;
        default : break; }
    return res; }

bool checknum (nitpick& nits, const html_version& , const unsigned int was, unsigned int& expected, const char last)
{   if (expected > 0) { expected -= 1; return true; }
    if (was == 0) return true;
    nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "'", last, "' expects ", was, " arguments");
    return false; }

bool numend (nitpick& nits, const html_version& v, const e_d cmd, const unsigned int expected, vdbl_t& args, ::std::string& x, const bool& twas, const char last)
{   bool res = true;
    const bool xpt = twas && (expected == 0);
    if (! x.empty ())
    {   args.push_back (lexical < double > :: cast (x)); x.clear (); }
    if (! args.empty ()) {
        if (! checkargs (nits, v, cmd, args, xpt, last)) res = false;
        args.clear (); }
    return res; }

bool parse_d (nitpick& nits, const html_version& v, const ::std::string& d)
{   e_d cmd = d_nowt;
    unsigned int expected = 0, was = 0;
    bool good = true;
    bool num = false; bool in = false; bool twas = false;
    char last = 0;
    ::std::string x;
    vdbl_t args;
    if (d.empty ())
        nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a D attribute cannot be empty");
    else if (d.length () > 1023)
        nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a path specification cannot exceed 1023 characters");
    else for (auto ch : d)
    {   if (::std::iswcntrl (ch)) continue;
        switch (ch)
        {   case '.' : if (! num)
                       {    nits.pick (nit_path_spec, ed_svg_1_0, "11.2.6 The grammar for path data", es_error, ec_type, "A number in path data cannot start with a decimal point");
                            good = false; }
                       in = true; break;
            case 'E' :
            case 'e' : if (! num)
                       {    nits.pick (nit_path_spec, ed_svg_1_0, "11.2.6 The grammar for path data", es_error, ec_type, "A number in path data cannot start with an exponent");
                            good = false; }
                       in = true; break;
            case '-' : num = false; // not clear whether - requires a separator beforehand; I presume not and that it starts a new number
                       in = true; break;
            case '0' :
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' : in = true; break;
            default : break; }
        if (in)
        {   if (! num)
            {   if (! numend (nits, v, cmd, expected, args, x, twas, last)) good = false;
                if (expected == 0) expected = was;
                num = true; }
            x += ch;
            in = false; continue; }
        if (num)
        {   if (! checknum (nits, v, was, expected, last)) good = false;
            twas = true; num = false; }
        switch (ch)
        {   case ' ' :
            case ',' : break;
            case 'A' : if (v.is_svg_12 ())
                       {    nits.pick (nit_path_spec, ed_svg_1_2_tiny, "8 Paths", es_error, ec_type, "SVG 1.2 excludes path command 'A'");
                            good = false; break; }
                       last = ch; cmd = d_a_ea; was = expected = 7; twas = false; break;
            case 'a' : if (v.is_svg_12 ())
                       {    nits.pick (nit_path_spec, ed_svg_1_2_tiny, "8 Paths", es_error, ec_type, "SVG 1.2 excludes path command 'a'");
                            good = false; break; }
                       last = ch; cmd = d_r_ea; was = expected = 7; twas = false; break;
            case 'C' : last = ch; cmd = d_a_curve; was = expected = 6; twas = false; break;
            case 'c' : last = ch; cmd = d_r_curve; was = expected = 6; twas = false; break;
            case 'H' : last = ch; cmd = d_a_horz; was = expected = 1; twas = false; break;
            case 'h' : last = ch; cmd = d_r_horz; was = expected = 1; twas = false; break;
            case 'L' : last = ch; cmd = d_a_lineto; was = expected = 2; twas = false; break;
            case 'l' : last = ch; cmd = d_r_lineto; was = expected = 2; twas = false; break;
            case 'M' : last = ch; cmd = d_a_moveto; was = expected = 2; twas = false; break;
            case 'm' : last = ch; cmd = d_r_moveto; was = expected = 2; twas = false; break;
            case 'Q' : last = ch; cmd = d_a_qbc; was = expected = 4; twas = false; break;
            case 'q' : last = ch; cmd = d_r_qbc; was = expected = 4; twas = false; break;
            case 'S' : last = ch; cmd = d_a_smooth; was = expected = 4; twas = false; break;
            case 's' : last = ch; cmd = d_r_smooth; was = expected = 4; twas = false; break;
            case 'T' : last = ch; cmd = d_a_sqbc; was = expected = 2; twas = false; break;
            case 't' : last = ch; cmd = d_r_sqbc; was = expected = 2; twas = false; break;
            case 'V' : last = ch; cmd = d_a_vert; was = expected = 1; twas = false; break;
            case 'v' : last = ch; cmd = d_r_vert; was = expected = 1; twas = false; break;
            case 'Z' : if (v.svg () == sv_1_0)
                       {    nits.pick (nit_path_spec, ed_svg_1_1, "8.3.3 The closepath command", es_error, ec_type, "path command 'Z' requires SVG 1.1 or better (use 'z')");
                            good = false; break; }
                       last = ch; cmd = d_closepath; was = expected = 0; twas = false; break;
            case 'z' : last = ch; cmd = d_closepath; was = expected = 0; twas = false; break;
            default :
                nits.pick (nit_path_spec, ed_svg_1_0, "11.2 General information about path data", es_error, ec_type, "bad character '", ch, "' in D value");
                good = false; break; }
    }
    if (! numend (nits, v, cmd, expected, args, x, twas, last)) good = false;
    if (! checknum (nits, v, was, expected, last)) good = false;
    return good; }
