/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

#include "main/standard.h"
#include "main/enum.h"
#include "main/context.h"

#ifndef NO_FRED
#include "coop/lox.h"
#include "coop/knickers.h"
#endif // NO_FRED

knickers::~knickers ()
{   if (! nits_.empty ())
    try {
        lox l (lox_nits);
        ticks_ -> merge (nits_); }
    catch (...) { } }

void knickers::accumulate_and_clear ()
{   if (! nits_.empty ())
    try {
        lox l (lox_nits);
        nits_.accumulate (*ticks_);
        nits_.reset (); }
    catch (...) { } }
