/*
ssc (static site checker)
File Info
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

#pragma once

class stats6
{   friend class stats;
    sstr_t ss_;
public:
    stats6 () = default;
    void swap (stats6& s6) noexcept
    {   ss_.swap (s6.ss_); }
    sstr_t::const_iterator cbegin () const { return ss_.cbegin (); }
    sstr_t::const_iterator cend () const { return ss_.cend (); }
    sstr_t::const_iterator find (const ::std::string& s) const { return ss_.find (s); }
    bool empty () const { return ss_.empty (); }
    ::std::size_t size () const { return ss_.size (); }
    void merge (const sstr_t& s)
    {   for (auto item : s)
            ss_.insert (item); }
    void mark (const ::std::string& s)
    {   ss_.insert (s); }
    void accumulate (stats6& o) const
    {   for (auto item : ss_)
            o.mark (item); } };

typedef ::std::vector < stats6 > vs6_stats;
