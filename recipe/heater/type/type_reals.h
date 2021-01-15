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

template < > struct type_master < t_2pt > : tidy_string < t_2pt >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_filter_res > : tidy_string < t_filter_res >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_filter_res > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_filter_res > :: get_string ();
        if (tidy_string < t_filter_res >  :: good ())
            if ((v.svg () == sv_1_0) && (test_reals (nits, v, ss, 2))) return;
            else if (test_reals (nits, v, ss, 1, false, 2)) return;
        nits.pick (nit_unreal, es_error, ec_type, quote (ss), " is not a width height pair");
        tidy_string < t_filter_res > :: status (s_invalid); } };

template < > struct type_master < t_points > : tidy_string < t_points >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_points > :: set_value (nits, v, s);
        if (tidy_string < t_points >  :: good ())
            if (test_reals (nits, v, tidy_string < t_points > :: get_string (), 0, true)) return;
        nits.pick (nit_unreal, es_error, ec_type, "a sequence of coordinates is expected");
        tidy_string < t_points > :: status (s_invalid); } };

template < > struct type_master < t_real_1_2 > : tidy_string < t_real_1_2 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_real_1_2 > :: set_value (nits, v, s);
        if (tidy_string < t_real_1_2 >  :: good ())
            if ((v.svg () == sv_1_1) && test_reals (nits, v, tidy_string < t_real_1_2 > :: get_string (), 1)) return;
            else if ((v.svg () > sv_1_1) && test_reals (nits, v, tidy_string < t_real_1_2 > :: get_string (), 1, false, 2)) return;
        nits.pick (nit_unreal, es_error, ec_type, "one or two numbers expected");
        tidy_string < t_real_1_2 > :: status (s_invalid); } };

template < > struct type_master < t_table_values > : tidy_string < t_table_values >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_table_values > :: set_value (nits, v, s);
        if (tidy_string < t_table_values >  :: good ())
            if (test_reals (nits, v, tidy_string < t_table_values > :: get_string (), 0)) return;
        nits.pick (nit_unreal, es_error, ec_type, "a sequence of measurements is expected");
        tidy_string < t_table_values > :: status (s_invalid); } };

template < > struct type_master < t_svg_viewbox > : tidy_string < t_svg_viewbox >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "none")) type_master < t_svg_viewbox > :: status (s_good);
        else
        {   tidy_string < t_svg_viewbox > :: set_value (nits, v, s);
            if (tidy_string < t_svg_viewbox >  :: good ())
                if (test_reals (nits, v, tidy_string < t_svg_viewbox > :: get_string (), 4)) return;
            nits.pick (nit_bad_2pt, es_error, ec_type, "'none' or a list of numbers is expected");
            tidy_string < t_svg_viewbox > :: status (s_invalid); } } };
