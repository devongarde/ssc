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
#include "coop/lox.h"
#include "utility/filesystem.h"

css_uptr css_cache;

void init_css_cache ()
{   css_cache = css_uptr (new css_cache_t); }

bool css_cache_t::parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding, const bool snippet)
{   lox l (lox_css);
    csss_it cc = csss_.find (content);
    if (cc == csss_.cend ())
        return csss_.insert (csss_vt (content, css_ptr (new css (nits, v, content, encoding, snippet)))).second;
    VERIFY_NOT_NULL (cc -> second, __FILE__, __LINE__);
    if (cc -> second -> invalid ()) return false;
    cc -> second -> active (true);
    return true; }

bool css_cache_t::parse_file (nitpick& nits, const page& p, const url& u)
{   if (! u.valid ()) return false;
    nits.set_context (0, u.original ());
    ::std::string content, ua (u.absolute ());
    if (ss_.get () != nullptr )
    {   lox l (lox_css);
        auto i = ss_ -> find (ua);
        if (i != ss_ -> cend ())
            content = i -> second; }
    if (content.empty ())
    {   if (context.rpt_opens ())
            nits.pick (nit_opening_file, es_debug, ec_css, "Loading ", absolute_name (u.original ()));
        content = p.load_url (nits, u);
        if (content.empty ())
            nits.pick (nit_cannot_load_css, es_error, ec_css, "Cannot load ", quote (u.original ()), ", or it is empty");
        if (ss_.get () == nullptr)
        {   ss_ptr ssp (new ss_t);
            VERIFY_NOT_NULL (ssp.get (), __FILE__, __LINE__);
            lox l (lox_css);
            ss_ = ssp;
            ::std::this_thread::yield (); }
        lox l (lox_css);
        ss_ -> insert (ss_vt (ua, content)); }
    if (content.empty ()) return false;
    return parse (nits, p.version (), content, bom_to_encoding (get_byte_order (content)), false); }

bool css_cache_t::has_id (const ::std::string& id) const
{   lox l (lox_css);
    for (csss_cit i = csss_.cbegin (); i != csss_.cend (); ++i)
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        if (i -> second -> has_id (id)) return true; }
    return false; }

bool css_cache_t::note_usage (const ::std::string& id)
{   lox l (lox_css);
    for (auto i : csss_)
    {   VERIFY_NOT_NULL (i.second, __FILE__, __LINE__);
        if (i.second -> note_usage (id))
            return true; }
    return false; }

void css_cache_t::report_usage (::std::ostringstream& ss) const
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

void css_cache_t::delete_snippets ()
{   csss_it i = csss_.begin ();
    while (i != csss_.end ())
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        if (i -> second -> snippet ())
            i = csss_.erase (i);
        else ++i; } }

void css_cache_t::deactivate_all ()
{   for (csss_it i = csss_.begin (); i != csss_.end (); ++i)
    {   VERIFY_NOT_NULL (i -> second, __FILE__, __LINE__);
        i -> second -> active (false); } }

void css_cache_t::post_process ()
{   delete_snippets ();
    deactivate_all (); }
