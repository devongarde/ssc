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
#include "utility/common.h"
#include "utility/category.h"

struct arguments;
class css;
typedef ::std::shared_ptr < css > css_ptr;

class distilled
{   friend class css_global;
    vsstr_t str_ = vsstr_t (gst_max);
    categorical dcl_, use_;
    ustr_t custom_media_;
    css_ptr cp_;
    v_np ticks_;
    bool in_progress_ = false, file_ = false, borked_ = false;
public:
    DEFAULT_CONSTRUCTORS_NO_EMPTY (distilled);
    explicit distilled (bool b) : in_progress_ (b) { }
    explicit distilled (const categorical& dcl, const categorical& use) : dcl_ (dcl), use_ (use)
    { }
    bool wait () const noexcept { return in_progress_; }
    bool sort_it_out () const noexcept { return in_progress_; }
    bool borked () const noexcept { return borked_; }
    void borked (const bool b) { borked_ = b; }
    css_ptr css () const { return cp_; }
    void css (const css_ptr cp) { cp_ = cp; }
    void reset ();
    css_ptr expel () { css_ptr res (cp_); cp_.reset (); return res; }
    vsstr_t& ss () { return str_; }

    bool has (const e_id_category cic, const ::std::string& s) const
    {   return dcl_.exists (cic, s); }
    void use (const e_id_category cic, const ::std::string& s, const ::std::size_t n = 1)
    {   use_.insert (cic, s, n); }
    void dcl (const e_id_category cic, const ::std::string& s, const ::std::size_t n = 1)
    {   dcl_.insert (cic, s, n); }
    void erase (const e_id_category cat, const ::std::string& s)
    {   dcl_.erase (cat, s); use_.erase (cat, s); }

    void accumulate (stats_t* s) const;
    const categorical& dcl () const { return dcl_; }
    const categorical& use () const { return use_; }
    bool has_custom_media (const ::std::string& name) const
    {   return custom_media_.find (name) != custom_media_.cend (); }
    bool note_custom_media (const ::std::string& name, const ::std::string& def)
    {   if (has_custom_media (name)) return false;
        auto i = custom_media_.insert (::std::pair (name, def));
        return i.second; } 
    bool note_str (const e_gsstr g, const ::std::string& s)
    {   auto i = str_.at (g).insert (s);
        return i.second; }
    bool has_str (const e_gsstr g, const ::std::string& s) const
    {   return (str_.at (g).find (s) != str_.at (g).cend ()); }
    const sstr_t& get_str (const e_gsstr g) const
    {   return str_.at (g); }
    sstr_t& get_str (const e_gsstr g)
    {   return str_.at (g); }
    void merge (const nitpick& ticks)
    {   ticks_.push_back (ticks); }
    ::std::string report () const;
    ::std::string review (const mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false); };

typedef ::std::shared_ptr < distilled > dst_ptr;
typedef ssc_map < ::std::string, dst_ptr > mdst_t;
