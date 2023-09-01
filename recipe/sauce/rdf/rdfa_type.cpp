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
#include "rdf/rdfa_type.h"
#include "type/type.h"
#include "ontology/ontology_type.h"

::std::string type_index_name (const type_index ndx)
{   if (ndx != invalid_type) return sch :: name (static_cast < e_ontology_type > (ndx), true);
    return "untyped"; }

type_index find_type_index (nitpick& nits, const html_version& v, const ::std::string& name)
{   nitpick nuts;
    type_master < t_ontology > sc;
    sc.set_value (nits, v, name);
    if (sc.good ())
    {   const sch st (nits, v, sc.vocab (), sc.root ());
        if (! st.invalid ()) return make_type_index (st.get ()); }
    return invalid_type; }
