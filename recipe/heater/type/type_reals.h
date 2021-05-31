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
#include "type/type_master.h"

bool test_reals (nitpick& nits, const html_version& v, const ::std::string& s, const ::std::size_t expected, const bool pts = false, const int max = 0);

template < > struct type_master < t_pt > : tidy_string < t_pt >
{   static e_animation_type animation_type () { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_pt > :: set_value (nits, v, s);
        if (tidy_string < t_pt >  :: good ())
            if (test_reals (nits, v, tidy_string < t_pt > :: get_string (), 2)) return;
        nits.pick (nit_bad_2pt, es_error, ec_type, "two coordinates, \"x y\", are expected");
        tidy_string < t_pt > :: status (s_invalid); } };

template < > struct type_master < t_2pt > : tidy_string < t_2pt >
{   static e_animation_type animation_type () { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_2pt > :: set_value (nits, v, s);
        if (tidy_string < t_2pt >  :: good ())
            if (test_reals (nits, v, tidy_string < t_2pt > :: get_string (), 4)) return;
        nits.pick (nit_bad_2pt, es_error, ec_type, "four coordinates, \"x y width height\", are expected");
        tidy_string < t_2pt > :: status (s_invalid); } };

template < > struct type_master < t_matrix_values > : tidy_string < t_matrix_values >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_matrix_values > :: set_value (nits, v, s);
        if (tidy_string < t_matrix_values >  :: good ())
            if (test_reals (nits, v, tidy_string < t_matrix_values > :: get_string (), 20)) return;
        nits.pick (nit_unreal, es_error, ec_type, "a sequence of 20 coordinates is expected");
        tidy_string < t_matrix_values > :: status (s_invalid); } };

template < > struct type_master < t_filterres > : tidy_string < t_filterres >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_filterres > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_filterres > :: get_string ();
        if (tidy_string < t_filterres >  :: good ())
            if (test_reals (nits, v, ss, 1, false, 2)) return;
        nits.pick (nit_unreal, es_error, ec_type, quote (ss), " is not a width height pair");
        tidy_string < t_filterres > :: status (s_invalid); } };

template < > struct type_master < t_points > : tidy_string < t_points >
{   static e_animation_type animation_type () { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_points > :: set_value (nits, v, s);
        if (tidy_string < t_points >  :: good ())
            if (test_reals (nits, v, tidy_string < t_points > :: get_string (), 0, true)) return;
        nits.pick (nit_unreal, es_error, ec_type, "a sequence of coordinates is expected");
        tidy_string < t_points > :: status (s_invalid); } };

template < > struct type_master < t_tablevalues > : tidy_string < t_tablevalues >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_tablevalues > :: set_value (nits, v, s);
        if (tidy_string < t_tablevalues >  :: good ())
            if (test_reals (nits, v, tidy_string < t_tablevalues > :: get_string (), 0)) return;
        nits.pick (nit_unreal, es_error, ec_type, "a sequence of measurements is expected");
        tidy_string < t_tablevalues > :: status (s_invalid); } };
