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
#include "coop/lox.h"
#include "element/elem.h"
#include "css/distilled.h"

class css_global
{   mdst_t mdst_;
    dst_ptr inner_get (const ::std::string& s) const;
public:
    dst_ptr get_or_preinsert (const ::std::string& s);
    void release (dst_ptr cp);
    dst_ptr get (const ::std::string& s) const;
    css_ptr get_cp (const ::std::string& s) const;
    void accumulate (stats_t* s) const;
    void report_usage (::std::ostringstream& ss) const;
    void report_stragglers (::std::ostringstream& ss, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const; };

extern css_global global_css;
