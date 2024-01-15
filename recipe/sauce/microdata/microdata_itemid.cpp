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
#include "microdata/microdata_itemid.h"
#include "element/element.h"
#include "utility/quote.h"
#include "webpage/page.h"

struct itemid
{   ::std::string path_;
    int line_ = 0;
    itemid (const ::std::string& path, const int line)
        :   path_ (path), line_ (line) { } };

typedef ::std::map < ::std::string, itemid > miid_t;
typedef ::std::unique_ptr < miid_t > miid_uptr;
miid_uptr miid;

void reset_itemid ()
{   miid = miid_uptr (new miid_t); }

bool note_itemid (nitpick& nits, const html_version& , const ::std::string& id, const ::std::string& path, const int line)
{   VERIFY_NOT_NULL (miid.get (), __FILE__, __LINE__);
    int l2 = 0;
    ::std::string p2;
    {   lox l (lox_itemid);
        auto i = miid -> emplace (id, itemid (path, line));
        if (i.second) return true;
        l2 = i.first -> second.line_;
        p2 = i.first -> second.path_; }
    nits.pick (nit_bad_itemid, ed_microdata, "5.1.4 Global identifiers for items", es_warning, ec_microdata, quote (id), " is not unique; see line ", l2, " of ", p2);
    return false; }

::std::string report_itemids ()
{   ::std::string res;
    if (! empty_itemid () && context.stats_itemid ())
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        VERIFY_NOT_NULL (miid.get (), __FILE__, __LINE__);
        lox l (lox_itemid);
        for (auto i : *miid)
        {   mmac_t mac;
            mac.emplace (nm_itemid_name, i.first);
            mac.emplace (nm_itemid_page, i.second.path_);
            mac.emplace (nm_itemid_line, ::boost::lexical_cast < ::std::string > (i.second.line_));
            res += macro -> apply (ns_itemid, mac); }
        if (! res.empty ())
            res = macro -> apply (ns_itemid_head) + res + macro -> apply (ns_itemid_foot); }
    return res; }

bool empty_itemid ()
{   lox l (lox_itemid);
    return (miid.get () == nullptr) || miid -> empty (); }

bool invalid_itemid (nitpick& nits, const html_version& v, const ::std::string& id, const element* const e)
{   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    return ! note_itemid (nits, v, id, e -> get_page ().get_site_path (), e -> line ()); }
