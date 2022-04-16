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
#include "css/css_cache.h"
#include "url/url.h"
#include "webpage/page.h"
#include "feedback/nitout.h"

css_cache_t css_cache;

bool css_cache_t::parse_file (nitpick& nits, const page& p, const url& u)
{   csss_it cc = csss_.find (u.original ());
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (u.original (), css_ptr (new css (nits, p, u)))).second;
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return false;
    cc -> second -> active (true);
    return true; }

bool css_cache_t::parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding)
{   csss_it cc = csss_.find (content);
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (content, css_ptr (new css (nits, v, content, encoding, true)))).second;
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return false;
    cc -> second -> active (true);
    return true; }

void css_cache_t::delete_snippets ()
{   csss_it i = csss_.begin ();
    while (i != csss_.end ())
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        if (i -> second -> snippet ())
            i = csss_.erase (i);
        else ++i; } }

bool css_cache_t::has_id (const ::std::string& id) const
{   for (csss_cit i = csss_.cbegin (); i != csss_.cend (); ++i)
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        if (i -> second -> has_id (id)) return true; }
    return false; }

bool css_cache_t::note_usage (const ::std::string& id)
{   for (auto i : csss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        if (i.second -> note_usage (id))
            return true; }
    return false; }

void css_cache_t::report_usage (::std::ostringstream& ss) const
{   if (context.tell (es_warning))
    {   smsid_t sum;
        ::std::string cls;
        for (auto i : csss_)
        {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
            i.second -> tally (sum); }
        for (auto i : sum)
        {   mmac_t mac;
            ::std::string lex (::boost::lexical_cast < ::std::string > (i.second));
            mac.emplace (nm_class_name, i.first);
            mac.emplace (nm_class_int, lex);
            mac.emplace (nm_class_count, once_twice_thrice (i.second));
            cls += macro.apply (ns_class, mac); }
        if (! cls.empty ())
            ss << macro.apply (ns_class_head) << cls << macro.apply (ns_class_foot); } }
