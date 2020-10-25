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

#include "standard.h"
#include "root.h"
#include "common.h"
#include "fileindex.h"
#include "quote.h"

path_root::path_root (const ::boost::filesystem::path& disk, const ::std::string& site)
    : disk_path_ (disk), site_path_ (local_path_to_nix (site))
{   add_site_path (site, insert_disk_path (disk, 0, nullptr)); }

bool path_root::applicable (const ::std::string& path) const
{   if (path.length () < site_path_.length ()) return false;
    return (local_path_to_nix (path.substr (0, site_path_.length ())) == site_path_); }

::boost::filesystem::path path_root::get_disk_filename (const ::std::string& path) const
{   assert (applicable (path));
    ::std::string::size_type pos = site_path_.length ();
    ::boost::filesystem::path res (disk_path_);
    res /= path.substr (pos);
    return res; }

::boost::filesystem::path paths_root::get_filename (const ::std::string& filename)
{   assert (root_.size () > 0);
    ::std::string f (local_path_to_nix (filename));
    for (::std::size_t i = root_.size () - 1; i > 0; --i)
        if (root_ [i] -> applicable (f))
            return root_ [i] -> get_disk_filename (f);
    return root_ [0] -> get_disk_filename (f); }

bool paths_root::add_virtual (nitpick& nits, const ::std::string& assignment)
{   ::std::size_t len = assignment.length ();
    ::std::size_t sz = assignment.find ('=');
    if ((sz == ::std::string::npos) || (sz < 1) || (sz >= len - 1))
        nits.pick (nit_bad_parameter, es_error, ec_init, quote (assignment), " is badly formed");
    else
    {   ::boost::filesystem::path p (nix_path_to_local (assignment.substr (sz + 1)));
        if (! ::boost::filesystem::exists (p))
            nits.pick (nit_bad_path, es_error, ec_init, quote (p.string ()), " does not exist or cannot be accessed");
        else if (! ::boost::filesystem::is_directory (p))
            nits.pick (nit_bad_path, es_error, ec_init, quote (p.string ()), " is not a directory");
        else
        {   add_root (p, assignment.substr (0, sz));
            return true; } }
    return false; }

paths_root& paths_root::virtual_roots ()
{   static paths_root virtuals;
    return virtuals; }
