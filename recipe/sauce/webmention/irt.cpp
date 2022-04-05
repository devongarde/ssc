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
#include "webmention/irt.h"
#include "main/context.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "webpage/external.h"
#include "webpage/page.h"
#include "webpage/directory.h"
#include "webpage/headers.h"
#include "webmention/webmention.h"

void reply::swap (reply& r) noexcept
{   file_.swap (r.file_);
    id_.swap (r.id_);
    server_.swap (r.server_);
    target_.swap (r.target_);
    content_.swap (r.content_);
    when_.swap (r.when_);
    ::std::swap (activity_, r.activity_); }

bool reply::set_server (const ::std::string& link)
{   if (link.empty ()) return false;
    PRESUME (! target_.empty (), __FILE__, __LINE__);
    if (link.find (COLON) != link.npos)
        server_ = link;
    else
    {   ::std::size_t eod = target_.npos;
        const ::std::size_t css = target_.find (CSS);
        if (css != target_.npos)
        {   eod = target_.find (SLASH, css+3);
            if (eod == target_.npos) eod = target_.length (); }
        if (::gsl::at (link, 0) == SLASH)
        {   if (eod != target_.npos)
                server_ = target_.substr (0, eod);
            else
            {   vstr_t site (context.site ());
                if (site.size () == 0) return false;
                server_ = HTTP;
                server_ += ::gsl::at (site, 0); }
            server_ += link; }
        else
        {   const ::std::size_t last = target_.length () - 1;
            const bool slashed = ::gsl::at (target_, last) == SLASH;
            if (eod != target_.npos)
                server_ = target_;
            else
            {   vstr_t site (context.site ());
                if (site.size () == 0) return false;
                server_ = HTTP;
                server_ += ::gsl::at (site, 0);
                if (::gsl::at (target_, 0) != SLASH)
                    server_ += SLASH;
                server_ += target_; }
            if (! slashed) server_ += SLASH;
            server_ += link; } }
    return true; }

bool reply::find_server (nitpick& nits, const html_version& v, const lingo& lang)
{   if (target_.empty ()) return false;
    bool ok = true;
    bool vrai = context.header ().empty ();
    ::boost::filesystem::path http_temp (context.header ());
    if (vrai)
    {   http_temp = get_tmp_filename ();
        ok = fetch_http (nits, v, url (nits, v, target_), http_temp); }
    if (ok)
    {   ::std::string http (read_text_file (nits, http_temp.string ()));
        headers h (nits, v, http);
        if (h.abusive_site ()) if (context.tell (es_warning)) nits.pick (nit_pos_piracy, es_warning, ec_webmention, target_, " uses privacy piracy techniques");
        ::std::string link (h.link (WEBMENTION));
        if (set_server (link))
        {   if (context.tell (es_comment)) nits.pick (nit_webmention, es_comment, ec_webmention, "found " WEBMENTION " server ", server_, " in headers for ", target_);
            if (vrai) if (file_exists (http_temp)) delete_file (http_temp);
            return true; } }
    if (vrai) if (file_exists (http_temp)) delete_file (http_temp);
    ::boost::filesystem::path html_temp (get_tmp_filename ());
    ::std::string html;
    if (fetch (nits, v, url (nits, v, target_), html_temp)) html = read_text_file (nits, html_temp.string ());
    if (file_exists (html_temp)) delete_file (html_temp);
    if (html.empty ()) return false;
    page p (nits, target_, 0, html);
    p.examine ();
    ::std::string mention = p.find_webmention (lang);
    if (! set_server (mention)) return false;
    if (context.tell (es_comment))
        nits.pick (nit_webmention, es_comment, ec_webmention, "found " WEBMENTION " server ", server_, " for ", target_);
    return true; }

void reply::mark ()
{   time_t ridiculous_1;
    time (&ridiculous_1);
    const struct tm *ridiculous_2 = gmtime (&ridiculous_1);
    VERIFY_NOT_NULL (ridiculous_2, __FILE__, __LINE__);
    ::boost::format ridiculous_3 ("%04d.%02d.%02d %02d:%02d:%02d");
    ridiculous_3 % (ridiculous_2 -> tm_year + 1900) % ridiculous_2 -> tm_mon % ridiculous_2 -> tm_mday % ridiculous_2 -> tm_hour % ridiculous_2 -> tm_min % ridiculous_2 -> tm_sec;
    when_ = ridiculous_3.str (); }

::std::string reply::clean (const ::std::string& s)
{   ::std::string res;
    bool whitespace = false;
    for (auto ch : s)
    {   if (! ::std::iswspace (ch) && ! ::std::iswcntrl (ch)) { res += ch; whitespace = false; }
        else if (! whitespace) { res += ' '; whitespace = true; } }
    return res; }

bool reply::operator == (const reply& rhs) const noexcept
{   return  (file_ == rhs.file_) &&
            (id_ == rhs.id_) &&
            (target_ == rhs.target_) &&
            (content_ == rhs.content_); }

bool reply::close_but_no_banana (const reply& rhs) const noexcept
{   return  (file_ == rhs.file_) &&
            (id_ == rhs.id_) &&
            (target_ == rhs.target_); }

void reply::read (const ::boost::property_tree::ptree& tree, const ::std::string& container)
{   file_ = read_field < ::std::string > (tree, container, PAGE);
    id_ = read_field < ::std::string > (tree, container, ID);
    server_ = read_field < ::std::string > (tree, container, SERVER);
    target_ = read_field < ::std::string > (tree, container, TARGET);
    content_ = read_field < ::std::string > (tree, container, CONTENT);
    when_ = read_field < ::std::string > (tree, container, WHEN); }

void reply::write (::boost::property_tree::ptree& tree, const ::std::string& container)
{   write_field < ::std::string > (tree, container, PAGE, file_);
    write_field < ::std::string > (tree, container, ID, id_);
    write_field < ::std::string > (tree, container, SERVER, server_);
    write_field < ::std::string > (tree, container, TARGET, target_);
    write_field < ::std::string > (tree, container, CONTENT, content_);
    write_field < ::std::string > (tree, container, WHEN, when_); }

void reply::mark_unchanged ()
 {  if (context.tell (es_info)) report ("Static");
    activity_ = act_static; }

void reply::mark_update ()
{   activity_ = act_update; mark (); }

void reply::mark_insert ()
{   activity_ = act_insert; mark (); }

void reply::mark_delete ()
{   activity_ = act_delete; mark (); }

::std::string reply::report (const char* verb) const
{   ::std::ostringstream res;
    if (context.tell (es_all)) res << START_OF_SECTION " " << verb << '\n' <<  file_ << '\n' << id_ << '\n' << server_ << '\n' << target_ << '\n' << content_ << '\n' << ::std::endl;
    return res.str (); }

::std::string reply::report (const ::std::size_t n) const
{   ::std::ostringstream res;
    if (context.tell (es_all)) res << n << ":" << file_ << ',' << id_ << ',' << server_ << ',' << target_ << ',' << content_ << ::std::endl;
    return res.str (); }

bool reply::enact (nitpick& nits, const html_version& v, const lingo& lang)
{   PRESUME (activity_ != act_unknown, __FILE__, __LINE__);
    if (activity_ == act_static) return true;
    if (! find_server (nits, v, lang)) return false;
    return mention (nits, v, url (nits, v, file_), url (nits, v, target_), url (nits, v, server_)); }

reply::reply (nitpick& nits, const ::boost::json::object& jo)
{    }

bool reply::save (nitpick& nits, ::boost::json::object& jo)
{   
    return true; }
#endif // HAS_WM
