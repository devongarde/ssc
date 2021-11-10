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

// important: this template does not retain vector guarantees, such as data continuity

#pragma once

template < class MEMBER, size_t CHUNK > class big_vector
{   typedef ::std::vector < MEMBER > base_t;
    typedef ::std::shared_ptr < base_t > chunk_t;
    typedef ::std::vector < chunk_t > data_t;
    data_t data_;
    size_t size_ = 0;
    size_t chunk (const size_t index) const noexcept
    {   return index / CHUNK; }
    size_t offset (const size_t index) const noexcept
    {   return index % CHUNK; }
    void pre_push_back ()
    {   if ((size_ % CHUNK) == 0)
        {   const size_t c = chunk (size_);
            PRESUME (c <= data_.size (), __FILE__, __LINE__);
            if (c == data_.size ())
                data_.push_back (chunk_t (new base_t));
            PRESUME (data_.at (c) != nullptr, __FILE__, __LINE__);
            data_.at (c) -> reserve (CHUNK); } }
public:
	big_vector() = default;
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
    size_t size () const noexcept
    {   return size_; }
    MEMBER& at (const size_t index)
    {   PRESUME (index < size_, __FILE__, __LINE__);
        const size_t c = chunk (index);
        PRESUME (c < data_.size (), __FILE__, __LINE__);
        VERIFY_NOT_NULL (data_.at (c), __FILE__, __LINE__);
        const size_t o = offset (index);
        PRESUME (o < data_.at (c) -> size (), __FILE__, __LINE__);
        return data_.at (c) -> at (o); }
    const MEMBER& at (const size_t index) const
    {   PRESUME (index < size_, __FILE__, __LINE__);
        const size_t c = chunk (index);
        PRESUME (c < data_.size (), __FILE__, __LINE__);
        VERIFY_NOT_NULL (data_.at (c), __FILE__, __LINE__);
        const size_t o = offset (index);
        PRESUME (o < data_.at (c) -> size (), __FILE__, __LINE__);
        return data_.at (c) -> at (o); }
    void pop_back () { --size_; }
    void push_back (const MEMBER& m)
    {   pre_push_back ();
        chunk_t ptr = data_.at (chunk (size_));
        VERIFY_NOT_NULL (ptr, __FILE__, __LINE__);
        size_t off (offset (size_));
        PRESUME (off <= ptr -> size (), __FILE__, __LINE__);
        if (off == ptr -> size ())
        {   ptr -> push_back (m);
            ++size_; }
        else ptr -> at (off).reset (m); }
    void push_back (MEMBER&& m)
    {   pre_push_back ();
        chunk_t ptr = data_.at (chunk (size_));
        VERIFY_NOT_NULL (ptr, __FILE__, __LINE__);
        const size_t off (offset (size_));
        PRESUME (off <= ptr -> size (), __FILE__, __LINE__);
        if (off == ptr -> size ())
        {   ptr -> push_back (m);
            ++size_; }
        else ptr -> at (off).reset (m); }
    MEMBER& operator [] (const size_t index)
    {   return at (index); }
    const MEMBER& operator [] (const size_t index) const
    {   return at (index); }
    MEMBER& back ()
    {   return at (size_ - 1); }
    const MEMBER& back () const
    {   return at (size_ - 1); }
    bool empty () const { return size_ == 0; }
    void clear () noexcept
    {   size_ = 0;
        data_.clear (); } };
