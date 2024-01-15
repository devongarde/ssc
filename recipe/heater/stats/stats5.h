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

class stats5
{   friend class stats;
    smsid_t count_;
public:
    stats5 () = default;
    void swap (stats5& s5) noexcept
    {   count_.swap (s5.count_); }
    ::std::size_t at (const ::std::string& s) const
    {   smsid_t::const_iterator i = count_.find (s);
        if (i == count_.cend ()) return 0;
        return i -> second; }
    smsid_t::const_iterator cbegin () const { return count_.cbegin (); }
    smsid_t::const_iterator cend () const { return count_.cend (); }
    void merge (const smsid_t& s) { merge_smsid (count_, s); }
    void mark (const ::std::string& s, const ::std::size_t u = 1)
    {   smsid_t::iterator i = count_.find (s);
        if (i == count_.end ()) count_.insert (smsid_t::value_type (s, u));
        else i -> second += u; }
    void accumulate (stats5& o) const
    {   if (o.count_.size () == 0) o.count_ = count_;
        else for (auto item : count_)
            o.mark (item.first, item.second); } };

typedef stats5 smsid_stats;
