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
#include "type/type_master.h"

template < > struct type_master < t_char > : string_value < t_char >
{   using string_value < t_char > :: string_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string val (trim_the_lot_off (s));
        if (val.length () == 1)
            string_value < t_char > :: set_value (nits, v, val);
        else if ((val.length () > 1) && (val.at (0) == '&') && (val.at (val.length () - 1) == ';'))
            string_value < t_char > :: set_value (nits, v, val);
        else
        {   nits.pick (nit_single_character, es_error, ec_type, quote (val), " is not a single character");
            string_value < t_char > :: status (s_invalid); } } };

template < > struct type_master < t_compact > : tidy_string < t_compact >
{   using tidy_string < t_compact > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_compact > :: set_value (nits, v, s);
        if (s.empty ())
        {   string_value < t_compact > :: status (s_good); return; }
        if (v.is_1 ())
        {   string_value < t_compact > :: status (s_invalid);
            nits.pick (nit_bad_compact, es_error, ec_type, "in ", v.report (), ", compact has no value"); }
        ::std::string ss (string_value < t_compact > :: get_string ());
        if (! compare_complain (nits, v, "compact", ss))
        {   string_value < t_compact > :: status (s_invalid);
            nits.pick (nit_bad_border, es_error, ec_type, "if compact is given a value, it must be \"compact\", not ", quote (s)); } }
    void shadow (::std::stringstream& ss, const html_version& v, element* )
    {   if (v.xhtml ()) ss << "=\"compact\""; } };

template < > struct type_master < t_existential > : type_base < mono, t_existential >
{   using type_base < mono, t_existential > :: type_base;
    static bool is_existential () noexcept { return true; }
//    void shadow (::std::stringstream& , const html_version& , element* ) noexcept { }
    void set_value (nitpick& , const html_version& , const ::std::string& ) noexcept
    {   type_base < mono, t_existential > :: status (s_good); } };

template < > struct type_master < t_html > : tidy_string < t_html >
{   using tidy_string < t_html > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_html > :: set_value (nits, v, s);
        if (tidy_string < t_html > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "a SRCDOC value cannot be empty");
            string_value < t_html > :: status (s_invalid); }
        else
        {   elements_node nodes;
            if (nodes.parse (nits, tidy_string < t_html > :: get_string ()))
                if (! nodes.has_element (elem_html))
                    nits.pick (nit_requires_html, ed_50, "4.7.2 The iframe element", es_error, ec_attribute, "the HTML snippet in a SRCDOC attribute must include an <HTML> element");
            nodes.harvest_nits (nits); } } };

template < > struct type_master < t_illegal > : type_base < mono, t_illegal >
{   using type_base < mono, t_illegal > :: type_base;
    void set_value (nitpick& nits, const html_version& , const ::std::string& )
    {   nits.pick (nit_evermore, es_error, ec_type, "always illegal");
        type_base < mono, t_illegal > :: status (s_invalid); }
    static mono default_value () noexcept { return GSL_NARROW_CAST <mono> (0); }
    mono get () const
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return GSL_NARROW_CAST <mono> (0)); } };

template < > struct type_master < t_loopie > : tidy_string < t_loopie >
{   using tidy_string < t_loopie > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_loopie > :: set_value (nits, v, s);
        const ::std::string& x = tidy_string < t_loopie > :: get_string ();
        if (x.empty ()) return;
        if ((x.find_first_not_of (DENARY) == ::std::string::npos) || (x == "-1"))
            tidy_string < t_loopie > :: status (s_good);
        if (compare_complain (nits, v, "infinite", x))
            tidy_string < t_loopie > :: status (s_good);
        else
        {   nits.pick (nit_infinite_number, es_error, ec_type, quote (s), "should be an unsigned integer, -1, or the keyword 'infinite'");
            tidy_string < t_loopie > :: status (s_invalid); } } };

template < > struct type_master < t_not_empty > : string_value < t_not_empty >
{   using string_value < t_not_empty > :: string_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_not_empty > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value should not be empty");
            string_value < t_not_empty > :: status (s_invalid); } } };

template < > struct type_master < t_wanted > : public tidy_string < t_wanted >
{   using tidy_string < t_wanted > :: tidy_string;
    void verify_attribute (nitpick& nits, const html_version& , const elem& , element* , const ::std::string& situation)
    {   if (tidy_string < t_wanted > :: unknown ())
            nits.pick (nit_value_expected, es_warning, ec_type, "a value ought to be supplied (", situation, ")"); } };
