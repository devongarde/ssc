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
#include "css/group.h"

void property::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    if ((b < 0) || (args.t_.at (b).t_ == ct_curly_ket)) return;
    from_ = b;
    nitpick& nits = args.t_.at (b).nits_;
    if (args.t_.at (b).t_ != ct_keyword)
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
            css_token p = ct_error;
            bool xs = false, xk = false, xn = false, xi = false, fn = false, clean = true;
            int kc = 0, var = b, bang = -1;
            if (! args.prep_for_make (nits, from, b, to, var, bang, p, xs, xk, xn, xi, fn, clean, kc, val_)) return;
            prop_ = make_property_v_ptr (args, var, to, nits, k, val_, p);
            if (prop_.get () != nullptr)
            {   const e_css_property pr (prop_ -> get ());
                enum_n < t_css_property, e_css_property > pp;
                pp.set (pr);
                VERIFY_NOT_NULL (args.ps_, __FILE__, __LINE__);
                args.ps_ -> state () |= pr;
                if (pr == ec_custom)
                {   name_ = args.t_.at (k).val_;
                    auto cp = args.g_.custom_prop ().find (name_);
                    if (cp == args.g_.custom_prop ().cend ())
                    {   args.g_.custom_prop ().emplace (name_, 1);
                        nits.pick (nit_css_custom, es_info, ec_css, quote (name_), " noted"); }
                    else
                    {   cp -> second += 1;
                        nits.pick (nit_css_custom, es_comment, ec_css, quote (name_), " referenced again"); } }
                flags_ = pp.flags ();
                args.check_flags (nits, flags_, pp.name ());
                args.check_flags (nits, flags_, pp.name (), xk, xi, xn, xs, fn, kc, args.t_.at (k).val_, val_);
                if (pp.first ().css_ui () > args.v_.css_ui ())
                    nits.pick (nit_css_version, ed_css_ui_3, "3.1. Changing the Box Model: the box-sizing property", es_error, ec_css, quote (args.t_.at (k).val_), " requires CSS Basic User Interface level 3");
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
    w_.accumulate (s);
    if (! name_.empty ())
        s -> mark_custom_prop (name_); }

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

void property::name (arguments& , const ::std::string& n)
{   name_ = n; } 
