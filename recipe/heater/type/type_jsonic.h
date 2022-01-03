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
#include "type/type_autocomplete.h"
#include "url/url_protocol.h"

template < > struct type_master < t_js_lang > : type_or_null < t_js_lang, t_lang >
{ using type_or_null < t_js_lang, t_lang > :: type_or_null; };

template < > struct type_master < t_js_term > : tidy_string < t_js_term >
{   using tidy_string < t_js_term > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_js_term > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_js_term > :: get_string ();
        if (ss.empty ()) nits.pick (nit_empty, es_error, ec_type, "A JSON-LD term cannot be empty");
        else if (good ())
            if (ss.at (0) == '@')
                nits.pick (nit_json_bad_term, ed_jsonld_1_0, "8.1 Terms", es_error, ec_json, "a term should not start with an '@'");
            else if (! v.is_jsonld_11 ()) return;
            else if (ss.find (":") != ::std::string::npos)
                nits.pick (nit_json_bad_term, ed_jsonld_1_1, "9.1 Terms", es_error, ec_json, "a term should not contain a ':'");
            else
            {   nitpick nuts;
                protocol p (nuts, v, ss, pr_error);
                if (p.is_valid ())
                    nits.pick (nit_json_bad_term, ed_jsonld_1_1, "9.1 Terms", es_error, ec_json, "a term should not be a standard URL scheme (https://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml)");
                else return; }
        tidy_string < t_js_term > :: status (s_invalid); } };

template < > struct type_master < t_js_type > : type_either_neither < t_js_type, t_url, t_text >
{ using type_either_neither < t_js_type, t_url, t_text > :: type_either_neither; };

template < > struct type_master < t_js_value > : type_one_of_three < t_js_value, t_tfn, t_fixedpoint, t_text >
{ using type_one_of_three < t_js_value, t_tfn, t_fixedpoint, t_text > :: type_one_of_three; };
