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
#include "type/type.h"
#include "url/url_protocol.h"

e_status set_js_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "A JSON-LD term cannot be empty");
    else if (s.at (0) == '@')
            nits.pick (nit_json_bad_term, ed_jsonld_1_0, "8.1 Terms", es_error, ec_json, "a term should not start with an '@'");
    else if (! v.is_jsonld_11 ()) return s_good;
    else if (s.find (":") != ::std::string::npos)
        nits.pick (nit_json_bad_term, ed_jsonld_1_1, "9.1 Terms", es_error, ec_json, "a term should not contain a ':'");
    else
    {   nitpick nuts;
        protocol p (nuts, v, s, pr_error);
        if (p.is_valid ())
            nits.pick (nit_json_bad_term, ed_jsonld_1_1, "9.1 Terms", es_error, ec_json, "a term should not be a standard URL scheme (https://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml)");
        else return s_good; }
    return s_invalid; }
