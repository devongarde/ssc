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
#include "css/typed_property.h"
#include "main/enum.h"

typedef typed_property < t_css_addsyms, ec_additive_symbols > desc_additive_symbols;
typedef typed_property < t_real, ec_ascent > desc_ascent;
typedef typed_property < t_percent_flexible, ec_ascent_override > desc_ascent_override;
typedef typed_property < t_percents_n, ec_ascent_override > desc_ascent_override_5;
typedef typed_property < t_css_background, ec_background > desc_background;
typedef typed_property < t_css_background_attachments, ec_background_attachment > desc_background_attachment;
typedef typed_property < t_css_col, ec_background_colour > desc_background_colour;
typedef typed_property < t_css_image, ec_background_image > desc_background_image;
typedef typed_property < t_css_background_position_3, ec_background_position > desc_background_position;
typedef typed_property < t_css_background_repeat_3, ec_background_repeat > desc_background_repeat;
typedef typed_property < t_real, ec_baseline > desc_baseline;
typedef typed_property < t_css_base_palette, ec_base_palette > desc_base_palette;
typedef typed_property < t_reals, ec_bbox > desc_bbox;
typedef typed_property < t_css_length_a, ec_bleed > desc_bleed;
typedef typed_property < t_css_border_wsc_i, ec_border > desc_border;
typedef typed_property < t_css_border_wsc_i, ec_border_bottom > desc_border_bottom;
typedef typed_property < t_css_col, ec_border_bottom_colour > desc_border_bottom_colour;
typedef typed_property < t_css_border_style, ec_border_bottom_style > desc_border_bottom_style;
typedef typed_property < t_css_border_measure, ec_border_bottom_width > desc_border_bottom_width;
typedef typed_property < t_css_border_wsc_i, ec_border_left > desc_border_left;
typedef typed_property < t_css_col, ec_border_left_colour > desc_border_left_colour;
typedef typed_property < t_css_border_style, ec_border_left_style > desc_border_left_style;
typedef typed_property < t_css_border_measure, ec_border_left_width > desc_border_left_width;
typedef typed_property < t_css_border_wsc_i, ec_border_right > desc_border_right;
typedef typed_property < t_css_col, ec_border_right_colour > desc_border_right_colour;
typedef typed_property < t_css_border_style, ec_border_right_style > desc_border_right_style;
typedef typed_property < t_css_border_measure, ec_border_right_width > desc_border_right_width;
typedef typed_property < t_css_border_wsc_i, ec_border_top > desc_border_top;
typedef typed_property < t_css_col, ec_border_top_colour > desc_border_top_colour;
typedef typed_property < t_css_border_style, ec_border_top_style > desc_border_top_style;
typedef typed_property < t_css_border_measure, ec_border_top_width > desc_border_top_width;
typedef typed_property < t_css_borders_measure_l, ec_border_width > desc_border_width;
typedef typed_property < t_real, ec_cap_height > desc_cap_height;
typedef typed_property < t_real, ec_centre_line > desc_centre_line;
typedef typed_property < t_css_col, ec_colour > desc_colour;
typedef typed_property < t_css_content, ec_content > desc_content;
typedef typed_property < t_css_counter_set, ec_counter_increment > desc_counter_increment;
typedef typed_property < t_css_counter_set, ec_counter_reset > desc_counter_reset;
typedef typed_property < t_css_url, ec_definition_src > desc_definition_src;
typedef typed_property < t_real, ec_descent > desc_descent;
typedef typed_property < t_percent_flexible, ec_descent_override > desc_descent_override;
typedef typed_property < t_percents_n, ec_descent_override > desc_descent_override_5;
typedef typed_property < t_svg_direction, ec_direction > desc_direction;
typedef typed_property < t_css_counter_style_name, ec_fallback > desc_fallback;
typedef typed_property < t_css_font, ec_font > desc_font;
typedef typed_property < t_css_font_display, ec_font_display > desc_font_display;
typedef typed_property < t_css_font_families, ec_font_family > desc_font_family;
typedef typed_property < t_css_font_feature_settings, ec_font_feature_settings > desc_font_feature_settings;
typedef typed_property < t_lang_n, ec_font_language_override > desc_font_language_override;
typedef typed_property < t_generic, ec_font_named_instance > desc_font_named_instance;
typedef typed_property < t_measures_all, ec_font_size > desc_font_size;
typedef typed_property < t_svg_fontstretch, ec_font_stretch > desc_font_stretch;
typedef typed_property < t_css_font_style_2, ec_font_style > desc_font_style;
typedef typed_property < t_svg_fontvariant, ec_font_variant > desc_font_variant;
typedef typed_property < t_css_font_variation_settings, ec_font_variation_settings > desc_font_variation_settings;
typedef typed_property < t_css_font_weights, ec_font_weight > desc_font_weight;
typedef typed_property < t_css_length_2, ec_height > desc_height;
typedef typed_property < t_css_length_xtz, ec_height > desc_vp_height;
typedef typed_property < t_css_length_n, ec_letter_spacing > desc_letter_spacing;
typedef typed_property < t_percent_flexible, ec_line_gap_override > desc_line_gap_override;
typedef typed_property < t_percents_n, ec_line_gap_override > desc_line_gap_override_5;
typedef typed_property < t_css_line_height, ec_line_height > desc_line_height;
typedef typed_property < t_css_margins_l, ec_margin > desc_margin;
typedef typed_property < t_measure_ai, ec_margin_bottom > desc_margin_bottom;
typedef typed_property < t_measure_ai, ec_margin_left > desc_margin_left;
typedef typed_property < t_measure_ai, ec_margin_right > desc_margin_right;
typedef typed_property < t_measure_ai, ec_margin_top > desc_margin_top;
typedef typed_property < t_css_marx, ec_marks > desc_marks;
typedef typed_property < t_real, ec_mathline > desc_mathline;
typedef typed_property < t_css_length_a, ec_max_height > desc_max_height;
typedef typed_property < t_css_length_a, ec_max_width > desc_max_width;
typedef typed_property < t_real_perflex, ec_max_zoom > desc_max_zoom;
typedef typed_property < t_css_length_a, ec_min_height > desc_min_height;
typedef typed_property < t_css_length_a, ec_min_width > desc_min_width;
typedef typed_property < t_real_perflex, ec_min_zoom > desc_min_zoom;
typedef typed_property < t_text_2, ec_negative > desc_negative;
typedef typed_property < t_alp, ec_orientation > desc_orientation;
typedef typed_property < t_css_override_colours, ec_override_colours > desc_override_colours;
typedef typed_property < t_css_outline_i, ec_outline > desc_outline;
typedef typed_property < t_css_col, ec_outline_colour > desc_outline_colour;
typedef typed_property < t_css_outline_style, ec_outline_style > desc_outline_style;
typedef typed_property < t_css_border_width_i, ec_outline_width > desc_outline_width;
typedef typed_property < t_css_overflows, ec_overflow > desc_overflow;
typedef typed_property < t_css_addsym, ec_pad > desc_pad;
typedef typed_property < t_measures_l, ec_padding > desc_padding;
typedef typed_property < t_measure_i, ec_padding_bottom > desc_padding_bottom;
typedef typed_property < t_measure_i, ec_padding_left > desc_padding_left;
typedef typed_property < t_measure_i, ec_padding_right > desc_padding_right;
typedef typed_property < t_measure_i, ec_padding_top > desc_padding_top;
typedef typed_property < t_rotate_upright, ec_page_orientation > desc_page_orientation;
typedef typed_property < t_10_int, ec_panose_1 > desc_panose_1;
typedef typed_property < t_text, ec_prefix > desc_prefix;
typedef typed_property < t_4string_ni, ec_quotes > desc_quotes;
typedef typed_property < t_css_range_a, ec_range > desc_range;
typedef typed_property < t_percent, ec_size_adjust > desc_size_adjust;
typedef typed_property < t_real, ec_slope > desc_slope;
typedef typed_property < t_css_size_3, ec_size > desc_size;
typedef typed_property < t_css_speak_as, ec_speak_as > desc_speak_as;
typedef typed_property < t_css_srcs, ec_src > desc_src;
typedef typed_property < t_real, ec_stemh > desc_stemh;
typedef typed_property < t_real, ec_stemv > desc_stemv;
typedef typed_property < t_text, ec_suffix > desc_suffix;
typedef typed_property < t_texts, ec_symbols > desc_symbols;
typedef typed_property < t_css_system, ec_system > desc_system;
typedef typed_property < t_percents_nf, ec_subscript_position_override > desc_subscript_position_override;
typedef typed_property < t_percents_nf, ec_superscript_position_override > desc_superscript_position_override;
typedef typed_property < t_percents_nf, ec_subscript_size_override > desc_subscript_size_override;
typedef typed_property < t_percents_nf, ec_superscript_size_override > desc_superscript_size_override;
typedef typed_property < t_css_text_align_4, ec_text_align > desc_text_align;
typedef typed_property < t_css_textdec_short, ec_text_decoration > desc_text_decoration;
typedef typed_property < t_css_texts_indent, ec_text_indent > desc_text_indent;
typedef typed_property < t_css_text_transform_n, ec_text_transform > desc_text_transform;
typedef typed_property < t_real, ec_topline > desc_topline;
typedef typed_property < t_unicode_bidi, ec_unicode_bidi > desc_unicode_bidi;
typedef typed_property < t_css_unicode_ranges, ec_unicode_range > desc_unicode_range;
typedef typed_property < t_real, ec_units_per_em > desc_units_per_em;
typedef typed_property < t_fixed_zoom, ec_user_zoom > desc_user_zoom;
typedef typed_property < t_css_vertal_2, ec_vertical_align > desc_vertical_align;
typedef typed_property < t_auto_contain_cover, ec_viewport_fit > desc_viewport_fit;
typedef typed_property < t_visibility11, ec_visibility > desc_visibility;
typedef typed_property < t_css_whitespace_2, ec_white_space > desc_white_space;
typedef typed_property < t_css_length_2, ec_width > desc_width;
typedef typed_property < t_css_length_xtz, ec_width > desc_vp_width;
typedef typed_property < t_generic, ec_widths > desc_widths;
typedef typed_property < t_css_length_n, ec_word_spacing > desc_word_spacing;
typedef typed_property < t_real, ec_x_height > desc_x_height;
typedef typed_property < t_integer_ai, ec_z_index > desc_z_index;
typedef typed_property < t_real_perflex, ec_zoom > desc_zoom;
typedef typed_property < t_unknown, ec_unknown > desc_unknown;

#define COUNTER_DESCRIPTORS \
    desc_additive_symbols, \
    desc_negative, \
    desc_fallback, \
    desc_pad, \
    desc_prefix, \
    desc_range, \
    desc_speak_as, \
    desc_suffix, \
    desc_symbols, \
    desc_system

#define DESCRIPTORS_2 \
    desc_baseline, \
    desc_bbox, \
    desc_cap_height, \
    desc_centre_line, \
    desc_definition_src, \
    desc_descent, \
    desc_font_family, \
    desc_font_size, \
    desc_font_stretch, \
    desc_font_style, \
    desc_font_variant, \
    desc_font_weight, \
    desc_mathline, \
    desc_panose_1, \
    desc_slope, \
    desc_src, \
    desc_stemh, \
    desc_stemv, \
    desc_topline, \
    desc_unicode_range, \
    desc_units_per_em, \
    desc_widths, \
    desc_x_height

#define DESCRIPTORS_3 \
    desc_font_family, \
    desc_font_feature_settings, \
    desc_font_stretch, \
    desc_font_style, \
    desc_font_weight, \
    desc_src, \
    desc_unicode_range

#define DESCRIPTORS_4_BASE \
    DESCRIPTORS_3, \
    desc_font_display, \
    desc_font_language_override, \
    desc_font_named_instance, \
    desc_font_variation_settings

#define DESCRIPTORS_4 \
    DESCRIPTORS_4_BASE, \
    desc_ascent_override, \
    desc_descent_override, \
    desc_line_gap_override

#define DESCRIPTORS_5 \
    DESCRIPTORS_4_BASE, \
    desc_ascent_override_5, \
    desc_descent_override_5, \
    desc_line_gap_override_5, \
    desc_size_adjust, \
    desc_subscript_position_override, \
    desc_superscript_position_override, \
    desc_subscript_size_override, \
    desc_superscript_size_override

#define FEATURE_DESCRIPTORS \
    desc_font_display

#define PAGE_2_1_DESCRIPTORS \
    desc_margin, \
    desc_margin_bottom, \
    desc_margin_left, \
    desc_margin_right, \
    desc_margin_top

#define PAGE_2_0_DESCRIPTORS \
    PAGE_2_1_DESCRIPTORS, \
    desc_marks, \
    desc_size

#define PAGE_3_BASE \
    PAGE_2_1_DESCRIPTORS, \
    desc_background, \
    desc_background_attachment, \
    desc_background_colour, \
    desc_background_image, \
    desc_background_position, \
    desc_background_repeat, \
    desc_border, \
    desc_border_bottom, \
    desc_border_bottom_colour, \
    desc_border_bottom_style, \
    desc_border_bottom_width, \
    desc_border_left, \
    desc_border_left_colour, \
    desc_border_left_style, \
    desc_border_left_width, \
    desc_border_right, \
    desc_border_right_colour, \
    desc_border_right_style, \
    desc_border_right_width, \
    desc_border_top, \
    desc_border_top_colour, \
    desc_border_top_style, \
    desc_border_top_width, \
    desc_border_width, \
    desc_colour, \
    desc_counter_increment, \
    desc_counter_reset, \
    desc_direction, \
    desc_font, \
    desc_font_family, \
    desc_font_size, \
    desc_font_style, \
    desc_font_weight, \
    desc_font_variant, \
    desc_height, \
    desc_letter_spacing, \
    desc_line_height, \
    desc_marks, \
    desc_max_height, \
    desc_max_width, \
    desc_min_height, \
    desc_max_height, \
    desc_outline, \
    desc_outline_colour, \
    desc_outline_style, \
    desc_outline_width, \
    desc_padding, \
    desc_padding_bottom, \
    desc_padding_left, \
    desc_padding_right, \
    desc_padding_top, \
    desc_quotes, \
    desc_text_align, \
    desc_text_decoration, \
    desc_text_indent, \
    desc_text_transform, \
    desc_white_space, \
    desc_width, \
    desc_word_spacing

#define PAGE_3_DESCRIPTORS \
    PAGE_3_BASE, \
    desc_bleed, \
    desc_marks, \
    desc_page_orientation

#define MARGIN_DESCRIPTORS \
    PAGE_3_BASE, \
    desc_content, \
    desc_overflow, \
    desc_unicode_bidi, \
    desc_vertical_align, \
    desc_visibility, \
    desc_z_index

#define PALETTE_DESCRIPTORS \
    desc_base_palette, \
    desc_font_family, \
    desc_override_colours

#define VIEWPORT_DESCRIPTORS \
    desc_vp_height, \
    desc_max_height, \
    desc_max_width, \
    desc_max_zoom, \
    desc_min_height, \
    desc_min_width, \
    desc_min_zoom, \
    desc_orientation, \
    desc_user_zoom, \
    desc_viewport_fit, \
    desc_vp_width, \
    desc_zoom
