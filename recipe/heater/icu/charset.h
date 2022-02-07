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
#include "parser/html_version.h"

#ifdef NOICU
void verify_file_charset (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& charset, const void_ptr& vp, const uintmax_t sz) { }
void verify_file_charset (nitpick& nits, const html_version& v, const ::boost::filesystem::path& p, const ::std::string& charset) { }
#else // NOICU
#include "utility/common.h"

::std::string identify_probable_charset (const void* vp, const uintmax_t sz);
void verify_file_charset (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& charset, const void* vp, const uintmax_t sz);
void verify_file_charset (nitpick& nits, const html_version& v, const ::boost::filesystem::path& p, const ::std::string& charset);
#endif // NOICU
