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
#include "main/context.h"
#include "schema/schema_version.h"
#include "parser/html_version.h"

vsv_t vsv;

schema_version::schema_version (const html_version& v)
{   schema_version sv;
    set_mjr (v.mjr (), v.mnr ());
    if (! sv.invalid ()) swap (sv); }

void schema_version::init () // call post context construction
{   vsv.resize (mdd_illegal);
    vsv [mdr_none] = default_schema;
    vsv [mdr_schema] = context.schema_ver ();
    vsv [mdr_whatwg] = whatwg_schema;
    if (context.mf_version1 ()) vsv [mdr_microformats] = mf_1;
    else vsv [mdr_microformats] = mf_2;
    vsv [mdr_purl] = default_schema; }

::std::string schema_version::report () const
{   ::std::ostringstream res;
    if (known ()) switch (root ())
    {   case mdr_schema :
            res << "schema.org v";
            if (mjr () == 7)
                res << static_cast < int > (mjr ()) << ".0" << static_cast < int > (mnr ());
            else res << static_cast < int > (mjr ()) << "." << static_cast < int > (mnr ());
            break;
        case mdr_microformats :
            res << "microformats.org v";
            res << static_cast < int > (mjr ());
            break;
        case mdr_whatwg :
            res << "n.whatwg.org";
            break;
        default :
            res << "unknown schema";
            break; }
    return res.str (); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   DBG_ASSERT (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()));
    DBG_ASSERT (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()));
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_schema_version (const e_microdata_root root, const unsigned char j, const unsigned char n)
{   switch (root)
    {   case mdr_none : return true;
        case mdr_schema :
            if ((j == 0) && (n == 0)) return true;
            if ((j > schema_major_max) || (j < 2)) return false;
            switch (j)
            {   case 2 : return n < 3;
                case 3 : return true;
                case 7 : return n < 5;
                default : return n == 0; }
        case mdr_whatwg :
            return ((j == 1) && (n == 0));
        case mdr_microformats :
            if (n != 0) return false;
            return ((j == 1) || (j == 2));
        default : return false; } }
