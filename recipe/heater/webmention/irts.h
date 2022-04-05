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
#include "webmention/irt.h"

class lingo;

class replies
{   vreply_t reply_;
    ::std::size_t size () const noexcept { return reply_.size (); }
    ::std::size_t find (const reply& r);
    ::std::size_t probably_match (const reply& r);
    bool read (const ::std::string filename);
    bool write ();
    bool update_records (nitpick& nits);
    bool enact (nitpick& nits, const html_version& v, const lingo& lang);
public:
//    void swap (replies& r) noexcept { reply_.swap (r.reply_); }
    bool load (nitpick& nits, const ::boost::json::object& jo);
    bool save (nitpick& nits, ::boost::json::object& jo);
    void append (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content);
    ::std::string report (const char* comment = nullptr) const;
    bool process (nitpick& nits, const html_version& v, const lingo& lang); };
#endif // HAS_WM
