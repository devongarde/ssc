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

void element::examine_embed ()
{   if (node_.version ().mjr () < 5) return;
    no_anchor_daddy ();
    bool src_known = a_.known (a_src);
    bool type_known = a_.known (a_type);
    if (! src_known)
    {   if (a_.known (a_itemprop))
            pick (nit_bad_embed, ed_jul20, "4.8.6 The embed element", es_error, ec_attribute, "SRC is required when ITEMPROP is used on <EMBED>");
        if (! type_known)
            pick (nit_bad_embed, ed_jan21, "4.8.6 The embed element", es_info, ec_attribute, "with neither SRC nor TYPE attributes, this <EMBED> represents nothing"); }
    else if (a_.empty (a_src))
        pick (nit_bad_embed, ed_jan21, "4.8.6 The embed element", es_warning, ec_attribute, "is that empty SRC intended?");
    if (ancestral_elements_.test (elem_audio) || ancestral_elements_.test (elem_video))
        pick (nit_bad_embed, ed_jan21, "4.8.6 The embed element", es_info, ec_attribute, "when <EMBED> is a child of <AUDIO> or <VIDEO>, it represents nothing");
    if (ancestral_elements_.test (elem_object))
        pick (nit_bad_embed, ed_jan21, "4.8.6 The embed element", es_comment, ec_attribute, "when <EMBED> is a child of <OBJECT>, it is inactive unless <OBJECT> displays its fallback content");
    if (src_known && type_known) check_extension_compatibility (nits (), node_.version (), a_.get_string (a_type), a_.get_urls (a_src), true); }

void element::examine_equation ()
{   if (node_.version ().math () != math_2) return;
    if (tag () == elem_reln) pick (nit_deprecated_element, ed_math_2, "4.4.2.2 Relation (reln)", es_warning, ec_element, "<RELN> is deprecated");
    uint64_t fl = 0;
    bool start = true;
    int args = 0;
    e_element op = elem_undefined;
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
        if (c -> node_.id ().is_math ())
            if (start)
            {   fl = c -> node_.id ().flags ();
                op = c -> tag ();
                start = false; }
            else
            {   if (node_.version ().math () > math_2)
                    switch (c -> tag ())
                    {   case elem_bvar :
                        case elem_bind :
                        case elem_condition :
                        case elem_lowlimit :
                        case elem_uplimit : continue;
                        default : break; }
                if (! c -> node_.is_closure ()) ++args; }
    if (start)
    {   pick (nit_operator_required, ed_math_2, "4.4.2.1 Apply (apply)", es_error, ec_element, "<", elem::name (tag ()), "> requires an operator");
        return; }
    if ((fl & EP_ARGS_COUNT_MASK) == 0) return;
    bool more = (fl & EP_ARGS_MORE) == EP_ARGS_MORE;
    bool none = (fl & EP_ARGS_0) == EP_ARGS_0;
    if (more && none) return;
    bool a1 = (fl & EP_ARGS_1) == EP_ARGS_1;
    bool a2 = (fl & EP_ARGS_2) == EP_ARGS_2;
    bool a3 = (fl & EP_ARGS_3) == EP_ARGS_3;
    switch (args)
    {   case 0 : if (none) return;
                 break;
        case 1 : if (a1) return;
                 break;
        case 2 : if (a2) return;
                 if (a1 && more) return;
                 break;
        case 3 : if (a3) return;
                 if (a1 && more) return;
                 if (a2 && more) return;
                 break;
        default : if (more) return;
                 break; }
    pick (nit_arg_count, ed_math_2, "4.4.2.1 Apply (apply)", es_error, ec_element, "<", elem::name (tag ()), "> has ", args, " arguments, which is wrong");
    ::std::string msg ("<");
    msg += elem::name (op);
    msg += "> expects";
    bool singular = true;
    if (none) { singular = false; msg += " 0"; }
    if (a1) { if (none) msg += " or"; msg += " 1"; }
    if (a2) { singular = false; if (a1) msg += " or"; msg += " 2"; }
    if (a3) { singular = false; if (a1 || a2) msg += " or"; msg += " 3"; }
    if (more) msg += " or more";
    msg += " argument";
    if (! singular) msg += "s";
    pick (nit_arg_count, ed_math_2, "4.4.2.1 Apply (apply)", es_info, ec_element, msg); }

void element::examine_fecolourmatrix ()
{   e_matrixtype mt = mt_matrix;
    if (a_.known (a_type)) mt = static_cast < e_matrixtype > (a_.get_int (a_type));
    bool vals = a_.known (a_values);
    if (mt == mt_luminance_alpha)
    {   if (vals) pick (nit_colour_matrix, ed_svg_1_1, "15.10 Filter primitive feColorMatrix", es_warning, ec_attribute, "when TYPE is luminance-alpha, VALUES should be omitted");
        return; }
    if (! vals)
    {   pick (nit_colour_matrix, ed_svg_1_1, "15.10 Filter primitive feColorMatrix", es_error, ec_attribute, "unless TYPE is luminance-alpha, VALUES is required");
        return; }
    switch (mt)
    {   case mt_matrix :
            test_value < t_matrix_values > (node_.nits (), page_.version (), a_.get_string (a_values));
            break;
        case mt_saturate :
            test_value < t_normalised > (node_.nits (), page_.version (), a_.get_string (a_values));
            break;
        case mt_hue_rotate :
            test_value < t_angle > (node_.nits (), page_.version (), a_.get_string (a_values));
            break;
        default :
            assert (false);
            break; } }

void element::examine_felighting ()
{   int cc = 0;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            switch (c -> tag ())
            {   case elem_fedistantlight :
                case elem_fepointlight :
                case elem_fespotlight : ++cc; break;
                default : break; }
    if (cc == 0) pick (nit_lighting, ed_svg_1_1, "15.14 / 15.22 Filter primitive lighting", es_error, ec_element, "Both <FEDIFFUSELIGHTING> and <FESPECULARLIGHTING> must have a child light source element");
    else if (cc > 1) pick (nit_lighting, ed_svg_1_1, "15.14 / 15.22 Filter primitive lighting", es_error, ec_element, "Both <FEDIFFUSELIGHTING> and <FESPECULARLIGHTING> can only have ONE child light source element"); }

void element::examine_fieldset ()
{   bool first = true;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (is_standard_element (c -> tag ()) && (! c -> node_.is_closure ()))
                if (first) first = false;
                else if (c -> tag () == elem_legend)
                {   pick (nit_fieldset_legend, ed_50, "4.10.16 The fieldset element", es_error, ec_element, "<LEGEND> can only be the first child of <FIELDSET>");
                    break; } };

void element::examine_figcaption ()
{   if ((node_.version ().is_5 ()) && (w3_minor_5 (node_.version ()) == 0))
        if (node_.has_previous () && node_.has_next ())
            pick (nit_figcaption_middle, ed_50, "4.4.12 The figcaption element", es_error, ec_element, "<FIGCAPTION> must be the first or last child of <FIGURE>"); }

void element::examine_figure ()
{   bool had_figcaption = false, first = true, last_was_fig = false;
    if (has_child () && (node_.version ().is_5 ()))
        if (node_.version ().whatwg () || (node_.version () == html_5_0))
            for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            {   e_element tag = c -> node_.tag ();
                if (is_standard_element (tag) && ! c -> node_.is_closure ())
                {   if (tag != elem_figcaption)
                    {   if (last_was_fig)
                            pick (nit_figcaption_first_last, ed_50, "4.4.11 The figure element", es_error, ec_element, "<FIGCAPTION> must be the first or last child of <FIGURE>");
                        last_was_fig = false; }
                    else if (had_figcaption)
                        pick (nit_too_many_figcaption, ed_50, "4.4.11 The figure element", es_error, ec_element, "<FIGURE> can only have one child <FIGCAPTION>");
                    else
                    {   had_figcaption = true;
                        if (! first) last_was_fig = true;  }
                    first = false; } } }

void element::examine_filter ()
{   if (node_.version ().svg () >= sv_1_1)
        examine_descendant_in (this); }

void element::examine_fn ()
{   e_mathversion mv = node_.version ().math_version ();
    if (mv == math_none) mv = page_.version ().math_version ();
    if (mv < math_3) return;
    pick (nit_no_fn, ed_math_3, "F.2 Changes between MathML 2.0 Second Edition and MathML 3.0", es_error, ec_element, "<FN> is not part of MathML 3."); }

void element::examine_fontymacfontface ()
{   bool had = false;
    if (has_child ())
        for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
            if (c -> tag () == elem_fontfacesrc)
                if (! had) had = true;
                else
                {   pick (nit_animatemotion, ed_svg_1_1, "20.8.3 The font-face element", es_error, ec_element, "<FONTY-MacFONT-FACE> can only have ONE child <FONT-FACE-SRC>");
                    return; } }

void element::examine_footer ()
{   if (node_.version ().is_5 ())
    {   check_ancestors (elem_footer, empty_element_bitset | elem_address | elem_footer | elem_header | elem_dt);
        if ((node_.version () > html_jan13) && (node_.version () < html_jul18))
            check_descendants (elem_footer, empty_element_bitset | elem_main);
        if ((node_.version ().whatwg ()) || (node_.version () == html_5_0))
            check_descendants (elem_footer, empty_element_bitset | elem_header | elem_footer); } }

void element::examine_form ()
{   switch (node_.version ().mjr ())
    {   case 0 :
        case 1 :  // shouldn't get here, of course, but ... :-)
        case 3 :
        case 4 : break;
        case 2 :
            if (node_.version ().strict ())
                pick (nit_no_form, es_error, ec_element, "<FORM> should not appear in ", node_.version ().report (), " documents");
            break;
        default :
        {   check_ancestors (elem_form, element_bit_set (elem_form));
            if ((node_.version () >= html_jan19) && a_.good (a_acceptcharset))
            {   auto v = a_.get_x < attr_acceptcharset > ();
                if (v.size () != 1) pick (nit_form_charset, ed_jul20, "4.10.3 The form element", es_error, ec_attribute, "ACCEPT-CHARSET, if present, must be set to 'utf-8' only");
                else
                {   auto cs = v.at (0);
                    if (cs != cs_utf_8) pick (nit_form_charset, ed_jul20, "4.10.3 The form element", es_error, ec_attribute, "ACCEPT-CHARSET, if present, must be set to 'utf-8'"); } }
            if (! radio_kids_.empty ())
            {   msid_t names;
                for (auto rk : radio_kids_)
                {   ::std::string n (rk -> a_.get_string (a_name));
                    auto i = names.find (n);
                    if (i == names.cend ()) names.emplace (msid_t::value_type (n, 1));
                    else i -> second += 1; }
                for (auto rk : radio_kids_)
                {   ::std::string n (rk -> a_.get_string (a_name));
                    auto i = names.find (n);
                    assert (i != names.cend ());
                    if (i -> second == 1)
                        if (n.empty ())
                            rk -> pick (nit_lonely_radio, ed_50, "4.10.5.1.13 Radio Button state", es_error, ec_element, "radio buttons require company; there should be multiple unnamed <INPUT> TYPE=radio");
                        else
                            rk -> pick (nit_lonely_radio, ed_50, "4.10.5.1.13 Radio Button state", es_error, ec_element, "radio buttons require company; there must be multiple <INPUT> TYPE=radio with NAME ", quote (n)); } } } } }

void element::examine_h123456 ()
{   if (node_.version ().mjr () < 5) return;
    check_ancestors (tag (), empty_element_bitset | elem_address | elem_dt);
    if (node_.version () < html_jan08)
        check_descendants (tag (), empty_element_bitset | elem_faux_asp | elem_faux_cdata | elem_faux_char | elem_faux_code | elem_faux_php | elem_faux_ssi | elem_faux_text, false); }

void element::examine_header ()
{   if (node_.version ().is_5 ())
    {   check_ancestors (elem_header, empty_element_bitset | elem_address | elem_footer | elem_header | elem_dt);
        if ((node_.version () > html_jan13) && (node_.version () < html_jul18))
            check_descendants (elem_header, empty_element_bitset | elem_main);
        if ((node_.version ().whatwg ()) || (node_.version () == html_5_0))
            check_descendants (elem_header, empty_element_bitset | elem_header | elem_footer); } }

void element::examine_hgroup ()
{   if (node_.version () < html_jul13)
    {   if (has_invalid_child (empty_element_bitset | elem_h1 | elem_h2 | elem_h3 | elem_h4 | elem_h5 | elem_h6))
            pick (nit_bad_descendant, ed_jan10, "4.4.7 The hgroup element", es_error, ec_element, "<HGROUP> can only have <H1> ... <H6> children"); }
    else if (node_.version () >= html_jul18)
    {   if (has_invalid_child (empty_element_bitset | elem_h1 | elem_h2 | elem_h3 | elem_h4 | elem_h5 | elem_h6 | elem_script | elem_template))
            pick (nit_bad_descendant, ed_jul20, "4.3.7 The hgroup element", es_error, ec_element, "<HGROUP> can only have <SCRIPT>, <TEMPLATE>, or <H1> ... <H6> children"); }
    else if (has_invalid_child (empty_element_bitset | elem_h1 | elem_h2 | elem_h3 | elem_h4 | elem_h5 | elem_h6 | elem_template))
        pick (nit_bad_descendant, ed_jul17, "4.3.7 The hgroup element", es_error, ec_element, "<HGROUP> can only have <TEMPLATE>, or <H1> ... <H6> children"); }

void element::examine_html ()
{   if (node_.version () == html_plus)
        pick (nit_use_htmlplus, es_error, ec_element, "HTML+ uses the <HTMLPLUS> element, not <HTML>");
    else
    {   only_one_of (elem_html);
        if (node_.version () >= html_jan13)
           if (! a_.known (a_lang) && ! a_.known (a_xmllang))
                pick (nit_naughty_lang, ed_50, "4.1.1 The html element", es_warning, ec_attribute, "use LANG to specify a default language");
        if (node_.version () >= html_jan17)
            if (a_.known (a_manifest))
                pick (nit_avoid_manifest, ed_52, "4.1.1 The html element", es_warning, ec_attribute, "MANIFEST is deprecated & should be avoided because application caches are doomed"); } }

void element::examine_iframe ()
{   if (node_.version ().mjr () < 5) return;
    const bool has_src = a_.known (a_src);
    no_anchor_daddy ();
    if (has_src) check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_src), MIME_PAGE);
    if (a_.known (a_itemprop) && ! a_.known (a_src))
        pick (nit_bad_iframe, ed_jul20, "4.8.5 The iframe element", es_error, ec_attribute, "SRC is required when ITEMPROP is used with <IFRAME>");
    if (! a_.known (a_srcdoc) && ! a_.known (a_src))
        pick (nit_chocolate_teapot, es_info, ec_attribute, "Not sure what use <IFRAME> is without SRC or SRCDOC"); }

void element::examine_img ()
{   const bool alt_known = a_.known (a_alt);
    const bool alt_empty = alt_known ? a_.get_string (a_alt).empty () : false;
    const bool ancestor_a = ancestral_elements_.test (elem_a);
    const bool ancestor_figure = ancestral_elements_.test (elem_figure);
    const bool has_title = a_.good (a_title) && (! a_.get_string (a_title).empty ());
    const bool has_src = a_.known (a_src);
    check_required_type (elem_img);
    if (a_.known (a_usemap) && ! node_.version ().is_5 ()) no_anchor_daddy ();
    if (has_src) check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_src), MIME_IMAGE);
    if (node_.version ().is_4 ())
    {   if (! alt_known)
            pick (nit_attribute_required, ed_4, "13.2 Including an image", es_error, ec_attribute, "ALT is required on <IMG>");
        else if (alt_empty)
            pick (nit_naughty_alt, ed_4, "13.2 Including an image", es_warning, ec_attribute, "ALT should not be empty"); }
    else if (node_.version ().is_5 ())
    {   bool complained = false;
        bool figured = false;
        if ((node_.version () < html_jan08) && a_.known (a_ismap))
            if (! ancestor_a)
            {   complained = true;
                pick (nit_naughty_alt, ed_jan07, "3.14.1. The img element", es_warning, ec_element, "ISMAP cannot be used on <IMG> unless it has an <A> ancestor"); }
            else for (element* p = parent_; p != nullptr; p = p -> parent_)
                if (p -> tag () == elem_a)
                    if (! p -> a_.known (a_href))
                    {   complained = true;
                        pick (nit_naughty_alt, ed_jan21, "4.8.3 The img element", es_warning, ec_attribute, "when ISMAP is used on <IMG>, its ancestral <A> must have an HREF");
                        break; }
        if (node_.version () >= html_jan17)
        {   if (a_.valid (a_srcset))
            {   attribute_v_ptr srsptr = a_.get (a_srcset);
                attr_srcset* const srs = static_cast <attr_srcset*> (srsptr.get ());
                if (srs -> has_width () && ! a_.known (a_sizes))
                {   complained = true;
                    pick (nit_attribute_required, ed_jan21, "4.8.5 The img element", es_error, ec_attribute, "SIZES is required when a SRCSET has a width specification"); }
                if (a_.known (a_sizes) && srs -> has_density ())
                {   complained = true;
                    pick (nit_bad_srcset, ed_jan21, "4.8.4.2.1 Srcset attributes", es_error, ec_attribute, "if <IMG> has SIZES, then SRCSET must contain width specifiers"); } }
            if (ancestor_figure)
                if (! has_title)
                    for (element* p = parent_; p != nullptr; p = p -> parent_)
                        if (p -> tag () == elem_figure)
                        {   bool alone = true;
                            for (element_ptr ac = p -> child_; alone && (ac != nullptr); ac = ac -> sibling_)
                                if (is_standard_element (ac -> tag ()))
                                    if (! ac -> node_.is_closure ())
                                        switch (ac -> tag ())
                                        {   case elem_img :
                                                continue;
                                            case elem_figcaption :
                                                if ((! ac -> text ().empty ()) && (! is_whitespace (ac -> text ()))) figured = true;
                                                break;
                                            default :
                                                if (((ac -> node_.id ().flags ()) & EF_5_FLOW) == EF_5_FLOW)
                                                    figured = alone = false;
                                                break; }
                            break; }
            if (alt_empty || ! alt_known)
                if (ancestor_a)
                {   bool alt_required = true, alone = true;
                    for (element* p = parent_; p != nullptr; p = p -> parent_)
                        if (p -> tag () == elem_a)
                        {   if (! p -> text ().empty ()) alt_required = false;
                            else for (element_ptr ac = p -> child_; ac != nullptr; ac = ac -> sibling_)
                                if (! ac -> node_.is_closure ())
                                    if (is_standard_element (ac -> tag ()))
                                        if (ac.get () != this)
                                        {   alone = false; break; }
                            break; }
                    if (alt_required)
                        if (alone)
                            if (! alt_known) pick (nit_attribute_required, ed_50, "4.7.1 The img element", es_error, ec_attribute, "ALT is required when <IMG> is a solo child of <A>");
                            else pick (nit_naughty_alt, ed_50, "4.7.1 The img element", es_error, ec_attribute, "ALT cannot be empty when <IMG> is a solo child of <A>");
                        else
                            if (! alt_known) pick (nit_attribute_required, ed_50, "4.7.1 The img element", es_warning, ec_attribute, "ALT is recommended when <IMG> is a child of <A>");
                            else pick (nit_naughty_alt, ed_50, "4.7.1 The img element", es_warning, ec_attribute, "ALT is better with content when <IMG> is a child of <A>");
                    complained = true; } // even if not
                else if (! complained && ! has_title && ! figured)
                    if (! alt_known)
                    {   complained = true; pick (nit_naughty_alt, ed_50, "4.7.1 The img element", es_error, ec_element, "here, ALT is required on <IMG>"); } }
        if (! complained)
            if (page_.version () < html_feb21)
                if ((! ancestor_figure) || (node_.version () == html_5_0))
                    if (! alt_known)
                        pick (nit_naughty_alt, ed_50, "4.7.1 The img element", es_warning, ec_element, "with exceptions, ALT is required on <IMG>");
                    else if (alt_empty)
                        if (node_.version ().w3 ()) pick (nit_naughty_alt, ed_50, "4.7.1 The img element", es_info, ec_attribute, "generally, ALT should not be empty");
                        else pick (nit_naughty_alt, ed_jan14, "4.7.1 The img element", es_info, ec_attribute, "ALT should normally have content"); }
    if ((node_.version ().is_4_or_more ()) && alt_known && has_title)
        if (compare_no_case (a_.get_string (a_alt), a_.get_string (a_title)))
            pick (nit_alt_title, ed_51, "4.7.5.1.2. General guidelines", es_warning, ec_element, "ALT and TITLE should have different values"); }
