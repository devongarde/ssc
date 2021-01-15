/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

bool css_cache::parse_file (nitpick& nits, const page& p, const url& u)
{   csss_it cc = csss_.find (u.original ());
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (u.original (), css_ptr (new css (nits, p, u)))).second;
    if (cc -> second -> invalid ()) return false;
    cc -> second -> active (true);
    return true; }

bool css_cache::parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding)
{   csss_it cc = csss_.find (content);
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (content, css_ptr (new css (nits, v, content, encoding, true)))).second;
    if (cc -> second -> invalid ()) return false;
    cc -> second -> active (true);
    return true; }

void css_cache::delete_snippets ()
{   csss_it i = csss_.begin ();
    while (i != csss_.end ())
    {   if (i -> second -> snippet ())
            i = csss_.erase (i);
        else ++i; } }

bool css_cache::has_id (const ::std::string& id) const
{   for (csss_cit i = csss_.cbegin (); i != csss_.cend (); ++i)
        if (i -> second -> has_id (id)) return true;
    return false; }

bool css_cache::note_usage (const ::std::string& id)
{   for (auto i : csss_)
        if (i.second -> note_usage (id))
            return true;
    return false; }

void css_cache::report_usage (::std::ostringstream& ss) const
{   if (context.tell (e_warning))
    {   smsid_t sum;
        for (auto i : csss_)
            i.second -> tally (sum);
        for (auto i : sum)
            if (context.test ())
                if (i.second == UINT_MAX) ss << i.first << " *\n";
                else ss << i.first << " " << i.second << "\n";
            else if (i.second == 0)
                ss << "class " << quote (i.first) << " is unused\n";
            else if (context.tell (e_info))
                switch (i.second)
                {   case 1 :
                        if (context.tell (e_info))
                            ss << "class " << quote (i.first) << " is used once\n";
                        break;
                    case 2 :
                        if (context.tell (e_info))
                            ss << "class " << quote (i.first) << " is used twice\n";
                        break;
                    case 3 :
                        if (context.tell (e_info))
                            ss << "class " << quote (i.first) << " is used thrice\n";
                        break;
                    case UINT_MAX :
                        if (context.tell (e_info))
                            ss << "class " << quote (i.first) << " is heavily used\n";
                        break;
                    default :
                        if (context.tell (e_info))
                            ss << "class " << quote (i.first) << " is used " << i.second << " times\n";
                        break; } } }
