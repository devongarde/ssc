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

#ifndef NO_JSONIC
#include "main/context.h"
#include "symbol/nstr.h"
#include "type/type.h"
#include "microdata/microdata_itemtype.h"
#include "microdata/microdata_itemprop.h"
#include "parser/jsonic.h"
#include "parser/parse_abb.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "ontology/jsonld.h"
#include "ontology/ontology_type.h"
#include "ontology/ontology_property.h"
#include "ontology/ontology_hierarchy.h"

// this is not, and not intended to be, a full json-ld interpreter. It exists, mostly, to enable schema testing.

typedef ::std::vector < ::boost::json::value > vv_t;
typedef ::std::vector < vv_t > vk_t;
typedef ssc_map < ::std::string, e_ontology_property > mssp_t;
typedef ::std::vector < e_ontology > vo_t;
typedef ::std::vector < ontology_version > vov_t;

struct json_scope
{   json_scope* parent_ = nullptr;
    vk_t keyword_;
    url base_;
    vo_t vo_;
    ssch_t type_;
    mssp_t bespoke_;
    ::std::string name_;
    unsigned int terms_ = 0;
    bool atless_type_ = false;
    json_scope ()
    {   keyword_.resize (jt_error); }
    explicit json_scope (json_scope* parent)
    {   keyword_.resize (jt_error);
        parent_ = parent; }
    vo_t ontologies () const
    {   if (! vo_.empty ()) return vo_;
        if (parent_ != nullptr) return parent_ -> ontologies ();
        return vo_t (); }
};

void outer_process_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o);
bool process_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o);
void examine_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o, const e_jtoken tk = jt_error);

e_ontology_property get_ontology_property (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string::size_type after = ::std::string::npos;
    const e_ontology es = ontology_names.starts_with_mixed (ONTOLOGY_CURIE, s, &after);
    if (es == s_error)
    {   nits.pick (nit_jsonld_type, es_error, ec_json, "schema type ", quote (s), " is unrecognised");
        return op_illegal; }
    if (after == ::std::string::npos)
    {   nits.pick (nit_jsonld_type, es_error, ec_json, "schema type ", quote (s), " is incomplete");
        return op_illegal; }
    const ontology_version sv (v);
    const e_ontology_property sp = identify_ontology_property (s.substr (after));
    if (sp == op_illegal)
        nits.pick (nit_not_ontology_property, es_error, ec_schema, quote (s.substr (after)), " is not a recognised ", sv.report (), " property");
    const sch sc (nits, v, s.substr (after), es);
    if (sc.unknown ()) return op_illegal;
    return sp; }

bool is_token_valid_here (nitpick& nits, const html_version& , const e_jtoken parent, const e_jtoken token)
{   switch (parent)
    {   case jt_list :
        case jt_set :
            if ((token == jt_list) || (token == jt_context) || (token == jt_index)) return true;
            nits.pick (nit_json_out_of_place, ed_jsonld_1_0, "8.4 Lists and Sets", es_error, ec_json, "@list and @set can only have @list, @context, and @index children");
            return false;
        default : return true; } }

void note_token (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& s, const ::boost::json::value& val, const e_jtoken tk)
{   enum_n < t_jtoken, e_jtoken > jt;
    jt.set_value (nits, v, s);
    if (jt.good ())
        if (is_token_valid_here (nits, v, tk, jt.get ()))
        {   if (scope.keyword_.empty ()) scope.keyword_.resize (jt_error);
            PRESUME (scope.keyword_.size () > jt.get (), __FILE__, __LINE__);
            vv_t& vv = scope.keyword_.at (jt.get ());
            vv.push_back (val); } }

bool separate_ontology_wot (nitpick& nits, const json_scope& scope, const ::std::string& s, e_ontology& o, ::std::string& wot)
{   const ::std::string::size_type pos = s.find (':');
    if (pos == ::std::string::npos) return false;
    if ((pos == 0) || (pos == s.size () - 1)) 
    {   nits.pick (nit_missing_ontology, es_error, ec_json, quote (s), ": ':'??");
        return false; }
    const ::std::string ont = s.substr (0, pos);
    const ::std::string ty = s.substr (pos+1);
    e_ontology xo = s_none;
    for (auto vo : scope.ontologies ())
        if (ontology_names.get (vo, ONTOLOGY_NAME) == ont)
        {   xo = vo; break; }
    if (xo == s_none)
    {   nits.pick (nit_missing_ontology, es_error, ec_json, quote (ont), " is not recognised (missing @context ?)");
        return false; }
    wot = ty;
    o = xo;
    return true; }

::std::string expand_term (nitpick& , json_scope& , const ::std::string& s)
{   return s; }

e_ontology_property wot_prop (nitpick& nits, const html_version& , const json_scope& scope, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    e_ontology o = s_none;
    ::std::string pr;
    nitpick nuts;
    if (separate_ontology_wot (nuts, scope, s, o, pr))
    {   const e_ontology_property sp = identify_ontology_property (pr, o);
        if (sp != op_illegal)
        {   nits.merge (nuts);
            return sp; } }
    for (auto vo : scope.ontologies ())
    {   const e_ontology_property sp = identify_ontology_property (s, vo);
        if (sp != op_illegal) return sp; }
    nits.pick (nit_not_ontology_property, es_error, ec_schema, quote (s), " is not a recognised property (3)");
    return op_illegal; }

bool process_map (nitpick& nits, const html_version& v, const ::boost::json::object& o, const e_type key_type)
{   bool res = true;
    for (auto e : o)
    {   if (e.key_c_str () == nullptr) continue;
        test_value (nits, v, key_type, e.key_c_str ());
        if (e.value ().kind () != ::boost::json::kind::string)
        {   nits.pick (nit_jsonld_map, es_error, ec_json, quote (e.key_c_str ()), " must be paired with a string");
            res = false; } }
    return res; }

bool process_term_object (nitpick& nits, const html_version& v, json_scope& scope, const e_ontology_property p, const ::boost::json::object& obj)
{   nitpick nuts;
    vov_t vov;
    for (auto on : scope.ontologies ())
    {   const ontology_version sv (corresponding_ontology_version (on, v));
//    {   const ontology_version sv = get_default_ontology_version (on);
        vov.push_back (sv);
        vt_t vt = sought_types (sv, p);
        for (auto st : vt)
            switch (st)
            {   case t_js_map :
                    if (process_map (nuts, v, obj, t_generic))
                    {   nits.merge (nuts); return false; }
                    break;
                case t_js_lang_map :
                    if (process_map (nuts, v, obj, t_lang))
                    {   nits.merge (nuts); return false; }
                    break;
                default :
                    break; } }
    PRESUME (vov.size () == scope.ontologies ().size (), __FILE__, __LINE__);
    json_scope new_scope (&scope);
    examine_json_ld (nits, v, new_scope, obj);
    const bool name_type = process_json_ld (nits, v, new_scope, obj);
    if (name_type)
        for (auto ov : vov)
            for (auto st : scope.type_)
            {   nitpick nets;
                if (is_valid_ontology_property (nets, v, st, p, new_scope.name_, false))
                {   vit_t sst = sought_ontology_types (ov, p);
                    for (auto t : new_scope.type_)
                    {   for (auto tt : sst)
                        {   const e_ontology_type ti = type_itself (tt);
                            if ((ti == t) || is_specific_type_of (ti, t) || is_specific_type_of (t, ti)) return name_type; }
                        nuts.pick (nit_jsonld_type, es_error, ec_json, sch::name (t), " is not a valid type for ", ontology_property_name (p)); }
                    nits.merge (nets);
                    nits.merge (nuts);
                    return name_type; } }
    else for (auto st : scope.type_)
        for (auto t : new_scope.type_)
            if (is_valid_ontology_property (nuts, v, st, p, t))
                return name_type;
    nits.merge (nuts);
    return name_type; }

void process_term_string (nitpick& nits, const html_version& v, json_scope& scope, const e_ontology_property p, const ::std::string& s)
{   nitpick nuts;
    for (auto st : scope.type_)
        if (is_valid_ontology_property (nuts, v, st, p, s, false))
            return;
    nits.merge (nuts); }

e_ontology process_context_string_int (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    e_ontology sn = ontology_names.find (v, ONTOLOGY_CURIE, s, false);
    if ((sn == s_none) || (sn == s_error))
    {   sn = ontology_names.find (v, ONTOLOGY_CURIE, s + "/", false);
        if ((sn == s_none) || (sn == s_error))
        {   sn = ontology_names.find (v, ONTOLOGY_CURIE, s + "#", false);
            if ((sn == s_none) || (sn == s_error))
            {   nits.pick (nit_jsonld_context, es_warning, ec_json, "Unfortunately, " PROG " does not recognise the schema ", quote (s), ", so cannot verify it.");
                return s_none; } } }
    if (context.tell (es_debug)) nits.pick (nit_jsonld_context, es_debug, ec_json, ontology_names.get (sn, ONTOLOGY_DESCRIPTION), " recognised");
    for (auto o : scope.ontologies ())
        if (o == sn)
        {   nits.pick (nit_jsonld_context, es_info, ec_json, quote (ontology_names.get (o, ONTOLOGY_CURIE)), " previously noted");
            break; }
    if ((ontology_names.flags (sn) & ONTOLOGY_CRAPSPEC) == ONTOLOGY_CRAPSPEC)
        nits.pick (nit_crap_spec, es_warning, ec_json, quote (ontology_names.get (sn, ONTOLOGY_NAME)), " is poorly specified: use an alternative");
    return sn; }

e_ontology_type process_ontology_name_type_string_int (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& s, const e_ontology o = s_none)
{   const e_ontology_type st = sch::parse (nits, v, s, o);
    if (st != ont_illegal)
        if (scope.type_.find (st) != scope.type_.cend ())
            nits.pick (nit_jsonld_type, es_error, ec_json, sch::name (st), " previously declared");
        else
        {   scope.type_.emplace (st);
            return st; }
    return ont_illegal; }

e_ontology_type process_ontology_name_type_string (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& s)
{   e_ontology o = s_none;
    ::std::string ty;
    nitpick nuts;
    if (separate_ontology_wot (nuts, scope, s, o, ty))
    {   nits.merge (nuts);
        return process_ontology_name_type_string_int (nits, v, scope, ty, o); }
    for (auto vo : scope.ontologies ())
    {   const e_ontology_type st = process_ontology_name_type_string_int (nits, v, scope, s, vo); 
        if (st != ont_illegal) return st; }
    return ont_illegal; }

bool note_term (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& s, const ::boost::json::value& val)
{   bool name_type = true;
    bool named = true;
    bool test = true;
    ::std::string vs;
    const e_ontology_property sp = wot_prop (nits, v, scope, expand_term (nits, scope, s));
    if (sp != op_illegal)
    {   switch (val.kind ())
        {   case ::boost::json::kind::object :
                name_type = process_term_object (nits, v, scope, sp, val.as_object ());
                named = test = false;
                break;
            case ::boost::json::kind::array :
                name_type = named = test = false;
                for (auto e : val.as_array ())
                    if (e.kind () != ::boost::json::kind::object)
                        note_term (nits, v, scope, s, e);
                    else
                    {   json_scope subscope (&scope);
                        const ::boost::json::object& o = e.as_object ();
                        examine_json_ld (nits, v, subscope, o);
                        process_json_ld (nits, v, subscope, o); }
                break;
            case ::boost::json::kind::string :
                vs = val.as_string ().c_str ();
                if (scope.atless_type_ && compare_no_case (s, "type")) named = test = false;
                break;
            case ::boost::json::kind::bool_ :
                vs = val.as_bool () ? "true" : "false";
                break;
            case ::boost::json::kind::int64 :
                vs = ::boost::lexical_cast < ::std::string > (val.as_int64 ());
                break;
            case ::boost::json::kind::uint64 :
                vs = ::boost::lexical_cast < ::std::string > (val.as_uint64 ());
                break;
            case ::boost::json::kind::double_ :
                vs = ::boost::lexical_cast < ::std::string > (val.as_double ());
                break;
            default :
                nits.pick (nit_json_bad_term, ed_jsonld_1_0, "8.1 Terms", es_error, ec_json, "expecting a string or an object for ", quote (s));
                name_type = named = test = false;
                break; }
        if (test) process_term_string (nits, v, scope, sp, vs);
        if (named)
        {   name_type = compare_no_case (s, "name");
            if (name_type) scope.name_ = vs; } }
    return name_type; }

bool is_suitable_kvp (const ::boost::json::key_value_pair& e, ::std::string& s)
{   if (e.key ().empty ()) return false;
    const char* k = e.key_c_str ();
    if (k == nullptr) return false;
    s = trim_the_lot_off (k);
    if (s.empty ()) return false;
    return (s.at (0) != '@'); }

bool examine_terms (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o)
{   bool name_type = true;
    const bool count_terms = (scope.terms_ == 0);
    ::std::string s;
    if (scope.type_.empty ())
        for (auto e : o)
            if (is_suitable_kvp (e, s))
            {   if (e.value ().kind () != ::boost::json::kind::string) continue;
                if (compare_no_case (s, "type"))
                {   scope.atless_type_ = true;
                    ::std::string vs = e.value ().as_string ().c_str ();
                    if (process_ontology_name_type_string (nits, v, scope, vs) == ont_illegal)
                        nits.pick (nit_jsonld_mistype, es_warning, ec_json, "were it '@type', not 'type', ", quote (vs), " would be invalid");
                    else nits.pick (nit_jsonld_mistype, es_info, ec_json, "for ", quote (vs), ", should 'type' be '@type'?"); } }
    for (auto e : o)
        if (is_suitable_kvp (e, s))
        {   if (! note_term (nits, v, scope, s, e.value ())) name_type = false;
            if (count_terms) ++scope.terms_; }
    return name_type; }

void examine_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o, const e_jtoken tk)
{   for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const char* k = e.key_c_str ();
        VERIFY_NOT_NULL (k, __FILE__, __LINE__);
        const ::std::string s = trim_the_lot_off (k);
        if (s.empty ()) nits.pick (nit_json_bad_term, ed_jsonld_1_0, "8.1 Terms", es_error, ec_json, "a term cannot be empty");
        else if (s.at (0) == '@') note_token (nits, v, scope, k, e.value (), tk); } }

void process_group_token (nitpick& nits, const html_version& v, json_scope& scope, const vv_t& vv)
{   for (auto val : vv)
    {   VERIFY_NOT_NULL (val, __FILE__, __LINE__);
        if (val.kind () != ::boost::json::kind::object)
            nits.pick (nit_json_value_object, ed_jsonld_1_0, "8.4 Lists and Sets", es_error, ec_json, "@list and @set values must be JSON objects");
        else
        {   const ::boost::json::object& o = val.as_object ();
            examine_json_ld (nits, v, scope, o);
            outer_process_json_ld (nits, v, scope, o); } } }

void insert_context_object_string (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& key, const ::std::string& s)
{   const e_ontology_type et = process_ontology_name_type_string (nits, v, scope, s);
    if (et != ont_illegal)
    {   for (auto b : scope.type_)
            if (b == et)
            {   nits.pick (nit_jsonld_context, es_warning, ec_json, sch::name (et), " was previously defined"); break; }
        if (context.tell (es_debug)) nits.pick (nit_jsonld_context, es_debug, ec_json, sch::name (et), " recognised as ", key);
        scope.type_.insert (et); } }

void process_context_object_string (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& key, const ::boost::json::key_value_pair& kvp)
{   PRESUME (kvp.value ().kind () == ::boost::json::kind::string, __FILE__, __LINE__);
    const ::std::string s (trim_the_lot_off (kvp.value ().as_string ().c_str ()));
    if (s.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "The @context URI associated with ", quote (key), " cannot be empty");
//    else insert_context_object_string (nits, v, scope, key, s); }
    else
    {   const e_ontology o = process_context_string_int (nits, v, scope, s);
        if ((o != s_none) && (o != s_error)) scope.vo_.push_back (o); } }

void process_context_object_object (nitpick& nits, const html_version& v, json_scope& scope, const ::std::string& key, const ::boost::json::key_value_pair& kvp)
{   PRESUME (kvp.value ().kind () == ::boost::json::kind::object, __FILE__, __LINE__);
    const ::boost::json::object& o = kvp.value ().as_object ();
    ::std::string id, type;
    for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const ::std::string k (trim_the_lot_off (e.key_c_str ()));
        if (k.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@context ", quote (key), " cannot have an empty child key");
        else if (e.value ().kind () != ::boost::json::kind::string) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@context ", quote (key), " can only have string / URI components.");
        else
        {   const ::std::string val (e.value ().as_string ().c_str ());
            if (compare_no_case (k, "@id"))
                if (id.empty ()) id = val;
                else nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@id repeated in ", quote (key));
            else if (compare_no_case (k, "@type"))
                if (type.empty ()) type = val;
                else nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@type repeated in ", quote (key));
            else nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@context ", quote (key), " as an unknown component ", quote (k)); } }
    if (id.empty ())
    {   if (! type.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@id expected in @context ", quote (key));
        return; }
    if (type.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@type expected in @context ", quote (key));
    else if (! compare_no_case (type, "@id")) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "unexpected value ", type, " for @type in @context ", quote (key));
    else insert_context_object_string (nits, v, scope, key, id); }

void process_context_string (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   PRESUME (val.kind () == ::boost::json::kind::string, __FILE__, __LINE__);
    const ::std::string s = val.as_string ().c_str ();
    if (s.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@context cannot have an empty value");
    else
    {   const e_ontology o = process_context_string_int (nits, v, scope, s);
        if ((o != s_none) && (o != s_error)) scope.vo_.push_back (o); } }

void process_context_object (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   PRESUME (val.kind () == ::boost::json::kind::object, __FILE__, __LINE__);
    const ::boost::json::object& o = val.as_object ();
    for (auto e : o)
    {   if (e.key ().empty ()) continue;
        const ::std::string key (trim_the_lot_off (e.key_c_str ()));
        if (key.empty ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "A @context term cannot have an empty key");
        else if (test_value < t_js_term > (nits, v, key))
            if (scope.bespoke_.find (key) != scope.bespoke_.cend ()) nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, quote (key), " is already defined");
            else switch (e.value ().kind ())
            {   case ::boost::json::kind::string :
                    process_context_object_string (nits, v, scope, key, e);
                    break;
                case ::boost::json::kind::object :
                    process_context_object_object (nits, v, scope, key, e);
                    break;
                default :
                    break; } } }

void process_context (nitpick& nits, const html_version& v, json_scope& scope, const vv_t& vv)
{   if (vv.empty ()) nits.pick (nit_empty, es_comment, ec_json, "Empty @context found.");
    else for (auto val : vv)
        switch (val.kind ())
        {   case ::boost::json::kind::string :
                process_context_string (nits, v, scope, val);
                break;
            case ::boost::json::kind::object :
                process_context_object (nits, v, scope, val);
                break;
            default :
                nits.pick (nit_jsonld_context, ed_jsonld_1_0, "5.1 The Context", es_error, ec_json, "@context can only be a string (containing a schema type), or a map.");
                break; } }

void process_single_type (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::value& val)
{   PRESUME (val.kind () == ::boost::json::kind::string, __FILE__, __LINE__);
    ::std::string s (trim_the_lot_off (val.as_string ().c_str ()));
    if (s.empty ()) nits.pick (nit_jsonld_type, ed_jsonld_1_0, "5.4 Specifying the Type", es_error, ec_json, "@type cannot have an empty value");
    else process_ontology_name_type_string (nits, v, scope, s); }

void process_type (nitpick& nits, const html_version& v, json_scope& scope, const vv_t& vv)
{   bool booboo = false;
    if (vv.empty ()) nits.pick (nit_jsonld_type, es_comment, ec_json, "Empty @type found.");
    else for (auto val : vv)
        switch (val.kind ())
        {   case ::boost::json::kind::string :
                process_single_type (nits, v, scope, val);
                break;
            case ::boost::json::kind::array :
                for (auto ta : val.as_array ())
                    if (ta.kind () == ::boost::json::kind::string) process_single_type (nits, v, scope, ta.as_string ());
                    else
                    {   if (! booboo) nits.pick (nit_jsonld_type, ed_jsonld_1_0, "5.4 Specifying the Type", es_error, ec_json, "@type requires a string or an array of strings");
                        booboo = true; }
                break;
            default :
                nits.pick (nit_jsonld_type, ed_jsonld_1_0, "5.4 Specifying the Type", es_error, ec_json, "@type requires a string or an array of strings");
                break; } }

bool process_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o)
{   PRESUME (scope.keyword_.size () >= jt_error, __FILE__, __LINE__);
    bool name_type = true;
    for (int i = 0; i < jt_error; ++i)
        if (! scope.keyword_.at (i).empty ())
                // the specs are badly phrased here. They state some keywords "must be ignored when processed",
                // then immediately discuss how they are to be processed. What they mean is that the keywords
                // are not content, but metacontent.
            switch (i)
            {   case jt_container :
                case jt_direction :
                case jt_graph :
                case jt_id :
                case jt_import :
                case jt_included :
                case jt_index :
                case jt_json :
                case jt_language :
                    name_type = false;
                    break;
                case jt_context :
                    name_type = false;
                    process_context (nits, v, scope, scope.keyword_.at (i));
                    break;
                case jt_list :
                case jt_set :
                    name_type = false;
                    process_group_token (nits, v, scope, scope.keyword_.at (i));
                    break;
                case jt_nest :
                case jt_none :
                case jt_prefix :
                case jt_propagate :
                case jt_protected :
                case jt_reverse :
                    name_type = false;
                    break;
                case jt_type :
                    process_type (nits, v, scope, scope.keyword_.at (i));
                    break;
                case jt_value :
                case jt_version :
                case jt_vocab :
                    name_type = false;
                    break;
                default :
                    break; }
    if (! examine_terms (nits, v, scope, o)) name_type = false;
    return name_type; }

void outer_process_json_ld (nitpick& nits, const html_version& v, json_scope& scope, const ::boost::json::object& o)
{   bool limited = true;
    PRESUME (scope.keyword_.size () >= static_cast < ::std::size_t > (jt_error) - 1, __FILE__, __LINE__);
    bool gt = true;
    for (int i = 0; i < jt_error; ++i)
        if (! scope.keyword_.at (i).empty ())
        {   limited = false;
            if (gt) gt = (i == jt_graph) || (i == jt_context);
            if (! gt) break; }
    process_json_ld (nits, v, scope, o);
    if (gt && (scope.terms_ == 0)) nits.pick (nit_json_invalid_node, ed_jsonld_1_0, "8.2 Node Objects", es_warning, ec_json, "A topmost JSON-LD node must contain more than just @graph and @context");
    else if (limited) nits.pick (nit_json_invalid_node, ed_jsonld_1_0, "8.2 Node Objects", es_warning, ec_json, "A topmost JSON-LD node must contain keywords"); }

void parse_json_ld (nitpick& nits, const html_version& v, const ::std::string& s, const e_charcode encoding)
{   if (! s.empty ())
    {   nits.set_context (0, "JSON-LD");
        jsonic jhbbc (nits, s, encoding);
        if (! jhbbc.val ().is_object ()) nits.pick (nit_json_error, es_error, ec_json, "cannot parse as JSON-LD");
        else
        {   json_scope scope;
            const ::boost::json::object& o = jhbbc.val ().as_object ();
            examine_json_ld (nits, v, scope, o);
            outer_process_json_ld (nits, v, scope, o); } } }

#endif // NO_JSONIC