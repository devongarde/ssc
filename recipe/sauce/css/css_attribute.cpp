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
#include "main/context.h"
#include "css/css_attribute.h"
#include "css/arguments.h"

void css_attribute::parse (arguments& args, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    const int k = token_find (args.t_, ct_keyword, b, to);
    ::std::string ns, wo (assemble_string (args.t_, b, to));
    if (k < 0)
    {   nitpick& nits = args.t_.at (b).nits_;
        nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": missing attribute name");
        return; }
    bool no_ns = true, all_ns = false;
    int b4 = -1;
    const int n = token_find (args.t_, ct_bar, b, to, &b4);
    if ((n > 0) && ((n < to) || (to < 0)))
    {   const int p = next_non_whitespace (args.t_, n, to);
        if ((p > 0) && ((args.t_.at (p).t_ == ct_identifier) || (args.t_.at (p).t_ == ct_keyword) || (args.t_.at (p).t_ == ct_splat)))
        {   nitpick& nits = args.t_.at (n).nits_;
            b = p;
            if (args.v_.css_namespace () < 3)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": namespaces requires CSS Namespace 3 or better");
            else if ((b < 0) && (b4 < 0))
                nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": a namespace andor an attribute must be given");
            else if (b4 > 0)
            {   no_ns = false;
                PRESUME (b4 < n, __FILE__, __LINE__);
                switch (args.t_.at (b4).t_)
                {   case ct_splat :
                        ns = "*"; all_ns = true; break;
                    case ct_keyword :
                    case ct_identifier :
                        ns = args.t_.at (b4).val_; break;
                    default :
                        nits.pick (nit_css_namespace, es_error, ec_css, tkn_rpt (args.t_.at (b4)), ": namespace name expected"); } } } }
    nitpick& nits = args.t_.at (b).nits_;
    if ((b == -1) || (args.t_.at (b).t_ != ct_keyword))
        args.t_.at (from).nits_.pick (nit_css_attribute, es_error, ec_css, "missing attribute name");
    else
    {   const int at = b;
        PRESUME (! args.styled (), __FILE__, __LINE__);
        if (no_ns || (! args.snippet_))
        {   css_attribute a (nits, args.v_, args.ns_, args.t_.at (at).val_);
            ::std::swap (*this, a); }
        else
        {   ::std::string att;
            if (! all_ns) att = ns + ":" + args.t_.at (at).val_;
            else att = args.t_.at (at).val_;
            css_attribute a (nits, args.v_, args.ns_, att);
            ::std::swap (*this, a); }
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket)) return;
        switch (args.t_.at (b).t_)
        {   case ct_eq :
                b = next_non_whitespace (args.t_, b, to);
                eat_ = eat_is;
                break;
            case ct_bar :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following |");
                else b = next_non_whitespace (args.t_, b, to);
                eat_ = eat_lang;
                break; 
            case ct_hat :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following ^");
                else b = next_non_whitespace (args.t_, b, to);
                if (context.html_ver ().css_selector () < 3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "^= requires CSS 3 or later");
                else eat_ = eat_begins;
                break; 
            case ct_dollar :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following $");
                else b = next_non_whitespace (args.t_, b, to);
                if (context.html_ver ().css_selector () < 3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "$= requires CSS 3 or later");
                else eat_ = eat_ends;
                break; 
            case ct_splat :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following *");
                else b = next_non_whitespace (args.t_, b, to);
                if (context.html_ver ().css_selector () < 3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "*= requires CSS 3 or later");
                else eat_ = eat_contains;
                break; 
            case ct_squiggle :
                b = next_non_whitespace (args.t_, b, to);
                if (args.t_.at (b).t_ != ct_eq)
                    nits.pick (nit_css_attribute, es_error, ec_css, "missing = following ~");
                else b = next_non_whitespace (args.t_, b, to);
                eat_ = eat_in_list;
                break; 
            default :
                nits.pick (nit_css_syntax, es_error, ec_css, tkn_rpt (args.t_.at (b)), ": unexpected (2)");
                return; }
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket))
        {   nits.pick (nit_css_syntax, es_error, ec_css, args.t_.at (b).val_, ": missing value (for an empty string, use \"\")");
            return; }
        switch (args.t_.at (b).t_)
        {   case ct_string :
            case ct_identifier :
            case ct_keyword :
            case ct_number :
                value_ = args.t_.at (b).val_;
                break;
            default :
                nits.pick (nit_css_attribute, es_error, ec_css, args.t_.at (b).val_, ": an attribute value should be a quoted string");
                return; }
        b = next_non_whitespace (args.t_, b, to);
        if ((b == -1) || (args.t_.at (b).t_ == ct_square_ket)) return;
        if (args.t_.at (b).t_ != ct_keyword)
        {   nits.pick (nit_css_syntax, es_error, ec_css, tkn_rpt (args.t_.at (b)), ": unexpected (3)");
            return; }
        if (context.css_selector () < 4)
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
        if ((b != -1) && (args.t_.at (b).t_ != ct_square_ket))
            nits.pick (nit_css_syntax, es_error, ec_css, "unexpected junk at end of attribute description"); } }

void css_attribute::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (e, a_.get ()); }

::std::string css_attribute::rpt () const
{   ::std::string res ("[");
    res += attr::name (a_);
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
