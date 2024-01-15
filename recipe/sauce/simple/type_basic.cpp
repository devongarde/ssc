/*
ssc (static site checker)
File Info
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

e_status set_compact_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! s.empty ())
    {   if (v.is_1 ())
        {   nits.pick (nit_bad_compact, es_error, ec_type, "in ", v.report (), ", compact has no value");
            return s_invalid; }
        if (! compare_complain (nits, v, "compact", s))
        {   nits.pick (nit_bad_compact, es_error, ec_type, "if compact is given a value, it must be \"compact\", not ", quote (s));
            return s_invalid; } }
    return s_good; }

e_status set_html_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
    {   nits.pick (nit_empty, es_error, ec_type, "a SRCDOC value cannot be empty");
        return s_invalid; }
    e_status res = s_good;
    elements_node nodes;
    if (nodes.parse (nits, s))
        if (! nodes.has_element (elem_html))
        {   nits.pick (nit_requires_html, ed_50, "4.7.2 The iframe element", es_error, ec_attribute, "the HTML snippet in a SRCDOC attribute must include an <HTML> element");
            res = s_invalid; }
    nodes.harvest_nits (nits);
    return res; }

e_status set_loopie_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) return s_empty;
    if ((s.find_first_not_of (DENARY) == ::std::string::npos) || (s == "-1")) return s_good;
    if (compare_complain (nits, v, "infinite", s)) return s_good;
    nits.pick (nit_infinite_number, es_error, ec_type, quote (s), " should be an unsigned integer, -1, or 'infinite'");
    return s_invalid; }
