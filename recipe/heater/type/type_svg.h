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
void svg_feature_init (nitpick& nits);
bool parse_d (nitpick& nits, const html_version& v, const ::std::string& d);
bool parse_paint (nitpick& nits, const html_version& v, const ::std::string& d, bool recheck = false);
bool parse_transform (nitpick& nits, const html_version& v, const ::std::string& d);
bool test_animation_timing (nitpick& nits, const html_version& v, const ::std::string& d, const bool begin);
e_attribute identify_svg_animation_attribute (nitpick& nits, const html_version& v, element& e, const ::std::string& s, const ::std::string& attnam);

template < > struct type_master < t_angle > : type_master < t_real >
{   using type_master < t_real > :: type_master;
    static e_animation_type animation_type () noexcept { return at_angle; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_complain (nits, v, "auto", ss))
            type_master < t_real > :: status (s_good);
        else
        {   float max = 360.0; ::std::string::size_type len = ss.length ();
            if (len > 3)
            {   ::std::string sss (ss.substr (len - 3));
                ::std::string ssss (ss.substr (len - 4));
                if (compare_complain (nits, v, ssss, "grad")) { max = 400.0; len -= 4; }
                else if (v.is_svg_2 () && compare_complain (nits, v, ssss, "turn")) { max = 1.0; len -= 4; }
                else if (compare_complain (nits, v, sss, "rad")) { max = static_cast < float > (3.141592653589*2); len -= 3; }
                else if (compare_complain (nits, v, sss, "deg")) len -= 3; }
            if (ss.substr (0, len).find_first_not_of (DECIMAL) != ::std::string::npos)
                nits.pick (nit_angle, es_error, ec_type, quote (s), " contains unexpected characters (units are 'deg', 'grad', or 'rad')");
            else
            {   type_master < t_real > :: set_value (nits, v, s);
                if (good ())
                    if ((value_ >= max) || (value_ <= (-1 * static_cast < double> (max))))
                        nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " should be less that ", ::boost::lexical_cast < ::std::string > (max));
                    else return; }
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_attributename > : tidy_string < t_attributename >
{   e_attribute value_ = a_unknown;
    using tidy_string < t_attributename > :: tidy_string;
    e_attribute get () const noexcept { return value_; }
    int get_int () const noexcept { return static_cast < int > (value_); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_attributename > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "ATTRIBUTENAME should have an attribute name");
            string_value < t_attributename > :: status (s_invalid); } }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* pe, const ::std::string& attnam)
    {   VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
        if (tidy_string < t_attributename > :: good ())
        {   value_ = identify_svg_animation_attribute (nits, v, *pe, tidy_string < t_attributename > :: get_string (), attnam);
            if (value_ == a_unknown)
                tidy_string < t_attributename > :: status (s_invalid); } } };

template < > struct type_master < t_audio_level > : type_or_string < t_audio_level, t_real, sz_inherit >
{ using type_or_string < t_audio_level, t_real, sz_inherit > :: type_or_string; };

template < > struct type_master < t_angle_i > : type_or_string < t_angle_i, t_angle, sz_inherit >
{ using type_or_string < t_angle_i, t_angle, sz_inherit > :: type_or_string; };

template < > struct type_master < t_angle_a > : type_or_string < t_angle_a, t_angle, sz_auto >
{ using type_or_string < t_angle_a, t_angle, sz_auto > :: type_or_string; };

template < > struct type_master < t_angle_ai > : type_or_either_string < t_angle_ai, t_angle, sz_auto, sz_inherit >
{ using type_or_either_string < t_angle_ai, t_angle, sz_auto, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_beginvalues > : type_at_least_one < t_beginvalues, sz_semicolon, t_beginvalue >
{   using type_at_least_one < t_beginvalues, sz_semicolon, t_beginvalue > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_beginvaluelist > : type_or_string < t_beginvaluelist, t_beginvalues, sz_indefinite >
{ using type_or_string < t_beginvaluelist, t_beginvalues, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_clip_path_rule > : type_or_either_string < t_clip_path_rule, t_urifn, sz_none, sz_inherit >
{ using type_or_either_string < t_clip_path_rule, t_urifn, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_rendering_colour_space > : type_one_of_three < t_rendering_colour_space, t_colour_interpolation, t_colour_profile_name, t_urifn >
{ using type_one_of_three < t_rendering_colour_space, t_colour_interpolation, t_colour_profile_name, t_urifn > :: type_one_of_three; };

template < > struct type_master < t_colour_profile_name_or_uri > : type_either_or < t_colour_profile_name_or_uri, t_urifn, t_colour_profile_name >
{   using type_either_or < t_colour_profile_name_or_uri, t_urifn, t_colour_profile_name > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_colour; } };

template < > struct type_master < t_colour_profile > : type_or_any_string < t_colour_profile, t_colour_profile_name_or_uri, sz_auto, sz_inherit, sz_srgb >
{ using type_or_any_string < t_colour_profile, t_colour_profile_name_or_uri, sz_auto, sz_inherit, sz_srgb > :: type_or_any_string; };

template < > struct type_master < t_cursor_f > : type_many_then_must < t_cursor_f, t_urifn, sz_comma, t_cursor >
{   using type_many_then_must < t_cursor_f, t_urifn, sz_comma, t_cursor > :: type_many_then_must;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_cursor_i > : type_or_string < t_cursor_i, t_cursor_f, sz_inherit >
{ using type_or_string < t_cursor_i, t_cursor_f, sz_inherit > :: type_or_string; };

template < > struct type_master < t_d > : tidy_string < t_d >
{   using tidy_string < t_d > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_list; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_d > :: set_value (nits, v, s);
        if (tidy_string < t_d > :: empty ())
            nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a D attribute cannot be empty");
        else if (tidy_string < t_d > :: good ())
            if (parse_d (nits, v, tidy_string < t_d > :: get_string ())) return;
        tidy_string < t_d > :: status (s_invalid); } };

template < > struct type_master < t_dashes > : type_or_either_string < t_dashes, t_measures, sz_none, sz_inherit >
{ using type_or_either_string < t_dashes, t_measures, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_dur > : type_or_either_string < t_dur, t_svg_time, sz_media, sz_indefinite >
{ using type_or_either_string < t_dur, t_svg_time, sz_media, sz_indefinite > :: type_or_either_string; };

template < > struct type_master < t_dur_repeat > : type_or_string < t_dur_repeat, t_svg_duration, sz_indefinite >
{ using type_or_string < t_dur_repeat, t_svg_duration, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_endvaluelist > : tidy_string < t_endvaluelist >
{   using tidy_string < t_endvaluelist > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_list; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_endvaluelist > :: set_value (nits, v, s);
        bool good = true;
        if (tidy_string < t_endvaluelist > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
        else if (tidy_string < t_endvaluelist > :: good ())
        {   vstr_t ve (split_by_charset (tidy_string < t_endvaluelist > :: get_string (), ";"));
            if (ve.empty ())
                nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
            else for (auto sss : ve)
                if (! test_animation_timing (nits, v, sss, false)) good = false;
            if (good) return; }
        tidy_string < t_endvaluelist > :: status (s_invalid); } };

template < > struct type_master < t_fill_opacity > : tidy_string < t_fill_opacity >
{   using tidy_string < t_fill_opacity > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fill_opacity > :: set_value (nits, v, s);
        if (tidy_string < t_fill_opacity> :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "an opacity is expected");
        else if (tidy_string < t_fill_opacity> :: good ())
        {   const ::std::string ss (tidy_string < t_fill_opacity > :: get_string ());
            if (compare_complain (nits, v, sz_inherit :: sz (), ss)) return;
            nitpick nuts, knits;
            if (test_value < t_zero_to_one > (nuts, v, ss)) { nits.merge (nuts); return; }
            if (v.is_svg_2 () && (test_value < t_percent > (knits, v, ss))) { nits.merge (knits); return; }
            nits.merge (nuts); nits.merge (knits); }
        tidy_string < t_fill_opacity > :: status (s_invalid); } };

template < > struct type_master < t_font > : tidy_string < t_font >
{   using tidy_string < t_font > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& sss)
    {   tidy_string < t_font > :: set_value (nits, v, sss);
        if (tidy_string < t_font> :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font specification cannot be empty");
        else if (tidy_string < t_font> :: good ())
        {   vstr_t ss (split_by_space (tidy_string < t_font > :: get_string ()));
            PRESUME (! ss.empty (), __FILE__, __LINE__);
            bool res = true;
            typedef enum { fs_style, fs_variant, fs_weight, fs_stretch, fs_size, fs_family, fs_done } font_state;
            font_state state = fs_style;
            for (auto s : ss)
            {   nitpick nuts, knits;
                ::std::string::size_type pos = ::std::string::npos;
                if (test_value < t_font_enum > (nuts, v, s))
                {   nits.merge (nuts);
                    if (ss.size () > 1)
                    {   nits.pick (nit_font_enum, es_error, ec_type, quote (s), " cannot be combined with other values");
                        res = false; break; } }
                else switch (state)
                {   case fs_style :
                        if (test_value < t_fontstyle > (knits, v, s))
                        {   state = fs_variant; break; }
                        [[fallthrough]];
                    case fs_variant :
                        if (test_value < t_fontvariant > (knits, v, s))
                        {   state = fs_weight; break; }
                        [[fallthrough]];
                    case fs_weight :
                        if (test_value < t_fontweight > (knits, v, s))
                        {   state = fs_stretch; break; }
                        [[fallthrough]];
                    case fs_stretch :
                        if (test_value < t_fontstretch > (knits, v, s))
                        {   state = fs_size; break; }
                        [[fallthrough]];
                    case fs_size :
                        pos = s.find ('/');
                        if (pos == ::std::string::npos)
                        {   if (test_value < t_fontsize > (knits, v, s))
                            {   state = fs_family; break; } }
                        else if (test_value < t_fontsize > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        [[fallthrough]];
                    case fs_family :
                        if (test_value < t_font_family > (knits, v, s))
                        {   state = fs_done; break; }
                        [[fallthrough]];
                    default :
                        nits.pick (nit_font_enum, es_error, ec_type, quote (s), " is not a known FONT property");
                        res = false; break; }
                if (! res) break; }
            if (res) return; }
        tidy_string < t_font > :: status (s_invalid); } };

template < > struct type_master < t_fontsize > : type_or_string < t_fontsize, t_measure, sz_inherit >
{ using type_or_string < t_fontsize, t_measure, sz_inherit > :: type_or_string; };

template < > struct type_master < t_fontsizeadjust > : type_or_either_string < t_fontsizeadjust, t_real, sz_none, sz_inherit >
{ using type_or_either_string < t_fontsizeadjust, t_real, sz_none, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_fontstretches > : public tidy_string < t_fontstretches >
{   using tidy_string < t_fontstretches > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font stretch requires SVG");
        else
        {   tidy_string < t_fontstretches > :: set_value (nits, v, s);
            if (tidy_string < t_fontstretches > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font stretch cannot be empty");
            else if (tidy_string < t_fontstretches > :: good ())
            {   ::std::string ss (tidy_string < t_fontstretches > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                const ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontstyle, es_error, ec_type, "font stretch is effectively empty");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontstretch_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontstyle, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font stretch can be 'all', or one or more condensed and/or expanded values");
        tidy_string < t_fontstretches > :: status (s_invalid); } };

template < > struct type_master < t_fontvariants > : public tidy_string < t_fontvariants >
{   using tidy_string < t_fontvariants > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font variant requires SVG");
        else
        {   tidy_string < t_fontvariants > :: set_value (nits, v, s);
            if (tidy_string < t_fontvariants > :: empty ())
                nits.pick (nit_fontvariant, es_error, ec_type, "font variant cannot be empty");
            else if (tidy_string < t_fontvariants > :: good ())
            {   ::std::string ss (tidy_string < t_fontvariants > :: get_string ());
                const ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontvariant, es_error, ec_type, "font variant is effectively empty");
                else if (fs.size () > 2)
                    nits.pick (nit_fontvariant, es_error, ec_type, "too many font variant keywords");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontvariant_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontvariant, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font variant can be'normal', 'small-caps', or both of them");
        tidy_string < t_fontvariants > :: status (s_invalid); } };

template < > struct type_master < t_frequency > : type_master < t_real >
{   using type_master < t_real > :: type_master;
    static e_animation_type animation_type () noexcept { return at_frequency; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (! ends_with_letters (v, ss, "kHz") && ! ends_with_letters (v, ss, "Hz"))
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " contains unexpected characters (units are 'kHz' or 'Hz')");
        else if (v.svg () < sv_1_1)
            nits.pick (nit_bad_frequency, es_error, ec_type, "frequencies require SVG 1.1 or better.");
        else
        {   type_master < t_real > :: set_value (nits, v, s);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_glyphname > : public tidy_string < t_glyphname >
{   using tidy_string < t_glyphname > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_glyphname > :: set_value (nits, v, s);
        if (tidy_string < t_glyphname > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "A glyph name cannot be empty"); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* pe, const ::std::string& )
    {   void store_glyph_name (nitpick& nits, const html_version& v, element* pe, const ::std::string name);
        ::std::string s (tidy_string < t_glyphname > :: get_string ());
        store_glyph_name (nits, v, pe, s); } };

template < > struct type_master < t_glyphnames > : public string_vector < t_glyphname, sz_comma >
{   using string_vector < t_glyphname, sz_comma > :: string_vector;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_glyphname, sz_comma > :: set_value (nits, v, s); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* pe)
    {   bool check_glyph_names (nitpick& nits, const html_version& v, const element* const pe, const vstr_t& vs);
        PRESUME (pe != nullptr, __FILE__, __LINE__);
        if (! string_vector < t_glyphname, sz_comma > :: good ()) return false;
        return ! check_glyph_names (nits, v, pe, string_vector < t_glyphname, sz_comma > :: get ()); } };

template < > struct type_master < t_hash_ref > : string_then_type < t_hash_ref, t_idref, sz_hash >
{   using string_then_type < t_hash_ref, t_idref, sz_hash > :: string_then_type;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_hash_fn > : type_function < t_hash_fn, t_urisz, t_hash_ref >
{   using type_function < t_hash_fn, t_urisz, t_hash_ref > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_icccolour > : tidy_string < t_icccolour >
{   using tidy_string < t_icccolour > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_icccolour > :: set_value (nits, v, s);
        if (tidy_string < t_icccolour > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "a colour specification cannot be empty");
            string_value < t_icccolour > :: status (s_invalid); }
        else if (tidy_string < t_icccolour > :: good ())
        {   ::std::string icc (tidy_string < t_icccolour > :: get_string ());
            ::std::string ought ("icc-color(");
            if ((icc.length () < ought.length ()) || icc.substr (0, ought.length ()) != ought)
                nits.pick (nit_icc_colour, ed_svg_1_1, "4.2 Basic data types", es_error, ec_attribute, "a colour specification should be ", quote (ought), " ... values ... )");
            else if (icc.at (icc.length () - 1) != ')')
                nits.pick (nit_icc_colour, ed_svg_1_1, "4.2 Basic data types", es_error, ec_attribute, "a colour specification should be ", quote (ought), " ... values ... )");
            else return;
            tidy_string < t_icccolour > :: status (s_invalid); } } };

template < > struct type_master < t_keyspline > : type_exactly_n < t_keyspline, sz_commaspace, t_real, 4 >
{ using type_exactly_n < t_keyspline, sz_commaspace, t_real, 4 > :: type_exactly_n; };

template < > struct type_master < t_keysplines > : type_at_least_one < t_keysplines, sz_semicolon, t_keyspline >
{ using type_at_least_one < t_keysplines, sz_semicolon, t_keyspline > :: type_at_least_one; };

template < > struct type_master < t_keytimes > : type_at_least_one < t_keytimes, sz_semicolon, t_zero_to_one >
{   using type_at_least_one < t_keytimes, sz_semicolon, t_zero_to_one > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_time; } };

template < > struct type_master < t_line_height > : either_type_or_string < t_line_height, t_measure, t_real, sz_normal >
{ using either_type_or_string < t_line_height, t_measure, t_real, sz_normal > :: either_type_or_string; };

template < > struct type_master < t_origin > : tidy_string < t_origin >
{   using tidy_string < t_origin > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_origin > :: set_value (nits, v, s);
        if (tidy_string < t_origin > :: good ())
        {   ::std::string ss (tidy_string < t_origin > :: get_string ());
            if (compare_complain (nits, v, "default", ss)) return; }
        nits.pick (nit_origin, ed_svg_1_1, "19.2.14 The 'animateMotion' element", es_error, ec_attribute, "ORIGIN must be set to 'default'");
        tidy_string < t_origin > :: status (s_invalid); } };

template < > struct type_master < t_marker > : id_or_either_string < t_marker, t_hash_fn, sz_none, sz_inherit >
{   using id_or_either_string < t_marker, t_hash_fn, sz_none, sz_inherit > :: id_or_either_string;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_navigation > : id_or_either_string < t_navigation, t_hash_fn, sz_auto, sz_self >
{   using id_or_either_string < t_navigation, t_hash_fn, sz_auto, sz_self > :: id_or_either_string;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_opacity > : type_or_string < t_opacity, t_zero_to_one, sz_inherit >
{ using type_or_string < t_opacity, t_zero_to_one, sz_inherit > :: type_or_string; };

template < > struct type_master < t_panose1 > : type_exactly_n < t_panose1, sz_space, t_integer, 10 >
{ using type_exactly_n < t_panose1, sz_space, t_integer, 10 > :: type_exactly_n; };

template < > struct type_master < t_paint > : tidy_string < t_paint >
{   using tidy_string < t_paint > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_paint > :: set_value (nits, v, s);
        if (tidy_string < t_paint > :: empty ())
            nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "a paint specification should not be empty");
        else if (tidy_string < t_paint > :: good ())
            if (parse_paint (nits, v, tidy_string < t_paint > :: get_string ())) return;
        tidy_string < t_paint > :: status (s_invalid); } };

template < > struct type_master < t_repeatcount > : type_or_string < t_repeatcount, t_0_more, sz_indefinite >
{ using type_or_string < t_repeatcount, t_0_more, sz_indefinite > :: type_or_string; };

template < > struct type_master < t_preserveaspectratio10 > : type_one_or_both < t_preserveaspectratio10, t_svg_align, sz_space, t_meetslice >
{   using type_one_or_both < t_preserveaspectratio10, t_svg_align, sz_space, t_meetslice > :: type_one_or_both;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_preserveaspectratio12 > : type_or_string < t_preserveaspectratio12, t_preserveaspectratio10, sz_defer >
{ using type_or_string < t_preserveaspectratio12, t_preserveaspectratio10, sz_defer > :: type_or_string; };

template < > struct type_master < t_rotate_anim > : type_or_either_string < t_rotate_anim, t_angle, sz_auto, sz_autoreverse >
{ using type_or_either_string < t_rotate_anim, t_angle, sz_auto, sz_autoreverse > :: type_or_either_string; };

template < > struct type_master < t_setback_offset > : type_range < t_setback_offset, sz_commaspace, t_measure, 1, 4 >
{ using type_range < t_setback_offset, sz_commaspace, t_measure, 1, 4 > :: type_range; };

template < > struct type_master < t_shape_fn_circlesz > : type_must_be < t_shape_fn_circlesz, sz_circle >
{   using type_must_be < t_shape_fn_circlesz, sz_circle > :: type_must_be;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_circle > : type_function < t_shape_fn_circle, t_shape_fn_circlesz, t_text >
{   using type_function < t_shape_fn_circle, t_shape_fn_circlesz, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_ellipsesz > : type_must_be < t_shape_fn_ellipsesz, sz_ellipse >
{   using type_must_be < t_shape_fn_ellipsesz, sz_ellipse > :: type_must_be;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_ellipse > : type_function < t_shape_fn_ellipse, t_shape_fn_ellipsesz, t_text >
{   using type_function < t_shape_fn_ellipse, t_shape_fn_ellipsesz, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_polygonsz > : type_must_be < t_shape_fn_circle, sz_polygon >
{   using type_must_be < t_shape_fn_circle, sz_polygon > :: type_must_be;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn_polygon > : type_function < t_shape_fn_polygon, t_shape_fn_polygonsz, t_text >
{   using type_function < t_shape_fn_polygon, t_shape_fn_polygonsz, t_text > :: type_function;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_fn > : type_one_of_three < t_shape_fn, t_shape_fn_circle, t_shape_fn_ellipse, t_shape_fn_polygon >
{   using type_one_of_three < t_shape_fn, t_shape_fn_circle, t_shape_fn_ellipse, t_shape_fn_polygon > :: type_one_of_three;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_uri > : type_either_or < t_shape_uri, t_shape_fn, t_urifn >
{   using type_either_or < t_shape_uri, t_shape_fn, t_urifn > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_shape_none_uri > : type_or_string < t_shape_none_uri, t_shape_uri, sz_none >
{ using type_or_string < t_shape_none_uri, t_shape_uri, sz_none > :: type_or_string; };

template < > struct type_master < t_svg_baselineshift > : type_either_or < t_svg_baselineshift, t_baselineshift, t_measure >
{   using type_either_or < t_svg_baselineshift, t_baselineshift, t_measure > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_length; } };

template < > struct type_master < t_svg_clip > : type_or_either_string < t_svg_clip, t_svg_shape, sz_auto, sz_inherit >
{ using type_or_either_string < t_svg_clip, t_svg_shape, sz_auto, sz_inherit > :: type_or_either_string; };


template < > struct type_master < t_svg_fontstyle_ff > : public tidy_string < t_svg_fontstyle_ff >
{   using tidy_string < t_svg_fontstyle_ff > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font style requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontstyle_ff > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontstyle_ff > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontstyle_ff > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontstyle_ff > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                const ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontstyle, es_error, ec_type, "font style is effectively empty");
                else if (fs.size () > 2)
                    nits.pick (nit_fontstyle, es_error, ec_type, "too many font style keywords");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_fontnia > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontstyle, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font style can be 'all', or one or two of 'normal', 'italic', 'oblique'");
        tidy_string < t_svg_fontstyle_ff > :: status (s_invalid); } };

template < > struct type_master < t_svg_fontweights > : public tidy_string < t_svg_fontweights >
{   using tidy_string < t_svg_fontweights > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font weight requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontweights > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontweights > :: empty ())
                nits.pick (nit_fontweight, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontweights > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontweights > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                const ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontweight, es_error, ec_type, "font style is effectively empty");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontweight_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontweight, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font weight can be 'all', or one or more of 'normal', 'bold', and / or specific weights");
        tidy_string < t_svg_fontweights > :: status (s_invalid); } };

template < > struct type_master < t_svg_shapefn > : tidy_string < t_svg_shapefn >
{   using tidy_string < t_svg_shapefn > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_shapefn > :: set_value (nits, v, s);
        if (compare_complain (nits, v, "rect", tidy_string < t_svg_shapefn > :: get_string ())) return;
        nits.pick (nit_function, ed_svg_1_0, "", es_error, ec_type, "shape must be 'rect");
        tidy_string < t_svg_shapefn > :: status (s_invalid); } };

template < > struct type_master < t_svg_shape > : type_function < t_svg_shape, t_svg_shapefn, t_real >
{   using type_function < t_svg_shape, t_svg_shapefn, t_real > :: type_function;
    static e_animation_type animation_type () noexcept { return at_number; } };

template < > struct type_master < t_svg_host > : either_string < t_svg_host, sz_svg, sz_host >
{ using either_string < t_svg_host, sz_svg, sz_host > :: either_string; };

template < > struct type_master < t_svg_svg > : type_must_be < t_svg_svg, sz_svg >
{ using type_must_be < t_svg_svg, sz_svg > :: type_must_be; };

template < > struct type_master < t_svg_transform > : type_or_string < t_svg_transform, t_transform, sz_none >
{ using type_or_string < t_svg_transform, t_transform, sz_none > :: type_or_string; };


template < > struct type_master < t_svg_time > : type_master < t_real >
{   using type_master < t_real > :: type_master;
    static e_animation_type animation_type () noexcept { return at_time; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        ::std::string t (ss);
        if (ends_with_letters (v, ss, "ms") && (ss.length () > 2)) t = ss.substr (0, ss.length () - 2);
        else if (ends_with_letters (v, ss, "s") && (ss.length () > 1)) t = ss.substr (0, ss.length () - 1);
        if (t.find_first_not_of (REAL) != ::std::string::npos)
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " must be a number, optionally followed by 'ms' or 's'");
        else
        {   type_master < t_real > :: set_value (nits, v, t);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_svg_time_default > : type_or_string < t_svg_time_none, t_svg_time, sz_default >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_default > :: type_or_string; };

template < > struct type_master < t_svg_time_inherit > : type_or_string < t_svg_time_none, t_svg_time, sz_inherit >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_inherit > :: type_or_string; };

template < > struct type_master < t_svg_time_none > : type_or_string < t_svg_time_none, t_svg_time, sz_none >
{ using type_or_string < t_svg_time_none, t_svg_time, sz_none > :: type_or_string; };

template < > struct type_master < t_svg_values > : type_at_least_one < t_svg_values, sz_semicolon, t_real >
{ using type_at_least_one < t_svg_values, sz_semicolon, t_real > :: type_at_least_one; };

template < > struct type_master < t_vector_effect_2s > : type_at_least_one < t_vector_effect_2s, sz_space, t_vector_effect_2 >
{ using type_at_least_one < t_vector_effect_2s, sz_space, t_vector_effect_2 > :: type_at_least_one; };

template < > struct type_master < t_vector_effect_20 > : type_many_then_maybe < t_vector_effect_20, t_vector_effect_2, sz_space, t_viewportscreen >
{   using type_many_then_maybe < t_vector_effect_20, t_vector_effect_2, sz_space, t_viewportscreen > :: type_many_then_maybe;
    static e_animation_type animation_type () noexcept { return at_list; } };

template < > struct type_master < t_svg_viewboxrect > : type_exactly_n < t_svg_viewboxrect, sz_commaspace, t_real, 4 >
{   using type_exactly_n < t_svg_viewboxrect, sz_commaspace, t_real, 4 > :: type_exactly_n;
    static e_animation_type animation_type () noexcept { return at_coordinate; } };

template < > struct type_master < t_svg_viewbox > : tidy_string < t_svg_viewbox >
{   using tidy_string < t_svg_viewbox > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        tidy_string < t_svg_viewbox > :: set_value (nits, v, ss);
        if (v.is_svg_12 () && compare_complain (nits, v, QNONE, ss))
            type_master < t_svg_viewbox > :: status (s_good);
        else
        {   type_master < t_svg_viewboxrect > vb;
            vb.set_value (nits, v, ss);
            if (vb.good ())
                if (vb.size () != 4)
                    nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX expects four numbers: x, y, width and height (or '", QNONE "')");
                else
                {   const double width = lexical < double > :: cast (vb.at (2));
                    const double height = lexical < double > :: cast (vb.at (3));
                    if ((width >= 0.0) && (height >= 0.0)) return;
                    if (width < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX width cannot be negative");
                    if (height < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, quote (ss), "a VIEWBOX height cannot be negative"); }
            else if (v.is_svg_12 ()) nits.pick (nit_viewbox, es_error, ec_type, quote (ss), ": '", QNONE "' or four numbers (x y width height) expected");
            else nits.pick (nit_viewbox, es_error, ec_type, quote (ss), ": four numbers (x y width height) expected");
            tidy_string < t_svg_viewbox > :: status (s_invalid); } } };

template < > struct type_master < t_transform > : tidy_string < t_transform >
{   using tidy_string < t_transform > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_transform; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_transform > :: set_value (nits, v, s);
        if (tidy_string < t_transform > :: empty ())
            nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_warning, ec_type, "a TRANSFORM value ought to transform");
        else if (tidy_string < t_transform > :: good ())
            if (parse_transform (nits, v, tidy_string < t_transform > :: get_string ())) return;
        tidy_string < t_transform > :: status (s_invalid); } };

template < > struct type_master < t_urange > : type_at_least_one < t_urange, sz_comma, t_text >
{   using type_at_least_one < t_urange, sz_comma, t_text > :: type_at_least_one;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_urifn > : type_function < t_urifn, t_urisz, t_url >
{   using type_function < t_urifn, t_urisz, t_url > :: type_function;
    static e_animation_type animation_type () noexcept { return at_url; } };

template < > struct type_master < t_urifn_ni > : id_or_either_string < t_urifn_ni, t_urifn, sz_none, sz_inherit >
{ using id_or_either_string < t_urifn_ni, t_urifn, sz_none, sz_inherit > :: id_or_either_string; };

template < > struct type_master < t_urisz > : type_must_be < t_urisz, sz_url >
{   using type_must_be < t_urisz, sz_url > :: type_must_be;
    static e_animation_type animation_type () noexcept { return at_other; } };

template < > struct type_master < t_vertical_align > : type_either_or < t_vertical_align, t_vertical_align_enum, t_measure >
{   using type_either_or < t_vertical_align, t_vertical_align_enum, t_measure > :: type_either_or;
    static e_animation_type animation_type () noexcept { return at_other; } };
