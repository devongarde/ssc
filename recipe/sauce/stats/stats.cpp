/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "stats/stats.h"
#include "stats/stats_impl.h"

stats_t::stats_t ()
{   p_ = new stats;
    DBG_ASSERT (p_ != nullptr); }

stats_t::~stats_t () { delete p_; }

void stats_t::mark (const e_element e)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (e); }

void stats_t::visible (const e_element e)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> visible (e); }

void stats_t::mark_abbr (const ::std::string& a, const ::std::string& b)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_abbr (a, b); }

void stats_t::mark_dfn (const ::std::string& a, const ::std::string& b)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_dfn (a, b); }

void stats_t::mark_dtdd (const ::std::string& a, const ::std::string& b)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_dtdd (a, b); }

void stats_t::mark (const e_severity s)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (s); }

void stats_t::mark (const e_category c)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (c); }

void stats_t::mark (const e_doc d)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (d); }

void stats_t::mark (const html_version& v)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (v); }

void stats_t::mark (const e_element f, const e_attribute m)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (f, m); }

void stats_t::mark (const e_schema_type s)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (s); }

void stats_t::mark (const e_schema_type s, const e_schema_property p)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark (s, p); }

void stats_t::mark_file (const unsigned size)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_file (size); }

void stats_t::mark_meta (const e_httpequiv he)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_meta (he); }

void stats_t::mark_meta (const e_metaname mn)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_meta (mn); }

void stats_t::mark_meta (const e_metaname mn, const ::std::string& val)
{   DBG_ASSERT (p_ != nullptr);
    p_ -> mark_meta (mn, val); }

::std::string stats_t::report (const bool grand) const
{   DBG_ASSERT (p_ != nullptr);
    return p_ -> report (grand); }

uint64_t stats_t::file_count () const
{   DBG_ASSERT (p_ != nullptr);
    return p_ -> file_count (); }

unsigned stats_t::count (const e_element e) const
{   DBG_ASSERT (p_ != nullptr);
    return p_ -> element_count (e); }

unsigned stats_t::visible_count (const e_element e) const
{   DBG_ASSERT (p_ != nullptr);
    return p_ -> visible_count (e); }
