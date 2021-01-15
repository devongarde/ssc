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
#include "type/type_enum.h"

bool is_default_role (const html_version& v, const e_element elem, const e_aria_role role);
bool is_permitted_role (const html_version& v, const e_element elem, const e_aria_role role);

template < > inline void enum_n < t_role, e_aria_role > :: validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
{   if (v >= html_5_0)
        if (is_default_role (v, e.get (), enum_base < e_aria_role, t_role > :: value_))
            nits.pick (nit_default_role, es_error, ec_type, "do not specify the default role");
        else if (! is_permitted_role (v, e.get (), enum_base < e_aria_role, t_role > :: value_))
            nits.pick (nit_default_role, es_error, ec_type, quote (enum_base < e_aria_role, t_role > :: get_string ()), " is not permitted here"); }

template < > inline void enum_n < t_role, e_aria_role > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s);
    enum_base < e_aria_role, t_role > :: original_ = s;
    if (v < html_4_0)
    {   enum_base < e_aria_role, t_role > :: value_ = default_value ();
        if (s.empty ()) enum_base < e_aria_role, t_role > :: status (s_empty);
        else enum_base < e_aria_role, t_role > :: status (s_good);
        return; }
    if (v.xhtml () && ! v.svg () && (s.find_first_of (UPPERCASE) != ::std::string::npos))
        nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, "enumerations must be lower cased in ", v.report ());
    ::std::string t (s);
    e_namespace n (examine_namespace (nits, v, t));
    if (symbol < e_aria_role > :: parse (nits, v, s, n))
    {   enum_base < e_aria_role, t_role > :: value_ = symbol < e_aria_role > :: get ();
        const html_version f = symbol < e_aria_role > :: first ();
        if (! may_apply (v, f, symbol < e_aria_role > :: last ()))
            nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ());
        else if (f.reject ())
            nits.pick (nit_rejected, es_error, ec_type, quote (s), " is valid but incompatible with ", v.report ());
        else
        {   if (f.deprecated (v)) nits.pick (nit_deprecated_value, es_warning, ec_type, quote (s), " is deprecated in ", v.report ());
            enum_base < e_aria_role, t_role > :: status (s_good);
            enum_base < e_aria_role, t_role > :: post_set_value (nits, v);
            return; } }
    else
    {   check_spelling (nits, v, t);
        nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here"); }
    enum_base < e_aria_role, t_role > :: status (s_invalid); }
