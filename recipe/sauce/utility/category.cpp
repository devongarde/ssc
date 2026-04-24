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

#include "main/standard.h"
#include "utility/common.h"
#include "utility/category.h"

::std::size_t category::ids_ = 0;

::std::size_t categorical::find (const ::std::string& s) const
{   smsid_t::const_iterator ri = rev_.find (s);
    if (ri == rev_.cend ()) return oops_a_daisy;
    return ri -> second; }

const category categorical::get (const ::std::size_t& n) const
{   const mcic_t::const_iterator ci = cics_.find (n);
    if (ci == cics_.cend ()) return category ();
    return ci -> second; }

const category categorical::get (const ::std::string& s) const
{   const ::std::size_t n = find (s);
    if (n == oops_a_daisy) return category ();
    return get (n); }

::std::size_t categorical::inc (const ::std::size_t& n, const ::std::size_t c)
{   const mcic_t::iterator ci = cics_.find (n);
    if (ci == cics_.end ()) return oops_a_daisy;
    ci -> second.count_ += c;
    return ci -> second.count_; }

::std::size_t categorical::dec (const ::std::size_t& n, const ::std::size_t c)
{   const mcic_t::iterator ci = cics_.find (n);
    if (ci == cics_.end ()) return oops_a_daisy;
    if (c < ci -> second.count_) ci -> second.count_ -= c;
    else ci -> second.count_ = 0;
    return ci -> second.count_; }

::std::size_t categorical::insert (const category& cic)
{   smsid_t::const_iterator ri = rev_.find (cic.s_);
    if (ri != rev_.cend ())
    {   if (ri -> second == oops_a_daisy)
            return oops_a_daisy;
        if (cic.count_ > 0)
        {   mcic_t::iterator i = cics_.find (ri -> second);
            PRESUME (i != cics_.end (), __FILE__, __LINE__);
            i -> second.count_ += cic.count_; }
        return ri -> second; }
    ::std::size_t id = ++(cic.ids_);
    cics_.insert (mcic_t::value_type (id, cic));
    rev_.insert (smsid_t::value_type (cic.s_, id));
    cid_.insert (mmcid_t::value_type (cic.cic_, id));
    return id; }

::std::size_t categorical::insert (const category& cic, const ::std::size_t c)
{   smsid_t::const_iterator ri = rev_.find (cic.s_);
    if (ri != rev_.cend ())
    {   if (ri -> second == oops_a_daisy)
            return oops_a_daisy;
        if (c > 0)
        {   mcic_t::iterator i = cics_.find (ri -> second);
            PRESUME (i != cics_.end (), __FILE__, __LINE__);
            i -> second.count_ += c; }
        return ri -> second; }
    ::std::size_t id = ++(cic.ids_);
    cics_.insert (mcic_t::value_type (id, cic));
    rev_.insert (smsid_t::value_type (cic.s_, id));
    cid_.insert (mmcid_t::value_type (cic.cic_, id));
    return id; }

void categorical::erase (const ::std::size_t& n)
{   mcic_t::iterator i = cics_.find (n);
    if (i != cics_.end ())
    {   for (mmcid_t::iterator m = cid_.find (i -> second.cic_); (m != cid_.end ()) && (m -> first == i -> second.cic_); ++m)
            if (m -> second == i -> second.id_)
            {   cid_.erase (m); break; }
        smsid_t::iterator r = rev_.find (i -> second.s_);
        if (r != rev_.end ()) rev_.erase (r);
        cics_.erase (i); } }

void categorical::erase (const e_id_category cic, const ::std::string& s)
{   const ::std::size_t n = find (s);
    if (n != oops_a_daisy)
    {   category got = get (n);
        if (got.cic_ == cic) erase (n); } }

void categorical::merge (const categorical& ee)
{   for (auto cic : ee.cics_)
        insert (cic.second); }

void categorical::set (const categorical& ee)
{   clear ();
    merge (ee); }

void categorical::clear ()
{   cics_.clear ();
    rev_.clear ();
    cid_.clear (); }

smsid_t::const_iterator categorical::rbegin (const e_id_category cic) const
{   for (smsid_t::const_iterator i = rev_.cbegin (); i != rev_.cend (); ++i)
        if (get (i -> second).cic_ == cic)
            return i;
    return rev_.cend (); }

smsid_t::const_iterator categorical::rend (const e_id_category ) const
{   return rev_.cend (); }

void categorical::ritinc (smsid_t::const_iterator& ri, const e_id_category cic) const
{   for (++ri; ri != rev_.cend (); ++ri)
        if (get (ri -> second).cic_ == cic)
            return;
    ri = rev_.cend (); }

void categorical::accumulate (categorical& o) const
{   for (mcic_t::const_iterator i = cics_.cbegin (); i != cics_.cend (); ++i)
        o.insert (i -> second.cic_, i -> second.s_, i -> second.count_); }   

::std::string categorical::rpt () const
{   ::std::string res;
    for (auto c : cics_)
        res += ::boost::lexical_cast < ::std::string > (c.first) + ": " + c.second.rpt () + "\n";
    return res; }
