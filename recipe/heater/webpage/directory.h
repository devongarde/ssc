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
#include "utility/common.h"
#include "webpage/crosslink.h"
#include "webpage/root.h"
#include "element/state.h"

class external;
class url;
class directory;
typedef ::std::shared_ptr < directory > dir_ptr;
typedef ::std::vector < dir_ptr > vd_t;

class directory
{   typedef ::std::map < ::std::string, dir_ptr > map_t;
    typedef map_t::value_type value_t;
    ::std::string name_;
    map_t content_, priority_;
    bool offsite_ = false;
    directory* mummy_ = nullptr;
    path_root_ptr root_;
    fileindex_t ndx_ = nullfileindex;
    static external external_;
    bool add_to_content (nitpick* ticks, const ::boost::filesystem::directory_entry& i, const ::std::string& site);
    void maintain_fileindex (nitpick& nits, const ::boost::filesystem::path& p, const ::std::string& up, fileindex_t ndx, const fileindex_flags flags) const;
    void internal_get_disk_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    void internal_get_shadow_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    void internal_get_export_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    ::std::string internal_get_site_path (nitpick& nits, const ::std::string& item) const;
    bool verify_external (nitpick& nits, const html_version& v, const url& u) const;
    bool verify_local (nitpick& nits, const html_version& v, const url& u, const bool fancy = true) const;
    bool shadow_folder (nitpick& nits) const;
    bool shadow_file (nitpick& nits, const ::std::string& name) const;
    bool avoid_update (const ::boost::filesystem::path& original, const ::boost::filesystem::path& shadow, const bool page) const;
    bool avoid_update (const ::std::string& name, const bool page) const;
protected:
    directory (nitpick* ticks, const ::std::string& name, const fileindex_t ndx, directory* mummy, const ::std::string& site, const bool check = true);
public:
    explicit directory (const path_root_ptr& root, const short v);
    directory (const fileindex_t parent_ndx, const ::std::string& name, const bool offsite);
    void swap (directory& d) noexcept;
    bool is_root () const noexcept { return root_.get () != nullptr; }
    bool empty () const noexcept { return content_.empty (); }
    bool offsite () const noexcept { return offsite_; }
    bool scan (nitpick* ticks, const ::std::string& site);
    void examine (nitpick* ticks, dir_ptr me_me_me) const;
    void examine_page (nitpick* ticks, const ::std::string& file) const;
    uint64_t url_size (nitpick& nits, const url& u) const;
    ::std::time_t url_last_write_time (nitpick& nits, const url& u) const;
    ::std::string load_url (nitpick& nits, const url& u, ::std::time_t* updated = nullptr) const;
    bool verify_url (nitpick& nits, const html_version& v, const url& u, const bool fancy = true) const;
    bool integrate_virtual (const ::std::string& v, path_root_ptr& r, dir_ptr p);
    ::std::string get_site_path () const;
    ::std::string get_site_path (nitpick& nits, const ::std::string& item) const;
    fileindex_t get_ndx () const { return ndx_; }
    ::boost::filesystem::path get_disk_path (nitpick& nits, const url& u) const;
    ::boost::filesystem::path get_disk_path () const;
    ::boost::filesystem::path get_disk_path (nitpick& nits, const ::std::string& item) const;
    ::boost::filesystem::path get_export_path (nitpick& nits, const url& u) const;
    ::boost::filesystem::path get_export_path () const;
    ::boost::filesystem::path get_export_path (nitpick& nits, const ::std::string& item) const;
    ::boost::filesystem::path get_shadow_path () const; };

bool has_extension (const ::std::string& name, const vstr_t& extensions);
bool is_css (const ::std::string& name);
bool is_jsonld (const ::std::string& name);
bool is_webpage (const ::std::string& name);
bool is_verifiable_file (const ::std::string& name);
::std::size_t integrate_virtuals (paths_root& virt, vd_t& dirs);
