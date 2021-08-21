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

#pragma once
#include "stats/stats0.h"
#include "stats/stats1.h"
#include "stats/stats2.h"
#include "stats/stats3.h"
#include "stats/stats4.h"
#include "parser/html_version.h"

typedef stats0 < html_version > version_stats;
typedef stats4 < ::std::string > term_stats;
typedef stats1 < e_element, last_element_tag, elem_undefined > element_stats;
typedef stats1 < e_category, last_category, ec_undefined > category_stats;
typedef stats1 < e_severity, last_severity, es_undefined > severity_stats;
typedef stats1 < e_doc, last_doc, ed_mishmash > ref_stats;
typedef stats2 < e_element, e_attribute, last_element_tag, last_attribute > attribute_stats;
typedef stats1 < e_schema_type, sty_illegal, sty_context > schema_stats;
typedef stats2 < e_schema_type, e_schema_property, sty_illegal, sp_illegal > schema_property_stats;
typedef stats1 < e_httpequiv, he_error, he_context > httpequiv_stats;
typedef stats1 < e_metaname, mn_illegal, mn_context > metaname_stats;
typedef stats3 < ::std::string, e_metaname, mn_illegal, mn_context > meta_value_stats;

class stats
{   element_stats element_, visible_;
    term_stats dfn_, abbr_, dtdd_;
    severity_stats severity_;
    category_stats category_;
    ref_stats ref_;
    version_stats version_;
    attribute_stats attribute_;
    schema_stats schema_;
    schema_property_stats schema_property_;
    httpequiv_stats httpequiv_;
    metaname_stats metaname_;
    meta_value_stats meta_value_;
    uint64_t file_count_ = 0;
    unsigned smallest_ = UINT_MAX;
    unsigned biggest_ = 0;
    double file_size_ = 0.0;
    ::std::string times (const uint64_t n) const;
    ::std::string saybe (const unsigned n, const ::std::string& msg) const;
    ::std::string ontology_report () const;
    ::std::string element_report () const;
    ::std::string version_report () const;
    ::std::string abbr_report () const;
    ::std::string dfn_report () const;
    ::std::string dtdd_report () const;
    ::std::string error_report () const;
    ::std::string category_report () const;
    ::std::string file_report () const;
    ::std::string reference_report () const;
    ::std::string meta_report () const;
public:
    void mark (const e_element e)
    {   element_.mark (e); }
    void visible (const e_element e)
    {   visible_.mark (e); }
    void mark_abbr (const ::std::string& a, const ::std::string& b)
    {   abbr_.mark (tart (a), tart (b)); }
    void mark_dfn (const ::std::string& a, const ::std::string& b)
    {   dfn_.mark (tart (a), tart (b)); }
    void mark_dtdd (const ::std::string& a, const ::std::string& b)
    {   dtdd_.mark (tart (a), tart (b)); }
    void mark (const e_severity s)
    {   severity_.mark (s); }
    void mark (const e_category c)
    {   category_.mark (c); }
    void mark (const html_version& v)
    {   version_.mark (v); }
    void mark (const e_doc d)
    {   ref_.mark (d); }
    void mark (const e_element f, const e_attribute m)
    {   attribute_.mark (f, m); }
    void mark (const e_schema_type s)
    {   schema_.mark (s); }
    void mark (const e_schema_type s, const e_schema_property p)
    {   schema_property_.mark (s, p); }
    void mark_meta (const e_httpequiv he)
    {   httpequiv_.mark (he); }
    void mark_meta (const e_metaname mn)
    {   metaname_.mark (mn); }
    void mark_meta (const e_metaname mn, const ::std::string& val)
    {   meta_value_.mark (mn, tart (val)); }
    void mark_file (const unsigned size);
    uint64_t file_count () const
    {   return file_count_; }
    unsigned element_count (const e_element e) const
    {   return element_.at (e); }
    unsigned severity_count (const e_severity s) const
    {   return severity_.at (s); }
    unsigned visible_count (const e_element e) const
    {   return visible_.at (e); }
    ::std::string report (const bool grand) const; };

