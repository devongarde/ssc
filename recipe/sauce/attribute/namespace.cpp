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
#include "type/type_enum.h"
#include "type/type_case.h"
#include "type/type_xmlns.h"
#include "attribute/namespace.h"

const ns_id unspecified_namespace = 0;
const ns_id xmlns_namespace = unspecified_namespace + 1;
const ns_id xhtmlns_namespace = xmlns_namespace + 1;
const ns_id xlink_namespace = xhtmlns_namespace + 1;

ns_ptr new_namespace_stack (const html_version& v)
{   ns_ptr res (new namespace_stack);
    namespace_stack* nss = res.get ();
    if (nss != nullptr)
    {   nss -> vns_.emplace_back ("(unspecified)", unspecified_namespace, ns_default, true);
        nss -> ens_.emplace (ns_default, unspecified_namespace);
        nss -> vns_.emplace_back (::std::string (XMLNS), xmlns_namespace, ns_xmlns, true);
        nss -> names_.emplace (::std::string (XMLNS), xmlns_namespace);
        nss -> ens_.emplace (ns_xmlns, xmlns_namespace);
        if (v >= xhtml_1_0)
        {   nss -> vns_.emplace_back (::std::string (XHTMLNS), xhtmlns_namespace, ns_xhtml, true);
            nss -> names_.emplace (::std::string (XHTMLNS), xhtmlns_namespace);
            nss -> ens_.emplace (ns_xhtml, xhtmlns_namespace);
            nss -> vns_.emplace_back (::std::string (XLINK), xlink_namespace, ns_xlink, true);
            nss -> names_.emplace (::std::string (XLINK), xlink_namespace);
            nss -> ens_.emplace (ns_xlink, xlink_namespace); } }
    return res; }

ns_ptr copy_namespace_stack (const ns_ptr& orig)
{   ns_ptr res;
    if (orig.get () != nullptr)
        res = ns_ptr (new namespace_stack (*orig.get ()));
    return res; }

ns_ptr initialise_namespace_stack (const html_version& v, const ns_ptr& orig)
{   if (orig.get () == nullptr) return new_namespace_stack (v);
    return copy_namespace_stack (orig); }

ns_id namespace_stack::add (nitpick& nits, const html_version& v, const ::std::string& xmlns, const ::std::string& schema)
{   DBG_ASSERT (v >= xhtml_1_0);
    DBG_ASSERT (vns_.size () > 0);
    if (schema.empty ())
    {   nits.pick (nit_bad_namespace, es_error, ec_namespace, "a namespace URL cannot be empty");
        return unspecified_namespace; }
    ::std::string lc_name, lc_schema;
    if (v.xhtml ())
    {   lc_name = xmlns; lc_schema = schema; }
    else
    {   lc_name = ::boost::to_lower_copy (xmlns);
        lc_schema = ::boost::to_lower_copy (schema); }
    mxni_t::const_iterator x = xs_.find (lc_schema);
    if (x != xs_.cend ())
        if (x -> second < vns_.size ())
            if (vns_.at (x -> second).name_.empty ())
                nits.pick (nit_duplicate_namespace, es_warning, ec_namespace, "namespace ", quote (schema), " previously declared");
            else nits.pick (nit_duplicate_namespace, es_warning, ec_namespace, "namespace ", quote (schema), " previously declared as ", quote (vns_.at (x -> second).name_));
    midni_t::const_iterator j;
    if (lc_name.empty ()) j = names_.cend ();
    else
    {   j = names_.find (lc_name);
        if (j != names_.cend ())
            if (! vns_.at (j -> second).automatic_)
                nits.pick (nit_duplicate_namespace, es_warning, ec_namespace, "another ", quote (xmlns), " was declared above"); }
    type_master < t_xmlns > typical;
    nitpick nuts;
    typical.set_value (nuts, v, schema);
    if (typical.good ())
    {   if (! xmlns.empty ())
        {   ::std::string typical_name = type_master < t_namespace > :: name (xmlns_to_namespace (nuts, v, typical.get ()));
            if (! typical_name.empty ())
                if (! compare_complain (nits, v, typical_name.c_str (), xmlns))
                    nits.pick (nit_contradictory_namespace, es_info, ec_namespace, quote (schema), " is commonly associated with ", quote (typical_name), ", not ", quote (xmlns)); } }
    else if (! typical.empty ())
        if (xmlns.empty ())
        {   nits.pick (nit_unrecognised_namespace, es_catastrophic, ec_namespace, PROG " does not know about the default namespace ", quote (schema), ", so cannot properly verify its content");
            return unspecified_namespace; }
        else nits.pick (nit_unrecognised_namespace, es_warning, ec_namespace, PROG " does not know about ", quote (schema), ", so will be unable to verify ", quote (xmlns));
    ns_id id = vns_.size ();
    try
    {   e_namespace ens (xmlns_to_namespace (nits, v, typical.get ()));
        vns_.emplace_back (lc_name, id, ens, false);
        if (vns_.back ().id_ != id)
        {   DBG_ASSERT (false);
            return unspecified_namespace; }
        names_.emplace (lc_name, id);
        if (typical.good ()) ens_.emplace (ens, id);
        if (j == names_.cend ()) xs_.emplace (lc_schema, id); }
    catch (...)
    {   // I believe the technical term is 'balls'. Free some memory to help ensure there is sufficient to report the situation, then crash.
        vns_.clear ();
        xs_.clear ();
        ens_.clear ();
        names_.clear ();
        ::std::cerr << "CATASTROPHE: namespace_stack::add is out of sanity while processing " << xmlns << "=" << schema << "\n";
        throw; }
    return id; }

ns_id namespace_stack::find (const ::std::string& name) const
{   midni_t::const_iterator i = names_.find (name);
    if (i == names_.cend ()) return unspecified_namespace;
    return i -> second; }

ns_id namespace_stack::find (const e_namespace en) const
{   meni_t::const_iterator i = ens_.find (en);
    if (i == ens_.cend ()) return unspecified_namespace;
    return i -> second; }

e_namespace namespace_stack::standard (const ns_id id) const
{   DBG_ASSERT (id <= vns_.size ());
    if (id >= vns_.size ()) return ns_custom;
    return vns_.at (id).standard_; }

ns_name namespace_stack::name (const ns_id id) const
{   DBG_ASSERT (id <= vns_.size ());
    if (id >= vns_.size ()) return "";
    return vns_.at (id).name_; }

e_namespace examine_namespace (nitpick& nits, const html_version& v, ns_ptr& ns_stack, ::std::string& s, ::std::string& n)
{   ::std::string ss (::boost::to_lower_copy (trim_the_lot_off (s)));
    if (v >= xhtml_1_0)
    {   ::std::string::size_type pos = ss.find (':');
        if (pos != ::std::string::npos)
        {   e_namespace res = ns_error;
            if ((pos == 0) || (pos == (ss.length () - 1)))
                nits.pick (nit_bad_namespace, es_error, ec_namespace, quote (s), " is malformed");
            else
            {   n = ss.substr (0, pos);
                s = ss.substr (pos+1);
                bool stackless = (ns_stack.get () == nullptr);
                if (compare_complain (nits, v, n, XMLNS)) return ns_xmlns;
                if (! stackless)
                {   ns_id id = ns_stack -> find (n);
                    if (id != unspecified_namespace)
                        return ns_stack -> standard (id); }
                nitpick nuts;
                res = examine_value < t_namespace > (nuts, v, n);
                nits.pick (nit_bad_namespace, es_error, ec_namespace, quote (n), " has not been declared (using XMLNS)"); }
            return res; } }
    s = ss; n.clear ();
    return ns_default; }

ns_id namespace_declaration (nitpick& nits, const html_version& v, ns_ptr& ns_stack, ::std::string& name, const ::std::string& schema)
{   if (ns_stack.get () == nullptr)
        ns_stack = new_namespace_stack (v);
    return ns_stack -> add (nits, v, name, schema); }
