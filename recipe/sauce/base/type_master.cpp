/*
ssc (static site checker)
File Info
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
#include "element/element.h"

// would prefer to use template parameter packs, but got hacked off with the fussy clear-as-mud syntax
bool test_many (const vtype_t& vty, v_np& bad, v_np& good, const nitpick& model, const html_version& v, const vstr_t& vs) 
{   if (vs.size () == 0) return true;
    if (vty.size () == 0)
    {   nitpick gnits (model.get_line (), model.get_context ());
        for (::std::size_t i = 0; i < vs.size (); ++i)
            gnits.pick (nit_css_syntax, es_error, ec_type, quote (vs.at (i)), ": unexpected (1)");
        bad.push_back (gnits);
        return false; }
    nitpick nits (model.get_line (), model.get_context ());
    if (! test_value (nits, v, vty.at (0), vs.at (0)))
    {   bad.push_back (nits);
        return test_many (vtype_t (vty.cbegin () + 1, vty.cend ()), bad, good, model, v, vs); }
    bad.push_back (nits);
    good.push_back (nits);
    return test_many (vtype_t (vty.cbegin () + 1, vty.cend ()), bad, good, model, v, vstr_t (vs.cbegin () + 1, vs.cend ())); }

bool test_many (const vtype_t& vty, nitpick& nits, const html_version& v, const vstr_t& vs) 
{   v_np bad, good;
    if (test_many (vty, bad, good, nits, v, vs))
    {   for (auto g : good)
            nits.merge (g);
        return true; }
    for (auto b : bad)
        nits.merge (b);
    return false; }
