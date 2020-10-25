/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "microformat_constructor.h"

typedef ::std::vector < microformat_pv > microformat_vpv; // indexed by VOCAB
typedef microformat_vpv::const_iterator microformat_vpv_ci;
typedef microformat_vpv::iterator microformat_vpv_i;

class element;

class microformats
{   microformat_vpv mf_;
    static ::std::size_t index (const e_class v) { return microformat_pv::index (v); }
    static ::std::size_t index (const e_rel r) { return microformat_pv::index (r); }
    bool allocated (const ::std::size_t ndx) const;
    void alloc (const ::std::size_t ndx);
    bool has (const ::std::size_t ndx, const e_property p) const;
    bool has (const ::std::size_t ndx) const;
    void declare (const ::std::size_t v);
    bool has_property (const ::std::size_t ndx, const e_property p) const;
    bool is_declared (const ::std::size_t ndx) const;
    void set_mf_value (nitpick& nits, const html_version& v, const ::std::size_t ndx, const e_property pp, element& e);
    ::std::string get_string (const ::std::size_t ndx, const e_property pp);
    bool empty (const ::std::size_t ndx) const;
public:
    microformats () { mf_.resize (vocab_size + rel_size); } // needs fixing for valid microformat rels
    void swap (microformats& m) noexcept
    {   mf_.swap (m.mf_); }
    bool allocated (const e_class v) const { return allocated (index (v)); }
    bool allocated (const e_rel v) const { return allocated (index (v)); }
    void alloc (const e_class v) { alloc (index (v)); }
    void alloc (const e_rel v) { alloc (index (v)); }
    template < class VOCAB > VOCAB& get ();
    template < class VOCAB > const VOCAB& get () const;
    template < class VOCAB > bool has () const;
    void verify (nitpick& nits, const html_version& v);
    bool has (const e_class v, const e_property p) const { return has (index (v), p); }
    bool has (const e_rel v, const e_property p) const { return has (index (v), p); }
    bool has (const e_class v) const { return has (index (v)); }
    bool has (const e_rel v) const { return has (index (v)); }
    void reset ();
    void declare (const e_class v) { declare (index (v)); }
    void declare (const e_rel v) { declare (index (v)); }
    bool has_property (const e_class v, const e_property p) const { return has_property (index (v), p); }
    bool has_property (const e_rel v, const e_property p) const { return has_property (index (v), p); }
    e_class plausible_vocabulary (const e_property p) const;
    bool is_relational () const;
    void validate (nitpick& nits, const html_version& v, const elem& e);
    bool is_declared (const e_class v) const { return is_declared (index (v)); }
    bool is_declared (const e_rel v) const { return is_declared (index (v)); }
    void set_mf_value (nitpick& nits, const html_version& ver, const e_class v, const e_property pp, element& e) { set_mf_value (nits, ver, index (v), pp, e); }
    void set_mf_value (nitpick& nits, const html_version& ver, const e_rel v, const e_property pp, element& e) { set_mf_value (nits, ver, index (v), pp, e); }
    ::std::string get_string (const e_class v, const e_property pp) { return get_string (index (v), pp); }
    ::std::string get_string (const e_rel v, const e_property pp) { return get_string (index (v), pp); }
    void text (const ::std::string& s);
    bool empty () const;
    bool empty (const e_class v) const { return empty (index (v)); }
    bool empty (const e_rel v) const { return empty (index (v)); }
    ::std::string report () const; };

template < class VOCAB > VOCAB& microformats::get ()
{   assert (allocated (VOCAB::whoami ()));
    return * (reinterpret_cast < VOCAB* > (mf_ [VOCAB::whoami ()].get ())); }

template < class VOCAB > const VOCAB& microformats::get () const
{   assert (allocated (VOCAB::whoami ()));
    return * (reinterpret_cast < const VOCAB* > (mf_ [VOCAB::whoami ()].get ())); }

template < class VOCAB > bool microformats::has () const
{   if (! allocated (VOCAB::whoami ())) return true;
    return has (VOCAB::whoami ()); }
