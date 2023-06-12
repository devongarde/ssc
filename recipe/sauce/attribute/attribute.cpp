   /*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

/*
        if (! v.check_math_svg (nits, attr :: first_version (IDENTITY), name ())) excluded_ = true;
        if (is_invalid_attribute_version (v, tag, IDENTITY))
        {   nits.pick (nit_invalid_attribute_version, es_error, ec_attribute, quote (name ()), " is invalid in ", v.report ());
            return false; }
        if (! excluded_)
        {   excluded_ = attr :: first_version (IDENTITY).invalid_addendum (v);
            if (excluded_) nits.pick (nit_excluded_attribute, es_warning, ec_attribute, "the attribute ", quote (name ()), " is invalid in pure ", v.report ()); }
        deprecated_ = is_deprecated_attribute_version (v, tag, IDENTITY);
        if (deprecated_) nits.pick (nit_deprecated_attribute, es_warning, ec_attribute, name (), " is deprecated in ", v.report ());
        else if (not_production_attribute (v, tag, IDENTITY))
            nits.pick (nit_prototype, ed_jan21, "1.11.1 Presentational markup", es_comment, ec_attribute, name (), " is best not used in production in ", v.report ());
        return true; }




*/