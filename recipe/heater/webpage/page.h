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
#include "symbol/symbol_table.h"
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
{   ids_t ids_;
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
    stats_t stats_;
    schema_version schema_version_;
    ssi_compedium ssi_;
    nitpick nits_;
    uid_t euid_ = 0;
    itemscope_ptr itemscope_;
    ::std::string lang_, charset_;
    friend class tag;
public:
    page () = delete;
    page (nitpick& nits, const ::std::string& name, ::std::string& content, directory* d = nullptr, const e_charcode encoding = cc_ansi);
    page (const ::std::string& name, ::std::string& content, const fileindex_t ndx, directory* d = nullptr, const e_charcode encoding = cc_ansi);
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
    bool check_links () const { return check_links_; }
    void check_links (const bool b) { check_links_ = b; }
    void examine (const directory& d);
    ::std::string find_webmention () const;
    ::std::string find_mention_info (const url& u, bool text, bool anything);
    bool verify_url (nitpick& nits, const ::std::string& s, const attribute_bitset& state, const vit_t& itemtypes) const;
    const ::std::string name () const { return name_; }
    const ::std::string get_site_path () const;
    const ::boost::filesystem::path get_disk_path () const;
    const ::boost::filesystem::path get_export_path () const;
    void export_rel (const ::std::string& url, const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type)
    {   mf_export_.rel (url, hreflang, media, rels, text, title, type); }
    void export_item (const ::std::string& wo, const ::std::string& was)
    {   mf_export_.item (wo, was); }
    bool mf_write (const ::boost::filesystem::path& name)
    {   return mf_export_.write (nits_, name); }
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
    void mark (const e_element f, const e_attribute m)
    {   stats_.mark (f, m);
        context.mark (f, m); }
    void mark (const e_schema s)
    {   stats_.mark (s);
        context.mark (s); }
    void mark (const e_schema s, const e_schema_property p)
    {   stats_.mark (s, p);
        context.mark (s, p); }
    unsigned count (const e_element e) const
    {   return stats_.count (e); }
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
    ::std::string report (); };

::std::string get_page_url (const ::std::string& url);
