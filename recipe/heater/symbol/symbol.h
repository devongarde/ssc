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
#include "symbol/symbol_table.h"

::std::string namespace_name (const ident_t ns);
::std::string namespace_name (const e_ontology ns);

// VALUE is presumed to be an enum or an int
template < class V, typename VALUE, typename CATEGORY = ident_t, CATEGORY INIT = 0, class LC = sz_true > class symbol : public enlc < LC >
{   typedef symbol_table < V, CATEGORY, INIT > table_t;
    typedef ::std::shared_ptr < table_t > table_ptr;
    static table_ptr table_;
    V first_, last_;
    VALUE value_ = GSL_NARROW_CAST < VALUE > (0);
    CATEGORY ns_ = INIT;
    bool unknown_ = true;
    flags_t flags_ = NOFLAGS, flags2_ = NOFLAGS;
public:
    typedef VALUE value_type;
	DEFAULT_CONSTRUCTORS (symbol);
    explicit symbol (const VALUE& value, const CATEGORY ns = INIT) : value_ (value), ns_ (ns), unknown_ (false)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        first_ = table_ -> first_version (value);
        last_ = table_ -> final_version (value);
        flags_ = table_ -> flags (value);
        flags2_ = table_ -> flags2 (value); }
    explicit symbol (const V& v, const ::std::string& x, const CATEGORY ns = INIT) : ns_ (ns)
    {   unknown_ = ! find (v, x, value_, ns, &first_, &last_, &flags_, &flags2_); }
    void swap (symbol& s) noexcept
    {   ::std::swap (unknown_, s.unknown_);
        ::std::swap (value_, s.value_);
        ::std::swap (ns_, s.ns_);
        ::std::swap (flags_, s.flags_);
        ::std::swap (flags2_, s.flags2_);
        first_.swap (s.first_);
        last_.swap (s.last_); }
    void reset () { symbol tmp; swap (tmp); }
    void reset (const VALUE& v) { symbol tmp (v); swap (tmp); }
    static void init (nitpick& nits, const symbol_entry < V, VALUE, CATEGORY, INIT > table [], const ::std::size_t size, const bool wildcards = false)
    {   table_ = table_ptr (new table_t);
        VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        table_ -> template init < VALUE, LC > (nits, table, size, wildcards); }
    static bool find (const V& v, const ::std::string& x, VALUE& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> template find < VALUE, LC > (v, x, res, ns, first, last, flags, flags2); }
    static VALUE find (const V& v, const ::std::string& x, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return static_cast < VALUE > (table_ -> find (v, enlc < LC > :: to (x), ns, first, last, flags, flags2)); }
    static bool exists (const ::std::string& x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> exists (x); }
    static bool parse (nitpick& , const V& v, const ::std::string& x, VALUE& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> template parse < VALUE, LC > (v, x, res, ns, first, last, flags, flags2); }
    bool parse (nitpick& , const V& v, const ::std::string& x, const CATEGORY ns = INIT)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        unknown_ = ! table_ -> template parse < VALUE, LC > (v, x, value_, ns, &first_, &last_, &flags_, &flags2_);
        if (unknown_) return false;
        ns_ = ns; return true; }
    static ::std::string value_list (const V& v)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> value_list (v); }
    static ::std::size_t value_count (const V& v)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> value_count (v); }
    static ::std::string name (const VALUE x, const bool ns_req = false)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> name (x, ns_req); }
    static bool is_invalid_version (const V& v, const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> is_invalid_version (v, x); }
    static V first_version (const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> first_version (x); }
    static V final_version (const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> final_version (x); }
    static CATEGORY category (const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> ns (x); }
    static flags_t flags (const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> flags (x); }
    static flags_t categories (const VALUE x)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> flags2 (x); }
    static void extend (const ::std::string& key, const ::std::string& symbol, const ::std::size_t value, const CATEGORY ns = INIT,
                        const V& first = html_0, const V& last = html_0, const flags_t flags = 0, const flags_t flags2 = 0)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        table_ -> extend (key, symbol, value, ns, first, last, flags, flags2); }
    static void extend (const ::std::string& symbol, const ::std::size_t value, const CATEGORY ns = INIT, const V& first = html_0, const V& last = html_0, const flags_t flags = 0, const flags_t flags2 = 0)
    {   extend (enlc < LC > :: to (symbol), symbol, value, ns, first, last, flags, flags2); }
    VALUE get () const noexcept { if (unknown_) return GSL_NARROW_CAST <VALUE> (0); return value_; }
    V first () const noexcept { return first_; }
    V last () const noexcept { return last_; }
    V first (const ::std::size_t v) const
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> first_version (v); }
    V last (const ::std::size_t v) const
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> final_version (v); }
    CATEGORY ns () const noexcept { return ns_; }
    void ns (const CATEGORY n) noexcept { ns_ = n; }
    flags_t flags () const noexcept { return flags_; }
    flags_t categories () const noexcept { return flags2_; }
    void refresh (const flags_t f) noexcept { flags_ |= f; }
    void congeal (const flags_t c) noexcept { flags2_ = c; }
    void set (const V& ver, const VALUE& v, const CATEGORY ns = INIT, const flags_t flags = 0, const flags_t flags2 = 0) noexcept
    {   value_ = v; ns_ = ns; first_ = last_ = ver; flags_ = flags; flags2_ = flags2; unknown_ = false; }
    operator VALUE () const noexcept { return get (); }
    bool unknown () const noexcept { return unknown_; }
    bool required () const { return first_.required (); }
    ::std::string name (const bool ns_req = false, const bool colonise = true) const
    {   if (unknown_) return "(unknown)";
        VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        ::std::string res (table_ -> name (get ()));
        if (res.empty ())
        {   res = "(";
            res += ::boost::lexical_cast < ::std::string > (value_);
            res += ")"; }
        if (ns_req || (ns_ != ns_default))
            if (colonise) res = namespace_name (ns_) + ":" + res;
            else res = namespace_name (ns_) + res;
        return res; }
    static VALUE starts_with (const ::std::string& s, ::std::string::size_type* ends_at = nullptr)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> template starts_with < VALUE> (s, ends_at); }
    static ::std::string after_start (const ::std::string& s)
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> after_start (s); }
    bool invalid () const noexcept { return unknown_; }
    bool is_invalid_version (const V& v)
    {   return ((v > last ()) || (v < first ())); }
    static ::std::string table ()
    {   VERIFY_NOT_NULL (table_.get (), __FILE__, __LINE__);
        return table_ -> report (); } };

template < class V, typename VALUE, typename CATEGORY, CATEGORY INIT, class LC >
    typename symbol < V, VALUE, CATEGORY, INIT, LC > :: table_ptr  symbol < V, VALUE, CATEGORY, INIT, LC > :: table_;
