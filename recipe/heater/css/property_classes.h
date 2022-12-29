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
#include "type/enum.h"

typedef typed_property < t_unknown, ec_unknown > prop_unknown;
typedef typed_property < t_generic, ec_context > prop_context;
typedef typed_property < t_css_background, ec_background > prop_background;
typedef typed_property < t_css_background_attachment, ec_background_attachment > prop_background_attachment;
typedef typed_property < t_colour_trans, ec_background_colour > prop_background_colour;
typedef typed_property < t_css_image, ec_background_image > prop_background_image;
typedef typed_property < t_css_background_position, ec_background_position > prop_background_position;
typedef typed_property < t_css_background_repeat, ec_background_repeat > prop_background_repeat;
typedef typed_property < t_css_border_wsc, ec_border > prop_border;
typedef typed_property < t_css_border_wsc, ec_border_bottom > prop_border_bottom;
typedef typed_property < t_colour, ec_border_bottom_colour > prop_border_bottom_colour;
typedef typed_property < t_css_border_style, ec_border_bottom_style > prop_border_bottom_style;
typedef typed_property < t_css_border_measure, ec_border_bottom_width > prop_border_bottom_width;
typedef typed_property < t_colour, ec_border_colour > prop_border_colour;
typedef typed_property < t_css_border_wsc, ec_border_left > prop_border_left;
typedef typed_property < t_colour, ec_border_left_colour > prop_border_left_colour;
typedef typed_property < t_css_border_style, ec_border_left_style > prop_border_left_style;
typedef typed_property < t_css_border_measure, ec_border_left_width > prop_border_left_width;
typedef typed_property < t_css_border_wsc, ec_border_right > prop_border_right;
typedef typed_property < t_colour, ec_border_right_colour > prop_border_right_colour;
typedef typed_property < t_css_border_style, ec_border_right_style > prop_border_right_style;
typedef typed_property < t_css_border_measure, ec_border_right_width > prop_border_right_width;
typedef typed_property < t_css_border_styles, ec_border_style > prop_border_style;
typedef typed_property < t_css_border_wsc, ec_border_top > prop_border_top;
typedef typed_property < t_colour, ec_border_top_colour > prop_border_top_colour;
typedef typed_property < t_css_border_style, ec_border_top_style > prop_border_top_style;
typedef typed_property < t_css_border_measure, ec_border_top_width > prop_border_top_width;
typedef typed_property < t_css_borders_measure, ec_border_width > prop_border_width;
typedef typed_property < t_css_clear, ec_clear > prop_clear;
typedef typed_property < t_generic, ec_clip > prop_clip;
typedef typed_property < t_colour, ec_colour > prop_colour;
typedef typed_property < t_generic, ec_content > prop_content;
typedef typed_property < t_generic, ec_direction > prop_direction;
typedef typed_property < t_css_display, ec_display > prop_display;
typedef typed_property < t_generic, ec_error > prop_error;
typedef typed_property < t_lrnalign, ec_float > prop_float;
typedef typed_property < t_font, ec_font > prop_font;
typedef typed_property < t_font_families, ec_font_family > prop_font_family;
typedef typed_property < t_css_font_size, ec_font_size > prop_font_size;
typedef typed_property < t_fontstyle, ec_font_style > prop_font_style;
typedef typed_property < t_fontvariant, ec_font_variant > prop_font_variant;
typedef typed_property < t_fontweight, ec_font_weight > prop_font_weight;
typedef typed_property < t_css_length_auto, ec_height > prop_height;
typedef typed_property < t_generic, ec_inherit > prop_inherit;
typedef typed_property < t_css_spacing, ec_letter_spacing > prop_letter_spacing;
typedef typed_property < t_css_line_height, ec_line_height > prop_line_height;
typedef typed_property < t_css_list_style, ec_list_style > prop_list_style;
typedef typed_property < t_css_image, ec_list_style_image > prop_list_style_image;
typedef typed_property < t_css_list_style_position, ec_list_style_position > prop_list_style_position;
typedef typed_property < t_css_list_style_type, ec_list_style_type > prop_list_style_type;
typedef typed_property < t_css_margins, ec_margin > prop_margin;
typedef typed_property < t_measure_a, ec_margin_bottom > prop_margin_bottom;
typedef typed_property < t_measure_a, ec_margin_left > prop_margin_left;
typedef typed_property < t_measure_a, ec_margin_right > prop_margin_right;
typedef typed_property < t_measure_a, ec_margin_top > prop_margin_top;
typedef typed_property < t_generic, ec_max_height > prop_max_height;
typedef typed_property < t_generic, ec_max_width > prop_max_width;
typedef typed_property < t_generic, ec_min_height > prop_min_height;
typedef typed_property < t_generic, ec_min_width > prop_min_width;
typedef typed_property < t_generic, ec_overflow > prop_overflow;
typedef typed_property < t_measures, ec_padding > prop_padding;
typedef typed_property < t_measure, ec_padding_bottom > prop_padding_bottom;
typedef typed_property < t_measure, ec_padding_left > prop_padding_left;
typedef typed_property < t_measure, ec_padding_right > prop_padding_right;
typedef typed_property < t_measure, ec_padding_top > prop_padding_top;
typedef typed_property < t_generic, ec_position > prop_position;
typedef typed_property < t_align2070, ec_text_align > prop_text_align;
typedef typed_property < t_css_text_decoration, ec_text_decoration > prop_text_decoration;
typedef typed_property < t_measure, ec_text_indent > prop_text_indent;
typedef typed_property < t_css_text_transform, ec_text_transform > prop_text_transform;
typedef typed_property < t_generic, ec_unicode_bidi > prop_unicode_bidi;
typedef typed_property < t_css_vertical_align, ec_vertical_align > prop_vertical_align;
typedef typed_property < t_generic, ec_visibility > prop_visibility;
typedef typed_property < t_css_whitespace, ec_white_space > prop_white_space;
typedef typed_property < t_measure_a, ec_width > prop_width;
typedef typed_property < t_css_spacing, ec_word_spacing > prop_word_spacing;
typedef typed_property < t_generic, ec_z_index > prop_z_index;

#define PROPERTIES \
    prop_background, \
    prop_background_attachment, \
    prop_background_colour, \
    prop_background_image, \
    prop_background_position, \
    prop_background_repeat, \
    prop_border, \
    prop_border_bottom, \
    prop_border_bottom_colour, \
    prop_border_bottom_style, \
    prop_border_bottom_width, \
    prop_border_colour, \
    prop_border_left, \
    prop_border_left_colour, \
    prop_border_left_style, \
    prop_border_left_width, \
    prop_border_right, \
    prop_border_right_colour, \
    prop_border_right_style, \
    prop_border_right_width, \
    prop_border_style, \
    prop_border_top, \
    prop_border_top_colour, \
    prop_border_top_style, \
    prop_border_top_width, \
    prop_border_width, \
    prop_clear, \
    prop_clip, \
    prop_colour, \
    prop_content, \
    prop_context, \
    prop_direction, \
    prop_display, \
    prop_error, \
    prop_float, \
    prop_font, \
    prop_font_family, \
    prop_font_size, \
    prop_font_style, \
    prop_font_variant, \
    prop_font_weight, \
    prop_height, \
    prop_inherit, \
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
    prop_max_height, \
    prop_max_width, \
    prop_min_height, \
    prop_min_width, \
    prop_overflow, \
    prop_padding, \
    prop_padding_bottom, \
    prop_padding_left, \
    prop_padding_right, \
    prop_padding_top, \
    prop_position, \
    prop_text_align, \
    prop_text_decoration, \
    prop_text_indent, \
    prop_text_transform, \
    prop_unicode_bidi, \
    prop_vertical_align, \
    prop_visibility, \
    prop_white_space, \
    prop_width, \
    prop_word_spacing, \
    prop_z_index, \
    prop_unknown
