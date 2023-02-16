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

void css_fn::parse (arguments& args, const int from, const int to)
{   PRESUME (from <= to, __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
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
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ != ct_round_brac))
        {   if ((cats & H2_CSS_ARG_MASK) != 0)
                nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": missing arguments");   
            return; }
        if ((cats & H2_CSS_ARG_MASK) == 0)
        {   nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": takes no arguments");
            return; }
        b = next_non_whitespace (args.t_, b, to);
        params_.clear ();
        bool tock = false;
        while ((b > 0) && (b <= to) && (args.t_.at (b).t_ != ct_round_ket))
        {   if (args.t_.at (b).t_ == ct_comma)
            {   if (! tock) params_.emplace_back ("");
                tock = false; }
            else
            {   if (tock) nits.pick (nit_css_syntax, es_error, ec_css, fn.name (), ": missing comma between arguments");
                params_.emplace_back (tkn_rpt (args.t_.at (b)));
                tock = true; }
            b = args.t_.at (b).next_; }
        if (params_.size () > 0)
            switch (fn_)
            {   case efn_lang :
                    test_value < t_lang > (nits, context.html_ver (), params_.at (0));
                    if (params_.size () != 1) nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": too many arguments");
                    break;
                case efn_dir :
                    test_value < t_ltr_rtl > (nits, context.html_ver (), params_.at (0));
                    if (params_.size () != 1) nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": too many arguments");
                    break;
                case efn_current :
                case efn_has :
                case efn_is :
                case efn_not :
                case efn_where :
                    for (auto a : params_) ve_.emplace_back (new css_element (nits, args.v_, args.ns_, a));
                    break;
                case efn_nth_child :
                case efn_nth_col :
                case efn_nth_last_child :
                case efn_nth_last_col :
                case efn_nth_last_of_type :
                case efn_nth_of_type :
                    test_value < t_unsigned > (nits, context.html_ver (), params_.at (0));
                    if (params_.size () != 1) nits.pick (nit_pseud, es_error, ec_css, fn.name (), ": too many arguments");
                    break;
                default : break; } } }

void css_fn::accumulate (stats_t* ) const { }

::std::string css_fn::rpt () const
{   ::std::string res (":");
    res += type_master < t_css_fn > ::name (fn_);
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
