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
{   VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
    if (pe -> itemscope ().get () != nullptr)
        ids_.emplace (id, sid_t (pe, pe -> tag (), pe -> itemscope () -> type (), pe -> uid (), pe -> hidden ()));
    else
        ids_.emplace (id, sid_t (pe, pe -> tag (), vit_t (), pe -> uid (), pe -> hidden ())); }

bool ids_t::is_hidden (const ::std::string& id) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    return i -> second.hidden_; }

e_element ids_t::get_tag (const ::std::string& id) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    return i -> second.elem_; }

uid_t ids_t::get_uid (const ::std::string& id) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    return i -> second.uid_; }

bool ids_t::has_itemtype (const ::std::string& id, const itemtype_index s) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    if (i -> second.element_ != nullptr)
    {   for (auto t : i -> second.element_ -> own_itemtype ())
            if (t == s) return true; }
    else for (auto t : i -> second.types_)
        if (t == s) return true;
    return false; }

bool ids_t::has_itemtype (const ::std::string& id, const vit_t vit) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    if (i -> second.element_ != nullptr)
    {   for (auto t : i -> second.element_ -> own_itemtype ())
            for (auto it : vit)
                if (t == it) return true; }
    else for (auto t : i -> second.types_)
        for (auto it : vit)
            if (t == it) return true;
    return false; }

element* ids_t::get_element (const ::std::string& id) const
{   PRESUME (has_id (id), __FILE__, __LINE__);
    mif_t::const_iterator i = ids_.find (id);
    return i -> second.element_; }

void ids_t::cover_arse ()
{   for (auto id : ids_)
        if (id.second.element_ != nullptr)
        {   id.second.types_ = id.second.element_ -> own_itemtype ();
            id.second.element_ = nullptr; } }

bool ids_t::compatible_state (const ::std::string& id, const bool hidden)
{   return compatible_id_state (is_hidden (id), hidden); }

bool ids_t::compatible_category (const html_version& v, const element& e, const e_sought_category cat)
{   return e.fits_link_category (v, cat); }

bool compatible_id_state (const bool source, const bool target) noexcept
{   if (! target) return true;
    return (source); }

bool ids_t::is_good_id (element& e, const ::std::string& s, const e_category naughty_cat, const e_nit naughty_nit, const bool hidden_concern)
{   ids_t& ids (e.get_ids ());
    if (! ids.has_id (s))
    {   e.pick (naughty_nit, es_error, naughty_cat, "#", s, " doesn't exist"); return false; }
    if (hidden_concern && ! compatible_id_state (e.ancestral_attributes ().test (a_hidden), ids.is_hidden (s)))
    {   e.pick (nit_id_hidden, es_error, naughty_cat, "#", s, " is hidden"); return false; }
    const element* const pe = ids.get_element (s);
    VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
    if (! ids.compatible_category (e.node ().version (), *pe, e.link_category_sought ()))
    {   e.pick (nit_id_category, ed_svg_1_1, "17.1.4 Processing of IRI references", es_error, naughty_cat,
            "#", s, ": <", pe -> node ().id ().name (), "> is not a suitable target for <", e.node ().id ().name (), ">"); return false; }
    return true; }
