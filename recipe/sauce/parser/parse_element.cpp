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
#include "parser/text.h"
#include "utility/quote.h"

void element_node::init ()
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    PRESUME (va_.box () == nullptr, __FILE__, __LINE__);
    if (parent_ == nullptr) version_ = context.html_ver ();
    else version_ = parent_ -> version_;
    manage_reversioner (); }

element_node::element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const e_element tag, const bool presumed)
    : parent_ (parent), child_ (child), last_ (child), next_ (next), previous_ (previous), box_ (box), line_ (line), closure_ (closure), presumed_ (presumed), elem_ (tag), nits_ (nits)
{   init (); }

element_node::element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const elem& el, const bool presumed)
    : parent_ (parent), child_ (child), last_ (child), next_ (next), previous_ (previous), box_ (box), line_ (line), closure_ (closure), presumed_ (presumed), elem_ (el), nits_ (nits)
{   init (); }

element_node::element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, const e_element tag, const bool presumed, const ::std::string str)
    : parent_ (parent), child_ (nullptr), last_ (nullptr), next_ (nullptr), previous_ (nullptr), box_ (box), line_ (line), closure_ (closure), presumed_ (presumed), elem_ (tag), text_ (str), nits_ (nits)
{   init (); }

element_node::element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, const elem& el, const bool presumed, const ::std::string str)
    : parent_ (parent), child_ (nullptr), last_ (nullptr), next_ (nullptr), previous_ (nullptr), box_ (box), line_ (line), closure_ (closure), presumed_ (presumed), elem_ (el), text_ (str), nits_ (nits)
{   init (); }

element_node::element_node (elements_node* box)
    : box_ (box)
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__); }

element_node::~element_node ()
{
    // When omitted, some versions of VC++ 19 seem to have a spot of bother
}

void element_node::reset ()
{   element_node en (box_);
    swap (en); }

void element_node::reset (const element_node& en)
{   element_node tmp (en);
    swap (tmp);
    va_.box (this); }

void element_node::swap (element_node& en) NOEXCEPT
{   ::std::swap (parent_, en.parent_);
    ::std::swap (child_, en.child_);
    ::std::swap (last_, en.last_);
    ::std::swap (next_, en.next_);
    ::std::swap (previous_, en.previous_);
    ::std::swap (line_, en.line_);
    ::std::swap (closure_, en.closure_);
    ::std::swap (checked_sanitised_, en.checked_sanitised_);
    ::std::swap (presumed_, en.presumed_);
    ::std::swap (box_, en.box_);
    prefixes_.swap (en.prefixes_);
    namespaces_.swap (en.namespaces_);
    version_.swap (en.version_);
    elem_.swap (en.elem_);
    va_.swap (en.va_);
    text_.swap (en.text_);
    sanitised_.swap (en.sanitised_);
    nits_.swap (en.nits_); }

::std::string element_node::text ()
{   if (! checked_sanitised_)
    {   sanitised_ = unify_whitespace (trim_the_lot_off (inner_text ()));
        checked_sanitised_ = true; }
    return sanitised_; }

void element_node::manage_reversioner ()
{   switch (tag ())
    {   case elem_svg :
            {   e_svg_version e = va_.get_svg (version_);
                if (e != sv_none) version_.svg_version (e); }
            break;
        case elem_math :
            {   e_math_version m = va_.get_math (version_);
                if (m != math_none) version_.math_version (m); }
        default : break; } }

void element_node::parse_attributes (const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   PRESUME (va_.box () == nullptr, __FILE__, __LINE__);
    va_.box (this);
//    if (parent_ != nullptr) nss_ = initialise_namespace_stack (version_, parent_ -> nss_);
    va_.parse (nits_, version_, b, e, line_, elem_, true);
    if (version_.mjr () < 4) return;
    if (! va_.empty ())
    {   va_.manage_xmlns (nits (), version_);
        switch (id ())
        {   case elem_svg : version_.svg_version (va_.get_svg (version_)); break;
            case elem_math : version_.math_version (va_.get_math (version_)); break;
            default : break; } } }

::std::string element_node::rpt (const int level)
{   ::std::string res (::boost::lexical_cast < ::std::string > (level) + ": ");
    if (presumed_) res += "*";
    switch (elem_.get ())
    {   case elem_faux_cdata :
            {   ::std::string s (trim_the_lot_off (text ()));
                if (s.empty ()) res += ln (line_) + "(cdata)\n";
                else res += ln (line_) + "(cdata) " + quoted_limited_string (s, 30) + "\n"; }
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
    if (namespaces_.get () != nullptr) res += namespaces_ -> rpt (level);
    if (prefixes_.get () != nullptr) res += prefixes_ -> rpt (level);
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
    {   VERIFY_NOT_NULL (kids, __FILE__, __LINE__);
        res += kids -> rpt (level + 1); }
    return res; }

::std::string element_node::inner_text () const
{   ::std::string tmp;
    switch (elem_.get ())
    {   case elem_faux_cdata :
        case elem_faux_code :
            if (is_whitespace (text_)) return " ";
            return text_;
        case elem_faux_char :
            if (is_whitespace (text_)) return " ";
            tmp = interpret_character_code (version_, text_);
            if (! tmp.empty ()) return tmp;
            return text_;
        case elem_faux_text :
            return text_;
        case elem_faux_whitespace :
            return " "; // yaboo xml
        default : break; }
    if (child_ == nullptr) return ::std::string ();
    ::std::string res;
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
    {   VERIFY_NOT_NULL (kids, __FILE__, __LINE__);
        res += kids -> inner_text (); }
    return res; }

//::std::string element_node::rpt () const
//{   ::std::ostringstream ss;
//    ss << elem_.name () << " " << version_.report () << ":\n";
//    ss << "    " << line_ << " " << closure_ << " " << closed_ << " " << checked_sanitised_ << " " << presumed_ << " ";
//    if (box_ == nullptr) ss << "-"; else ss << "boxed"; ss << "\n";
//    ss << "    " << quote (text_) << " " << quote (raw_) << " " << quote (sanitised_) << "\n";
//    if (prefixes_.get () != nullptr) ss << prefixes_ -> rpt ();
//    ss << va_.rpt ();
//    for (element_node* child = child_; child != nullptr; child = child -> next_)
//        ss << child -> rpt ();
//    return ss.str (); }
