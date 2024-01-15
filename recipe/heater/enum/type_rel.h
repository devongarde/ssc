/*
ssc (static site checker)
File Info
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
#include "enum/type_enum_vec.h"
#include "simple/type_rdf.h"

const e_rel first_mf1_rel = r_entry_category;
const e_rel last_mf1_rel = r_tag;
const e_rel first_mf2_rel = r_acquaintance;
const e_rel last_mf2_rel = r_accessibility;
CONSTEXPR ::std::size_t rel_size = static_cast < ::std::size_t > (r_illegal + 1);

void check_rel_spelling (nitpick& nits, const html_version& v, const ::std::string& original);

template < > inline void enum_vec < t_rel, e_rel > :: set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   enum_vec < t_rel, e_rel > :: original_ = ss;
    bool res = true;
    vstr_t strs (split_by_comma_space (trim_the_lot_off (ss)));
    for (auto s : strs)
    {   bool bad = false;
        base_t t;
        if (context.rdfa () && (s.find (':') != ::std::string::npos))
        {   type_master < t_curie > c;
            c.set_value (nits, v, s);
            t.status (c.status ());
            if (c.invalid ()) bad = true;
            t.original_ = s;
            t.set (r_curie); }
        else
        {   t.set_value (nits, v, s);
            bad = t.invalid (); }
        value_.push_back (t);
        if (bad)
        {   res = false;
            check_rel_spelling (nits, v, s); } }
    if (strs.size () == 0) enum_vec < t_rel, e_rel > :: status (s_empty);
    else if (res) enum_vec < t_rel, e_rel > :: status (s_good);
    else enum_vec < t_rel, e_rel > :: status (s_invalid); }

template < > inline bool type_base < e_rel, t_rel > :: is_relational () noexcept
{ return true; }

struct rel : enum_n < t_rel, e_rel >
{   rel () = default;
    explicit rel (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (context.rdfa () && (s.find (':') != ::std::string::npos))
        {   type_master < t_curie > c;
            c.set_value (nits, v, s);
            enum_n < t_rel, e_rel > :: status (c.status ());
            enum_n < t_rel, e_rel > :: original_ = s;
            enum_n < t_rel, e_rel > :: set (r_curie); }
        else enum_n < t_rel, e_rel > :: set_value (nits, v, s); }
    explicit rel (element* box) noexcept : enum_n < t_rel, e_rel > (box) { }
    rel (const rel& r) = default;
    rel (rel&& r) = default;
    ~rel () = default;
    rel& operator = (const rel& ) = default;
    rel& operator = (rel&& ) = default;
    CONSTEXPR static bool is_microformat (const e_rel value) noexcept
    {   return value >= first_mf1_rel && value <= last_mf2_rel; }
    CONSTEXPR static bool is_microformat_vocabulary (const e_rel ) noexcept
    {   return false; }
    CONSTEXPR static bool is_microformat_property (const e_rel value) noexcept
    {   return is_microformat (value); }
    CONSTEXPR static bool is_microformat_v1 (const e_rel value) noexcept
    {   return (value >= first_mf1_rel && value <= last_mf1_rel); }
    CONSTEXPR static bool is_microformat_v2 (const e_rel value) noexcept
    {   return (value >= first_mf2_rel && value <= last_mf2_rel); }
    CONSTEXPR static bool is_rel () { return true; }
    bool is_microformat () const noexcept { return good () && is_microformat (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_property () const noexcept { return is_microformat_property (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_vocabulary () const noexcept { return is_microformat_vocabulary (enum_base < e_rel, t_rel > :: value_); }
    bool is_microformat_v1 () const noexcept { return good () && is_microformat_v1 (enum_base < e_rel, t_rel > :: value_ ); }
    bool is_microformat_v2 () const noexcept { return good () && is_microformat_v2 (enum_base < e_rel, t_rel > :: value_); } };
