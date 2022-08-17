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
#include "webpage/page.h"
#include "element/element.h"
#include "attribute/attribute_classes.h"

void element::verify_microdata ()
{   const bool has_itemid = a_.known (a_itemid);
    const bool has_itemref = a_.known (a_itemref);
    const bool has_itemtype = a_.known (a_itemtype);
    const bool has_itemscope = a_.known (a_itemscope);
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
{   switch (tag ())
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
        case elem_t :
        case elem_time :
            return a_.get_string (a_datetime);
        default :
            return node_.text (); } }

itemscope_ptr element::examine_itemscope (itemscope_ptr& itemscope, const bool pagify)
{   VERIFY_NOT_NULL (page_ -> md_export (), __FILE__, __LINE__);
    itemscope_ptr new_scope (new microdata_itemscope ());
    VERIFY_NOT_NULL (new_scope.get (), __FILE__, __LINE__);
    if (itemscope.get () == nullptr)
        new_scope -> set_exporter (page_ -> md_export (), page_ -> md_export () -> append_path (page_ -> get_export_root (), null_itemprop, true));
    else                                                                                                                                      
    {   bool se = false;
        if (! a_.known (a_itemtype)) new_scope -> parent (itemscope);
        new_scope -> parent2 (itemscope);
        ::std::string value (get_microdata_value ());
        if (a_.known (a_itemprop))
            for (auto name : a_.get_x < attr_itemprop > ())
            {   se = true;
                itemscope -> note_itemprop (node_.nits (), node_.version (), name, value, new_scope, *page_); }
        if (! se) new_scope -> set_exporter (page_ -> md_export (), page_ -> md_export () -> append_path (itemscope -> export_path (), null_itemprop, true)); }
    itemscope = new_scope;
    if (pagify)
        if (page_ -> itemscope ().get () == nullptr)
            page_ -> itemscope (itemscope);
    if (a_.known (a_itemid))
        itemscope -> note_itemid (node_.nits (), node_.version (), a_.get_string (a_itemid));
    return itemscope; }

void element::examine_itemprop (itemscope_ptr& itemscope)
{    if (! ancestral_elements_.test (elem_template))
        if (itemscope.get () == nullptr)
        {   if (node_.version ().mjr () >= 10)
                if (ancestral_attributes_.test (a_id)) // an ancestral id suggests an itemref
                    pick (nit_no_itemscope, ed_jul20, "5.2.2 Items", es_comment, ec_microdata, "if the ancestral ID is not referenced by an ITEMREF elsewhere, then ITEMPROP requires ITEMSCOPE on the current or an ancestral element");
                else pick (nit_no_itemscope, ed_jul20, "5.2.2 Items", es_warning, ec_microdata, "ITEMPROP requires ITEMSCOPE on the current or an ancestral element"); }
        else
        {   ::std::string value (get_microdata_value ());
            const bool is_link = (tag () == elem_a) || (tag () == elem_link) || (tag () == elem_area);
            const bool mummy_expected = (a_.known (a_itemscope) || a_.known (a_itemtype));
            const bool check_mummy = mummy_expected && itemscope -> has_parent2 ();
            for (auto name : a_.get_x < attr_itemprop > ())
                if (! mummy_expected) itemscope -> note_itemprop (node_.nits (), node_.version (), name, value, is_link, *page_);
                else if (check_mummy) itemscope -> parent2 ().lock () -> note_itemprop (node_.nits (), node_.version (), name, value, itemscope, *page_);
                else if (ancestral_attributes_.test (a_id))
                    if (ancestral_attributes_.test (a_itemscope)) pick (nit_missing_itemtype, ed_jul20, "5.2.2 Items", es_info, ec_schema, "if the ancestral ID is not referenced by an ITEMREF elsewhere, then, although valid with an ITEMSCOPE, ", quote (name), " may require an ancestral ITEMTYPE");
                    else pick (nit_missing_itemtype, ed_jul20, "5.2.2 Items", es_info, ec_schema, "if the ancestral ID is not referenced by an ITEMREF elsewhere, then, although valid with an ITEMSCOPE, ", quote (name), " may require an ancestral ITEMTYPE or ITEMSCOPE");
                else if (ancestral_attributes_.test (a_itemscope)) pick (nit_missing_itemtype, ed_jul20, "5.2.2 Items", es_warning, ec_schema, "although valid with an ITEMSCOPE, ", quote (name), " may require an ancestral ITEMTYPE");
                    else pick (nit_missing_itemtype, ed_jul20, "5.2.2 Items", es_warning, ec_schema, "although valid with an ITEMSCOPE, ", quote (name), " may require an ancestral ITEMTYPE or ITEMSCOPE"); } }

void element::examine_itemref (const itemscope_ptr& itemscope)
{   if (icarus_) pick (nit_icarus, es_warning, ec_attribute, "Oh Momus, oh Icarus, why do you torment me so (with ITEMREF recursion)?");
    else if (itemscope.get () != nullptr)
        if (a_.known (a_itemscope) && a_.known (a_itemtype) && a_.known (a_itemref))
            for (auto name : a_.get_x < attr_itemref > ())
                if (get_ids ().has_id (name))
                {   element* ire = get_ids ().get_element (name);
                    if (ire != nullptr)
                    {   icarus_ = true;
                        ire -> walk_itemprop (itemscope);
                        icarus_ = false; } } }

void element::examine_itemtype (const itemscope_ptr& itemscope)
{   const bool has_itemid = a_.known (a_itemid);
    if (a_.known (a_itemscope))
    {   VERIFY_NOT_NULL (itemscope, __FILE__, __LINE__);
        for (auto name : a_.get_x < attr_itemtype > ())
            itemscope -> note_itemtype (node_.nits (), node_.version (), name, *page_, has_itemid); } }

vit_t element::own_itemtype () const
{   if (! a_.good (a_itemtype)) return vit_t ();
    if (itemscope_.get () == nullptr) return vit_t ();
    return itemscope_ -> type (); }

void element::walk_itemprop (itemscope_ptr itemscope)
{   {   reverter < itemscope_ptr > r (itemscope_);
        if (a_.known (a_itemscope)) examine_itemscope (itemscope, false);
        if (a_.known (a_itemtype)) examine_itemtype (itemscope);
        if (a_.known (a_itemprop)) examine_itemprop (itemscope);
        if (a_.known (a_itemref)) examine_itemref (itemscope); }
    for (element* p = child_; p != nullptr; p = p -> sibling_)
        p -> walk_itemprop (itemscope); }

vit_t element::supplied_itemtypes ()
{   return own_itemtype (); }

vit_t element::sought_itemtypes ()
{   vit_t res;
    VERIFY_NOT_NULL (itemscope_, __FILE__, __LINE__);
    if (a_.known (a_itemprop))
        for (auto name : a_.get_x < attr_itemprop > ())
            for (auto i : itemscope_ -> sought_itemtypes (node_.version (), name))
                res.push_back (i);
    return res; }
