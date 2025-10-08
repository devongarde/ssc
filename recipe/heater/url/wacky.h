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
#include "url/url.h"

class directory;

class wacky_url
{   vstr_t layers_;
    bool valid_ = false;
public:
    DEFAULT_CONSTRUCTORS (wacky_url);
    explicit wacky_url (nitpick& nits, const ::std::string& site_path)
    {   valid_ = parse (nits, site_path); }
    void swap (wacky_url& t) noexcept
    {   layers_.swap (t.layers_); }
    void reset () noexcept
    {   layers_.clear (); }
    bool valid () const noexcept
    {   return valid_; }
    bool parse (nitpick& nits, const ::std::string& site_path);
    bool verify (nitpick& nits); };

typedef ::std::vector < wacky_url > wacky_vt;
