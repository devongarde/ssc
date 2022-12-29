/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "css/distilled.h"

class page;

struct arguments
{   html_version v_;
    namespaces_ptr ns_;
    page* p_ = nullptr;
    bool sv_ = true;
    bool snippet_ = false;
    bool had_rule_ = false;
    ::std::string abs_;
    dst_ptr dst_;
    arguments (const html_version& v, const namespaces_ptr& namespaces, page* p)
        : v_ (v), ns_ (namespaces), p_ (p) { }
    arguments (const html_version& v, const namespaces_ptr& namespaces, page* p, bool sv, bool snippet)
        : v_ (v), ns_ (namespaces), p_ (p), sv_ (sv), snippet_ (snippet) { }
    arguments (const html_version& v, const namespaces_ptr& namespaces, page* p, bool sv, bool snippet, const ::std::string& abs, dst_ptr dst)
        : v_ (v), ns_ (namespaces), p_ (p), sv_ (sv), snippet_ (snippet), abs_ (abs), dst_ (dst)
    { } };
