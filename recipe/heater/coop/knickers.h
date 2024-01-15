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

// knickers: - a gentle curse
//           - something essential
//           - can be rather smelly

class knickers
{   nitpick& nits_;
    nitpick* ticks_ = nullptr;
public:
    knickers () = delete;
    NO_COPY_CONSTRUCTORS (knickers);
    explicit knickers (nitpick& nits, nitpick* ticks)
            : nits_ (nits), ticks_ (ticks)
    {   VERIFY_NOT_NULL (ticks, __FILE__, __LINE__); }
    void accumulate_and_clear ();
    ~knickers (); };
