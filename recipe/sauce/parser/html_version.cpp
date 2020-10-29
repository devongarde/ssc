/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
const ::std::size_t doctype_len = 7;
const char* docdot = "<!DOCTYPE ...>";

html_version::html_version (const BYTE major, const BYTE minor, const uint64_t flags, const uint64_t extensions)
        :   major_ (major), minor_ (minor), flags_ (flags), ext_ (extensions)
{   if (minor_ == 0xFF)
        if (major_ == 5) minor_ = context.html_minor ();
        else minor_ = 0; }

void html_version::swap (html_version& v) noexcept
{   ::std::swap (major_, v.major_);
    ::std::swap (minor_, v.minor_);
    ::std::swap (flags_, v.flags_);
    ::std::swap (ext_, v.ext_); }

::std::string minor_to_date (const html_version& v)
{   assert (v.major () >= 5);
    if (v == html_5_0) return "5.0";
    if (v == html_5_1) return "5.1";
    if (v == html_5_2) return "5.2";
    if (v == html_5_3) return "5.3";
    ::std::string res ("5:");
    if (v.major () <= 9)
    {   res += "0";
        res += static_cast <char> (v.major () + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (static_cast < int > (v.major ()));
    int mon = v.minor () / 16;
    if (mon <= 9)
    {   res += "0";
        res += static_cast <char> (mon + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (mon);
    int day = v.minor () % 16;
    day *= 2;
    day += 1;
    if (day <= 9)
    {   res += "0";
        res += static_cast <char> (day + '0'); }
    else res += ::boost::lexical_cast < ::std::string > (day);
    return res; }

::std::string html_version::report () const
{   ::std::ostringstream res;
    if (known () && (major_ == 4) && (minor_ > 1))
    {   res << "XHTML";
        switch (minor_)
        {   case 2 : res << "1.0"; break;
            case 3 : res << "1.1"; break;
            case 4 : res << "2.0"; break; } }
    else
    {   res << "HTML";
        if (known ())
            switch (major_)
            {   case 0 :
                    if (minor_ == 1) res << "Tags";
                    break;
                case 1 :
                    if (minor_ == 0) res << "1";
                    else if (minor_ == 1) res << "+";
                    break;
                case 2 :
                    res <<  "2";
                    if (level () > 0) res << "/" << level ();
                    break;
                case 3 :
                    res <<  "3." << static_cast <char> (minor_ + '0');
                    break;
                case 4 :
                    res <<  "4";
                    if (minor_ == 1) res << ".01";
                    else res << ".00";
                    break;
                default:
                    res << minor_to_date (*this);
                    break; } }
    if ((flags_ & HV_LEVEL_MASK) != 0) res << "." << (flags_ & HV_LEVEL_MASK);
    if ((flags_ & HV_STRICT) == HV_STRICT) res << "/strict";
    if ((flags_ & HV_FRAMESET) == HV_FRAMESET) res << "/frameset";
    if ((flags_ & HV_TRANSITIONAL) == HV_TRANSITIONAL) res << "/transitional";
    if (has_svg ()) res << "/SVG-" << type_master < t_svg_version > :: name (svg_version ());
    if (has_math ()) res << "/MathML-" << math_version ();
    if (has_xlink ()) res << "/xLink"; // << xlink ();
    if (has_rdf ()) res << "/rdf"; // << rdf ();
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
    if (bespoke ()) res << "/obscure";
    if ((flags_ & HV_DEPRECATED_MASK) != 0) res << "/deprecated";
    return res.str (); }

::std::string html_version::detailed_report () const
{   return report (); }

bool html_version::note_parsed_version (nitpick& nits, const e_nit n, const html_version& got, const ::std::string& gen)
{   if (is_not (got))
    {   if (got > *this)
        {   nits.pick (nit_html_contradictory, es_warning, ec_parser, report (), " upgraded to ", got.report ());
            reset (got);
            return true; }
        if (got.has_svg ())
            if (! has_svg () || (got.svg_version () >= svg_version ()))
            {   nits.pick (nit_svg, es_comment, ec_parser, "SVG recognised");
                return true; }
        if (got.has_math ())
            if (! has_math ())
            {   nits.pick (nit_svg, es_comment, ec_parser, "MathML recognised");
                return true; }
        nits.pick (nit_html_contradictory, es_warning, ec_parser, "contradictory ", gen, " statement encountered");
        return true; }
    if (unknown ())
    {   nits.pick (n, es_comment, ec_parser, gen, " recognised");
        reset (got); }
    return true; }

bool html_version::invalid_addendum (const html_version& v) const
{   if (microdata ())
        if (context.microdata ()) return false;
        else if (v.whatwg ()) return false;
        else return (v.major () < 5) || (w3_minor_5 (v) < 4);
    if (rdf ()) return (! context.rdf ()) && (v != xhtml_2);
    return (frameset () && ! v.frameset ()); }

bool html_version::parse_doctype (nitpick& nits, const::std::string& content)
{   nits.set_context (0, trim_the_lot_off (content));
    if (! compare_no_case (doctype, content.substr (0, doctype_len))) // probably best changed to an assert
    {   if (context.presume_tags ())
        {   nits.pick (nit_presume_html_tags, ed_tags, "", es_info, ec_parser, "no <!DOCTYPE> found, presuming HTML Tags");
            reset (html_tags); }
        else
        if ((context.html_major () == 0) && (context.html_minor () == 0))
        {   nits.pick (nit_presume_html_1, ed_1, "", es_info, ec_parser, "no <!DOCTYPE> found, presuming HTML 1.0");
            reset (html_1); }
        else
        {   reset (context.html_ver ());
            nits.pick (nit_html, es_info, ec_parser, "no <!DOCTYPE> found, presuming ", report ()); }
        return true; }
    bool found_html = false;
    bool found_public = false;
    bool found_system = false;
    bool found_unknown = false;
    bool sq_bra_ket = false;
    ::std::string::size_type pos = doctype_len;
    vstr_t keywords = split_quoted_by_space (trim_the_lot_off (content.substr (pos)));
    if (keywords.empty ())
    {   nits.pick (nit_html_unrecognised, es_error, ec_parser, "Document type not specified. This is not an HTML file. Abandoning verification");
        return false; }
    for (auto s : keywords)
        if (! s.empty ())  // should never happen, but ...
        {   if (sq_bra_ket)
            {   if (s != "]") continue;  // broken by nesting, if it's permitted
                sq_bra_ket = false; }
            if (s.at (0) == '"') s = s.substr (1);  // crude way to remove excess "
            pos = s.length ();
            if (pos == 0) continue;
            if (s.at (pos - 1) == '"') s = s.substr (0, pos - 1);
            e_sgml d = symbol < e_sgml > :: find (s); // crude way to handle case
            if (d == doc_unknown) d = symbol < e_sgml > :: find (::boost::algorithm::to_lower_copy (s));
            switch (d)
            {   case doc_unknown : found_unknown = true; break;
                case doc_html : found_html = true; break;
                case doc_public: found_public = true; break;
                case doc_system: found_system = true; break;
                case doc_htmlplus :
                    if (note_parsed_version (nits, nit_html_plus, html_plus, "HTML+"))
                        found_html = true;
                    break;
                case doc_math :
                case doc_svg :
                    break;
                case doc_math1 :
                    if (note_parsed_version (nits, nit_math, xhtml_1_0, "XHTML 1.0 with MathML 1"))
                    {   ext_ |= HE_MATH_1; found_html = true; }
                    break;
                case doc_math2 :
                    if (note_parsed_version (nits, nit_math, html_5_0, "HTML 5.0 with MathML 2"))
                    {   ext_ |= HE_MATH_2; found_html = true; }
                    break;
                case doc_math3 :
                    if (note_parsed_version (nits, nit_math, html_5_2, "HTML 5.2 with MathML 3"))
                    {   ext_ |= HE_MATH_3; found_html = true; }
                    break;
                case doc_math4 :
                    if (note_parsed_version (nits, nit_math, html_5_3, "HTML 5.3 with MathML 4"))
                    {   ext_ |= HE_MATH_4; found_html = true; }
                    break;
                case doc_svg1 :
                    if (note_parsed_version (nits, nit_svg, html_version (HTML_4_0, 0, HE_SVG_1_0), "HTML 4.00 with SVG 1.0"))
                    {   svg_version (sv_1_0); found_html = true; }
                    break;
                case doc_svg11 :
                    if (note_parsed_version (nits, nit_svg, html_version (HTML_4_01, 0, HE_SVG_1_1), "HTML 4.01 with SVG 1.1"))
                    {   svg_version (sv_1_1); found_html = true; }
                    break;
                case doc_svg2 :
                    if (note_parsed_version (nits, nit_svg, html_version (HTML_5_3, 0, HE_SVG_2_0), "HTML 5.3 with SVG 2.0"))
                    {   svg_version (sv_2_0); found_html = true; }
                    break;
                case doc_compound :
                    if (note_parsed_version (nits, nit_math, html_version (HTML_5_1, 0, HE_SVG_1_0 | HE_MATH_2), "HTML 5.1 with SVG 1.0 & MathML 2"))
                    {   ext_ |= HE_MATH_2; svg_version (sv_1_0); found_html = true; }
                    break;
                case doc_xhtml10_basic :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Basic")) flags_ |= HV_BASIC;
                    break;
                case doc_xhtml10_strict :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Strict")) flags_ |= HV_STRICT;
                    break;
                case doc_xhtml10_loose :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Transitional")) flags_ |= HV_TRANSITIONAL;
                    break;
                case doc_xhtml10_frameset :
                    if (note_parsed_version (nits, nit_xhtml_1_0, xhtml_1_0, "XHTML 1.0 Frameset")) flags_ |= HV_FRAMESET;
                    break;
                case doc_xhtml11 :
                    note_parsed_version (nits, nit_xhtml_1_1, xhtml_1_1, "XHTML 1.1");
                    break;
                case doc_xhtml2 :
                    note_parsed_version (nits, nit_xhtml_2_0, xhtml_2, "XHTML 2.0");
                    break;
                case doc_html5 :
                    note_parsed_version (nits, nit_html_5_0, html_5_0, "HTML 5");
                    break;
                case doc_html400_strict :
                    if (note_parsed_version (nits, nit_html_4_00s, html_4_0, "HTML 4.00 Strict")) flags_ |= HV_STRICT;
                    break;
                case doc_html400_loose :
                    note_parsed_version (nits, nit_html_4_00, html_4_0, "HTML 4.00");
                    break;
                case doc_html400_frameset :
                    if (note_parsed_version (nits, nit_html_4_00f, html_4_0, "HTML 4.00 Frameset")) flags_ |= HV_FRAMESET;
                    break;
                case doc_latin :
                case doc_special :
                case doc_symbols :
                    break;
                case doc_html401_strict :
                    if (note_parsed_version (nits, nit_html_4_01s, html_4_1, "HTML 4.01 Strict")) flags_ |= HV_STRICT;
                    break;
                case doc_html401_loose :
                    if (note_parsed_version (nits, nit_html_4_01, html_4_1, "HTML 4.01 Transitional")) flags_ |= HV_TRANSITIONAL;
                    break;
                case doc_html401_frameset :
                    if (note_parsed_version (nits, nit_html_4_01f, html_4_1, "HTML 4.01 Frameset")) flags_ |= HV_FRAMESET;
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
                    if (note_parsed_version (nits, nit_html_2_0s, html_2, "HTML 2.0 Strict")) flags_ |= HV_STRICT;
                    break;
                case doc_html20_int :
                    if (! context.rfc_2070 ())
                    {   nits.pick (nit_rfc_2070, es_error, ec_parser, "HTML 2.0 International (RFC 2070), which is disabled: abandoning verification");
                        return false; }
                    if (note_parsed_version (nits, nit_html_2_0i, html_2, "HTML 2.0 International")) flags_ |= HV_INT;
                    break;
                case doc_html21 :
                    if (note_parsed_version (nits, nit_html_2_0l1, html_2_level_1, "HTML 2.0 Level 1")) flags_ |= 1;
                    break;
                case doc_html21_strict :
                    if (note_parsed_version (nits, nit_html_2_0l1s, html_2, "HTML 2.0 Level 1 Strict")) flags_ |= HV_STRICT | 1;
                    break;
                case doc_html22 :
                    if (note_parsed_version (nits, nit_html_2_0l2, html_2_level_2, "HTML 2.0 Level 2")) flags_ |= 2;
                    break;
                case doc_html1 :
                    note_parsed_version (nits, nit_html_tags, html_tags, "HTML 1.0");
                case doc_sqclose :
                    break;
                case doc_sqopen :
                    nits.pick (nit_sq_bra_ket, es_info, ec_parser, "ignoring [ ... ] details in <!DOCTYPE ... >");
                    sq_bra_ket = true;
                    break;
               default :
                    nits.pick (nit_internal_parsing_error, es_catastrophic, ec_parser, "bork! bork! bork! when parsing html_version. Abandoning hope");
                    return false; } }
    if (found_html)
    {   if (unknown ())
        {   if (found_unknown)
            {   nits.pick (nit_html_unknown_sgml, es_warning, ec_parser, "The HTML declaration in <!DOCTYPE ...> contains unrecognised content. Abandoning verification");
                return false; }
            ::std::string ver ("HTML 5.");
            ver += static_cast < char > ('0' + context.html_minor ());
            switch (context.html_minor ())
            {   case 0 : note_parsed_version (nits, nit_html_5_0, html_5_0, ver); break;
                case 1 : note_parsed_version (nits, nit_html_5_1, html_5_1, ver); break;
                case 2 : note_parsed_version (nits, nit_html_5_2, html_5_2, ver); break;
                case 3 : note_parsed_version (nits, nit_html_5_3, html_5_3, ver); break;
                default : note_parsed_version (nits, nit_html_20_07, html_jul_20, ver); break; }
            if (found_public)
                nits.pick (nit_public_unexpected, es_warning, ec_parser, "PUBLIC is unexpected"); }
        else
        {   if (! found_public && ! found_system)
                if ((major_ > 1) || ((major_ == 1) && (minor_ == 1)))
                    nits.pick (nit_public_missing, es_info, ec_parser, "Either PUBLIC or SYSTEM expected");
            if (found_unknown) if (context.tell (e_warning))
                nits.pick (nit_unexpected_doctype_content, es_warning, ec_parser, "Ignoring unexpected content found in <!DOCTYPE>"); }
        return true; }
    nits.pick (nit_doctype_incomprehensible, es_catastrophic, ec_parser, PROG " does not understand the <!DOCTYPE>. Is HTML missing? Abandoning verification");
    return false; }

bool html_version::deprecated (const html_version& current) const
{   switch (current.major_)
    {   case 1 : return (current.flags_ & HV_DEPRECATED1) != 0;
        case 2 : return (current.flags_ & HV_DEPRECATED2) != 0;
        case 3 :
            switch (current.minor_)
            {   case 0 : return (flags_ & HV_DEPRECATED30) != 0;
                case 2 : return (flags_ & HV_DEPRECATED32) != 0; }
            assert (false); break;
        case 4:
            switch (current.minor_)
            {   case 0 :
                case 1 : return (flags_ & HV_DEPRECATED4) != 0;
                case 2 : return (flags_ & HV_DEPRECATEDX1) != 0;
                case 3 : return (flags_ & HV_DEPRECATEDX11) != 0;
                case 4 : return (flags_ & HV_DEPRECATEDX2) != 0; }
            assert (false); break;
        default :
            switch (w3_minor_5 (current))
            {   case 0 : return (flags_ & HV_DEPRECATED50) != 0;
                case 1 : return (flags_ & HV_DEPRECATED51) != 0;
                case 2 : return (flags_ & HV_DEPRECATED52) != 0;
                case 3 : return (flags_ & HV_DEPRECATED53) != 0; } }
    return false; }

bool html_version::lazy () const
{   if (major_ > 1) return true;
    if (major_ == 0) return false;
    return (minor_ > 0); }


typedef enum { emi_good, emi_math, emi_not_svg, emi_svg, emi_rdf } e_emi;
e_emi extension_conflict (const html_version& lhs, const html_version& rhs)
{   if (lhs.major () < 4) return emi_good;
    if (! lhs.has_math () && rhs.has_math ()) return emi_math;
    if (! lhs.has_svg () && rhs.has_svg ())
    {   if (rhs.svg_old_html () && (lhs.major () == 4)) return emi_good;
        if (rhs.rdf () && lhs.has_rdf ()) return emi_good;
        if (rhs.svg_x1 () && (lhs.major () == 4) && (lhs.minor () >= 2) && (lhs.minor () <= 3)) return emi_good;
        if (rhs.svg_x2 () && (lhs.major () == 4) && (lhs.minor () == 4)) return emi_good;
        return emi_svg; }
    else if (lhs.has_svg () && rhs.not_svg ()) return emi_not_svg;
    if (! lhs.has_rdf () && rhs.has_rdf ()) return emi_rdf;
    return emi_good; }

bool html_version::check_math_svg (nitpick& nits, const html_version& a, const ::std::string& x) const
{   switch (extension_conflict (*this, a))
    {   case emi_math : nits.pick (nit_math, es_error, ec_attribute, quote (x), " requires MathML"); return false;
        case emi_not_svg : nits.pick (nit_svg, es_error, ec_attribute, quote (x), " cannot be applied to SVG elements"); return false;
        case emi_svg : nits.pick (nit_svg, es_error, ec_attribute, quote (x), " requires SVG"); return false;
        case emi_rdf : nits.pick (nit_rdf, es_error, ec_attribute, quote (x), " requires RDFa"); return false;
        default : break; }
    return true; }

e_svg_version html_version::svg_version () const
{   if ((ext_ & HE_SVG_2_0) == HE_SVG_2_0) return sv_2_0;
    if ((ext_ & HE_SVG_1_2_FULL) == HE_SVG_1_2_FULL) return sv_1_2_full;
    if ((ext_ & HE_SVG_1_2_TINY) == HE_SVG_1_2_TINY) return sv_1_2_tiny;
    if ((ext_ & HE_SVG_1_1) == HE_SVG_1_1) return sv_1_1;
    if ((ext_ & HE_SVG_1_0) == HE_SVG_1_0) return sv_1_0;
    return sv_none; }

void html_version::svg_version (const e_svg_version v)
{   ext_reset (SVG_MASK);
    switch (v)
    {   case sv_1_0 : ext_set (HE_SVG_1_0); break;
        case sv_1_1 : ext_set (HE_SVG_1_1); break;
        case sv_1_2_tiny : ext_set (HE_SVG_1_2_TINY); break;
        case sv_1_2_full : ext_set (HE_SVG_1_2_FULL); break;
        case sv_2_0 : ext_set (HE_SVG_2_0); break;
        default : break; } }

e_math_version html_version::math_version () const
{   if ((ext_ & HE_MATH_4) == HE_MATH_4) return math_4;
    if ((ext_ & HE_MATH_3) == HE_MATH_3) return math_3;
    if ((ext_ & HE_MATH_2) == HE_MATH_2) return math_2;
    if ((ext_ & HE_MATH_1) == HE_MATH_1) return math_1;
    return math_none; }

void html_version::math_version (const e_math_version v)
{   ext_reset (MATH_MASK);
    switch (v)
    {   case math_1 : ext_set (HE_MATH_1); break;
        case math_2 : ext_set (HE_MATH_2); break;
        case math_3 : ext_set (HE_MATH_3); break;
        case math_4 : ext_set (HE_MATH_4); break;
        default : break; } }

bool parse_doctype (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   bool res = version.parse_doctype (nits, ::std::string (b, e));
    if (! res) version.reset (html_0);
    return res; }

bool operator == (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.major () != rhs.major ()) return false;
    return (lhs.minor () == rhs.minor ()); }

bool operator != (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs == rhs); }

bool operator < (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.major () > rhs.major ()) return false;
    if (lhs.major () < rhs.major ()) return true;
    return (lhs.minor () < rhs.minor ()); }

bool operator > (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs) && ! (lhs == rhs); }

bool operator <= (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs > rhs); }

bool operator >= (const html_version& lhs, const html_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs); }

bool does_apply (const html_version& v, const html_version& from, const html_version& to)
{   if (! from.unknown () && (v < from)) return false;
    if (! to.unknown () && (v > to)) return false;
    switch (v.major ())
    {   case 0 :    break;
        case 1 :    if (v.minor () == 0) return ! from.not10 ();
                    assert (v.minor () == 1);
                    return ! from.notplus ();
        case 2 :    if (from.not2 ()) return false;
                    if (from.not2l1 () && (v.level () == 1)) return false;
                    if (! context.rfc_1867 () && from.rfc_1867 ()) return false;
                    if (! context.rfc_1942 () && from.rfc_1942 ()) return false;
                    if (! context.rfc_1980 () && from.rfc_1980 ()) return false;
                    if (! context.rfc_2070 () && from.rfc_2070 ()) return false;
                    break;
        case 3 :    if (v.minor () == 2) return ! from.not32 ();
                    assert (v.minor () == 0);
                    return ! from.not30 ();
        case 4 :    //if (extension_conflict (v, from) != emi_good) return false;
                    switch (v.minor ())
                    {   case 0 :
                        case 1 : return ! from.not4 ();
                        case 2 :
                        case 3 : return ! from.notx1 ();
                        case 4 : return ! from.notx2 (); }
                    assert (false);
                    break;
        default :   if (v.major () == 0) break;
                    if (from.xhtml () && from.notx5 ()) return false;
                    switch (w3_minor_5 (v))
                    {   case 0 : return ! from.not50 ();
                        case 1 : return ! from.not51 ();
                        case 2 : return ! from.not52 ();
                        case 3 : return ! from.not53 ();
                        case 4 : return ! from.not54 (); }
                    assert (false);
                    break; }
    return true; }

bool may_apply (const html_version& v, const html_version& from, const html_version& to)
{   return (v.unknown () || does_apply (v, from, to)); }

int w3_minor_5 (const html_version& v)
{   if (v.major () < 5) return v.minor ();
    if (v.major () < MAJOR_5_0) return 0;
    if ((v.major () == MAJOR_5_0) && (v.minor () <= MINOR_5_0)) return 0;
    if (v.major () < MAJOR_5_1) return 1;
    if ((v.major () == MAJOR_5_1) && (v.minor () <= MINOR_5_1)) return 1;
    if (v.major () < MAJOR_5_2) return 2;
    if ((v.major () == MAJOR_5_2) && (v.minor () <= MINOR_5_2)) return 2;
    if (v.major () < MAJOR_5_3) return 3;
    if ((v.major () == MAJOR_5_3) && (v.minor () <= MINOR_5_3)) return 3;
    return 4; }
