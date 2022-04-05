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
#include "main/context.h"
#include "main/args.h"
#include "webmention/converse.h"

#ifndef NO_JSONIC
/* json format:

    control info (ssc version etc.)
    context info (date)
    site
        page
            label
                webmention
*/

#define WM_FILE "wm.json"
#define FIRST_RELEASE 125

#define NEW_SNIPPET \
    "<div class=\"new_mention\">\n" \
    "<h4 lang=\"" STANDARD_ENGLISH "\">New!!</h4>\n\n" \
    "<p>\n" \
    "{{content}}\n" \
    "</p>\n" \
    "<p>\n\n" \
    "<a href=\"{{source}}\">{{source}}</a>, {{when}}\n" \
    "</p>\n" \
    "</div>"

#define CHANGE_SNIPPET \
    "<div class=\"change_mention\">\n" \
    "<h4 lang=\"" STANDARD_ENGLISH "\">Changed!</h4>\n\n" \
    "<p>\n" \
    "{{content}}\n" \
    "</p>\n\n" \
    "<p>\n" \
    "<a href=\"{{source}}\">{{source}}</a>, {{when}}\n" \
    "</p>\n" \
    "</div>"

#define DELETE_SNIPPET \
    "<div class=\"delete_mention\">\n" \
    "<h4 lang=\"" STANDARD_ENGLISH "\">Deleted</h4>\n\n" \
    "<p>\n" \
    "<a href=\"{{source}}\">{{source}}</a>, {{when}}\n\n" \
    "</p>\n" \
    "</div>"

#define STATIC_SNIPPET \
    "<div class=\"static_mention\">\n" \
    "<h4 lang=\"" STANDARD_ENGLISH "\">Static</h4>\n\n" \
    "<p>\n" \
    "{{content}}\n" \
    "</p>\n\n" \
    "<p>\n" \
    "<a href=\"{{source}}\">{{source}}</a>, {{when}}\n" \
    "</p>\n" \
    "</div>"

bool converse_t::load_headers (nitpick& nits, const ::boost::json::object& jo, uint64_t& major, uint64_t& minor, uint64_t& release)
{   if (jo.empty ())
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, " is borked");
        return false; }
    if (! jo.contains (PROG) || ! jo.contains (VERSION) || ! jo.contains (SITE))
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, " does not appear to be written by " PROG);
        return false; }
    if ((jo.count (PROG) != 1) || (jo.count (VERSION) != 1) || (jo.count (SITE) != 1) || (jo.at (PROG) != FULLNAME))
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, " does not appear to be written by " PROG ", or is corrupt and should be deleted");
        return false; }
    if (! jo.at (VERSION).is_array ())
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, " appears to be corrupt; please delete it");
        return false; }
    ::boost::json::array jv = jo.at (VERSION).as_array ();
    if (jv.size () != 3)
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, "'s version information is corrupt; please delete the file");
        return false; }
    major = jv.at (0).as_int64 ();
    minor = jv.at (1).as_int64 ();
    release = jv.at (2).as_int64 ();
    if ((major <= 0) && (minor <= 0) && (release < FIRST_RELEASE))
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, " is corrupt; please delete it");
        return false; }
    ::boost::tribool later = ::boost::indeterminate;
    if (major > VERSION_MAJOR) later = true;
    else if (major < VERSION_MAJOR) later = false;
    else if (minor > VERSION_MINOR) later = true;
    else if (minor < VERSION_MINOR) later = false;
    else if (release > VERSION_RELEASE) later = true;
    if (later == true)
    {   nits.pick (nit_json_version, es_error, ec_webmention, "This is " PROG " v" VERSION_STRING ", but ", filename_, " was written by " PROG " v", major, ".", minor, ".", release, ": it's from the future.");
        return false; }
    else if (later == false)
    {   nits.pick (nit_json_version, es_error, ec_webmention, "This is " PROG " v" VERSION_STRING ", but ", filename_, " was written by " PROG " v", major, ".", minor, ".", release, ": it's too old.");
        return false; }
    ::boost::json::array jd = jo.at (SITE).as_array ();
    if (jd.size () == 0)
    {   nits.pick (nit_json_corrupt, es_error, ec_webmention, filename_, "'s site information is corrupt; please delete the file");
        return false; }
    vstr_t ss = context.site ();
    bool ok = ss.size () == jd.size ();
    for (int i = 0; ok && (i < ss.size ()); ++i)
        if (ss.at (i) != jd.at (i).as_string ().c_str ())
            ok = false;
    if (! ok)
    {   ::std::string ours, theirs;
        for (auto s : ss) ours += s + ' ';
        for (auto j : jd)
        {   theirs += j.as_string ().c_str ();
            theirs += ' '; }
        nits.pick (nit_json_domain, es_warning, ec_webmention, filename_, " was written for ", theirs, "not ", ours); }
    return true; }

bool converse_t::prepare_headers (jsonic& js)
{   ::boost::json::object jo;
    jo [PROG] = FULLNAME;
    ::boost::json::array jv, jd;
    jv.emplace_back (VERSION_MAJOR);
    jv.emplace_back (VERSION_MINOR);
    jv.emplace_back (VERSION_RELEASE);
    jo [VERSION] = jv;
    jo [BUILD] = context.build ();
    for (auto a : context.site ()) jd.emplace_back (a);
    jo [SITE] = jd;
    jo [DATETIME] = context.started ();
    js.val () = jo;
    return true; }

void converse_t::set_filename ()
{   if (filename_.empty ())
    {   filename_ = context.path ();
        filename_ /= WM_FILE; } }

bool converse_t::load (nitpick& nits)
{   if (activity_) return true;
    activity_ = true;
    set_filename ();
    if (! ::boost::filesystem::exists (filename_)) return false;
    ::std::string content (read_text_file (nits, filename_));
    jsonic js;
    if (! js.parse (nits, content, cc_utf8)) return false;
    if (! js.val ().is_object ())
    {   nits.pick (nit_json_error, es_error, ec_webmention, "cannot parse " WEBMENTION " cache ", filename_);
        return false; }
    const ::boost::json::object& jo = js.val ().as_object ();
    uint64_t major = 0, minor = 0, release = 0;
    if (! load_headers (nits, jo, major, minor, release)) return false;
    in_.load (nits, jo);
    return true; }

bool converse_t::save (nitpick& nits)
{   if (! activity_) return true;
    jsonic js;
    prepare_headers (js);
    set_filename ();
    try
    {   ::boost::filesystem::path tmp (get_tmp_filename ());
        {   ::std::ofstream f (tmp.string ());
            f << js.val (); }
        if (! ::boost::filesystem::exists (tmp))
        {   nits.pick (nit_json_error, es_error, ec_webmention, "cannot prepare ", filename_);
            return false; }
        if (::boost::filesystem::exists (filename_)) ::boost::filesystem::remove (filename_);
        ::boost::filesystem::rename (tmp, filename_); }
    catch (const ::std::system_error& e)
    {   nits.pick (nit_json_error, es_error, ec_webmention, "preparing ", filename_, " raised system error ", e.what ());
        return false; }
    catch (const ::std::exception& e)
    {   nits.pick (nit_json_error, es_error, ec_webmention, "preparing ", filename_, " raised ", e.what ());
        return false; }
    catch (...)
    {   nits.pick (nit_json_error, es_error, ec_webmention, "unknown exception preparing ", filename_);
        return false; }
    return true; }

::std::string converse_t::load_template (nitpick& nits, const ::std::string& supplied, const char* defname, const char* deftmp)
{   ::std::string res (template_path (nits, defname, supplied));
    if (! res.empty ()) return res;
    return deftmp; }

void converse_t::load_templates (nitpick& nits)
{   if (! templates_.empty ()) return;
    templates_ = context.templates ();
    if (templates_.size () <= 4) templates_.resize (4);
    ::gsl::at (templates_, act_insert) = load_template (nits, ::gsl::at (templates_, act_insert), "new.tpl", NEW_SNIPPET);
    ::gsl::at (templates_, act_update) = load_template (nits, ::gsl::at (templates_, act_update), "change.tpl", CHANGE_SNIPPET);
    ::gsl::at (templates_, act_delete) = load_template (nits, ::gsl::at (templates_, act_delete), "delete.tpl", DELETE_SNIPPET);
    ::gsl::at (templates_, act_static) = load_template (nits, ::gsl::at (templates_, act_static), "static.tpl", STATIC_SNIPPET); }

void converse_t::process_outgoing_webmentions (nitpick& nits, const html_version& v, const lingo& lang)
{   load (nits);
    out_.process (nits, v, lang); }

void converse_t::process_incoming_webmentions (nitpick& nits, const html_version& v, const vstr_t& mentions)
{   load_templates (nits);
    load (nits);
    in_.process (nits, v, templates_, mentions); }

#endif // NO_JSONIC
#endif // HAS_WM
