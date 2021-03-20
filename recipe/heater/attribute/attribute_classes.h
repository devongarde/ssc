/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "attribute/attribute.h"

typedef typed_attribute < t_unknown, a_unknown > attr_unknown;
typedef typed_attribute < t_generic, a_abbr > attr_abbr;
typedef typed_attribute < t_curie_safe, a_about > attr_about;
typedef typed_attribute < t_idref, a_above > attr_above;
typedef typed_attribute < t_bool, a_accent > attr_accent;
typedef typed_attribute < t_real, a_accentheight > attr_accentheight;
typedef typed_attribute < t_bool, a_accentunder > attr_accentunder;
typedef typed_attribute < t_accept, a_accept > attr_accept;
typedef typed_attribute < t_charsets, a_acceptcharset > attr_acceptcharset;
typedef typed_attribute < t_key, a_accesskey > attr_accesskey;
typedef typed_attribute < t_accumulate, a_accumulate > attr_accumulate;
typedef typed_attribute < t_url, a_action > attr_action;
typedef typed_attribute < t_actiontype, a_actiontype > attr_actiontype;
typedef typed_attribute < t_bool, a_activate > attr_activate;
typedef typed_attribute < t_actuate, a_actuate > attr_actuate;
typedef typed_attribute < t_additive, a_additive > attr_additive;
typedef typed_attribute < t_align, a_align > attr_align;
typedef typed_attribute < t_alignmentbaseline, a_alignmentbaseline > attr_alignmentbaseline;
typedef typed_attribute < t_bools, a_alignmentscope > attr_alignmentscope;
typedef typed_attribute < t_colour, a_alink > attr_alink;
typedef typed_attribute < t_featurepolicy, a_allow > attr_allow;
typedef typed_attribute < t_html_boolean, a_allowfullscreen > attr_allowfullscreen;
typedef typed_attribute < t_html_boolean, a_allowpaymentrequest > attr_allowpaymentrequest;
typedef typed_attribute < t_html_boolean, a_allowusermedia > attr_allowusermedia;
typedef typed_attribute < t_bool, a_allow_zoom_pan > attr_allowzoompan;
typedef typed_attribute < t_real, a_alphabetic > attr_alphabetic;
typedef typed_attribute < t_text, a_alt > attr_alt;
typedef typed_attribute < t_url, a_altimg > attr_altimg;
typedef typed_attribute < t_measure, a_altimg_height > attr_altimg_height;
typedef typed_attribute < t_generic, a_altimg_valign > attr_altimg_valign;
typedef typed_attribute < t_measure, a_altimg_width > attr_altimg_width;
typedef typed_attribute < t_text, a_alttext > attr_alttext;
typedef typed_attribute < t_real, a_amplitude > attr_amplitude;
typedef typed_attribute < t_arabicform, a_arabicform > attr_arabicform;
typedef typed_attribute < t_urls, a_archive > attr_archive;
typedef typed_attribute < t_idref, a_ariaactivedescendant > attr_ariaactivedescendant;
typedef typed_attribute < t_bool, a_ariaatomic > attr_ariaatomic;
typedef typed_attribute < t_aria_autocomplete, a_ariaautocomplete > attr_ariaautocomplete;
typedef typed_attribute < t_bool, a_ariabusy > attr_ariabusy;
typedef typed_attribute < t_tfmu, a_ariachecked > attr_ariachecked;
typedef typed_attribute < t_idrefs, a_ariacontrols > attr_ariacontrols;
typedef typed_attribute < t_idrefs, a_ariadescribedby > attr_ariadescribedby;
typedef typed_attribute < t_bool, a_ariadisabled > attr_ariadisabled;
typedef typed_attribute < t_roles, a_ariadropeffect > attr_ariadropeffect;
typedef typed_attribute < t_tfu, a_ariaexpanded > attr_ariaexpanded;
typedef typed_attribute < t_idrefs, a_ariaflowto > attr_ariaflowto;
typedef typed_attribute < t_tfu, a_ariagrabbed > attr_ariagrabbed;
typedef typed_attribute < t_bool, a_ariahaspopup > attr_ariahaspopup;
typedef typed_attribute < t_bool, a_ariahidden > attr_ariahidden;
typedef typed_attribute < t_aria_invalidity, a_ariainvalid > attr_ariainvalid;
typedef typed_attribute < t_text, a_arialabel > attr_arialabel;
typedef typed_attribute < t_idrefs, a_arialabelledby > attr_arialabelledby;
typedef typed_attribute < t_text, a_arialevel > attr_arialevel;
typedef typed_attribute < t_aria_live, a_arialive > attr_arialive;
typedef typed_attribute < t_bool, a_ariamultiline > attr_ariamultiline;
typedef typed_attribute < t_bool, a_ariamultiselectable > attr_ariamultiselectable;
typedef typed_attribute < t_hv, a_ariaorientation > attr_ariaorientation;
typedef typed_attribute < t_idrefs, a_ariaowns > attr_ariaowns;
typedef typed_attribute < t_text, a_ariaposinset > attr_ariaposinset;
typedef typed_attribute < t_tfmu, a_ariapressed > attr_ariapressed;
typedef typed_attribute < t_bool, a_ariareadonly > attr_ariareadonly;
typedef typed_attribute < t_roles, a_ariarelevant > attr_ariarelevant;
typedef typed_attribute < t_bool, a_ariarequired > attr_ariarequired;
typedef typed_attribute < t_tfu, a_ariaselected > attr_ariaselected;
typedef typed_attribute < t_text, a_ariasetsize > attr_ariasetsize;
typedef typed_attribute < t_aria_sort, a_ariasort > attr_ariasort;
typedef typed_attribute < t_integer, a_ariavaluemax > attr_ariavaluemax;
typedef typed_attribute < t_integer, a_ariavaluemin > attr_ariavaluemin;
typedef typed_attribute < t_integer, a_ariavaluenow > attr_ariavaluenow;
typedef typed_attribute < t_text, a_ariavaluetext > attr_ariavaluetext;
typedef typed_attribute < t_as, a_as > attr_as;
typedef typed_attribute < t_real, a_ascent > attr_ascent;
typedef typed_attribute < t_html_boolean, a_async > attr_async;
typedef typed_attribute < t_integer, a_at > attr_at;
typedef typed_attribute < t_attributename, a_attributename > attr_attributename;
typedef typed_attribute < t_attributetype, a_attributetype > attr_attributetype;
typedef typed_attribute < t_html_boolean, a_audio > attr_audio;
typedef typed_attribute < t_html_boolean, a_autobuffer > attr_autobuffer;
typedef typed_attribute < t_autocapitalise, a_autocapitalise > attr_autocapitalise;
typedef typed_attribute < t_autocompletevaried, a_autocomplete > attr_autocomplete;
typedef typed_attribute < t_html_boolean, a_autocorrect > attr_autocorrect;
typedef typed_attribute < t_html_boolean, a_autofocus > attr_autofocus;
typedef typed_attribute < t_html_boolean, a_autopictureinpicture > attr_autopictureinpicture;
typedef typed_attribute < t_existential, a_autoplay > attr_autoplay;
typedef typed_attribute < t_existential, a_autosubmit > attr_autosubmit;
typedef typed_attribute < t_generic, a_axes > attr_axes;
typedef typed_attribute < t_generic, a_axis > attr_axis;
typedef typed_attribute < t_angle, a_azimuth > attr_azimuth;
typedef typed_attribute < t_background, a_background > attr_background;
typedef typed_attribute < t_integer, a_balance > attr_balance;
typedef typed_attribute < t_unsigned, a_bandwidth > attr_bandwidth;
typedef typed_attribute < t_base, a_base > attr_base;
typedef typed_attribute < t_real_1_2, a_basefrequency > attr_base_frequency;
typedef typed_attribute < t_measure, a_baseline > attr_baseline;
typedef typed_attribute < t_svg_baselineshift, a_baselineshift > attr_baselineshift;
typedef typed_attribute < t_svg_baseprofile, a_baseprofile > attr_baseprofile;
typedef typed_attribute < t_text, a_bbox > attr_bbox;
typedef typed_attribute < t_beginvaluelist, a_begin > attr_begin;
typedef typed_attribute < t_behaviour, a_behaviour > attr_behaviour;
typedef typed_attribute < t_idref, a_below > attr_below;
typedef typed_attribute < t_bool, a_bevelled > attr_bevelled;
typedef typed_attribute < t_colour, a_bgcolour > attr_bgcolour;
typedef typed_attribute < t_generic, a_bias > attr_bias;
typedef typed_attribute < t_border, a_border > attr_border;
typedef typed_attribute < t_unsigned, a_bottommargin > attr_bottommargin;
typedef typed_attribute < t_existential, a_box > attr_box;
typedef typed_attribute < t_existential, a_bubbles > attr_bubbles;
typedef typed_attribute < t_text, a_buffered > attr_buffered;
typedef typed_attribute < t_vid, a_by > attr_by;
typedef typed_attribute < t_calcmode, a_calcmode > attr_calcmode;
typedef typed_attribute < t_existential, a_cancelable > attr_cancelable;
typedef typed_attribute < t_real, a_capheight > attr_capheight;
typedef typed_attribute < t_capture, a_capture > attr_capture;
typedef typed_attribute < t_url, a_cdgroup > attr_cdgroup;
typedef typed_attribute < t_text, a_cd > attr_cd;
typedef typed_attribute < t_generic, a_cell > attr_cell;
typedef typed_attribute < t_generic, a_cellpadding > attr_cellpadding;
typedef typed_attribute < t_generic, a_cellspacing > attr_cellspacing;
typedef typed_attribute < t_generic, a_challenge > attr_challenge;
typedef typed_attribute < t_char, a_char > attr_char;
typedef typed_attribute < t_lcralign, a_charalign > attr_charalign;
typedef typed_attribute < t_generic, a_charoff > attr_charoff;
typedef typed_attribute < t_charset, a_charset > attr_charset;
typedef typed_attribute < t_charspacing, a_charspacing > attr_charspacing;
typedef typed_attribute < t_existential, a_checked > attr_checked;
typedef typed_attribute < t_url, a_cite > attr_cite;
typedef typed_attribute < t_class, a_class > attr_class;
typedef typed_attribute < t_url, a_classid > attr_classid;
typedef typed_attribute < t_clear, a_clear > attr_clear;
typedef typed_attribute < t_clip, a_clip > attr_clip;
typedef typed_attribute < t_marker, a_clip_path > attr_clip_path;
typedef typed_attribute < t_fillrule, a_clip_rule > attr_clip_rule;
typedef typed_attribute < t_coordinatesystem, a_clippathunits > attr_clippathunits;
typedef typed_attribute < t_text, a_close > attr_close;
typedef typed_attribute < t_closure, a_closure > attr_closure;
typedef typed_attribute < t_local_url, a_code > attr_code;
typedef typed_attribute < t_generic, a_codebase > attr_codebase;
typedef typed_attribute < t_mime, a_codetype > attr_codetype;
typedef typed_attribute < t_text, a_coldef > attr_coldef;
typedef typed_attribute < t_colour_v, a_colour > attr_colour;
typedef typed_attribute < t_colourinterpolation, a_colour_interpolation > attr_colour_interpolation;
typedef typed_attribute < t_colourinterpolation, a_colour_interpolation_filters > attr_colour_interpolation_filters;
typedef typed_attribute < t_generic, a_colour_profile > attr_colour_profile;
typedef typed_attribute < t_colourrendering, a_colour_rendering > attr_colour_rendering;
typedef typed_attribute < t_rowscols, a_cols > attr_cols;
typedef typed_attribute < t_unsigned, a_colspan > attr_colspan;
typedef typed_attribute < t_generic, a_colspec > attr_colspec;
typedef typed_attribute < t_lcraligns, a_columnalign > attr_columnalign;
typedef typed_attribute < t_nsds, a_columnlines > attr_columnlines;
typedef typed_attribute < t_mathspace, a_columnspacing > attr_columnspacing;
typedef typed_attribute < t_unsigned, a_columnspan > attr_columnspan;
typedef typed_attribute < t_mathspacefit, a_columnwidth > attr_columnwidth;
typedef typed_attribute < t_compact, a_compact > attr_compact;
typedef typed_attribute < t_text, a_content > attr_content;
typedef typed_attribute < t_truefalseempty, a_contenteditable > attr_contenteditable;
typedef typed_attribute < t_unsigned, a_contentlength > attr_contentlength;
typedef typed_attribute < t_mime, a_contentscripttype > attr_contentscripttype;
typedef typed_attribute < t_mime, a_contentstyletype > attr_contentstyletype;
typedef typed_attribute < t_context_menu, a_contextmenu > attr_contextmenu;
typedef typed_attribute < t_existential, a_continue > attr_continue;
typedef typed_attribute < t_html_boolean, a_controls > attr_controls;
typedef typed_attribute < t_controlslist, a_controlslist > attr_controlslist;
typedef typed_attribute < t_coords, a_coords > attr_coords;
typedef typed_attribute < t_cors, a_crossorigin > attr_crossorigin;
typedef typed_attribute < t_crossout, a_crossout > attr_crossout;
typedef typed_attribute < t_csp, a_csp > attr_csp;
typedef typed_attribute < t_real, a_currenttime > attr_currenttime;
typedef typed_attribute < t_cursor_f, a_cursor > attr_cursor;
typedef typed_attribute < t_measure, a_cx > attr_cx;
typedef typed_attribute < t_measure, a_cy > attr_cy;
typedef typed_attribute < t_d, a_d > attr_d;
typedef typed_attribute < t_url, a_data > attr_data;
typedef typed_attribute < t_text, a_datafld > attr_datafld;
typedef typed_attribute < t_dataformatas, a_dataformatas > attr_dataformatas;
typedef typed_attribute < t_url, a_datasrc > attr_datasrc;
typedef typed_attribute < t_data, a_datawild > attr_datastar;
typedef typed_attribute < t_curie, a_datatype > attr_datatype;
typedef typed_attribute < t_datetime, a_datetime > attr_datetime;
typedef typed_attribute < t_char, a_decimalpoint > attr_decimalpoint;
typedef typed_attribute < t_existential, a_declare > attr_declare;
typedef typed_attribute < t_decoding, a_decoding > attr_decoding;
typedef typed_attribute < t_html_boolean, a_default > attr_default;
typedef typed_attribute < t_defaultaction, a_defaultaction > attr_defaultaction;
typedef typed_attribute < t_html_boolean, a_defer > attr_defer;
typedef typed_attribute < t_url, a_definitionurl > attr_definition;
typedef typed_attribute < t_lcralign, a_denomalign > attr_denomalign;
typedef typed_attribute < t_depth, a_depth > attr_depth;
typedef typed_attribute < t_real, a_descent > attr_descent;
typedef typed_attribute < t_real, a_diffuseconstant > attr_diffuse_constant;
typedef typed_attribute < t_dingbat, a_dingbat > attr_dingbat;
typedef typed_attribute < t_dir, a_dir > attr_dir;
typedef typed_attribute < t_direction, a_direction > attr_direction;
typedef typed_attribute < t_generic, a_dirname > attr_dirname;
typedef typed_attribute < t_existential, a_disabled > attr_disabled;
typedef typed_attribute < t_existential, a_disablepictureinpicture > attr_disablepictureinpicture;
typedef typed_attribute < t_html_boolean, a_disableremoteplayback > attr_disableremoteplayback;
typedef typed_attribute < t_display, a_display > attr_display;
typedef typed_attribute < t_bool, a_displaystyle > attr_displaystyle;
typedef typed_attribute < t_generic, a_divisor > attr_divisor;
typedef typed_attribute < t_dominantbaseline, a_dominantbaseline > attr_dominantbaseline;
typedef typed_attribute < t_filename, a_download > attr_download;
typedef typed_attribute < t_char, a_dp > attr_dp;
typedef typed_attribute < t_bool, a_draggable > attr_draggable;
typedef typed_attribute < t_text, a_dropzone > attr_dropzone;
typedef typed_attribute < t_dur, a_dur > attr_dur;
typedef typed_attribute < t_real, a_duration > attr_duration;
typedef typed_attribute < t_measure_or_more, a_dx > attr_dx;
typedef typed_attribute < t_measure_or_more, a_dy > attr_dy;
typedef typed_attribute < t_lralign, a_edge > attr_edge;
typedef typed_attribute < t_edgemode, a_edgemode > attr_edgemode;
typedef typed_attribute < t_edit, a_edit > attr_edit;
typedef typed_attribute < t_generic, a_editable > attr_editable;
typedef typed_attribute < t_effect, a_effect > attr_effect;
typedef typed_attribute < t_angle, a_elevation > attr_elevation;
typedef typed_attribute < t_text, a_encoding > attr_encoding;
typedef typed_attribute < t_enctype, a_enctype > attr_enctype;
typedef typed_attribute < t_enablebackground, a_enablebackground > attr_enablebackground;
typedef typed_attribute < t_end, a_end > attr_end;
typedef typed_attribute < t_enterkeyhint, a_enterkeyhint > attr_enterkeyhint;
typedef typed_attribute < t_generic, a_equalcolumns > attr_equalcolumns;
typedef typed_attribute < t_generic, a_equalrows > attr_equalrows;
typedef typed_attribute < t_existential, a_error > attr_error;
typedef typed_attribute < t_text, a_event > attr_event;
typedef typed_attribute < t_idref, a_eventtarget > attr_eventtarget;
typedef typed_attribute < t_generic, a_evevent > attr_evevent;
typedef typed_attribute < t_real, a_exponent > attr_exponent;
typedef typed_attribute < t_generic, a_exportparts > attr_exportparts;
typedef typed_attribute < t_bool, a_externalresourcesrequired > attr_externalresourcesrequired;
typedef typed_attribute < t_text, a_face > attr_face;
typedef typed_attribute < t_bool, a_fence > attr_fence;
typedef typed_attribute < t_fill, a_fill > attr_fill;
typedef typed_attribute < t_generic, a_fill_opacity > attr_fill_opacity;
typedef typed_attribute < t_fillrule, a_fill_rule > attr_fill_rule;
typedef typed_attribute < t_marker, a_filter > attr_filter;
typedef typed_attribute < t_filter_res, a_filterres > attr_filterres;
typedef typed_attribute < t_coordinatesystem, a_filterunits > attr_filterunits;
typedef typed_attribute < t_svg_units, a_filter_units > attr_filter_units;
typedef typed_attribute < t_2pt, a_fitbbox > attr_fitbbox;
typedef typed_attribute < t_2pt, a_fitboxtoviewport > attr_fitboxtoviewport;
typedef typed_attribute < t_measure, a_flatness > attr_flatness;
typedef typed_attribute < t_marker, a_flood_colour > attr_flood_colour;
typedef typed_attribute < t_opacity, a_flood_opacity > attr_flood_opacity;
typedef typed_attribute < t_tfa, a_focusable > attr_focusable;
typedef typed_attribute < t_generic, a_focushighlight > attr_focushighlight;
typedef typed_attribute < t_font, a_font > attr_font;
typedef typed_attribute < t_fontfamily, a_font_family > attr_font_family;
typedef typed_attribute < t_fontsize, a_font_size > attr_font_size;
typedef typed_attribute < t_fontsizeadjust, a_font_size_adjust > attr_font_size_adjust;
typedef typed_attribute < t_fontstretch, a_font_stretch > attr_font_stretch;
typedef typed_attribute < t_fontstyle, a_font_style > attr_font_style;
typedef typed_attribute < t_fontvariant, a_font_variant > attr_font_variant;
typedef typed_attribute < t_fontweight, a_font_weight > attr_font_weight;
typedef typed_attribute < t_fontfamily, a_fontfamily > attr_fontfamily;
typedef typed_attribute < t_vunit, a_fontsize > attr_fontsize;
typedef typed_attribute < t_fontstretch, a_fontstretch > attr_fontstretch;
typedef typed_attribute < t_fontstyle, a_fontstyle > attr_fontstyle;
typedef typed_attribute < t_fontvariant, a_fontvariant > attr_fontvariant;
typedef typed_attribute < t_fontweight, a_fontweight > attr_fontweight;
typedef typed_attribute < t_idref, a_for > attr_for;
typedef typed_attribute < t_form, a_form > attr_form;
typedef typed_attribute < t_url, a_formaction > attr_formaction;
typedef typed_attribute < t_text, a_format > attr_format;
typedef typed_attribute < t_enctype, a_formenctype > attr_formenctype;
typedef typed_attribute < t_method, a_formmethod > attr_formmethod;
typedef typed_attribute < t_existential, a_formnovalidate > attr_formnovalidate;
typedef typed_attribute < t_onoff, a_forms > attr_forms;
typedef typed_attribute < t_target, a_formtarget > attr_formtarget;
typedef typed_attribute < t_generic, a_fr > attr_fr;
typedef typed_attribute < t_frame, a_frame > attr_frame;
typedef typed_attribute < t_10, a_frameborder > attr_frameborder;
typedef typed_attribute < t_framespacing, a_framespacing > attr_framespacing;
typedef typed_attribute < t_vid, a_from > attr_from;
typedef typed_attribute < t_idref, a_full > attr_full;
typedef typed_attribute < t_url, a_function > attr_function;
typedef typed_attribute < t_measure, a_fx > attr_fx;
typedef typed_attribute < t_measure, a_fy > attr_fy;
typedef typed_attribute < t_glyphnames, a_g1 > attr_g1;
typedef typed_attribute < t_glyphnames, a_g2 > attr_g2;
typedef typed_attribute < t_existential, a_generator_unable > attr_generatorunable;
typedef typed_attribute < t_angle_ai, a_glyph_orientation_vertical > attr_glyph_orientation_vertical;
typedef typed_attribute < t_glyphname, a_glyphname > attr_glyphname;
typedef typed_attribute < t_angle_i, a_glyphorientation_horizontal > attr_glyphorientation_horizontal;
typedef typed_attribute < t_text, a_glyphref > attr_glyphref;
typedef typed_attribute < t_transform, a_gradienttransform > attr_gradienttransform;
typedef typed_attribute < t_svg_units, a_gradient_units > attr_gradient_units;
typedef typed_attribute < t_coordinatesystem, a_gradientunits > attr_gradientunits;
typedef typed_attribute < t_groupalign, a_groupalign > attr_groupalign;
typedef typed_attribute < t_integer, a_gutter > attr_gutter;
typedef typed_attribute < t_url, a_handler > attr_handler;
typedef typed_attribute < t_real, a_hanging > attr_hanging;
typedef typed_attribute < t_idrefs, a_headers > attr_headers;
typedef typed_attribute < t_height, a_height > attr_height;
typedef typed_attribute < t_existential, a_hidden > attr_hidden;
typedef typed_attribute < t_real, a_high > attr_high;
typedef typed_attribute < t_real, a_horizadvx > attr_horizadvx;
typedef typed_attribute < t_real, a_horizoriginx > attr_horizoriginx;
typedef typed_attribute < t_real, a_horizoriginy > attr_horizoriginy;
typedef typed_attribute < t_url, a_href > attr_href;
typedef typed_attribute < t_lang, a_hreflang > attr_hreflang;
typedef typed_attribute < t_media, a_hrefmedia > attr_hrefmedia;
typedef typed_attribute < t_mimelist, a_hreftype > attr_hreftype;
typedef typed_attribute < t_integer, a_hspace > attr_hspace;
typedef typed_attribute < t_existential, a_html > attr_html;
typedef typed_attribute < t_httpequiv, a_httpequiv > attr_httpequiv;
typedef typed_attribute < t_url, a_icon > attr_icon;
typedef typed_attribute < t_id, a_id > attr_id;
typedef typed_attribute < t_real, a_ideographic > attr_ideographic;
typedef typed_attribute < t_idref, a_idref > attr_idref;
typedef typed_attribute < t_conditional, a_if > attr_if;
typedef typed_attribute < t_imagerendering, a_imagerendering > attr_imagerendering;
typedef typed_attribute < t_url, a_imagemap > attr_imagemap;
typedef typed_attribute < t_sizes, a_imagesizes > attr_imagesizes;
typedef typed_attribute < t_srcset, a_imagesrcset > attr_imagesrcset;
typedef typed_attribute < t_url, a_implements > attr_implements;
typedef typed_attribute < t_importance, a_importance > attr_importance;
typedef typed_attribute < t_in, a_in2 > attr_in2;
typedef typed_attribute < t_in, a_in > attr_in;
typedef typed_attribute < t_html_boolean, a_incremental > attr_incremental;
typedef typed_attribute < t_unsigned, a_indent > attr_indent;
typedef typed_attribute < t_indentalign, a_indentalign > attr_indentalign;
typedef typed_attribute < t_indentalign2, a_indentalignfirst > attr_indentalignfirst;
typedef typed_attribute < t_indentalign2, a_indentalignlast > attr_indentalignlast;
typedef typed_attribute < t_measure, a_indentshift > attr_indentshift;
typedef typed_attribute < t_indentshift2, a_indentshiftfirst > attr_indentshiftfirst;
typedef typed_attribute < t_indentshift2, a_indentshiftlast > attr_indentshiftlast;
typedef typed_attribute < t_idref, a_indenttarget > attr_indenttarget;
typedef typed_attribute < t_index, a_index > attr_index;
typedef typed_attribute < t_html_boolean, a_inert > attr_inert;
typedef typed_attribute < t_infixlinebreakstyle, a_infixlinebreakstyle > attr_infixlinebreakstyle;
typedef typed_attribute < t_generic, a_initialvisibility > attr_initialvisibility;
typedef typed_attribute < t_inlist, a_inlist > attr_inlist;
typedef typed_attribute < t_inputmode, a_inputmode > attr_inputmode;
typedef typed_attribute < t_text, a_integrity > attr_integrity;
typedef typed_attribute < t_real, a_intercept > attr_intercept;
typedef typed_attribute < t_text, a_intrinsicsize > attr_intrinsicsize;
typedef typed_attribute < t_html_boolean, a_irrelevant > attr_irrelevant;
typedef typed_attribute < t_is, a_is > attr_is;
typedef typed_attribute < t_existential, a_ismap > attr_ismap;
typedef typed_attribute < t_existential, a_item > attr_item;
typedef typed_attribute < t_itemid, a_itemid > attr_itemid;
typedef typed_attribute < t_itemprop, a_itemprop > attr_itemprop;
typedef typed_attribute < t_idrefs, a_itemref > attr_itemref;
typedef typed_attribute < t_existential, a_itemscope > attr_itemscope;
typedef typed_attribute < t_itemtype, a_itemtype > attr_itemtype;
typedef typed_attribute < t_yesno, a_itstranslate > attr_itstranslate;
typedef typed_attribute < t_real, a_k > attr_k;
typedef typed_attribute < t_real, a_k1 > attr_k1;
typedef typed_attribute < t_real, a_k2 > attr_k2;
typedef typed_attribute < t_real, a_k3 > attr_k3;
typedef typed_attribute < t_real, a_k4 > attr_k4;
typedef typed_attribute < t_generic, a_kernelmatrix > attr_kernelmatrix;
typedef typed_attribute < t_real_1_2, a_kernelunitlength > attr_kernelunitlength;
typedef typed_attribute < t_measure_ai, a_kerning > attr_kerning;
typedef typed_attribute < t_text, a_key > attr_key;
typedef typed_attribute < t_generic, a_keyparams > attr_keyparams;
typedef typed_attribute < t_generic, a_keypoints > attr_keypoints;
typedef typed_attribute < t_normalisations, a_keysplines > attr_keysplines;
typedef typed_attribute < t_normalisations, a_keytimes > attr_keytimes;
typedef typed_attribute < t_keytype, a_keytype > attr_keytype;
typedef typed_attribute < t_kind, a_kind > attr_kind;
typedef typed_attribute < t_generic, a_label > attr_label;
typedef typed_attribute < t_existential, a_labels > attr_labels;
typedef typed_attribute < t_lang, a_lang > attr_lang;
typedef typed_attribute < t_mime, a_language > attr_language;
typedef typed_attribute < t_bool, a_largeop > attr_largeop;
typedef typed_attribute < t_layout, a_layout > attr_layout;
typedef typed_attribute < t_char, a_ldelim > attr_ldelim;
typedef typed_attribute < t_unsigned, a_left > attr_left;
typedef typed_attribute < t_unsigned, a_leftmargin > attr_leftmargin;
typedef typed_attribute < t_measure, a_leftoverhang > attr_leftoverhang;
typedef typed_attribute < t_unsigned, a_length > attr_length;
typedef typed_attribute < t_lengthadjust, a_lengthadjust > attr_lengthadjust;
typedef typed_attribute < t_measure_ai, a_letter_spacing > attr_letter_spacing;
typedef typed_attribute < t_colour, a_lightcolour > attr_lightcolour;
typedef typed_attribute < t_marker, a_lighting_colour > attr_lighting_colour;
typedef typed_attribute < t_angle, a_limitingconeangle > attr_limitingconeangle;
typedef typed_attribute < t_linebreak, a_linebreak > attr_linebreak;
typedef typed_attribute < t_text, a_linebreakmultichar > attr_linebreakmultichar;
typedef typed_attribute < t_linebreakstyle, a_linebreakstyle > attr_linebreakstyle;
typedef typed_attribute < t_measure, a_lineleading > attr_lineleading;
typedef typed_attribute < t_linethickness, a_linethickness > attr_linethickness;
typedef typed_attribute < t_colour, a_link > attr_link;
typedef typed_attribute < t_idref, a_list > attr_list;
typedef typed_attribute < t_loading, a_loading > attr_loading;
typedef typed_attribute < t_id, a_local > attr_local;
typedef typed_attribute < t_mathlocation, a_location > attr_location;
typedef typed_attribute < t_url, a_longdesc > attr_longdesc;
typedef typed_attribute < t_longdivstyle, a_longdivstyle > attr_longdivstyle;
typedef typed_attribute < t_loop, a_loop > attr_loop;
typedef typed_attribute < t_unsigned, a_loopcount > attr_loopcount;
typedef typed_attribute < t_just_time, a_loopend > attr_loopend;
typedef typed_attribute < t_just_time, a_loopstart > attr_loopstart;
typedef typed_attribute < t_real, a_low > attr_low;
typedef typed_attribute < t_text, a_lquote > attr_lquote;
typedef typed_attribute < t_lspace, a_lspace > attr_lspace;
typedef typed_attribute < t_urls, a_macros > attr_macros;
typedef typed_attribute < t_url, a_manifest > attr_manifest;
typedef typed_attribute < t_unsigned, a_marginheight > attr_marginheight;
typedef typed_attribute < t_unsigned, a_marginwidth > attr_marginwidth;
typedef typed_attribute < t_marker, a_marker > attr_marker;
typedef typed_attribute < t_marker, a_marker_end > attr_marker_end;
typedef typed_attribute < t_marker, a_marker_mid > attr_marker_mid;
typedef typed_attribute < t_marker, a_marker_start > attr_marker_start;
typedef typed_attribute < t_measure, a_markerheight > attr_markerheight;
typedef typed_attribute < t_markerunits, a_markerunits > attr_markerunits;
typedef typed_attribute < t_measure, a_markerwidth > attr_markerwidth;
typedef typed_attribute < t_marker, a_mask > attr_mask;
typedef typed_attribute < t_coordinatesystem, a_maskcontentunits > attr_maskcontentunits;
typedef typed_attribute < t_svg_units, a_mask_units > attr_mask_units;
typedef typed_attribute < t_coordinatesystem, a_maskunits > attr_maskunits;
typedef typed_attribute < t_existential, a_math > attr_math;
typedef typed_attribute < t_colour, a_mathbackground > attr_mathbackground;
typedef typed_attribute < t_colour, a_mathcolour > attr_mathcolour;
typedef typed_attribute < t_real, a_mathematical > attr_mathematical;
typedef typed_attribute < t_mathsize, a_mathsize > attr_mathsize;
typedef typed_attribute < t_mathvariant, a_mathvariant > attr_mathvariant;
typedef typed_attribute < t_num, a_max > attr_max;
typedef typed_attribute < t_unsigned, a_maxlength > attr_maxlength;
typedef typed_attribute < t_mathspaceinfinity, a_maxsize > attr_maxsize;
typedef typed_attribute < t_measure, a_maxwidth > attr_maxwidth;
typedef typed_attribute < t_generic, a_md > attr_md;
typedef typed_attribute < t_mql, a_media > attr_media;
typedef typed_attribute < t_charset, a_mediacharacterencoding > attr_mediacharacterencoding;
typedef typed_attribute < t_content_encodings, a_mediacontentencodings > attr_mediacontentencodings;
typedef typed_attribute < t_generic, a_mediagroup > attr_mediagroup;
typedef typed_attribute < t_unsigned, a_mediasize > attr_mediasize;
typedef typed_attribute < t_duration, a_mediatime > attr_mediatime;
typedef typed_attribute < t_hunit, a_mediummathspace > attr_mediummathspace;
typedef typed_attribute < t_id, a_menu > attr_menu;
typedef typed_attribute < t_methodological, a_method > attr_method;
typedef typed_attribute < t_generic, a_methods > attr_methods;
typedef typed_attribute < t_num, a_min > attr_min;
typedef typed_attribute < t_mathspace, a_minilabelspacing > attr_minilabelspacing;
typedef typed_attribute < t_unsigned, a_minlength > attr_minlength;
typedef typed_attribute < t_mathspace, a_minsize > attr_minsize;
typedef typed_attribute < t_text, a_mode > attr_mode;
typedef typed_attribute < t_bool, a_movablelimits > attr_movablelimits;
typedef typed_attribute < t_mah, a_mozactionhint > attr_mozactionhint;
typedef typed_attribute < t_existential, a_mozbrowser > attr_mozbrowser;
typedef typed_attribute < t_linethickness, a_mslinethickness > attr_mslinethickness;
typedef typed_attribute < t_existential, a_multiple > attr_multiple;
typedef typed_attribute < t_html_boolean, a_muted > attr_muted;
typedef typed_attribute < t_not_empty, a_n > attr_n;
typedef typed_attribute < t_name, a_name > attr_name;
typedef typed_attribute < t_unsigned, a_nargs > attr_nargs;
typedef typed_attribute < t_navigation, a_navdown > attr_navdown;
typedef typed_attribute < t_navigation, a_navdownleft > attr_navdownleft;
typedef typed_attribute < t_navigation, a_navdownright > attr_navdownright;
typedef typed_attribute < t_navigation, a_navleft > attr_navleft;
typedef typed_attribute < t_navigation, a_navnext > attr_navnext;
typedef typed_attribute < t_navigation, a_navprev > attr_navprev;
typedef typed_attribute < t_navigation, a_navright > attr_navright;
typedef typed_attribute < t_navigation, a_navup > attr_navup;
typedef typed_attribute < t_navigation, a_navupleft > attr_navupleft;
typedef typed_attribute < t_navigation, a_navupright > attr_navupright;
typedef typed_attribute < t_idref, a_nextfocus > attr_nextfocus;
typedef typed_attribute < t_id, a_nodeid > attr_nodeid;
typedef typed_attribute < t_text, a_noflow > attr_noflow;
typedef typed_attribute < t_existential, a_nohref > attr_nohref;
typedef typed_attribute < t_measure, a_nominallength > attr_nominallength;
typedef typed_attribute < t_existential, a_nomodule > attr_nomodule;
typedef typed_attribute < t_existential, a_noresize > attr_noresize;
typedef typed_attribute < t_existential, a_noshade > attr_noshade;
typedef typed_attribute < t_notation, a_notation > attr_notation;
//typedef typed_attribute < t_generic, a_novalidate > attr_novalidate;
typedef typed_attribute < t_existential, a_novalidate > attr_novalidate;
typedef typed_attribute < t_existential, a_nowrap > attr_nowrap;
typedef typed_attribute < t_lcralign, a_numalign > attr_numalign;
typedef typed_attribute < t_text, a_numberonce > attr_numberonce;
typedef typed_attribute < t_real, a_numoctaves > attr_numoctaves;
typedef typed_attribute < t_generic, a_object > attr_object;
typedef typed_attribute < t_idref, a_observer > attr_observer;
typedef typed_attribute < t_occurence, a_occurrence > attr_occurrence;
typedef typed_attribute < t_measure, a_offset > attr_offset;
typedef typed_attribute < t_script, a_onabort > attr_onabort;
typedef typed_attribute < t_script, a_onactivate > attr_onactivate;
typedef typed_attribute < t_script, a_onafterprint > attr_onafterprint;
typedef typed_attribute < t_script, a_onautocomplete > attr_onautocomplete;
typedef typed_attribute < t_script, a_onautocompleteerror > attr_onautocompleteerror;
typedef typed_attribute < t_script, a_onauxclick > attr_onauxclick;
typedef typed_attribute < t_script, a_onbeforeprint > attr_onbeforeprint;
typedef typed_attribute < t_script, a_onbeforeunload > attr_onbeforeunload;
typedef typed_attribute < t_script, a_onbegin > attr_onbegin;
typedef typed_attribute < t_script, a_onblur > attr_onblur;
typedef typed_attribute < t_script, a_oncancel > attr_oncancel;
typedef typed_attribute < t_script, a_oncanplay > attr_oncanplay;
typedef typed_attribute < t_script, a_oncanplaythrough > attr_oncanplaythrough;
typedef typed_attribute < t_script, a_onchange > attr_onchange;
typedef typed_attribute < t_script, a_onclick > attr_onclick;
typedef typed_attribute < t_script, a_onclose > attr_onclose;
typedef typed_attribute < t_script, a_oncontextmenu > attr_oncontextmenu;
typedef typed_attribute < t_script, a_oncopy > attr_oncopy;
typedef typed_attribute < t_script, a_oncuechange > attr_oncuechange;
typedef typed_attribute < t_script, a_oncut > attr_oncut;
typedef typed_attribute < t_script, a_ondblclick > attr_ondblclick;
typedef typed_attribute < t_script, a_ondrag > attr_ondrag;
typedef typed_attribute < t_script, a_ondragend > attr_ondragend;
typedef typed_attribute < t_script, a_ondragenter > attr_ondragenter;
typedef typed_attribute < t_script, a_ondragexit > attr_ondragexit;
typedef typed_attribute < t_script, a_ondragleave > attr_ondragleave;
typedef typed_attribute < t_script, a_ondragover > attr_ondragover;
typedef typed_attribute < t_script, a_ondragstart > attr_ondragstart;
typedef typed_attribute < t_script, a_ondrop > attr_ondrop;
typedef typed_attribute < t_script, a_ondurationchange > attr_ondurationchange;
typedef typed_attribute < t_script, a_onemptied > attr_onemptied;
typedef typed_attribute < t_script, a_onend > attr_onend;
typedef typed_attribute < t_script, a_onended > attr_onended;
typedef typed_attribute < t_script, a_onevent > attr_onevent;
typedef typed_attribute < t_script, a_onerror > attr_onerror;
typedef typed_attribute < t_script, a_onfocus > attr_onfocus;
typedef typed_attribute < t_script, a_onfocusin > attr_onfocusin;
typedef typed_attribute < t_script, a_onfocusout > attr_onfocusout;
typedef typed_attribute < t_script, a_onformchange > attr_onformchange;
typedef typed_attribute < t_script, a_onformdata > attr_onformdata;
typedef typed_attribute < t_script, a_onforminput > attr_onforminput;
typedef typed_attribute < t_script, a_onfullscreenchange > attr_onfullscreenchange;
typedef typed_attribute < t_script, a_onfullscreenerror > attr_onfullscreenerror;
typedef typed_attribute < t_script, a_onhashchange > attr_onhashchange;
typedef typed_attribute < t_script, a_oninput > attr_oninput;
typedef typed_attribute < t_script, a_oninvalid > attr_oninvalid;
typedef typed_attribute < t_script, a_onkeydown > attr_onkeydown;
typedef typed_attribute < t_script, a_onkeypress > attr_onkeypress;
typedef typed_attribute < t_script, a_onkeyup > attr_onkeyup;
typedef typed_attribute < t_script, a_onlanguagechange > attr_onlanguagechange;
typedef typed_attribute < t_script, a_onload > attr_onload;
typedef typed_attribute < t_script, a_onloadeddata > attr_onloadeddata;
typedef typed_attribute < t_script, a_onloadedmetadata > attr_onloadedmetadata;
typedef typed_attribute < t_script, a_onloadend > attr_onloadend;
typedef typed_attribute < t_script, a_onloadstart > attr_onloadstart;
typedef typed_attribute < t_script, a_onmessage > attr_onmessage;
typedef typed_attribute < t_script, a_onmessageerror > attr_onmessageerror;
typedef typed_attribute < t_script, a_onmousedown > attr_onmousedown;
typedef typed_attribute < t_script, a_onmouseenter > attr_onmouseenter;
typedef typed_attribute < t_script, a_onmouseleave > attr_onmouseleave;
typedef typed_attribute < t_script, a_onmousemove > attr_onmousemove;
typedef typed_attribute < t_script, a_onmouseout > attr_onmouseout;
typedef typed_attribute < t_script, a_onmouseover > attr_onmouseover;
typedef typed_attribute < t_script, a_onmouseup > attr_onmouseup;
typedef typed_attribute < t_script, a_onmousewheel > attr_onmousewheel;
typedef typed_attribute < t_script, a_onoffline > attr_onoffline;
typedef typed_attribute < t_script, a_ononline > attr_ononline;
typedef typed_attribute < t_script, a_onpagehide > attr_onpagehide;
typedef typed_attribute < t_script, a_onpageshow > attr_onpageshow;
typedef typed_attribute < t_script, a_onpaste > attr_onpaste;
typedef typed_attribute < t_script, a_onpause > attr_onpause;
typedef typed_attribute < t_script, a_onplay > attr_onplay;
typedef typed_attribute < t_script, a_onplaying > attr_onplaying;
typedef typed_attribute < t_script, a_onpopstate > attr_onpopstate;
typedef typed_attribute < t_script, a_onprogress > attr_onprogress;
typedef typed_attribute < t_script, a_onratechange > attr_onratechange;
typedef typed_attribute < t_script, a_onreadystatechange > attr_onreadystatechange;
typedef typed_attribute < t_script, a_onredo > attr_onredo;
typedef typed_attribute < t_script, a_onrejectionhandled > attr_onrejectionhandled;
typedef typed_attribute < t_script, a_onrepeat > attr_onrepeat;
typedef typed_attribute < t_script, a_onreset > attr_onreset;
typedef typed_attribute < t_script, a_onresize > attr_onresize;
typedef typed_attribute < t_script, a_onscroll > attr_onscroll;
typedef typed_attribute < t_script, a_onsecuritypolicyviolation > attr_onsecuritypolicyviolation;
typedef typed_attribute < t_script, a_onseeking > attr_onseeking;
typedef typed_attribute < t_script, a_onselect > attr_onselect;
typedef typed_attribute < t_script, a_onshow > attr_onshow;
typedef typed_attribute < t_script, a_onslotchange > attr_onslotchange;
typedef typed_attribute < t_script, a_onsort > attr_onsort;
typedef typed_attribute < t_script, a_onsought > attr_onsought;
typedef typed_attribute < t_script, a_onstalled > attr_onstalled;
typedef typed_attribute < t_script, a_onstorage > attr_onstorage;
typedef typed_attribute < t_script, a_onsubmit > attr_onsubmit;
typedef typed_attribute < t_script, a_onsuspend > attr_onsuspend;
typedef typed_attribute < t_script, a_ontimeupdate > attr_ontimeupdate;
typedef typed_attribute < t_script, a_ontoggle > attr_ontoggle;
typedef typed_attribute < t_script, a_onundo > attr_onundo;
typedef typed_attribute < t_script, a_onunhandledrejection > attr_onunhandledrejection;
typedef typed_attribute < t_script, a_onunload > attr_onunload;
typedef typed_attribute < t_script, a_onvolumechange > attr_onvolumechange;
typedef typed_attribute < t_script, a_onwaiting > attr_onwaiting;
typedef typed_attribute < t_script, a_onwheel > attr_onwheel;
typedef typed_attribute < t_script, a_onzoom > attr_onzoom;
typedef typed_attribute < t_generic, a_opacity > attr_opacity;
typedef typed_attribute < t_open, a_open > attr_open;
typedef typed_attribute < t_operator, a_operator > attr_operator;
typedef typed_attribute < t_real, a_optimum > attr_optimum;
typedef typed_attribute < t_order, a_order > attr_order;
typedef typed_attribute < t_angle, a_orient > attr_orient;
typedef typed_attribute < t_orientation, a_orientation > attr_orientation;
typedef typed_attribute < t_origin, a_origin > attr_origin;
typedef typed_attribute < t_text, a_other > attr_other;
typedef typed_attribute < t_overflow, a_overflow > attr_overflow;
typedef typed_attribute < t_real, a_overlineposition > attr_overlineposition;
typedef typed_attribute < t_real, a_overlinethickness > attr_overlinethickness;
typedef typed_attribute < t_unsigned, a_pagex > attr_pagex;
typedef typed_attribute < t_unsigned, a_pagey > attr_pagey;
typedef typed_attribute < t_generic, a_paint_order > attr_paint_order;
typedef typed_attribute < t_panose1, a_panose1 > attr_panose1;
typedef typed_attribute < t_generic, a_part > attr_part;
typedef typed_attribute < t_generic, a_path > attr_path;
typedef typed_attribute < t_unsigned, a_pathlength > attr_pathlength;
typedef typed_attribute < t_regex, a_pattern > attr_pattern;
typedef typed_attribute < t_coordinatesystem, a_patterncontentunits > attr_patterncontentunits;
typedef typed_attribute < t_transform, a_patterntransform > attr_patterntransform;
typedef typed_attribute < t_coordinatesystem, a_patternunits > attr_patternunits;
typedef typed_attribute < t_svg_units, a_pattern_units > attr_pattern_units;
typedef typed_attribute < t_phase, a_phase > attr_phase;
typedef typed_attribute < t_urls, a_ping > attr_ping;
typedef typed_attribute < t_generic, a_placeholder > attr_placeholder;
typedef typed_attribute < t_existential, a_plain > attr_plain;
typedef typed_attribute < t_svg_playbackorder, a_playbackorder > attr_playbackorder;
typedef typed_attribute < t_unsigned, a_playcount > attr_playcount;
typedef typed_attribute < t_html_boolean, a_playsinline > attr_playsinline;
typedef typed_attribute < t_pointerevents, a_pointerevents > attr_pointerevents;
typedef typed_attribute < t_points, a_points > attr_points;
typedef typed_attribute < t_points, a_pointsatx > attr_pointsatx;
typedef typed_attribute < t_points, a_pointsaty > attr_pointsaty;
typedef typed_attribute < t_points, a_pointsatz > attr_pointsatz;
typedef typed_attribute < t_integer, a_position > attr_position;
typedef typed_attribute < t_generic, a_poster > attr_poster;
typedef typed_attribute < t_url, a_prefetch > attr_prefetch;
typedef typed_attribute < t_prefix, a_prefix > attr_prefix;
typedef typed_attribute < t_preload, a_preload > attr_preload;
typedef typed_attribute < t_bool, a_preservealpha > attr_preservealpha;
typedef typed_attribute < t_preserveaspectratio, a_preserveaspectratio > attr_preserveaspectratio;
typedef typed_attribute < t_idref, a_prevfocus > attr_prevfocus;
typedef typed_attribute < t_coordinatesystem, a_primitiveunits > attr_primitiveunits;
typedef typed_attribute < t_print, a_print > attr_print;
typedef typed_attribute < t_urls, a_profile > attr_profile;
typedef typed_attribute < t_generic, a_prompt > attr_prompt;
typedef typed_attribute < t_propagate, a_propagate > attr_propagate;
typedef typed_attribute < t_curies, a_property > attr_property;
typedef typed_attribute < t_datetime, a_pubdate > attr_pubdate;
typedef typed_attribute < t_existential, a_public > attr_public;
typedef typed_attribute < t_measure, a_r > attr_r;
typedef typed_attribute < t_idref, a_radiogroup > attr_radiogroup;
typedef typed_attribute < t_real_1_2, a_radius > attr_radius;
typedef typed_attribute < t_char, a_rdelim > attr_rdelim;
//typedef typed_attribute < t_html_boolean, a_readonly > attr_readonly;
typedef typed_attribute < t_existential, a_readonly > attr_readonly;
typedef typed_attribute < t_refx, a_refx > attr_refx;
typedef typed_attribute < t_refy, a_refy > attr_refy;
typedef typed_attribute < t_referrer, a_referrerpolicy > attr_referrerpolicy;
typedef typed_attribute < t_text, a_registrationmark > attr_registrationmark;
typedef typed_attribute < t_rel, a_rel > attr_rel;
typedef typed_attribute < t_renderingintent, a_renderingintent > attr_renderingintent;
typedef typed_attribute < t_repeatcount, a_repeatcount > attr_repeatcount;
typedef typed_attribute < t_dur_repeat, a_repeatdur > attr_repeatdur;
//typedef typed_attribute < t_html_boolean, a_required > attr_required;
typedef typed_attribute < t_existential, a_required > attr_required;
typedef typed_attribute < t_urls, a_requiredextensions > attr_requiredextensions;
typedef typed_attribute < t_svg_features, a_requiredfeatures > attr_requiredfeatures;
typedef typed_attribute < t_fontfamilies, a_requiredfonts > attr_requiredfonts;
typedef typed_attribute < t_mimelist, a_requiredformats > attr_requiredformats;
typedef typed_attribute < t_curie_safe, a_resource > attr_resource;
typedef typed_attribute < t_restart, a_restart > attr_restart;
typedef typed_attribute < t_result, a_result > attr_result;
typedef typed_attribute < t_unsigned, a_results > attr_results;
typedef typed_attribute < t_real, a_resultscale > attr_resultscale;
typedef typed_attribute < t_rel, a_rev > attr_rev;
typedef typed_attribute < t_html_boolean, a_reversed > attr_reversed;
typedef typed_attribute < t_measure, a_rightoverhang > attr_rightoverhang;
typedef typed_attribute < t_unsigned, a_rightmargin > attr_rightmargin;
typedef typed_attribute < t_role, a_role > attr_role;
typedef typed_attribute < t_rotate, a_rotate > attr_rotate;
typedef typed_attribute < t_generic, a_row > attr_row;
typedef typed_attribute < t_mathaligns, a_rowalign > attr_rowalign;
typedef typed_attribute < t_generic, a_rowgroup > attr_rowgroup;
typedef typed_attribute < t_nsds, a_rowlines > attr_rowlines;
typedef typed_attribute < t_rowscols, a_rows > attr_rows;
typedef typed_attribute < t_vunits, a_rowspacing > attr_rowspacing;
typedef typed_attribute < t_unsigned, a_rowspan > attr_rowspan;
typedef typed_attribute < t_text, a_rquote > attr_rquote;
typedef typed_attribute < t_mathspace, a_rspace > attr_rspace;
typedef typed_attribute < t_rules, a_rules > attr_rules;
typedef typed_attribute < t_measure, a_rx > attr_rx;
typedef typed_attribute < t_measure, a_ry > attr_ry;
typedef typed_attribute < t_sandboxen, a_sandbox > attr_sandbox;
typedef typed_attribute < t_real, a_scale > attr_scale;
typedef typed_attribute < t_generic, a_scheme > attr_scheme;
typedef typed_attribute < t_scope, a_scope > attr_scope;
typedef typed_attribute < t_generic, a_scoped > attr_scoped;
typedef typed_attribute < t_url, a_script > attr_script;
typedef typed_attribute < t_integer, a_scriptlevel > attr_scriptlevel;
typedef typed_attribute < t_vunit, a_scriptminsize > attr_scriptminsize;
typedef typed_attribute < t_real, a_scriptsizemultiplier > attr_scriptsizemultiplier;
typedef typed_attribute < t_unsigned, a_scrollamount > attr_scrollamount;
typedef typed_attribute < t_unsigned, a_scrolldelay > attr_scrolldelay;
typedef typed_attribute < t_scrolling, a_scrolling > attr_scrolling;
typedef typed_attribute < t_html_boolean, a_seamless > attr_seamless;
typedef typed_attribute < t_generic, a_seed > attr_seed;
typedef typed_attribute < t_generic, a_seethru > attr_seethru;
typedef typed_attribute < t_not_empty, a_select > attr_select;
typedef typed_attribute < t_existential, a_selected > attr_selected;
typedef typed_attribute < t_generic, a_selection > attr_selection;
typedef typed_attribute < t_bool, a_separator > attr_separator;
typedef typed_attribute < t_text, a_separators > attr_separators;
typedef typed_attribute < t_unsigned, a_seqnum > attr_seqnum;
typedef typed_attribute < t_existential, a_several > attr_several;
typedef typed_attribute < t_shape, a_shape > attr_shape;
typedef typed_attribute < t_shaperendering, a_shaperendering > attr_shaperendering;
typedef typed_attribute < t_integer, a_shift > attr_shift;
typedef typed_attribute < t_show, a_show > attr_show;
typedef typed_attribute < t_side, a_side > attr_side;
typedef typed_attribute < t_size, a_size > attr_size;
typedef typed_attribute < t_sizes, a_sizes > attr_sizes;
typedef typed_attribute < t_un_ex, a_skip > attr_skip;
typedef typed_attribute < t_real, a_slope > attr_slope;
typedef typed_attribute < t_idref, a_slot > attr_slot;
typedef typed_attribute < t_svg_snapshottime, a_snapshottime > attr_snapshottime;
typedef typed_attribute < t_existential, a_sortable > attr_sortable;
typedef typed_attribute < t_existential, a_sorted > attr_sorted;
typedef typed_attribute < t_spacing, a_spacing > attr_spacing;
typedef typed_attribute < t_positive, a_span > attr_span;
typedef typed_attribute < t_real, a_specularconstant > attr_specular_constant;
typedef typed_attribute < t_real, a_specularexponent > attr_specular_exponent;
typedef typed_attribute < t_truefalseempty, a_spellcheck > attr_spellcheck;
typedef typed_attribute < t_spread_method, a_spreadmethod > attr_spreadmethod;
typedef typed_attribute < t_url, a_src > attr_src;
typedef typed_attribute < t_html, a_srcdoc > attr_srcdoc;
typedef typed_attribute < t_lang, a_srclang > attr_srclang;
typedef typed_attribute < t_srcset, a_srcset > attr_srcset;
typedef typed_attribute < t_mimelist, a_srctype > attr_srctype;
typedef typed_attribute < t_text, a_standby > attr_standby;
typedef typed_attribute < t_lcrd, a_stackalign > attr_stackalign;
typedef typed_attribute < t_start, a_start > attr_start;
typedef typed_attribute < t_measure, a_start_offset > attr_start_offset;
typedef typed_attribute < t_measure, a_startoffset > attr_startoffset;
typedef typed_attribute < t_real_1_2, a_std_deviation > attr_std_deviation;
typedef typed_attribute < t_real_1_2, a_stddeviation > attr_stddeviation;
typedef typed_attribute < t_real, a_stemh > attr_stemh;
typedef typed_attribute < t_real, a_stemv > attr_stemv;
typedef typed_attribute < t_step, a_step > attr_step;
typedef typed_attribute < t_stitchtiles, a_stitchtiles > attr_stitchtiles;
typedef typed_attribute < t_colour_ci, a_stop_colour > attr_stop_colour;
typedef typed_attribute < t_opacity, a_stop_opacity > attr_stop_opacity;
typedef typed_attribute < t_bool, a_stretchy > attr_stretchy;
typedef typed_attribute < t_real, a_strikethroughposition > attr_strikethroughposition;
typedef typed_attribute < t_real, a_strikethroughthickness > attr_strikethroughthickness;
typedef typed_attribute < t_text, a_string > attr_string;
typedef typed_attribute < t_paint, a_stroke > attr_stroke;
typedef typed_attribute < t_dashes, a_stroke_dasharray > attr_stroke_dasharray;
typedef typed_attribute < t_measure_i, a_stroke_dashoffset > attr_stroke_dashoffset;
typedef typed_attribute < t_linecap, a_stroke_linecap > attr_stroke_linecap;
typedef typed_attribute < t_linejoin, a_stroke_linejoin > attr_stroke_linejoin;
typedef typed_attribute < t_1_more_i, a_stroke_miterlimit > attr_stroke_miterlimit;
typedef typed_attribute < t_opacity, a_stroke_opacity > attr_stroke_opacity;
typedef typed_attribute < t_measure_i, a_stroke_width > attr_stroke_width;
typedef typed_attribute < t_style, a_style > attr_style;
typedef typed_attribute < t_idref, a_subject > attr_subject;
typedef typed_attribute < t_vunit, a_subscriptshift > attr_subscriptshift;
typedef typed_attribute < t_text, a_summary > attr_summary;
typedef typed_attribute < t_vunit, a_superscriptshift > attr_superscriptshift;
typedef typed_attribute < t_measure, a_surfacescale > attr_surfacescale;
typedef typed_attribute < t_existential, a_svg > attr_svg;
typedef typed_attribute < t_svg_transform, a_svg_transform > attr_svg_transform;
typedef typed_attribute < t_sym, a_sym > attr_sym;
typedef typed_attribute < t_bool, a_symmetric > attr_symmetric;
typedef typed_attribute < t_generic, a_syncbehaviour > attr_syncbehaviour;
typedef typed_attribute < t_generic, a_syncbehaviourdefault > attr_syncbehaviourdefault;
typedef typed_attribute < t_generic, a_syncmaster > attr_syncmaster;
typedef typed_attribute < t_generic, a_synctolerance > attr_synctolerance;
typedef typed_attribute < t_generic, a_synctolerancedefault > attr_synctolerancedefault;
typedef typed_attribute < t_existential, a_system > attr_system;
typedef typed_attribute < t_langs, a_systemlanguage > attr_systemlanguage;
typedef typed_attribute < t_xmlns, a_systemrequired > attr_systemrequired;
typedef typed_attribute < t_integer, a_tabindex > attr_tabindex;
typedef typed_attribute < t_table_values, a_tablevalues > attr_tablevalues;
typedef typed_attribute < t_not_empty, a_tag > attr_tag;
typedef typed_attribute < t_target, a_target > attr_target;
typedef typed_attribute < t_idref, a_targetid > attr_targetid;
typedef typed_attribute < t_curies, a_targetrole > attr_targetrole;
typedef typed_attribute < t_generic, a_targetx > attr_targetx;
typedef typed_attribute < t_generic, a_targety > attr_targety;
typedef typed_attribute < t_url, a_template > attr_template;
typedef typed_attribute < t_colour, a_text > attr_text;
typedef typed_attribute < t_smei, a_textanchor > attr_textanchor;
typedef typed_attribute < t_textdecoration, a_textdecoration > attr_textdecoration;
typedef typed_attribute < t_textrendering, a_textrendering > attr_textrendering;
typedef typed_attribute < t_real, a_textlength > attr_textlength;
typedef typed_attribute < t_hunit, a_thickmathspace > attr_thickmathspace;
typedef typed_attribute < t_hunit, a_thinmathspace > attr_thinmathspace;
typedef typed_attribute < t_svg_timelinebegin, a_timelinebegin > attr_timelinebegin;
typedef typed_attribute < t_text, a_title > attr_title;
typedef typed_attribute < t_vid, a_to > attr_to;
typedef typed_attribute < t_unsigned, a_top > attr_top;
typedef typed_attribute < t_unsigned, a_topmargin > attr_topmargin;
typedef typed_attribute < t_transform, a_transform > attr_transform;
typedef typed_attribute < t_generic, a_transformbehaviour > attr_transformbehaviour;
typedef typed_attribute < t_yesnoempty, a_translate > attr_translate;
typedef typed_attribute < t_existential, a_truespeed > attr_truespeed;
typedef typed_attribute < t_type, a_type > attr_type;
typedef typed_attribute < t_html_boolean, a_typemustmatch > attr_typemustmatch;
typedef typed_attribute < t_curies, a_typeof > attr_typeof;
typedef typed_attribute < t_urange, a_u1 > attr_u1;
typedef typed_attribute < t_urange, a_u2 > attr_u2;
typedef typed_attribute < t_real, a_underlineposition > attr_underlineposition;
typedef typed_attribute < t_real, a_underlinethickness > attr_underlinethickness;
typedef typed_attribute < t_text, a_unicode > attr_unicode;
typedef typed_attribute < t_unicodebidi, a_unicodebidi > attr_unicodebidi;
typedef typed_attribute < t_urange, a_unicoderange > attr_unicoderange;
typedef typed_attribute < t_units, a_units > attr_units;
typedef typed_attribute < t_real, a_unitsperem > attr_unitsperem;
typedef typed_attribute < t_idref, a_until > attr_until;
typedef typed_attribute < t_generic, a_updateviacache > attr_updateviacache;
typedef typed_attribute < t_generic, a_urn > attr_urn;
typedef typed_attribute < t_url, a_usemap > attr_usemap;
typedef typed_attribute < t_valign, a_valign > attr_valign;
typedef typed_attribute < t_real, a_valphabetic > attr_valphabetic;
typedef typed_attribute < t_value, a_value > attr_value;
typedef typed_attribute < t_values, a_values > attr_values;
typedef typed_attribute < t_valuetype, a_valuetype > attr_valuetype;
typedef typed_attribute < t_vectoreffect, a_vector_effect > attr_vectoreffect;
typedef typed_attribute < t_version, a_version > attr_version;
typedef typed_attribute < t_real, a_vertadvy > attr_vertadvy;
typedef typed_attribute < t_real, a_vertoriginx > attr_vertoriginx;
typedef typed_attribute < t_real, a_vertoriginy > attr_vertoriginy;
typedef typed_attribute < t_hunit, a_verythickmathspace > attr_verythickmathspace;
typedef typed_attribute < t_hunit, a_verythinmathspace > attr_verythinmathspace;
typedef typed_attribute < t_hunit, a_veryverythickmathspace > attr_veryverythickmathspace;
typedef typed_attribute < t_hunit, a_veryverythinmathspace > attr_veryverythinmathspace;
typedef typed_attribute < t_real, a_vhanging > attr_vhanging;
typedef typed_attribute < t_real, a_videographic > attr_videographic;
typedef typed_attribute < t_svg_viewbox, a_viewbox > attr_viewbox;
typedef typed_attribute < t_generic, a_viewtarget > attr_viewtarget;
typedef typed_attribute < t_visibility, a_visibility > attr_visibility;
typedef typed_attribute < t_colour, a_vlink > attr_vlink;
typedef typed_attribute < t_real, a_vmathematical > attr_vmathematical;
typedef typed_attribute < t_vocab, a_vocab > attr_vocab;
typedef typed_attribute < t_pseudonamedspace, a_voffset > attr_voffset;
typedef typed_attribute < t_negative, a_volume > attr_volume;
typedef typed_attribute < t_integer, a_vspace > attr_vspace;
typedef typed_attribute < t_html_boolean, a_webkitdirectory > attr_webkitdirectory;
typedef typed_attribute < t_conditional, a_while > attr_while;
typedef typed_attribute < t_width, a_width > attr_width;
typedef typed_attribute < t_text, a_widths > attr_widths;
typedef typed_attribute < t_measure_ai, a_word_spacing > attr_word_spacing;
typedef typed_attribute < t_workertype, a_workertype > attr_workertype;
typedef typed_attribute < t_rap, a_wrap > attr_wrap;
typedef typed_attribute < t_writingmode, a_writingmode > attr_writingmode;
typedef typed_attribute < t_measure, a_x1 > attr_x1;
typedef typed_attribute < t_measure, a_x2 > attr_x2;
typedef typed_attribute < t_measure_or_more, a_x > attr_x;
typedef typed_attribute < t_channel_selector, a_xchannelselector > attr_xchannelselector;
typedef typed_attribute < t_real, a_xheight > attr_xheight;
typedef typed_attribute < t_xlinkactuate, a_xlinkactuate > attr_xlinkactuate;
typedef typed_attribute < t_url, a_xlinkarcrole > attr_xlinkarcrole;
typedef typed_attribute < t_url, a_xlinkhref > attr_xlinkhref;
typedef typed_attribute < t_url, a_xlinkrole > attr_xlinkrole;
typedef typed_attribute < t_xlinkshow, a_xlinkshow > attr_xlinkshow;
typedef typed_attribute < t_text, a_xlinktitle > attr_xlinktitle;
typedef typed_attribute < t_xlinktype, a_xlinktype > attr_xlinktype;
typedef typed_attribute < t_url, a_xmlbase > attr_xmlbase;
typedef typed_attribute < t_id, a_xmlid > attr_xmlid;
typedef typed_attribute < t_lang, a_xmllang > attr_xmllang;
typedef typed_attribute < t_xmllink, a_xmllink > attr_xmllink;
typedef typed_attribute < t_xmlns, a_xmlns > attr_xmlns;
typedef typed_attribute < t_generic, a_xref > attr_xref;
typedef typed_attribute < t_xmlspace, a_xmlspace > attr_xmlspace;
typedef typed_attribute < t_url, a_xsischemaloc > attr_xsischemaloc;
typedef typed_attribute < t_measure, a_y1 > attr_y1;
typedef typed_attribute < t_measure, a_y2 > attr_y2;
typedef typed_attribute < t_measure_or_more, a_y > attr_y;
typedef typed_attribute < t_channel_selector, a_ychannelselector > attr_ychannelselector;
typedef typed_attribute < t_measure, a_z > attr_z;
typedef typed_attribute < t_unsigned, a_zindex > attr_zindex;
typedef typed_attribute < t_zoompan, a_zoomandpan > attr_zoomandpan;

#define ATTRIBUTESAM \
    attr_abbr, \
    attr_about, \
    attr_above, \
    attr_accent, \
    attr_accentheight, \
    attr_accentunder, \
    attr_accept, \
    attr_acceptcharset, \
    attr_accesskey, \
    attr_accumulate, \
    attr_action, \
    attr_actiontype, \
    attr_activate, \
    attr_actuate, \
    attr_additive, \
    attr_align, \
    attr_alignmentbaseline, \
    attr_alignmentscope, \
    attr_alink, \
    attr_allow, \
    attr_allowfullscreen, \
    attr_allowpaymentrequest, \
    attr_allowusermedia, \
    attr_allowzoompan, \
    attr_alphabetic, \
    attr_alt, \
    attr_altimg, \
    attr_altimg_height, \
    attr_altimg_valign, \
    attr_altimg_width, \
    attr_alttext, \
    attr_amplitude, \
    attr_arabicform, \
    attr_archive, \
    attr_ariaactivedescendant, \
    attr_ariaatomic, \
    attr_ariaautocomplete, \
    attr_ariabusy, \
    attr_ariachecked, \
    attr_ariacontrols, \
    attr_ariadescribedby, \
    attr_ariadisabled, \
    attr_ariadropeffect, \
    attr_ariaexpanded, \
    attr_ariaflowto, \
    attr_ariagrabbed, \
    attr_ariahaspopup, \
    attr_ariahidden, \
    attr_ariainvalid, \
    attr_arialabel, \
    attr_arialabelledby, \
    attr_arialevel, \
    attr_arialive, \
    attr_ariamultiline, \
    attr_ariamultiselectable, \
    attr_ariaorientation, \
    attr_ariaowns, \
    attr_ariaposinset, \
    attr_ariapressed, \
    attr_ariareadonly, \
    attr_ariarelevant, \
    attr_ariarequired, \
    attr_ariaselected, \
    attr_ariasetsize, \
    attr_ariasort, \
    attr_ariavaluemax, \
    attr_ariavaluemin, \
    attr_ariavaluenow, \
    attr_ariavaluetext, \
    attr_as, \
    attr_ascent, \
    attr_async, \
    attr_at, \
    attr_attributename, \
    attr_attributetype, \
    attr_audio, \
    attr_autobuffer, \
    attr_autocapitalise, \
    attr_autocomplete, \
    attr_autocorrect, \
    attr_autofocus, \
    attr_autopictureinpicture, \
    attr_autoplay, \
    attr_axes, \
    attr_axis, \
    attr_azimuth, \
    attr_background, \
    attr_balance, \
    attr_bandwidth, \
    attr_base, \
    attr_base_frequency, \
    attr_baseline, \
    attr_baselineshift, \
    attr_baseprofile, \
    attr_bbox, \
    attr_begin, \
    attr_behaviour, \
    attr_below, \
    attr_bevelled, \
    attr_bgcolour, \
    attr_bias, \
    attr_border, \
    attr_bottommargin, \
    attr_box, \
    attr_bubbles, \
    attr_buffered, \
    attr_by, \
    attr_calcmode, \
    attr_cancelable, \
    attr_capheight, \
    attr_capture, \
    attr_cdgroup, \
    attr_cd, \
    attr_cell, \
    attr_cellpadding, \
    attr_cellspacing, \
    attr_challenge, \
    attr_char, \
    attr_charalign, \
    attr_charoff, \
    attr_charset, \
    attr_charspacing, \
    attr_checked, \
    attr_cite, \
    attr_class, \
    attr_classid, \
    attr_clear, \
    attr_clip, \
    attr_clip_path, \
    attr_clip_rule, \
    attr_clippathunits, \
    attr_close, \
    attr_closure, \
    attr_code, \
    attr_codebase, \
    attr_codetype, \
    attr_coldef, \
    attr_colour, \
    attr_colour_interpolation, \
    attr_colour_interpolation_filters, \
    attr_colour_profile, \
    attr_colour_rendering, \
    attr_cols, \
    attr_colspan, \
    attr_colspec, \
    attr_columnalign, \
    attr_columnlines, \
    attr_columnspacing, \
    attr_columnspan, \
    attr_columnwidth, \
    attr_compact, \
    attr_content, \
    attr_contenteditable, \
    attr_contentlength, \
    attr_contentscripttype, \
    attr_contentstyletype, \
    attr_contextmenu, \
    attr_continue, \
    attr_controls, \
    attr_controlslist, \
    attr_coords, \
    attr_crossorigin, \
    attr_crossout, \
    attr_csp, \
    attr_currenttime, \
    attr_cursor, \
    attr_cx, \
    attr_cy, \
    attr_d, \
    attr_data, \
    attr_datafld, \
    attr_dataformatas, \
    attr_datasrc, \
    attr_datastar, \
    attr_datatype, \
    attr_datetime, \
    attr_decimalpoint, \
    attr_declare, \
    attr_decoding, \
    attr_default, \
    attr_defaultaction, \
    attr_defer, \
    attr_definition, \
    attr_denomalign, \
    attr_depth, \
    attr_descent, \
    attr_diffuse_constant, \
    attr_dingbat, \
    attr_dir, \
    attr_direction, \
    attr_dirname, \
    attr_disabled, \
    attr_disablepictureinpicture, \
    attr_disableremoteplayback, \
    attr_display, \
    attr_displaystyle, \
    attr_divisor, \
    attr_dominantbaseline, \
    attr_download, \
    attr_dp, \
    attr_draggable, \
    attr_dropzone, \
    attr_dur, \
    attr_duration, \
    attr_dx, \
    attr_dy, \
    attr_edge, \
    attr_edgemode, \
    attr_edit, \
    attr_editable, \
    attr_effect, \
    attr_elevation, \
    attr_encoding, \
    attr_enctype, \
    attr_enablebackground, \
    attr_end, \
    attr_enterkeyhint, \
    attr_equalcolumns, \
    attr_equalrows, \
    attr_error, \
    attr_event, \
    attr_eventtarget, \
    attr_evevent, \
    attr_exponent, \
    attr_exportparts, \
    attr_externalresourcesrequired, \
    attr_face, \
    attr_fence, \
    attr_fill, \
    attr_fill_opacity, \
    attr_fill_rule, \
    attr_filter, \
    attr_filterres, \
    attr_filterunits, \
    attr_filter_units, \
    attr_fitbbox, \
    attr_fitboxtoviewport, \
    attr_flatness, \
    attr_flood_colour, \
    attr_flood_opacity, \
    attr_focusable, \
    attr_focushighlight, \
    attr_font, \
    attr_font_family, \
    attr_font_size, \
    attr_font_size_adjust, \
    attr_font_stretch, \
    attr_font_style, \
    attr_font_variant, \
    attr_font_weight, \
    attr_fontfamily, \
    attr_fontsize, \
    attr_fontstretch, \
    attr_fontstyle, \
    attr_fontvariant, \
    attr_fontweight, \
    attr_for, \
    attr_form, \
    attr_formaction, \
    attr_format, \
    attr_formenctype, \
    attr_formmethod, \
    attr_formnovalidate, \
    attr_forms, \
    attr_formtarget, \
    attr_fr, \
    attr_frame, \
    attr_frameborder, \
    attr_framespacing, \
    attr_from, \
    attr_full, \
    attr_function, \
    attr_fx, \
    attr_fy, \
    attr_g1, \
    attr_g2, \
    attr_generatorunable, \
    attr_glyph_orientation_vertical, \
    attr_glyphname, \
    attr_glyphorientation_horizontal, \
    attr_glyphref, \
    attr_gradienttransform, \
    attr_gradientunits, \
    attr_gradient_units, \
    attr_groupalign, \
    attr_gutter, \
    attr_handler, \
    attr_hanging, \
    attr_headers, \
    attr_height, \
    attr_hidden, \
    attr_high, \
    attr_horizadvx, \
    attr_horizoriginx, \
    attr_horizoriginy, \
    attr_href, \
    attr_hreflang, \
    attr_hrefmedia, \
    attr_hreftype, \
    attr_hspace, \
    attr_html, \
    attr_httpequiv, \
    attr_icon, \
    attr_id, \
    attr_ideographic, \
    attr_idref, \
    attr_if, \
    attr_imagerendering, \
    attr_imagemap, \
    attr_imagesizes, \
    attr_imagesrcset, \
    attr_implements, \
    attr_importance, \
    attr_in2, \
    attr_in, \
    attr_incremental, \
    attr_indent, \
    attr_indentalign, \
    attr_indentalignfirst, \
    attr_indentalignlast, \
    attr_indentshift, \
    attr_indentshiftfirst, \
    attr_indentshiftlast, \
    attr_indenttarget, \
    attr_index, \
    attr_inert, \
    attr_infixlinebreakstyle, \
    attr_initialvisibility, \
    attr_inlist, \
    attr_inputmode, \
    attr_integrity, \
    attr_intercept, \
    attr_intrinsicsize, \
    attr_irrelevant, \
    attr_is, \
    attr_ismap, \
    attr_item, \
    attr_itemid, \
    attr_itemprop, \
    attr_itemref, \
    attr_itemscope, \
    attr_itemtype, \
    attr_itstranslate, \
    attr_k, \
    attr_k1, \
    attr_k2, \
    attr_k3, \
    attr_k4, \
    attr_kernelmatrix, \
    attr_kernelunitlength, \
    attr_kerning, \
    attr_key, \
    attr_keyparams, \
    attr_keypoints, \
    attr_keysplines, \
    attr_keytimes, \
    attr_keytype, \
    attr_kind, \
    attr_label, \
    attr_labels, \
    attr_lang, \
    attr_language, \
    attr_largeop, \
    attr_layout, \
    attr_ldelim, \
    attr_left, \
    attr_leftmargin, \
    attr_leftoverhang, \
    attr_length, \
    attr_lengthadjust, \
    attr_letter_spacing, \
    attr_lightcolour, \
    attr_lighting_colour, \
    attr_limitingconeangle, \
    attr_linebreak, \
    attr_linebreakmultichar, \
    attr_linebreakstyle, \
    attr_lineleading, \
    attr_linethickness, \
    attr_link, \
    attr_list, \
    attr_loading, \
    attr_local, \
    attr_location, \
    attr_longdesc, \
    attr_longdivstyle, \
    attr_loop, \
    attr_loopcount, \
    attr_loopend, \
    attr_loopstart, \
    attr_low, \
    attr_lquote, \
    attr_lspace, \
    attr_macros, \
    attr_manifest, \
    attr_marginheight, \
    attr_marginwidth, \
    attr_marker, \
    attr_marker_end, \
    attr_marker_mid, \
    attr_marker_start, \
    attr_markerheight, \
    attr_markerunits, \
    attr_markerwidth, \
    attr_mask, \
    attr_maskcontentunits, \
    attr_mask_units, \
    attr_maskunits, \
    attr_math, \
    attr_mathbackground, \
    attr_mathcolour, \
    attr_mathematical, \
    attr_mathsize, \
    attr_mathvariant, \
    attr_max, \
    attr_maxlength, \
    attr_maxsize, \
    attr_md, \
    attr_media, \
    attr_mediacharacterencoding, \
    attr_mediacontentencodings, \
    attr_mediagroup, \
    attr_mediasize, \
    attr_mediatime, \
    attr_mediummathspace, \
    attr_menu, \
    attr_method, \
    attr_methods, \
    attr_min, \
    attr_minilabelspacing, \
    attr_minlength, \
    attr_minsize, \
    attr_mode, \
    attr_movablelimits, \
    attr_mozactionhint, \
    attr_mozbrowser, \
    attr_mslinethickness, \
    attr_multiple, \
    attr_muted, \
    attr_unknown

const e_attribute last_am = a_muted;

#define ATTRIBUTESNZ \
    attr_n, \
    attr_name, \
    attr_nargs, \
    attr_navdown, \
    attr_navdownleft, \
    attr_navdownright, \
    attr_navleft, \
    attr_navnext, \
    attr_navprev, \
    attr_navright, \
    attr_navup, \
    attr_navupleft, \
    attr_navupright, \
    attr_nextfocus, \
    attr_nodeid, \
    attr_noflow, \
    attr_nohref, \
    attr_nominallength, \
    attr_nomodule, \
    attr_noresize, \
    attr_noshade, \
    attr_notation, \
    attr_novalidate, \
    attr_nowrap, \
    attr_numalign, \
    attr_numberonce, \
    attr_numoctaves, \
    attr_object, \
    attr_observer, \
    attr_occurrence, \
    attr_offset, \
    attr_onabort, \
    attr_onactivate, \
    attr_onafterprint, \
    attr_onautocomplete, \
    attr_onautocompleteerror, \
    attr_onauxclick, \
    attr_onbeforeprint, \
    attr_onbeforeunload, \
    attr_onbegin, \
    attr_onblur, \
    attr_oncancel, \
    attr_oncanplay, \
    attr_oncanplaythrough, \
    attr_onchange, \
    attr_onclick, \
    attr_onclose, \
    attr_oncontextmenu, \
    attr_oncopy, \
    attr_oncuechange, \
    attr_oncut, \
    attr_ondblclick, \
    attr_ondrag, \
    attr_ondragend, \
    attr_ondragenter, \
    attr_ondragexit, \
    attr_ondragleave, \
    attr_ondragover, \
    attr_ondragstart, \
    attr_ondrop, \
    attr_ondurationchange, \
    attr_onemptied, \
    attr_onend, \
    attr_onended, \
    attr_onevent, \
    attr_onerror, \
    attr_onfocus, \
    attr_onfocusin, \
    attr_onfocusout, \
    attr_onformchange, \
    attr_onformdata, \
    attr_onforminput, \
    attr_onfullscreenchange, \
    attr_onfullscreenerror, \
    attr_onhashchange, \
    attr_oninput, \
    attr_oninvalid, \
    attr_onkeydown, \
    attr_onkeypress, \
    attr_onkeyup, \
    attr_onlanguagechange, \
    attr_onload, \
    attr_onloadeddata, \
    attr_onloadedmetadata, \
    attr_onloadend, \
    attr_onloadstart, \
    attr_onmessage, \
    attr_onmessageerror, \
    attr_onmousedown, \
    attr_onmouseenter, \
    attr_onmouseleave, \
    attr_onmousemove, \
    attr_onmouseout, \
    attr_onmouseover, \
    attr_onmouseup, \
    attr_onmousewheel, \
    attr_onoffline, \
    attr_ononline, \
    attr_onpagehide, \
    attr_onpageshow, \
    attr_onpaste, \
    attr_onpause, \
    attr_onplay, \
    attr_onplaying, \
    attr_onpopstate, \
    attr_onprogress, \
    attr_onratechange, \
    attr_onreadystatechange, \
    attr_onredo, \
    attr_onrejectionhandled, \
    attr_onrepeat, \
    attr_onreset, \
    attr_onresize, \
    attr_onscroll, \
    attr_onsecuritypolicyviolation, \
    attr_onseeking, \
    attr_onselect, \
    attr_onshow, \
    attr_onslotchange, \
    attr_onstalled, \
    attr_onsort, \
    attr_onsought, \
    attr_onstorage, \
    attr_onsubmit, \
    attr_onsuspend, \
    attr_ontimeupdate, \
    attr_ontoggle, \
    attr_onundo, \
    attr_onunhandledrejection, \
    attr_onunload, \
    attr_onvolumechange, \
    attr_onwaiting, \
    attr_onwheel, \
    attr_onzoom, \
    attr_opacity, \
    attr_open, \
    attr_operator, \
    attr_optimum, \
    attr_order, \
    attr_orient, \
    attr_orientation, \
    attr_origin, \
    attr_other, \
    attr_overflow, \
    attr_overlineposition, \
    attr_overlinethickness, \
    attr_pagex, \
    attr_pagey, \
    attr_paint_order, \
    attr_panose1, \
    attr_part, \
    attr_path, \
    attr_pathlength, \
    attr_pattern, \
    attr_patterncontentunits, \
    attr_patterntransform, \
    attr_patternunits, \
    attr_pattern_units, \
    attr_phase, \
    attr_ping, \
    attr_placeholder, \
    attr_plain, \
    attr_playbackorder, \
    attr_playcount, \
    attr_playsinline, \
    attr_pointerevents, \
    attr_points, \
    attr_pointsatx, \
    attr_pointsaty, \
    attr_pointsatz, \
    attr_position, \
    attr_poster, \
    attr_prefetch, \
    attr_prefix, \
    attr_preload, \
    attr_preservealpha, \
    attr_preserveaspectratio, \
    attr_prevfocus, \
    attr_primitiveunits, \
    attr_print, \
    attr_profile, \
    attr_prompt, \
    attr_propagate, \
    attr_property, \
    attr_pubdate, \
    attr_public, \
    attr_r, \
    attr_radiogroup, \
    attr_radius, \
    attr_rdelim, \
    attr_readonly, \
    attr_refx, \
    attr_refy, \
    attr_referrerpolicy, \
    attr_registrationmark, \
    attr_rel, \
    attr_renderingintent, \
    attr_repeatcount, \
    attr_repeatdur, \
    attr_required, \
    attr_requiredextensions, \
    attr_requiredfeatures, \
    attr_requiredfonts, \
    attr_requiredformats, \
    attr_resource, \
    attr_restart, \
    attr_result, \
    attr_results, \
    attr_resultscale, \
    attr_rev, \
    attr_reversed, \
    attr_rightmargin, \
    attr_rightoverhang, \
    attr_role, \
    attr_rotate, \
    attr_row, \
    attr_rowalign, \
    attr_rowgroup, \
    attr_rowlines, \
    attr_rows, \
    attr_rowspacing, \
    attr_rowspan, \
    attr_rquote, \
    attr_rspace, \
    attr_rules, \
    attr_rx, \
    attr_ry, \
    attr_sandbox, \
    attr_scale, \
    attr_scheme, \
    attr_scope, \
    attr_scoped, \
    attr_script, \
    attr_scriptlevel, \
    attr_scriptminsize, \
    attr_scriptsizemultiplier, \
    attr_scrollamount, \
    attr_scrolldelay, \
    attr_scrolling, \
    attr_seamless, \
    attr_seed, \
    attr_seethru, \
    attr_select, \
    attr_selected, \
    attr_selection, \
    attr_separator, \
    attr_separators, \
    attr_seqnum, \
    attr_several, \
    attr_shape, \
    attr_shaperendering, \
    attr_shift, \
    attr_show, \
    attr_side, \
    attr_size, \
    attr_sizes, \
    attr_skip, \
    attr_slope, \
    attr_slot, \
    attr_snapshottime, \
    attr_sortable, \
    attr_sorted, \
    attr_spacing, \
    attr_span, \
    attr_specular_constant, \
    attr_specular_exponent, \
    attr_spellcheck, \
    attr_spreadmethod, \
    attr_src, \
    attr_srcdoc, \
    attr_srclang, \
    attr_srcset, \
    attr_srctype, \
    attr_stackalign, \
    attr_standby, \
    attr_start, \
    attr_start_offset, \
    attr_startoffset, \
    attr_std_deviation, \
    attr_stddeviation, \
    attr_stemh, \
    attr_stemv, \
    attr_step, \
    attr_stitchtiles, \
    attr_stop_colour, \
    attr_stop_opacity, \
    attr_stretchy, \
    attr_strikethroughposition, \
    attr_strikethroughthickness, \
    attr_string, \
    attr_stroke, \
    attr_stroke_dasharray, \
    attr_stroke_dashoffset, \
    attr_stroke_linecap, \
    attr_stroke_linejoin, \
    attr_stroke_miterlimit, \
    attr_stroke_opacity, \
    attr_stroke_width, \
    attr_style, \
    attr_subject, \
    attr_subscriptshift, \
    attr_summary, \
    attr_superscriptshift, \
    attr_surfacescale, \
    attr_svg, \
    attr_svg_transform, \
    attr_sym, \
    attr_symmetric, \
    attr_syncbehaviour, \
    attr_syncbehaviourdefault, \
    attr_syncmaster, \
    attr_synctolerance, \
    attr_synctolerancedefault, \
    attr_system, \
    attr_systemlanguage, \
    attr_systemrequired, \
    attr_tabindex, \
    attr_tablevalues, \
    attr_tag, \
    attr_target, \
    attr_targetid, \
    attr_targetrole, \
    attr_targetx, \
    attr_targety, \
    attr_template, \
    attr_text, \
    attr_textanchor, \
    attr_textdecoration, \
    attr_textrendering, \
    attr_textlength, \
    attr_thickmathspace, \
    attr_thinmathspace, \
    attr_timelinebegin, \
    attr_title, \
    attr_to, \
    attr_top, \
    attr_topmargin, \
    attr_transform, \
    attr_transformbehaviour, \
    attr_translate, \
    attr_truespeed, \
    attr_type, \
    attr_typemustmatch, \
    attr_typeof, \
    attr_u1, \
    attr_u2, \
    attr_underlineposition, \
    attr_underlinethickness, \
    attr_unicode, \
    attr_unicodebidi, \
    attr_unicoderange, \
    attr_units, \
    attr_unitsperem, \
    attr_until, \
    attr_urn, \
    attr_updateviacache, \
    attr_usemap, \
    attr_valign, \
    attr_valphabetic, \
    attr_value, \
    attr_values, \
    attr_valuetype, \
    attr_vectoreffect, \
    attr_version, \
    attr_vertadvy, \
    attr_vertoriginx, \
    attr_vertoriginy, \
    attr_verythickmathspace, \
    attr_verythinmathspace, \
    attr_veryverythickmathspace, \
    attr_veryverythinmathspace, \
    attr_vhanging, \
    attr_videographic, \
    attr_viewbox, \
    attr_viewtarget, \
    attr_visibility, \
    attr_vlink, \
    attr_vmathematical, \
    attr_vocab, \
    attr_voffset, \
    attr_volume, \
    attr_vspace, \
    attr_webkitdirectory, \
    attr_while, \
    attr_width, \
    attr_widths, \
    attr_word_spacing, \
    attr_workertype, \
    attr_wrap, \
    attr_writingmode, \
    attr_x1, \
    attr_x2, \
    attr_x, \
    attr_xchannelselector, \
    attr_xheight, \
    attr_xlinkactuate, \
    attr_xlinkarcrole, \
    attr_xlinkhref, \
    attr_xlinkrole, \
    attr_xlinkshow, \
    attr_xlinktitle, \
    attr_xlinktype, \
    attr_xmlbase, \
    attr_xmlid, \
    attr_xmllang, \
    attr_xmllink, \
    attr_xmlns, \
    attr_xmlspace, \
    attr_xref, \
    attr_xsischemaloc, \
    attr_y1, \
    attr_y2, \
    attr_y, \
    attr_ychannelselector, \
    attr_z, \
    attr_zindex, \
    attr_zoomandpan, \
    attr_unknown
