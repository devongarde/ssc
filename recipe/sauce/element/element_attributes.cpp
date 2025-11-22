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

#include "main/standard.h"
#include "element/element.h"
#include "webpage/page.h"
#include "microformat/family.h"
#include "microformat/field.h"
#include "microformat/sibling.h"
#include "type/type.h"
#include "attribute/attribute_classes.h"
#include "parser/text.h"

void element::span_check ()
{   if (a_.known (a_colspan))
    {   const auto x = a_.get_int (a_colspan);
        if ((x < 1) || (x > max_colspan))
            pick (nit_1000, ed_50, "4.9.11 Attributes common to td and th element", es_error, ec_attribute, "ROWSPAN must be greater than zero and less than 1001");
        const auto y = a_.get_int (a_rowspan);
        if ((y < 0) || (y > max_rowspan))
            pick (nit_bad_rowspan, ed_50, "4.9.11 Attributes common to td and th element", es_error, ec_attribute, "ROWSPAN must be a positive integer less than 65535"); } }

void element::examine_accesskey ()
{   if ((node_.version ().mjr () > 4) && (node_.version () < html_jul09))
        pick (nit_attribute_unrecognised_here, es_error, ec_attribute, "ACCESSKEY requires a different version of HTML"); }

void element::examine_animation_attributes ()
{   const e_svg_version sv = node_.version ().svg_version ();
    PRESUME ((sv != sv_none), __FILE__, __LINE__);
    bool block_add = false;
    if (a_.good (a_xlinkhref))
    {   auto xh (a_.get_x < attr_xlinkhref > ());
        if (! xh.is_simple_id ())
            pick (nit_anim_simple_id, ed_svg_1_0, "19.2.4 Attributes to identify the target element for an animation", es_error, ec_link, "here, XLINK:HREF must link to an animation under the same parent SVG"); }
    if (a_.good (a_href))
    {   auto hr (a_.get_x < attr_href > ());
        if (! hr.is_simple_id ())
            pick (nit_anim_simple_id, ed_svg_2_anim, "2.5. Attributes to identify the target element for an animation", es_error, ec_link, "here, HREF must link to an animation under the same parent SVG"); }
    if (a_.good (a_attributename))
    {   const e_attribute a = static_cast < e_attribute > (a_.get_int (a_attributename));
        if (sv > sv_1_1)
        {   const e_animation_type at = get_animation_type (a);
            bool bad = false;
            if (sv >= sv_2_0) switch (tag ())
            {   case elem_animate :
                case elem_set : bad = ((at == at_frequency) || (at == at_time));
                                block_add = ((at == at_url) || (at == at_other)); break;
                case elem_animatetransform : bad = (at != at_transform); break;
                default : bad = true; break; }
            else if (sv > sv_1_1) switch (tag ())
            {   case elem_animate :
                case elem_set : bad = (at == at_transform);
                                block_add = ((at == at_url) || (at == at_other) || (at == at_list)); break;
                case elem_animatecolour : bad = (at != at_colour) && (at != at_paint); break;
                case elem_animatemotion :
                case elem_animatetransform : bad = (at != at_transform); break;
                default : bad = true; break; }
            if (bad) pick ( nit_not_animatable, ed_svg_2_0, "2.18. Elements, attributes and properties that can be animated", es_warning, ec_type,
                            quote (attr :: name (a)), " cannot normally be animated by <", node_.id ().name (), "> in ", node_.version ().report ()); }
        if ((sv <= sv_1_1) && attr::first_version (a).svg_limited (sv))
        {   block_add = true;
            if ((sv == sv_1_0) && (tag () != elem_animate) && (tag () != elem_set))
                pick (nit_not_animatable, ed_svg_1_0, "Appendix N: Property Index", es_warning, ec_type, quote (attr :: name (a)), " can only be animated by <ANIMATE> or <SET>"); }
        if (block_add && a_.known (a_additive))
            pick (nit_not_animatable, ed_svg_2_0, "2.18. Elements, attributes and properties that can be animated", es_warning, ec_type, quote (attr :: name (a)), " cannot be animated when ADDITIVE is specified"); } }

void element::examine_autofocus ()
{   if (node_.version ().mjr () < 5) return;
    element* anc (this);
    if (tag () != elem_dialogue)
    {   anc = get_ancestor (elem_dialogue);
        if (anc == nullptr) anc = get_ancestor (elem_html);
        if (anc == nullptr) return; }
    VERIFY_NOT_NULL (anc, __FILE__, __LINE__);
    if (anc -> autofocus_ == nullptr)
        anc -> autofocus_ = this;
    else
    {   VERIFY_NOT_NULL (anc -> autofocus_, __FILE__, __LINE__);
        pick (nit_autofocus, es_error, ec_attribute, "there should be one AUTOFOCUS, yet a(n) <", anc -> autofocus_ -> node_.id ().name (), "> element above has one too");
        anc -> autofocus_ -> pick (nit_autofocus, es_error, ec_attribute, "there should be one AUTOFOCUS, yet a(n)  <", node_.id ().name (), "> element below has one too"); } }

bool element::examine_class (const lingo& lang)
{   if (! context.microformats ()) return true;
    ::std::string content (a_.get_string (a_class));
    if (content.empty ()) return false;
    vstr_t entries;
    bool res = false;
    ::boost::algorithm::split (entries, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    vhc_t vc;
    vc.reserve (entries.size ());
    unsigned mf_count = 0;
    for (auto x : entries)
        vc.push_back (html_class (nits (), node_.version (), x));
    for (auto c : vc)
        if (c.is_whatwg_draft ())
            pick (nit_whatwg_class, ed_jan07, "3.4.5. Classes", es_info, ec_attribute, "FYI, ", quote (c.name ()), " was once a draft HTML 5 standard class name.");
        else if (c.is_microformat_vocabulary ())
        {   ++mf_count;
            activate_microformats ();
            VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
            if (mf_ -> is_declared (c.get ()))
            {   if (context.mf_verify ()) pick (nit_duplicate_microformat, es_warning, ec_microformat, "ignoring duplicate ", quote (c.name ())); }
            else
            {   if (context.mf_verify ())
                    if (context.tell (es_debug))
                        pick (nit_mf_found, es_comment, ec_microformat, "microformat vocabulary ", quote (c.name ()), " (", c.get (), ") found");
                    else pick (nit_mf_found, es_comment, ec_microformat, "microformat vocabulary ", quote (c.name ()), " found");
                mf_ -> declare (c.get ());
                res = true; } }
    if (mf_count > 0)
    {   VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
        mf_ -> text (trim_the_lot_off (text ())); }
    bool unfound = false;
    for (auto c : vc)
        if (c.is_microformat_property ())
        {   const prop p (c);
            if (! p.invalid ())
            {   found_farm farm = find_farm (p.get ());
                element* prop_vocab_element = nullptr;
                if ((farm.second == c_error) || ! is_plausible_field (farm.second, p.get ()))
                {   unfound = true; continue; }
                VERIFY_NOT_NULL (farm.first, __FILE__, __LINE__);
                VERIFY_NOT_NULL (farm.first -> mf_, __FILE__, __LINE__);
                farm.first -> mf_ -> set_mf_value (nits (), node_.version (), farm.second, p.get (), *this);
                if (context.mf_verify ())
                {   farm.first -> mf_ -> verify_attributes (nits (), node_.version (), node_.id (), this, lang);
                    if (context.tell (es_detail))
                        pick (nit_prop_set, es_comment, ec_microformat, html_class::name (farm.second),
                            " property ", p.name (), " (", p.get (), ")", " set to ", quote (farm.first -> mf_ -> get_string (farm.second, p.get ())));
                    else pick (nit_prop_set, es_comment, ec_microformat, html_class::name (farm.second),
                            " property ", p.name (), " set to ", quote (farm.first -> mf_ -> get_string (farm.second, p.get ()))); }
                prop_vocab_element = farm.first;
                farm.first -> mf_put_vocab (farm.second, p);
                res = true;
                found_farm ancestral_farm = find_farm (p.get (), prop_vocab_element);
                if ((ancestral_farm.second != c_error) && (is_plausible_parent (nits (), farm.second, ancestral_farm.second, p.get ())))
                {   PRESUME (ancestral_farm.first -> mf_, __FILE__, __LINE__);
                    ancestral_farm.first -> mf_ -> set_mf_value (nits (), node_.version (), farm.second, p.get (), *prop_vocab_element);
                    if (context.mf_verify ())
                    {   ancestral_farm.first -> mf_ -> verify_attributes (nits (), node_.version (), node_.id (), this, lang);
                        if (context.tell (es_detail))
                            pick (nit_prop_set, es_comment, ec_microformat,
                                "parental ", html_class::name (ancestral_farm.second), " property ", p.name (), " (", p.get (), ")",
                                " set to ", quote (ancestral_farm.first -> mf_ -> get_string (ancestral_farm.second, p.get ())));
                         else pick (nit_prop_set, es_comment, ec_microformat,
                                "parental ", html_class::name (ancestral_farm.second), " property ", p.name (),
                                " set to ", quote (ancestral_farm.first -> mf_ -> get_string (ancestral_farm.second, p.get ()))); }
                    ancestral_farm.first -> mf_put_vocab (ancestral_farm.second, p,
                        EXPORT_ITEMPROP EXPORT_STRSEP EXPORT_ITEM EXPORT_STRSEP EXPORT_TYPE,
                        EXPORT_ITEMPROP EXPORT_STRSEP EXPORT_ITEM EXPORT_STRSEP EXPORT_PROPS);
                    res = true; } } }
    if (unfound && (mf_count > 1))
        for (auto c : vc)
            if (c.is_microformat_property ())
            {   const prop p (c);
                if (! p.invalid ())
                {   bool fraternal = false; // sibternal?!
                    const found_farm farm = find_farm (p.get ()); // should store this result beforehand rather than search for it again
                    if (context.mf_version1 ())
                    {   if ((farm.second != c_error) && is_plausible_field (farm.second, p.get ())) continue;
                        VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
                        for (auto bro : vc)
                            if (! bro.invalid ())
                            {   if (bro.is_microformat_vocabulary ()) continue;
                                if (bro.get () == c.get ()) continue;
                                const prop sis (bro); // my family's weird!
                                if (! is_plausible_sibling (p.get (), sis.get ())) continue;
                                mf_ -> set_mf_value (nits (), node_.version (), c.get (), p.get (), *this);
                                if (context.mf_verify ())
                                    if (context.tell (es_detail))
                                        pick (nit_sibling, es_comment, ec_microformat, html_class::name (farm.second), " property ", p.name (),
                                            " (", p.get (), "), sibling of property ", sis.name (),  " (", sis.get (), "), set to ", quote (mf_ -> get_string (c.get (), p.get ())));
                                    else pick (nit_sibling, es_comment, ec_microformat, html_class::name (farm.second), " property ", p.name (),
                                            ", sibling of property ", sis.name (), ", set to ", quote (mf_ -> get_string (c.get (), p.get ())));
                                fraternal = true;
                                break; } }
                    if (! fraternal && context.mf_verify ())
                        if (farm.second == c_error) pick (nit_no_vocab, es_error, ec_microformat, "cannot find vocabulary for ", quote (p.name ()));
                        else if (! is_plausible_field (farm.second, p.get ()))
                            pick (nit_no_plausible_vocab, es_error, ec_microformat, "cannot find plausible vocabulary for ", quote (p.name ())); } }
    return res; }

void element::examine_clip ()
{   if (node_.version ().svg_version () != sv_1_1) return;
    if ((tag () != elem_svg) || ancestral_elements_.test (elem_svg))
        pick (nit_clipped, ed_svg_1_1, "6.1 SVG's styling properties", es_error, ec_attribute, "CLIP can only be applied to an outermost <SVG> in SVG 1.1"); }

void element::examine_content ()
{   if (tag () == elem_meta) return;
    if (context.rdfa () || node_.version().is_svg_12 ()) return;
    switch (node_.version ().mjr ())
    {   case 0 :
        case 1 :
        case 2 :
        case 3 :    return;
        case 4 :    if (node_.version ().mnr () == 4) return;
                    break;
        default : break; }
    pick (nit_svg_rdf, es_info, ec_attribute, "CONTENT requires <META>, RDFa, SVG 1.2, or XHTML 2.0"); }

void element::examine_defaultaction ()
{   if (node_.version () == xhtml_2) return;
    if (node_.version ().is_svg_12 ())
        if (ancestral_elements_.test (elem_svg) || (node_.tag () == elem_svg)) return;
    pick (nit_svg_version, es_info, ec_attribute, "DEFAULTACTION requires an SVG 1.2 <SVG> parent, or XHTML 2.0"); }

void element::examine_draggable ()
{   if (node_.version ().mjr () < 5) return;
    PRESUME (a_.has (a_draggable) && a_.known (a_draggable), __FILE__, __LINE__);
    if (! a_.known (a_title) && (node_.version () >= html_jan13))
        pick (nit_title_required, ed_51, "5.7.7. The draggable attribute", es_warning, ec_attribute, "An element with DRAGGABLE should also define TITLE"); }

void element::examine_headers ()
{   if (! a_.known (a_headers)) return;
    if (node_.version ().mjr () < 5) return;
    uid_t tuid_first, tuid_last;
    if (! family_uids (elem_table, tuid_first, tuid_last))
        pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "HEADERS must be applied to a descendant of <TABLE>");
    else
    {   vstr_t ids = a_.get_x < attr_headers > ();
        for (auto s : ids)
            if (get_ids ().has_id (s))
                if (get_ids ().get_tag (s) != elem_th)
                    pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "id ", quote (s), " is not applied to a <TH>");
                else
                {   const uid_t uid = get_ids ().get_uid (s);
                    if ((uid < tuid_first) || (uid > tuid_last))
                        pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "id ", quote (s), " is applied to a <TH> in a different <TABLE>"); } } }

void element::examine_href ()
{   if (node_.version () == xhtml_2) return;
    if (node_.id ().is_math ())
        if (context.math_version () < math_3)
            if (tag () != elem_image)
                pick (nit_math_href, ed_math_3, "2.1.6 Attributes Shared by all MathML Elements", es_error, ec_attribute, "HREF requires MathML 3"); }

void element::examine_keysplines ()
{   if (! a_.known (a_keytimes))
        pick (nit_keysplines, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_warning, ec_attribute, "KEYSPLINES requires KEYTIMES");
    else if (a_.good (a_keytimes))
    {   auto ks = a_.get_x < attr_keysplines > ();
        const ::std::size_t n = ks.size ();
        auto kt = a_.get_x < attr_keytimes > ();
        const ::std::size_t m = kt.size ();
        if ((m > 0) && (n != (m - 1)))
            pick (nit_keytimes, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "KEYSPLINES requires one less entry than KEYTIMES"); } }

void element::examine_keytimes ()
{   auto kt = a_.get_x < attr_keytimes > ();
    const ::std::size_t n = kt.size ();
    if (! a_.known (a_values))
    {   if (n != 2) pick (nit_keytimes, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "KEYTIMES without VALUES should have precisely two numbers");
        return; }
    if (! a_.good (a_values)) return;
    auto vl = a_.get_x < attr_values > ();
    const ::std::size_t m = vl.size ();
    if (n != m)
        pick (nit_keytimes, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "KEYTIMES must have the same quantity of numbers as VALUES"); }

void element::examine_langs (lingo& lang)
{   if (a_.good (a_xmllang))
    {   lang = lingo (nits (), a_.original (a_xmllang));
        if (node_.version ().xhtml ()) return; }
    if (a_.good (a_lang))
        lang = lingo (nits (), a_.original (a_lang)); }

void element::examine_line_increment ()
{   if ((! node_.version ().is_svg_12 ()) || (! ancestral_elements_.test (elem_svg)))
        pick (nit_line_increment, ed_svg_1_2_tiny, "10.11.4 The 'line-increment' property", es_error, ec_attribute, "LINE-INCREMENT requires SVG 1.2");
    else if ((node_.tag () != elem_textarea) || (! ancestral_elements_.test (elem_textarea)))
        pick (nit_line_increment, ed_svg_1_2_tiny, "10.11.4 The 'line-increment' property", es_error, ec_attribute, "LINE-INCREMENT requires a <TEXTAREA> ancestor"); }

void element::examine_descendant_in (const element* filter)
{   VERIFY_NOT_NULL (filter, __FILE__, __LINE__);
    if (a_.known (a_in))
    {   ::std::string s (a_.get_string (a_in));
        nitpick nuts;
        if (! test_value < t_inky > (nuts, node_.version (), s))
            if (! filter -> has_result (s))
            {   node_.merge (nuts);
                pick (nit_bad_result, ed_svg_1_1, "15.7.2 Common attributes", es_error, ec_attribute, quote (s), " is neither a filter primitive nor a result associated with the current filter"); } }
    for (element* p = child_; p != nullptr; p = p -> sibling_)
        p -> examine_descendant_in (filter); }

void element::examine_other ()
{   if (node_.id ().is_math ())
        if (context.math_version () > math_1)
            pick (nit_deprecated_attribute, ed_math_3, "2.1.6 Attributes Shared by all MathML Elements", es_warning, ec_attribute, "except in MathML 1, OTHER is deprecated"); }

void element::examine_popovertarget ()
{   if (! a_.known (a_popovertargetaction)) return;
    if (node_.version ().mjr () < 5) return;
    if (! a_.good (a_popovertargetaction)) return;
    ::std::string id (a_.get_string (a_popovertargetaction));
    if (get_ids ().has_id (id))
    {   const element* pel = get_ids ().get_element (id);
        if (pel != nullptr)
            if (! pel -> a_.known (a_popover))
                pick (nit_bad_header_id, ed_jun23, "6.11.1 The popover target attributes", es_error, ec_attribute, "id ", quote (id), " must reference an element with a POPOVER attribute"); } }

void element::examine_rel (const ::std::string& content, const lingo& lang, const char* const an)
{   switch (node_.tag ())
    {   case elem_a :
        case elem_area :
        case elem_form :
        case elem_link :
            break;
        default :
            return; }
    const bool tis5 = node_.version ().is_5 ();
    if (content.empty ())
    {   if (tis5) pick (nit_link_rel_off, ed_50, "4.2.4 The link element", es_error, ec_attribute, an, " cannot be empty");
        return; }
    vstr_t entries, ve;
    rel vr;
    prop vp;
    const ::std::string el (::std::string ("<") + node_.id ().name () + ">");
    const bool anal = context.analysis () >= anal_aug25;
    const bool has_blocking = a_.known (a_blocking);
    const bool has_href = a_.known (a_href);
    const bool has_imagesrcset = a_.known (a_imagesrcset);
    const bool has_media = a_.known (a_media);
    const bool under_head = ancestral_elements_.test (elem_head);
    const bool under_body = ancestral_elements_.test (elem_body);
    bool blocker = false, icon = false, preload = false, modulepreload = false, maskicon = false, serviceworker = false, stylesheet = false, external = has_imagesrcset, internal = false;
    if (has_href)
    {   const vurl_t& us = a_.get_urls (a_href);
        for (auto u : us)
        {   if (u.is_self ()) internal = true;
            else external = true;
            if (internal && external) break; } }
    ::boost::algorithm::split (entries, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    ve.reserve (entries.size ());
    for (auto x : entries)
    {   rel r (nits (), node_.version (), x);
        if (r.unknown ())
        {   pick (nit_unrecognised_rel, es_warning, ec_attribute, "unknown ", an, " type ", quote (x), " encountered");
            continue; }
        if (anal)
        {   if (r.invalid ()) continue;
            const html_version from (r.first ());
            const flags_t flags = from.flags ();
            if (tis5 && (r.get () != r_curie))
            {   if (! may_apply (node_.version (), from, r.last ()))
                {   if (from.is_mf ()) pick (nit_rel_version, es_comment, ec_attribute, el, " ", an, "=", quote (x), " is not standard in ", node_.version ().report (), " (3)");
                    else pick (nit_rel_version, es_info, ec_attribute, el, " ", an, "=", quote (x), " is not standard in ", node_.version ().report (), " (2)"); }
                if (! from.is_rel ())
                {   e_severity sv = es_info;
                    if (context.rel ()) sv = es_debug; else if (from.is_mf ()) sv = es_comment;
                    pick (nit_rel_version, sv, ec_attribute, el, " ", an, "=", quote (x), " is not standard in ", node_.version ().report (), " (1)"); }
                if (from.not_production ())
                    pick (nit_rel_version, es_warning, ec_attribute, el, " ", an, "=", quote (x), " is merely proposed");
                if (from.posh ())
                    pick (nit_misplaced_rel, es_warning, ec_attribute, el, " ", an, "=", quote (x), " is not intended for use with HTML");
                if ((! external) && from.is_external ())
                    pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, an, "=", quote (x), " requires an external url");
                if ((! internal) && from.is_internal ())
                    pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, an, "=", quote (x), " requires an internal url"); }
            switch (node_.tag ())
            {   case elem_a :
                case elem_area :
                    if ((flags & HR_A_AREA) == 0)
                        pick (nit_rel_bad_element, ed_rel, "formats", es_error, ec_attribute, an, " ", quote (x), " cannot be applied to ", el);
                    break;
                case elem_form :
                    if ((flags & HR_FORM) == 0)
                        pick (nit_rel_bad_element, ed_rel, "formats", es_error, ec_attribute, an, " ", quote (x), " cannot be applied to ", el);
                    break;
                case elem_link :
                    if ((flags & HR_LINK) == 0)
                        pick (nit_rel_bad_element, ed_rel, "formats", es_error, ec_attribute, an, " ", quote (x), " cannot be applied to ", el);
                    else if (under_head)
                    {   if ((flags & HR_LINKHEAD) == 0)
                            pick (nit_misplaced_rel, ed_rel, "formats", es_error, ec_attribute, an, " ", quote (x), " cannot be used in under <HEAD>");  }
                    else if (under_body)
                    {   if ((flags & HR_LINKBODY) == 0)
                            pick (nit_misplaced_rel, ed_rel, "formats", es_error, ec_attribute, an, " ", quote (x), " cannot be used in under <BODY>");  }
                    break;
                default :
                    GRACEFUL_CRASH (__FILE__, __LINE__); }
            switch (r.get ())
            {   case r_apple_touch_icon :
                case r_icon :
                    icon = true;
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_IMAGE);
                    break;
                case r_maskicon :
                    maskicon = true;
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_IMAGE);
                    break;
                case r_modulepreload :
                    modulepreload = blocker = true;
                    break;
                case r_preload :
                    preload = blocker = true;
                    break;
                case r_serviceworker :
                    serviceworker = true;
                    break;
                case r_stylesheet :
                    stylesheet = blocker = true; 
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_STYLE);
                    break;
                case r_feed :
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE | MIME_XML | MIME_APPLICATION);
                    break;
                case r_contact :
                case r_first :
                case r_next :
                case r_prev :
                case r_search :
                case r_up :
                case r_author :
                case r_help :
                case r_licence :
                case r_canonical : 
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE);
                    break;
                default : break; }
            if (tis5 && has_blocking && ! blocker)
                pick (nit_blocking, ed_apr22, "4.2.4 The link element", es_error, ec_attribute, "<LINK> with BLOCKING requires REL='stylesheet', REL='preload', or REL='modulepreload'."); }
        if (r.is_microformat_property ())
        {   activate_microformats ();
            VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
            if (mf_ -> is_declared (r.get ()))
            {   if (context.mf_verify ()) pick (nit_duplicate_rel, es_warning, ec_attribute, "ignoring duplicate ", quote (r.name ())); }
            else
            {   mf_ -> declare (r.get ());
                mf_ -> verify_attributes (nits (), node_.version (), node_.id (), this, lang);
                if (context.mf_verify ())
                    if (context.tell (es_variable)) pick (nit_rel_found, es_comment, ec_attribute, an, " type ", quote (r.name ()), " (", r.get (), ") found");
                    else pick (nit_rel_found, es_comment, ec_attribute, an, " type ", quote (r.name ()), " found");
                const prop p (r);
                if (! p.invalid ())
                {   mf_ -> set_mf_value (nits (), node_.version (), r.get (), p.get (), *this);
                    if (ve.empty ()) { vr = r; vp = p; }
                    ve.push_back (x); } } } }
    if (anal && (node_.tag () == elem_link))    
    {   if (! icon) if (a_.known (a_sizes))
            pick (nit_daft_rel_attr, ed_50, "4.2.4 The link element", es_error, ec_attribute, "SIZES requires ", an, "=\"icon\"");
        if (! maskicon) if (a_.known (a_colour))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "COLOR (sic) requires ", an, "=\"mask-icon\"");
        if (! stylesheet) if (a_.known (a_disabled))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "DISABLED requires ", an, "=\"stylesheet\"");
        if (preload)
        {   if (! a_.known (a_as))
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, an, "=\"preload\" requires AS"); }
        else
        {   if (a_.known (a_imagesizes))
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESIZES requires ", an, "=\"preload\"");
            if (has_imagesrcset)
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESRCSET requires ", an, "=\"preload\"");
            if (! modulepreload)
            {   if (a_.known (a_as))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "AS requires ", an, "=\"preload\" or \"modulepreload\"");
                if (! stylesheet) if (a_.known (a_integrity))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "INTEGRITY requires ", an, "=\"stylesheet\", \"preload\" or \"modulepreload\""); } }
        if (! serviceworker)
            if (a_.known (a_scope) || a_.known (a_updateviacache) || a_.known (a_workertype))
                pick (nit_no_serviceworker, ed_jul17, "4.2.4 The link element", es_error, ec_attribute, "SCOPE, UPDATEVIACACHE and WORKERTYPE each require ", an, "=\"serviceworker\""); 
        if (has_media)
            if (! stylesheet)
                pick (nit_media_ignored, ed_41, "12.3.2 Links and external style sheets", es_comment, ec_attribute, "MEDIA is for stylesheets, usually");
        if (stylesheet)
        {   bool is_css = false;
            if (a_.known (a_type))
            {   bool bad = ! a_.good (a_type);
                if (! bad)
                {   ::std::string ty (a_.get_string (a_type));
                    if (compare_no_case (ty, CSS_TYPE)) is_css = true;
                    else bad = true; }
                if (bad)
                    pick (nit_style_not_css, ed_50, "4.2.4 The link element", es_warning, ec_css, an, "=\"stylesheet\" requires TYPE=\"" CSS_TYPE "\"; ignoring non-CSS stylesheet"); }
            if (context.unknown_class () && context.load_css () && (node_.version ().css_version () >= css_1))
                if (has_href && a_.good (a_href))
                    if (is_css || page_ -> style_css ())
                    {   vurl_t v (a_.get_urls (a_href));
                        for (auto u : v)
                            if (! u.invalid ())
                            {   nitpick nuts;
                                const bool local = u.is_local ();
                                if (! context.cache ().empty () || ! local) pick (nit_gather, es_comment, ec_css, "gathering ", u.original ());
                                page_ -> css ().parse_file (nuts, node_.namespaces (), u, false, local, false, page_ -> xxx ());
                                if (page_ -> xxx () || context.extra () || ! local)
                                    nits ().merge (nuts); } } } } }

void element::examine_ref ()
{   if (! a_.known (a_template))
        pick (nit_bad_ref, ed_jan08, "4.12.5 Global attributes for data templates", es_error, ec_attribute, "REF requires TEMPLATE"); }

void element::examine_registrationmark ()
{   if (! ancestral_elements_.test (elem_rule))
        pick (nit_registration_mark, ed_jan08, "4.12.5 Global attributes for data templates", es_error, ec_attribute, "an element with REGISTRATIONMARK must descend from <RULE>"); }

void element::examine_spellcheck (flags_t& flags)
{   if (a_.good (a_spellcheck) && ! a_.empty (a_spellcheck))
        if (a_.get_int (a_spellcheck) == 0) flags |= EP_NOSPELL;
        else flags &= ~EP_NOSPELL; }

void element::examine_style_attr ()
{   if (node_.version () >= html_2)
        if ((context.css_version () == css_none) && (node_.version () < html_jul07))
            pick (nit_attribute_unrecognised_here, es_error, ec_attribute, "STYLE requires a more recent version of HTML");
        else if (a_.good (a_style) && ! a_.empty (a_style))
        {   ::std::string content = interpret_string (node_.nits (), node_.version (), a_.get_string (a_style));
            VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
            page_ -> css ().parse (content, node_.version (), node_.namespaces (), ancestral_elements_, true, node_.line (), tag ()); } }

void element::examine_tabindex ()
{   if (node_.version ().has_aria_html ())
        if (ancestral_roles_.any (no_tabindex_role_bitset))
            pick (nit_no_role_found, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_warning, ec_element, "Do not use TABINDEX when an ancestral element uses any ROLE ", rpt_role_bitset (no_tabindex_role_bitset)); }

void element::examine_xlinkhref ()
{   if (node_.id ().is_math ())
        if (ancestral_elements_.test (elem_math))
            if (context.math_version () >= math_3)
                pick (nit_math_href, ed_math_3, "2.1.6 Attributes Shared by all MathML Elements", es_warning, ec_attribute, "prefer HREF to XLINK:HREF in MathML 3"); }

void element::test_for_ancestral_role ()
{   if ((node_.version () >= html_aria_html) && context.aria ())
        if (! ancestral_attributes_.test (a_role))
            if (! any (ancestral_elements_, role_element_bitset))
                if ((tag () == elem_div) || (tag () == elem_span))
                    pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element, "It is ... recommended that authors add a role attribute to a semantically neutral element such as a div or span ...");
                else pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element, "It is ... recommended that authors add a role attribute to a semantically neutral (ancestral) element such as a div or span ..."); }

void element::test_for_ancestral_role (const role_bitset& permitted)
{   const bool can_any = permitted.test (role_any);
    const bool can_none = permitted.test (role_none);
    const bool can_any_none = can_any || can_none;
    const bool div_span = (tag () == elem_div) || (tag () == elem_span);
    if ((node_.version () >= html_aria_html) && context.aria ())
    {   if (! ancestral_attributes_.test (a_role))
        {   if (! any (ancestral_elements_, role_element_bitset))
                if (! can_none)
                    if (div_span)
                        pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element,
                            "It is ... recommended that authors add a role attribute to a semantically neutral element such as a div or span ...");
                    else pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element,
                        "It is ... recommended that authors add a role attribute to a semantically neutral (ancestral) element such as a div or span ...");
                else if (div_span)
                    pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element,
                        "Presuming no role given none found on a semantically neutral element such as a div or span ...");
                else pick (nit_role_missing, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element,
                    "Presuming no role given none found  a semantically neutral (ancestral) element such as a div or span ..."); }
        else if (! can_any_none)
        {   if (! ancestral_roles_.any (permitted))
                if (permitted.count () == 1)
                    pick (nit_role_conflict, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element,
                        "Conflicting ancestral ROLEs for <", id ().name (), "> found; the expected role is ", rpt_role_bitset (permitted));
                else pick (nit_role_conflict, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_warning, ec_element,
                    "Conflicting ancestral ROLEs for <", id ().name (), "> found; expected roles are ", rpt_role_bitset (permitted)); }
        else if (! can_any)
            if (! ancestral_roles_.any (permitted))
                if (permitted.count () == 1)
                    pick (nit_role_conflict, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element,
                        "Presuming no role, given conflicting ancestral ROLEs for <", id ().name (), "> found; the expected role is ", rpt_role_bitset (permitted));
                else pick (nit_role_conflict, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element,
                    "Presuming no role, given conflicting ancestral ROLEs for <", id ().name (), "> found; expected roles are ", rpt_role_bitset (permitted)); } }

void element::test_for_no_ancestral_role (const role_bitset& banned)
{   if ((node_.version () >= html_aria_html) && context.aria ())
        if (ancestral_roles_.any (banned))
            pick (nit_no_role_found, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_warning, ec_element, "Do not set <", id ().name (), "> when an ancestral element uses any ROLE ", rpt_role_bitset (banned)); }

void element::test_no_role ()
{   if ((node_.version () >= html_aria_html) && context.aria ())
        if (own_attributes_.test (a_role))
            pick (nit_aria_found, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_error, ec_element, "<", id ().name (), "> should not have a ROLE attribute");
        else if (ancestral_attributes_.test (a_role))
            pick (nit_no_role_found, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element, "<", id ().name (), "> should not have an ancestral ROLE attribute"); }

void element::test_no_role_no_aria ()
{   if ((node_.version () >= html_aria_html) && context.aria ())
        if (own_attributes_.test (a_role) || own_attributes_.any (aria_attribute_bitset))
            pick (nit_aria_found, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_error, ec_element, "<", id ().name (), "> should have neither a ROLE nor an ARIA attribute");
        else if (ancestral_attributes_.test (a_role) || ancestral_attributes_.any (aria_attribute_bitset))
            pick (nit_no_role_found, ed_aria_html, "4. Document conformance requirements for use of ARIA attributes in HTML", es_comment, ec_element, "<", id ().name (), "> should have neither ancestral ROLE nor any ancestral ARIA attributes"); }

void element::test_compatible_ancestral_role ()
{   if (ancestral_attributes_.test (a_role) && node_.version ().has_aria_html () && context.aria ())
    {   const flags_t cat = node_.id ().categories ();
        const bool flow = (cat & EF_5_FLOW) == EF_5_FLOW;
        const bool phrase = (cat & EF_5_PHRASE) == EF_5_PHRASE;
        const bool inter = (cat & EF_5_INTERACTIVE) == EF_5_INTERACTIVE;
        bool ok = true;
        if (flow || phrase)
            for (::std::size_t n = 0; ok&& (n < last_role); ++n)
                if (ancestral_roles_.test (n))
                {   const flags_t rf = enum_n < t_role, e_aria_role > :: flags (static_cast < e_aria_role > (n));
                    if (flow && ((rf & EF_5_FLOW) != EF_5_FLOW))
                    {   pick (nit_role_incompatible, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_error, ec_element, "The flow element <", id ().name (), "> is incompatible with the ancestral role ", enum_n < t_role, e_aria_role > :: name (static_cast < e_aria_role > (n)));
                        ok = false; break; }
                    if (inter && ((rf & EF_5_INTERACTIVE) == EF_5_INTERACTIVE))
                    {   pick (nit_role_incompatible, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_error, ec_element, "The interactive element <", id ().name (), "> is incompatible with the ancestral role ", enum_n < t_role, e_aria_role > :: name (static_cast < e_aria_role > (n)));
                        ok = false; break; }
                    if (phrase && ((rf & (EF_5_PHRASE | EF_5_INTERACTIVE)) != 0))
                    {   pick (nit_role_incompatible, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_error, ec_element, "The phrase element <", id ().name (), "> is incompatible with the ancestral role ", enum_n < t_role, e_aria_role > :: name (static_cast < e_aria_role > (n)));
                        ok = false; break; } } } }

void element::check_element_role (const e_aria_role ar)
{   if (context.aria ()) switch (ar)
    {   case role_article :
            if (ancestral_elements_.test (elem_article) || (tag () == elem_article))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The article role is not needed with <ARTICLE>");
            break;
        case role_banner :
            if (ancestral_elements_.test (elem_header) || (tag () == elem_header))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The banner role is not needed with <HEADER>");
            break;
        case role_cell :
            if (ancestral_elements_.test (elem_td) || (tag () == elem_td))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The cell role is not needed with <TD>");
            break;
        case role_complementary :
            if (ancestral_elements_.test (elem_aside) || (tag () == elem_aside))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The complementary role is not needed with <ASIDE>");
            break;
        case role_contentinfo :
            if (ancestral_elements_.test (elem_footer) || (tag () == elem_footer))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The contentinfo role is not needed with <FOOTER>");
            break;
        case role_definition :
            if (ancestral_elements_.test (elem_dfn) || (tag () == elem_dfn))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The definition role is not needed with <DFN>");
            break;
        case role_figure :
            if (ancestral_elements_.test (elem_figure) || (tag () == elem_figure))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The figure role is not needed with <FIGURE>");
            break;
        case role_form :
            if (ancestral_elements_.test (elem_form) || (tag () == elem_form))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The form role is not needed with <FORM>");
            break;
        case role_heading :
            if (ancestral_elements_.any (header_bitset) || header_bitset.test (tag ()))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The header role is not needed with a heading element");
            break;
        case role_img :
            if (ancestral_elements_.test (elem_img) || (tag () == elem_img) || ancestral_elements_.test (elem_picture) || (tag () == elem_picture))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The img role is not needed with <IMG> or <PICTURE>");
            break;
        case role_list :
            if (ancestral_elements_.test (elem_ol) || (tag () == elem_ol) || ancestral_elements_.test (elem_ul) || (tag () == elem_ul))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The list role is not needed with <OL> or <UL>");
            break;
        case role_listitem :
            if (ancestral_elements_.test (elem_li) || (tag () == elem_li))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The listitem role is not needed with <LI>");
            break;
        case role_main :
            if (ancestral_elements_.test (elem_main) || (tag () == elem_main))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The main role is not needed with <MAIN>");
            break;
        case role_meter :
            if (ancestral_elements_.test (elem_meter) || (tag () == elem_meter))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The meter role is not needed with <METER>");
            break;
        case role_navigation :
            if (ancestral_elements_.test (elem_nav) || (tag () == elem_nav))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The navigation role is not needed with <NAV>");
            break;
        case role_region :
            if (ancestral_elements_.test (elem_section) || (tag () == elem_section))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The region role is not needed with <SECTION>");
            break;
        case role_row :
            if (ancestral_elements_.test (elem_tr) || (tag () == elem_tr))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The row role is not needed with <TR>");
            break;
        case role_rowgroup :
            if (ancestral_elements_.any (rowgroup_bitset) || rowgroup_bitset.test (tag ()))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The group role is not needed with a row group element");
            break;
        case role_search :
            if (ancestral_elements_.test (elem_search) || (tag () == elem_search))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_warning, ec_attribute, "The search role is not needed with <SEARCH>");
            break;
        case role_separator :
            if (ancestral_elements_.test (elem_hr) || (tag () == elem_hr))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_info, ec_attribute, "The row role might not be needed with <HR>");
            break;
        case role_table :
            if (ancestral_elements_.test (elem_table) || (tag () == elem_table))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_info, ec_attribute, "The table role is not needed with <TABLE>");
            break;
        case role_term :
            if (ancestral_elements_.test (elem_dfn) || (tag () == elem_dfn))
                pick (nit_unnecessary_role, ed_aria_mdn, "WAI-ARIA Roles", es_info, ec_attribute, "The term role is not needed with <DFN>");
            break;
        default :
            break; } }

void element::examine_role ()
{   if (node_.version ().has_aria_html () && context.aria ())
        if (a_.known (a_role) && a_.good (a_role))
            for (auto r : a_.get_ints (a_role))
            {   e_aria_role ar = furq_at (static_cast < e_aria_role > (r), 0);
                if (ar == role_any) continue;
                check_element_role (ar);
                bool ok = false;
                for (::std::size_t sz = 0; (ar != role_any) && ! ok; )
                    if (descendant_roles_.test (ar)) ok = true;
                    else ar = furq_at (static_cast < e_aria_role > (r), ++sz);
                if (! ok)
                    pick (nit_role_incompatible, ed_aria_html, "5. Allowed descendants of ARIA roles ", es_error, ec_element, "Required descendent of ROLE ", enum_n < t_role, e_aria_role > :: name (ar), " missing"); } }
