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
#include "utility/common.h"
#include "coop/lox.h"

class distilled
{   friend class css_global;
    smsid_t class_, id_, element_class_, element_id_;
    bool in_progress_ = false;
public:
    DEFAULT_CONSTRUCTORS_NO_EMPTY (distilled);
    explicit distilled (bool b) : in_progress_ (b) { } // set to false for a snippet
    explicit distilled (const smsid_t& c, const smsid_t& i, const smsid_t& ec, const smsid_t& ei)
        :   class_ (c), id_ (i), element_class_ (ec), element_id_ (ei)
    { }
    void swap (distilled& cp) noexcept;
    bool wait () const noexcept { return in_progress_; }
    bool sort_it_out () const noexcept { return in_progress_; }
    void set (const smsid_t& c, const smsid_t& i, const smsid_t& ec, const smsid_t& ei)
    {   distilled tmp (c, i, ec, ei);
        swap (tmp); }
    void merge (const distilled& cp);
    smsid_t& cl () { return class_; }
    smsid_t& id () { return id_; }
    smsid_t& ecl () { return element_class_; }
    smsid_t& eid () { return element_id_; }
    const smsid_t& cl () const { return class_; }
    const smsid_t& id () const { return id_; }
    const smsid_t& ecl () const { return element_class_; }
    const smsid_t& eid () const { return element_id_; }
    void accumulate (stats_t* s) const;
    void insert_class (const ::std::string& s, const int n = 1);
    void insert_id (const ::std::string& s, const int n = 1);
    void insert_element_class (const ::std::string& s, const int n = 1);
    void insert_element_id (const ::std::string& s, const int n = 1);
    bool has_class (const ::std::string& s)
    {   return (class_.find (s) != class_.cend ()); }
    bool has_id (const ::std::string& s)
    {   return (id_.find (s) != id_.cend ()); }
    bool has_element_class (const e_element e, const ::std::string& s);
    bool has_element_class (const ::std::string& s)
    {   return (element_class_.find (s) != element_class_.cend ()); }
    bool has_element_id (const e_element e, const ::std::string& s);
    bool has_element_id (const ::std::string& s)
    {   return (element_id_.find (s) != element_id_.cend ()); } };

typedef ::std::shared_ptr < distilled > dst_ptr;
typedef ssc_map < ::std::string, dst_ptr > mdst_t;
