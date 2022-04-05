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
#ifdef HAS_WM
#include "url/url.h"
#include "webmention/webmentions.h"

class hook
{   url source_, target_;
    mws_t mentions_;
    bool valid_ = false;
    void check ();
    bool update_mention (nitpick& nits, const ::std::string& mention, const ::std::string& trg_src);
public:
    hook () = default;
    hook (const hook& h) = default;
    hook (hook&& h) = default;
    hook (nitpick& nits, const ::boost::json::object& jo);
    ~hook () = default;
    hook& operator = (const hook& ) = default;
    hook& operator = (hook&& ) = default;
    hook (nitpick& nits, const html_version& v, const ::std::string& source, const ::std::string& target);
    url source () const { return source_; }
    url target () const { return target_; }
    bool invalid () const noexcept { return ! valid_; }
    bool save (nitpick& nits, ::boost::json::object& jo);
    void merge (nitpick& nits, const hook& h);
    ::std::string page_path () const;
    bool process (nitpick& nits, const html_version& v, const vstr_t& templates); };

typedef ssc_map < ::std::string, hook > mh_t;
#endif // HAS_WM
