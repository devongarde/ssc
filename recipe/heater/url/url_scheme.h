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
#include "url/url_protocol.h"

bool equivalent_rfc3986 (const vc_t& lhs, const vc_t& rhs);
bool parse_rfc3986 (nitpick& nits, const html_version& v, const e_protocol prot, const ::std::string& s, vc_t& component);
::std::string get_rfc3986 (const vc_t& component, bool defaulted);
::std::string absolute_rfc3986 (const vc_t& component, bool can_use_index, bool defaulted);

template < e_scheme SCHEME > struct url_scheme
{   static bool equivalent (const vc_t& lhs, const vc_t& rhs);
    static bool parse (nitpick& nits, const html_version& v, const e_protocol prot, const ::std::string& url, vc_t& component);
    static bool is_valid (const vc_t& component, bool defaulted);
    static ::std::string get (const vc_t& component, bool defaulted);
    static ::std::string absolute (const vc_t& component, bool can_use_index, bool defaulted); };

template < e_scheme SCHEME > inline bool url_scheme < SCHEME > :: equivalent (const vc_t& lhs, const vc_t& rhs)
{   return equivalent_rfc3986 (lhs, rhs); }
template < e_scheme SCHEME > inline bool url_scheme < SCHEME > :: parse (nitpick& nits, const html_version& v, const e_protocol prot, const ::std::string& s, vc_t& component)
{   return parse_rfc3986 (nits, v, prot, s, component); }
template < e_scheme SCHEME > inline bool url_scheme < SCHEME > :: is_valid (const vc_t& component, bool defaulted)
{   return (defaulted || ! component.at (es_original).empty ()); }
template < e_scheme SCHEME > inline ::std::string url_scheme < SCHEME > :: get (const vc_t& component, bool )
{   return component.at (es_original); }
template < e_scheme SCHEME > inline ::std::string url_scheme < SCHEME > :: absolute (const vc_t& component, bool , bool )
{   return component.at (es_original); }

template < > inline bool url_scheme < pt_rfc3986 > :: is_valid (const vc_t& component, bool defaulted)
{   return (defaulted && ! component.at (es_original).empty ()) || ! component.at (es_server).empty (); }
template < > inline ::std::string url_scheme < pt_rfc3986 > :: get (const vc_t& component, bool defaulted)
{   return get_rfc3986 (component, defaulted); }
template < > inline ::std::string url_scheme < pt_rfc3986 > :: absolute (const vc_t& component, bool can_use_index, bool defaulted)
{   return absolute_rfc3986 (component, can_use_index, defaulted); }
