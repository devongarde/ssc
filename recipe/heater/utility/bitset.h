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
#include "main/enum.h"
#include "utility/common.h"

void state_init ();

// I got fed up working around borked bitset implementations. This is extremely
// inefficient compared to a decent working implementation, but at least it
// pretends to work. :-(

template < typename T, T SIZE > class ssc_bitset
{   typedef faux_vb_t base_t;
    base_t bs_;
    explicit ssc_bitset (const base_t& b) : bs_ (b)
    { PRESUME (bs_.size () == SIZE, __FILE__, __LINE__); }
    explicit ssc_bitset (base_t&& b) : bs_ (b)
    { PRESUME (bs_.size () == SIZE, __FILE__, __LINE__); }
public:
    ssc_bitset () : bs_ (SIZE, false) { }
    ssc_bitset (const ssc_bitset& bs) : bs_ (bs.bs_) { }
    ssc_bitset (ssc_bitset&& bs) : bs_ (bs.bs_) { }
    explicit ssc_bitset (const T t) : bs_ (SIZE, false) { set (t); }
    ~ssc_bitset () { }
    ssc_bitset& operator = (const ssc_bitset& bs) { bs_ = bs.bs_; return *this; }
    ssc_bitset& operator = (ssc_bitset&& bs) { bs_ = bs.bs_; return *this; }
    friend bool operator == (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   return lhs.bs_ == rhs.bs_; }
    friend bool operator != (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   return lhs.bs_ != rhs.bs_; }
    void swap (ssc_bitset& bs) noexcept
    {   bs_.swap (bs.bs_); }
    void reset ()
    {   ssc_bitset t;
        swap (t); }
    void reset (ssc_bitset& bs)
    {   swap (bs); }
    bool operator [] (const ::std::size_t x) const
    {   PRESUME (x < SIZE, __FILE__, __LINE__);
        return bs_.at (x); }
    bool test (const ::std::size_t x) const
    {   PRESUME (x < SIZE, __FILE__, __LINE__);
        return bs_.at (x); }
    void set (const ::std::size_t x, const bool b = true)
    {   PRESUME (x < SIZE, __FILE__, __LINE__);
        bs_.at (x) = b; }
    void reset (const ::std::size_t x)
    {   PRESUME (x < SIZE, __FILE__, __LINE__);
        bs_.at (x) = false; }
    void flip (const ::std::size_t x)
    {   PRESUME (x < SIZE, __FILE__, __LINE__);
        bs_.at (x) = ! bs_.at (x); }
    void flip ()
    {   PRESUME (bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t x = 0; x < SIZE; ++x)
            bs_.at (x) = ! bs_.at (x); }
    static bool any (const ssc_bitset& lhs, const ssc_bitset& rhs) noexcept
    {   for (::std::size_t n = 0; n < SIZE; ++n)
            if (lhs.test (n) && rhs.test (n)) return true;
        return false; }
    static bool all (const ssc_bitset& lhs, const ssc_bitset& rhs) noexcept
    {   for (::std::size_t n = 0; n < SIZE; ++n)
            if (rhs.test (n))
                if (! lhs.test (n)) return false;
        return true; }
    bool any (const ssc_bitset& rhs) noexcept
    {   return any (*this, rhs); }
    bool all (const ssc_bitset& rhs) noexcept
    {   return all (*this, rhs); }
    bool any () const
    {   PRESUME (bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            if (test (n)) return true;
        return false; }
    bool all () const
    {   PRESUME (bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            if (! test (n)) return false;
        return true; }
    ::std::size_t count () const
    {   PRESUME (bs_.size () == SIZE, __FILE__, __LINE__);
        ::std::size_t n = 0;
        for (::std::size_t x = 0; x < SIZE; ++x)
            if (bs_.at (x)) ++n;
        return n; }
    bool none () const
    {   return ! any (); }
    bool empty () const
    {   return none (); }
    constexpr ::std::size_t size () const noexcept
    {   return SIZE; }
    friend ssc_bitset AND (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   ssc_bitset res;
        PRESUME (res.bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            if (lhs.test (n) && rhs.test (n))
                res.set (n);
        return res; }
    friend ssc_bitset OR (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   ssc_bitset res;
        PRESUME (res.bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            if (lhs.test (n) || rhs.test (n))
                res.set (n);
        return res; }
    friend ssc_bitset XOR (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   ssc_bitset res;
        PRESUME (res.bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            if (lhs.test (n) ^ rhs.test (n))
                res.set (n);;
        return res; }
    friend ssc_bitset AND (const ssc_bitset& lhs, const T rhs)
    {   return AND (lhs, ssc_bitset (rhs)); }
    friend ssc_bitset OR (const ssc_bitset& lhs, const T rhs)
    {   return OR (lhs, ssc_bitset (rhs)); }
    friend ssc_bitset XOR (const ssc_bitset& lhs, const T rhs)
    {   return XOR (lhs, ssc_bitset (rhs)); }
    friend ssc_bitset operator & (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   return AND (lhs, rhs); }
    friend ssc_bitset operator | (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   return OR (lhs, rhs); }
    friend ssc_bitset operator ^ (const ssc_bitset& lhs, const ssc_bitset& rhs)
    {   return XOR (lhs, rhs); }
    friend ssc_bitset operator & (const ssc_bitset& lhs, const T rhs)
    {   return AND (lhs, rhs); }
    friend ssc_bitset operator | (const ssc_bitset& lhs, const T rhs)
    {   return OR (lhs, rhs); }
    friend ssc_bitset operator ^ (const ssc_bitset& lhs, const T rhs)
    {   return XOR (lhs, rhs); }
    ssc_bitset operator ~ () const
    {   PRESUME (bs_.size () == SIZE, __FILE__, __LINE__);
        ssc_bitset res;
        PRESUME (res.bs_.size () == SIZE, __FILE__, __LINE__);
        for (::std::size_t n = 0; n < SIZE; ++n)
            res.bs_.at (n) = ! bs_.at (n);
        return res; }
    ssc_bitset& operator |= (const T e)
    {   *this = OR (*this, e);
        return *this; }
    ssc_bitset& operator &= (const T e)
    {   *this = AND (*this, e);
        return *this; }
    ssc_bitset& operator ^= (const T e)
    {   *this = XOR (*this, e);
        return *this; }
    ssc_bitset operator |= (const ssc_bitset& rhs)
    {   *this = OR (*this, rhs);
        return *this; }
    ssc_bitset operator &= (const ssc_bitset& rhs)
    {   *this = AND (*this, rhs);
        return *this; }
    ssc_bitset operator ^= (const ssc_bitset& rhs)
    {   *this = XOR (*this, rhs);
        return *this; } };
