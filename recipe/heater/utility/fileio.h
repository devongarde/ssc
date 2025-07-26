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

::std::string read_text_file (nitpick& nits, const ::boost::filesystem::path& name, bool& borked);
::std::string read_text_file (nitpick& nits, const ::std::string& name, bool& borked);
void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, ::std::size_t& sz, const bool zero_ok = false);
bool write_text_file (nitpick& nits, const ::boost::filesystem::path& n, const ::std::string& content);
bool write_text_file (nitpick& nits, const ::std::string& name, const ::std::string& content);
bool write_binary_file (nitpick& nits, const ::boost::filesystem::path& n, const void* content, const ::std::size_t sz);
inline bool write_binary_file (nitpick& nits, const ::boost::filesystem::path& n, const void_ptr& v, const ::std::size_t sz)
{   return write_binary_file (nits, n, v.get (), sz); }
//template < class T > bool write_file (nitpick& nits, const ::boost::filesystem::path& n, const T* t, const ::std::size_t sz)
//{   return write_binary_file (nits, n, t, sz); }
//::boost::filesystem::path get_tmp_filename ();
