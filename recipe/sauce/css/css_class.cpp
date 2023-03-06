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
#include "css/css_class.h"
#include "stats/stats.h"
#include "type/type.h"

css_class::css_class (arguments& args, const int i, const ::std::string& s)
    : s_ (s)
{   nitpick& nits = args.t_.at (i).nits_;
    html_class c (nits, args.v_, s);
    if (c.is_whatwg_draft ())
        nits.pick (nit_whatwg_class, ed_jan07, "3.4.5. Classes", es_info, ec_css, "FYI, ", quote (c.name ()), " was once a draft HTML 5 standard class name.");
    if (c.is_microformat_vocabulary ())
        nits.pick (nit_class_microformat_vocabulary, ed_microformats, "https://microformats.org/", es_warning, ec_css, quote (c.name ()), " is a microformats vocabulary class name.");
    if (c.is_microformat_property ())
        nits.pick (nit_class_microformat_property, ed_microformats, "https://microformats.org/", es_warning, ec_css, quote (c.name ()), " is a microformats property class name.");
    if (args.dst_.get () != nullptr)
        args.dst_ -> insert_class (s); }

void css_class::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> dcl_class (s_);
    s -> dcl_element_class (elem::name (e) + "." + s_); }

void css_class::shadow (::std::stringstream& ss, arguments& )
{   if (! s_.empty ()) ss << "." << s_;   }
