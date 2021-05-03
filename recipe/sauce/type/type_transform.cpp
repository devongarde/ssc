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

bool checkargs (nitpick& nits, const html_version& v, const e_transform_fn cmd, const vstr_t& args)
{   switch (cmd)
    {   case tr_matrix :
            if (args.size () != 6)
            {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "a TRANSFORM matrix requires six parameters");
                return false; }
            break;
        case tr_translate :
        case tr_scale :
            if ((args.size () < 1) || (args.size () > 2))
            {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "both TRANSFORM translate and scale require one or two parameters");
                return false; }
            break;
        case tr_rotate :
        case tr_skewx :
        case tr_skewy :
            if (args.size () != 1)
            {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "TRANSFORM rotate, skew-x and skew-y each require one parameters");
                return false; }
            return test_value < t_angle > (nits, v, args.at (0));
        default :
            DBG_ASSERT (false);
            nits.pick (nit_svg, es_catastrophic, ec_attribute, "internal TRANSFORM error, bad command (", static_cast < int > (cmd), ")");
            return false; }
    for (auto s : args)
        if (! test_value < t_real > (nits, v, s)) return false;
    return true; }

bool parse_transform (nitpick& nits, const html_version& v, const ::std::string& d)
{   e_transform_fn cmd = tr_nowt;
    typedef enum { es_dull, es_bra, es_ket, es_fn, es_out, es_in, es_arg } et_state;
    et_state state = es_dull;
    bool had_comma = false;
    ::std::string name, arg;
    vstr_t args;
    if (d.empty ())
    {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "a TRANSFORM value should transform");
        return false; }
    if ((v.svg_version () > sv_1_1) && (compare_complain (nits, v, "none", d))) return true;
    for (auto ch : d)
    {   if (ch != ',') had_comma = false;
        if (::std::iswcntrl (ch)) continue;
        switch (ch)
        {   case ',' :
                if (had_comma)
                {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected ',' in TRANSFORM value");
                    return false; }
                switch (state)
                {   case es_dull :
                    case es_bra :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected ',' in TRANSFORM value");
                        return false;
                    default : break; }
                had_comma = true;
                // drop thru'
            case ' ' :
                switch (state)
                {   case es_arg :
                        args.emplace_back (arg);
                        arg.clear ();
                        state = es_in;
                        break;
                    case es_bra :
                        state = es_in;
                        break;
                    case es_fn :
                        cmd = examine_value < t_transform_fn > (nits, v, name);
                        if (cmd == tr_nowt) return false;
                        name.clear ();
                        state = es_out;
                        break;
                    case es_dull :
                        break;
                    case es_ket :
                        state = es_out;
                        break;
                    default :
                        return false; }
                break;
            case '(' :
                switch (state)
                {   case es_out :
                    case es_dull :
                        break;
                    case es_fn :
                        cmd = examine_value < t_transform_fn > (nits, v, name);
                        if (cmd == tr_nowt) return false;
                        name.clear ();
                        break;
                    default :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected '(' in TRANSFORM value");
                        return false; }
                state = es_bra;
                break;
            case ')' :
                switch (state)
                {   case es_bra :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "empty brackets in TRANSFORM value");
                        return false;
                    case es_in :
                    case es_arg :
                        args.emplace_back (arg);
                        if (! checkargs (nits, v, cmd, args)) return false;
                        arg.clear ();
                        args.clear ();
                        state = es_ket;
                        break;
                    default :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected ')' in TRANSFORM value");
                        return false; }
                break;
            default :
                if (((ch >= 'A') && (ch <= 'Z')) ||
                    ((ch >= 'a') && (ch <= 'z')) ||
                    ((ch >= '0') && (ch <= '9')) ||
                    (ch == '.') || (ch == '-') || (ch == '+'))
                switch (state)
                {   case es_fn :
                    case es_out :
                    case es_dull :
                    case es_ket :
                        name += ch;
                        state = es_fn;
                        continue;
                    case es_in :
                    case es_arg :
                    case es_bra :
                        arg += ch;
                        state = es_arg;
                        continue;
                    default : break; }
                nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected '", ch, "' in TRANSFORM value");
                return false; } }
    if ((state == es_ket) || (state == es_out)) return true;
    nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected end of TRANSFORM value");
    return false; }
