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

#include "standard.h"
#include "parse_bra_ket.h"
#include "common.h"
#include "elem.h"

::std::string faux_rpt (const bk_status st, const int l, const ::std::string::const_iterator& s, const ::std::string::const_iterator& e)
{   switch (st)
    {   case bk_asp : return (ln (l) + "ASP...");
        case bk_cdata : return (ln (l) + "<![CDATA[...");
        case bk_code : return ln (l) + ::std::string ("&") + ::std::string (s, e) + ::std::string (";");
        case bk_doctype : return (ln (l) + "<!DOCTYPE>");
        case bk_node : break;
        case bk_num : return ln (l) + ::std::string ("&#") + ::std::string (s, e) + ::std::string (";");
        case bk_php : return (ln (l) + "PHP...");
        case bk_ssi : return (ln (l) + "SSI...");
        case bk_stylesheet : return (ln (l) + "<?xml.stylesheet ... ?>");
        case bk_text : return (ln (l) + "text...");
        case bk_xml : return (ln (l) + "XML..."); }
    return ::std::string (); }

::std::string bra_element_ket::rpt () const
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

::std::string bra_element_ket::text () const
{   ::std::string res (faux_rpt (status_, line_, start_, end_));
    if (! res.empty ())
    {   res = "<";
        if (closure_) res += "/";
        res += ::std::string (start_, eofe_);
        if (closed_) res += "/";
        res += ">"; }
    return res; }

void bra_element_ket::test_specific ()
{   if (! tested_)
    {   if ((status_ == bk_node) && (start_ != eofe_))
            switch (*start_)
            {   case 'C' :
                case 'c' :  comment_ = compare_no_case (::std::string (start_, eofe_), elem::name (elem_comment));
                            break;
                case 'P' :
                case 'p' :  plaintext_ = compare_no_case (::std::string (start_, eofe_), elem::name (elem_plaintext));
                            break;
                case 'X' :
                case 'x' :  xmp_ = compare_no_case (::std::string (start_, eofe_), elem::name (elem_xmp));
                            break;
                default  :  break; }
        tested_ = true; } }

bool bra_element_ket::is_xmp ()
{   test_specific ();
    return xmp_; }

bool bra_element_ket::is_comment ()
{   test_specific ();
    return comment_; }

bool bra_element_ket::is_plaintext ()
{   test_specific ();
    return plaintext_; }

bool bra_element_ket::is_whitespace () const
{   if (status_ != bk_text) return false;
    for (::std::string::const_iterator i = start_; i < end_; ++i)
        if (*i > ' ') return false;
    return true; }

