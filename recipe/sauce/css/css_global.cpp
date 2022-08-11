/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "css/css_global.h"
#include "url/url.h"
#include "webpage/page.h"
#include "feedback/nitout.h"
#include "coop/lox.h"
#include "utility/filesystem.h"
#include "utility/cache.h"

cs_uptr css_global;

void init_css ()
{   css_global = cs_uptr (new css_global_t); }

void css_global_t::report_usage (::std::ostringstream& ss) const
{   PRESUME (! fred.activity (), __FILE__, __LINE__);
    if (context.tell (es_warning))
    {   ::std::string cls;
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        for (auto i : smsi_)
        {   mmac_t mac;
            ::std::string lex (::boost::lexical_cast < ::std::string > (i.second));
            mac.emplace (nm_class_name, i.first);
            mac.emplace (nm_class_int, lex);
            mac.emplace (nm_class_count, once_twice_thrice (i.second));
            cls += macro -> apply (ns_class, mac); }
        if (! cls.empty ())
            ss << macro -> apply (ns_class_head) << cls << macro -> apply (ns_class_foot); } }
