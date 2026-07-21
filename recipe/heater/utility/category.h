/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

CONSTEXPR ::std::size_t oops_a_daisy = SIZE_MAX;

struct category
{   e_id_category cic_ = cic_none;
    ::std::string s_;
    ::std::size_t count_ = 0, id_ = 0;
    static ::std::size_t ids_;
    category () : cic_ (cic_none), count_ (0) { }
    category (const e_id_category cic, const ::std::string& s)
        : cic_ (cic), s_ (s), count_ (1) { }
    category (const e_id_category cic, const ::std::string& s, const ::std::size_t c)
        : cic_ (cic), s_ (s), count_ (c) { }
    ::std::string rpt () const
    {   return s_ + " ("+ ::boost::lexical_cast < ::std::string > (cic_) + ", " + ::boost::lexical_cast < ::std::string > (count_) + ", " + ::boost::lexical_cast < ::std::string > (id_) + ")"; } };

typedef ssc_map < ::std::size_t, category > mcic_t;
typedef ssc_mm < e_id_category, ::std::size_t > mmcid_t;

class categorical
{   mcic_t cics_;
    smsid_t rev_;
    mmcid_t cid_;
public:
    DEFAULT_CONSTRUCTORS (categorical);
    explicit categorical (const ::std::string& ) { }
    const category get (const ::std::size_t& n) const;
    const category get (const ::std::string& s) const;
    ::std::size_t inc (const ::std::size_t& n, const ::std::size_t c = 1);
    ::std::size_t dec (const ::std::size_t& n, const ::std::size_t c = 1);
    ::std::size_t find (const ::std::string& s) const;
    ::std::size_t insert (const category& cic, const ::std::size_t c);
    ::std::size_t insert (const category& cic);
    void erase (const ::std::size_t& n);
    void erase (const e_id_category cic, const ::std::string& s);
    void merge (const categorical& ee);
    void set (const categorical& ee);
    void clear ();
    bool exists (const ::std::string& s) const
    {   return find (s) != oops_a_daisy; }
     e_id_category id_category (const ::std::string& s) const
    {   const category& cic = get (s);
        return cic.cic_; }
    bool exists (const e_id_category cic, const ::std::string& s) const
    {   return (id_category (s) == cic); }
    ::std::size_t insert (const e_id_category cic, const ::std::string& s, const ::std::size_t c = 1)
    {   return insert (category (cic, s, c)); }
    mcic_t::const_iterator cbegin () const
    {   return cics_.cbegin (); }
    mcic_t::const_iterator cend () const
    {   return cics_.cend (); }
    smsid_t::const_iterator rbegin (const e_id_category cic) const;
    smsid_t::const_iterator rend (const e_id_category cic) const;
    void ritinc (smsid_t::const_iterator& ri, const e_id_category cic) const;
    mmcid_t::const_iterator cbegin (const e_id_category cic) const
    {   return cid_.find (cic); }
    mmcid_t::const_iterator cend (const e_id_category ) const
    {   return cid_.cend (); }
    bool another (const e_id_category cic, mmcid_t::const_iterator& i) const
    {   if ((++i) -> first != cic) return false;
        return i != cid_.cend (); }
    bool more (const mmcid_t::const_iterator& i)
    {   return i != cid_.cend (); }
    void accumulate (categorical& o) const;
    ::std::string rpt () const; };
