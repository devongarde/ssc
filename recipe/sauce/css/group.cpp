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
#include "css/group.h"
#include "css/arguments.h"
#include "url/url.h"
#include "webpage/page.h"
#include "feedback/nitout.h"
#include "coop/lox.h"
#include "utility/filesystem.h"
#include "utility/cache.h"

css_group::css_group (page& p)
    : page_ (&p)
{   snippets_ = dst_ptr (new distilled (false)); }

void css_group::swap (css_group& g) noexcept
{   bs_.swap (g.bs_);
    snippets_.swap (g.snippets_); 
    mcss_.swap (g.mcss_); 
    elements_.swap (g.elements_); 
    ::std::swap (merged_, g.merged_);
    ::std::swap (page_, g.page_); }

bool css_group::parse (nitpick& , arguments& args, dst_ptr cp, const ::std::string& content, int line)
{   if (! context.load_css () || (context.css_version () != css_1)) return true;
    mcss_t::iterator cc = mcss_.find (content);
    if (cc == mcss_.cend ())
    {   css_ptr p (new css (args, cp, content, line));
        auto res = mcss_.insert ( mcss_t::value_type (content, p)).second;
        bs_ |= p -> get_elements ();
        merged_ = false;
        return res; }
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return false;
    return true; }

bool css_group::parse (nitpick& nits, arguments& args, const ::std::string& content, int line)
{   return parse (nits, args, snippets_, content, line); }

bool css_group::parse_file (nitpick& nits, const namespaces_ptr& n, page& p, const url& u, bool state_versions)
{   if (! context.load_css () || (context.css_version () != css_1)) return true;
    if (! u.valid ()) return false;
    nits.set_context (0, u.original ());
    ::std::string abs = u.absolute ();
    ::std::string::size_type pos = abs.find_last_of ("/");
    PRESUME (pos != ::std::string::npos, __FILE__, __LINE__);
    abs = abs.substr (0, pos+1);
    pos = abs.find ('/');
    if (pos != ::std::string::npos) abs = abs.substr (pos);
    dst_ptr cp = global_css.get_or_preinsert (u.absolute (true));
    VERIFY_NOT_NULL (cp.get (), __FILE__, __LINE__);
    if (cp -> sort_it_out ())
    {   try
        {   bool res = false;
            ::std::string content; ::std::time_t when;
            VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
            if (cached_url (nits, p.version (), p.get_directory (), u, content, when))
                if (content.empty ()) res = true;
                else
                {   arguments args (context.html_ver (), n, &p, state_versions, false, abs, cp);
                    res = parse (nits, args, cp, content, 0); }
            global_css.release (cp);
            return res; }
        catch (const ::std::system_error& e)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "system error ", e.what (), " (processing ", u.original (), ")"); }
        catch (const ::std::exception& e)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "exception ", e.what (), " (processing ", u.original (), ")"); }
        catch (...)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "Unexpected exception processing ", u.original ()); }
        global_css.release (cp);
        return false; }
    p.merge_class (cp -> cl ());
    p.merge_id (cp -> id ());
    p.merge_element_class (cp -> ecl ());
    p.merge_element_id (cp -> eid ());
    return true; }

bool css_group::has_id (const ::std::string& id) const
{   VERIFY_NOT_NULL (snippets_.get (), __FILE__, __LINE__);
    if (snippets_ -> has_id (id)) return true;
    for (auto cs : mcss_)
        if (cs.second -> has_id (id)) return true;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    return page_ -> has_id (id); }

bool css_group::has_class (const ::std::string& s) const
{   VERIFY_NOT_NULL (snippets_.get (), __FILE__, __LINE__);
    if (snippets_ -> has_class (s)) return true;
    for (auto cs : mcss_)
        if (cs.second -> has_class (s)) return true;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    return page_ -> has_class (s); }

bool css_group::note_class (const ::std::string& s)
{   if (! has_class (s)) return false;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    page_ -> use_class (s);
    return true; }

bool css_group::note_element_class (const ::std::string& s)
{   if (! note_class (s)) return false;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    page_ -> use_element_class (s);
    return true; }

bool css_group::note_element (const e_element e)
{   if (! merged_)
    {   merge_smsid (elements_, bs_);
        bs_.reset ();
        merged_ = true; }
    ::std::string s (elem::name (e));
    smsid_t::iterator i = elements_.find (s);
    if (i == elements_.end ()) return false;
    TALLY_TO_MAX (i -> second, 1, SIZE_MAX);
    return true; }

bool css_group::note_id (const ::std::string& s)
{   if (! has_id (s)) return false;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    page_ -> use_id (s);
    return true; }

bool css_group::note_element_id (const ::std::string& s)
{   if (! note_id (s)) return false;
    VERIFY_NOT_NULL (page_, __FILE__, __LINE__);
    page_ -> use_element_id (s);
    return true; }

bool css_group::note_class (const e_element e, const ::std::string& s)
{   if (! note_class (s)) return false;
    if ((e < elem_error) && (e != elem_undefined))
        note_element_class (elem::name (e) + "." + s);
    return true; }

bool css_group::note_id (const e_element e, const ::std::string& s)
{   if (! note_id (s)) return false;
    if ((e < elem_error) && (e != elem_undefined))
        note_element_id (elem::name (e) + "#" + s);
    return true; }

::std::string css_group::review (mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   ::std::string res;
    for (auto i : mcss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        const css_ptr& p = i.second;
        res += p -> review (mac, entry, head, foot, page_head, unfiltered); }
    return res; }

void css_group::accumulate (nitpick& nits) const
{   for (auto i : mcss_)
        i.second -> accumulate (nits); }

void css_group::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (auto c : mcss_)
        c.second -> accumulate (s);
    if (snippets_.get () != nullptr)
        snippets_ -> accumulate (s); }
