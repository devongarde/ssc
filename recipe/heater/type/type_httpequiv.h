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
#include "type/type_enum.h"

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content);
vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args = 2, const ::std::size_t max_args = 2);

template < > struct type_master < t_content_type > : tidy_string < t_content_type >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_content_type > :: set_value (nits, v, s);
        if (tidy_string < t_content_type > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_content_type > :: get_string ()));
            if (sides.size () > 0)
            {   if (! compare_no_case (sides.at (0), "text/html"))
                    nits.pick (nit_text_html_expected, es_error, ec_type, "content type should be 'text/html;charset=...'");
                if (sides.size () == 1)
                    nits.pick (nit_charset_missing, es_error, ec_type, "the charset is missing");
                else
                {   ::std::string ss (trim_the_lot_off (sides.at (1)));
                    ::std::string::size_type pos = ss.find ('=');
                    if ((pos != ::std::string::npos) && compare_no_case (ss.substr (0, pos), "charset"))
                    {   type_master < t_charset > cs;
                        cs.set_value (nits, v, ss.substr (pos+1));
                        if (cs.good ()) return; } }
            tidy_string < t_content_type > :: status (s_invalid); } } } };

template < > struct type_master < t_refresh > : tidy_string < t_refresh >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_refresh > :: set_value (nits, v, s);
        if (tidy_string < t_refresh > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_refresh > :: get_string ()));
            if (sides.size () > 0)
            {   if (! compare_no_case (sides.at (0), "0"))
                    nits.pick (nit_text_html_expected, ed_w3, "https://www.w3.org/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use refresh with any period but zero, to avoid causing some users significant problems");
                if (sides.size () == 1)
                    nits.pick (nit_url_empty, es_error, ec_type, "the url is missing");
                else
                {   ::std::string x (trim_the_lot_off (sides.at (1)));
                    if (x.length () < 5 || ! compare_no_case (x.substr (0, 4), "url="))
                        nits.pick (nit_url_empty, es_error, ec_type, "the url, if present, must be preceded by 'url='");
                    else
                    {   url u (nits, v, x.substr (0, 5));
                        if (! u.invalid ())
                        {   string_value < t_refresh > :: set_value (nits, v, u.original ()); return; } } } }
             tidy_string < t_refresh > :: status (s_invalid); } } };

template < > struct type_master < t_location > : tidy_string < t_location >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_location > :: set_value (nits, v, s);
        if (tidy_string < t_location > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_location > :: get_string ()));
            if (sides.size () > 0)
            {   if (! compare_no_case (sides.at (0), "0"))
                    nits.pick (nit_text_html_expected, ed_w3, "https://www.w3.org/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use location with any period but zero, to avoid causing some users significant problems");
                if (sides.size () == 1)
                    nits.pick (nit_url_empty, es_error, ec_type, "the url is missing");
                else
                {   url u (nits, v, trim_the_lot_off (sides.at (2)));
                    if (! u.invalid ()) { string_value < t_location > :: set_value (nits, v, u.original ()); return; } } }
             tidy_string < t_location > :: status (s_invalid); } } };

template < > struct type_master < t_x_ua_compatible > : tidy_string < t_x_ua_compatible >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_x_ua_compatible > :: set_value (nits, v, s);
        if (! compare_no_case (tidy_string < t_x_ua_compatible > :: get_string (), "IE=edge"))
        {   tidy_string < t_x_ua_compatible > :: status (s_invalid);
            nits.pick (nit_x_ua_compatible, es_error, ec_type, quote (s), ": only 'IE=edge' is valid"); } } };
