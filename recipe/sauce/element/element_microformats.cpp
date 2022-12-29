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
#include "attribute/attribute_classes.h"

template < class PROPERTY > void mf_postprocess_entry (const microformats_ptr& mf, e_wm_status& wms, ::std::string& mention)
{   if (wms < wm_addr)
        if (! is_microformat_property_empty < mf_entry, PROPERTY > (mf))
        {   mention = get_microformat_property_value < mf_entry, PROPERTY > (mf);
            wms = wm_addr; } }

found_farm element::find_farm (const e_property p, element* starter)
{   if (! is_top ())
        for (element* ancestor = (starter == nullptr) ? this : starter; (ancestor != nullptr) && ! ancestor -> is_top (); ancestor = ancestor -> parent ())
            if (ancestor -> mf_)
            {   VERIFY_NOT_NULL (ancestor -> mf_, __FILE__, __LINE__);
                e_class v = ancestor -> mf_ -> plausible_vocabulary (p);
                if (v != c_error) return found_farm (ancestor, v);
                if (ancestor -> is_top ()) break; }
    return found_farm (nullptr, c_error); }

void element::mf_put_vocab (const e_class v, const prop& p, const ::std::string& itemtype, const ::std::string& itemprop)
{   PRESUME (! p.invalid (), __FILE__, __LINE__);
    if (context.mf_export ())
    {   VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
        ::std::string val (mf_ -> get_string (v, p.get ()));
        if (! val.empty ())
        {   const ::std::string vs (html_class::name (v));
            if (context.tell (es_debug)) pick (nit_debug, es_debug, ec_element, "putting ", quote (vs), " in json at ", itemtype);
            page_ -> export_item (itemtype, vs);
            ::std::string naam (itemprop);
            naam += EXPORT_SEP;
            naam += p.name ();
            if (context.tell (es_debug)) pick (nit_debug, es_debug, ec_element, "putting ", quote (val), " in json at ", naam);
            page_ -> export_item (naam, val); } } }

void element::mf_put_rel (const e_class v, const prop& p, const vstr_t& rels)
{   PRESUME (! p.invalid (), __FILE__, __LINE__);
    if (context.mf_export ())
    {   VERIFY_NOT_NULL (mf_, __FILE__, __LINE__);
        ::std::string val (mf_ -> get_string (v, p.get ()));
        if (! val.empty ())
        {   ::std::string hreflang, media, t (text ()), title, type;
            PRESUME (! rels.empty (), __FILE__, __LINE__);
            if (a_.has (a_hreflang)) hreflang = a_.get_string (a_hreflang);
            if (a_.has (a_media)) media = a_.get_string (a_media);
            if (a_.has (a_title)) title = a_.get_string (a_title);
            if (a_.has (a_type)) type = a_.get_string (a_type);
            page_ -> export_rel (val, hreflang, media, rels, t, title, type);
            if (context.tell (es_debug))
                pick (nit_debug, es_debug, ec_element,
                    "export_rel ", quote (val), ", ", hreflang, ", ", media, ", ",
                    quote (rels), ", ", quote (t), ", ", quote (title), ", ", type); } } }

::std::string element::find_date_value () const
{   if (a_.known (a_value) && a_.valid (a_value) && a_.valid (a_class))
        return a_.get_string (a_value);
    switch (tag ())
    {   case elem_t :
        case elem_time :
        case elem_ins :
        case elem_del :
            if (a_.known (a_datetime)) return a_.get_string (a_datetime);
            break;
        case elem_abbr :
            if (a_.known (a_title)) return a_.get_string (a_title);
            break;
        case elem_data :
        case elem_input :
            if (a_.known (a_value)) return a_.get_string (a_value);
            break;
        default : break; }
    return text (); }

::std::string element::find_text_value () const
{   if (a_.known (a_value) && a_.valid (a_class))
        return a_.get_string (a_value);
    switch (tag ())
    {   case elem_abbr :
        case elem_link :
            if (a_.known (a_title)) return a_.get_string (a_title);
            break;
        case elem_data :
        case elem_input :
            if (a_.known (a_value)) return a_.get_string (a_value);
            break;
        case elem_img :
        case elem_area :
            if (a_.known (a_alt)) return a_.get_string (a_alt);
            break;
        default : break; }
    return text (); }

::std::string element::find_url_value () const
{   switch (tag ())
    {   case elem_a :
        case elem_area :
        case elem_link :
            if (a_.known (a_href) && ! a_.invalid (a_href)) return a_.get_string (a_href);
            break;
        case elem_audio :
        case elem_source :
        case elem_iframe :
        case elem_img :
            if (a_.known (a_src)) return a_.get_string (a_src);
            break;
        case elem_video :
            if (a_.known (a_src)) return a_.get_string (a_src);
            if (a_.known (a_poster)) return a_.get_string (a_poster);
            break;
        case elem_object :
            if (a_.known (a_data)) return a_.get_string (a_data);
            break;
        default : break; }
    if (a_.known (a_value) && a_.valid (a_class))
        return a_.get_string (a_value);
    switch (tag ())
    {   case elem_abbr :
            if (a_.known (a_title)) return a_.get_string (a_title);
            break;
        case elem_data :
        case elem_input :
            if (a_.known (a_value)) return a_.get_string (a_value);
            break;
        default : break; }
    return text (); }

::std::string element::find_html_value () const
{   return text (); }
