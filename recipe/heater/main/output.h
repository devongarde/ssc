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
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "feedback/nitout.h"

class output_streams_t
{   ::std::unique_ptr < ::std::ofstream > fos_;
    ::std::string name_;
    unsigned dot_ = 0;
    ::std::string ensane (const ::std::string& s) const;
public:
    void init (nitpick& nits, const ::std::string& s);
    void out (const ::std::string& s) const { out () << s; }
    void err (const ::std::string& s) const { err () << ensane (s); }
    ::std::ostream& out () const noexcept { if (fos_) return *fos_; return ::std::cout; }
    ::std::ostream& err () const noexcept { if (fos_) return *fos_; return ::std::cerr; }
    void dot ();
    void dedot (unsigned n = 0) noexcept { dot_ = n; } };

extern output_streams_t outstr;
