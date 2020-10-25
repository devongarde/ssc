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

#include "standard.h"
#include "element.h"
#include "page.h"
#include "family.h"
#include "field.h"
#include "sibling.h"
#include "reldef.h"
#include "attribute_classes.h"

void element::span_check ()
{   if (a_.known (a_colspan))
    {   auto x = a_.get_int (a_colspan);
        if ((x < 1) || (x > 1000))
            pick (nit_1000, ed_50, "4.9.11 Attributes common to td and th element", es_error, ec_attribute, "ROWSPAN must be greater than zero and less than 1001");
        auto y = a_.get_int (a_rowspan);
        if ((y < 0) || (y > 65534))
            pick (nit_1000, ed_50, "4.9.11 Attributes common to td and th element", es_error, ec_attribute, "ROWSPAN must be a positive integer less than 65535"); } }

void element::examine_autofocus ()
{   if (node_.version ().major () < 5) return;
    element* anc (this);
    if (tag () != elem_dialogue)
    {   anc = get_ancestor (elem_dialogue);
        if (anc == nullptr) anc = get_ancestor (elem_html);
        if (anc == nullptr) return; }
    if (anc -> autofocus_ == nullptr)
        anc -> autofocus_ = this;
    else
    {   pick (nit_autofocus, es_error, ec_attribute, "there should be one AUTOFOCUS, yet a <", anc -> autofocus_ -> node_.id ().name (), "> element above has one too");
        anc -> autofocus_ -> pick (nit_autofocus, es_error, ec_attribute, "there should be one AUTOFOCUS, yet a  <", node_.id ().name (), "> element below has one too"); } }

bool element::examine_class ()
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
        if (c.is_microformat_vocabulary ())
        {   ++mf_count;
            activate_microformats ();
            if (mf_ -> is_declared (c.get ()))
            {   if (context.mf_verify ()) pick (nit_duplicate_microformat, es_warning, ec_microformat, "ignoring duplicate ", quote (c.name ())); }
            else
            {   if (context.mf_verify ())
                    if (context.tell (e_debug))
                        pick (nit_mf_found, es_comment, ec_microformat, "microformat vocabulary ", quote (c.name ()), " (", c.get (), ") found");
                    else pick (nit_mf_found, es_comment, ec_microformat, "microformat vocabulary ", quote (c.name ()), " found");
                mf_ -> declare (c.get ());
                res = true; } }
    if (mf_count > 0) mf_ -> text (trim_the_lot_off (text ()));
    bool unfound = false;
    for (auto c : vc)
        if (c.is_microformat_property ())
        {   prop p (c);
            if (! p.invalid ())
            {   found_farm farm = find_farm (p.get ());
                element* prop_vocab_element = nullptr;
                if ((farm.second == c_error) || ! is_plausible_field (farm.second, p.get ()))
                {   unfound = true; continue; }
                assert (farm.first -> mf_);
                farm.first -> mf_ -> set_mf_value (nits (), node_.version (), farm.second, p.get (), *this);
                if (context.mf_verify ())
                {   farm.first -> mf_ -> validate (nits (), node_.version (), node_.id ());
                    if (context.tell (e_detail))
                        pick (nit_prop_set, es_comment, ec_microformat, html_class::name (farm.second),
                            " property ", p.name (), " (", p.get (), ")", " set to ", quote (farm.first -> mf_ -> get_string (farm.second, p.get ())));
                    else pick (nit_prop_set, es_comment, ec_microformat, html_class::name (farm.second),
                            " property ", p.name (), " set to ", quote (farm.first -> mf_ -> get_string (farm.second, p.get ()))); }
                prop_vocab_element = farm.first;
                farm.first -> mf_put_vocab (farm.second, p);
                res = true;
                found_farm ancestral_farm = find_farm (p.get (), prop_vocab_element);
                if ((ancestral_farm.second != c_error) && (is_plausible_parent (nits (), farm.second, ancestral_farm.second, p.get ())))
                {   assert (ancestral_farm.first -> mf_);
                    ancestral_farm.first -> mf_ -> set_mf_value (nits (), node_.version (), farm.second, p.get (), *prop_vocab_element);
                    if (context.mf_verify ())
                    {   ancestral_farm.first -> mf_ -> validate (nits (), node_.version (), node_.id ());
                        if (context.tell (e_detail))
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
            {   prop p (c);
                if (! p.invalid ())
                {   bool fraternal = false; // sibternal?!
                    found_farm farm = find_farm (p.get ()); // should store this result beforehand rather than search for it again
                    if (context.mf_version1 ())
                    {   if ((farm.second != c_error) && is_plausible_field (farm.second, p.get ())) continue;
                        for (auto bro : vc)
                            if (! bro.invalid ())
                            {   if (bro.is_microformat_vocabulary ()) continue;
                                if (bro.get () == c.get ()) continue;
                                prop sis (bro); // my family's weird!
                                if (! is_plausible_sibling (p.get (), sis.get ())) continue;
                                mf_ -> set_mf_value (nits (), node_.version (), c.get (), p.get (), *this);
                                if (context.mf_verify ())
                                    if (context.tell (e_detail))
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

void element::examine_css (const e_element tag)
{   if (context.load_css ())
        if ((tag == elem_link) && a_.good (a_rel))
            if (a_.get_string (a_rel) == R_STYLESHEET)
                if (a_.known (a_href) && a_.good (a_href))
                {   bool is_css = false;
                    if (a_.known (a_type))
                    {   if (a_.good (a_type))
                            is_css = (a_.get_string (a_type) == CSS_TYPE); }
                    else if (page_.style_css ()) is_css = true;
                    if (is_css)
                    {   ::std::string name (a_.get_string (a_href));
                        vurl_t v (a_.get_urls (a_href));
                        for (auto u : v)
                            if (! u.invalid ())
                            {   pick (nit_gather, es_comment, ec_css, "gathering CSS identifiers from ", u.original ());
                                context.css ().parse_file (nits (), page_, u); } } } }

void element::examine_content ()
{   if (tag () == elem_meta) return;
    if (context.rdf () || (node_.version().svg_version () == sv_1_2_tiny) || (node_.version().svg_version () == sv_1_2_full)) return;
    switch (node_.version ().major ())
    {   case 0 :
        case 1 :
        case 2 :
        case 3 :    return;
        case 4 :    if (node_.version ().minor () == 4) return;
                    break;
        default : break; }
    pick (nit_svg_rdf, es_info, ec_attribute, "CONTENT requires <META>, RDFa, SVG 1.2, or XHTML 2.0"); }

void element::examine_draggable ()
{   if (node_.version ().major () < 5) return;
    assert (a_.has (a_draggable) && a_.known (a_draggable));
    if (! a_.known (a_title))
        pick (nit_title_required, ed_51, "5.7.7. The draggable attribute", es_warning, ec_attribute, "An element with DRAGGABLE should also define TITLE"); }

void element::examine_headers ()
{   if (! a_.known (a_headers)) return;
    if (node_.version ().major () < 5) return;
    uid_t tuid_first, tuid_last;
    if (! family_uids (elem_table, tuid_first, tuid_last))
        pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "HEADERS must be on a descendant of <TABLE>");
    else
    {   vstr_t ids = a_.get_x < attr_headers > ();
        for (auto s : ids)
            if (ids_.has_id (s))
                if (ids_.get_tag (s) != elem_th)
                    pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "id ", quote (s), " is not on a <TH>");
                else
                {   uid_t uid = ids_.get_uid (s);
                    if ((uid < tuid_first) || (uid > tuid_last))
                        pick (nit_bad_header_id, ed_50, "4.9.11 Attributes common to td and th elements", es_error, ec_attribute, "id ", quote (s), " is on a <TH> in a different <TABLE>"); } } }

void element::examine_descendant_in (const element* filter)
{   assert (filter != nullptr);
    if (a_.known (a_in))
    {   ::std::string s (a_.get_string (a_in));
        nitpick nuts;
        if (! test_value < t_inky > (nuts, node_.version (), s))
            if (! filter -> has_result (a_.get_string (a_in)))
            {   node_.merge (nuts);
                pick (nit_bad_result, ed_svg_1_1, "15.7.2 Common attributes", es_error, ec_attribute, quote (a_.get_string (a_in)), " is neither a filter primitive nor a result associated with the current filter"); } }
    if (has_child ())
    {   element_ptr e = child ();
        do
        {   e -> examine_descendant_in (filter); }
        while (to_sibling (e)); } }

bool element::examine_rel (const ::std::string& content)
{   if (! context.microformats ()) return true;
    if (content.empty ()) return false;
    vstr_t entries, ve;
    bool res = false;
    rel vr;
    prop vp;
    ::boost::algorithm::split (entries, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
    ve.reserve (entries.size ());
    for (auto x : entries)
    {   rel r (nits (), node_.version (), x);
        if (r.unknown ())
            pick (nit_unrecognised_rel, es_warning, ec_attribute, "unknown REL type ", quote (x), " encountered");
        else if (r.is_microformat_property ())
        {   activate_microformats ();
            if (mf_ -> is_declared (r.get ()))
            {   if (context.mf_verify ()) pick (nit_duplicate_rel, es_warning, ec_attribute, "ignoring duplicate ", quote (r.name ())); }
            else
            {   mf_ -> declare (r.get ());
                mf_ -> validate (nits (), node_.version (), node_.id ());
                if (context.mf_verify ())
                    if (context.tell (e_variable)) pick (nit_rel_found, es_comment, ec_attribute, "REL type ", quote (r.name ()), " (", r.get (), ") found");
                    else pick (nit_rel_found, es_comment, ec_attribute, "REL type ", quote (r.name ()), " found");
                prop p (r);
                if (! p.invalid ())
                {   mf_ -> set_mf_value (nits (), node_.version (), r.get (), p.get (), *this);
                    if (ve.empty ()) { vr = r; vp = p; }
                    ve.push_back (x); }
                res = true; } } }
    return res; }