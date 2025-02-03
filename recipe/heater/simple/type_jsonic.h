/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "base/type_master.h"
#include "simple/type_autocomplete.h"

e_status set_js_value (nitpick& nits, const html_version& v, const ::std::string& s);
#ifdef NO_JSONIC
inline e_status parse_json (nitpick& , const html_version& , const ::std::string& ) { return s_good; }
#else // NO_JSONIC
e_status parse_json (nitpick& nits, const html_version& v, const ::std::string& s);
#endif // NO_JSONIC

template < > struct type_master < t_js_term > : tidy_string < t_js_term >
{   using tidy_string < t_js_term > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_js_term > :: set_value (nits, v, s);
        tidy_string < t_js_term > :: status (set_js_value (nits, v, tidy_string < t_js_term > :: get_string ())); } };

template < > struct type_master < t_json > : tidy_string < t_json >
{   using tidy_string < t_json > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_json > :: set_value (nits, v, s);
        tidy_string < t_json > :: status (parse_json (nits, v, tidy_string < t_json > :: get_string ())); } };
