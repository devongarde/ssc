/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

template < class T > struct ab
{   T a_, b_;
    ab (const T& a, const T& b) : a_ (a), b_ (b) { } };

template < class T> inline bool operator == (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ == rhs.a_) && (lhs.b_ == rhs.b_); };
template < class T> inline bool operator != (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ != rhs.a_) || (lhs.b_ != rhs.b_); };
template < class T> inline bool operator < (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ < rhs.a_) || ((lhs.a_ == rhs.a_) && (lhs.b_ < rhs.b_)); };
template < class T> inline bool operator > (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ > rhs.a_) || ((lhs.a_ == rhs.a_) && (lhs.b_ > rhs.b_)); };
template < class T> inline bool operator <= (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ < rhs.a_) || ((lhs.a_ == rhs.a_) && (lhs.b_ <= rhs.b_)); };
template < class T> inline bool operator >= (const ab <T> & lhs, const ab <T> & rhs)
{   return (lhs.a_ > rhs.a_) || ((lhs.a_ == rhs.a_) && (lhs.b_ >= rhs.b_)); };

template < class T > class stats4
{   friend class stats;
    typedef ab < T > ab_t;
    typedef ::std::map < ab_t, unsigned > counter_t;
    counter_t count_;
public:
    typedef typename counter_t :: const_iterator cit;
    stats4 () = default;
    unsigned at (const T& a, const T& b) const
    {   const ab_t e (a, b);
        typename counter_t::const_iterator i = count_.find (e);
        if (i == count_.cend ()) return 0;
        return i -> second; }
    cit cbegin () const { return count_.cbegin (); }
    cit cend () const { return count_.cend (); }
    void mark (const T& a, const T& b)
    {   const ab_t e (a, b);
        typename counter_t::iterator i = count_.find (e);
        if (i == count_.end ()) count_.insert (typename counter_t::value_type (e, 1));
        else i -> second += 1; } };
