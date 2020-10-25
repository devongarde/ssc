/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type.h"

const e_property first_class = static_cast < e_property > (c_context);
const e_property first_rel = first_class + static_cast < e_property > (class_size);
const e_property last_class = first_rel - 1;
const e_property first_illegal = first_rel + static_cast < e_property > (rel_size);
const e_property last_rel = first_illegal - 1;

inline bool is_vocabulary (const e_property p) { return ((p >= h1_aggregate) && (p <= h_aggregate)); }
inline bool is_property (const e_property p) { return ((p >= mf1_additional_name) && (p <= u_search)); }
inline bool is_mf1 (const e_property p) { return ((p >= h1_aggregate) && (p <= h1_xoxo)) || ((p >= h1_aggregate) && (p <= mf1_website)) ; }
inline bool is_mf2 (const e_property p) { return ((p >= h_adr) && (p <= h_aggregate)) || ((p >= dt_accessed) && (p <= u_search)) ; }
inline bool is_mf_class (const e_property p) { return (p >= first_class) && (p <= last_class); }
inline bool is_mf_rel (const e_property p) { return (p >= first_rel) && (p <= last_rel); }

class prop  // would be better templated
{   e_property value_ = 0;
    typedef enum { ps_unknown, ps_class, ps_rel, ps_invalid } state_t;
    state_t state_ = ps_unknown;

    void assign (const e_property value)
    {   value_ = value;
        if (value_ >= first_class && value <= last_class) state_ = ps_class;
        else if (value_ >= first_rel && value <= last_rel) state_ = ps_rel;
        else state_ = ps_invalid; }
    void reset (const e_class e)
    {   assert (html_class::is_microformat_property (e));
        assign (static_cast < e_property > (e) + first_class);
        assert (value_ <= last_class); }
    void reset (const e_rel e)
    {   assert (rel::is_microformat_property (e));
        assign (static_cast < e_property > (e) + first_rel);
        assert (value_ <= last_rel); }
public:
    typedef e_property value_type;
    prop () = default;
    prop (const prop& ) = default;
    prop (prop&& ) = default;
    ~prop () = default;
    prop& operator = (const prop& ) = default;
    prop& operator = (prop&& ) = default;
    explicit prop (const html_class& c) { reset (c); }
    explicit prop (const rel& r) { reset (r); }
    explicit prop (const e_class c) { reset (c); }
    explicit prop (const e_rel r) { reset (r); }
    explicit prop (const e_property p) { reset (p); }
    explicit prop (nitpick& nits, const html_version& v, const ::std::string& s) { set_value (nits, v, s); }
    void swap (prop& p) noexcept
    {   ::std::swap (value_, p.value_);
        ::std::swap (state_, p.state_); }
    void reset () { prop p; swap (p); }
    void reset (const e_property p)
    { prop pp; pp.assign (p); swap (pp); }
    void reset (const html_class& c) { reset (c.get ()); }
    void reset (const rel& r) { reset (r.get ()); }
    bool unknown () const { return state_ == ps_unknown; }
    bool invalid () const { return state_ == ps_invalid; }
    bool is_class () const { return state_ == ps_class; }
    bool is_rel () const { return state_ == ps_rel; }
    e_class get_class () const
    {   if (is_class ()) return static_cast < e_class > (value_ - first_class);
        return c_error; }
    e_rel get_rel () const
    {   if (is_rel ()) return static_cast < e_rel > (value_ - first_rel);
        return r_illegal; }
    ::std::string get_string () const
    {   switch (state_)
        {   case ps_class : return html_class :: name (get_class ());
            case ps_rel : return rel :: name (get_rel ());
            default: return ::std::string (); } }
    ::std::string name () const { return get_string (); }
    static ::std::string name (const e_property p)
    {   prop pp (p); return pp.get_string (); }
    e_property get () const { return value_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   html_class c (nits, v, s);
        if (c.is_microformat_property ()) reset (c);
        else
        {   rel r (nits, v, s);
            if (r.is_microformat_property ()) reset (r);
            else reset (); } } };

inline e_class get_property_class (const e_property p)
{   prop pp (p); return pp.get_class (); }
inline e_rel get_property_rel (const e_property p)
{   prop pp (p); return pp.get_rel (); }
inline e_property get_class_property (const e_class c)
{   prop pp (c); return pp.get (); }
inline e_property get_rel_property (const e_rel r)
{   prop pp (r); return pp.get (); }
