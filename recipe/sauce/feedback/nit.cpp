/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

nit::nit () : code_ (nit_free), severity_ (es_undefined), category_ (ec_undefined), doc_ (ed_mishmash), ref_ (nullptr)
{   if (context.nits ()) context.out ("adding empty nit\n"); }

nit::nit (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (doc), ref_ (ref), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding ref nit " << severity << ", " << msg << "\n";
        context.out (ss.str ()); } }

nit::nit (const e_nit code, const e_severity severity, const e_category category, const ::std::string& msg)
    : code_ (code), severity_ (severity), category_ (category), doc_ (ed_mishmash), msg_ (msg)
{   if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "adding nit " << severity << ", " << msg << "\n";
        context.out (ss.str ()); } }

void nit::swap (nit& n) NOEXCEPT
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

void nit::notify () const
{   context.mark (severity_);
    context.mark (category_);
    context.mark (doc_); }

::std::string nitcode (const e_nit code, const e_severity severity)
{   ::std::ostringstream res;
    unsigned m = 1;
    switch (severity)
    {   case es_undefined : m = 90000; res << "?"; break;
        case es_catastrophic : res << "F"; break;  // F failure
        case es_error : m = 10000; res << "E"; break;
        case es_warning : m = 20000; res << "W"; break;
        case es_info : m = 30000; res << "I"; break;
        case es_comment : m = 40000; res << "C"; break;
        case es_debug : m = 50000; res << "D"; break;
        case es_detail : m = 60000; res << ":"; break;
        case es_splurge : m = 70000; res << "."; break;
        default : m = 8000; res << " "; break; }
    res << ::std::setw (4) << (m + static_cast < unsigned > (code));
    return res.str (); }

bool ignore_this_slob_stuff (const e_nit code)
{   if (! context.slob ()) return false;
    switch (code)
    {   case nit_missing_close :
        case nit_inserted_missing_closure :
        case nit_inserted_missing_parent : return true;
        default : return false; } }

::std::string nit::review () const
{   ::std::ostringstream res;
    ::std::string info;
    if (! empty ())
        if (severity_ != es_silence)
            if (! ignore_this_slob_stuff (code ()))
            {   if (context.tell (static_cast < e_verbose > (static_cast < unsigned > (severity_))))
                {   if (code () != nit_context)
                        if (context.codes ()) res << nitcode (code_, severity_) << "  ";
                        else switch (severity_)
                        {   case es_catastrophic : res << " >>> "; break;
                            case es_error : res << " ==> "; break;
                            case es_warning : res << " --> "; break;
                            case es_info : res << " ..> "; break;
                            case es_comment : res << " . > "; break;
                            default : res << "     "; break; }
                    res << msg_;
                    if (doc_ != ed_mishmash)
                        if (ref_.empty ()) res << " [" << doc_ref (doc_) << "]";
                        else res << " [" << doc_title (doc_) << ", "<< ref_ << "]";
                    if (context.nids ())
                    {   const ::std::string& s = lookup_name (code_);
                        res << " (" << nitcode (code_, severity_);
                        if (! s.empty ()) res << ", " << s;
                        res << ")"; }
                    res << "\n"; } }
    return res.str (); }

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
        case ed_math_4 : return "MathML 4";
        case ed_mimetype : return "IANA media types";
        case ed_rdf : return "RDFa";
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
        case ed_ecma : return "ECMAScript, 22.2.1 Patterns";
        case ed_mozilla : return "mozilla.org (May 2020)";
        case ed_microdata : return "WhatWG Microdata";
        case ed_microformats : return MICROFORMATS_ORG " (May 2020)";
        case ed_ariaAug2020 : return "Aria (August 2020)";
        case ed_ariaApr2021 : return "Aria (April 2021)";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_css_transform : return "CSS Transforms";
        case ed_mql : return "Media Queries"; }
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
        case ed_50 : return "HTML 5.0 (W3), Oct 2014";
        case ed_51 : return "HTML 5.1 (W3), Nov 2016";
        case ed_52 : return "HTML 5.2 (W3), Dec 2017";
        case ed_53 : return "HTML 5.3 (W3), Oct 2018, draft";
        case ed_jan05 : return "WhatWG Web Applications 1.0 Working Draft, 31 January 2005";
        case ed_jan06 : return "WhatWG Web Applications 1.0 Working Draft, 1 January 2006";
        case ed_jan07 : return "WhatWG Web Applications 1.0 Working Draft, 4 January 2007";
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
        case ed_rdf : return "RDFa Core 1.1 - Third Edition";
        case ed_csp : return "Content Security Policy Level 3, Oct 2018, draft";
        case ed_math_1 : return "MathML 1.01";
        case ed_math_2 : return "MathML 2.0 - Second Edition";
        case ed_math_3 : return "MathML 3.0 - Second Edition";
        case ed_math_4 : return "MathML 4.0, draft, January 2019";
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
        case ed_ariaApr2021 : return "W3C ARIA in HTML draft, April 2021";
        case ed_apache : return "Apache 2.4 mod_include, 2020";
        case ed_css_transform : return "CSS Transforms Module Level 1, February 2019";
        case ed_so_11 : return SCHEMA_ORG " 11.0";
        case ed_mozilla : return "moz://a, May 2020";
        case ed_microdata : return "HTML 5 living standard, WhatWG, July 2020";
        case ed_microformats : return "Microformats (" MICROFORMATS_ORG "), May 2020"; }
    return "unknown reference"; }
