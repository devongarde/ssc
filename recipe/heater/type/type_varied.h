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
#include "type/type_enum.h"
#include "element/elem.h"

class element;

template < class T, class V > struct basic_value
{   static int get_int (const T& ) { return 0; } };

template < class T > struct basic_value < T, true_type >
{   static int get_int (const T& t) { return static_cast < int > (t.get ()); } };

template < e_type BASE > struct varied : tidy_string < BASE >
{   ::std::size_t type_ = 0;
    int int_ = 0;
    void swap (tidy_string < BASE >& t) NOEXCEPT
    {   tidy_string < BASE > :: swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < BASE > :: set_value (nits, v, s); }
    ::std::size_t type () const { return type_; }
    int get_int () const { return int_; }
    template < class T > void validate_type (nitpick& nits, const html_version& v)
    {   T t;
        t.set_value (nits, v, tidy_string < BASE > :: get_string ());
        if (t.good ())
        {   type_ = t.type ();
            int_ = basic_value < T, typename T :: has_int_type > :: get_int (t); }
        else tidy_string < BASE > :: status (s_invalid); }
   template < class T > void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* pe, const ::std::string& )
    {   if (tidy_string < BASE > :: good ())
        {   T t;
            t.set_value (nits, v, tidy_string < BASE > :: get_string ());
            t.verify_attribute (nits, v, e, pe);
            if (! t.good ()) tidy_string < BASE > :: status (s_invalid); } }
    template < class T > bool check_id_defined (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   T t;
        t.set_value (nits, v, tidy_string < BASE > :: get_string ());
        if (t.good ()) return t.invalid_id (nits, v, ids, pe);
        return false; } };

template < > struct type_master < t_about > : varied < t_about >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.svg ()) validate_type < string_vector < t_text, sz_space > > (nits, v);
            else validate_type < type_master < t_curie_safe > > (nits, v); } };

template < > struct type_master < t_accept > : varied < t_accept >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_input :
                    if (v == html_2)
                    {   validate_type < type_master < t_mimelist > > (nits, v); return; }
                    // drop thru'
                default :
                    validate_type < type_master < t_generic > > (nits, v); } } };

template < > struct type_master < t_actiontype > : varied < t_actiontype >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.math_version () == math_2)
                validate_type < type_master < t_actiontype2 > > (nits, v); } };

template < > struct type_master < t_align > : varied < t_align >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_applet :
                    validate_type < type_master < t_align3 > > (nits, v); return;
                case elem_array :
                    return;
                case elem_br :
                    validate_type < type_master < t_lcrnalign > > (nits, v); return;
                case elem_caption :
                    switch (v.mjr ())
                    {   case 0 :
                        case 1 : break;
                        case 2 :    validate_type < type_master < t_align2070 > > (nits, v);
                                    break;
                        case 3 :    if (v.mnr () == 2) validate_type < type_master < t_tbalign > > (nits, v);
                                    else validate_type < type_master < t_captionalign > > (nits, v);
                                    break;
                        case 4 :    validate_type < type_master < t_captionalign > > (nits, v);  break;
                        default :   validate_type < type_master < t_lcralign > > (nits, v); break; }
                    return;
                case elem_div :
                case elem_hr :
                case elem_p :
                    if (v >= html_3_2) { validate_type < type_master < t_lcralign > > (nits, v); return; }
                    else if (v == html_plus) { validate_type < type_master < t_alignplus > > (nits, v); return; }
                    break;
                case elem_fig :
                    if (v == html_plus) { validate_type < type_master < t_alignfig > > (nits, v); return; }
                    validate_type < type_master < t_figalign > > (nits, v); return;
                case elem_legend :
                    validate_type < type_master < t_captionalign > > (nits, v); return;
                case elem_image :
                    if (v == html_plus) { validate_type < type_master < t_valign_tmb > > (nits, v); return; }
                    return;
                case elem_img :
                    if (v >= html_3_0) validate_type < type_master < t_align3 > > (nits, v);
                    else if ((v == html_plus) || (v == html_2)) validate_type < type_master < t_valign_tmb > > (nits, v);
                    else validate_type < type_master < t_lcralign > > (nits, v);
                    return;
                case elem_input :
                    if ((v == html_2) || (v == html_plus)) { validate_type < type_master < t_valign_tmb > > (nits, v); return; }
                    break;
                case elem_l :
                    validate_type < type_master < t_alignplus > > (nits, v); return;
                case elem_mstack :
                case elem_mtable :
                    validate_type < type_master < t_mathalign_n > > (nits, v); return;
                case elem_spacer :
                case elem_sub :
                case elem_sup :
                    validate_type < type_master < t_lcralign > > (nits, v); return;
                case elem_tab :
                    if ((v == html_plus) || (v == html_2)) validate_type < type_master < t_aligndec > > (nits, v);
                    return;
                case elem_table :
                    if (v == html_3_0) { validate_type < type_master < t_figalign > > (nits, v); return; }
                    else if (v == html_3_2) { validate_type < type_master < t_lcralign > > (nits, v); return; }
                    else if (v == html_4_1) { validate_type < type_master < t_halign > > (nits, v); return; }
                    break;
                case elem_td :
                case elem_th :
                case elem_tr :
                    if ((v == html_3_2) || (v == html_plus))
                    {   validate_type < type_master < t_lcralign > > (nits, v); return; }
                    else if (v == html_3_0)
                    {   validate_type < type_master < t_decalign > > (nits, v); return; }
                    break;
                default : break; }
            if ((v == html_2) && context.rfc_2070 ()) validate_type < type_master < t_align2070 > > (nits, v);
            else validate_type < type_master < t_halign > > (nits, v); } };

template < > struct type_master < t_arabic_form > : varied < t_arabic_form >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            switch (v.svg_version ())
            {   case sv_1_0 :
                case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_text > > (nits, v);
                    break;
                case sv_1_1 :
                    validate_type < type_master < t_arabicenum > > (nits, v);
                    break;
                default :
                    PRESUME (false, __FILE__, __LINE__);
                    break; } } };

template < > struct type_master < t_autocompletevaried > : varied < t_autocompletevaried >
{   bool form_ = true;
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if ((e.get () == elem_form) || (v < html_jan13)) validate_type < type_master < t_onoff > > (nits, v);
            else { form_ = false; validate_type < type_master < t_autocompletes > > (nits, v); } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (form_) return false;
        type_master < t_autocompletes > t;
        ::std::string s (trim_the_lot_off (varied < t_autocompletevaried > :: get_string ()));
        nitpick nuts;
        t.set_value (nuts, v, s);
        return t.invalid_id (nits, v, ids, pe); } };

template < > struct type_master < t_background > : varied < t_background >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_colour > > (nits, v);
            else validate_type < type_master < t_url > > (nits, v); } };

template < > struct type_master < t_clear > : varied < t_clear >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_br :
                    validate_type < type_master < t_larnalign > > (nits, v); break;
                default :
                    validate_type < type_master < t_clear30 > > (nits, v); } } };

template < > struct type_master < t_clip > : varied < t_clip >
{   static e_animation_type animation_type () { return at_coordinate; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_svg ()) validate_type < type_master < t_svg_clip > > (nits, v);
            else validate_type < type_master < t_points > > (nits, v); } };

template < > struct type_master < t_closure > : varied < t_closure >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.math_version () == math_1) validate_type < type_master < t_text > > (nits, v);
            else validate_type < type_master < t_mathclosure > > (nits, v); } };

template < > struct type_master < t_colour_v > : varied < t_colour_v >
{   static e_animation_type animation_type () { return at_colour; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.svg_version () != sv_none) validate_type < type_master < t_colour_i > > (nits, v);
            else validate_type < type_master < t_colour > > (nits, v); } };

template < > struct type_master < t_direction > : varied < t_direction >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            switch (v.svg_version ())
            {   case sv_1_0 :
                case sv_1_1 :
                case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_svg_direction > > (nits, v);
                    break;
                case sv_2_0 :
                case sv_2_1 :
                    validate_type < type_master < t_svg_direction2 > > (nits, v);
                    break;
                default :
                    validate_type < type_master < t_uplr > > (nits, v); } } };

template < > struct type_master < t_display > : varied < t_display >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& id, element* , const ::std::string& )
    {   if (good () || empty ())
            if (id.is_svg () || (id.get () == elem_a)) validate_type < type_master < t_svg_display > > (nits, v);
            else if (id.is_math ()) validate_type < type_master < t_mathdisplay > > (nits, v); } };

template < > struct type_master < t_end > : varied < t_end >
{   static e_animation_type animation_type () { return at_time; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_audio :
                case elem_video :
                    validate_type < type_master < t_just_time > > (nits, v); break;
                default :
                    validate_type < type_master < t_endvaluelist > > (nits, v); } } };

template < > struct type_master < t_fill > : varied < t_fill >
{   static e_animation_type animation_type () { return at_paint; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if ((e.get () == elem_vefill) || (e.get () == elem_vestroke))
                validate_type < type_master < t_fill_ve > > (nits, v);
            else if (((elem :: categories (e) & EF_SVG_ANIM) != 0) || (e.get () == elem_animation))
                validate_type < type_master < t_fillanim > > (nits, v);
            else validate_type < type_master < t_paint > > (nits, v); } };

template < > struct type_master < t_fontstretch > : varied < t_fontstretch >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_font_face)
                validate_type < type_master < t_fontstretches > > (nits, v);
            else validate_type < type_master < t_svg_fontstretch > > (nits, v); } };

template < > struct type_master < t_fontstyle > : varied < t_fontstyle >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ())
                validate_type < type_master < t_mathfontstyle > > (nits, v);
            else if (e.get () == elem_font_face)
                validate_type < type_master < t_svg_fontstyle_ff > > (nits, v);
            else validate_type < type_master < t_svg_fontstyle > > (nits, v); } };

template < > struct type_master < t_fontvariant > : varied < t_fontvariant >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_font_face)
                validate_type < type_master < t_svg_fontstyle_ff > > (nits, v);
            else validate_type < type_master < t_svg_fontstyle > > (nits, v); } };

template < > struct type_master < t_font_variant > : varied < t_font_variant >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            switch (v.svg_version ())
            {   case sv_1_0 :
                case sv_1_1 :
                case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_fontvariant > > (nits, v);
                    break;
                case sv_2_0 :
                case sv_2_1 :
                    validate_type < type_master < t_font_variant_2 > > (nits, v);
                    break;
                default :
                    PRESUME (false, __FILE__, __LINE__);
                    break; } } };

template < > struct type_master < t_fontweight > : varied < t_fontweight >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_mathfontweight > > (nits, v);
            else if (e.get () == elem_font_face)
                validate_type < type_master < t_svg_fontweights > > (nits, v);
            else validate_type < type_master < t_svg_fontweight > > (nits, v); } };

template < > struct type_master < t_form > : varied < t_form >
{   bool math_ = false;
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   math_ = e.is_math ();
        if (good () || empty ())
            if (math_) validate_type < type_master < t_mathform > > (nits, v);
            else validate_type < type_master < t_idref > > (nits, v); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (math_) return false;
        type_master < t_idref > t;
        ::std::string s (trim_the_lot_off (varied < t_form > :: get_string ()));
        t.set_value (nits, v, s);
        if (t.invalid_id (nits, v, ids, pe)) return true;
        if (! ids.has_id (s)) return true;
        if (v < html_5_0) return false;
        e_element e (ids.get_tag (s));
        if (e == elem_form) return false;
        nits.pick (nit_not_form, ed_50, "4.10.18.3 Association of controls and forms", es_error, ec_attribute, quote (s), " is <", elem::name (e), ">, not <FORM>");
        return true; } };

template < > struct type_master < t_frame > : varied < t_frame >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
        {   if (e.is_math ()) validate_type < type_master < t_mathframe > > (nits, v);
            switch (e.get ())
            {   case elem_mtable :
                    validate_type < type_master < t_nsd > > (nits, v); break;
                case elem_table :
                    validate_type < type_master < t_tableframe > > (nits, v); break; // maybe 2 only
                default :
                    validate_type < type_master < t_frame4 > > (nits, v); } } } };

template < > struct type_master < t_groupalign > : varied < t_groupalign >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_mtable :
                case elem_mtr :
                case elem_mlabeledtr :
                    validate_type < type_master < t_lcrdss > > (nits, v); break;
                case elem_mtd :
                    validate_type < type_master < t_lcrds > > (nits, v); break;
                default :
                    validate_type < type_master < t_lcrd > > (nits, v); } } };

template < > struct type_master < t_index > : varied < t_index >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_integer > > (nits, v);
            else validate_type < type_master < t_text > > (nits, v); } };

template < > struct type_master < t_in > : varied < t_in >
{   bool concerned_ = false;
    static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& , const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good ())
            if (v.svg_version () != sv_none)
                if ((e.categories () & EF_SVG_FILTER) != 0)
                {   nitpick nuts;
                    concerned_ = test_value < t_filter_in > (nuts, v, varied < t_in > :: get_string ()); } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (concerned_) return false;
        return check_id_defined < type_master < t_idref > > (nits, v, ids, pe); } };

template < > struct type_master < t_loop > : varied < t_loop >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_audio :
                    validate_type < type_master < t_html_boolean > > (nits, v); break;
                case elem_marquee :
                case elem_bgsound :
                    validate_type < type_master < t_loopie > > (nits, v); } } };

template < > struct type_master < t_methodological > : varied < t_methodological >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_textpath)
                validate_type < type_master < t_svg_method > > (nits, v);
            else
                validate_type < type_master < t_method > > (nits, v); } };

template < > struct type_master < t_mode > : varied < t_mode >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_math :
                    validate_type < type_master < t_mathmode > > (nits, v); break;
                case elem_feblend :
                    validate_type < type_master < t_svg_mode > > (nits, v); } } };

template < > struct type_master < t_name > : varied < t_name >
{   e_element e_ = 0;
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_meta :
                    validate_type < type_master < t_metaname > > (nits, v); break;
                case elem_a :
                case elem_map :
                    validate_type < type_master < t_id > > (nits, v);
                    e_ = e.get (); break;
                case elem_button :
                case elem_input :
                case elem_meter :
                case elem_output :
                case elem_progress :
                case elem_select :
                case elem_textarea :
                    validate_type < type_master < t_id > > (nits, v);
                    e_ = e.get (); break;
                case elem_colour_profile :
                    return; }
        if (good () && v.is_5 () && form_bitset.test (e.get ()))
        {   ::std::string s (varied < t_name > :: get_string ());
            if (compare_complain (nits, v, "_charset_", s))
                nits.pick (nit_special_name, ed_50, "4.10.19.1 Naming form controls: the name attribute", es_comment, ec_type, "note that ", quote (s), " causes special behaviour");
            if (compare_complain (nits, v, "isindex", s))
                switch (w3_minor_5 (v))
                {   case 0 :
                        nits.pick (nit_special_name, ed_50, "4.10.19.1 Naming form controls: the name attribute", es_comment, ec_type, "note that ", quote (s), " causes special behaviour in ", v.report (), " only");
                        break;
                    case 4 :
                        nits.pick (nit_special_name, ed_50, "4.10.19.1 Naming form controls: the name attribute", es_error, ec_type, "do not use ", quote (s), ", it had special behaviour in old versions of HTML");
                        break;
                    default :
                        nits.pick (nit_special_name, ed_50, "4.10.19.1 Naming form controls: the name attribute", es_warning, ec_type, "avoid ", quote (s), ", it has special behaviour in older versions of HTML"); } } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   ids_t& get_varied_names (element* pe);
        switch (e_)
        {   case elem_a :
            case elem_map :
                return check_id_defined < type_master < t_id > > (nits, v, ids, pe);
            case elem_button :
            case elem_input :
            case elem_meter :
            case elem_output :
            case elem_progress :
            case elem_select :
            case elem_textarea :
                return check_id_defined < type_master < t_id > > (nits, v, get_varied_names (pe), pe);
            default : return false; } } };

template < > struct type_master < t_notation > : varied < t_notation >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.mjr () > 3)
                if (v.math_version () == math_2) validate_type < type_master < t_mathnotation > > (nits, v);
                else if (v.math_version () > math_2) validate_type < type_master < t_mathnotations > > (nits, v);
            else validate_type < type_master < t_notations > > (nits, v); } };

template < > struct type_master < t_occurence > : varied < t_occurence >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.math_version () == math_1) validate_type < type_master < t_text > > (nits, v);
            else validate_type < type_master < t_mathoccurence > > (nits, v); } };

template < > struct type_master < t_open > : varied < t_open >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (! e.is_math ()) validate_type < type_master < t_existential > > (nits, v); } };

template < > struct type_master < t_operator > : varied < t_operator >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_fecomposite :
                    validate_type < type_master < t_composite_operator > > (nits, v); break;
                case elem_femorphology :
                    validate_type < type_master < t_morphology_operator > > (nits, v); } } };

template < > struct type_master < t_order > : varied < t_order >
{   static e_animation_type animation_type () { return at_integer; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_mathorder > > (nits, v);
            else if (e.is_svg ()) validate_type < type_master < t_unsigned_1_or_2 > > (nits, v);
            else validate_type < type_master < t_xorder > > (nits, v); } };

template < > struct type_master < t_overflow > : varied < t_overflow >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_mathoverflow > > (nits, v);
            else validate_type < type_master < t_svg_overflow > > (nits, v); } };

template < > struct type_master < t_phase > : varied < t_phase >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_svg ()) validate_type < type_master < t_svg_phase > > (nits, v);
            else validate_type < type_master < t_phase_x > > (nits, v); } };

template < > struct type_master < t_preload > : varied < t_preload >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   PRESUME (v >= html_4_0, __FILE__, __LINE__);
        if (good () || empty ())
            if (v <= html_4_1) validate_type < type_master < t_html_boolean > > (nits, v);
            else if (good ()) validate_type < type_master < t_preload5 > > (nits, v); } };

template < > struct type_master < t_preserveaspectratio > : varied < t_preserveaspectratio >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            switch (v.svg_version ())
            {   case sv_1_2_tiny :
                case sv_1_2_full :
                case sv_2_0 :
                case sv_2_1 :
                    validate_type < type_master < t_preserveaspectratio12 > > (nits, v);
                    break;
                default :
                    validate_type < type_master < t_preserveaspectratio10 > > (nits, v); } } };

template < > struct type_master < t_rap > : varied < t_rap >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_ul :
                    validate_type < type_master < t_wrap3 > > (nits, v);
                    break;
                case elem_textarea :
                    if (v.is_5 ()) validate_type < type_master < t_wrap > > (nits, v);
                    break;
                case elem_dir :
                case elem_menu :
                    if ((v == html_plus) || (v == html_3_0))
                    {   validate_type < type_master < t_wrap3 > > (nits, v);  return; }
                    // drop through
                default :
                    validate_type < type_master < t_integer > > (nits, v); break; } } };

template < > struct type_master < t_rowscols > : varied < t_rowscols >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_textarea :
                    validate_type < type_master < t_positive > > (nits, v); break;
                case elem_frameset :
                    validate_type < type_master < t_measures > > (nits, v); break; } } };

template < > struct type_master < t_scope > : varied < t_scope >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_mathscope > > (nits, v);
            else if (e.get () == elem_link) validate_type < type_master < t_url > > (nits, v);
            else validate_type < type_master < t_tdscope > > (nits, v); } };

template < > struct type_master < t_shape > : varied < t_shape >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            switch (v.mjr ())
            {   case 1 :    return;
                case 2 :    validate_type < type_master < t_shape_rcp > > (nits, v); return;
                case 3 :    if (v.mnr () == 0) validate_type < type_master < t_shape3 > > (nits, v);
                            else validate_type < type_master < t_shape_rcp > > (nits, v);
                            return;
                case 4 :    validate_type < type_master < t_shape4 > > (nits, v); return;
                default :   validate_type < type_master < t_shape7 > > (nits, v); } } };

template < > struct type_master < t_side > : varied < t_side >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good ())
            if (e.is_math ()) validate_type < type_master < t_mathside > > (nits, v);
            else if (e.is_svg ()) validate_type < type_master < t_svg_side > > (nits, v); } };

template < > struct type_master < t_size > : varied < t_size >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_basefont :
                    validate_type < type_master < t_1_to_7 > > (nits, v);
                    break;
                case elem_box :
                    validate_type < type_master < t_size3 > > (nits, v);
                    break;
                case elem_font :
                    validate_type < type_master < t_plus_1_7 > > (nits, v);
                    break;
                case elem_select :
                    validate_type < type_master < t_positive > > (nits, v);
                    break;
                default :
                    validate_type < type_master < t_unsigned > > (nits, v); } } };

template < > struct type_master < t_sizes > : varied < t_sizes >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_link :
                    validate_type < type_master < t_wxhs > > (nits, v); break;
                case elem_img :
                case elem_source :
                    validate_type < type_master < t_imgsizes > > (nits, v); break; } } };

template < > struct type_master < t_start > : varied < t_start >
{   static e_animation_type animation_type () { return at_time; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_audio :
                case elem_video :
                    validate_type < type_master < t_just_time > > (nits, v); break;
                default :
                    validate_type < type_master < t_integer > > (nits, v); } } };

template < > struct type_master < t_style > : varied < t_style >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v == html_plus) validate_type < type_master < t_plusstyle > > (nits, v);
            else validate_type < type_master < t_css > > (nits, v); } };

template < > struct type_master < t_measure_or_more > : varied < t_measure_or_more >
{   static e_animation_type animation_type () { return at_length; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (v.svg_version () != sv_none)
                switch (e.get ())
                {   case elem_altglyph :
                    case elem_text :
                    case elem_tref :
                    case elem_tspan : validate_type < type_master < t_measures > > (nits, v); return;
                    default : break; }
                    // drop thru
            validate_type < type_master < t_measure > > (nits, v); } };

template < > struct type_master < t_num > : varied < t_num >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_input)
                validate_type < type_master < t_text > > (nits, v);
            else validate_type < type_master < t_duration_media > > (nits, v); } };

template < > struct type_master < t_rotate > : varied < t_rotate >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e == elem_animatemotion)
                validate_type < type_master < t_rotate_anim > > (nits, v);
            else validate_type < type_master < t_reals > > (nits, v); } };

template < > struct type_master < t_type > : varied < t_type >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_a :
                case elem_link :
                case elem_map :
                case elem_object :
                case elem_param :
                case elem_source :
                case elem_style :
                case elem_transformer :
                    validate_type < type_master < t_mime > > (nits, v); break;
                case elem_animatetransform :
                    validate_type < type_master < t_transform_anim > > (nits, v); break;
                case elem_bb :
                    validate_type < type_master < t_bb > > (nits, v); break;
                case elem_button :
                    validate_type < type_master < t_button > > (nits, v); break;
                case elem_ci :
                    validate_type < type_master < t_citype > > (nits, v); break;
                case elem_cn :
                    validate_type < type_master < t_cntype > > (nits, v); break;
                case elem_command :
                    validate_type < type_master < t_command > > (nits, v); break;
                case elem_declare :
                    validate_type < type_master < t_text > > (nits, v); break;
                case elem_device :
                    validate_type < type_master < t_device > > (nits, v); break;
                case elem_fecolourmatrix :
                    validate_type < type_master < t_matrixtype > > (nits, v); break;
                case elem_fefunca :
                case elem_fefuncb :
                case elem_fefuncg :
                case elem_fefuncr :
                    validate_type < type_master < t_svg_type > > (nits, v);
                    break;
                case elem_feturbulence :
                    validate_type < type_master < t_turbulence_type > > (nits, v); break;
                case elem_input :
                    switch (v.mjr ())
                    {   case 0 :
                        case 2 :    break;
                        case 1 :    if (v.mnr () == 1) { validate_type < type_master < t_inputplus > > (nits, v); return; }
                                    break;
                        case 3 :    if (v.mnr () == 0) validate_type < type_master < t_inputtype3 > > (nits, v);
                                    else validate_type < type_master < t_inputtype32 > > (nits, v);
                                    break;
                        case 4 :    if (v.mnr () == 1) { validate_type < type_master < t_inputtype4 > > (nits, v);  return; }
                                    break;
                        default :   validate_type < type_master <  t_inputtype5 > > (nits, v); return;}
                    validate_type < type_master < t_inputtype > > (nits, v);
                    break;
                case elem_keygen :
                    validate_type < type_master < t_keygentype > > (nits, v); break;
                case elem_li :
                    validate_type < type_master < t_roman_dsc > > (nits, v); break;
                case elem_ul :
                    validate_type < type_master < t_dsc > > (nits, v); break;
                case elem_menu :
                    if (v < html_jul17)
                        validate_type < type_master < t_menutype > > (nits, v);
                    break;
                case elem_menuitem :
                    validate_type < type_master < t_menuitem > > (nits, v); break;
                case elem_ol :
                    validate_type < type_master < t_listtype > > (nits, v); break;
                case elem_script :
                    if (v >= html_jan16)
                        if (compare_complain (nits, v, "module", varied < t_type > :: get_string ()))
                        {   varied < t_type > :: type_ = static_cast < ::std::size_t > (mime_faux_module);
                            break; }
                    validate_type < type_master < t_mime > > (nits, v); break;
                case elem_set :
                    validate_type < type_master < t_settype > > (nits, v); break;
                case elem_spacer :
                    validate_type < type_master < t_spacer > > (nits, v); break;
                case elem_tendsto :
                    validate_type < type_master < t_tendstotype > > (nits, v); break;
                case elem_traitdef :
                    validate_type < type_master < t_attributetype > > (nits, v); break;
                case elem_transition :
                    validate_type < type_master < t_transition_type > > (nits, v); break; } } };

template < > struct type_master < t_valign > : varied < t_valign >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (good () || empty ())
            if (v == html_3_0) validate_type < type_master < t_valign3 > > (nits, v);
            else validate_type < type_master < t_valign_tmb > > (nits, v); } };

template < > struct type_master < t_value > : varied < t_value >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (e.get () == elem_li)
            if (empty ()) nits.pick (nit_empty, es_error, ec_attribute, "value expected");
            else validate_type < type_master < t_integer > > (nits, v); } };

template < > struct type_master < t_values > : varied < t_values >
{   static e_animation_type animation_type () { return at_list; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_fecolourmatrix) return;  // process separately
            else if ((elem :: categories (e) & EF_SVG_ANIM) != 0)
                validate_type < type_master < t_svg_values > > (nits, v);
            else validate_type < type_master < t_matrix_values > > (nits, v); } };

template < > struct type_master < t_valuetype2 > : varied < t_valuetype2 >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (e.get () != elem_traitdef)
            validate_type < type_master < t_valuetype > > (nits, v); } };

template < > struct type_master < t_vector_effect > : varied < t_vector_effect >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (empty ())
            nits.pick (nit_vector_effect, es_error, ec_attribute, "vector effect should not be empty");
        else if (good ())
            switch (v.svg_version ())
            {   case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_vector_effect_12 > > (nits, v); break;
                case sv_2_0 :
                    validate_type < type_master < t_vector_effect_20 > > (nits, v); break;
                case sv_2_1 :
                    validate_type < type_master < t_vector_effect_2s > > (nits, v); break;
                default :
                    nits.pick (nit_vector_effect, es_error, ec_attribute, "vector effect requires SVG 1.2 or SVG 2");
                    break; } } };

template < > struct type_master < t_version > : varied < t_version >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () && (e.get () == elem_svg)) validate_type < type_master < t_svg_version > > (nits, v); } };

// R.I.P. David Senior, 'vid', murdered in Prague, 1996
template < > struct type_master < t_vid > : varied < t_vid >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () != elem_set)
                if ((elem :: categories (e) & EF_SVG_ANIM) != 0)
//                    validate_type < type_master < t_real > > (nits, v);
                    validate_type < type_master < t_text > > (nits, v);  // number or function, functions to be investigated
                else validate_type < type_master < t_idref > > (nits, v); } };

template < > struct type_master < t_depth > : varied < t_depth >
{   static e_animation_type animation_type () { return at_length; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_mspace :
                    validate_type < type_master < t_vunit > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudo > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_height > : varied < t_height >
{   static e_animation_type animation_type () { return at_coordinate; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_mspace :
                    validate_type < type_master < t_vunit > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudo > > (nits, v); break;
                case elem_image :
                    if (v.math_version () == math_2) validate_type < type_master < t_mathvertauto > > (nits, v);
                    else validate_type < type_master < t_vunit > > (nits, v);
                    break;
                case elem_textarea :
                    if (v.is_svg_12 ())
                    {   validate_type < type_master < t_measure_a > > (nits, v); break; }
                    // drop thru'
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_lspace > : varied < t_lspace >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_mo :
                    validate_type < type_master < t_mathspace > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudonamedspace > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_visibility > : varied < t_visibility >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
    {   if (empty ())
            nits.pick (nit_vector_effect, es_error, ec_attribute, "visibility should be seen");
        else if (good ())
            switch (v.svg_version ())
            {   case sv_1_0 :
                case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_visibility10 > > (nits, v); break;
                case sv_1_1 :
                case sv_2_0 :
                case sv_2_1 :
                    validate_type < type_master < t_visibility11 > > (nits, v); break;
                default :
                    PRESUME (false, __FILE__, __LINE__); break; } } };

template < > struct type_master < t_width > : varied < t_width >
{   static e_animation_type animation_type () { return at_coordinate; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_mspace :
                    validate_type < type_master < t_mathspace > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudonamedspace > > (nits, v); break;
                case elem_mtable :
                    validate_type < type_master < t_mathspaceauto > > (nits, v); break;
                case elem_textarea :
                    if (v.is_svg_12 ())
                    {   validate_type < type_master < t_measure_a > > (nits, v); break; }
                    // drop thru'
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_xlinkactuate_onload > : type_must_be < t_xlinkactuate_onload, sz_onload > { };
template < > struct type_master < t_xlinkactuate_onrequest > : type_must_be < t_xlinkactuate_onrequest, sz_onrequest > { };

template < > struct type_master < t_xlinkactuate > : varied < t_xlinkactuate >
{   void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_a) validate_type < type_master < t_xlinkactuate_onload > > (nits, v);
            else validate_type < type_master < t_xlinkactuate_onrequest > > (nits, v); } };

template < > struct type_master < t_xlinkshow_e > : type_must_be < t_xlinkactuate_onload, sz_embed > { };
template < > struct type_master < t_xlinkshow_o > : type_must_be < t_xlinkactuate_onrequest, sz_other > { };

template < > struct type_master < t_xlinkshow > : varied < t_xlinkshow >
{   static e_animation_type animation_type () { return at_other; }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
    {   if (empty ())
            nits.pick (nit_empty, es_error, ec_attribute, "xlink:show requires a value");
        else if (good ())
            switch (e.get ())
            {   case elem_a :
                    validate_type < type_master < t_xlinkshow_a > > (nits, v); break;
                case elem_animation :
                case elem_audio :
                case elem_foreignobject :
                case elem_image :
                case elem_use :
                case elem_video :
                    validate_type < type_master < t_xlinkshow_e > > (nits, v); break;
                case elem_mtable :
                    validate_type < type_master < t_xlinkshow_o > > (nits, v); break;
                default :
                    PRESUME (false, __FILE__, __LINE__); break; } } };
