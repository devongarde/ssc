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
#include "type/type_numeric.h"

#ifdef SMALLINT
bool mad_max (nitpick& , const html_version& , const int )
{   return true; }
#else // X32
bool mad_max (nitpick& nits, const html_version& , const int val)
{   if (val < 2147483647) return true;
    nits.pick (nit_out_of_range, ed_svg_1_0, "4.1 Basic data types", es_warning, ec_type, "some browsers may find ", quote (::boost::lexical_cast < ::std::string > (val)), " too high to handle");
    return false; }
#endif // X32

#ifdef SMALLINT
bool within_integer_limits (nitpick& , const html_version& , const int )
{   return true; }
#else // SMALLINT
bool within_integer_limits (nitpick& nits, const html_version& v, const int val)
{   if (val > -2147483648) return mad_max (nits, v, val);
    nits.pick (nit_out_of_range, ed_svg_1_0, "4.1 Basic data types", es_warning, ec_type, "some browsers may find ", quote (::boost::lexical_cast < ::std::string > (val)), " too low to handle");
    return false; }
#endif // SMALLINT

bool within_unsigned_limits (nitpick& nits, const html_version& v, const int val)
{   if (val >= 0) return mad_max (nits, v, val);
    nits.pick (nit_out_of_range, es_error, ec_type, quote (::boost::lexical_cast < ::std::string > (val)), " cannot be negative");
    return false; }

bool within_real_limits (nitpick& nits, const html_version& , const double val)
{   if (val < -3.4e+38F)
        nits.pick (nit_out_of_range, ed_svg_1_0, "4.1 Basic data types", es_warning, ec_type, "some browsers may find ", quote (::boost::lexical_cast < ::std::string > (val)), " too low to handle");
    else if (val > 3.4e+38F)
        nits.pick (nit_out_of_range, ed_svg_1_0, "4.1 Basic data types", es_warning, ec_type, "some browsers may find ", quote (::boost::lexical_cast < ::std::string > (val)), " too high to handle");
    else return true;
    return false; }
