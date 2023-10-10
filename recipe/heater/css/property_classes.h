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

typedef typed_property < t_generic, ec_custom > prop_custom;

typedef typed_property < t_css_colour_a, ec_accent_colour > prop_accent_colour;
typedef typed_property < t_css_addsyms, ec_additive_symbols > prop_additive_symbols;
typedef typed_property < t_css_box_content_n, ec_align_content > prop_align_content;
typedef typed_property < t_css_box_alignitems_ns, ec_align_items > prop_align_items;
typedef typed_property < t_css_box_alignself_acs, ec_align_self > prop_align_self;
typedef typed_property < t_alignment_baseline, ec_alignment_baseline > prop_alignment_baseline;
typedef typed_property < t_css_all_2, ec_all > prop_all;
typedef typed_property < t_css_animation, ec_animation > prop_animation;
typedef typed_property < t_css_anim_comp, ec_animation_composition > prop_animation_composition;
typedef typed_property < t_datetime, ec_animation_delay > prop_animation_delay;
typedef typed_property < t_datetime, ec_animation_delay_end > prop_animation_delay_end;
typedef typed_property < t_datetime, ec_animation_delay_start > prop_animation_delay_start;
typedef typed_property < t_css_anim_dir, ec_animation_direction > prop_animation_direction;
typedef typed_property < t_datetime, ec_animation_duration > prop_animation_duration;
typedef typed_property < t_css_anim_fill_mode, ec_animation_fill_mode > prop_animation_fill_mode;
typedef typed_property < t_unsigned, ec_animation_iteration_count > prop_animation_iteration_count;
typedef typed_property < t_css_anim_name, ec_animation_name > prop_animation_name;
typedef typed_property < t_css_anim_play_state, ec_animation_play_state > prop_animation_play_state;
typedef typed_property < t_generic, ec_animation_range > prop_animation_range;
typedef typed_property < t_css_anim_timeline, ec_animation_timeline > prop_animation_timeline;
typedef typed_property < t_generic, ec_animation_timing_function > prop_animation_timing_function;
typedef typed_property < t_css_appearance, ec_appearance > prop_appearance;
typedef typed_property < t_real, ec_ascent > prop_ascent;
typedef typed_property < t_percent_flexible, ec_ascent_override > prop_ascent_override;
typedef typed_property < t_generic, ec_aspect_ratio > prop_aspect_ratio;
typedef typed_property < t_css_azimuth, ec_azimuth > prop_azimuth;

typedef typed_property < t_visibility10, ec_backface_visibility > prop_backface_visibility;
typedef typed_property < t_css_background, ec_background > prop_background;
typedef typed_property < t_css_background_attachments, ec_background_attachment > prop_background_attachment;
typedef typed_property < t_css_blend_mode, ec_background_blend_mode > prop_background_blend_mode;
typedef typed_property < t_css_background_boxes, ec_background_clip > prop_background_clip;
typedef typed_property < t_css_col, ec_background_colour > prop_background_colour;
typedef typed_property < t_css_image, ec_background_image > prop_background_image;
typedef typed_property < t_css_background_boxes, ec_background_origin > prop_background_origin;
typedef typed_property < t_css_background_position_3, ec_background_position > prop_background_position;
typedef typed_property < t_css_background_repeat_3, ec_background_repeat > prop_background_repeat;
typedef typed_property < t_css_background_sizes, ec_background_size > prop_background_size;
typedef typed_property < t_real, ec_baseline > prop_baseline;
typedef typed_property < t_svg_baselineshift, ec_baseline_shift > prop_baseline_shift;
typedef typed_property < t_generic, ec_baseline_source > prop_baseline_source;
typedef typed_property < t_css_base_palette, ec_base_palette > prop_base_palette;
typedef typed_property < t_generic, ec_bbox > prop_bbox;
typedef typed_property < t_generic, ec_block_ellipsis > prop_block_ellipsis;
typedef typed_property < t_generic, ec_block_size > prop_block_size;
typedef typed_property < t_generic, ec_block_step > prop_block_step;
typedef typed_property < t_generic, ec_block_step_align > prop_block_step_align;
typedef typed_property < t_generic, ec_block_step_insert > prop_block_step_insert;
typedef typed_property < t_generic, ec_block_step_round > prop_block_step_round;
typedef typed_property < t_generic, ec_block_step_size > prop_block_step_size;
typedef typed_property < t_generic, ec_bookmark_label > prop_bookmark_label;
typedef typed_property < t_generic, ec_bookmark_level > prop_bookmark_level;
typedef typed_property < t_generic, ec_bookmark_state > prop_bookmark_state;
typedef typed_property < t_css_border_wsc_i, ec_border > prop_border;
typedef typed_property < t_generic, ec_border_block > prop_border_block;
typedef typed_property < t_css_col, ec_border_block_colour > prop_border_block_colour;
typedef typed_property < t_generic, ec_border_block_end > prop_border_block_end;
typedef typed_property < t_css_col, ec_border_block_end_colour > prop_border_block_end_colour;
typedef typed_property < t_generic, ec_border_block_end_style > prop_border_block_end_style;
typedef typed_property < t_generic, ec_border_block_end_width > prop_border_block_end_width;
typedef typed_property < t_generic, ec_border_block_start > prop_border_block_start;
typedef typed_property < t_css_col, ec_border_block_start_colour > prop_border_block_start_colour;
typedef typed_property < t_generic, ec_border_block_start_style > prop_border_block_start_style;
typedef typed_property < t_generic, ec_border_block_start_width > prop_border_block_start_width;
typedef typed_property < t_generic, ec_border_block_style > prop_border_block_style;
typedef typed_property < t_generic, ec_border_block_width > prop_border_block_width;
typedef typed_property < t_css_border_wsc_i, ec_border_bottom > prop_border_bottom;
typedef typed_property < t_css_col, ec_border_bottom_colour > prop_border_bottom_colour;
typedef typed_property < t_css_length_2, ec_border_bottom_left_radius > prop_border_bottom_left_radius;
typedef typed_property < t_css_length_2, ec_border_bottom_right_radius > prop_border_bottom_right_radius;
typedef typed_property < t_css_border_style, ec_border_bottom_style > prop_border_bottom_style;
typedef typed_property < t_css_border_measure, ec_border_bottom_width > prop_border_bottom_width;
typedef typed_property < t_generic, ec_border_boundary > prop_border_boundary;
typedef typed_property < t_css_border_collapse, ec_border_collapse > prop_border_collapse;
typedef typed_property < t_css_cols, ec_border_colour > prop_border_colour;
typedef typed_property < t_generic, ec_border_end_end_radius > prop_border_end_end_radius;
typedef typed_property < t_generic, ec_border_end_start_radius > prop_border_end_start_radius;
typedef typed_property < t_css_border_image, ec_border_image > prop_border_image;
typedef typed_property < t_css_lengths, ec_border_image_outset > prop_border_image_outset;
typedef typed_property < t_css_border_images_repeat, ec_border_image_repeat > prop_border_image_repeat;
typedef typed_property < t_css_border_image_slice, ec_border_image_slice > prop_border_image_slice;
typedef typed_property < t_css_border_image_src, ec_border_image_source > prop_border_image_source;
typedef typed_property < t_css_lengths_a, ec_border_image_width > prop_border_image_width;
typedef typed_property < t_generic, ec_border_inline > prop_border_inline;
typedef typed_property < t_css_col, ec_border_inline_colour > prop_border_inline_colour;
typedef typed_property < t_generic, ec_border_inline_end > prop_border_inline_end;
typedef typed_property < t_css_col, ec_border_inline_end_colour > prop_border_inline_end_colour;
typedef typed_property < t_generic, ec_border_inline_end_style > prop_border_inline_end_style;
typedef typed_property < t_generic, ec_border_inline_end_width > prop_border_inline_end_width;
typedef typed_property < t_generic, ec_border_inline_start > prop_border_inline_start;
typedef typed_property < t_css_col, ec_border_inline_start_colour > prop_border_inline_start_colour;
typedef typed_property < t_generic, ec_border_inline_start_style > prop_border_inline_start_style;
typedef typed_property < t_generic, ec_border_inline_start_width > prop_border_inline_start_width;
typedef typed_property < t_generic, ec_border_inline_style > prop_border_inline_style;
typedef typed_property < t_generic, ec_border_inline_width > prop_border_inline_width;
typedef typed_property < t_css_border_wsc_i, ec_border_left > prop_border_left;
typedef typed_property < t_css_col, ec_border_left_colour > prop_border_left_colour;
typedef typed_property < t_css_border_style, ec_border_left_style > prop_border_left_style;
typedef typed_property < t_css_border_measure, ec_border_left_width > prop_border_left_width;
typedef typed_property < t_css_border_radius, ec_border_radius > prop_border_radius;
typedef typed_property < t_css_border_wsc_i, ec_border_right > prop_border_right;
typedef typed_property < t_css_col, ec_border_right_colour > prop_border_right_colour;
typedef typed_property < t_css_border_style, ec_border_right_style > prop_border_right_style;
typedef typed_property < t_css_border_measure, ec_border_right_width > prop_border_right_width;
typedef typed_property < t_css_border_spacing, ec_border_spacing > prop_border_spacing;
typedef typed_property < t_generic, ec_border_start_end_radius > prop_border_start_end_radius;
typedef typed_property < t_generic, ec_border_start_start_radius > prop_border_start_start_radius;
typedef typed_property < t_css_border_styles, ec_border_style > prop_border_style;
typedef typed_property < t_css_border_wsc_i, ec_border_top > prop_border_top;
typedef typed_property < t_css_col, ec_border_top_colour > prop_border_top_colour;
typedef typed_property < t_css_length_2, ec_border_top_left_radius > prop_border_top_left_radius;
typedef typed_property < t_css_length_2, ec_border_top_right_radius > prop_border_top_right_radius;
typedef typed_property < t_css_border_style, ec_border_top_style > prop_border_top_style;
typedef typed_property < t_css_border_measure, ec_border_top_width > prop_border_top_width;
typedef typed_property < t_css_borders_measure_i, ec_border_width > prop_border_width;
typedef typed_property < t_css_length_ai, ec_bottom > prop_bottom;
typedef typed_property < t_css_break_box, ec_box_decoration_break > prop_box_decoration_break;
typedef typed_property < t_real, ec_box_flex > prop_box_flex;
typedef typed_property < t_css_box_orient, ec_box_orient > prop_box_orient;
typedef typed_property < t_css_box_shadows_n, ec_box_shadow > prop_box_shadow;
typedef typed_property < t_css_box_sizing, ec_box_sizing > prop_box_sizing;
typedef typed_property < t_generic, ec_box_snap > prop_box_snap;
typedef typed_property < t_css_break, ec_break_after > prop_break_after;
typedef typed_property < t_css_break, ec_break_before > prop_break_before;
typedef typed_property < t_css_break_inside, ec_break_inside > prop_break_inside;

typedef typed_property < t_real, ec_cap_height > prop_cap_height;
typedef typed_property < t_tblri, ec_caption_side > prop_caption_side;
typedef typed_property < t_css_caret, ec_caret > prop_caret;
typedef typed_property < t_css_colour_a, ec_caret_colour > prop_caret_colour;
typedef typed_property < t_css_caret_shape, ec_caret_shape > prop_caret_shape;
typedef typed_property < t_real, ec_centre_line > prop_centre_line;
typedef typed_property < t_generic, ec_chains > prop_chains;
typedef typed_property < t_css_clear, ec_clear > prop_clear;
typedef typed_property < t_css_rect_ai, ec_clip > prop_clip;
typedef typed_property < t_css_clip_path, ec_clip_path > prop_clip_path;
typedef typed_property < t_fill_rule, ec_clip_rule > prop_clip_rule;
typedef typed_property < t_generic, ec_colour_adjust > prop_colour_adjust;
typedef typed_property < t_colour_interpolation, ec_colour_interpolation > prop_colour_interpolation;
typedef typed_property < t_colour_interpolation, ec_colour_interpolation_filters > prop_colour_interpolation_filters;
typedef typed_property < t_svg_colour_profile, ec_colour_profile > prop_colour_profile;
typedef typed_property < t_colour_rendering, ec_colour_rendering > prop_colour_rendering;
typedef typed_property < t_generic, ec_colour_scheme > prop_colour_scheme;
typedef typed_property < t_css_col, ec_colour > prop_colour;
typedef typed_property < t_unsigned_1_more_a, ec_column_count > prop_column_count;
typedef typed_property < t_css_column_fill, ec_column_fill > prop_column_fill;
typedef typed_property < t_measure_ni, ec_column_gap > prop_column_gap;
typedef typed_property < t_css_column_rule, ec_column_rule > prop_column_rule;
typedef typed_property < t_css_col, ec_column_rule_colour > prop_column_rule_colour;
typedef typed_property < t_css_border_style, ec_column_rule_style > prop_column_rule_style;
typedef typed_property < t_css_border_measure, ec_column_rule_width > prop_column_rule_width;
typedef typed_property < t_all_none, ec_column_span > prop_column_span;
typedef typed_property < t_measure_a, ec_column_width > prop_column_width;
typedef typed_property < t_css_columns, ec_columns > prop_columns;
typedef typed_property < t_css_contain, ec_contain > prop_contain;
typedef typed_property < t_generic, ec_contain_intrinsic_block_size > prop_contain_intrinsic_block_size;
typedef typed_property < t_generic, ec_contain_intrinsic_height > prop_contain_intrinsic_height;
typedef typed_property < t_generic, ec_contain_intrinsic_inline_size > prop_contain_intrinsic_inline_size;
typedef typed_property < t_generic, ec_contain_intrinsic_size > prop_contain_intrinsic_size;
typedef typed_property < t_generic, ec_contain_intrinsic_width > prop_contain_intrinsic_width;
typedef typed_property < t_css_container, ec_container > prop_container;
typedef typed_property < t_css_container_name, ec_container_name > prop_container_name;
typedef typed_property < t_css_container_type, ec_container_type > prop_container_type;
typedef typed_property < t_css_content, ec_content > prop_content;
typedef typed_property < t_auto_hidden_visible, ec_content_visibility > prop_content_visibility;
typedef typed_property < t_generic, ec_context > prop_context;
typedef typed_property < t_generic, ec_continue > prop_continue;
typedef typed_property < t_css_counter_set, ec_counter_increment > prop_counter_increment;
typedef typed_property < t_css_counter_set, ec_counter_reset > prop_counter_reset;
typedef typed_property < t_generic, ec_counter_set > prop_counter_set;
typedef typed_property < t_css_cues, ec_cue > prop_cue;
typedef typed_property < t_css_cue, ec_cue_after > prop_cue_after;
typedef typed_property < t_css_cue, ec_cue_before > prop_cue_before;
typedef typed_property < t_css_cursor, ec_cursor > prop_cursor;
typedef typed_property < t_measure, ec_cx > prop_cx;
typedef typed_property < t_measure, ec_cy > prop_cy;

typedef typed_property < t_measure, ec_d > prop_d;
typedef typed_property < t_css_url, ec_definition_src > prop_definition_src;
typedef typed_property < t_real, ec_descent > prop_descent;
typedef typed_property < t_percent_flexible, ec_descent_override > prop_descent_override;
typedef typed_property < t_svg_direction, ec_direction > prop_direction;
typedef typed_property < t_css_display_1, ec_display > prop_display;
typedef typed_property < t_dominantbaseline, ec_dominant_baseline > prop_dominant_baseline;

typedef typed_property < t_css_elevation, ec_elevation > prop_elevation;
typedef typed_property < t_css_empty_cells, ec_empty_cells > prop_empty_cells;
typedef typed_property < t_enable_background, ec_enable_background > prop_enable_background;
typedef typed_property < t_generic, ec_error > prop_error;

typedef typed_property < t_css_counter_style_name, ec_fallback > prop_fallback;
typedef typed_property < t_fill_v, ec_fill > prop_fill;
typedef typed_property < t_generic, ec_fill_break > prop_fill_break;
typedef typed_property < t_css_col, ec_fill_colour > prop_fill_colour;
typedef typed_property < t_generic, ec_fill_image > prop_fill_image;
typedef typed_property < t_fill_opacity, ec_fill_opacity > prop_fill_opacity;
typedef typed_property < t_generic, ec_fill_origin > prop_fill_origin;
typedef typed_property < t_generic, ec_fill_position > prop_fill_position;
typedef typed_property < t_generic, ec_fill_repeat > prop_fill_repeat;
typedef typed_property < t_fill_rule, ec_fill_rule > prop_fill_rule;
typedef typed_property < t_generic, ec_fill_size > prop_fill_size;
typedef typed_property < t_css_filters_n, ec_filter > prop_filter;
typedef typed_property < t_css_flex, ec_flex > prop_flex;
typedef typed_property < t_css_flex_basis, ec_flex_basis > prop_flex_basis;
typedef typed_property < t_css_flex_direction, ec_flex_direction > prop_flex_direction;
typedef typed_property < t_css_flex_flow, ec_flex_flow > prop_flex_flow;
typedef typed_property < t_fixedpoint, ec_flex_grow > prop_flex_grow;
typedef typed_property < t_fixedpoint, ec_flex_shrink > prop_flex_shrink;
typedef typed_property < t_css_flex_wrap, ec_flex_wrap > prop_flex_wrap;
typedef typed_property < t_lrnialign, ec_float > prop_float;
typedef typed_property < t_generic, ec_float_defer > prop_float_defer;
typedef typed_property < t_generic, ec_float_offset > prop_float_offset;
typedef typed_property < t_generic, ec_float_reference > prop_float_reference;
typedef typed_property < t_css_col, ec_flood_colour > prop_flood_colour;
typedef typed_property < t_opacity, ec_flood_opacity > prop_flood_opacity;
typedef typed_property < t_generic, ec_flow > prop_flow;
typedef typed_property < t_generic, ec_flow_from > prop_flow_from;
typedef typed_property < t_generic, ec_flow_into > prop_flow_into;
typedef typed_property < t_css_font, ec_font > prop_font;
typedef typed_property < t_css_font_display, ec_font_display > prop_font_display;
typedef typed_property < t_css_font_families, ec_font_family > prop_font_family;
typedef typed_property < t_css_font_feature_settings, ec_font_feature_settings > prop_font_feature_settings;
typedef typed_property < t_css_font_kerning, ec_font_kerning > prop_font_kerning;
typedef typed_property < t_lang_n, ec_font_language_override > prop_font_language_override;
typedef typed_property < t_generic, ec_font_named_instance > prop_font_named_instance;
typedef typed_property < t_auto_none, ec_font_optical_sizing > prop_font_optical_sizing;
typedef typed_property < t_css_palette_nld, ec_font_palette > prop_font_palette;
typedef typed_property < t_css_font_size_4, ec_font_size > prop_font_size;
typedef typed_property < t_real_ni, ec_font_size_adjust > prop_font_size_adjust;
typedef typed_property < t_css_font_stretch, ec_font_stretch > prop_font_stretch;
typedef typed_property < t_css_font_style_a, ec_font_style > prop_font_style;
typedef typed_property < t_font_synthesis_n, ec_font_synthesis > prop_font_synthesis;
typedef typed_property < t_auto_none, ec_font_synthesis_small_caps > prop_font_synthesis_small_caps;
typedef typed_property < t_auto_none, ec_font_synthesis_style > prop_font_synthesis_style;
typedef typed_property < t_auto_none, ec_font_synthesis_weight > prop_font_synthesis_weight;
typedef typed_property < t_css_font_variant, ec_font_variant > prop_font_variant;
typedef typed_property < t_font_variant_alternatives, ec_font_variant_alternatives > prop_font_variant_alternates;
typedef typed_property < t_font_variant_caps, ec_font_variant_caps > prop_font_variant_caps;
typedef typed_property < t_font_variant_east_asians, ec_font_variant_east_asian > prop_font_variant_east_asian;
typedef typed_property < t_font_variant_emoji, ec_font_variant_emoji > prop_font_variant_emoji;
typedef typed_property < t_font_variant_ligatures, ec_font_variant_ligatures > prop_font_variant_ligatures;
typedef typed_property < t_font_variant_numerics, ec_font_variant_numeric > prop_font_variant_numeric;
typedef typed_property < t_font_variant_position, ec_font_variant_position > prop_font_variant_position;
typedef typed_property < t_css_font_variation_settings, ec_font_variation_settings > prop_font_variation_settings;
typedef typed_property < t_css_font_weights, ec_font_weight > prop_font_weight;
typedef typed_property < t_generic, ec_footnote_display > prop_footnote_display;
typedef typed_property < t_generic, ec_footnote_policy > prop_footnote_policy;
typedef typed_property < t_generic, ec_forced_colour_adjust > prop_forced_colour_adjust;

typedef typed_property < t_css_gap, ec_gap > prop_gap;
typedef typed_property < t_angle_i, ec_glyph_orientation_horizontal > prop_glyph_orientation_horizontal;
typedef typed_property < t_angle_ai, ec_glyph_orientation_vertical > prop_glyph_orientation_vertical;
typedef typed_property < t_css_grid, ec_grid > prop_grid;
typedef typed_property < t_css_grid_lines, ec_grid_area > prop_grid_area;
typedef typed_property < t_css_grid_track_sizes, ec_grid_auto_columns > prop_grid_auto_columns;
typedef typed_property < t_css_grid_auto_flow, ec_grid_auto_flow > prop_grid_auto_flow;
typedef typed_property < t_css_grid_track_sizes, ec_grid_auto_rows > prop_grid_auto_rows;
typedef typed_property < t_css_grid_lines, ec_grid_column > prop_grid_column;
typedef typed_property < t_css_grid_line, ec_grid_column_end > prop_grid_column_end;
typedef typed_property < t_css_grid_line, ec_grid_column_start > prop_grid_column_start;
typedef typed_property < t_css_grid_lines, ec_grid_row > prop_grid_row;
typedef typed_property < t_css_grid_line, ec_grid_row_end > prop_grid_row_end;
typedef typed_property < t_css_grid_line, ec_grid_row_start > prop_grid_row_start;
typedef typed_property < t_css_grid_templates, ec_grid_template > prop_grid_template;
typedef typed_property < t_texts_n, ec_grid_template_areas > prop_grid_template_areas;
typedef typed_property < t_css_grid_template, ec_grid_template_columns > prop_grid_template_columns;
typedef typed_property < t_css_grid_template, ec_grid_template_rows > prop_grid_template_rows;

typedef typed_property < t_generic, ec_hanging_punctuation > prop_hanging_punctuation;
typedef typed_property < t_css_length_amm, ec_height > prop_height;
typedef typed_property < t_generic, ec_hyphenate_character > prop_hyphenate_character;
typedef typed_property < t_generic, ec_hyphenate_limit_chars > prop_hyphenate_limit_chars;
typedef typed_property < t_generic, ec_hyphenate_limit_last > prop_hyphenate_limit_last;
typedef typed_property < t_generic, ec_hyphenate_limit_lines > prop_hyphenate_limit_lines;
typedef typed_property < t_generic, ec_hyphenate_limit_zone > prop_hyphenate_limit_zone;
typedef typed_property < t_generic, ec_hyphens > prop_hyphens;

typedef typed_property < t_css_image_processing, ec_image_orientation > prop_image_orientation;
typedef typed_property < t_image_rendering, ec_image_rendering > prop_image_rendering;
typedef typed_property < t_css_image_resolution, ec_image_resolution > prop_image_resolution;
typedef typed_property < t_generic, ec_ime_mode > prop_ime_mode;
typedef typed_property < t_generic, ec_inherit > prop_inherit;
typedef typed_property < t_generic, ec_initial_letter > prop_initial_letter;
typedef typed_property < t_generic, ec_initial_letter_align > prop_initial_letter_align;
typedef typed_property < t_generic, ec_initial_letter_wrap > prop_initial_letter_wrap;
typedef typed_property < t_measure, ec_inline_size > prop_inline_size;
typedef typed_property < t_generic, ec_inline_sizing > prop_inline_sizing;
typedef typed_property < t_css_lengths_a, ec_inset > prop_inset;
typedef typed_property < t_css_length_a2, ec_inset_block > prop_inset_block;
typedef typed_property < t_css_length_ai, ec_inset_block_end > prop_inset_block_end;
typedef typed_property < t_css_length_ai, ec_inset_block_start > prop_inset_block_start;
typedef typed_property < t_css_length_a2, ec_inset_inline > prop_inset_inline;
typedef typed_property < t_css_length_ai, ec_inset_inline_end > prop_inset_inline_end;
typedef typed_property < t_css_length_ai, ec_inset_inline_start > prop_inset_inline_start;
typedef typed_property < t_css_isolation, ec_isolation > prop_isolation;

typedef typed_property < t_css_box_justify_n, ec_justify_content > prop_justify_content;
typedef typed_property < t_css_box_justitems_ns, ec_justify_items > prop_justify_items;
typedef typed_property < t_css_box_justself, ec_justify_self > prop_justify_self;

typedef typed_property < t_measure_ai, ec_kerning > prop_kerning;

typedef typed_property < t_generic, ec_leading_trim > prop_leading_trim;
typedef typed_property < t_css_length_ai, ec_left > prop_left;
typedef typed_property < t_css_spacing, ec_letter_spacing > prop_letter_spacing;
typedef typed_property < t_css_col, ec_lighting_colour > prop_lighting_colour;
typedef typed_property < t_generic, ec_line_break > prop_line_break;
typedef typed_property < t_generic, ec_line_clamp > prop_line_clamp;
typedef typed_property < t_percent_flexible, ec_line_gap_override > prop_line_gap_override;
typedef typed_property < t_generic, ec_line_grid > prop_line_grid;
typedef typed_property < t_css_line_height, ec_line_height > prop_line_height;
typedef typed_property < t_generic, ec_line_height_step > prop_line_height_step;
typedef typed_property < t_generic, ec_line_padding > prop_line_padding;
typedef typed_property < t_generic, ec_line_snap > prop_line_snap;
typedef typed_property < t_css_list_style, ec_list_style > prop_list_style;
typedef typed_property < t_css_image, ec_list_style_image > prop_list_style_image;
typedef typed_property < t_css_list_style_position, ec_list_style_position > prop_list_style_position;
typedef typed_property < t_css_list_style_type_cs, ec_list_style_type > prop_list_style_type;

typedef typed_property < t_css_margins, ec_margin > prop_margin;
typedef typed_property < t_generic, ec_margin_block > prop_margin_block;
typedef typed_property < t_generic, ec_margin_block_end > prop_margin_block_end;
typedef typed_property < t_generic, ec_margin_block_start > prop_margin_block_start;
typedef typed_property < t_measure_ai, ec_margin_bottom > prop_margin_bottom;
typedef typed_property < t_css_margin_break, ec_margin_break > prop_margin_break;
typedef typed_property < t_generic, ec_margin_inline > prop_margin_inline;
typedef typed_property < t_generic, ec_margin_inline_end > prop_margin_inline_end;
typedef typed_property < t_generic, ec_margin_inline_start > prop_margin_inline_start;
typedef typed_property < t_measure_ai, ec_margin_left > prop_margin_left;
typedef typed_property < t_measure_ai, ec_margin_right > prop_margin_right;
typedef typed_property < t_measure_ai, ec_margin_top > prop_margin_top;
typedef typed_property < t_css_margin_trim, ec_margin_trim > prop_margin_trim;
typedef typed_property < t_marker, ec_marker > prop_marker;
typedef typed_property < t_marker, ec_marker_end > prop_marker_end;
typedef typed_property < t_generic, ec_marker_knockout_left > prop_marker_knockout_left;
typedef typed_property < t_generic, ec_marker_knockout_right > prop_marker_knockout_right;
typedef typed_property < t_marker, ec_marker_mid > prop_marker_mid;
typedef typed_property < t_css_length_a, ec_marker_offset > prop_marker_offset;
typedef typed_property < t_generic, ec_marker_pattern > prop_marker_pattern;
typedef typed_property < t_generic, ec_marker_segment > prop_marker_segment;
typedef typed_property < t_generic, ec_marker_side > prop_marker_side;
typedef typed_property < t_marker, ec_marker_start > prop_marker_start;
typedef typed_property < t_css_marx, ec_marks > prop_marks;
typedef typed_property < t_generic, ec_marquee_direction > prop_marquee_direction;
typedef typed_property < t_generic, ec_marquee_loop > prop_marquee_loop;
typedef typed_property < t_generic, ec_marquee_speed > prop_marquee_speed;
typedef typed_property < t_generic, ec_marquee_style > prop_marquee_style;
typedef typed_property < t_css_mask, ec_mask > prop_mask;
typedef typed_property < t_css_mask_border, ec_mask_border > prop_mask_border;
typedef typed_property < t_css_mask_border_mode, ec_mask_border_mode > prop_mask_border_mode;
typedef typed_property < t_css_mask_border_outsets, ec_mask_border_outset > prop_mask_border_outset;
typedef typed_property < t_css_mask_border_repeats, ec_mask_border_repeat > prop_mask_border_repeat;
typedef typed_property < t_css_mask_border_slice, ec_mask_border_slice > prop_mask_border_slice;
typedef typed_property < t_css_val_fn_n, ec_mask_border_source > prop_mask_border_source;
typedef typed_property < t_css_mask_border_widths, ec_mask_border_width > prop_mask_border_width;
typedef typed_property < t_css_clip_coord_boxen, ec_mask_clip > prop_mask_clip;
typedef typed_property < t_css_composites, ec_mask_composite > prop_mask_composite;
typedef typed_property < t_css_mask_refs, ec_mask_image > prop_mask_image;
typedef typed_property < t_css_masking_modes, ec_mask_mode > prop_mask_mode;
typedef typed_property < t_css_coord_boxen, ec_mask_origin > prop_mask_origin;
typedef typed_property < t_positions, ec_mask_position > prop_mask_position;
typedef typed_property < t_css_background_repeats, ec_mask_repeat > prop_mask_repeat;
typedef typed_property < t_css_background_sizes, ec_mask_size > prop_mask_size;
typedef typed_property < t_css_mask_border_mode, ec_mask_type > prop_mask_type;
typedef typed_property < t_real, ec_mathline > prop_mathline;
typedef typed_property < t_generic, ec_max_block_size > prop_max_block_size;
typedef typed_property < t_css_length_amm, ec_max_height > prop_max_height;
typedef typed_property < t_generic, ec_max_inline_size > prop_max_inline_size;
typedef typed_property < t_generic, ec_max_lines > prop_max_lines;
typedef typed_property < t_css_length_amm, ec_max_width > prop_max_width;
typedef typed_property < t_generic, ec_min_block_size > prop_min_block_size;
typedef typed_property < t_css_length_amm, ec_min_height > prop_min_height;
typedef typed_property < t_generic, ec_min_inline_size > prop_min_inline_size;
typedef typed_property < t_generic, ec_min_intrinsic_sizing > prop_min_intrinsic_sizing;
typedef typed_property < t_css_length_amm, ec_min_width > prop_min_width;
typedef typed_property < t_css_blend_mode, ec_mix_blend_mode > prop_mix_blend_mode;

typedef typed_property < t_text, ec_name > prop_name;
typedef typed_property < t_css_kdb_nav, ec_nav_down > prop_nav_down;
typedef typed_property < t_css_kdb_nav, ec_nav_left > prop_nav_left;
typedef typed_property < t_css_kdb_nav, ec_nav_right > prop_nav_right;
typedef typed_property < t_css_kdb_nav, ec_nav_up > prop_nav_up;
typedef typed_property < t_text_2, ec_negative > prop_negative;

typedef typed_property < t_css_object_fit, ec_object_fit > prop_object_fit;
typedef typed_property < t_css_background_0, ec_object_position > prop_object_position;
typedef typed_property < t_generic, ec_offset > prop_offset;
typedef typed_property < t_generic, ec_offset_anchor > prop_offset_anchor;
typedef typed_property < t_generic, ec_offset_distance > prop_offset_distance;
typedef typed_property < t_generic, ec_offset_path > prop_offset_path;
typedef typed_property < t_generic, ec_offset_position > prop_offset_position;
typedef typed_property < t_generic, ec_offset_rotate > prop_offset_rotate;
typedef typed_property < t_opacity, ec_opacity > prop_opacity;
typedef typed_property < t_integer, ec_order > prop_order;
typedef typed_property < t_integer_i, ec_orphans > prop_orphans;
typedef typed_property < t_css_outline_i, ec_outline > prop_outline;
typedef typed_property < t_css_col, ec_outline_colour > prop_outline_colour;
typedef typed_property < t_measure_i, ec_outline_offset > prop_outline_offset;
typedef typed_property < t_css_outline_style, ec_outline_style > prop_outline_style;
typedef typed_property < t_css_border_width_i, ec_outline_width > prop_outline_width;
typedef typed_property < t_css_overflows, ec_overflow > prop_overflow;
typedef typed_property < t_generic, ec_overflow_anchor > prop_overflow_anchor;
typedef typed_property < t_css_overflow, ec_overflow_block > prop_overflow_block;
typedef typed_property < t_css_visual_box, ec_overflow_clip_margin > prop_overflow_clip_margin;
typedef typed_property < t_generic, ec_overflow_clip_margin_block > prop_overflow_clip_margin_block;
typedef typed_property < t_generic, ec_overflow_clip_margin_block_end > prop_overflow_clip_margin_block_end;
typedef typed_property < t_generic, ec_overflow_clip_margin_block_start > prop_overflow_clip_margin_block_start;
typedef typed_property < t_generic, ec_overflow_clip_margin_bottom > prop_overflow_clip_margin_bottom;
typedef typed_property < t_generic, ec_overflow_clip_margin_inline > prop_overflow_clip_margin_inline;
typedef typed_property < t_generic, ec_overflow_clip_margin_inline_end > prop_overflow_clip_margin_inline_end;
typedef typed_property < t_generic, ec_overflow_clip_margin_inline_start > prop_overflow_clip_margin_inline_start;
typedef typed_property < t_generic, ec_overflow_clip_margin_left > prop_overflow_clip_margin_left;
typedef typed_property < t_generic, ec_overflow_clip_margin_right > prop_overflow_clip_margin_right;
typedef typed_property < t_generic, ec_overflow_clip_margin_top > prop_overflow_clip_margin_top;
typedef typed_property < t_css_overflow, ec_overflow_inline > prop_overflow_inline;
typedef typed_property < t_generic, ec_overflow_style > prop_overflow_style;
typedef typed_property < t_generic, ec_overflow_wrap > prop_overflow_wrap;
typedef typed_property < t_css_overflow, ec_overflow_x > prop_overflow_x;
typedef typed_property < t_css_overflow, ec_overflow_y > prop_overflow_y;
typedef typed_property < t_css_override_colours, ec_override_colours > prop_override_colours;
typedef typed_property < t_generic, ec_overscroll_behavior > prop_overscroll_behavior;
typedef typed_property < t_generic, ec_overscroll_behavior_block > prop_overscroll_behavior_block;
typedef typed_property < t_generic, ec_overscroll_behavior_inline > prop_overscroll_behavior_inline;
typedef typed_property < t_generic, ec_overscroll_behavior_x > prop_overscroll_behavior_x;
typedef typed_property < t_generic, ec_overscroll_behavior_y > prop_overscroll_behavior_y;

typedef typed_property < t_css_addsym, ec_pad > prop_pad;
typedef typed_property < t_measures_i, ec_padding > prop_padding;
typedef typed_property < t_generic, ec_padding_block > prop_padding_block;
typedef typed_property < t_generic, ec_padding_block_end > prop_padding_block_end;
typedef typed_property < t_generic, ec_padding_block_start > prop_padding_block_start;
typedef typed_property < t_measure_i, ec_padding_bottom > prop_padding_bottom;
typedef typed_property < t_generic, ec_padding_inline > prop_padding_inline;
typedef typed_property < t_generic, ec_padding_inline_end > prop_padding_inline_end;
typedef typed_property < t_generic, ec_padding_inline_start > prop_padding_inline_start;
typedef typed_property < t_measure_i, ec_padding_left > prop_padding_left;
typedef typed_property < t_measure_i, ec_padding_right > prop_padding_right;
typedef typed_property < t_measure_i, ec_padding_top > prop_padding_top;
typedef typed_property < t_generic, ec_page_property > prop_page; // in code
typedef typed_property < t_css_aaalri, ec_page_break_after > prop_page_break_after;
typedef typed_property < t_css_aaalri, ec_page_break_before > prop_page_break_before;
typedef typed_property < t_css_aai, ec_page_break_inside > prop_page_break_inside;
typedef typed_property < t_paint_order, ec_paint_order > prop_paint_order;
typedef typed_property < t_10_int, ec_panose_1 > prop_panose_1;
typedef typed_property < t_css_pauses, ec_pause > prop_pause;
typedef typed_property < t_css_pause, ec_pause_after > prop_pause_after;
typedef typed_property < t_css_pause, ec_pause_before > prop_pause_before;
typedef typed_property < t_css_length_n, ec_perspective > prop_perspective;
typedef typed_property < t_position, ec_perspective_origin > prop_perspective_origin;
typedef typed_property < t_css_pitch, ec_pitch > prop_pitch;
typedef typed_property < t_real_i, ec_pitch_range > prop_pitch_range;
typedef typed_property < t_css_place_content, ec_place_content > prop_place_content;
typedef typed_property < t_css_place_items, ec_place_items > prop_place_items;
typedef typed_property < t_css_place_self, ec_place_self > prop_place_self;
typedef typed_property < t_css_play_during, ec_play_during > prop_play_during;
typedef typed_property < t_pointer_events, ec_pointer_events > prop_pointer_events;
typedef typed_property < t_css_position, ec_position > prop_position;
typedef typed_property < t_text, ec_prefix > prop_prefix;
typedef typed_property < t_generic, ec_print_colour_adjust > prop_print_colour_adjust;

typedef typed_property < t_4string_ni, ec_quotes > prop_quotes;

typedef typed_property < t_measure, ec_r > prop_r;
typedef typed_property < t_css_range_a, ec_range > prop_range;
typedef typed_property < t_generic, ec_region_fragment > prop_region_fragment;
typedef typed_property < t_svg_rendering_intent, ec_rendering_intent > prop_rendering_intent;
typedef typed_property < t_css_resize, ec_resize > prop_resize;
typedef typed_property < t_css_pauses, ec_rest > prop_rest;
typedef typed_property < t_css_pause, ec_rest_after > prop_rest_after;
typedef typed_property < t_css_pause, ec_rest_before > prop_rest_before;
typedef typed_property < t_real_i, ec_richness > prop_richness;
typedef typed_property < t_css_length_ai, ec_right > prop_right;
typedef typed_property < t_css_rotate, ec_rotate > prop_rotate;
typedef typed_property < t_measure_ni, ec_row_gap > prop_row_gap;
typedef typed_property < t_generic, ec_ruby_align > prop_ruby_align;
typedef typed_property < t_generic, ec_ruby_merge > prop_ruby_merge;
typedef typed_property < t_generic, ec_ruby_overhang > prop_ruby_overhang;
typedef typed_property < t_generic, ec_ruby_position > prop_ruby_position;
typedef typed_property < t_generic, ec_running > prop_running;
typedef typed_property < t_measure, ec_rx > prop_rx;
typedef typed_property < t_measure, ec_ry > prop_ry;

typedef typed_property < t_css_scale, ec_scale > prop_scale;
typedef typed_property < t_auto_smooth, ec_scroll_behaviour > prop_scroll_behavior;
typedef typed_property < t_css_lengths, ec_scroll_margin > prop_scroll_margin;
typedef typed_property < t_css_length_a2, ec_scroll_margin_block > prop_scroll_margin_block;
typedef typed_property < t_css_length_a, ec_scroll_margin_block_end > prop_scroll_margin_block_end;
typedef typed_property < t_css_length_a, ec_scroll_margin_block_start > prop_scroll_margin_block_start;
typedef typed_property < t_css_length_a, ec_scroll_margin_bottom > prop_scroll_margin_bottom;
typedef typed_property < t_css_length_a2, ec_scroll_margin_inline > prop_scroll_margin_inline;
typedef typed_property < t_css_length_a, ec_scroll_margin_inline_end > prop_scroll_margin_inline_end;
typedef typed_property < t_css_length_a, ec_scroll_margin_inline_start > prop_scroll_margin_inline_start;
typedef typed_property < t_css_length_a, ec_scroll_margin_left > prop_scroll_margin_left;
typedef typed_property < t_css_length_a, ec_scroll_margin_right > prop_scroll_margin_right;
typedef typed_property < t_css_length_a, ec_scroll_margin_top > prop_scroll_margin_top;
typedef typed_property < t_css_lengths_a, ec_scroll_padding > prop_scroll_padding;
typedef typed_property < t_css_length_a2, ec_scroll_padding_block > prop_scroll_padding_block;
typedef typed_property < t_css_length_a, ec_scroll_padding_block_end > prop_scroll_padding_block_end;
typedef typed_property < t_css_length_a, ec_scroll_padding_block_start > prop_scroll_padding_block_start;
typedef typed_property < t_css_length_a, ec_scroll_padding_bottom > prop_scroll_padding_bottom;
typedef typed_property < t_css_length_a2, ec_scroll_padding_inline > prop_scroll_padding_inline;
typedef typed_property < t_css_length_a, ec_scroll_padding_inline_end > prop_scroll_padding_inline_end;
typedef typed_property < t_css_length_a, ec_scroll_padding_inline_start > prop_scroll_padding_inline_start;
typedef typed_property < t_css_length_a, ec_scroll_padding_left > prop_scroll_padding_left;
typedef typed_property < t_css_length_a, ec_scroll_padding_right > prop_scroll_padding_right;
typedef typed_property < t_css_length_a, ec_scroll_padding_top > prop_scroll_padding_top;
typedef typed_property < t_css_ss_align, ec_scroll_snap_align > prop_scroll_snap_align;
typedef typed_property < t_always_normal, ec_scroll_snap_stop > prop_scroll_snap_stop;
typedef typed_property < t_css_ss_type_n, ec_scroll_snap_type > prop_scroll_snap_type;
typedef typed_property < t_generic, ec_scroll_timeline > prop_scroll_timeline;
typedef typed_property < t_generic, ec_scroll_timeline_axis > prop_scroll_timeline_axis;
typedef typed_property < t_generic, ec_scroll_timeline_name > prop_scroll_timeline_name;
typedef typed_property < t_css_col, ec_scrollbar_colour > prop_scrollbar_colour;
typedef typed_property < t_css_scrollbar_gutter, ec_scrollbar_gutter > prop_scrollbar_gutter;
typedef typed_property < t_generic, ec_scrollbar_width > prop_scrollbar_width;
typedef typed_property < t_zero_to_one, ec_shape_image_threshold > prop_shape_image_threshold;
typedef typed_property < t_generic, ec_shape_inside > prop_shape_inside;
typedef typed_property < t_css_length, ec_shape_margin > prop_shape_margin;
typedef typed_property < t_css_shape_outside, ec_shape_outside > prop_shape_outside;
typedef typed_property < t_measure, ec_shape_padding > prop_shape_padding;
typedef typed_property < t_shape_rendering, ec_shape_rendering > prop_shape_rendering;
typedef typed_property < t_shape_none_uri, ec_shape_subtract > prop_shape_subtract;
typedef typed_property < t_css_size, ec_size > prop_size;
typedef typed_property < t_percent, ec_size_adjust > prop_size_adjust;
typedef typed_property < t_real, ec_slope > prop_slope;
typedef typed_property < t_generic, ec_spatial_navigation_action > prop_spatial_navigation_action;
typedef typed_property < t_generic, ec_spatial_navigation_contain > prop_spatial_navigation_contain;
typedef typed_property < t_generic, ec_spatial_navigation_function > prop_spatial_navigation_function;
typedef typed_property < t_css_speak, ec_speak > prop_speak;
typedef typed_property < t_css_speak_as, ec_speak_as > prop_speak_as;
typedef typed_property < t_css_speak_header, ec_speak_header > prop_speak_header;
typedef typed_property < t_css_speak_numeral, ec_speak_numeral > prop_speak_numeral;
typedef typed_property < t_css_speak_punctuation, ec_speak_punctuation > prop_speak_punctuation;
typedef typed_property < t_css_speech_rate, ec_speech_rate > prop_speech_rate;
typedef typed_property < t_css_srcs, ec_src > prop_src;
typedef typed_property < t_real, ec_stemh > prop_stemh;
typedef typed_property < t_real, ec_stemv > prop_stemv;
typedef typed_property < t_css_col, ec_stop_colour > prop_stop_colour;
typedef typed_property < t_opacity, ec_stop_opacity > prop_stop_opacity;
typedef typed_property < t_real_i, ec_stress > prop_stress;
typedef typed_property < t_generic, ec_string_set > prop_string_set;
typedef typed_property < t_paint, ec_stroke > prop_stroke;
typedef typed_property < t_generic, ec_stroke_align > prop_stroke_align;
typedef typed_property < t_generic, ec_stroke_alignment > prop_stroke_alignment;
typedef typed_property < t_generic, ec_stroke_break > prop_stroke_break;
typedef typed_property < t_css_col, ec_stroke_colour > prop_stroke_colour;
typedef typed_property < t_generic, ec_stroke_dash_corner > prop_stroke_dash_corner;
typedef typed_property < t_generic, ec_stroke_dash_justify > prop_stroke_dash_justify;
typedef typed_property < t_generic, ec_stroke_dashadjust > prop_stroke_dashadjust;
typedef typed_property < t_dashes, ec_stroke_dasharray > prop_stroke_dasharray;
typedef typed_property < t_generic, ec_stroke_dashcorner > prop_stroke_dashcorner;
typedef typed_property < t_generic, ec_stroke_dashoffset > prop_stroke_dashoffset;
typedef typed_property < t_generic, ec_stroke_image > prop_stroke_image;
typedef typed_property < t_linecap, ec_stroke_linecap > prop_stroke_linecap;
typedef typed_property < t_linejoin, ec_stroke_linejoin > prop_stroke_linejoin;
typedef typed_property < t_1_more_i, ec_stroke_miterlimit > prop_stroke_miterlimit;
typedef typed_property < t_opacity, ec_stroke_opacity > prop_stroke_opacity;
typedef typed_property < t_generic, ec_stroke_origin > prop_stroke_origin;
typedef typed_property < t_generic, ec_stroke_position > prop_stroke_position;
typedef typed_property < t_generic, ec_stroke_repeat > prop_stroke_repeat;
typedef typed_property < t_generic, ec_stroke_size > prop_stroke_size;
typedef typed_property < t_measure_i, ec_stroke_width > prop_stroke_width;
typedef typed_property < t_percents_nf, ec_subscript_position_override > prop_subscript_position_override;
typedef typed_property < t_percents_nf, ec_superscript_position_override > prop_superscript_position_override;
typedef typed_property < t_percents_nf, ec_subscript_size_override > prop_subscript_size_override;
typedef typed_property < t_percents_nf, ec_superscript_size_override > prop_superscript_size_override;
typedef typed_property < t_text, ec_suffix > prop_suffix;
typedef typed_property < t_texts, ec_symbols > prop_symbols;
typedef typed_property < t_css_system, ec_system > prop_system;

typedef typed_property < t_generic, ec_tab_size > prop_tab_size;
typedef typed_property < t_css_table_layout, ec_table_layout > prop_table_layout;
typedef typed_property < t_css_text_align, ec_text_align > prop_text_align;
typedef typed_property < t_generic, ec_text_align_all > prop_text_align_all;
typedef typed_property < t_generic, ec_text_align_last > prop_text_align_last;
typedef typed_property < t_smei, ec_text_anchor > prop_text_anchor;
typedef typed_property < t_generic, ec_text_autospace > prop_text_autospace;
typedef typed_property < t_css_text_combine_upright, ec_text_combine_upright > prop_text_combine_upright;
typedef typed_property < t_css_textdec_short, ec_text_decoration > prop_text_decoration;
typedef typed_property < t_css_col, ec_text_decoration_colour > prop_text_decoration_colour;
typedef typed_property < t_css_textdec_line, ec_text_decoration_line > prop_text_decoration_line;
typedef typed_property < t_auto_none, ec_text_decoration_skip > prop_text_decoration_skip;
typedef typed_property < t_all_none, ec_text_decoration_skip_box > prop_text_decoration_skip_box;
typedef typed_property < t_all_auto_none, ec_text_decoration_skip_ink > prop_text_decoration_skip_ink;
typedef typed_property < t_auto_none, ec_text_decoration_skip_inset > prop_text_decoration_skip_inset;
typedef typed_property < t_none_objects, ec_text_decoration_skip_self > prop_text_decoration_skip_self;
typedef typed_property < t_css_textdec_skip_space, ec_text_decoration_skip_spaces > prop_text_decoration_skip_spaces;
typedef typed_property < t_css_textdec_style, ec_text_decoration_style > prop_text_decoration_style;
typedef typed_property < t_css_textdec_thickness, ec_text_decoration_thickness > prop_text_decoration_thickness;
typedef typed_property < t_generic, ec_text_definition > prop_text_definition;
typedef typed_property < t_generic, ec_text_edge > prop_text_edge;
typedef typed_property < t_css_text_emphasis, ec_text_emphasis > prop_text_emphasis;
typedef typed_property < t_css_col, ec_text_emphasis_colour > prop_text_emphasis_colour;
typedef typed_property < t_css_textemph_pos, ec_text_emphasis_position > prop_text_emphasis_position;
typedef typed_property < t_css_textemph_skip, ec_text_emphasis_skip > prop_text_emphasis_skip;
typedef typed_property < t_css_textemph_style, ec_text_emphasis_style > prop_text_emphasis_style;
typedef typed_property < t_generic, ec_text_group_align > prop_text_group_align;
typedef typed_property < t_measure_i, ec_text_indent > prop_text_indent;
typedef typed_property < t_generic, ec_text_justify > prop_text_justify;
typedef typed_property < t_generic, ec_text_orientation > prop_text_orientation;
typedef typed_property < t_css_text_resize, ec_text_overflow > prop_text_overflow;
typedef typed_property < t_text_rendering, ec_text_rendering > prop_text_rendering;
typedef typed_property < t_css_text_resize, ec_text_resize > prop_text_resize;
typedef typed_property < t_css_box_shadows_n, ec_text_shadow > prop_text_shadow;
typedef typed_property < t_generic, ec_text_space_trim > prop_text_space_trim;
typedef typed_property < t_generic, ec_text_spacing > prop_text_spacing;
typedef typed_property < t_generic, ec_text_spacing_trim > prop_text_spacing_trim;
typedef typed_property < t_css_text_transform, ec_text_transform > prop_text_transform;
typedef typed_property < t_css_textdec_underline_offset, ec_text_underline_offset > prop_text_underline_offset;
typedef typed_property < t_css_textdec_underline_lru, ec_text_underline_position > prop_text_underline_position;
typedef typed_property < t_generic, ec_text_wrap > prop_text_wrap;
typedef typed_property < t_css_length_ai, ec_top > prop_top;
typedef typed_property < t_real, ec_topline > prop_topline;
typedef typed_property < t_css_transform_n, ec_transform > prop_transform;
typedef typed_property < t_css_transform_box, ec_transform_box > prop_transform_box;
typedef typed_property < t_css_transform_origins, ec_transform_origin > prop_transform_origin;
typedef typed_property < t_css_transform_style, ec_transform_style > prop_transform_style;
typedef typed_property < t_generic, ec_transition > prop_transition;
typedef typed_property < t_css_durations, ec_transition_delay > prop_transition_delay;
typedef typed_property < t_css_durations, ec_transition_duration > prop_transition_duration;
typedef typed_property < t_css_trans_props_n, ec_transition_property > prop_transition_property;
typedef typed_property < t_css_easing_fns, ec_transition_timing_function > prop_transition_timing_function;
typedef typed_property < t_generic, ec_translate > prop_translate;

typedef typed_property < t_unicode_bidi, ec_unicode_bidi > prop_unicode_bidi;
typedef typed_property < t_css_unicode_ranges, ec_unicode_range > prop_unicode_range;
typedef typed_property < t_real, ec_units_per_em > prop_units_per_em;
typedef typed_property < t_user_modify, ec_user_modify > prop_user_modify;
typedef typed_property < t_css_user_select, ec_user_select > prop_user_select;

typedef typed_property < t_svg_rendering_intent, ec_vector_effect > prop_vector_effect;
typedef typed_property < t_css_vertal, ec_vertical_align > prop_vertical_align;
typedef typed_property < t_generic, ec_view_timeline > prop_view_timeline;
typedef typed_property < t_generic, ec_view_timeline_axis > prop_view_timeline_axis;
typedef typed_property < t_generic, ec_view_timeline_inset > prop_view_timeline_inset;
typedef typed_property < t_generic, ec_view_timeline_name > prop_view_timeline_name;
typedef typed_property < t_generic, ec_view_transition_name > prop_view_transition_name;
typedef typed_property < t_visibility11, ec_visibility > prop_visibility;
typedef typed_property < t_css_voice_balance, ec_voice_balance > prop_voice_balance;
typedef typed_property < t_duration_a, ec_voice_duration > prop_voice_duration;
typedef typed_property < t_css_voice_families_p, ec_voice_family > prop_voice_family;
typedef typed_property < t_css_voice_pitch, ec_voice_pitch > prop_voice_pitch;
typedef typed_property < t_css_voice_pitch, ec_voice_range > prop_voice_range;
typedef typed_property < t_css_speech_rate, ec_voice_rate > prop_voice_rate;
typedef typed_property < t_stress, ec_voice_stress > prop_voice_stress;
typedef typed_property < t_css_voice_volume, ec_voice_volume > prop_voice_volume;
typedef typed_property < t_css_volume, ec_volume > prop_volume;

typedef typed_property < t_css_whitespace, ec_white_space > prop_white_space;
typedef typed_property < t_generic, ec_white_space_collapse > prop_white_space_collapse;
typedef typed_property < t_integer_i, ec_widows > prop_widows;
typedef typed_property < t_css_length_amm, ec_width > prop_width;
typedef typed_property < t_generic, ec_widths > prop_widths;
typedef typed_property < t_css_wcs_a, ec_will_change > prop_will_change;
typedef typed_property < t_generic, ec_word_boundary_detection > prop_word_boundary_detection;
typedef typed_property < t_generic, ec_word_boundary_expansion > prop_word_boundary_expansion;
typedef typed_property < t_generic, ec_word_break > prop_word_break;
typedef typed_property < t_css_spacing, ec_word_spacing > prop_word_spacing;
typedef typed_property < t_generic, ec_word_wrap > prop_word_wrap;
typedef typed_property < t_generic, ec_wrap_after > prop_wrap_after;
typedef typed_property < t_generic, ec_wrap_before > prop_wrap_before;
typedef typed_property < t_generic, ec_wrap_flow > prop_wrap_flow;
typedef typed_property < t_generic, ec_wrap_inside > prop_wrap_inside;
typedef typed_property < t_generic, ec_wrap_through > prop_wrap_through;
typedef typed_property < t_writingmode, ec_writing_mode > prop_writing_mode;

typedef typed_property < t_measure, ec_x > prop_x;
typedef typed_property < t_real, ec_x_height > prop_x_height;

typedef typed_property < t_measure, ec_y > prop_y;

typedef typed_property < t_integer_ai, ec_z_index > prop_z_index;
typedef typed_property < t_css_length, ec_zoom > prop_zoom;

typedef typed_property < t_unknown, ec_unknown > prop_unknown;


typedef typed_property < t_css_bespoke, ec_epub_text_decoration > prop_epub_text_decoration;
typedef typed_property < t_css_bespoke, ec_epub_text_emphasis > prop_epub_text_emphasis;
typedef typed_property < t_css_bespoke, ec_epub_text_emphasis_colour > prop_epub_text_emphasis_colour;
typedef typed_property < t_css_bespoke, ec_epub_text_emphasis_style > prop_epub_text_emphasis_style;
typedef typed_property < t_css_bespoke, ec_epub_word_break > prop_epub_word_break;
typedef typed_property < t_css_bespoke, ec_epub_writing_mode > prop_epub_writing_mode;
typedef typed_property < t_css_bespoke, ec_moz_animation > prop_moz_animation;
typedef typed_property < t_css_bespoke, ec_moz_animation_delay > prop_moz_animation_delay;
typedef typed_property < t_css_bespoke, ec_moz_animation_direction > prop_moz_animation_direction;
typedef typed_property < t_css_bespoke, ec_moz_animation_duration > prop_moz_animation_duration;
typedef typed_property < t_css_bespoke, ec_moz_animation_fill_mode > prop_moz_animation_fill_mode;
typedef typed_property < t_css_bespoke, ec_moz_animation_iteration_count > prop_moz_animation_iteration_count;
typedef typed_property < t_css_bespoke, ec_moz_animation_name > prop_moz_animation_name;
typedef typed_property < t_css_bespoke, ec_moz_animation_play_state > prop_moz_animation_play_state;
typedef typed_property < t_css_bespoke, ec_moz_animation_timing_function > prop_moz_animation_timing_function;
typedef typed_property < t_css_bespoke, ec_moz_appearance > prop_moz_appearance;
typedef typed_property < t_css_bespoke, ec_moz_backface_visibility > prop_moz_backface_visibility;
typedef typed_property < t_css_bespoke, ec_moz_background_clip > prop_moz_background_clip;
typedef typed_property < t_css_bespoke, ec_moz_background_inline_policy > prop_moz_background_inline_policy;
typedef typed_property < t_css_bespoke, ec_moz_background_origin > prop_moz_background_origin;
typedef typed_property < t_css_bespoke, ec_moz_background_size > prop_moz_background_size;
typedef typed_property < t_css_bespoke, ec_moz_binding > prop_moz_binding;
typedef typed_property < t_css_bespoke, ec_moz_border_bottom_colours > prop_moz_border_bottom_colours;
typedef typed_property < t_css_bespoke, ec_moz_border_end > prop_moz_border_end;
typedef typed_property < t_css_bespoke, ec_moz_border_end_colour > prop_moz_border_end_colour;
typedef typed_property < t_css_bespoke, ec_moz_border_end_style > prop_moz_border_end_style;
typedef typed_property < t_css_bespoke, ec_moz_border_end_width > prop_moz_border_end_width;
typedef typed_property < t_css_bespoke, ec_moz_border_image > prop_moz_border_image;
typedef typed_property < t_css_bespoke, ec_moz_border_left_colours > prop_moz_border_left_colours;
typedef typed_property < t_css_bespoke, ec_moz_border_right_colours > prop_moz_border_right_colours;
typedef typed_property < t_css_bespoke, ec_moz_border_start > prop_moz_border_start;
typedef typed_property < t_css_bespoke, ec_moz_border_start_colour > prop_moz_border_start_colour;
typedef typed_property < t_css_bespoke, ec_moz_border_start_style > prop_moz_border_start_style;
typedef typed_property < t_css_bespoke, ec_moz_border_start_width > prop_moz_border_start_width;
typedef typed_property < t_css_bespoke, ec_moz_border_top_colours > prop_moz_border_top_colours;
typedef typed_property < t_css_bespoke, ec_moz_box_align > prop_moz_box_align;
typedef typed_property < t_css_bespoke, ec_moz_box_direction > prop_moz_box_direction;
typedef typed_property < t_css_bespoke, ec_moz_box_flex > prop_moz_box_flex;
typedef typed_property < t_css_bespoke, ec_moz_box_ordinal_group > prop_moz_box_ordinal_group;
typedef typed_property < t_css_bespoke, ec_moz_box_orient > prop_moz_box_orient;
typedef typed_property < t_css_bespoke, ec_moz_box_pack > prop_moz_box_pack;
typedef typed_property < t_css_bespoke, ec_moz_box_sizing > prop_moz_box_sizing;
typedef typed_property < t_css_bespoke, ec_moz_column_count > prop_moz_column_count;
typedef typed_property < t_css_bespoke, ec_moz_column_fill > prop_moz_column_fill;
typedef typed_property < t_css_bespoke, ec_moz_column_gap > prop_moz_column_gap;
typedef typed_property < t_css_bespoke, ec_moz_column_rule > prop_moz_column_rule;
typedef typed_property < t_css_bespoke, ec_moz_column_rule_colour > prop_moz_column_rule_colour;
typedef typed_property < t_css_bespoke, ec_moz_column_rule_style > prop_moz_column_rule_style;
typedef typed_property < t_css_bespoke, ec_moz_column_rule_width > prop_moz_column_rule_width;
typedef typed_property < t_css_bespoke, ec_moz_column_width > prop_moz_column_width;
typedef typed_property < t_css_bespoke, ec_moz_context_properties > prop_moz_context_properties;
typedef typed_property < t_css_bespoke, ec_moz_float_edge > prop_moz_float_edge;
typedef typed_property < t_css_bespoke, ec_moz_font_feature_settings > prop_moz_font_feature_settings;
typedef typed_property < t_css_bespoke, ec_moz_font_language_override > prop_moz_font_language_override;
typedef typed_property < t_css_bespoke, ec_moz_force_broken_image_icon > prop_moz_force_broken_image_icon;
typedef typed_property < t_css_bespoke, ec_moz_hyphens > prop_moz_hyphens;
typedef typed_property < t_css_bespoke, ec_moz_image_region > prop_moz_image_region;
typedef typed_property < t_css_bespoke, ec_moz_margin_end > prop_moz_margin_end;
typedef typed_property < t_css_bespoke, ec_moz_margin_start > prop_moz_margin_start;
typedef typed_property < t_css_bespoke, ec_moz_opacity > prop_moz_opacity;
typedef typed_property < t_css_bespoke, ec_moz_orient > prop_moz_orient;
typedef typed_property < t_css_bespoke, ec_moz_osx_font_smoothing > prop_moz_osx_font_smoothing;
typedef typed_property < t_css_bespoke, ec_moz_outline > prop_moz_outline;
typedef typed_property < t_css_bespoke, ec_moz_outline_colour > prop_moz_outline_colour;
typedef typed_property < t_css_bespoke, ec_moz_outline_offset > prop_moz_outline_offset;
typedef typed_property < t_css_bespoke, ec_moz_outline_radius > prop_moz_outline_radius;
typedef typed_property < t_css_bespoke, ec_moz_outline_radius_bottomleft > prop_moz_outline_radius_bottomleft;
typedef typed_property < t_css_bespoke, ec_moz_outline_radius_bottomright > prop_moz_outline_radius_bottomright;
typedef typed_property < t_css_bespoke, ec_moz_outline_radius_topleft > prop_moz_outline_radius_topleft;
typedef typed_property < t_css_bespoke, ec_moz_outline_radius_topright > prop_moz_outline_radius_topright;
typedef typed_property < t_css_bespoke, ec_moz_outline_style > prop_moz_outline_style;
typedef typed_property < t_css_bespoke, ec_moz_outline_width > prop_moz_outline_width;
typedef typed_property < t_css_bespoke, ec_moz_padding_end > prop_moz_padding_end;
typedef typed_property < t_css_bespoke, ec_moz_padding_start > prop_moz_padding_start;
typedef typed_property < t_css_bespoke, ec_moz_perspective > prop_moz_perspective;
typedef typed_property < t_css_bespoke, ec_moz_perspective_origin > prop_moz_perspective_origin;
typedef typed_property < t_css_bespoke, ec_moz_stack_sizing > prop_moz_stack_sizing;
typedef typed_property < t_css_bespoke, ec_moz_tab_size > prop_moz_tab_size;
typedef typed_property < t_css_bespoke, ec_moz_text_align_last > prop_moz_text_align_last;
typedef typed_property < t_css_bespoke, ec_moz_text_decoration_colour > prop_moz_text_decoration_colour;
typedef typed_property < t_css_bespoke, ec_moz_text_decoration_line > prop_moz_text_decoration_line;
typedef typed_property < t_css_bespoke, ec_moz_text_decoration_style > prop_moz_text_decoration_style;
typedef typed_property < t_css_bespoke, ec_moz_text_size_adjust > prop_moz_text_size_adjust;
typedef typed_property < t_css_bespoke, ec_moz_transform > prop_moz_transform;
typedef typed_property < t_css_bespoke, ec_moz_transform_origin > prop_moz_transform_origin;
typedef typed_property < t_css_bespoke, ec_moz_transform_style > prop_moz_transform_style;
typedef typed_property < t_css_bespoke, ec_moz_transition > prop_moz_transition;
typedef typed_property < t_css_bespoke, ec_moz_transition_delay > prop_moz_transition_delay;
typedef typed_property < t_css_bespoke, ec_moz_transition_duration > prop_moz_transition_duration;
typedef typed_property < t_css_bespoke, ec_moz_transition_property > prop_moz_transition_property;
typedef typed_property < t_css_bespoke, ec_moz_transition_timing_function > prop_moz_transition_timing_function;
typedef typed_property < t_css_bespoke, ec_moz_user_focus > prop_moz_user_focus;
typedef typed_property < t_css_bespoke, ec_moz_user_input > prop_moz_user_input;
typedef typed_property < t_css_bespoke, ec_moz_user_modify > prop_moz_user_modify;
typedef typed_property < t_css_bespoke, ec_moz_user_select > prop_moz_user_select;
typedef typed_property < t_css_bespoke, ec_moz_window_dragging > prop_moz_window_dragging;
typedef typed_property < t_css_bespoke, ec_moz_window_shadow > prop_moz_window_shadow;
typedef typed_property < t_css_bespoke, ec_webkit_align_content > prop_webkit_align_content;
typedef typed_property < t_css_bespoke, ec_webkit_align_items > prop_webkit_align_items;
typedef typed_property < t_css_bespoke, ec_webkit_align_self > prop_webkit_align_self;
typedef typed_property < t_css_bespoke, ec_webkit_alt > prop_webkit_alt;
typedef typed_property < t_css_bespoke, ec_webkit_animation > prop_webkit_animation;
typedef typed_property < t_css_bespoke, ec_webkit_animation_delay > prop_webkit_animation_delay;
typedef typed_property < t_css_bespoke, ec_webkit_animation_direction > prop_webkit_animation_direction;
typedef typed_property < t_css_bespoke, ec_webkit_animation_duration > prop_webkit_animation_duration;
typedef typed_property < t_css_bespoke, ec_webkit_animation_fill_mode > prop_webkit_animation_fill_mode;
typedef typed_property < t_css_bespoke, ec_webkit_animation_iteration_count > prop_webkit_animation_iteration_count;
typedef typed_property < t_css_bespoke, ec_webkit_animation_name > prop_webkit_animation_name;
typedef typed_property < t_css_bespoke, ec_webkit_animation_play_state > prop_webkit_animation_play_state;
typedef typed_property < t_css_bespoke, ec_webkit_animation_timing_function > prop_webkit_animation_timing_function;
typedef typed_property < t_css_bespoke, ec_webkit_animation_trigger > prop_webkit_animation_trigger;
typedef typed_property < t_css_bespoke, ec_webkit_app_region > prop_webkit_app_region;
typedef typed_property < t_css_bespoke, ec_webkit_appearance > prop_webkit_appearance;
typedef typed_property < t_css_bespoke, ec_webkit_aspect_ratio > prop_webkit_aspect_ratio;
typedef typed_property < t_css_bespoke, ec_webkit_backdrop_filter > prop_webkit_backdrop_filter;
typedef typed_property < t_css_bespoke, ec_webkit_backface_visibility > prop_webkit_backface_visibility;
typedef typed_property < t_css_bespoke, ec_webkit_background_clip > prop_webkit_background_clip;
typedef typed_property < t_css_bespoke, ec_webkit_background_composite > prop_webkit_background_composite;
typedef typed_property < t_css_bespoke, ec_webkit_background_origin > prop_webkit_background_origin;
typedef typed_property < t_css_bespoke, ec_webkit_background_size > prop_webkit_background_size;
typedef typed_property < t_css_bespoke, ec_webkit_border_after > prop_webkit_border_after;
typedef typed_property < t_css_bespoke, ec_webkit_border_after_colour > prop_webkit_border_after_colour;
typedef typed_property < t_css_bespoke, ec_webkit_border_after_style > prop_webkit_border_after_style;
typedef typed_property < t_css_bespoke, ec_webkit_border_after_width > prop_webkit_border_after_width;
typedef typed_property < t_css_bespoke, ec_webkit_border_before > prop_webkit_border_before;
typedef typed_property < t_css_bespoke, ec_webkit_border_before_colour > prop_webkit_border_before_colour;
typedef typed_property < t_css_bespoke, ec_webkit_border_before_style > prop_webkit_border_before_style;
typedef typed_property < t_css_bespoke, ec_webkit_border_before_width > prop_webkit_border_before_width;
typedef typed_property < t_css_bespoke, ec_webkit_border_bottom_left_radius > prop_webkit_border_bottom_left_radius;
typedef typed_property < t_css_bespoke, ec_webkit_border_bottom_right_radius > prop_webkit_border_bottom_right_radius;
typedef typed_property < t_css_bespoke, ec_webkit_border_end > prop_webkit_border_end;
typedef typed_property < t_css_bespoke, ec_webkit_border_end_colour > prop_webkit_border_end_colour;
typedef typed_property < t_css_bespoke, ec_webkit_border_end_style > prop_webkit_border_end_style;
typedef typed_property < t_css_bespoke, ec_webkit_border_end_width > prop_webkit_border_end_width;
typedef typed_property < t_css_bespoke, ec_webkit_border_fit > prop_webkit_border_fit;
typedef typed_property < t_css_bespoke, ec_webkit_border_horizontal_spacing > prop_webkit_border_horizontal_spacing;
typedef typed_property < t_css_bespoke, ec_webkit_border_image > prop_webkit_border_image;
typedef typed_property < t_css_bespoke, ec_webkit_border_radius > prop_webkit_border_radius;
typedef typed_property < t_css_bespoke, ec_webkit_border_start > prop_webkit_border_start;
typedef typed_property < t_css_bespoke, ec_webkit_border_start_colour > prop_webkit_border_start_colour;
typedef typed_property < t_css_bespoke, ec_webkit_border_start_style > prop_webkit_border_start_style;
typedef typed_property < t_css_bespoke, ec_webkit_border_start_width > prop_webkit_border_start_width;
typedef typed_property < t_css_bespoke, ec_webkit_border_top_left_radius > prop_webkit_border_top_left_radius;
typedef typed_property < t_css_bespoke, ec_webkit_border_top_right_radius > prop_webkit_border_top_right_radius;
typedef typed_property < t_css_bespoke, ec_webkit_border_vertical_spacing > prop_webkit_border_vertical_spacing;
typedef typed_property < t_css_bespoke, ec_webkit_box_align > prop_webkit_box_align;
typedef typed_property < t_css_bespoke, ec_webkit_box_decoration_break > prop_webkit_box_decoration_break;
typedef typed_property < t_css_bespoke, ec_webkit_box_direction > prop_webkit_box_direction;
typedef typed_property < t_css_bespoke, ec_webkit_box_flex > prop_webkit_box_flex;
typedef typed_property < t_css_bespoke, ec_webkit_box_flex_group > prop_webkit_box_flex_group;
typedef typed_property < t_css_bespoke, ec_webkit_box_lines > prop_webkit_box_lines;
typedef typed_property < t_css_bespoke, ec_webkit_box_ordinal_group > prop_webkit_box_ordinal_group;
typedef typed_property < t_css_bespoke, ec_webkit_box_orient > prop_webkit_box_orient;
typedef typed_property < t_css_bespoke, ec_webkit_box_pack > prop_webkit_box_pack;
typedef typed_property < t_css_bespoke, ec_webkit_box_reflect > prop_webkit_box_reflect;
typedef typed_property < t_css_bespoke, ec_webkit_box_shadow > prop_webkit_box_shadow;
typedef typed_property < t_css_bespoke, ec_webkit_box_sizing > prop_webkit_box_sizing;
typedef typed_property < t_css_bespoke, ec_webkit_clip_path > prop_webkit_clip_path;
typedef typed_property < t_css_bespoke, ec_webkit_colour_correction > prop_webkit_colour_correction;
typedef typed_property < t_css_bespoke, ec_webkit_column_axis > prop_webkit_column_axis;
typedef typed_property < t_css_bespoke, ec_webkit_column_break_after > prop_webkit_column_break_after;
typedef typed_property < t_css_bespoke, ec_webkit_column_break_before > prop_webkit_column_break_before;
typedef typed_property < t_css_bespoke, ec_webkit_column_break_inside > prop_webkit_column_break_inside;
typedef typed_property < t_css_bespoke, ec_webkit_column_count > prop_webkit_column_count;
typedef typed_property < t_css_bespoke, ec_webkit_column_fill > prop_webkit_column_fill;
typedef typed_property < t_css_bespoke, ec_webkit_column_gap > prop_webkit_column_gap;
typedef typed_property < t_css_bespoke, ec_webkit_column_progression > prop_webkit_column_progression;
typedef typed_property < t_css_bespoke, ec_webkit_column_rule > prop_webkit_column_rule;
typedef typed_property < t_css_bespoke, ec_webkit_column_rule_colour > prop_webkit_column_rule_colour;
typedef typed_property < t_css_bespoke, ec_webkit_column_rule_style > prop_webkit_column_rule_style;
typedef typed_property < t_css_bespoke, ec_webkit_column_rule_width > prop_webkit_column_rule_width;
typedef typed_property < t_css_bespoke, ec_webkit_column_span > prop_webkit_column_span;
typedef typed_property < t_css_bespoke, ec_webkit_column_width > prop_webkit_column_width;
typedef typed_property < t_css_bespoke, ec_webkit_columns > prop_webkit_columns;
typedef typed_property < t_css_bespoke, ec_webkit_cursor_visibility > prop_webkit_cursor_visibility;
typedef typed_property < t_css_bespoke, ec_webkit_dashboard_region > prop_webkit_dashboard_region;
typedef typed_property < t_css_bespoke, ec_webkit_device_pixel_ratio > prop_webkit_device_pixel_ratio;
typedef typed_property < t_css_bespoke, ec_webkit_filter > prop_webkit_filter;
typedef typed_property < t_css_bespoke, ec_webkit_flex > prop_webkit_flex;
typedef typed_property < t_css_bespoke, ec_webkit_flex_basis > prop_webkit_flex_basis;
typedef typed_property < t_css_bespoke, ec_webkit_flex_direction > prop_webkit_flex_direction;
typedef typed_property < t_css_bespoke, ec_webkit_flex_flow > prop_webkit_flex_flow;
typedef typed_property < t_css_bespoke, ec_webkit_flex_grow > prop_webkit_flex_grow;
typedef typed_property < t_css_bespoke, ec_webkit_flex_shrink > prop_webkit_flex_shrink;
typedef typed_property < t_css_bespoke, ec_webkit_flex_wrap > prop_webkit_flex_wrap;
typedef typed_property < t_css_bespoke, ec_webkit_flow_from > prop_webkit_flow_from;
typedef typed_property < t_css_bespoke, ec_webkit_flow_into > prop_webkit_flow_into;
typedef typed_property < t_css_bespoke, ec_webkit_font_feature_settings > prop_webkit_font_feature_settings;
typedef typed_property < t_css_bespoke, ec_webkit_font_kerning > prop_webkit_font_kerning;
typedef typed_property < t_css_bespoke, ec_webkit_font_size_delta > prop_webkit_font_size_delta;
typedef typed_property < t_css_bespoke, ec_webkit_font_smoothing > prop_webkit_font_smoothing;
typedef typed_property < t_css_bespoke, ec_webkit_font_variant_ligatures > prop_webkit_font_variant_ligatures;
typedef typed_property < t_css_bespoke, ec_webkit_grid > prop_webkit_grid;
typedef typed_property < t_css_bespoke, ec_webkit_grid_area > prop_webkit_grid_area;
typedef typed_property < t_css_bespoke, ec_webkit_grid_auto_columns > prop_webkit_grid_auto_columns;
typedef typed_property < t_css_bespoke, ec_webkit_grid_auto_flow > prop_webkit_grid_auto_flow;
typedef typed_property < t_css_bespoke, ec_webkit_grid_auto_rows > prop_webkit_grid_auto_rows;
typedef typed_property < t_css_bespoke, ec_webkit_grid_column > prop_webkit_grid_column;
typedef typed_property < t_css_bespoke, ec_webkit_grid_column_end > prop_webkit_grid_column_end;
typedef typed_property < t_css_bespoke, ec_webkit_grid_column_gap > prop_webkit_grid_column_gap;
typedef typed_property < t_css_bespoke, ec_webkit_grid_column_start > prop_webkit_grid_column_start;
typedef typed_property < t_css_bespoke, ec_webkit_grid_columns > prop_webkit_grid_columns;
typedef typed_property < t_css_bespoke, ec_webkit_grid_gap > prop_webkit_grid_gap;
typedef typed_property < t_css_bespoke, ec_webkit_grid_row > prop_webkit_grid_row;
typedef typed_property < t_css_bespoke, ec_webkit_grid_row_end > prop_webkit_grid_row_end;
typedef typed_property < t_css_bespoke, ec_webkit_grid_row_gap > prop_webkit_grid_row_gap;
typedef typed_property < t_css_bespoke, ec_webkit_grid_row_start > prop_webkit_grid_row_start;
typedef typed_property < t_css_bespoke, ec_webkit_grid_rows > prop_webkit_grid_rows;
typedef typed_property < t_css_bespoke, ec_webkit_grid_template > prop_webkit_grid_template;
typedef typed_property < t_css_bespoke, ec_webkit_grid_template_areas > prop_webkit_grid_template_areas;
typedef typed_property < t_css_bespoke, ec_webkit_grid_template_columns > prop_webkit_grid_template_columns;
typedef typed_property < t_css_bespoke, ec_webkit_grid_template_rows > prop_webkit_grid_template_rows;
typedef typed_property < t_css_bespoke, ec_webkit_highlight > prop_webkit_highlight;
typedef typed_property < t_css_bespoke, ec_webkit_hyphenate_character > prop_webkit_hyphenate_character;
typedef typed_property < t_css_bespoke, ec_webkit_hyphenate_charset > prop_webkit_hyphenate_charset;
typedef typed_property < t_css_bespoke, ec_webkit_hyphenate_limit_after > prop_webkit_hyphenate_limit_after;
typedef typed_property < t_css_bespoke, ec_webkit_hyphenate_limit_before > prop_webkit_hyphenate_limit_before;
typedef typed_property < t_css_bespoke, ec_webkit_hyphenate_limit_lines > prop_webkit_hyphenate_limit_lines;
typedef typed_property < t_css_bespoke, ec_webkit_hyphens > prop_webkit_hyphens;
typedef typed_property < t_css_bespoke, ec_webkit_image_set > prop_webkit_image_set;
typedef typed_property < t_css_bespoke, ec_webkit_initial_letter > prop_webkit_initial_letter;
typedef typed_property < t_css_bespoke, ec_webkit_justify_content > prop_webkit_justify_content;
typedef typed_property < t_css_bespoke, ec_webkit_justify_items > prop_webkit_justify_items;
typedef typed_property < t_css_bespoke, ec_webkit_justify_self > prop_webkit_justify_self;
typedef typed_property < t_css_bespoke, ec_webkit_line_align > prop_webkit_line_align;
typedef typed_property < t_css_bespoke, ec_webkit_line_box_contain > prop_webkit_line_box_contain;
typedef typed_property < t_css_bespoke, ec_webkit_line_break > prop_webkit_line_break;
typedef typed_property < t_css_bespoke, ec_webkit_line_clamp > prop_webkit_line_clamp;
typedef typed_property < t_css_bespoke, ec_webkit_line_grid > prop_webkit_line_grid;
typedef typed_property < t_css_bespoke, ec_webkit_line_snap > prop_webkit_line_snap;
typedef typed_property < t_css_bespoke, ec_webkit_locale > prop_webkit_locale;
typedef typed_property < t_css_bespoke, ec_webkit_logical_height > prop_webkit_logical_height;
typedef typed_property < t_css_bespoke, ec_webkit_logical_width > prop_webkit_logical_width;
typedef typed_property < t_css_bespoke, ec_webkit_margin_after > prop_webkit_margin_after;
typedef typed_property < t_css_bespoke, ec_webkit_margin_after_collapse > prop_webkit_margin_after_collapse;
typedef typed_property < t_css_bespoke, ec_webkit_margin_before > prop_webkit_margin_before;
typedef typed_property < t_css_bespoke, ec_webkit_margin_before_collapse > prop_webkit_margin_before_collapse;
typedef typed_property < t_css_bespoke, ec_webkit_margin_bottom_collapse > prop_webkit_margin_bottom_collapse;
typedef typed_property < t_css_bespoke, ec_webkit_margin_collapse > prop_webkit_margin_collapse;
typedef typed_property < t_css_bespoke, ec_webkit_margin_end > prop_webkit_margin_end;
typedef typed_property < t_css_bespoke, ec_webkit_margin_start > prop_webkit_margin_start;
typedef typed_property < t_css_bespoke, ec_webkit_margin_top_collapse > prop_webkit_margin_top_collapse;
typedef typed_property < t_css_bespoke, ec_webkit_marquee > prop_webkit_marquee;
typedef typed_property < t_css_bespoke, ec_webkit_marquee_direction > prop_webkit_marquee_direction;
typedef typed_property < t_css_bespoke, ec_webkit_marquee_increment > prop_webkit_marquee_increment;
typedef typed_property < t_css_bespoke, ec_webkit_marquee_repetition > prop_webkit_marquee_repetition;
typedef typed_property < t_css_bespoke, ec_webkit_marquee_speed > prop_webkit_marquee_speed;
typedef typed_property < t_css_bespoke, ec_webkit_marquee_style > prop_webkit_marquee_style;
typedef typed_property < t_css_bespoke, ec_webkit_mask > prop_webkit_mask;
typedef typed_property < t_css_bespoke, ec_webkit_mask_attachment > prop_webkit_mask_attachment;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image > prop_webkit_mask_box_image;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image_outset > prop_webkit_mask_box_image_outset;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image_repeat > prop_webkit_mask_box_image_repeat;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image_slice > prop_webkit_mask_box_image_slice;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image_source > prop_webkit_mask_box_image_source;
typedef typed_property < t_css_bespoke, ec_webkit_mask_box_image_width > prop_webkit_mask_box_image_width;
typedef typed_property < t_css_bespoke, ec_webkit_mask_clip > prop_webkit_mask_clip;
typedef typed_property < t_css_bespoke, ec_webkit_mask_composite > prop_webkit_mask_composite;
typedef typed_property < t_css_bespoke, ec_webkit_mask_image > prop_webkit_mask_image;
typedef typed_property < t_css_bespoke, ec_webkit_mask_origin > prop_webkit_mask_origin;
typedef typed_property < t_css_bespoke, ec_webkit_mask_position > prop_webkit_mask_position;
typedef typed_property < t_css_bespoke, ec_webkit_mask_position_x > prop_webkit_mask_position_x;
typedef typed_property < t_css_bespoke, ec_webkit_mask_position_y > prop_webkit_mask_position_y;
typedef typed_property < t_css_bespoke, ec_webkit_mask_repeat > prop_webkit_mask_repeat;
typedef typed_property < t_css_bespoke, ec_webkit_mask_repeat_x > prop_webkit_mask_repeat_x;
typedef typed_property < t_css_bespoke, ec_webkit_mask_repeat_y > prop_webkit_mask_repeat_y;
typedef typed_property < t_css_bespoke, ec_webkit_mask_size > prop_webkit_mask_size;
typedef typed_property < t_css_bespoke, ec_webkit_mask_source_type > prop_webkit_mask_source_type;
typedef typed_property < t_css_bespoke, ec_webkit_match_nearest_mail_blockquote_colour > prop_webkit_match_nearest_mail_blockquote_colour;
typedef typed_property < t_css_bespoke, ec_webkit_max_logical_height > prop_webkit_max_logical_height;
typedef typed_property < t_css_bespoke, ec_webkit_max_logical_width > prop_webkit_max_logical_width;
typedef typed_property < t_css_bespoke, ec_webkit_media_text_track_container > prop_webkit_media_text_track_container;
typedef typed_property < t_css_bespoke, ec_webkit_min_logical_height > prop_webkit_min_logical_height;
typedef typed_property < t_css_bespoke, ec_webkit_min_logical_width > prop_webkit_min_logical_width;
typedef typed_property < t_css_bespoke, ec_webkit_nbsp_mode > prop_webkit_nbsp_mode;
typedef typed_property < t_css_bespoke, ec_webkit_opacity > prop_webkit_opacity;
typedef typed_property < t_css_bespoke, ec_webkit_order > prop_webkit_order;
typedef typed_property < t_css_bespoke, ec_webkit_overflow_scrolling > prop_webkit_overflow_scrolling;
typedef typed_property < t_css_bespoke, ec_webkit_padding_after > prop_webkit_padding_after;
typedef typed_property < t_css_bespoke, ec_webkit_padding_before > prop_webkit_padding_before;
typedef typed_property < t_css_bespoke, ec_webkit_padding_end > prop_webkit_padding_end;
typedef typed_property < t_css_bespoke, ec_webkit_padding_start > prop_webkit_padding_start;
typedef typed_property < t_css_bespoke, ec_webkit_perspective > prop_webkit_perspective;
typedef typed_property < t_css_bespoke, ec_webkit_perspective_origin > prop_webkit_perspective_origin;
typedef typed_property < t_css_bespoke, ec_webkit_perspective_origin_x > prop_webkit_perspective_origin_x;
typedef typed_property < t_css_bespoke, ec_webkit_perspective_origin_y > prop_webkit_perspective_origin_y;
typedef typed_property < t_css_bespoke, ec_webkit_print_colour_adjust > prop_webkit_print_colour_adjust;
typedef typed_property < t_css_bespoke, ec_webkit_region_break_after > prop_webkit_region_break_after;
typedef typed_property < t_css_bespoke, ec_webkit_region_break_before > prop_webkit_region_break_before;
typedef typed_property < t_css_bespoke, ec_webkit_region_break_inside > prop_webkit_region_break_inside;
typedef typed_property < t_css_bespoke, ec_webkit_region_fragment > prop_webkit_region_fragment;
typedef typed_property < t_css_bespoke, ec_webkit_rtl_ordering > prop_webkit_rtl_ordering;
typedef typed_property < t_css_bespoke, ec_webkit_ruby_position > prop_webkit_ruby_position;
typedef typed_property < t_css_bespoke, ec_webkit_scroll_snap_type > prop_webkit_scroll_snap_type;
typedef typed_property < t_css_bespoke, ec_webkit_shape_image_threshold > prop_webkit_shape_image_threshold;
typedef typed_property < t_css_bespoke, ec_webkit_shape_inside > prop_webkit_shape_inside;
typedef typed_property < t_css_bespoke, ec_webkit_shape_margin > prop_webkit_shape_margin;
typedef typed_property < t_css_bespoke, ec_webkit_shape_outside > prop_webkit_shape_outside;
typedef typed_property < t_css_bespoke, ec_webkit_svg_shadow > prop_webkit_svg_shadow;
typedef typed_property < t_css_bespoke, ec_webkit_tap_highlight_colour > prop_webkit_tap_highlight_colour;
typedef typed_property < t_css_bespoke, ec_webkit_text_colour_decoration > prop_webkit_text_colour_decoration;
typedef typed_property < t_css_bespoke, ec_webkit_text_combine > prop_webkit_text_combine;
typedef typed_property < t_css_bespoke, ec_webkit_text_decoration_line > prop_webkit_text_decoration_line;
typedef typed_property < t_css_bespoke, ec_webkit_text_decoration_skip > prop_webkit_text_decoration_skip;
typedef typed_property < t_css_bespoke, ec_webkit_text_decoration_style > prop_webkit_text_decoration_style;
typedef typed_property < t_css_bespoke, ec_webkit_text_decorations_in_effect > prop_webkit_text_decorations_in_effect;
typedef typed_property < t_css_bespoke, ec_webkit_text_emphasis > prop_webkit_text_emphasis;
typedef typed_property < t_css_bespoke, ec_webkit_text_emphasis_colour > prop_webkit_text_emphasis_colour;
typedef typed_property < t_css_bespoke, ec_webkit_text_emphasis_position > prop_webkit_text_emphasis_position;
typedef typed_property < t_css_bespoke, ec_webkit_text_emphasis_style > prop_webkit_text_emphasis_style;
typedef typed_property < t_css_bespoke, ec_webkit_text_fill_colour > prop_webkit_text_fill_colour;
typedef typed_property < t_css_bespoke, ec_webkit_text_justify > prop_webkit_text_justify;
typedef typed_property < t_css_bespoke, ec_webkit_text_orientation > prop_webkit_text_orientation;
typedef typed_property < t_css_bespoke, ec_webkit_text_security > prop_webkit_text_security;
typedef typed_property < t_css_bespoke, ec_webkit_text_size_adjust > prop_webkit_text_size_adjust;
typedef typed_property < t_css_bespoke, ec_webkit_text_stroke > prop_webkit_text_stroke;
typedef typed_property < t_css_bespoke, ec_webkit_text_stroke_colour > prop_webkit_text_stroke_colour;
typedef typed_property < t_css_bespoke, ec_webkit_text_stroke_width > prop_webkit_text_stroke_width;
typedef typed_property < t_css_bespoke, ec_webkit_text_underline_position > prop_webkit_text_underline_position;
typedef typed_property < t_css_bespoke, ec_webkit_text_zoom > prop_webkit_text_zoom;
typedef typed_property < t_css_bespoke, ec_webkit_touch_callout > prop_webkit_touch_callout;
typedef typed_property < t_css_bespoke, ec_webkit_transform > prop_webkit_transform;
typedef typed_property < t_css_bespoke, ec_webkit_transform_2d > prop_webkit_transform_2d;
typedef typed_property < t_css_bespoke, ec_webkit_transform_3d > prop_webkit_transform_3d;
typedef typed_property < t_css_bespoke, ec_webkit_transform_origin > prop_webkit_transform_origin;
typedef typed_property < t_css_bespoke, ec_webkit_transform_origin_x > prop_webkit_transform_origin_x;
typedef typed_property < t_css_bespoke, ec_webkit_transform_origin_y > prop_webkit_transform_origin_y;
typedef typed_property < t_css_bespoke, ec_webkit_transform_origin_z > prop_webkit_transform_origin_z;
typedef typed_property < t_css_bespoke, ec_webkit_transform_style > prop_webkit_transform_style;
typedef typed_property < t_css_bespoke, ec_webkit_transition > prop_webkit_transition;
typedef typed_property < t_css_bespoke, ec_webkit_transition_delay > prop_webkit_transition_delay;
typedef typed_property < t_css_bespoke, ec_webkit_transition_duration > prop_webkit_transition_duration;
typedef typed_property < t_css_bespoke, ec_webkit_transition_property > prop_webkit_transition_property;
typedef typed_property < t_css_bespoke, ec_webkit_transition_timing_function > prop_webkit_transition_timing_function;
typedef typed_property < t_css_bespoke, ec_webkit_user_drag > prop_webkit_user_drag;
typedef typed_property < t_css_bespoke, ec_webkit_user_modify > prop_webkit_user_modify;
typedef typed_property < t_css_bespoke, ec_webkit_user_select > prop_webkit_user_select;
typedef typed_property < t_css_bespoke, ec_background_origin_x > prop_background_origin_x;
typedef typed_property < t_css_bespoke, ec_background_origin_y > prop_background_origin_y;
typedef typed_property < t_css_bespoke, ec_overflow_clip_box > prop_overflow_clip_box;
typedef typed_property < t_css_bespoke, ec_overflow_clip_box_block > prop_overflow_clip_box_block;
typedef typed_property < t_css_bespoke, ec_overflow_clip_box_inline > prop_overflow_clip_box_inline;

typedef typed_property < t_css_bespoke, ec_mso_ansi_font_size > prop_mso_ansi_font_size;
typedef typed_property < t_css_bespoke, ec_mso_ansi_font_style > prop_mso_ansi_font_style;
typedef typed_property < t_css_bespoke, ec_mso_ansi_font_weight > prop_mso_ansi_font_weight;
typedef typed_property < t_css_bespoke, ec_mso_ansi_language > prop_mso_ansi_language;
typedef typed_property < t_css_bespoke, ec_mso_arabic_font_family > prop_mso_arabic_font_family;
typedef typed_property < t_css_bespoke, ec_mso_armenian_font_family > prop_mso_armenian_font_family;
typedef typed_property < t_css_bespoke, ec_mso_ascii_font_family > prop_mso_ascii_font_family;
typedef typed_property < t_css_bespoke, ec_mso_ascii_theme_font > prop_mso_ascii_theme_font;
typedef typed_property < t_css_bespoke, ec_mso_background_source > prop_mso_background_source;
typedef typed_property < t_css_bespoke, ec_mso_bengali_font_family > prop_mso_bengali_font_family;
typedef typed_property < t_css_bespoke, ec_mso_bidi_font_family > prop_mso_bidi_font_family;
typedef typed_property < t_css_bespoke, ec_mso_bidi_font_size > prop_mso_bidi_font_size;
typedef typed_property < t_css_bespoke, ec_mso_bidi_font_style > prop_mso_bidi_font_style;
typedef typed_property < t_css_bespoke, ec_mso_bidi_font_weight > prop_mso_bidi_font_weight;
typedef typed_property < t_css_bespoke, ec_mso_bidi_language > prop_mso_bidi_language;
typedef typed_property < t_css_bespoke, ec_mso_bidi_theme_font > prop_mso_bidi_theme_font;
typedef typed_property < t_css_bespoke, ec_mso_bookmark > prop_mso_bookmark;
typedef typed_property < t_css_bespoke, ec_mso_bopomofo_font_family > prop_mso_bopomofo_font_family;
typedef typed_property < t_css_bespoke, ec_mso_border_alt > prop_mso_border_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_bottom_alt > prop_mso_border_bottom_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_colour_alt > prop_mso_border_colour_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_insideh > prop_mso_border_insideh;
typedef typed_property < t_css_bespoke, ec_mso_border_insidev > prop_mso_border_insidev;
typedef typed_property < t_css_bespoke, ec_mso_border_left_alt > prop_mso_border_left_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_right_alt > prop_mso_border_right_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_shadow > prop_mso_border_shadow;
typedef typed_property < t_css_bespoke, ec_mso_border_style_alt > prop_mso_border_style_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_top_alt > prop_mso_border_top_alt;
typedef typed_property < t_css_bespoke, ec_mso_border_width_alt > prop_mso_border_width_alt;
typedef typed_property < t_css_bespoke, ec_mso_break_type > prop_mso_break_type;
typedef typed_property < t_css_bespoke, ec_mso_cell_special > prop_mso_cell_special;
typedef typed_property < t_css_bespoke, ec_mso_cellspacing > prop_mso_cellspacing;
typedef typed_property < t_css_bespoke, ec_mso_char_indent_count > prop_mso_char_indent_count;
typedef typed_property < t_css_bespoke, ec_mso_char_indent_size > prop_mso_char_indent_size;
typedef typed_property < t_css_bespoke, ec_mso_char_tracking > prop_mso_char_tracking;
typedef typed_property < t_css_bespoke, ec_mso_char_type > prop_mso_char_type;
typedef typed_property < t_css_bespoke, ec_mso_char_wrap > prop_mso_char_wrap;
typedef typed_property < t_css_bespoke, ec_mso_colour_alt > prop_mso_colour_alt;
typedef typed_property < t_css_bespoke, ec_mso_colour_index > prop_mso_colour_index;
typedef typed_property < t_css_bespoke, ec_mso_column_margin > prop_mso_column_margin;
typedef typed_property < t_css_bespoke, ec_mso_currency_font_family > prop_mso_currency_font_family;
typedef typed_property < t_css_bespoke, ec_mso_cyrillic_font_family > prop_mso_cyrillic_font_family;
typedef typed_property < t_css_bespoke, ec_mso_data_placement > prop_mso_data_placement;
typedef typed_property < t_css_bespoke, ec_mso_default_font_family > prop_mso_default_font_family;
typedef typed_property < t_css_bespoke, ec_mso_default_props > prop_mso_default_props;
typedef typed_property < t_css_bespoke, ec_mso_devanagari_font_family > prop_mso_devanagari_font_family;
typedef typed_property < t_css_bespoke, ec_mso_displayed_decimal_separator > prop_mso_displayed_decimal_separator;
typedef typed_property < t_css_bespoke, ec_mso_displayed_thousand_separator > prop_mso_displayed_thousand_separator;
typedef typed_property < t_css_bespoke, ec_mso_element > prop_mso_element;
typedef typed_property < t_css_bespoke, ec_mso_element_anchor_horizontal > prop_mso_element_anchor_horizontal;
typedef typed_property < t_css_bespoke, ec_mso_element_anchor_vertical > prop_mso_element_anchor_vertical;
typedef typed_property < t_css_bespoke, ec_mso_element_frame_height > prop_mso_element_frame_height;
typedef typed_property < t_css_bespoke, ec_mso_element_frame_hspace > prop_mso_element_frame_hspace;
typedef typed_property < t_css_bespoke, ec_mso_element_frame_width > prop_mso_element_frame_width;
typedef typed_property < t_css_bespoke, ec_mso_element_left > prop_mso_element_left;
typedef typed_property < t_css_bespoke, ec_mso_element_top > prop_mso_element_top;
typedef typed_property < t_css_bespoke, ec_mso_element_wrap > prop_mso_element_wrap;
typedef typed_property < t_css_bespoke, ec_mso_endnote_continuation_separator > prop_mso_endnote_continuation_separator;
typedef typed_property < t_css_bespoke, ec_mso_endnote_numbering_style > prop_mso_endnote_numbering_style;
typedef typed_property < t_css_bespoke, ec_mso_endnote_separator > prop_mso_endnote_separator;
typedef typed_property < t_css_bespoke, ec_mso_eudc_font_family > prop_mso_eudc_font_family;
typedef typed_property < t_css_bespoke, ec_mso_even_footer > prop_mso_even_footer;
typedef typed_property < t_css_bespoke, ec_mso_fareast_font_family > prop_mso_fareast_font_family;
typedef typed_property < t_css_bespoke, ec_mso_fareast_language > prop_mso_fareast_language;
typedef typed_property < t_css_bespoke, ec_mso_fareast_theme_font > prop_mso_fareast_theme_font;
typedef typed_property < t_css_bespoke, ec_mso_field_code > prop_mso_field_code;
typedef typed_property < t_css_bespoke, ec_mso_font_alt > prop_mso_font_alt;
typedef typed_property < t_css_bespoke, ec_mso_font_charset > prop_mso_font_charset;
typedef typed_property < t_css_bespoke, ec_mso_font_format > prop_mso_font_format;
typedef typed_property < t_css_bespoke, ec_mso_font_kerning > prop_mso_font_kerning;
typedef typed_property < t_css_bespoke, ec_mso_font_pitch > prop_mso_font_pitch;
typedef typed_property < t_css_bespoke, ec_mso_font_signature > prop_mso_font_signature;
typedef typed_property < t_css_bespoke, ec_mso_font_width > prop_mso_font_width;
typedef typed_property < t_css_bespoke, ec_mso_footer > prop_mso_footer;
typedef typed_property < t_css_bespoke, ec_mso_footer_margin > prop_mso_footer_margin;
typedef typed_property < t_css_bespoke, ec_mso_footnote_continuation_separator > prop_mso_footnote_continuation_separator;
typedef typed_property < t_css_bespoke, ec_mso_footnote_id > prop_mso_footnote_id;
typedef typed_property < t_css_bespoke, ec_mso_footnote_separator > prop_mso_footnote_separator;
typedef typed_property < t_css_bespoke, ec_mso_generic_font_family > prop_mso_generic_font_family;
typedef typed_property < t_css_bespoke, ec_mso_georgian_font_family > prop_mso_georgian_font_family;
typedef typed_property < t_css_bespoke, ec_mso_gram_e > prop_mso_gram_e;
typedef typed_property < t_css_bespoke, ec_mso_greek_font_family > prop_mso_greek_font_family;
typedef typed_property < t_css_bespoke, ec_mso_gurmukhi_font_family > prop_mso_gurmukhi_font_family;
typedef typed_property < t_css_bespoke, ec_mso_halfwidthkana_font_family > prop_mso_halfwidthkana_font_family;
typedef typed_property < t_css_bespoke, ec_mso_han_font_family > prop_mso_han_font_family;
typedef typed_property < t_css_bespoke, ec_mso_hangul_font_family > prop_mso_hangul_font_family;
typedef typed_property < t_css_bespoke, ec_mso_hansi_font_family > prop_mso_hansi_font_family;
typedef typed_property < t_css_bespoke, ec_mso_hansi_theme_font > prop_mso_hansi_theme_font;
typedef typed_property < t_css_bespoke, ec_mso_header > prop_mso_header;
typedef typed_property < t_css_bespoke, ec_mso_header_margin > prop_mso_header_margin;
typedef typed_property < t_css_bespoke, ec_mso_hebrew_font_family > prop_mso_hebrew_font_family;
typedef typed_property < t_css_bespoke, ec_mso_height_rule > prop_mso_height_rule;
typedef typed_property < t_css_bespoke, ec_mso_height_source > prop_mso_height_source;
typedef typed_property < t_css_bespoke, ec_mso_hide > prop_mso_hide;
typedef typed_property < t_css_bespoke, ec_mso_highlight > prop_mso_highlight;
typedef typed_property < t_css_bespoke, ec_mso_hyphenate > prop_mso_hyphenate;
typedef typed_property < t_css_bespoke, ec_mso_ignore > prop_mso_ignore;
typedef typed_property < t_css_bespoke, ec_mso_kana_font_family > prop_mso_kana_font_family;
typedef typed_property < t_css_bespoke, ec_mso_kannada_font_family > prop_mso_kannada_font_family;
typedef typed_property < t_css_bespoke, ec_mso_kinsoku_overflow > prop_mso_kinsoku_overflow;
typedef typed_property < t_css_bespoke, ec_mso_lao_font_family > prop_mso_lao_font_family;
typedef typed_property < t_css_bespoke, ec_mso_latin_font_family > prop_mso_latin_font_family;
typedef typed_property < t_css_bespoke, ec_mso_latinext_font_family > prop_mso_latinext_font_family;
typedef typed_property < t_css_bespoke, ec_mso_layout_grid_align > prop_mso_layout_grid_align;
typedef typed_property < t_css_bespoke, ec_mso_level_font_family > prop_mso_level_font_family;
typedef typed_property < t_css_bespoke, ec_mso_level_indent > prop_mso_level_indent;
typedef typed_property < t_css_bespoke, ec_mso_level_legacy > prop_mso_level_legacy;
typedef typed_property < t_css_bespoke, ec_mso_level_legacy_indent > prop_mso_level_legacy_indent;
typedef typed_property < t_css_bespoke, ec_mso_level_legacy_space > prop_mso_level_legacy_space;
typedef typed_property < t_css_bespoke, ec_mso_level_number_format > prop_mso_level_number_format;
typedef typed_property < t_css_bespoke, ec_mso_level_number_position > prop_mso_level_number_position;
typedef typed_property < t_css_bespoke, ec_mso_level_size > prop_mso_level_size;
typedef typed_property < t_css_bespoke, ec_mso_level_start_at > prop_mso_level_start_at;
typedef typed_property < t_css_bespoke, ec_mso_level_style_link > prop_mso_level_style_link;
typedef typed_property < t_css_bespoke, ec_mso_level_tab_stop > prop_mso_level_tab_stop;
typedef typed_property < t_css_bespoke, ec_mso_level_text > prop_mso_level_text;
typedef typed_property < t_css_bespoke, ec_mso_line_height_alt > prop_mso_line_height_alt;
typedef typed_property < t_css_bespoke, ec_mso_line_height_rule > prop_mso_line_height_rule;
typedef typed_property < t_css_bespoke, ec_mso_line_spacing > prop_mso_line_spacing;
typedef typed_property < t_css_bespoke, ec_mso_linked_frame > prop_mso_linked_frame;
typedef typed_property < t_css_bespoke, ec_mso_list > prop_mso_list;
typedef typed_property < t_css_bespoke, ec_mso_list_id > prop_mso_list_id;
typedef typed_property < t_css_bespoke, ec_mso_list_template_ids > prop_mso_list_template_ids;
typedef typed_property < t_css_bespoke, ec_mso_list_type > prop_mso_list_type;
typedef typed_property < t_css_bespoke, ec_mso_malayalam_font_family > prop_mso_malayalam_font_family;
typedef typed_property < t_css_bespoke, ec_mso_margin_bottom_alt > prop_mso_margin_bottom_alt;
typedef typed_property < t_css_bespoke, ec_mso_margin_left_alt > prop_mso_margin_left_alt;
typedef typed_property < t_css_bespoke, ec_mso_margin_top_alt > prop_mso_margin_top_alt;
typedef typed_property < t_css_bespoke, ec_mso_no_proof > prop_mso_no_proof;
typedef typed_property < t_css_bespoke, ec_mso_number_format > prop_mso_number_format;
typedef typed_property < t_css_bespoke, ec_mso_oriya_font_family > prop_mso_oriya_font_family;
typedef typed_property < t_css_bespoke, ec_mso_outline_level > prop_mso_outline_level;
typedef typed_property < t_css_bespoke, ec_mso_padding_alt > prop_mso_padding_alt;
typedef typed_property < t_css_bespoke, ec_mso_page_border_surround_footer > prop_mso_page_border_surround_footer;
typedef typed_property < t_css_bespoke, ec_mso_page_border_surround_header > prop_mso_page_border_surround_header;
typedef typed_property < t_css_bespoke, ec_mso_page_orientation > prop_mso_page_orientation;
typedef typed_property < t_css_bespoke, ec_mso_pagination > prop_mso_pagination;
typedef typed_property < t_css_bespoke, ec_mso_paper_source > prop_mso_paper_source;
typedef typed_property < t_css_bespoke, ec_mso_para_margin > prop_mso_para_margin;
typedef typed_property < t_css_bespoke, ec_mso_para_margin_bottom > prop_mso_para_margin_bottom;
typedef typed_property < t_css_bespoke, ec_mso_para_margin_left > prop_mso_para_margin_left;
typedef typed_property < t_css_bespoke, ec_mso_para_margin_right > prop_mso_para_margin_right;
typedef typed_property < t_css_bespoke, ec_mso_para_margin_top > prop_mso_para_margin_top;
typedef typed_property < t_css_bespoke, ec_mso_pattern > prop_mso_pattern;
typedef typed_property < t_css_bespoke, ec_mso_position_horizontal > prop_mso_position_horizontal;
typedef typed_property < t_css_bespoke, ec_mso_position_horizontal_relative > prop_mso_position_horizontal_relative;
typedef typed_property < t_css_bespoke, ec_mso_position_vertical > prop_mso_position_vertical;
typedef typed_property < t_css_bespoke, ec_mso_position_vertical_relative > prop_mso_position_vertical_relative;
typedef typed_property < t_css_bespoke, ec_mso_protection > prop_mso_protection;
typedef typed_property < t_css_bespoke, ec_mso_rotate > prop_mso_rotate;
typedef typed_property < t_css_bespoke, ec_mso_row_margin_left > prop_mso_row_margin_left;
typedef typed_property < t_css_bespoke, ec_mso_row_margin_right > prop_mso_row_margin_right;
typedef typed_property < t_css_bespoke, ec_mso_shading > prop_mso_shading;
typedef typed_property < t_css_bespoke, ec_mso_spacerun > prop_mso_spacerun;
typedef typed_property < t_css_bespoke, ec_mso_special_character > prop_mso_special_character;
typedef typed_property < t_css_bespoke, ec_mso_special_format > prop_mso_special_format;
typedef typed_property < t_css_bespoke, ec_mso_spl_e > prop_mso_spl_e;
typedef typed_property < t_css_bespoke, ec_mso_style_id > prop_mso_style_id;
typedef typed_property < t_css_bespoke, ec_mso_style_link > prop_mso_style_link;
typedef typed_property < t_css_bespoke, ec_mso_style_locked > prop_mso_style_locked;
typedef typed_property < t_css_bespoke, ec_mso_style_name > prop_mso_style_name;
typedef typed_property < t_css_bespoke, ec_mso_style_next > prop_mso_style_next;
typedef typed_property < t_css_bespoke, ec_mso_style_noshow > prop_mso_style_noshow;
typedef typed_property < t_css_bespoke, ec_mso_style_parent > prop_mso_style_parent;
typedef typed_property < t_css_bespoke, ec_mso_style_priority > prop_mso_style_priority;
typedef typed_property < t_css_bespoke, ec_mso_style_qformat > prop_mso_style_qformat;
typedef typed_property < t_css_bespoke, ec_mso_style_type > prop_mso_style_type;
typedef typed_property < t_css_bespoke, ec_mso_style_unhide > prop_mso_style_unhide;
typedef typed_property < t_css_bespoke, ec_mso_style_update > prop_mso_style_update;
typedef typed_property < t_css_bespoke, ec_mso_symbol_font_family > prop_mso_symbol_font_family;
typedef typed_property < t_css_bespoke, ec_mso_syriac_font_family > prop_mso_syriac_font_family;
typedef typed_property < t_css_bespoke, ec_mso_tab_count > prop_mso_tab_count;
typedef typed_property < t_css_bespoke, ec_mso_table_anchor_horizontal > prop_mso_table_anchor_horizontal;
typedef typed_property < t_css_bespoke, ec_mso_table_anchor_vertical > prop_mso_table_anchor_vertical;
typedef typed_property < t_css_bespoke, ec_mso_table_layout_alt > prop_mso_table_layout_alt;
typedef typed_property < t_css_bespoke, ec_mso_table_left > prop_mso_table_left;
typedef typed_property < t_css_bespoke, ec_mso_table_lspace > prop_mso_table_lspace;
typedef typed_property < t_css_bespoke, ec_mso_table_overlap > prop_mso_table_overlap;
typedef typed_property < t_css_bespoke, ec_mso_table_rspace > prop_mso_table_rspace;
typedef typed_property < t_css_bespoke, ec_mso_table_top > prop_mso_table_top;
typedef typed_property < t_css_bespoke, ec_mso_tamil_font_family > prop_mso_tamil_font_family;
typedef typed_property < t_css_bespoke, ec_mso_telugu_font_family > prop_mso_telugu_font_family;
typedef typed_property < t_css_bespoke, ec_mso_text_animation > prop_mso_text_animation;
typedef typed_property < t_css_bespoke, ec_mso_text_raise > prop_mso_text_raise;
typedef typed_property < t_css_bespoke, ec_mso_thaana_font_family > prop_mso_thaana_font_family;
typedef typed_property < t_css_bespoke, ec_mso_thai_font_family > prop_mso_thai_font_family;
typedef typed_property < t_css_bespoke, ec_mso_themecolour > prop_mso_themecolour;
typedef typed_property < t_css_bespoke, ec_mso_themeshade > prop_mso_themeshade;
typedef typed_property < t_css_bespoke, ec_mso_title_page > prop_mso_title_page;
typedef typed_property < t_css_bespoke, ec_mso_tstyle_colband_size > prop_mso_tstyle_colband_size;
typedef typed_property < t_css_bespoke, ec_mso_tstyle_rowband_size > prop_mso_tstyle_rowband_size;
typedef typed_property < t_css_bespoke, ec_mso_width_alt > prop_mso_width_alt;
typedef typed_property < t_css_bespoke, ec_mso_width_source > prop_mso_width_source;
typedef typed_property < t_css_bespoke, ec_mso_wrap_distance_bottom > prop_mso_wrap_distance_bottom;
typedef typed_property < t_css_bespoke, ec_mso_wrap_distance_left > prop_mso_wrap_distance_left;
typedef typed_property < t_css_bespoke, ec_mso_wrap_distance_right > prop_mso_wrap_distance_right;
typedef typed_property < t_css_bespoke, ec_mso_wrap_distance_top > prop_mso_wrap_distance_top;
typedef typed_property < t_css_bespoke, ec_mso_wrap_edited > prop_mso_wrap_edited;
typedef typed_property < t_css_bespoke, ec_mso_yfti_firstrow > prop_mso_yfti_firstrow;
typedef typed_property < t_css_bespoke, ec_mso_yfti_irow > prop_mso_yfti_irow;
typedef typed_property < t_css_bespoke, ec_mso_yfti_lastrow > prop_mso_yfti_lastrow;
typedef typed_property < t_css_bespoke, ec_mso_yfti_tbllook > prop_mso_yfti_tbllook;

typedef typed_property < t_css_bespoke, ec_o_table_baseline > prop_o_table_baseline;
typedef typed_property < t_css_bespoke, ec_o_text_overflow > prop_o_text_overflow;
typedef typed_property < t_css_bespoke, ec_o_transform > prop_o_transform;
typedef typed_property < t_css_bespoke, ec_o_transform_origin > prop_o_transform_origin;
typedef typed_property < t_css_bespoke, ec_o_transition > prop_o_transition;
typedef typed_property < t_css_bespoke, ec_o_transition_delay > prop_o_transition_delay;
typedef typed_property < t_css_bespoke, ec_o_transition_duration > prop_o_transition_duration;
typedef typed_property < t_css_bespoke, ec_o_transition_property > prop_o_transition_property;
typedef typed_property < t_css_bespoke, ec_o_transition_timing_function > prop_o_transition_timing_function;
typedef typed_property < t_css_bespoke, ec_o_tab_size > prop_o_tab_size;

typedef typed_property < t_css_bespoke, ec_apple_dashboard_region > prop_apple_dashboard_region;
typedef typed_property < t_css_bespoke, ec_epub_caption_side > prop_epub_caption_side;
typedef typed_property < t_css_bespoke, ec_epub_hyphens > prop_epub_hyphens;
typedef typed_property < t_css_bespoke, ec_epub_text_combine > prop_epub_text_combine;
typedef typed_property < t_css_bespoke, ec_epub_text_orientation > prop_epub_text_orientation;
typedef typed_property < t_css_bespoke, ec_epub_text_transform > prop_epub_text_transform;
typedef typed_property < t_css_bespoke, ec_ms_animation > prop_ms_animation;
typedef typed_property < t_css_bespoke, ec_ms_animation_delay > prop_ms_animation_delay;
typedef typed_property < t_css_bespoke, ec_ms_animation_direction > prop_ms_animation_direction;
typedef typed_property < t_css_bespoke, ec_ms_animation_duration > prop_ms_animation_duration;
typedef typed_property < t_css_bespoke, ec_ms_animation_fill_mode > prop_ms_animation_fill_mode;
typedef typed_property < t_css_bespoke, ec_ms_animation_iteration_count > prop_ms_animation_iteration_count;
typedef typed_property < t_css_bespoke, ec_ms_animation_name > prop_ms_animation_name;
typedef typed_property < t_css_bespoke, ec_ms_animation_play_state > prop_ms_animation_play_state;
typedef typed_property < t_css_bespoke, ec_ms_animation_timing_function > prop_ms_animation_timing_function;
typedef typed_property < t_css_bespoke, ec_ms_block_progression > prop_ms_block_progression;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_chaining > prop_ms_content_zoom_chaining;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_limit > prop_ms_content_zoom_limit;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_limit_max > prop_ms_content_zoom_limit_max;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_limit_min > prop_ms_content_zoom_limit_min;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_snap > prop_ms_content_zoom_snap;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_snap_points > prop_ms_content_zoom_snap_points;
typedef typed_property < t_css_bespoke, ec_ms_content_zoom_snap_type > prop_ms_content_zoom_snap_type;
typedef typed_property < t_css_bespoke, ec_ms_content_zooming > prop_ms_content_zooming;
typedef typed_property < t_css_bespoke, ec_ms_flex_align > prop_ms_flex_align;
typedef typed_property < t_css_bespoke, ec_ms_flex_item_align > prop_ms_flex_item_align;
typedef typed_property < t_css_bespoke, ec_ms_flex_line_pack > prop_ms_flex_line_pack;
typedef typed_property < t_css_bespoke, ec_ms_flex_negative > prop_ms_flex_negative;
typedef typed_property < t_css_bespoke, ec_ms_flex_order > prop_ms_flex_order;
typedef typed_property < t_css_bespoke, ec_ms_flex_pack > prop_ms_flex_pack;
typedef typed_property < t_css_bespoke, ec_ms_flex_positive > prop_ms_flex_positive;
typedef typed_property < t_css_bespoke, ec_ms_flex_preferred_size > prop_ms_flex_preferred_size;
typedef typed_property < t_css_bespoke, ec_ms_font_feature_settings > prop_ms_font_feature_settings;
typedef typed_property < t_css_bespoke, ec_ms_grid_columns > prop_ms_grid_columns;
typedef typed_property < t_css_bespoke, ec_ms_grid_rows > prop_ms_grid_rows;
typedef typed_property < t_css_bespoke, ec_ms_high_contrast_adjust > prop_ms_high_contrast_adjust;
typedef typed_property < t_css_bespoke, ec_ms_hyphenate_limit_chars > prop_ms_hyphenate_limit_chars;
typedef typed_property < t_css_bespoke, ec_ms_hyphenate_limit_lines > prop_ms_hyphenate_limit_lines;
typedef typed_property < t_css_bespoke, ec_ms_hyphenate_limit_zone > prop_ms_hyphenate_limit_zone;
typedef typed_property < t_css_bespoke, ec_ms_ime_align > prop_ms_ime_align;
typedef typed_property < t_css_bespoke, ec_ms_interpolation_mode > prop_ms_interpolation_mode;
typedef typed_property < t_css_bespoke, ec_ms_scroll_chaining > prop_ms_scroll_chaining;
typedef typed_property < t_css_bespoke, ec_ms_scroll_limit > prop_ms_scroll_limit;
typedef typed_property < t_css_bespoke, ec_ms_scroll_limit_x_max > prop_ms_scroll_limit_x_max;
typedef typed_property < t_css_bespoke, ec_ms_scroll_limit_x_min > prop_ms_scroll_limit_x_min;
typedef typed_property < t_css_bespoke, ec_ms_scroll_limit_y_max > prop_ms_scroll_limit_y_max;
typedef typed_property < t_css_bespoke, ec_ms_scroll_limit_y_min > prop_ms_scroll_limit_y_min;
typedef typed_property < t_css_bespoke, ec_ms_scroll_rails > prop_ms_scroll_rails;
typedef typed_property < t_css_bespoke, ec_ms_scroll_snap_points_x > prop_ms_scroll_snap_points_x;
typedef typed_property < t_css_bespoke, ec_ms_scroll_snap_points_y > prop_ms_scroll_snap_points_y;
typedef typed_property < t_css_bespoke, ec_ms_scroll_snap_type > prop_ms_scroll_snap_type;
typedef typed_property < t_css_bespoke, ec_ms_scroll_snap_x > prop_ms_scroll_snap_x;
typedef typed_property < t_css_bespoke, ec_ms_scroll_snap_y > prop_ms_scroll_snap_y;
typedef typed_property < t_css_bespoke, ec_ms_scroll_translation > prop_ms_scroll_translation;
typedef typed_property < t_css_bespoke, ec_ms_text_combine_horizontal > prop_ms_text_combine_horizontal;
typedef typed_property < t_css_bespoke, ec_ms_touch_action > prop_ms_touch_action;
typedef typed_property < t_css_bespoke, ec_ms_touch_select > prop_ms_touch_select;
typedef typed_property < t_css_bespoke, ec_ms_transition > prop_ms_transition;
typedef typed_property < t_css_bespoke, ec_ms_transition_delay > prop_ms_transition_delay;
typedef typed_property < t_css_bespoke, ec_ms_transition_duration > prop_ms_transition_duration;
typedef typed_property < t_css_bespoke, ec_ms_transition_property > prop_ms_transition_property;
typedef typed_property < t_css_bespoke, ec_ms_transition_timing_function > prop_ms_transition_timing_function;
typedef typed_property < t_css_bespoke, ec_ms_wrap_margin > prop_ms_wrap_margin;
typedef typed_property < t_css_bespoke, ec_o_border_image > prop_o_border_image;
typedef typed_property < t_css_bespoke, ec_o_device_pixel_ratio > prop_o_device_pixel_ratio;
typedef typed_property < t_css_bespoke, ec_o_focus_opacity > prop_o_focus_opacity;
typedef typed_property < t_css_bespoke, ec_o_link > prop_o_link;
typedef typed_property < t_css_bespoke, ec_o_link_source > prop_o_link_source;
typedef typed_property < t_css_bespoke, ec_o_mini_fold > prop_o_mini_fold;
typedef typed_property < t_css_bespoke, ec_o_object_fit > prop_o_object_fit;
typedef typed_property < t_css_bespoke, ec_o_object_position > prop_o_object_position;
typedef typed_property < t_css_bespoke, ec_o_tab_size > prop_o_tab_size;
typedef typed_property < t_css_bespoke, ec_o_table_baseline > prop_o_table_baseline;
typedef typed_property < t_css_bespoke, ec_o_transform > prop_o_transform;
typedef typed_property < t_css_bespoke, ec_o_transform_origin > prop_o_transform_origin;
typedef typed_property < t_css_bespoke, ec_o_transition > prop_o_transition;
typedef typed_property < t_css_bespoke, ec_o_transition_delay > prop_o_transition_delay;
typedef typed_property < t_css_bespoke, ec_o_transition_duration > prop_o_transition_duration;
typedef typed_property < t_css_bespoke, ec_o_transition_property > prop_o_transition_property;
typedef typed_property < t_css_bespoke, ec_o_transition_timing_function > prop_o_transition_timing_function;
typedef typed_property < t_css_bespoke, ec_wap_accesskey > prop_wap_accesskey;
typedef typed_property < t_css_bespoke, ec_wap_input_format > prop_wap_input_format;
typedef typed_property < t_css_bespoke, ec_wap_input_required > prop_wap_input_required;
typedef typed_property < t_css_bespoke, ec_wap_marquee_dir > prop_wap_marquee_dir;
typedef typed_property < t_css_bespoke, ec_wap_marquee_loop > prop_wap_marquee_loop;
typedef typed_property < t_css_bespoke, ec_wap_marquee_speed > prop_wap_marquee_speed;
typedef typed_property < t_css_bespoke, ec_wap_marquee_style > prop_wap_marquee_style;
typedef typed_property < t_css_bespoke, ec_xv_interpret_as > prop_xv_interpret_as;
typedef typed_property < t_css_bespoke, ec_xv_phonemes > prop_xv_phonemes;
typedef typed_property < t_css_bespoke, ec_xv_voice_balance > prop_xv_voice_balance;
typedef typed_property < t_css_bespoke, ec_xv_voice_duration > prop_xv_voice_duration;
typedef typed_property < t_css_bespoke, ec_xv_voice_pitch > prop_xv_voice_pitch;
typedef typed_property < t_css_bespoke, ec_xv_voice_pitch_range > prop_xv_voice_pitch_range;
typedef typed_property < t_css_bespoke, ec_xv_voice_rate > prop_xv_voice_rate;
typedef typed_property < t_css_bespoke, ec_xv_voice_stress > prop_xv_voice_stress;
typedef typed_property < t_css_bespoke, ec_xv_voice_volume > prop_xv_voice_volume;


#define CSS_PROPERTIES_1 \
    prop_custom, \
    prop_accent_colour, \
    prop_additive_symbols, \
    prop_align_content, \
    prop_align_items, \
    prop_align_self, \
    prop_alignment_baseline, \
    prop_all, \
    prop_animation, \
    prop_animation_composition, \
    prop_animation_delay, \
    prop_animation_delay_end, \
    prop_animation_delay_start, \
    prop_animation_direction, \
    prop_animation_duration, \
    prop_animation_fill_mode, \
    prop_animation_iteration_count, \
    prop_animation_name, \
    prop_animation_play_state, \
    prop_animation_range, \
    prop_animation_timeline, \
    prop_animation_timing_function, \
    prop_appearance, \
    prop_ascent, \
    prop_ascent_override, \
    prop_aspect_ratio, \
    prop_azimuth, \
    prop_backface_visibility, \
    prop_background, \
    prop_background_attachment, \
    prop_background_blend_mode, \
    prop_background_clip, \
    prop_background_colour, \
    prop_background_image, \
    prop_background_origin, \
    prop_background_position, \
    prop_background_repeat, \
    prop_background_size, \
    prop_baseline, \
    prop_baseline_shift, \
    prop_baseline_source, \
    prop_base_palette, \
    prop_bbox, \
    prop_block_ellipsis, \
    prop_block_size, \
    prop_block_step, \
    prop_block_step_align, \
    prop_block_step_insert, \
    prop_block_step_round, \
    prop_block_step_size, \
    prop_bookmark_label, \
    prop_bookmark_level, \
    prop_bookmark_state, \
    prop_border, \
    prop_border_block, \
    prop_border_block_colour, \
    prop_border_block_end, \
    prop_border_block_end_colour, \
    prop_border_block_end_style, \
    prop_border_block_end_width, \
    prop_border_block_start, \
    prop_border_block_start_colour, \
    prop_border_block_start_style, \
    prop_border_block_start_width, \
    prop_border_block_style, \
    prop_border_block_width, \
    prop_border_bottom, \
    prop_border_bottom_colour, \
    prop_border_bottom_left_radius, \
    prop_border_bottom_right_radius, \
    prop_border_bottom_style, \
    prop_border_bottom_width, \
    prop_border_boundary, \
    prop_border_collapse, \
    prop_border_colour, \
    prop_border_end_end_radius, \
    prop_border_end_start_radius, \
    prop_border_image, \
    prop_border_image_outset, \
    prop_border_image_repeat, \
    prop_border_image_slice, \
    prop_border_image_source, \
    prop_border_image_width, \
    prop_border_inline, \
    prop_border_inline_colour, \
    prop_border_inline_end, \
    prop_border_inline_end_colour, \
    prop_border_inline_end_style, \
    prop_border_inline_end_width, \
    prop_border_inline_start, \
    prop_border_inline_start_colour, \
    prop_border_inline_start_style, \
    prop_border_inline_start_width, \
    prop_border_inline_style, \
    prop_border_inline_width, \
    prop_border_left, \
    prop_border_left_colour, \
    prop_border_left_style, \
    prop_border_left_width, \
    prop_border_radius, \
    prop_border_right, \
    prop_border_right_colour, \
    prop_border_right_style, \
    prop_border_right_width, \
    prop_border_spacing, \
    prop_border_start_end_radius, \
    prop_border_start_start_radius, \
    prop_border_style, \
    prop_border_top, \
    prop_border_top_colour, \
    prop_border_top_left_radius, \
    prop_border_top_right_radius, \
    prop_border_top_style, \
    prop_border_top_width, \
    prop_border_width, \
    prop_bottom, \
    prop_box_decoration_break, \
    prop_box_flex, \
    prop_box_orient, \
    prop_box_shadow, \
    prop_box_sizing, \
    prop_box_snap, \
    prop_break_after, \
    prop_break_before, \
    prop_break_inside, \
    prop_cap_height, \
    prop_caption_side, \
    prop_caret, \
    prop_caret_colour, \
    prop_caret_shape, \
    prop_centre_line, \
    prop_chains, \
    prop_clear, \
    prop_clip, \
    prop_clip_path, \
    prop_clip_rule, \
    prop_colour, \
    prop_colour_adjust, \
    prop_colour_interpolation_filters, \
    prop_colour_interpolation, \
    prop_colour_profile, \
    prop_colour_rendering, \
    prop_colour_scheme, \
    prop_column_count, \
    prop_column_fill, \
    prop_column_gap, \
    prop_column_rule, \
    prop_column_rule_colour, \
    prop_column_rule_style, \
    prop_column_rule_width, \
    prop_column_span, \
    prop_column_width, \
    prop_columns, \
    prop_contain, \
    prop_contain_intrinsic_block_size, \
    prop_contain_intrinsic_height, \
    prop_contain_intrinsic_inline_size, \
    prop_contain_intrinsic_size, \
    prop_contain_intrinsic_width, \
    prop_container, \
    prop_container_name, \
    prop_container_type, \
    prop_content, \
    prop_content_visibility, \
    prop_context, \
    prop_continue, \
    prop_counter_increment, \
    prop_counter_reset, \
    prop_counter_set, \
    prop_cue, \
    prop_cue_after, \
    prop_cue_before, \
    prop_cursor, \
    prop_cx, \
    prop_cy, \
    prop_d, \
    prop_definition_src, \
    prop_descent, \
    prop_descent_override, \
    prop_direction, \
    prop_display, \
    prop_dominant_baseline, \
    prop_elevation, \
    prop_empty_cells, \
    prop_enable_background, \
    prop_epub_text_decoration, \
    prop_epub_text_emphasis, \
    prop_epub_text_emphasis_colour, \
    prop_epub_text_emphasis_style, \
    prop_epub_word_break, \
    prop_epub_writing_mode, \
    prop_error, \
    prop_fallback, \
    prop_fill, \
    prop_fill_break, \
    prop_fill_colour, \
    prop_fill_image, \
    prop_fill_opacity, \
    prop_fill_origin, \
    prop_fill_position, \
    prop_fill_repeat, \
    prop_fill_rule, \
    prop_fill_size, \
    prop_filter, \
    prop_flex, \
    prop_flex_basis, \
    prop_flex_direction, \
    prop_flex_flow, \
    prop_flex_grow, \
    prop_flex_shrink, \
    prop_flex_wrap, \
    prop_float, \
    prop_float_defer, \
    prop_float_offset, \
    prop_float_reference, \
    prop_flood_colour, \
    prop_flood_opacity, \
    prop_flow, \
    prop_flow_from, \
    prop_flow_into, \
    prop_font, \
    prop_font_display, \
    prop_font_family, \
    prop_font_feature_settings, \
    prop_font_kerning, \
    prop_font_language_override, \
    prop_font_named_instance, \
    prop_font_optical_sizing, \
    prop_font_palette, \
    prop_font_size, \
    prop_font_size_adjust, \
    prop_font_stretch, \
    prop_font_style, \
    prop_font_synthesis, \
    prop_font_synthesis_small_caps, \
    prop_font_synthesis_style, \
    prop_font_synthesis_weight, \
    prop_font_variant, \
    prop_font_variant_alternates, \
    prop_font_variant_caps, \
    prop_font_variant_east_asian, \
    prop_font_variant_emoji, \
    prop_font_variant_ligatures, \
    prop_font_variant_numeric, \
    prop_font_variant_position, \
    prop_font_variation_settings, \
    prop_font_weight, \
    prop_footnote_display, \
    prop_footnote_policy, \
    prop_forced_colour_adjust, \
    prop_gap, \
    prop_glyph_orientation_horizontal, \
    prop_glyph_orientation_vertical, \
    prop_grid, \
    prop_grid_area, \
    prop_grid_auto_columns, \
    prop_grid_auto_flow, \
    prop_grid_auto_rows, \
    prop_grid_column, \
    prop_grid_column_end, \
    prop_grid_column_start, \
    prop_grid_row, \
    prop_grid_row_end, \
    prop_grid_row_start, \
    prop_grid_template, \
    prop_grid_template_areas, \
    prop_grid_template_columns, \
    prop_grid_template_rows, \
    prop_hanging_punctuation, \
    prop_height, \
    prop_hyphenate_character, \
    prop_hyphenate_limit_chars, \
    prop_hyphenate_limit_last, \
    prop_hyphenate_limit_lines, \
    prop_hyphenate_limit_zone, \
    prop_hyphens, \
    prop_image_orientation, \
    prop_image_rendering, \
    prop_image_resolution, \
    prop_ime_mode, \
    prop_inherit, \
    prop_initial_letter, \
    prop_initial_letter_align, \
    prop_initial_letter_wrap, \
    prop_inline_size, \
    prop_inline_sizing, \
    prop_inset, \
    prop_inset_block, \
    prop_inset_block_end, \
    prop_inset_block_start, \
    prop_inset_inline, \
    prop_inset_inline_end, \
    prop_inset_inline_start, \
    prop_isolation, \
    prop_justify_content, \
    prop_justify_items, \
    prop_justify_self, \
    prop_kerning, \
    prop_leading_trim, \
    prop_left, \
    prop_letter_spacing, \
    prop_lighting_colour, \
    prop_line_break, \
    prop_line_clamp, \
    prop_line_gap_override, \
    prop_line_grid, \
    prop_line_height, \
    prop_line_height_step, \
    prop_line_padding, \
    prop_line_snap, \
    prop_list_style, \
    prop_list_style_image, \
    prop_list_style_position, \
    prop_list_style_type

#define LAST_CSS_1_PROP ec_list_style_type

#define CSS_PROPERTIES_2 \
    prop_margin, \
    prop_margin_block, \
    prop_margin_block_end, \
    prop_margin_block_start, \
    prop_margin_bottom, \
    prop_margin_break, \
    prop_margin_inline, \
    prop_margin_inline_end, \
    prop_margin_inline_start, \
    prop_margin_left, \
    prop_margin_right, \
    prop_margin_top, \
    prop_margin_trim, \
    prop_marker, \
    prop_marker_end, \
    prop_marker_knockout_left, \
    prop_marker_knockout_right, \
    prop_marker_mid, \
    prop_marker_offset, \
    prop_marker_pattern, \
    prop_marker_segment, \
    prop_marker_side, \
    prop_marker_start, \
    prop_marks, \
    prop_marquee_direction, \
    prop_marquee_loop, \
    prop_marquee_speed, \
    prop_marquee_style, \
    prop_mask, \
    prop_mask_border, \
    prop_mask_border_mode, \
    prop_mask_border_outset, \
    prop_mask_border_repeat, \
    prop_mask_border_slice, \
    prop_mask_border_source, \
    prop_mask_border_width, \
    prop_mask_clip, \
    prop_mask_composite, \
    prop_mask_image, \
    prop_mask_mode, \
    prop_mask_origin, \
    prop_mask_position, \
    prop_mask_repeat, \
    prop_mask_size, \
    prop_mask_type, \
    prop_mathline, \
    prop_max_block_size, \
    prop_max_height, \
    prop_max_inline_size, \
    prop_max_lines, \
    prop_max_width, \
    prop_min_block_size, \
    prop_min_height, \
    prop_min_inline_size, \
    prop_min_intrinsic_sizing, \
    prop_min_width, \
    prop_mix_blend_mode, \
    prop_name, \
    prop_nav_down, \
    prop_nav_left, \
    prop_nav_right, \
    prop_nav_up, \
    prop_negative, \
    prop_object_fit, \
    prop_object_position, \
    prop_offset, \
    prop_offset_anchor, \
    prop_offset_distance, \
    prop_offset_path, \
    prop_offset_position, \
    prop_offset_rotate, \
    prop_opacity, \
    prop_order, \
    prop_orphans, \
    prop_outline, \
    prop_outline_colour, \
    prop_outline_offset, \
    prop_outline_style, \
    prop_outline_width, \
    prop_overflow, \
    prop_overflow_anchor, \
    prop_overflow_block, \
    prop_overflow_clip_margin, \
    prop_overflow_clip_margin_block, \
    prop_overflow_clip_margin_block_end, \
    prop_overflow_clip_margin_block_start, \
    prop_overflow_clip_margin_bottom, \
    prop_overflow_clip_margin_inline, \
    prop_overflow_clip_margin_inline_end, \
    prop_overflow_clip_margin_inline_start, \
    prop_overflow_clip_margin_left, \
    prop_overflow_clip_margin_right, \
    prop_overflow_clip_margin_top, \
    prop_overflow_inline, \
    prop_overflow_style, \
    prop_overflow_wrap, \
    prop_overflow_x, \
    prop_overflow_y, \
    prop_overscroll_behavior, \
    prop_overscroll_behavior_block, \
    prop_overscroll_behavior_inline, \
    prop_overscroll_behavior_x, \
    prop_overscroll_behavior_y, \
    prop_override_colours, \
    prop_pad, \
    prop_padding, \
    prop_padding_block, \
    prop_padding_block_end, \
    prop_padding_block_start, \
    prop_padding_bottom, \
    prop_padding_inline, \
    prop_padding_inline_end, \
    prop_padding_inline_start, \
    prop_padding_left, \
    prop_padding_right, \
    prop_padding_top, \
    prop_page, \
    prop_page_break_after, \
    prop_page_break_before, \
    prop_page_break_inside, \
    prop_page, \
    prop_paint_order, \
    prop_panose_1, \
    prop_pause, \
    prop_pause_after, \
    prop_pause_before, \
    prop_perspective, \
    prop_perspective_origin, \
    prop_pitch, \
    prop_pitch_range, \
    prop_place_content, \
    prop_place_items, \
    prop_place_self, \
    prop_play_during, \
    prop_pointer_events, \
    prop_position, \
    prop_prefix, \
    prop_print_colour_adjust, \
    prop_quotes, \
    prop_r, \
    prop_range, \
    prop_region_fragment, \
    prop_rendering_intent, \
    prop_resize, \
    prop_rest, \
    prop_rest_after, \
    prop_rest_before, \
    prop_richness, \
    prop_right, \
    prop_rotate, \
    prop_row_gap, \
    prop_ruby_align, \
    prop_ruby_merge, \
    prop_ruby_overhang, \
    prop_ruby_position, \
    prop_running, \
    prop_rx, \
    prop_ry, \
    prop_scale, \
    prop_scroll_behavior, \
    prop_scroll_margin, \
    prop_scroll_margin_block, \
    prop_scroll_margin_block_end, \
    prop_scroll_margin_block_start, \
    prop_scroll_margin_bottom, \
    prop_scroll_margin_inline, \
    prop_scroll_margin_inline_end, \
    prop_scroll_margin_inline_start, \
    prop_scroll_margin_left, \
    prop_scroll_margin_right, \
    prop_scroll_margin_top, \
    prop_scroll_padding, \
    prop_scroll_padding_block, \
    prop_scroll_padding_block_end, \
    prop_scroll_padding_block_start, \
    prop_scroll_padding_bottom, \
    prop_scroll_padding_inline, \
    prop_scroll_padding_inline_end, \
    prop_scroll_padding_inline_start, \
    prop_scroll_padding_left, \
    prop_scroll_padding_right, \
    prop_scroll_padding_top, \
    prop_scroll_snap_align, \
    prop_scroll_snap_stop, \
    prop_scroll_snap_type, \
    prop_scroll_timeline, \
    prop_scroll_timeline_axis, \
    prop_scroll_timeline_name, \
    prop_scrollbar_colour, \
    prop_scrollbar_gutter, \
    prop_scrollbar_width, \
    prop_shape_image_threshold, \
    prop_shape_inside, \
    prop_shape_margin, \
    prop_shape_outside, \
    prop_size, \
    prop_size_adjust, \
    prop_slope, \
    prop_spatial_navigation_action, \
    prop_spatial_navigation_contain, \
    prop_spatial_navigation_function, \
    prop_speak, \
    prop_speak_as, \
    prop_speak_header, \
    prop_speak_numeral, \
    prop_speak_punctuation, \
    prop_speech_rate, \
    prop_src, \
    prop_stemh, \
    prop_stemv, \
    prop_stress, \
    prop_string_set, \
    prop_subscript_position_override, \
    prop_subscript_size_override, \
    prop_superscript_position_override, \
    prop_superscript_size_override, \
    prop_symbols, \
    prop_system, \
    prop_shape_padding, \
    prop_shape_rendering, \
    prop_shape_subtract, \
    prop_stop_colour, \
    prop_stop_opacity, \
    prop_stroke, \
    prop_stroke_align, \
    prop_stroke_alignment, \
    prop_stroke_break, \
    prop_stroke_colour, \
    prop_stroke_dash_corner, \
    prop_stroke_dash_justify, \
    prop_stroke_dashadjust, \
    prop_stroke_dasharray, \
    prop_stroke_dashcorner, \
    prop_stroke_dashoffset, \
    prop_stroke_image, \
    prop_stroke_linecap, \
    prop_stroke_linejoin, \
    prop_stroke_miterlimit, \
    prop_stroke_opacity, \
    prop_stroke_origin, \
    prop_stroke_position, \
    prop_stroke_repeat, \
    prop_stroke_size, \
    prop_stroke_width, \
    prop_suffix, \
    prop_tab_size, \
    prop_table_layout, \
    prop_text_align, \
    prop_text_align_all, \
    prop_text_align_last, \
    prop_text_anchor, \
    prop_text_autospace, \
    prop_text_combine_upright, \
    prop_text_decoration, \
    prop_text_decoration_colour, \
    prop_text_decoration_line, \
    prop_text_decoration_skip, \
    prop_text_decoration_skip_box, \
    prop_text_decoration_skip_ink, \
    prop_text_decoration_skip_inset, \
    prop_text_decoration_skip_self, \
    prop_text_decoration_skip_spaces, \
    prop_text_decoration_style, \
    prop_text_decoration_thickness, \
    prop_text_definition, \
    prop_text_edge, \
    prop_text_emphasis, \
    prop_text_emphasis_colour, \
    prop_text_emphasis_position, \
    prop_text_emphasis_skip, \
    prop_text_emphasis_style, \
    prop_text_group_align, \
    prop_text_indent, \
    prop_text_justify, \
    prop_text_orientation, \
    prop_text_overflow, \
    prop_text_rendering, \
    prop_text_resize, \
    prop_text_shadow, \
    prop_text_space_trim, \
    prop_text_spacing, \
    prop_text_spacing_trim, \
    prop_text_transform, \
    prop_text_underline_offset, \
    prop_text_underline_position, \
    prop_text_wrap, \
    prop_top, \
    prop_topline, \
    prop_transform, \
    prop_transform_box, \
    prop_transform_origin, \
    prop_transform_style, \
    prop_transition, \
    prop_transition_delay, \
    prop_transition_duration, \
    prop_transition_property, \
    prop_transition_timing_function, \
    prop_translate

#define LAST_CSS_2_PROP ec_translate

#define CSS_PROPERTIES_3 \
    prop_unicode_bidi, \
    prop_unicode_range, \
    prop_units_per_em, \
    prop_vector_effect, \
    prop_unknown, \
    prop_user_modify, \
    prop_user_select, \
    prop_vertical_align, \
    prop_view_timeline, \
    prop_view_timeline_axis, \
    prop_view_timeline_inset, \
    prop_view_timeline_name, \
    prop_view_transition_name, \
    prop_visibility, \
    prop_voice_balance, \
    prop_voice_duration, \
    prop_voice_family, \
    prop_voice_pitch, \
    prop_voice_range, \
    prop_voice_rate, \
    prop_voice_stress, \
    prop_voice_volume, \
    prop_volume, \
    prop_white_space, \
    prop_white_space_collapse, \
    prop_widows, \
    prop_width, \
    prop_widths, \
    prop_will_change, \
    prop_word_boundary_detection, \
    prop_word_boundary_expansion, \
    prop_word_break, \
    prop_word_spacing, \
    prop_word_wrap, \
    prop_wrap_after, \
    prop_wrap_before, \
    prop_wrap_flow, \
    prop_wrap_inside, \
    prop_wrap_through, \
    prop_writing_mode, \
    prop_x, \
    prop_x_height, \
    prop_y, \
    prop_z_index, \
    prop_zoom, \
    prop_moz_animation, \
    prop_moz_animation_delay, \
    prop_moz_animation_direction, \
    prop_moz_animation_duration, \
    prop_moz_animation_fill_mode, \
    prop_moz_animation_iteration_count, \
    prop_moz_animation_name, \
    prop_moz_animation_play_state, \
    prop_moz_animation_timing_function, \
    prop_moz_appearance, \
    prop_moz_backface_visibility, \
    prop_moz_background_clip, \
    prop_moz_background_inline_policy, \
    prop_moz_background_origin, \
    prop_moz_background_size, \
    prop_moz_binding, \
    prop_moz_border_bottom_colours, \
    prop_moz_border_end, \
    prop_moz_border_end_colour, \
    prop_moz_border_end_style, \
    prop_moz_border_end_width, \
    prop_moz_border_image, \
    prop_moz_border_left_colours, \
    prop_moz_border_right_colours, \
    prop_moz_border_start, \
    prop_moz_border_start_colour, \
    prop_moz_border_start_style, \
    prop_moz_border_start_width, \
    prop_moz_border_top_colours, \
    prop_moz_box_align, \
    prop_moz_box_direction, \
    prop_moz_box_flex, \
    prop_moz_box_ordinal_group, \
    prop_moz_box_orient, \
    prop_moz_box_pack, \
    prop_moz_box_sizing, \
    prop_moz_column_count, \
    prop_moz_column_fill, \
    prop_moz_column_gap, \
    prop_moz_column_rule, \
    prop_moz_column_rule_colour, \
    prop_moz_column_rule_style, \
    prop_moz_column_rule_width, \
    prop_moz_column_width, \
    prop_moz_context_properties, \
    prop_moz_float_edge, \
    prop_moz_font_feature_settings, \
    prop_moz_font_language_override, \
    prop_moz_force_broken_image_icon, \
    prop_moz_hyphens, \
    prop_moz_image_region, \
    prop_moz_margin_end, \
    prop_moz_margin_start, \
    prop_moz_opacity, \
    prop_moz_orient, \
    prop_moz_osx_font_smoothing, \
    prop_moz_outline, \
    prop_moz_outline_colour, \
    prop_moz_outline_offset, \
    prop_moz_outline_radius, \
    prop_moz_outline_radius_bottomleft, \
    prop_moz_outline_radius_bottomright, \
    prop_moz_outline_radius_topleft, \
    prop_moz_outline_radius_topright, \
    prop_moz_outline_style, \
    prop_moz_outline_width, \
    prop_moz_padding_end, \
    prop_moz_padding_start, \
    prop_moz_perspective, \
    prop_moz_perspective_origin, \
    prop_moz_stack_sizing, \
    prop_moz_tab_size, \
    prop_moz_text_align_last, \
    prop_moz_text_decoration_colour, \
    prop_moz_text_decoration_line, \
    prop_moz_text_decoration_style, \
    prop_moz_text_size_adjust, \
    prop_moz_transform, \
    prop_moz_transform_origin, \
    prop_moz_transform_style, \
    prop_moz_transition, \
    prop_moz_transition_delay, \
    prop_moz_transition_duration, \
    prop_moz_transition_property, \
    prop_moz_transition_timing_function, \
    prop_moz_user_focus, \
    prop_moz_user_input, \
    prop_moz_user_modify, \
    prop_moz_user_select, \
    prop_moz_window_dragging, \
    prop_moz_window_shadow, \
    prop_webkit_align_content, \
    prop_webkit_align_items, \
    prop_webkit_align_self, \
    prop_webkit_alt, \
    prop_webkit_animation, \
    prop_webkit_animation_delay, \
    prop_webkit_animation_direction, \
    prop_webkit_animation_duration, \
    prop_webkit_animation_fill_mode, \
    prop_webkit_animation_iteration_count, \
    prop_webkit_animation_name, \
    prop_webkit_animation_play_state, \
    prop_webkit_animation_timing_function, \
    prop_webkit_animation_trigger, \
    prop_webkit_app_region, \
    prop_webkit_appearance, \
    prop_webkit_aspect_ratio, \
    prop_webkit_backdrop_filter, \
    prop_webkit_backface_visibility, \
    prop_webkit_background_clip, \
    prop_webkit_background_composite, \
    prop_webkit_background_origin, \
    prop_webkit_background_size, \
    prop_webkit_border_after, \
    prop_webkit_border_after_colour, \
    prop_webkit_border_after_style, \
    prop_webkit_border_after_width, \
    prop_webkit_border_before, \
    prop_webkit_border_before_colour, \
    prop_webkit_border_before_style, \
    prop_webkit_border_before_width, \
    prop_webkit_border_bottom_left_radius, \
    prop_webkit_border_bottom_right_radius, \
    prop_webkit_border_end, \
    prop_webkit_border_end_colour, \
    prop_webkit_border_end_style, \
    prop_webkit_border_end_width, \
    prop_webkit_border_fit, \
    prop_webkit_border_horizontal_spacing, \
    prop_webkit_border_image, \
    prop_webkit_border_radius, \
    prop_webkit_border_start, \
    prop_webkit_border_start_colour, \
    prop_webkit_border_start_style, \
    prop_webkit_border_start_width, \
    prop_webkit_border_top_left_radius, \
    prop_webkit_border_top_right_radius, \
    prop_webkit_border_vertical_spacing, \
    prop_webkit_box_align, \
    prop_webkit_box_decoration_break, \
    prop_webkit_box_direction, \
    prop_webkit_box_flex, \
    prop_webkit_box_flex_group, \
    prop_webkit_box_lines, \
    prop_webkit_box_ordinal_group, \
    prop_webkit_box_orient, \
    prop_webkit_box_pack, \
    prop_webkit_box_reflect, \
    prop_webkit_box_shadow, \
    prop_webkit_box_sizing, \
    prop_webkit_clip_path, \
    prop_webkit_colour_correction, \
    prop_webkit_column_axis, \
    prop_webkit_column_break_after, \
    prop_webkit_column_break_before, \
    prop_webkit_column_break_inside, \
    prop_webkit_column_count, \
    prop_webkit_column_fill, \
    prop_webkit_column_gap, \
    prop_webkit_column_progression, \
    prop_webkit_column_rule, \
    prop_webkit_column_rule_colour, \
    prop_webkit_column_rule_style, \
    prop_webkit_column_rule_width, \
    prop_webkit_column_span, \
    prop_webkit_column_width, \
    prop_webkit_columns, \
    prop_webkit_cursor_visibility, \
    prop_webkit_dashboard_region, \
    prop_webkit_device_pixel_ratio, \
    prop_webkit_filter, \
    prop_webkit_flex, \
    prop_webkit_flex_basis, \
    prop_webkit_flex_direction, \
    prop_webkit_flex_flow, \
    prop_webkit_flex_grow, \
    prop_webkit_flex_shrink, \
    prop_webkit_flex_wrap, \
    prop_webkit_flow_from, \
    prop_webkit_flow_into, \
    prop_webkit_font_feature_settings, \
    prop_webkit_font_kerning, \
    prop_webkit_font_size_delta, \
    prop_webkit_font_smoothing, \
    prop_webkit_font_variant_ligatures, \
    prop_webkit_grid, \
    prop_webkit_grid_area, \
    prop_webkit_grid_auto_columns, \
    prop_webkit_grid_auto_flow, \
    prop_webkit_grid_auto_rows, \
    prop_webkit_grid_column, \
    prop_webkit_grid_column_end, \
    prop_webkit_grid_column_gap, \
    prop_webkit_grid_column_start, \
    prop_webkit_grid_columns, \
    prop_webkit_grid_gap, \
    prop_webkit_grid_row, \
    prop_webkit_grid_row_end, \
    prop_webkit_grid_row_gap, \
    prop_webkit_grid_row_start, \
    prop_webkit_grid_rows, \
    prop_webkit_grid_template, \
    prop_webkit_grid_template_areas, \
    prop_webkit_grid_template_columns, \
    prop_webkit_grid_template_rows, \
    prop_webkit_highlight, \
    prop_webkit_hyphenate_character, \
    prop_webkit_hyphenate_charset, \
    prop_webkit_hyphenate_limit_after, \
    prop_webkit_hyphenate_limit_before, \
    prop_webkit_hyphenate_limit_lines, \
    prop_webkit_hyphens, \
    prop_webkit_image_set, \
    prop_webkit_initial_letter, \
    prop_webkit_justify_content, \
    prop_webkit_justify_items, \
    prop_webkit_justify_self, \
    prop_webkit_line_align, \
    prop_webkit_line_box_contain, \
    prop_webkit_line_break, \
    prop_webkit_line_clamp, \
    prop_webkit_line_grid, \
    prop_webkit_line_snap, \
    prop_webkit_locale, \
    prop_webkit_logical_height, \
    prop_webkit_logical_width, \
    prop_webkit_margin_after, \
    prop_webkit_margin_after_collapse, \
    prop_webkit_margin_before, \
    prop_webkit_margin_before_collapse, \
    prop_webkit_margin_bottom_collapse, \
    prop_webkit_margin_collapse, \
    prop_webkit_margin_end, \
    prop_webkit_margin_start, \
    prop_webkit_margin_top_collapse, \
    prop_webkit_marquee, \
    prop_webkit_marquee_direction, \
    prop_webkit_marquee_increment, \
    prop_webkit_marquee_repetition, \
    prop_webkit_marquee_speed, \
    prop_webkit_marquee_style, \
    prop_webkit_mask, \
    prop_webkit_mask_attachment, \
    prop_webkit_mask_box_image, \
    prop_webkit_mask_box_image_outset, \
    prop_webkit_mask_box_image_repeat, \
    prop_webkit_mask_box_image_slice, \
    prop_webkit_mask_box_image_source, \
    prop_webkit_mask_box_image_width, \
    prop_webkit_mask_clip, \
    prop_webkit_mask_composite, \
    prop_webkit_mask_image, \
    prop_webkit_mask_origin, \
    prop_webkit_mask_position, \
    prop_webkit_mask_position_x, \
    prop_webkit_mask_position_y, \
    prop_webkit_mask_repeat, \
    prop_webkit_mask_repeat_x, \
    prop_webkit_mask_repeat_y, \
    prop_webkit_mask_size, \
    prop_webkit_mask_source_type, \
    prop_webkit_match_nearest_mail_blockquote_colour, \
    prop_webkit_max_logical_height, \
    prop_webkit_max_logical_width, \
    prop_webkit_media_text_track_container, \
    prop_webkit_min_logical_height, \
    prop_webkit_min_logical_width

#define LAST_CSS_3_PROP ec_webkit_min_logical_width

#define CSS_PROPERTIES_4 \
    prop_webkit_nbsp_mode, \
    prop_webkit_opacity, \
    prop_webkit_order, \
    prop_webkit_overflow_scrolling, \
    prop_webkit_padding_after, \
    prop_webkit_padding_before, \
    prop_webkit_padding_end, \
    prop_webkit_padding_start, \
    prop_webkit_perspective, \
    prop_webkit_perspective_origin, \
    prop_webkit_perspective_origin_x, \
    prop_webkit_perspective_origin_y, \
    prop_webkit_print_colour_adjust, \
    prop_webkit_region_break_after, \
    prop_webkit_region_break_before, \
    prop_webkit_region_break_inside, \
    prop_webkit_region_fragment, \
    prop_webkit_rtl_ordering, \
    prop_webkit_ruby_position, \
    prop_webkit_scroll_snap_type, \
    prop_webkit_shape_image_threshold, \
    prop_webkit_shape_inside, \
    prop_webkit_shape_margin, \
    prop_webkit_shape_outside, \
    prop_webkit_svg_shadow, \
    prop_webkit_tap_highlight_colour, \
    prop_webkit_text_colour_decoration, \
    prop_webkit_text_combine, \
    prop_webkit_text_decoration_line, \
    prop_webkit_text_decoration_skip, \
    prop_webkit_text_decoration_style, \
    prop_webkit_text_decorations_in_effect, \
    prop_webkit_text_emphasis, \
    prop_webkit_text_emphasis_colour, \
    prop_webkit_text_emphasis_position, \
    prop_webkit_text_emphasis_style, \
    prop_webkit_text_fill_colour, \
    prop_webkit_text_justify, \
    prop_webkit_text_orientation, \
    prop_webkit_text_security, \
    prop_webkit_text_size_adjust, \
    prop_webkit_text_stroke, \
    prop_webkit_text_stroke_colour, \
    prop_webkit_text_stroke_width, \
    prop_webkit_text_underline_position, \
    prop_webkit_text_zoom, \
    prop_webkit_touch_callout, \
    prop_webkit_transform, \
    prop_webkit_transform_2d, \
    prop_webkit_transform_3d, \
    prop_webkit_transform_origin, \
    prop_webkit_transform_origin_x, \
    prop_webkit_transform_origin_y, \
    prop_webkit_transform_origin_z, \
    prop_webkit_transform_style, \
    prop_webkit_transition, \
    prop_webkit_transition_delay, \
    prop_webkit_transition_duration, \
    prop_webkit_transition_property, \
    prop_webkit_transition_timing_function, \
    prop_webkit_user_drag, \
    prop_webkit_user_modify, \
    prop_webkit_user_select, \
    prop_background_origin_x, \
    prop_background_origin_y, \
    prop_filter, \
    prop_overflow_clip_box, \
    prop_overflow_clip_box_block, \
    prop_overflow_clip_box_inline, \
    prop_mso_ansi_font_size, \
    prop_mso_ansi_font_style, \
    prop_mso_ansi_font_weight, \
    prop_mso_ansi_language, \
    prop_mso_arabic_font_family, \
    prop_mso_armenian_font_family, \
    prop_mso_ascii_font_family, \
    prop_mso_ascii_theme_font, \
    prop_mso_background_source, \
    prop_mso_bengali_font_family, \
    prop_mso_bidi_font_family, \
    prop_mso_bidi_font_size, \
    prop_mso_bidi_font_style, \
    prop_mso_bidi_font_weight, \
    prop_mso_bidi_language, \
    prop_mso_bidi_theme_font, \
    prop_mso_bookmark, \
    prop_mso_bopomofo_font_family, \
    prop_mso_border_alt, \
    prop_mso_border_bottom_alt, \
    prop_mso_border_colour_alt, \
    prop_mso_border_insideh, \
    prop_mso_border_insidev, \
    prop_mso_border_left_alt, \
    prop_mso_border_right_alt, \
    prop_mso_border_shadow, \
    prop_mso_border_style_alt, \
    prop_mso_border_top_alt, \
    prop_mso_border_width_alt, \
    prop_mso_break_type, \
    prop_mso_cell_special, \
    prop_mso_cellspacing, \
    prop_mso_char_indent_count, \
    prop_mso_char_indent_size, \
    prop_mso_char_tracking, \
    prop_mso_char_type, \
    prop_mso_char_wrap, \
    prop_mso_colour_alt, \
    prop_mso_colour_index, \
    prop_mso_column_margin, \
    prop_mso_currency_font_family, \
    prop_mso_cyrillic_font_family, \
    prop_mso_data_placement, \
    prop_mso_default_font_family, \
    prop_mso_default_props, \
    prop_mso_devanagari_font_family, \
    prop_mso_displayed_decimal_separator, \
    prop_mso_displayed_thousand_separator, \
    prop_mso_element, \
    prop_mso_element_anchor_horizontal, \
    prop_mso_element_anchor_vertical, \
    prop_mso_element_frame_height, \
    prop_mso_element_frame_hspace, \
    prop_mso_element_frame_width, \
    prop_mso_element_left, \
    prop_mso_element_top, \
    prop_mso_element_wrap, \
    prop_mso_endnote_continuation_separator, \
    prop_mso_endnote_numbering_style, \
    prop_mso_endnote_separator, \
    prop_mso_eudc_font_family, \
    prop_mso_even_footer, \
    prop_mso_fareast_font_family, \
    prop_mso_fareast_language, \
    prop_mso_fareast_theme_font, \
    prop_mso_field_code, \
    prop_mso_font_alt, \
    prop_mso_font_charset, \
    prop_mso_font_format, \
    prop_mso_font_kerning, \
    prop_mso_font_pitch, \
    prop_mso_font_signature, \
    prop_mso_font_width, \
    prop_mso_footer, \
    prop_mso_footer_margin, \
    prop_mso_footnote_continuation_separator, \
    prop_mso_footnote_id, \
    prop_mso_footnote_separator, \
    prop_mso_generic_font_family, \
    prop_mso_georgian_font_family, \
    prop_mso_gram_e, \
    prop_mso_greek_font_family, \
    prop_mso_gurmukhi_font_family, \
    prop_mso_halfwidthkana_font_family, \
    prop_mso_han_font_family, \
    prop_mso_hangul_font_family, \
    prop_mso_hansi_font_family, \
    prop_mso_hansi_theme_font, \
    prop_mso_header, \
    prop_mso_header_margin, \
    prop_mso_hebrew_font_family, \
    prop_mso_height_rule, \
    prop_mso_height_source, \
    prop_mso_hide, \
    prop_mso_highlight, \
    prop_mso_hyphenate, \
    prop_mso_ignore, \
    prop_mso_kana_font_family, \
    prop_mso_kannada_font_family, \
    prop_mso_kinsoku_overflow, \
    prop_mso_lao_font_family, \
    prop_mso_latin_font_family, \
    prop_mso_latinext_font_family, \
    prop_mso_layout_grid_align, \
    prop_mso_level_font_family, \
    prop_mso_level_indent, \
    prop_mso_level_legacy, \
    prop_mso_level_legacy_indent, \
    prop_mso_level_legacy_space, \
    prop_mso_level_number_format, \
    prop_mso_level_number_position, \
    prop_mso_level_size, \
    prop_mso_level_start_at, \
    prop_mso_level_style_link, \
    prop_mso_level_tab_stop, \
    prop_mso_level_text, \
    prop_mso_line_height_alt, \
    prop_mso_line_height_rule, \
    prop_mso_line_spacing, \
    prop_mso_linked_frame, \
    prop_mso_list, \
    prop_mso_list_id, \
    prop_mso_list_template_ids, \
    prop_mso_list_type, \
    prop_mso_malayalam_font_family, \
    prop_mso_margin_bottom_alt, \
    prop_mso_margin_left_alt, \
    prop_mso_margin_top_alt, \
    prop_mso_no_proof, \
    prop_mso_number_format, \
    prop_mso_oriya_font_family, \
    prop_mso_outline_level, \
    prop_mso_padding_alt, \
    prop_mso_page_border_surround_footer, \
    prop_mso_page_border_surround_header, \
    prop_mso_page_orientation, \
    prop_mso_pagination, \
    prop_mso_paper_source, \
    prop_mso_para_margin, \
    prop_mso_para_margin_bottom, \
    prop_mso_para_margin_left, \
    prop_mso_para_margin_right, \
    prop_mso_para_margin_top, \
    prop_mso_pattern, \
    prop_mso_position_horizontal, \
    prop_mso_position_horizontal_relative, \
    prop_mso_position_vertical, \
    prop_mso_position_vertical_relative, \
    prop_mso_protection, \
    prop_mso_rotate, \
    prop_mso_row_margin_left, \
    prop_mso_row_margin_right, \
    prop_mso_shading, \
    prop_mso_spacerun, \
    prop_mso_special_character, \
    prop_mso_special_format, \
    prop_mso_spl_e, \
    prop_mso_style_id, \
    prop_mso_style_link, \
    prop_mso_style_locked, \
    prop_mso_style_name, \
    prop_mso_style_next, \
    prop_mso_style_noshow, \
    prop_mso_style_parent, \
    prop_mso_style_priority, \
    prop_mso_style_qformat, \
    prop_mso_style_type, \
    prop_mso_style_unhide, \
    prop_mso_style_update, \
    prop_mso_symbol_font_family, \
    prop_mso_syriac_font_family, \
    prop_mso_tab_count, \
    prop_mso_table_anchor_horizontal, \
    prop_mso_table_anchor_vertical, \
    prop_mso_table_layout_alt, \
    prop_mso_table_left, \
    prop_mso_table_lspace, \
    prop_mso_table_overlap, \
    prop_mso_table_rspace, \
    prop_mso_table_top, \
    prop_mso_tamil_font_family, \
    prop_mso_telugu_font_family, \
    prop_mso_text_animation, \
    prop_mso_text_raise, \
    prop_mso_thaana_font_family, \
    prop_mso_thai_font_family, \
    prop_mso_themecolour, \
    prop_mso_themeshade, \
    prop_mso_title_page, \
    prop_mso_tstyle_colband_size, \
    prop_mso_tstyle_rowband_size, \
    prop_mso_width_alt, \
    prop_mso_width_source, \
    prop_mso_wrap_distance_bottom, \
    prop_mso_wrap_distance_left, \
    prop_mso_wrap_distance_right, \
    prop_mso_wrap_distance_top, \
    prop_mso_wrap_edited, \
    prop_mso_yfti_firstrow, \
    prop_mso_yfti_irow, \
    prop_mso_yfti_lastrow, \
    prop_mso_yfti_tbllook, \
    prop_o_table_baseline, \
    prop_o_text_overflow

#define LAST_CSS_4_PROP ec_o_text_overflow

#define CSS_PROPERTIES_5 \
    prop_o_transform, \
    prop_o_transform_origin, \
    prop_o_transition, \
    prop_o_transition_delay, \
    prop_o_transition_duration, \
    prop_o_transition_property, \
    prop_o_transition_timing_function, \
    prop_o_tab_size, \
    prop_apple_dashboard_region, \
    prop_epub_caption_side, \
    prop_epub_hyphens, \
    prop_epub_text_combine, \
    prop_epub_text_orientation, \
    prop_epub_text_transform, \
    prop_ms_animation, \
    prop_ms_animation_delay, \
    prop_ms_animation_direction, \
    prop_ms_animation_duration, \
    prop_ms_animation_fill_mode, \
    prop_ms_animation_iteration_count, \
    prop_ms_animation_name, \
    prop_ms_animation_play_state, \
    prop_ms_animation_timing_function, \
    prop_ms_block_progression, \
    prop_ms_content_zoom_chaining, \
    prop_ms_content_zoom_limit, \
    prop_ms_content_zoom_limit_max, \
    prop_ms_content_zoom_limit_min, \
    prop_ms_content_zoom_snap, \
    prop_ms_content_zoom_snap_points, \
    prop_ms_content_zoom_snap_type, \
    prop_ms_content_zooming, \
    prop_ms_flex_align, \
    prop_ms_flex_item_align, \
    prop_ms_flex_line_pack, \
    prop_ms_flex_negative, \
    prop_ms_flex_order, \
    prop_ms_flex_pack, \
    prop_ms_flex_positive, \
    prop_ms_flex_preferred_size, \
    prop_ms_font_feature_settings, \
    prop_ms_grid_columns, \
    prop_ms_grid_rows, \
    prop_ms_high_contrast_adjust, \
    prop_ms_hyphenate_limit_chars, \
    prop_ms_hyphenate_limit_lines, \
    prop_ms_hyphenate_limit_zone, \
    prop_ms_ime_align, \
    prop_ms_interpolation_mode, \
    prop_ms_scroll_chaining, \
    prop_ms_scroll_limit, \
    prop_ms_scroll_limit_x_max, \
    prop_ms_scroll_limit_x_min, \
    prop_ms_scroll_limit_y_max, \
    prop_ms_scroll_limit_y_min, \
    prop_ms_scroll_rails, \
    prop_ms_scroll_snap_points_x, \
    prop_ms_scroll_snap_points_y, \
    prop_ms_scroll_snap_type, \
    prop_ms_scroll_snap_x, \
    prop_ms_scroll_snap_y, \
    prop_ms_scroll_translation, \
    prop_ms_text_combine_horizontal, \
    prop_ms_touch_action, \
    prop_ms_touch_select, \
    prop_ms_transition, \
    prop_ms_transition_delay, \
    prop_ms_transition_duration, \
    prop_ms_transition_property, \
    prop_ms_transition_timing_function, \
    prop_ms_wrap_margin, \
    prop_o_border_image, \
    prop_o_device_pixel_ratio, \
    prop_o_focus_opacity, \
    prop_o_link, \
    prop_o_link_source, \
    prop_o_mini_fold, \
    prop_o_object_fit, \
    prop_o_object_position, \
    prop_o_tab_size, \
    prop_o_table_baseline, \
    prop_o_transform, \
    prop_o_transform_origin, \
    prop_o_transition, \
    prop_o_transition_delay, \
    prop_o_transition_duration, \
    prop_o_transition_property, \
    prop_o_transition_timing_function, \
    prop_wap_accesskey, \
    prop_wap_input_format, \
    prop_wap_input_required, \
    prop_wap_marquee_dir, \
    prop_wap_marquee_loop, \
    prop_wap_marquee_speed, \
    prop_wap_marquee_style, \
    prop_xv_interpret_as, \
    prop_xv_phonemes, \
    prop_xv_voice_balance, \
    prop_xv_voice_duration, \
    prop_xv_voice_pitch, \
    prop_xv_voice_pitch_range, \
    prop_xv_voice_rate, \
    prop_xv_voice_stress, \
    prop_xv_voice_volume
