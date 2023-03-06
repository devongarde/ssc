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
#include "main/context.h"
#include "css/css_attribute.h"
#include "css/arguments.h"

void css_attribute::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    if ((b == -1) || (args.t_.at (b).t_ != ct_keyword))
        args.t_.at (from).nits_.pick (nit_css_attribute, es_error, ec_css, "missing attribute name");
    else
    {   nitpick& nits = args.t_.at (b).nits_;
        const int at = b;
        css_attribute a (nits, args.v_, args.ns_, args.t_.at (at).val_);
        ::std::swap (*this, a);
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket)) return;
        switch (args.t_.at (b).t_)
        {   case ct_eq :
                b = next_non_whitespace (args.t_, b, to);
                break;
            case ct_bar :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following |");
                else next_non_whitespace (args.t_, b, to);
                eat_ = eat_lang;
                break; 
            case ct_hat :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following ^");
                else next_non_whitespace (args.t_, b+1, to);
                if (context.html_ver ().css_version () < css_3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "^= requires CSS 3 or later");
                else eat_ = eat_begins;
                break; 
            case ct_dollar :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following $");
                else next_non_whitespace (args.t_, b+1, to);
                if (context.html_ver ().css_version () < css_3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "$= requires CSS 3 or later");
                else eat_ = eat_ends;
                break; 
            case ct_splat :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following *");
                else next_non_whitespace (args.t_, b+1, to);
                eat_ = eat_contains;
                break; 
            case ct_squiggle :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following ~");
                else next_non_whitespace (args.t_, b, to);
                eat_ = eat_in_list;
                break; 
            default :
                nits.pick (nit_css_syntax, es_error, ec_css, tkn_rpt (args.t_.at (b)), ": unexpected");
                return; }
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket))
        {   nits.pick (nit_css_syntax, es_error, ec_css, args.t_.at (b).val_, ": missing value (for an empty string, use \"\")");
            return; }
        switch (args.t_.at (b).t_)
        {   case ct_string :
                break;
            case ct_identifier :
            case ct_keyword :
                if (context.html_ver ().css_version () >= css_3)
                    nits.pick (nit_enquote_value, ed_css_selectors_3, "2 Selectors", es_warning, ec_css, "attribute values should be quoted");
                break;
            default :
                nits.pick (nit_css_attribute, es_error, ec_css, args.t_.at (b).val_, ": an attribute value should be a quoted string");
                return; }
        // TODO validate attribute value
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket)) return;
        if (args.t_.at (b).t_ != ct_keyword)
        {   nits.pick (nit_css_syntax, es_error, ec_css, tkn_rpt (args.t_.at (b)), ": unexpected");
            return; }
        if ((context.html_ver ().css_version () < css_4) || (context.html_ver () < html_css_selectors_4))
        {   nits.pick (nit_css_version, ed_css_selectors_4, "2 Selectors Overview", es_error, ec_css, "case sensitivity selectors require CSS Selectors Level 4");
            return; }
        bool ok = false;
        if (args.t_.at (b).val_.size () == 1)
            switch (args.t_.at (b).val_.at (0))
            {   case 'i' :
                case 'I' :
                    eat_ = eat_uncased;
                    ok = true;
                    break;
                case 's' :
                case 'S' :
                    eat_ = eat_identical;
                    ok = true;
                    break;
                default :
                    break; }
        if (! ok) nits.pick (nit_css_attribute, es_error, ec_css, quote (args.t_.at (b).val_), ": invalid case sensitivity selector (expecting 'i' or 's')");
        b = next_non_whitespace (args.t_, b, to);
        if ((b != -1) && (args.t_.at (b).t_ != ct_square_ket)) return;
            nits.pick (nit_css_syntax, es_error, ec_css, "unexpected junk at end of attribute description"); } }

void css_attribute::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (e, a_.get ()); }

::std::string css_attribute::rpt () const
{   ::std::string res ("[");
    res += attr::name (a_);
    if (has_value_)
        switch (eat_)
        {   case eat_any : break;
            case eat_begins : res += "^="; res += quote (value_); break;
            case eat_ends : res += "$="; res += quote (value_); break;
            case eat_identical : res += "="; res += quote (value_) + " s"; break;
            case eat_in_list : res += "~="; res += quote (value_); break;
            case eat_is : res += "="; res += quote (value_); break;
            case eat_lang : res += "|="; res += quote (value_); break;
            case eat_uncased : res += "="; res += quote (value_) + " i"; break;
            default : break; }
    res += "]";
    return res; }

void css_attribute::shadow (::std::stringstream& ss, arguments& )
{   ss << "[" << attr::name (a_);
    if (has_value_)
        switch (eat_)
        {   case eat_any : break;
            case eat_begins : ss << "^=" << value_; break;
            case eat_ends : ss << "$=" << value_; break;
            case eat_identical : ss << "=" << value_ << " s"; break;
            case eat_in_list : ss << "~=" << value_; break;
            case eat_is : ss << "=" << value_; break;
            case eat_lang : ss << "|=" << value_; break;
            case eat_uncased : ss << "=" << value_ << " i"; break;
            default : break; }
    ss << "]"; }
