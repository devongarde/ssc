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

void compare_validate (nitpick& nits, const html_version& v, const ::std::string& naam, const ::std::string& s)
{   if (v.xhtml () && (naam != s) && compare_no_case (naam, s))
        if (naam.find_first_of (UPPERCASE) != ::std::string::npos)
            nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, quote (s), ": enumerations must have matching case in ", v.report (), " (", quote (naam), ")");
        else nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, quote (s), ": enumerations must be lower cased in ", v.report (), " (", quote (naam), ")"); }

bool compare_complain (nitpick& nits, const html_version& v, const char* lhs, const ::std::string& rhs)
{   if (! compare_no_case (lhs, rhs)) return false;
    compare_validate (nits, v, lhs, rhs);
    return true; }
