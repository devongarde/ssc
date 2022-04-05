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
#include "utility/common.h"

class lingo;

class reply
{   ::std::string file_, id_, server_, target_, content_, when_;
    e_activity activity_ = act_unknown;
    ::std::string clean (const ::std::string& s);
    bool find_server (nitpick& nits, const html_version& v, const lingo& lang);
    bool set_server (const ::std::string& link);
public:
    reply (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
        : file_ (file), id_ (id), target_ (target), content_ (clean (content)), activity_ (act_unknown)  { mark (); }
    reply (::boost::property_tree::ptree& tree, const ::std::string& container) : activity_ (act_unknown) { read (tree, container); }
    reply (nitpick& nits, const ::boost::json::object& jo);
    void swap (reply& r) noexcept;
    bool invalid () const noexcept { return file_.empty (); }
    void mark ();
    bool operator == (const reply& rhs) const noexcept;
    bool close_but_no_banana (const reply& rhs) const noexcept;
    void mark_unchanged ();
    void mark_unknown () noexcept { activity_ = act_unknown; }
    void mark_update ();
    void mark_insert ();
    void mark_delete ();
    bool is_unknown () const noexcept { return activity_ == act_unknown; }
    bool is_deleted () const noexcept { return activity_ == act_delete; }
    void read (const ::boost::property_tree::ptree& tree, const ::std::string& container);
    void write (::boost::property_tree::ptree& tree, const ::std::string& container);
    ::std::string report (const char* verb) const;
    ::std::string report (const ::std::size_t n) const;
    bool enact (nitpick& nits, const html_version& v, const lingo& lang);
    bool save (nitpick& nits, ::boost::json::object& jo);
    bool process (nitpick& nits, const html_version& v); };

typedef ::std::vector < reply > vreply_t;
constexpr ::std::size_t no_reply = UINT_MAX;
#endif // HAS_WM
