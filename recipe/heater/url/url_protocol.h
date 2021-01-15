/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "symbol/symbol.h"

const ::std::size_t last_component = static_cast <::std::size_t> (es_file);
const ::std::size_t component_count = last_component + 1;

typedef vstr_t vc_t;

class protocol : public symbol < e_protocol >
{   bool default_ = false;
    vc_t component_;
public:
    protocol () : default_ (false)
    {   component_.resize (component_count); }
	protocol(const protocol&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	protocol (protocol&&) = default;
#endif // VS
    protocol (nitpick& nits, const html_version& v, const ::std::string& x, const e_protocol current = pr_https)
    {   component_.resize (component_count);
        parse (nits, v, x, current); }
	protocol& operator = (const protocol&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	protocol& operator = (protocol&&) = default;
#endif // VS
	~protocol() = default;
    bool operator == (const protocol& rhs) const;
    bool parse (nitpick& nits, const html_version& v, const ::std::string& x, e_protocol current = pr_https);
    void swap (protocol& p) NOEXCEPT
    {   ::std::swap (default_, p.default_);
        component_.swap (p.component_);
        symbol < e_protocol > :: swap (p); }
    bool is_valid () const;
    ::std::string get () const;
    ::std::string absolute (bool can_use_index) const;
    bool defaulted () const { return default_; }
    e_protocol get_protocol () const { return (symbol < e_protocol > :: get ()); }
    bool unknown () const { return get_protocol () == pr_other; }
    bool has_component (const e_component c) const { return ! get_component (c).empty (); }
    ::std::string original () const { return component_ [es_original]; }
    ::std::string get_component (const e_component c) const { return component_ [c]; }
    void reset_component (const e_component c) { component_ [c].clear (); }
    void set_component (const e_component c, const ::std::string& val) { component_ [c] = val; }
    bool is_protocol (const e_protocol p) const { return (get_protocol () == p); }
    e_scheme scheme () const;
    static void init (nitpick& nits); };
