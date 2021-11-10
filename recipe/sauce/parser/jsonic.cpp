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
#include "parser/jsonic.h"

#ifdef NO_JSONIC
void parse_json_ld (nitpick& , const html_version& , const ::std::string& ) { }
#else // NO_JSONIC

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS ) // boost
#endif // _MSC_VER
#include <boost/json/src.hpp>
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

#include "main/context.h"
#include "type/type_enum.h"
#include "type/type_rdf.h"
#include "microdata/microdata_itemtype.h"
#include "microdata/microdata_itemprop.h"
#include "parser/parse_abb.h"
#include "url/url.h"
#include "url/url_sanitise.h"

// this is not, and not intended to be, a full json-ld interpreter. It exists, mostly, to enable schema testing.

const ::boost::json::value& parse_json (nitpick& nits, const ::std::string& s);

class jsonic
{   ::boost::json::value value_;
public:
    jsonic () = default;
    jsonic (const jsonic& j) = delete;
    void reset () noexcept
    {   value_.emplace_null (); }
    void parse (nitpick& nits, const ::std::string& s)
    {   try {
            ::boost::json::error_code ec;
            value_ = ::boost::json::parse (s, ec);
            if (ec)
            {   nits.pick (nit_json_error, es_error, ec_json, "JSON error: ", ec.message ());
                value_.emplace_null (); } }
        catch (const ::std::exception& x)
        {   nits.pick (nit_json_error, es_error, ec_json, "JSON exception: ", x.what ());
            value_.emplace_null (); }
        catch (...)
        {   nits.pick (nit_json_error, es_error, ec_json, "unknown JSON exception");
            value_.emplace_null (); } }
    const ::boost::json::value& val () const noexcept { return value_; } };

typedef ssc_map < ::std::string, const ::boost::json::value* > msv_t;
typedef ::std::vector < const ::boost::json::value* > vv_t;
typedef ::std::vector < vv_t > vk_t;

struct json_scope
{   json_scope* parent_ = nullptr;
    vk_t keyword_;
    msv_t prop_;
    url base_;
    //prefixes_ptr prefixes_;
    //jcontext context_;
//    itemtype_index ii_ = 0;
//    ::std::string base_, id_;
//    e_schema vocab_ = s_error;
};

jsonic jhbbc;

#if 0

/*
void prepare_prefixes (json_scope& scope)
{   if (scope.prefixes_.get () == nullptr)
    {   prefixes_t* parent = nullptr;
        for (json_scope* ancestor = scope.parent_; ancestor != nullptr; ancestor = ancestor -> parent_)
            if (ancestor -> prefixes_.get () != nullptr)
            {   parent = ancestor -> prefixes_.get (); break; }
        scope.prefixes_.reset (new prefixes_t);
        VERIFY_NOT_NULL (scope.prefixes_.get (), __FILE__, __LINE__);
        scope.prefixes_ -> up (parent); } }
*/
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
        if (! scope.base_.empty ()) return scope.base_ + ss;
        if (! scope.context_.name_.empty ()) return scope.context_.name_ + ss; }
    return s; }

bool process_base (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   if (val.kind () != ::boost::json::kind::string)
    {   nits.pick (nit_json_id, es_error, ec_json, "JSON @base requires a url");
        return false; }
    ::std::string base = val.as_string ().c_str ();
    url u (nits, v, base);
    if (! u.invalid ()) scope.base_ = base;
    return true; }

void process_context_object (nitpick& nits, json_scope& scope, const ::boost::json::object& o)
{   //PRESUME (scope.prefixes_.get () != nullptr, __FILE__, __LINE__);
    for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const char* k = e.key_c_str ();
        if (k [0] == '@') nits.pick (nit_jsonld_context, es_comment, ec_json, "@context: not processing ", quote (k));
        else switch (e.value ().kind ())
        {   case ::boost::json::kind::string :
                //VERIFY_NOT_NULL (scope.prefixes_, __FILE__, __LINE__);
                //scope.prefixes_ -> declare (nits, context.html_ver (), schema_names, k, e.value ().as_string ().c_str (), false);
                scope.context_.name_ = e.value ().as_string ().c_str ();
                break;
            case ::boost::json::kind::object :
                nits.pick (nit_jsonld_context, es_comment, ec_json, "@context: not processing ", quote (k));
                break;
            default :
                nits.pick (nit_jsonld_context, es_error, ec_json, "@context ", quote (k), " requires a string or an object");
                break; } } }

void process_context (nitpick& nits, json_scope& scope, const ::boost::json::value& val)
{   switch (val.kind ())
    {   case ::boost::json::kind::string :
            scope.context_.name_ = val.as_string ().c_str ();
            // prepare_prefixes (scope);
            //{   const char* k = val.as_string ().c_str ();
            //    scope.prefixes_ -> declare (nits, context.html_ver (), schema_names, ::std::string (), k, false); }
            break;
        case ::boost::json::kind::object :
           // gents, a  prepare_prefixes (scope);
            process_context_object (nits, scope, val.as_object ());
            break;
        default :
            nits.pick (nit_jsonld_context, es_error, ec_json, "default @context requires a string or an object");
            break; } }

bool process_vocab (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   if (scope.vocab_ != s_error)
        nits.pick (nit_vocab, es_info, ec_json, "replacing existing default @vocab ", schema_names.get (scope.vocab_, ABB_LONGFORM));
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
#endif

void outer_process_json_ld (nitpick& nits, const html_version& v, json_scope& scope);

bool is_token_valid_here  (nitpick& nits, const html_version& v, const e_jtoken parent, const e_jtoken token)
{   switch (parent)
    {   case jt_list :
        case jt_set :
            if ((token == jt_list) || (token == jt_context) || (token == jt_index)) return true;
            nits.pick (nit_json_out_of_place, ed_jsonld_1_0, "8.4 Lists and Sets", es_error, ec_json, "@list and @set can only have @list, @context, and @index children");
            return false;
        default : return true; } }

void note_token (nitpick& nits, const html_version& v, json_scope& scope, const char *s, const ::boost::json::value& val, const e_jtoken tk)
{   enum_n < t_jtoken, e_jtoken > jt;
    jt.set_value (nits, v, s);
    if (jt.good ())
        if (is_token_valid_here (nits, v, tk, jt.get ()))
        {   if (scope.keyword_.empty ()) scope.keyword_.resize (jt_error);
            PRESUME (scope.keyword_.size () > jt.get (), __FILE__, __LINE__);
            vv_t& vv = scope.keyword_.at (jt.get ());
            vv.push_back (&val); } }

::std::string expand_term (nitpick& nits, json_scope& scope, const ::std::string& key)
{   // prop_
    msv_t::const_iterator i = scope.prop_.find (key);
    if (i != scope.prop_.cend ())
        if (i -> second != nullptr)
            if (i -> second -> kind () == ::boost::json::kind::string)
                return i -> second -> as_string ().c_str ();
//    if (! scope.base_.empty ()) return scope.base_ + key;
    return key; }

void note_term (nitpick& nits, json_scope& scope, const char *s, const ::boost::json::value* val)
{   ::std::string key (trim_the_lot_off (s));
    if (key.empty ()) nits.pick (nit_empty, ed_jsonld_1_0, "8.1 terms", es_error, ec_json, "a term must not be empty");
    else
    {   key = expand_term (nits, scope, key);
        msv_t::iterator i = scope.prop_.find (key);
        if (i == scope.prop_.end ()) scope.prop_.insert (msv_t::value_type (key, val));
        else nits.pick (nit_json_name, ed_json, "2.2 Objects", es_error, ec_json, "additional term ", quote (key), " ignored"); } }

void examine_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o, const e_jtoken tk = jt_error)
{   for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const char* k = e.key_c_str ();
        VERIFY_NOT_NULL (k, __FILE__, __LINE__);
        if (*k != '@') note_term (nits, scope, k, &e.value ());
        else note_token (nits, v, scope, k, e.value (), tk); } }

void process_group_token (nitpick& nits, const html_version& v, json_scope& scope, const vv_t& vv)
{   for (auto val : vv)
    {   VERIFY_NOT_NULL (val, __FILE__, __LINE__);
        if (val -> kind () != ::boost::json::kind::object)
            nits.pick (nit_json_value_object, ed_jsonld_1_0, "8.4 Lists and Sets", es_error, ec_json, "@list and @set values must be JSON objects");
        else
        {
            examine_json_ld (nits, v, scope, val -> as_object ());
            outer_process_json_ld (nits, v, scope); } } }


void process_node (nitpick& nits, const html_version& v, json_scope& scope)
{   PRESUME (scope.keyword_.size () >= jt_error, __FILE__, __LINE__);
    if (! scope.keyword_.at (jt_list).empty ()) process_group_token (nits, v, scope, scope.keyword_.at (jt_list));
    if (! scope.keyword_.at (jt_set).empty ()) process_group_token (nits, v, scope, scope.keyword_.at (jt_set));
// jt_base,
//    jt_container, jt_context,
//    jt_direction,
//    jt_graph,
//    jt_id, jt_import, jt_included, jt_index,
//    jt_json,
//    jt_language, jt_list,
//    jt_nest, jt_none,
 //   jt_prefix, jt_propagate, jt_protected,
 //   jt_reverse,
//    jt_set,
//    jt_type,
//    jt_value, jt_version, jt_vocab

//    if (! scope.keyword_.at ().empty ()

}


void process_json_ld (nitpick& nits, const html_version& v, json_scope& scope)
{   for (int i = 0; i < jt_error; ++i)
        if (! scope.keyword_.at (i).empty ())
            if ((i == jt_value) || (i == jt_set) || (i == jt_list))
            {   nits.pick (nit_json_invalid_node, ed_jsonld_1_0, "8.2 Node Objects", es_error, ec_json,
                           "A JSON-LD node cannot contain @value, @list or @set");
                return; }
    process_node (nits, v, scope); }

void outer_process_json_ld (nitpick& nits, const html_version& v, json_scope& scope)
{   bool limited = true;
    for (int i = 0; i < jt_error; ++i)
        if (! scope.keyword_.at (i).empty ())
            if ((i != jt_graph) && (i != jt_context))
            {   limited = false; break; }
    if (limited)
        nits.pick (nit_json_invalid_node, ed_jsonld_1_0, "8.2 Node Objects", es_error, ec_json, "A topmost JSON-LD node must contain more than just @graph and @context");
    else process_json_ld (nits, v, scope); }

const ::boost::json::value& parse_json (nitpick& nits, const ::std::string& s)
{   jhbbc.reset ();
    if (! s.empty ()) jhbbc.parse (nits, s);
    return jhbbc.val (); }

void parse_json_ld (nitpick& nits, const html_version& v, const ::std::string& s)
{   jhbbc.reset ();
    if (! s.empty ())
    {   jhbbc.parse (nits, s);
        if (! jhbbc.val ().is_object ()) nits.pick (nit_json_error, es_error, ec_json, "cannot parse as JSON-LD");
        else
        {   json_scope scope;
            examine_json_ld (nits, v, scope, jhbbc.val ().as_object ());
            outer_process_json_ld (nits, v, scope); } } }

#endif // NO_JSONIC