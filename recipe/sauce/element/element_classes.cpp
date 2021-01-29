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
#include "element/elem.h"
#include "attribute/attr.h"
#include "element/element_classes.h"

#define WIDEHIGH    a_height, a_width

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
#define MATH2TABLE  a_columnwidth, a_minilabelspacing, a_side, a_width, MATH1TABLE
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

#define SVGXY       a_x, a_y
#define SVGDXY      a_dx, a_dy
#define SVGBOX      a_fitbbox, WIDEHIGH, SVGXY
#define SVGCOMP     a_amplitude, a_exponent, a_intercept, a_offset, a_slope, a_tablevalues, a_type
#define SVGFIT      a_fitboxtoviewport, a_preserveaspectratio
#define SVG10FILTER a_in, a_nodeid
#define SVGGRAD     a_gradienttransform, a_gradientunits, a_gradient_units
#define SVGREF      a_refx, a_refy
#define SVGREPL     a_actuate, a_xmllink, a_show
#define SVGG        a_systemrequired, a_transform

#define SVG11       a_xmlspace, a_xmlbase
#define SVG11COND   a_requiredextensions, a_requiredfeatures, a_systemlanguage
#define SVG11ANEV   a_onbegin, a_onend, a_onrepeat
#define SVG11GREV   a_onactivate, a_onfocusin, a_onfocusout
#define SVG11EVENT  SVG11ANEV, SVG11GREV
#define SVG11FILTER a_result, WIDEHIGH, SVGXY
#define SVG11PRES   a_alignmentbaseline, a_baselineshift, a_clip, a_clip_path, a_clip_rule, a_colour, a_colour_interpolation, a_colour_interpolation_filters, \
                    a_colour_profile, a_colour_rendering, a_cursor, a_direction, a_display, a_dominantbaseline, a_enablebackground, a_fill, a_fill_opacity, \
                    a_fill_rule, a_filter, a_flood_colour, a_flood_opacity, a_font, a_font_family, a_font_size, a_font_size_adjust, a_font_stretch, \
                    a_font_style, a_font_variant, a_font_weight, a_glyph_orientation_vertical, a_glyphorientation_horizontal, a_imagerendering, a_kerning, \
                    a_letter_spacing, a_lighting_colour, a_marker, a_marker_end, a_marker_mid, a_marker_start, a_mask, a_opacity, a_overflow, a_paint_order, \
                    a_pointerevents, a_shaperendering, a_stop_colour, a_stop_opacity, a_stroke, a_stroke_dasharray, a_stroke_dashoffset, a_stroke_linecap, \
                    a_stroke_linejoin, a_stroke_miterlimit, a_stroke_opacity, a_stroke_width, a_textdecoration, a_unicodebidi, a_vector_effect, a_visibility, \
                    a_word_spacing, a_writingmode
#define SVG11XLINK  a_xlinkactuate, a_xlinkarcrole, a_xlinkhref, a_xlinkrole, a_xlinkshow, a_xlinktitle, a_xlinktype
#define SVG11ANAT   a_attributename, a_attributetype
#define SVG11ANTIME a_begin, a_dur, a_end, a_min, a_max, a_restart, a_repeatcount, a_repeatdur
#define SVG11ANVAL  a_calcmode, a_values, a_keytimes, a_keysplines
#define SVG11ANADD  a_additive, a_accumulate

#define SVG20       a_tabindex
#define SVG20COND   SVG11COND
#define SVGPRES     a_textanchor, a_textrendering, SVG11PRES

#define RDFa        a_about, a_content, a_datatype, a_inlist, a_prefix, a_property, a_rel, a_resource, a_rev, a_src, a_typeof, a_vocab

#define ALIGNCHAR   a_align, a_char, a_charoff, a_valign
#define BLUR        a_onfocus, a_onblur
#define DINGBAT     a_dingbat, a_md, a_seqnum, a_skip, a_align, a_clear, a_nowrap
#define KEYMOUSE    a_onclick, a_ondblclick, a_onkeydown, a_onkeypress, a_onkeyup, a_onmousedown, a_onmousemove, a_onmouseout, a_onmouseover, a_onmouseup
#define RESERVED4   a_datafld, a_dataformatas, a_datasrc
#define XHTML       a_xmlns, a_xmllang, RDFa, SVG11

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
#define ARIA        a_ariaactivedescendant, a_ariaatomic, a_ariaautocomplete, a_ariabusy, a_ariachecked, a_ariacontrols, a_ariadescribedby, \
                    a_ariadisabled, a_ariadropeffect, a_ariaexpanded, a_ariaflowto, a_ariagrabbed, a_ariahaspopup, a_ariahidden, a_ariainvalid, \
                    a_arialabel, a_arialabelledby, a_arialevel, a_arialive, a_ariamultiline, a_ariamultiselectable, a_ariaorientation, a_ariaowns, \
                    a_ariaposinset, a_ariapressed, a_ariareadonly, a_ariarelevant, a_ariarequired, a_ariaselected, a_ariasetsize, a_ariasort, \
                    a_ariavaluemax, a_ariavaluemin, a_ariavaluenow, a_ariavaluetext
#define COMMON4     TSL, XHTML, ARIA
#define X2_CORE     a_layout, a_xmlid
#define X2_HYPER    a_cite, a_href, a_hreflang, a_hrefmedia, a_hreftype, a_nextfocus, a_prevfocus, a_target, a_itstranslate
#define X2_SOLO     a_class, a_dir, a_id, a_style, a_title, XHTML
#define X2_EMBED    a_encoding, a_srctype
#define X2_MAP      a_usemap, a_ismap, a_shape, a_coords
#define X2_EVENT    a_event, a_observer, a_eventtarget, a_function, a_handler, a_phase, a_propagate, a_defaultaction
#define X2_COMMON   a_edit, a_media, a_role, X2_CORE, X2_HYPER, X2_EMBED, X2_MAP, X2_EVENT, SVG20
#define X2          X2_COMMON, COMMON4
#define XHTML2      X2_COMMON, X2_SOLO
#define COMMON5     a_accesskey, a_contenteditable, a_contextmenu, a_draggable, a_hidden, a_inert, a_irrelevant, a_item, a_itemid, a_itemprop, \
                    a_itemref, a_itemscope, a_itemtype, a_numberonce, a_onabort, a_onautocomplete, a_onautocompleteerror, a_onbeforeunload, \
                    a_oncancel, a_oncanplay, a_oncanplaythrough, a_onchange, a_onclose, a_oncontextmenu, a_oncuechange, a_ondrag, a_ondragend, \
                    a_ondragenter, a_ondragexit, a_ondragleave, a_ondragover, a_ondragstart, a_ondrop, a_dropzone, a_ondurationchange, a_onemptied, \
                    a_onended, a_onerror, a_onformchange, a_onforminput, a_onhashchange, a_oninput, a_oninvalid, a_is, a_onload, a_onloadeddata, \
                    a_onloadedmetadata, a_onloadstart, a_onmessage, a_onmouseenter, a_onmouseleave, a_onmousewheel, a_onpause, a_onplay, \
                    a_onplaying, a_onprogress, a_onratechange, a_onreadystatechange, a_onreset, a_onresize, a_onscroll, a_onsought, a_onseeking, \
                    a_onselect, a_onstorage, a_onsubmit, a_onunload, a_registrationmark, a_spellcheck, a_onshow, a_onstalled, a_subject, \
                    a_onsuspend, a_ontimeupdate, a_template, a_ontoggle, a_translate, a_onvolumechange, a_onwaiting, BLUR, X2
#define COMMON50    a_generator_unable, COMMON5
#define COMMON51    a_oncopy, a_oncut, a_onpaste, a_onwheel, COMMON50
#define COMMON52    a_onauxclick, a_onloadend, COMMON51
#define COMMON53    a_datawild, COMMON52
#define COMMON54    a_autocapitalise, a_autofocus, a_enterkeyhint, a_exportparts, a_inputmode, a_onformdata, a_onsecuritypolicyviolation, \
                    a_onslotchange, a_part, a_slot, COMMON53
#define COMMON54PLUS a_index, COMMON54

struct element_init_t
{   e_element tag_;
    e_attribute a_ [512]; };

element_init_t ei [] =
{   { elem_undefined, { a_unknown } },
    { elem_a, { a_actuate, a_charset, a_download, a_effect, a_externalresourcesrequired, a_md, a_methods, a_name, a_ping, a_print, a_referrerpolicy, a_show, a_size,
                a_transform, a_type, a_urn, a_xmllink, SVG11GREV, SVG11XLINK, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_abbr, { a_full, COMMON54, a_unknown } },
    { elem_abbrev, { LC3PLUS, a_unknown } },
    { elem_above, { a_sym, LANGCLASS3, a_unknown } },
    { elem_abs, { MATH3DEFCOM, a_unknown } },
    { elem_abstract, { HTMLPLUS, a_unknown } },
    { elem_access, { a_activate, a_key, a_order, a_targetid, a_targetrole, XHTML2, a_unknown } },
    { elem_acronym, { TSLPLUS, a_unknown } },
    { elem_action, { a_if, a_while, XHTML2, a_unknown } },
    { elem_added, { HTMLPLUS, a_unknown } },
    { elem_addeventlistener, { XHTML2, a_unknown } },
    { elem_address, { a_align, a_clear, a_nowrap, COMMON54, a_unknown } },
    { elem_altglyph, { a_externalresourcesrequired, a_glyphref, a_format, a_rotate, SVG11GREV, SVG11XLINK, SVGDXY, SVG20COND, SVGPRES, SVGXY, COMMON54, a_unknown } },
    { elem_altglyphdef, { COMMON54, a_unknown } },
    { elem_altglyphitem, { COMMON54, a_unknown } },
    { elem_and, { MATH3DEFCOM, a_unknown } },
    { elem_animate, {   a_externalresourcesrequired, a_from, a_to, SVG11ANAT, SVG11ANTIME, SVG11ANEV, SVG11ANVAL, SVG11ANADD, SVG11XLINK, SVG20COND, SVGPRES, COMMON54,
                        a_unknown } },
    { elem_animatecolour, { a_externalresourcesrequired, SVG11ANAT, SVG11ANTIME, SVG11ANEV, SVG11ANVAL, SVG11ANADD, SVG11XLINK, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_animatemotion, { a_externalresourcesrequired, a_fill, a_keypoints, a_origin, a_path, a_rotate, SVG11ANTIME, SVG11ANEV, SVG11ANVAL, SVG11ANADD, SVG11XLINK,
                            SVG20COND, COMMON54, a_unknown } },
    { elem_animatetransform, {  a_externalresourcesrequired, a_from, a_to, a_type, SVG11ANAT, SVG11ANTIME, SVG11ANEV, SVG11ANVAL, SVG11ANADD, SVG11XLINK, SVG20COND,
                                SVGPRES, COMMON54, a_unknown } },
    { elem_animation, { COMMON54, a_unknown } },
    { elem_annotation, { a_cd, a_name, a_src, MATH3DEFCOM, a_unknown } },
    { elem_annotation_xml, { a_cd, a_name, a_src, MATH3DEFCOM, a_unknown } },
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
    { elem_area, { a_alt, a_download, a_nohref, a_name, a_ping, a_referrerpolicy, a_type, COMMON54, a_unknown } },
    { elem_arg, { a_index, a_lang, MATH3DEFCOM, a_unknown } },
    { elem_array, { a_align, a_coldef, a_labels, a_ldelim, a_rdelim, a_unknown } },
    { elem_article, { a_pubdate, COMMON54, a_unknown } },
    { elem_aside, { COMMON54, a_unknown } },
    { elem_atop, { a_unknown } },
    { elem_au, { LANGCLASS3, a_unknown } },
    { elem_audio, { a_autoplay, a_controls, a_crossorigin, a_currenttime, a_duration, a_loop, a_mediagroup, a_muted, a_preload, COMMON54, a_unknown } },
    { elem_b, { COMMON54PLUS, a_unknown } },
    { elem_banner, { LANGCLASS3, a_unknown } },
    { elem_bar, { LANGCLASS3, a_unknown } },
    { elem_base, { COMMON54, a_unknown } },
    { elem_basefont, { a_colour, a_size, a_face, COMMON4, a_unknown } },
    { elem_bdi, { COMMON54, a_unknown } },
    { elem_bdo, { COMMON54, a_unknown } },
    { elem_below, { a_sym, LANGCLASS3, a_unknown } },
    { elem_bgsound, { a_balance, a_loop, a_src, a_volume, a_unknown } },
    { elem_big, { COMMON4, a_unknown } },
    { elem_bind, { MATH3COMMON, a_unknown } },
    { elem_blink, { a_unknown } },
    { elem_blockquote, { a_align, COMMON54, a_unknown } },
    { elem_blockcode, { XHTML2, a_unknown } },
    { elem_body, {  a_alink, a_background, a_bgcolour, a_bottommargin, a_leftmargin, a_link, a_onafterprint, a_onbeforeprint,
                    a_onfullscreenchange, a_onfullscreenerror, a_onlanguagechange, a_onmessageerror, a_onoffline, a_ononline, a_onpagehide, a_onpageshow, a_onpopstate,
                    a_onredo, a_onrejectionhandled, a_onundo, a_onunhandledrejection, a_rightmargin, a_text, a_topmargin, a_vlink,
                    COMMON54, a_unknown } },
    { elem_box, { a_size, LANGCLASS3, a_unknown } },
    { elem_bq, { a_nowrap, a_clear, LANGCLASS3, a_unknown } },
    { elem_br, { a_clear, COMMON54PLUS, a_unknown } },
    { elem_bt, { a_class, a_unknown } },
    { elem_button, {    a_autocomplete, a_disabled, a_form, a_formaction, a_formenctype, a_formmethod, a_formnovalidate, a_formtarget, a_menu, a_name,
                        a_type, a_value, RESERVED4, COMMON54, a_unknown } },
    { elem_bvar, { MATH3COMMON, a_unknown } },
    { elem_byline, { HTMLPLUS, a_unknown } },
    { elem_canvas, { WIDEHIGH, COMMON54, a_unknown } },
    { elem_caption, { a_align, a_valign, COMMON54PLUS, a_unknown } },
    { elem_card, { MATH3DEFCOM, a_unknown } },
    { elem_cartesianproduct, { MATH3DEFCOM, a_unknown } },
    { elem_cbytes, { MATH3COMMON, a_unknown } },
    { elem_cdata, { a_unknown } },
    { elem_ceiling, { MATH3DEFCOM, a_unknown } },
    { elem_centre, { a_unknown } },
    { elem_cerror, { MATH3COMMON, a_unknown } },
    { elem_changed, { a_id, a_idref, a_unknown } },
    { elem_choose, { a_unknown } },
    { elem_ci, { a_type, MATH3DEFCOM, a_unknown } },
    { elem_circle, { a_externalresourcesrequired, a_cx, a_cy, a_r, SVG11GREV, SVG20COND, SVGPRES, SVGG, COMMON54, a_unknown } },
    { elem_cite, { COMMON54PLUS, a_unknown } },
    { elem_clippath, { a_clippathunits, a_externalresourcesrequired, a_transform, SVGPRES, COMMON54, a_unknown } },
    { elem_cmd, { HTMLPLUS, a_unknown } },
    { elem_cn, { a_base, a_type, MATH3DEFCOM, a_unknown } },
    { elem_code, { COMMON54PLUS, a_unknown } },
    { elem_col, { a_bgcolour, a_span, a_width, ALIGNCHAR, COMMON54, a_unknown } },
    { elem_colgroup, { a_bgcolour, a_span, a_width, ALIGNCHAR, COMMON54, a_unknown } },
    { elem_colourprofile, { a_local, a_renderingintent, SVG11XLINK, COMMON54, a_unknown } },
    { elem_command, { a_checked, a_disabled, a_icon, a_label, a_radiogroup, a_type, COMMON50, a_unknown } },
    { elem_comment, { a_data, TIPSYLANG, a_unknown } },
    { elem_complexes, { MATH3DEFCOM, a_unknown } },
    { elem_compose, { MATH3DEFCOM, a_unknown } },
    { elem_condition, { MATH3COMMON, a_unknown } },
    { elem_conjugate, { MATH3DEFCOM, a_unknown } },
    { elem_content, { a_select, COMMON54, a_unknown } },
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
    { elem_cursor, { a_externalresourcesrequired, SVGXY, SVG11XLINK, SVG20COND, COMMON54, a_unknown } },
    { elem_data, { a_d, a_value, COMMON54, a_unknown } },
    { elem_datalist, { COMMON54, a_unknown } },
    { elem_dd, { a_compact, a_clear, COMMON54PLUS, a_unknown } },
    { elem_ddot, { LANGCLASS3, a_unknown } },
    { elem_declare, { a_occurrence, a_nargs, a_scope, a_type, MATH3DEFCOM, a_unknown } },
    { elem_defs, { a_externalresourcesrequired, a_transform, SVG11GREV, SVGBOX, SVGFIT, SVGREF, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_degree, { MATH3COMMON, a_unknown } },
    { elem_desc, { a_systemrequired, COMMON54, a_unknown } },
    { elem_del, { a_datetime, COMMON54, a_unknown } },
    { elem_details, { a_open, COMMON54, a_unknown } },
    { elem_determinant, { MATH3DEFCOM, a_unknown } },
    { elem_dfn, { COMMON54PLUS, a_unknown } },
    { elem_di, { XHTML2, a_unknown } },
    { elem_dialogue, { a_open, COMMON54, a_unknown } },
    { elem_diff, { MATH3DEFCOM, a_unknown } },
    { elem_dir, { a_align, a_clear, a_compact, a_dingbat, a_md, a_index, a_plain, a_wrap, COMMON4, a_unknown } },
    { elem_discard, { a_begin, a_xlinkhref, COMMON54, a_unknown } },
    { elem_dispatchevent, { a_bubbles, a_cancelable, XHTML2, a_unknown } },
    { elem_div, { a_align, a_clear, a_nowrap, RESERVED4, COMMON54, a_unknown } },
    { elem_divergence, { MATH3DEFCOM, a_unknown } },
    { elem_divide, { MATH3DEFCOM, a_unknown } },
    { elem_dl, { a_compact, a_clear, COMMON54PLUS, a_unknown } },
    { elem_domain, { MATH3COMMON, a_unknown } },
    { elem_domainofapplication, { MATH3DEFCOM, a_unknown } },
    { elem_dot, { LANGCLASS3, a_unknown } },
    { elem_dt, { a_compact, a_clear, COMMON54PLUS, a_unknown } },
    { elem_element, { COMMON54, a_unknown } },
    { elem_elementdef, { COMMON54, a_unknown } },
    { elem_ellipse, { a_externalresourcesrequired, a_cx, a_cy, a_rx, a_ry, SVG11GREV, SVG20COND, SVGPRES, SVGG, COMMON54, a_unknown } },
    { elem_em, { COMMON54PLUS, a_unknown } },
    { elem_embed, { a_type, WIDEHIGH, COMMON54, a_unknown } },
    { elem_emptyset, { MATH3DEFCOM, a_unknown } },
    { elem_eq, { MATH3DEFCOM, a_unknown } },
    { elem_equivalent, { MATH3DEFCOM, a_unknown } },
    { elem_eulergamma, { MATH3DEFCOM, a_unknown } },
    { elem_event_source, { a_onevent, COMMON5, a_unknown } },
    { elem_eventsource, { COMMON5, a_unknown } },
    { elem_exists, { MATH3DEFCOM, a_unknown } },
    { elem_exp, { MATH3DEFCOM, a_unknown } },
    { elem_exponentiale, { MATH3DEFCOM, a_unknown } },
    { elem_extensiondefs, { COMMON54, a_unknown } },
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
    { elem_faux_xml, { a_encoding, a_version, a_unknown } },
    { elem_faux_whitespace, { a_unknown } },
    { elem_feblend, { a_mode, a_in2, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fecolour, { a_colour, SVG10FILTER, COMMON54, a_unknown } },
    { elem_fecolourmatrix, { a_type, a_values, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fecomposite, { a_in2, a_k1, a_k2, a_k3, a_k4, a_operator, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fecomponenttransfer, { SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_feconvolvematrix, {  a_bias, a_divisor, a_edgemode,  a_in, a_kernelmatrix, a_kernelunitlength, a_order, a_preservealpha,
                                a_targetx, a_targety, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fediffuselighting, { a_diffuseconstant, a_lightcolour, a_resultscale, a_surfacescale, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fedisplacementmap, { a_in2, a_scale, a_xchannelselector, a_ychannelselector, SVG10FILTER, COMMON54, a_unknown } },
    { elem_fedistantlight, { a_azimuth, a_elevation, COMMON54, a_unknown } },
    { elem_fedropshadow, { COMMON54, a_unknown } },
    { elem_feflood, { SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fefunca, { SVGCOMP, COMMON54, a_unknown } },
    { elem_fefuncb, { SVGCOMP, COMMON54, a_unknown } },
    { elem_fefuncg, { SVGCOMP, COMMON54, a_unknown } },
    { elem_fefuncr, { SVGCOMP, COMMON54, a_unknown } },
    { elem_fegaussianblur, { a_stddeviation, a_std_deviation, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_feimage, { a_externalresourcesrequired, a_nodeid, a_preserveaspectratio, a_transform, SVGREPL, SVG11XLINK, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_femerge, { SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_femergenode, { a_in, COMMON54, a_unknown } },
    { elem_femorphology, { a_operator, a_radius, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_feoffset, { SVGDXY, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fepointlight, { a_z, SVGXY, COMMON54, a_unknown } },
    { elem_fespecularlighting, { a_kernelunitlength, a_lightcolour, a_specularconstant, a_specularexponent, a_surfacescale, SVG10FILTER, SVG11FILTER, SVGPRES,
                                COMMON54, a_unknown } },
    { elem_fespotlight, { a_pointsatx, a_pointsaty, a_pointsatz, a_limitingconeangle, a_specularexponent, a_z, SVGXY, COMMON54, a_unknown } },
    { elem_fetile, { SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_feturbulence, { a_basefrequency, a_numoctaves, a_seed, a_stitchtiles, a_type, SVG10FILTER, SVG11FILTER, SVGPRES, COMMON54, a_unknown } },
    { elem_fieldset, { a_disabled, a_form, a_name, COMMON54, a_unknown } },
    { elem_fig, { a_align, a_clear, a_ismap, a_md, a_noflow, a_src, a_units, WIDEHIGH, LC3PLUS, a_unknown } },
    { elem_figure, { COMMON54, a_unknown } },
    { elem_figcaption, { COMMON54, a_unknown } },
    { elem_filter, { a_externalresourcesrequired, a_filterres, a_filter_units, a_filterunits, a_primitiveunits, SVG11XLINK, SVGPRES, SVGBOX, COMMON54, a_unknown } },
    { elem_floor, { MATH3DEFCOM, a_unknown } },
    { elem_flowdiv, { COMMON54, a_unknown } },
    { elem_flowimage, { COMMON54, a_unknown } },
    { elem_flowline, { COMMON54, a_unknown } },
    { elem_flowpara, { COMMON54, a_unknown } },
    { elem_flowref, { COMMON54, a_unknown } },
    { elem_flowregion, { COMMON54, a_unknown } },
    { elem_flowregionbreak, { COMMON54, a_unknown } },
    { elem_flowregionexclude, { COMMON54, a_unknown } },
    { elem_flowroot, { COMMON54, a_unknown } },
    { elem_flowspan, { COMMON54, a_unknown } },
    { elem_flowtref, { COMMON54, a_unknown } },
    { elem_fn, { a_lang, MATH2DEFCOM, a_unknown } },
    { elem_font, {  a_externalresourcesrequired, a_face, a_horizadvx, a_horizoriginx, a_horizoriginy, a_size, a_vertadvy, a_vertoriginx, a_vertoriginy, SVGPRES,
                    COMMON54, a_unknown } },
    { elem_fontface, {  a_accentheight, a_alphabetic, a_ascent, a_bbox, a_capheight, a_descent, a_font_family, a_font_size, a_font_stretch, a_font_style,
                        a_font_variant, a_font_weight, a_hanging, a_ideographic, a_mathematical, a_overlineposition, a_overlinethickness, a_panose1,
                        a_slope, a_stemh, a_stemv, a_strikethroughposition, a_strikethroughthickness, a_underlineposition, a_underlinethickness,
                        a_unicoderange, a_unitsperem, a_valphabetic, a_vhanging, a_videographic, a_vmathematical, a_widths, a_xheight, COMMON54, a_unknown } },
    { elem_fontfaceformat, { a_string, COMMON54, a_unknown } },
    { elem_fontfacename, { a_name, COMMON54, a_unknown } },
    { elem_fontfacesrc, { COMMON54, a_unknown } },
    { elem_fontfaceuri, { SVG11XLINK, COMMON54, a_unknown } },
    { elem_forall, { MATH3DEFCOM, a_unknown } },
    { elem_form, { a_accept, a_acceptcharset, a_action, a_autocomplete, a_enctype, a_method, a_name, a_novalidate, a_script, COMMON54PLUS, a_unknown } },
    { elem_foreignobject, { a_externalresourcesrequired, SVG20COND, SVGG, SVGBOX, SVGPRES, COMMON54, a_unknown } },
    { elem_footer, { COMMON54, a_unknown } },
    { elem_footnote, { HTMLPLUS , a_unknown } },
    { elem_frame, { a_dir, a_frameborder, a_longdesc, a_name, a_noresize, a_marginheight, a_marginwidth, a_scrolling, XHTML, X2_COMMON, TIPSYCLID, a_unknown } },
    { elem_frameset, { a_cols, a_onload, a_onunload, a_rows, XHTML, TIPSYCLID, a_unknown } },
    { elem_g, { a_externalresourcesrequired, a_transform, SVG11GREV, SVGBOX, SVGFIT, SVGREF, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_gcd, { MATH3DEFCOM, a_unknown } },
    { elem_geq, { MATH3DEFCOM, a_unknown } },
    { elem_glyph, { a_arabicform, a_d, a_glyphname, a_horizadvx, a_orientation, a_unicode, a_vertadvy, a_vertoriginx, a_vertoriginy, SVGPRES, COMMON54, a_unknown } },
    { elem_glyphref, { a_glyphref, SVGXY, SVGDXY, SVG11XLINK, SVGPRES, COMMON54, a_unknown } },
    { elem_grad, { MATH3DEFCOM, a_unknown } },
    { elem_gt, { MATH3DEFCOM, a_unknown } },
    { elem_h, { XHTML2, a_unknown } },
    { elem_h1, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_h2, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_h3, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_h4, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_h5, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_h6, { DINGBAT, COMMON54PLUS, a_unknown } },
    { elem_handler, { COMMON54, a_unknown } },
    { elem_hat, { LANGCLASS3, a_unknown } },
    { elem_head, { a_profile, COMMON54, a_unknown } },
    { elem_header, { COMMON54, a_unknown } },
    { elem_hgroup, { COMMON54, a_unknown } },
    { elem_hint, { COMMON54, a_unknown } },
    { elem_hkern, { a_g1, a_g2, a_k, a_u1, a_u2, COMMON54, a_unknown } },
    { elem_hp1, { a_unknown } },
    { elem_hp2, { a_unknown } },
    { elem_hp3, { a_unknown } },
    { elem_hp4, { a_unknown } },
    { elem_hp5, { a_unknown } },
    { elem_hp6, { a_unknown } },
    { elem_hr, { a_align, a_colour, a_noshade, a_size, a_md, a_width, COMMON54PLUS, a_unknown } },
    { elem_html, { a_manifest, a_version, a_urn, a_xsischemaloc, COMMON54 } },
    { elem_htmlplus, { a_forms, a_version, a_unknown } },
    { elem_i, { COMMON54PLUS, a_unknown } },
    { elem_ident, { MATH3DEFCOM, a_unknown } },
    { elem_iframe, {    a_align, a_allow, a_allowfullscreen, a_allowpaymentrequest, a_allowusermedia, a_csp, a_frameborder, a_importance,
                        a_loading, a_longdesc, a_marginheight, a_marginwidth, a_mozbrowser, a_name, a_referrerpolicy, a_sandbox, a_scrolling,
                        a_srcdoc, WIDEHIGH, COMMON54, a_unknown } },
    { elem_ilayer, {    a_above, a_background, a_below, a_bgcolour, a_class, a_clip, a_height, a_id, a_left, a_name, a_pagex, a_pagey,
                        a_src, a_style, a_top, a_visibility, a_zindex, a_unknown } },
    { elem_image, { a_align, a_externalresourcesrequired, a_seethru, a_xlinkhref, MATH2UNIQUE, MATH2UNIDEF, SVG11GREV, SVGBOX, SVGG, SVGREPL,
                    SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_imaginary, { MATH3DEFCOM, a_unknown } },
    { elem_imaginaryi, { MATH3DEFCOM, a_unknown } },
    { elem_img, {   a_align, a_alt, a_border, a_crossorigin, a_decoding, a_hspace, a_importance, a_intrinsicsize, a_loading, a_longdesc,
                    a_md, a_referrerpolicy, a_seethru, a_sizes, a_srcset, a_units, a_vspace, WIDEHIGH, COMMON54, a_unknown } },
    { elem_implies, { MATH3DEFCOM, a_unknown } },
    { elem_in, { MATH3DEFCOM, a_unknown } },
    { elem_infinity, { MATH3DEFCOM, a_unknown } },
    { elem_input, { a_accept, a_align, a_alt, a_autocorrect, a_autocomplete, a_capture, a_checked, a_dirname,
                    a_disabled, a_error, a_form, a_formaction, a_formenctype, a_formmethod, a_formnovalidate, a_formtarget, a_incremental,
                    a_list, a_max, a_maxlength, a_md, a_min, a_minlength, a_mozactionhint, a_multiple, a_name, a_orient, a_pattern, a_placeholder,
                    a_readonly, a_required, a_results, a_size, a_step, a_type, a_value, a_webkitdirectory, WIDEHIGH, RESERVED4, COMMON54, a_unknown } },
    { elem_ins, { a_datetime, COMMON54, a_unknown } },
    { elem_int, { MATH3DEFCOM, a_unknown } },
    { elem_interval, { a_closure, MATH3COMMON, a_unknown } },
    { elem_integers, { MATH3DEFCOM, a_unknown } },
    { elem_inverse, { MATH3DEFCOM, a_unknown } },
    { elem_intersect, { MATH3DEFCOM, a_unknown } },
    { elem_isindex, { a_href, a_prompt, COMMON4, a_unknown } },
    { elem_item, { a_align, a_colspan, a_rowspan, a_unknown } },
    { elem_kbd, { COMMON54PLUS, a_unknown } },
    { elem_keygen, { a_autofocus, a_challenge, a_disabled, a_form, a_keyparams, a_keytype, a_name, COMMON51, a_unknown } },
    { elem_l, { a_align, HTMLPLUS, a_unknown } },
    { elem_label, { a_for, a_form, COMMON54, a_unknown } },
    { elem_lambda, { MATH3COMMON, a_unknown } },
    { elem_lang, { LANGCLASS3, a_unknown } },
    { elem_laplacian, { MATH3DEFCOM, a_unknown } },
    { elem_layer, { a_above, a_background, a_below, a_bgcolour, a_class, a_clip, a_height, a_id, a_left, a_name, a_pagex, a_pagey, a_src, a_style,
                    a_top, a_visibility, a_zindex, a_unknown } },
    { elem_lcm, { MATH3DEFCOM, a_unknown } },
    { elem_left, { a_unknown } },
    { elem_legend, { a_align, COMMON54, a_unknown } },
    { elem_leq, { MATH3DEFCOM, a_unknown } },
    { elem_lh, { LANGCLASS3, a_unknown } },
    { elem_li, { a_clear, a_compact, a_dingbat, a_md, a_skip, a_type, a_value, COMMON54PLUS, a_unknown } },
    { elem_limit, { MATH3DEFCOM, a_unknown } },
    { elem_line, { a_externalresourcesrequired, a_x1, a_x2, a_y1, a_y2, SVG11GREV, SVG20COND, SVGPRES, SVGG, COMMON54, a_unknown } },
    { elem_lineargradient, { a_externalresourcesrequired, a_spreadmethod, a_x1, a_x2, a_y1, a_y2, SVG11XLINK, SVGPRES, SVGGRAD, COMMON54, a_unknown } },
    { elem_link, {  a_as, a_charset, a_colour, a_crossorigin, a_disabled, a_idref, a_imagesizes, a_imagesrcset, a_importance, a_integrity,
                    a_methods, a_ping, a_prefetch, a_referrerpolicy, a_scope, a_sizes, a_type, a_updateviacache, a_urn, a_workertype, COMMON54, a_unknown } },
    { elem_listener, { COMMON54, a_unknown } },
    { elem_list, { a_order, MATH3COMMON, a_unknown } },
    { elem_listing, { COMMON4, a_unknown } },
    { elem_lit, { HTMLPLUS, a_unknown } },
    { elem_ln, { MATH3DEFCOM, a_unknown } },
    { elem_loc, { COMMON54, a_unknown } },
    { elem_log, { MATH3DEFCOM, a_unknown } },
    { elem_logbase, { MATH3COMMON, a_unknown } },
    { elem_lowlimit, { MATH3COMMON, a_unknown } },
    { elem_lt, { MATH3DEFCOM, a_unknown } },
    { elem_maction, { a_actiontype, a_selection, MATH3PRES, a_unknown } },
    { elem_main, { COMMON54, a_unknown } },
    { elem_maligngroup, { a_groupalign, MATH3PRES, a_unknown } },
    { elem_malignmark, { a_edge, a_unknown } },
    { elem_map, { a_name, COMMON54, a_unknown } },
    { elem_margin, { HTMLPLUS, a_unknown } },
    { elem_mark, { COMMON54, a_unknown } },
    { elem_marker, {    a_externalresourcesrequired, a_orient, a_markerheight, a_markerunits, a_markerwidth, a_viewbox, SVGPRES, SVGBOX, SVGFIT, SVGREF,
                        COMMON54, a_unknown } },
    { elem_marquee, { a_behaviour, a_bgcolour, a_direction, a_hspace, a_loop, a_scrollamount, a_scrolldelay, a_truespeed, a_vspace, WIDEHIGH, a_unknown } },
    { elem_mask, { a_externalresourcesrequired, a_maskcontentunits, a_mask_units, a_maskunits, SVG20COND, SVGPRES, SVGBOX, COMMON54, a_unknown } },
    { elem_math, {  a_accentunder, a_altimg, a_altimg_height, a_altimg_width, a_altimg_valign, a_alttext, a_background, a_baseline,
                    a_bevelled, a_box, a_cdgroup, a_charalign, a_charspacing, a_close, a_columnspan, a_crossout, a_decimalpoint,
                    a_display, a_denomalign, a_depth, a_edge, a_infixlinebreakstyle, a_leftoverhang, a_length,
                    a_linethickness, a_location, a_longdivstyle, a_lquote, a_macros, a_maxwidth, a_mediummathspace, a_mode,
                    a_mslinethickness, a_name, a_notation, a_numalign, a_open, a_overflow, a_position, a_rightoverhang, a_rowspan,
                    a_rquote, a_scriptlevel, a_scriptminsize, a_scriptsizemultiplier, a_selection, a_separators, a_shift,
                    a_stackalign, a_subscriptshift, a_superscriptshift, a_thickmathspace, a_thinmathspace, a_valign,
                    a_verythickmathspace, a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace,
                    /* a_schemalocation, */ a_style, a_type, MATH3BREAK, MATH3INDENT, MATH3TOKEN, MATH3SHARED,
                    MATH3UNIQUE, MATH3UNIPR, WIDEHIGH, LANGCLASS3, a_unknown } },
    { elem_matrix, { MATH3COMMON, a_unknown } },
    { elem_matrixrow, { MATH3COMMON, a_unknown } },
    { elem_max, { MATH3DEFCOM, a_unknown } },
    { elem_mean, { MATH3DEFCOM, a_unknown } },
    { elem_median, { MATH3DEFCOM, a_unknown } },
    { elem_menclose, { a_notation, MATH3PRES, a_unknown } },
    { elem_menu, { a_align, a_clear, a_compact, a_dingbat, a_index, a_label, a_md, a_plain, a_type, a_wrap, COMMON51, a_unknown } },
    { elem_menuitem, { a_checked, a_default, a_disabled, a_icon, a_label, a_radiogroup, a_type, COMMON51, a_unknown } },
    { elem_merror, { MATH3PRES, a_unknown } },
    { elem_meta, { a_charset, a_httpequiv, a_name, a_scheme, COMMON54, a_unknown } },
    { elem_metadata, { COMMON54, a_unknown } },
    { elem_meter, { a_form, a_high, a_low, a_max, a_min, a_optimum, a_value, COMMON54, a_unknown } },
    { elem_mfenced, { a_close, a_open, a_separators, MATH3PRES, a_unknown } },
    { elem_mfrac, { a_bevelled, a_denomalign, a_linethickness, a_numalign, MATH3PRES, a_unknown } },
    { elem_mglyph, { a_alt, a_fontfamily, a_height, a_index, a_mathvariant, a_mathsize, a_other, a_src, a_width, a_unknown, MATH3PRES } },
    { elem_mh, { a_action, a_hidden, a_method, HTMLPLUS, a_unknown } },
    { elem_mi, { MATH3FONT, MATH3PRES, a_unknown } },
    { elem_min, { MATH3DEFCOM, a_unknown } },
    { elem_minus, { MATH3DEFCOM, a_unknown } },
    { elem_missingglyph, { a_d, a_horizadvx, a_vertadvy, a_vertoriginx, a_vertoriginy, SVGPRES, COMMON54, a_unknown } },
    { elem_mlabeledtr, { a_columnalign, a_groupalign, a_rowalign, MATH3PRES, a_unknown } },
    { elem_mlongdiv, { a_align, a_charalign, a_charspacing, a_longdivstyle, a_stackalign, MATH3PRES, a_unknown } },
    { elem_mn, { MATH3FONT, MATH3PRES, a_unknown } },
    { elem_mmultiscripts, { a_subscriptshift, a_superscriptshift, MATH3PRES, a_unknown } },
    { elem_mo, { MATH3BREAK, MATH3INDENT, MATH3FONT, MATHOPINFO, MATH3PRES, a_unknown } },
    { elem_mode, { MATH3DEFCOM, a_unknown } },
    { elem_moment, { MATH3DEFCOM, a_unknown } },
    { elem_momentabout, { MATH3DEFCOM, a_unknown } },
    { elem_mover, { a_accent, a_align, MATH3PRES, a_unknown } },
    { elem_mpadded, { a_lspace, a_voffset, MATHSIZE, MATH3PRES, a_unknown } },
    { elem_mpath, { a_externalresourcesrequired, SVG11XLINK, COMMON54, a_unknown } },
    { elem_mphantom, { MATH3PRES, a_unknown } },
    { elem_mprescripts, { a_xmlns, a_unknown } },
    { elem_mroot, { MATH3PRES, a_unknown } },
    { elem_mrow, { MATH3PRES, a_unknown } },
    { elem_ms, { a_lquote, a_rquote, MATH3FONT, MATH3PRES, a_unknown } },
    { elem_mscarries, { a_crossout, a_location, a_scriptsizemultiplier, a_position, MATH3PRES, a_unknown } },
    { elem_mscarry, { a_crossout, a_location, MATH3PRES, a_unknown } },
    { elem_msgroup, { a_position, a_shift, MATH3PRES, a_unknown } },
    { elem_msline, { a_leftoverhang, a_length, a_mslinethickness, a_position, a_rightoverhang, MATH3PRES, a_unknown } },
    { elem_mspace, { a_linebreak, MATH3INDENT, MATHSIZE, MATH3TOKEN, MATH3PRES, a_unknown } },
    { elem_msqrt, { MATH3PRES, a_unknown } },
    { elem_msrow, { a_position, MATH3PRES, a_unknown } },
    { elem_mstack, { a_align, a_charalign, a_charspacing, a_stackalign, MATH3PRES, a_unknown } },
    { elem_mstyle, {    a_accentunder, a_background, a_bevelled, a_charalign, a_charspacing, a_close, a_columnspan, a_crossout,
                        a_decimalpoint, a_denomalign, a_depth, a_edge, a_height, a_infixlinebreakstyle, a_leftoverhang, a_length,
                        a_linethickness, a_location, a_longdivstyle, a_lquote, a_mediummathspace, a_mslinethickness, a_notation,
                        a_numalign, a_open, a_position, a_rightoverhang, a_rowspan, a_rquote, a_scriptlevel, a_scriptminsize,
                        a_scriptsizemultiplier, a_selection, a_separators, a_shift, a_stackalign, a_subscriptshift,
                        a_superscriptshift, a_thickmathspace, a_thinmathspace, a_valign, a_verythickmathspace,
                        a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace, MATH3BREAK, MATH3INDENT,
                        MATH3TABLE, MATH3FONT, MATHOPINFO, MATH3PRES, a_unknown } },
    { elem_msub, { a_subscriptshift, MATH3PRES, a_unknown } },
    { elem_msubsup, { a_subscriptshift, a_superscriptshift, MATH3PRES, a_unknown } },
    { elem_msup, { a_superscriptshift, MATH3PRES, a_unknown } },
    { elem_mtable, { MATH3TABLE, MATH3PRES, a_unknown } },
    { elem_mtd, { a_columnalign, a_columnspan, a_groupalign, a_rowalign, a_rowspan, MATH3PRES, a_unknown } },
    { elem_mtext, { MATH3FONT, MATH3PRES, a_unknown } },
    { elem_mtr, { a_columnalign, a_groupalign, a_rowalign, MATH3PRES, a_unknown } },
    { elem_multicol, { a_class, a_cols, a_gutter, a_id, a_style, a_width, a_unknown } },
    { elem_munder, { a_accentunder, a_align, MATH3PRES, a_unknown } },
    { elem_munderover, { a_accent, a_accentunder, a_align, MATH3PRES, a_unknown } },
    { elem_naturalnumbers, { MATH3DEFCOM, a_unknown } },
    { elem_nav, { COMMON54, a_unknown } },
    { elem_navigation, { COMMON5, a_unknown } },
    { elem_neq, { MATH3DEFCOM, a_unknown } },
    { elem_nextid, { a_n, a_unknown } },
    { elem_nl, { XHTML2, a_unknown } },
    { elem_nobr, { a_unknown } },
    { elem_noembed, { a_unknown } },
    { elem_noframes, { COMMON4, a_unknown } },
    { elem_none, { a_xmlns, a_unknown } },
    { elem_noscript, { COMMON54, a_unknown } },
    { elem_not, { MATH3DEFCOM, a_unknown } },
    { elem_notanumber, { MATH3DEFCOM, a_unknown } },
    { elem_note, { a_clear, a_md, a_role, a_src, LC3PLUS, a_unknown } },
    { elem_notin, { MATH3DEFCOM, a_unknown } },
    { elem_notprsubset, { MATH3DEFCOM, a_unknown } },
    { elem_notsubset, { MATH3DEFCOM, a_unknown } },
    { elem_object, {    a_align, a_archive, a_border, a_classid, a_codebase, a_codetype, a_contentlength, a_data, a_declare, a_form,
                        a_hspace, a_name, a_standby, a_type, a_typemustmatch, a_vspace, WIDEHIGH, RESERVED4, COMMON54, a_unknown } },
    { elem_of, { a_unknown } },
    { elem_ol, { a_align, a_clear, a_compact, a_continue, a_reversed, a_seqnum, a_start, a_type, COMMON54PLUS, a_unknown } },
    { elem_online, { a_unknown } },
    { elem_optgroup, { a_disabled, a_label, COMMON54, a_unknown } },
    { elem_option, { a_disabled, a_error, a_label, a_selected, a_value, COMMON54, a_unknown } },
    { elem_or, { MATH3DEFCOM, a_unknown } },
    { elem_otherwise, { MATH3COMMON, a_unknown } },
    { elem_output, { a_for, a_form, a_name, COMMON54, a_unknown } },
    { elem_outerproduct, { MATH3DEFCOM, a_unknown } },
    { elem_over, { a_unknown } },
    { elem_overlay, { a_src, a_md, a_x, a_y, a_imagemap, WIDEHIGH, LANGCLASS3, a_unknown } },
    { elem_p, { a_align, a_clear, a_dingbat, a_md, a_nowrap, a_seqnum, a_skip, COMMON54PLUS, a_unknown } },
    { elem_page, { COMMON54, a_unknown } },
    { elem_pageset, { COMMON54, a_unknown } },
    { elem_param, { a_name, a_type, a_value, a_valuetype, COMMON54, a_unknown } },
    { elem_partialdiff, { MATH3DEFCOM, a_unknown } },
    { elem_path, {  a_d, a_externalresourcesrequired, a_flatness, a_nominallength, a_pathlength, SVG11GREV, SVGBOX, SVGG, SVG20COND, SVGPRES,
                    COMMON54, a_unknown } },
    { elem_pattern, {   a_externalresourcesrequired, a_patterncontentunits, a_patterntransform, a_patternunits, a_pattern_units, a_viewbox,
                        SVG11XLINK, SVG20COND, SVGPRES, SVGFIT, SVGREF, SVGBOX, COMMON54, a_unknown } },
    { elem_person, { LC3PLUS, a_unknown } },
    { elem_pi, { MATH3DEFCOM, a_unknown } },
    { elem_picture, { COMMON54, a_unknown } },
    { elem_piece, { MATH3COMMON, a_unknown } },
    { elem_piecewise, { MATH3COMMON, a_unknown } },
    { elem_plaintext, { LANGCLASS, a_unknown } },
    { elem_plus, { MATH3DEFCOM, a_unknown } },
    { elem_polygon, { a_externalresourcesrequired, a_points, SVG11GREV, SVG20COND, SVGPRES, SVGG, COMMON54, a_unknown } },
    { elem_polyline, { a_externalresourcesrequired, a_points, SVG11GREV, SVG20COND, SVGPRES, SVGG, COMMON54, a_unknown } },
    { elem_power, { MATH3DEFCOM, a_unknown } },
    { elem_pre, { a_clear, a_cols, a_width, a_wrap, COMMON54PLUS, a_unknown } },
    { elem_prefetch, { COMMON54, a_unknown } },
    { elem_preventdefault, { XHTML2, a_unknown } },
    { elem_primes, { MATH3DEFCOM, a_unknown } },
    { elem_printed, { a_unknown } },
    { elem_product, { MATH3DEFCOM, a_unknown } },
    { elem_progress, { a_value, a_max, COMMON54, a_unknown } },
    { elem_prototype, { COMMON54, a_unknown } },
    { elem_prsubset, { MATH3DEFCOM, a_unknown } },
    { elem_q, { a_align, COMMON54PLUS, a_unknown } },
    { elem_quote, { HTMLPLUS, a_unknown } },
    { elem_quotient, { MATH3DEFCOM, a_unknown } },
    { elem_radialgradient, { a_externalresourcesrequired, a_cx, a_cy, a_fx, a_fy, a_r, SVG11XLINK, SVGPRES, SVGGRAD, COMMON54, a_unknown } },
    { elem_range, { a_from, a_until, a_class, a_id, a_unknown } },
    { elem_rationals, { MATH3DEFCOM, a_unknown } },
    { elem_rb, { COMMON54, a_unknown } },
    { elem_rbc, { COMMON54, a_unknown } },
    { elem_real, { MATH3DEFCOM, a_unknown } },
    { elem_reals, { MATH3DEFCOM, a_unknown } },
    { elem_rect, { a_externalresourcesrequired, a_rx, a_ry, SVG11GREV, SVG20COND, SVGPRES, SVGBOX, SVGG, COMMON54, a_unknown } },
    { elem_refcontent, { COMMON54, a_unknown } },
    { elem_reln, { MATH2COMMON, a_unknown } },
    { elem_rem, { MATH3DEFCOM, a_unknown } },
    { elem_removed, { HTMLPLUS, a_unknown } },
    { elem_removeeventlistener, { XHTML2, a_unknown } },
    { elem_render, { a_style, a_tag, a_unknown } },
    { elem_right, { a_unknown } },
    { elem_root, { a_lang, MATH3DEFCOM, a_unknown } },
    { elem_row, { a_unknown } },
    { elem_rp, { COMMON54, a_unknown } },
    { elem_rt, { COMMON54, a_unknown } },
    { elem_rtc, { COMMON54, a_unknown } },
    { elem_ruby, { COMMON54, a_unknown } },
    { elem_s, { COMMON54, a_unknown } },
    { elem_samp, { COMMON54PLUS, a_unknown } },
    { elem_scalarproduct, { MATH3DEFCOM, a_unknown } },
    { elem_script, {    a_async, a_charset, a_crossorigin, a_defer, a_externalresourcesrequired, a_implements, a_integrity, a_language, a_nomodule, a_referrerpolicy,
                        a_type, SVG11XLINK, SVGREPL, COMMON54, a_unknown } },
    { elem_sdev, { MATH3DEFCOM, a_unknown } },
    { elem_sec, { MATH3DEFCOM, a_unknown } },
    { elem_sech, { MATH3DEFCOM, a_unknown } },
    { elem_section, { COMMON54, a_unknown } },
    { elem_select, {    a_align, a_autocomplete, a_disabled, a_error, a_form, a_md, a_multiple, a_name, a_required, a_several, a_size, a_units, WIDEHIGH, RESERVED4,
                        COMMON54, a_unknown } },
    { elem_selector, { MATH3DEFCOM, a_unknown } },
    { elem_semantics, { a_cd, a_name, a_src, MATH3DEFCOM, a_unknown } },
    { elem_sep, { a_xmlns, a_unknown } },
    { elem_separator, { XHTML2, a_unknown } },
    { elem_set, { a_externalresourcesrequired, a_fill, a_to, a_type, MATH2UNIQUE, SVG11ANAT, SVG11ANTIME, SVG11ANEV, SVG11XLINK, SVG20COND, COMMON54, a_unknown } },
    { elem_setdiff, { MATH3DEFCOM, a_unknown } },
    { elem_shadow, { COMMON54, a_unknown } },
    { elem_share, { a_src, MATH3COMMON, a_unknown } },
    { elem_sidebar, { COMMON5, a_unknown } },
    { elem_sin, { MATH3DEFCOM, a_unknown } },
    { elem_sinh, { MATH3DEFCOM, a_unknown } },
    { elem_slot, { a_name, COMMON54, a_unknown } },
    { elem_small, { COMMON54, a_unknown } },
    { elem_solidcolour, { COMMON54, a_unknown } },
    { elem_source, { a_sizes, a_srcset, a_type, COMMON54, a_unknown } },
    { elem_spacer, { a_align, a_size, a_type, WIDEHIGH, a_unknown } },
    { elem_span, { a_align, RESERVED4, COMMON54, a_unknown } },
    { elem_spot, { a_id, a_unknown } },
    { elem_sqrt, { LANGCLASS3, a_unknown } },
    { elem_standby, { MATH3DEFCOM, a_unknown } },
    { elem_stop, { a_offset, SVGPRES, COMMON54, a_unknown } },
    { elem_stoppropagation, { XHTML2, a_unknown } },
    { elem_strike, { COMMON4, a_unknown } },
    { elem_strong, { COMMON54PLUS, a_unknown } },
    { elem_style, { a_disabled, a_notation, a_scoped, a_type, COMMON54, a_unknown } },
    { elem_sub, { a_align, COMMON54PLUS, a_unknown } },
    { elem_subset, { MATH3DEFCOM , a_unknown } },
    { elem_sum, { MATH3DEFCOM, a_unknown } },
    { elem_summary, { COMMON54, a_unknown } },
    { elem_sup, { a_align, COMMON54PLUS, a_unknown } },
    { elem_svg, {   a_allow_zoom_pan, a_baseprofile, a_contentscripttype, a_contentstyletype, a_externalresourcesrequired, a_onzoom, a_playbackorder,
                    a_systemrequired, a_snapshottime, a_timelinebegin, a_transform, a_version, a_viewbox, a_zoomandpan, SVG11GREV, SVGBOX, SVGFIT, SVGREF, SVG20COND,
                    SVGPRES, COMMON54PLUS, a_unknown } },
    { elem_switch, { a_externalresourcesrequired, SVG11GREV, SVGG, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_symbol, { a_externalresourcesrequired, a_viewbox, SVG11GREV, SVGBOX, SVGFIT, SVGREF, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_t, { a_class, a_unknown } },
    { elem_tab, { a_align, a_at, a_dp, a_indent, a_to, LANGCLASS3, a_unknown } },
    { elem_table, { a_align, a_background, a_bgcolour, a_border, a_cellspacing, a_cellpadding, a_clear, a_cols, a_colspec, a_dp, a_frame, a_noflow, a_nowrap,
                    a_rules, a_sortable, a_summary, a_units, a_width, RESERVED4, COMMON54PLUS, a_unknown } },
    { elem_tan, { MATH3DEFCOM, a_unknown } },
    { elem_tanh, { MATH3DEFCOM, a_unknown } },
    { elem_tbody, { a_bgcolour, a_rowgroup, ALIGNCHAR, COMMON54, a_unknown } },
    { elem_tbreak, { COMMON54, a_unknown } },
    { elem_td, { a_axes, a_axis, a_background, a_bgcolour, a_cell, a_colspan, a_dp, a_headers, a_nowrap, a_rowspan, a_scope, WIDEHIGH, ALIGNCHAR, COMMON54PLUS, a_unknown } },
    { elem_template, { COMMON54, a_unknown } },
    { elem_text, { a_externalresourcesrequired, a_lengthadjust, a_rotate, a_textlength, SVG11GREV, SVGDXY, SVG20COND, SVGPRES, SVGXY, SVGG, COMMON54, a_unknown } },
    { elem_tendsto, { a_type, MATH3DEFCOM, a_unknown } },
    { elem_textarea, {  a_align, a_autocomplete, a_cols, a_dirname, a_disabled, a_error, a_form, a_maxlength, a_minlength, a_name, a_placeholder, a_readonly, a_required,
                        a_rows, a_wrap, COMMON54, a_unknown } },
    { elem_textpath, { a_externalresourcesrequired, a_method, a_spacing, a_start_offset, a_startoffset, SVG11GREV, SVG11XLINK, SVG20COND, SVGPRES, SVGREPL, COMMON54, a_unknown } },
    { elem_tfoot, { a_bgcolour, a_rowgroup, ALIGNCHAR, RESERVED4, COMMON54PLUS, a_unknown } },
    { elem_th, { a_axis, a_abbr, a_bgcolour, a_colspan, a_dp, a_headers, a_nowrap, a_rowspan, a_scope, a_sorted, WIDEHIGH, ALIGNCHAR, COMMON54PLUS, a_unknown } },
    { elem_thead, { a_bgcolour, a_rowgroup, ALIGNCHAR, COMMON54, a_unknown } },
    { elem_tilde, { LANGCLASS3, a_unknown } },
    { elem_time, { a_datetime, COMMON54, a_unknown } },
    { elem_times, { MATH3DEFCOM, a_unknown } },
    { elem_title, { a_systemrequired, COMMON54PLUS, a_unknown } },
    { elem_tr, { a_bgcolour, a_dp, a_nowrap, a_row, ALIGNCHAR, COMMON54, a_unknown } },
    { elem_track, { a_default, a_kind, a_label, a_srclang, COMMON54, a_unknown } },
    { elem_traitdef, { COMMON54, a_unknown } },
    { elem_transition, { COMMON54, a_unknown } },
    { elem_transformer, { COMMON54, a_unknown } },
    { elem_transpose, { MATH3DEFCOM, a_unknown } },
    { elem_tref, { a_externalresourcesrequired, SVG11GREV, SVG11XLINK, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_true, { MATH3DEFCOM, a_unknown } },
    { elem_tspan, { a_externalresourcesrequired, a_lengthadjust, a_rotate, a_textlength, SVG11GREV, SVGDXY, SVG20COND, SVGPRES, SVGG, SVGXY, SVGREPL, COMMON54, a_unknown } },
    { elem_tt, { TSLPLUS, XHTML, a_unknown } },
    { elem_u, { COMMON54PLUS, a_unknown } },
    { elem_ul, { a_align, a_clear, a_compact, a_plain, a_type, a_wrap, COMMON54PLUS, a_unknown } },
    { elem_union, { MATH3DEFCOM, a_unknown } },
    { elem_uplimit, { MATH3COMMON, a_unknown } },
    { elem_use, { a_externalresourcesrequired, a_xlinkhref, SVG11GREV, SVGBOX, SVGFIT, SVGG, SVGREPL, SVG20COND, SVGPRES, COMMON54, a_unknown } },
    { elem_var, { COMMON54PLUS, a_unknown } },
    { elem_variance, { MATH3DEFCOM, a_unknown } },
    { elem_veaffine, { COMMON54, a_unknown } },
    { elem_vec, { LANGCLASS3, a_unknown } },
    { elem_vector, { MATH3COMMON, a_unknown } },
    { elem_vectoreffect, { COMMON54, a_unknown } },
    { elem_vectorproduct, { MATH3DEFCOM, a_unknown } },
    { elem_veexclude, { COMMON54, a_unknown } },
    { elem_vefill, { COMMON54, a_unknown } },
    { elem_veintersect, { COMMON54, a_unknown } },
    { elem_vejoin, { COMMON54, a_unknown } },
    { elem_vemarker, { COMMON54, a_unknown } },
    { elem_vemarkerpath, { COMMON54, a_unknown } },
    { elem_vepath, { COMMON54, a_unknown } },
    { elem_vepathref, { COMMON54, a_unknown } },
    { elem_vereverse, { COMMON54, a_unknown } },
    { elem_vesetback, { COMMON54, a_unknown } },
    { elem_vestroke, { COMMON54, a_unknown } },
    { elem_vestrokepath, { COMMON54, a_unknown } },
    { elem_veunion, { COMMON54, a_unknown } },
    { elem_video, { a_autopictureinpicture, a_autoplay, a_buffered, a_controls, a_controlslist, a_crossorigin, a_currenttime, a_disablepictureinpicture,
                    a_disableremoteplayback, a_duration, a_intrinsicsize, a_loop, a_mediagroup, a_muted, a_playsinline, a_poster, a_preload, WIDEHIGH, COMMON54, a_unknown } },
    { elem_view, { a_externalresourcesrequired, a_preserveaspectratio, a_viewbox, a_viewtarget, a_zoomandpan, COMMON54, a_unknown } },
    { elem_vkern, { a_g1, a_g2, a_k, a_u1, a_u2, COMMON54, a_unknown } },
    { elem_wbr, { COMMON54, a_unknown } },
    { elem_xa, { COMMON54, a_unknown } },
    { elem_xml, { a_id, a_src, a_unknown } },
    { elem_xmp, { LANGCLASS, a_unknown } },
    { elem_xor, { MATH3DEFCOM, a_unknown } },
    { elem_error, { a_unknown } } };

const size_t vebs_size = last_element_tag + 1;
typedef ::std::array < attribute_bitset, vebs_size > vebs_t;
vebs_t vebs;

void elements_init (nitpick& nits)
{   vebs.fill (attribute_bitset ());
    for (int i = 0; ei [i].tag_ != elem_error; ++i)
    {   if (vebs.at (ei [i].tag_).any ())
            nits.pick (nit_repeated_attribute, es_warning, ec_program, elem::name (ei [i].tag_), " repeated in bitset init");
        for (int j = 0; ei [i].a_ [j] != a_unknown; ++j)
            if (vebs.at (ei [i].tag_).test (ei [i].a_ [j]))
                nits.pick (nit_repeated_attribute, es_warning, ec_program, "attribute ", attr::name (ei [i].a_ [j]), " repeated in ", elem::name (ei [i].tag_), " bitset init");
            else vebs.at (ei [i].tag_).set (ei [i].a_ [j]); } }

attribute_bitset element_attributes (const e_element e)
{   assert (e < vebs.size ());
    if (e >= vebs.size ()) return attribute_bitset ();
    return vebs.at (e); }

bool has_attribute (const e_element e, const e_attribute a)
{   assert (e < vebs.size ());
    if (e >= vebs.size ()) return false;
    return vebs.at (e).test (a); }
