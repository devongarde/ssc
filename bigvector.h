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

// important: this template does not retain vector guarantees, such as data continuity

#pragma once

template < class MEMBER, ::std::size_t CHUNK > class big_vector
{   typedef ::std::vector < MEMBER > base_t;
    typedef ::std::shared_ptr < base_t > chunk_t;
    typedef ::std::vector < chunk_t > data_t;
    data_t data_;
    uint64_t size_ = 0;
    uint64_t chunk (const uint64_t index) const
    {   return index / CHUNK; }
    uint64_t offset (const uint64_t index) const
    {   return index % CHUNK; }
    void pre_push_back ()
    {   if ((size_ % CHUNK) == 0)
        {   uint64_t c = chunk (size_);
            assert (c <= data_.size ());
            if (c == data_.size ())
                data_.push_back (chunk_t (new base_t));
            assert (data_.at (c) != nullptr);
            data_.at (c) -> reserve (CHUNK); } }
public:
    big_vector () = default;
    big_vector (const big_vector& bv) = default;
    big_vector (big_vector&& bv) = default;
    big_vector& operator = (const big_vector& bv) = default;
    big_vector& operator = (big_vector&& bv) = default;
    ~big_vector () = default;
    void swap (big_vector& bv) noexcept
    {   data_.swap (bv.data_);
        ::std::swap (size_, bv.size_); }
    void reset ()
    {   data_.clear (); }
    void reset (const big_vector& bv)
    {   data_ = bv.data_;
        size_ = bv.size_; }
    uint64_t size () const
    {   return size_; }
    MEMBER& at (const uint64_t index)
    {   assert (index < size_);
        uint64_t c = chunk (index);
        assert (c < data_.size ());
        assert (data_.at (c) != nullptr);
        uint64_t o = offset (index);
        assert (o < data_.at (c) -> size ());
        return data_.at (c) -> at (o); }
    const MEMBER& at (const uint64_t index) const
    {   assert (index < size_);
        uint64_t c = chunk (index);
        assert (c < data_.size ());
        assert (data_.at (c) != nullptr);
        uint64_t o = offset (index);
        assert (o < data_.at (c) -> size ());
        return data_.at (c) -> at (o); }
    void pop_back () { --size_; }
    void push_back (const MEMBER& m)
    {   pre_push_back ();
        chunk_t ptr = data_.at (chunk (size_));
        assert (ptr != nullptr);
        uint64_t off (offset (size_));
        assert (off <= ptr -> size ());
        if (off == ptr -> size ())
        {   ptr -> push_back (m);
            ++size_; }
        else ptr -> at (off).reset (m); }
    void push_back (MEMBER&& m)
    {   pre_push_back ();
        chunk_t ptr = data_.at (chunk (size_));
        assert (ptr != nullptr);
        uint64_t off (offset (size_));
        assert (off <= ptr -> size ());
        if (off == ptr -> size ())
        {   ptr -> push_back (m);
            ++size_; }
        else ptr -> at (off).reset (m); }
    MEMBER& operator [] (const uint64_t index)
    {   return at (index); }
    const MEMBER& operator [] (const uint64_t index) const
    {   return at (index); }
    MEMBER& back ()
    {   return at (size_ - 1); }
    const MEMBER& back () const
    {   return at (size_ - 1); }
    bool empty () const { return size_ == 0; }
    void clear ()
    {   size_ = 0;
        data_.clear (); } };
