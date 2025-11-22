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
#include "feedback/nit.h"
#include "feedback/nitnames.h"
#include "main/context.h"
#include "type/type.h"
#include "feedback/nitout.h"
#include "coop/lox.h"

nit::nit () : code_ (nit_free), severity_ (es_illegal), category_ (ec_undefined), doc_ (ed_mishmash)
{   if (context.nits ()) context.os () -> out ("adding empty nit\n"); }

nit::nit (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (doc), ref_ (ref), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding ref nit " << severity << ", " << msg << "\n";
        context.os () -> out (ss.str ()); } }

nit::nit (const e_nit code, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (ed_mishmash), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding nit " << severity << ", " << msg << "\n";
        context.os () -> out (ss.str ()); } }

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

bool ignore_this_slovenly_stuff (const e_nit code) noexcept
{   switch (code)
    {   case nit_dl_ancestor :
        case nit_inserted_missing_closure :
        case nit_inserted_missing_parent :
        case nit_missing_close :
        case nit_missing_open :
        case nit_only_once :
        case nit_use_quote_code :
        case nit_use_double_quote_code :
        case nit_wrong_parent :
            return (context.analysis () == anal_original) && context.sloven ();
        default :
            return false; } }

::std::string nit_ref (const ::std::string& doc, const ::std::string& ref)
{   ::std::string res;
    res = "[";
    res += doc;
    if (! ref.empty ())
    {   res += PLAINSEP;
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
    {   ::std::string link;
        values.emplace (nm_nit_ref, ref_);
        values.emplace (nm_nit_doc, doc_title (doc_));
        values.emplace (nm_nit_doc_long, doc_ref (doc_));
        switch (doc_link (doc_, link))
        {   case nlt_html : values.emplace (nm_nit_doc_link, link); values.emplace (nm_nit_doc_pdf, ""); values.emplace (nm_nit_doc_text, ""); values.emplace (nm_nit_doc_zip, ""); break;   
            case nlt_pdf : values.emplace (nm_nit_doc_pdf, link); values.emplace (nm_nit_doc_link, ""); values.emplace (nm_nit_doc_text, ""); values.emplace (nm_nit_doc_zip, ""); break; 
            case nlt_txt : values.emplace (nm_nit_doc_text, link); values.emplace (nm_nit_doc_link, ""); values.emplace (nm_nit_doc_pdf, ""); values.emplace (nm_nit_doc_zip, ""); break; 
            case nlt_zip : values.emplace (nm_nit_doc_zip, link); values.emplace (nm_nit_doc_link, ""); values.emplace (nm_nit_doc_pdf, ""); values.emplace (nm_nit_doc_text, ""); break; 
            default : break; } }
    else
    {   values.emplace (nm_nit_ref, "");
        values.emplace (nm_nit_doc, "");
        values.emplace (nm_nit_doc_long, "");
        values.emplace (nm_nit_doc_link, "");
        values.emplace (nm_nit_doc_pdf, "");
        values.emplace (nm_nit_doc_text, "");
        values.emplace (nm_nit_doc_zip, ""); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    return macro -> apply (entry, mac, outer, values); }

::std::string doc_title (const e_doc doc)
{   switch (doc)
    {   case ed_mishmash : return "[no reference]";
        case ed_imaginary : return "[invalid]";
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
        case ed_math_4 : return "MathML 4, Nov 24";
        case ed_math_core : return "Math Core, Jun 25";
        case ed_mimetype : return "IANA media types";
        case ed_prism_1 : return "PRISM spec 1.0";
        case ed_rdfa : return "RDFa";
        case ed_rdfa_c : return "RDFa Context";
        case ed_iso_8859_1 : return "ISO 8859-1";
        case ed_rfc_1867 : return "RFC 1867";
        case ed_rfc_1980 : return "RFC 1980";
        case ed_rfc_2616 : return "RFC 2616";
        case ed_rfc_3986 : return "RFC 3986";
        case ed_rfc_3966 : return "RFC 3966";
        case ed_rfc_6265 : return "RFC 6265";
        case ed_rfc_6570 : return "RFC 6570";
        case ed_rfc_7231 : return "RFC 7231";
        case ed_rfc_7234 : return "RFC 7234";
        case ed_rfc_8288 : return "RFC 8288";
        case ed_svg_1_0 : return "SVG 1.0";
        case ed_svg_1_1 : return "SVG 1.1";
        case ed_svg_1_2_tiny : return "SVG 1.2 Tiny";
        case ed_svg_1_2_full : return "SVG 1.2 Full";
        case ed_svg_2_0 : return "SVG 2.0";
        case ed_svg_2_anim : return "SVG 2.0 Animation";
        case ed_w3 : return "World Wide Web Consortium";
        case ed_apache : return "Apache";
        case ed_jan05 : return "WebApps Jan 05";
        case ed_jan06 : return "WebApps Jan 06";
        case ed_jan07 : return "WebApps Jan 07";
        case ed_jan08 : return "WhatWG HTML 5, Jan 08";
        case ed_jan10 : return "WhatWG HTML 5, Jan 10";
        case ed_jul10 : return "WhatWG HTML 5, Jul 10";
        case ed_jan12 : return "WhatWG HTML 5, Jan 12";
        case ed_jan13 : return "WhatWG HTML 5, Jan 13";
        case ed_jan14 : return "WhatWG HTML 5, Jan 14";
        case ed_jul17 : return "WhatWG HTML 5, Jul 17";
        case ed_may20 : return "WhatWG HTML 5, May 20";
        case ed_jul20 : return "WhatWG HTML 5, Jul 20";
        case ed_jan21 : return "HTML 5, Jan 21";
        case ed_apr21 : return "HTML 5, Apr 21";
        case ed_jul21 : return "HTML 5, Jul 21";
        case ed_apr22 : return "HTML 5, Apr 22";
        case ed_oct22 : return "HTML 5, Oct 22";
        case ed_jun23 : return "HTML 5, Jun 23";
        case ed_jul25 : return "HTML 5, Jul 25";
        case ed_aug25 : return "HTML 5, Aug 25";
        case ed_wx : return "wxWidgets HTML";
        case ed_owasp : return "OWASP";
        case ed_ecma : return "ECMAScript, 22.2.1 Patterns";
        case ed_keyboard : return "KeyboardEvent key Values";
        case ed_mozilla : return "mozilla.org May 20";
        case ed_microdata : return "WhatWG Microdata";
        case ed_microformats : return MICROFORMATS_ORG " May 20";
        case ed_aria_1_0 : return "Aria 1.0";
        case ed_aria_1_1 : return "Aria 1.1";
        case ed_aria_1_2 : return "Aria 1.2";
        case ed_aria_1_3 : return "Aria 1.3 (draft)";
        case ed_aria_dp_1_0 : return "Aria Digital Publishing 1.0";
        case ed_aria_dp_1_1 : return "Aria Digital Publishing 1.1 (draft)";
        case ed_aria_graphics : return "Aria Graphics";
        case ed_aria_html : return "Aria in HTML";
        case ed_aria_mdn : return "WAI-ARIA roles (MDN)";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_mql : return "Media Queries";
        case ed_css_1 : return "CSS Level 1";
        case ed_css_20 : return "CSS Level 2";
        case ed_css_21 : return "CSS Level 2.1";
        case ed_css_22 : return "CSS Level 2.2";
        case ed_css_animation_3 : return "CSS Animation 3"; 
        case ed_css_cascade_4 : return "CSS Cascade 4"; 
        case ed_css_cascade_5 : return "CSS Cascade 5"; 
        case ed_css_cascade_6 : return "CSS Cascade 6";
        case ed_cr_4 : return "CSS Conditional Rule 4"; 
        case ed_cr_5 : return "CSS Conditional Rule 5"; 
        case ed_css_colour_3 : return "CSS Colour 3";
        case ed_css_colour_4 : return "CSS Colour 4";
        case ed_css_colour_5 : return "CSS Colour 5";
        case ed_css_content : return "CSS Generated Content";
        case ed_css_cs_3 : return "CSS Counter Styles 3";
        case ed_css_custom : return "CSS Custom Properties";
        case ed_css_ease : return "CSS Easing Functions";
        case ed_css_filter_3 : return "CSS Filter Effects 3";
        case ed_css_font_4 : return "CSS Fonts 4";
        case ed_css_image_3 : return "CSS Images 3";
        case ed_css_media_3 : return "CSS Media 3"; 
        case ed_css_media_4 : return "CSS Media 4"; 
        case ed_css_namespaces_3 : return "CSS Namespaces 3";
        case ed_css_nesting : return "CSS Nesting";
        case ed_css_selectors_3 : return "CSS Selectors 3";
        case ed_css_selectors_4 : return "CSS Selectors 4";
        case ed_css_syntax : return "CSS Syntax Module";
        case ed_css_table : return "CSS Table Module Level 3";
        case ed_css_transform : return "CSS Transforms Module 1";
        case ed_css_ui_3 : return "CSS UI 3";
        case ed_css_ui_4 : return "CSS UI 4";
        case ed_css_value_3 : return "CSS Value 3";
        case ed_css_value_4 : return "CSS Value 4";
        case ed_json : return "JSON";
        case ed_jsonld_1_0 : return "JSON-LD 1.0";
        case ed_jsonld_1_1 : return "JSON-LD 1.1";
        case ed_doctype : return "Doctype Declarations";
        case ed_clacks : return "X-Clacks-Overhead";
        case ed_vtt : return "Video Text Tracks";
        case ed_rel : return "official rel registry";
        case ed_con : return "ads.txt, iab.tech lab";
        case ed_robotic : return "RFC 9309";
        case ed_security : return "RFC 9116";
        case ed_rsl : return "really simple licensing";
        case ed_rss : return "really simple syndication";
        case ed_ccrss : return "Creative Commons RSS";
        case ed_mrss : return "Media RSS";
        case ed_atom : return "atom syndication"; }
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
        case ed_jan05 : return "WhatWG Web Applications 1.0 Draft, 31 January 05";
        case ed_jan06 : return "WhatWG Web Applications 1.0 Draft, 1 January 06";
        case ed_jan07 : return "WhatWG Web Applications 1.0 Draft, 4 January 07";
        case ed_jan08 : return "WhatWG HTML 5, WhatWG, January 2008";
        case ed_jan10 : return "WhatWG HTML 5, WhatWG, January 2010";
        case ed_jul10 : return "WhatWG HTML 5, WhatWG, July 2010";
        case ed_jan12 : return "WhatWG HTML 5, WhatWG, January 2012";
        case ed_jan13 : return "WhatWG HTML 5, WhatWG, January 2013";
        case ed_jan14 : return "WhatWG HTML 5, WhatWG, January 2014";
        case ed_jul17 : return "WhatWG HTML 5, WhatWG, July 2017";
        case ed_may20 : return "WhatWG HTML 5, WhatWG, May 2020";
        case ed_jul20 : return "WhatWG HTML 5, WhatWG, July 2020";
        case ed_jan21 : return "HTML 5, WhatWG, January 2021";
        case ed_apr21 : return "HTML 5, WhatWG, April 2021";
        case ed_jul21 : return "HTML 5, WhatWG, July 2021";
        case ed_apr22 : return "HTML 5, WhatWG, April 2022";
        case ed_oct22 : return "HTML 5, WhatWG, October 2022";
        case ed_jun23 : return "HTML 5, WhatWG, Juny 2023";
        case ed_jul25 : return "HTML 5, WhatWG, July 2025";
        case ed_aug25 : return "HTML 5, WhatWG, August 2025";
        case ed_wx : return "wxWidgets HTML, list of stable HTML tags, November 2024";
        case ed_owasp : return "Open Web Application Security Project, January 2025"; 
        case ed_prism_1 : return "Publishing Requirements for Industry Standard Metadata, Version 1.0";
        case ed_rdfa : return "RDFa Core 1.1 Third Edition";
        case ed_rdfa_c : return "RDFa Core Initial Context, May 2020";
        case ed_csp : return "Content Security Policy Level 3 Draft, Oct 2018";
        case ed_math_1 : return "MathML 1.01";
        case ed_math_2 : return "MathML 2.0 Second Edition";
        case ed_math_3 : return "MathML 3.0 Second Edition";
        case ed_math_4 : return "MathML 4.0, draft, November 2024";
        case ed_math_core : return "MathML Core, recommended snapshot, June 2025";
        case ed_iso_8859_1 : return "ISO/IEC 8859-1:1998";
        case ed_ecma : return "ECMAScript 2022 Language Specification, 22.2.1 Patterns, March 2021";
        case ed_keyboard : return "UI Events KeyboardEvent key Values, W3, November 2024";
        case ed_mimetype : return "IANA Media Types, February 2019";
        case ed_rfc_1867 : return "RFC 1867, Form-based File Upload in HTML";
        case ed_rfc_1980 : return "RFC 1980, Client-Side Image Maps";
        case ed_rfc_2616 : return "RFC 2616, Hypertext Transfer Protocol -- HTTP/1.1";
        case ed_rfc_3986 : return "RFC 3986, Uniform Resource Identifier (URI): Generic Syntax";
        case ed_rfc_3966 : return "RFC 3966, The tel URI for Telephone Numbers";
        case ed_rfc_6265 : return "RFC 6265, HTTP State Management Mechanism";
        case ed_rfc_6570 : return "RFC 6570, URI Template";
        case ed_rfc_7231 : return "RFC 7231, HTTP/1.1 Semantics and Content";
        case ed_rfc_7234 : return "RFC 7234, Hypertext Transfer Protocol (HTTP/1.1): Caching"; // plus https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control
        case ed_rfc_8288 : return "RFC 8288, Web Linking";
        case ed_svg_1_0 : return "Scalable Vector Graphics (SVG) Specification 1.0";
        case ed_svg_1_1 : return "Scalable Vector Graphics (SVG) 1.1, Second Edition";
        case ed_svg_1_2_tiny : return "Scalable Vector Graphics (SVG) Tiny 1.2 Specification";
        case ed_svg_1_2_full : return "Scalable Vector Graphics (SVG) Full 1.2, draft, May 2004";
        case ed_svg_2_0 : return "Scalable Vector Graphics (SVG) 2 W3C Candidate Recommendation";
        case ed_svg_2_anim : return "SVG Animations Level 2, November 2024 draft";
        case ed_w3 : return "The World Wide Web Consortium";
        case ed_mql : return "Media Queries, W3C recommendation, June 2012";
        case ed_aria_1_0 : return "Accessible Rich Internet Applications (WAI-ARIA) 1.0, March 2014";
        case ed_aria_1_1 : return "Accessible Rich Internet Applications (WAI-ARIA) 1.1, December 2017";
        case ed_aria_1_2 : return "Accessible Rich Internet Applications (WAI-ARIA) 1.2, June 2023";
        case ed_aria_1_3 : return "Accessible Rich Internet Applications (WAI-ARIA) 1.3 draft, February 2025";
        case ed_aria_dp_1_0 : return "Digital Publishing WAI-ARIA Module 1.0, December 2017";
        case ed_aria_dp_1_1 : return "Digital Publishing WAI-ARIA Module 1.1 (draft), February 2025";
        case ed_aria_graphics : return "WAI-ARIA Graphics Module, October 2018";
        case ed_aria_html : return "ARIA in HTML, February 2025";
        case ed_aria_mdn : return "WAI-ARIA roles (developer.mozilla.org, June 2025)";
        case ed_apache : return "Apache 2.4 mod_include, 2020";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_mozilla : return "moz://a, May 2020";
        case ed_microdata : return "WhatWG HTML 5, WhatWG, July 2020";
        case ed_microformats : return "Microformats (" MICROFORMATS_ORG "), May 2020";
        case ed_css_1 : return "CSS Level 1 (April 2008)";
        case ed_css_20 : return "CSS Level 2 (May 1998)";
        case ed_css_21 : return "CSS Level 2.1 (April 2016)";
        case ed_css_22 : return "CSS Level 2.2 (February 2022 draft)";
        case ed_css_animation_3 : return "CSS Animation Level '1', March 2023"; 
        case ed_css_cascade_4 : return "CSS Cascade Level 4, January 2022"; 
        case ed_css_cascade_5 : return "CSS Cascade Level 5, January 2022"; 
        case ed_css_cascade_6 : return "CSS Cascade Level 6, March 2023"; 
        case ed_cr_4 : return "CSS Conditional Rule Level 4, February 2022"; 
        case ed_cr_5 : return "CSS Conditional Rule Level 5, December 2021"; 
        case ed_css_colour_3 : return "CSS Colour 3, January 2022";
        case ed_css_colour_4 : return "CSS Colour 4, November 2022";
        case ed_css_colour_5 : return "CSS Colour 5 (June 2022 draft)";
        case ed_css_content : return "CSS Generated Content (August 2019 draft)";
        case ed_css_cs_3 : return "CSS Counter Stylse 3, July 2021";
        case ed_css_custom : return "CSS Custom Properties for Cascading Variables Level 1, June 2022";
        case ed_css_ease : return "CSS Easing Functions Level 1, February 2023";
        case ed_css_filter_3 : return "CSS Filter Effects Level 3, December 2018";
        case ed_css_font_4 : return "CSS Fonts Level 4, December 2021";
        case ed_css_image_3 : return "CSS Images Level 3, December 2020"; 
        case ed_css_media_3 : return "CSS Media Queries Level 3, April 2022"; 
        case ed_css_media_4 : return "CSS Media Queries Level 4, July 2020"; 
        case ed_css_namespaces_3 : return "CSS Namespaces 3, September 2011";
        case ed_css_nesting : return "CSS Nesting, February 2023";
        case ed_css_selectors_3 : return "CSS Selectors Level 3, November 2018";
        case ed_css_selectors_4 : return "CSS Selectors Level 4, November 2022 draft";
        case ed_css_syntax : return "CSS Syntax Module Level 3, December 2021 draft";
        case ed_css_table : return "CSS Table Module Level 3, July 2019 draft";
        case ed_css_transform : return "CSS Transforms Module 1, February 2019";
        case ed_css_ui_3 : return "CSS Basic User Interface Level 3, June 2018";
        case ed_css_ui_4 : return "CSS Basic User Interface Level 4, March 2021 draft";
        case ed_css_value_3 : return "CSS Values and Units 3, December 2022";
        case ed_css_value_4 : return "CSS Values and Units 4, October 2022 draft";
        case ed_json : return "RFC 4627, JSON";
        case ed_jsonld_1_0 : return "JSON-LD 1.0, January 2014";
        case ed_jsonld_1_1 : return "JSON-LD 1.1, July 2020";
        case ed_doctype : return "Doctype Declarations, July 2016, https://www.w3.org/QA/2002/04/valid-dtd-list.html";
        case ed_clacks : return "X-Clacks-Overhead / xclacksoverhead.org";
        case ed_vtt : return "WebVTT: The Web Video Text Tracks Format, April 2019, https://www.w3.org/TR/webvtt1/";
        case ed_rel : return "official rel registry: existing rel values, https://microformats.org/";
        case ed_con : return "iab.tech lab, ads.txt, August 2022";
        case ed_robotic : return "RFC 9309, Robots Exclusion Protocol, September 2022";
        case ed_security : return "RFC 9116, Security Vulnerability Disclosure, April 2022";
        case ed_rsl : return "Really Simple Licensing, September 2025 draft";
        case ed_rss : return "Really Simple Syndication 2.0.11, March 2009";
        case ed_ccrss : return "Creative Commons Namespace for RSS, June 2023";
        case ed_mrss : return "Media RSS Specification 1.5.1, December 2009";
        case ed_atom : return "RFC 4287, Atom Syndication Format, December 2005"; }
    return "unknown reference"; }

e_nit_link_type doc_link (const e_doc doc, ::std::string& link)
{   
#define SPEX WEBADDR "spex/"
#define HTMLSPEX SPEX "html/"
#define ARIASPEX SPEX "aria/"
#define CSSSPEX SPEX "css/"
#define JSON SPEX "json/"
#define LIVING SPEX "whatwg/"
#define MATHSPEX SPEX "mathml/"
#define ONTSPEX SPEX "ontology/"
#define RFC SPEX "rfc/"
#define RDFSPEX SPEX "rdf/"
#define SVGSPEX SPEX "svg/"
#define XHTMLSPEX SPEX "xhtml/"
    link.clear ();
    switch (doc)
    {   case ed_1 : link = HTMLSPEX "html1/html10.txt"; return nlt_txt;
        case ed_2 : link = HTMLSPEX "html2/rfc1866.txt"; return nlt_txt;
        case ed_3 : link = HTMLSPEX "html3/html30.txt"; return nlt_txt;
        case ed_32 : link = HTMLSPEX "html3/html32.pdf"; return nlt_pdf;
        case ed_4 : link = HTMLSPEX "html4/html400.pdf"; return nlt_pdf;
        case ed_41 : link = HTMLSPEX "html4/html401.pdf"; return nlt_pdf;
        case ed_x1 : link = XHTMLSPEX "xhtml1.pdf"; return nlt_pdf;
        case ed_x11 : link = XHTMLSPEX "xhtml11basic.pdf"; return nlt_pdf;
        case ed_x2 : link = XHTMLSPEX "xhtml2.pdf"; return nlt_pdf;
        case ed_50 : link = HTMLSPEX "html5/html5.0.pdf"; return nlt_pdf;
        case ed_51 : link = HTMLSPEX "html5/html5.1.pdf"; return nlt_pdf;
        case ed_52 : link = HTMLSPEX "html5/html5.2.pdf"; return nlt_pdf;
        case ed_53 : link = HTMLSPEX "html5/html5.3.pdf"; return nlt_pdf;
        case ed_jan05 : link = LIVING "webapps-whatwg-2005-01.pdf"; return nlt_pdf;
        case ed_jan06 : link = LIVING "webapps-whatwg-2006-01.pdf"; return nlt_pdf;
        case ed_jan07 : link = LIVING "webapps-whatwg-2007-01.pdf"; return nlt_pdf;
        case ed_jan08 : link = LIVING "html-whatwg-2008-01.pdf"; return nlt_pdf;
        case ed_jan10 : link = LIVING "html-whatwg-2010-01.pdf"; return nlt_pdf;
        case ed_jul10 : link = LIVING "html-whatwg-2010-07.pdf"; return nlt_pdf;
        case ed_jan12 : link = LIVING "html-whatwg-2012-01.pdf"; return nlt_pdf;
        case ed_jan13 : link = LIVING "html-whatwg-2013-01.pdf"; return nlt_pdf;
        case ed_jan14 : link = LIVING "html-whatwg-2014-01.pdf"; return nlt_pdf;
        case ed_jul17 : link = LIVING "html-whatwg-2017-07.pdf"; return nlt_pdf;
        case ed_may20 : link = LIVING "html-whatwg-2020-05.pdf"; return nlt_pdf;
        case ed_jul20 : link = LIVING "html-whatwg-2020-07.pdf"; return nlt_pdf;
        case ed_jan21 : link = LIVING "html-whatwg-2021-01.pdf"; return nlt_pdf;
        case ed_apr21 : link = LIVING "html-whatwg-2021-04.pdf"; return nlt_pdf;
        case ed_jul21 : link = LIVING "html-whatwg-2021-07.pdf"; return nlt_pdf;
        case ed_apr22 : link = LIVING "html-whatwg-2022-04.pdf"; return nlt_pdf;
        case ed_jun23 : link = LIVING "html-whatwg-2023-06.pdf"; return nlt_pdf;
        case ed_jul25 : link = LIVING "html-whatwg-2025-07.pdf"; return nlt_pdf;
        case ed_aug25 : link = LIVING "html-whatwg-2025-08.pdf"; return nlt_pdf;
        case ed_apache : link = "https://httpd.apache.org/docs/current/mod/mod_include.html"; return nlt_html;
        case ed_aria_1_0 : link = ARIASPEX "aria-1.0.pdf"; return nlt_pdf;
        case ed_aria_1_1 : link = ARIASPEX "aria-1.1.pdf"; return nlt_pdf;
        case ed_aria_1_2 : link = ARIASPEX "aria-1.2.pdf"; return nlt_pdf;
        case ed_aria_1_3 : link = ARIASPEX "aria-1.3-jan24.pdf"; return nlt_pdf;
        case ed_aria_dp_1_0 : link = ARIASPEX "aria-dp-1.0.pdf"; return nlt_pdf;
        case ed_aria_dp_1_1 : link = ARIASPEX "aria-dp-1.1.pdf"; return nlt_pdf;
        case ed_aria_graphics : link = ARIASPEX "aria-graph-1.0.pdf"; return nlt_pdf;
        case ed_aria_html : link = ARIASPEX "aria-html-1.0.pdf"; return nlt_pdf;
        case ed_aria_mdn : link = "https://developer.mozilla.org/en-US/docs/Web/Accessibility/ARIA/Reference/Roles"; return nlt_html;
        case ed_atom : link = "https://validator.w3.org/feed/docs/rfc4287.html"; return nlt_html;
        case ed_ccrss : link = "https://www.rssboard.org/creative-commons"; return nlt_html;
        case ed_clacks : link = "https://xclacksoverhead.org/"; return nlt_html;
        case ed_con : link = "https://iabtechlab.com/wp-content/uploads/2022/04/Ads.txt-1.1.pdf"; return nlt_html;
        case ed_cr_4 : link = CSSSPEX "css-conditional-rules-4-feb22"; return nlt_pdf;  
        case ed_cr_5 : link = CSSSPEX "css-conditional-rules-5-dec21"; return nlt_pdf;  
        case ed_csp : link = "csp/csp3.pdf"; return nlt_pdf;
        case ed_css_1 : link = CSSSPEX "css-1-apr08.pdf"; return nlt_pdf;
        case ed_css_20 : link = CSSSPEX "css-2.0-may98.pdf"; return nlt_pdf;
        case ed_css_21 : link = CSSSPEX "css-2.1-apr16.pdf"; return nlt_pdf;
        case ed_css_22 : link = CSSSPEX "css-2.2-feb22.pdf"; return nlt_pdf;
        case ed_css_animation_3 : link = CSSSPEX "css-animations-1-mar23.pdf"; return nlt_pdf; 
        case ed_css_cascade_4 : link = CSSSPEX "css-cascading-inheritance-4-jan22.pdf"; return nlt_pdf; 
        case ed_css_cascade_5 : link = CSSSPEX "css-cascading-inheritance-5-jan22.pdf"; return nlt_pdf; 
        case ed_css_cascade_6 : link = CSSSPEX "css-cascading-inheritance-6-mar23.pdf"; return nlt_pdf; 
        case ed_css_colour_3 : link = CSSSPEX "css-colour-3-jan22.pdf"; return nlt_pdf;  
        case ed_css_colour_4 : link = CSSSPEX "css-colour-4-nov22.pdf"; return nlt_pdf;  
        case ed_css_colour_5 : link = CSSSPEX "css-colour-5-jun22.pdf"; return nlt_pdf;  
        case ed_css_content : link = CSSSPEX "css-generated-content-3-dec20.pdf"; return nlt_pdf;
        case ed_css_cs_3 : link = CSSSPEX "css-counter-styles-3-jul21.pdf"; return nlt_pdf;
        case ed_css_custom : link = CSSSPEX "css-cpcv-1-jun22.pdf"; return nlt_pdf;
        case ed_css_ease : link = CSSSPEX "css-easing-1-feb23.pdf"; return nlt_pdf;
        case ed_css_filter_3 : link = CSSSPEX "css-filter-effects-1-dec18.pdf"; return nlt_pdf;
        case ed_css_font_4 : link = CSSSPEX "css-fonts-4-dec21.pdf"; return nlt_pdf;
        case ed_css_image_3 : link = CSSSPEX "css-images-3.pdf"; return nlt_pdf;
        case ed_css_media_3 : link = CSSSPEX "css-media-queries-3-apr-22.pdf"; return nlt_pdf; 
        case ed_css_media_4 : link = CSSSPEX "css-media-queries-4.pdf"; return nlt_pdf; 
        case ed_css_namespaces_3 : link = CSSSPEX "css-namespaces-3.pdf"; return nlt_pdf; 
        case ed_css_nesting : link = CSSSPEX "css-nesting-aug21.pdf"; return nlt_pdf; 
        case ed_css_selectors_3 : link = CSSSPEX "css-selectors-3.pdf"; return nlt_pdf;
        case ed_css_selectors_4 : link = CSSSPEX "css-selectors-4-nov22.pdf"; return nlt_pdf;
        case ed_css_syntax : link = CSSSPEX "css-syntax-s-dec21.pdf"; return nlt_pdf;
        case ed_css_table : link = CSSSPEX "css-tables-3-sep20.pdf"; return nlt_pdf;
        case ed_css_transform : link = CSSSPEX "css-transforms-1.pdf"; return nlt_pdf;
        case ed_css_ui_3 : link = CSSSPEX "css-basic-ui-3.pdf"; return nlt_pdf;
        case ed_css_ui_4 : link = CSSSPEX "css-basic-ui-3.pdf"; return nlt_pdf;
        case ed_css_value_3 : link = CSSSPEX "css-values-units-3-dec22.pdf"; return nlt_pdf;
        case ed_css_value_4 : link = CSSSPEX "css-values-units-3-dec22.pdf"; return nlt_pdf;
        case ed_dict : link = SPEX "dict/johnsons_dictionary_1755.pdf"; return nlt_pdf;
        case ed_doctype : link = "https://www.w3.org/QA/2002/04/valid-dtd-list.html"; return nlt_html;
        case ed_ecma : link = SPEX "ecma/ecmascript-draft-2021-03.pdf"; return nlt_pdf;
        case ed_iso_8859_1 : link = SPEX "charset/charsets-jan21.pdf"; return nlt_pdf;
        case ed_json : link = JSON "rfc4627.txt"; return nlt_txt;
        case ed_jsonld_1_0 : link = JSON "JSON-LD-1.0.pdf"; return nlt_pdf;
        case ed_jsonld_1_1 : link = JSON "JSON-LD-1.1.pdf"; return nlt_pdf;
        case ed_keyboard : link = SPEX "uieke/uieke-nov24.pdf"; return nlt_pdf;
        case ed_math_1 : link = MATHSPEX "mathml-1.pdf"; return nlt_pdf;
        case ed_math_2 : link = MATHSPEX "mathml-2.pdf"; return nlt_pdf;
        case ed_math_3 : link = MATHSPEX "mathml-3.pdf"; return nlt_pdf;
        case ed_math_4 : link = MATHSPEX "mathml-4-nov24.pdf"; return nlt_pdf;
        case ed_math_core :link = MATHSPEX "mathml-core.pdf"; return nlt_pdf;
        case ed_microdata : link = LIVING "html-whatwg-2020-07.pdf"; return nlt_pdf;
        case ed_microformats : link = "https://microformats.org/"; return nlt_html;
        case ed_mimetype : link = "mime/media-types.txt"; return nlt_txt;
        case ed_mozilla : link = "https://developer.mozilla.org/en-US/docs/Web/HTML/Reference/Elements/meta"; return nlt_html;
        case ed_mql : link = "media/media-queries.pdf"; return nlt_pdf;
        case ed_mrss : link = "https://www.rssboard.org/media-rss"; return nlt_html;
        case ed_owasp : link = "https://cheatsheetseries.owasp.org/cheatsheets/HTML5_Security_Cheat_Sheet.html"; return nlt_html;
        case ed_plus : link = "https://www.w3.org/MarkUp/HTMLPlus/htmlplus_1.html"; return nlt_html;
        case ed_prism_1 : link = ONTSPEX "PRISM1.0.pdf"; return nlt_pdf;
        case ed_rdfa : link = RDFSPEX "rdfa-core.1.1.3.pdf"; return nlt_pdf;
        case ed_rdfa_c : link = RDFSPEX "RDFa Core Initial Context.pdf"; return nlt_pdf;
        case ed_rel : link = "https://microformats.org/wiki/existing-rel-values"; return nlt_html;
        case ed_rfc_1867 : link = RFC "rfc1867.html"; return nlt_html;
        case ed_rfc_1980 : link = RFC "rfc1980.html"; return nlt_html;
        case ed_rfc_2616 : link = RFC "rfc2616.pdf"; return nlt_pdf;
        case ed_rfc_3966 : link = RFC "rfc3966.pdf"; return nlt_pdf;
        case ed_rfc_3986 : link = RFC "rfc3986.txt"; return nlt_txt;
        case ed_rfc_6265 : link = RFC "rfc6265.pdf"; return nlt_pdf;
        case ed_rfc_6570 : link = RFC "rfc6570.txt"; return nlt_txt;
        case ed_rfc_7231 : link = RFC "rfc7231.pdf"; return nlt_pdf;
        case ed_rfc_7234 : link = RFC "rfc7234.pdf"; return nlt_pdf;
        case ed_rfc_8288 : link = RFC "rfc8288.pdf"; return nlt_pdf;
        case ed_robotic : link = "https://www.rfc-editor.org/rfc/rfc9309.html"; return nlt_html;
        case ed_rsl : link = NSLS_RSL; return nlt_html;
        case ed_rss : link = HTTPS RSS_BOARD "/rss-specification"; return nlt_html;
        case ed_security : link = "https://www.rfc-editor.org/rfc/rfc9116.html"; return nlt_html;
        case ed_so_11 : link = ONTSPEX "schemas-11.0.zip"; return nlt_zip;
        case ed_svg_1_0 : link = SVGSPEX "svg.pdf"; return nlt_pdf;
        case ed_svg_1_1 : link = SVGSPEX "svg11.pdf"; return nlt_pdf;
        case ed_svg_1_2_tiny : link = SVGSPEX "svg12Tiny.pdf"; return nlt_pdf;
        case ed_svg_1_2_full : link = SVGSPEX "svg12Full.pdf"; return nlt_pdf;
        case ed_svg_2_0 : link = SVGSPEX "svg-2-03-2023.pdf"; return nlt_pdf;
        case ed_svg_2_anim : link = SVGSPEX "svg-2-animations-04-2021.pdf"; return nlt_pdf;
        case ed_tags : link = HTMLSPEX "html1/html1tags.pdf"; return nlt_pdf;
        case ed_vtt : link = "vtt/webvtt-apr-2019.pdf"; return nlt_pdf;
        case ed_w3 : link = "https://w3.org/"; return nlt_html;
        case ed_wx : link = "https://docs.wxwidgets.org/stable/overview_html.html"; return nlt_html;
        default: break; }
    return nlt_none; }
