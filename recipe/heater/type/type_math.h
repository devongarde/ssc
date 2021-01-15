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

template < > struct type_master < t_hunit > : tidy_string < t_hunit > // verify against HTML 5.0, 2.4.4.4
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_hunit > :: set_value (nits, v, s);
        if (! tidy_string < t_hunit > :: empty ())
            if (tidy_string < t_hunit > :: good ())
            {   const ::std::string& ss = tidy_string < t_hunit > :: get_string ();
                ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos == ::std::string::npos) return;
                ::std::string units (ss.substr (pos));
                switch (units.length ())
                {   case 1 :
                        if (units [0] == '%') return;
                        break;
                    case 2 :
                        switch (units [0])
                        {   case 'c' :
                            case 'e' :
                            case 'm' :
                                if (units [1] == 'm') return;
                                break;
                            case 'i' :
                                if (units [1] == 'n') return;
                                break;
                            case 'p' :
                                if ((units [1] == 'c') || (units [1] == 't') || (units [1] == 'x')) return;
                                break;
                            default :
                                break; } } }
        nits.pick (nit_bad_hunit, es_error, ec_type, quote (s), ": a horizontal length is an integer or a real, optionally followed immediately by one of '%', 'cm', 'em', 'in', 'mm', 'pc', 'pt', or 'px'");
        tidy_string < t_hunit > :: status (s_invalid); } };

template < > struct type_master < t_vunit > : tidy_string < t_vunit > // verify against HTML 5.0, 2.4.4.4
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_vunit > :: set_value (nits, v, s);
        if (! tidy_string < t_vunit > :: empty ())
            if (tidy_string < t_vunit > :: good ())
            {   const ::std::string& ss = tidy_string < t_vunit > :: get_string ();
                ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos == ::std::string::npos) return;
                ::std::string units (ss.substr (pos));
                switch (units.length ())
                {   case 1 :
                        if (units [0] == '%') return;
                        break;
                    case 2 :
                        switch (units [0])
                        {   case 'c' :
                            case 'm' :
                                if (units [1] == 'm') return;
                                break;
                            case 'e' :
                                if (units [1] == 'x') return;
                                break;
                            case 'i' :
                                if (units [1] == 'n') return;
                                break;
                            case 'p' :
                                if ((units [1] == 'c') || (units [1] == 't') || (units [1] == 'x')) return;
                                break;
                            default :
                                break; } } }
        nits.pick (nit_bad_vunit, es_error, ec_type, quote (s), ": a vertical length is an integer or a real, optionally followed immediately by one of '%', 'cm', 'ex', 'in', 'mm', 'pc', 'pt', or 'px'");
        tidy_string < t_vunit > :: status (s_invalid); } };

template < > struct type_master < t_vunits > : type_at_least_none < t_vunits, sz_space, t_vunit > { };

template < > struct type_master < t_pseudo > : string_vector < t_pseudo, sz_space > // verify against HTML 5.0, 2.4.4.4
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_pseudo, sz_space > :: set_value (nits, v, s);
        bool good = true;
        if (string_vector < t_pseudo, sz_space > :: good ())
            for (auto ss : string_vector < t_pseudo, sz_space > :: get ())
            {   ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos == ::std::string::npos) continue;
                if (compare_no_case (ss, "depth")) continue;
                if (compare_no_case (ss, "height")) continue;
                if (compare_no_case (ss, "lspace")) continue;
                if (compare_no_case (ss, "width")) continue;
                ::std::string units (ss.substr (pos));
                switch (units.length ())
                {   case 1 :
                        if (units [0] == '%') continue;
                        break;
                    case 2 :
                        switch (units [0])
                        {   case 'c' :
                            case 'm' :
                                if (units [1] == 'm') continue;
                                break;
                            case 'e' :
                                if ((units [1] == 'x') || (units [1] == 'm')) continue;
                                break;
                            case 'i' :
                                if (units [1] == 'n') continue;
                                break;
                            case 'p' :
                                if ((units [1] == 'c') || (units [1] == 't') || (units [1] == 'x')) continue;
                                break;
                            default :
                                break; } }
                good = false; break; }
        if (good) return;
        nits.pick (nit_bad_vunit, es_error, ec_type, quote (s), ": expecting a measurement, and/or maybe 'depth', 'height', 'lspace' or 'width'");
        string_vector < t_pseudo, sz_space > :: status (s_invalid); } };
