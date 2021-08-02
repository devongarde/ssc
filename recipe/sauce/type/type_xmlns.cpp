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
#include "type/type_xmlns.h"

e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s, ::std::string& n)
{   ::std::string ss (::boost::to_lower_copy (trim_the_lot_off (s)));
    if (v >= xhtml_1_0)
    {   ::std::string::size_type pos = ss.find (':');
        if ((pos != ::std::string::npos) && (pos > 0) && (pos < (ss.length () - 1)))
        {   type_master < t_namespace > ns;
            html_version vv (v);
            ::std::string lhs (ss.substr (0, pos));
            ns.set_value (nits, vv, lhs);
            s = ss.substr (pos+1);
            n = lhs;
            if (! ns.good ()) return ns_error;
            if (ns.get () != ns_xmlns) return ns.get ();
            e_namespace e = type_master < t_namespace > :: find (v, s);
            if (e != ns_default) return ns_xmlns;
            n = XMLNS;
            static ::std::size_t next_free_namespace = first_runtime_namespace;
            if (next_free_namespace == 0xFF)
            {   nits.pick (nit_no_namespaces_left, es_catastrophic, ec_program, PROG " has no capacity for another XMLNS namespace");
                return ns_default; }
            type_master < t_namespace > :: extend (s, ++next_free_namespace);
            return static_cast < e_namespace> (next_free_namespace); } }
    s = ss; n.clear ();
    return ns_default; }

e_namespace xmlns_to_namespace (nitpick& nits, const html_version& , const e_xmlns x)
{   switch (x)
    {   case x_xhtml_1 :
        case x_xhtml_1_superseded :
        case x_xhtml_11 :
        case x_xhtml_2 :return ns_xhtml;
        case x_bibo :   return ns_bibo;
        case x_cc :     return ns_cc;
        case x_crs :    return ns_crs;
        case x_dc :     return ns_dc;
        case x_dc_terms : return ns_dcterms;
        case x_default : return ns_default;
        case x_mathml : return ns_math;
        case x_dbp :    return ns_dbp;
        case x_dbp_owl : return ns_dbp_owl;
        case x_dbr :    return ns_dbr;
        case x_ex :     return ns_ex;
        case x_foaf :   return ns_foaf;
        case x_owl :    return ns_owl;
        case x_rddl :   return ns_rddl;
        case x_rdf :    return ns_rdf;
        case x_rdfa :   return ns_rdfa;
        case x_rdfs :   return ns_rdfs;
        case x_svg :    return ns_svg;
        case x_xhv :    return ns_xhv;
        case x_xlink :  return ns_xlink;
        case x_xml :    return ns_xhtml;
        case x_xmlevents : return ns_xmlevents;
        case x_xmlns :  return ns_xmlns;
        case x_xsd :    return ns_xs;
        case x_xsi :    return ns_xsi;
        case x_html :   return ns_html;
        default :
            nits.pick (nit_xmlns_namespace, es_catastrophic, ec_program, XMLNS " ", static_cast < int > (x), " has no corresponding namespace");
            break; }
    return ns_error; }
