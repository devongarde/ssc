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
#include "utility/common.h"
#include "webpage/fileindex.h"
#include "type/enum.h"
#include "microdata/microdata_itemtype.h"

class element;

struct sid_t
{   uid_t uid_ = 0;
    bool hidden_ = false;
    vit_t types_;
    e_element elem_ = elem_error;
    element* element_ = nullptr;
    sid_t (element* ptr, const e_element e, const vit_t types, const uid_t uid, const bool hidden)
        : uid_ (uid), hidden_ (hidden), types_ (types), elem_ (e), element_ (ptr) { } };

typedef ssc_map < ::std::string, sid_t > mif_t;

class ids_t
{   fileindex_t ndx_ = nullfileindex;
    mif_t ids_;
    ::std::size_t data_ = 0;
    bool unique_ = true;
public:
    void swap (ids_t& x) noexcept
    {   ::std::swap (ndx_, x.ndx_);
        ::std::swap (data_, x.data_);
        ::std::swap (unique_, x.unique_);
        ids_.swap (x.ids_); }
    fileindex_t ndx () const noexcept { return ndx_; }
    void ndx (fileindex_t x, const bool b = true) noexcept
    {   ndx_ = x; unique_ = b; }
    bool unique () const noexcept { return unique_; }
    ::std::size_t data () const noexcept { return data_; }
    void data (::std::size_t x) noexcept { data_ = x; }
    bool empty () const noexcept
    {   return ids_.empty (); }
    bool has_id (const ::std::string& id) const
    {   return (ids_.find (id) != ids_.cend ()); }
    void insert_id (const ::std::string& id, element* pe);
    void cover_arse ();
    const mif_t& mif () const noexcept { return ids_; }
    bool compatible_state (const ::std::string& id, const bool hidden);
    bool compatible_category (const html_version& v, const element& e, const e_sought_category cat);
    bool is_hidden (const ::std::string& id) const;
    bool has_itemtype (const ::std::string& id, const itemtype_index s) const;
    bool has_itemtype (const ::std::string& id, const vit_t vit) const;
    e_element get_tag (const ::std::string& id) const;
    uid_t get_uid (const ::std::string& id) const;
    element* get_element (const ::std::string& id) const;
    static bool is_good_id (element& e, const ::std::string& s, const e_category naughty_cat, const e_nit naughty_nit, const bool hidden_concern); };

bool compatible_id_state (const bool source, const bool target) noexcept;
