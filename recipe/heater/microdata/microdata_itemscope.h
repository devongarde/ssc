/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "microdata/microdata_export.h"

class microdata_itemscope;
class page;

typedef ::std::shared_ptr < microdata_itemscope > itemscope_ptr;
typedef ssc_variant < itemscope_ptr, ::std::string > itemprop_value;
typedef ssc_mm < itemprop_index, itemprop_value > mpv_t;

class microdata_itemscope
{   mpv_t itemprop_;
    vit_t type_;
    microdata_export* export_ = nullptr;
    ::std::string export_path_;
    itemscope_ptr parent_;
    itemprop_indices prepare_itemprop_indices (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value);
    bool use_parent () const noexcept { return (type_.empty () && (parent_.get () != nullptr)); }
public:
    void swap (microdata_itemscope& mi);
    void note_itemtype (nitpick& nits, const html_version& v, const ::std::string& name, page& p, const bool has_itemid);
    bool note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, const bool is_link, page& p);
    bool note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, itemscope_ptr& scope, page& p);
    bool note_itemid (nitpick& nits, const html_version& v, const ::std::string& name);
    vit_t type () const
    {   if (use_parent ())
        {   VERIFY_NOT_NULL (parent_, __FILE__, __LINE__);
            return parent_ -> type (); }
        return type_; }
    void parent (const itemscope_ptr& parent) noexcept { parent_ = parent; }
    itemscope_ptr& parent () noexcept { return parent_; }
    vit_t sought_itemtypes (const html_version& v, const ::std::string& name) const;
    ::std::string report (const ::std::size_t offset = 0) const;
    void set_exporter (microdata_export* exporter, const ::std::string& export_path)
    {   export_ = exporter; export_path_ = export_path; }
    ::std::string export_path () const
    {   if (use_parent ())
        {   VERIFY_NOT_NULL (parent_, __FILE__, __LINE__);
            return parent_ -> export_path (); }
        return export_path_; }
    microdata_export* exporter () const
    {   if (use_parent ())
        {   VERIFY_NOT_NULL (parent_, __FILE__, __LINE__);
            return parent_ -> exporter (); }
        return export_; }
    bool write (nitpick& nits, const ::boost::filesystem::path& name); };

bool are_categories_compatible (const e_itemprop_category ipc, const e_itemtype_category itc);
bool are_categories_compatible (nitpick& nits, const html_version& v, const itemprop_index ipi, const itemtype_index iti);
bool are_compatible_types (nitpick& nits, const html_version& v, const itemtype_index lhs, const itemtype_index rhs);
