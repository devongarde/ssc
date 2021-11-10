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
#include "utility/common.h"

class parameters
{   ustr_t key_value_;
    void parse (const html_version& v, const ::std::string& url_args);
public:
	parameters () = default;
    parameters (const parameters&) = default;
	parameters (parameters&&) = default;
	explicit parameters (const html_version& v, const ::std::string& url_args) { parse (v, url_args); }
	parameters& operator = (const parameters&) = default;
	parameters& operator = (parameters&&) = default;
    bool operator == (const parameters& rhs) const;
    ~parameters () = default;
    void swap (parameters& p) noexcept { key_value_.swap (p.key_value_); }
    bool empty () const noexcept { return key_value_.empty (); }
    ::std::size_t size () const noexcept { return key_value_.size (); }
    ::std::string assemble () const;
    bool exists (const ::std::string& key) const
    {   return (key_value_.find (key) != key_value_.end ()); }
    ::std::string value (const ::std::string& key) const; };
