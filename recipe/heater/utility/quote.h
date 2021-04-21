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

#pragma once
#include "utility/common.h"
#define QUOTESEP "\","

const ::std::size_t def_quote_cut = 60;

::std::string slash_quote (const ::std::string& str);
::std::string enquote (const ::std::string& str, const char space, const ::std::string& qs = ::std::string (QUOTESEP));
::std::string enquote (const ::std::string& str, const ::std::string& qs = ::std::string (QUOTESEP));
::std::string enquote (const vstr_t vs, const ::std::string& quotesep = ::std::string (QUOTESEP));
::std::ostringstream& enquote (::std::ostringstream& ss, const vstr_t vs, const ::std::string& quotesep = ::std::string (QUOTESEP));
::std::string unquote (::std::string::const_iterator ci, const ::std::string::const_iterator cie, const ::std::string& quotesep = ::std::string (QUOTESEP));
vstr_t unquote (const ::std::string& str, const ::std::size_t len = 0, const ::std::string& quotesep = ::std::string (QUOTESEP));
::std::istringstream& unquote (::std::istringstream& ss, vstr_t& res, const ::std::size_t len = 0, const ::std::string& quotesep = ::std::string (QUOTESEP));

::std::string limited_string_with_quote (bool quoted, const ::std::string& s, const ::std::size_t max, const ::std::string& qs);
inline ::std::string limited_string (const ::std::string& s, const ::std::size_t max = def_quote_cut, const ::std::string& qs = ::std::string (QUOTESEP))
{   return limited_string_with_quote (false, s, max, qs); }
inline ::std::string quoted_limited_string (const ::std::string& s, const ::std::size_t max = def_quote_cut, const ::std::string& qs = ::std::string (QUOTESEP))
{   return limited_string_with_quote (true, s, max, qs); }

inline ::std::string quote (const ::std::string& str, const ::std::string& qs = ::std::string (QUOTESEP))
{ return limited_string_with_quote (true, str, def_quote_cut, qs); }
inline ::std::string quote (const char ch, const ::std::string& qs = ::std::string (QUOTESEP))
{ return limited_string_with_quote (true, ::std::string (1, ch), def_quote_cut, qs); }
inline ::std::string quote (const vstr_t vs, const ::std::string& quotesep = ::std::string (QUOTESEP))
{ return enquote (vs, quotesep); }
inline ::std::ostringstream& quote (::std::ostringstream& ss, const vstr_t vs, const ::std::string& quotesep = ::std::string (QUOTESEP))
{ return enquote (ss, vs, quotesep); }

inline ::std::string uq (const ::std::string& str, const ::std::string& qs = ::std::string (QUOTESEP))
{ return unquote (str.cbegin (), str.cend (), qs); }
