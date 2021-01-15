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

#include "main/standard.h"
#include "webpage/id.h"
#include "element/element.h"

void ids_t::insert_id (const ::std::string& id, element* pe)
{   assert (pe != nullptr);
    if (pe -> itemscope ().get () != nullptr)
        ids_.emplace (id, sid_t (pe, pe -> tag (), pe -> itemscope () -> type (), pe -> uid (), pe -> hidden ()));
    else
        ids_.emplace (id, sid_t (pe, pe -> tag (), vit_t (), pe -> uid (), pe -> hidden ())); }

bool ids_t::is_hidden (const ::std::string& id) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.cend ()) return false;
    return i -> second.hidden_; }

e_element ids_t::get_tag (const ::std::string& id) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.cend ()) return elem_error;
    return i -> second.elem_; }

uid_t ids_t::get_uid (const ::std::string& id) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.cend ()) return 0;
    return i -> second.uid_; }

bool ids_t::has_itemtype (const ::std::string& id, const itemtype_index s) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.end ()) return false;
    if (i -> second.element_ != nullptr)
    {   for (auto t : i -> second.element_ -> own_itemtype ())
            if (t == s) return true; }
    else for (auto t : i -> second.types_)
        if (t == s) return true;
    return false; }

bool ids_t::has_itemtype (const ::std::string& id, const vit_t vit) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.end ()) return false;
    if (i -> second.element_ != nullptr)
    {   for (auto t : i -> second.element_ -> own_itemtype ())
            for (auto it : vit)
                if (t == it) return true; }
    else for (auto t : i -> second.types_)
        for (auto it : vit)
            if (t == it) return true;
    return false; }

element* ids_t::get_element (const ::std::string& id) const
{   assert (has_id (id));
    mif_t::const_iterator i = ids_.find (id);
    if (i == ids_.cend ()) return nullptr;
    return i -> second.element_; }

void ids_t::cover_arse ()
{   for (auto id : ids_)
        if (id.second.element_ != nullptr)
        {   id.second.types_ = id.second.element_ -> own_itemtype ();
            id.second.element_ = nullptr; } }

bool ids_t::compatible_state (const ::std::string& id, const bool hidden)
{   return compatible_id_state (is_hidden (id), hidden); }

bool compatible_id_state (const bool source, const bool target)
{   if (! target) return true;
    return (source); }
