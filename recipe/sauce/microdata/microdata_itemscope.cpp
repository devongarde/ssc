/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "microdata/microdata_itemscope.h"
#include "microdata/microdata_itemtype.h"
#include "schema/schema_property.h"
#include "microformat/prop.h"
#include "main/context.h"
#include "utility/quote.h"
#include "webpage/page.h"

typedef enum { ip_itemscope, ip_string } itemprop_member;

void microdata_itemscope::swap (microdata_itemscope& mi)
{   itemprop_.swap (mi.itemprop_);
    type_.swap (mi.type_);
    ::std::swap (export_, mi.export_); }

void microdata_itemscope::note_itemtype (nitpick& nits, const html_version& v, const ::std::string& name, page& p)
{   nitpick nuts;
    itemtype_index ii = find_itemtype_index (nuts, v, name);
    if (ii != invalid_itemtype)
    {   type_.push_back (ii);
        type_master < t_schema > ts;
        ts.set_value (nits, v, name);
        switch (type_master < t_microdata_domain > :: starts_with (name))
        {   case mdd_microformats :
            {   type_master < t_class > c;
                c.set_value (nits, v, type_master < t_microdata_domain > :: after_start (name));
                if (context.md_export ())
                    for (auto cc : c.get ())
                        export_ -> add (export_path_, make_itemtype_index (cc)); }
                break;
            case mdd_schema :
            {   sch s (nits, v, type_master < t_microdata_domain > :: after_start (name));
                p.mark (s.get ());
                if (context.md_export ())
                    export_ -> add (export_path_, make_itemtype_index (s.get ())); }
                break;
            // purl, whatwg, etc.. ; this needs generalising
            default :
                break; } } }

bool microdata_itemscope::note_itemid (nitpick& , const html_version& , const ::std::string& name)
{   if (context.md_export () && ! name.empty ())
        export_ -> add (export_path_, name);
    return true; }

bool microdata_itemscope::note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, const bool is_link, page& p)
{   itemprop_index prop = find_itemprop_index (nits, v, name, type_.empty ());
    if (prop == illegal_itemprop)
    {   switch (type_master < t_microdata_domain > :: starts_with (value))
        {   case mdd_none :     return false;
            case mdd_schema :   break;
            default :           nits.pick (nit_bad_itemprop, es_error, ec_microdata, "expecting schema.org");
                                return false; }
        if (value.at (4) == 's') prop = find_itemprop_index (nits, v, name.substr (HTTPS_SCHEMA_ORG), type_.empty ());
        else prop = find_itemprop_index (nits, v, name.substr (HTTP_SCHEMA_ORG), type_.empty ()); }
    if (prop != illegal_itemprop)
    {   nitpick knots;
        for (auto i : type_)
            if (are_categories_compatible (knots, v, prop, i))
            {   nitpick nuts;
                if (is_valid_property (nuts, v, i, prop, value, is_link))
                {   nits.merge (nuts);
                    itemprop_.emplace (prop, itemprop_value (value));
                    if (context.md_export ()) export_ -> add (export_path_, prop, value);
                    p.mark (static_cast < e_schema > (i & uint32_item_mask), static_cast < e_schema_property > (prop & uint32_item_mask));
                    return true; }
                knots.merge (nuts); }
        nits.merge (knots); }
    return false; }

bool microdata_itemscope::note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, itemscope_ptr& value, page& p)
{   itemprop_index prop = find_itemprop_index (nits, v, name, type_.empty ());
    if (value.get () != nullptr) value -> set_exporter (export_, export_ -> append_path (export_path_, prop, true));
    if (prop != illegal_itemprop)
    {   nitpick knots;
        for (auto parent : type_)
            if (are_categories_compatible (knots, v, parent, prop))
                for (auto child : value -> type_)
                    if (are_compatible_types (knots, v, parent, child))
                    {   nitpick nuts;
                        if (is_valid_property (nuts, v, parent, prop, child))
                        {   nits.merge (nuts);
                            itemprop_.emplace (prop, value);
                            p.mark (static_cast < e_schema > (parent & uint32_item_mask), static_cast < e_schema_property > (prop & uint32_item_mask));
                            return true; }
                        knots.merge (nuts); }
        nits.merge (knots); }
    return false; }

::std::string microdata_itemscope::report (const ::std::size_t offset) const
{   ::std::string res, indent (offset*2, ' ');
    for (mpv_t::const_iterator i = itemprop_.cbegin (); i != itemprop_.cend (); ++i)
#ifndef BOOVAR
        if (! i -> second.valueless_by_exception ())
#endif // BOOVAR
#if BOOVAR == 1
// I can't honest be arsed to work my around around ::boost::variants' restrictions, and in particular VS2015's (presuming) bizarre
// belief that code that contains no consts suffers from too many consts
            ;
#else
            switch (i -> second.index ())
            {   case ip_itemscope :
                    assert (ssc_get < itemscope_ptr > (i -> second).get () != nullptr);
                    res += indent + itemprop_index_name (i -> first) + ":\n";
                    res += ssc_get < itemscope_ptr > (i -> second) -> report (offset+1);
                    break;
                case ip_string :
                    res += indent + itemprop_index_name (i -> first) + " = " + quote (ssc_get < ::std::string > (i -> second)) + "\n";
                    break; }
#endif // BOOVAR
    return res; }

bool microdata_itemscope::write (nitpick& nits, const ::boost::filesystem::path& name)
{   return export_ -> write (nits, name); }

vit_t microdata_itemscope::sought_itemtypes (const html_version& v, const ::std::string& name) const
{   nitpick nits;
    vit_t res;
    itemprop_index prop = find_itemprop_index (nits, v, name, type_.empty ());
    if (prop != illegal_itemprop)
        if (prop_category (prop) == itemprop_schema)
            for (auto i : sought_schema_itemtypes (static_cast < e_schema_property > (prop & uint32_item_mask)))
                res.push_back (i);
    return res; }


bool are_categories_compatible (const e_itemprop_category ipc, const e_itemtype_category itc)
{   switch (itc)
    {   case itemtype_none : return (ipc == itemprop_bespoke);
        case itemtype_schema : return (ipc == itemprop_schema);
        default : return (ipc == itemprop_microformat); } }

bool are_categories_compatible (nitpick& nits, const html_version& , const itemprop_index ipi, const itemtype_index iti)
{   if (are_categories_compatible (prop_category (ipi), type_category (iti))) return true;
    if (prop_category (ipi) == itemprop_bespoke) nits.pick (nit_incompatible_itemtype, es_error, ec_microdata, "ITEMTYPE rejects bespoke ITEMPROPs");
    else nits.pick (nit_incompatible_itemtype, es_info, ec_microdata, "ITEMTYPE and ITEMPROP belong to different microdata categories");
    return false; }

bool are_compatible_types (nitpick& nits, const html_version& , const itemtype_index lhs, const itemtype_index rhs)
{   if (type_category (lhs) == type_category (rhs)) return true;
    nits.pick (nit_incompatible_itemtype, es_info, ec_microdata, "ITEMTYPEs belong to different microdata categories");
    return false; }
