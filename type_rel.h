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
#include "type_enum_vec.h"

const e_rel first_mf1_rel = r_entry_category;
const e_rel last_mf1_rel = r_tag;
const e_rel first_mf2_rel = r_acquaintance;
const e_rel last_mf2_rel = r_accessibility;
const ::std::size_t rel_size = static_cast < ::std::size_t > (r_illegal + 1);

void check_rel_spelling (nitpick& nits, const html_version& v, const ::std::string& original);

template < > inline void enum_vec < t_rel, e_rel > :: set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   enum_vec < t_rel, e_rel > :: original_ = ss;
    bool res = true; vstr_t strs;
    ::boost::algorithm::split (strs, trim_the_lot_off (ss), ::boost::algorithm::is_any_of (", "), ::boost::algorithm::token_compress_on);
    for (auto s : strs)
    {   base_t t;
        t.set_value (nits, v, s);
        value_.push_back (t);
        if (t.invalid ())
        {   res = false;
            check_rel_spelling (nits, v, s); } }
    if (strs.size () == 0) enum_vec < t_rel, e_rel > :: status (s_empty);
    else if (res) enum_vec < t_rel, e_rel > :: status (s_good);
    else enum_vec < t_rel, e_rel > :: status (s_invalid); }

template < > inline bool type_base < e_rel, t_rel > :: is_relational ()
{ return true; }

struct rel : enum_n < t_rel, e_rel >
{   rel () = default;
    rel (const rel& ) = default;
    rel (rel&& ) = default;
    explicit rel (nitpick& nits, const html_version& v, const ::std::string& s)
    {   enum_n < t_rel, e_rel > :: set_value (nits, v, s); }
    ~rel () = default;
    rel& operator = (const rel& ) = default;
    rel& operator = (rel&& ) = default;
    static bool is_microformat (const e_rel value)
    {   return value >= first_mf1_rel && value <= last_mf2_rel; }
    static bool is_microformat_vocabulary (const e_rel )
    {   return false; }
    static bool is_microformat_property (const e_rel value)
    {   return is_microformat (value); }
    static bool is_microformat_v1 (const e_rel value)
    {   return (value >= first_mf1_rel && value <= last_mf1_rel); }
    static bool is_microformat_v2 (const e_rel value)
    {   return (value >= first_mf2_rel && value <= last_mf2_rel); }
    constexpr static bool is_rel () { return true; }
    bool is_microformat () const { return good () && is_microformat (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_property () const { return is_microformat_property (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_vocabulary () const { return is_microformat_vocabulary (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_v1 () const { return good () && is_microformat_v1 (enum_base < e_rel, t_rel > :: value_ ); }
    bool is_microformat_v2 () const { return good () && is_microformat_v2 (enum_base < e_rel, t_rel > :: value_); } };
