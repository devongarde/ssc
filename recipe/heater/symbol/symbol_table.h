/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "symbol/symbol_store.h"
#include "symbol/symbol_key.h"

template < typename CATEGORY > struct behaviour
{   const char* ns_sep () const noexcept { return ":"; }
    bool can_be_default (const CATEGORY ) const noexcept { return false; } };

template < > inline const char* behaviour < e_ontology > :: ns_sep () const noexcept { return ""; }
template < > inline bool behaviour < ident_t > :: can_be_default (const ident_t c) const noexcept { return (c == ns_xhtml); }

template < class V, typename CATEGORY, CATEGORY INIT > class symbol_table : public behaviour < CATEGORY >
{   typedef ssc_map < symbol_key, symbol_store < V, CATEGORY, INIT > > symbol_t;
    typedef ssc_map < ::std::size_t, symbol_store < V, CATEGORY, INIT > > reverse_t;
    symbol_t symbol_;
    reverse_t reverse_;
    bool wildcards_ = false;
public:
    void extend (   const ::std::string& key, const ::std::string& symbol, const ::std::size_t value, const CATEGORY ns = INIT,
                    const V& first = html_0, const V& last = html_0, const flags_t flags = NOFLAGS, const flags_t flags2 = NOFLAGS)
    {
    #ifdef DEBUG
        if ((key.length () > 1) && (key.find (",") != ::std::string::npos)) ::std::cerr << "key '" << key << "' contains a comma\n";
        if ((symbol.length () > 1) && (symbol.find (",") != ::std::string::npos)) ::std::cerr << "symbol '" << symbol << "' contains a comma\n";
    #endif // DEBUG
        symbol_.insert (typename symbol_t::value_type (symbol_key (key, ns), symbol_store < V, CATEGORY, INIT > (first, last, symbol, value, ns, flags, flags2)));
        reverse_.insert (typename reverse_t::value_type (value, symbol_store < V, CATEGORY, INIT > (first, last, symbol, value, ns, flags, flags2))); }
    template < typename VALUE, class LC > void init (nitpick& nits, const symbol_entry < V, VALUE, CATEGORY, INIT > table [], const ::std::size_t size, const bool wildcards = false)
    {   VERIFY_NOT_NULL (table, __FILE__, __LINE__);
        wildcards_ = wildcards;
        const auto t = GSL_SPAN (table, size);
        for (::std::size_t i = 0; (i < size) && (t [i].sz_ != nullptr); ++i)
        {   ::std::string key (enlc < LC > :: to (::std::string (t [i].sz_)));
            auto it = symbol_.find (symbol_key (key, t [i].ns_));
            if (it != symbol_.end ())
                nits.pick (nit_symbol_aleady_defined, es_error, ec_program, "program error: symbol ", t [i].sz_, " already defined (ignoring case)");
            else extend (key, t [i].sz_, static_cast < ::std::size_t > (t [i].v_), t [i].ns_, t [i].first_, t [i].last_, t [i].flags_, t [i].flags2_); } }
    bool find (const V& v, const ::std::string& x, ::std::size_t& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr) const
    {   auto i = symbol_.find (symbol_key (x, ns));
        if (behaviour < CATEGORY > :: can_be_default (ns) && (i == symbol_.end ())) i = symbol_.find (symbol_key (x, INIT));
        if (i != symbol_.end () && may_apply (v, i -> second.first_, i -> second.last_))
        {   res = i -> second.v_;
            if (first != nullptr) *first = i -> second.first_;
            if (last != nullptr) *last = i -> second.last_;
            if (flags != nullptr) *flags = i -> second.flags_;
            if (flags2 != nullptr) *flags2 = i -> second.flags2_;
            return true; }
        if (! wildcards_) return false;
        const auto p = x.find_first_of (":-");
        if ((p == 0) || (p == x.npos) || (p == x.length () - 1)) return false;
        return find (v, x.substr (0, p+1), res, ns, first, last, flags); }
    ::std::size_t find (const V& v, const ::std::string& x, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr) const
    {   auto i = symbol_.find (symbol_key (x, ns));
        if (i != symbol_.end () && may_apply < V > (v, i -> second.first_, i -> second.last_))
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
    template < typename VALUE, class LC > bool find (const V& v, const ::std::string& x, VALUE& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr) const
    {   ::std::size_t val = 0;
        if (! find (v, enlc < LC > :: to (x), val, ns, first, last, flags, flags2)) return false;
        res = GSL_NARROW_CAST < VALUE > (val); return true; }
    bool exists (const ::std::string& x, const CATEGORY ns = INIT) const
    {   return (symbol_.find (symbol_key (x, ns)) != symbol_.end ()); }
    bool parse (const V& v, const ::std::string& x, ::std::size_t& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr)
    {   return find (v, ::boost::algorithm::to_lower_copy (trim_the_lot_off (x)), res, ns, first, last, flags, flags2); }
    template < typename VALUE, class LC > bool parse (const V& v, const ::std::string& x, VALUE& res, const CATEGORY ns = INIT, V* first = nullptr, V* last = nullptr, flags_t* flags = nullptr, flags_t* flags2 = nullptr)
    {   ::std::size_t val = 0;
        if (! parse (v, enlc < LC > :: to (x), val, ns, first, last, flags, flags2)) return false;
        res = GSL_NARROW_CAST < VALUE > (val);
        return true; }
    ::std::string value_list (const V& v) const
    {   ::std::string res;
        for (auto e : symbol_)
            if (does_apply < V > (v, e.second.first_, e.second.last_))
            {   if (! res.empty ()) res += ", ";
                res += e.first.first; }
        return res; }
    ::std::size_t value_count (const V& ) const { return symbol_.size (); }
    bool is_invalid_version (const V& v, const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        return ((i != reverse_.end ()) && ! may_apply < V > (v, i -> second.first_, i -> second.last_)); }
    V first_version (const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        if (i == reverse_.end ()) return html_0;
        return (i -> second.first_); }
    V final_version (const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        if (i == reverse_.end ()) return html_0;
        return (i -> second.last_); }
    CATEGORY ns (const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        if (i == reverse_.end ()) return INIT;
        return (i -> second.ns_); }
    flags_t flags (const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        if (i == reverse_.end ()) return NOFLAGS;
        return (i -> second.flags_); }
    flags_t flags2 (const ::std::size_t x) const
    {   auto i = reverse_.find (x);
        if (i == reverse_.end ()) return NOFLAGS;
        return (i -> second.flags2_); }
    template < typename VALUE > VALUE starts_with (const ::std::string& s, ::std::string::size_type* ends_at = nullptr) const
    {   ::std::size_t len = s.length ();
        if (len > 0)
            for (typename symbol_t :: const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
            {   ::std::string::size_type max = i -> second.sz_.length ();
                if ((max > 0) && (max <= len))
                    if (compare_no_case (s.substr (0, max), i -> second.sz_))
                    {   if (ends_at != nullptr) *ends_at = max;
                        return static_cast < VALUE > (i -> second.v_); } }
        return static_cast < VALUE > (0); }
    ::std::string after_start (const ::std::string& s) const
    {   ::std::size_t len = s.length ();
        if (len > 0)
            for (typename symbol_t :: const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
            {   ::std::string::size_type max = i -> second.sz_.length ();
                if ((max > 0) && (max <= len))
                    if (compare_no_case (s.substr (0, max), i -> second.sz_))
                        return s.substr (max); }
        return s; }
    ::std::string name (const ::std::size_t x, const bool ns_req = false) const
    {   extern ::std::string namespace_name (const CATEGORY ns);
        auto i = reverse_.find (x);
        if (i == reverse_.end ()) return ::std::string ();
        if ((! ns_req) && (i -> second.ns_ == INIT)) return i -> second.sz_;
        ::std::string res (namespace_name (i -> second.ns_));
        res += behaviour < CATEGORY > :: ns_sep ();
        res += i -> second.sz_;
        return res; }
    ::std::string report () const
    {   ::std::stringstream res;
        for (typename symbol_t :: const_iterator i = symbol_.cbegin (); i != symbol_.cend (); ++i)
        {   res << i -> first.first;
            if (i -> first.second != 0) res << "/" << i -> first.second;
            res << " : " << i -> second.report () << "\n"; }
        return res.str (); } };
