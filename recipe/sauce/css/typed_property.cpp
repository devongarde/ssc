/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "feedback/nitpick.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/group.h"

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to)
{   bool res = true;
    if (from > 0)
    {   ::std::string prop;
        const int comma = token_find (args.t_, ct_comma, from, to);
        const int ket = token_find (args.t_, ct_round_ket, from, to);
        int next = ket;
        if ((comma > 0) && (comma < ket)) next = comma;
        if (args.t_.at (from).t_ == ct_string)
        {   prop = args.t_.at (from).val_;
            const int k = next_non_whitespace (args.t_, from, to);
            if (k != next)
            {   nits.pick (nit_css_custom, ed_css_custom, "2. Defining Custom Properties", es_error, ec_css, "Junk found after ", quote (prop));
                res = false; } }
        else prop = assemble_string (args.t_, from, next, false);
        auto i = args.g_.custom_prop ().find (prop);
        if (i == args.g_.custom_prop ().cend ())
        {   if (comma < 0)
            {   nits.pick (nit_css_custom, es_warning, ec_css, quote (prop), " is not a known customer property");
                res = false; }
            else
            {   args.g_.custom_prop ().emplace (prop, 1);
                nits.pick (nit_css_custom, es_info, ec_css, quote (prop), " noted (with fallback value)"); }
            res = false; }
        else i -> second += 1; }
    return res; }

bool check_custom_property (arguments& args, const ::std::string& s)
{   auto i = args.g_.custom_prop ().find (s);
    if (i == args.g_.custom_prop ().cend ()) return false;
    i -> second += 1;
    return true; }
