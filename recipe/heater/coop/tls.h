/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

struct fred_tls  // thread local storage, not sorted ssl
{   const e_fred fred_;
    ::std::atomic_int lox_;
    ::std::atomic_bool empty_;
    ::std::atomic_bool flox_;
    ::std::atomic_bool dear_;
    fred_tls () : fred_ (fred_bloggs), lox_ (lox_none), empty_ (true), flox_ (false), dear_ (false) { }
    explicit fred_tls (const e_fred f) noexcept : fred_ (f), lox_ (lox_none), empty_ (true), flox_ (false), dear_ (false) { }
    fred_tls (const fred_tls& ) = delete;
    fred_tls (fred_tls&& ) = delete;
    ~fred_tls () = default;
    fred_tls& operator = (const fred_tls& ) = delete;
    fred_tls& operator = (fred_tls&& ) = delete; };

typedef ::std::shared_ptr < fred_tls > tls_ptr;
typedef ssc_map < ::std::thread::id, int > mid_t;
typedef ::std::vector < ::std::thread > vth_t;
typedef ::std::vector < tls_ptr > vtls_t;
