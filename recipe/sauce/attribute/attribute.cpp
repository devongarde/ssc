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

#include "main/standard.h"
#include "attribute/attribute.h"

bool verify_attribute_version (nitpick& nits, const html_version& v, const e_element tag, const e_attribute id, const ::std::string& name, bool& excluded, bool& deprecated)
{   if (! v.check_math_svg (nits, attr :: first_version (id), name)) excluded = true;
        if (is_invalid_attribute_version (v, tag, id))
        {   nits.pick (nit_invalid_attribute_version, es_error, ec_attribute, quote (name), " is invalid in ", v.report ());
            return false; }
        if (! excluded)
        {   excluded = attr :: first_version (id).invalid_addendum (v);
            if (excluded) nits.pick (nit_excluded_attribute, es_warning, ec_attribute, "the attribute ", quote (name), " is invalid in pure ", v.report ()); }
        deprecated = is_deprecated_attribute_version (v, tag, id);
        if (deprecated) nits.pick (nit_deprecated_attribute, es_warning, ec_attribute, name, " is deprecated in ", v.report ());
        else if (not_production_attribute (v, tag, id))
            nits.pick (nit_prototype, ed_jan21, "1.11.1 Presentational markup", es_comment, ec_attribute, name, " is best not used in production in ", v.report ());
    return true; }

bool set_attribute_value (nitpick& nits, const html_version& v, const ::std::string& ss, const ::std::string& n)
{   if (v.is_b4_2 ())
        nits.pick (nit_existential_value, es_warning, ec_type, "in ", v.report (), ", ", n, " cannot be given a value");
    else
    if (v.xhtml ())
    {   if (ss == n) return true;
        nits.pick (nit_xhtml_existential_makework, es_error, ec_type, "in ", v.report (), ", the value of ", n, " must be ", quote (n)); }
    else
    {   if (compare_no_case (ss, n)) return true;
        nits.pick (nit_existential_value, es_warning, ec_type, "if ", n, " has a value, it must be ", quote (n)); }
    return false; }
