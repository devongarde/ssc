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

#pragma once
#ifdef HAS_WM
#include "main/version.h"

#ifndef NO_JSONIC
#include "feedback/nitpick.h"
#include "parser/jsonic.h"
#include "webmention/hooks.h"
#include "webmention/irts.h"

class converse_t
{   ::boost::filesystem::path filename_;
    hooks in_;
    replies out_;
    vstr_t templates_;
    bool activity_ = false;
    void set_filename ();
    bool load_headers (nitpick& nits, const ::boost::json::object& jo, uint64_t& major, uint64_t& minor, uint64_t& release);
    bool prepare_headers (jsonic& js);
    ::std::string load_template (nitpick& nits, const ::std::string& supplied, const char* defname, const char* deftmp);
    void load_templates (nitpick& nits);
public:
    void reset ()
    {   filename_.clear (); }
    bool load (nitpick& nits);
    bool save (nitpick& nits);
    void note_reply (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
    {   out_.append (file, id, target, content); }
    replies& get_replies () noexcept { return out_; }
    void process_outgoing_webmentions (nitpick& nits, const html_version& v, const lingo& lang);
    void process_incoming_webmentions (nitpick& nits, const html_version& v, const vstr_t& mentions);
};
#endif // NO_JSONIC
#endif // HAS_WM
