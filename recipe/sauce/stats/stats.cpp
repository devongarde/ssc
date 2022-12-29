/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

stats_t overall;

stats_t::stats_t ()
{   p_ = stats_ptr (new stats);
    VERIFY_NOT_NULL (p_, __FILE__, __LINE__); }

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

void stats_t::mark (const e_severity s, const unsigned n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (s, n); }

void stats_t::mark (const e_category c, const unsigned n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (c, n); }

void stats_t::mark (const e_doc d, const unsigned n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (d, n); }

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

void stats_t::mark (const e_css_property p)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (p); }

void stats_t::mark (const e_css_statement s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> mark (s); }

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

void stats_t::dcl_class (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> dcl_class (s, n); }

void stats_t::dcl_id (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> dcl_id (s, n); }

void stats_t::dcl_element_class (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> dcl_element_class (s, n); }

void stats_t::dcl_element_id (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> dcl_element_id (s, n); }

void stats_t::mark_font (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> mark_font (s, n); }

void stats_t::merge_class (const smsid_t& s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> merge_class (s); }

void stats_t::merge_id (const smsid_t& s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> merge_id (s); }

void stats_t::merge_element_class (const smsid_t& s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> merge_element_class (s); }

void stats_t::merge_element_id (const smsid_t& s)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> merge_element_id (s); }

void stats_t::use_class (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> use_class (s, n); }

void stats_t::use_id (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> use_id (s, n); }

void stats_t::use_element_class (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> use_element_class (s, n); }

void stats_t::use_element_id (const ::std::string& s, const ::std::size_t n)
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> use_element_id (s, n); }

bool stats_t::has_class (const ::std::string& s) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> has_class (s); }

bool stats_t::has_id (const ::std::string& s) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> has_id (s); }

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

bool stats_t::severity_exceeded () const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    return p_ -> severity_exceeded (); }

void stats_t::check_for_standard_classes (nitpick& nits, const html_version& v) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    p_ -> check_for_standard_classes (nits, v); }

void stats_t::accumulate () const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    VERIFY_NOT_NULL (overall.p_, __FILE__, __LINE__);
    p_ -> accumulate (*overall.p_); }

void stats_t::accumulate (stats_t& s) const
{   VERIFY_NOT_NULL (p_, __FILE__, __LINE__);
    VERIFY_NOT_NULL (s.p_, __FILE__, __LINE__);
    p_ -> accumulate (*s.p_); }
