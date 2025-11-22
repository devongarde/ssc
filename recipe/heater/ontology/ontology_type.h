/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "symbol/symbol.h"
#include "feedback/nitpick.h"
#include "ontology/ontology_version.h"

#define SF_ENUMERATION          0x01000000
#define SF_EXTERNAL_ENUMERATION 0x02000000
#define SF_NO_ITEMID            0x04000000
#define SF_DEPRECATED           0x08000000
#define SF_VAGUE                0x10000000
#define SF_SIMPLE_MASK          0x00FFFFFF
#define SF_NO_SIMPLE_TYPE       0

typedef ::std::vector < e_ontology_type > vsch_t;

#define HIERARCHY_DEBUG
#ifdef HIERARCHY_DEBUG
typedef ::std::vector < e_ontology_type > ssch_t;
#else // HIERARCHY_DEBUG
typedef ::std::set < e_ontology_type > ssch_t;
#endif // HIERARCHY_DEBUG

struct sch : symbol < ontology_version, e_ontology_type, e_ontology, s_schema, sz_true >
{   sch () {}
    sch (nitpick& nits, const html_version& v, const ::std::string& x, const e_ontology root = s_schema);
    static e_ontology_type parse (nitpick& nits, const html_version& v, const ::std::string& x, const e_ontology root = s_schema);
    static void init (nitpick& nits);
    bool unknown () const noexcept
    {   return (symbol < ontology_version, e_ontology_type, e_ontology, s_schema, sz_true > :: unknown ()) ||
        (symbol < ontology_version, e_ontology_type, e_ontology, s_schema, sz_true > :: get () == ont_illegal); }
    bool enumerated () const noexcept;
    bool has_simple_type () const noexcept;
    bool external_enumerated () const noexcept;
    bool vague () const noexcept;
    e_ontology root () const noexcept;
    static e_ontology root (const e_ontology_type st);
    static bool vague (const e_ontology_type st);
    e_type get_simple_type () const noexcept; };

#ifndef HIERARCHY_DEBUG
inline void insert_ssch (ssch_t& x, const e_ontology_type s)
{   x.insert (s); }
inline bool find_ssch (const ssch_t& x, const e_ontology_type s)
{   return x.find (s) != x.cend (); }
#else // HIERARCHY_DEBUG
inline void insert_ssch (ssch_t& x, const e_ontology_type s)
{   x.push_back (s); }
inline bool find_ssch (const ssch_t& x, const e_ontology_type s)
{   for (ssch_t::const_iterator i = x.cbegin (); i != x.cend (); ++i)
        if (*i == s) return true;
    return false; }
#endif // HIERARCHY_DEBUG

CONSTEXPR inline bool enumerated_ontology_type (const flags_t flags) noexcept
{ return (flags & SF_ENUMERATION) == SF_ENUMERATION; }

CONSTEXPR inline bool has_simple_ontology_type (const flags_t flags) noexcept
{ return (flags & SF_SIMPLE_MASK) != 0; }

CONSTEXPR inline bool external_enumerated_ontology_type (const flags_t flags) noexcept
{ return (flags & SF_EXTERNAL_ENUMERATION) == SF_EXTERNAL_ENUMERATION; }

CONSTEXPR inline e_type get_simple_ontology_type (const flags_t flags) noexcept
{ return static_cast < e_type > (flags & SF_SIMPLE_MASK); }

CONSTEXPR inline bool is_itemid_ok (const flags_t flags) noexcept
{ return (flags & SF_NO_ITEMID) == 0; }

CONSTEXPR inline bool has_fluffy_description (const flags_t flags) noexcept
{ return (flags & SF_VAGUE) == SF_VAGUE; }
