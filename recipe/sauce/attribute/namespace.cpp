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
#include "symbol/nstr.h"
#include "type/type.h"
#include "attribute/namespace.h"

ns_id examine_namespace (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, ::std::string& s, ::std::string& n)
{   ::std::string ss = trim_the_lot_off (s);
    if ((! ss.empty ()) && (v >= xhtml_1_0))
    {   if ((ss.at (0) == ':') || (ss.at (ss.length () - 1) == ':'))
        {   nits.pick (nit_bad_namespace, es_error, ec_namespace, quote (s), " is malformed");
            return ns_error; }
        n = decolonise (ss);
        if (! n.empty ())
        {   s = ss;
            if (compare_complain (nits, v, n, XMLNS)) return ns_xmlns;
            const e_namespace standard_name = namespace_names.find (v, NAMESPACE_NAME, n, ! v.xhtml ());
            if ((standard_name != ns_error) && (standard_name != ns_default))
                if ((namespace_names.flags (standard_name) & NS_PREDECLARED) == NS_PREDECLARED)
                    return standard_name;
            if (namespaces)
            {   const ident_t id = namespaces -> find_shortform (v, namespace_names, n, false);
                if ((id != ns_error) && (id != ns_default)) return static_cast < ns_id > (id); }
            nits.pick (nit_bad_namespace, es_error, ec_namespace, quote (n), " has not been declared (using XMLNS)");
            return ns_error; } }
    s = ss; n.clear ();
    return ns_default; }

e_status declare_namespace (nitpick& nits, const html_version& v, const ::std::string& ns, const ::std::string& value, const namespaces_ptr& namespaces, const bool vrai)
{   VERIFY_NOT_NULL (namespaces.get (), __FILE__, __LINE__);
    PRESUME (v >= xhtml_1_0, __FILE__, __LINE__);
    ::std::string xmlns (tart (ns));
    ::std::string schema (tart (value));
    if (schema.empty ())
    {   if (vrai) nits.pick (nit_bad_namespace, es_error, ec_namespace, "a namespace cannot be empty");
        return s_invalid; }
    if (compare_no_case (xmlns, XMLNS))
    {   if (vrai) nits.pick (nit_bad_namespace, es_error, ec_namespace, quote (xmlns), ": really? Unfortunately, that exceeds " PROG "'s daft 'apeth quota (don't define a namespace called XMLNS)");
        return s_invalid; }
    ::std::string lc_name, lc_schema;
    if (v.xhtml ())
    {   lc_name = xmlns; lc_schema = schema; }
    else
    {   lc_name = ::boost::to_lower_copy (xmlns);
        lc_schema = ::boost::to_lower_copy (schema); }
    ident_t id = 0;
    e_namespace standard_name = ns_default;
    if (! lc_name.empty ())
    {   id = namespaces -> find_shortform (v, namespace_names, lc_name, false);
        standard_name = namespace_names.find (v, NAMESPACE_NAME, lc_name, ! v.xhtml ());
        if ((id == 0) && (standard_name != ns_error) && (standard_name != ns_default))
        {   const flags_t flags = namespace_names.flags (standard_name);
            if ((flags & NS_PREDECLARED) == NS_PREDECLARED) id = standard_name; }
        if (vrai)
        {   const e_protocol prot = protocol_names.find (v, 0, xmlns, true);
            if ((prot != pr_error) && (prot != pr_other))
                nits.pick (nit_namespace_confusion, es_info, ec_namespace,  "it is potentially confusing that ", quote (xmlns), ", the name of a standard internet protocol (",
                                                                            protocol_names.get (prot, PROTOCOL_DESCRIPTION), " protocol), is used as an XMLNS namespace"); } }
    const ident_t lf = namespaces -> find_longform (v, namespace_names, lc_schema, false);
    const e_namespace standard_schema = namespace_names.find (v, NAMESPACE_SCHEMA, lc_schema, ! v.xhtml ());
    if (vrai)
    {   if ((id != 0) || (lf != 0))
            if (lf == id) nits.pick (nit_duplicate_namespace, es_comment, ec_namespace, quote (xmlns), " has already been specified");
            else
            {   if (id != 0) nits.pick (nit_namespace_confusion, es_warning, ec_namespace, "namespace ", quote (xmlns), " was previously specified as ", quote (namespaces -> longform (namespace_names, id)));
                if (lf != 0)
                {   ::std::string osf = namespaces -> shortform (namespace_names, lf);
                    if (! osf.empty ())
                    {   const ident_t osf_id = namespaces -> find_shortform (v, namespace_names, osf, false);
                        if ((osf_id != ns_default) && (osf_id != ns_error))
                        {   const flags_t flags = namespace_names.flags (static_cast < e_namespace > (osf_id));
                            if ((flags & NS_PREDECLARED) == 0)
                                nits.pick (nit_namespace_confusion, es_warning, ec_namespace, quote (schema), " was previously specified with ", quote (osf));
                            else nits.pick (nit_namespace_confusion, es_info, ec_namespace, quote (schema), " is specified with ", quote (osf), " by default"); } } } }
        if ((standard_name != ns_default) && (standard_schema != ns_xhtml))
            if (standard_name != standard_schema)
            {   if ((standard_name != ns_default) && (standard_name != ns_error))
                    nits.pick (nit_contradictory_namespace, es_warning, ec_namespace, quote (xmlns), " is commonly associated with ", quote (namespace_names.get (standard_name, NAMESPACE_SCHEMA)), ", not ", quote (schema));
                if ((standard_schema != ns_default) && (standard_schema != ns_error))
                    nits.pick (nit_contradictory_namespace, es_warning, ec_namespace, quote (schema), " is commonly associated with ", quote (namespace_names.get (standard_schema, NAMESPACE_NAME)), ", not ", quote (xmlns)); }
        if (standard_schema == ns_error)
        {   if (standard_name == ns_default)
                nits.pick (nit_unrecognised_namespace, es_catastrophic, ec_namespace, PROG " does not know about the default namespace ", quote (schema), ", so cannot properly verify its content");
            else nits.pick (nit_unrecognised_namespace, es_warning, ec_namespace, PROG " does not know about ", quote (schema), ", so will be unable to verify ", quote (xmlns));
            world_wide_wombat_web (nits, v, schema); } }
    switch (standard_name)
    {   case ns_default :
            if (standard_schema == ns_error)
                if (lc_name.empty () || (lc_name == "_")) return s_invalid;
            break;
        case ns_xhtml :
            if (standard_schema != ns_xhtml)
            {   nits.pick (nit_namespace_redefine, es_error, ec_rdfa, quote (xmlns), " cannot be redefined to ", quote (schema));
                return s_invalid; }
            nits.pick (nit_namespace_redefine, ed_rdfa_c, "(entire document)", es_info, ec_rdfa, "it is not necessary to redefine ", quote (xmlns), ", it is defined by default");
            break;
        default :
            break; }
    const ident_t ns_id = namespaces -> declare (v, namespace_names, lc_name, lc_schema);
    if (ns_id == ns_error) return s_invalid;
    return s_good; }
