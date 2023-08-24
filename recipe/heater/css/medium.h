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

#pragma once
#include "css/typed_property.h"
#include "css/arguments.h"

struct media_token
{   e_media m_;
    ::std::string s_;
    media_token (const e_media m, const ::std::string& s = ::std::string ()) : m_ (m), s_ (s) { } };

typedef ::std::vector < media_token > vm_t;

class medium_t
{   typedef enum { me_id, me_after_id, me_val, me_prop, me_after_prop, me_after_val, me_number, me_brac } media_expects;
    ::std::string shadow_;
    bool valid_ = true;
    vm_t vm_;
    void mtkn_report ();
    void note_value (const arguments& args, nitpick& nits, const ::std::string& s);
    void note_token (const arguments& args, nitpick& nits, const e_media m, const ::std::string& s = ::std::string ());
    bool value_expected (const e_media prop, e_type& t, bool& length, bool& ratio, bool& dpi);
    void check_feature_compatibility (nitpick& nits, const e_media media, const e_media prop);
    bool validate_version (const arguments& args, nitpick& nits, const e_media media, const vstr_t& commas, const int comma);
    bool token_flow (arguments args, nitpick& nits, const vstr_t& commas);
    void triple_pong (  const arguments& args, nitpick& nits, const int level, const bool zero, const int brackets,
                        const media_expects got, const media_expects expect, media_expects& expecting,
                        const char* wot, const e_media e, ::std::string& ss);
public:
    DEFAULT_CONSTRUCTORS (medium_t);
    medium_t (arguments& args, const int from, const int to)
    {   parse (args, from, to); }
    void parse (arguments& args, const int from, const int to);
    void validate (arguments& args);
    void accumulate (stats_t*  ) const { }
    void shadow (::std::stringstream& ss, arguments& args);
    ::std::string rpt () const; };

typedef ::std::vector < medium_t > vmdm_t;
