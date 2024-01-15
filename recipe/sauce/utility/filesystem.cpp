/*
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "utility/common.h"
#include "utility/filesystem.h"

#ifndef UNIX
// see also local_path_to_nix declaration in fileindex.h
// presuming if not unix then windows
::std::string local_path_to_nix (const ::std::string& s)
{   ::std::string res (s);
    ::boost::replace_all (res, "\\", "/");
    if ((res.length () >= 2) && (res.at (1) == ':')) res = res.substr (2);
    return res; }

::std::string nix_path_to_local (const ::std::string& s)
{   if (s.empty ()) return s;
    ::std::string res (s);
    ::boost::replace_all (res, "/", "\\");
    return res; }

vstr_t nix_path_to_local (const vstr_t& v)
{   vstr_t res;
    for (auto s : v)
        res.emplace_back (nix_path_to_local (s));
    return res; }
#endif // UNIX

::std::time_t get_last_write_time (const ::boost::filesystem::path& name)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{   ::std::time_t res = 0;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::last_write_time (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::last_write_time (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   res = 0; } }
    return res; }

uintmax_t get_file_size (const ::boost::filesystem::path& name)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{   uintmax_t res = 0;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::file_size (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::file_size (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   res = 0; } }
    return res; }

bool is_folder (const ::boost::filesystem::path& name)
{   bool res = false;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::is_directory (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::is_directory (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return res; }

bool is_normal_file (const ::boost::filesystem::path& name)
{   bool res = false;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::is_regular_file (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::is_regular_file (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return res; }

bool file_exists (const ::boost::filesystem::path& name)
{   bool res = false;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::exists (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::exists (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return res; }

::boost::filesystem::file_status file_data (const ::boost::filesystem::path& name)
{   ::boost::filesystem::file_status res;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::status (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::status (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return ::boost::filesystem::file_status (); } }
    return res; }

#ifndef NO_PERMS
bool file_permissions (const ::boost::filesystem::path& name, ::boost::filesystem::perms p)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::permissions (name, p); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::permissions (name, p, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }
#endif // NO_PERMS

::boost::filesystem::path absolute_name (const ::boost::filesystem::path& name)
{   ::boost::filesystem::path res;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::absolute (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::absolute (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return name; } }
    return res; }

::boost::filesystem::path canonical_name (const ::boost::filesystem::path& name)
{   ::boost::filesystem::path res;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::canonical (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::canonical (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return name; } }
    return res; }

bool make_directories (const ::boost::filesystem::path& name)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::create_directories (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::create_directories (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }

bool make_directory (const ::boost::filesystem::path& name)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::create_directory (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::create_directory (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }

bool delete_file (const ::boost::filesystem::path& name)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{   bool res = false;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::remove (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::remove (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return res; }

bool rename_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::rename (from, to); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::rename (from, to, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }

bool duplicate_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to, const BOOST_COPY_OPTION opt)
#ifndef FS_THROWS
    noexcept
#endif // FS_THROWS
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::copy_file (from, to, opt); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::copy_file (from, to, opt, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }

::boost::filesystem::path temp_dir ()
{   ::boost::filesystem::path res;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::temp_directory_path (); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::temp_directory_path (jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return ::boost::filesystem::path (); } }
    return res; }

#ifndef NOLYNX
bool is_file_linked (const ::boost::filesystem::path& name)
{   bool res = false;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::is_symlink (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::is_symlink (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return res; }

::boost::filesystem::path resolve_link (const ::boost::filesystem::path& name)
{   ::boost::filesystem::path res;
#ifdef FS_THROWS
    {   try
	    {	res = ::boost::filesystem::read_symlink (name); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        res = ::boost::filesystem::read_symlink (name, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return name; } }
    return res; }

bool make_hard_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link)
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::create_hard_link (name, link); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::create_hard_link (name, link, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }

bool make_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link)
{
#ifdef FS_THROWS
    {   try
	    {	::boost::filesystem::create_symlink (name, link); }
	    catch (...)
#else // FS_THROWS
    {   ::boost::system::error_code jec;
        ::boost::filesystem::create_symlink (name, link, jec);
        if (jec.failed ())
#endif // FS_THROWS
        {   return false; } }
    return true; }
#endif // NOLYNX
