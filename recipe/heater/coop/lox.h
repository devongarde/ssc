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

// most locks are mutually exclusive; if one lock is applied, no others can be, except flox (outputting nits), dear (updating fileindices)
// and eleanor (initing enums) can be applied when another lock is applied

// no locks are recursive

#pragma once

#ifndef NO_FRED
#include "coop/fred.h"
#endif // NO_FRED

class lox
#ifndef NO_FRED
{   e_lox l_;
    ::std::atomic_bool un_;
#else // NO_FRED
{
#endif // NO_FRED
public:
    lox () = delete;
    NO_COPY_CONSTRUCTORS (lox);
#ifndef NO_FRED
    explicit lox (const e_lox l, const bool not_really = false);
#else // NO_FRED
    explicit lox (const e_lox ) { }
#endif // NO_FRED
    ~lox (); };

struct flox
{   flox () = delete;
    NO_COPY_CONSTRUCTORS (flox);
#ifndef NO_FRED
    explicit flox (const e_lox l);
#else // NO_FRED
    explicit flox (const e_lox ) { }
#endif // NO_FRED
    ~flox (); };

struct dear
{   dear () = delete;
    NO_COPY_CONSTRUCTORS (dear);
#ifndef NO_FRED
    explicit dear (const e_lox l);
#else // NO_FRED
    explicit dear (const e_lox ) { }
#endif // NO_FRED
    ~dear (); };

struct eleanor
{   eleanor () = delete;
    NO_COPY_CONSTRUCTORS (eleanor);
#ifndef NO_FRED
    explicit eleanor (const e_lox l);
#else // NO_FRED
    explicit eleanor (const e_lox ) { }
#endif // NO_FRED
    ~eleanor (); };
