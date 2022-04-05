/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "parser/parse_elements.h"
#include "utility/quote.h"
#include "main/context.h"

bool parse_xml (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e, const int line, ::std::string& stylesheet)
{   elements_node fake_a_roony;
    attributes_node args (fake_a_roony.faux_node ());
    bool ok = false;
    bool style = false;
    if (e-b < 5) return false; // the <?xml should already have been parsed, but ...
    nits.set_context (line, b, e);
    ::std::string::const_iterator s = b + 5;
    if ((e-b > 15) && (::std::string (s, s + 11) == "-stylesheet"))
    {   style = true; s += 11; }
    else if (version.unknown ())
    {   const html_version s_v (get_min_version (context.svg_version ()));
        const html_version m_v (get_min_version (context.math_version ()));
        html_version def (context.html_ver ());
        if (def.unknown ())
            def = html_tags;
        if (! s_v.unknown ())
            if (s_v > def) def = s_v;
        if (! m_v.unknown ())
            if (m_v > def) def = m_v;
        if (def < xhtml_1_0)
            def = xhtml_1_0;
        if (! s_v.unknown ())
            def.svg_version (s_v.svg_version ());
        if (! m_v.unknown ())
            def.math_version (m_v.math_version ());
        switch (def.mjr ())
        {   case 0 :
            case 1 :
            case 2 :
            case 3 :
                version = xhtml_1_1;
                nits.pick (nit_program_error, es_catastrophic, ec_parser, "XML version deduction programming error; pretending XHTML 1.1");
                break;
            case 4 :
                version = def;
                switch (version.mnr ())
                {   case 2 :
                        nits.pick (nit_xhtml_1_0, es_info, ec_parser, "XML found, inferring XHTML 1.0"); break;
                    case 3 :
                        nits.pick (nit_xhtml_1_1, es_info, ec_parser, "XML found, inferring XHTML 1.1"); break;
                    case 4 :
                        nits.pick (nit_xhtml_2_0, es_info, ec_parser, "XML found, inferring XHTML 2.0"); break;
                    default :
                        version = xhtml_1_1;
                        nits.pick (nit_program_error, es_catastrophic, ec_parser, "XML version deduction programming error; pretending XHTML 1.1");
                        break; }
                break;
            default :
                version = def;
                version.set_flags (HV_XHTML);
                nits.pick (nit_xhtml_5_0, es_info, ec_parser, "XML found, inferring XHTML 5");
                break; } }
    args.parse (nits, version, s, e, line, elem (elem_undefined), true);
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
                        nits.pick (nit_unknown_xml, es_error, ec_parser, "unexpected version of xml");
                    break;
                case a_encoding :
                    ok = true; break;
                default : break; } }
    return ok; }
