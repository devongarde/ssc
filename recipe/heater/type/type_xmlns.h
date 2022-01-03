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
#include "type/type_enum.h"
#include "type/type_case.h"

template < > inline void enum_n < t_namespace, e_namespace > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string pret (trim_the_lot_off (s));
    ::std::string t (case_must_match < false >::lower (pret));
    enum_base < e_namespace, t_namespace > :: original_ = s;
    html_version from, to;
    if (symbol < html_version, e_namespace > :: parse (nits, v, t, enum_base < e_namespace, t_namespace > :: value_, ns_default, &from, &to))
    {   compare_validate (nits, v, get_string (), pret);
        if (may_apply (v, from, to))
        {   enum_base < e_namespace, t_namespace > :: status (s_good);
            enum_base < e_namespace, t_namespace > :: post_set_value (nits, v);
            return; }
        v.check_math_svg (nits, from, name ());
        nits.pick (nit_wrong_version, es_error, ec_type, quote (pret), " is invalid here in ", v.report ()); }
    else
    {   check_spelling (nits, v, t);
        nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid here"); }
    enum_base < e_namespace, t_namespace > :: status (s_invalid); }

template < > inline void enum_n < t_xmlns, e_xmlns > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_base < e_xmlns, t_xmlns > :: original_ = s;
    ::std::string t (::boost::to_lower_copy (trim_the_lot_off (s)));
    html_version from, to;
    if (symbol < html_version, e_xmlns > :: parse (nits, v, t, enum_base < e_xmlns, t_xmlns > :: value_, ns_default, &from, &to))
    {   if (may_apply (v, from, to))
        {   enum_base < e_xmlns, t_xmlns > :: status (s_good);
            enum_base < e_xmlns, t_xmlns > :: post_set_value (nits, v);
            return; }
        v.check_math_svg (nits, from, name ());
        nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ()); }
    else nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here");
    enum_base < e_xmlns, t_xmlns > :: status (s_invalid); }
