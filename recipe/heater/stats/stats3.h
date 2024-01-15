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
#include "stats/stats1.h"

template < class VALUE, class ENUM, ENUM max_enum, ENUM undefined_enum > class stats3
{   friend class stats;
public:
#ifdef _MSC_VER
    typedef typename stats0 < VALUE > base_t;
#else  // _MSC_VER
    typedef stats0 < VALUE > base_t;
#endif // _MSC_VER
    typedef ::std::vector < base_t > counter_t;
private:
    counter_t count_;
public:
    typedef typename counter_t :: const_iterator cit;
    void swap (stats3& s3) noexcept
    {   count_.swap (s3.count_); }
    const base_t& at (const ENUM& e) const
    {   if (count_.size () == 0)
        {   static base_t b;
            return b; }
        return count_.at (e); }
    void mark (const ENUM& e, const VALUE& k, const unsigned u = 1)
    {   if (count_.size () == 0)
            count_.resize (static_cast <::std::size_t> (max_enum + 1), base_t ());
        if (e <= max_enum) count_.at (e).mark (k, u);
        else count_.at (undefined_enum).mark (k, u); }
    void accumulate (stats3 < VALUE, ENUM, max_enum, undefined_enum >& o) const
    {   if (o.count_.size () == 0) o.count_ = count_;
        else for (unsigned u = 0; u < count_.size (); ++u)
            count_.at (u).accumulate (o.count_.at (u)); } };

typedef stats3 < ::std::string, e_metaname, mn_illegal, mn_context > meta_value_stats;
