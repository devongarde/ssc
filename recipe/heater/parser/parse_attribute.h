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

#pragma once
#include "attribute/attr.h"
#include "feedback/nitpick.h"
#include "parser/parse_abb.h"

class attributes_node;

// all these require the original string that produced the iterators to be in memory
// presumes copy constructor etc. only used by container class (attributes_node)
class attribute_node
{   ::std::string key_, value_;
    bool has_key_ = false;
    bool has_value_ = false;
    e_attribute id_ = a_unknown;
    attributes_node* box_ = nullptr;
    void parse (nitpick& nits, const html_version& v, const bool normal);
public:
    attribute_node () = default;
    attribute_node (nitpick& nits, const html_version& v, attributes_node* box, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                    const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end, const bool xmlns);
    attribute_node (nitpick& nits, const html_version& v, attributes_node* box, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const bool xmlns);
    attribute_node (const attribute_node& an) = default;
	attribute_node (attribute_node&& an) = default;
    explicit attribute_node (attributes_node* box);
	~attribute_node () = default;
    attribute_node& operator = (const attribute_node& an) { reset (an); return *this; }
	attribute_node& operator = (attribute_node&& an) { reset (an); return *this; }
	void swap (attribute_node& an) noexcept;
    void reset ()
    {   attribute_node an (box_);
        swap (an); }
    void reset (const attribute_node& an)
    {   attribute_node tmp (an);
        swap (tmp); }
    void reset (attribute_node&& an) noexcept
    {   swap (an); }
    e_attribute id () const noexcept { return id_; }
    bool invalid () const noexcept { return id_ == a_unknown; }
    bool has_key () const noexcept { return has_key_; }
    bool has_value () const noexcept { return has_value_; }
    ::std::string get_key () const { PRESUME (has_key_, __FILE__, __LINE__); return key_; }
    ::std::string get_string () const { return value_; }
    const attributes_node* box () const noexcept { return box_; }
    attributes_node* box () noexcept { return box_; }
    prefixes_ptr prefixes () const;
    void prepare_prefixes ();
    namespaces_ptr namespaces () const;
    void prepare_namespaces ();
    ::std::string rpt () const; };
