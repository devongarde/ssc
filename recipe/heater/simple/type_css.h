/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
e_status set_css_content_name_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
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
e_status set_fn_calc_args_value (nitpick& nits, const html_version& v, const ::std::string& ss);
e_status set_fn_trans_args_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_fn_type_args_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_region_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_stn_value (nitpick& nits, const html_version& v, const vstr_t& vs, element* box);
e_status set_vtn_value (nitpick& nits, const html_version& v, const vstr_t& vs, element* box);
e_status test_css_anchor (nitpick& nits, const e_status st, const html_version& v, const ::std::string& ss);
e_status test_css_template_set (nitpick& nits, const e_status st, arguments* a, const vstr_t& val);
e_status test_region_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status test_route_name (nitpick& nits, const e_status st, const ::std::string& n, arguments* a);
void validate_anchor_idref (nitpick& nits, type_master < t_css_anchor_idref >& cai, arguments& args, const ::std::string& s);  // typed_property.cpp
        
template < > struct type_master < t_css > : public tidy_string < t_css >
{   using tidy_string < t_css > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css > :: set_value (nits, v, s);
        if (tidy_string < t_css > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic STYLE"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (! tidy_string < t_css > :: good ()) return true;
        return ! process_css (nits, v, tidy_string < t_css > :: get_string (), e); } };

template < > struct type_master < t_css_anchor_id > : public tidy_string < t_css_anchor_id >
{   using tidy_string < t_css_anchor_id > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_anchor_id > :: set_value (nits, v, trim_the_lot_off (s));
        tidy_string < t_css_anchor_id > :: status (test_css_anchor (nits, tidy_string < t_css_anchor_id > :: status (), v, s)); } };

template < > struct type_master < t_css_anchor_idref > : public tidy_string < t_css_anchor_idref >
{   using tidy_string < t_css_anchor_idref > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_anchor_idref > :: set_value (nits, v, trim_the_lot_off (s));
        tidy_string < t_css_anchor_idref > :: status (test_css_anchor (nits, tidy_string < t_css_anchor_idref > :: status (), v, s)); }
    void argue (nitpick& nits, arguments* a)
    {   if ((a != nullptr) && tidy_string < t_css_anchor_idref > :: good ())
            validate_anchor_idref (nits, *this, *a, tidy_string < t_css_anchor_idref > :: get_string ()); } };

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
    {   nits.pick (nit_css_bespoke, es_comment, ec_type, "bespoke properties, such as ", attnam, ", are processed neither by " PROG " nor many browsers"); } };

template < > struct type_master < t_css_content_name > : public tidy_string < t_css_content_name >
{   using tidy_string < t_css_content_name > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_content_name > :: set_value (nits, v, s);
        if (context.css_version () < 3)
        {   nits.pick (nit_css_version, es_error, ec_type, "CSS Generated Content required");
            status (s_invalid); }
        else if (tidy_string < t_css_content_name > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic name, that"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (tidy_string < t_css_content_name > :: good ())
            tidy_string < t_css_content_name > :: status (set_css_content_name_value (nits, v, tidy_string < t_css_content_name > :: get_string (), e));
        return false; } };

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
        nits.pick (nit_counter_style, es_error, ec_css, "@counter-style ", quote (x), " is referenced but not defined");
        return true; } };

template < > struct type_master < t_css_descriptor > : tidy_string < t_css_descriptor >
{   using tidy_string < t_css_descriptor > :: tidy_string;
    void set_value (nitpick& nits, const html_version& , const ::std::string& )
    {   nits.pick (nit_descriptor, es_error, ec_css, "invalid: descriptors can only be used with @statements");
        tidy_string < t_css_descriptor > :: status (s_invalid); } };

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

template < > struct type_master < t_css_font_weights > : public string_vector < t_css_font_weights, sz_space_char >
{   using string_vector < t_css_font_weights, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   string_vector < t_css_font_weights, sz_space_char > :: set_value (nits, v, ss);
        if (string_vector < t_css_font_weights, sz_space_char > :: good ())
            for (auto s : string_vector < t_css_font_weights, sz_space_char > :: value_)
                if (set_css_font_weights_value (nits, v, s) == s_invalid)
                    string_vector < t_css_font_weights, sz_space_char > :: status (s_invalid); } };

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

template < > struct type_master < t_css_stn > : public string_vector < t_css_stn, sz_space_char >
{   using string_vector < t_css_stn, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_stn, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_css_stn, sz_space_char > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "missing content"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (string_vector < t_css_stn, sz_space_char > :: good ())
            set_stn_value (nits, v, string_vector < t_css_stn, sz_space_char > :: get (), e);
        return true; } };

template < > struct type_master < t_css_template_set > : public string_vector < t_css_template_set, sz_space_char >
{   using string_vector < t_css_template_set, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_template_set, sz_space_char > :: set_value (nits, v, trim_the_lot_off (s)); }
    void argue (nitpick& nits, arguments* a)
    {   string_vector < t_css_template_set, sz_space_char > :: status (test_css_template_set (
            nits, string_vector < t_css_template_set, sz_space_char > :: status (), a, string_vector < t_css_template_set, sz_space_char > :: get ())); } };

template < > struct type_master < t_css_unicode_from_to > : public tidy_string < t_css_unicode_from_to >
{   using tidy_string < t_css_unicode_from_to > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_unicode_from_to > :: set_value (nits, v, s);
        tidy_string < t_css_unicode_from_to > :: status (set_css_unicode_from_to_value (nits, v, tidy_string < t_css_unicode_from_to > :: get_string ())); } };

template < > struct type_master < t_css_vtn > : public string_vector < t_css_vtn, sz_space_char >
{   using string_vector < t_css_vtn, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_css_vtn, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_css_vtn, sz_space_char > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "missing content"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (string_vector < t_css_vtn, sz_space_char > :: good ())
            set_vtn_value (nits, v, string_vector < t_css_vtn, sz_space_char > :: get (), e);
        return true; } };

template < > struct type_master < t_css_unicode_wildcard > : public tidy_string < t_css_unicode_wildcard >
{   using tidy_string < t_css_unicode_wildcard > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_unicode_wildcard > :: set_value (nits, v, s);
        tidy_string < t_css_unicode_wildcard > :: status (set_css_unicode_wildcard_value (nits, v, tidy_string < t_css_unicode_wildcard > :: get_string ())); } };

template < > struct type_master < t_css_fn_calc_args > : public tidy_string < t_css_fn_calc_args >
{   using tidy_string < t_css_fn_calc_args > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_fn_calc_args > :: set_value (nits, v, s);
        tidy_string < t_css_fn_calc_args > :: status (set_fn_calc_args_value (nits, v, tidy_string < t_css_fn_calc_args > :: get_string ())); } };

template < > struct type_master < t_css_fn_trans_args > : public tidy_string < t_css_fn_trans_args >
{   using tidy_string < t_css_fn_trans_args > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_fn_trans_args > :: set_value (nits, v, s);
        if ((v.css_version () <= css_2_2) && ! v.css_any_3_4_5_6 ())
        {   nits.pick (nit_css_version, es_error, ec_type, "CSS level 3 or better required");
            status (s_invalid); }
        else if (tidy_string < t_css_fn_trans_args > :: empty ())
            nits.pick (nit_empty, es_warning, ec_type, "rather a minimalistic transform"); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (tidy_string < t_css_fn_trans_args > :: good ())
            tidy_string < t_css_fn_trans_args > :: status (set_fn_trans_args_value (nits, v, tidy_string < t_css_fn_trans_args > :: get_string (), e));
        return false; } };

template < > struct type_master < t_css_fn_type_args > : public tidy_string < t_css_fn_type_args >
{   using tidy_string < t_css_fn_type_args > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_fn_type_args > :: set_value (nits, v, s);
        tidy_string < t_css_fn_type_args > :: status (set_fn_type_args_value (nits, v, tidy_string < t_css_fn_type_args > :: get_string ())); } };

template < > struct type_master < t_css_region_id > : public tidy_string < t_css_region_id >
{   using tidy_string < t_css_region_id > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_region_id > :: set_value (nits, v, s);
        if (! tidy_string < t_css_region_id > :: empty ()) return;
        nits.pick (nit_empty, es_error, ec_type, "missing region name");
        tidy_string < t_css_region_id > :: status (s_invalid); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (tidy_string < t_css_region_id > :: good ())
            if (set_region_value (nits, v, tidy_string < t_css_region_id > :: get (), e) == s_good)
                return false;
        return true; } };

template < > struct type_master < t_css_required_region > : public tidy_string < t_css_required_region >
{   using tidy_string < t_css_required_region > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_required_region > :: set_value (nits, v, s);
        if (! tidy_string < t_css_required_region > :: empty ()) return;
        nits.pick (nit_empty, es_error, ec_type, "missing region name");
        tidy_string < t_css_required_region > :: status (s_invalid); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   if (tidy_string < t_css_required_region > :: good ())
            if (test_region_value (nits, v, tidy_string < t_css_required_region > :: get (), e) == s_good)
                return false;
        return true; } };

template < > struct type_master < t_custom_id > : tidy_string < t_custom_id >
{   using tidy_string < t_custom_id > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_custom; }
    static bool is_colourful () { return true; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_custom_id > :: set_value (nits, v, s);
        const ::std::string& id = tidy_string < t_custom_id > :: get_string ();
        if (s.empty () || (id.size () < 3) || (id.substr (0, 2) != "--"))
        {   nits.pick (nit_css_syntax, es_error, ec_css, "CSS custom ids must start with '--'");
            tidy_string < t_custom_id > :: status (s_invalid); }
        else tidy_string < t_custom_id > :: status (s_good); } };

template < > struct type_master < t_css_route_name > : tidy_string < t_css_route_name >
{   using tidy_string < t_css_route_name > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_route_name > :: set_value (nits, v, s);
        const ::std::string& id = tidy_string < t_css_route_name > :: get_string ();
        if ((id.size () < 3) || (id.substr (0, 2) != "--"))
        {   nits.pick (nit_css_syntax, es_error, ec_css, "CSS route names must start with '--'");
            tidy_string < t_css_route_name > :: status (s_invalid); }
        else tidy_string < t_css_route_name > :: status (s_good); }
    void argue (nitpick& nits, arguments* a)
    {   tidy_string < t_css_route_name > :: status (test_route_name (nits, tidy_string < t_css_route_name > :: status (), tidy_string < t_css_route_name > :: get_string (), a)); } };

template < > struct type_master < t_css_track_name > : tidy_string < t_css_track_name >
{   using tidy_string < t_css_track_name > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_track_name > :: set_value (nits, v, s);
        const ::std::string& id = tidy_string < t_css_track_name > :: get_string ();
        const ::std::string::size_type sz = id.size ();
        if ((sz < 2) || (id.at (0) != '[') || (id.at (sz - 1) != ']'))
        {   nits.pick (nit_css_syntax, es_error, ec_css, "CSS track list names be enclosed in square brackets ('[' & ']')");
            tidy_string < t_css_track_name > :: status (s_invalid); }
        else tidy_string < t_css_track_name > :: status (s_good); } };

template < > struct type_master < t_custom_property > : tidy_string < t_custom_property >
{   using tidy_string < t_custom_property > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_custom; }
    static bool is_colourful () { return true; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_custom_property > :: set_value (nits, v, s);
        if (s.empty ()) tidy_string < t_custom_property > :: status (s_empty);
        else tidy_string < t_custom_property > :: status (s_good); } };
