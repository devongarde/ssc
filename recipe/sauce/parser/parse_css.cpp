/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "parser/parse_css.h"
#include "main/context.h"

void parse_css (nitpick& nits, const html_version& , smsid_t& ids, const ::std::string& content, const e_charcode )
{   typedef enum
    {   st_dull,
        st_single_quote,
        st_double_quote,
        st_class_start,
        st_class,
        st_comment_maybe,
        st_comment_end_maybe,
        st_comment
    } css_status;

    css_status status = st_dull;
    const ::std::string::const_iterator b = content.begin ();
    const ::std::string::const_iterator e = content.end ();
    ::std::string::const_iterator start = b;
    int count = 0;
    int line = 1;

    for (::std::string::const_iterator i = b; i != e; ++i)
    {   auto ch = *i;
        bool newline = false;
        switch (ch)
        {   case '\r' :
                ++line;
                break;
            case '\n' :
            case '\f' :
                newline = true;
                ++line;
                [[fallthrough]];
            case '\t' :
                ch = ' ';
                break;
            default :
                break; }
        if (::std::iswcntrl (ch)) continue;
        switch (status)
        {   case st_class :
                if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')) && ((ch < '0') || (ch > '9')) && (ch != '-') && (ch != '_'))
                {   ::std::string x (start, i);
                    if (ids.find (x) == ids.cend ())
                    {   ids.emplace (::std::string (start, i), 0);
                        if (context.tell (e_debug)) nits.pick (nit_found_css_class, es_debug, ec_css, "Found CSS class ", x);
                        ++count; }
                    status = st_dull; }
                [[fallthrough]];
            case st_dull :
                switch (ch)
                {   case '.' :  status = st_class_start; break;
                    case '\'' : status = st_single_quote; break;
                    case '"' : status = st_double_quote; break;
                    case '/' : status = st_comment_maybe; break;
                    default : break; }
                break;
            case st_class_start :
                if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || (ch != '-') || (ch != '_'))  // CSS 2.1, pg 48
                {   status = st_class; start = i; }
                else status = st_dull;
                break;
            case st_single_quote :
                if (newline) ch = '\'';
                if (ch == '\'') status = st_dull;
                break;
            case st_double_quote :
                if (newline) ch = '"';
                if (ch == '"') status = st_dull;
                break;
            case st_comment_maybe :
                if (ch == '*') status = st_comment;
                else status = st_dull;
                break;
            case st_comment :
                if (ch == '*') status = st_comment_end_maybe;
                break;
            case st_comment_end_maybe :
                if (ch == '/') status = st_dull;
                else status = st_comment;
                break; } }
    if (context.tell (e_debug))
        switch (count)
        {   case 0 : nits.pick (nit_found_css_class, es_comment, ec_css, "no CSS classes encountered"); break;
            case 1 : nits.pick (nit_found_css_class, es_comment, ec_css, "1 CSS class added"); break;
            default : nits.pick (nit_found_css_class, es_comment, ec_css, count, " CSS classes added"); break; } }
