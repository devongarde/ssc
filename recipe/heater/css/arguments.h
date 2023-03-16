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
#include "css/css_parse.h"

class page;
class selectors;
class statement;
class css_group;
class properties;

struct arguments
{   css_group& g_;
    html_version v_;
    namespaces_ptr ns_;
    bool sv_ = true;
    bool snippet_ = false;
    bool had_rule_ = false;
    ::std::string abs_;
    dst_ptr dst_;
    vtt_t t_;
    selectors* ss_ = nullptr;
    statement* st_ = nullptr;
    properties* ps_ = nullptr;
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g);
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet);
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet, const ::std::string& abs, dst_ptr dst);
    void check_flags (nitpick& nits, const flags_t f, const ::std::string& s) const;
    void validate (nitpick& nits, const flags_t f, const ::std::string& p, const ::std::string& v) const; };
