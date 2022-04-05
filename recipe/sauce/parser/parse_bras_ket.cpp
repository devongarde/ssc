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
#include "parser/parse_bras_ket.h"
#include "parser/text.h"
#include "parser/xhtml_xml.h"

typedef enum
{   s_start, // when starting
    s_dull,
    s_startopen, //  < at beginning of file
    s_open, // < elsewhere
    s_element_quote, // '
    s_element_double_quote, // "
    s_grammar_quote, // '   (in grammar)
    s_grammar_double_quote, // "    (in grammar)
    s_php_quote, // '    (in php)
    s_php_double_quote, // "    (in php)
    s_xml_quote, // '    (in xml)
    s_xml_double_quote, // "    (in xml)
    s_q_quote, // '    (in neither php nor xml)
    s_q_double_quote, // "    (in neither php nor xml)
    s_asp_quote, // '    (in asp)
    s_asp_double_quote, // "    (in asp)
    s_ssi_quote, // '    (in ssi)
    s_ssi_double_quote, // "    (in ssi)
    s_pxq, // php, xml, or something else
    s_php, // in insecure mode
    s_x,
    s_q, // neither php nor xml
    s_asp, // in insecure mode
    s_ssi, // in slow mode
    s_php_closing, // ? maybe ?>
    s_xml_closing, // ? maybe ?>
    s_q_closing, // ? maybe ?>
    s_asp_closing, // % maybe %>
    s_slash, // </
    s_startbang, // <! at beginning of file
    s_bang, // <! elsewhere
    s_bangsquare, // <![ ...
    s_cdata, // <![CDATA[ ...
    s_comment_first_open, // <!-
    s_comment_second_open, // <!--
    s_comment, // <!-- & not a hash
    s_comment_first_close, // -   (in comment/longwinded)
    s_comment_second_close, // --  (in comment/longwinded)
    s_ssi_first_close, // -   (in ssi)
    s_ssi_second_close, // --  (in ssi)
    s_bq_first_close, // ] (in bangsquare)
    s_bq_second_close, // ]] (in bangsquare)
    s_amper, // &
    s_hash, // &#
    s_symbol, // collecting character symbol
    s_num, // collecting denary character number
    s_hex, // collecting hex character number
    s_element, // collecting element name
    s_inside, // expecting an attribute
    s_purgatory, // < ... /   here
    s_grammar,  // <! letter
    s_grsq  // <! ... [
} e_statemachine;

void bras_ket::nodoctype (nitpick& nits, html_version& v, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i)
{   if (! v.unknown ()) return;
    nits.set_context (line_, b, e, i);
    if (context.presume_tags ())
    {   v.reset (html_tags);
        nits.pick (nit_presume_html_tags, ed_tags, "", es_warning, ec_parser, "No <!DOCTYPE ... > found at beginning of content; presuming HTML Tags"); }
    else
    {   v.reset (html_1);
        nits.pick (nit_presume_html_1, ed_1, "", es_warning, ec_parser, "No <!DOCTYPE ... > found at beginning of content; presuming HTML 1.0"); } }

void bras_ket::mixed_mess (nitpick& nits, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const char* item, const char* inside)
{   PRESUME (item != nullptr, __FILE__, __LINE__);
    PRESUME (inside != nullptr, __FILE__, __LINE__);
    nits.set_context (line_, b, e, i);
    nits.pick (nit_mixed_mess, es_warning, ec_parser, item, " starts inside ", inside); }

e_statemachine ket_quote (nitpick& nits, char ch, const e_statemachine status, const e_statemachine new_state, const char qu, const bool newline, bool& backslashed)
{   if (newline) nits.pick (nit_newline_in_string, es_warning, ec_parser, "end of line in string");
    if (backslashed) backslashed = false;
    else if (ch == '\\') backslashed = true;
    else if (ch == qu) return new_state;
    return status; }

void faux_xmp_check (bra_element_ket& current, e_element& xmp_tag, bool& xmp_mode, const ::std::string::const_iterator& i, ::std::string::const_iterator& x)
{   e_element ee = current.suspender ();
    if (ee != elem_undefined)
    {   xmp_tag = ee;
        xmp_mode = true;
        x = i + 1; } }

void check_character (nitpick& nits, const html_version& v, const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   if (v >= html_4_0)
    {   switch (*i)
        {   case '\'' :
                nits.pick (nit_use_quote_code, ed_4, "24 Character entity references in HTML 4.0", es_info, ec_parser, "consider using character codes for single quotes / apostrophes (e.g. '&lsquo;', '&rsquo;', etc.)");
                return;
            case '"' :
                nits.pick (nit_use_double_quote_code, ed_4, "24 Character entity references in HTML 4.0", es_info, ec_parser, "consider using character codes for double quotes (e.g. '&ldquo;', '&rdquo;', etc.)");
                return;
            case '`' :
                if (v >= html_jul10)
                {   nits.pick (nit_naughty_grave, ed_jul10, "1.11.2 Syntax errors", es_info, ec_parser, "a grave accent is better encoded (e.g. '&grave;') or quoted"); return; }
                break;
            default :
                {   ::std::string cc = get_character_code (::std::string (1, *i));
                    if (! cc.empty ())
                    {   if (isprint (*i) && (*i < 127))
                            nits.pick (nit_character_code, ed_4, "24 Character entity references in HTML 4.0", es_comment, ec_parser, "consider using '&", cc, ";' instead of '", *i, "'");
                        else nits.pick (nit_character_code, ed_4, "24 Character entity references in HTML 4.0", es_comment, ec_parser, "consider using '&", cc, ";'");
                        return; } } }
        // presumes i will be incremented by the caller
        if (e - i > 2)
        {   ::std::string t (i, i + 3);
            ::std::string cc = get_extra (t);
            if (! cc.empty ())
            {   nits.pick (nit_character_code, ed_4, "24 Character entity references in HTML 4.0", es_comment, ec_parser, "consider using '&", cc, ";' instead of '", t, "'");
                ++i; ++i;
                return; } }
        if (e - i > 1)
        {   ::std::string t (i, i + 2);
            ::std::string cc = get_extra (t);
            if (! cc.empty ())
            {   nits.pick (nit_character_code, ed_4, "24 Character entity references in HTML 4.0", es_comment, ec_parser, "consider using '&", cc, ";' instead of '", t, "'");
                ++i;
                return; } }
        if (static_cast < unsigned int > (*i) > 127)
            nits.pick (nit_encode, ed_jan21, "13.5 Named character references", es_comment, ec_parser, "consider using named character references for non-ASCII characters"); } }

// this parser is horrid, and, worse, it works
html_version bras_ket::parse (const ::std::string& content)
{   html_version res;
    e_statemachine status = s_start;
    ::std::string linelog;
    const ::std::string::const_iterator b = content.begin ();
    const ::std::string::const_iterator e = content.end ();
    ::std::string::const_iterator collect = b, eofe = b, x = b;
    ::std::string::const_iterator text = b;
    ::std::string::const_iterator twas = b;
    ::std::string::const_iterator soe = b;
    ::std::string::const_iterator i = b;
    ::std::string::const_iterator bol = e;
    constexpr ::std::size_t ket_alloc = 8192;
    ::std::size_t ket_reserve = ket_alloc;
    ::std::size_t ll = 0;
    bool ll_warned = false;
    ve_.clear ();
    ve_.reserve (ket_reserve);
    bool doubleopen = false;
    bool php_warn = false;
    bool asp_warn = false;
    bool ssi_warn = false;
    bool closure = false;
    bool xmp_mode = false;
    bool plaintext = false;
    bool had_doctype = false;
    bool backslashed = false;
    bool aftercab = false;
    bool silent_content = false;
    bool comment_start = false;
    bool doubledashed = false;
    e_element xmp_tag = elem_undefined;
    const char* cc = "character code";
    const char* ccnu = "character code, or a character code has not been used";
    const char* elmt = "element";
    const char* sg = "SGML";
    const char* occ = "one character code";
    const char* oel = "one element";
    const char* ano = "another";
    nitpick nits;
    line_ = 1;
    for (i = b; (i != e) && (! plaintext); ++i)
    {   if (ve_.size () >= ket_reserve - 16)
        {   ket_reserve += ket_alloc;
            ve_.reserve (ket_reserve); }
        auto ch = *i;
        if (backslashed)
        {   switch (ch)
            {   case '\v' :
                    if (context.tell (es_all)) linelog += "v";
                    ++line_; ll = 0; bol = e;
                    break;
                case '\n' :
                    if (context.tell (es_all)) linelog += "n";
                    ++line_; ll = 0; bol = e;
                    break;
                case '\f' :
                    if (context.tell (es_all)) linelog += "f";
                    ++line_; ll = 0; bol = e;
                    break;
                case '\r' :
                    if (context.tell (es_all)) linelog += "r";
                    ll = 0; bol = e;
                    break;
                default :
                    break; }
            backslashed = false;
            continue; }
        bool newline = false;
        switch (ch)
        {   case '\\' :
                if (silent_content) backslashed = true;
                continue;
            case '\'' :
                if (i + 1 < e)
                    if (*(i+1) == '\'')
                    {   ++i; continue; }
                break;
            case '"' :
                if (i + 1 < e)
                    if (*(i+1) == '"')
                    {   ++i; continue; }
                break;
            case '\v' :
                if (context.tell (es_all)) linelog += "v";
                ++line_; newline = true;
                ll = 0; bol = e; ch = ' ';
                break;
            case '\n' :
                if (context.tell (es_all)) linelog += "n";
                ++line_; newline = true;
                ll = 0; bol = e; ch = ' ';
                break;
            case '\f' :
                if (context.tell (es_all)) linelog += "f";
                ++line_; newline = true;
                ll = 0; bol = e; ch = ' ';
                break;
            case '\r' :
                if (context.tell (es_all)) linelog += "r";
                ll = 0; bol = e; ch = ' ';
                break;
            case '\t' :
                ch = ' ';
                break;
            default :
                break; }
         if (context.tell (es_all) && (linelog.length () > 60))
        {   nits.pick (nit_all, es_all, ec_parser, "\\\\ ", linelog);
            linelog.clear (); }
        ++ll;
        if ((ll > 254) && (res.mjr () < 4) && (! ll_warned))
        {   nits.pick (nit_mosaic_crash, es_warning, ec_parser, "long lines crash older versions of MOSAIC");
            ll_warned = true; }
        if (::std::iswcntrl (ch)) { aftercab = false; continue; }
        if (::std::iswspace (ch)) ch = ' ';
        if (aftercab && (ch != '>')) aftercab = false;
        if (bol == e) bol = i;
        ::std::string s;
        switch (status)
        {   case s_start :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_start ", ch);
                switch (ch)
                {   case '<' :  status = s_startopen; soe = twas = i; break;
                    case ' ' :  break;
                    case '&' :  nodoctype (nits, res, b, e, i);
                                status = s_amper; break;
                    default :   nodoctype (nits, res, b, e, i);
                                status = s_dull; }
                break;
            case s_startopen :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_startopen ", ch);
                switch (ch)
                {   case '<' :  if (! doubleopen)
                                {   doubleopen = true; soe = twas = i;
                                    nits.set_context (line_, b, e, i);
                                    nits.pick (nit_double_angular_open, es_warning, ec_parser, "is '<<' intentional?"); }
                                break;
                    case ' ' :  break;
                    case '!' :  doubleopen = false; status = s_startbang; break;
                    case '/' :  nodoctype (nits, res, b, e, i);
                                doubleopen = false; status = s_slash; break;
                    case '?' :  doubleopen = false; status = s_pxq; collect = i; break;
                    case ':' :  nodoctype (nits, res, b, e, i);
                                doubleopen = false; status = s_asp; collect = i; break;
                    case '&' :  nodoctype (nits, res, b, e, i);
                                mixed_mess (nits, b, e, i, cc, elmt);
                                doubleopen = false; status = s_amper; twas = i; collect = i; break;
                    default :   doubleopen = false; nodoctype (nits, res, b, e, i);
                                if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || (ch == '/'))
                                {   status = s_element; collect = i; closure = false; }
                                else status = s_dull; }
                break;
            case s_startbang :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_startbang ", ch);
                switch (ch)
                {   case '-' :  // nodoctype (nits, res, b, e, i);
                                nits.set_context (line_, b, e, i);
                                status = s_comment_first_open; comment_start = true; break;
                    case '<' :  nodoctype (nits, res, b, e, i);
                                mixed_mess (nits, b, e, i, elmt, sg);
                                soe = twas = i; status = s_open; break;
                    case '&' :  nodoctype (nits, res, b, e, i);
                                mixed_mess (nits, b, e, i, cc, sg);
                                status = s_amper; twas = i; break;
                    case '[' :  nodoctype (nits, res, b, e, i);
                                status = s_bangsquare; twas = i; break;
                    default :   if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')))
                                {   nodoctype (nits, res, b, e, i);
                                    twas = text; status = s_dull; }
                                else
                                {   status = s_grammar; collect = i; } }
                break;
            case s_grammar :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_grammar ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i+1);
                                if (parse_doctype (nits, res, collect, i))
                                {   had_doctype = true;
                                    ve_.emplace_back (nits, line_, bk_doctype, collect, i);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_doctype ", quoted_limited_string (::std::string (collect, i), 30)); }
                                else form_.merge (nits);
                                nits.reset ();
                                status = s_dull; twas = text = i+1; break;
                    case ' ' :  break;
                    case '[' :  status = s_grsq; break;
                    case '<' :  nodoctype (nits, res, b, e, i);
                                mixed_mess (nits, b, e, i, elmt, sg);
                                status = s_open; twas = soe = i; break;
                    case '&' :  nodoctype (nits, res, b, e, i);
                                mixed_mess (nits, b, e, i, cc, sg);
                                status = s_amper; twas = i; break;
                    case '\'' : status = s_grammar_quote; break;
                    case '"' :  status = s_grammar_double_quote; break;
                    default :   if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')))
                                {   status = s_start; twas = b; }
                                break; }
                break;
            case s_grsq :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_grsq ", ch);
                if (ch == ']') status = s_grammar; // no support for nesting, presumes no ] in strings
                break;
            case s_dull :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_dull ", ch);
                switch (ch)
                {   case '<' :  status = s_open; soe = twas = i; break;
                    case '>' : if (aftercab) if (! silent_content) nits.pick (nit_double_gin_and_tonic, es_info, ec_parser, "is that double '>' intentional?"); break;
                    case '&' :  if (! xmp_mode) { status= s_amper; twas = i; } break;
                    default : if (! xmp_mode && ! silent_content) check_character (nits, res, e, i); }
                break;
            case s_amper :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_amper ", ch);
                switch (ch)
                {   case '#' :  status = s_hash; break;
                    case ' ' :  break;
                    case '<' :  mixed_mess (nits, b, e, i, elmt, ccnu);
                                status = s_open; soe = twas = i; break;
                    case ';' :  nits.pick (nit_empty_character_code, es_info, ec_parser, "empty character code");
                                status = s_dull; break;
                    case '&' :  break;
                    default :   if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')))
                                {   status = s_symbol; collect = i; }
                                else
                                {   if (! xmp_mode && ! silent_content && (res >= html_4_0))
                                    {   nits.set_context (line_, b, e, bol, i+1);
                                        nits.pick (nit_lonely_ampersand, ed_4, "24 Character entity references in HTML 4.0", es_warning, ec_parser, "consider using character codes for ampersands (e.g. '&amp;')"); }
                                    status = s_dull; } }
                break;
            case s_hash :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_hash ", ch);
                switch (ch)
                {   case '<' :  mixed_mess (nits, b, e, i, elmt, ccnu);
                                status = s_open; soe = twas = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, occ, ano);
                                status = s_amper; twas = i; break;
                    case 'X' :  if (res.xhtml ())
                                {   nits.pick (nit_xhtml_hex_lc, ed_x1, "4.12. Entity references as hex value", es_warning, ec_parser, "in ", res.report (), ", hex character codes must start with lower-case 'x'");
                                    status = s_dull; break; }
                                [[fallthrough]];
                    case 'x' :  if (res < html_4_0)
                                {   nits.pick (nit_hex_code_version, ed_4, "5.3.1 Numeric character references", es_warning, ec_parser, "hex character codes require HTML 4.0 or later");
                                    status = s_dull; }
                                else
                                {   status = s_hex; collect = i; }
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
                    case '9' : status = s_num; collect = i; break;
                    default :  status = s_dull; }
                break;
            case s_symbol :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_symbol ", ch);
                switch (ch)
                {   case ';' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                nits.set_context (line_, b, e, i);
                                s = ::std::string (collect, i);
                                text_check (nits, res, s);
                                interpret_character_code (nits, res, s);
                                ve_.emplace_back (nits, line_, bk_code, collect, i);
                                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_code ", quoted_limited_string (s, 30));
                                nits.reset ();
                                status = s_dull; text = twas = i+1; break;
                    case '<' :  mixed_mess (nits, b, e, i, elmt, ccnu);
                                status = s_open; soe = twas = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, occ, ano);
                                status= s_amper; twas = i; break;
                    default :   if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')))
                                {   if (i - collect <= max_wotsit_len) break;
                                    if (! xmp_mode && ! silent_content && (res >= html_4_0))
                                    {   nits.set_context (line_, b, e, collect);
                                        nits.pick (nit_encode_ampersand, ed_4, "24 Character entity references in HTML 4.0", es_warning, ec_parser, "should that ampersand be '&amp;' ?"); } }
                                status = s_dull; break; }
                break;
            case s_num :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_num ", ch);
                switch (ch)
                {   case ';' :  if (res < html_1)
                                {   if (! xmp_mode && ! silent_content)
                                    {   nits.set_context (line_, b, e, i);
                                        nits.pick (nit_invalid_character_code, ed_tags, "", es_error, ec_parser, "numeric characters codes are not part of HTML tags"); } }
                                else
                                {   if (twas > text)
                                    {   nits.set_context (line_, b, e, text, twas);
                                        ve_.emplace_back (nits, line_, text, twas);
                                        if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                        nits.reset (); }
                                    nits.set_context (line_, b, e, i);
                                    text_check (nits, res, ::std::string (collect-1, i));
                                    s = ::std::string (collect, i);
                                    interpret_character_number (nits, s);
                                    ve_.emplace_back (nits, line_, bk_num, collect, i);
                                        if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_num ", quoted_limited_string (s, 30));
                                    nits.reset (); }
                                status = s_dull; text = twas = i+1; break;
                    case '<' :  mixed_mess (nits, b, e, i, elmt, ccnu); status = s_open; soe = twas = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, occ, ano); status = s_amper; twas = i; break;
                    case '0' :
                    case '1' :
                    case '2' :
                    case '3' :
                    case '4' :
                    case '5' :
                    case '6' :
                    case '7' :
                    case '8' :
                    case '9' : break;
                    default :  status = s_dull; }
                break;
            case s_hex :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_hex ", ch);
                switch (ch)
                {   case ';' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                nits.set_context (line_, b, e, i);
                                text_check (nits, res, ::std::string (collect-1, i));
                                s = ::std::string (++collect, i);
                                interpret_character_hex (nits, s);
                                ve_.emplace_back (nits, line_, bk_num, collect, i);
                                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_num ", quoted_limited_string (s, 30));
                                nits.reset ();
                                status = s_dull; text = twas = i+1; break;
                    case '<' :  mixed_mess (nits, b, e, i, elmt, ccnu); status = s_open; soe = twas = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, occ, ano); status = s_amper; twas = i; break;
                    case 'A' :
                    case 'B' :
                    case 'C' :
                    case 'D' :
                    case 'E' :
                    case 'F' :
                    case 'a' :
                    case 'b' :
                    case 'c' :
                    case 'd' :
                    case 'e' :
                    case 'f' :
                    case '0' :
                    case '1' :
                    case '2' :
                    case '3' :
                    case '4' :
                    case '5' :
                    case '6' :
                    case '7' :
                    case '8' :
                    case '9' : break;
                    default :  status = s_dull; }
                break;
            case s_open :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_open ", ch, " (xmp:", xmp_mode, ")");
                if (xmp_mode && (ch != '/')) { status = s_dull; break; }
                switch (ch)
                {   case '<' :  if (! doubleopen)
                                {   doubleopen = true; twas = soe = i;
                                    nits.set_context (line_, b, e, i);
                                    nits.pick (nit_double_angular_open, es_warning, ec_parser, "is '<<' intentional?"); }
                                break;
                    case ' ' :  break;
                    case '!' :  doubleopen = false; status = s_bang; break;
                    case '/' :  doubleopen = false; status = s_slash; break;
                    case '?' :  doubleopen = false; status = s_pxq; collect = i; break;
                    case '%' :  if (! asp_warn)
                                {   nits.set_context (line_, b, e, i);
                                    nits.pick (nit_embedded_lingo, es_info, ec_parser, PROG " is a *STATIC* site checker, it does not understand ASP"); }
                                doubleopen = false; asp_warn = true; status = s_asp; collect = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, cc, elmt);
                                status= s_amper; twas = i; break;
                    default :   if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || (ch == '/'))
                                {   status = s_element; collect = i; closure = false; }
                                else
                                {   status = s_dull; twas = text; }
                                doubleopen = false; }
                break;
            case s_slash :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_slash ", ch);
                switch (ch)
                {   case '<' :  if (! xmp_mode) mixed_mess (nits, b, e, i, oel, ano);
                                status= s_open; soe = twas = i; break;
                    case ' ' :  break;
                    case '/' :  if (xmp_mode) { status= s_dull; break; }
                                nits.set_context (line_, b, e, i);
                                nits.pick (nit_double_slash, es_info, ec_parser, "is '//' intentional?");
                                status= s_dull; twas = text; break;
                    case '&' :  if (xmp_mode) { status= s_dull; break; }
                                status = s_amper; twas = i; break;
                    default :   if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')))
                                {   status = s_element; collect = i; closure = true; }
                                else
                                {   status = s_dull; twas = text; } }
                break;
            case s_pxq :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_pxq ", ch);
                if (::std::iswspace (ch))
                {   if (collect+1 == i)
                    {   if (! had_doctype) nodoctype (nits, res, b, e, i);
                        if (! php_warn)
                        {   nits.set_context (line_, b, e, i);
                            nits.pick (nit_embedded_lingo, es_warning, ec_parser, "incorrectly presuming PHP; prefer <?php to <? --- also, " PROG " is a *STATIC* site checker, it does not understand PHP");
                            php_warn = true; }
                        status = s_php; }
                    else
                    {   ::std::string wot (::std::string (collect+1, i)); // yay captain sensible
                        if (compare_no_case (wot, "php"))
                        {   if (! had_doctype) nodoctype (nits, res, b, e, i);
                            if (! php_warn)
                            {   nits.set_context (line_, b, e, i);
                                nits.pick (nit_embedded_lingo, es_info, ec_parser, PROG " is a *STATIC* site checker, it does not understand PHP");
                                php_warn = true; }
                            status = s_php; }
                        else if (compare_no_case (wot, "xml")) status = s_x;
                        else { status = s_q; twas = text; } } }
                else if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')))
                {   status = s_q; twas = text; }
                break;
            case s_php :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_php ", ch);
                switch (ch)
                {   case '?' :  status = s_php_closing; break;
                    case '"' :  status = s_php_double_quote; break;
                    case '\'' : status = s_php_quote; break;
                    default : break; }
                break;
            case s_x :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_x ", ch);
                switch (ch)
                {   case '?' :  status = s_xml_closing; break;
                    case '"' :  status = s_xml_double_quote; break;
                    case '\'' : status = s_xml_quote; break;
                    default : break; }
                break;
            case s_q :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_q ", ch);
                switch (ch)
                {   case '?' :  status = s_q_closing; break;
                    case '"' :  status = s_q_double_quote; break;
                    case '\'' : status = s_q_quote; break;
                    default : break; }
                break;
            case s_asp :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_asp ", ch);
                switch (ch)
                {   case '%' :  status = s_asp_closing; break;
                    case '"' :  status = s_asp_double_quote; break;
                    case '\'' : status = s_asp_quote; break;
                    default : break; }
                break;
            case s_ssi :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_ssi ", ch);
                switch (ch)
                {   case '-' :  status = s_ssi_first_close; break;
                    case '"' :  status = s_ssi_double_quote; break;
                    case '\'' : status = s_ssi_quote; break;
                    default : break; }
                break;
            case s_ssi_first_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_ssi_first_close ", ch);
                switch (ch)
                {   case '-' :  status = s_ssi_second_close; break;
                    case '"' :  status = s_ssi_double_quote; break;
                    case '\'' : status = s_ssi_quote; break;
                    default :   status = s_ssi; break; }
                break;
            case s_ssi_second_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_ssi_second_close ", ch);
                switch (ch)
                {   case '>' :  if (twas > text) ve_.emplace_back (nits, line_, text, twas);
                                ve_.emplace_back (nits, line_, bk_ssi, collect, i-1);
                                nits.reset ();
                                aftercab = true;
                                status = s_dull; text = twas = i+1; break;
                    case '"' :  status = s_ssi_double_quote; break;
                    case '\'' : status = s_ssi_quote; break;
                    default :   status = s_ssi; break; }
                break;
            case s_php_closing :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_php_closing ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i-1);
                                ve_.emplace_back (nits, line_, bk_php, collect, i-1);
                                aftercab = true;
                                nits.reset ();
                                status = s_dull; text = twas = i+1; break;
                    default  :  status = s_php; break; }
                break;
            case s_xml_closing :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_xml_closing ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i-1);
                                parse_xml (nits, res, collect, i, line_, s);
                                if (s.empty ()) ve_.emplace_back (nits, line_, bk_xml, collect, i);
                                else ve_.emplace_back (nits, line_, bk_stylesheet, s);
                                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_xml ", quoted_limited_string (::std::string (collect, i), 30));
                                nits.reset ();
                                if (had_doctype) status = s_dull; else status = s_start;
                                aftercab = true;
                                text = twas = i+1; break;
                    default  :  status = s_x; break; }
                break;
            case s_q_closing :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_q_closing ", ch);
                switch (ch)
                {   case '>' :  if (twas > text) ve_.emplace_back (nits, line_, text, twas);
                                if (had_doctype) status = s_dull; else status = s_start;
                                text = twas = i+1; break;
                    default  :  status = s_q; break; }
                break;
            case s_asp_closing :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_asp_closing ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i);
                                ve_.emplace_back (nits, line_, bk_asp, collect, i-1);
                                nits.reset ();
                                aftercab = true;
                                status = s_dull; text = twas = i+1; break;
                    default :   status = s_asp; break; }
                break;
            case s_bang :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_bang ", ch);
                switch (ch)
                {   case '-' :  status = s_comment_first_open; break;
                    case '<' :  mixed_mess (nits, b, e, i, elmt, sg);
                                soe = twas = i; status = s_open; break;
                    case '&' :  mixed_mess (nits, b, e, i, cc, sg);
                                status = s_amper; twas = i; break;
                    case '[' :  status = s_bangsquare; twas = i; break;
                    default :   if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')))
                                {   twas = text; status = s_dull; }
                                else
                                {   status = s_grammar; collect = i; } }
                break;
            case s_bangsquare :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_bangsquare ", ch);
                if (ch == '[') status = s_cdata;
                else if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')))
                {   twas = text; status = s_dull; }
                break;
            case s_cdata :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_cdata ", ch);
                if (ch == ']') status = s_bq_first_close;
                break;
            case s_bq_first_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_bq_first_close ", ch);
                if (ch == ']') status = s_bq_second_close;
                else status = s_cdata;
                break;
            case s_bq_second_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_bq_second_close ", ch);
                if (ch != '>') status = s_cdata;
                else
                {   status = s_dull;
                    nits.set_context (line_, b, e, soe, i);
                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_cdata ", quoted_limited_string (::std::string (text, twas), 30));
                    ve_.emplace_back (nits, line_, bk_cdata, text+9, i-2);
                    aftercab = true; text = twas = i+1;
                    nits.reset (); }
                break;
            case s_comment_first_open :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_comment_first_open ", ch);
                switch (ch)
                {   case '-' :  status = s_comment_second_open; break;
                    default :   twas = text; status = s_dull;
                                if (comment_start) { comment_start = false; nodoctype (nits, res, b, e, i); } }
                break;
            case s_comment_second_open :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_comment_second_open ", ch);
                switch (ch)
                {   case '-' :  status = s_comment_first_close; break;
                    case '#' :  if (! ssi_warn)
                                {   nits.set_context (line_, b, e, i);
                                    nits.pick (nit_ssi, es_info, ec_parser, "Server Side Includes processing disabled");
                                    ssi_warn = true; }
                                status = s_ssi; collect = i; break;
                    default :   status = s_comment; }
                break;
            case s_comment :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_comment ", ch);
                if (ch == '-') status = s_comment_first_close;
                break;
            case s_comment_first_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_comment_first_close ", ch);
                switch (ch)
                {   case '-' :  status = s_comment_second_close; break;
                    default :   status = s_comment; }
                break;
            case s_comment_second_close :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_comment_second_close ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                if (context.shadow_comment ())
                                {   nits.set_context (line_, b, e, soe, i);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace comment ", quoted_limited_string (::std::string (text, twas), 30));
                                    ve_.emplace_back (nits, line_, bk_comment, text+6, i-2);
                                    nits.reset (); }
                                else if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "not inserting comment");
                                aftercab = true;
                                if (comment_start) status = s_start; else status = s_dull;
                                comment_start = doubledashed = false; text = twas = i+1; break;
                    case ' ' :  if (res < html_2) break;
                                // HTML 1 permits white space here!
                                // otherwise drop thru'
                                [[fallthrough]];
                    default :   if (! doubledashed)
                                {   nits.set_context (line_, b, e, i);
                                    if (res.xhtml ())
                                        nits.pick (nit_dashdash, ed_jan10, "1.10.2 Syntax errors", es_warning, ec_parser, "'--' inside a comment drives some XML parsers space");
                                    else if (res.mjr () >= 5)
                                        nits.pick (nit_dashdash, ed_jan10, "1.10.2 Syntax errors", es_info, ec_parser, "'--' inside a comment drives some XML parsers spare"); }
                                doubledashed = true; status = s_comment; }
                break;
            case s_element :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_element ", ch);
                switch (ch)
                {   case ' ' :  if (xmp_mode) { status = s_dull; break; }
                                eofe = i; status = s_inside; break;
                    case '>' :  if (xmp_mode)
                                {   if (! closure) { status = s_dull; break; }
                                    ::std::string n (elem::name (xmp_tag));
                                    if (! compare_no_case (n, ::std::string (collect, i)))
                                    {   PRESUME (collect - b > 2, __FILE__, __LINE__);
                                        PRESUME (e - 1 > i, __FILE__, __LINE__);
                                        if (xmp_tag == elem_xmp)
                                        {   nits.set_context (line_, b, e, collect-2, i+1);
                                            nits.pick (nit_closure_not_xmp, ed_1, "ELEMENT XMP", es_error, ec_element, "a closure started inside <", n, "> must be </", n, ">");
                                            ve_.emplace_back (nits, line_, collect, i, i, true, false);
                                            nits.reset (); }
                                        break; }
                                    nits.set_context (line_, b, e, x, collect-2);
                                    xmp_mode = false;
                                    ve_.emplace_back (nits, line_, x, collect-2);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (x, collect - 2), 30));
                                    nits.reset ();
                                    nits.set_context (line_, b, e, soe, i+1);
                                    ve_.emplace_back (nits, line_, collect, i, i, closure, false);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_node ", quoted_limited_string (::std::string (collect, i), 30));
                                    nits.reset (); }
                                else
                                {   if (twas > text)
                                    {   nits.set_context (line_, b, e, text, twas);
                                        ve_.emplace_back (nits, line_, text, twas);
                                        if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                        nits.reset (); }
                                    nits.set_context (line_, b, e, soe, i+1);
                                    ve_.emplace_back (nits, line_, collect, i, i, closure, false);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_node ", quoted_limited_string (::std::string (collect, i), 30));
                                    nits.reset ();
                                    if (closure) silent_content = false;
                                    else
                                    {   bra_element_ket& current = ve_.back ();
                                        silent_content = current.is_silent_content ();
                                        if (res <= html_2)
                                        {   if (current.is_plaintext ())
                                            {   plaintext = true;
                                                if (i + 1 != e)
                                                {   ve_.emplace_back (nits, line_, i+1, e);
                                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (i+1, e), 30)); } }
                                            else
                                            {   if (current.is_xmp ())
                                                {   xmp_tag = elem_xmp;
                                                    xmp_mode = true; }
                                                x = i + 1; } }
                                        if (! plaintext && ! xmp_mode)
                                            faux_xmp_check (current, xmp_tag, xmp_mode, i, x); } }
                                aftercab = true;
                                status = s_dull; text = twas = i+1; break;
                    case '/' :  if (xmp_mode) { status= s_dull; break; }
                                eofe = i; status = s_purgatory; break;
                    case '<' :  if (xmp_mode) { status = s_dull; break; }
                                mixed_mess (nits, b, e, i, oel, ano); status = s_open; twas = i; break;
                    case '&' :  if (xmp_mode) { status = s_dull; break; }
                                mixed_mess (nits, b, e, i, cc, elmt); status= s_amper; twas = i;break;
                    case '=' :  nits.pick (nit_forgotten_name, es_warning, ec_parser, "has an attribute name been omitted?");
                                twas = text; status = s_dull; break;
                    default :   if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z')) && ((ch < '0') || (ch > '9')) && (ch != '-') && (ch != ':'))
                                {   twas = text; status = s_dull; } }
                break;
            case s_purgatory :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_purgatory ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i+1);
                                if ((i > eofe) && (*(i-1) == '/')) ve_.emplace_back (nits, line_, collect, eofe, i-1, closure, true);
                                else ve_.emplace_back (nits, line_, collect, eofe, i, closure, true);
                                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_node ", quoted_limited_string (::std::string (collect, i), 30));
                                nits.reset ();
                                if (! closure && ! plaintext && ! xmp_mode)
                                    faux_xmp_check (ve_.back (), xmp_tag, xmp_mode, i, x);
                                aftercab = true;
                                status = s_dull; text = twas = i+1; break;
                    case '<' :  mixed_mess (nits, b, e, i, oel, ano); status = s_open; twas = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, cc, elmt); status= s_amper; twas = i; break;
                    default :   status = s_inside; break; }
                break;
            case s_inside :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_inside ", ch);
                switch (ch)
                {   case '>' :  if (twas > text)
                                {   nits.set_context (line_, b, e, text, twas);
                                    ve_.emplace_back (nits, line_, text, twas);
                                    if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (text, twas), 30));
                                    nits.reset (); }
                                nits.set_context (line_, b, e, soe, i+1);
                                ve_.emplace_back (nits, line_, collect, eofe, i, closure, false);
                                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_ncode ", quoted_limited_string (::std::string (collect, i), 30));
                                nits.reset ();
                                if (! closure && ! plaintext && ! xmp_mode)
                                    faux_xmp_check (ve_.back (), xmp_tag, xmp_mode, i, x);
                                aftercab = true;
                                status = s_dull; text = twas = i+1; break;
                    case '<' :  mixed_mess (nits, b, e, i, oel, ano); status = s_open; twas = soe = i; break;
                    case '&' :  mixed_mess (nits, b, e, i, cc, elmt); status= s_amper; twas = i; break;
                    case '/' :  status = s_purgatory; break;
                    case '\'' : status = s_element_quote; break;
                    case '"' :  status = s_element_double_quote; break;
                    default : break; }
                break;
            case s_asp_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_asp_quote ", ch);
                status = ket_quote (nits, ch, status, s_asp, '\'', newline, backslashed);
                break;
            case s_asp_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_asp_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_asp, '"', newline, backslashed);
                break;
            case s_grammar_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_grammar_quote ", ch);
                status = ket_quote (nits, ch, status, s_grammar, '\'', newline, backslashed);
                break;
            case s_grammar_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_grammar_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_grammar, '"', newline, backslashed);
                break;
            case s_php_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_php_quote ", ch);
                status = ket_quote (nits, ch, status, s_php, '\'', newline, backslashed);
                break;
            case s_php_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_php_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_php, '"', newline, backslashed);
                break;
            case s_xml_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_xml_quote ", ch);
                status = ket_quote (nits, ch, status, s_x, '\'', newline, backslashed);
                break;
            case s_xml_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_xml_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_x, '"', newline, backslashed);
                break;
            case s_q_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_q_quote ", ch);
                status = ket_quote (nits, ch, status, s_q, '\'', newline, backslashed);
                break;
            case s_q_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_q_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_q, '"', newline, backslashed);
                break;
            case s_ssi_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_ssi_quote ", ch);
                status = ket_quote (nits, ch, status, s_ssi, '\'', newline, backslashed);
                break;
            case s_ssi_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_ssi_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_ssi, '"', newline, backslashed);
                break;
            case s_element_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_element_quote ", ch);
                status = ket_quote (nits, ch, status, s_inside, '\'', newline, backslashed);
                break;
            case s_element_double_quote :
                if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "s_element_double_quote ", ch);
                status = ket_quote (nits, ch, status, s_inside, '"', newline, backslashed);
                break; } }
    if (context.tell (es_all))
    {   if (! linelog.empty ()) nits.pick (nit_all, es_all, ec_parser, "\\\\ ", linelog);
        form_.pick (nit_all, es_all, ec_parser, "end of input"); }
    if (xmp_mode)
    {   nits.set_context (line_, x, e, e);
        switch (xmp_tag)
        {   case elem_xmp :
                nits.pick (nit_ends_in_xmp, es_warning, ec_parser, "document finishes in <XMP> (use <PLAINTEXT>");
                break;
            case elem_comment :
                nits.pick (nit_eof_in_comment, es_error, ec_parser, "document finishes in a comment");
                break;
            case elem_annotation :
            case elem_annotation_xml :
                nits.pick (nit_eof_in_annotation, es_error, ec_parser, "document finishes in an annotation");
                break;
            default :
                nits.pick (nit_eof_unexpected, es_error, ec_parser, "document finishes unexpectedly");
                break; }
        ve_.emplace_back (nits, line_, x, e);
        if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (x, e), 30)); }
    else
    {   bool sc = true;
        switch (status)
        {   case s_element_quote :
            case s_element_double_quote :
            case s_grammar_quote :
            case s_grammar_double_quote :
            case s_php_quote :
            case s_php_double_quote :
            case s_asp_quote :
            case s_asp_double_quote :
            case s_ssi_quote :
            case s_ssi_double_quote :
            case s_xml_quote :
            case s_xml_double_quote :
            case s_q_quote :
            case s_q_double_quote :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_string, es_error, ec_parser, "document finishes in string");
                sc = false;
                break;
            case s_q :
            case s_q_closing :
            case s_comment_first_close :
            case s_comment_second_close :
            case s_comment :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_comment, es_error, ec_parser, "document finishes in comment");
                sc = false;
                break;
            case s_ssi_first_close :
            case s_ssi_second_close :
            case s_ssi :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_ssi, es_error, ec_parser, "document finishes in Server Side Include");
                sc = false;
                break;
            case s_php :
            case s_asp :
            case s_php_closing :
            case s_asp_closing :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_script, es_error, ec_parser, "document finishes in script");
                sc = false;
                break;
            case s_inside :
            case s_element :
            case s_purgatory :
            case s_slash :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_element, es_error, ec_parser, "document finishes in element");
                sc = false;
                break;
            case s_bq_first_close :
            case s_bq_second_close :
            case s_cdata :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_in_cdata, es_error, ec_parser, "document finishes inside <![CDATA[ ...");
                sc = false;
                break;
            case s_open :
            case s_bangsquare :
            case s_startopen :
            case s_grammar :
            case s_x :
            case s_xml_closing :
                nits.set_context (line_, collect, e, e);
                nits.pick (nit_eof_unexpected, es_warning, ec_parser, "document finishes unexpectedly");
                sc = false;
                break;
            default: break; }
        if ((i != e) || ! nits.empty ())
        {   if (sc) nits.set_context (line_, i, e, e);
            ve_.emplace_back (nits, line_, i, e);
            if (context.tell (es_all)) form_.pick (nit_all, es_all, ec_parser, "emplace bk_text ", quoted_limited_string (::std::string (i, e), 30)); } }
    return res; }

::std::string bras_ket::rpt () const
{   ::std::string res;
    for (auto e : ve_)
        res += e.rpt () + "\n";
    return res; }
