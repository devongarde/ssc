/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "nitpick.h"

class path_root
{   ::boost::filesystem::path disk_path_;
    ::std::string site_path_;
public:
    path_root (const ::boost::filesystem::path& disk, const ::std::string& site);
    ::boost::filesystem::path get_disk_path () const { return disk_path_; }
    ::std::string get_site_path () const { return site_path_; }
    bool applicable (const ::std::string& path) const;
    ::boost::filesystem::path get_disk_filename (const ::std::string& path) const; };

typedef ::std::shared_ptr < path_root > path_root_ptr;

class paths_root
{   typedef ::std::vector < path_root_ptr > vr_t; // zeroth element must be site root, e.g. /
    vr_t root_;
public:
    void add_root (const ::boost::filesystem::path& disk, const ::std::string& site)
    {   root_.emplace_back (new path_root (disk, site)); }
    bool add_virtual (nitpick& nits, const ::std::string& assignment);
    static paths_root& virtual_roots ();
    const path_root_ptr& at (const ::std::size_t x) const { return root_.at (x); }
    path_root_ptr& at (const ::std::size_t x) { return root_.at (x); }
    ::std::size_t size () const { return root_.size (); }
    ::boost::filesystem::path get_filename (const ::std::string& filename); };
