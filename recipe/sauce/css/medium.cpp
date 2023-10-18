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

#include "main/standard.h"
#include "type/type.h"
#include "css/medium.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/flags.h"
#include "css/group.h"

void medium_t::mtkn_report ()
{   ::std::string res, line, item;
    if (context.tell (es_detail))
    {   res += "\nMedia:\n";
        for (auto m : vm_)
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
        outstr.out (res); } }
   
void medium_t::note_value (const arguments& args, nitpick& nits, const ::std::string& s)
{   PRESUME (! s.empty (), __FILE__, __LINE__);
    if (args.g_.custom_media ().find (s) != args.g_.custom_media ().cend ())
        vm_.emplace_back (md_custom_media, s);
    else
    {   const ::std::string starters (DENARY "-");
        const ::std::string denary (DENARY);
        if (starters.find (s.at (0)) == ::std::string::npos) 
        {   enum_n < t_media, e_media > md;
            md.set_value (nits, args.v_, s); }
        else
        {   ::std::string n;
            const ::std::string::size_type pos = s.substr (1).find_first_not_of (DENARY);
            if (pos == ::std::string::npos) n = s;
            else n = s.substr (0, pos+1);
            if (n.at (0) == '-') vm_.emplace_back (md_negative, s);   
            else vm_.emplace_back (md_positive, s);
            if (pos == ::std::string::npos) return;
            n = s.substr (pos+1);
            nitpick nuts;
            enum_n < t_media, e_media > md;
            md.set_value (nuts, args.v_, n);
            if (md.good ())
                nits.merge (nuts);
            else
            {   enum_n < t_unit, e_unit > un;
                un.set_value (nits, args.v_, n); } } } }

void medium_t::note_token (const arguments& args, nitpick& nits, const e_media m, const ::std::string& s)
{   if (! s.empty ()) note_value (args, nits, s);
    vm_.emplace_back (m); }
    
bool medium_t::value_expected (const e_media prop, e_type& t, bool& length, bool& ratio, bool& dpi)
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

void medium_t::check_feature_compatibility (nitpick& nits, const e_media media, const e_media prop)
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
        case md_reader :
        case md_tv :
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            break; } }

bool medium_t::validate_version (const arguments& args, nitpick& nits, const e_media media, const vstr_t& commas, const int comma)
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
            if (args.v_.css_media () < 5)
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
            if ((args.v_.css_media () < 4) && (args.v_.css_conditional_rule () < 3))
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires CSS Conditional Rules, or CSS Media 4 or later");
                return false; }
            break;
        case md_aural :
        case md_braille :
        case md_embossed :
        case md_handheld :
        case md_projection :
        case md_speech :
        case md_tty :
        case md_tv :
            if (args.v_.css_media () >= 4)
                nits.pick (nit_deprecated_media, ed_css_media_4, "2.3. Media Types", es_warning, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media),
                    " is deprecated in ", args.v_.long_css_version_name (), ", 'Authors must not use these media types'");
            break;
        case md_media :
        case md_supports :
            if (args.v_.css_conditional_rule () < 5)
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires CSS Conditional Rules 5 or better");
                return false; }
            if ((args.st_ == nullptr) || ((args.st_ -> get () != css_else) && (args.st_ -> get () != css_when)))
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires a parental @else or @when");
                return false; }
            break;
        case md_selector :
            if (args.v_.css_conditional_rule () < 4)
            {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (media), " requires CSS Conditional Rules 4 or better");
                return false; }
            break;
        default :
            break; }
    return true; }

bool medium_t::token_flow (arguments args, nitpick& nits, const vstr_t& commas)
{   typedef enum { tf_dull, tf_brac, tf_colonised, tf_silly_brac } tf_state;
    typedef::std::vector < bool > vdv_t;
    int comma = 0;
    tf_state status = tf_dull;
    e_media device = md_error;
    vdv_t vdv (md_error);
    bool    res = true, ignore = false, knot = false, arged = false, argled = false, colonised = false, numbered = false, want_val = false,
            len = false, ratio = false, dpi = false, slashed = false, resolved = false, discrete = false, rator = false, silly = false;
    e_type t = t_error;
    const ::std::string ver_name (args.v_.long_css_version_name ());
    for (auto m : vm_)
    {   if (ignore && (m.m_ != md_comma)) continue;
        if (! args.v_.is_css_compatible (enum_n < t_media, e_media > :: first_version (m.m_)))
        {   ::std::string mm (enum_n < t_media, e_media > :: name (m.m_));
            if (commas.at (comma) != enum_n < t_media, e_media > :: name (m.m_))
                nits.pick (nit_media_ignored, es_warning, ec_mql, quote (mm), ", and so ", quote (commas.at (comma)), ", is ignored in ", ver_name);
            else nits.pick (nit_media_ignored, es_warning, ec_mql, quote (mm), " is ignored in ", ver_name);
            ignore = true;
            continue; }
        if (! validate_version (args, nits, m.m_, commas, comma))
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
                case md_any_hover :
                case md_any_pointer :
                case md_colour_gamut :
                case md_inverted_colours :
                case md_nav_controls :
                case md_pointer :
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
                    want_val = true;
                    discrete = rator = numbered = colonised = false;
                    break;
                case md_colon :
                    if (! arged)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (1)");
                        res = false; }
                    else colonised = true;
                    arged = rator = false;
                    break;
                case md_colour :
                case md_colour_index :
                case md_grid :
                case md_monochrome :
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    {   arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    if (want_val && arged && ! argled)
                        nits.pick (nit_bad_media, es_warning, ec_mql, quote (commas.at (comma)), ": missing feature value");
                    if (status == tf_silly_brac)
                    {   status = tf_brac;
                        silly = true; }
                    else
                    {   status = tf_dull;
                        arged = argled = colonised = numbered = len = ratio = dpi = slashed = resolved = want_val = discrete = rator = silly = false; }
                    break;
                case md_landscape :
                case md_portrait :
                    if (! colonised)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": unexpected ", enum_n < t_media, e_media > :: name (m.m_), " (3)");
                        res = rator = false;
                        break; }
                    colonised = rator = false;
                    if (t != t_media_orientation)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": expecting an orientation value");
                        res = false; }
                    argled = true;
                    break;
                case md_media :
                case md_supports :
                    check_feature_compatibility (nits, device, m.m_);
                    break;
                case md_min_resolution :
                case md_max_resolution :
                case md_resolution :
                    resolved = true;
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                case md_not :
                    if (args.v_.css_media () < 3)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": here, ", enum_n < t_media, e_media > :: name (m.m_), " requires CSS Media 3");
                        return false; }
                    else if (! vm_.empty ())
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), " must be first");
                        return false; }
                    break;
                case md_only :
                    if (args.v_.css_media () < 4)
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": here, ", enum_n < t_media, e_media > :: name (m.m_), " requires CSS Media 4");
                        return false; }
                    else if (! vm_.empty ())
                    {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), " must be first");
                        return false; }
                    break;
                case md_orientation :
                case md_scan :
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
                    check_feature_compatibility (nits, device, m.m_);
                    arged = value_expected (m.m_, t, len, ratio, dpi);
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
            case md_print :
            case md_projection :
            case md_reader :
            case md_screen :
            case md_speech :
            case md_tty :
            case md_tv :
            case md_all :
                if ((device != md_all) && (device != md_error))
                {   nits.pick (nit_bad_media, es_error, ec_mql, quote (commas.at (comma)), ": ", enum_n < t_media, e_media > :: name (m.m_), " unexpected; is a comma missing?");
                    res = false; }
                else if ((m.m_ == md_all) && knot)
                {   nits.pick (nit_bad_media, es_error, ec_mql, "not all?! only all?!");
                    res = false; }
                knot = false;
                if (args.v_.css_media () < css_3)
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

void medium_t::triple_pong (const arguments& args, nitpick& nits, const int level, const bool zero, const int brackets,
                            const media_expects got, const media_expects expect, media_expects& expecting,
                            const char* wot, const e_media e, ::std::string& ss)
{   if (context.css_media () < level) 
    {   valid_ = false;
        nits.pick (nit_css_version, es_error, ec_mql, "'", wot, "' in media queries require CSS Media Queries level ", level, " or better"); }
    else if ((! zero) && (brackets == 0))
    {   valid_ = false;
        nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected ", wot); }
    else if (expecting != got)
    {   valid_ = false;
        nits.pick (nit_css_syntax, es_error, ec_mql, "malplaced ", wot); }
    else
    {   note_token (args, nits, e);
        expecting = expect;
        ss += wot; } }

void medium_t::parse (arguments& args , const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int final = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < final, __FILE__, __LINE__);
    PRESUME (to < final, __FILE__, __LINE__);
    const int len = (to > 0) ? to : final;
    typedef ssc_bitset < e_media, md_error > medium_bitset;
    medium_bitset mb;
    media_expects expecting = me_id;
    int brackets = 0;
    int i = first_non_whitespace (args.t_, from, len);
    if (i < 0) return;
    nitpick& nits = args.t_.at (i).nits_;
    ::std::string ss;
    vstr_t commas;
    bool first = true;
    for (; (i >= 0) && (i <= len); i = next_token_at (args.t_, i, len))
    {   const ::std::string& val = args.t_.at (i).val_;
        switch (args.t_.at (i).t_)
        {   case ct_identifier :
                if ((args.v_.css_media () > 3) && (args.g_.custom_media ().find (val) != args.g_.custom_media ().cend ()))
                {   switch (expecting)
                    {   case me_id :
                            expecting = me_after_id;
                            break;
                        case me_prop :
                            expecting = me_after_prop;
                            break;
                        case me_val :
                            expecting = me_after_val;
                            break;
                        default :
                            valid_ = false;
                            nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected \"", val, "\"");
                            break; }
                    if (valid_)
                    {   note_token (args, nits, md_custom_media);
                        ss += val; }
                    break; }
                FALLTHROUGH;
            case ct_keyword :
            {   nitpick nuts;
                const e_media e = examine_value < t_media > (nuts, args.v_, val);                
                if ((e == md_context) || (e == md_error))
                    switch (expecting)
                    {   case me_id :
                            if (! first)
                            {   valid_ = false;
                                nits.merge (nuts);
                                expecting = me_after_id;
                                break; }
                            FALLTHROUGH;
                        case me_prop :
                            if (! first)
                            {   valid_ = false;
                                nits.merge (nuts);
                                expecting = me_after_prop;
                                break; }
                            FALLTHROUGH;
                        case me_number :
                        case me_val :
                            ss += val;
                            note_value (args, nits, val);
                            expecting = me_after_val;
                            break;
                        default :
                            valid_ = false;
                            nits.merge (nuts);
                            break; }
                else
                {   nits.merge (nuts);
                    const flags_t fl = enum_n < t_media, e_media > :: flags (e);
                    args.check_flags (nits, fl, val);
                    if ((fl & CF_MEDIA_FIRST) == CF_MEDIA_FIRST)
                    {   if (! first)
                        {   nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), " must come first");
                            valid_ = false; }
                        break; }
                    switch (expecting)
                    {   case me_id :
                            if ((fl & CF_MEDIA_DEVICE) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": expecting a device"); }
                            else
                            {   note_token (args, nits, e);
                                ss += val;
                                if ((fl & CF_FUNCTION) == CF_FUNCTION) expecting = me_brac;
                                else expecting = me_after_id; }
                            break;
                        case me_prop : 
                            if ((fl & CF_MEDIA_PROPERTY) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": expecting a property"); }
                            else
                            {   note_token (args, nits, e);
                                ss += val;
                                expecting = me_after_prop; }
                            break;
                        case me_val :
                            if ((fl & CF_MEDIA_VALUE) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": expecting a value (strings must be in quotes)"); }
                            else
                            {   note_token (args, nits, e);
                                ss += val;
                                if (brackets == 0) expecting = me_after_id;
                                else expecting = me_after_val; }
                            break;
                        case me_after_id :
                            if ((fl & (CF_MEDIA_LOGIC | CF_MEDIA_UNIT)) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": rather unexpected"); }
                            else
                            {   note_token (args, nits, e);
                                if ((fl & CF_MEDIA_LOGIC) == CF_MEDIA_LOGIC) expecting = me_id;
                                ss += val; }
                            break;
                        case me_after_val :
                            if ((fl & CF_MEDIA_UNIT) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": expecting units, if anything"); }
                            else
                            {   note_token (args, nits, e);
                                if ((fl & CF_MEDIA_LOGIC) == CF_MEDIA_LOGIC) expecting = me_id;
                                ss += val; }
                            break;
                        case me_after_prop :
                            if ((fl & CF_MEDIA_LOGIC) == 0)
                            {   valid_ = false;
                                nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": expecting a value, if anything"); }
                            else
                            {   note_token (args, nits, e);
                                expecting = me_prop;
                                ss += val; }
                            break;
                        default :
                            valid_ = false;
                            nits.pick (nit_css_syntax, es_error, ec_mql, quote (val), ": unexpected");
                            break; } }
                break; }
            case ct_string :
                if (expecting != me_val)
                {   valid_ = false;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected \"", val, "\""); }
                else
                {   note_value (args, nits, val);
                    if (brackets == 0) expecting = me_after_id;
                    else expecting = me_after_val;
                    if (args.t_.at (i).t_ == ct_string) ss += "\"";
                    ss += val; 
                    if (args.t_.at (i).t_ == ct_string) ss += "\""; }
                break;
            case ct_number :
                if ((expecting != me_val) && (expecting != me_number))
                {   valid_ = false;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected ", val); }
                else
                {   note_value (args, nits, val);
                    if (brackets == 0) expecting = me_after_id;
                    else expecting = me_after_val;
                    ss += val; }
                break;
            case ct_curly_brac :
                i = -1;
                break;
            case ct_round_brac :
                if (context.css_media () < 3)
                {   valid_ = false;
                    nits.pick (nit_css_version, es_error, ec_mql, "'(' in media queries require CSS Media Queries level 3 or better");
                    break; }
                switch (expecting)
                {   case me_after_id :
                    case me_brac :
                    case me_id :
                    case me_prop :
                        note_token (args, nits, md_brac);
                        break;
                    default : 
                        valid_ = false;
                        nits.pick (nit_css_syntax, es_error, ec_mql, "malplaced brac");
                        break; }
                if (first && mb.empty ()) mb.set (md_all);
                expecting = me_prop;
                ss += "(";
                ++brackets;
                if (context.css_cascade () > 3) first = true;
                break;
            case ct_round_ket :
                if (context.css_media () < 3) 
                {   valid_ = false;
                    nits.pick (nit_css_version, es_error, ec_mql, "')' in media queries require CSS Media Queries level 3 or better"); }
                else if (brackets < 1) 
                {   valid_ = false;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected ket"); }
                else if ((expecting != me_after_val) && (expecting != me_after_prop)) 
                {   valid_ = false;
                    --brackets;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "malplaced ket"); }
                else
                {   note_token (args, nits, md_ket);
                    --brackets;
                    ss += ")"; }
                if (brackets < 1) expecting = me_after_id;
                break;
            case ct_colon :
                if (expecting != me_after_prop)
                {   valid_ = false;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "malplaced colon"); }
                else
                {   note_token (args, nits, md_colon);
                    expecting = me_val;
                    ss += ":"; }
                break;
            case ct_comma :
                if (expecting != me_after_id) 
                {   valid_ = false;
                    nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected comma"); }
                else {
                    commas.push_back (ss);
                    shadow_ += ss + ","; 
                    ss.clear ();
                    note_token (args, nits, md_comma);
                    expecting = me_id;
                    continue; }
                break;
            case ct_eq :
                if (expecting == me_after_val) triple_pong (args, nits, 3, true, brackets, me_after_val, me_prop, expecting, "=", md_eq, ss);
                else triple_pong (args, nits, 3, true, brackets, me_after_prop, me_val, expecting, "=", md_eq, ss);
                break;
            case ct_gt :
                if (expecting == me_after_val) triple_pong (args, nits, 3, true, brackets, me_after_val, me_prop, expecting, ">", md_gt, ss);
                else triple_pong (args, nits, 3, true, brackets, me_after_prop, me_val, expecting, ">", md_gt, ss);
                break;
            case ct_gteq :
                if (expecting == me_after_val) triple_pong (args, nits, 3, true, brackets, me_after_val, me_prop, expecting, ">=", md_gteq, ss);
                else triple_pong (args, nits, 3, true, brackets, me_after_prop, me_val, expecting, ">=", md_gteq, ss);
               break;
            case ct_lt :
                if (expecting == me_after_val) triple_pong (args, nits, 3, true, brackets, me_after_val, me_prop, expecting, "<", md_lt, ss);
                else triple_pong (args, nits, 3, true, brackets, me_after_prop, me_val, expecting, "<", md_lt, ss);
                break;
            case ct_lteq :
                if (expecting == me_after_val) triple_pong (args, nits, 3, true, brackets, me_after_val, me_prop, expecting, "<=", md_lteq, ss);
                else triple_pong (args, nits, 3, true, brackets, me_after_prop, me_val, expecting, "<=", md_lteq, ss);
                break;
            case ct_slash :
                triple_pong (args, nits, 3, false, brackets, me_after_val, me_number, expecting, "/", md_slash, ss);
                break;
            case ct_whitespace :
                note_token (args, nits, md_space);
                ss += " ";
                break;
            case ct_eof :
            case ct_root :
                break;
            default :
                if (valid_) 
                {   valid_ = false;
                    if (! val.empty ()) nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected ", quote (val));
                    else nits.pick (nit_css_syntax, es_error, ec_mql, "unexpected ", tkn_rpt (args.t_.at (i).t_)); }
                break; }
        if ((i > 0) && (args.t_.at (i).t_ != ct_whitespace) && (args.t_.at (i).t_ != ct_round_brac)) first = false; }
    if (brackets > 0) 
    {   valid_ = false; nits.pick (nit_css_syntax, es_error, ec_mql, "missing ket/s"); }
    commas.push_back (ss);
    shadow_ += ss; 
    if (context.tell (es_detail)) mtkn_report ();
    if (valid_ && ! token_flow (args, nits, commas)) valid_ = false; }
    
::std::string medium_t::rpt () const
{   return ::std::string (); }

void medium_t::validate (arguments& )
{   }

void medium_t::shadow (::std::stringstream& ss, arguments& )
{   if (valid_) ss << shadow_; }
