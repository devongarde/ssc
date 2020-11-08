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
#include "feedback/nitpick.h"
#include "main/context.h"

const char* doc_ref (const e_doc doc)
{   switch (doc)
    {   case ed_mishmash : return "(no reference)";
        case ed_imaginary : return "invalid reference";
        case ed_dict : return "A Dictionary of the English Language, Apr 1755, https://archive.org/details/dictionaryofengl01johnuoft";
        case ed_tags : return "HTML Tags, 1991, informal, http://info.cern.ch/hypertext/WWW/MarkUp/Tags.html";
        case ed_plus : return "HTML Plus, Nov 1993, draft, https://www.w3.org/MarkUp/HTMLPlus/htmlplus_1.html";
        case ed_1 : return "HTML 1.0, Jun 1993, draft, https://web.archive.org/web/20170103041713/https://www.w3.org/MarkUp/draft-ietf-iiir-html-01.txt";
        case ed_2 : return "HTML 2.0, Nov 1995, RFC 1866, https://tools.ietf.org/html/rfc1866";
        case ed_3 : return "HTML 3.0, Mar 1995, draft, https://www.w3.org/MarkUp/html3/CoverPage.html";
        case ed_32 : return "HTML 3.2, Jan 1997, https://www.w3.org/TR/2018/SPSD-html32-20180315/";
        case ed_4 : return "HTML 4.0, Apr 1998, https://www.w3.org/TR/1998/REC-html40-19980424/";
        case ed_41 : return "HTML 4.01, Dec 1999, https://www.w3.org/TR/html401/";
        case ed_x1 : return "XHTML 1.0, Aug 2002, https://www.w3.org/TR/xhtml1/";
        case ed_x11 : return "XHTML 1.1, Nov 2010, https://www.w3.org/TR/xhtml-basic/";
        case ed_x2 : return "XHTML 2.0, Dec 2010, https://www.w3.org/TR/2010/NOTE-xhtml2-20101216/";
        case ed_50 : return "HTML 5.0, Oct 2014, https://www.w3.org/TR/2014/REC-html5-20141028/";
        case ed_51 : return "HTML 5.1, Nov 2016, https://www.w3.org/TR/2016/REC-html51-20161101/";
        case ed_52 : return "HTML 5.2, Dec 2017, https://www.w3.org/TR/2017/REC-html52-20171214/";
        case ed_53 : return "HTML 5.3, Oct 2018, draft, https://www.w3.org/TR/html53/";
        case ed_rdf : return "RDFa Core 1.1 - Third Edition";
        case ed_math_1 : return "MathML 1.01";
        case ed_math_2 : return "MathML 2.0 - Second Edition";
        case ed_math_3 : return "MathML 3.0 - Second Edition";
        case ed_math_4 : return "MathML 4.0, draft, January 2019";
        case ed_rfc_1867 : return "RFC 1867, Form-based File Upload in HTML";
        case ed_rfc_1980 : return "RFC 1980, Client-Side Image Maps";
        case ed_svg_1_0 : return "Scalable Vector Graphics (SVG) Specification 1.0";
        case ed_svg_1_1 : return "Scalable Vector Graphics (SVG) 1.1, Second Edition";
        case ed_svg_1_2_tiny : return "Scalable Vector Graphics (SVG) Tiny 1.2 Specification";
        case ed_svg_1_2_full : return "Scalable Vector Graphics (SVG) Full 1.2, draft, May 2004";
        case ed_svg_2_0 : return "Scalable Vector Graphics (SVG) 2 W3C Candidate Recommendation";
        case ed_w3 : return "The World Wide Web Consortium";
        case ed_mql : return "Media Queries, W3C recommendation, June 2012";
        case ed_ariaAug2020 : return "WhatWG Aria requirements, draft, August 2020";
        case ed_apache : return "Apache 2.4 mod_include, 2020, https://httpd.apache.org/docs/current/mod/mod_include.html";
        case ed_May2020 : return "HTML 5 living standard, WhatWG, May 2020";
        case ed_July2020 : return "HTML 5 living standard, WhatWG, July 2020";
        case ed_mozilla : return "moz://a, May 2020, https://developer.mozilla.org/en-US/docs/Web/HTML/Reference";
        case ed_microdata : return "HTML 5 living standard, WhatWG, July 2020";
        case ed_microformats : return "microformats, May 2020, http://microformats.org/"; }
    return "unknown reference"; }

void nitpick::swap (nitpick& np) NOEXCEPT
{   ::std::swap (line_, np.line_);
    nits_.swap (np.nits_);
    context_.swap (np.context_); }

void nitpick::reset ()
{   nitpick np;
    swap (np); }

void nitpick::reset (const nitpick& np)
{   nitpick tmp (np);
    swap (tmp); }

void nitpick::merge (const nitpick& np)
{   if (context_.empty ()) context_ = np.context_;
    for (auto n : np.nits_)
        nits_.emplace_back (n); }

void nitpick::merge (nitpick&& np)
{   if (context_.empty ()) context_.assign (np.context_);
   for (auto n : np.nits_)
        nits_.emplace_back (n); }

::std::string nitpick::review () const
{   ::std::string res;
    bool quote = false, dq = false, infoed = false, eol = false;;
    if (! empty ())
    {   for (auto n : nits_)
        {   switch (n.code ())
            {   case nit_context:
                    infoed = true;
                    break;
                case nit_use_double_quote_code :
                    if (dq) continue;
                    dq = true;
                    break;
                case nit_use_quote_code :
                    if (quote) continue;
                    quote = true;
                    break;
                case nit_newline_in_string :
                    if (eol) continue;
                    eol = true;
                    break;
                default : break; }
            n.notify ();
            if (context.test ())
            {   extern bool ignore_this_slob_stuff (const e_nit code);
                if ((n.code () != nit_context) && context.tell (static_cast < e_verbose > (static_cast < unsigned > (n.severity ()))) && ! ignore_this_slob_stuff (n.code ()))
                {   res += " ";
                    res += ::boost::lexical_cast < ::std::string > (n.code ()); } }
            else res += n.review (); }
        if (! res.empty ())
        {   ::std::string ln (::boost::lexical_cast < ::std::string > (line_));
            if (context.test ()) res = ln + " " + res + "\n";
            else if (! infoed)
            {   if (! context_.empty ()) prepend (res, "\n", context_);
                if (line_ > 0) prepend (res, ": ", ::std::string ("\n") + ln); } } }
    return res; }

nitpick nitpick::nick ()
{   nitpick tmp;
    swap (tmp);
    return tmp; }

void nitpick::pick (const nit& n)
{   nits_.emplace_back (n); }

void nitpick::pick (nit&& n)
{   nits_.emplace_back (n); }

void nitpick::set_context (const int line, const ::std::string& c)
{   ::std::string r (trim_the_lot_off (unify_whitespace (c)));
    if (context_.empty ())
    {   if (context.nits ()) context.out () << "set context to " << r << "\n";
        line_ = line;
        context_.assign (r); } }

void nitpick::set_context (const int line, const ::std::string::const_iterator b, ::std::string::const_iterator e)
{   set_context (line, ::std::string (b, e)); }
