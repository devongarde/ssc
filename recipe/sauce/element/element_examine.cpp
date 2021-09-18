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
#include "element/parentage.h"
#include "attribute/attribute_classes.h"

void element::pre_examine_element ()
{   switch (tag ())
    {   case elem_animate :
        case elem_animatecolour :
        case elem_animatemotion :
        case elem_animatetransform :
        case elem_set : examine_animation_attributes (); break;
        case elem_annotation :
        case elem_annotation_xml : examine_annotation (); break;
        case elem_area : examine_area (); break;
        case elem_base : examine_base (); break;
        case elem_body :
        case elem_head :
        case elem_htmlplus :
        case elem_isindex :  only_one_of (); break;
        case elem_col : examine_col (); break;
        case elem_colour_profile : examine_colour_profile (); break;
        case elem_command : examine_command (); break;
        case elem_data : examine_data (); break;
        case elem_dialogue : examine_dialogue (); break;
        case elem_embed : examine_embed (); break;
        case elem_fe : examine_fe (); break;
        case elem_fecolourmatrix : examine_fecolourmatrix (); break;
        case elem_fecomponenttransfer : examine_fecomponenttransfer (); break;
        case elem_fecomposite : examine_fecomposite (); break;
        case elem_feconvolvematrix : examine_feconvolvematrix (); break;
        case elem_fn : examine_fn (); break;
        case elem_html : examine_html (); break;
        case elem_iframe : examine_iframe (); break;
        case elem_li : examine_li (); break;
        case elem_link : examine_link (); break;
        case elem_main : examine_main (); break;
        case elem_map : examine_map (); break;
        case elem_meter : examine_meter (); break;
        case elem_mstyle : examine_mstyle (); break;
        case elem_nest : examine_nest (); break;
        case elem_nextid :
            pick (nit_deprecated_element, es_warning, ec_element, "Really? <NEXTID> was obsolete in HTML Tags!");
            break;
        case elem_progress : examine_progress (); break;
        case elem_reln : examine_reln (); break;
        case elem_render :
            pick (nit_render, es_warning, ec_element, "With apologies, " PROG " does not understand <RENDER>");
            break;
        case elem_sarcasm : examine_sarcasm (); break;
        case elem_section : examine_section (); break;
        case elem_share : examine_share (); break;
        case elem_style : examine_style (); break;
        case elem_svg : examine_svg (); break;
        case elem_tab : examine_tab (); break;
        case elem_textarea : examine_textarea (); break;
        case elem_title : examine_title (); break;
        case elem_track : examine_track (); break; } }

void element::post_examine_element ()
{   switch (tag ()) // should integrate this into individual element verification?
    {   case elem_a : examine_anchor (); break;
        case elem_abbr : examine_abbr (); break;
        case elem_address : examine_address (); break;
        case elem_altglyphdef : examine_altglyphdef (); break;
        case elem_animatemotion : examine_animatemotion (); break;
        case elem_apply : examine_equation (); break;
        case elem_article : examine_article (); break;
        case elem_aside : examine_aside (); break;
        case elem_audio : examine_audio (); break;
        case elem_bind : examine_bind (); break;
        case elem_body : examine_body (); break;
        case elem_button : examine_button (); break;
        case elem_bvar :
        case elem_maction :
        case elem_merror :
        case elem_mmultiscripts :
        case elem_mpadded :
        case elem_mphantom :
        case elem_mscarry :
        case elem_msqrt :
        case elem_mstyle :
        case elem_mtd :
        case elem_semantics : check_math_children (1, true); break;
        case elem_card : examine_card (); break;
        case elem_caption : examine_caption (); break;
        case elem_circle :
        case elem_ellipse :
        case elem_foreignobject :
        case elem_line :
        case elem_g :
        case elem_path :
        case elem_polygon :
        case elem_polyline :
        case elem_rect :
        case elem_symbol :
        case elem_text :
        case elem_textpath :
        case elem_tspan :
        case elem_use : check_inclusion_criteria (); break;
        case elem_colgroup : examine_colgroup (); break;
        case elem_condition :
        case elem_degree :
        case elem_lowlimit :
        case elem_uplimit : if (page_.version ().math () <= math_1) break;
                            check_math_children (1); break;
        case elem_datagrid : examine_datagrid (); break;
        case elem_datalist : examine_datalist (); break;
        case elem_dfn : examine_dfn (); break;
        case elem_dd : examine_dd (); break;
        case elem_declare : if (page_.version ().math () > math_1) check_math_children (1, 2);
                            break;
        case elem_details : examine_details (); break;
        case elem_div : examine_div (); break;
        case elem_dl : examine_dl (); break;
        case elem_dt : examine_dt (); break;
        case elem_fediffuselighting : examine_felighting (); break;
        case elem_fespecularlighting : examine_felighting (); break;
        case elem_fieldset : examine_fieldset (); break;
        case elem_figure : examine_figure (); break;
        case elem_filter : examine_filter (); break;
        case elem_fn : if (page_.version ().math () > math_1) check_math_children (1);
                       break;
        case elem_font : examine_font (); break;
        case elem_font_face : examine_fontymacfontface (); break;
        case elem_footer : examine_footer (); break;
        case elem_form : examine_form (); break;
        case elem_h1:
        case elem_h2:
        case elem_h3:
        case elem_h4:
        case elem_h5:
        case elem_h6 : examine_h123456 (); break;
        case elem_hgroup : examine_hgroup () ; break;
        case elem_header : examine_header (); break;
        case elem_img : examine_img (); break;
        case elem_input : examine_input (); break;
        case elem_interval :if (page_.version ().math () <= math_1) break;
                            // drop thru'
        case elem_piece :   check_math_children (2); break;
        case elem_label : examine_label (); break;
        case elem_math : examine_math (); break;
        case elem_menu : examine_menu (); break;
        case elem_menubar : examine_menubar (); break;
        case elem_meta : examine_meta (); break;
        case elem_mfrac :
        case elem_mover :
        case elem_mroot :
        case elem_msub :
        case elem_msup :
        case elem_munder : check_math_children (2); break;
        case elem_mlongdiv :    check_math_children (3, true);
                                check_mscarries_pos ();
                                break;
        case elem_mn : examine_mn (); break;
        case elem_mstack : check_mscarries_pos (); break;
        case elem_msubsup :
        case elem_munderover : check_math_children (3); break;
        case elem_nav : examine_nav (); break;
        case elem_noscript : examine_noscript (); break;
        case elem_object : examine_object (); break;
        case elem_option : examine_option (); break;
        case elem_output : examine_output (); break;
        case elem_select : examine_select (); break;
        case elem_piecewise : examine_piecewise (); break;
        case elem_picture : examine_picture (); break;
        case elem_reln : examine_equation (); break;
        case elem_ruby : examine_ruby (); break;
        case elem_source : examine_source (); break;
        case elem_script : examine_script (); break;
        case elem_switch : examine_switch (); break;
        case elem_table : examine_table (); break;
        case elem_td : examine_td (); break;
        case elem_th : examine_th (); break;
        case elem_time : examine_time (); break;
        case elem_video : examine_video (); break; } }

void element::late_examine_element ()
{   switch (tag ())
    {   case elem_image : examine_image (); break;
        default : break; } }

void element::remove_category (const flags_t cat)
{   uint64_t c (node_.id ().categories ());
    c &= ~cat;
    node_.id ().congeal (c);
    node_.id ().refresh (EP_5_REFRESHED); }

void element::congeal_dynamism ()
{   if (node_.version ().is_5 ())
        if ((node_.id ().flags () & EP_5_REFRESHED) == 0)
            switch (tag ())
            {   case elem_audio :
                    if (! a_.known (a_controls))
                    {   remove_category (EF_5_INTERACTIVE);
                        remove_category (EF_5_PALPABLE); }
                    break;
                case elem_dl :
                    if (! has_this_child (elem_dd) || ! has_this_child (elem_dt)) remove_category (EF_5_PALPABLE); break;
                case elem_img :
                case elem_object :
                    if (! a_.known (a_usemap)) remove_category (EF_5_INTERACTIVE); break;
                case elem_input :
                    if (a_.known (a_type) && (a_.type (a_type) == static_cast < ::std::size_t > (i5_hidden)))
                    {   remove_category (EF_5_INTERACTIVE);
                        remove_category (EF_5_PALPABLE); }
                    break;
                case elem_link :
                    if ((w3_minor_5 (node_.version ()) < 2) || ! a_.known (a_itemprop))
                    {   remove_category (EF_5_FLOW);
                        remove_category (EF_5_PHRASE); }
                    break;
                case elem_menu :
                    if (node_.version ().mjr () > 5)
                        if (! has_this_child (elem_li))
                            remove_category (EF_5_PALPABLE);
                    break;
                case elem_meta :
                    if (! a_.known (a_itemprop))
                    {   remove_category (EF_5_FLOW);
                        remove_category (EF_5_PHRASE); }
                    break;
                case elem_ol :
                case elem_ul :
                    if (! has_this_child (elem_li)) remove_category (EF_5_PALPABLE); break;
                case elem_style :
                    if (w3_minor_5 (node_.version ()) > 3) remove_category (EF_5_FLOW); break;
                case elem_video :
                    if (! a_.known (a_controls)) remove_category (EF_5_INTERACTIVE); break;
                default :
                    pick (nit_missing_dynamic, es_catastrophic, ec_element, "missing dynamic congeal for ", node_.id ().name ());
                    break;  } }

void element::examine_self (const itemscope_ptr& itemscope, const attribute_bitset& ancestral_attributes, const attribute_bitset& sibling_attributes, const flags_t parental_flags)
{   if (examined_) return;
    flags_t flags (parental_flags);
    ancestral_attributes_ = ancestral_attributes;
    sibling_attributes_ = sibling_attributes;
    itemscope_ = itemscope;
    e_element tag = node_.tag ();
    if (! node_.is_closure ())
    {   page_.mark (tag);
        if (! a_.known (a_hidden)) page_.visible (tag);
        a_.mark (page_); }
    bool postprocess = false, post_examine = false;
    if (tag == elem_faux_stylesheet)
    {   url u (node_.nits (), node_.version (), node_.text ());
        if (! u.invalid ())
        {   pick (nit_gather, es_comment, ec_css, "gathering CSS identifiers from ", u.original ());
            context.css ().parse_file (node_.nits (), page_, u); } }
    else if (tag == elem_faux_text)
    {   PRESUME (node_.has_parent (), __FILE__, __LINE__);
        if ((node_.version () >= html_2) || ! node_.has_previous ()) if ((elem :: flags (node_.parent ().tag ()) & EP_ONLYELEMENTS) == EP_ONLYELEMENTS)
            pick (nit_only_elements, es_warning, ec_element, "<", elem :: name (node_.parent ().tag ()), "> can only contain elements, not text."); }
    else if (is_standard_element (tag) && ! node_.is_closure ())
    {   if (elem :: is_invalid_version (node_.version (), tag))
            pick (nit_invalid_element_version, es_error, ec_element, "<", elem :: name (tag), "> is invalid in ", node_.version ().report ());
        post_examine = true;
        node_.version ().check_math_svg (node_.nits (), node_.id ().first () , node_.id ().name ());
        html_version hv = elem :: first_version (tag);
        if (hv.invalid_addendum (node_.version ())) pick (nit_invalid_addendum, es_error, ec_element, "<", elem :: name (tag), "> is part of an extension that is being ignored");
        else if (hv.netscape ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid (ancient) Netscape bespoke elements");
        else if (hv.mozilla ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid non-standard Firefox / Mozilla elements");
        else if (hv.ie ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid (ancient) Internet Explorer bespoke elements");
        else if (hv.chrome ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid non-standard Chrome bespoke elements");
        else if (hv.safari ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid non-standard Safari bespoke elements");
        else if (hv.opera ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid non-standard Opera bespoke elements");
        else if (hv.webcomponents ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid bespoke Web Components elements");
        else if (hv.bespoke () ) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), ">: avoid using bespoke elements");
        if ((node_.version ().w3 ()) && hv.whatwg ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), "> is only defined by WhatWG");
        else if ((node_.version ().whatwg ()) && hv.w3 ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), "> is element only defined by W3");

        if (hv.deprecated (node_.version ())) pick (nit_deprecated_element, es_warning, ec_element, "<", elem :: name (tag), "> is deprecated in ", node_.version ().report ());
        if (hv.experimental ()) pick (nit_bespoke_element, es_warning, ec_element, "<", elem :: name (tag), "> is experimental; it will probably change, it may be withdrawn");

        a_.verify_attributes (nits (), node_.version (), this);
        ancestral_attributes_ |= own_attributes_;

        if (node_.id ().is_dynamic ()) if (! node_.id ().refreshed ()) congeal_dynamism ();

        if (parent_ == nullptr) is_permitted_parent (nits (), node_.version (), node_.id (), elem ());
        else is_permitted_parent (nits (), node_.version (), node_.id (), parent_ -> node_.id ());

        if (node_.version ().is_4_or_more ()) verify_microdata ();

        if (context.has_rdfa () && (node_.version () >= xhtml_1_0))
            if (    a_.known (a_vocab) || a_.known (a_about) || a_.known (a_content) || a_.known (a_datatype) || a_.known (a_inlist) ||
                    a_.known (a_instanceof) || a_.known (a_prefix) || a_.known (a_property) || a_.known (a_resource) || a_.known (a_typeof))
                if ((flags & EF_NULL_DATATYPE) == EF_NULL_DATATYPE)
                    pick (nit_null_datatype, ed_rdfa, "6.3.1.3. XML Literals", es_comment, ec_rdfa, "RDFa attributes ignored when parent element has DATATYPE=\"\"");
                else
                {   if (a_.known (a_vocab)) examine_vocab ();
                    if (a_.known (a_about)) examine_about ();
                    if (a_.known (a_typeof)) examine_typeof ();
//                  if (a_.known (a_content)) examine_content ();
                    if (a_.known (a_datatype)) examine_datatype (flags);
                    if (a_.known (a_inlist)) examine_inlist ();
                    if (a_.known (a_instanceof)) examine_instanceof ();
                    if (a_.known (a_prefix)) examine_prefix ();
                    if (a_.known (a_property)) examine_property ();
                    if (a_.known (a_resource)) examine_resource ();
                    if (a_.known (a_rel)) examine_rdfa_rel (a_.get_string (a_rel));
                    if (a_.known (a_rev)) examine_rdfa_rev (a_.get_string (a_rev)); }

        if (node_.version ().is_5 ())
            if (a_.known (a_xmllang))
                if (! a_.known (a_lang))
                {   if (! node_.version ().xhtml ())
                        if (node_.id ().is_svg () && (node_.version ().svg_version () == sv_1_1))
                            if (a_.good (a_xmllang)) pick (nit_no_lang, es_info, ec_attribute, "to avoid a conflict between the SVG 1.1 and most HTML 5 specifications, add lang=", quote (a_.get_string (a_xmllang)));
                            else pick (nit_no_lang, es_info, ec_attribute, "to avoid a conflict between the SVG 1.1 and most HTML 5 specifications, add a lang attribute");
                        else pick (nit_no_xmllang, ed_50, "3.2.5.3 The lang and xml:lang attributes", es_error, ec_attribute, "'Authors must not use LANG in the XML namespace on HTML elements in HTML documents'"); }
                else if (a_.known (a_lang) && (a_.get_string (a_lang) != a_.get_string (a_xmllang)))
                    pick (nit_lang_xmllang, ed_50, "3.2.5.3 The lang and xml:lang attributes", es_error, ec_attribute, "if both LANG and xml:lang are specified, they must have the same value");

        if (node_.version () >= html_apr21)
        {   if (a_.known (a_aria_checked)) examine_aria_checked ();
            if (a_.known (a_aria_colspan)) examine_aria_colspan ();
            if (a_.known (a_aria_disabled)) examine_aria_disabled ();
            if (a_.known (a_aria_hidden)) examine_aria_hidden ();
            if (a_.known (a_aria_placeholder)) examine_aria_placeholder ();
            if (a_.known (a_aria_readonly)) examine_aria_readonly ();
            if (a_.known (a_aria_required)) examine_aria_required ();
            if (a_.known (a_aria_rowspan)) examine_aria_rowspan ();
            if (a_.known (a_aria_valuemax)) examine_aria_valuemax ();
            if (a_.known (a_aria_valuemin)) examine_aria_valuemin (); }

        if (a_.known (a_accesskey)) examine_accesskey ();
        if (a_.known (a_clip)) examine_clip ();
        if (a_.known (a_content)) examine_content ();
        if (a_.known (a_href)) examine_href ();
        if (a_.known (a_itemscope)) examine_itemscope (itemscope_);
        if (a_.known (a_itemtype)) examine_itemtype (itemscope_);

        if (a_.known (a_itemprop))
        {   examine_itemprop (itemscope_);
            if (itemscope_.get () != nullptr)
                if ((tag == elem_a) || (tag == elem_area) || (tag == elem_link))
                    vit_ = sought_itemtypes (); }

        if (context.links ())
            if (a_.has_url ())
                a_.verify_url (nits (), node_.version (), *this);

        if (a_.known (a_keytimes)) examine_keytimes ();
        if (a_.known (a_keysplines)) examine_keysplines ();
        if (a_.known (a_other)) examine_other ();
        if (a_.known (a_ref)) examine_ref ();
        if (a_.known (a_registrationmark)) examine_registrationmark ();
        if (a_.known (a_style)) examine_style_attr ();
        if (a_.known (a_xlinkhref)) examine_xlinkhref ();

        if (node_.line () >= 0) get_ids ().data (node_.line ());
        a_.invalid_id (nits (), node_.version (), get_ids (), this);
        a_.invalid_access (nits (), node_.version (), access_);

        pre_examine_element ();

        if (a_.known (a_autofocus)) examine_autofocus ();
        if (a_.known (a_defaultaction)) examine_defaultaction ();
        if (a_.known (a_draggable)) examine_draggable ();
        if (a_.known (a_class)) postprocess = examine_class ();
        if (a_.known (a_line_increment)) examine_line_increment ();

        if (context.microformats ())
        {   if (a_.known (a_rel)) examine_rel (a_.get_string (a_rel));
            if (a_.known (a_rev)) examine_rel (a_.get_string (a_rev)); }

        if (mf_ && a_.has (a_href))
            if (a_.known (a_href))
            {   ::std::string href (a_.get_string (a_href));
                VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
                if  (mf_ -> allocated (r_webmention))
                    context.webmention (nits (), href, tag == elem_link ? wm_link : wm_addr);
                if (mf_ -> allocated (r_in_reply_to))
                    context.note_reply (name_, a_.get_string (a_id), href, quoted_limited_string (text ())); } }

    examine_children (flags);

    if (post_examine)
    {   post_examine_element ();
        if (a_.known (a_itemref)) examine_itemref (itemscope_); }
    if (postprocess)
        if (mf_)
        {   if (mf_ -> allocated (h_entry))
            {   note_reply < in_reply_to_at > ();
                note_reply < like_of_at > ();
                note_reply < repost_of_at > ();
                note_reply < rsvp_at > ();
                note_reply < bookmark_of_at > (); }
            mf_ -> verify (nits (), node_.version ()); }
    examined_ = true; }

bool element::to_sibling (element_ptr& e, const bool canreconstruct)
{   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    if (! e -> has_next ()) return false;
    element_ptr x (e -> next (canreconstruct));
    x.swap (e);
    return true; }

void element::examine_children (const flags_t flags)
{   if (has_child ())
    {   attribute_bitset ancestral_attributes, sibling_attributes;
        itemscope_ptr itemscope;
        if (tag () == elem_template)
            ancestral_attributes = own_attributes_;
        else
        {   ancestral_attributes = ancestral_attributes_;
            itemscope = itemscope_; }
        element_ptr e = child ();
        do
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            e -> examine_self (itemscope, ancestral_attributes, sibling_attributes, flags);
            if (e -> node_.is_closure ())
                closure_uid_ = e -> uid_;
            else
            {   sibling_attributes |= e -> own_attributes_;
                if (tag () != elem_template)
                {   descendant_attributes_ |= e -> descendant_attributes_;
                    descendant_attributes_ |= e -> own_attributes_; } } }
        while (to_sibling (e));
        e = child ();
        do
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            e -> sibling_attributes_ = sibling_attributes; }
        while (to_sibling (e)); } }

::std::string element::make_children (const int depth, const element_bitset& ancestral_elements)
{   ::std::string res;
    ancestral_elements_ = ancestral_elements;
    if (context.tell (e_structure))
    {   res += ::std::string (depth * 2, ' ');
        if (node_.is_closure ()) res += "/";
        res += node_.id ().name () + "\n"; }
    if (has_child ())
    {   element_bitset ancestors, siblings;
        element_ptr e = child (false);
        if (tag () == elem_template) ancestors.set (elem_template);
        else ancestors = ancestral_elements_ | node_.tag ();
        do
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            res += e -> make_children (depth + 1, ancestors);
            if (! e -> node_.is_closure ())
            {   siblings |= e -> node_.tag ();
                if (tag () != elem_template)
                {   descendant_elements_ |= e -> descendant_elements_;
                    descendant_elements_ |= e -> node_.tag (); } } }
        while (to_sibling (e, false));
        e = child (false);
        do
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            e -> sibling_elements_ = siblings; }
        while (to_sibling (e, false)); }
    return res; }

void element::verify_children ()
{   if (has_child ())
    {   element_ptr e = child ();
        do
        {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
            e -> verify (); }
        while (to_sibling (e)); } }

void element::verify ()
{   VERIFY_NOT_NULL (access_, __FILE__, __LINE__);
    if (node_.line () >= 0) get_ids ().data (node_.line ());
    a_.verify_id (*this);
    if (a_.has (a_headers)) examine_headers ();
    verify_children ();
    if (a_.has (a_list)) validate_input_id ();
    late_examine_element (); }

void element::verify_document ()
{   bool titled = (node_.version ().mjr () < 5) && (page_.count (elem_title) == 0);
    if (titled)
        pick (nit_title_required, ed_2, "5.2.1. Title", es_error, ec_element, "every document header must have <TITLE>");
    switch (node_.version ().mjr ())
    {   case 0 :
        case 1 :
        case 3 :
            break;
        case 2 :
            if (context.rfc_1867 ())
                for (element* f = find_first (elem_form); f != nullptr; f = find_next (elem_form, f))
                {   VERIFY_NOT_NULL (f, __FILE__, __LINE__);
                    for (element* inp = f -> find_first (elem_input); inp != nullptr; inp = find_next (elem_input, inp))
                    {   VERIFY_NOT_NULL (inp, __FILE__, __LINE__);
                        if (inp -> a_.has (a_type))
                        {   attr_type* it = reinterpret_cast < attr_type* > (inp -> a_.get (a_type).get ());
                            VERIFY_NOT_NULL (it, __FILE__, __LINE__);
                            if ((it -> good ()) && (::boost::to_lower_copy (it -> get_string ()) == "file"))
                            {   if (! f -> a_.has (a_enctype))
                                {   f -> pick (nit_file_requires_enctype, ed_rfc_1867, "2. HTML forms with file submission", es_warning, ec_element,
                                        "given the <INPUT TYPE=file>, add ENCTYPE='application/x-www-form-urlencoded'");
                                    inp -> pick (nit_file_requires_enctype, ed_rfc_1867, "2. HTML forms with file submission", es_warning, ec_element,
                                        "the enclosing FORM should have ENCTYPE='application/x-www-form-urlencoded' when using TYPE=file"); }
                                else
                                {   attr_enctype* enc = reinterpret_cast < attr_enctype* > (f -> a_.get (a_enctype).get ());
                                    PRESUME (enc != nullptr, __FILE__, __LINE__);
                                    if (enc -> good ())
                                    {   ::std::string ee (::boost::to_lower_copy (enc -> get_string ()));
                                        if ((ee != "application/x-www-form-urlencoded") && (ee != "multipart/form-data"))
                                            f -> pick (nit_form_urlencoded, ed_rfc_1867, "2. HTML forms with file submission", es_warning, ec_element,
                                                "given the <INPUT TYPE=file>, set ENCTYPE to 'application/x-www-form-urlencoded'"); } }
                                if (! f -> a_.has (a_method))
                                    f -> pick (nit_use_post, ed_rfc_1867, "2. HTML forms with file submission", es_warning, ec_element,
                                        "when <INPUT TYPE=file>, specify METHOD=post");
                                else
                                {   attr_method* m = reinterpret_cast < attr_method* > (f -> a_.get (a_method).get ());
                                    PRESUME (m != nullptr, __FILE__, __LINE__);
                                    if (m -> good ()) if (::boost::to_lower_copy (m -> get_string ()) != "post")
                                        f -> pick (nit_use_post, ed_rfc_1867, "2. HTML forms with file submission", es_warning, ec_element,
                                            "given the <INPUT TYPE=file>, prefer METHOD=post"); } } } } }
            break;
        case 4 :
            if ((page_.count (elem_frameset) > 0) && (page_.count (elem_body) > 0))
                pick (nit_frameset_body, ed_4, "16.2 Layout of frames", es_error, ec_element, "either <FRAMESET> or <BODY>, not both");
            break;
        default :
            if (page_.count (elem_title) == 0)
                pick (nit_title_required, ed_2, "5.2.1. Title", es_warning, ec_element, "the document header has no <TITLE>");
            if (! page_.charset_defined ())
                pick (nit_charset_redefined, ed_50, "4.2.5.5 Specifying the document's character encoding", es_comment, ec_element, "Consider specifying a charset in the document header");
            break; }
    verify (); }

::std::string element::report ()
{   ::std::ostringstream res;
    res << nits ().review ();
    for (element_ptr e = child_; e; e = e -> sibling_)
    {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
        res << e -> report (); }
    return res.str (); }

element* element::next_element (element* previous)
{   if (previous == nullptr) return nullptr;
    if (previous -> has_child ()) return previous -> child_.get ();
    if (previous -> has_next ()) return previous -> sibling_.get ();
    if (previous -> parent () == nullptr) return nullptr;
    element* res = previous;
    do
    {   VERIFY_NOT_NULL (res, __FILE__, __LINE__);
        res = res -> parent ();
        if (res -> has_next ()) return res -> next ().get ();
    } while ((res != nullptr) && (res -> tag () != elem_faux_document));
    return nullptr; }

element* element::find_next (const e_element e, element* previous)
{   VERIFY_NOT_NULL (previous, __FILE__, __LINE__);
    for (element* res (next_element (previous)); res != nullptr; res = next_element (res))
    {   VERIFY_NOT_NULL (res, __FILE__, __LINE__);
        if (res -> tag () == e) return res; }
    return nullptr; }

element* element::find_first (const e_element e)
{   if (! has_child ()) return nullptr;
    return find_next (e, child ().get ()); }

bool element::family_uids (const e_element e, uid_t& from, uid_t& to) const
{   if (tag () == e)
    {   from = uid_; to = closure_uid_; return true; }
    if (parent_ == nullptr) return false;
    return parent_ -> family_uids (e, from, to); }

::std::string element::term () const
{   switch (tag ())
    {   case elem_abbr :
            if (a_.known (a_title))
                if (a_.good (a_title)) return a_.get_string (a_title);
            break;
        case elem_dfn :
            if (a_.known (a_title))
            {   if (a_.good (a_title)) return a_.get_string (a_title);
                break; }
            if (has_child ())
            {   element_bitset bs (empty_element_bitset | elem_abbr | elem_faux_comment |elem_faux_ssi | elem_faux_stylesheet | elem_faux_whitespace);
                element* abr = nullptr;
                for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
                {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
                    if (! c -> node_.is_closure ())
                    {   if (! bs.test (c -> tag ())) return text ();
                        if (c -> tag () != elem_abbr) continue;
                        if (abr != nullptr) return text ();
                        abr = c; } }
                if (abr != nullptr)
                    if (abr -> a_.good (a_title))
                        return abr -> a_.get_string (a_title); }
            return text ();
        default :
            return text (); }
    return ::std::string (); }
