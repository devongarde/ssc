/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "ontology/ontology_property.h"
#include "microformat/prop.h"
#include "main/context.h"
#include "utility/quote.h"
#include "webpage/page.h"

typedef enum { ip_itemscope, ip_string } itemprop_member;

void microdata_itemscope::swap (microdata_itemscope& mi)
{   itemprop_.swap (mi.itemprop_);
    type_.swap (mi.type_);
    ::std::swap (export_, mi.export_);
    export_path_.swap (mi.export_path_);
    parent_.swap (mi.parent_);
    parent2_.swap (mi.parent2_); }

void microdata_itemscope::note_itemtype (nitpick& nits, const html_version& v, const ::std::string& name, page& p, const bool has_itemid)
{   nitpick nuts;
    const itemtype_index ii = find_itemtype_index (nuts, v, name);
    if (ii != invalid_itemtype)
    {   type_.push_back (ii);
        type_master < t_ontology > ts;
        ts.set_value (nits, v, name);
        ::std::string::size_type ends_at = 0;
        const e_ontology sc = ontology_names.starts_with (ONTOLOGY_CURIE, v.xhtml (), name, &ends_at);
        if (sc == s_error)
            world_wide_wombat_web (nits, v, name);
        else
        {   if ((ontology_names.flags (sc) & ONTOLOGY_CRAPSPEC) == ONTOLOGY_CRAPSPEC)
                nits.pick (nit_crap_spec, es_warning, ec_microdata, quote (ontology_names.get (sc, ONTOLOGY_NAME)), " is poorly specified: use an alternative");
            if ((ontology_names.flags (sc) & ONTOLOGY_PRISM) == ONTOLOGY_PRISM)
                nits.pick (nit_bad_namespace, es_warning, ec_namespace, quote (ontology_names.get (sc, ONTOLOGY_CURIE)), " is incorrect, despite its occasional use. Browse 'namespaces' at 'https://www.w3.org/submissions/2020/SUBM-prism-20200910/prism-basic.html' for gen.");
            else if ((ontology_names.flags (sc) & ONTOLOGY_CRAPNS) == ONTOLOGY_CRAPNS)
                nits.pick (nit_bad_namespace, es_warning, ec_microdata, quote (ontology_names.get (sc, ONTOLOGY_CURIE)), " is incorrect, despite its occasional use.");
            const sch s (nits, v, ontology_names.after_start (ONTOLOGY_CURIE, name.substr (ends_at), v.xhtml ()));
            p.mark (s.get ());
            const flags_t flags = sch :: flags (s.get ());
            if (has_itemid && ((flags & SF_NO_ITEMID) == SF_NO_ITEMID))
                nits.pick (nit_deprecated_ontology, ed_jan21, "5.3 Sample microdata vocabularies", es_info, ec_microdata, quote (name), " cannot have ITEMID");
            if ((flags & SF_DEPRECATED) == SF_DEPRECATED)
                nits.pick (nit_deprecated_ontology, es_info, ec_microdata, quote (name), " is deprecated");
            if (context.md_export ())
            {   VERIFY_NOT_NULL (export_, __FILE__, __LINE__);
                export_ -> add (export_path_, make_itemtype_index (s.get ())); } } } }

bool microdata_itemscope::note_itemid (nitpick& , const html_version& , const ::std::string& name)
{   if (context.md_export () && ! name.empty ())
    {   VERIFY_NOT_NULL (exporter (), __FILE__, __LINE__);
        exporter () -> add (export_path_, name); }
    return true; }

itemprop_indices microdata_itemscope::prepare_itemprop_indices (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value)
{   itemprop_indices ii = find_itemprop_indices (nits, v, name, type ().empty ());
    if (ii.empty ())
    {   e_ontology mr = s_none;
        ::std::string::size_type ends_at = 0;
        mr = ontology_names.starts_with (ONTOLOGY_CURIE, v.xhtml (), value, &ends_at);
        if (mr == s_error) return ii;
        ii = find_itemprop_indices (nits, v, name.substr (ends_at), type ().empty ()); }
    return ii; }

bool microdata_itemscope::note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, const bool is_link, page& p)
{   itemprop_indices ii = prepare_itemprop_indices (nits, v, name, value);
    nitpick knots, nuts;
    for (auto prop : ii)
        for (auto i : type ())
            if (are_categories_compatible (knots, v, prop, i))
            {   if (is_valid_property (nuts, v, i, prop, value, is_link))
                {   nits.merge (nuts);
                    itemprop_.emplace (prop, itemprop_value (value));
                    if (context.md_export ())
                    {   VERIFY_NOT_NULL (exporter (), __FILE__, __LINE__);
                        exporter () -> add (export_path_, prop, value); }
                    p.mark (static_cast < e_ontology_type > (ndx_item (i)), static_cast < e_ontology_property > (ndx_item (prop)));
                    return true; }
                knots.merge (nuts); nuts.reset (); }
    nits.merge (knots);
    world_wide_wombat_web (nits, v, name);
    return false; }

bool microdata_itemscope::note_itemprop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, itemscope_ptr& scope, page& p)
{   itemprop_indices ii = prepare_itemprop_indices (nits, v, name, value);
    if (scope.get () != nullptr)
    {   microdata_export* ex = exporter ();
        if (ex == nullptr)
            nits.pick (nit_export_none, es_catastrophic, ec_microdata, "exporter failure");
        else for (auto prop : ii)
            scope -> set_exporter (ex, ex -> append_path (export_path_, prop, true)); }
    nitpick knots, nuts;
    for (auto parent : type ())
        for (auto prop : ii)
            if (are_categories_compatible (knots, v, parent, prop))
            {   VERIFY_NOT_NULL (scope, __FILE__, __LINE__);
                for (auto child : scope -> type ())
                    if (are_compatible_types (knots, v, parent, child))
                    {   if (is_valid_property (nuts, v, parent, prop, child))
                        {   nits.merge (nuts);
                            itemprop_.emplace (prop, scope);
                            p.mark (static_cast < e_ontology_type > (parent & uint32_item_mask), static_cast < e_ontology_property > (prop & uint32_item_mask));
                            return true; }
                        knots.merge (nuts); nuts.reset (); } }
    nits.merge (knots);
    world_wide_wombat_web (nits, v, name);
    return false; }

::std::string microdata_itemscope::report (const ::std::size_t offset) const
{   ::std::string res, indent (offset*2, ' ');
    for (mpv_t::const_iterator i = itemprop_.cbegin (); i != itemprop_.cend (); ++i)
#ifndef BOOVAR
        if (! i -> second.valueless_by_exception ())
#endif // BOOVAR
#if BOOVAR == 1
// I can't honest be arsed to work my way around ::boost::variants' restrictions, and in particular VS2015's (presuming) bizarre
// whinging that code containing no consts has too many consts : so no reports for aging compilers.
            ;
#else
            switch (i -> second.index ())
            {   case ip_itemscope :
                    PRESUME (ssc_get < itemscope_ptr > (i -> second).get () != nullptr, __FILE__, __LINE__);
                    res += indent + itemprop_index_name (i -> first) + ":\n";
                    res += ssc_get < itemscope_ptr > (i -> second) -> report (offset+1);
                    break;
                case ip_string :
                    res += indent + itemprop_index_name (i -> first) + " = " + quote (ssc_get < ::std::string > (i -> second)) + "\n";
                    break;
                default :
                    break; }
#endif // BOOVAR
    return res; }

bool microdata_itemscope::write (nitpick& nits, const ::boost::filesystem::path& name)
{   VERIFY_NOT_NULL (export_, __FILE__, __LINE__);
    return export_ -> write (nits, name); }

vit_t microdata_itemscope::sought_itemtypes (const html_version& v, const ::std::string& name) const
{   nitpick nits;
    vit_t res;
    const itemprop_index prop = find_itemprop_index (nits, v, name, type ().empty ());
    if (prop != illegal_itemprop)
        if (prop_category (prop) == itemprop_schema)
            for (auto i : sought_ontology_types (static_cast < e_ontology_property > (ndx_item (prop))))
                res.push_back (i);
    return res; }


bool are_categories_compatible (const e_itemprop_category ipc, const e_itemtype_category itc)
{   if (itc == itemtype_none) return (ipc == itemprop_bespoke);
    return (ipc != itemprop_bespoke); }

bool are_categories_compatible (nitpick& nits, const html_version& , const itemprop_index ipi, const itemtype_index iti)
{   if (are_categories_compatible (prop_category (ipi), type_category (iti))) return true;
    if (prop_category (ipi) == itemprop_bespoke) nits.pick (nit_incompatible_itemtype, es_error, ec_microdata, "ITEMTYPE rejects bespoke ITEMPROPs");
    else nits.pick (nit_incompatible_itemtype, es_info, ec_microdata, "ITEMTYPE and ITEMPROP belong to different microdata categories");
    return false; }

bool are_compatible_types (nitpick& nits, const html_version& , const itemtype_index lhs, const itemtype_index rhs)
{   if (type_category (lhs) == type_category (rhs)) return true;
    nits.pick (nit_incompatible_itemtype, es_info, ec_microdata, "ITEMTYPEs belong to different microdata categories");
    return false; }
