/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

bool element::naughty_label_descendents (const element* e, const uid_t uid, bool& first)
{   bool res = false;
    VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    for (element* c = e -> child_; c != nullptr; c = c -> sibling_)
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        if (is_standard_element (c -> tag ()) && ! c -> node_.is_closure ())
        {   if (c -> uid_ != uid)
                if (label_bitset.test (c -> tag ()))
                    if (first) first = false;
                    else
                    {   res = true;
                        c -> pick (nit_label_parentage, ed_50, "4.10.4 The label element", es_error, ec_attribute, "<", elem::name (c -> tag ()), "> cannot have a <LABEL> ancestor"); }
            if (c -> has_child ())
                if (naughty_label_descendents (c, uid, first)) res = true; } }
    return res; }

void element::examine_label ()
{   if (node_.version ().is_5 ())
    {   check_ancestors (elem_label, element_bitset (elem_label));
        no_anchor_daddy ();
        uid_t uid = 0;
        if (a_.good (a_for))
        {   if (a_.size (a_for) != 1)
                pick (nit_bad_for, ed_50, "4.10.4 The label element", es_error, ec_attribute, "FOR on <LABEL> may only have one ID");
            ::std::string s (a_.get_string (a_for));
            if (get_ids ().has_id (s)) // if not WTF
            {   const e_element e (get_ids ().get_tag (s));
                if (! label_bitset.test (e))
                    pick (nit_bad_for, ed_50, "4.10.4 The label element", es_error, ec_attribute, "FOR on <LABEL> must reference a <BUTTON>, <FIELDSET>, <INPUT>, <OBJECT>, <OUTPUT>, <SELECT>, or a <TEXTAREA>");
                uid = get_ids ().get_uid (s); } }
        element_bitset bs (descendant_elements_);
        bs &= label_bitset;
        bool first = (uid == 0);
        if (bs.any ())
            if (first)
            {   if (naughty_label_descendents (this, uid, first))
                    pick (nit_label_parentage, ed_50, "4.10.4 The label element", es_error, ec_element, "a <LABEL> without FOR can only have one form control descendant"); }
            else if (naughty_label_descendents (this, uid, first))
                pick (nit_label_parentage, ed_50, "4.10.4 The label element", es_error, ec_element, "a <LABEL> cannot have any form control descendants, except that indicated by FOR"); } }

void element::examine_lambda ()
{   if (node_.version ().math () < math_2) return;
    bool domain = false, other = false, bnoted = false, dnoted = false;
    for (element* c = child_; c != nullptr; c = c -> sibling_)
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        if (c -> node_.id ().is_math () && ! c -> node_.is_closure ())
            switch (c -> tag ())
            {   case elem_bvar :
                    if (domain || other)
                        if (! bnoted)
                        {   pick (nit_bad_bvar, ed_math_2, "4.4.2.9 Lambda (lambda)", es_error, ec_element, "Under <LAMBDA>, all <BVAR>s must precede other elements.");
                            bnoted = true; }
                    break;
                case elem_domainofapplication :
                    domain = true;
                    if (other)
                        if (! dnoted)
                        {   pick (nit_bad_doa, ed_math_2, "4.4.2.9 Lambda (lambda)", es_error, ec_element, "Under <LAMBDA>, a <DOMAINOFAPPLICATION> must follow any <BVAR>s but precede other elements.");
                            dnoted = true; }
                    break;
                default :
                    other = true;
                    break; } } }

void element::examine_li ()
{   if (a_.known (a_value))
        if (node_.version () >= html_jan16)
        {   if (ancestral_elements_.test (elem_ul) || ancestral_elements_.test (elem_menu))
                pick (nit_value_ol, ed_jul20, "4.4.7 The li element", es_error, ec_element, "<LI> VALUE is barred under <UL> or <MENU>"); }
        else if (! ancestral_elements_.test (elem_ol) && (node_.version ().mjr () > 5))
            pick (nit_value_ol, ed_50, "4.4.7 The li element", es_error, ec_element, "<LI> VALUE requires an <OL> parent"); }

void element::examine_link ()
{   if (node_.version ().mjr () < 4) return;
    const bool tis5 = node_.version ().is_5 ();
    const bool has_rel = a_.known (a_rel);
    const bool has_property = a_.known (a_property) && context.rdfa ();
    const bool has_itemprop = a_.known (a_itemprop);
    const bool has_imagesrcset = a_.known (a_imagesrcset);
    const bool has_imagesizes = a_.known (a_imagesizes);
    const bool has_media = a_.known (a_media);
    const bool has_type = a_.known (a_type);
    const bool has_href = a_.known (a_href);
    const bool has_blocking = a_.known (a_blocking);
    bool icon = false, preload = false, modulepreload = false, maskicon = false, serviceworker = false, stylesheet = false, external = has_imagesrcset, as_image = false;
    VERIFY_NOT_NULL (parent_, __FILE__, __LINE__);
    const e_element mummy = parent_ -> tag ();
    if (has_href && has_type) check_extension_compatibility (nits (), node_.version (), a_.get_string (a_type), a_.get_urls (a_href), false);
    if (tis5)
    {   if (node_.version () <= html_jul07)
        {   if (mummy != elem_head)
                pick (nit_bad_mummy, es_error, ec_element, "<LINK> must be a child of <HEAD>"); }
        else if (node_.version () <= html_jan08)
        {   if (mummy != elem_head)
                if (mummy != elem_noscript)
                    pick (nit_bad_mummy, es_error, ec_element, "<LINK> must be a child of <HEAD> or <NOSCRIPT>");
                else if (parent_ -> parent_ != nullptr)
                    if (parent_ -> parent_ -> tag () != elem_head)
                        pick (nit_bad_mummy, es_error, ec_element, "the <NOSCRIPT> parent of <LINK> must be a child of <HEAD>"); }
        if (has_rel && has_itemprop)
        {   pick (nit_link_rel_off, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "<LINK > must have either REL or ITEMPROP, but not both");
            return; } }
    if (has_href && ! external)
    {   vurl_t vu (a_.get_urls (a_href));
        for (auto u : vu)
            if (! u.is_simple_id ())
            {   external = true; break; } }
    if (a_.known (a_as))
        as_image = compare_no_case (trim_the_lot_off (a_.get_string (a_as)), "image");
    if (! as_image)
    {   if (has_imagesrcset)
            pick (nit_as_not_image, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "if IMAGESRCSET is used, AS must be set to \"image\"");
        if (has_imagesizes)
            pick (nit_as_not_image, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "if IMAGESIZES is used, AS must be set to \"image\""); }
    if (has_blocking && ! has_rel)
        pick (nit_blocking, ed_apr22, "4.2.4 The link element", es_error, ec_attribute, "<LINK> with BLOCKING requires REL");
    if (! has_property)
    {   if (! has_rel)
        {   if (tis5)
                if (node_.version ().w3 ())
                    pick (nit_link_rel_off, ed_50, "4.2.4 The link element", es_error, ec_attribute, "<LINK> must have REL");
                else if (! has_itemprop)
                    pick (nit_link_rel_off, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "<LINK> must have either REL or ITEMPROP");
            return; }
        if (node_.version () >= html_jul20)
            if (! has_href && ! has_imagesrcset)
                pick (nit_link, ed_jul20, "4.2.4 The link element", es_warning, ec_attribute, "<LINK> requires HREF or IMAGESRCSET"); }
    if (has_rel)
    {   ::std::string content (a_.get_string (a_rel));
        if (content.empty ())
        {   if (tis5) pick (nit_link_rel_off, ed_50, "4.2.4 The link element", es_error, ec_attribute, "REL cannot be empty");
            return; }
        vstr_t entries;
        ::boost::algorithm::split (entries, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
        for (auto s : entries)
        {   rel r (node_.nits (), node_.version (), s);
            if (r.invalid ()) continue;
            if (tis5 && (r.get () != r_curie))
            {   const html_version from (r.first ());
                if (! may_apply (node_.version (), from, r.last ()))
                {   if (from.is_mf ()) pick (nit_link_rel_off, es_comment, ec_attribute, "<LINK> REL=", quote (s), " is not standard in ", node_.version ().report (), " (3)");
                    else pick (nit_link_rel_off, es_info, ec_attribute, "<LINK> REL=", quote (s), " is not standard in ", node_.version ().report (), " (2)");
                    continue; }
                if (! from.is_rel ())
                {   e_severity sv = es_info;
                    if (context.rel ()) sv = es_debug; else if (from.is_mf ()) sv = es_comment;
                    pick (nit_link_rel_off, sv, ec_attribute, "<LINK> REL=", quote (s), " is not standard in ", node_.version ().report (), " (1)");
                    continue; }
                if (! from.is_mf ())
                    if (! from.is_link ())
                    {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, "REL=", quote (s), " cannot be used with <LINK>"); continue; }
                    else if (ancestral_elements_.test (elem_body))
                        if (! from.is_linkbody ())
                        {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, "REL=", quote (s), " requires <LINK> to be under <HEAD>, not <BODY>"); continue; }
                if (! external)
                    if (from.is_external ())
                    {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, "REL=", quote (s), " requires an external url"); continue; } }
            bool headonly = true;
            switch (r.get ())
            {   case r_apple_touch_icon :
                case r_icon : icon = true; check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_IMAGE); break;
                case r_maskicon : maskicon = true; check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_IMAGE); break;
                case r_bodyok : headonly = false; break;
                case r_modulepreload : modulepreload = true; break;
                case r_preload : preload = true; break;
                case r_serviceworker : serviceworker = true; break;
                case r_stylesheet : stylesheet = true; check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_STYLE); break;
                case r_tag :
                    if (node_.version () >= html_jan12)
                    {   pick (nit_link_rel_off, es_info, ec_attribute, "<LINK> REL=", quote (s), " is not valid in ", node_.version ().report ());
                        continue; }
                    break;
                case r_feed :
                    check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE | MIME_XML | MIME_APPLICATION);
                    break;
                case r_contact :
                case r_first :
                case r_next :
                case r_prev :
                case r_search :
                case r_up : check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE); break;
                case r_alternative :
                case r_manifest :
                case r_pingback :
                case r_preconnect :
                case r_prefetch :
                case r_prerender :
                case r_dnsprefetch : break;
                case r_author :
                case r_help :
                case r_licence :
                case r_canonical : check_extension_compatibility (nits (), node_.version (), a_.get_urls (a_href), MIME_PAGE); headonly = false; break;
                default : headonly = false; break; }
            if (headonly && ! ancestral_elements_.test (elem_head))
                pick (nit_rel_head, ed_jul20, "4.2.4 The link element", es_warning, ec_attribute, "<LINK> with REL=", quote (s), " should be under <HEAD>");
            if (has_blocking && ! stylesheet && ! preload && ! modulepreload)
                pick (nit_blocking, ed_apr22, "4.2.4 The link element", es_error, ec_attribute, "<LINK> with BLOCKING requires REL='stylesheet', REL='preload', or REL='modulepreload'."); } }
    if (tis5)
    {   if (! icon) if (a_.known (a_sizes))
            pick (nit_daft_rel_attr, ed_50, "4.2.4 The link element", es_error, ec_attribute, "SIZES requires REL=\"icon\"");
        if (! maskicon) if (a_.known (a_colour))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "COLOR (sic) requires REL=\"mask-icon\"");
        if (! stylesheet) if (a_.known (a_disabled))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "DISABLED requires REL=\"stylesheet\"");
        if (preload)
        {   if (! a_.known (a_as))
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "REL=\"preload\" requires AS"); }
        if (! preload)
        {   if (has_imagesizes)
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESIZES requires REL=\"preload\"");
            if (has_imagesrcset)
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESRCSET requires REL=\"preload\"");
            if (! modulepreload)
            {   if (a_.known (a_as))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "AS requires REL=\"preload\" or \"modulepreload\"");
                if (! stylesheet) if (a_.known (a_integrity))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "INTEGRITY requires REL=\"stylesheet\", \"preload\" or \"modulepreload\""); } }
        if (! serviceworker)
            if (a_.known (a_scope) || a_.known (a_updateviacache) || a_.known (a_workertype))
                pick (nit_no_serviceworker, ed_jul17, "4.2.4 The link element", es_error, ec_attribute, "SCOPE, UPDATEVIACACHE and WORKERTYPE each require REL=\"serviceworker\""); }
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
            {   pick (nit_style_not_css, ed_50, "4.2.4 The link element", es_warning, ec_css, "REL=\"stylesheet\" requires TYPE=\"" CSS_TYPE "\"; ignoring non-CSS stylesheet");
                return; } }
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
                                nits ().merge (nuts); } } } }
