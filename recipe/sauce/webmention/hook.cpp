/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "webmention/hook.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "main/context.h"
#include "webpage/external.h"
#include "webpage/directory.h"
#include "element/element.h"
#include "webpage/page.h"
#include "webmention/webmentions.h"

#define AUTHOR "author"
#define DELETED "deleted"
#define POST "post"
#define SECRET "secret"
#define SOURCE "source"
#define TARGET "target"

/*   turns out this example is just that . the actual contents is entirely random, judging by https://github.com/aaronpk/webmention.io#api
{
  "secret": "1234abcd",
  "source": "http://rhiaro.co.uk/2015/11/1446953889",
  "target": "http://aaronparecki.com/notes/2015/11/07/4/indiewebcamp",
  "post": {
    "type": "entry",
    "author": {
      "name": "Amy Guy",
      "photo": "http://webmention.io/avatar/rhiaro.co.uk/829d3f6e7083d7ee8bd7b20363da84d88ce5b4ce094f78fd1b27d8d3dc42560e.png",
      "url": "http://rhiaro.co.uk/about#me"
    },
    "url": "http://rhiaro.co.uk/2015/11/1446953889",
    "published": "2015-11-08T03:38:09+00:00",
    "name": "repost of http://aaronparecki.com/notes/2015/11/07/4/indiewebcamp",
    "repost-of": "http://aaronparecki.com/notes/2015/11/07/4/indiewebcamp",
    "wm-property": "repost-of"
  }
}

{
  "secret": "1234abcd",
  "source": "http://rhiaro.co.uk/2015/11/1446953889",
  "target": "http://aaronparecki.com/notes/2015/11/07/4/indiewebcamp",
  "deleted": true
}
*/

hook::hook (nitpick& nits, const html_version& v, const ::std::string& filename)
    : deleted_ (false)
{   parse (nits, v, filename);
    check (); }

hook::hook (nitpick& nits, const html_version& v, const ::std::string& source, const ::std::string& target)
    : source_ (nits, v, source), target_ (nits, v, target), deleted_ (false), valid_ (true)
{   check (); }

bool hook::parse (nitpick& nits, const html_version& , const ::std::string& filename)
{   if (! file_exists (filename)) return false;
    ::boost::property_tree::ptree json;
    ::boost::property_tree::read_json (filename, json);
    if (json.empty ()) return false;
    ::std::string secret = read_field < ::std::string > (json, SECRET);
    if (secret != context.secret ())
    {   nits.pick (nit_wrong_secret, es_catastrophic, ec_webmention, "wrong secret :-("); return false; }
    DBG_ASSERT (false); // want to diagnose what's up, don't want to drop out
    source_.reset (nits, read_field < ::std::string > (json, SOURCE));
    target_.reset (nits, read_field < ::std::string > (json, TARGET));
    if (source_.empty () || target_.empty ())
    {   nits.pick (nit_insufficient, es_error, ec_webmention, "insufficient information"); return false; }
    deleted_ = read_field < bool > (json, DELETED);
    return true; }

bool hook::update_mention (nitpick& nits, const ::std::string& s)
{   /* source, target, content, datetime of change */
    /* target / page (slashes to dots) . id / source / number  */
    ::boost::filesystem::path folder (context.incoming ());
    folder /= target_.domain ();
    if (target_.has_path () && target_.path () != "/")
        folder /= slash_dot (target_.path ());
    if (target_.has_id ())
    {   folder += ".";
        folder += target_.id (); }
    folder /= source_.domain ();
    folder /= slash_dot (source_.path ());
    if (! file_exists (folder))
        make_directories (folder);
    ::boost::filesystem::path filename (folder);
    filename /= source_.page ();
    filename += EXT;
    webmentions mentions (nits, filename, target_);
    if (mentions.invalid ()) mentions.reset ();
    webmention mensh (source_, target_, s);
    if (! mensh.invalid ())
        mentions.merge (mensh);
    if (! mentions.write (nits)) return false;
    return mentions.create_html (); }

bool hook::process (nitpick& nits, const html_version& v)
{   if (! source_.is_usable ()) return false;
    ::boost::filesystem::path tmp (get_tmp_filename ());
    if (! fetch (nits, v, url (nits, v, source_.original ()), tmp))
        nits.pick (nit_cannot_read, es_error, ec_webmention, "Cannot read ", source_.original ());
    else
    {   ::std::string html = read_text_file (tmp.string ());
        ::std::time_t updated = 0;
        page p (nits, source_.original (), updated, html);
        if (p.invalid ())
            nits.pick (nit_dubious_html, es_error, ec_webmention, source_.original (), " appears to be dubious HTML");
        else
        {   // directory d (source_.page (), true);
            p.examine ();
            ::std::string info = p.find_mention_info (target_, false, false);
            if (info.empty ())
                nits.pick (nit_cannot_find_mention, es_warning, ec_webmention, "cannot find mention of ", target_.absolute (), " in ", source_.original ());
            else update_mention (nits, info); } }
    delete_file (tmp);
    return true;

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
}

void hook::check ()
{   if (target_.empty () || source_.empty ()) valid_ = false;
    else
    {   url t (target_);
        url s (source_);
        valid_ = ! s.invalid () && ! t.invalid () && is_one_of (t.domain (), context.site ()); } }

bool hooks::process (nitpick& nits, const html_version& v)
{   bool res = false;
    for (auto s : context.mentions ())
    {   parameters p (v, s);
        if (p.exists (SOURCE) && p.exists (TARGET))
        {   hook h (nits, v, p.value (SOURCE), p.value (TARGET));
            res = true;
            hooks_.push_back (h); } }
    if (res)
        for (auto h : hooks_)
        {   nits.pick (nit_webmention, es_info, ec_webmention, WEBMENTION " from ", h.source ().domain (), " for ", h.target ().domain (), " found");
            h.process (nits, v); }
    return res; }
