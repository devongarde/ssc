/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "parser/xhtml_xml.h"
#include "parser/parse_attributes.h"
#include "utility/quote.h"
#include "main/context.h"

bool parse_xml (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line, ::std::string& stylesheet)
{   attributes_node args;
    bool ok = false;
    bool style = false;
    if (e-b < 5) return false; // the <?xml should already have been parsed, but ...
    nits.set_context (line, b, e);
    ::std::string::const_iterator s = b + 5;
    if ((e-b > 15) && (::std::string (s, s + 11) == "-stylesheet"))
    {   style = true; s += 11; }
    else if (version.unknown ())
    {   version = xhtml_1_0;
        nits.pick (nit_xhtml_1_0, es_info, ec_parser, "XML found, inferring XHTML 1.0"); }
    args.parse (nits, version, s, e, line, elem (elem_undefined));
    for (auto a : args.get_attributes ())
        if (a.has_key () && a.has_value ())
        {   ::std::string value (::boost::to_lower_copy (trim_the_lot_off (a.get_string ())));
            if (style)
            {   bool css = true;
                ::std::string hr;
                switch (a.id ())
                {   case a_type :
                        css = value == CSS_TYPE; break;
                    case a_href :
                        hr = value; break;
                    case a_title : break;
                    default :
                        nits.pick (nit_xhtml_css, es_warning, ec_parser, "unexpected attribute ", quote (a.get_key ()), " on <?xml-stylesheet ...>"); }
                if (css && ! hr.empty ()) stylesheet = hr; }
            else switch (a.id ())
            {   case a_version :  // unless this defines the version of XML itself
                    if (value != "1.0")
                        nits.pick (nit_unknown_xhtml, es_error, ec_parser, "unexpected version of xml");
                    break;
                case a_encoding :
                    ok = true; break;
                default : break; } }
    return ok; }
