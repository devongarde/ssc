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

void init_cache ();
bool cached_file (nitpick& nits, const ::boost::filesystem::path& pt, ::std::string& content, bool& borked, bool store = true); 
bool cached_url (nitpick& nits, const html_version& v, const directory* d, const url& u, ::std::string& content, ::std::time_t& when, bool& borked); 
void report_cache (nitpick& nits, const ::std::string& intro = ::std::string ());
bool cache_of_interest (const ::std::string& n);
