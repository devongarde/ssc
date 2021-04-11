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

#include "main/standard.h"
#include "microdata/microdata_export.h"
#include "microdata/microdata_itemscope.h"
#include "main/context.h"

#define JSON_ITEMID     ".id"
#define JSON_ITEMPROP   ".prop"
#define JSON_ITEMTYPE   ".type"

void microdata_export::swap (microdata_export& m) NOEXCEPT
{   tree_.swap (m.tree_);
    ::std::swap (uid_, m.uid_);
    ::std::swap (initiated_, m.initiated_); }

void microdata_export::init (const ::std::string& name)
{   tree_.put (name, ::std::string ()); }

void microdata_export::add (const ::std::string& path, const itemprop_index itemprop, const ::std::string& value)
{   initiated_ = true;
    tree_.add (append_path (path + JSON_ITEMPROP, itemprop), value); }

void microdata_export::add (const ::std::string& path, const itemtype_index itemtype)
{   initiated_ = true;
    tree_.add (path + JSON_ITEMTYPE, itemtype_index_name (itemtype)); }

void microdata_export::add (const ::std::string& path, const ::std::string& itemid)
{   initiated_ = true;
    tree_.add (path + JSON_ITEMID, itemid); }

::std::string microdata_export::append_path (const ::std::string& orig, const itemprop_index prop, const bool uid, const ::std::string& it)
{   DBG_ASSERT (! orig.empty ());
    ::std::string res (orig);
    if (prop != null_itemprop)
    {   res += ".";
        res += itemprop_index_name (prop); }
    if (! it.empty ())
    {   res += ".";
        res += it; }
    if (uid)
    {   res += ".";
        res += ::boost::lexical_cast < ::std::string > ( ++uid_ ); }
    return res; }

bool microdata_export::write (nitpick& nits, const ::boost::filesystem::path& file)
{   if (! context.md_export ()) return true;
    ::boost::filesystem::path json (file);
    json += EXPORT_EXTENSION;
    if (empty ())
    {   try
        {   if (::boost::filesystem::exists (json))
            {   ::boost::filesystem::remove (json);
                 nits.pick (nit_export_none, es_info, ec_microformat, "No microdata; deleted existing ", json); }
            else nits.pick (nit_export_none, es_info, ec_microformat, "Not exporting " , file, ", it would be empty"); }
        catch (...) { }
        return true; }
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
        {   nits.pick (nit_cannot_write, es_catastrophic, ec_microformat, "Cannot write to temporary file ", tmp);
            happy = false; }
        f.close ();
        if (happy)
        {   if (::boost::filesystem::exists (json))
                if (! ::boost::filesystem::remove (json))
                {   nits.pick (nit_cannot_delete, es_catastrophic, ec_microformat, "Cannot delete existing file ", json);
                    return false; }
            ::boost::filesystem::rename (tmp, json);
            nits.pick (nit_write_wrote, es_info, ec_microformat, "Written microdata to ", json);
            return true; } }
    catch (...) { }
    try
    {   if (::boost::filesystem::exists (tmp))
            ::boost::filesystem::remove (tmp); }
    catch (...) { }
    nits.pick (nit_cannot_update, es_catastrophic, ec_microformat, "Cannot update ", json);
    return false; }
