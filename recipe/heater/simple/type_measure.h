/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

template < > struct type_master < t_measure > : tidy_string < t_measure > // verify against HTML 5.0, 2.4.4.4
{   using tidy_string < t_measure > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure > :: set_value (nits, v, s);
        if (tidy_string < t_measure > :: good ())
        {   ::std::string ss = tidy_string < t_measure > :: get_string ();
            if (! ss.empty ())
            {   ::std::string units;
                const ::std::string::size_type pos = ss.find_first_not_of (SIGNEDDECIMAL " ");
                if (pos != ::std::string::npos)
                {   units = ss.substr (pos);
                    ss = ss.substr (0, pos); }
                if ((! ss.empty ()) && test_value < t_fixedpoint > (nits, v, ss))
                {   if (units.empty ()) return;
                    if ((v >= html_2) && (units == "%")) return;
                    if ((v >= html_4_0) && (units == "*")) return;
                    if (v.svg () || v.is_5 () || v.has_css ())
                        if (test_value < t_unit > (nits, v, units))
                            return; } } }   // dpi, dpcm?
        nits.pick (nit_immeasurable, es_error, ec_type, quote (s), " should be a number optionally followed immediately by '%', '*', or a standard unit of measurement");
        tidy_string < t_measure > :: status (s_invalid); } };

template < > struct type_master < t_css_length > : tidy_string < t_css_length >
{   using tidy_string < t_css_length > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_length > :: set_value (nits, v, s);
        if (tidy_string < t_css_length > :: good ())
        {   ::std::string ss = tidy_string < t_css_length > :: get_string ();
            if (! ss.empty ())
            {   ::std::string units;
                if (ss == "0") return;
                const ::std::string::size_type pos = ss.find_first_not_of (SIGNEDDECIMAL " ");
                if (pos != ::std::string::npos)
                {   units = ss.substr (pos);
                    ss = ss.substr (0, pos);
                    if (ss.empty ())
                    {   nits.pick (nit_missing_value, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_type, quote (s), ": got the units but not how many");
                        tidy_string < t_css_length > :: status (s_invalid); } }
                else
                {   nits.pick (nit_missing_units, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_type, quote (s), ": units must be specified for lengths");
                    tidy_string < t_css_length > :: status (s_invalid); }
                if (test_value < t_fixedpoint > (nits, v, ss))
                {   if (units.empty ()) return;
                    if (units == "%") return;
                    if (v.svg () || v.is_5 () || v.has_css ()) if (test_value < t_unit > (nits, v, units)) return; } } }
        nits.pick (nit_immeasurable, es_error, ec_type, quote (s), ": a length is a number immediately followed a standard unit of measurement");
        tidy_string < t_css_length > :: status (s_invalid); } };

