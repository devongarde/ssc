/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "elem.h"
#include "attr.h"
#include "html_version.h"

class stats;

class stats_t
{   stats* p_ = nullptr;
public:
    stats_t ();
    ~stats_t ();
    void mark (const e_element e);
    void mark (const html_version& v);
    void mark (const e_severity s);
    void mark (const e_category c);
    void mark (const e_doc d);
    void mark (const e_element f, const e_attribute m);
    void mark (const e_schema s);
    void mark (const e_schema s, const e_schema_property p);
    void mark_file (const unsigned size);
    uint64_t file_count () const;
    unsigned count (const e_element e) const;
    ::std::string report (const bool grand) const; };
