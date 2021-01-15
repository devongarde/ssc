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
#include "webpage/page.h"
#include "element/element.h"
#include "attribute/attribute_classes.h"

void element::verify_microdata ()
{   bool has_itemid = a_.known (a_itemid);
    bool has_itemref = a_.known (a_itemref);
    bool has_itemtype = a_.known (a_itemtype);
    bool has_itemscope = a_.known (a_itemscope);
    if (has_itemtype)
        if (! has_itemscope)
            node_.pick (nit_requires_itemscope, ed_jul20, "5.2.2 Items", es_error, ec_attribute, "missing ITEMSCOPE; ITEMTYPE ignored");
    if (has_itemid)
        if (! has_itemscope || ! has_itemtype)
            node_.pick (nit_requires_itemscope, ed_jul20, "5.2.2 Items", es_error, ec_attribute, "ITEMID requires both ITEMSCOPE and ITEMTYPE");
    if (has_itemref)
        if (! has_itemscope)
            node_.pick (nit_requires_itemscope, ed_jul20, "5.2.2 Items", es_error, ec_attribute, "missing ITEMSCOPE; ITEMREF ignored"); }

::std::string element::get_microdata_value () const
{   // need to rethink template structures, since this should be templated based on the tag
    // (which *is* templated in html_element) :-(
    switch (tag ())
    {   case elem_a :
        case elem_area :
        case elem_link :
            return a_.get_string (a_href);
        case elem_audio :
        case elem_embed :
        case elem_iframe :
        case elem_img :
        case elem_source :
        case elem_track :
        case elem_video :
            return a_.get_string (a_src);
        case elem_data :
        case elem_meter :
            return a_.get_string (a_value);
        case elem_meta :
            return a_.get_string (a_content);
        case elem_object :
            return a_.get_string (a_data);
        case elem_time :
            return a_.get_string (a_datetime);
        default :
            return node_.text (); } }

itemscope_ptr element::examine_itemscope (itemscope_ptr& itemscope)
{   assert (page_.md_export () != nullptr);
    itemscope_ptr new_scope (new microdata_itemscope ());
    assert (new_scope.get () != nullptr);
    if (itemscope.get () == nullptr)
        new_scope -> set_exporter (page_.md_export (), page_.md_export () -> append_path (page_.get_export_root (), null_itemprop, true));
    else
    {   bool se = false;
        if (a_.known (a_itemprop))
            for (auto name : a_.get_x < attr_itemprop > ())
            {   se = true;
                itemscope -> note_itemprop (node_.nits (), node_.version (), name, new_scope, page_); }
        if (! se) new_scope -> set_exporter (page_.md_export (), page_.md_export () -> append_path (itemscope -> export_path (), null_itemprop, true)); }
    itemscope = new_scope;
    if (page_.itemscope ().get () == nullptr)
        page_.itemscope (itemscope);
    if (a_.known (a_itemid) && a_.known (a_itemid))
        itemscope -> note_itemid (node_.nits (), node_.version (), a_.get_string (a_itemid));
    return itemscope; }

void element::examine_itemprop (itemscope_ptr& itemscope)
{   if (itemscope.get () == nullptr)
        if (ancestral_attributes_.test (a_id)) // an ancestral id suggests an itemref
            pick (nit_no_itemscope, es_comment, ec_microdata, "if the ancestral ID is not referenced by an ITEMREF elsewhere, then ITEMPROP requires ITEMSCOPE on an ancestral element");
        else pick (nit_no_itemscope, es_warning, ec_microdata, "ITEMPROP requires ITEMSCOPE on an ancestral element");
    else
    if (! a_.known (a_itemscope) && ! a_.known (a_itemtype))
    {   ::std::string value (get_microdata_value ());
        bool is_link = (tag () == elem_a) || (tag () == elem_link) || (tag () == elem_area);
        for (auto name : a_.get_x < attr_itemprop > ())
            itemscope -> note_itemprop (node_.nits (), node_.version (), name, value, is_link, page_); } }

void element::examine_itemref (itemscope_ptr& itemscope)
{   if (icarus_ ) pick (nit_icarus, es_info, ec_attribute, "Oh Momus, oh Icarus, why do you torment me so?");
    else if (itemscope.get () != nullptr)
        if (a_.known (a_itemscope) && a_.known (a_itemtype) && a_.known (a_itemref))
            for (auto name : a_.get_x < attr_itemref > ())
                if (ids_.has_id (name))
                {   element* ire = ids_.get_element (name);
                    if (ire != nullptr)
                    {   icarus_ = true;
                        ire -> walk_itemprop (itemscope);
                        icarus_ = false; } } }

void element::examine_itemtype (itemscope_ptr& itemscope)
{   if (a_.known (a_itemscope))
        for (auto name : a_.get_x < attr_itemtype > ())
            itemscope -> note_itemtype (node_.nits (), node_.version (), name, page_); }

vit_t element::own_itemtype () const
{   if (! a_.good (a_itemtype)) return vit_t ();
    if (itemscope_.get () == nullptr) return vit_t ();
    return itemscope_ -> type (); }

void element::walk_itemprop (itemscope_ptr itemscope)
{   itemscope_ptr tmp = itemscope_;
    itemscope_ptr sub = itemscope;
    if (a_.known (a_itemscope)) sub = examine_itemscope (itemscope);
    if (a_.known (a_itemtype)) examine_itemtype (itemscope);
    if (a_.known (a_itemprop)) examine_itemprop (itemscope);
    if (a_.known (a_itemref)) examine_itemref (itemscope);
    itemscope_ = tmp;
    if (has_child ())
    {   element_ptr e = child ();
        do {
            assert (e != nullptr);
            e -> walk_itemprop (sub);
        } while (to_sibling (e)); } }

vit_t element::supplied_itemtypes ()
{   return own_itemtype (); }

vit_t element::sought_itemtypes ()
{   vit_t res;
    if (a_.known (a_itemprop))
        for (auto name : a_.get_x < attr_itemprop > ())
            for (auto i : itemscope_ -> sought_itemtypes (node_.version (), name))
                res.push_back (i);
    return res; }

