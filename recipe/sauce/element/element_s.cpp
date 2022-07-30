/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

#include "main/standard.h"
#include "element/element.h"
#include "webpage/page.h"
#include "attribute/attribute_classes.h"

void element::examine_sarcasm ()
{   if (! nitpick::sarcasm ())
    {   pick (nit_sarcasm, es_info, ec_element, "contact your favourite " PROG " vendor now for bulk discount on &lt; and &gt;");
        nitpick::sarcasm (true); } }

void element::examine_script ()
{   if (! node_.version ().is_5 ()) return;
    check_ancestors (elem_script, element_bit_set (elem_script));
    bool datablock = false, module = false, jsld = false;
    if (! a_.known (a_type) || a_.empty (a_type))
        pick (nit_script, ed_50, "4.11.1 The script element", es_comment, ec_element, "this should be treated as ECMAscript / Javascript");
    else
    {   if (a_.good (a_charset))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "CHARSET should be omitted when using <SCRIPT> TYPE");
        if (a_.good (a_type))
        {   const e_mimetype mt (static_cast < e_mimetype > (a_.type (a_type)));
            switch (mt)
            {   case mime_text_plain :
                case mime_text_xml :
                case mime_application_octet_stream :
                case mime_application_xml :
                    if (node_.version () < html_jul18)
                        pick (nit_script, ed_50, "4.11.1 The script element", es_info, ec_element, quote (type_master < t_mime > :: name (mt)), " is not a scripting language");
                    else
                    {   pick (nit_script, ed_52, "4.12.1 The script element", es_comment, ec_element, "this will be treated as a block of datat");
                        datablock = true; }
                    break;
                case mime_application_ecmascript :
                case mime_application_javascript :
                case mime_application_x_ecmascript :
                case mime_application_x_javascript :
                case mime_text_ecmascript :
                case mime_text_javascript :
                case mime_text_javascript_x :
                case mime_text_javascript10 :
                case mime_text_javascript11 :
                case mime_text_javascript12 :
                case mime_text_javascript13 :
                case mime_text_javascript14 :
                case mime_text_javascript15 :
                case mime_text_jscript :
                case mime_text_livescript :
                case mime_text_x_ecmascript :
                case mime_text_x_javascript :
                    if (node_.version () >= html_5_1)
                        pick (nit_script, ed_52, "4.12.1 The script element", es_info, ec_element, "omit the TYPE attribute for javascript");
                    break;
                case mime_faux_module :
                    module = true;
                    break;
                case mime_application_ld_json :
                    jsld = context.jsonld ();
                    break;
                default :
                    {   const flags_t flags = type_master < t_mime > :: flags (mt);
                        if ((flags & MIME_SCRIPT) == MIME_SCRIPT)
                            pick (nit_script, ed_50, "4.11.1 The script element", es_info, ec_element, quote (type_master < t_mime > :: name (mt)), " may not be supported by all browsers on all systems");
                        else
                        {   pick (nit_script, ed_50, "4.11.1 The script element", es_info, ec_element, quote (type_master < t_mime > :: name (mt)), " may not be processed");
                            datablock = true; } }
                    break; } } }
    if (datablock)
        if (a_.good (a_async) || a_.good (a_charset) || a_.known (a_crossorigin) ||
            a_.good (a_defer) || a_.good (a_integrity) || a_.good (a_nomodule) || a_.known (a_numberonce) ||
            a_.good (a_referrerpolicy) || a_.good (a_src))
        pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "no attribute but TYPE should be used with data blocks");
    if (module)
    {   if (a_.known (a_charset) && (node_.version () <= html_5_3))
            pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "do not use CHARSET when TYPE='module' (which must be " UTF_8 ")");
        if (a_.known (a_nomodule) && (node_.version () > html_5_3))
            pick (nit_bad_script, ed_jul20, "4.12.1 The script element", es_error, ec_element, "NOMODULE is dubious when TYPE='module'");
        if (a_.known (a_defer))
            pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "DEFER has no effect when TYPE='module'"); }
    if (a_.known (a_src))
    {   if (! is_whitespace (node_.text ()))
            pick (nit_script, ed_jan10, "1.10.2 Syntax errors", es_info, ec_element, "If <SCRIPT> has a SRC attribute, its content is ignored"); }
    else
    {   if (a_.good (a_charset))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "CHARSET requires SRC");
        if (a_.known (a_defer))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "DEFER requires SRC");
        if (a_.known (a_integrity))
            pick (nit_bad_script, ed_jul20, "4.12.1 The script element", es_error, ec_element, "INTEGRITY requires SRC");
        if (a_.known (a_async))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "ASYNC requires SRC"); }
    if (jsld) page_.append_jsonld (content ());
    if (has_child ()) report_script_comment (child_); }

bool element::report_script_comment (element_ptr child)
{   for (element_ptr p = child; p != nullptr; p = p -> sibling_)
    {   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
        if (! p -> node_.is_closure ())
            if (p -> tag () == elem_faux_text)
            {   if ((p -> node_.text ().find ("<!--") != ::std::string::npos) ||
                    (p -> node_.text ().find ("<script") != ::std::string::npos) ||
                    (p -> node_.text ().find ("</script") != ::std::string::npos))
                {   pick (nit_bad_script, ed_jan14, "4.12.1.2 Restrictions for contents of script elements", es_warning, ec_element, "within the <SCRIPT> content, replace '<!--', '<script', and '</script', even if its quoted, with '<\\!--', '<\\script', and '<\\/script', respectively");
                    return true; } }
            else if (p -> has_child ())
                if (report_script_comment (p -> child_)) return true; }
    return false; }

void element::examine_section ()
{   if (node_.version ().is_5 ())
    {   if (w3_minor_5 (node_.version ()) > 0)
            check_ancestors (tag (), empty_element_bitset | elem_dt); } }

void element::examine_select ()
{   if (node_.version ().mjr () < 5) return;
    no_anchor_daddy ();
    int size = 1;
    const bool multiple = a_.known (a_multiple);
    const bool required = a_.known (a_required);
    if (a_.good (a_size)) size = a_.get_int (a_size);
    else if (multiple) size = 4;
    if (a_.known (a_role) && (w3_minor_5 (node_.version ()) >= 2))
    {   const e_aria_role r = static_cast < e_aria_role > (a_.get_int (a_role));
        if (multiple || (size > 1))
        {   if (r == role_combobox)
                pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "do not set ROLE to 'combobox', it is the default");
            else if (r == role_menu)
                pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "with MULTIPLE and SIZE greater than one, ARIA cannot be 'menu'"); }
        else if (r == role_combobox)
            pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "do not set ROLE to 'listbox', it is the default"); }
    if (required && (! multiple) && (size == 1) && has_child ())
    {   uint64_t selected = 0;
        int selectedness = 0;
        bool firstempty = false, first = true;
        for (element_ptr p = child_; p != nullptr; p = p -> sibling_)
        {   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
            if (! p -> node_.is_closure ())
                switch (p -> tag ())
                {   case elem_optgroup :
                        if (p -> descendant_attributes_.test (a_selected))
                            ++selectedness;
                        break;
                    case elem_option :
                        if (p -> a_.known (a_selected))
                            if (selected == 0)
                                selected = p -> uid ();
                        if ((p -> a_.known (a_value) && (p -> a_.empty (a_value) || trim_the_lot_off (p -> a_.get_string (a_value)).empty ())) || trim_the_lot_off (p -> text ()).empty ())
                        {   if (first) firstempty = true; }
                        else if (p -> a_.known (a_selected)) ++selectedness;
                        first = false;
                        break;
                    default : break; } }
        if (! firstempty)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "the first child <OPTION> that is not in an <OPTGROUP> should have an empty VALUE");
        if (selectedness == 0)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "one <OPTION> with a non-empty VALUE should have SELECTED specified");
        else if (selectedness > 1)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "<SELECT> has no MULTIPLE yet multiple child <OPTION>s have been SELECTED"); } }

void element::examine_share ()
{   if (! a_.known (a_href) && ! a_.known (a_src))
        pick (nit_requires_href, ed_math_3, "4.2.7.1 The share element", es_error, ec_attribute, "<SHARE> requires a SRC or an HREF");
    else
    {   ::std::string i;
        if (a_.known (a_src))
        {   url u (a_.get_x < attr_src > ());
            if (! u.is_simple_id ()) return;
            i = u.id (); }
        else if (a_.known (a_href))
        {   url u (a_.get_x < attr_href > ());
            if (! u.is_simple_id ()) return;
            i = u.id (); }
        if (get_ids ().has_id (i))
        {   const element* const pide = get_ids ().get_element (i);
            if (pide != nullptr)
                for (element* p = parent_; p != nullptr; p = p -> parent_)
                {   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
                    if (p == pide)
                    {   pick (nit_bad_share, ed_math_3, "4.2.7.2 An Acyclicity Constraint", es_error, ec_attribute, quote (i), " is recursive");
                        break; } } } } }

void element::examine_source ()
{   const bool has_src = a_.known (a_src);
    const bool has_type = a_.known (a_type);
    if (has_src && has_type) check_extension_compatibility (nits (), node_.version (), a_.get_string (a_type), a_.get_urls (a_src), true);
    if (ancestral_elements_.test (elem_picture))
    {   if (! a_.known (a_srcset))
            pick (nit_bad_srcset, ed_52, "4.7.4. The source element", es_error, ec_element, "SRCSET is required when <SOURCE> descends from <PICTURE>");
        if (a_.known (a_src))
            pick (nit_saucy_source, ed_52, "4.7.4. The source element", es_warning, ec_element, "SRC has no meaning when <SOURCE> descends from <PICTURE>"); }
    else
    {   if (! has_src)
            pick (nit_src_required, ed_52, "4.7.4. The source element", es_error, ec_element, "SRC attribute is required when <SOURCE> descends from a media element");
        if (a_.known (a_srcset) || a_.known (a_sizes) || a_.known (a_media))
            pick (nit_saucy_source, ed_52, "4.7.4. The source element", es_warning, ec_element, "SRCSET, SIZES and MEDIA have no meaning when <SOURCE> is not a child of <PICTURE>");
        nitpick nuts;
        type_master < t_mime > mt;
        ::std::string s (a_.get_string (a_type));
        mt.set_value (nuts, node_.version (), s);
        if (mt.good ())
        {   const flags_t f = mt.flags ();
            if ((f & MIME_MULTIPART) == 0)
            {   if (ancestral_elements_.test (elem_audio) && ((f & MIME_AUDIO) == 0))
                    pick (nit_mime, es_warning, ec_attribute, "expecting an audio mimetype");
                if (ancestral_elements_.test (elem_video) && ((f & MIME_VIDEO) == 0))
                    pick (nit_mime, es_warning, ec_attribute, "expecting a video mimetype"); } } } }

void element::examine_summary ()
{   if ((node_.version () < html_5_1) || (node_.version () >= html_jul20)) return;
    bool heading = false;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (is_standard_element (c -> tag ()) && (! c -> node_.is_closure ()))
                if (header_bitset.test (c -> tag ()))
                    if (! heading) heading = true;
                    else
                    {   pick (nit_summary_header, ed_51, "4.11.2 The summary element", es_error, ec_element, "<SUMMARY> can only have one child header element");
                        break; } } }

void element::examine_svg ()
{   const bool ancestor = ancestral_elements_.test (elem_svg);
    if (a_.good (a_contentscripttype))
    {   const e_mimetype em = a_.get_x < attr_contentscripttype > ();
        check_mimetype_family (nits (), node_.version (), em, MIME_SCRIPT, attr::name (a_contentscripttype)); }
    if (a_.good (a_contentstyletype))
    {   const e_mimetype em = a_.get_x < attr_contentstyletype > ();
        check_mimetype_family (nits (), node_.version (), em, MIME_STYLE, attr::name (a_contentstyletype));
        if (context.html_ver () >= html_jan18)
            if (em == mime_text_css)
                pick (nit_style_fixed, es_info, ec_attribute, context.html_ver ().name (), " requires CSS, so ", attr::name (a_contentstyletype), " is redundant");
            else
                pick (nit_style_fixed, es_warning, ec_attribute, context.html_ver ().name (), " requires CSS, so ", quote (a_.get_string (a_contentstyletype)), " is problematic"); }
    if (a_.known (a_version))
    {   const e_svg_version sv = static_cast < e_svg_version > (a_.get_int (a_version));
        e_svg_baseprofile prof = sbp_none;
        if (a_.known (a_baseprofile)) prof = static_cast < e_svg_baseprofile > (a_.get_int (a_baseprofile));
        ::std::string svg ("SVG ");
        switch (sv)
        {   case sv_1_0 : svg += "1.0"; break;
            case sv_1_1 : svg += "1.1"; break;
            case sv_1_2_full :
            case sv_1_2_tiny : svg += "1.2/";
                if (prof == sbp_full) svg += "full";
                else svg += "tiny";
                break;
            case sv_2_0 : svg += "2.0"; break;
            case sv_2_1 : svg += "2.1"; break;
            default : svg += "version not"; break; }
        svg += " recognised (";
        svg += node_.version ().report ();
        svg += ")";
        if (sv == sv_none) pick (nit_svg_version, es_error, ec_attribute, svg);
        else pick (nit_svg_version, es_info, ec_attribute, svg); }
    switch (node_.version ().svg_version ())
    {   case sv_1_1 :
        case sv_2_0 :
        case sv_2_1 :
            if (! ancestor) if (a_.known (a_x) || a_.known (a_y))
                pick (nit_svg_xy, ed_svg_1_1, "5.1.2 The 'svg' element", es_warning, ec_element, "X and Y are ignored on outermost <SVG> elements");
            break;
        case sv_1_2_tiny:
        case sv_1_2_full :
            if (ancestor)
                pick (nit_svg_ancestor, ed_svg_1_2_tiny, "5.1.1 ... the 'svg' element: overview", es_error, ec_element, "An <SVG> cannot descend from another <SVG>");
            break;
        default : break; } }

void element::examine_switch ()
{   if (! has_child ())
    {   pick (nit_switch, es_comment, ec_element, "bit of a useless <SWITCH>, that"); return; }
    if (node_.version ().is_svg_12 ()) return;
    const flags_t cat = (elem :: categories (parent_ -> tag ()) & EF_SVG_CATMASK);
    bool nofaux = false;
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        const e_element ct = c -> tag ();
        nofaux = nofaux || is_standard_element (ct);
        const flags_t kitten = elem :: categories (ct);
        if ((kitten & cat) == 0)
        {   pick (nit_switch, es_comment, ec_element, "the <SWITCH> beneath <", elem::name (parent_ -> tag ()), "> has an outside context problem with <", elem::name (ct), ">"); return; } }
    if (! nofaux) pick (nit_switch, es_comment, ec_element, "bit of a useless <SWITCH>, that"); }

void element::examine_style ()
{   if (node_.version () > html_plus)
        if (! a_.known (a_type) || (a_.get_string (a_type) == CSS_TYPE))
        {   VERIFY_NOT_NULL (css_cache.get (), __FILE__, __LINE__);
            css_cache -> parse (nits (), node_.version (), text ()); } }
