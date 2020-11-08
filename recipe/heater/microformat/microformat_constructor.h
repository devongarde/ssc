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
#include "microformat/microformat_classes.h"

class microformat_pv
{   bool holds_alternative (const ::std::size_t v) const { return (v == index_) && ! is_empty (); }
public:
    ::std::size_t           index_ = 0;
    microformat_base_ptr    microformat_ = nullptr;
    microformat_pv () NOEXCEPT
        :   index_ (c_error)
    { }
    explicit microformat_pv (const ::std::size_t v) NOEXCEPT
        :   index_ (v)
    { }
    explicit microformat_pv (const e_class v) NOEXCEPT
        :   index_ (index (v))
    { }
    explicit microformat_pv (const e_rel v) NOEXCEPT
        :   index_ (index (v))
    { }

    microformat_pv (const microformat_pv& mf) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    microformat_pv (microformat_pv&& mf) = default;
#endif
    microformat_pv& operator = (const microformat_pv& mf) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    microformat_pv& operator = (microformat_pv&& mf) = default;
#endif
    ~microformat_pv () = default;

    static const ::std::size_t first_rel_ = static_cast < ::std::size_t > (r_entry_category);
    static ::std::size_t index (const e_class v) { return static_cast < ::std::size_t > (v); }
    static ::std::size_t index (const e_rel r) { return static_cast < ::std::size_t > (r) /* + first_rel_ */ ; }

    static microformat_pv alloc_microformat_pv (const ::std::size_t v);
    static microformat_pv alloc_microformat_pv (const e_class v) { return alloc_microformat_pv (index (v)); }
    static microformat_pv alloc_microformat_pv (const e_rel v) { return alloc_microformat_pv (index (v)); }

    void reset () { if (is_allocated ()) microformat_ -> reset (); }
    void swap (microformat_pv& m) NOEXCEPT
    {   ::std::swap (index_, m.index_);
        microformat_.swap (m.microformat_); }

    template < class MICROFORMAT > const MICROFORMAT* get () const
    {   assert (MICROFORMAT::whoami () == index_);
        return reinterpret_cast <const MICROFORMAT*> (microformat_.get ()); }
    template < class MICROFORMAT > MICROFORMAT* get ()
    {   assert (MICROFORMAT::whoami () == index_);
        return reinterpret_cast <MICROFORMAT*> (microformat_.get ()); }
    const microformat_base* get () const
    {   return microformat_.get (); }
    microformat_base* get ()
    {   return microformat_.get (); }

    bool is_vocabulary () const { return index_ < first_rel_; }
    bool is_rel () const { return index_ >= first_rel_; }
    e_class which_vocabulary () const { assert (is_vocabulary ()); return static_cast < e_class > (index_); }
    e_rel which_rel () const { assert (is_rel ()); return static_cast < e_rel > (index_ /* - first_rel_ */ ); }
    bool operator ! () const { return is_empty (); }
    bool is_empty () const { return ! microformat_; }
    bool is_valid () const { return (index_ != c_error) && (index_ != r_illegal); }
    bool is_allocated () const { return is_valid () && ! is_empty (); }
    bool holds_alternative (const e_class v) const { return (is_vocabulary () && holds_alternative (index (v))); }
    bool holds_alternative (const e_rel v) const { return (is_rel () && holds_alternative (index (v))); }
    bool has_prop (const e_property p) const { return is_allocated () && microformat_ -> has_prop (p); }
    bool is_relational () const { return is_allocated () && microformat_ -> is_relational (); }
    void validate (nitpick& nits, const html_version& v, const elem& e) const { if (is_allocated ()) microformat_ -> validate (nits, v, e); }
    bool declared () const { return is_allocated () && microformat_ -> declared (); }
    void set_mf_value (nitpick& nits, const html_version& v, const e_property pp, element& e) { if (is_allocated ()) microformat_ -> set_mf_value (nits, v, pp, e); }
    ::std::string get_string (const e_property pp) { if (! is_allocated ()) return ::std::string (); return microformat_ -> get_string (pp); }
    ::std::string report () const { if (! is_allocated ()) return ::std::string (); return microformat_ -> report (); } };
