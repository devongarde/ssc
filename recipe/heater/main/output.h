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
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "feedback/nitout.h"
#include "coop/lox.h"

class output_streams_t
{   ::std::unique_ptr < ::std::ofstream > fos_;
    ::std::string name_;
    ::std::string ensane (const ::std::string& s) const;
    ::std::ostream& out () const noexcept { if (fos_) return *fos_; return ::std::cout; }
    ::std::ostream& err () const noexcept { if (fos_) return *fos_; return ::std::cerr; }
public:
    void init (nitpick& nits, const ::std::string& s);
    const ::std::string& name () const noexcept { return name_; }
    void out (const ::std::string& s) const
    {   lox l (lox_out);
        out () << s; }
    void out (const ::std::string& s1, const ::std::string& s2) const
    {   lox l (lox_out);
        out () << s1 << s2; }
    void out (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3)
    {   lox l (lox_out);
        out () << s1 << s2 << s3; }
    void out (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3, const ::std::string& s4)
    {   lox l (lox_out);
        out () << s1 << s2 << s3 << s4; }
    void out (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3, const ::std::string& s4, const ::std::string& s5)
    {   lox l (lox_out);
        out () << s1 << s2 << s3 << s4 << s5; }
    void err (const ::std::string& s) const
    {   lox l (lox_out);
        err () << ensane (s); }
    void err (const ::std::string& s1, const ::std::string& s2) const
    {   lox l (lox_out);
        err () << ensane (s1) << ensane (s2); }
    void err (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3) const
    {   lox l (lox_out);
        err () << ensane (s1) << ensane (s2) << ensane (s3); }
    void err (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3, const ::std::string& s4, const ::std::string& s5) const
    {   lox l (lox_out);
        err () << ensane (s1) << ensane (s2) << ensane (s3) << ensane (s4) << ensane (s5); } };

extern output_streams_t outstr;
