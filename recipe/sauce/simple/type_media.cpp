/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "type/type.h"
#include "element/element.h"
#include "webpage/page.h"
#include "css/group.h"

struct symbol_entry < html_version, e_media > media_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "(", md_brac },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, ":", md_colon },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "=", md_eq },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, ">", md_gt },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, ">=", md_gteq },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, ")", md_ket },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "<", md_lt },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "<=", md_lteq },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "/", md_slash },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 }, { HTML_UNDEF }, " ", md_space },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 }, { HTML_UNDEF }, ",", md_comma },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "@custom-media", md_custom_media },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "active", md_active, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "additive", md_additive, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "all", md_all, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "and", md_and, ns_default, CF_MEDIA_LOGIC },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "any-hover", md_any_hover, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "any-pointer", md_any_pointer, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "aspect-ratio", md_aspect_ratio, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_2_0 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "aural", md_aural, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "back", md_back, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "braille", md_braille, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "browser", md_browser, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "cm", md_cm, ns_default, CF_MEDIA_UNIT },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "coarse", md_coarse, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "color", md_colour, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "color-gamut", md_colour_gamut, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "color-index", md_colour_index, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "custom", md_custom, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "dark", md_dark, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-aspect-ratio", md_device_aspect_ratio, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-height", md_device_height, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-width", md_device_width, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "display-mode", md_display_mode, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "dpcm", md_dpcm, ns_default, CF_MEDIA_UNIT },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "dpi", md_dpi, ns_default, CF_MEDIA_UNIT },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "dynamic-range", md_dynamic_range, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "em", md_em, ns_default, CF_MEDIA_UNIT },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "embossed", md_embossed, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "enabled", md_enabled, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "environment-blending", md_environment_blending, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "fast", md_fast, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "fine", md_fine, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "forced-colors", md_forced_colours, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "fullscreen", md_fullscreen, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "grid", md_grid, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "height", md_height, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "handheld", md_handheld, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "high", md_high, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "horizontal-viewport-segments", md_horizontal_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "hover", md_hover, ns_default, CF_MEDIA_PROPERTY | CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "infinite", md_infinite, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "initial-only", md_initial_only, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "interlace", md_interlace, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "inverted", md_inverted, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "inverted-colors", md_inverted_colours, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "landscape", md_landscape, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "less", md_less, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "light", md_light, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-aspect-ratio", md_max_aspect_ratio, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-color", md_max_colour, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-aspect-ratio", md_max_device_aspect_ratio, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-height", md_max_device_height, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-width", md_max_device_width, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-color-index", md_max_colour_index, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-height", md_max_height, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "max-horizontal-viewport-segments", md_max_horizontal_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-monochrome", md_max_monochrome, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-resolution", md_max_resolution, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "max-vertical-viewport-segments", md_max_vertical_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "max-width", md_max_width, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_COND_RULE_5 }, { HTML_UNDEF }, "media", md_media, ns_default, CF_MEDIA_DEVICE | CF_FUNCTION },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-aspect-ratio", md_min_aspect_ratio, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-color", md_min_colour, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-aspect-ratio", md_min_device_aspect_ratio, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-height", md_min_device_height, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-width", md_min_device_width, ns_default, CF_MEDIA_PROPERTY | CF_DEPRECATED_45 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-color-index", md_min_colour_index, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-height", md_min_height, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "min-horizontal-viewport-segments", md_min_horizontal_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-monochrome", md_min_monochrome, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-resolution", md_min_resolution, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "min-vertical-viewport-segments", md_min_vertical_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "min-width", md_min_width, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "minimal-ui", md_minimal_ui, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "monochrome", md_monochrome, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "more", md_more, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "nav-controls", md_nav_controls, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "no-preference", md_no_preference, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "(-ve number)", md_negative },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "none", md_none, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "not", md_not, ns_default, CF_MEDIA_FIRST },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "only", md_only, ns_default, CF_MEDIA_FIRST },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "opaque", md_opaque, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "or", md_or, ns_default, CF_MEDIA_LOGIC },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "orientation", md_orientation, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "overflow-block", md_overflow_block, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "overflow-inline", md_overflow_inline, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "paged", md_paged, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "pointer", md_pointer, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "portrait", md_portrait, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "(+ve number)", md_positive },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-color-scheme", md_prefers_colour_scheme, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-contrast", md_prefers_contrast, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-data", md_prefers_reduced_data, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-motion", md_prefers_reduced_motion, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-transparency", md_prefers_reduced_transparency, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "print", md_print, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "progressive", md_progressive, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "projection", md_projection, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "p3", md_p3, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "px", md_px, ns_default, CF_MEDIA_UNIT },
    { { HTML_4_0, HV_ABANDONED }, { HTML_UNDEF }, "reader", md_reader, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "rec2020", md_rec2020, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45, H3_CSS_ROUND }, { HTML_UNDEF }, "rect", md_rect, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "reduce", md_reduce, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "resolution", md_resolution, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45, H3_CSS_ROUND }, { HTML_UNDEF }, "round", md_round, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "scan", md_scan, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "screen", md_screen, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "scripting", md_scripting, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "scroll", md_scroll, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_COND_RULE_45 }, { HTML_UNDEF }, "selector", md_selector, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45, H3_CSS_ROUND }, { HTML_UNDEF }, "shape", md_shape, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "slow", md_slow, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_21_22 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "speech", md_speech, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "srgb", md_srgb, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "standalone", md_standalone, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "standard", md_standard, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "subtractive", md_subtractive, ns_default, CF_MEDIA_VALUE },
    { { HTML_4_0, 0, 0, H2_CSS_COND_RULE_5 }, { HTML_UNDEF }, "supports", md_supports, ns_default, CF_MEDIA_DEVICE | CF_FUNCTION },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "tty", md_tty, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "tv", md_tv, ns_default, CF_MEDIA_DEVICE },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 | H2_CSS_COND_RULE }, { HTML_UNDEF }, "update", md_update, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "vertical-viewport-segments", md_vertical_viewport_segments, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "video-color-gamut", md_video_colour_gamut, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "video-dynamic-range", md_video_dynamic_range, ns_default, CF_MEDIA_PROPERTY },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_COND_RULE }, { HTML_UNDEF }, "width", md_width, ns_default, CF_MEDIA_PROPERTY } };

void media_init (nitpick& nits)
{   type_master < t_media > :: init (nits, media_symbol_table, sizeof (media_symbol_table) / sizeof (symbol_entry < html_version, e_media >)); }

bool parse_media_query (nitpick& nits, const html_version& v, const ::std::string& sss, element* e)
{   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    page& p = e -> get_page ();
    css_group& cg (p.css ());
    css_ptr cp = cg.parse_media_queries (sss, v, e -> get_page (), e -> namespaces (), e -> ancestral_elements (), true, e -> line (), e -> tag ());
    if (cp.get () == nullptr) return false;
    cp -> nick_nits (nits);
    return true; }
