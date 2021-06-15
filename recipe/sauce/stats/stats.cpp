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
    VERIFY_NOT_NULL (p_, __FILE__, __LINE__); }

stats_t::~stats_t () { delete p_; }

void stats_t::mark (const e_element e)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (e); }

void stats_t::visible (const e_element e)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> visible (e); }

void stats_t::mark_abbr (const ::std::string& a, const ::std::string& b)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_abbr (a, b); }

void stats_t::mark_dfn (const ::std::string& a, const ::std::string& b)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_dfn (a, b); }

void stats_t::mark_dtdd (const ::std::string& a, const ::std::string& b)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_dtdd (a, b); }

void stats_t::mark (const e_severity s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (s); }

void stats_t::mark (const e_category c)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (c); }

void stats_t::mark (const e_doc d)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (d); }

void stats_t::mark (const html_version& v)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (v); }

void stats_t::mark (const e_element f, const e_attribute m)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (f, m); }

void stats_t::mark (const e_schema_type s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (s); }

void stats_t::mark (const e_schema_type s, const e_schema_property p)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (s, p); }

void stats_t::mark_file (const unsigned size)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_file (size); }

void stats_t::mark_meta (const e_httpequiv he)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_meta (he); }

void stats_t::mark_meta (const e_metaname mn)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_meta (mn); }

void stats_t::mark_meta (const e_metaname mn, const ::std::string& val)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark_meta (mn, val); }

::std::string stats_t::report (const bool grand) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> report (grand); }

uint64_t stats_t::file_count () const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> file_count (); }

unsigned stats_t::count (const e_element e) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> element_count (e); }

unsigned stats_t::count (const e_severity s) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> severity_count (s); }

unsigned stats_t::visible_count (const e_element e) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> visible_count (e); }
