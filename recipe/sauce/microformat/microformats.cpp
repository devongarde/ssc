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

bool microformats::allocated (const ::std::size_t v) const
{   return ! mf_ [v].is_empty (); }

void microformats::alloc (const ::std::size_t v)
{   DBG_ASSERT (! allocated (v));
    mf_ [v] = microformat_pv::alloc_microformat_pv (v); }

bool microformats::has (const ::std::size_t v, const e_property p) const
{   DBG_ASSERT (allocated (v));
    return mf_ [v].has_prop (p); }

bool microformats::has (const ::std::size_t v) const
{   return allocated (v); }

bool microformats::empty (const ::std::size_t v) const
{   if (! allocated (v)) return true;
    return mf_ [v].is_empty (); }

bool microformats::has_property (const ::std::size_t v, const e_property p) const
{   DBG_ASSERT (allocated (v));
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

void microformats::validate (nitpick& nits, const html_version& v, const elem& e)
{   for (auto mf : mf_)
        if (mf.is_allocated ())
            mf.get () -> validate (nits, v, e); }

bool microformats::is_declared (const ::std::size_t v) const
{   if (! allocated (v)) return false;
    for (auto mf : mf_)
        if (mf.is_allocated ())
            if (! mf.get () -> declared ()) return false;
    return true; }

void microformats::set_mf_value (nitpick& nits, const html_version& ver, const ::std::size_t v, const e_property pp, element& e)
{   DBG_ASSERT (allocated (v));
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
{   if (! mf_ [v].is_allocated ())
        mf_ [v] = microformat_pv::alloc_microformat_pv (v);
    if (mf_ [v].is_allocated ())
        mf_ [v].get () -> declare (); }

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


