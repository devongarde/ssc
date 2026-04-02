/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "parser/html_version.h"
#include "utility/common.h"
#include "main/context.h"
#include "type/type.h"

const char* doctype = "DOCTYPE";
CONSTEXPR ::std::size_t doctype_len = 7;
const char* docdot = "<!DOCTYPE ...>";

html_version::html_version (const ::boost::gregorian::date& d)
        :   version (0, 0, HV_WHATWG, ao_html), ext_ (NOFLAGS), ext2_ (NOFLAGS), ext3_ (NOFLAGS), ext4_ (NOFLAGS), ext5_ (NOFLAGS)
{   if (d.is_not_a_date ()) { reset (html_1); return; }
    int y = d.year ();
    if ((y > 100) && (y < 2000)) { reset (html_1); return; }
    int m = d.month ();
    if (y > 2000) y -= 2000;
    if ((y < HTML_5_EARLIEST_YEAR) || ((y == HTML_5_EARLIEST_YEAR) && (m < HTML_5_EARLIEST_MONTH)))
    {   y = HTML_5_EARLIEST_YEAR; m = HTML_5_EARLIEST_MONTH; }
    else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
    {   y = HTML_LATEST_YEAR; m = HTML_LATEST_MONTH; }
    PRESUME ((m > 0) && (m < 13), __FILE__, __LINE__);
    set_mjr (GSL_NARROW_CAST <unsigned short> (y), GSL_NARROW_CAST <unsigned short> (m * 16));
    if (mjr () >= 4)
        if (mjr () <= HTML_2010) set_ext2 (H2_MATH_1);
        else if (mjr () <= HTML_2014) set_ext2 (H2_MATH_2);
        else if (mjr () <= HTML_2020) set_ext2 (H2_MATH_3);
        else if (mjr () <= HTML_2024) set_ext2 (H2_MATH_C);
        else set_ext2 (H2_MATH_4);
    if (mjr () >= 4)
        if (*this >= html_apr21) set_ext (HE_SVG_21);
        else if (*this >= html_5_3) set_ext (HE_SVG_20);
        else if (mjr () > HTML_2008) set_ext (HE_SVG_12_TINY);
        else set_ext (HE_SVG_11);
    if (mjr () >= 5)
        if (*this >= html_jul20) set_ext2 (H2_JSONLD_1_1);
        else if (mjr () >= HTML_2014) set_ext2 (H2_JSONLD_1_0);
    switch (mjr ())
    {   case 0 :
        case 1 : break;
        case 2 :
        case 3 : css_version (css_1); break;
        case 4 : if (mnr () == 0) css_version (css_2_0);
                 else css_version (css_2_1);
                 break;
        case 5 :
        case 6 : css_version (css_2_1); break;
        case 7 :
        case 8 :
        case 9 : css_version (css_2007); break;
        case 10 :
        case 11 :
        case 12 :
        case 13 :
        case 14 : css_version (css_2010); break; 
        case 15 : 
        case 16 : css_version (css_2015); break;
        case 17 : css_version (css_2017); break; 
        case 18 :
        case 19 : css_version (css_2018); break;  
        case 20 : css_version (css_2020); break; 
        case 21 : css_version (css_2021); break; 
        case 22 : css_version (css_2022); break; 
        case 23 : css_version (css_2023); break; 
        case 24 : css_version (css_2024); break;
        case 25 : css_version (css_2025); break;
        default : css_version (css_2025); break; } }

html_version::html_version (const boost::gregorian::date& d, const flags_t flags, const flags_t extensions, const flags_t e2, const flags_t e3, const flags_t e4, const flags_t e5)
        :   version (0, 0, flags | HV_WHATWG, ao_html), ext_ (extensions), ext2_ (e2), ext3_ (e3), ext4_ (e4), ext5_ (e5)
{   if (d.is_not_a_date ()) { reset (html_1); return; }
    int y = d.year ();
    if ((y > 100) && (y < 2000)) { reset (html_1); return; }
    int m = d.month ();
    if (y > 2000) y -= 2000;
    if ((y < HTML_5_EARLIEST_YEAR) || ((y == HTML_5_EARLIEST_YEAR) && (m < HTML_5_EARLIEST_MONTH)))
    {   y = HTML_5_EARLIEST_YEAR; m = HTML_5_EARLIEST_MONTH; }
    else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
    {   y = HTML_LATEST_YEAR; m = HTML_LATEST_MONTH; }
    PRESUME ((m > 0) && (m < 13), __FILE__, __LINE__);
    set_mjr (GSL_NARROW_CAST <unsigned short> (y), GSL_NARROW_CAST <unsigned short> (m * 16));
    if (no_ext2 (MATH_MASK))
        if (mjr () >= 4)
            if (mjr () <= HTML_2010) set_ext2 (H2_MATH_1);
            else if (mjr () <= HTML_2014) set_ext2 (H2_MATH_2);
            else if (mjr () <= HTML_2020) set_ext2 (H2_MATH_3);
            else if (mjr () <= HTML_2025) set_ext2 (H2_MATH_C);
            else set_ext2 (H2_MATH_4);
    if (no_ext (SVG_MASK))
        if (mjr () >= 4)
            if (*this >= html_apr21) set_ext (HE_SVG_21);
            else if (*this >= html_5_3) set_ext (HE_SVG_20);
            else if (mjr () > HTML_2008) set_ext (HE_SVG_12_TINY);
            else set_ext (HE_SVG_11);
    if (no_ext2 (JSONLD_MASK))
        if (mjr () >= 5)
            if (*this >= html_jul20) set_ext2 (H2_JSONLD_1_1);
            else if (mjr () >= HTML_2014) set_ext2 (H2_JSONLD_1_0);
    if (no_ext2 (H2_CSS_MASK))
        switch (mjr ())
        {   case 0 :
            case 1 : break;
            case 2 :
            case 3 : set_ext2 (H2_CSS_1); break;
            case 4 : set_ext2 (H2_CSS_2); break;
            default : set_ext2 (H2_CSS_3); break; }
    if (mjr () > 4)
    {   if (no_ext3 (H3_CSS_MASK)) set_ext3 (H3_CSS_3);
        if (no_ext4 (H4_CSS_MASK)) set_ext4 (H4_CSS_3); } }

html_version::html_version (nitpick& nits, const ::std::string& ss) : version (ao_html)
{   if (! ss.empty ())
    {   ::std::string s (trim_the_lot_off (ss));
        bool xhtml = false;
        if (s.length () >= 4)
            if (compare_no_case (s.substr (0, 4), HTML_EXT)) s = trim_the_lot_off (s.substr (4));
            else if (compare_no_case (s.substr (0, 5), XHTML_EXT)) { s = trim_the_lot_off (s.substr (5)); xhtml = true; }
        const ::std::string::size_type pos = s.find ('.');
        if (pos != ::std::string::npos)
        {   int mj = 1, mn = USHRT_MAX;
            if (pos == s.length () - 1) mj = lexical < int > :: cast (s.substr (0, pos));
            else if (pos == 0) { mj = 0; mn = 1; }
            else
            {   mj = lexical < int > :: cast (s.substr (0, pos));
                mn = lexical < int > :: cast (s.substr (pos+1)); }
            if (xhtml)
                switch (mj)
                {   case 1 :
                        if (mn == 0) { mj = 4; mn = 2; }
                        else if (mn == 1) { mj = 4; mn = 3; }
                        else
                        {   mj = 4; mn = 3;
                            nits.pick ( nit_config_version, es_warning, ec_init,
                                        "unknown version of XHTML; presuming XHTML 1.1"); }
                        break;
                    case 2 :
                        if (mn > 0)
                            nits.pick ( nit_config_version, es_warning, ec_init,
                                        "unknown version of XHTML; presuming XHTML 2.0");
                        mj = 4; mn = 4;
                        break;
                    case 5 :
                        if (mn > 3)
                        {   mn = 2;
                            nits.pick ( nit_config_version, es_warning, ec_init,
                                        "unknown version of XHTML, presuming XHTML 5.2"); }
                        break;
                    default :
                        mj = 5; mn = 2;
                            nits.pick ( nit_config_version, es_warning, ec_init,
                                        "unknown version of XHTML; presuming XHTML 5.2");
                        break;  }
            if ((mj > 255) || (mn > 255))
                reset (html_default);
            else switch (mj)
            {   case 5 :
                    switch (mn)
                    {   case 0 : reset (html_5_0); break;
                        case 1 : reset (html_5_1); break;
                        case 2 : reset (html_5_2); break;
                        case 3 : reset (html_5_3); break;
                        case 4 : reset (html_jul20); break;
                        default : reset (html_5_3); break; }
                    break;
                case 4 :
                    switch (mn)
                    {   case 0 : reset (html_4_0); break;
                        case 1 : reset (html_4_1); break;
                        case 2 : reset (xhtml_1_0); break;
                        case 3 : reset (xhtml_1_1); break;
                        default : reset (xhtml_2); break; }
                    break;
                case 3 :
                    if (mn == 0) reset (html_3_0);
                    else reset (html_3_2);
                    break;
                case 2 :
                    switch (mn)
                    {   case 0 : reset (html_2); break;
                        case 1 : reset (html_2_level_1); break;
                        default : reset (html_2_level_2); break; }
                    break;
                case 1 :
                    reset (html_1);
                    break;
                default :
                    reset (html_default);
                    break; }
            if (xhtml) set_flags (HV_XHTML); }
        else if (s.find ('/') != ::std::string::npos)
            if ((s.length () != 10) || (s.at (4) != '/') || (s.at (7) != '/') || (s.find_first_not_of (DENARY "/") != ::std::string::npos))
                nits.pick (nit_config_date, es_warning, ec_init, "bad date ", quote (s), " ignored ('YYYY/MM/DD' expected)");
            else
            {   const ::boost::gregorian::date d (::boost::gregorian::from_string (s));
                if (d.is_not_a_date ())
                    nits.pick (nit_config_date, es_warning, ec_init, "invalid date ", quote (s), " ignored");
                else
                {   int y = d.year ();
                    const int m = d.month ();
                    if (y > 2000) y -= 2000;
                    else if (y > 99) y = 99;
                    if ((y < HTML_5_EARLIEST_YEAR) || ((y == HTML_5_EARLIEST_YEAR) && (m < HTML_5_EARLIEST_MONTH)))
                    {   nits.pick (nit_config_date, es_warning, ec_init, quote (s) + " is too early, presuming ", HTML_5_EARLIEST_YEAR, "/", HTML_5_EARLIEST_MONTH, "/1");
                        reset (html_version (html_jan05)); }
                    else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
                    {   nits.pick (nit_config_date, es_warning, ec_init, quote (s), " is too recent, presuming ", HTML_LATEST_YEAR, "/", HTML_LATEST_MONTH, "/1");
                        reset (html_version (html_current)); }
                    else reset (html_version (d));
                    if (xhtml) set_flags (HV_XHTML); } }
        else switch (lexical < int > :: cast (s))
        {   case 1 : reset (html_version (html_1)); break;
            case 2 : reset (html_version (html_2)); break;
            case 3 : reset (html_version (html_3_2)); break;
            case 4 : reset (html_version (html_4_1)); break;
            case 5 : reset (html_version (html_default)); break;
            default : 
                if (s == "+") reset (html_version (html_plus));
                else if (compare_no_case (s, "plus")) reset (html_version (html_plus));
                else if (compare_no_case (s, "tags")) reset (html_version (html_tags));
                else nits.pick (nit_config_version, es_error, ec_init, quote (s), ": bad HTML version"); } } }

void html_version::swap (html_version& v) noexcept
{   version::swap (v);
    ::std::swap (css_, v.css_);
    ::std::swap (ext_, v.ext_);
    ::std::swap (ext2_, v.ext2_);
    ::std::swap (ext3_, v.ext3_);
    ::std::swap (ext4_, v.ext4_);
    ::std::swap (ext5_, v.ext5_); }

void html_version::init (const unsigned short mjr)
{   css_ = css_unknown;
    switch (mjr)
    {   case 0 :
            reset (html_tags); break;
        case 1 :
            reset (html_1); break;
        case 2 :
            reset (html_2); break;
        case 3 :
            reset (html_3_2); break;
        case 4 :
            reset (html_4_1); break;
        case 5 :
            reset (html_current); break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            UNREACHABLE (reset (html_current)); } }

::std::string minor_to_date (const html_version& v)
{   PRESUME (v.is_5 (), __FILE__, __LINE__);
    if (v == html_5_0) return "5.0";
    if (v == html_5_1) return "5.1";
    if (v == html_5_2) return "5.2";
    if (v == html_5_3) return "5.3";
    ::std::string res ("5/20");
    if (v.mjr () < 10)
    {   res += "0";
        res += GSL_NARROW_CAST <char> (v.mjr () + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (static_cast < int > (v.mjr ()));
    const int mon = v.mnr () / 16;
    if (mon <= 9)
    {   res += "0";
        res += GSL_NARROW_CAST <char> (mon + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (mon);
    int day = v.mnr () % 16;
    day *= 2;
    day += 1;
    if (day <= 9)
    {   res += "0";
        res += GSL_NARROW_CAST <char> (day + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (day);
    return res; }

::std::string html_version::name () const
{   ::std::ostringstream res;
    if (known () && xhtml ())
    {   res << "XHTML";
        switch (mnr ())
        {   case 2 : res << "-1.0"; break;
            case 3 : res << "-1.1"; break;
            case 4 : res << "-2.0"; break;
            default : res << "-5"; } }
    else if (known () && atom ())
        res << "ATOM";
    else if (known () && rsl ())
        res << "RSL";
    else if (known () && rss ())
        res << "RSS";
    else
    {   res << "HTML";
        if (known ())
            switch (mjr ())
            {   case 0 :
                    if (mnr () == 1) res << "-Tags";
                    break;
                case 1 :
                    if (mnr () == 0) res << "-1";
                    else if (mnr () == 1) res << "+";
                    break;
                case 2 :
                    res << "-2";
                    if (level () > 0) res << "/" << level ();
                    break;
                case 3 :
                    res << "-3." << GSL_NARROW_CAST <char> (mnr () + '0');
                    break;
                case 4 :
                    res << "-4.0";
                    if (mnr () == 1) res << "1";
                    break;
                default:
                    res << "-" << minor_to_date (*this);
                    break; } }
    return res.str (); }

::std::string html_version::nice_name () const
{   if (mjr () < 5) return name ();
    ::std::ostringstream res;
    if (known () && xhtml ()) res << "X";
    res << "HTML-5";
    switch (mnr ())
    {   case MINOR_5_0 : res << ".0"; return res.str ();
        case MINOR_5_1 : res << ".1"; return res.str (); 
        case MINOR_5_2 : res << ".2"; return res.str ();
        case MINOR_5_3 : res << ".3"; return res.str (); 
        default : break; }
    switch (mjr ())
    {   case 5 :
            if (mnr () >= HTML_JUL) return "WebApps-2005/Jul";
            return "WebApps-2005/Jan";
        case 6 :
            if (mnr () >= HTML_JUL) return "WebApps-2006/Jul";
            return "WebApps-2006/Jan";
        case 7 :
            if (mnr () >= HTML_JUL) break;
            return "WebApps-2007/Jan";
        default : break; }
    res << "-20";
    if (mjr () < 10) res << "0";
    res << mjr () << "/";
    if (mjr () <= 20)
        if (mnr () >= HTML_JUL) res << "Jul";
        else res << "Jan";
    else if (mnr () >= HTML_DEC) res << "Dec";
    else if (mnr () >= HTML_NOV) res << "Nov";
    else if (mnr () >= HTML_OCT) res << "Oct";
    else if (mnr () >= HTML_SEP) res << "Sep";
    else if (mnr () >= HTML_AUG) res << "Aug";
    else if (mnr () >= HTML_JUL) res << "Jul";
    else if (mnr () >= HTML_JUN) res << "Jun";
    else if (mnr () >= HTML_MAY) res << "May";
    else if (mnr () >= HTML_APR) res << "Apr";
    else if (mnr () >= HTML_MAR) res << "Mar";
    else if (mnr () >= HTML_FEB) res << "Feb";
    else res << "Jan";
    return res.str (); }

::std::string html_version::report () const
{   ::std::ostringstream res;
    res << name ();
    if (any_level ()) res << "." << level ();
    if (strict ()) res << "/Strict";
    if (frameset ()) res << "/Frameset";
    if (transitional ()) res << "/Transitional";
    if (has_svg ()) res << "/SVG-" << svg_version_name ();
    if (has_math ()) res << "/MathML-" << math_version_name ();
    if (has_xlink ()) res << "/xLink";
    if (has_rdfa ()) res << "/RDFa";
    if (has_css ()) res << "/CSS-" << css_version_name ();
    if (chrome ()) res << "/Chrome";
    if (ie ()) res << "/IE";
    if (mozilla ()) res << "/Mozilla";
    if (netscape ()) res << "/Netscape";
    if (opera ()) res << "/Opera";
    if (safari ()) res << "/Safari";
    if (w3 ()) res << "/W3";
    if (webcomponents ()) res << "/WebComponents";
    if (whatwg ()) res << "/WhatWG";
    if (experimental ()) res << "/Experimental";
    if (bespoke ()) res << "/Obscure";
    if (any_flags (HV_DEPRECATED_MASK)) res << "/deprecated";  // not the deprecated function here
    return res.str (); }

bool html_version::note_parsed_version (nitpick& nits, const e_nit n, const html_version& got, const ::std::string& gen)
{   const e_css_version cv = context.css_version ();
    const e_jsonld_version jv = context.jsonld_version ();
    const e_rdf_version rv = context.rdf_version ();
    const uint64_t cm = (context.html_ver ().ext2 () & H2_FULL_CSS_MASK);
    const uint64_t cm3 = (context.html_ver ().ext3 () & H3_FULL_CSS_MASK);
    const uint64_t cm4 = (context.html_ver ().ext4 () & (H4_FULL_CSS_MASK | H4_CSS_VER_MASK));
    const uint64_t cm5 = (context.html_ver ().ext5 () & H5_FULL_CSS_MASK);
    css_ = css_unknown;
    if (is_not (got))
    {   if (got > *this)
        {   bool minor = false;
            switch (this -> mjr ())
            {   case 2 :
                    minor = ((*this == html_2) && ((got == html_2_level_1) || (got == html_2_level_2)));
                    break;
                case 4 :
                    minor = (((*this == xhtml_1_0) && (got == xhtml_1_1)) || ((*this == html_4_0) && (got == html_4_1)));
                    break;
                case 1 :
                case 5 :
                    minor = (got.mjr () == this -> mjr ());
                    break;
                default : break; }
            if (minor) nits.pick (nit_html_contradictory, es_comment, ec_parser, report (), " changed to ", got.report ());
            else nits.pick (nit_html_contradictory, es_warning, ec_parser, report (), " changed to ", got.report ());
            reset (got);
            if (cv > css_none)
            {   set_ext2 (H2_FULL_CSS_MASK, cm);
                set_ext3 (H3_FULL_CSS_MASK, cm3);
                set_ext4 (H4_FULL_CSS_MASK, cm4);
                set_ext5 (H5_FULL_CSS_MASK, cm5); }
            if (jv > jsonld_none) jsonld_version (jv);
            if (rv > rdf_none) rdf_version (rv);
            return true; }
        if (got.has_svg ())
            if (! has_svg () || (got.svg_version () >= svg_version ()))
            {   nits.pick (nit_svg, es_comment, ec_parser, "SVG recognised");
                math_version (got.math_version ());
                return true; }
        if (got.has_math ())
            if (! has_math ())
            {   nits.pick (nit_svg, es_comment, ec_parser, "MathML recognised");
                svg_version (got.svg_version ());
                return true; }
        nits.pick (nit_html_contradictory, es_warning, ec_parser, "contradictory ", gen, " statement encountered");
        return true; }
    if (unknown ())
    {   nits.pick (n, es_comment, ec_parser, gen, " recognised");
        reset (got);
        if (cv > css_none)
        {   set_ext2 (H2_FULL_CSS_MASK, cm);
            set_ext3 (H3_FULL_CSS_MASK, cm3);
            set_ext4 (H4_FULL_CSS_MASK, cm4);
            set_ext5 (H5_FULL_CSS_MASK, cm5); }
        if (jv > jsonld_none) jsonld_version (jv);
        if (rv > rdf_none) rdf_version (rv); }
    return true; }

bool html_version::invalid_addendum (const html_version& v) const noexcept
{   if (microdata ())
        if (context.microdata ()) return false;
        else return v.w3 ();
    if (rdfa ())
        if (context.has_rdfa ()) return false;
        else return ((v != xhtml_2) && (! v.is_svg_12 ()));
    return (frameset () && ! v.frameset ()); }

bool html_version::parse_doctype (nitpick& nits, const::std::string& content)
{   nits.set_context (0, trim_the_lot_off (content));
    css_ = css_unknown;
    if (! compare_no_case (doctype, content.substr (0, doctype_len)))
    {   nits.pick (nit_html_unknown_sgml, es_error, ec_parser, content.substr (0, doctype_len), " is not understood by " PROG);
        return true; }
    bool found_html = false;
    bool found_jan05 = false;
    bool found_math = false;
    bool found_svg = false;
    bool found_xhtml = false;
    bool found_public = false;
    bool found_system = false;
    bool found_unknown = false;
    bool sq_brac_ket = false;
    ::std::string::size_type pos = doctype_len;
    ::std::string wtf;
    vstr_t keywords = split_quoted_by_space (trim_the_lot_off (content.substr (pos)));
    if (keywords.empty ())
    {   nits.pick (nit_html_unrecognised, es_error, ec_parser, "Document type not specified. This does not appear to be an HTML file. Abandoning verification");
        return false; }
    for (auto s : keywords)
        if (! s.empty ())  // empty should never happen, but ...
        {   if (sq_brac_ket)
            {   if (s != "]") continue;  // broken by nesting, if it's permitted
                sq_brac_ket = false; }
            if (s.at (0) == '"') s = s.substr (1);  // crude way to remove excess "
            pos = s.length ();
            if (pos == 0) continue;
            if (s.at (pos - 1) == '"') s = s.substr (0, pos - 1);
            e_sgml d = symbol < html_version, e_sgml > :: find (html_0, s); // crude way to handle case
            if (d == doc_unknown) d = symbol < html_version, e_sgml > :: find (html_0, ::boost::algorithm::to_lower_copy (s));
            switch (d)
            {   case doc_unknown : found_unknown = true; wtf = s; break;
                case doc_html : found_html = true; break;
                case doc_public: found_public = true; break;
                case doc_system: found_system = true; break;
                case doc_context :
                    nits.pick (nit_html_unrecognised, es_info, ec_parser, "bespoke SGML specification encountered; am pretending it's HTML 5");
                    note_parsed_version (nits, nit_html_5_0, html_5_0, "HTML 5");
                    break;
                case doc_math :
                case doc_svg :
                case doc_rdf :
                    break;
                case doc_math1 :
                    if (note_parsed_version (nits, nit_math, html_4_0, "HTML 4.0 with MathML 1"))
                    {   set_ext2 (H2_MATH_1); found_math = found_html = true; }
                    break;
                case doc_math2 :
                    if (note_parsed_version (nits, nit_math, xhtml_1_0, "XHTML 1.0 with MathML 2"))
                    {   set_ext2 (H2_MATH_2); found_math = found_html = true; }
                    break;
                case doc_math3 :
                    if (note_parsed_version (nits, nit_math, html_5_0, "HTML 5.0 with MathML 3"))
                    {   set_ext2 (H2_MATH_3); found_math = found_html = true; }
                    break;
                case doc_math4 :
                    if (note_parsed_version (nits, nit_math, html_apr21, "Living Standard (April 2021) with MathML 4"))
                    {   set_ext2 (H2_MATH_4); found_math = found_html = true; }
                    break;
                case doc_html_aria :
                    if (note_parsed_version (nits, nit_html_4_01, html_4_1, "HTML 4.01 + ARIA 1.0"))
                    {   set_flags (HV_TRANSITIONAL); found_html = true; }
                    break;
                case doc_svg10 :
                    if (note_parsed_version (nits, nit_svg, xhtml_svg_1_0, "HTML 4.00 with SVG 1.0"))
                    {   svg_version (sv_1_0); found_svg = found_html = true; }
                    break;
                case doc_svg11 :
                    if (note_parsed_version (nits, nit_svg, xhtml_svg_1_1, "XHTML 1.1 with SVG 1.1"))
                    {   svg_version (sv_1_1); found_svg = found_html = true; }
                    break;
                case doc_svg20 :
                    if (note_parsed_version (nits, nit_svg, html_svg_2_0, "Living Standard (October 2018) with SVG 2.0"))
                    {   svg_version (sv_2_0); found_svg = found_html = true; }
                    break;
                case doc_svg21 :
                    if (note_parsed_version (nits, nit_svg, html_svg_2_1, "Living Standard (October 2024) with SVG 2 (November 2024 draft)"))
                    {   svg_version (sv_2_1); found_svg = found_html = true; }
                    break;
                case doc_compound_m :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, 0, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with MathML 2"))
                    {   set_ext2 (H2_MATH_2); math_version (math_2); found_math = found_xhtml = found_html = true; }
                    break;
                case doc_compound_1_0 :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, HE_SVG_10, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with SVG 1.0 & MathML 2"))
                    {   set_ext2 (H2_MATH_2); set_ext (HE_SVG_10); math_version (math_2); svg_version (sv_1_0);
                        found_math = found_svg = found_xhtml = found_html = true; }
                    break;
                case doc_compound_1_1 :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, HE_SVG_11, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with SVG 1.1 & MathML 2"))
                    {   set_ext2 (H2_MATH_2); set_ext (HE_SVG_11); math_version (math_2); svg_version (sv_1_1);
                        found_math = found_svg = found_xhtml = found_html = true; }
                    break;
                case doc_xhtml10_basic :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Basic")) set_flags (HV_BASIC);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml10_strict_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that strict XHTML 1.0 declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_strict :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Strict")) set_flags (HV_STRICT);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml10_loose_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that transitional XHTML 1.0 declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_loose :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Transitional")) set_flags (HV_TRANSITIONAL);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml10_frameset_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that XHTML 1.0 frameset declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_frameset :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Frameset")) set_flags (HV_FRAMESET);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml10_mobile :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Mobile")) set_flags (HV_BASIC);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml11 :
                    note_parsed_version (nits, nit_xhtml_1_1, xhtml_1_1, "XHTML 1.1");
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_xhtml2 :
                    note_parsed_version (nits, nit_xhtml_2_0, xhtml_2, "XHTML 2.0");
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    found_xhtml = true;
                    break;
                case doc_jan05 :
                    nits.pick (nit_draft_html_5, ed_jan05, "", es_warning, ec_parser, PROG " cannot properly process pre-draft HTML 5");
                    note_parsed_version (nits, nit_draft_html_5, html_jan05, "Web Apps Jan 2005");
                    found_jan05 = true;
                    break;
                case doc_html5 :
                    note_parsed_version (nits, nit_html_5_0, html_5_0, "HTML 5");
                    break;
                case doc_html400_strict :
                    if (note_parsed_version (nits, nit_html_4_00s, html_4_0, "HTML 4.00 Strict")) set_flags (HV_STRICT);
                    break;
                case doc_html400_loose :
                    note_parsed_version (nits, nit_html_4_00, html_4_0, "HTML 4.00");
                    break;
                case doc_html400_frameset :
                    if (note_parsed_version (nits, nit_html_4_00f, html_4_0, "HTML 4.00 Frameset")) set_flags (HV_FRAMESET);
                    break;
                case doc_latin :
                case doc_special :
                case doc_symbols :
                    break;
                case doc_html401_strict_superseded :
                    nits.pick (nit_html_superseded, ed_41, "21 Document Type Definition", es_warning, ec_parser, "that strict HTML .dtd was withdrawn (consider /html40/, not /html4/)");
                    FALLTHROUGH;
                case doc_html401_strict :
                    if (note_parsed_version (nits, nit_html_4_01s, html_4_1, "HTML 4.01 Strict")) set_flags (HV_STRICT);
                    break;
                case doc_html401_loose_superseded :
                    nits.pick (nit_html_superseded, ed_41, "21 Document Type Definition", es_warning, ec_parser, "that transitional HTML .dtd was withdrawn (consider /html40/, not /html4/)");
                    FALLTHROUGH;
                case doc_html401_loose :
                    if (note_parsed_version (nits, nit_html_4_01, html_4_1, "HTML 4.01 Transitional")) set_flags (HV_TRANSITIONAL);
                    break;
                case doc_html401_frameset_superseded :
                    nits.pick (nit_html_superseded, ed_41, "21 Document Type Definition", es_warning, ec_parser, "that HTML frameset .dtd was withdrawn");
                    FALLTHROUGH;
                case doc_html401_frameset :
                    if (note_parsed_version (nits, nit_html_4_01f, html_4_1, "HTML 4.01 Frameset")) set_flags (HV_FRAMESET);
                    break;
                case doc_html30 :
                    note_parsed_version (nits, nit_html_3_0, html_3_0, "HTML 3.0");
                    break;
                case doc_html32 :
                    note_parsed_version (nits, nit_html_3_2, html_3_2, "HTML 3.2");
                    break;
                case doc_html20 :
                    note_parsed_version (nits, nit_html_2_0, html_2, "HTML 2.0");
                    break;
                case doc_html20_strict :
                    if (note_parsed_version (nits, nit_html_2_0s, html_2, "HTML 2.0 Strict")) set_flags (HV_STRICT);
                    break;
                case doc_html20_int :
                    if (! context.rfc_2070 ())
                    {   nits.pick (nit_rfc_2070, es_error, ec_parser, "HTML 2.0 International (RFC 2070), which is disabled: abandoning verification");
                        return false; }
                    if (note_parsed_version (nits, nit_html_2_0i, html_2, "HTML 2.0 International"))
                    {   set_flags (HV_INT); found_html = true; }
                    break;
                case doc_html21 :
                    if (note_parsed_version (nits, nit_html_2_0l1, html_2_level_1, "HTML 2.0 Level 1")) 
                    {   set_flags (HV_LEVEL1); found_html = true; }
                    break;
                case doc_html21_strict :
                    if (note_parsed_version (nits, nit_html_2_0l1s, html_2, "HTML 2.0 Level 1 Strict")) 
                    {   set_flags (HV_STRICT | HV_LEVEL1); found_html = true; }
                    break;
                case doc_html22 :
                    if (note_parsed_version (nits, nit_html_2_0l2, html_2_level_2, "HTML 2.0 Level 2")) 
                    {   set_flags (HV_LEVEL2); found_html = true; }
                    break;
                case doc_htmlplus :
                    if (note_parsed_version (nits, nit_html_plus, html_plus, "HTML+"))
                        found_html = true;
                    break;
                case doc_html1 :
                    if (note_parsed_version (nits, nit_html_1_0, html_1, "HTML 1.0"))
                    {   found_html = true;
                        nits.pick (nit_html_1_0, es_info, ec_parser, "Really? HTML 1.0?"); }
                    break;
                case doc_html_tags :
                    note_parsed_version (nits, nit_html_tags, html_tags, "HTML Tags");
                        found_html = true;
                    break;
                case doc_rss_91 :
                    set_ext4 (H4_RSS);
                    return true;
                case doc_sqclose :
                    break;
                case doc_sqopen :
                    nits.pick (nit_sq_brac_ket, es_info, ec_parser, "ignoring [ ... ] details in <!DOCTYPE ... >");
                    sq_brac_ket = true;
                    break;
               default :
                    nits.pick (nit_internal_parsing_error, es_catastrophic, ec_parser, "bork! bork! bork! when parsing html_version (", quote (s), "): abandoning hope");
                    return false; } }
    if (found_html)
    {   if (unknown ())
        {   if (found_unknown)
            {   nits.pick (nit_html_unknown_sgml, es_warning, ec_parser, "The HTML declaration in <!DOCTYPE ...> contains unrecognised content (", quote (wtf), "): abandoning verification");
                return false; }
            html_version vvv;
            ::std::string ver;
            e_nit wit = nit_free;
            const e_math_version ev = context.math_version ();
            const e_svg_version sv = context.svg_version ();
            if (context.versioned ())
            {   vvv = context.html_ver ();
                if (vvv.mjr () < 5) vvv = html_default;
                wit = nit_overriding_html;
                ver = vvv.name (); }
            else
            {   vvv = html_default;
                if (vvv == html_5_0) wit = nit_html_5_0;
                else if (vvv == html_5_1) wit = nit_html_5_1;
                else if (vvv == html_5_2) wit = nit_html_5_2;
                else if (vvv == html_5_3) wit = nit_html_5_3;
                else wit = nit_html_5_living;
                ver = "HTML ";
                ver += minor_to_date (vvv); }
            if (ev > math_none) vvv.math_version (ev);
            if (sv > sv_none) vvv.svg_version (sv);
            note_parsed_version (nits, wit, vvv, ver);
            if (found_public)
                nits.pick (nit_public_unexpected, es_warning, ec_parser, "PUBLIC is unexpected"); }
        else if (mjr () >= 5) 
        {   if (found_public && ! (found_jan05 || found_math || found_svg || found_xhtml))
                nits.pick (nit_public_unexpected, es_info, ec_parser, "PUBLIC is unexpected"); }
        else
        {   if (! found_public && ! found_system)
                if ((mjr () > 1) || ((mjr () == 1) && (mnr ()== 1)))
                    nits.pick (nit_public_missing, es_info, ec_parser, "Either PUBLIC or SYSTEM expected");
            if (found_unknown) if (context.tell (es_warning))
                nits.pick (nit_unexpected_doctype_content, ed_doctype, "", es_warning, ec_parser, "Ignoring unexpected content (", quote (wtf), ") found in <!DOCTYPE>"); }
        return true; }
    nits.pick (nit_doctype_incomprehensible, es_catastrophic, ec_parser, PROG " does not understand the <!DOCTYPE> so is abandoning verification");
    return false; }

bool html_version::deprecated (const html_version& current) const
{   switch (context.math_version ())
    {   case math_2 :
            if (current.all_ext2 (H2_M2_DEPRECAT)) return true;
            break;
        case math_3 :
            if (current.all_ext2 (H2_M3_DEPRECAT)) return true;
            break;
        case math_4 :
            if (current.all_ext2 (H2_M4_DEPRECAT)) return true;
            break;
        default : break; }
    if (current.rdf_version () == rdf_deprecated) return true;
    switch (context.svg_version ())
    {   case sv_1_1 :
            if (current.all_ext (HE_SVG_DEPR_11)) return true;
            break;
        case sv_1_2_tiny :
        case sv_1_2_full :
            if (current.all_ext (HE_SVG_DEPR_12)) return true;
            break;
        case sv_2_0 :
            if (current.all_ext (HE_SVG_DEPR_20)) return true;
            break;
        case sv_2_1 :
            if (current.all_ext (HE_SVG_DEPR_21)) return true;
            break;
        default : break; }
    if ((context.css_version () > 0) && current.css_deprecated ()) return true;
    switch (current.mjr ())
    {   case 1 : return (current.any_flags (HV_DEPRECATEDX10));
        case 2 : return (current.any_flags (HV_DEPRECATED2));
        case 3 :
            switch (current.mnr ())
            {   case 0 : return any_flags (HV_DEPRECATED30);
                case 2 : return any_flags (HV_DEPRECATED32);
                default : break; }
            GRACEFUL_CRASH (__FILE__, __LINE__);
            UNBREAKABLE;
        case 4:
            switch (current.mnr ())
            {   case 0 :
                case 1 : return any_flags (HV_DEPRECATED4);
                case 2 : return any_flags (HV_DEPRECATEDX1);
                case 3 : return any_flags (HV_DEPRECATEDX11);
                case 4 : return any_flags (HV_DEPRECATEDX2);
                default : break; }
            GRACEFUL_CRASH (__FILE__, __LINE__);
            UNBREAKABLE;
        default :
            if (current.any_flags (HV_WHATWG))
                if (any_flags (HV_DEPRECATEDWWG))
                    return true;
            switch (w3_minor_5 (current))
            {   case 0 : return any_flags (HV_DEPRECATED50);
                case 1 : return any_flags (HV_DEPRECATED51);
                case 2 : return any_flags (HV_DEPRECATED52);
                case 3 : return any_flags (HV_DEPRECATED53);
                default : break; } }
    return false; }

bool html_version::lazy () const noexcept
{   if (is_2_or_more ()) return true;
    if (is_0 ()) return false;
    return (mnr () > 0); }

bool test_not_extension (const html_version& lhs, const html_version& rhs) noexcept
{   switch (lhs.svg_version ())
    {   case sv_1_0 : return rhs.not_svg_10 ();
        case sv_1_1 : return rhs.not_svg_11 ();
        case sv_1_2_tiny :
        case sv_1_2_full :
                      return rhs.not_svg_12 ();
        case sv_2_0 : return rhs.not_svg_20 ();
        case sv_2_1 : return rhs.not_svg_21 ();
        default : break; }
    return false; }

// have encountered occasional bugs with 64 bit manipulation on some platforms (a & b), but the &= operator appears reliable, so ...
bool is_excluded (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    flags_t a = mask, b = mask;
    a &= lhs.ext ();
    b &= rhs.ext ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

bool is_excluded2 (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    flags_t a = mask, b = mask;
    a &= lhs.ext2 ();
    b &= rhs.ext2 ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

bool is_excluded3 (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    flags_t a = mask, b = mask;
    a &= lhs.ext3 ();
    b &= rhs.ext3 ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

bool is_excluded4 (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    flags_t a = mask, b = mask;
    a &= lhs.ext4 ();
    b &= rhs.ext4 ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

bool is_excluded5 (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    flags_t a = mask, b = mask;
    a &= lhs.ext5 ();
    b &= rhs.ext5 ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

e_emi rdfa_conflict (const html_version& lhs, const html_version& rhs)
{   PRESUME (! lhs.is_b4_4 (), __FILE__, __LINE__);
    PRESUME (rhs.has_rdfa (), __FILE__, __LINE__);
    if ((lhs != xhtml_2) && (! lhs.is_svg_12 ()))
        if (! context.has_rdfa () && ! lhs.has_rdfa ()) return emi_rdfa;
    return emi_good; }

e_emi math_conflict (const html_version& lhs, const html_version& rhs)
{   PRESUME (! lhs.is_b4_4 (), __FILE__, __LINE__);
    PRESUME (rhs.has_math (), __FILE__, __LINE__);
    if (! lhs.has_math ()) return emi_math;
    if (is_excluded2 (lhs, rhs, MATH_MASK)) return emi_not_this_math;
    return emi_good; }

e_emi svg_conflict (const html_version& lhs, const html_version& rhs)
{   PRESUME (! lhs.is_b4_4 (), __FILE__, __LINE__);
    PRESUME (rhs.has_svg (), __FILE__, __LINE__);
    if (! lhs.has_svg ()) return emi_svg;
    if (lhs.is_4 ())
    {   if (rhs.svg_x2 () && (lhs == xhtml_2)) return emi_good;
        if (rhs.svg_old_html ()) return emi_good; }
    else if (lhs < html_jul08) return emi_good;
    if (rhs.any_ext2 (H2_CSS_SVG))
        if (lhs.is_css_compatible (rhs.ext2 (), rhs.ext3 (), rhs.ext4 (), rhs.ext5 ()))
            switch (lhs.svg_version ())
            {   case sv_1_0 :
                    if (rhs.any_ext2 (H2_CSS_SVG_10)) return emi_good;
                    break;
                case sv_1_1 :
                    if (rhs.any_ext2 (H2_CSS_SVG_11)) return emi_good;
                    break;
                case sv_1_2_tiny :
                case sv_1_2_full :
                    if (rhs.any_ext2 (H2_CSS_SVG_12)) return emi_good;
                    break;
                case sv_2_0 :
                    if (rhs.any_ext2 (H2_CSS_SVG_20)) return emi_good;
                    break;
                case sv_2_1 :
                    if (rhs.any_ext2 (H2_CSS_SVG_21)) return emi_good;
                    break;
                default :
                    break; }
    if (is_excluded (lhs, rhs, SVG_MASK)) return emi_not_this_svg;
    if (test_not_extension (lhs, rhs)) return emi_not_this_svg;
    return emi_good; }

e_emi extension_conflict (const html_version& lhs, const html_version& rhs)
{   if (lhs >= xhtml_1_0)
    {   e_emi r = emi_untested, m = emi_untested, s = emi_untested;
        if (rhs.has_math ()) { m = math_conflict (lhs, rhs); if (m == emi_good) return emi_good; }
        if (rhs.has_svg ()) { s = svg_conflict (lhs, rhs); if (s == emi_good) return emi_good; }
        if (rhs.has_rdfa ()) { r = rdfa_conflict (lhs, rhs); if (r == emi_good) return emi_good; }
        if ((s != emi_untested) && (m != emi_untested)) return emi_math_svg;
        if (m != emi_untested) return m;
        if (s != emi_untested) return s;
        if (r != emi_untested) return r; }
    return emi_good; }

bool html_version::check_math_svg (nitpick& nits, const html_version& a, const ::std::string& x) const
{   switch (extension_conflict (*this, a))
    {   case emi_math :
            nits.pick (nit_math, es_error, ec_attribute, quote (x), " requires MathML"); return false;
        case emi_not_this_math :
            nits.pick (nit_math, es_error, ec_attribute, quote (x), " requires another version of MathML"); return false;
        case emi_math_svg :
            nits.pick (nit_math_or_svg, es_error, ec_attribute, quote (x), " requires MathML or SVG"); return false;
        case emi_not_svg :
            nits.pick (nit_svg, es_error, ec_attribute, quote (x), " cannot be applied to SVG elements"); return false;
        case emi_not_this_svg :
            nits.pick (nit_svg, es_error, ec_attribute, quote (x), " cannot be applied to SVG elements here"); return false;
        case emi_svg :
            nits.pick (nit_svg, es_error, ec_attribute, quote (x), " requires SVG"); return false;
        case emi_rdfa :
            nits.pick (nit_rdf, es_error, ec_attribute, quote (x), " requires RDFa"); return false;
        default : break; }
    return true; }

bool html_version::has_this_css (const flags_t f2, const flags_t f3, const flags_t f4, const flags_t f5) const noexcept
{   return  ((ext2 () & f2) == f2) &&
            ((ext3 () & f3) == f3) &&
            ((ext4 () & f4) == f4) &&
            ((ext5 () & f5) == f5); }

e_css_version html_version::css_version () const noexcept
{   if (css_ < css_unknown) return css_;
    if (has_this_css (H2_CSS_6_FULL, H3_CSS_6_FULL, H4_CSS_6_FULL, H5_CSS_6_FULL)) css_ = css_6;
    else if (has_this_css (H2_CSS_5_FULL, H3_CSS_5_FULL, H4_CSS_5_FULL, H5_CSS_5_FULL)) css_ = css_5;
    else if (has_this_css (H2_CSS_4_FULL, H3_CSS_4_FULL, H4_CSS_4_FULL, H4_CSS_4_FULL)) css_ = css_4;
    else if (has_this_css (H2_CSS_3_FULL, H3_CSS_3_FULL, H4_CSS_3_FULL, H5_CSS_3_FULL)) css_ = css_3;
    else if (has_this_css (H2_CSS_LS_2026, H3_CSS_LS_2026, H4_CSS_LS_2026, H5_CSS_LS_2026)) css_ = css_ls_2026;
    else if (has_this_css (H2_CSS_2026_3, H3_CSS_2026_3, H4_CSS_2026_3, H5_CSS_2026_3)) css_ = css_2026_3;
    else if (has_this_css (H2_CSS_2026_2, H3_CSS_2026_2, H4_CSS_2026_2, H5_CSS_2026_2)) css_ = css_2026_2;
    else if (has_this_css (H2_CSS_2026_1, H3_CSS_2026_1, H4_CSS_2026_1, H5_CSS_2026_1)) css_ = css_2026_1;
    else if (has_this_css (H2_CSS_2026, H3_CSS_2026, H4_CSS_2026, H5_CSS_2026)) css_ = css_2026;
    else if (has_this_css (H2_CSS_LS_2025, H3_CSS_LS_2025, H4_CSS_LS_2025, H5_CSS_LS_2025)) css_ = css_ls_2025;
    else if (has_this_css (H2_CSS_2025_3, H3_CSS_2025_3, H4_CSS_2025_3, H5_CSS_2025_3)) css_ = css_2025_3;
    else if (has_this_css (H2_CSS_2025_2, H3_CSS_2025_2, H4_CSS_2025_2, H5_CSS_2025_2)) css_ = css_2025_2;
    else if (has_this_css (H2_CSS_2025_1, H3_CSS_2025_1, H4_CSS_2025_1, H5_CSS_2025_1)) css_ = css_2025_1;
    else if (has_this_css (H2_CSS_2025, H3_CSS_2025, H4_CSS_2025, H5_CSS_2025)) css_ = css_2025;
    else if (has_this_css (H2_CSS_LS_2024, H3_CSS_LS_2024, H4_CSS_LS_2024, H5_CSS_LS_2024)) css_ = css_ls_2024;
    else if (has_this_css (H2_CSS_2024_3, H3_CSS_2024_3, H4_CSS_2024_3, H5_CSS_2024_3)) css_ = css_2024_3;
    else if (has_this_css (H2_CSS_2024_2, H3_CSS_2024_2, H4_CSS_2024_2, H5_CSS_2024_2)) css_ = css_2024_2;
    else if (has_this_css (H2_CSS_2024_1, H3_CSS_2024_1, H4_CSS_2024_1, H5_CSS_2024_1)) css_ = css_2024_1;
    else if (has_this_css (H2_CSS_2024, H3_CSS_2024, H4_CSS_2024, H5_CSS_2024)) css_ = css_2024;
    else if (has_this_css (H2_CSS_2023_2, H3_CSS_2023_2, H4_CSS_2023_2, H5_CSS_2023_2)) css_ = css_2023_2;
    else if (has_this_css (H2_CSS_2023_1, H3_CSS_2023_1, H4_CSS_2023_1, H5_CSS_2023_1)) css_ = css_2023_1;
    else if (has_this_css (H2_CSS_2023, H3_CSS_2023, H4_CSS_2023, H5_CSS_2023)) css_ = css_2023;
    else if (has_this_css (H2_CSS_2022_2, H3_CSS_2022_2, H4_CSS_2022_2, H5_CSS_2022_2)) css_ = css_2022_2;
    else if (has_this_css (H2_CSS_2022_1, H3_CSS_2022_1, H4_CSS_2022_1, H5_CSS_2023_2)) css_ = css_2022_1;
    else if (has_this_css (H2_CSS_2022, H3_CSS_2022, H4_CSS_2022, H5_CSS_2022)) css_ = css_2022;
    else if (has_this_css (H2_CSS_2021_2, H3_CSS_2021_2, H4_CSS_2021_2, H5_CSS_2021_2)) css_ = css_2021_2;
    else if (has_this_css (H2_CSS_2021_1, H3_CSS_2021_1, H4_CSS_2021_1, H5_CSS_2021_2)) css_ = css_2021_1;
    else if (has_this_css (H2_CSS_2021, H3_CSS_2021, H4_CSS_2021, H5_CSS_2021)) css_ = css_2021;
    else if (has_this_css (H2_CSS_2020_2, H3_CSS_2020_2, H4_CSS_2020_2, H5_CSS_2020_2)) css_ = css_2020_2;
    else if (has_this_css (H2_CSS_2020_1, H3_CSS_2020_1, H4_CSS_2020_1, H5_CSS_2020_2)) css_ = css_2020_1;
    else if (has_this_css (H2_CSS_2020, H3_CSS_2020, H4_CSS_2020, H5_CSS_2020)) css_ = css_2020;
    else if (has_this_css (H2_CSS_2018_2, H3_CSS_2018_2, H4_CSS_2018_2, H5_CSS_2018_2)) css_ = css_2018_2;
    else if (has_this_css (H2_CSS_2018_1, H3_CSS_2018_1, H4_CSS_2018_1, H5_CSS_2018_2)) css_ = css_2018_1;
    else if (has_this_css (H2_CSS_2018, H3_CSS_2018, H4_CSS_2018, H5_CSS_2018)) css_ = css_2018;
    else if (has_this_css (H2_CSS_2017_2, H3_CSS_2017_2, H4_CSS_2017_2, H5_CSS_2017_2)) css_ = css_2017_2;
    else if (has_this_css (H2_CSS_2017_1, H3_CSS_2017_1, H4_CSS_2017_1, H5_CSS_2017_2)) css_ = css_2017_1;
    else if (has_this_css (H2_CSS_2017, H3_CSS_2017, H4_CSS_2017, H5_CSS_2017)) css_ = css_2017;
    else if (has_this_css (H2_CSS_2015_2, H3_CSS_2015_2, H4_CSS_2015_2, H5_CSS_2015_2)) css_ = css_2015_2;
    else if (has_this_css (H2_CSS_2015_1, H3_CSS_2015_1, H4_CSS_2015_1, H5_CSS_2015_2)) css_ = css_2015_1;
    else if (has_this_css (H2_CSS_2015, H3_CSS_2015, H4_CSS_2015, H5_CSS_2015)) css_ = css_2015;
    else if (has_this_css (H2_CSS_2010, H3_CSS_2010, H4_CSS_2010, H5_CSS_2010)) css_ = css_2010;
    else if (has_this_css (H2_CSS_2007, H3_CSS_2007, H4_CSS_2007, H5_CSS_2007)) css_ = css_2007;
    else if (all_ext2 (H2_CSS_2_2)) css_ = css_2_2;
    else if (all_ext2 (H2_CSS_2_1)) css_ = css_2_1;
    else if (all_ext2 (H2_CSS_2_0)) css_ = css_2_0;
    else if (all_ext2 (H2_CSS_1)) css_ = css_1;
    else css_ = css_none;
    return css_; }

bool html_version::compare_css (const flags_t e2, const flags_t e3, const flags_t e4, const flags_t e5, flags_t& ext2, flags_t& ext3, flags_t& ext4, flags_t& ext5) const
{   if (! all_ext2 (e2)) return false;
    if ((e3 != 0) && ! all_ext3 (e3)) return false;
    if ((e4 != 0) && ! all_ext4 (e4)) return false;
    if ((e5 != 0) && ! all_ext5 (e5)) return false;
    ext2 = e2;
    ext3 = e3;
    ext4 = e4;
    ext5 = e5;
    return true; }

::std::string big_small_start (const bool b, const char* klein, const char* gross)
{   VERIFY_NOT_NULL (klein, __FILE__, __LINE__);
    VERIFY_NOT_NULL (gross, __FILE__, __LINE__);
    if (b) return gross;
    return klein; }

::std::string big_small (const ::std::string& x, const bool b, const char* klein, const char* gross, const char* level = nullptr)
{   VERIFY_NOT_NULL (klein, __FILE__, __LINE__);
    VERIFY_NOT_NULL (gross, __FILE__, __LINE__);
    ::std::string plus;
    if (! x.empty ())
        if (b) plus = " + ";
        else plus = "+";
    if (level == nullptr)
    {   if (b) return plus + gross;
        return plus + klein; }
    if (b) return plus + gross + " level " + level;
    return plus + klein +"/" + level; }

::std::string single_feature (const ::std::string& x, const bool b, const char* klein, const char* gross, const flags_t ext, const flags_t e, const flags_t f3, const flags_t f4 = NOFLAGS, const flags_t f5 = NOFLAGS, const flags_t f6 = NOFLAGS)
{   ::std::string res;
    if ((f6 != 0) && ((f6 & ext) == f6) && (f6 && e) == 0) return big_small (x, b, klein, gross, "6"); 
    if ((f5 != 0) && ((f5 & ext) == f5) && (f5 && e) == 0) return big_small (x, b, klein, gross, "5"); 
    if (f4 != 0)
    {   if (((f4 & ext) == f4) && (f4 && e) == 0) return big_small (x, b, klein, gross, "4"); 
        if ((f3 != 0) && ((f3 & ext) == f3) && ((f3 && e) == 0)) return big_small (x, b, klein, gross, "3"); }
    else if ((f3 != 0) && ((f3 & ext) == f3) && ((f3 && e) == 0)) return big_small (x, b, klein, gross);
    return ::std::string (); }

::std::string html_version::css_version_text (const bool b) const
{   ::std::string res;
    flags_t e2 = NOFLAGS, e3 = NOFLAGS, e4 = NOFLAGS, e5 = NOFLAGS;
    if (compare_css (H2_CSS_6, H3_CSS_6, H4_CSS_6, H5_CSS_6, e2, e3, e4, e5)) return big_small_start (b, "6", "level 6");
    else if (compare_css (H2_CSS_5, H3_CSS_5, H4_CSS_5, H5_CSS_5, e2, e3, e4, e5)) res = big_small_start (b, "5", "level 5");
    else if (compare_css (H2_CSS_4, H3_CSS_4, H4_CSS_4, H5_CSS_4, e2, e3, e4, e5)) res = big_small_start (b, "4", "level 4");
    else if (compare_css (H2_CSS_3, H3_CSS_3, H4_CSS_3, H5_CSS_4, e2, e3, e4, e5)) res = big_small_start (b, "3", "level 3");
    else if (compare_css (H2_CSS_LS_2026, H3_CSS_LS_2026, H4_CSS_LS_2026, H5_CSS_LS_2026, e2, e3, e4, e5)) res = big_small_start (b, "5/26", "HTML5 CSS/26");
    else if (compare_css (H2_CSS_2026_3, H3_CSS_2026_3, H4_CSS_2026_3, H5_CSS_LS_2026, e2, e3, e4, e5)) res = big_small_start (b, "26+++", "2026+++ snapshot");
    else if (compare_css (H2_CSS_2026_2, H3_CSS_2026_2, H4_CSS_2026_2, H5_CSS_LS_2026, e2, e3, e4, e5)) res = big_small_start (b, "26++", "2026++ snapshot");
    else if (compare_css (H2_CSS_2026_1, H3_CSS_2026_1, H4_CSS_2026_1, H5_CSS_LS_2026, e2, e3, e4, e5)) res = big_small_start (b, "26+", "2026+ snapshot");
    else if (compare_css (H2_CSS_2026, H3_CSS_2026, H4_CSS_2026, H5_CSS_2026, e2, e3, e4, e5)) res = big_small_start (b, "26", "2026 snapshot");
    else if (compare_css (H2_CSS_LS_2025, H3_CSS_LS_2025, H4_CSS_LS_2025, H5_CSS_LS_2025, e2, e3, e4, e5)) res = big_small_start (b, "5/25", "HTML5 CSS/25");
    else if (compare_css (H2_CSS_2025_3, H3_CSS_2025_3, H4_CSS_2025_3, H5_CSS_LS_2025, e2, e3, e4, e5)) res = big_small_start (b, "25+++", "2025+++ snapshot");
    else if (compare_css (H2_CSS_2025_2, H3_CSS_2025_2, H4_CSS_2025_2, H5_CSS_LS_2025, e2, e3, e4, e5)) res = big_small_start (b, "25++", "2025++ snapshot");
    else if (compare_css (H2_CSS_2025_1, H3_CSS_2025_1, H4_CSS_2025_1, H5_CSS_LS_2025, e2, e3, e4, e5)) res = big_small_start (b, "25+", "2025+ snapshot");
    else if (compare_css (H2_CSS_2025, H3_CSS_2025, H4_CSS_2025, H5_CSS_2025, e2, e3, e4, e5)) res = big_small_start (b, "25", "2025 snapshot");
    else if (compare_css (H2_CSS_LS_2024, H3_CSS_LS_2024, H4_CSS_LS_2024, H5_CSS_LS_2024, e2, e3, e4, e5)) res = big_small_start (b, "5/24", "HTML5 CSS/24");
    else if (compare_css (H2_CSS_2024_3, H3_CSS_2024_3, H4_CSS_2024_3, H5_CSS_2024_3, e2, e3, e4, e5)) res = big_small_start (b, "24+++", "2024+++ snapshot");
    else if (compare_css (H2_CSS_2024_2, H3_CSS_2024_2, H4_CSS_2024_2, H5_CSS_2024_2, e2, e3, e4, e5)) res = big_small_start (b, "24++", "2024++ snapshot");
    else if (compare_css (H2_CSS_2024_1, H3_CSS_2024_1, H4_CSS_2024_1, H5_CSS_2024_1, e2, e3, e4, e5)) res = big_small_start (b, "24+", "2024+ snapshot");
    else if (compare_css (H2_CSS_2024, H3_CSS_2024, H4_CSS_2024, H5_CSS_2024, e2, e3, e4, e5)) res = big_small_start (b, "24", "2024 snapshot");
    else if (compare_css (H2_CSS_2023_2, H3_CSS_2023_2, H4_CSS_2023_2, H5_CSS_2023_2, e2, e3, e4, e5)) res = big_small_start (b, "23++", "2023++ snapshot");
    else if (compare_css (H2_CSS_2023_1, H3_CSS_2023_1, H4_CSS_2023_1, H5_CSS_2023_1, e2, e3, e4, e5)) res = big_small_start (b, "23+", "2023+ snapshot");
    else if (compare_css (H2_CSS_2023, H3_CSS_2023, H4_CSS_2023, H5_CSS_2023, e2, e3, e4, e5)) res = big_small_start (b, "23", "2023 snapshot");
    else if (compare_css (H2_CSS_2022_2, H3_CSS_2022_2, H4_CSS_2022_2, H5_CSS_2022_2, e2, e3, e4, e5)) res = big_small_start (b, "22++", "2022++ snapshot");
    else if (compare_css (H2_CSS_2022_1, H3_CSS_2022_1, H4_CSS_2022_1, H5_CSS_2022_1, e2, e3, e4, e5)) res = big_small_start (b, "22+", "2022+ snapshot");
    else if (compare_css (H2_CSS_2022, H3_CSS_2022, H4_CSS_2022, H5_CSS_2022, e2, e3, e4, e5)) res = big_small_start (b, "22", "2022 snapshot");
    else if (compare_css (H2_CSS_2021_2, H3_CSS_2021_2, H4_CSS_2021_2, H5_CSS_2021_2, e2, e3, e4, e5)) res = big_small_start (b, "21++", "2021++ snapshot");
    else if (compare_css (H2_CSS_2021_1, H3_CSS_2021_1, H4_CSS_2021_1, H5_CSS_2021_1, e2, e3, e4, e5)) res = big_small_start (b, "21+", "2021+ snapshot");
    else if (compare_css (H2_CSS_2021, H3_CSS_2021, H4_CSS_2021, H5_CSS_2021, e2, e3, e4, e5)) res = big_small_start (b, "21", "2021 snapshot");
    else if (compare_css (H2_CSS_2020_2, H3_CSS_2020_2, H4_CSS_2020_2, H5_CSS_2020_2, e2, e3, e4, e5)) res = big_small_start (b, "20++", "2020++ snapshot");
    else if (compare_css (H2_CSS_2020_1, H3_CSS_2020_1, H4_CSS_2020_1, H5_CSS_2020_1, e2, e3, e4, e5)) res = big_small_start (b, "20+", "2020+ snapshot");
    else if (compare_css (H2_CSS_2020, H3_CSS_2020, H4_CSS_2020, H5_CSS_2020, e2, e3, e4, e5)) res = big_small_start (b, "20", "2020 snapshot");
    else if (compare_css (H2_CSS_2018_2, H3_CSS_2018_2, H4_CSS_2018_2, H5_CSS_2018_2, e2, e3, e4, e5)) res = big_small_start (b, "18++", "2018++ snapshot");
    else if (compare_css (H2_CSS_2018_1, H3_CSS_2018_1, H4_CSS_2018_1, H5_CSS_2018_1, e2, e3, e4, e5)) res = big_small_start (b, "18+", "2018+ snapshot");
    else if (compare_css (H2_CSS_2018, H3_CSS_2018, H4_CSS_2018, H5_CSS_2018, e2, e3, e4, e5)) res = big_small_start (b, "18", "2018 snapshot");
    else if (compare_css (H2_CSS_2017_2, H3_CSS_2017_2, H4_CSS_2017_2, H5_CSS_2017_2, e2, e3, e4, e5)) res = big_small_start (b, "17++", "2017++ snapshot");
    else if (compare_css (H2_CSS_2017_1, H3_CSS_2017_1, H4_CSS_2017_1, H5_CSS_2017_1, e2, e3, e4, e5)) res = big_small_start (b, "17+", "2017+ snapshot");
    else if (compare_css (H2_CSS_2017, H3_CSS_2017, H4_CSS_2017, H5_CSS_2017, e2, e3, e4, e5)) res = big_small_start (b, "17", "2017 snapshot");
    else if (compare_css (H2_CSS_2015_2, H3_CSS_2015_2, H4_CSS_2015_2, H5_CSS_2015_2, e2, e3, e4, e5)) res = big_small_start (b, "15++", "2015++ snapshot");
    else if (compare_css (H2_CSS_2015_1, H3_CSS_2015_1, H4_CSS_2015_1, H5_CSS_2015_1, e2, e3, e4, e5)) res = big_small_start (b, "15+", "2015+ snapshot");
    else if (compare_css (H2_CSS_2015, H3_CSS_2015, H4_CSS_2015, H5_CSS_2015, e2, e3, e4, e5)) res = big_small_start (b, "15", "2015 snapshot");
    else if (compare_css (H2_CSS_2010, H3_CSS_2010, H4_CSS_2010, H5_CSS_2010, e2, e3, e4, e5)) res = big_small_start (b, "10", "2010 snapshot");
    else if (compare_css (H2_CSS_2007, H3_CSS_2007, H4_CSS_2007, H5_CSS_2007, e2, e3, e4, e5)) res = big_small_start (b, "07", "2007 snapshot");
    else if (compare_css (H2_CSS_2_2, 0, 0, 0, e2, e3, e4, e5)) res = "2.2";
    else if (compare_css (H2_CSS_2_1, 0, 0, 0, e2, e3, e4, e5)) res = "2.1";
    else if (compare_css (H2_CSS_2_0, 0, 0, 0, e2, e3, e4, e5)) res = "2.0";
    else if (compare_css (H2_CSS_1, 0, 0, 0, e2, e3, e4, e5)) res = "1";

    res += single_feature (res, b, "AcP", "Anchor Positioning", ext4_, e4, H4_CSS_ANCHOR_POS);
    res += single_feature (res, b, "Adj", "Colour Adjustment", ext3_, e3, H3_CSS_ADJUST);
    res += single_feature (res, b, "Anc", "Scrollbar Anchoring", ext3_, e3, H3_CSS_ANCHOR);
    res += single_feature (res, b, "Ani", "Animation", ext2_, H2_CSS_ANIM_3, H2_CSS_ANIM_4);
    res += single_feature (res, b, "Bac", "Background (and Borders)", ext5_, e5, H5_CSS_BACKGROUND_3, H5_CSS_BACKGROUND_4);
    res += single_feature (res, b, "BrB", "Borders and Boxes", ext5_, e5, 0, H5_CSS_BORD_BOX_4);
    res += single_feature (res, b, "BxA", "Box Alignment", ext3_, e3, H3_CSS_BOX_ALIGN);
    res += single_feature (res, b, "BxM", "Box Model", ext3_, e3, H3_CSS_BOX_MODEL_3, H3_CSS_BOX_MODEL_4);
    res += single_feature (res, b, "BxS", "Box Sizing", ext3_, e3, H3_CSS_BOX_SIZING_3, H3_CSS_BOX_SIZING_4);
    res += single_feature (res, b, "Cas", "Cascade & Inheritance", ext2_, e2, H2_CSS_CASCADE_3, H2_CSS_CASCADE_4, H2_CSS_CASCADE_5, H2_CSS_CASCADE_6);
    res += single_feature (res, b, "Cmp", "Compositing and Blending", ext2_, e2, H2_CSS_COMBLE_3, H2_CSS_COMBLE_4);
    res += single_feature (res, b, "Col", "Colour", ext4_, e4, H4_CSS_COLOUR_3, H4_CSS_COLOUR_4, H4_CSS_COLOUR_5, H4_CSS_COLOUR_6);
    res += single_feature (res, b, "Con", "Contain", ext3_, e3, H3_CSS_CONTAIN_3, H3_CSS_CONTAIN_4, H3_CSS_CONTAIN_5);
    res += single_feature (res, b, "Cnt", "Generated Content", ext3_, e3, H3_CSS_CONTENT);
    res += single_feature (res, b, "CoR", "Conditional Rule", ext2_, e2, H2_CSS_COND_RULE_3, H2_CSS_COND_RULE_4, H2_CSS_COND_RULE_5);
    res += single_feature (res, b, "CoS", "Counter Style", ext2_, e2, H2_CSS_CS);
    res += single_feature (res, b, "Cus", "Custom Properties for Cascading Variables", ext2_, e2, H2_CSS_CUSTOM);
    res += single_feature (res, b, "Dev", "Device Adaption", ext3_, e3, H3_CSS_DEVICE);
    res += single_feature (res, b, "Dsp", "Display", ext5_, e5, H5_CSS_DISPLAY_3, H5_CSS_DISPLAY_4);
    res += single_feature (res, b, "Eas", "Easing Functions", ext5_, e5, H5_CSS_EASE_3, H5_CSS_EASE_4);
    res += single_feature (res, b, "Env", "Environment", ext3_, e3, H3_CSS_ENVIRONMENT);
    res += single_feature (res, b, "Exc", "Exclusions", ext3_, e3, H3_CSS_EXCLUDE);
    res += single_feature (res, b, "Fll", "Fill and Stroke", ext3_, e3, H3_CSS_FILL);
    res += single_feature (res, b, "Fil", "Filter Effects", ext5_, e5, H5_CSS_FILTER_3, H5_CSS_FILTER_4);
    res += single_feature (res, b, "FBL", "Flexible Box Layout", ext2_, e2, H2_CSS_FBL);
    res += single_feature (res, b, "FCS", "Form Control Styling", ext4_, e4, H4_CSS_FCS);
    res += single_feature (res, b, "Fon", "Fonts", ext2_, e2, H2_CSS_FONT_3, H2_CSS_FONT_4, H2_CSS_FONT_5);
    res += single_feature (res, b, "Fra", "Fragmentation", ext2_, e2, H2_CSS_FRAG_3, H2_CSS_FRAG_4);
    res += single_feature (res, b, "Grd", "Grid", ext3_, e3, H3_CSS_GRID_3, H3_CSS_GRID_4);
    res += single_feature (res, b, "HiL", "Custom Highlight", ext3_, e3, H3_CSS_HIGHLIGHT);
    res += single_feature (res, b, "HTM", "HTML5 Living Standard", ext4_, e4, H4_CSS_LIVING_STANDARD);
    res += single_feature (res, b, "Img", "Images", ext3_, e3, H3_CSS_IMAGE_3, H3_CSS_IMAGE_4, H3_CSS_IMAGE_5);
    res += single_feature (res, b, "Inl", "Inline Layout", ext3_, e3, H3_CSS_INLINE);
    res += single_feature (res, b, "LnG", "Lists and Counters", ext3_, e3, H3_CSS_LINE_GRID);
    res += single_feature (res, b, "Lst", "Line Grid", ext3_, e3, H3_CSS_LIST);
    res += single_feature (res, b, "Log", "Logical Properties and Values", ext3_, e3, H3_CSS_LOGIC);
    res += single_feature (res, b, "Mrq", "Marquee", ext4_, e4, H4_CSS_ADVLAY);
    res += single_feature (res, b, "Mrq", "Marquee", ext4_, e4, H4_CSS_MARQUEE);
    res += single_feature (res, b, "Msk", "Masking", ext3_, e3, H3_CSS_MASKING);
    res += single_feature (res, b, "MCr", "Math Core", ext4_, e4, H4_CSS_MATH_CORE);
    res += single_feature (res, b, "Med", "Media Queries", ext2_, e2, H2_CSS_MEDIA_3, H2_CSS_MEDIA_4, H2_CSS_MEDIA_5);
    res += single_feature (res, b, "Mix", "Functions and Mixin", ext2_, e2, H2_CSS_MIXIN);
    res += single_feature (res, b, "Mot", "Motion Path", ext3_, e3, H3_CSS_MOTION);
    res += single_feature (res, b, "Mlt", "Multi-Column", ext5_, e5, H5_CSS_MULTCOL_3, H5_CSS_MULTCOL_4);
    res += single_feature (res, b, "Nam", "Namespaces", ext2_, e2, H2_CSS_NAMESPACE);
    res += single_feature (res, b, "Nes", "Non-Element Selectors", ext3_, e2, H3_CSS_NES);
    res += single_feature (res, b, "Nst", "Nesting", ext3_, e2, H3_CSS_NESTING);
    res += single_feature (res, b, "Ofl", "Overflow", ext5_, e5, H5_CSS_OVERFLOW_3, H5_CSS_OVERFLOW_4, H5_CSS_OVERFLOW_5);
    res += single_feature (res, b, "Osc", "Overscroll Behaviour", ext3_, e3, H3_CSS_OVERSCROLL);
    res += single_feature (res, b, "PaM", "Paged Media", ext3_, e3, H3_CSS_PAGE);
    res += single_feature (res, b, "PFl", "Page Floats", ext3_, e3, H3_CSS_FLOAT);
    res += single_feature (res, b, "Pos", "Positions", ext3_, e3, H3_CSS_POSITION_3, H3_CSS_POSITION_4);
    res += single_feature (res, b, "Pre", "Presentation Levels", ext3_, e3, H3_CSS_PRESENT);
    res += single_feature (res, b, "PEv", "Pointer Events", ext5_, e5, H5_CSS_PTR_EV_3, H5_CSS_PTR_EV_4, H5_CSS_PTR_EV_5, H5_CSS_PTR_EV_6);
    res += single_feature (res, b, "Rou", "Round Display", ext3_, e3, H3_CSS_ROUND);
    res += single_feature (res, b, "Psd", "Pseudo-Elements", ext5_, e5, H5_CSS_PSEUDO_3, H5_CSS_PSEUDO_4);
    res += single_feature (res, b, "Reg", "Regions", ext3_, e3, H3_CSS_REGION);
    res += single_feature (res, b, "Rhy", "Rhythmic Sizing", ext3_, e3, H3_CSS_RHYTHM);
    res += single_feature (res, b, "Rub", "Ruby Annotation", ext3_, e3, H3_CSS_RUBY);
    res += single_feature (res, b, "Sco", "Scope", ext3_, e3, H3_CSS_SCOPE);
    res += single_feature (res, b, "Scr", "Scrollbar Style", ext3_, e3, H3_CSS_SCROLLBAR);
    res += single_feature (res, b, "Sel", "Selectors", ext2_, e2, H2_CSS_SELECTOR_3, H2_CSS_SELECTOR_4);
    res += single_feature (res, b, "Sha", "Shadow Parts", ext3_, e3, H3_CSS_SHADOW);
    res += single_feature (res, b, "Shp", "Shapes", ext3_, e3, H3_CSS_SHAPE_3, H3_CSS_SHAPE_4);
    res += single_feature (res, b, "Sda", "Scroll-driven Animation", ext3_, e3, H3_CSS_SDA);
    res += single_feature (res, b, "Snp", "Scroll Snap", ext3_, e3, H3_CSS_SNAP_3, H3_CSS_SNAP_4);
    res += single_feature (res, b, "Spa", "Spatial Navigation", ext4_, e4, H4_CSS_SPATIAL);
    res += single_feature (res, b, "Spe", "Speech", ext3_, e3, H3_CSS_SPEECH);
    res += single_feature (res, b, "Sty", "Style Attributes", ext2_, e2, H2_CSS_STYLE);
    if (any_ext2 (H2_CSS_SVG_10)) res += single_feature (res, b, "S10", "SVG 1.0", ext2_, e2, H2_CSS_SVG_10);
    else if (any_ext2 (H2_CSS_SVG_11)) res += single_feature (res, b, "S11", "SVG 1.1", ext2_, e2, H2_CSS_SVG_11);
    else if (any_ext2 (H2_CSS_SVG_20)) res += single_feature (res, b, "S20", "SVG 2.0", ext2_, e2, H2_CSS_SVG_20);
    else if (any_ext2 (H2_CSS_SVG_21)) res += single_feature (res, b, "S21", "SVG 2.1", ext2_, e2, H2_CSS_SVG_21);
    else if (any_ext2 (H2_CSS_SVG_12_TINY)) res += single_feature (res, b, "S1t", "SVG 1.2 tiny", ext2_, e2, H2_CSS_SVG_12_TINY);
    else if (any_ext2 (H2_CSS_SVG_12_FULL)) res += single_feature (res, b, "S1f", "SVG 1.2 full", ext2_, e2, H2_CSS_SVG_12_FULL);
    res += single_feature (res, b, "Syn", "Syntax Module", ext2_, e2, H2_CSS_SYNTAX);
    res += single_feature (res, b, "Tab", "Tables", ext3_, e3, H3_CSS_TABLE);
    res += single_feature (res, b, "Trf", "Transforms", ext3_, e3, H3_CSS_TRANSFORM_3, H3_CSS_TRANSFORM_4);
    res += single_feature (res, b, "Trs", "Transitions", ext4_, e4, H4_CSS_TRANSITION_3, H4_CSS_TRANSITION_4);
    res += single_feature (res, b, "Txd", "Text Decoration", ext3_, e3, H3_CSS_TEXTDEC_3, H3_CSS_TEXTDEC_4);
    res += single_feature (res, b, "Txt", "Text", ext3_, e3, H3_CSS_TEXT_3, H3_CSS_TEXT_4);
    res += single_feature (res, b, "UsI", "Basic User Interface", ext2_, e2, H2_CSS_UI_3, H2_CSS_UI_4);
    res += single_feature (res, b, "Val", "Values and Units", ext5_, e5, H5_CSS_VALUE_3, H5_CSS_VALUE_4, H5_CSS_VALUE_5);
    res += single_feature (res, b, "Vpt", "Viewport", ext4_, e4, H4_CSS_VIEWPORT);
    res += single_feature (res, b, "Vtr", "View Transitions", ext5_, e5, H5_CSS_VIEWTRAN_3, H5_CSS_VIEWTRAN_4);
    res += single_feature (res, b, "WCh", "Will Change", ext3_, e3, H3_CSS_WC);
    res += single_feature (res, b, "WrM", "Writing Mode", ext3_, e3, H3_CSS_WRITING_3, H3_CSS_WRITING_4);
    return res; }

void html_version::css_version (const e_css_version v) noexcept
{   css_ = v;
    reset_ext2 (H2_FULL_CSS_MASK);
    reset_ext3 (H3_FULL_CSS_MASK);
    reset_ext4 (H4_FULL_CSS_MASK | H4_CSS_VER_MASK);
    reset_ext5 (H5_FULL_CSS_MASK);
    switch (v)
    {   case css_1 :        set_ext2 (H2_CSS_1);
                            break;
        case css_2_0 :      set_ext2 (H2_CSS_2_0);
                            break;
        case css_2_1 :      set_ext2 (H2_CSS_2_1);
                            break;
        case css_2_2 :      set_ext2 (H2_CSS_2_2);
                            break;
        case css_3 :        set_ext2 (H2_CSS_3_FULL);
                            set_ext3 (H3_CSS_3_FULL);
                            set_ext4 (H4_CSS_3_FULL);
                            set_ext5 (H5_CSS_3_FULL);
                            break;
        case css_4 :        set_ext2 (H2_CSS_4_FULL);
                            set_ext3 (H3_CSS_4_FULL);
                            set_ext4 (H4_CSS_4_FULL);
                            set_ext5 (H5_CSS_4_FULL);
                            break;
        case css_5 :        set_ext2 (H2_CSS_5_FULL);
                            set_ext3 (H3_CSS_5_FULL);
                            set_ext4 (H4_CSS_5_FULL);
                            set_ext5 (H5_CSS_5_FULL);
                            break;
        case css_6 :        set_ext2 (H2_CSS_6_FULL);
                            set_ext3 (H3_CSS_6_FULL);
                            set_ext4 (H4_CSS_6_FULL);
                            set_ext5 (H5_CSS_6_FULL);
                            break;
        case css_2007 :     set_ext2 (H2_CSS_2007);
                            set_ext3 (H3_CSS_2007);
                            set_ext4 (H4_CSS_2007);
                            set_ext5 (H5_CSS_2007);
                            break;
        case css_2010 :     set_ext2 (H2_CSS_2010);
                            set_ext3 (H3_CSS_2010);
                            set_ext4 (H4_CSS_2010);
                            set_ext5 (H5_CSS_2010);
                            break;
        case css_2015 :     set_ext2 (H2_CSS_2015);
                            set_ext3 (H3_CSS_2015);
                            set_ext4 (H4_CSS_2015);
                            set_ext5 (H5_CSS_2015);
                            break;
        case css_2015_1 :   set_ext2 (H2_CSS_2015 | H2_CSS_2015_1);
                            set_ext3 (H3_CSS_2015 | H3_CSS_2015_1);
                            set_ext4 (H4_CSS_2015 | H4_CSS_2015_1);
                            set_ext5 (H5_CSS_2015 | H5_CSS_2015_1);
                            break;
        case css_2015_2 :   set_ext2 (H2_CSS_2015 | H2_CSS_2015_1 | H2_CSS_2015_2);
                            set_ext3 (H3_CSS_2015 | H3_CSS_2015_1 | H3_CSS_2015_2);
                            set_ext4 (H4_CSS_2015 | H4_CSS_2015_1 | H4_CSS_2015_2);
                            set_ext5 (H5_CSS_2015 | H5_CSS_2015_1 | H5_CSS_2015_2);
                            break;
        case css_2017 :     set_ext2 (H2_CSS_2017);
                            set_ext3 (H3_CSS_2017);
                            set_ext4 (H4_CSS_2017);
                            set_ext5 (H5_CSS_2017);
                            break;
        case css_2017_1 :   set_ext2 (H2_CSS_2017 | H2_CSS_2017_1);
                            set_ext3 (H3_CSS_2017 | H3_CSS_2017_1);
                            set_ext4 (H4_CSS_2017 | H4_CSS_2017_1);
                            set_ext5 (H5_CSS_2017 | H5_CSS_2017_1);
                            break;
        case css_2017_2 :   set_ext2 (H2_CSS_2017 | H2_CSS_2017_1 | H2_CSS_2017_2);
                            set_ext3 (H3_CSS_2017 | H3_CSS_2017_1 | H3_CSS_2017_2);
                            set_ext4 (H4_CSS_2017 | H4_CSS_2017_1 | H4_CSS_2017_2);
                            set_ext5 (H5_CSS_2017 | H5_CSS_2017_1 | H5_CSS_2017_2);
                            break;
        case css_2018 :     set_ext2 (H2_CSS_2018);
                            set_ext3 (H3_CSS_2018);
                            set_ext4 (H4_CSS_2018);
                            set_ext5 (H5_CSS_2018);
                            break;
        case css_2018_1 :   set_ext2 (H2_CSS_2018 | H2_CSS_2018_1);
                            set_ext3 (H3_CSS_2018 | H3_CSS_2018_1);
                            set_ext4 (H4_CSS_2018 | H4_CSS_2018_1);
                            set_ext5 (H5_CSS_2018 | H5_CSS_2018_1);
                            break;
        case css_2018_2 :   set_ext2 (H2_CSS_2018 | H2_CSS_2018_1 | H2_CSS_2018_2);
                            set_ext3 (H3_CSS_2018 | H3_CSS_2018_1 | H3_CSS_2018_2);
                            set_ext4 (H4_CSS_2018 | H4_CSS_2018_1 | H4_CSS_2018_2);
                            set_ext5 (H5_CSS_2018 | H5_CSS_2018_1 | H5_CSS_2018_2);
                            break;
        case css_2020 :     set_ext2 (H2_CSS_2020);
                            set_ext3 (H3_CSS_2020);
                            set_ext4 (H4_CSS_2020);
                            set_ext5 (H5_CSS_2020);
                            break;
        case css_2020_1 :   set_ext2 (H2_CSS_2020 | H2_CSS_2020_1);
                            set_ext3 (H3_CSS_2020 | H3_CSS_2020_1);
                            set_ext4 (H4_CSS_2020 | H4_CSS_2020_1);
                            set_ext5 (H5_CSS_2020 | H5_CSS_2020_1);
                            break;
        case css_2020_2 :   set_ext2 (H2_CSS_2020 | H2_CSS_2020_1 | H2_CSS_2020_2);
                            set_ext3 (H3_CSS_2020 | H3_CSS_2020_1 | H3_CSS_2020_2);
                            set_ext4 (H4_CSS_2020 | H4_CSS_2020_1 | H4_CSS_2020_2);
                            set_ext5 (H5_CSS_2020 | H5_CSS_2020_1 | H5_CSS_2020_2);
                            break;
        case css_2021 :     set_ext2 (H2_CSS_2021);
                            set_ext3 (H3_CSS_2021);
                            set_ext4 (H4_CSS_2021);
                            set_ext5 (H5_CSS_2021);
                            break;
        case css_2021_1 :   set_ext2 (H2_CSS_2021 | H2_CSS_2021_1);
                            set_ext3 (H3_CSS_2021 | H3_CSS_2021_1);
                            set_ext4 (H4_CSS_2021 | H4_CSS_2021_1);
                            set_ext5 (H5_CSS_2021 | H5_CSS_2021_1);
                            break;
        case css_2021_2 :   set_ext2 (H2_CSS_2021 | H2_CSS_2021_1 | H2_CSS_2021_2);
                            set_ext3 (H3_CSS_2021 | H3_CSS_2021_1 | H3_CSS_2021_2);
                            set_ext4 (H4_CSS_2021 | H4_CSS_2021_1 | H4_CSS_2021_2);
                            set_ext5 (H5_CSS_2021 | H5_CSS_2021_1 | H5_CSS_2021_2);
                            break;
        case css_2022 :     set_ext2 (H2_CSS_2022);
                            set_ext3 (H3_CSS_2022);
                            set_ext4 (H4_CSS_2022);
                            set_ext5 (H5_CSS_2022);
                            break;
        case css_2022_1 :   set_ext2 (H2_CSS_2022 | H2_CSS_2022_1);
                            set_ext3 (H3_CSS_2022 | H3_CSS_2022_1);
                            set_ext4 (H4_CSS_2022 | H4_CSS_2022_1);
                            set_ext5 (H5_CSS_2022 | H5_CSS_2022_1);
                            break;
        case css_2022_2 :   set_ext2 (H2_CSS_2022 | H2_CSS_2022_1 | H2_CSS_2022_2);
                            set_ext3 (H3_CSS_2022 | H3_CSS_2022_1 | H3_CSS_2022_2);
                            set_ext4 (H4_CSS_2022 | H4_CSS_2022_1 | H4_CSS_2022_2);
                            set_ext5 (H5_CSS_2022 | H5_CSS_2022_1 | H5_CSS_2022_2);
                            break;
        case css_2023 :     set_ext2 (H2_CSS_2023);
                            set_ext3 (H3_CSS_2023);
                            set_ext4 (H4_CSS_2023);
                            set_ext5 (H5_CSS_2023);
                            break;
        case css_2023_1 :   set_ext2 (H2_CSS_2023 | H2_CSS_2023_1);
                            set_ext3 (H3_CSS_2023 | H3_CSS_2023_1);
                            set_ext4 (H4_CSS_2023 | H4_CSS_2023_1);
                            set_ext5 (H5_CSS_2023 | H5_CSS_2023_1);
                            break;
        case css_2023_2 :   set_ext2 (H2_CSS_2023 | H2_CSS_2023_1 | H2_CSS_2023_2);
                            set_ext3 (H3_CSS_2023 | H3_CSS_2023_1 | H3_CSS_2023_2);
                            set_ext4 (H4_CSS_2023 | H4_CSS_2023_1 | H4_CSS_2023_2);
                            set_ext5 (H5_CSS_2023 | H5_CSS_2023_1 | H5_CSS_2023_2);
                            break;
        case css_2024 :     set_ext2 (H2_CSS_2024);
                            set_ext3 (H3_CSS_2024);
                            set_ext4 (H4_CSS_2024);
                            set_ext5 (H5_CSS_2024);
                            break;
        case css_2024_1 :   set_ext2 (H2_CSS_2024 | H2_CSS_2024_1);
                            set_ext3 (H3_CSS_2024 | H3_CSS_2024_1);
                            set_ext4 (H4_CSS_2024 | H4_CSS_2024_1);
                            set_ext5 (H5_CSS_2024 | H5_CSS_2024_1);
                            break;
        case css_2024_2 :   set_ext2 (H2_CSS_2024 | H2_CSS_2024_1 | H2_CSS_2024_2);
                            set_ext3 (H3_CSS_2024 | H3_CSS_2024_1 | H3_CSS_2024_2);
                            set_ext4 (H4_CSS_2024 | H4_CSS_2024_1 | H4_CSS_2024_2);
                            set_ext5 (H5_CSS_2024 | H5_CSS_2024_1 | H5_CSS_2024_2);
                            break;
        case css_2024_3 :   set_ext2 (H2_CSS_2024 | H2_CSS_2024_1 | H2_CSS_2024_2 | H2_CSS_2024_3);
                            set_ext3 (H3_CSS_2024 | H3_CSS_2024_1 | H3_CSS_2024_2 | H3_CSS_2024_3);
                            set_ext4 (H4_CSS_2024 | H4_CSS_2024_1 | H4_CSS_2024_2 | H4_CSS_2024_3);
                            set_ext5 (H5_CSS_2024 | H5_CSS_2024_1 | H5_CSS_2024_2 | H5_CSS_2024_3);
                            break;
        case css_2025 :     set_ext2 (H2_CSS_2025);
                            set_ext3 (H3_CSS_2025);
                            set_ext4 (H4_CSS_2025);
                            set_ext5 (H5_CSS_2025);
                            break;
        case css_2025_1 :   set_ext2 (H2_CSS_2025 | H2_CSS_2025_1);
                            set_ext3 (H3_CSS_2025 | H3_CSS_2025_1);
                            set_ext4 (H4_CSS_2025 | H4_CSS_2025_1);
                            set_ext5 (H5_CSS_2025 | H5_CSS_2025_1);
                            break;
        case css_2025_2 :   set_ext2 (H2_CSS_2025 | H2_CSS_2025_1 | H2_CSS_2025_2);
                            set_ext3 (H3_CSS_2025 | H3_CSS_2025_1 | H3_CSS_2025_2);
                            set_ext4 (H4_CSS_2025 | H4_CSS_2025_1 | H4_CSS_2025_2);
                            set_ext5 (H5_CSS_2025 | H5_CSS_2025_1 | H5_CSS_2025_2);
                            break;
        case css_2025_3 :   set_ext2 (H2_CSS_2025 | H2_CSS_2025_1 | H2_CSS_2025_2 | H2_CSS_2025_3);
                            set_ext3 (H3_CSS_2025 | H3_CSS_2025_1 | H3_CSS_2025_2 | H3_CSS_2025_3);
                            set_ext4 (H4_CSS_2025 | H4_CSS_2025_1 | H4_CSS_2025_2 | H4_CSS_2025_3);
                            set_ext5 (H5_CSS_2025 | H5_CSS_2025_1 | H5_CSS_2025_2 | H5_CSS_2025_3);
                            break;
        case css_2026 :     set_ext2 (H2_CSS_2026);
                            set_ext3 (H3_CSS_2026);
                            set_ext4 (H4_CSS_2026);
                            set_ext5 (H5_CSS_2026);
                            break;
        case css_2026_1 :   set_ext2 (H2_CSS_2026 | H2_CSS_2026_1);
                            set_ext3 (H3_CSS_2026 | H3_CSS_2026_1);
                            set_ext4 (H4_CSS_2026 | H4_CSS_2026_1);
                            set_ext5 (H5_CSS_2026 | H5_CSS_2026_1);
                            break;
        case css_2026_2 :   set_ext2 (H2_CSS_2026 | H2_CSS_2026_1 | H2_CSS_2026_2);
                            set_ext3 (H3_CSS_2026 | H3_CSS_2026_1 | H3_CSS_2026_2);
                            set_ext4 (H4_CSS_2026 | H4_CSS_2026_1 | H4_CSS_2026_2);
                            set_ext5 (H5_CSS_2026 | H5_CSS_2026_1 | H5_CSS_2026_2);
                            break;
        case css_2026_3 :   set_ext2 (H2_CSS_2026 | H2_CSS_2026_1 | H2_CSS_2026_2 | H2_CSS_2026_3);
                            set_ext3 (H3_CSS_2026 | H3_CSS_2026_1 | H3_CSS_2026_2 | H3_CSS_2026_3);
                            set_ext4 (H4_CSS_2026 | H4_CSS_2026_1 | H4_CSS_2026_2 | H4_CSS_2026_3);
                            set_ext5 (H5_CSS_2026 | H5_CSS_2026_1 | H5_CSS_2026_2 | H5_CSS_2026_3);
                            break;
        case css_ls_2024 :  set_ext2 (H2_CSS_LS_2024);
                            set_ext3 (H3_CSS_LS_2024);
                            set_ext4 (H4_CSS_LS_2024);
                            set_ext5 (H5_CSS_LS_2024);
                            break;
        case css_ls_2025 :  set_ext2 (H2_CSS_LS_2025);
                            set_ext3 (H3_CSS_LS_2025);
                            set_ext4 (H4_CSS_LS_2025);
                            set_ext5 (H5_CSS_LS_2025);
                            break;
        case css_ls_2026 :  set_ext2 (H2_CSS_LS_2026);
                            set_ext3 (H3_CSS_LS_2026);
                            set_ext4 (H4_CSS_LS_2026);
                            set_ext5 (H5_CSS_LS_2026);
                            break;
        default :           break; }
    set_ext4 (H4_CSS_VER_MASK, v, H4_CSS_VER_SHIFT); }

bool html_version::css_any_3_4_5_6 () const noexcept
{   if ((ext5_ & H5_CSS_3_4_5_6) != 0) return true;
    if ((ext4_ & H4_CSS_3_4_5_6) != 0) return true;
    if ((ext3_ & H3_CSS_3_4_5_6) != 0) return true;
    return (ext2_ & H2_CSS_3_4_5_6) != 0; }

e_rdf_version html_version::rdf_version () const noexcept
{   if (all_ext (HE_RDFA)) return rdf_a;
    if (all_ext (HE_RDF)) return rdf_1_0;
    if (all_ext (HE_RDF_DEP)) return rdf_deprecated;
    return rdf_none; }

void html_version::rdf_version (const e_rdf_version v) noexcept
{   reset_ext (RDF_MASK);
    switch (v)
    {   case rdf_a : set_ext (HE_RDFA); break;
        case rdf_1_1 :
        case rdf_1_0 : set_ext (HE_RDF); break;
        case rdf_deprecated : set_ext (HE_RDF_DEP); break;
        default : break; } }

e_svg_version html_version::svg_version () const noexcept
{   if (all_ext (HE_SVG_21)) return sv_2_1;
    if (all_ext (HE_SVG_20)) return sv_2_0;
    if (all_ext (HE_SVG_12_TINY)) return sv_1_2_tiny;
    if (all_ext (HE_SVG_12_FULL)) return sv_1_2_full;
    if (all_ext (HE_SVG_11)) return sv_1_1;
    if (all_ext (HE_SVG_10)) return sv_1_0;
    return sv_none; }

void html_version::svg_version (const e_svg_version v) noexcept
{   reset_ext (SVG_MASK);
    switch (v)
    {   case sv_1_0 : set_ext (HE_SVG_10); break;
        case sv_1_1 : set_ext (HE_SVG_11); break;
        case sv_1_2_tiny : set_ext (HE_SVG_12_TINY); break;
        case sv_1_2_full : set_ext (HE_SVG_12_FULL); break;
        case sv_2_0 : set_ext (HE_SVG_20); break;
        case sv_2_1 : set_ext (HE_SVG_21); break;
        default : break; } }

::std::string html_version::svg_version_name () const
{   return type_master < t_svg_version > :: name (svg_version ()); }

bool html_version::math_4_core () const noexcept
{   return (any_ext2 (H2_MATH_C)); }

e_math_version html_version::math_version () const noexcept
{   if (all_ext2 (H2_MATH_4)) return math_4;
    if (all_ext2 (H2_MATH_C)) return math_core;
    if (all_ext2 (H2_MATH_3)) return math_3;
    if (all_ext2 (H2_MATH_2)) return math_2;
    if (all_ext2 (H2_MATH_1)) return math_1;
    return math_none; }

::std::string html_version::math_version_name () const
{   if (all_ext2 (H2_MATH_4)) return "4";
    if (all_ext2 (H2_MATH_C)) return "core";
    if (all_ext2 (H2_MATH_3)) return "3";
    if (all_ext2 (H2_MATH_2)) return "2";
    if (all_ext2 (H2_MATH_1)) return "1";
    return ""; }

e_jsonld_version html_version::jsonld_version () const noexcept
{   if (all_ext2 (H2_JSONLD_1_1)) return jsonld_1_1;
    if (all_ext2 (H2_JSONLD_1_0)) return jsonld_1_0;
    return jsonld_none; }

void html_version::math_version (const e_math_version v) noexcept
{   reset_ext2 (MATH_MASK);
    switch (v)
    {   case math_1 : set_ext2 (H2_MATH_1); break;
        case math_2 : set_ext2 (H2_MATH_2); break;
        case math_3 : set_ext2 (H2_MATH_3); break;
        case math_4 : set_ext2 (H2_MATH_4); break;
        case math_core :
            set_ext2 (H2_MATH_C);
            if (*this >= html_math_core)
                set_ext4 (H4_CSS_MATH_CORE);
            break;
        default : break; } }

void html_version::jsonld_version (const e_jsonld_version v) noexcept
{   reset_ext2 (JSONLD_MASK);
    switch (v)
    {   case jsonld_1_0 : set_ext2 (H2_JSONLD_1_0); break;
        case jsonld_1_1 : set_ext2 (H2_JSONLD_1_1); break;
        default : break; } }

::std::string html_version::get_doctype () const
{   switch (mjr ())
    {   case 0 : break;
        case 1 :
            switch (mnr ())
            {   case 0 : return "HTML PUBLIC \"-//IETF//DTD HTML//EN\"";
                case 1 : return "htmlplus PUBLIC \"-//Internet/RFC xxxx//EN\"";
                default : break; }
            break;
        case 2 :
            switch (level ())
            {   case 1 : return "HTML PUBLIC \"-//IETF//DTD HTML 2.0 Level 1//EN\"";
                case 2 : return "HTML PUBLIC \"-//IETF//DTD HTML 2.0 Level 2//EN\"";
                default : return "HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\""; }
        case 3 :
            switch (mnr ())
            {   case 0 : return "HTML PUBLIC \"-//IETF//DTD HTML 3.0//EN\"";
                case 2 : return "HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"";
                default : break; }
            break;
        case 4 :
            switch (mnr ())
            {   case 0 : return "HTML PUBLIC \"-//IETF//DTD HTML 4.0 Transitional//EN\" \"" HTTP_W3 "/TR/REC-html40/loose.dtd\"";
                case 1 : return "HTML PUBLIC \"-//IETF//DTD HTML 4.01 Transitional//EN\" \"" HTTP_W3 "/TR/html40/loose.dtd\"";
                case 2 : return "html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"" HTTP_W3 "/TR/xhtml1/DTD/xhtml1-transitional.dtd\"";
                case 3 : return "html PUBLIC \"-//W3C//DTD XHTML Basic 1.1//EN\" \"" HTTP_W3 "/TR/xhtml-basic/xhtml-basic11.dtd\"";
                case 4 : return "html PUBLIC \"-//W3C//DTD XHTML 2.0//EN\" \"" HTTP_W3 "/MarkUp/DTD/xhtml2.dtd\"";
                default : break; }
            break;
        default : return "HTML"; }
    return ::std::string (); }

bool html_version::restricted_charset () const noexcept
{   return (is_5 ()); }

bool html_version::valid_charset (const ::std::string& charset) const
{   if (is_5 ()) return compare_no_case (charset, UTF_8);
    if (is_b4_1 ()) return compare_no_case (charset, US_ASCII);
    return true; }

const char *html_version::default_charset () const noexcept
{ return ::default_charset (*this); }

const char *html_version::alternative_charset () const  noexcept
{ return ::alternative_charset (*this); }

bool html_version::test_extension () const noexcept
{   if (is_b4_4 ()) return false;
    return (has_svg () || has_math_not_core () || has_rdfa ()); }

bool html_version::is_plain_html () const noexcept
{   if (xhtml () || atom () || rdfa () || rsl () || rss ()) return false;
    return ! test_extension (); }

bool html_version::requires_extension () const noexcept
{   return test_extension (); }

bool html_version::svg_anim (const e_svg_version v) const noexcept
{   switch (v)
    {   case sv_1_0 : return svg_anim_10 ();
        case sv_1_1 : return svg_anim_11 ();
        case sv_1_2_tiny :
        case sv_1_2_full : return svg_anim_12 ();
        case sv_2_0 : return svg_anim_20 ();
        case sv_2_1 : return svg_anim_21 ();
        default : break; }
    return false; }

bool html_version::svg_limited (const e_svg_version v) const noexcept
{   switch (v)
    {   case sv_1_0 : return svg_limited_10 ();
        case sv_1_1 : return svg_limited_11 ();
        case sv_1_2_tiny :
        case sv_1_2_full : return svg_limited_12 ();
        case sv_2_0 : return svg_limited_20 ();
        case sv_2_1 : return svg_limited_21 ();
        default : break; }
    return false; }

bool html_version::valid_context (const html_version& v) const noexcept
{   bool res = true;
    if (has_svg ())
    {   switch (v.svg_version ())
        {   case sv_1_0 : if (any_ext (HE_SVG_10)) return true; res = false; break;  
            case sv_1_1 : if (any_ext (HE_SVG_11)) return true; res = false; break;  
            case sv_1_2_tiny : if (any_ext (HE_SVG_12_TINY)) return true; res = false; break;  
            case sv_1_2_full : if (any_ext (HE_SVG_12_FULL)) return true; res = false; break;  
            case sv_2_0 : if (any_ext (HE_SVG_20)) return true; res = false; break;  
            case sv_2_1 : if (any_ext (HE_SVG_21)) return true; res = false; break; 
            default : break; } }
   if (has_math ())
   {    switch (v.math_version ())
        {   case math_1 : if (any_ext2 (H2_MATH_1)) return true; res = false; break;
            case math_2 : if (any_ext2 (H2_MATH_2)) return true; res = false; break;  
            case math_3 : if (any_ext2 (H2_MATH_3)) return true; res = false; break;  
            case math_4 : if (any_ext2 (H2_MATH_4)) return true; res = false; break;  
            case math_core : if (any_ext2 (H2_MATH_C)) return true; res = false; break; 
            default : break; } }
    if (has_css ())
    {   if (has_css_crossover (v.css_version (), v, context.html_ver ())) return true;
        if (has_css_crossover (css_version (), *this, v)) return true; }
    if (has_rdf ())
    {   switch (context.rdf_version ())
        {   case rdf_a : if (any_ext (HE_RDFA)) return true; res = false; break;
            case rdf_deprecated : if (any_ext (HE_RDF_DEP)) return true; res = false; break;  
            case rdf_1_0 : 
            case rdf_1_1 : if (any_ext (HE_RDF)) return true; res = false; break;  
            default : break; } }
    if (has_rdfa ())
        if (context.has_rdfa ()) return true;
        else res = false;
    if (has_jsonld ())
    {   switch (context.jsonld_version ())
        {   case jsonld_1_0 : if (any_ext2 (H2_JSONLD_1_0)) return true; res = false; break;
            case jsonld_1_1 : if (any_ext2 (H2_JSONLD_1_1)) return true; res = false; break;  
            default : break; } }
    return res; }

template < e_css_module MOD > void html_version::set_level (const int ) { }

template < e_css_module MOD > int html_version::get_level () const { return 0; }

template < > int html_version::get_level < c_colour_adjustment > () const
{   if (any_ext3 (H3_CSS_ADJUST)) return 3;
    return 0; }

template < > void html_version::set_level < c_colour_adjustment > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_ADJUST);
    else reset_ext3 (H3_CSS_ADJUST); }

template < > int html_version::get_level < c_advanced_layout > () const
{   if (any_ext4 (H4_CSS_ADVLAY)) return 3;
    return 0; }

template < > void html_version::set_level < c_advanced_layout > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_ADVLAY);
    else reset_ext4 (H4_CSS_ADVLAY); }

template < > int html_version::get_level < c_scroll_anchoring > () const
{   if (any_ext3 (H3_CSS_ANCHOR)) return 3;
    return 0; }

template < > void html_version::set_level < c_scroll_anchoring > (const int n)
{   if (n == 3) set_ext4 (H3_CSS_ANCHOR);
    else reset_ext4 (H3_CSS_ANCHOR); }

template < > int html_version::get_level < c_anchor_pos > () const
{   if (any_ext4 (H4_CSS_ANCHOR_POS)) return 3;
    return 0; }

template < > void html_version::set_level < c_anchor_pos > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_ANCHOR_POS);
    else reset_ext4 (H4_CSS_ANCHOR_POS); }

template < > int html_version::get_level < c_animation > () const
{   if ((ext2 () & H2_CSS_ANIM_4) == H2_CSS_ANIM_4) return 4;   
    if ((ext2 () & H2_CSS_ANIM_3) == H2_CSS_ANIM_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_animation > (const int n)
{   reset_ext2 (H2_CSS_ANIM_MASK);
    if (n == 4) set_ext2 (H2_CSS_ANIM_34);
    else if (n == 3) set_ext2 (H2_CSS_ANIM_3); }

template < > int html_version::get_level < c_background_border > () const
{   if ((ext5 () & H5_CSS_BACKGROUND_4) == H5_CSS_BACKGROUND_4) return 4;   
    if ((ext5 () & H5_CSS_BACKGROUND_3) == H5_CSS_BACKGROUND_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_background_border > (const int n)
{   reset_ext5 (H5_CSS_BACKGROUND_MASK);
    if (n == 4) set_ext5 (H5_CSS_BACKGROUND_34);
    else if (n == 3) set_ext5 (H5_CSS_BACKGROUND_3); }

template < > int html_version::get_level < c_border_box > () const
{   if ((ext5 () & H5_CSS_BORD_BOX_4) == H5_CSS_BORD_BOX_4) return 4;   
    return 0; }

template < > void html_version::set_level < c_border_box > (const int n)
{   reset_ext5 (H5_CSS_BORD_BOX_4);
    if (n == 4) set_ext5 (H5_CSS_BORD_BOX_4); }

template < > int html_version::get_level < c_box_alignment > () const
{   if (any_ext3 (H3_CSS_BOX_ALIGN)) return 3;
    return 0; }

template < > void html_version::set_level < c_box_alignment > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_BOX_ALIGN);
    else reset_ext3 (H3_CSS_BOX_ALIGN); }

template < > int html_version::get_level < c_box_model > () const
{   if ((ext3 () & H3_CSS_BOX_MODEL_4) == H3_CSS_BOX_MODEL_4) return 4;
    if ((ext3 () & H3_CSS_BOX_MODEL_3) == H3_CSS_BOX_MODEL_3) return 3;
    return 0; }

template < > void html_version::set_level < c_box_model > (const int n)
{   reset_ext3 (H3_CSS_BOX_MODEL_MASK);
    if (n == 4) set_ext3 (H3_CSS_BOX_MODEL);
    else if (n == 3) set_ext3 (H3_CSS_BOX_MODEL_3); }

template < > int html_version::get_level < c_box_sizing > () const
{   if ((ext3 () & H3_CSS_BOX_SIZING_4) == H3_CSS_BOX_SIZING_4) return 4;
    if ((ext3 () & H3_CSS_BOX_SIZING_3) == H3_CSS_BOX_SIZING_3) return 3;
    return 0; }

template < > void html_version::set_level < c_box_sizing > (const int n)
{   reset_ext3 (H3_CSS_BOX_SIZING_MASK);
    if (n == 4) set_ext3 (H3_CSS_BOX_SIZING_34);
    else if (n == 3) set_ext3 (H3_CSS_BOX_SIZING_3); }

template < > int html_version::get_level < c_cascade_inheritance > () const
{   if ((ext2 () & H2_CSS_CASCADE_6) == H2_CSS_CASCADE_6) return 6;   
    if ((ext2 () & H2_CSS_CASCADE_5) == H2_CSS_CASCADE_5) return 5;   
    if ((ext2 () & H2_CSS_CASCADE_4) == H2_CSS_CASCADE_4) return 4;   
    if ((ext2 () & H2_CSS_CASCADE_3) == H2_CSS_CASCADE_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_cascade_inheritance > (const int n)
{   reset_ext2 (H2_CSS_CASCADE_MASK);
    switch (n)
    {   case 6 : set_ext2 (H2_CSS_CASCADE); break;
        case 5 : set_ext2 (H2_CSS_CASCADE_345); break;
        case 4 : set_ext2 (H2_CSS_CASCADE_34); break;
        case 3 : set_ext2 (H2_CSS_CASCADE_3); break;
        default : break; } }

template < > int html_version::get_level < c_colour > () const
{   if ((ext4 () & H4_CSS_COLOUR_6) == H4_CSS_COLOUR_6) return 6;   
    if ((ext4 () & H4_CSS_COLOUR_5) == H4_CSS_COLOUR_5) return 5;   
    if ((ext4 () & H4_CSS_COLOUR_4) == H4_CSS_COLOUR_4) return 4;   
    if ((ext4 () & H4_CSS_COLOUR_3) == H4_CSS_COLOUR_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_colour > (const int n)
{   reset_ext4 (H4_CSS_COLOUR_MASK);
    switch (n)
    {   case 6 : set_ext4 (H4_CSS_COLOUR); break;
        case 5 : set_ext4 (H4_CSS_COLOUR_345); break;
        case 4 : set_ext4 (H4_CSS_COLOUR_34); break;
        case 3 : set_ext4 (H4_CSS_COLOUR_3); break;
        default : break; } }

template < > int html_version::get_level < c_compositing_blending > () const
{   if ((ext2 () & H2_CSS_COMBLE_4) == H2_CSS_COMBLE_4) return 4;
    if ((ext2 () & H2_CSS_COMBLE_3) == H2_CSS_COMBLE_3) return 3;
    return 0; }

template < > void html_version::set_level < c_compositing_blending > (const int n)
{   reset_ext2 (H2_CSS_COMBLE_MASK);
    if (n == 4) set_ext2 (H2_CSS_COMBLE_34);
    else if (n == 3) set_ext2 (H2_CSS_COMBLE_3); }

template < > int html_version::get_level < c_conditional_rule > () const
{   if ((ext2 () & H2_CSS_COND_RULE_5) == H2_CSS_COND_RULE_5) return 5;   
    if ((ext2 () & H2_CSS_COND_RULE_4) == H2_CSS_COND_RULE_4) return 4;   
    if ((ext2 () & H2_CSS_COND_RULE_3) == H2_CSS_COND_RULE_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_conditional_rule > (const int n)
{   reset_ext2 (H2_CSS_COND_RULE_MASK);
    switch (n)
    {   case 5 : set_ext2 (H2_CSS_COND_RULE); break;
        case 4 : set_ext2 (H2_CSS_COND_RULE_34); break;
        case 3 : set_ext2 (H2_CSS_COND_RULE_3); break;
        default : break; } }

template < > int html_version::get_level < c_containment > () const
{   if ((ext3 () & H3_CSS_CONTAIN_5) == H3_CSS_CONTAIN_5) return 5;   
    if ((ext3 () & H3_CSS_CONTAIN_4) == H3_CSS_CONTAIN_4) return 4;   
    if ((ext3 () & H3_CSS_CONTAIN_3) == H3_CSS_CONTAIN_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_containment > (const int n)
{   reset_ext3 (H3_CSS_CONTAIN_MASK);
    switch (n)
    {   case 5 : set_ext3 (H3_CSS_CONTAIN); break;
        case 4 : set_ext3 (H3_CSS_CONTAIN_34); break;
        case 3 : set_ext3 (H3_CSS_CONTAIN_3); break;
        default : break; } }

template < > int html_version::get_level < c_generated_content > () const
{   if (any_ext3 (H3_CSS_CONTENT)) return 3;
    return 0; }

template < > void html_version::set_level < c_generated_content > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_CONTENT);
    else reset_ext3 (H3_CSS_CONTENT); }

template < > int html_version::get_level < c_counter_style > () const
{   if (any_ext2 (H2_CSS_CS)) return 3;
    return 0; }

template < > void html_version::set_level < c_counter_style > (const int n)
{   if (n > 0) set_ext2 (H2_CSS_CS);
    else reset_ext2 (H2_CSS_CS); }

template < > int html_version::get_level < c_custom_property > () const
{   if (any_ext2 (H2_CSS_CUSTOM)) return 3;
    return 0; }

template < > void html_version::set_level < c_custom_property > (const int n)
{   if (n > 0) set_ext2 (H2_CSS_CUSTOM);
    else reset_ext2 (H2_CSS_CUSTOM); }

template < > int html_version::get_level < c_device_adaption > () const
{   if (any_ext3 (H3_CSS_DEVICE)) return 3;
    return 0; }

template < > void html_version::set_level < c_device_adaption > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_DEVICE);
    else reset_ext3 (H3_CSS_DEVICE); }

template < > int html_version::get_level < c_display > () const
{   if ((ext5 () & H5_CSS_DISPLAY_4) == H5_CSS_DISPLAY_4) return 4;   
    if ((ext5 () & H5_CSS_DISPLAY_3) == H5_CSS_DISPLAY_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_display > (const int n)
{   reset_ext5 (H5_CSS_DISPLAY_MASK);
    if (n == 4) set_ext5 (H5_CSS_DISPLAY_34);
    else if (n == 3) set_ext5 (H5_CSS_DISPLAY_3); }

template < > int html_version::get_level < c_easing_function > () const
{   if ((ext5 () & H5_CSS_EASE_4) == H5_CSS_EASE_4) return 4;   
    if ((ext5 () & H5_CSS_EASE_3) == H5_CSS_EASE_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_easing_function > (const int n)
{   reset_ext5 (H5_CSS_EASE_MASK);
    if (n == 4) set_ext5 (H5_CSS_EASE_34);
    else if (n == 3) set_ext5 (H5_CSS_EASE_3); }

template < > int html_version::get_level < c_environment > () const
{   if (any_ext3 (H3_CSS_ENVIRONMENT)) return 3;
    return 0; }

template < > void html_version::set_level < c_environment > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_ENVIRONMENT);
    else reset_ext3 (H3_CSS_ENVIRONMENT); }

template < > int html_version::get_level < c_exclusion > () const
{   if (any_ext3 (H3_CSS_EXCLUDE)) return 3;
    return 0; }

template < > void html_version::set_level < c_exclusion > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_EXCLUDE);
    else reset_ext3 (H3_CSS_DEVICE); }

template < > int html_version::get_level < c_flexible_box_layout > () const
{   if (any_ext2 (H2_CSS_FBL)) return 3;
    return 0; }

template < > void html_version::set_level < c_flexible_box_layout > (const int n)
{   if (n > 0) set_ext2 (H2_CSS_FBL);
    else reset_ext2 (H2_CSS_FBL); }

template < > int html_version::get_level < c_fill_stroke > () const
{   if (any_ext3 (H3_CSS_FILL)) return 3;
    return 0; }

template < > void html_version::set_level < c_fill_stroke > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_FILL);
    else reset_ext3 (H3_CSS_FILL); }

template < > int html_version::get_level < c_filter_effect > () const
{   if ((ext5 () & H5_CSS_FILTER_4) == H5_CSS_FILTER_4) return 4;   
    if ((ext5 () & H5_CSS_FILTER_3) == H5_CSS_FILTER_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_filter_effect > (const int n)
{   reset_ext5 (H5_CSS_FILTER_MASK);
    if (n == 4) set_ext5 (H5_CSS_FILTER_34);
    else if (n == 3) set_ext5 (H5_CSS_FILTER_3); }

template < > int html_version::get_level < c_page_float > () const
{   if (any_ext3 (H3_CSS_FLOAT)) return 3;
    return 0; }

template < > void html_version::set_level < c_page_float > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_FLOAT);
    else reset_ext3 (H3_CSS_FLOAT); }

template < > int html_version::get_level < c_fcs > () const
{   if (any_ext4 (H4_CSS_FCS)) return 3;
    return 0; }

template < > void html_version::set_level < c_fcs > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_FCS);
    else reset_ext4 (H4_CSS_FCS); }

template < > int html_version::get_level < c_font > () const
{   if ((ext2 () & H2_CSS_FONT_5) == H2_CSS_FONT_5) return 5;   
    if ((ext2 () & H2_CSS_FONT_4) == H2_CSS_FONT_4) return 4;   
    if ((ext2 () & H2_CSS_FONT_3) == H2_CSS_FONT_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_font > (const int n)
{   reset_ext2 (H2_CSS_FONT_MASK);
    switch (n)
    {   case 5 : set_ext2 (H2_CSS_FONT); break;
        case 4 : set_ext2 (H2_CSS_FONT_34); break;
        case 3 : set_ext2 (H2_CSS_FONT_3); break;
        default : break; } }

template < > int html_version::get_level < c_fragmentation > () const
{   if ((ext2 () & H2_CSS_FRAG_4) == H2_CSS_FRAG_4) return 4;   
    if ((ext2 () & H2_CSS_FRAG_3) == H2_CSS_FRAG_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_fragmentation > (const int n)
{   reset_ext2 (H2_CSS_FRAG_MASK);
    if (n == 4) set_ext2 (H2_CSS_FRAG_34);
    else if (n == 3) set_ext2 (H2_CSS_FRAG_3); }

template < > int html_version::get_level < c_grid_layout > () const
{   if ((ext3 () & H3_CSS_GRID_4) == H3_CSS_GRID_4) return 4;
    if ((ext3 () & H3_CSS_GRID_3) == H3_CSS_GRID_3) return 3;
    return 0; }

template < > void html_version::set_level < c_grid_layout > (const int n)
{   reset_ext3 (H3_CSS_GRID_MASK);
    if ((n == 2) || (n == 4)) set_ext3 (H3_CSS_GRID);
    else if ((n == 1) || (n == 3)) set_ext3 (H3_CSS_GRID_3); }

template < > int html_version::get_level < c_custom_highlight > () const
{   if (any_ext3 (H3_CSS_HIGHLIGHT)) return 3;
    return 0; }

template < > void html_version::set_level < c_custom_highlight > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_HIGHLIGHT);
    else reset_ext3 (H3_CSS_HIGHLIGHT); }

template < > int html_version::get_level < c_hdr > () const
{   if (any_ext4 (H4_CSS_HDR)) return 3;
    return 0; }

template < > void html_version::set_level < c_hdr > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_HDR);
    else reset_ext4 (H4_CSS_HDR); }

template < > int html_version::get_level < c_hyperlink_presentation > () const
{   if (any_ext3 (H3_CSS_HYPERLINK)) return 3;
    return 0; }

template < > void html_version::set_level < c_hyperlink_presentation > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_HYPERLINK);
    else reset_ext3 (H3_CSS_HYPERLINK); }

template < > int html_version::get_level < c_image > () const
{   if ((ext3 () & H3_CSS_IMAGE_5) == H3_CSS_IMAGE_5) return 5;
    if ((ext3 () & H3_CSS_IMAGE_4) == H3_CSS_IMAGE_4) return 4;
    if ((ext3 () & H3_CSS_IMAGE_3) == H3_CSS_IMAGE_3) return 3;
    return 0; }

template < > void html_version::set_level < c_image > (const int n)
{   reset_ext3 (H3_CSS_IMAGE_MASK);
    if (n == 5) set_ext3 (H3_CSS_IMAGE);
    else if (n == 4) set_ext3 (H3_CSS_IMAGE_34);
    else if (n == 3) set_ext3 (H3_CSS_IMAGE_3); }

template < > int html_version::get_level < c_inline_layout > () const
{   if (any_ext3 (H3_CSS_INLINE)) return 3;
    return 0; }

template < > void html_version::set_level < c_inline_layout > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_INLINE);
    else reset_ext3 (H3_CSS_INLINE); }

template < > int html_version::get_level < c_line_grid > () const
{   if (any_ext3 (H3_CSS_LINE_GRID)) return 3;
    return 0; }

template < > void html_version::set_level < c_line_grid > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_LINE_GRID);
    else reset_ext3 (H3_CSS_LINE_GRID); }

template < > int html_version::get_level < c_list_counter > () const
{   if (any_ext3 (H3_CSS_LIST)) return 3;
    return 0; }

template < > void html_version::set_level < c_list_counter > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_LIST);
    else reset_ext3 (H3_CSS_LIST); }

template < > int html_version::get_level < c_living_standard > () const
{   if (any_ext4 (H4_CSS_LIVING_STANDARD)) return 3;
    return 0; }

template < > void html_version::set_level < c_living_standard > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_LIVING_STANDARD);
    else reset_ext4 (H4_CSS_LIVING_STANDARD); }

template < > int html_version::get_level < c_logical_property > () const
{   if (any_ext3 (H3_CSS_LOGIC)) return 3;
    return 0; }

template < > void html_version::set_level < c_logical_property > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_LOGIC);
    else reset_ext3 (H3_CSS_LOGIC); }

template < > int html_version::get_level < c_marquee > () const
{   if (any_ext4 (H4_CSS_MARQUEE)) return 3;
    return 0; }

template < > void html_version::set_level < c_marquee > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_MARQUEE);
    else reset_ext4 (H4_CSS_MARQUEE); }

template < > int html_version::get_level < c_math_core > () const
{   if (any_ext4 (H4_CSS_MATH_CORE)) return 3;
    return 0; }

template < > void html_version::set_level < c_math_core > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_MATH_CORE);
    else reset_ext4 (H4_CSS_MATH_CORE); }

template < > int html_version::get_level < c_masking > () const
{   if (any_ext3 (H3_CSS_MASKING)) return 3;
    return 0; }

template < > void html_version::set_level < c_masking > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_MASKING);
    else reset_ext3 (H3_CSS_MASKING); }

template < > int html_version::get_level < c_media_query > () const
{   if ((ext2 () & H2_CSS_MEDIA_5) == H2_CSS_MEDIA_5) return 5;   
    if ((ext2 () & H2_CSS_MEDIA_4) == H2_CSS_MEDIA_4) return 4;   
    if ((ext2 () & H2_CSS_MEDIA_3) == H2_CSS_MEDIA_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_media_query > (const int n)
{   reset_ext2 (H2_CSS_MEDIA_MASK);
    switch (n)
    {   case 5 : set_ext2 (H2_CSS_MEDIA); break;
        case 4 : set_ext2 (H2_CSS_MEDIA_34); break;
        case 3 : set_ext2 (H2_CSS_MEDIA_3); break;
        default : break; } }

template < > int html_version::get_level < c_mixin > () const
{   if (any_ext2 (H2_CSS_MIXIN)) return 3;
    return 0; }

template < > void html_version::set_level < c_mixin > (const int n)
{   if (n == 3) set_ext2 (H2_CSS_MIXIN);
    else reset_ext2 (H2_CSS_MIXIN); }

template < > int html_version::get_level < c_motion_path > () const
{   if (any_ext3 (H3_CSS_MOTION)) return 3;
    return 0; }

template < > void html_version::set_level < c_motion_path > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_MOTION);
    else reset_ext3 (H3_CSS_MOTION); }

template < > int html_version::get_level < c_multicolumn > () const
{   if ((ext5 () & H5_CSS_MULTCOL_4) == H5_CSS_MULTCOL_4) return 4;   
    if ((ext5 () & H5_CSS_MULTCOL_3) == H5_CSS_MULTCOL_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_multicolumn > (const int n)
{   reset_ext5 (H5_CSS_MULTCOL_MASK);
    if (n == 4) set_ext5 (H5_CSS_MULTCOL_34);
    else if (n == 3) set_ext5 (H5_CSS_MULTCOL_3); }

template < > int html_version::get_level < c_namespace > () const
{   if (any_ext2 (H2_CSS_NAMESPACE)) return 3;
    return 0; }

template < > void html_version::set_level < c_namespace > (const int n)
{   if (n == 3) set_ext2 (H2_CSS_NAMESPACE);
    else reset_ext2 (H2_CSS_NAMESPACE); }

template < > void html_version::set_level < c_non_element_selector > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_NES);
    else reset_ext3 (H3_CSS_NES); }

template < > int html_version::get_level < c_non_element_selector > () const
{   if (any_ext3 (H3_CSS_NES)) return 3;
    return 0; }

template < > int html_version::get_level < c_nesting > () const
{   if (any_ext3 (H3_CSS_NESTING)) return 3;
    return 0; }

template < > void html_version::set_level < c_nesting > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_NESTING);
    else reset_ext3 (H3_CSS_NESTING); }

template < > int html_version::get_level < c_overflow > () const
{   if ((ext5 () & H5_CSS_OVERFLOW_5) == H5_CSS_OVERFLOW_5) return 5;
    if ((ext5 () & H5_CSS_OVERFLOW_4) == H5_CSS_OVERFLOW_4) return 4;
    if ((ext5 () & H5_CSS_OVERFLOW_3) == H5_CSS_OVERFLOW_3) return 3;
    return 0; }

template < > void html_version::set_level < c_overflow > (const int n)
{   reset_ext5 (H5_CSS_OVERFLOW_MASK);
    if (n == 5) set_ext5 (H5_CSS_OVERFLOW);
    else if (n == 4) set_ext5 (H5_CSS_OVERFLOW_34);
    else if (n == 3) set_ext5 (H5_CSS_OVERFLOW_3); }

template < > int html_version::get_level < c_overscroll_behaviour > () const
{   if (any_ext3 (H3_CSS_OVERSCROLL)) return 3;
    return 0; }

template < > void html_version::set_level < c_overscroll_behaviour > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_OVERSCROLL);
    else reset_ext3 (H3_CSS_OVERSCROLL); }

template < > int html_version::get_level < c_paged_media > () const
{   if (any_ext3 (H3_CSS_PAGE)) return 3;
    return 0; }

template < > void html_version::set_level < c_paged_media > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_PAGE);
    else reset_ext3 (H3_CSS_PAGE); }

template < > int html_version::get_level < c_positioned_layout > () const
{   if (any_ext3 (H3_CSS_POSITION_4)) return 4;
    if (any_ext3 (H3_CSS_POSITION_3)) return 3;
    return 0; }

template < > void html_version::set_level < c_positioned_layout > (const int n)
{   reset_ext3 (H3_CSS_POSITION_MASK);
    if (n == 4) set_ext3 (H3_CSS_POSITION_34);
    else if (n == 3) set_ext3 (H3_CSS_POSITION_3); }

template < > int html_version::get_level < c_presentation_level > () const
{   if (any_ext3 (H3_CSS_PRESENT)) return 3;
    return 0; }

template < > void html_version::set_level < c_presentation_level > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_PRESENT);
    else reset_ext3 (H3_CSS_PRESENT); }

template < > int html_version::get_level < c_pseudo_element > () const
{   if (any_ext5 (H5_CSS_PSEUDO_4)) return 4;
    if (any_ext5 (H5_CSS_PSEUDO_3)) return 3;
    return 0; }

template < > void html_version::set_level < c_pseudo_element > (const int n)
{   reset_ext5 (H5_CSS_PSEUDO_MASK);
    if (n == 4) set_ext5 (H5_CSS_PSEUDO_34);
    else if (n == 3) set_ext5 (H5_CSS_PSEUDO_3); }

template < > int html_version::get_level < c_region > () const
{   if (any_ext3 (H3_CSS_REGION)) return 3;
    return 0; }

template < > void html_version::set_level < c_region > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_REGION);
    else reset_ext3 (H3_CSS_REGION); }

template < > int html_version::get_level < c_rhythmic_sizing > () const
{   if (any_ext3 (H3_CSS_RHYTHM)) return 3;
    return 0; }

template < > void html_version::set_level < c_rhythmic_sizing > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_RHYTHM);
    else reset_ext3 (H3_CSS_RHYTHM); }

template < > int html_version::get_level < c_round_display > () const
{   if (any_ext3 (H3_CSS_ROUND)) return 3;
    return 0; }

template < > void html_version::set_level < c_round_display > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_ROUND);
    else reset_ext3 (H3_CSS_ROUND); }

template < > int html_version::get_level < c_ruby_annotation > () const
{   if (any_ext3 (H3_CSS_RUBY)) return 3;
    return 0; }

template < > void html_version::set_level < c_ruby_annotation > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_RUBY);
    else reset_ext3 (H3_CSS_RUBY); }

template < > int html_version::get_level < c_scoping > () const
{   if (any_ext3 (H3_CSS_SCOPE)) return 3;
    return 0; }

template < > void html_version::set_level < c_scoping > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_SCOPE);
    else reset_ext3 (H3_CSS_SCOPE); }

template < > int html_version::get_level < c_scrollbar_styling > () const
{   if (any_ext3 (H3_CSS_SCROLLBAR)) return 3;
    return 0; }

template < > void html_version::set_level < c_scrollbar_styling > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_SCROLLBAR);
    else reset_ext3 (H3_CSS_SCROLLBAR); }

template < > int html_version::get_level < c_scroll_driven_animation > () const
{   if (any_ext3 (H3_CSS_SDA)) return 3;
    return 0; }

template < > void html_version::set_level < c_scroll_driven_animation > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_SDA);
    else reset_ext3 (H3_CSS_SDA); }

template < > int html_version::get_level < c_selector > () const
{   if ((ext2 () & H2_CSS_SELECTOR_4) == H2_CSS_SELECTOR_4) return 4;   
    if ((ext2 () & H2_CSS_SELECTOR_3) == H2_CSS_SELECTOR_3) return 3; 
    if ((ext4 () & H4_LV_JAN25) == H4_LV_JAN25) if (context.html_ver () >= html_jan25) return 4;   
    return 0; }

template < > void html_version::set_level < c_selector > (const int n)
{   reset_ext2 (H2_CSS_SELECTOR_MASK);
    if (n == 3) set_ext2 (H2_CSS_SELECTOR_3);
    else if (n == 4) set_ext2 (H2_CSS_SELECTOR); }

template < > int html_version::get_level < c_shadow_part > () const
{   if (any_ext3 (H3_CSS_SHADOW)) return 3;
    return 0; }

template < > void html_version::set_level < c_shadow_part > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_SHADOW);
    else reset_ext3 (H3_CSS_SHADOW); }

template < > int html_version::get_level < c_shape > () const
{   if ((ext3 () & H3_CSS_SHAPE_4) == H3_CSS_SHAPE_4) return 4;   
    if ((ext3 () & H3_CSS_SHAPE_3) == H3_CSS_SHAPE_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_shape > (const int n)
{   reset_ext3 (H3_CSS_SHAPE_MASK);
    if (n == 3) set_ext3 (H3_CSS_SHAPE_3);
    else if (n == 4) set_ext3 (H3_CSS_SHAPE_4); }

template < > int html_version::get_level < c_scroll_snap > () const
{   if ((ext3 () & H3_CSS_SNAP_4) == H3_CSS_SNAP_4) return 4;   
    if ((ext3 () & H3_CSS_SNAP_3) == H3_CSS_SNAP_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_scroll_snap > (const int n)
{   reset_ext3 (H3_CSS_SNAP_MASK);
    if (n == 3) set_ext3 (H3_CSS_SNAP_3);
    else if (n == 4) set_ext3 (H3_CSS_SNAP_4); }

template < > int html_version::get_level < c_scroll_snap_point > () const
{   if (any_ext4 (H4_CSS_SNAP_POINTS)) return 3;
    return 0; }

template < > void html_version::set_level < c_scroll_snap_point > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_SNAP_POINTS);
    else reset_ext4 (H4_CSS_SNAP_POINTS); }

template < > int html_version::get_level < c_spatial_navigation > () const
{   if (any_ext4 (H4_CSS_SPATIAL)) return 3;
    return 0; }

template < > void html_version::set_level < c_spatial_navigation > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_SPATIAL);
    else reset_ext4 (H4_CSS_SPATIAL); }

template < > int html_version::get_level < c_speech > () const
{   if (any_ext3 (H3_CSS_SPEECH)) return 3;
    return 0; }

template < > void html_version::set_level < c_speech > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_SPEECH);
    else reset_ext3 (H3_CSS_SPEECH); }

template < > int html_version::get_level < c_style_attribute > () const
{   if (any_ext2 (H2_CSS_STYLE)) return 3;
    return 0; }

template < > void html_version::set_level < c_style_attribute > (const int n)
{   if (n >= 3) set_ext2 (H2_CSS_STYLE);
    else reset_ext2 (H2_CSS_STYLE); }

template < > int html_version::get_level < c_syntax > () const
{   if (any_ext2 (H2_CSS_SYNTAX)) return 3;
    return 0; }

template < > void html_version::set_level < c_syntax > (const int n)
{   if (n == 3) set_ext2 (H2_CSS_SYNTAX);
    else reset_ext2 (H2_CSS_SYNTAX); }

template < > int html_version::get_level < c_table > () const
{   if (any_ext3 (H3_CSS_TABLE)) return 3;
    return 0; }

template < > void html_version::set_level < c_table > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_TABLE);
    else reset_ext3 (H3_CSS_TABLE); }

template < > int html_version::get_level < c_text > () const
{   if ((ext3 () & H3_CSS_TEXT_4) == H3_CSS_TEXT_4) return 4;
    if ((ext3 () & H3_CSS_TEXT_3) == H3_CSS_TEXT_3) return 3;
    return 0; }

template < > void html_version::set_level < c_text > (const int n)
{   reset_ext3 (H3_CSS_TEXT_MASK);
    if (n == 4) set_ext3 (H3_CSS_TEXT_34);
    else if (n == 3) set_ext3 (H3_CSS_TEXT_3); }

template < > int html_version::get_level < c_text_decoration > () const
{   if ((ext3 () & H3_CSS_TEXTDEC_4) == H3_CSS_TEXTDEC_4) return 4;
    if ((ext3 () & H3_CSS_TEXTDEC_3) == H3_CSS_TEXTDEC_3) return 3;
    return 0; }

template < > void html_version::set_level < c_text_decoration > (const int n)
{   reset_ext3 (H3_CSS_TEXTDEC_MASK);
    if (n == 4) set_ext3 (H3_CSS_TEXTDEC_34);
    else if (n == 3) set_ext3 (H3_CSS_TEXTDEC_3); }

template < > int html_version::get_level < c_transform > () const
{   if ((ext3 () & H3_CSS_TRANSFORM_4) == H3_CSS_TRANSFORM_4) return 4;
    if ((ext3 () & H3_CSS_TRANSFORM_3) == H3_CSS_TRANSFORM_3) return 3;
    return 0; }

template < > void html_version::set_level < c_transform > (const int n)
{   reset_ext3 (H3_CSS_TRANSFORM_MASK);
    if ((n == 2) || (n == 4)) set_ext3 (H3_CSS_TRANSFORM_34);
    else if ((n == 1) || (n == 3)) set_ext3 (H3_CSS_TRANSFORM_3); }

template < > int html_version::get_level < c_transition > () const
{   if ((ext4 () & H4_CSS_TRANSITION_4) == H4_CSS_TRANSITION_4) return 4;
    if ((ext4 () & H4_CSS_TRANSITION_3) == H4_CSS_TRANSITION_3) return 3;
    return 0; }

template < > void html_version::set_level < c_transition > (const int n)
{   reset_ext4 (H4_CSS_TRANSITION);
    if (n == 4) set_ext4 (H4_CSS_TRANSITION);
    else if (n == 3) set_ext4 (H4_CSS_TRANSITION_3); }

template < > int html_version::get_level < c_basic_user_interface > () const
{   if ((ext2 () & H2_CSS_UI_4) == H2_CSS_UI_4) return 4;   
    if ((ext2 () & H2_CSS_UI_3) == H2_CSS_UI_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_basic_user_interface > (const int n)
{   reset_ext2 (H2_CSS_UI_MASK);
    if (n == 3) set_ext2 (H2_CSS_UI_3);
    else if (n == 4) set_ext2 (H2_CSS_UI); }

template < > int html_version::get_level < c_value_unit > () const
{   if ((ext5 () & H5_CSS_VALUE_5) == H5_CSS_VALUE_5) return 5;   
    if ((ext5 () & H5_CSS_VALUE_4) == H5_CSS_VALUE_4) return 4;   
    if ((ext5 () & H5_CSS_VALUE_3) == H5_CSS_VALUE_3) return 3;   
    return 0; }

template < > void html_version::set_level < c_value_unit > (const int n)
{   reset_ext5 (H5_CSS_VALUE_MASK);
    if (n == 5) set_ext5 (H5_CSS_VALUE_345);
    else if (n == 4) set_ext5 (H5_CSS_VALUE_34);
    else if (n == 3) set_ext5 (H5_CSS_VALUE_3); }

template < > int html_version::get_level < c_viewport > () const
{   if (any_ext4 (H4_CSS_VIEWPORT)) return 3;
    return 0; }

template < > void html_version::set_level < c_viewport > (const int n)
{   if (n == 3) set_ext4 (H4_CSS_VIEWPORT);
    else reset_ext4 (H4_CSS_VIEWPORT); }

template < > int html_version::get_level < c_view_transition > () const
{   if ((ext5 () & H5_CSS_VIEWTRAN_4) == H5_CSS_VIEWTRAN_4) return 4;
    if ((ext5 () & H5_CSS_VIEWTRAN_3) == H5_CSS_VIEWTRAN_3) return 3;
    return 0; }

template < > void html_version::set_level < c_view_transition > (const int n)
{   reset_ext5 (H5_CSS_VIEWTRAN_MASK);
    if (n == 4) set_ext5 (H5_CSS_VIEWTRAN_34);
    else if (n == 3) set_ext5 (H5_CSS_VIEWTRAN_3); }

template < > int html_version::get_level < c_will_change > () const
{   if (any_ext3 (H3_CSS_WC)) return 3;
    return 0; }

template < > void html_version::set_level < c_will_change > (const int n)
{   if (n == 3) set_ext3 (H3_CSS_WC);
    else reset_ext3 (H3_CSS_WC); }

template < > int html_version::get_level < c_writing_mode > () const
{   if ((ext3 () & H3_CSS_WRITING_4) == H3_CSS_WRITING_4) return 4;
    if ((ext3 () & H3_CSS_WRITING_3) == H3_CSS_WRITING_3) return 3;
    return 0; }

template < > void html_version::set_level < c_writing_mode > (const int n)
{   reset_ext3 (H3_CSS_WRITING_MASK);
    if (n == 4) set_ext3 (H3_CSS_WRITING_34);
    else if (n == 3) set_ext3 (H3_CSS_WRITING_3); }

template < e_css_module MOD, e_css_module... MS > struct process_module : process_module < MS... >
{   static void set_level (html_version& v, const e_css_module m, const int n)
    {   if (m != MOD) process_module < MS... > :: set_level (v, m, n);
        else v.set_level < MOD > (n); }
    static int get_level (const html_version& v, const e_css_module m)
    {   if (m != MOD) return process_module < MS... > :: get_level (v, m);
        return v.get_level < MOD > (); } };

template < e_css_module MOD > struct process_module < MOD >
{   static void set_level (html_version& v, const e_css_module m, const int n)
    {   PRESUME (m == MOD, __FILE__, __LINE__);
        v.set_level < MOD > (n); }
    static int get_level (const html_version& v, const e_css_module m)
    {   PRESUME (m == MOD, __FILE__, __LINE__);
        return v.get_level < MOD > (); } };

int html_version::css_module (const e_css_module m) const
{   return process_module < CSS_MODULES > :: get_level (*this, m); }      

void html_version::css_module (const e_css_module m, const int n)
{   process_module < CSS_MODULES > :: set_level (*this, m, n); }

bool html_version::is_css_compatible (const flags_t& f2, const flags_t& f3, const flags_t& f4, const flags_t& f5) const
{   constexpr flags_t ext2_concerned = H2_FULL_CSS_MASK & ~H2_CSS_SYNTAX_MASK;
    if (((ext2_ & ext2_concerned) == 0) && ((ext3_ & H3_FULL_CSS_MASK) == 0) && ((ext4_ & H4_FULL_CSS_MASK) == 0) && ((ext5_ & H5_FULL_CSS_MASK) == 0)) return true;
    if (((f2 & ext2_concerned) == 0) && ((f3 & H3_FULL_CSS_MASK) == 0) && ((f4 & H4_FULL_CSS_MASK) == 0) && ((f5 & H5_FULL_CSS_MASK) == 0)) return true;
    if (((ext2_ & f2) != 0) || ((ext3_ & f3) != 0) || ((ext4_ & f4) != 0) || ((ext5_ & f5) != 0)) return true;
    if (((ext4_ & f4) & H4_CSS_SAFE) != 0) return true;
//    if ((ext4_ & H4_VTT) && (f4 & H4_VTT)) return true;
    if (((ext4_ & f4) & H4_VTT) != 0) return true;
    if (has_svg ())
    {   if (((f2 & H2_CSS_SVG_10) == H2_CSS_SVG_10) && ((ext_ & HE_SVG_10) == HE_SVG_10)) return true;
        if (((f2 & H2_CSS_SVG_11) == H2_CSS_SVG_11) && ((ext_ & HE_SVG_11) == HE_SVG_11)) return true;
        if (((f2 & H2_CSS_SVG_20) == H2_CSS_SVG_20) && ((ext_ & HE_SVG_20) == HE_SVG_20)) return true;
        if (((f2 & H2_CSS_SVG_21) == H2_CSS_SVG_21) && ((ext_ & HE_SVG_21) == HE_SVG_21)) return true;
        if (((f2 & H2_CSS_SVG_12) == H2_CSS_SVG_12) && ((ext_ & HE_SVG_12) == HE_SVG_12)) return true; }
    return false; }

bool html_version::is_css_compatible (nitpick& nits, const flags_t& f2, const flags_t& f3, const flags_t& f4, const flags_t& f5) const
{   if (is_css_compatible (f2, f3, f4, f5)) return true;
    nits.pick (nit_css_version, es_error, ec_css, "CSS ", long_css_version_name (), " required");   
    return false; }

void html_version::check_status (nitpick& nits, const ::std::string& s) const
{   if (context.profile_checks ())
    {   if (context.mobile_profile () && ((ext3_ & H3_NOT_MOBILE) == H3_NOT_MOBILE))
            nits.pick (nit_profile, es_warning, ec_css, s, " may be ignored when the CSS Mobile profile applies");   
        if (context.print_profile () && ((ext3_ & H3_NOT_PRINT) == H3_NOT_PRINT))
            nits.pick (nit_profile, es_warning, ec_css, s, " may be ignored when the CSS Print profile applies");   
        if (context.tv_profile () && ((ext3_ & H3_NOT_TV) == H3_NOT_TV))
            nits.pick (nit_profile, es_warning, ec_css, s, " may be ignored when the CSS TV profile applies"); }
    if (abandoned ())
        nits.pick (nit_abandoned, es_warning, ec_css, quote (s), " was rejected, abandoned, unfinished, andor unimplemented: it will at best be ignored");
    if (borked ())
        nits.pick (nit_borked, es_warning, ec_css, quote (s), " is known to be buggy, so cannot be relied on");
    if (dinosaur ())
        nits.pick (nit_dinosaur, es_warning, ec_css, quote (s), " is so ancient it will be recognised");
    if (experimental ())
        nits.pick (nit_experimental, es_warning, ec_css, quote (s), " is experimental, so unlikely to be recognised");
    if (css_deprecated ())   
        nits.pick (nit_deprecated, es_warning, ec_css, quote (s), " has been deprecated and should not be used");
    if (bizarritude ())
    {   if (chrome () && ! context.chrome ()) nits.pick (nit_chrome, es_warning, ec_browser, quote (s), " requires an appropriate version of a Chrome-based browser");
        if (ie () && ! context.ie ()) nits.pick (nit_ie, es_warning, ec_browser, quote (s), " requires an appropriate version of Internet Explorer");
        if (mozilla () && ! context.mozilla ()) nits.pick (nit_mozilla, es_warning, ec_browser, quote (s), " requires an appropriate version of a Mozilla browser, such as Firefox");
        if (netscape () && ! context.netscape ()) nits.pick (nit_netscape, es_warning, ec_browser, quote (s), " requires an appropriate version of the Netscape browser");
        if (opera () && ! context.opera ()) nits.pick (nit_opera, es_warning, ec_browser, quote (s), " requires an appropriate version of the Opera browser");
        if (webcomponents ()) nits.pick (nit_bespoke_obsolete, es_info, ec_browser, quote (s), " is bespoke WebComponents content");
        if (bespoke ()) nits.pick (nit_bespoke_obsolete, es_comment, ec_browser, quote (s), " is bespoke");
        if (safari () && ! context.safari ()) nits.pick (nit_safari, es_warning, ec_browser, quote (s), " requires an appropriate version of the Safari browser"); } }

bool parse_doctype (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   const bool res = version.parse_doctype (nits, ::std::string (b, e));
    if (! res) version.reset (html_0);
    return res; }

bool does_html_apply (const html_version& v, const html_version& from, const html_version& to)
{   if (from.ao () != to.ao ()) return true;
    if (from.ao () != ao_html) return true;
    if (! from.unknown () && (v < from)) return false;
    if (! to.unknown () && (v > to)) return false;
    if (context.microformats () && from.is_mf ()) return true;
    if (from.requires_extension ())
        if (extension_conflict (v, from) != emi_good) return false;
    if (! from.valid_context (v)) return false;
//    if (from.bizarritude ())
//    {   if (from.chrome () && ! context.chrome ()) return false;
//        if (from.ie () && ! context.ie ()) return false;
//        if (from.mozilla () && ! context.mozilla ()) return false;
//        if (from.netscape () && ! context.netscape ()) return false;
//        if (from.opera () && ! context.opera ()) return false;
//        if (from.safari () && ! context.safari ()) return false; }
    switch (v.mjr ())
    {   case 0 :    break;
        case 1 :    if (v.mnr () == 0) return ! from.not10 ();
                    PRESUME (v.mnr () == 1, __FILE__, __LINE__);
                    return ! from.notplus ();
        case 2 :    if (from.not2 ()) return false;
                    if (from.not2l1 () && (v.level () == 1)) return false;
                    if (! context.rfc_1867 () && from.rfc_1867 ()) return false;
                    if (! context.rfc_1942 () && from.rfc_1942 ()) return false;
                    if (! context.rfc_1980 () && from.rfc_1980 ()) return false;
                    if (! context.rfc_2070 () && from.rfc_2070 ()) return false;
                    break;
        case 3 :    if (v.mnr () == 2) return ! from.not32 ();
                    PRESUME (v.mnr () == 0, __FILE__, __LINE__);
                    return ! from.not30 ();
        case 4 :    switch (v.mnr ())
                    {   case 0 :
                        case 1 : return ! from.not4 ();
                        case 2 :
                        case 3 : return (! from.notx1 ()) || (from.svg_version () != sv_none) || (from.math_version () != math_none);
                        case 4 : return (! from.notx2 ()) || (from.svg_version () != sv_none) || (from.math_version () != math_none);
                        default : break; }
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    UNBREAKABLE;
        default :   if (from.xhtml () && from.notx5 ()) return false;
                    if (context.html_ver ().whatwg () && from.w3 ())
                        if (! from.ruby () || ! context.ruby ()) return false;
                        else if (context.html_ver () < html_ruby) return false;
                    switch (w3_5_minor (v))
                    {   case 0 : return ! from.not50 ();
                        case 1 : return ! from.not51 ();
                        case 2 : return ! from.not52 ();
                        case 3 : return ! from.not53 ();
                        default : break; }
                    break; }
    return true; }

bool overlap (const html_version& lhs_from, const html_version& lhs_to, const html_version& rhs_from, const html_version& rhs_to)
{   if (! lhs_to.unknown ())
    {   if (rhs_from > lhs_to) return false;
        if (lhs_to < rhs_from) return false; }
    if (! rhs_to.unknown ())
    {   if (lhs_from > rhs_to) return false;
        if (rhs_to < lhs_from) return false; }
    if (rhs_from > lhs_from) return does_apply (rhs_from, lhs_from, lhs_to);
    else return does_apply (lhs_from, rhs_from, rhs_to); }

int w3_minor_5 (const html_version& v) noexcept
{   if (! v.is_5 ()) return v.mnr ();
    if (v.mjr () < MAJOR_5_0) return 0;
    if ((v.mjr () == MAJOR_5_0) && (v.mnr () <= MINOR_5_0)) return 0;
    if (v.mjr () < MAJOR_5_1) return 1;
    if ((v.mjr () == MAJOR_5_1) && (v.mnr () <= MINOR_5_1)) return 1;
    if (v.mjr () < MAJOR_5_2) return 2;
    if ((v.mjr () == MAJOR_5_2) && (v.mnr () <= MINOR_5_2)) return 2;
    if (v.mjr () < MAJOR_5_3) return 3;
    if ((v.mjr () == MAJOR_5_3) && (v.mnr () <= MINOR_5_3)) return 3;
    return 4; }

int w3_5_minor (const html_version& v) noexcept
{   if (! v.is_5 ()) return v.mnr ();
    if ((v.mjr () == MAJOR_5_0) && (v.mnr () == MINOR_5_0)) return 0;
    if ((v.mjr () == MAJOR_5_1) && (v.mnr () == MINOR_5_1)) return 1;
    if ((v.mjr () == MAJOR_5_2) && (v.mnr () == MINOR_5_2)) return 2;
    if ((v.mjr () == MAJOR_5_3) && (v.mnr () == MINOR_5_3)) return 3;
    return -1; }

const char *default_charset (const html_version& v) noexcept
{   switch (v.mjr ())
    {   case 0 :
        case 1 : return US_ASCII;
        case 2 :
        case 3 :
        case 4 : return LATIN_1;
        case 5 : return LATIN_1;
        default : return UTF_8; } }

const char *alternative_charset (const html_version& v) noexcept
{   if (v.is_b4_2 () || v.is_4_or_more ()) return "";
    return US_ASCII; }

html_version get_min_version (const e_svg_version e) noexcept
{   switch (e)
    {   case sv_1_0 : return xhtml_svg_1_0;
        case sv_1_1 : return xhtml_svg_1_1;
        case sv_1_2_full : return xhtml_svg_1_2_tiny;
        case sv_1_2_tiny : return xhtml_svg_1_2_full;
        case sv_2_0 : return html_svg_2_0;
        case sv_2_1 : return html_svg_2_1;
        default : return html_0; } }

html_version get_min_version (const e_math_version e) noexcept
{   switch (e)
    {   case math_1 : return html_math_1;
        case math_2 : return xhtml_math_2;
        case math_3 : return html_math_3;
        case math_4 : return html_math_4;
        case math_core : return html_math_core;
        default : return html_0; } }

html_version get_min_version (const e_jsonld_version e) noexcept
{   switch (e)
    {   case jsonld_1_0 : return html_jsonld_1_0;
        case jsonld_1_1 : return html_jsonld_1_1;
        default : return html_0; } }

html_version get_min_version (const e_css_version e) noexcept
{   switch (e)
    {   case css_1 : return html_css_1;
        case css_2_0 : return html_css_2_0;
        case css_2_1 : return html_css_2_1;
        case css_2_2 : return html_css_2_2;
        case css_3 : return html_css_3;
        case css_4 : return html_css_4;
        case css_5 : return html_css_5;
        case css_6 : return html_css_6;
        default : return html_0; } }

bool is_css_identical (const html_version& lhs, const html_version& rhs)
{   if ((lhs.ext2 () & H2_FULL_CSS_MASK) != (rhs.ext2 () & H2_FULL_CSS_MASK)) return false;
    if ((lhs.ext3 () & H3_MPT_CSS_MASK) != (rhs.ext3 () & H3_MPT_CSS_MASK)) return false;
    if ((lhs.ext4 () & H4_FULL_CSS_MASK) != (rhs.ext4 () & H4_FULL_CSS_MASK)) return false;
    return (lhs.ext5 () & H5_FULL_CSS_MASK) == (rhs.ext5 () & H5_FULL_CSS_MASK); }

bool has_css_crossover (const html_version& lhs, const html_version& rhs, const flags_t f2, const flags_t f3, const flags_t f4, const flags_t f5) noexcept
{   const bool b2 = (((lhs.ext2 () & rhs.ext2 ()) & f2) != 0);
    const bool b3 = (((lhs.ext3 () & rhs.ext3 ()) & f3) != 0);
    const bool b4 = (((lhs.ext4 () & rhs.ext4 ()) & f4) != 0);
    const bool b5 = (((lhs.ext5 () & rhs.ext5 ()) & f5) != 0);
    return  b2 || b3 || b4 || b5; }

bool has_css_crossover (const e_css_version c, const html_version& lhs, const html_version& rhs) noexcept
{   switch (c)
    {   case css_1 :
        case css_2_0 :
        case css_2_1 :
        case css_2_2 : return (lhs.css_version () >= c) && (rhs.css_version () >= c);
        case css_3 : return has_css_crossover (lhs, rhs, H2_CSS_3_FULL, H3_CSS_3_FULL, H4_CSS_3_FULL, H5_CSS_3_FULL);
        case css_4 : return has_css_crossover (lhs, rhs, H2_CSS_4_FULL, H3_CSS_4_FULL, H4_CSS_4_FULL, H5_CSS_4_FULL);
        case css_5 : return has_css_crossover (lhs, rhs, H2_CSS_5_FULL, H3_CSS_5_FULL, H4_CSS_5_FULL, H5_CSS_5_FULL);
        case css_6 : return has_css_crossover (lhs, rhs, H2_CSS_6_FULL, H3_CSS_6_FULL, H4_CSS_6_FULL, H5_CSS_6_FULL);
        case css_2007 : return has_css_crossover (lhs, rhs, H2_CSS_2007, H3_CSS_2007, H4_CSS_2007, H5_CSS_2007);
        case css_2010 : return has_css_crossover (lhs, rhs, H2_CSS_2010, H3_CSS_2010, H4_CSS_2010, H5_CSS_2010);
        case css_2015 : return has_css_crossover (lhs, rhs, H2_CSS_2015, H3_CSS_2015, H4_CSS_2015, H5_CSS_2015);
        case css_2015_1 : return has_css_crossover (lhs, rhs, H2_CSS_2015_1, H3_CSS_2015_1, H4_CSS_2015_1, H5_CSS_2015_1);
        case css_2015_2 : return has_css_crossover (lhs, rhs, H2_CSS_2015_2, H3_CSS_2015_2, H4_CSS_2015_2, H5_CSS_2015_2);
        case css_2017 : return has_css_crossover (lhs, rhs, H2_CSS_2017, H3_CSS_2017, H4_CSS_2017, H5_CSS_2017);
        case css_2017_1 : return has_css_crossover (lhs, rhs, H2_CSS_2017_1, H3_CSS_2017_1, H4_CSS_2017_1, H5_CSS_2017_1);
        case css_2017_2 : return has_css_crossover (lhs, rhs, H2_CSS_2017_2, H3_CSS_2017_2, H4_CSS_2017_2, H5_CSS_2017_2);
        case css_2018 : return has_css_crossover (lhs, rhs, H2_CSS_2018, H3_CSS_2018, H4_CSS_2018, H5_CSS_2018);
        case css_2018_1 : return has_css_crossover (lhs, rhs, H2_CSS_2018_1, H3_CSS_2018_1, H4_CSS_2018_1, H5_CSS_2018_1);
        case css_2018_2 : return has_css_crossover (lhs, rhs, H2_CSS_2018_2, H3_CSS_2018_2, H4_CSS_2018_2, H5_CSS_2018_2);
        case css_2020 : return has_css_crossover (lhs, rhs, H2_CSS_2020, H3_CSS_2020, H4_CSS_2020, H5_CSS_2020);
        case css_2020_1 : return has_css_crossover (lhs, rhs, H2_CSS_2020_1, H3_CSS_2020_1, H4_CSS_2020_1, H5_CSS_2020_1);
        case css_2020_2 : return has_css_crossover (lhs, rhs, H2_CSS_2020_2, H3_CSS_2020_2, H4_CSS_2020_2, H5_CSS_2020_2);
        case css_2021 : return has_css_crossover (lhs, rhs, H2_CSS_2021, H3_CSS_2021, H4_CSS_2021, H5_CSS_2021);
        case css_2021_1 : return has_css_crossover (lhs, rhs, H2_CSS_2021_1, H3_CSS_2021_1, H4_CSS_2021_1, H5_CSS_2021_1);
        case css_2021_2 : return has_css_crossover (lhs, rhs, H2_CSS_2021_2, H3_CSS_2021_2, H4_CSS_2021_2, H5_CSS_2021_2);
        case css_2022 : return has_css_crossover (lhs, rhs, H2_CSS_2022, H3_CSS_2022, H4_CSS_2022, H5_CSS_2022);
        case css_2022_1 : return has_css_crossover (lhs, rhs, H2_CSS_2022_1, H3_CSS_2022_1, H4_CSS_2022_1, H5_CSS_2022_1);
        case css_2022_2 : return has_css_crossover (lhs, rhs, H2_CSS_2022_2, H3_CSS_2022_2, H4_CSS_2022_2, H5_CSS_2022_2);
        case css_2023 : return has_css_crossover (lhs, rhs, H2_CSS_2023, H3_CSS_2023, H4_CSS_2023, H5_CSS_2023);
        case css_2023_1 : return has_css_crossover (lhs, rhs, H2_CSS_2023_1, H3_CSS_2023_1, H4_CSS_2023_1, H5_CSS_2023_1);
        case css_2023_2 : return has_css_crossover (lhs, rhs, H2_CSS_2023_2, H3_CSS_2023_2, H4_CSS_2023_2, H5_CSS_2023_2);
        case css_2024 : return has_css_crossover (lhs, rhs, H2_CSS_2024, H3_CSS_2024, H4_CSS_2024, H5_CSS_2024);
        case css_2024_1 : return has_css_crossover (lhs, rhs, H2_CSS_2024_1, H3_CSS_2024_1, H4_CSS_2024_1, H5_CSS_2024_1);
        case css_2024_2 : return has_css_crossover (lhs, rhs, H2_CSS_2024_2, H3_CSS_2024_2, H4_CSS_2024_2, H5_CSS_2024_2);
        case css_2024_3 : return has_css_crossover (lhs, rhs, H2_CSS_2024_3, H3_CSS_2024_3, H4_CSS_2024_3, H5_CSS_2024_3);
        case css_2025 : return has_css_crossover (lhs, rhs, H2_CSS_2025, H3_CSS_2025, H4_CSS_2025, H5_CSS_2025);
        case css_ls_2024 : return has_css_crossover (lhs, rhs, H2_CSS_LS_2024, H3_CSS_LS_2024, H4_CSS_LS_2024, H4_CSS_LS_2024);
        case css_2025_1 : return has_css_crossover (lhs, rhs, H2_CSS_2025_1, H3_CSS_2025_1, H4_CSS_2025_1, H5_CSS_2025_1);
        case css_2025_2 : return has_css_crossover (lhs, rhs, H2_CSS_2025_2, H3_CSS_2025_2, H4_CSS_2025_2, H5_CSS_2025_2);
        case css_2025_3 : return has_css_crossover (lhs, rhs, H2_CSS_2025_3, H3_CSS_2025_3, H4_CSS_2025_3, H5_CSS_2025_3);
        case css_ls_2025 : return has_css_crossover (lhs, rhs, H2_CSS_LS_2025, H3_CSS_LS_2025, H4_CSS_LS_2025, H5_CSS_LS_2025);
        case css_2026 : return has_css_crossover (lhs, rhs, H2_CSS_2026, H3_CSS_2026, H4_CSS_2026, H5_CSS_2026);
        case css_2026_1 : return has_css_crossover (lhs, rhs, H2_CSS_2026_1, H3_CSS_2026_1, H4_CSS_2026_1, H5_CSS_2026_1);
        case css_2026_2 : return has_css_crossover (lhs, rhs, H2_CSS_2026_2, H3_CSS_2026_2, H4_CSS_2026_2, H5_CSS_2026_2);
        case css_2026_3 : return has_css_crossover (lhs, rhs, H2_CSS_2026_3, H3_CSS_2026_3, H4_CSS_2026_3, H5_CSS_2026_3);
        case css_ls_2026 : return has_css_crossover (lhs, rhs, H2_CSS_LS_2026, H3_CSS_LS_2026, H4_CSS_LS_2026, H5_CSS_LS_2026);
        default : return false; } } 

bool comparable (const html_version& lhs, const html_version& rhs) noexcept
{   if (lhs.is_css () != rhs.is_css ()) return false;
    return comparable (static_cast < version > (lhs), static_cast < version > (rhs)); }
