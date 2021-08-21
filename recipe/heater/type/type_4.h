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
#include "type/type_master.h"
#include "type/type_case.h"

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 > class four_value : public type_base < base_type, TYPE >
{   base_type value_ = static_cast < base_type > (0);
    static ::std::string a_, b_, c_, d_;
public:
    typedef true_type has_int_type;
    using type_base < base_type, TYPE > :: type_base;
    static e_animation_type animation_type () { return at_other; }
    ::std::string get_string () const;
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void swap (four_value& t) NOEXCEPT { ::std::swap (value_, t.value_); type_base < base_type, TYPE >::swap (t); }
    static base_type default_value () { return static_cast <base_type> (0); }
    base_type get () const { return value_; }
    int get_int () const { return static_cast < int > (value_); }
    ::std::size_t type () const { return static_cast < ::std::size_t > (get ()); }
    bool has_value (const base_type& b) const { return type_base < base_type, TYPE > :: good () && (value_ == b); } };

template < > struct type_master < t_actiontype2 > : four_value < t_actiontype2, e_actiontype, sz_toggle, sz_statusline, sz_tooltip, sz_highlight >
{ using four_value < t_actiontype2, e_actiontype, sz_toggle, sz_statusline, sz_tooltip, sz_highlight > :: four_value; };

template < > struct type_master < t_align2070 > : four_value < t_align2070, e_align2070, sz_centre, sz_justify, sz_left, sz_right >
{ using four_value < t_align2070, e_align2070, sz_centre, sz_justify, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_aligndec > : four_value < t_aligndec, e_aligndec, sz_centre, sz_decimal, sz_left, sz_right >
{ using four_value < t_aligndec, e_aligndec, sz_centre, sz_decimal, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_alignfig > : four_value < t_alignfig, e_alignfig, sz_centre, sz_float, sz_left, sz_right >
{ using four_value < t_alignfig, e_alignfig, sz_centre, sz_float, sz_left, sz_right > :: four_value; };

template < > struct type_master < t_arabicenum > : four_value < t_arabicenum, e_arabicenum, sz_initial, sz_medial, sz_terminal, sz_isolated >
{ using four_value < t_arabicenum, e_arabicenum, sz_initial, sz_medial, sz_terminal, sz_isolated > :: four_value; };

template < > struct type_master < t_aria_autocomplete > : four_value < t_aria_autocomplete, e_aria_autocomplete, sz_both, sz_inline, sz_list, sz_none >
{ using four_value < t_aria_autocomplete, e_aria_autocomplete, sz_both, sz_inline, sz_list, sz_none > :: four_value; };

template < > struct type_master < t_aria_invalidity > : four_value < t_aria_invalidity, e_aria_invalidity, sz_false, sz_grammar, sz_spelling, sz_true >
{ using four_value < t_aria_invalidity, e_aria_invalidity, sz_false, sz_grammar, sz_spelling, sz_true > :: four_value; };

template < > struct type_master < t_buffered_rendering > : four_value < t_buffered_rendering, e_buffered_rendering, sz_auto, sz_dynamic, sz_static, sz_inherit >
{ using four_value < t_buffered_rendering, e_buffered_rendering, sz_auto, sz_dynamic, sz_static, sz_inherit > :: four_value; };

template < > struct type_master < t_calcmode > : four_value < t_calcmode, e_calcmode, sz_discrete, sz_linear, sz_paced, sz_spline >
{ using four_value < t_calcmode, e_calcmode, sz_discrete, sz_linear, sz_paced, sz_spline > :: four_value; };

template < > struct type_master < t_captionalign > : four_value < t_captionalign, e_captionalign, sz_bottom, sz_left, sz_right, sz_top >
{ using four_value < t_captionalign, e_captionalign, sz_bottom, sz_left, sz_right, sz_top > :: four_value; };

template < > struct type_master < t_cc_requires > : four_value < t_cc_requires, e_cc_requires, sz_cc_attribution, sz_cc_notice, sz_cc_sharealike, sz_cc_sourcecode >
{ using four_value < t_cc_requires, e_cc_requires, sz_cc_attribution, sz_cc_notice, sz_cc_sharealike, sz_cc_sourcecode > :: four_value; };

template < > struct type_master < t_channelselector > : four_value < t_channelselector, e_channelselector, sz_a, sz_b, sz_g, sz_r >
{ using four_value < t_channelselector, e_channelselector, sz_a, sz_b, sz_g, sz_r > :: four_value; };

template < > struct type_master < t_content_encoding > : four_value < t_content_encoding, e_content_encoding, sz_gzip, sz_compress, sz_deflate, sz_identity >
{ using four_value < t_content_encoding, e_content_encoding, sz_gzip, sz_compress, sz_deflate, sz_identity > :: four_value; };

template < > struct type_master < t_dsctv > : four_value < t_dsctv, e_dsctv, sz_disc, sz_square, sz_circle, sz_triangle >
{ using four_value < t_dsctv, e_dsctv, sz_disc, sz_square, sz_circle, sz_triangle > :: four_value; };

template < > struct type_master < t_device > : four_value < t_device, e_device, sz_media, sz_fs, sz_rs232, sz_usb >
{ using four_value < t_device, e_device, sz_media, sz_fs, sz_rs232, sz_usb > :: four_value; };

template < > struct type_master < t_edit > : four_value < t_edit, e_edit, sz_changed, sz_deleted, sz_inserted, sz_moved >
{ using four_value < t_edit, e_edit, sz_changed, sz_deleted, sz_inserted, sz_moved > :: four_value; };

template < > struct type_master < t_effect > : four_value < t_effect, e_effect, sz_embed, sz_overlay, sz_replace, sz_new >
{ using four_value < t_effect, e_effect, sz_embed, sz_overlay, sz_replace, sz_new > :: four_value; };

template < > struct type_master < t_frame4 > : four_value < t_frame4, e_frame4, sz__blank, sz__parent, sz__self, sz__top >
{ using four_value < t_frame4, e_frame4, sz__blank, sz__parent, sz__self, sz__top > :: four_value; };

template < > struct type_master < t_larnalign > : four_value < t_larnalign, e_larnalign, sz_left, sz_all, sz_right, sz_none >
{ using four_value < t_larnalign, e_larnalign, sz_left, sz_all, sz_right, sz_none > :: four_value; };

template < > struct type_master < t_lcrnalign > : four_value < t_lcrnalign, e_lcrnalign, sz_left, sz_centre, sz_right, sz_none >
{ using four_value < t_lcrnalign, e_lcrnalign, sz_left, sz_centre, sz_right, sz_none > :: four_value; };

template < > struct type_master < t_lcrd > : four_value < t_lcrd, e_lcrd, sz_left, sz_centre, sz_right, sz_decimalpoint >
{ using four_value < t_lcrd, e_lcrd, sz_left, sz_centre, sz_right, sz_decimalpoint > :: four_value; };

template < > struct type_master < t_linebreakstyle > : four_value < t_linebreakstyle, e_linebreakstyle, sz_before, sz_after, sz_duplicate, sz_infixlinebreakstyle >
{ using four_value < t_linebreakstyle, e_linebreakstyle, sz_before, sz_after, sz_duplicate, sz_infixlinebreakstyle > :: four_value; };

template < > struct type_master < t_linecap > : four_value < t_linecap, e_linecap, sz_butt, sz_round, sz_square, sz_inherit >
{ using four_value < t_linecap, e_linecap, sz_butt, sz_round, sz_square, sz_inherit > :: four_value; };

template < > struct type_master < t_linejoin > : four_value < t_linejoin, e_linejoin, sz_miter, sz_round, sz_bevel, sz_inherit >
{ using four_value < t_linejoin, e_linejoin, sz_miter, sz_round, sz_bevel, sz_inherit > :: four_value; };

template < > struct type_master < t_mathclosure > : four_value < t_mathclosure, e_mathclosure, sz_open, sz_closed, sz_openclosed, sz_closedopen >
{ using four_value < t_mathclosure, e_mathclosure, sz_open, sz_closed, sz_openclosed, sz_closedopen > :: four_value; };

template < > struct type_master < t_mathside > : four_value < t_mathside, e_mathside, sz_left, sz_right, sz_leftoverlap, sz_rightoverlap >
{ using four_value < t_mathside, e_mathside, sz_left, sz_right, sz_leftoverlap, sz_rightoverlap > :: four_value; };

template < > struct type_master < t_mf_availability > : four_value < t_mf_availability, e_mf_availability, sz_out_of_stock, sz_in_stock, sz_instore_only, sz_preorder >
{ using four_value < t_mf_availability, e_mf_availability, sz_out_of_stock, sz_in_stock, sz_instore_only, sz_preorder > :: four_value; };

template < > struct type_master < t_mf_category > : four_value < t_mf_category, e_mf_category, sz_meeting, sz_appointment, sz_conference, sz_expo >
{ using four_value < t_mf_category, e_mf_category, sz_meeting, sz_appointment, sz_conference, sz_expo > :: four_value; };

template < > struct type_master < t_paint_order > : four_value < t_paint_order, e_paint_order, sz_normal, sz_fill, sz_stroke, sz_markers >
{ using four_value < t_paint_order, e_paint_order, sz_normal, sz_fill, sz_stroke, sz_markers > :: four_value; };

template < > struct type_master < t_phase_x > : four_value < t_phase_x, e_phase_x, sz_bubble, sz_capture, sz_default, sz_target >
{ using four_value < t_phase_x, e_phase_x, sz_bubble, sz_capture, sz_default, sz_target > :: four_value; };

template < > struct type_master < t_rsvp > : four_value < t_rsvp, e_rsvp, sz_yes, sz_no, sz_maybe, sz_interested >
{ using four_value < t_rsvp, e_rsvp, sz_yes, sz_no, sz_maybe, sz_interested > :: four_value; };

template < > struct type_master < t_tdscope > : four_value < t_tdscope, e_tdscope, sz_row, sz_col, sz_rowgroup, sz_colgroup >
{ using four_value < t_tdscope, e_tdscope, sz_row, sz_col, sz_rowgroup, sz_colgroup > :: four_value; };

template < > struct type_master < t_shadowinherit > : four_value < t_shadowinherit, e_shadowinherit, sz_ondefine, sz_onuse, sz_none, sz_inherit >
{ using four_value < t_shadowinherit, e_shadowinherit, sz_ondefine, sz_onuse, sz_none, sz_inherit > :: four_value; };

template < > struct type_master < t_shape4 > : four_value < t_shape4, e_shape4, sz_circle, sz_default, sz_poly, sz_rect >
{ using four_value < t_shape4, e_shape4, sz_circle, sz_default, sz_poly, sz_rect > :: four_value; };

template < > struct type_master < t_size3 > : four_value < t_size3, e_size3, sz_normal, sz_medium, sz_large, sz_huge >
{ using four_value < t_size3, e_size3, sz_normal, sz_medium, sz_large, sz_huge > :: four_value; };

template < > struct type_master < t_ssi_config > : four_value < t_ssi_config, e_ssi_config, sz_echomsg, sz_errmsg, sz_sizefmt, sz_timefmt >
{ using four_value < t_ssi_config, e_ssi_config, sz_echomsg, sz_errmsg, sz_sizefmt, sz_timefmt > :: four_value; };

template < > struct type_master < t_ssi_set > : four_value < t_ssi_set, e_ssi_set, sz_decoding, sz_encoding, sz_value, sz_var >
{ using four_value < t_ssi_set, e_ssi_set, sz_decoding, sz_encoding, sz_value, sz_var > :: four_value; };

template < > struct type_master < t_svg_baseprofile > : four_value < t_svg_baseprofile, e_svg_baseprofile, sz_basic, sz_full, sz_none, sz_tiny >
{ using four_value < t_svg_baseprofile, e_svg_baseprofile, sz_basic, sz_full, sz_none, sz_tiny > :: four_value; };

template < > struct type_master < t_syncbehaviour > : four_value < t_syncbehaviour, e_syncbehaviour, sz_canslip, sz_locked, sz_independent, sz_default >
{ using four_value < t_syncbehaviour, e_syncbehaviour, sz_canslip, sz_locked, sz_independent, sz_default > :: four_value; };

template < > struct type_master < t_syncbehaviourdefault > : four_value < t_syncbehaviourdefault, e_syncbehaviourdefault, sz_canslip, sz_locked, sz_independent, sz_inherit >
{ using four_value < t_syncbehaviourdefault, e_syncbehaviourdefault, sz_canslip, sz_locked, sz_independent, sz_inherit > :: four_value; };

template < > struct type_master < t_tfmu > : four_value < t_tfmu, e_tfmu, sz_false, sz_mixed, sz_true, sz_undefined >
{ using four_value < t_tfmu, e_tfmu, sz_false, sz_mixed, sz_true, sz_undefined > :: four_value; };

template < > struct type_master < t_uplr > : four_value < t_uplr, e_uplr, sz_down, sz_left, sz_right, sz_up >
{ using four_value < t_uplr, e_uplr, sz_down, sz_left, sz_right, sz_up > :: four_value; };

template < > struct type_master < t_valign3 > : four_value < t_valign3, e_valign3, sz_top, sz_middle, sz_bottom, sz_baseline >
{ using four_value < t_valign3, e_valign3, sz_top, sz_middle, sz_bottom, sz_baseline > :: four_value; };

template < > struct type_master < t_visibility11 > : four_value < t_visibility11, e_visibility11, sz_visible, sz_hidden, sz_collapse, sz_inherit >
{ using four_value < t_visibility11, e_visibility11, sz_visible, sz_hidden, sz_collapse, sz_inherit > :: four_value; };

template < > struct type_master < t_xsdbool > : four_value < t_xsdbool, e_xsdbool, sz_0, sz_1, sz_false, sz_true >
{ using four_value < t_xsdbool, e_xsdbool, sz_0, sz_1, sz_false, sz_true > :: four_value; };


template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: get_string () const
{   if (! type_base < base_type, TYPE > :: unknown ())
        switch (static_cast <int> (value_))
        {   case 0 : return SZ0::sz ();
            case 1 : return SZ1::sz ();
            case 2 : return SZ2::sz ();
            case 3 : return SZ3::sz ();
            default : break; }
    return ::std::string (); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    void four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string pret (trim_the_lot_off (s));
    ::std::string t (case_must_match < false >::lower (pret));
    type_base < base_type, TYPE > :: status (s_good);
    if (a_.empty ())
    {   a_ = ::boost::to_lower_copy (::std::string (SZ0::sz ()));
        b_ = ::boost::to_lower_copy (::std::string (SZ1::sz ()));
        c_ = ::boost::to_lower_copy (::std::string (SZ2::sz ()));
        d_ = ::boost::to_lower_copy (::std::string (SZ3::sz ())); }
    if (t == a_) value_ = static_cast <base_type> (0);
    else if (t == b_) value_ = static_cast <base_type> (1);
    else if (t == c_) value_ = static_cast <base_type> (2);
    else if (t == d_) value_ = static_cast <base_type> (3);
    else
    {   if (! check_spelling (nits, v, t))
            if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "attribute cannot have an empty value");
            else nits.pick (nit_unrecognised_value, es_error, ec_type, quote (pret), " is invalid; it can be \"", SZ0::sz (), "\", \"", SZ1::sz (), "\", \"", SZ2::sz (), "\", or \"", SZ3::sz (), "\"");
        type_base < base_type, TYPE > :: status (s_invalid);
        return; }
    compare_validate (nits, v, get_string (), pret); }

template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: a_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: b_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: c_;
template < e_type TYPE, typename base_type, class SZ0, class SZ1, class SZ2, class SZ3 >
    ::std::string four_value < TYPE, base_type, SZ0, SZ1, SZ2, SZ3 > :: d_;
