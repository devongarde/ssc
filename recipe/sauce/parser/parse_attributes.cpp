/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

#include "main/standard.h"
#include "parser/parse_attributes.h"
#include "main/context.h"
#include "element/elem.h"
#include "utility/quote.h"
#include "type/type.h"
#include "attribute/namespace.h"

constexpr ::std::size_t max_attrib = static_cast <::std::size_t> (a_y) + 1;

attributes_node :: attributes_node (element_node* box)
    :   box_ (box)
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    va_.reserve (max_attrib); }

void attributes_node::report_invalid (nitpick& nits, const html_version& v, const bool known, const ::std::string::const_iterator key_start, const ::std::string::const_iterator key_end, const elem& el) const
{   ::std::string s (key_start, key_end);
    if (el.wild_attributes (v))
        if (s.find (':') != ::std::string::npos)
            nits.pick (nit_bad_wild, ed_jan21, "4.8.6 The embed element ", es_error, ec_attribute, quote(s), ": parameters cannot be in namespaces");
        else if (s.find_first_of (UPPERCASE) != ::std::string::npos)
            nits.pick (nit_bad_wild, ed_jan21, "4.8.6 The embed element ", es_error, ec_attribute, quote(s), ": parameters may not contain upper case letters");
        else nits.pick (nit_wild_attribute, ed_jan21, "4.8.6 The embed element ", es_info, ec_attribute, quote (s), " noted");
    else if (known) nits.pick (nit_attribute_unrecognised_here, es_warning, ec_attribute, "attribute ", quote (s), " is unrecognised here (", v.report (), ")");
        else nits.pick (nit_attribute_unrecognised, es_warning, ec_attribute, "attribute ", quote (s), " is unrecognised (", v.report (), ")"); }

void attributes_node::push_back_and_report (nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                            const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end, const elem& el, const bool normal)
{   ::std::string x (name_start, name_end);
    if (keyed.find (x) == keyed.cend ()) keyed.insert (x);
    else if (normal) nits.pick (nit_attribute_repeated, es_warning, ec_attribute, "attribute ", x, " repeated");
    if (context.tell (e_detail)) nits.pick (nit_attribute_recognised, es_detail, ec_attribute, ::std::string ("found "), x, "=", quote (::std::string (value_start, value_end)));
    va_.emplace_back (nits, v, this, name_start, name_end, value_start, value_end, normal);
    if (va_.back ().invalid () && normal) report_invalid (nits, v, attr :: exists (x), name_start, name_end, el); }

void attributes_node::push_back_and_report (nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                            const elem& el, const bool normal)
{   ::std::string x (name_start, name_end);
    if (keyed.find (x) == keyed.cend ()) keyed.insert (x);
    else if (normal) nits.pick (nit_attribute_repeated, es_warning, ec_attribute, "attribute ", x, " repeated");
    if (context.tell (e_detail)) nits.pick (nit_attribute_recognised, es_detail, ec_attribute, ::std::string ("found "), quote (x));
    va_.emplace_back (nits, v, this, name_start, name_end, normal);
    if (va_.back ().invalid () && normal) report_invalid (nits, v, attr :: exists (x), name_start, name_end, el); }

::std::string attributes_node::rpt () const
{   ::std::string res;
    for (auto a : va_) res += a.rpt ();
    return res; }

void attributes_node::parse (nitpick& nits, const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line, const elem& el, const bool normal)
{   VERIFY_NOT_NULL (box (), __FILE__, __LINE__);
    typedef enum
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
                [[fallthrough]];
            case '\r' :
            case '\t' :
                ch = ' ';
                break;
            default :
                break; }
        if (! ::std::iswcntrl (ch)) switch (status)
        {   case s_dull :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_dull ", ch);
                switch (ch)
                {   case ' ' :  break;
                    case '=' :  if (! el.unknown ()) nits.pick (nit_missing_attribute_name, es_comment, ec_parser, "is an attribute name missing?\n");
                                break;
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
                                if (normal) switch (ch)
                                {   case '<' :
                                    case '>' :
                                        nits.pick (nit_missing_double_quote, es_warning, ec_parser, "unexpected character ", quote (ch), " in attribute name (has a \" been omitted?)");
                                        break;
                                    default :
                                        nits.pick (nit_attribute_name_unexpected_character, es_warning, ec_parser, "unexpected character ", quote (ch), " in attribute name");
                                        break; }
                                status = s_dull; break; }
                break;
            case s_keyend :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_keyend ", ch);
                switch (ch)
                {   case ' ' :  break;
                    case '=' :  status = s_assign; break;
                    default :   push_back_and_report (nits, v, keyed, key_start, key_end, el, normal);
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
                    default :   if (v.xhtml () && normal) nits.pick (nit_xhtml_quote_values, ed_x1, "4.4. Attribute values must always be quoted", es_error, ec_parser, "attribute values must be quoted in ", v.report ());
                                status = s_val; value_start = i; break; }
                break;
            case s_val :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_val ", ch);
                switch (ch)
                {   case ' ' :  status = s_dull;
                                push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el, normal);
                                break;
                    case 0x60 : if (! v.xhtml () && normal)
                                    nits.pick (nit_naked_grave, ed_jan10, "1.10.2 Syntax errors", es_error, ec_parser, "an attribute value must be quoted if it contains a naked grave accent (\"`\")");
                                break;
                    case '"' :
                    case '\'' : nits.pick (nit_enquote_value, es_info, ec_parser, "should the value for attribute ", quote (::std::string (key_start, key_end)), " be quoted?");
                                break;
                    default :
                                break; }
                break;
            case s_key_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_key_quote ", ch);
                if (newline) if (normal) nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in quoted attribute key");
                switch (ch)
                {   case '\'' : status = s_purgatory;
                                push_back_and_report (nits, v, keyed, key_start, key_end, el, normal);
                                break;
                    default :   status = s_value_quote; value_start = i; break; }
                break;
            case s_key_double_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_key_double_quote ", ch);
                if (newline) if (normal) nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in quoted attribute key");
                switch (ch)
                {   case '"' :  status = s_purgatory;
                                push_back_and_report (nits, v, keyed, key_start, key_end, el, normal);
                                break;
                    default :   status = s_value_double_quote; value_start = i; break; }
                break;
            case s_value_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_value_quote ", ch);
                if (newline) if (normal) nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in string");
                switch (ch)
                {   case '\\' :
                        if (i+1 < e) ++i;
                        break;
                    case '\'' :
                        if ((i+1 < e) && (*(i+1) == '\'')) ++i;
                        else
                        {   status = s_purgatory;
                            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el, normal); }
                        break;
                    default :
                        break; }
                break;
            case s_value_double_quote :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_value_double_quote ", ch);
                if (newline) if (normal) nits.pick (nit_newline_in_string, es_warning, ec_parser, "newline in string");
                switch (ch)
                {   case '\\' :
                        if (i+1 < e) ++i;
                        break;
                    case '"' :
                        if ((i+1 < e) && (*(i+1) == '"')) ++i;
                        else
                        {   status = s_purgatory;
                            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, i, el, normal); }
                        break;
                   default :
                        break; }
                break;
            case s_purgatory :
                if (context.tell (e_all)) nits.pick (nit_all, es_all, ec_parser, "s_purgatory ", ch);
                if (::std::iswspace (ch)) status = s_dull;
                break; } }
    switch (status)
    {   case s_key :
            push_back_and_report (nits, v, keyed, key_start, e, el, normal);
            break;
        case s_val :
            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, e, el, normal);
            break;
        case s_key_quote :
        case s_key_double_quote :
            if (normal) nits.pick (nit_missing_close_quote, es_warning, ec_parser, "the attribute ", quote (::std::string (key_start, key_end)), " has no closing quote");
            push_back_and_report (nits, v, keyed, key_start, e, el, normal);
            break;
        case s_value_double_quote :
        case s_value_quote :
            nits.pick (nit_missing_close_quote, es_warning, ec_parser, "the attribute ", quote (::std::string (key_start, key_end)), " has no closing quote");
            push_back_and_report (nits, v, keyed, key_start, key_end, value_start, e, el, normal);
            break;
        default: break; } }

void attributes_node::process_attributes (nitpick& nits, const html_version& v, element_node* box, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line)
{   attributes_node an (box);
    an.parse (nits, v, b, e, line, elem (), false); }

void attributes_node::manage_xmlns (nitpick& nits, html_version& v)
{   nitpick knots;
    for (auto a : va_)
        if (a.id () == a_xmlns)
        {   ::std::string ver (trim_the_lot_off (a.get_string ()));
            auto val = examine_value < t_xmlns > (knots, v, ver);
            switch (val)
            {   case x_mathml : if (! v.math ()) v.set_ext (HE_MATH_1); break;
                case x_svg : if (! v.svg ()) v.set_ext (HE_SVG_10); break;
                case x_xlink : if (! v.xlink ()) v.set_ext (HE_XLINK_1_0); break;
                case x_xhtml_1_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, quote (ver), " is non-standard (it was withdrawn before XHTML 1.0 was published)");
                    [[fallthrough]];
                case x_xhtml_1 : if (v.unknown ()) v = xhtml_1_0; break;
                case x_xhtml_11 : if (v.unknown ()) v = xhtml_1_1; break;
                case x_xhtml_2 : if (v.unknown ()) v = xhtml_2; break;
                default : break; }
            break; } }

e_svg_version attributes_node::get_svg (const html_version& v) const
{   bool check_profile = false;
    nitpick nuts;
    for (auto a : va_)
        if (a.id () == a_version)
        {   ::std::string ver (trim_the_lot_off (a.get_string ()));
            const e_svg_version ev = examine_value < t_svg_version > (nuts, v, ver);
            if (ev == sv_1_2_tiny) check_profile = true;
            else if (ev != sv_none) return ev;
            else check_profile = (ver.length () >= 3) && (ver.substr (0, 3) == "1.2");
            break; }
    if (! check_profile)
        for (auto a : va_)
            if (a.id () == a_xmlns)
            {   ::std::string ver (trim_the_lot_off (a.get_string ()));
                const e_svg_version_grand evg = examine_value < t_svg_version_grand > (nuts, v, ver);
                if (evg == svg_1_2_tiny) check_profile = true;
                else if (evg != svg_none) return static_cast < e_svg_version > (evg);
                else check_profile = (ver.length () >= 27) && (ver.substr (0, 27) == SVG_2000);
                break; }
    if (check_profile)
    {   for (auto a : va_)
            if (a.id () == a_baseprofile)
            {   ::std::string s (trim_the_lot_off (a.get_string ()));
                if (compare_no_case (s, "full")) return sv_1_2_full;
                break; }
        return sv_1_2_tiny; }
    if (context.svg_version () != sv_none) return context.svg_version ();
    switch (v.mjr ())
    {   case 0 :
        case 1 :
        case 2 :
        case 3 : return sv_none;
        case 4 :
            switch (v.mnr ())
            {   case 0 :
                case 1 : return sv_none;
                case 2 : return sv_1_0;
                case 3 : return sv_1_1;
                case 4 : return sv_1_2_tiny;
                default : GRACEFUL_CRASH (__FILE__, __LINE__);
                          UNREACHABLE (return sv_1_0); }
        default : break; }
    if (v >= html_apr21) return sv_2_1;
    if (v >= html_oct18) return sv_2_0;
    return sv_1_1; }

e_math_version attributes_node::get_math (const html_version& v) const
{   if (context.math_version () != math_none) return context.math_version ();
    switch (v.mjr ())
    {   case 0 :
        case 1 :
        case 2 :
        case 3 : return math_none;
        case 4 :
            switch (v.mnr ())
            {   case 0 :
                case 1 : return math_1;
                case 2 :
                case 3 :
                case 4 : return math_2;
                default : GRACEFUL_CRASH (__FILE__, __LINE__);
                          UNREACHABLE (return math_1); }
        default : break; }
    if (v >= html_apr21) return math_4;
    if (v >= html_5_0) return math_3;
    return math_2; }

prefixes_ptr attributes_node::prefixes () const
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prefixes (); }

void attributes_node::prepare_prefixes ()
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prepare_prefixes (); }

namespaces_ptr attributes_node::namespaces () const
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> namespaces (); }

void attributes_node::prepare_namespaces ()
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prepare_namespaces (); }
