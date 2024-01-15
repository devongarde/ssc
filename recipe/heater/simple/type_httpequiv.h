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
#include "enum/type_enum.h"
#include "type/type_csp.h"

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content, page& p);
vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args = 2, const ::std::size_t max_args = 2);
e_status set_cache_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_content_type_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& charset);
e_status set_csp_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_csp_sauce_value (nitpick& nits, const html_version& v, const ::std::string& s);
bool linkarg_set_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_linkarg_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_linkitself_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_location_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& val);
e_status set_refresh_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& val);

template < > struct type_master < t_cache > : public tidy_string < t_cache >
{   using tidy_string < t_cache > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_cache > :: set_value (nits, v, ss);
        tidy_string < t_cache > :: status (set_cache_value (nits, v, tidy_string < t_cache > :: get_string ())); } };

template < > struct type_master < t_content_type > : tidy_string < t_content_type >
{   ::std::string charset_;
    using tidy_string < t_content_type > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_content_type > :: set_value (nits, v, s);
        tidy_string < t_content_type > :: status (set_content_type_value (nits, v, tidy_string < t_content_type > :: get_string (), charset_)); }
    ::std::string get_charset () const { return charset_; } };

template < > struct type_master < t_csp_sauce > : tidy_string < t_csp_sauce >
{   using tidy_string < t_csp_sauce > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_csp_sauce > :: set_value (nits, v, s);
        tidy_string < t_csp_sauce > :: status (set_csp_sauce_value (nits, v, tidy_string < t_csp_sauce > :: get_string ())); } };

template < > struct type_master < t_csp > : tidy_string < t_csp >
{   using tidy_string < t_csp > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_csp > :: set_value (nits, v, s);
        tidy_string < t_csp > :: status (set_csp_value (nits, v, tidy_string < t_csp > :: get_string ())); } };

template < > struct type_master < t_linkarg > : public tidy_string < t_linkarg >
{   using tidy_string < t_linkarg > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_linkarg > :: set_value (nits, v, ss);
        tidy_string < t_linkarg > :: status (set_linkarg_value (nits, v, tidy_string < t_linkarg > :: get_string ())); } };

template < > struct type_master < t_linkitself > : tidy_string < t_linkitself >
{   using tidy_string < t_linkitself > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_linkitself > :: set_value (nits, v, ss);
        tidy_string < t_linkitself > :: status (set_linkitself_value (nits, v, tidy_string < t_linkitself > :: get_string ())); } };

template < > struct type_master < t_location > : tidy_string < t_location >
{   using tidy_string < t_location > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_location > :: set_value (nits, v, s);
        ::std::string val;
        tidy_string < t_location > :: status (set_location_value (nits, v, tidy_string < t_location > :: get_string (), val));
        if (tidy_string < t_location > :: status () == s_good) tidy_string < t_location > :: set_value (nits, v, val); } };

template < > struct type_master < t_refresh > : tidy_string < t_refresh >
{   using tidy_string < t_refresh > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_refresh > :: set_value (nits, v, s);
        ::std::string val;
        tidy_string < t_refresh > :: status (set_refresh_value (nits, v, tidy_string < t_refresh > :: get_string (), val));
        if (tidy_string < t_refresh > :: status () == s_good) tidy_string < t_refresh > :: set_value (nits, v, val); } };

template < > struct type_master < t_x_ua_compatible > : tidy_string < t_x_ua_compatible >
{   using tidy_string < t_x_ua_compatible > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_x_ua_compatible > :: set_value (nits, v, s);
        if (! compare_no_case (tidy_string < t_x_ua_compatible > :: get_string (), "IE=edge"))
        {   tidy_string < t_x_ua_compatible > :: status (s_invalid);
            nits.pick (nit_x_ua_compatible, es_error, ec_type, quote (s), ": only 'IE=edge' is valid"); } } };
