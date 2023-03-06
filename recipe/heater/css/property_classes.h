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

typedef typed_property < t_unknown, ec_unknown > prop_unknown;
typedef typed_property < t_generic, ec_context > prop_context;
typedef typed_property < t_real, ec_ascent > prop_ascent;
typedef typed_property < t_css_background, ec_background > prop_background;
typedef typed_property < t_css_azimuth, ec_azimuth > prop_azimuth;
typedef typed_property < t_css_background_attachment, ec_background_attachment > prop_background_attachment;
typedef typed_property < t_colour_trans, ec_background_colour > prop_background_colour;
typedef typed_property < t_css_image, ec_background_image > prop_background_image;
typedef typed_property < t_css_background_position, ec_background_position > prop_background_position;
typedef typed_property < t_css_background_repeat, ec_background_repeat > prop_background_repeat;
typedef typed_property < t_real, ec_baseline > prop_baseline;
typedef typed_property < t_generic, ec_bbox > prop_bbox;
typedef typed_property < t_css_border_wsc_i, ec_border > prop_border;
typedef typed_property < t_css_border_wsc_i, ec_border_bottom > prop_border_bottom;
typedef typed_property < t_colour_trans_i, ec_border_bottom_colour > prop_border_bottom_colour;
typedef typed_property < t_css_border_style, ec_border_bottom_style > prop_border_bottom_style;
typedef typed_property < t_css_border_measure, ec_border_bottom_width > prop_border_bottom_width;
typedef typed_property < t_css_border_collapse, ec_border_collapse > prop_border_collapse;
typedef typed_property < t_colour_trans_i, ec_border_colour > prop_border_colour;
typedef typed_property < t_css_border_wsc_i, ec_border_left > prop_border_left;
typedef typed_property < t_colour_trans_i, ec_border_left_colour > prop_border_left_colour;
typedef typed_property < t_css_border_style, ec_border_left_style > prop_border_left_style;
typedef typed_property < t_css_border_measure, ec_border_left_width > prop_border_left_width;
typedef typed_property < t_css_border_wsc_i, ec_border_right > prop_border_right;
typedef typed_property < t_colour_trans_i, ec_border_right_colour > prop_border_right_colour;
typedef typed_property < t_css_border_style, ec_border_right_style > prop_border_right_style;
typedef typed_property < t_css_border_measure, ec_border_right_width > prop_border_right_width;
typedef typed_property < t_css_border_spacing, ec_border_spacing > prop_border_spacing;
typedef typed_property < t_css_border_styles, ec_border_style > prop_border_style;
typedef typed_property < t_css_border_wsc_i, ec_border_top > prop_border_top;
typedef typed_property < t_colour_trans_i, ec_border_top_colour > prop_border_top_colour;
typedef typed_property < t_css_border_style, ec_border_top_style > prop_border_top_style;
typedef typed_property < t_css_border_measure, ec_border_top_width > prop_border_top_width;
typedef typed_property < t_css_borders_measure_i, ec_border_width > prop_border_width;
typedef typed_property < t_css_length_ai, ec_bottom > prop_bottom;
typedef typed_property < t_real, ec_cap_height > prop_cap_height;
typedef typed_property < t_tblri, ec_caption_side > prop_caption_side;
typedef typed_property < t_real, ec_centre_line > prop_centre_line;
typedef typed_property < t_css_clear, ec_clear > prop_clear;
typedef typed_property < t_css_rect_ai, ec_clip > prop_clip;
typedef typed_property < t_colour_i, ec_colour > prop_colour;
typedef typed_property < t_css_content, ec_content > prop_content;
typedef typed_property < t_css_counter_set, ec_counter_increment > prop_counter_increment;
typedef typed_property < t_css_counter_set, ec_counter_reset > prop_counter_reset;
typedef typed_property < t_css_cues, ec_cue > prop_cue;
typedef typed_property < t_css_cue, ec_cue_after > prop_cue_after;
typedef typed_property < t_css_cue, ec_cue_before > prop_cue_before;
typedef typed_property < t_css_cursor, ec_cursor > prop_cursor;
typedef typed_property < t_css_url, ec_definition_src > prop_definition_src;
typedef typed_property < t_real, ec_descent > prop_descent;
typedef typed_property < t_svg_direction, ec_direction > prop_direction;
typedef typed_property < t_css_display, ec_display > prop_display;
typedef typed_property < t_css_elevation, ec_elevation > prop_elevation;
typedef typed_property < t_css_empty_cells, ec_empty_cells > prop_empty_cells;
typedef typed_property < t_generic, ec_error > prop_error;
typedef typed_property < t_lrnialign, ec_float > prop_float;
typedef typed_property < t_css_font, ec_font > prop_font;
typedef typed_property < t_css_font_families, ec_font_family > prop_font_family;
typedef typed_property < t_css_font_size, ec_font_size > prop_font_size;
typedef typed_property < t_real_ni, ec_font_size_adjust > prop_font_size_adjust;
typedef typed_property < t_svg_fontstretch, ec_font_stretch > prop_font_stretch;
typedef typed_property < t_css_font_style, ec_font_style > prop_font_style;
typedef typed_property < t_svg_fontvariant, ec_font_variant > prop_font_variant;
typedef typed_property < t_css_font_weight, ec_font_weight > prop_font_weight;
typedef typed_property < t_css_length_ai, ec_height > prop_height;
typedef typed_property < t_generic, ec_inherit > prop_inherit;
typedef typed_property < t_css_length_ai, ec_left > prop_left;
typedef typed_property < t_css_spacing, ec_letter_spacing > prop_letter_spacing;
typedef typed_property < t_css_line_height, ec_line_height > prop_line_height;
typedef typed_property < t_css_list_style, ec_list_style > prop_list_style;
typedef typed_property < t_css_image, ec_list_style_image > prop_list_style_image;
typedef typed_property < t_css_list_style_position, ec_list_style_position > prop_list_style_position;
typedef typed_property < t_css_list_style_type, ec_list_style_type > prop_list_style_type;
typedef typed_property < t_css_margins, ec_margin > prop_margin;
typedef typed_property < t_measure_ai, ec_margin_bottom > prop_margin_bottom;
typedef typed_property < t_measure_ai, ec_margin_left > prop_margin_left;
typedef typed_property < t_measure_ai, ec_margin_right > prop_margin_right;
typedef typed_property < t_measure_ai, ec_margin_top > prop_margin_top;
typedef typed_property < t_css_marx, ec_marks > prop_marks;
typedef typed_property < t_real, ec_mathline > prop_mathline;
typedef typed_property < t_measure_in, ec_max_height > prop_max_height;
typedef typed_property < t_measure_in, ec_max_width > prop_max_width;
typedef typed_property < t_measure_i, ec_min_height > prop_min_height;
typedef typed_property < t_measure_i, ec_min_width > prop_min_width;
typedef typed_property < t_integer_i, ec_orphans > prop_orphans;
typedef typed_property < t_css_overflow, ec_overflow > prop_overflow;
typedef typed_property < t_css_outline_i, ec_outline > prop_outline;
typedef typed_property < t_colour_ii, ec_outline_colour > prop_outline_colour;
typedef typed_property < t_css_border_style_i, ec_outline_style > prop_outline_style;
typedef typed_property < t_css_border_width_i, ec_outline_width > prop_outline_width;
typedef typed_property < t_measures_i, ec_padding > prop_padding;
typedef typed_property < t_measure_i, ec_padding_bottom > prop_padding_bottom;
typedef typed_property < t_measure_i, ec_padding_left > prop_padding_left;
typedef typed_property < t_measure_i, ec_padding_right > prop_padding_right;
typedef typed_property < t_measure_i, ec_padding_top > prop_padding_top;
typedef typed_property < t_generic, ec_page_property > prop_page; // in code
typedef typed_property < t_css_aaalri, ec_page_break_after > prop_page_break_after;
typedef typed_property < t_css_aaalri, ec_page_break_before > prop_page_break_before;
typedef typed_property < t_css_aai, ec_page_break_inside > prop_page_break_inside;
typedef typed_property < t_10_int, ec_panose_1 > prop_panose_1;
typedef typed_property < t_css_pauses, ec_pause > prop_pause;
typedef typed_property < t_css_pause, ec_pause_after > prop_pause_after;
typedef typed_property < t_css_pause, ec_pause_before > prop_pause_before;
typedef typed_property < t_css_pitch, ec_pitch > prop_pitch;
typedef typed_property < t_real_i, ec_pitch_range > prop_pitch_range;
typedef typed_property < t_css_play_during, ec_play_during > prop_play_during;
typedef typed_property < t_css_position, ec_position > prop_position;
typedef typed_property < t_4string_ni, ec_quotes > prop_quotes;
typedef typed_property < t_real_i, ec_richness > prop_richness;
typedef typed_property < t_css_length_ai, ec_right > prop_right;
typedef typed_property < t_css_size, ec_size > prop_size;
typedef typed_property < t_real, ec_slope > prop_slope;
typedef typed_property < t_css_speak, ec_speak > prop_speak;
typedef typed_property < t_css_speak_header, ec_speak_header > prop_speak_header;
typedef typed_property < t_css_speak_numeral, ec_speak_numeral > prop_speak_numeral;
typedef typed_property < t_css_speak_punctuation, ec_speak_punctuation > prop_speak_punctuation;
typedef typed_property < t_css_speech_rate, ec_speech_rate > prop_speech_rate;
typedef typed_property < t_css_url, ec_src > prop_src;
typedef typed_property < t_real, ec_stemh > prop_stemh;
typedef typed_property < t_real, ec_stemv > prop_stemv;
typedef typed_property < t_real_i, ec_stress > prop_stress;
typedef typed_property < t_generic, ec_table_layout > prop_table_layout;
typedef typed_property < t_css_text_align, ec_text_align > prop_text_align;
typedef typed_property < t_css_text_decoration, ec_text_decoration > prop_text_decoration;
typedef typed_property < t_measure_i, ec_text_indent > prop_text_indent;
typedef typed_property < t_css_text_shadow, ec_text_shadow > prop_text_shadow;
typedef typed_property < t_css_text_transform, ec_text_transform > prop_text_transform;
typedef typed_property < t_css_length_ai, ec_top > prop_top;
typedef typed_property < t_real, ec_topline > prop_topline;
typedef typed_property < t_unicode_bidi, ec_unicode_bidi > prop_unicode_bidi;
typedef typed_property < t_generic, ec_unicode_range > prop_unicode_range;
typedef typed_property < t_real, ec_units_per_em > prop_units_per_em;
typedef typed_property < t_css_vertical_align, ec_vertical_align > prop_vertical_align;
typedef typed_property < t_visibility11, ec_visibility > prop_visibility;
typedef typed_property < t_css_voice_family, ec_voice_family > prop_voice_family;
typedef typed_property < t_css_volume, ec_volume > prop_volume;
typedef typed_property < t_css_whitespace, ec_white_space > prop_white_space;
typedef typed_property < t_integer_i, ec_widows > prop_widows;
typedef typed_property < t_css_length_ai, ec_width > prop_width;
typedef typed_property < t_generic, ec_widths > prop_widths;
typedef typed_property < t_css_spacing, ec_word_spacing > prop_word_spacing;
typedef typed_property < t_real, ec_x_height > prop_x_height;
typedef typed_property < t_integer_ai, ec_z_index > prop_z_index;

#define PROPERTIES \
    prop_ascent, \
    prop_azimuth, \
    prop_background, \
    prop_background_attachment, \
    prop_background_colour, \
    prop_background_image, \
    prop_background_position, \
    prop_background_repeat, \
    prop_baseline, \
    prop_bbox, \
    prop_border, \
    prop_border_bottom, \
    prop_border_bottom_colour, \
    prop_border_bottom_style, \
    prop_border_bottom_width, \
    prop_border_colour, \
    prop_border_left, \
    prop_border_collapse, \
    prop_border_left_colour, \
    prop_border_left_style, \
    prop_border_left_width, \
    prop_border_right, \
    prop_border_right_colour, \
    prop_border_right_style, \
    prop_border_right_width, \
    prop_border_spacing, \
    prop_border_style, \
    prop_border_top, \
    prop_border_top_colour, \
    prop_border_top_style, \
    prop_border_top_width, \
    prop_border_width, \
    prop_bottom, \
    prop_cap_height, \
    prop_caption_side, \
    prop_centre_line, \
    prop_clear, \
    prop_clip, \
    prop_colour, \
    prop_content, \
    prop_context, \
    prop_counter_increment, \
    prop_counter_reset, \
    prop_cue, \
    prop_cue_after, \
    prop_cue_before, \
    prop_cursor, \
    prop_definition_src, \
    prop_descent, \
    prop_direction, \
    prop_display, \
    prop_elevation, \
    prop_empty_cells, \
    prop_error, \
    prop_float, \
    prop_font, \
    prop_font_family, \
    prop_font_size, \
    prop_font_size_adjust, \
    prop_font_stretch, \
    prop_font_style, \
    prop_font_variant, \
    prop_font_weight, \
    prop_height, \
    prop_inherit, \
    prop_left, \
    prop_letter_spacing, \
    prop_line_height, \
    prop_list_style, \
    prop_list_style_image, \
    prop_list_style_position, \
    prop_list_style_type, \
    prop_margin, \
    prop_margin_bottom, \
    prop_margin_left, \
    prop_margin_right, \
    prop_margin_top, \
    prop_marks, \
    prop_mathline, \
    prop_max_height, \
    prop_max_width, \
    prop_min_height, \
    prop_min_width, \
    prop_orphans, \
    prop_overflow, \
    prop_outline, \
    prop_outline_colour, \
    prop_outline_style, \
    prop_outline_width, \
    prop_padding, \
    prop_padding_bottom, \
    prop_padding_left, \
    prop_padding_right, \
    prop_padding_top, \
    prop_page, \
    prop_page_break_after, \
    prop_page_break_before, \
    prop_page_break_inside, \
    prop_panose_1, \
    prop_pause, \
    prop_pause_after, \
    prop_pause_before, \
    prop_pitch, \
    prop_pitch_range, \
    prop_position, \
    prop_play_during, \
    prop_quotes, \
    prop_right, \
    prop_size, \
    prop_slope, \
    prop_speak, \
    prop_speak_header, \
    prop_speech_rate, \
    prop_stemh, \
    prop_stemv, \
    prop_table_layout, \
    prop_text_align, \
    prop_text_decoration, \
    prop_text_indent, \
    prop_text_shadow, \
    prop_text_transform, \
    prop_top, \
    prop_topline, \
    prop_unicode_bidi, \
    prop_unicode_range, \
    prop_units_per_em, \
    prop_vertical_align, \
    prop_visibility, \
    prop_voice_family, \
    prop_volume, \
    prop_white_space, \
    prop_widows, \
    prop_width, \
    prop_widths, \
    prop_word_spacing, \
    prop_x_height, \
    prop_z_index, \
    prop_unknown
