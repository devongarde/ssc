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
#include "microformat/microformat_classes.h"

class microformat_pv
{   bool holds_alternative (const ::std::size_t v) const noexcept
    {   return (v == index_) && ! is_empty (); }
public:
    ::std::size_t           index_ = 0;
    microformat_base_ptr    microformat_ = nullptr;
    microformat_pv () noexcept : index_ (c_error) { }
    explicit microformat_pv (const ::std::size_t v) noexcept : index_ (v) { }
    explicit microformat_pv (const e_class v) noexcept : index_ (index (v)) { }
    explicit microformat_pv (const e_rel v) noexcept : index_ (index (v)) { }
    DEFAULT_COPY_CONSTRUCTORS (microformat_pv);
    ~microformat_pv () = default;

    static const ::std::size_t first_rel_ = static_cast < ::std::size_t > (r_entry_category);
    CONSTEXPR static ::std::size_t index (const e_class v) noexcept
    {   return static_cast < ::std::size_t > (v); }
    CONSTEXPR static ::std::size_t index (const e_rel r) noexcept
    {    return static_cast < ::std::size_t > (r) /* + first_rel_ */ ; }

    static microformat_pv alloc_microformat_pv (const ::std::size_t v);
    static microformat_pv alloc_microformat_pv (const e_class v)
    {   return alloc_microformat_pv (index (v)); }
    static microformat_pv alloc_microformat_pv (const e_rel v)
    {   return alloc_microformat_pv (index (v)); }

    void reset ()
    {   if (is_allocated ()) microformat_ -> reset (); }
    void swap (microformat_pv& m) noexcept
    {   ::std::swap (index_, m.index_);
        microformat_.swap (m.microformat_); }

    template < class MICROFORMAT > const MICROFORMAT* get () const
    {   PRESUME (MICROFORMAT::whoami () == index_, __FILE__, __LINE__);
        return reinterpret_cast <const MICROFORMAT*> (microformat_.get ()); }
    template < class MICROFORMAT > MICROFORMAT* get ()
    {   PRESUME (MICROFORMAT::whoami () == index_, __FILE__, __LINE__);
        return reinterpret_cast <MICROFORMAT*> (microformat_.get ()); }
    const microformat_base* get () const noexcept
    {   return microformat_.get (); }
    microformat_base* get () noexcept
    {   return microformat_.get (); }

    bool is_vocabulary () const noexcept
    {   return index_ < first_rel_; }
    bool is_rel () const noexcept
    {   return index_ >= first_rel_; }
    e_class which_vocabulary () const
    {   PRESUME (is_vocabulary (), __FILE__, __LINE__); return static_cast < e_class > (index_); }
    e_rel which_rel () const
    {   PRESUME (is_rel (), __FILE__, __LINE__); return static_cast < e_rel > (index_ /* - first_rel_ */ ); }
    bool operator ! () const  noexcept
    {   return is_empty (); }
    bool is_empty () const noexcept
    {   return ! microformat_; }
    bool is_valid () const noexcept
    {   return (index_ != c_error) && (index_ != r_illegal); }
    bool is_allocated () const noexcept
    {   return is_valid () && ! is_empty (); }
    bool holds_alternative (const e_class v) const noexcept
    {   return (is_vocabulary () && holds_alternative (index (v))); }
    bool holds_alternative (const e_rel v) const noexcept
    {   return (is_rel () && holds_alternative (index (v))); }
    bool has_prop (const e_property p) const
    {   return is_allocated () && microformat_ -> has_prop (p); }
    bool is_relational () const
    {   return is_allocated () && microformat_ -> is_relational (); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* pe) const
    {   if (is_allocated ())
        {   VERIFY_NOT_NULL (microformat_, __FILE__, __LINE__);
            microformat_ -> verify_attribute (nits, v, e, pe); } }
    bool declared () const { return is_allocated () && microformat_ -> declared (); }
    void set_mf_value (nitpick& nits, const html_version& v, const e_property pp, element& e)
    {   if (is_allocated ())
        {   VERIFY_NOT_NULL (microformat_, __FILE__, __LINE__);
            microformat_ -> set_mf_value (nits, v, pp, e); } }
    ::std::string get_string (const e_property pp)
    {   if (! is_allocated ()) return ::std::string ();
        VERIFY_NOT_NULL (microformat_, __FILE__, __LINE__);
        return microformat_ -> get_string (pp); }
    ::std::string report () const
    {   if (! is_allocated ()) return ::std::string ();
        VERIFY_NOT_NULL (microformat_, __FILE__, __LINE__);
        return microformat_ -> report (); } };
