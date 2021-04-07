/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#pragma once
#include "type/type_master.h"
#include "url/url_protocol.h"

template < > struct type_master < t_curie > : tidy_string < t_curie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie > :: set_value (nits, v, s); } };

template < > struct type_master < t_curie_safe > : tidy_string < t_curie_safe >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie_safe > :: set_value (nits, v, s); } };

template < > struct type_master < t_curies > : string_vector < t_curies, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_curies, sz_space > :: set_value (nits, v, s); } };

template < > struct type_master < t_inlist > : tidy_string < t_inlist >
{   void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   if (s.empty ()) tidy_string < t_inlist > :: status (s_good);
        else
        {   nits.pick (nit_inlist, ed_rdf, "5. Attributes and Syntax", es_error, ec_rdf, "never give INLIST a value");
            tidy_string < t_inlist > :: status (s_invalid); } } };

template < > struct type_master < t_prefix > : string_vector < t_prefix, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   string_vector < t_prefix, sz_space > :: set_value (nits, v, ss);
        if (! string_vector < t_prefix, sz_space > :: good ()) return;
        if (string_vector < t_prefix, sz_space > :: value_.size () % 2 != 0)
           nits.pick (nit_prefix_odd, ed_rdf, "5. Attributes and Syntax", es_error, ec_rdf, "PREFIX: at least one name or IRI is missing");
        else
        {   ::std::string name;
            bool ok = true;
            for (auto s : string_vector < t_prefix, sz_space > :: value_)
                if (name.empty ())
                {   DBG_ASSERT (! s.empty ());
                    size_t sz = s.length () - 1;
                    if (s.at (sz) == ':')
                    {   name = s.substr (0, sz);
                        if (protocol :: exists (name))
                            nits.pick (nit_rdf_protocol, es_info, ec_rdf, "a standard internet protocol name ", quote (name), ", is used as an RDF name"); }
                    else
                    {   nits.pick (nit_prefix_format, ed_rdf, "5. Attributes and Syntax", es_error, ec_rdf, quote (s), " is not followed by a colon and a space");
                        ok = false;
                        name = s; } }
                else
                {   if (test_value < t_url > (nits, v, s))
                    {   e_namespace ns = examine_value < t_namespace > (nits, v, name);
                        e_xmlns x (examine_value < t_xmlns > (nits, v, s));
                        if (x == x_default) nits.pick (nit_rdf_redefine, es_info, ec_rdf, "redefining known namespace ", quote (name));
                        else
                        {   e_namespace nsx = map_xmlns_to_namespace (x);
                            if (nsx == ns_default)
                                nits.pick (nit_rdf_confusion, es_warning, ec_rdf, "potentially confusion redefinition of XML namespace for ", type_master < t_namespace > :: name (ns));
                            else if (nsx != ns)
                                nits.pick (nit_rdf_confusion, es_warning, ec_rdf, quote(s), " is better used for ", type_master < t_namespace > :: name (ns), ", not ", type_master < t_namespace > :: name (nsx)); } }
                    name.clear (); }
            if (ok) return; }
        string_vector < t_prefix, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_vocab > : tidy_string < t_curie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie > :: set_value (nits, v, s); } };
