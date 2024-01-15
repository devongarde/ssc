/*
ssc (static site checker)
File Info
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
#include "attribute/attribute_classes.h"
#include "webpage/page.h"

void element::examine_abbr ()
{   ::std::string t (term ());
    ::std::string ab (trim_the_lot_off (text ()));
    if (t.empty () || ab.empty ()) return;
    page_ -> mark_abbr (ab, t);
    ustr_t::const_iterator i = page_ -> abbrs ().find (ab);
    if (i == page_ -> abbrs ().cend ())
        page_ -> abbrs ().insert (ustrv_t (ab, t));
    else if (i -> second != t)
        pick (nit_contradictory_expansion, es_warning, ec_element, quote (ab), " has a different expansion above (", quote (t), " versus ", quote (i -> second)); }

void element::examine_address ()
{   if (node_.version ().is_5 ())
    {   check_ancestors (elem_address, empty_element_bitset | elem_address);
        check_descendants (elem_address, header_bitset | sectioning_bitset | elem_address | elem_header | elem_footer); } }

void element::examine_altglyphdef ()
{   bool ref = false, item = false, bad = false;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
            switch (c -> tag ())
            {   case elem_altglyphitem :
                    if (ref) bad = true; else item = true;
                    break;
                case elem_glyphref :
                    if (item) bad = true; else ref = true;
                    break;
                default :
                    break; }
    if (bad) pick (nit_altglyphdef, ed_svg_1_0, "10.14 Alternate glyphs", es_error, ec_element, "<ALTGLYPHDEF> can have only <GLYPHREF> or only <ALTGLYPHITEM> children"); }

void element::examine_anchor ()
{   const bool href_known = a_.known (a_href) || a_.known (a_xlinkhref);
    const bool type_known = a_.known (a_type);
    const bool rel_known = a_.known (a_rel);
    const bool rev_known = a_.known (a_rev);
    const bool five = node_.version ().is_5 ();
    if (href_known)
    {   no_anchor_daddy ();
        if (type_known) check_extension_compatibility (nits (), node_.version (), a_.get_string (a_type), a_.get_urls (a_href), false); }
    else if (rel_known || rev_known)
        pick (nit_rel_requires_href, ed_1, "Anchors", es_error, ec_element, "REL and REV both require a valid HREF");
    else if (five) pick (nit_chocolate_teapot, es_warning, ec_element, "An <A> with no HREF, or an invalid HREF, is not useful");
    else if (! a_.known (a_name))
        pick (nit_chocolate_teapot, ed_tags, "Anchors", es_warning, ec_element, "An <A> with neither a valid HREF nor a NAME is not useful");
    if (a_.known (a_urn))
        pick (nit_urn_undefined, ed_1, "Anchors", es_info, ec_element, PROG " cannot verify URN values");
    if (a_.known (a_methods))
        pick (nit_methods_undefined, ed_1, "Anchors", es_info, ec_element, PROG " cannot verify METHOD values here");
    if (five)
    {   if (! href_known)
        {   if (a_.known (a_target) || a_.known (a_download) || a_.known (a_ping) || a_.known (a_referrerpolicy) || rel_known || rev_known || a_.known (a_hreflang) || type_known)
                pick (nit_chocolate_teapot, ed_50, "4.5.1 The a element", es_error, ec_element, "An <A> with no HREF can have no DOWNLOAD, HREFLANG, REL, REV, REFERRERPOLICY, PING, TARGET or TYPE attributes");
            if (a_.known (a_itemprop))
                pick (nit_chocolate_teapot, ed_jul20, "4.5.1 The a element", es_error, ec_element, "An <A> with an ITEMPROP requires an HREF"); }
        if (w3_minor_5 (node_.version ()) >= 4)
        {   const attribute_bitset as (descendant_attributes_);
            if (as.test (a_tabindex))
                pick (nit_tabindex, ed_jul20, "4.5.1 The a element", es_error, ec_element, "An <A> cannot have a descendant with TABINDEX"); } } }

void element::examine_animatemotion ()
{   bool had = false;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
            if (c -> tag () == elem_mpath)
                if (! had) had = true;
                else
                {   pick (nit_animatemotion, ed_svg_1_1, "19.2.14 The animateMotion element", es_error, ec_element, "<ANIMATEMOTION> can only have ONE child <MPATH>");
                    return; } }

void element::examine_annotation ()
{   switch (node_.version ().math ())
    {   case math_2 :
            if (a_.known (a_definitionurl) || a_.known (a_cd) || a_.known (a_name) || a_.known (a_src))
                pick (nit_annotation, es_info, ec_element, "CD, DEFINITIONURL, NAME, SRC are invalid with <", elem::name (tag ()), "> in MathML 2.0");
            break;
        case math_3 :
            break;
        default : return; }
    if (has_child ())
        pick (nit_annotation, es_info, ec_element, "apologies, but " PROG " makes no effort to analyse the content of <", elem::name (tag ()), ">"); }

void element::examine_area ()
{   const bool href_known = a_.known (a_href);
    const bool alt_known = a_.known (a_alt);
    if (href_known) check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE);
    if (node_.version ().is_5 ())
    {   if (! any (ancestral_elements_, empty_element_bitset | elem_map | elem_template))
            pick (nit_area_map_template, ed_50, "4.7.12 The area element", es_error, ec_element, "<AREA> requires a <MAP> or a <TEMPLATE> ancestor");
        if (href_known)
        {    if (! alt_known)
                pick (nit_requires_href, ed_50, "4.7.12 The area element", es_warning, ec_attribute, "HREF requires ALT"); }
        else
        {   if (alt_known)
                pick (nit_requires_href, ed_50, "4.7.12 The area element", es_warning, ec_attribute, "ALT requires HREF");
            if (a_.known (a_target) || a_.known (a_download) || a_.known (a_rel))
                pick (nit_requires_href, ed_50, "4.7.12 The area element", es_warning, ec_attribute, "DOWNLOAD, REL, and TARGET each require HREF");
            if (a_.known (a_hreflang) || a_.known (a_type))
                if ((node_.version () < html_jan17) || (node_.version ().w3 ()))
                    pick (nit_requires_href, ed_50, "4.7.12 The area element", es_warning, ec_attribute, "HREFLANG and TYPE both require HREF"); } }
    if (a_.good (a_shape))
    {   type_master < t_shape7 > s7;
        nitpick knots;
        s7.set_value (knots, node_.version (), a_.get_string (a_shape));
        if (s7.good ())
        {   if ((s7.get () != s7_default) && ! a_.known (a_coords))
            {   pick (nit_need_coords, ed_50, "4.7.12 The area element", es_warning, ec_attribute, "Unless SHAPE is present and set to 'default', COORDS must be specified");
                return; }
            if (! a_.good (a_coords)) return;
            vint_t c = a_.get_x < attr_coords > ();
            switch (s7.get ())
            {   case s7_circ :
                    if (c.size () != 3) pick (nit_bad_coords, ed_rfc_1980, "2.1 Syntax", es_error, ec_attribute, "When SHAPE is circle, COORDS should contain three values");
                    break;
                case s7_poly :
                    if (c.size () % 2 != 0) pick (nit_bad_coords, ed_rfc_1980, "2.1 Syntax", es_error, ec_attribute, "When SHAPE is polygon, COORDS should contain a sequence of coordinates (an even number of values)");
                    break;
                case s7_rect :
                    if (c.size () != 4) pick (nit_bad_coords, ed_rfc_1980, "2.1 Syntax", es_error, ec_attribute, "When SHAPE is rectangle (the default value), COORDS should contain two coordinates");
                    break;
                default : break; } } } }

void element::examine_article ()
{   if (! context.corpus ().empty ()) if (context.article ()) page_ -> corpus (text ());
    if (node_.version ().w3 ())
        if (has_this_descendant (elem_main))
            pick (nit_no_main_kids, ed_50, "4.3.2 The article element", es_warning, ec_element, "<ARTICLE> can have no <MAIN> descendants"); }

void element::examine_aside ()
{   if (context.html_ver ().w3 () || (node_.version () < html_jul18))
        if (has_this_descendant (elem_main))
            pick (nit_no_main_kids, ed_50, "4.3.5 The aside element", es_warning, ec_element, "<ASIDE> can have no <MAIN> descendants"); }

void element::examine_audio ()
{   if (! node_.version ().is_5 () && ! node_.version ().is_svg_12 ())
        pick (nit_unknown_element, es_error, ec_element, "<AUDIO> requires HTML 5 or SVG 1.2");
    else
    {   examine_media_element (elem_audio, "4.7.7 The audio element", "<AUDIO>", MIME_AUDIO);
        if (a_.known (a_autoplay)) pick (nit_autoplay, es_warning, ec_rudeness, "AUTOPLAY on <AUDIO> is usually rude"); } }

void element::examine_base ()
{   if (node_.version () == html_tags)
    {   pick (nit_base_undefined, ed_tags, "Page 1, Base Address", es_error, ec_element, "<BASE> is reserved but undefined in HTML Tags");
        return; }
    if (! only_one_of ()) return;
    if (sibling_attributes_.test (a_href) != 0)
        switch (node_.version ().mjr ())
        {   case 0 :
            case 1 :
            case 2 :
            case 3 :
                break;
            case 4 :
                pick (nit_base_b4_lynx, ed_4, "12.4 Path information: the BASE element", es_error, ec_element, "<BASE> must appear before any element with a link");
                break;
            default :
                if (node_.version () >= html_jan08)
                    if (a_.known (a_href) || a_.known (a_target))
                        pick (nit_base_b4_lynx, ed_50, "4.2.3 The base element", es_error, ec_element, "a <BASE> with TARGET or HREF must appear before any element with a link"); }
    if (! a_.known (a_href))
    {   if (a_.known (a_target))
        {   pick (nit_target, es_warning, ec_element, "TARGET forces " PROG " to abandon local link checks");
            page_ -> check_links (false); }
        else if (node_.version () >= html_jul07)
           pick (nit_base, ed_50, "4.2.3 The base element", es_error, ec_element, "<BASE> must have an HREF or a TARGET attribute");
        return; }
    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE);
    url u (nits (), node_.version (), a_.get_string (a_href));
    if (u.empty ())
        pick (nit_empty, es_error, ec_element, "ignoring empty <BASE>");
    else if (u.has_component (es_fragment) || u.has_component (es_query))
    {   pick (nit_element_bizarre_base, es_error, ec_element, "ignoring bizarre <BASE> ", quote (u.original ())); }
    else
    {   if (! u.is_local ())
        {   pick (nit_element_offsite_base, es_warning, ec_element, "WARNING: Because of the offsite <BASE> ", quote (u.original ()), ", " PROG " is abandoning local link checks");
            page_ -> check_links (false); }
        page_ -> base (u); } }

void element::examine_bind ()
{   if (! check_math_children (3, true)) return;
    bool first = true, other = false, bound = false;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   if (c -> tag () != elem_bvar) other = true;
            else if (first)
            {   pick (nit_bad_bind, ed_math_3, "4.2.6.1 Bindings", es_error, ec_element, "<BVAR> cannot be the first child of <BIND>");
                return; }
            else bound = true;
            first = false; }
    if (! bound)
        pick (nit_bad_bind, ed_math_3, "4.2.6.1 Bindings", es_error, ec_element, "<BIND> requires at least one <BVAR> child");
    else if (! other)
        pick (nit_bad_bind, ed_math_3, "4.2.6.1 Bindings", es_error, ec_element, "<BVAR> cannot be the last child of <BIND>"); }

void element::examine_body ()
{   if (! context.corpus ().empty ()) if (context.body () || ! page_ -> corpus ()) page_ -> corpus (text ()); }

void element::examine_button ()
{   if (node_.version ().is_5 ())
    {   no_anchor_daddy ();
        if (has_child ())
        {   element_bitset bs (descendant_elements_);
            bs &= interactive_bitset;
            if (bs.any ())
                pick (nit_interactive, ed_50, "4.10.6 The Button element", es_warning, ec_element, "An <BUTTON> element cannot have interactive descendant elements");
            if (descendant_attributes_.test (a_tabindex))
                pick (nit_interactive, ed_50, "4.10.6 The Button element", es_warning, ec_element, "An <BUTTON> element cannot have a descendant element with a TABINDEX"); }
        const e_button bu = static_cast < e_button > (a_.get_int (a_type));
        if (bu != bu_submit)
            if (a_.known (a_formaction) || a_.known (a_formenctype) || a_.known (a_formmethod) || a_.known (a_formnovalidate) || a_.known (a_formtarget) ||
                a_.known (a_action) || a_.known (a_enctype) || a_.known (a_method) || a_.known (a_novalidate) || a_.known (a_target))
                pick (nit_bad_form, ed_50, "", es_error, ec_attribute, "FORM... attributes require <BUTTON> TYPE='submit'"); } }

void element::examine_caption ()
{   if (node_.version ().is_5 ()) check_descendants (elem_caption, element_bitset (elem_table)); }

void element::examine_card ()
{   if ((node_.version () < html_jan05) || (node_.version () >= html_jan07))
    {   if (! node_.version ().has_math ())
            pick (nit_bad_card, es_error, ec_element, "<CARD> requires MathML");
        if (has_child ())
            pick (nit_bad_card, es_error, ec_element, "<CARD> has no children"); } }

void element::examine_command ()
{   if (a_.known (a_command))
    {   attribute_bitset bs = empty_attribute_bitset | a_type | a_label | a_title | a_hidden | a_icon | a_disabled | a_checked | a_radiogroup | a_default;
        bs &= own_attributes_;
        if (bs.any ())
            pick (nit_bad_command, ed_jan12, "4.11.3 The command element", es_warning, ec_element, "A <COMMAND> element can either have the COMMAND attribute or other attributes"); } }

void element::examine_col ()
{   if (node_.version ().is_5 ())
        if (a_.known (a_span))
            if (a_.get_int (a_span) > 1000) pick (nit_1000, ed_50, "4.9.4 The col element", es_error, ec_element, "SPAN cannot exceed 1000"); }

void element::examine_colgroup ()
{   if (node_.version ().is_5 ())
        if (a_.known (a_span))
        {   element_bitset bs (descendant_elements_);
            bs &= ~ ( non_standard_bitset | elem_col | elem_template );
            if (bs.any ())
                if (node_.version () < html_jul13) pick (nit_colgroup_children, ed_jan13, "4.9.3 The colgroup element", es_error, ec_element, "<COLGROUP> with SPAN can only have <COL> descendants");
                else pick (nit_colgroup_children, ed_50, "4.9.3 The colgroup element", es_error, ec_element, "<COLGROUP> with SPAN can only have <COL> and <TEMPLATE> descendants");
            if (a_.get_int (a_span) > 1000) pick (nit_1000, ed_50, "4.9.3 The colgroup element", es_error, ec_element, "SPAN cannot exceed 1000"); } }

void element::examine_colour_profile ()
{   if (node_.version ().is_svg_1 ())
        if (a_.good (a_name))
        {   const ::std::string& naam (a_.get_string (a_name));
            if (compare_no_case (naam, sz_srgb :: sz ()))
                pick (nit_colour_profile, es_warning, ec_attribute, "standard colour profiles cannot be redefined");
            else if (page_ -> profiles ().find (naam) != page_ -> profiles ().cend ())
                pick (nit_colour_profile, es_warning, ec_attribute, "colour profile ", quote (naam), " previously defined");
            else page_ -> profiles ().insert (naam); } }

void element::examine_data ()
{   if (ancestral_elements_.test (elem_svg))
    {   if (! node_.is_closed ())
            pick (nit_svg_data, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_element, "The SVG <DATA> element is empty, it has no </DATA>");
        if (! a_.known (a_d))
            pick (nit_svg_data, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_attribute, "The SVG <DATA> element requires the D attribute"); }
    else if (! node_.version ().whatwg ())
        pick (nit_svg_data, es_error, ec_element, "<DATA> is not part of W3's HTML 5 specifications");
    else if (node_.version () < html_jan12)
        pick (nit_svg_data, es_error, ec_element, "<DATA> requires a later version of WhatWG's HTML 5 living standard");
    else if (! a_.known (a_value))
        pick (nit_svg_data, ed_jan12, "4.6.10 The data element", es_error, ec_attribute, "The HTML 5 <DATA> element requires the VALUE attribute"); }

void element::examine_datagrid ()
{   if (has_child ())
    {   bool had_table = false, had_select = false, had_datalist = false, had_other = false;
        int n = 0;
        for (element* p = child_; p != nullptr; p = p -> sibling_)
            if (is_standard_element (p -> tag ()) && ! p -> node_.is_closure ())
                switch (p -> tag ())
                {   case elem_datalist :
                        had_datalist = true;
                        ++n;
                        break;
                    case elem_select :
                        had_select = true;
                        ++n;
                        break;
                    case elem_table :
                        had_table = true;
                         ++n;
                        break;
                   default :
                        had_other = true;
                        break; }
        if (n > 1)
            pick (nit_bad_datagrid, ed_jan07, "3.18.2. The datagrid element", es_error, ec_element, "a <DATAGRID> can have only one <DATALIST>, <SELECT> or <TABLE> child");
        if (had_other)
            if (had_table || had_select || had_datalist)
                pick (nit_bad_datagrid, ed_jan07, "3.18.2. The datagrid element", es_error, ec_element, "a <DATAGRID> can have one <DATALIST>, <SELECT> or <TABLE> child, or other children, but not a mix of them"); } }

void element::examine_datalist ()
{   if (! has_child ()) pick (nit_bad_datalist, ed_50, "4.10.8 The datalist element", es_warning, ec_element, "is the empty <DATALIST> intentional");
    else
    {   bool had_option = false, had_other = false;
        for (element* p = child_; p != nullptr; p = p -> sibling_)
            if (is_standard_element (p -> tag ()) && ! p -> node_.is_closure ())
                switch (p -> tag ())
                {   case elem_option :
                        had_option = true;
                        FALLTHROUGH;
                    case elem_script :
                    case elem_template :
                        break;
                    default :
                        had_other = true;
                        break; }
        if (had_other)
            if (had_option)
            {   pick (nit_bad_datalist, ed_50, "4.10.8 The datalist element", es_error, ec_element, "a <DATALIST> can have <OPTION> children, or other children, but not both"); }
            else if (! descendant_elements_.test (elem_select))
                pick (nit_bad_datalist, ed_50, "4.10.8 The datalist element", es_warning, ec_element, "a <DATALIST> without <OPTION> children should contain a <SELECT>"); } }

void element::examine_details ()
{   no_anchor_daddy ();
    bool first = true;
    if (has_child ())
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (is_standard_element (c -> tag ()) && (! c -> node_.is_closure ()))
                if (first) first = false;
                else if (c -> tag () == elem_summary)
                {   pick (nit_details_summary, ed_51, "4.11.1. The details element", es_error, ec_element, "<SUMMARY> can only be the first child of <DETAILS>");
                    break; } } }

void element::dddt (const char* ref1, const char* ref2, const char* el)
{   if (node_.version ().is_5 ())
    {   if (! ancestral_elements_.test (elem_dl))
            if (node_.version () < html_jan10)
            {   if (! ancestral_elements_.test (elem_dialogue))
                    pick (nit_dl_ancestor, ed_jan07, ref1, es_error, ec_element, "<", el, "> must have a <DL> or <DIALOG> ancestor"); }
            else if (node_.version () < html_jul10)
            {   if (! ancestral_elements_.test (elem_figure) && ! ancestral_elements_.test (elem_details))
                    pick (nit_dl_ancestor, ed_jan10, ref1, es_error, ec_element, "<", el, "> must have a <DETAILS>, <DL> or <FIGURE> ancestor"); }
            else pick (nit_dl_ancestor, ed_52, ref2, es_error, ec_element, "<", el, "> must have a <DL> ancestor");
        check_descendants (elem_dt, header_bitset | sectioning_bitset | elem_header | elem_footer); } }

void element::examine_dd ()
{   dddt ("3.11.6. The dd element", "4.4.11. The dd element", "DD"); }

void element::examine_dfn ()
{   ::std::string t (term ());
    if (! t.empty ())
        page_ -> mark_dfn (t, trim_the_lot_off (parent_ -> text ()));
    if (node_.version ().is_5 ())
    {   if (! t.empty () && (node_.version () < html_jul08))
            if (page_ -> dfns ().find (t) != page_ -> dfns ().cend ())
                pick (nit_repeated_definition, ed_jan07, "3.12.8. The dfn element", es_error, ec_element, quote (t), " has already been defined");
            else page_ -> dfns ().insert (t);
        check_ancestors (elem_dfn, element_bitset (elem_dfn)); } }

void element::examine_dialogue ()
{   if (node_.version () >= html_jan10)
        if (node_.version () < html_jul12)
            pick (nit_bad_dialogue, es_error, ec_element, "<DAILOG> is not defined by ", node_.version ().name ());
        else if (a_.known (a_tabindex))
            pick (nit_bad_dialogue, ed_52, "4.11.4 The dialog element", es_error, ec_element, "<DAILOG> cannot have TABINDEX"); }

void element::examine_div ()
{   if (has_child () && (node_.version () >= html_jan17))
    {   bool dt = false, dd = false;
        if (parent_ -> tag () == elem_dl)
        {   for (element* c = child_; c != nullptr; c = c -> sibling_)
            {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
                if (! c -> node_.is_closure ())
                {   if (faux_bitset.test (c -> tag ())) continue;
                    if (script_bitset.test (c -> tag ())) continue;
                    switch (c -> tag ())
                    {   case elem_dt :
                            dt = true;
                            if (dd) pick (nit_dl_div, ed_50, "4.4.8. The dl element", es_error, ec_element, "when <DIV> is a child of <DL>, all <DT> children must precede all <DD> children");
                            break;
                        case elem_dd :
                            dd = true;
                            if (! dt) pick (nit_no_dd, ed_50, "4.4.8. The dl element", es_error, ec_element, "when <DIV> is a child of <DL>, there must be at least one <DT> child before any <DD> children");
                            break;
                        default :
                            pick (nit_dt_dd, ed_52, "4.4.15. The div element", es_error, ec_element, "when <DIV> is a child of <DL>, it can only have <DD>, <DT>, and script children");
                            break; } } }
            if (! dt || ! dd)
                pick (nit_dt_dd, ed_52, "4.4.15. The div element", es_error, ec_element, "when <DIV> is a child of <DL>, it must have at least one <DT> child, then at least one <DD> child"); } } }

void element::examine_dl ()
{   bool dtdd = false, dt = false, div = false, dd = false;
    vstr_t terms; ::std::string s;
    if (has_child () && (node_.version ().is_5 ()))
        for (element* c = child_; c != nullptr; c = c -> sibling_)
        {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
            if (! c -> node_.is_closure ())
                switch (c -> tag ())
                {   case elem_div :
                        if (node_.version () < html_jan17) break;
                        if (dtdd || dt) pick (nit_dl_div, ed_52, "4.4.9. The dl element", es_error, ec_element, "<DL> can have <DT>/<DD> children, or <DIV> children, but not both");
                        else div = true;
                        break;
                    case elem_dt :
                        if (dd) { terms.clear ();  dd = false; }
                        dt = true;
                        s = tart (c -> text ());
                        if (! s.empty ()) terms.push_back (s);
                        if (node_.version () < html_jan17) break;
                        if (div) pick (nit_dl_div, ed_52, "4.4.9. The dl element", es_error, ec_element, "<DL> can have <DT>/<DD> children, or <DIV> children, but not both");
                        else dtdd = true;
                        break;
                    case elem_dd :
                        dd = true;
                        if (! dt) pick (nit_no_dd, ed_50, "4.4.8. The dl element", es_error, ec_element, "<DD> must be preceded by <DT>");
                        s = tart (c -> text ());
                        if (! s.empty ()) for (auto t : terms) page_ -> mark_dtdd (t, s);
                        if (node_.version () < html_jan17) break;
                        if (div) pick (nit_dl_div, ed_52, "4.4.9. The dl element", es_error, ec_element, "<DL> can have <DT>/<DD> children, or <DIV> children, but not both");
                        else dtdd = true;
                        break;
                    case elem_faux_cdata :
                    case elem_faux_char :
                    case elem_faux_code :
                    case elem_faux_text :
                        if (node_.version () < html_jul05)
                            pick (nit_bad_dl, ed_jan05, "2.4.2. The dl, dt, and dd elements", es_error, ec_element, "<DL> cannot have non-whitespace text content");
                        break;
                    default :
                        break; } } }

void element::examine_dt ()
{   dddt ("3.11.5. The dt element", "4.4.10. The dt element", "DT"); }
