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
#include "css.h"

typedef ::std::map < ::std::string, css_ptr > csss_t;
typedef csss_t::value_type csss_vt;
typedef csss_t::iterator csss_it;
typedef csss_t::const_iterator csss_cit;
typedef ::std::pair < csss_it, bool > csss_pt;
typedef ::std::map < ::std::string, ::std::string > ss_t;
typedef ::std::shared_ptr < ss_t > ss_ptr;
typedef ss_t::value_type ss_vt;

class css_cache_t
{   csss_t csss_;
    ss_ptr ss_;
    void deactivate_all ();
    void delete_snippets ();
public:
    void swap (css_cache_t& c) noexcept
    {   csss_.swap (c.csss_); }
    void post_process ();
    bool parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding = cc_ansi, const bool snippet = true);
    bool parse_file (nitpick& nits, const page& p, const url& u);
    bool note_usage (const ::std::string& id);
    void report_usage (::std::ostringstream& ss) const;
    bool has_id (const ::std::string& id) const; };

typedef ::std::unique_ptr < css_cache_t > css_uptr;
extern css_uptr css_cache;
void init_css_cache ();
