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
#include "type/type.h"

template < class A, class B > struct connection : ::std::pair < A, B >
{   connection (const A& a, const B& b) noexcept : ::std::pair < A, B > (a, b) { } };

template < class A, class B > inline bool operator == (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   return  (lhs.first == rhs.first) &&
            (lhs.second == rhs.second); }

template < class A, class B > inline bool operator != (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   return ! (lhs == rhs); }

template < class A, class B > inline bool operator < (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   if (lhs.first < rhs.first) return true;
    if (lhs.first > rhs.first) return false;
    return lhs.second < rhs.second; }

template < class A, class B > inline bool operator <= (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   if (lhs < rhs) return true;
    return (lhs == rhs); }

template < class A, class B > inline bool operator > (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   return ! (lhs <= rhs); }

template < class A, class B > inline bool operator >= (const connection < A, B >& lhs, const connection < A, B >& rhs)
{   return ! (lhs < rhs); }

template < class A, class B > struct std::hash <connection < A, B > >
{   ::std::size_t operator() (const connection < A, B >& f) const
    {   ::std::size_t a = f.first;
        a <<= 16;
        a += static_cast <::std::size_t > (f.second);
        return ::std::hash <::std::size_t> () (a); } };

// expects ::std::pair
template < class PAIR > class connections
{   typedef typename PAIR :: first_type first_t;
    typedef typename PAIR :: second_type second_t;
    typedef ssc_set < PAIR > connection_set_t;
    typedef ssc_set < second_t > b_set_t;
    connection_set_t connexion_;
    b_set_t b_;
public:
    void init (nitpick& , const PAIR* standard_members, const ::std::size_t max)
    {   for (::std::size_t i = 0; i < max / sizeof (PAIR); ++i)
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif // _MSC_VER
        {   b_.insert (standard_members [i].second);
            connexion_.insert (standard_members [i]); } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
    bool is_plausible_connection (const PAIR& p) const
    {   return (connexion_.find (p) != connexion_.end ()); }
    bool is_plausible_connection (const first_t& a, const second_t& b) const
    {   return is_plausible_connection (PAIR (a, b)); }
    bool is_possible_member (const second_t& b) const
    {   return b_.find (b) != b_.end (); } };
