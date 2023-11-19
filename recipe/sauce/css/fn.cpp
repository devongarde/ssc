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
#include "css/arguments.h"
#include "css/decoration.h"
#include "css/css_element.h"
#include "css/selector.h"
#include "css/group.h"
#include "webpage/page.h"

void css_fn::parse (arguments& args, const int from, const int to, const bool coco, const bool knotted)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    nitpick& nits = args.t_.at (from).nits_;
    if (args.t_.at (b).t_ != ct_keyword)
        nits.pick (nit_pseud, es_error, ec_css, "pseudo name expected");
    else
    {   enum_n < t_css_fn, e_css_fn > fn;
        fn.set_value (nits, context.html_ver (), args.t_.at (b).val_);
        args.check_flags (nits, fn.flags (), fn.name ());
        fn_ = fn.get ();
        const flags_t cats (fn.first ().ext2 ());
        if (args.v_.css_selector () >= 3)
        {   if ((cats & H2_CSS_COCO) == H2_CSS_COCO)
            {   if (! coco)
                    nits.pick (nit_pseud, ed_css_selectors_3, "2 Selectors", es_warning, ec_css, fn.name (), " is a pseudo element, use '::', not ':'"); }  
            else
            {   if (coco)
                    nits.pick (nit_pseud, ed_css_selectors_3, "2 Selectors", es_error, ec_css, fn.name (), " is a pseudo class, use ':', not '::'"); } }
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ != ct_round_brac))
        {   if (((cats & H2_CSS_ARG_MASK) != 0) && (fn_ != efn_host))
                nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": missing arguments");   
            return; }
        if ((cats & H2_CSS_ARG_MASK) == 0)
        {   nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": takes no arguments");
            return; }
        b = next_non_whitespace (args.t_, b, to);
        const int ket = token_find (args.t_, ct_round_ket, b, to);
        if (ket < 0)
        {   nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": where's the ket?");
            return; }
        ::std::string param (assemble_string (args.t_, b, ket));
        params_.clear ();
        params_.push_back (param);
        switch (fn_)
        {   case efn_attr :
                if (context.css_nes () < 3)
                    nits.pick (nit_css_version, es_error, ec_css, quote (fn.name ()), " requires CSS Non-Element Selectors");
                else
                {   const ::std::string::size_type bar = param.find ('|');
                    ::std::string ns, at (param);
                    if (bar != ::std::string::npos)
                    {   if ((bar == 0) || (bar == at.length () - 1))
                        {   nits.pick (nit_pseud, es_error, ec_css, quote (param), ": bad namespace");
                            return; }
                        ns = at.substr (0, bar - 1);
                        at = at.substr (bar+1); }
                    const attr a (nits, args.v_, args.ns_, at, ns);
                    if (a.get () == a_unknown)
                        nits.pick (nit_attribute_unrecognised, es_error, ec_css, quote (param), ": unknown attribute"); }
                return;
            case efn_auto :
                test_value < t_lang > (nits, context.html_ver (), param);
                return;
            case efn_highlight :
                if (context.css_highlight () < 3)
                    nits.pick (nit_css_version, es_error, ec_css, quote (fn.name ()), " requires CSS Custom Highlight");
//                else
//                {   sstr_t& h = args.g_.highlight ();
//                    if (h.find (param) != h.cend ())
//                        nits.pick (nit_highlight, es_error, ec_css, quote (param), ": previously defined");
//                    else h.insert (param); }
                else if (args.has_str (gst_highlight, param) || ! args.dst_ -> note_str (gst_highlight, param))
                    nits.pick (nit_highlight, es_error, ec_css, quote (param), ": previously defined");
                return;
            case efn_host :
            case efn_host_context :
                if (context.css_view () > 0)
                    vsl_.emplace_back (new selector (args, b, ket, true));
                break;
            case efn_lang :
                if (args.v_.css_selector () >= 4)
                    test_value < t_css_langs > (nits, context.html_ver (), param);
                else test_value < t_lang > (nits, context.html_ver (), param);
                return;
            case efn_dir :
                test_value < t_ltr_rtl > (nits, context.html_ver (), param);
                return;
            case efn_nth_child :
            case efn_nth_col :
            case efn_nth_last_child :
            case efn_nth_last_col :
            case efn_nth_last_of_type :
            case efn_nth_of_type :
                {   if (args.v_.css_selector () >= 4)
                    {   int prev = -1;
                        int of = ident_find (args.t_, "of", b, to, &prev);
                        if (of != -1)
                        {   of = next_non_whitespace (args.t_, of, to);
                            vsl_.emplace_back (new selector (args, of, ket, true));
                            param = assemble_string (args.t_, b, prev); } }
                    test_value < t_css_nth_oe > (nits, context.html_ver (), param); }
                return;
            case efn_nth_fragment :
                if (context.css_overflow () < 4)
                    nits.pick (nit_css_version, es_error, ec_css, quote (fn.name ()), " requires CSS Text Overflow 4");
                test_value < t_positive > (nits, context.html_ver (), param);
                break;
            case efn_not :
                if (knotted)
                {   nits.pick (nit_not_not, ed_css_selectors_3, "6.6.7. The negation pseudo-class", es_error, ec_css, ":not(:not) is not nice");
                    return; }
                break;
            case efn_part :
                if (context.css_shadow () < 3)
                    nits.pick (nit_css_version, es_error, ec_css, quote (fn.name ()), " requires CSS Shadow Parts");
                else
                {   vstr_t parts = split_by_space (param);
                    for (auto part : parts)
                        args.g_.get_page ().parts ().insert (part); }
                return;
            case efn_view_transition_group :
            case efn_view_transition_new :
            case efn_view_transition_old :
            case efn_view_transition_image_pair :
                if (context.css_view () < 3)
                    nits.pick (nit_css_version, es_error, ec_css, quote (fn.name ()), " requires CSS View Transitions");
                else if (param != "*")
//                {   sstr_t& h = args.g_.view ();
//                    if (h.find (param) == h.cend ()) h.insert (param); }
                    if (! args.has_str (gst_view, param))
                        args.dst_ -> note_str (gst_view, param); 
                return;
            case efn_current :
            case efn_has :
            case efn_is :
            case efn_where :
                break;
            default : return; }
        params_.clear ();
        ::std::vector < int > f;
        int start = b;
        bool pf = false;
        while ((b > 0) && ((to < 0) || (b <= to)) && (args.t_.at (b).t_ != ct_round_ket))
        {   switch (args.t_.at (b).t_)
            {   case ct_comma:
                    {   PRESUME (start > 0, __FILE__, __LINE__);
                        const ::std::string p (assemble_string (args.t_, start, b));
                        params_.emplace_back (p);
                        if (pf) f.emplace_back (start);
                        else f.emplace_back (-1);
                        start = -1; }
                    break;
                case ct_colon :
                    pf = true;
                    break;
                default :
                    break; }
            b = args.t_.at (b).next_;
            if (start == -1) start = b; }
        if (params_.size () > 0)
            switch (fn_)
            {   case efn_not :
                    if ((params_.size () != 1) && (args.v_.css_selector () < 4))
                        nits.pick (nit_not_not, ed_css_selectors_3, "6.6.7. The negation pseudo-class", es_error, ec_css, ":not with multiple arguments requires CSS Selector 4");
                    FALLTHROUGH;
                case efn_current :
                case efn_has :
                case efn_is :
                case efn_where :
                    PRESUME (f.size () == params_.size (), __FILE__, __LINE__);
                    for (::std::size_t n = 0; n < params_.size (); ++n)
                        if (f.at (n) > 0) vsl_.emplace_back (new selector (args, f.at (n), ket, true)); 
                        else ve_.emplace_back (new css_element (nits, args.v_, args.ns_, params_.at (n)));
                    break;
                default :
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    break; } } }

void css_fn::accumulate (stats_t* ) const { }

::std::string css_fn::rpt () const
{   ::std::string res (":");
    res += type_master < t_css_fn > :: name (fn_);
    if (params_.size () > 0)
    {   res += "(";
        bool extra = false;
        for (auto a : params_)
        {   if (extra) res += ",";
            else extra = true;
            res += a; }
        res += ")"; }
    return res; }

void css_fn::validate (arguments& args)
{   for (auto e : ve_)
        e -> validate (args); }

void css_fn::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
