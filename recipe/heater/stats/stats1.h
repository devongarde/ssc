/*
ssc (static site checker)
File Info
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
#include "main/enum.h"

template < class ENUM, ENUM max_enum, ENUM undefined_enum > class stats1
{   typedef ::std::vector < unsigned > counter_t;
    counter_t count_;
public:
    static unsigned size () noexcept { return max_enum + 1; }
    void swap (stats1 < ENUM, max_enum, undefined_enum >& s1) noexcept
    {   count_.swap (s1.count_); }
    void reset () noexcept
    {   stats1 < ENUM, max_enum, undefined_enum > tmp;
        swap (tmp); }
    unsigned at (const ENUM e) const
    {   if (count_.size () == 0) return 0;
        PRESUME (e < count_.size (), __FILE__, __LINE__);
        return count_.at (e); }
    void mark (const ENUM e, const unsigned u = 1)
    {   if (u == 0) return;
        if (count_.size () == 0)
            count_.resize (static_cast < ::std::size_t > (max_enum + 1), 0);
        if (e < count_.size ())
            count_.at (e) += u;
        else count_.at (undefined_enum) += u; }
    void accumulate (stats1 < ENUM, max_enum, undefined_enum >& o) const
    {   if (o.count_.size () == 0) o.count_ = count_;
        else for (unsigned i = 0; i < count_.size (); ++i)
            if (count_.at (i) > 0)
                o.mark (GSL_NARROW_CAST < ENUM > (i), count_.at (i)); } };

typedef stats1 < e_element, last_element_tag, elem_undefined > element_stats;
typedef stats1 < e_category, last_category, ec_undefined > category_stats;
typedef stats1 < e_severity, last_severity, es_undefined > severity_stats;
typedef stats1 < e_doc, last_doc, ed_mishmash > ref_stats;
typedef stats1 < e_ontology_type, ont_illegal, ont_context > ontology_stats;
typedef stats1 < e_httpequiv, he_error, he_context > httpequiv_stats;
typedef stats1 < e_metaname, mn_illegal, mn_context > metaname_stats;
typedef stats1 < e_css_property, ec_error, ec_context > css_property_stats;
typedef stats1 < e_css_statement, css_error, css_context > css_statement_stats;
