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

struct symbol_entry < html_version, e_svg_feature > svg_feature_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.svg", sf_org_w3c_svg },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.svg.static", sf_org_w3c_svg_static },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.svg.animation", sf_org_w3c_svg_animation },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.svg.dynamic", sf_org_w3c_svg_dynamic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.svg.all", sf_org_w3c_svg_all },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.dom.svg", sf_org_w3c_dom_svg },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.dom.svg.static", sf_org_w3c_dom_svg_static },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.dom.svg.animation", sf_org_w3c_dom_svg_animation },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.dom.svg.dynamic", sf_org_w3c_dom_svg_dynamic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "org.w3c.dom.svg.all", sf_org_w3c_dom_svg_all },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVG", sf_svg },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVGDOM", sf_svgdom },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVG-static", sf_svgstatic },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVGDOM-static", sf_svgdomstatic },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVG-animation", sf_svganimation },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVG-dynamic", sf_svgdynamic },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVGDOM-animation", sf_svgdomanimation },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Hyperlinking", sf_hyperlinking },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#SVGDOM-dynamic", sf_svgdomdynamic },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#CoreAttribute", sf_coreattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Structure", sf_structure },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicStructure", sf_basicstructure },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#ContainerAttribute", sf_containerattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#ConditionalProcessing", sf_conditionalprocessing },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Image", sf_image },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Style", sf_style },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#ViewportAttribute", sf_viewportattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Shape", sf_shape },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Text", sf_text },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicText", sf_basictext },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#PaintAttribute", sf_paintattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicPaintAttribute", sf_basicpaintattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#OpacityAttribute", sf_opacityattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#GraphicsAttribute", sf_graphicsattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicGraphicsAttribute", sf_basicgraphicsattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Marker", sf_marker },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#ColorProfile", sf_colourprofile },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Gradient", sf_gradient },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Pattern", sf_pattern },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Clip", sf_clip },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicClip", sf_basicclip },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Mask", sf_mask },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Filter", sf_filter },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicFilter", sf_basicfilter },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#DocumentEventsAttribute", sf_documenteventsattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#GraphicalEventsAttribute", sf_graphicaleventsattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#AnimationEventsAttribute", sf_animationeventsattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Cursor", sf_cursor },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#XlinkAttribute", sf_xlinkattribute },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#ExternalResourcesRequired", sf_externalresourcesrequired },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#View", sf_view},
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Script", sf_script},
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Animation", sf_animation },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Font", sf_font },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#BasicFont", sf_basicfont },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/TR/SVG11/feature#Scripting", sf_scripting },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Animation", sf_animation2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Audio", sf_audio2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#ComposedVideo", sf_composedvideo2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#ConditionalProcessing", sf_conditionalprocessing2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#ConditionalProcessingAttribute", sf_conditionalprocessingattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#CoreAttribute", sf_coreattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Discard", sf_discard2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#EditableTextAttribute", sf_editabletextattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Extensibility", sf_extensibility2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#ExternalResourcesRequired", sf_externalresourcesrequired2, },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Font", sf_font2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Gradient", sf_gradient2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#GraphicsAttribute", sf_graphicsattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Handler", sf_handler2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Hyperlinking", sf_hyperlinking2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Image", sf_image2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Listener", sf_listener2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#MediaAttribute", sf_mediaattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#NavigationAttribute", sf_navigationattribute },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#OpacityAttribute", sf_opacityattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#PaintAttribute", sf_paintattribute2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Prefetch", sf_prefetch2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Scripting", sf_scripting2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Shape", sf_shape2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SolidColor", sf_solidcolour2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Structure", sf_structure2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SVG-all", sf_svgall },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SVG-animated", sf_svganimated },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SVG-interactive", sf_svginteractive },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SVG-static", sf_svgstatic2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#SVG-static-DOM", sf_svgstaticdom },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Text", sf_text2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#TextFlow", sf_textflow2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#TimedAnimation", sf_timedanimation2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#TransformedVideo", sf_transformedvideo2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#Video", sf_video2 },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/feature/1.2/#XlinkAttribute", sf_xlinkattribute2 } };

void svg_feature_init (nitpick& nits)
{   type_master < t_svg_feature > :: init (nits, svg_feature_symbol_table, sizeof (svg_feature_symbol_table) / sizeof (symbol_entry < html_version, e_svg_feature >)); }

bool invalid_id_result (nitpick& nits, const html_version& , const ::std::string& s, element* e)
{   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
    element* anc = e -> get_ancestor (elem_filter);
    if (anc == nullptr)
    {   nits.pick (nit_bad_result, ed_svg_1_0, "15.7.2 Common attributes", es_error, ec_attribute, "result requires a parent filter element");
        return true; }
    VERIFY_NOT_NULL (anc, __FILE__, __LINE__);
    anc -> add_result (s);
    return false; }

void store_glyph_name (nitpick& nits, const html_version& , element* pe, const ::std::string name)
{   VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
    if (pe -> has_glyph (name))
        nits.pick (nit_glyphname, es_warning, ec_type, "Glyph name ", quote (name), " repeated");
    else pe -> add_glyph (name); }

bool check_glyph_names (nitpick& nits, const html_version& , element* pe, const vstr_t& vs)
{   bool res = true;
    VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
    for (auto s : vs)
        if (! pe -> has_glyph (s))
        {   nits.pick (nit_glyphname, es_warning, ec_type, "Glyph name ", quote (s), " not recognised");
            res = false; }
    return res; }
