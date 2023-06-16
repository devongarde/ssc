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

struct arguments;
class css;
typedef ::std::shared_ptr < css > css_ptr;

class distilled
{   friend class css_global;
    smsid_t class_, id_, element_class_, element_id_, font_;
    css_ptr cp_;
    v_np ticks_;
    bool in_progress_ = false, file_ = false;
public:
    DEFAULT_CONSTRUCTORS_NO_EMPTY (distilled);
    explicit distilled (bool b) : in_progress_ (b) { } // set to false for a snippet
    explicit distilled (const smsid_t& c, const smsid_t& i, const smsid_t& ec, const smsid_t& ei)
        :   class_ (c), id_ (i), element_class_ (ec), element_id_ (ei)
    { }
    bool wait () const noexcept { return in_progress_; }
    bool sort_it_out () const noexcept { return in_progress_; }
    css_ptr css () const { return cp_; }
    void css (const css_ptr cp) { cp_ = cp; }
    void reset ();
    css_ptr expel () { css_ptr res (cp_); cp_.reset (); return res; }
    smsid_t& cl () { return class_; }
    smsid_t& id () { return id_; }
    smsid_t& ecl () { return element_class_; }
    smsid_t& eid () { return element_id_; }
    smsid_t& f () { return element_id_; }
    const smsid_t& cl () const { return class_; }
    const smsid_t& id () const { return id_; }
    const smsid_t& ecl () const { return element_class_; }
    const smsid_t& eid () const { return element_id_; }
    const smsid_t& f () const { return element_id_; }
    void accumulate (stats_t* s) const;
    void insert_class (const ::std::string& s, const int n = 1)
    {   insert_smsid (class_, s, n); }
    void insert_id (const ::std::string& s, const int n = 1)
    {   insert_smsid (id_, s, n); }
    void insert_element_class (const ::std::string& s, const int n = 1)
    {   insert_smsid (element_class_, s, n); }
    void insert_element_id (const ::std::string& s, const int n = 1)
    {   insert_smsid (element_id_, s, n); }
    void insert_font (const ::std::string& s, const int n = 1)
    {   insert_smsid (font_, s, n); }
    bool has_class (const ::std::string& s) const
    {   return (class_.find (s) != class_.cend ()); }
    bool has_id (const ::std::string& s) const
    {   return (id_.find (s) != id_.cend ()); }
    bool has_element_class (const e_element e, const ::std::string& s) const;
    bool has_element_class (const ::std::string& s) const
    {   return (element_class_.find (s) != element_class_.cend ()); }
    bool has_element_id (const e_element e, const ::std::string& s) const;
    bool has_element_id (const ::std::string& s) const
    {   return (element_id_.find (s) != element_id_.cend ()); }
    bool has_font (const ::std::string& s) const
    {   return (font_.find (s) != font_.cend ()); }
    void merge (const nitpick& ticks)
    {   ticks_.push_back (ticks); }
    ::std::string review (const mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false); };

typedef ::std::shared_ptr < distilled > dst_ptr;
typedef ssc_map < ::std::string, dst_ptr > mdst_t;
