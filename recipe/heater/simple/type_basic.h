/*
ssc (static site checker)
File Info
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

e_status set_compact_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_html_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_loopie_value (nitpick& nits, const html_version& v, const ::std::string& s);

template < > struct type_master < t_empty > : string_value < t_empty >
{   using string_value < t_empty > :: string_value;
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   ::std::string val (trim_the_lot_off (s));
        if (val.empty ()) string_value < t_empty > :: status (s_good);
        else
        {   nits.pick (nit_empty, es_error, ec_type, quote (val), " is insufficiently empty");
            string_value < t_empty > :: status (s_invalid); } } };

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
        string_value < t_compact > :: status (set_compact_value (nits, v, string_value < t_compact > :: get_string ())); }
    void shadow (::std::stringstream& ss, const html_version& v, element* )
    {   if (v.xhtml ()) ss << "=\"compact\""; } };

template < > struct type_master < t_contain > : type_string < t_contain, sz_contain >
{ using type_string < t_contain, sz_contain > :: type_string; };

template < > struct type_master < t_digits > : type_string < t_digits, sz_digits >
{ using type_string < t_digits, sz_digits > :: type_string; };

template < > struct type_master < t_existential > : type_base < mono, t_existential >
{   using type_base < mono, t_existential > :: type_base;
    static bool is_existential () noexcept { return true; }
    void set_value (nitpick& , const html_version& , const ::std::string& ) noexcept
    {   type_base < mono, t_existential > :: status (s_good); } };

template < > struct type_master < t_html > : tidy_string < t_html >
{   using tidy_string < t_html > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_html > :: set_value (nits, v, s);
        string_value < t_html > :: status (set_html_value (nits, v, string_value < t_html > :: get_string ())); } };

template < > struct type_master < t_illegal > : type_base < mono, t_illegal >
{   using type_base < mono, t_illegal > :: type_base;
    void set_value (nitpick& nits, const html_version& , const ::std::string& )
    {   nits.pick (nit_evermore, es_error, ec_type, "always illegal");
        type_base < mono, t_illegal > :: status (s_invalid); }
    static mono default_value () noexcept { return GSL_NARROW_CAST <mono> (0); }
    mono get () const
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return GSL_NARROW_CAST <mono> (0)); } };

template < > struct type_master < t_inset > : type_string < t_inset, sz_inset >
{ using type_string < t_inset, sz_inset > :: type_string; };

template < > struct type_master < t_loopie > : tidy_string < t_loopie >
{   using tidy_string < t_loopie > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_loopie > :: set_value (nits, v, s);
        string_value < t_loopie > :: status (set_loopie_value (nits, v, string_value < t_loopie > :: get_string ())); } };

template < > struct type_master < t_not_empty > : string_value < t_not_empty >
{   using string_value < t_not_empty > :: string_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_not_empty > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value should not be empty");
            string_value < t_not_empty > :: status (s_invalid); } } };

template < > struct type_master < t_slash > : type_string < t_slash, sz_slash >
{ using type_string < t_slash, sz_slash > :: type_string; };

template < > struct type_master < t_wanted > : public tidy_string < t_wanted >
{   using tidy_string < t_wanted > :: tidy_string;
    void verify_attribute (nitpick& nits, const html_version& , const elem& , element* , const ::std::string& situation)
    {   if (tidy_string < t_wanted > :: unknown ())
            nits.pick (nit_value_expected, es_warning, ec_type, "a value ought to be supplied (", situation, ")"); } };
