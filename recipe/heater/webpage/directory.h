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
#include "utility/common.h"
#include "css/css_cache.h"
#include "webpage/crosslink.h"
#include "webpage/root.h"
#include "element/state.h"

class external;
class url;
class directory;
typedef ::std::shared_ptr < directory > dir_ptr;
typedef ::std::vector < dir_ptr > vd_t;

class directory
{   typedef dir_ptr self_ptr;
    typedef ::std::map < ::std::string, self_ptr > map_t;
    typedef map_t::value_type value_t;
    ::std::string name_;
    map_t content_;
    bool offsite_ = false;
    directory* mummy_ = nullptr;
    path_root_ptr root_;
    fileindex_t ndx_ = nullfileindex;
    static external external_;
    bool add_to_content (nitpick& nits, const ::boost::filesystem::directory_entry& i, const ::std::string& site);
    bool unguarded_verify_url (nitpick& nits, const html_version& v, const url& u) const;
    void internal_get_disk_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    void internal_get_shadow_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    void internal_get_export_path (const ::std::string& item, ::boost::filesystem::path& res) const;
    ::std::string internal_get_site_path (nitpick& nits, const ::std::string& item) const;
    bool shadow_folder (nitpick& nits);
    bool shadow_file (nitpick& nits, const ::std::string& name, sstr_t& shadowed);
    bool avoid_update (const ::boost::filesystem::path& original, const ::boost::filesystem::path& shadow, const bool page);
    bool avoid_update (const ::std::string& name, const bool page);
protected:
    directory (nitpick& nits, const ::std::string& name, const fileindex_t ndx, directory* mummy, const ::std::string& site, const bool check = true);
public:
    explicit directory (const path_root_ptr& root);
    directory (const ::std::string& name, const bool offsite);
    void swap (directory& d) noexcept;
    bool is_root () const noexcept { return root_.get () != nullptr; }
    bool empty () const noexcept { return content_.empty (); }
    bool offsite () const noexcept { return offsite_; }
    bool scan (nitpick& nits, const ::std::string& site);
    void examine (nitpick& nits);
    uint64_t url_size (nitpick& nits, const url& u) const;
    ::std::time_t url_last_write_time (nitpick& nits, const url& u) const;
    ::std::string load_url (nitpick& nits, const url& u, ::std::time_t* updated = nullptr) const;
    bool verify_url (nitpick& nits, const html_version& v, const url& u) const;
    bool verify_external (nitpick& nits, const html_version& v, const url& u) const;
    bool integrate_virtual (const ::std::string& v, path_root_ptr& r, dir_ptr p);
    ::std::string get_site_path () const;
    ::std::string get_site_path (nitpick& nits, const ::std::string& item) const;
    ::boost::filesystem::path get_disk_path (nitpick& nits, const url& u) const;
    ::boost::filesystem::path get_disk_path () const;
    ::boost::filesystem::path get_disk_path (nitpick& nits, const ::std::string& item) const;
    ::boost::filesystem::path get_export_path (nitpick& nits, const url& u) const;
    ::boost::filesystem::path get_export_path () const;
    ::boost::filesystem::path get_export_path (nitpick& nits, const ::std::string& item) const;
    ::boost::filesystem::path get_shadow_path () const; };

bool is_webpage (const ::std::string& name, const vstr_t& extensions);
::std::size_t integrate_virtuals (paths_root& virt, vd_t& dirs);
