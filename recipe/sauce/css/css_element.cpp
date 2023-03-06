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
#include "main/enum.h"
#include "type/type.h"
#include "element/state.h"

#define SEL_SEPS ":.#["

void css_element::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    nitpick& nits = args.t_.at (from).nits_;
    int b = first_non_whitespace (args.t_, from, to);
    if (b == -1) return;
    bool pseudo = true;
    switch (args.t_.at (from).t_)
    {   case ct_splat :
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, "* requires CSS 2.0 or better");
            else
            {   css_element e (elem_css_all);
                ::std::swap (*this, e);
                b = next_non_whitespace (args.t_, b, to); }
            break;
        case ct_hash :
        case ct_dot :
        case ct_colon :
        case ct_square_brac :
            {   css_element e (elem_css_all);
                ::std::swap (*this, e); }
            break;
        case ct_gt :
            pseudo = false;
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, "> requires CSS 2.0 or better");
            else
            {   css_element e (elem_css_child);
                ::std::swap (*this, e); }
            break;
        case ct_plus :
            pseudo = false;
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, "+ requires CSS 2.0 or better");
            else
            {   css_element e (elem_css_precede_immediate);
                ::std::swap (*this, e); }
            break;
        case ct_squiggle :
            pseudo = false;
            if (context.html_ver ().css_version () < css_3)
                nits.pick (nit_css_version, es_error, ec_css, "~ requires CSS 3 selectors or better");
            else
            {   css_element e (elem_css_precede);
                ::std::swap (*this, e); }
            break;
        case ct_keyword :
            {   css_element e (nits, args.v_, args.ns_, args.t_.at (from).val_);
                ::std::swap (*this, e);
                b = next_non_whitespace (args.t_, b, to); }
            break;
        default :
            nits.pick (nit_css_element, es_error, ec_css, quote (tkn_rpt (args.t_.at (from))), ": element expected");
            return; }
    if (! pseudo)
    {   if ((b > 0) && (b < to))
        {   b = next_non_whitespace (args.t_, b, to);
            switch (args.t_.at (b).t_)
            {   case ct_hash :
                case ct_dot :
                case ct_colon :
                case ct_square_brac :
                    nits.pick (nit_naughty_decoration, es_error, ec_css, quote (tkn_rpt (args.t_.at (from))), " cannot be decorated");
                    break;
                default:
                    parse (args, b, to);
                    break; } }
        return; }
    for (int i = b; (i >= 0) && (i < to); )
        switch (args.t_.at (i).t_)
        {   case ct_square_brac :
                if (context.html_ver ().css_version () == css_1)
                    nits.pick (nit_css_version, es_error, ec_css, "[...] requires CSS 2.0 or better");
                else
                {   decore_.emplace_back (args, b);
                    i =  next_non_whitespace (args.t_, i, to); }
                break;
            case ct_dot :
            case ct_hash :
                {   int j = next_non_whitespace (args.t_, i, to);
                    if (j < 0) nits.pick (nit_css_syntax, es_error, ec_css, "missing class or ID");
                    else decore_.emplace_back (args, i, j);
                    i = next_non_whitespace (args.t_, j, to); }
                break;
            case ct_colon :
                {   int brac = token_find (args.t_, ct_round_brac, i, to);
                    if (brac < 0) brac = next_non_whitespace (args.t_, i, to);
                    else
                    {   brac = token_find (args.t_, ct_round_ket, i, to);
                        if (brac < 0) nits.pick (nit_css_syntax, es_error, ec_css, "missing close bracket"); }
                    if (brac > 0) decore_.emplace_back (args, i, brac);
                    i = next_non_whitespace (args.t_, brac, to); }
                break;
            case ct_plus :
            case ct_gt :
            case ct_squiggle :
                parse (args, i, to);
                return;
            default :
                nits.pick (nit_css_syntax, es_error, ec_css, quote (tkn_rpt (args.t_.at (i))), ": unexpected");
                return; } }

bool css_element::bef_aft () const
{   for (auto d : decore_)
        if (d.bef_aft ())
            return true;
    return false; }

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

void css_element::validate (arguments& args)
{   for (auto i : decore_)
        i.validate (args); }

void css_element::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : decore_)
        i.shadow (ss, args); }
