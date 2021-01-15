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

bool element::naughty_label_descendents (const element* e, const uid_t uid, bool& first)
{   bool res = false;
    for (element* c = e -> child_.get (); c != nullptr; c = c -> sibling_.get ())
        if (is_standard_element (c -> tag ()) && ! c -> node_.is_closure ())
        {   if (c -> uid_ != uid)
                if (label_bitset.test (c -> tag ()))
                    if (first) first = false;
                    else
                    {   res = true;
                        c -> pick (nit_label_parentage, ed_50, "4.10.4 The label element", es_error, ec_attribute, "<", elem::name (c -> tag ()), "> cannot have a <LABEL> ancestor"); }
            if (c -> has_child ())
                if (naughty_label_descendents (c, uid, first)) res = true; }
    return res; }

void element::examine_label ()
{   if (node_.version ().mjr () >= 5)
    {   check_ancestors (elem_label, element_bit_set (elem_label));
        no_anchor_daddy ();
        uid_t uid = 0;
        if (a_.good (a_for))
        {   ::std::string s (a_.get_string (a_for));
            if (ids_.has_id (s)) // if not WTF
            {   e_element e (ids_.get_tag (s));
                if (! label_bitset.test (e))
                    pick (nit_bad_for, ed_50, "4.10.4 The label element", es_error, ec_element, "FOR must reference a <BUTTON>, <FIELDSET>, <INPUT>, <OBJECT>, <OUTPUT>, <SELECT>, or a <TEXTAREA>");
                uid = ids_.get_uid (s); } }
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
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
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
                    break; } }

void element::examine_li ()
{   if ((node_.version ().mjr () >= 5) && a_.known (a_value))
        switch (w3_minor_5 (node_.version ()))
        {   case 0 :
                if (! ancestral_elements_.test (elem_ol))
                    pick (nit_value_ol, ed_50, "4.4.7 The li element", es_error, ec_element, "VALUE requires an <OL> parent");
                break;
            case 2 :
            case 3 :
                if (ancestral_elements_.test (elem_ul))
                    pick (nit_value_ol, ed_52, "4.4.7 The li element", es_error, ec_element, "VALUE is not permitted under <UL>");
                break;
            default :
                if (ancestral_elements_.test (elem_ul) || ancestral_elements_.test (elem_menu))
                    pick (nit_value_ol, ed_51, "4.4.7 The li element", es_error, ec_element, "VALUE is not permitted under <UL> or <MENU>");
                break; } }

void element::examine_link ()
{   if (node_.version ().mjr () < 4) return;
    bool tis5 = (node_.version ().mjr () > 4);
    bool has_rel = a_.known (a_rel);
    bool has_itemprop = a_.known (a_itemprop);
    bool has_imagesrcset = a_.known (a_imagesrcset);
    bool has_imagesizes = a_.known (a_imagesizes);
    e_element mummy = parent_ -> tag ();
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
    if (! has_rel)
    {   if (tis5)
            if (node_.version ().w3 ())
                pick (nit_link_rel_off, ed_50, "4.2.4 The link element", es_error, ec_attribute, "<LINK> must have REL");
            else if (! has_itemprop)
                pick (nit_link_rel_off, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "<LINK> must have either REL or ITEMPROP");
        return; }
    ::std::string content (a_.get_string (a_rel));
    if (content.empty ())
    {   if (tis5) pick (nit_link_rel_off, ed_50, "4.2.4 The link element", es_error, ec_attribute, "REL cannot be empty");
        return; }
    vstr_t entries;
    ::boost::algorithm::split (entries, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    bool icon = false, preload = false, modulepreload = false, maskicon = false, serviceworker = false, stylesheet = false, external = has_imagesrcset, as_image = false;
    bool href = a_.known (a_href);
    if (href && ! external)
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
    if (node_.version () >= html_jul20)
        if (! href && ! has_imagesrcset)
            pick (nit_link, ed_jul20, "4.2.4 The link element", es_warning, ec_attribute, "<LINK> requires HREF or IMAGESRCSET");
    for (auto s : entries)
    {   rel r (node_.nits (), node_.version (), s);
        if (r.invalid ()) continue;
        if (r.is_microformat () && context.microformats ()) continue; // microformats are processed later
        if (tis5)
        {   html_version from (r.first ());
            ::std::size_t flags = static_cast < ::std::size_t > (from.flags () & 0xFFFFFFFF);
            flags >>= (w3_minor_5 (node_.version ()) * 4);
            flags &= 0x0000000F;
            if (flags == 0)
            {   pick (nit_link_rel_off, es_comment, ec_attribute, quote (s), " is not a HTML standard <LINK> REL value");
                continue; }
            // apparently, sometimes in VC19, 0x6622 & 0x0001 is 0x6620. This is called a bug. Wonderful. It seems &= works, though, so...
            ::std::size_t bug_bypasser = flags;
            bug_bypasser &= HR_LINK;
            if (bug_bypasser == 0)
            {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, quote (s), " cannot be used with <LINK>"); continue; }
            else if (ancestral_elements_.test (elem_body))
            {   bug_bypasser = flags;
                bug_bypasser &= HR_LINKBODY;
                if (bug_bypasser == 0)
                {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, quote (s), " can only be used with <LINK> under <HEAD>, not <BODY>"); continue; } }
            if (! external)
            {   bug_bypasser = flags;
                bug_bypasser &= HR_EXTERNAL;
                if (bug_bypasser != 0)
                {   pick (nit_link_rel_off, ed_53, "4.8.6. Link types", es_error, ec_attribute, quote (s), " requires an external url"); continue; } } }
        bool headonly = true;
        switch (r.get ())
        {   case r_apple_touch_icon :
            case r_icon : icon = true; break;
            case r_bodyok : headonly = false; break;
            case r_maskicon : maskicon = true; break;
            case r_modulepreload : modulepreload = true; break;
            case r_preload : preload = true; break;
            case r_serviceworker : serviceworker = true; break;
            case r_stylesheet : stylesheet = true; break;
            case r_alternative :
            case r_dnsprefetch :
            case r_manifest :
            case r_next :
            case r_pingback :
            case r_preconnect :
            case r_prefetch :
            case r_search : break;
            default : headonly = false; break; }
        if (headonly && ! ancestral_elements_.test (elem_head))
            pick (elem_rel_head, ed_jul20, "4.2.4 The link element", es_warning, ec_attribute, quote (s), " needs <LINK> to be in <HEAD>"); }
    if (tis5)
    {   if (! icon) if (a_.known (a_sizes))
            pick (nit_daft_rel_attr, ed_50, "4.2.4 The link element", es_error, ec_attribute, "SIZES is only useful when REL includes \"icon\"");
        if (! maskicon) if (a_.known (a_colour))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "COLOR (sic) is only useful when REL includes \"mask-icon\"");
        if (! stylesheet) if (a_.known (a_disabled))
            pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "DISABLED requires a REL \"stylesheet\"");
        if (preload)
        {   if (! a_.known (a_as))
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "the \"preload\" REL value requires AS"); }
        if (! preload)
        {   if (has_imagesizes)
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESIZES is only useful when REL includes \"preload\"");
            if (has_imagesrcset)
                pick (nit_daft_rel_attr, ed_jul20, "4.2.4 The link element", es_error, ec_attribute, "IMAGESRCSET is only useful when REL includes \"preload\"");
            if (! modulepreload)
            {   if (a_.known (a_as))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "AS is only useful when REL includes \"preload\" or \"modulepreload\"");
                if (! stylesheet) if (a_.known (a_integrity))
                    pick (nit_daft_rel_attr, ed_53, "4.2.4 The link element", es_error, ec_attribute, "INTEGRITY is only useful when REL includes \"stylesheet\", \"preload\" or \"modulepreload\""); } }
        if (! serviceworker)
            if (a_.known (a_scope) || a_.known (a_updateviacache) || a_.known (a_workertype))
                pick (nit_no_serviceworker, ed_jul17, "4.2.4 The link element", es_error, ec_attribute, "the SCOPE, UPDATEVIACACHE and WORKERTYPE attributes require the \"serviceworker\" REL value"); }
    if (stylesheet)
    {   bool is_css = false;
        if (a_.known (a_type))
        {   bool bad = ! a_.good (a_type);
            if (! bad)
            {   ::std::string ty (a_.get_string (a_type));
                if (compare_no_case (ty, CSS_TYPE)) is_css = true;
                else bad = true; }
            if (bad)
            {   pick (nit_style_not_css, ed_50, "4.2.4 The link element", es_warning, ec_css, "stylesheet TYPE is not text/css; ignored");
                return; } }
        if (context.unknown_class () && context.load_css ())
            if (href && a_.good (a_href))
                if (is_css || page_.style_css ())
                {   vurl_t v (a_.get_urls (a_href));
                    for (auto u : v)
                        if (! u.invalid ())
                        {   pick (nit_gather, es_comment, ec_css, "gathering CSS identifiers from ", u.original ());
                            context.css ().parse_file (nits (), page_, u); } } } }
