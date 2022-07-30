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

// I have to decide whether I use completely independent locks, which requires that it is never true that more than one lock is taken at any one time,
// or a cascade of locks, which is more complex but permits multiple locked objects at any one time without risk of deadlock
// or simply one common lock, which reduces performance gains significantly but is far simpler and also never deadlocks

// I am minded towards the one lock at a time approach, but that depends on analysis of the crosslink / id / file index checking code

// shared, & so lockable components, are:
// - directory scan queue (init phase, directory phase)
// - extending the file index (directory phase)
// - writing the corpus (scan phase) ... the shared part is writing text so this can be controlled by assembling the text into a string, then doing one write of 
//    that string, so making writing 'atomic' from the I/O perspective, thus no locking required       DONE
// - crosslinks (scan phase, post phase)
// - id analysis (scan phase, post phase)
// - stats (scan phase, final phase) ... when gathering, if it's just a matter of incrementing a stats, that could be atomic if atomic unsigneds could be chucked in a collection. They can't.
//     Anyway, if it's a matter of defining a new category, then a collection insertion occurs, so locking will be required. Stats1 is fixed sized.
//     since the only stats that will require locking will be the grand stats, then that can be moved from incrementing with any mark to updating when stats are reported, thus reducing the
//     need for locking   DONE
// - feedback (scan phase, post phase)
// - nits currently kick up to root for directory reporting; this needs separating out for threading 

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
