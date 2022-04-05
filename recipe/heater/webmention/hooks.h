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
#include "webmention/hook.h"
/*
hook === page
webmentions === id
webmention === mention
*/

class hooks
{   mh_t hooks_;
public:
    bool load (nitpick& nits, const ::boost::json::object& jo);
    bool save (nitpick& nits, ::boost::json::object& jo);
    bool empty () const noexcept;
    bool process (nitpick& nits, const html_version& v, const vstr_t& templates, const vstr_t& mentions); };
#endif // HAS_WM
