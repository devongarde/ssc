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

void statements::parse (arguments& args, const ::std::string& s)
{    vint_t lines;
    ::std::string twas;
    reset ();
    ::std::size_t count = 0;
    vstr_t ss (uq2 (s, UQ_C_CMT | UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_BRACE | UQ_TRIM | UQ_16 | UQ_UNIFY | UQ_SEP, "@;", &lines, &ticks_));
    if (args.sv_ && (args.v_ != html_default))
    {   nitpick gnats;
        gnats.set_context (0, "(*content)");
        gnats.pick (nit_html, es_info, ec_css, "Presuming CSS intended for use with ", args.v_.name ());
        ticks_.push_back (gnats); }
    bool at = false, expect_semi = false;
    for (auto sss : ss)
    {   PRESUME (count < lines.size (), __FILE__, __LINE__); 
        nitpick gnats;
        if (sss == ";")
            if (expect_semi)
                expect_semi = false;
            else
            {   if (twas.length () >= DEFAULT_LINE_LENGTH / 2)
                    twas += twas.substr (twas.length () - (DEFAULT_LINE_LENGTH / 2)) + " ...";
                gnats.set_context (lines.at (count), twas);
                gnats.pick (nit_css_syntax, es_comment, ec_css, "unexpected semicolon follows here");
                ticks_.push_back (gnats); }
        else
        {   if (expect_semi)
            {   gnats.set_context (lines.at (count), sss);
                gnats.pick (nit_css_syntax, es_error, ec_css, "missing semicolon here");
                ticks_.push_back (gnats); }
            expect_semi = false;
            twas = sss;
            if (sss == "@") at = true;
            else
            {   if (at)
                {   gnats.set_context (lines.at (count), sss);
                    statements_.push_back (statement (gnats, args, sss));
                    ticks_.push_back (gnats);
                    at = false;
                    expect_semi = true; }
                else
                {   v_np vgn;
                    rules r;
                    r.parse (vgn, args, sss, lines.at (count));
                    rules_.push_back (r);
                    for (auto gn : vgn) ticks_.push_back (gn); } } }
        ++count; } }

void statements::accumulate (nitpick& accumulator) const
{   for (auto n : ticks_)
        n.accumulate (accumulator);  }

void statements::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto r : rules_)
        r.accumulate (s);
    for (auto st : statements_)
        st.accumulate (s); } 

::std::string statements::rpt () const
{   ::std::string res;
    for (auto r : rules_)
        res += r.rpt () + "\n";
    return res; }  
