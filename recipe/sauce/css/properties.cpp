/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "type/type.h"
#include "css/arguments.h"
#include "css/properties.h"
#include "utility/quote.h"
#include "css/statements.h"
#include "css/property.h"

void properties::parse (arguments& args, const int from, const int to)
{   PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < len) || (to < 0), __FILE__, __LINE__);
    int b = -1, prev = -1, atat = -1;
    bool burnt = false;
    fiddlesticks < properties > f (&args.ps_, this);
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (b == -1) b = i;
        if (atat >= 0)
            switch (args.t_.at (i).t_)
            {   case ct_at :
                    if (! burnt)
                    {   nitpick& nits = args.t_.at (b).nits_;
                        nits.pick (nit_css_syntax, es_error, ec_css, "two @s for the price of one?!");
                        burnt = true; }
                    else
                    {   nitpick& nits = args.t_.at (i).nits_;
                        nits.pick (nit_css_syntax, es_error, ec_css, "unexpected second @..."); }
                    break; 
                case ct_curly_brac :
                {   PRESUME (args.t_.at (i).child_ > 0, __FILE__, __LINE__);
                    if (args.t_.at (i).child_ > 0)
                        if (st_.get () == nullptr) st_ = pst_t (new statements (args, args.t_.at (i).child_, -1));
                        else st_ -> parse (args, args.t_.at (i).child_, -1);
                    atat = b = -1; }
                    break;
                case ct_colon :
                case ct_comment :
                case ct_dash :
                case ct_identifier :
                case ct_keyword :
                case ct_whitespace :
                    break;
                default :
                    if (! burnt)
                    {   nitpick& nits = args.t_.at (atat).nits_;
                        nits.pick (nit_css_syntax, es_comment, ec_css, quote (tkn_rpt (args.t_.at (i))), ": unexpected; expecting { ... }");
                        burnt = true; }
                    break; }
        else switch (args.t_.at (i).t_)
        {   case ct_at :
                if (context.css_module (c_paged_media) >= 3) atat = i;
                break;
            case ct_semicolon :
                if (b != i) prop_.emplace_back (new property (args, b, prev));
                b = -1;
                break;
            case ct_ampersand :
                if (b != i) prop_.emplace_back (new property (args, b, prev));
                b = -1;
                atat = i;
                break;
            default :
                break; }
        prev = i; }
    if (b != -1)
        if (atat < 0) prop_.emplace_back (new property (args, b, to));
        else if (! burnt) args.st_ -> parse (args, atat, (to > 0) ? to : prev); }

void properties::accumulate (stats_t* s, const element_bitset& e) const
{   for (auto p : prop_)
        p -> accumulate (s, e); }

::std::string properties::rpt () const
{   ::std::string res ("{ ");
    for (auto s : prop_)
    {   if (! res.empty ()) res += "; ";
        res += s -> rpt (); }
    res += " }";
    return res; }
  
void properties::validate (arguments& args)
{   fiddlesticks < properties > f (&args.ps_, this);
    for (auto i : prop_)
        i -> validate (args); }

void properties::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
