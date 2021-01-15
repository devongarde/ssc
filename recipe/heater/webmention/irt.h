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

#pragma once
#include "utility/common.h"

class context;

class reply
{   ::std::string file_, id_, server_, target_, content_, when_;
    e_activity activity_ = act_unknown;
    ::std::string clean (const ::std::string& s);
    bool find_server (nitpick& nits, const html_version& v);
    bool set_server (const ::std::string& link);
public:
    reply (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
        : file_ (file), id_ (id), target_ (target), content_ (clean (content)), activity_ (act_unknown)  { mark (); }
    reply (::boost::property_tree::ptree& tree, const ::std::string& container) : activity_ (act_unknown) { read (tree, container); }
    reply (const reply& r)
        :   file_ (r.file_), id_ (r.id_), server_ (r.server_), content_ (r.content_), when_ (r.when_), activity_ (r.activity_)
    { }
#ifndef NO_MOVE_CONSTRUCTOR
	reply(reply&&) = default;
#endif // VS
    void swap (reply& r) NOEXCEPT;
    bool invalid () const { return file_.empty (); }
    void mark ();
    bool operator == (const reply& rhs) const;
    bool close_but_no_banana (const reply& rhs) const;
    void mark_unchanged ();
    void mark_unknown () { activity_ = act_unknown; }
    void mark_update ();
    void mark_insert ();
    void mark_delete ();
    bool is_unknown () const { return activity_ == act_unknown; }
    bool is_deleted () const { return activity_ == act_delete; }
    void read (::boost::property_tree::ptree& tree, const ::std::string& container);
    void write (::boost::property_tree::ptree& tree, const ::std::string& container);
    ::std::string report (const char* verb) const;
    ::std::string report (const ::std::size_t n) const;
    bool enact (nitpick& nits, const html_version& v); };

typedef ::std::vector < reply > vreply_t;
const ::std::size_t no_reply = UINT_MAX;

class replies
{   vreply_t reply_;
    ::std::size_t size () const { return reply_.size (); }
    ::std::size_t find (const reply& r);
    ::std::size_t probably_match (const reply& r);
    bool read (const ::std::string filename);
    bool write ();
    bool update_records (nitpick& nits);
    bool enact (nitpick& nits, const html_version& v);
public:
    replies () {}
    void swap (replies& r) NOEXCEPT { reply_.swap (r.reply_); }
    void append (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content);
    ::std::string report (const char* comment = nullptr) const;
    bool process (nitpick& nits, const html_version& v); };
