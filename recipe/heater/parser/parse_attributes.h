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
#include "parser/parse_attribute.h"
#include "element/elem.h"
#include "parser/parse_abb.h"

typedef ::std::vector < attribute_node > van_t;
class element_node;

// presumes copy constructor etc. only used by container class (element_node)
class attributes_node
{   van_t va_;
    element_node* box_ = nullptr;
    void report_invalid (nitpick& nits, const html_version& v, const bool known, const ::std::string::const_iterator key_start, const ::std::string::const_iterator key_end, const elem& el) const;
    void push_back_and_report ( nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end, const elem& el, const bool normal);
    void push_back_and_report ( nitpick& nits, const html_version& v, sstr_t& keyed, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                const elem& el, const bool normal);
public:
    attributes_node () = default;
    explicit attributes_node (element_node* box);
    attributes_node (const attributes_node& an) = default;
    attributes_node (element_node* box, const attributes_node& an)
        :   box_ (box)
    {   va_ = an.va_; }
#ifndef NO_MOVE_CONSTRUCTOR
//	attributes_node(attributes_node&& an) = default;
#endif
	~attributes_node() = default;
//    attributes_node& operator = (const attributes_node& an) = default;
#ifndef NO_MOVE_CONSTRUCTOR
//	attributes_node& operator = (attributes_node&& an) = default;
#endif
	void swap (attributes_node& an)
    {   va_.swap (an.va_);
        ::std::swap (box_, an.box_); }
    void reset ()
    {   attributes_node an (box_);
        swap (an); }
    void reset (const attributes_node& an)
    {   attributes_node tmp (box_, an);
        swap (tmp); }
    const van_t& get_attributes () const { return va_; }
    e_svg_version get_svg (const html_version& v) const;
    e_math_version get_math (const html_version& v) const;
    void manage_xmlns (nitpick& nits, html_version& v);
    bool empty () const { return va_.size () == 0; }
    static void process_attributes (nitpick& nits, const html_version& v, element_node* box, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line);
    void parse (nitpick& nits, const html_version& v, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line, const elem& el, const bool normal);
    const element_node* box () const { return box_; }
    element_node* box () { return box_; }
    void box (element_node* b) { box_ = b; }
    prefixes_ptr prefixes () const;
    void prepare_prefixes ();
    namespaces_ptr namespaces () const;
    void prepare_namespaces ();
    ::std::size_t size () const { return va_.size (); }
    ::std::string rpt () const; };
