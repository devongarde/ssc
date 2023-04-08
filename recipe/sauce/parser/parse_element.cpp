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

void element_node::reset ()
{   element_node en (box_);
    swap (en); }

void element_node::reset (const element_node& en)
{   element_node tmp (en);
    swap (tmp);
    va_.box (this); }

void element_node::swap (element_node& en) noexcept
{   ::std::swap (parent_, en.parent_);
    ::std::swap (child_, en.child_);
    ::std::swap (last_, en.last_);
    ::std::swap (next_, en.next_);
    ::std::swap (previous_, en.previous_);
    ::std::swap (line_, en.line_);
    ::std::swap (closure_, en.closure_);
    ::std::swap (closed_, en.closed_);
    ::std::swap (checked_sanitised_, en.checked_sanitised_);
    ::std::swap (presumed_, en.presumed_);
    ::std::swap (box_, en.box_);
    prefixes_.swap (en.prefixes_);
    rdf_schemas_.swap (en.rdf_schemas_);
    rdf_.swap (en.rdf_);
    rdfa_.swap (en.rdfa_);
    version_.swap (en.version_);
    namespaces_.swap (en.namespaces_);
    elem_.swap (en.elem_);
    va_.swap (en.va_);
    text_.swap (en.text_);
    raw_.swap (en.raw_);
    sanitised_.swap (en.sanitised_);
    nits_.swap (en.nits_); }

::std::string element_node::text (const bool simplify)
{   if (! checked_sanitised_)
    {   if (simplify) sanitised_ = unify_whitespace (inner_text (simplify));
        else sanitised_ = unify_whitespace (trim_the_lot_off (inner_text ()));
        checked_sanitised_ = true; }
    return sanitised_; }

void element_node::manage_reversioner ()
{   switch (tag ())
    {   case elem_svg :
            {   const e_svg_version e = va_.get_svg (version_);
                if (e != sv_none) version_.svg_version (e); }
            break;
        case elem_math :
            {   const e_math_version m = va_.get_math (version_);
                if (m != math_none) version_.math_version (m); }
            break;
        default : break; } }

void element_node::parse_attributes (const html_version& , const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   PRESUME (va_.box () == nullptr, __FILE__, __LINE__);
    va_.box (this);
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
        case elem_css_all :
            res += ln (line_) + "{*}\n"; break;
        case elem_css_cell :
            res += ln (line_) + "{||}\n"; break;
        case elem_css_child :
            res += ln (line_) + "{>}\n"; break;
        case elem_css_precede :
            res += ln (line_) + "{~}\n"; break;
        case elem_css_precede_immediate :
            res += ln (line_) + "{+}\n"; break;
        case elem_css_scope_descendent :
            res += ln (line_) + "{>>}\n"; break;
        case elem_css_scope_root :
            res += ln (line_) + "{&}\n"; break;
        default :
            if (closure_) res += ln (line_) + "/" + elem_.name () + va_.rpt () + "\n";
            else res += ln (line_) + elem_.name () + va_.rpt () + "\n"; }
    if (namespaces_.get () != nullptr) res += namespaces_ -> rpt (level);
    if (prefixes_.get () != nullptr) res += prefixes_ -> rpt (level);
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
    {   VERIFY_NOT_NULL (kids, __FILE__, __LINE__);
        res += kids -> rpt (level + 1); }
    return res; }

::std::string element_node::word (bool simplify) const
{   ::std::string tmp;
    switch (elem_.get ())
    {   case elem_faux_cdata :
        case elem_faux_code :
            if (text_.empty ()) return "";
            if (is_whitespace (text_)) return " ";
            if (text_.at (0) == 'x') tmp = interpret_character_hex (text_);
            else tmp = interpret_character_number (text_);
            if (! tmp.empty ()) return tmp;
            return text_;
        case elem_faux_char :
            if (text_.empty ()) return "";
            if (is_whitespace (text_)) return " ";
            tmp = interpret_character_code (version_, text_, simplify);
            if (! tmp.empty ()) return tmp;
            return text_;
        case elem_faux_text :
            return text_;
        case elem_faux_whitespace :
            return " ";
        default : break; }
    return ""; }

::std::string element_node::word (nitpick& nits, const html_version& v) const
{   ::std::string tmp;
    switch (elem_.get ())
    {   case elem_faux_cdata :
        case elem_faux_code :
            if (text_.empty ()) return "";
            if (is_whitespace (text_)) return " ";
            if (text_.at (0) == 'x') tmp = interpret_character_hex (nits, text_);
            else tmp = interpret_character_number (nits, text_);
            if (! tmp.empty ()) return tmp;
            return text_;
        case elem_faux_char :
            if (text_.empty ()) return "";
            if (is_whitespace (text_)) return " ";
            tmp = interpret_character_code (nits, v, text_, true);
            if (! tmp.empty ()) return tmp;
            return text_;
        case elem_faux_text :
            return text_;
        case elem_faux_whitespace :
            return " ";
        default : break; }
    return ""; }

::std::string element_node::inner_text (const bool simplify) const
{   ::std::string res (word (simplify));
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
    {   VERIFY_NOT_NULL (kids, __FILE__, __LINE__);
        res += kids -> inner_text (); }
    return res; }

::std::string element_node::inner_text (nitpick& nits, const html_version& v) const
{   ::std::string res (word (nits, v));
    for (element_node* kids = child_; kids != nullptr; kids = kids -> next_)
    {   VERIFY_NOT_NULL (kids, __FILE__, __LINE__);
        res += kids -> inner_text (nits, v); }
    return res; }
