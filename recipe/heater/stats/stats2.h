/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#pragma once

template < class FAMILY, class MEMBER, FAMILY max_family, MEMBER max_member > class stats2
{   typedef ssc_map < uint64_t, unsigned > counter_t;
    typedef ::std::vector < unsigned > partial_t;
    counter_t count_;
    partial_t family_, member_;
    uint64_t index (const FAMILY f, const MEMBER m) const
    {   return (static_cast < uint64_t > (f) << 32) + static_cast < uint64_t > (m); }
public:
    stats2 ()
    {   family_.resize (static_cast <::std::size_t> (max_family + 1), 0);
        member_.resize (static_cast <::std::size_t> (max_member + 1), 0); }
    unsigned at (const FAMILY f, const MEMBER m) const
    {   counter_t::const_iterator i = count_.find (index (f, m));
        if (i == count_.cend ()) return 0;
        return i -> second; }
    unsigned family (const FAMILY e) const
    {   return family_.at (e); }
    unsigned member (const MEMBER m) const
    {   return member_.at (m); }
    void mark (const FAMILY f, const MEMBER m)
    {   assert (m <= max_member);
        ++(family_.at (f));
        ++(member_.at (m));
        uint64_t i = index (f, m);
        if (count_.find (i) != count_.cend ()) ++(count_.at (i));
        else count_.insert (counter_t :: value_type (i, 1)); } };
