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
#include "utility/common.h"
#include "microdata/microdata_itemprop.h"

class microdata_export
{   ::boost::property_tree::ptree tree_;
    bool initiated_ = false;
    uid_t uid_ = 0;
    ::std::string rpt (const ::boost::property_tree::ptree& tree, const int dent) const;
public:
    void swap (microdata_export& m);
    void init (const ::std::string& name);
    bool empty () const noexcept { return (! initiated_); }
    bool write (nitpick& nits, const ::boost::filesystem::path& name);
    void add (const ::std::string& path, const itemprop_index itemprop, const ::std::string& value);
    void add (const ::std::string& path, const itemtype_index itemtype);
    void add (const ::std::string& path, const ::std::string& itemid);
    ::std::string append_path (const ::std::string& orig, const itemprop_index prop, const bool uid = false, const ::std::string& it = ::std::string ());
    ::std::string rpt () const { return rpt (tree_, 0); } };
