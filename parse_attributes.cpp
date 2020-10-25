/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "standard.h"
#include "parse_attributes.h"
#include "context.h"
#include "elem.h"
#include "quote.h"
#include "type.h"

const ::std::size_t max_attrib = static_cast <::std::size_t> (a_y) + 1;

attributes_node::attributes_node ()
{   va_.reserve (max_attrib); }

void attributes_node::report_invalid (nitpick& nits, const html_version& v, const bool known, const ::std::string::const_iterator key_start, const ::std::string::const_iterator key_end, const elem& el) const
{   if (! el.unknown () && ! el.wild_attributes (v))
        if (known) nits.pick (nit_attribute_unrecognised_here, es_warning, ec_attribute, "attribute ", quote (::std::string (key_start, key_end)), " is unrecognised here");
        else nits.pick (nit_attribute_unrecognised, es_warning, ec_attribute, "attribute ", quote (::std::string (key_start, key_end)), " is unrecognised"); }

void attributes_node::push_back_and_report (nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                            const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end, const elem& el)
{   ::std::string x (name_start, name_end);
    if (keyed.find (x) == keyed.cend ()) keyed.insert (x);
    else nits.pick (nit_attribute_repeated, es_warning, ec_attribute, "attribute ", x, " repeated");
    if (context.tell (e_detail)) nits.pick (nit_attribute_recognised, es_detail, ec_attribute, ::std::string ("found "), x, "=", quote (::std::string (value_start, value_end)));
    va_.emplace_back (nits, v, name_start, name_end, value_start, value_end);
    if (va_.back ().invalid ()) report_invalid (nits, v, attr :: exists (x), name_start, name_end, el); }

void attributes_node::push_back_and_report (nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const elem& el)
{   ::std::string x (name_start, name_end);
    if (keyed.find (x) == keyed.cend ()) keyed.insert (x);
    else nits.pick (nit_attribute_repeated, es_warning, ec_attribute, "attribute ", x, " repeated");
    if (context.tell (e_detail)) nits.pick (nit_attribute_recognised, es_detail, ec_attribute, ::std::string ("found "), quote (x));
    va_.emplace_back (nits, v, name_start, name_end);
    if (va_.back ().invalid ()) report_invalid (nits, v, attr :: exists (x), name_start, name_end, el); }

::std::string attributes_node::rpt () const
{   ::std::string res;
    for (auto a : va_) res += a.rpt ();
    return res; }

void attributes_node::parse (nitpick& nits, const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line, const elem& el)
{   typedef enum
    {   s_dull,
        s_key,
        s_keyend,
        s_assign,
        s_key_quote, // '
        s_key_double_quote, // "
        s_val, // collecting unquoted value
        s_value_quote, // collecting value in single quote
        s_value_double_quote, // collecting value in single quote
        s_purgatory // end of collected value in quote(s)
    } e_statemachine;
    e_statemachine status = s_dull;
    ::std::string::const_iterator key_start, key_end, value_start;
    sstr_t keyed;
    va_.clear ();
    va_.reserve (max_attrib);
    nits.set_context (line, b, e);
    for (::std::string::const_iterator i = b; i != e; ++i)
    {   auto ch = *i;
        bool newline = false;
        switch (ch)
        {   case '\n' :
            case '\f' :
                newline = true;
                // drop thru'
            case '\r' :
            case '\t' :
                ch = ' '; }
        if (ch >= ' ') switch (status)
        {   case s_dull :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_dull ", ch);
                switch (ch)
                {   case ' ' :  break;
                    case '=' :  nits.pick (nit_missing_attribute_name, es_comment, ec_parser, "is an attribute name missing?\n");
                    default :   if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')))
                                {   status = s_key; key_start = i; } }
                break;
            case s_key :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_key ", ch);
                switch (ch)
                {   case ' ' :  key_end = i;
                                status = s_keyend;
                                break;
                    case '=' :  key_end = i; status = s_assign; break;
                    default :   if (    ((ch >= 'A') && (ch <= 'Z')) ||
                                        ((ch >= 'a') && (ch <= 'z')) ||
                                        ((ch >= '0') && (ch <= '9')) ||
                                        (ch == '-') ||
                                        (ch == ':')) break;
                                nits.pick (nit_attribute_name_unexpected_character, es_warning, ec_parser, ::std::string ("unexpected character "), quote (ch), " in attribute name");
                                status = s_dull; break; }
                break;
            case s_keyend :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_keyend ", ch);
                switch (ch)
                {   case ' ' :  break;
                    case '=' :  status = s_assign; break;
                    default :   push_back_and_report (nits, v, keyed, key_start, key_end, el);
                                if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')) || (ch == ':') || (ch == '-'))
                                {   status = s_key; key_start = i; }
                                else status = s_dull;
                                break; }
                break;
            case s_assign :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_assign ", ch);
                switch (ch)
                {   case ' ' :  break;
                    case '\'' : status = s_key_quote; break;
                    case '"' :  status = s_key_double_quote; break;
                    default :   if (v.xhtml ()) nits.pick (nit_xhtml_quote_values, ed_x1, "4.4. Attribute values must always be quoted", es_error, ec_parser, "attribute values must be quoted in ", v.report ());
                                status = s_val; value_start = i; break; }
                break;
            case s_val :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_val ", ch);
                switch (ch)
                {   case ' ' :  status = s_dull;
                                push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el);
                                break;
                    case '"' :
                    case '\'' : nits.pick (nit_enquote_value, es_info, ec_parser, "should the value for attribute ", quote (::std::string (key_start, key_end)), " be quoted?"); }
                break;
            case s_key_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_key_quote ", ch);
                if (newline)
                    nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in quoted attribute key");
                switch (ch)
                {   case '\'' : status = s_purgatory;
                                push_back_and_report (nits, v, keyed, key_start, key_end, el);
                                break;
                    default :   status = s_value_quote; value_start = i; break; }
                break;
            case s_key_double_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_key_double_quote ", ch);
                if (newline)
                    nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in quoted attribute key");
                switch (ch)
                {   case '"' :  status = s_purgatory;
                                push_back_and_report (nits, v, keyed, key_start, key_end, el);
                                break;
                    default :   status = s_value_double_quote; value_start = i; break; }
                break;
            case s_value_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_value_quote ", ch);
                if (newline)
                    nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in string");
                switch (ch)
                {   case '\\' :
                        if (i+1 < e) ++i; break;
                    case '\'' :
                        if ((i+1 < e) && (*(i+1) == '\'')) ++i;
                        else
                        {   status = s_purgatory;
                            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el); } }
                break;
            case s_value_double_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_value_double_quote ", ch);
                if (newline)
                     nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in string");
                switch (ch)
                {   case '\\' :
                        if (i+1 < e) ++i; break;
                    case '"' :
                        if ((i+1 < e) && (*(i+1) == '"')) ++i;
                        else
                        {   status = s_purgatory;
                            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el); } }
                break;
            case s_purgatory :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_purgatory ", ch);
                if (ch == ' ') status = s_dull;
                break; } }
    switch (status)
    {   case s_key :
            push_back_and_report (nits, v, keyed, key_start, e, el);
            break;
        case s_val :
            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, e, el);
            break;
        case s_key_quote :
        case s_key_double_quote :
            nits.pick (nit_missing_close_quote, es_warning, ec_parser, "the attribute ", quote (::std::string (key_start, key_end)), " has no closing quote");
            push_back_and_report (nits, v, keyed, key_start, e, el);
            break;
        case s_value_double_quote :
        case s_value_quote :
            nits.pick (nit_missing_close_quote, es_warning, ec_parser, "the attribute ", quote (::std::string (key_start, key_end)), " has no closing quote");
            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, e, el);
        default: break; } }

void attributes_node::manage_xmlns (html_version& v)
{   nitpick knots;
    for (auto a : va_)
        if (a.id () == a_xmlns)
        {   ::std::string ver (trim_the_lot_off (a.get_string ()));
            auto val = examine_value < t_xmlns > (knots, v, ver);
            switch (val)
            {   case x_mathml : if (! v.math ()) v.ext_set (HE_MATH_1); break;
                case x_svg : if (! v.svg ()) v.ext_set (HE_SVG_1_0); break;
                case x_xlink : if (! v.xlink ()) v.ext_set (HE_XLINK_1_0); break;
                case x_xhtml_1 : if (v.unknown ()) v = xhtml_1_0; break;
                case x_xhtml_11 : if (v.unknown ()) v = xhtml_1_1; break;
                case x_xhtml_2 : if (v.unknown ()) v = xhtml_2; break;
                default : break; }
            break; } }

e_svg_version attributes_node::get_svg (const html_version& v) const
{   bool check_profile = false;
    for (auto a : va_)
        if (a.id () == a_version)
        {   ::std::string ver (trim_the_lot_off (a.get_string ()));
            if (ver == "1.0") return sv_1_0;
            if (ver == "1.1") return sv_1_1;
            if (ver == "1.2") check_profile = true;
            break; }
    if (! check_profile)
        for (auto a : va_)
            if (a.id () == a_xmlns)
            {   ::std::string ns (trim_the_lot_off (a.get_string ()));
                if (compare_no_case (ns, "http://www.w3.org/graphics/svg/svg-19990706.dtd")) return sv_1_1;
                if (compare_no_case (ns, "https://www.w3.org/graphics/svg/svg-19990706.dtd")) return sv_1_1;
                if (compare_no_case (ns, "http://www.w3.org/tr/rec-mathml-19980407")) return sv_1_0;
                if (compare_no_case (ns, "https://www.w3.org/tr/rec-mathml-19980407")) return sv_1_0;
                else if (compare_no_case (ns, "http://www.w3.org/2000/svg")) check_profile = true;
                else if (compare_no_case (ns, "https://www.w3.org/2000/svg")) check_profile = true;
                break; }
    if (check_profile)
        for (auto a : va_)
            if (a.id () == a_baseprofile)
            {   ::std::string s (trim_the_lot_off (a.get_string ()));
                if (compare_no_case (s, "full")) return sv_1_2_full;
                return sv_1_2_tiny; }
    if (context.svg_version () != sv_none) return context.svg_version ();
    switch (v.major ())
    {   case 4 :
            switch (v.minor ())
            {   case 0 :
                case 1 : return sv_1_0;
                case 2 :
                case 3 : return sv_1_1;
                case 4 : return sv_1_2_tiny;
                default : assert (false); return sv_1_0; }
        case 5 : if (v > html_5_3) return sv_2_0;
                 break;
        default : break; }
    return sv_1_1; }

e_math_version attributes_node::get_math (const html_version& v) const
{   if (context.math_version () != math_none) return context.math_version ();
    if (v.major () == 5)
        if (v >= html_5_3) return math_3;
        else return math_2;
    return math_1; }
