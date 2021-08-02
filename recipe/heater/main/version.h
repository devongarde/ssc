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

class version
{   unsigned char mjr_ = 0, mnr_ = 0;
    flags_t flags_ = NOFLAGS;
public:
    version () = default;
    version (const unsigned char mjr, const unsigned char mnr, const flags_t flags = NOFLAGS)
        :   mjr_ (mjr), mnr_ (mnr), flags_ (flags) { }
	version (const version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	version (version&& ) = default;
#endif // VS
	~version () = default;
    version& operator = (const version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	version& operator = (version&& ) = default;
#endif // VS
    void swap (version& v) NOEXCEPT
    {   ::std::swap (mjr_, v.mjr_);
        ::std::swap (mnr_, v.mnr_);
        ::std::swap (flags_, v.flags_); }
    void reset () { version v; swap (v); }
    void reset (const version& v) { version vv (v); swap (vv); }
    void set_mjr (const unsigned char mjr, const unsigned char mnr = 0) NOEXCEPT
    {   mjr_ = mjr; mnr_ = mnr; }
    bool unknown () const { return (mjr_ == 0) && (mnr_ == 0); }
    bool known () const { return ! unknown (); }
    unsigned char mjr () const { return mjr_; }
    unsigned char mnr () const { return mnr_; }
    void set_flags (const flags_t u) { flags_ |= u; }
    void reset_flags (const flags_t u) { flags_ &= ~u; }
    bool all_flags (const flags_t u) const { return ((flags_ & u) == u); }
    bool any_flags (const flags_t u) const { return ((flags_ & u) != 0); }
    bool no_flags (const flags_t u) const { return ((flags_ & u) == 0); }
    flags_t flags () const { return flags_; }
    bool empty () const { return (mjr_ == 0) && (mnr_ == 0); }
    ::std::string name () const;
    ::std::string report () const; };

bool operator == (const version& lhs, const version& rhs);
bool operator != (const version& lhs, const version& rhs);
bool operator < (const version& lhs, const version& rhs);
bool operator > (const version& lhs, const version& rhs);
bool operator <= (const version& lhs, const version& rhs);
bool operator >= (const version& lhs, const version& rhs);

template < class V > inline bool does_apply  (const V& v, const V& from, const V& to)
{   if (! from.unknown () && (v < from)) return false;
    if (! to.unknown () && (v > to)) return false;
    return true; }

template < class V > inline bool may_apply (const V& v, const V& from, const V& to)
{   return (v.unknown () || does_apply < V > (v, from, to)); }
