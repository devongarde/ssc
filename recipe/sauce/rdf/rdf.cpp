/*
ssc (static site checker)
File Info
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
#include "rdf/rdf.h"
#include "utility/quote.h"
#include "webpage/page.h"
#include "ontology/ontology_type.h"
#include "ontology/ontology_property.h"
#include "type/type.h"
#include "element/element.h"

typedef enum { pm_scope, pm_string } prop_member;

bool is_valid_property (nitpick& nits, const html_version& v, const e_ontology_type t, const e_ontology_property p, const ::std::string& value, const bool is_link)
{   switch (sch::root (t))
    {   case s_as :
        case s_cc :
        case s_ctag :
        case s_dc :
        case s_dcam :
        case s_dct :
        case s_dcmi :
        case s_ddi :
        case s_foaf :
        case s_gr :
        case s_pam :
        case s_pamp :
        case s_pcmm :
        case s_pcm :
        case s_pcv :
        case s_pim :
        case s_pmi :
        case s_prism :
        case s_prism_ad :
        case s_prl :
        case s_prm :
        case s_prs :
        case s_psv :
        case s_pur :
        case s_schema :
        case s_vcard :
            return is_valid_ontology_property (nits, v, t, p, value, is_link);
        case s_microformats :
        case s_rdfa :
            return true;
        default :
            break; }
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }

bool is_valid_property (nitpick& nits, const html_version& v, const e_ontology_type t, const e_ontology_property p, const e_ontology_type value)
{   switch (sch::root (t))
    {   case s_as :
        case s_cc :
        case s_ctag :
        case s_dc :
        case s_dcam :
        case s_dct :
        case s_dcmi :
        case s_foaf :
        case s_gr :
        case s_pam :
        case s_pamp :
        case s_pcmm :
        case s_pcm :
        case s_pcv :
        case s_pim :
        case s_pmi :
        case s_prism :
        case s_prism_ad :
        case s_prl :
        case s_prm :
        case s_prs :
        case s_psv :
        case s_pur :
        case s_schema :
        case s_vcard :
            return is_valid_ontology_property (nits, v, t, p, value);
        case s_microformats :
        case s_rdfa :
            return true;
        default :
            break; }
    GRACEFUL_CRASH (__FILE__, __LINE__);
    UNREACHABLE (return false); }

template < typename ENUM > ENUM rdf_t::fit_vocab (const html_version& , const ::std::string& ) const
{   GRACEFUL_CRASH (__FILE__, __LINE__); }

template < > e_ontology_type rdf_t::fit_vocab < e_ontology_type > (const html_version& v, const ::std::string& name) const
{   for (auto voc : vocab_)
    {   nitpick nuts;
        const e_ontology_type t = sch :: parse (nuts, v, name, voc);
        if (t != ont_illegal) return t; }
    if (up_ != nullptr) return up_ -> fit_vocab < e_ontology_type > (v, name);
    return ont_illegal; }

template < > prop_indices rdf_t::fit_vocab < prop_indices > (const html_version& v, const ::std::string& name) const
{   prop_indices ii;
    for (auto voc : vocab_)
    {   vsp_t props = get_ontology_properties (name, voc);
        for (auto pp : props)
            ii.emplace_back (make_prop_index (pp)); }
    if (up_ != nullptr)
    {   prop_indices pii = up_ -> fit_vocab < prop_indices > (v, name);
        for (auto pi : pii)
            ii.emplace_back (pi); }
    return ii; }

vty_t rdf_t::type () const
{   if (use_parent ())
    {   VERIFY_NOT_NULL (up_, __FILE__, __LINE__);
        return up_ -> type (); }
    return type_; }

vsh_t rdf_t::vocabs () const
{   vsh_t res (vocab_);
#ifdef NOMERGE
    if (up_ == nullptr) merge_stuff (res, rdfa_ontology_context ());
    else merge_stuff (res, up_ -> vocabs ());
#else // NOMERGE
    if (up_ == nullptr) res.merge (rdfa_ontology_context ());
    else res.merge (up_ -> vocabs ());
#endif // NOMERGE
    return res; }

prop_indices rdf_t::prepare_prop_indices (nitpick& nits, const html_version& v, const ::std::string& name)
{   prop_indices ii;
    vsh_t vs (vocabs ());
    if (name.find (':') == ::std::string::npos)
        ii = fit_vocab < prop_indices > (v, name);
    if (ii.empty ())
        ii = find_prop_indices (nits, v, vs, name, false);
    if (ii.empty ())
    {   e_ontology mr = s_none;
        ::std::string::size_type ends_at = 0;
        mr = ontology_names.starts_with (ONTOLOGY_CURIE, v.xhtml (), name, &ends_at);
        if (mr == s_error)
        {   world_wide_wombat_web (nits, v, name);
            return ii; }
        ii = find_prop_indices (nits, v, vs, name.substr (ends_at), false); }
    if (ii.empty ())
        nits.pick (nit_bad_property, es_warning, ec_rdfa, quote (name), " is not known");
    return ii; }

bool rdf_t::note_prop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, const bool is_link, page& p)
{   ::std::string xpan = expand_prefix (v, name);
    prop_indices ii = prepare_prop_indices (nits, v, xpan);
    for (auto prop : ii)
        for (auto i : type ())
        {   if (is_valid_property (nits, v, i, prop, value, is_link))
            {   prop_.emplace (prop, prop_value (value));
                p.mark (static_cast < e_ontology_type > (i), static_cast < e_ontology_property > (prop));
                return true; } }
   world_wide_wombat_web (nits, v, xpan);
   return false; }

bool rdf_t::note_prop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& , rdf_t* scope, page& p)
{   ::std::string xpan (expand_prefix (v, name));
    prop_indices ii = prepare_prop_indices (nits, v, xpan);
    nitpick knots, nuts;
    bool ok = true;
    for (auto parent : type ())
        for (auto prop : ii)
            {   VERIFY_NOT_NULL (scope, __FILE__, __LINE__);
            for (auto child : scope -> type ())
                {   if (is_valid_property (nuts, v, parent, prop, child))
                    {   nits.merge (nuts);
                        prop_.emplace (prop, scope);
                        p.mark (static_cast < e_ontology_type > (parent), static_cast < e_ontology_property > (prop)); }
                    else
                    {   ok = false;
                        knots.merge (nuts);
                        nuts.reset (); } } }
    if (! ok)
    {   nits.merge (knots);
        world_wide_wombat_web (nits, v, xpan); }
    return ok; }

e_ontology_type rdf_t::note_type (nitpick& nits, const html_version& v, const ::std::string& name, page& p)
{   nitpick nuts;
    e_ontology_type t = ont_illegal;
    if (name.find (':') == ::std::string::npos)
        t = fit_vocab < e_ontology_type > (v, name);
    else
    {   ::std::string xpan = expand_prefix (v, name);
            type_master < t_ontology > ts;
            ts.set_value (nits, v, xpan);
            ::std::string::size_type ends_at = 0;
            const e_ontology ns = ontology_names.starts_with (ONTOLOGY_CURIE, v.xhtml (), xpan, &ends_at);
            if (ns == s_error)
                world_wide_wombat_web (nits, v, xpan);
            else
            {   const sch sc (nits, v, ontology_names.after_start (ONTOLOGY_CURIE, xpan.substr (ends_at), v.xhtml ()), ns);
                t = sc.get (); } }
    if (t != ont_illegal)
    {   p.mark (t);
        const flags_t flags = sch :: flags (t);
        if ((flags & SF_DEPRECATED) == SF_DEPRECATED)
            nits.pick (nit_deprecated_ontology, es_info, ec_microdata, quote (name), " is deprecated");
        const itemtype_index ii = make_type_index (t);
        type_.push_back (ii);
        return t; }
    return ont_context; }

e_ontology rdf_t::note_vocab (nitpick& nits, const html_version& v, const ::std::string& name, page& )
{   ::std::string xpan = expand_prefix (v, name);
    const e_ontology s = ontology_names.find_lower (v, ONTOLOGY_CURIE, xpan);
    if ((s == s_none) || (s == s_error))
        nits.pick (nit_bad_vocab, es_error, ec_rdfa, PROG " does not know about ", quote (name), " so will be unable to verify its content");
    else if (is_vocab_defined (s))
        nits.pick (nit_vocab_defined, es_warning, ec_rdfa, quote (name), " is already defined");
    else
    {   if ((ontology_names.flags (s) & ONTOLOGY_CRAPSPEC) == ONTOLOGY_CRAPSPEC)
            nits.pick (nit_crap_spec, es_warning, ec_json, quote (ontology_names.get (s, ONTOLOGY_NAME)), " is poorly specified: use an alternative");
        vocab_.insert (s); }
    return s; }

::std::string rdf_t::report (const ::std::size_t offset) const
{   ::std::string res, indent (offset*2, ' ');
    for (mrv_t::const_iterator i = prop_.cbegin (); i != prop_.cend (); ++i)
#ifndef BOOVAR
        if (! i -> second.valueless_by_exception ())
#endif // BOOVAR
#if BOOVAR == 1
            ;
#else
            switch (i -> second.index ())
            {   case pm_scope :
                    PRESUME (ssc_get < rdf_t*> (i -> second) != nullptr, __FILE__, __LINE__);
                    res += indent + prop_index_name (i -> first) + ":\n";
                    res += ssc_get < rdf_t* > (i -> second) -> report (offset+1);
                    break;
                case pm_string :
                    res += indent + prop_index_name (i -> first) + " = " + quote (ssc_get < ::std::string > (i -> second)) + "\n";
                    break;
                default :
                    break; }
#endif // BOOVAR
    return res; }

vty_t rdf_t::sought_types (const html_version& v, const ::std::string& name) const
{   nitpick nits;
    vit_t res;
    prop_indices pi = find_prop_indices (nits, v, vocabs (), name, type ().empty ());
    for (auto prop : pi)
        for (auto i : sought_ontology_types (static_cast < e_ontology_property > (ndx_item (prop))))
            res.push_back (i);
    return res; }

::std::string rdf_t::expand_prefix (const html_version& v, const ::std::string& s) const
{   if (prefixes_ == nullptr) return s;
    ::std::string ss (s);
    ::std::string prefix (decolonise (ss));
    if (prefix.empty ()) return s;
    const ident_t p = prefixes_ -> find_shortform (v, ontology_names, prefix);
    if ((p == s_error) || (p == s_none)) return s;
    return prefixes_ -> longform (ontology_names, p) + ss; }

bool rdf_t::verify_value (nitpick& nits, const html_version& v, const e_ontology_type ty, const ::std::string& value)
{   const flags_t f (sch::flags (ty));
    if (has_simple_ontology_type (f))
    {   const e_type t = get_simple_ontology_type (f);
        return test_value (nits, v, t, value); }
    return false; }
