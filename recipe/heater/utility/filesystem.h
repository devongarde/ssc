/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

struct ffsf_deleter
{   void operator () (FILE *p)
    {   if (p != nullptr) fclose (p); } };

typedef ::std::shared_ptr < FILE > ffsf;

class fancy_FILE // use BOOST_IFSTREAM_CNSTRO etc.
{   ffsf fp_;
public:
    fancy_FILE () = default;
    explicit fancy_FILE (nitpick& nits, const ::boost::filesystem::path& s, const char* flags = "r")
    {   open (nits, s, flags); }
    COPY_MOVE (fancy_FILE);
    ~fancy_FILE () { close (); }
    bool open (nitpick& nits, const ::boost::filesystem::path& s, const char* flags = "r");
    void close () noexcept;
    FILE* fp () const
    {   PRESUME (fp_, __FILE__, __LINE__);
        return fp_.get (); }
    bool invalid () const
    {   return fp_ == nullptr; } };

#ifdef UNIX
inline ::std::string local_path_to_nix (const ::std::string& s) { return s; }
inline ::std::string nix_path_to_local (const ::std::string& s) { return s; }
inline vstr_t nix_path_to_local (const vstr_t& v) { return v; }
#else // presuming if not unix then windows
::std::string local_path_to_nix (const ::std::string& win);
::std::string nix_path_to_local (const ::std::string& nix);
vstr_t nix_path_to_local (const vstr_t& v);
#endif // UNIX

#ifdef FS_THROWS
::std::time_t get_last_write_time (const ::boost::filesystem::path& name);
uintmax_t get_file_size (const ::boost::filesystem::path& name);
#ifndef NO_PERMS
bool file_permissions (const ::boost::filesystem::path& name, ::boost::filesystem::perms prms);
#endif // NO_PERMS
bool make_directories (const ::boost::filesystem::path& name);
bool make_directory (const ::boost::filesystem::path& name);
bool delete_file (const ::boost::filesystem::path& name);
bool rename_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to);
bool duplicate_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to, const BOOST_COPY_OPTION opt);
#else // FS_THROWS
::std::time_t get_last_write_time (const ::boost::filesystem::path& name) noexcept;
uintmax_t get_file_size (const ::boost::filesystem::path& name) noexcept;
#ifndef NO_PERMS
bool file_permissions (const ::boost::filesystem::path& name, ::boost::filesystem::perms prms) noexcept;
#endif // NO_PERMS
bool make_directories (const ::boost::filesystem::path& name) noexcept;
bool make_directory (const ::boost::filesystem::path& name) noexcept;
bool delete_file (const ::boost::filesystem::path& name) noexcept;
bool rename_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to) noexcept;
bool duplicate_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to, const BOOST_COPY_OPTION opt) noexcept;
#endif // FS_THROWS

bool is_folder (const ::boost::filesystem::path& name);
bool is_normal_file (const ::boost::filesystem::path& name);
bool file_exists (const ::boost::filesystem::path& name);
::boost::filesystem::file_status file_data (const ::boost::filesystem::path& name);
::boost::filesystem::path absolute_name (const ::boost::filesystem::path& name);
::boost::filesystem::path absolute_name (const ::boost::filesystem::path& name, const ::boost::filesystem::path& p2);
::boost::filesystem::path canonical_name (const ::boost::filesystem::path& name);
::boost::filesystem::path unique (const ::boost::filesystem::path& name = "%%%%-%%%%-%%%%-%%%%");
::boost::filesystem::path get_working_directory ();
::boost::filesystem::path temp_dir ();

#ifdef NOLYNX
inline bool is_file_linked (const ::boost::filesystem::path& ) noexcept { return false; }
inline ::boost::filesystem::path resolve_link (const ::boost::filesystem::path& name) { return name; }
inline bool make_hard_link (const ::boost::filesystem::path& , const ::boost::filesystem::path& )
{   GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }
inline bool make_link (const ::boost::filesystem::path& , const ::boost::filesystem::path& )
{   GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }
#else // NOLYNX
bool is_file_linked (const ::boost::filesystem::path& name);
::boost::filesystem::path resolve_link (const ::boost::filesystem::path& name);
bool make_hard_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link);
bool make_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link);
#endif // NOLYNX

bool is_normal_or_zap (const ::boost::filesystem::path& fn);
