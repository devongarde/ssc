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

constexpr ::std::size_t last_component = static_cast <::std::size_t> (es_extension);
constexpr ::std::size_t component_count = last_component + 1;

typedef vstr_t vc_t;

class protocol : public symbol < html_version, e_protocol >
{   bool default_ = false;
    mutable vc_t component_;
    void reinit () const
    {   if (component_.size () == 0)
        try
        {   component_.resize (component_count); }
        catch (...)
        {   GRACEFUL_CRASH (__FILE__, __LINE__); } }
public:
    protocol () noexcept = default;
    protocol (const protocol& rhs) = default;
    protocol (protocol&& rhs) = default;
    ~protocol () = default;
    protocol (nitpick& nits, const html_version& v, const ::std::string& x, const e_protocol current = pr_https)
    {   component_.resize (component_count);
        parse (nits, v, x, current); }
    protocol& operator = (const protocol& rhs) = default;
    protocol& operator = (protocol&& rhs) = default;
    bool operator == (const protocol& rhs) const;
    bool parse (nitpick& nits, const html_version& v, const ::std::string& x, e_protocol current = pr_https);
    void swap (protocol& p) noexcept
    {   ::std::swap (default_, p.default_);
        component_.swap (p.component_);
        symbol < html_version, e_protocol > :: swap (p); }
    bool is_valid () const;
    ::std::string get () const;
    ::std::string absolute (bool can_use_index) const;
    bool defaulted () const noexcept { return default_; }
    e_protocol get_protocol () const noexcept { return (symbol < html_version, e_protocol > :: get ()); }
    bool unknown () const noexcept { return get_protocol () == pr_other; }
    bool has_component (const e_component c) const
    {   reinit ();
        return ! get_component (c).empty (); }
    ::std::string original () const
    {   reinit ();
        return ::gsl::at (component_, es_original); }
    ::std::string get_component (const e_component c) const
    {   reinit ();
        return ::gsl::at (component_, c); }
    void reset_component (const e_component c)
    {   reinit ();
        ::gsl::at (component_, c).clear (); }
    void set_component (const e_component c, const ::std::string& val)
    {   reinit ();
        ::gsl::at (component_, c) = val; }
    bool is_protocol (const e_protocol p) const noexcept { return (get_protocol () == p); }
    e_scheme scheme () const;
    static void init (nitpick& nits); };
