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

#include "main/standard.h"
#include "css/css_parse.h"
#include "css/css.h"
#include "css/group.h"

typedef ::std::vector < css_token > vct_t;

bool hexen (::std::string& s, ::std::string& hex)
{   if (hex.empty ()) return false;
    const int ch = hex_value (hex);
    s += ch; 
    hex.clear ();
    return true; }

void bonk (vtt_t& vt, css_token t, const int line, ::std::string& s, ::std::string& hex, const ::std::string& x, bool& commented, bool& sgml_cmt, bool& xml_cmt)
{   hexen (s, hex);
    if (t == ct_root) commented = sgml_cmt = xml_cmt = false;
    bool shush = false;
    if (! s.empty ())
    {   if ((s.length () > 1) && ((s.at (0) == '"') || (s.at (0) == '\'') || (s.at (0) == '\\')) && (s.at (s.length () - 1) == s.at (0)))
        {   vt.emplace_back (ct_string, line, x, uq3 (s)); shush = true; }
        else if ((s.length () == 1) && (s.at (0) == '-'))
            vt.emplace_back (ct_dash, line, x);
        else if ((s.substr (0, 1).find_first_not_of (SIGNEDDECIMAL) == ::std::string::npos) &&
                    (s.substr (1).find_first_not_of (EXPONENTIAL) == ::std::string::npos))
            vt.emplace_back (ct_number, line, x, s);
        else
        {   if (context.html_ver ().css_version () == css_1)
                if (s.find_first_not_of (HYPHENATED) == ::std::string::npos)
                    vt.emplace_back (ct_keyword, line, x, s);
                else vt.emplace_back (ct_identifier, line, x, s);
            else if (s.substr (0, 1).find_first_of (POSITIVE) != ::std::string::npos)   
                vt.emplace_back (ct_identifier, line, x, s);
            else
            {   char ch = 0;
                for (auto ss : s)
                    if ((ss != '-') && ((ss < 'a') || (ss > 'z')) && ((ss < 'A') || (ss > 'Z')) && ((ss < '0') || (ss > '9')))
                    {   ch = ss;
                        break; }
                if (ch == 0)
                    vt.emplace_back (ct_keyword, line, x, s);
                else
                    vt.emplace_back (ct_identifier, line, x, s); } }
        s.clear (); }
    if (! shush && ! commented)
        vt.emplace_back (t, line, x); }

bool anticipate (::std::string::const_iterator& from, ::std::string::const_iterator to, const ::std::string& super)
{   const ::std::string::size_type len = super.size ();
    PRESUME (len > 0, __FILE__, __LINE__);
    if (to - from < GSL_NARROW_CAST < int > (len)) return false;
    if (::std::string (from, from + len) != super) return false;
    from += len - 1;
    return true; }

void breed (v_np& , vtt_t& t, const ::std::string::const_iterator , const ::std::string::const_iterator )
{   int mum = 0;
    PRESUME (t.size () > 0, __FILE__, __LINE__);
    const int last = ::gsl::narrow_cast < int > (t.size () - 1);
    if (last == 0) return;
    t.at (0).child_ = 1;
    vct_t brat;
    for (int i = 1; i < ::gsl::narrow_cast < int > (t.size ()); ++i)
    {   t.at (i).mum_ = mum;
        if (i < last) t.at (i).next_ = i + 1;
        switch (t.at (i).t_)
        {   case ct_root :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                break;
            case ct_curly_brac :
            case ct_square_brac :
                brat.push_back (t.at (i).t_);
                if (i < last) t.at (i).child_ = i + 1;
                else t.at (i).nits_.pick (nit_css_syntax, es_error, ec_css, "open bracket at end of CSS");
                t.at (i).next_ = -1;
                mum = i;
                break;
            case ct_curly_ket :
            case ct_square_ket :
                if ((t.at (mum).t_ == ct_root) || (brat.size () == 0))
                {   t.at (i).nits_.pick (nit_css_syntax, es_error, ec_css, "no corresponding open bracket");
                    t.at (i).mum_ = 0;
                    break; }
                else
                {   const int pos = ::gsl::narrow_cast < int > (brat.size () - 1);
                    if (((t.at (i).t_ == ct_curly_ket) && (brat.at (pos) != ct_curly_brac)) ||
                        ((t.at (i).t_ == ct_round_ket) && (brat.at (pos) != ct_round_brac)) ||
                        ((t.at (i).t_ == ct_square_ket) && (brat.at (pos) != ct_square_brac)))
                    {   t.at (i).nits_.pick (nit_css_syntax, es_error, ec_css, "contradictory close and open brackets");
                        break; }
                    brat.pop_back (); }
                if (i != last) t.at (mum).next_ = i + 1;
                mum = t.at (mum).mum_;
                t.at (i).next_ = -1;
                break;
            default :
                break; } }
    if (brat.size () > 0)
        t.at (last).nits_.pick (nit_css_syntax, es_error, ec_css, "unclosed brackets at end of CSS"); }

void boast (vtt_t& t)
{   if (context.tell (es_detail))
    {   ::std::cout << "n: token parent/next/child text\n";
        for (int i = 0; i < GSL_NARROW_CAST < int > (t.size ()); ++i)
        {   ::std::cout << i << ": ";
            switch (t.at (i).t_)
            {   case ct_root : ::std::cout << "root"; break;
                case ct_whitespace : ::std::cout << "whitespace"; break;
                case ct_comment : ::std::cout << "comment"; break;
                case ct_string : ::std::cout << "string"; break;
                case ct_identifier : ::std::cout << "identifier"; break;
                case ct_keyword : ::std::cout << "keyword"; break;
                case ct_number : ::std::cout << "number"; break;
                case ct_ampersand : ::std::cout << "ampersand"; break;
                case ct_at : ::std::cout << "at"; break;
                case ct_comma : ::std::cout << "comma"; break;
                case ct_bang : ::std::cout << "bang"; break;
                case ct_dollar : ::std::cout << "dollar"; break;
                case ct_semicolon : ::std::cout << "semicolon"; break;
                case ct_slash : ::std::cout << "slash"; break;
                case ct_coco : ::std::cout << "coco"; break;
                case ct_colon : ::std::cout << "colon"; break;
                case ct_hash : ::std::cout << "hash"; break;
                case ct_hat : ::std::cout << "hat"; break;
                case ct_dot : ::std::cout << "dot"; break;
                case ct_dash : ::std::cout << "dash"; break;
                case ct_splat : ::std::cout << "splat"; break;
                case ct_eq : ::std::cout << "eq"; break;
                case ct_gt : ::std::cout << "gt"; break;
                case ct_gteq : ::std::cout << "gteq"; break;
                case ct_gtgt : ::std::cout << "gtgt"; break;
                case ct_lt : ::std::cout << "lt"; break;
                case ct_lteq : ::std::cout << "lteq"; break;
                case ct_bar : ::std::cout << "bar"; break;
                case ct_barbar : ::std::cout << "barbar"; break;
                case ct_plus : ::std::cout << "plus"; break;
                case ct_squiggle : ::std::cout << "squiggle"; break;
                case ct_curly_brac : ::std::cout << "curly_brac"; break;
                case ct_curly_ket : ::std::cout << "curly_ket"; break;
                case ct_square_brac : ::std::cout << "square_brac"; break;
                case ct_square_ket : ::std::cout << "square_ket"; break;
                case ct_round_brac : ::std::cout << "round_brac"; break;
                case ct_round_ket : ::std::cout << "round_ket"; break;
                case ct_eof : ::std::cout << "eof"; break;
                case ct_error : ::std::cout << "error"; break;
                default: ::std::cout << "unexpected " << t.at (i).t_; break; }
            ::std::cout << " " << t.at (i).mum_ << "/" << t.at (i).next_ << "/" << t.at (i).child_ << " " << quote (t.at (i).val_) << "\n"; } } }

bool css::parse (const ::std::string& content, const bool x)
{   if (invalid ()) return false;
    if (content.empty ()) return true;
    if (args_.abs_.empty ()) args_.abs_ = abs_;

    if (line_ == 0) line_ = 1;
    ::std::string v, hex;
    const ::std::string::const_iterator b (content.cbegin ());
    const ::std::string::const_iterator e (content.cend ());
    PRESUME (args_.t_.empty (), __FILE__, __LINE__);
    args_.t_.emplace_back (ct_root, 0, "(overview)");
    bool backslash = false;
    bool controlled = false;
    bool sq = false;
    bool dq = false;
    bool commented = false, sgml_cmt = false, xml_cmt = false;

    if (! args_.g_.told ())
    {   if (args_.snippet_ || args_.styled ())
            args_.t_.at (0).nits_.pick (nit_css_version, es_comment, ec_css, "Presuming CSS version ", args_.v_.css_version_name ());
        else if (context.html_ver () != html_default)
            args_.t_.at (0).nits_.pick (nit_html, es_info, ec_css, "Presuming CSS intended for use with ", context.html_ver ().name ());
        args_.g_.told (true); }

    for (::std::string::const_iterator i = b; i != e; ++i)
        if (backslash)
        {   if (! commented) 
            {   const ::std::string h (HEX);
                if (h.find (*i) == ::std::string::npos)
                {   v += *i;
                    if ((*i == '\n') || (*i == '\v')) ++line_; }
                else
                {   hexen (v, hex);
                    hex = *i; } }
            backslash = false; }
        else
        {   const ::std::string c (near_here (b, e, i));
            if (commented) switch (*i)
            {   case '\v' :
                case '\n' :++line_; break;
                case '*' : if (anticipate (i, e, "*/")) commented = false;
                           break;
                default  : break; }
            else if (sq || dq) switch (*i)
            {   case '\\' : backslash = true; break;
                case '\v' :
                case '\n' : bonk (args_.t_, ct_string, line_++, v, hex, c, commented, sgml_cmt, xml_cmt);
                            if (args_.t_.size () > 0)
                                args_.t_.at (args_.t_.size () - 1).nits_.pick (nit_css_syntax, es_warning, ec_css, "end of line in string");
                            sq = dq = false;
                            break;
                case '"' :  v += *i;
                            if (sq) break;
                            PRESUME (dq, __FILE__, __LINE__);
                            dq = false;
                            bonk (args_.t_, ct_string, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                            break;
                case '\'' : v += *i;
                            if (dq) break;
                            PRESUME (sq, __FILE__, __LINE__);
                            sq = false;
                            bonk (args_.t_, ct_string, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                            break;
                default :   v += *i; break; }
            else switch (*i)
            {   case '\t' :
                case '\r' :
                case ' ' : bonk (args_.t_, ct_whitespace, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '\v' :
                case '\n' :bonk (args_.t_, ct_whitespace, line_++, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '\\' :backslash = true; break;
                case '/' : if (anticipate (i, e, "/*"))
                           {    bonk (args_.t_, ct_comment, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                                commented = true; }
                           else bonk (args_.t_, ct_slash, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           break;
                case '*' : if (anticipate (i, e, "*/")) commented = false;
                           else bonk (args_.t_, ct_splat, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           break;
                case '{' : bonk (args_.t_, ct_curly_brac, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '}' : bonk (args_.t_, ct_curly_ket, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '[' : bonk (args_.t_, ct_square_brac, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case ']' : if (xml_cmt && anticipate (i, e, "]]>")) xml_cmt = false;
                           else bonk (args_.t_, ct_square_ket, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           break;
                case '(' : bonk (args_.t_, ct_round_brac, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case ')' : bonk (args_.t_, ct_round_ket, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '@' : bonk (args_.t_, ct_at, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '.' : if ((! v.empty ()) && (v.find_first_not_of (EXPONENTIAL) == ::std::string::npos)) v += '.';
                           else if (v.empty () && (i+1 < e) && ((*(i+1) >= '-') && (*(i+1) <= '9'))) v = '.'; 
                           else bonk (args_.t_, ct_dot, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           break;
                case ',' : bonk (args_.t_, ct_comma, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case ':' : if (! anticipate (i, e, "::")) bonk (args_.t_, ct_colon, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else if (args_.v_.css_selector () >= 3) bonk (args_.t_, ct_coco, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else args_.t_.at (args_.t_.size () - 1).nits_.pick (nit_css_version, ed_css_selectors_3, "2. Selectors", es_error, ec_css, ":: requires CSS Selector 3 or better");
                           break;
                case ';' : bonk (args_.t_, ct_semicolon, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '!' : bonk (args_.t_, ct_bang, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '#' : bonk (args_.t_, ct_hash, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '^' : bonk (args_.t_, ct_hat, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '$' : bonk (args_.t_, ct_dollar, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '>' : if (anticipate (i, e, ">="))
                                bonk (args_.t_, ct_gteq, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else if (! anticipate (i, e, ">>"))
                                bonk (args_.t_, ct_gt, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else if (context.html_ver ().css_cascade () >= 6)
                                bonk (args_.t_, ct_gtgt, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else args_.t_.at (args_.t_.size () - 1).nits_.pick (nit_css_version, ed_css_cascade_6, "2.6. Scoped Descendant Combinator", es_error, ec_css, ">> requires CSS Cascade 6");
                           break;
                case '<' : if (anticipate (i, e, "<="))
                                bonk (args_.t_, ct_lteq, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else if (x && (! xml_cmt) && anticipate (i, e, "<![CDATA["))
                           {    bonk (args_.t_, ct_whitespace, line_, v, hex, c, commented, sgml_cmt, xml_cmt); xml_cmt = true; }
                           else if ((! sgml_cmt) && anticipate (i, e, "<!--"))
                           {    bonk (args_.t_, ct_whitespace, line_, v, hex, c, commented, sgml_cmt, xml_cmt); sgml_cmt = true; }
                           else bonk (args_.t_, ct_lt, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           break;
                case '=' : bonk (args_.t_, ct_eq, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '~' : bonk (args_.t_, ct_squiggle, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '|' : if (! anticipate (i, e, "||"))
                               bonk (args_.t_, ct_bar, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else if (context.html_ver ().css_selector () >= 4)
                               bonk (args_.t_, ct_barbar, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else args_.t_.at (args_.t_.size () - 1).nits_.pick (nit_css_version, ed_css_selectors_4, "2. Selectors Overview", es_error, ec_css, "|| requires CSS Selector 4");
                           break;
                case '&' : if (context.html_ver ().css_cascade () >= 6)
                               bonk (args_.t_, ct_ampersand, line_, v, hex, c, commented, sgml_cmt, xml_cmt);
                           else args_.t_.at (args_.t_.size () - 1).nits_.pick (nit_css_version, ed_css_cascade_6, "2.5.3. Scoped Style Rules", es_error, ec_css, "& requires CSS Cascade 6");
                           break;
                case '+' : bonk (args_.t_, ct_plus, line_, v, hex, c, commented, sgml_cmt, xml_cmt); break;
                case '"' :
                    v += *i;
                    if (v.size () == 1)
                    {   dq = true;
                        PRESUME (! sq, __FILE__, __LINE__); }
                    break;
                case '\'' :
                    v += *i;
                    if (v.size () == 1)
                    {   sq = true;
                        PRESUME (! dq, __FILE__, __LINE__); }
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
                case 'A' :
                case 'a' :
                case 'B' :
                case 'b' :
                case 'C' :
                case 'c' :
                case 'D' :
                case 'd' :
                case 'E' :
                case 'e' :
                case 'F' :
                case 'f' :
                    if (! hex.empty ())
                    {   unsigned int max = 6;
                        if (args_.v_.css_version () == css_1) max = 4; // CSS 1 Appendix B grammar
                        if (hex.length () < max) hex += *i;
                        else
                        {   hexen (v, hex);
                            v += *i; } }
                    else v += *i;
                    break;
                case '-' :
                    if (sgml_cmt && anticipate (i, e, "-->"))
                    {   sgml_cmt = false;
                        break; }
                    FALLTHROUGH;
                default :
                    if (::std::iswspace (*i) || ::std::iswblank (*i))
                    {   if (! hexen (v, hex))
                            bonk (args_.t_, ct_whitespace, line_, v, hex, c, commented, sgml_cmt, xml_cmt); }
#ifdef STR_IT_BYTE
                    else if (::std::iscntrl (*i))
#else // STR_IT_BYTE
                    else if ((*i <= 254) && (*i >= 0) && ::std::iscntrl (*i))
#endif // STR_IT_BYTE
                    {   if (! controlled)
                        {   args_.t_.at (0).nits_.pick (nit_css_syntax, es_warning, ec_css, "Unexpected control characters ignored.");
                            controlled = true; }
                        if (! hexen (v, hex))
                            bonk (args_.t_, ct_whitespace, line_, v, hex, c, commented, sgml_cmt, xml_cmt); }
                    else
                    {   hexen (v, hex); v += *i; }
                    break; } }

    if (xml_cmt || sgml_cmt || commented)
        if (args_.t_.size () > 0)
        {   nitpick& nits = args_.t_.at (args_.t_.size () - 1).nits_;
            if (xml_cmt)
                nits.pick (nit_eof_in_comment, es_warning, ec_css, "CSS ends in CDATA");
            if (sgml_cmt)
                nits.pick (nit_eof_in_comment, es_warning, ec_css, "CSS ends in an SGML comment");
            if (commented)
                nits.pick (nit_eof_in_comment, es_warning, ec_css, "CSS ends in a comment"); }

    // these function calls are dedicated to my younger brother-in-law!!
    bonk (args_.t_, ct_eof, line_, v, hex, near_here (b, e, e), commented, sgml_cmt, xml_cmt);
    breed (ticks_, args_.t_, b, e);
    boast (args_.t_);

    st_.parse (args_);
    check_for_standard_classes (context.html_ver ());

    if (! snippet ())
        for (auto t : args_.t_)
            if (args_.dst_.get () != nullptr)
                args_.dst_ -> merge (t.nits_);

    return true; }

::std::string tkn_rpt (const css_token t, const ::std::string& s)
{   switch (t)
    {   case ct_keyword :
        case ct_identifier :
        case ct_number : return s;
        case ct_string : return s;
        case ct_slash : return "/";
        case ct_splat : return "*";
        case ct_curly_brac : return "{";
        case ct_curly_ket : return "}";
        case ct_square_brac : return "[";
        case ct_square_ket : return "]";
        case ct_round_brac : return "(";
        case ct_round_ket : return ")";
        case ct_at : return "@";
        case ct_dot : return ".";
        case ct_dash : return "-";
        case ct_comma : return ",";
        case ct_coco : return "::";
        case ct_colon : return ":";
        case ct_semicolon : return ";";
        case ct_ampersand : return "&";
        case ct_bang : return "!";
        case ct_hash : return "#";
        case ct_hat : return "^";
        case ct_dollar : return "$";
        case ct_gt : return ">";
        case ct_gteq : return ">=";
        case ct_gtgt : return ">>";
        case ct_lt : return "<";
        case ct_lteq : return "<=";
        case ct_eq : return "=";
        case ct_squiggle : return "~";
        case ct_bar : return "|";
        case ct_barbar : return "||";
        case ct_plus : return "+";
        case ct_whitespace : return " ";
        case ct_comment : return " ";
        case ct_error : return "???";
        case ct_eof : return "";
        default : GRACEFUL_CRASH (__FILE__, __LINE__); } }

::std::string assemble_string (vtt_t& vt, const int from, const int to, const bool inclusive)
{   PRESUME (from > 0, __FILE__, __LINE__);
    PRESUME (((to == -1) || (from <= to)), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (vt.size ());
    PRESUME (to < len, __FILE__, __LINE__);
    ::std::string res;
    int t = to;
    if (inclusive && (t > 0)) ++t; 
    for (int i = from; ((t < 0) || (i < t)) && (i < len) && (vt.at (i).next_ == (i+1)); ++i)
        res += tkn_rpt (vt.at (i));
    return res; }

int token_find (const vtt_t& vt, const css_token t, const int from, const int to, int* prev)
{   PRESUME ((from >= 0) && (from < GSL_NARROW_CAST < int > (vt.size ())), __FILE__, __LINE__);
    PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    if (prev != nullptr) *prev = -1;
    for (int i = from; (i >= 0) && (i < GSL_NARROW_CAST < int > (vt.size ())); i = next_token_at (vt, i, to))
    {   if ((to >= 0) && (i > to)) break;
        else if (vt.at (i).t_ == t) return i;
        if (prev != nullptr) *prev = i; }
    return -1; }
 
int ident_find (const vtt_t& vt, const ::std::string& kw, const int from, const int to, int* prev)
{   PRESUME ((from >= 0) && (from < GSL_NARROW_CAST < int > (vt.size ())), __FILE__, __LINE__);
    PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    if (prev != nullptr) *prev = -1;
    for (int i = from; (i >= 0) && (i < GSL_NARROW_CAST < int > (vt.size ())); i = next_token_at (vt, i, to))
    {   if ((to >= 0) && (i > to)) break;
        else if (((vt.at (i).t_ == ct_identifier) || (vt.at (i).t_ == ct_keyword)) && compare_no_case (kw, vt.at (i).val_)) return i;
        if (prev != nullptr) *prev = i; }
    return -1; }
 
int next_token_at (const vtt_t& vt, const int from, const int to)
{   if ((from < 0) || ((to >= 0) && (from >= to)) || (vt.at (from).t_ == ct_eof))
        return -1;
    return vt.at (from).next_; }

int first_non_whitespace (const vtt_t& vt, int from, const int to)
{   while ((from >= 0) && ((to < 0) || (from <= to)) && ((vt.at (from).t_ == ct_whitespace) || (vt.at (from).t_ == ct_comment)))
        from = next_token_at (vt, from, to);
    return from; }

int next_non_whitespace (const vtt_t& vt, const int from, const int to)
{   return first_non_whitespace (vt, next_token_at (vt, from, to), to); }

::std::string assemble_unit (vtt_t& vt, int& i, const int to)
{   ::std::string s;
    if ((i >= 0) && ((to < 0) || (i <= to)))
        if ((static_cast < ::std::size_t > (i) + 1 < vt.size ()) && (vt.at (i).t_ == ct_number))
        {   PRESUME (! vt.at (i).val_.empty (), __FILE__, __LINE__);
            if ((vt.at (stp (i)).t_ == ct_keyword) || (vt.at (stp (i)).t_ == ct_identifier))
            {   s = vt.at (i).val_ + vt.at (stp (i)).val_;
                i += 2; }
            else s = vt.at (i++).val_; }
        else s = tkn_rpt (vt.at (i++));
    return s; }
