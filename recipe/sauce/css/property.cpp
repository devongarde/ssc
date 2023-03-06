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
#include "type/type.h"
#include "css/property.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/flags.h"

void property::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    if ((b < 0) || (args.t_.at (b).t_ == ct_curly_ket)) return;
    from_ = b;
    nitpick& nits = args.t_.at (b).nits_;
    if (args.t_.at (b).t_ == ct_dash)
    {   ::std::string pn ("-");
        const int k = next_non_whitespace (args.t_, b, to);
        if (k > 0) pn += assemble_string (args.t_, k, to);
        nits.pick (nit_bespoke_property, es_warning, ec_css, quote (pn), ": apologies, but " PROG " cannot verify bespoke properties."); }
    else if (args.t_.at (b).t_ != ct_keyword)
        nits.pick (nit_property, es_error, ec_css, quote (tkn_rpt (args.t_.at (b))), ": property name expected");
    else
    {   const int k = b;
        b = next_non_whitespace (args.t_, b, to);
        if ((b > 0) && (args.t_.at (b).t_ == ct_colon)) b = next_token_at (args.t_, b, to);
        else nits.pick (nit_css_syntax, es_error, ec_css, "missing colon after property name");
        b = first_non_whitespace (args.t_, b, to);
        if ((b < 0) || ((b > 0) && (args.t_.at (b).t_ == ct_curly_ket)))
            nits.pick (nit_property, es_error, ec_css, "missing property value");
        else
        {   val_.clear ();
            int pre = to; css_token p = ct_error;
            const int bang = token_find (args.t_, ct_bang, b, to, &pre);
            if (bang < 0) pre = to;
            bool xs = false, xk = false, xn = false, xi = false, fn = false, clean = true;
            const bool nff = (args.st_ == nullptr) || (args.st_ -> get () != css_font_face);
            int kc = 0;
            while (((to == -1) || (b <= pre)) && (b > 0) && (args.t_.at (b).t_ != ct_curly_ket))
            {   if ((p == ct_error) || (p <= ct_comment)) p = args.t_.at (b).t_;
                switch (args.t_.at (b).t_)
                {   case ct_keyword : xk = true; break;
                    case ct_identifier : xi = true; break;
                    case ct_number : xn = true; break;
                    case ct_string : xs = true; break;
                    case ct_round_brac : fn = true; break;
                    case ct_comma: clean = nff; break;
                    default : break; }                    
                if (clean) val_ += tkn_rpt (args.t_.at (b));
                b = next_token_at (args.t_, b, pre);
                ++kc; }
            prop_ = make_property_v_ptr (nits, args.t_.at (k).val_, val_, p);
            if (prop_.get () != nullptr)
            {   const e_css_property pr (prop_ -> get ());
                enum_n < t_css_property, e_css_property > pp;
                pp.set (pr);
                VERIFY_NOT_NULL (args.ps_, __FILE__, __LINE__);
                args.ps_ -> state () |= pr;
                flags_ = pp.flags ();
                args.check_flags (nits, flags_, pp.name ());
                if (! fn)
                {   if (xs && ((flags_ & CF_NOT_STRING) == CF_NOT_STRING))
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val_), ": should not be a string");
                    if (((flags_ & CF_EXPECT_FN) == CF_EXPECT_FN))
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val_), ": function expected"); }
                if (((flags_ & CF_EXPECT_FN) != CF_EXPECT_FN) || ! fn)
                {   if ((kc > 1) && ((flags_ & (CF_EXPECT_STRING | CF_EXPECT_NUMBER)) != 0))
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "a single value is sought");
                    if (xs) if ((flags_ & CF_EXPECT_KEYWORDS) == CF_EXPECT_KEYWORDS)
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val_), ": should be a keyword");
                    if (xk || xn || xi) if ((flags_ & CF_EXPECT_STRING) == CF_EXPECT_STRING)
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val_), ": should be a string");
                    if (! xn) if ((flags_ & CF_EXPECT_NUMBER) == CF_EXPECT_NUMBER)
                        nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val_), ": should be a number"); }
                static elem eca (elem_css_all);
                prop_ -> verify (nits, eca); }
            if (bang > 0)
            {   b = next_non_whitespace (args.t_, bang, to);
                if (b < 0)
                    nits.pick (nit_weight, ed_css_20, "5 Selectors", es_error, ec_css, "missing weight");
                else if (args.t_.at (b).t_ != ct_keyword)
                    nits.pick (nit_weight, ed_css_20, "5 Selectors", es_error, ec_css, "keyword expected after !");
                else w_ = weight (args.t_.at (b).nits_, args, args.t_.at (b).val_); } } } }
    
void property::accumulate (stats_t* s, const element_bitset& e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    if (prop_.get () != nullptr)
    {   s -> mark (prop_ -> get ());
        prop_ -> accumulate (s, e); }
    w_.accumulate (s); }

::std::string property::rpt () const
{   if (prop_.get () == nullptr) return ::std::string ();
    return prop_ -> rpt (); }  

void property::validate (arguments& args)
{   if ((from_ > 0) && ! val_.empty ())
    {   nitpick& nits = args.t_.at (from_).nits_;
        args.validate (nits, flags_, type_master < t_css_property >::name (static_cast < e_css_property > (prop_ -> get ())), val_); }
    w_.validate (args);
    if (prop_.get () != nullptr) prop_ -> validate (args); }

void property::shadow (::std::stringstream& ss, arguments& args)
{   if (prop_.get () != nullptr) prop_ -> shadow (ss, args, nullptr);
    w_.shadow (ss, args); }
