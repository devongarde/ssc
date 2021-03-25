/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

class element_node
{   friend class elements_node;
    element_node* parent_ = nullptr;
    element_node* child_ = nullptr;
    element_node* last_ = nullptr;
    element_node* next_ = nullptr;
    element_node* previous_ = nullptr;
    int line_ = 0;
    bool closure_ = false, closed_ = false, checked_sanitised_ = false, presumed_ = false;
    elem elem_;
    attributes_node va_;
    ::std::string text_, raw_, sanitised_;
    nitpick nits_;
    html_version version_;
    ::std::string inner_text () const;
public:
    element_node () = default;
    element_node (nitpick& nits, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const e_element tag, const bool presumed);
    element_node (nitpick& nits, const int line, const bool closure, element_node* parent, element_node* child, element_node* next, element_node* previous, const elem& el, const bool presumed);
    element_node (nitpick& nits, const int line, const bool closure, element_node* parent, const e_element tag, const bool presumed, const ::std::string str = ::std::string ());
    element_node (nitpick& nits, const int line, const bool closure, element_node* parent, const elem& el, const bool presumed, const ::std::string str = ::std::string ());
    element_node (const element_node& en) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	element_node(element_node&& en) = default;
#endif
	~element_node ();
    element_node& operator = (const element_node& en) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	element_node& operator = (element_node&& en) = default;
#endif
	void swap(element_node& en) NOEXCEPT;
    void reset ();
    void reset (const element_node& en);
    void parse_attributes (const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e);
    ::std::size_t attribute_count () const { return va_.size (); }
    ::std::string text ();
    ::std::string raw () const { return raw_; }
    ::std::string rpt (const int level = 0);
    void set_raw (const ::std::string& raw) { raw_ = raw; }
    int line () const { return line_; }
    bool invalid () const { return elem_.unknown (); }
    bool is_closure () const { return closure_; }
    bool is_closed () const { return closed_; }
    bool has_child () const { return child_ != nullptr; }
    bool has_next () const { return next_ != nullptr; }
    bool has_last () const { return last_ != nullptr; }
    bool has_previous () const { return previous_ != nullptr; }
    bool has_parent () const { return parent_ != nullptr; }
    bool presumed () const { return presumed_; }
    const element_node& child () const
    {   assert (has_child ());
        return *child_; }
    const element_node& last () const
    {   assert (has_last ());
        return *last_; }
    const element_node& next () const
    {   assert (has_next ());
        return *next_; }
    const element_node& previous () const
    {   assert (has_previous ());
        return *previous_; }
    const element_node& parent () const
    {   assert (has_parent ());
        return *parent_; }
    element_node& child ()
    {   assert (has_child ());
        return *child_; }
    element_node& next ()
    {   assert (has_next ());
        return *next_; }
    element_node& previous ()
    {   assert (has_previous ());
        return *previous_; }
    element_node& parent ()
    {   assert (has_parent ());
        return *parent_; }

    nitpick& nits () { return nits_; }

    bool has_attributes () const { return va_.size () > 0; }
    const attributes_node& attributes () const { return va_; }
    html_version version () const { return version_; }
    const html_version& version () { return version_; }

    void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, char* const msg)
    {   nits_.pick (code, doc, ref, severity, category, msg); }
    void pick (const e_nit code, const e_severity severity, const e_category category, const char* msg)
    {   nits_.pick (code, severity, category, msg); }
    template < typename ... Ts > void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.pick (code, doc, ref, severity, category, msg...); }
    template < typename ... Ts > void pick (const e_nit code, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.pick (code, severity, category, msg...); }

    void merge (const nitpick& np) { nits_.merge (np); }
    void merge (nitpick&& np) { nits_.merge (np); }

    elem& id () { return elem_; }
    const elem& id () const { return elem_; }
    e_element tag () const { return elem_.get (); } };
