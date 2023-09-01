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

#pragma once

template < class FAMILY, class MEMBER, FAMILY max_family, MEMBER max_member > class stats2
{   typedef ssc_map < uint64_t, unsigned > counter_t;
    typedef ::std::vector < unsigned > partial_t;
    counter_t count_;
    partial_t family_, member_;
    uint64_t index (const FAMILY f, const MEMBER m) const noexcept
    {   return (static_cast < uint64_t > (f) << 32) + static_cast < uint64_t > (m); }
    void resize ()
    {   family_.resize (static_cast <::std::size_t> (max_family + 1), 0);
        member_.resize (static_cast <::std::size_t> (max_member + 1), 0); }
public:
    void swap (stats2& s2) noexcept
    {   count_.swap (s2.count_);
        family_.swap (s2.family_);
        member_.swap (s2.member_); }
    unsigned at (const FAMILY f, const MEMBER m) const
    {   if ((f >= family_.size ()) || (m >= member_.size ())) return 0;
        counter_t::const_iterator i = count_.find (index (f, m));
        if (i == count_.cend ()) return 0;
        return i -> second; }
    unsigned family (const FAMILY f) const
    {   if (f >= family_.size ()) return 0;
        return family_.at (f); }
    unsigned member (const MEMBER m) const
    {   if (m >= member_.size ()) return 0;
        return member_.at (m); }
    void mark (const FAMILY f, const MEMBER m, const unsigned u = 1)
    {   PRESUME (f <= max_family, __FILE__, __LINE__);
        PRESUME (m <= max_member, __FILE__, __LINE__);
        if (u == 0) return;
        if ((f >= family_.size ()) || (m >= member_.size ()))
            resize ();
        family_.at (f) += u;
        member_.at (m) += u;
        uint64_t i = index (f, m);
        if (count_.find (i) != count_.cend ()) count_.at (i) += u;
        else count_.insert (counter_t :: value_type (i, u)); }
    void accumulate (stats2 < FAMILY, MEMBER, max_family, max_member >& o) const
    {   if (o.family_.size () == 0)
        {   PRESUME (o.member_.size () == 0, __FILE__, __LINE__);
            o.resize (); }
        for (unsigned i = 0; i < family_.size (); ++i)
            o.family_.at (i) += family_.at (i);
        for (unsigned i = 0; i < member_.size (); ++i)
            o.member_.at (i) += member_.at (i);
        for (auto item : count_)
            if (item.second > 0)
                if (o.count_.find (item.first) != o.count_.cend ()) o.count_.at (item.first) += item.second;
                else o.count_.insert (counter_t :: value_type (item.first, item.second)); } };

typedef stats2 < e_element, e_attribute, last_element_tag, last_attribute > attribute_stats;
typedef stats2 < e_ontology_type, e_ontology_property, ont_illegal, op_illegal > ontology_property_stats;
