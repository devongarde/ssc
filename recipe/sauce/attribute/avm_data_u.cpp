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

#include "main/standard.h"
#include "attribute/avm_data.h"

hav_t havt_u [] =
{   HTMLPLUS_ATTRIBUTES (elem_u),
    HTML3_CLID_ATTRIBUTES (elem_u),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_u),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ul [] =
{   { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_ul, a_align },
    { { HTML_3_0, HV_NOT32 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_clear },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_compact },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_dingbat },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_plain },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_md },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ul, a_src },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ul, a_type },
    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_ul, a_wrap },
    HTMLPLUS_ATTRIBUTES (elem_ul),
    HTML23_CLID_ATTRIBUTES (elem_ul),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ul),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_union [] =
{   MATH3_DEFS_ATTRIBUTES (elem_union),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_uplimit [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_uplimit),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_use [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_use, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_use, a_transform },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_use, a_transin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_use, a_transout },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_use, a_will_change },
    SVG_BOX_ATTRIBUTES(elem_use),
    SVG_CONDITIONAL_ATTRIBUTES (elem_use),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_use, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_use),
    SVG_HTML_ATTRIBUTES (elem_use),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_use),
    SVG_PRESENTATION_ATTRIBUTES (elem_use),
    SVG_XLINK_ATTRIBUTES (elem_use),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
