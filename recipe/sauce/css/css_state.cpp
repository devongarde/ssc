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
#include "type/type.h"
#include "css/css_state.h"

const property_bitset empty_property_bitset;

::std::string nameset (const property_bitset& bs)
{   ::std::string res;
    for (::std::size_t i = 0; i < ec_error; ++i)
        if (bs.test (i))
        {   if (! res.empty ()) res += ", ";
            res += type_master < t_css_property >::name (static_cast < e_css_property > (i)); }
    return res; }
