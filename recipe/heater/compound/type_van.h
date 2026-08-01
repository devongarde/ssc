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
#include "base/type_master.h"
#include "simple/type_autocomplete.h"
#include "microdata/microdata_itemtype.h"
#include "compound/compound.h"

bool invalid_context_menu_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe, element* box, const ::std::string& s);
e_status set_clear30_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_css_place_content (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_place_items (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_place_self (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_text_align_4_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_text_resizes_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_vertal_2_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_css_whitespace_2_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_custom_element_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_duration_media_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_enable_background_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_fallback (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_hidden_ex_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_inputaccept_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_lcrdss_value (nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_linethickness_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_margin_padding_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_mathalign_n_value (const e_status es, nitpick& nits, const html_version& v, const vstr_t& args);
e_status set_og_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_pseudonamedspace_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_ratio_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);
e_status set_roman_dsc_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box);
e_status set_sandboxen_value (const e_status es, nitpick& nits, const html_version& v, const vstr_t& args, element* box);
e_status set_shape3_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s);

template < > struct type_master < t_1_more_i > : type_or_string < t_1_more_i, t_1_more, sz_inherit >
{ using type_or_string < t_1_more_i, t_1_more, sz_inherit > :: type_or_string; };

template < > struct type_master < t_10_int > : type_exactly_n < t_10_int, sz_space_char, t_integer, 10 >
{ using type_exactly_n < t_10_int, sz_space_char, t_integer, 10 > :: type_exactly_n; };

template < > struct type_master < t_2string > : type_exactly_n < t_2string, sz_space_char, t_text, 2 >
{ using type_exactly_n < t_2string, sz_space_char, t_text, 2 > :: type_exactly_n; };

template < > struct type_master < t_4string > : type_exactly_n < t_4string, sz_space_char, t_text, 4 >
{ using type_exactly_n < t_4string, sz_space_char, t_text, 4 > :: type_exactly_n; };

template < > struct type_master < t_4string_ni > : any_type_or_any_string < t_4string_ni, t_4string, t_2string, t_css_inherit, sz_auto, sz_none, sz_match_parent >
{ using any_type_or_any_string < t_4string_ni, t_4string, t_2string, t_css_inherit, sz_auto, sz_none, sz_match_parent > :: any_type_or_any_string; };

template < > struct type_master < t_bandwidth > : type_or_string < t_bandwidth, t_real, sz_auto >
{ using type_or_string < t_bandwidth, t_real, sz_auto > :: type_or_string; };

template < > struct type_master < t_bools > : type_at_least_one < t_bools, sz_space_char, t_bool >
{ using type_at_least_one < t_bools, sz_space_char, t_bool > :: type_at_least_one; };

template < > struct type_master < t_braille_or_not > : type_either_or < t_braille_or_not, t_braille, t_no_braille >
{ using type_either_or < t_braille_or_not, t_braille, t_no_braille > :: type_either_or; };

template < > struct type_master < t_charspacing > : type_or_any_string < t_charspacing, t_measure, sz_loose, sz_medium, sz_tight >
{ using type_or_any_string < t_charspacing, t_measure, sz_loose, sz_medium, sz_tight > :: type_or_any_string; };

template < > struct type_master < t_clear30 > : tidy_string < t_clear30 >
{   using tidy_string < t_clear30 > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_clear30 > :: set_value (nits, v, s);
        tidy_string < t_clear30 > :: status (set_clear30_value (status (), nits, v, s, box ())); } };

template < > struct type_master < t_colour_a > : type_or_string < t_colour_a, t_colour, sz_auto >
{   static bool is_colourful () { return true; }
    using type_or_string < t_colour_a, t_colour, sz_auto > :: type_or_string; };

template < > struct type_master < t_colour_i > : type_or_string < t_colour_i, t_colour, sz_inherit >
{   static bool is_colourful () { return true; }
    using type_or_string < t_colour_i, t_colour, sz_inherit > :: type_or_string; };

template < > struct type_master < t_colour_ci > : type_or_string < t_colour_ci, t_colour_i, sz_currentcolour >
{   static bool is_colourful () { return true; }
    using type_or_string < t_colour_ci, t_colour_i, sz_currentcolour > :: type_or_string; };

template < > struct type_master < t_colour_cii > : type_or_either_string < t_colour_cii, t_colour_i, sz_currentcolour, sz_inherit >
{   static bool is_colourful () { return true; }
    using type_or_either_string < t_colour_cii, t_colour_i, sz_currentcolour, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_colour_ni > : type_or_any_string < t_colour_ni, t_colour, sz_none, sz_inherit, sz_currentcolour >
{   static bool is_colourful () { return true; }
    using type_or_any_string < t_colour_ni, t_colour, sz_none, sz_inherit, sz_currentcolour > :: type_or_any_string; };

template < > struct type_master < t_colour_trans > : either_type_or_string < t_colour_trans, t_css_colour, t_colour, sz_transparent >
{   static bool is_colourful () { return true; }
    using either_type_or_string < t_colour_trans, t_css_colour, t_colour, sz_transparent > :: either_type_or_string; };

template < > struct type_master < t_colour_trans_i > : type_or_string < t_colour_trans_i, t_colour_trans, sz_inherit >
{   static bool is_colourful () { return true; }
    using type_or_string < t_colour_trans_i, t_colour_trans, sz_inherit > :: type_or_string; };

template < > struct type_master < t_colour_ii > : type_or_either_string < t_colour_ii, t_colour, sz_invert, sz_inherit >
{   static bool is_colourful () { return true; }
    using type_or_either_string < t_colour_ii, t_colour, sz_invert, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_context_menu > : tidy_string < t_context_menu >
{   using tidy_string < t_context_menu > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_context_menu > :: set_value (nits, v, s);
        if (tidy_string < t_context_menu > :: empty ())
        {   nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, "CONTEXTMENU cannot be empty");
            tidy_string < t_context_menu > :: status (s_invalid); } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (! invalid_context_menu_id (nits, v, ids, pe, box (), tidy_string < t_context_menu > :: get_string ())) return false;
        string_value < t_context_menu > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_countries > : type_at_least_one < t_countries, sz_comma, t_country >
{ using type_at_least_one < t_countries, sz_comma, t_country > :: type_at_least_one; };

template < > struct type_master < t_custom_element > : tidy_string < t_custom_element >
{   using tidy_string < t_custom_element > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_custom_element > :: set_value (nits, v, s);
        tidy_string < t_custom_element > :: status (set_custom_element_value (status (), nits, v, tidy_string < t_custom_element > :: get_string ())); } };

template < > struct type_master < t_duration_media > : tidy_string < t_duration_media >
{   using tidy_string < t_duration_media > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_duration_media > :: set_value (nits, v, s);
        tidy_string < t_duration_media > :: status (set_duration_media_value (status (), nits, v, tidy_string < t_duration_media > :: get_string ())); } };

template < > struct type_master < t_enable_background > : tidy_string < t_enable_background >
{   using tidy_string < t_enable_background > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_enable_background > :: set_value (nits, v, s);
        tidy_string < t_enable_background > :: status (set_enable_background_value (status (), nits, v, tidy_string < t_enable_background > :: get_string ())); } };

template < > struct type_master < t_fallback > : tidy_string < t_fallback >
{   using tidy_string < t_fallback > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fallback > :: set_value (nits, v, s);
        tidy_string < t_fallback > :: status (set_fallback (status (), nits, v, tidy_string < t_fallback > :: get_string ())); } };

template < > struct type_master < t_font_families > : type_at_least_one < t_font_families, sz_comma, t_font_family >
{ using type_at_least_one < t_font_families, sz_comma, t_font_family > :: type_at_least_one; };

template < > struct type_master < t_css_font_families > : type_either_or < t_css_font_families, t_iiu, t_font_families >
{ using type_either_or < t_css_font_families, t_iiu, t_font_families > :: type_either_or; };

template < > struct type_master < t_hidden_ex > : public tidy_string < t_hidden_ex >
{   using tidy_string < t_hidden_ex > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_hidden_ex > :: set_value (nits, v, s);
        tidy_string < t_hidden_ex > :: status (set_hidden_ex_value (status (), nits, v, tidy_string < t_hidden_ex > :: get_string (), box ())); } };

template < > struct type_master < t_indentalign2 > : type_or_string < t_indentalign2, t_indentalign, sz_indentalign >
{ using type_or_string < t_indentalign2, t_indentalign, sz_indentalign > :: type_or_string; };

template < > struct type_master < t_indentshift2 > : type_or_string < t_indentshift2, t_measure, sz_indentshift >
{ using type_or_string < t_indentshift2, t_measure, sz_indentshift > :: type_or_string; };

template < > struct type_master < t_inputaccept > : tidy_string < t_inputaccept >
{   using tidy_string < t_inputaccept > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_inputaccept > :: set_value (nits, v, s);
        tidy_string < t_inputaccept > :: status (set_inputaccept_value (status (), nits, v, tidy_string < t_inputaccept > :: get_string (), box ())); } };

template < > struct type_master < t_lcraligns > : type_at_least_one < t_lcraligns, sz_space_char, t_lcralign >
{ using type_at_least_one < t_lcraligns, sz_space_char, t_lcralign > :: type_at_least_one; };

template < > struct type_master < t_lcrds > : type_at_least_one < t_lcrds, sz_space_char, t_lcrd >
{ using type_at_least_one < t_lcrds, sz_space_char, t_lcrd > :: type_at_least_one; };

template < > struct type_master < t_lcrdss > : string_vector < t_lcrdss, sz_space_char >
{   using string_vector < t_lcrdss, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_lcrdss, sz_space_char > :: set_value (nits, v, s);
        string_vector < t_lcrdss, sz_space_char > :: status (set_lcrdss_value (nits, v, string_vector < t_lcrdss, sz_space_char > :: get_string ())); } };

template < > struct type_master < t_length > : type_either_or < t_length, t_length_absolute, t_length_relative >
{ using type_either_or < t_length, t_length_absolute, t_length_relative > :: type_either_or; };

template < > struct type_master < t_linethickness > : tidy_string < t_linethickness >
{   using tidy_string < t_linethickness > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_linethickness > :: set_value (nits, v, s);
        tidy_string < t_linethickness > :: status (set_linethickness_value (status (), nits, v, tidy_string < t_linethickness > :: get_string ())); } };

template < > struct type_master < t_margin_padding > : tidy_string < t_margin_padding >
{   using tidy_string < t_margin_padding > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_margin_padding > :: set_value (nits, v, s);
        tidy_string < t_margin_padding > :: status (set_margin_padding_value (status (), nits, v, tidy_string < t_margin_padding > :: get_string ())); } };

template < > struct type_master < t_mathalign_n > : string_vector < t_mathalign_n, sz_space_char >
{   using string_vector < t_mathalign_n, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_mathalign_n, sz_space_char > :: set_value (nits, v, s);
        string_vector < t_mathalign_n, sz_space_char > :: status (set_mathalign_n_value (status (), nits, v, string_vector < t_mathalign_n, sz_space_char > :: get ())); } };

template < > struct type_master < t_mathaligns > : type_at_least_one < t_mathaligns, sz_space_char, t_mathalign >
{ using type_at_least_one < t_mathaligns, sz_space_char, t_mathalign > :: type_at_least_one; };

template < > struct type_master < t_mathnotations > : type_at_least_one < t_mathnotations, sz_space_char, t_mathnotation >
{ using type_at_least_one < t_mathnotations, sz_space_char, t_mathnotation > :: type_at_least_one; };

template < > struct type_master < t_mathspace > : type_either_or < t_mathspace, t_namedspace, t_hunit >
{ using type_either_or < t_mathspace, t_namedspace, t_hunit > :: type_either_or; };

template < > struct type_master < t_mathspaceauto > : type_or_string < t_mathspaceauto, t_mathspace, sz_auto >
{ using type_or_string < t_mathspaceauto, t_mathspace, sz_auto > :: type_or_string; };

template < > struct type_master < t_mathspacefit > : type_or_either_string < t_mathspacefit, t_mathspace, sz_auto, sz_fit >
{ using type_or_either_string < t_mathspacefit, t_mathspace, sz_auto, sz_fit > :: type_or_either_string; };

template < > struct type_master < t_mathspaceinfinity > : type_or_string < t_mathspaceinfinity, t_mathspace, sz_infinity >
{ using type_or_string < t_mathspaceinfinity, t_mathspace, sz_infinity > :: type_or_string; };

template < > struct type_master < t_og > : type_either_or < t_og, t_url, t_ogtype >
{   using type_either_or < t_og, t_url, t_ogtype > :: type_either_or;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_either_or < t_og, t_url, t_ogtype > :: set_value (nits, v, s);
        type_either_or < t_og, t_url, t_ogtype > :: status (set_og_value (status (), nits, v, type_either_or < t_og, t_url, t_ogtype > :: get_string ())); } };

template < > struct type_master < t_ogdet > : type_or_null < t_ogdet, t_determiner >
{   using type_or_null < t_ogdet, t_determiner > :: type_or_null; };

template < > struct type_master < t_ontology > : tidy_string < t_ontology >
{   e_ontology mdr_ = s_none;
    e_ontology_type st_ = ont_illegal;
    ::std::string vocab_;
    using tidy_string < t_ontology > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    e_ontology_type ontology_type () const noexcept { return st_; }
    e_ontology root () const noexcept { return mdr_; }
    ::std::string vocab () const { return vocab_; } };

template < > struct type_master < t_pseudonamedspace > : tidy_string < t_pseudonamedspace >
{   using tidy_string < t_pseudonamedspace > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_pseudonamedspace > :: set_value (nits, v, s);
        tidy_string < t_pseudonamedspace > :: status (set_pseudonamedspace_value (status (), nits, v, tidy_string < t_pseudonamedspace > :: get_string ())); } };

template < > struct type_master < t_nsds > : type_at_least_one < t_nsds, sz_space_char, t_nsd >
{ using type_at_least_one < t_nsds, sz_space_char, t_nsd > :: type_at_least_one; };

template < > struct type_master < t_ratio > : tidy_string < t_ratio >
{   using tidy_string < t_ratio > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_number; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_ratio > :: set_value (nits, v, s);
        tidy_string < t_ratio > :: status (set_ratio_value (tidy_string < t_ratio > :: status (), nits, v, tidy_string < t_ratio > :: get_string ())); } };

template < > struct type_master < t_real_1_2 > : type_one_or_both < t_real_1_2, t_real, sz_commaspace, t_real >
{   using type_one_or_both < t_real_1_2, t_real, sz_commaspace, t_real > :: type_one_or_both;
    static e_animation_type animation_type () noexcept { return at_number; } };

template < > struct type_master < t_roles > : string_vector < t_roles, sz_space_char >
{   using string_vector < t_roles, sz_space_char > :: string_vector;
    vint_t vr_;
    void swap (type_master < t_roles >& t) noexcept
    {   vr_.swap (t.vr_);
        string_vector < t_roles, sz_space_char > :: swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void reset () noexcept
    {   vr_.clear ();
        string_vector < t_roles, sz_space_char > :: reset (); }
    int at (const ::std::size_t n) const
    {   PRESUME (n < vr_.size (), __FILE__, __LINE__);
        return vr_.at (n); }
    int& at (const ::std::size_t n)
    {   PRESUME (n < vr_.size (), __FILE__, __LINE__);
        return vr_.at (n); }
    vint_t get_ints () const { return vr_; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s); };

template < > struct type_master < t_roman_dsc > : tidy_string < t_roman_dsc >
{   using tidy_string < t_roman_dsc > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_roman_dsc > :: set_value (nits, v, s);
        tidy_string < t_roman_dsc > :: status (set_roman_dsc_value (tidy_string < t_roman_dsc > :: status (), nits, v, tidy_string < t_roman_dsc > :: get_string (), box ())); } };

template < > struct type_master < t_sandboxen > : string_vector < t_sandboxen, sz_space_char >
{   using string_vector < t_sandboxen, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_sandboxen, sz_space_char > :: set_value (nits, v, s);
        string_vector < t_sandboxen, sz_space_char > :: status (set_sandboxen_value (string_vector < t_sandboxen, sz_space_char > :: status (),
            nits, v, string_vector < t_sandboxen, sz_space_char > :: get (), box ())); } };

template < > struct type_master < t_shape3 > : tidy_string < t_shape3 >
{   using tidy_string < t_shape3 > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_shape3 > :: set_value (nits, v, s);
        tidy_string < t_shape3 > :: status (set_shape3_value (tidy_string < t_shape3 > :: status (), nits, v, tidy_string < t_shape3 > :: get_string ())); } };

template < > struct type_master < t_imcastr > : tidy_string < t_imcastr >
{   url u_;
    int width_ = 0;
    float density_ = 1.0;
    bool has_width_ = false, has_density_ = false;
    using tidy_string < t_imcastr > :: tidy_string;
    void swap (type_master < t_imcastr >& t);
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s);
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) tidy_string < t_imcastr > :: status (s_good);
        else tidy_string < t_imcastr > :: status (s_invalid); }
    bool has_width () const noexcept { return has_width_; }
    bool has_density () const noexcept { return has_density_; }
    void reset () noexcept
    {   u_.reset (); width_ = 0; density_ = 1.0;
        tidy_string < t_imcastr > :: reset (); }
    static ::std::string default_value () noexcept { return ::std::string (); } };

template < > struct type_master < t_srcset > : tidy_string < t_srcset >
{   typedef ::std::vector < type_master < t_imcastr > > vix_t;
    vix_t value_;
    bool has_width_ = false, has_density_ = false;
    using tidy_string < t_srcset > :: tidy_string;
    void swap (type_master < t_srcset >& t) noexcept
    {   value_.swap (t.value_);
        tidy_string < t_srcset >::swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s);
    bool has_width () const noexcept { return has_width_; }
    bool has_density () const noexcept { return has_density_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) string_value < t_srcset > :: status (s_good);
        else tidy_string < t_srcset > :: status (s_invalid); }
    void reset () noexcept
    {   value_.clear ();
        tidy_string < t_srcset > :: reset (); } };

template < > struct type_master < t_css_text_align_4 > : tidy_string < t_css_text_align_4 >
{   using tidy_string < t_css_text_align_4 > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_text_align_4 > :: set_value (nits, v, s);
        tidy_string < t_css_text_align_4 > :: status (set_css_text_align_4_value (tidy_string < t_css_text_align_4 > :: status (), nits, v, tidy_string < t_css_text_align_4 > :: get_string ())); } };

template < > struct type_master < t_css_text_resizes > : tidy_string < t_css_text_resizes >
{   using tidy_string < t_css_text_resizes > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_text_resizes > :: set_value (nits, v, s);
        tidy_string < t_css_text_resizes > :: status (set_css_text_resizes_value (tidy_string < t_css_text_resizes > :: status (), nits, v, tidy_string < t_css_text_resizes > :: get_string ())); } };

template < > struct type_master < t_css_vertal_2 > : tidy_string < t_css_vertal_2 >
{   using tidy_string < t_css_vertal_2 > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_vertal_2 > :: set_value (nits, v, s);
        tidy_string < t_css_vertal_2 > :: status (set_css_vertal_2_value (tidy_string < t_css_vertal_2 > :: status (), nits, v, tidy_string < t_css_vertal_2 > :: get_string ())); } };

template < > struct type_master < t_css_whitespace_2 > : tidy_string < t_css_whitespace_2 >
{   using tidy_string < t_css_whitespace_2 > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_whitespace_2 > :: set_value (nits, v, s);
        tidy_string < t_css_whitespace_2 > :: status (set_css_whitespace_2_value (tidy_string < t_css_whitespace_2 > :: status (), nits, v, tidy_string < t_css_whitespace_2 > :: get_string ())); } };

template < > struct type_master < t_rsl_usages > : type_at_least_one < t_rsl_usages, sz_comma, t_rsl_usage >
{ using type_at_least_one < t_rsl_usages, sz_comma, t_rsl_usage > :: type_at_least_one; };

template < > struct type_master < t_rsl_users > : type_at_least_one < t_rsl_users, sz_comma, t_rsl_user >
{ using type_at_least_one < t_rsl_users, sz_comma, t_rsl_user > :: type_at_least_one; };

template < > struct type_master < t_css_place_content > : tidy_string < t_css_place_content >
{   using tidy_string < t_css_place_content > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_place_content > :: set_value (nits, v, s);
        tidy_string < t_css_place_content > :: status (set_css_place_content (tidy_string < t_css_place_content > :: status (), nits, v, tidy_string < t_css_place_content > :: get_string ())); } };

template < > struct type_master < t_css_place_items > : tidy_string < t_css_place_items >
{   using tidy_string < t_css_place_items > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_place_items > :: set_value (nits, v, s);
        tidy_string < t_css_place_items > :: status (set_css_place_items (tidy_string < t_css_place_items > :: status (), nits, v, tidy_string < t_css_place_items > :: get_string ())); } };

template < > struct type_master < t_css_place_self > : tidy_string < t_css_place_self >
{   using tidy_string < t_css_place_self > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_place_self > :: set_value (nits, v, s);
        tidy_string < t_css_place_self > :: status (set_css_place_self (tidy_string < t_css_place_self > :: status (), nits, v, tidy_string < t_css_place_self > :: get_string ())); } };
