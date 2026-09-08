/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "parser/html_version.h"
#include "type/type.h"
#include "webpage/page.h"
#include "element/element.h"
#include "css/arguments.h"
#include "parser/text.h"

struct type_cvf
{   e_type type_ = t_error;
    e_css_val_fn cvf_ = cvf_none; };

type_cvf a_tc [] =
{   { t_css_fn_anchor, cvf_anchor },
    { t_css_fn_anchor_size, cvf_anchor_size },
    { t_css_fn_anchored, cvf_anchored },
    { t_css_fn_annotation, cvf_annotation },
    { t_css_fn_attr, cvf_attr },
    { t_css_fn_calc, cvf_calc },
    { t_css_fn_calc_size, cvf_calc_size },
    { t_css_fn_character_variant, cvf_character_variant },
    { t_css_fn_conic_gradient, cvf_conic_gradient },
    { t_css_fn_repeating_conic_gradient, cvf_repeating_conic_gradient },
    { t_css_fn_counter, cvf_counter },
    { t_css_fn_counters, cvf_counters },
    { t_css_fn_cross_fade, cvf_cross_fade },
    { t_css_fn_cross_fade, cvf_cross_fade },
    { t_css_fn_cubic_bezier, cvf_cubic_bezier },
    { t_css_fn_custom, cvf_custom },
    { t_css_fn_dylm, cvf_dynamic_range_limit_mix },
    { t_css_fn_element, cvf_element },
    { t_css_fn_fit_content, cvf_fit_content },
    { t_css_fn_if, cvf_if },
    { t_css_fn_if_media, cvf_media },
    { t_css_fn_if_style, cvf_style },
    { t_css_fn_if_supports, cvf_supports },
    { t_css_fn_image, cvf_image },
    { t_css_fn_image_set, cvf_image_set },
    { t_css_fn_inset, cvf_inset },
    { t_css_fn_keypress, cvf_keypress },
    { t_css_fn_linear, cvf_linear },
    { t_css_fn_linear_gradient, cvf_linear_gradient },
    { t_css_fn_minmax, cvf_minmax },
    { t_css_fn_mix, cvf_mix },
    { t_css_fn_moz_image_rect, cvf_moz_image_rect },
    { t_css_fn_ornaments, cvf_ornaments },
    { t_css_fn_param, cvf_param },
    { t_css_fn_radial_gradient, cvf_radial_gradient },
    { t_css_fn_ray, cvf_ray },
    { t_css_fn_rect, cvf_rect },
    { t_css_fn_repeat, cvf_repeat },
    { t_css_fn_repeating_linear_gradient, cvf_linear_gradient },
    { t_css_fn_repeating_radial_gradient, cvf_repeating_radial_gradient },
    { t_css_fn_round_t, cvf_round },
    { t_css_fn_shape, cvf_shape },
    { t_css_fn_snap_block, cvf_snap_block },
    { t_css_fn_snap_inline, cvf_snap_inline },
    { t_css_fn_steps, cvf_steps },
    { t_css_fn_styleset, cvf_styleset },
    { t_css_fn_stylistic, cvf_stylistic },
    { t_css_fn_superellipse, cvf_superellipse },
    { t_css_fn_swash, cvf_swash },
    { t_css_fn_type, cvf_type },
    // { t_urifn, cvf_url },
    { t_css_fn_url_pattern, cvf_url_pattern },
    { t_css_fn_var, cvf_var },
    { t_css_fn_wcag2, cvf_wcag2 },
    { t_css_fn_xywh, cvf_xywh },
    { t_hslafn, cvf_hsla },
    { t_hslfn, cvf_hsl },
    //{ t_hslfn4, cvf_hsl },
    { t_error, cvf_none } };

typedef ssc_map < e_css_val_fn, e_type > m_cvf_t;
static m_cvf_t mct;

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e)
{   try
    {   if (e == nullptr)
            nits.pick (nit_css_syntax, es_catastrophic, ec_type, "null element processing STYLE");
        else
        {   page& p = e -> get_page ();
            if (! p.style_css ())
                nits.pick (nit_style_not_css, es_comment, ec_type, PROG " can only check style type " CSS_TYPE);
            else if (context.load_css () && (context.css_version () >= css_1))
                p.css ().parse (s, v, e -> namespaces (), e -> ancestral_elements (), false, e -> line (), e -> tag ()); } }
    catch (const ::std::system_error& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "system exception processing STYLE: ", ex.what ()); }
    catch (const ::std::exception& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "exception processing STYLE: ", ex.what ()); }
    catch (...)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "unknown exception processing STYLE"); }
    return nits.worst () < es_warning; }

e_status set_css_all_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! compare_no_case (s, "all"))
    {   if (v.css_version () == css_2_0)
            nits.pick (nit_unrecognised_value, es_comment, ec_type, quote (s), ": is not 'all'"); }
    else if (v.css_version () != css_2_0)
        nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'all' requires CSS 2.0 (only)");
    else return s_good;
    return s_invalid; }

e_status set_css_content_name_value (nitpick& , const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    g.note_str (gst_content_name, s);
    return s_good; }

e_status set_css_font_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   if (sss.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font specification cannot be empty");
    else
    {   nitpick gnats;
        ::std::string gs (sss);
        if (test_value < t_font_enum > (gnats, v, gs))
        {   nits.merge (gnats);
            return s_good; }
        vstr_t ss (split_by_comma_space (gs));
        PRESUME (! ss.empty (), __FILE__, __LINE__);
        bool res = true;
        typedef enum { fs_style, fs_variant, fs_weight, fs_size, fs_family, fs_done } font_state;
        font_state state = fs_style;
        for (auto s : ss)
        {   nitpick nuts, knits;
            ::std::string::size_type pos = ::std::string::npos;
            if (test_value < t_font_enum > (nuts, v, s))
            {   nits.merge (nuts);
                if (ss.size () > 1)
                {   nits.pick (nit_font_enum, es_error, ec_type, quote (s), " cannot be combined with other values");
                    res = false; break; } }
            else switch (state)
            {   case fs_style :
                    if (test_value < t_css_font_style_a > (knits, v, s))
                    {   state = fs_variant; break; }
                    FALLTHROUGH;
                case fs_variant :
                    if (test_value < t_svg_fontvariant > (knits, v, s))
                    {   state = fs_weight; break; }
                    FALLTHROUGH;
                case fs_weight :
                    if (test_value < t_css_font_weights > (knits, v, s))
                    {   state = fs_size; break; }
                    FALLTHROUGH;
                case fs_size :
                    pos = s.find ('/');
                    if (pos == ::std::string::npos)
                    {   if (test_value < t_fontsize > (knits, v, s))
                        {   state = fs_family; break; }
                        if (v.has_css () && test_value < t_css_font_size_4 > (knits, v, s))
                        {   state = fs_family; break; } }
                    else if (test_value < t_fontsize > (knits, v, s.substr (0, pos)) &&
                                test_value < t_measure > (knits, v, s.substr (pos)))
                    {   state = fs_family; break; }
                    else if (v.has_css () && 
                                test_value < t_css_font_size_4 > (knits, v, s.substr (0, pos)) &&
                                test_value < t_measure > (knits, v, s.substr (pos)))
                    {   state = fs_family; break; }
                    FALLTHROUGH;
                case fs_family :
                    if (test_value < t_font_family > (knits, v, s))
                    {   if (! v.has_css ()) state = fs_done;
                        break; }
                    if (v.has_css () && test_value < t_css_generic_family > (knits, v, s))
                        break;
                    FALLTHROUGH;
                default :
                    nits.pick (nit_font_enum, es_error, ec_type, quote (s), " is not a known CSS FONT property");
                    res = false; break; }
            if (! res) break; }
        if (res) return s_good; }
    return s_invalid; }

e_status set_css_font_stretch_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "font-stretch cannot be empty");
    else
    {   nitpick nuts;
        if (v >= html_dec25)
            nits.pick (nit_deprecated, es_warning, ec_css, "font-stretch has been replaced by font-width");
        if (context.css_module (c_font) >= 4)
            if (test_value < t_percentish > (nuts, v, s))
            {   nits.merge (nuts);
                return s_good; }
        if (test_value < t_svg_fontstretch > (nits, v, s)) return s_good;
        nits.merge (nuts); }
    return s_invalid; }

e_status set_css_font_variant_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font variant cannot be empty");
    else
    {   if (context.css_module (c_font) >= 4)
        {   if (test_value < t_css_font_variant_4 > (nits, v, s)) return s_good; }
        if (context.css_module (c_font) == 3)
        {   if (test_value < t_font_variant_2 > (nits, v, s)) return s_good; }
        else if (test_value < t_svg_fontvariant > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_font_weights_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font weight cannot be empty");
    else
    {   if (context.css_module (c_font) >= 4)
        {   if (test_value < t_css_font_weight_4 > (nits, v, s)) return s_good; }
        else if (test_value < t_css_font_weight > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_frame_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a frame name cannot be empty");
    else
    {   if (s.at (0) != '_') return s_good;
        if (compare_no_case (s, "_parent") || compare_no_case (s, "_root")) return s_good;
        nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "to quote, a frame name 'MUST NOT start with the underscore \"_\" character'"); }
    return s_invalid; }

e_status set_css_id_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a id cannot be empty");
    else
    {   if (s.at (0) == '#') return s_good;
        nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "An id selector is expected, which starts with '#'"); }
    return s_invalid; }

e_status set_css_inherit_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! compare_no_case (s, "inherit"))
    {   if (v.css_version () >= css_2_0)
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), ": is not 'inherit'"); }
    else if (v.css_version () < css_2_0)
        nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'inherit' requires CSS 2.0 or later");
    else return s_good;
    return s_invalid; }

e_status set_css_nth_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, "pseudo class children specification cannot be empty");
    else if (s.find_first_not_of (DENARY "+-nN ") != ::std::string::npos)
        nits.pick (nit_css_syntax, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, quote (s), " contains invalid characters");
    else return s_good; // maybe do more checking!
     return s_invalid; }

e_status set_css_unicode_from_to_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
    else
    {   const ::std::size_t len = s.length ();
        if ((len <= 2) || (s.at (1) != '+') || ((s.at (0) != 'U') && (s.at (0) != 'u')))
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": must start with 'U+'");
        else if (len > 18)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": too big");
        else if (s.substr (2).find_first_not_of (HEX "-") != ::std::string::npos) 
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": not hexadecimal");
        else
        {   const ::std::string::size_type minus = s.find_first_of ("-");
            if ((minus < 3) || (minus >= len-1)) 
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": is not a pair of hexadecimal values"); 
            else if (s.substr (minus+1).find ('-') != ::std::string::npos)
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": bad hexadecimal range"); 
            else return s_good; } }
    return s_invalid; }

e_status set_css_unicode_wildcard_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
    else
    {   const ::std::size_t len = s.length ();
        if ((len <= 2) || (s.at (1) != '+') || ((s.at (0) != 'U') && (s.at (0) != 'u')))
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": must start with 'U+'");
        else if (s.substr (2).find_first_not_of (HEX "?") != ::std::string::npos)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": not hexadecimal with wildcards");
        else if (len > 10)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": too big");
        else return s_good; }
    return s_invalid; }

template < e_type TYPE, e_type... TYPES > struct fn_by_type : public fn_by_type < TYPES... >
{   static e_status check (const e_type e, nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (e != TYPE) return fn_by_type < TYPES... > :: check (e, nits, v, s);
        type_master < TYPE > t;
        t.set_value (nits, v, s);
        return t.status (); } };

template < e_type TYPE > struct fn_by_type < TYPE >
{   static e_status check (const e_type e, nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < TYPE > t;
        if (e != TYPE) return s_invalid;
        t.set_value (nits, v, s);
        return t.status (); } };

bool set_calc_ex (nitpick& nits, const html_version& v, char ch, e_status& st, ::std::string& n, bool& had_op, bool is_op = false)
{   if (! n.empty ())
        if (n != "-")
            if (is_op || (ch <= ' '))
                if (! test_value < t_css_calc_value > (nits, v, n))
                    st = s_invalid;
    if ((n == "-") || is_op)
        switch (ch)
        {   case '+' :
            case '-' :
            case '*' :
            case '/' :
                nits.pick (nit_css_type, ed_mdn, "calc ()", es_error, ec_css, quote (ch), ": after ", quote (n), " is wrong");
                st = s_invalid;
                had_op = true;
                break;
            case ')' :
                break;
            case '(' :
                return true;
            default :
                if (! is_op)
                    if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')) || (ch == '_') || (ch == '-'))
                    {   had_op = false; n += ch; break; }
                if (ch <= ' ') break;
                nits.pick (nit_css_type, ed_mdn, "calc ()", es_error, ec_css, quote (ch), ": unexpected (39)");
                st = s_invalid;
                break; }
    else
        switch (ch)
        {   case '+' :
            case '-' :
            case '*' :
            case '/' :
                had_op = true;
                n.clear ();
                break;
            case '%' :
            case ')' :
                break;
            case '(' :
                return true;
            default :
                if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')) || (ch == '_') || (ch == '-') || (ch == '.'))
                {   had_op = false; n += ch; break; }
                n.clear ();
                if (ch <= ' ') break;
                nits.pick (nit_css_type, ed_mdn, "calc ()", es_error, ec_css, quote (ch), ": unexpected (40)");
                st = s_invalid;
                break; }
    if (is_op) n.clear ();
    return false; } 

e_status set_fn_calc_args_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   if (ss.empty ()) return s_good;
    nitpick gnats;
    bool had_op = true;
    int rounds = 0, fn = -1;
    e_status st = s_good;
    e_css_val_fn cvf = cvf_none;
    ::std::string n, fnn, fna;
    for (auto s : ss)
    {   switch (s)
        {   case '(' :
                ++rounds;
                if (fn >= 0) { fna += s; continue; }
                fnn = n;
                if (set_calc_ex (nits, v, s, st, n, had_op, true))
                {   fn = rounds; n.clear (); fna.clear ();
                    if (! fnn.empty ()) cvf = examine_value < t_css_val_fn > (nits, v, fnn);
                    continue; }
                break;
            case ')' :
                set_calc_ex (nits, v, s, st, n, had_op, true);
                if (fn > rounds) fna += s;
                else if (fn == rounds)
                    if (! fnn.empty ())
                    {   if (cvf > cvf_none)
                        {   if ((type_master < t_css_val_fn > :: flags (cvf) & CF_CALC) == 0)
                                nits.pick (nit_css_type, ed_mdn, "functions", es_warning, ec_css, quote (fnn), ": may be unsuitable here");
                            if (mct.empty ())
                                for (int i = 0; GSL_AT (a_tc, i).type_ != t_error; ++i)
                                    mct.insert (m_cvf_t::value_type (GSL_AT (a_tc, i).cvf_, GSL_AT (a_tc, i).type_));
                            auto t = mct.find (cvf);
                            if (t == mct.cend ())
                            {   nits.pick (nit_css_type, ed_mdn, "functions", es_warning, ec_css, "cannot convert ", fnn, " to internal type"); 
                                st = s_invalid; }
                            else fn_by_type < SSC_TYPES_CSS_FN_1, SSC_TYPES_CSS_FN_2, SSC_TYPES_CSS_FN_3, t_error > :: check (t -> second, nits, v, fna); }
                        fnn.clear ();
                        n.clear (); }
                if (rounds == 0)
                {   nits.pick (nit_css_type, ed_mdn, "functions", es_error, ec_css, quote (ss), ": is a '(' missing?");
                    st = s_invalid; }
                else --rounds;
                break;
            default :
                if (fn >= 0) { fna += s; continue; }
                set_calc_ex (nits, v, s, st, n, had_op);
                break; } }
    if (rounds > 0)
    {   nits.pick (nit_css_type, ed_mdn, "functions", es_error, ec_css, quote (ss), ": '(' and ')' appear to be imbalanced.");
        st = s_invalid; }
    return st; }

e_status set_fn_trans_args_value (nitpick& , const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_good;
    if (! test_esii (sii_fn, s))
    {   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
        esii_scope esii (sii_fn, s);
//        if (box -> get_page ().css ().parse_transform (interpret_string (nits, v, s, true), v, box -> namespaces (), box -> ancestral_elements (), false, box -> line ()))
            return s_good; }
    return s_invalid; }

e_status set_fn_type_args_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   if (ss.empty ()) return s_good;
    if (ss == "*") return s_good;
    nitpick gnats;
    bool angular = false, had_type = false, had_word = false;
    e_status st = s_good;
    ::std::string n;
    for (auto s : ss)
        switch (s)
        {   case '<' :
                if (! n.empty ())
                {   n.clear ();
                    nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": is a '|' missing?");
                    st = s_invalid; }
                if (angular)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": cannot have nested types");
                    st = s_invalid; }
                else angular = true;
                had_word = had_type = false;
                break;
            case '>' :
                if (! angular)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": missing '<'");
                    st = s_invalid;
                    had_word = had_type = false; }
                else
                {   angular = false;
                    if (! test_value < t_css_type > (nits, v, n))
                        st = s_invalid;
                    had_type = true;
                    n.clear (); }
                had_word = false;
                break;
            case '|' :
                if (! had_word && ! had_type)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": should follow a type specification (e.g. '< TYPE >*') or a value");
                    st = s_invalid; }
                had_word = had_type = false;
                break;
            case '+' :
                if (! had_type)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": should follow a type specification (e.g. '< TYPE >*')");
                    st = s_invalid; }
                had_word = had_type = false;
                break;
            case '#' :
                if (! had_type)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": should follow a type specification (e.g. '< TYPE >#')");
                    st = s_invalid; }
                had_word = had_type = false;
                break;
            default :
                if (s <= ' ')
                {   if (! n.empty ()) had_word = true;
                    break; }
                if (((s >= '0') && (s <= '9')) || ((s >= 'a') && (s <= 'z')) || ((s >= 'A') && (s <= 'Z')) || (s == '-') || (s == '_'))
                {   had_word = true;
                    n += s; }
                else if (had_word || had_type)
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, "is a '|' missing after ", quote (n), " (", quote (s), ")");
                    n.clear ();
                    st = s_invalid;
                    had_word = had_type = false; }
                else
                {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, quote (s), ": unexpected when processing type ()");
                    st = s_invalid; }
                had_type = false;
                break; }
    if (angular)
    {   nits.pick (nit_css_type, ed_mdn, "type ()", es_error, ec_css, "missing '>' at end of type ()");
        st = s_invalid; }
    return st; }

e_status set_region_value (nitpick& , const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_invalid;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    g.note_str (gst_region, s);
    return s_good; }

e_status test_region_value (nitpick& nits, const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_invalid;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    if (g.has_str (gst_region, s)) return s_good;
    nits.pick (nit_pagination_template, es_error, ec_css, quote (s), ": unknown flow.");
    return s_invalid; }

e_status set_stn_value (nitpick& nits, const html_version& , const vstr_t& vs, element* box)
{   if (vs.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    for (auto s : vs)
        if ((s.length () < 2) || (s.substr (0, 2) != "--"))
            nits.pick (nit_sda, es_error, ec_css, quote (s), ": Scroll-Driver Animation identifiers must start with double dash");
        else g.note_str (gst_scroll_anim, s);
    return s_good; }

e_status set_vtn_value (nitpick& nits, const html_version& , const vstr_t& vs, element* box)
{   if (vs.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    for (auto s : vs)
        if ((s.length () < 2) || (s.substr (0, 2) != "--"))
            nits.pick (nit_vtn, es_error, ec_css, quote (s), ": View Transition identifiers must start with double dash");
        else g.note_str (gst_view, s);
    return s_good; }

e_status test_css_anchor (nitpick& nits, const e_status st, const html_version& , const ::std::string& ss)
{   if (st == s_empty)
        nits.pick (nit_empty, es_error, ec_type, "missing anchor name");
    else if ((st == s_good) || (st == s_unset))
        if ((ss.size () < 2) || (ss.substr (0, 2) != "--"))
            nits.pick (nit_anchor, ed_css_anchor, "2.1. Creating an Anchor: the anchor-name property", es_error, ec_type, "an anchor name must begin with --");
        else return s_good;
    return s_invalid; }

e_status test_css_template_set (nitpick& nits, const e_status st, arguments* a, const vstr_t& val)
{   if ((a == nullptr) || (st != s_good)) return st;
    if (a -> dst_ == nullptr) return s_invalid;
    if (context.css_module (c_page_template) < 3)
    {   nits.pick (nit_css_version, ed_css_page_template, "2. Pagination Templates and Slots", es_error, ec_css, "@slot requires CSS Pagination Template 3");
        return s_invalid; }
    e_status res = s_good;
    for (::std::size_t i = 0; i < val.size (); ++i)
        if (! a -> dst_ -> has (cic_template, val.at (i)))
        {   nits.pick (nit_pagination_template, ed_css_page_template, "2. Pagination Templates and Slots", es_error, ec_css, "No such @template as ", quote (val.at (i)));
            res = s_invalid; }
    return res; }

e_status test_route_name (nitpick& nits, const e_status st, const ::std::string& n, arguments* a)
{   if ((a == nullptr) || (st != s_good)) return st;
    if (context.css_module (c_route) < 3)
    {   nits.pick (nit_css_version, es_error, ec_css, "CSS Route 3 required");
        return s_invalid; }
    if (a -> has (cic_route, n)) return s_good;
    nits.pick (nit_route, es_error, ec_css, "@route ", quote (n), " undefined");
    return s_invalid; }
