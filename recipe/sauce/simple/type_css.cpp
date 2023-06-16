/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "parser/html_version.h"
#include "type/type.h"
#include "webpage/page.h"
#include "element/element.h"
#include "css/arguments.h"

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e)
{   try
    {   if (e == nullptr)
            nits.pick (nit_css_syntax, es_catastrophic, ec_type, "null element processing STYLE");
        else
        {   page& p = e -> get_page ();
            if (! p.style_css ())
                nits.pick (nit_style_not_css, es_comment, ec_type, PROG " can only check style type " CSS_TYPE);
            else if (context.load_css () && (context.css_version () >= css_1))
                p.css ().parse (s, v, e -> namespaces (), e -> ancestral_elements (), false, e -> line (), e -> tag ()); } }
    catch (const ::std::system_error& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "system exception processing STYLE: ", ex.what ()); }
    catch (const ::std::exception& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "exception processing STYLE: ", ex.what ()); }
    catch (...)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "unknown exception processing STYLE"); }
    return nits.worst () < es_warning; }
