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
#include "css/selectors.h"
#include "css/arguments.h"
#include "utility/quote.h"

void selectors::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = -1; int prev = -1; int bracstac = 0, ns = -1, wotsit = -1, ident = -1, slashstart = -1;
    for (int i = from; i > 0; i = next_token_at (args.t_, i, to))
    {   if (b == -1) b = i;
        switch (args.t_.at (i).t_)
        {   case ct_round_brac :
                if (slashstart >= 0)
                {   args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "Unclosed reference combinator (e.g. '/ref/')");
                    slashstart = -1; }
                ++bracstac; break;
            case ct_round_ket :
               if (bracstac > 0) --bracstac; break;
            case ct_identifier :
            case ct_keyword :
            case ct_string :
                if (slashstart > 0) ident = i;
                break;
            case ct_bar :
                if (slashstart > 0)
                {   if (i > from)
                        if (ident > slashstart) ns = ident;
                    ident = -1; }
                break;
            case ct_slash :
                if (bracstac == 0)
                    if (args.v_.css_module (c_selector) > 4)
                        if (slashstart < 0)
                        {   if ((b < i) && (b >= 0))
                            {   sel_.emplace_back (args, b, prev);
                                b = -1; }
                            slashstart = i; }
                        else
                        {   if (b > 0)
                            {   const ::std::string s (trim_the_lot_off (assemble_string (args.t_, b, i-1)));
                                if (! s.empty ())
                                    args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, quote (s), ": unexpected content before reference combinator ('/ref/')"); }
                            if (ident > slashstart) wotsit = ident;
                            slashstart = ident = -1;
                            ident_t id = 0;
                            if (ns >= 0)
                                if (args.ns_.get () == nullptr)
                                    args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "no namespaces, thus unknown namespace ", quote (args.t_.at (ns).val_), " in reference combinator");
                                else
                                {   id = args.ns_ -> find_shortform (args.v_, namespace_names, args.t_.at (ns).val_);
                                    if (id == 0)
                                    {   args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "unknown namespace ", quote (args.t_.at (ns).val_), " in reference combinator"); 
                                        ns = -1; } }
                            if (wotsit < 0)
                                args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "no reference in reference combinator ('/ref/')");
                            else if (! attr::find (args.v_, args.t_.at (wotsit).val_, id))
                                if (! elem::find (args.v_, args.t_.at (wotsit).val_, id))
                                    args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "unrecognised reference combinator (", quote (args.t_.at (wotsit).val_), ")");
                            wotsit = ns = b = -1; }
                break;
            case ct_comma :
                if (bracstac == 0)
                {   if (slashstart > 0)
                    {   args.t_.at (i).nits_.pick (nit_refcomb, es_error, ec_css, "unclosed reference combinator ('/ref/')");
                        slashstart = -1; }
                    if (b != i) sel_.emplace_back (args, b, prev);
                    b = -1; }
                break;
            default : break; }
        prev = i; }
    if (slashstart > 0)
    {   args.t_.at (prev).nits_.pick (nit_refcomb, es_error, ec_css, "unfinished reference combinator ('/ref/')");
        slashstart = -1; }
    if (b != -1)
        sel_.emplace_back (args, b, to);
    if (! sel_.empty ())
    {   nitpick& nits = args.t_.at (from).nits_;
        len = GSL_NARROW_CAST < int > (sel_.size ());
        const element_bitset eb (sel_.at (stm (len)).get_elements ());
        if ((eb & ~pure_faux_bitset) != empty_element_bitset)
        {   const ::std::string r (sel_.at (stm (len)).rpt ());
            if (! r.empty () && (len > 1))
                for (int n = 0; n < len - 2; ++n)
                    if (sel_.at (n).rpt () == r)
                        nits.pick (nit_selector, es_warning, ec_css, quote (r), " is repeated"); } } }

bool selectors::bef_aft () const
{   for (auto se : sel_)
        if (se.bef_aft ()) return true;
    return false; }

void selectors::accumulate (stats_t* s) const
{   for (auto se : sel_)
        se.accumulate (s); }

::std::string selectors::rpt () const
{   ::std::string res;
    for (auto s : sel_)
    {   if (! res.empty ()) res += ",";
        res += s.rpt (); }
    return res; }  

void selectors::validate (arguments& args)
{   for (auto i : sel_)
        i.validate (args); }

void selectors::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : sel_)
        i.shadow (ss, args); }
