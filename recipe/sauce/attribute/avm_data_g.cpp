/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

hav_t havt_g [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, a_class },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_g, a_externalresourcesrequired },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, a_focusable },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_g, a_focushighlight },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_g, a_transform },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_g, a_style },
    SVG_HTML_ATTRIBUTES (elem_g),
    SVG_CONDITIONAL_ATTRIBUTES (elem_g),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_g),
    SVG_PRESENTATION_ATTRIBUTES (elem_g),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_g),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_gauge [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_gauge),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_gcd [] =
{   MATH3_DEFS_ATTRIBUTES (elem_gcd),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_geq [] =
{   MATH3_DEFS_ATTRIBUTES (elem_geq),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_glyph [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_arabic_form },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_d },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_glyphname },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_horiz_adv_x },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_lang },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_orientation },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_glyph, a_unicode },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_adv_y },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_origin_x },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyph, a_vert_origin_y },
    SVG_HTML_ATTRIBUTES (elem_glyph),
    SVG_PRESENTATION_ATTRIBUTES (elem_glyph),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_glyphref [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyphref, a_format },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_glyphref, a_glyphref },
    SVG_DXY_ATTRIBUTES(elem_glyphref),
    SVG_HTML_ATTRIBUTES (elem_glyphref),
    SVG_PRESENTATION_ATTRIBUTES (elem_glyphref),
    SVG_XLINK_ATTRIBUTES(elem_glyphref),
    SVG_XY_ATTRIBUTES(elem_glyphref),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_grad [] =
{   MATH3_DEFS_ATTRIBUTES (elem_grad),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_gt [] =
{   MATH3_DEFS_ATTRIBUTES (elem_gt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
