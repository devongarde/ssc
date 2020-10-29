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

#pragma once
#include "attribute/attr.h"
#include "feedback/nitpick.h"

// all these require the original string that produced the iterators to be in memory

class attribute_node
{   ::std::string::const_iterator name_start_;
    ::std::string::const_iterator name_end_;
    ::std::string::const_iterator value_start_;
    ::std::string::const_iterator value_end_;
    bool has_key_ = false;
    bool has_value_ = false;
    e_attribute id_ = a_unknown;
    void parse (nitpick& nits, const html_version& v)
    {   id_ = attr :: parse (nits, v, ::std::string (name_start_, name_end_)); }
public:
    attribute_node () = default;
    attribute_node (nitpick& nits, const html_version& v, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end);
    attribute_node (nitpick& nits, const html_version& v, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end);
    attribute_node (const attribute_node& an) = default;
    attribute_node (attribute_node&& an) = default;
    ~attribute_node () = default;
    attribute_node& operator = (const attribute_node& an) = default;
    attribute_node& operator = (attribute_node&& an) = default;
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
    ::std::string get_key () const { assert (has_key_); return ::std::string (name_start_, name_end_); }
    ::std::string get_string () const { if (! has_value_) return ::std::string (); return ::std::string (value_start_, value_end_); }
    ::std::string rpt () const; };
