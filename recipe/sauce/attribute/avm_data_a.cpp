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

#include "main/standard.h"
#include "attribute/avm_data.h"

hav_t havt_a [] =
{   { { HTML_2_0, HV_RFC_2070 | HV_NOT3 }, { XHTML_2_0 }, elem_a, a_charset },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_a, a_command },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_coords },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_a, a_download },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_effect },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_a, a_externalresourcesrequired },
    { { HTML_TAGS }, { HTML_UNDEF }, elem_a, a_href },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_a, a_hreflang },
    { { HTML_3_0 }, { HTML_3_0 }, elem_a, a_md },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_a, a_media },
    { { HTML_1_0 }, { HTML_3_0 }, elem_a, a_methods },
    { { HTML_TAGS, HV_DEPRECATED30 | HV_DEPRECATEDX1 }, { XHTML_1_1 }, elem_a, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_onfocus },
    { { HTML_JAN06, HV_NOT50 | HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, elem_a, a_ping },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_print },
    { { HTML_JUL16 }, { HTML_UNDEF }, elem_a, a_referrerpolicy },
    { { HTML_1_0 }, { HTML_UNDEF }, elem_a, a_rel },
    { { HTML_1_0, HV_NOT50 | HV_W3 }, { HTML_5_3 }, elem_a, a_rev },
    { { HTML_2_0, 0, HE_MOZILLA | HE_NETSCAPE }, { HTML_3_2 }, elem_a, a_shape },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { XHTML_2_0 }, elem_a, a_shape },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_size },
    { { HTML_PLUS }, { HTML_PLUS }, elem_a, a_style },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_a, a_target },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_a, a_target },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_a, a_target },
    { { HTML_1_0, HV_NOT30 }, { HTML_3_2 }, elem_a, a_title },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_a, a_transform },
    { { HTML_TAGS, HV_NOT10 | HV_NOT2 | HV_NOT3 }, { HTML_UNDEF }, elem_a, a_type },
    { { HTML_1_0 }, { HTML_2_0 }, elem_a, a_urn },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, elem_a, a_xmlns_xlink },
    HTMLPLUS_ATTRIBUTES (elem_a),
    HTML23_CLID_ATTRIBUTES (elem_a),
    HTML4_FORM_ATTRIBUTES (elem_a),
    SVG_CONDITIONAL_ATTRIBUTES (elem_a),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_a, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_a),
    SVG_HTML_ATTRIBUTES (elem_a),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_a),
    SVG_PRESENTATION_ATTRIBUTES (elem_a),
    SVG_XLINK_ATTRIBUTES (elem_a),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_abbr [] =
{   { { XHTML_2_0 }, { XHTML_2_0 }, elem_abbr, a_full },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_abbr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_abbrev [] =
{   HTMLPLUS_ATTRIBUTES (elem_abbrev),
    HTML3_CLID_ATTRIBUTES (elem_abbrev),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_above [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_above, a_sym },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_abs [] =
{   MATH3_DEFS_ATTRIBUTES (elem_abs),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_abstract [] =
{   HTMLPLUS_ATTRIBUTES (elem_abstract),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_acronym [] =
{   HTMLPLUS_ATTRIBUTES (elem_acronym),
    HTML3_CLID_ATTRIBUTES (elem_acronym),
    COMMON_HTML4_ATTRIBUTES (elem_acronym),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_access [] =
{   { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_activate },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_key },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_media },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_order },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetid },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetrole },
    XHTML2_ATTRIBUTES (elem_access),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_action [] =
{   { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_declare },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_if },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_while },
    XHTML2_ATTRIBUTES (elem_action),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_added [] =
{   HTMLPLUS_ATTRIBUTES (elem_added),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_addeventlistener [] =
{   XHTML2_ATTRIBUTES (elem_addeventlistener),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_address [] =
{   { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_address, a_align },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_address, a_clear },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_address, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_address),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_address),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_altglyph [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyph, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyph, a_format },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyph, a_glyphref },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyph, a_rotate },
    SVG_CONDITIONAL_ATTRIBUTES (elem_altglyph),
    SVG_DXY_ATTRIBUTES (elem_altglyph),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_altglyph),
    SVG_HTML_ATTRIBUTES (elem_altglyph),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_altglyph),
    SVG_PRESENTATION_ATTRIBUTES (elem_altglyph),
    SVG_XLINK_ATTRIBUTES (elem_altglyph),
    SVG_XY_ATTRIBUTES (elem_altglyph),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_altglyphdef [] =
{   SVG_HTML_ATTRIBUTES (elem_altglyphdef),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_altglyphitem [] =
{   SVG_HTML_ATTRIBUTES (elem_altglyphitem),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_and [] =
{   MATH3_DEFS_ATTRIBUTES (elem_and),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_animate [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_animate, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animate, a_href },
    SVG_ANIMATION_ADD_ATTRIBUTES (elem_animate),
    SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES (elem_animate),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_animate),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animate),
    SVG_ANIMATION_VALUE_ATTRIBUTES (elem_animate),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animate),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_animate, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_animate),
    SVG_PRESENTATION_ATTRIBUTES_11_2 (elem_animate),
    SVG_XLINK_ATTRIBUTES_EX (elem_animate, HE_SVG_1_20),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_animatecolour [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatecolour, a_externalresourcesrequired },
    SVG_ANIMATION_ADD_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_VALUE_ATTRIBUTES (elem_animatecolour),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animatecolour),
    SVG_HTML_ATTRIBUTES (elem_animatecolour),
    SVG_PRESENTATION_ATTRIBUTES_11_2 (elem_animatecolour),
    SVG_XLINK_ATTRIBUTES_EX (elem_animatecolour, HE_SVG_11_12_20),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_animatemotion [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatemotion, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animatemotion, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, a_keypoints },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, a_origin },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, a_path },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatemotion, a_rotate },
    SVG_ANIMATION_ADD_ATTRIBUTES (elem_animatemotion),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_animatemotion),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animatemotion),
    SVG_ANIMATION_VALUE_ATTRIBUTES (elem_animatemotion),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animatemotion),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_animatemotion, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_animatemotion),
    SVG_XLINK_ATTRIBUTES_EX (elem_animatemotion, HE_SVG_1_20),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_animatetransform [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatetransform, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_animatetransform, a_href },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_animatetransform, a_type },
    SVG_ANIMATION_ADD_ATTRIBUTES (elem_animatetransform),
    SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES (elem_animatetransform),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_animatetransform),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animatetransform),
    SVG_ANIMATION_VALUE_ATTRIBUTES (elem_animatetransform),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animatetransform),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_animatetransform, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_animatetransform),
    SVG_PRESENTATION_ATTRIBUTES_11_2 (elem_animatetransform),
    SVG_XLINK_ATTRIBUTES_EX (elem_animatetransform, HE_SVG_1_20),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_animation [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_externalresourcesrequired },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_initialvisibility },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_preserveaspectratio },
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animation),
    SVG_BOX_ATTRIBUTES (elem_animation),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animation),
    SVG_HTML_ATTRIBUTES (elem_animation),
    SVG_PRESENTATION_ATTRIBUTES (elem_animation),
    SVG_SYNC_ATTRIBUTES (elem_animation),
    SVG_XLINK_ATTRIBUTES (elem_animation),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_annotation [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_cd },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_annotation, a_definitionurl },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, elem_annotation, a_encoding },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_name },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_annotation),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_annotation_xml [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_cd },
    { { HTML_MATH2, 0, 0, H2_MATH_2_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_definitionurl },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, elem_annotation_xml, a_encoding },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_name },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation_xml),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_annotation_xml),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_applet [] =
{   { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_align },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_alt },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_archive },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_class },
    { { HTML_3_2, HV_DEPRECATED4 | REQUIRED }, { XHTML_2_0 }, elem_applet, a_code },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_codebase },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_height },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_id },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_hspace },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_name },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_object },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_style },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_title },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_vspace },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_width },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_apply [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_apply),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_approx [] =
{   MATH3_DEFS_ATTRIBUTES (elem_approx),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccos [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccos),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccosh [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccosh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccot [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccoth [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccoth),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccsc [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccsc),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arccsch [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arccsch),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arcsec [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arcsec),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arcsech [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arcsech),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arcsin [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arcsin),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arcsinh [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arcsinh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arctan [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arctan),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arctanh [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arctanh),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_area [] =
{   { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_DEC06 }, elem_area, a_alt },
    { { HTML_JAN07, REQUIRED }, { HTML_JUN07 }, elem_area, a_alt },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_area, a_alt },
    { { HTML_2_0, HV_RFC_1980 | HV_NOT30 | REQUIRED }, { HTML_DEC06 }, elem_area, a_coords },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_area, a_coords },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_area, a_download },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_area, a_href },
    { { HTML_JAN07 }, { HTML_DEC15 }, elem_area, a_hreflang },
    { { HTML_5_1, HV_W3 }, { HTML_5_3 }, elem_area, a_hreflang },
    { { HTML_JAN07 }, { HTML_DEC12 }, elem_area, a_media },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_name },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { XHTML_2_0 }, elem_area, a_nohref },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_onfocus },
    { { HTML_JAN07, HV_NOT50 | HV_NOT51 | HV_NOT52 }, { HTML_UNDEF }, elem_area, a_ping },
    { { HTML_JAN17 }, { HTML_UNDEF }, elem_area, a_referrerpolicy },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_area, a_rel },
    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_UNDEF }, elem_area, a_shape },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_target },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_area, a_target },
    { { HTML_JAN07 }, { HTML_DEC15 }, elem_area, a_type },
    { { HTML_5_1, HV_W3 }, { HTML_5_3 }, elem_area, a_type },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_area, a_usemap },
    HTML4_FORM_ATTRIBUTES (elem_area),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_area),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_arg [] =
{   MATH3_DEFS_ATTRIBUTES (elem_arg),
    HTMLPLUS_ATTRIBUTES (elem_arg),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_array [] =
{   { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_array, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_coldef },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_labels },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_ldelim },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_rdelim },
    HTML3_CLID_ATTRIBUTES (elem_array),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_article [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_article, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_cite },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_article),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_aside [] =
{   { { HTML_JAN05 }, { HTML_DEC06 }, elem_aside, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_aside),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_audio [] =
{   { { HTML_JUL09 }, { HTML_JUN10 }, elem_audio, a_autobuffer },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_autoplay },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_controls },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_audio, a_crossorigin },
    { { HTML_JUL07, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_audio, a_currenttime },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_audio, a_disableremoteplayback },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_end },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, a_externalresourcesrequired },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_audio, a_loop },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopcount },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopend },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_loopstart },
    { { HTML_JUL11 }, { HTML_JUN16 }, elem_audio, a_mediagroup },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_audio, a_muted },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_audio, a_preload },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_audio, a_src },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_audio, a_start },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_audio, a_type },
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_audio),
    SVG_CONDITIONAL_ATTRIBUTES (elem_audio),
    SVG_HTML_ATTRIBUTES (elem_audio),
    SVG_PRESENTATION_ATTRIBUTES (elem_audio),
    SVG_SYNC_ATTRIBUTES (elem_audio),
    SVG_XLINK_ATTRIBUTES (elem_audio),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_au [] =
{   HTML3_CLID_ATTRIBUTES (elem_au),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
