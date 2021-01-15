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
#include "microdata/microdata_itemprop.h"
#include "schema/schema_property.h"
#include "microformat/prop.h"

typedef ssc_map < ::std::string, itemprop_index > min_t;
typedef ssc_map < itemprop_index, ::std::string > mii_t;

itemprop_index bespoke_itemprop = 0;

min_t unknown_props;
mii_t unknown_ids;

itemprop_index make_itemprop_index (const e_schema_property p)
{   assert (p <= sp_illegal);
    return static_cast < itemprop_index> (p) + (static_cast < itemprop_index > (itemprop_schema) << uint32_category_shift); }

itemprop_index make_itemprop_index (const e_property p)
{   assert (p <= first_illegal);
    return static_cast < itemprop_index> (p) + (static_cast < itemprop_index > (itemprop_microformat) << uint32_category_shift); }

e_itemprop_category prop_category (const itemprop_index ii)
{   return static_cast < e_itemprop_category> (static_cast < uint32_t > (ii) >> uint32_category_shift); }

::std::string bespoke_itemprop_name (const itemprop_index ii)
{   mii_t::const_iterator i = unknown_ids.find (ii & uint32_item_mask);
    if (i != unknown_ids.cend ()) return i -> second;
    return ::std::string (); }

itemprop_index find_itemprop_index (nitpick& nits, const html_version& v, const ::std::string& name, bool bespoke_permitted)
{   nitpick knots;
    e_schema_property mp = identify_schema_property (knots, context.schema_ver (), name);
    if (mp != sp_illegal) return make_itemprop_index (mp);
    prop p (knots, v, name);
    if (! p.unknown () && ! p.invalid ()) return make_itemprop_index (p.get ());
    if (! bespoke_permitted)
    {   nits.merge (knots);
        nits.pick (nit_bad_itemprop, es_error, ec_microdata, quote (name), " is not recognised");
        return illegal_itemprop; }
    min_t::const_iterator ini = unknown_props.find (name);
    if (ini != unknown_props.cend ()) return ini -> second;
    unknown_props.emplace (name, ++bespoke_itemprop);
    unknown_ids.emplace (bespoke_itemprop, name);
    nits.pick (nit_new_itemprop, es_comment, ec_microdata, "new untyped itemprop ", quote (name), " noted");
    return bespoke_itemprop; }

::std::string itemprop_index_name (const itemprop_index ndx)
{   if (ndx != illegal_itemprop)
        switch (ndx >> uint32_category_shift)
        {   case itemprop_bespoke :
                return bespoke_itemprop_name (ndx);
            case itemprop_schema :
                return schema_property_name (static_cast < e_schema_property > (ndx & uint32_item_mask));
            case itemprop_microformat :
                return prop::name (static_cast < e_property > (ndx & uint32_item_mask));
            default : break; }
    return "illegal"; }

bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const ::std::string& value, const bool is_link)
{   switch (ndx >> uint32_category_shift)
    {   case itemprop_bespoke :
            return true;
        case itemprop_schema :
            return is_valid_schema_property (nits, v, static_cast < e_schema> (itemtype & uint32_item_mask), static_cast < e_schema_property > (ndx & uint32_item_mask), value, is_link);
        case itemprop_microformat :
            return true;
        default : assert (false); break; }
    return false; }

bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const itemtype_index value)
{   switch (ndx >> uint32_category_shift)
    {   case itemprop_bespoke :
            return true;
        case itemprop_schema :
            return is_valid_schema_property (nits, v, static_cast < e_schema> (itemtype & uint32_item_mask), static_cast < e_schema_property > (ndx & uint32_item_mask), static_cast < e_schema> (value & uint32_item_mask));
        case itemprop_microformat :
            return true;
        default : assert (false); break; }
    return false; }
