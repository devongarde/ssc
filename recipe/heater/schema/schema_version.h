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

#define SV_DEP_3034     0x007B0000

typedef unsigned int schema_flag_t;
const unsigned char schema_major_max = 10;
class html_version;
class schema_version;

schema_version html_to_schema_version (const html_version& v);
bool is_valid_schema_version (const unsigned char major, const unsigned char minor);

class schema_version
{   unsigned char major_ = 0, minor_ = 0;
    schema_flag_t flags_ = 0;
public:
    schema_version () : major_ (0), minor_ (0), flags_ (0) { }
    schema_version (const unsigned char major, const unsigned char minor, const schema_flag_t sf = 0)
        :   major_ (major), minor_ (minor), flags_ (sf)
    { if (invalid ()) major_ = minor_ = 0; }
    schema_version (const schema_version& ) = default;
    schema_version (const html_version& v);
    schema_version (schema_version&& ) = default;
    ~schema_version () = default;
    schema_version& operator = (const schema_version& ) = default;
    schema_version& operator = (schema_version&& ) = default;
    void swap (schema_version& v) noexcept;
    void reset () { schema_version v; swap (v); }
    void reset (const schema_version& v) { schema_version vv (v); swap (vv); }
    bool unknown () const { return (major_ == 0) && (minor_ == 0); }
    bool known () const { return ! unknown (); }
    bool is_not (const unsigned char major, const unsigned char minor = 0xFF) const
    {   if (unknown ()) return false;
        if (major != major_) return true;
        return ((minor != 0xFF) && (minor != minor_)); }
    bool is_not (const schema_version& v) const
    {   return is_not (v.major_, v.minor_); }
    unsigned char major () const { return major_; }
    unsigned char minor () const { return minor_; }
    bool invalid () const { return ! is_valid_schema_version (major_, minor_); }
    schema_flag_t flags () const { return flags_; }
    ::std::string report () const; };

const schema_version schema_0;
const schema_version schema_2_0 (2, 0);
const schema_version schema_2_1 (2, 1);
const schema_version schema_2_2 (2, 2);
const schema_version schema_3_0 (3, 0);
const schema_version schema_3_1 (3, 1);
const schema_version schema_3_2 (3, 2);
const schema_version schema_3_3 (3, 3);
const schema_version schema_3_4 (3, 4);
const schema_version schema_3_5 (3, 5);
const schema_version schema_3_6 (3, 6);
const schema_version schema_3_7 (3, 7);
const schema_version schema_3_8 (3, 8);
const schema_version schema_3_9 (3, 9);
const schema_version schema_4 (4, 0);
const schema_version schema_5 (5, 0);
const schema_version schema_6 (6, 0);
const schema_version schema_7_00 (7, 0);
const schema_version schema_7_01 (7, 1);
const schema_version schema_7_02 (7, 2);
const schema_version schema_7_03 (7, 3);
const schema_version schema_7_04 (7, 4);
const schema_version schema_8 (8, 0);
const schema_version schema_9 (9, 0);
const schema_version schema_10 (10, 0);

bool operator == (const schema_version& lhs, const schema_version& rhs);
bool operator != (const schema_version& lhs, const schema_version& rhs);
bool operator < (const schema_version& lhs, const schema_version& rhs);
bool operator > (const schema_version& lhs, const schema_version& rhs);
bool operator <= (const schema_version& lhs, const schema_version& rhs);
bool operator >= (const schema_version& lhs, const schema_version& rhs);
bool does_apply (const schema_version& v, const schema_version& from, const schema_version& to);
bool may_apply (const schema_version& v, const schema_version& from, const schema_version& to);
bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to);
