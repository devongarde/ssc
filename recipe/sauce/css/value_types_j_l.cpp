/*
ssc (static site checker)
File Info
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

#include "main/standard.h"

#ifdef LIMITED_META_COMPLEXITY
#include "css/value.h"
#include "css/value_types.h"

int test_value_fns_j_l (arguments& args, int& start, const int to, nitpick& nits, const e_type t, const e_css_val_fn fn, const e_css_property id)
{   return value_types < SSC_TYPES_J_L, t_unknown > :: check (args, start, to, nits, t, fn, id); }
#endif // LIMITED_META_COMPLEXITY
