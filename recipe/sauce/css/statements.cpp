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
#include "css/statements.h"
#include "utility/quote.h"

void statements::parse (arguments& args, const int start, const int finish)
{   PRESUME (args.t_.at (0).t_ == ct_root, __FILE__, __LINE__);
    int from = -1, at = -1;
    const int last = (finish >= 0) ? finish : GSL_NARROW_CAST < int > (args.t_.size ());
    int prev = -1;

    for (int i = start; (i > 0) && (i < last); prev = i, i = next_token_at (args.t_, i, last))
        switch (args.t_.at (i).t_)
        {   case ct_at :
                if (from > 0)
                {   args.t_.at (i).nits_.pick (nit_css_syntax, es_error, ec_css, "unexpected ", tkn_rpt (args.t_.at (i)), " (5)");
                    rules_.emplace_back (args, from, prev);
                    from = -1; }
                at = i;
                break;
            case ct_semicolon :
                if (at > 0)
                {   statements_.emplace_back (args, at, prev);
                    at = -1; }
                else if (from > 0)
                {   if (args.styled ()) props_.parse (args, from, prev);
                    else
                    {   args.t_.at (i).nits_.pick (nit_css_syntax, es_error, ec_css, "unexpected ", tkn_rpt (args.t_.at (i)), " (6)");
                        rules_.emplace_back (args, from, prev); }
                    from = -1; }
                break;
            case ct_curly_brac :
            case ct_curly_ket :
                if (at > 0)
                {   statements_.emplace_back (args, at, i);
                    at = -1; }
                else if (from > 0)
                {   if (args.styled ()) props_.parse (args, from, prev);
                    else rules_.emplace_back (args, from, i);
                    from = -1; }
                break;
            case ct_whitespace :
            case ct_comment :
                break;
            default :
                if ((at < 0) && (from < 0)) from = i;
                break; }
    if (at > 0)
        if (args.styled ()) props_.parse (args, from, prev);
        else
        {   args.t_.at (stm (last)).nits_.pick (nit_css_unfinished, es_error, ec_css, "incomplete");
            rules_.emplace_back (args, from, last - 1); }
    else if ((from > 0) && (args.t_.at (from).t_ != ct_eof))
        if (args.styled ()) props_.parse (args, from, prev);
        else
        {   args.t_.at (stm (last)).nits_.pick (nit_css_unfinished, es_error, ec_css, "incomplete");
            rules_.emplace_back (args, from, last - 1); } }

void statements::accumulate (stats_t* s) const
{   props_.accumulate (s, get_elements ());
    for (auto r : rules_)
        r.accumulate (s);
    for (auto st : statements_)
        st.accumulate (s); } 

::std::string statements::rpt () const
{   ::std::string res;
    for (auto i : statements_)
        res += i.rpt () + "\n";
    for (auto r : rules_)
        res += r.rpt () + "\n";
    res += props_.rpt () + "\n";
    return res; }  

void statements::validate (arguments& args)
{   for (auto i : statements_)
        i.validate (args);
    for (auto i : rules_)
        i.validate (args);
    props_.validate (args); }

void statements::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : statements_)
        i.shadow (ss, args);
    for (auto i : rules_)
        i.shadow (ss, args);
    props_.shadow (ss, args); }
