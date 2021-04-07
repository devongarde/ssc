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

#include "main/standard.h"
#include "main/version.h"

::std::string version::name () const
{   ::std::ostringstream res;
    res << mjr_;
    if (mnr_ != 0) res << "." << mnr_;
    return res.str (); }

::std::string version::report () const
{   ::std::ostringstream res;
    res << name ();
    if (flags_ != 0) res << "f" << ::std::hex << flags_;
    return res.str (); }

bool operator == (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.mjr () != rhs.mjr ()) return false;
    return (lhs.mnr () == rhs.mnr ()); }

bool operator != (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs == rhs); }

bool operator < (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    if (lhs.mjr () > rhs.mjr ()) return false;
    if (lhs.mjr () < rhs.mjr ()) return true;
    return (lhs.mnr () < rhs.mnr ()); }

bool operator > (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs) && ! (lhs == rhs); }

bool operator <= (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs > rhs); }

bool operator >= (const version& lhs, const version& rhs)
{   if (lhs.unknown () || rhs.unknown ()) return false;
    return ! (lhs < rhs); }
