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
#include "attribute/attr.h"
#include "feedback/nitpick.h"

// all these require the original string that produced the iterators to be in memory

class attribute_node
{   ::std::string key_, value_;
    bool has_key_ = false;
    bool has_value_ = false;
    e_attribute id_ = a_unknown;
    void parse (nitpick& nits, const html_version& v, ns_ptr& nss);
public:
    attribute_node () = default;
    attribute_node (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end);
    attribute_node (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end);
    attribute_node (const attribute_node& an) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	attribute_node(attribute_node&& an) = default;
#endif
	~attribute_node () = default;
    attribute_node& operator = (const attribute_node& an) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	attribute_node& operator = (attribute_node&& an) = default;
#endif
	void swap (attribute_node& an);
    void reset ()
    {   attribute_node an;
        swap (an); }
    void reset (const attribute_node& an)
    {   attribute_node tmp (an);
        swap (tmp); }
    e_attribute id () const { return id_; }
    bool invalid () const { return id_ == a_unknown; }
    bool has_key () const { return has_key_; }
    bool has_value () const { return has_value_; }
    ::std::string get_key () const { PRESUME (has_key_, __FILE__, __LINE__); return key_; }
    ::std::string get_string () const { return value_; }
    ::std::string rpt () const; };
