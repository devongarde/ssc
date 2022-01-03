/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "type/type_master.h"

template < > struct type_master < t_measure > : tidy_string < t_measure > // verify against HTML 5.0, 2.4.4.4
{   using tidy_string < t_measure > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_length; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure > :: set_value (nits, v, s);
        if (tidy_string < t_measure > :: good ())
        {   ::std::string ss = tidy_string < t_measure > :: get_string ();
            if (! ss.empty ())
            {   ::std::string units;
                const ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos != ::std::string::npos)
                {   units = ss.substr (pos);
                    ss = ss.substr (0, pos); }
                if (test_value < t_fixedpoint > (nits, v, ss))
                {   if (units.empty ()) return;
                    if ((v >= html_2) && (units == "%")) return;
                    if ((v >= html_4_0) && (units == "*")) return;
                    if (v.svg () || v.is_5 ()) if (test_value < t_unit > (nits, v, units)) return; } } }   // dpi, dpcm?
        nits.pick (nit_immeasurable, es_error, ec_type, quote (s), " should be a number optionally followed immediately by '%', '*', or a standard unit of measurement");
        tidy_string < t_measure > :: status (s_invalid); } };

template < > struct type_master < t_measures > : type_at_least_none < t_measures, sz_space_comma, t_measure >
{ using type_at_least_none < t_measures, sz_space_comma, t_measure > :: type_at_least_none; };

template < > struct type_master < t_measure_i > : type_or_string < t_measure_i, t_measure, sz_inherit >
{ using type_or_string < t_measure_i, t_measure, sz_inherit > :: type_or_string; };

template < > struct type_master < t_measure_a > : type_or_string < t_measure_a, t_measure, sz_auto >
{ using type_or_string < t_measure_a, t_measure, sz_auto > :: type_or_string; };

template < > struct type_master < t_measure_ai > : type_or_either_string < t_measure_ai, t_measure, sz_auto, sz_inherit >
{ using type_or_either_string < t_measure_ai, t_measure, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_measure_ni > : type_or_either_string < t_measure_ai, t_measure, sz_normal, sz_inherit >
{ using type_or_either_string < t_measure_ai, t_measure, sz_normal, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_refx > : type_or_any_string < t_refx, t_measure, sz_left, sz_centre, sz_right >
{ using type_or_any_string < t_refx, t_measure, sz_left, sz_centre, sz_right > :: type_or_any_string; };

template < > struct type_master < t_refy > : type_or_any_string < t_refy, t_measure, sz_top, sz_centre, sz_bottom >
{ using type_or_any_string < t_refy, t_measure, sz_top, sz_centre, sz_bottom > :: type_or_any_string; };

