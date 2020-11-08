/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
        if (::boost::to_lower_copy (ss) == "auto")
            type_master < t_real > :: status (s_good);
        else
        {   float max = 360.0; ::std::string::size_type len = ss.length ();
            bool units = false;
            if (ends_with_letters (ss, "grad")) { max = 400.0; len -= 4; units = true; }
            else if (ends_with_letters (ss, "rad")) { max = static_cast < float > (3.141592653589*2); len -= 3; units = true; }
            else if (ends_with_letters (ss, "deg")) { len -= 3; units = true; }
            if (ss.substr (0, len).find_first_not_of (DECIMAL) != ::std::string::npos)
                nits.pick (nit_angle, es_error, ec_type, quote (s), " contains unexpected characters (units are 'deg', 'grad', or 'rad')");
            else
            if (units && (v.svg () < sv_1_1))
                nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, "angular units require SVG 1.1 or better.");
            else
            {   type_master < t_real > :: set_value (nits, v, s);
                if (good ())
                    if ((value_ >= max) || (value_ <= (-1 * max)))
                        nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " should be less that ", ::boost::lexical_cast < ::std::string > (max));
                    else return; }
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_angle_i > : type_or_string < t_angle_i, t_angle, sz_inherit > { };
template < > struct type_master < t_angle_ai > : type_or_either_string < t_angle_i, t_angle, sz_auto, sz_inherit > { };

template < > struct type_master < t_beginvaluelist > : tidy_string < t_beginvaluelist >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_beginvaluelist > :: set_value (nits, v, s);
        bool good = true;
        if (tidy_string < t_beginvaluelist > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
        else if (tidy_string < t_beginvaluelist > :: good ())
        {   vstr_t ve (split_by_charset (tidy_string < t_beginvaluelist > :: get_string (), ";"));
            if (ve.empty ())
                nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
            else for (auto sss : ve)
                if (! test_animation_timing (nits, v, sss, true)) good = false;
            if (good) return; }
        tidy_string < t_beginvaluelist > :: status (s_invalid); } };

template < > struct type_master < t_d > : tidy_string < t_d >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_d > :: set_value (nits, v, s);
        if (tidy_string < t_d > :: empty ())
            nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a D attribute cannot be empty");
        else if (tidy_string < t_d > :: good ())
            if (parse_d (nits, v, tidy_string < t_d > :: get_string ())) return;
        tidy_string < t_d > :: status (s_invalid); } };

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

template < > struct type_master < t_frequency > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (! ends_with_letters (ss, "kHz") && ! ends_with_letters (ss, "Hz"))
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

template < > struct type_master < t_origin > : tidy_string < t_origin >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_origin > :: set_value (nits, v, s);
        if (tidy_string < t_origin > :: good ())
        {   ::std::string ss (tidy_string < t_origin > :: get_string ());
            if (compare_no_case (ss, "default")) return; }
        nits.pick (nit_origin, ed_svg_1_1, "19.2.14 The 'animateMotion' element", es_error, ec_attribute, "ORIGIN must be set to 'default'");
        tidy_string < t_origin > :: status (s_invalid); } };

template < > struct type_master < t_paint > : tidy_string < t_paint >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_paint > :: set_value (nits, v, s);
        if (tidy_string < t_paint > :: empty ())
            nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "a paint specification should not be empty");
        else if (tidy_string < t_paint > :: good ())
            if (parse_paint (nits, v, tidy_string < t_paint > :: get_string ())) return;
        tidy_string < t_paint > :: status (s_invalid); } };

template < > struct type_master < t_svg_time > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (v.svg () < sv_1_1)
            nits.pick (nit_bad_frequency, es_error, ec_type, "time requires SVG 1.1 or better.");
        else if ((ss.find_first_not_of (REAL) != ::std::string::npos) && (! ends_with_letters (ss, "ms")) && (! ends_with_letters (ss, "s")))
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " must be a number, optionally followed by 'ms' or 's'");
        else
        {   type_master < t_real > :: set_value (nits, v, s);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_svg_snapshottime > : type_or_string < t_svg_snapshottime, t_svg_time, sz_none > { };

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
                if (compare_no_case (ss, "all")) return;
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
                if (compare_no_case (ss, "all")) return;
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
                if (compare_no_case (ss, "all")) return;
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

template < > struct type_master < t_svg_transform > : type_or_string < t_svg_transform, t_transform, sz_none > { };

template < > struct type_master < t_svg_values > : tidy_string < t_svg_values >
{   vdbl_t value_;
    void swap (type_master < t_svg_values >& t)
    {   value_.swap (t.value_);
        tidy_string < t_svg_values >::swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_values > :: set_value (nits, v, s);
        if (tidy_string < t_svg_values > :: good ())
        {   vstr_t ss (split_by_charset (tidy_string < t_svg_values > :: get_string (), ";"));
            if (ss.size () > 0)
            {   bool ok = true;
                for (auto sss : ss)
                    if (! test_value < t_real > (nits, v, sss))
                        ok = false;
                if (ok) return; } }
        nits.pick (nit_svg_values, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "a semi-colon separated series of numbers expected");
        tidy_string < t_svg_values > :: status (s_invalid); }
    void reset ()
    {   value_.clear ();
        tidy_string < t_svg_values > :: reset (); }
    static ::std::string default_value () { return ""; }
    ::std::string get () const { return get_string (); } };

template < > struct type_master < t_rotate_anim > : type_or_either_string < t_rotate_anim, t_real, sz_auto, sz_autoreverse > { };
