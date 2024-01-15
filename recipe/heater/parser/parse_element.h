/*
ssc (static site checker)
File Info
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

#pragma once
#include "element/elem.h"
#include "parser/parse_attributes.h"
#include "parser/parse_abb.h"
#include "rdf/rdf.h"

class elements_node;

class element_node
{   friend class elements_node;
    typedef enum { enab_namespace, enab_prefix, enab_error } e_abb;
    element_node* parent_ = nullptr;
    element_node* child_ = nullptr;
    element_node* last_ = nullptr;
    element_node* next_ = nullptr;
    element_node* previous_ = nullptr;
    elements_node* box_ = nullptr;
    int line_ = 0;
    bool closure_ = false, closed_ = false, checked_sanitised_ = false, presumed_ = false;
    elem elem_;
    attributes_node va_;
    ::std::string text_, raw_, sanitised_;
    nitpick nits_;
    html_version version_;
    namespaces_ptr namespaces_;
    prefixes_ptr prefixes_, rdf_schemas_;
    rdf_ptr rdf_, rdfa_;
    ::std::string inner_text (const bool simplify = false) const;
    ::std::string inner_text (nitpick& nits, const html_version& v) const;
    void init ();
    void manage_reversioner ();

    namespaces_ptr find_namespace_parent () const noexcept;
    prefixes_ptr find_prefixes_parent () const noexcept;
    prefixes_ptr find_rdf_schemas_parent () const noexcept;
    rdf_ptr find_rdf_parent () const noexcept;
    rdf_ptr find_rdfa_parent () const noexcept;
    ::std::string word (bool simplify) const;
    ::std::string word (nitpick& nits, const html_version& v) const;
public:
    DEFAULT_CONSTRUCTORS (element_node);
    element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const e_element tag, const bool presumed);
    element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const elem& el, const bool presumed);
    element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, const e_element tag, const bool presumed, const ::std::string str = ::std::string ());
    element_node (nitpick& nits, elements_node* box, const int line, const bool closure, element_node* parent, const elem& el, const bool presumed, const ::std::string str = ::std::string ());
    explicit element_node (elements_node* box);
	void swap (element_node& en) noexcept;
    void reset ();
    void reset (const element_node& en);
    void parse_attributes (const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e);
    ::std::size_t attribute_count () const noexcept { return va_.size (); }
    ::std::string text (const bool simplify = false);
    ::std::string raw () const { return raw_; }
    void set_raw (const ::std::string& raw) { raw_ = raw; }
    int line () const noexcept { return line_; }
    bool invalid () const noexcept { return elem_.unknown (); }
    bool is_closure () const noexcept { return closure_; }
    bool is_closed () const noexcept { return closed_; }
    bool has_child () const noexcept { return child_ != nullptr; }
    bool has_next () const noexcept { return next_ != nullptr; }
    bool has_last () const noexcept { return last_ != nullptr; }
    bool has_previous () const noexcept { return previous_ != nullptr; }
    bool has_parent () const noexcept { return parent_ != nullptr; }
    bool presumed () const noexcept { return presumed_; }

    const element_node& child () const
    {   PRESUME (has_child (), __FILE__, __LINE__);
        return *child_; }
    const element_node& last () const
    {   PRESUME (has_last (), __FILE__, __LINE__);
        return *last_; }
    const element_node& next () const
    {   PRESUME (has_next (), __FILE__, __LINE__);
        return *next_; }
    const element_node& previous () const
    {   PRESUME (has_previous (), __FILE__, __LINE__);
        return *previous_; }
    const element_node& parent () const
    {   PRESUME (has_parent (), __FILE__, __LINE__);
        return *parent_; }
    element_node& child ()
    {   PRESUME (has_child (), __FILE__, __LINE__);
        return *child_; }
    element_node& next ()
    {   PRESUME (has_next (), __FILE__, __LINE__);
        return *next_; }
    element_node& previous ()
    {   PRESUME (has_previous (), __FILE__, __LINE__);
        return *previous_; }
    element_node& parent ()
    {   PRESUME (has_parent (), __FILE__, __LINE__);
        return *parent_; }

    nitpick& nits () noexcept { return nits_; }

    bool has_attributes () const noexcept { return va_.size () > 0; }
    const attributes_node& attributes () const noexcept { return va_; }
    attributes_node& attributes () noexcept { return va_; }
    html_version& version () noexcept { return version_; }
    const html_version& version () const noexcept { return version_; }

    void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, char* const msg)
    {   nits_.pick (code, doc, ref, severity, category, msg); }
    void pick (const e_nit code, const e_severity severity, const e_category category, const char* msg)
    {   nits_.pick (code, severity, category, msg); }
    template < typename ... Ts > void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.pick (code, doc, ref, severity, category, msg...); }
    template < typename ... Ts > void pick (const e_nit code, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.pick (code, severity, category, msg...); }

    void merge (const nitpick& np) { nits_.merge (np); }

    elem& id () noexcept { return elem_; }
    const elem& id () const noexcept { return elem_; }
    const elements_node* box () const noexcept { return box_; }

    void prepare_namespaces ();
    namespaces_ptr namespaces () const noexcept;
    void prepare_prefixes ();
    prefixes_ptr prefixes () const noexcept;
    void prepare_rdf_schemas ();
    prefixes_ptr rdf_schemas () const noexcept;
    void prepare_rdf ();
    rdf_ptr rdf () const noexcept;
    void prepare_rdfa ();
    rdf_ptr rdfa () const noexcept;

    e_element tag () const noexcept;
    vstr_t words (nitpick& nits, const html_version& v) const;
    ::std::string rpt (const int level = 0); };
