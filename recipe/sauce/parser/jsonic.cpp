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

#include <boost/json/src.hpp>

#include "parser/jsonic.h"
#include "main/context.h"
#include "type/type_enum.h"
#include "type/type_rdf.h"
#include "microdata/microdata_itemtype.h"
#include "microdata/microdata_itemprop.h"
#include "parser/parse_abb.h"
#include "url/url.h"
#include "url/url_sanitise.h"

const ::boost::json::value& parse_json (nitpick& nits, const ::std::string& s);

class jsonic
{   //::boost::json::monotonic_resource mr_;
    ::boost::json::value value_;
    //::boost::json::parse_options po_ = { true, true, true };
    //::boost::json::parser p_;
public:
    jsonic () = default;
    jsonic (const jsonic& j) = delete;
    void reset ()
    {   value_.emplace_null ();
        /* p_.reset (); */ }
    void parse (nitpick& nits, const ::std::string& s)
    {   ::boost::json::monotonic_resource mr_;
        //::boost::json::value value_;
        ::boost::json::parse_options po_ = { true, true, true };
        ::boost::json::parser p_;
        try {
            ::boost::json::error_code ec;
            value_ = ::boost::json::parse (s, ec);
            if (ec)
            {   nits.pick (nit_json_error, es_error, ec_json, "JSON error: ", ec.message ());
                value_.emplace_null (); } }
        catch (::std::exception& x)
        {   nits.pick (nit_json_error, es_error, ec_json, "JSON exception: ", x.what ());
            value_.emplace_null (); }
        catch (...)
        {   nits.pick (nit_json_error, es_error, ec_json, "unknown JSON exception");
            value_.emplace_null (); } }
    const ::boost::json::value& val () const { return value_; } };

struct json_scope
{   prefixes_ptr prefixes_;
    itemtype_index ii_ = 0;
    ::std::string base_, id_;
    e_schema vocab_ = s_error;
};

jsonic jhbbc;

const ::boost::json::value untangle_value_tokens (json_scope& scope, const ::boost::json::value& val)
{   if (val.kind () != ::boost::json::kind::string) return val;
    ::std::string s (val.as_string ().c_str ());
    if (s.empty ()) return val;
    if (s.at (1) != '@') return val;
    if (s != "@id") return val;
    ::boost::json::value res;
    res.emplace_string () = scope.id_;
    return res; }

::std::string incorporate_kitchen_sink (json_scope& scope, const ::std::string s)
{   if (s.find (':') == ::std::string::npos)
    {   ::std::string ss ("/");
        if (! s.empty ())
            if (s.at (0) == '/') ss = s;
            else ss += s;
        if ((scope.vocab_ != s_error) && (scope.vocab_ != s_none))
            return schema_names.get (scope.vocab_, ABB_LONGFORM) + ss;
        if (! scope.base_.empty ()) return scope.base_ + ss; }
    return s; }

bool process_base (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   if (val.kind () != ::boost::json::kind::string)
    {   nits.pick (nit_json_id, es_error, ec_json, "JSON @base requires a url");
        return false; }
    ::std::string base = val.as_string ().c_str ();
    url u (nits, v, base);
    if (! u.invalid ()) scope.base_ = base;
    return true; }

void process_context (nitpick& nits, json_scope& scope, const ::boost::json::value& val)
{
}

bool process_vocab (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   if (scope.vocab_ != s_error)
        nits.pick (nit_vocab, es_info, ec_rdfa, "replacing existing default @vocab ", schema_names.get (scope.vocab_, ABB_LONGFORM));
    if (val.kind () != ::boost::json::kind::string)
    {   nits.pick (nit_bad_vocab, es_error, ec_json, "JSON @vocab requires a url");
        return false; }
    ::std::string ss (val.as_string ().c_str ());
    if (ss.find (':') == ::std::string::npos)
        if (! scope.base_.empty ())
            ss = scope.base_ + ss;
    e_schema s = schema_names.find_lower (v, SCHEMA_CURIE, ss);
    if (s == s_none)
        nits.pick (nit_bad_vocab, es_error, ec_rdfa, PROG " does not know about ", quote (ss), ", so will be unable to verify its content");
    else scope.vocab_ = s;
    return true; }


bool process_token (nitpick& nits, const html_version& v, json_scope& scope, const char *s, const ::boost::json::value& val)
{   enum_n < t_jtoken, e_jtoken > jt;
    jt.set_value (nits, v, s);
    if (jt.good ()) switch (jt.get ())
    {   case jt_base :
            if (val.kind () != ::boost::json::kind::string)
                nits.pick (nit_json_id, es_error, ec_json, "JSON @base requires a url");
            else
            {   ::std::string base = val.as_string ().c_str ();
                url u (nits, v, base);
                if (! u.invalid ()) scope.base_ = base;
                return true; }
            break;
        case jt_context :
            process_context (nits, scope, val);
            break;
        case jt_container :
        case jt_direction :
        case jt_graph :
            break;
        case jt_id :
            if (val.kind () != ::boost::json::kind::string)
                nits.pick (nit_json_id, es_error, ec_json, "JSON @id requires a url");
            else scope.id_ = sanitise (scope.base_ + "/" + val.as_string ().c_str ());
            break;
        case jt_import :
        case jt_included :
        case jt_index :
        case jt_json :
        case jt_language :
        case jt_list :
        case jt_nest :
        case jt_none :
        case jt_prefix :
        case jt_propagate :
        case jt_protected :
        case jt_reverse :
        case jt_set :
        case jt_type :
        case jt_value :
        case jt_version :
            break;
        case jt_vocab :
            process_vocab (nits, v, scope, val);
            break;
        default :
            nits.pick (nit_json_internal_error, es_catastrophic, ec_json, "process_token: unprocessed JSON token ", static_cast < int > (jt.get ()));
            break; }
    return false; }

void note_value (nitpick& nits, const html_version& v, json_scope& scope, const char *s, const ::boost::json::value& val, itemprop_index ndx = illegal_itemprop)
{   if (ndx == illegal_itemprop)
    {   ndx = find_itemprop_index (nits, v, s, false);
        if (ndx == illegal_itemprop) return; }
    switch (val.kind ()) // bollox; have to convert to string which will be converted right back to the original type deep in the tests.
    {   case ::boost::json::kind::null :
            is_valid_property (nits, v, scope.ii_, ndx, ::std::string (), false);
            break;
        case ::boost::json::kind::bool_ :
            if (val.as_bool ()) is_valid_property (nits, v, scope.ii_, ndx, "true", false);
            else is_valid_property (nits, v, scope.ii_, ndx, "false", false);
            break;
        case ::boost::json::kind::int64 :
            is_valid_property (nits, v, scope.ii_, ndx, ::boost::lexical_cast < ::std::string > (val.as_int64 ()), false);
            break;
        case ::boost::json::kind::uint64 :
            is_valid_property (nits, v, scope.ii_, ndx, ::boost::lexical_cast < ::std::string > (val.as_uint64 ()), false);
            break;
        case ::boost::json::kind::double_ :
            is_valid_property (nits, v, scope.ii_, ndx, ::boost::lexical_cast < ::std::string > (val.as_double ()), false);
            break;
        case ::boost::json::kind::string :
            is_valid_property (nits, v, scope.ii_, ndx, untangle_value_tokens (scope, val).as_string ().c_str (), false);
            break;
        case ::boost::json::kind::array :
            {   for (auto i : val.as_array ())
                    note_value (nits, v, scope, s, i, ndx); }
            break;
        case ::boost::json::kind::object : break; }

/*
itemtype_index find_itemtype_index (nitpick& nits, const html_version& v, const ::std::string& name, const bool propped)   // propped must be false here
*/


}

void examine_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o)
{   for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const char* k = e.key_c_str ();
        if (k [0] == '@') process_token (nits, v, scope, k, e.value ());
        else note_value (nits, v, scope, k, e.value ()); } }

const ::boost::json::value& parse_json (nitpick& nits, const ::std::string& s)
{   jhbbc.reset ();
    if (! s.empty ()) jhbbc.parse (nits, s);
    return jhbbc.val (); }

void parse_json_ld (nitpick& nits, const html_version& v, const ::std::string& s)
{   jhbbc.reset ();
    if (! s.empty ())
    {   jhbbc.parse (nits, s);
        if (! jhbbc.val ().is_object ()) nits.pick (nit_json_error, es_error, ec_json, "cannot parse JSON-LD");
        else
        {   json_scope scope;
            examine_json_ld (nits, v, scope, jhbbc.val ().as_object ()); } } }
