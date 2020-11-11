/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "schema/schema_version.h"
#include "parser/html_version.h"

schema_version::schema_version (const html_version& v)
{   schema_version sv;
    sv.mjr_ = v.mjr ();
    sv.mnr_ = v.mnr ();
    if (! sv.invalid ()) swap (sv); }

void schema_version::swap (schema_version& v) NOEXCEPT
{   ::std::swap (mjr_, v.mjr_);
    ::std::swap (mnr_, v.mnr_);
    ::std::swap (flags_, v.flags_); }

::std::string schema_version::report () const
{   ::std::ostringstream res;
    if (known ())
        if (mjr_ == 7)
            res << static_cast < int > (mjr_) << ".0" << static_cast < int > (mnr_);
        else res << static_cast < int > (mjr_) << "." << static_cast < int > (mnr_);
    return res.str (); }

bool operator == (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.mjr () != rhs.mjr ()) return false;
    return (lhs.mnr () == rhs.mnr ()); }

bool operator != (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs == rhs); }

bool operator < (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.mjr () > rhs.mjr ()) return false;
    if (lhs.mjr () < rhs.mjr ()) return true;
    return (lhs.mnr () < rhs.mnr ()); }

bool operator > (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs) && ! (lhs == rhs); }

bool operator <= (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs > rhs); }

bool operator >= (const schema_version& lhs, const schema_version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs); }

bool does_apply (const schema_version& v, const schema_version& from, const schema_version& to)
{   if (! from.unknown () && (v < from)) return false;
    if (! to.unknown () && (v > to)) return false;
    return true; }

bool may_apply (const schema_version& v, const schema_version& from, const schema_version& to)
{   return (v.unknown () || does_apply (v, from, to)); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

schema_version html_to_schema_version (const html_version& v)
{   if (v.mjr () >= 5)
        switch (w3_minor_5 (v))
        {   case 0 :
                return schema_2_0;
            case 1 :
                return schema_3_2;
            case 2 :
                return schema_3_3;
            case 3 :
                return schema_3_4;
            case 4 :
                return schema_9;
            default :
                assert (false); }
    return schema_0; }

bool is_valid_schema_version (const unsigned char mjr, const unsigned char mnr)
{   if ((mjr == 0) && (mnr == 0)) return true;
    if ((mjr > schema_major_max) || (mjr < 2)) return false;
    if (mnr > 9) return false;
    switch (mjr)
    {   case 2 : return mnr < 3;
        case 3 : return true;
        case 7 : return mnr < 5;
        default : return mnr == 0; } }
