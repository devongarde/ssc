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
#include "parser/html_version.h"
#include "utility/common.h"
#include "main/context.h"
#include "type/type.h"

const char* doctype = "DOCTYPE";
CONSTEXPR ::std::size_t doctype_len = 7;
const char* docdot = "<!DOCTYPE ...>";

html_version::html_version (const boost::gregorian::date& d, const flags_t flags, const flags_t extensions, const flags_t e2)
        :   version (0, 0, flags | HV_WHATWG), ext_ (extensions), ext2_ (e2)
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
            else if (mjr () <= HTML_2022) set_ext2 (H2_MATH_4_20);
            else set_ext2 (H2_MATH_C);
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
            default : set_ext2 (H2_CSS_3); break; } }

void html_version::init (const unsigned short mjr)
{   switch (mjr)
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
        {   case 2 : res << "1.0"; break;
            case 3 : res << "1.1"; break;
            case 4 : res << "2.0"; break;
            default : res << "5"; } }
    else
    {   res << "HTML";
        if (known ())
            switch (mjr ())
            {   case 0 :
                    if (mnr () == 1) res << "Tags";
                    break;
                case 1 :
                    if (mnr () == 0) res << "1";
                    else if (mnr () == 1) res << "+";
                    break;
                case 2 :
                    res << "2";
                    if (level () > 0) res << "/" << level ();
                    break;
                case 3 :
                    res << "3." << GSL_NARROW_CAST <char> (mnr () + '0');
                    break;
                case 4 :
                    res << "4.0";
                    if (mnr () == 1) res << "1";
                    break;
                default:
                    res << minor_to_date (*this);
                    break; } }
    return res.str (); }

::std::string html_version::report () const
{   ::std::ostringstream res;
    res << name ();
    if (any_level ()) res << "." << level ();
    if (strict ()) res << "/Strict";
    if (frameset ()) res << "/Frameset";
    if (transitional ()) res << "/Transitional";
    if (has_svg ()) res << "/SVG-" << type_master < t_svg_version > :: name (svg_version ());
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
            if (cv > css_none) set_ext2 (H2_FULL_CSS_MASK, cm);
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
        if (cv > css_none) set_ext2 (H2_FULL_CSS_MASK, cm);
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
    if (! compare_no_case (doctype, content.substr (0, doctype_len)))
    {   nits.pick (nit_html_unknown_sgml, es_error, ec_parser, content.substr (0, doctype_len), " is not understood by " PROG);
        return true; }
    bool found_html = false;
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
        if (! s.empty ())  // should never happen, but ...
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
                    {   set_ext2 (H2_MATH_1); found_html = true; }
                    break;
                case doc_math2 :
                    if (note_parsed_version (nits, nit_math, xhtml_1_0, "XHTML 1.0 with MathML 2"))
                    {   set_ext2 (H2_MATH_2); found_html = true; }
                    break;
                case doc_math3 :
                    if (note_parsed_version (nits, nit_math, html_5_0, "HTML 5.0 with MathML 3"))
                    {   set_ext2 (H2_MATH_3); found_html = true; }
                    break;
                case doc_math4 :
                    if (note_parsed_version (nits, nit_math, html_apr21, "Living Standard (April 2021) with MathML 4"))
                    {   set_ext2 (H2_MATH_4); found_html = true; }
                    break;
                case doc_svg10 :
                    if (note_parsed_version (nits, nit_svg, xhtml_svg_1_0, "HTML 4.00 with SVG 1.0"))
                    {   svg_version (sv_1_0); found_html = true; }
                    break;
                case doc_svg11 :
                    if (note_parsed_version (nits, nit_svg, xhtml_svg_1_1, "XHTML 1.1 with SVG 1.1"))
                    {   svg_version (sv_1_1); found_html = true; }
                    break;
                case doc_svg20 :
                    if (note_parsed_version (nits, nit_svg, html_svg_2_0, "Living Standard (October 2018) with SVG 2.0"))
                    {   svg_version (sv_2_0); found_html = true; }
                    break;
                case doc_svg21 :
                    if (note_parsed_version (nits, nit_svg, html_svg_2_1, "Living Standard (April 2021) with SVG 2 (April 2021 draft)"))
                    {   svg_version (sv_2_1); found_html = true; }
                    break;
                case doc_compound_m :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, 0, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with MathML 2"))
                    {   set_ext2 (H2_MATH_2); math_version (math_2); found_html = true; }
                    break;
                case doc_compound_1_0 :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, HE_SVG_10, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with SVG 1.0 & MathML 2"))
                    {   set_ext2 (H2_MATH_2); set_ext (HE_SVG_10); math_version (math_2); svg_version (sv_1_0); found_html = true; }
                    break;
                case doc_compound_1_1 :
                    if (note_parsed_version (nits, nit_math, html_version (XHTML_1_1, 0, HE_SVG_11, H2_MATH_2 | H2_CSS_2_1), "XHTML 1.1 with SVG 1.1 & MathML 2"))
                    {   set_ext2 (H2_MATH_2); set_ext (HE_SVG_11); math_version (math_2); svg_version (sv_1_1); found_html = true; }
                    break;
                case doc_xhtml10_basic :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Basic")) set_flags (HV_BASIC);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml10_strict_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that strict XHTML 1.0 declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_strict :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Strict")) set_flags (HV_STRICT);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml10_loose_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that transitional XHTML 1.0 declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_loose :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Transitional")) set_flags (HV_TRANSITIONAL);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml10_frameset_superseded :
                    nits.pick (nit_xhtml_superseded, ed_x1, "W3C Recommendation 26 January 2000, revised 1 August 2002", es_warning, ec_parser, "that XHTML 1.0 frameset declaration was withdrawn before XHTML 1.0 was published");
                    FALLTHROUGH;
                case doc_xhtml10_frameset :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Frameset")) set_flags (HV_FRAMESET);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml10_mobile :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Mobile")) set_flags (HV_BASIC);
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml11 :
                    note_parsed_version (nits, nit_xhtml_1_1, xhtml_1_1, "XHTML 1.1");
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_xhtml2 :
                    note_parsed_version (nits, nit_xhtml_2_0, xhtml_2, "XHTML 2.0");
                    if (::boost::algorithm::starts_with (s, "http")) set_flags (HV_XHTML_DTD);
                    break;
                case doc_jan05 :
                    nits.pick (nit_draft_html_5, ed_jan05, "", es_warning, ec_parser, PROG " cannot properly process pre-draft HTML 5");
                    note_parsed_version (nits, nit_draft_html_5, html_jan05, "Web Apps Jan 2005");
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
                case doc_sqclose :
                    break;
                case doc_sqopen :
                    nits.pick (nit_sq_brac_ket, es_info, ec_parser, "ignoring [ ... ] details in <!DOCTYPE ... >");
                    sq_brac_ket = true;
                    break;
               default :
                    nits.pick (nit_internal_parsing_error, es_catastrophic, ec_parser, "bork! bork! bork! when parsing html_version: abandoning hope");
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
        else
        {   if (! found_public && ! found_system)
                if ((mjr () > 1) || ((mjr () == 1) && (mnr ()== 1)))
                    nits.pick (nit_public_missing, es_info, ec_parser, "Either PUBLIC or SYSTEM expected");
            if (found_unknown) if (context.tell (es_warning))
                nits.pick (nit_unexpected_doctype_content, es_warning, ec_parser, "Ignoring unexpected content (", quote (wtf), ") found in <!DOCTYPE>"); }
        return true; }
    nits.pick (nit_doctype_incomprehensible, es_catastrophic, ec_parser, PROG " does not understand the <!DOCTYPE> so is abandoning verification");
    return false; }

bool html_version::deprecated (const html_version& current) const
{   switch (context.math_version ())
    {   case math_2 :
            if (current.all_ext (H2_M2_DEPRECAT)) return true;
            break;
        case math_3 :
            if (current.all_ext (H2_M3_DEPRECAT)) return true;
            break;
        case math_4_20 :
        case math_4_22 :
            if (current.all_ext (H2_M4_DEPRECAT)) return true;
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

bool is_excluded (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    // have encountered occasional bugs with 64 bit manipulation on some platforms (a & b), but the &= operator appears reliable, so ...
    flags_t a = mask, b = mask;
    a &= lhs.ext ();
    b &= rhs.ext ();
    if ((a == 0) || (b == 0)) return false;
    a &= b;
    return (a == 0); }

bool is_excluded2 (const html_version& lhs, const html_version& rhs, const flags_t mask)
{   PRESUME (mask != 0, __FILE__, __LINE__);
    // have encountered occasional bugs with 64 bit manipulation on some platforms (a & b), but the &= operator appears reliable, so ...
    flags_t a = mask, b = mask;
    a &= lhs.ext2 ();
    b &= rhs.ext2 ();
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

e_css_version html_version::css_version () const noexcept
{   if (all_ext2 (H2_CSS_6)) return css_6;
    if (all_ext2 (H2_CSS_5)) return css_5;
    if (all_ext2 (H2_CSS_4)) return css_4;
    if (all_ext2 (H2_CSS_3)) return css_3;
    if (all_ext2 (H2_CSS_2_2)) return css_2_2;
    if (all_ext2 (H2_CSS_2_1)) return css_2_1;
    if (all_ext2 (H2_CSS_2_0)) return css_2_0;
    if (all_ext2 (H2_CSS_1)) return css_1;
    return css_none; }

::std::string subver (const int b, const int n, const char* s)
{   ::std::string res;
    if (n > b)
    {   res += "+";
        res += s;
        res += ::boost::lexical_cast < ::std::string > (n); }
    return res; }

::std::string html_version::css_version_name () const
{   if (all_ext2 (H2_CSS_6)) return "6";
    ::std::string res;
    int b = INT_MAX;
    if (all_ext2 (H2_CSS_5)) { res = "5"; b = 5; }
    else if (all_ext2 (H2_CSS_4)) { res = "4"; b = 4; }
    else if (all_ext2 (H2_CSS_3)) { res = "3"; b = 3; }
    else if (all_ext2 (H2_CSS_2_2)) { res = "2.2"; b = 2; }
    else if (all_ext2 (H2_CSS_2_1)) { res = "2.1"; b = 2; }
    else if (all_ext2 (H2_CSS_2_0)) { res = "2.0"; b = 2; }
    else if (all_ext2 (H2_CSS_1)) { res = "1"; b = 1; }
    else return "";
    PRESUME (b < 7, __FILE__, __LINE__);
    res += subver (b, css_cascade (), "Cas");
    res += subver (b, css_colour (), "Col");
    res += subver (b, css_media (), "Med");
    res += subver (b, css_namespace (), "Ns");
    res += subver (b, css_selector (), "Sel");
    res += subver (b, css_style (), "Sty");
    res += subver (b, css_ui (), "UI");
    return res; }

void html_version::css_version (const e_css_version v) noexcept
{   reset_ext2 (H2_FULL_CSS_MASK);
    switch (v)
    {   case css_1 : set_ext2 (H2_CSS_1); break;
        case css_2_0 : set_ext2 (H2_CSS_2_0_FULL); break;
        case css_2_1 : set_ext2 (H2_CSS_2_1_FULL); break;
        case css_2_2 : set_ext2 (H2_CSS_2_2_FULL); break;
        case css_3 : set_ext2 (H2_CSS_3_FULL); break;
        case css_4 : set_ext2 (H2_CSS_4_FULL); break;
        case css_5 : set_ext2 (H2_CSS_5_FULL); break;
        case css_6 : set_ext2 (H2_CSS_6_FULL); break;
        default : break; } }

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

bool html_version::math_4_core () const noexcept
{   return (any_ext2 (H2_MATH_C)); }

e_math_version html_version::math_version () const noexcept
{   if (all_ext2 (H2_MATH_4_22)) return math_4_22;
    if (all_ext2 (H2_MATH_C)) return math_core;
    if (all_ext2 (H2_MATH_4_20)) return math_4_20;
    if (all_ext2 (H2_MATH_3)) return math_3;
    if (all_ext2 (H2_MATH_2)) return math_2;
    if (all_ext2 (H2_MATH_1)) return math_1;
    return math_none; }

::std::string html_version::math_version_name () const
{   if (all_ext2 (H2_MATH_4_22)) return "4(Aug22)";
    if (all_ext2 (H2_MATH_C)) return "core";
    if (all_ext2 (H2_MATH_4_20)) return "4(Dec20)";
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
        case math_4_20 : set_ext2 (H2_MATH_4_20); break;
        case math_core : set_ext2 (H2_MATH_C); break;
        case math_4_22 : set_ext2 (H2_MATH_4_22); break;
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
{   if (xhtml ()) return false;
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

int html_version::css_cascade () const
{   if ((ext2 () & H2_CSS_CASCADE_6) == H2_CSS_CASCADE_6) return 6;   
    if ((ext2 () & H2_CSS_CASCADE_5) == H2_CSS_CASCADE_5) return 5;   
    if ((ext2 () & H2_CSS_CASCADE_4) == H2_CSS_CASCADE_4) return 4;   
    if ((ext2 () & H2_CSS_CASCADE_3) == H2_CSS_CASCADE_3) return 3;   
    return 0; }

void html_version::css_cascade (const int n)
{   reset_ext2 (H2_CSS_CASCADE_MASK);
    switch (n)
    {   case 6 : set_ext2 (H2_CSS_CASCADE_6 | H2_CSS_CASCADE_5 | H2_CSS_CASCADE_4 | H2_CSS_CASCADE_3); break;
        case 5 : set_ext2 (H2_CSS_CASCADE_5 | H2_CSS_CASCADE_4 | H2_CSS_CASCADE_3); break;
        case 4 : set_ext2 (H2_CSS_CASCADE_4 | H2_CSS_CASCADE_3); break;
        case 3 : set_ext2 (H2_CSS_CASCADE_3); break;
        default : break; } }

int html_version::css_colour () const
{   if ((ext2 () & H2_CSS_COLOUR_5) == H2_CSS_COLOUR_5) return 5;   
    if ((ext2 () & H2_CSS_COLOUR_4) == H2_CSS_COLOUR_4) return 4;   
    if ((ext2 () & H2_CSS_COLOUR_3) == H2_CSS_COLOUR_3) return 3;   
    return 0; }

void html_version::css_colour (const int n)
{   reset_ext2 (H2_CSS_COLOUR_MASK);
    switch (n)
    {   case 5 : set_ext2 (H2_CSS_COLOUR_5 | H2_CSS_COLOUR_4 | H2_CSS_COLOUR_3); break;
        case 4 : set_ext2 (H2_CSS_COLOUR_4 | H2_CSS_COLOUR_3); break;
        case 3 : set_ext2 (H2_CSS_COLOUR_3); break;
        default : break; } }

int html_version::css_custom () const
{   if (any_ext2 (H2_CSS_CUSTOM)) return 3;
    return 0; }

void html_version::css_custom (const int n)
{   if (n > 0) set_ext2 (H2_CSS_CUSTOM);
    else reset_ext2 (H2_CSS_CUSTOM); }

int html_version::css_media () const
{   if ((ext2 () & H2_CSS_MEDIA_5) == H2_CSS_MEDIA_5) return 5;   
    if ((ext2 () & H2_CSS_MEDIA_4) == H2_CSS_MEDIA_4) return 4;   
    if ((ext2 () & H2_CSS_MEDIA_3) == H2_CSS_MEDIA_3) return 3;   
    return 0; }

void html_version::css_media (const int n)
{   reset_ext2 (H2_CSS_MEDIA_MASK);
    switch (n)
    {   case 5 : set_ext2 (H2_CSS_MEDIA_5 | H2_CSS_MEDIA_4 | H2_CSS_MEDIA_3); break;
        case 4 : set_ext2 (H2_CSS_MEDIA_4 | H2_CSS_MEDIA_3); break;
        case 3 : set_ext2 (H2_CSS_MEDIA_3); break;
        default : break; } }

int html_version::css_namespace () const
{   if (any_ext2 (H2_CSS_NAMESPACE)) return 3;
    return 0; }

void html_version::css_namespace (const int n)
{   if (n == 3) set_ext2 (H2_CSS_NAMESPACE);
    else reset_ext2 (H2_CSS_NAMESPACE); }

int html_version::css_selector () const
{   if ((ext2 () & H2_CSS_SELECTOR_4) == H2_CSS_SELECTOR_4) return 4;   
    if ((ext2 () & H2_CSS_SELECTOR_3) == H2_CSS_SELECTOR_3) return 3;   
    return 0; }

void html_version::css_selector (const int n)
{   reset_ext2 (H2_CSS_SELECTOR_MASK);
    if (n == 3) set_ext2 (H2_CSS_SELECTOR_3);
    else if (n == 4) set_ext2 (H2_CSS_SELECTOR_3 | H2_CSS_SELECTOR_4); }

int html_version::css_style () const
{   if (any_ext2 (H2_CSS_STYLE)) return 3;
    return 0; }

void html_version::css_style (const int n)
{   if (n >= 3) set_ext2 (H2_CSS_STYLE);
    else reset_ext2 (H2_CSS_STYLE); }

int html_version::css_syntax () const
{   if (any_ext2 (H2_CSS_SYNTAX)) return 3;
    return 0; }

void html_version::css_syntax (const int n)
{   if (n == 3) set_ext2 (H2_CSS_SYNTAX);
    else reset_ext2 (H2_CSS_SYNTAX); }

int html_version::css_ui () const
{   if ((ext2 () & H2_CSS_UI_4) == H2_CSS_UI_4) return 4;   
    if ((ext2 () & H2_CSS_UI_3) == H2_CSS_UI_3) return 3;   
    return 0; }

void html_version::css_ui (const int n)
{   reset_ext2 (H2_CSS_UI_MASK);
    if (n == 3) set_ext2 (H2_CSS_UI_3);
    else if (n == 4) set_ext2 (H2_CSS_UI_3 | H2_CSS_UI_4); }

int html_version::css_value () const
{   if ((ext2 () & H2_CSS_VALUE_4) == H2_CSS_VALUE_4) return 4;   
    if ((ext2 () & H2_CSS_VALUE_3) == H2_CSS_VALUE_3) return 3;   
    return 0; }

void html_version::css_value (const int n)
{   reset_ext2 (H2_CSS_UI_MASK);
    if (n == 3) set_ext2 (H2_CSS_VALUE_3);
    else if (n == 4) set_ext2 (H2_CSS_VALUE_3 | H2_CSS_VALUE_4); }


bool parse_doctype (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   bool res = version.parse_doctype (nits, ::std::string (b, e));
    if (! res) version.reset (html_0);
    return res; }

bool does_html_apply (const html_version& v, const html_version& from, const html_version& to)
{   if (! from.unknown () && (v < from)) return false;
    if (context.microformats () && from.is_mf ()) return true;
    if (! to.unknown () && (v > to)) return false;
    if (from.requires_extension ())
        if (extension_conflict (v, from) != emi_good) return false;
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
                    if (context.html_ver ().whatwg () && from.w3 ()) return false;
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
        case math_4_20 : return html_math_4_20;
        case math_core : return html_math_core;
        case math_4_22 : return html_math_4_22;
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
