/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

void elements_node::swap (elements_node& en) noexcept
{   ::std::swap (invalid_, en.invalid_);
    version_.swap (en.version_);
    ven_.swap (en.ven_); }

void elements_node::reset () noexcept
{   elements_node tmp;
    swap (tmp); }

void elements_node::reset (const elements_node& en)
{   elements_node tmp (en);
    swap (tmp); }

::std::string elements_node::text ()
{   if (size () == 0) return ::std::string ();
    return ven_.at (0).text (); }

::std::string elements_node::rpt ()
{   if (size () == 0) return ::std::string ();
    return ven_.at (0).rpt (); }

element_node* elements_node::find_corresponding_open (const elem& id, element_node* parent)
{   PRESUME (parent != nullptr, __FILE__, __LINE__);
    element_node* res = parent;
    while (res != nullptr)
    {   if (res -> id () == id) return res;
        res = res -> parent_; }
    return nullptr; }

void elements_node::report_missing_closures (const html_version& v, element_node* parent, element_node* ancestor)
{   VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    VERIFY_NOT_NULL (ancestor, __FILE__, __LINE__);
    while (parent -> has_parent ())
    {   if (parent == ancestor) return;
        if (does_apply < html_version > (v, parent -> id ().first (), parent -> id ().last ()))
            if (does_apply < html_version > (v, ancestor -> id ().first (), ancestor -> id ().last ()))
            {   const bool is_lazy = parent -> id ().is_lazy (v);
                const ::std::string n (parent -> id ().name ());
                parent -> nits_.pick (nit_missing_close, is_lazy ? es_warning : es_error, ec_element, "<", n, "> has no matching </", n, ">"); }
        parent = parent -> parent_; } }

element_node* elements_node::find_permitted_parent (const html_version& v, const elem& id, element_node* parent)
{   VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
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

void elements_node::repair_invalid_parents (nitpick& nits, const html_version& v, const elem& id, element_node* parent, const element_node* ancestor, const bra_element_ket& ket, const bool closing)
{   VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    VERIFY_NOT_NULL (ancestor, __FILE__, __LINE__);
    if (does_apply < html_version > (v, id.first (), id.last ()))
        while ((parent != nullptr) && (parent != ancestor))
        {   if (does_apply < html_version > (v, parent -> id ().first (), parent -> id ().last ()))
            {   if (closing) is_permitted_parent (v, id, parent -> id ());
                else is_permitted_parent (nits, v, id, parent -> id ());
                nits.pick (nit_inserted_missing_closure, es_warning, ec_element, "inserted missing </", elem :: name (parent -> tag ()), ">");
                const elem def (parent -> tag ());
                nitpick defnits (ket.line_, ket.nits_.get_context ());
                ven_.push_back (element_node (defnits, this, ket.line_, true, parent, def, true, def.name ()));
                element_node* current = & ven_.back ();
                element_node* previous = nullptr;
                hook_up (current, previous, parent, false, false); }
            parent = parent -> parent_; } }

void elements_node::hook_up (element_node* current, element_node*& previous, element_node*& parent, const bool closure, const bool open)
{   VERIFY_NOT_NULL (current, __FILE__, __LINE__);
    VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    PRESUME (! (closure && open), __FILE__, __LINE__);
    current -> next_ = current -> previous_ = current -> parent_ = current -> child_ = current -> last_ = nullptr;
    if (previous != nullptr)
    {   previous -> next_ = current;
        current -> previous_ = previous;
        PRESUME (parent == previous -> parent_, __FILE__, __LINE__);
        parent = current -> parent_ = previous -> parent_;
        PRESUME (parent -> last_ == previous, __FILE__, __LINE__);
        parent -> last_ = current; }
    else if (parent -> child_ == nullptr)
    {   parent -> child_ = parent -> last_ = current;
        current -> parent_ = parent; }
    else
    {   PRESUME (parent -> last_ != nullptr, __FILE__, __LINE__);
        current -> parent_ = parent;
        previous = parent -> last_;
        VERIFY_NOT_NULL (previous, __FILE__, __LINE__);
        PRESUME (previous -> parent_ == parent, __FILE__, __LINE__);
        current -> previous_ = previous;
        previous -> next_ = current;
        parent -> last_ = current; }
    if (open)
    {   parent = current;
        previous = nullptr; }
    else if (closure)
    {   current = parent;
        PRESUME (current != nullptr, __FILE__, __LINE__);
        parent = current -> parent_;
        previous = current; }
    else previous = current; }

element_node* elements_node::insert_closure (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool presumed)
{   PRESUME (parent != nullptr, __FILE__, __LINE__);
    if (ket.eofe_ != ket.end_)
        if (! is_whitespace (ket.eofe_, ket.end_))
            ket.nits_.pick (nit_attributes_on_closure, es_error, ec_element, "attributes not expected on a closure");
    bool matched = false;
    if (does_apply < html_version > (v, id.first (), id.last ()))
    {   element_node* ancestor = find_corresponding_open (id, parent);
        matched = (ancestor != nullptr);
        if (! matched)
            ket.nits_.pick (nit_missing_open, es_warning, ec_element, "no corresponding <", id.name (), "> found");
        else
        {   report_missing_closures (v, parent, ancestor);
            repair_invalid_parents (ket.nits_, v, id, parent, ancestor, ket, true);
            parent = ancestor;
            VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
            previous = parent -> last_; } }
    ven_.push_back (element_node (ket.nits_, this, ket.line_, true, parent, id.get (), presumed, ::std::string (ket.start_, ket.end_)));
    const ::gsl::not_null < element_node* > current = & ven_.back ();
    hook_up (current, previous, parent, matched, false);
    PRESUME (current -> box () == this, __FILE__, __LINE__);
    return current; }

element_node* elements_node::insert_family_tree (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool presumed)
{   PRESUME (id != elem_faux_document, __FILE__, __LINE__);
    const elem def (default_parent (v, id));
    element_node* ancestor = find_permitted_parent (v, def, parent);
    if (ancestor == nullptr)
    {   ancestor = insert_family_tree (v, previous, parent, ket, def, true);
        PRESUME (ancestor != nullptr, __FILE__, __LINE__); }
    nitpick defnits (ket.line_, ket.nits_.get_context ());
    VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    defnits.pick (nit_inserted_missing_parent, es_info, ec_element, "<", parent -> id ().name (), "> cannot have <", id.name (), "> children; inserting intermediate <", def.name (), ">");
    report_missing_closures (v, parent, ancestor);
    repair_invalid_parents (defnits, v, def, parent, ancestor, ket, false);
    parent = ancestor;
    VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    previous = parent -> last_;
    ven_.push_back (element_node (defnits, this, ket.line_, false, ancestor, def, presumed, def.name ()));
    const ::gsl::not_null < element_node*> current = & ven_.back ();
    current -> attributes ().box (current);
    hook_up (current, previous, parent, false, true);
    PRESUME (current -> box () == this, __FILE__, __LINE__);
    return current; }

element_node* elements_node::insert_non_closure (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool open)
{   PRESUME (parent != nullptr, __FILE__, __LINE__);
    element_node* current = nullptr;
    element_node* ancestor = find_permitted_parent (v, id, parent);
    if (ancestor != nullptr)
    {   repair_invalid_parents (ket.nits_, v, id, parent, ancestor, ket, false);
        parent = ancestor;
        VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
        previous = parent -> last_; }
    else
        insert_family_tree (v, previous, parent, ket, id, false);
    switch (id.get ())
    {   case elem_faux_whitespace :
            ven_.push_back (element_node (ket.nits_, this, ket.line_, false, parent, id, false)); break;
        case elem_faux_stylesheet :
            ven_.push_back (element_node (ket.nits_, this, ket.line_, false, parent, id, false, ket.arg ())); break;
        case elem_error :
            ket.nits_.pick (nit_internal_parsing_error, es_error, ec_element, "internal program error: invalid parse token status (", ::boost::lexical_cast < ::std::string > (ket.status_), ")");
            // drip (!) thru'
        default :
            ven_.push_back (element_node (ket.nits_, this, ket.line_, false, parent, id, false, ::std::string (ket.start_, ket.end_))); }
    current = & ven_.back ();
    VERIFY_NOT_NULL (current, __FILE__, __LINE__);
    hook_up (current, previous, parent, false, open);
    current -> parse_attributes (v, ket.eofe_, ket.end_);
    PRESUME (current -> box () == this, __FILE__, __LINE__);
    PRESUME (current -> attributes ().box () == current, __FILE__, __LINE__);
    return current; }

element_node* elements_node::insert_closed (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   element_node* current = insert_non_closure (v, previous, parent, ket, id, false);
    if (current != nullptr)
    {   current -> closed_ = true;
        if (context.copy () > c_none)
            switch (id.get ())
            {   case elem_faux_asp :
                case elem_faux_cdata :
                case elem_faux_char :
                case elem_faux_code :
                case elem_faux_comment :
                case elem_faux_php :
                case elem_faux_ssi :
                case elem_faux_stylesheet :
                case elem_faux_text :
                case elem_faux_whitespace :
                case elem_faux_xml :
                    current -> set_raw (::std::string (ket.start_, ket.end_));
                    break;
                default : break; } }
    return current; }

element_node* elements_node::insert_open (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   return insert_non_closure (v, previous, parent, ket, id, true); }

element_node* elements_node::insert  (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id)
{   if (ket.closed_ || id.is_unclosed (v)) return insert_closed (v, previous, parent, ket, id);
    if (id.is_closed (v))
    {   if (v.xhtml ()) ket.nits_.pick (nit_xhtml_missing_slash, es_error, ec_element, "in ", v.report (), ", closed elements must use the <... /> syntax");
        return insert_closed (v, previous, parent, ket, id); }
    if (ket.closure_) return insert_closure (v, previous, parent, ket, id, false);
    return insert_open (v, previous, parent, ket, id); }

void elements_node::parse (const html_version& v, bras_ket& elements)
{   ven_.clear ();
    ven_.push_back (element_node (elements.form_, this, 1, false, nullptr, elem_faux_document, false, ::std::string ()));
    element_node* document = & ven_.back ();
    VERIFY_NOT_NULL (document, __FILE__, __LINE__);
    document -> version_ = v;
    if (context.rdfa ()) document -> prepare_prefixes ();
    element_node* parent = document;
    element_node* previous = nullptr;
    for (auto e : elements.ve_)
    {   elem id;
        VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
        const html_version ver (parent -> version_);
        switch (e.status_)
        {   case bk_asp :       id.reset (elem_faux_asp); break;
            case bk_cdata :     id.reset (elem_faux_cdata); break;
            case bk_comment :   id.reset (elem_faux_comment); break;
            case bk_code :      if (ver.xhtml ())
                                    if ((parent -> tag () == elem_script) || (parent -> tag () == elem_style))
                                        e.nits_.pick (nit_xhtml_cdata, ed_x1, "4.8. Script and Style elements", es_warning, ec_element, "consider wrapping SCRIPT or STYLE content in <![CDATA[ ... ]]>");
                                id.reset (elem_faux_char); break;
            case bk_doctype :   id.reset (elem_faux_doctype); break;
            case bk_node :      {   ::std::string mc (::std::string (e.start_, e.eofe_));
                                    if (e.eofe_ < e.end_) attributes_node::process_attributes (e.nits_, ver, parent, e.eofe_, e.end_, e.line_);
                                    id.reset (e.nits_, ver, parent -> namespaces (), mc);
                                    if (ver.xhtml () && ! id.unknown ())
                                    {   const ::std::string& naam (id.name ());
                                        if (parent -> version_.xhtml () && (naam != mc))
                                            if (mc.find (':') == ::std::string::npos)
                                                if ((id.flags () & EP_NO_WHINGE) == 0)
                                                    if (naam.find_first_of (UPPERCASE) != ::std::string::npos)
                                                        e.nits_.pick (nit_xhtml_element_lc, ed_x1, "4.2. Element and attribute names must be in lower case", es_warning, ec_element, "element names must match case in ", v.report ());
                                                    else e.nits_.pick (nit_xhtml_element_lc, ed_x1, "4.2. Element and attribute names must be in lower case", es_warning, ec_element, "standard element names must be in lower case in ", v.report ()); } }
                                break;
            case bk_num :       id.reset (elem_faux_code); break;
            case bk_php :       id.reset (elem_faux_php); break;
            case bk_ssi :       id.reset (elem_faux_ssi); break;
            case bk_stylesheet: id.reset (elem_faux_stylesheet); break;
            case bk_xml :       id.reset (elem_faux_xml); break;
            case bk_text :      if (e.is_whitespace ()) id.reset (elem_faux_whitespace);
                                else id.reset (elem_faux_text);
                                break; }
        if (id.unknown ())
        {   ::std::string s (e.start_, e.eofe_);
            if (::gsl::narrow_cast < size_t > (id.ns ()) < first_runtime_namespace)
                e.nits_.pick (nit_unknown_element, es_warning, ec_element, PROG " does not know the element <", ::std::string (s), ">, so cannot verify it");
            else e.nits_.pick (nit_unknown_element, es_comment, ec_element, PROG " does not know <", ::std::string (s), ">, so cannot verify it");
            if (v.xhtml () && (s == "base"))
                e.nits_.pick (nit_unknown_element, es_comment, ec_element, "in XHTML, use <xml:base>, not <base>"); }

        insert (ver, previous, parent, e, id); }
    report_missing_closures (v, parent, document);
    if (context.tell (e_splurge))
    {   VERIFY_NOT_NULL (document, __FILE__, __LINE__);
        ::std::cerr << document -> rpt (0); } }

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

// temporary, until the XML code is rewritten
element_node* elements_node::faux_node ()
{   PRESUME (ven_.size () == 0, __FILE__, __LINE__);
    nitpick nuts;
    ven_.push_back (element_node (nuts, this, 1, false, nullptr, elem_faux_document, false, ::std::string ()));
    PRESUME (ven_.size () == 1, __FILE__, __LINE__);
    return &ven_.at (0); }

