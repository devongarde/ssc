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

#include "main/standard.h"
#include "webpage/root.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "webpage/fileindex.h"
#include "utility/quote.h"

bool make_export_directory (nitpick& nits, const ::boost::filesystem::path& p);
bool make_shadow_directory (nitpick& nits, const ::boost::filesystem::path& p);

path_root::path_root (const ::boost::filesystem::path& disk, const ::std::string& site)
    : disk_path_ (disk), site_path_ (local_path_to_nix (site))
{   add_site_path (site, insert_directory_path (disk)); }

bool path_root::applicable (const ::std::string& path) const
{   if (path.length () < site_path_.length ()) return false;
    return (local_path_to_nix (path.substr (0, site_path_.length ())) == site_path_); }

::boost::filesystem::path path_root::get_xxx_filename (const ::std::string& path, const ::boost::filesystem::path& p) const
{   PRESUME (applicable (path), __FILE__, __LINE__);
    ::std::string::size_type pos = site_path_.length ();
    ::boost::filesystem::path res (p);
    res /= path.substr (pos);
    return res; }

::boost::filesystem::path path_root::get_disk_filename (const ::std::string& path) const
{   return get_xxx_filename (path, disk_path_); }

::boost::filesystem::path path_root::get_shadow_filename (const ::std::string& path) const
{   return get_xxx_filename (path, shadow_); }

::boost::filesystem::path path_root::get_export_filename (const ::std::string& path) const
{   return get_xxx_filename (path, export_); }

bool path_root::shadow_root (nitpick& nits, const ::boost::filesystem::path& shadow)
{   if (! make_shadow_directory (nits, shadow)) return false;
    shadow_ = shadow;
    return true; }

bool path_root::set_export (nitpick& nits, const ::boost::filesystem::path& ex)
{   if (! make_export_directory (nits, ex)) return false;
    export_ = ex;
    return true; }

::std::size_t paths_root::get_xxx (const ::std::string& f) const
{   PRESUME (root_.size () > 0, __FILE__, __LINE__);
    for (::std::size_t i = root_.size () - 1; i > 0; --i)
        if (root_ [i] -> applicable (f)) return i;
    return 0; }

::boost::filesystem::path paths_root::get_filename (const ::std::string& filename)
{   VERIFY_NOT_NULL (root_ [get_xxx (filename)], __FILE__, __LINE__);
    return root_ [get_xxx (filename)] -> get_disk_filename (local_path_to_nix (filename)); }

::boost::filesystem::path paths_root::get_shadow (const ::std::string& filename)
{   VERIFY_NOT_NULL (root_ [get_xxx (filename)], __FILE__, __LINE__);
    return root_ [get_xxx (filename)] -> get_shadow_filename (local_path_to_nix (filename)); }

::boost::filesystem::path paths_root::get_export (const ::std::string& filename)
{   VERIFY_NOT_NULL (root_ [get_xxx (filename)], __FILE__, __LINE__);
    return root_ [get_xxx (filename)] -> get_export_filename (local_path_to_nix (filename)); }

bool paths_root::prep_xxx (nitpick& nits, const ::std::string& assignment, ::std::string& virt, ::boost::filesystem::path& p) const
{   ::std::size_t len = assignment.length ();
    ::std::size_t sz = assignment.find ('=');
    if ((sz == ::std::string::npos) || (sz < 1) || (sz >= len - 1))
    {   nits.pick (nit_bad_parameter, es_error, ec_init, quote (assignment), " is badly formed");
        return false; }
    virt = assignment.substr (0, sz);
    p = nix_path_to_local (assignment.substr (sz + 1));
    return true; }

bool paths_root::add_virtual (nitpick& nits, const ::std::string& assignment)
{   ::boost::filesystem::path p;
    ::std::string virt;
    if (prep_xxx (nits, assignment, virt, p))
        if (! file_exists (p))
            nits.pick (nit_bad_path, es_error, ec_init, quote (p.string ()), " does not exist or cannot be accessed");
        else if (! is_folder (p))
            nits.pick (nit_bad_path, es_error, ec_init, quote (p.string ()), " exists but is not a directory");
        else
        {   add_root (p, virt);
            return true; }
    return false; }

bool paths_root::add_shadow (nitpick& nits, const ::std::string& assignment)
{   ::boost::filesystem::path p;
    ::std::string virt;
    if (prep_xxx (nits, assignment, virt, p))
    {   for (size_t n = 1; n < root_.size (); ++n)
        {   VERIFY_NOT_NULL (root_.at (n), __FILE__, __LINE__);
            if (root_.at (n) -> get_site_path () == virt)
                return root_.at (n) -> shadow_root (nits, p);
        nits.pick (nit_bad_parameter, es_error, ec_init, quote (virt), " is no virtual directory"); } }
    return false; }

bool paths_root::add_export (nitpick& nits, const ::std::string& assignment)
{   ::boost::filesystem::path p;
    ::std::string virt;
    if (prep_xxx (nits, assignment, virt, p))
    {   for (size_t n = 1; n < root_.size (); ++n)
        {   VERIFY_NOT_NULL (root_.at (n), __FILE__, __LINE__);
            if (root_.at (n) -> get_site_path () == virt)
                return root_.at (n) -> set_export (nits, p);
        nits.pick (nit_bad_parameter, es_error, ec_init, quote (virt), " is no virtual directory"); } }
    return false; }

paths_root& paths_root::virtual_roots ()
{   static paths_root virtuals;
    return virtuals; }

bool make_xxx_directory (nitpick& nits, const ::boost::filesystem::path& p)
{   if (file_exists (p))
    {   if (! is_folder (p))
        {   nits.pick (nit_shadow, es_error, ec_init, quote (p.string ()), " exists but is not a directory");
            return false; } }
    else if (make_directories (p))
        nits.pick (nit_shadow, es_info, ec_init, "created ", quote (p.string ()));
    else
    {   nits.pick (nit_shadow, es_error, ec_init, "cannot create ", quote (p.string ())); return false; }
    return true; }

bool make_shadow_directory (nitpick& nits, const ::boost::filesystem::path& p)
{   return make_xxx_directory (nits, p); }

bool make_export_directory (nitpick& nits, const ::boost::filesystem::path& p)
{   return make_xxx_directory (nits, p); }
