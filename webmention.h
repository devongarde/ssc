/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "url.h"

class webmention
{   url source_, target_;
    ::std::string html_, when_;
    bool invalid_ = true;
    e_activity activity_ = act_unknown;
public:
    webmention () : invalid_ (true), activity_ (act_unknown) {}
    webmention (const url& source, const url& target, const ::std::string& html);
    webmention (nitpick& nits, ::boost::property_tree::ptree& tree, const ::std::string& container)
        : activity_ (act_static)
    {   try { read (nits, tree, container); }
        catch (...) { invalid_ = true; activity_ = act_unknown; } }
    void swap (webmention& w) noexcept
    {   source_.swap (w.source_);
        target_.swap (w.target_);
        html_.swap (w.html_);
        when_.swap (w.when_);
        ::std::swap (invalid_, w.invalid_);
        ::std::swap (activity_, w.activity_); }
    bool invalid () const { return invalid_; }
    int compare_updated (const webmention& w);
    int compare (const webmention& w);
    void read (nitpick& nits, ::boost::property_tree::ptree& tree, const ::std::string& container);
    void write (::boost::property_tree::ptree& tree, const ::std::string& container);
    e_activity activity () const { return activity_; }
    void activity (const e_activity a) { activity_ = a; }
    ::std::string apply_template (const vstr_t& templates);
    ::std::string report () const; };
