/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_reals.h"

bool test_reals (nitpick& nits, const html_version& v, const ::std::string& s, const ::std::size_t expected, const bool pts, const int max)
{   vstr_t args (split_by_comma_space (trim_the_lot_off (s)));
    if (expected == 0)
    {   if (pts)
            if (args.size () % 2 != 0)
            {   nits.pick (nit_unreal, es_error, ec_type, "an even quantity of real numbers expected, but ", args.size (), " found");
                return false; } }
    else if (args.size () < expected)
    {   nits.pick (nit_unreal, es_error, ec_type, "at least ", expected, " real numbers expected, but ", args.size (), " found");
        return false; }
    else if ((max > 0) && (args.size () > static_cast < size_t > (max)))
    {   nits.pick (nit_unreal, es_error, ec_type, "at most ", max, " real numbers expected, but ", args.size (), " found");
        return false; }
    else if ((max == 0) && (args.size () != expected))
    {   nits.pick (nit_unreal, es_error, ec_type, "precisely ", expected, " real numbers expected, but ", args.size (), " found");
        return false; }
    for (auto arg : args)
    {   type_master < t_measure > m;
        m.set_value (nits, v, arg);
        if (! m.good ()) return false; }
    return true; }
