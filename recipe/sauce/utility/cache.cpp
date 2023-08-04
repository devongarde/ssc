/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "main/context.h"
#include "utility/common.h"
#include "utility/filesystem.h"
#include "coop/lox.h"
#include "webpage/directory.h"
#include "url/url.h"
#include "utility/cache.h"
#include "icu/converter.h"

// #define CACHE_REPORT

struct cache_t
{   e_cache_state cs_ = cs_loading;
    time_t when_ = 0;
    bool borked_ = false;
    ::std::string content_; };

typedef ssc_map < ::std::string, cache_t > mc_t;
typedef ::std::unique_ptr < mc_t > mc_ptr;
mc_ptr mc;

void init_cache ()
{   mc = mc_ptr ( new mc_t ); }

bool current_cache (const ::std::string& name, ::std::string& content, bool& res, time_t& t, bool store, bool& borked)
{   res = true;
    {   lox l (lox_cache);
        auto i = mc -> find (name);
        if (i == mc -> cend ())
        {   if (store)
            {   cache_t c;
                c.cs_ = cs_loading;
                mc -> insert (mc_t::value_type (name, c)); }
            res = true;
            return false; }
        else switch (i -> second.cs_)
        {   case cs_empty : content.clear (); borked = i -> second.borked_; return true;
            case cs_content : content = i -> second.content_; t = i -> second.when_; borked = i -> second.borked_; return true;
            case cs_loading : break;
            default : res = false; return true; } }
    for (;;)
    {   ::std::this_thread::yield ();
        {   lox l (lox_cache);
            auto i = mc -> find (name);
            PRESUME (i != mc -> cend (), __FILE__, __LINE__);
            switch (i -> second.cs_)
            {   case cs_empty : content.clear (); borked = i -> second.borked_; return true;
                case cs_content : content = i -> second.content_; t = i -> second.when_; borked = i -> second.borked_; return true;
                case cs_loading : continue;
                default : res = false; return true; } } } }

void post_load (const ::std::string& name, const ::std::string& content, const time_t t, bool borked)
{   lox l (lox_cache);
    auto i = mc -> find (name);
    PRESUME ((i != mc -> cend ()), __FILE__, __LINE__);
    PRESUME ((i -> second.cs_ == cs_loading), __FILE__, __LINE__);
    i -> second.borked_ = borked;
    if (borked || content.empty ())
        i -> second.cs_ = cs_empty;
    else
    {   i -> second.content_ = content;
        i -> second.when_ = t;
        i -> second.cs_ = cs_content; } }

bool cached_file (nitpick& nits, const ::boost::filesystem::path& pt, ::std::string& content, bool& borked, bool store)
{   bool res = false;
    ::std::string name (pt.string ());
    time_t t;
    if (current_cache (name, content, res, t, store, borked))
    {   if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_cache, "Found file ", name, " (", content.size (), " bytes)");
#ifdef CACHE_REPORT
        ::std::cout << "found file " << name << " (" << content.size () << " bytes).\n";
#endif // CACHE_REPORT
        if (borked) nits.pick (nit_url_not_found, es_error, ec_cache, name, " was previously found to be borked");
        return res; }
    if (! res)
    {   nits.pick (nit_internal_cache_error, es_error, ec_cache, "Error when seeking file ", name);
        borked = true;
        return false; }
    if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_cache, "Loading file ", name);
#ifdef CACHE_REPORT
        ::std::cout << "loading file " << name << "\n";
#endif // CACHE_REPORT
    content = normalise_utf8 (nits, read_text_file (nits, pt, borked));
    t = get_last_write_time (pt);
    if (store) post_load (name, content, get_last_write_time (pt), borked);
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_cache, "Loaded file ", name, " (", content.size (), " bytes)");
#ifdef CACHE_REPORT
        ::std::cout << "loaded file " << name << " (" << content.size () << " bytes).\n";
#endif // CACHE_REPORT
    return true; } 

bool cached_url (nitpick& nits, const html_version& v, const directory* d, const url& u, ::std::string& content, ::std::time_t& when, bool& borked) 
{   VERIFY_NOT_NULL (d, __FILE__, __LINE__);
    bool res = false;
    ::std::string name (u.absolute ());
    if (current_cache (name, content, res, when, true, borked))
    {   if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_cache, "Found url ", name, " (", content.size (), " bytes)");
#ifdef CACHE_REPORT
        ::std::cout << "found url " << name << " (" << content.size () << " bytes).\n";
#endif // CACHE_REPORT
        if (borked) nits.pick (nit_url_not_found, es_error, ec_cache, name, " was previously found to be borked");
        return res; }
    if (! res)
    {   nits.pick (nit_internal_cache_error, es_error, ec_cache, "Error when seeking url ", name);
        borked = true;
        return false; }
    if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_cache, "Loading url ", name);
#ifdef CACHE_REPORT
        ::std::cout << "loading url " << name << "\n";
#endif // CACHE_REPORT
    if (! d -> verify_url (nits, v, u, false)) borked = true;
    else content = normalise_utf8 (nits, d -> load_url (nits, u, borked, &when));
    post_load (name, content, when, borked);
    if (! borked) if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_cache, "Loaded url ", name, " (", content.size (), " bytes)");
#ifdef CACHE_REPORT
    if (borked) ::std::cout << "failed to load url " << name << ".\n";
    else ::std::cout << "loaded url " << name << " (" << content.size () << " bytes).\n";
#endif // CACHE_REPORT
    return true; } 
