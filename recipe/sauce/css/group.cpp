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
#include "webpage/page.h"

css_group::css_group (page& p) : page_ (p)
{   snippets_ = dst_ptr (new distilled (false)); }

css_ptr css_group::parse (  dst_ptr dsp, const ::std::string& content, const html_version& v, const namespaces_ptr& ns, bool state_version, bool snippet, const ::std::string& abs, const element_bitset eb,
                            int line, const e_element e, const ::boost::filesystem::path dp)
{   VERIFY_NOT_NULL (dsp.get (), __FILE__, __LINE__);
    css_ptr res;
    if (! context.load_css () || (context.css_version () == css_none)) return res;
    element_bitset ebc (eb);
    if (e != elem_undefined)
    {   bs_.set (e);
        ebc.set (e); }
    mcss_t::iterator cc = mcss_.find (content);
    if (cc == mcss_.cend ())
    {   res = css_ptr (new css (v, content, ns, dsp, page_, abs, state_version, snippet, line, e, ebc, dp));
        if (! mcss_.insert (mcss_t::value_type (content, res)).second) return css_ptr ();
        bs_ |= res -> get_elements ();
        merged_ = false;
        return res; }
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return css_ptr ();
    return res; }

css_ptr css_group::parse (const ::std::string& content, const html_version& v, bool state_version, int line , const e_element e)
{   return parse (snippets_, content, v, ns_, state_version, true, ::std::string (), bs_, line, e); }

bool css_group::parse (const ::std::string& content, const html_version& v, const namespaces_ptr& ns, const element_bitset eb, bool state_version, int line, const e_element e, const ::boost::filesystem::path dp)
{   return parse (snippets_, content, v, ns, state_version, true, ::std::string (), eb, line, e, dp) != css_ptr (); }

bool css_group::parse_file (nitpick& nits, const namespaces_ptr& ns, const url& u, const bool state_versions, const bool local, const bool reparse)
{   if (! context.load_css () || (context.css_version () == css_none)) return true;
    if (! u.valid ()) return false;
    nits.set_context (0, u.original ());
    ::std::string abs = u.absolute ();
    ::std::string::size_type pos = abs.find_last_of ("/");
    if (pos == ::std::string::npos)
    {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_css, "read beyond end of url (", quote (u.original ()), ") file name ", quote (abs));
        return false; }
    abs = abs.substr (0, pos+1);
    pos = abs.find ('/');
    if (pos != ::std::string::npos) abs = abs.substr (pos);
    dst_ptr dsp = global_css.get_or_preinsert (u.absolute (true));
    VERIFY_NOT_NULL (dsp.get (), __FILE__, __LINE__);
    if (dsp -> borked ())
    {   nits.pick (nit_url_not_found, es_error, ec_css, u.original (), " appears borked");
        return false; }
    if (reparse || dsp -> sort_it_out ())
    {   try
        {   bool res = false;
            ::std::string content;
            ::std::time_t when = 0;
            bool borked = false;
            VERIFY_NOT_NULL (page_.get_directory (), __FILE__, __LINE__);
            if (cached_url (nits, page_.version (), page_.get_directory (), u, content, when, borked))
                if (borked || content.empty ()) res = true;
                else
                {   // namespaces_ptr ns; // don't optimise this away, mr. optimiser!
                    css_ptr cp = parse (dsp, content, context.html_ver (), ns, state_versions, false, abs, empty_element_bitset, 0, elem_undefined, page_.get_disk_path (nits, u));
                    res = (cp != css_ptr ());
                    if (res && (local || context.ext_css ())) dsp -> css (cp); }
            global_css.release (dsp);
            return res; }
        catch (const ::std::system_error& e)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "system error ", e.what (), " (processing ", u.original (), ")"); }
        catch (const ::std::exception& e)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "exception ", e.what (), " (processing ", u.original (), ")"); }
        catch (...)
        {   nits.pick (nit_cannot_read, es_catastrophic, ec_css, "unexpected exception processing ", u.original ()); }
        dsp -> borked (true);
        global_css.release (dsp);
        return false; }
    page_.merge_class (dsp -> cl ());
    page_.merge_id (dsp -> id ());
    page_.merge_element_class (dsp -> ecl ());
    page_.merge_element_id (dsp -> eid ());
    page_.merge_font (dsp -> f ());
    return true; }

css_ptr css_group::parse_media_queries (const ::std::string& content, const html_version& v, page& p, const namespaces_ptr& namespaces, const element_bitset eb, bool sv,
                                        int line, const e_element e)
{   dst_ptr dst;
    css_ptr cp = css_ptr (new css (v, content, namespaces, dst, p, p.get_site_path (), sv, true, line, e, eb, p.get_disk_path (), true));
    return cp; }

bool css_group::has_id (const ::std::string& id) const
{   VERIFY_NOT_NULL (snippets_.get (), __FILE__, __LINE__);
    if (snippets_ -> has_id (id)) return true;
    for (auto cs : mcss_)
        if (cs.second -> has_id (id)) return true;
    return page_.has_id (id); }

bool css_group::has_class (const ::std::string& s) const
{   VERIFY_NOT_NULL (snippets_.get (), __FILE__, __LINE__);
    if (snippets_ -> has_class (s)) return true;
    for (auto cs : mcss_)
        if (cs.second -> has_class (s)) return true;
    return page_.has_class (s); }

bool css_group::note_class (const ::std::string& s)
{   if (! has_class (s)) return false;
    page_.use_class (s);
    return true; }

bool css_group::note_element_class (const ::std::string& s)
{   if (! note_class (s)) return false;
    page_.use_element_class (s);
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
    page_.use_id (s);
    return true; }

bool css_group::note_element_id (const ::std::string& s)
{   if (! note_id (s)) return false;
    page_.use_element_id (s);
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

::std::string css_group::review (mmac_t& mac, const ::std::string& sp, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   ::std::string res;
    for (auto i : mcss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        const css_ptr& p = i.second;
        res += p -> review (mac, entry, head, foot, page_head, unfiltered); }
    css_ptr cp = global_css.expel_cp (sp);
    if (cp.get () != nullptr)
        res += cp -> review (mac, entry, head, foot, page_head, unfiltered); 
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

void css_group::validate ()
{   for (auto i : mcss_)
        i.second -> validate (); }
