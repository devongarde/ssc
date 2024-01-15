/*
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "type/type.h"
#include "stats/stats.h"

bool set_measure_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   ::std::string s (ss);
    if (! s.empty ())
    {   ::std::string units;
        const ::std::string::size_type pos = s.find_first_not_of (SIGNEDDECIMAL " ");
        if (pos != ::std::string::npos)
        {   units = s.substr (pos);
            s = s.substr (0, pos); }
        if ((! s.empty ()) && test_value < t_fixedpoint > (nits, v, s))
        {   if (units.empty ()) return true;
            if ((v >= html_2) && (units == "%")) return true;
            if ((v >= html_4_0) && (units == "*")) return true;
            if (v.svg () || v.is_5 () || v.has_css ())
                if (test_value < t_unit > (nits, v, units))
                    return true; } }   // dpi, dpcm?
    nits.pick (nit_immeasurable, es_error, ec_type, quote (s), " should be a number optionally followed immediately by '%', '*', or a standard unit of measurement");
    return false; }

bool set_css_measure_value (nitpick& nits, const html_version& v, const ::std::string& ss, const bool absolute)
{   ::std::string s (ss);
    if (! s.empty ())
    {   ::std::string units;
        if (s == "0") return true;
        const ::std::string::size_type pos = s.find_first_not_of (SIGNEDDECIMAL " ");
        if (pos != ::std::string::npos)
        {   units = s.substr (pos);
            s = s.substr (0, pos);
            if (s.empty ())
            {   nits.pick (nit_missing_value, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_type, quote (s), ": got the units but not how many");
                return false; } }
        else if (context.html_ver ().is_css_compatible (v.ext2 (), v.ext3 (), v.ext4 ())) return true;
        else
        {   nits.pick (nit_missing_units, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_type, quote (s), ": units must be specified for lengths");
            return false; }
        if (test_value < t_fixedpoint > (nits, v, s))
        {   if (units.empty ()) return true;
            if ((! absolute) && (units == "%")) return true;
            if (v.svg () || v.is_5 () || v.has_css ()) if (test_value < t_unit > (nits, v, units)) return true; } }
    if (absolute) nits.pick (nit_immeasurable, es_error, ec_type, quote (s), ": a length is a number immediately followed a standard unit of measurement");
    else nits.pick (nit_immeasurable, es_error, ec_type, quote (s), ": a length is a percentage or a number immediately followed a standard unit of measurement");
    return false; }
