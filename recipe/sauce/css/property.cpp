/*
ssc (static site checker)
File Info
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
    if (b < 0) return;
    while ((token_category (args.t_.at (b).t_) & TC_ROUND) != 0)
        b = next_non_whitespace (args.t_, b, to);
    from_ = b;
    nitpick& nits = args.t_.at (b).nits_;
    const int brac = token_find (args.t_, ct_curly_brac, b);
    if (brac == b)
    {   nits.pick (nit_nesting, ed_css_nesting, "2.1. Syntax", es_error, ec_css, "unexpected {");
        return; }
    int mx = -1, n = 1;
    if (brac > 0) mx = brac-1;
    else if (to > 0) mx = to;
    else mx = GSL_NARROW_CAST < int > (args.t_.size ()) - 1;
    PRESUME (mx > 0, __FILE__, __LINE__);
    PRESUME (mx >= from_, __FILE__, __LINE__);
    vint_t vfr, vto;
    vfr.push_back (from_);
    vto.push_back (mx);
    bool nesting3 = false;
    switch (args.t_.at (b).t_)
    {   case ct_ampersand :
        case ct_dot :
        case ct_bar :
        case ct_barbar :
        case ct_colon :
        case ct_dollar :
        case ct_eq :
        case ct_gt :
        case ct_hat :
        case ct_plus :
        case ct_squiggle :
        case ct_at :
            if (context.css_nesting () < 3)
            {   nits.pick (nit_nesting, ed_css_nesting, "2.1. Syntax", es_error, ec_css,
                    "property name expected (", quote (tkn_rpt (args.t_.at (b))), " here requires CSS Nesting)");
                return; }
            if (brac < 0)
            {   nits.pick (nit_nesting, ed_css_nesting, "2.1. Syntax", es_error, ec_css, "missing { ... } after ", tkn_rpt (args.t_.at (b)));
                return; }
            n = pos_de (args.t_, ct_comma, b, mx, vfr, vto);
            nesting3 = true;
            break;
        case ct_curly_brac :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            return;
        case ct_curly_ket :
            return;
        default :
            break; }
    for (int x = 0; x < n; ++x)
        switch (args.t_.at (vfr.at (x)).t_)
        {   case ct_ampersand :
            case ct_dot :
                {   b = next_non_whitespace (args.t_, vfr.at (x), to);
                    if (b < 0)
                    {   nitpick& nuts = args.t_.at (vfr.at (x)).nits_;
                        nuts.pick (nit_nesting, ed_css_nesting, "2.1. Syntax", es_error, ec_css, "missing selector after ", quote (tkn_rpt (args.t_.at (b))));
                        return; }
                    if (duff_ == nullptr) duff_ = ps_t (new statement ());
                    fiddlesticks < statement > f (&args.st_, duff_.get ());
                    fiddlesticks < bool > nb (&args.nested_, true);
                    if (vto.at (x) - 1 >= b)
                        sel_ = psel_t (new selector (args, b, vto.at (x))); }
                break;
            case ct_bar :
            case ct_barbar :
            case ct_colon :
            case ct_dollar :
            case ct_eq :
            case ct_gt :
            case ct_hat :
            case ct_plus :
            case ct_squiggle :
                {   if (duff_ == nullptr) duff_ = ps_t (new statement ());
                    fiddlesticks < statement > f (&args.st_, duff_.get ());
                    fiddlesticks < bool > nb (&args.nested_, true);
                    if (brac - 1 >= vfr.at (x))
                        sel_ = psel_t (new selector (args, vfr.at (x), vto.at (x))); }
                break;
            case ct_at :
                {   nitpick& nuts = args.t_.at (vfr.at (x)).nits_;
                    const int kw = next_non_whitespace (args.t_, vfr.at (x), vto.at (x));
                    if (kw < 0)
                    {   nuts.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "missing keyword after '@'");
                        return; }
                    if ((args.t_.at (kw).t_ != ct_keyword) || (args.t_.at (kw).t_ != ct_identifier))
                    {   nuts.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), "??");
                        return; }
                    enum_n < t_css_statement, e_css_statement > cst;
                    cst.set_value (nuts, args.v_, args.t_.at (kw).val_);
                    const e_css_statement st = cst.get ();
                    switch (st)
                    {   case css_media :
                        case css_supports :
                        case css_scope :
                        case css_layer :
                        case css_container :
                            break;
                        case css_context :
                        case css_error :
                            nuts.pick (nit_nesting, es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " is unrecognised");
                            return;
                        default :
                            nuts.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " cannot be nested");
                            return; }
                    if (! cst.first ().is_css_compatible (context.html_ver ()))
                    {   nuts.pick (nit_nesting, es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " is not available in ", context.html_ver ().long_css_version_name ());
                        return; }
                    if (duff_ == nullptr) duff_ = ps_t (new statement ());
                    fiddlesticks < statement > f (&args.st_, duff_.get ());
                    fiddlesticks < bool > nb (&args.nested_, true);
                    st_.emplace_back (pst_t (new statements (args, vfr.at (x), vto.at (x)))); }
                break;
            case ct_comment :
            case ct_keyword :
            case ct_identifier :
            case ct_whitespace :
                break;
            case ct_eof :
                return;
            default :
                nits.pick (nit_property, es_error, ec_css, quote (tkn_rpt (args.t_.at (vfr.at (x)))), ": property name expected");
                return; }
    if (nesting3)
    {   if (brac >= 0)
        {   fiddlesticks < bool > nb (&args.nested_, true);
            if (pp_.get () == nullptr) pp_ = pp_t (new properties (args, args.t_.at (brac).child_));
            else pp_ -> parse (args, args.t_.at (brac).child_); }
        return; }
    nitpick nuts;
    enum_n < t_css_property, e_css_property > ppp;
    ppp.set_value (nuts, args.v_, args.t_.at (b).val_);
    if (ppp.good ())
        if ((ppp.flags () & CF_MEDIA_LOGIC) == CF_MEDIA_LOGIC)
            return;
    const int k = b;
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
                if (args.has_custom_prop (name_))
                    nits.pick (nit_css_custom, es_comment, ec_css, quote (name_), " noted");
                else
                {   args.note_custom_prop (name_);
                    nits.pick (nit_css_custom, es_comment, ec_css, quote (name_), " referenced again"); } }
            flags_ = pp.flags ();
            args.check_flags (nits, flags_, pp.name ());
            args.check_flags (nits, flags_, pp.name (), xk, xi, xn, xs, fn, kc, args.t_.at (k).val_, val_);
            if (pp.first ().css_ui () > args.v_.css_ui ())
                nits.pick (nit_css_version, ed_css_ui_3, "3.1. Changing the Box Model: the box-sizing property", es_error, ec_css, quote (args.t_.at (k).val_), " requires CSS Basic User Interface level 3");
            static elem eca (elem_css_all);
            prop_ -> verify (nits, eca);
            prop_ -> invalid_id (args, nits); }
        if (bang > 0)
        {   b = next_non_whitespace (args.t_, bang, to);
            if (b < 0)
                nits.pick (nit_weight, ed_css_20, "5 Selectors", es_error, ec_css, "missing weight");
            else if (args.t_.at (b).t_ != ct_keyword)
                nits.pick (nit_weight, ed_css_20, "5 Selectors", es_error, ec_css, "keyword expected after !");
            else w_ = weight (args.t_.at (b).nits_, args, args.t_.at (b).val_); } } }

void property::accumulate (stats_t* s, const element_bitset& e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    if (prop_.get () != nullptr)
    {   s -> mark (prop_ -> get ());
        prop_ -> accumulate (s, e); }
    w_.accumulate (s);
    if (! name_.empty ())
        s -> use_custom_prop (name_); }

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
