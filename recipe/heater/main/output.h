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
#include "utility/lexical.h"

class nitpick;

#ifdef WX
class wxLogWindow;
#endif // WX

class output_streams_t
{   ::std::unique_ptr < ::std::ofstream > fos_;
#ifdef WX
    bool wx_ = false;
#endif // WX
    ::std::string name_;
    ::std::string ensane (const ::std::string& s) const;
public:
    void init (nitpick& nits, const ::std::string& s);
    const ::std::string& name () const noexcept { return name_; }
#ifdef WX
    void enloggen (const bool b) noexcept { wx_ = b; }
#endif // WX
    void out (const ::std::string& s) const;
    void console (const ::std::string& s) const;
    void err (const ::std::string& s) const;
    bool invalid () const { return fos_.get () == nullptr; }
    template < typename... Ts > void out (const ::std::string& s, Ts... msg) const
    {   out (s + com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void console (const ::std::string& s, Ts... msg) const
    {   console (s + com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void err (const ::std::string& s, Ts... msg) const
    {   err (s + com < Ts... > :: bine (msg...)); } };

extern output_streams_t outstr;
