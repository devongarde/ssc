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

// t_css_font

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e) noexcept;

template < > struct type_master < t_css > : public tidy_string < t_css >
{   using tidy_string < t_css > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css > :: set_value (nits, v, s);
        if (tidy_string < t_css > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic style"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e) noexcept
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
                        if (test_value < t_css_font_style > (knits, v, s))
                        {   state = fs_variant; break; }
                        FALLTHROUGH;
                    case fs_variant :
                        if (test_value < t_svg_fontvariant > (knits, v, s))
                        {   state = fs_weight; break; }
                        FALLTHROUGH;
                    case fs_weight :
                        if (test_value < t_css_font_weight > (knits, v, s))
                        {   state = fs_size; break; }
                        FALLTHROUGH;
                    case fs_size :
                        pos = s.find ('/');
                        if (pos == ::std::string::npos)
                        {   if (test_value < t_fontsize > (knits, v, s))
                            {   state = fs_family; break; }
                            if (v.has_css () && test_value < t_css_font_size > (knits, v, s))
                            {   state = fs_family; break; } }
                        else if (test_value < t_fontsize > (knits, v, s.substr (0, pos)) &&
                                 test_value < t_measure > (knits, v, s.substr (pos)))
                        {   state = fs_family; break; }
                        else if (v.has_css () && 
                                 test_value < t_css_font_size > (knits, v, s.substr (0, pos)) &&
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
