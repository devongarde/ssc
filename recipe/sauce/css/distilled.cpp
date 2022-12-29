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

#include "main/standard.h"
#include "css/distilled.h"
#include "utility/common.h"
#include "element/elem.h"
#include "stats/stats.h"

void distilled::swap (distilled& cp) noexcept
{   ::std::swap (in_progress_, cp.in_progress_);
    class_.swap (cp.class_);
    id_.swap (cp.id_);
    element_class_.swap (cp.element_class_);
    element_id_.swap (cp.element_id_); }

void distilled::merge (const distilled& cp)
{   merge_smsid (class_, cp.class_);
    merge_smsid (id_, cp.id_);
    merge_smsid (element_class_, cp.element_class_);
    merge_smsid (element_id_, cp.element_id_); }

void distilled::insert_class (const ::std::string& s, const int n)
{   class_.emplace (s, n); }

void distilled::insert_id (const ::std::string& s, const int n)
{   id_.emplace (s, n); }

void distilled::insert_element_class (const ::std::string& s, const int n)
{   element_class_.emplace (s, n); }

bool distilled::has_element_class (const e_element e, const ::std::string& s)
{   ::std::string l (elem::name (e) + "." + s);
    return (element_class_.find (l) != element_class_.cend ()); }

void distilled::insert_element_id (const ::std::string& s, const int n)
{   element_id_.emplace (s, n); }

bool distilled::has_element_id (const e_element e, const ::std::string& s)
{   ::std::string l (elem::name (e) + "#" + s);
    return (element_id_.find (l) != element_id_.cend ()); }

void distilled::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto c : class_)
        s -> dcl_class (c.first, c.second);
    for (auto c : id_)
        s -> dcl_id (c.first, c.second);
    for (auto c : element_class_)
        s -> dcl_element_class (c.first, c.second);
    for (auto c : element_id_)
        s -> dcl_element_id (c.first, c.second); }
