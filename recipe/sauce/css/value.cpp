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

#include "main/standard.h"
#include "css/value.h"
#include "css/flags.h"

void add_param (const arguments& args, t_params& params, int& from, const int i)
{   params.emplace_back (from, i-1);
    from = next_non_whitespace (args.t_, i, -1); }

bool maybe_content (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_content () < 3)
    {   nits.pick (nit_css_version, ed_css_content, "1. Inserting and replacing content with the content property", es_error, ec_css, "Requires CSS Generated Content");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_CONTENT) == CF_CONTENT) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_content, "1. Inserting and replacing content with the content property", es_error, ec_css, "not a content property");
    return false; }

bool maybe_filter (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_filter () < 3)
    {   nits.pick (nit_css_version, ed_css_filter_3, "6. Filter Functions", es_error, ec_css, "Requires CSS Filter 3 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FILTER) == CF_FILTER) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_filter_3, "6. Filter Functions", es_error, ec_css, "not a filter property");
    return false; }

bool maybe_float (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_float () < 3)
    {   nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Page Floats 3 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FLOAT) == CF_FLOAT) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, "not a Page Float property");
    return false; }

bool maybe_image (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_IMAGE) == CF_IMAGE) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_image_3, "2. Image Values: the <image> type", es_error, ec_css, "not an image property");
    return false; }

bool maybe_math (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & (CF_EXPECT_STRING | CF_EXPECT_KEYWORDS)) == 0) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_value_4, "10 Mathematical Expressions", es_error, ec_css, "not a numeric property");
    return false; }

bool maybe_offset_path (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_motion () < 3)
    {   nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Motion Path 3 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_TEXT_4) == CF_TEXT_4) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, "not a CSS Text 4 property");
    return false; }

bool maybe_text_4 (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_text () < 4)
    {   nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Text 4 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_TEXT_4) == CF_TEXT_4) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, "not a CSS Text 4 property");
    return false; }

bool maybe_text_overflow (nitpick& nits, const e_css_property id)
{   if (id < ec_custom) return true;
    if (context.css_overflow () < 4)
    {   nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Text Overflow 4 or better");
        return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_FADE) == CF_FADE) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, es_error, ec_css, "fade() only applies to text-overflow");
    return false; }

bool maybe_transform (nitpick& nits, const e_css_property id, const bool t4)
{   if (id < ec_custom) return true;
    switch (context.css_transform ())
    {   case 3 :
            if (t4)
            {   nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Transform 4 or better");
                return false; }
            break;
        case 4 :
            break;
        default :
            nits.pick (nit_css_version, es_error, ec_css, "Requires CSS Transform 3 or better");
            return false; }
    const flags_t f (enum_n < t_css_property, e_css_property > :: flags (id));
    if ((f & CF_TRANSFORM) == CF_TRANSFORM) return true;
    if (! test_esii (sii_hush, HIDE_ME))
        nits.pick (nit_css_value_fn, ed_css_transform_3, "9. The Transform Functions", es_error, ec_css, "not transform property");
    return false; }

int check_typed_feature (arguments& args, nitpick& nits, const int start, const int to, const e_css_statement cs, const char* const sz)
{   ::std::string name (assemble_string (args.t_, start, to, true));
    if (name.empty ()) return to;
//    if (args.font_feature (cs).find (name) != args.font_feature (cs).cend ()) return to;
    if (args.has_font_feature (cs, name)) return to;
    if (name.find_first_not_of (DENARY) == ::std::string::npos) return to;
    else nits.pick (nit_css_font_feature, es_error, ec_css, quote (name), ": unknown @", sz);
    return start; }

int test_value_fns (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
#ifdef LIMITED_META_COMPLEXITY
{   int test_value_fns_0_9 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_a (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_b (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_c (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_a (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_b_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_c_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_d_e (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_f_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_f_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_g_i (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_j_l (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_m_n (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_o_p (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_r (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_s (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_t_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_css_u_z (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_d_e (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_f (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_g_h (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_i (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_j_l (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_m_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_n_o (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_1 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_p_2 (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_q_r (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_s (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_svg (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_t (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_u (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_v_w (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);
    int test_value_fns_x_z (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id);

    if (t <= SSC_TYPES_0_9_MAX) return test_value_fns_0_9 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_A_MAX) return test_value_fns_a (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_B_MAX) return test_value_fns_b (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_C_MAX) return test_value_fns_c (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_A_MAX) return test_value_fns_css_a (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_1_MAX) return test_value_fns_css_b_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_B_2_MAX) return test_value_fns_css_b_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_1_MAX) return test_value_fns_css_c_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_C_2_MAX) return test_value_fns_css_c_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_D_E_MAX) return test_value_fns_css_d_e (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_F_1_MAX) return test_value_fns_css_f_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_F_2_MAX) return test_value_fns_css_f_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_G_I_MAX) return test_value_fns_css_g_i (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_J_L_MAX) return test_value_fns_css_j_l (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_M_N_MAX) return test_value_fns_css_m_n (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_O_P_MAX) return test_value_fns_css_o_p (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_R_MAX) return test_value_fns_css_r (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_S_MAX) return test_value_fns_css_s (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_1_MAX) return test_value_fns_css_t_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_T_2_MAX) return test_value_fns_css_t_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_CSS_U_Z_MAX) return test_value_fns_css_u_z (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_D_E_MAX) return test_value_fns_d_e (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_F_MAX) return test_value_fns_f (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_G_H_MAX) return test_value_fns_g_h (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_I_MAX) return test_value_fns_i (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_J_L_MAX) return test_value_fns_j_l (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_1_MAX) return test_value_fns_m_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_M_2_MAX) return test_value_fns_m_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_N_O_MAX) return test_value_fns_n_o (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_1_MAX) return test_value_fns_p_1 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_P_2_MAX) return test_value_fns_p_2 (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_Q_R_MAX) return test_value_fns_q_r (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_S_MAX) return test_value_fns_s (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_SVG_MAX) return test_value_fns_svg (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_T_MAX) return test_value_fns_t (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_U_MAX) return test_value_fns_u (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_V_W_MAX) return test_value_fns_v_w (args, start, to, nits, t, fn, id);
    if (t <= SSC_TYPES_X_Z_MAX) return test_value_fns_x_z (args, start, to, nits, t, fn, id);
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#else // LIMITED_META_COMPLEXITY
{   return value_types < SSC_TYPES, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#endif // LIMITED_META_COMPLEXITY 
