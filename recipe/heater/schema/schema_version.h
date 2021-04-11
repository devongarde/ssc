/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "main/version.h"

#define SV_NOT_30       0x00000001
#define SV_NOT_31       0x00000002
#define SV_NOT_32       0x00000004
#define SV_NOT_33       0x00000008
#define SV_NOT_34       0x00000010
#define SV_NOT_3034     0x0000001F
#define SV_NOT_3134     0x0000001E

#define SV_DEP20        0x00010000
#define SV_DEP21        0x00020000
#define SV_DEP30        0x00040000
#define SV_DEP31        0x00080000
#define SV_DEP32        0x00100000
#define SV_DEP33        0x00200000
#define SV_DEP34        0x00400000

#define SV_WILDCARD     0x80000000

#define SV_DEP_3034     ( SV_DEP30 | SV_DEP31 | SV_DEP32 | SV_DEP33 | SV_DEP34 )
#define SV_FLAG_MASK    0xFFFFFFFF
#define SV_ROOT_SHIFT   32

#define DEFAULT_SCHEMA_MAJOR 12
#define DEFAULT_SCHEMA_MINOR 0
#define DEFAULT_SCHEMA_VERSION "12"

const unsigned char schema_major_max = DEFAULT_SCHEMA_MAJOR;
class html_version;

bool is_valid_schema_version (const e_microdata_root root, const unsigned char mjr, const unsigned char mnr);

struct schema_version : public version
{   schema_version () = default;
    schema_version (const unsigned char mjr, const unsigned char mnr, const uint64_t sf = NOFLAGS)
        :   version (mjr, mnr, (static_cast < uint64_t > (mdr_schema) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    {   DBG_ASSERT (! invalid ()); }
    schema_version (const e_microdata_root root, const unsigned char mjr, const unsigned char mnr, const uint64_t sf = NOFLAGS)
        :   version (mjr, mnr, (static_cast < uint64_t > (root) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    {   DBG_ASSERT (! invalid ()); }
    schema_version (const schema_version& ) = default;
    schema_version (const html_version& v);
#ifndef NO_MOVE_CONSTRUCTOR
	schema_version (schema_version&& ) = default;
#endif // VS
	~schema_version () = default;
    schema_version& operator = (const schema_version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	schema_version& operator = (schema_version&&) = default;
#endif // VS
    static void init ();
    void reset ()
    {   schema_version v; swap (v); }
    void reset (const schema_version& v)
    {   schema_version vv (v); swap (vv); }
    bool unknown () const { return (mjr () == 0) && (mnr () == 0); }
    bool known () const { return ! unknown (); }
    bool is_not (const unsigned char mj, const unsigned char mn = 0xFF) const
    {   if (unknown ()) return false;
        if (mj != mjr ()) return true;
        return ((mn != 0xFF) && (mn != mnr ())); }
    bool is_not (const schema_version& v) const
    {   return is_not (v.mjr (), v.mnr ()); }
    bool invalid () const { return ! is_valid_schema_version (root (), mjr (), mnr ()); }
    e_microdata_root root () const
    {   return static_cast < e_microdata_root > (flags () >> SV_ROOT_SHIFT); }
    ::std::string report () const; };

typedef ::std::vector < schema_version > vsv_t;
extern vsv_t vsv;

const schema_version default_schema (mdr_none, 0, 0);

const schema_version schema_0 (mdr_schema, 0, 0);
const schema_version schema_2_0 (mdr_schema, 2, 0);
const schema_version schema_2_1 (mdr_schema, 2, 1);
const schema_version schema_2_2 (mdr_schema, 2, 2);
const schema_version schema_3_0 (mdr_schema, 3, 0);
const schema_version schema_3_1 (mdr_schema, 3, 1);
const schema_version schema_3_2 (mdr_schema, 3, 2);
const schema_version schema_3_3 (mdr_schema, 3, 3);
const schema_version schema_3_4 (mdr_schema, 3, 4);
const schema_version schema_3_5 (mdr_schema, 3, 5);
const schema_version schema_3_6 (mdr_schema, 3, 6);
const schema_version schema_3_7 (mdr_schema, 3, 7);
const schema_version schema_3_8 (mdr_schema, 3, 8);
const schema_version schema_3_9 (mdr_schema, 3, 9);
const schema_version schema_4 (mdr_schema, 4, 0);
const schema_version schema_5 (mdr_schema, 5, 0);
const schema_version schema_6 (mdr_schema, 6, 0);
const schema_version schema_7_00 (mdr_schema, 7, 0);
const schema_version schema_7_01 (mdr_schema, 7, 1);
const schema_version schema_7_02 (mdr_schema, 7, 2);
const schema_version schema_7_03 (mdr_schema, 7, 3);
const schema_version schema_7_04 (mdr_schema, 7, 4);
const schema_version schema_8 (mdr_schema, 8, 0);
const schema_version schema_9 (mdr_schema, 9, 0);
const schema_version schema_10 (mdr_schema, 10, 0);
const schema_version schema_11 (mdr_schema, 11, 0);
const schema_version schema_12 (mdr_schema, 12, 0);
const schema_version schema_default (mdr_schema, DEFAULT_SCHEMA_MAJOR, DEFAULT_SCHEMA_MINOR);

const schema_version whatwg_schema (mdr_whatwg, 1, 0);

const schema_version mf_1 (mdr_microformats, 1, 0);
const schema_version mf_2 (mdr_microformats, 2, 0);
const schema_version mf_all (mdr_microformats, 2, 0, SV_WILDCARD);

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to);
bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to);

template < > inline bool does_apply < schema_version > (const schema_version& v, const schema_version& from, const schema_version& to)
{   return does_schema_apply (v, from, to); }
