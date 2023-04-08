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
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "active", md_active },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "additive", md_additive },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 }, { HTML_UNDEF }, "all", md_all },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "and", md_and },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "any-hover", md_any_hover },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "any-pointer", md_any_pointer },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "aspect-ratio", md_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_2_0 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "aural", md_aural },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "back", md_back },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "braille", md_braille },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "browser", md_browser },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "cm", md_cm },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "coarse", md_coarse },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "color", md_colour },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "color-gamut", md_colour_gamut },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "color-index", md_colour_index },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "custom", md_custom },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "dark", md_dark },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-aspect-ratio", md_device_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-height", md_device_height },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "device-width", md_device_width },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "display-mode", md_display_mode },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "dpcm", md_dpcm },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "dpi", md_dpi },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "dynamic-range", md_dynamic_range },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "em", md_em },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "embossed", md_embossed },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "enabled", md_enabled },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "environment-blending", md_environment_blending },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "fast", md_fast },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "fine", md_fine },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "forced-colors", md_forced_colours },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "fullscreen", md_fullscreen },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "grid", md_grid },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "height", md_height },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "handheld", md_handheld },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "high", md_high },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "horizontal-viewport-segments", md_horizontal_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "hover", md_hover },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "infinite", md_infinite },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "initial-only", md_initial_only },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "interlace", md_interlace },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "inverted", md_inverted },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "inverted-colors", md_inverted_colours },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "landscape", md_landscape },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "less", md_less },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "light", md_light },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-aspect-ratio", md_max_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-color", md_max_colour },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-aspect-ratio", md_max_device_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-height", md_max_device_height },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "max-device-width", md_max_device_width },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-color-index", md_max_colour_index },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-height", md_max_height },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "max-horizontal-viewport-segments", md_max_horizontal_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-monochrome", md_max_monochrome },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-resolution", md_max_resolution },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "max-vertical-viewport-segments", md_max_vertical_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "max-width", md_max_width },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-aspect-ratio", md_min_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-color", md_min_colour },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-aspect-ratio", md_min_device_aspect_ratio },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-height", md_min_device_height },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "min-device-width", md_min_device_width },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-color-index", md_min_colour_index },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-height", md_min_height },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "min-horizontal-viewport-segments", md_min_horizontal_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-monochrome", md_min_monochrome },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-resolution", md_min_resolution },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "min-vertical-viewport-segments", md_min_vertical_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "min-width", md_min_width },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "minimal-ui", md_minimal_ui },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "monochrome", md_monochrome },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "more", md_more },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "nav-controls", md_nav_controls },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "no-preference", md_no_preference },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "(-ve number)", md_negative },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "none", md_none },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "not", md_not },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "only", md_only },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "opaque", md_opaque },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "or", md_or },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "orientation", md_orientation },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "overflow-block", md_overflow_block },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "overflow-inline", md_overflow_inline },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "paged", md_paged },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "pointer", md_pointer },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "portrait", md_portrait },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "(+ve number)", md_positive },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-color-scheme", md_prefers_colour_scheme },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-contrast", md_prefers_contrast },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-data", md_prefers_reduced_data },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-motion", md_prefers_reduced_motion },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "prefers-reduced-transparency", md_prefers_reduced_transparency },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 }, { HTML_UNDEF }, "print", md_print },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "progressive", md_progressive },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "projection", md_projection },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "p3", md_p3 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "px", md_px },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "rec2020", md_rec2020 },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "reduce", md_reduce },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "resolution", md_resolution },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "scan", md_scan },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA | H2_CSS_2 }, { HTML_UNDEF }, "screen", md_screen },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "scripting", md_scripting },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "scroll", md_scroll },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "slow", md_slow },
    { { HTML_4_0, 0, 0, H2_CSS_21_22 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "speech", md_speech },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "srgb", md_srgb },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "standalone", md_standalone },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "standard", md_standard },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "subtractive", md_subtractive },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "tty", md_tty },
    { { HTML_4_0, 0, 0, H2_CSS_2 | H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "tv", md_tv },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_45 }, { HTML_UNDEF }, "update", md_update },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "vertical-viewport-segments", md_vertical_viewport_segments },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "video-color-gamut", md_video_colour_gamut },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "video-dynamic-range", md_video_dynamic_range },
    { { HTML_4_0, 0, 0, H2_CSS_MEDIA }, { HTML_UNDEF }, "width", md_width } };

void media_init (nitpick& nits)
{   type_master < t_media > :: init (nits, media_symbol_table, sizeof (media_symbol_table) / sizeof (symbol_entry < html_version, e_media >)); }

typedef enum { had_nowt, had_space, had_gt, had_lt, had_error } e_had;

const char* had_table [] =
{   "", " ", "<", ">", "?" };

struct media_token
{   e_media m_;
    ::std::string s_;
    media_token (const e_media m, const ::std::string& s = ::std::string ()) : m_ (m), s_ (s) { } };

typedef ::std::vector < media_token > vm_t;

::std::string mtkn_report (const vm_t& v)
{   ::std::string res, line, item;
    if (context.tell (es_detail))
    {   res += "\nMedia:\n";
        for (auto m : v)
        {   ::std::string s (enum_n < t_media, e_media > :: name (m.m_));
            if (s.length () > 1) item = s;
            else item = quote (s);
            if (! m.s_.empty ())
            {   item += "="; item += m.s_; }
            if (line.size () + item.size () > DEFAULT_LINE_LENGTH)
            {   res += line + "\n"; line.clear (); }
            else if (! line.empty ()) line += " | ";
            line += item; }
        if (! line.empty ()) res += line + "\n";
        outstr.out (res); }
    return res; }
   
e_had had_had (nitpick& nits, const html_version& , const e_had old, const e_had had)
{   PRESUME (old < had_error, __FILE__, __LINE__);
    PRESUME (had < had_error, __FILE__, __LINE__);
    switch (old)
    {   case had_nowt :
        case had_space :
            return had;
        case had_gt :
        case had_lt :
            nits.pick (nit_bad_media, es_error, ec_mql, "media syntax error: ", ::gsl::at (had_table, old), ::gsl::at (had_table, had));
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__); }
    return had_nowt; }

e_had note_value (nitpick& nits, const html_version& v, vm_t& vm, const e_had had, const ::std::string& s, const ustr_t& custom_media)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    had_had (nits, v, had, had_nowt);
    if (custom_media.find (s) != custom_media.cend ())
        vm.emplace_back (md_custom_media, s);
    else if (s.at (0) == '@')
        nits.pick (nit_bad_media, es_error, ec_mql, quote (s), ": unexpected (12)");
    else
    {   const ::std::string starters (DENARY "-");
        const ::std::string denary (DENARY);
        ::std::string n;
        if (starters.find (s.at (0)) == ::std::string::npos) n = s;
        else
        {   const ::std::string::size_type pos = s.substr (1).find_first_not_of (DENARY);
            if (pos == ::std::string::npos) n = s;
            else n = s.substr (0, pos+1);
            if (n.at (0) == '-') vm.emplace_back (md_negative, n);   
            else vm.emplace_back (md_positive, n);
            if (pos == ::std::string::npos) return had_nowt;
            n = s.substr (pos+1); }
        enum_n < t_media, e_media > md;
        md.set_value (nits, v, n);
        if (md.good ())
        {   e_media m = md.get ();
            vm.emplace_back (m); } }
    return had_nowt; }

e_had note_token (nitpick& nits, const html_version& v, vm_t& vm, const e_had had, const e_media m, ::std::string& s, const ustr_t& custom_media)
{   if (! s.empty ())
    {   note_value (nits, v, vm, had, s, custom_media);
        s.clear (); }
    vm.emplace_back (m);
    if (m == md_space) return had_space;
    had_had (nits, v, had, had_nowt);
    return had_nowt; }
    
bool value_expected (const e_media prop, e_type& t, bool& length, bool& ratio, bool& dpi)
{   length = ratio = dpi = false;
    switch (prop)
    {   case md_any_hover :
        case md_hover :
            t = t_media_hover;
            return true;
        case md_any_pointer :
        case md_pointer :
            t = t_media_pointer;
            return true;
        case md_aspect_ratio :
        case md_device_aspect_ratio :
        case md_max_aspect_ratio :
        case md_max_device_aspect_ratio :
        case md_min_aspect_ratio :
        case md_min_device_aspect_ratio :
            t = t_unsigned;
            length = ratio = true;
            return true;
        case md_colour :
        case md_colour_index :
        case md_horizontal_viewport_segments :
        case md_max_colour :
        case md_max_colour_index :
        case md_max_monochrome :
        case md_min_colour :
        case md_min_colour_index :
        case md_min_monochrome :
        case md_monochrome :
        case md_vertical_viewport_segments :
            t = t_unsigned;
            return true;
        case md_colour_gamut :
        case md_video_colour_gamut :
            t = t_gamut;
            return true;
        case md_prefers_colour_scheme :
            t = t_colour_scheme;
            return true;
        case md_device_height :
        case md_device_width :
        case md_height :
        case md_max_device_height :
        case md_max_device_width :
        case md_max_height :
        case md_max_width :
        case md_min_device_height :
        case md_min_device_width :
        case md_min_height :
        case md_min_width :
        case md_width :
            t = t_unsigned;
            length = true;
            return true;
        case md_display_mode :
            t = t_media_display_mode;
            return true;
        case md_dynamic_range :
        case md_video_dynamic_range :
            t = t_dynamic_range;
            return true;
        case md_environment_blending :
            t = t_environment_blending;
            return true;
        case md_forced_colours :
            t = t_forced_colours;
            return true;
       case md_grid :
            t = t_zero_or_one;
            return true;
        case md_inverted_colours :
            t = t_inverted_colours;
            return true;
        case md_max_resolution :
        case md_min_resolution :
        case md_resolution :
            t = t_unsigned;
            dpi = true;
            return true;
        case md_nav_controls :
            t = t_nav_controls;
            return true;
        case md_orientation :
            t = t_media_orientation;
            return true;
        case md_overflow_block :
            t = t_media_overflow;
            return true;
        case md_overflow_inline :
            t = t_media_inline;
            return true;
        case md_prefers_reduced_data :
        case md_prefers_reduced_transparency :
            t = t_media_prefers;
            return true;
        case md_prefers_contrast :
            t = t_media_prefers_2;
            return true;
        case md_scan :
            t = t_scan;
            return true;
        case md_scripting :
            t = t_media_scripting;
            return true;
        case md_update :
            t = t_media_update;
            return true;
        default :
            break; }
    return false; }

void check_feature_compatibility (nitpick& nits, const html_version& , const e_media media, const e_media prop)
{   switch (media)
    {   case md_all :
            break;
        case md_aural :
        case md_speech :
            switch (prop)
            {   case md_colour :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, "although colour is essential in audio, the colour feature only applies to visual media");
                    break;
                case md_colour_index :
                case md_aspect_ratio :
                case md_device_aspect_ratio :
                case md_device_width :
                case md_device_height :
                case md_grid :
                case md_height :
                case md_max_aspect_ratio :
                case md_max_colour :
                case md_max_colour_index :
                case md_max_device_aspect_ratio :
                case md_max_device_width :
                case md_max_device_height :
                case md_max_height :
                case md_max_monochrome :
                case md_max_resolution :
                case md_max_width :
                case md_min_aspect_ratio :
                case md_min_colour :
                case md_min_colour_index :
                case md_min_device_aspect_ratio :
                case md_min_device_width :
                case md_min_device_height :
                case md_min_height :
                case md_min_monochrome :
                case md_min_resolution :
                case md_min_width :
                case md_monochrome :
                case md_orientation :
                case md_resolution :
                case md_scan :
                case md_width :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, enum_n < t_media, e_media > :: name (prop), " is ignored by ", enum_n < t_media, e_media > :: name (media), " media");
                    break;
                default :
                    break; }
            break;
        case md_tty :
            switch (prop)
            {   case md_orientation :
                case md_aspect_ratio :
                case md_max_aspect_ratio :
                case md_max_resolution :
                case md_min_aspect_ratio :
                case md_min_resolution :
                case md_resolution :
                case md_scan :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, enum_n < t_media, e_media > :: name (prop), " is ignored by ", enum_n < t_media, e_media > :: name (media), " media");
                    break;
                default :
                    break; }
            break;
        case md_print :
            switch (prop)
            {   case md_scan :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, enum_n < t_media, e_media > :: name (prop), " is ignored by ", enum_n < t_media, e_media > :: name (media), " media");
                    break;
                default :
                    break; }
            break;
        case md_braille :
        case md_embossed :
            switch (prop)
            {   case md_aspect_ratio :
                case md_colour :
                case md_colour_index :
                case md_max_aspect_ratio :
                case md_max_colour :
                case md_max_colour_index :
                case md_max_monochrome :
                case md_max_resolution :
                case md_min_aspect_ratio :
                case md_min_colour :
                case md_min_colour_index :
                case md_min_monochrome :
                case md_min_resolution :
                case md_monochrome :
                case md_orientation :
                case md_resolution :
                case md_scan :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, enum_n < t_media, e_media > :: name (prop), " is ignored by ", enum_n < t_media, e_media > :: name (media), " media");
                    break;
                default :
                    break; }
            break;
        case md_screen :
        case md_projection :
        case md_handheld :
            switch (prop)
            {   case md_scan :
                    nits.pick (nit_media_ignored, es_warning, ec_mql, enum_n < t_media, e_media > :: name (prop), " is ignored by ", enum_n < t_media, e_media > :: name (media), " media");
                    break;
                default :
                    break; }
            break;
        case md_tv :
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            break; } }

bool validate_version (nitpick& nits, const int cv, const e_media media, const vstr_t& commas, const int comma, const ::std::string& ver_name)
{   switch (media)
    {   case md_active :
        case md_additive :
        case md_back :
        case md_browser :
        case md_custom :
        case md_dark :
        case md_dynamic_range :
        case md_enabled :
        case md_environment_blending :
        case md_fullscreen :
        case md_forced_colours :
        case md_high :
        case md_horizontal_viewport_segments :
        case md_initial_only :
        case md_inverted :
        case md_inverted_colours :
        case md_less :
        case md_light :
        case md_minimal_ui :
        case md_more :
        case md_opaque :
        case md_prefers_colour_scheme :
        case md_prefers_contrast :
        case md_prefers_reduced_data :
        case md_prefers_reduced_transparency :
        case md_reduce :
        case md_scripting :
        case md_standalone :
        case md_standard :
        case md_subtractive :
        case md_vertical_viewport_segments :
        case md_video_colour_gamut :
        case md_video_dynamic_range :
            if (cv < 5)
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires CSS Media 5");
                return false; }
            break;
        case md_any_hover :
        case md_any_pointer :
        case md_coarse :
        case md_fast :
        case md_fine :
        case md_colour_gamut :
        case md_gt :
        case md_gteq :
        case md_hover :
        case md_lt :
        case md_lteq :
        case md_infinite :
        case md_no_preference :
        case md_none :
        case md_p3 :
        case md_paged :
        case md_pointer :
        case md_rec2020 :
        case md_scroll :
        case md_slow :
        case md_srgb :
            if (cv < 4)
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires CSS Media 4 or later");
                return false; }
            break;
        case md_device_aspect_ratio :
        case md_device_width :
        case md_device_height :
        case md_max_device_aspect_ratio :
        case md_max_device_width :
        case md_max_device_height :
        case md_min_device_aspect_ratio :
        case md_min_device_width :
        case md_min_device_height :
            if (cv > 3)
                nits.pick (nit_deprecated_media, ed_css_media_4, "Appendix A", es_warning, ec_mql,
                    enum_n < t_media, e_media > :: name (media), " is deprecated in ", ver_name, ", 'Authors must not use them'.");
            break;
        case md_aural :
        case md_braille :
        case md_embossed :
        case md_handheld :
        case md_projection :
        case md_speech :
        case md_tty :
        case md_tv :
            if (cv >= 4)
                nits.pick (nit_deprecated_media, ed_css_media_4, "2.3. Media Types", es_warning, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media),
                    " is deprecated in ", ver_name, ", 'Authors must not use these media types'");
            break;
        default :
            break; }
    return true; }

bool token_flow (nitpick& nits, const html_version& v, const vm_t& vm, const ::std::string& , const vstr_t& commas)
{   typedef enum { tf_dull, tf_brac, tf_colonised, tf_silly_brac } tf_state;
    typedef::std::vector < bool > vdv_t;
    int comma = 0;
    tf_state status = tf_dull;
    e_media device = md_error;
    vdv_t vdv (md_error);
    bool    res = true, ignore = false, knot = false, args = false, argled = false, colonised = false, numbered = false, want_val = false,
            len = false, ratio = false, dpi = false, slashed = false, resolved = false, discrete = false, rator = false, silly = false;
    e_type t = t_error;
    ::std::string ver_name;
    switch (v.css_media ())
    {   case 3 : ver_name = "CSS Media Level 3"; break;
        case 4 : ver_name = "CSS Media Level 4"; break;
        case 5 : ver_name = "CSS Media Level 5 (draft)"; break;
        default : ver_name = v.name (); break; }
    constexpr flags_t mask = ( H2_CSS_MEDIA_MASK | H2_CSS_2_PLUS );
    const flags_t mv = v.ext2 () & mask;
    const int cv = v.css_media ();
    for (auto m : vm)
    {   if (ignore && (m.m_ != md_comma)) continue;
        const html_version ver = enum_n < t_media, e_media > :: first_version (m.m_);
        const flags_t mv2 = ver.ext2 () & mask;
        if ((mv & mv2) == 0)
        {   ::std::string mm (enum_n < t_media, e_media > :: name (m.m_));
            if (commas.at (comma) != enum_n < t_media, e_media > :: name (m.m_))
                nits.pick (nit_media_ignored, es_warning, ec_mql, quote (mm), ", and so ", quote (commas.at (comma)), ", is ignored in ", ver_name);
            else nits.pick (nit_media_ignored, es_warning, ec_mql, quote (mm), " is ignored in ", ver_name);
            ignore = true;
            continue; }
        if (! validate_version (nits, v.css_media (), m.m_, commas, comma, ver_name))
        {   ignore = true;
            continue; }
        if ((status == tf_brac) || (status == tf_silly_brac))
        {   switch (m.m_)
            {   case md_active :
                    if (t != t_forced_colours)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to forced-colors");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_additive :
                case md_opaque :
                case md_subtractive :
                    if (t != t_environment_blending)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to environment-blending");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_and :
                case md_or :
                    if (! silly)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (11)");
                        res = discrete = false;
                        ignore = true;
                        device = md_error; }
                    break;
                case md_not :
                case md_only :
                    if (cv < 5)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": here, ", enum_n < t_media, e_media > :: name (m.m_), " requires CSS Media 5");
                        return false; }
                    break;
                case md_any_hover :
                case md_any_pointer :
                case md_colour_gamut :
                case md_inverted_colours :
                case md_nav_controls :
                case md_pointer :
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = rator = colonised = false;
                    discrete = true;
                    break;
                case md_aspect_ratio :
                case md_height :
                case md_max_aspect_ratio :
                case md_max_colour :
                case md_max_colour_index :
                case md_max_height :
                case md_max_monochrome :
                case md_max_width :
                case md_min_aspect_ratio :
                case md_min_colour :
                case md_min_colour_index :
                case md_min_height :
                case md_min_monochrome :
                case md_min_width :
                case md_width :
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = true;
                    discrete = rator = numbered = colonised = false;
                    break;
                case md_back :
                    if (t != t_nav_controls)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to nav-controls");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_brac :
                    if (status == tf_silly_brac)
                    {   nits.pick (nit_bad_media, es_warning, ec_mql, quote (commas.at (comma)), ": too many brackets for ", PROG, " today");
                        ignore = true; }
                    status = tf_silly_brac;
                    break;
                case md_browser :
                case md_fullscreen :
                case md_minimal_ui :
                case md_standalone :
                    if (t != t_media_display_mode)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to any-pointer or pointer");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_custom_media :
                    ignore = true;
                    break;
                case md_dark :
                case md_light :
                    if (t != t_colour_scheme)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to color-scheme");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_device_aspect_ratio :
                case md_device_width :
                case md_device_height :
                case md_max_device_aspect_ratio :
                case md_max_device_width :
                case md_max_device_height :
                case md_min_device_aspect_ratio :
                case md_min_device_width :
                case md_min_device_height :
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = true;
                    discrete = rator = numbered = colonised = false;
                    break;
                case md_colon :
                    if (! args)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (1)");
                        res = false; }
                    else colonised = true;
                    args = rator = false;
                    break;
                case md_colour :
                case md_colour_index :
                case md_grid :
                case md_monochrome :
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = discrete = rator = colonised = false;
                    break;
                case md_coarse :
                case md_fine :
                    if (t != t_media_pointer)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to any-pointer or pointer");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_custom :
                case md_more :
                case md_less :
                    if (t != t_media_prefers_2)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to prefers-contrast");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_dpcm :
                case md_dpi :
                    if (! numbered)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": missing quantity before ", enum_n < t_media, e_media > :: name (m.m_));
                        res = false; 
                        break; }
                    else numbered = false;
                    if (! resolved)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applied to resolution properties.");
                        res = false; }
                    else resolved = false;
                    argled = true;
                    rator = false;
                    break;
                case md_display_mode :
                case md_dynamic_range :
                case md_environment_blending :
                case md_forced_colours :
                case md_horizontal_viewport_segments :
                case md_prefers_colour_scheme :
                case md_prefers_contrast :
                case md_prefers_reduced_data :
                case md_prefers_reduced_transparency :
                case md_scripting :
                case md_vertical_viewport_segments :
                case md_video_colour_gamut :
                case md_video_dynamic_range :
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    discrete = want_val = true;
                    rator = false;
                    break;
                case md_em :
                case md_px :
                    if (! numbered)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": missing quantity before ", enum_n < t_media, e_media > :: name (m.m_));
                        res = false;
                        break; }
                    numbered = rator = false;
                    if (want_val && ! len)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applied to length properties.");
                        res = false; }
                    len = false;
                    argled = true;
                    break;
                case md_enabled :
                case md_initial_only :
                    if (t != t_media_display_mode)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to scripting");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_eq :
                    if (discrete)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " does not work on features with discrete values");
                        ignore = true;
                        break; }
                    FALLTHROUGH;
                case md_gt :
                case md_gteq :
                case md_lt :
                case md_lteq :
                    if (colonised)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": specify one ", enum_n < t_media, e_media > :: name (m.m_), " or colon, but not more");
                        ignore = true; }
                    else if (rator)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": syntax error (", enum_n < t_media, e_media > :: name (m.m_), ")");
                        ignore = true; }
                    else rator = colonised = true;
                    numbered = false;
                    break;
                case md_fast :
                case md_slow :
                    if (t != t_media_update)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting an update value");
                        res = false;
                        ignore = true; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_high :
                case md_standard :
                    if (t != t_dynamic_range)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to dynamic-range");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_hover :
                    if (colonised)
                    {   if (t != t_media_hover)
                        {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to any-hover or hover");
                            ignore = true; }
                        else if (slashed)
                        {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                            ignore = true; }
                        rator = false;
                        argled = true; }
                    else
                    {   args = value_expected (m.m_, t, len, ratio, dpi);
                        want_val = rator = false;
                        discrete = true; }
                    break;
                case md_infinite :
                    if (! resolved)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to resolution");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_interlace :
                case md_progressive :
                    if (! colonised)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (3)");
                        res = rator = false;
                        break; }
                    colonised = rator = false;
                    if (t != t_scan)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting a scan value");
                        res = false; }
                     argled = true;
                    break;
                case md_inverted :
                    if (t != t_inverted_colours)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to inverted-colors");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_ket :
                    if (want_val && args && ! argled)
                        nits.pick (nit_bad_media, es_warning, ec_mql, quote (commas.at (comma)), ": missing feature value");
                    if (status == tf_silly_brac)
                    {   status = tf_brac;
                        silly = true; }
                    else
                    {   status = tf_dull;
                        args = argled = colonised = numbered = len = ratio = dpi = slashed = resolved = want_val = discrete = rator = silly = false; }
                    break;
                case md_landscape :
                case md_portrait :
                    if (! colonised)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (3)");
                        res = rator = false;
                        break; }
                    colonised = rator = false;
                    if (t != t_media_orientation)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting an orientation value");
                        res = false; }
                    argled = true;
                    break;
                case md_min_resolution :
                case md_max_resolution :
                case md_resolution :
                    resolved = true;
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = true;
                    discrete = rator = colonised = false;
                    break;
                case md_negative :
                case md_positive :
                    if (numbered)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", quote (m.s_), " (9)");
                        res = rator = false;
                        break; }
                    argled = numbered = true;
                    colonised = slashed = rator = false;
                    if (m.m_ == md_negative)
                    {   if (t != t_integer)
                        {   nits.pick (nit_illegal_value, es_error, ec_mql, quote (commas.at (comma)), ": not expecting a negative number here");
                            res = false;
                            break; } }
                    else switch (t)
                    {   case t_integer :
                        case t_unsigned :
                            if (ratio && (m.s_ == "0"))
                            {   nits.pick (nit_illegal_value, es_error, ec_mql, quote (commas.at (comma)), ": ratios cannot contain zero");
                                res = false; }
                            break;
                        case t_zero_or_one :
                            if ((m.s_ != "0") && (m.s_ != "1"))
                            {   nits.pick (nit_illegal_value, es_error, ec_mql, quote (commas.at (comma)), ": only 0 and 1 are valid");
                                res = false; }
                            break;
                        case t_error :
                            break;
                        default :
                            nits.pick (nit_illegal_value, es_error, ec_mql, quote (commas.at (comma)), ": not expecting an integer here");
                            res = false;
                            break; }
                    break;
                case md_no_preference :
                    if ((t != t_media_prefers) && (t != t_media_prefers_2))
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is not a valid value here");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_none :
                    switch (t)
                    {   case t_forced_colours :
                        case t_inverted_colours :
                        case t_media_hover :
                        case t_media_inline :
                        case t_media_overflow :
                        case t_media_pointer :
                        case t_media_update :
                        case t_nav_controls :
                            break;
                        default :
                            nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting none here");
                            res = false;
                            ignore = true;
                            break; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_orientation :
                case md_scan :
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = discrete = true;
                    rator = false;
                    break;
                case md_p3 :
                case md_rec2020 :
                case md_srgb :
                    if (t != t_gamut)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting a colour gamut value");
                        res = false;
                        ignore = true; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_paged :
                    if (t != t_media_overflow)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting an overflow value");
                        res = false;
                        ignore = true; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_reduce :
                    if (t != t_media_prefers)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " only applies to prefers-reduced-transparency");
                        ignore = true; }
                    else if (slashed)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is no ratio");
                        ignore = true; }
                    rator = colonised = false;
                    argled = true;
                    break;
                case md_scroll :
                    if ((t != t_media_overflow) && (t != t_media_inline))
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": not expecting an overflow value");
                        res = false;
                        ignore = true; }
                    rator = resolved = false;
                    argled = true;
                    break;
                case md_slash :
                    if (! numbered)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (4)");
                        res = rator = false;
                        break; }
                    if (! ratio)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " is only for ratio values");
                        res = rator = false;
                        break; }
                    numbered = ratio = argled = rator = false;
                    slashed = true;
                    break;
                case md_space :
                    numbered = false;
                    continue;
                case md_update :
                    check_feature_compatibility (nits, v, device, m.m_);
                    args = value_expected (m.m_, t, len, ratio, dpi);
                    discrete = true;
                    want_val = rator = false;
                    break;
                default :
                    nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (5)");
                    res = discrete = false;
                    ignore = true;
                    device = md_error;
                    break; } }
        else switch (m.m_)
        {   case md_comma :
                if (status != tf_dull)
                {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected comma (6)");
                    status = tf_dull;
                    res = false; }
                device = md_error;
                ignore = knot = false;
                ++comma;
                break;
            case md_brac :
                if (device == md_error) device = md_all;
                status = tf_brac;
                knot = false;
                break;
            case md_and :
            case md_or :
                device = md_all;
                knot = false;
                break;
            case md_not :
            case md_only :
                device = md_error;
                knot = true;
                break;
            case md_aural :
            case md_braille :
            case md_embossed :
            case md_handheld :
            case md_projection :
            case md_speech :
            case md_tty :
            case md_tv :
            case md_screen :
            case md_print :
            case md_all :
                if ((device != md_all) && (device != md_error))
                {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " unexpected; is a comma missing?");
                    res = false; }
                else if ((m.m_ == md_all) && knot)
                {   nits.pick (nit_bad_media, es_error, ec_mql, "not all?");
                    res = false; }
                knot = false;
                if (cv < css_3)
                {   PRESUME (m.m_ < vdv.size (), __FILE__, __LINE__);
                    if (vdv.at (m.m_))
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " repeated");
                        res = false; }
                    vdv.at (m.m_) = true; }
                device = m.m_;
                break;                    
            case md_space :
                continue;
            case md_colon :
            case md_slash :
            case md_ket :
            case md_px :
            case md_em :
            case md_dpcm :
            case md_dpi :
                nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": syntax error (", quote (enum_n < t_media, e_media > :: name (m.m_)));
                res = knot = false;
                ignore = true;
                device = md_error;
                break;
            case md_custom_media :
                knot = false;
                ignore = true;
                device = md_error;
                break;
            case md_portrait :
            case md_landscape :
            case md_progressive :
            case md_interlace :
                nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", quote (enum_n < t_media, e_media > :: name (m.m_)), " (7)");
                res = knot = false;
                ignore = true;
                device = md_error;
                break;                    
            case md_negative :
            case md_positive :
                nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", m.s_, " (8)");
                res = knot = false;
                ignore = true;
                device = md_error;
                break;
            default :
                if (m.m_ == md_error)
                    nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": syntax error");
                else
                    nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), "; perhaps missing brackets?");
                res = knot = false;
                ignore = true;
                device = md_error;
                break; } }
    return res; }

bool parse_media_query (nitpick& nits, const html_version& v, const ::std::string& sss, const ustr_t& custom_media)
{   e_had had = had_nowt;
    ::std::string s, ss;
    vstr_t commas;
    vm_t vm;
    for (auto ch : sss)
    {   switch (ch)
        {   case '(' : had = note_token (nits, v, vm, had, md_brac, s, custom_media); break;
            case ':' : had = note_token (nits, v, vm, had, md_colon, s, custom_media); break;
            case ')' : had = note_token (nits, v, vm, had, md_ket, s, custom_media); break;
            case '/' : had = note_token (nits, v, vm, had, md_slash, s, custom_media); break;
            case '<' : had = had_had (nits, v, had, had_lt); break;
            case '>' : had = had_had (nits, v, had, had_gt); break;
            case '=' :
                if (had == had_lt) had = note_token (nits, v, vm, had_nowt, md_lteq, s, custom_media);
                else if (had == had_gt) had = note_token (nits, v, vm, had_nowt, md_gteq, s, custom_media);
                else had = note_token (nits, v, vm, had_nowt, md_eq, s, custom_media);
                break;        
            case ',' :
                commas.push_back (ss);
                ss.clear ();
                had = note_token (nits, v, vm, had, md_comma, s, custom_media);
                continue;
            case ' ' :
                if (had != had_space)
                    had = note_token (nits, v, vm, had, md_space, s, custom_media);
                break;
            default :
                if (ch > ' ')
                {   s += ch;
                    had = had_nowt; }
                break; }
        if ((ch > ' ') || ! ss.empty ()) ss += ch; }
    commas.push_back (ss);
    if (! s.empty ()) note_value (nits, v, vm, had, s, custom_media);
    if (context.tell (es_detail)) mtkn_report (vm);
    return token_flow (nits, v, vm, sss, commas); }
