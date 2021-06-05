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

hav_t havt_abc [] =
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

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_abbr, a_full },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_abbr),

    HTMLPLUS_ATTRIBUTES (elem_abbrev),
    HTML3_CLID_ATTRIBUTES (elem_abbrev),

    { { HTML_3_0 }, { HTML_3_0 }, elem_above, a_sym },

    MATH3_DEFS_ATTRIBUTES (elem_abs),

    HTMLPLUS_ATTRIBUTES (elem_abstract),

    HTMLPLUS_ATTRIBUTES (elem_acronym),
    HTML3_CLID_ATTRIBUTES (elem_acronym),
    COMMON_HTML4_ATTRIBUTES (elem_acronym),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_activate },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_key },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_media },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_order },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetid },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_access, a_targetrole },
    XHTML2_ATTRIBUTES (elem_access),

    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_declare },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_if },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_action, a_while },
    XHTML2_ATTRIBUTES (elem_action),

    HTMLPLUS_ATTRIBUTES (elem_added),

    XHTML2_ATTRIBUTES (elem_addeventlistener),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_address, a_align },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_address, a_clear },
    { { HTML_3_2 }, { XHTML_2_0 }, elem_address, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_address),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_address),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_altglyph, a_externalresourcesrequired },
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

    SVG_HTML_ATTRIBUTES (elem_altglyphdef),

    SVG_HTML_ATTRIBUTES (elem_altglyphitem),

    MATH3_DEFS_ATTRIBUTES (elem_and),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_animate, a_externalresourcesrequired },
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

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatecolour, a_externalresourcesrequired },
    SVG_ANIMATION_ADD_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_ATTRIBUTE_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_EVENT_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animatecolour),
    SVG_ANIMATION_VALUE_ATTRIBUTES (elem_animatecolour),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animatecolour),
    SVG_HTML_ATTRIBUTES (elem_animatecolour),
    SVG_PRESENTATION_ATTRIBUTES_11_2 (elem_animatecolour),
    SVG_XLINK_ATTRIBUTES_EX (elem_animatecolour, HE_SVG_11_12_20),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatemotion, a_externalresourcesrequired },
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

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_animatetransform, a_externalresourcesrequired },
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

    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_externalresourcesrequired },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_initialvisibility },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_animation, a_preserveaspectratio },
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_animation),
    SVG_BOX_ATTRIBUTES (elem_animation),
    SVG_CONDITIONAL_ATTRIBUTES (elem_animation),
    SVG_HTML_ATTRIBUTES (elem_animation),
    SVG_PRESENTATION_ATTRIBUTES (elem_animation),
    SVG_SYNC_ATTRIBUTES (elem_animation),
    SVG_XLINK_ATTRIBUTES (elem_animation),

    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_cd },
    { { HTML_MATH2, 0, HE_MATH_2_3_4 }, { HTML_UNDEF }, elem_annotation, a_definitionurl },
    { { XHTML_1_0, 0, HE_MATH }, { HTML_UNDEF }, elem_annotation, a_encoding },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_name },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation),

    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_cd },
    { { HTML_MATH2, 0, HE_MATH_2_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_definitionurl },
    { { XHTML_1_0, 0, HE_MATH }, { HTML_UNDEF }, elem_annotation_xml, a_encoding },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_name },
    { { HTML_MATH3, 0, HE_MATH_3_4 }, { HTML_UNDEF }, elem_annotation_xml, a_src },
    MATH3_STANDARD_ATTRIBUTES (elem_annotation_xml),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_applet, a_align },
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

    MATH3_STANDARD_ATTRIBUTES (elem_apply),

    MATH3_DEFS_ATTRIBUTES (elem_approx),

    MATH3_DEFS_ATTRIBUTES (elem_arccos),

    MATH3_DEFS_ATTRIBUTES (elem_arccosh),

    MATH3_DEFS_ATTRIBUTES (elem_arccot),

    MATH3_DEFS_ATTRIBUTES (elem_arccoth),

    MATH3_DEFS_ATTRIBUTES (elem_arccsc),

    MATH3_DEFS_ATTRIBUTES (elem_arccsch),

    MATH3_DEFS_ATTRIBUTES (elem_arcsec),

    MATH3_DEFS_ATTRIBUTES (elem_arcsech),

    MATH3_DEFS_ATTRIBUTES (elem_arcsin),

    MATH3_DEFS_ATTRIBUTES (elem_arcsinh),

    MATH3_DEFS_ATTRIBUTES (elem_arctan),

    MATH3_DEFS_ATTRIBUTES (elem_arctanh),

    { { HTML_2_0, HV_NOT30 | HV_RFC_1980 }, { HTML_DEC06 }, elem_area, a_alt },
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

    MATH3_DEFS_ATTRIBUTES (elem_arg),
    HTMLPLUS_ATTRIBUTES (elem_arg),

    { { HTML_PLUS, HV_NOT2 }, { HTML_3_0 }, elem_array, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_coldef },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_labels },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_ldelim },
    { { HTML_3_0 }, { HTML_3_0 }, elem_array, a_rdelim },

    HTML3_CLID_ATTRIBUTES (elem_array),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_article, a_active },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_cite },
    { { HTML_JUL09 }, { HTML_DEC09 }, elem_article, a_pubdate },
    STANDARD_HTML5_ATTRIBUTES (elem_article),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_aside, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_aside),

    { { HTML_JUL09 }, { HTML_JUN10 }, elem_audio, a_autobuffer },
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

    HTML3_CLID_ATTRIBUTES (elem_au),

    HTMLPLUS_ATTRIBUTES (elem_b),
    HTML23_CLID_ATTRIBUTES (elem_b),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_b),

    { { HTML_JUL08 }, { HTML_DEC09 }, elem_bb, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_bb),

    HTML3_CLID_ATTRIBUTES (elem_banner),

    HTML3_CLID_ATTRIBUTES (elem_bar),

    { { HTML_2_0, REQUIRED }, { HTML_4_01 }, elem_base, a_href },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_base, a_href },
    { { HTML_3_0 }, { HTML_3_0 }, elem_base, a_id },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_base, a_target },
    STANDARD_HTML5_ATTRIBUTES (elem_base),

    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_colour },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_face },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_basefont, a_size },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_basefont, MAJOR_4_0, MINOR_4_0),

    { { HTML_JAN11 }, { HTML_UNDEF }, elem_bdi, a_dir },
    STANDARD_HTML5_ATTRIBUTES (elem_bdi),

    { { HTML_2_0, HV_RFC_2070 | REQUIRED }, { HTML_2_0 }, elem_bdo, a_dir },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_bdo, a_dir },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_bdo, a_lang },
    HTML2_CLID_ATTRIBUTES (elem_bdo),
    STANDARD_HTML5_ATTRIBUTES (elem_bdo),

    { { HTML_3_0 }, { HTML_3_0 }, elem_below, a_sym },

    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_balance },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_loop },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_src },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_bgsound, a_volume },

    HTML3_CLID_ATTRIBUTES (elem_big),
    COMMON_HTML4_ATTRIBUTES (elem_big),

    MATH3_STANDARD_ATTRIBUTES (elem_bind),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_blockquote, a_active },
    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_blockquote, a_align },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_blockquote, a_cite },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_blockquote, a_nowrap },
    HTML23_CLID_ATTRIBUTES (elem_blockquote),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_blockquote),

    XHTML2_ATTRIBUTES (elem_blockcode),

    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_alink },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_background },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_bgcolour },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { XHTML_2_0 }, elem_body, a_bottommargin },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { XHTML_2_0 }, elem_body, a_leftmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_link },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onafterprint },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onbeforeprint },
    { { HTML_JAN13 }, { HTML_JUN13 }, elem_body, a_onfullscreenchange },
    { { HTML_JAN13 }, { HTML_JUN13 }, elem_body, a_onfullscreenerror },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onhashchange },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_body, a_onlanguagechange },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_body, a_onload },
    { { HTML_JAN05 }, { HTML_JUN13 }, elem_body, a_onmessage },
    { { HTML_JAN05 }, { HTML_JUN13 }, elem_body, a_onmessage },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_body, a_onmessageerror },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onoffline },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_ononline },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_body, a_onpagehide },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_body, a_onpageshow },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onpopstate },
    { { HTML_JUL09 }, { HTML_DEC11 }, elem_body, a_onredo },
    { { HTML_JAN16 }, { HTML_UNDEF }, elem_body, a_onrejectionhandled },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_body, a_onstorage },
    { { HTML_JUL09 }, { HTML_DEC11 }, elem_body, a_onundo },
    { { HTML_JAN16 }, { HTML_UNDEF }, elem_body, a_onunhandledrejection },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_body, a_onunload },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { HTML_3_2 }, elem_body, a_rightmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_text },
    { { HTML_3_2, HV_DEPRECATED4, HE_CHROME }, { HTML_3_2 }, elem_body, a_topmargin },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_body, a_vlink },
    HTML23_CLID_ATTRIBUTES (elem_body),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_body),

    { { HTML_3_0 }, { HTML_3_0 }, elem_box, a_size },

    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_clear },
    { { HTML_3_0 }, { HTML_3_0 }, elem_bq, a_nowrap },
    HTML3_CLID_ATTRIBUTES (elem_bq),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_id },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_class },
    { { HTML_2_0, HV_RFC_1942 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_br, a_clear },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_br, a_title },
    { { HTML_4_0, HV_NOTPROD }, { HTML_UNDEF }, elem_br, a_style },
    HTMLPLUS_ATTRIBUTES (elem_br),
    HTML3_CLID_ATTRIBUTES (elem_br),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_br, HTML_2005, 0),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_br, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_br),

    { { HTML_3_0 }, { HTML_3_0 }, elem_bt, a_class },

    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_action },
    { { HTML_JAN20, 0, HE_MOZILLA }, { HTML_UNDEF }, elem_button, a_autocomplete },
    { { HTML_JAN09 }, { HTML_DEC19 }, elem_button, a_autofocus },
    { { HTML_JAN05 }, { HTML_DEC05 }, elem_button, a_command },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_datasrc },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_disabled },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_enctype },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_button, a_form },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formaction },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formenctype },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formmethod },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formnovalidate },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_button, a_formtarget },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_button, a_menu },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_method },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_name },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_novalidate },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_onblur },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_button, a_onfocus },
    { { HTML_JAN09 }, { HTML_JUN09 }, elem_button, a_target },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_type },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_button, a_value },
    HTML4_FORM_ATTRIBUTES (elem_button),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_button),

    MATH3_STANDARD_ATTRIBUTES (elem_bvar),

    HTMLPLUS_ATTRIBUTES (elem_byline),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_calendar, a_active },
    STANDARD_HTML5_ATTRIBUTES (elem_calendar),

    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_height },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_canvas, a_width },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_canvas),
    SVG_HTML_ATTRIBUTES (elem_canvas),

    { { HTML_2_0, HV_DEPRECATED4 | HV_RFC_1942 }, { XHTML_2_0 }, elem_caption, a_align },
    { { HTML_3_2 }, { HTML_3_2 }, elem_caption, a_valign },
    HTMLPLUS_ATTRIBUTES (elem_caption),
    HTML23_CLID_ATTRIBUTES (elem_caption),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_caption),

    { { HTML_JAN05 }, { HTML_DEC06 }, elem_card, a_active },
    MATH3_DEFS_ATTRIBUTES (elem_card),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_card),

    MATH3_DEFS_ATTRIBUTES (elem_cartesianproduct),

    MATH3_STANDARD_ATTRIBUTES (elem_cbytes),

    MATH3_DEFS_ATTRIBUTES (elem_ceiling),

    MATH3_STANDARD_ATTRIBUTES (elem_cerror),

    { { HTML_PLUS }, { HTML_PLUS }, elem_changed, a_idref },
    HTMLPLUS_ATTRIBUTES (elem_changed),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_ci, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_ci),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_circle, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, a_pathlength },
    { { HTML_SVG10, 0, HE_SVG | REQUIRED }, { HTML_UNDEF }, elem_circle, a_r },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_circle, a_transform },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_circle, a_will_change },
    SVG_CONDITIONAL_ATTRIBUTES (elem_circle),
    SVG_CXY_ATTRIBUTES (elem_circle),
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_circle, HE_SVG_2),
    SVG_GRAPHICAL_EVENT_ATTRIBUTES (elem_circle),
    SVG_HTML_ATTRIBUTES (elem_circle),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_circle),
    SVG_PRESENTATION_ATTRIBUTES (elem_circle),

    HTMLPLUS_ATTRIBUTES (elem_cite),
    HTML23_CLID_ATTRIBUTES (elem_cite),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_cite),

    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_clippathunits },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_clippath, a_transform },
    SVG_CONDITIONAL_ATTRIBUTES (elem_clippath),
    SVG_HTML_ATTRIBUTES (elem_clippath),
    SVG_LANGSPACE_ATTRIBUTES_10 (elem_clippath),
    SVG_PRESENTATION_ATTRIBUTES (elem_clippath),

    HTMLPLUS_ATTRIBUTES (elem_cmd),

    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_base },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_cn, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_cn),

    HTMLPLUS_ATTRIBUTES (elem_code),
    HTML23_CLID_ATTRIBUTES (elem_code),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_code),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_col, a_align },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3, HE_IE }, { XHTML_2_0 }, elem_col, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_char },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_col, a_span },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_valign },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { XHTML_2_0 }, elem_col, a_width },
    HTML2_CLID_ATTRIBUTES (elem_col),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_col),

    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 | HV_DEPRECATED4 }, { XHTML_2_0 }, elem_colgroup, a_align },
    { { HTML_2_0, HV_NOT3, HE_IE }, { HTML_2_0 }, elem_colgroup, a_bgcolour },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_char },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_char },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_4_0, 0, HE_IE }, { XHTML_2_0 }, elem_colgroup, a_charoff },
    { { HTML_2_0, HV_RFC_1942 | HV_NOT3 }, { HTML_UNDEF }, elem_colgroup, a_span },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_valign },
    { { HTML_2_0, HV_RFC_1942 }, { HTML_2_0 }, elem_colgroup, a_width },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_colgroup, a_width },
    HTML2_CLID_ATTRIBUTES (elem_colgroup),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_colgroup),

    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_local },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_name },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_colour_profile, a_rendering_in_tents },
    SVG_HTML_ATTRIBUTES (elem_colour_profile),
    SVG_XLINK_ATTRIBUTES (elem_colour_profile),

    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_checked },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_command },
    { { HTML_JAN05 }, { HTML_JUN09 }, elem_command, a_default },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_disabled },
    { { HTML_JAN05 }, { HTML_DEC08 }, elem_command, a_hidden },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_icon },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_label },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_radiogroup },
    { { HTML_JAN05 }, { HTML_DEC12 }, elem_command, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_command),

    STANDARD_HTML5_ATTRIBUTES (elem_commandset),

    MATH3_DEFS_ATTRIBUTES (elem_complexes),

    MATH3_DEFS_ATTRIBUTES (elem_compose),

    MATH3_STANDARD_ATTRIBUTES (elem_condition),

    { { HTML_2_0 }, { HTML_4_01 }, elem_comment, a_data },
    HTML4_STANDARD_TSL_ATTRIBUTES (elem_comment, MAJOR_4_0, MINOR_4_0),

    MATH3_DEFS_ATTRIBUTES (elem_conjugate),

    { { HTML_JAN05 }, { HTML_UNDEF }, elem_content, a_select },
    STANDARD_HTML5_ATTRIBUTES (elem_content),

    MATH3_DEFS_ATTRIBUTES (elem_cos),

    MATH3_DEFS_ATTRIBUTES (elem_cosh),

    MATH3_DEFS_ATTRIBUTES (elem_cot),

    MATH3_DEFS_ATTRIBUTES (elem_coth),

    HTML3_CLID_ATTRIBUTES (elem_credit),

    MATH3_DEFS_ATTRIBUTES (elem_cs),

    MATH3_DEFS_ATTRIBUTES (elem_csc),

    MATH3_DEFS_ATTRIBUTES (elem_csch),

    { { HTML_5_2 }, { HTML_UNDEF }, elem_csymbol, a_cd },
    { { XHTML_1_0 }, { HTML_UNDEF }, elem_csymbol, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_csymbol),

    MATH3_DEFS_ATTRIBUTES (elem_curl),

    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_cursor, a_externalresourcesrequired },
    SVG_CONDITIONAL_ATTRIBUTES (elem_cursor),
    SVG_HTML_ATTRIBUTES (elem_cursor),
    SVG_XLINK_ATTRIBUTES (elem_cursor),
    SVG_XY_ATTRIBUTES (elem_cursor),

    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_disabled },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_form },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_name },
    { { HTML_JUL19 }, { HTML_UNDEF }, elem_custom, a_readonly },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_custom),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
