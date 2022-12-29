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
#include "feedback/nitpick.h"
#include "webpage/fileindex.h"

class path_root
{   ::boost::filesystem::path disk_path_, shadow_, export_;
    ::std::string site_path_;
    fileindex_t ndx_ = nullfileindex;
    ::boost::filesystem::path get_xxx_filename (const ::std::string& path, const ::boost::filesystem::path& p) const;
public:
    path_root (const ::boost::filesystem::path& disk, const ::std::string& site);
    ::boost::filesystem::path get_disk_path () const { return disk_path_; }
    ::std::string get_site_path () const { return site_path_; }
    bool applicable (const ::std::string& path) const;
    ::boost::filesystem::path shadow_root () const { return shadow_; }
    bool shadow_root (nitpick& nits, const ::boost::filesystem::path& shadow);
    ::boost::filesystem::path get_export () const { return export_; }
    bool set_export (nitpick& nits, const ::boost::filesystem::path& ex);
    fileindex_t fileindex () const noexcept { return ndx_; }
    void fileindex (const fileindex_t ndx) noexcept { ndx_ = ndx; }
    ::boost::filesystem::path get_disk_filename (const ::std::string& path) const;
    ::boost::filesystem::path get_export_filename (const ::std::string& path) const;
    ::boost::filesystem::path get_shadow_filename (const ::std::string& path) const; };

typedef ::std::shared_ptr < path_root > path_root_ptr;

class paths_root
{   typedef ::std::vector < path_root_ptr > vr_t; // zeroth element must be site root, e.g. /
    vr_t root_;
    ::std::size_t get_xxx (const ::std::string& f) const;
    bool prep_xxx (nitpick& nits, const ::std::string& assignment, ::std::string& virt, ::boost::filesystem::path& p) const;
public:
    void add_root (const ::boost::filesystem::path& disk, const ::std::string& site)
    {   root_.emplace_back (new path_root (disk, site)); }
    bool add_virtual (nitpick& nits, const ::std::string& assignment);
    bool add_shadow (nitpick& nits, const ::std::string& assignment);
    bool add_export (nitpick& nits, const ::std::string& assignment);
    static paths_root& virtual_roots () noexcept;
    const path_root_ptr& at (const ::std::size_t x) const { return root_.at (x); }
    path_root_ptr& at (const ::std::size_t x) { return root_.at (x); }
    ::std::size_t size () const noexcept { return root_.size (); }
    ::boost::filesystem::path get_filename (const ::std::string& filename);
    ::boost::filesystem::path get_export (const ::std::string& filename);
    ::boost::filesystem::path get_shadow (const ::std::string& filename); };
