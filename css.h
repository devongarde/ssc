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
#include "common.h"
#include "nitpick.h"

class url;
class page;

class css
{   static bool parsing_;
    bool active_ = false;
    bool snippet_ = false;
    smsid_t ids_;
    void check_for_standard_classes (nitpick& nits, const html_version& v);
public:
    css () { }
    explicit css (nitpick& nits, const page& p, const url& u)
    {   parse_file (nits, p, u); }
    css (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding, bool snippet = false)
        :   snippet_ (snippet)
    {   parse (nits, v, content, encoding); }
    css (const css& c) = default;
    css (css&& c) = default;
    ~css () { }
    void swap (css& c) noexcept
    {   ::std::swap (active_, c.active_);
        ::std::swap (snippet_, c.snippet_);
        ids_.swap (c.ids_); }
    void reset () { ids_.clear (); }
    bool invalid () const { return false; }
    bool active () const { return active_; }
    void active (const bool b) { active_ = b; }
    bool snippet () const { return snippet_; }
    void snippet (const bool b) { snippet_ = b; }
    bool has_id (const ::std::string& id) const { return active_ && ids_.find (id) != ids_.end (); }
    bool note_usage (const ::std::string& id);
    void tally (smsid_t& ids) const;
    bool parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding = cc_ansi);
    bool parse_file (nitpick& nits, const page& p, const url& u); };

typedef ::std::shared_ptr < css > css_ptr;
