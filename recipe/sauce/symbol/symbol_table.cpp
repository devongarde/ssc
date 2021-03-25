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
#include "symbol/symbol_table.h"

void symbol_store :: swap (symbol_store& ss) NOEXCEPT
{   first_.swap (ss.first_);
    last_.swap (ss.last_);
    sz_.swap (ss.sz_);
    ::std::swap (v_, ss.v_);
    ::std::swap (ns_, ss.ns_);
    ::std::swap (flags_, ss.flags_);
    ::std::swap (flags2_, ss.flags2_); }

void symbol_table :: swap (symbol_table& s) NOEXCEPT
{   symbol_.swap (s.symbol_);
    reverse_.swap (s.reverse_);
    ::std::swap (wildcards_, s.wildcards_); }

::std::string symbol_table :: value_list (const html_version& v) const
{   ::std::string res;
    for (auto e : symbol_)
        if (does_apply (v, e.second.first_, e.second.last_))
        {   if (! res.empty ()) res += ", ";
            res += e.first.first; }
    return res; }

bool symbol_table :: is_invalid_version (const html_version& v, const ::std::size_t x) const
{   auto i = reverse_.find (x);
    return ((i != reverse_.end ()) && ! may_apply (v, i -> second.first_, i -> second.last_)); }

html_version symbol_table :: first_version (const ::std::size_t x) const
{   auto i = reverse_.find (x);
    if (i == reverse_.end ()) return html_0;
    return (i -> second.first_); }

html_version symbol_table :: final_version (const ::std::size_t x) const
{   auto i = reverse_.find (x);
    if (i == reverse_.end ()) return html_0;
    return (i -> second.last_); }

e_namespace symbol_table :: ns (const ::std::size_t x) const
{   auto i = reverse_.find (x);
    if (i == reverse_.end ()) return ns_default;
    return (i -> second.ns_); }

uint64_t symbol_table :: flags (const ::std::size_t x) const
{   auto i = reverse_.find (x);
    if (i == reverse_.end ()) return NOFLAGS;
    return (i -> second.flags_); }

uint64_t symbol_table :: flags2 (const ::std::size_t x) const
{   auto i = reverse_.find (x);
    if (i == reverse_.end ()) return NOFLAGS;
    return (i -> second.flags2_); }

::std::string symbol_table :: name (const ::std::size_t x) const
{   extern ::std::string namespace_name (const e_namespace ns);
    auto i = reverse_.find (x);
    if (i == reverse_.end ()) return ::std::string ();
    if (i -> second.ns_ == ns_default) return i -> second.sz_;
    ::std::string res (namespace_name (i -> second.ns_));
    res += ":";
    res += i -> second.sz_;
    return res; }

bool symbol_table :: find (const html_version& v, const ::std::string& x, ::std::size_t& res, const e_namespace ns, html_version* first, html_version* last, uint64_t* flags, uint64_t* flags2) const
{   auto i = symbol_.find (symbol_key (x, ns));
    if (i != symbol_.end () && may_apply (v, i -> second.first_, i -> second.last_))
    {   res = i -> second.v_;
        if (first != nullptr) *first = i -> second.first_;
        if (last != nullptr) *last = i -> second.last_;
        if (flags != nullptr) *flags = i -> second.flags_;
        if (flags2 != nullptr) *flags2 = i -> second.flags2_;
        return true; }
    if (! wildcards_) return false;
    auto p = x.find_first_of (":-");
    if ((p == 0) || (p == x.npos) || (p == x.length () - 1)) return false;
    return find (v, x.substr (0, p+1), res, ns, first, last, flags); }

::std::size_t symbol_table :: find (const html_version& v, const ::std::string& x, const e_namespace ns, html_version* first, html_version* last, uint64_t* flags, uint64_t* flags2) const
{   auto i = symbol_.find (symbol_key (x, ns));
    if (i != symbol_.end () && may_apply (v, i -> second.first_, i -> second.last_))
    {   if (first != nullptr) *first = i -> second.first_;
        if (last != nullptr) *last = i -> second.last_;
        if (flags != nullptr) *flags = i -> second.flags_;
        if (flags2 != nullptr) *flags2 = i -> second.flags2_;
        return i -> second.v_; }
    if (! wildcards_) return 0;
    auto p = x.find ('-');
    if ((p == 0) || (p == x.npos))
    {   p = x.find (':');
        if ((p == 0) || (p == x.npos)) return 0; }
    return find (v, x.substr (0, p), ns, first, last, flags); }

void symbol_table :: extend (const ::std::string& key, const ::std::string& symbol, const ::std::size_t value, const e_namespace ns, const html_version& first, const html_version& last, const uint64_t flags, const uint64_t flags2)
{
#ifdef _DEBUG
    if (key.find (",") != ::std::string::npos) ::std::cerr << "key '" << key << "' contains a comma\n";
    if (symbol.find (",") != ::std::string::npos) ::std::cerr << "symbol '" << symbol << "' contains a comma\n";
#endif // _DEBUG
    symbol_.insert (symbol_t::value_type (symbol_key (key, ns), symbol_store (first, last, symbol, value, ns, flags, flags2)));
    reverse_.insert (reverse_t::value_type (value, symbol_store (first, last, symbol, value, ns, flags, flags2))); }

::std::string symbol_table :: after_start (const ::std::string& s) const
{   ::std::size_t len = s.length ();
    if (len > 0)
        for (symbol_t::const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
        {   ::std::string::size_type max = i -> second.sz_.length ();
            if ((max > 0) && (max <= len))
                if (compare_no_case (s.substr (0, max), i -> second.sz_))
                    return s.substr (max); }
    return s; }

::std::string symbol_store :: report () const
{   ::std::stringstream res;
    res << v_ << ":'" << sz_ << "'," << first_.report () << "," << last_.report () << "," << ns_ << "," << flags_ << "," << flags2_;
    return res.str (); }

::std::string symbol_table :: report () const
{   ::std::stringstream res;
    for (symbol_t::const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
    {   res << i -> first.first;
        if (i -> first.second != 0) res << "/" << i -> first.second;
        res << " : " << i -> second.report () << "\n"; }
    return res.str (); }
