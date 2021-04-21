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

#pragma once
#include "element/element.h"
#include "utility/byteorder.h"
#include "microdata/microdata_export.h"
#include "microformat/microformat_export.h"
#include "css/css.h"
#include "parser/parse_elements.h"
#include "stats/stats.h"
#include "parser/parse_ssi.h"
#include "schema/schema_version.h"
#include "webpage/fileindex.h"
#include "webpage/id.h"
#include "microdata/microdata_itemscope.h"

class directory;

class page
{   ids_t ids_, names_;
    sstr_t access_;
    element_ptr document_;
    elements_node nodes_;
    ::std::string name_;
    microdata_export md_export_;
    microformat_export mf_export_;
    directory* directory_ = nullptr;
    bool has_title_ = false;
    bool style_css_ = true;
    bool check_links_ = true;
    bool snippet_ = false;
    stats_t stats_;
    schema_version schema_version_;
    ssi_compedium ssi_;
    nitpick nits_;
    uid_t euid_ = 0;
    itemscope_ptr itemscope_;
    ::std::string lang_, charset_, title_, corpus_, keywords_, description_, author_;
    sstr_t dfns_;
    ustr_t abbrs_;
    ::std::time_t updated_ = 0;
    friend class tag;
public:
    page () = delete;
    page (nitpick& nits, const ::std::string& name, const ::std::time_t updated, ::std::string& content, directory* d = nullptr, const e_charcode encoding = cc_ansi);
    page (const ::std::string& name, const ::std::time_t updated, ::std::string& content, const fileindex_t ndx, directory* d = nullptr, const e_charcode encoding = cc_ansi);
    explicit page (const ::std::string& content, const e_charcode encoding = cc_ansi);
    page (const page& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    page (page&& ) = default;
#endif
    page& operator = (const page& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    page& operator = (page&& ) = default;
#endif
    ~page () = default;
    void swap (page& p) NOEXCEPT;
    void reset (const page& p);
    nitpick& nits () { return nits_; }
    const nitpick& nits () const { return nits_; }
    bool parse (::std::string& content, const e_charcode encoding = cc_ansi);
    bool invalid () const { return nodes_.invalid (); }
    bool check_links () const { return check_links_ && ! snippet_; }
    void check_links (const bool b) { check_links_ = b; }
    void examine ();
    ::std::string find_webmention () const;
    ::std::string find_mention_info (const url& u, bool text, bool anything);
    ids_t& get_ids () { return ids_; }
    const ids_t& get_ids () const { return ids_; }
    ids_t& get_names () { return names_; }
    const ids_t& get_names () const { return names_; }
    bool verify_url (nitpick& nits, const ::std::string& s) const;
    const ::std::string name () const { return name_; }
    const ::std::string get_site_path () const;
    const ::boost::filesystem::path get_disk_path () const;
    const ::boost::filesystem::path get_export_path () const;
    void export_rel (const ::std::string& url, const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type)
    {   if (! snippet_) mf_export_.rel (url, hreflang, media, rels, text, title, type); }
    void export_item (const ::std::string& wo, const ::std::string& was)
    {   if (! snippet_) mf_export_.item (wo, was); }
    bool mf_write (const ::boost::filesystem::path& name)
    {   return snippet_ || mf_export_.write (nits_, name); }
    const html_version version () const { return nodes_.version (); }
    const schema_version schema_ver () const { return schema_version_; }
    void schema_ver (const schema_version& v) { schema_version_ = v; }
    ::boost::filesystem::path absolute_member (nitpick& nits, const ::boost::filesystem::path& file) const;
    ::std::string load_url (nitpick& nits, const url& u) const;
    void confirm_title () { has_title_ = true; }
    void style_css (const bool b) { style_css_ = b; }
    bool style_css () const { return style_css_; }
    bool charset_defined () const { return ! charset_.empty (); }
    const ::std::string& lang () const { return lang_; }
    void lang (nitpick& nits, const html_version& v, const ::std::string& l);
    const ::std::string& charset () const { return charset_; }
    void charset (nitpick& nits, const html_version& v, const ::std::string& cs);
    void mark (const e_element e)
    {   stats_.mark (e);
        context.mark (e); }
    void visible (const e_element e)
    {   stats_.visible (e);
        context.visible (e); }
    void mark_abbr (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_abbr (a, b);
        context.mark_abbr (a, b); }
    void mark_dfn (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_dfn (a, b);
        context.mark_dfn (a, b); }
    void mark_dtdd (const ::std::string& a, const ::std::string& b)
    {   stats_.mark_dtdd (a, b);
        context.mark_dtdd (a, b); }
    void mark (const e_element f, const e_attribute m)
    {   stats_.mark (f, m);
        context.mark (f, m); }
    void mark (const e_schema_type s)
    {   stats_.mark (s);
        context.mark (s); }
    void mark (const e_schema_type s, const e_schema_property p)
    {   stats_.mark (s, p);
        context.mark (s, p); }
    void mark_meta (const e_httpequiv he)
    {   stats_.mark_meta (he);
        context.mark_meta (he); }
    void mark_meta (const e_metaname mn)
    {   stats_.mark_meta (mn);
        context.mark_meta (mn); }
    void mark_meta (const e_metaname mn, const ::std::string& val)
    {   stats_.mark_meta (mn, val);
        context.mark_meta (mn, val); }
    unsigned count (const e_element e) const
    {   return stats_.count (e); }
    unsigned visible_count (const e_element e) const
    {   return stats_.visible_count (e); }
    void lynx ();
    void shadow (nitpick& nits, const ::boost::filesystem::path& s);
    uid_t euid ();
    void itemscope (const itemscope_ptr itemscope);
    const itemscope_ptr itemscope () const { return itemscope_; }
    itemscope_ptr itemscope () { return itemscope_; }
    microdata_export* md_export () { return &md_export_; }
    ::std::string get_export_root () const;
    const directory* get_directory () const { return directory_; }
    void verify_locale (const ::boost::filesystem::path& p);
    const ustr_t& abbrs () const { return abbrs_; }
    ustr_t& abbrs () { return abbrs_; }
    const sstr_t& dfns () const { return dfns_; }
    sstr_t& dfns () { return dfns_; }
    void title (const ::std::string& s) { title_ = s; }
    void corpus (const ::std::string& s) { corpus_ = s; }
    void keywords (const ::std::string& s) { keywords_ = s; }
    void description (const ::std::string& s) { description_ = s; }
    void author (const ::std::string& s) { author_ = s; }
    ::std::string report (); };

::std::string get_page_url (const ::std::string& url);
