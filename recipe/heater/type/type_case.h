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
#include "main/context.h"
#include "type/sz.h"
#include "utility/quote.h"

inline void compare_validate (nitpick& nits, const html_version& v, const ::std::string& naam, const ::std::string& s)
{   if (v.xhtml () && (naam != s) && compare_no_case (naam, s))
        if (naam.find_first_of (UPPERCASE) != ::std::string::npos)
            nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, quote (s), ": enumerations must have matching case in ", v.report (), " (", quote (naam), ")");
        else nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, quote (s), ": enumerations must be lower cased in ", v.report (), " (", quote (naam), ")"); }

inline bool compare_complain (nitpick& nits, const html_version& v, const char* lhs, const ::std::string& rhs)
{   if (! compare_no_case (lhs, rhs)) return false;
    compare_validate (nits, v, lhs, rhs);
    return true; }

inline bool compare_complain (nitpick& nits, const html_version& v, const ::std::string& lhs, const char* rhs)
{   return compare_complain (nits, v, rhs, lhs); }

template < bool CASE > struct case_must_match
{   static void validate (nitpick& , const html_version& , const ::std::string& , const ::std::string& ) { }
    static bool compare (nitpick& , const html_version& , const char* lhs, const ::std::string& rhs)
    {   return compare_no_case (lhs, rhs); }
    static bool compare (nitpick& , const html_version& , const ::std::string& lhs, const char* rhs)
    {   return compare_no_case (lhs, rhs); }
    static ::std::string lower (::std::string& s) { return s; } };

template < > struct case_must_match < false >
{   static void validate (nitpick& nits, const html_version& v, const ::std::string& naam, const ::std::string& s)
    {   compare_validate (nits, v, naam, s); }
    static bool compare (nitpick& nits, const html_version& v, const char* lhs, const ::std::string& rhs)
    {   return compare_complain (nits, v, lhs, rhs); }
    static bool compare (nitpick& nits, const html_version& v, const ::std::string& lhs, const char* rhs)
    {   return compare_complain (nits, v, lhs, rhs); }
    static ::std::string lower (::std::string& s) { return ::boost::to_lower_copy (s); } };

template < class LC > struct careless_case : case_must_match < false > { };
template < > struct careless_case < sz_false > : case_must_match < true > { };
