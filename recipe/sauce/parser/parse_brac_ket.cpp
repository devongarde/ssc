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
#include "parser/parse_brac_ket.h"
#include "utility/common.h"
#include "element/elem.h"

::std::string faux_rpt (const bk_status st, const int l, const ::std::string::const_iterator& s, const ::std::string::const_iterator& e)
{   switch (st)
    {   case bk_asp : return (ln (l) + "ASP...");
        case bk_cdata : return (ln (l) + "<![CDATA[...");
        case bk_code : return ln (l) + ::std::string ("&") + ::std::string (s, e) + ::std::string (";");
        case bk_comment : return (ln (l) + "comment...");
        case bk_doctype : return (ln (l) + "<!DOCTYPE>");
        case bk_node : break;
        case bk_num : return ln (l) + ::std::string ("&#") + ::std::string (s, e) + ::std::string (";");
        case bk_php : return (ln (l) + "PHP...");
        case bk_ssi : return (ln (l) + "SSI...");
        case bk_stylesheet : return (ln (l) + "<?xml.stylesheet ... ?>");
        case bk_text : return (ln (l) + "text...");
        case bk_xml : return (ln (l) + "XML..."); }
    return ::std::string (); }

void brac_element_ket::swap (brac_element_ket& bek)
{   arg_.swap (bek.arg_);
    nits_.swap (bek.nits_);
    ::std::swap (start_, bek.start_);
    ::std::swap (eofe_, bek.eofe_);
    ::std::swap (end_, bek.end_);
    ::std::swap (line_, bek.line_);
    ::std::swap (status_, bek.status_);
    ::std::swap (suspender_, bek.suspender_);
    ::std::swap (closure_, bek.closure_);
    ::std::swap (closed_, bek.closed_);
    ::std::swap (tested_, bek.tested_); }

::std::string brac_element_ket::rpt () const
{   ::std::string res (faux_rpt (status_, line_, start_, end_));
    if (! res.empty ())
    {   res = ln (line_);
        res += "<";
        if (closure_) res += "/";
        res += ::std::string (start_, eofe_);
        if (eofe_ != end_) res += ::std::string (" ") + ::std::string (eofe_, end_);
        if (closed_) res += "/";
        res += ">"; }
    return res; }

::std::string brac_element_ket::text () const
{   ::std::string res (faux_rpt (status_, line_, start_, end_));
    if (! res.empty ())
    {   res = "<";
        if (closure_) res += "/";
        res += ::std::string (start_, eofe_);
        if (closed_) res += "/";
        res += ">"; }
    return res; }

void brac_element_ket::test_specific ()
{   if (! tested_)
    {   if ((status_ == bk_node) && (start_ != eofe_) && ! closure_ && ! closed_)
        {   e_element el = elem::find (html_0, ::std::string (start_, eofe_));
            switch (el)
            {   case elem_comment :
                case elem_plaintext :
                case elem_xmp :
                    suspender_ = el;
                    break;
                case elem_annotation :
                case elem_annotation_xml :
                case elem_script :
                case elem_style :
                    if (! elem::ignored (el)) suspender_ = el;
                    break;
                default :
                    if (elem::ignored (el)) suspender_ = el;
                    break; } }
        tested_ = true; } }

e_element brac_element_ket::suspender ()
{   test_specific ();
    return suspender_; }

bool brac_element_ket::is_plaintext ()
{   test_specific ();
    return (suspender_ == elem_plaintext); }

bool brac_element_ket::is_xmp ()
{   test_specific ();
    return (suspender_ == elem_xmp); }

bool brac_element_ket::is_silent_content ()
{   test_specific ();
    return (suspender_ == elem_script) || (suspender_ == elem_style); }

bool brac_element_ket::is_whitespace () const noexcept
{   if (status_ != bk_text) return false;
    for (::std::string::const_iterator i = start_; i < end_; ++i)
        if (! ::std::iswspace (*i)) return false;
    return true; }
