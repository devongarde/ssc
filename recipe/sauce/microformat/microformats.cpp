/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#include "main/standard.h"
#include "microformat/microformats.h"
#include "microformat/microformat_constructor.h"

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26481) // linter, read the sodding code. Things ARE checked.
#endif // _MSC_VER
bool microformats::allocated (const ::std::size_t v) const noexcept
{   if (v >= mf_.size ()) return false;
    return ! mf_ [v].is_empty (); }

void microformats::alloc (const ::std::size_t v)
{   PRESUME (! allocated (v), __FILE__, __LINE__);
    mf_ [v] = microformat_pv::alloc_microformat_pv (v); }

bool microformats::has (const ::std::size_t v, const e_property p) const
{   PRESUME (allocated (v), __FILE__, __LINE__);
    return mf_ [v].has_prop (p); }

bool microformats::has (const ::std::size_t v) const noexcept
{   return allocated (v); }

bool microformats::empty (const ::std::size_t v) const noexcept
{   return (! allocated (v)); }

bool microformats::has_property (const ::std::size_t v, const e_property p) const
{   PRESUME (allocated (v), __FILE__, __LINE__);
    return mf_ [v].has_prop (p); }

e_class microformats::plausible_vocabulary (const e_property p) const
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            if (mf.get () -> has_prop (p))
                return mf.which_vocabulary ();
    return c_error; }

bool microformats::is_relational () const
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            if (mf.get () -> is_relational ()) return true;
    return false; }

void microformats::verify_attributes (nitpick& nits, const html_version& v, const elem& e, element* pe)
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            mf.get () -> verify_attribute (nits, v, e, pe); }

bool microformats::is_declared (const ::std::size_t v) const
{   if (! allocated (v)) return false;
    for (auto mf : mf_)
        if (mf.is_allocated ())
            if (! mf.get () -> declared ()) return false;
    return true; }

void microformats::set_mf_value (nitpick& nits, const html_version& ver, const ::std::size_t v, const e_property pp, element& e)
{   PRESUME (allocated (v), __FILE__, __LINE__);
    return mf_ [v].set_mf_value (nits, ver, pp, e); }

::std::string microformats::get_string (const ::std::size_t v, const e_property pp)
{   if (! allocated (v)) return ::std::string ();
    return mf_ [v].get_string (pp); }

bool microformats::empty () const
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            if (! mf.get () -> empty ()) return false;
    return true; }

::std::string microformats::report () const
{   ::std::string res;
    for (auto mf : mf_)
        if (mf.is_allocated ())
            res += mf.get () -> report ();
    return res; }

void microformats::declare (const ::std::size_t v)
{   if (! mf_.at (v).is_allocated ())
        mf_.at (v) = microformat_pv::alloc_microformat_pv (v);
    if (mf_.at (v).is_allocated ())
        mf_.at (v).get () -> declare (); }

void microformats::reset ()
{   for (auto mf : mf_)
        mf.reset (); }

void microformats::verify (nitpick& nits, const html_version& v)
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            mf.get () -> verify (nits, v); }

void microformats::text (const ::std::string& s)
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            mf.get () -> text (s); }

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
