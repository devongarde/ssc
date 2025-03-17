/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "enum/type_enum.h"
#include "base/type_case.h"
#include "spell/spell.h"

typedef ssc_bitset < e_aria_role, last_role > role_bitset;
extern const role_bitset empty_role_bitset;
extern role_bitset abstract_role_bitset;
extern role_bitset application_role_bitset;
extern role_bitset adii_role_bitset;
extern role_bitset adiinp_role_bitset;
extern role_bitset glnp_role_bitset;
extern role_bitset gnp_role_bitset;
extern role_bitset listitem_role_bitset;
extern role_bitset no_form_role_bitset;
extern role_bitset no_hf_role_bitset;
extern role_bitset no_main_role_bitset;
extern role_bitset no_meter_role_bitset;
extern role_bitset no_progress_role_bitset;
extern role_bitset no_tabindex_role_bitset;
extern role_bitset no_table_role_bitset;
extern role_bitset none_pres_role_bitset;

void aria_init ();
bool is_default_role (const html_version& v, const e_element elem, const e_aria_role role);
bool is_permitted_role (const html_version& v, const e_element elem, const e_aria_role role);
e_aria_role furq_at (const e_aria_role& parent, const ::std::size_t n);
::std::string rpt_role_bitset (const role_bitset& rb);

template < > inline void enum_n < t_role, e_aria_role > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
{   if (v >= html_5_0)
    {   const e_aria_role r = enum_base < e_aria_role, t_role > :: value_;
        if (is_default_role (v, e, r))
            nits.pick (nit_default_role, es_error, ec_aria, "do not specify the default role");
        else if (abstract_role_bitset.test (r))
            nits.pick (nit_bad_role, ed_aria_1_0, "5.2.1 Abstract Roles", es_error, ec_aria, "Content authors MUST NOT use abstract roles");
        else if (! is_permitted_role (v, e.get (), r))
            nits.pick (nit_bad_role, es_error, ec_aria, quote (enum_base < e_aria_role, t_role > :: original ()), " is not permitted here"); } }

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
            {   f.check_status (nits, symbol < html_version, e_aria_role > :: name ());
                if (f.deprecated (v)) nits.pick (nit_deprecated_value, es_warning, ec_type, quote (pret), " is deprecated in ", v.report ());
                enum_base < e_aria_role, t_role > :: status (s_good);
                enum_base < e_aria_role, t_role > :: post_set_value (nits, v);
                return; } }
        else
        {   check_identifier_spelling (nits, v, t);
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid here"); } }
    enum_base < e_aria_role, t_role > :: status (s_invalid); }
