/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

// once windows and unix paths are handled properly and interchangeably with
// url paths, then this type should be integrated deeply into the rest of the code
// issues: not just / versus \  but also root version X: and \\xyzzy\ and how
// WSL and other utilities mount windows volumes in 'nix

typedef unsigned long long fileindex_t;
typedef unsigned int fileindex_flags;
typedef ::std::set < fileindex_t > sndx_t;
class directory;

typedef ::boost::crc_32_type crc_calc;
typedef crc_calc::value_type crc_t;
CONSTEXPR crc_t crc_initrem = 0xFFFFFFFF; // CRC 32 initial remainder; see boost docs
CONSTEXPR fileindex_t nullfileindex = SIZE_MAX;

#define FX_SCANNED  0x00000001
#define FX_EXISTS   0x00000002
#define FX_TESTED   0x00000004
#define FX_CRC      0x00000008
#define FX_DIR      0x00000010
#define FX_BORKED   0x00000020
#define FX_STALE    0x00000040
#define FX_DELETED  0x00000080
#define FX_LINKED   0x00000100
#define FX_WAITAMO  0x00000200

void fileindex_init ();
::boost::filesystem::path persist_path ();
bool fileindex_load (nitpick& nits);
void fileindex_save_and_close (nitpick& nits);
fileindex_t insert_disk_path (const ::boost::filesystem::path& name, const fileindex_flags flags = 0);
fileindex_t insert_directory_path (const ::boost::filesystem::path& name);
void add_site_path (const ::std::string& name, const fileindex_t s);
fileindex_t get_fileindex (const ::boost::filesystem::path& name);
fileindex_t get_fileindex (const ::std::string& name);
::boost::filesystem::path get_disk_path (const fileindex_t ndx);
::std::string get_site_path (const fileindex_t ndx);
fileindex_flags get_flags (const fileindex_t ndx);
bool get_any_flag (const fileindex_t ndx, const fileindex_flags flag);
bool get_every_flag (const fileindex_t ndx, const fileindex_flags flag);
void inner_set_flag (const fileindex_t ndx, const fileindex_flags flag);
bool try_set_flag (const fileindex_t ndx, const fileindex_flags flag);
void set_flag (const fileindex_t ndx, const fileindex_flags flag);
void reset_flag (const fileindex_t ndx, const fileindex_flags flag);
uintmax_t get_size (const fileindex_t ndx);
::std::time_t last_write (const fileindex_t ndx);
crc_t calc_crc (nitpick& nits, const ::boost::filesystem::path& dp);
crc_t get_crc (nitpick& nits, const fileindex_t ndx);
void set_crc (const fileindex_t ndx, const crc_t& crc);
::std::string fileindex_report ();
::std::string join_site_paths (const ::std::string& lhs, const ::std::string& rhs);
::std::string join_and_sanatise_site_paths (const ::std::string& lhs, const ::std::string& rhs);
void dedu (nitpick& nits);
bool isdu (const fileindex_t ndx);
fileindex_t du (const fileindex_t ndx);
void add_dependency (const fileindex_t ndx, const fileindex_t dependency);
void clear_dependencies (const fileindex_t ndx);
sndx_t get_dependencies (const fileindex_t ndx);
void set_lynx (const fileindex_t ndx, const fileindex_t dependency);
void clear_lynx (const fileindex_t ndx);
sndx_t get_lynx (const fileindex_t ndx);
bool needs_update (const fileindex_t ndx, const ::std::time_t& st);
void reset_fileindices () noexcept;
fileindex_t get_fileindex_count ();
