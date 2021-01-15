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
#include "type/type_enum.h"
#include "element/element.h"

struct symbol_entry < e_svg_feature > svg_feature_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.svg", sf_org_w3c_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.svg.static", sf_org_w3c_svg_static },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.svg.animation", sf_org_w3c_svg_animation },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.svg.dynamic", sf_org_w3c_svg_dynamic },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.svg.all", sf_org_w3c_svg_all },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.dom.svg", sf_org_w3c_dom_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.dom.svg.static", sf_org_w3c_dom_svg_static },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.dom.svg.animation", sf_org_w3c_dom_svg_animation },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.dom.svg.dynamic", sf_org_w3c_dom_svg_dynamic },
    { { HTML_4_0 }, { HTML_UNDEF }, "org.w3c.dom.svg.all", sf_org_w3c_dom_svg_all },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVG", sf_svg },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVGDOM", sf_svgdom },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVG-static", sf_svgstatic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVGDOM-static", sf_svgdomstatic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVG-animation", sf_svganimation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVGDOM-animation", sf_svgdomanimation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVG-dynamic", sf_svgdynamic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Hyperlinking", sf_hyperlinking },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#SVGDOM-dynamic", sf_svgdomdynamic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#CoreAttribute", sf_coreattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Structure", sf_structure },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicStructure", sf_basicstructure },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#ContainerAttribute", sf_containerattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#ConditionalProcessing", sf_conditionalprocessing },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Image", sf_image },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Style", sf_style },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#ViewportAttribute", sf_viewportattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Shape", sf_shape },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Text", sf_text },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicText", sf_basictext },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#PaintAttribute", sf_paintattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicPaintAttribute", sf_basicpaintattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#OpacityAttribute", sf_opacityattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#GraphicsAttribute", sf_graphicsattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicGraphicsAttribute", sf_basicgraphicsattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Marker", sf_marker },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#ColorProfile", sf_colourprofile },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Gradient", sf_gradient },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Pattern", sf_pattern },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Clip", sf_clip },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicClip", sf_basicclip },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Mask", sf_mask },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Filter", sf_filter },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicFilter", sf_basicfilter },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#DocumentEventsAttribute", sf_documenteventsattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#GraphicalEventsAttribute", sf_graphicaleventsattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#AnimationEventsAttribute", sf_animationeventsattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Cursor", sf_cursor },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#XlinkAttribute", sf_xlinkattribute },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#ExternalResourcesRequired", sf_externalresourcesrequired },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#View", sf_view},
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Script", sf_script},
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Animation", sf_animation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Font", sf_font },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#BasicFont", sf_basicfont },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/TR/SVG11/feature#Scripting", sf_scripting } };

void svg_feature_init (nitpick& nits)
{   type_master < t_svg_feature > :: init (nits, svg_feature_symbol_table, sizeof (svg_feature_symbol_table) / sizeof (symbol_entry < e_svg_feature >)); }

bool invalid_id_result (nitpick& nits, const html_version& , const ::std::string& s, element* e)
{   assert (e != nullptr);
    element* anc = e -> get_ancestor (elem_filter);
    if (anc == nullptr)
    {   nits.pick (nit_bad_result, ed_svg_1_1, "15.7.2 Common attributes", es_error, ec_attribute, "result requires a parent filter element");
        return true; }
    anc -> add_result (s);
    return false; }
