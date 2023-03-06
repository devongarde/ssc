/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "element/element.h"
#include "webpage/page.h"

element::element (const ::std::string& name, element_node& en, element* parent, page* p)
    :   node_ (en), a_ (*this), examined_ (false), page_ (p), parent_ (parent), name_ (name), uid_ (0)
{   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
    uid_ = page_ -> euid (); }

void element::reconstruct (sstr_t* access)
{   if (reconstructed_) return;
    access_ = access;
    a_.reconstruct (node_);
    reconstructed_ = true; }

::std::string element::content () const
{   if (! node_.invalid ()) return text ();
    return ::std::string ("empty base"); }

void element::swap (element& e) noexcept
{   a_.swap (e.a_);
    mf_.swap (e.mf_);
    name_.swap (e.name_);
    ::std::swap (sibling_, e.sibling_);
    ::std::swap (child_, e.child_);
    radio_kids_.swap (e.radio_kids_);
    itemscope_.swap (e.itemscope_);
    results_.swap (e.results_);
    node_.swap (e.node_);
    // do not swap icarus_
    ::std::swap (page_, e.page_);
    ::std::swap (examined_, e.examined_);
    ::std::swap (parent_, e.parent_);
    ::std::swap (autofocus_, e.autofocus_);
    ::std::swap (reconstructed_, e.reconstructed_);
    ::std::swap (ancestral_elements_, e.ancestral_elements_);
    ::std::swap (sibling_elements_, e.sibling_elements_);
    ::std::swap (descendant_elements_, e.descendant_elements_);
    ::std::swap (ancestral_attributes_, e.ancestral_attributes_);
    ::std::swap (own_attributes_, e.own_attributes_);
    ::std::swap (descendant_attributes_, e.descendant_attributes_);
    ::std::swap (uid_, e.uid_);
    ::std::swap (closure_uid_, e.closure_uid_);
    ::std::swap (access_, e.access_);
    ::std::swap (vit_, e.vit_); }

void element::cleanup () noexcept
{   try
    {   if (child_ != nullptr)
        {   child_ -> cleanup ();
            delete child_;
            child_ = nullptr; }
        if (sibling_ != nullptr)
        {   sibling_ -> cleanup ();
            delete sibling_;
            sibling_ = nullptr; } }
    catch (...) { } }

ids_t& element::get_ids () noexcept
{   return page_ -> get_ids (); }

const ids_t& element::get_ids () const noexcept
{   return page_ -> get_ids (); }

ids_t& element::get_names () noexcept
{   return page_ -> get_names (); }

const ids_t& element::get_names () const noexcept
{   return page_ -> get_names (); }

int element::line () const noexcept
{   return node_.line (); }

element* element::make_child ()
 {  PRESUME (has_child (), __FILE__, __LINE__);
    if (child_ == nullptr)
        child_ = new element (name_, node_.child (), this, page_);
    return child_; }

element* element::make_next ()
 {  PRESUME (has_next (), __FILE__, __LINE__);
    if (sibling_ == nullptr)
        sibling_ = new element (name_, node_.next (), parent_, page_);
    return sibling_; }

bool element::make_sibling (element*& e)
{   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    if (! e -> has_next ()) return false;
    e = e -> make_next ();
    return true; }

element* element::get_ancestor (const e_element e) const
{   element* anc = parent_;
    while (anc != nullptr)
    {   VERIFY_NOT_NULL (anc, __FILE__, __LINE__);
        if (anc -> tag () == e) return anc;
        if (anc -> tag () == elem_template) break;
        anc = anc -> parent_; }
    return nullptr; }

bool element::has_this_child (const e_element e) const
{   if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (c -> tag () == e) return true; }
    return false; }

bool element::has_this_descendant (const e_element e) const
{   return (descendant_elements_.test (e)); }

void element::check_ancestors (const e_element self, const element_bitset& gf)
{   element_bitset tmp (ancestral_elements_);
    tmp &= gf;
    if (tmp.any ())
        pick (nit_bad_ancestor, es_error, ec_element, "No <", elem::name (self), "> can have an ancestral ", nameset (gf)); }

void element::check_descendants (const e_element self, const element_bitset& gf, const bool absent)
{   element_bitset tmp (descendant_elements_);
    tmp &= gf;
    if (absent && tmp.any ())
        pick (nit_bad_descendant, es_error, ec_element, "No <", elem::name (self), "> can have a descendant ", nameset (gf));
    else if (! absent && ! tmp.any ())
        pick (nit_insufficient_content, es_error, ec_element, "<", elem::name (self), "> requires content"); }

bool element::has_invalid_child (const element_bitset& gf)
{   if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (! c -> node ().is_closure ())
                if (! faux_bitset.test (c -> tag ()) && ! gf.test (c -> tag ())) return true; }
    return false; }

void element::check_required_type ()
{   if (tag () != elem_img) return;
    if (a_.known (a_type)) return;
    if (node_.version () < html_3_0) return;
    pick (nit_element_no_type, es_comment, ec_element, elem::name (tag ()), " has no TYPE attribute here"); }

void element::no_anchor_daddy ()
{   if (node_.version ().is_5 ())
        if (ancestral_elements_.test (elem_a))
            pick (nit_interactive, ed_50, "4.5.1 The a element", es_warning, ec_element, "<A> cannot have an interactive descendant element."); }

bool element::only_one_of ()
{   if (page_ -> count (tag ()) == 1) return true;
    pick (nit_only_once, es_error, ec_element, "there should only be one <", node_.id ().name (), "> per page");
    return false; }

bool element::only_one_visible_of ()
{   if (page_ -> visible_count (tag ()) == 1) return true;
    pick (nit_only_once, es_error, ec_element, "there should only be one visible (not hidden) <", node_.id ().name (), "> per page");
    return false; }

bool element::check_math_children (const int expected, const bool or_more)
{   int n = 0;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (! c -> node_.is_closure ()) if (c -> node_.id ().is_math ()) ++n; }
    if ((n == expected) || (or_more && (n > expected))) return true;
    if (node_.version ().math_version () >= math_4_22) return true;
    if (or_more)
        pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires ", expected, " or more");
    else pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires ", expected);
    return false; }

void element::check_math_children (const int from, const int to)
{   PRESUME (to > from, __FILE__, __LINE__);
    int n = 0;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (! c -> node_.is_closure ()) if (c -> node_.id ().is_math ()) ++n; }
    if ((n < from) || (n > to))
        pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires between ", from, " and ", to); }

void element::check_mscarries_pos ()
{   bool last = false;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            last = (c -> tag () == elem_mscarries); }
    if (last)
        pick (nit_mscarries_last, ed_math_3, "3.6.5 Carries, Borrows, and Crossouts <mscarries>", es_error, ec_element, "<MSCARRIES> cannot be the last child of <", elem::name (tag ()), ">"); }

void element::do_shadow (::std::stringstream& ss, const html_version& v, bool& was_closure, bool& allspace, bool& was_nl)
{   PRESUME (examined_, __FILE__, __LINE__);
    switch (tag ())
    {   case elem_faux_asp : ss << "<%" << node_.raw () << "%>"; was_nl = false; break;
        case elem_faux_cdata : ss << "<![CDATA[" << node_.raw () << "]]>"; was_nl = false; break;
        case elem_faux_char : ss << '&' << node_.raw () << ';'; was_nl = false; break;
        case elem_faux_code : ss << "&#" << node_.raw () << ';'; was_nl = false; break;
        case elem_faux_comment : if (context.shadow_comment ()) { was_nl = false; ss << "<!--" << node_.raw () << "-->"; } break;
        case elem_faux_doctype : was_nl = false; ss << "<!DOCTYPE " << v.get_doctype () << ">"; break;
        case elem_faux_document :
            was_closure = allspace = false;
            if (! context.msg ().empty ()) ss << "<!-- " << context.msg () << " -->\n";
            if (context.info ()) ss <<  "<!-- generated by " FULLNAME " v" VERSION_STRING
#ifdef DEBUG
                                        "D"
#endif // DEBUG
                                        ", " WEBADDR ", " << ::boost::posix_time::second_clock::local_time () << " -->\n";
            break;
        case elem_faux_php : ss << "<$" << node_.raw () << "$>"; was_nl = false; break;
        case elem_faux_ssi : if (context.shadow_comment ()) { ss << "<!--" << node_.raw () << "-->"; was_nl = false; } break;
        case elem_faux_stylesheet : ss << "<?xml.stylesheet" << node_.raw () << "?>"; was_nl = false; break;
        case elem_faux_text : ss << node_.raw (); was_nl = false; break;
        case elem_faux_whitespace :
            if (context.shadow_space () || allspace) { ss << node_.raw (); was_nl = false; }
            else if (! was_nl && (was_closure || (node_.raw ().find_first_of (LINE_SEPARATORS) != ::std::string::npos)))
            {   ss << "\n"; was_nl = true; }
            else { was_nl = false; ss << " "; }
            was_closure = false; break;
        case elem_faux_xml : ss << "<?xml" << node_.raw () << "?>"; was_nl = false; break;
        case elem_css_all : ss << "*"; was_nl = false; break;
        case elem_css_cell : ss << "||"; was_nl = false; break;
        case elem_css_child : ss << ">"; was_nl = false; break;
        case elem_css_precede : ss << "~"; was_nl = false; break;
        case elem_css_precede_immediate : ss << "+"; was_nl = false; break;
        case elem_annotation :
        case elem_annotation_xml :
        case elem_comment :
        case elem_plaintext :
        case elem_pre :
        case elem_script :
        case elem_style :
        case elem_xmp : allspace = ! node_.is_closure ();
            FALLTHROUGH;
        default :
            ss << "<";
            was_closure = node_.is_closure ();
            if (was_closure) ss << "/";
            ss << node_.id ().name ();
            a_.shadow (ss, v, this);
            if (node_.id ().is_closed (v) && v.xhtml ()) ss << "/";
            ss << ">";
            was_nl = false;
            break; }
    for (element* p = child_; p != nullptr; p = p -> sibling_)
        p -> do_shadow (ss, v, was_closure, allspace, was_nl); }

void element::shadow (::std::stringstream& ss, const html_version& v)
{   bool was_closure = false;
    bool allspace = false;
    bool was_nl = true;
    do_shadow (ss, v, was_closure, allspace, was_nl); }

bool element::has_glyph (const ::std::string& s) const
{   return page_ -> get_glyphs ().has_id (s); }

void element::add_glyph (const ::std::string& s)
{   page_ -> get_glyphs ().insert_id (s, this); }

ns_id element::verify_namespace (::std::string& s, ::std::string n)
{   return examine_namespace (nits (), node ().version (), node_.namespaces (), s, n); }

void element::accumulate (stats_t* st) const
{   a_.accumulate (st, tag ());
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            c -> accumulate (st); } }
