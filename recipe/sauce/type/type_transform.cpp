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

const ::std::size_t maxfnargs = 6;

struct fnarg_t {
    e_transform_fn      fn_ = tr_nowt;
    e_type              args_ [maxfnargs];
    fnarg_t (   const e_transform_fn fn = tr_nowt,
                const e_type t1 = t_unknown, const e_type t2 = t_unknown, const e_type t3 = t_unknown,
                const e_type t4 = t_unknown, const e_type t5 = t_unknown, const e_type t6 = t_unknown)
        : fn_ (fn)
    {   args_ [0] = t1;
        args_ [1] = t2;
        args_ [2] = t3;
        args_ [3] = t4;
        args_ [4] = t5;
        args_ [5] = t6; }
    void reset (const e_transform_fn fn = tr_nowt,
                const e_type t1 = t_unknown, const e_type t2 = t_unknown, const e_type t3 = t_unknown,
                const e_type t4 = t_unknown, const e_type t5 = t_unknown, const e_type t6 = t_unknown)
    {   fn_ = fn;
        args_ [0] = t1;
        args_ [1] = t2;
        args_ [2] = t3;
        args_ [3] = t4;
        args_ [4] = t5;
        args_ [5] = t6; } };

fnarg_t fnarg [] =
{   {   tr_matrix, t_real, t_real, t_real, t_real, t_real, t_real },
    {   tr_ref, t_svg_svg, t_real, t_real },
    {   tr_translate, t_measure, t_measure },
    {   tr_translatex, t_measure },
    {   tr_translatey, t_measure },
    {   tr_scale, t_real, t_real },
    {   tr_scalex, t_measure },
    {   tr_scaley, t_measure },
    {   tr_rotate, t_angle },
    {   tr_skew, t_angle, t_angle },
    {   tr_skewx, t_angle },
    {   tr_skewy, t_angle },
    {   tr_nowt } };

typedef ::std::vector < fnarg_t > va_t;

bool checkargs (nitpick& nits, const html_version& v, const e_transform_fn cmd, const vstr_t& args)
{   static va_t va;
    if (va.empty ())
    {   va.resize (max_transform_fn + 1);
        for (int x = 0; fnarg [x].fn_ != tr_nowt; ++x)
            va.at (fnarg [x].fn_).reset (fnarg [x].fn_, fnarg [x].args_ [0], fnarg [x].args_ [1], fnarg [x].args_ [2], fnarg [x].args_ [3], fnarg [x].args_ [4], fnarg [x].args_ [5]); }
    DBG_ASSERT (static_cast < ::std::size_t > (cmd) < va.size ());
    DBG_ASSERT (va.at (static_cast < ::std::size_t > (cmd)).fn_ == cmd);
    html_version lh (type_master < t_transform_fn > :: first_version (cmd));
    ::std::size_t low = lh.minargs ();
    ::std::size_t high = lh.maxargs ();
    DBG_ASSERT (low <= maxfnargs);
    DBG_ASSERT (high <= maxfnargs);
    if ((args.size () < low) || (args.size () > high))
    {   if (v.svg_version () < sv_2_0)
            if (low == high)
                nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type,
                    "a TRANSFORM ", quote (type_master < t_transform_fn > :: name (cmd)), " expects ", low, " parameter(s)");
            else
                nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type,
                    "a TRANSFORM ", quote (type_master < t_transform_fn > :: name (cmd)), " expects between ", low, " and ", high, " parameters");
        else
            if (low == high)
                nits.pick (nit_transform, ed_css_transform, "9. The Transform Functions", es_error, ec_type,
                    "a TRANSFORM ", quote (type_master < t_transform_fn > :: name (cmd)), " expects ", low, " parameter(s)");
            else
                nits.pick (nit_transform, ed_css_transform, "9. The Transform Functions", es_error, ec_type,
                    "a TRANSFORM ", quote (type_master < t_transform_fn > :: name (cmd)), " expects between ", low, " and ", high, " parameters"); }
    bool res = true;
    for (::std::size_t i = 0; i < ::std::min (high, args.size ()); ++i)
    {   DBG_ASSERT (va.at (cmd).args_ [i] != t_unknown);
        if (! test_value (nits, v, va.at (cmd).args_ [i], args.at (i))) res = false; }
    return res; }

bool parse_transform (nitpick& nits, const html_version& v, const ::std::string& d)
{   e_transform_fn cmd = tr_nowt;
    typedef enum { es_dull, es_bra, es_ket, es_fn, es_out, es_in, es_arg } et_state;
    et_state state = es_dull;
    bool had_comma = false;
    bool res = true;
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
                if (had_comma || (state == es_dull) || (state == es_bra))
                {   nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected ',' in TRANSFORM value");
                    res = false; }
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
                        if (cmd == tr_nowt) res = false;
                        name.clear ();
                        state = es_out;
                        break;
//                    case es_dull :
//                        break;
                    case es_ket :
                        state = es_out;
                        break;
                    default :
                        break; }
                break;
            case '(' :
                switch (state)
                {   case es_out :
                    case es_dull :
                        break;
                    case es_fn :
                        cmd = examine_value < t_transform_fn > (nits, v, name);
                        if (cmd == tr_nowt) res = false;
                        name.clear ();
                        break;
                    default :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected '(' in TRANSFORM value");
                        res = false; }
                state = es_bra;
                break;
            case ')' :
                switch (state)
                {   case es_bra :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "empty brackets in TRANSFORM value");
                        arg.clear ();
                        args.clear ();
                        res = false;
                        state = es_ket;
                        break;
                    case es_in :
                    case es_arg :
                        args.emplace_back (arg);
                        if ((cmd != tr_nowt) && ! checkargs (nits, v, cmd, args)) res = false;
                        arg.clear ();
                        args.clear ();
                        state = es_ket;
                        break;
                    default :
                        nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected ')' in TRANSFORM value");
                        res = false; }
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
    if ((state == es_ket) || (state == es_out)) return res;
    nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_error, ec_type, "unexpected end of TRANSFORM value");
    return false; }
