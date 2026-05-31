/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

#include "main/standard.h"
#include "css/value.h"
#include "css/flags.h"

void add_param (const arguments& args, t_params& params, int& from, const int i)
{   params.emplace_back (from, i-1);
    from = next_non_whitespace (args.t_, i, -1); }

bool maybe_anchor (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_ANCHOR) == CF_ANCHOR) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_image_3, "2. Anchor Values: the <anchor> type", es_error, ec_css, type_master < t_css_property > :: name (id), ": not an anchor property");
    return false; }

bool maybe_anchor_size (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_ANCHOR_SIZE) == CF_ANCHOR_SIZE) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_image_3, "2. Anchor Values: the <anchor> type", es_error, ec_css, type_master < t_css_property > :: name (id), ": not an anchor-size property");
    return false; }

bool maybe_content (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_generated_content) < 3)
    {   nits.pick (nit_css_version, ed_css_content, "1. Inserting and replacing content with the content property", es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Generated Content");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_CONTENT) == CF_CONTENT) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_content, "1. Inserting and replacing content with the content property", es_error, ec_css, type_master < t_css_property > :: name (id), ": not a content property");
    return false; }

bool maybe_corner (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_CORNER) == CF_CORNER) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_bb_4, "3.7. Corner Shaping: the corner-*-shape properties", es_error, ec_css, type_master < t_css_property > :: name (id), ": not a superellipse corner property");
    return false; }

bool maybe_filter (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_filter_effect) < 3)
    {   nits.pick (nit_css_version, ed_css_filter_3, "6. Filter Functions", es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Filter 3 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FILTER) == CF_FILTER) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_filter_3, "6. Filter Functions", es_error, ec_css, type_master < t_css_property > :: name (id), ": not a filter property");
    return false; }

bool maybe_float (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_page_float) < 3)
    {   nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Page Floats 3 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FLOAT) == CF_FLOAT) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_property > :: name (id), ": not a Page Float property");
    return false; }

bool maybe_image (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_IMAGE) == CF_IMAGE) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_image_3, "2. Image Values: the <image> type", es_error, ec_css, type_master < t_css_property > :: name (id), ": not an image property");
    return false; }

bool maybe_math (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & (CF_EXPECT_STRING | CF_EXPECT_KEYWORDS)) == 0) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_value_4, "10 Mathematical Expressions", es_error, ec_css, type_master < t_css_property > :: name (id), ": not a numeric property");
    return false; }

bool maybe_offset_path (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_motion_path) >= 3) return true;
    nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Motion Path 3 or better");
    return false; }

bool maybe_text_4 (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_text) < 4)
    {   nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Text 4 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_TEXT_4) == CF_TEXT_4) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_property > :: name (id), ": not a CSS Text 4 property (2)");
    return false; }

bool maybe_text_overflow (nitpick& nits, const e_css_property id)
{   if (id <= ec_custom) return true;
    if (context.css_module (c_overflow) < 4)
    {   nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Text Overflow 4 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FADE) == CF_FADE) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, type_master < t_css_property > :: name (id), ": fade() only applies to text-overflow");
    return false; }

bool maybe_transform (nitpick& nits, const e_css_property id, const bool t4)
{   if (id <= ec_custom) return true;
    switch (context.css_module (c_transform))
    {   case 3 :
            if (t4)
            {   nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Transform 4 or better");
                return false; }
            break;
        case 4 :
            break;
        default :
            nits.pick (nit_css_version, es_error, ec_css, type_master < t_css_property > :: name (id), ": requires CSS Transform 3 or better");
            return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_TRANSFORM) == CF_TRANSFORM) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_transform, "9. The Transform Functions", es_error, ec_css, type_master < t_css_property > :: name (id), ": not transform property");
    return false; }

int check_typed_feature (arguments& args, nitpick& nits, const int start, const int to, const e_css_statement cs, const char* const sz)
{   ::std::string name (assemble_string (args.t_, start, to, true));
    if (name.empty ()) return to;
    if (args.has_font_feature (cs, name)) return to;
    if (name.find_first_not_of (DENARY) == ::std::string::npos) return to;
    else nits.pick (nit_css_font_feature, es_error, ec_css, quote (name), ": unknown @", sz);
    return start; }

int test_value_fns (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
#ifdef LIMITED_META_COMPLEXITY
{   int test_value_fns_0_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_2_9 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_b_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_b_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_a_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_a_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_a_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_d (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_e (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_f_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_f_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_f_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_fn_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_fn_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_g_h (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_i_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_i_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_j_k (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_l_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_l_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_l_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_m_n (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_o (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_p_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_p_q (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_r_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_r_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_s_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_s_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_s_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_u (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_v (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_w_z (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_d_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_d_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_e (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_f_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_f_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_f_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_g (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_h (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_i_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_i_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_i_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_j_k (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_l_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_l_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_l_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_6 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_n (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_o (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_r_6 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_3 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_4 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_5 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s_6 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_t_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_t_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_u_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_u_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_v_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_v_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_w (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_x_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_x_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_y_z (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);

    if (t <= SSC_TYPES_0_1_MAX) return test_value_fns_0_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_2_9_MAX) return test_value_fns_2_9 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_1_MAX) return test_value_fns_a_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_2_MAX) return test_value_fns_a_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_3_MAX) return test_value_fns_a_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_4_MAX) return test_value_fns_a_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_5_MAX) return test_value_fns_a_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_B_1_MAX) return test_value_fns_b_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_B_2_MAX) return test_value_fns_b_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_1_MAX) return test_value_fns_c_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_2_MAX) return test_value_fns_c_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_3_MAX) return test_value_fns_c_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_4_MAX) return test_value_fns_c_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_5_MAX) return test_value_fns_c_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_A_1_MAX) return test_value_fns_css_a_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_A_2_MAX) return test_value_fns_css_a_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_A_3_MAX) return test_value_fns_css_a_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_1_MAX) return test_value_fns_css_b_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_2_MAX) return test_value_fns_css_b_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_3_MAX) return test_value_fns_css_b_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_4_MAX) return test_value_fns_css_b_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_1_MAX) return test_value_fns_css_c_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_2_MAX) return test_value_fns_css_c_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_3_MAX) return test_value_fns_css_c_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_4_MAX) return test_value_fns_css_c_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_5_MAX) return test_value_fns_css_c_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_D_MAX) return test_value_fns_css_d (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_E_MAX) return test_value_fns_css_e (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_F_1_MAX) return test_value_fns_css_f_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_F_2_MAX) return test_value_fns_css_f_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_F_3_MAX) return test_value_fns_css_f_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_FN_1_MAX) return test_value_fns_css_fn_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_FN_2_MAX) return test_value_fns_css_fn_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_G_H_MAX) return test_value_fns_css_g_h (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_I_1_MAX) return test_value_fns_css_i_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_I_2_MAX) return test_value_fns_css_i_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_J_K_MAX) return test_value_fns_css_j_k (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_L_1_MAX) return test_value_fns_css_l_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_L_2_MAX) return test_value_fns_css_l_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_L_3_MAX) return test_value_fns_css_l_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_M_N_MAX) return test_value_fns_css_m_n (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_O_MAX) return test_value_fns_css_o (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_P_1_MAX) return test_value_fns_css_p_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_P_Q_MAX) return test_value_fns_css_p_q (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_R_1_MAX) return test_value_fns_css_r_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_R_2_MAX) return test_value_fns_css_r_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_S_1_MAX) return test_value_fns_css_s_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_S_2_MAX) return test_value_fns_css_s_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_S_3_MAX) return test_value_fns_css_s_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_1_MAX) return test_value_fns_css_t_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_2_MAX) return test_value_fns_css_t_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_3_MAX) return test_value_fns_css_t_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_4_MAX) return test_value_fns_css_t_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_U_MAX) return test_value_fns_css_u (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_V_MAX) return test_value_fns_css_v (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_W_Z_MAX) return test_value_fns_css_w_z (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_D_1_MAX) return test_value_fns_d_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_D_2_MAX) return test_value_fns_d_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_E_MAX) return test_value_fns_e (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_F_1_MAX) return test_value_fns_f_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_F_2_MAX) return test_value_fns_f_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_F_3_MAX) return test_value_fns_f_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_G_MAX) return test_value_fns_g (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_H_MAX) return test_value_fns_h (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_I_1_MAX) return test_value_fns_i_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_I_2_MAX) return test_value_fns_i_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_I_3_MAX) return test_value_fns_i_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_J_K_MAX) return test_value_fns_j_k (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_L_1_MAX) return test_value_fns_l_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_L_2_MAX) return test_value_fns_l_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_L_3_MAX) return test_value_fns_l_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_1_MAX) return test_value_fns_m_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_2_MAX) return test_value_fns_m_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_3_MAX) return test_value_fns_m_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_4_MAX) return test_value_fns_m_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_5_MAX) return test_value_fns_m_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_6_MAX) return test_value_fns_m_6 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_N_MAX) return test_value_fns_n (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_O_MAX) return test_value_fns_o (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_1_MAX) return test_value_fns_p_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_2_MAX) return test_value_fns_p_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_3_MAX) return test_value_fns_p_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_4_MAX) return test_value_fns_p_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_1_MAX) return test_value_fns_r_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_2_MAX) return test_value_fns_r_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_3_MAX) return test_value_fns_r_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_4_MAX) return test_value_fns_r_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_5_MAX) return test_value_fns_r_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_R_6_MAX) return test_value_fns_r_6 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_1_MAX) return test_value_fns_s_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_2_MAX) return test_value_fns_s_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_3_MAX) return test_value_fns_s_3 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_4_MAX) return test_value_fns_s_4 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_5_MAX) return test_value_fns_s_5 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_6_MAX) return test_value_fns_s_6 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_T_1_MAX) return test_value_fns_t_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_T_2_MAX) return test_value_fns_t_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_U_1_MAX) return test_value_fns_u_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_U_2_MAX) return test_value_fns_u_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_V_1_MAX) return test_value_fns_v_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_V_1_MAX) return test_value_fns_v_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_W_MAX) return test_value_fns_w (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_X_1_MAX) return test_value_fns_x_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_X_1_MAX) return test_value_fns_x_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_Y_Z_MAX) return test_value_fns_y_z (args, start, to, nits, t, fn, id);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
{   return value_types < SSC_TYPES, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#endif // LIMITED_META_COMPLEXITY 
