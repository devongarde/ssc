/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "url/url_parameters.h"
#include "url/url_sanitise.h"

::std::string parameters::value (const ::std::string& key) const
{   auto i = key_value_.find (key);
    if (i != key_value_.end ()) return i -> second;
    return ::std::string (); }

void parameters::parse (const html_version& , const ::std::string& url_args)
{   vstr_t args = split_by_charset (sanitise (url_args), "&");
    for (auto s : args)
    {   const ::std::size_t pos = s.find (EQUAL);
        if (pos == s.npos)
            key_value_.insert (ustrv_t (s, ::std::string ()));
        else
        {   ::std::string lhs (s.substr (0, pos));
            ::std::string rhs (s.substr (pos+1));
            key_value_.insert (ustrv_t (lhs, rhs)); } } }

::std::string parameters::assemble () const
{   ::std::string res;
    for (auto kv : key_value_)
    {   if (! res.empty ()) res += '&';
        res += kv.first;
        if (! kv.second.empty ())
        {   res += '=';
            res += kv.second; } }
    return res; }

bool parameters::operator == (const parameters& rhs) const
{   return key_value_ == rhs.key_value_; }
