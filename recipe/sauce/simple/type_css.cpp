/*
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "parser/html_version.h"
#include "type/type.h"
#include "webpage/page.h"
#include "element/element.h"
#include "css/arguments.h"
#include "parser/text.h"

bool process_css (nitpick& nits, const html_version& v, const ::std::string& s, element* e)
{   try
    {   if (e == nullptr)
            nits.pick (nit_css_syntax, es_catastrophic, ec_type, "null element processing STYLE");
        else
        {   page& p = e -> get_page ();
            if (! p.style_css ())
                nits.pick (nit_style_not_css, es_comment, ec_type, PROG " can only check style type " CSS_TYPE);
            else if (context.load_css () && (context.css_version () >= css_1))
                p.css ().parse (s, v, e -> namespaces (), e -> ancestral_elements (), false, e -> line (), e -> tag ()); } }
    catch (const ::std::system_error& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "system exception processing STYLE: ", ex.what ()); }
    catch (const ::std::exception& ex)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "exception processing STYLE: ", ex.what ()); }
    catch (...)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_type, "unknown exception processing STYLE"); }
    return nits.worst () < es_warning; }

e_status set_css_all_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! compare_no_case (s, "all"))
    {   if (v.css_version () == css_2_0)
            nits.pick (nit_unrecognised_value, es_comment, ec_type, quote (s), ": is not 'all'"); }
    else if (v.css_version () != css_2_0)
        nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'all' requires CSS 2.0 (only)");
    else return s_good;
    return s_invalid; }

e_status set_css_content_name_value (nitpick& , const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    g.note_str (gst_content_name, s);
    return s_good; }

e_status set_css_font_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   if (sss.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font specification cannot be empty");
    else
    {   nitpick gnats;
        ::std::string gs (sss);
        if (test_value < t_font_enum > (gnats, v, gs))
        {   nits.merge (gnats);
            return s_good; }
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
        if (res) return s_good; }
    return s_invalid; }

e_status set_css_font_stretch_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "font-stretch cannot be empty");
    else
    {   nitpick nuts;
        if (context.css_font () >= 4)
            if (test_value < t_percent > (nuts, v, s))
            {   nits.merge (nuts);
                return s_good; }
        if (test_value < t_svg_fontstretch > (nits, v, s)) return s_good;
        nits.merge (nuts); }
    return s_invalid; }

e_status set_css_font_variant_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font variant cannot be empty");
    else
    {   if (context.css_font () >= 4)
        {   if (test_value < t_css_font_variant_4 > (nits, v, s)) return s_good; }
        if (context.css_font () == 3)
        {   if (test_value < t_font_variant_2 > (nits, v, s)) return s_good; }
        else if (test_value < t_svg_fontvariant > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_font_weights_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a font weight cannot be empty");
    else
    {   if (context.css_font () >= 4)
        {   if (test_value < t_css_font_weight_4 > (nits, v, s)) return s_good; }
        else if (test_value < t_css_font_weight > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_frame_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a frame name cannot be empty");
    else
    {   if (s.at (0) != '_') return s_good;
        if (compare_no_case (s, "_parent") || compare_no_case (s, "_root")) return s_good;
        nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "to quote, a frame name 'MUST NOT start with the underscore \"_\" character'"); }
    return s_invalid; }

e_status set_css_id_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a id cannot be empty");
    else
    {   if (s.at (0) == '#') return s_good;
        nits.pick (nit_empty, ed_css_ui_4, "5.3. Keyboard control", es_error, ec_type, "An id selector is expected, which starts with '#'"); }
    return s_invalid; }

e_status set_css_inherit_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (! compare_no_case (s, "inherit"))
    {   if (v.css_version () >= css_2_0)
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), ": is not 'inherit'"); }
    else if (v.css_version () < css_2_0)
        nits.pick (nit_css_version, ed_css_20, "2.4 CSS design principles, Accessibility", es_warning, ec_type, quote (s), ": 'inherit' requires CSS 2.0 or later");
    else return s_good;
    return s_invalid; }

e_status set_css_nth_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, "pseudo class children specification cannot be empty");
    else if (s.find_first_not_of (DENARY "+-nN ") != ::std::string::npos)
        nits.pick (nit_css_syntax, ed_css_selectors_3, "6.6.5.2. :nth-child() pseudo-class", es_error, ec_type, quote (s), " contains invalid characters");
    else return s_good; // maybe do more checking!
     return s_invalid; }

e_status set_css_unicode_from_to_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
    else
    {   const ::std::size_t len = s.length ();
        if ((len <= 2) || (s.at (1) != '+') || ((s.at (0) != 'U') && (s.at (0) != 'u')))
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": must start with 'U+'");
        else if (len > 18)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": too big");
        else if (s.substr (2).find_first_not_of (HEX "-") != ::std::string::npos) 
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": not hexadecimal");
        else
        {   const ::std::string::size_type minus = s.find_first_of ("-");
            if ((minus < 3) || (minus >= len-1)) 
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": is not a pair of hexadecimal values"); 
            else if (s.substr (minus+1).find ('-') != ::std::string::npos)
                nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": bad hexadecimal range"); 
            else return s_good; } }
    return s_invalid; }

e_status set_css_unicode_wildcard_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a unicode value cannot be empty");
    else
    {   const ::std::size_t len = s.length ();
        if ((len <= 2) || (s.at (1) != '+') || ((s.at (0) != 'U') && (s.at (0) != 'u')))
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": must start with 'U+'");
        else if (s.substr (2).find_first_not_of (HEX "?") != ::std::string::npos)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": not hexadecimal with wildcards");
        else if (len > 10)
            nits.pick (nit_unicode_my_arse, ed_css_20, "15.3.3 Descriptors for Font Data Qualification: 'unicode-range'", es_error, ec_css, quote (s), ": too big");
        else return s_good; }
    return s_invalid; }

e_status set_fn_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ()) return s_good;
    if (! test_esii (sii_fn, s))
    {   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
        esii_scope esii (sii_fn, s);
        if (box -> get_page ().css ().parse_transform (interpret_string (nits, v, s), v, box -> namespaces (), box -> ancestral_elements (), false, box -> line ()))
            return s_good; }
    return s_invalid; }

e_status set_region_value (nitpick& , const html_version& , const ::std::string& s, element* box)
{   if (s.empty ()) return s_invalid;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    g.note_str (gst_region, s);
    return s_good; }

e_status set_stn_value (nitpick& nits, const html_version& , const vstr_t& vs, element* box)
{   if (vs.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    for (auto s : vs)
        if ((s.length () < 2) || (s.substr (0, 2) != "--"))
            nits.pick (nit_sda, es_error, ec_css, quote (s), ": Scroll-Driver Animation identifiers must start with double dash");
        else g.note_str (gst_scroll_anim, s);
    return s_good; }

e_status set_vtn_value (nitpick& nits, const html_version& , const vstr_t& vs, element* box)
{   if (vs.empty ()) return s_empty;
    VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    css_group& g = box -> get_page ().css ();
    for (auto s : vs)
        if ((s.length () < 2) || (s.substr (0, 2) != "--"))
            nits.pick (nit_vtn, es_error, ec_css, quote (s), ": View Transition identifiers must start with double dash");
        else g.note_str (gst_view, s);
    return s_good; }
