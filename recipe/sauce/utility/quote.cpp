/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

::std::string maybe_enquote (const ::std::string& s, const ::std::string& qs)
{   PRESUME (! qs.empty (), __FILE__, __LINE__);
    if (s.empty ()) return enquote (s, ' ', qs);
    for (auto q : qs)
        if (s.find (q) != ::std::string::npos)
            return enquote (s, ' ', ::std::string (1, q));
    return s; }

void pushpush (vstr_t& res, vint_t* lines, const ::std::string& s, const int line)
{   if (! s.empty ())
    {   res.push_back (s);
        if (lines != nullptr) lines -> push_back (line); } }

vstr_t uq2 (const ::std::string& s, const unsigned int flags, const vstr_t& sep, vint_t* lines, v_np* ticks)
{   for (auto p : sep)
    {   PRESUME (! p.empty (), __FILE__, __LINE__);
        PRESUME (p.find ("\\") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_SQ) == UQ_SQ) PRESUME (p.find ("'") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_DQ) == UQ_DQ) PRESUME (p.find ("\"") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_BS) == UQ_BS) PRESUME (p.find ("\\") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_ROUND) == UQ_ROUND) PRESUME (p.find ("(") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_SQUARE) == UQ_SQUARE) PRESUME (p.find ("[") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_BRACE) == UQ_BRACE) PRESUME (p.find ("{") == ::std::string::npos, __FILE__, __LINE__);
        if ((flags & UQ_ANGULAR) == UQ_ANGULAR) PRESUME (p.find ("<") == ::std::string::npos, __FILE__, __LINE__); }
    vstr_t res;
    ::std::string o;
    int br = 0, sq = 0, an = 0, ro = 0;
    typedef enum { uq_dull, uq_bracket, uq_expect_sep, uq_es2, uq_sq, uq_dq, uq_bs, uq_repsq, uq_repdq, uq_borked } e_uq_status;
    const e_uq_status breakage = uq_sq;
    e_uq_status state = uq_dull;
    typedef ::std::vector < e_uq_status > old_stack;
    old_stack os;
    typedef enum { cq_dull, cq_pos_cmt, cq_cpp, cq_c, cq_pos_c_end } e_cmt_status;
    e_cmt_status cmt_state = cq_dull;
    const ::std::string::const_iterator sb = s.cbegin ();
    const ::std::string::const_iterator se = s.cend ();
    ::std::string::const_iterator bol = s.begin ();
    ::std::string::const_iterator eol = s.begin ();
    ::std::string bst;
    if ((flags & UQ_36) == UQ_36) bst = ALPHANUMERIC;
    else if ((flags & UQ_16) == UQ_16) bst = HEX;
    else if ((flags & UQ_10) == UQ_10) bst = DENARY;
    else if ((flags & UQ_8) == UQ_8) bst = OCTAL;
    bool had_whitespace = false;
    bool had_content = false;
    bool newline = false;
    int line = 0;
    nitpick nits;
    for (::std::string::const_iterator i = sb; i != se; ++i)
    {   bool extend = true;
        bool consider = true;
        bool is_q = false;
        if ((ticks != nullptr) || (lines != nullptr))
            switch (*i)
            {   case '\r' :
                    if (ticks != nullptr)
                    {   if (! nits.empty ())
                            ticks -> push_back (nits);
                        nits.reset ();
                        nits.set_context (line, ::std::string (bol, eol+1));
                        newline = true; }
                    ++line;
                    break;
                default :
                    if (ticks != nullptr)
                        if ((*i >= 32) || (! ::std::iscntrl (*i)))
                        {   if (newline)
                            {   newline = false;
                                bol = i; }
                            eol = i; }
                    break; }
        if ((cmt_state != cq_c) && (cmt_state != cq_cpp) && (cmt_state != cq_pos_c_end))
            switch (state)
            {   case uq_bs :
                    if (bst.find (*i) != ::std::string::npos) o += '\\';
                    o += *i;
                    if (os.size () > 0)
                    {   state = os.back (); os.pop_back (); }
                    else state = uq_dull;
                    continue;
                case uq_repsq :
                    if (*i == '\'')
                    {   o += *i;
                        state = uq_sq;
                        continue; }
                    if (os.size () > 0)
                    {   state = os.back ();
                        os.pop_back ();
                        if (state == uq_dull) state = uq_expect_sep; }
                    else state = uq_expect_sep;
                    break;
                case uq_repdq :
                    if (*i == '"')
                    {   o += *i;
                        state = uq_dq;
                        continue; }
                    if (os.size () > 0)
                    {   state = os.back ();
                        os.pop_back ();
                        if (state == uq_dull) state = uq_expect_sep; }
                    else state = uq_expect_sep;
                    break;
                case uq_expect_sep :
                    state = uq_es2;
                    break;
                case uq_es2 :
                    if (ticks != nullptr)
                    {   nits.set_context (line, sb, se, i);
                        nits.pick (nit_css_syntax, es_warning, ec_css, "separator expected after quoted string"); }
                    state = uq_dull;
                    break;
                default : break; }
        if ((flags & (UQ_C_CMT | UQ_CPP_CMT)) != 0)
        {   switch (*i)
            {   case '\n' :
                case '\v' :
                case '\r' :
                    ++line;
                    if (cmt_state == cq_cpp)
                    {   cmt_state = cq_dull;
                        continue; }
                    break;
                case '*' :
                    switch (cmt_state)
                    {   case cq_c :
                            cmt_state = cq_pos_c_end;
                            continue;
                        case cq_pos_cmt :
                            if ((flags & UQ_C_CMT) == UQ_C_CMT)
                            {   cmt_state = cq_c;
                                PRESUME (o.size () > 0, __FILE__, __LINE__);
                                o.pop_back ();
                                continue; }
                            cmt_state = cq_dull;
                            break;
                        case cq_cpp :
                            continue;
                        case cq_pos_c_end :
                            cmt_state = cq_c;
                            continue;
                        default :
                            break; }
                    break;
                case '/' :
                    switch (cmt_state)
                    {   case cq_pos_c_end :
                            cmt_state = cq_dull;
                            continue;
                        case cq_pos_cmt :
                            if ((flags & UQ_CPP_CMT) == UQ_CPP_CMT)
                            {   cmt_state = cq_cpp;
                                PRESUME (o.size () > 0, __FILE__, __LINE__);
                                o.pop_back ();
                                continue; }
                            cmt_state = cq_dull;
                            break;
                        case cq_dull :
                            cmt_state = cq_pos_cmt;
                            break;
                        case cq_c :
                        case cq_cpp :
                            continue;
                        default :
                            break; }
                    break;
                default :
                    switch (cmt_state)
                    {   case cq_pos_c_end :
                            cmt_state = cq_c;
                            continue;
                        case cq_pos_cmt :
                            cmt_state = cq_dull;
                            continue;
                        case cq_c :
                        case cq_cpp :
                            continue;
                        default :
                            break; }
                    break; } }
        switch (*i)
        {   case '\'' :
                if (state == uq_dq) break;
                consider = false;
                if (state == uq_sq)
                {   if ((flags & UQ_REPEATQ) == UQ_REPEATQ) state = uq_repsq;
                    else
                    {   is_q = true;
                        if (os.size () > 0)
                        {   state = os.back ();
                            os.pop_back ();
                            if (state == uq_dull) state = uq_expect_sep; }
                        else state = uq_expect_sep; } }
                else
                {   if ((flags & UQ_SQ) != UQ_SQ) break;
                    if (had_content) break;
                    is_q = true;
                    if (state >= breakage) break;
                    os.push_back (state);
                    state = uq_sq; }
                break;
            case '"' :
                if (state == uq_sq) break;
                consider = false;
                if (state == uq_dq)
                {   if ((flags & UQ_REPEATQ) == UQ_REPEATQ) state = uq_repdq;
                    {   is_q = true;
                        if (os.size () > 0)
                        {   state = os.back ();
                            os.pop_back ();
                            if (state == uq_dull) state = uq_expect_sep; }
                        else state = uq_expect_sep; } }
                else
                {   if ((flags & UQ_DQ) != UQ_DQ) break;
                    if (had_content) break;
                    is_q = true;
                    if (state >= breakage) break;
                    os.push_back (state);
                    state = uq_dq; }
                break;
            case '\\' :
                if ((flags & BS_MASK) == 0) break;
                os.push_back (state);
                state = uq_bs;
                consider = extend = false;
                break;
            case '(' :
                if (state >= breakage) break;
                if ((flags & UQ_ROUND) != UQ_ROUND) break;
                os.push_back (state);
                state = uq_bracket;
                ++ro;
                consider = false;
                break;
            case ')' :
                if (state != uq_bracket) break;
                if (ro > 0) consider = --ro == 0;
                if (os.size () > 0)
                {   state = os.back (); os.pop_back (); }
                else state = uq_dull;
                break;
            case '[' :
                if (state >= breakage) break;
                if ((flags & UQ_SQUARE) != UQ_SQUARE) break;
                os.push_back (state);
                state = uq_bracket;
                ++sq;
                consider = false;
                break;
            case ']' :
                if (state != uq_bracket) break;
                if (sq > 0) consider = --sq == 0;
                if (os.size () > 0)
                {   state = os.back (); os.pop_back (); }
                else state = uq_dull;
                break;
            case '{' :
                if (state >= breakage) break;
                if ((flags & UQ_BRACE) != UQ_BRACE) break;
                os.push_back (state);
                state = uq_bracket;
                ++br;
                consider = false;
                break;
            case '}' :
                if (state != uq_bracket) break;
                if (br > 0) consider = --br == 0;
                if (os.size () > 0)
                {   state = os.back (); os.pop_back (); }
                else state = uq_dull;
                break;
            case '<' :
                if (state >= breakage) break;
                if ((flags & UQ_ANGULAR) != UQ_ANGULAR) break;
                os.push_back (state);
                state = uq_bracket;
                ++an;
                consider = false;
                break;
            case '>' :
                if (state != uq_bracket) break;
                if (an > 0) consider = --an == 0;
                if (os.size () > 0)
                {   state = os.back (); os.pop_back (); }
                else state = uq_dull;
                break;
            default : break; }
        if (consider && (state != uq_bracket))
            for (auto p : sep)
                if (p.at (0) == *i)
                    if (GSL_NARROW_CAST < ::std::size_t > (se - i) >= p.length ())
                    {   bool matches = true;
                        for (auto n = 0; matches && (static_cast < ::std::size_t > (n) < p.length ()); ++n)
                            if (p.at (n) != ' ') matches = p.at (n) == *(i + n);
                            else matches = ::std::iswspace (*(i + n));   
                        if (matches)
                        {   if ((flags & UQ_TRIM) != UQ_TRIM) pushpush (res, lines, o, line); 
                            else pushpush (res, lines, trim_the_lot_off (o), line);
                            if ((flags & UQ_SEP) == UQ_SEP)
                                if (((flags & UQ_UNIFY) == 0) || (res.size () == 0) || (res.at (res.size () - 1) != p))
                                    pushpush (res, lines, p, line);
                            o.clear ();
                            extend = had_content = false;
                            break; } }
        if (extend)
        {   if ((flags & UQ_UNIFY) == UQ_UNIFY)
                switch (state)
                {   case uq_sq :
                    case uq_dq :
                    case uq_bs :
                        break;
                    default :
                        if (::std::iswspace (*i))
                        {   if (! had_whitespace)
                            {   had_whitespace = true;
                                o += ' '; }
                            continue; }
                        had_whitespace = false;
                        break; }
            if (! is_q)
            {   o += *i;
                if (! ::std::iswspace (*i))
                    had_content = true; } } }
    if (cmt_state == cq_c)
        if (ticks != nullptr)
        {   nits.set_context (line, sb, se, se);
            nits.pick (nit_css_syntax, es_warning, ec_css, "unfinished comment"); }
    switch (state)
    {   case uq_bs :
            if (ticks != nullptr)
            {   nits.set_context (line, sb, se, se);
                nits.pick (nit_css_syntax, es_warning, ec_css, "cannot backslash end of string"); }
            o += '\\';
            break;
        case uq_repsq :
            o += '\'';
            FALLTHROUGH;
        case uq_sq :
            if (ticks != nullptr)
            {   nits.set_context (line, sb, se, se);
                nits.pick (nit_css_syntax, es_warning, ec_css, "missing close quote"); }
            break;
        case uq_repdq :
            o += '\'';
            FALLTHROUGH;
        case uq_dq :
            if (ticks != nullptr)
            {   nits.set_context (line, sb, se, se);
                nits.pick (nit_css_syntax, es_warning, ec_css, "missing close double quote"); }
            break;
        case uq_bracket :
            if (ticks != nullptr)
            {   nits.set_context (line, sb, se, se);
                nits.pick (nit_css_syntax, es_warning, ec_css, "mismatched brackets"); }
            break;
        default :
            break; }
    if ((! o.empty ()) || (state != uq_dull))
        if ((flags & UQ_TRIM) == UQ_TRIM) pushpush (res, lines, trim_the_lot_off (o), line);
        else pushpush (res, lines, o, line);
    if (! nits.empty ())
        ticks -> emplace_back (nits); 
    return res; }                
