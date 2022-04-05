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
#include "webmention/wm.h"

class webmention
{   url source_, target_;
    ::std::string mention_, when_, target_source_;
    bool invalid_ = true;
    e_activity activity_ = act_unknown;
public:
    webmention () = default;
    webmention (const url& source, const url& target, const ::std::string& mention, const ::std::string& trg_src);
//    webmention (nitpick& nits, ::boost::property_tree::ptree& tree, const ::std::string& container)
//        : activity_ (act_static)
//    {   try { read (nits, tree, container); }
//        catch (...) { invalid_ = true; activity_ = act_unknown; } }
    webmention (nitpick& nits, const ::boost::json::object& jo);
    bool invalid () const noexcept { return invalid_; }
    int compare_updated (const webmention& w);
    int compare (const webmention& w);
    bool save (nitpick& nits, ::boost::json::object& jo);
//    void read (nitpick& nits, const ::boost::property_tree::ptree& tree, const ::std::string& container);
//    void write (::boost::property_tree::ptree& tree, const ::std::string& container);
    e_activity activity () const noexcept { return activity_; }
    void activity (const e_activity a) noexcept { activity_ = a; }
    ::std::string apply_template (const vstr_t& templates);
    ::std::string report () const; };
#endif // HAS_WM
