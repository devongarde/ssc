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
bool parse_d (nitpick& nits, const html_version& v, const ::std::string& d);
bool parse_paint (nitpick& nits, const html_version& v, const ::std::string& d, bool recheck = false);
bool parse_transform (nitpick& nits, const html_version& v, const ::std::string& d);
bool test_animation_timing (nitpick& nits, const html_version& v, const ::std::string& d, const bool begin);

template < > struct type_master < t_angle > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_complain (nits, v, "auto", ss))
            type_master < t_real > :: status (s_good);
        else
        {   float max = 360.0; ::std::string::size_type len = ss.length ();
            bool units = false;
            if (len > 3)
            {   ::std::string sss (ss.substr (len - 3));
                ::std::string ssss (ss.substr (len - 4));
                if (compare_complain (nits, v, ssss, "grad")) { max = 400.0; len -= 4; units = true; }
                else if (v.is_svg_2 () && compare_complain (nits, v, ssss, "turn")) { max = 1.0; len -= 4; units = true; }
                else if (compare_complain (nits, v, sss, "rad")) { max = static_cast < float > (3.141592653589*2); len -= 3; units = true; }
                else if (compare_complain (nits, v, sss, "deg")) { len -= 3; units = true; } }
            if (ss.substr (0, len).find_first_not_of (DECIMAL) != ::std::string::npos)
                nits.pick (nit_angle, es_error, ec_type, quote (s), " contains unexpected characters (units are 'deg', 'grad', or 'rad')");
            else
            {   type_master < t_real > :: set_value (nits, v, s);
                if (good ())
                    if ((value_ >= max) || (value_ <= (-1 * max)))
                        nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " should be less that ", ::boost::lexical_cast < ::std::string > (max));
                    else return; }
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_audio_level > : type_or_string < t_audio_level, t_real, sz_inherit > { };
template < > struct type_master < t_angle_i > : type_or_string < t_angle_i, t_angle, sz_inherit > { };
template < > struct type_master < t_angle_a > : type_or_string < t_angle_a, t_angle, sz_auto > { };
template < > struct type_master < t_angle_ai > : type_or_either_string < t_angle_ai, t_angle, sz_auto, sz_inherit > { };
template < > struct type_master < t_beginvalues > : type_at_least_one < t_beginvalues, sz_semicolon, t_beginvalue > { };
template < > struct type_master < t_beginvaluelist > : type_or_string < t_beginvaluelist, t_beginvalues, sz_indefinite > { };

template < > struct type_master < t_svg_shapefn > : tidy_string < t_svg_shapefn >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_shapefn > :: set_value (nits, v, s);
        if (compare_complain (nits, v, "rect", tidy_string < t_svg_shapefn > :: get_string ())) return;
        nits.pick (nit_function, ed_svg_1_0, "", es_error, ec_type, "shape must be 'rect");
        tidy_string < t_svg_shapefn > :: status (s_invalid); } };

template < > struct type_master < t_svg_shape > : type_function < t_svg_shape, t_svg_shapefn, t_real > { };
template < > struct type_master < t_clip > : type_or_either_string < t_clip, t_svg_shape, sz_auto, sz_inherit > { };
template < > struct type_master < t_urisz > : type_must_be < t_urisz, sz_url > { };
template < > struct type_master < t_hash_ref > : string_then_type < t_hash_ref, t_idref, sz_hash > { };
template < > struct type_master < t_hash_fn > : type_function < t_hash_fn, t_urisz, t_hash_ref > { };
template < > struct type_master < t_urifn > : type_function < t_urifn, t_urisz, t_url > { };
template < > struct type_master < t_clip_path_rule > : type_or_either_string < t_clip_path_rule, t_urifn, sz_none, sz_inherit > { };
template < > struct type_master < t_cursor_f > : type_either_or < t_cursor_f, t_cursor, t_urifn > { };

template < > struct type_master < t_d > : tidy_string < t_d >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_d > :: set_value (nits, v, s);
        if (tidy_string < t_d > :: empty ())
            nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a D attribute cannot be empty");
        else if (tidy_string < t_d > :: good ())
            if (parse_d (nits, v, tidy_string < t_d > :: get_string ())) return;
        tidy_string < t_d > :: status (s_invalid); } };

template < > struct type_master < t_dashes > : type_or_either_string < t_dashes, t_measures, sz_none, sz_inherit > { };

template < > struct type_master < t_endvaluelist > : tidy_string < t_endvaluelist >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_fillopacity > : tidy_string < t_fillopacity >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fillopacity > :: set_value (nits, v, s);
        if (tidy_string < t_fillopacity> :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "an opacity is expected");
        else if (tidy_string < t_fillopacity> :: good ())
        {   const ::std::string ss (tidy_string < t_fillopacity > :: get_string ());
            if (compare_complain (nits, v, sz_inherit :: sz (), ss)) return;
            nitpick nuts;
            if (test_value < t_zero_to_one > (nuts, v, ss)) return;
            if (v.is_svg_2 () && (test_value < t_percent > (nuts, v, ss))) return;
            nits.merge (nuts); }
        tidy_string < t_fillopacity > :: status (s_invalid); } };

template < > struct type_master < t_frequency > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (! ends_with_letters (v, ss, "kHz") && ! ends_with_letters (v, ss, "Hz"))
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " contains unexpected characters (units are 'kHz' or 'Hz')");
        else if (v.svg () < sv_1_1)
            nits.pick (nit_bad_frequency, es_error, ec_type, "frequencies require SVG 1.1 or better.");
        else
        {   type_master < t_real > :: set_value (nits, v, s);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_icccolour > : tidy_string < t_icccolour >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_keyspline > : type_exactly_n < t_keyspline, sz_commaspace, t_real, 4 > { };
template < > struct type_master < t_keysplines > : type_at_least_one < t_keysplines, sz_semicolon, t_keyspline > { };
template < > struct type_master < t_keytimes > : type_at_least_one < t_keytimes, sz_semicolon, t_zero_to_one > { };

template < > struct type_master < t_line_height > : either_type_or_string < t_line_height, t_measure, t_real, sz_normal > { };

template < > struct type_master < t_origin > : tidy_string < t_origin >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_origin > :: set_value (nits, v, s);
        if (tidy_string < t_origin > :: good ())
        {   ::std::string ss (tidy_string < t_origin > :: get_string ());
            if (compare_complain (nits, v, "default", ss)) return; }
        nits.pick (nit_origin, ed_svg_1_1, "19.2.14 The 'animateMotion' element", es_error, ec_attribute, "ORIGIN must be set to 'default'");
        tidy_string < t_origin > :: status (s_invalid); } };

template < > struct type_master < t_marker > : id_or_either_string < t_marker, t_hash_fn, sz_none, sz_inherit > { };
template < > struct type_master < t_navigation > : id_or_either_string < t_navigation, t_hash_fn, sz_auto, sz_self > { };
template < > struct type_master < t_opacity > : type_or_string < t_opacity, t_zero_to_one, sz_inherit > { };
template < > struct type_master < t_panose1 > : type_exactly_n < t_panose1, sz_space, t_integer, 10 > { };

template < > struct type_master < t_paint > : tidy_string < t_paint >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_paint > :: set_value (nits, v, s);
        if (tidy_string < t_paint > :: empty ())
            nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "a paint specification should not be empty");
        else if (tidy_string < t_paint > :: good ())
            if (parse_paint (nits, v, tidy_string < t_paint > :: get_string ())) return;
        tidy_string < t_paint > :: status (s_invalid); } };

template < > struct type_master < t_repeatcount > : type_or_string < t_repeatcount, t_0_more, sz_indefinite > { };
template < > struct type_master < t_dur_repeat > : type_or_string < t_dur_repeat, t_svg_duration, sz_indefinite > { };

template < > struct type_master < t_svg_time > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_svg_time_default > : type_or_string < t_svg_time_none, t_svg_time, sz_default > { };
template < > struct type_master < t_svg_time_inherit > : type_or_string < t_svg_time_none, t_svg_time, sz_inherit > { };
template < > struct type_master < t_svg_time_none > : type_or_string < t_svg_time_none, t_svg_time, sz_none > { };

template < > struct type_master < t_transform > : tidy_string < t_transform >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_transform > :: set_value (nits, v, s);
        if (tidy_string < t_transform > :: empty ())
            nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_warning, ec_type, "a TRANSFORM value ought to transform");
        else if (tidy_string < t_transform > :: good ())
            if (parse_transform (nits, v, tidy_string < t_transform > :: get_string ())) return;
        tidy_string < t_transform > :: status (s_invalid); } };

template < > struct type_master < t_fontsize > : type_or_string < t_fontsize, t_measure, sz_inherit > { };
template < > struct type_master < t_fontsizeadjust > : type_or_either_string < t_fontsizeadjust, t_real, sz_none, sz_inherit > { };

template < > struct type_master < t_svg_baselineshift > : tidy_string < t_svg_baselineshift >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (test_value < t_baselineshift > (nits, v, s) || test_value < t_measure > (nits, v, s))
            tidy_string < t_svg_baselineshift > :: status (s_good);
        else
            tidy_string < t_svg_baselineshift > :: status (s_invalid); } };

template < > struct type_master < t_svg_fontstyle_ff > : public tidy_string < t_svg_fontstyle_ff >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font style requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontstyle_ff > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontstyle_ff > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontstyle_ff > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontstyle_ff > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                ::std::string::size_type comma = ss.find (",");
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

template < > struct type_master < t_fontstretches > : public tidy_string < t_fontstretches >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font stretch requires SVG");
        else
        {   tidy_string < t_fontstretches > :: set_value (nits, v, s);
            if (tidy_string < t_fontstretches > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font stretch cannot be empty");
            else if (tidy_string < t_fontstretches > :: good ())
            {   ::std::string ss (tidy_string < t_fontstretches > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                ::std::string::size_type comma = ss.find (",");
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
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font variant requires SVG");
        else
        {   tidy_string < t_fontvariants > :: set_value (nits, v, s);
            if (tidy_string < t_fontvariants > :: empty ())
                nits.pick (nit_fontvariant, es_error, ec_type, "font variant cannot be empty");
            else if (tidy_string < t_fontvariants > :: good ())
            {   ::std::string ss (tidy_string < t_fontvariants > :: get_string ());
                ::std::string::size_type comma = ss.find (",");
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

template < > struct type_master < t_svg_fontweights > : public tidy_string < t_svg_fontweights >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font weight requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontweights > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontweights > :: empty ())
                nits.pick (nit_fontweight, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontweights > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontweights > :: get_string ());
                if (compare_complain (nits, v, "all", ss)) return;
                ::std::string::size_type comma = ss.find (",");
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

template < > struct type_master < t_glyphname > : public tidy_string < t_glyphname >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_glyphname > :: set_value (nits, v, s);
        if (tidy_string < t_glyphname > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "A glyph name cannot be empty"); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* pe, const ::std::string& )
    {   void store_glyph_name (nitpick& nits, const html_version& v, element* pe, const ::std::string name);
        ::std::string s (tidy_string < t_glyphname > :: get_string ());
        store_glyph_name (nits, v, pe, s); } };

template < > struct type_master < t_glyphnames > : public string_vector < t_glyphname, sz_comma >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_glyphname, sz_comma > :: set_value (nits, v, s); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* pe)
    {   bool check_glyph_names (nitpick& nits, const html_version& v, element* pe, const vstr_t& vs);
        DBG_ASSERT (pe != nullptr);
        if (! string_vector < t_glyphname, sz_comma > :: good ()) return false;
        return ! check_glyph_names (nits, v, pe, string_vector < t_glyphname, sz_comma > :: get ()); } };

template < > struct type_master < t_svg_transform > : type_or_string < t_svg_transform, t_transform, sz_none > { };
template < > struct type_master < t_svg_values > : type_at_least_one < t_svg_values, sz_semicolon, t_real > { };

template < > struct type_master < t_svg_viewboxrect > : type_exactly_n < t_svg_viewboxrect, sz_commaspace, t_real, 4 > { };

template < > struct type_master < t_svg_viewbox > : tidy_string < t_svg_viewbox >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        tidy_string < t_svg_viewbox > :: set_value (nits, v, ss);
        if (v.is_svg_12 () && compare_complain (nits, v, QNONE, ss))
            type_master < t_svg_viewbox > :: status (s_good);
        else
        {   type_master < t_svg_viewboxrect > vb;
            vb.set_value (nits, v, ss);
            if (vb.good ())
                if (vb.size () != 4)
                    nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, ss, "a VIEWBOX expects four numbers: x, y, width and height (or '", QNONE "')");
                else
                {   double width = lexical < double > :: cast (vb.at (2));
                    double height = lexical < double > :: cast (vb.at (3));
                    if ((width >= 0.0) && (height >= 0.0)) return;
                    if (width < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, ss, "a VIEWBOX width cannot be negative");
                    if (height < 0.0) nits.pick (nit_viewbox, ed_svg_1_0, "7.7 The viewBox attribute", es_error, ec_type, ss, "a VIEWBOX height cannot be negative"); }
            else nits.pick (nit_viewbox, es_error, ec_type, "'", QNONE "' or four numbers (x y width height) expected");
            tidy_string < t_svg_viewbox > :: status (s_invalid); } } };

template < > struct type_master < t_rotate_anim > : type_or_either_string < t_rotate_anim, t_angle, sz_auto, sz_autoreverse > { };
template < > struct type_master < t_dur > : type_or_either_string < t_dur, t_svg_time, sz_media, sz_indefinite > { };
template < > struct type_master < t_urange > : type_at_least_one < t_urange, sz_comma, t_text > { };
