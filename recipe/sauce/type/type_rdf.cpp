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
#include "parser/parse_abb.h"
#include "type/type_rdf.h"
#include "element/element.h"

e_status parse_prefixes (nitpick& nits, const html_version& v, const ::std::string ss, const prefixes_t* up, vabb_t& vpre, const bool vrai)
{   ::std::string sss (tart (ss));
    if (sss.empty ())
    {   if (vrai) nits.pick (nit_empty, es_info, ec_rdfa, "empty PREFIX declaration");
        return s_empty; }
    vstr_t vstr (split_by_space (sss));
    if (vstr.size () % 2 != 0)
    {   if (vrai) nits.pick (nit_prefix_odd, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, " a list of space separated PREFIX: CURIE definitions is expected; note the colon space separator");
        return s_invalid; }
    ::std::string name, old_curie, old_name;
    ident_t id = s_error, curie = s_error;
    bool ok = true;
    for (auto s : vstr)
    {   PRESUME (! s.empty (), __FILE__, __LINE__);
        size_t sz = s.length () - 1;
        if ((sz == 0) && (s.at (0) == ':'))
        {   if (vrai) nits.pick (nit_prefix_format, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, "ignoring an isolated colon in ", quote (sss));
            ok = false;
            continue; }
        if (name.empty ())
        {   if (s.at (sz) == ':')
                name = s.substr (0, sz);
            else
            {   if (vrai) nits.pick (nit_prefix_format, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, quote (s), " is not followed by a colon and a space");
                ok = false;
                name = s; }
            PRESUME (! name.empty (), __FILE__, __LINE__);
            if (name == "_")
            {   if (vrai) nits.pick (nit_prefix_format, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, "the default prefix ", quote (name), " cannot be redefined");
                ok = false; }
            else if ((name.find_first_of (ALPHABET) == ::std::string::npos) ||
                (name.find_first_not_of (ALPHADDD "./-_") != ::std::string::npos))
            {   if (vrai) nits.pick (nit_prefix_format, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, quote (name), " must start with a letter, and can contain letters, digits, '.', '/', '-', '_'");
                ok = false; }
            e_protocol prot = protocol_names.find (v, PROTOCOL_NAME, name, true);
            switch (prot)
            {   case pr_error :
                case pr_other :
                    break;
                case pr_http :
                    nits.pick (nit_namespace_confusion, es_error, ec_namespace, "'http' should never be used as a prefix");
                    return s_invalid;
                case pr_https :
                    if (vrai) nits.pick (nit_namespace_confusion, es_warning, ec_namespace, "it is very confusing to use 'https' as a prefix");
                    break;
                default :
                    if (vrai) nits.pick (nit_rdfa_confusion, es_info, ec_rdfa,   "it is confusing that ", quote (name), ", the name of a standard internet protocol (",
                                                                                protocol_names.get (prot, PROTOCOL_DESCRIPTION), " protocol), is used as PREFIX");
                    break; }
            if (up != nullptr)
            {   id = up -> find_shortform (v, schema_names, name);
                if ((id != s_error) && (id != s_none)) old_curie = up -> longform (schema_names, id); }
            else
            {   id = schema_names.find (v, SCHEMA_NAME, name, ! v.xhtml ());
                if ((id != s_error) && (id != s_none)) old_curie = schema_names.get (static_cast < e_schema > (id), SCHEMA_CURIE); }
           if (id == s_error) id = s_none; }
        else
        {   ::std::string l (::boost::to_lower_copy (s)), oc;
            if (up != nullptr)
            {   curie = up -> find_longform (v, schema_names, l);
                if ((curie != s_error) && (curie != s_none)) old_name = up -> shortform (schema_names, curie); }
            else
            {   curie = schema_names.find (v, SCHEMA_CURIE, l, true);
                if (curie != s_error) old_name = schema_names.get (static_cast < e_schema > (curie), SCHEMA_NAME); }
            if (curie == s_error) curie = s_none;
            if (vrai)
                if (id == curie)
                {   if ((id != s_error) && (id != s_none))
                        if (id < s_error)
                            nits.pick (nit_rdfa_redefine, es_info, ec_rdfa, "it is not necessary to redefine ", quote (name), " given it is defined by default");
                        else nits.pick (nit_rdfa_redefine, es_info, ec_rdfa, quote (name), " has already been defined"); }
                else
                {   if ((id < s_error) && (id != s_none))
                        if (vrai) nits.pick (nit_rdfa_confusion, es_warning, ec_rdfa, "it is confusing to redefine the standard prefix ", quote (name));
                    else if (id != s_none)
                        if (vrai) nits.pick (nit_rdfa_redefine, es_warning, ec_rdfa, quote (name), " was previously defined as ", quote (old_curie));
                    if ((curie < s_error) && (curie != s_none))
                        nits.pick (nit_rdfa_confusion, ed_rdfa_c, "", es_info, ec_rdfa, quote (l), " is predefined by standard as ", quote (schema_names.get (static_cast < e_schema > (curie), SCHEMA_NAME)));
                    else if (curie != s_none)
                        nits.pick (nit_rdfa_redefine, es_warning, ec_rdfa, quote (l), " is already defined with ", quote (old_name)); }
            if ((id == s_none) || (id != curie))
                vpre.emplace_back (id, name, l);
            name.clear (); } }
    if (ok) return s_good;
    return s_invalid; }

e_status parse_prefixes (nitpick& nits, const html_version& v, const ::std::string ss, const element* box, vabb_t& vpre, const bool vrai)
{   const prefixes_t* prs = nullptr;
    if (box != nullptr)
        if (box != nullptr)
            prs = box -> node ().prefixes ().get ();
    return parse_prefixes (nits, v, ss, prs, vpre, vrai); }
