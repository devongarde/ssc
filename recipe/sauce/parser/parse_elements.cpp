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
#include "parser/parse_elements.h"
#include "main/context.h"
#include "parser/text.h"
#include "element/parentage.h"

void elements_node::swap (elements_node& en) NOEXCEPT
{   ::std::swap (invalid_, en.invalid_);
    version_.swap (en.version_);
    ven_.swap (en.ven_); }

void elements_node::reset ()
{   elements_node tmp;
    swap (tmp); }

void elements_node::reset (elements_node& en)
{   elements_node tmp (en);
    swap (tmp); }

::std::string elements_node::text () const
{   if (size () == 0) return ::std::string ();
    return ven_.at (0).text (); }

::std::string elements_node::rpt () const
{   if (size () == 0) return ::std::string ();
    return ven_.at (0).rpt (); }

element_node* elements_node::find_corresponding_open (const elem& id, element_node* parent)
{   assert (parent != nullptr);
    element_node* res = parent;
    while (res != nullptr)
    {   if (res -> id () == id) return res;
        res = res -> parent_; }
    return nullptr; }

void elements_node::report_missing_closures (const html_version& v, element_node* parent, element_node* ancestor)
{   assert (parent != nullptr);
    assert (ancestor != nullptr);
    while (parent -> has_parent ())
    {   if (parent == ancestor) return;
        if (does_apply (v, parent -> id ().first (), parent -> id ().last ()))
            if (does_apply (v, ancestor -> id ().first (), ancestor -> id ().last ()))
            {   bool is_lazy = parent -> id ().is_lazy (v);
                const ::std::string n (parent -> id ().name ());
                parent -> nits_.pick (nit_missing_close, is_lazy ? es_warning : es_error, ec_element, "<", n, "> has no matching </", n, ">"); }
        parent = parent -> parent_; } }

element_node* elements_node::find_permitted_parent (const html_version& v, const elem& id, element_node* parent)
{   assert (parent != nullptr);
    element_node* trans = nullptr;
    while (parent != nullptr)
    {   if (is_permitted_parent (v, id, parent -> id ()))
            if (trans != nullptr) return trans;
            else return parent;
        if (parent -> id ().is_transparent (v))
            if (trans == nullptr)
                if (parent -> tag () != elem_switch) // SVG 2.0: 16.2. Links out of SVG content: the a element
                    trans = parent;
        parent = parent -> parent_; }
    return nullptr; }

void elements_node::report_invalid_parents (nitpick& nits, const html_version& v, const elem& id, element_node* parent, element_node* ancestor, bool closing)
{   assert (parent != nullptr);
    assert (ancestor != nullptr);
    if (does_apply (v, id.first (), id.last ()))
        while ((parent != nullptr) && (parent != ancestor))
        {   if (does_apply (v, parent -> id ().first (), parent -> id ().last ()))
            {   if (closing) is_permitted_parent (v, id, parent -> id ());
                else is_permitted_parent (nits, v, id, parent -> id ());
                nits.pick (nit_inserted_missing_closure, es_warning, ec_element, "inserted missing </", elem :: name (parent -> tag ()), ">"); }
            parent = parent -> parent_; } }

void elements_node::hook_up (element_node* current, element_node*& previous, element_node*& parent, bool closure, bool open)
{   assert (current != nullptr);
    assert (parent != nullptr);
    assert (! (closure && open));

    current -> next_ = current -> previous_ = current -> parent_ = current -> child_ = current -> last_ = nullptr;

    if (previous != nullptr)
    {   previous -> next_ = current;
        current -> previous_ = previous;
        assert (parent == previous -> parent_);
        parent = current -> parent_ = previous -> parent_;
        assert (parent -> last_ == previous);
        parent -> last_ = current; }
    else if (parent -> child_ == nullptr)
    {   parent -> child_ = parent -> last_ = current;
        current -> parent_ = parent; }
    else
    {   assert (parent -> last_ != nullptr);
        current -> parent_ = parent;
        previous = parent -> last_;
        assert (previous -> parent_ == parent);
        current -> previous_ = previous;
        previous -> next_ = current;
        parent -> last_ = current; }

    if (open)
    {   parent = current;
        previous = nullptr; }
    else if (closure)
    {   current = parent;
        assert (current != nullptr);
        parent = current -> parent_;
        previous = current; }
    else previous = current; }

element_node* elements_node::insert_closure (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   assert (parent != nullptr);
    if (ket.eofe_ != ket.end_)
        if (! is_whitespace (ket.eofe_, ket.end_))
            ket.nits_.pick (nit_attributes_on_closure, es_error, ec_element, "attributes not expected on a closure");
    bool matched = false;
    if (does_apply (v, id.first (), id.last ()))
    {   element_node* ancestor = find_corresponding_open (id, parent);
        matched = (ancestor != nullptr);
        if (! matched)
            ket.nits_.pick (nit_missing_open, es_warning, ec_element, "no corresponding <", id.name (), "> found");
        else
        {   report_missing_closures (v, parent, ancestor);
            report_invalid_parents (ket.nits_, v, id, parent, ancestor, true);
            parent = ancestor;
            previous = parent -> last_; } }
    ven_.push_back (element_node (ket.nits_, ket.line_, true, parent, id.get (), ::std::string (ket.start_, ket.end_)));
    element_node* current = & ven_.back ();
    hook_up (current, previous, parent, matched, false);
    return current; }

element_node* elements_node::insert_family_tree (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   assert (id != elem_faux_document);
    elem def (default_parent (v, id));
    element_node* ancestor = find_permitted_parent (v, def, parent);
    if (ancestor == nullptr)
    {   ancestor = insert_family_tree (v, previous, parent, ket, def);
        assert (ancestor != nullptr); }
    nitpick defnits (ket.line_, ket.nits_.get_context ());
    defnits.pick (nit_inserted_missing_parent, es_info, ec_element, "<", parent -> id ().name (), "> cannot have <", id.name (), "> children; inserting intermediate <", def.name (), ">");
    report_missing_closures (v, parent, ancestor);
    report_invalid_parents (defnits, v, def, parent, ancestor);
    parent = ancestor;
    previous = parent -> last_;
    ven_.push_back (element_node (defnits, ket.line_, false, ancestor, def, def.name ()));
    element_node* current = & ven_.back ();
    hook_up (current, previous, parent, false, true);
    return current; }

element_node* elements_node::insert_non_closure (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, bool open)
{   assert (parent != nullptr);
    element_node* current = nullptr;
    element_node* ancestor = find_permitted_parent (v, id, parent);
    if (ancestor != nullptr)
    {   report_invalid_parents (ket.nits_, v, id, parent, ancestor);
        parent = ancestor;
        previous = parent -> last_; }
    else
        insert_family_tree (v, previous, parent, ket, id);
    switch (id.get ())
    {   case elem_faux_whitespace :
            ven_.push_back (element_node (ket.nits_, ket.line_, false, parent, id)); break;
        case elem_faux_stylesheet :
            ven_.push_back (element_node (ket.nits_, ket.line_, false, parent, id, ket.arg ())); break;
        case elem_error :
            ket.nits_.pick (nit_ignoring_unknown, es_error, ec_element, "internal program error: invalid parse token status (", ::boost::lexical_cast < ::std::string > (ket.status_), ")");
            // drip (!) thru'
        default :
            ven_.push_back (element_node (ket.nits_, ket.line_, false, parent, id, ::std::string (ket.start_, ket.end_))); }
    current = & ven_.back ();
    hook_up (current, previous, parent, false, open);
    current -> parse_attributes (v, ket.eofe_, ket.end_);
    return current; }

element_node* elements_node::insert_closed (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   return insert_non_closure (v, previous, parent, ket, id, false); }

element_node* elements_node::insert_open (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   return insert_non_closure (v, previous, parent, ket, id, true); }

element_node* elements_node::insert  (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   if (ket.closed_ || id.is_unclosed (v)) return insert_closed (v, previous, parent, ket, id);
    if (id.is_closed (v))
    {   if (v.xhtml ()) ket.nits_.pick (nit_xhtml_missing_slash, es_error, ec_element, "in ", v.report (), ", closed elements must use the <... /> syntax");
        return insert_closed (v, previous, parent, ket, id); }
    if (ket.closure_) return insert_closure (v, previous, parent, ket, id);
    return insert_open (v, previous, parent, ket, id); }

void elements_node::parse (const html_version& v, bras_ket& elements)
{   ven_.clear ();
    ven_.push_back (element_node (elements.form_, 1, false, nullptr, elem_faux_document, ::std::string ()));
    element_node* document = & ven_.back ();
    document -> version_ = v;
    element_node* parent = document;
    element_node* previous = nullptr;
    for (auto e : elements.ve_)
    {   elem id;
        switch (e.status_)
        {   case bk_asp :       id.reset (elem_faux_asp); break;
            case bk_cdata :     id.reset (elem_faux_text); break;
            case bk_code :      if (v.xhtml ())
                                    if ((parent -> tag () == elem_script) || (parent -> tag () == elem_style))
                                        e.nits_.pick (nit_xhtml_cdata, ed_x1, "4.8. Script and Style elements", es_warning, ec_element, "consider wrapping SCRIPT or STYLE content in <![CDATA[ ... ]]>");
                                id.reset (elem_faux_text); break;
            case bk_doctype :   id.reset (elem_faux_doctype); break;
            case bk_node :      {   ::std::string mc (::std::string (e.start_, e.eofe_));
                                    if (v.xhtml () && ! v.svg () && (mc.find_first_of (UPPERCASE) != ::std::string::npos))
                                        e.nits_.pick (nit_xhtml_element_lc, ed_x1, "4.2. Element and attribute names must be in lower case", es_warning, ec_element, "element names must be lower cased in ", v.report ());
                                    ::boost::to_lower (mc);
                                    id.reset (e.nits_, v, mc); }
                                break;
            case bk_num :       id.reset (elem_faux_text); break;
            case bk_php :       id.reset (elem_faux_php); break;
            case bk_ssi :       id.reset (elem_faux_ssi); break;
            case bk_stylesheet : id.reset (elem_faux_stylesheet); break;
            case bk_xml :       id.reset (elem_faux_xml); break;
            case bk_text :      if (e.is_whitespace ()) id.reset (elem_faux_whitespace);
                                else id.reset (elem_faux_text);
                                break; }
        if (id.unknown ())
            if (static_cast < size_t > (id.ns ()) < first_runtime_namespace)
                e.nits_.pick (nit_ignoring_unknown, es_warning, ec_element, "unknown element <", ::std::string (e.start_, e.eofe_), ">");
        insert (v, previous, parent, e, id); }
    report_missing_closures (v, parent, document);
    if (context.tell (e_splurge))
        context.out () << document -> rpt (0); }

bool elements_node::parse (nitpick& nits, const ::std::string& content)
{   bras_ket elements;
    version_ = elements.parse (nits, content);
    invalid_ = version_.unknown ();
    if (invalid_) nits.merge (elements.form_);
    else parse (version_, elements);
    return ! invalid_; }

void elements_node::harvest_nits (nitpick& nits)
{   for (::std::size_t i = 0; i < ven_.size (); ++i)
        nits.merge (ven_.at (i).nits ()); }

bool elements_node::has_element (const e_element e) const
{   for (::std::size_t i = 0; i < ven_.size (); ++i)
        if (ven_.at (i).id () == e) return true;
    return false; }
