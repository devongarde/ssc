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
#include "base/type_master.h"

bool set_measure_value (nitpick& nits, const html_version& v, const ::std::string& ss);
bool set_css_measure_value (nitpick& nits, const html_version& v, const ::std::string& ss, const bool absolute);

template < > struct type_master < t_measure > : tidy_string < t_measure > // verify against HTML 5.0, 2.4.4.4
{   using tidy_string < t_measure > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure > :: set_value (nits, v, s);
        if (tidy_string < t_measure > :: good ())
            if (set_measure_value (nits, v, tidy_string < t_measure > :: get_string ()))
                return;
        tidy_string < t_measure > :: status (s_invalid); } };

template < > struct type_master < t_css_length > : tidy_string < t_css_length >
{   using tidy_string < t_css_length > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_length > :: set_value (nits, v, s);
        if (tidy_string < t_css_length > :: good ())
            if (set_css_measure_value (nits, v, tidy_string < t_css_length > :: get_string (), false))
                return;
        tidy_string < t_css_length > :: status (s_invalid); } };

template < > struct type_master < t_css_length_abs > : tidy_string < t_css_length_abs >
{   using tidy_string < t_css_length_abs > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_length_abs > :: set_value (nits, v, s);
        if (tidy_string < t_css_length_abs > :: good ())
            if (set_css_measure_value (nits, v, tidy_string < t_css_length_abs > :: get_string (), true))
                return;
        tidy_string < t_css_length_abs > :: status (s_invalid); } };
