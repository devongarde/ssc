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
#include "utility/common.h"
#include "url/url_sanitise.h"

struct escape_t
{   char encoding_ [4];
    char ch_; }
encoded [] =
{   { "%20", SPACE },
    { "%23", HASH },
    { "%24", '$' },
    { "%25", PERCENT },
    { "%26", '&' },
//    { "%2F", '/' },
    { "%3A", COLON },
    { "%3B", ';' },
    { "%3C", '<' },
    { "%3D", EQUAL },
    { "%3E", '>' },
    { "%3F", QUESTION },
    { "%40", '@' },
    { "%5B", '[' },
    { "%5C", '\\'},
    { "%5D", ']' },
    { "%5E", '^' },
    { "%60", '\''},
    { "%7B", '{' },
    { "%7C", '|' },
    { "%7D", '}' },
    { "%7E", '~' } };

typedef ssc_map < ::std::string, char > decode_map_t;
typedef ssc_map < char, ::std::string > encode_map_t;
decode_map_t decode_map;
encode_map_t encode_map;

void code_map_init (nitpick& nits)
{   CONSTEXPR ::std::size_t max = sizeof (encoded) / sizeof (escape_t);
    for (::std::size_t i = 0; i < max; i++)
    {   if (decode_map.find (GSL_AT (encoded, i).encoding_) != decode_map.cend ())
            nits.pick (nit_symbol_aleady_defined, es_error, ec_program,  "Program error: decoder ", GSL_AT (encoded, i).encoding_, " already defined");
        else decode_map.insert (decode_map_t::value_type (GSL_AT (encoded, i).encoding_, GSL_AT (encoded, i).ch_));
        if (encode_map.find (GSL_AT (encoded, i).ch_) != encode_map.cend ())
            nits.pick (nit_symbol_aleady_defined, es_error, ec_program,  "Program error: encoder ", GSL_AT (encoded, i).ch_, " already defined");
        else encode_map.insert (encode_map_t::value_type (GSL_AT (encoded, i).ch_, GSL_AT (encoded, i).encoding_)); } }

::std::string unescape (const ::std::string& s)
{   const ::std::size_t len = s.length ();
    if (len < 3) return s;
    ::std::string res;
    for (::std::size_t x = 0; x < len; ++x)
        if ((x > len - 3) || (s.at (x) != PERCENT)) res += s.at (x);
        else
        {   ::std::string sub (s.substr (x, 3));
            auto i = decode_map.find (sub);
            if (i != decode_map.end ())
            {   res += i -> second;
                x += 2; }
            else res += s.at (x); }
    return res; }

::std::string enescape (const ::std::string& s)
{   const ::std::size_t len = s.length ();
    if (len == 0) return s;
    ::std::string res;
    const ::std::size_t pos = s.find (COLON);
    if (pos == s.npos) return s;
    res = s.substr (0, pos + 2);
    for (::std::size_t x = pos + 2; x < len ; ++x)
    {   auto i = encode_map.find (s.at (x));
        if (i != encode_map.end ()) res += s.at (x);
        else res += i -> second;  }
    return res; }

::std::string sanitise (const ::std::string& s)
{   ::std::string res (unescape (s));
    ::std::size_t ds = 0;
    while (true)
    {   ds = res.find ("//", ds);
        if (ds == ::std::string::npos) break;
        if (ds == 0 || res.at (ds-1) != COLON) res.replace (ds, 2, "/");
        ++ds; }
    ds = 0;
    while (true)
    {   ds = res.find ("/./", ds);
        if (ds == ::std::string::npos) break;
        if (ds == 0 || res.at (ds-1) != COLON) res.replace (ds, 3, "/");
        ++ds; }
    if ((res.length () > 2) && (res.substr (res.length () - 2) == "/."))
        res = res.substr (0, res.length () - 2);
    ds = 0;
    while (true)
    {   ds = res.find ("/..", ds);
        if (ds == ::std::string::npos) break;
        if (ds > 0)
        {   ::std::size_t prev = res.substr (0, ds).rfind ('/');
            if (prev != ::std::string::npos)
                if ((prev == 0) || (res.at (prev - 1) != COLON))
                {   PRESUME (prev < ds, __FILE__, __LINE__);
                    res.replace (prev, ds-prev+3, "/"); } }
        ++ds; }
    return res; }

::std::string desanitise (const ::std::string& s)
{   return enescape (s); }

int char2hex (const char ch)
{   if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'F')
        return ch - 'a' + 10;
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return 0); }

bool is_hex (const char ch) noexcept
{   if (ch >= '0' && ch <= '9')
        return true;
    if (ch >= 'A' && ch <= 'F')
        return true;
    return (ch >= 'a' && ch <= 'F'); }

::std::string decode (const ::std::string& url)
{   ::std::string res;
    bool percent = false;
    bool first = true;
    int val = 0;
    char was = ' ';
    for (auto ch : url)
        if (percent)
            if (first)
                if (! is_hex (ch))
                {   res += PERCENT;
                    res += ch;
                    percent = false; }
                else
                {   val = char2hex (ch);
                    was = ch;
                    first = false; }
            else
            {   if (! is_hex (ch))
                {   res += PERCENT;
                    res += was;
                    res += ch; }
                else
                {   val *= 16;
                    val += char2hex (ch);
                    res += GSL_NARROW_CAST < char > (val); }
                val = 0;
                first = true;
                percent = false; }
        else if (ch == PERCENT) percent = true;
        else if (ch < SPACE) continue;
        else res += ch;
    return res; }

::std::string tolower (const ::std::string& s)
{   ::std::string res;
    for (auto ch : s) res += GSL_NARROW_CAST < char > (tolower (ch));
    return res; }
