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
#include "type/type_master.h"

template < > struct type_master < t_measure > : tidy_string < t_measure > // verify against HTML 5.0, 2.4.4.4
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure > :: set_value (nits, v, s);
        if (! tidy_string < t_measure > :: empty ())
            if (tidy_string < t_measure > :: good ())
            {   const ::std::string& ss = tidy_string < t_measure > :: get_string ();
                ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos == ::std::string::npos) return;
                ::std::string units (ss.substr (pos));
                if (units.length () == 1)
                {   if ((units [0] == '%') || (units [0] == '*')) return; }
                else
                switch (units.length ())
                    {   case 2 :
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
                                    if ((units [1] == 'i') || (units [1] == 't') || (units [1] == 'x')) return;
                                    break;
                                default :
                                    break; }
                            break;
                        case 3 :
                            if (units == "dpi") return;
                            break;
                        case 4 :
                            if (units == "dpcm") return;
                            break;
                        default :
                            break; } }
        nits.pick (nit_immeasurable, es_error, ec_type, quote (s), ": a length is an integer or a real, optionally followed immediately by one of '%', '*', 'cm', 'dpi', 'dpcm', 'em', 'in', 'mm', 'pt', 'pi', or 'px'");
        tidy_string < t_measure > :: status (s_invalid); } };

template < > struct type_master < t_measures > : type_at_least_none < t_measures, sz_comma, t_measure > { };
template < > struct type_master < t_measure_i > : type_or_string < t_measure_i, t_measure, sz_inherit > { };
template < > struct type_master < t_measure_ai > : type_or_either_string < t_measure_ai, t_measure, sz_auto, sz_inherit > { };
template < > struct type_master < t_refx > : type_or_any_string < t_refx, t_measure, sz_left, sz_centre, sz_right > { };
template < > struct type_master < t_refy > : type_or_any_string < t_refy, t_measure, sz_top, sz_centre, sz_bottom > { };
