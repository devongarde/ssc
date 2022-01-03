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

#include "main/standard.h"
#include "main/context.h"
#include "utility/filesystem.h"
#include "microformat/microformat_export.h"

microformat_export::microformat_export ()
    :  rel_ (EXPORT_RELS), url_ (EXPORT_URLS)
{   tree_.put (EXPORT_ITEMS, ::std::string ());
    tree_.put (EXPORT_RELS, ::std::string ());
    tree_.put (EXPORT_URLS, ::std::string ()); }

void microformat_export::item (const ::std::string& wo, const ::std::string& was)
{   initiated_ = true;
    tree_.put (::boost::property_tree::path (wo, EXPORT_SEP), was); }

void microformat_export::rel (const ::std::string& url, const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type)
{   initiated_ = true;
    for (auto rel : rels) rel_.insert (rel, url);
    url_.insert (url, url_export (hreflang, media, rels, text, title, type)); }

bool microformat_export::write (nitpick& nits, const ::boost::filesystem::path& file)
{   if (! context.mf_export ()) return true;
    ::boost::filesystem::path json (file);
    json += EXPORT_EXTENSION;
    if (empty ())
    {   try
        {   if (file_exists (json))
            {   if (delete_file (json)) nits.pick (nit_export_none, es_info, ec_microformat, "No microformats; deleted existing ", json);
                else nits.pick (nit_export_none, es_catastrophic, ec_microformat, "No microformats, but cannot deleted existing, probably incorrect, ", json); }
            else nits.pick (nit_export_none, es_comment, ec_microformat, "No microformats found in " , file); }
        catch (...) { }
        return true; }
    rel_.put (tree_);
    url_.put (tree_);
    ::boost::filesystem::path tmp (json);
    tmp += ".tmp";
    try
    {   ::boost::filesystem::ofstream f (tmp);
        if (f.bad ())
        {   nits.pick (nit_cannot_create_file, es_catastrophic, ec_microformat, "Cannot open temporary file ", tmp);
            return false; }
        bool happy = true;
        try
        {   ::boost::property_tree::write_json (f, tree_); }
        catch (...)
        {   nits.pick (nit_cannot_write, es_catastrophic, ec_microformat, "Cannot write microformats data to temporary file ", tmp);
            happy = false; }
        f.close ();
        if (happy)
        {   if (file_exists (json))
                if (! delete_file (json))
                {   nits.pick (nit_cannot_delete, es_catastrophic, ec_microformat, "Cannot delete existing file ", json);
                    return false; }
            rename_file (tmp, json);
            nits.pick (nit_write_wrote, es_info, ec_microformat, "Written microformats ", json);
            return true; } }
    catch (...) { }
    if (file_exists (tmp))
        if (! delete_file (tmp))
            nits.pick (nit_cannot_update, es_catastrophic, ec_microformat, "Cannot update ", json);
    return false; }
