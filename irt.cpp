/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#include "standard.h"
#include "irt.h"
#include "context.h"
#include "common.h"
#include "external.h"
#include "page.h"
#include "directory.h"
#include "headers.h"

#define REPLY "reply"

#define V "version"
#define LENGTH "length"

#define PAGE "page"
#define ID "id"
#define SERVER "server"
#define TARGET "target"
#define CONTENT "content"
#define WHEN "when"

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
    assert (! target_.empty ());
    if (link.find (COLON) != link.npos)
        server_ = link;
    else
    {   ::std::size_t  eod = target_.npos,
                css = target_.find (CSS);
        if (css != target_.npos)
        {   eod = target_.find (SLASH, css+3);
            if (eod == target_.npos) eod = target_.length (); }
        if (link [0] == SLASH)
        {   if (eod != target_.npos)
                server_ = target_.substr (0, eod);
            else
            {   vstr_t site (context.site ());
                if (site.size () == 0) return false;
                server_ = HTTP;
                server_ += site [0]; }
            server_ += link; }
        else
        {   ::std::size_t last = target_.length () - 1;
            bool slashed = target_ [last] == SLASH;
            if (eod != target_.npos)
                server_ = target_;
            else
            {   vstr_t site (context.site ());
                if (site.size () == 0) return false;
                server_ = HTTP;
                server_ += site [0];
                if (target_ [0] != SLASH)
                    server_ += SLASH;
                server_ += target_; }
            if (! slashed) server_ += SLASH;
            server_ += link; } }
    return true; }

bool reply::find_server (nitpick& nits, const html_version& v)
{   if (target_.empty ()) return false;
    bool ok = true;
    bool vrai = context.test_header ().empty ();
    ::boost::filesystem::path http_temp (context.test_header ());
    if (vrai)
    {   http_temp = get_tmp_filename ();
        ok = fetch_http (nits, v, url (nits, v, target_), http_temp); }
    if (ok)
    {   ::std::string http (read_text_file (http_temp.string ()));
        headers h (nits, v, http);
        if (h.abusive_site ()) nits.pick (nit_pos_piracy, es_warning, ec_webmention, target_, " uses privacy piracy techniques");
        ::std::string link (h.link (WEBMENTION));
        if (set_server (link))
        {   nits.pick (nit_webmention, es_comment, ec_webmention, "found " WEBMENTION " server ", server_, " in headers for ", target_);
            if (vrai) if (::boost::filesystem::exists (http_temp)) ::boost::filesystem::remove (http_temp);
            return true; } }
    if (vrai) if (::boost::filesystem::exists (http_temp)) ::boost::filesystem::remove (http_temp);
    ::boost::filesystem::path html_temp (get_tmp_filename ());
    ::std::string html;
    if (fetch (nits, v, url (nits, v, target_), html_temp)) html = read_text_file (html_temp.string ());
    if (::boost::filesystem::exists (html_temp)) ::boost::filesystem::remove (html_temp);
    if (html.empty ()) return false;
    page p (nits, target_, html);
    directory d (target_, true);
    p.examine (d);
    ::std::string mention = p.find_webmention ();
    if (! set_server (mention)) return false;
    if (context.tell (e_comment))
        nits.pick (nit_webmention, es_comment, ec_webmention, "found " WEBMENTION " server ", server_, " for ", target_);
    return true; }

void reply::mark ()
{   time_t ridiculous_1;
    time (&ridiculous_1);
    struct tm *ridiculous_2 = gmtime (&ridiculous_1);
    assert (ridiculous_2 != nullptr);
    ::boost::format ridiculous_3 ("%04d.%02d.%02d %02d:%02d:%02d");
    ridiculous_3 % (ridiculous_2 -> tm_year + 1900) % ridiculous_2 -> tm_mon % ridiculous_2 -> tm_mday % ridiculous_2 -> tm_hour % ridiculous_2 -> tm_min % ridiculous_2 -> tm_sec;
    when_ = ridiculous_3.str (); }

::std::string reply::clean (const ::std::string& s)
{   ::std::string res;
    bool whitespace = false;
    for (auto ch : s)
    {   if (ch > ' ') { res += ch; whitespace = false; }
        else if (! whitespace) { res += ' '; whitespace = true; } }
    return res; }

bool reply::operator == (const reply& rhs) const
{   return  (file_ == rhs.file_) &&
            (id_ == rhs.id_) &&
            (target_ == rhs.target_) &&
            (content_ == rhs.content_); }

bool reply::close_but_no_banana (const reply& rhs) const
{   return  (file_ == rhs.file_) &&
            (id_ == rhs.id_) &&
            (target_ == rhs.target_); }

void reply::read (::boost::property_tree::ptree& tree, const ::std::string& container)
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
 {  if (context.tell (e_info)) report ("Static");
    activity_ = act_static; }

void reply::mark_update ()
{   if (context.nochange () || context.tell (e_info)) report ("Update");
    activity_ = act_update; mark (); }

void reply::mark_insert ()
{   if (context.nochange () || context.tell (e_info)) report ("Insert");
    activity_ = act_insert; mark (); }

void reply::mark_delete ()
{   if (context.nochange () || context.tell (e_info)) report ("Delete");
    activity_ = act_delete; mark (); }

::std::string reply::report (const char* verb) const
{   ::std::ostringstream res;
    if (context.tell (e_all)) res << "*** " << verb << '\n' <<  file_ << '\n' << id_ << '\n' << server_ << '\n' << target_ << '\n' << content_ << '\n' << ::std::endl;
    return res.str (); }

::std::string reply::report (const ::std::size_t n) const
{   ::std::ostringstream res;
    if (context.tell (e_all)) res << n << ":" << file_ << ',' << id_ << ',' << server_ << ',' << target_ << ',' << content_ << ::std::endl;
    return res.str (); }

bool reply::enact (nitpick& nits, const html_version& v)
{   assert (activity_ != act_unknown);
    if (activity_ == act_static) return true;
    if (! find_server (nits, v)) return false;
    return mention (nits, v, url (nits, v, file_), url (nits, v, target_), url (nits, v, server_)); }


void replies::append (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
{   reply_.push_back (reply (file, id, target, content)); }

bool replies::read (const ::std::string filename)
{   if (! ::boost::filesystem::exists (filename)) return true; // no data is mega insert
    ::boost::property_tree::ptree json;
    ::boost::property_tree::read_json (filename, json);
    if (json.empty ()) return false;
    ::std::string version = read_field < ::std::string > (json, PROG, V);
    if (version.substr (0, 3) != "0.0") return false;
    ::std::size_t max = json.get < ::std::size_t > (PROG SEP REPLY SEP LENGTH, 0);
    if (max == 0) return true;
    reply_.reserve (max);
    for (::std::size_t n = 0; n < max; ++n)
    {   ::std::string count = PROG SEP REPLY SEP;
        count += ::boost::lexical_cast < ::std::string > (n);
        reply_.push_back (reply (json, count));
        if (reply_.back ().invalid ()) return false; }
    return true; }

bool replies::write ()
{   ::boost::property_tree::ptree json;
    ::boost::filesystem::path filename (context.persisted ());
    if (context.tell (e_detail)) report ("write");
    write_header (json, REPLY);
    write_field < ::std::size_t > (json, REPLY SEP LENGTH, reply_.size ());
    for (::std::size_t n = 0; n < reply_.size (); ++n)
    {   ::std::string count = REPLY SEP;
        count += ::boost::lexical_cast < ::std::string > (n);
        reply_ [n].write (json, count); }
    return replace_file (json, filename); }

::std::size_t replies::find (const reply& r)
{   for (::std::size_t z = 0; z < reply_.size (); ++z)
        if (reply_ [z] == r) return z;
    return no_reply; }

::std::size_t replies::probably_match (const reply& r)
{   for (::std::size_t z = 0; z < reply_.size (); ++z)
        if (reply_ [z].close_but_no_banana (r)) return z;
    return no_reply; }

bool replies::update_records (nitpick& nits) // not efficient for any real quantities
{   bool res = false;
    ::std::size_t mmax = reply_.size ();
    ::std::size_t imax = context.get_replies ().reply_.size ();
    nits.pick (nit_debug, es_debug, ec_webmention, mmax, " previous replies found in ", context.persisted (), ", ", imax, " found in pages");
    context.get_replies ().report (WEBMENTION);
    if (context.tell (e_detail)) report ("persisted");
    for (::std::size_t z = 0; z < mmax; ++z)
        reply_ [z].mark_unknown ();
    for (::std::size_t z = 0; z < imax; ++z)
    {   ::std::size_t here = find (context.get_replies ().reply_ [z]);
        if (here != no_reply)
        {   if (reply_ [here].is_unknown ())
                reply_ [here].mark_unchanged (); }
        else
        {   here = probably_match (context.get_replies ().reply_ [z]);
            if (here != no_reply)
                reply_ [here].mark_update ();
            else
            {   reply_.push_back (context.get_replies ().reply_ [z]);
                reply_.back ().mark_insert (); }
            res = true; } }
    mmax = reply_.size ();
    for (::std::size_t z = 0; z < mmax; ++z)
    {   if (reply_ [z].is_unknown ())
        {   res = true;
            reply_ [z].mark_delete (); } }
    if (context.tell (e_detail)) report ("post update");
    return res; }

 bool replies::enact (nitpick& nits, const html_version& v) // not efficient for any real quantities
{   bool res = false;
    if (context.tell (e_detail)) report ("enact");
    ::std::size_t mmax = reply_.size ();
    for (::std::size_t z = 0; z < mmax; ++z)
        if (! reply_ [z].enact (nits, v))
        {  if (reply_ [z].is_deleted ())
                reply_ [z].mark_unchanged (); }
        else res = true;
    if (res)
    {   vreply_t reply;
        for (::std::size_t x = 0; x < mmax; ++x)
            if (! reply_ [x].is_deleted ())
                reply.push_back (reply_ [x]);
        reply.shrink_to_fit ();
        reply_.swap (reply); }
    return res; }

bool replies::process (nitpick& nits, const html_version& v)
{   if (! context.notify ()) return true;
    if (context.persisted ().empty ()) return true;
    replies persisted;
    if (! context.clear () && ! persisted.read (context.persisted ())) return false;
    if (! persisted.update_records (nits)) return true;
    if (context.nochange ()) return true;
    persisted.enact (nits, v); // whatever the webmentions, still update the file
    return persisted.write (); }

::std::string replies::report (const char* comment) const
{   ::std::ostringstream res;
    if (context.tell (e_info))
    {   if (comment != nullptr) res << comment << "\n";    // tell?
        for (::std::size_t s = 0; s < reply_.size (); ++s)
           res << reply_ [s].report (s); }
    return res.str (); }
