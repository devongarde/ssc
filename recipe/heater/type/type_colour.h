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
#include "type/type_enum.h"

template < > struct type_master < t_colour > : tidy_string < t_colour >
{   using tidy_string < t_colour > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_colour > :: set_value (nits, v, s);
        if (tidy_string < t_colour > :: good ())
        {   const ::std::string& val (tidy_string < t_colour > :: get_string ());
            const ::std::string::size_type len = val.length ();
            if ((len == 7) && (val.at (0) == '#') && (val.substr (1).find_first_not_of (HEX) == ::std::string::npos)) return;
            if ((len == 4) && (val.at (0) == '#') && ((v.svg () >= sv_1_0) || v.has_css ()) && (val.substr (1).find_first_not_of (HEX) == ::std::string::npos)) return;
            if ((len > 5) && (val.at (len - 1) == ')') && compare_no_case (val.substr (0, 4), "rgb("))
            {   if ((v.svg () < sv_1_0) && ! v.has_css ())
                    nits.pick (nit_svg_version, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (val), ": rgb (...) colour syntax requires SVG 1.1 or better, or CSS.");
                else
                {   const ::std::string x (val.substr (0, val.length () - 1).substr (4));
                    vstr_t nums (split_by_charset (x, ","));
                    if (nums.size () == 3)
                    {   int perky = 0, jollybon = 0;
                        for (::std::size_t i = 0; i < nums.size (); ++i)
                        {   const ::std::string::size_type ssl = nums.at (i).length ();
                            if (! nums.at (i).empty ()) if (nums.at (i).at (ssl - 1) == '%')
                            {   ++perky;
                                nums.at (i) = nums.at (i).substr (0, nums.at (i).length () - 1); } }
                        if ((perky != 0) && (perky != 3))
                            nits.pick (nit_bad_rgb, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (val), ": rgb colours must be all relative or all absolute, the two cannot be mixed");
                        else for (auto ss : nums)
                        {   const double d = lexical < double > :: cast (ss);
                            if (d < 0.0)
                                nits.pick (nit_bad_rgb, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (ss), ": rgb colours cannot be negative");
                            else if ((perky > 0) && (d > 100.0))
                                nits.pick (nit_bad_rgb, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (ss), ": percentages must lie between 0 and 100");
                            else if ((perky == 0) && (d > 255))
                                nits.pick (nit_bad_rgb, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (ss), ": absolute values must lie between 0 and 255");
                            else ++jollybon; }
                        if (jollybon == 3) return; } } }
            else
            {   if (v.css_version () >= css_1)
                {   type_master < t_css_colour > cc;
                    cc.set_value (nits, v, val);
                    if (cc.good ()) return; }
                type_master < t_fixedcolour > fix;
                fix.set_value (nits, v, val);
                if (fix.good ()) return; } }
        if ((v.svg () >= sv_1_0) || (v.css_version () != css_none))
            nits.pick (nit_bad_colour, es_error, ec_type, quote (s), " is neither '#' followed by 3 or 6 hexadecimal digits, nor a valid rgb, nor a standard colour name");
        else nits.pick (nit_bad_colour, es_error, ec_type, quote (s), " is neither '#' followed by 6 hexadecimal digits, nor a valid rgb, nor a standard colour name");
        tidy_string < t_colour > :: status (s_invalid); } };
