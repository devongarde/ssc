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
#include "type/type_case.h"

bool is_default_role (const html_version& v, const e_element elem, const e_aria_role role);
bool is_permitted_role (const html_version& v, const e_element elem, const e_aria_role role);

template < > inline void enum_n < t_role, e_aria_role > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
{   if (v >= html_5_0)
        if (is_default_role (v, e, enum_base < e_aria_role, t_role > :: value_))
            nits.pick (nit_default_role, es_error, ec_type, "do not specify the default role");
        else if (! is_permitted_role (v, e.get (), enum_base < e_aria_role, t_role > :: value_))
            nits.pick (nit_default_role, es_error, ec_type, quote (enum_base < e_aria_role, t_role > :: original ()), " is not permitted here"); }

template < > inline void enum_n < t_role, e_aria_role > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s, ::std::string& ns);
    enum_base < e_aria_role, t_role > :: original_ = s;
    if (v < html_4_0)
    {   enum_base < e_aria_role, t_role > :: value_ = default_value ();
        if (s.empty ()) enum_base < e_aria_role, t_role > :: status (s_empty);
        else enum_base < e_aria_role, t_role > :: status (s_good);
        return; }
    ::std::string pret (trim_the_lot_off (s));
    if (v <= xhtml_2)
    {   if (test_value < t_urls > (nits, v, pret))
        {   if (s.empty ()) enum_base < e_aria_role,t_role > :: status (s_empty);
            else enum_base < e_aria_role,t_role > :: status (s_good);
            return; } } // https://www.w3.org/TR/xhtml-role/
    else
    {   ::std::string t (case_must_match < false >::lower (pret));
        if (symbol < html_version, e_aria_role > :: parse (nits, v, t, ns_default))
        {   enum_base < e_aria_role, t_role > :: value_ = symbol < html_version, e_aria_role > :: get ();
            compare_validate (nits, v, get_string (), pret);
            const html_version f = symbol < html_version, e_aria_role > :: first ();
            if (! may_apply (v, f, symbol < html_version, e_aria_role > :: last ()))
            {   v.check_math_svg (nits, f, name ());
                nits.pick (nit_wrong_version, es_error, ec_type, quote (pret), " is invalid here in ", v.report ()); }
            else if (f.reject ())
                nits.pick (nit_rejected, es_error, ec_type, quote (pret), " is valid but incompatible with ", v.report ());
            else
            {   if (f.deprecated (v)) nits.pick (nit_deprecated_value, es_warning, ec_type, quote (pret), " is deprecated in ", v.report ());
                enum_base < e_aria_role, t_role > :: status (s_good);
                enum_base < e_aria_role, t_role > :: post_set_value (nits, v);
                return; } }
        else
        {   check_spelling (nits, v, t);
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid here"); } }
    enum_base < e_aria_role, t_role > :: status (s_invalid); }
