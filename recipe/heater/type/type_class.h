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
#include "type/type_enum_vec.h"

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
inline bool is_whatwg_class (const e_class c) { return (c >= first_jun07_class) && (c <= last_jun07_class); }
const ::std::size_t class_size = static_cast < ::std::size_t > (c_error + 1);
const ::std::size_t vocab_size = static_cast < ::std::size_t > (h_aggregate + 1);  // not last minus first because of c_context etc.

bool check_class_spelling (nitpick& nits, const html_version& v, const ::std::string& original);

template < > inline void enum_n < t_class, e_class > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_base < e_class, t_class > :: original_ = s;
    if (symbol < e_class > :: parse (nits, v, s, enum_base < e_class, t_class > :: value_)) enum_base < e_class, t_class > :: status (s_good);
    else enum_n < t_class, e_class > :: status (s_invalid); }

template < > inline void enum_vec < t_class, e_class > :: set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   enum_vec_base < e_class, t_class > :: original_ = ss;
    bool res = true; vstr_t strs;
    ::std::string sss (trim_the_lot_off (ss));
    ::boost::algorithm::split (strs, sss, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    if (strs.size () == 0)
    {   enum_vec_base < e_class, t_class > :: status (s_empty); return; }
    for (auto s : strs)
    {   enum_vec_base < e_class, t_class > :: base_t t;
        t.set_value (nits, v, s);
        if (is_whatwg_class (t.get ()))
        {   nits.pick (nit_whatwg_class, ed_jan07, "3.4.5. Classes", es_comment, ec_attribute, "FYI, ", quote (s), " was a draft HTML 5 standard class name.");
            if ((v.mjr () != HTML_2007) || (v.mnr () >= HTML_JUL)) t.status (s_invalid); }
        if (t.invalid ())
            if (context.css ().note_usage (s))
            {   nits.pick (nit_spotted_css_class, es_comment, ec_css, "CSS class ", quote (s), " recognised");
                t.status (s_good); }
            else
            {   res = false;
                if (! check_class_spelling (nits, v, s))
                    nits.pick (nit_unrecognised_value, es_warning, ec_type, quote (s), " is unknown"); }
        enum_vec_base < e_class, t_class > :: value_.push_back (t); }
    if (res) type_base < e_class, t_class > :: status (s_good);
    else type_base < e_class, t_class > :: status (s_invalid); }

struct html_class : enum_n < t_class, e_class >
{   typedef enum_n < t_class, e_class > :: value_type value_type;
    html_class () = default;
    html_class (const html_class& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    html_class (html_class&& ) = default;
#endif
    explicit html_class (nitpick& nits, const html_version& v, const ::std::string& s)
    {   enum_n < t_class, e_class > :: set_value (nits, v, s); }
    ~html_class () = default;
    html_class& operator = (const html_class& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    html_class& operator = (html_class&& ) = default;
#endif
    static bool is_microformat_property (const e_class value)
    {   return value >= first_mf1_property && value <= last_mf2_property; }
    static bool is_microformat_vocabulary (const e_class value)
    {   return value >= first_mf1_vocab && value <= last_mf2_vocab; }
    static bool is_microformat (const e_class value)
    {   return value >= first_mf1_vocab && value <= last_mf2_property; }
    static bool is_microformat_v1 (const e_class value)
    {   return (value >= first_mf1_vocab && value <= last_mf1_vocab) || (value >= first_mf1_property && value <= last_mf1_property); }
    static bool is_microformat_v2 (const e_class value)
    {   return (value >= first_mf2_vocab && value <= last_mf2_vocab) || (value >= first_mf2_property && value <= last_mf2_property); }
    static bool is_whatwg_draft (const e_class value)
    {   return is_whatwg_class (value); }
    CONSTEXPR static bool is_rel () { return false; }
    bool is_microformat_property () const { return is_microformat_property (enum_base < e_class, t_class >  :: value_); }
    bool is_microformat_vocabulary () const { return is_microformat_vocabulary (enum_base < e_class, t_class > :: value_); }
    bool is_microformat () const { return is_microformat (enum_base < e_class, t_class > :: value_); }
    bool is_microformat_v1 () const { return is_microformat_v1 (enum_base < e_class, t_class > :: value_ ); }
    bool is_microformat_v2 () const { return is_microformat_v2 (enum_base < e_class, t_class > :: value_); }
    bool is_whatwg_draft () const { return is_whatwg_class (enum_base < e_class, t_class > :: value_); } };

typedef  ::std::vector < html_class > vhc_t;
