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

::std::time_t get_last_write_time (const ::boost::filesystem::path& name);
uintmax_t get_file_size (const ::boost::filesystem::path& name);
bool is_folder (const ::boost::filesystem::path& name);
bool is_file (const ::boost::filesystem::path& name);
bool file_exists (const ::boost::filesystem::path& name);
::boost::filesystem::file_status file_data (const ::boost::filesystem::path& name);
bool file_permissions (const ::boost::filesystem::path& name, ::boost::filesystem::perms prms);
::boost::filesystem::path absolute_name (const ::boost::filesystem::path& name);
::boost::filesystem::path canonical_name (const ::boost::filesystem::path& name);
bool make_directories (const ::boost::filesystem::path& name);
bool make_directory (const ::boost::filesystem::path& name);
bool delete_file (const ::boost::filesystem::path& name);
bool rename_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to);
bool duplicate_file (const ::boost::filesystem::path& from, const ::boost::filesystem::path& to, const ::boost::filesystem::copy_option opt);
::boost::filesystem::path temp_dir ();

#ifdef NOLYNX
inline bool is_file_linked (const ::boost::filesystem::path& ) { return false; }
inline ::boost::filesystem::path resolve_link (const ::boost::filesystem::path& name) { return name; }
inline bool make_hard_link (const ::boost::filesystem::path& , const ::boost::filesystem::path& )
{   GRACEFUL_CRASH (__FILE__, __LINE__);
    return false; }
inline bool make_link (const ::boost::filesystem::path& , const ::boost::filesystem::path& )
{   GRACEFUL_CRASH (__FILE__, __LINE__);
    return false; }
#else // NOLYNX
bool is_file_linked (const ::boost::filesystem::path& name);
::boost::filesystem::path resolve_link (const ::boost::filesystem::path& name);
bool make_hard_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link);
bool make_link (const ::boost::filesystem::path& name, const ::boost::filesystem::path& link);
#endif // NOLYNX
