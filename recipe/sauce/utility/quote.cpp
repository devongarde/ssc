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
#include "utility/quote.h"

::std::string slash_quote (const ::std::string& str)
{   ::std::string res;
    const bool bq = (str.find_first_of (" \"\t\n\\") != ::std::string::npos);
    if (bq) res += '"';
    for (auto ch : str)
    {   switch (ch)
        {   case '\\' :
            case '"' :
                res += '\\';
                break;
            case '\n' :
            case '\t' :
                res += ' ';
                continue;
            default :
                if (::std::iswcntrl (ch)) continue;
                if (! (::std::iswprint (ch) || ::std::iswspace (ch))) continue;
                break; }
        res += ch; }
    if (bq) res += '"';
    return res; }

::std::string enquote (const ::std::string& str, const char space, const ::std::string& quotesep)
{   PRESUME (quotesep.length () >= 2, __FILE__, __LINE__);
    ::std::string res;
    const char quote = quotesep.at (0);
    res += quote;
    for (auto ch : str)
    {   if (ch == quote)
            res += quote;
        else if ((ch >= 0x7F) || (ch < 0x20))
        {   res += space;
            continue; }
        res += ch; }
    res += quote;
    return res; }

::std::string enquote (const ::std::string& str, const ::std::string& quotesep)
{   return enquote (str, 0x7F, quotesep); }

::std::string enquote (const vstr_t vs, const ::std::string& quotesep)
{   PRESUME (quotesep.length () >= 2, __FILE__, __LINE__);
    ::std::string res;
    const char sep = quotesep.at (1);
    for (auto str : vs)
    {   if (! res.empty ()) res += sep;
        res += quote (str, quotesep); }
    return res; }

::std::ostringstream& enquote (::std::ostringstream& ss, const vstr_t vs, const ::std::string& quotesep)
{   ss << quote (vs, quotesep);
    return ss; }

::std::string unquote (::std::string::const_iterator ci, const ::std::string::const_iterator cie, const ::std::string& quotesep)
    // presumes string prepared by quote; not bulletproof
{   PRESUME (quotesep.length () >= 2, __FILE__, __LINE__);
    const char quote = quotesep.at (0);
    ::std::string res;
    if (ci != cie)
    {   if (*ci != quote)
            res = ::std::string (ci, cie);
        else while (true)
        {   ++ci;
            if (ci == cie) break;
            if (*ci == quote)
            {   if (ci+1 == cie) break;
                if (*(ci + 1) != quote) break;
                ++ci; }
            res += *ci; } }
    return res; }

vstr_t unquote (const ::std::string& str, const ::std::size_t len, const ::std::string& quotesep)
{   PRESUME (quotesep.length () >= 2, __FILE__, __LINE__);
    vstr_t res;
    if (len) res.reserve (len);
    const char sep = quotesep.at (1);
    ::std::string::const_iterator ci = str.cbegin ();
    const ::std::string::const_iterator cie = str.cend ();
    while (ci != cie)
    {   res.push_back (unquote (ci, cie, quotesep));
        while (ci != cie && *ci != sep) ++ci; }
    if (res.size () < len) res.resize (len);
    return res; }

::std::istringstream& unquote (::std::istringstream& ss, vstr_t& res, const ::std::size_t len, const ::std::string& quotesep)
{   ::std::string tmp;
    ss >> tmp;
    res = unquote (tmp, len, quotesep);
    return ss; }

::std::string limited_string_with_quote (bool quoted, const ::std::string& s, const ::std::size_t max, const ::std::string& qs = ::std::string (QUOTESEP))
{   ::std::string res (s.substr (0, max));
    const ::std::string::size_type pos = res.find_first_of (LINE_SEPARATORS);
    if (pos != ::std::string::npos) res = res.substr (0, pos);
    if (quoted) res = enquote (res, qs);
    else if (s.length () > max) res += " ...";
    return res; }
