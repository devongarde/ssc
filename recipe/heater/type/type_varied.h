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
#include "type/type_enum.h"
#include "element/elem.h"

class element;

template < class T, class V > struct basic_value
{   static int get_int (const T& ) { return 0; } };

template < class T > struct basic_value < T, true_type >
{   static int get_int (const T& t) { return static_cast < int > (t.get ()); } };

template < class BASE > struct varied : BASE
{   ::std::size_t type_ = 0;
    int int_ = 0;
    void swap (BASE& t) NOEXCEPT
    {   BASE :: swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   BASE :: set_value (nits, v, s); }
    ::std::size_t type () const { return type_; }
    int get_int () const { return int_; }
    template < class T > void validate_type (nitpick& nits, const html_version& v)
    {   T t;
        t.set_value (nits, v, BASE :: get_string ());
        if (t.good ())
        {   type_ = t.type ();
            int_ = basic_value < T, typename T :: has_int_type > :: get_int (t); }
        else BASE :: status (s_invalid); }
   template < class T > void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (BASE :: good ())
        {   T t;
            t.set_value (nits, v, BASE :: get_string ());
            t.validate (nits, v, e);
            if (! t.good ()) BASE :: status (s_invalid); } }
    template < class T > bool check_id_defined (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   T t;
        t.set_value (nits, v, BASE :: get_string ());
        if (t.good ()) return t.invalid_id (nits, v, ids, pe);
        return false; } };

template < > struct type_master < t_accept > : varied < string_value < t_accept > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_input :
                    if (v == html_2)
                    {   validate_type < type_master < t_mimelist > > (nits, v); return; }
                    // drop thru'
                default :
                    validate_type < type_master < t_generic > > (nits, v); } } };

template < > struct type_master < t_align > : varied < tidy_string < t_align > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (! e.is_math ()) // not defined in MathML 1.0, merely mentioned
            {   switch (e.get ())
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
                else validate_type < type_master < t_halign > > (nits, v); } } };

template < > struct type_master < t_background > : varied < tidy_string < t_background > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_colour > > (nits, v);
            else validate_type < type_master < t_url > > (nits, v); } };

template < > struct type_master < t_clear > : varied < tidy_string < t_clear > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_br :
                    validate_type < type_master < t_larnalign > > (nits, v); break;
                default :
                    validate_type < type_master < t_clear30 > > (nits, v); } } };

template < > struct type_master < t_colour_v > : varied < tidy_string < t_colour_v > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            if (v.svg () != sv_none) validate_type < type_master < t_colour_i > > (nits, v);
            else validate_type < type_master < t_colour > > (nits, v); } };

template < > struct type_master < t_direction > : varied < tidy_string < t_direction > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            if (v.svg () >= sv_1_1) validate_type < type_master < t_svg_direction > > (nits, v);
            else validate_type < type_master < t_uplr > > (nits, v); } };

template < > struct type_master < t_fill > : varied < tidy_string < t_fill > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if ((elem :: categories (e) & EF_SVG_ANIM) != 0)
                validate_type < type_master < t_fillanim > > (nits, v);
            else validate_type < type_master < t_paint > > (nits, v); } };

template < > struct type_master < t_fontstretch > : varied < tidy_string < t_fontstretch > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_fontface)
                validate_type < type_master < t_fontstretches > > (nits, v);
            else validate_type < type_master < t_svg_fontstretch > > (nits, v); } };

template < > struct type_master < t_fontstyle > : varied < tidy_string < t_fontstyle > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ())
                validate_type < type_master < t_math_fontstyle > > (nits, v);
            else if (e.get () == elem_fontface)
                validate_type < type_master < t_svg_fontstyle_ff > > (nits, v);
            else validate_type < type_master < t_svg_fontstyle > > (nits, v); } };

template < > struct type_master < t_fontvariant > : varied < tidy_string < t_fontvariant > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_fontface)
                validate_type < type_master < t_svg_fontstyle_ff > > (nits, v);
            else validate_type < type_master < t_svg_fontstyle > > (nits, v); } };

template < > struct type_master < t_fontweight > : varied < tidy_string < t_fontweight > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_math_fontweight > > (nits, v);
            else if (e.get () == elem_fontface)
                validate_type < type_master < t_svg_fontweights > > (nits, v);
            else validate_type < type_master < t_svg_fontweight > > (nits, v); } };

template < > struct type_master < t_form > : varied < tidy_string < t_form > >
{   bool math_ = false;
    void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   math_ = e.is_math ();
        if (good () || empty ())
            if (math_) validate_type < type_master < t_mathform > > (nits, v);
            else validate_type < type_master < t_idref > > (nits, v); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (math_) return false;
        type_master < t_idref > t;
        ::std::string s (trim_the_lot_off (varied < tidy_string < t_form > > :: get_string ()));
        t.set_value (nits, v, s);
        if (t.invalid_id (nits, v, ids, pe)) return true;
        if (! ids.has_id (s)) return true;
        if (v < html_5_0) return false;
        e_element e (ids.get_tag (s));
        if (e == elem_form) return false;
        nits.pick (nit_not_form, ed_50, "4.10.18.3 Association of controls and forms", es_error, ec_attribute, quote (s), " is <", elem::name (e), ">, not <FORM>");
        return true; } };

template < > struct type_master < t_frame > : varied < tidy_string < t_frame > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
        {   if (e.is_math ()) validate_type < type_master < t_mathframe > > (nits, v);
            switch (e.get ())
            {   case elem_mtable :
                    validate_type < type_master < t_nsd > > (nits, v); break;
                case elem_table :
                    validate_type < type_master < t_tableframe > > (nits, v); break; // maybe 2 only
                default :
                    validate_type < type_master < t_frame4 > > (nits, v); } } } };

template < > struct type_master < t_groupalign > : varied < tidy_string < t_groupalign > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
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

template < > struct type_master < t_index > : varied < tidy_string < t_index > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_integer > > (nits, v);
            else validate_type < type_master < t_text > > (nits, v); } };

template < > struct type_master < t_in > : varied < tidy_string < t_in > >
{   bool concerned_ = false;
    void validate (nitpick& , const html_version& v, const e_element e, const ::std::string& )
    {   if (good ())
            if (v.svg () >= sv_1_1)
                if ((elem :: categories (e) & EF_SVG_FILTER) != 0)
                    concerned_ = true; }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   if (concerned_) return false;
        return check_id_defined < type_master < t_idref > > (nits, v, ids, pe); } };

template < > struct type_master < t_loop > : varied < tidy_string < t_loop > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_audio :
                    validate_type < type_master < t_html_boolean > > (nits, v); break;
                case elem_marquee :
                case elem_bgsound :
                    validate_type < type_master < t_loopie > > (nits, v); } } };

template < > struct type_master < t_methodological > : varied < tidy_string < t_methodological > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_textpath)
                validate_type < type_master < t_svg_method > > (nits, v);
            else
                validate_type < type_master < t_method > > (nits, v); } };

template < > struct type_master < t_mode > : varied < tidy_string < t_mode > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_math :
                    validate_type < type_master < t_math_mode > > (nits, v); break;
                case elem_feblend :
                    validate_type < type_master < t_svg_mode > > (nits, v); } } };

template < > struct type_master < t_name > : varied < tidy_string < t_name > >
{   e_element e_ = 0;
    void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_meta :
                    validate_type < type_master < t_metaname > > (nits, v); break;
                case elem_a :
                case elem_map :
                    validate_type < type_master < t_id > > (nits, v);
                    e_ = e.get (); break;
                case elem_colourprofile :
                    return;
                case elem_input :
                case elem_select :
                case elem_textarea :
                    validate_type < type_master < t_not_empty > > (nits, v); break; }
        if (good () && (v >= html_5_0) && form_bitset.test (e.get ()))
        {   ::std::string s (varied < tidy_string < t_name > > :: get_string ());
            if (compare_no_case ("_charset_", s))
                nits.pick (nit_special_name, ed_50, "4.10.19.1 Naming form controls: the name attribute", es_comment, ec_type, "note that ", quote (s), " causes special behaviour");
            if (compare_no_case ("isindex", s))
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
    {   if ((e_ != elem_a) && (e_ != elem_map)) return false;
        return check_id_defined < type_master < t_id > > (nits, v, ids, pe); } };

template < > struct type_master < t_notation > : varied < tidy_string < t_notation > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            if (v.mjr () > 3) validate_type < type_master < t_mathnotation > > (nits, v);
            else validate_type < type_master < t_notations > > (nits, v); } };

template < > struct type_master < t_open > : varied < tidy_string < t_open > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (! e.is_math ()) validate_type < type_master < t_html_boolean > > (nits, v); } };

template < > struct type_master < t_operator > : varied < tidy_string < t_operator > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_fecomposite :
                    validate_type < type_master < t_composite_operator > > (nits, v); break;
                case elem_femorphology :
                    validate_type < type_master < t_morphology_operator > > (nits, v); } } };

template < > struct type_master < t_overflow > : varied < tidy_string < t_overflow > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.is_math ()) validate_type < type_master < t_math_overflow > > (nits, v);
            else validate_type < type_master < t_svg_overflow > > (nits, v); } };

template < > struct type_master < t_preload > : varied < tidy_string < t_preload > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   assert (v >= html_4_0);
        if (good () || empty ())
            if (v <= html_4_1) validate_type < type_master < t_html_boolean > > (nits, v);
            else if (good ()) validate_type < type_master < t_preload5 > > (nits, v); } };

template < > struct type_master < t_rap > : varied < tidy_string < t_rap > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_ul :
                    validate_type < type_master < t_wrap3 > > (nits, v);
                    break;
                case elem_dir :
                case elem_menu :
                    if ((v == html_plus) || (v == html_3_0))
                    {   validate_type < type_master < t_wrap3 > > (nits, v);  return; }
                    // drop through
                default :
                    validate_type < type_master < t_integer > > (nits, v); break; } } };

template < > struct type_master < t_rowscols > : varied < tidy_string < t_rowscols > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_textarea :
                    validate_type < type_master < t_positive > > (nits, v); break;
                case elem_frameset :
                    validate_type < type_master < t_measures > > (nits, v); break; } } };

template < > struct type_master < t_shape > : varied < tidy_string < t_shape > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            switch (v.mjr ())
            {   case 1 :    return;
                case 2 :    validate_type < type_master < t_shape_rcp > > (nits, v); return;
                case 3 :    if (v.mnr () == 0) validate_type < type_master < t_shape3 > > (nits, v);
                            else validate_type < type_master < t_shape_rcp > > (nits, v);
                            return;
                case 4 :    validate_type < type_master < t_shape4 > > (nits, v); return;
                default :   validate_type < type_master < t_shape7 > > (nits, v); } } };

template < > struct type_master < t_size > : varied < tidy_string < t_size > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
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

template < > struct type_master < t_style > : varied < tidy_string < t_style > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            if (v == html_plus) validate_type < type_master < t_plusstyle > > (nits, v);
            else validate_type < type_master < t_css > > (nits, v); } };

template < > struct type_master < t_measure_or_more > : varied < tidy_string < t_measure_or_more > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (v.svg ())
            {   case sv_1_1 :
                case sv_1_2_tiny :
                case sv_1_2_full :
                    switch (e)
                    {   case elem_altglyph :
                        case elem_text :
                        case elem_tref :
                        case elem_tspan : validate_type < type_master < t_measures > > (nits, v); return;
                        default : break; }
                    // drop thru
                default : validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_rotate > : varied < tidy_string < t_rotate > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e == elem_animatemotion)
                validate_type < type_master < t_rotate_anim > > (nits, v);
            else validate_type < type_master < t_reals > > (nits, v); } };

template < > struct type_master < t_type > : varied < tidy_string < t_type > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e.get ())
            {   case elem_animatetransform :
                    validate_type < type_master < t_transform_anim > > (nits, v); break;
                case elem_button :
                    validate_type < type_master < t_button > > (nits, v); break;
                case elem_command :
                    validate_type < type_master < t_command > > (nits, v); break;
                case elem_fecolourmatrix :
                    validate_type < type_master < t_matrix_type > > (nits, v); break;
                case elem_fefunca :
                case elem_fefuncb :
                case elem_fefuncg :
                case elem_fefuncr :
                    if (v.svg () < sv_1_1)
                        validate_type < type_master < t_svg_type > > (nits, v);
                    else
                        validate_type < type_master < t_svg_type_11 > > (nits, v);
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
                    validate_type < type_master < t_menutype > > (nits, v); break;
                case elem_menuitem :
                    validate_type < type_master < t_menuitem > > (nits, v); break;
                case elem_ol :
                    validate_type < type_master < t_listtype > > (nits, v); break;
                case elem_a :
                case elem_link :
                case elem_map :
                case elem_object :
                case elem_param :
                case elem_source :
                case elem_style :
                    validate_type < type_master < t_mime > > (nits, v); break;
                case elem_script :
                    if (v >= html_5_2)
                        if (compare_no_case ("module", varied < tidy_string < t_type > > :: get_string ()))
                        {   varied < tidy_string < t_type > > :: type_ = static_cast < ::std::size_t > (mime_faux_module);
                            break; }
                    validate_type < type_master < t_mime > > (nits, v); break;
                case elem_spacer :
                    validate_type < type_master < t_spacer > > (nits, v); break; } } };

template < > struct type_master < t_valign > : varied < tidy_string < t_valign > >
{   void validate (nitpick& nits, const html_version& v, const e_element , const ::std::string& )
    {   if (good () || empty ())
            if (v == html_3_0) validate_type < type_master < t_valign3 > > (nits, v);
            else validate_type < type_master < t_valign_tmb > > (nits, v); } };

template < > struct type_master < t_value > : varied < tidy_string < t_value > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (e.get () == elem_li)
            if (empty ()) nits.pick (nit_empty, es_error, ec_attribute, "value expected");
            else validate_type < type_master < t_integer > > (nits, v); } };

template < > struct type_master < t_values > : varied < tidy_string < t_values > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if (e.get () == elem_fecolourmatrix) return;  // process separately
            else if ((elem :: categories (e) & EF_SVG_ANIM) != 0)
                validate_type < type_master < t_svg_values > > (nits, v);
            else validate_type < type_master < t_matrix_values > > (nits, v); } };

template < > struct type_master < t_vectoreffect > : varied < tidy_string < t_vectoreffect > >
{   void validate (nitpick& nits, const html_version& v, const elem& , const ::std::string& )
    {   if (empty ())
            nits.pick (nit_vector_effect, es_error, ec_attribute, "vector effect should not be empty");
        else if (good ())
            switch (v.svg ())
            {   case sv_1_2_tiny :
                case sv_1_2_full :
                    validate_type < type_master < t_vectoreffect_12 > > (nits, v); break;
                case sv_2_0 :
                    validate_type < type_master < t_vectoreffect_2 > > (nits, v); break;
                default :
                    nits.pick (nit_vector_effect, es_error, ec_attribute, "vector effect requires SVG 1.2 or SVG 2.0");
                    break; } } };

template < > struct type_master < t_version > : varied < tidy_string < t_version > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () && (e.get () == elem_svg))
        {   type_master < t_svg_version > sv;
            sv.set_value (nits, v, varied < tidy_string < t_version > > :: get_string ());
            if (sv.good ())
            {   ::std::string svgv ("SVG ");
                switch (sv.get ())
                {   case sv_1_0 : svgv += "1.0"; break;
                    case sv_1_1 : svgv += "1.1"; break;
                    case sv_1_2_tiny : svgv += "1.2 tiny"; break;
                    case sv_1_2_full : svgv += "1.2 full"; break;
                    default : assert (false); svgv += "version not "; } // illegal value for t_svg_version
                svgv += " recognised";
                nits.pick (nit_svg_version, es_info, ec_type, svgv); } } } };

// R.I.P. David Senior, 'vid', murdered in Prague, 1996
template < > struct type_master < t_vid > : varied < tidy_string < t_vid > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            if ((elem :: categories (e) & EF_SVG_ANIM) != 0)
                validate_type < type_master < t_generic > > (nits, v);
            else validate_type < type_master < t_idref > > (nits, v); } };

template < > struct type_master < t_depth > : varied < tidy_string < t_depth > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e)
            {   case elem_mspace :
                    validate_type < type_master < t_vunit > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudo > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_height > : varied < tidy_string < t_height > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e)
            {   case elem_mspace :
                    validate_type < type_master < t_vunit > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudo > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_lspace > : varied < tidy_string < t_lspace > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e)
            {   case elem_mo :
                    validate_type < type_master < t_mathspace > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudonamedspace > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };

template < > struct type_master < t_width > : varied < tidy_string < t_width > >
{   void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& )
    {   if (good () || empty ())
            switch (e)
            {   case elem_mspace :
                    validate_type < type_master < t_mathspace > > (nits, v); break;
                case elem_mpadded :
                    validate_type < type_master < t_pseudonamedspace > > (nits, v); break;
                case elem_mtable :
                    validate_type < type_master < t_mathspaceauto > > (nits, v); break;
                default :
                    validate_type < type_master < t_measure > > (nits, v); } } };
