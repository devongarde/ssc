/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "symbol/symbol_entry.h"

template < class V, typename CATEGORY, CATEGORY INIT > struct symbol_store
{   V               first_, last_;
    ::std::string   sz_;
    ::std::size_t   v_ = 0;
    CATEGORY        ns_ = INIT;
    flags_t        flags_ = 0, flags2_ = 0;
	symbol_store () = default;
    symbol_store (const symbol_store& ss) = default;
	symbol_store (symbol_store&& ss) = default;
	~symbol_store () = default;
    symbol_store (const V& first, const V& last, const ::std::string& str, const ::std::size_t v, const CATEGORY ns = INIT, const flags_t flags = NOFLAGS, const flags_t flags2 = NOFLAGS)
        : first_ (first), last_ (last), sz_ (str), v_ (v), ns_ (ns), flags_ (flags), flags2_ (flags2) { }
    symbol_store (const V& first, const V& last, const char* sz, const ::std::size_t v, const CATEGORY ns = INIT, const flags_t flags = NOFLAGS, const flags_t flags2 = NOFLAGS)
        : first_ (first), last_ (last), sz_ (sz), v_ (v), ns_ (ns), flags_ (flags), flags2_ (flags2) { }
    symbol_store (const symbol_entry_t < V >& se)
        : first_ (se.first_), last_ (se.last_), sz_ (se.sz_), v_ (se.v_), ns_ (se.ns_), flags_ (se.flags_), flags2_ (se.flags2_) { }
    symbol_store& operator = (const symbol_store& ss) = default;
	symbol_store& operator = (symbol_store&& ss) = default;
    void swap (symbol_store& ss) noexcept
    {   first_.swap (ss.first_);
        last_.swap (ss.last_);
        sz_.swap (ss.sz_);
        ::std::swap (v_, ss.v_);
        ::std::swap (ns_, ss.ns_);
        ::std::swap (flags_, ss.flags_);
        ::std::swap (flags2_, ss.flags2_); }
    ::std::string report () const
    {   ::std::stringstream res;
        res << v_ << ":'" << sz_ << "'," << first_.report () << "," << last_.report () << "," << ns_ << "," << flags_ << "," << flags2_;
        return res.str (); }
    void reset () { symbol_store ss; swap (ss); }
    void reset (const symbol_store& s) { symbol_store ss (s); swap (ss); } };
