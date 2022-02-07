/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "parser/text.h"
#include "parser/text-data.h"
#include "feedback/nitpick.h"
#include "icu/lingo.h"
#include "icu/converter.h"

typedef ssc_map < ::std::string, ::std::size_t > vw_t;
vw_t wotsit, inverted_wotsit;
ustr_t symbol_code, code_symbol, extras;
::std::size_t wotsit_count = 0;

void extra_wotsit (nitpick& nits, const char* s, const char* c);
void known_wotsit (nitpick& nits, const char* s, const char* c, const bool suggest);

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26482) // Suggested solution breaks the compilation, plus ::std::array can't be length initialised by the initialiser
#endif // _MSC_VER
void wotsit_init (nitpick& nits)
{   for (wotsit_count = 0; wotsit_table [wotsit_count].wotsit_ != nullptr; ++wotsit_count)
    {   ::std::string w (normalise_utf8 (nits, wotsit_table [wotsit_count].wotsit_));
        if (wotsit.find (w) != wotsit.end ())
            nits.pick (nit_symbol_aleady_defined, es_error, ec_program, "Program error: wotsit ", w, " already defined");
        else wotsit.insert (vw_t::value_type (w, wotsit_count)); }
    for (int i = 0; known_symbols [i].symbol_ != nullptr; ++i)
        known_wotsit (nits, known_symbols [i].symbol_, known_symbols [i].code_, known_symbols [i].suggest_);
    for (int i = 0; xtra [i].symbol_ != nullptr; ++i)
        extra_wotsit (nits, xtra [i].symbol_, xtra [i].code_); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

void extra_wotsit (nitpick& nits, const char* s, const char* c)
{   ::std::string sym (normalise_utf8 (nits, s));
    ::std::string cod (normalise_utf8 (nits, c));
    auto sc = extras.find (cod);
    if (sc == extras.cend ()) extras.insert (ustr_t::value_type (cod, sym)); }

void known_wotsit (nitpick& nits, const char* s, const char* c, const bool suggest)
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    VERIFY_NOT_NULL (c, __FILE__, __LINE__);
    ::std::string sym (normalise_utf8 (nits, s));
    ::std::string cod (normalise_utf8 (nits, c));
    if (suggest)
    {
#ifdef DEBUG
        if ((sym.length () == 1) && (*s < 127) && (*s >= ' '))
            switch (*s)
            {   case '<' :
                case '>' :
                case '&' :
                case '`' :
                    break;
                default :
                    ::std::cerr << "Character " << sym << " (&" << cod << ";) is suggested.\n";
                    break; }
#endif // DEBUG
        auto sc = symbol_code.find (s);
        if (sc == symbol_code.cend ()) symbol_code.insert (ustr_t::value_type (sym, cod)); }
    auto cs = code_symbol.find (c);
    if (cs == code_symbol.cend ()) code_symbol.insert (ustr_t::value_type (cod, sym));
    auto ws = wotsit.find (s);
    if (ws != wotsit.cend ())
    {   auto iw = inverted_wotsit.find (c);
        if (iw == inverted_wotsit.cend ())
            inverted_wotsit.insert (vw_t::value_type (::std::string (c), ws -> second)); } }

void text_check (nitpick& nits, const html_version& v, const ::std::string& text)
{   nits.set_context (0, text);
    if (context.tell (e_error))
    {   char after = text.at (0);
        const ::std::string::size_type equal = text.find ('=', 1);
        if (equal != ::std::string::npos) return; // probably an HREF param that hasn't been normalised
        if (text.length () > max_wotsit_len + 1)
        {   nits.pick (nit_bizarre_character_code, es_error, ec_parser, "&", text, "; is neither a known text entity nor a normalised URL");
            return; }
        if (v.is_2_or_more ())
        {   if (::std::string (ALPHABET HASHES).find (after) == ::std::string::npos) return;
            if (after == HASH)
            {   if (text.length () == 1)
                    nits.pick (nit_empty_denary_code, es_warning, ec_parser, "empty numeric character code");
                else
                {   after = text.at (1);
                    if ((after == 'x') || (after == 'X'))
                    {   if (text.length () == 2)
                            nits.pick (nit_empty_hex_code, es_warning, ec_parser, "empty hex character code");
                        else
                        {   after = text.at (2);
                            if (text.length () > 8)
                                nits.pick (nit_hex_too_long, es_warning, ec_parser, "hex character code too long");
                            else if (::std::string (HEX).find_first_of (after) == ::std::string::npos)
                                nits.pick (nit_dubious_denary, es_warning, ec_parser, "dubious hex character code");
                            else if (text.substr (2).find_first_not_of (HEX) != ::std::string::npos)
                                nits.pick (nit_invalid_denary, es_warning, ec_parser, "invalid hex character code"); } }
                    else if (text.length () > 7)
                        nits.pick (nit_denary_too_long, es_warning, ec_parser, "denary character code too long");
                    else if (::std::string (DENARY).find_first_of (after) == ::std::string::npos)
                        nits.pick (nit_dubious_denary, es_warning, ec_parser, " dubious denary character code");
                    else if (text.substr (1).find_first_not_of (DENARY) != ::std::string::npos)
                        nits.pick (nit_invalid_denary, es_warning, ec_parser, "invalid denary character code"); }
                return; } }
        vw_t::const_iterator i = wotsit.find (text.c_str ());
        if (i == wotsit.end ())
            nits.pick (nit_bizarre_character_code, es_error, ec_parser, "&", text, "; is neither a known text entity nor a normalised URL");
        else
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26482) // Suggested solution breaks the compilation, plus ::std::array can't be length initialised by the initiliser
#endif // _MSC_VER
        {   PRESUME (i -> second < wotsit_count, __FILE__, __LINE__);
            if (! does_apply < html_version > (v, wotsit_table [i -> second].first_, wotsit_table [i -> second].last_))
                nits.pick (nit_code_unrecognised_here, es_warning, ec_parser, "&", text, "; is invalid in ", v.report ());
            else if (v.is_5 () && v.xhtml () && ! v.xhtml_dtd ())
                if ((wotsit_table [i -> second].flags_ & WOTSIT_XML) != WOTSIT_XML)
                    nits.pick (nit_code_dtd, ed_jul21, "14.1 Writing documents in the XML syntax", es_error, ec_parser, "to be valid, &", text, "; requires an appropriate DTD in <!DOCTYPE ...> in ", v.report ()); } } }

void examine_character_code (const html_version& v, const ::std::string& text, bool& known, bool& invalid)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    vw_t::const_iterator i = wotsit.find (text);
    if (i != wotsit.end ())
    {   PRESUME (i -> second < wotsit_count, __FILE__, __LINE__);
        if (! may_apply (v, wotsit_table [i -> second].first_, wotsit_table [i -> second].last_)) invalid = true;
        else known = true; } }

::std::string interpret_character_code (const html_version& v, const ::std::string& text, bool& known, bool& invalid, const bool simplify)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    vw_t::const_iterator i = wotsit.find (text);
    if (i != wotsit.cend ())
    {   PRESUME (i -> second < wotsit_count, __FILE__, __LINE__);
        if (! may_apply (v, wotsit_table [i -> second].first_, wotsit_table [i -> second].last_)) invalid = true;
        else
        {   known = true;
            if (simplify && (wotsit_table [i -> second].simple_ != nullptr))
                return wotsit_table [i -> second].simple_;
            auto ci = code_symbol.find (wotsit_table [i -> second].wotsit_);
            if (ci != code_symbol.cend ()) return ci -> second; } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
   ::std::string res ("&");
    res += text + ';';
    return res; }

::std::string interpret_character_code (const html_version& v, const ::std::string& text, const bool simplify)
{   bool invalid = false;
    bool known = false;
    return interpret_character_code (v, text, known, invalid, simplify); }

::std::string interpret_character_code (nitpick& nits, const html_version& v, const ::std::string& text, const bool simplify)
{   bool invalid = false;
    bool known = false;
    ::std::string res (interpret_character_code (v, text, known, invalid, simplify));
    if (invalid)
        nits.pick (nit_invalid_character_code, es_error, ec_parser, res, " is invalid in ", v.report ());
    else if (! known)
        nits.pick (nit_invalid_character_code, es_error, ec_parser, res, " is unrecognised");
    return res; }

::std::string interpret_character_number (const ::std::string& text)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    unsigned int n = 0;
    for (auto ch : text)
    {   n *= 10;
        if ((ch >= '0') && (ch <= '9')) n += ch - '0';
        else return text;
        if (n > UINT_MAX / 4) return text; }
    return ::std::string (1, ::gsl::narrow_cast <char> (n)); }

bool is_naughty_number (nitpick& nits, const ::std::string& s, const int n)
{   if (n < 32)
        nits.pick (nit_not_iso_8859_1, ed_iso_8859_1, "https://en.wikipedia.org/wiki/ISO/IEC_8859-1", es_warning, ec_parser, quote (s), " is a control character");
    else if ((n >= 127) && (n <= 159))
        nits.pick (nit_not_iso_8859_1, ed_iso_8859_1, "https://en.wikipedia.org/wiki/ISO/IEC_8859-1", es_warning, ec_parser, quote (s), " is an invalid character code");
    else if ((n == 65534) || (n == 65535))
        nits.pick (nit_not_iso_8859_1, ed_41, "24.2 Character entity references for ISO 8859-1 characters", es_warning, ec_parser, quote (s), " is invalid");
    else return false;
    return true; }

::std::string interpret_character_number (nitpick& nits, const ::std::string& text)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    unsigned int n = 0;
    ::std::string res = "&#";
    res += text;
    res += ';';
    for (auto ch : text)
    {   n *= 10;
        if ((ch >= '0') && (ch <= '9')) n += ch - '0';
        else
        {   nits.pick (nit_invalid_character_denary, ed_41, "24.2 Character entity references for ISO 8859-1 characters", es_error, ec_parser, quote (res), " is not a denary integer");
            return res; }
        if (n > UINT_MAX / 4)
        {   nits.pick (nit_denary_too_long, ed_41, "24.2 Character entity references for ISO 8859-1 characters", es_error, ec_parser, text, " is too big");
            return res; } }
    if (is_naughty_number (nits, res, n)) return res;
    return ::std::string (1, ::gsl::narrow_cast <char> (n)); }

::std::string interpret_character_hex (const ::std::string& text)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    unsigned int n = 0;
    for (auto ch : text)
    {   n <<= 4;
        if ((ch >= '0') && (ch <= '9')) n += ch - '0';
        else if ((ch >= 'A') && (ch <= 'F')) n += ch - 'A' + 10;
        else if ((ch >= 'a') && (ch <= 'f')) n += ch - 'a' + 10;
        else return text;
        if (n > UINT_MAX / 4) return text; }
    return ::std::string (1, ::gsl::narrow_cast <char> (n)); }

::std::string interpret_character_hex (nitpick& nits, const ::std::string& text)
{   PRESUME (! text.empty (), __FILE__, __LINE__);
    ::std::string res = "&#x";
    res += text;
    res += ';';
    unsigned int n = 0;
    for (auto ch : text)
    {   n <<= 4;
        if ((ch >= '0') && (ch <= '9')) n += ch - '0';
        else if ((ch >= 'A') && (ch <= 'F')) n += ch - 'A' + 10;
        else if ((ch >= 'a') && (ch <= 'f')) n += ch - 'a' + 10;
        else
        {   nits.pick (nit_invalid_character_hex, es_error, ec_parser, quote (res), " is not a hexadecimal integer");
            return res; }
        if (n > UINT_MAX / 4)
        {   nits.pick (nit_hex_too_long, es_error, ec_parser, text, " is too big");
            break; } }
    if (is_naughty_number (nits, res, n)) return res;
    return ::std::string (1, ::gsl::narrow_cast <char> (n)); }

::std::string get_character_code (const ::std::string& text)
{   auto ci = symbol_code.find (text);
    if (ci != symbol_code.end ()) return ci -> second;
    return ::std::string (); }

::std::string get_extra (const ::std::string& text)
{   auto ci = extras.find (text);
    if (ci != extras.end ()) return get_character_code (ci -> second);
    return ::std::string (); }

::std::string enwotsit (const ::std::string& s)
{   ::std::string res;
    for (::std::string::const_iterator i = s.cbegin (); i != s.cend (); ++i)
    {   switch (*i)
        {   case ' ' :
                res += *i;
                continue;
            default :
                break; }
        auto ci = symbol_code.find (::std::string (1, *i));
        if (ci == symbol_code.end ())
            res += *i;
        else
        {   res += "&";
            res += ci -> second;
            res += ";"; } }
    return res; }

::std::string interpret_string (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string res;
    ::std::string special;
    bool code = false, bs = false;
    for (::std::string::const_iterator i = s.cbegin (); i != s.cend (); ++i)
        switch (*i)
        {   case '&' :
                if (bs) { bs = false; res += '&'; }
                else code = true;
                break;
            case '\\' :
                if (bs) { bs = false; res += '\\'; }
                else bs = true;
                break;
            case ';' :
                if (! code) res += ';';
                else if (bs) { bs = false; special += ';'; }
                else if (! special.empty ())
                {   ::std::string got;
                    if (special.front () != '#') got = interpret_character_code (nits, v, special, true);
                    else if ((special.length () > 1) && (special.at (1) == 'x')) got = interpret_character_hex (nits, special.substr (2));
                    else got = interpret_character_number (nits, special.substr (1));
                    if (got.empty ()) { res += '&'; res += special; res += ';'; }
                    else res += got;
                    special.clear ();
                    code = false; }
                break;
            default :
                bs = false;
                if (code) special += *i;
                else res += *i;
                break; }
    return res; }
