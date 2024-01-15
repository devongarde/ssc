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
#ifndef NO_FRED

#include "coop/lox.h"
#include "coop/fred.h"

class kew
{   typedef ::std::deque < q_entry > d_kew;
    d_kew kew_;
    ::std::atomic_bool empty_;
public:
    kew () : empty_ (true) { }
    NO_COPY_CONSTRUCTORS (kew);
    ~kew () = default;
    void push (const q_entry& t)
    {   lox l (lox_q);
        empty_ = false;
        kew_.push_back (t); }
    void push (q_entry&& t)
    {   lox l (lox_q);
        empty_ = false;
        kew_.emplace_back (t); }
    void rude (const q_entry& t)
    {   lox l (lox_q);
        empty_ = false;
        kew_.push_front (t); }
    void rude (q_entry&& t)
    {   lox l (lox_q);
        empty_ = false;
        kew_.emplace_front (t); }
    bool empty () const
    {   return empty_; }
    bool activity () const
    {   return (! empty_) || fred.activity (); }
    bool pop (q_entry& t); };

extern kew q;
#endif // NO_FRED
