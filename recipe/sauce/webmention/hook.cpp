/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#ifdef HAS_WM
#include "webmention/hook.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "main/context.h"
#include "webpage/external.h"
#include "webpage/directory.h"
#include "element/element.h"
#include "webpage/page.h"
#include "webmention/webmentions.h"
#include "url/url_sanitise.h"

hook::hook (nitpick& nits, const html_version& v, const ::std::string& source, const ::std::string& target)
    : source_ (nits, v, source), target_ (nits, v, target), valid_ (true)
{   check (); }

hook::hook (nitpick& nits, const ::boost::json::object& jo) : valid_ (false) // thank you, lint, but I prefer to explicitly state the falue of valid_ here
{   ::std::string src, targ;
    if (jo.at (SOURCE).is_string ()) src = jo.at (SOURCE).as_string ().c_str ();
    if (jo.at (TARGET).is_string ()) targ = jo.at (TARGET).as_string ().c_str ();
    if (! src.empty () && ! targ.empty ()) 
    {   source_.reset (url (nits, context.html_ver (), src));
        target_.reset (url (nits, context.html_ver (), targ));
        if (source_.valid () && target_.valid ())
            if (! jo.contains (MENTIONS)) valid_ = true;
            else if (jo.at (MENTIONS).is_object ())
            {   const ::boost::json::object& jws (jo.at (MENTIONS).as_object ());
                bool ok = true;
                for (auto i : jws)
                {   ::std::string k (i.key_c_str ());
                    if (i.value ().is_object ())
                        mentions_.emplace (k, webmentions (nits, i.value ().as_object ())); }
                for (auto mensch : mentions_)
                    if (mensch.second.any_invalid ())
                    {   ok = false; break; }
                valid_ = ok; } } } 

bool hook::save (nitpick& nits, ::boost::json::object& jo)
{   if (! valid_) return false;
    jo.emplace (SOURCE, source_.get ());
    jo.emplace (TARGET, target_.get ());
    if (! mentions_.empty ())
    {   ::boost::json::object wmo;
        for (auto i : mentions_)
        {   ::boost::json::object ob;
            if (! i.second.save (nits, ob)) return false;
            wmo.insert_or_assign (i.first, i.second.save (nits, ob)); }
        jo.emplace (MENTIONS, wmo); }
    return true; }

bool hook::update_mention (nitpick& nits, const ::std::string& mention, const ::std::string& trg_src)
{   /* source, target, content, datetime of change */
    /* target / page (slashes to dots) . id / source / number  */
    ::boost::filesystem::path folder (context.incoming ());
    folder /= target_.domain ();
    if (target_.has_path ())
    {   ::std::string p (target_.path ());
        if (p != "/")
        {   if (p.at (0) == '/') p = p.substr (1);
            if ((p != "/") && (p != ".")) folder /= sanitise (slash_dot (p)); } }
    if (target_.has_id ())
    {   folder += ".";
        folder += target_.id (); }
    folder /= source_.domain ();
    if (source_.has_path ())
    {   ::std::string p (source_.path ());
        if (p != "/")
        {   if (p.at (0) == '/') p = p.substr (1);
            if ((p != "/") && (p != ".")) folder /= sanitise (slash_dot (p)); } }
    folder = sanitise (folder.string ());
    if (! file_exists (folder)) make_directories (folder);
    ::boost::filesystem::path filename (folder);
    filename /= source_.page ();
    filename += EXT;
/*
    webmentions mentions (nits, filename, target_);
    if (mentions.invalid ()) mentions.reset ();
    webmention mensh (source_, target_, mention, trg_src);
    if (mensh.invalid ()) return false;
    mentions.merge (mensh);
    if (! mentions.write (nits)) return false;
    return mentions.create_html (nits); */ return true; }

::std::string process_page (nitpick& nits, const html_version& v, const url& u)
{   ::std::string res;
    if (! u.is_usable ())
        nits.pick (nit_protocol, es_error, ec_webmention, quote (u.original ()), " uses neither http nor https");
    else
    {   ::boost::filesystem::path tmp (get_tmp_filename ());
        try
        {   if (fetch (nits, v, url (nits, v, u.original ()), tmp)) res = read_text_file (nits, tmp.string ());
            else nits.pick (nit_cannot_read, es_error, ec_webmention, "Cannot read ", u.original ()); }
        catch (...)
        {   res.clear (); }
        delete_file (tmp); }
    return res; }

bool hook::process (nitpick& nits, const html_version& v, const vstr_t& templates)
{   ::std::string src = process_page (nits, v, source_);
    if (src.empty ()) return false;
    page source (src, true);
    if (source.invalid ())
    {   nits.pick (nit_dubious_html, es_error, ec_webmention, quote (source_.original ()), " doesn't seem to contain HTML");
        return false; }
    ::std::string trg = process_page (nits, v, target_);
    if (trg.empty ()) return false;
    page target (trg, true);
    if (target.invalid ())
    {   nits.pick (nit_dubious_html, es_error, ec_webmention, quote (target_.original ()), " doesn't seem to contain HTML");
        return false; }
    source.examine ();
    if (! source.mentions (target_))
        nits.pick (nit_dubious_mention, es_warning, ec_webmention, quote (source_.absolute ()), " doesn't seem to mention ", quote (target_.absolute ()));
    target.examine ();
    ::std::string info = target.find_mention_hook (target_);
    if (info.empty ())
    {   nits.pick (nit_cannot_find_mention, es_warning, ec_webmention, "cannot find webmention hook in ", quote (target_.absolute ()));
        return false; }
    bool to_us = false;
    const ::std::size_t len = target_.domain ().length ();
    for (auto d : context.site ())
        if (len >= d.length ())
            if (::boost::algorithm::find_tail (d, static_cast < int > (len)) == target_.domain ())
            {   to_us = true; break; }
    if (! to_us)
    {   nits.pick (nit_webmention_external, es_error, ec_webmention, "the webmention target ", quote (target_.absolute ()), " is not local");
        return false; }
    nitpick nuts;
    url u (nuts, v, info, target_.get_protocol ());
    if (! u.is_usable ())
    {   if (context.tell (es_warning)) nits.pick (nit_cannot_find_mention, es_warning, ec_webmention, "unusable webmention link in ", quote (target_.absolute ()));
        nits.merge (nuts);
        return false; }
    if (u.has_absolute_path ())
    {   if (context.tell (es_comment)) nits.pick (nit_endpoint, es_comment, ec_webmention, "webmention endpoint at ", quote (target_.absolute ()), " appears to be ", quote (u.absolute ())); }
    else
    {   ::std::string x (target_.path ());
        ::std::string y (u.path ());
        if (! y.empty ())
        {   if (y.at (0) != '/') x += "/";
            x += y; }
        u.set_component (es_path, sanitise (x));
        if (context.tell (es_info)) nits.pick (nit_endpoint, es_info, ec_webmention, "webmention endpoint at ", quote (target_.absolute ()), " appears to be ", quote (u.absolute (false, true))); }
    if (! u.has_domain ()) u.set_component (es_server, target_.domain ());
    u.set_components (target_);
    if ((u.domain ().find (target_.domain ()) == ::std::string::npos) &&
        (target_.domain ().find (u.domain ()) == ::std::string::npos))
    {   to_us = false;
        for (auto d : context.site ())
            if (len >= d.length ())
                if (::boost::algorithm::find_tail (d, static_cast < int > (len)) == u.domain ())
                {   to_us = true; break; }
        if (! to_us)
            if (context.tell (es_warning)) nits.pick (nit_webmention_css, es_warning, ec_webmention,
                "the webmention hook at ", quote (target_.absolute ()), " is to ", quote (u.absolute ()), ": cross site scripting is dangerous."); }
    update_mention (nits, info, trg);
    return true; }

    // grab offsite source
    // grab all pos relevent webmention info
    // load, if pos, earlier version
    // add new version
    // save
    // load existing page template
    // modify
    // write updated template
    // apply template to page
    // mark website upload necessary

void hook::check ()
{   if (target_.empty () || source_.empty ()) valid_ = false;
    else
    {   url t (target_);
        url s (source_);
        valid_ = ! s.invalid () && ! t.invalid () && is_one_of (t.domain (), context.site ()); } }

void hook::merge (nitpick& nits, const hook& h)
{
}

::std::string hook::page_path () const
{   ::std::string res = target_.get_filepath ();
    ::std::string i = target_.id ();
    if (! i.empty ())
    {   res += '#'; res += i; }
    return res; }
#endif // HAS_WM
