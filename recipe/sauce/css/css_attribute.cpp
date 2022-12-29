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

void css_attribute::swap (css_attribute& a) noexcept
{   a_.swap (a.a_);
    ::std::swap (has_value_, a.has_value_);
    name_.swap (a.name_);
    value_.swap (a.value_);
    ::std::swap (eat_, a.eat_); }

void css_attribute::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    ::std::string ss (s);
    const ::std::string::size_type pos = ss.find_first_of ("=~^$*|");
    if (pos != ::std::string::npos)
    {   ::std::string ssss (trim_the_lot_off (ss.substr (0, pos)));
        if (ssss.empty ())
            nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": missing attribute name");
        else ss = ssss; }
    css_attribute a (nits, args.v_, args.ns_, ss);
    swap (a);
    if (pos != ::std::string::npos)
    {   const ::std::string::size_type fin = s.length ();
        if (s.at (pos) == '=')
        {   has_value_ = true;
            if (fin <= pos + 1) nits.pick (nit_value_expected, ed_css_20, "5.1 Pattern matching", es_error, ec_css, "missing value (for an empty value, use \"\")");
            else
            {   value_ = s.substr (pos+1);
                if (fin > pos + 2)
                    if ((s.at (fin - 1) != '"') && (s.at (fin - 2) == ' '))
                        if (args.v_ < html_css_selectors_4)
                            nits.pick (nit_css_version, ed_css_selectors_4, "2 Selectors Overview", es_error, ec_css, "case sensitivity selectors require CSS Selectors Level 4");
                        else switch (s.at (fin - 1))
                            {   case 'i' :
                                    value_ = value_.substr (0, value_.length () - 2);
                                    eat_ = eat_uncased;
                                    break;
                                case 's' :
                                    value_ = value_.substr (0, value_.length () - 2);
                                    eat_ = eat_identical;
                                    break;
                                default :
                                    nits.pick (nit_unexpected, ed_css_selectors_4, "2 Selectors", es_error, ec_css, quote (s.at (fin - 1)), " is unexpected");
                                    break; } } }
        else if (fin <= pos + 2)
            nits.pick (nit_value_expected, ed_css_20, "5.1 Pattern matching", es_error, ec_css, "value expected (for an empty value, use \"\")");
        else if (s.at (pos+1) != '=')
            nits.pick (nit_unknown_operator, ed_css_selectors_3, "2 Selectors", es_error, ec_css, quote (s.substr (pos, 2)), ": unknown operator");
        else
        {   value_ = trim_the_lot_off (s.substr (pos+2));
            has_value_ = true;
            switch (s.at (pos))
            {   case '~' :
                    eat_ = eat_in_list;
                    break;
                case '^' :
                    if (args.v_.css_version () < css_3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "^= requires CSS 3 or later");
                    else eat_ = eat_begins;
                    break;
                case '$' :
                    if (args.v_.css_version () < css_3) nits.pick (nit_css_version, ed_css_selectors_3, "2 Selectors", es_error, ec_css, "$= requires CSS 3 or later");
                    else eat_ = eat_ends;
                    break;
                case '*' :
                    eat_ = eat_contains;
                    break;
                case '|' :
                    eat_ = eat_lang;
                    break;
                default :
                    nits.pick (nit_unknown_operator, ed_css_selectors_3, "2 Selectors", es_error, ec_css, quote (s.substr (pos, 2)), ": unknown operator");
                    break; } }
        if (! value_.empty ())
            if ((value_.at (0) != '"') && (value_.at (0) != '\''))
                nits.pick (nit_enquote_value, ed_css_selectors_3, "2 Selectors", es_warning, ec_css, "attribute values should be quoted"); } }

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
