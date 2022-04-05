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
#include "webmention/webmention.h"
// #include "main/context.h"

class webmentions
{   ::std::vector < webmention > w_;
    ::std::string id_;
    ::boost::filesystem::path html_;
    bool invalid_ = false;
public:
    webmentions () = default;
    webmentions (nitpick& nits, const ::boost::json::object& jo);
//    void reset () { w_.clear (); id_.clear (); html_.clear (); invalid_ = true; }
//    bool exists (const webmention& mensh);
//    void merge (webmention& mensh);
    bool any_invalid () const;
    ::std::string id () const noexcept { return id_; }
    bool create_html (nitpick& nits);
    bool save (nitpick& nits, ::boost::json::object& jo);
    ::std::string report () const; };

typedef ssc_map < ::std::string, webmentions > mws_t;
#endif // HAS_WM
