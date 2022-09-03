/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "type/type_enum.h"

template < typename TYPE, e_type E, typename CATEGORY = ident_t, CATEGORY INIT = 0 >
    struct enum_vec_base : public type_base < TYPE, E >
{   typedef enum_n < E, TYPE, CATEGORY, INIT > base_t;
    typedef ::std::vector < base_t > vec_t;
    typedef TYPE base_type;
    typedef vec_t value_type;
    vec_t value_;
    ::std::string original_;
    enum_vec_base () = default;
    enum_vec_base (const enum_vec_base& s) = default;
    enum_vec_base (enum_vec_base&&) = default;
    explicit enum_vec_base (const html_version& v, const ::std::string& s);
    explicit enum_vec_base (element* box) noexcept : type_base < TYPE, E > (box) { }
    enum_vec_base& operator = (const enum_vec_base&) = default;
    enum_vec_base& operator = (enum_vec_base&&) = default;
    ~enum_vec_base () = default;
    static ::std::string values (const html_version& ) { return ::std::string (); }
    static ::std::size_t value_count () { return 0; }
    void swap (enum_vec_base& t) noexcept;
    ::std::string get_string () const { return ::std::string (); }
    ::std::string name () const { return ::std::string (); }
    static ::std::string name (const TYPE ) { return ::std::string (); }
    ::std::string original () const { return original_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    static vec_t default_value () { return vec_t (); }
    ::std::size_t size () const noexcept { return value_.size (); }
    bool has_value (const base_type& b) const
    {   if (! type_base < TYPE, E > :: good ()) return false;
        return (value_.find (b) != vec_t::npos); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << "=\""; bool first = true;
        for (auto e : value_)
        {   if (! first) ss << ' ';
            first = false;
            ss << e.get_string (); }
        ss << '"'; }
    vec_t get () const { return value_; } };

template < typename TYPE, e_type E, typename CATEGORY, CATEGORY INIT >
    enum_vec_base < TYPE, E, CATEGORY, INIT > :: enum_vec_base (const html_version& v, const ::std::string& s)
{   enum_vec_base < TYPE, E > e;
    e.set_value (v, s);
    if (e.good ()) swap (e); }

template < typename TYPE, e_type E, typename CATEGORY, CATEGORY INIT >
    void enum_vec_base < TYPE, E, CATEGORY, INIT > :: swap (enum_vec_base& t) noexcept
{   ::std::swap (value_, t.value_);
    original_.swap (t.original_);
    type_base < TYPE, E >::swap (t); }

template < typename TYPE, e_type E, typename CATEGORY, CATEGORY INIT >
    void enum_vec_base < TYPE, E, CATEGORY, INIT > :: set_value (nitpick& nits, const html_version& , const ::std::string& s)
{   original_ = s;
    nits.pick (nit_missing_set_value, es_error, ec_type, "Internal error: an enum vector is missing setvalue");
    type_base < TYPE, E > :: status (s_invalid); }

template < e_type E, typename ENUM, typename CATEGORY = ident_t, CATEGORY INIT = 0 >
    struct enum_vec : public enum_vec_base < ENUM, E, CATEGORY, INIT >
{   using enum_vec_base < ENUM, E, CATEGORY, INIT > :: enum_vec_base;
    static e_animation_type animation_type () noexcept { return at_other; }
    void swap (enum_vec& n) noexcept
    {   enum_vec_base < ENUM, E, CATEGORY, INIT > :: swap (n); }
    void reset ()
    {   enum_vec tmp;
        swap (tmp); }
    void reset (const enum_vec& n)
    {   enum_vec tmp (n);
        swap (tmp); }
    static void init (nitpick& nits, const symbol_entry < html_version, ENUM, CATEGORY, INIT > table [], const ::std::size_t size, const bool wildcards = false)
    {   symbol < html_version, ENUM, CATEGORY, INIT > :: init (nits, table, size, wildcards); }
    static void extend (const vstr_t& extension, const std::size_t s = 0)
    {   for (auto e : extension)
            symbol < html_version, ENUM, CATEGORY, INIT > :: extend (e, static_cast < ENUM > (s)); }
    ::std::string values (const html_version& v) const
    {   return symbol < html_version, ENUM, CATEGORY, INIT > :: value_list (v); }
    ::std::string get_string () const
    {   ::std::string res;
        for (auto e : enum_vec_base < ENUM, E, CATEGORY, INIT > :: value_)
        {   if (! res.empty ()) res += " ";
            if (e.good ())
            {   ::std::string s (e.get_string ());
                if (s.empty ()) s = e.original ();
                res += s; } }
        return res; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss);
    ::std::string name () const
    {   return get_string (); }
    static ::std::string name (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT > :: name (e); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   bool bitten = false;
        ss << "=\"";
        for (auto e : enum_vec_base < ENUM, E, CATEGORY, INIT > :: value_)
            if (! e.empty ())
            {   ::std::string s (e.get_string ());
                if (s.empty ()) s = e.original ();
                if (! s.empty ())
                {   if (bitten) ss << " ";
                    ss << s;
                    bitten = true; } }
        ss << "\""; }
    static ::std::size_t value_count ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT > :: value_count (); } };

template < e_type E, typename ENUM, typename CATEGORY, CATEGORY INIT >
    void enum_vec < E, ENUM, CATEGORY, INIT > :: set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   enum_vec_base < ENUM, E > :: original_ = ss;
    bool res = true;
    vstr_t strs;
    ::std::string sss (trim_the_lot_off (ss));
    ::boost::algorithm::split (strs, sss, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    for (auto s : strs)
    {   typename enum_vec_base < ENUM, E > :: base_t t;
        t.set_value (nits, v, s);
        enum_vec_base < ENUM, E > :: value_.push_back (t);
        if (t.invalid ())
        {   res = false;
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is not a valid value"); }
        else if (t.first ().dinosaur ())
            nits.pick (nit_dinosaur, es_info, ec_type, "been dancing with the dinosaurs, have we? (", quote (s), " is archaic)"); }
    if (strs.size () == 0) enum_vec_base < ENUM, E > :: status (s_empty);
    else if (res) enum_vec_base < ENUM, E > :: status (s_good);
    else enum_vec_base < ENUM, E > :: status (s_invalid); }

template < e_type E, typename ENUM, typename CATEGORY = ident_t, CATEGORY INIT = 0 >
    struct enum_constrained_vec : public enum_vec < E, ENUM, CATEGORY, INIT >
{   using enum_vec < E, ENUM, CATEGORY, INIT > :: enum_vec;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss); };

template < e_type E, typename ENUM, typename CATEGORY, CATEGORY INIT >
    void enum_constrained_vec < E, ENUM, CATEGORY, INIT > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_vec < E, ENUM, CATEGORY, INIT > :: set_value (nits, v, s);
    bool first = true;
    bool ok = true;
    constexpr ::std::size_t max_combinable_enum = 32;
    ::std::bitset < max_combinable_enum > bs, gs, said;
    if (enum_vec < E, ENUM, CATEGORY, INIT > :: good ())
    {   for (auto val : enum_vec < E, ENUM, CATEGORY, INIT > :: value_)
        {   if (val > GSL_NARROW_CAST < int > (max_combinable_enum))
            {   PRESUME (false, __FILE__, __LINE__);
                nits.pick (nit_not_combine, es_catastrophic, ec_type, val.name (), " is too big; abandoning constrained enum check");
                ok = false; break; }
            if (bs.test (val))
            {   nits.pick (nit_not_combine, es_error, ec_type, val.name (), " is repeated");
                ok = false; continue; }
            bs.set (val);
            const flags_t x = val.first ().ext ();
            if ((x & HE_COMBINES) == 0)
                if ((! first) || (enum_vec < E, ENUM, CATEGORY, INIT > :: value_.size () > 1))
                {   nits.pick (nit_not_combine, es_error, ec_type, val.name (), " cannot be combined with any other values");
                    ok = false; }
            const ::std::size_t g = val.first ().group ();
            PRESUME (g <= max_combinable_enum, __FILE__, __LINE__);
            if (g != 0)
                if (! gs.test (g)) gs.set (g);
                else if (! said.test (g))
                {   ::std::string ss;
                    for (auto v2 : enum_vec < E, ENUM, CATEGORY, INIT > :: value_)
                        if (val.first ().group () == g)
                        {   if (! ss.empty ()) ss += ", ";
                            ss += quote (v2.name ()); }
                    nits.pick (nit_not_combine, es_error, ec_type, ss, " are contradictory, so cannot be combined");
                    said.set (g);
                    ok = false; }
            first = false; }
        if (ok) return; }
    enum_vec_base < ENUM, E > :: status (s_invalid); }

template < > struct type_master < t_charsets > : enum_vec < t_charsets, e_charset >
{ using enum_vec < t_charsets, e_charset > :: enum_vec; };

template < > struct type_master < t_class > : enum_vec < t_class, e_class >
{ using enum_vec < t_class, e_class > :: enum_vec; };

template < > struct type_master < t_content_encodings > : enum_vec < t_content_encodings, e_content_encoding >
{ using enum_vec < t_content_encodings, e_content_encoding > :: enum_vec; };

template < > struct type_master < t_font_variant_2s > : enum_constrained_vec < t_font_variant_2s, e_font_variant_2 >
{ using enum_constrained_vec < t_font_variant_2s, e_font_variant_2 > :: enum_constrained_vec; };

template < > struct type_master < t_font_variant_east_asians > : enum_constrained_vec < t_font_variant_east_asians, e_font_variant_east_asian >
{ using enum_constrained_vec < t_font_variant_east_asians, e_font_variant_east_asian > :: enum_constrained_vec; };

template < > struct type_master < t_font_variant_ligatures > : enum_constrained_vec < t_font_variant_ligatures, e_font_variant_ligature >
{ using enum_constrained_vec < t_font_variant_ligatures, e_font_variant_ligature > :: enum_constrained_vec; };

template < > struct type_master < t_font_variant_numerics > : enum_constrained_vec < t_font_variant_numerics, e_font_variant_numeric >
{ using enum_constrained_vec < t_font_variant_numerics, e_font_variant_numeric > :: enum_constrained_vec; };

template < > struct type_master < t_plusstyle > : enum_vec < t_plusstyle, e_plusstyle >
{ using enum_vec < t_plusstyle, e_plusstyle > :: enum_vec; };

template < > struct type_master < t_rel > : enum_vec < t_rel, e_rel >
{ using enum_vec < t_rel, e_rel > :: enum_vec; };

template < > struct type_master < t_svg_features > : enum_vec < t_svg_features, e_svg_feature >
{ using enum_vec < t_svg_features, e_svg_feature > :: enum_vec; };

