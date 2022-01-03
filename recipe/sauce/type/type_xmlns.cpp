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
#include "type/type_xmlns.h"

e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s, ::std::string& n)
{   ::std::string ss (::boost::to_lower_copy (trim_the_lot_off (s)));
    if (v >= xhtml_1_0)
    {   const ::std::string::size_type pos = ss.find (':');
        if ((pos != ::std::string::npos) && (pos > 0) && (pos < (ss.length () - 1)))
        {   type_master < t_namespace > ns;
            const html_version vv (v);
            ::std::string lhs (ss.substr (0, pos));
            ns.set_value (nits, vv, lhs);
            s = ss.substr (pos+1);
            n = lhs;
            if (! ns.good ()) return ns_error;
            if (ns.get () != ns_xmlns) return ns.get ();
            const e_namespace e = type_master < t_namespace > :: find (v, s);
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
