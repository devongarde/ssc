/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "webpage/directory.h"

struct q_entry
{   nitpick* ticks_ = nullptr;
    dir_ptr dir_;
    ::std::string page_;
    e_stage stage_ = st_init;
    DEFAULT_CONSTRUCTORS_NO_EMPTY (q_entry);
    explicit q_entry (nitpick* ticks, dir_ptr dir, const e_stage s, const ::std::string& p = ::std::string ()) : ticks_ (ticks), dir_ (dir), page_ (p), stage_ (s) { }
    explicit q_entry (const e_stage s) : ticks_ (nullptr), dir_ (), stage_ (s) { }
    bool empty () const
    {   return (ticks_ == nullptr) || (dir_.get () == nullptr); }
    bool valid () const
    {   return ! empty (); }
    ::std::string rpt () const;
    void swap (q_entry& qe) noexcept; };

bool d_q (q_entry& qe);
#endif // NO_FRED
