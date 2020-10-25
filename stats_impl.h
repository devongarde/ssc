/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "stats0.h"
#include "stats1.h"
#include "stats2.h"
#include "html_version.h"

typedef stats0 < html_version > version_stats;
typedef stats1 < e_element, last_element_tag, elem_undefined > element_stats;
typedef stats1 < e_category, last_category, ec_undefined > category_stats;
typedef stats1 < e_severity, last_severity, es_undefined > severity_stats;
typedef stats1 < e_doc, last_doc, ed_mishmash > ref_stats;
typedef stats2 < e_element, e_attribute, last_element_tag, last_attribute > attribute_stats;
typedef stats1 < e_schema, sch_illegal, sch_context > schema_stats;
typedef stats2 < e_schema, e_schema_property, sch_illegal, sp_illegal > schema_property_stats;

class stats
{   element_stats element_;
    severity_stats severity_;
    category_stats category_;
    ref_stats ref_;
    version_stats version_;
    attribute_stats attribute_;
    schema_stats schema_;
    schema_property_stats schema_property_;
    uint64_t file_count_ = 0;
    unsigned smallest_ = UINT_MAX;
    unsigned biggest_ = 0;
    double file_size_ = 0.0;
    ::std::string times (const uint64_t n) const;
    ::std::string saybe (const unsigned n, const ::std::string& msg) const;
    ::std::string microdata_report () const;
    ::std::string element_report () const;
    ::std::string version_report () const;
    ::std::string error_report () const;
    ::std::string category_report () const;
    ::std::string file_report () const;
    ::std::string reference_report () const;
public:
    void mark (const e_element e)
    {   element_.mark (e); }
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
    void mark (const e_schema s)
    {   schema_.mark (s); }
    void mark (const e_schema s, const e_schema_property p)
    {   schema_property_.mark (s, p); }
    void mark_file (const unsigned size);
    uint64_t file_count () const
    {   return file_count_; }
    unsigned element_count (const e_element e) const
    {   return element_.at (e); }
    ::std::string report (const bool grand) const; };

