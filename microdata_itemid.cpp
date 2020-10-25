/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#include "standard.h"
#include "microdata_itemid.h"
#include "element.h"
#include "quote.h"

struct itemid
{   ::std::string path_;
    int line_ = 0;
    itemid (const ::std::string& path, const int line)
        :   path_ (path), line_ (line) { } };

typedef ::std::map < ::std::string, itemid > miid_t;
miid_t miid;

bool note_itemid (nitpick& nits, const html_version& , const ::std::string& id, const ::std::string& path, const int line)
{   auto i = miid.emplace (id, itemid (path, line));
    if (i.second) return true;
    nits.pick (nit_bad_itemid, ed_microdata, "5.1.4 Global identifiers for items", es_warning, ec_microdata, quote (id), " is not unique; see line ", i.first -> second.line_, " of ", i.first -> second.path_);
    return false; }

::std::string report_itemids ()
{   ::std::string res;
    for (auto i : miid)
        res += i.first + " (" + i.second.path_ + ":" + ::boost::lexical_cast < ::std::string > (i.second.line_) + ")\n";
    return res; }

bool empty_itemid ()
{   return miid.empty (); }

bool invalid_itemid (nitpick& nits, const html_version& v, const ::std::string& id, const element* const e)
{   return ! note_itemid (nits, v, id, e -> name (), e -> line ()); }
