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
#include "css/css_group.h"
#include "css/css_global.h"
#include "url/url.h"
#include "webpage/page.h"
#include "feedback/nitout.h"
#include "coop/lox.h"
#include "utility/filesystem.h"
#include "utility/cache.h"

bool css_group_t::parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding, const bool snippet)
{   csss_it cc = csss_.find (content);
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (content, css_ptr (new css (nits, v, content, encoding, snippet)))).second;
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return false;
    return true; }

bool css_group_t::parse_file (nitpick& nits, const page& p, const url& u)
{   if (! u.valid ()) return false;
    nits.set_context (0, u.original ());
    ::std::string content; ::std::time_t when;
    if (! cached_url (nits, p.version (), p.get_directory (), u, content, when)) return false;
    if (content.empty ()) return true;
    return parse (nits, p.version (), content, bom_to_encoding (get_byte_order (content)), false); }

bool css_group_t::has_id (const ::std::string& id) const
{   for (csss_cit i = csss_.cbegin (); i != csss_.cend (); ++i)
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        if (i -> second -> has_id (id)) return true; }
    return false; }

bool css_group_t::note_usage (const ::std::string& id)
{   for (auto i : csss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        if (i.second -> note_usage (id))
            return true; }
    return false; }

void css_group_t::report_usage (::std::ostringstream& ss) const
{   if (context.tell (es_warning))
    {   smsid_t sum;
        ::std::string cls;
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        for (auto i : csss_)
        {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
            i.second -> tally (sum); }
        for (auto i : sum)
        {   mmac_t mac;
            ::std::string lex (::boost::lexical_cast < ::std::string > (i.second));
            mac.emplace (nm_class_name, i.first);
            mac.emplace (nm_class_int, lex);
            mac.emplace (nm_class_count, once_twice_thrice (i.second));
            cls += macro -> apply (ns_class, mac); }
        if (! cls.empty ())
            ss << macro -> apply (ns_class_head) << cls << macro -> apply (ns_class_foot); } }

void css_group_t::accumulate () const
{   if (csss_.empty ()) return;
    lox l (lox_css);
    for (auto i : csss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        const css_ptr& p = i.second;
        p -> tally (css_global -> ho ()); } }
