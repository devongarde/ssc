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

void css_fn::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    const ::std::string::size_type pos = s.find ('(');
    enum_n < t_css_fn, e_css_fn > fn;
    if (pos == ::std::string::npos) fn.set_value (nits, args.v_, s);
    else
    {   ::std::string ss (s.substr (0, pos));
        if (ss.empty ())
            nits.pick (nit_css_syntax, es_error, ec_css, quote (ss), ": missing pseudo name");
        else fn.set_value (nits, args.v_, trim_the_lot_off (ss)); }
    fn_ = fn.get ();
    const flags_t flags (fn.flags ());
    if (pos == ::std::string::npos)
    {   if ((flags & H2_CSS_ARG_MASK) != 0)
            nits.pick (nit_css_syntax, es_error, ec_css, fn.name (), ": missing arguments"); }
    else
    {   if (s.at (s.length () - 1) != ')')
            nits.pick (nit_css_syntax, es_error, ec_css, "imbalanced or incorrect argument brackets");
        else if ((flags & H2_CSS_ARG_MASK) == 0)
            nits.pick (nit_css_syntax, es_error, ec_css, fn.name (), ": takes no arguments");
        else
        {   params_ = uq2_sep (s.substr (pos+1, s.length () - pos - 2),
                            UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_10 | UQ_TRIM, ",");
            if ((flags & H2_CSS_MORE_ARGS) != H2_CSS_MORE_ARGS)
                if ((params_.size () != 1) && ((flags & H2_CSS_1_ARG) == H2_CSS_1_ARG))
                    nits.pick (nit_css_syntax, es_error, ec_css, fn.name (), ": takes a single argument");
                else if ((flags & H2_CSS_2_ARGS) == H2_CSS_2_ARGS)
                    if ((params_.size () < 1) || (params_.size () > 2))
                        nits.pick (nit_css_syntax, es_error, ec_css, fn.name (), ": takes one or two arguments"); } }
    switch (fn_)
    {   case efn_lang :
            test_value < t_lang > (nits, args.v_, params_.at (0));
            break;
        case efn_dir :
            test_value < t_ltr_rtl > (nits, args.v_, params_.at (0));
            break;
        case efn_current :
        case efn_has :
        case efn_is :
        case efn_not :
        case efn_where :
            {   for (auto a : params_)
                {   css_element e;
                    e.parse (nits, args, a);
                    ve_.emplace_back (new css_element (e)); } }
            break;
        case efn_nth_child :
        case efn_nth_col :
        case efn_nth_last_child :
        case efn_nth_last_col :
        case efn_nth_last_of_type :
        case efn_nth_of_type :
            test_value < t_unsigned > (nits, args.v_, params_.at (0));
            break;
        default : break; } }

void css_fn::accumulate (stats_t* ) const
{   }

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
