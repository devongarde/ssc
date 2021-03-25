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
#include "main/include.h"

typedef enum { e_0, e_1 } e_10;
typedef enum { ac_none, ac_sum } e_accumulate;
typedef enum { av_sell, av_rent, av_trade, av_meet, av_announce, av_offer, av_wanted, av_event, av_service } e_action;
typedef enum { at_toggle, at_statusline, at_tooltip, at_highlight } e_actiontype;
typedef enum { act_insert, act_update, act_delete, act_static, act_unknown } e_activity;
typedef enum { ea_auto, ea_user } e_actuate;
typedef enum { ad_replace, ad_sum } e_additive;
typedef enum { a70_centre, a70_justify, a70_left, a70_right } e_align2070;
typedef enum { ald_centre, ald_decimal, ald_left, ald_right } e_aligndec;
typedef enum { alf_centre, alf_float, alf_left, alf_right } e_alignfig;
typedef enum {  ab_auto, ab_baseline, ab_beforeedge, ab_textbeforeedge, ab_middle, ab_central, ab_afteredge,
                ab_textafteredge, ab_ideographic, ab_alphabetic, ab_hanging, ab_mathematical, ab_inherit } e_alignmentbaseline;
typedef enum { ap_centre, ap_indent, ap_justify, ap_left, ap_right } e_alignplus;
typedef enum { a3_top, a3_middle, a3_bottom, a3_left, a3_right } e_align3;
typedef enum { ar_initial, ar_medial, at_terminal, at_isolated } e_arabicform;
typedef enum { aa_both, aa_inline, aa_list, aa_none  } e_aria_autocomplete;
typedef enum { ai_false, ai_grammar, ai_spelling, ai_true } e_aria_invalidity;
typedef enum { al_assertive, al_off, al_polite } e_aria_live;
typedef enum {  role_any, role_alert, role_alertdialogue, role_application, role_article, role_banner, role_button, role_cell, role_checkbox, role_columnheader, role_combobox,
                role_command, role_complementary, role_contentinfo, role_definition, role_dialogue, role_directory, role_document, role_feed, role_figure, role_form,
                role_grid, role_gridcell, role_group, role_heading, role_img, role_landmark, role_link, role_list, role_listbox, role_listitem, role_log, role_main,
                role_marquee, role_math, role_menu, role_menubar, role_menuitem, role_menuitemcheckbox, role_menuitemradio, role_navigation, role_none, role_note,
                role_option, role_presentation, role_progressbar, role_radio, role_radiogroup, role_range, role_region, role_roletype, role_row, role_rowgroup,
                role_rowheader, role_scrollbar, role_search, role_searchbox, role_section, role_sectionhead, role_select, role_separator, role_slider, role_spinbutton,
                role_status, role_structure, role_switch, role_tab, role_table, role_tablist, role_tabpanel, role_term, role_textbox, role_timer, role_toolbar,
                role_tooltip, role_tree, role_treegrid, role_treeitem, role_widget, role_window } e_aria_role;
typedef enum { as_ascending, as_descending, as_none, as_other } e_aria_sort;

typedef enum
{   a_unknown,
        a_abbr, a_about, a_above, a_accent, a_accentheight, a_accentunder, a_accept, a_acceptcharset, a_accesskey, a_accumulate, a_action,
        a_actiontype, a_activate, a_actuate, a_additive, a_align, a_alignmentbaseline, a_alignmentscope, a_alink, a_allow, a_allow_zoom_pan,
        a_allowfullscreen, a_allowpaymentrequest, a_allowusermedia, a_alphabetic, a_alt, a_altimg, a_altimg_height, a_altimg_width, a_altimg_valign,
        a_alttext, a_amplitude, a_arabicform, a_archive, a_ariaactivedescendant, a_ariaatomic, a_ariaautocomplete, a_ariabusy, a_ariachecked,
        a_ariacontrols, a_ariadescribedby, a_ariadisabled, a_ariadropeffect, a_ariaexpanded, a_ariaflowto, a_ariagrabbed, a_ariahaspopup, a_ariahidden,
        a_ariainvalid, a_arialabel, a_arialabelledby, a_arialevel, a_arialive, a_ariamultiline, a_ariamultiselectable, a_ariaorientation, a_ariaowns,
        a_ariaposinset, a_ariapressed, a_ariareadonly, a_ariarelevant, a_ariarequired, a_ariaselected, a_ariasetsize, a_ariasort, a_ariavaluemax,
        a_ariavaluemin, a_ariavaluenow, a_ariavaluetext, a_as, a_ascent, a_async, a_at, a_attributename, a_attributetype, a_audio, a_autobuffer,
        a_autocapitalise, a_autocomplete, a_autocorrect, a_autofocus, a_autopictureinpicture, a_autoplay, a_autosubmit, a_axes, a_axis, a_azimuth,
    a_background, a_balance, a_bandwidth, a_base, a_basefrequency, a_baseline, a_baselineshift, a_baseprofile, a_bbox, a_begin, a_behaviour,
        a_below, a_bevelled, a_bgcolour, a_bias, a_border, a_bottommargin, a_box, a_bubbles, a_buffered, a_by,
    a_calcmode, a_cancelable, a_capheight, a_capture, a_cd, a_cdgroup, a_cell, a_cellpadding, a_cellspacing, a_challenge, a_char, a_charalign, a_charoff,
        a_charset, a_charspacing,
        a_checked, a_cite, a_class, a_classid, a_clear, a_clip, a_clip_path, a_clip_rule, a_clippathunits, a_close, a_closure, a_code, a_codebase,
        a_codetype, a_coldef, a_colour, a_colour_interpolation, a_colour_interpolation_filters, a_colour_profile, a_colour_rendering, a_cols,
        a_colspan, a_colspec, a_columnalign, a_columnlines, a_columnspacing, a_columnspan, a_columnwidth, a_compact, a_content, a_contenteditable,
        a_contentlength, a_contentscripttype, a_contentstyletype, a_contextmenu, a_continue, a_controls, a_controlslist, a_coords, a_crossorigin,
        a_crossout, a_csp, a_currenttime, a_cursor, a_cx, a_cy,
    a_d, a_data, a_datafld, a_dataformatas, a_datasrc, a_datatype, a_datawild, a_datetime, a_decimalpoint, a_declare, a_decoding, a_default,
        a_defaultaction,
        a_defer, a_definitionurl, a_denomalign, a_depth, a_descent, a_diffuseconstant, a_dingbat, a_dir, a_direction, a_dirname, a_disabled,
        a_disablepictureinpicture, a_disableremoteplayback, a_display, a_displaystyle, a_divisor, a_dominantbaseline, a_download, a_dp,
        a_draggable, a_dropzone, a_dur, a_duration, a_dx, a_dy,
    a_edge, a_edgemode, a_edit, a_editable, a_effect, a_elevation, a_enablebackground, a_encoding, a_enctype, a_end, a_enterkeyhint, a_equalcolumns,
        a_equalrows,a_error, a_event, a_eventtarget, a_evevent, a_exponent, a_exportparts, a_externalresourcesrequired,
    a_face, a_fence, a_fill, a_fill_opacity, a_fill_rule, a_filter, a_filterres, a_filter_units, a_filterunits, a_fitbbox, a_fitboxtoviewport,
        a_flatness,
        a_flood_colour, a_flood_opacity, a_focusable, a_focushighlight, a_font, a_font_family, a_font_size, a_font_size_adjust, a_font_stretch,
        a_font_style, a_font_variant, a_font_weight, a_fontfamily, a_fontsize, a_fontstretch, a_fontstyle, a_fontvariant, a_fontweight, a_for,
        a_form, a_formaction, a_format, a_formenctype, a_formmethod, a_formnovalidate, a_forms, a_formtarget, a_fr, a_frame, a_frameborder,
        a_framespacing, a_from, a_full, a_function, a_fx, a_fy,
    a_g1, a_g2, a_generator_unable, a_glyph_orientation_vertical, a_glyphname, a_glyphorientation_horizontal, a_glyphref, a_gradienttransform,
        a_gradientunits, a_gradient_units, a_groupalign, a_gutter,
    a_handler, a_hanging, a_headers, a_height, a_hidden, a_high, a_horizadvx, a_horizoriginx, a_horizoriginy, a_href, a_hreflang, a_hrefmedia,
        a_hreftype, a_hspace, a_html, a_httpequiv,
    a_icon, a_id, a_ideographic, a_idref, a_if, a_imagerendering, a_imagemap, a_imagesizes, a_imagesrcset, a_implements, a_importance,
        a_in, a_in2, a_incremental, a_indent, a_indentalign, a_indentalignfirst, a_indentalignlast, a_indentshift, a_indentshiftfirst, a_indentshiftlast,
        a_indenttarget, a_index, a_inert, a_infixlinebreakstyle, a_initialvisibility, a_inlist, a_inputmode, a_integrity, a_intercept, a_intrinsicsize,
        a_irrelevant, a_is, a_ismap, a_item, a_itemid, a_itemprop, a_itemref, a_itemscope, a_itemtype, a_itstranslate,
    a_k, a_k1, a_k2, a_k3, a_k4, a_kernelmatrix, a_kernelunitlength, a_kerning, a_key, a_keyparams, a_keypoints, a_keysplines, a_keytimes,
        a_keytype, a_kind,
    a_label, a_labels, a_lang, a_language, a_largeop, a_layout, a_ldelim, a_left, a_leftmargin, a_leftoverhang, a_length, a_lengthadjust, a_letter_spacing,
        a_lightcolour, a_lighting_colour, a_limitingconeangle, a_linebreak, a_linebreakmultichar, a_linebreakstyle, a_lineleading, a_linethickness, a_link,
        a_list, a_loading, a_local, a_location, a_longdesc, a_longdivstyle, a_loop, a_loopcount, a_loopend, a_loopstart, a_low, a_lquote, a_lspace,
    a_macros, a_manifest, a_marginheight, a_marginwidth, a_marker, a_marker_end, a_marker_mid, a_marker_start, a_markerheight, a_markerunits,
        a_markerwidth, a_mask, a_maskcontentunits, a_mask_units, a_maskunits, a_math, a_mathbackground, a_mathematical, a_mathcolour,
        a_mathsize,
        a_mathvariant, a_max, a_maxlength, a_maxsize, a_maxwidth, a_md, a_media, a_mediacharacterencoding, a_mediacontentencodings,
        a_mediagroup, a_mediasize,
        a_mediatime, a_mediummathspace, a_menu, a_method, a_methods, a_min, a_minilabelspacing, a_minlength, a_minsize, a_mode, a_movablelimits,
        a_mozactionhint, a_mozbrowser, a_mslinethickness, a_multiple, a_muted,
    a_n, a_name, a_nargs, a_navdown, a_navdownleft, a_navdownright, a_navleft, a_navnext, a_navprev, a_navright,
        a_navup, a_navupleft, a_navupright, a_nextfocus, a_nodeid, a_noflow, a_nohref, a_nominallength, a_nomodule, a_noresize, a_noshade,
        a_notation, a_novalidate, a_nowrap, a_numalign, a_numberonce, a_numoctaves,
    a_object, a_observer, a_occurrence, a_offset, a_onabort, a_onactivate, a_onafterprint, a_onautocomplete, a_onautocompleteerror, a_onauxclick,
        a_onbeforeprint, a_onbeforeunload, a_onbegin,
        a_onblur, a_oncancel, a_oncanplay, a_oncanplaythrough, a_onchange, a_onclick, a_onclose, a_oncontextmenu, a_oncopy, a_oncuechange, a_oncut,
        a_ondblclick, a_ondrag, a_ondragend, a_ondragenter, a_ondragexit, a_ondragleave, a_ondragover, a_ondragstart, a_ondrop, a_ondurationchange,
        a_onemptied, a_onend, a_onended, a_onerror, a_onevent, a_onfocus, a_onfocusin, a_onfocusout, a_onformchange, a_onformdata, a_onforminput,
        a_onfullscreenchange, a_onfullscreenerror,
        a_onhashchange, a_oninput, a_oninvalid, a_onkeydown, a_onkeypress, a_onkeyup, a_onlanguagechange, a_onload, a_onloadeddata, a_onloadedmetadata,
        a_onloadend, a_onloadstart, a_onmessage, a_onmessageerror, a_onmousedown, a_onmouseenter, a_onmouseleave, a_onmousemove, a_onmouseout,
        a_onmouseover, a_onmouseup, a_onmousewheel,  a_onoffline, a_ononline, a_onpagehide, a_onpageshow, a_onpaste, a_onpause, a_onplay, a_onplaying,
        a_onpopstate, a_onprogress, a_onratechange, a_onreadystatechange, a_onredo, a_onrejectionhandled, a_onrepeat, a_onreset, a_onresize, a_onscroll,
        a_onsecuritypolicyviolation, a_onsought, a_onseeking, a_onselect, a_onshow, a_onslotchange, a_onsort, a_onstalled, a_onstorage, a_onsubmit,
        a_onsuspend, a_ontimeupdate, a_ontoggle, a_onunhandledrejection, a_onundo, a_onunload, a_onvolumechange, a_onwaiting, a_onwheel, a_onzoom,
        a_opacity, a_open, a_operator, a_optimum, a_order, a_orient, a_orientation, a_origin, a_other, a_overflow, a_overlay, a_overlineposition,
        a_overlinethickness,
    a_pagex, a_pagey, a_paint_order, a_panose1, a_part, a_path, a_pathlength, a_pattern, a_patterncontentunits, a_patterntransform,
        a_patternunits, a_pattern_units, a_phase, a_ping, a_placeholder, a_plain, a_playbackorder, a_playcount, a_playsinline, a_pointerevents,
        a_points, a_pointsatx, a_pointsaty, a_pointsatz, a_position, a_poster, a_prefetch, a_prefix, a_preload, a_preservealpha, a_preserveaspectratio,
        a_prevfocus, a_primitiveunits, a_print, a_profile, a_prompt, a_propagate, a_property, a_pubdate, a_public,
    a_r, a_radiogroup, a_radius, a_rdelim, a_readonly, a_referrerpolicy, a_refx, a_refy, a_registrationmark, a_rel, a_renderingintent, a_repeatcount,
        a_repeatdur, a_required, a_requiredextensions, a_requiredfeatures, a_requiredfonts, a_requiredformats, a_resource, a_restart, a_result,
        a_results, a_resultscale, a_rev, a_reversed, a_rightmargin, a_rightoverhang, a_role, a_rotate, a_row, a_rowalign, a_rowgroup, a_rowlines,
        a_rows, a_rowspacing, a_rowspan, a_rquote, a_rspace, a_rules, a_rx, a_ry,
    a_sandbox, a_scale, a_scheme, a_scope, a_scoped, a_script, a_scriptlevel, a_scriptminsize, a_scriptsizemultiplier, a_scrollamount,  a_scrolldelay,
        a_scrolling, a_seamless, a_seed, a_seethru, a_select, a_selected, a_selection, a_separator, a_separators, a_seqnum, a_several, a_shape,
        a_shaperendering, a_shift, a_show, a_side, a_size, a_sizes, a_skip, a_slope, a_slot, a_snapshottime, a_sortable, a_sorted, a_spacing, a_span,
        a_specularconstant, a_specularexponent, a_spellcheck, a_spreadmethod, a_src, a_srcdoc, a_srclang, a_srcset, a_srctype, a_stackalign,
        a_standby, a_start, a_start_offset, a_startoffset, a_std_deviation, a_stddeviation, a_stemh, a_stemv, a_step, a_stitchtiles, a_stop_colour,
        a_stop_opacity, a_stretchy, a_strikethroughposition, a_strikethroughthickness, a_string, a_stroke, a_stroke_dasharray, a_stroke_dashoffset,
        a_stroke_linecap, a_stroke_linejoin, a_stroke_miterlimit, a_stroke_opacity, a_stroke_width, a_style, a_subject, a_subscriptshift, a_summary,
        a_superscriptshift, a_surfacescale, a_svg, a_sym, a_svg_transform, a_symmetric, a_syncbehaviour, a_syncbehaviourdefault, a_syncmaster,
        a_synctolerance, a_synctolerancedefault, a_system, a_systemlanguage, a_systemrequired,
    a_tabindex, a_tablevalues, a_tag, a_target, a_targetid, a_targetrole, a_targetx, a_targety, a_template, a_text, a_textanchor, a_textdecoration,
        a_textrendering, a_textlength, a_thickmathspace, a_thinmathspace, a_timelinebegin, a_title, a_to, a_top, a_topmargin, a_transform,
        a_transformbehaviour, a_translate, a_truespeed, a_type, a_typemustmatch, a_typeof,
    a_u1, a_u2, a_underlineposition, a_underlinethickness, a_unicode, a_unicodebidi, a_unicoderange, a_units, a_unitsperem, a_until, a_updateviacache,
        a_urn, a_usemap,
    a_valign, a_valphabetic, a_value, a_values, a_valuetype, a_vector_effect, a_version, a_vertadvy, a_vertoriginx, a_vertoriginy,
        a_verythickmathspace, a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace, a_vhanging,
        a_videographic, a_viewbox, a_viewtarget, a_visibility, a_vlink, a_vmathematical, a_vocab, a_voffset, a_volume, a_vspace,
    a_webkitdirectory, a_while, a_width, a_widths, a_word_spacing, a_workertype, a_wrap, a_writingmode,
    a_x, a_x1, a_x2, a_xchannelselector, a_xheight, a_xlinkactuate, a_xlinkarcrole, a_xlinkhref, a_xlinkrole, a_xlinkshow, a_xlinktitle,
        a_xlinktype, a_xmlbase, a_xmlid, a_xmllang, a_xmllink, a_xmlns, a_xmlspace, a_xref, a_xsischemaloc,
    a_y, a_y1, a_y2, a_ychannelselector,
    a_z, a_zindex, a_zoomandpan,
    a_illegal
 } e_attribute;
const e_attribute last_attribute = a_illegal;

typedef enum { an_auto, an_css, an_xml } e_attributetype;
typedef enum { ac4_characters, ec4_default, ac4_none, ac4_sentences, ac4_words } e_autocapitalise;

typedef enum {
    aco_additional_name, aco_address_level1, aco_address_level2, aco_address_level3, aco_address_level4, aco_address_line1, aco_address_line2, aco_address_line3,
    aco_bday, aco_bday_day, aco_bday_month, aco_bday_year, aco_billing, aco_cc_additional_name, aco_cc_csc, aco_cc_exp, aco_cc_exp_month, aco_cc_exp_year, aco_cc_family_name,
    aco_cc_given_name, aco_cc_name, aco_cc_number, aco_cc_type, aco_country, aco_country_name, aco_current_password, aco_email, aco_family_name, aco_fax, aco_given_name,
    aco_home, aco_honorific_prefix, aco_honorific_suffix, aco_impp, aco_language, aco_locality, aco_mobile, aco_name, aco_new_password, aco_nickname, aco_off, aco_on, aco_one_time_code,
    aco_organization, aco_organization_title, aco_pager, aco_photo, aco_postal_code, aco_region, aco_sex, aco_section, aco_shipping, aco_street_address, aco_tel, aco_tel_area_code,
    aco_tel_country_code, aco_tel_extension, aco_tel_local, aco_tel_local_prefix, aco_tel_local_suffix, aco_tel_national, aco_transaction_amount, aco_transaction_currency,
    aco_url, aco_username, aco_work
} e_autocomplete;

typedef enum { bsb_baseline, bsb_sub, bsb_super, bsb_inherit } e_baselineshift;
typedef enum { as_audio, as_document, as_embed, as_fetch, as_font, as_image, as_object, as_script, as_style, as_track, as_video, as_worker } e_as;
typedef enum { be_alternative, be_scroll, be_slide } e_behaviour;
typedef enum { bk_asp, bk_cdata, bk_code, bk_comment, bk_doctype, bk_node, bk_num, bk_php, bk_ssi, bk_stylesheet, bk_text, bk_xml } bk_status;
typedef enum { b_true, b_false } e_bool;
typedef enum { bu_button, bu_submit, bu_reset } e_button;
typedef enum { bm_ansi, bm_utf8, bm_utf16_be, bm_utf16_le, bm_utf32_be, bm_utf32_le, bm_utf7, bm_utf1, bm_utf_ebcdic, bm_scsu, bm_bocu_1, bm_gb_1830, bm_error } byte_order_mark;
typedef enum { ck_maxage, ck_maxstale, ck_minfresh, ck_nocache, ck_nostore, ck_notransform, ck_onlyifcached } e_cachekey;
typedef enum { cm_discrete, cm_linear, cm_paced, cm_spline } e_calcmode;
typedef enum { ca_bottom, cap_left, ca_right, ca_top } e_captionalign;
typedef enum { cv_user, cv_environment } ev_capture;
typedef enum {  ec_undefined, ec_io, ec_icu, ec_attribute, ec_crc, ec_css, ec_directory, ec_element, ec_html, ec_incorrectness, ec_init, ec_link, ec_microdata, ec_microformat,
                ec_mime, ec_mql, ec_namespace, ec_parser, ec_program, ec_rdf, ec_regex, ec_rudeness, ec_shadow, ec_ssi, ec_page, ec_tidyness, ec_type, ec_url, ec_utility, ec_webmention } e_category;
const e_category last_category = ec_webmention;
typedef enum {  cc_ansi, cc_utf8, cc_utf16be, cc_utf16le, cc_gb, cc_fkd } e_charcode;
typedef enum {  ch_a, ch_b, ch_g, ch_r } e_channel_selector;

typedef enum {  cs_context,
                cs_adobe_standard_encoding, cs_adobe_symbol_encoding, cs_amiga_1251, cs_ansi_x3_110_1983, cs_ascii, cs_asmo_449, cs_axiom, cs_bocu_1, cs_brf, cs_bs_4730, cs_bs_viewdata,
                cs_big5, cs_cesu_8, cs_cp50220, cs_cp51932, cs_csa_z243_4_1985_1, cs_csa_z243_4_1985_2, cs_csa_z243_4_1985_gr, cs_csn_369103,
                cs_dec_mcs, cs_din_66003, cs_ds_2089, cs_ebcdic_at_de, cs_ebcdic_at_de_a, cs_ebcdic_ca_fr, cs_ebcdic_dk_no, cs_ebcdic_dk_no_a, cs_ebcdic_es,
                cs_ebcdic_es_a, cs_ebcdic_es_s, cs_ebcdic_fi_se, cs_ebcdic_fi_se_a, cs_ebcdic_fr, cs_ebcdic_it, cs_ebcdic_pt, cs_ebcdic_uk, cs_ebcdic_us, cs_ecma_cyrillic,
                cs_es, cs_es2, cs_euc_jp, cs_euc_kr, cs_extended_unix_code_fixed_width_for_japanese, cs_extended_unix_code_packed_format_for_japanese, cs_gb18030,
                cs_gbk, cs_gb_1988_80, cs_gost_19768_74, cs_hp_desktop, cs_hp_legal, cs_hp_math8, cs_hp_pi_font, cs_ibm_symbols,
                cs_ibm_thai, cs_ibm00858, cs_ibm00924, cs_ibm01140, cs_ibm01141, cs_ibm01142, cs_ibm01143, cs_ibm01144, cs_ibm01145, cs_ibm01146, cs_ibm01147, cs_ibm01148,
                cs_ibm01149, cs_ibm037, cs_ibm038, cs_ibm1026, cs_ibm1047, cs_ibm273, cs_ibm274, cs_ibm275, cs_ibm277, cs_ibm278, cs_ibm280, cs_ibm281, cs_ibm284,
                cs_ibm285, cs_ibm290, cs_ibm297, cs_ibm420, cs_ibm423, cs_ibm424, cs_ibm437, cs_ibm500, cs_ibm775, cs_ibm850, cs_ibm851, cs_ibm852, cs_ibm855, cs_ibm857,
                cs_ibm860, cs_ibm861, cs_ibm862, cs_ibm863, cs_ibm864, cs_ibm865, cs_ibm866, cs_ibm868, cs_ibm869, cs_ibm870, cs_ibm871, cs_ibm880, cs_ibm891, cs_ibm903,
                cs_ibm904, cs_ibm905, cs_ibm918, cs_iec_p27_1, cs_inis, cs_inis_8, cs_inis_cyrillic, cs_invariant, cs_iso_10646_j_1, cs_iso_10646_ucs_4,
                cs_iso_10646_ucs_basic, cs_iso_10646_utf_1, cs_iso_10646_unicode_latin1, cs_iso_11548_1, cs_iso_2022_cn, cs_iso_2022_jp,
                cs_iso_2022_jp_2, cs_iso_8859_1_windows_3_0_latin_1, cs_iso_8859_1_windows_3_1_latin_1, cs_iso_8859_10, cs_iso_8859_13,
                cs_iso_8859_14, cs_iso_8859_15, cs_iso_8859_16, cs_iso_8859_2, cs_iso_8859_2_windows_latin_2, cs_iso_8859_3, cs_iso_8859_4, cs_iso_8859_5, cs_iso_8859_6,
                cs_iso_8859_6_e, cs_iso_8859_6_i, cs_iso_8859_7, cs_iso_8859_8, cs_iso_8859_8_e, cs_iso_8859_8_i, cs_iso_8859_9, cs_iso_8859_9_windows_latin_5,
                cs_iso_unicode_ibm_1261, cs_iso_unicode_ibm_1264, cs_iso_unicode_ibm_1265, cs_iso_unicode_ibm_1268, cs_iso_unicode_ibm_1276, cs_iso_10367_box,
                cs_iso_2033_1983, cs_iso_5427, cs_iso_5427_1981, cs_iso_5428_1980, cs_iso_646_basic_1983, cs_iso_646_irv_1983, cs_iso_6937_2_25,
                cs_iso_6937_2_add, cs_iso_8859_3_1988, cs_iso_8859_4_1988, cs_iso_8859_9_1989, cs_iso_8859_supp, cs_it, cs_jis_c6220_1969_jp, cs_jis_c6220_1969_ro,
                cs_jis_c6226_1978, cs_jis_c6226_1983, cs_jis_c6229_1984_a, cs_jis_c6229_1984_b, cs_jis_c6229_1984_b_add, cs_jis_c6229_1984_hand, cs_jis_c6229_1984_hand_add,
                cs_jis_c6229_1984_kana, cs_jis_encoding, cs_jis_x0201, cs_jis_x0212_1990, cs_jus_i_b1_002, cs_jus_i_b1_003_mac, cs_jus_i_b1_003_serb, cs_koi7_switched,
                cs_koi8_r, cs_koi8_u, cs_ksc5636, cs_kz_1048, cs_latin_greek_1, cs_macintosh, cs_maple, cs_mathematica, cs_mathml_content, cs_mathml_presentation, cs_mnem,
                cs_mnemonic, cs_msz_7795_3,
                cs_microsoft_publishing, cs_nats_dano, cs_nats_dano_add, cs_nats_sefi, cs_nats_sefi_add, cs_cs_nc_nc00_10_81, cs_nf_z_62_010, cs_nf_z_62_010_1973,
                cs_ns_4551_1, cs_ns_4551_2, cs_openmath, cs_osd_ebcdic_df03_irv, cs_osd_ebcdic_df04_1, cs_osd_ebcdic_df04_15, cs_pc8_danish_norwegian, cs_pc8_turkish,
                cs_pt, cs_pt2, cs_ptcp154, cs_scsu, cs_sen_850200_b, cs_sen_850200_c, cs_t_101_g2, cs_t_61_7bit, cs_t_61_8bit, cs_tex, cs_text, cs_tscii, cs_unicode_1_1,
                cs_unicode_1_1_utf_7, cs_unknown_8bit, cs_utf_16be, cs_utf_16le, cs_utf_32, cs_utf_32be, cs_utf_32le, cs_utf_7, cs_utf_8, cs_viqr, cs_viscii,
                cs_ventura_international, cs_ventura_math, cs_ventura_us, cs_windows_31j, cs_dk_us, cs_greek_ccitt, cs_greek7, cs_greek7_old, cs_hp_roman8, cs_iso_ir_90,
                cs_latin_greek, cs_latin_lap, cs_us_dk, cs_videotex_suppl, cs_windows_1250, cs_windows_1251, cs_windows_1252, cs_windows_1253,
                cs_windows_1254, cs_windows_1255, cs_windows_1256, cs_windows_1257, cs_windows_1258, cs_windows_874, cs_x_user_defined, cs_illegal
} e_charset;

typedef enum {  ci_integer, ci_rational, ci_real, ci_complexpolar, ci_complexcartesian, ci_constant,
                ci_complex, ci_function, ci_vector, ci_list, ci_set, ci_matrix } e_citype;

typedef enum {  c_context,

                // microformats v1 vocabulary
                h1_aggregate, h1_atom, h1_audio, h1_calendar, h1_card, h1_listing, h1_media, h1_product, h1_recipe, h1_resume, h1_review,
                h1_adr, h1_geo, h1_news, h1_xmdp, h1_xoxo,

                // microformats v2 vocabulary
                h_adr, h_breadcrumb, h_card, h_cite, h_entry, h_event, h_feed, h_geo, h_item, h_listing, h_product, h_recipe, h_resume, h_review,
                h_aggregate,

                // microformats v1 property
                mf1_additional_name, mf1_adr, mf1_affliation, mf1_agent, mf1_album, mf1_amount, mf1_attach, mf1_attendee, mf1_author, mf1_average, mf1_bday,
                mf1_best, mf1_brand, mf1_category, mf1_class, mf1_contact, mf1_contributor, mf1_count, mf1_country_name, mf1_currency,
                mf1_dateline, mf1_dtend, mf1_dtexpired, mf1_dtlisted, mf1_dtreviewed, mf1_dtstart, mf1_description,
                mf1_duration, mf1_education, mf1_email, mf1_entry_content, mf1_entry_title,
                mf1_entry_summary, mf1_experience, mf1_extended_address, mf1_family_name, mf1_fn, mf1_given_name,
                mf1_geo, mf1_hentry, mf1_honorific_prefix, mf1_honorific_suffix, mf1_identifier, mf1_ingredient, mf1_instructions,
                mf1_item, mf1_item_info, mf1_item_licence, mf1_item_tags, mf1_item_type, mf1_key, mf1_label, mf1_latitude, mf1_licence, mf1_lister,
                mf1_listing, mf1_locality, mf1_location, mf1_logo, mf1_longitude, mf1_mailer, mf1_n, mf1_nickname, mf1_note,
                mf1_nutrition, mf1_org, mf1_organisation_name, mf1_organisation_unit, mf1_organiser, mf1_partstat, mf1_payment, mf1_permalink, mf1_photo,
                mf1_player, mf1_postal_code, mf1_post_office_box, mf1_price, mf1_principles, mf1_profile, mf1_position, mf1_publications, mf1_published, mf1_rating,
                mf1_rdate, mf1_region, mf1_rev, mf1_review, mf1_reviewer, mf1_role, mf1_rrule, mf1_sample, mf1_skill, mf1_sort_string,
                mf1_sound, mf1_source_org, mf1_status, mf1_street_address, mf1_summary, mf1_tag, mf1_tel, mf1_title,
                mf1_type, mf1_tz, mf1_uid, mf1_updated, mf1_url, mf1_value, mf1_version, mf1_votes, mf1_worst, mf1_yield,
                mf1_sell, mf1_rent, mf1_trade, mf1_meet, mf1_announce, mf1_offer, mf1_wanted, mf1_event, mf1_service,
                mf1_opening, mf1_housing, mf1_product, mf1_business, mf1_person, mf1_place, mf1_website,

                // microformats v2 property
                dt_accessed, p_action, p_additional_name, p_adr, p_affiliation, p_altitude, dt_anniversary, p_attendee, u_audio,
                p_author, p_average, dt_bday, p_best, u_bookmark_of, p_brand, p_category, p_comment, p_contact, e_content, p_content,
                p_count, p_country_name, e_description, p_description, dt_duration, p_education, u_email, dt_end, p_entry,
                p_experience, dt_expired, p_extended_address, p_family_name, u_featured, p_gender_identity, p_geo, u_geo, p_given_name,
                p_honorific_prefix, p_honorific_suffix, u_identifier, u_impp, p_ingredient, u_in_reply_to, e_instructions,
                p_item, p_job_title, u_key, p_label, p_latitude, u_like, u_like_of, dt_listed, p_lister,
                p_locality, p_location, u_logo, p_longitude, p_name, p_nickname, p_note, p_nutrition,
                p_org, p_organisation_name, p_organisation_unit, p_organiser, u_photo, p_post_office_box, p_postal_code,
                p_price, p_publication, dt_published, p_rating, p_region, dt_rev, u_repost, u_repost_of, p_review, dt_reviewed,
                p_reviewer, p_role, p_rsvp, p_sex, p_skill, p_sort_string, u_sound, dt_start, p_street_address,
                p_summary, u_syndication, p_tel, p_tz, u_uid, dt_updated, u_url, u_video, p_votes, p_worst, p_yield,
                u_dnsprefetch, u_external, u_icon, u_noopener, u_noreferrer, u_preconnect, u_prefetch, u_preload, u_prerender, u_search,

                h5d_copyright, h5d_error, h5d_example, h5d_issue, h5d_note, h5d_search, h5d_warning,

                c_error
} e_class;

typedef enum {  cn_enotation, cn_integer, cn_rational, cn_real, cn_complexpolar, cn_complexcartesian, cn_constant,
                cn_double, cn_hexdouble } e_cntype;
typedef enum { ci_auto, ci_srgb, ci_linearrgb, ci_inerit } e_colourinterpolation;
typedef enum { cr_auto, cr_optimisespeed, cr_optimisequality, cr_inerit } e_colourrendering;
typedef enum { co_command, co_checkbox, co_radio } e_command;
typedef enum { es_original, es_query, es_fragment, es_scheme, es_authority, es_user, es_password, es_server, es_port, es_path, es_file, es_extension } e_component;
typedef enum { co_arithmetic, co_atop, co_in, co_out, co_over, co_xor } e_composite_operator;
typedef enum { ce_gzip, ce_compress, ce_deflate, ce_identity } e_content_encoding;
typedef enum { cl_nodownload, cl_nofullscreen, cl_noremoteplayback } e_controlslist;
typedef enum { coo_expires, coo_maxage, coo_domain, coo_path, coo_secure, coo_httponly } e_cookieid;
typedef enum { c_none, c_html, c_hard, c_soft, c_copy, c_deduplicate, c_rpt } e_copy;
typedef enum { cr_same_origin, cr_same_site, cr_cross_origin } e_corp;
typedef enum { cc_anonymous, cc_credentials } ev_cors;
typedef enum { co_none, co_updiagonalstrike, co_downdiagonalstrike, co_verticalstrike, co_horizontalstrike } e_crossout;

typedef enum {  csp_context,
                // CSP 1
                csp_connect, csp_default, csp_font, csp_frame, csp_img, csp_media, csp_object, csp_script, csp_style,
                csp_sandbox, csp_report_uri,
                // CSP 2
                csp_base_uri, csp_child, csp_form_action, csp_frame_ancestors, csp_plugin_types,
                // CSP 3
                csp_manifest, csp_prefetch, csp_script_elem, csp_script_attr, csp_style_elem, csp_style_attr,
                csp_worker, csp_navigate_to, csp_report_to,
                // Extensions
                csp_block_all_mixed_content, csp_update_insecure_requests, csp_require_sri_for,
                csp_error } e_csp_directive;

typedef enum {  cspa_context,
                cspa_forms, cspa_pointer_lock, cspa_popups, cspa_same_origin, cspa_scripts, cspa_top_navigation,
                cspa_error } e_csp_allow;
typedef enum {  csk_context,
                csk_self, csk_unsafe_inline, csk_unsafe_eval, csk_strict_dynamic, csk_unsafe_hashes, csk_report_sample, csk_unsafe_allow_redirects,
                csk_error } e_csp_keyword;
typedef enum {  e_iso_context,
                e_iso_AED, e_iso_AFN, e_iso_ALL, e_iso_AMD, e_iso_ANG, e_iso_AOA, e_iso_ARS, e_iso_AUD, e_iso_AWG, e_iso_AZN, e_iso_BAM,
                e_iso_BBD, e_iso_BDT, e_iso_BGN, e_iso_BHD, e_iso_BIF, e_iso_BMD, e_iso_BND, e_iso_BOB, e_iso_BOV, e_iso_BRL, e_iso_BSD,
                e_iso_BTN, e_iso_BWP, e_iso_BYN, e_iso_BZD, e_iso_CAD, e_iso_CDF, e_iso_CHE, e_iso_CHF, e_iso_CHW, e_iso_CLF, e_iso_CLP,
                e_iso_CNY, e_iso_COP, e_iso_COU, e_iso_CRC, e_iso_CUC, e_iso_CUP, e_iso_CVE, e_iso_CZK, e_iso_DJF, e_iso_DKK, e_iso_DOP,
                e_iso_DZD, e_iso_EGP, e_iso_ERN, e_iso_ETB, e_iso_EUR, e_iso_FJD, e_iso_FKP, e_iso_GBP, e_iso_GEL, e_iso_GHS, e_iso_GIP,
                e_iso_GMD, e_iso_GNF, e_iso_GTQ, e_iso_GYD, e_iso_HKD, e_iso_HNL, e_iso_HRK, e_iso_HTG, e_iso_HUF, e_iso_IDR, e_iso_ILS,
                e_iso_INR, e_iso_IQD, e_iso_IRR, e_iso_ISK, e_iso_JMD, e_iso_JOD, e_iso_JPY, e_iso_KES, e_iso_KGS, e_iso_KHR, e_iso_KMF,
                e_iso_KPW, e_iso_KRW, e_iso_KWD, e_iso_KYD, e_iso_KZT, e_iso_LAK, e_iso_LBP, e_iso_LKR, e_iso_LRD, e_iso_LSL, e_iso_LYD,
                e_iso_MAD, e_iso_MDL, e_iso_MGA, e_iso_MKD, e_iso_MMK, e_iso_MNT, e_iso_MOP, e_iso_MRU, e_iso_MUR, e_iso_MVR, e_iso_MWK,
                e_iso_MXN, e_iso_MXV, e_iso_MYR, e_iso_MZN, e_iso_NAD, e_iso_NGN, e_iso_NIO, e_iso_NOK, e_iso_NPR, e_iso_NZD, e_iso_OMR,
                e_iso_PAB, e_iso_PEN, e_iso_PGK, e_iso_PHP, e_iso_PKR, e_iso_PLN, e_iso_PYG, e_iso_QAR, e_iso_RON, e_iso_RSD, e_iso_RUB,
                e_iso_RWF, e_iso_SAR, e_iso_SBD, e_iso_SCR, e_iso_SDG, e_iso_SEK, e_iso_SGD, e_iso_SHP, e_iso_SLL, e_iso_SOS, e_iso_SRD,
                e_iso_SSP, e_iso_STN, e_iso_SVC, e_iso_SYP, e_iso_SZL, e_iso_THB, e_iso_TJS, e_iso_TMT, e_iso_TND, e_iso_TOP, e_iso_TRY,
                e_iso_TTD, e_iso_TWD, e_iso_TZS, e_iso_UAH, e_iso_UGX, e_iso_USD, e_iso_USN, e_iso_UYI, e_iso_UYU, e_iso_UYW, e_iso_UZS,
                e_iso_VES, e_iso_VND, e_iso_VUV, e_iso_WST, e_iso_XAF, e_iso_XAG, e_iso_XAU, e_iso_XBA, e_iso_XBB, e_iso_XBC, e_iso_XBD,
                e_iso_XCD, e_iso_XDR, e_iso_XOF, e_iso_XPD, e_iso_XPF, e_iso_XPT, e_iso_XSU, e_iso_XTS, e_iso_XUA, e_iso_XXX, e_iso_YER,
                e_iso_ZAR, e_iso_ZMW, e_iso_ZWL } e_currency; // ISO 4217

typedef enum {  cu_auto, cu_crosshair, cu_default, cu_pointer, cu_move, cu_eresize, cu_neresize, cu_nwresize, cu_nresize, cu_seresize,
                cu_swresize, cu_sresize, cu_wresize, cu_text, cu_wait, cu_help  } e_cursor;
typedef enum { edf_html, edf_plaintext } e_dataformatas;
typedef enum { dec_left, dec_center, dec_right, dec_justify, dec_decimal } e_decalign;
typedef enum { ed_auto, ed_sync, ed_async } e_decoding;
typedef enum { df_cancel, df_perform } e_defaultaction;

typedef enum {  db_context,
                db_ftp, db_gopher, db_telnet, db_archive, db_filing_cabinet, db_folder, db_fixed_disk, db_disk_drive, db_document,
                db_unknown_document, db_text_document, db_binary_document, db_binhex_document, db_audio, db_film, db_image, db_map,
                db_form, db_mail, db_parent, db_next, db_previous, db_home, db_toc, db_glossary, db_index, db_summary, db_calculator,
                db_caution, db_clock, db_compressed_document, db_diskette, db_display, db_fax, db_mail_in, db_mail_out, db_mouse,
                db_printer, db_tn3270, db_trash } e_dingbat;

typedef enum { di_auto, di_lro, di_rlo, di_ltr, di_rtl } e_dir;
typedef enum {  ds_inline, ds_block, ds_listitem, ds_runin, ds_compact, ds_marker, ds_table, ds_inlinetable, ds_tablerowgroup, ds_tableheadergroup,
                ds_tablefootergroup, ds_tablerow, ds_tablecolumngroup, ds_tablecolumn, ds_tablecell, ds_tablecaption, ds_none, ds_inherit } e_display;
typedef enum {  ed_mishmash, ed_dict, ed_tags, ed_1, ed_plus, ed_2, ed_3, ed_32, ed_4, ed_41, ed_x1, ed_x11, ed_x2,
                ed_50, ed_51, ed_52, ed_53,
                ed_jan05, ed_jan06, ed_jan07, ed_jan10, ed_jul10, ed_jan12, ed_jan13, ed_jan14, ed_jul17, ed_may20, ed_jul20, ed_jan21,
                ed_svg_1_0, ed_svg_1_1, ed_svg_1_2_tiny, ed_svg_1_2_full, ed_svg_2_0, ed_math_1, ed_math_2, ed_math_3, ed_math_4,
                ed_iso_8859_1, ed_csp,
                ed_rfc_1867, ed_rfc_1980, ed_rfc_3986, ed_rfc_3966, ed_rfc_6265, ed_rfc_7231, ed_rfc_7234, ed_rfc_8288,
                ed_w3, ed_mql, ed_ariaAug2020, ed_mozilla, ed_ecma,
                ed_microdata, ed_microformats, ed_mimetype, ed_rdf, ed_apache, ed_so_11,
                ed_imaginary } e_doc;
const e_doc last_doc = ed_imaginary;
typedef enum {  db_auto, db_usescript, db_nochange, db_resetsize, db_ideographic, db_hanging, db_mathematical,
                db_central, db_middle, db_textafteredge, db_textbeforeedge, db_inherit } e_dominantbaseline;
typedef enum { dsc_disc, dsc_square, dsc_circle } e_dsc;
typedef enum { dtv_disc, dtv_square, dtv_circle, dtv_triangle } e_dsctv;
typedef enum { em_duplicate, em_wrap, em_none } e_edgemode;
typedef enum { ed_changed, ed_deleted, ed_inserted, ed_moved } e_edit;
typedef enum { ef_embed, ef_overlay, ef_new, ef_replace } e_effect;

typedef enum {
    elem_undefined,

    elem_faux_document, elem_faux_asp, elem_faux_cdata, elem_faux_char, elem_faux_code, elem_faux_comment, elem_faux_doctype, elem_faux_php,
        elem_faux_ssi, elem_faux_stylesheet, elem_faux_text, elem_faux_xml, elem_faux_whitespace,

    elem_a, elem_abbr, elem_abbrev, elem_above, elem_abs, elem_abstract, elem_access, elem_acronym, elem_action, elem_added, elem_addeventlistener,
        elem_address, elem_altglyph, elem_altglyphdef, elem_altglyphitem, elem_and, elem_animate, elem_animatecolour, elem_animatemotion,
        elem_animatetransform, elem_animation, elem_annotation, elem_annotation_xml, elem_applet, elem_apply, elem_approx, elem_arccos, elem_arcsin,
        elem_arctan, elem_arccosh, elem_arccot, elem_arccoth, elem_arccsc, elem_arccsch, elem_arcsec, elem_arcsech, elem_arcsinh, elem_arctanh,
        elem_area, elem_arg, elem_array, elem_article, elem_aside, elem_atop, elem_au, elem_audio,
    elem_b, elem_banner, elem_bar, elem_base, elem_basefont, elem_bdi, elem_bdo, elem_below, elem_bgsound, elem_big, elem_bind, elem_blink, elem_blockcode,
        elem_blockquote, elem_body, elem_box, elem_bq, elem_br, elem_bt, elem_button, elem_bvar, elem_byline,
    elem_canvas, elem_caption, elem_card, elem_cartesianproduct, elem_cbytes, elem_cdata, elem_ceiling, elem_centre, elem_cerror, elem_changed, elem_choose,
        elem_ci, elem_circle, elem_cite, elem_clippath, elem_cmd, elem_cn, elem_code, elem_codomain, elem_col, elem_colgroup, elem_colourprofile, elem_command,
        elem_comment, elem_complexes, elem_compose, elem_condition, elem_conjugate, elem_content, elem_cos, elem_cosh, elem_cot, elem_coth, elem_credit, elem_cs,
        elem_csc, elem_csch, elem_csymbol, elem_curl, elem_cursor,
    elem_data, elem_datalist, elem_dd, elem_ddot, elem_declare, elem_defs, elem_degree, elem_del, elem_desc, elem_details, elem_determinant, elem_dfn,
        elem_di, elem_dialogue, elem_diff, elem_dir, elem_discard, elem_dispatchevent, elem_div, elem_divergence, elem_divide, elem_dl, elem_domain,
        elem_domainofapplication, elem_dot, elem_dt,
    elem_element, elem_elementdef, elem_ellipse, elem_em, elem_embed, elem_emptyset, elem_eq, elem_equivalent, elem_eulergamma, elem_event_source,
        elem_eventsource, elem_exists, elem_exp, elem_exponentiale, elem_extensiondefs,
    elem_factorial, elem_factorof, elem_false, elem_feblend, elem_fecolour, elem_fecolourmatrix, elem_fecomponenttransfer, elem_fecomposite,
        elem_feconvolvematrix, elem_fediffuselighting, elem_fedisplacementmap, elem_fedistantlight, elem_fedropshadow, elem_feflood, elem_fefunca,
        elem_fefuncb, elem_fefuncg, elem_fefuncr, elem_fegaussianblur, elem_feimage, elem_femerge, elem_femergenode, elem_femorphology, elem_feoffset,
        elem_fepointlight, elem_fespecularlighting, elem_fespotlight, elem_fetile, elem_feturbulence, elem_fieldset, elem_fig, elem_figcaption,
        elem_figure, elem_filter, elem_floor, elem_flowdiv, elem_flowimage, elem_flowline, elem_flowpara, elem_flowref, elem_flowregion,
        elem_flowregionbreak, elem_flowregionexclude, elem_flowroot, elem_flowspan, elem_flowtref, elem_fn, elem_font, elem_fontface, elem_fontfaceformat,
        elem_fontfacename, elem_fontfacesrc, elem_fontfaceuri, elem_footer, elem_footnote, elem_forall, elem_foreignobject, elem_form, elem_frame,
        elem_frameset,
    elem_g, elem_gcd, elem_geq, elem_glyph, elem_glyphref, elem_grad, elem_gt,
    elem_h, elem_h1, elem_h2, elem_h3, elem_h4, elem_h5, elem_h6, elem_handler, elem_hat, elem_head, elem_header, elem_hgroup, elem_hint, elem_hkern,
        elem_hp1, elem_hp2, elem_hp3, elem_hp4, elem_hp5, elem_hp6, elem_hr, elem_html, elem_htmlplus,
    elem_i, elem_ident, elem_iframe, elem_ilayer, elem_image, elem_imaginary, elem_imaginaryi, elem_img, elem_implies, elem_in, elem_infinity, elem_integers,
        elem_input, elem_ins, elem_int, elem_intersect, elem_interval, elem_inverse, elem_isindex, elem_item,
    elem_kbd, elem_keygen,
    elem_l, elem_label, elem_lambda, elem_lang, elem_laplacian, elem_layer, elem_lcm, elem_left, elem_legend, elem_leq, elem_lh, elem_li, elem_limit,
        elem_line, elem_lineargradient, elem_link, elem_list, elem_listener, elem_listing, elem_lit, elem_ln, elem_loc, elem_log, elem_logbase, elem_lowlimit,
        elem_lt,
    elem_m, elem_maction, elem_main, elem_maligngroup, elem_malignmark, elem_map, elem_margin, elem_mark, elem_marker, elem_marquee, elem_mask, elem_math, elem_matrix,
        elem_matrixrow, elem_max, elem_mean, elem_median, elem_menclose, elem_menu, elem_menuitem, elem_menulabel, elem_merror, elem_meta, elem_metadata, elem_meter,
        elem_mfenced, elem_mfrac, elem_mglyph, elem_mh, elem_mi, elem_min, elem_minus, elem_missingglyph, elem_mlabeledtr, elem_mlongdiv, elem_mmultiscripts,
        elem_mn, elem_mo, elem_mode, elem_moment, elem_momentabout, elem_mover, elem_mpadded, elem_mpath, elem_mphantom, elem_mprescripts, elem_mroot, elem_mrow,
        elem_ms, elem_mscarries, elem_mscarry, elem_msgroup, elem_msline, elem_mspace, elem_msqrt, elem_msrow, elem_mstack, elem_mstyle, elem_msub, elem_msubsup,
        elem_msup, elem_mtable, elem_mtd, elem_mtext, elem_mtr, elem_multicol, elem_munder, elem_munderover,
    elem_naturalnumbers, elem_nav, elem_navigation, elem_neq, elem_nextid, elem_nl, elem_nobr, elem_noembed, elem_noframes, elem_none, elem_noscript, elem_not,
        elem_notanumber, elem_note, elem_notin, elem_notprsubset, elem_notsubset,
    elem_object, elem_of, elem_ol, elem_online, elem_optgroup, elem_option, elem_or, elem_otherwise, elem_outerproduct, elem_output, elem_over, elem_overlay,
    elem_p, elem_page, elem_pageset, elem_param, elem_partialdiff, elem_path, elem_pattern, elem_person, elem_pi, elem_picture, elem_piece, elem_piecewise,
        elem_plaintext, elem_plus, elem_polygon, elem_polyline, elem_power, elem_pre, elem_prefetch, elem_preventdefault, elem_primes, elem_printed,
        elem_product, elem_progress, elem_prototype, elem_prsubset,
    elem_q, elem_quote, elem_quotient,
    elem_radialgradient, elem_range, elem_rationals, elem_rb, elem_rbc, elem_real, elem_reals, elem_rect, elem_refcontent, elem_reln, elem_rem, elem_removed,
        elem_removeeventlistener, elem_render, elem_right, elem_root, elem_row, elem_rp, elem_rt, elem_rtc, elem_ruby,
    elem_s, elem_samp, elem_scalarproduct, elem_script, elem_sdev, elem_sec, elem_sech, elem_section, elem_select, elem_selector, elem_semantics, elem_sep,
        elem_separator, elem_set, elem_setdiff, elem_shadow, elem_share, elem_sidebar, elem_sin, elem_sinh, elem_slot, elem_small, elem_solidcolour, elem_source,
        elem_spacer, elem_span, elem_spot, elem_sqrt, elem_standby, elem_stop, elem_stoppropagation, elem_strike, elem_strong, elem_style, elem_sub, elem_subset,
        elem_sum, elem_summary, elem_sup, elem_svg, elem_switch, elem_symbol,
    elem_t, elem_tab, elem_table, elem_tan, elem_tanh, elem_tbody, elem_tbreak, elem_td, elem_template, elem_tendsto, elem_text, elem_textarea, elem_textpath,
        elem_tfoot, elem_th, elem_thead, elem_tilde, elem_time, elem_times, elem_title, elem_tr, elem_track, elem_traitdef, elem_transition, elem_transformer,
        elem_transpose, elem_tref, elem_true, elem_tspan, elem_tt,
    elem_u, elem_ul, elem_union, elem_uplimit, elem_use,
    elem_var, elem_variance, elem_veaffine, elem_vec, elem_vector, elem_vectoreffect, elem_vectorproduct, elem_veexclude, elem_vefill, elem_veintersect,
        elem_vejoin, elem_vemarker, elem_vemarkerpath, elem_vepath, elem_vepathref, elem_vereverse, elem_vesetback, elem_vestroke, elem_vestrokepath,
        elem_veunion, elem_video, elem_view, elem_vkern,
    elem_wbr, elem_webmention,
    elem_xa, elem_xml, elem_xmp, elem_xor,

    elem_error
} e_element_tag;
const e_element_tag last_element_tag = elem_error;
typedef unsigned int e_element;

inline bool is_faux_element (const e_element e) { return (e >= elem_faux_document) && (e <= elem_faux_whitespace); }
inline bool is_error_element (const e_element e) { return (e == elem_error); }
inline bool is_undefined_element (const e_element e) { return (e == elem_undefined); }
inline bool is_standard_element (const e_element e) { return (e >= elem_a) && (e <= elem_xor); }

typedef enum { ee_www, e_multi, ee_text } e_enctype;
typedef enum { ekh_done, ekh_enter, ekh_go, ekh_next, ekh_previous, ekh_search, ekh_send } e_enterkeyhint;
typedef enum { emi_good, emi_math, emi_not_svg, emi_svg, emi_rdf } e_emi;
typedef enum { fa_bleedleft, fa_left, fa_centre, fa_right, fa_bleedright, fa_justify } e_figalign;
typedef enum { fa_freeze, fa_remove } e_fillanim;
typedef enum { fr_nonzero, fr_evenodd, fr_inherit } e_fillrule;
typedef enum { fi_sourcegraphic, fi_sourcealpha, fi_backgroundimage, fi_backgroundalpha, fi_fillpaint, fi_strokepaint } e_filter_in;

typedef enum {
    fc_aliceblue, fc_antiquewhite, fc_aqua, fc_aquamarine, fc_azure, fc_beige, fc_bisque, fc_black, fc_blanchedalmond, fc_blue,
    fc_blueviolet, fc_brown, fc_burlywood, fc_cadetblue, fc_chartreuse, fc_chocolate, fc_coral, fc_cornflowerblue, fc_cornsilk,
    fc_crimson, fc_cyan, fc_darkblue, fc_darkcyan, fc_darkgoldenrod, fc_darkgray, fc_darkgreen, fc_darkgrey, fc_darkkhaki,
    fc_darkmagenta, fc_darkolivegreen, fc_darkorange, fc_darkorchid, fc_darkred, fc_darksalmon, fc_darkseagreen, fc_darkslateblue,
    fc_darkslategray, fc_darkslategrey, fc_darkturquoise, fc_darkviolet, fc_deeppink, fc_deepskyblue, fc_dimgray, fc_dimgrey,
    fc_dodgerblue, fc_firebrick, fc_floralwhite, fc_forestgreen, fc_fuchsia, fc_gainsboro, fc_ghostwhite, fc_gold, fc_goldenrod,
    fc_gray, fc_green, fc_greenyellow, fc_grey, fc_honeydew, fc_hotpink, fc_indianred, fc_indigo, fc_ivory, fc_khaki, fc_lavender,
    fc_lavenderblush, fc_lawngreen, fc_lemonchiffon, fc_lightblue, fc_lightcoral, fc_lightcyan, fc_lightgoldenrodyellow,
    fc_lightgray, fc_lightgreen, fc_lightgrey, fc_lightpink, fc_lightsalmon, fc_lightseagreen, fc_lightskyblue, fc_lightslategray,
    fc_lightslategrey, fc_lightsteelblue, fc_lightyellow, fc_lime, fc_limegreen, fc_linen, fc_magenta, fc_maroon,
    fc_mediumaquamarine, fc_mediumblue, fc_mediumorchid, fc_mediumpurple, fc_mediumseagreen, fc_mediumslateblue,
    fc_mediumspringgreen, fc_mediumturquoise, fc_mediumvioletred, fc_midnightblue, fc_mintcream, fc_mistyrose, fc_moccasin,
    fc_navajowhite, fc_navy, fc_oldlace, fc_olive, fc_olivedrab, fc_orange, fc_orangered, fc_orchid, fc_palegoldenrod,
    fc_palegreen, fc_paleturquoise, fc_palevioletred, fc_papayawhip, fc_peachpuff, fc_peru, fc_pink, fc_plum, fc_powderblue,
    fc_purple, fc_rebeccapurple , fc_red , fc_rosybrown, fc_royalblue, fc_saddlebrown, fc_salmon, fc_sandybrown, fc_seagreen,
    fc_seashell, fc_sienna, fc_silver, fc_skyblue, fc_slateblue, fc_slategray, fc_slategrey, fc_snow, fc_springgreen,
    fc_steelblue, fc_tan, fc_teal, fc_thistle, fc_tomato, fc_transparent, fc_turquoise, fc_violet, fc_wheat, fc_white, fc_whitesmoke,
    fc_yellow, fc_yellowgreen
} e_fixedcolour;

typedef enum { fs_italic, fs_normal } e_fontstyle;
typedef enum { fmw_bold, fmw_normal } e_math_fontweight;
typedef enum { fn_normal, fn_italic, fn_oblique } e_fontnia;
typedef unsigned short e_format;
typedef enum { f4_blank, f4_parent, f4_self, fr_top } e_frame4;
typedef enum { gu_userspaceonuse, gu_objectboundingbox } e_gradientunits;
typedef enum { al_left, al_center, al_right, al_justify, al_char } e_halign;

typedef enum
{   he_context,
    he_allow, he_cache_control, he_content_disposition, he_content_encoding, he_content_language, he_content_location, he_content_script_type,
    he_content_security_policy, he_content_security_policy_report_only, he_content_style_type, he_content_type, he_date,
    he_default_style, he_expires, he_ext_cache, he_imagetoolbar, he_last_modified, he_location, he_pics_label, he_pragma,
    he_refresh, he_set_cookie, he_vary, he_window_target, he_www_authenticate, he_x_ua_compatible,
    // HTML 2
    he_keywords, he_reply_to,
    // WhatWg
    he_accept, he_accept_language, he_cookie, he_corp, he_link, he_origin, he_referrer, he_referrer_policy, he_x_content_type_options,
    // Ms DHTML
    he_page_enter, he_page_exit, he_site_enter, he_site_exit,
    // deprecated
    he_x_content_security_policy, he_webkit_csp,
    he_error } e_httpequiv;

typedef enum { ehv_horizontal, ehv_vertical } e_hv;
typedef enum { ir_auto, ir_optimisespeed, ir_optimisequality, ir_inherit } e_imagerendering;
typedef enum { ei_auto, ei_high, ei_low } e_importance;
typedef enum { ia_left, ia_centre, ia_right, ia_auto, ia_id } e_indentalign;
typedef enum { ifl_before, ifl_after, ifl_duplicate } e_infixlinebreakstyle;
typedef enum { ink_sourcegraphic, ink_sourcealpha, ink_backgroundimage, ink_backgroundalpha, ink_fillpaint, ink_strokepaint } e_inky;
typedef enum {  im_email, im_fullwidthlatin, im_katakana, im_kana, im_kananame, im_latin, im_latinname, im_latinprose, im_numeric,
                im_tel, im_url, im_verbatim, im_decimal, im_none, im_search, im_text } e_inputmode;
typedef enum {  ip_audio, ip_checkbox, ip_date, ip_float, ip_image, ip_int, ip_radio, ip_range, ip_reset, ip_scribble, ip_submit,
                ip_text, ip_url } e_inputplus;
typedef enum { it_checkbox, it_file, it_hidden, it_image, it_password, it_radio, it_reset, it_submit, it_text } e_inputtype;
typedef enum { i3_checkbox, i3_file, i3_hidden, i3_image, i3_password, i3_radio, i3_range, i3_reset, i3_scribble, i3_submit, i3_text } e_inputtype3;
typedef enum { i2_checkbox, i2_file, i2_hidden, i2_image, i2_password, i2_radio, i2_reset, i2_submit, i2_text } e_inputtype32;
typedef enum { i4_button, i4_checkbox, i4_file, i4_hidden, i4_image, i4_password, i4_radio, i4_reset, i4_submit, i4_text } e_inputtype4;
typedef enum {  i5_button, i5_checkbox, i5_colour, i5_date, i5_datetime, i5_datetime_local, i5_email, i5_file, i5_hidden, i5_image, i5_month, i5_number,
                i5_password, i5_radio, i5_reset, i5_range, i5_search, i5_submit, i5_tel, i5_text, i5_time, i5_url, i5_week } e_inputtype5;
typedef enum { itemprop_bespoke, itemprop_schema, itemprop_microformat } e_itemprop_category;
typedef enum { itemtype_none, itemtype_schema, itemtype_microformat, itemtype_rel } e_itemtype_category;
typedef enum { ky_dsa, ky_ec, ky_rsa } e_keytype;
typedef enum { k_subtitles, k_captions, k_descriptions, k_chapters, k_metadata } e_kind;

typedef enum { la_context,

    // iso-639-1
    la_ab, la_aa, la_af, la_ak, la_sq, la_am, la_ar, la_an, la_hy, la_as, la_av,
    la_ae, la_ay, la_az, la_bm, la_ba, la_eu, la_be, la_bn, la_bh, la_bi, la_bs,
    la_br, la_bg, la_my, la_ca, la_ch, la_ce, la_ny, la_zh, la_cv, la_kw, la_co,
    la_cr, la_hr, la_cs, la_da, la_dv, la_nl, la_dz, la_en, la_eo, la_et, la_ee,
    la_fo, la_fj, la_fi, la_fr, la_ff, la_gl, la_ka, la_de, la_el, la_gn, la_gu,
    la_ht, la_ha, la_he, la_hz, la_hi, la_ho, la_hu, la_ia, la_id, la_ie, la_ga,
    la_ig, la_ik, la_io, la_is, la_it, la_iu, la_ja, la_jv, la_kl, la_kn, la_kr,
    la_ks, la_kk, la_km, la_ki, la_rw, la_ky, la_kv, la_kg, la_ko, la_ku, la_kj,
    la_la, la_lb, la_lg, la_li, la_ln, la_lo, la_lt, la_lu, la_lv, la_gv, la_mk,
    la_mg, la_ms, la_ml, la_mt, la_mi, la_mr, la_mh, la_mn, la_na, la_nv, la_nd,
    la_ne, la_ng, la_nb, la_nn, la_no, la_ii, la_nr, la_oc, la_oj, la_cu, la_om,
    la_or, la_os, la_pa, la_pi, la_fa, la_pl, la_ps, la_pt, la_qu, la_rm, la_rn,
    la_ro, la_ru, la_sa, la_sc, la_sd, la_se, la_sm, la_sg, la_sr, la_gd, la_sn,
    la_si, la_sk, la_sl, la_so, la_st, la_es, la_su, la_sw, la_ss, la_sv, la_ta,
    la_te, la_tg, la_th, la_ti, la_bo, la_tk, la_tl, la_tn, la_to, la_tr, la_ts,
    la_tt, la_tw, la_ty, la_ug, la_uk, la_ur, la_uz, la_ve, la_vi, la_vo, la_wa,
    la_cy, la_wo, la_fy, la_xh, la_yi, la_yo, la_za, la_zu,

    // iso-639-2
    la_aar, la_abk, la_ace, la_ach, la_ada, la_ady, la_afa, la_afh, la_afr, la_ain, la_aka,
    la_akk, la_alb, la_ale, la_alg, la_alt, la_amh, la_ang, la_anp, la_apa, la_ara, la_arc,
    la_arg, la_arm, la_arn, la_arp, la_art, la_arw, la_asm, la_ast, la_ath, la_aus, la_ava,
    la_ave, la_awa, la_aym, la_aze, la_bad, la_bai, la_bak, la_bal, la_bam, la_ban, la_baq,
    la_bas, la_bat, la_bej, la_bel, la_bem, la_ben, la_ber, la_bho, la_bih, la_bik, la_bin,
    la_bis, la_bla, la_bnt, la_bod, la_bos, la_bra, la_bre, la_btk, la_bua, la_bug, la_bul,
    la_bur, la_byn, la_cad, la_cai, la_car, la_cat, la_cau, la_ceb, la_cel, la_ces, la_cha,
    la_chb, la_che, la_chg, la_chi, la_chk, la_chm, la_chn, la_cho, la_chp, la_chr, la_chu,
    la_chv, la_chy, la_cmc, la_cnr, la_cop, la_cor, la_cos, la_cpe, la_cpf, la_cpp, la_cre,
    la_crh, la_crp, la_csb, la_cus, la_cym, la_cze, la_dak, la_dan, la_dar, la_day, la_del,
    la_den, la_deu, la_dgr, la_din, la_div, la_doi, la_dra, la_dsb, la_dua, la_dum, la_dut,
    la_dyu, la_dzo, la_efi, la_egy, la_eka, la_ell, la_elx, la_eng, la_enm, la_epo, la_est,
    la_eus, la_ewe, la_ewo, la_fan, la_fao, la_fas, la_fat, la_fij, la_fil, la_fin, la_fiu,
    la_fon, la_fra, la_fre, la_frm, la_fro, la_frr, la_frs, la_fry, la_ful, la_fur, la_gaa,
    la_gay, la_gba, la_gem, la_geo, la_ger, la_gez, la_gil, la_gla, la_gle, la_glg, la_glv,
    la_gmh, la_goh, la_gon, la_gor, la_got, la_grb, la_grc, la_gre, la_grn, la_gsw, la_guj,
    la_gwi, la_hai, la_hat, la_hau, la_haw, la_heb, la_her, la_hil, la_him, la_hin, la_hit,
    la_hmn, la_hmo, la_hrv, la_hsb, la_hun, la_hup, la_hye, la_iba, la_ibo, la_ice, la_ido,
    la_iii, la_ijo, la_iku, la_ile, la_ilo, la_ina, la_inc, la_ind, la_ine, la_inh, la_ipk,
    la_ira, la_iro, la_isl, la_ita, la_jav, la_jbo, la_jpn, la_jpr, la_jrb, la_kaa, la_kab,
    la_kac, la_kal, la_kam, la_kan, la_kar, la_kas, la_kat, la_kau, la_kaw, la_kaz, la_kbd,
    la_kha, la_khi, la_khm, la_kho, la_kik, la_kin, la_kir, la_kmb, la_kok, la_kom, la_kon,
    la_kor, la_kos, la_kpe, la_krc, la_krl, la_kro, la_kru, la_kua, la_kum, la_kur, la_kut,
    la_lad, la_lah, la_lam, la_lao, la_lat, la_lav, la_lez, la_lim, la_lin, la_lit, la_lol,
    la_loz, la_ltz, la_lua, la_lub, la_lug, la_lui, la_lun, la_luo, la_lus, la_mac, la_mad,
    la_mag, la_mah, la_mai, la_mak, la_mal, la_man, la_mao, la_map, la_mar, la_mas, la_may,
    la_mdf, la_mdr, la_men, la_mga, la_mic, la_min, la_mis, la_mkd, la_mkh, la_mlg, la_mlt,
    la_mnc, la_mni, la_mno, la_moh, la_mon, la_mos, la_mri, la_msa, la_mul, la_mun, la_mus,
    la_mwl, la_mwr, la_mya, la_myn, la_myv, la_nah, la_nai, la_nap, la_nau, la_nav, la_nbl,
    la_nde, la_ndo, la_nds, la_nep, la_new, la_nia, la_nic, la_niu, la_nld, la_nno, la_nob,
    la_nog, la_non, la_nor, la_nqo, la_nso, la_nub, la_nwc, la_nya, la_nym, la_nyn, la_nyo,
    la_nzi, la_oci, la_oji, la_ori, la_orm, la_osa, la_oss, la_ota, la_oto, la_paa, la_pag,
    la_pal, la_pam, la_pan, la_pap, la_pau, la_peo, la_per, la_phi, la_phn, la_pli, la_pol,
    la_pon, la_por, la_pra, la_pro, la_pus, la_que, la_raj, la_rap, la_rar, la_roa, la_roh,
    la_rom, la_ron, la_rum, la_run, la_rup, la_rus, la_sad, la_sag, la_sah, la_sai, la_sal,
    la_sam, la_san, la_sas, la_sat, la_scn, la_sco, la_sel, la_sem, la_sga, la_sgn, la_shn,
    la_sid, la_sin, la_sio, la_sit, la_sla, la_slk, la_slo, la_slv, la_sma, la_sme, la_smi,
    la_smj, la_smn, la_smo, la_sms, la_sna, la_snd, la_snk, la_sog, la_som, la_son, la_sot,
    la_spa, la_sqi, la_srd, la_srn, la_srp, la_srr, la_ssa, la_ssw, la_suk, la_sun, la_sus,
    la_sux, la_swa, la_swe, la_syc, la_syr, la_tah, la_tai, la_tam, la_tat, la_tel, la_tem,
    la_ter, la_tet, la_tgk, la_tgl, la_tha, la_tib, la_tig, la_tir, la_tiv, la_tkl, la_tlh,
    la_tli, la_tmh, la_tog, la_ton, la_tpi, la_tsi, la_tsn, la_tso, la_tuk, la_tum, la_tup,
    la_tur, la_tut, la_tvl, la_twi, la_tyv, la_udm, la_uga, la_uig, la_ukr, la_umb, la_und,
    la_urd, la_uzb, la_vai, la_ven, la_vie, la_vol, la_vot, la_wak, la_wal, la_war, la_was,
    la_wel, la_wen, la_wln, la_wol, la_xal, la_xho, la_yao, la_yap, la_yid, la_yor, la_ypk,
    la_zap, la_zbl, la_zen, la_zgh, la_zha, la_zho, la_znd, la_zul, la_zun, la_zxx, la_zza,

    // archaic but accepted for historic reasons
    la_i,

    la_illegal } e_lang;

typedef enum { lar_left, lar_all, lar_right, lar_none } e_larnalign;
typedef enum { lay_irrelevant, lay_relevant } e_layout;
typedef enum { lcr_left, lcr_centre, lcr_right } e_lcralign;
typedef enum { crd_left, crd_centre, crd_right, crd_decimalpoint } e_lcrd;
typedef enum { ln_left, ln_centre, ln_right, ln_none } e_lcrnalign;
typedef enum { l_cm, l_mm, l_q, l_in, l_pc, l_pt, l_px } e_length_absolute;
typedef enum { l_percent, l_star, l_em, l_ex, l_cap, l_ch, l_ic, l_rem, l_lh, l_rlh, l_vw, l_vh, l_vi, l_vb, l_vmin, l_vmax } e_length_relative;
typedef enum { lad_spacing, lad_spacingandglyphs } e_lengthadjust;
typedef enum { lb_auto, lb_newline, lb_indentingnewline, lb_nobreak, lb_goodbreak, lb_badbreak } e_linebreak;
typedef enum { ls_before, ls_after, ls_duplicate, ls_infixlinebreakstyle } e_linebreakstyle;
typedef enum { lc_butt, lc_round, lc_square, lc_inherit } e_linecap;
typedef enum { lj_miter, lj_round, lj_bevel, lj_inherit } e_linejoin;
typedef enum { lp_rel, lp_anchor, lp_rev, lp_hreflang, lp_media, lp_title, lp_titlestar, lp_type } e_linkparam;
typedef enum { li_1, li_a, li_A, li_i, li_I } e_listtype;
typedef enum { b_eager, b_lazy } e_loading;
typedef enum {  ls_lefttop, ls_stackedrightright, ls_mediumstackedrightright, ls_shortstackedrightright, ls_righttop,
                ls_leftslashright, ls_leftketbraright, ls_rightequalright, ls_stackedleftleft, ls_stackedleftlinetop } e_longdivstyle;
typedef enum { lra_all, lra_left, lra_right } e_lraalign;
typedef enum { lr_left, lr_right } e_lralign;
typedef enum { mah_go, mah_done, mah_next, mah_search, mah_send } e_mah;
typedef enum { mu_stroke_width, mu_userspace } e_markerunits;
typedef enum { ma_axis, ma_baseline, ma_bottom, ma_centre, ma_top } e_mathalign;
typedef enum { mc_open, mc_closed, mc_openclosed, mc_closedopen } e_mathclosure;
typedef enum { ml_w, ml_nw, ml_n, ml_ne, ml_e, ml_se, ml_s, ml_sw } e_mathlocation;
typedef enum { mo_prefix, mo_infix, mo_functionmodel } e_mathoccurence;
typedef enum { mo_numeric, mo_lexicographic } m_mathorder;
typedef enum { ov_elide, ov_linebreak, ov_scale, ov_scroll, ov_truncate } e_mathoverflow;
typedef enum { ms_global, ms_local } e_mathscope;
typedef enum { math_none, math_1, math_2, math_3, math_4 } e_mathversion;
typedef enum { mf_infix, mf_prefix, mf_postfix } e_mathform;
typedef enum { mf_dash, mf_none, mf_solid } e_mathframe;
typedef enum {  mn_longdiv, mn_actuarial, mn_radical, mn_box, mn_roundedbox, mn_circle, mn_left, mn_right, mn_top, mn_bottom,
                mn_updiagonalstrike, mn_downdiagonalstrike, mn_verticalstrike, mn_horizontalstrike, mn_phasorangle,
                mn_madruwb, mn_uparrow, mn_rightarrow, mn_downarrow, mn_leftarrow, mn_northwestarrow, mn_southwestarrow,
                mn_southeastarrow, mn_northeastarrow, mn_updownarrow, mn_leftrightarrow, mn_northwestsoutheastarrow,
                mn_northeastsouthwestarrow } e_mathnotation;
typedef enum {  mv_normal, mv_bold, mv_italic, mv_bolditalic, mv_doublestruck, mv_boldfraktur, mv_script, mv_boldscript, mv_fraktur,
                mv_sansserif, mv_boldsansserif, mv_sansserifitalic, mv_sansserifbolditalic, mv_monospace, mv_initial, mv_tailed,
                mv_looped, mv_stretched } e_mathvariant;
typedef enum { mt_matrix, mt_saturate, mt_hue_rotate, mt_luminance_alpha } e_matrixtype;
typedef enum { md_all, md_aural, md_braille, md_embossed, md_handheld, md_print, md_projection, md_screen, md_speech, md_tty, md_tv } e_media;
typedef enum {  mef_width, mef_min_width, mef_max_width,
                mef_height, mef_min_height, mef_max_height,
                mef_device_width, mef_min_device_width, mef_max_device_width,
                mef_device_height, mef_min_device_height, mef_max_device_height,
                mef_orientation,
                mef_aspect_ration, mef_min_aspect_ration, mef_max_aspect_ration,
                mef_device_aspect_ratio, mef_min_device_aspect_ratio, mef_max_device_aspect_ratio,
                mef_colour, mef_min_colour, mef_max_colour,
                mef_colour_index, mef_min_colour_index, mef_max_colour_index,
                mef_monochrome, mef_min_monochrome, mef_max_monochrome,
                mef_resolution, mef_min_resolution, mef_max_resolution,
                mef_scan, mef_grid, mef_update, mef_overflow_block, mef_overflow_inline,
                mef_colour_gamut, mef_pointer, mef_hover, mef_any_pointer, mef_any_hover } e_mediafeature;
typedef enum { mk_and, mk_eq, mk_ge, mk_gt, mk_ident, mk_le, mk_lt, mk_or, mk_not, mk_only } e_mediakeyword;
typedef enum { ms_meet, me_slice } e_meetslice;
typedef enum { mi_command, mi_checkbox, mi_radio } e_menuitem;
typedef enum { mt_context, mt_popup, mt_toolbar } e_menutype;
typedef enum { md_delete, md_dialogue, md_get, md_post, md_put } e_method;

typedef enum { mn_context,
// https://www.w3.org/html/wiki/Elements/meta
               mn_application, mn_author, mn_description, mn_generator, mn_keywords,
// HTML 4.01 specification
               mn_identifier,
// http://ec.europa.eu/ipg/content/optimise/metadata/annex2_en.htm
               mn_classification,
// https://www.metatags.org/
               mn_copyright,  // despite metatags opinion, I suggest this metaname still has legal relevance
               // outdated
               mn_contactCity, mn_contactCountry, mn_contactFaxNumber, mn_contactName, mn_contactNetworkAddress, mn_contactOrganization,
               mn_contactPhoneNumber, mn_contactStreetAddress1, mn_contactZipcode, mn_creation, mn_distribution,
               mn_host, mn_host_admin, mn_id, mn_identifier_url, mn_language, mn_linkage, mn_note, mn_operator, mn_presdate,
               mn_rating, mn_subject, mn_template, mn_version,
// https://gist.github.com/lancejpollard/1978404
                // archaic
                mn_abstract, mn_coverage, mn_og_email, mn_og_phone_number, mn_og_fax_number, mn_og_latitude, mn_og_longitude,
                mn_og_street_address, mn_og_locality, mn_og_region, mn_og_postal_code, mn_og_country_name, mn_microid,
                mn_owner, mn_revised, mn_topic, mn_summary, mn_tweetmeme_title,
// https://wiki.whatwg.org/wiki/MetaExtensions
               // valid proposals
               mn_aglsterms_accessmode, mn_aglsterms_accessibility, mn_aglsterms_act, mn_aglsterms_aggregationlevel, mn_aglsterms_allow_search,
               mn_aglsterms_availability, mn_aglsterms_case, mn_aglsterms_category, mn_aglsterms_datelicensed, mn_aglsterms_documenttype,
               mn_aglsterms_function, mn_aglsterms_isbasedon, mn_aglsterms_isbasisfor, mn_aglsterms_jurisdiction, mn_aglsterms_mandate,
               mn_aglsterms_protectivemarking, mn_aglsterms_regulation, mn_aglsterms_servicetype, mn_dcs_dcssta, mn_essaydirectory,
               mn_flblogauthor, mn_fsdatecreation, mn_fsdatepublish, mn_fsflcontent, mn_fslanguage, mn_fsonsitemap, mn_fspagedescription,
               mn_fspagename, mn_fssearchable, mn_fssection, mn_fswritertoolpagetype, mn_ie_rm_off, mn_mssmarttagspreventparsing,
               mn_repostusapikey, mn_resourceloaderdynamicstyles, mn_wt_si_n, mn_wt_si_p, mn_wt_si_x, mn_zoomcategory, mn_zoomdescription,
               mn_zoomimage, mn_zoompageboost, mn_zoomtitle, mn_zoomwords, mn_alexaverifyid, mn_apple_itunes_app, mn_apple_mobile_web_app_capable,
               mn_apple_mobile_web_app_status_bar_style, mn_apple_mobile_web_app_title, mn_apple_touch_fullscreen, mn_application_name,
               mn_application_url, mn_appstore_bundle_id, mn_appstore_developer_url, mn_appstore_store_id, mn_audience, mn_bitcoin,
               mn_blazerr_secure, mn_blazerr_seo, mn_blazerr_ssl, mn_blazerr_support_id_noncookies, mn_blazerr_support_identifier,
               mn_bug_blocked, mn_bug_comment, mn_bug_component, mn_bug_product, mn_bug_short_desc, mn_cfia_gdr_activity,
               mn_cfia_gdr_commodity, mn_cfia_gdr_include, mn_cfia_gdr_program, mn_citation_author, mn_citation_author_email,
               mn_citation_author_institution, mn_citation_conference_title, mn_citation_date, mn_citation_dissertation_institution,
               mn_citation_doi, mn_citation_firstpage, mn_citation_fulltext_html_url, mn_citation_isbn, mn_citation_issn, mn_citation_issue,
               mn_citation_journal_abbrev, mn_citation_journal_title, mn_citation_keywords, mn_citation_language, mn_citation_lastpage,
               mn_citation_pdf_url, mn_citation_publication_date, mn_citation_publisher, mn_citation_technical_report_institution,
               mn_citation_technical_report_number, mn_citation_title, mn_citation_volume, mn_collection, mn_colour_scheme, mn_contact, mn_creator,
               mn_csrf_param, mn_csrf_token, mn_da_anonymiseip, mn_da_contactcompany, mn_da_contactemail, mn_da_contactfirstname,
               mn_da_contactlastname, mn_da_contactname, mn_da_contacttelephone, mn_da_conversioncurrency, mn_da_conversionid,
               mn_da_conversionvalue, mn_da_goalcurrency, mn_da_goalid, mn_da_goalvalue, mn_da_interactionselector, mn_da_pagerole,
               mn_da_pagetaxonomy, mn_da_pagetitle, mn_da_pageversion, mn_da_sessionid, mn_da_userid, mn_date,

                // https://en.wikipedia.org/wiki/Dublin_Core
               mn_dc_contributor, mn_dc_coverage, mn_dc_creator, mn_dc_date, mn_dc_description, mn_dc_format, mn_dc_identifier,
               mn_dc_language, mn_dc_publisher, mn_dc_relation, mn_dc_rights, mn_dc_source, mn_dc_subject, mn_dc_title, mn_dc_type,

               mn_dcterms_abstract, mn_dcterms_accessrights, mn_dcterms_accrualmethod, mn_dcterms_accrualperiodicity,
               mn_dcterms_accrualpolicy, mn_dcterms_alternative, mn_dcterms_audience, mn_dcterms_available, mn_dcterms_bibliographiccitation,
               mn_dcterms_conformsto, mn_dcterms_contributor, mn_dcterms_coverage, mn_dcterms_created, mn_dcterms_creator,
               mn_dcterms_date, mn_dcterms_dateaccepted, mn_dcterms_datecopyrighted, mn_dcterms_datesubmitted, mn_dcterms_description,
               mn_dcterms_educationlevel, mn_dcterms_extent, mn_dcterms_format, mn_dcterms_hasformat, mn_dcterms_haspart, mn_dcterms_hasversion,
               mn_dcterms_identifier, mn_dcterms_instructionalmethod, mn_dcterms_isformatof, mn_dcterms_ispartof, mn_dcterms_isreferencedby,
               mn_dcterms_isreplacedby, mn_dcterms_isrequiredby, mn_dcterms_isversionof, mn_dcterms_issued, mn_dcterms_language, mn_dcterms_license,
               mn_dcterms_mediator, mn_dcterms_medium, mn_dcterms_modified, mn_dcterms_provenance, mn_dcterms_publisher, mn_dcterms_references,
               mn_dcterms_relation, mn_dcterms_replaces, mn_dcterms_requires, mn_dcterms_rights, mn_dcterms_rightsholder, mn_dcterms_source,
               mn_dcterms_spatial, mn_dcterms_subject, mn_dcterms_tableofcontents, mn_dcterms_temporal, mn_dcterms_title, mn_dcterms_type,
               mn_dcterms_valid, mn_designer, mn_detectify_verification, mn_entity,
               mn_fdse_description, mn_fdse_index_as, mn_fdse_keywords, mn_fdse_refresh, mn_fdse_robots, mn_format_detection, mn_format_print,
               mn_fragment, mn_gcterms_topictaxonomy, mn_geo_a1, mn_geo_a2, mn_geo_a3, mn_geo_country, mn_geo_lmk, mn_geo_placename, mn_geo_position,
               mn_geo_region, mn_globrix_bathrooms, mn_globrix_bedrooms, mn_globrix_condition, mn_globrix_features, mn_globrix_instruction,
               mn_globrix_latitude, mn_globrix_longitude, mn_globrix_outsidespace, mn_globrix_parking, mn_globrix_period, mn_globrix_poa,
               mn_globrix_postcode, mn_globrix_price, mn_globrix_priceproximity, mn_globrix_tenure, mn_globrix_type, mn_globrix_underoffer,
               mn_go_import, mn_google, mn_google_play_app, mn_google_site_verification,
               mn_gwt_property, mn_handheldfriendly, mn_icas_datetime, mn_icas_datetime_abbr, mn_icas_datetime_day, mn_icas_datetime_long,
               mn_icbm, mn_itemsperpage, mn_keywords_not, mn_meta_date, mn_microtip, mn_mobile_agent, mn_mobile_web_app_capable, mn_mobileoptimized,
               mn_msapplication_tilecolor, mn_msapplication_tileimage, mn_msapplication_config, mn_msapplication_navbutton_color,
               mn_msapplication_notification, mn_msapplication_square150x150logo, mn_msapplication_square310x310logo,
               mn_msapplication_square70x70logo, mn_msapplication_starturl, mn_msapplication_tap_highlight, mn_msapplication_task,
               mn_msapplication_tooltip, mn_msapplication_wide310x150logo, mn_msapplication_window, mn_msvalidate_01, mn_nextgen,
               mn_nibbler_site_verification, mn_nonfiction, mn_norton_safeweb_site_verification, mn_origin, mn_origin_trials, mn_p_domain_verify, mn_page_version,
               mn_pingdom, mn_pinterest, mn_prism_alternatetitle, mn_pro, mn_pro_auth, mn_pro_auth_field, mn_pro_auth_fragment,
               mn_referrer, mn_review_date, mn_revision, mn_revisit_after, mn_rights, mn_rights_standard, mn_robots, mn_rpuplugin,
               mn_rqid, mn_shareaholic_analytics, mn_shareaholic_article_author, mn_shareaholic_article_author_name,
               mn_shareaholic_article_modified_time, mn_shareaholic_article_published_time, mn_shareaholic_article_visibility,
               mn_shareaholic_drupal_version, mn_shareaholic_image, mn_shareaholic_keywords, mn_shareaholic_language, mn_shareaholic_outstreamads,
               mn_shareaholic_shareable_page, mn_shareaholic_site_id, mn_shareaholic_site_name, mn_shareaholic_url, mn_shareaholic_wp_version,
               mn_signet_authors, mn_signet_links, mn_skype_toolbar, mn_startindex, mn_startver, mn_subject_datetime, mn_subject_system,
               mn_theme_colour, mn_thumbnail, mn_topper, mn_topper_major, mn_topper_minor, mn_totalresults, mn_translator, mn_twitter_app_country,
               mn_twitter_app_id_googleplay, mn_twitter_app_id_ipad, mn_twitter_app_id_iphone, mn_twitter_app_name_googleplay,
               mn_twitter_app_name_ipad, mn_twitter_app_name_iphone, mn_twitter_app_url_googleplay, mn_twitter_app_url_ipad,
               mn_twitter_app_url_iphone, mn_twitter_card, mn_twitter_creator, mn_twitter_creator_id, mn_twitter_data1, mn_twitter_data2,
               mn_twitter_description, mn_twitter_domain, mn_twitter_image, mn_twitter_image0, mn_twitter_image1, mn_twitter_image2,
               mn_twitter_image3, mn_twitter_image_height, mn_twitter_image_src, mn_twitter_image_width, mn_twitter_label1, mn_twitter_label2,
               mn_twitter_player, mn_twitter_player_height, mn_twitter_player_stream, mn_twitter_player_stream_content_type,
               mn_twitter_player_width, mn_twitter_site, mn_twitter_site_id, mn_twitter_title, mn_twitter_url, mn_typemetal_formatprefs,
               mn_verify_v1, mn_vfb_version, mn_viewport, mn_web_author, mn_witget, mn_wot_verification, mn_wt_ac, mn_wt_ad, mn_wt_cg_n,
               mn_wt_cg_s, mn_wt_mc_id, mn_wt_sv, mn_wt_ti, mn_y_key, mn_yandex_verification,
               // invalid proposals
               mn_blogcatalog, mn_created, mn_expires, mn_fb_admins, mn_fb_page_id, mn_gm_gpx_v, mn_google_translate_customization, mn_og_description,
               mn_og_image, mn_og_locale, mn_og_site_name, mn_og_title, mn_og_type, mn_og_url, mn_resolutions,
               // rejected propoals
               mn_cache, mn_dir_content_pointer, mn_no_email_collection,
               // http://vancouver-webpages.com/META/metatags.detail.html
               mn_formatter, mn_vw96_object, mn_dc_chem, mn_searchbc,
               mn_author_corporate, mn_author_personal, mn_publisher_email, mn_bookmark,
               mn_ekbu, mn_ekdoctype, mn_ekdocowner, mn_ekdoctech, mn_ekreviewdate, mn_ekarea,
               mn_cc, mn_alias, mn_content_type, mn_sic87, mn_document, mn_build, mn_resource_type, mn_location,
               mn_googlebot, mn_contributor, mn_custodian, mn_custodian_contact, mn_custodian_contact_position,
               mn_east_bounding_coordinate, mn_north_bounding_coordinate, mn_relation, mn_reply_to, mn_south_bounding_coordinate,
               mn_west_bounding_coordinate,
               // https://web.archive.org/web/19971018015804/http://www.mathematik.uni-osnabrueck.de/ak-technik/DMVPreprint-Core.html
               mn_mathdmv_author, mn_mathdmv_title, mn_mathdmv_identifier, mn_mathdmv_pclass, mn_mathdmv_sclass, mn_mathdmv_pacs,
               mn_mathdmv_cr, mn_mathdmv_subject, mn_mathdmv_keywords, mn_mathdmv_upload, mn_mathdmv_update, mn_mathdmv_objecttype,
               mn_mathdmv_series, mn_mathdmv_referencejournals, mn_mathdmv_contact, mn_mathdmv_abstract, mn_mathdmv_notes,
               // https://web.archive.org/web/19991111062508/http://www.htdig.org/meta.html
               mn_htdig_keywords, mn_htdig_noindex, mn_htdig_email, mn_htdig_notification_date, mn_htdig_email_subject,
               // WhatWG Jan 2008
               mn_dns,
                // https://ogp.me/
                mn_og_audio, mn_og_determiner, mn_og_locale_alternate, mn_og_video, mn_og_image_url,mn_og_image_secure_url, mn_og_image_type, mn_og_image_width,
                mn_og_image_height, mn_og_image_alt, mn_og_video_url, mn_og_video_secure_url, mn_og_video_width, mn_og_video_height, mn_og_video_alt,
                mn_og_audio_url, mn_og_audio_secure_url, mn_og_audio_type, mn_music_album, mn_music_album_disc, mn_music_album_track, mn_music_creator, mn_music_duration,
                mn_music_musician, mn_music_release_date, mn_music_song, mn_music_song_disc, mn_music_song_track, mn_video_actor, mn_video_actor_role, mn_video_director,
                mn_video_duration, mn_video_release_date, mn_video_series, mn_video_tag, mn_video_writer, mn_article_author, mn_article_expiration_date,
                mn_article_modified_time, mn_article_published_time, mn_article_section, mn_article_tag, mn_book_author, mn_book_isbn, mn_book_release_date, mn_book_tag,
                mn_profile_first_name, mn_profile_gender, mn_profile_last_name, mn_profile_username,
               // that's it
               mn_illegal } e_metaname;
const e_metaname metaname_first_w3 = mn_application;
const e_metaname metaname_first_eu = mn_classification;
const e_metaname metaname_first_outdated = mn_contactCity;
const e_metaname metaname_first_archaic = mn_abstract;
const e_metaname metaname_first_whatwg = mn_aglsterms_accessmode;
const e_metaname metaname_first_dubious = mn_blogcatalog;
const e_metaname metaname_first_rejected = mn_cache;

typedef enum { mdd_none, mdd_schema, mdd_microformats, mdd_purl } e_microdata_domain;
typedef enum { mc_application, mc_audio, mc_example, mc_font, mc_image, mc_model, mc_multipart, mc_text, mc_video } e_mime_category;

typedef enum {
    mime_context,

    mime_application_1d_interleaved_parityfec, mime_application_3gpdash_qoe_report_xml, mime_application_3gpp_ims_xml, mime_application_A2L, mime_application_activemessage,
    mime_application_activity_json, mime_application_alto_costmap_json, mime_application_alto_costmapfilter_json, mime_application_alto_directory_json, mime_application_alto_endpointprop_json,
    mime_application_alto_endpointpropparams_json, mime_application_alto_endpointcost_json, mime_application_alto_endpointcostparams_json, mime_application_alto_error_json,
    mime_application_alto_networkmapfilter_json, mime_application_alto_networkmap_json, mime_application_alto_updatestreamcontrol_json, mime_application_alto_updatestreamparams_json,
    mime_application_AML, mime_application_andrew_inset, mime_application_applefile, mime_application_ATF, mime_application_ATFX, mime_application_atom_xml, mime_application_atomcat_xml,
    mime_application_atomdeleted_xml, mime_application_atomicmail, mime_application_atomsvc_xml, mime_application_atsc_dwd_xml, mime_application_atsc_dynamic_event_message,
    mime_application_atsc_held_xml, mime_application_atsc_rdt_json, mime_application_atsc_rsat_xml, mime_application_ATXML, mime_application_auth_policy_xml, mime_application_bacnet_xdd_zip,
    mime_application_batch_SMTP, mime_application_beep_xml, mime_application_calendar_json, mime_application_calendar_xml, mime_application_call_completion, mime_application_cals_1840,
    mime_application_cap_xml, mime_application_cbor, mime_application_cbor_seq, mime_application_cccex, mime_application_ccmp_xml, mime_application_ccxml_xml, mime_application_CDFX_XML,
    mime_application_cdmi_capability, mime_application_cdmi_container, mime_application_cdmi_domain, mime_application_cdmi_object, mime_application_cdmi_queue, mime_application_cdni,
    mime_application_CEA, mime_application_cea_2018_xml, mime_application_cellml_xml, mime_application_cfw, mime_application_clue_info_xml, mime_application_clue_xml, mime_application_cms,
    mime_application_cnrp_xml, mime_application_coap_group_json, mime_application_coap_payload, mime_application_commonground, mime_application_conference_info_xml, mime_application_cpl_xml,
    mime_application_cose, mime_application_cose_key, mime_application_cose_key_set, mime_application_csrattrs, mime_application_csta_xml, mime_application_CSTAdata_xml,
    mime_application_csvm_json, mime_application_cwt, mime_application_cybercash, mime_application_dash_xml, mime_application_dashdelta, mime_application_davmount_xml, mime_application_dca_rft,
    mime_application_DCD, mime_application_dec_dx, mime_application_dialog_info_xml, mime_application_dicom, mime_application_dicom_json, mime_application_dicom_xml, mime_application_DII,
    mime_application_DIT, mime_application_dns, mime_application_dns_json, mime_application_dns_message, mime_application_dots_cbor, mime_application_dskpp_xml, mime_application_dssc_der,
    mime_application_dssc_xml, mime_application_dvcs, mime_application_ecmascript, mime_application_EDI_consent, mime_application_EDIFACT, mime_application_EDI_X12, mime_application_efi,
    mime_application_EmergencyCallData_Comment_xml, mime_application_EmergencyCallData_Control_xml, mime_application_EmergencyCallData_DeviceInfo_xml,
    mime_application_EmergencyCallData_eCall_MSD, mime_application_EmergencyCallData_ProviderInfo_xml, mime_application_EmergencyCallData_ServiceInfo_xml,
    mime_application_EmergencyCallData_SubscriberInfo_xml, mime_application_EmergencyCallData_VEDS_xml, mime_application_emma_xml, mime_application_emotionml_xml, mime_application_encaprtp,
    mime_application_epp_xml, mime_application_epub_zip, mime_application_eshop, mime_application_example, mime_application_exi, mime_application_expect_ct_report_json,
    mime_application_fastinfoset, mime_application_fastsoap, mime_application_fdt_xml, mime_application_fhir_json, mime_application_fhir_xml, mime_application_fits, mime_application_flexfec,
    mime_application_font_sfnt, mime_application_font_tdpfr, mime_application_font_woff, mime_application_framework_attributes_xml, mime_application_geo_json, mime_application_geo_json_seq,
    mime_application_geopackage_sqlite3, mime_application_geoxacml_xml, mime_application_gltf_buffer, mime_application_gml_xml, mime_application_gzip, mime_application_H224,
    mime_application_held_xml, mime_application_http, mime_application_hyperstudio, mime_application_ibe_key_request_xml, mime_application_ibe_pkg_reply_xml, mime_application_ibe_pp_data,
    mime_application_iges, mime_application_im_iscomposing_xml, mime_application_index, mime_application_index_cmd, mime_application_index_obj, mime_application_index_response,
    mime_application_index_vnd, mime_application_inkml_xml, mime_application_IOTP, mime_application_ipfix, mime_application_ipp, mime_application_ISUP, mime_application_its_xml,
    mime_application_java, mime_application_java_archive, mime_application_javascript, mime_application_jf2feed_json, mime_application_jose, mime_application_jose_json, mime_application_jrd_json,
    mime_application_json, mime_application_json_patch_json, mime_application_json_seq, mime_application_jwk_json, mime_application_jwk_set_json, mime_application_jwt,
    mime_application_kpml_request_xml, mime_application_kpml_response_xml, mime_application_ld_json, mime_application_lgr_xml, mime_application_link_format, mime_application_load_control_xml,
    mime_application_lost_xml, mime_application_lostsync_xml, mime_application_lpf_zip, mime_application_LXF, mime_application_mac_binhex40, mime_application_macwriteii,
    mime_application_mads_xml, mime_application_marc, mime_application_marcxml_xml, mime_application_mathematica, mime_application_mathml_content_xml,
    mime_application_mathml_presentation_xml, mime_application_mathml_xml, mime_application_mbms_associated_procedure_description_xml, mime_application_mbms_deregister_xml,
    mime_application_mbms_envelope_xml, mime_application_mbms_msk_response_xml, mime_application_mbms_msk_xml, mime_application_mbms_protection_description_xml,
    mime_application_mbms_reception_report_xml, mime_application_mbms_register_response_xml, mime_application_mbms_register_xml, mime_application_mbms_schedule_xml,
    mime_application_mbms_user_service_description_xml, mime_application_mbox, mime_application_media_control_xml, mime_application_media_policy_dataset_xml,
    mime_application_mediaservercontrol_xml, mime_application_merge_patch_json, mime_application_metalink4_xml, mime_application_mets_xml, mime_application_MF4, mime_application_mikey,
    mime_application_mipc, mime_application_mmt_aei_xml, mime_application_mmt_usd_xml, mime_application_mods_xml, mime_application_moss_keys, mime_application_moss_signature,
    mime_application_mosskey_data, mime_application_mosskey_request, mime_application_mp21, mime_application_mp4, mime_application_mpeg4_generic, mime_application_mpeg4_iod,
    mime_application_mpeg4_iod_xmt, mime_application_mrb_consumer_xml, mime_application_mrb_publish_xml, mime_application_msc_ivr_xml, mime_application_msc_mixer_xml,
    mime_application_msword, mime_application_mud_json, mime_application_multipart_core, mime_application_mxf, mime_application_n_quads, mime_application_n_triples, mime_application_nasdata,
    mime_application_news_checkgroups, mime_application_news_groupinfo, mime_application_news_transmission, mime_application_nlsml_xml, mime_application_node, mime_application_nss,
    mime_application_ocsp_request, mime_application_ocsp_response, mime_application_octet_stream, mime_application_odm_xml, mime_application_ODX,
    mime_application_oebps_package_xml, mime_application_ogg, mime_application_oscore, mime_application_oxps, mime_application_p2p_overlay_xml, mime_application_parityfec,
    mime_application_passport, mime_application_patch_ops_error_xml, mime_application_pdf, mime_application_PDX, mime_application_pem_certificate_chain, mime_application_pgp_encrypted,
    mime_application_pgp_keys, mime_application_pgp_signature, mime_application_pidf_diff_xml, mime_application_pidf_xml, mime_application_pkcs10, mime_application_pkcs7_mime,
    mime_application_pkcs7_signature, mime_application_pkcs8, mime_application_pkcs8_encrypted, mime_application_pkcs12, mime_application_pkix_attr_cert, mime_application_pkix_cert,
    mime_application_pkix_crl, mime_application_pkix_pkipath, mime_application_pkixcmp, mime_application_pls_xml, mime_application_poc_settings_xml, mime_application_postscript,
    mime_application_ppsp_tracker_json, mime_application_problem_json, mime_application_problem_xml, mime_application_provenance_xml, mime_application_prs_alvestrand_titrax_sheet,
    mime_application_prs_cww, mime_application_prs_hpub_zip, mime_application_prs_nprend, mime_application_prs_plucker, mime_application_prs_rdf_xml_crypt, mime_application_prs_xsf_xml,
    mime_application_pskc_xml, mime_application_pvd_json, mime_application_rdf_xml, mime_application_route_apd_xml, mime_application_route_s_tsid_xml, mime_application_route_usd_xml,
    mime_application_QSIG, mime_application_raptorfec, mime_application_rdap_json, mime_application_reginfo_xml, mime_application_relax_ng_compact_syntax, mime_application_remote_printing,
    mime_application_reputon_json, mime_application_resource_lists_diff_xml, mime_application_resource_lists_xml, mime_application_rfc_xml, mime_application_riscos,
    mime_application_rlmi_xml, mime_application_rls_services_xml, mime_application_rpki_ghostbusters, mime_application_rpki_manifest, mime_application_rpki_publication,
    mime_application_rpki_roa, mime_application_rpki_updown, mime_application_rss_xml,
    mime_application_rtf, mime_application_rtploopback, mime_application_rtx, mime_application_samlassertion_xml,
    mime_application_samlmetadata_xml, mime_application_sbe, mime_application_sbml_xml, mime_application_scaip_xml, mime_application_scim_json, mime_application_scvp_cv_request,
    mime_application_scvp_cv_response, mime_application_scvp_vp_request, mime_application_scvp_vp_response, mime_application_sdp, mime_application_secevent_jwt,
    mime_application_senml_etch_cbor, mime_application_senml_etch_json, mime_application_senml_exi, mime_application_senml_cbor, mime_application_senml_json, mime_application_senml_xml,
    mime_application_sensml_exi, mime_application_sensml_cbor, mime_application_sensml_json, mime_application_sensml_xml, mime_application_sep_exi, mime_application_sep_xml,
    mime_application_session_info, mime_application_set_payment, mime_application_set_payment_initiation, mime_application_set_registration, mime_application_set_registration_initiation,
    mime_application_sgml, mime_application_sgml_open_catalog, mime_application_shf_xml, mime_application_sieve, mime_application_simple_filter_xml, mime_application_simple_message_summary,
    mime_application_simpleSymbolContainer, mime_application_sipc, mime_application_slate, mime_application_smil, mime_application_smil_xml, mime_application_smpte336m,
    mime_application_soap_fastinfoset, mime_application_soap_xml, mime_application_sparql_query, mime_application_sparql_results_xml, mime_application_spirits_event_xml,
    mime_application_sql, mime_application_srgs, mime_application_srgs_xml, mime_application_sru_xml, mime_application_ssml_xml, mime_application_stix_json, mime_application_swid_xml,
    mime_application_tamp_apex_update, mime_application_tamp_apex_update_confirm, mime_application_tamp_community_update, mime_application_tamp_community_update_confirm,
    mime_application_tamp_error, mime_application_tamp_sequence_adjust, mime_application_tamp_sequence_adjust_confirm, mime_application_tamp_status_query,
    mime_application_tamp_status_response, mime_application_tamp_update, mime_application_tamp_update_confirm, mime_application_taxii_json, mime_application_tcl, mime_application_td_json,
    mime_application_tei_xml, mime_application_TETRA_ISI, mime_application_thraud_xml, mime_application_timestamp_query, mime_application_timestamp_reply, mime_application_timestamped_data,
    mime_application_tlsrpt_gzip, mime_application_tlsrpt_json, mime_application_tnauthlist, mime_application_trickle_ice_sdpfrag, mime_application_trig, mime_application_ttml_xml,
    mime_application_tve_trigger, mime_application_tzif, mime_application_tzif_leap, mime_application_ulpfec, mime_application_urc_grpsheet_xml, mime_application_urc_ressheet_xml,
    mime_application_urc_targetdesc_xml, mime_application_urc_uisocketdesc_xml, mime_application_vbscript, // nearly HTML 4.01 specification example
    mime_application_vcard_json, mime_application_vcard_xml, mime_application_vemmi, mime_application_vnd_1000minds_decision_model_xml, mime_application_vnd_3gpp_access_transfer_events_xml,
    mime_application_vnd_3gpp_bsf_xml, mime_application_vnd_3gpp_GMOP_xml, mime_application_vnd_3gpp_mc_signalling_ear, mime_application_vnd_3gpp_mcdata_affiliation_command_xml,
    mime_application_vnd_3gpp_mcdata_info_xml, mime_application_vnd_3gpp_mcdata_payload, mime_application_vnd_3gpp_mcdata_service_config_xml, mime_application_vnd_3gpp_mcdata_signalling,
    mime_application_vnd_3gpp_mcdata_ue_config_xml, mime_application_vnd_3gpp_mcdata_user_profile_xml, mime_application_vnd_3gpp_mcptt_affiliation_command_xml,
    mime_application_vnd_3gpp_mcptt_floor_request_xml, mime_application_vnd_3gpp_mcptt_info_xml, mime_application_vnd_3gpp_mcptt_location_info_xml,
    mime_application_vnd_3gpp_mcptt_mbms_usage_info_xml, mime_application_vnd_3gpp_mcptt_service_config_xml, mime_application_vnd_3gpp_mcptt_signed_xml,
    mime_application_vnd_3gpp_mcptt_ue_config_xml, mime_application_vnd_3gpp_mcptt_ue_init_config_xml, mime_application_vnd_3gpp_mcptt_user_profile_xml,
    mime_application_vnd_3gpp_mcvideo_affiliation_command_xml, mime_application_vnd_3gpp_mcvideo_affiliation_info_xml, mime_application_vnd_3gpp_mcvideo_info_xml,
    mime_application_vnd_3gpp_mcvideo_location_info_xml, mime_application_vnd_3gpp_mcvideo_mbms_usage_info_xml, mime_application_vnd_3gpp_mcvideo_service_config_xml,
    mime_application_vnd_3gpp_mcvideo_transmission_request_xml, mime_application_vnd_3gpp_mcvideo_ue_config_xml, mime_application_vnd_3gpp_mcvideo_user_profile_xml,
    mime_application_vnd_3gpp_mid_call_xml, mime_application_vnd_3gpp_pic_bw_large, mime_application_vnd_3gpp_pic_bw_small, mime_application_vnd_3gpp_pic_bw_var,
    mime_application_vnd_3gpp_prose_pc3ch_xml, mime_application_vnd_3gpp_prose_xml, mime_application_vnd_3gpp_sms, mime_application_vnd_3gpp_sms_xml, mime_application_vnd_3gpp_srvcc_ext_xml,
    mime_application_vnd_3gpp_SRVCC_info_xml, mime_application_vnd_3gpp_state_and_event_info_xml, mime_application_vnd_3gpp_ussd_xml, mime_application_vnd_3gpp_v2x_local_service_information,
    mime_application_vnd_3gpp2_bcmcsinfo_xml, mime_application_vnd_3gpp2_sms, mime_application_vnd_3gpp2_tcap, mime_application_vnd_3lightssoftware_imagescal,
    mime_application_vnd_3M_Post_it_Notes, mime_application_vnd_accpac_simply_aso, mime_application_vnd_accpac_simply_imp, mime_application_vnd_acucobol, mime_application_vnd_acucorp,
    mime_application_vnd_adobe_flash_movie, mime_application_vnd_adobe_formscentral_fcdt, mime_application_vnd_adobe_fxp, mime_application_vnd_adobe_partial_upload,
    mime_application_vnd_adobe_xdp_xml, mime_application_vnd_adobe_xfdf, mime_application_vnd_aether_imp, mime_application_vnd_afpc_afplinedata, mime_application_vnd_afpc_afplinedata_pagedef,
    mime_application_vnd_afpc_foca_charset, mime_application_vnd_afpc_foca_codedfont, mime_application_vnd_afpc_foca_codepage, mime_application_vnd_afpc_modca,
    mime_application_vnd_afpc_modca_formdef, mime_application_vnd_afpc_modca_mediummap, mime_application_vnd_afpc_modca_objectcontainer, mime_application_vnd_afpc_modca_overlay,
    mime_application_vnd_afpc_modca_pagesegment, mime_application_vnd_ah_barcode, mime_application_vnd_ahead_space, mime_application_vnd_airzip_filesecure_azf,
    mime_application_vnd_airzip_filesecure_azs, mime_application_vnd_amadeus_json, mime_application_vnd_amazon_mobi8_ebook, mime_application_vnd_americandynamics_acc,
    mime_application_vnd_amiga_ami, mime_application_vnd_amundsen_maze_xml, mime_application_vnd_android_ota, mime_application_vnd_anki,
    mime_application_vnd_anser_web_certificate_issue_initiation, mime_application_vnd_antix_game_component, mime_application_vnd_apache_thrift_binary,
    mime_application_vnd_apache_thrift_compact, mime_application_vnd_apache_thrift_json, mime_application_vnd_api_json, mime_application_vnd_aplextor_warrp_json,
    mime_application_vnd_apothekende_reservation_json, mime_application_vnd_apple_installer_xml, mime_application_vnd_apple_keynote, mime_application_vnd_apple_mpegurl,
    mime_application_vnd_apple_numbers, mime_application_vnd_apple_pages, mime_application_vnd_arastra_swi, mime_application_vnd_aristanetworks_swi, mime_application_vnd_artisan_json,
    mime_application_vnd_artsquare, mime_application_vnd_astraea_software_iota, mime_application_vnd_audiograph, mime_application_vnd_autopackage, mime_application_vnd_avalon_json,
    mime_application_vnd_avistar_xml, mime_application_vnd_balsamiq_bmml_xml, mime_application_vnd_banana_accounting, mime_application_vnd_bbf_usp_error, mime_application_vnd_bbf_usp_msg,
    mime_application_vnd_bbf_usp_msg_json, mime_application_vnd_balsamiq_bmpr, mime_application_vnd_bekitzur_stech_json, mime_application_vnd_bint_med_content,
    mime_application_vnd_biopax_rdf_xml, mime_application_vnd_blink_idb_value_wrapper, mime_application_vnd_blueice_multipass, mime_application_vnd_bluetooth_ep_oob,
    mime_application_vnd_bluetooth_le_oob, mime_application_vnd_bmi, mime_application_vnd_bpf, mime_application_vnd_bpf3, mime_application_vnd_businessobjects,
    mime_application_vnd_byu_uapi_json, mime_application_vnd_cab_jscript, mime_application_vnd_canon_cpdl, mime_application_vnd_canon_lips, mime_application_vnd_capasystems_pg_json,
    mime_application_vnd_cendio_thinlinc_clientconf, mime_application_vnd_century_systems_tcp_stream, mime_application_vnd_chemdraw_xml, mime_application_vnd_chess_pgn,
    mime_application_vnd_chipnuts_karaoke_mmd, mime_application_vnd_ciedi, mime_application_vnd_cinderella, mime_application_vnd_cirpack_isdn_ext,
    mime_application_vnd_citationstyles_style_xml, mime_application_vnd_claymore, mime_application_vnd_cloanto_rp9, mime_application_vnd_clonk_c4group,
    mime_application_vnd_cluetrust_cartomobile_config, mime_application_vnd_cluetrust_cartomobile_config_pkg, mime_application_vnd_coffeescript,
    mime_application_vnd_collabio_xodocuments_document, mime_application_vnd_collabio_xodocuments_document_template, mime_application_vnd_collabio_xodocuments_presentation,
    mime_application_vnd_collabio_xodocuments_presentation_template, mime_application_vnd_collabio_xodocuments_spreadsheet, mime_application_vnd_collabio_xodocuments_spreadsheet_template,
    mime_application_vnd_collection_doc_json, mime_application_vnd_collection_json, mime_application_vnd_collection_next_json, mime_application_vnd_comicbook_rar,
    mime_application_vnd_comicbook_zip, mime_application_vnd_commerce_battelle, mime_application_vnd_commonspace, mime_application_vnd_coreos_ignition_json,
    mime_application_vnd_cosmocaller, mime_application_vnd_contact_cmsg, mime_application_vnd_crick_clicker, mime_application_vnd_crick_clicker_keyboard,
    mime_application_vnd_crick_clicker_palette, mime_application_vnd_crick_clicker_template, mime_application_vnd_crick_clicker_wordbank, mime_application_vnd_criticaltools_wbs_xml,
    mime_application_vnd_cryptii_pipe_json, mime_application_vnd_crypto_shade_file, mime_application_vnd_ctc_posml, mime_application_vnd_ctct_ws_xml, mime_application_vnd_cups_pdf,
    mime_application_vnd_cups_postscript, mime_application_vnd_cups_ppd, mime_application_vnd_cups_raster, mime_application_vnd_cups_raw, mime_application_vnd_curl,
    mime_application_vnd_cyan_dean_root_xml, mime_application_vnd_cybank, mime_application_vnd_d2l_coursepackage1p0_zip, mime_application_vnd_dart, mime_application_vnd_data_vision_rdz,
    mime_application_vnd_datapackage_json, mime_application_vnd_dataresource_json, mime_application_vnd_dbf, mime_application_vnd_debian_binary_package, mime_application_vnd_dece_data,
    mime_application_vnd_dece_ttml_xml, mime_application_vnd_dece_unspecified, mime_application_vnd_dece_zip, mime_application_vnd_denovo_fcselayout_link,
    mime_application_vnd_desmume_movie, mime_application_vnd_dir_bi_plate_dl_nosuffix, mime_application_vnd_dm_delegation_xml, mime_application_vnd_dna,
    mime_application_vnd_document_json, mime_application_vnd_dolby_mobile_1, mime_application_vnd_dolby_mobile_2, mime_application_vnd_doremir_scorecloud_binary_document,
    mime_application_vnd_dpgraph, mime_application_vnd_dreamfactory, mime_application_vnd_drive_json, mime_application_vnd_dtg_local, mime_application_vnd_dtg_local_flash,
    mime_application_vnd_dtg_local_html, mime_application_vnd_dvb_ait, mime_application_vnd_dvb_dvbisl_xml, mime_application_vnd_dvb_dvbj, mime_application_vnd_dvb_esgcontainer,
    mime_application_vnd_dvb_ipdcdftnotifaccess, mime_application_vnd_dvb_ipdcesgaccess, mime_application_vnd_dvb_ipdcesgaccess2, mime_application_vnd_dvb_ipdcesgpdd,
    mime_application_vnd_dvb_ipdcroaming, mime_application_vnd_dvb_iptv_alfec_base, mime_application_vnd_dvb_iptv_alfec_enhancement, mime_application_vnd_dvb_notif_aggregate_root_xml,
    mime_application_vnd_dvb_notif_container_xml, mime_application_vnd_dvb_notif_generic_xml, mime_application_vnd_dvb_notif_ia_msglist_xml,
    mime_application_vnd_dvb_notif_ia_registration_request_xml, mime_application_vnd_dvb_notif_ia_registration_response_xml, mime_application_vnd_dvb_notif_init_xml,
    mime_application_vnd_dvb_pfr, mime_application_vnd_dvb_service, mime_application_vnd_dxr, mime_application_vnd_dynageo, mime_application_vnd_dzr,
    mime_application_vnd_easykaraoke_cdgdownload, mime_application_vnd_ecip_rlp, mime_application_vnd_ecdis_update, mime_application_vnd_ecowin_chart,
    mime_application_vnd_ecowin_filerequest, mime_application_vnd_ecowin_fileupdate, mime_application_vnd_ecowin_series, mime_application_vnd_ecowin_seriesrequest,
    mime_application_vnd_ecowin_seriesupdate, mime_application_vnd_efi_img, mime_application_vnd_efi_iso, mime_application_vnd_emclient_accessrequest_xml,
    mime_application_vnd_enliven, mime_application_vnd_enphase_envoy, mime_application_vnd_eprints_data_xml, mime_application_vnd_epson_esf,
    mime_application_vnd_epson_msf, mime_application_vnd_epson_quickanime, mime_application_vnd_epson_salt, mime_application_vnd_epson_ssf,
    mime_application_vnd_ericsson_quickcall, mime_application_vnd_espass_espass_zip, mime_application_vnd_eszigno3_xml, mime_application_vnd_etsi_aoc_xml,
    mime_application_vnd_etsi_asic_s_zip, mime_application_vnd_etsi_asic_e_zip, mime_application_vnd_etsi_cug_xml, mime_application_vnd_etsi_iptvcommand_xml,
    mime_application_vnd_etsi_iptvdiscovery_xml, mime_application_vnd_etsi_iptvprofile_xml, mime_application_vnd_etsi_iptvsad_bc_xml,
    mime_application_vnd_etsi_iptvsad_cod_xml, mime_application_vnd_etsi_iptvsad_npvr_xml, mime_application_vnd_etsi_iptvservice_xml,
    mime_application_vnd_etsi_iptvsync_xml, mime_application_vnd_etsi_iptvueprofile_xml, mime_application_vnd_etsi_mcid_xml, mime_application_vnd_etsi_mheg5,
    mime_application_vnd_etsi_overload_control_policy_dataset_xml, mime_application_vnd_etsi_pstn_xml, mime_application_vnd_etsi_sci_xml,
    mime_application_vnd_etsi_simservs_xml, mime_application_vnd_etsi_timestamp_token, mime_application_vnd_etsi_tsl_xml, mime_application_vnd_etsi_tsl_der,
    mime_application_vnd_evolv_ecig_profile, mime_application_vnd_evolv_ecig_settings, mime_application_vnd_evolv_ecig_theme, mime_application_vnd_eudora_data,
    mime_application_vnd_exstream_empower_zip, mime_application_vnd_exstream_package, mime_application_vnd_ezpix_album, mime_application_vnd_ezpix_package,
    mime_application_vnd_f_secure_mobile, mime_application_vnd_fastcopy_disk_image, mime_application_vnd_fdf, mime_application_vnd_fdsn_mseed,
    mime_application_vnd_fdsn_seed, mime_application_vnd_ffsns, mime_application_vnd_ficlab_flb_zip, mime_application_vnd_filmit_zfc, mime_application_vnd_fints,
    mime_application_vnd_firemonkeys_cloudcell, mime_application_vnd_FloGraphIt, mime_application_vnd_fluxtime_clip, mime_application_vnd_font_fontforge_sfd,
    mime_application_vnd_framemaker, mime_application_vnd_frogans_fnc, mime_application_vnd_frogans_ltf, mime_application_vnd_fsc_weblaunch,
    mime_application_vnd_fujitsu_oasys, mime_application_vnd_fujitsu_oasys2, mime_application_vnd_fujitsu_oasys3, mime_application_vnd_fujitsu_oasysgp,
    mime_application_vnd_fujitsu_oasysprs, mime_application_vnd_fujixerox_ART4, mime_application_vnd_fujixerox_ART_EX, mime_application_vnd_fujixerox_ddd,
    mime_application_vnd_fujixerox_docuworks, mime_application_vnd_fujixerox_docuworks_binder, mime_application_vnd_fujixerox_docuworks_container,
    mime_application_vnd_fujixerox_HBPL, mime_application_vnd_fut_misnet, mime_application_vnd_futoin_cbor, mime_application_vnd_futoin_json,
    mime_application_vnd_fuzzysheet, mime_application_vnd_genomatix_tuxedo, mime_application_vnd_gentics_grd_json, mime_application_vnd_geo_json,
    mime_application_vnd_geocube_xml, mime_application_vnd_geogebra_file, mime_application_vnd_geogebra_tool, mime_application_vnd_geometry_explorer,
    mime_application_vnd_geonext, mime_application_vnd_geoplan, mime_application_vnd_geospace, mime_application_vnd_gerber,
    mime_application_vnd_globalplatform_card_content_mgt, mime_application_vnd_globalplatform_card_content_mgt_response, mime_application_vnd_gmx,
    mime_application_vnd_google_earth_kml_xml, mime_application_vnd_google_earth_kmz, mime_application_vnd_gov_sk_e_form_xml,
    mime_application_vnd_gov_sk_e_form_zip, mime_application_vnd_gov_sk_xmldatacontainer_xml, mime_application_vnd_grafeq,
    mime_application_vnd_gridmp, mime_application_vnd_groove_account, mime_application_vnd_groove_help, mime_application_vnd_groove_identity_message,
    mime_application_vnd_groove_injector, mime_application_vnd_groove_tool_message, mime_application_vnd_groove_tool_template, mime_application_vnd_groove_vcard,
    mime_application_vnd_hal_json, mime_application_vnd_hal_xml, mime_application_vnd_HandHeld_Entertainment_xml, mime_application_vnd_hbci,
    mime_application_vnd_hc_json, mime_application_vnd_hcl_bireports, mime_application_vnd_hdt, mime_application_vnd_heroku_json,
    mime_application_vnd_hhe_lesson_player, mime_application_vnd_hp_HPGL, mime_application_vnd_hp_hpid, mime_application_vnd_hp_hps, mime_application_vnd_hp_jlyt,
    mime_application_vnd_hp_PCL, mime_application_vnd_hp_PCLXL, mime_application_vnd_httphone, mime_application_vnd_hydrostatix_sof_data,
    mime_application_vnd_hyper_item_json, mime_application_vnd_hyper_json, mime_application_vnd_hyperdrive_json, mime_application_vnd_hzn_3d_crossword,
    mime_application_vnd_ibm_afplinedata, mime_application_vnd_ibm_electronic_media, mime_application_vnd_ibm_MiniPay, mime_application_vnd_ibm_modcap,
    mime_application_vnd_ibm_rights_management, mime_application_vnd_ibm_secure_container, mime_application_vnd_iccprofile, mime_application_vnd_ieee_1905,
    mime_application_vnd_igloader, mime_application_vnd_imagemeter_folder_zip, mime_application_vnd_imagemeter_image_zip, mime_application_vnd_immervision_ivp,
    mime_application_vnd_immervision_ivu, mime_application_vnd_ims_imsccv1p1, mime_application_vnd_ims_imsccv1p2, mime_application_vnd_ims_imsccv1p3,
    mime_application_vnd_ims_lis_v2_result_json, mime_application_vnd_ims_lti_v2_toolconsumerprofile_json, mime_application_vnd_ims_lti_v2_toolproxy_id_json,
    mime_application_vnd_ims_lti_v2_toolproxy_json, mime_application_vnd_ims_lti_v2_toolsettings_json, mime_application_vnd_ims_lti_v2_toolsettings_simple_json,
    mime_application_vnd_informedcontrol_rms_xml, mime_application_vnd_infotech_project, mime_application_vnd_infotech_project_xml,
    mime_application_vnd_informix_visionary, mime_application_vnd_innopath_wamp_notification, mime_application_vnd_insors_igm,
    mime_application_vnd_intercon_formnet, mime_application_vnd_intergeo, mime_application_vnd_intertrust_digibox, mime_application_vnd_intertrust_nncp,
    mime_application_vnd_intu_qbo, mime_application_vnd_intu_qfx, mime_application_vnd_iptc_g2_catalogitem_xml, mime_application_vnd_iptc_g2_conceptitem_xml,
    mime_application_vnd_iptc_g2_knowledgeitem_xml, mime_application_vnd_iptc_g2_newsitem_xml, mime_application_vnd_iptc_g2_newsmessage_xml,
    mime_application_vnd_iptc_g2_packageitem_xml, mime_application_vnd_iptc_g2_planningitem_xml, mime_application_vnd_ipunplugged_rcprofile,
    mime_application_vnd_irepository_package_xml, mime_application_vnd_is_xpr, mime_application_vnd_isac_fcs, mime_application_vnd_jam,
    mime_application_vnd_iso11783_10_zip, mime_application_vnd_japannet_directory_service, mime_application_vnd_japannet_jpnstore_wakeup,
    mime_application_vnd_japannet_payment_wakeup, mime_application_vnd_japannet_registration, mime_application_vnd_japannet_registration_wakeup,
    mime_application_vnd_japannet_setstore_wakeup, mime_application_vnd_japannet_verification, mime_application_vnd_japannet_verification_wakeup,
    mime_application_vnd_jcp_javame_midlet_rms, mime_application_vnd_jisp, mime_application_vnd_joost_joda_archive, mime_application_vnd_jsk_isdn_ngn,
    mime_application_vnd_kahootz, mime_application_vnd_kde_karbon, mime_application_vnd_kde_kchart, mime_application_vnd_kde_kformula,
    mime_application_vnd_kde_kivio, mime_application_vnd_kde_kontour, mime_application_vnd_kde_kpresenter, mime_application_vnd_kde_kspread,
    mime_application_vnd_kde_kword, mime_application_vnd_kenameaapp, mime_application_vnd_kidspiration, mime_application_vnd_Kinar,
    mime_application_vnd_koan, mime_application_vnd_kodak_descriptor, mime_application_vnd_las, mime_application_vnd_las_las_json,
    mime_application_vnd_las_las_xml, mime_application_vnd_laszip, mime_application_vnd_leap_json, mime_application_vnd_liberty_request_xml,
    mime_application_vnd_llamagraphics_life_balance_desktop, mime_application_vnd_llamagraphics_life_balance_exchange_xml,
    mime_application_vnd_logipipe_circuit_zip, mime_application_vnd_loom, mime_application_vnd_lotus_1_2_3, mime_application_vnd_lotus_approach,
    mime_application_vnd_lotus_freelance, mime_application_vnd_lotus_notes, mime_application_vnd_lotus_organiser, mime_application_vnd_lotus_screencam,
    mime_application_vnd_lotus_wordpro, mime_application_vnd_macports_portpkg, mime_application_vnd_mapbox_vector_tile,
    mime_application_vnd_marlin_drm_actiontoken_xml, mime_application_vnd_marlin_drm_conftoken_xml, mime_application_vnd_marlin_drm_license_xml,
    mime_application_vnd_marlin_drm_mdcf, mime_application_vnd_mason_json, mime_application_vnd_maxmind_maxmind_db, mime_application_vnd_mcd,
    mime_application_vnd_medcalcdata, mime_application_vnd_mediastation_cdkey, mime_application_vnd_meridian_slingshot, mime_application_vnd_MFER,
    mime_application_vnd_mfmp, mime_application_vnd_micro_json, mime_application_vnd_micrografx_flo, mime_application_vnd_micrografx_igx,
    mime_application_vnd_microsoft_portable_executable, mime_application_vnd_microsoft_windows_thumbnail_cache, mime_application_vnd_miele_json,
    mime_application_vnd_mif, mime_application_vnd_minisoft_hp3000_save, mime_application_vnd_mitsubishi_misty_guard_trustweb,
    mime_application_vnd_Mobius_DAF, mime_application_vnd_Mobius_DIS, mime_application_vnd_Mobius_MBK, mime_application_vnd_Mobius_MQY,
    mime_application_vnd_Mobius_MSL, mime_application_vnd_Mobius_PLC, mime_application_vnd_Mobius_TXF, mime_application_vnd_mophun_application,
    mime_application_vnd_mophun_certificate, mime_application_vnd_motorola_flexsuite, mime_application_vnd_motorola_flexsuite_adsi,
    mime_application_vnd_motorola_flexsuite_fis, mime_application_vnd_motorola_flexsuite_gotap, mime_application_vnd_motorola_flexsuite_kmr,
    mime_application_vnd_motorola_flexsuite_ttc, mime_application_vnd_motorola_flexsuite_wem, mime_application_vnd_motorola_iprm,
    mime_application_vnd_mozilla_xul_xml, mime_application_vnd_ms_artgalry, mime_application_vnd_ms_asf, mime_application_vnd_ms_cab_compressed,
    mime_application_vnd_ms_3mfdocument, mime_application_vnd_ms_excel, mime_application_vnd_ms_excel_addin_macroEnabled_12,
    mime_application_vnd_ms_excel_sheet_binary_macroEnabled_12, mime_application_vnd_ms_excel_sheet_macroEnabled_12,
    mime_application_vnd_ms_excel_template_macroEnabled_12, mime_application_vnd_ms_fontobject, mime_application_vnd_ms_htmlhelp,
    mime_application_vnd_ms_ims, mime_application_vnd_ms_lrm, mime_application_vnd_ms_office_activeX_xml, mime_application_vnd_ms_officetheme,
    mime_application_vnd_ms_playready_initiator_xml, mime_application_vnd_ms_powerpoint, mime_application_vnd_ms_powerpoint_addin_macroEnabled_12,
    mime_application_vnd_ms_powerpoint_presentation_macroEnabled_12, mime_application_vnd_ms_powerpoint_slide_macroEnabled_12,
    mime_application_vnd_ms_powerpoint_slideshow_macroEnabled_12, mime_application_vnd_ms_powerpoint_template_macroEnabled_12,
    mime_application_vnd_ms_PrintDeviceCapabilities_xml, mime_application_vnd_ms_PrintSchemaTicket_xml, mime_application_vnd_ms_project,
    mime_application_vnd_ms_tnef, mime_application_vnd_ms_windows_devicepairing, mime_application_vnd_ms_windows_nwprinting_oob,
    mime_application_vnd_ms_windows_printerpairing, mime_application_vnd_ms_windows_wsd_oob, mime_application_vnd_ms_wmdrm_lic_chlg_req,
    mime_application_vnd_ms_wmdrm_lic_resp, mime_application_vnd_ms_wmdrm_meter_chlg_req, mime_application_vnd_ms_wmdrm_meter_resp,
    mime_application_vnd_ms_word_document_macroEnabled_12, mime_application_vnd_ms_word_template_macroEnabled_12,
    mime_application_vnd_ms_works, mime_application_vnd_ms_wpl, mime_application_vnd_ms_xpsdocument, mime_application_vnd_msa_disk_image,
    mime_application_vnd_mseq, mime_application_vnd_msign, mime_application_vnd_multiad_creator, mime_application_vnd_multiad_creator_cif,
    mime_application_vnd_musician, mime_application_vnd_music_niff, mime_application_vnd_muvee_style, mime_application_vnd_mynfc,
    mime_application_vnd_ncd_control, mime_application_vnd_ncd_reference, mime_application_vnd_nearst_inv_json, mime_application_vnd_nervana,
    mime_application_vnd_netfpx, mime_application_vnd_neurolanguage_nlu, mime_application_vnd_nimn, mime_application_vnd_nintendo_snes_rom,
    mime_application_vnd_nintendo_nitro_rom, mime_application_vnd_nitf, mime_application_vnd_noblenet_directory, mime_application_vnd_noblenet_sealer,
    mime_application_vnd_noblenet_web, mime_application_vnd_nokia_catalogs, mime_application_vnd_nokia_conml_wbxml,
    mime_application_vnd_nokia_conml_xml, mime_application_vnd_nokia_iptv_config_xml, mime_application_vnd_nokia_iSDS_radio_presets,
    mime_application_vnd_nokia_landmark_wbxml, mime_application_vnd_nokia_landmark_xml, mime_application_vnd_nokia_landmarkcollection_xml,
    mime_application_vnd_nokia_ncd, mime_application_vnd_nokia_n_gage_ac_xml, mime_application_vnd_nokia_n_gage_data,
    mime_application_vnd_nokia_n_gage_symbian_install, mime_application_vnd_nokia_pcd_wbxml, mime_application_vnd_nokia_pcd_xml,
    mime_application_vnd_nokia_radio_preset, mime_application_vnd_nokia_radio_presets, mime_application_vnd_novadigm_EDM,
    mime_application_vnd_novadigm_EDX, mime_application_vnd_novadigm_EXT, mime_application_vnd_ntt_local_content_share,
    mime_application_vnd_ntt_local_file_transfer, mime_application_vnd_ntt_local_ogw_remote_access, mime_application_vnd_ntt_local_sip_ta_remote,
    mime_application_vnd_ntt_local_sip_ta_tcp_stream, mime_application_vnd_oasis_opendocument_chart,
    mime_application_vnd_oasis_opendocument_chart_template, mime_application_vnd_oasis_opendocument_database,
    mime_application_vnd_oasis_opendocument_formula, mime_application_vnd_oasis_opendocument_formula_template,
    mime_application_vnd_oasis_opendocument_graphics, mime_application_vnd_oasis_opendocument_graphics_template,
    mime_application_vnd_oasis_opendocument_image, mime_application_vnd_oasis_opendocument_image_template,
    mime_application_vnd_oasis_opendocument_presentation, mime_application_vnd_oasis_opendocument_presentation_template,
    mime_application_vnd_oasis_opendocument_spreadsheet, mime_application_vnd_oasis_opendocument_spreadsheet_template,
    mime_application_vnd_oasis_opendocument_text, mime_application_vnd_oasis_opendocument_text_master,
    mime_application_vnd_oasis_opendocument_text_template, mime_application_vnd_oasis_opendocument_text_web,
    mime_application_vnd_obn, mime_application_vnd_ocf_cbor, mime_application_vnd_oci_image_manifest_v1_json, mime_application_vnd_oftn_l10n_json,
    mime_application_vnd_oipf_contentaccessdownload_xml, mime_application_vnd_oipf_contentaccessstreaming_xml,
    mime_application_vnd_oipf_cspg_hexbinary, mime_application_vnd_oipf_dae_svg_xml, mime_application_vnd_oipf_dae_xhtml_xml,
    mime_application_vnd_oipf_mippvcontrolmessage_xml, mime_application_vnd_oipf_pae_gem, mime_application_vnd_oipf_spdiscovery_xml,
    mime_application_vnd_oipf_spdlist_xml, mime_application_vnd_oipf_ueprofile_xml, mime_application_vnd_oipf_userprofile_xml,
    mime_application_vnd_olpc_sugar, mime_application_vnd_oma_bcast_associated_procedure_parameter_xml, mime_application_vnd_oma_bcast_drm_trigger_xml,
    mime_application_vnd_oma_bcast_imd_xml, mime_application_vnd_oma_bcast_ltkm, mime_application_vnd_oma_bcast_notification_xml,
    mime_application_vnd_oma_bcast_provisioningtrigger, mime_application_vnd_oma_bcast_sgboot, mime_application_vnd_oma_bcast_sgdd_xml,
    mime_application_vnd_oma_bcast_sgdu, mime_application_vnd_oma_bcast_simple_symbol_container, mime_application_vnd_oma_bcast_smartcard_trigger_xml,
    mime_application_vnd_oma_bcast_sprov_xml, mime_application_vnd_oma_bcast_stkm, mime_application_vnd_oma_cab_address_book_xml,
    mime_application_vnd_oma_cab_feature_handler_xml, mime_application_vnd_oma_cab_pcc_xml, mime_application_vnd_oma_cab_subs_invite_xml,
    mime_application_vnd_oma_cab_user_prefs_xml, mime_application_vnd_oma_dcd, mime_application_vnd_oma_dcdc, mime_application_vnd_oma_dd2_xml,
    mime_application_vnd_oma_drm_risd_xml, mime_application_vnd_oma_group_usage_list_xml, mime_application_vnd_oma_lwm2m_json,
    mime_application_vnd_oma_lwm2m_tlv, mime_application_vnd_oma_pal_xml, mime_application_vnd_oma_poc_detailed_progress_report_xml,
    mime_application_vnd_oma_poc_final_report_xml, mime_application_vnd_oma_poc_groups_xml, mime_application_vnd_oma_poc_invocation_descriptor_xml,
    mime_application_vnd_oma_poc_optimized_progress_report_xml, mime_application_vnd_oma_push, mime_application_vnd_oma_scidm_messages_xml,
    mime_application_vnd_oma_xcap_directory_xml, mime_application_vnd_omads_email_xml, mime_application_vnd_omads_file_xml,
    mime_application_vnd_omads_folder_xml, mime_application_vnd_omaloc_supl_init, mime_application_vnd_oma_scws_config,
    mime_application_vnd_oma_scws_http_request, mime_application_vnd_oma_scws_http_response, mime_application_vnd_onepager,
    mime_application_vnd_onepagertamp, mime_application_vnd_onepagertamx, mime_application_vnd_onepagertat, mime_application_vnd_onepagertatp,
    mime_application_vnd_onepagertatx, mime_application_vnd_openblox_game_binary, mime_application_vnd_openblox_game_xml,
    mime_application_vnd_openeye_oeb, mime_application_vnd_openstreetmap_data_xml,
    mime_application_vnd_openxmlformats_officedocument_custom_properties_xml,
    mime_application_vnd_openxmlformats_officedocument_customXmlProperties_xml,
    mime_application_vnd_openxmlformats_officedocument_drawing_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_chart_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_chartshapes_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_diagramColors_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_diagramData_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_diagramLayout_xml,
    mime_application_vnd_openxmlformats_officedocument_drawingml_diagramStyle_xml,
    mime_application_vnd_openxmlformats_officedocument_extended_properties_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_commentAuthors_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_comments_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_handoutMaster_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_notesMaster_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_notesSlide_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_presentation,
    mime_application_vnd_openxmlformats_officedocument_presentationml_presentation_main_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_presProps_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slide,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slide_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slideLayout_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slideMaster_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slideshow,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slideshow_main_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_slideUpdateInfo_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_tableStyles_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_tags_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_template,
    mime_application_vnd_openxmlformats_officedocument_presentationml_template_main_xml,
    mime_application_vnd_openxmlformats_officedocument_presentationml_viewProps_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_calcChain_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_chartsheet_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_comments_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_connections_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_dialogsheet_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_externalLink_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_pivotCacheDefinition_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_pivotCacheRecords_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_pivotTable_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_queryTable_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_revisionHeaders_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_revisionLog_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_sharedStrings_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_sheet,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_sheet_main_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_sheetMetadata_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_styles_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_table_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_tableSingleCells_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_template,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_template_main_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_userNames_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_volatileDependencies_xml,
    mime_application_vnd_openxmlformats_officedocument_spreadsheetml_worksheet_xml,
    mime_application_vnd_openxmlformats_officedocument_theme_xml,
    mime_application_vnd_openxmlformats_officedocument_themeOverride_xml,
    mime_application_vnd_openxmlformats_officedocument_vmlDrawing,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_comments_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_document,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_document_glossary_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_document_main_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_endnotes_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_fontTable_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_footer_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_footnotes_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_numbering_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_settings_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_styles_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_template,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_template_main_xml,
    mime_application_vnd_openxmlformats_officedocument_wordprocessingml_webSettings_xml,
    mime_application_vnd_openxmlformats_package_core_properties_xml,
    mime_application_vnd_openxmlformats_package_digital_signature_xmlsignature_xml,
    mime_application_vnd_openxmlformats_package_relationships_xml,
    mime_application_vnd_oracle_resource_json, mime_application_vnd_orange_indata, mime_application_vnd_osa_netdeploy,
    mime_application_vnd_osgeo_mapguide_package, mime_application_vnd_osgi_bundle, mime_application_vnd_osgi_dp,
    mime_application_vnd_osgi_subsystem, mime_application_vnd_otps_ct_kip_xml, mime_application_vnd_oxli_countgraph,
    mime_application_vnd_pagerduty_json, mime_application_vnd_palm, mime_application_vnd_panoply, mime_application_vnd_paos_xml,
    mime_application_vnd_patentdive, mime_application_vnd_patientecommsdoc, mime_application_vnd_pawaafile, mime_application_vnd_pcos,
    mime_application_vnd_pg_format, mime_application_vnd_pg_osasli, mime_application_vnd_piaccess_application_licence,
    mime_application_vnd_picsel, mime_application_vnd_pmi_widget, mime_application_vnd_poc_group_advertisement_xml,
    mime_application_vnd_pocketlearn, mime_application_vnd_powerbuilder6, mime_application_vnd_powerbuilder6_s,
    mime_application_vnd_powerbuilder7, mime_application_vnd_powerbuilder75, mime_application_vnd_powerbuilder75_s,
    mime_application_vnd_powerbuilder7_s, mime_application_vnd_preminet, mime_application_vnd_previewsystems_box,
    mime_application_vnd_proteus_magazine, mime_application_vnd_psfs, mime_application_vnd_publishare_delta_tree,
    mime_application_vnd_pvi_ptid1, mime_application_vnd_pwg_multiplexed, mime_application_vnd_pwg_xhtml_print_xml,
    mime_application_vnd_qualcomm_brew_app_res, mime_application_vnd_quarantainenet, mime_application_vnd_Quark_QuarkXPress,
    mime_application_vnd_quobject_quoxdocument, mime_application_vnd_radisys_moml_xml, mime_application_vnd_radisys_msml_audit_conf_xml,
    mime_application_vnd_radisys_msml_audit_conn_xml, mime_application_vnd_radisys_msml_audit_dialog_xml,
    mime_application_vnd_radisys_msml_audit_stream_xml, mime_application_vnd_radisys_msml_audit_xml,
    mime_application_vnd_radisys_msml_conf_xml, mime_application_vnd_radisys_msml_dialog_base_xml,
    mime_application_vnd_radisys_msml_dialog_fax_detect_xml, mime_application_vnd_radisys_msml_dialog_fax_sendrecv_xml,
    mime_application_vnd_radisys_msml_dialog_group_xml, mime_application_vnd_radisys_msml_dialog_speech_xml,
    mime_application_vnd_radisys_msml_dialog_transform_xml, mime_application_vnd_radisys_msml_dialog_xml,
    mime_application_vnd_radisys_msml_xml, mime_application_vnd_rainstor_data, mime_application_vnd_rapid, mime_application_vnd_rar,
    mime_application_vnd_realvnc_bed, mime_application_vnd_recordare_musicxml, mime_application_vnd_recordare_musicxml_xml,
    mime_application_vnd_RenLearn_rlprint, mime_application_vnd_restful_json, mime_application_vnd_rig_cryptonote,
    mime_application_vnd_route66_link66_xml, mime_application_vnd_rs_274x, mime_application_vnd_ruckus_download,
    mime_application_vnd_s3sms, mime_application_vnd_sailingtracker_track, mime_application_vnd_sar, mime_application_vnd_sbm_cid,
    mime_application_vnd_sbm_mid2, mime_application_vnd_scribus, mime_application_vnd_sealed_3df, mime_application_vnd_sealed_csf,
    mime_application_vnd_sealed_doc, mime_application_vnd_sealed_eml, mime_application_vnd_sealed_mht, mime_application_vnd_sealed_net,
    mime_application_vnd_sealed_ppt, mime_application_vnd_sealed_tiff, mime_application_vnd_sealed_xls,
    mime_application_vnd_sealedmedia_softseal_html, mime_application_vnd_sealedmedia_softseal_pdf, mime_application_vnd_seemail,
    mime_application_vnd_sema, mime_application_vnd_semd, mime_application_vnd_semf, mime_application_vnd_shade_save_file,
    mime_application_vnd_shana_informed_formdata, mime_application_vnd_shana_informed_formtemplate,
    mime_application_vnd_shana_informed_interchange, mime_application_vnd_shana_informed_package, mime_application_vnd_shootproof_json,
    mime_application_vnd_shopkick_json, mime_application_vnd_shp, mime_application_vnd_shx, mime_application_vnd_sigrok_session,
    mime_application_vnd_SimTech_MindMapper, mime_application_vnd_siren_json, mime_application_vnd_smaf,
    mime_application_vnd_smart_notebook, mime_application_vnd_smart_teacher, mime_application_vnd_snesdev_page_table,
    mime_application_vnd_software602_filler_form_xml, mime_application_vnd_software602_filler_form_xml_zip,
    mime_application_vnd_solent_sdkm_xml, mime_application_vnd_spotfire_dxp, mime_application_vnd_spotfire_sfs,
    mime_application_vnd_sqlite3, mime_application_vnd_sss_cod, mime_application_vnd_sss_dtf, mime_application_vnd_sss_ntf,
    mime_application_vnd_stepmania_package, mime_application_vnd_stepmania_stepchart, mime_application_vnd_street_stream,
    mime_application_vnd_sun_wadl_xml, mime_application_vnd_sus_calendar, mime_application_vnd_svd,
    mime_application_vnd_swiftview_ics, mime_application_vnd_syncml_dm_notification, mime_application_vnd_syncml_dmddf_xml,
    mime_application_vnd_syncml_dmtnds_wbxml, mime_application_vnd_syncml_dmtnds_xml, mime_application_vnd_syncml_dmddf_wbxml,
    mime_application_vnd_syncml_dm_wbxml, mime_application_vnd_syncml_dm_xml, mime_application_vnd_syncml_ds_notification,
    mime_application_vnd_syncml_xml, mime_application_vnd_tableschema_json, mime_application_vnd_tao_intent_module_archive,
    mime_application_vnd_tcpdump_pcap, mime_application_vnd_think_cell_ppttc_json, mime_application_vnd_tml,
    mime_application_vnd_tmd_mediaflex_api_xml, mime_application_vnd_tmobile_livetv, mime_application_vnd_tri_onesource,
    mime_application_vnd_trid_tpt, mime_application_vnd_triscape_mxs, mime_application_vnd_trueapp, mime_application_vnd_truedoc,
    mime_application_vnd_ubisoft_webplayer, mime_application_vnd_ufdl, mime_application_vnd_uiq_theme, mime_application_vnd_umajin,
    mime_application_vnd_unity, mime_application_vnd_uoml_xml, mime_application_vnd_uplanet_alert,
    mime_application_vnd_uplanet_alert_wbxml, mime_application_vnd_uplanet_bearer_choice, mime_application_vnd_uplanet_bearer_choice_wbxml,
    mime_application_vnd_uplanet_cacheop, mime_application_vnd_uplanet_cacheop_wbxml, mime_application_vnd_uplanet_channel,
    mime_application_vnd_uplanet_channel_wbxml, mime_application_vnd_uplanet_list, mime_application_vnd_uplanet_listcmd,
    mime_application_vnd_uplanet_listcmd_wbxml, mime_application_vnd_uplanet_list_wbxml, mime_application_vnd_uri_map,
    mime_application_vnd_uplanet_signal, mime_application_vnd_valve_source_material, mime_application_vnd_vcx,
    mime_application_vnd_vd_study, mime_application_vnd_vectorworks, mime_application_vnd_vel_json, mime_application_vnd_verimatrix_vcas,
    mime_application_vnd_veryant_thin, mime_application_vnd_ves_encrypted, mime_application_vnd_vidsoft_vidconference,
    mime_application_vnd_visio, mime_application_vnd_visionary, mime_application_vnd_vividence_scriptfile, mime_application_vnd_vsf,
    mime_application_vnd_wap_sic, mime_application_vnd_wap_slc, mime_application_vnd_wap_wbxml, mime_application_vnd_wap_wmlc,
    mime_application_vnd_wap_wmlscriptc, mime_application_vnd_webturbo, mime_application_vnd_wfa_p2p, mime_application_vnd_wfa_wsc,
    mime_application_vnd_windows_devicepairing, mime_application_vnd_wmc, mime_application_vnd_wmf_bootstrap,
    mime_application_vnd_wolfram_mathematica, mime_application_vnd_wolfram_mathematica_package, mime_application_vnd_wolfram_player,
    mime_application_vnd_wordperfect, mime_application_vnd_wqd, mime_application_vnd_wrq_hp3000_labelled, mime_application_vnd_wt_stf,
    mime_application_vnd_wv_csp_xml, mime_application_vnd_wv_csp_wbxml, mime_application_vnd_wv_ssp_xml, mime_application_vnd_xacml_json,
    mime_application_vnd_xara, mime_application_vnd_xfdl, mime_application_vnd_xfdl_webform, mime_application_vnd_xmi_xml,
    mime_application_vnd_xmpie_cpkg, mime_application_vnd_xmpie_dpkg, mime_application_vnd_xmpie_plan, mime_application_vnd_xmpie_ppkg,
    mime_application_vnd_xmpie_xlim, mime_application_vnd_yamaha_hv_dic, mime_application_vnd_yamaha_hv_script,
    mime_application_vnd_yamaha_hv_voice, mime_application_vnd_yamaha_openscoreformat_osfpvg_xml, mime_application_vnd_yamaha_openscoreformat,
    mime_application_vnd_yamaha_remote_setup, mime_application_vnd_yamaha_smaf_audio, mime_application_vnd_yamaha_smaf_phrase,
    mime_application_vnd_yamaha_through_ngn, mime_application_vnd_yamaha_tunnel_udpencap, mime_application_vnd_yaoweme,
    mime_application_vnd_yellowriver_custom_menu, mime_application_vnd_youtube_yt, mime_application_vnd_zul,
    mime_application_vnd_zzazz_deck_xml, mime_application_voicexml_xml, mime_application_voucher_cms_json, mime_application_vq_rtcpxr,
    mime_application_watcherinfo_xml, mime_application_webpush_options_json, mime_application_whoispp_query,
    mime_application_whoispp_response, mime_application_widget, mime_application_wita, mime_application_wordperfect5_1,
    mime_application_wsdl_xml, mime_application_wspolicy_xml, mime_application_x_ecmascript, mime_application_x_java_applet,
    mime_application_x_javascript,  mime_application_x_pki_message, mime_application_x_shockwave_flash, mime_application_x_webfont,
    mime_application_x_www_form_urlencoded, mime_application_x_x509_ca_cert,
    mime_application_x_x509_ca_ra_cert, mime_application_x_x509_next_ca_cert, mime_application_x400_bp, mime_application_xacml_xml,
    mime_application_xcap_att_xml, mime_application_xcap_caps_xml, mime_application_xcap_diff_xml, mime_application_xcap_el_xml,
    mime_application_xcap_error_xml, mime_application_xcap_ns_xml, mime_application_xcon_conference_info_diff_xml,
    mime_application_xcon_conference_info_xml, mime_application_xenc_xml, mime_application_xhtml_xml, mime_application_xliff_xml,
    mime_application_xml, mime_application_xml_dtd, mime_application_xml_external_parsed_entity, mime_application_xml_patch_xml,
    mime_application_xmpp_xml, mime_application_xop_xml, mime_application_xslt_xml, mime_application_xv_xml, mime_application_yang,
    mime_application_yang_data_json, mime_application_yang_data_xml, mime_application_yang_patch_json, mime_application_yang_patch_xml,
    mime_application_yin_xml, mime_application_zip, mime_application_zlib, mime_application_zstd, mime_audio_1d_interleaved_parityfec,
    mime_audio_32kadpcm, mime_audio_3gpp, mime_audio_3gpp2, mime_audio_aac, mime_audio_ac3, mime_audio_AMR, mime_audio_AMR_WB,
    mime_audio_amr_wb_, mime_audio_aptx, mime_audio_asc, mime_audio_ATRAC_ADVANCED_LOSSLESS, mime_audio_ATRAC_X, mime_audio_ATRAC3,
    mime_audio_basic, mime_audio_BV16, mime_audio_BV32, mime_audio_clearmode, mime_audio_CN, mime_audio_DAT12, mime_audio_dls,
    mime_audio_dsr_es201108, mime_audio_dsr_es202050, mime_audio_dsr_es202211, mime_audio_dsr_es202212, mime_audio_DV, mime_audio_DVI4,
    mime_audio_eac3, mime_audio_encaprtp, mime_audio_EVRC, mime_audio_EVRC_QCP, mime_audio_EVRC0, mime_audio_EVRC1, mime_audio_EVRCB,
    mime_audio_EVRCB0, mime_audio_EVRCB1, mime_audio_EVRCNW, mime_audio_EVRCNW0, mime_audio_EVRCNW1, mime_audio_EVRCWB, mime_audio_EVRCWB0,
    mime_audio_EVRCWB1, mime_audio_EVS, mime_audio_example, mime_audio_flexfec, mime_audio_fwdred, mime_audio_G711_0, mime_audio_G719,
    mime_audio_G7221, mime_audio_G722, mime_audio_G723, mime_audio_G726_16, mime_audio_G726_24, mime_audio_G726_32, mime_audio_G726_40,
    mime_audio_G728, mime_audio_G729, mime_audio_G7291, mime_audio_G729D, mime_audio_G729E, mime_audio_GSM, mime_audio_GSM_EFR,
    mime_audio_GSM_HR_08, mime_audio_iLBC, mime_audio_ip_mr_v2_5, mime_audio_L8, mime_audio_L16, mime_audio_L20, mime_audio_L24,
    mime_audio_LPC, mime_audio_MELP, mime_audio_MELP600, mime_audio_MELP1200, mime_audio_MELP2400, mime_audio_mhas, mime_audio_mobile_xmf,
    mime_audio_MPA, mime_audio_mp4, mime_audio_MP4A_LATM, mime_audio_mpa_robust, mime_audio_mpeg, mime_audio_mpeg4_generic, mime_audio_ogg,
    mime_audio_opus, mime_audio_parityfec, mime_audio_PCMA, mime_audio_PCMA_WB, mime_audio_PCMU, mime_audio_PCMU_WB, mime_audio_prs_sid,
    mime_audio_QCELP, mime_audio_raptorfec, mime_audio_RED, mime_audio_rtp_enc_aescm128, mime_audio_rtploopback, mime_audio_rtp_midi,
    mime_audio_rtx, mime_audio_SMV, mime_audio_SMV0, mime_audio_SMV_QCP, mime_audio_sp_midi, mime_audio_speex, mime_audio_t140c,
    mime_audio_t38, mime_audio_telephone_event, mime_audio_TETRA_ACELP, mime_audio_TETRA_ACELP_BB, mime_audio_tone, mime_audio_UEMCLIP,
    mime_audio_ulpfec, mime_audio_usac, mime_audio_VDVI, mime_audio_VMR_WB, mime_audio_vnd_3gpp_iufp, mime_audio_vnd_4SB,
    mime_audio_vnd_audiokoz, mime_audio_vnd_CELP, mime_audio_vnd_cisco_nse, mime_audio_vnd_cmles_radio_events, mime_audio_vnd_cns_anp1,
    mime_audio_vnd_cns_inf1, mime_audio_vnd_dece_audio, mime_audio_vnd_digital_winds, mime_audio_vnd_dlna_adts, mime_audio_vnd_dolby_heaac_1,
    mime_audio_vnd_dolby_heaac_2, mime_audio_vnd_dolby_mlp, mime_audio_vnd_dolby_mps, mime_audio_vnd_dolby_pl2, mime_audio_vnd_dolby_pl2x,
    mime_audio_vnd_dolby_pl2z, mime_audio_vnd_dolby_pulse_1, mime_audio_vnd_dra, mime_audio_vnd_dts, mime_audio_vnd_dts_hd,
    mime_audio_vnd_dts_uhd, mime_audio_vnd_dvb_file, mime_audio_vnd_everad_plj, mime_audio_vnd_hns_audio, mime_audio_vnd_lucent_voice,
    mime_audio_vnd_ms_playready_media_pya, mime_audio_vnd_nokia_mobile_xmf, mime_audio_vnd_nortel_vbk, mime_audio_vnd_nuera_ecelp4800,
    mime_audio_vnd_nuera_ecelp7470, mime_audio_vnd_nuera_ecelp9600, mime_audio_vnd_octel_sbc, mime_audio_vnd_presonus_multitrack,
    mime_audio_vnd_qcelp, mime_audio_vnd_rhetorex_32kadpcm, mime_audio_vnd_rip, mime_audio_vnd_sealedmedia_softseal_mpeg,
    mime_audio_vnd_vmx_cvsd, mime_audio_vorbis, mime_audio_vorbis_config, mime_font_collection, mime_font_otf, mime_font_sfnt,
    mime_font_ttf, mime_font_woff, mime_font_woff2, mime_image_aces, mime_image_avci, mime_image_avcs, mime_image_bmp, mime_image_cgm,
    mime_image_dicom_rle, mime_image_emf, mime_image_example, mime_image_fits, mime_image_g3fax, mime_image_gif, mime_image_heic,
    mime_image_heic_sequence, mime_image_heif, mime_image_heif_sequence, mime_image_hej2k, mime_image_hsj2, mime_image_ief, mime_image_jls,
    mime_image_jp2, mime_image_jpeg, mime_image_jph, mime_image_jphc, mime_image_jpm, mime_image_jpx, mime_image_jxr, mime_image_jxrA,
    mime_image_jxrS, mime_image_jxs, mime_image_jxsc, mime_image_jxsi, mime_image_jxss, mime_image_ktx, mime_image_naplps, mime_image_png,
    mime_image_prs_btif, mime_image_prs_pti, mime_image_pwg_raster, mime_image_svg_xml, mime_image_t38, mime_image_tiff, mime_image_tiff_fx,
    mime_image_vnd_adobe_photoshop, mime_image_vnd_airzip_accelerator_azv, mime_image_vnd_cns_inf2, mime_image_vnd_dece_graphic,
    mime_image_vnd_djvu, mime_image_vnd_dwg, mime_image_vnd_dxf, mime_image_vnd_dvb_subtitle, mime_image_vnd_fastbidsheet,
    mime_image_vnd_fpx, mime_image_vnd_fst, mime_image_vnd_fujixerox_edmics_mmr, mime_image_vnd_fujixerox_edmics_rlc,
    mime_image_vnd_globalgraphics_pgb, mime_image_vnd_microsoft_icon, mime_image_vnd_mix, mime_image_vnd_ms_modi,
    mime_image_vnd_mozilla_apng, mime_image_vnd_net_fpx, mime_image_vnd_radiance, mime_image_vnd_sealed_png,
    mime_image_vnd_sealedmedia_softseal_gif, mime_image_vnd_sealedmedia_softseal_jpg, mime_image_vnd_svf, mime_image_vnd_tencent_tap,
    mime_image_vnd_valve_source_texture, mime_image_vnd_wap_wbmp, mime_image_vnd_xiff, mime_image_vnd_zbrush_pcx, mime_image_wmf,
    mime_image_xemf, mime_image_xwmf, mime_message_CPIM, mime_message_delivery_status, mime_message_disposition_notification,
    mime_message_example, mime_message_external_body, mime_message_feedback_report, mime_message_global, mime_message_global_delivery_status,
    mime_message_global_disposition_notification, mime_message_global_headers, mime_message_http, mime_message_imdn_xml, mime_message_news,
    mime_message_partial, mime_message_rfc822, mime_message_s_http, mime_message_sip, mime_message_sipfrag, mime_message_tracking_status,
    mime_message_vnd_si_simp, mime_message_vnd_wfa_wsc, mime_model_3mf, mime_model_example, mime_model_gltf_binary, mime_model_gltf_json,
    mime_model_iges, mime_model_mesh, mime_model_mtl, mime_model_obj, mime_model_stl, mime_model_vnd_collada_xml, mime_model_vnd_dwf,
    mime_model_vnd_flatland_3dml, mime_model_vnd_gdl, mime_model_vnd_gs_gdl, mime_model_vnd_gtw, mime_model_vnd_moml_xml,
    mime_model_vnd_mts, mime_model_vnd_opengex, mime_model_vnd_parasolid_transmit_binary, mime_model_vnd_parasolid_transmit_text,
    mime_model_vnd_rosette_annotated_data_model, mime_model_vnd_usdz_zip, mime_model_vnd_valve_source_compiled_map, mime_model_vnd_vtu,
    mime_model_vrml, mime_model_x3d_vrml, mime_model_x3d_fastinfoset, mime_model_x3d_xml, mime_multipart_alternative,
    mime_multipart_appledouble, mime_multipart_byteranges, mime_multipart_digest, mime_multipart_encrypted, mime_multipart_example,
    mime_multipart_form_data, mime_multipart_header_set, mime_multipart_mixed, mime_multipart_multilingual, mime_multipart_parallel,
    mime_multipart_related, mime_multipart_report, mime_multipart_signed, mime_multipart_vnd_bint_med_plus, mime_multipart_voice_message,
    mime_multipart_x_mixed_replace, mime_text_1d_interleaved_parityfec, mime_text_cache_manifest, mime_text_calendar, mime_text_css,
    mime_text_csv, mime_text_csv_schema, mime_text_directory, mime_text_dns, mime_text_ecmascript, mime_text_encaprtp, mime_text_enriched,
    mime_text_example, mime_text_flexfec, mime_text_fwdred, mime_text_grammar_ref_list, mime_text_html, mime_text_javascript, mime_text_javascript_x,
    mime_text_javascript10, mime_text_javascript11, mime_text_javascript12, mime_text_javascript13, mime_text_javascript14,
    mime_text_javascript15, mime_text_jcr_cnd, mime_text_jscript, mime_text_livescript, mime_text_markdown, mime_text_mizar,
    mime_text_n3, mime_text_parameters, mime_text_parityfec, mime_text_plain, mime_text_provenance_notation, mime_text_prs_fallenstein_rst,
    mime_text_prs_lines_tag, mime_text_prs_prop_logic, mime_text_raptorfec, mime_text_RED, mime_text_rfc822_headers, mime_text_richtext,
    mime_text_rtf, mime_text_rtp_enc_aescm128, mime_text_rtploopback, mime_text_rtx, mime_text_SGML, mime_text_strings, mime_text_t140,
    mime_text_tab_separated_values, mime_text_tcl, // HTML 4.01 spec example
    mime_text_troff, mime_text_turtle, mime_text_ulpfec,mime_text_uri_list, mime_text_vbscript, // HTML 4.01 spec example
    mime_text_vcard, mime_text_vnd_a, mime_text_vnd_abc, mime_text_vnd_ascii_art, mime_text_vnd_curl, mime_text_vnd_debian_copyright,
    mime_text_vnd_DMClientScript, mime_text_vnd_dvb_subtitle, mime_text_vnd_esmertec_theme_descriptor, mime_text_vnd_ficlab_flt,
    mime_text_vnd_fly, mime_text_vnd_fmi_flexstor, mime_text_vnd_gml, mime_text_vnd_graphviz, mime_text_vnd_hgl, mime_text_vnd_in3d_3dml,
    mime_text_vnd_in3d_spot, mime_text_vnd_IPTC_NewsML, mime_text_vnd_IPTC_NITF, mime_text_vnd_latex_z, mime_text_vnd_motorola_reflex,
    mime_text_vnd_ms_mediapackage, mime_text_vnd_net2phone_commcenter_command, mime_text_vnd_radisys_msml_basic_layout,
    mime_text_vnd_senx_warpscript, mime_text_vnd_si_uricatalogue, mime_text_vnd_sun_j2me_app_descriptor, mime_text_vnd_sosi,
    mime_text_vnd_trolltech_linguist, mime_text_vnd_wap_si, mime_text_vnd_wap_sl, mime_text_vnd_wap_wml, mime_text_vnd_wap_wmlscript,
    mime_text_vtt, mime_text_x_ecmascript, mime_text_x_javascript, mime_text_xml, mime_text_xml_external_parsed_entity,
    mime_video_1d_interleaved_parityfec, mime_video_3gpp, mime_video_3gpp2, mime_video_3gpp_tt, mime_video_BMPEG, mime_video_BT656,
    mime_video_CelB, mime_video_DV, mime_video_encaprtp, mime_video_example, mime_video_flexfec, mime_video_H261, mime_video_H263,
    mime_video_H263_1998, mime_video_H263_2000, mime_video_H264, mime_video_H264_RCDO, mime_video_H264_SVC, mime_video_H265,
    mime_video_iso_segment, mime_video_JPEG, mime_video_jpeg2000, mime_video_mj2, mime_video_MP1S, mime_video_MP2P, mime_video_MP2T,
    mime_video_mp4, mime_video_MP4V_ES, mime_video_MPV, mime_video_mpeg, mime_video_mpeg4_generic, mime_video_nv, mime_video_ogg,
    mime_video_parityfec, mime_video_pointer, mime_video_quicktime, mime_video_raptorfec, mime_video_raw, mime_video_rtp_enc_aescm128,
    mime_video_rtploopback, mime_video_rtx, mime_video_smpte291, mime_video_SMPTE292M, mime_video_ulpfec, mime_video_vc1,
    mime_video_vc2, mime_video_vnd_CCTV, mime_video_vnd_dece_hd, mime_video_vnd_dece_mobile, mime_video_vnd_dece_mp4,
    mime_video_vnd_dece_pd, mime_video_vnd_dece_sd, mime_video_vnd_dece_video, mime_video_vnd_directv_mpeg, mime_video_vnd_directv_mpeg_tts,
    mime_video_vnd_dlna_mpeg_tts, mime_video_vnd_dvb_file, mime_video_vnd_fvt, mime_video_vnd_hns_video,
    mime_video_vnd_iptvforum_1dparityfec_1010, mime_video_vnd_iptvforum_1dparityfec_2005, mime_video_vnd_iptvforum_2dparityfec_1010,
    mime_video_vnd_iptvforum_2dparityfec_2005, mime_video_vnd_iptvforum_ttsavc, mime_video_vnd_iptvforum_ttsmpeg2,
    mime_video_vnd_motorola_video, mime_video_vnd_motorola_videop, mime_video_vnd_mpegurl, mime_video_vnd_ms_playready_media_pyv,
    mime_video_vnd_nokia_interleaved_multimedia, mime_video_vnd_nokia_mp4vr, mime_video_vnd_nokia_videovoip, mime_video_vnd_objectvideo,
    mime_video_vnd_radgamettools_bink, mime_video_vnd_radgamettools_smacker, mime_video_vnd_sealed_mpeg1, mime_video_vnd_sealed_mpeg4,
    mime_video_vnd_sealed_swf, mime_video_vnd_sealedmedia_softseal_mov, mime_video_vnd_uvvu_mp4, mime_video_vnd_youtube_yt,
    mime_video_vnd_vivo, mime_video_VP8, mime_faux_module,

    // https://www.lifewire.com/file-extensions-and-mime-types-3469109
    mime_application_envoy, mime_application_fractals, mime_application_futuresplash, mime_application_hta, mime_application_internet_property_stream,
    mime_application_oda, mime_application_olescript, mime_application_vnd_ms_outlook, mime_application_vnd_ms_pkicertstore,
    mime_application_vnd_ms_pkiseccat, mime_application_vnd_ms_pkistl, mime_application_winhlp, mime_application_x_bcpio, mime_application_x_cdf,
    mime_application_x_compress, mime_application_x_compressed, mime_application_x_cpio, mime_application_x_csh, mime_application_x_director,
    mime_application_pics_rules, mime_application_x_dvi, mime_application_x_gtar, mime_application_x_gzip, mime_application_x_hdf,
    mime_application_x_internet_signup, mime_application_x_iphone, mime_application_x_latex, mime_application_x_msaccess,
    mime_application_x_mscardfile, mime_application_x_msclip, mime_application_x_msdownload, mime_application_x_msmediaview, mime_application_x_msmetafile,
    mime_application_x_msmoney, mime_application_x_mspublisher, mime_application_x_msschedule, mime_application_x_msterminal, mime_application_x_mswrite,
    mime_application_x_netcdf, mime_application_x_perfmon, mime_application_x_pkcs12, mime_application_x_pkcs7_certificates, mime_application_x_pkcs7_certreqresp,
    mime_application_x_pkcs7_mime, mime_application_x_pkcs7_signature, mime_application_x_sh, mime_application_x_shar, mime_application_x_stuffit,
    mime_application_x_sv4cpio, mime_application_x_sv4crc, mime_application_x_tar, mime_application_x_tcl, mime_application_x_tex, mime_application_x_texinfo,
    mime_application_x_troff, mime_application_x_troff_man, mime_application_x_troff_me, mime_application_x_troff_ms, mime_application_x_ustar,
    mime_application_x_wais_source, mime_application_ynd_ms_pkipko, mime_audio_mid, mime_audio_x_aiff, mime_audio_x_mpegurl, mime_audio_x_pn_realaudio,
    mime_audio_x_wav, mime_image_cis_cod, mime_image_pipeg, mime_image_x_cmu_raster, mime_image_x_cmx, mime_image_x_icon, mime_x_world_x_vrml,
    mime_image_x_portable_anymap, mime_image_x_portable_bitmap, mime_image_x_portable_graymap, mime_image_x_portable_pixmap, mime_image_x_rgb,
    mime_image_x_xbitmap, mime_image_x_xpixmap, mime_image_x_xwindowdump, mime_text_h323, mime_text_iuls, mime_text_scriptlet, mime_text_webviewhtml,
    mime_text_x_component, mime_text_x_setext, mime_text_x_vcard, mime_video_x_la_asf, mime_video_x_ms_asf, mime_video_x_msvideo, mime_video_x_sgi_movie,

    // https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types
    mime_application_x_abiword, mime_application_x_freearc, mime_application_vnd_amazon_ebook, mime_application_x_bzip, mime_application_x_bzip2,
    mime_audio_midi, mime_audio_x_midi, mime_application_x_httpd_php, mime_video_mp2t, mime_audio_wav, mime_audio_webm,
    mime_video_webm, mime_image_webp, mime_application_x_7z_compressed,

    // microsoft (-ish)
    mime_application_news_message_id, mime_application_x_httpd_asp,

    mime_bork } e_mimetype;

typedef enum { mo_dilate, mo_erode } e_morphology_operator;
typedef enum { mo_display, mo_inline } e_mode;
typedef enum {  nd_negativeveryverythinmathspace, nd_negativeverythinmathspace, nd_negativethinmathspace, nd_negativemediummathspace,
                nd_negativethickmathspace, nd_negativeverythickmathspace, nd_negativeveryverythickmathspace, nd_veryverythinmathspace,
                nd_verythinmathspace, nd_thinmathspace, nd_mediummathspace, nd_thickmathspace, nd_verythickmathspace, nd_veryverythickmathspace } e_namedspace;
typedef enum {  ns_default, ns_bibo, ns_cc, ns_crs, ns_dbp, ns_dbp_owl, ns_dbr, ns_dc, ns_dcterms, ns_ex, ns_foaf, ns_its, ns_math, ns_owl,
                ns_rdf, ns_rdfa, ns_rdfs, ns_svg, ns_xhv, ns_xlink, ns_xhtml, ns_xmlns, ns_xsd, ns_xsi, ns_error } e_namespace;
const ::std::size_t first_runtime_namespace = static_cast < ::std::size_t > (ns_error) + 1;

typedef enum
{   nit_free,

    // crash
    nit_internal_parsing_error, nit_symbol_aleady_defined,

    // catastrophe
    nit_math, nit_svg, nit_no_compound, nit_doctype_incomprehensible, nit_element_offsite_base, nit_missing_set_value, nit_no_curl, nit_cannot_create_file,
    nit_cannot_write, nit_cannot_delete, nit_cannot_update, nit_cannot_read, nit_wrong_secret,

    // error
    nit_html_unrecognised, nit_newline_in_string, nit_invalid_character_code, nit_unrecognised_character_code, nit_invalid_character_denary, nit_denary_too_long,
    nit_invalid_character_hex, nit_hex_too_long, nit_hex_code_version, nit_cannot_load_css, nit_element_bizarre_base, nit_itemprop_name_charset_equiv, nit_not_an_integer,
    nit_unrecognised_value, nit_correctly_spelt, nit_confusion, nit_abbreviated_correctly, nit_nuts, nit_bad_colour, nit_single_character, nit_value_expected, nit_is_existential,
    nit_bad_id, nit_id_exists, nit_evermore, nit_infinite_number, nit_immeasurable, nit_positive, nit_empty, nit_sunk, nit_sex, nit_sizes, nit_badtarget, nit_phone,
    nit_timezone, nit_unsigned, nit_unknown, nit_bad_money, nit_lingo, nit_mime, nit_a_area, nit_relative_path, nit_url_id_unfound, nit_url_not_found, nit_link,
    nit_308, nit_400, nit_401, nit_403, nit_404, nit_407, nit_408, nit_451, nit_cannot_open, nit_found_rel, nit_no_fn, nit_n_fn, nit_hcard_infer, nit_no_n, nit_export_none,
    nit_invalid_attribute_version, nit_wrong_version, nit_sterile, nit_orphan, nit_wrong_parent, nit_invalid_element_version, nit_invalid_addendum, nit_unimplemented, nit_no_form,
    nit_only_once, nit_no_vocab, nit_no_plausible_vocab, nit_dubious_html, nit_insufficient, nit_invalid_protocol, nit_url_empty, nit_protocol_empty, nit_bad_char,
    nit_unknown_protocol, nit_not_just_protocol, nit_malformed_ipv6, nit_empty_ipv6, nit_invalid_ipv6, nit_bad_port, nit_empty_host, nit_invalid_ipv4, nit_invalid_domain,
    nit_base_undefined,
    nit_html_contradictory, nit_xhtml_recognised, nit_html_unknown_sgml, nit_public_unexpected, nit_unexpected_doctype_content, nit_correct_spelling, nit_attribute_unrecognised,
    nit_attribute_unrecognised_here, nit_attribute_name_unexpected_character, nit_missing_close_quote, nit_ends_in_xmp, nit_mixed_mess, nit_embedded_lingo, nit_encode_ampersand,
    nit_ssi, nit_attributes_on_closure, nit_element_has_no_closure, nit_unexpected_closure, nit_missing_open, nit_missing_close, nit_class_microformat_property, nit_class_microformat_vocabulary,
    nit_text_html_expected, nit_charset_missing, nit_unadvised, nit_rejected, nit_bad_datetime, nit_unknown_rel, nit_deprecated_attribute, nit_excluded_attribute, nit_unrecognised_attribute,
    nit_bespoke_element, nit_deprecated_element, nit_duplicate_microformat, nit_unrecognised_class, nit_unrecognised_rel, nit_duplicate_rel, nit_cannot_find_mention,
    nit_pos_piracy, nit_url_empty_password, nit_url_insecure_password, nit_url_missing_at, nit_chocolate_teapot,
    nit_html_recognised, nit_presume_html_tags, nit_presume_html_1, nit_public_missing, nit_sq_bra_ket, nit_enquote_value, nit_double_angular_open, nit_use_quote_code, nit_use_double_quote_code,
    nit_lonely_ampersand, nit_empty_character_code, nit_bizarre_character_code, nit_empty_denary_code, nit_empty_hex_code, nit_dubious_denary, nit_invalid_denary, nit_code_unrecognised_here,
    nit_double_slash, nit_ignoring_unknown, nit_protocol, nit_write_wrote, nit_webmention,
    nit_missing_attribute_name, nit_element_no_type, nit_style_not_css, nit_gather, nit_mf_found, nit_prop_set, nit_sibling, nit_rel_found, nit_spotted_css_class,
    nit_html_tags, nit_html_plus, nit_html_1_0,
    nit_html_2_0, nit_html_2_0s, nit_html_2_0i, nit_html_2_0l1, nit_html_2_0l1s, nit_html_2_0l2,
    nit_html_3_0, nit_html_3_2,
    nit_html_4_00, nit_html_4_00s, nit_html_4_00f, nit_html_4_01, nit_html_4_01s, nit_html_4_01f,
    nit_xhtml_1_0, nit_xhtml_1_1, nit_xhtml_2_0,
    nit_html_5_0, nit_html_5_1, nit_html_5_2, nit_html_5_3, nit_html_5_living,
    nit_debug, nit_detail, nit_attribute_recognised, nit_found_css_class, nit_splurge, nit_all,
    nit_eof_in_string, nit_eof_in_comment, nit_eof_in_ssi, nit_eof_in_script, nit_eof_in_element, nit_eof_unexpected, nit_title_required,
    nit_one_title, nit_long_title, nit_only_elements, nit_closure_not_xmp, nit_one_isindex, nit_rel_requires_href, nit_bad_border, nit_bad_ismap,
    nit_urn_undefined, nit_methods_undefined, nit_render, nit_mosaic_crash, nit_use_htmlplus, nit_inserted_missing_closure, nit_inserted_missing_parent,
    nit_equiv_error, nit_ignoring_extra_content, nit_missing_content, nit_equiv_refresh, nit_x_ua_compatible, nit_use_metaname, nit_not_html2_level_1,
    nit_bad_compact, nit_url_missing_username, nit_1_to_7, nit_plus_1_7, nit_attribute_required, nit_frameset_body, nit_unknown_xhtml, nit_xhtml_missing_slash,
    nit_xhtml_element_lc, nit_xhtml_quote_values, nit_xhtml_attribute_lc, nit_xhtml_existential_makework, nit_existential_value, nit_xhtml_enum_lc,
    nit_xhtml_hex_lc, nit_attribute_repeated, nit_eof_in_cdata, nit_xhtml_cdata, nit_negative_dosh, nit_mf_empty, nit_bad_rating, nit_no_tel,
    nit_xhtml_css, nit_naughty_lang, nit_nahtch, nit_charset_redefined, nit_not_utf_8, nit_no_content, nit_default_role, nit_bad_role,
    nit_use_datetime, nit_alt_title, nit_naughty_alt, nit_data_type, nit_typemustmatch, nit_missing_dynamic, nit_bad_meta_place, nit_bad_ancestor,
    nit_value_ol, nit_too_many_figcaption, nit_figcaption_middle, nit_missing_case, nit_requires_html, nit_overallowed, nit_saucy_source,
    nit_area_map_template, nit_requires_href, nit_bad_aspect_ratio, nit_bad_2pt, nit_table_manners, nit_unreal, nit_no_namespaces_left,
    nit_xmlns_namespace, nit_table_children, nit_colgroup_children, nit_input_bad_mix, nit_option_child, nit_fieldset_legend, nit_bad_noscript,
    nit_src_required, nit_element_unconstructed, nit_requires_xhtml, nit_text_content, nit_daft_rel_attr, nit_link_rel_off, nit_autofocus,
    nit_virtual_exception, nit_bad_parameter, nit_bad_path, nit_scan_failed, nit_examine_failed, nit_stage, nit_id_hidden, nit_empty_link,
    nit_requires_itemscope, nit_requires_itemtype, nit_bad_itemprop, nit_double_gin_and_tonic, nit_lang_xmllang, nit_no_xmllang,
    nit_avoid_manifest, nit_base_b4_lynx, nit_as_not_image, nit_bad_srcset, nit_mq_syntax, nit_attempted_escape, nit_no_such_folder,
    nit_dinosaur, nit_no_main_kids, nit_bad_descendant, nit_dl_div, nit_no_dd, nit_dl_ancestor, nit_figcaption_first_last, nit_dt_dd,
    nit_rfc_1867, nit_rfc_1942, nit_rfc_1980, nit_rfc_2070, nit_file_requires_enctype, nit_form_urlencoded, nit_use_post, nit_mime_list,
    nit_no_exec, nit_unknown_ssi, nit_attribute_assignment, nit_invalid_config, nit_invalid_set, nit_invalid_echo, nit_unsupported_code,
    nit_ssi_include_error, nit_invalid_fsize, nit_ssi_if, nit_linechange, nit_no_if, nit_invalid_flastmod, nit_ssi_syntax, nit_cannot_access,
    nit_key, nit_interactive, nit_tabindex, nit_schema_url, nit_unrecognised_schema, nit_schema_domain, nit_mix_ruby_non, nit_too_many_ruby,
    nit_no_rp, nit_too_many_rp, nit_not_img, nit_bad_iframe, nit_bad_embed, nit_wild_attribute, nit_attribute_barred, nit_bad_object,
    nit_disordered_param, nit_source_track, nit_src_source, nit_media_descendants, nit_autoplay, nit_out_of_order, nit_kind_media_srclang,
    nit_track_default, nit_name_id, nit_need_coords, nit_bad_coords, nit_1000, nit_bad_header_id, nit_form_charset, nit_deprecated_value,
    nit_bad_for, nit_label_parentage, nit_input_bad_aria, nit_illegal_value, nit_bad_email, nit_bang_path, nit_unacceptable, nit_lonely_radio,
    nit_minmax, nit_pattern, nit_bad_datalist_id, nit_placeholder, nit_bad_form, nit_bad_select, nit_bad_datalist, nit_bad_option,
    nit_bad_textarea, nit_no_progress, nit_bad_meter, nit_not_form, nit_special_name, nit_solo, nit_bad_autocomplete, nit_snafu,
    nit_details_summary, nit_summary_header, nit_bad_dialogue, nit_bad_contextmenu, nit_bad_script, nit_bad_itemid, nit_untidy_string,
    nit_no_itemscope, nit_new_itemprop, nit_type_error, nit_schema_property, nit_forgotten_name, nit_incompatible_itemtype, nit_inlist,
    nit_schema_hierarchy, nit_html, nit_angle, nit_svg_version, nit_bad_rgb, nit_bad_frequency, nit_icc_colour, nit_svg_ancestor, nit_rdf,
    nit_bad_namespace, nit_svg_rdf, nit_clipped, nit_closed_shape, nit_mf_infer, nit_path_spec, nit_lighting, nit_animatemotion,
    nit_fontface, nit_switch, nit_transform, nit_attribute_name, nit_repeated_attribute, nit_svg_xy, nit_fontstyle, nit_svg_math,
    nit_fontstretch, nit_fontvariant, nit_fontweight, nit_panose_1, nit_icarus, nit_vector_effect, nit_paint, nit_0_1, nit_1_more,
    nit_dashed, nit_marker, nit_background, nit_bad_result, nit_not_schema_property, nit_curses, nit_xlinktype, nit_xlinkactuate,
    nit_dur, nit_svg_values, nit_rotate, nit_origin, nit_colour_matrix, nit_math_kids, nit_bad_hunit, nit_bad_vunit, nit_too_many,
    nit_use_apply, nit_base, nit_declare_first, nit_arg_count, nit_operator_required, nit_bad_bvar, nit_bad_doa, nit_bad_piece,
    nit_annotation, nit_eof_in_annotation, nit_prefix_odd, nit_prefix_format, nit_rdf_redefine, nit_rdf_confusion, nit_rdf_protocol,
    nit_math_href, nit_math_empty, nit_mglyph_alt_src, nit_dir_rtl_ltr, nit_bad_linebreak, nit_non_standard_value, nit_mscarries_last,
    nit_bad_bind, nit_bad_share, nit_shadow, nit_out_of_memory, nit_duplicate, nit_shadow_failed, nit_create_folder, nit_internal_file_error,
    nit_shadow_ignore, nit_shadow_link, nit_shadow_copy, nit_too_big, nit_icu, nit_lang_redefined, nit_page_charset, nit_charset_mismatch,
    nit_charset_used, nit_charset_invalid, nit_no_converters, nit_xhtml_superseded, nit_not_iso_8859_1, hit_draft_html_5, nit_overriding_html,
    nit_whatwg_class, nit_opening_file, nit_target, nit_bad_mummy, nit_no_serviceworker, nit_rel_head, nit_theme_colour, nit_refresh_zero,
    nit_bad_csp_directive, nit_bad_number_once, nit_bad_csp_source, nit_invalid_algorithm, nit_insufficient_content, nit_bad_q,
    nit_bad_cookie, nit_bad_cache, nit_bad_link_pragma, nit_nocando, nit_bad_root, nit_isnt, nit_menu_type, nit_menu_child, nit_bad_dl,
    nit_repeated_definition, nit_contradictory_expansion, nit_naughty_grave, nit_encode, nit_svg_data, nit_data, nit_bad_wild,
    nit_risky_filetype, nit_reputation, nit_incompatible_mime, nit_os_dependent, nit_bad_usemap, nit_bad_type_attribute, nit_bad_pattern,

    nit_context,

    // eof
    nit_off } e_nit;

typedef enum { no_dsssl, no_w3c } e_notations;
typedef enum { nsd_none, nsd_space, nsd_dashed } e_nsd;
typedef enum { og_musicsong, og_musicalbum, og_musicplaylist, og_musicradiostation, og_videomovie, og_videoepisode, og_videotvshow, og_videoother,
               og_article, og_book, og_profile, og_website } e_ogtype;
typedef enum { oo_off, oo_on } e_onoff;
typedef enum { op_arithmetic, op_atop, op_in, op_out, op_over, op_xor } e_operator;
typedef enum { or_h, or_v } e_orientation;
typedef enum { pk_bad, pk_none, pk_currentcolour, pk_inherit, pk_icccolour, pk_url } e_paintkeyword;
typedef enum { ph_bubble, ph_capture, ph_default, ph_target } e_phase;
typedef enum { ps_b, ps_i, ps_p, ps_s, ps_sub, ps_sup, ps_tt, ps_u } e_plusstyle;
typedef enum { pe_visiblepainted, pe_visiblefill, pe_visiblestroke, pe_visible, pe_painted, pe_fill, pe_stroke, pe_all, pe_none, pe_inherit } e_pointerevents;
typedef enum { pr_auto, pr_metadata, pr_none } e_preload;
typedef enum { pt_footnote, pt_reference, pt_section, pt_sidebar, pt_silent } e_print;
typedef enum { pr_stop, pr_continue } e_propagate;
typedef int e_property;
typedef enum { pr_other, pr_file, pr_ftp, pr_ftps, pr_geo, pr_http, pr_https, pr_ldap, pr_mailto, pr_news, pr_sftp, pr_ssh, pr_telnet, pr_tel, pr_urn } e_protocol;
typedef enum { rf_no, rf_downgrade, rf_same, rf_origin, rf_strict, rf_strictcross, rf_cross, rf_unsafe } e_referrer;

typedef enum {
    r_context,

    // microformats v1 only
    r_entry_category = (int) c_error + 1,

    // both v1 and v2
    r_acquaintance, r_alternative, r_appendix, r_author, r_bookmark, r_chapter, r_child, r_colleague, r_contact,
    r_contents, r_copyright, r_coresident, r_coworker, r_crush, r_date, r_directory, r_enclosure, r_first, r_friend,
    r_glossary, r_help, r_home, r_index, r_in_reply_to, r_its_rules, r_kin, r_last, r_licence, r_me, r_met, r_muse,
    r_parent, r_payment, r_prev, r_pronunciation, r_section, r_sibling, r_sidebar,  r_spouse, r_start, r_stylesheet,
    r_subsection, r_supercedes, r_sweetheart, r_toc, r_top, r_transformation, r_up, r_vcs_git, r_vcs_svn,
    r_micropub, r_pingback, r_webmention, r_canonical, r_code_licence, r_content_licence, r_discussion, r_issues,
    r_bibliography, r_cite, r_group, r_map, r_member,
    r_neighbour, r_next, r_nofollow, r_tag,

    // microformats v2 only
    r_about, r_profile, r_accessibility,

        // https://github.com/ampproject/amphtml
    r_amphtml,

    r_apple_touch_icon, r_apple_touch_icon_precomposed,
    r_apple_touch_startup_image,

    // https://sitemorse.com/rel-archived/
    r_archived,

    r_archives, r_attachment, r_authorisation_endpoint, r_banner, r_begin, r_biblioentry,
    r_blocked_by, r_category, r_chrome_webstore_item, r_citation,
    r_cite_as, r_code_repository, r_collection, r_comment, r_component,
    r_content_repository, r_contribution, r_convertedfrom, r_create_form,
    r_current, r_dcterms_conformsto, r_dcterms_contributor, r_dcterms_creator, r_dcterms_description, r_dcterms_hasformat,
    r_dcterms_haspart, r_dcterms_hasversion, r_dcterms_isformatof, r_dcterms_ispartof, r_dcterms_isreferencedby, r_dcterms_isreplacedby,
    r_dcterms_isrequiredby, r_dcterms_isversionof, r_dcterms_licence, r_dcterms_mediator, r_dcterms_publisher, r_dcterms_references,
    r_dcterms_relation, r_dcterms_replaces, r_dcterms_requires, r_dcterms_rightsholder, r_dcterms_source, r_dcterms_subject, r_definition,
    r_describedby, r_describes, r_disclaimer, r_disclosure, r_dnsprefetch, r_docs_oasis_open_org_ns_cmis_link_200908_acl,
    r_duplicate, r_edit, r_edit_form, r_edit_media, r_editor, r_edituri, r_end, r_endorsed, r_entry_content, r_external,
    r_fan, r_feed, r_footnote, r_gbfs, r_gtfs_realtime, r_gtfs_static, r_hosts,
    r_hub, r_icon, r_image_src, r_import, r_intervalafter, r_intervalbefore, r_intervalcontains, r_intervaldisjoint,
    r_intervalduring, r_intervalequals, r_intervalfinishedby, r_intervalfinishes, r_intervalin, r_intervalmeets, r_intervalmetby,
    r_intervaloverlappedby, r_intervaloverlaps, r_intervalstartedby, r_intervalstarts, r_item, r_item_licence, r_jslicence,
    r_kinetic_stylesheet, r_latest_version, r_lightbox, r_lightvideo, r_logo, r_longdesc, r_lrdd, r_m_pagescroll2id, r_made,
    r_manifest, r_maskicon, r_memento, r_meta, r_microsummary, r_monitor, r_monitor_group,
    r_next_archive, r_navigate, r_noopener, r_noreferrer, r_openid2_local_id, r_openid2_provider,
    r_openid_delegate, r_openid_server, r_origin, r_original, r_p3pv1, r_pavatar, r_permalink, r_pgpkey, r_pointer,
    r_popover, r_preconnect, r_predecessor_version, r_prefetch, r_preload, r_prerender, r_prev_archive, r_preview,
    r_principles, r_privacy, r_privacy_policy,
    r_publickey, r_publisher, r_radioepg, r_referral, r_related, r_rendition, r_replies, r_reply_to, r_resource,
    r_respond_proxy, r_respond_redirect, r_restconf, r_root, r_schema_dc, r_schema_dcterms, r_search, r_self, r_service,
    r_service_desc, r_service_doc, r_service_meta, r_shortlink, r_sitemap, r_source, r_sponsor,
    r_status, r_stylesheetless, r_subresource, r_successor_version, r_sunset, r_sword, r_syndication,
    r_terms_of_service, r_timegate, r_timemap, r_timesheet, r_token_endpoint, r_tooltip, r_trackback, r_trademark,
    r_translation, r_type, r_unendorsed, r_urc, r_user, r_vcalendar_child, r_vcalendar_parent, r_vcalendar_sibling,
    r_version_history, r_via, r_w_api_org, r_widget, r_wlwmanifest, r_working_copy, r_working_copy_of,
    r_yandex_tableau_widget,

    // standard dublin core
    r_dc_contributor, r_dc_coverage, r_dc_creator, r_dc_date, r_dc_description, r_dc_format, r_dc_identifier, r_dc_language,
    r_dc_publisher, r_dc_relation, r_dc_rights, r_dc_source, r_dc_subject, r_dc_title, r_dc_type,

    // creative commons
    r_cc_permits, r_cc_requires, r_cc_prohibits, r_cc_jurisdiction, r_cc_legalcode, r_cc_deprecatedon,
    r_cc_licence, r_cc_morepermissions, r_cc_attributionname, r_cc_attributionurl, r_cc_useguidelines,

    // HTML 1.0 ()  plus made & search
    r_annotation, r_embed, r_history, r_includes, r_interested, r_present, r_recedes, r_reply, r_subdocument,
    r_supersedes, r_useglossary, r_useindex,

    // WhatWG HTML
    r_bodyok, r_modulepreload, r_opener, r_serviceworker,

    r_illegal } e_rel;

typedef enum { ri_auto, ri_perceptual, ri_relativecolourimetric, ri_saturation, ri_absolutecolourimetric } e_renderingintent;
typedef enum { re_always, re_whennotactive, re_never } e_restart;
typedef enum { ru_none, ru_groups, ru_rows, ru_cols, ru_all } e_rules;
typedef enum { rs_yes, rs_no, rs_maybe, rs_interested } e_rsvp;
typedef enum { s_unknown, s_adwua, s_asabua, s_atnbua, s_ad, s_forms, s_modals, s_orientation, s_pointer, s_popups, s_popupescape, s_presentation, s_origin, s_scripts, s_navigation } e_sandbox;

typedef enum
{   sch_context,

    sch_3dmodel,

    sch_abdomen, sch_aboutpage, sch_acceptaction, sch_accommodation, sch_accountingservice, sch_achieveaction, sch_action, sch_actionaccessspecification, sch_actionstatustype, sch_activationfee,
    sch_activateaction, sch_activeactionstatus,sch_activenotrecruiting, sch_addaction, sch_administrativearea, sch_adultentertainment, sch_advertisercontentarticle, sch_aerobicactivity, sch_aggregateoffer,
    sch_aggregaterating, sch_agreeaction, sch_airline, sch_airport, sch_albumrelease, sch_alignmentobject, sch_allergieshealthaspect, sch_allocateaction, sch_allwheeldriveconfiguration, sch_ampstory,
    sch_amradiochannel, sch_amusementpark, sch_anaerobicactivity, sch_anaesthesia, sch_analysisnewsarticle, sch_anatomicalstructure,sch_anatomicalsystem, sch_animalshelter, sch_answer, sch_apartment,
    sch_apartmentcomplex, sch_apireference, sch_appearance, sch_appendaction, sch_applyaction, sch_approvedindication, sch_aquarium, sch_archivecomponent,sch_archiveorganisation, sch_arriveaction,
    sch_artery, sch_artgallery, sch_article, sch_askaction, sch_askpublicnewsarticle, sch_assessaction, sch_assignaction, sch_atlas, sch_attorney, sch_audience, sch_audiobook, sch_audiobookformat,
    sch_audioobject, sch_authenticcontent, sch_authoriseaction, sch_authoritativelegalvalue, sch_autobodyshop, sch_autodealer, sch_automatedteller, sch_automotivebusiness, sch_autopartsstore,
    sch_autorental, sch_autorepair, sch_autowash,

    sch_backgroundnewsarticle, sch_backorder, sch_bacteria, sch_bakery, sch_balance, sch_bankaccount, sch_bankorcreditunion, sch_barcode, sch_barorpub, sch_basicincome, sch_beach, sch_beautysalon,
    sch_bedandbreakfast, sch_beddetails, sch_bedtype,  sch_befriendaction, sch_benefitshealthaspect, sch_bikestore, sch_blog, sch_blogposting, sch_bloodtest, sch_boardingpolicytype, sch_boatreservation,
    sch_boatterminal, sch_boattrip, sch_bodymeasurementarm, sch_bodymeasurementbust, sch_bodymeasurementchest, sch_bodymeasurementfoot, sch_bodymeasurementhand, sch_bodymeasurementhead,
    sch_bodymeasurementheight, sch_bodymeasurementhips, sch_bodymeasurementinsideleg, sch_bodymeasurementneck, sch_bodymeasurementtypeenumeration, sch_bodymeasurementunderbust, sch_bodymeasurementwaist,
    sch_bodymeasurementweight, sch_bodyofwater, sch_bone, sch_book, sch_bookformattype, sch_bookmarkaction, sch_bookseries, sch_bookstore, sch_boolean, sch_borrowaction, sch_bowlingalley,
    sch_brainstructure, sch_brand, sch_breadcrumblist, sch_brewery, sch_bridge, sch_broadcastchannel, sch_broadcastevent, sch_broadcastfrequencyspecification, sch_broadcastrelease, sch_broadcastservice,
    sch_brokerageaccount, sch_buddhisttemple, sch_businessaudience, sch_businessentitytype, sch_businessevent, sch_businessfunction, sch_businesssupport, sch_busorcoach, sch_busreservation,
    sch_busstation, sch_busstop, sch_bustrip, sch_buyaction,

    sch_cableorsatelliteservice, sch_cafeorcoffeeshop, sch_campground, sch_campingpitch, sch_canal, sch_cancelaction, sch_car, sch_cardiovascular, sch_cardiovascularexam, sch_carusagetype, sch_caseseries,
    sch_casino, sch_cassetteformat, sch_categorycode, sch_categorycodeset, sch_catholicchurch, sch_causeshealthaspect, sch_cdcpmdrecord, sch_cdformat, sch_cemetery, sch_chapter,
    sch_charitableincorporatedorganization, sch_checkaction, sch_checkinaction, sch_checkoutaction, sch_checkoutpage, sch_childcare, sch_childrensevent, sch_chooseaction, sch_church, sch_city, sch_cityhall,
    sch_civicstructure, sch_claim, sch_claimreview, sch_class, sch_cleaningfee, sch_clinician, sch_clip, sch_clothingstore, sch_code, sch_cohortstudy, sch_collection, sch_collectionpage,
    sch_collegeoruniversity, sch_comedyclub, sch_comedyevent, sch_comiccoverart, sch_comicissue, sch_comicseries, sch_comicstory, sch_comment, sch_commentaction, sch_commentpermission,
    sch_communicateaction, sch_communityhealth, sch_compilationalbum, sch_completed, sch_completedactionstatus, sch_completedatafeed, sch_compoundpricespecification, sch_computerlanguage, sch_computerstore,
    sch_confirmaction, sch_consortium, sch_consumeaction, sch_contactpage, sch_contactpoint, sch_contactpointoption, sch_contagiousnesshealthaspect, sch_continent, sch_controlaction, sch_conveniencestore,
    sch_conversation, sch_cookaction, sch_coop, sch_corporation, sch_correctioncomment, sch_country, sch_course, sch_courseinstance, sch_courthouse, sch_coverart, sch_covidtestingfacility, sch_createaction,
    sch_creativework, sch_creativeworkseason, sch_creativeworkseries, sch_creditcard, sch_crematorium, sch_criticreview, sch_crosssectional, sch_cssselectortype, sch_ct, sch_currencyconversionservice,

    sch_damagedcondition, sch_danceevent, sch_dancegroup, sch_datacatalogue, sch_datadownload, sch_datafeed, sch_datafeeditem, sch_datatype, sch_dataset, sch_date, sch_datedmoneyspecification, sch_datetime,
    sch_dayofweek, sch_dayspa, sch_ddxelement, sch_deactivateaction, sch_decontextualisedcontent, sch_defenceestablishment, sch_definedregion, sch_definedterm, sch_definedtermset, sch_definitivelegalvalue,
    sch_deleteaction, sch_deliverychargespecification, sch_deliveryevent, sch_deliverymethod, sch_deliverytimesettings, sch_demand, sch_demoalbum, sch_dentist, sch_dentistry, sch_departaction,
    sch_departmentstore, sch_depositaccount, sch_dermatology, sch_diabeticdiet, sch_diagnostic, sch_diagnosticlab, sch_diagnosticprocedure, sch_diet, sch_dietarysupplement, sch_dietnutrition,
    sch_digitalaudiotapeformat, sch_digitaldocument, sch_digitaldocumentpermission, sch_digitaldocumentpermissiontype, sch_digitalformat, sch_disabilitysupport, sch_disagreeaction, sch_discontinued,
    sch_discoveraction, sch_discussionforumposting, sch_dislikeaction, sch_distance, sch_distancefee, sch_distillery, sch_djmixalbum, sch_donateaction, sch_doseschedule, sch_doubleblindedtrial,
    sch_downloadaction, sch_downpayment, sch_drawaction, sch_drawing, sch_drinkaction, sch_drivewheelconfigurationvalue, sch_drivingschoolvehicleusage, sch_drug, sch_drugclass, sch_drugcost,
    sch_drugcostcategory, sch_druglegalstatus, sch_drugpregnancycategory, sch_drugprescriptionstatus, sch_drugstrength, sch_drycleaningorlaundry, sch_duration, sch_dvdformat,
    sch_dystopianhealthinsuranceplan, sch_dystopianhealthplancostsharingspecification, sch_dystopianhealthplanformulary, sch_dystopianhealthplannetwork,

    sch_ear, sch_eataction, sch_ebook, sch_editedorcroppedcontent, sch_educationalaudience, sch_educationaloccupationalcredential, sch_educationaloccupationalprogramme, sch_educationalorganisation,
    sch_educationevent, sch_effectivenesshealthaspect, sch_electrician, sch_electronicsstore,  sch_elementaryschool, sch_emailmessage, sch_embassy, sch_emergency, sch_emergencyservice, sch_employeerole,
    sch_employeraggregaterating, sch_employerreview, sch_employmentagency, sch_endocrine, sch_endorseaction, sch_endorsementrating, sch_energy, sch_energyconsumptiondetails,
    sch_energyefficiencyenumeration, sch_energystarcertified, sch_enginespecification, sch_enrollingbyinvitation, sch_entertainmentbusiness, sch_entrypoint, sch_enumeration, sch_environmentharm,
    sch_episode, sch_eprelease,sch_euenergyefficiencycategorya, sch_euenergyefficiencycategorya1plus, sch_euenergyefficiencycategorya2plus, sch_euenergyefficiencycategorya3plus,
    sch_euenergyefficiencycategoryb, sch_euenergyefficiencycategoryc, sch_euenergyefficiencycategoryd, sch_euenergyefficiencycategorye, sch_euenergyefficiencycategoryf, sch_euenergyefficiencycategoryg,
    sch_euenergyefficiencyenumeration, sch_event, sch_eventattendancemodeenumeration, sch_eventcancelled, sch_eventmovedonline, sch_eventpostponed, sch_eventrescheduled, sch_eventreservation,
    sch_eventscheduled, sch_eventseries, sch_eventstatustype, sch_eventvenue, sch_evidencelevela, sch_evidencelevelb, sch_evidencelevelc, sch_exchangeratespecification, sch_exchangerefund,
    sch_exerciseaction, sch_exercisegym, sch_exerciseplan, sch_exhibitionevent, sch_eye,

    sch_failedactionstatus, sch_false, sch_faqpage, sch_fastfoodrestaurant, sch_fdacategorya, sch_fdacategoryb, sch_fdacategoryc, sch_fdacategoryd, sch_fdacategoryx, sch_fdanotevaluated, sch_female,
    sch_festival, sch_filmaction, sch_financialproduct, sch_financialservice, sch_findaction, sch_firestation, sch_flexibility, sch_flight, sch_flightreservation, sch_float, sch_floorplan, sch_florist,
    sch_fmradiochannel, sch_followaction, sch_foodestablishment, sch_foodestablishmentreservation, sch_foodevent, sch_foodservice, sch_fourwheeldriveconfiguration, sch_friday,
    sch_frontwheeldriveconfiguration, sch_fullrefund, sch_fundingagency, sch_fundingscheme, sch_fungus, sch_furniturestore,

    sch_game, sch_gameplaymode, sch_gameserver, sch_gameserverstatus, sch_gardenstore, sch_gasstation, sch_gastroenterologic, sch_gatedresidencecommunity, sch_gendertype, sch_generalcontractor,
    sch_genetic, sch_genitourinary,sch_geocircle, sch_geocoordinates, sch_geoshape, sch_geospatialgeometry, sch_geriatric, sch_gettingaccesshealthaspect, sch_giveaction, sch_glutenfreediet,
    sch_golfcourse, sch_governmentbenefitstype, sch_governmentbuilding, sch_governmentoffice, sch_governmentorganisation, sch_governmentpermit, sch_governmentservice, sch_grant, sch_graphicnovel,
    sch_grocerystore, sch_groupboardingpolicy, sch_guide, sch_gynaecologic,

    sch_hackathon, sch_haematologic, sch_hairsalon, sch_halaldiet, sch_hardcover, sch_hardwarestore, sch_harmful, sch_head, sch_healthandbeautybusiness, sch_healthaspectenumeration, sch_healthcare,
    sch_healthclub, sch_healthtopiccontent, sch_hearingimpairedsupported, sch_highschool, sch_hindudiet, sch_hindutemple, sch_hobbyshop, sch_homeandconstructionbusiness, sch_homegoodsstore, sch_hospital,
    sch_hostel, sch_hotel, sch_hotelroom, sch_house, sch_housepainter,sch_howitworkshealthaspect, sch_howorwherehealthaspect, sch_howto, sch_howtodirection, sch_howtoitem, sch_howtosection, sch_howtostep,
    sch_howtosupply, sch_howtotip, sch_howtotool, sch_hvacbusiness, sch_hypertoc, sch_hypertocentry,

    sch_icecreamshop, sch_ignoreaction, sch_imagegallery, sch_imageobject, sch_imagingtest, sch_individualproduct, sch_infectious, sch_infectiousagentclass, sch_infectiousdisease, sch_inforce,
    sch_informaction, sch_ingredientshealthaspect, sch_insertaction, sch_installaction, sch_installment, sch_instock, sch_instoreonly, sch_insuranceagency, sch_intangible, sch_integer, sch_interactaction,
    sch_interactioncounter, sch_internationaltrial, sch_internetcafe, sch_investmentfund, sch_investmentordeposit, sch_inviteaction, sch_invoice, sch_invoiceprice, sch_itemavailability, sch_itemlist,
    sch_itemlistorderascending, sch_itemlistorderdescending, sch_itemlistordertype, sch_itemlistunordered, sch_itempage,

    sch_jewelrystore, sch_jobposting, sch_joinaction, sch_joint,

    sch_kosherdiet,

    sch_laboratoryscience, sch_lakebodyofwater, sch_landform, sch_landmarksorhistoricalbuildings, sch_language, sch_laserdiscformat, sch_learningresource, sch_leaveaction, sch_lefthanddriving, sch_legalforcestatus, sch_legalservice,
    sch_legalvaluelevel, sch_legislation, sch_legislationobject, sch_legislativebuilding, sch_leisuretimeactivity, sch_lendaction, sch_library, sch_librarysystem, sch_lifestylemodification, sch_ligament, sch_likeaction,
    sch_limitedavailability, sch_limitedbyguaranteecharity, sch_linkrole, sch_liquorstore, sch_listenaction, sch_listitem, sch_listprice, sch_literaryevent, sch_livealbum, sch_liveblogposting, sch_livingwithhealthaspect, sch_loanorcredit,
    sch_localbusiness, sch_locationfeaturespecification, sch_lockerdelivery, sch_locksmith, sch_lodgingbusiness, sch_lodgingreservation, sch_longitudinal, sch_loseaction, sch_lowcaloriediet, sch_lowfatdiet, sch_lowlactosediet,
    sch_lowsaltdiet, sch_lung, sch_lymphaticvessel,

    sch_magic, sch_male, sch_manuscript, sch_map, sch_mapcategorytype, sch_marryaction, sch_mass, sch_mathsolver, sch_maximumdoseschedule, sch_maytreathealthaspect, sch_measurementtypeenumeration, sch_mediagallery, sch_mediamanipulationratingenumeration, sch_mediaobject,
    sch_mediareview, sch_mediasubscription, sch_medicalaudience, sch_medicalaudiencetype, sch_medicalbusiness, sch_medicalcause, sch_medicalclinic, sch_medicalcode, sch_medicalcondition, sch_medicalconditionstage,
    sch_medicalcontraindication, sch_medicaldevice, sch_medicaldevicepurpose, sch_medicalentity, sch_medicalenumeration, sch_medicalevidencelevel, sch_medicalguideline, sch_medicalguidelinecontraindication,
    sch_medicalguidelinerecommendation, sch_medicalimagingtechnique, sch_medicalindication, sch_medicalintangible, sch_medicalobservationalstudy, sch_medicalobservationalstudydesign, sch_medicalorganisation, sch_medicalprocedure,
    sch_medicalproceduretype, sch_medicalresearcher, sch_medicalriskcalculator, sch_medicalriskestimator, sch_medicalriskfactor, sch_medicalriskscore, sch_medicalscholarlyarticle, sch_medicalsign, sch_medicalsignorsymptom,
    sch_medicalspeciality, sch_medicalstudy, sch_medicalstudystatus, sch_medicalsymptom, sch_medicaltest, sch_medicaltestpanel, sch_medicaltherapy, sch_medicaltrial, sch_medicaltrialdesign, sch_medicalwebpage, sch_medicinesystem,
    sch_meetingroom, sch_mensclothingstore, sch_menu, sch_menuitem, sch_menusection, sch_merchantreturnenumeration, sch_merchantreturnfinitereturnwindow, sch_merchantreturnnotpermitted, sch_merchantreturnpolicy,
    sch_merchantreturnunlimitedwindow, sch_merchantreturnunspecified, sch_message, sch_middleschool, sch_midwifery, sch_minimumadvertisedprice, sch_misconceptionshealthaspect, sch_missingcontext, sch_mixedeventattendancemode, sch_mixtapealbum,
    sch_mobileapplication, sch_mobilephonestore, sch_monday, sch_monetaryamount, sch_monetaryamountdistribution, sch_monetarygrant, sch_moneytransfer, sch_mortgageloan, sch_mosque, sch_motel, sch_motorcycle, sch_motorcycledealer, sch_msrp,
    sch_motorcyclerepair, sch_motorisedbicycle, sch_mountain, sch_moveaction, sch_movie, sch_movieclip, sch_movierentalstore, sch_movieseries, sch_movietheatre, sch_movingcompany, sch_mri, sch_multicellularparasite, sch_multicentretrial,
    sch_multiplayer, sch_muscle, sch_musculoskeletal, sch_musculoskeletalexam, sch_museum, sch_musicalbum, sch_musicalbumproductiontype, sch_musicalbumreleasetype, sch_musiccomposition, sch_musicevent, sch_musicgroup, sch_musicplaylist,
    sch_musicrecording, sch_musicrelease, sch_musicreleaseformattype, sch_musicstore, sch_musicvenue, sch_musicvideoobject,

    sch_nailsalon, sch_neck, sch_nerve, sch_neuro, sch_neurologic, sch_newcondition, sch_newsarticle, sch_newsmediaorganisation, sch_newspaper, sch_ngo, sch_nightclub, sch_nlnonprofittype, sch_noninvasiveprocedure, sch_nonprofit501a,
    sch_nonprofit501c1, sch_nonprofit501c10, sch_nonprofit501c11, sch_nonprofit501c12, sch_nonprofit501c13, sch_nonprofit501c14, sch_nonprofit501c15, sch_nonprofit501c16, sch_nonprofit501c17, sch_nonprofit501c18, sch_nonprofit501c19,
    sch_nonprofit501c2, sch_nonprofit501c20, sch_nonprofit501c21, sch_nonprofit501c22, sch_nonprofit501c23, sch_nonprofit501c24, sch_nonprofit501c25, sch_nonprofit501c26, sch_nonprofit501c27, sch_nonprofit501c28, sch_nonprofit501c3,
    sch_nonprofit501c4, sch_nonprofit501c5, sch_nonprofit501c6, sch_nonprofit501c7, sch_nonprofit501c8, sch_nonprofit501c9, sch_nonprofit501d, sch_nonprofit501e, sch_nonprofit501f, sch_nonprofit501k, sch_nonprofit501n, sch_nonprofit501q,
    sch_nonprofit527, sch_nonprofitanbi, sch_nonprofitsbbi, sch_nonprofittype, sch_nose, sch_notary, sch_notedigitaldocument, sch_notinforce, sch_notyetrecruiting, sch_number, sch_nursing, sch_nutritioninformation,

    sch_observation, sch_observational, sch_obstetric, sch_occupation, sch_occupationalactivity, sch_occupationalexperiencerequirements, sch_occupationaltherapy, sch_oceanbodyofwater, sch_offer, sch_offercatalogue, sch_offerforlease, sch_offerforpurchase,
    sch_offeritemcondition, sch_offershippingdetails, sch_officeequipmentstore, sch_officiallegalvalue, sch_offlineeventattendancemode, sch_offlinepermanently, sch_offlinetemporarily, sch_oncologic, sch_ondemandevent, sch_onetimepayments,
    sch_online, sch_onlineeventattendancemode, sch_onlinefull, sch_onlineonly, sch_onsitepickup, sch_openinghoursspecification, sch_opentrial, sch_opinionnewsarticle, sch_optician, sch_optometric, sch_order, sch_orderaction,
    sch_ordercancelled, sch_orderdelivered, sch_orderintransit, sch_orderitem, sch_orderpaymentdue, sch_orderpickupavailable, sch_orderproblem, sch_orderprocessing, sch_orderreturned, sch_orderstatus, sch_organisation,
    sch_organisationrole, sch_organiseaction, sch_originalmediacontent, sch_originalshippingfees, sch_osteopathic, sch_otc, sch_otolaryngologic, sch_outletstore, sch_outofstock, sch_overviewhealthaspect, sch_ownershipinfo,

    sch_paediatric, sch_paidleave, sch_paintaction, sch_painting, sch_palliativeprocedure, sch_paperback, sch_parceldelivery, sch_parcelservice, sch_parentalsupport, sch_parentaudience, sch_park, sch_parkingfacility, sch_parkingmap,
    sch_partiallyinforce, sch_pathology, sch_pathologytest, sch_patient, sch_patientexperiencehealthaspect, sch_pawnshop, sch_payaction, sch_paymentautomaticallyapplied, sch_paymentcard, sch_paymentchargespecification,
    sch_paymentcomplete, sch_paymentdeclined, sch_paymentdue, sch_paymentmethod, sch_paymentpastdue, sch_paymentservice, sch_paymentstatustype, sch_peopleaudience, sch_percutaneousprocedure, sch_performaction, sch_performancerole,
    sch_performingartstheatre, sch_performinggroup, sch_periodical, sch_permit, sch_person, sch_pet, sch_petstore, sch_pharmacy, sch_pharmacyspeciality, sch_photograph, sch_photographaction, sch_physicalactivity,
    sch_physicalactivitycategory, sch_physicalexam, sch_physicaltherapy, sch_physician, sch_physiotherapy, sch_pixiegiven, sch_place, sch_placebocontrolledtrial, sch_placeofworship, sch_planaction, sch_plasticsurgery, sch_play,
    sch_playaction, sch_playground, sch_plumber, sch_podcastepisode, sch_podcastseason, sch_podcastseries, sch_podiatric, sch_policestation, sch_pond, sch_postaladdress, sch_postalcoderangespecification, sch_poster, sch_postoffice,
    sch_potentialactionstatus, sch_pregnancyhealthaspect, sch_preorder, sch_preorderaction, sch_prependaction, sch_presale, sch_preschool, sch_prescriptiononly, sch_presentationdigitaldocument, sch_preventionhealthaspect, sch_preventionindication,
    sch_pricecomponenttypeenumeration, sch_pricespecification, sch_pricetypeenumeration, sch_primarycare, sch_prion, sch_product, sch_productcollection, sch_productgroup, sch_productmodel, sch_productreturnenumeration, sch_productreturnfinitereturnwindow, sch_productreturnnotpermitted,
    sch_productreturnpolicy, sch_productreturnunlimitedwindow, sch_productreturnunspecified, sch_professionalservice, sch_profilepage, sch_prognosishealthaspect, sch_programmemembership, sch_project, sch_pronounceabletext, sch_property,
    sch_propertyvalue, sch_propertyvaluespecification, sch_protozoa, sch_psychiatric, sch_psychologicaltreatment, sch_publicationevent, sch_publicationissue, sch_publicationvolume, sch_publichealth, sch_publicholidays,
    sch_publicswimmingpool, sch_publictoilet, sch_pulmonary,

    sch_qapage, sch_qualitativevalue, sch_quantitativevalue, sch_quantitativevaluedistribution, sch_quantity, sch_question, sch_quiz, sch_quotation, sch_quoteaction,

    sch_radiationtherapy, sch_radiobroadcastservice, sch_radiochannel, sch_radioclip, sch_radioepisode, sch_radiography, sch_radioseason, sch_radioseries, sch_radiostation, sch_randomisedtrial, sch_rating, sch_reactaction, sch_readaction,
    sch_readpermission, sch_realestateagent, sch_realestatelisting, sch_realitybased, sch_rearwheeldriveconfiguration, sch_receiveaction, sch_recipe, sch_recommendation, sch_recommendeddoseschedule, sch_recruiting, sch_recyclingcentre,
    sch_refundtypeenumeration, sch_refurbishedcondition, sch_registeraction, sch_registry, sch_reimbursementcap, sch_rejectaction, sch_relatedtopicshealthaspect, sch_remixalbum, sch_renal, sch_rentaction, sch_rentalcarreservation,
    sch_rentalvehicleusage, sch_repaymentspecification, sch_replaceaction, sch_replyaction, sch_report, sch_reportagenewsarticle, sch_reporteddoseschedule, sch_researchproject, sch_reservation, sch_reservationcancelled,
    sch_reservationconfirmed, sch_reservationhold, sch_reservationpackage, sch_reservationpending, sch_reservationstatustype, sch_reserveaction, sch_reservoir, sch_residence, sch_resort, sch_respiratorytherapy, sch_restaurant,
    sch_restockingfees, sch_restricteddiet, sch_resultsavailable, sch_resultsnotavailable, sch_resumeaction, sch_retail, sch_returnaction, sch_returnfeesenumeration, sch_returnshippingfees, sch_review, sch_reviewaction,
    sch_reviewnewsarticle, sch_rheumatologic, sch_righthanddriving, sch_risksorcomplicationshealthaspect, sch_riverbodyofwater, sch_role, sch_roofingcontractor, sch_room, sch_rsvpaction, sch_rsvpresponsemaybe, sch_rsvpresponseno,
    sch_rsvpresponsetype, sch_rsvpresponseyes, sch_rvpark,

    sch_safetyhealthaspect, sch_saleevent, sch_saleprice, sch_satireorparodycontent, sch_satiricalarticle, sch_saturday, sch_schedule, sch_scheduleaction, sch_scholarlyarticle, sch_school, sch_schooldistrict, sch_screeningevent, sch_screeninghealthaspect, sch_sculpture, sch_seabodyofwater,
    sch_searchaction, sch_searchresultspage, sch_season, sch_seat, sch_seatingmap, sch_seedoctorhealthaspect, sch_seektoaction, sch_selfcarehealthaspect, sch_selfstorage, sch_sellaction, sch_sendaction, sch_series, sch_service, sch_servicechannel,
    sch_shareaction, sch_sheetmusic, sch_shippingdeliverytime, sch_shippingratesettings, sch_shoestore, sch_shoppingcentre, sch_shortstory, sch_sideeffectshealthaspect, sch_singleblindedtrial, sch_singlecentretrial,
    sch_singlefamilyresidence, sch_singleplayer, sch_singlerelease, sch_sitenavigationelement, sch_sizegroupenumeration, sch_sizespecification, sch_sizesystemenumeration, sch_sizesystemimperial, sch_sizesystemmetric,
    sch_skin, sch_skiresort, sch_socialevent, sch_socialmediaposting, sch_softwareapplication, sch_softwaresourcecode, sch_soldout,
    sch_solvemathaction, sch_someproducts, sch_soundtrackalbum, sch_speakablespecification, sch_specialannouncement, sch_speciality, sch_speechpathology, sch_spokenwordalbum, sch_sportinggoodsstore, sch_sportsactivitylocation, sch_sportsclub, sch_srp,
    sch_sportsevent, sch_sportsorganisation, sch_sportsteam, sch_spreadsheetdigitaldocument, sch_stadiumorarena, sch_stagedcontent, sch_stageshealthaspect, sch_state, sch_statisticalpopulation, sch_statusenumeration, sch_steeringpositionvalue, sch_store,
    sch_storecreditrefund, sch_strengthtraining, sch_structuredvalue, sch_studioalbum, sch_stupidtype, sch_subscribeaction, sch_subscription, sch_substance, sch_subwaystation, sch_suite, sch_sunday, sch_superficialanatomy, sch_surgical,
    sch_surgicalprocedure, sch_suspendaction, sch_suspended, sch_symptomshealthaspect, sch_synagogue,

    sch_table, sch_takeaction, sch_tattooparlour, sch_taxi, sch_taxireservation, sch_taxiservice, sch_taxistand, sch_taxivehicleusage, sch_techarticle, sch_televisionchannel, sch_televisionstation, sch_tenniscomplex, sch_terminated,
    sch_text, sch_textdigitaldocument, sch_theatreevent, sch_theatregroup, sch_therapeutic, sch_therapeuticprocedure, sch_thesis, sch_thing, sch_throat, sch_thursday, sch_ticket, sch_tieaction, sch_time, sch_tipaction, sch_tollfree, sch_touristattraction,
    sch_touristdestination, sch_touristinformationcentre, sch_touristtrip, sch_toxicologic, sch_toystore, sch_trackaction, sch_tradeaction, sch_trainreservation, sch_trainstation, sch_traintrip, sch_transferaction, sch_transformedcontent, sch_transitmap,
    sch_travelaction, sch_travelagency, sch_treatmentindication, sch_treatmentshealthaspect, sch_trip, sch_tripleblindedtrial, sch_true, sch_tuesday, sch_tvclip, sch_tvepisode, sch_tvseason, sch_tvseries, sch_typeandquantitynode,
    sch_typeshealthaspect, sch_tyreshop,

    sch_uknonprofittype, sch_uktrust, sch_ultrasound, sch_unemploymentsupport, sch_unincorporatedassociationcharity, sch_unitpricespecification, sch_unofficiallegalvalue, sch_unregisteraction, sch_updateaction, sch_url, sch_urologic,
    sch_usageorschedulehealthaspect, sch_useaction, sch_usedcondition, sch_userblocks, sch_usercheckins, sch_usercomments, sch_userdownloads, sch_userinteraction, sch_userlikes, sch_userpagevisits, sch_userplays, sch_userplusones,
    sch_userreview, sch_usertweets, sch_usnonprofittype,

    sch_vegandiet, sch_vegetariandiet, sch_vehicle, sch_vein, sch_venuemap, sch_vessel, sch_veterinarycare, sch_videogallery, sch_videogame, sch_videogameclip, sch_videogameseries, sch_videoobject, sch_viewaction, sch_vinylformat,
    sch_virtuallocation, sch_virus, sch_visualartsevent, sch_visualartwork, sch_vitalsign, sch_volcano, sch_voteaction,

    sch_wantaction, sch_warrantypromise, sch_warrantyscope, sch_watchaction, sch_waterfall,
    sch_wearablemeasurementtypeenumeration, sch_wearablemeasurementback, sch_wearablemeasurementchestorbust, sch_wearablemeasurementcollar, sch_wearablemeasurementcup, sch_wearablemeasurementheight, sch_wearablemeasurementhips,
    sch_wearablemeasurementinseam, sch_wearablemeasurementlength, sch_wearablemeasurementoutsideleg, sch_wearablemeasurementsleeve, sch_wearablemeasurementwaist, sch_wearablemeasurementwidth,
    sch_wearablesizegroupbig, sch_wearablesizegroupboys, sch_wearablesizegroupenumeration, sch_wearablesizegroupextrashort, sch_wearablesizegroupextratall, sch_wearablesizegroupgirls, sch_wearablesizegrouphusky, sch_wearablesizegroupinfants,
    sch_wearablesizegroupjuniors, sch_wearablesizegroupmaternity, sch_wearablesizegroupmens, sch_wearablesizegroupmisses, sch_wearablesizegrouppetite, sch_wearablesizegroupplus, sch_wearablesizegroupregular, sch_wearablesizegroupshort,
    sch_wearablesizegrouptall, sch_wearablesizegroupwomens,
    sch_wearablesizesystemau, sch_wearablesizesystembr, sch_wearablesizesystemcn, sch_wearablesizesystemcontinental, sch_wearablesizesystemde,
    sch_wearablesizesystemen13402, sch_wearablesizesystemenumeration, sch_wearablesizesystemeurope, sch_wearablesizesystemfr, sch_wearablesizesystemgs1, sch_wearablesizesystemit, sch_wearablesizesystemjp, sch_wearablesizesystemmx,
    sch_wearablesizesystemuk, sch_wearablesizesystemus,
    sch_wearaction, sch_webapi, sch_webapplication, sch_webcontent, sch_webpage, sch_webpageelement, sch_website, sch_wednesday, sch_wholesale,
    sch_wholesalestore, sch_winaction, sch_winery, sch_withdrawn, sch_workbasedprogramme, sch_workersunion, sch_wpadblock, sch_wpfooter, sch_wpheader, sch_wpsidebar, sch_writeaction, sch_writepermission,

    sch_xpathtype, sch_xray,

    sch_zoneboardingpolicy, sch_zoo,

    sch_illegal } e_schema;

typedef enum
{   sp_context,

    sp_about, sp_abridged, sp_abstract, sp_accelerationtime, sp_acceptedanswer, sp_acceptedoffer, sp_acceptedpaymentmethod, sp_acceptoffer, sp_acceptsreservations, sp_accessibilityapi, sp_accessibilitycontrol, sp_accessibilityfeature,
    sp_accessibilityhazard, sp_accessibilitysummary, sp_accesscode, sp_accessmode, sp_accessmodesufficient, sp_accommodationcategory, sp_accommodationfloorplan, sp_accountableperson, sp_accountid, sp_accountminimuminflow,
    sp_accountoverdraftlimit, sp_acquiredfrom, sp_acquirelicensepage, sp_acrisscode, sp_action, sp_actionablefeedbackpolicy, sp_actionaccessibilityrequirement, sp_actionapplication, sp_actionoption, sp_actionplatform, sp_actionstatus,
    sp_activeingredient, sp_activityduration, sp_activityfrequency, sp_actor, sp_additionalname, sp_additionalnumberofguests, sp_additionalproperty, sp_additionaltype, sp_additionalvariable, sp_addon, sp_address, sp_addresscountry,
    sp_addresslocality, sp_addressregion, sp_administrationroute, sp_advancebookingrequirement, sp_adverseoutcome, sp_affectedby, sp_affiliation, sp_aftermedia, sp_agent, sp_aggregaterating, sp_aircraft, sp_album,
    sp_albumproductiontype, sp_albumrelease, sp_albumreleasetype, sp_alcoholwarning, sp_algorithm, sp_alignmenttype, sp_alternatename, sp_alternativeheadline, sp_alumni, sp_alumniof, sp_amenityfeature, sp_amount, sp_amountofthisgood,
    sp_announcementlocation, sp_annualpercentagerate, sp_answercount, sp_antagonist, sp_appearance, sp_applicablelocation, sp_applicantcontact, sp_applicantlocationrequirements, sp_applicationcategory, sp_applicationdeadline,
    sp_applicationstartdate, sp_applicationsubcategory, sp_applicationsuite, sp_appliestodeliverymethod, sp_appliestopaymentmethod, sp_archiveheld, sp_areaserved, sp_arrivalairport, sp_arrivalboatterminal, sp_arrivalbusstop,
    sp_arrivalgate, sp_arrivalplatform, sp_arrivalstation, sp_arrivalterminal, sp_arrivaltime, sp_artedition, sp_arterialbranch, sp_artform, sp_articlebody, sp_articlesection, sp_artist, sp_artmedium, sp_artworksurface, sp_aspect,
    sp_assemblyversion, sp_assess, sp_assesses, sp_associatedanatomy, sp_associatedarticle, sp_associatedmedia, sp_associatedpathophysiology, sp_athlete, sp_attendee, sp_audience, sp_audiencetype, sp_audio, sp_authenticator, sp_author,
    sp_availabedeliverymethod, sp_availability, sp_availabilityends, sp_availabilitystarts, sp_availableatorfrom, sp_availablechannel, sp_availabledeliverymethod, sp_availablefrom, sp_availablein, sp_availablelanguage,
    sp_availablelocation, sp_availableondevice, sp_availableservice, sp_availablestrength, sp_availabletest, sp_availablethrough, sp_award, sp_awayteam,

    sp_bankaccounttype, sp_background, sp_backstory, sp_basesalary, sp_bccrecipient, sp_bed, sp_beforemedia, sp_beneficiarybank, sp_benefitssummaryurl, sp_bestrating, sp_billingaddress, sp_billingduration, sp_billingincrement, sp_billingperiod, sp_billingstart,
    sp_biomechanicalclass, sp_birthdate, sp_birthplace, sp_bitrate, sp_blogpost, sp_bloodsupply, sp_boardinggroup, sp_boardingpolicy, sp_bodylocation, sp_bodytype, sp_bookedition, sp_bookformat, sp_bookingtime, sp_box, sp_branch,
    sp_branchcode, sp_brand, sp_breadcrumb, sp_breastfeedingwarning, sp_broadcastaffiliateof, sp_broadcastchannelid, sp_broadcastdisplayname, sp_broadcaster, sp_broadcastfrequency, sp_broadcastfrequencyvalue, sp_broadcastofevent,
    sp_broadcastservicetier, sp_broadcastsignalmodulation, sp_broadcastsubchannel, sp_broadcasttimezone, sp_broker, sp_browserrequirements, sp_businessdays, sp_businessfunction, sp_busname, sp_busnumber, sp_buyer, sp_byartist, sp_byday,
    sp_bymonth, sp_bymonthday, sp_bymonthweek,

    sp_callsign, sp_calories, sp_candidate, sp_caption, sp_carbohydratecontent, sp_cargovolume, sp_carrierrequirements, sp_cashback, sp_cataloguenumber, sp_category, sp_cause, sp_causeof, sp_ccrecipient, sp_character,
    sp_characterattribute, sp_charactername, sp_cheatcode, sp_checkintime, sp_checkouttime, sp_childmaxage, sp_childminage, sp_children, sp_cholesterolcontent, sp_circle, sp_citation, sp_claimreviewed, sp_clinicalpharamcology,
    sp_clipnumber, sp_closes, sp_coach, sp_code, sp_coderepository, sp_codesampletype, sp_codevalue, sp_codingsystem, sp_colleague, sp_collectionsize, sp_colour, sp_colourist, sp_comment, sp_commentcount, sp_commenttext, sp_commenttime,
    sp_competencyrequired, sp_competitor, sp_composer, sp_comprisedof, sp_conditionsofaccess, sp_confirmationnumber, sp_connectedto, sp_constrainingproperty, sp_contactlesspayment, sp_contactoption, sp_contactpoint, sp_contacttype,
    sp_containedin, sp_containedinplace, sp_containsplace, sp_containsseason, sp_contentlocation, sp_contentrating, sp_contentreferencetime, sp_contentsize, sp_contenttype, sp_contenturl, sp_contraindication, sp_contributor, sp_cookingmethod, sp_cooktime,
    sp_copyrightholder, sp_copyrightnotice, sp_copyrightyear, sp_correction, sp_correctionspolicy, sp_cost, sp_costcategory, sp_costcurrency, sp_costorigin, sp_costperunit, sp_countriesnotsupported, sp_countriessupported , sp_countryoforigin, sp_coursecode,
    sp_coursemode, sp_coursepresequisites, sp_courseworkload, sp_coverageendtime, sp_coveragestarttime, sp_creativeworkstatus, sp_creator, sp_credentialcategory, sp_creditedto, sp_credittext, sp_cssselector, sp_currenciesaccepted, sp_currency,
    sp_currentexchangerate, sp_customer, sp_cutofftime, sp_cvdcollectiondate, sp_cvdfacilitycounty, sp_cvdfacilityid, sp_cvdnumbeds, sp_cvdnumbedsocc, sp_cvdnumc19died, sp_cvdnumc19hopats, sp_cvdnumc19hosppats, sp_cvdnumc19mechventpats,
    sp_cvdnumc19ofmechventpats, sp_cvdnumc19overflowpats, sp_cvdnumicubeds, sp_cvdnumicubedsocc, sp_cvdnumtotbeds, sp_cvdnumvent,

    sp_cvdnumventuse, sp_datafeedelement, sp_dataset, sp_datasettimeinterval, sp_datecreated, sp_datedeleted, sp_dateissued, sp_dateline, sp_datemodified, sp_dateposted, sp_datepublished, sp_dateread, sp_datereceived, sp_datesent,
    sp_datevehiclefirstregistered, sp_dayofweek, sp_deathdate, sp_deathplace, sp_defaultvalue, sp_deliveryaddress, sp_deliveryleadtime, sp_deliverymethod, sp_deliverystatus, sp_deliverytime, sp_department, sp_departureairport,
    sp_departureboatterminal, sp_departurebusstop, sp_departuregate, sp_departureplatform, sp_departurestation, sp_departureterminal, sp_departuretime, sp_dependencies, sp_depth, sp_description, sp_diagnosis, sp_diagram, sp_diet,
    sp_dietfeatures, sp_differentialdiagnosis, sp_director, sp_disambiguatingdescription, sp_discount, sp_discountcode, sp_discountcurrency, sp_discusses, sp_discussionurl, sp_diseasepreventioninfo, sp_diseasespreadstatistics,
    sp_dissolutiondate, sp_distance, sp_distinguishingsign, sp_distribution, sp_diversitypolicy, sp_diversitystaffingreport, sp_documentation, sp_doesnotship, sp_domainincludes, sp_domiciledmortgage, sp_doortime, sp_dosageform,
    sp_doseschedule, sp_doseunit, sp_dosevalue, sp_downloadurl, sp_downpayment, sp_downvotecount, sp_drainsto, sp_drivewheelconfiguration, sp_dropofflocation, sp_dropofftime, sp_drug, sp_drugclass, sp_drugunit, sp_duns,
    sp_duplicatetherapy, sp_duration, sp_durationofwarranty, sp_duringmedia,

    sp_earlyprepaymentpenalty, sp_editeidr, sp_editor, sp_educationalalignment, sp_educationalcredentialawarded, sp_educationalframework, sp_educationallevel, sp_educationalprogrammode, sp_educationalrole, sp_educationaluse,
    sp_educationcredentialawarded, sp_educationrequirements, sp_eduquestiontype, sp_elevation, sp_eligibilecustomertype, sp_eligibilitytoworkrequirement, sp_eligiblecustomertype, sp_eligibleduration, sp_eligiblequantity, sp_eligibleregion,
    sp_eligibletransactionvolume, sp_email, sp_embedurl, sp_emmissionsco2, sp_employee, sp_employeroverview, sp_employmenttype, sp_employmentunit, sp_encodescreativework, sp_encoding, sp_encodingformat, sp_encodingtype, sp_enddate,
    sp_endoffset, sp_endorsee, sp_endorsers, sp_endtime, sp_energyefficiencyscalemax, sp_energyefficiencyscalemin,
    sp_enginedisplacement, sp_enginepower, sp_enginetype, sp_entertainmentbusiness, sp_epidemiology, sp_episode, sp_episodenumber, sp_equal, sp_error, sp_estimatedcost,
    sp_estimatedflightduration, sp_estimatedsalary, sp_estimatesriskof, sp_ethicspolicy, sp_event, sp_eventattendancemode, sp_eventschedule, sp_eventstatus, sp_evidencelevel, sp_evidenceorigin, sp_exampleofwork, sp_exceptdate,
    sp_exchangeratespread, sp_executablelibraryname, sp_exercisecourse, sp_exerciseplan, sp_exerciserelateddiet, sp_exercisetype, sp_exifdata, sp_expectedarrivalfrom, sp_expectedarrivaluntil, sp_expectedprognosis, sp_expectsacceptanceof,
    sp_experiencerequirements, sp_experienceinplaceofeducation, sp_expires, sp_exportconsiderations,

    sp_familyname, sp_fatcontent, sp_faxnumber, sp_featurelist, sp_feesandcommissionsspecification, sp_fibrecontent, sp_fileformat, sp_filesize, sp_financialaideligible, sp_firstappearance, sp_firstperformance, sp_flightdistance,
    sp_flightnumber, sp_floorlevel, sp_floorlimit, sp_floorsize, sp_followee, sp_follows, sp_followup, sp_foodestablishment, sp_foodevent, sp_foodwarning, sp_founder, sp_foundingdate, sp_foundinglocation, sp_freeshippingthreshold,
    sp_frequency, sp_fromlocation, sp_fuelcapacity, sp_fuelconsumption, sp_fuelefficiency, sp_fueltype, sp_funcionalclass, sp_function, sp_fundeditem, sp_funder,

    sp_game, sp_gameitem, sp_gamelocation, sp_gameplatform, sp_gameserver, sp_gametip, sp_gender, sp_genre, sp_geo, sp_geocontains, sp_geocoveredby, sp_geocovers, sp_geocrosses, sp_geodisjoint, sp_geoequals, sp_geographicarea,
    sp_geointersects, sp_geomidpoint, sp_geooverlaps, sp_georadius, sp_geotouches, sp_geowithin, sp_gettingtestedinfo, sp_givenname, sp_globallocationnumber, sp_governmentbenefitsinfo, sp_graceperiod, sp_grantee, sp_greater,
    sp_greaterorequal, sp_gtin, sp_gtin12, sp_gtin13, sp_gtin14, sp_gtin8, sp_guideline, sp_guidelinedate, sp_guidelinesubject,

    sp_handlingtime, sp_hasbroadcastchannel, sp_hascategorycode, sp_hascourse, sp_hascourseinstance, sp_hascredential, sp_hasdefinedterm, sp_hasdeliverymethod, sp_hasdigitaldocumentpermission, sp_hasdrivethroughservice,
    sp_hasenergyconsumptiondetails, sp_hasenergyefficiencycategory, sp_hashealthaspect, sp_hasmap, sp_hasmeasurement, sp_hasmenu,
    sp_hasmenuitem, sp_hasmenusection, sp_hasmerchantreturnpolicy, sp_hasoccupation, sp_hasoffercatalogue, sp_haspart, sp_haspos, sp_hasproductreturnpolicy, sp_hasvariant, sp_headline, sp_healthcarereportingdata, sp_healthcondition,
    sp_healthplancoinsuranceoption, sp_healthplancoinsurancerate, sp_healthplancopay, sp_healthplancopayoption, sp_healthplancostsharing, sp_healthplandrugoption, sp_healthplandrugtier, sp_healthplanid, sp_healthplanmarketingurl,
    sp_healthplannetworkid, sp_healthplannetworktier, sp_healthplanpharmacycategory, sp_height, sp_highprice, sp_hiringorganization, sp_holdingarchive, sp_homelocation, sp_hometeam, sp_honourificprefix, sp_honourificsuffix,
    sp_hospitalaffiliation, sp_hostingorganisation, sp_hoursavailable, sp_howperformed, sp_httpmethod,

    sp_iatacode, sp_identifier, sp_identifyingexam, sp_identifyingtest, sp_illustrator, sp_image, sp_imagingtechnique, sp_inalbum, sp_inbroadcastlineup, sp_incentivecompensation, sp_includedcomposition, sp_includeddatacatalog,
    sp_includedinhealthinsuranceplan, sp_includedriskfactor, sp_includesattraction, sp_includeshealthplanformulary, sp_includeshealthplannetwork, sp_includesobject, sp_incodeset, sp_increasesriskof, sp_indefinedtermset, sp_indication,
    sp_industry, sp_ineligibleregion, sp_infectiousagent, sp_infectiousagentclass, sp_inker, sp_inlanguage, sp_inplaylist, sp_inproductgroupwithid, sp_insertion, sp_installurl, sp_instorereturnsoffered, sp_instructor, sp_instrument,
    sp_insupportof, sp_intensity, sp_interactingdrug, sp_interactionservice, sp_interactionstatistic, sp_interactiontype, sp_interactivitytype, sp_interestrate, sp_inventorylevel, sp_inverseof, sp_isacceptingnewpatients,
    sp_isaccessibleforfree, sp_isaccessoryorsparepartfor, sp_isavailablegenerally, sp_isbasedon, sp_isbasedonurl, sp_isbn, sp_isconsumablefor, sp_isfamilyfriendly, sp_isgift, sp_isicv4, sp_islivebroadcast, sp_ispartof,
    sp_isplanforapartment, sp_isproprietary, sp_isrccode, sp_isrelatedto, sp_isresizable, sp_issimilarto, sp_issn, sp_issuedby, sp_issuedthrough, sp_issuenumber, sp_isunlabelledfallback, sp_isvariantof, sp_iswccode, sp_item,
    sp_itemcondition, sp_itemlistelement, sp_itemlistorder, sp_itemlocation, sp_itemoffered, sp_itemreviewed, sp_itemshipped, sp_itinerary,

    sp_jobbenefits, sp_jobimmediatestart, sp_joblocation, sp_joblocationtype, sp_jobstartdate, sp_jobtitle, sp_jurisdiction,

    sp_keywords, sp_knownvehicledamages, sp_knows, sp_knowsabout, sp_knowslanguage,

    sp_labeldetails, sp_landlord, sp_lastreviewed, sp_latitude, sp_layoutimage, sp_learningresourcetype, sp_leaselength, sp_legalname, sp_legalstatus, sp_legislationapplies, sp_legislationchanges, sp_legislationconsolidates, sp_legislationdate,
    sp_legislationdateversion, sp_legislationidentifier, sp_legislationjurisdiction, sp_legislationlegalforce, sp_legislationlegalvalue, sp_legislationpassedby, sp_legislationresponsible, sp_legislationtransposes, sp_legislationtype,
    sp_leicode, sp_lender, sp_lesser, sp_lesserorequal, sp_letterer, sp_license, sp_line, sp_linkrelationship, sp_liveblogupdate, sp_loanmortgagamandateamount, sp_loanpaymentamount, sp_loanpaymentfrequency, sp_loanrepaymentform,
    sp_loanterm, sp_loantype, sp_location, sp_locationcreated, sp_lodgingunitdescription, sp_lodgingunittype, sp_logo, sp_longitude, sp_loser, sp_lowprice, sp_lyricist, sp_lyrics,

    sp_maincontentofpage, sp_mainentity, sp_mainentityofpage, sp_maintainer, sp_makesoffer, sp_manufacturer, sp_maptype, sp_marginoferror, sp_masthead, sp_material, sp_materialextent, sp_mathexpression, sp_maximumattendeecapacity, sp_maximumenrollment,
    sp_maximumintake, sp_maximumphysicalattendeecapacity, sp_maximumvirtualattendeecapacity, sp_maxprice, sp_maxvalue, sp_mealservice, sp_measuredproperty, sp_measuredvalue, sp_measurementtechnique, sp_mechanismofaction,
    sp_mediaauthenticitycategory, sp_median, sp_medicalaudience, sp_medicalspeciality, sp_medicinesystem, sp_meetsemissionstandard, sp_member, sp_memberof, sp_membershipnumber, sp_membershippointsearned, sp_memoryrequirements,
    sp_mentions, sp_menu, sp_menuaddon, sp_merchantreturndays, sp_merchantreturnlink, sp_messageattachment, sp_mileagefromodometer, sp_minimummonthlyrepaymentamount, sp_minimumpaymentdue, sp_minprice, sp_minvalue,
    sp_missioncoverageprioritiespolicy, sp_model, sp_modeldate, sp_modifiedtime, sp_monthsofexperience, sp_mpn, sp_multiplevalues, sp_muscleaction, sp_musicalkey, sp_musicarrangement, sp_musicby, sp_musiccompositionform, sp_musicreleaseformat,

    sp_naics, sp_name, sp_nationality, sp_naturalprogression, sp_nerve, sp_nervemotor, sp_networth, sp_newupdatesandguidelines, sp_nextitem, sp_nobylinespolicy, sp_nonequal, sp_nonprofitstatus, sp_nonpropriatryname,
    sp_nonproprietaryname, sp_normalrange, sp_nsn, sp_numadults, sp_numberedposition, sp_numberofaccommodationunits, sp_numberofairbags, sp_numberofavailableaccommodationunits, sp_numberofaxles, sp_numberofbathroomstotal,
    sp_numberofbedrooms, sp_numberofbeds, sp_numberofcredits, sp_numberofdoors, sp_numberofemployees, sp_numberofepisodes, sp_numberofforwardgears, sp_numberoffullbathrooms, sp_numberofitems, sp_numberofloanpayments, sp_numberofpages,
    sp_numberofpartialbathrooms, sp_numberofplayers, sp_numberofpreviousowners, sp_numberofrooms, sp_numberofseasons, sp_numchildren, sp_numconstraints, sp_numtracks, sp_nutrition,

    sp_object, sp_observationdate, sp_observednode, sp_ocaocode, sp_occupancy, sp_occupationalcategory, sp_occupationalcredentialawarded, sp_occupationlocation, sp_offercount, sp_offeredby, sp_offers, sp_offersprescriptionbymail,
    sp_openinghours, sp_openinghoursspecification, sp_opens, sp_operatingsystem, sp_opponent, sp_orderdate, sp_orderdelivery, sp_ordereditem, sp_orderitemnumber, sp_orderitemstatus, sp_ordernumber, sp_orderquantity, sp_orderstatus,
    sp_organiser, sp_origin, sp_originaddress, sp_originatesfrom, sp_outcome, sp_overdosage, sp_overview, sp_ownedfrom, sp_ownedthrough, sp_ownershipfundinginfo, sp_owns,

    sp_pageend, sp_pagestart, sp_pagination, sp_parent, sp_parentitem, sp_parentorganisation, sp_parentservice, sp_participant, sp_partofepisode, sp_partofinvoice, sp_partoforder, sp_partofseason, sp_partofseries, sp_partofsystem,
    sp_partoftrip, sp_partysize, sp_passengerprioritystatus, sp_passengersequencenumber, sp_pathophysiology, sp_pattern, sp_payload, sp_paymentaccepted, sp_paymentdue, sp_paymentduedate, sp_paymentmethod, sp_paymentmethodid,
    sp_paymentstatus, sp_paymenturl, sp_penciler, sp_percentile10, sp_percentile25, sp_percentile75, sp_percentile90, sp_performer, sp_performerin, sp_performtime, sp_permissions, sp_permissiontype, sp_permitaudience, sp_permittedusage,
    sp_petsallowed, sp_phase, sp_phonetictext, sp_photo, sp_physicalrequirement, sp_physiologicalbenefits, sp_pickuplocation, sp_pickuptime, sp_playersonline, sp_playertype, sp_playmode, sp_polygon, sp_population, sp_populationtype,
    sp_position, sp_possiblecomplication, sp_possibletreatment, sp_postalcode, sp_postalcodebegin, sp_postalcodeend, sp_postalcodeprefix, sp_postalcoderange, sp_postofficeboxnumber, sp_postop, sp_potentialaction, sp_predecessorof,
    sp_pregnancycategory, sp_pregnancywarning, sp_preop, sp_preparation, sp_preptime, sp_prescribinginfo, sp_prescriptionstatus, sp_previousitem, sp_previousstartdate, sp_price, sp_pricecomponent, sp_pricecomponenttype, sp_pricecurrency, sp_pricerange,
    sp_pricespecification, sp_pricetype, sp_pricevaliduntil, sp_primaryimageofpage, sp_primaryprevention, sp_printcolumn, sp_printedition, sp_printpage, sp_printsection, sp_procedure, sp_proceduretype, sp_processingtime,
    sp_processorrequirements, sp_producer, sp_productgroupid, sp_productid, sp_productioncompany, sp_productiondate, sp_productsupported, sp_proficiencylevel, sp_programmemembershipused, sp_programmename, sp_programminglanguage,
    sp_programmingmodel, sp_programprequisites, sp_programtype, sp_propertyid, sp_propriatryname, sp_proprietaryname, sp_proteincontent, sp_provider, sp_providermobility, sp_providesbroadcastservice, sp_providesservice, sp_publicaccess,
    sp_publication, sp_publicationtype, sp_publictransportclosuresinfo, sp_publishedby, sp_publishedon, sp_publisher, sp_publisherimprint, sp_publishingprinciples, sp_purchasedate, sp_purpose,

    sp_qualifications, sp_quarantineguidelines, sp_query, sp_quest, sp_question,

    sp_rangeincludes, sp_ratingcount, sp_ratingexplanation, sp_ratingvalue, sp_readby, sp_readonlyvalue, sp_realestateagent, sp_recipe, sp_recipecategory, sp_recipecuisine, sp_recipeingredient, sp_recipeinstructions, sp_recipeyield,
    sp_recipient, sp_recognisedby, sp_recognisingauthority, sp_recommendationstrength, sp_recommendedintake, sp_recordedas, sp_recordedat, sp_recordedin, sp_recordingof, sp_recordlabel, sp_recourseloan, sp_referencequantity,
    sp_referencesorder, sp_refundtype, sp_regiondrained, sp_regionsallowed, sp_relatedanatomy, sp_relatedcondition, sp_relateddrug, sp_relatedlink, sp_relatedstructure, sp_relatedtherapy, sp_relatedto, sp_releasedate, sp_releasedevent,
    sp_releasenotes, sp_releaseof, sp_relevantoccupation, sp_relevantspeciality, sp_remainingattendeecapacity, sp_renegotiableloan, sp_repeatcount, sp_repeatfrequency, sp_repetitions, sp_replacee, sp_replacer, sp_replytourl,
    sp_reportnumber, sp_representativeofpage, sp_requiredcollateral, sp_requiredgender, sp_requiredmaxage, sp_requiredminage, sp_requiredquantity, sp_requiressubscription, sp_reservationfor, sp_reservationid, sp_reservationstatus,
    sp_reservedticket, sp_responsibilities, sp_restperiods, sp_result, sp_resultcomment, sp_resultreview, sp_returnfees, sp_returnpolicycategory, sp_review, sp_reviewaspect, sp_reviewbody, sp_reviewcount, sp_reviewedby, sp_reviewrating,
    sp_riskfactor, sp_risks, sp_rolename, sp_roofload, sp_rsvpresponse, sp_runsto, sp_runtimeplatform, sp_rxcui,

    sp_safetyconsideration, sp_salarycurrency, sp_salaryuponcompletion, sp_sameas, sp_saturatedfatcontent, sp_scheduledpaymentdate, sp_scheduledtime, sp_scheduletimezone, sp_schemaversion, sp_schoolclosuresinfo, sp_screencount,
    sp_screenshot, sp_sddatepublished, sp_sdlicense, sp_sdpublisher, sp_seasonnumber, sp_seatingcapacity, sp_seatingtype, sp_seatnumber, sp_seatrow, sp_seatsection, sp_secondaryprevention, sp_securityclearancerequirement,
    sp_securityscreening, sp_seeks, sp_seller, sp_sender, sp_sensoryclearancerequirement, sp_sensoryunit, sp_serialnumber, sp_seriousadverseoutcome, sp_serverstatus, sp_servescuisine, sp_servicearea, sp_servicelocation,
    sp_serviceoperator, sp_serviceoutput, sp_servicephone, sp_servicepostaladdress, sp_servicesmsnumber, sp_servicetype, sp_serviceurl, sp_servingsize, sp_sharedcontent, sp_shippingdestination, sp_shippinglabel, sp_shippingrate,
    sp_shippingsettingslink, sp_sibling, sp_signdetected, sp_significance, sp_significantlink, sp_signorsymptom, sp_size, sp_sizegroup, sp_sizesystem, sp_skills, sp_sku, sp_slogan, sp_smokingallowed, sp_sodiumcontent, sp_softwareaddon, sp_softwarehelp,
    sp_softwarerequirements, sp_softwareversion, sp_source, sp_sourcedfrom, sp_sourceorganisation, sp_spatial, sp_spatialcoverage, sp_speakable, sp_specialcommitments, sp_speciality, sp_specialopeninghoursspecification,
    sp_speechtotextmarkup, sp_speed, sp_spokenbycharacter, sp_sponsor, sp_sport, sp_sportsactivitylocation, sp_sportsevent, sp_sportsteam, sp_spouse, sp_stage, sp_stageasnumber, sp_starrating, sp_startdate, sp_startoffset,
    sp_starttime, sp_status, sp_steeringposition, sp_step, sp_steps, sp_stepvalue, sp_storagerequirements, sp_streetaddress, sp_strengthunit, sp_strengthvalue, sp_structuralclass, sp_study, sp_studydesign, sp_studylocation, sp_studysubject,
    sp_stupidproperty, sp_subevent, sp_subjectof, sp_suborganisation, sp_subreservation, sp_substagesuffix, sp_substructure, sp_subtitlelanguage, sp_subtrip, sp_subtype, sp_successorof, sp_sugarcontent, sp_suggestedage, sp_suggestedanswer,
    sp_suggestedgender, sp_suggestedmaxage, sp_suggestedmeasurement, sp_suggestedminage, sp_suitablefordiet, sp_superevent, sp_supersededby, sp_supply, sp_supplyto, sp_supportingdata, sp_suspersededby,

    sp_target, sp_targetcollection, sp_targetdescription, sp_targetname, sp_targetplatform, sp_targetpopulation, sp_targeturl, sp_taxid, sp_teaches, sp_telephone, sp_temporal, sp_temporalcoverage, sp_termcode, sp_termduration,
    sp_termsofservice, sp_termsperyear, sp_text, sp_textvalue, sp_thumbnail, sp_thumbnailurl, sp_tickersymbol, sp_ticketedseat, sp_ticketnumber, sp_tickettoken, sp_timeofday, sp_timerequired, sp_timetocomplete, sp_tissuesample,
    sp_title, sp_titleeidr, sp_toccontinuation, sp_tocentry, sp_tolocation, sp_tongueweight, sp_tool, sp_torecipient, sp_torque, sp_totaljobopenings, sp_totalpaymentdue, sp_totalprice, sp_totaltime, sp_tourbookingpage, sp_touristtype, sp_track, sp_trackingnumber,
    sp_trackingurl, sp_trailer, sp_trailerweight, sp_trainingsalary, sp_trainname, sp_trainnumber, sp_transcript, sp_transfatcontent, sp_transittime, sp_transittimelabel, sp_translationofwork, sp_translator, sp_transmissionmethod,
    sp_travelbans, sp_trialdesign, sp_tributary, sp_typeofbed, sp_typeofgood, sp_typicalagerange, sp_typicalcreditsperterm, sp_typicaltest,

    sp_undername, sp_unitcode, sp_unittext, sp_unnamedsourcespolicy, sp_unsaturatedfatcontent, sp_uploaddate, sp_upvotecount, sp_url, sp_urltemplate, sp_usageinfo, sp_usedtodiagnose, sp_userinteractioncount, sp_usesdevice,
    sp_useshealthplanidstandard, sp_utterances,

    sp_validfor, sp_validfrom, sp_validin, sp_validthrough, sp_validuntil, sp_value, sp_valueaddedtaxincluded, sp_valuemaxlength, sp_valueminlength, sp_valuename, sp_valuepattern, sp_valuereference, sp_valuerequired,
    sp_variablemeasured, sp_variablesmeasured, sp_variantcover, sp_variesby, sp_vatid, sp_vehicleconfiguration, sp_vehicleengine, sp_vehicleidentificationnumber, sp_vehicleinteriorcolour, sp_vehicleinteriortype, sp_vehiclemodeldate,
    sp_vehicleseatingcapacity, sp_vehiclespecialusage, sp_vehicletransmission, sp_verificationfactcheckingpolicy, sp_version, sp_video, sp_videoformat, sp_videoframesize, sp_videoquality, sp_volumenumber,

    sp_warning, sp_warranty, sp_warrantyscope, sp_webcheckintime, sp_webfeed, sp_weight, sp_weighttotal, sp_wheelbase, sp_width, sp_winner, sp_wordcount, sp_workexample, sp_workfeatured, sp_workhours, sp_workload, sp_worklocation,
    sp_workperformed, sp_workpresented, sp_worksfor, sp_worktranslation, sp_worstrating,

    sp_xpath,

    sp_yearbuilt, sp_yearlyrevenue, sp_yearsinoperation, sp_yield,

    sp_illegal } e_schema_property;

#define SCHEMES pt_rfc3986, pt_rfc3986_ignore, pt_geo, pt_local, pt_news, pt_tel, pt_urn
typedef enum { SCHEMES } e_scheme;

typedef enum { s_auto, s_no, s_yes } e_scrolling;
typedef enum { st_normal, st_multiset } e_settype;
typedef enum { es_undefined, es_catastrophic, es_error, es_warning, es_info, es_comment, es_debug, es_detail, es_splurge, es_all, es_silence } e_severity;
const e_severity last_severity = es_all;

typedef enum {  doc_unknown, doc_context, doc_html, doc_public, doc_system, doc_math, doc_rdf, doc_svg, doc_xhtml,
                doc_math1, doc_math2, doc_math3, doc_math4,
                doc_rdfa_1_0, doc_rdfa_1_1,
                doc_svg1, doc_svg11, doc_svg2,
                doc_jan05, doc_html5,
                doc_xhtml2,
                doc_xhtml11,
                doc_xhtml10_basic, doc_xhtml10_strict, doc_xhtml10_loose, doc_xhtml10_frameset,
                doc_xhtml10_strict_superseded, doc_xhtml10_loose_superseded, doc_xhtml10_frameset_superseded,
                doc_html401_strict, doc_html401_loose, doc_html401_frameset,
                doc_html401_strict_superseded, doc_html401_loose_superseded, doc_html401_frameset_superseded,
                doc_html400_strict, doc_html400_loose, doc_html400_frameset,
                doc_latin, doc_special, doc_symbols,
                doc_html32, doc_html30,
                doc_html20, doc_html20_strict, doc_html20_int, doc_html21, doc_html21_strict, doc_html22, doc_html1, doc_html_tags,
                doc_htmlplus, doc_sqopen, doc_sqclose,
                doc_compound } e_sgml;
const e_sgml last_sgml = doc_compound;

typedef enum { sh_circle, sh_default, sh_poly, sh_rect } e_shape4;
typedef enum { s7_circ, s7_default, s7_poly, s7_rect } e_shape7;
typedef enum { rcp_circle, rcp_poly, rcp_rect } e_shape_rcp;
typedef enum { sr_auto, sr_optimisespeed, sr_crispedges, sr_geometricprecision, sr_inherit } e_shaperendering;
typedef enum { sh_embed, sh_replace } e_show;
typedef enum { si_left, si_right, si_leftoverlap, si_rightoverlap } e_side;
typedef enum { siz_normal, siz_medium, siz_large, siz_huge } e_size3;
typedef enum { smei_start, smei_middle, smei_end, smei_inherit } e_smei;
typedef enum { sp_block, sp_horz, sp_vert } e_spacer;
typedef enum { spa_auto, spa_exact } e_spacing;
typedef enum { sm_reflect, sm_repeat, sm_stick } e_spread_method;
typedef enum { ssi_comment, ssi_config, ssi_echo, ssi_elif, ssi_else, ssi_endif, ssi_exec, ssi_flastmod, ssi_fsize, ssi_if, ssi_include, ssi_printenv, ssi_set } e_ssi;
typedef enum { ssi_comparison_and, ssi_comparison_eq, ssi_comparison_ge, ssi_comparison_gt, ssi_comparison_le, ssi_comparison_lt, ssi_comparison_ne, ssi_comparison_or } e_ssi_comparison;
typedef enum { ssi_config_echomsg, ssi_config_errmsg, ssi_config_sizefmt, ssi_config_timefmt } e_ssi_config;
typedef enum { ssi_echo_decoding, ssi_echo_encoding, ssi_echo_var } e_ssi_echo;
typedef enum { ssi_encoding_base64, ssi_encoding_none, ssi_encoding_entity, ssi_encoding_url, ssi_encoding_urlencoded } e_ssi_encoding;
typedef enum { ssi_DATE_GMT, ssi_DATE_LOCAL, ssi_DOCUMENT_ARGS, ssi_DOCUMENT_NAME, ssi_DOCUMENT_PATH_INFO, ssi_DOCUMENT_URI, ssi_LAST_MODIFIED, ssi_QUERY_STRING_UNESCAPED, ssi_USER_NAME } e_ssi_env;
typedef enum { ssi_f_file, ssi_f_virtual } e_ssi_f;
typedef enum { ssi_include_file, ssi_include_onerror, ssi_include_virtual } e_ssi_include;
typedef enum { stt_stitch, stt_nostitch } e_stitchtiles;
typedef enum { sov_visible, sov_hidden, sov_scroll, sov_auto, sov_inherit } e_svg_overflow;
typedef enum { ssi_set_decoding, ssi_set_encoding, ssi_set_value, ssi_set_var } e_ssi_set;
typedef enum { ssi_size_abbrev, ssi_size_bytes } e_ssi_sizefmt;
typedef enum { s_unset, s_invalid, s_empty, s_good } e_status;
typedef enum { sa_none, sa_xmin_ymin, sa_xmid_ymin, sa_xmax_ymin, sa_xmin_ymid, sa_xmid_ymid, sa_xmax_ymid, sa_xmin_ymax, sa_xmid_ymax, sa_xmax_ymax } e_svg_align;
typedef enum { sbp_basic, sbp_full, sbp_none, sbp_tiny } e_svg_baseprofile;
typedef enum { sd_ltr, sd_rtl, sd_inherit } e_svg_direction;
typedef enum {
    sf_org_w3c_svg, sf_org_w3c_svg_static, sf_org_w3c_svg_animation, sf_org_w3c_svg_dynamic, sf_org_w3c_svg_all,
    sf_org_w3c_dom_svg, sf_org_w3c_dom_svg_static, sf_org_w3c_dom_svg_animation, sf_org_w3c_dom_svg_dynamic, sf_org_w3c_dom_svg_all,
    sf_svg, sf_svgdom, sf_svgstatic, sf_svgdomstatic, sf_svganimation, sf_svgdomanimation, sf_svgdynamic, sf_svgdomdynamic, sf_coreattribute, sf_structure,
    sf_basicstructure, sf_containerattribute, sf_conditionalprocessing, sf_image, sf_style, sf_viewportattribute, sf_shape, sf_text, sf_basictext, sf_paintattribute, sf_basicpaintattribute,
    sf_opacityattribute, sf_graphicsattribute, sf_basicgraphicsattribute, sf_marker, sf_colourprofile, sf_gradient, sf_pattern, sf_clip, sf_basicclip, sf_mask, sf_filter, sf_basicfilter,
    sf_documenteventsattribute, sf_graphicaleventsattribute, sf_animationeventsattribute, sf_cursor, sf_hyperlinking, sf_xlinkattribute, sf_externalresourcesrequired, sf_view, sf_script,
    sf_animation, sf_font, sf_basicfont, sf_extensibility, sf_scripting
 } e_svg_feature;
typedef enum { sfs_normal, sfs_italic, sfs_oblique, sfs_inherit } e_svg_fontstyle;
typedef enum { sme_align, sme_stretch } e_svg_method;
typedef enum { sm_darken, sm_lighten, sm_multiple, sm_normal, sm_screen } e_svg_mode;
typedef enum { sbo_all, abo_forwardonly } e_svg_playbackorder;
typedef enum { stb_onload, stb_onstart } e_svg_timelinebegin;
typedef enum { st_gamma, st_identity, st_linear, st_table } e_svg_type;
typedef enum { su_object_bbox, su_userspace } e_svg_units;
typedef enum { fst_normal, fst_wider, fst_narrower, fst_ultracondensed, fst_extracondensed, fst_condensed, fst_semicondensed, fst_semiexpanded, fst_expanded, fst_extraexpanded, fst_ultraexpanded, fst_inherit } e_svg_fontstretch;
typedef enum { fff_normal, fff_ultracondensed, fff_extracondensed, fff_condensed, fff_semicondensed, fff_semiexpanded, fff_expanded, fff_extraexpanded, fff_ultraexpanded } e_svg_fontstretch_ff;
typedef enum { fv_normal, fv_smallcaps, fv_inherit } e_svg_fontvariant;
typedef enum { fvf_normal, fvf_smallcaps } e_svg_fontvariant_ff;
typedef enum { tsz_discrete, tsz_gamma, tsz_identity, tsz_linear, tsz_table } e_svg_type_11;
typedef enum { sv_none, sv_1_0, sv_1_1, sv_1_2_tiny, sv_1_2_full, sv_2_0 } e_svg_version;
typedef enum { fsw_normal, fsw_bold, fsw_bolder, fsw_lighter, fsw_100, fsw_200, fsw_300, fsw_400, fsw_500, fsw_600, fsw_700, fsw_800, fsw_900, fsw_inherit } e_svg_fontweight;
typedef enum { fsf_normal, fsf_bold, fsf_100, fsf_200, fsf_300, fsf_400, fsf_500, fsf_600, fsf_700, fsf_800, fsf_900 } e_svg_fontweight_ff;
typedef enum { fr_void, fr_above, fr_below, fr_hsides, fr_lhs, fr_rhs, fr_vsides, fr_box, fr_border } e_tableframe;
typedef enum { tb_bottom, tb_top } e_tbalign;
typedef enum { sc_row, sc_col, sc_rowgroup, sc_colgroup } e_tdscope;
typedef enum { eto_above, eto_below, eto_twosided } e_tendstotype;
typedef enum { td_none, td_underline, td_overline, td_linethrough, td_blink, td_inherit } e_textdecoration;
typedef enum { tr_auto, tr_optimisespeed, tr_optimiselegibility, tr_geometricprecision, tr_inherit } e_textrendering;
typedef enum { ac_false, ac_mixed, ac_true, ac_undefined  } e_tfmu;
typedef enum { tfa_auto, tfa_false, tfa_true } e_tfa;
typedef enum { tfu_false, tfu_true, tfu_undefined } e_tfu;
typedef enum { ta_translate, ta_scale, ta_rotate, ta_skewx, ta_skewy } e_transform_anim;
typedef enum { tr_nowt, tr_matrix, tr_translate, tr_scale, tr_rotate, tr_skewx, tr_skewy } e_transform_fn;
typedef enum { tu_fractal_noise, tu_turbulence } e_turbulence_type;

typedef enum {
    t_unknown,

    t_1, t_10, t_1_to_7, t_1_more, t_1_more_i, t_2pt,
    t_absolute_url, t_accept, t_accumulate, t_action, t_actiontype, t_actiontype2, t_actuate, t_additive, t_align, t_align2070, t_align3, t_aligndec, t_alignfig,
        t_alignmentbaseline, t_alignplus, t_angle, t_angle_ai, t_angle_i, t_arabicform, t_aria_autocomplete, t_aria_invalidity, t_aria_live, t_aria_pressed,
        t_aria_sort, t_as, t_attributename, t_attributetype, t_autocapitalise, t_autocomplete, t_autocompletes, t_autocompletevaried,
    t_background, t_base, t_baselineshift, t_beginvaluelist, t_behaviour, t_border, t_bool, t_bools, t_button,
    t_cache, t_cachekey, t_caches, t_calcmode, t_captionalign, t_capture, t_channel_selector, t_char, t_charset, t_charsets, t_charspacing, t_citype, t_class,
        t_clear, t_clear30, t_clip, t_closure, t_colour, t_colour_ci, t_colour_i,t_colourinterpolation, t_colourrendering, t_colour_v, t_command, t_compact,
        t_composite_operator, t_conditional, t_content_encoding, t_content_encodings, t_content_type, t_context_menu, t_controlslist, t_cookie, t_cookieid,
        t_cookies, t_coordinatesystem, t_coords, t_corp, t_cors, t_cntype, t_crossout, t_css, t_csp, t_csp_ancestor, t_csp_directive, t_csp_keyword, t_csp_sauce,
        t_csp_source, t_curie, t_curie_safe, t_curies, t_currency, t_cursor, t_cursor_f,
    t_d, t_dashes, t_data, t_dataformatas, t_datetime, t_datetime_absolute, t_datetime_local, t_datetime_4, t_datetime_5, t_decalign, t_decoding,
        t_defaultaction, t_depth, t_dingbat, t_dir, t_direction, t_display, t_dominantbaseline, t_dosh, t_dsc, t_dsctv, t_dur, t_dur_repeat, t_duration,
        t_duration_media,
    t_edgemode, t_edit, t_effect, t_email, t_emails, t_enablebackground, t_enctype, t_end, t_endvaluelist, t_enterkeyhint, t_existential, t_expected,
    t_featurepolicy, t_figalign, t_filename, t_fill, t_fillanim, t_fillrule, t_filter_in, t_filter_res, t_fixedcolour, t_fixedpoint, t_font, t_fontfamily,
        t_fontfamilies, t_fontnia, t_fontsize, t_fontsizeadjust, t_fontstretch, t_fontstretches, t_fontstyle, t_fontweight, t_fontvariant, t_fontvariants,
        t_form, t_format, t_frame, t_frame4, t_framespacing, t_frequency,
    t_generic, t_glyphname, t_glyphnames, t_groupalign,
    t_halign, t_height, t_html, t_html_boolean, t_httpequiv, t_hv, t_hunit,
    t_icccolour, t_id, t_identifier_url, t_idref, t_idrefs, t_illegal, t_imagerendering, t_imcastr, t_imgsizes, t_importance, t_in, t_index, t_indentalign,
        t_indentalign2, t_indentshift2, t_infixlinebreakstyle, t_inky, t_inlist, t_inputaccept, t_inputmode, t_inputplus, t_inputtype, t_inputtype3, t_inputtype32,
        t_inputtype4, t_inputtype5, t_integer, t_is, t_isbn, t_issn, t_itemid, t_itemprop, t_itemtype,
    t_just_date, t_just_time,
    t_key, t_keygentype, t_keytype, t_kind,
    t_lang, t_langq, t_langs, t_langqs, t_larnalign, t_layout, t_lcralign, t_lcraligns, t_lcrnalign, t_lcrd, t_lcrds, t_lcrdss, t_length, t_length_absolute,
        t_length_relative, t_lengthadjust, t_linebreak, t_linebreakstyle, t_linecap, t_linejoin, t_linethickness, t_link, t_linkarg, t_linkargs, t_linkitself,
        t_linkparam, t_links, t_listtype, t_loading, t_local_url, t_location, t_longdivstyle, t_loop, t_loopie, t_lraalign, t_lralign, t_lspace,
    t_mah, t_marked_up, t_marker, t_markerunits, t_mathalign, t_mathalign_n, t_mathaligns, t_mathclosure, t_mathfontstyle, t_mathfontweight, t_mathform,
        t_mathframe, t_mathlocation, t_mathmode, t_mathnotation, t_mathnotations, t_mathoccurence, t_mathorder, t_mathoverflow, t_mathscope, t_mathsize,
        t_mathspace, t_mathspaceauto, t_mathspacefit, t_mathspaceinfinity, t_mathvariant, t_matrixtype, t_matrix_values, t_measure, t_measure_ai, t_measure_i,
        t_measure_or_more, t_measures, t_media, t_mediafeature, t_mediakeyword, t_meetslice, t_menuitem, t_menutype, t_metaname, t_method, t_methodological,
        t_microdata_domain, t_mime, t_mimelist, t_mimeq, t_mimeqs, t_mimestar, t_mode, t_month, t_morphology_operator, t_mql, t_mqls,
    t_name, t_nameref, t_namedspace, t_namespace, t_navigation, t_negative, t_normalised, t_normalisations, t_not_empty, t_notation, t_notations, t_nsd, t_nsds, t_num,
    t_occurence, t_ogtype, t_onoff, t_opacity, t_open, t_operator, t_order, t_orientation, t_origin, t_overflow,
    t_paint, t_paintkeyword, t_panose1, t_phase, t_pics, t_plus_1_7, t_plusstyle, t_pointerevents, t_points, t_positive, t_pragma, t_prefix, t_preload, t_preload5,
        t_preserveaspectratio, t_print, t_propagate, t_pseudo, t_pseudonamedspace,
    t_q,
    t_rap, t_rating, t_real, t_real_1_2, t_reals, t_referrer, t_refresh, t_refx, t_refy, t_regex, t_rel, t_rel_a, t_rel_avoid, t_rel_css, t_rel_illegal, t_rel_link,
        t_rel_obsolete, t_renderingintent, t_repeatcount, t_restart, t_result, t_reveal_trans, t_role, t_roles, t_roman_dsc, t_root_url, t_rotate, t_rotate_anim,
        t_rowscols,  t_rsvp, t_rules,
    t_sandbox, t_sandboxen, t_schema, t_scope, t_script, t_scrolling, t_settype, t_sex, t_sgml, t_shape, t_shape3, t_shape4, t_shape7, t_shaperendering,
        t_shape_rcp, t_show, t_side, t_size, t_size3, t_sizes,  t_sizex, t_smei, t_spacer, t_spacing, t_spread_method, t_srcset, t_ssi, t_ssi_comparison,
        t_ssi_config, t_ssi_echo, t_ssi_encoding, t_ssi_env, t_ssi_f, t_start, t_stitchtiles, t_svg_feature, t_ssi_include, t_ssi_set, t_ssi_sizefmt, t_step, t_style,
        t_svg_align, t_svg_baselineshift, t_svg_baseprofile, t_svg_content, t_svg_direction, t_svg_duration, t_svg_features, t_svg_fontstretch, t_svg_fontstretch_ff,
        t_svg_fontstyle, t_svg_fontstyle_ff, t_svg_fontvariant, t_svg_fontvariant_ff, t_svg_fontweight, t_svg_fontweight_ff, t_svg_fontweights, t_svg_method,
        t_svg_mode, t_svg_overflow, t_svg_playbackorder, t_svg_snapshottime, t_svg_time, t_svg_timelinebegin, t_svg_transform, t_svg_type, t_svg_type_11,
        t_svg_units, t_svg_values, t_svg_version, t_svg_viewbox, t_sym,
    t_tableframe, t_table_values, t_target, t_tbalign, t_tdscope, t_tel, t_tendstotype, t_text, t_textdecoration, t_textrendering, t_tfmu, t_tfa, t_tfu, t_tokens,
        t_transform, t_transform_anim, t_transform_fn, t_truefalseempty, t_turbulence_type, t_type, t_tz,
    t_ugeo, t_unicodebidi, t_units, t_unsigned, t_un_ex, t_unsigned_dosh, t_uplr, t_urange, t_url, t_urls,
    t_valign, t_valign3, t_valign_tmb, t_value, t_values, t_valuetype, t_vectoreffect, t_vectoreffect_12, t_vectoreffect_2, t_version, t_vid, t_visibility, t_vocab,
        t_vunit, t_vunits,
    t_wanted, t_week, t_width, t_workertype, t_wrap, t_wrap3, t_writingmode, t_wxhs,
    t_x_content_type_options, t_x_ua_compatible, t_xlinkactuate, t_xlinkshow, t_xlinktype, t_xmllink, t_xmlns, t_xmlspace, t_xmlurl, t_xorder,
    t_yesno, t_yesnoempty,
    t_zoompan,

    t_zzz } e_type;

typedef enum { ub_normal, ub_embed, ub_bidioverride, ub_inherit } e_unicodebidi;
typedef enum { w_en, w_pixels, w_relative } e_units;
typedef enum { di_down, di_left, di_right, di_up } e_uplr;
typedef enum { va32_top, va32_middle, va32_bottom } e_valign_tmb;
typedef enum { va_top, va_middle, va_bottom, va_baseline } e_valign3;
typedef enum { vt_data, vt_object, vt_ref } e_valuetype;
typedef enum { v12_inherit, v12_none, v12_nonscalingstroke } e_vectoreffect_12;
typedef enum { v2_fixedposition, v2_none, v2_nonrotation, v2_nonscalingstroke, v2_nonscalingsize } e_vectoreffect_2;
typedef enum { e_silent, e_severe, e_error, e_warning, e_info, e_comment, e_debug, e_variable, e_structure, e_detail, e_callstack, e_splurge, e_all } e_verbose;
typedef enum { vi_visible, vi_hidden, vi_collapse, vi_inherit } e_visibility;
typedef enum { wm_undefined, wm_addr, wm_link, wm_root } e_wm_status;
typedef enum { wt_classic, wt_module } e_workertype;
typedef enum { w_soft, w_hard } e_wrap;
typedef enum { w_horiz, w_vert } e_wrap3;
typedef enum { wm_lrtb, wm_rltb, wm_tbrl, wm_lr, wm_rl, wm_tb, wm_inherit } e_writingmode;
typedef enum { xls_new, xls_replace, xls_embed, xls_other, xls_none } e_xlinkshow;
typedef enum {  x_default, x_xhtml_1, x_xhtml_1_superseded, x_xhtml_11, x_xhtml_2, x_bibo, x_cc, x_crs, x_dbp, x_dbp_owl, x_dbr, x_dc, x_ex, x_foaf,
                x_mathml, x_owl, x_rdf, x_rdfa, x_rdfs, x_svg, x_xhv, x_xlink, x_xml, x_xmlns, x_xsd } e_xmlns;
typedef enum { xs_default, xs_preserve } e_xmlspace;
typedef enum { or_document, or_list } e_xorder;
typedef enum { y_yes, y_no } e_yesno;
typedef enum { z_disable, z_magnify } e_zoompan;
