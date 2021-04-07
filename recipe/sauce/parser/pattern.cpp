/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "parser/pattern.h"

bool test_character_class (nitpick& nits, const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   DBG_ASSERT (*i == '\\');
    ::std::string::const_iterator x = i;
    bool res = true;
    if (++x == e)
    {   res = false;
        nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, attempt to escape the end of the string"); }
    else switch (*x)
    {   case '0' :
        case 'b' :
        case 'B' :
        case 'd' :
        case 'D' :
        case 'f' :
        case 'n' :
        case 'r' :
        case 's' :
        case 'S' :
        case 't' :
        case 'v' :
        case 'w' :
        case 'W' :
        case '\\' :
        case '{' :
        case '}' :
        case '[' :
        case ']' :
        case '(' :
        case ')' :
        case '<' :
        case '>' :
        case '?' :
        case '=' :
        case '.' :
        case '*' :
        case '+' :
        case '^' :
        case '$' :
        case '!' :
        case '|' :
        case '-' :
        case ':' :
        case ',' :
            ++x;
            break;
        case 'c' :
            ++x;
            if ((x == e) || (*x < 'A') || (*x > 'Z'))
            {   nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, '\\c' must be followed by an upper-case letter");
                res = false; }
            break;
        case 'u' :
            if ((++x != e) && (*x == '{'))
            {   if (is_hex (x, e)) if (is_hex (++x, e))
                    if ((++x != e) && (*x == '-'))
                    {   if (is_hex (x, e)) if (is_hex (++x, e)) if (is_hex (++x, e))
                            if ((++x != e) && (*x == '}')) break; }
                    else if (is_hex (x, e)) if (is_hex (++x, e))
                        if ((++x != e) && (*x == '}')) break;
                nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "'in PATTERN, \\u{...}' must contain four hex digits, or two, then '-', then three, hex digits");
                res = false; break; }
            else if (is_hex (x, e)) if (is_hex (++x, e)) if (is_hex (++x, e)) if (is_hex (++x, e)) break;
            nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, '\\u' must be followed by four hexadecimal digits");
            res = false;
            break;
        case 'x' :
            if (is_hex (++x, e)) if (is_hex (++x, e)) break;
            nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, '\\x' must be followed by two hexadecimal digits");
            res = false;
            break;
        default :
            nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_info, ec_regex, "in PATTERN, the backslash before '", *x , "' is unnecessary");
            ++x;
            break; }
    i = x;
    return res; }

bool test_bra (nitpick& nits, const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   DBG_ASSERT (*i == '(');
    ::std::string::const_iterator x = i;
    bool res = true, tmp = false;
    if (++x == e)
        nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_info, ec_regex, "in PATTERN, is that unclosed bracket intended?");
    else switch (*x)
    {   case '?' :
            if (++x != e)
                switch (*x)
                {   case '=' :
                    case '!' :
                        if ((++x != e) && (++x != e) && (*x == ')')) break;
                        nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, for '(?=X)' or '(?!X)', the bracket must be closed, and X must be a single character");
                        res = false;
                        break;
                    case '<' :
                        if (++x != e)
                            switch (*x)
                            {   case '=' :
                                case '!' :
                                    if ((++x != e) && (++x != e) && (*x == ')')) break;
                                    nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, for '(?<=X)' or '(?<!X)', the bracket must be closed, and X must be a single character");
                                    res = false;
                                    break;
                                default :
                                    while (++x != e)
                                        if (*x == '>')
                                        {   tmp = true; break; }
                                    if (tmp)
                                    {   tmp = false;
                                        if (++x != e)
                                            while (++x != e)
                                                if (*x == ')')
                                                {   tmp = true; break; } }
                                    if (! tmp)
                                    {   nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, for '(?<Name>X)', both angular and rounded brackets must be closed");
                                        res = false; } }
                            break;
                    case ':' :
                        if ((++x != e) && (++x != e) && (*x == ')')) break;
                        nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, for '(?:=X)', the bracket must be closed, and X must be a single character");
                        res = false;
                        break;
                }
            break;
        default :
            break; }
    i = x;
    return res; }

bool test_squ (nitpick& nits, const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   DBG_ASSERT (*i == '[');
    ::std::string::const_iterator x = i;
    bool res = true, tmp = false;
    while (++x != e)
        if (*x == ']')
        {   tmp = true; break; }
    if (! tmp)
    {   nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_info, ec_regex, "in PATTERN, is that unclosed square bracket intended?");
        res = false; }
    i = x;
    return res; }

bool test_brace (nitpick& nits, const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   DBG_ASSERT (*i == '{');
    ::std::string::const_iterator x = i;
    bool res = true, tmp = false, had_comma = false;
    while (++x != e)
        if (*x == '}')
        {   tmp = true; break; }
        else switch (*x)
        {   case ',' :
                if (had_comma)
                {   nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, no more than one comma between braces");
                    res = false; }
                else had_comma = true;
                break;
            case '0' :
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' :
                break;
            default :
                nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_error, ec_regex, "in PATTERN, only digits (and a comma) may lie between braces");
                res = false;
                break; }
    if (! tmp)
    {   nits.pick (nit_bad_pattern, ed_ecma, "AtomEscape", es_info, ec_regex, "in PATTERN, is that unclosed brace ('{') intended?");
        res = false; }
    i = x;
    return res; }

bool verify_pattern (nitpick& nits, const html_version& v, const ::std::string& text)
{   ::std::string::const_iterator b = text.cbegin ();
    ::std::string::const_iterator e = text.cend ();
    bool res = true;
    for (::std::string::const_iterator i = b; res && (i != e); ++i)
    {   switch (*i)
        {   case '\\' : res = test_character_class (nits, v, b, e, i); break;
            case '(' : res = test_bra (nits, v, b, e, i); break;
            case '[' : res = test_squ (nits, v, b, e, i); break;
            case '{' : res = test_brace (nits, v, b, e, i); break;
            default : break; }
        if (i == e) { res = false; break; } }
    return res; }
