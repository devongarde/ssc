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
e_status set_css_all_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_stretch_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_variant_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_font_weights_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_frame_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_id_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_inherit_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_nth_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_unicode_from_to_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_unicode_wildcard_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_fn_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);

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
            tidy_string < t_css_all > :: status (set_css_all_value (nits, v, tidy_string < t_css_all > :: get_string ())); } };

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
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font > :: set_value (nits, v, s);
        tidy_string < t_css_font > :: status (set_css_font_value (nits, v, tidy_string < t_css_font > :: get_string ())); } };

template < > struct type_master < t_css_font_stretch > : public tidy_string < t_css_font_stretch >
{   using tidy_string < t_css_font_stretch > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_stretch > :: set_value (nits, v, s);
        tidy_string < t_css_font_stretch > :: status (set_css_font_stretch_value (nits, v, tidy_string < t_css_font_stretch > :: get_string ())); } };

template < > struct type_master < t_css_font_variant > : public tidy_string < t_css_font_variant >
{   using tidy_string < t_css_font_variant > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_variant > :: set_value (nits, v, s);
        tidy_string < t_css_font_variant > :: status (set_css_font_variant_value (nits, v, tidy_string < t_css_font_variant > :: get_string ())); } };

template < > struct type_master < t_css_font_weights > : public tidy_string < t_css_font_weights >
{   using tidy_string < t_css_font_weights > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_font_weights > :: set_value (nits, v, s);
        tidy_string < t_css_font_weights > :: status (set_css_font_weights_value (nits, v, tidy_string < t_css_font_weights > :: get_string ())); } };

template < > struct type_master < t_css_frame > : public tidy_string < t_css_frame >
{   using tidy_string < t_css_frame > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_frame > :: set_value (nits, v, s);
        tidy_string < t_css_frame > :: status (set_css_frame_value (nits, v, tidy_string < t_css_frame > :: get_string ())); } };

template < > struct type_master < t_css_id > : public tidy_string < t_css_id >
{   using tidy_string < t_css_id > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_id > :: set_value (nits, v, s);
        tidy_string < t_css_id > :: status (set_css_id_value (nits, v, tidy_string < t_css_id > :: get_string ())); } };

template < > struct type_master < t_css_inherit > : public tidy_string < t_css_inherit >
{   using tidy_string < t_css_inherit > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_inherit > :: set_value (nits, v, s);
        tidy_string < t_css_inherit > :: status (set_css_inherit_value (nits, v, tidy_string < t_css_inherit > :: get_string ())); } };

template < > struct type_master < t_css_nth > : public tidy_string < t_css_nth >
{   using tidy_string < t_css_nth > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_nth > :: set_value (nits, v, s);
        tidy_string < t_css_nth > :: status (set_css_nth_value (nits, v, tidy_string < t_css_nth > :: get_string ())); } };

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
        tidy_string < t_css_unicode_from_to > :: status (set_css_unicode_from_to_value (nits, v, tidy_string < t_css_unicode_from_to > :: get_string ())); } };

template < > struct type_master < t_css_unicode_wildcard > : public tidy_string < t_css_unicode_wildcard >
{   using tidy_string < t_css_unicode_wildcard > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_unicode_wildcard > :: set_value (nits, v, s);
        tidy_string < t_css_unicode_wildcard > :: status (set_css_unicode_wildcard_value (nits, v, tidy_string < t_css_unicode_wildcard > :: get_string ())); } };

template < > struct type_master < t_fn > : public tidy_string < t_fn >
{   using tidy_string < t_fn > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fn > :: set_value (nits, v, s);
        if ((v.css_version () <= css_2_2) && ! v.css_any_3_4_5_6 ())
        {   nits.pick (nit_css_version, es_error, ec_type, "CSS level 3 or better required");
            status (s_invalid); }
        else if (tidy_string < t_fn > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic transform"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (tidy_string < t_fn > :: good ())
            tidy_string < t_fn > :: status (set_fn_value (nits, v, tidy_string < t_fn > :: get_string (), e));
        return false; } };
  