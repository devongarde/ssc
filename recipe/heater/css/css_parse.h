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
#include "main/enum.h"
#include "feedback/nitpick.h"

struct token_t
{   css_token t_ = ct_error;
    ::std::string val_;
    nitpick nits_;
    int mum_ = -1, next_ = -1, child_ = -1;
    token_t () = default;
    token_t (const css_token t, const int line, const ::std::string& x, const ::std::string& s = ::std::string ())
        : t_ (t), val_ (s)
    {   nits_.set_context (line, x); } };

typedef ::std::vector < token_t > vtt_t;

::std::string tkn_rpt (const css_token t, const ::std::string& s = ::std::string ());
inline ::std::string tkn_rpt (const token_t& t)
{ return tkn_rpt (t.t_, t.val_); }
::std::string assemble_string (vtt_t& vt, const int from, const int to = -1, const bool inclusive = false);
int token_find (const vtt_t& vt, const css_token t, const int from = 0, const int to = -1, int* prev = nullptr);
int ident_find (const vtt_t& vt, const ::std::string& kw, const int from = 0, const int to = -1, int* prev = nullptr);
int first_non_whitespace (const vtt_t& vt, int from, const int to = -1);
int next_non_whitespace (const vtt_t& vt, const int from, const int to = -1);
int next_token_at (const vtt_t& vt, const int from, const int to = -1);
::std::string assemble_unit (vtt_t& vt, int& i, const int to = -1);

#define TC_ERROR    0x0001
#define TC_BASE     0x0002
#define TC_SPACE    0x0004
#define TC_COMPARE  0x0008
#define TC_PLUMBING 0x0010
#define TC_ROUND    0x0020
#define TC_SQUIGGLE 0x0040
#define TC_SQUARE   0x0080
#define TC_VALUE    0x0100

unsigned short token_category (const css_token t);
