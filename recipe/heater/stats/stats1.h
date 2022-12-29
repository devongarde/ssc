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

#pragma once
#include "type/enum.h"

template < class ENUM, ENUM max_enum, ENUM undefined_enum > class stats1
{   typedef ::std::vector < unsigned > counter_t;
    counter_t count_;
public:
    stats1 ()
    {   count_.resize (static_cast <::std::size_t> (max_enum + 1), 0); }
    static unsigned size () { return max_enum + 1; }
    void swap (stats1& s1) noexcept
    {   count_.swap (s1.count_); }
    unsigned at (const ENUM e) const
    {   return count_.at (e); }
    void mark (const ENUM e, const unsigned u = 1)
    {   if (e <= max_enum) count_.at (e) += u;
        else count_.at (undefined_enum) += u; }
    void accumulate (stats1 < ENUM, max_enum, undefined_enum >& o) const
    {   PRESUME (o.count_.size () >= count_.size (), __FILE__, __LINE__);
        for (unsigned i = 0; i < count_.size (); ++i)
            if (count_.at (i) > 0)
                o.mark (static_cast < ENUM > (i), count_.at (i)); } };

typedef stats1 < e_element, last_element_tag, elem_undefined > element_stats;
typedef stats1 < e_category, last_category, ec_undefined > category_stats;
typedef stats1 < e_severity, last_severity, es_undefined > severity_stats;
typedef stats1 < e_doc, last_doc, ed_mishmash > ref_stats;
typedef stats1 < e_schema_type, sty_illegal, sty_context > schema_stats;
typedef stats1 < e_httpequiv, he_error, he_context > httpequiv_stats;
typedef stats1 < e_metaname, mn_illegal, mn_context > metaname_stats;
typedef stats1 < e_css_property, ec_error, ec_context > css_property_stats;
typedef stats1 < e_css_statement, css_error, css_context > css_statement_stats;
