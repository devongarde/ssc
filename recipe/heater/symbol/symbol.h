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
#include "symbol/symbol_table.h"

::std::string namespace_name (const e_namespace ns);

// VALUE is presumed to be an enum or an int ; will enforce when concepts are generally available
template < typename VALUE, class LC = sz_true > class symbol : public enlc < LC >
{   static symbol_table table_;
    html_version first_, last_;
    VALUE value_ = static_cast < VALUE > (0);
    e_namespace ns_ = ns_default;
    bool unknown_ = true;
    uint64_t flags_ = NOFLAGS, flags2_ = NOFLAGS;
public:
    typedef VALUE value_type;
	symbol () = default;
    symbol (const symbol& s) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	symbol (symbol&&) = default;
#endif // VS
    explicit symbol (const VALUE& v, const e_namespace ns = ns_default) : value_ (v), ns_ (ns), unknown_ (false)
    {   first_ = table_.first_version (v);
        last_ = table_.final_version (v);
        flags_ = table_.flags (v);
        flags2_ = table_.flags2 (v); }
    explicit symbol (const html_version& v, const ::std::string& x, const e_namespace ns = ns_default)
    { unknown_ = ! find (v, x, value_, ns, &first_, &last_, &flags_, &flags2_); }
	symbol& operator = (const symbol&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	symbol& operator = (symbol&&) = default;
#endif // VS
    void swap (symbol& s) NOEXCEPT
    {   ::std::swap (unknown_, s.unknown_);
        ::std::swap (value_, s.value_);
        ::std::swap (ns_, s.ns_);
        ::std::swap (flags_, s.flags_);
        ::std::swap (flags2_, s.flags2_);
        first_.swap (s.first_);
        last_.swap (s.last_); }
    void reset () { symbol tmp; swap (tmp); }
    void reset (const VALUE& v) { symbol tmp (v); swap (tmp); }
    static void init (nitpick& nits, const symbol_entry < VALUE > table [], const ::std::size_t size, const bool wildcards = false)
    {   table_.init < VALUE, LC > (nits, table, size, wildcards); }
    static bool find (const html_version& v, const ::std::string& x, VALUE& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr)
    {   return table_.find < VALUE, LC > (v, x, res, ns, first, last, flags, flags2); }
    static VALUE find (const html_version& v, const ::std::string& x, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr)
    {   return static_cast < VALUE > (table_.find (v, enlc < LC > :: to (x), ns, first, last, flags, flags2)); }
    static bool exists (const ::std::string& x) { return table_.exists (x); }
    static bool parse (nitpick& , const html_version& v, const ::std::string& x, VALUE& res, const e_namespace ns = ns_default, html_version* first = nullptr, html_version* last = nullptr, uint64_t* flags = nullptr, uint64_t* flags2 = nullptr)
    {   return table_.parse < VALUE, LC > (v, x, res, ns, first, last, flags, flags2); }
    bool parse (nitpick& , const html_version& v, const ::std::string& x, const e_namespace ns = ns_default)
    {   unknown_ = ! table_.parse < VALUE, LC > (v, x, value_, ns, &first_, &last_, &flags_, &flags2_);
        if (unknown_) return false;
        ns_ = ns; return true; }
    static ::std::string value_list (const html_version& v) { return table_.value_list (v); }
    static ::std::size_t value_count (const html_version& v) { return table_.value_count (v); }
    static ::std::string name (const VALUE x) { return table_.name (x); }
    static bool is_invalid_version (const html_version& v, const VALUE x) { return table_.is_invalid_version (v, x); }
    static html_version first_version (const VALUE x) { return table_.first_version (x); }
    static html_version final_version (const VALUE x) { return table_.final_version (x); }
    static uint64_t flags (const VALUE x) { return table_.flags (x); }
    static uint64_t categories (const VALUE x) { return table_.flags2 (x); }
    static void extend (const ::std::string& key, const ::std::string& symbol, const ::std::size_t value, const e_namespace ns = ns_default,
                        const html_version& first = html_0, const html_version& last = html_0, const uint64_t flags = 0, const uint64_t flags2 = 0)
    {   table_.extend (key, symbol, value, ns, first, last, flags, flags2); }
    static void extend (const ::std::string& symbol, const ::std::size_t value, const e_namespace ns = ns_default, const html_version& first = html_0, const html_version& last = html_0, const uint64_t flags = 0, const uint64_t flags2 = 0)
    {   extend (enlc < LC > :: to (symbol), symbol, value, ns, first, last, flags, flags2); }
    VALUE get () const { if (unknown_) return static_cast <VALUE> (0); return value_; }
    html_version first () const { return first_; }
    html_version last () const { return last_; }
    e_namespace ns () const { return ns_; }
    void ns (const e_namespace n) { ns_ = n; }
    uint64_t flags () const { return flags_; }
    uint64_t categories () const { return flags2_; }
    void refresh (const uint64_t f) { flags_ |= f; }
    void congeal (const uint64_t c) { flags2_ = c; }
    void set (const html_version& ver, const VALUE& v, const e_namespace ns = ns_default, const uint64_t flags = 0, const uint64_t flags2 = 0)
    {   value_ = v; ns_ = ns; first_ = last_ = ver; flags_ = flags; flags2_ = flags2; unknown_ = false; }
    operator VALUE () const { return get (); }
    bool unknown () const { return unknown_; }
    bool required () const { return first_.required (); }
    ::std::string name () const
    {   if (unknown_) return "(unknown)";
        ::std::string res (table_.name (get ()));
        if (res.empty ())
        {   res = "(";
            res += ::boost::lexical_cast < ::std::string > (value_);
            res += ")"; }
        if (ns_ != ns_default) res = namespace_name (ns_) + ":" + res;
        return res; }
    static VALUE starts_with (const ::std::string& s)
    {   return table_.starts_with < VALUE> (s); }
    static ::std::string after_start (const ::std::string& s)
    {   return table_.after_start (s); }
   bool invalid () const { return unknown_; }
    bool is_invalid_version (const html_version& v)
    {   return ((v > last ()) || (v < first ())); } };

template < typename VALUE, class LC > symbol_table symbol < VALUE, LC > :: table_;
