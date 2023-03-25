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

#pragma once
#include "utility/common.h"

#define QUOTESEP "\","

CONSTEXPR ::std::size_t def_quote_cut = 60;

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

::std::string maybe_enquote (const ::std::string& s, const ::std::string& qs = ::std::string ("\"'"));

inline ::std::string uq (const ::std::string& str, const ::std::string& qs = ::std::string (QUOTESEP))
{ return unquote (str.cbegin (), str.cend (), qs); }

#define UQ_DQ       0x00000001
#define UQ_SQ       0x00000002
#define UQ_BS       0x00000004
#define UQ_REPEATQ  0x00000008
#define UQ_SEP      0x00000010

#define UQ_ROUND    0x00000040
#define UQ_SQUARE   0x00000080
#define UQ_BRACE    0x00000100
#define UQ_ANGULAR  0x00000200
#define UQ_8        0x00000400
#define UQ_10       0x00000800
#define UQ_16       0x00001000
#define UQ_36       0x00002000
#define UQ_TRIM     0x00004000

#define UQ_C_CMT    0x00010000
#define UQ_CPP_CMT  0x00020000
#define UQ_UNIFY    0x00040000

#define BS_NUMERIC  ( UQ_8 | UQ_10 | UQ_16 | UQ_36 )
#define BS_MASK     ( UQ_BS | BS_NUMERIC )
#define BS_FN       ( UQ_BS | UQ_SQ | UQ_DQ | UQ_ROUND | UQ_TRIM )

vstr_t uq2 (const ::std::string& s, const unsigned int flags = UQ_DQ | UQ_SQ | UQ_BS, const vstr_t& sep = vstr_t (), vint_t* lines = nullptr, v_np* ticks = nullptr);

inline vstr_t uq2 (const ::std::string& s, const unsigned int flags, const ::std::string& sep, vint_t* lines = nullptr, v_np* ticks = nullptr)
{   vstr_t v;
    for (auto ch : sep)
        v.push_back (::std::string (1, ch));
    return uq2 (s, flags, v, lines, ticks); }

inline vstr_t uq2_sep (const ::std::string& s, const unsigned int flags = UQ_DQ | UQ_SQ | UQ_BS, const ::std::string& sep = ::std::string (QUOTESEP), vint_t* lines = nullptr, v_np* ticks = nullptr)
{   vstr_t v;
    v.push_back (sep);
    return uq2 (s, flags, v, lines, ticks); }

inline ::std::string uq3 (const ::std::string& s)
{   vstr_t v = uq2 (s);
    if (v.size () > 0) return v.at (0);
    return ::std::string (); }

 