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
#include "main/context.h"

class url;

bool fetch (nitpick& nits,const html_version& v, const url& u, const ::boost::filesystem::path& file);
bool fetch_http (nitpick& nits,const html_version& v, const url& u, const ::boost::filesystem::path& file);
bool mention (nitpick& nits,const html_version& v, const url& source, const url& target, const url& server);

class external
{   typedef ssc_map < ::std::string, int > map_t;
    typedef map_t::value_type value_t;
    map_t url_;
public:
    void swap (external& e) NOEXCEPT
    {   url_.swap (e.url_); }
    bool verify (nitpick& nits, const html_version& v, const url& u);
    ::std::string load (const url& u); };
