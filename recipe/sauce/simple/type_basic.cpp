/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "type/type.h"
#include "element/element.h"

e_status set_char_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.length () > 0)
    {   if (s.length () == 1) return s_good;
        if ((s.length () > 2) && (s.at (0) == '&') && (s.at (s.length () - 1) == ';')) return s_good;
        if ((s.length () == 5) && (s.at (0) == '\\') && (s.substr (1).find_first_not_of (HEX) == ::std::string::npos)) return s_good; }
    nits.pick (nit_single_character, es_error, ec_type, quote (s), " is not a single character");
    return s_invalid; }

e_status set_compact_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! s.empty ())
    {   if (v.is_1 ())
        {   nits.pick (nit_bad_compact, es_error, ec_type, "in ", v.report (), ", compact has no value");
            return s_invalid; }
        if (! compare_complain (nits, v, "compact", s))
        {   nits.pick (nit_bad_compact, es_error, ec_type, "if compact is given a value, it must be \"compact\", not ", quote (s));
            return s_invalid; } }
    return s_good; }

e_status set_custom_old_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (! s.empty ())
        if ((s.at (0) < 'a') || (s.at (0) > 'z'))
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_error, ec_type, quote (s), ": the first character of a custom element must be an ASCII lower-case letter");
        else if (s.find ('-') == ::std::string::npos)
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_error, ec_type, quote (s), ": a custom element name must contain '-' (ASCII minus)");
        else if (s.find_first_of (UPPERCASE) != ::std::string::npos)
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_error, ec_type, quote (s), ": a custom element name must not contain an upper-case ASCII letter");
        else return s_good;
    return s_invalid; }

e_status set_custom_new_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (! s.empty ())
        if ((s.at (0) < 'a') || (s.at (0) > 'z'))
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_error, ec_type, quote (s), ": the first character of a custom element must be an ASCII lower-case letter");
        else if (s.find_first_of (UPPERCASE) != ::std::string::npos)
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_error, ec_type, quote (s), ": a custom element name must not contain an upper-case ASCII letter");
        else
        {   bool whoops = false;
            for (   ::std::string::size_type pos = s.find_first_not_of (LOWERCASE DENARY ".-_");
                    pos != ::std::string::npos;
                    pos = s.substr (pos+1).find_first_not_of (LOWERCASE DENARY ".-_"))
#ifdef _MSC_VER
            {   const char ch = s.at (pos);
                if ((ch >= 0xC0) && (ch <= 0xD6)) continue;
                if ((ch >= 0xC0) && (ch <= 0xD6)) continue;
                if (ch > 0xF8) continue;
                if (ch == 0xB8) continue;
                whoops = true;
#else // _MSC_VER
            {   whoops = true;
#endif // _MSC_VER
                break; }
            if (! whoops) return s_good;
            nits.pick (nit_custom_element, ed_jul25, "4.13.3 Core concepts", es_warning, ec_type, quote (s), ": the custom element name may contain an illegal ASCII character"); }
    return s_invalid; }

e_status set_html_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
    {   nits.pick (nit_empty, es_error, ec_type, "a SRCDOC value cannot be empty");
        return s_invalid; }
    e_status res = s_good;
    elements_node nodes;
    const bool r = (context.analysis () == anal_original) ? nodes.parse (nits, s) : nodes.parse (nits, s, v);
    if (r)
        if (! nodes.has_vrai_element ())
        {   nits.pick (nit_requires_html, ed_50, "4.7.2 The iframe element", es_error, ec_attribute, "the HTML snippet in a SRCDOC attribute must include an HTML element");
            res = s_invalid; }
    nodes.harvest_nits (nits);
    return res; }

e_status set_loopie_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) return s_empty;
    if ((s.find_first_not_of (DENARY) == ::std::string::npos) || (s == "-1")) return s_good;
    if (compare_complain (nits, v, "infinite", s)) return s_good;
    nits.pick (nit_infinite_number, es_error, ec_type, quote (s), " should be an unsigned integer, -1, or 'infinite'");
    return s_invalid; }
