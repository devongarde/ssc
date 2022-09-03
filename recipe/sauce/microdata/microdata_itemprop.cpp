/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
typedef ::std::unique_ptr < min_t > min_uptr;
typedef ::std::unique_ptr < mii_t > mii_uptr;

itemprop_index bespoke_itemprop = 0;

min_uptr unknown_props;
mii_uptr unknown_ids;

void init_itemprop ()
{   unknown_props = min_uptr (new min_t); 
    unknown_ids = mii_uptr (new mii_t); }

itemprop_index make_itemprop_index (const e_schema_property p)
{   PRESUME (p <= sp_illegal, __FILE__, __LINE__);
    return static_cast < itemprop_index> (p) + (static_cast < itemprop_index > (itemprop_schema) << uint32_category_shift); }

itemprop_indices make_itemprop_indices (const e_schema_property p)
{   PRESUME (p <= sp_illegal, __FILE__, __LINE__);
    itemprop_indices res;
    res.emplace_back (make_itemprop_index (p));
    return res; }

itemprop_indices make_itemprop_indices (const vsp_t& vsp)
{   itemprop_indices res;
    for (auto p : vsp) res.emplace_back (make_itemprop_index (p));
    return res; }

itemprop_index make_itemprop_index (const e_property p)
{   PRESUME (p <= first_illegal, __FILE__, __LINE__);
    return GSL_NARROW_CAST < itemprop_index> (p) + (static_cast < itemprop_index > (itemprop_microformat) << uint32_category_shift); }

itemprop_indices make_itemprop_indices (const e_property p)
{   PRESUME (p <= sp_illegal, __FILE__, __LINE__);
    itemprop_indices res;
    res.emplace_back (make_itemprop_index (p));
    return res; }

::std::string bespoke_itemprop_name (const itemprop_index ii)
{   VERIFY_NOT_NULL (unknown_ids.get (), __FILE__, __LINE__);
    mii_t::const_iterator i = unknown_ids -> find (ndx_item (ii));
    if (i != unknown_ids -> cend ()) return i -> second;
    return ::std::string (); }

itemprop_index find_itemprop_index (nitpick& nits, const html_version& v, const ::std::string& name, bool bespoke_permitted)
{   nitpick knots;
    const e_schema_property mp = identify_schema_property (name);
    if (mp != sp_illegal) return make_itemprop_index (mp);
    knots.pick (nit_not_schema_property, es_error, ec_schema, quote (name), " is not a recognised property");
    const prop p (knots, v, name);
    if (! p.unknown () && ! p.invalid ()) return make_itemprop_index (p.get ());
    if (! bespoke_permitted)
    {   nits.merge (knots);
        check_identifier_spelling (nits, v, name);
        nits.pick (nit_bad_itemprop, es_error, ec_microdata, quote (name), " is not recognised");
        return illegal_itemprop; }
    lox l (lox_itemprop);
    VERIFY_NOT_NULL (unknown_props.get (), __FILE__, __LINE__);
    VERIFY_NOT_NULL (unknown_ids.get (), __FILE__, __LINE__);
    min_t::const_iterator ini = unknown_props -> find (name);
    if (ini != unknown_props -> cend ()) return ini -> second;
    unknown_props -> emplace (name, ++bespoke_itemprop);
    unknown_ids -> emplace (bespoke_itemprop, name);
    nits.pick (nit_new_itemprop, es_comment, ec_microdata, "new untyped itemprop ", quote (name), " noted");
    return bespoke_itemprop; }

itemprop_indices find_itemprop_indices (nitpick& nits, const html_version& v, const ::std::string& name, bool bespoke_permitted)
{   nitpick knots;
    vsp_t vsp = identify_schema_properties (name);
    if (! vsp.empty ()) return make_itemprop_indices (vsp);
    knots.pick (nit_not_schema_property, es_error, ec_schema, quote (name), " is not a recognised property");
    const prop p (knots, v, name);
    if (! p.unknown () && ! p.invalid ()) return make_itemprop_indices (p.get ());
    if (! bespoke_permitted)
    {   nits.merge (knots);
        check_identifier_spelling (nits, v, name);
        nits.pick (nit_bad_itemprop, es_error, ec_microdata, quote (name), " is not recognised");
        return itemprop_indices (); }
    lox l (lox_itemprop);
    VERIFY_NOT_NULL (unknown_props.get (), __FILE__, __LINE__);
    VERIFY_NOT_NULL (unknown_ids.get (), __FILE__, __LINE__);
    min_t::const_iterator ini = unknown_props -> find (name);
    if (ini != unknown_props -> cend ()) return make_itemprop_indices (ini -> second);
    unknown_props -> emplace (name, ++bespoke_itemprop);
    unknown_ids -> emplace (bespoke_itemprop, name);
    nits.pick (nit_new_itemprop, es_comment, ec_microdata, "new untyped itemprop ", quote (name), " noted");
    return make_itemprop_indices (bespoke_itemprop); }

::std::string itemprop_index_name (const itemprop_index ndx)
{   if (ndx != illegal_itemprop)
        switch (ndx >> uint32_category_shift)
        {   case itemprop_bespoke :
                return bespoke_itemprop_name (ndx);
            case itemprop_schema :
                return schema_property_name (static_cast < e_schema_property > (ndx_item (ndx)));
            case itemprop_microformat :
                return prop::name (GSL_NARROW_CAST < e_property > (ndx_item (ndx)));
            default : break; }
    return "illegal"; }

bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const ::std::string& value, const bool is_link)
{   switch (ndx >> uint32_category_shift)
    {   case itemprop_bespoke :
            return true;
        case itemprop_schema :
            return is_valid_schema_property (nits, v, static_cast < e_schema_type> (ndx_item (itemtype)), static_cast < e_schema_property > (ndx_item (ndx)), value, is_link);
        case itemprop_microformat :
            return true;
        default :
            break; }
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }

bool is_valid_property (nitpick& nits, const html_version& v, const itemtype_index itemtype, const itemprop_index ndx, const itemtype_index value)
{   switch (ndx >> uint32_category_shift)
    {   case itemprop_bespoke :
            return true;
        case itemprop_schema :
            return is_valid_schema_property (nits, v, static_cast < e_schema_type> (ndx_item (itemtype)), static_cast < e_schema_property > (ndx_item (ndx)), static_cast < e_schema_type> (ndx_item (value)));
        case itemprop_microformat :
            return true;
        default :
            break; }
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }
