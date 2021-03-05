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

#include "main/standard.h"
#include "element/element.h"
#include "webpage/page.h"
#include "attribute/attribute_classes.h"

void element::examine_section ()
{   if (node_.version ().is_5 ())
    {   if (w3_minor_5 (node_.version ()) > 0)
            check_ancestors (tag (), empty_element_bitset | elem_dt); } }

void element::examine_script ()
{   if (node_.version ().mjr () < 5) return;
    check_ancestors (elem_script, element_bit_set (elem_script));
    bool datablock = false, module = false;
    if (a_.known (a_type))
    {   if (a_.good (a_charset))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "CHARSET should be omitted when using <SCRIPT> TYPE");
        if (a_.good (a_type))
        {   e_mimetype mt (static_cast < e_mimetype > (a_.type (a_type)));
            switch (mt)
            {   case mime_text_plain :
                case mime_text_xml :
                case mime_application_octet_stream :
                case mime_application_xml :
                    if (node_.version () < html_jul18)
                        pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, quote (type_master < t_mime > :: name (mt)), " is not a scripting language");
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
                        pick (nit_bad_script, ed_52, "4.12.1 The script element", es_info, ec_element, "omit the TYPE attribute for javascript");
                    break;
                case mime_faux_module :
                    module = true;
                    break;
                default :
                    {   uint64_t flags = type_master < t_mime > :: flags (mt);
                        if ((flags & MIME_SCRIPT) == MIME_SCRIPT)
                            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_info, ec_element, quote (type_master < t_mime > :: name (mt)), " may not be supported by all browsers on all systems");
                        else if (node_.version () < html_jul20)
                        {   pick (nit_bad_script, ed_50, "4.11.1 The script element", es_info, ec_element, quote (type_master < t_mime > :: name (mt)), " may not be processed");
                            datablock = true; } }
                    break; } } }
    if (datablock)
        if (a_.good (a_async) || a_.good (a_async) || a_.good (a_charset) || a_.known (a_crossorigin) ||
            a_.good (a_defer) || a_.good (a_integrity) || a_.good (a_nomodule) || a_.known (a_numberonce) ||
            a_.good (a_referrerpolicy) || a_.good (a_src))
        pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "no attribute but TYPE should be used with data blocks");
    if (module)
    {   if (a_.known (a_charset) && (node_.version () <= html_5_3))
            pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "do not use CHARSET when TYPE='module' (which must be " UTF_8 ")");
        if (a_.known (a_nomodule) && (node_.version () > html_5_3))
            pick (nit_bad_script, ed_jul20, "4.12.1 The script element", es_error, ec_element, "NOMODULE is daft when TYPE='module'");
        if (a_.known (a_defer))
            pick (nit_bad_script, ed_52, "4.12.1 The script element", es_error, ec_element, "DEFER has no effect when TYPE='module'"); }
    if (! a_.known (a_src))
    {   if (a_.known (a_charset) && (node_.version () <= html_5_3))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "CHARSET requires SRC");
        if (a_.known (a_defer))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "DEFER requires SRC");
        if (a_.known (a_integrity))
            pick (nit_bad_script, ed_jul20, "4.12.1 The script element", es_error, ec_element, "INTEGRITY requires SRC");
        if (a_.known (a_async))
            pick (nit_bad_script, ed_50, "4.11.1 The script element", es_error, ec_element, "ASYNC requires SRC"); } }

void element::examine_select ()
{   if (node_.version ().mjr () < 5) return;
    no_anchor_daddy ();
    int size = 1;
    bool multiple = a_.known (a_multiple);
    bool required = a_.known (a_required);
    if (a_.good (a_size)) size = a_.get_int (a_size);
    else if (multiple) size = 4;
    if (a_.known (a_role) && (w3_minor_5 (node_.version ()) >= 2))
    {   e_aria_role r = static_cast < e_aria_role > (a_.get_int (a_role));
        if (multiple || (size > 1))
        {   if (r == role_combobox)
                pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "do not set ROLE to 'combobox', it is the default");
            else if (r == role_menu)
                pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "with MULTIPLE and SIZE greater than one, ARIA cannot be 'menu'"); }
        else if (r == role_combobox)
            pick (nit_input_bad_aria, ed_52, "4.10.7 The select element", es_error, ec_attribute, "do not set ROLE to 'listbox', it is the default"); }
    if (required && (! multiple) && (size == 1) && (has_child ()))
    {   uint64_t placeholder = 0;
        int selectedness = 0;
        for (element_ptr p = child_; p != nullptr; p = p -> sibling_)
            if (! p -> node_.is_closure ())
                switch (p -> tag ())
                {   case elem_optgroup :
                        if (p -> descendant_attributes_.test (a_selected))
                            ++selectedness;
                        break;
                    case elem_option :
                        if ((! p -> a_.known (a_value)) || p -> a_.empty (a_value) || p -> a_.get_string (a_value).empty ())
                            placeholder = p -> uid ();
                        else if (p -> a_.known (a_selected))
                            ++selectedness;
                        break;
                    default : break; }
        if (placeholder == 0)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "the first child <OPTION> that is not in an <OPTGROUP> should have an empty VALUE");
        if (selectedness == 0)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "one <OPTION> with a non-empty VALUE should have SELECTED specified");
        else if (selectedness > 1)
            pick (nit_bad_select, ed_50, "4.10.7 The select element", es_warning, ec_attribute, "<SELECT> has no MULTIPLE yet multiple child <OPTION>s have SELECTED specified"); } }

void element::examine_share ()
{   if (! a_.known (a_href))
        pick (nit_requires_href, ed_math_3, "4.2.7.1 The share element", es_error, ec_attribute, "<SHARE> requires an HREF");
    else
    {   url u (a_.get_x < attr_href > ());
        if (! u.is_simple_id ()) return;
        ::std::string i (u.id ());
        if (get_ids ().has_id (i))
        {   element* pide = get_ids ().get_element (i);
            if (pide != nullptr)
                for (element* p = parent_; p != nullptr; p = p -> parent_)
                    if (p == pide)
                    {   pick (nit_bad_share, ed_math_3, "4.2.7.2 An Acyclicity Constraint", es_error, ec_attribute, quote (i), " is recursive");
                        break; } } } }

void element::examine_source ()
{   bool has_src = a_.known (a_src);
    bool has_type = a_.known (a_type);
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
        {   uint64_t f = mt.flags ();
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
            if (is_standard_element (c -> tag ()) && (! c -> node_.is_closure ()))
                if (header_bitset.test (c -> tag ()))
                    if (! heading) heading = true;
                    else
                    {   pick (nit_summary_header, ed_51, "4.11.2 The summary element", es_error, ec_element, "<SUMMARY> can only have one child header element");
                        break; } }

void element::examine_svg ()
{   bool ancestor = ancestral_elements_.test (elem_svg);
    switch (node_.version ().svg_version ())
    {   case sv_1_1 :
        case sv_2_0 :
            if (! ancestor) if (a_.known (a_x) || a_.known (a_y))
                pick (nit_svg_xy, ed_svg_1_1, "5.1.2 The 'svg' element", es_warning, ec_element, "X and Y are ignored on outermost <SVG> elements");
            break;
        case sv_1_2_tiny:
        case sv_1_2_full :
            if (ancestor)
                pick (nit_svg_ancestor, ed_svg_1_2_tiny, "5.1.1 ... the 'svg' element: overview", es_error, ec_element, "An <SVG> cannot descend from another <SVG>");
            break;
        default : break; } }

void element::examine_svg_shape ()
{   if (node_.version ().svg_version () != sv_1_0) return;
    if (has_child ())
        pick (nit_closed_shape, ed_svg_1_0, "12 Other Vector Graphic Shapes", es_error, ec_element, "in SVG 1.0, <", elem :: name (tag ()), "> cannot have descendants"); }

void element::examine_switch ()
{   if (! has_child ())
    {   pick (nit_switch, es_comment, ec_element, "bit of a useless <SWITCH>, that"); return; }
    if ((node_.version ().svg_version () != sv_1_2_tiny) && (node_.version ().svg_version () != sv_1_2_full)) return;
    uint64_t cat = (elem :: categories (parent_ -> tag ()) & EF_SVG_CATMASK);
    bool nofaux = false;
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
    {   e_element ct = c -> tag ();
        nofaux = nofaux || is_standard_element (ct);
        uint64_t kitten = elem :: categories (ct);
        if ((kitten & cat) == 0)
        {   pick (nit_switch, es_comment, ec_element, "the <SWITCH> beneath <", elem::name (parent_ -> tag ()), "> has an outside context problem with <", elem::name (ct), ">"); return; } }
    if (! nofaux) pick (nit_switch, es_comment, ec_element, "bit of a useless <SWITCH>, that"); }

void element::examine_style ()
{   if (node_.version () > html_plus)
        if (! a_.known (a_type) || (a_.get_string (a_type) == CSS_TYPE))
            context.css ().parse (nits (), node_.version (), text ()); }
