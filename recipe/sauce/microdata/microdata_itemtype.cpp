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
#include "microdata/microdata_itemtype.h"
#include "schema/schema_type.h"
#include "microformat/prop.h"
#include "type/type_enum_vec.h"

itemtype_index make_itemtype_index (const e_schema_type p)
{   PRESUME (p <= sty_illegal, __FILE__, __LINE__);
    return static_cast < itemtype_index> (p) + (static_cast < itemtype_index> (itemtype_schema) << uint32_category_shift); }

itemtype_index make_itemtype_index (const e_property p)
{   PRESUME (p <= first_illegal, __FILE__, __LINE__);
    if (is_mf_class (p)) return static_cast < itemtype_index> (p) + (static_cast < itemtype_index> (itemtype_microformat) << uint32_category_shift);
    if (is_mf_rel (p)) return static_cast < itemtype_index> (p) + (static_cast < itemtype_index> (itemtype_rel) << uint32_category_shift);
    return 0; }

e_itemtype_category type_category (const itemtype_index ii)
{   return static_cast < e_itemtype_category> (ndx_category (static_cast < uint32_t > (ii))); }

e_schema_type type_itself (const itemtype_index ii)
{   return static_cast < e_schema_type> (ndx_item (static_cast < uint32_t > (ii))); }

itemtype_index find_itemtype_index (nitpick& nits, const html_version& v, const ::std::string& name)
{   nitpick nuts;
    type_master < t_schema > sc;
    sc.set_value (nits, v, name);
    if (sc.good ())
    {   sch st (nits, v, sc.vocab (), sc.root ());
        if (! st.invalid ()) return make_itemtype_index (st.get ()); }
    prop p (nuts, v, name);
    if (p.is_class () || p.is_rel ()) return make_itemtype_index (p.get ());
    return invalid_itemtype; }

::std::string itemtype_index_name (const itemtype_index ndx)
{   if (ndx != invalid_itemtype)
        switch (ndx >> uint32_category_shift)
        {   case itemtype_microformat :
            case itemtype_rel :
                return type_master < t_class > :: name (static_cast < e_class > (ndx_item (ndx)));
            case itemtype_schema :
                return sch :: name (static_cast < e_schema_type > (ndx_item (ndx)), true);
            default : break; }
    return "untyped"; }
