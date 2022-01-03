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
#include "microformat/microformat_export_rel.h"

#define EXPORT_ITEMS    "items"
#define EXPORT_PROPS    "properties"
#define EXPORT_RELS     "rels"
#define EXPORT_TYPES    "types"
#define EXPORT_URLS     "rel-urls"

#define EXPORT_ITEMPROP EXPORT_ITEMS EXPORT_STRSEP EXPORT_PROPS
#define EXPORT_ITEMTYPE EXPORT_ITEMS EXPORT_STRSEP EXPORT_TYPE

class microformat_export
{   ::boost::property_tree::ptree tree_;
    t_export < ::std::string > rel_;
    t_export < url_export > url_;
    bool initiated_ = false;
public:
    microformat_export ();
    void swap (microformat_export& m)
    {   tree_.swap (m.tree_);
        rel_.swap (m.rel_);
        url_.swap (m.url_);
        ::std::swap (initiated_, m.initiated_); }
    bool empty () const noexcept { return (! initiated_); }
    bool write (nitpick& nits, const ::boost::filesystem::path& name);
    void rel (const ::std::string& url, const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type);
    void item (const ::std::string& wo, const ::std::string& was); };
