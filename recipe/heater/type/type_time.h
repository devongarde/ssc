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

bool verify_time_4 (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_time_5 (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_absolute (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_duration (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_svg_duration (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_month (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_local_datetime (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_timezone (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_week (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_plain_date (nitpick& nits, const html_version& v, const ::std::string& s);
bool verify_coarse_time (nitpick& nits, const html_version& v, const ::std::string& s);

template < > struct type_master < t_datetime_4 > : tidy_string < t_datetime_4 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_datetime_4 > :: set_value (nits, v, s);
        if (! tidy_string < t_datetime_4 > :: good ()) return;
        if (! verify_time_4 (nits, v, tidy_string < t_datetime_4 > :: get_string ()))
            tidy_string < t_datetime_4 > :: status (s_invalid); } };

template < > struct type_master < t_datetime_5 > : public tidy_string < t_datetime_5 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_datetime_5 > :: set_value (nits, v, s);
        if (! tidy_string < t_datetime_5 > :: good ()) return;
        if (! verify_time_5 (nits, v, tidy_string < t_datetime_5 > :: get_string ()))
            tidy_string < t_datetime_5 > :: status (s_invalid); } };

template < > struct type_master < t_datetime_absolute > : public tidy_string < t_datetime_absolute >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_datetime_absolute > :: set_value (nits, v, s);
        if (! tidy_string < t_datetime_absolute > :: good ()) return;
        if (! verify_absolute (nits, v, tidy_string < t_datetime_absolute > :: get_string ()))
            tidy_string < t_datetime_absolute > :: status (s_invalid); } };

template < > struct type_master < t_datetime_local > : public tidy_string < t_datetime_local >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_datetime_local > :: set_value (nits, v, s);
        if (! tidy_string < t_datetime_local > :: good ()) return;
        if (! verify_local_datetime (nits, v, tidy_string < t_datetime_local > :: get_string ()))
            tidy_string < t_datetime_local > :: status (s_invalid); } };

template < > struct type_master < t_duration > : public tidy_string < t_duration >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_duration > :: set_value (nits, v, s);
        if (! tidy_string < t_duration > :: good ()) return;
        if (! verify_duration (nits, v, tidy_string < t_duration > :: get_string ()))
            tidy_string < t_duration > :: status (s_invalid); } };

template < > struct type_master < t_datetime > : public tidy_string < t_datetime >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_datetime > :: set_value (nits, v, s);
        const ::std::string& ss (tidy_string < t_datetime > :: get_string ());
        if (! tidy_string < t_datetime > :: good ()) return;
        if (v.is_5 ())
        { if (verify_time_5 (nits, v, ss)) return; }
        else if (verify_time_4 (nits, v, ss)) return;
        tidy_string < t_datetime > :: status (s_invalid); } };

template < > struct type_master < t_just_date > : public tidy_string < t_just_date >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_just_date > :: set_value (nits, v, s);
        if (! tidy_string < t_just_date > :: good ()) return;
        if (v.is_4_or_more ())
        { if (verify_plain_date (nits, v, tidy_string < t_just_date > :: get_string ())) return; }
        tidy_string < t_just_date > :: status (s_invalid); } };

template < > struct type_master < t_just_time > : public tidy_string < t_just_time >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_just_time > :: set_value (nits, v, s);
        if (! tidy_string < t_just_time > :: good ()) return;
        if (v.is_4_or_more ())
        { if (verify_coarse_time (nits, v, tidy_string < t_just_time > :: get_string ())) return; }
        tidy_string < t_just_time > :: status (s_invalid); } };

template < > struct type_master < t_month > : public tidy_string < t_month >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_month > :: set_value (nits, v, s);
        if (! tidy_string < t_month > :: good ()) return;
        if (! verify_month (nits, v, tidy_string < t_month > :: get_string ()))
            tidy_string < t_month > :: status (s_invalid); } };

template < > struct type_master < t_week > : public tidy_string < t_week >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_week > :: set_value (nits, v, s);
        if (! tidy_string < t_week > :: good ()) return;
        if (! verify_week (nits, v, tidy_string < t_week > :: get_string ()))
            tidy_string < t_week > :: status (s_invalid); } };

template < > struct type_master < t_tz > : public tidy_string < t_tz >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_tz > :: set_value (nits, v, s);
        if (! tidy_string < t_tz > :: good ()) return;
        if (v.mjr () < 4) return;
        if (! verify_timezone (nits, v, tidy_string < t_tz > :: get_string ()))
            tidy_string < t_tz > :: status (s_invalid); } };

template < > struct type_master < t_svg_duration > : public tidy_string < t_svg_duration >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_duration > :: set_value (nits, v, s);
        if (! tidy_string < t_svg_duration > :: good ()) return;
        if (! verify_svg_duration (nits, v, tidy_string < t_svg_duration > :: get_string ()))
            tidy_string < t_svg_duration > :: status (s_invalid); } };

