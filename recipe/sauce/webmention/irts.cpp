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
#include "webmention/irts.h"

void replies::append (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
{   reply_.push_back (reply (file, id, target, content)); }

bool replies::read (const ::std::string filename)
{   if (! file_exists (filename)) return true; // no data is mega insert
    ::boost::property_tree::ptree json;
    ::boost::property_tree::read_json (filename, json);
    if (json.empty ()) return false;
    ::std::string version = read_field < ::std::string > (json, PROG, VER);
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
    if (context.tell (es_detail)) report ("write");
    write_header (json, REPLY);
    write_field < ::std::size_t > (json, REPLY SEP LENGTH, reply_.size ());
    for (::std::size_t n = 0; n < reply_.size (); ++n)
    {   ::std::string count = REPLY SEP;
        count += ::boost::lexical_cast < ::std::string > (n);
        reply_ .at (n).write (json, count); }
    return replace_file (json, filename); }

::std::size_t replies::find (const reply& r)
{   for (::std::size_t z = 0; z < reply_.size (); ++z)
        if (reply_.at (z) == r) return z;
    return no_reply; }

::std::size_t replies::probably_match (const reply& r)
{   for (::std::size_t z = 0; z < reply_.size (); ++z)
        if (reply_.at (z).close_but_no_banana (r)) return z;
    return no_reply; }

bool replies::update_records (nitpick& nits) // not efficient for any real quantities
{   bool res = false;
    ::std::size_t mmax = reply_.size ();
    const ::std::size_t imax = context.get_replies ().reply_.size ();
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_webmention, mmax, " previous replies found in ", context.persisted (), ", ", imax, " found in pages");
    context.get_replies ().report (WEBMENTION);
    if (context.tell (es_detail)) report ("persisted");
    for (::std::size_t z = 0; z < mmax; ++z)
        reply_.at (z).mark_unknown ();
    for (::std::size_t z = 0; z < imax; ++z)
    {   ::std::size_t here = find (::gsl::at (context.get_replies ().reply_, z));
        if (here != no_reply)
        {   if (reply_.at (here).is_unknown ())
                reply_.at (here).mark_unchanged (); }
        else
        {   here = probably_match (::gsl::at (context.get_replies ().reply_, z));
            if (here != no_reply)
                reply_.at (here).mark_update ();
            else
            {   reply_.push_back (::gsl::at (context.get_replies ().reply_, z));
                reply_.back ().mark_insert (); }
            res = true; } }
    mmax = reply_.size ();
    for (::std::size_t z = 0; z < mmax; ++z)
    {   if (reply_.at (z).is_unknown ())
        {   res = true;
            reply_.at (z).mark_delete (); } }
    if (context.tell (es_detail)) report ("post update");
    return res; }

 bool replies::enact (nitpick& nits, const html_version& v, const lingo& lang) // not efficient for any real quantities
{   bool res = false;
    if (context.tell (es_detail)) report ("enact");
    const ::std::size_t mmax = reply_.size ();
    for (::std::size_t z = 0; z < mmax; ++z)
        if (! reply_.at (z).enact (nits, v, lang))
        {  if (reply_.at (z).is_deleted ())
                reply_.at (z).mark_unchanged (); }
        else res = true;
    if (res)
    {   vreply_t reply;
        for (::std::size_t x = 0; x < mmax; ++x)
            if (! reply_.at (x).is_deleted ())
                reply.push_back (reply_.at (x));
        reply.shrink_to_fit ();
        reply_.swap (reply); }
    return res; }

bool replies::process (nitpick& nits, const html_version& v, const lingo& lang)
{   if (! context.notify ()) return true;
    if (context.persisted ().empty ()) return true;
    replies persisted;
    if (! context.clear () && ! persisted.read (context.persisted ())) return false;
    if (! persisted.update_records (nits)) return true;
    persisted.enact (nits, v, lang); // whatever the webmentions, still update the file
    return persisted.write (); }

::std::string replies::report (const char* comment) const
{   ::std::ostringstream res;
    if (context.tell (es_info))
    {   if (comment != nullptr) res << comment << "\n";    // tell?
        for (::std::size_t s = 0; s < reply_.size (); ++s)
           res << reply_.at (s).report (s); }
    return res.str (); }

bool replies::load (nitpick& nits, const ::boost::json::object& jo)
{   PRESUME (reply_.empty (), __FILE__, __LINE__);
    if (jo.at (INPUT).is_array ())
    {   const ::boost::json::array& ja (jo.at (INPUT).as_array ());
        for (auto jh : ja)
            if (jh.is_object ())
                reply_.emplace_back (nits, jh.as_object ()); }
    return true; }

bool replies::save (nitpick& nits, ::boost::json::object& jo)
{   ::boost::json::array ja;
    for (auto h : reply_)
    {   ::boost::json::object jh;
        if (h.save (nits, jh))
            ja.emplace_back (jh); }
    if (! ja.empty ())
        jo.emplace (INPUT, ja);
    return true; }
#endif // HAS_WM
