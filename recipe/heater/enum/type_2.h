/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "base/type_master.h"
#include "base/type_case.h"
#include "spell/spell.h"

template < e_type TYPE, typename base_type, class OFF, class ON, bool EMPTY = false > class two_value : public type_base < base_type, TYPE >, public is_that < EMPTY >
{   bool true_ = false;
    static ::std::string off_, on_;
    static void init ();
public:
    typedef true_type has_int_type;
    two_value () = default;
    explicit two_value (element* box) noexcept : type_base < base_type, TYPE > (box) { }
    static e_animation_type animation_type () noexcept { return at_other; }
    ::std::string get_string () const
    {   if (! type_base < base_type, TYPE > :: unknown ())
        {   init ();
            if (true_) return ON::sz (); else return OFF::sz (); }
        return ::std::string (); }
    ::std::string name () const { return get_string (); }
    static ::std::string name (const base_type e)
    {   if (e == 0) return OFF::sz ();
        if (e == 1) return ON::sz ();
        GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return ::std::string ()); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void swap (two_value& t) noexcept
    {   ::std::swap (true_, t.true_);
        type_base < base_type, TYPE > :: swap (t); }
    static bool default_value () { return false; }
    bool has_value (const base_type& b) const { return type_base < base_type, TYPE > :: good () && ((b != static_cast < base_type> (0)) == true_); }
    base_type get () const noexcept
    {   return static_cast < base_type > (true_); }
    int get_int () const noexcept { return true_ ? 1 : 0; }
    ::std::size_t type () const noexcept { return static_cast < ::std::size_t > (get ()); } };

template < e_type TYPE, typename base_type, class OFF, class ON, bool EMPTY >
    void two_value < TYPE, base_type, OFF, ON, EMPTY > :: init ()
{   if (off_.empty ())
    {   eleanor f (lox_eleanor);
        off_ = ::boost::to_lower_copy (::std::string (OFF::sz ()));
        on_ =  ::boost::to_lower_copy (::std::string (ON::sz ()));
        PRESUME (! off_.empty (), __FILE__, __LINE__);
        PRESUME (! on_.empty (), __FILE__, __LINE__); } }

template < e_type TYPE, typename base_type, class OFF, class ON, bool EMPTY >
    void two_value < TYPE, base_type, OFF, ON, EMPTY > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string pret (trim_the_lot_off (s));
    ::std::string t (case_must_match < false >::lower (pret));
    type_base < base_type, TYPE > :: status (s_good);
    if (is_that < EMPTY > :: beside_the_point (t)) return;
    init ();
    if (t == off_) true_ = false;
    else if (t == on_) true_ = true;
    else
    {   if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "attribute cannot have an empty value (", type_name (TYPE), ")");
        else if (! check_identifier_spelling (nits, v, t))
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid; it can be ", quote (OFF::sz ()), " or ", quote (ON::sz ()));
        type_base < base_type, TYPE > :: status (s_invalid);
        return; }
    compare_validate (nits, v, get_string (), pret); }

template < e_type TYPE, typename base_type, class OFF, class ON, bool EMPTY >
    ::std::string two_value < TYPE, base_type, OFF, ON, EMPTY > :: off_;
template < e_type TYPE, typename base_type, class OFF, class ON, bool EMPTY >
    ::std::string two_value < TYPE, base_type, OFF, ON, EMPTY > :: on_;

template < > struct type_master < t_10 > : two_value < t_10, e_10, sz_0, sz_1 >
{ using two_value < t_10, e_10, sz_0, sz_1 > :: two_value; };

template < > struct type_master < t_a_v > : two_value < t_a_v, e_a_v, sz_a, sz_v >
{ using two_value < t_a_v, e_a_v, sz_a, sz_v > :: two_value; };

template < > struct type_master < t_accumulate > : two_value < t_accumulate, e_accumulate, sz_none, sz_sum >
{ using two_value < t_accumulate, e_accumulate, sz_none, sz_sum > :: two_value; };

template < > struct type_master < t_additive > : two_value < t_additive, e_additive, sz_replace, sz_sum >
{ using two_value < t_additive, e_additive, sz_replace, sz_sum > :: two_value; };

template < > struct type_master < t_aesf > : two_value < t_aesf, e_aesf, sz_allow_end, sz_space_first >
{ using two_value < t_aesf, e_aesf, sz_allow_end, sz_space_first > :: two_value; };

template < > struct type_master < t_all_none > : two_value < t_all_none, e_bool, sz_all, sz_none >
{ using two_value < t_all_none, e_bool, sz_all, sz_none > :: two_value; };

template < > struct type_master < t_allow_force > : two_value < t_allow_force, e_allow_force, sz_allow_end, sz_force_end >
{ using two_value < t_allow_force, e_allow_force, sz_allow_end, sz_force_end > :: two_value; };

template < > struct type_master < t_always_normal > : two_value < t_always_normal, e_always_normal, sz_always, sz_normal >
{ using two_value < t_always_normal, e_always_normal, sz_always, sz_normal > :: two_value; };

template < > struct type_master < t_auto_break > : two_value < t_auto_break, e_auto_break, sz_auto, sz_break >
{ using two_value < t_auto_break, e_auto_break, sz_auto, sz_break > :: two_value; };

template < > struct type_master < t_auto_contain > : two_value < t_auto_contain, e_auto_contain, sz_auto, sz_contain >
{ using two_value < t_auto_contain, e_auto_contain, sz_auto, sz_contain > :: two_value; };

template < > struct type_master < t_auto_none > : two_value < t_auto_none, e_auto_none, sz_auto, sz_none >
{ using two_value < t_auto_none, e_auto_none, sz_auto, sz_none > :: two_value; };

template < > struct type_master < t_auto_smooth > : two_value < t_auto_smooth, e_auto_smooth, sz_all, sz_smooth >
{ using two_value < t_auto_smooth, e_auto_smooth, sz_all, sz_smooth > :: two_value; };

template < > struct type_master < t_auto_stable > : two_value < t_auto_stable, e_auto_smooth, sz_all, sz_stable >
{ using two_value < t_auto_stable, e_auto_smooth, sz_all, sz_stable > :: two_value; };

template < > struct type_master < t_block_inline > : two_value < t_block_inline, e_block_inline, sz_block, sz_inline >
{ using two_value < t_block_inline, e_block_inline, sz_block, sz_inline > :: two_value; };

template < > struct type_master < t_bool > : two_value < t_bool, e_bool, sz_false, sz_true >
{ using two_value < t_bool, e_bool, sz_false, sz_true > :: two_value; };

template < > struct type_master < t_capture > : two_value < t_capture, ev_capture, sz_user, sz_environment >
{ using two_value < t_capture, ev_capture, sz_user, sz_environment > :: two_value; };

template < > struct type_master < t_circle_ellipse > : two_value < t_circle_ellipse, e_circle_ellipse, sz_circle, sz_ellipse >
{ using two_value < t_circle_ellipse, e_circle_ellipse, sz_circle, sz_ellipse > :: two_value; };

template < > struct type_master < t_closed_open > : two_value < t_closed_open, e_closed_open, sz_closed, sz_open >
{ using two_value < t_closed_open, e_closed_open, sz_closed, sz_open > :: two_value; };

template < > struct type_master < t_colour_scheme > : two_value < t_colour_scheme, e_colour_scheme, sz_dark, sz_light >
{ using two_value < t_colour_scheme, e_colour_scheme, sz_dark, sz_light > :: two_value; };

template < > struct type_master < t_colourspace > : two_value < t_colourspace, e_colourspace, sz_display_p3, sz_limited_srgb >
{ using two_value < t_colourspace, e_colourspace, sz_display_p3, sz_limited_srgb > :: two_value; };

template < > struct type_master < t_compositing > : two_value < t_compositing, e_compositing, sz_normal, sz_knockout >
{ using two_value < t_compositing, e_compositing, sz_normal, sz_knockout > :: two_value; };

template < > struct type_master < t_connect > : two_value < t_connect, e_connect, sz_line, sz_none >
{ using two_value < t_connect, e_connect, sz_line, sz_none > :: two_value; };

template < > struct type_master < t_contain_cover > : two_value < t_contain_cover, e_contain_cover, sz_contain, sz_cover >
{ using two_value < t_contain_cover, e_contain_cover, sz_contain, sz_cover > :: two_value; };

template < > struct type_master < t_coordinatesystem > : two_value < t_coordinatesystem, e_gradientunits, sz_userspaceonuse, sz_objectboundingbox >
{ using two_value < t_coordinatesystem, e_gradientunits, sz_userspaceonuse, sz_objectboundingbox > :: two_value; };

template < > struct type_master < t_cors > : two_value < t_cors, ev_cors, sz_anonymous, sz_use_credentials >
{ using two_value < t_cors, ev_cors, sz_anonymous, sz_use_credentials > :: two_value; };

template < > struct type_master < t_create_parent > : two_value < t_create_parent, e_create_parent, sz_create, sz_match_parent >
{ using two_value < t_create_parent, e_create_parent, sz_create, sz_match_parent > :: two_value; };

template < > struct type_master < t_cs > : two_value < t_cs, e_cs, sz_compress, sz_stretch >
{ using two_value < t_cs, e_cs, sz_compress, sz_stretch > :: two_value; };

template < > struct type_master < t_css_anim_play_state > : two_value < t_css_anim_play_state, e_css_anim_play_state, sz_paused, sz_running >
{ using two_value < t_css_anim_play_state, e_css_anim_play_state, sz_paused, sz_running > :: two_value; };

template < > struct type_master < t_css_box_sizing > : two_value < t_css_box_sizing, e_css_box_sizing, sz_border_box, sz_content_box >
{ using two_value < t_css_box_sizing, e_css_box_sizing, sz_border_box, sz_content_box > :: two_value; };

template < > struct type_master < t_css_break_box > : two_value < t_css_break_box, e_css_break_box, sz_clone, sz_slice >
{ using two_value < t_css_break_box, e_css_break_box, sz_clone, sz_slice > :: two_value; };

template < > struct type_master < t_css_display_box > : two_value < t_css_display_box, e_css_display_box, sz_contents, sz_none >
{ using two_value < t_css_display_box, e_css_display_box, sz_contents, sz_none > :: two_value; };

template < > struct type_master < t_css_display_flow > : two_value < t_css_display_flow, e_css_display_flow, sz_flow, sz_flow_root >
{ using two_value < t_css_display_flow, e_css_display_flow, sz_flow, sz_flow_root > :: two_value; };

template < > struct type_master < t_css_isolation > : two_value < t_css_isolation, e_css_isolation, sz_auto, sz_isolate >
{ using two_value < t_css_isolation, e_css_isolation, sz_auto, sz_isolate > :: two_value; };

template < > struct type_master < t_css_mark > : two_value < t_css_mark, e_css_mark, sz_crop, sz_cross >
{ using two_value < t_css_mark, e_css_mark, sz_crop, sz_cross > :: two_value; };

template < > struct type_master < t_css_mask_border_mode > : two_value < t_css_mask_border_mode, e_css_mask_border_mode, sz_alpha, sz_luminance >
{ using two_value < t_css_mask_border_mode, e_css_mask_border_mode, sz_alpha, sz_luminance > :: two_value; };

template < > struct type_master < t_css_shape_fillrule > : two_value < t_css_shape_fillrule, e_css_shape_fillrule, sz_evenodd, sz_nonzero >
{ using two_value < t_css_shape_fillrule, e_css_shape_fillrule, sz_evenodd, sz_nonzero > :: two_value; };

template < > struct type_master < t_css_text_resize > : two_value < t_css_text_resize, e_css_text_resize, sz_clip, sz_ellipsis >
{ using two_value < t_css_text_resize, e_css_text_resize, sz_clip, sz_ellipsis > :: two_value; };

template < > struct type_master < t_css_transform_style > : two_value < t_css_transform_style, e_css_transform_style, sz_flat, sz_preserve_3d >
{ using two_value < t_css_transform_style, e_css_transform_style, sz_flat, sz_preserve_3d > :: two_value; };

template < > struct type_master < t_css_wc_e > : two_value < t_css_wc_e, e_css_wc_e, sz_contents, sz_scroll_position >
{ using two_value < t_css_wc_e, e_css_wc_e, sz_contents, sz_scroll_position > :: two_value; };

template < > struct type_master < t_dataformatas > : two_value < t_dataformatas, e_dataformatas, sz_html, sz_plaintext >
{ using two_value < t_dataformatas, e_dataformatas, sz_html, sz_plaintext > :: two_value; };

template < > struct type_master < t_defaultaction > : two_value < t_defaultaction, e_defaultaction, sz_cancel, sz_perform >
{ using two_value < t_defaultaction, e_defaultaction, sz_cancel, sz_perform > :: two_value; };

template < > struct type_master < t_dg > : two_value < t_dg, e_dg, sz_dash, sz_gaps >
{ using two_value < t_dg, e_dg, sz_dash, sz_gaps > :: two_value; };

template < > struct type_master < t_drop_raise > : two_value < t_drop_raise, e_drop_raise, sz_drop, sz_raise >
{ using two_value < t_drop_raise, e_drop_raise, sz_drop, sz_raise > :: two_value; };

template < > struct type_master < t_dynamic_range > : two_value < t_dynamic_range, e_dynamic_range, sz_high, sz_standard >
{ using two_value < t_dynamic_range, e_dynamic_range, sz_high, sz_standard > :: two_value; };

template < > struct type_master < t_e_w > : two_value < t_e_w, e_e_w, sz_e, sz_w >
{ using two_value < t_e_w, e_e_w, sz_e, sz_w > :: two_value; };

template < > struct type_master < t_economy_exact > : two_value < t_economy_exact, e_economy_exact, sz_economy, sz_exact >
{ using two_value < t_economy_exact, e_economy_exact, sz_economy, sz_exact > :: two_value; };

template < > struct type_master < t_editable > : two_value < t_editable, e_editable, sz_none, sz_simple >
{ using two_value < t_editable, e_editable, sz_none, sz_simple > :: two_value; };

template < > struct type_master < t_fillanim > : two_value < t_fillanim, e_fillanim, sz_freeze, sz_remove >
{ using two_value < t_fillanim, e_fillanim, sz_freeze, sz_remove > :: two_value; };

template < > struct type_master < t_filled_open > : two_value < t_filled_open, e_filled_open, sz_filled, sz_open >
{ using two_value < t_filled_open, e_filled_open, sz_filled, sz_open > :: two_value; };

template < > struct type_master < t_fill_ve > : two_value < t_fill_ve, e_fill_ve, sz_strokepaint, sz_fillpaint >
{ using two_value < t_fill_ve, e_fill_ve, sz_strokepaint, sz_fillpaint > :: two_value; };

template < > struct type_master < t_first_last > : two_value < t_first_last, e_first_last, sz_first, sz_last >
{ using two_value < t_first_last, e_first_last, sz_first, sz_last > :: two_value; };

template < > struct type_master < t_fixed_zoom > : two_value < t_fixed_zoom, e_fixed_zoom, sz_fixed, sz_zoom >
{ using two_value < t_fixed_zoom, e_fixed_zoom, sz_fixed, sz_zoom > :: two_value; };

template < > struct type_master < t_forced_colours > : two_value < t_forced_colours, e_forced_colours, sz_active, sz_none >
{ using two_value < t_forced_colours, e_forced_colours, sz_active, sz_none > :: two_value; };

template < > struct type_master < t_forrev > : two_value < t_forrev, e_forrev, sz_forward, sz_reverse >
{ using two_value < t_forrev, e_forrev, sz_forward, sz_reverse > :: two_value; };

template < > struct type_master < t_gender > : two_value < t_gender, e_gender, sz_female, sz_male >
{ using two_value < t_gender, e_gender, sz_female, sz_male > :: two_value; };

template < > struct type_master < t_grid_normal > : two_value < t_grid_normal, e_grid_normal, sz_grid, sz_normal >
{ using two_value < t_grid_normal, e_grid_normal, sz_grid, sz_normal > :: two_value; };

template < > struct type_master < t_hidden > : two_value < t_hidden, e_hidden, sz_hidden, sz_until_found, true >
{ using two_value < t_hidden, e_hidden, sz_hidden, sz_until_found, true > :: two_value; };

template < > struct type_master < t_hv > : two_value < t_hv, e_hv, sz_horizontal, sz_vertical >
{ using two_value < t_hv, e_hv, sz_horizontal, sz_vertical > :: two_value; };

template < > struct type_master < t_initialvisibility > : two_value < t_initialvisibility, e_initialvisibility, sz_whenstarted, sz_always >
{ using two_value < t_initialvisibility, e_initialvisibility, sz_whenstarted, sz_always > :: two_value; };

template < > struct type_master < t_inverted_colours > : two_value < t_inverted_colours, e_inverted_colours, sz_inverted, sz_none >
{ using two_value < t_inverted_colours, e_inverted_colours, sz_inverted, sz_none > :: two_value; };

template < > struct type_master < t_js_version > : two_value < t_js_version, e_jsonld_version, sz_1_0, sz_1_1 >
{ using two_value < t_js_version, e_jsonld_version, sz_1_0, sz_1_1 > :: two_value; };

template < > struct type_master < t_layout > : two_value < t_layout, e_layout, sz_irrelevant, sz_relevant >
{ using two_value < t_layout, e_layout, sz_irrelevant, sz_relevant > :: two_value; };

template < > struct type_master < t_lengthadjust > : two_value < t_lengthadjust, e_lengthadjust, sz_spacing, sz_spacingandglyphs >
{ using two_value < t_lengthadjust, e_lengthadjust, sz_spacing, sz_spacingandglyphs > :: two_value; };

template < > struct type_master < t_literal_or_not > : two_value < t_literal_or_not, e_literal_or_not, sz_literal_punctuation, sz_no_punctuation >
{ using two_value < t_literal_or_not, e_literal_or_not, sz_literal_punctuation, sz_no_punctuation > :: two_value; };

template < > struct type_master < t_loading > : two_value < t_loading, e_loading, sz_eager, sz_lazy >
{ using two_value < t_loading, e_loading, sz_eager, sz_lazy > :: two_value; };

template < > struct type_master < t_lralign > : two_value < t_lralign, e_lralign, sz_left, sz_right >
{ using two_value < t_lralign, e_lralign, sz_left, sz_right > :: two_value; };

template < > struct type_master < t_m_t > : two_value < t_m_t, e_m_t, sz_m, sz_t >
{ using two_value < t_m_t, e_m_t, sz_m, sz_t > :: two_value; };

template < > struct type_master < t_mand_prox > : two_value < t_mand_prox, e_mand_prox, sz_mandatory, sz_proximity >
{ using two_value < t_mand_prox, e_mand_prox, sz_mandatory, sz_proximity > :: two_value; };

template < > struct type_master < t_manual_normal > : two_value < t_manual_normal, e_manual_normal, sz_manual, sz_normal >
{ using two_value < t_manual_normal, e_manual_normal, sz_manual, sz_normal > :: two_value; };

template < > struct type_master < t_markerunits > : two_value < t_markerunits, e_markerunits, sz_strokewidth, sz_userspaceonuse >
{ using two_value < t_markerunits, e_markerunits, sz_strokewidth, sz_userspaceonuse > :: two_value; };

template < > struct type_master < t_margin_padding > : two_value < t_margin_padding, e_margin_padding, sz_margin, sz_padding >
{ using two_value < t_margin_padding, e_margin_padding, sz_margin, sz_padding > :: two_value; };

template < > struct type_master < t_match_self_parent > : two_value < t_match_self_parent, e_match_self_parent, sz_match_parent, sz_match_self >
{ using two_value < t_match_self_parent, e_match_self_parent, sz_match_parent, sz_match_self > :: two_value; };

template < > struct type_master < t_mathfontstyle > : two_value < t_mathfontstyle, e_fontstyle, sz_italic, sz_normal >
{ using two_value < t_mathfontstyle, e_fontstyle, sz_italic, sz_normal > :: two_value; };

template < > struct type_master < t_mathfontweight > : two_value < t_mathfontweight, e_math_fontweight, sz_bold, sz_normal >
{ using two_value < t_mathfontweight, e_math_fontweight, sz_bold, sz_normal > :: two_value; };

template < > struct type_master < t_mathmode > : two_value < t_mathmode, e_mode, sz_display, sz_inline >
{ using two_value < t_mathmode, e_mode, sz_display, sz_inline > :: two_value; };

template < > struct type_master < t_mathorder > : two_value < t_mathorder, m_mathorder, sz_numeric, sz_lexicographic >
{ using two_value < t_mathorder, m_mathorder, sz_numeric, sz_lexicographic > :: two_value; };

template < > struct type_master < t_mathscope > : two_value < t_mathscope, e_mathscope, sz_global, sz_local >
{ using two_value < t_mathscope, e_mathscope, sz_global, sz_local > :: two_value; };

template < > struct type_master < t_media_hover > : two_value < t_media_hover, e_media_hover, sz_hover, sz_none >
{ using two_value < t_media_hover, e_media_hover, sz_hover, sz_none > :: two_value; };

template < > struct type_master < t_media_inline > : two_value < t_media_inline, e_media_inline, sz_none, sz_scroll >
{ using two_value < t_media_inline, e_media_inline, sz_none, sz_scroll > :: two_value; };

template < > struct type_master < t_media_orientation > : two_value < t_media_orientation, e_media_orientation, sz_landscape, sz_portrait >
{ using two_value < t_media_orientation, e_media_orientation, sz_landscape, sz_portrait > :: two_value; };

template < > struct type_master < t_media_prefers > : two_value < t_media_prefers, e_media_prefers, sz_no_preference, sz_reduce >
{ using two_value < t_media_prefers, e_media_prefers, sz_no_preference, sz_reduce > :: two_value; };

template < > struct type_master < t_meetslice > : two_value < t_meetslice, e_meetslice, sz_meet, sz_slice >
{ using two_value < t_meetslice, e_meetslice, sz_meet, sz_slice > :: two_value; };

template < > struct type_master < t_morphology_operator > : two_value < t_morphology_operator, e_morphology_operator, sz_dilate, sz_erode >
{ using two_value < t_morphology_operator, e_morphology_operator, sz_dilate, sz_erode > :: two_value; };

template < > struct type_master < t_n_s > : two_value < t_n_s, e_n_s, sz_n, sz_s >
{ using two_value < t_n_s, e_n_s, sz_n, sz_s > :: two_value; };

template < > struct type_master < t_nav_controls > : two_value < t_nav_controls, e_nav_controls, sz_back, sz_none >
{ using two_value < t_nav_controls, e_nav_controls, sz_back, sz_none > :: two_value; };

template < > struct type_master < t_none_objects > : two_value < t_none_objects, e_none_objects, sz_none, sz_objects >
{ using two_value < t_none_objects, e_none_objects, sz_none, sz_objects > :: two_value; };

template < > struct type_master < t_none_wrap > : two_value < t_none_wrap, e_none_wrap, sz_none, sz_wrap >
{ using two_value < t_none_wrap, e_none_wrap, sz_none, sz_wrap > :: two_value; };

template < > struct type_master < t_normal_spell > : two_value < t_normal_spell, e_normal_spell, sz_normal, sz_spell_out >
{ using two_value < t_normal_spell, e_normal_spell, sz_normal, sz_spell_out > :: two_value; };

template < > struct type_master < t_normal_stretch > : two_value < t_normal_stretch, e_normal_stretch, sz_normal, sz_stretch >
{ using two_value < t_normal_stretch, e_normal_stretch, sz_normal, sz_stretch > :: two_value; };

template < > struct type_master < t_notations > : two_value < t_notations, e_notations, sz_dsssl, sz_w3c >
{ using two_value < t_notations, e_notations, sz_dsssl, sz_w3c > :: two_value; };

template < > struct type_master < t_onetwo > : two_value < t_onetwo, e_onetwo, sz_one, sz_two >
{ using two_value < t_onetwo, e_onetwo, sz_one, sz_two > :: two_value; };

template < > struct type_master < t_onoff > : two_value < t_onoff, e_onoff, sz_off, sz_on >
{ using two_value < t_onoff, e_onoff, sz_off, sz_on > :: two_value; };

template < > struct type_master < t_orientation > : two_value < t_orientation, e_orientation, sz_h, sz_v >
{ using two_value < t_orientation, e_orientation, sz_h, sz_v > :: two_value; };

template < > struct type_master < t_overlay > : two_value < t_overlay, e_overlay, sz_none, sz_top >
{ using two_value < t_overlay, e_overlay, sz_none, sz_top > :: two_value; };

template < > struct type_master < t_over_under > : two_value < t_over_under, e_over_under, sz_over, sz_under >
{ using two_value < t_over_under, e_over_under, sz_over, sz_under > :: two_value; };

template < > struct type_master < t_pri_img_orientation > : two_value < t_pri_img_orientation, e_pri_img_orientation, sz_horizontal, sz_vertical >
{ using two_value < t_pri_img_orientation, e_pri_img_orientation, sz_horizontal, sz_vertical > :: two_value; };

template < > struct type_master < t_prism_fccv > : two_value < t_prism_fccv, e_prism_fccv, sz_credit, sz_mediatitle >
{ using two_value < t_prism_fccv, e_prism_fccv, sz_credit, sz_mediatitle > :: two_value; };

template < > struct type_master < t_prism_issue_type > : two_value < t_prism_issue_type, e_prism_issue_type, sz_regularissue, sz_specialissue >
{ using two_value < t_prism_issue_type, e_prism_issue_type, sz_regularissue, sz_specialissue > :: two_value; };

template < > struct type_master < t_propagate > : two_value < t_propagate, e_propagate, sz_stop, sz_continue >
{ using two_value < t_propagate, e_propagate, sz_stop, sz_continue > :: two_value; };

template < > struct type_master < t_rect_round > : two_value < t_rect_round, e_rect_round, sz_rect, sz_round >
{ using two_value < t_rect_round, e_rect_round, sz_rect, sz_round > :: two_value; };

template < > struct type_master < t_row_column > : two_value < t_row_column, e_row_column, sz_column, sz_row >
{ using two_value < t_row_column, e_row_column, sz_column, sz_row > :: two_value; };

template < > struct type_master < t_safe_unsafe > : two_value < t_safe_unsafe, e_safe_unsafe, sz_safe, sz_unsafe >
{ using two_value < t_safe_unsafe, e_safe_unsafe, sz_safe, sz_unsafe > :: two_value; };

template < > struct type_master < t_settype > : two_value < t_settype, e_settype, sz_normal, sz_multiset >
{ using two_value < t_settype, e_settype, sz_normal, sz_multiset > :: two_value; };

template < > struct type_master < t_size_inlinesize > : two_value < t_size_inlinesize, e_size_inlinesize, sz_inline_size, sz_size >
{ using two_value < t_size_inlinesize, e_size_inlinesize, sz_inline_size, sz_size > :: two_value; };

template < > struct type_master < t_spacing > : two_value < t_spacing, e_spacing, sz_auto, sz_exact >
{ using two_value < t_spacing, e_spacing, sz_auto, sz_exact > :: two_value; };

template < > struct type_master < t_ssi_sizefmt > : two_value < t_ssi_sizefmt, e_ssi_sizefmt, sz_abbrev, sz_bytes >
{ using two_value < t_ssi_sizefmt, e_ssi_sizefmt, sz_abbrev, sz_bytes > :: two_value; };

template < > struct type_master < t_ssi_exec > : two_value < t_ssi_exec, e_ssi_exec, sz_cgi, sz_cmd >
{ using two_value < t_ssi_exec, e_ssi_exec, sz_cgi, sz_cmd > :: two_value; };

template < > struct type_master < t_ssi_f > : two_value < t_ssi_f, e_ssi_f, sz_file, sz_virtual >
{ using two_value < t_ssi_f, e_ssi_f, sz_file, sz_virtual > :: two_value; };

template < > struct type_master < t_startend > : two_value < t_startend, e_startend, sz_start, sz_end >
{ using two_value < t_startend, e_startend, sz_start, sz_end > :: two_value; };

template < > struct type_master < t_stitchtiles > : two_value < t_stitchtiles, e_stitchtiles, sz_stitch, sz_nostitch >
{ using two_value < t_stitchtiles, e_stitchtiles, sz_stitch, sz_nostitch > :: two_value; };

template < > struct type_master < t_streamedcontents > : two_value < t_streamedcontents, e_streamedcontents, sz_keep, sz_discard >
{ using two_value < t_streamedcontents, e_streamedcontents, sz_keep, sz_discard > :: two_value; };

template < > struct type_master < t_ltr_rtl > : two_value < t_ltr_rtl, e_svg_direction2, sz_ltr, sz_rtl >
{ using two_value < t_ltr_rtl, e_svg_direction2, sz_ltr, sz_rtl > :: two_value; };

template < > struct type_master < t_scan > : two_value < t_scan, e_scan, sz_interlace, sz_progressive >
{ using two_value < t_scan, e_scan, sz_interlace, sz_progressive > :: two_value; };

template < > struct type_master < t_svg_fontvariant_ff > : two_value < t_svg_fontvariant_ff, e_svg_fontvariant_ff, sz_normal, sz_smallcaps >
{ using two_value < t_svg_fontvariant_ff, e_svg_fontvariant_ff, sz_normal, sz_smallcaps > :: two_value; };

template < > struct type_master < t_svg_method > : two_value < t_svg_method, e_svg_method, sz_align, sz_stretch >
{ using two_value < t_svg_method, e_svg_method, sz_align, sz_stretch > :: two_value; };

template < > struct type_master < t_svg_playbackorder > : two_value < t_svg_playbackorder, e_svg_playbackorder, sz_all, sz_forwardonly >
{ using two_value < t_svg_playbackorder, e_svg_playbackorder, sz_all, sz_forwardonly > :: two_value; };

template < > struct type_master < t_svg_side > : two_value < t_svg_side, e_svg_side, sz_left, sz_right >
{ using two_value < t_svg_side, e_svg_side, sz_left, sz_right > :: two_value; };

template < > struct type_master < t_svg_timelinebegin > : two_value < t_svg_timelinebegin, e_svg_timelinebegin, sz_onload, sz_onstart >
{ using two_value < t_svg_timelinebegin, e_svg_timelinebegin, sz_onload, sz_onstart > :: two_value; };

template < > struct type_master < t_svg_units > : two_value < t_svg_units, e_svg_units, sz_object_bbox, sz_userspace >
{ using two_value < t_svg_units, e_svg_units, sz_object_bbox, sz_userspace > :: two_value; };

template < > struct type_master < t_tbalign > : two_value < t_tbalign, e_tbalign, sz_bottom, sz_top >
{ using two_value < t_tbalign, e_tbalign, sz_bottom, sz_top > :: two_value; };

template < > struct type_master < t_tfn > : two_value < t_tfn, e_bool, sz_false, sz_true, true >
{ using two_value < t_tfn, e_bool, sz_false, sz_true, true > :: two_value; };

template < > struct type_master < t_transp > : two_value < t_transp, e_transp, sz_opaque, sz_transparent >
{ using two_value < t_transp, e_transp, sz_opaque, sz_transparent > :: two_value; };

template < > struct type_master < t_truefalseempty > : two_value < t_truefalseempty, e_bool, sz_false, sz_true, true >
{ using two_value < t_truefalseempty, e_bool, sz_false, sz_true, true > :: two_value; };

template < > struct type_master < t_viewportscreen > : two_value < t_viewportscreen, e_viewportscreen, sz_viewport, sz_screen >
{ using two_value < t_viewportscreen, e_viewportscreen, sz_viewport, sz_screen > :: two_value; };

template < > struct type_master < t_vtype > : two_value < t_vtype, e_vtype, sz_home, sz_work >
{ using two_value < t_vtype, e_vtype, sz_home, sz_work > :: two_value; };

template < > struct type_master < t_workertype > : two_value < t_workertype, e_workertype, sz_classic, sz_module >
{ using two_value < t_workertype, e_workertype, sz_classic, sz_module > :: two_value; };

template < > struct type_master < t_wrap > : two_value < t_wrap, e_wrap, sz_soft, sz_hard >
{ using two_value < t_wrap, e_wrap, sz_soft, sz_hard > :: two_value; };

template < > struct type_master < t_wrap3 > : two_value < t_wrap3, e_wrap3, sz_horiz, sz_vert >
{ using two_value < t_wrap3, e_wrap3, sz_horiz, sz_vert > :: two_value; };

template < > struct type_master < t_xlinkshow_a > : two_value < t_xlinkshow_a, e_xlinkshow_a, sz_new, sz_replace >
{ using two_value < t_xlinkshow_a, e_xlinkshow_a, sz_new, sz_replace > :: two_value; };

template < > struct type_master < t_xmlspace > : two_value < t_xmlspace, e_xmlspace, sz_default, sz_preserve >
{ using two_value < t_xmlspace, e_xmlspace, sz_default, sz_preserve > :: two_value; };

template < > struct type_master < t_xmpg_type > : two_value < t_xmpg_type, e_xmpg_type, sz_process, sz_spot >
{ using two_value < t_xmpg_type, e_xmpg_type, sz_process, sz_spot > :: two_value; };

template < > struct type_master < t_xorder > : two_value < t_xorder, e_xorder, sz_document, sz_list >
{ using two_value < t_xorder, e_xorder, sz_document, sz_list > :: two_value; };

template < > struct type_master < t_yesno > : two_value < t_yesno, e_yesno, sz_no, sz_yes >
{ using two_value < t_yesno, e_yesno, sz_no, sz_yes > :: two_value; };

template < > struct type_master < t_yesnoempty > : two_value < t_yesnoempty, e_yesno, sz_no, sz_yes, true >
{ using two_value < t_yesnoempty, e_yesno, sz_no, sz_yes, true > :: two_value; };

template < > struct type_master < t_zoompan > : two_value < t_zoompan, e_zoompan, sz_disable, sz_magnify >
{ using two_value < t_zoompan, e_zoompan, sz_disable, sz_magnify > :: two_value; };
