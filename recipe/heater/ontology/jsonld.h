/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "feedback/nitpick.h"

#ifdef NO_JSONIC
inline void parse_json_ld (nitpick& , const html_version& , const ::std::string& , const e_charcode = cc_ansi) { }
#else // NO_JSONIC
#include "parser/jsonic.h"

// this is not, and not intended to be, a full json-ld interpreter. It exists, mostly, to enable schema testing.

typedef ::std::vector < ::boost::json::value > vjv_t;
typedef ::std::vector < vjv_t > vk_t;
typedef ssc_map < ::std::string, e_ontology_property > mssp_t;
typedef ssc_map < ::std::string, e_ontology > mso_t;
typedef ::std::vector < ontology_version > vov_t;

struct json_scope
{   json_scope* parent_ = nullptr;
    vk_t keyword_;
    url base_;
    mso_t mso_;
    ssch_t type_;
    mssp_t bespoke_;
    sstr_t id_;
    ::std::string name_;
    unsigned int terms_ = 0;
    bool atless_type_ = false;
    json_scope ()
    {   keyword_.resize (jt_error); }
    json_scope (const json_scope& js) = default;
    json_scope (json_scope&& js) = default;
    explicit json_scope (json_scope* parent)
    {   keyword_.resize (jt_error);
        parent_ = parent; }
    json_scope& operator = (const json_scope& js) = default;
    json_scope& operator = (json_scope&& js) = default;
    ~json_scope () = default;
#ifdef DEBUG
    ::std::string rpt (const ::std::string& n) const
    {   ::std::string r (n);
        r += ':';
        for (auto m : mso_)
        {   r += ' '; r += m.first; } 
        r += "\n";
        return r; }
#endif // DEBUG
    mso_t ontologies () const
    {   if (! mso_.empty ()) return mso_;
        if (parent_ != nullptr) return parent_ -> ontologies ();
        return mso_t (); } };

#ifdef DEBUG
//#define SRPT(XXX) scope_.rpt (XXX)
#define SRPT(XXX)
#else // DEBUG
#define SRPT(XXX)
#endif // DEBUG

struct scoped_scope
{   json_scope old_;
    json_scope& zombie_;
    scoped_scope () = delete;
    NO_COPY_NO_MOVE (scoped_scope);
    explicit scoped_scope (json_scope& js) : old_ (js), zombie_ (js)
    { }
    ~scoped_scope ()
    {   try
        {   zombie_ = old_; }
        catch (...)
        {   GRACELESS_CRASH (__FILE__, __LINE__); } } };

class json_ld
{   json_scope scope_;
    jsonic jsonic_;
    html_version v_;
    e_ontology_property get_ontology_property (nitpick& nits, const ::std::string& s);
    void insert_mso (const ::std::string& key, const e_ontology o);
    void note_token (nitpick& nits, const ::std::string& s, const ::boost::json::value& val, const e_jtoken tk);
    bool separate_ontology_wot (nitpick& nits, const ::std::string& s, e_ontology& o, ::std::string& wot) const;
    e_ontology_property wot_prop (nitpick& nits, const ::std::string& s) const;
    bool process_map (nitpick& nits, const ::boost::json::object& o, const e_type key_type);
    e_ontology_type process_ontology_name_type_string_int (nitpick& nits,  const ::std::string& s, const e_ontology o = s_none, const bool mention = false);
    e_ontology_type process_ontology_name_type_string (nitpick& nits, const ::std::string& s, const bool mention = false);
    bool process_term_object (nitpick& nits, const e_ontology_property p, const ::boost::json::object& obj);
    void process_term_string (nitpick& nits, const e_ontology_property p, const ::std::string& s);
    e_ontology process_context_string_int (nitpick& nits, const ::std::string& s);
    bool note_term (nitpick& nits, const ::std::string& s, const ::boost::json::value& val);
    bool examine_terms (nitpick& nits, const ::boost::json::object& o);
    void examine_json_ld (nitpick& nits, const ::boost::json::object& o, const e_jtoken tk = jt_error);
    void process_group_token (nitpick& nits, const vjv_t& vv);
    void insert_context_object_string (nitpick& nits, const ::std::string& key, const ::std::string& s);
    void process_context_object_string (nitpick& nits, const ::std::string& key, const ::boost::json::key_value_pair& kvp);
    void process_context_object_object (nitpick& nits, const ::std::string& key, const ::boost::json::key_value_pair& kvp);
    void process_context_string (nitpick& nits, const ::boost::json::value& val);
    void process_context_object (nitpick& nits, const ::boost::json::value& val);
    void process_context (nitpick& nits, const vjv_t& vv);
    void process_id (nitpick& nits, const vjv_t& vv);
    void process_language (nitpick& nits, const vjv_t& vv);
    void process_vocab (nitpick& nits, const vjv_t& vv);
    void process_single_type (nitpick& nits, const ::boost::json::value& val);
    void process_type (nitpick& nits, const vjv_t& vv);
    bool process_json_ld (nitpick& nits, const ::boost::json::object& o);
    void outer_process_json_ld (nitpick& nits,  const ::boost::json::object& o);
public:
    json_ld () = delete;
    json_ld (const json_ld& jld) = delete;
    json_ld (json_ld&& jld) = delete;
    json_ld& operator = (const json_ld& jld) = delete;
    json_ld& operator = (json_ld&& jld) = delete;
    ~json_ld () = default;
    explicit json_ld (const html_version& v) : v_ (v) { }
    json_ld (nitpick& nits, const html_version& v, const ::std::string& s, const e_charcode encoding = cc_ansi) : v_ (v)
    {   parse (nits, s, encoding); }
    void parse (nitpick& nits, const ::std::string& s, const e_charcode encoding = cc_ansi); };

inline void parse_json_ld (nitpick& nits, const html_version& v, const ::std::string& s, const e_charcode encoding = cc_ansi)
{   json_ld jld (nits, v, s, encoding); }

#endif // NO_JSONIC
