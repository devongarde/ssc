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

#include "main/standard.h"
#include "webpage/fileindex.h"
#include "webpage/directory.h"

struct index_t
{   ::boost::filesystem::path disk_path_;
    fileindex_flags flags_ = 0;
    directory* pd_ = nullptr;
    index_t (const ::boost::filesystem::path& p, fileindex_flags flags, directory* d) : disk_path_ (p), flags_ (flags), pd_ (d) { } };

typedef ::std::vector < index_t > vx_t;
typedef ssc_map < ::std::string, fileindex_t > mxp_t;
vx_t vx;
mxp_t site_x, disk_x;  // note ::boost::filesystem::path and ::std::map are not pals

#if defined (UNIX)
::std::string local_path_to_nix (const ::std::string& win) { return win; }
::std::string nix_path_to_local (const ::std::string& win) { return win; }
#else // presuming if not unix then windows
::std::string local_path_to_nix (const ::std::string& win)
{   ::std::string res (win);
    ::boost::replace_all (res, "\\", "/");
    if ((res.length () >= 2) && (res.at (1) == ':')) res = res.substr (2);
    return res; }

::std::string nix_path_to_local (const ::std::string& nix)
{   if (nix.empty ()) return nix;
    ::std::string res (nix);
    ::boost::replace_all (res, "/", "\\");
    return res; }
#endif // UNIX

void fileindex_init ()
{   assert (disk_x.empty ());
    assert (site_x.empty ());
#ifndef ORDERED
    disk_x.reserve (16384);
    site_x.reserve (16384);
#endif // FUDDYDUDDY
 }

fileindex_t insert_disk_path (const ::boost::filesystem::path& name, fileindex_flags flags, directory* pd)
{   if (name.empty ()) return nullfileindex;
    mxp_t::iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ())
    {   assert (i -> second < vx.size ());
        if (vx [i -> second].pd_ == nullptr)
            vx [i -> second].pd_ = pd;
        return i -> second; }
    vx.emplace_back (name, flags, pd);
    assert (vx.size () > 0);
    fileindex_t xin = vx.size () - 1;
    disk_x.emplace (name.string (), xin);
    return xin; }

void add_site_path (const ::std::string& name, const fileindex_t s)
{   assert (s < vx.size ());
    auto i = site_x.emplace (name, s);
    if (! i.second) i.first -> second = s; }

fileindex_t get_fileindex (const ::boost::filesystem::path& name)
{   mxp_t :: const_iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ()) return i -> second;
    return insert_disk_path (name, 0, nullptr); }

fileindex_t get_fileindex (const ::std::string& name)
{   mxp_t :: const_iterator i = site_x.find (name);
    if (i != site_x.cend ()) return i -> second;
    return nullfileindex; }

::boost::filesystem::path get_filename (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::boost::filesystem::path ();
    return vx [ndx].disk_path_; }

fileindex_flags get_flags (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return 0;
    return vx [ndx].flags_; }

bool get_flag (const fileindex_t ndx, const fileindex_flags flag)
{   if (ndx >= vx.size ()) return false;
    return (vx [ndx].flags_ & flag) != 0; }

void set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   if (ndx >= vx.size ()) return;
    vx [ndx].flags_ |= flag; }

void reset_flag (const fileindex_t ndx, const fileindex_flags flag)
{   if (ndx >= vx.size ()) return;
    vx [ndx].flags_ &= ~flag; }

::std::string fileindex_report ()
{   ::std::string res ("\nFile Indices\n");
    if (vx.size () == 0) return ::std::string ();
    for (::std::size_t i = 0; i < vx.size (); ++i)
    {   res += ::boost::lexical_cast < ::std::string > (i);
        res += ": ";
        res += vx [i].disk_path_.string ();
        res += " (";
        res += ::boost::lexical_cast < ::std::string > (vx [i].flags_);
        res += ")\n"; }
    res += "\nSite:\n";
    for (auto i : site_x)
    {   res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\nDisk index:\n";
    for (auto i : disk_x)
    {   res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\n";
    return res; }

::std::string inner_join_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   if (lhs.empty ()) return rhs;
    if (rhs.empty ()) return lhs;
    ::std::string l (lhs);
    ::std::string r (rhs);
    if (r.at (0) != '/') r = ::std::string ("/") + r;
    ::std::string::size_type len = l.size ();
    if (l.at (len - 1) == '/')
    {   if (len == 1) return r;
        l = l.substr (0, len - 1); }
    return l + r; }

::std::string join_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   return ::boost::replace_all_copy (inner_join_site_paths (lhs, rhs), "//", "/"); }
