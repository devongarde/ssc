/*
ssc (static site checker)
File Info
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
#include "element/element.h"
#include "utility/byteorder.h"
#include "microdata/microdata_export.h"
#include "microformat/microformat_export.h"
#include "css/css.h"
#include "css/group.h"
#include "parser/parse_elements.h"
#include "stats/stats.h"
#include "parser/parse_ssi.h"
#include "ontology/ontology_version.h"
#include "webpage/fileindex.h"
#include "webpage/id.h"
#include "microdata/microdata_itemscope.h"
#include "spell/spell.h"
#include "spell/phrase.h"

class directory;
class url;

class page
{   ids_t ids_, names_, glyphs_;
    sstr_t access_, dfns_, parts_, profiles_;
    element* document_ = nullptr;
    elements_node nodes_;
    ::std::string name_;
    microdata_export md_export_;
    microformat_export mf_export_;
    const directory* directory_ = nullptr;
    bool has_title_ = false, style_css_ = true, check_links_ = true, snippet_ = false, outsider_ = false, dot_css_ = false, xxx_ = false;
    stats_t stats_;
    ssi_compedium ssi_;
    nitpick nits_;
    uid_t euid_ = 0;
    itemscope_ptr itemscope_;
    ::std::string lang_, charset_, title_, corpus_, keywords_, description_, author_, jsonld_;
    phrase phrase_;
    url base_;
    ustr_t abbrs_;
    ::std::time_t updated_ = 0;
    css_group css_;
    friend class tag;
    void init (const ::std::string& name, ::std::string& content, const fileindex_t x);
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (page);
    page (nitpick& nits, const ::std::string& name, const ::std::time_t updated, ::std::string& content, const directory* d = nullptr);
    page (const ::std::string& name, const ::std::time_t updated, ::std::string& content, const fileindex_t ndx, const directory* d = nullptr);
    explicit page (const ::std::string& content, const bool outsider = false);
    ~page () { cleanup (); }
    void swap (page& p);
    void cleanup () noexcept;
    nitpick& nits () noexcept { return nits_; }
    const nitpick& nits () const noexcept { return nits_; }
    bool parse (::std::string& content);
    bool invalid () const noexcept { return nodes_.invalid (); }
    bool check_links () const noexcept { return check_links_ && ! snippet_ && ! outsider_; }
    void check_links (const bool b) noexcept { check_links_ = b; }
    void examine ();
    ids_t& get_ids () noexcept { return ids_; }
    const ids_t& get_ids () const noexcept { return ids_; }
    ids_t& get_names () noexcept { return names_; }
    const ids_t& get_names () const noexcept { return names_; }
    ids_t& get_glyphs () noexcept { return glyphs_; }
    const ids_t& get_glyphs () const noexcept { return glyphs_; }
    bool verify_url (nitpick& nits, const ::std::string& s) const;
    const ::std::string name () const { return name_; }
    const ::std::string get_site_path () const;
    const ::boost::filesystem::path get_disk_path () const;
    const ::boost::filesystem::path get_disk_path (nitpick& nits, const url& u) const;
    const ::boost::filesystem::path get_export_path () const;
    void export_rel (const ::std::string& url, const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type)
    {   if (! snippet_) mf_export_.rel (url, hreflang, media, rels, text, title, type); }
    void export_item (const ::std::string& wo, const ::std::string& was)
    {   if (! snippet_) mf_export_.item (wo, was); }
    bool mf_write (const ::boost::filesystem::path& name)
    {   return snippet_ || mf_export_.write (nits_, name); }
    const html_version version () const noexcept { return nodes_.version (); }
    ::boost::filesystem::path absolute_member (nitpick& nits, const ::boost::filesystem::path& file) const;
    ::std::string load_url (nitpick& nits, const url& u, bool& borked) const;
    void confirm_title () noexcept { has_title_ = true; }
    void style_css (const bool b) noexcept { style_css_ = b; }
    bool style_css () const noexcept { return style_css_; }
    bool dot_css () const noexcept { return dot_css_; }
    css_group& css () { return css_; }
    const css_group& css () const { return css_; }
    ::std::string css_review (mmac_t& mac) const;
    bool charset_defined () const noexcept { return ! charset_.empty (); }
    const ::std::string& lang () const noexcept { return lang_; }
    void lang (nitpick& nits, const html_version& v, const ::std::string& l);
    const ::std::string& charset () const noexcept { return charset_; }
    void charset (nitpick& nits, const html_version& v, const ::std::string& cs);
    element* get_document () { return document_; }
    void mark (const e_element e)
    {   stats_.mark (e); }
    void visible (const e_element e)
    {   stats_.visible (e); }
    void mark_abbr (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_abbr (a, b); }
    void mark_custom_media (const ::std::string& str, const ::std::string& def)
    {   stats_.mark_custom_media (str, def); }
    void mark_dfn (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_dfn (a, b); }
    void mark_dtdd (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_dtdd (a, b); }
    void mark (const e_element f, const e_attribute m)
    {   stats_.mark (f, m); }
    void mark (const e_ontology_type s)
    {   stats_.mark (s); }
    void mark (const e_ontology_type s, const e_ontology_property p)
    {   stats_.mark (s, p); }
    void mark (const e_css_property s)
    {   stats_.mark (s); }
    void mark_meta (const e_httpequiv he)
    {   stats_.mark_meta (he); }
    void mark_meta (const e_metaname mn)
    {   stats_.mark_meta (mn); }
    void mark_meta (const e_metaname mn, const ::std::string& val)
    {   stats_.mark_meta (mn, val); }
    void dcl_class (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.dcl_class (s, n); }
    void dcl_custom_prop (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.dcl_custom_prop (s, n); }
    void dcl_id (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.dcl_id (s, n); }
    void dcl_element_class (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.dcl_element_class (s, n); }
    void dcl_element_id (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.dcl_element_id (s, n); }
    void mark_font (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.mark_font (s, n); }
    void mark_str (const e_gsstr gst, const ::std::string& s)
    {   stats_.mark_str (gst, s); }
    void merge_class (const smsid_t& s)
    {   stats_.merge_class (s); }
    void merge_custom_prop (const smsid_t& s)
    {   stats_.merge_custom_prop (s); }
    void merge_id (const smsid_t& s)
    {   stats_.merge_id (s); }
    void merge_element_class (const smsid_t& s)
    {   stats_.merge_element_class (s); }
    void merge_element_id (const smsid_t& s)
    {   stats_.merge_element_id (s); }
    void merge_font (const smsid_t& s)
    {   stats_.merge_font (s); }
    void use_class (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.use_class (s, n); }
    void use_custom_prop (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.use_custom_prop (s, n); }
    void use_id (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.use_id (s, n); }
    void use_element_class (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.use_element_class (s, n); }
    void use_element_id (const ::std::string& s, const ::std::size_t n = 1)
    {   stats_.use_element_id (s, n); }
    bool has_class (const ::std::string& s) const
    {   return stats_.has_class (s); }
    bool has_custom_media (const ::std::string& name) const
    {   return stats_.has_custom_media (name); }
    bool has_custom_prop (const ::std::string& s) const
    {   return stats_.has_custom_prop (s); }
    bool has_id (const ::std::string& s) const
    {   return stats_.has_id (s); }
    bool has_str (const e_gsstr g, const ::std::string& s) const
    {   return stats_.has_str (g, s); }
    void check_for_standard_classes (nitpick& nits, const html_version& v) const
    {   stats_.check_for_standard_classes (nits, v); }
    unsigned count (const e_element e) const
    {   return stats_.count (e); }
    unsigned visible_count (const e_element e) const
    {   return stats_.visible_count (e); }
    void lynx ();
    void shadow (nitpick& nits, const ::boost::filesystem::path& s);
    uid_t euid () noexcept;
    void itemscope (const itemscope_ptr itemscope);
    const itemscope_ptr itemscope () const noexcept { return itemscope_; }
    itemscope_ptr itemscope () noexcept { return itemscope_; }
    microdata_export* md_export () noexcept { return &md_export_; }
    ::std::string get_export_root () const;
    const directory* get_directory () const noexcept { return directory_; }
    void verify_locale (const ::boost::filesystem::path& p);
    void validate () { css_.validate (); }
    const ustr_t& abbrs () const noexcept { return abbrs_; }
    ustr_t& abbrs () noexcept { return abbrs_; }
    const sstr_t& dfns () const noexcept { return dfns_; }
    sstr_t& dfns () noexcept { return dfns_; }
    const sstr_t& parts () const noexcept { return parts_; }
    sstr_t& parts () noexcept { return parts_; }
    const sstr_t& profiles () const noexcept { return profiles_; }
    sstr_t& profiles () noexcept { return profiles_; }
    const url& base () const noexcept;
    void base (const url& u);
    ::std::string get_absolute_url (const ::std::string& s) const;
    ::std::string get_absolute_url () const { return get_absolute_url (name_); }
    void title (const ::std::string& s) { title_ = s; }
    bool corpus () const noexcept { return ! corpus_.empty (); }
    void corpus (const ::std::string& s) { corpus_ = s; }
    void keywords (const ::std::string& s) { keywords_ = s; }
    void description (const ::std::string& s) { description_ = s; }
    void author (const ::std::string& s) { author_ = s; }
    void note_lynx (const fileindex_t dependency)
    {   set_lynx (ids_.ndx (), dependency); }
    void add_depend (const fileindex_t dependency)
    {   add_dependency (ids_.ndx (), dependency); }
    void append_jsonld (const ::std::string& j);
    void phrasal (const lingo& lang, const ::std::string& s)
    {   phrase_.extend (lang, s); }
    void phrasal (nitpick& nits, const html_version& v)
    {   phrase_.complete (nits, v); }
    bool xxx () const { return xxx_; }
    ::std::string report (); };

::std::string get_page_url (const ::std::string& url);
