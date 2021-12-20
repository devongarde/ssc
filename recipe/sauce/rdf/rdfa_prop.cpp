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
#include "main/context.h"
#include "rdf/rdfa_prop.h"
#include "schema/schema_property.h"

typedef ssc_map < ::std::string, prop_index > mpn_t;
typedef ssc_map < prop_index, ::std::string > mpi_t;

prop_index bespoke_prop = static_cast < prop_index > (sp_illegal);

mpn_t bespoke_props;
mpi_t bespoke_ids;

prop_indices make_prop_indices (const prop_index p)
{   prop_indices res;
    res.emplace_back (p);
    return res; }

prop_indices make_prop_indices (const e_schema_property p)
{   PRESUME (p <= sp_illegal, __FILE__, __LINE__);
    prop_indices res;
    res.emplace_back (make_prop_index (p));
    return res; }

prop_indices make_prop_indices (const vsp_t& vsp)
{   prop_indices res;
    for (auto p : vsp) res.emplace_back (make_prop_index (p));
    return res; }

::std::string bespoke_prop_name (const prop_index ii)
{   mpi_t::const_iterator i = bespoke_ids.find (ndx_item (ii));
    if (i != bespoke_ids.cend ()) return i -> second;
    return ::std::string (); }

prop_index find_prop_index (nitpick& nits, const html_version& , const ::std::string& name, bool bespoke_permitted)
{   nitpick knots;
    const e_schema_property mp = identify_schema_property (knots, context.schema_ver (), name);
    if (mp != sp_illegal) return make_prop_index (mp);
    if (! bespoke_permitted)
    {   nits.merge (knots);
        nits.pick (nit_bad_property, es_error, ec_rdfa, quote (name), " is not recognised");
        return illegal_prop; }
    mpn_t::const_iterator ini = bespoke_props.find (name);
    if (ini != bespoke_props.cend ()) return ini -> second;
    bespoke_props.emplace (name, ++bespoke_prop);
    bespoke_ids.emplace (bespoke_prop, name);
    nits.pick (nit_new_property, es_comment, ec_rdfa, "new untyped property ", quote (name), " noted");
    return bespoke_prop; }

prop_indices find_prop_indices (nitpick& nits, const html_version& , const ::std::string& name, bool bespoke_permitted)
{   nitpick knots;
    vsp_t vsp = identify_schema_properties (knots, context.schema_ver (), name);
    if (! vsp.empty ()) return make_prop_indices (vsp);
    if (! bespoke_permitted)
    {   nits.merge (knots);
        nits.pick (nit_bad_property, es_error, ec_rdfa, quote (name), " is not recognised");
        return prop_indices (); }
    mpn_t::const_iterator ini = bespoke_props.find (name);
    if (ini != bespoke_props.cend ()) return make_prop_indices (ini -> second);
    bespoke_props.emplace (name, ++bespoke_prop);
    bespoke_ids.emplace (bespoke_prop, name);
    nits.pick (nit_new_property, es_comment, ec_rdfa, "new untyped property ", quote (name), " noted");
    return make_prop_indices (bespoke_prop); }

::std::string prop_index_name (const prop_index ndx)
{   if (ndx < sp_illegal)
        return schema_property_name (static_cast < e_schema_property > (ndx));
    if (ndx > sp_illegal)
        return bespoke_prop_name (ndx);
    return "(illegal)"; }

bool is_valid_prop (nitpick& nits, const html_version& v, const type_index t, const prop_index ndx, const ::std::string& value, const bool is_link)
{   if (ndx < sp_illegal)
        return is_valid_schema_property (nits, v, static_cast < e_schema_type> (t), static_cast < e_schema_property > (ndx), value, is_link);
    if (ndx > sp_illegal) return true;
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }

bool is_valid_prop (nitpick& nits, const html_version& v, const type_index t, const prop_index ndx, const type_index value)
{   if (ndx < sp_illegal)
        return is_valid_schema_property (nits, v, static_cast < e_schema_type> (t), static_cast < e_schema_property > (ndx), static_cast < e_schema_type> (value));
    if (ndx > sp_illegal) return true;
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }
