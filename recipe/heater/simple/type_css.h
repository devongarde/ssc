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
#include "simple/type_numeric.h"
#include "base/type_master.h"

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e);

template < > struct type_master < t_css > : public tidy_string < t_css >
{   using tidy_string < t_css > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css > :: set_value (nits, v, s);
        if (tidy_string < t_css > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic STYLE"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (! tidy_string < t_css > :: good ()) return true;
        return ! process_css (nits, v, tidy_string < t_css > :: get_string (), e); } };

template < > struct type_master < t_css_all > : public tidy_string < t_css_all >
{   using tidy_string < t_css_all > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_all > :: set_value (nits, v, s);
        if (tidy_string < t_css_all > :: good ())
            if (! compare_no_case (tidy_string < t_css_all > :: get_string (), "all"))
            {   if (v.css_version () == css_2_0)
                    nits.pick (nit_unrecognised_value, es_comment, ec_type, quote (s), ": is not 'all'"); }
            else if (v.css_version () != css_2_0)
                nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'all' requires CSS 2.0 (only)");
            else return;
        tidy_string < t_css_all > :: status (s_invalid); } };

template < > struct type_master < t_css_anim_base > : public tidy_string < t_css_anim_base >
{   using tidy_string < t_css_anim_base > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_anim_base > :: set_value (nits, v, s);
        if (tidy_string < t_css_anim_base > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "missing @keyframes name"); }
    bool invalid_access (nitpick& nits, const html_version& , sstr_t* s)
    {   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
        if (! tidy_string < t_css_anim_base > :: good ()) return true;
        const ::std::string& x = tidy_string < t_css_anim_base > :: get_string ();
        if (s -> find (x) != s -> cend ()) return false;
        nits.pick (nit_css_keyframes, es_error, ec_css, "@keyframes ", quote (x), " is referenced but not defined");
        return true; } };

template < > struct type_master < t_css_bespoke > : public tidy_string < t_css_bespoke >
{   using tidy_string < t_css_bespoke > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_bespoke > :: set_value (nits, v, s);
        tidy_string < t_css_bespoke > :: status (s_good); }
    void verify_attribute (nitpick& nits, const html_version& , const elem& , element* , const ::std::string& attnam)
    {   nits.pick (nit_css_bespoke, es_warning, ec_type, "bespoke properties, such as ", attnam, ", are processed neither by " PROG " nor all browsers"); } };

template < > struct type_master < t_css_counter_style_name > : public tidy_string < t_css_counter_style_name >
{   using tidy_string < t_css_counter_style_name > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_counter_style_name > :: set_value (nits, v, s);
        if (tidy_string < t_css_counter_style_name > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "missing @counter-style name"); }
    bool invalid_access (nitpick& nits, const html_version& , sstr_t* s)
    {   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
        if (! tidy_string < t_css_counter_style_name > :: good ()) return true;
        const ::std::string& x = tidy_string < t_css_counter_style_name > :: get_string ();
        if (s -> find (x) != s -> cend ()) return false;
        nits.pick (nit_css_keyframes, es_error, ec_css, "@counter-style ", quote (x), " is referenced but not defined");
        return true; } };

template < > struct type_master < t_css_font > : tidy_string < t_css_font >
{   using tidy_string < t_css_font > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& sss)
    {   tidy_string < t_css_font > :: set_value (nits, v, sss);
        if (tidy_string < t_css_font> :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font specification cannot be empty");
        else if (tidy_string < t_css_font> :: good ())
        {   nitpick gnats;
            ::std::string gs (tidy_string < t_css_font > :: get_string ());
            if (test_value < t_font_enum > (gnats, v, gs))
            {   nits.merge (gnats);
                return; }
            vstr_t ss (split_by_space (gs));
            PRESUME (! ss.empty (), __FILE__, __LINE__);
            bool res = true;
            typedef enum { fs_style, fs_variant, fs_weight, fs_size, fs_family, fs_done } font_state;
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
                        if (test_value < t_css_font_style_a > (knits, v, s))
                        {   state = fs_variant; break; }
                        FALLTHROUGH;
                    case fs_variant :
                        if (test_value < t_svg_fontvariant > (knits, v, s))
                        {   state = fs_weight; break; }
                        FALLTHROUGH;
                    case fs_weight :
                        if (test_value < t_css_font_weights > (knits, v, s))
                        {   state = fs_size; break; }
                        FALLTHROUGH;
                    case fs_size :
                        pos = s.find ('/');
                        if (pos == ::std::string::npos)
                        {   if (test_value < t_fontsize > (knits, v, s))
                            {   state = fs_family; break; }
                            if (v.has_css () && test_value < t_css_font_size_4 > (knits, v, s))
                            {   state = fs_family; break; } }
                        else if (test_value < t_fontsize > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        else if (v.has_css () && 
                                 test_value < t_css_font_size_4 > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        FALLTHROUGH;
                    case fs_family :
                        if (test_value < t_font_family > (knits, v, s))
                        {   if (! v.has_css ()) state = fs_done;
                            break; }
                        if (v.has_css () && test_value < t_css_generic_family > (knits, v, s))
                            break;
                        FALLTHROUGH;
                    default :
                        nits.pick (nit_font_enum, es_error, ec_type, quote (s), " is not a known CSS FONT property");
                        res = false; break; }
                if (! res) break; }
            if (res) return; }
        tidy_string < t_css_font > :: status (s_invalid); } };

template < > struct type_master < t_css_font_stretch > : public tidy_string < t_css_font_stretch >
{   using tidy_string < t_css_font_stretch > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_stretch > :: set_value (nits, v, s);
        if (tidy_string < t_css_font_stretch > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "font-stretch cannot be empty");
        else if (tidy_string < t_css_font_stretch > :: good ())
        {   ::std::string n (tidy_string < t_css_font_stretch > :: get_string ());
            nitpick nuts;
            if (context.css_font () >= 4)
                if (test_value < t_percent > (nuts, v, n))
                {   nits.merge (nuts);
                    return; }
            if (test_value < t_svg_fontstretch > (nits, v, n)) return;
            nits.merge (nuts); }
        tidy_string < t_css_font_stretch > :: status (s_invalid); } };

template < > struct type_master < t_css_font_variant > : public tidy_string < t_css_font_variant >
{   using tidy_string < t_css_font_variant > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_variant > :: set_value (nits, v, s);
        if (tidy_string < t_css_font_variant > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font variant cannot be empty");
        else if (tidy_string < t_css_font_variant > :: good ())
        {   ::std::string n (tidy_string < t_css_font_variant > :: get_string ());
            if (context.css_font () >= 4)
            {   if (test_value < t_css_font_variant_4 > (nits, v, n)) return; }
            if (context.css_font () == 3)
            {   if (test_value < t_font_variant_2 > (nits, v, n)) return; }
            else if (test_value < t_svg_fontvariant > (nits, v, n)) return; }
        tidy_string < t_css_font_variant > :: status (s_invalid); } };

template < > struct type_master < t_css_font_weights > : public tidy_string < t_css_font_weights >
{   using tidy_string < t_css_font_weights > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_weights > :: set_value (nits, v, s);
        if (tidy_string < t_css_font_weights > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font weight cannot be empty");
        else if (tidy_string < t_css_font_weights > :: good ())
        {   ::std::string n (tidy_string < t_css_font_weights > :: get_string ());
            if (context.css_font () >= 4)
            {   if (test_value < t_css_font_weight_4 > (nits, v, n)) return; }
            else if (test_value < t_css_font_weight > (nits, v, n)) return; }
        tidy_string < t_css_font_weights > :: status (s_invalid); } };

template < > struct type_master < t_css_frame > : public tidy_string < t_css_frame >
{   using tidy_string < t_css_frame > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_frame > :: set_value (nits, v, s);
        if (tidy_string < t_css_frame > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a frame name cannot be empty");
        else if (tidy_string < t_css_frame > :: good ())
        {   ::std::string n (tidy_string < t_css_frame > :: get_string ());
            if (n.at (0) != '_') return;
            if (compare_no_case (n, "_parent") || compare_no_case (n, "_root")) return;
            nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "to quote, a frame name 'MUST NOT start with the underscore \"_\" character'"); }
        tidy_string < t_css_frame > :: status (s_invalid); } };

template < > struct type_master < t_css_id > : public tidy_string < t_css_id >
{   using tidy_string < t_css_id > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_id > :: set_value (nits, v, s);
        if (tidy_string < t_css_id > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a id cannot be empty");
        else if (tidy_string < t_css_id > :: good ())
        {   ::std::string n (tidy_string < t_css_id > :: get_string ());
            if (n.at (0) == '#') return;
            nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "An id selector is expected, which starts with '#'"); }
        tidy_string < t_css_id > :: status (s_invalid); } };

template < > struct type_master < t_css_inherit > : public tidy_string < t_css_inherit >
{   using tidy_string < t_css_inherit > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_inherit > :: set_value (nits, v, s);
        if (tidy_string < t_css_inherit > :: good ())
            if (! compare_no_case (tidy_string < t_css_inherit > :: get_string (), "inherit"))
            {   if (v.css_version () >= css_2_0)
                    nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), ": is not 'inherit'"); }
            else if (v.css_version () < css_2_0)
                nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'inherit' requires CSS 2.0 or later");
            else return;
        tidy_string < t_css_inherit > :: status (s_invalid); } };

template < > struct type_master < t_css_nth > : public tidy_string < t_css_nth >
{   using tidy_string < t_css_nth > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_nth > :: set_value (nits, v, s);
        ::std::string ss (tidy_string < t_css_nth > :: get_string ());
        if (tidy_string < t_css_nth > :: empty () || ss.empty ())
            nits.pick (nit_empty, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, "pseudo class children specification cannot be empty");
        else if (tidy_string < t_css_nth > :: good ())
            if (ss.find_first_not_of (DENARY "+-nN ") != ::std::string::npos)
                nits.pick (nit_css_syntax, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, quote (ss), " contains invalid characters");
            else return; // maybe do more checking!
        tidy_string < t_css_nth > :: status (s_invalid); } };

template < > struct type_master < t_css_palette > : public tidy_string < t_css_palette >
{   using tidy_string < t_css_palette > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_palette > :: set_value (nits, v, s);
        if (tidy_string < t_css_palette > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "missing @font-palette name"); }
    bool invalid_access (nitpick& nits, const html_version& , sstr_t* s)
    {   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
        if (! tidy_string < t_css_palette > :: good ()) return true;
        const ::std::string& x = tidy_string < t_css_palette > :: get_string ();
        if (s -> find (x) != s -> cend ()) return false;
        nits.pick (nit_css_keyframes, es_error, ec_css, "@font-palette ", quote (x), " is referenced but not defined");
        return true; } };

template < > struct type_master < t_css_unicode_from_to > : public tidy_string < t_css_unicode_from_to >
{   using tidy_string < t_css_unicode_from_to > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_unicode_from_to > :: set_value (nits, v, s);
        if (tidy_string < t_css_unicode_from_to > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
        else if (tidy_string < t_css_unicode_from_to > :: good ())
        {   ::std::string n (tidy_string < t_css_unicode_from_to > :: get_string ());
            const ::std::size_t len = n.length ();
            if ((len <= 2) || (n.at (1) != '+') || ((n.at (0) != 'U') && (n.at (0) != 'u')))
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": must start with 'U+'");
            else if (len > 18)
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": too big");
            else if (n.substr (2).find_first_not_of (HEX "-") != ::std::string::npos) 
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": not hexadecimal");
            else
            {   const ::std::string::size_type minus = n.find_first_of ("-");
                if ((minus < 3) || (minus >= len-1)) 
                    nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": is not a pair of hexadecimal values"); 
                else if (n.substr (minus+1).find ('-') != ::std::string::npos)
                    nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": bad hexadecimal range"); 
                else return; } }
        tidy_string < t_css_unicode_from_to > :: status (s_invalid); } };

template < > struct type_master < t_css_unicode_wildcard > : public tidy_string < t_css_unicode_wildcard >
{   using tidy_string < t_css_unicode_wildcard > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_unicode_wildcard > :: set_value (nits, v, s);
        if (tidy_string < t_css_unicode_wildcard > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
        else if (tidy_string < t_css_unicode_wildcard > :: good ())
        {   ::std::string n (tidy_string < t_css_unicode_wildcard > :: get_string ());
            const ::std::size_t len = n.length ();
            if ((len <= 2) || (n.at (1) != '+') || ((n.at (0) != 'U') && (n.at (0) != 'u')))
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": must start with 'U+'");
            else if (n.substr (2).find_first_not_of (HEX "?") != ::std::string::npos)
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": not hexadecimal with wildcards");
            else if (len > 10)
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (n), ": too big");
            else return; }
        tidy_string < t_css_unicode_wildcard > :: status (s_invalid); } };
