/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "type/type_core.h"

::std::string make_tidy (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ()) return s;
    const bool untidy_start = ::std::iswspace (s.at (0));
    const bool untidy_end = ::std::iswspace (s.at (s.length () - 1));
    if (untidy_start && untidy_end)
    {   if (::std::find_if_not (s.cbegin (), s.cend (), ::std::iswspace) == s.cend ())
            return ::std::string ();
        nits.pick (nit_untidy_string, es_comment, ec_attribute, quote (s), " starts and ends with spaces"); }
    else if (untidy_start)
        nits.pick (nit_untidy_string, es_comment, ec_attribute, quote (s), " starts with one or more spaces");
    else if (untidy_end)
        nits.pick (nit_untidy_string, es_comment, ec_attribute, quote (s), " ends with one or more spaces");
    else return s;
    return trim_the_lot_off (s); }
