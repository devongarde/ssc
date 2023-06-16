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
#include "feedback/nit.h"
#include "feedback/nitnames.h"
#include "main/context.h"
#include "type/type.h"
#include "feedback/nitout.h"
#include "coop/lox.h"

nit::nit () : code_ (nit_free), severity_ (es_illegal), category_ (ec_undefined), doc_ (ed_mishmash)
{   if (context.nits ()) outstr.out ("adding empty nit\n"); }

nit::nit (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (doc), ref_ (ref), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding ref nit " << severity << ", " << msg << "\n";
        outstr.out (ss.str ()); } }

nit::nit (const e_nit code, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (ed_mishmash), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding nit " << severity << ", " << msg << "\n";
        outstr.out (ss.str ()); } }

void nit::swap (nit& n) noexcept
{   ::std::swap (code_, n.code_);
    ::std::swap (severity_, n.severity_);
    ::std::swap (category_, n.category_);
    ::std::swap (doc_, n.doc_);
    ::std::swap (ref_, n.ref_);
    msg_.swap (n.msg_); }

void nit::reset ()
{   nit n;
    swap (n); }

void nit::reset (const nit& n)
{   nit tmp (n);
    swap (tmp); }

::std::string nitcode (const e_nit code, const e_severity severity)
{   ::std::ostringstream res;
    unsigned m = 1;
    switch (severity)
    {   case es_illegal :
        case es_undefined : m = 110000; res << "?"; break;
        case es_catastrophic : res << "F"; break;  // F failure
        case es_abhorrent : res << "A"; break;
        case es_error : m = 10000; res << "E"; break;
        case es_warning : m = 20000; res << "W"; break;
        case es_info : m = 30000; res << "I"; break;
        case es_comment : m = 40000; res << "C"; break;
        case es_debug : m = 50000; res << "D"; break;
        case es_variable : m = 60000; res << "V"; break;
        case es_structure : m = 70000; res << "S"; break;
        case es_detail : m = 80000; res << ":"; break;
        case es_splurge : m = 90000; res << "."; break;
        default : m = 10000; res << " "; break; }
    res << ::std::setw (4) << (m + static_cast < unsigned > (code));
    return res.str (); }

bool ignore_this_slob_stuff (const e_nit code) noexcept
{   if (! context.slob ()) return false;
    switch (code)
    {   case nit_inserted_missing_closure :
        case nit_inserted_missing_parent :
        case nit_missing_close :
        case nit_missing_open : return true;
        default : return false; } }

::std::string nit_ref (const ::std::string& doc, const ::std::string& ref)
{   ::std::string res;
    res = "[";
    res += doc;
    if (! ref.empty ())
    {   res += ",";
        res += quote (ref); }
    res += "]";
    return res; }

::std::string nit::level_symbol () const
{   switch (severity_)
    {   case es_catastrophic : return " >>> ";
        case es_abhorrent : return " **> ";
        case es_error : return " ==> ";
        case es_warning : return " --> ";
        case es_info : return " ..> ";
        case es_comment : return " . > ";
        default : return "     "; } }

::std::string nit::review (const e_nit_section& entry, const mmac_t& mac, const mmac_t& outer) const
{   mmac_t values;
    values.emplace (nm_nit_code, nitcode (code_, severity_));
    values.emplace (nm_nit_explanation, msg_);
    values.emplace (nm_level_name, type_master < t_severity > :: name (severity_));
    values.emplace (nm_level_symbol, level_symbol ());
    values.emplace (nm_nit_id, lookup_name (code_));
    if (! ref_.empty ())
    {   values.emplace (nm_nit_ref, ref_);
        values.emplace (nm_nit_doc, doc_title (doc_));
        values.emplace (nm_nit_doc_long, doc_ref (doc_)); }
    else
    {   values.emplace (nm_nit_ref, "");
        values.emplace (nm_nit_doc, "");
        values.emplace (nm_nit_doc_long, ""); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    return macro -> apply (entry, mac, outer, values); }

::std::string doc_title (const e_doc doc)
{   switch (doc)
    {   case ed_mishmash : return "(no reference)";
        case ed_imaginary : return "(invalid)";
        case ed_dict: return "Dictionary";
        case ed_tags : return "HTML Tags";
        case ed_plus : return "HTML Plus";
        case ed_1 : return "HTML 1.0";
        case ed_2 : return "HTML 2.0";
        case ed_3 : return "HTML 3.0";
        case ed_32 : return "HTML 3.2";
        case ed_4 : return "HTML 4.0";
        case ed_41 : return "HTML 4.01";
        case ed_x1 : return "XHTML 1.0";
        case ed_x11 : return "XHTML 1.1";
        case ed_x2 : return "XHTML 2.0";
        case ed_50 : return "HTML 5.0";
        case ed_51 : return "HTML 5.1";
        case ed_52 : return "HTML 5.2";
        case ed_53 : return "HTML 5.3";
        case ed_csp : return "Content Security Policy";
        case ed_math_1 : return "MathML 1.01";
        case ed_math_2 : return "MathML 2 2nd Ed.";
        case ed_math_3 : return "MathML 3 2nd Ed.";
        case ed_math_4_20 : return "MathML 4 (Jan 2019 draft)";
        case ed_math_4_22 : return "MathML 4 (Aug 2022 draft)";
        case ed_mimetype : return "IANA media types";
        case ed_rdfa : return "RDFa";
        case ed_rdfa_c : return "RDFa Context";
        case ed_iso_8859_1 : return "ISO 8859-1";
        case ed_rfc_1867 : return "RFC 1867";
        case ed_rfc_1980 : return "RGC 1980";
        case ed_rfc_3986 : return "RFC 3986";
        case ed_rfc_3966 : return "RFC 3966";
        case ed_rfc_6265 : return "RFC 6265";
        case ed_rfc_7231 : return "RFC 7231";
        case ed_rfc_7234 : return "RFC 7234";
        case ed_rfc_8288 : return "RFC 8288";
        case ed_svg_1_0 : return "SVG 1.0";
        case ed_svg_1_1 : return "SVG 1.1";
        case ed_svg_1_2_tiny : return "SVG 1.2 Tiny";
        case ed_svg_1_2_full : return "SVG 1.2 Full";
        case ed_svg_2_0 : return "SVG 2.0";
        case ed_svg_2_anim : return "SVG 2.0 animation";
        case ed_w3 : return "World Wide Web Consortium";
        case ed_apache : return "Apache";
        case ed_jan05 : return "WebApps draft (Jan 2005)";
        case ed_jan06 : return "WebApps draft (Jan 2006)";
        case ed_jan07 : return "WebApps draft (Jan 2007)";
        case ed_jan08 : return "HTML 5 living standard (Jan 2008)";
        case ed_jan10 : return "HTML 5 living standard (Jan 2010)";
        case ed_jul10 : return "HTML 5 living standard (July 2010)";
        case ed_jan12 : return "HTML 5 living standard (Jan 2012)";
        case ed_jan13 : return "HTML 5 living standard (Jan 2013)";
        case ed_jan14 : return "HTML 5 living standard (Jan 2014)";
        case ed_jul17 : return "HTML 5 living standard (July 2017)";
        case ed_may20 : return "HTML 5 living standard (May 2020)";
        case ed_jul20 : return "HTML 5 living standard (July 2020)";
        case ed_jan21 : return "HTML 5 living standard (Jan 2021)";
        case ed_apr21 : return "HTML 5 living standard (April 2021)";
        case ed_jul21 : return "HTML 5 living standard (July 2021)";
        case ed_apr22 : return "HTML 5 living standard (April 2022)";
        case ed_oct22 : return "HTML 5 living standard (October 2022)";
        case ed_ecma : return "ECMAScript, 22.2.1 Patterns";
        case ed_mozilla : return "mozilla.org (May 2020)";
        case ed_microdata : return "WhatWG Microdata";
        case ed_microformats : return MICROFORMATS_ORG " (May 2020)";
        case ed_ariaAug2020 : return "Aria (August 2020)";
        case ed_ariaApr2021 : return "Aria (April 2021)";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_css_transform : return "CSS Transforms";
        case ed_mql : return "Media Queries";
        case ed_css_1 : return "CSS Level 1";
        case ed_css_20 : return "CSS Level 2";
        case ed_css_21 : return "CSS Level 2.1";
        case ed_css_22 : return "CSS Level 2.2";
        case ed_css_animation_3 : return "CSS Animation 3"; 
        case ed_css_cascade_4 : return "CSS Cascade 4"; 
        case ed_css_cascade_5 : return "CSS Cascade 5"; 
        case ed_css_cascade_6 : return "CSS Cascade 6";
        case ed_css_colour_3 : return "CSS Colour 3";
        case ed_css_colour_4 : return "CSS Colour 4";
        case ed_css_colour_5 : return "CSS Colour 5";
        case ed_css_custom : return "CSS Custom Properties";
        case ed_css_media_4 : return "CSS Media 4"; 
        case ed_css_namespaces_3 : return "CSS Namespaces 3";
        case ed_css_selectors_3 : return "CSS Selectors 3";
        case ed_css_selectors_4 : return "CSS Selectors 4";
        case ed_css_syntax : return "CSS Syntax Module";
        case ed_css_ui_3 : return "CSS UI 3";
        case ed_css_ui_4 : return "CSS UI 4";
        case ed_css_value_3 : return "CSS Value 3";
        case ed_css_value_4 : return "CSS Value 4";
        case ed_json : return "JSON";
        case ed_jsonld_1_0 : return "JSON-LD 1.0";
        case ed_jsonld_1_1 : return "JSON-LD 1.1"; }
    return "Unknown reference"; }

::std::string doc_ref (const e_doc doc)
{   switch (doc)
    {   case ed_mishmash : return "(no reference)";
        case ed_imaginary : return "(invalid reference)";
        case ed_dict : return "A Dictionary of the English Language, Apr 1755";
        case ed_tags : return "HTML Tags, 1991, informal";
        case ed_plus : return "HTML Plus, Nov 1993, draft";
        case ed_1 : return "HTML 1.0, Jun 1993, draft";
        case ed_2 : return "HTML 2.0, Nov 1995, RFC 1866";
        case ed_3 : return "HTML 3.0, Mar 1995, draft";
        case ed_32 : return "HTML 3.2, Jan 1997";
        case ed_4 : return "HTML 4.0, Apr 1998";
        case ed_41 : return "HTML 4.01, Dec 1999";
        case ed_x1 : return "XHTML 1.0, Aug 2002";
        case ed_x11 : return "XHTML 1.1, Nov 2010";
        case ed_x2 : return "XHTML 2.0, Dec 2010";
        case ed_50 : return "HTML 5.0, W3, Oct 2014";
        case ed_51 : return "HTML 5.1, W3, Nov 2016";
        case ed_52 : return "HTML 5.2, W3, Dec 2017";
        case ed_53 : return "HTML 5.3, W3, Oct 2018, draft";
        case ed_jan05 : return "WhatWG Web Applications 1.0 Draft, 31 January 2005";
        case ed_jan06 : return "WhatWG Web Applications 1.0 Draft, 1 January 2006";
        case ed_jan07 : return "WhatWG Web Applications 1.0 Draft, 4 January 2007";
        case ed_jan08 : return "HTML 5 living standard, WhatWG, January 2008";
        case ed_jan10 : return "HTML 5 living standard, WhatWG, January 2010";
        case ed_jul10 : return "HTML 5 living standard, WhatWG, July 2010";
        case ed_jan12 : return "HTML 5 living standard, WhatWG, January 2012";
        case ed_jan13 : return "HTML 5 living standard, WhatWG, January 2013";
        case ed_jan14 : return "HTML 5 living standard, WhatWG, January 2014";
        case ed_jul17 : return "HTML 5 living standard, WhatWG, July 2017";
        case ed_may20 : return "HTML 5 living standard, WhatWG, May 2020";
        case ed_jul20 : return "HTML 5 living standard, WhatWG, July 2020";
        case ed_jan21 : return "HTML 5 living standard, WhatWG, January 2021";
        case ed_apr21 : return "HTML 5 living standard, WhatWG, April 2021";
        case ed_jul21 : return "HTML 5 living standard, WhatWG, July 2021";
        case ed_apr22 : return "HTML 5 living standard, WhatWG, April 2022";
        case ed_oct22 : return "HTML 5 living standard, WhatWG, October 2022";
        case ed_rdfa : return "RDFa Core 1.1 Third Edition";
        case ed_rdfa_c : return "RDFa Core Initial Context, May 2020";
        case ed_csp : return "Content Security Policy Level 3 Draft, Oct 2018";
        case ed_math_1 : return "MathML 1.01";
        case ed_math_2 : return "MathML 2.0 Second Edition";
        case ed_math_3 : return "MathML 3.0 Second Edition";
        case ed_math_4_20 : return "MathML 4.0, draft, January 2019";
        case ed_math_4_22 : return "MathML 4.0, draft, August 2022";
        case ed_iso_8859_1 : return "ISO/IEC 8859-1:1998";
        case ed_ecma : return "ECMAScript 2022 Language Specification, 22.2.1 Patterns, March 2021";
        case ed_mimetype : return "IANA Media Types, February 2019";
        case ed_rfc_1867 : return "RFC 1867, Form-based File Upload in HTML";
        case ed_rfc_1980 : return "RFC 1980, Client-Side Image Maps";
        case ed_rfc_3986 : return "RFC 3986, Uniform Resource Identifier (URI): Generic Syntax";
        case ed_rfc_3966 : return "RFC 3966, The tel URI for Telephone Numbers";
        case ed_rfc_6265 : return "RFC 6265, HTTP State Management Mechanism";
        case ed_rfc_7231 : return "RFC 7231, HTTP/1.1 Semantics and Content";
        case ed_rfc_7234 : return "RFC 7234, Hypertext Transfer Protocol (HTTP/1.1): Caching"; // plus https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control
        case ed_rfc_8288 : return "RFC 8288, Web Linking";
        case ed_svg_1_0 : return "Scalable Vector Graphics (SVG) Specification 1.0";
        case ed_svg_1_1 : return "Scalable Vector Graphics (SVG) 1.1, Second Edition";
        case ed_svg_1_2_tiny : return "Scalable Vector Graphics (SVG) Tiny 1.2 Specification";
        case ed_svg_1_2_full : return "Scalable Vector Graphics (SVG) Full 1.2, draft, May 2004";
        case ed_svg_2_0 : return "Scalable Vector Graphics (SVG) 2 W3C Candidate Recommendation";
        case ed_svg_2_anim : return "SVG Animations Level 2, April 2021 draft";
        case ed_w3 : return "The World Wide Web Consortium";
        case ed_mql : return "Media Queries, W3C recommendation, June 2012";
        case ed_ariaAug2020 : return "WhatWG Aria requirements, draft, August 2020";
        case ed_ariaApr2021 : return "W3C ARIA in HTML, draft, April 2021";
        case ed_apache : return "Apache 2.4 mod_include, 2020";
        case ed_css_transform : return "CSS Transforms Module Level 1, February 2019";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_mozilla : return "moz://a, May 2020";
        case ed_microdata : return "HTML 5 living standard, WhatWG, July 2020";
        case ed_microformats : return "Microformats (" MICROFORMATS_ORG "), May 2020";
        case ed_css_1 : return "CSS Level 1 (April 2008)";
        case ed_css_20 : return "CSS Level 2 (May 1998)";
        case ed_css_21 : return "CSS Level 2.1 (April 2016)";
        case ed_css_22 : return "CSS Level 2.2 (February 2022 draft)";
        case ed_css_animation_3 : return "CSS Animation Level '1', March 2023"; 
        case ed_css_cascade_4 : return "CSS Cascade Level 4, January 2022"; 
        case ed_css_cascade_5 : return "CSS Cascade Level 5, January 2022"; 
        case ed_css_cascade_6 : return "CSS Cascade Level 6, March 2023"; 
        case ed_css_colour_3 : return "CSS Colour 3, January 2022";
        case ed_css_colour_4 : return "CSS Colour 4, November 2022";
        case ed_css_colour_5 : return "CSS Colour 5 (June 2022 draft)";
        case ed_css_custom : return "CSS Custom Properties for Cascading Variables Level 1 (June 2022)"; 
        case ed_css_media_4 : return "CSS Media Queries Level 4, July 2020"; 
        case ed_css_namespaces_3 : return "CSS Namespaces 3, September 2011";
        case ed_css_selectors_3 : return "CSS Selectors Level 3, November 2018";
        case ed_css_selectors_4 : return "CSS Selectors Level 4 (November 2022 draft)";
        case ed_css_syntax : return "CSS Syntax Module Level 3 (December 2021 draft)";
        case ed_css_ui_3 : return "CSS Basic User Interface Level 3, June 2018";
        case ed_css_ui_4 : return "CSS Basic User Interface Level 4 (March 2021 draft)";
        case ed_css_value_3 : return "CSS Values and Units 3, December 2022";
        case ed_css_value_4 : return "CSS Values and Units 4 (October 2022 draft)";
        case ed_json : return "RFC 4627, JSON";
        case ed_jsonld_1_0 : return "JSON-LD 1.0, January 2014";
        case ed_jsonld_1_1 : return "JSON-LD 1.1, July 2020"; }
    return "unknown reference"; }
