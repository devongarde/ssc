/*
ssc (static site checker)
File Info
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

#ifndef NOICU
#include "feedback/nitpick.h"
#include "parser/html_version.h"

::std::string get_standard_converter_name (nitpick& nits, const ::std::string& name);
::std::string convert_to_utf8 (nitpick& nits, const ::std::string& name, const void_ptr& vp, const uintmax_t& sz);
::std::string normalise_utf8 (nitpick& nits, const ::std::string& s);
::std::string convert_to_utf8 (const unsigned int n);

#ifdef _MSC_VER
::std::wstring convert_to_wstring (nitpick& nits, const ::icu::UnicodeString& us);
#ifndef VS2017
::std::wstring convert_to_wstring (const ::std::string& s);
#endif // VS2017
::std::string normalise_utf8 (nitpick& nits, const ::std::string& s);
#endif // _MSC_VER

#else // NOICU
inline ::std::string normalise_utf8 (nitpick& , const ::std::string& s) { return s; }
#endif // NOICU
