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

// most locks are mutually exclusive; if one lock is applied, no others can be, except flox (outputting nits) and dear (updating fileindices) can be applied when another lock is applied

// no locks are recursive

#pragma once
#include "coop/fred.h"

class lox
{   e_lox l_ = lox_none;    // this must be thread static
    ::std::atomic_bool un_ = false;
public:
    lox () = delete;
    lox (const lox& ) = delete;
    lox (lox&& ) = delete;
    explicit lox (const e_lox l);
    lox& operator = (const lox& ) = delete;
    lox& operator = (lox&& ) = delete;
    ~lox ();
    static ::std::mutex& mx (const e_lox l); };

struct flox
{   flox () = delete;
    flox (const flox& ) = delete;
    flox (lox&& ) = delete;
    explicit flox (const e_lox l);
    flox& operator = (const flox& ) = delete;
    flox& operator = (flox&& ) = delete;
    ~flox ();
    static ::std::mutex& mx (); };

struct dear
{   dear () = delete;
    dear (const dear& ) = delete;
    dear (lox&& ) = delete;
    explicit dear (const e_lox l);
    dear& operator = (const dear& ) = delete;
    dear& operator = (dear&& ) = delete;
    ~dear ();
    static ::std::mutex& mx (); };
