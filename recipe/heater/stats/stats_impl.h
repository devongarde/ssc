/*
ssc (static site checker)
File Info
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
#include "stats/stats5.h"
#include "stats/stats6.h"
#include "parser/html_version.h"

class stats
{   element_stats element_, visible_;
    term_stats dfn_, abbr_, dtdd_, custom_media_;
    severity_stats severity_;
    category_stats category_;
    ref_stats ref_;
    version_stats version_;
    attribute_stats attribute_;
    ontology_stats ontology_;
    ontology_property_stats ontology_property_;
    httpequiv_stats httpequiv_;
    metaname_stats metaname_;
    meta_value_stats meta_value_;
    css_property_stats css_property_;
    css_statement_stats css_statement_;
    smsid_stats dcl_class_, dcl_custom_prop_, dcl_id_, dcl_element_class_, dcl_element_id_, font_,
                use_class_, use_custom_prop_, use_id_, use_element_class_, use_element_id_;
    vs6_stats str_ = vs6_stats (gst_max);
    uint64_t file_count_ = 0;
    unsigned smallest_ = UINT_MAX;
    unsigned biggest_ = 0;
    double file_size_ = 0.0;
    ::std::string single_usage (const ::std::string name, const ::std::size_t dn, const ::std::size_t un,
        e_nit_section sc = ns_tally, e_nit_macro n = nm_tally_name, e_nit_macro i1 = nm_tally_int,
        e_nit_macro i2 = nm_tally_use_int, e_nit_macro c1 = nm_tally_count, e_nit_macro c2 = nm_tally_use_count) const;
    ::std::string report_usage (const ::std::string& category, const smsid_stats& sum) const;
    ::std::string report_usage (const ::std::string& category, const smsid_stats& dcl, const smsid_stats& used,
        e_nit_section sc = ns_tally, e_nit_section h = ns_tally_head, e_nit_section f = ns_tally_foot,
        e_nit_macro n = nm_tally_name, e_nit_macro i1 = nm_tally_int,
        e_nit_macro i2 = nm_tally_use_int, e_nit_macro c1 = nm_tally_count, e_nit_macro c2 = nm_tally_use_count,
        e_nit_macro ttl = nm_tally_title, e_nit_macro t1 = nm_tally_total, e_nit_macro t2 = nm_tally_use_total,
        e_nit_macro sum1 = nm_tally_sum, e_nit_macro sum2 = nm_tally_use_sum) const;
    ::std::string abbr_report () const;
    ::std::string category_report () const;
    ::std::string class_report () const;
    ::std::string class_report2 () const;
    ::std::string css_str_report (const e_gsstr gst) const;
    ::std::string custom_media_report () const;
    ::std::string custom_property_report () const;
    ::std::string definition_report () const;
    ::std::string value_pair_report () const;
    ::std::string element_report () const;
    ::std::string error_report () const;
    ::std::string file_report () const;
    ::std::string font_report () const;
    ::std::string id_report () const;
    ::std::string id_report2 () const;
    ::std::string itemid_report () const;
    ::std::string meta_report () const;
    ::std::string ontology_report () const;
    ::std::string property_report () const;
    ::std::string reference_report () const;
    ::std::string statement_report () const;
    ::std::string version_report () const;
public:
    void dcl_class (const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_class_.mark (s, n); }
    void dcl_custom_prop (const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_custom_prop_.mark (s, n); }
    void dcl_id (const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_id_.mark (s, n); }
    void dcl_element_class (const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_element_class_.mark (s, n); }
    void dcl_element_id (const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_element_id_.mark (s, n); }
    void mark (const e_element e)
    {   element_.mark (e); }
    void mark_abbr (const ::std::string& a, const ::std::string& b)
    {   abbr_.mark (tart (a), tart (b)); }
    void mark_custom_media (const ::std::string& str, const ::std::string& def)
    {   custom_media_.mark (tart (str), tart (def)); }
    void mark_dfn (const ::std::string& a, const ::std::string& b)
    {   dfn_.mark (tart (a), tart (b)); }
    void mark_dtdd (const ::std::string& a, const ::std::string& b)
    {   dtdd_.mark (tart (a), tart (b)); }
    void mark (const e_severity s, const unsigned n = 1)
    {   severity_.mark (s, n); }
    void mark (const e_category c, const unsigned n = 1)
    {   category_.mark (c, n); }
    void mark (const html_version& v)
    {   version_.mark (v); }
    void mark (const e_doc d, const unsigned n = 1)
    {   ref_.mark (d, n); }
    void mark (const e_element f, const e_attribute m)
    {   attribute_.mark (f, m); }
    void mark (const e_ontology_type s)
    {   ontology_.mark (s); }
    void mark (const e_ontology_type s, const e_ontology_property p)
    {   ontology_property_.mark (s, p); }
    void mark (const e_css_property p)
    {   css_property_.mark (p); }
    void mark (const e_css_statement s)
    {   css_statement_.mark (s); }
    void mark_meta (const e_metaname mn, const ::std::string& val)
    {   meta_value_.mark (mn, tart (val)); }
    void mark_file (const unsigned size) noexcept;
    void mark_font (const ::std::string& s, const ::std::size_t n = 1)
    {   font_.mark (s, n); }
    void mark_meta (const e_httpequiv he)
    {   httpequiv_.mark (he); }
    void mark_meta (const e_metaname mn)
    {   metaname_.mark (mn); }
    void mark_str (const e_gsstr gst, const ::std::string& s)
    {   str_.at (gst).mark (s); }
    void use_class (const ::std::string& s, const ::std::size_t n = 1)
    {   use_class_.mark (s, n); }
    void use_custom_prop (const ::std::string& s, const ::std::size_t n = 1)
    {   use_custom_prop_.mark (s, n); }
    void use_id (const ::std::string& s, const ::std::size_t n = 1)
    {   use_id_.mark (s, n); }
    void use_element_class (const ::std::string& s, const ::std::size_t n = 1)
    {   use_element_class_.mark (s, n); }
    void use_element_id (const ::std::string& s, const ::std::size_t n = 1)
    {   use_element_id_.mark (s, n); }
    void visible (const e_element e)
    {   visible_.mark (e); }
    bool has_class (const ::std::string& s) const
    {   return dcl_class_.at (s) > 0; }
    bool has_custom_media (const ::std::string& name) const
    {   return custom_media_.exists (name); }
    bool has_custom_prop (const ::std::string& s) const
    {   return dcl_custom_prop_.at (s) > 0; }
    bool has_id (const ::std::string& s) const
    {   return dcl_id_.at (s) > 0; }
    bool has_str (const e_gsstr g, const ::std::string& s) const
    {   return str_.at (g).find (s) != str_.at (g).cend (); }
    void merge_class (const smsid_t& s) { dcl_class_.merge (s); }
    void merge_custom_prop (const smsid_t& s) { dcl_custom_prop_.merge (s); }
    void merge_id (const smsid_t& s) { dcl_id_.merge (s); }
    void merge_element_class (const smsid_t& s) { dcl_element_class_.merge (s); }
    void merge_element_id (const smsid_t& s) { dcl_element_id_.merge (s); }
    void merge_font (const smsid_t& s) { font_.merge (s); }
    uint64_t file_count () const noexcept
    {   return file_count_; }
    unsigned element_count (const e_element e) const
    {   return element_.at (e); }
    unsigned severity_count (const e_severity s) const
    {   return severity_.at (s); }
    unsigned visible_count (const e_element e) const
    {   return visible_.at (e); }
    void check_for_standard_classes (nitpick& nits, const html_version& v) const;
    bool severity_exceeded () const;
    void accumulate (stats& o) const;
    ::std::string class_and_id_report () const;
    ::std::string report (const bool grand) const; };
