/*
ssc (static site checker)
File Info
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
#include "url/url_scheme.h"

template < e_scheme SCHEME, e_scheme... S > struct url_schemes
{   static bool similar (const e_scheme scheme, const vc_t& lhs, const vc_t& rhs)
    {   if (lhs.at (es_scheme) != rhs.at (es_scheme)) return false;
        return equivalent (scheme, lhs, rhs); }
    static bool equivalent (const e_scheme scheme, const vc_t& lhs, const vc_t& rhs)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: equivalent (lhs, rhs);
        return url_schemes < S... > :: equivalent (scheme, lhs, rhs); }
    static bool parse (nitpick& nits, const html_version& v, const e_scheme scheme, const e_protocol prot, const ::std::string& url, vc_t& component)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: parse (nits, v, prot, url, component);
        return url_schemes < S... > :: parse (nits, v, scheme, prot, url, component); }
    static bool is_valid (const e_scheme scheme, const vc_t& component, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: is_valid (component, defaulted);
        return url_schemes < S... > :: is_valid (scheme, component, defaulted); }
    static ::std::string get (const e_scheme scheme, const vc_t& component, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: get (component, defaulted);
        return url_schemes < S... > :: get (scheme, component, defaulted); }
    static ::std::string absolute (const e_scheme scheme, const vc_t& component, bool can_use_index, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: absolute (component, can_use_index, defaulted);
        return url_schemes < S... > :: absolute (scheme, component, can_use_index, defaulted); } };

template < e_scheme SCHEME > struct url_schemes < SCHEME >
{   static bool similar (const e_scheme scheme, const vc_t& lhs, const vc_t& rhs)
    {   if (lhs.at (es_scheme) != rhs.at (es_scheme)) return false;
        return equivalent (scheme, lhs, rhs); }
    static bool equivalent (const e_scheme scheme, const vc_t& lhs, const vc_t& rhs)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: equivalent (lhs, rhs);
        return false; }
    static bool parse (nitpick& nits, const html_version& v, const e_scheme scheme, const e_protocol prot, const ::std::string& url, vc_t& component)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: parse (nits, v, prot, url, component);
        return false; }
    static bool is_valid (const e_scheme scheme, const vc_t& component, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: is_valid (component, defaulted);
        return false; }
    static ::std::string get (const e_scheme scheme, const vc_t& component, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: get (component, defaulted);
        return ::std::string (); }
    static ::std::string absolute (const e_scheme scheme, const vc_t& component, bool can_use_index, bool defaulted)
    {   if (SCHEME == scheme) return url_scheme < SCHEME > :: absolute (component, can_use_index, defaulted);
        return ::std::string (); } };
