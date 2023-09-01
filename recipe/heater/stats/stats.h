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
#include "element/elem.h"
#include "attribute/attr.h"
#include "parser/html_version.h"
#include "main/output.h"

class stats;

class stats_t
{   typedef ::std::shared_ptr < stats > stats_ptr;
    stats_ptr p_;
public:
    stats_t ();
    DEFAULT_COPY_CONSTRUCTORS (stats_t);
    ~stats_t () = default;
    void swap (stats_t& s) noexcept
    {   p_.swap (s.p_); }
    void dcl_class (const ::std::string& s, const ::std::size_t n = 1);
    void dcl_id (const ::std::string& s, const ::std::size_t n = 1);
    void dcl_element_class (const ::std::string& s, const ::std::size_t n = 1);
    void dcl_element_id (const ::std::string& s, const ::std::size_t n = 1);
    void mark (const e_element e);
    void mark_abbr (const ::std::string& a, const ::std::string& b);
    void mark_dfn (const ::std::string& a, const ::std::string& b);
    void mark_dtdd (const ::std::string& a, const ::std::string& b);
    void mark (const html_version& v);
    void mark (const e_severity s, const unsigned n = 1);
    void mark (const e_category c, const unsigned n = 1);
    void mark (const e_doc d, const unsigned n = 1);
    void mark (const e_element f, const e_attribute m);
    void mark (const e_ontology_type s);
    void mark (const e_ontology_type s, const e_ontology_property p);
    void mark (const e_css_property p);
    void mark (const e_css_statement s);
    void mark_custom_prop (const ::std::string& s, const ::std::size_t n = 1);
    void mark_file (const unsigned size);
    void mark_font (const ::std::string& s, const ::std::size_t n = 1);
    void mark_meta (const e_httpequiv he);
    void mark_meta (const e_metaname mn);
    void mark_meta (const e_metaname mn, const ::std::string& val);
    void use_class (const ::std::string& s, const ::std::size_t n = 1);
    void use_id (const ::std::string& s, const ::std::size_t n = 1);
    void use_element_class (const ::std::string& s, const ::std::size_t n = 1);
    void use_element_id (const ::std::string& s, const ::std::size_t n = 1);
    void visible (const e_element e);
    bool has_class (const ::std::string& s) const;
    bool has_id (const ::std::string& s) const;
    void merge_class (const smsid_t& s);
    void merge_id (const smsid_t& s);
    void merge_element_class (const smsid_t& s);
    void merge_element_id (const smsid_t& s);
    void merge_font (const smsid_t& s);
    uint64_t file_count () const;
    unsigned count (const e_element e) const;
    unsigned count (const e_severity s) const;
    unsigned visible_count (const e_element e) const;
    void check_for_standard_classes (nitpick& nits, const html_version& v) const;
    bool severity_exceeded () const;
    void accumulate () const;
    void accumulate (const stats_t& s) const;
    ::std::string class_and_id_report () const;
    ::std::string report (const bool grand) const; };

extern stats_t overall;

inline void report_global_stats (const bool grand)
{   outstr.out (overall.report (grand)); }
