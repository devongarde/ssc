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
#include "utility/common.h"
#include "type/sz.h"

template < class LC > struct enlc
{   static ::std::string to (const ::std::string& from) { return ::boost::to_lower_copy (from); } };

template < > struct enlc < sz_false >
{   static ::std::string to (const ::std::string& from) { return from; } };

template < typename VALUE > struct symbol_entry
{   html_version    first_, last_;
    const char*     sz_ = nullptr;
    VALUE           v_ = static_cast < VALUE > (0);
    e_namespace     ns_ = ns_default;
    uint64_t        flags_ = 0;
    uint64_t        flags2_ = 0;
#ifdef REQUIRE_CONSTRUCTOR
    symbol_entry (  const html_version& first, const html_version& last, const char* sz, const VALUE v,
                    const e_namespace ns = ns_default, const uint64_t flags = 0, const uint64_t flags2 = 0)
        : first_ (first), last_ (last), sz_ (sz), v_ (v), ns_ (ns), flags_ (flags), flags2_ (flags2) { }
#endif
};

struct symbol_entry_t
{   html_version    first_, last_;
    const char*     sz_ = nullptr;
    ::std::size_t   v_ = 0;
    e_namespace     ns_ = ns_default;
    uint64_t        flags_ = 0;
    uint64_t        flags2_ = 0; };

struct symbol_store
{   html_version    first_, last_;
    ::std::string   sz_;
    ::std::size_t   v_ = 0;
    e_namespace     ns_ = ns_default;
    uint64_t        flags_ = 0;
    uint64_t        flags2_ = 0;
	symbol_store() = default;
    symbol_store (const symbol_store& ss) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	symbol_store (symbol_store&& ss) = default;
#endif // VS
	~symbol_store() = default;
    symbol_store (const html_version& first, const html_version& last, const ::std::string& str, const ::std::size_t v, const e_namespace ns = ns_default, const uint64_t flags = NOFLAGS, const uint64_t flags2 = NOFLAGS)
        : first_ (first), last_ (last), sz_ (str), v_ (v), ns_ (ns), flags_ (flags), flags2_ (flags2) { }
    symbol_store (const html_version& first, const html_version& last, const char* sz, const ::std::size_t v, const e_namespace ns = ns_default, const uint64_t flags = NOFLAGS, const uint64_t flags2 = NOFLAGS)
        : first_ (first), last_ (last), sz_ (sz), v_ (v), ns_ (ns), flags_ (flags), flags2_ (flags2) { }
    symbol_store (const symbol_entry_t& se)
        : first_ (se.first_), last_ (se.last_), sz_ (se.sz_), v_ (se.v_), ns_ (se.ns_), flags_ (se.flags_), flags2_ (se.flags2_) { }
    symbol_store& operator = (const symbol_store& ss) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	symbol_store& operator = (symbol_store&& ss) = default;
#endif
    void swap (symbol_store& ss) NOEXCEPT;
    void reset () { symbol_store ss; swap (ss); }
    void reset (const symbol_store& s) { symbol_store ss (s); swap (ss); } };

typedef ::std::pair < ::std::string, e_namespace > symbol_key;

inline bool operator == (const symbol_key& lhs, const symbol_key& rhs)
{   return (lhs.second == rhs.second) && (lhs.first == rhs.first); }

inline bool operator != (const symbol_key& lhs, const symbol_key& rhs)
{   return ! (lhs == rhs); }

inline bool operator < (const symbol_key& lhs, const symbol_key& rhs)
{   if (lhs.second < rhs.second) return true;
    if (lhs.second > rhs.second) return false;
    return (lhs.first < rhs.first); }

inline bool operator >= (const symbol_key& lhs, const symbol_key& rhs)
{   return ! (lhs < rhs); }

inline bool operator > (const symbol_key& lhs, const symbol_key& rhs)
{   return (lhs >= rhs) && (lhs != rhs); }

inline bool operator <= (const symbol_key& lhs, const symbol_key& rhs)
{   return ! (lhs > rhs); }

template < > struct std::hash < symbol_key >
{   ::std::size_t operator() (const symbol_key& k) const
    {   ::std::size_t h = ::std::hash < ::std::string > () (k.first); // bollocks
        return ::std::hash <::std::size_t> () (h  ^ static_cast < ::std::size_t > (k.second)); } };

class symbol_table
{   typedef ssc_map < symbol_key, symbol_store > symbol_t;
    typedef ssc_map < ::std::size_t, symbol_store > reverse_t;
    symbol_t symbol_;
    reverse_t reverse_;
    bool wildcards_ = false;
public:
    void swap (symbol_table& s) NOEXCEPT;
    void extend (   const ::std::string& key, const ::std::string& symbol, const ::std::size_t value, const e_namespace ns = ns_default,
                    const html_version& first = html_0, const html_version& last = html_0, const uint64_t flags = 0, const uint64_t flags2 = 0);
    template < typename VALUE, class LC > void init (nitpick& nits, const symbol_entry < VALUE > table [], const ::std::size_t size, const bool wildcards = false)
    {   wildcards_ = wildcards;
        for (::std::size_t i = 0; i < size; ++i)
            if (table [i].sz_ == nullptr) break;
            else
            {   ::std::string key (enlc < LC > :: to (::std::string (table [i].sz_)));
                if (symbol_.find (symbol_key (key, table [i].ns_)) != symbol_.end ())
                    nits.pick (nit_symbol_aleady_defined, es_error, ec_program, "program error: symbol ", table [i].sz_, " already defined");
                else extend (key, table [i].sz_, static_cast < ::std::size_t > (table [i].v_), table [i].ns_, table [i].first_, table [i].last_, table [i].flags_, table [i].flags2_); } }
    bool find (const html_version& v, const ::std::string& x, ::std::size_t& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr) const;
    ::std::size_t find (const html_version& v, const ::std::string& x, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr) const;
    template < typename VALUE, class LC > bool find (const html_version& v, const ::std::string& x, VALUE& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr) const
    {   ::std::size_t val = 0;
        if (! find (v, enlc < LC > :: to (x), val, ns, first, last, flags, flags2)) return false;
        res = static_cast < VALUE > (val); return true; }
    bool exists (const ::std::string& x, const e_namespace ns = ns_default) const
    {   return (symbol_.find (symbol_key (x, ns)) != symbol_.end ()); }
    bool parse (const html_version& v, const ::std::string& x, ::std::size_t& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr)
    {   return find (v, ::boost::algorithm::to_lower_copy (trim_the_lot_off (x)), res, ns, first, last, flags, flags2); }
    template < typename VALUE, class LC > bool parse (const html_version& v, const ::std::string& x, VALUE& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr)
    {   ::std::size_t val = 0;
        if (! parse (v, enlc < LC > :: to (x), val, ns, first, last, flags, flags2)) return false;
        res = static_cast < VALUE > (val); return true; }
    ::std::string value_list (const html_version& v) const;
    ::std::size_t value_count (const html_version& ) const { return symbol_.size (); }
    bool is_invalid_version (const html_version& v, const ::std::size_t x) const;
    html_version first_version (const ::std::size_t x) const;
    html_version final_version (const ::std::size_t x) const;
    e_namespace ns (const ::std::size_t x) const;
    uint64_t flags (const ::std::size_t x) const;
    uint64_t flags2 (const ::std::size_t x) const;
    template < typename VALUE > VALUE starts_with (const ::std::string& s) const
    {   ::std::size_t len = s.length ();
        if (len > 0)
            for (symbol_t::const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
            {   ::std::string::size_type max = i -> second.sz_.length ();
                if ((max > 0) && (max <= len))
                    if (compare_no_case (s.substr (0, max), i -> second.sz_))
                        return static_cast < VALUE > (i -> second.v_); }
        return static_cast < VALUE > (0); }
    ::std::string after_start (const ::std::string& s) const;
    ::std::string name (const ::std::size_t x) const; };
