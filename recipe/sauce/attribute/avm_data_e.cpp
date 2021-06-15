/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

hav_t havt_e [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_element),

    { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_elementdef, a_name },
    SVG_HTML_ATTRIBUTES (elem_elementdef),
    SVG_PRESENTATION_ATTRIBUTES (elem_elementdef),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_ellipse, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_ellipse, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_ellipse, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_ellipse),
    SVG_CXY_ATTRIBUTES (elem_ellipse),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_ellipse, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_ellipse),
    SVG_HTML_ATTRIBUTES (elem_ellipse),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_ellipse),
    SVG_PRESENTATION_ATTRIBUTES (elem_ellipse),
    SVG_RXY_ATTRIBUTES (elem_ellipse),

    HTMLPLUS_ATTRIBUTES (elem_em),
    HTML3_CLID_ATTRIBUTES (elem_em),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_em),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_height },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_src },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_type },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, a_width },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_align },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_hspace },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_name },
    { { HTML_JAN07, REJECT }, { HTML_UNDEF }, elem_embed, a_vspace },
    STANDARD_HTML5_ATTRIBUTES (elem_embed),

    MATH3_DEFS_ATTRIBUTES (elem_emptyset),

    MATH3_DEFS_ATTRIBUTES (elem_eq),

    MATH3_DEFS_ATTRIBUTES (elem_equivalent),

    MATH3_DEFS_ATTRIBUTES (elem_eulergamma),

    { { HTML_JAN05 }, { HTML_JUN08 }, elem_event_source, a_onevent },
    { { HTML_JAN05 }, { HTML_JUN08 }, elem_event_source, a_src },
    STANDARD_HTML5_ATTRIBUTES (elem_event_source),

    { { HTML_JUL08 }, { HTML_JUN09 }, elem_eventsource, a_src },
    STANDARD_HTML5_ATTRIBUTES (elem_eventsource),

    MATH3_DEFS_ATTRIBUTES (elem_exists),

    MATH3_DEFS_ATTRIBUTES (elem_exp),

    MATH3_DEFS_ATTRIBUTES (elem_exponentiale),

    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_extensiondefs, a_namespace },
    SVG_HTML_ATTRIBUTES (elem_extensiondefs),
    SVG_PRESENTATION_ATTRIBUTES (elem_extensiondefs),
    SVG_XLINK_ATTRIBUTES (elem_extensiondefs),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
