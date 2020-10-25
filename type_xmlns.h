/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type_enum.h"

e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s);
e_namespace xmlns_to_namespace (nitpick& nits, const html_version& v, const e_xmlns x);

template < > inline void enum_n < t_namespace, e_namespace > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s);
    enum_base < e_namespace, t_namespace > :: original_ = s;
    if (v.xhtml () && ! v.svg () && (s.find_first_of (UPPERCASE) != ::std::string::npos))
        nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, "enumerations must be lower cased in ", v.report ());
    ::std::string t (::boost::to_lower_copy (trim_the_lot_off (s)));
    html_version from, to;
    if (symbol < e_namespace > :: parse (nits, v, t, enum_base < e_namespace, t_namespace > :: value_, ns_default, &from, &to))
    {   if (may_apply (v, from, to))
        {   enum_base < e_namespace, t_namespace > :: status (s_good);
            enum_base < e_namespace, t_namespace > :: post_set_value (nits, v);
            return; }
        nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ()); }
    else
    {   check_spelling (nits, v, t);
        nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here"); }
    enum_base < e_namespace, t_namespace > :: status (s_invalid); }

template < > inline void enum_n < t_xmlns, e_xmlns > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_base < e_xmlns, t_xmlns > :: original_ = s;
    ::std::string t (::boost::to_lower_copy (trim_the_lot_off (s)));
    html_version from, to;
    if (symbol < e_xmlns > :: parse (nits, v, t, enum_base < e_xmlns, t_xmlns > :: value_, ns_default, &from, &to))
    {   if (may_apply (v, from, to))
        {   enum_base < e_xmlns, t_xmlns > :: status (s_good);
/*            switch (get ())
            {   case x_mathml : if (! v.math ()) v.ext_set (HE_MATH_1); break;
                case x_svg : if (! v.svg ()) v.ext_set (HE_SVG_1_0); break;
                case x_xlink : if (! v.xlink ()) v.ext_set (HE_XLINK_1_0); break;
                case x_xhtml_1 : if (v.unknown ()) v = xhtml_1_0; break;
                case x_xhtml_11 : if (v.unknown ()) v = xhtml_1_1; break;
                case x_xhtml_2 : if (v.unknown ()) v = xhtml_2; break;
                default : break; } */
            enum_base < e_xmlns, t_xmlns > :: post_set_value (nits, v);
            return; }
        nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ()); }
    else nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here");
    enum_base < e_xmlns, t_xmlns > :: status (s_invalid); }
