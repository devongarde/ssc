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
#include "main/context.h"
#include "parser/parse_element.h"
#include "utility/quote.h"

element_node::element_node (nitpick& nits, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const e_element tag)
    : parent_ (parent), child_ (child), last_ (child), next_ (next), previous_ (previous), line_ (line), closure_ (closure), elem_ (tag), nits_ (nits)
{   if (parent_ != nullptr) version_ = parent_ -> version_; else version_ = context.html_ver (); }

element_node::element_node (nitpick& nits, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const elem& el)
    : parent_ (parent), child_ (child), last_ (child), next_ (next), previous_ (previous), line_ (line), closure_ (closure), elem_ (el), nits_ (nits)
{   if (parent_ != nullptr) version_ = parent_ -> version_; else version_ = context.html_ver (); }

element_node::element_node (nitpick& nits, const int line, const bool closure, element_node* parent, const e_element tag, const ::std::string str)
    : parent_ (parent), child_ (nullptr), last_ (nullptr), next_ (nullptr), previous_ (nullptr), line_ (line), closure_ (closure), elem_ (tag), text_ (str), nits_ (nits)
{   if (parent_ != nullptr) version_ = parent_ -> version_; else version_ = context.html_ver (); }

element_node::element_node (nitpick& nits, const int line, const bool closure, element_node* parent, const elem& el, const ::std::string str)
    : parent_ (parent), child_ (nullptr), last_ (nullptr), next_ (nullptr), previous_ (nullptr), line_ (line), closure_ (closure), elem_ (el), text_ (str), nits_ (nits)
{   if (parent_ != nullptr) version_ = parent_ -> version_; else version_ = context.html_ver (); }

element_node::~element_node ()
{
    // Necessary to appease the VC++ 19 optimiser, SFAICT
}

void element_node::reset ()
{   element_node en;
    swap (en); }

void element_node::reset (const element_node& en)
{   element_node tmp (en);
    swap (tmp); }

::std::string element_node::text () const
{   return (unify_whitespace (trim_the_lot_off (inner_text (elem_faux_text)))); }

void element_node::parse_attributes (const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   va_.parse (nits_, v, b, e, line_, elem_);
    if (v.mjr () < 4) return;
    if (parent_ != nullptr) version_ = parent_ -> version_;
    if (! va_.empty ())
    {   va_.manage_xmlns (nits (), version_);
        switch (id ())
        {   case elem_svg : version_.svg_version (va_.get_svg (v)); break;
            case elem_math : version_.math_version (va_.get_math (v)); break;
            default : break; } } }

void element_node::swap (element_node& en) NOEXCEPT
{   ::std::swap (parent_, en.parent_);
    ::std::swap (child_, en.child_);
    ::std::swap (last_, en.last_);
    ::std::swap (next_, en.next_);
    ::std::swap (previous_, en.previous_);
    ::std::swap (line_, en.line_);
    ::std::swap (closure_, en.closure_);
    version_.swap (en.version_);
    elem_.swap (en.elem_);
    va_.swap (en.va_);
    text_.swap (en.text_);
    nits_.swap (en.nits_); }

::std::string element_node::rpt (const int level) const
{   ::std::string res (::boost::lexical_cast < ::std::string > (level) + ": ");
    switch (elem_.get ())
    {   case elem_faux_cdata :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (s.empty ()) res += ln (line_) + "(cdata)\n";
                else res += ln (line_) + "(cata) " + quoted_limited_string (s, 30) + "\n"; }
            break;
        case elem_faux_char :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (s.empty ()) res += ln (line_) + "&...;\n";
                else res += ln (line_) + "&...; " + quoted_limited_string (s, 30) + "\n"; }
            break;
        case elem_faux_code :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (s.empty ()) res += ln (line_) + "&#...;\n";
                else res += ln (line_) + "&#...; " + quoted_limited_string (s, 30) + "\n"; }
            break;
        case elem_faux_text :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (s.empty ()) res += ln (line_) + "(text)\n";
                else res += ln (line_) + "(text) " + quoted_limited_string (s, 30) + "\n"; }
            break;
        case elem_faux_document :
            res += ln (line_) + "(document)\n"; break;
        case elem_faux_comment :
            res += ln (line_) + "(comment)\n"; break;
        case elem_faux_whitespace :
            res += ln (line_) + "(whitespace)\n"; break;
        case elem_faux_asp :
        case elem_faux_php :
        case elem_faux_ssi :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (! s.empty ()) res += ln (line_) + elem_.name () + quoted_limited_string (s, 30) + "\n"; }
            break;
        case elem_faux_doctype :
            res += ln (line_) + "<!DOCTYPE>\n"; break;
        case elem_faux_xml :
            res += ln (line_) + "<?xml...?>\n"; break;
        default :
            if (closure_) res += ln (line_) + "/" + elem_.name () + va_.rpt () + "\n";
            else res += ln (line_) + elem_.name () + va_.rpt () + "\n"; }
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
        res += kids -> rpt (level + 1);
    return res; }

::std::string element_node::inner_text (const ::std::size_t tag) const
{   if (elem_.get () == tag) return text_;
    if (elem_.get () == elem_faux_whitespace) return " "; // yaboo xml
    if (child_ == nullptr) return ::std::string ();
    ::std::string res;
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
        res += kids -> inner_text (tag);
    return res; }
