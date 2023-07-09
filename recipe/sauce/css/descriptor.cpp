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
#include "css/descriptor.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/flags.h"
#include "css/group.h"

void descriptor::parse (arguments& args, const e_css_statement cs, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    VERIFY_NOT_NULL (args.st_, __FILE__, __LINE__);
    PRESUME (args.cs () != css_error, __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    if ((b < 0) || (args.t_.at (b).t_ == ct_curly_ket)) return;
    from_ = b;
    nitpick& nits = args.t_.at (b).nits_;
    if (args.t_.at (b).t_ != ct_keyword)
        nits.pick (nit_descriptor, es_error, ec_css, quote (tkn_rpt (args.t_.at (b))), ": descriptor name expected");
    else
    {   const int k = b;
        b = next_non_whitespace (args.t_, b, to);
        if ((b > 0) && (args.t_.at (b).t_ == ct_colon)) b = next_token_at (args.t_, b, to);
        else nits.pick (nit_css_syntax, es_error, ec_css, "missing colon after descriptor name");
        b = first_non_whitespace (args.t_, b, to);
        if ((b < 0) || ((b > 0) && (args.t_.at (b).t_ == ct_curly_ket)))
            nits.pick (nit_descriptor, es_error, ec_css, "missing descriptor value");
        else
        {   val_.clear ();
            css_token p = ct_error;
            bool xs = false, xk = false, xn = false, xi = false, fn = false, clean = true;
            int kc = 0, var = b, bang = -1;
            if (! args.prep_for_make (nits, from, b, to, var, bang, p, xs, xk, xn, xi, fn, clean, kc, val_)) return;
            if (bang > 0) nits.pick (nit_weight, es_warning, ec_css, "weights cannot be applied to descriptors.");
            switch (args.cs ())
            {   case css_counter_style :
                    dsc_ = make_counter_style_v_ptr (args, var, to, nits, k, val_, p);
                    break;
                case css_font_face :
                    dsc_ = make_descriptor_v_ptr (args, var, to, nits, k, val_, p);
                    break;
                case css_font_feature_values :
                    dsc_ = make_feature_v_ptr (args, var, to, nits, k, val_, p);
                    break;
                case css_font_palette_values :
                    dsc_ = make_palette_v_ptr (args, var, to, nits, k, val_, p);
                    break;
                default :
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    break; }
            if (dsc_.get () != nullptr)
            {   const e_css_property pr (dsc_ -> get ());
                enum_n < t_css_property, e_css_property > pp;
                pp.set (pr);
                flags_ = pp.flags ();
                args.check_flags (nits, flags_, pp.name ());
                args.check_flags (nits, flags_, pp.name (), xk, xi, xn, xs, fn, clean, kc, args.t_.at (k).val_, val_);
                if (pp.first ().css_ui () > args.v_.css_ui ())
                    nits.pick (nit_css_version, ed_css_ui_3, "3.1. Changing the Box Model: the box-sizing property", es_error, ec_css, quote (args.t_.at (k).val_), " requires CSS Basic User Interface level 3");
                static elem eca (elem_css_all);
                dsc_ -> verify (nits, eca); } } } }
    
void descriptor::accumulate (stats_t* s, const element_bitset& e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    if (dsc_.get () != nullptr)
    {   s -> mark (dsc_ -> get ());
        dsc_ -> accumulate (s, e); } }

::std::string descriptor::rpt () const
{   if (dsc_.get () == nullptr) return ::std::string ();
    return dsc_ -> rpt (); }  

void descriptor::validate (arguments& args)
{   if ((from_ > 0) && ! val_.empty ())
    {   nitpick& nits = args.t_.at (from_).nits_;
        args.validate (nits, flags_, type_master < t_css_property >::name (static_cast < e_css_property > (dsc_ -> get ())), val_); }
    if (dsc_.get () != nullptr) dsc_ -> validate (args); }

void descriptor::shadow (::std::stringstream& ss, arguments& args)
{   if (dsc_.get () != nullptr) dsc_ -> shadow (ss, args, nullptr); }
