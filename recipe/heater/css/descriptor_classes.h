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
typedef typed_property < t_real, ec_baseline > desc_baseline;
typedef typed_property < t_css_base_palette, ec_base_palette > desc_base_palette;
typedef typed_property < t_reals, ec_bbox > desc_bbox;
typedef typed_property < t_real, ec_cap_height > desc_cap_height;
typedef typed_property < t_real, ec_centre_line > desc_centre_line;
typedef typed_property < t_css_url, ec_definition_src > desc_definition_src;
typedef typed_property < t_real, ec_descent > desc_descent;
typedef typed_property < t_percent_flexible, ec_descent_override > desc_descent_override;
typedef typed_property < t_percents_n, ec_descent_override > desc_descent_override_5;
typedef typed_property < t_css_counter_style_name, ec_fallback > desc_fallback;
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
typedef typed_property < t_percent_flexible, ec_line_gap_override > desc_line_gap_override;
typedef typed_property < t_percents_n, ec_line_gap_override > desc_line_gap_override_5;
typedef typed_property < t_real, ec_mathline > desc_mathline;
typedef typed_property < t_text_2, ec_negative > desc_negative;
typedef typed_property < t_css_override_colours, ec_override_colours > desc_override_colours;
typedef typed_property < t_css_addsym, ec_pad > desc_pad;
typedef typed_property < t_10_int, ec_panose_1 > desc_panose_1;
typedef typed_property < t_text, ec_prefix > desc_prefix;
typedef typed_property < t_css_range_a, ec_range > desc_range;
typedef typed_property < t_percent, ec_size_adjust > desc_size_adjust;
typedef typed_property < t_real, ec_slope > desc_slope;
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
typedef typed_property < t_real, ec_topline > desc_topline;
typedef typed_property < t_css_unicode_ranges, ec_unicode_range > desc_unicode_range;
typedef typed_property < t_real, ec_units_per_em > desc_units_per_em;
typedef typed_property < t_generic, ec_widths > desc_widths;
typedef typed_property < t_real, ec_x_height > desc_x_height;
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

#define PALETTE_DESCRIPTORS \
    desc_base_palette, \
    desc_font_family, \
    desc_override_colours
