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
#include "enum/type_enum_vec.h"

const e_class first_mf1_vocab = h1_aggregate;
const e_class last_mf1_vocab = h1_xoxo;
const e_class first_mf2_vocab = h_adr;
const e_class last_mf2_vocab = h_aggregate;
const e_class first_mf1_property = mf1_additional_name;
const e_class last_mf1_property = mf1_website;
const e_class first_mf2_property = dt_accessed;
const e_class last_mf2_property = u_search;
const e_class first_jun07_class = h5d_copyright;
const e_class last_jun07_class = h5d_warning;
inline CONSTEXPR bool is_whatwg_class (const e_class c) { return (c >= first_jun07_class) && (c <= last_jun07_class); }
CONSTEXPR ::std::size_t class_size = static_cast < ::std::size_t > (c_error + 1);
CONSTEXPR ::std::size_t vocab_size = static_cast < ::std::size_t > (h_aggregate + 1);  // not last minus first because of c_context etc.

bool check_class_spelling (nitpick& nits, const html_version& v, const ::std::string& original);
bool note_class_usage (element* p, const ::std::string& s);

template < > inline void enum_n < t_class, e_class > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_base < e_class, t_class > :: original_ = s;
    if (symbol < html_version, e_class > :: parse (nits, v, s, enum_base < e_class, t_class > :: value_)) enum_base < e_class, t_class > :: status (s_good);
    else enum_n < t_class, e_class > :: status (s_invalid); }

template < > inline void enum_vec < t_class, e_class > :: accumulate (stats_t* st, const e_element e) const
{   VERIFY_NOT_NULL (st, __FILE__, __LINE__);
    for (auto v : enum_vec_base < e_class, t_class > :: originals_)
    {   st -> use_class (v);
        st -> use_element_class (elem::name (e) + "." + v); } }

template < > inline void enum_vec < t_class, e_class > :: accumulate (stats_t* st, const element_bitset& e) const
{   VERIFY_NOT_NULL (st, __FILE__, __LINE__);
    for (auto v : enum_vec_base < e_class, t_class > :: originals_)
    {   st -> use_class (v);
        for (::std::size_t i = elem_css_all; i < last_element_tag; ++i)
            if (e.test (i))
                st -> use_element_class (elem::name (::gsl::narrow_cast < e_element > (i)) + "." + v); } }

template < > inline void enum_vec < t_class, e_class > :: set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   enum_vec_base < e_class, t_class > :: original_ = ss;
    vstr_t strs;
    ::std::string sss (trim_the_lot_off (ss));
    ::boost::algorithm::split (strs, sss, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    if (strs.size () == 0)
    {   enum_vec_base < e_class, t_class > :: status (s_empty); return; }
    for (auto s : strs)
    {   enum_vec_base < e_class, t_class > :: base_t t (enum_vec_base < e_class, t_class > :: box ());
        t.set_value (nits, v, s);
        VERIFY_NOT_NULL (box (), __FILE__, __LINE__);
        if (is_whatwg_class (t.get ()))
        {   nits.pick (nit_whatwg_class, ed_jan07, "3.4.5. Classes", es_comment, ec_attribute, "FYI, ", quote (s), " was a standard class name in some early drafts of HTML 5.");
            if ((v.mjr () != HTML_2007) || (v.mnr () >= HTML_JUL)) t.status (s_invalid); }
        if (t.invalid ())
        {   if (context.unknown_class ())
                if (note_class_usage (box (), s))
                    nits.pick (nit_spotted_css_class, es_comment, ec_css, "CSS class ", quote (s), " recognised");
                else if (! check_class_spelling (nits, v, s))
                    nits.pick (nit_unrecognised_value, es_warning, ec_type, quote (s), " is unknown");
            t.status (s_good); }
        enum_vec_base < e_class, t_class > :: originals_.push_back (s);
        enum_vec_base < e_class, t_class > :: value_.push_back (t); }
    type_base < e_class, t_class > :: status (s_good); }

struct html_class : enum_n < t_class, e_class >
{   using enum_n < t_class, e_class > :: enum_n;
    typedef enum_n < t_class, e_class > :: value_type value_type;
    explicit html_class (nitpick& nits, const html_version& v, const ::std::string& s)
    {   enum_n < t_class, e_class > :: set_value (nits, v, s); }
    CONSTEXPR static bool is_microformat_property (const e_class value) noexcept
    {   return value >= first_mf1_property && value <= last_mf2_property; }
    CONSTEXPR static bool is_microformat_vocabulary (const e_class value) noexcept
    {   return value >= first_mf1_vocab && value <= last_mf2_vocab; }
    CONSTEXPR static bool is_microformat (const e_class value) noexcept
    {   return value >= first_mf1_vocab && value <= last_mf2_property; }
    CONSTEXPR static bool is_microformat_v1 (const e_class value) noexcept
    {   return (value >= first_mf1_vocab && value <= last_mf1_vocab) || (value >= first_mf1_property && value <= last_mf1_property); }
    CONSTEXPR static bool is_microformat_v2 (const e_class value) noexcept
    {   return (value >= first_mf2_vocab && value <= last_mf2_vocab) || (value >= first_mf2_property && value <= last_mf2_property); }
    CONSTEXPR static bool is_whatwg_draft (const e_class value)
    {   return is_whatwg_class (value); }
    CONSTEXPR static bool is_rel () { return false; }
    bool is_microformat_property () const noexcept { return is_microformat_property (enum_base < e_class, t_class >  :: value_); }
    bool is_microformat_vocabulary () const noexcept { return is_microformat_vocabulary (enum_base < e_class, t_class > :: value_); }
    bool is_microformat () const noexcept { return is_microformat (enum_base < e_class, t_class > :: value_); }
    bool is_microformat_v1 () const noexcept { return is_microformat_v1 (enum_base < e_class, t_class > :: value_ ); }
    bool is_microformat_v2 () const noexcept { return is_microformat_v2 (enum_base < e_class, t_class > :: value_); }
    bool is_whatwg_draft () const { return is_whatwg_class (enum_base < e_class, t_class > :: value_); } };

typedef  ::std::vector < html_class > vhc_t;