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
#include "parser/parse_abb.h"
#include "css/arguments.h"
#include "css/id.h"
#include "stats/stats.h"

css_id::css_id (arguments& args, const ::std::string& s)
    : s_ (s)
{   if (args.dst_.get () != nullptr)
        args.dst_ -> insert_id (s); }

void css_id::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> dcl_id (s_);
    s -> dcl_element_id (elem::name (e) + "#" + s_); }

void css_id::shadow (::std::stringstream& ss, arguments& )
{   if (! s_.empty ()) ss << "#" << s_;   }
