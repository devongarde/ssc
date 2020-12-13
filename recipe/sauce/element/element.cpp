/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

element::element (const ::std::string& name, element_node& en, element* parent, ids_t& ids, sstr_t* access, page& p)
    :   node_ (en), a_ (en), examined_ (false), page_ (p), parent_ (parent), name_ (name), ids_ (ids), access_ (access), uid_ (page_.euid ()) { }

::std::string element::content () const
{   if (! node_.invalid ()) return text ();
    return ::std::string ("empty base"); }

void element::swap (element& e) NOEXCEPT
{   a_.swap (e.a_);
    mf_.swap (e.mf_);
    name_.swap (e.name_);
    sibling_.swap (e.sibling_);
    child_.swap (e.child_);
    radio_kids_.swap (e.radio_kids_);
    itemscope_.swap (e.itemscope_);
    ids_.swap (e.ids_);
    results_.swap (e.results_);
    // do not swap icarus_
    ::std::swap (node_, e.node_);
    ::std::swap (examined_, e.examined_);
    ::std::swap (page_, e.page_);
    ::std::swap (parent_, e.parent_);
    ::std::swap (autofocus_, e.autofocus_);
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

int element::line () const
{   return node_.line (); }

element_ptr element::child ()
 {  assert (has_child ());
    if (! child_)
        child_.reset (new element (name_, node_.child (), this, ids_, access_, page_));
    return child_; }

element_ptr element::next ()
 {  assert (has_next ());
    if (! sibling_)
        sibling_.reset (new element (name_, node_.next (), parent_, ids_, access_, page_));
    return sibling_; }

element* element::get_ancestor (const e_element e) const
{   element* anc = parent_;
    while (anc != nullptr)
    {   if (anc -> tag () == e) return anc;
        if (anc -> tag () == elem_template) break;
        anc = anc -> parent_; }
    return nullptr; }

element* element::get_ancestor_member (const uint64_t f) const
{   element* anc = parent_;
    while (anc != nullptr)
    {   if ((anc -> node_.id ().categories () & f) != 0) return anc;
        if (anc -> tag () == elem_template) break;
        anc = anc -> parent_; }
    return nullptr; }

bool element::has_this_child (const e_element e) const
{   if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (c -> tag () == e) return true;
    return false; }

bool element::has_this_descendant (const e_element e) const
{   return (descendant_elements_.test (e)); }

unsigned element::count_this_child (const e_element e) const
{   unsigned n = 0;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (c -> tag () == e) ++n;
    return n; }

void element::check_ancestors (const e_element self, const element_bitset& gf)
{   element_bitset tmp (ancestral_elements_);
    tmp &= gf;
    if (tmp.any ())
        pick (nit_bad_ancestor, es_error, ec_element, "No <", elem::name (self), "> can have an ancestral ", nameset (gf)); }

void element::check_descendants (const e_element self, const element_bitset& gf)
{   element_bitset tmp (descendant_elements_);
    tmp &= gf;
    if (tmp.any ())
        pick (nit_bad_descendant, es_error, ec_element, "No <", elem::name (self), "> can have a descendant ", nameset (gf)); }

e_element element::has_immediate_descendant (const e_element e []) const
{   if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            for (::std::size_t i = 0; e [i] != elem_undefined; ++i)
                if (c -> tag () == e [i]) return e [i];
    return elem_undefined; }

void element::check_required_type (const e_element tag)
{   if (tag != elem_img) return;
    if (a_.known (a_type)) return;
    if (node_.version () < html_3_0) return;
    pick (nit_element_no_type, es_comment, ec_element, "has no TYPE attribute"); }

void element::no_anchor_daddy ()
{   if (node_.version ().mjr () >= 5)
        if (ancestral_elements_.test (elem_a))
            pick (nit_interactive, ed_50, "4.5.1 The a element", es_warning, ec_element, "<A> cannot have an interactive descendant element."); }

bool element::only_one_of (const e_element e)
{   if (page_.count (e) == 1) return true;
    pick (nit_only_once, es_error, ec_element, "there should only be one <", node_.id ().name (), "> per page");
    return false; }

bool element::check_math_children (const int expected, const bool or_more)
{   int n = 0;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (! c -> node_.is_closure ()) if (c -> node_.id ().is_math ()) ++n;
    if ((n == expected) || (or_more && (n > expected))) return true;
    if (or_more)
        pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires ", expected, " or more");
    else pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires ", expected);
    return false; }

void element::check_math_children (const int from, const int to)
{   assert (to > from);
    int n = 0;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (! c -> node_.is_closure ()) if (c -> node_.id ().is_math ()) ++n;
    if ((n < from) || (n > to))
        pick (nit_math_kids, ed_math_2, "3.1.3.2 Table of argument requirements", es_error, ec_element, "<", elem::name (tag ()), "> has  ", n, " math child elements; it requires between ", from, " and ", to); }

void element::check_mscarries_pos (const e_element self)
{   bool last = false;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            last = (c -> tag () == elem_mscarries);
    if (last)
        pick (nit_mscarries_last, ed_math_3, "3.6.5 Carries, Borrows, and Crossouts <mscarries>", es_error, ec_element, "<MSCARRIES> cannot be the last child of <", elem::name (self), ">"); }

void element::do_shadow (::std::stringstream& ss, const html_version& v, bool& was_closure, bool& allspace, bool& was_nl)
{   assert (examined_);
    switch (tag ())
    {   case elem_faux_asp : ss << "<%" << node_.raw () << "%>"; was_nl = false; break;
        case elem_faux_cdata : ss << "<![CDATA[" << node_.raw () << "]]>"; was_nl = false; break;
        case elem_faux_char : ss << '&' << node_.raw () << ';'; was_nl = false; break;
        case elem_faux_code : ss << "&#" << node_.raw () << ';'; was_nl = false; break;
        case elem_faux_comment : if (context.shadow_comment ()) { was_nl = false; ss << "<!--" << node_.raw () << "-->"; } break;
        case elem_faux_doctype : ss << "<!DOCTYPE " << v.get_doctype () << ">"; was_nl = false; break;
        case elem_faux_document : was_closure = allspace = false; break;
        case elem_faux_php : ss << "<$" << node_.raw () << "$>"; was_nl = false; break;
        case elem_faux_ssi : if (context.shadow_comment ()) { ss << "<!--" << node_.raw () << "-->"; was_nl = false; } break;
        case elem_faux_stylesheet : ss << "<?xml.stylesheet" << node_.raw () << "?>"; was_nl = false; break;
        case elem_faux_text : ss << node_.raw (); was_nl = false; break;
        case elem_faux_whitespace :
            if (context.shadow_space () || allspace) { ss << node_.raw (); was_nl = false; }
            else if (! was_nl && (was_closure || (node_.raw ().find_first_of ("\n\r\f") != ::std::string::npos)))
            {   ss << "\n"; was_nl = true; }
            else { was_nl = false; ss << " "; }
            was_closure = false; break;
        case elem_faux_xml : ss << "<?xml" << node_.raw () << "?>"; was_nl = false; break;
        case elem_annotation :
        case elem_annotation_xml :
        case elem_comment :
        case elem_plaintext :
        case elem_pre :
        case elem_script :
        case elem_style :
        case elem_xmp : allspace = ! node_.is_closure ();
            // drop thru'
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
    if (has_child ())
    {   element_ptr e = child ();
        do
        {   e -> do_shadow (ss, v, was_closure, allspace, was_nl); }
        while (to_sibling (e)); } }

void element::shadow (::std::stringstream& ss, const html_version& v)
{   bool was_closure = false;
    bool allspace = false;
    bool was_nl = true;
    do_shadow (ss, v, was_closure, allspace, was_nl); }
