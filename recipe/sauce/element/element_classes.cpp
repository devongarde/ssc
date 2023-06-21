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
#include "main/context.h"
#include "element/elem.h"
#include "attribute/attr.h"
#include "element/element_classes.h"

#define WIDEHIGH    a_height, a_width

#define ARIA        a_aria_activedescendant, a_aria_atomic, a_aria_autocomplete, a_aria_busy, a_aria_checked, a_aria_colcount, a_aria_colindex, \
                    a_aria_current, a_aria_colspan, a_aria_controls, a_aria_describedby, a_aria_details,  a_aria_disabled, a_aria_dropeffect, \
                    a_aria_errormessage, a_aria_expanded, a_aria_flowto, a_aria_grabbed, a_aria_haspopup, a_aria_hidden, a_aria_invalid, \
                    a_aria_label, a_aria_labelledby, a_aria_level, a_aria_live, a_aria_modal, a_aria_multiline, a_aria_multiselectable, \
                    a_aria_orientation, a_aria_owns,  a_aria_placeholder, a_aria_posinset, a_aria_pressed, a_aria_readonly, a_aria_relevant, \
                    a_aria_required, a_aria_roledescription, a_aria_rowcount, a_aria_rowindex, a_aria_rowspan, a_aria_selected, a_aria_setsize, \
                    a_aria_sort, a_aria_valuemax, a_aria_valuemin, a_aria_valuenow, a_aria_valuetext

#define ON          a_onabort, a_onautocomplete, a_onautocompleteerror, a_onbeforeunload, a_oncancel, a_oncanplay, a_oncanplaythrough, \
                    a_onchange, a_onclose, a_oncontextmenu, a_oncuechange, a_ondrag, a_ondragend,  a_ondragenter, a_ondragexit, \
                    a_ondragleave, a_ondragover, a_ondragstart, a_ondrop, a_dropzone, a_ondurationchange, a_onemptied, a_onended, \
                    a_onerror, a_onformchange, a_onforminput, a_onhashchange, a_oninput, a_oninvalid, a_is, a_onload, a_onloadeddata, \
                    a_onloadedmetadata, a_onloadstart, a_onmessage, a_onmouseenter, a_onmouseleave, a_onmousewheel, a_onpause, a_onplay, \
                    a_onplaying, a_onprogress, a_onratechange, a_onreadystatechange, a_onreset, a_onresize, a_onscroll, a_onscrollend, \
                    a_onsought, a_onseeking, a_onselect, a_onshow, a_onstalled, a_onstorage, a_onsubmit, a_onunload

#define ALIGNCHAR   a_align, a_char, a_charoff, a_valign
#define BLUR        a_onfocus, a_onblur
#define DINGBAT     a_dingbat, a_md, a_seqnum, a_skip, a_align, a_clear, a_nowrap
#define KEYMOUSE    a_onclick, a_ondblclick, a_onkeydown, a_onkeypress, a_onkeyup, a_onmousedown, a_onmousemove, a_onmouseout, a_onmouseover, a_onmouseup
#define RESERVED4   a_datafld, a_dataformatas, a_datasrc
#define XHTML       a_role, a_xmlbase, a_xmlns, a_xmllang, a_xmlspace, RDFa

#define MATH1UNIQUE a_other
#define MATH1SHARED a_class, a_id, a_style
#define MATH1COMMON MATH1SHARED, MATH1UNIQUE
#define MATH1FONT   a_colour, a_fontfamily, a_fontsize, a_fontstyle, a_fontweight
#define MATHOPINFO  a_accent, a_fence, a_form, a_largeop, a_lspace, a_maxsize, a_minsize, a_movablelimits, a_rspace, a_separator, a_stretchy, a_symmetric
#define MATHSIZE    a_depth, WIDEHIGH
#define MATH1TABLE  a_align, a_alignmentscope, a_columnalign, a_columnlines, a_columnspacing, a_displaystyle, a_equalcolumns, a_equalrows, a_frame, a_framespacing, \
                    a_groupalign, a_rowalign, a_rowlines, a_rowspacing
#define MATH1DEFCOM a_definitionurl, MATH1COMMON

#define MATH2UNIQUE a_xref, MATH1UNIQUE
#define MATH2SHARED a_xlinkhref, a_xlinktype, a_xmlns
#define MATH2COMMON MATH2UNIQUE, MATH2SHARED, MATH1SHARED
#define MATH2FONT   a_mathsize, a_mathvariant, MATH1FONT
#define MATH2TABLE  a_columnwidth, a_minlabelspacing, a_side, a_width, MATH1TABLE
#define MATH2UNIDEF a_definitionurl
#define MATH2ENC    a_encoding
#define MATH2DEFCOM MATH2ENC, MATH2UNIDEF, MATH2COMMON

#define MATH3UNIQUE MATH2UNIQUE
#define MATH3SHARED a_href, MATH2SHARED
#define MATH3COMMON MATH3UNIQUE, MATH3SHARED, MATH1SHARED
#define MATH3FONT   a_dir, MATH2FONT
#define MATH3TABLE  MATH2TABLE
#define MATH3TOKEN  a_dir, a_mathsize, a_mathvariant
#define MATH3BREAK  a_linebreak, a_linebreakmultichar, a_linebreakstyle, a_lineleading
#define MATH3INDENT a_indentalign, a_indentalignfirst, a_indentalignlast, a_indentshift, a_indentshiftfirst, a_indentshiftlast, a_indenttarget
#define MATH3UNIDEF MATH2UNIDEF
#define MATH3DEFCOM MATH3UNIDEF, MATH2ENC, MATH3COMMON
#define MATH3UNIPR  a_mathbackground, a_mathcolour
#define MATH3PRES   MATH3UNIPR, MATH3COMMON

#define MATH4PRBASE a_arg, a_intent
#define MATH4PRES   MATH4PRBASE, MATH3PRES

#define MATH4CBASE  a_datawild, a_dir, a_mathbackground, a_mathcolour, a_mathsize, a_mathvariant, a_numberonce, a_onautocomplete, a_onautocompleteerror, \
                    a_onauxclick, a_onblur, a_oncancel, a_oncanplay, a_oncanplaythrough, a_onchange, a_onclose, a_oncontextmenu, a_oncopy, a_oncuechange, a_oncut, a_ondrag, \
                    a_ondragend, a_ondragenter, a_ondragleave, a_ondragover, a_ondragstart, a_ondrop, a_ondurationchange, a_onemptied, a_onended, a_onerror, a_onfocus, a_onformdata, \
                    a_oninput, a_oninvalid, a_onload, a_onloadeddata, a_onloadedmetadata, a_onloadstart, a_onmouseenter, a_onmouseleave, a_onpaste, a_onpause, a_onplay, a_onplaying, \
                    a_onprogress, a_onratechange, a_onreset, a_onresize, a_onscroll, a_onsecuritypolicyviolation, a_onseeking, a_onselect, a_onslotchange, a_onsort, a_onsought, \
                    a_onstalled, a_onsubmit, a_onsuspend, a_ontimeupdate, a_onwaiting, a_onwheel, a_scriptlevel, a_tabindex, KEYMOUSE

#define MATH4CCOMMON a_displaystyle, MATH4CBASE

#define MATH4CDEFCOM MATH3DEFCOM, MATH4CCOMMON
#define MATH4CPRES  MATH4PRBASE, MATH3COMMON, MATH4CCOMMON
#define MATH4CFONT  MATH1FONT, MATH4CPRES
#define MATH4CTABLE MATH3TABLE, MATH4PRES, MATH4CBASE
#define MATH4CSTYLE MATH1FONT, MATH4PRES, MATH4CBASE
#define MATH4CORE   MATH1SHARED, MATH4CCOMMON

#define RDFa        a_about, a_content, a_datatype, a_inlist, a_prefix, a_property, a_rel, a_resource, a_rev, a_src, a_typeof, a_vocab

#define SVG_ANADD   a_additive, a_accumulate
#define SVG_ANAT    a_attributename, a_attributetype
#define SVG_ANIM    a_onbegin, a_onend, a_onrepeat
#define SVG_ANTIME  a_begin, a_dur, a_end, a_min, a_max, a_restart, a_repeatcount, a_repeatdur
#define SVG_ANVAL   a_by, a_calcmode, a_from, a_keytimes, a_keysplines, a_to, a_values
#define SVG_COMP    a_amplitude, a_exponent, a_intercept, a_offset, a_slope, a_tablevalues, a_type
#define SVG_COND    a_max_unit_scale, a_min_unit_scale, a_requiredextensions, a_requiredfeatures, a_requiredfonts, a_requiredformats, \
                    a_systemlanguage
#define SVG_DOC     a_onzoom
#define SVG_DXDY    a_dx, a_dy
#define SVG_GR      a_onactivate, a_onfocusin, a_onfocusout
#define SVG_EVENT   SVG_ANIM, SVG_GR
#define SVG_PRES    a_alignment_baseline, a_audio_level, a_background_fill, a_baseline_shift, a_buffered_rendering, \
                    a_cache, a_clip, a_clip_path, a_clip_rule, a_clip_to_self, a_colour, a_colour_interpolation, \
                    a_colour_interpolation_filters, a_colour_profile, a_colour_rendering, a_comp_op, a_cursor, \
                    a_direction, a_display, a_display_align, a_dominant_baseline, a_enable_background, a_fill, \
                    a_fill_opacity, a_fill_rule, a_filter, a_flood_colour, a_flood_opacity, a_focushighlight, \
                    a_focusable, a_font, a_font_family, a_font_feature_settings, a_font_kerning, a_font_size, \
                    a_font_size_adjust, a_font_stretch, a_font_style, a_font_variant, a_font_variant_caps, \
                    a_font_variant_east_asian, a_font_variant_ligatures, a_font_variant_numeric, a_font_variant_position, \
                    a_font_weight, a_glyph_orientation_vertical, a_glyph_orientation_horizontal, a_image_rendering, \
                    a_isolation, a_kerning, a_knock_out, a_letter_spacing, a_lighting_colour, a_line_increment, a_marker, \
                    a_marker_end,  a_marker_mid, a_marker_start, a_mask, a_nav_down, a_nav_downleft, a_nav_downright, \
                    a_nav_left, a_nav_next, a_nav_prev, a_nav_right, a_nav_up, a_nav_upleft, a_nav_upright, a_opacity, \
                    a_overlay_host, a_overflow, a_page_orientation, a_paint_order, a_pointer_events, \
                    a_rendering_colour_space, a_shape_rendering, a_snap, a_solid_colour, a_solid_opacity, a_static, \
                    a_stop_colour, a_stop_opacity, a_stroke, a_stroke_dasharray, a_stroke_dashoffset, a_stroke_linecap, \
                    a_stroke_linejoin, a_stroke_miterlimit, a_stroke_opacity, a_stroke_width, a_text_anchor, a_text_align, \
                    a_text_align_last, a_text_decoration, a_text_decoration_colour, a_text_decoration_fill, \
                    a_text_decoration_line, a_text_decoration_stroke, a_text_decoration_style, a_text_indent, \
                    a_text_orientation, a_text_overflow, a_text_rendering, a_tooltip, a_transform, a_transform_box, \
                    a_transform_host, a_transform_origin, a_unicode_bidi, a_vector_effect, a_vertical_align, a_visibility, \
                    a_viewport_fill, a_viewport_fill_opacity, a_white_space, a_word_spacing, a_writing_mode
#define SVG_SYNC    a_syncbehaviour, a_syncmaster, a_synctolerance
#define SVG_XLINK   a_onloadprogress, a_onpostload, a_onpreload, a_xlinkactuate, a_xlinkarcrole, a_xlinkhref, a_xlinkrole, \
                    a_xlinkshow, a_xlinktitle, a_xlinktype
#define SVG_XY      a_x, a_y
#define SVG_BOX     SVG_XY, WIDEHIGH
#define SVG_FILTER  a_result, SVG_BOX

#define SVG_STRUCTURAL SVG_BOX, SVG_COND, SVG_DOC, SVG_GR, SVG_PRES

#define RDF_METADATA a_rdf_about, a_rdf_datatype, a_rdf_id, a_rdf_nodeid, a_rdf_parsetype, a_rdf_resource

#define METADATA    RDF_METADATA

#define LANGDIR     a_dir, a_lang
#define CLID        a_class, a_id
#define TIPSY       a_title, a_style
#define TIPSYCLID   TIPSY, CLID
#define LANGCLASS3  a_lang, CLID
#define LC3PLUS     a_index, LANGCLASS3
#define LANGCLASS   a_dir, LANGCLASS3
#define TIPSYLANG   TIPSY, LANGCLASS
#define TSL         TIPSYLANG, KEYMOUSE
#define HTMLPLUS    a_id, a_index, a_lang
#define TSLPLUS     a_index, TSL

#define COMMON4     TSL, XHTML, ARIA
#define X2_CORE     a_layout, a_xmlid
#define X2_HYPER    a_cite, a_href, a_hreflang, a_hrefmedia, a_hreftype, a_nextfocus, a_prevfocus, a_target, a_itstranslate
#define X2_SOLO     a_class, a_dir, a_id, a_style, a_title, XHTML
#define X2_EMBED    a_encoding, a_srctype
#define X2_MAP      a_usemap, a_ismap, a_shape, a_coords
#define X2_EVENT    a_event, a_observer, a_eventtarget, a_function, a_handler, a_phase, a_propagate, a_defaultaction
#define X2_COMMON   a_autofocus, a_datawild, a_edit, a_media, a_tabindex, X2_CORE, X2_HYPER, X2_EMBED, X2_MAP, X2_EVENT
#define X2          X2_COMMON, COMMON4
#define XHTML2      X2_COMMON, X2_SOLO
#define COMMON5     a_accesskey, a_contenteditable, a_contextmenu, a_draggable, a_hidden, a_inert, a_irrelevant, a_item, a_itemid, a_itemprop, \
                    a_itemref, a_itemscope, a_itemtype, a_numberonce, a_ref, a_registrationmark, a_spellcheck, a_subject, \
                    a_onsuspend, a_ontimeupdate, a_template, a_ontoggle, a_translate, a_onvolumechange, a_onwaiting, BLUR, X2, ON
#define COMMON50    a_generator_unable, COMMON5
#define COMMON51    a_oncopy, a_oncut, a_onpaste, a_onwheel, COMMON50
#define COMMON52    a_onauxclick, a_onloadend, COMMON51
#define COMMON53    COMMON52
#define LIVING_STANDARD    a_autocapitalise, a_enterkeyhint, a_exportparts, a_inputmode, a_onformdata, a_onsecuritypolicyviolation, \
                    a_onslotchange, a_part, a_popover, a_slot, COMMON53
#define X5          LIVING_STANDARD
#define LIVING_STANDARD_PLUS a_index, LIVING_STANDARD

CONSTEXPR ::std::size_t max_attrib = last_attribute + 1;

struct element_init_t
{   e_element tag_;
    e_attribute a_ [max_attrib]; };

element_init_t ei [] =
{   { elem_undefined, { a_unknown } },
    { elem_a, { a_charset, a_command, a_download, a_effect, a_externalresourcesrequired, a_md, a_methods, a_name, a_ping, a_print, a_referrerpolicy,
                a_size, a_type, a_urn, a_xmllink, a_xmlns_xlink, SVG_GR, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_abbr, { a_full, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_abbrev, { LC3PLUS, a_unknown } },
    { elem_above, { a_sym, LANGCLASS3, a_unknown } },
    { elem_abs, { MATH3DEFCOM, a_unknown } },
    { elem_abstract, { HTMLPLUS, a_unknown } },
    { elem_access, { a_activate, a_key, a_order, a_targetid, a_targetrole, METADATA, XHTML2, a_unknown } },
    { elem_acronym, { COMMON4, a_unknown } },
    { elem_action, { a_if, a_while, METADATA, XHTML2, a_unknown } },
    { elem_added, { HTMLPLUS, a_unknown } },
    { elem_addeventlistener, { METADATA, XHTML2, a_unknown } },
    { elem_address, { a_align, a_clear, a_nowrap, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_altglyph, { a_externalresourcesrequired, a_glyphref, a_format, a_rotate, SVG_GR, SVG_XLINK, SVG_DXDY, SVG_COND, SVG_PRES, SVG_XY, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_altglyphdef, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_altglyphitem, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_and, { MATH3DEFCOM, a_unknown } },
    { elem_animate, {   a_externalresourcesrequired, SVG_ANAT, SVG_ANTIME, SVG_ANIM, SVG_ANVAL, SVG_ANADD, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD,
                        a_unknown } },
    { elem_animatecolour, { a_externalresourcesrequired, SVG_ANAT, SVG_ANTIME, SVG_ANIM, SVG_ANVAL, SVG_ANADD, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_animatemotion, { a_externalresourcesrequired, a_fill, a_keypoints, a_origin, a_path, a_rotate, SVG_ANTIME, SVG_ANIM, SVG_ANVAL, SVG_ANADD, SVG_XLINK,
                            SVG_COND, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_animatetransform, {  a_externalresourcesrequired, a_type, SVG_ANAT, SVG_ANTIME, SVG_ANIM, SVG_ANVAL, SVG_ANADD, SVG_XLINK, SVG_COND,
                                SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_animation, { a_initialvisibility, SVG_BOX, SVG_COND, SVG_XLINK, SVG_ANTIME, SVG_PRES, SVG_SYNC, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_annotation, { a_cd, a_name, a_src, MATH4CDEFCOM, a_unknown } },
    { elem_annotation_xml, { a_cd, a_name, a_src, MATH4CDEFCOM, a_unknown } },
    { elem_applet, { a_align, a_alt, a_archive, a_code, a_codebase, a_hspace, a_name, a_object, a_vspace, WIDEHIGH, CLID, TIPSY, a_unknown } },
    { elem_approx, { MATH3DEFCOM, a_unknown } },
    { elem_apply, { MATH3COMMON, a_unknown } },
    { elem_arccos, { MATH3DEFCOM, a_unknown } },
    { elem_arcsin, { MATH3DEFCOM, a_unknown } },
    { elem_arctan, { MATH3DEFCOM, a_unknown } },
    { elem_arccosh, { MATH3DEFCOM, a_unknown } },
    { elem_arccot, { MATH3DEFCOM, a_unknown } },
    { elem_arccoth, { MATH3DEFCOM, a_unknown } },
    { elem_arccsc, { MATH3DEFCOM, a_unknown } },
    { elem_arccsch, { MATH3DEFCOM, a_unknown } },
    { elem_arcsinh, { MATH3DEFCOM, a_unknown } },
    { elem_arcsec, { MATH3DEFCOM, a_unknown } },
    { elem_arcsech, { MATH3DEFCOM, a_unknown } },
    { elem_arctanh, { MATH3DEFCOM, a_unknown } },
    { elem_area, { a_alt, a_download, a_nohref, a_name, a_ping, a_referrerpolicy, a_type, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_arg, { a_index, a_lang, MATH3DEFCOM, a_unknown } },
    { elem_array, { a_align, a_coldef, a_labels, a_ldelim, a_rdelim, a_unknown } },
    { elem_article, { a_active, a_pubdate, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_aside, { a_active, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_atop, { a_unknown } },
    { elem_au, { LANGCLASS3, a_unknown } },
    { elem_audio, { a_autobuffer, a_autoplay, a_controls, a_crossorigin, a_currenttime, a_duration, a_loop, a_loopcount, a_loopend, a_loopstart,
                    a_mediagroup, a_muted, a_preload, a_start, a_type, SVG_COND, SVG_XLINK, SVG_ANTIME, SVG_PRES, SVG_SYNC, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_b, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_bb, { a_type, METADATA, COMMON5, a_unknown } },
    { elem_banner, { LANGCLASS3, a_unknown } },
    { elem_bar, { LANGCLASS3, a_unknown } },
    { elem_base, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_basefont, { a_colour, a_size, a_face, COMMON4, a_unknown } },
    { elem_bdi, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_bdo, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_below, { a_sym, LANGCLASS3, a_unknown } },
    { elem_bgsound, { a_balance, a_loop, a_src, a_volume, a_unknown } },
    { elem_big, { COMMON4, a_unknown } },
    { elem_bind, { MATH3COMMON, a_unknown } },
    { elem_blink, { a_unknown } },
    { elem_blockquote, { a_active, a_align, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_blockcode, { METADATA, XHTML2, a_unknown } },
    { elem_body, {  a_alink, a_background, a_bgcolour, a_bottommargin, a_leftmargin, a_link, a_onafterprint, a_onbeforeprint,
                    a_onfullscreenchange, a_onfullscreenerror, a_onlanguagechange, a_onmessageerror, a_onoffline, a_ononline, a_onpagehide, a_onpageshow, a_onpopstate,
                    a_onredo, a_onrejectionhandled, a_onundo, a_onunhandledrejection, a_rightmargin, a_text, a_topmargin, a_vlink,
                    METADATA, LIVING_STANDARD, a_unknown } },
    { elem_box, { a_size, LANGCLASS3, a_unknown } },
    { elem_bq, { a_nowrap, a_clear, LANGCLASS3, a_unknown } },
    { elem_br, { a_clear, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_bt, { a_class, a_unknown } },
    { elem_button, {    a_action, a_autocomplete, a_command, a_disabled, a_enctype, a_form, a_formaction, a_formenctype, a_formmethod, a_formnovalidate, a_formtarget,
                        a_menu, a_method, a_name, a_novalidate, a_popovertarget, a_popovertargetaction, a_type, a_value, RESERVED4, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_bvar, { MATH3COMMON, a_unknown } },
    { elem_byline, { HTMLPLUS, a_unknown } },
    { elem_calendar, { a_active, METADATA, COMMON5, a_unknown } },
    { elem_canvas, { WIDEHIGH, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_caption, { a_align, a_valign, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_card, { a_active, MATH3UNIQUE, METADATA, COMMON5, a_unknown } },
    { elem_cartesianproduct, { MATH3DEFCOM, a_unknown } },
    { elem_cbytes, { MATH3COMMON, a_unknown } },
    { elem_cdata, { a_unknown } },
    { elem_ceiling, { MATH3DEFCOM, a_unknown } },
    { elem_centre, { a_unknown } },
    { elem_cerror, { MATH3COMMON, a_unknown } },
    { elem_changed, { a_id, a_idref, a_unknown } },
    { elem_choose, { a_unknown } },
    { elem_ci, { a_type, MATH3DEFCOM, a_unknown } },
    { elem_circle, { a_externalresourcesrequired, a_cx, a_cy, a_r, a_will_change, SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_cite, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_clippath, { a_clippathunits, a_externalresourcesrequired, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_cmd, { HTMLPLUS, a_unknown } },
    { elem_cn, { a_base, a_type, MATH3DEFCOM, a_unknown } },
    { elem_code, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_col, { a_bgcolour, a_span, a_width, ALIGNCHAR, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_colgroup, { a_bgcolour, a_span, a_width, ALIGNCHAR, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_colour_profile, { a_local, a_name, a_rendering_in_tents, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_command, { a_checked, a_command, a_default, a_disabled, a_icon, a_label, a_radiogroup, a_type, METADATA, COMMON5, a_unknown } },
    { elem_commandset, { METADATA, COMMON5, a_unknown } },
    { elem_comment, { a_data, TIPSYLANG, a_unknown } },
    { elem_complexes, { MATH3DEFCOM, a_unknown } },
    { elem_compose, { MATH3DEFCOM, a_unknown } },
    { elem_condition, { MATH3COMMON, a_unknown } },
    { elem_conjugate, { MATH3DEFCOM, a_unknown } },
    { elem_content, { a_select, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_cos, { MATH3DEFCOM, a_unknown } },
    { elem_cosh, { MATH3DEFCOM, a_unknown } },
    { elem_cot, { MATH3DEFCOM, a_unknown } },
    { elem_coth, { MATH3DEFCOM, a_unknown } },
    { elem_credit, { LANGCLASS3, a_unknown } },
    { elem_cs, { MATH3DEFCOM, a_unknown } },
    { elem_csc, { MATH3DEFCOM, a_unknown } },
    { elem_csch, { MATH3DEFCOM, a_unknown } },
    { elem_csymbol, { a_cd, a_type, MATH3DEFCOM, a_unknown } },
    { elem_curl, { MATH3DEFCOM, a_unknown } },
    { elem_cursor, { a_externalresourcesrequired, SVG_XY, SVG_XLINK, SVG_COND, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_custom, { a_disabled, a_form, a_name, a_readonly, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_data, { a_value, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_datagrid, { a_disabled, a_multiple, METADATA, COMMON5, a_unknown } },
    { elem_datalist, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_datatemplate, { METADATA, COMMON5, a_unknown } },
    { elem_dd, { a_compact, a_clear, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_ddot, { LANGCLASS3, a_unknown } },
    { elem_declare, { a_occurrence, a_nargs, a_scope, a_type, MATH3DEFCOM, a_unknown } },
    { elem_definition_src, { a_xmlns_xlink, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_defs, { SVG_STRUCTURAL, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_degree, { MATH3COMMON, a_unknown } },
    { elem_desc, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_del, { a_datetime, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_details, { a_open, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_determinant, { MATH3DEFCOM, a_unknown } },
    { elem_device, { a_type, METADATA, COMMON5, a_unknown } },
    { elem_devicecolour, { a_name, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_dfn, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_di, { METADATA, XHTML2, a_unknown } },
    { elem_dialogue, { a_open, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_diff, { MATH3DEFCOM, a_unknown } },
    { elem_dir, { a_align, a_clear, a_compact, a_dingbat, a_md, a_index, a_plain, a_wrap, COMMON4, a_unknown } },
    { elem_discard, { a_begin, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_dispatchevent, { a_bubbles, a_cancelable, METADATA, XHTML2, a_unknown } },
    { elem_div, { a_align, a_clear, a_nowrap, RESERVED4, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_divergence, { MATH3DEFCOM, a_unknown } },
    { elem_divide, { MATH3DEFCOM, a_unknown } },
    { elem_dl, { a_compact, a_clear, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_domain, { MATH3COMMON, a_unknown } },
    { elem_domainofapplication, { MATH3DEFCOM, a_unknown } },
    { elem_dot, { LANGCLASS3, a_unknown } },
    { elem_dt, { a_compact, a_clear, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_element, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_elementdef, { a_name, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_ellipse, { a_externalresourcesrequired, a_cx, a_cy, a_rx, a_ry, a_will_change, SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_em, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_embed, { a_type, a_align, a_hspace, a_name, a_vspace, WIDEHIGH, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_emptyset, { MATH3DEFCOM, a_unknown } },
    { elem_eq, { MATH3DEFCOM, a_unknown } },
    { elem_equivalent, { MATH3DEFCOM, a_unknown } },
    { elem_eulergamma, { MATH3DEFCOM, a_unknown } },
    { elem_event_source, { a_onevent, METADATA, COMMON5, a_unknown } },
    { elem_eventsource, { METADATA, COMMON5, a_unknown } },
    { elem_exists, { MATH3DEFCOM, a_unknown } },
    { elem_exp, { MATH3DEFCOM, a_unknown } },
    { elem_exponentiale, { MATH3DEFCOM, a_unknown } },
    { elem_extensiondefs, { a_namespace, SVG_PRES, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_factorial, { MATH3DEFCOM, a_unknown } },
    { elem_factorof, { MATH3DEFCOM, a_unknown } },
    { elem_false, { MATH3DEFCOM, a_unknown } },
    { elem_faux_asp, { a_unknown } },
    { elem_faux_cdata, { a_unknown } },
    { elem_faux_char, { a_unknown } },
    { elem_faux_code, { a_unknown } },
    { elem_faux_comment, { a_unknown } },
    { elem_faux_doctype, { a_html, a_math, a_svg, a_system, a_public, a_unknown } },
    { elem_faux_document, { a_unknown } },
    { elem_faux_php, { a_unknown } },
    { elem_faux_ssi, { a_unknown } },
    { elem_faux_stylesheet, { a_unknown } },
    { elem_faux_text, { a_unknown } },
    { elem_faux_xml, { a_encoding, a_version, a_standalone, a_unknown } },
    { elem_faux_whitespace, { a_unknown } },
    { elem_fe, { a_unknown } },
    { elem_feblend, { a_in, a_in2, a_mode, a_no_composite, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fecolourmatrix, { a_in, a_type, a_values, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fecomposite, {  a_in, a_in2, a_k1, a_k2, a_k3, a_k4, a_operator, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fecomponenttransfer, { a_in, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_feconvolvematrix, {  a_bias, a_divisor, a_edgemode,  a_in, a_kernelmatrix, a_kernelunitlength, a_order, a_preservealpha,
                                a_targetx, a_targety, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fediffuselighting, { a_diffuseconstant, a_in, a_kernelunitlength, a_surfacescale, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fedisplacementmap, { a_in, a_in2, a_scale, a_xchannelselector, a_ychannelselector, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fedistantlight, { a_azimuth, a_elevation, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fedropshadow, { a_in, a_stddeviation, SVG_DXDY, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_feflood, { SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fefunca, { SVG_COMP, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fefuncb, { SVG_COMP, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fefuncg, { SVG_COMP, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fefuncr, { SVG_COMP, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fegaussianblur, { a_edgemode, a_in, a_stddeviation, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_feimage, { a_crossorigin, a_externalresourcesrequired, a_preserveaspectratio, a_shadowinherit, SVG_XLINK, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_femerge, { SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_femergenode, { a_in, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_femorphology, {  a_in, a_operator, a_radius, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_feoffset, { a_in, SVG_DXDY, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fepointlight, { a_z, SVG_XY, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fespecularlighting, { a_in, a_kernelunitlength, a_specularconstant, a_specularexponent, a_surfacescale, SVG_FILTER, SVG_PRES,
                                METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fespotlight, { a_pointsatx, a_pointsaty, a_pointsatz, a_limitingconeangle, a_specularexponent, a_z, SVG_XY, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fetile, { a_in, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_feturbulence, { a_basefrequency, a_numoctaves, a_seed, a_stitchtiles, a_type, SVG_FILTER, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fieldset, { a_disabled, a_form, a_name, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fig, { a_align, a_clear, a_ismap, a_md, a_noflow, a_src, a_units, WIDEHIGH, LC3PLUS, a_unknown } },
    { elem_figure, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_figcaption, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_filter, { a_animate, a_dh, a_dw, a_externalresourcesrequired, a_fecolourmatrix, a_fecomposite, a_fegaussianblur, a_femorphology, a_fetile,
                     a_filterres,a_filterunits, a_primitiveunits, SVG_XLINK, SVG_PRES, SVG_BOX, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_floor, { MATH3DEFCOM, a_unknown } },
    { elem_flowdiv, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowimage, { a_height, a_width, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowline, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowpara, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowref, { SVG_PRES, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowregion, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowregionbreak, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowregionexclude, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowroot, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowspan, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_flowtref, { SVG_PRES, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_fn, { a_lang, MATH2DEFCOM, a_unknown } },
    { elem_font, {  a_externalresourcesrequired, a_face, a_horiz_adv_x, a_horiz_origin_x, a_horiz_origin_y, a_size, a_vert_adv_y, a_vert_origin_x,
                    a_vert_origin_y, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_font_face, {  a_accent_height, a_alphabetic, a_ascent, a_bbox, a_cap_height, a_descent, a_font_family, a_font_size, a_font_stretch, a_font_style,
                        a_font_variant, a_font_weight, a_hanging, a_ideographic, a_mathematical, a_overline_position, a_overline_thickness, a_panose_1,
                        a_slope, a_stemh, a_stemv, a_strikethrough_position, a_strikethrough_thickness, a_underline_position, a_underline_thickness,
                        a_unicode_range, a_units_per_em, a_v_alphabetic, a_v_hanging, a_v_ideographic, a_v_mathematical, a_widths, a_x_height, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_font_face_format, { a_string, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_font_face_name, { a_name, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_font_face_src, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_font_face_uri, { a_externalresourcesrequired, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_forall, { MATH3DEFCOM, a_unknown } },
    { elem_form, { a_accept, a_accept_charset, a_action, a_autocomplete, a_enctype, a_method, a_name, a_novalidate, a_script, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_foreignobject, { a_externalresourcesrequired, SVG_COND, SVG_BOX, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_footer, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_footnote, { HTMLPLUS , a_unknown } },
    { elem_frame, { a_dir, a_frameborder, a_longdesc, a_name, a_noresize, a_marginheight, a_marginwidth, a_scrolling, METADATA, XHTML, X2_COMMON, TIPSYCLID, a_unknown } },
    { elem_frameset, { a_cols, a_onload, a_onunload, a_rows, METADATA, XHTML, TIPSYCLID, a_unknown } },
    { elem_g, { a_externalresourcesrequired, SVG_STRUCTURAL, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_gauge, { METADATA, COMMON5, a_unknown } },
    { elem_gcd, { MATH3DEFCOM, a_unknown } },
    { elem_geq, { MATH3DEFCOM, a_unknown } },
    { elem_glyph, { a_arabic_form, a_d, a_glyphname, a_horiz_adv_x, a_orientation, a_unicode, a_vert_adv_y, a_vert_origin_x, a_vert_origin_y, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_glyphref, { a_format, a_glyphref, SVG_XY, SVG_DXDY, SVG_XLINK, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_grad, { MATH3DEFCOM, a_unknown } },
    { elem_gt, { MATH3DEFCOM, a_unknown } },
    { elem_h, { METADATA, XHTML2, a_unknown } },
    { elem_h1, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_h2, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_h3, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_h4, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_h5, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_h6, { DINGBAT, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_handler, { a_evevent, a_externalresourcesrequired, a_type, SVG_COND, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_hat, { LANGCLASS3, a_unknown } },
    { elem_head, { a_profile, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_header, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_hgroup, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_hint, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_hkern, { a_g1, a_g2, a_k, a_u1, a_u2, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_hp1, { a_unknown } },
    { elem_hp2, { a_unknown } },
    { elem_hp3, { a_unknown } },
    { elem_hp4, { a_unknown } },
    { elem_hp5, { a_unknown } },
    { elem_hp6, { a_unknown } },
    { elem_hr, { a_align, a_colour, a_noshade, a_size, a_md, a_width, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_html, { a_manifest, a_version, a_urn, a_xsischemaloc, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_htmlplus, { a_forms, a_version, a_unknown } },
    { elem_i, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_ident, { MATH3DEFCOM, a_unknown } },
    { elem_iframe, {    a_align, a_allow, a_allowfullscreen, a_allowpaymentrequest, a_allowusermedia, a_csp, a_frameborder, a_importance,
                        a_loading, a_longdesc, a_marginheight, a_marginwidth, a_mozbrowser, a_name, a_referrerpolicy, a_sandbox, a_scrolling,
                        a_seamless, a_srcdoc, WIDEHIGH, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_ilayer, {    a_above, a_background, a_below, a_bgcolour, a_class, a_clip, a_height, a_id, a_left, a_name, a_pagex, a_pagey,
                        a_src, a_style, a_top, a_visibility, a_zindex, a_unknown } },
    { elem_image, { a_align, a_crossorigin, a_externalresourcesrequired, a_onloadprogress, a_onpostload, a_onpreload, a_onzoom, a_preserveaspectratio, a_seethru,
                    a_shadowinherit, a_transin, a_transout, a_xlinkhref, a_will_change, MATH2UNIQUE, MATH2UNIDEF, SVG_GR, SVG_BOX, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_imaginary, { MATH3DEFCOM, a_unknown } },
    { elem_imaginaryi, { MATH3DEFCOM, a_unknown } },
    { elem_img, {   a_align, a_alt, a_border, a_crossorigin, a_decoding, a_hspace, a_importance, a_intrinsicsize, a_loading, a_longdesc,
                    a_md, a_referrerpolicy, a_seethru, a_sizes, a_srcset, a_units, a_vspace, WIDEHIGH, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_implies, { MATH3DEFCOM, a_unknown } },
    { elem_in, { MATH3DEFCOM, a_unknown } },
    { elem_infinity, { MATH3DEFCOM, a_unknown } },
    { elem_input, { a_accept, a_action, a_align, a_alt, a_autocorrect, a_autocomplete, a_capture, a_checked, a_command, a_dirname, a_disabled, a_enctype, a_error, a_form,
                    a_formaction, a_formenctype, a_formmethod, a_formnovalidate, a_formtarget, a_incremental, a_list, a_max, a_maxlength, a_md, a_method, a_min, a_minlength,
                    a_mozactionhint, a_multiple, a_name, a_novalidate, a_orient, a_pattern, a_placeholder, a_popovertarget, a_popovertargetaction, a_readonly, a_required,
                    a_results, a_size, a_step, a_type, a_value, a_webkitdirectory, WIDEHIGH, RESERVED4, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_ins, { a_datetime, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_int, { MATH3DEFCOM, a_unknown } },
    { elem_interval, { a_closure, MATH3COMMON, a_unknown } },
    { elem_integers, { MATH3DEFCOM, a_unknown } },
    { elem_inverse, { MATH3DEFCOM, a_unknown } },
    { elem_intersect, { MATH3DEFCOM, a_unknown } },
    { elem_isindex, { a_href, a_prompt, COMMON4, a_unknown } },
    { elem_item, { a_align, a_colspan, a_rowspan, a_unknown } },
    { elem_kbd, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_keygen, { a_challenge, a_disabled, a_form, a_keyparams, a_keytype, a_name, METADATA, COMMON51, a_unknown } },
    { elem_l, { a_align, METADATA, XHTML2, a_unknown } },
    { elem_label, { a_for, a_form, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_lambda, { MATH3COMMON, a_unknown } },
    { elem_lang, { LANGCLASS3, a_unknown } },
    { elem_laplacian, { MATH3DEFCOM, a_unknown } },
    { elem_layer, { a_above, a_background, a_below, a_bgcolour, a_class, a_clip, a_height, a_id, a_left, a_name, a_pagex, a_pagey, a_src, a_style,
                    a_top, a_visibility, a_zindex, a_unknown } },
    { elem_lcm, { MATH3DEFCOM, a_unknown } },
    { elem_left, { a_unknown } },
    { elem_legend, { a_align, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_leq, { MATH3DEFCOM, a_unknown } },
    { elem_lh, { LANGCLASS3, a_unknown } },
    { elem_li, { a_clear, a_compact, a_dingbat, a_md, a_skip, a_type, a_value, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_limit, { MATH3DEFCOM, a_unknown } },
    { elem_line, {  a_externalresourcesrequired, a_x1, a_x2, a_y1, a_y2, a_will_change,
                    SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_lineargradient, { a_externalresourcesrequired, a_gradienttransform, a_gradientunits, a_spreadmethod, a_x1, a_x2, a_y1, a_y2, SVG_XLINK, SVG_PRES,METADATA, LIVING_STANDARD, a_unknown } },
    { elem_link, {  a_as, a_blocking, a_charset, a_colour, a_crossorigin, a_disabled, a_fetchpriority, a_idref, a_imagesizes, a_imagesrcset, a_importance, a_integrity,
                    a_methods, a_ping, a_prefetch, a_referrerpolicy, a_scope, a_sizes, a_type, a_updateviacache, a_urn, a_workertype, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_listener, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_list, { a_order, MATH3COMMON, a_unknown } },
    { elem_listing, { COMMON4, a_unknown } },
    { elem_lit, { HTMLPLUS, a_unknown } },
    { elem_ln, { MATH3DEFCOM, a_unknown } },
    { elem_loc, { SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_log, { MATH3DEFCOM, a_unknown } },
    { elem_logbase, { MATH3COMMON, a_unknown } },
    { elem_lowlimit, { MATH3COMMON, a_unknown } },
    { elem_lt, { MATH3DEFCOM, a_unknown } },
    { elem_m, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_maction, { a_actiontype, a_selection, MATH4CPRES, a_unknown } },
    { elem_main, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_maligngroup, { a_groupalign, MATH4PRES, a_unknown } },
    { elem_malignmark, { a_edge, a_unknown } },
    { elem_map, { a_name, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_margin, { HTMLPLUS, a_unknown } },
    { elem_mark, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_marker, {    a_externalresourcesrequired, a_orient, a_markerheight, a_markerunits, a_markerwidth, a_preserveaspectratio, a_refx, a_refy, a_viewbox, SVG_PRES,
                        SVG_DOC, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_marquee, { a_behaviour, a_bgcolour, a_direction, a_hspace, a_loop, a_scrollamount, a_scrolldelay, a_truespeed, a_vspace, WIDEHIGH, a_unknown } },
    { elem_mask, { a_externalresourcesrequired, a_maskcontentunits, a_maskunits, SVG_COND, SVG_PRES, SVG_BOX, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_math, {  a_accentunder, a_altimg, a_altimg_height, a_altimg_width, a_altimg_valign, a_alttext, a_background, a_baseline,
                    a_bevelled, a_box, a_cdgroup, a_charalign, a_charspacing, a_close, a_columnspan, a_crossout, a_decimalpoint,
                    a_display, a_denomalign, a_depth, a_edge, a_infixlinebreakstyle, a_lang, a_leftoverhang, a_length,
                    a_linethickness, a_location, a_longdivstyle, a_lquote, a_macros, a_maxwidth, a_mediummathspace, a_mode,
                    a_mslinethickness, a_name, a_notation, a_numalign, a_open, a_overflow, a_position, a_rightoverhang, a_rowspan,
                    a_rquote, a_scriptlevel, a_scriptminsize, a_scriptsizemultiplier, a_selection, a_separators, a_shift,
                    a_stackalign, a_subscriptshift, a_superscriptshift, a_thickmathspace, a_thinmathspace, a_valign,
                    a_verythickmathspace, a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace,
                    a_style, a_type, MATH3BREAK, MATH3INDENT, MATH3SHARED, MATH3UNIQUE, WIDEHIGH, MATH4CPRES, a_unknown } },
    { elem_matrix, { MATH3COMMON, a_unknown } },
    { elem_matrixrow, { MATH3COMMON, a_unknown } },
    { elem_max, { MATH3DEFCOM, a_unknown } },
    { elem_mean, { MATH3DEFCOM, a_unknown } },
    { elem_median, { MATH3DEFCOM, a_unknown } },
    { elem_menclose, { a_notation, MATH4PRES, a_unknown } },
    { elem_menu, { a_align, a_autosubmit, a_clear, a_compact, a_dingbat, a_index, a_label, a_md, a_plain, a_type, a_wrap, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_menubar, { METADATA, COMMON5, a_unknown } },
    { elem_menuitem, { a_checked, a_default, a_disabled, a_icon, a_label, a_radiogroup, a_type, METADATA, COMMON51, a_unknown } },
    { elem_menulabel, { a_label, METADATA, COMMON5, a_unknown } },
    { elem_merror, { MATH4CPRES, a_unknown } },
    { elem_meta, { a_charset, a_httpequiv, a_name, a_scheme, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_metadata, { SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_meter, { a_form, a_high, a_low, a_max, a_min, a_optimum, a_value, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_mfenced, { a_close, a_open, a_separators, MATH4PRES, a_unknown } },
    { elem_mfrac, { a_bevelled, a_denomalign, a_linethickness, a_numalign, MATH4CPRES, a_unknown } },
    { elem_mglyph, { a_alt, a_fontfamily, a_height, a_index, a_mathvariant, a_mathsize, a_other, a_src, a_width, a_unknown, MATH4PRES } },
    { elem_mh, { a_action, a_hidden, a_method, HTMLPLUS, a_unknown } },
    { elem_mi, { MATH4CFONT, a_unknown } },
    { elem_min, { MATH3DEFCOM, a_unknown } },
    { elem_minus, { MATH3DEFCOM, a_unknown } },
    { elem_missingglyph, { a_d, a_horiz_adv_x, a_vert_adv_y, a_vert_origin_x, a_vert_origin_y, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_mlabeledtr, { a_columnalign, a_groupalign, a_rowalign, MATH4PRES, a_unknown } },
    { elem_mlongdiv, { a_align, a_charalign, a_charspacing, a_longdivstyle, a_stackalign, MATH4PRES, a_unknown } },
    { elem_mmultiscripts, { a_subscriptshift, a_superscriptshift, MATH4CPRES, a_unknown } },
    { elem_mn, { MATH4CFONT, a_unknown } },
    { elem_mo, { MATH3BREAK, MATH3INDENT, MATHOPINFO, MATH4CFONT, a_unknown } },
    { elem_mode, { MATH3DEFCOM, a_unknown } },
    { elem_moment, { MATH3DEFCOM, a_unknown } },
    { elem_momentabout, { MATH3DEFCOM, a_unknown } },
    { elem_mover, { a_accent, a_align, MATH4CPRES, a_unknown } },
    { elem_mpadded, { a_lspace, a_voffset, MATHSIZE, MATH4CPRES, a_unknown } },
    { elem_mpath, { a_externalresourcesrequired, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_mphantom, { MATH4CPRES, a_unknown } },
    { elem_mprescripts, { a_xmlns, MATH4CPRES, a_unknown } },
    { elem_mroot, { MATH4CPRES, a_unknown } },
    { elem_mrow, { MATH4CPRES, a_unknown } },
    { elem_ms, { a_lquote, a_rquote, MATH4CFONT, a_unknown } },
    { elem_mscarries, { a_crossout, a_location, a_scriptsizemultiplier, a_position, MATH4PRES, a_unknown } },
    { elem_mscarry, { a_crossout, a_location, MATH4PRES, a_unknown } },
    { elem_msgroup, { a_position, a_shift, MATH4PRES, a_unknown } },
    { elem_msline, { a_leftoverhang, a_length, a_mslinethickness, a_position, a_rightoverhang, MATH4PRES, a_unknown } },
    { elem_mspace, { a_linebreak, MATH3INDENT, MATHSIZE, MATH3TOKEN, MATH4CPRES, a_unknown } },
    { elem_msqrt, { MATH4CPRES, a_unknown } },
    { elem_msrow, { a_position, MATH4PRES, a_unknown } },
    { elem_mstack, { a_align, a_charalign, a_charspacing, a_stackalign, MATH4PRES, a_unknown } },
    { elem_mstyle, {    a_accentunder, a_background, a_bevelled, a_charalign, a_charspacing, a_close, a_columnspan, a_crossout,
                        a_decimalpoint, a_denomalign, a_depth, a_edge, a_height, a_infixlinebreakstyle, a_leftoverhang, a_length,
                        a_linethickness, a_location, a_longdivstyle, a_lquote, a_mediummathspace, a_mslinethickness, a_notation,
                        a_numalign, a_open, a_position, a_rightoverhang, a_rowspan, a_rquote, a_scriptlevel, a_scriptminsize,
                        a_scriptsizemultiplier, a_selection, a_separators, a_shift, a_stackalign, a_subscriptshift,
                        a_superscriptshift, a_thickmathspace, a_thinmathspace, a_valign, a_verythickmathspace,
                        a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace, MATH3BREAK, MATH3INDENT,
                        MATH3TABLE, MATHOPINFO, MATH4CSTYLE, a_unknown } },
    { elem_msub, { a_subscriptshift, MATH4CPRES, a_unknown } },
    { elem_msubsup, { a_subscriptshift, a_superscriptshift, MATH4CPRES, a_unknown } },
    { elem_msup, { a_superscriptshift, MATH4CPRES, a_unknown } },
    { elem_mtable, { MATH4CTABLE, a_unknown } },
    { elem_mtd, { a_columnalign, a_columnspan, a_groupalign, a_rowalign, a_rowspan, MATH4CPRES, a_unknown } },
    { elem_mtext, { MATH4CFONT, a_unknown } },
    { elem_mtr, { a_columnalign, a_groupalign, a_rowalign, MATH4CPRES, a_unknown } },
    { elem_multicol, { a_class, a_cols, a_gutter, a_id, a_style, a_width, a_unknown } },
    { elem_munder, { a_accentunder, a_align, MATH4CPRES, a_unknown } },
    { elem_munderover, { a_accent, a_accentunder, a_align, MATH4CPRES, a_unknown } },
    { elem_naturalnumbers, { MATH3DEFCOM, a_unknown } },
    { elem_nav, { a_active, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_navigation, { a_active, METADATA, COMMON5, a_unknown } },
    { elem_neq, { MATH3DEFCOM, a_unknown } },
    { elem_nest, { a_filter, a_mode, METADATA, COMMON5, a_unknown } },
    { elem_nextid, { a_n, a_unknown } },
    { elem_nl, { METADATA, XHTML2, a_unknown } },
    { elem_nobr, { a_unknown } },
    { elem_noembed, { a_unknown } },
    { elem_noframes, { COMMON4, a_unknown } },
    { elem_none, { a_xmlns, MATH4CORE, a_unknown } },
    { elem_noscript, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_not, { MATH3DEFCOM, a_unknown } },
    { elem_notanumber, { MATH3DEFCOM, a_unknown } },
    { elem_note, { a_clear, a_md, a_role, a_src, LC3PLUS, a_unknown } },
    { elem_notin, { MATH3DEFCOM, a_unknown } },
    { elem_notprsubset, { MATH3DEFCOM, a_unknown } },
    { elem_notsubset, { MATH3DEFCOM, a_unknown } },
    { elem_object, {    a_align, a_archive, a_border, a_classid, a_codebase, a_codetype, a_contentlength, a_data, a_declare, a_form,
                        a_hspace, a_name, a_standby, a_type, a_typemustmatch, a_vspace, WIDEHIGH, RESERVED4, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_of, { a_unknown } },
    { elem_ol, { a_align, a_clear, a_compact, a_continue, a_reversed, a_seqnum, a_start, a_type, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_online, { a_unknown } },
    { elem_optgroup, { a_disabled, a_label, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_option, { a_command, a_disabled, a_error, a_label, a_selected, a_value, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_or, { MATH3DEFCOM, a_unknown } },
    { elem_otherwise, { MATH3COMMON, a_unknown } },
    { elem_output, { a_for, a_form, a_name, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_outerproduct, { MATH3DEFCOM, a_unknown } },
    { elem_over, { a_unknown } },
    { elem_overlay, { a_src, a_md, a_x, a_y, a_imagemap, WIDEHIGH, LANGCLASS3, a_unknown } },
    { elem_p, { a_align, a_clear, a_dingbat, a_md, a_nowrap, a_seqnum, a_skip, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_page, { a_orientation, a_preserveaspectratio, a_transin, a_transout, a_viewbox, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_pageset, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_param, { a_name, a_type, a_value, a_valuetype, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_partialdiff, { MATH3DEFCOM, a_unknown } },
    { elem_path, {  a_d, a_externalresourcesrequired, a_flatness, a_nominal_length, a_pathlength, a_will_change,
                    SVG_GR, SVG_BOX, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_pattern, {   a_externalresourcesrequired, a_patterncontentunits, a_patterntransform, a_patternunits, a_preserveaspectratio, a_refx, a_refy, a_viewbox,
                        SVG_XLINK, SVG_COND, SVG_PRES, SVG_BOX, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_person, { LC3PLUS, a_unknown } },
    { elem_pi, { MATH3DEFCOM, a_unknown } },
    { elem_picture, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_piece, { MATH3COMMON, a_unknown } },
    { elem_piecewise, { MATH3COMMON, a_unknown } },
    { elem_plaintext, { LANGCLASS, a_unknown } },
    { elem_plus, { MATH3DEFCOM, a_unknown } },
    { elem_polygon, {   a_externalresourcesrequired, a_points, a_will_change,
                        SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_polyline, {  a_externalresourcesrequired, a_points, a_will_change,
                        SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_power, { MATH3DEFCOM, a_unknown } },
    { elem_pre, { a_clear, a_cols, a_width, a_wrap, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_prefetch, { a_bandwidth, a_mediacharacterencoding, a_mediacontentencodings, a_mediasize, a_mediatime, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_preventdefault, { METADATA, XHTML2, a_unknown } },
    { elem_primes, { MATH3DEFCOM, a_unknown } },
    { elem_printed, { a_unknown } },
    { elem_product, { MATH3DEFCOM, a_unknown } },
    { elem_progress, { a_form, a_max, a_value, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_prototype, { SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_prsubset, { MATH3DEFCOM, a_unknown } },
    { elem_q, { a_align, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_quote, { HTMLPLUS, a_unknown } },
    { elem_quotient, { MATH3DEFCOM, a_unknown } },
    { elem_radialgradient, { a_cx, a_cy, a_externalresourcesrequired, a_fr, a_fx, a_fy, a_gradienttransform, a_gradientunits, a_r, a_spreadmethod, SVG_XLINK, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_range, { a_from, a_until, a_class, a_id, a_unknown } },
    { elem_rationals, { MATH3DEFCOM, a_unknown } },
    { elem_rb, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rbc, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_1, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_2, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_3, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_4, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_5, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_6, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_7, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_8, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_9, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_about, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_abouteach, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_abouteachprefix, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_alt, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_bag, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_bagid, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_datatype, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_description, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_id, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_li, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_nodeid, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_parsetype, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_rdf, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_resource, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rdf_seq, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_real, { MATH3DEFCOM, a_unknown } },
    { elem_reals, { MATH3DEFCOM, a_unknown } },
    { elem_rect, { a_externalresourcesrequired, a_rx, a_ry, a_will_change, SVG_GR, SVG_COND, SVG_PRES, SVG_BOX, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_refcontent, { a_select, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_reln, { MATH2COMMON, a_unknown } },
    { elem_rem, { MATH3DEFCOM, a_unknown } },
    { elem_removed, { HTMLPLUS, a_unknown } },
    { elem_removeeventlistener, { METADATA, XHTML2, a_unknown } },
    { elem_render, { a_style, a_tag, a_unknown } },
    { elem_right, { a_unknown } },
    { elem_root, { a_lang, MATH3DEFCOM, a_unknown } },
    { elem_row, { a_unknown } },
    { elem_rp, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rt, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rtc, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_ruby, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_rule, { a_condition, a_mode, METADATA, COMMON5, a_unknown } },
    { elem_s, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_samp, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_sarcasm, { a_unknown } },
    { elem_scalarproduct, { MATH3DEFCOM, a_unknown } },
    { elem_script, {    a_async, a_blocking, a_charset, a_crossorigin, a_defer, a_externalresourcesrequired, a_implements, a_integrity, a_language, a_nomodule, a_referrerpolicy,
                        a_type, SVG_XLINK, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_sdev, { MATH3DEFCOM, a_unknown } },
    { elem_search, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_sec, { MATH3DEFCOM, a_unknown } },
    { elem_sech, { MATH3DEFCOM, a_unknown } },
    { elem_section, { a_active, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_select, {    a_align, a_autocomplete, a_disabled, a_error, a_form, a_md, a_multiple, a_name, a_required, a_several, a_size, a_units, WIDEHIGH, RESERVED4,
                        METADATA, LIVING_STANDARD, a_unknown } },
    { elem_selector, { MATH3DEFCOM, a_unknown } },
    { elem_semantics, { a_cd, a_name, a_src, MATH4CDEFCOM, a_unknown } },
    { elem_sep, { a_xmlns, a_unknown } },
    { elem_separator, { METADATA, XHTML2, a_unknown } },
    { elem_set, { a_externalresourcesrequired, a_to, a_type, MATH2UNIQUE, SVG_ANAT, SVG_ANTIME, SVG_ANIM, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_setdiff, { MATH3DEFCOM, a_unknown } },
    { elem_shadow, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_share, { a_src, MATH3COMMON, a_unknown } },
    { elem_sidebar, { a_active, METADATA, COMMON5, a_unknown } },
    { elem_sin, { MATH3DEFCOM, a_unknown } },
    { elem_sinh, { MATH3DEFCOM, a_unknown } },
    { elem_slot, { a_name, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_small, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_solidcolour, { SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_source, { a_height, a_sizes, a_srcset, a_type, a_width, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_spacer, { a_align, a_size, a_type, WIDEHIGH, a_unknown } },
    { elem_span, { a_align, RESERVED4, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_spot, { a_id, a_unknown } },
    { elem_sqrt, { LANGCLASS3, a_unknown } },
    { elem_standby, { MATH3DEFCOM, a_unknown } },
    { elem_stop, { a_offset, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_stoppropagation, { METADATA, XHTML2, a_unknown } },
    { elem_strike, { COMMON4, a_unknown } },
    { elem_strong, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_style, { a_blocking, a_disabled, a_notation, a_onzoom, a_scoped, a_type, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_sub, { a_align, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_subset, { MATH3DEFCOM , a_unknown } },
    { elem_sum, { MATH3DEFCOM, a_unknown } },
    { elem_summary, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_sup, { a_align, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_svg, {   a_allow_zoom_and_pan, a_baseprofile, a_contentscripttype, a_contentstyletype, a_externalresourcesrequired, a_onafterprint, a_onbeforeprint, a_onzoom,
                    a_playbackorder, a_preserveaspectratio, a_snapshottime, a_streamedcontents, a_syncbehaviourdefault, a_synctolerancedefault, a_timelinebegin,
                    a_version, a_viewbox, a_zoomandpan, SVG_BOX, SVG_COND, SVG_GR, SVG_PRES, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_switch, { a_externalresourcesrequired, a_onzoom, SVG_GR, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_symbol, { a_externalresourcesrequired, a_onzoom, a_preserveaspectratio, a_refx, a_refy, a_shadowinherit, a_viewbox, SVG_BOX, SVG_COND, SVG_GR, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_t, { a_datetime, METADATA, COMMON5, a_unknown } },
    { elem_tab, { a_align, a_at, a_dp, a_indent, a_to, LANGCLASS3, a_unknown } },
    { elem_tabbox, { METADATA, COMMON5, a_unknown } },
    { elem_table, { a_align, a_background, a_bgcolour, a_border, a_cellspacing, a_cellpadding, a_clear, a_cols, a_colspec, a_dp, a_frame, a_noflow, a_nowrap,
                    a_rules, a_sortable, a_summary, a_units, a_width, RESERVED4, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_tan, { MATH3DEFCOM, a_unknown } },
    { elem_tanh, { MATH3DEFCOM, a_unknown } },
    { elem_tbody, { a_bgcolour, a_rowgroup, ALIGNCHAR, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_tbreak, { SVG_COND, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_td, { a_axes, a_axis, a_background, a_bgcolour, a_cell, a_colspan, a_dp, a_headers, a_nowrap, a_rowspan, a_scope, WIDEHIGH, ALIGNCHAR, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_template, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_text, {  a_editable, a_externalresourcesrequired, a_hyphens, a_inline_size, a_lengthadjust, a_line_break, a_line_height, a_overflow_wrap, a_rotate,
                    a_shape_image_threshold, a_shape_inside, a_shape_margin, a_shape_padding, a_shape_subtract, a_text_justify, a_textlength, a_word_break, a_word_wrap, a_will_change,
                    SVG_GR, SVG_DXDY, SVG_COND, SVG_PRES, SVG_XY, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_tendsto, { a_type, MATH3DEFCOM, a_unknown } },
    { elem_textarea, {  a_align, a_autocomplete, a_cols, a_dirname, a_disabled, a_editable, a_error, a_form, a_maxlength, a_minlength, a_name, a_placeholder, a_readonly, a_required,
                        a_rotate, a_rows, a_wrap, SVG_BOX, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_textpath, { a_externalresourcesrequired, a_lengthadjust, a_method, a_path, a_side, a_spacing, a_startoffset, a_textlength, SVG_GR, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_tfoot, { a_bgcolour, a_rowgroup, ALIGNCHAR, RESERVED4, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_th, { a_axis, a_abbr, a_bgcolour, a_colspan, a_dp, a_headers, a_nowrap, a_rowspan, a_scope, a_sorted, WIDEHIGH, ALIGNCHAR, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_thead, { a_bgcolour, a_rowgroup, ALIGNCHAR, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_tilde, { LANGCLASS3, a_unknown } },
    { elem_time, { a_datetime, a_pubdate, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_times, { MATH3DEFCOM, a_unknown } },
    { elem_title, { a_systemlanguage, SVG_PRES, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_tr, { a_bgcolour, a_dp, a_nowrap, a_row, ALIGNCHAR, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_track, { a_default, a_kind, a_label, a_srclang, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_traitdef, { a_namespace, SVG_BOX, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_transition, { a_direction, a_dur, a_fadecolour, a_endprogress, a_startprogress, a_subtype, a_type, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_transformer, { a_type, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_transpose, { MATH3DEFCOM, a_unknown } },
    { elem_tref, { a_externalresourcesrequired, a_rotate, a_textlength, SVG_GR, SVG_XLINK, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_true, { MATH3DEFCOM, a_unknown } },
    { elem_tspan, { a_externalresourcesrequired, a_hyphens, a_lengthadjust, a_line_break, a_overflow_wrap, a_rotate, a_text_justify, a_textlength, a_word_break, a_word_wrap,
                    SVG_GR, SVG_DXDY, SVG_COND, SVG_PRES, SVG_XY, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_tt, { TSLPLUS, METADATA, XHTML, a_unknown } },
    { elem_u, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_ul, { a_align, a_clear, a_compact, a_plain, a_type, a_wrap, LIVING_STANDARD_PLUS, a_unknown } },
    { elem_union, { MATH3DEFCOM, a_unknown } },
    { elem_uplimit, { MATH3COMMON, a_unknown } },
    { elem_use, {   a_externalresourcesrequired, a_onzoom, a_preserveaspectratio, a_transin, a_transout, a_xlinkhref, a_will_change,
                    SVG_GR, SVG_BOX, SVG_COND, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_var, { LIVING_STANDARD_PLUS, a_unknown } },
    { elem_variance, { MATH3DEFCOM, a_unknown } },
    { elem_veaffine, { a_in, a_result, a_transformpath, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vec, { LANGCLASS3, a_unknown } },
    { elem_vector, { MATH3COMMON, a_unknown } },
    { elem_vectoreffect, { a_compositing, a_vectoreffectunits, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vectorproduct, { MATH3DEFCOM, a_unknown } },
    { elem_veexclude, { a_in, a_in2, a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vefill, { a_fill, a_in, a_transform, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_veintersect, { a_in, a_in2, a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vejoin, { a_connect, a_in, a_in2, a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vemarker, { a_in, a_marker_end, a_marker_mid, a_marker_start, a_transform, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vemarkerpath, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vepath, { a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vepathref, { a_connect, a_reverse, a_transform, SVG_XLINK, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vereverse, { a_in, a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vesetback, { a_in, a_result, a_setback_offset, a_transform, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vestroke, { a_fill, a_in, a_transform, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vestrokepath, { a_in, a_result, a_stroke_dasharray, a_stroke_dashoffset, a_stroke_linecap, a_stroke_linejoin, a_stroke_miterlimit, a_stroke_width, a_transform, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_veunion, { a_in, a_in2, a_result, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_video, { a_audio, a_autobuffer, a_autopictureinpicture, a_autoplay, a_buffered, a_controls, a_controlslist, a_crossorigin,
                    a_currenttime, a_disablepictureinpicture, a_disableremoteplayback, a_duration, a_initialvisibility, a_intrinsicsize, a_loop,
                    a_loopcount, a_loopend, a_loopstart, a_mediagroup, a_muted, a_overlay, a_playcount, a_playsinline, a_poster, a_preload,
                    a_preserveaspectratio, a_start, a_transformbehaviour, a_transin, a_transout, a_type,
                    SVG_BOX, SVG_COND, SVG_XLINK, SVG_ANTIME, SVG_PRES, SVG_SYNC, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_view, { a_externalresourcesrequired, a_preserveaspectratio, a_viewbox, a_viewtarget, a_zoomandpan, SVG_PRES, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_vkern, { a_g1, a_g2, a_k, a_u1, a_u2, METADATA, LIVING_STANDARD, a_unknown } },
    { elem_wbr, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_xa, { METADATA, LIVING_STANDARD, a_unknown } },
    { elem_xml, { a_encoding, a_id, a_standalone, a_src, a_unknown } },
    { elem_xmp, { LANGCLASS, a_unknown } },
    { elem_xor, { MATH3DEFCOM, a_unknown } },
    { elem_error, { a_unknown } } };

CONSTEXPR size_t vebs_size = last_element_tag + 1;
typedef ::std::array < attribute_bitset, vebs_size > vebs_t;
vebs_t vebs;

void elements_init (nitpick& nits)
{   vebs.fill (attribute_bitset ());
#ifdef DEBUG
    int n = 0;
    e_element e = elem_error;
#endif // DEBUG
    for (int i = 0; GSL_AT (ei, i).tag_ != elem_error; ++i)
    {   if (vebs.at (GSL_AT (ei, i).tag_).any ())
            nits.pick (nit_repeated_attribute, es_warning, ec_program, elem::name (GSL_AT (ei, i).tag_), " repeated in bitset init");
        for (int j = 0; GSL_AT (GSL_AT (ei, i).a_, j) != a_unknown; ++j)
        {   if (static_cast < ::std::size_t > (j) >= max_attrib)
            {   nits.pick (nit_internal_parsing_error, es_catastrophic, ec_program, elem::name (GSL_AT (ei, i).tag_), " has more attributes than allocated");
                break; }
#ifdef DEBUG
            if (j > n) { n = j; e = i; }
            if (vebs.at (GSL_AT (ei, i).tag_).test (GSL_AT (GSL_AT (ei, i).a_, j)))
                nits.pick (nit_repeated_attribute, es_comment, ec_program, "attribute ", attr::name (GSL_AT (GSL_AT (ei, i).a_, j)), " repeated in ", elem::name (GSL_AT (ei, i).tag_), " bitset init");
            else vebs.at (GSL_AT (ei, i).tag_).set (GSL_AT (GSL_AT (ei, i).a_, j)); } }
    nits.pick (nit_note, es_splurge, ec_program, "<", elem::name (e), "> has ", n, " attributes"); }
#else // DEBUG
            if (! vebs.at (GSL_AT (ei, i).tag_).test (GSL_AT (GSL_AT (ei, i).a_, j)))
                vebs.at (GSL_AT (ei, i).tag_).set (GSL_AT (GSL_AT (ei, i).a_, j)); } } }
#endif // DEBUG

void element_add_attribute (const e_element e, const e_attribute a)
{   PRESUME (e < elem_error, __FILE__, __LINE__);
    PRESUME (a < a_illegal, __FILE__, __LINE__);
    vebs.at (e).set (a); }

attribute_bitset element_attributes (const e_element e)
{   PRESUME (e < vebs.size (), __FILE__, __LINE__);
    if (e >= vebs.size ()) return attribute_bitset ();
    return vebs.at (e); }

bool has_attribute (const e_element e, const e_attribute a)
{   PRESUME (e < vebs.size (), __FILE__, __LINE__);
    if (e >= vebs.size ()) return false;
    return vebs.at (e).test (a); }

void add_element_attributes (const vstr_t& v)
{   nitpick nuts;
    for (auto e : v)
    {   vstr_t args (split_by_charset (e, ","));
        if (args.size () < 2) continue;
        const elem el (context.html_ver (), args.at (0));
        if (el.invalid ())
        {   outstr.err ("the element '", args.at (0), "' is not recognised\n"); }
        else if (args.at (1).find (':') != ::std::string::npos)
            outstr.err ("apologies, but " PROG " does not support adding attributes in non-standard namespaces (yet)\n");
        else
        {   ::std::string ns;
            namespaces_ptr ptr;
            const e_attribute a = attr :: parse (nuts, context.html_ver (), ptr, args.at (1), ns);
            if (a == a_error)
            {   outstr.err ("the attribute '", args.at (1), "' is not recognised\n"); }
            else element_add_attribute (el.get (), a); } } }

#ifdef DEBUG
void avm_class_crosscheck (const e_element e, const e_attribute a)
{   if (! vebs.at (e).test (a))
        if (overlap (elem::first_version (e), elem::final_version (e), elem::first_version (a), elem::final_version (a)))
        {   ::std::cerr << "avm/elem dispute ";
            ::std::string n (elem::name (e));
            if (n.empty ()) ::std::cerr << e; else ::std::cerr << n;
            ::std::cerr << " ";
            n = attr::name (a);
            if (n.empty ()) ::std::cerr << a; else ::std::cerr << n;
            ::std::cerr << "\n"; } }
#endif // DEBUG
