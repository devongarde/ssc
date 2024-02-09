﻿/*                                                                 ,
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
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

typedef enum { e_0, e_1 } e_10;
typedef enum { ac_a, av_v } e_a_v;
typedef enum { abc_after, abc_before, abc_content, abc_first_letter } e_abcfl;
typedef enum { abf_after, abf_before, abf_first_letter, abf_marker, abf_text } e_abfmt;
typedef enum {  am_deposit, am_donation, am_purchase, am_loan, am_licence, am_item_creation } e_accrual_method;
typedef enum {  ap_triennial, ap_biennial, ap_annual, ap_semiannual, ap_thriceyearly, ap_quarterly, ap_bimonthly, ap_monthly, ap_semimonthly, ap_biweekly, ap_thricemonthly,
                ap_weekly, ap_semiweekly, ap_thriceweekly, ap_daily, ap_continuous, ap_irregular } e_accrual_periodicity;
typedef enum {  ap_closed, ap_active, ap_passive, ap_partial } e_accrual_policy;
typedef enum { ac_none, ac_sum } e_accumulate;
typedef enum { ace_auto, ace_centre, ace_end, ace_start } e_aces;
typedef enum { acm_arcs, acm_crop, acm_miter } e_acm;
typedef enum { acn_auto, acn_contain, acn_none } e_acn;
typedef enum { av_sell, av_rent, av_trade, av_meet, av_announce, av_offer, av_wanted, av_event, av_service } e_action;
typedef enum { at_toggle, at_statusline, at_tooltip, at_highlight } e_actiontype;
typedef enum { act_insert, act_update, act_delete, act_static, act_unknown } e_activity;
typedef enum { ea_auto, ea_user } e_actuate;
typedef enum { ad_replace, ad_sum } e_additive;
typedef enum { aesf_allow_end, aesf_space_first } e_aesf;
typedef enum { a70_centre, a70_justify, a70_left, a70_right } e_align2070;
typedef enum { ald_centre, ald_decimal, ald_left, ald_right } e_aligndec;
typedef enum { alf_centre, alf_float, alf_left, alf_right } e_alignfig;
typedef enum {  ab_afteredge, ab_alphabetic, ab_auto, ab_baseline, ab_beforeedge, ab_bottom, ab_central,
                ab_hanging, ab_ideographic, ab_inherit, ab_mathematical, ab_middle, ab_textafteredge,
                ab_textbeforeedge, ab_textbottom, ab_texttop, ab_top } e_alignment_baseline;
typedef enum { ap_centre, ap_indent, ap_justify, ap_left, ap_right } e_alignplus;
typedef enum { a3_top, a3_middle, a3_bottom, a3_left, a3_right } e_align3;
typedef enum { aan_all, aan_auto, aan_none } e_all_auto_none;
typedef enum { af_allow_end, af_force_end } e_allow_force;
typedef enum { alp_auto, alp_landscape, alp_portrait } e_alp;
typedef enum { ean_always, ean_normal } e_always_normal;
typedef enum {  at_none, at_angle, at_colour, at_coordinate, at_frequency, at_integer, at_percentage, at_length, at_list, at_number, at_paint, at_time,
                at_transform, at_url, at_other } e_animation_type;
typedef enum { ebn_anywhere, ebn_break_word, ebn_normal } e_anywhere_break_normal;
typedef enum { ar_initial, ar_medial, at_terminal, at_isolated } e_arabicenum;
typedef enum { asu_cm, asu_feet, asu_inches, asu_km, asu_m, asu_miles } e_as_units;
typedef enum { aa_both, aa_inline, aa_list, aa_none  } e_aria_autocomplete;
typedef enum { ai_false, ai_grammar, ai_spelling, ai_true } e_aria_invalidity;
typedef enum { al_assertive, al_off, al_polite } e_aria_live;
typedef enum {  role_any, role_alert, role_alertdialogue, role_application, role_article, role_banner, role_button, role_cell, role_checkbox, role_columnheader, role_combobox,
                role_command, role_complementary, role_contentinfo, role_definition, role_dialogue, role_directory, role_document, role_feed, role_figure, role_form,
                role_graphics_document, role_graphics_object, role_graphics_symbol, role_grid, role_gridcell, role_group, role_heading, role_img, role_landmark, role_link,
                role_list, role_listbox, role_listitem, role_log, role_main, role_marquee, role_math, role_menu, role_menubar, role_menuitem, role_menuitemcheckbox,
                role_menuitemradio, role_navigation, role_none, role_note, role_option, role_presentation, role_progressbar, role_radio, role_radiogroup, role_range,
                role_region, role_roletype, role_row, role_rowgroup, role_rowheader, role_scrollbar, role_search, role_searchbox, role_section, role_sectionhead,
                role_select, role_separator, role_slider, role_spinbutton, role_status, role_structure, role_switch, role_tab, role_table, role_tablist, role_tabpanel,
                role_term, role_textbox, role_timer, role_toolbar, role_tooltip, role_tree, role_treegrid, role_treeitem, role_widget, role_window } e_aria_role;
typedef enum { as_ascending, as_descending, as_none, as_other } e_aria_sort;
typedef enum { as_audio, as_document, as_embed, as_fetch, as_font, as_image, as_object, as_script, as_style, as_track, as_video, as_worker } e_as;
typedef enum { ass_alternative, ass_slide, ass_scroll } e_ass;

typedef enum
{   a_unknown, a_custom,
        a_abbr, a_about, a_above, a_accent, a_accent_height, a_accentunder, a_accept, a_accept_charset, a_accesskey, a_accumulate, a_action, a_actiontype,
        a_activate, a_active, a_additive, a_align, a_alignment_baseline, a_alignmentscope, a_alink, a_allow, a_allow_zoom_and_pan, a_allowfullscreen,
        a_allowpaymentrequest, a_allowusermedia, a_alphabetic, a_alt, a_altimg, a_altimg_height, a_altimg_width, a_altimg_valign, a_alttext,
        a_amplitude, a_animate, a_arabic_form, a_archive, a_arg, a_aria_activedescendant, a_aria_atomic, a_aria_autocomplete, a_aria_busy, a_aria_checked,
        a_aria_colcount, a_aria_colindex, a_aria_colspan, a_aria_controls, a_aria_current, a_aria_describedby, a_aria_details, a_aria_disabled,
        a_aria_dropeffect, a_aria_errormessage, a_aria_expanded, a_aria_flowto, a_aria_grabbed, a_aria_haspopup, a_aria_hidden, a_aria_invalid, a_aria_label,
        a_aria_labelledby, a_aria_level, a_aria_live, a_aria_modal, a_aria_multiline, a_aria_multiselectable, a_aria_orientation, a_aria_owns,
        a_aria_placeholder, a_aria_posinset, a_aria_pressed, a_aria_readonly, a_aria_relevant, a_aria_required, a_aria_roledescription, a_aria_rowcount,
        a_aria_rowindex, a_aria_rowspan, a_aria_selected, a_aria_setsize, a_aria_sort, a_aria_valuemax, a_aria_valuemin, a_aria_valuenow, a_aria_valuetext,
        a_as, a_ascent, a_async, a_at, a_attributename, a_attributetype, a_audio, a_audio_level, a_autobuffer, a_autocapitalise, a_autocomplete,
        a_autocorrect, a_autofocus, a_autopictureinpicture, a_autoplay, a_autosubmit, a_axes, a_axis, a_azimuth,
    a_background, a_background_fill, a_balance, a_bandwidth, a_base, a_basefrequency, a_baseline, a_baseline_shift, a_baseprofile, a_bbox, a_begin,
        a_behaviour, a_below, a_bevelled, a_bgcolour, a_bias, a_blocking, a_border, a_bottommargin, a_box, a_bubbles, a_buffered, a_buffered_rendering, a_by,
    a_cache, a_calcmode, a_cancelable, a_cap_height, a_capture, a_cd, a_cdgroup, a_cell, a_cellpadding, a_cellspacing, a_challenge, a_char, a_charalign,
        a_charoff, a_charset, a_charspacing, a_checked, a_cite, a_class, a_classid, a_clear, a_clip, a_clip_path, a_clip_rule, a_clippathunits,
        a_clip_to_self, a_close, a_closure, a_code, a_codebase, a_codetype, a_coldef, a_colour, a_colour_interpolation, a_colour_interpolation_filters,
        a_colour_profile, a_colour_rendering, a_cols, a_colspan, a_colspec, a_columnalign, a_columnlines, a_columnspacing, a_columnspan, a_columnwidth,
        a_command, a_compact, a_comp_op, a_compositing, a_condition, a_connect, a_content, a_contenteditable, a_contentlength, a_contentscripttype,
        a_contentstyletype, a_contextmenu, a_continue, a_controls, a_controlslist, a_coords, a_crossorigin, a_crossout, a_csp, a_currenttime, a_cursor,
        a_cx, a_cy,
    a_d, a_data, a_datafld, a_dataformatas, a_datasrc, a_datatype, a_datawild, a_datetime,
        a_decimalpoint, a_declare, a_decoding, a_default, a_defaultaction, a_defer, a_definitionurl, a_denomalign, a_depth, a_descent, a_dh,
        a_diffuseconstant, a_dingbat, a_dir, a_direction, a_dirname, a_disabled, a_disablepictureinpicture, a_disableremoteplayback, a_display,
        a_display_align, a_displaystyle, a_divisor, a_dominant_baseline, a_download, a_dp, a_draggable, a_dropzone, a_dur, a_duration, a_dw, a_dx, a_dy,
    a_edge, a_edgemode, a_edit, a_editable, a_effect, a_elevation, a_enable_background, a_encoding, a_enctype, a_end, a_endprogress, a_enterkeyhint,
        a_equalcolumns, a_equalrows, a_error, a_event, a_eventtarget, a_evevent, a_exponent, a_exportparts, a_externalresourcesrequired,
    a_face, a_fadecolour, a_fecolourmatrix, a_fecomposite, a_fegaussianblur, a_femorphology, a_fence, a_fetchpriority, a_fetile, a_fill, a_fill_opacity,
        a_fill_rule, a_filter, a_filterres, a_filterunits, a_flatness, a_flood_colour, a_flood_opacity, a_focusable, a_focushighlight, a_font,
        a_font_feature_settings, a_font_family, a_font_kerning, a_font_size,
        a_font_size_adjust, a_font_stretch, a_font_style, a_font_variant, a_font_variant_caps, a_font_variant_east_asian, a_font_variant_ligatures,
        a_font_variant_numeric, a_font_variant_position, a_font_weight, a_fontfamily, a_fontsize, a_fontstretch, a_fontstyle, a_fontvariant,
        a_fontweight, a_for, a_form, a_formaction, a_format, a_formenctype, a_formmethod, a_formnovalidate, a_forms, a_formtarget, a_fr, a_frame,
        a_frameborder, a_framespacing, a_from, a_full, a_function, a_fx, a_fy,
    a_g1, a_g2, a_generator_unable, a_glyph_orientation_vertical, a_glyphname, a_glyph_orientation_horizontal, a_glyphref, a_gradienttransform,
        a_gradientunits, a_groupalign, a_gutter,
    a_handler, a_hanging, a_headers, a_height, a_hidden, a_high, a_horiz_adv_x, a_horiz_origin_x, a_horiz_origin_y, a_href, a_hreflang, a_hrefmedia,
        a_hreftype, a_hspace, a_html, a_httpequiv, a_hyphens,
    a_icon, a_id, a_ideographic, a_idref, a_if, a_image_rendering, a_imagemap, a_imagesizes, a_imagesrcset, a_implements, a_importance,
        a_in, a_in2, a_incremental, a_indent, a_indentalign, a_indentalignfirst, a_indentalignlast, a_indentshift, a_indentshiftfirst,
        a_indentshiftlast, a_indenttarget, a_index, a_inert, a_infixlinebreakstyle, a_initialvisibility, a_inline_size, a_inlist,
        a_inputmode, a_instanceof, a_integrity, a_intent, a_intercept, a_intrinsicsize, a_irrelevant, a_is, a_ismap, a_isolation, a_item, a_itemid,
        a_itemprop, a_itemref, a_itemscope, a_itemtype, a_itstranslate,
    a_k, a_k1, a_k2, a_k3, a_k4, a_kernelmatrix, a_kernelunitlength, a_kerning, a_key, a_keyparams, a_keypoints, a_keysplines, a_keytimes,
        a_keytype, a_kind, a_knock_out,
    a_label, a_labels, a_lang, a_language, a_largeop, a_layout, a_ldelim, a_left, a_leftmargin, a_leftoverhang, a_length, a_lengthadjust,
        a_letter_spacing, a_lighting_colour, a_limitingconeangle, a_linebreak, a_line_break, a_linebreakmultichar, a_linebreakstyle,
        a_line_height, a_line_increment, a_lineleading, a_linethickness, a_link, a_list, a_loading, a_local, a_location, a_longdesc,
        a_longdivstyle, a_loop, a_loopcount, a_loopend, a_loopstart, a_low, a_lquote, a_lspace,
    a_macros, a_manifest, a_marginheight, a_marginwidth, a_marker, a_marker_end, a_marker_mid, a_marker_start, a_markerheight, a_markerunits,
        a_markerwidth, a_mask, a_maskcontentunits, a_masktype, a_maskunits, a_math, a_mathbackground, a_mathematical, a_mathcolour, a_mathsize,
        a_mathvariant, a_max, a_maxlength, a_maxsize, a_max_unit_scale, a_maxwidth, a_md, a_media, a_mediacharacterencoding,
        a_mediacontentencodings, a_mediagroup, a_mediasize, a_mediatime, a_mediummathspace, a_menu, a_method, a_methods, a_min,
        a_minlabelspacing, a_minlength, a_minsize, a_min_unit_scale, a_mode, a_movablelimits, a_mozactionhint, a_mozbrowser,
        a_mslinethickness, a_multiple, a_muted,
    a_n, a_name, a_namespace, a_nargs, a_nav_down, a_nav_downleft, a_nav_downright, a_nav_left, a_nav_next, a_nav_prev, a_nav_right, a_nav_up,
        a_nav_upleft, a_nav_upright, a_nextfocus, a_no_composite, a_noflow, a_nohref, a_nominal_length, a_nomodule, a_noresize, a_noshade,
        a_notation, a_novalidate, a_nowrap, a_numalign, a_numberonce, a_numoctaves,
    a_object, a_observer, a_occurrence, a_offset, a_onabort, a_onactivate, a_onafterprint, a_onautocomplete, a_onautocompleteerror, a_onauxclick,
        a_onbeforeprint, a_onbeforeunload, a_onbegin, a_onblur, a_oncancel, a_oncanplay, a_oncanplaythrough, a_onchange, a_onclick, a_onclose,
        a_oncontextmenu, a_oncopy, a_oncuechange, a_oncut, a_ondblclick, a_ondrag, a_ondragend, a_ondragenter, a_ondragexit, a_ondragleave,
        a_ondragover, a_ondragstart, a_ondrop, a_ondurationchange, a_onemptied, a_onend, a_onended, a_onerror, a_onevent, a_onfocus, a_onfocusin,
        a_onfocusout, a_onformchange, a_onformdata, a_onforminput, a_onfullscreenchange, a_onfullscreenerror, a_onhashchange, a_oninput,
        a_oninvalid, a_onkeydown, a_onkeypress, a_onkeyup, a_onlanguagechange, a_onload, a_onloadeddata, a_onloadedmetadata, a_onloadend,
        a_onloadprogress, a_onloadstart, a_onmessage, a_onmessageerror, a_onmousedown, a_onmouseenter, a_onmouseleave, a_onmousemove,
        a_onmouseout, a_onmouseover, a_onmouseup, a_onmousewheel, a_onoffline, a_ononline, a_onpagehide, a_onpageshow, a_onpaste, a_onpause,
        a_onplay, a_onplaying, a_onpopstate, a_onpostload, a_onpreload, a_onprogress, a_onratechange, a_onreadystatechange, a_onredo,
        a_onrejectionhandled, a_onrepeat, a_onreset, a_onresize, a_onscroll, a_onscrollend, a_onsecuritypolicyviolation, a_onsought, a_onseeking, a_onselect,
        a_onshow, a_onslotchange, a_onsort, a_onstalled, a_onstorage, a_onsubmit, a_onsuspend, a_ontimeupdate, a_ontoggle, a_onunhandledrejection,
        a_onundo, a_onunload, a_onvolumechange, a_onwaiting, a_onwheel, a_onzoom, a_opacity, a_open, a_operator, a_optimum, a_order, a_orient,
        a_orientation, a_origin, a_other, a_overflow, a_overflow_wrap, a_overlay, a_overlay_host, a_overline_position, a_overline_thickness,
    a_pagex, a_pagey, a_page_orientation, a_paint_order, a_panose_1, a_part, a_path, a_pathlength, a_pattern, a_patterncontentunits,
        a_patterntransform, a_patternunits, a_phase, a_ping, a_placeholder, a_plain, a_playbackorder, a_playcount, a_playsinline, a_pointer_events,
        a_points, a_pointsatx, a_pointsaty, a_pointsatz, a_popover, a_popovertarget, a_popovertargetaction,
        a_position, a_poster, a_prefetch, a_prefix, a_preload, a_preservealpha,
        a_preserveaspectratio, a_prevfocus, a_primitiveunits, a_print, a_profile, a_prompt, a_propagate, a_property, a_pubdate, a_public,
    a_r, a_radiogroup, a_radius, a_rdelim, a_rdf_about, a_rdf_datatype, a_rdf_id, a_rdf_nodeid, a_rdf_parsetype, a_rdf_resource, a_readonly, a_ref,
        a_referrerpolicy, a_refx, a_refy, a_registrationmark, a_rel, a_rendering_colour_space, a_rendering_in_tents, a_repeatcount, a_repeatdur,
        a_required, a_requiredextensions, a_requiredfeatures, a_requiredfonts, a_requiredformats, a_resource, a_restart, a_result, a_results, a_rev,
        a_reverse, a_reversed, a_rightmargin, a_rightoverhang, a_role, a_rotate, a_row, a_rowalign, a_rowgroup, a_rowlines, a_rows, a_rowspacing,
        a_rowspan, a_rquote, a_rspace, a_rules, a_rx, a_ry,
    a_sandbox, a_scale, a_scheme, a_scope, a_scoped, a_script, a_scriptlevel, a_scriptminsize, a_scriptsizemultiplier, a_scrollamount, a_scrolldelay,
        a_scrolling, a_seamless, a_seed, a_seethru, a_select, a_selected, a_selection, a_separator, a_separators, a_seqnum, a_setback_offset,
        a_several, a_shadowinherit, a_shape, a_shape_image_threshold, a_shape_inside, a_shape_margin, a_shape_padding, a_shape_rendering,
        a_shape_subtract, a_shift, a_side, a_size, a_sizes, a_skip, a_slope, a_slot, a_snap, a_snapshottime, a_solid_colour, a_solid_opacity,
        a_sortable, a_sorted, a_spacing, a_span, a_specularconstant, a_specularexponent, a_spellcheck, a_spreadmethod, a_src, a_srcdoc, a_srclang,
        a_srcset, a_srctype, a_stackalign, a_standalone, a_standby, a_start, a_startoffset, a_startprogress, a_static, a_stddeviation, a_stemh,
        a_stemv, a_step, a_stitchtiles, a_stop_colour, a_stop_opacity, a_streamedcontents, a_stretchy, a_strikethrough_position,
        a_strikethrough_thickness, a_string, a_stroke, a_stroke_dasharray, a_stroke_dashoffset, a_stroke_linecap, a_stroke_linejoin,
        a_stroke_miterlimit, a_stroke_opacity, a_stroke_width, a_style, a_subtype, a_subject, a_subscriptshift, a_summary, a_superscriptshift,
        a_surfacescale, a_svg, a_sym, a_svg_transform, a_symmetric, a_syncbehaviour, a_syncbehaviourdefault, a_syncmaster, a_synctolerance,
        a_synctolerancedefault, a_system, a_systemlanguage,
    a_tabindex, a_tablevalues, a_tag, a_target, a_targetid, a_targetrole, a_targetx, a_targety, a_template, a_text, a_text_align, a_text_align_last,
        a_text_anchor, a_text_decoration, a_text_decoration_colour, a_text_decoration_fill, a_text_decoration_line, a_text_decoration_stroke,
        a_text_decoration_style, a_text_indent, a_text_justify, a_text_orientation, a_text_overflow, a_text_rendering, a_textlength, a_thickmathspace,
        a_thinmathspace, a_timelinebegin, a_title, a_to, a_tooltip, a_top, a_topmargin, a_transform, a_transformbehaviour, a_transform_box,
        a_transform_host, a_transform_origin, a_transformpath, a_transin, a_transout, a_translate, a_truespeed, a_type, a_typemustmatch, a_typeof,
    a_u1, a_u2, a_underline_position, a_underline_thickness, a_unicode, a_unicode_bidi, a_unicode_range, a_units, a_units_per_em, a_until,
        a_updateviacache, a_urn, a_usemap,
    a_valign, a_v_alphabetic, a_value, a_values, a_valuetype, a_vector_effect, a_vectoreffectunits, a_version, a_vert_adv_y, a_vert_origin_x,
        a_vert_origin_y, a_vertical_align, a_verythickmathspace, a_verythinmathspace, a_veryverythickmathspace, a_veryverythinmathspace, a_v_hanging,
        a_v_ideographic, a_viewbox, a_viewtarget, a_viewport_fill, a_viewport_fill_opacity, a_visibility, a_vlink, a_v_mathematical, a_vocab,
        a_voffset, a_volume, a_vspace,
    a_webkitdirectory, a_while, a_white_space, a_width, a_widths, a_will_change, a_word_break, a_word_spacing, a_word_wrap, a_workertype, a_wrap,
        a_writing_mode,
    a_x, a_x1, a_x2, a_xchannelselector, a_x_height, a_xlinkactuate, a_xlinkarcrole, a_xlinkhref, a_xlinkrole, a_xlinkshow, a_xlinktitle, a_xlinktype,
        a_xmlbase, a_xmlid, a_xmllang, a_xmllink, a_xmlns, a_xmlns_xlink, a_xmlspace, a_xref, a_xsischemaloc,
    a_y, a_y1, a_y2, a_ychannelselector,
    a_z, a_zindex, a_zoomandpan,
    a_illegal
 } e_attribute;
const e_attribute last_attribute = a_illegal;

typedef enum { an_auto, an_css, an_xml } e_attributetype;
typedef enum {  au_angle, au_colour, au_cm, au_deg, au_em, au_ex, au_frequency, au_grad, au_hz, au_in, au_integer, au_khz, au_length, au_mm, au_ms,
                au_number, au_pc, au_percent, au_pt, au_px, au_string, au_rad, au_rem, au_s, au_time, au_url, au_vh, au_vmax, au_vmin, au_vw } e_attr_unit;
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

typedef enum { abr_auto, abr_break } e_auto_break;
typedef enum { eac_auto, eac_contain } e_auto_contain;
typedef enum { acc_auto, acc_contain, acc_cover } e_auto_contain_cover;
typedef enum { afl_auto, afl_first, afl_last } e_auto_first_last;
typedef enum { afs_auto, afs_focus, afs_scroll } e_auto_focus_scroll;
typedef enum { ahv_auto, ahv_hidden, ahv_visible } e_auto_hidden_visible;
typedef enum { amn_auto, amn_manual, amn_none } e_auto_manual_none;
typedef enum { ems_auto, ems_merge, ems_separate } e_auto_merge_separate;
typedef enum { fch_auto, fch_none } e_auto_none;
typedef enum { ant_auto, ant_none, ant_thin } e_auto_none_thin;
typedef enum { eas_auto, eas_smooth } e_auto_smooth;
typedef enum { as_auto, as_stable } e_auto_stable;
typedef enum { bcn_baseline, bcn_contain, bcn_none } e_baseline_contain_none;
typedef enum { bsb_baseline, bsb_bottom, bsb_centre, bsb_top, bsb_sub, bsb_super, bsb_inherit } e_baselineshift;
typedef enum { bcs_bounding_box, bcs_clone, bcs_slice } e_bcs;
typedef enum { be_alternative, be_scroll, be_slide } e_behaviour;
typedef enum { bens_both, bens_end, bens_none, bens_start } e_bens;
typedef enum { benrs_both, benrs_end, benrs_normal, benrs_start } e_benrs;
typedef enum { bixy_block, bixy_inline, bixy_x, bixy_y } e_bixy;
typedef enum { bk_asp, bk_cdata, bk_code, bk_comment, bk_doctype, bk_node, bk_num, bk_php, bk_ssi, bk_stylesheet, bk_text, bk_xml } bk_status;
typedef enum { bi_block, bi_inline } e_block_inline;
typedef enum { b_true, b_false } e_bool;
typedef enum { brs_bevel, brs_round, brs_stupid } e_brs;
typedef enum { br_auto, br_dynamic, br_static, br_inherit } e_buffered_rendering;
typedef enum { bu_button, bu_submit, bu_reset } e_button;
typedef enum { bm_ansi, bm_utf8, bm_utf16_be, bm_utf16_le, bm_utf32_be, bm_utf32_le, bm_utf7, bm_utf1, bm_utf_ebcdic, bm_scsu, bm_bocu_1, bm_gb_1830, bm_error } byte_order_mark;
typedef enum { ck_maxage, ck_maxstale, ck_minfresh, ck_nocache, ck_nostore, ck_notransform, ck_onlyifcached } e_cachekey;
typedef enum { cs_free, cs_loading, cs_empty, cs_content, cs_error } e_cache_state;
typedef enum { cm_discrete, cm_linear, cm_paced, cm_spline } e_calcmode;
typedef enum { ca_bottom, cap_left, ca_right, ca_top } e_captionalign;
typedef enum { cv_user, cv_environment } ev_capture;
typedef enum {  ec_undefined, ec_aria, ec_attribute, ec_cache, ec_corpus, ec_crc, ec_css, ec_directory, ec_element, ec_file, ec_fred, ec_html, ec_icu, ec_incorrectness,
                ec_init, ec_io, ec_json, ec_link, ec_microdata, ec_microformat, ec_mime, ec_mql, ec_namespace, ec_page, ec_parser, ec_program, ec_rdfa, ec_regex, ec_rudeness,
                ec_schema, ec_shadow, ec_spell, ec_ssi, ec_tidyness, ec_type, ec_url, ec_utility } e_category;
const e_category last_category = ec_utility;
typedef enum { ccp_derivativeworks, ccp_distribution, ccp_reproduction } e_cc_permits;
typedef enum { ccr_attribution, ccr_notice, ccr_sharealike, ccr_sourcecode } e_cc_requires;
typedef enum { cel_centre, cel_end, cel_left, cel_none, cel_right, cel_start } e_celnrs;
typedef enum { cens_centre, cens_end, cens_none, cens_start } e_cens;
typedef enum { cs_centre, cs_space_around, cs_space_between, cs_start } e_centre_space;
typedef enum { cc_ansi, cc_utf8, cc_utf16be, cc_utf16le, cc_gb, cc_fkd } e_charcode;
typedef enum { ch_a, ch_b, ch_g, ch_r } e_channelselector;

typedef enum { 
    cs_context,
    cs_adobe_standard_encoding, cs_adobe_symbol_encoding, cs_amiga_1251, cs_ansi_x3_110_1983, cs_ascii, cs_asmo_449, cs_axiom,
    cs_bocu_1, cs_brf, cs_bs_4730, cs_bs_viewdata, cs_big5,
    cs_cesu_8, cs_cp50220, cs_cp51932, cs_csa_z243_4_1985_1, cs_csa_z243_4_1985_2, cs_csa_z243_4_1985_gr, cs_csn_369103,
    cs_dec_mcs, cs_din_66003, cs_dk_us, cs_ds_2089,
    cs_ebcdic_at_de, cs_ebcdic_at_de_a, cs_ebcdic_ca_fr, cs_ebcdic_dk_no, cs_ebcdic_dk_no_a, cs_ebcdic_es, cs_ebcdic_es_a, cs_ebcdic_es_s, cs_ebcdic_fi_se,
        cs_ebcdic_fi_se_a, cs_ebcdic_fr, cs_ebcdic_it, cs_ebcdic_pt, cs_ebcdic_uk, cs_ebcdic_us, cs_ecma_cyrillic, cs_es, cs_es2, cs_euc_jp, cs_euc_kr,
        cs_extended_unix_code_fixed_width_for_japanese, cs_extended_unix_code_packed_format_for_japanese,
    cs_gb18030, cs_gbk, cs_gb_1988_80, cs_gost_19768_74, cs_greek_ccitt, cs_greek7, cs_greek7_old,
    cs_hp_desktop, cs_hp_legal, cs_hp_math8, cs_hp_pi_font, cs_hp_roman8, 
    cs_ibm_symbols, cs_ibm_thai, cs_ibm00858, cs_ibm00924, cs_ibm01140, cs_ibm01141, cs_ibm01142, cs_ibm01143, cs_ibm01144, cs_ibm01145, cs_ibm01146,
        cs_ibm01147, cs_ibm01148, cs_ibm01149, cs_ibm037, cs_ibm038, cs_ibm1026, cs_ibm1047, cs_ibm273, cs_ibm274, cs_ibm275, cs_ibm277, cs_ibm278,
        cs_ibm280, cs_ibm281, cs_ibm284, cs_ibm285, cs_ibm290, cs_ibm297, cs_ibm420, cs_ibm423, cs_ibm424, cs_ibm437, cs_ibm500, cs_ibm775, cs_ibm850,
        cs_ibm851, cs_ibm852, cs_ibm855, cs_ibm857, cs_ibm860, cs_ibm861, cs_ibm862, cs_ibm863, cs_ibm864, cs_ibm865, cs_ibm866, cs_ibm868, cs_ibm869,
        cs_ibm870, cs_ibm871, cs_ibm880, cs_ibm891, cs_ibm903, cs_ibm904, cs_ibm905, cs_ibm918,
        cs_iec_p27_1, cs_inis, cs_inis_8, cs_inis_cyrillic, cs_invariant,
        cs_iso_10646_j_1, cs_iso_10646_ucs_4, cs_iso_10646_ucs_basic, cs_iso_10646_utf_1, cs_iso_10646_unicode_latin1, cs_iso_11548_1, cs_iso_2022_cn,
        cs_iso_2022_jp, cs_iso_2022_jp_2, cs_iso_8859_1_windows_3_0_latin_1, cs_iso_8859_1_windows_3_1_latin_1, cs_iso_8859_10, cs_iso_8859_13,
        cs_iso_8859_14, cs_iso_8859_15, cs_iso_8859_16, cs_iso_8859_2, cs_iso_8859_2_windows_latin_2, cs_iso_8859_3, cs_iso_8859_4, cs_iso_8859_5,
        cs_iso_8859_6, cs_iso_8859_6_e, cs_iso_8859_6_i, cs_iso_8859_7, cs_iso_8859_8, cs_iso_8859_8_e, cs_iso_8859_8_i, cs_iso_8859_9, cs_iso_ir_90,
        cs_iso_8859_9_windows_latin_5, cs_iso_unicode_ibm_1261, cs_iso_unicode_ibm_1264, cs_iso_unicode_ibm_1265, cs_iso_unicode_ibm_1268,
        cs_iso_unicode_ibm_1276, cs_iso_10367_box, cs_iso_2033_1983, cs_iso_5427, cs_iso_5427_1981, cs_iso_5428_1980, cs_iso_646_basic_1983,
        cs_iso_646_irv_1983, cs_iso_6937_2_25, cs_iso_6937_2_add, cs_iso_8859_3_1988, cs_iso_8859_4_1988, cs_iso_8859_9_1989, cs_iso_8859_supp, cs_it,
    cs_jis_c6220_1969_jp, cs_jis_c6220_1969_ro, cs_jis_c6226_1978, cs_jis_c6226_1983, cs_jis_c6229_1984_a, cs_jis_c6229_1984_b, cs_jis_c6229_1984_b_add,
        cs_jis_c6229_1984_hand, cs_jis_c6229_1984_hand_add, cs_jis_c6229_1984_kana, cs_jis_encoding, cs_jis_x0201, cs_jis_x0212_1990, cs_jus_i_b1_002,
        cs_jus_i_b1_003_mac, cs_jus_i_b1_003_serb,
    cs_koi7_switched, cs_koi8_r, cs_koi8_u, cs_ksc5636, cs_kz_1048,
    cs_latin_greek, cs_latin_greek_1, cs_latin_lap,
    cs_macintosh, cs_maple, cs_mathematica, cs_mathml_content, cs_mathml_presentation, cs_mnem, cs_mnemonic, cs_msz_7795_3, cs_microsoft_publishing,
    cs_nats_dano, cs_nats_dano_add, cs_nats_sefi, cs_nats_sefi_add, cs_cs_nc_nc00_10_81, cs_nf_z_62_010, cs_nf_z_62_010_1973, cs_ns_4551_1,
        cs_ns_4551_2,
    cs_openmath, cs_osd_ebcdic_df03_irv, cs_osd_ebcdic_df04_1, cs_osd_ebcdic_df04_15,
    cs_pc8_danish_norwegian, cs_pc8_turkish, cs_pt, cs_pt2, cs_ptcp154,
    cs_scsu, cs_sen_850200_b, cs_sen_850200_c,
    cs_t_101_g2, cs_t_61_7bit, cs_t_61_8bit, cs_tex, cs_text, cs_tscii,
    cs_unicode_1_1, cs_unicode_1_1_utf_7, cs_unknown_8bit, cs_us_dk, cs_utf_16be, cs_utf_16le, cs_utf_32, cs_utf_32be, cs_utf_32le, cs_utf_7, cs_utf_8,
    cs_videotex_suppl, cs_viqr, cs_viscii, cs_ventura_international, cs_ventura_math, cs_ventura_us,
    cs_windows_1250, cs_windows_1251, cs_windows_1252, cs_windows_1253, cs_windows_1254, cs_windows_1255, cs_windows_1256, cs_windows_1257,
        cs_windows_1258, cs_windows_31j, cs_windows_874,
    cs_x_user_defined,
    cs_illegal } e_charset;

typedef enum { cio_centre, cio_inset, cio_outset } e_cio;
typedef enum { cipr_column, cipr_inline, cipr_page, cipr_region } e_cipr;
typedef enum { ece_circle, ece_ellipse } e_circle_ellipse;
typedef enum {
    ci_integer, ci_rational, ci_real, ci_complexpolar, ci_complexcartesian, ci_constant,
    ci_complex, ci_function, ci_vector, ci_list, ci_set, ci_matrix } e_citype;

typedef enum { 
    c_context,

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

    c_error } e_class;

typedef enum { cf_clear, cf_float } e_clear_float;
typedef enum { co_closed, co_open } e_closed_open;
typedef enum {  cn_enotation, cn_integer, cn_rational, cn_real, cn_complexpolar, cn_complexcartesian, cn_constant,
                cn_double, cn_hexdouble } e_cntype;
typedef enum { cs_cmyk, cs_rgb, cs_lab } e_colour_space;
typedef enum { ci_auto, ci_srgb, ci_linearrgb, ci_inherit } e_colour_interpolation;
typedef enum { cr_auto, cr_optimisespeed, cr_optimisequality, cr_inherit } e_colour_rendering;
typedef enum { ecs_dark, ecs_light } e_colour_scheme;
typedef enum { co_command, co_checkbox, co_radio } e_command;
typedef enum { es_original, es_query, es_fragment, es_scheme, es_authority, es_user, es_password, es_server, es_port, es_path, es_file, es_extension } e_component;
typedef enum {  cop_clear, cop_src, cop_dst, cop_src_over, cop_dst_over, cop_src_in, cop_dst_in, cop_src_out, cop_dst_out, cop_src_atop, cop_dst_atop, cop_xor, cop_plus,
                cop_multiply, cop_screen, cop_overlay, cop_darken, cop_lighten, cop_colour_dodge, cop_colour_burn, cop_hard_light, cop_soft_light, cop_difference,
                cop_exclusion, cop_inherit } e_comp_op;
typedef enum { co_arithmetic, co_atop, co_in, co_lighter, co_out, co_over, co_xor } e_composite_operator;
typedef enum { com_normal, com_knockout } e_compositing;
typedef enum { cv_examine, cv_stage, cv_purgatory, cv_scan, cv_done, cv_max } e_condvar;

typedef enum {
    icl_absolute_complement, icl_absolute_value, icl_acceleration, icl_adjacent, icl_adjugate, icl_aligned_equation, icl_and, icl_angle, icl_angle_angle,
        icl_angular_description, icl_annotation, icl_approaches, icl_approximately, icl_aqueous, icl_arc, icl_area, icl_array, icl_average,
    icl_base, icl_binomial_coefficient, icl_blank, icl_braced_group,
    icl_celsius, icl_centimeter, icl_cents, icl_change, icl_circle, icl_common_logarithm, icl_complex_square_root, icl_compound_name, icl_conditional_probability,
        icl_congruent, icl_conjugate, icl_constraint, icl_continued_fraction,
    icl_day_period, icl_defined_as, icl_degrees, icl_delimited_subexpression, icl_derivative_operator, icl_determinant, icl_diameter, icl_direction_of_approach,
        icl_discriminant, icl_distance, icl_divide, icl_dollar,
    icl_element_of, icl_ellipsis, icl_empty_set, icl_equal, icl_error_function, icl_euler_number, icl_evaluate, icl_evaluates_to, icl_exaannum,
    icl_factorial, icl_fenced_group, icl_final, icl_first_derivative, icl_focus, icl_foot, icl_fraction, icl_function_composition,
    icl_gas, icl_giga_base_pair, icl_giga_nucleotide, icl_gigaannum, icl_golden_ratio, icl_gram, icl_greater_than, icl_greater_than_or_equal,
        icl_greatest_common_divisor,
    icl_hypotenuse,
    icl_identically_equal, icl_identity_matrix, icl_iff, icl_imaginary_part, icl_imaginary_unit, icl_implies, icl_inch, icl_indexed_argument, icl_initial,
        icl_integral, icl_interchange_rows, icl_interquartile_range, icl_intersection, icl_interval, icl_inverse_function, icl_inverse_matrix,
    icl_kilo_nucleotide, icl_kiloannum, icl_kilogram, icl_kilometer, icl_kilonewton,
    icl_least_common_denominator, icl_least_common_multiple, icl_length_of_segment, icl_less_than, icl_less_than_or_equal, icl_limit, icl_line, icl_line_segment,
        icl_liquid, icl_list_separator, icl_liter,
    icl_magnitude, icl_matrix, icl_matrix_by, icl_matrix_order, icl_mean_absolute_deviation, icl_measure, icl_measure_of_angle, icl_mega_nucleotide,
        icl_megaannum, icl_meter, icl_miles_per_hour, icl_milliliter, icl_minus, icl_more_than,
    icl_natural_logarithm, icl_negated_operator, icl_negative, icl_negative_ion, icl_neutral, icl_not_element_of, icl_not_equal, icl_nth_derivative,
        icl_nucleotide, icl_number, icl_number_of, icl_number_set, icl_operator_range,
    icl_opposite, icl_or, icl_ordered_pair, icl_ordinal_mark, icl_ounce, icl_outcome,
    icl_parallel, icl_parenthetical, icl_particular_value_of, icl_percent, icl_permutation_symbol, icl_perpendicular, icl_petaannum, icl_ph, icl_pi,
        icl_piecewise, icl_plus, icl_plus_or_minus, icl_point, icl_point_at, icl_polynomial_arguments_degree_center, icl_position, icl_positive, icl_positive_ion,
        icl_pound, icl_power, icl_probability, icl_progression, icl_proper_subset_of, icl_proper_superset_of,
    icl_qualified_operator,
    icl_radian, icl_radius, icl_range_separator, icl_rate, icl_ratio, icl_ray, icl_real_numbers, icl_real_part, icl_rectangle, icl_remainder,
        icl_remainder_function, icl_repeating_digits, icl_root,
    icl_second_derivative, icl_sequence_range, icl_set, icl_set_difference, icl_shape, icl_side_angle_side, icl_side_side_side, icl_solid, icl_square,
        icl_square_root, icl_subset_of_or_equal, icl_such_that, icl_sum, icl_system_of_equations,
    icl_teraannum, icl_time_separator, icl_times, icl_ton, icl_transform, icl_translates_to, icl_translation, icl_transpose, icl_triangle,
        icl_triangle_similarity, icl_trigonometric_function, icl_union,
    icl_unit, icl_unit_vector,
    icl_variable, icl_vector, icl_velocity, icl_volume
} e_conlit;

typedef enum { con_line, con_none } e_connect;
typedef enum { ecc_contain, ecc_cover } e_contain_cover;
typedef enum { ce_gzip, ce_compress, ce_deflate, ce_identity } e_content_encoding;
typedef enum { cl_nodownload, cl_nofullscreen, cl_noremoteplayback } e_controlslist;
typedef enum { coo_expires, coo_maxage, coo_domain, coo_path, coo_secure, coo_httponly } e_cookieid;
typedef enum { c_none, c_html, c_hard, c_soft, c_copy, c_deduplicate, c_rpt } e_copy;
typedef enum { cr_same_origin, cr_same_site, cr_cross_origin } e_corp;
typedef enum { cc_anonymous, cc_credentials } ev_cors;

typedef enum { cou_context,
    cou_af, cou_ax, cou_al, cou_dz, cou_as, cou_ad, cou_ao, cou_ai, cou_aq, cou_ag, cou_ar, cou_am, cou_aw, cou_au, cou_at, cou_az, cou_bs, cou_bh, cou_bd, cou_bb, cou_by, cou_be, cou_bz, cou_bj,
    cou_bm, cou_bt, cou_bo, cou_bq, cou_ba, cou_bw, cou_bv, cou_br, cou_io, cou_bn, cou_bg, cou_bf, cou_bi, cou_cv, cou_kh, cou_cm, cou_ca, cou_ky, cou_cf, cou_td, cou_cl, cou_cn, cou_cx, cou_cc,
    cou_co, cou_km, cou_cd, cou_cg, cou_ck, cou_cr, cou_ci, cou_hr, cou_cu, cou_cw, cou_cy, cou_cz, cou_dk, cou_dj, cou_dm, cou_do, cou_ec, cou_eg, cou_sv, cou_gq, cou_er, cou_ee, cou_sz, cou_et,
    cou_fk, cou_fo, cou_fj, cou_fi, cou_fr, cou_gf, cou_pf, cou_tf, cou_ga, cou_gm, cou_ge, cou_de, cou_gh, cou_gi, cou_gr, cou_gl, cou_gd, cou_gp, cou_gu, cou_gt, cou_gg, cou_gn, cou_gw, cou_gy,
    cou_ht, cou_hm, cou_va, cou_hn, cou_hk, cou_hu, cou_is, cou_in, cou_id, cou_ir, cou_iq, cou_ie, cou_im, cou_il, cou_it, cou_jm, cou_jp, cou_je, cou_jo, cou_kz, cou_ke, cou_ki, cou_kp, cou_kr,
    cou_kw, cou_kg, cou_la, cou_lv, cou_lb, cou_ls, cou_lr, cou_ly, cou_li, cou_lt, cou_lu, cou_mo, cou_mk, cou_mg, cou_mw, cou_my, cou_mv, cou_ml, cou_mt, cou_mh, cou_mq, cou_mr, cou_mu, cou_yt,
    cou_mx, cou_fm, cou_md, cou_mc, cou_mn, cou_me, cou_ms, cou_ma, cou_mz, cou_mm, cou_na, cou_nr, cou_np, cou_nl, cou_nc, cou_nz, cou_ni, cou_ne, cou_ng, cou_nu, cou_nf, cou_mp, cou_no, cou_om,
    cou_pk, cou_pw, cou_ps, cou_pa, cou_pg, cou_py, cou_pe, cou_ph, cou_pn, cou_pl, cou_pt, cou_pr, cou_qa, cou_re, cou_ro, cou_ru, cou_rw, cou_bl, cou_sh, cou_kn, cou_lc, cou_mf, cou_pm, cou_vc,
    cou_ws, cou_sm, cou_st, cou_sa, cou_sn, cou_rs, cou_sc, cou_sl, cou_sg, cou_sx, cou_sk, cou_si, cou_sb, cou_so, cou_za, cou_gs, cou_ss, cou_es, cou_lk, cou_sd, cou_sr, cou_sj, cou_se, cou_ch,
    cou_sy, cou_tw, cou_tj, cou_tz, cou_th, cou_tl, cou_tg, cou_tk, cou_to, cou_tt, cou_tn, cou_tr, cou_tm, cou_tc, cou_tv, cou_ug, cou_ua, cou_ae, cou_gb, cou_um, cou_us, cou_uy, cou_uz, cou_vu,
    cou_ve, cou_vn, cou_vg, cou_vi, cou_wf, cou_eh, cou_ye, cou_zm, cou_zw, cou_error
} e_country;

typedef enum { cp_create, cp_match_parent } e_create_parent;
typedef enum { co_none, co_updiagonalstrike, co_downdiagonalstrike, co_verticalstrike, co_horizontalstrike } e_crossout;
typedef enum { crs_custom, crs_linear, crs_mediumcontrast, crs_strongcontrast } e_crs_tonecurvename;
typedef enum { cwb_asshot, cwb_auto, cwb_cloudy, cwb_custom, cwb_daylight, cwb_flash, cwb_flourescent, cwb_shade, cwb_tungsten } e_crs_whitebalance;
typedef enum { cs_compress, cs_stretch } e_cs;

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

typedef enum { caa_always, caa_auto, caa_avoid, caa_inherit, caa_left, caa_recto, caa_right, caa_verso } e_css_aaalri;
typedef enum { cai_auto, cai_avoid, cai_inherit } e_css_aai;
typedef enum { ecac_baseline, ecac_centre, ecac_flex_end, ecac_flex_start, ecac_space_around, ecac_space_between, ecac_space_evenly, ecac_stretch } e_css_align_content;
typedef enum { ecai_baseline, ecai_centre, ecai_flex_end, ecai_flex_start, ecai_stretch } e_css_align_items;
typedef enum { eat_any, eat_begins, eat_identical, eat_contains, eat_ends, eat_in_list, eat_is, eat_lang, eat_uncased } e_css_attribute_value;
typedef enum { ecas_inherit, eca_xx_small, eca_x_small, eca_small, eca_medium, eca_large, eca_x_large, eca_xx_large, eca_xxx_large } e_css_absolute_size;
typedef enum { all_inherit, all_initial, all_revert, all_revert_layer, all_unset } e_css_all_2;
typedef enum {  eca_auto, eca_button, eca_checkbox, eca_inherit, eca_listbox, eca_menulist, eca_menulist_button, eca_meter, eca_none, eca_progress_bar,
                eca_push_button, eca_radio, eca_searchfield, eca_slider_horizontal, eca_square_button, eca_textarea, eca_textfield,} e_css_appearance;
typedef enum { ecc_accumulate, ecc_add, ecc_replace } e_css_anim_comp;
typedef enum { ecd_alternative, scd_alternative_reverse, ecd_normal, ecd_reverse } e_css_anim_dir;
typedef enum { ecfm_backwards, ecfm_both, ecfm_forwards, ecfm_none } e_anim_fill_mode;
typedef enum { ecps_paused, ecps_running } e_css_anim_play_state;
typedef enum { cae_centre, cae_centre_left, cae_centre_right, cae_far_left, cae_far_right, cae_left, cae_left_side, cae_right, cae_right_side } e_css_azimuth_e;
typedef enum { cab_behind } e_css_azimuth_be;
typedef enum { lri_leftwards, lri_inherit, lri_rightwards } e_css_azimuth_lri;
typedef enum { ecba_inherit, ecba_fixed, ecba_local, ecba_scroll } e_css_background_attachment;
typedef enum { ecbr_inherit, ecbr_no_repeat, ecbr_repeat, ecbr_repeat_x, ecbr_repeat_y, ecbr_round, ecbr_space } e_css_background_repeat;
typedef enum {  ecbm_colour, colour_darken, ecbm_colour_burn, ecbm_colour_dodge, ecbm_darken, ecbm_difference, ecbm_exclusion, ecbm_hard_light, ecbm_hue, ecbm_lighten, ecbm_luminosity,
                ecbm_multiply, ecbm_normal, ecbm_overlay, ecbm_saturation, ecbm_screen, ecbm_soft_light } e_css_blend_mode;
typedef enum { cbc_collapse, cbc_inherit, cbc_separate } e_css_border_collapse;
typedef enum { cbii_repeat, cbii_round, cbii_space, cbii_stretch } e_css_border_image_repeat;
typedef enum { ecbs_inherit, ecb_dashed, ecb_dotted, ecb_double, ecb_groove, ecb_hidden, ecb_inset, ecb_none, ecb_outset, ecb_ridge, ecb_solid } e_css_border_style;
typedef enum { ecb_inherit, ecb_medium, ecb_thick, ecb_thin } e_css_border_width;
typedef enum { ebam_auto, ebam_baseline, ebam_centre, ebam_flex_end, ebam_flex_start, ebam_normal, ebam_stretch } e_css_box_alignself_mess;
typedef enum { cbo_block_axis, cbo_horizontal, cbo_inline_axis, cbo_vertical } e_css_box_orient;
typedef enum { ebx_border_box, ebx_content_box } e_css_box_sizing;
typedef enum { cbs_block_end, cbs_block_start, cbs_centre, cbs_first_baseline, cbs_last_baseline, cbs_none } e_css_box_snap;
typedef enum {  ecb_all, ecb_always, ecb_auto, ecb_avoid, ecb_avoid_column, ecb_avoid_page, ecb_avoid_region, ecb_column, ecb_left, ecb_page, ecb_recto,
                ecb_region, ecb_right, ecb_verso } e_css_break;
typedef enum { ecbb_clone, ecbb_slice } e_css_break_box;
typedef enum { ecbi_auto, ecbi_avoid, ecbi_avoid_column, ecbi_avoid_page, ecbi_avoid_region } e_css_break_inside;
typedef enum { ecsc_auto, ecsc_bar, ecsc_block, ecsc_inherit, ecsc_underscore } e_css_caret_shape;
typedef enum { ecc_inherit, ecc_block_end, ecc_block_start, ecc_both, ecc_bottom, ecc_inline_end, ecc_inline_start, ecc_left, ecc_none, ecc_right, ecc_top } e_css_clear;
typedef enum { cpb_fill_box, cpb_stroke_box, cpb_view_box } e_css_clip_path_box;
typedef enum {  csc_aliceblue, csc_antiquewhite, csc_aqua, csc_aquamarine, csc_azure, csc_beige, csc_bisque, csc_black, csc_blanchedalmond, csc_blue,
                csc_blueviolet, csc_brown, csc_burlywood, csc_cadetblue, csc_chartreuse, csc_chocolate, csc_coral, csc_cornflowerblue, csc_cornsilk,
                csc_crimson, csc_cyan, csc_darkblue, csc_darkcyan, csc_darkgoldenrod, csc_darkgray, csc_darkgreen, csc_darkgrey, csc_darkkhaki,
                csc_darkmagenta, csc_darkolivegreen, csc_darkorange, csc_darkorchid, csc_darkred, csc_darksalmon, csc_darkseagreen, csc_darkslateblue,
                csc_darkslategray, csc_darkslategrey, csc_darkturquoise, csc_darkviolet, csc_deeppink, csc_deepskyblue, csc_dimgray, csc_dimgrey,
                csc_dodgerblue, csc_firebrick, csc_floralwhite, csc_forestgreen, csc_fuchsia, csc_gainsboro, csc_ghostwhite, csc_gold, csc_goldenrod,
                csc_gray, csc_green, csc_greenyellow, csc_grey, csc_honeydew, csc_hotpink, csc_indianred, csc_indigo, csc_ivory, csc_khaki, csc_lavender,
                csc_lavenderblush, csc_lawngreen, csc_lemonchiffon, csc_lightblue, csc_lightcoral, csc_lightcyan, csc_lightgoldenrodyellow,
                csc_lightgray, csc_lightgreen, csc_lightgrey, csc_lightpink, csc_lightsalmon, csc_lightseagreen, csc_lightskyblue, csc_lightslategray,
                csc_lightslategrey, csc_lightsteelblue, csc_lightyellow, csc_lime, csc_limegreen, csc_linen, csc_magenta, csc_maroon,
                csc_mediumaquamarine, csc_mediumblue, csc_mediumorchid, csc_mediumpurple, csc_mediumseagreen, csc_mediumslateblue,
                csc_mediumspringgreen, csc_mediumturquoise, csc_mediumvioletred, csc_midnightblue, csc_mintcream, csc_mistyrose, csc_moccasin,
                csc_navajowhite, csc_navy, csc_oldlace, csc_olive, csc_olivedrab, csc_orange, csc_orangered, csc_orchid, csc_palegoldenrod,
                csc_palegreen, csc_paleturquoise, csc_palevioletred, csc_papayawhip, csc_peachpuff, csc_peru, csc_pink, csc_plum, csc_powderblue,
                csc_purple, csc_rebeccapurple , csc_red , csc_rosybrown, csc_royalblue, csc_saddlebrown, csc_salmon, csc_sandybrown, csc_seagreen,
                csc_seashell, csc_sienna, csc_silver, csc_skyblue, csc_slateblue, csc_slategray, csc_slategrey, csc_snow, csc_springgreen,
                csc_steelblue, csc_tan, csc_teal, csc_thistle, csc_tomato, csc_transparent, csc_turquoise, csc_violet, csc_wheat, csc_white, csc_whitesmoke,
                csc_yellow, csc_yellowgreen,
                csc_activeborder, csc_activecaption, csc_appworkspace, csc_background, csc_buttonface, csc_buttonhighlight, csc_buttonshadow,csc_buttontext,
                csc_captiontext, csc_greytext, csc_highlight, csc_highlighttext, csc_inactiveborder, csc_inactivecaption, csc_inactivecaptiontext,
                csc_infobackground, csc_infotext, csc_menu, csc_menutext, csc_scrollbar, csc_threeddarkshadow, csc_threedface, csc_threedhighlight,
                csc_threedlightshadow, csc_threedshadow, csc_window, csc_windowframe, csc_windowtext,
                csc_accentcolour, csc_accentcolourtext, csc_activetext, csc_buttonborder, csc_canvas, csc_canvastext, csc_field, csc_fieldtext, csc_linktext,
                csc_mark, csc_marktext, csc_selecteditem, csc_selecteditemtext, csc_visitedtext,
                csc_currentcolour } e_css_colour;
typedef enum { eco_add, eco_exclude, eco_intersect, eco_subtract } e_css_composite;
typedef enum { lps_inline_size, lps_layout, lps_paint, lps_size, lps_style } e_css_contain_e;
typedef enum { ccf_none, ccf_aspect_ratio, ccf_block_size, ccf_height, ccf_inline_size, ccf_orientation, ccf_width } e_css_container_feature;
typedef enum {  econ_whoopsie, econ_attr, econ_close_quote, econ_counter, econ_counters, econ_inherit, econ_open_quote, econ_no_close_quote,
                econ_no_open_quote, econ_url } e_css_content_enum;
typedef enum { ecse_auto, ecse_discard, ecse_fragments, ecse_overflow, ecse_paginate, ecse_webkit_discard } e_css_continue;
typedef enum { ccb_auto, ccb_avoid, ccb_avoid_flex, ccb_avoid_line, ccb_flex, ccb_line } e_css_control_break;
typedef enum { eccb_border_box, eccb_content_box, eccb_fill_box, eccb_match_parent, eccb_padding_box, eccb_stroke_box, eccb_view_box } e_css_coord_box;
typedef enum { eccp_centre, eccp_end, eccp_flex_end, eccp_flex_start, eccp_start } e_css_content_position;
typedef enum {  eccs_inherit, eccs_initial, eccs_none, eccs_revert, eccs_revert_layer, eccs_unset,
                eccs_arabic_indic, eccs_armenian, eccs_bengali, eccs_cambodian, eccs_circle, eccs_cjk_decimal, eccs_cjk_earthly_branch, eccs_cjk_heavenly_stem,
                eccs_decimal, eccs_decimal_leading_zero, eccs_devanagari, eccs_disc, eccs_disclosure_closed, eccs_disclosure_open, eccs_ethiopic_numeric, eccs_georgian,
                eccs_gujarati, eccs_gurmukhi, eccs_hebrew, eccs_hiragana, eccs_hiragana_iroha, eccs_japanese_formal, eccs_japanese_informal, eccs_kannada, eccs_katakana,
                eccs_katakana_iroha, eccs_khmer, eccs_korean_hangul_formal, eccs_korean_hanja_formal, eccs_korean_hanja_informal, eccs_lao, eccs_lower_alpha,
                eccs_lower_armenian, eccs_lower_greek, eccs_lower_latin, eccs_lower_roman, eccs_malayalam, eccs_mongolian, eccs_myanmar, eccs_oriya, eccs_persian,
                eccs_simp_chinese_formal, eccs_simp_chinese_informal, eccs_square, eccs_tamil, eccs_telugu, eccs_thai, eccs_tibetan, eccs_trad_chinese_formal,
                eccs_trad_chinese_informal, eccs_upper_alpha, eccs_upper_armenian, eccs_upper_latin, eccs_upper_roman } e_css_counter_style;
typedef enum {  ece_alias, ece_all_scroll, ece_auto,
                ece_cell, ece_context_menu, ece_copy, ece_crosshair,
                ece_default,
                ece_e_resize, ece_ew_resize,
                ece_grab, ece_grabbing,
                ece_help,
                ece_move,
                ece_n_resize, ece_ne_resize, ece_nesw_resize, ece_ns_resize, ece_nw_resize, ece_nwse_resize, ece_no_drop, ece_none, ece_not_allowed,
                ece_pointer, ece_progress,
                ece_resize,
                ece_s_resize, ece_se_resize, ece_sw_resize,
                ece_text,
                ece_vertical_text,
                ece_w_resize, ece_wait,
                ece_zoom_in, ece_zoom_out } e_css_cursor_e;
typedef enum { ecc_auto, ecc_balance, ecc_balance_all } e_css_column_fill;
typedef enum {  ecd_inherit,
                ecd_block,
                ecd_compact,
                ecd_flex, ecd_flex_inline,
                ecd_grid, ecd_grid_inline,
                ecd_inline, ecd_inline_block, ecd_inline_table,
                ecd_list_item,
                ecd_marker,
                ecd_none,
                ecd_ruby, ecd_ruby_base, ecd_ruby_base_container, ecd_ruby_text, ecd_ruby_text_container, ecd_run_in,
                ecd_table, ecd_table_caption, ecd_table_cell, ecd_table_column, ecd_table_column_group, ecd_table_footer_group, ecd_table_header_group,
                    ecd_table_row, ecd_table_row_group, } e_css_display;
typedef enum { ecdb_contents, ecdb_none } e_css_display_box;
typedef enum { ecdf_flow, ecdf_flow_root } e_css_display_flow;
typedef enum { ecdi_flex, ecdi_flex_inline, ecdi_flow, ecdi_flow_root, ecdi_grid, ecdi_grid_inline, ecdi_ruby, ecdi_table } e_css_display_inside;
typedef enum {  ecdi_ruby_base, ecdi_ruby_base_container, ecdi_ruby_text, ecdi_ruby_text_container, ecdi_table_caption, ecdi_table_cell, ecdi_table_column,
                ecdi_table_column_group, ecdi_table_footer_group, ecdi_table_header_group, ecdi_table_row, ecdi_table_row_group } e_css_display_internal;
typedef enum { ecdl_inline_block, ecdl_inline_flex, ecdl_inline_grid, ecdl_inline_table } e_css_display_legacy;
typedef enum { ecdo_block, ecdo_inline, ecdo_run_in } e_css_display_outside;
typedef enum { ece_important } e_css_earnest;
typedef enum { cee_above, cee_below, cee_higher, cee_inherit, cee_level, cee_lower } e_css_elevation_e;
typedef enum { cec_hide, cec_inherit, cec_show } e_css_empty_cells;
typedef enum { fca_auto, fca_none, fca_preserve } e_css_fca;
typedef enum {  cf_block_end, cf_block_start, cf_bottom, cf_inherit, cf_inline_end, cf_inline_start, cf_left, cf_none, cf_right,
                cf_snap_block, cf_snap_inline, cf_top } e_css_float;
typedef enum { ecfd_column, ecfd_column_reverse, ecfd_row, ecfd_row_reverse } e_css_flex_direction;
typedef enum { ecfw_nowrap, ecfw_wrap, ecfw_wrap_reverse } e_css_flex_wrap;
typedef enum { ecfd_auto, ecfd_block, ecfd_fallback, ecfd_optional, ecfd_swap } e_css_font_display;

// https://learn.microsoft.com/lb-lu/typography/opentype/spec/featurelist
typedef enum {  ecff_aalt, ecff_abvf, ecff_abvm, ecff_abvs, ecff_afrc, ecff_akhn, ecff_blwf, ecff_blwm, ecff_blws, ecff_calt,
                ecff_case, ecff_ccmp, ecff_cfar, ecff_chws, ecff_cjct, ecff_clig, ecff_cpct, ecff_cpsp, ecff_cswh, ecff_curs,
                ecff_cv01, ecff_cv02, ecff_cv03, ecff_cv04, ecff_cv05, ecff_cv06, ecff_cv07, ecff_cv08, ecff_cv09,
                ecff_cv10, ecff_cv11, ecff_cv12, ecff_cv13, ecff_cv14, ecff_cv15, ecff_cv16, ecff_cv17, ecff_cv18, ecff_cv19,
                ecff_cv20, ecff_cv21, ecff_cv22, ecff_cv23, ecff_cv24, ecff_cv25, ecff_cv26, ecff_cv27, ecff_cv28, ecff_cv29,
                ecff_cv30, ecff_cv31, ecff_cv32, ecff_cv33, ecff_cv34, ecff_cv35, ecff_cv36, ecff_cv37, ecff_cv38, ecff_cv39,
                ecff_cv40, ecff_cv41, ecff_cv42, ecff_cv43, ecff_cv44, ecff_cv45, ecff_cv46, ecff_cv47, ecff_cv48, ecff_cv49,
                ecff_cv50, ecff_cv51, ecff_cv52, ecff_cv53, ecff_cv54, ecff_cv55, ecff_cv56, ecff_cv57, ecff_cv58, ecff_cv59,
                ecff_cv60, ecff_cv61, ecff_cv62, ecff_cv63, ecff_cv64, ecff_cv65, ecff_cv66, ecff_cv67, ecff_cv68, ecff_cv69,
                ecff_cv70, ecff_cv71, ecff_cv72, ecff_cv73, ecff_cv74, ecff_cv75, ecff_cv76, ecff_cv77, ecff_cv78, ecff_cv79,
                ecff_cv80, ecff_cv81, ecff_cv82, ecff_cv83, ecff_cv84, ecff_cv85, ecff_cv86, ecff_cv87, ecff_cv88, ecff_cv89,
                ecff_cv90, ecff_cv91, ecff_cv92, ecff_cv93, ecff_cv94, ecff_cv95, ecff_cv96, ecff_cv97, ecff_cv98, ecff_cv99,
                ecff_c2pc, ecff_c2sc, ecff_dist, ecff_dlig, ecff_dnom, ecff_dtls, ecff_expt, ecff_falt, ecff_fin2, ecff_fin3,
                ecff_fina, ecff_flac, ecff_frac, ecff_fwid, ecff_half, ecff_haln, ecff_halt, ecff_hist, ecff_hkna, ecff_hlig,
                ecff_hngl, ecff_hojo, ecff_hwid, ecff_init, ecff_isol, ecff_ital, ecff_jalt, ecff_jp78, ecff_jp83, ecff_jp90,
                ecff_jp04, ecff_kern, ecff_lfbd, ecff_liga, ecff_ljmo, ecff_lnum, ecff_locl, ecff_ltra, ecff_ltrm, ecff_mark,
                ecff_med2, ecff_medi, ecff_mgrk, ecff_mkmk, ecff_mset, ecff_nalt, ecff_nlck, ecff_nukt, ecff_numr, ecff_onum,
                ecff_opbd, ecff_ordn, ecff_ornm, ecff_palt, ecff_pcap, ecff_pkna, ecff_pnum, ecff_pref, ecff_pres, ecff_pstf,
                ecff_psts, ecff_pwid, ecff_qwid, ecff_rand, ecff_rclt, ecff_rkrf, ecff_rlig, ecff_rphf, ecff_rtbd, ecff_rtla,
                ecff_rtlm, ecff_ruby, ecff_rvrn, ecff_salt, ecff_sinf, ecff_size, ecff_smcp, ecff_smpl, ecff_ss01, ecff_ss02,
                ecff_ss03, ecff_ss04, ecff_ss05, ecff_ss06, ecff_ss07, ecff_ss08, ecff_ss09, ecff_ss10, ecff_ss11, ecff_ss12,
                ecff_ss13, ecff_ss14, ecff_ss15, ecff_ss16, ecff_ss17, ecff_ss18, ecff_ss19, ecff_ss20, ecff_ssty, ecff_stch,
                ecff_subs, ecff_sups, ecff_swsh, ecff_titl, ecff_tjmo, ecff_tnam, ecff_tnum, ecff_trad, ecff_twid, ecff_unic,
                ecff_valt, ecff_vatu, ecff_vchw, ecff_vert, ecff_vhal, ecff_vjmo, ecff_vkna, ecff_vkrn, ecff_vpal, ecff_vrt2,
                ecff_vrtr, ecff_zero } e_css_font_feature;

typedef enum {  efsa_cap_height, efsa_ch_width, efsa_ex_height, efsa_ic_height, efsa_ic_width } e_css_font_size_adjust_e;
typedef enum {  ecft_colour_cbdt, ecft_colour_colrv0, ecft_colour_colrv1, ecft_colour_sbix, ecft_colour_svg, ecft_feature_aat, ecft_feature_graphite, ecft_feature_opentype, ecft_incremental,
                ecft_palette, ecft_variations } e_css_font_tech;
typedef enum { ecfn_down, ecfn_nearest, ecfn_to_zero, ecfn_up } e_css_fn_round_t;
typedef enum { ecfw_all, ecfw_normal, ecfw_bold, ecfw_bolder, ecfw_lighter, ecfw_100, ecfw_200, ecfw_300, ecfw_400, ecfw_500, ecfw_600, ecfw_700, ecfw_800, ecfw_900, ecfw_inherit } e_css_font_weight;
typedef enum {  efn_none, efn_webkit_autofill,
                efn_above_level, efn_active, efn_after, efn_any_link, efn_at_level, efn_attr, efn_auto, efn_autofill,
                efn_backdrop, efn_before, efn_below_level, efn_blank, efn_buffering,
                efn_checked, efn_circle, efn_closed, efn_content, efn_cubic_bezier, efn_cue, efn_cue_region, efn_current,
                efn_default, efn_defined, efn_dir, efn_disabled,
                efn_ellipse, efn_empty, efn_enabled,
                efn_file_selector_button, efn_first, efn_first_child, efn_first_letter, efn_first_line, efn_first_of_type, efn_focus,
                    efn_focus_visible, efn_focus_within, efn_fullscreen, efn_future,
                efn_grammar_error,
                efn_has, efn_highlight, efn_host, efn_host_context, efn_hover,
                efn_image, efn_indeterminate, efn_in_range, efn_inset, efn_invalid, efn_is,
                efn_lang, efn_last_child, efn_last_of_type, efn_left, efn_link, efn_local_link,
                efn_marker, efn_modal, efn_muted,
                efn_not, efn_nth_child, efn_nth_col, efn_nth_fragment, efn_nth_last_child, efn_nth_last_col, efn_nth_last_of_type, efn_nth_of_type,
                efn_only_child, efn_only_of_type, efn_open, efn_optional, efn_out_of_range,
                efn_part, efn_past, efn_paused, efn_picture_in_picture, efn_placeholder, efn_placeholder_shown, efn_playing, efn_polygon, efn_popover_open,
                efn_read_only, efn_read_write, efn_recto, efn_region, efn_required, efn_right, efn_root,
                efn_scope, efn_seeking, efn_selection, efn_shadow, efn_slotted, efn_spelling_error, efn_stalled, efn_state,
                efn_target, efn_target_text, efn_target_within,
                efn_user_invalid, efn_user_valid,
                efn_valid, efn_verso, efn_view_transition, efn_view_transition_group, efn_view_transition_new, efn_view_transition_old,
                    efn_view_transition_image_pair, efn_visited, efn_volume_locked,
                efn_where,
                efn_xywh } e_css_fn;
typedef enum { ecff_collection, ecff_embedded_opentype, ecff_intellifont, ecff_opentype, ecff_speedo, ecff_svg, ecf_truedoc_pfr, ecff_truetype, ecff_truetype_gx, ecff_type_1, ecff_woff, ecff_woff2 } e_css_font_format;
typedef enum { ecfk_auto, ecfk_none, ecfk_normal } e_css_font_kerning;
typedef enum { ecfs_normal, ecfs_italic, ecfs_oblique, ecfs_inherit } e_css_font_style_e;
typedef enum {  ecfv_acnt, ecfv_ankr, ecfv_avar, ecfv_base, ecfv_bdat, ecfv_bhed, ecfv_bloc, ecfv_bsln, ecfv_cbdt, ecfv_cblc, ecfv_cff, ecfv_cff2, ecfv_cmap,
                ecfv_colr, ecfv_cpal, ecfv_cvar, ecfv_cvt, ecfv_dsig, ecfv_ebdt, ecfv_eblc, ecfv_ebsc, ecfv_fdsc, ecfv_feat, ecfv_fmtx, ecfv_fond, ecfv_fpgm,
                ecfv_fvar, ecfv_gasp, ecfv_gcid, ecfv_gdef, ecfv_glyf, ecfv_gpos, ecfv_gsub, ecfv_gvar, ecfv_hdmx, ecfv_head, ecfv_hhea, ecfv_hmtx, ecfv_hvar,
                ecfv_jstf, ecfv_just, ecfv_kern, ecfv_kerx, ecfv_lcar, ecfv_loca, ecfv_ltag, ecfv_ltsh, ecfv_math, ecfv_maxp, ecfv_merg, ecfv_meta, ecfv_mort,
                ecfv_morx, ecfv_mvar, ecfv_name, ecfv_opbd, ecfv_os_2, ecfv_pclt, ecfv_post, ecfv_prep, ecfv_prop, ecfv_sbix, ecfv_stat, ecfv_svg, ecfv_trak,
                ecfv_vdmx, ecfv_vhea, ecfv_vmtx, ecfv_vorg, ecfv_vvar, ecfv_xref, ecfv_zapf } e_css_font_variation;
typedef enum {  ecgf_inherit, ecf_cursive, ecf_emoji, ecf_fangsong, ecf_fantasy, ecf_math, ecf_monospace, ecf_sans_serif, ecf_serif, ecf_system_ui, ecf_ui_monospace, ecf_ui_rounded,
                ecf_ui_sans_serif, ecf_ui_serif } e_css_generic_family;
typedef enum { hll_always, hll_column, hll_none, hll_page, hll_spread } e_css_hll;
typedef enum { cip_flip, cip_from_image, cip_none } e_css_image_proc_e;
typedef enum { ila_alphabetic, ila_hanging, ila_ideographic, ila_leading } e_css_initial_letter_align;
typedef enum { ilw_all, ilw_first, ilw_grid, ilw_none } e_css_initial_letter_wrap_e;
typedef enum { cib1_alphabetic, cib1_cap, cib1_ex, cib1_ideographic, cib1_ideographic_ink, cib1_text } e_css_inline_bem_1;
typedef enum { cib2_alphabetic, cib2_ideographic, cib2_ideographic_ink, cib2_text } e_css_inline_bem_2;
typedef enum { ehi_decreasing, ehi_increasing, ehi_longer, ehi_shorter } e_css_hue_interpolation;
typedef enum { eci_auto, eci_isolate } e_css_isolation;
typedef enum { ejc_centre, ejc_flex_end, ejc_flex_start, ejc_space_around, ejc_space_between, ejc_space_evenly, ejc_stretch } e_css_justify_content;
typedef enum { eclb_border_box, eclb_content_box, eclb_margin_box, eclb_padding_box } e_css_layout_box;
typedef enum { clb_anywhere, clb_auto, clb_loose, clb_normal, clb_strict } e_css_line_break;
typedef enum {  ecls_inherit, ecl_circle, ecl_decimal, ecl_disc, ecl_lower_alpha, ecl_lower_roman, ecl_none, ecl_square, ecl_upper_alpha, ecl_upper_roman,
                ecl_hebrew, ecl_armenian, ecl_georgian, ecl_cjk_ideographic, ecl_hiragana, ecl_katakana, ecl_hira_gana_iroha, ecl_katakana_iroha } e_css_list_style_type;
typedef enum { eclp_inherit, ecp_inside, ecp_outside } e_css_list_style_position;
typedef enum { ecmb_auto, ecmb_discard, ecmb_keep } e_css_margin_break;
typedef enum { emti_block_end, emti_block_start, emti_inline_end, emti_inline_start } e_css_margin_trim_inner;
typedef enum { ecm_crop, ecm_cross } e_css_mark;
typedef enum { mbm_alpha, mbm_luminance } e_css_mask_border_mode;
typedef enum { mbr_repeat, mbr_round, mbr_space, mbd_stretch } e_css_mask_border_repeat;
typedef enum { cmm_alpha, cmm_luminance, cmm_match_source } e_css_masking_mode;
typedef enum { esz_auto, esz_inherit, esz_landscape, esz_portrait } e_css_orientation;
typedef enum { eco_auto, eco_hidden, eco_inherit, eco_scroll, eco_visible } e_css_overflow;
typedef enum { cos_auto, cos_marquee_block, cos_marquee_line } e_css_overflow_style;
typedef enum { epe_medium, epe_none, epe_strong, epe_weak, epe_xweak, epe_xstrong } e_css_pause_3_e;
typedef enum { ecpb_border_box, ecpb_content_box, ecpb_fill_box, ecpb_padding_box, ecpb_stroke_box } e_css_paint_box;
typedef enum { epi_high, epi_inherit, epi_low, epi_medium, epi_x_high, epi_x_low } e_css_pitch_e;
typedef enum { epo_hsl, epo_hwb, epo_lch, epo_oklch } e_css_polar;
typedef enum { ecp_absolute, ecp_fixed, ecp_inherit, ecp_relative, ecp_static, ecp_sticky } e_css_position;
typedef enum {  ec_unknown, ec_context, ec_custom, ec_inherit,
                ec_and, ec_not, ec_or,
                ec_accent_colour, ec_additive_symbols, ec_align_content, ec_align_items, ec_align_self, ec_alignment_baseline, ec_all,
                    ec_altglyph, ec_anchor_default, ec_anchor_name, ec_anchor_scroll, 
                    ec_animation, ec_animation_composition, ec_animation_delay, ec_animation_direction,
                    ec_animation_duration, ec_animation_fill_mode, ec_animation_iteration_count, ec_animation_name, ec_animation_play_state,
                    ec_animation_range, ec_animation_range_end, ec_animation_range_start, ec_animation_timeline, ec_animation_timing_function,
                    ec_appearance, ec_ascent, ec_ascent_override, ec_aspect_ratio, ec_audio_level, ec_azimuth,
                ec_backface_visibility, ec_background, ec_background_attachment, ec_background_blend_mode,
                    ec_background_clip, ec_background_colour, ec_background_image, ec_background_origin,
                    ec_background_position, ec_background_repeat, ec_background_size, ec_baseline,
                    ec_baseline_shift, ec_baseline_source, ec_base_palette, ec_bbox, ec_bleed, ec_block_ellipsis, ec_block_size, ec_block_step,
                    ec_block_step_align, ec_block_step_insert, ec_block_step_round, ec_block_step_size, ec_bookmark_label, ec_bookmark_level,
                    ec_bookmark_state, ec_border, ec_border_block, ec_border_block_colour, ec_border_block_end, ec_border_block_end_colour,
                    ec_border_block_end_style, ec_border_block_end_width, ec_border_block_start, ec_border_block_start_colour, ec_border_block_start_style,
                    ec_border_block_start_width, ec_border_block_style, ec_border_block_width, ec_border_bottom,ec_border_bottom_colour,
                    ec_border_bottom_left_radius, ec_border_bottom_right_radius, ec_border_bottom_style, ec_border_bottom_width, ec_border_boundary,
                    ec_border_collapse, ec_border_colour, ec_border_end_end_radius, ec_border_end_start_radius, ec_border_image, ec_border_image_outset,
                    ec_border_image_repeat, ec_border_image_slice, ec_border_image_source, ec_border_image_width, ec_border_inline, ec_border_inline_colour,
                    ec_border_inline_end, ec_border_inline_end_colour, ec_border_inline_end_style, ec_border_inline_end_width, ec_border_inline_start,
                    ec_border_inline_start_colour, ec_border_inline_start_style, ec_border_inline_start_width, ec_border_inline_style,
                    ec_border_inline_width, ec_border_left, ec_border_left_colour, ec_border_left_style, ec_border_left_width, ec_border_radius,
                    ec_border_right, ec_border_right_colour, ec_border_right_style, ec_border_right_width, ec_border_spacing, ec_border_start_end_radius,
                    ec_border_start_start_radius, ec_border_style, ec_border_top, ec_border_top_colour, ec_border_top_left_radius, ec_border_top_right_radius,
                    ec_border_top_style, ec_border_top_width, ec_border_width, ec_bottom, ec_box_decoration_break, ec_box_shadow,
                    ec_box_sizing, ec_box_snap, ec_break_after, ec_break_before, ec_break_inside, ec_buffered_rendering,
                ec_cap_height, ec_caption_side, ec_caret, ec_caret_colour, ec_caret_shape, ec_centre_line, ec_chains, ec_clear, ec_clip, ec_clip_path,
                    ec_clippath, ec_clip_rule, ec_cliprule, ec_colour, ec_colour_adjust, ec_colour_interpolation, ec_colour_interpolation_filters, ec_colour_profile,
                    ec_colour_rendering, ec_colour_scheme, ec_column_count, ec_column_fill, ec_column_gap, ec_column_rule, ec_column_rule_colour,
                    ec_column_rule_style, ec_column_rule_width, ec_column_span, ec_column_width, ec_columns, ec_contain, ec_contain_intrinsic_block_size,
                    ec_contain_intrinsic_height, ec_contain_intrinsic_inline_size, ec_contain_intrinsic_size, ec_contain_intrinsic_width, ec_container,
                    ec_container_name, ec_container_type, ec_content, ec_content_visibility, ec_continue, ec_counter_increment, ec_counter_reset,
                    ec_counter_set, ec_cue, ec_cue_after, ec_cue_before, ec_cursor, ec_cx, ec_cy,
                ec_d, ec_definition_src, ec_descent, ec_descent_override, ec_direction, ec_display, ec_display_align, ec_dominant_baseline,
                ec_elevation, ec_empty_cells, ec_enable_background,
                ec_fallback, ec_fill, ec_fill_break, ec_fill_colour, ec_fill_image, ec_fill_opacity, ec_fill_origin, ec_fill_params, ec_fill_position, ec_fill_repeat,
                    ec_fillrule, ec_fill_rule, ec_fill_size, ec_filter, ec_flex, ec_flex_basis, ec_flex_direction, ec_flex_flow, ec_flex_grow, ec_flex_shrink,
                    ec_flex_wrap, ec_float, ec_float_defer, ec_float_offset, ec_float_reference, ec_flood_colour, ec_flood_opacity, ec_flow, ec_flow_from,
                    ec_flow_into, ec_font, ec_font_display, ec_font_family, ec_font_feature_settings, ec_font_kerning, ec_font_language_override,
                    ec_font_named_instance, ec_font_optical_sizing, ec_font_palette, ec_font_size, ec_font_size_adjust, ec_font_stretch, ec_font_style,
                    ec_font_synthesis, ec_font_synthesis_small_caps, ec_font_synthesis_style, ec_font_synthesis_weight, ec_font_variant,
                    ec_font_variant_alternatives, ec_font_variant_caps, ec_font_variant_east_asian, ec_font_variant_emoji, ec_font_variant_ligatures,
                    ec_font_variant_numeric, ec_font_variant_position, ec_font_variation_settings, ec_font_weight, ec_footnote_display, ec_footnote_policy,
                    ec_forced_colour_adjust,
                ec_gap, ec_glyph_orientation_horizontal, ec_glyph_orientation_vertical, ec_grid, ec_grid_area, ec_grid_auto_columns, ec_grid_auto_flow,
                    ec_grid_auto_rows, ec_grid_column, ec_grid_column_end, ec_grid_column_start, ec_grid_row, ec_grid_row_end, ec_grid_row_start,
                    ec_grid_template, ec_grid_template_areas, ec_grid_template_columns, ec_grid_template_rows,
                ec_hanging_punctuation, ec_height, ec_hyphenate_character, ec_hyphenate_limit_chars, ec_hyphenate_limit_last, ec_hyphenate_limit_lines,
                    ec_hyphenate_limit_zone, ec_hyphens,
                ec_icc_profile, ec_image_orientation, ec_image_rendering, ec_image_resolution, ec_initial_letter, ec_initial_letter_align,
                    ec_initial_letter_wrap, ec_inline_size, ec_inline_sizing, ec_inset, ec_inset_block, ec_inset_block_end, ec_inset_block_start,
                    ec_inset_inline, ec_inset_inline_end, ec_inset_inline_start, ec_isolation,
                ec_justify_content, ec_justify_items, ec_justify_self,
                ec_kerning,
                ec_leading_trim, ec_left, ec_letter_spacing, ec_lighting_colour, ec_line_break, ec_line_clamp, ec_line_gap_override, ec_line_grid,
                    ec_line_height, ec_line_height_step, ec_line_increment, ec_line_padding, ec_line_snap, ec_list_style, ec_list_style_image,
                    ec_list_style_position, ec_list_style_type,
                ec_margin, ec_margin_block, ec_margin_block_end, ec_margin_block_start, ec_margin_bottom, ec_margin_break, ec_margin_inline,
                    ec_margin_inline_end, ec_margin_inline_start, ec_margin_left, ec_margin_right, ec_margin_top, ec_margin_trim, ec_marker,
                    ec_marker_end, ec_marker_knockout_left, ec_marker_knockout_right, ec_marker_mid, ec_marker_offset, ec_marker_pattern, ec_marker_segment,
                    ec_marker_side, ec_marker_start, ec_marks, ec_mask,
                    ec_mask_border, ec_mask_border_mode, ec_mask_border_outset, ec_mask_border_repeat, ec_mask_border_slice, ec_mask_border_source,
                    ec_mask_border_width, ec_mask_clip, ec_mask_composite, ec_mask_image, ec_mask_mode, ec_mask_origin, ec_mask_position, ec_mask_repeat,
                    ec_mask_size, ec_mask_type, ec_mathline, ec_max_block_size, ec_max_height, ec_max_inline_size, ec_max_lines, ec_max_width, ec_max_zoom,
                    ec_min_block_size, ec_min_height, ec_min_inline_size, ec_min_intrinsic_sizing, ec_min_width, ec_min_zoom, ec_mix_blend_mode,
                ec_name, ec_nav_down, ec_nav_left, ec_nav_right, ec_nav_up, ec_negative,
                ec_object_fit, ec_object_position, ec_offset, ec_offset_anchor, ec_offset_distance, ec_offset_path, ec_offset_position, ec_offset_rotate,
                    ec_orientation, ec_opacity, ec_order, ec_orphans, ec_outline, ec_outline_colour, ec_outline_offset, ec_outline_style, ec_outline_width,
                    ec_overflow, ec_overflow_anchor, ec_overflow_block, ec_overflow_clip_margin, ec_overflow_clip_margin_block,
                    ec_overflow_clip_margin_block_end, ec_overflow_clip_margin_block_start, ec_overflow_clip_margin_bottom, ec_overflow_clip_margin_inline,
                    ec_overflow_clip_margin_inline_end, ec_overflow_clip_margin_inline_start, ec_overflow_clip_margin_left, ec_overflow_clip_margin_right,
                    ec_overflow_clip_margin_top, ec_overflow_inline, ec_overflow_wrap, ec_overflow_x, ec_overflow_y, ec_override_colours,
                    ec_overscroll_behavior, ec_overscroll_behavior_block, ec_overscroll_behavior_inline, ec_overscroll_behavior_x, ec_overscroll_behavior_y,
                ec_pad, ec_padding, ec_padding_block, ec_padding_block_end, ec_padding_block_start, ec_padding_bottom, ec_padding_inline,
                    ec_padding_inline_end, ec_padding_inline_start, ec_padding_left, ec_padding_right, ec_padding_top, ec_page_break_after,
                    ec_page_break_before, ec_page_break_inside, ec_page_property, ec_paint_order, ec_page_orientation, ec_panose_1, ec_pause, ec_pause_after,
                    ec_pause_before, ec_perspective, ec_perspective_origin, ec_pitch, ec_pitch_range, ec_place_content, ec_place_items, ec_place_self,
                    ec_play_during, ec_pointer_events, ec_position, ec_position_fallback, ec_position_fallback_bounds, ec_prefix, ec_presentation_level,
                    ec_print_colour_adjust,
                ec_quotes,
                ec_r, ec_range, ec_region_fragment, ec_rendering_intent, ec_resize, ec_rest, ec_rest_after, ec_rest_before, ec_richness, ec_right, ec_rotate,
                    ec_row_gap, ec_ruby_align, ec_ruby_merge, ec_ruby_overhang, ec_ruby_position, ec_running, ec_rx, ec_ry,
                ec_scale, ec_scroll_behaviour, ec_scroll_margin, ec_scroll_margin_block, ec_scroll_margin_block_end, ec_scroll_margin_block_start,
                    ec_scroll_margin_bottom, ec_scroll_margin_inline, ec_scroll_margin_inline_end, ec_scroll_margin_inline_start, ec_scroll_margin_left,
                    ec_scroll_margin_right, ec_scroll_margin_top, ec_scroll_padding, ec_scroll_padding_block, ec_scroll_padding_block_end,
                    ec_scroll_padding_block_start, ec_scroll_padding_bottom, ec_scroll_padding_inline, ec_scroll_padding_inline_end,
                    ec_scroll_padding_inline_start, ec_scroll_padding_left, ec_scroll_padding_right, ec_scroll_padding_top, ec_scroll_snap_align,
                    ec_scroll_snap_stop, ec_scroll_snap_type, ec_scroll_timeline, ec_scroll_timeline_axis, ec_scroll_timeline_name, ec_scrollbar_colour,
                    ec_scrollbar_gutter, ec_scrollbar_width, ec_shape_image_threshold, ec_shape_inside, ec_shape_margin, ec_shape_outside, ec_shape_padding,
                    ec_shape_rendering, ec_shape_subtract, ec_size, ec_size_adjust, ec_slope, ec_solid_colour, ec_solid_opacity, ec_spatial_navigation_action,
                    ec_spatial_navigation_contain, ec_spatial_navigation_function, ec_speak, ec_speak_as, ec_speak_header, ec_speak_numeral,
                    ec_speak_punctuation, ec_speech_rate, ec_src, ec_stemh, ec_stemv, ec_stress, ec_string_set, ec_stop_colour, ec_stop_opacity, ec_stroke,
                    ec_stroke_align, ec_stroke_alignment, ec_stroke_break, ec_stroke_colour, ec_stroke_dashadjust, ec_stroke_dasharray, ec_stroke_dashcorner,
                    ec_stroke_dash_corner, ec_stroke_dash_justify, ec_stroke_dashoffset,
                    ec_stroke_image, ec_stroke_linecap, ec_stroke_linejoin, ec_stroke_miterlimit, ec_stroke_opacity, ec_stroke_origin, ec_stroke_params,
                    ec_stroke_position, ec_stroke_repeat, ec_stroke_size, ec_stroke_width, ec_subscript_position_override, ec_subscript_size_override,
                    ec_suffix, ec_superscript_position_override, ec_superscript_size_override, ec_symbols, ec_system,
                ec_tab_size, ec_table_layout, ec_text_align, ec_text_align_all, ec_text_align_last, ec_text_anchor, ec_text_autospace, ec_text_box_edge,
                    ec_text_box_trim, ec_text_combine_upright, ec_text_decoration, ec_text_decoration_colour, ec_text_decoration_line, ec_text_decoration_skip,
                    ec_text_decoration_skip_box, ec_text_decoration_skip_ink, ec_text_decoration_skip_inset, ec_text_decoration_skip_self,
                    ec_text_decoration_skip_spaces, ec_text_decoration_style, ec_text_decoration_thickness, ec_text_definition, ec_text_emphasis,
                    ec_text_emphasis_colour, ec_text_emphasis_position, ec_text_emphasis_skip, ec_text_emphasis_style, ec_text_group_align, ec_text_indent,
                    ec_text_justify, ec_text_orientation, ec_text_overflow, ec_text_rendering, ec_text_resize, ec_text_shadow,
                    ec_text_spacing, ec_text_spacing_trim, ec_text_transform, ec_text_underline_offset, ec_text_underline_position, ec_text_wrap,
                    ec_timeline_scope, ec_top, ec_topline, ec_transform, ec_transform_box, ec_transform_origin, ec_transform_style, ec_transition,
                    ec_text_wrap_mode, ec_text_wrap_style, ec_transition_behaviour, ec_transition_delay, ec_transition_duration, ec_transition_property,
                    ec_transition_timing_function, ec_translate,
                ec_unicode_bidi, ec_unicode_range, ec_units_per_em, ec_user_modify, ec_user_select, ec_user_zoom,
                ec_vector_effect, ec_vertical_align, ec_view_timeline, ec_view_timeline_axis, ec_view_timeline_inset, ec_view_timeline_name,
                    ec_view_transition_name, ec_viewport_fill, ec_viewport_fill_opacity, ec_viewport_fit, ec_visibility, ec_voice_balance, ec_voice_duration,
                    ec_voice_family, ec_voice_pitch, ec_voice_range, ec_voice_rate, ec_voice_stress, ec_voice_volume, ec_volume,
                ec_white_space, ec_white_space_collapse, ec_white_space_trim, ec_widows, ec_width, ec_widths, ec_will_change, ec_word_boundary_detection,
                    ec_word_boundary_expansion, ec_word_break, ec_word_space_transform, ec_word_spacing, ec_word_wrap, ec_wrap_after, ec_wrap_before,
                    ec_wrap_flow, ec_wrap_inside, ec_wrap_through, ec_writing_mode,
                ec_x, ec_x_height,
                ec_y,
                ec_z_index, ec_zoom,

                // old abandoned properties from https://www.w3.org/Style/CSS/all-properties.en.html
                ec_all_space_treatment, ec_animation_delay_end, ec_animation_delay_start,
                ec_background_break, ec_background_image_transform, ec_background_quantity, ec_background_spacing, ec_bikeshedding, ec_block_overflow,
                ec_block_progression, ec_bookmark_target, ec_border_break, ec_border_image_transform, ec_border_length, ec_box_align, ec_box_break, ec_box_direction,
                ec_box_flex, ec_box_flex_group, ec_box_height, ec_box_lines, ec_box_ordinal_group, ec_box_orient, ec_box_pack, ec_box_suppress, ec_box_width,
                ec_caret_animation, ec_clear_after, ec_column_break_after, ec_column_break_before, ec_content_order, ec_crop,
                ec_display_box, ec_display_extras, ec_display_inside, ec_display_list, ec_display_model, ec_display_outside, ec_display_role,
                ec_feBlend, ec_feColorMatrix, ec_feComponentTransfer, ec_feComposite, ec_feConvolveMatrix, ec_feCustom, ec_feCustomParam, ec_feCustomSource,
                ec_feDiffuseLighting, ec_feDisplacementMap, ec_feDistantLight, ec_feDropShadow, ec_feFlood, ec_feFuncA, ec_feFuncB, ec_feFuncG, ec_feFuncR,
                ec_feGaussianBlur, ec_feImage, ec_feMerge, ec_feMergeNode, ec_feMorphology, ec_feOffset, ec_fePointLight, ec_feSpecularLighting, ec_feSpotLight,
                ec_feTile, ec_feTurbulence, ec_feUnsharpMask, ec_filter_margin, ec_filter_margin_bottom, ec_filter_margin_left, ec_filter_margin_right,
                ec_filter_margin_top, ec_fit, ec_fit_position, ec_flex_align, ec_flex_item_align, ec_flex_line_pack, ec_flex_order, ec_flex_pack, ec_float_displace,
                ec_float_displace__alternative_2, ec_float_displace__alternative_3, ec_font_max_size, ec_font_min_size, ec_font_presentation,
                ec_grid_after, ec_grid_auto_position, ec_grid_before, ec_grid_cell, ec_grid_cell_stacking, ec_grid_column_align,
                ec_grid_column_gap, ec_grid_column_position, ec_grid_column_sizing, ec_grid_column_span, ec_grid_columns, ec_grid_definition_columns,
                ec_grid_definition_rows, ec_grid_end, ec_grid_flow, ec_grid_gap, ec_grid_position, ec_grid_row_align, ec_grid_row_gap, ec_grid_row_position,
                ec_grid_row_sizing, ec_grid_row_span, ec_grid_rows, ec_grid_span, ec_grid_start,
                ec_hyphenate, ec_hyphenate_after, ec_hyphenate_before, ec_hyphenate_dictionary, ec_hyphenate_limit_after, ec_hyphenate_limit_before,
                ec_hyphenate_lines, ec_hyphenate_resource,
                ec_icon, ec_ime_mode, ec_indent_edge_reset, ec_initial_letters, ec_initial_letters_align, ec_initial_letters_wrap,
                ec_kerning_mode, ec_kerning_pair_threshold, ec_key_equivalent,
                ec_leading_trim_over, ec_leading_trim_under, ec_line_grid_mode, ec_line_grid_progression, ec_line_sizing, ec_line_slack,
                ec_linefeed_treatment,
                ec_mark, ec_mark_after, ec_mark_before, ec_marquee, ec_marquee_direction, ec_marquee_loop, ec_marquee_play_count, ec_marquee_repetition,
                ec_marquee_speed, ec_marquee_style, ec_mask_box, ec_mask_box_image, ec_mask_box_image_outset, ec_mask_box_image_repeat, ec_mask_box_image_slice,
                ec_mask_box_image_source, ec_mask_box_image_width, ec_mask_box_outset, ec_mask_box_repeat, ec_mask_box_slice, ec_mask_box_source, ec_mask_box_width,
                ec_mask_source_type, ec_max_font_size, ec_min_font_size, ec_motion, ec_motion_offset, ec_motion_path, ec_motion_rotation,
                ec_move_to,
                ec_nav_index,
                ec_offset_after, ec_offset_before, ec_offset_end, ec_offset_start, ec_overflow_clip, ec_overflow_style,
                ec_page_policy, ec_page_transition_tag, ec_phonemes, ec_polar_anchor, ec_polar_angle, ec_polar_distance, ec_polar_origin,
                ec_punctuation_trim,
                ec_region_overflow, ec_resizer, ec_resolution, ec_rotation, ec_rotation_point,
                ec_scroll_snap_coordinate, ec_scroll_snap_destination, ec_scroll_snap_margin, ec_scroll_snap_margin_block, ec_scroll_snap_margin_block_end,
                ec_scroll_snap_margin_block_start, ec_scroll_snap_margin_bottom, ec_scroll_snap_margin_inline, ec_scroll_snap_margin_inline_end,
                ec_scroll_snap_margin_inline_start, ec_scroll_snap_margin_left, ec_scroll_snap_margin_right, ec_scroll_snap_margin_top, ec_scroll_snap_padding,
                ec_scroll_snap_padding_block, ec_scroll_snap_padding_block_end, ec_scroll_snap_padding_block_start, ec_scroll_snap_padding_bottom,
                ec_scroll_snap_padding_inline, ec_scroll_snap_padding_inline_end, ec_scroll_snap_padding_inline_start, ec_scroll_snap_padding_left,
                ec_scroll_snap_padding_right, ec_scroll_snap_padding_top, ec_scroll_snap_points_x, ec_scroll_snap_points_y, ec_scroll_timeline_attachment,
                ec_something_or_other, ec_speakability,
                ec_tab_side, ec_target, ec_target_name, ec_target_new, ec_target_position, ec_text_align_first, ec_text_blink, ec_text_block_indent,
                ec_text_combine, ec_text_combine_horizontal, ec_text_combine_mode, ec_text_decoration_width, ec_text_edge, ec_text_first_indent,
                ec_text_justify_trim, ec_text_kashida_space, ec_text_line_through, ec_text_line_through_color, ec_text_line_through_mode,
                ec_text_line_through_style, ec_text_line_through_width, ec_text_outline, ec_text_overflow_ellipsis, ec_text_overflow_mode, ec_text_overline,
                ec_text_overline_color, ec_text_overline_mode, ec_text_overline_style, ec_text_overline_width, ec_text_replace, ec_text_script,
                ec_text_space_collapse, ec_text_space_trim, ec_text_trim, ec_text_underline, ec_text_underline_color, ec_text_underline_mode,
                ec_text_underline_style, ec_text_underline_width,
                ec_var, ec_vertical_position, ec_view_timeline_attachment, ec_voice_pitch_range,
                ec_white_space_collapsing, ec_white_space_treatment, ec_word_break_cjk,
                ec_word_break_inside, ec_wrap, ec_wrap_margin, ec_wrap_option, ec_wrap_padding,

                // additional abandoned properties per https://developer.mozilla.org/en-US/docs/Web/CSS/Reference#index
                ec_align_tracks,

                // https://developer.mozilla.org/en-US/docs/Web/CSS/Webkit_Extensions
                // https://developer.mozilla.org/en-US/docs/Web/CSS/Mozilla_Extensions
                ec_epub_text_decoration, ec_epub_text_emphasis, ec_epub_text_emphasis_colour, ec_epub_text_emphasis_style, ec_epub_word_break, ec_epub_writing_mode,
                ec_moz_animation, ec_moz_animation_delay, ec_moz_animation_direction, ec_moz_animation_duration, ec_moz_animation_fill_mode, ec_moz_animation_iteration_count, ec_moz_animation_name, ec_moz_animation_play_state, ec_moz_animation_timing_function,
                ec_moz_appearance, ec_moz_backface_visibility, ec_moz_background_clip, ec_moz_background_inline_policy, ec_moz_background_origin, ec_moz_background_size, ec_moz_binding, ec_moz_border_bottom_colours, ec_moz_border_end, ec_moz_border_end_colour,
                ec_moz_border_end_style, ec_moz_border_end_width, ec_moz_border_image, ec_moz_border_left_colours, ec_moz_border_right_colours, ec_moz_border_start, ec_moz_border_start_colour, ec_moz_border_start_style, ec_moz_border_start_width, ec_moz_border_top_colours,
                ec_moz_box_align, ec_moz_box_direction, ec_moz_box_flex, ec_moz_box_ordinal_group, ec_moz_box_orient, ec_moz_box_pack, ec_moz_box_sizing, ec_moz_column_count, ec_moz_column_fill, ec_moz_column_gap, ec_moz_column_rule, ec_moz_column_rule_colour,
                ec_moz_column_rule_style, ec_moz_column_rule_width, ec_moz_column_width, ec_moz_context_properties, ec_moz_float_edge, ec_moz_font_feature_settings, ec_moz_font_language_override, ec_moz_force_broken_image_icon, ec_moz_hyphens, ec_moz_image_region,
                ec_moz_margin_end, ec_moz_margin_start, ec_moz_opacity, ec_moz_orient, ec_moz_osx_font_smoothing, ec_moz_outline, ec_moz_outline_colour, ec_moz_outline_offset, ec_moz_outline_radius, ec_moz_outline_radius_bottomleft, ec_moz_outline_radius_bottomright,
                ec_moz_outline_radius_topleft, ec_moz_outline_radius_topright, ec_moz_outline_style, ec_moz_outline_width, ec_moz_padding_end, ec_moz_padding_start, ec_moz_perspective, ec_moz_perspective_origin, ec_moz_stack_sizing, ec_moz_tab_size, ec_moz_text_align_last,
                ec_moz_text_decoration_colour, ec_moz_text_decoration_line, ec_moz_text_decoration_style, ec_moz_text_size_adjust, ec_moz_transform, ec_moz_transform_origin, ec_moz_transform_style, ec_moz_transition, ec_moz_transition_delay, ec_moz_transition_duration,
                ec_moz_transition_property, ec_moz_transition_timing_function, ec_moz_user_focus, ec_moz_user_input, ec_moz_user_modify, ec_moz_user_select, ec_moz_window_dragging, ec_moz_window_shadow,
                ec_webkit_align_content, ec_webkit_align_items, ec_webkit_align_self, ec_webkit_alt, ec_webkit_animation, ec_webkit_animation_delay, ec_webkit_animation_direction, ec_webkit_animation_duration, ec_webkit_animation_fill_mode, ec_webkit_animation_iteration_count,
                ec_webkit_animation_name, ec_webkit_animation_play_state, ec_webkit_animation_timing_function, ec_webkit_animation_trigger, ec_webkit_app_region, ec_webkit_appearance, ec_webkit_aspect_ratio, ec_webkit_backdrop_filter,
                ec_webkit_backface_visibility, ec_webkit_background_clip, ec_webkit_background_composite, ec_webkit_background_origin, ec_webkit_background_size, ec_webkit_border_after, ec_webkit_border_after_colour, ec_webkit_border_after_style, ec_webkit_border_after_width,
                ec_webkit_border_before, ec_webkit_border_before_colour, ec_webkit_border_before_style, ec_webkit_border_before_width, ec_webkit_border_bottom_left_radius, ec_webkit_border_bottom_right_radius, ec_webkit_border_end, ec_webkit_border_end_colour,
                ec_webkit_border_end_style, ec_webkit_border_end_width, ec_webkit_border_fit, ec_webkit_border_horizontal_spacing, ec_webkit_border_image, ec_webkit_border_radius, ec_webkit_border_start, ec_webkit_border_start_colour, ec_webkit_border_start_style,
                ec_webkit_border_start_width, ec_webkit_border_top_left_radius, ec_webkit_border_top_right_radius, ec_webkit_border_vertical_spacing, ec_webkit_box_align, ec_webkit_box_decoration_break, ec_webkit_box_direction,
                ec_webkit_box_flex, ec_webkit_box_flex_group, ec_webkit_box_lines, ec_webkit_box_ordinal_group, ec_webkit_box_orient, ec_webkit_box_pack, ec_webkit_box_reflect, ec_webkit_box_shadow,
                ec_webkit_box_sizing, ec_webkit_clip_path, ec_webkit_colour_correction, ec_webkit_column_axis, ec_webkit_column_break_after, ec_webkit_column_break_before, ec_webkit_column_break_inside, ec_webkit_column_count, ec_webkit_column_fill, ec_webkit_column_gap,
                ec_webkit_column_progression, ec_webkit_column_rule, ec_webkit_column_rule_colour, ec_webkit_column_rule_style, ec_webkit_column_rule_width, ec_webkit_column_span, ec_webkit_column_width, ec_webkit_columns, ec_webkit_cursor_visibility,
                ec_webkit_dashboard_region, ec_webkit_device_pixel_ratio, ec_webkit_filter, ec_webkit_flex, ec_webkit_flex_basis, ec_webkit_flex_direction, ec_webkit_flex_flow, ec_webkit_flex_grow, ec_webkit_flex_shrink, ec_webkit_flex_wrap, ec_webkit_flow_from,
                ec_webkit_flow_into, ec_webkit_font_feature_settings, ec_webkit_font_kerning, ec_webkit_font_size_delta, ec_webkit_font_smoothing, ec_webkit_font_variant_ligatures, ec_webkit_grid, ec_webkit_grid_area, ec_webkit_grid_auto_columns, ec_webkit_grid_auto_flow,
                ec_webkit_grid_auto_rows, ec_webkit_grid_column, ec_webkit_grid_column_end, ec_webkit_grid_column_gap, ec_webkit_grid_column_start, ec_webkit_grid_columns, ec_webkit_grid_gap, ec_webkit_grid_row, ec_webkit_grid_row_end, ec_webkit_grid_row_gap,
                ec_webkit_grid_row_start, ec_webkit_grid_rows, ec_webkit_grid_template, ec_webkit_grid_template_areas, ec_webkit_grid_template_columns, ec_webkit_grid_template_rows, ec_webkit_highlight, ec_webkit_hyphenate_character, ec_webkit_hyphenate_charset,
                ec_webkit_hyphenate_limit_after, ec_webkit_hyphenate_limit_before, ec_webkit_hyphenate_limit_lines, ec_webkit_hyphens, ec_webkit_initial_letter, ec_webkit_justify_content, ec_webkit_justify_items, ec_webkit_justify_self, ec_webkit_line_align,
                ec_webkit_line_box_contain, ec_webkit_line_break, ec_webkit_line_clamp, ec_webkit_line_grid, ec_webkit_line_snap, ec_webkit_locale, ec_webkit_logical_height, ec_webkit_logical_width, ec_webkit_margin_after, ec_webkit_margin_after_collapse,
                ec_webkit_margin_before, ec_webkit_margin_before_collapse, ec_webkit_margin_bottom_collapse, ec_webkit_margin_collapse, ec_webkit_margin_end, ec_webkit_margin_start, ec_webkit_margin_top_collapse, ec_webkit_marquee, ec_webkit_marquee_direction,
                ec_webkit_marquee_increment, ec_webkit_marquee_repetition, ec_webkit_marquee_speed, ec_webkit_marquee_style, ec_webkit_mask, ec_webkit_mask_attachment, ec_webkit_mask_box_image, ec_webkit_mask_box_image_outset, ec_webkit_mask_box_image_repeat,
                ec_webkit_mask_box_image_slice, ec_webkit_mask_box_image_source, ec_webkit_mask_box_image_width, ec_webkit_mask_clip, ec_webkit_mask_composite, ec_webkit_mask_image, ec_webkit_mask_origin, ec_webkit_mask_position,
                ec_webkit_mask_position_x, ec_webkit_mask_position_y, ec_webkit_mask_repeat, ec_webkit_mask_repeat_x, ec_webkit_mask_repeat_y, ec_webkit_mask_size,
                ec_webkit_mask_source_type, ec_webkit_match_nearest_mail_blockquote_colour, ec_webkit_max_logical_height, ec_webkit_max_logical_width, ec_webkit_media_text_track_container, ec_webkit_min_logical_height, ec_webkit_min_logical_width, ec_webkit_nbsp_mode,
                ec_webkit_opacity, ec_webkit_order, ec_webkit_overflow_scrolling, ec_webkit_padding_after, ec_webkit_padding_before, ec_webkit_padding_end, ec_webkit_padding_start, ec_webkit_perspective, ec_webkit_perspective_origin, ec_webkit_perspective_origin_x,
                ec_webkit_perspective_origin_y, ec_webkit_print_colour_adjust, ec_webkit_region_break_after, ec_webkit_region_break_before, ec_webkit_region_break_inside, ec_webkit_region_fragment, ec_webkit_rtl_ordering, ec_webkit_ruby_position,
                ec_webkit_scroll_snap_type, ec_webkit_shape_image_threshold, ec_webkit_shape_inside, ec_webkit_shape_margin, ec_webkit_shape_outside, ec_webkit_svg_shadow, ec_webkit_tap_highlight_colour, ec_webkit_text_colour_decoration, ec_webkit_text_combine,
                ec_webkit_text_decoration_line, ec_webkit_text_decoration_skip, ec_webkit_text_decoration_style, ec_webkit_text_decorations_in_effect, ec_webkit_text_emphasis, ec_webkit_text_emphasis_colour, ec_webkit_text_emphasis_position, ec_webkit_text_emphasis_style,
                ec_webkit_text_fill_colour, ec_webkit_text_justify, ec_webkit_text_orientation, ec_webkit_text_security, ec_webkit_text_size_adjust, ec_webkit_text_stroke,
                ec_webkit_text_stroke_colour, ec_webkit_text_stroke_width, ec_webkit_text_underline_position, ec_webkit_text_zoom, ec_webkit_touch_callout, ec_webkit_transform, ec_webkit_transform_2d, ec_webkit_transform_3d,
                ec_webkit_transform_origin, ec_webkit_transform_origin_x, ec_webkit_transform_origin_y, ec_webkit_transform_origin_z, ec_webkit_transform_style, ec_webkit_transition, ec_webkit_transition_delay, ec_webkit_transition_duration, ec_webkit_transition_property,
                ec_webkit_transition_timing_function, ec_webkit_user_drag, ec_webkit_user_modify, ec_webkit_user_select, ec_webkit_image_set,
                ec_background_origin_x, ec_background_origin_y, ecp_clip_path, ecp_filter, ec_overflow_clip_box, ec_overflow_clip_box_block, ec_overflow_clip_box_inline,

                // https://litmus.com/community/learning/8-outlook-overview
                ec_mso_ansi_font_size, ec_mso_ansi_font_style, ec_mso_ansi_font_weight, ec_mso_ansi_language, ec_mso_arabic_font_family, ec_mso_armenian_font_family, ec_mso_ascii_font_family, ec_mso_ascii_theme_font,
                ec_mso_background_source, ec_mso_bengali_font_family, ec_mso_bidi_font_family, ec_mso_bidi_font_size, ec_mso_bidi_font_style, ec_mso_bidi_font_weight, ec_mso_bidi_language, ec_mso_bidi_theme_font,
                ec_mso_bookmark, ec_mso_bopomofo_font_family, ec_mso_border_alt, ec_mso_border_bottom_alt, ec_mso_border_colour_alt, ec_mso_border_insideh, ec_mso_border_insidev, ec_mso_border_left_alt, ec_mso_border_right_alt,
                ec_mso_border_shadow, ec_mso_border_style_alt, ec_mso_border_top_alt, ec_mso_border_width_alt, ec_mso_break_type, ec_mso_cell_special, ec_mso_cellspacing, ec_mso_char_indent_count, ec_mso_char_indent_size,
                ec_mso_char_tracking, ec_mso_char_type, ec_mso_char_wrap, ec_mso_colour_alt, ec_mso_colour_index, ec_mso_column_margin, ec_mso_currency_font_family, ec_mso_cyrillic_font_family, ec_mso_data_placement,
                ec_mso_default_font_family, ec_mso_default_props, ec_mso_devanagari_font_family, ec_mso_displayed_decimal_separator, ec_mso_displayed_thousand_separator, ec_mso_element, ec_mso_element_anchor_horizontal,
                ec_mso_element_anchor_vertical, ec_mso_element_frame_height, ec_mso_element_frame_hspace, ec_mso_element_frame_width, ec_mso_element_left, ec_mso_element_top, ec_mso_element_wrap, ec_mso_endnote_continuation_separator,
                ec_mso_endnote_numbering_style, ec_mso_endnote_separator, ec_mso_eudc_font_family, ec_mso_even_footer, ec_mso_fareast_font_family, ec_mso_fareast_language, ec_mso_fareast_theme_font, ec_mso_field_code,
                ec_mso_font_alt, ec_mso_font_charset, ec_mso_font_format, ec_mso_font_kerning, ec_mso_font_pitch, ec_mso_font_signature, ec_mso_font_width, ec_mso_footer, ec_mso_footer_margin, ec_mso_footnote_continuation_separator,
                ec_mso_footnote_id, ec_mso_footnote_separator, ec_mso_generic_font_family, ec_mso_georgian_font_family, ec_mso_gram_e, ec_mso_greek_font_family, ec_mso_gurmukhi_font_family, ec_mso_halfwidthkana_font_family,
                ec_mso_han_font_family, ec_mso_hangul_font_family, ec_mso_hansi_font_family, ec_mso_hansi_theme_font, ec_mso_header, ec_mso_header_margin, ec_mso_hebrew_font_family, ec_mso_height_rule, ec_mso_height_source,
                ec_mso_hide, ec_mso_highlight, ec_mso_hyphenate, ec_mso_ignore, ec_mso_kana_font_family, ec_mso_kannada_font_family, ec_mso_kinsoku_overflow, ec_mso_lao_font_family, ec_mso_latin_font_family,
                ec_mso_latinext_font_family, ec_mso_layout_grid_align, ec_mso_level_font_family, ec_mso_level_indent, ec_mso_level_legacy, ec_mso_level_legacy_indent, ec_mso_level_legacy_space, ec_mso_level_number_format,
                ec_mso_level_number_position, ec_mso_level_size, ec_mso_level_start_at, ec_mso_level_style_link, ec_mso_level_tab_stop, ec_mso_level_text, ec_mso_line_height_alt, ec_mso_line_height_rule, ec_mso_line_spacing,
                ec_mso_linked_frame, ec_mso_list, ec_mso_list_id, ec_mso_list_template_ids, ec_mso_list_type, ec_mso_malayalam_font_family, ec_mso_margin_bottom_alt, ec_mso_margin_left_alt, ec_mso_margin_top_alt,
                ec_mso_no_proof, ec_mso_number_format, ec_mso_oriya_font_family, ec_mso_outline_level, ec_mso_padding_alt, ec_mso_page_border_surround_footer, ec_mso_page_border_surround_header, ec_mso_page_orientation,
                ec_mso_pagination, ec_mso_paper_source, ec_mso_para_margin, ec_mso_para_margin_bottom, ec_mso_para_margin_left, ec_mso_para_margin_right, ec_mso_para_margin_top, ec_mso_pattern, ec_mso_position_horizontal,
                ec_mso_position_horizontal_relative, ec_mso_position_vertical, ec_mso_position_vertical_relative, ec_mso_protection, ec_mso_rotate, ec_mso_row_margin_left, ec_mso_row_margin_right, ec_mso_shading,
                ec_mso_spacerun, ec_mso_special_character, ec_mso_special_format, ec_mso_spl_e, ec_mso_style_id, ec_mso_style_link, ec_mso_style_locked, ec_mso_style_name, ec_mso_style_next, ec_mso_style_noshow, ec_mso_style_parent,
                ec_mso_style_priority, ec_mso_style_qformat, ec_mso_style_type, ec_mso_style_unhide, ec_mso_style_update, ec_mso_symbol_font_family, ec_mso_syriac_font_family, ec_mso_tab_count, ec_mso_table_anchor_horizontal,
                ec_mso_table_anchor_vertical, ec_mso_table_layout_alt, ec_mso_table_left, ec_mso_table_lspace, ec_mso_table_overlap, ec_mso_table_rspace, ec_mso_table_top, ec_mso_tamil_font_family, ec_mso_telugu_font_family,
                ec_mso_text_animation, ec_mso_text_raise, ec_mso_thaana_font_family, ec_mso_thai_font_family, ec_mso_themecolour, ec_mso_themeshade, ec_mso_title_page, ec_mso_tstyle_colband_size, ec_mso_tstyle_rowband_size,
                ec_mso_width_alt, ec_mso_width_source, ec_mso_wrap_distance_bottom, ec_mso_wrap_distance_left, ec_mso_wrap_distance_right, ec_mso_wrap_distance_top, ec_mso_wrap_edited, ec_mso_yfti_firstrow, ec_mso_yfti_irow,
                ec_mso_yfti_lastrow, ec_mso_yfti_tbllook,

                // https://dev.opera.com/blog/o-vendor-prefixed-css-supported-in-opera-10-50/
                ec_o_table_baseline, ec_o_text_overflow, ec_o_transform, ec_o_transform_origin, ec_o_transition, ec_o_transition_delay, ec_o_transition_duration,
                ec_o_transition_property, ec_o_transition_timing_function, ec_o_tab_size,

                // some extras from https://gist.github.com/ryboe/bb95223148e486acbe7a
                ec_apple_dashboard_region,
                ec_epub_caption_side, ec_epub_hyphens, ec_epub_text_combine, ec_epub_text_orientation, ec_epub_text_transform,
                ec_ms_animation, ec_ms_animation_delay, ec_ms_animation_direction, ec_ms_animation_duration, ec_ms_animation_fill_mode, ec_ms_animation_iteration_count, ec_ms_animation_name, ec_ms_animation_play_state,
                    ec_ms_animation_timing_function, ec_ms_block_progression, ec_ms_content_zoom_chaining, ec_ms_content_zoom_limit, ec_ms_content_zoom_limit_max, ec_ms_content_zoom_limit_min, ec_ms_content_zoom_snap,
                    ec_ms_content_zoom_snap_points, ec_ms_content_zoom_snap_type, ec_ms_content_zooming, ec_ms_flex_align, ec_ms_flex_item_align, ec_ms_flex_line_pack, ec_ms_flex_negative, ec_ms_flex_order, ec_ms_flex_pack,
                    ec_ms_flex_positive, ec_ms_flex_preferred_size, ec_ms_font_feature_settings, ec_ms_grid_columns, ec_ms_grid_rows, ec_ms_high_contrast_adjust, ec_ms_hyphenate_limit_chars, ec_ms_hyphenate_limit_lines,
                    ec_ms_hyphenate_limit_zone, ec_ms_ime_align, ec_ms_interpolation_mode, ec_ms_scroll_chaining, ec_ms_scroll_limit, ec_ms_scroll_limit_x_max, ec_ms_scroll_limit_x_min, ec_ms_scroll_limit_y_max,
                    ec_ms_scroll_limit_y_min, ec_ms_scroll_rails, ec_ms_scroll_snap_points_x, ec_ms_scroll_snap_points_y, ec_ms_scroll_snap_type, ec_ms_scroll_snap_x, ec_ms_scroll_snap_y, ec_ms_scroll_translation,
                    ec_ms_text_combine_horizontal, ec_ms_touch_action, ec_ms_touch_select, ec_ms_transition, ec_ms_transition_delay, ec_ms_transition_duration, ec_ms_transition_property, ec_ms_transition_timing_function,
                    ec_ms_wrap_margin,
                ec_o_border_image, ec_o_device_pixel_ratio, ec_o_focus_opacity, ec_o_link, ec_o_link_source, ec_o_mini_fold, ec_o_object_fit, ec_o_object_position,
                ec_wap_accesskey, ec_wap_input_format, ec_wap_input_required, ec_wap_marquee_dir, ec_wap_marquee_loop, ec_wap_marquee_speed, ec_wap_marquee_style,
                ec_xv_interpret_as, ec_xv_phonemes, ec_xv_voice_balance, ec_xv_voice_duration, ec_xv_voice_pitch, ec_xv_voice_pitch_range, ec_xv_voice_rate, ec_xv_voice_stress, ec_xv_voice_volume,

                ec_error } e_css_property;
typedef enum { crs_closest_corner, crs_closest_side, crs_farthest_corner, crs_farthest_size } e_css_radial_size;
typedef enum { cry_closest_corner, cry_closest_side, cry_farthest_corner, cry_farthest_side, cry_sides  } e_css_ray_size;
typedef enum { crx_a98_rgb, crx_display_p3, crx_prophoto_rgb, crx_rec2020, crx_srgb, crx_srgb_linear, crx_xyz, crx_xyz_d50, crx_xyz_d65 } e_css_rgb_xyz;
typedef enum { ec4_lab, ec4_oklab, ec4_srgb, ec4_srgb_linear, ec4_xyz, ec4_xyz_d50, ec4_xyz_d65 } e_css_rect;
typedef enum { ecr_inherit, ecr_larger, ecr_smaller } e_css_relative_size;
typedef enum { ecz_block, ecz_both, ecz_horizontal, ecz_inherit, ecz_inline, ecz_none, ecz_vertical } e_css_resize;
typedef enum { cst_block, cst_both, cst_inline, cst_x, cst_y } e_css_ss_type_e;
typedef enum { ecsp_centre, ecsp_end, ecsp_flex_end, ecsp_flex_start, ecsp_self_end, ecsp_self_start, ecsp_start } e_css_self_position;
typedef enum { ecsb_border_box, ecsb_content_box, ecsb_margin_box, ecsb_padding_box } e_css_shape_box;
typedef enum { csfr_evenodd, csfr_nonzero } e_css_shape_fillrule;
typedef enum { cse_a3, cse_a4, cse_a5, cse_b4, cse_b5, cse_jis_b4, cse_jis_b5, cse_ledger, cse_legal, cse_letter } e_css_size_e;
typedef enum { csz_auto, csz_contain, csz_fit_content, csz_max_content, csz_min_content, csz_stretch } e_css_sizing;
typedef enum { csp_inherit, csp_none, csp_normal, csp_spell_out } e_css_speak_2;
typedef enum { csp_always, csp_auto, csp_never } e_css_speak_3;
typedef enum { csae_auto, csae_bullets, csae_numbers, csae_spell_out, csae_words } e_css_speak_as_e;
typedef enum { ecsh_always, ecsh_inherit, ecsh_once } e_css_speak_header;
typedef enum { ecsn_continuous, ecsn_digits, ecsn_inherit } e_css_speak_numeral;
typedef enum { ecsp_code, ecsp_inherit, ecsp_none } e_css_speak_punctuation;
typedef enum { esr_fast, esr_faster, esr_inherit, esr_medium, esr_normal, esr_slow, esr_slower, esr_x_fast, est_x_slow } e_css_speech_rate_e;
typedef enum {  css_context,
                css_annotation,
                css_character_variant, css_charset, css_colour_profile, css_container, css_counter_style, css_custom_media,
                css_document,
                css_else,
                css_font_feature_values, css_font_face, css_font_palette_values,
                css_historical_forms,
                css_import,
                css_keyframes,
                css_layer, 
                css_media,
                css_namespace,
                css_ornaments,
                css_scope, css_swash, css_styleset, css_stylistic,
                css_viewport,
                css_when,
                css_page, // these and below must be at the end
                css_supports,
                css_bottom_centre, css_bottom_left, css_bottom_left_corner, css_bottom_right, css_bottom_right_corner,
                css_left_bottom, css_left_middle, css_left_top,
                css_right_bottom, css_right_middle, css_right_top,
                css_top_centre, css_top_left, css_top_left_corner, css_top_right, css_top_right_corner,
                css_error } e_css_statement;
constexpr e_css_statement css_content_ok = css_page;
typedef enum { cse_additive, cse_alphabetic, cse_cyclic, cse_numeric, cse_symbolic } e_css_system_e;
typedef enum { ctl_auto, ctl_fixed, ctl_inherit } e_css_table_layout;
typedef enum { cta_ideographic_alpha, cta_ideographic_numeric, cta_insert, cta_no_autospace, cta_punctuation, cta_replace } e_css_text_autospace;
typedef enum { ecta_centre, ecta_end, ecta_inherit, ecta_justify, ecta_justify_all, ecta_left, ecta_match_parent, ecta_right, ecta_start } e_css_text_align;
typedef enum { ectaa_centre, ectaa_end, ectaa_justify, ectaa_left, ectaa_match_parent, ectaa_right, ectaa_start } e_css_text_align_all;
typedef enum { ectal_auto, ectal_centre, ectal_end, ectal_justify, ectal_left, ectal_match_parent, ectal_right, ectal_start } e_css_text_align_last;
typedef enum { ectd_inherit, ectd_none, ectd_underline, ectd_overline, ectd_linethrough, ectd_blink } e_css_text_decoration;
typedef enum { etj_auto, etj_inter_character, etj_inter_word, etj_none } e_css_text_justify;
typedef enum { ecto_mixed, ecto_sideways, ecto_upright } e_css_text_orientation;
typedef enum { etr_clip, etr_ellipses } e_css_text_resize;
typedef enum { ect_capitalise, ect_full_width, ect_full_size_kana, ect_lowercase, ect_uppercase } e_css_text_transform;
typedef enum { ectl_grammar_error, ectl_none, ectl_spelling_error } e_css_textdec_line_e;
typedef enum { ects_dashed, ects_dotted, ects_double, ects_solid, ects_wavy } e_css_textdec_style;
typedef enum { cte_circle, cte_dot, cte_double_circle, cte_triangle, cte_sesame } e_css_textemph_shape;
typedef enum { cts_narrow, cts_punctuation, cts_spaces, cts_symbols } e_css_textemph_skip;
typedef enum { ctw_balance, ctw_nowrap, ctw_pretty, ctw_stable, ctw_wrap } e_css_text_wrap;
typedef enum {  ct_root, ct_whitespace, ct_comment, // root must be zero, all empty content must precede comment which must precede remaining values
                ct_identifier, ct_keyword, ct_number, ct_string, 
                ct_ampersand, ct_at, ct_bang, ct_bar, ct_barbar, ct_coco, ct_colon, ct_comma, ct_dash, ct_dollar, ct_dot, ct_eq,
                ct_gt, ct_gteq, ct_gtgt, ct_lt, ct_lteq, ct_hash, ct_hat, ct_plus, ct_semicolon, ct_slash, ct_splat, ct_squiggle,
                ct_curly_brac, ct_curly_ket, ct_round_brac, ct_round_ket, ct_square_brac, ct_square_ket,
                ct_eof,
                ct_error } css_token;
typedef enum { ctb_content_box, ctb_border_box, ctb_fill_box, ctb_stroke_box, ctb_view_box } e_css_transform_box;
typedef enum { cts_flat, cts_preserve_3d } e_css_transform_style;
typedef enum { ecu_all, ecu_auto, ecu_contain, ecu_inherit, ecu_none, ecu_text } e_css_user_select;
typedef enum { cvc_e, cvc_infinity, cvc_nan, cvc_pi } e_css_val_con;
#define CSS_VAL_FN \
                cvf_none, \
                cvf_abs, cvf_acos, cvf_annotation, cvf_asin, cvf_atan, cvf_atan2, cvf_attr, cvf_auto, \
                cvf_blur, cvf_brightness, \
                cvf_calc, cvf_character_variant, cvf_circle, cvf_clamp, cvf_colour, cvf_colour_mix, cvf_conic_gradient, cvf_content, cvf_contrast, \
                    cvf_cos, cvf_counter, cvf_counters, cvf_cross_fade, cvf_cubic_bezier, \
                cvf_device_cmyk, cvf_drop_shadow, \
                cvf_ease, cvf_ease_in, cvf_ease_in_out, cvf_ease_out, cvf_element, cvf_ellipse, cvf_exp, \
                cvf_fade, cvf_filter, cvf_format, \
                cvf_greyscale, \
                cvf_historical_forms, cvf_hsl, cvf_hsla, cvf_hue_rotate, cvf_hwb, cvf_hypot, \
                cvf_image, cvf_image_set, cvf_inset, cvf_invert, \
                cvf_lab, cvf_lch, cvf_leader, cvf_linear, cvf_linear_gradient, cvf_local, cvf_log, \
                cvf_matrix, cvf_matrix3d, cvf_max, cvf_min, cvf_mix, cvf_mod, \
                cvf_oklab, cvf_oklch, cvf_opacity, cvf_ornaments, \
                cvf_path, cvf_perspective, cvf_polygon, cvf_pow, \
                cvf_radial_gradient, cvf_ray, cvf_repeating_conic_gradient, cvf_repeating_linear_gradient, cvf_repeating_radial_gradient, cvf_rgb, \
                    cvf_rgba, cvf_rect, cvf_rem, cvf_rotate, cvf_rotate3d, cvf_rotatex, cvf_rotatey, cvf_rotatez, cvf_round, \
                cvf_saturate, cvf_scale, cvf_scale3d, cvf_scalex, cvf_scaley, cvf_scalez, cvf_sepia, cvf_sign, cvf_sin, cvf_skew, cvf_skewx, \
                    cvf_skewy, cvf_snap_block, cvf_snap_inline, cvf_sqrt, cvf_src, cvf_step_end, cvf_step_start, cvf_steps, cvf_string, \
                    cvf_stripes, cvf_styleset, cvf_stylistic, cvf_swash, \
                cvf_tan, cvf_target_counter, cvf_target_counters, cvf_target_text, cvf_tech, cvf_translate, cvf_translate3d, cvf_translatex, \
                    cvf_translatey, cvf_translatez, \
                cvf_url, \
                cvf_var, \
                cvf_xywh
typedef enum {  CSS_VAL_FN } e_css_val_fn;
typedef enum {  css_none, css_1, css_2_0, css_2_1, css_2_2, css_3, css_4, css_5, css_6, css_2007, css_2010,
                css_2015, css_2015_1, css_2015_2, css_2017, css_2017_1, css_2017_2, css_2018, css_2018_1, css_2018_2, css_2020, css_2020_1, css_2020_2,
                css_2021, css_2021_1, css_2021_2, css_2022, css_2022_1, css_2022_2, css_2023, css_2023_1, css_2023_2 } e_css_version;
typedef enum { ecva_inherit, ecv_baseline, ecv_bottom, ecv_middle, ecv_sub, ecv_super, ecv_text_bottom, ecv_text_top, ecv_top } e_css_vertical_align;
typedef enum { eccl_border_box, eccl_content_box, eccl_padding_box } e_css_visual_box;
typedef enum { cva_child, cva_old, cva_young  } e_css_voice_age;
typedef enum { cvg_female, cvg_male, cvg_neutral  } e_css_voice_gender;
typedef enum { evb_centre, evb_left, evb_leftwards, evb_right, evb_rightwards } e_css_voice_balance_e;
typedef enum { cve_inherit, cve_loud, cve_medium, cve_silent, cve_soft, cve_x_loud, cve_x_soft } e_css_volume_e;
typedef enum { wbe_ideographic_space, wbe_none, wbe_space } e_css_wbe;
typedef enum { wc_contents, wc_scroll_position } e_css_wc_e;
typedef enum { cw_default, cw_inherit, cw_initial, cw_revert, cw_revert_layer, cw_unset } e_css_wide;
typedef enum { ecwh_break_spaces, ecwh_inherit, ecwh_normal, ecwh_nowrap, ecwh_pre, ecwh_preline, ecwh_prewrap } e_css_whitespace;
typedef enum { wb_break_all, wb_break_word, wb_keep_all, wb_normal } e_css_word_break;
typedef enum { cwf_auto, cwf_both, cwf_clear, cwf_end, cwf_maximum, cwf_minimum, cwf_start } e_css_wrap_flow;
typedef enum { wsc_break_spaces, wsc_collapse, wsc_discard, wsc_preserve, wsc_preserve_breaks, wsc_preserve_spaces } e_css_wsc;
typedef enum { wst_discard_after, wst_discard_before, wst_discard_inner, wst_none  } e_css_wst;

typedef enum { cd_ltr, cd_rtl, cd_auto } e_csvw_direction;

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
                cu_swresize, cu_sresize, cu_wresize, cu_text, cu_wait, cu_help, cu_progress  } e_cursor;
typedef enum { edf_html, edf_plaintext } e_dataformatas;
typedef enum {  dt_collection, dt_dataset, dt_event, dt_image, dt_interactiveresource, dt_movingimage, dt_physicalobject, dt_service,
                dt_software, dt_sound, dt_stillimage, dt_text } e_dcmitype;
typedef enum { dec_left, dec_center, dec_right, dec_justify, dec_decimal } e_decalign;
typedef enum { ed_auto, ed_sync, ed_async } e_decoding;
typedef enum { df_cancel, df_perform } e_defaultaction;
typedef enum { dt_none, dt_a, dt_an, dt_the, dt_auto } e_determiner;
typedef enum { dv_media, dv_fs, dv_rs232, dv_usb } e_device;
typedef enum { dg_dash, dg_gaps } e_dg;
typedef enum {  db_context,
                db_ftp, db_gopher, db_telnet, db_archive, db_filing_cabinet, db_folder, db_fixed_disk, db_disk_drive, db_document,
                db_unknown_document, db_text_document, db_binary_document, db_binhex_document, db_audio, db_film, db_image, db_map,
                db_form, db_mail, db_parent, db_next, db_previous, db_home, db_toc, db_glossary, db_index, db_summary, db_calculator,
                db_caution, db_clock, db_compressed_document, db_diskette, db_display, db_fax, db_mail_in, db_mail_out, db_mouse,
                db_printer, db_tn3270, db_trash } e_dingbat;
typedef enum { di_auto, di_lro, di_rlo, di_ltr, di_rtl, di_forward, di_reverse } e_dir;
typedef enum { da_auto, da_before, da_centre, da_after, da_inherit } e_display_align;
typedef enum { dnp_display, dnp_none, dnp_parent } e_display_none_parent;
typedef enum { dnu_down, dnu_nearest, dnu_up } e_dnu;
typedef enum { do_booboo, do_cgi, do_examine, do_simple } e_do;
typedef enum {  ed_mishmash, ed_dict, ed_tags, ed_1, ed_plus, ed_2, ed_3, ed_32, ed_4, ed_41, ed_x1, ed_x11, ed_x2,
                ed_50, ed_51, ed_52, ed_53,
                ed_jan05, ed_jan06, ed_jan07, ed_jan08, ed_jan10, ed_jul10, ed_jan12, ed_jan13, ed_jan14, ed_jul17, ed_may20, ed_jul20, ed_jan21,
                ed_apr21, ed_jul21, ed_apr22, ed_oct22, ed_apr23, ed_jul23,
                ed_svg_1_0, ed_svg_1_1, ed_svg_1_2_tiny, ed_svg_1_2_full, ed_svg_2_0, ed_svg_2_anim,
                ed_math_1, ed_math_2, ed_math_3, ed_math_4_20, ed_math_4_22,
                ed_iso_8859_1, ed_csp,
                ed_rfc_1867, ed_rfc_1980, ed_rfc_3986, ed_rfc_3966, ed_rfc_6265, ed_rfc_7231, ed_rfc_7234, ed_rfc_8288,
                ed_w3, ed_mql, ed_ariaAug2020, ed_ariaApr2021, ed_mozilla, ed_ecma,
                ed_microdata, ed_microformats, ed_mimetype, ed_prism_1, ed_rdfa, ed_rdfa_c, ed_apache, ed_so_11, ed_css_transform,
                ed_css_1, ed_css_20, ed_css_21, ed_css_22,
                ed_css_animation_3,
                ed_css_cascade_4, ed_css_cascade_5, ed_css_cascade_6, ed_css_colour_3, ed_css_colour_4, ed_css_colour_5, ed_css_content,
                    ed_cr_4, ed_cr_5, ed_css_cs_3, ed_css_custom,
                ed_css_ease,
                ed_css_filter_3, ed_css_font_4,
                ed_css_image_3,
                ed_css_media_3, ed_css_media_4,
                ed_css_namespaces_3, ed_css_nesting,
                ed_css_selectors_3, ed_css_selectors_4, ed_css_syntax,
                ed_css_table, ed_css_transform_3,
                ed_css_ui_3, ed_css_ui_4, ed_css_value_3, ed_css_value_4,
                ed_json, ed_jsonld_1_0, ed_jsonld_1_1,
                ed_doctype,
                ed_clacks,
                ed_imaginary } e_doc;
const e_doc last_doc = ed_imaginary;
typedef enum { dr_drop, dr_raise } e_drop_raise;
typedef enum {  db_auto, db_usescript, db_nochange, db_resetsize, db_ideographic, db_alphabetic, db_hanging, db_mathematical,
                db_central, db_middle, db_textafteredge, db_textbeforeedge, db_textbottom, db_texttop, db_inherit } e_dominantbaseline;
typedef enum { dsc_disc, dsc_square, dsc_circle } e_dsc;
typedef enum { dss_dotted, dss_solid, dss_space } e_dss;
typedef enum { dr_high, dr_standard } e_dynamic_range;
typedef enum { ew_e, ew_w } e_e_w;
typedef enum { ee_economy, ee_exact } e_economy_exact;
typedef enum { em_duplicate, em_wrap, em_none } e_edgemode;
typedef enum { edi_enable, edi_disable, edi_inherit } e_edi;
typedef enum { ed_changed, ed_deleted, ed_inserted, ed_moved } e_edit;
typedef enum { edi_none, edi_simple } e_editable;
typedef enum { ef_embed, ef_overlay, ef_new, ef_replace } e_effect;

typedef enum {
    elem_undefined,

    elem_faux_document, elem_faux_asp, elem_faux_cdata, elem_faux_char, elem_faux_code, elem_faux_comment, elem_faux_doctype, elem_faux_php,
        elem_faux_ssi, elem_faux_stylesheet, elem_faux_text, elem_faux_xml, elem_faux_whitespace,

    elem_css_all, elem_css_cell, elem_css_child, elem_css_precede, elem_css_precede_immediate, elem_css_scope_descendent, elem_css_scope_root,

    elem_custom,

    elem_a, elem_abbr, elem_abbrev, elem_above, elem_abs, elem_abstract, elem_access, elem_acronym, elem_action, elem_added, elem_addeventlistener,
        elem_address, elem_altglyph, elem_altglyphdef, elem_altglyphitem, elem_and, elem_animate, elem_animatecolour, elem_animatemotion,
        elem_animatetransform, elem_animation, elem_annotation, elem_annotation_xml, elem_applet, elem_apply, elem_approx, elem_arccos, elem_arcsin,
        elem_arctan, elem_arccosh, elem_arccot, elem_arccoth, elem_arccsc, elem_arccsch, elem_arcsec, elem_arcsech, elem_arcsinh, elem_arctanh,
        elem_area, elem_arg, elem_array, elem_article, elem_aside, elem_atop, elem_au, elem_audio,
    elem_b, elem_bb, elem_banner, elem_bar, elem_base, elem_basefont, elem_bdi, elem_bdo, elem_below, elem_bgsound, elem_big, elem_bind, elem_blink,
        elem_blockcode, elem_blockquote, elem_body, elem_box, elem_bq, elem_br, elem_bt, elem_button, elem_bvar, elem_byline,
    elem_calendar, elem_canvas, elem_caption, elem_card, elem_cartesianproduct, elem_cbytes, elem_cdata, elem_ceiling, elem_centre,
        elem_cerror, elem_changed, elem_choose, elem_ci, elem_circle, elem_cite, elem_clippath, elem_cmd, elem_cn, elem_code, elem_codomain, elem_col,
        elem_colgroup, elem_colour_profile, elem_command, elem_commandset, elem_comment, elem_complexes, elem_compose, elem_condition, elem_conjugate,
        elem_content, elem_cos, elem_cosh, elem_cot, elem_coth, elem_credit, elem_cs, elem_csc, elem_csch, elem_csymbol, elem_curl, elem_cursor,
    elem_data, elem_datagrid, elem_datalist, elem_datatemplate, elem_dd, elem_ddot, elem_declare, elem_definition_src, elem_defs, elem_degree, elem_del,
        elem_desc, elem_details, elem_determinant, elem_device, elem_devicecolour, elem_dfn, elem_di, elem_dialogue, elem_diff, elem_dir, elem_discard,
        elem_dispatchevent, elem_div, elem_divergence, elem_divide, elem_dl, elem_domain, elem_domainofapplication, elem_dot, elem_dt,
    elem_element, elem_elementdef, elem_ellipse, elem_em, elem_embed, elem_emptyset, elem_eq, elem_equivalent, elem_eulergamma, elem_event_source,
        elem_eventsource, elem_exists, elem_exp, elem_exponentiale, elem_extensiondefs,
    elem_factorial, elem_factorof, elem_false, elem_fe, elem_feblend, elem_fecolourmatrix, elem_fecomponenttransfer, elem_fecomposite,
        elem_feconvolvematrix, elem_fediffuselighting, elem_fedisplacementmap, elem_fedistantlight, elem_fedropshadow, elem_feflood, elem_fefunca,
        elem_fefuncb, elem_fefuncg, elem_fefuncr, elem_fegaussianblur, elem_feimage, elem_femerge, elem_femergenode, elem_femorphology, elem_feoffset,
        elem_fepointlight, elem_fespecularlighting, elem_fespotlight, elem_fetile, elem_feturbulence, elem_fieldset, elem_fig, elem_figcaption,
        elem_figure, elem_filter, elem_floor, elem_flowdiv, elem_flowimage, elem_flowline, elem_flowpara, elem_flowref, elem_flowregion,
        elem_flowregionbreak, elem_flowregionexclude, elem_flowroot, elem_flowspan, elem_flowtref, elem_fn, elem_font, elem_font_face, elem_font_face_format,
        elem_font_face_name, elem_font_face_src, elem_font_face_uri, elem_footer, elem_footnote, elem_forall, elem_foreignobject, elem_form, elem_frame,
        elem_frameset,
    elem_g, elem_gauge, elem_gcd, elem_geq, elem_glyph, elem_glyphref, elem_grad, elem_gt,
    elem_h, elem_h1, elem_h2, elem_h3, elem_h4, elem_h5, elem_h6, elem_handler, elem_hat, elem_head, elem_header, elem_hgroup, elem_hint, elem_hkern,
        elem_hp1, elem_hp2, elem_hp3, elem_hp4, elem_hp5, elem_hp6, elem_hr, elem_html, elem_htmlplus,
    elem_i, elem_ident, elem_iframe, elem_ilayer, elem_image, elem_imaginary, elem_imaginaryi, elem_img, elem_implies, elem_in, elem_infinity, elem_integers,
        elem_input, elem_ins, elem_int, elem_intersect, elem_interval, elem_inverse, elem_isindex, elem_item,
    elem_kbd, elem_keygen,
    elem_l, elem_label, elem_lambda, elem_lang, elem_laplacian, elem_layer, elem_lcm, elem_left, elem_legend, elem_leq, elem_lh, elem_li, elem_limit,
        elem_line, elem_lineargradient, elem_link, elem_list, elem_listener, elem_listing, elem_lit, elem_ln, elem_loc, elem_log, elem_logbase, elem_lowlimit,
        elem_lt,
    elem_m, elem_maction, elem_main, elem_maligngroup, elem_malignmark, elem_map, elem_margin, elem_mark, elem_marker, elem_marquee, elem_mask, elem_math,
        elem_matrix, elem_matrixrow, elem_max, elem_mean, elem_median, elem_menclose, elem_menu, elem_menubar, elem_menuitem, elem_menulabel, elem_merror,
        elem_meta, elem_metadata, elem_meter, elem_mfenced, elem_mfrac, elem_mglyph, elem_mh, elem_mi, elem_min, elem_minus, elem_missingglyph, elem_mlabeledtr,
        elem_mlongdiv, elem_mmultiscripts, elem_mn, elem_mo, elem_mode, elem_moment, elem_momentabout, elem_mover, elem_mpadded, elem_mpath, elem_mphantom,
        elem_mprescripts, elem_mroot, elem_mrow, elem_ms, elem_mscarries, elem_mscarry, elem_msgroup, elem_msline, elem_mspace, elem_msqrt, elem_msrow,
        elem_mstack, elem_mstyle, elem_msub, elem_msubsup, elem_msup, elem_mtable, elem_mtd, elem_mtext, elem_mtr, elem_multicol, elem_munder, elem_munderover,
    elem_naturalnumbers, elem_nav, elem_navigation, elem_neq, elem_nest, elem_nextid, elem_nl, elem_nobr, elem_noembed, elem_noframes, elem_none, elem_noscript,
        elem_not, elem_notanumber, elem_note, elem_notin, elem_notprsubset, elem_notsubset,
    elem_object, elem_of, elem_ol, elem_online, elem_optgroup, elem_option, elem_or, elem_otherwise, elem_outerproduct, elem_output, elem_over, elem_overlay,
    elem_p, elem_page, elem_pageset, elem_param, elem_partialdiff, elem_path, elem_pattern, elem_person, elem_pi, elem_picture, elem_piece, elem_piecewise,
        elem_plaintext, elem_plus, elem_polygon, elem_polyline, elem_power, elem_pre, elem_prefetch, elem_preventdefault, elem_primes, elem_printed,
        elem_product, elem_progress, elem_prototype, elem_prsubset,
    elem_q, elem_quote, elem_quotient,
    elem_radialgradient, elem_range, elem_rationals, elem_rb, elem_rbc, elem_rdf_1, elem_rdf_2, elem_rdf_3, elem_rdf_4, elem_rdf_5, elem_rdf_6, elem_rdf_7,
        elem_rdf_8, elem_rdf_9, elem_rdf_about, elem_rdf_abouteach, elem_rdf_abouteachprefix, elem_rdf_alt, elem_rdf_bag, elem_rdf_bagid, elem_rdf_datatype,
        elem_rdf_description, elem_rdf_id, elem_rdf_li, elem_rdf_nodeid, elem_rdf_parsetype, elem_rdf_rdf, elem_rdf_resource, elem_rdf_seq, elem_real,
        elem_reals, elem_rect, elem_refcontent, elem_reln, elem_rem, elem_removed, elem_removeeventlistener, elem_render, elem_right, elem_root, elem_row,
        elem_rp, elem_rt, elem_rtc, elem_ruby, elem_rule,
    elem_s, elem_samp, elem_sarcasm, elem_scalarproduct, elem_script, elem_sdev, elem_search, elem_sec, elem_sech, elem_section, elem_select, elem_selector, elem_semantics,
        elem_sep, elem_separator, elem_set, elem_setdiff, elem_shadow, elem_share, elem_sidebar, elem_sin, elem_sinh, elem_slot, elem_small, elem_solidcolour,
        elem_source, elem_spacer, elem_span, elem_spot, elem_sqrt, elem_standby, elem_stop, elem_stoppropagation, elem_strike, elem_strong, elem_style, elem_sub,
        elem_subset, elem_sum, elem_summary, elem_sup, elem_svg, elem_switch, elem_symbol,
    elem_t, elem_tab, elem_tabbox, elem_table, elem_tan, elem_tanh, elem_tbody, elem_tbreak, elem_td, elem_template, elem_tendsto, elem_text, elem_textarea,
        elem_textpath, elem_tfoot, elem_th, elem_thead, elem_tilde, elem_time, elem_times, elem_title, elem_tr, elem_track, elem_traitdef, elem_transition,
        elem_transformer, elem_transpose, elem_tref, elem_true, elem_tspan, elem_tt,
    elem_u, elem_ul, elem_union, elem_uplimit, elem_use,
    elem_var, elem_variance, elem_veaffine, elem_vec, elem_vector, elem_vectoreffect, elem_vectorproduct, elem_veexclude, elem_vefill, elem_veintersect,
        elem_vejoin, elem_vemarker, elem_vemarkerpath, elem_vepath, elem_vepathref, elem_vereverse, elem_vesetback, elem_vestroke, elem_vestrokepath,
        elem_veunion, elem_video, elem_view, elem_vkern,
    elem_wbr,
    elem_xa, elem_xml, elem_xmp, elem_xor,

    elem_error
} e_element_tag;
const e_element_tag last_element_tag = elem_error;
typedef unsigned int e_element;

typedef enum { emi_good, emi_math, emi_not_this_math, emi_math_svg, emi_not_svg, emi_not_this_svg, emi_svg, emi_rdfa, emi_untested } e_emi;
typedef enum { ee_www, e_multi, ee_text } e_enctype;
typedef enum { es_end, es_start } e_end_start;
typedef enum { ens_end, ens_near, ens_start } e_ens;
typedef enum { ekh_done, ekh_enter, ekh_go, ekh_next, ekh_previous, ekh_search, ekh_send } e_enterkeyhint;
typedef enum {  env_args, env_auth_type, env_config, env_content_length, env_content_type, env_gateway_interface, env_http_accept, env_path_info,
                env_path_translated, env_query_string, env_remote_addr, env_remote_host, env_remote_user, env_request_method, env_script_name, env_server_name,
                env_server_port, env_server_protocol, env_server_software } e_environment;
CONSTEXPR ::std::size_t env_max = static_cast < ::std::size_t > (env_server_software) + 1;
typedef enum { eeb_additive, eeb_opaque, eeb_subtractive } e_environment_blending;
typedef enum {  evt_converted, evt_copied, evt_created, evt_cropped, evt_edited, evt_filtered, evt_formatted, evt_managed,
                evt_printed, evt_produced, evt_published, evt_resized, evt_saved, evt_version_updated } e_evt_action;
typedef enum { eii_r03, eii_r98, eii_thm } e_exif_intind;
typedef enum { ffls_first, ffls_first_except, ffls_last, ffls_start } e_ffls;
typedef enum { fa_bleedleft, fa_left, fa_centre, fa_right, fa_bleedright, fa_justify } e_figalign;
typedef enum { fa_freeze, fa_remove } e_fillanim;
typedef enum { fo_filled, fo_open } e_filled_open;
typedef enum { fr_nonzero, fr_evenodd, fr_inherit } e_fill_rule;
typedef enum { fv_strokepaint, fv_fillpaint } e_fill_ve;
typedef enum { fi_sourcegraphic, fi_sourcealpha, fi_backgroundimage, fi_backgroundalpha, fi_fillpaint, fi_strokepaint } e_filter_in;
typedef enum { fl_first, fl_last } e_first_last;

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
    fc_yellow, fc_yellowgreen,
} e_fixedcolour;

typedef enum { fz_fixed, fz_zoom } e_fixed_zoom;
typedef enum { fnrs_fast, fnrs_normal, fnrs_slow } e_fnrs;
typedef enum { fns_fast, fns_none, fns_slow } e_fns;
typedef enum { fe_caption, fe_icon, fe_menu, fe_message_box, fe_small_caption, fe_status_bar, fe_inherit } e_font_enum;

typedef enum {  fn_context, fn_serif, fn_sans_serif, fn_cursive, fn_fantasy, fn_monospace,
                fn_emoji, fn_fangsong, fn_math, fn_system_ui, fn_ui_monospace, fn_ui_rounded, fn_ui_sans_serif, fn_ui_serif,
                fn_al_bayan, fn_american_typewriter, fn_andale_mono, fn_apple_casual, fn_apple_chancery, fn_apple_garamond, fn_apple_gothic, fn_apple_ligothic, fn_apple_lisung,
                fn_apple_myungjo, fn_apple_symbols, fn_aquakana, fn_arial, fn_arial_black, fn_arial_hebrew, fn_ayuthaya, fn_baghdad, fn_bahnschrift, fn_baskerville, fn_beijing,
                fn_biaukai, fn_big_caslon, fn_browallia_new, fn_browalliaupc, fn_brush_script, fn_calibri, fn_cambria, fn_cambria_math, fn_candara, fn_cascadia_code, fn_cascadia_mono,
                fn_chalkboard, fn_chalkduster, fn_charcoal, fn_charcoal_cy, fn_chicago, fn_cochin, fn_comic_sans, fn_comic_sans_ms, fn_consolas, fn_constantia, fn_cooper,
                fn_copperplate, fn_corbel, fn_corsiva_hebrew, fn_courier, fn_courier_new, fn_decotype_naskh, fn_devanagari, fn_didot, fn_droid_sans, fn_droid_sans_mono, fn_droid_serif, fn_ebrima, fn_euphemia_ucas,
                fn_franklin_gothic_medium, fn_futura, fn_gabriola, fn_gadget, fn_gadugi, fn_geeza_pro, fn_geezah, fn_geneva, fn_geneva_cy, fn_georgia, fn_gill_sans, fn_gujarati,
                fn_gung_seoche, fn_gurmukhi, fn_hangangche, fn_headlinea, fn_hei, fn_helvetica, fn_helvetica_cy, fn_helvetica_neue, fn_herculanum, fn_hiragino_kaku_gothic_pro,
                fn_hiragino_kaku_gothic_pron, fn_hiragino_kaku_gothic_std, fn_hiragino_kaku_gothic_stdn, fn_hiragino_maru_gothic_pro, fn_hiragino_maru_gothic_pron,
                fn_hiragino_mincho_pro, fn_hiragino_mincho_pron, fn_hoefler_text, fn_hololens_mdl2_assets, fn_impact, fn_inai_mathi, fn_ink_free, fn_javanese_text, fn_jung_gothic,
                fn_kai, fn_keyboard, fn_krungthep, fn_kuenstler_script, fn_kufistandard_gk, fn_lastresort, fn_leelawadee_ui, fn_lihei_pro, fn_lisong_pro, fn_lucida_console,
                fn_lucida_sans, fn_lucida_sans_unicode, fn_ms_gothic, fn_mv_boli, fn_malgun_gothic, fn_marker_felt, fn_marlett, fn_menlo, fn_microsoft_himalaya, fn_microsoft_jhenghei,
                fn_microsoft_new_tai_lue, fn_microsoft_phagspa, fn_microsoft_sans_serif, fn_microsoft_tai_le, fn_microsoft_yahei, fn_microsoft_yi_baiti, fn_mingliu_extb,
                fn_monaco, fn_monaco_cy, fn_mongolian_baiti, fn_mshtakan, fn_myanmar_text, fn_nisc_gb18030, fn_nadeem, fn_new_peninim, fn_new_york, fn_nirmala_ui, fn_noto, fn_optima,
                fn_osaka, fn_pc_myungjo, fn_palatino, fn_palatino_linotype, fn_papyrus, fn_pilgiche, fn_plantagenet_cherokee, fn_raanana, fn_roboto, fn_st_fangsong, fn_st_fangsong_2,
                fn_st_heiti, fn_st_kaiti, fn_st_song, fn_sand, fn_sathu, fn_segoe_fluent_icons, fn_segoe_mdl2_assets, fn_segoe_print, fn_segoe_script, fn_segoe_ui,
                fn_segoe_ui_emoji, fn_segoe_ui_historic, fn_segoe_ui_symbol, fn_segoe_ui_variable, fn_seoul, fn_shin_myungjo_neue, fn_silom, fn_simsun, fn_sitka, fn_skia,
                fn_snell_roundhand, fn_sylfaen, fn_symbol, fn_tae_graphic, fn_tahoma, fn_taipei, fn_techno, fn_textile, fn_thonburi, fn_times, fn_times_cy, fn_times_new_roman,
                fn_trebuchet_ms, fn_verdana, fn_webdings, fn_wingdings, fn_yu_gothic, fn_zapf_chancery, fn_zapf_dingbats, fn_zapfino, fn_bespoke } e_fontname;

typedef enum { fs_italic, fs_normal } e_fontstyle;
typedef enum { fn_normal, fn_italic, fn_oblique } e_fontnia;
typedef enum {  fv2_normal, fv2_none, fv2_small_caps, fv2_all_small_caps, fv2_petite_caps, fv2_all_petite_caps, fv2_unicase, fv2_titling_caps,
                fv2_jis78, fv2_jis83, fv2_jis90, fv2_jis04, fv2_simplified, fv2_traditional, fv2_full_width, fv2_proportional_width,
                fv2_common, fv2_no_common, fv2_discretionary, fv2_no_discretionary, fv2_historical,
                fv2_no_historical, fv2_contextual, fv2_no_contextual, fv2_lining_nums, fv2_oldstyle_nums,
                fv2_proportional_nums, fv2_tabular_nums, fv2_diagonal_fractions, fv2_stacked_fractions, fv2_ordinal,
                fv2_slashed_zero, fv2_ruby, fv2_sub, fv2_super } e_font_variant_2;
typedef enum { fvc_normal, fvc_small_caps, fvc_all_small_caps, fvc_petite_caps, fvc_all_petite_caps, fvc_unicase, fvc_titling_caps } e_font_variant_caps;
typedef enum {  fvea_normal, fvea_jis78, fvea_jis83, fvea_jis90, fvea_jis04, fvea_simplified, fvea_traditional, fvea_full_width,
                fvea_proportional_width, fvea_ruby } e_font_variant_east_asian;
typedef enum { fve_auto, fve_emji, fve_text, fve_unicode } e_font_variant_emoji;
typedef enum {  fvl_normal, fvl_none, fvl_common, fvl_no_common, fvl_discretionary, fvl_no_discretionary, fvl_historical, fvl_no_historical,
                fvl_contextual, fvl_no_contextual } e_font_variant_ligature;
typedef enum {  fvn_normal, fvn_lining_nums, fvn_oldstyle_nums, fvn_proportional_nums, fvn_tabular_nums, fvn_diagonal_fractions,
                fvn_stacked_fractions, fvn_ordinal, fvn_slashed_zero } e_font_variant_numeric;
typedef enum { fvp_normal, fvp_sub, fvp_super } e_font_variant_position;
typedef enum { efc_active, efc_none } e_forced_colours;

typedef unsigned short e_format;

typedef enum {
    furi_json_ld, furi_ldpatch,
    furi_microdata,
    furi_n3,
    furi_n_quads, furi_n_triples,
    furi_owlfunctionalsyntax, furi_owlmanchestersyntax, furi_owlxmlserialization,
    furi_powder, furi_powder_s, furi_prov_n, furi_prov_xml,
    furi_rdf_json, furi_rdf_xml, furi_rdfa, furi_rifxmlsyntax,
    furi_sparqlresultsincsv, furi_sparqlresultsinjson, furi_sparqlresultsintsv, furi_sparqlresultsinxml,
    furi_trig, furi_turtle, } e_formaturi;

typedef enum { frrv_forward, frrv_reverse } e_forrev;
typedef enum { f4_blank, f4_parent, f4_self, fr_top } e_frame4;
typedef enum { fred_maestro, fred_bloggs } e_fred;
typedef enum { eg_p3, eg_rec2020, eg_srgb  } e_gamut;
typedef enum { g_female, g_male } e_gender;
typedef enum { gu_userspaceonuse, gu_objectboundingbox } e_gradientunits;
typedef enum { gn_grid, gn_normal } e_grid_normal;
typedef enum
{   gst_annotation, gst_character_variant, gst_content_name, gst_counter_style, gst_font_family, gst_highlight, gst_historical_form, gst_keyframe,
    gst_layer, gst_ornament, gst_page_name, gst_palette, gst_region, gst_scroll_anim, gst_styleset, gst_stylistic, gst_swash, gst_view, gst_max } e_gsstr;
typedef enum { al_left, al_center, al_right, al_justify, al_char } e_halign;
typedef enum { eh_hidden, eh_untilfound } e_hidden;

typedef enum
{   he_context,

    he_accept, he_accept_additions, he_accept_ch, he_accept_ch_lifetime, he_accept_charset, he_accept_datetime, he_accept_encoding, he_accept_features, he_accept_language,
        he_accept_patch, he_accept_post, he_accept_ranges, he_access_control, he_access_control_allow_credentials, he_access_control_allow_headers, he_access_control_allow_methods,
        he_access_control_allow_origin, he_access_control_expose_headers, he_access_control_max_age, he_access_control_request_headers, he_access_control_request_method, he_age,
        he_aim, he_allow, he_alpn, he_also_control, he_alt_svc, he_alt_used, he_alternatives, he_alternate_recipient, he_amp_cache_transformation, he_apparently_to,
        he_apply_to_redirect_ref, he_approved, he_arc_authentication_results, he_arc_message_signature, he_arc_seal, he_archive, he_archived_at, he_article_names, he_article_updates,
        he_authentication_control, he_authentication_info, he_authentication_results, he_author, he_authorisation, he_authorization, he_auto_submitted, he_autoforwarded,
        he_automated, he_autosubmitted,
    he_base, he_bcc, he_body,
    he_cache_control, he_cache_status, he_cal_managed_id, he_caldav_timezones, he_cancel_key, he_cancel_lock, he_cc, he_cdn_cache_control, he_cdn_loop, he_cert_not_after,
        he_cert_not_before, he_c_ext, he_clear_site_data, he_close, he_c_man, he_comments, he_configuration_context, he_connection, he_content_alternative, he_content_base,
        he_content_description, he_content_disposition, he_content_dpr, he_content_duration, he_content_encoding, he_content_features, he_content_id, he_content_identifier,
        he_content_language, he_content_length, he_content_location, he_content_md5, he_content_range, he_content_return, he_content_script_type, he_content_security_policy,
        he_content_security_policy_report_only, he_content_style_type, he_content_transfer_encoding, he_content_translation_type, he_content_type, he_content_version, he_control,
        he_conversion, he_conversion_with_loss, he_cookie, he_cookie2, he_c_opt, he_corp, he_c_pep, he_c_pep_info, he_cross_origin_embedder_policy,
        he_cross_origin_embedder_policy_report_only, he_cross_origin_opener_policy, he_cross_origin_opener_policy_report_only, he_cross_origin_resource_policy,
    he_date, he_date_received, he_dasl, he_dav, he_default_style, he_deferred_delivery, he_delivered_to, he_delivery_date, he_delta_base, he_depth, he_derived_from, he_destination,
        he_device_memory, he_differential_id, he_digest, he_discarded_x400_ipms_extensions, he_discarded_x400_mts_extensions, he_disclose_recipients,
        he_disposition_notification_options, he_disposition_notification_to, he_distribution, he_dkim_signature, he_dl_expansion_history, he_dnt, he_downgraded_bcc,
        he_downgraded_cc, he_downgraded_disposition_notification_to, he_downgraded_final_recipient, he_downgraded_from, he_downgraded_in_reply_to, he_downgraded_mail_from,
        he_downgraded_message_id, he_downgraded_original_recipient, he_downgraded_rcpt_to, he_downgraded_references, he_downgraded_reply_to, he_downgraded_resent_bcc,
        he_downgraded_resent_cc, he_downgraded_resent_from, he_downgraded_resent_reply_to, he_downgraded_resent_sender, he_downgraded_resent_to, he_downgraded_return_path,
        he_downgraded_sender, he_downgraded_to, he_downlink, he_dpr,
    he_early_data, he_ect, he_ediint_features, he_eesst_version, he_encoding, he_encrypted, he_errors_to, he_etag, he_except, he_expect, he_expect_ct, he_expires, he_expiry_date,
        he_ext, he_ext_cache,
    he_feature_policy, he_followup_to, he_form_sub, he_forwarded, he_from,
    he_generate_delivery_report, he_get_profile,
    he_hobareg, he_host, he_http2_settings, he_human,
    he_if, he_if_match, he_if_modified_since, he_if_none_match, he_if_range, he_if_schedule_tag_match, he_if_unmodified_since, he_im, he_imagetoolbar, he_importance,
        he_in_reply_to, he_include_referred_token_binding_id, he_incomplete_copy, he_injection_date, he_injection_info, he_isolation,
    he_jabber_id,
    he_keep_alive, he_keywords,
    he_label, he_language, he_large_allocation, he_last_event_id, he_last_modified, he_latest_delivery_time, he_lines, he_link, he_list_archive, he_list_help, he_list_id,
        he_list_owner, he_list_post, he_list_subscribe, he_list_unsubscribe, he_list_unsubscribe_post, he_location, he_lock_token,
    he_man, he_max_forwards, he_memento_datetime, he_message_context, he_message_id, he_message_type, he_meter, he_method_check, he_method_check_expires, he_mime_version,
        he_mmhs_acp127_message_identifier, he_mmhs_authorising_users, he_mmhs_codress_message_indicator, he_mmhs_copy_precedence, he_mmhs_exempted_address,
        he_mmhs_extended_authorisation_info, he_mmhs_handling_instructions, he_mmhs_message_instructions, he_mmhs_message_type, he_mmhs_originator_plad,
        he_mmhs_originator_reference, he_mmhs_other_recipients_indicator_cc, he_mmhs_other_recipients_indicator_to, he_mmhs_primary_precedence, he_mmhs_subject_indicator_codes,
        he_mt_priority,
    he_negotiate, he_nel, he_newsgroups, he_nntp_posting_date, he_nntp_posting_host,
    he_obsoletes, he_odata_entityid, he_odata_isolation, he_odata_maxversion, he_odata_version, he_opt, he_optional_www_authenticate, he_ordering_type, he_organisation,
        he_origin, he_origin_agent_cluster, he_original, he_original_encoded_information_types, he_original_from, he_original_message_id, he_original_recipient,
        he_original_sender, he_original_subject, he_originator_return_address, he_oscore, he_oslc_core_version, he_overwrite,
    he_p3p, he_page_enter, he_page_exit, he_path, he_pep, he_pep_info, he_pics_label, he_ping_from, he_ping_to, he_position, he_posting_version, he_pragma, he_prefer,
        he_preference_applied, he_prevent_nondelivery_report, he_priority, he_privicon, he_profile_object, he_protocol, he_protocol_info, he_protocol_query, he_protocol_request,
        he_proxy_authenticate, he_proxy_authenticate_info, he_proxy_authorisation, he_proxy_features, he_proxy_instruction, he_proxy_status, he_public, he_public_key_pins,
        he_public_key_pins_report_only,
    he_range, he_received, he_received_spf, he_redirect_ref, he_references, he_referrer, he_referrer_root, he_referrer_policy, he_refresh, he_relay_version,
        he_repeatability_client_id, he_repeatability_first_sent, he_repeatability_request_id, he_repeatability_result, he_replay_nonce, he_reply_by, he_reply_to,
        he_require_recipient_valid_since, he_resent_bcc, he_resent_cc, he_resent_date, he_resent_from, he_resent_message_id, he_resent_reply_to, he_resent_sender, he_resent_to,
        he_retry_after, he_return_path, he_rtt,
    he_safe, he_save_data, he_schedule_reply, he_schedule_tag, he_sec_ch_ua, he_sec_ch_ua_arch, he_sec_ch_ua_bitness, he_sec_ch_ua_full_version, he_sec_ch_ua_full_version_list,
        he_sec_ch_ua_mobile, he_sec_ch_ua_model, he_sec_ch_ua_platform, he_sec_ch_ua_platform_version, he_sec_fetch_dest, he_sec_fetch_mode, he_sec_fetch_site, he_sec_fetch_user,
        he_sec_gpc, he_sec_websocket_accept, he_sec_websocket_extensions, he_sec_websocket_key, he_sec_websocket_protocol, he_sec_websocket_version, he_security_scheme,
        he_see_also, he_sender, he_sensitivity, he_server, he_server_timing, he_service_worker_navigation_preload, he_set_cookie, he_set_cookie2, he_setprofile, he_sio_label,
        he_sio_label_history, he_site_enter, he_site_exit, he_slug, he_soapaction, he_solicitation, he_sourcemap, he_status_uri, he_strict_transport_security, he_subject,
        he_summary, he_sunset, he_supersedes, he_surrogate_capability, he_surrogate_control,
    he_tcn, he_te, he_timing_allow_origin, he_timeout, he_tk, he_tls_report_domain, he_tls_report_submitter, he_tls_required, he_to, he_topic, he_trailer, he_traceparent,
        he_tracestate, he_transfer_encoding, he_ttl,
    he_upgrade, he_upgrade_insecure_requests, he_urgency, he_uri, he_user_agent,
    he_variant_vary, he_vary, he_vbr_info, he_via, he_viewport_width,
    he_want_digest, he_warning, he_webkit_csp, he_width, he_window_target,
    he_www_authenticate, he_x400_content_identifier, he_x400_content_return, he_x400_content_type, he_x400_mts_identifier, he_x400_originator, he_x400_received,
    he_x400_recipients, he_x400_trace, he_x_clacks_overhead, he_x_archived_at, he_x_content_security_policy, he_x_content_type_options, he_x_dns_prefetch_control,
    he_x_forwarded_for, he_x_forwarded_host, he_x_forwarded_proto, he_x_frame_options, he_x_mittente, he_x_pgp_sig, he_x_ricevuta, he_x_riferimento_message_id,
    he_x_tiporicevuta, he_x_trasporto, he_x_ua_compatible, he_x_verificasicurezza, he_x_xss_protection, he_xref,
    he_error } e_httpequiv;

typedef enum { ehv_horizontal, ehv_vertical } e_hv;
typedef enum { if_sec, ical_min, ical_hour, ical_day, ical_week, ical_month, ical_year } e_icalfreq;
typedef enum {  icc_CGATS21_2_CRPC1, icc_CGATS21_2_CRPC2, icc_CGATS21_2_CRPC3, icc_CGATS21_2_CRPC4, icc_CGATS21_2_CRPC5, icc_CGATS21_2_CRPC6, icc_CGATS21_2_CRPC7,
                icc_CGATS_GRACoL_TR006_2007, icc_CGATS_SNAP_TR002_2007, icc_CGATS_SWOP_TR003_2007, icc_CGATS_SWOP_TR005_2007, icc_FOGRA39, icc_FOGRA40, icc_FOGRA47,
                icc_FOGRA51, icc_FOGRA52, icc_FOGRA54, icc_Japan_Color_2011 } e_icc;
typedef enum { iiu_none, iiu_inherit, iiu_initial, iiu_revert, iiu_revert_layer, iiu_unset } e_iiu;
typedef enum { ir_auto, ir_crisp_edges, ir_high_quality, ir_optimisespeed, ir_optimisequality, ir_inherit, ir_pixelated, ir_smooth } e_image_rendering;
typedef enum { ei_auto, ei_high, ei_low } e_importance;
typedef enum { ia_left, ia_centre, ia_right, ia_auto, ia_id } e_indentalign;
typedef enum { ifl_before, ifl_after, ifl_duplicate } e_infixlinebreakstyle;
typedef enum { iv_whenstarted, iv_always } e_initialvisibility;
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
typedef enum { ih_infix, ih_postfix, ih_prefix, ih_silent } e_intent_hint;
typedef enum { eic_inverted, eic_none } e_inverted_colours;
typedef enum { itemprop_bespoke, itemprop_schema, itemprop_microformat } e_itemprop_category;
typedef enum { itemtype_none, itemtype_schema, itemtype_microformat, itemtype_rel } e_itemtype_category;
typedef enum { jsonld_none, jsonld_1_0, jsonld_1_1 } e_jsonld_version;

// these must be in processing order as per processing a JSON-LD object
typedef enum
{   jt_unused,
    jt_list, jt_set,
    jt_context,
    jt_type,

    jt_base,
    jt_container,
    jt_direction,
    jt_graph,
    jt_id, jt_import, jt_included, jt_index,
    jt_json,
    jt_language,
    jt_nest, jt_none,
    jt_prefix, jt_propagate, jt_protected,
    jt_reverse,
    jt_value, jt_version, jt_vocab,
    jt_error } e_jtoken;

typedef enum { kmn_k, kmn_m, kmn_n } e_k_m_n;
typedef enum { kew_none, kew_scan, kew_examine, kew_error } e_kew;
typedef enum { ky_dsa, ky_ec, ky_rsa } e_keytype;
typedef enum { k_subtitles, k_captions, k_descriptions, k_chapters, k_metadata } e_kind;

typedef enum
{   la_context,

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
typedef enum { lcrn_left, lcrn_right, lcrn_none } e_lrnalign;
typedef enum { li_clear, li_float, li_left, li_right, li_none, li_inherit } e_lrnialign;
typedef enum { l_cm, l_mm, l_q, l_in, l_pc, l_pt, l_px } e_length_absolute;
typedef enum { l_percent, l_star, l_em, l_ex, l_cap, l_ch, l_ic, l_rem, l_lh, l_rlh, l_vw, l_vh, l_vi, l_vb, l_vmin, l_vmax } e_length_relative;
typedef enum { lad_spacing, lad_spacingandglyphs } e_lengthadjust;
typedef enum { lb_auto, lb_newline, lb_indentingnewline, lb_nobreak, lb_goodbreak, lb_badbreak } e_linebreak;
typedef enum { ls_before, ls_after, ls_duplicate, ls_infixlinebreakstyle } e_linebreakstyle;
typedef enum { lc_butt, lc_round, lc_square, lc_inherit } e_linecap;
typedef enum { lj_miter, lj_round, lj_bevel, lj_inherit } e_linejoin;
typedef enum { lp_rel, lp_anchor, lp_rev, lp_hreflang, lp_media, lp_title, lp_titlestar, lp_type } e_linkparam;
typedef enum { li_1, li_a, li_A, li_i, li_I } e_listtype;
typedef enum { ln_literal_punctuation, ln_no_punctuation } e_literal_or_not;
typedef enum { lnr_left, lnr_near, lnr_right } e_lnr;
typedef enum { b_eager, b_lazy } e_loading;
typedef enum {  ls_lefttop, ls_stackedrightright, ls_mediumstackedrightright, ls_shortstackedrightright, ls_righttop,
                ls_leftslashright, ls_leftketbraright, ls_rightequalright, ls_stackedleftleft, ls_stackedleftlinetop } e_longdivstyle;
typedef enum {  lox_none, lox_cache, lox_crosslinks, lox_css, lox_curl, lox_dear, lox_eleanor, lox_external, lox_fileindex, lox_flox, lox_itemid,
                lox_itemprop, lox_nits, lox_ns, lox_out, lox_q, lox_rdfa, lox_stats, lox_time, lox_xlynx, lox_error } e_lox;
typedef enum { lra_all, lra_left, lra_right } e_lraalign;
typedef enum { lr_left, lr_right } e_lralign;
typedef enum { lzz_legacy, lzz_zero_if_extrinsic, lzz_zero_if_scroll } e_lzz;
typedef enum { mah_go, mah_done, mah_next, mah_search, mah_send } e_mah;
typedef enum { mp_mandatory, mp_proximity } e_mand_prox;
typedef enum { mn_manual, mn_normal } e_manual_normal;
typedef enum { mp_margin, mp_padding } e_margin_padding;
typedef enum { mu_strokewidth, mu_userspaceonuse } e_markerunits;
typedef enum { msp_match_parent, msp_match_self } e_match_self_parent;
typedef enum { ma_axis, ma_baseline, ma_bottom, ma_centre, ma_top } e_mathalign;
typedef enum { mc_open, mc_closed, mc_openclosed, mc_closedopen } e_mathclosure;
typedef enum { ml_w, ml_nw, ml_n, ml_ne, ml_e, ml_se, ml_s, ml_sw } e_mathlocation;
typedef enum { mo_prefix, mo_infix, mo_functionmodel } e_mathoccurence;
typedef enum { mo_numeric, mo_lexicographic } m_mathorder;
typedef enum { ov_elide, ov_linebreak, ov_scale, ov_scroll, ov_truncate } e_mathoverflow;
typedef enum { ms_global, ms_local } e_mathscope;
typedef enum { math_none, math_1, math_2, math_3, math_4_20, math_4_22, math_core } e_math_version;
constexpr e_math_version last_math = math_core;
typedef enum { mf_infix, mf_prefix, mf_postfix } e_mathform;
typedef enum { fmw_bold, fmw_normal } e_math_fontweight;
typedef enum { mf_dash, mf_none, mf_solid } e_mathframe;
typedef enum {  mn_longdiv, mn_actuarial, mn_radical, mn_box, mn_roundedbox, mn_circle, mn_left, mn_right, mn_top, mn_bottom,
                mn_updiagonalstrike, mn_downdiagonalstrike, mn_verticalstrike, mn_horizontalstrike, mn_phasorangle,
                mn_madruwb, mn_uparrow, mn_rightarrow, mn_downarrow, mn_leftarrow, mn_northwestarrow, mn_southwestarrow,
                mn_southeastarrow, mn_northeastarrow, mn_updownarrow, mn_leftrightarrow, mn_northwestsoutheastarrow,
                mn_northeastsouthwestarrow } e_mathnotation;
typedef enum { sim_left, sim_right, sim_leftoverlap, sim_rightoverlap } e_mathside;
typedef enum {  mv_normal, mv_bold, mv_italic, mv_bolditalic, mv_doublestruck, mv_boldfraktur, mv_script, mv_boldscript, mv_fraktur,
                mv_sansserif, mv_boldsansserif, mv_sansserifitalic, mv_sansserifbolditalic, mv_monospace, mv_initial, mv_tailed,
                mv_looped, mv_stretched } e_mathvariant;
typedef enum { mt_matrix, mt_saturate, mt_huerotate, mt_luminancetoalpha } e_matrixtype;
typedef enum {  md_context,
                md_active, md_additive, md_all, md_and, md_any_hover, md_any_pointer, md_aspect_ratio, md_aural,
                md_back, md_braille, md_brac, md_browser,
                md_cm, md_coarse, md_colon, md_colour, md_colour_gamut, md_colour_index, md_comma, md_custom, md_custom_media,
                md_dark, md_device_aspect_ratio, md_device_height, md_device_width, md_display_mode, md_dpcm, md_dpi, md_dynamic_range,
                md_em, md_embossed, md_enabled, md_environment_blending, md_eq,
                md_fast, md_fine, md_forced_colours, md_fullscreen,
                md_grid, md_gt, md_gteq,
                md_handheld, md_height, md_high, md_horizontal_viewport_segments, md_hover,
                md_infinite, md_initial_only, md_interlace, md_inverted, md_inverted_colours,
                md_ket,
                md_landscape, md_less, md_light, md_lt, md_lteq,
                md_max_aspect_ratio, md_max_colour, md_max_colour_index, md_max_device_aspect_ratio, md_max_device_width, md_max_device_height,
                    md_max_height, md_min_horizontal_viewport_segments, md_max_monochrome, md_max_resolution, md_max_width, md_max_vertical_viewport_segments, 
                    md_media, md_min_aspect_ratio, md_min_colour, md_min_colour_index, md_min_device_aspect_ratio, md_min_device_width, md_min_device_height,
                    md_min_height, md_max_horizontal_viewport_segments, md_min_monochrome, md_min_resolution, md_min_width, md_min_vertical_viewport_segments,
                    md_minimal_ui, md_monochrome, md_more,
                md_nav_controls, md_negative, md_no_preference, md_none, md_not,
                md_only, md_opaque, md_or, md_orientation, md_overflow_block, md_overflow_inline,
                md_p3, md_paged, md_pointer, md_portrait, md_positive, md_prefers_colour_scheme, md_prefers_contrast, md_prefers_reduced_data,
                    md_prefers_reduced_motion, md_prefers_reduced_transparency, md_print, md_progressive, md_projection, md_px,
                md_reader, md_rec2020, md_rect, md_reduce, md_resolution, md_round,
                md_scan, md_screen, md_scripting, md_scroll, md_selector, md_shape, md_slash, md_slow, md_space, md_speech, md_srgb, md_standalone, 
                    md_standard, md_subtractive, md_supports,
                md_tty, md_tv,
                md_update,
                md_vertical_viewport_segments, md_video_colour_gamut, md_video_dynamic_range,
                md_width,
                md_error } e_media;
typedef enum { mdm_browser, mdm_full_screen, mdm_minimal_ui, mdm_standalone } e_media_display_mode;
typedef enum { emh_hover, emh_none } e_media_hover;
typedef enum { emi_none, emi_scroll } e_media_inline;
typedef enum { emo_landscape, emo_portrait } e_media_orientation;
typedef enum { emo_none, emo_paged, emo_scroll } e_media_overflow;
typedef enum { emp_coarse, emp_fine, emp_none } e_media_pointer;
typedef enum { mpr_no_preference, mpr_reduce } e_media_prefers;
typedef enum { pr2_custom, pr2_less, pr2_no_preference, pr2_more } e_media_prefers_2;
typedef enum { ems_enabled, ems_initial_only, ems_none } e_media_scripting;
typedef enum { ms_meet, me_slice } e_meetslice;
typedef enum { mi_command, mi_checkbox, mi_radio } e_menuitem;
typedef enum { mt_context, mt_popup, mt_toolbar } e_menutype;
typedef enum { md_delete, md_dialogue, md_get, md_post, md_put } e_method;

typedef enum {
    mn_context,
// https://www.w3.org/html/wiki/Elements/meta
    mn_application, mn_author, mn_description, mn_generator, mn_keywords,
    // HTML 4.01 specification
    mn_identifier,
    // http://ec.europa.eu/ipg/content/optimise/metadata/annex2_en.htm
    mn_classification,
    // https://www.metatags.org/
    mn_copyright, // despite metatags opinion, I suggest this metaname still has legal relevance
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
    mn_og_audio, mn_og_determiner, mn_og_locale_alternate, mn_og_video, mn_og_image_url, mn_og_image_secure_url, mn_og_image_type, mn_og_image_width,
    mn_og_image_height, mn_og_image_alt, mn_og_video_url, mn_og_video_secure_url, mn_og_video_width, mn_og_video_height, mn_og_video_alt,
    mn_og_audio_url, mn_og_audio_secure_url, mn_og_audio_type, mn_music_album, mn_music_album_disc, mn_music_album_track, mn_music_creator, mn_music_duration,
    mn_music_musician, mn_music_release_date, mn_music_song, mn_music_song_disc, mn_music_song_track, mn_video_actor, mn_video_actor_role, mn_video_director,
    mn_video_duration, mn_video_release_date, mn_video_series, mn_video_tag, mn_video_writer, mn_article_author, mn_article_expiration_date,
    mn_article_modified_time, mn_article_published_time, mn_article_section, mn_article_tag, mn_book_author, mn_book_isbn, mn_book_release_date, mn_book_tag,
    mn_profile_first_name, mn_profile_gender, mn_profile_last_name, mn_profile_username,
    // https://www.bing.com/webmasters/help/which-robots-metatags-does-bing-support-5198d240
    mn_bingbot, mn_msnbot,
    // https://developers.google.com/search/docs/crawling-indexing/robots-meta-tag
    mn_googlebot_news, mn_adbots_google,
    // https://developers.google.com/search/docs/crawling-indexing/overview-google-crawlers
    mn_googlebot_image, mn_googlebot_video, mn_storebot_google, mn_google_inspection_tool, mn_googleother,
    // harvested
    mn_360spider,
    mn_ahrefsbot, mn_apache_httpclient, mn_applebot, mn_archive_org_bot,
    mn_baidu, mn_baiduspider, mn_blexbot,
    mn_cfnetwork, mn_coccoc, mn_core, mn_crawl, mn_curl,
    mn_dalvik, mn_dataprovider_com, mn_dotbot, mn_duckduckgo_favicons_bot,
    mn_facebookexternalhit, mn_feed, mn_feedfetcher_google, mn_fetcher, mn_firefox,
    mn_gigablastopensource, 
    mn_harvest,
    mn_infobot,
    mn_java,
    mn_konqueror,
    mn_link, mn_linkdexbot,
    mn_mail_ru, mn_megaindex_ru, mn_mj12bot, mn_mojeekbot, mn_msie,
    mn_nautic, mn_nbot, mn_netcraft, mn_netnewswire,
    mn_obot,
    mn_python, mn_python_urllib,
    mn_riddler, mn_rome,
    mn_seek, mn_semrushbot, mn_seznambot, mn_sitebot, mn_sogou, mn_surdotlybot,
    mn_urllib,
    mn_validator,
    mn_wget, mn_windows,
    mn_yacybot, mn_yandexbot, mn_yandeximages,         
    // that's it
    mn_illegal } e_metaname;
const e_metaname metaname_first_w3 = mn_application;
const e_metaname metaname_first_eu = mn_classification;
const e_metaname metaname_first_outdated = mn_contactCity;
const e_metaname metaname_first_archaic = mn_abstract;
const e_metaname metaname_first_whatwg = mn_aglsterms_accessmode;
const e_metaname metaname_first_dubious = mn_blogcatalog;
const e_metaname metaname_first_rejected = mn_cache;

typedef enum { mfa_out_of_stock, mfa_in_stock, mfa_instore_only, mfa_preorder } e_mf_availability;
typedef enum { mfc_meeting, mfc_appointment, mfc_conference, mfc_expo } e_mf_category;
typedef enum { mfc_public, mfc_private, mfc_confidential } e_mf_class;
typedef enum { mfi_model, mfi_mpn, mfi_upc, mfi_isbn, mfi_issn, mfi_ean, mfi_jan, mfi_sn, mfi_vin, mfi_sku } e_mf_identifier;
typedef enum { mfit_opening, mfit_housing, mfit_product, mfit_business, mfit_event, mfit_person, mfit_place, mfit_website, mfit_url } e_mf_itemtype;
typedef enum { mfla_sell, mfla_rent, mfla_trade, mfla_meet, mfla_announce, mfla_offer, mfla_wanted, mfla_event, mfla_service } e_mf_listing_action;
typedef enum { mfm_none, mfm_publish, mfm_request, mfm_reply, mfm_add, mfm_cancel, mfm_refresh, mfm_counter, mfm_declinecounter } e_mf_method;
typedef enum { mfr_product, mfr_business, mfr_event, mfr_person, mfr_place, mfr_website, mfr_url } e_mf_reviewtype;
typedef enum { mfs_tentative, mfs_confirmed, mfs_cancelled } e_mf_status;
typedef enum { mc_application, mc_audio, mc_example, mc_font, mc_image, mc_model, mc_multipart, mc_text, mc_video } e_mime_category;

typedef enum {
    mime_context,

    // standard ish...
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
    mime_application_mediaservercontrol_xml, mime_application_merge_patch_json, mime_application_metalink4_xml, mime_application_mets_xml, mime_application_MF4,
    mime_application_microdata_json, mime_application_mikey,
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
    mime_application_vnd_syncml_xml, mime_application_vnd_tableontology_json, mime_application_vnd_tao_intent_module_archive,
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
    mime_application_x_javascript, mime_application_x_pki_message, mime_application_x_shockwave_flash, mime_application_x_webfont,
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
    mime_text_event_stream, mime_text_example, mime_text_flexfec, mime_text_fwdred, mime_text_grammar_ref_list, mime_text_html,
    mime_text_html_sandboxed, mime_text_javascript, mime_text_javascript_x, mime_text_javascript10, mime_text_javascript11, mime_text_javascript12,
    mime_text_javascript13, mime_text_javascript14, mime_text_javascript15, mime_text_jcr_cnd, mime_text_jscript, mime_text_livescript,
    mime_text_markdown, mime_text_mizar, mime_text_n3, mime_text_parameters, mime_text_parityfec, mime_text_ping, mime_text_plain,
    mime_text_provenance_notation, mime_text_prs_fallenstein_rst, mime_text_prs_lines_tag, mime_text_prs_prop_logic, mime_text_raptorfec,
    mime_text_RED, mime_text_rfc822_headers, mime_text_richtext, mime_text_rtf, mime_text_rtp_enc_aescm128, mime_text_rtploopback,
    mime_text_rtx, mime_text_SGML, mime_text_strings, mime_text_t140, mime_text_tab_separated_values, mime_text_tcl, // HTML 4.01 spec example
    mime_text_troff, mime_text_turtle, mime_text_ulpfec, mime_text_uri_list, mime_text_vbscript, // HTML 4.01 spec example
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

    // other
    mime_application_7z, mime_video_x_flv,

    mime_bork } e_mimetype;

typedef enum { mo_dilate, mo_erode } e_morphology_operator;
typedef enum { mo_display, mo_inline } e_mode;
typedef enum { mk_a, mk_asharp, mk_b, mk_c, mk_csharp, mk_d, mk_dsharp, mk_e, mk_f, mk_fsharp, mk_g, mk_gsharp } e_musickey;

// for foaf
// Note: Myers Briggs Type Indicator and MBTI are registered trademarks of Consulting Psychologists Press Inc. Oxford Psychologists Press Ltd has exclusive rights to the trademark in the UK.
// Note: it's pseudoscience. See the Skeptics' Guide to the Universe for gen.
// IMHO, if a prospective employer/client/partner etc. wants to use them, then, at the very least, their HR department has issues: I would suggest looking elsewhere. 
typedef enum { mb_ESTJ, mb_INFP, mb_ESFP, mb_INTJ, mb_ESFJ, mb_INTP, mb_ENFP, mb_ISTJ, mb_ESTP, mb_INFJ, mb_ENFJ, mb_ISTP, mb_ENTJ, mb_ISFP, mb_ENTP, mb_ISFJ } e_myersbriggs;
typedef enum { ns_n, ns_s } e_n_s;

typedef enum
{   nd_negativeveryverythinmathspace, nd_negativeverythinmathspace, nd_negativethinmathspace, nd_negativemediummathspace,
    nd_negativethickmathspace, nd_negativeverythickmathspace, nd_negativeveryverythickmathspace, nd_veryverythinmathspace,
    nd_verythinmathspace, nd_thinmathspace, nd_mediummathspace, nd_thickmathspace, nd_verythickmathspace, nd_veryverythickmathspace } e_namedspace;

typedef enum
{   ns_default,
    ns_bibo,
    ns_cc, ns_crs, ns_crs2,
    ns_dbp, ns_dbp_owl, ns_dbr, ns_dc, ns_dcterms, ns_dt,
    ns_ebuttm, ns_ebutts, ns_err, ns_ex, ns_exsl,
    ns_fn, ns_fo, ns_foaf,
    ns_html,
    ns_ims, ns_its, ns_ittm, ns_ittp, ns_itts, ns_ittx, ns_ittxi, ns_ittxt,
    ns_math,
    ns_odd, ns_oex, ns_owl, ns_owlxml,
    ns_pam, ns_pamp, ns_pccm, ns_pcm, ns_pcv, ns_pdf, ns_photoshop, ns_pim, ns_pmi, ns_prism, ns_prism_ad, ns_prl, ns_prm, ns_prs,ns_psv, ns_pur,
    ns_rdf, ns_rdfa, ns_rdfs, ns_rddl,
    ns_saxon, ns_smil, ns_smpte, ns_stdim, ns_stevt, ns_stfnt, ns_stjob, ns_stref, ns_stver, ns_svg,
    ns_tt, ns_ttf, ns_ttp, ns_tts,
    ns_v, ns_vcard,
    ns_xalan, ns_xf, ns_xhv, ns_xi, ns_xlink, ns_xhtml, ns_xmlevents, ns_xmlns, ns_xmp, ns_xmpbj, ns_xmpdm, ns_xmpg, ns_xmpgimg, ns_xmpidq, ns_xmpmm,
        ns_xmprights, ns_xmptpg, ns_xs, ns_xsi, ns_xslt, ns_xtm,
    ns_error } e_namespace;

CONSTEXPR ::std::size_t first_runtime_namespace = static_cast < ::std::size_t > (ns_error) + 1;

typedef enum { nc_back, nc_none } e_nav_controls;

typedef enum
{   nit_free,

    // crash
    nit_internal_parsing_error, nit_symbol_aleady_defined,

    // catastrophe
    nit_math, nit_svg, nit_no_compound, nit_doctype_incomprehensible, nit_element_offsite_base, nit_missing_set_value, nit_no_curl, nit_cannot_create_file,
    nit_cannot_write, nit_cannot_delete, nit_cannot_update, nit_cannot_read, nit_wrong_secret,

    // everything else
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
    nit_bespoke_element, nit_deprecated_element, nit_duplicate_microformat, nit_unrecognised_class, nit_unrecognised_rel, nit_duplicate_rel, nit_blocking,
    nit_pos_piracy, nit_url_empty_password, nit_url_insecure_password, nit_url_missing_at, nit_chocolate_teapot,
    nit_html_recognised, nit_presume_html_tags, nit_presume_html_1, nit_public_missing, nit_sq_brac_ket, nit_enquote_value, nit_double_angular_open, nit_use_quote_code, nit_use_double_quote_code,
    nit_lonely_ampersand, nit_empty_character_code, nit_bizarre_character_code, nit_empty_denary_code, nit_empty_hex_code, nit_dubious_denary, nit_invalid_denary, nit_code_unrecognised_here,
    nit_double_slash, nit_unknown_element, nit_protocol, nit_write_wrote,
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
    nit_out_of_scope, nit_ignoring_extra_content, nit_missing_content, nit_equiv_refresh, nit_x_ua_compatible, nit_use_metaname, nit_not_html2_level_1,
    nit_bad_compact, nit_url_missing_username, nit_1_to_7, nit_plus_1_7, nit_attribute_required, nit_frameset_body, nit_unknown_xml, nit_xhtml_missing_slash,
    nit_xhtml_element_lc, nit_xhtml_quote_values, nit_xhtml_attribute_lc, nit_xhtml_existential_makework, nit_existential_value, nit_xhtml_enum_lc,
    nit_xhtml_hex_lc, nit_attribute_repeated, nit_eof_in_cdata, nit_xhtml_cdata, nit_negative_dosh, nit_mf_empty, nit_bad_rating, nit_no_tel,
    nit_xhtml_css, nit_naughty_lang, nit_nahtch, nit_charset_redefined, nit_not_utf_8, nit_no_content, nit_default_role, nit_bad_role,
    nit_use_datetime, nit_alt_title, nit_naughty_alt, nit_data_type, nit_typemustmatch, nit_missing_dynamic, nit_bad_meta_place, nit_bad_ancestor,
    nit_value_ol, nit_too_many_figcaption, nit_figcaption_middle, nit_missing_case, nit_requires_html, nit_overallowed, nit_saucy_source,
    nit_area_map_template, nit_requires_href, nit_bad_aspect_ratio, nit_bad_2pt, nit_table_manners, nit_unreal, nit_no_namespaces_left,
    nit_xmlns_namespace, nit_table_children, nit_colgroup_children, nit_input_bad_mix, nit_option_child, nit_fieldset_legend, nit_bad_noscript,
    nit_src_required, nit_element_unconstructed, nit_requires_xhtml, nit_text_content, nit_daft_rel_attr, nit_link_rel_off, nit_autofocus,
    nit_virtual_exception, nit_bad_parameter, nit_bad_path, nit_scan_failed, nit_examine_failed, nit_stage, nit_id_hidden, nit_empty_link,
    nit_requires_itemscope, nit_missing_itemtype, nit_bad_itemprop, nit_double_gin_and_tonic, nit_lang_xmllang, nit_no_xmllang,
    nit_avoid_manifest, nit_base_b4_lynx, nit_as_not_image, nit_bad_srcset, nit_mq_syntax, nit_attempted_escape, nit_no_such_folder,
    nit_dinosaur, nit_no_main_kids, nit_bad_descendant, nit_dl_div, nit_no_dd, nit_dl_ancestor, nit_figcaption_first_last, nit_dt_dd,
    nit_rfc_1867, nit_rfc_1942, nit_rfc_1980, nit_rfc_2070, nit_file_requires_enctype, nit_form_urlencoded, nit_use_post, nit_mime_list,
    nit_no_exec, nit_unknown_ssi, nit_attribute_assignment, nit_invalid_config, nit_invalid_set, nit_invalid_echo, nit_unsupported_code,
    nit_ssi_include_error, nit_invalid_fsize, nit_ssi_if, nit_linechange, nit_no_if, nit_invalid_flastmod, nit_ssi_syntax, nit_cannot_access,
    nit_key, nit_interactive, nit_tabindex, nit_ontology_url, nit_unrecognised_ontology, nit_ontology_domain, nit_mix_ruby_non, nit_too_many_ruby,
    nit_no_rp, nit_too_many_rp, nit_not_img, nit_bad_iframe, nit_bad_embed, nit_wild_attribute, nit_attribute_barred, nit_bad_object,
    nit_disordered_param, nit_source_track, nit_src_source, nit_media_descendants, nit_autoplay, nit_out_of_order, nit_kind_media_srclang,
    nit_track_default, nit_name_id, nit_need_coords, nit_bad_coords, nit_1000, nit_bad_header_id, nit_form_charset, nit_deprecated_value,
    nit_bad_for, nit_label_parentage, nit_input_bad_aria, nit_illegal_value, nit_bad_email, nit_bang_path, nit_unacceptable, nit_lonely_radio,
    nit_minmax, nit_pattern, nit_bad_datalist_id, nit_placeholder, nit_bad_form, nit_bad_select, nit_bad_datalist, nit_bad_option,
    nit_bad_textarea, nit_no_progress, nit_bad_meter, nit_not_form, nit_special_name, nit_solo, nit_bad_autocomplete, nit_snafu,
    nit_details_summary, nit_summary_header, nit_bad_dialogue, nit_bad_contextmenu, nit_bad_script, nit_bad_itemid, nit_untidy_string,
    nit_no_itemscope, nit_new_itemprop, nit_type_error, nit_ontology_property, nit_forgotten_name, nit_incompatible_itemtype, nit_inlist,
    nit_ontology_hierarchy, nit_html, nit_angle, nit_svg_version, nit_bad_rgb, nit_bad_frequency, nit_icc_colour, nit_svg_ancestor, nit_rdf,
    nit_bad_namespace, nit_svg_rdf, nit_clipped, nit_mf_infer, nit_path_spec, nit_lighting, nit_animatemotion,
    nit_fontface, nit_switch, nit_transform, nit_attribute_name, nit_repeated_attribute, nit_svg_xy, nit_fontstyle, nit_svg_math,
    nit_fontstretch, nit_fontvariant, nit_fontweight, nit_panose_1, nit_icarus, nit_vector_effect, nit_paint, nit_0_1, nit_1_more,
    nit_dashed, nit_marker, nit_background, nit_bad_result, nit_not_ontology_property, nit_curses, nit_xlinktype, nit_xlinkactuate,
    nit_dur, nit_svg_values, nit_rotate, nit_origin, nit_colour_matrix, nit_math_kids, nit_bad_hunit, nit_bad_vunit, nit_too_many,
    nit_use_apply, nit_base, nit_declare_first, nit_arg_count, nit_operator_required, nit_bad_bvar, nit_bad_doa, nit_bad_piece,
    nit_annotation, nit_eof_in_annotation, nit_prefix_odd, nit_prefix_format, nit_rdfa_redefine, nit_rdfa_confusion, nit_rdf_protocol,
    nit_math_href, nit_math_empty, nit_mglyph_alt_src, nit_dir_rtl_ltr, nit_bad_linebreak, nit_non_standard_value, nit_mscarries_last,
    nit_bad_bind, nit_bad_share, nit_shadow, nit_out_of_memory, nit_duplicate, nit_shadow_failed, nit_create_folder, nit_internal_file_error,
    nit_shadow_ignore, nit_shadow_link, nit_shadow_copy, nit_too_big, nit_icu, nit_lang_redefined, nit_page_charset, nit_charset_mismatch,
    nit_charset_used, nit_charset_invalid, nit_no_converters, nit_xhtml_superseded, nit_not_iso_8859_1, nit_draft_html_5, nit_overriding_html,
    nit_whatwg_class, nit_opening_file, nit_target, nit_bad_mummy, nit_no_serviceworker, nit_rel_head, nit_theme_colour, nit_refresh_zero,
    nit_bad_csp_directive, nit_bad_number_once, nit_bad_csp_source, nit_invalid_algorithm, nit_insufficient_content, nit_bad_q,
    nit_bad_cookie, nit_bad_cache, nit_bad_link_pragma, nit_nocando, nit_bad_root, nit_isnt, nit_menu_type, nit_menu_child, nit_bad_dl,
    nit_repeated_definition, nit_contradictory_expansion, nit_naughty_grave, nit_encode, nit_svg_data, nit_data, nit_bad_wild,
    nit_risky_filetype, nit_reputation, nit_incompatible_mime, nit_os_dependent, nit_bad_usemap, nit_bad_type_attribute, nit_bad_pattern,
    nit_bad_command, nit_bad_datagrid, nit_script, nit_menubar, nit_bad_card, nit_nest, nit_registration_mark, nit_bad_ref, nit_font,
    nit_dashdash, nit_naked_grave, nit_prototype, nit_bad_property, nit_hour, nit_minute, nit_second, nit_deprecated_ontology,
    nit_character_code, nit_note, nit_aria_position, nit_impure_mn, nit_program_error, nit_xhtml_5_0, nit_html_superseded,
    nit_function, nit_zero_to_one, nit_percent, nit_fontname, nit_glyphname, nit_keytimes, nit_keysplines, nit_not_n, nit_syntax,
    nit_viewbox, nit_custom, nit_duplicate_namespace, nit_contradictory_namespace, nit_unrecognised_namespace, nit_out_of_range,
    nit_math_or_svg, nit_many_maybe, nit_not_combine, nit_font_enum, nit_altglyphdef, nit_line_increment, nit_is_property,
    nit_better_as_property, nit_colour_profile, nit_feconvolvematrix, nit_not_0, nit_fecomponenttransfer, nit_fecomposite,
    nit_style_fixed, nit_anim_simple_id, nit_id_category, nit_not_animatable, nit_shadow_delete, nit_root_change, nit_virtual_change,
    nit_shadow_unnecessary, nit_deleted_bad_file, nit_abandon, nit_prefix_again, nit_namespace_unknown, nit_missing_id, nit_namespace_confusion,
    nit_namespace_redefine, nit_no_lang, nit_null_datatype, nit_unknown_datatype, nit_rdfa_version, nit_bad_sha, nit_new_property,
    nit_wwww, nit_bad_vocab, nit_vocab_defined, nit_sarcasm, nit_fe, nit_missing_double_quote, nit_bad_media, nit_mb, nit_byte,
    nit_b64, nit_help, nit_configuration, nit_title, nit_webaddr, nit_copyright, nit_version, nit_info, nit_build, nit_config_version,
    nit_config_date, nit_config_nit, nit_config_shadow, nit_template_file, nit_code_dtd, nit_data_vocabulary, nit_json_error,
    nit_json_internal_error, nit_json_id, nit_vocab, nit_jsonld_context, nit_json_name, nit_json_invalid_node, nit_json_value_object,
    nit_json_out_of_place, nit_json_bad_term, nit_jsonld_type, nit_missing_ontology, nit_jsonld_format, nit_jsonld_mistype,
    nit_jsonld_encoding, nit_jsonld_map, nit_crap_spec, nit_bad_uid, nit_missing_property, nit_no_spell, nit_misspelt, nit_bad_list,
    nit_spell_lang, nit_spell_perhaps, nit_launch, nit_sent, nit_got, nit_bad_dict, nit_deprecated, nit_case, nit_icu_barf,
    nit_convert, nit_locale, nit_wtf, nit_normalise, nit_dictionary, nit_example, nit_local, nit_report, nit_unknown_option, nit_yea_nay,
    nit_mf_version, nit_not_directory, nit_endpoint, nit_header_empty, nit_header_malformed, nit_http_error, nit_header_no_data,
    nit_json_version, nit_json_corrupt, nit_json_domain, nit_dialect, nit_country, nit_languages, nit_hidden, nit_bespoke_obsolete,
    nit_regex, nit_fred_borked, nit_kew_borked, nit_internal_cache_error, nit_mtr_required, nit_mtd_required, nit_bad_intent,
    nit_cannot_scan, nit_thread, nit_icu_installation, nit_os_file, nit_found_css_id, nit_bad_classname, nit_css_syntax,
    nit_context, nit_nan, nit_a_expected, nit_block_expected, nit_elements_repeated, nit_bad_background,
    nit_css_url, nit_css_dubious, nit_bad_import, nit_spotted_id, nit_css_version, nit_bad_units, nit_charset,
    nit_reckless_rect, nit_unknown_operator, nit_unexpected, nit_css_attribute, nit_css_element, nit_selector, nit_pseud,
    nit_property, nit_rule, nit_statement, nit_weight, nit_naughty_content, nit_naughty_decoration, nit_bad_page,
    nit_naughty_page, nit_page_name_again, nit_css_unfinished, nit_missing_units, nit_no_such_page, nit_bespoke_property,
    nit_missing_value, nit_at_least, nit_at_most, nit_range, nit_precisely, nit_css_namespace, nit_css_bespoke,
    nit_not_not, nit_css_svg, nit_deprecated_media, nit_media_version, nit_media_ignored, nit_css_layer, nit_css_scope,
    nit_css_custom, nit_css_colour, nit_bad_number, nit_css_value, nit_css_keyframes, nit_css_value_fn, nit_css_value_param,
    nit_css_living_standard, nit_popover, nit_css_ease, nit_multiple_spaces, nit_repeated_value, nit_css_font, nit_unicode_my_arse,
    nit_css_font_feature, nit_css_palette, nit_descriptor, nit_not_here, nit_counter_style, nit_clacks, nit_bad_supports,
    nit_experimental, nit_cache, nit_arxiv, nit_coden, nit_prism, nit_mask, nit_mask_border, nit_profile, nit_container,
    nit_abandoned, nit_when_else, nit_part, nit_highlight, nit_sda, nit_vtn, nit_naughty_offset, nit_nesting, nit_content,
    nit_excluded, nit_ftp_protocol, nit_tld, nit_no_set, nit_bad_address,

    nit_incompatible,

    // eon
    nit_off } e_nit;

typedef enum
{   nm_none,
    nm_class_count, nm_class_decl_count, nm_class_decl_int, nm_class_int, nm_class_name, nm_class_title,
        nm_compile_time, nm_config,
        nm_context_article, nm_context_body, nm_context_build, nm_context_case, nm_context_cgi, nm_context_classic, nm_context_clear,
        nm_context_config, nm_context_copy, nm_context_corpus, nm_context_crosslinks, nm_context_css, nm_context_css_background,
        nm_context_css_adjust, nm_context_advanced_layout, nm_context_css_anchor, nm_context_css_anchor_pos, nm_context_css_box_align, nm_context_css_box_model, nm_context_css_box_sizing,
        nm_context_css_animation, nm_context_css_cascade, nm_context_css_colour, nm_context_css_compositing, nm_context_css_cond_rule,
        nm_context_css_contain, nm_context_css_content, nm_context_css_cs, nm_context_css_custom, nm_context_css_device, nm_context_css_display, nm_context_css_ease,
        nm_context_css_exclude, nm_context_css_extension, nm_context_css_fbl, nm_context_css_fill, nm_context_css_filter, nm_context_css_float, nm_context_css_font,
        nm_context_css_fragmentation, nm_context_css_grid, nm_context_css_highlight, nm_context_css_hyperlink, nm_context_css_image, nm_context_css_inline, nm_context_css_line_grid,
        nm_context_css_lists, nm_context_css_logic, nm_context_css_marquee, nm_context_css_masking, nm_context_css_media, nm_context_css_motion, nm_context_css_multi_column,
        nm_context_css_namespace, nm_context_css_nes, nm_context_css_nesting, nm_context_css_overflow, nm_context_css_overscroll, nm_context_css_page, nm_context_css_position,
        nm_context_css_present, nm_context_css_pseudo, nm_context_css_region, nm_context_css_rhythm, nm_context_css_round, nm_context_css_ruby, nm_context_css_scope,
        nm_context_css_scrollbar, nm_context_css_sda, nm_context_css_selector, nm_context_css_shadow, nm_context_css_shape, nm_context_css_snap, nm_context_css_snap_points,
        nm_context_css_speech, nm_context_css_spatial, nm_context_css_style, nm_context_css_syntax, nm_context_css_table, nm_context_css_transform,
        nm_context_css_transition, nm_context_css_text, nm_context_css_text_decoration, nm_context_css_ui, nm_context_css_value, nm_context_css_version,
        nm_context_css_view, nm_context_css_will_change, nm_context_css_writing_mode, nm_context_custom_elements, nm_context_dc, nm_context_example,
        nm_context_export_root, nm_context_exports, nm_context_extensions, nm_context_ext_css, nm_context_extra, nm_context_force_version,
        nm_context_foaf, nm_context_forward, nm_context_fred, nm_context_icu, nm_context_ie, nm_context_ignore, nm_context_index, nm_context_info, nm_context_iterate,
        nm_context_jsonld, nm_context_jsonld_extension, nm_context_jsonld_version, nm_context_lang, nm_context_links,
        nm_context_local, nm_context_math, nm_context_main, nm_context_max_file_size, nm_context_md_export,
        nm_context_mf_export, nm_context_mf_verify, nm_context_mf_version, nm_context_microdata, nm_context_msg, nm_context_no_ex_check,
        nm_context_once, nm_context_output, nm_context_persisted, nm_context_rdfa, nm_context_rdf_version, nm_context_rel, nm_context_report,
        nm_context_rfc_1867, nm_context_rfc_1942, nm_context_rfc_1980, nm_context_rfc_2070, nm_context_root, nm_context_safari,
        nm_context_server, nm_context_server_address_from, nm_context_server_address_to, nm_context_server_address, nm_context_server_port,
        nm_context_server_root,
        nm_context_schema, nm_context_ontology_version, nm_context_shadow_comment, nm_context_shadow_changed, nm_context_shadow_enable,
        nm_context_shadow_ignore, nm_context_shadow_persist, nm_context_shadow_root, nm_context_shadow_ssi, nm_context_shadow_space,
        nm_context_shadows, nm_context_site, nm_context_sloven, nm_context_spec, nm_context_spell, nm_context_spell_path, nm_context_spellings,
        nm_context_ssi, nm_context_stats_export, nm_context_stats_page, nm_context_stats_summary, nm_context_stats_abbr, nm_context_stats_annotation,
        nm_context_stats_attribute, nm_context_stats_category, nm_context_stats_character_variant, nm_context_stats_class,
        nm_context_stats_content_name, nm_context_stats_counter_style, nm_context_stats_css_property, nm_context_stats_custom_media,
        nm_context_stats_custom_property, nm_context_stats_dfn, nm_context_stats_dtdd, nm_context_stats_element, nm_context_stats_error,
        nm_context_stats_file, nm_context_stats_font, nm_context_stats_font_family, nm_context_stats_highlight, nm_context_stats_historical_form,
        nm_context_stats_id, nm_context_stats_itemid, nm_context_stats_keyframe, nm_context_stats_layer, nm_context_stats_meta,
        nm_context_stats_ontology, nm_context_stats_ornament, nm_context_stats_page_name, nm_context_stats_palette, nm_context_stats_reference,
        nm_context_stats_region, nm_context_stats_property, nm_context_stats_scroll_anim, nm_context_stats_statement, nm_context_stats_styleset,
        nm_context_stats_stylistic, nm_context_stats_swash, nm_context_stats_version, nm_context_stats_view,nm_context_svg_version, nm_context_tags,
        nm_context_test, nm_context_title, nm_context_unknown_class, nm_context_version, nm_context_virtuals, nm_context_xsd, nm_copy_addr,
        nm_copy_html, nm_copy_text,
    nm_general_info, nm_general_output, nm_general_path, nm_grand_title,
    nm_html_snippet,
    nm_id_count, nm_id_decl_count, nm_id_decl_int, nm_id_int, nm_id_name, nm_id_title,
    nm_itemid_line, nm_itemid_page, nm_itemid_name, nm_itemid_title,
    nm_level_name, nm_level_symbol,
    nm_note_content, nm_note_title, nm_note_note,
    nm_nit_after, nm_nit_before, nm_nit_code, nm_nit_doc, nm_nit_doc_long, nm_nit_explanation, nm_nit_id, nm_nit_line, nm_nit_mote, nm_nit_ns, nm_nit_ref,
        mn_nits_lost, mn_nits_format,
    nm_page_error, nm_page_name, nm_page_disk_path, nm_page_site_path, nm_prog_abbrev, nm_prog_build, nm_prog_fullname, nm_prog_version, nm_prog_webaddr,
    nm_query,
    nm_run_args, nm_run_catastrophe, nm_run_environment,
    nm_stat_count, nm_stat_detail, nm_stat_int, nm_stat_name, nm_stat_subname, nm_stat_subcount, nm_stat_subdetail, nm_stat_subint, nm_stats_subtitle,
        nm_stats_title, nm_stats_total,
    nm_tally_count, nm_tally_decl_count, nm_tally_decl_int, nm_tally_int, nm_tally_name, nm_tally_sum, nm_tally_title, nm_tally_total, nm_tally_use_count,
        nm_tally_use_int, nm_tally_use_sum, nm_tally_use_total,
        nm_time_duration, nm_time_finish, nm_time_start,
    nm_max } e_nit_macro;

typedef enum
{   ns_none,
    ns_class, ns_class_foot, ns_class_head, 
    ns_config, ns_config_foot, ns_config_head,
    ns_doc_foot, ns_doc_head,
    ns_du, ns_du_foot, ns_du_head, 
    ns_export, ns_export_foot, ns_export_head,
    ns_grand_foot, ns_grand_head,
    ns_nsid, ns_id_foot, ns_id_head,
    ns_itemid, ns_itemid_foot, ns_itemid_head,
    ns_init, ns_init_foot, ns_init_head,
    ns_link, ns_link_foot, ns_link_head,
    ns_note, ns_note_foot, ns_note_head,
    ns_nit, ns_nits_foot, ns_nits_head, ns_nits_page,
    ns_page_foot, ns_page_head,
    ns_shadow, ns_shadow_foot, ns_shadow_head,
    ns_stats_foot, ns_stats_head, ns_stat, ns_stats_subfoot, ns_stats_subhead, ns_substat,
    ns_tally, ns_tally_foot, ns_tally_head,
    ns_update, ns_update_foot, ns_update_head,
    ns_max } e_nit_section;

typedef enum { eno_none, eno_objects } e_none_objects;
typedef enum { nw_none, nw_wrap } e_none_wrap;
typedef enum { ens_normal, ens_spell_out } e_normal_spell;
typedef enum { ns_normal, ns_stretch } e_normal_stretch;
typedef enum { no_dsssl, no_w3c } e_notations;
typedef enum { nsd_none, nsd_space, nsd_dashed } e_nsd;
typedef enum { nuf_refurbished, nuf_new, nuf_used } e_nuf;

typedef enum {
    og_activity, og_actor, og_album, og_article, og_athlete, og_author,
    og_band, og_bar, og_blog, og_book,
    og_cafe, og_cause, og_company, og_city, og_country,
    og_director, og_drink,
    og_food,
    og_game, og_government,
    og_hotel,
    og_landmark,
    og_movie, og_musician,
    og_musicsong, og_musicalbum, og_musicplaylist, og_musicradiostation,
    og_product, og_non_profit,
    og_politician, og_profile, og_public_figure,
    og_restaurant,
    og_school, og_song, og_sport, og_sports_league, og_sports_team, og_state_province,
    og_tv_show,
    og_university,
    og_videomovie, og_videoepisode, og_videotvshow, og_videoother,
    og_website } e_ogtype;

typedef enum { ot_one, ot_two } e_onetwo;
typedef enum { ott_one, ott_two, ott_three } e_onetwothree;
typedef enum { oo_off, oo_on } e_onoff;
typedef enum { op_arithmetic, op_atop, op_in, op_out, op_over, op_xor } e_operator;
typedef enum { or_h, or_v } e_orientation;
typedef enum { eo_none, eo_top } e_overlay;
typedef enum { ou_over, ou_under } e_over_under;
typedef enum { po_270, po_180, po_90, po0, po90, po180, po270 } e_page_orientation;
typedef enum { pk_bad, pk_none, pk_child, pk_contextfill, pk_contextstroke, pk_currentcolour, pk_inherit, pk_icccolour, pk_url } e_paintkeyword;
typedef enum { po_normal, po_fill, po_stroke, po_markers } e_paint_order;
typedef enum {  pccv_box, pccv_byline, pccv_caption, pccv_credit, pccv_dateline, pccv_deck, pccv_footnotes, pccv_introduction, pccv_leadin, pccv_pullquote,
                pccv_recipe, pccv_sidebar, pccv_teaser, pccv_title } e_pam_ccv;
typedef enum { pam_a, pam_c, pam_d, pam_u } e_pam_status;
typedef enum { pcmm_draft, pcmm_beingnegotiated, pcmm_finalised, pcmm_uploaded, pcmm_upload_approved, pcmm_upload_rejected } e_pcmm_status;
typedef enum { ph_bubble, ph_capture, ph_default, ph_target } e_phase_x;
typedef enum { ps_b, ps_i, ps_p, ps_s, ps_sub, ps_sup, ps_tt, ps_u } e_plusstyle;
typedef enum {  pe_auto, pe_boundingbox, pe_bounding_box, pe_visiblepainted, pe_visiblefill, pe_visiblestroke, pe_visible, pe_painted, pe_fill,
                pe_stroke, pe_all, pe_none, pe_inherit } e_pointer_events;
typedef enum { pop_auto, pop_manual } e_popover;
typedef enum { pta_hide, pta_show, pta_toggle } e_popovertargetaction;
typedef enum { pr_auto, pr_metadata, pr_none } e_preload;
typedef enum { pic_bw, pic_colour, pic_duotone, pic_quadtone, pic_sepia, pic_tritone } e_pri_img_colour;
typedef enum { pio_horizontal, pio_vertical } e_pri_img_orientation;
typedef enum { pis_autumn, pis_spring, pis_summer, pis_winter } e_pri_img_season;
typedef enum { pis_indoor, pis_outdoor, pis_studio } e_pri_img_setting;
typedef enum {  pit_above, pit_aerial, pit_below, pit_center, pit_closeup, pit_detail, pit_distant, pit_front, pit_offcentre,
                pit_panoramic, pit_profile, pit_rear } e_pri_img_technique;
typedef enum {  piv_backlit, piv_candid, piv_cool, piv_doubleexposure, piv_flash, piv_hdr, piv_motionblur, piv_negative, piv_silhouette,
                piv_soft, piv_spotlit, piv_warm, piv_wideangle} e_pri_img_viewpoint;
typedef enum { pt_footnote, pt_reference, pt_section, pt_sidebar, pt_silent } e_print;
typedef enum { pap_ibc, pap_ifc, pap_main_body, pap_obc, pap_text } e_prism_ad_pos;
typedef enum { pat_dft, pat_eft, pat_text, pat_sfp, pat_spfplus } e_prism_ad_type;
typedef enum {  pag_blog, pag_book, pag_bookazine, pag_catalogue, pag_feed, pag_journal, pag_magazine, pag_manual, pag_newsletter,
                pag_newspaper, pag_other, pag_report, pag_pamphlet, pag_vook, pag_whitepaper } e_prism_ag_type;
typedef enum {  pas_agegroup, pas_agerange, pas_countryregion, pas_educationallevel, pas_employmentstatus, pas_gender, pas_incomerange, pas_maritalstatus,
                pas_culture, pas_other } e_prism_audience_sector;
typedef enum { pc_byline, pc_dateline, pc_deck, pc_footnotes, pc_leadin, pc_sidebar } e_prism_class;
typedef enum {  ptt_advertisement, ptt_article, ptt_blogentry, ptt_bookchapter, ptt_classifiedadsection, ptt_contentblock, ptt_frontcover, ptt_index,
                ptt_introduction, ptt_masthead, ptt_navigationalaid, ptt_othercover } e_prism_contenttype;
typedef enum {  prccv_box, prccv_byline, prccv_caption, prccv_credit, prccv_dateline, prccv_deck, prccv_footnotes, prccv_introduction, prccv_layer, prccv_leadin,
                prccv_pullquote, prccv_recipe, prccv_sidebar, prccv_subtitle, prccv_teaser, prccv_title } e_prism_ccv;

typedef enum {
    pcvp_article,
    pcvp_birdseye, pcvp_book, pcvp_body,
    pcvp_caption, pcvp_catalog, pcvp_clip, pcvp_close_up, pcvp_credit, pcvp_correction,
    pcvp_electronicbook,
    pcvp_graph,
    pcvp_homepage,
    pcvp_illustration, pcvp_index, pcvp_interactivecontent, pcvp_issue,
    pcvp_journal,
    pcvp_list,
    pcvp_magazine, pcvp_manual, pcvp_map,
    pcvp_news, pcvp_newspaper,
    pcvp_photo,
    pcvp_sidebar,
    pcvp_table,
    pcvp_webpage, pcvp_wormseye,
} e_prism_cvp;

typedef enum { pfcc_credit, pfcc_mediatitle } e_prism_fccv;

typedef enum {
    pg_abstract, pg_acknowledgement, pg_adaption, pg_advertorial, pg_analysis, pg_answers, pg_appendix, pg_authorbio, pg_autobiography,
    pg_backcover, pg_bibliography, pg_biography, pg_box,
    pg_calendar, pg_cartoon, pg_chapter, pg_chart, pg_chronolgy, pg_clarification, pg_classifiedad, pg_column, pg_correction, pg_coverstory, pg_coverpackagearticle,
    pg_dedication, pg_department, pg_diagram,
    pg_electionresults, pg_essay, pg_excerpt,
    pg_faq, pg_fashionshoot, pg_feature, pg_featurepackagearticle, pg_fiction, pg_financialstatement, pg_foreward,
    pg_glossary,
    pg_horoscope,
    pg_insidebackcover, pg_insidefrontcover, pg_interactivecontent, pg_interview,
    pg_jumppage,
    pg_legaldocument, pg_letters, pg_list,
    pg_map,
    pg_newsbulletin, pg_notice,
    pg_obituary, pg_opinion,
    pg_photoessay, pg_poem, pg_poll, pg_postscript, pg_preface, pg_pressrelease, pg_productdescription, pg_profile, pg_puzzle,
    pg_qanda, pg_quiz, pg_quotation,
    pg_ranking, pg_recipe, pg_references, pg_reprint, pg_resources, pg_response, pg_review,
    pg_schedule, pg_scrubber, pg_sectionlist, pg_sectiontableofcontents, pg_sidebar, pg_stockquote, pg_supplementarticle, pg_supplementbackcover, pg_supplementfrontcover,
    pg_tableofcontents, pg_transcript,
    pg_usercomments, pg_usergeneratedcontent, pg_userreview,
    pg_wirestory
} e_prism_genre;

typedef enum {  picv_academicfield, picv_event, picv_industry, picv_keyword, picv_link, picv_location, picv_object, picv_organisation, picv_person,
                picv_profession, picv_quote, picv_sport, picv_ticker, picv_timeframe } e_prism_icv;
typedef enum { pit_regular, pit_special } e_prism_issue_type;
typedef enum {  pasv_columnbyline, pasv_doublepagespread, pasv_freeformother, pasv_fullpage, pasv_onehalfpagehoriz, pasv_pasv_onehalfpagespread,
                pasv_pasv_onehalfpagevert, pasv_onethirdpagehoriz, pasv_onethirdpagesq, pasv_onethirdpagevert, pasv_twothirdpagehoriz, pasv_twothirdpagespread,
                pasv_twothirdpagevert } e_prism_pasv;
typedef enum { pcv_broadcast, pcv_email, pcv_ereader, pcv_mobile, pcv_other, pcv_print, pcv_recordablemedia, pcv_smartphone, pcv_tablet, pcv_web } e_prism_pcv;
typedef enum {  pfv_annually, pfv_bimonthly, pfv_biweekly, pfv_daily, pfv_continually, pfv_irregularly, pfv_monthly, pfv_other, pfv_quarterly,
                pfv_semiannually, pfv_weekly } e_prism_pfv;
typedef enum {  ptv_animation, ptv_audio, ptv_cartoon, ptv_chart, ptv_clip, ptv_codeblock, ptv_complexblock, ptv_diagram, ptv_gallery, ptv_illustration,
                ptv_infographic, ptv_logo, ptv_map, ptv_other, ptv_photo, ptv_photoillustration, ptv_photomontage, ptv_slideshow, ptv_spreadsheet,
                ptv_table, ptv_video } e_prism_ptv;

typedef enum { 
    prcv_abstract, prcv_acknowledgement, prcv_advertisement, prcv_analysis, prcv_authorbio, prcv_autobiography,
    prcv_bibliography, prcv_biography, prcv_brief,
    prcv_cartoon, prcv_chronology, prcv_classifiedad, prcv_column, prcv_cover,
    prcv_dateline,
    prcv_electionresults, prcv_eventscalendar, prcv_excerpt,
    prcv_feature, prcv_financialstatement,
    prcv_interview,
    prcv_legaldocument, prcv_letter, prcv_lettertoeditor, prcv_logo,
    prcv_newsbulletin, prcv_notice,
    prcv_obituary, prcv_opinion,
    prcv_photoessay, prcv_poll, prcv_portrait, prcv_pressrelease, prcv_productdescription, prcv_profile,
    prcv_quotation,
    prcv_ranking, prcv_recipe, prcv_review,
    prcv_schedule, prcv_stockquote,
    prcv_tableofcontents, prcv_transcript,
} e_prism_rcv;

typedef enum {
    role_amateur, role_animator, role_artist, role_author,
    role_cartographer, role_chef, role_choreographer, role_cinematographer, role_commentator, role_composer, role_correspondant, role_costumedesigner,
    role_director, role_draftsman,
    role_editor,
    role_fashioncoordinator, role_fashiondesigner, role_foodstylist, role_foodtester,
    role_graphicdesigner,
    role_hairstylist, role_host,
    role_illustrator, role_interviewee, role_interviewer, role_interpreter,
    role_layoutdesigner,
    role_makeupartist, role_musician,
    role_narrator, role_nutritionist,
    role_other, role_panelist, role_performer, role_photographer, role_producer, role_programmer,
    role_recipedeveloper, role_reporter, role_researcher, role_researchassistant,
    role_speaker,
    role_translator, role_tvhost,
    role_writer
 } e_prism_role;

typedef enum { pta_dfp, pta_efp, pta_sfp, pta_sfpplus } e_prism_tablet_ad;
typedef enum { pr_stop, pr_continue } e_propagate;
typedef int e_property;

typedef enum {
    pr_other,
    pr_aaa, pr_aaas, pr_about, pr_acap, pr_acct, pr_acr, pr_adiumxtra, pr_admin, pr_afp, pr_afs, pr_aim, pr_apt, pr_app, pr_attachment, pr_aw, pr_amss,
    pr_barian, pr_beshare, pr_bitcoin, pr_blob, pr_bolo,
    pr_callto, pr_cap, pr_chrome, pr_chrome_extension, pr_cid, pr_clsid, pr_coap, pr_coaps, pr_com_eventbrite_attendee, pr_content, pr_crid, pr_cvs,
    pr_dab, pr_data, pr_dav, pr_dict, pr_did, pr_dina_playsingle, pr_dina_playcontainer, pr_dns, pr_dntp, pr_doi, pr_drm, pr_dtn, pr_dvb,
    pr_ed2k, pr_example,
    pr_facetime, pr_fax, pr_feed, pr_file, pr_filesystem, pr_finger, pr_fish, pr_fm, pr_ftp, pr_ftps,
    pr_gemini, pr_geo, pr_gg, pr_git, pr_gizmoproject, pr_go, pr_gopher, pr_gtalk,
    pr_h323, pr_hcp, pr_http, pr_https,
    pr_iax, pr_icap, pr_icon, pr_im, pr_imap, pr_info, pr_iotdisco, pr_ipn, pr_ipp, pr_ipps, pr_irc, pr_irc6, pr_ircs, pr_iris, pr_iris_beep, pr_iris_xpc,
        pr_iris_xpcs, pr_iris_lws, pr_itms,
    pr_jabber, pr_jar, pr_javascript, pr_jdbc, pr_jms,
    pr_keyparc,
    pr_lastfm, pr_ldap, pr_ldaps,
    pr_magnet, pr_mailserver, pr_mailto, pr_maps, pr_market, pr_message, pr_mid, pr_mms, pr_modem, pr_ms_help, pr_ms_settings, pr_ms_settings_airplanemode,
        pr_ms_settings_bluetooth, pr_ms_settings_camera, pr_ms_settings_cellular, pr_ms_settings_cloudstorage, pr_ms_settings_emailandaccounts,
        pr_ms_settings_language, pr_ms_settings_location, pr_ms_settings_lock, pr_ms_settings_nfctransactions, pr_ms_settings_notifications, pr_ms_settings_power,
        pr_ms_settings_privacy, pr_ms_settings_proximity, pr_ms_settings_screenrotation, pr_ms_settings_wifi, pr_ms_settings_workplace, pr_msnum, pr_msrp, pr_msrps,
        pr_mtqp, pr_mumble, pr_mupdate, pr_mvn,
    pr_news, pr_nfs, pr_ni, pr_nih, pr_nntp, pr_notes,
    pr_ocsp, pr_odbc, pr_oid, pr_opaquelocktoken, pr_openpgp4fpr,
    pr_pack, pr_palm, pr_paparazzi, pr_payto, pr_pkcs11, pr_platform, pr_pop, pr_pres, pr_prospero, pr_proxy, pr_psyc,
    pr_query,
    pr_redis, pr_rediss, pr_reload, pr_res, pr_resource, pr_rmi, pr_rsync, pr_rtmfp, pr_rtmp, pr_rtsp,
    pr_s3, pr_secondlife, pr_service, pr_session, pr_sftp, pr_sgn, pr_shttp, pr_sieve, pr_sip, pr_sips, pr_skype, pr_slack, pr_smb, pr_sms, pr_snews, pr_snmp,
        pr_soap_beep, pr_soap_beeps, pr_soldat, pr_spotify, pr_ssh, pr_steam, pr_stratum, pr_stun, pr_stuns, pr_snv,
    pr_tag, pr_teamspeak, pr_tel, pr_telnet, pr_tftp, pr_things, pr_thismessage, pr_tn3270, pr_tip, pr_trueconf, pr_turn, pr_turns, pr_tv,
    pr_udp, pr_uid, pr_unreal, pr_urn, pr_ut2004, pr_vemmi, pr_ventrilo, pr_videotex, pr_view_source, pr_vnc,
    pr_wais, pr_webcal, pr_webplus, pr_ws, pr_wss, pr_wtai, pr_wyciwyg, pr_xcon, pr_xcon_userid, pr_xfire, pr_xmlrpc_beep, pr_xmlrpc_beeps, pr_xmpp, pr_xri,
    pr_ymsgr,
    pr_z39_50, pr_z39_50r, pr_z39_50s, pr_zoommtg, pr_zoomus,
    pr_error } e_protocol;

typedef enum { prsa_aggregate, prsa_presentdisplay, prsa_presentplay, prsa_presentprint, prsa_presenttexttospeech, prsa_transform, prsa_translate, prsa_use } e_prs_action;
typedef enum { prsd_compensate, prsd_credit, prsd_include, prsd_inform } e_prs_duty;
typedef enum { qs_none, qs_c, qs_csv, qs_double, qs_html, qs_single } e_quote_style;
typedef enum { rp_collection, rp_literal, rp_resource } e_rdf_parsetype;
typedef enum { rdf_none, rdf_a, rdf_deprecated, rdf_1_0, rdf_1_1 } e_rdf_version;
typedef enum {  erc_cooktime, erc_duration, erc_ingredient, erc_ingredientintro, erc_ingredients, erc_instructions, erc_instructionsintro, erc_itemname,
                erc_ingredienthead, erc_nutrition, erc_nutrient, erc_nutrientname, erc_nutritionintro, erc_othertime, erc_preptime, erc_quantity,
                erc_recipedescription, erc_recipenote, erc_recipetitle, erc_servingsize, erc_step, erc_stephead, erc_stepnote, erc_totaltime, erc_unit, erc_yield } e_recipe_content;
typedef enum { rco_appetiser, rco_desert, rco_drink, rco_main, rco_salad, rco_sidedish } e_recipe_course;

typedef enum {
    cui_african, cui_american, cui_asian, cui_austrian,
    cui_brazilian, cui_archipelagan,
    cui_cajunorcreole, cui_california, cui_caribbean, cui_centralorsouthamerican, cui_chinese, cui_cuban,
    cui_easterneuropean,
    cui_french,
    cui_german, cui_greek,
    cui_hungarian, cui_halal,
    cui_indian, cui_italian,
    cui_japanese, cui_jewishorkosher,
    cui_korean,
    cui_lebanese,
    cui_mediterranean, cui_mexican, cui_middleeastern, cui_moroccan,
    cui_nativeamerican, cui_newengland,
    cui_pacificnorthwest, cui_pacificrim, cui_peruvian, cui_polish,
    cui_scandinavian, cui_southern, cui_southwest, cui_spanish, cui_swiss,
    cui_thai,
    cui_vegan, cui_vegetarian, cui_vietnamese
} e_recipe_cuisine;

typedef enum {  dnv_brainboosting, dnv_bonebuilding, dnv_diabetic, dnv_glutenfree, dnv_healthy, dnv_hearthealthy, dnv_highfiber, dnv_lactoseintolerant,
                dnv_lowcalorie, dnv_lowcarbohydrate, dnv_lowcholesterol, dnv_lowfat, dnv_lowsaturatedfat, dnv_lowsodium, dnv_sugarfree, dnv_vegan,
                dnv_vegetarian, dnv_weightloss } e_recipe_dietary;

typedef enum {
    dtv_appetiser,
    dtv_babyfood, dtv_beanpealegume, dtv_beveragealcoholic, dtv_beveragenonalcoholic, dtv_bread,
    dtv_cakeorcupcakes, dtv_candy, dtv_casserole, dtv_cheese, dtv_cookie,
    dtv_dairy, dtv_diporspread,
    dtv_egg,
    dtv_fishshellfish, dtv_foodgift, dtv_frosting, dtv_fruit,
    dtv_gravy, dtv_grill,
    dtv_icecreamorsherbet,
    dtv_jellyjampreserves,
    dtv_marinadeorrub, dtv_meatorgame, dtv_muffinquickbread,
    dtv_nuts,
    dtv_pasta, dtv_pizza, dtv_picklesorrelishes, dtv_piestartspastries, dtv_poultry, dtv_puddingsorcustards,
    dtv_saladorsaladdressing, dtv_sandwich,
    dtv_sauceorcondiment, dtv_seafood, dtv_smoothie, dtv_spiceherbsseasonings, dtv_souporstew, dtv_stirfry, dtv_stuffingordressing,
    dtv_vegetable
} e_recipe_dish;

typedef enum {  rex_alcohol, rex_dairy, rex_eggs, rex_fish, rex_meat, rex_nutsorpeanuts, rex_pork, rex_salt, rex_shellfish, rex_soy,
                rex_sugar, rex_wheatorgluten } e_recipe_exclusion;
typedef enum {  erk_barbecuegrill, erk_blender, erk_breadmachine, erk_broiler, erk_convectionoven, erk_deepfryer, erk_fonduepot, erk_foodprocessor,
                erk_freezer, erk_fryingpan, erk_griddle, erk_grillpan, erk_icecreammaker, erk_microwaveoven, erk_oven, erk_pressurecooker, erk_ricecooker,
                erk_sandwichorpaninipress, erk_slowcooker, erk_wafflemaker, erk_wok } e_recipe_kit;
typedef enum { erm_breakfast, erm_brunch, erm_buffet, erm_dinner, erm_hdo, erm_lunch, erm_supper, erm_snack } e_recipe_meal;
typedef enum {  erm_bake, erm_blend, erm_boil, erm_braise, erm_broil, erm_can, erm_deepfry, erm_fondue, erm_freeze, erm_fry, erm_grillorbarbecue, erm_marinate,
                erm_microwave, erm_nocook, erm_press, erm_roast, erm_saute, erm_slowcook, erm_steam, erm_stirfry } e_recipe_method;
typedef enum {  erso_amateur, erso_book, erso_celeb, erso_chef, erso_client, erso_contest, erso_magazine, erso_onlinewebsite, erso_readersubmitted,
                erso_restaurant, erso_sponsors, erso_testkitchen, erso_tvshow } e_recipe_source;
typedef enum { ersk_children, ersk_easy, ersk_expert, ersk_moderate } e_recipe_skill;

typedef enum {
    ersp_anniversary,
    ersp_babyshower, ersp_barbeque, ersp_barbasmitzvah, ersp_birthdayadult, ersp_birthdaychild, ersp_bridalshower,
    ersp_chinesenewyear, ersp_christmasday, ersp_christmaseve, ersp_cincodemayo, ersp_cocktailparty, ersp_cookieswap,
    ersp_dinnerparty,
    ersp_easter,
    ersp_fathersday, ersp_fondueparty, ersp_fourthofjuly, ersp_funeralorwake,
    ersp_graduation,
    ersp_halloween, ersp_hanukkah,
    ersp_kwanzaa,
    ersp_labourday,
    ersp_mardigras, ersp_memorialday,
    ersp_newyearsday, ersp_newyearseve,
    ersp_oscars,
    ersp_passover, ersp_picnicorcookout, ersp_potluck,
    ersp_ramadan, ersp_roshhashanah,
    ersp_stpatricksday, ersp_superbowl,
    ersp_tailgating, ersp_thanksgiving,
    ersp_valentinesday,
    ersp_yomkippur,
    ersp_wedding, ersp_winterholidayparty
} e_recipe_special;

typedef enum {  ert_bake, ert_broil, ert_chill, ert_cool, ert_decorate, ert_grill, ert_freeze, ert_handson, ert_marinate, ert_microwave,
                ert_process, ert_rise, ert_roast, ert_slowcook, ert_stand, ert_starttofinish } e_recipe_time;
typedef enum { rr_rect, rr_round } e_rect_round;
typedef enum { rf_no, rf_downgrade, rf_same, rf_origin, rf_strict, rf_strictcross, rf_cross, rf_unsafe } e_referrer;

typedef enum {
    r_context,

    // microformats v1 only
    r_entry_category = (int) c_error + 1,

    // both v1 and v2
    r_acquaintance, r_alternative, r_appendix, r_author, r_bookmark, r_chapter, r_child, r_colleague, r_contact,
    r_contents, r_copyright, r_coresident, r_coworker, r_crush, r_date, r_directory, r_enclosure, r_first, r_friend,
    r_glossary, r_help, r_home, r_index, r_in_reply_to, r_its_rules, r_kin, r_last, r_licence, r_me, r_met, r_muse,
    r_parent, r_payment, r_prev, r_pronunciation, r_section, r_sibling, r_sidebar, r_spouse, r_start, r_stylesheet,
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
    r_respond_proxy, r_respond_redirect, r_restconf, r_root, r_ontology_dc, r_ontology_dcterms, r_search, r_self, r_service,
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

    // curie
    r_curie,

    // additional xhv
    r_role,

    r_illegal } e_rel;

typedef enum { ri_auto, ri_perceptual, ri_relativecolourimetric, ri_saturation, ri_absolutecolourimetric } e_rendering_in_tents;
typedef enum { re_always, re_whennotactive, re_never } e_restart;
typedef enum { ru_rotate_left, ru_rotate_right, ru_upright } e_rotate_upright;
typedef enum { trc_column, trc_row } e_row_column;
typedef enum { rs_yes, rs_no, rs_maybe, rs_interested } e_rsvp;
typedef enum { ru_none, ru_groups, ru_rows, ru_cols, ru_all } e_rules;
typedef enum { su_safe, su_unsafe } e_safe_unsafe;
typedef enum {  sand_unknown, sand_adwua, sand_asabua, sand_atnbua, sand_atntcp, sand_ad, sand_forms, sand_modals, sand_orientation, sand_pointer,
                sand_popups, sand_popupescape, sand_presentation, sand_origin, sand_scripts, sand_navigation } e_sandbox;
typedef enum { sc_interlace, sc_progressive } e_scan;
typedef enum { scei_after, scei_before, scei_centre, scei_end, scei_start, scei_inherit } e_scei;

// mostly RDFa common context
// (good grief : https://lov.linkeddata.es/dataset/lov/vocabs )

#define ONTOLOGIES \
    s_none, \
    s_adms, s_article, s_as, \
    s_bfo, s_bibo, s_biro, s_book, \
    s_cc, s_cito, s_content, s_crs2, s_csvw, s_ctag, \
    s_daq, s_dbd, s_dbo, s_dbp, s_dbp_owl, s_dbr, s_dc, s_dcam, s_dcat, s_dcmi, s_dct, s_ddi, s_doap, s_dqv, s_describedby, s_duv, \
    s_earl, s_event, s_exif, s_exifex, \
    s_fabio, s_faux, s_foaf, s_frbr, \
    s_gr, s_grddl, s_gs1, \
    s_ical, s_icaltzd, \
    s_jsonld, \
    s_ldp, s_licence, s_locn, \
    s_ma, s_microformats, s_music, \
    s_oa, s_odrl, s_og, s_org, s_owl, \
    s_pam, s_pamp, s_pcm, s_pcmm, s_pcv, s_pdf, s_photoshop, s_pim, s_pmi, s_poetry, s_prism, s_prism_ad, s_prl, s_prm, s_profile, s_prov, s_prs, s_psv, s_ptr, s_pur, \
    s_qb, \
    s_rdf, s_rdfa, s_rdfg, s_rdfs, s_rev, s_rif, s_role, s_rr, \
    s_schema, s_sd, s_sioc, s_sioc_s, s_sioc_t, s_skos, s_skosxl, s_stdim, s_stevt, s_stfnt, s_stjob, s_stref, s_stver, s_sosa, s_ssn, \
    s_taxo, s_tiff, s_time, \
    s_v, s_vann, s_vcard, s_video, s_void, \
    s_wdr, s_wdrs, s_website, s_whatwg, \
    s_xhv, s_xml, s_xmp, s_xmpbj, s_xmpdm, s_xmpg, s_xmpgimg, s_xmpidq, s_xmpmm, s_xmprights, s_xmptpg, s_xsd, \
    s_error

typedef enum { ONTOLOGIES } e_ontology;
CONSTEXPR ::std::size_t ontology_size = s_error;
typedef ::std::size_t ontology_id;

typedef enum
{   ont_context,

    anything,

    // automated dog management service
    adms_asset, adms_asset_distribution, adms_asset_repository, adms_identifier,

    // activity streams etc.
    asc_accept, asc_activity, asc_add, asc_announce, asc_application, asc_arrive, asc_article, asc_audio,
    asc_block,
    asc_collection, asc_collectionpage, asc_create,
    asc_delete, asc_dislike, asc_document,
    asc_event,
    asc_flag, asc_follow,
    asc_group,
    asc_ignore, asc_image, asc_intransitiveactivity, asc_invite, asc_iscontact, asc_isfollowedby, asc_isfollowing, asc_ismember,
    asc_join,
    asc_leave, asc_like, asc_link, asc_listen,
    asc_medialink, asc_mention, asc_move,
    asc_note,
    asc_object, asc_offer, asc_orderedcollection, asc_orderedcollectionpage, asc_organisation,
    asc_page, asc_person, asc_place, asc_profile,
    asc_question,
    asc_read, asc_reject, asc_relationship, asc_remove,
    asc_service,
    asc_tentativeaccept, asc_tentativereject, asc_tombstone, asc_travel,
    asc_undo, asc_update,
    asc_video, asc_view,

    // basic format ontology
    bfo_continuant, bfo_continuant_fiat_boundary,
    bfo_dependent_continuant, bfo_disposition,
    bfo_entity,
    bfo_fiat_line, bfo_fiat_object_part, bfo_fiat_point, bfo_fiat_surface, bfo_function,
    bfo_generically_dependent_continuant,
    bfo_history,
    bfo_immaterial_entity, bfo_independent_continuant,
    bfo_material_entity,
    bfo_object, bfo_object_aggregate, bfo_object_boundary, bfo_occurrent, bfo_one_dimensional_continuant_fiat_boundary, bfo_one_dimensional_region,
        bfo_one_dimensional_temporal_region,
    bfo_process, bfo_process_boundary, bfo_process_profile,
    bfo_quality,
    bfo_realisable_entity, bfo_relational_quality, bfo_role,
    bfo_site, bfo_spatial_region, bfo_spatiotemporal_region, bfo_specifically_dependent_continuant,
    bfo_temporal_instant, bfo_temporal_interval, bfo_temporal_region, bfo_three_dimensional_continuant_fiat_boundary, bfo_three_dimensional_region,
        bfo_two_dimensional_continuant_fiat_boundary, bfo_two_dimensional_region,
    bfo_zero_dimensional_continuant_fiat_boundary, bfo_zero_dimensional_region, bfo_zero_dimensional_temporal_region,

    // bibo
    bibo_academicarticle, bibo_article, bibo_audiodocument, bibo_audiovisualdocument,
    bibo_bdarcus, bibo_bill, bibo_book, bibo_booksection, bibo_brief,
    bibo_chapter, bibo_code, bibo_collecteddocument, bibo_collection, bibo_conference, bibo_courtreporter,
    bibo_degrees_ma, bibo_degrees_ms, bibo_degrees_phd, bibo_document, bibo_documentpart, bibo_documentstatus, bibo_editedbook,
    bibo_email, bibo_event, bibo_excerpt,
    bibo_fgiasson, bibo_film,
    bibo_hearing,
    bibo_image, bibo_interview, bibo_issue,
    bibo_journal,
    bibo_legalcasedocument, bibo_legaldecision, bibo_legaldocument, bibo_legislation, bibo_letter,
    bibo_magazine, bibo_manual, bibo_manuscript, bibo_map, bibo_multivolumebook,
    bibo_newspaper, bibo_note,
    bibo_patent, bibo_performance, bibo_periodical, bibo_personalcommunication, bibo_personalcommunicationdocument, bibo_proceedings,
    bibo_quote,
    bibo_referencesource, bibo_report,
    bibo_series, bibo_slide, bibo_slideshow, bibo_standard, bibo_status_accepted, bibo_status_draft, bibo_status_forthcoming, bibo_status_nonpeerreviewed, bibo_status_peerreviewed,
        bibo_status_published, bibo_status_rejected, bibo_status_unpublished, bibo_statute,
    bibo_thesis, bibo_thesisdegree,
    bibo_webpage, bibo_website, bibo_workshop,

    // biro
    biro_bibliographic_collection, biro_bibliographic_list, biro_bibliographic_record, biro_bibliographic_reference,
    biro_library_catalogue, biro_reference_list,

    // cito
    cito_affilation_self_citation, cito_author_network_self_citation, cito_author_self_citation, cito_citation,
    cito_distant_citation, cito_funder_self_citation, cito_journal_cartel_citation, cito_journal_self_citation,
    cito_self_citation,

    // common tag
    ctag_author, ctag_auto, ctag_reader, ctag_tag,

    // contrary sausages vote wibble
    csv_cell, csv_column,
    csv_datatype, csv_dialect, csv_direction,
    csv_foreignkey,
    csv_numericformat,
    csv_row,
    csv_schema,
    csv_table, csv_tablegroup, csv_tablereference, csv_transformation,
    csv_uritemplate,

    // data quality
    daq_metric, daq_category, daq_dimension, daq_qualitygraph, daq_observation,

    // dublin core vocabulary description
    dcam_vocabularyencodingscheme,

    // data catalogue
    dca_catalogue, dca_cataloguerecord,
    dca_dataservice, dca_dataset, dca_distribution,
    dca_relationship, dca_resource, dca_role,

    // dcmi type vocabulary
    dcmi_collection, dcmi_dataset, dcmi_event, dcmi_image, dcmi_interactiveresource, dcmi_movingimage, dcmi_physicalobject, dcmi_service, dcmi_software, dcmi_sound,
        dcmi_stillimage, dcmi_text,

    // dublin core terms
    dct_agent, dct_agentclass, dct_bibliographicresource, dct_fileformat, dct_frequency, dct_jurisdiction, dct_licencedocument, dct_linguisticsystem, dct_location,
        dct_locationperiodorjurisdiction, dct_mediatype, dct_mediatypeorextent, dct_methodofaccrual, dct_methodofinstruction, dct_periodoftime, dct_physicalmedium,
        dct_physicalresource, dct_policy, dct_provenancestatement, dct_rightsstatement, dct_sizeorduration, dct_standard, dct_thing,

    // disco
    ddi_analysis_unit,
    ddi_category_statistics,
    ddi_data_file, ddi_descriptive_statistics,
    ddi_instrument,
    ddi_logical_dataset,
    ddi_question, ddi_questionnaire,
    ddi_representation, ddi_representative_variable, ddi_response_domain,
    ddi_study, ddi_study_group, ddi_summary_statistics,
    ddi_thing,
    ddi_universe,
    ddi_variable,
 
    // doap
    doap_archrepository,
    doap_bazaarbranch, doap_bkrepository,
    doap_cvsrepository,
    doap_darcsrepository,
    doap_gitbranch, doap_gitrepository,
    doap_hgrepository,
    doap_project,
    doap_repository,
    doap_specification, doap_svnrepository,
    doap_version,

    // data quality
    dqv_category,
    dqv_dimension,
    dqv_metric,
    dqv_qualityannotation, dqv_qualitycertificate, dqv_qualitymetadata, dqv_qualitymeasurement, dqv_qualitymeasurementdataset, dqv_qualitypolicy,
    dqv_userqualityfeedback,

    // duv
    duv_ratingfeedback, duv_usage, duv_usagetool, duv_userfeedback,

     // earl
    earl_assertion, earl_assertor, earl_automatic,
    earl_cannottell, earl_canttell,
    earl_fail, earl_failed,
    earl_inapplicable,
    earl_manual,
    earl_notapplicable, earl_nottested,
    earl_outcomevalue,
    earl_pass, earl_passed,
    earl_semiauto, earl_software,
    earl_testcase, earl_testcriterion, earl_testmode, earl_testrequirement, earl_testresult, earl_testsubject,
    earl_undisclosed, earl_unknownmode, earl_untested,

    // event
    event_event, event_factor, event_product,

    // exifex
    exifex_exifan,

    // fabio
    fb_thing,
    fb_abstract, fb_academic_proceedings, fb_addendum, fb_algorithm, fb_analogue_item, fb_analog_magnetic_tape, fb_analogue_manifestation, fb_analogue_storage_medium, fb_announcement,
        fb_anthology, fb_api, fb_application_profile, fb_archival_document, fb_archival_document_set, fb_archival_record, fb_archival_record_set,
        fb_article, fb_asm_file, fb_artistic_work, fb_audio_document, fb_authority_file,
    fb_bachelors_thesis, fb_bibliographic_database, fb_bibliographic_metadata, fb_biography, fb_blog, fb_blog_post, fb_book, fb_book_chapter,
        fb_book_review, fb_book_series, fb_book_set, fb_brief_report,
    fb_call_for_applications, fb_case_for_support, fb_case_for_support_document, fb_case_report, fb_catalogue, fb_cd, fb_chapter, fb_citation_metadata,
        fb_clinical_case_report, fb_clinical_guideline, fb_clinical_trial_design, fb_clinical_trial_report, fb_cloud, fb_collected_works, fb_comment,
        fb_complete_works, fb_computer_application, fb_computer_file, fb_computer_program, fb_concept, fb_concept_scheme, fb_conference_paper,
        fb_conference_poster, fb_conference_proceedings, fb_controlled_vocabulary, fb_correction, fb_corrigendum, fb_cover, fb_critical_edition,
    fb_data_file, fb_data_management_plan, fb_data_management_policy, fb_data_management_policy_document, fb_data_repository, fb_database,
        fb_database_management_system, fb_dataset, fb_definitive_version, fb_deliverable, fb_deliverable_report, fb_demo_paper, fb_diary,
        fb_digital_item, fb_digital_magnetic_tape, fb_digital_manifestation, fb_digital_storage_medium, fb_directory, fb_discipline_dictionary, fb_doctoral_thesis,
        fb_document_repository, fb_dust_jacket, fb_dvd,
    fb_editorial, fb_email, fb_entity_metadata, fb_entry, fb_erratum, fb_essay, fb_examination_paper, fb_excerpt, fb_executive_summary,
        fb_experimental_protocol, fb_expression, fb_expression_collection,
    fb_figure, fb_film, fb_floppy_disk, fb_folksonomy,
    fb_gantt_chart, fb_grant_application, fb_grant_application_document,
    fb_hardback, fb_hd,
    fb_image, fb_in_brief, fb_in_use_paper, fb_index, fb_instruction_manual, fb_instructional_work, fb_internet, fb_intranet, fb_item, fb_item_collection,
    fb_journal, fb_journal_article, fb_journal_editorial, fb_journal_issue, fb_journal_news_item, fb_journal_volume,
    fb_laboratory_notebook, fb_lecture_notes, fb_legal_opinion, fb_letter, fb_library_catalogue, fb_literary_artistic_work,
    fb_magazine, fb_magazine_article, fb_magazine_editorial, fb_magazine_issue, fb_magazine_news_item, fb_manifestation, fb_manifestation_collection,
        fb_manuscript, fb_masters_thesis, fb_meeting_report, fb_metadata, fb_metadata_document, fb_methods_paper, fb_microblog, fb_micropost,
        fb_minimal_information_standard, fb_model, fb_movie, fb_moving_image, fb_musical_composition,
    fb_nanopublication, fb_news_item, fb_news_report, fb_newspaper, fb_newspaper_article, fb_newspaper_editorial, fb_newspaper_issue,
        fb_newspaper_news_item, fb_notebook, fb_notification_of_receipt, fb_novel,
    fb_obituary, fb_ontology, fb_ontology_document, fb_opinion, fb_oration,
    fb_page, fb_paper, fb_paperback, fb_patent, fb_patent_application, fb_patent_application_document, fb_patent_document, fb_periodical, fb_periodical_issue,
        fb_periodical_item, fb_periodical_volume, fb_personal_communication, fb_phd_symposium_paper, fb_play, fb_poem, fb_policy, fb_policy_document,
        fb_position_paper, fb_poster_paper, fb_postprint, fb_preprint, fb_presentation, fb_press_release, fb_print_object, fb_proceedings_paper,
        fb_product_review, fb_project_metadata, fb_project_plan, fb_proof, fb_proposition,
    fb_questionnaire, fb_quotation,
    fb_ram, fb_rapid_communication, fb_reference_book, fb_reference_entry, fb_reference_work, fb_relational_database, fb_reply, fb_report, fb_report_document,
        fb_reporting_standard, fb_repository, fb_research_paper, fb_resource_paper, fb_retraction, fb_review, fb_review_article, fb_review_paper,
    fb_scholarly_work, fb_screenplay, fb_script, fb_series, fb_short_story, fb_solid_state_memory, fb_song, fb_sound_recording, fb_specification, fb_specification_document,
        fb_spreadsheet, fb_standard_operating_procedure, fb_still_image, fb_storage_medium, fb_structured_summary, fb_subject_discipline, fb_subject_term,
        fb_supplement, fb_supplementary_information_file, fb_systematic_review,
    fb_table, fb_table_of_contents, fb_taxonomy, fb_technical_report, fb_technical_standard, fb_term_dictionary, fb_textbook, fb_thesaurus, fb_thesis,
        fb_timetable, fb_trial_report, fb_triplestore, fb_tweet,
    fb_uncontrolled_vocabulary,
    fb_vinyl_disk, fb_vocabulary, fb_vocabulary_document, fb_vocabulary_mapping, fb_vocabulary_mapping_document,
    fb_web_archive, fb_web_content, fb_web_manifestation, fb_web_page, fb_web_site, fb_white_paper, fb_wiki, fb_wiki_entry, fb_wikipedia_entry,
        fb_work, fb_work_collection, fb_work_package, fb_workflow, fb_working_paper, fb_workshop_paper, fb_workshop_proceedings, fb_www,

    // foaf
    foaf_agent, foaf_document, foaf_group, foaf_image, foaf_labelproperty, foaf_onlineaccount, foaf_onlinechataccount, foaf_onlineecommerceaccount,
        foaf_onlinegamingaccount, foaf_organisation, foaf_person, foaf_personalprofiledocument, foaf_project,

    // frbr
    fs_concept, fs_corporatebody, fs_endeavour, fs_event, fs_expression, fs_item, fs_manifestation, fs_object, fs_person, fs_place,
        fs_responsibleentity, fs_subject, fs_work,

    // good relations
    gr_actualproductorserviceinstance, gr_americanexpress,
    gr_brand, gr_buy, gr_business, gr_businessentity, gr_businessentitytype, gr_businessfunction, gr_bybanktransferinadvance, gr_byinvoice,
    gr_cash, gr_checkinadvance, gr_cod, gr_constructioninstallation,
    gr_dayofweek, gr_deliverychargespecification, gr_deliverymethod, gr_deliverymodedirectdownload, gr_deliverymodefreight, gr_deliverymodemail, gr_deliverymodeownfleet,
        gr_deliverymodeparcelservice, gr_deliverymodepickup, gr_dhl, gr_dinersclub, gr_directdebit, gr_discover, gr_dispose,
    gr_enduser,
    gr_federalexpress, gr_friday,
    gr_googlecheckout,
    gr_individual,
    gr_jcb,
    gr_labour_bringin, gr_leaseout, gr_licence, gr_location, gr_locationofsalesorserviceprovisioning,
    gr_maintain, gr_mastercard, gr_monday,
    gr_n_ary_relations,
    gr_offering, gr_openinghoursspecification,
    gr_partsandlabour_bringin, gr_partsandlabour_pickup, gr_paymentchargespecification, gr_paymentmethod, gr_paymentmethodcreditcard, gr_paypal, gr_payswarm,
        gr_pricespecification, gr_productorservice, gr_productorservicemodel, gr_productorservicessomeinstancesplaceholder, gr_provideservice, gr_publicholidays,
        gr_publicinstitution,
    gr_qualitativevalue, gr_quantitativevalue, gr_quantitativevaluefloat, gr_quantitativevalueinteger,
    gr_repair, gr_reseller,
    gr_saturday, gr_sell, gr_someitems, gr_sunday,
    gr_thursday, gr_tuesday, gr_typeandquantitynode,
    gr_unitpricespecification, gr_ups,
    gr_visa,
    gr_warrantypromise, gr_warrantyscope, gr_wednesday,

    // grddl
    grddl_transformation, grddl_transformationproperty,

    // gs1
    gs1s_additionalproductclassificationdetails, gs1s_additivedetails, gs1s_address, gs1s_ai, gs1s_allergendetails, gs1s_allergentypecode,
    gs1s_allergentypecode_13_bis_24_diaminophenoxypropane,
    gs1s_allergentypecode_1_naphthol, gs1s_allergentypecode_26_dimethoxy_35_pyridinediamine_hcl, gs1s_allergentypecode_2_hydroxyethyl_picramic_acid,
    gs1s_allergentypecode_2_methyl_5_hydroxyethylaminophenol, gs1s_allergentypecode_3_amino_24_dichlorophenol, gs1s_allergentypecode_3_aminophenol,
    gs1s_allergentypecode_4_amino_3_nitrophenol, gs1s_allergentypecode_4_hydroxy_propylamino_3_nitrophenol, gs1s_allergentypecode_abalone, gs1s_allergentypecode_almonds,
    gs1s_allergentypecode_alpha_isomethyl_ionone, gs1s_allergentypecode_amyl_cinnamal, gs1s_allergentypecode_amylcinnamyl_alcohol, gs1s_allergentypecode_anchovy,
    gs1s_allergentypecode_anise_alcohol, gs1s_allergentypecode_barley, gs1s_allergentypecode_barnacle, gs1s_allergentypecode_basa, gs1s_allergentypecode_bass,
    gs1s_allergentypecode_beech_nuts, gs1s_allergentypecode_beef, gs1s_allergentypecode_benzyl_alcohol, gs1s_allergentypecode_benzyl_benzoate,
    gs1s_allergentypecode_benzyl_cinnamate, gs1s_allergentypecode_benzyl_salicylate, gs1s_allergentypecode_bluefish, gs1s_allergentypecode_brazil_nuts,
    gs1s_allergentypecode_bream, gs1s_allergentypecode_butternuts, gs1s_allergentypecode_butylphenyl_methylpropionate, gs1s_allergentypecode_carp,
    gs1s_allergentypecode_carrots, gs1s_allergentypecode_cashew_nuts, gs1s_allergentypecode_catfish, gs1s_allergentypecode_celery,
    gs1s_allergentypecode_cereals_containing_gluten, gs1s_allergentypecode_char, gs1s_allergentypecode_chestnuts, gs1s_allergentypecode_chicken_meat,
    gs1s_allergentypecode_chinquapins, gs1s_allergentypecode_chub, gs1s_allergentypecode_cinnamal, gs1s_allergentypecode_cinnamyl_alcohol, gs1s_allergentypecode_cisco,
    gs1s_allergentypecode_citral, gs1s_allergentypecode_citronellol, gs1s_allergentypecode_clam, gs1s_allergentypecode_cockle, gs1s_allergentypecode_cocoa,
    gs1s_allergentypecode_coconuts, gs1s_allergentypecode_cod, gs1s_allergentypecode_conch, gs1s_allergentypecode_coriander, gs1s_allergentypecode_corn,
    gs1s_allergentypecode_cotton_seeds, gs1s_allergentypecode_coumarin, gs1s_allergentypecode_crab, gs1s_allergentypecode_crawfish, gs1s_allergentypecode_crustaceans,
    gs1s_allergentypecode_d_limonene, gs1s_allergentypecode_diaminophenols, gs1s_allergentypecode_eel, gs1s_allergentypecode_eggs, gs1s_allergentypecode_eugenol,
    gs1s_allergentypecode_evernia_furfuracea, gs1s_allergentypecode_evernia_prunastri, gs1s_allergentypecode_farnesol, gs1s_allergentypecode_fish,
    gs1s_allergentypecode_flounder, gs1s_allergentypecode_geraniol, gs1s_allergentypecode_ginkgo_nuts, gs1s_allergentypecode_glutamate, gs1s_allergentypecode_gluten,
    gs1s_allergentypecode_grouper, gs1s_allergentypecode_haddock, gs1s_allergentypecode_hake, gs1s_allergentypecode_halibut, gs1s_allergentypecode_hazelnuts,
    gs1s_allergentypecode_hc_blue_no_11, gs1s_allergentypecode_hc_blue_no_12, gs1s_allergentypecode_herring, gs1s_allergentypecode_hexyl_cinnamal,
    gs1s_allergentypecode_hickory_nuts, gs1s_allergentypecode_hydroxybenzomorpholine, gs1s_allergentypecode_hydroxycitronellal,
    gs1s_allergentypecode_hydroxyethyl_2_nitro_p_toluidine, gs1s_allergentypecode_hydroxyisohexyl_3_cyclohexene_carboxaldehyde_isoeugenol_limonene_linal,
    gs1s_allergentypecode_hydroxypropyl_bisn_hydroxyethyl_p_phenyldiamine_hcl, gs1s_allergentypecode_isoeugenol, gs1s_allergentypecode_kamut,
    gs1s_allergentypecode_krill, gs1s_allergentypecode_lactose, gs1s_allergentypecode_land, gs1s_allergentypecode_lichee_nuts, gs1s_allergentypecode_limpets,
    gs1s_allergentypecode_linalool, gs1s_allergentypecode_lobster, gs1s_allergentypecode_lupine, gs1s_allergentypecode_macadamia_nuts, gs1s_allergentypecode_mackerel,
    gs1s_allergentypecode_mahi_mahi, gs1s_allergentypecode_marlin, gs1s_allergentypecode_melatonin, gs1s_allergentypecode_methyl_2_octynoate,
    gs1s_allergentypecode_methyl_heptin_carbonate, gs1s_allergentypecode_milk, gs1s_allergentypecode_molluscs, gs1s_allergentypecode_monkfish_anglerfish_lotte,
    gs1s_allergentypecode_mussels, gs1s_allergentypecode_mustard, gs1s_allergentypecode_no_declared_allergens, gs1s_allergentypecode_oat, gs1s_allergentypecode_octopus,
    gs1s_allergentypecode_orange_roughy, gs1s_allergentypecode_oysters, gs1s_allergentypecode_p_methylaminophenol, gs1s_allergentypecode_p_phenylenediamine,
    gs1s_allergentypecode_peanuts, gs1s_allergentypecode_peas, gs1s_allergentypecode_pecan_nuts, gs1s_allergentypecode_perch, gs1s_allergentypecode_periwinkle,
    gs1s_allergentypecode_pike, gs1s_allergentypecode_pili_nuts, gs1s_allergentypecode_pine_nuts, gs1s_allergentypecode_pistachios, gs1s_allergentypecode_plaice,
    gs1s_allergentypecode_pod_fruits, gs1s_allergentypecode_pollock, gs1s_allergentypecode_pompano, gs1s_allergentypecode_poppy_seeds, gs1s_allergentypecode_porgy,
    gs1s_allergentypecode_pork, gs1s_allergentypecode_prawns, gs1s_allergentypecode_pulses, gs1s_allergentypecode_quahaugs, gs1s_allergentypecode_queensland_nuts,
    gs1s_allergentypecode_rockfish, gs1s_allergentypecode_rye, gs1s_allergentypecode_salicylate, gs1s_allergentypecode_salmon, gs1s_allergentypecode_sardine,
    gs1s_allergentypecode_scallops, gs1s_allergentypecode_seed_products, gs1s_allergentypecode_sesame_seeds, gs1s_allergentypecode_shark, gs1s_allergentypecode_shea_nuts,
    gs1s_allergentypecode_shellfish, gs1s_allergentypecode_shrimp, gs1s_allergentypecode_smelt, gs1s_allergentypecode_snapper, gs1s_allergentypecode_sole,
    gs1s_allergentypecode_soybeans, gs1s_allergentypecode_spelt, gs1s_allergentypecode_squid_calamari, gs1s_allergentypecode_sturgeon, gs1s_allergentypecode_sulphur_dioxide,
    gs1s_allergentypecode_sunflower_seeds, gs1s_allergentypecode_swordfish, gs1s_allergentypecode_tilapia, gs1s_allergentypecode_toluene_25_diamine,
    gs1s_allergentypecode_tree_nut_traces, gs1s_allergentypecode_tree_nuts, gs1s_allergentypecode_triticale, gs1s_allergentypecode_trout, gs1s_allergentypecode_tuna,
    gs1s_allergentypecode_turbot, gs1s_allergentypecode_walleye, gs1s_allergentypecode_walnuts, gs1s_allergentypecode_wheat, gs1s_allergentypecode_whelks,
    gs1s_allergentypecode_whitefish, gs1s_allergentypecode_whiting, gs1s_anatomicalformcode,
    gs1s_anatomicalformcode_belly, gs1s_anatomicalformcode_blood, gs1s_anatomicalformcode_bone, gs1s_anatomicalformcode_brain, gs1s_anatomicalformcode_carcass_nonpoultry,
    gs1s_anatomicalformcode_diaphram, gs1s_anatomicalformcode_esophagus, gs1s_anatomicalformcode_fat, gs1s_anatomicalformcode_feet, gs1s_anatomicalformcode_forequarter,
    gs1s_anatomicalformcode_gizzard, gs1s_anatomicalformcode_head, gs1s_anatomicalformcode_headmeat_cheekmeat, gs1s_anatomicalformcode_heart,
    gs1s_anatomicalformcode_hindquarter, gs1s_anatomicalformcode_horn, gs1s_anatomicalformcode_intestine_large, gs1s_anatomicalformcode_intestine_small,
    gs1s_anatomicalformcode_kidney, gs1s_anatomicalformcode_lips, gs1s_anatomicalformcode_liver, gs1s_anatomicalformcode_lungs, gs1s_anatomicalformcode_mixed_offal,
    gs1s_anatomicalformcode_mixed_parts_for_grounding_mincing, gs1s_anatomicalformcode_neck, gs1s_anatomicalformcode_pancreas, gs1s_anatomicalformcode_skin,
    gs1s_anatomicalformcode_stomach, gs1s_anatomicalformcode_tail, gs1s_anatomicalformcode_tendons, gs1s_anatomicalformcode_testicles, gs1s_anatomicalformcode_thymus,
    gs1s_anatomicalformcode_tongue, gs1s_anatomicalformcode_tripe, gs1s_anatomicalformcode_unclassified, gs1s_anatomicalformcode_unidentified,
    gs1s_anatomicalformcode_whole_bird, gs1s_anatomicalformcode_whole_muscle_nonpoultry_meatpart_piece, gs1s_anatomicalformcode_whole_muscle_poultry_part,
    gs1s_anatomicalformcode_whole_muscle_primal, gs1s_anatomicalformcode_whole_muscle_ribcut, gs1s_anatomicalformcode_whole_muscle_roastcut,
    gs1s_anatomicalformcode_whole_muscle_slice_chopcut, gs1s_anatomicalformcode_whole_muscle_slice_cutlet, gs1s_anatomicalformcode_whole_muscle_steak_chopcut,
    gs1s_anatomicalformcode_whole_muscle_subprimal,
    gs1s_authenticitydetails, gs1s_awardprize, gs1s_awardprizedetails, gs1s_beverage,
    gs1s_brand, gs1s_certification, gs1s_certificationdetails, gs1s_cheesefirmnesscode,
    gs1s_cheesefirmnesscode_extra_hard, gs1s_cheesefirmnesscode_firm_semihard, gs1s_cheesefirmnesscode_hard, gs1s_cheesefirmnesscode_soft, gs1s_cheesefirmnesscode_unidentified,
    gs1s_clothing, gs1s_colourcodedetails, gs1s_colourcodelist_buyer, gs1s_colourcodelist_ifps,
    gs1s_colourcodelist_ncs, gs1s_colourcodelist_nrf, gs1s_colourcodelist_pantone_hexachrome, gs1s_colourcodelist_pantone_matching, gs1s_colourcodelist_pantone_process_colour,
    gs1s_colourcodelist_pantone_textile, gs1s_colourcodelist_ral, gs1s_colourcodelist_seller, gs1s_colourcodelist_wws, gs1s_colourcodelistcode,
    gs1s_consumerlifestagecode,
    gs1s_consumerlifestagecode_adult, gs1s_consumerlifestagecode_all_ages, gs1s_consumerlifestagecode_baby_infant, gs1s_consumerlifestagecode_child_1_to_2_years,
    gs1s_consumerlifestagecode_child_2_years_onwards, gs1s_consumerlifestagecode_unclassified, gs1s_consumerlifestagecode_unidentified,
    gs1s_consumersalesconditionscode,
    gs1s_consumersalesconditionscode_btc, gs1s_consumersalesconditionscode_otc, gs1s_consumersalesconditionscode_prescription_required,
    gs1s_consumersalesconditionscode_restricted_to_sell_16, gs1s_consumersalesconditionscode_restricted_to_sell_18, gs1s_consumersalesconditionscode_restricted_to_sell_21,
    gs1s_contact, gs1s_contactpoint, gs1s_country, gs1s_diettypecode,
    gs1s_diettypecode_coeliac, gs1s_diettypecode_dietetic, gs1s_diettypecode_free_from_gluten, gs1s_diettypecode_halal, gs1s_diettypecode_kosher, gs1s_diettypecode_organic,
    gs1s_diettypecode_vegan, gs1s_diettypecode_vegetarian, gs1s_diettypecode_without_beef, gs1s_diettypecode_without_pork,   gs1s_diettypecodedetails, gs1s_discount,
    gs1s_discounttypecode, gs1s_discounttypecode_bogo, gs1s_discounttypecode_discounted_item, gs1s_discounttypecode_free_gift, gs1s_discounttypecode_free_shipping,
    gs1s_discounttypecode_other, gs1s_discounttypecode_percentage_off,
    gs1s_foodandbeveragepreparationinformation, gs1s_foodbeveragerefrigerationclaimcode,
    gs1s_foodbeveragerefrigerationclaimcode_can_be_refrigerated, gs1s_foodbeveragerefrigerationclaimcode_must_be_refrigerated,
    gs1s_foodbeveragerefrigerationclaimcode_shelf_stable, gs1s_foodbeveragerefrigerationclaimcode_unidentified, gs1s_foodbeveragetargetusecode,
    gs1s_foodbeveragetargetusecode_any_meal, gs1s_foodbeveragetargetusecode_breakfast, gs1s_foodbeveragetargetusecode_main_meal, gs1s_foodbeveragetargetusecode_portable_meal,
    gs1s_foodbeveragetargetusecode_snack, gs1s_foodbeveragetargetusecode_unclassified, gs1s_foodbeveragetobaccoingredient,
    gs1s_foodbeveragetobaccoingredientdetails, gs1s_foodbeveragetobaccoproduct, gs1s_foodbeveragetobaccotradeitem, gs1s_footwear, gs1s_footwearfasteningtypecode,
    gs1s_footwearfasteningtypecode_multiple_fastening, gs1s_footwearfasteningtypecode_shoe_lace, gs1s_footwearfasteningtypecode_slip_on_without_elastic,
    gs1s_footwearfasteningtypecode_slip_on_with_elastic, gs1s_footwearfasteningtypecode_strap, gs1s_footwearfasteningtypecode_unclassified,
    gs1s_footwearfasteningtypecode_unidentified, gs1s_footwearfasteningtypecode_velcro,
    gs1s_freshorseawaterfarmedcode,
    gs1s_freshorseawaterfarmedcode_freshwater_farmed, gs1s_freshorseawaterfarmedcode_seawater_farmed, gs1s_freshorseawaterfarmedcode_unclassified,
    gs1s_freshorseawaterfarmedcode_unidentified,
    gs1s_fruitsvegetables, gs1s_geocoordinates, gs1s_growingmethodcode,
    gs1s_growingmethodcode_cage_free, gs1s_growingmethodcode_cloned_foods, gs1s_growingmethodcode_conventional, gs1s_growingmethodcode_farm_raised,
    gs1s_growingmethodcode_field_grown, gs1s_growingmethodcode_fly_free, gs1s_growingmethodcode_free_range, gs1s_growingmethodcode_grass_fed,
    gs1s_growingmethodcode_greenhouse, gs1s_growingmethodcode_humanely_raised, gs1s_growingmethodcode_hydroponic, gs1s_growingmethodcode_integrated_pest_management,
    gs1s_growingmethodcode_organic, gs1s_growingmethodcode_shade_grown, gs1s_growingmethodcode_sustainable, gs1s_growingmethodcode_wild,
    gs1s_levelofcontainmentcode, gs1s_levelofcontainmentcodecontains, gs1s_levelofcontainmentcodefreefrom,
    gs1s_levelofcontainmentcodemaycontain, gs1s_maturationmethodcode,
    gs1s_maturationmethodcode_jet_fresh, gs1s_maturationmethodcode_preconditioned, gs1s_maturationmethodcode_tree_vine_ripe,
    gs1s_measurementprecisioncode, gs1s_measurementprecisioncode_approximately, gs1s_measurementprecisioncode_exact, gs1s_measurementprecisioncode_less_than,
    gs1s_meat, gs1s_meatpoultry, gs1s_milkbuttercreamyogurtcheeseeggssubstitutes,
    gs1s_nonbinarylogiccode, gs1s_nonbinarylogiccode_false, gs1s_nonbinarylogiccode_na, gs1s_nonbinarylogiccode_true, gs1s_nonbinarylogiccode_unspecified,
    gs1s_nutrientbasisquantitycode, gs1s_nutrientbasisquantitycode_by_measure, gs1s_nutrientbasisquantitycode_by_serving,
    gs1s_nutritionalclaimtypecode,
    gs1s_nutritionalclaimtypecode_additive_free, gs1s_nutritionalclaimtypecode_artificially_sweetened, gs1s_nutritionalclaimtypecode_cholesterol_free,
    gs1s_nutritionalclaimtypecode_colouring_agent_free, gs1s_nutritionalclaimtypecode_contains_glyzyrrhizin, gs1s_nutritionalclaimtypecode_contains_liquorice,
    gs1s_nutritionalclaimtypecode_contains_soy, gs1s_nutritionalclaimtypecode_egg_free, gs1s_nutritionalclaimtypecode_energy_free, gs1s_nutritionalclaimtypecode_energy_reduced,gs1s_nutritionalclaimtypecode_enriched_or_fortified_in_vitamins_and_or_minerals, gs1s_nutritionalclaimtypecode_fat_free, gs1s_nutritionalclaimtypecode_free_from_gluten,
    gs1s_nutritionalclaimtypecode_guaranteed_lactose_free, gs1s_nutritionalclaimtypecode_high_fibre, gs1s_nutritionalclaimtypecode_high_protein,
    gs1s_nutritionalclaimtypecode_high_vitamins_and_or_minerals, gs1s_nutritionalclaimtypecode_lactose_free, gs1s_nutritionalclaimtypecode_light_lite,
    gs1s_nutritionalclaimtypecode_low_energy, gs1s_nutritionalclaimtypecode_low_fat, gs1s_nutritionalclaimtypecode_low_lactose, gs1s_nutritionalclaimtypecode_low_protein,
    gs1s_nutritionalclaimtypecode_low_saturated_fat, gs1s_nutritionalclaimtypecode_low_sodium_salt, gs1s_nutritionalclaimtypecode_low_sugars,
    gs1s_nutritionalclaimtypecode_milk_free, gs1s_nutritionalclaimtypecode_milk_protein_free, gs1s_nutritionalclaimtypecode_natural_source_of_vitamins_and_or_minerals,
    gs1s_nutritionalclaimtypecode_non_alcoholic, gs1s_nutritionalclaimtypecode_nut_free, gs1s_nutritionalclaimtypecode_peanut_free,
    gs1s_nutritionalclaimtypecode_preservative_free, gs1s_nutritionalclaimtypecode_saturated_fat_free, gs1s_nutritionalclaimtypecode_sodium_free_or_salt_free,
    gs1s_nutritionalclaimtypecode_source_of_fibre, gs1s_nutritionalclaimtypecode_source_of_protein, gs1s_nutritionalclaimtypecode_soy_free,
    gs1s_nutritionalclaimtypecode_strongly_salted, gs1s_nutritionalclaimtypecode_sugars_free, gs1s_nutritionalclaimtypecode_sweetened_with_agave_syrup,
    gs1s_nutritionalclaimtypecode_sweetened_with_cane_sugar, gs1s_nutritionalclaimtypecode_sweetened_with_corn_syrup, gs1s_nutritionalclaimtypecode_sweetened_with_fructose,
    gs1s_nutritionalclaimtypecode_sweetened_with_fruit_juice, gs1s_nutritionalclaimtypecode_sweetened_with_fruit_syrup, gs1s_nutritionalclaimtypecode_sweetened_with_honey,
    gs1s_nutritionalclaimtypecode_sweetened_with_malt, gs1s_nutritionalclaimtypecode_sweetened_with_raw_beet_sugar, gs1s_nutritionalclaimtypecode_sweetened_with_white_sugar,
    gs1s_nutritionalclaimtypecode_very_low_gluten, gs1s_nutritionalclaimtypecode_very_low_sodium_salt, gs1s_nutritionalclaimtypecode_wheat_free,
    gs1s_nutritionalclaimtypecode_with_no_added_sugars, gs1s_nutritionmeasurementtype, gs1s_offer, gs1s_offering, gs1s_offerredemptiontypecode,
    gs1s_offerredemptiontypecode_coupon_code, gs1s_offerredemptiontypecode_gift_card, gs1s_offerredemptiontypecode_rebate, gs1s_offerredemptiontypecode_sale,
    gs1s_offerredemptiontypecode_single_use_code, gs1s_organicclaimagencycode,
    gs1s_organicclaimagencycode_bfa, gs1s_organicclaimagencycode_bioland, gs1s_organicclaimagencycode_demeter_bund, gs1s_organicclaimagencycode_demeter_international,
    gs1s_organicclaimagencycode_ecoland, gs1s_organicclaimagencycode_ecovin, gs1s_organicclaimagencycode_epa, gs1s_organicclaimagencycode_fda,
    gs1s_organicclaimagencycode_fsa, gs1s_organicclaimagencycode_gaa, gs1s_organicclaimagencycode_ifoa, gs1s_organicclaimagencycode_ifoam,
    gs1s_organicclaimagencycode_naturland, gs1s_organicclaimagencycode_qai, gs1s_organicclaimagencycode_suditirol, gs1s_organicclaimagencycode_usda,
    gs1s_organicclaimdetails, gs1s_organisation, gs1s_organisationroletype,
    gs1s_organisationroletype_accepting_party, gs1s_organisationroletype_bill_of_lading_recipient, gs1s_organisationroletype_bill_to,
    gs1s_organisationroletype_brand_owner, gs1s_organisationroletype_breeder, gs1s_organisationroletype_broker_agent, gs1s_organisationroletype_buyer,
    gs1s_organisationroletype_buyers_agent_representative, gs1s_organisationroletype_carrier, gs1s_organisationroletype_central_payment_service,
    gs1s_organisationroletype_checking_party, gs1s_organisationroletype_cheque_order, gs1s_organisationroletype_consignee, gs1s_organisationroletype_consolidator,
    gs1s_organisationroletype_consumer, gs1s_organisationroletype_corporate_identity, gs1s_organisationroletype_customs, gs1s_organisationroletype_customs_broker,
    gs1s_organisationroletype_cutter, gs1s_organisationroletype_declarants_agent_representative, gs1s_organisationroletype_delivery_party, gs1s_organisationroletype_designer,
    gs1s_organisationroletype_despatch_party, gs1s_organisationroletype_distributor, gs1s_organisationroletype_dock_door,
    gs1s_organisationroletype_empty_equipment_despatch_party, gs1s_organisationroletype_empty_equipment_return_party, gs1s_organisationroletype_equipment_owner,
    gs1s_organisationroletype_exporter, gs1s_organisationroletype_factor, gs1s_organisationroletype_fattener, gs1s_organisationroletype_freight_forwarder,
    gs1s_organisationroletype_goods_owner, gs1s_organisationroletype_grower, gs1s_organisationroletype_head_office, gs1s_organisationroletype_importer,
    gs1s_organisationroletype_information_provider, gs1s_organisationroletype_insurer, gs1s_organisationroletype_intermediary_bank_1,
    gs1s_organisationroletype_intermediary_bank_2, gs1s_organisationroletype_inventory_controller, gs1s_organisationroletype_inventory_reporting_party,
    gs1s_organisationroletype_invoicee, gs1s_organisationroletype_issuer_of_invoice, gs1s_organisationroletype_logistics_service_provider,
    gs1s_organisationroletype_manufacturer_of_goods, gs1s_organisationroletype_manufacturing_plant, gs1s_organisationroletype_mark_for,
    gs1s_organisationroletype_message_from, gs1s_organisationroletype_message_recipient, gs1s_organisationroletype_mincer, gs1s_organisationroletype_operating_division,
    gs1s_organisationroletype_operator, gs1s_organisationroletype_ordering_party, gs1s_organisationroletype_owner_of_equipment,
    gs1s_organisationroletype_owner_of_means_of_transport, gs1s_organisationroletype_party_declaring_the_value_added_tax,
    gs1s_organisationroletype_party_for_whom_item_is_ultimately_intended, gs1s_organisationroletype_party_receiving_private_data,
    gs1s_organisationroletype_party_recovering_the_value_added_tax, gs1s_organisationroletype_party_to_receive_all_documents,
    gs1s_organisationroletype_party_to_receive_commercial_invoice, gs1s_organisationroletype_party_to_receive_electronic_memo_of_invoice,
    gs1s_organisationroletype_party_to_receive_freight_bill, gs1s_organisationroletype_party_to_receive_refund, gs1s_organisationroletype_payee,
    gs1s_organisationroletype_payer, gs1s_organisationroletype_point_of_sale, gs1s_organisationroletype_price_location_party, gs1s_organisationroletype_proxy,
    gs1s_organisationroletype_public_warehouse, gs1s_organisationroletype_purchase_order_receiver, gs1s_organisationroletype_registered_agent,
    gs1s_organisationroletype_remit_to, gs1s_organisationroletype_returnable_asset_service_centre, gs1s_organisationroletype_seller,
    gs1s_organisationroletype_service_provider, gs1s_organisationroletype_ship_from, gs1s_organisationroletype_ship_to, gs1s_organisationroletype_slaughterer,
    gs1s_organisationroletype_store, gs1s_organisationroletype_substitute_supplier, gs1s_organisationroletype_supplier, gs1s_organisationroletype_transportation_carrier,
    gs1s_organisationroletype_visiting_address, gs1s_organisationroletype_warehouse_and_or_depot, gs1s_organisationroletype_warehouse_keeper,
    gs1s_organisationroletype_wholesaler,
    gs1s_packaging, gs1s_packagingdetails, gs1s_packagingfeaturecode,
    gs1s_packagingfeaturecode_base, gs1s_packagingfeaturecode_beam, gs1s_packagingfeaturecode_bung_seal, gs1s_packagingfeaturecode_cap, gs1s_packagingfeaturecode_carrier,
    gs1s_packagingfeaturecode_consumption_utensil, gs1s_packagingfeaturecode_core, gs1s_packagingfeaturecode_creel, gs1s_packagingfeaturecode_edge_protection,
    gs1s_packagingfeaturecode_handle, gs1s_packagingfeaturecode_inner_container, gs1s_packagingfeaturecode_internal_divider, gs1s_packagingfeaturecode_label,
    gs1s_packagingfeaturecode_lid, gs1s_packagingfeaturecode_liner, gs1s_packagingfeaturecode_lug, gs1s_packagingfeaturecode_nesting_edge, gs1s_packagingfeaturecode_peg,
    gs1s_packagingfeaturecode_pull_off_tab, gs1s_packagingfeaturecode_ring_holder, gs1s_packagingfeaturecode_rivet, gs1s_packagingfeaturecode_sleeve,
    gs1s_packagingfeaturecode_spout, gs1s_packagingfeaturecode_tag, gs1s_packagingfeaturecode_wicker_outer_container, gs1s_packagingfeaturecode_wrap,
    gs1s_packagingfunctioncode,
    gs1s_packagingfunctioncode_antiseptic, gs1s_packagingfunctioncode_anti_tampering, gs1s_packagingfunctioncode_coated, gs1s_packagingfunctioncode_compressed,
    gs1s_packagingfunctioncode_dispenser, gs1s_packagingfunctioncode_gift_wrapped, gs1s_packagingfunctioncode_isothermic, gs1s_packagingfunctioncode_modified_atmosphere,
    gs1s_packagingfunctioncode_oxygen_infused, gs1s_packagingfunctioncode_peel_off, gs1s_packagingfunctioncode_pinpack, gs1s_packagingfunctioncode_protected,
    gs1s_packagingfunctioncode_reinforced, gs1s_packagingfunctioncode_sift_proof, gs1s_packagingfunctioncode_tamper_evident, gs1s_packagingfunctioncode_water_resistant,
    gs1s_packagingmarkeddietallergencode,
    gs1s_packagingmarkeddietallergencode_approved_by_asthma_and_allergy_assoc, gs1s_packagingmarkeddietallergencode_approved_for_tube_feeding,
    gs1s_packagingmarkeddietallergencode_biological, gs1s_packagingmarkeddietallergencode_calories_per_portion, gs1s_packagingmarkeddietallergencode_contains_latex,
    gs1s_packagingmarkeddietallergencode_contains_pvc, gs1s_packagingmarkeddietallergencode_contains_pvc_without_phthalates,
    gs1s_packagingmarkeddietallergencode_contains_pvc_with_phthalates, gs1s_packagingmarkeddietallergencode_diet_product_450_800_kcal_per_day,
    gs1s_packagingmarkeddietallergencode_diet_product_800_1200_kcal_per_day, gs1s_packagingmarkeddietallergencode_gezonde_keuze_klavertje,
    gs1s_packagingmarkeddietallergencode_halal, gs1s_packagingmarkeddietallergencode_ik_kies_bewust, gs1s_packagingmarkeddietallergencode_kosher,
    gs1s_packagingmarkeddietallergencode_lactase_enzyme, gs1s_packagingmarkeddietallergencode_low_on_phenylalanine, gs1s_packagingmarkeddietallergencode_low_on_sugar,
    gs1s_packagingmarkeddietallergencode_mothers_milk_substitute, gs1s_packagingmarkeddietallergencode_nutrition_supplement,
    gs1s_packagingmarkeddietallergencode_nyckelhal_mark, gs1s_packagingmarkeddietallergencode_vegetarian,
    gs1s_packagingmarkedfreefromcode,
    gs1s_packagingmarkedfreefromcode_free_from_artificial_colouring, gs1s_packagingmarkedfreefromcode_free_from_artificial_flavouring,
    gs1s_packagingmarkedfreefromcode_free_from_artificial_preservatives, gs1s_packagingmarkedfreefromcode_free_from_cholesterol,
    gs1s_packagingmarkedfreefromcode_free_from_cloned_food, gs1s_packagingmarkedfreefromcode_free_from_dairy, gs1s_packagingmarkedfreefromcode_free_from_egg,
    gs1s_packagingmarkedfreefromcode_free_from_fish, gs1s_packagingmarkedfreefromcode_free_from_gluten, gs1s_packagingmarkedfreefromcode_free_from_lactose,
    gs1s_packagingmarkedfreefromcode_free_from_latex, gs1s_packagingmarkedfreefromcode_free_from_legume_protein, gs1s_packagingmarkedfreefromcode_free_from_milk,
    gs1s_packagingmarkedfreefromcode_free_from_milk_protein, gs1s_packagingmarkedfreefromcode_free_from_natural_gluten, gs1s_packagingmarkedfreefromcode_free_from_peanuts,
    gs1s_packagingmarkedfreefromcode_free_from_protein, gs1s_packagingmarkedfreefromcode_free_from_pvc, gs1s_packagingmarkedfreefromcode_free_from_soya,
    gs1s_packagingmarkedfreefromcode_free_from_sugar, gs1s_packagingmarkedfreefromcode_free_from_transfat, gs1s_packagingmarkedfreefromcode_reduced_lactose,
    gs1s_packagingmarkedfreefromcode_reduced_protein, gs1s_packagingmarkedfreefromcode_reduced_transfat, gs1s_packagingmarkedfreefromcode_very_low_gluten,
    gs1s_packagingmarkedfreefromcode_without_added_salt, gs1s_packagingmarkedfreefromcode_without_added_sugar, gs1s_packagingmarkedfreefromcode_without_added_sweetener,
    gs1s_packagingmarkedlabelaccreditationcode,
    gs1s_packagingmarkedlabelaccreditationcode_ama_organic_seal, gs1s_packagingmarkedlabelaccreditationcode_aus_kaup_estonia, gs1s_packagingmarkedlabelaccreditationcode_bdih_logo, gs1s_packagingmarkedlabelaccreditationcode_beter_leven_1_ster,
    gs1s_packagingmarkedlabelaccreditationcode_beter_leven_2_ster, gs1s_packagingmarkedlabelaccreditationcode_beter_leven_3_ster, gs1s_packagingmarkedlabelaccreditationcode_bio_austria_label, gs1s_packagingmarkedlabelaccreditationcode_bio_label_german,
    gs1s_packagingmarkedlabelaccreditationcode_bio_suisse_bud_seal, gs1s_packagingmarkedlabelaccreditationcode_blue_angel, gs1s_packagingmarkedlabelaccreditationcode_bord_bia_approved, gs1s_packagingmarkedlabelaccreditationcode_bord_bia_approved_meat,
    gs1s_packagingmarkedlabelaccreditationcode_bra_miljoval_label_swedish, gs1s_packagingmarkedlabelaccreditationcode_crossed_grain_symbol, gs1s_packagingmarkedlabelaccreditationcode_demeter_label, gs1s_packagingmarkedlabelaccreditationcode_ecocert_certificate,
    gs1s_packagingmarkedlabelaccreditationcode_eco_label_ladybug, gs1s_packagingmarkedlabelaccreditationcode_ec_national_health_mark, gs1s_packagingmarkedlabelaccreditationcode_eesti_okomark, gs1s_packagingmarkedlabelaccreditationcode_eesti_parim_toiduaine,
    gs1s_packagingmarkedlabelaccreditationcode_eko, gs1s_packagingmarkedlabelaccreditationcode_eu_eco_label, gs1s_packagingmarkedlabelaccreditationcode_eu_organic_farming, gs1s_packagingmarkedlabelaccreditationcode_fair_trade_mark,
    gs1s_packagingmarkedlabelaccreditationcode_falken, gs1s_packagingmarkedlabelaccreditationcode_finnish_heart_symbol, gs1s_packagingmarkedlabelaccreditationcode_forest_stewardship_council_label, gs1s_packagingmarkedlabelaccreditationcode_gmo_marked,
    gs1s_packagingmarkedlabelaccreditationcode_goods_from_finland_blue_swan, gs1s_packagingmarkedlabelaccreditationcode_green_dot, gs1s_packagingmarkedlabelaccreditationcode_green_restaurant_association_endorsed,
    gs1s_packagingmarkedlabelaccreditationcode_green_seal_certified, gs1s_packagingmarkedlabelaccreditationcode_guaranteed_irish, gs1s_packagingmarkedlabelaccreditationcode_krav_mark, gs1s_packagingmarkedlabelaccreditationcode_label_of_the_allergy_and_asthma_federation,
    gs1s_packagingmarkedlabelaccreditationcode_leaping_bunny, gs1s_packagingmarkedlabelaccreditationcode_loodussobralik_toode_estonia, gs1s_packagingmarkedlabelaccreditationcode_love_irish_food, gs1s_packagingmarkedlabelaccreditationcode_made_in_finland_flag_with_key,
    gs1s_packagingmarkedlabelaccreditationcode_marine_stewardship_council_label, gs1s_packagingmarkedlabelaccreditationcode_max_havelaar, gs1s_packagingmarkedlabelaccreditationcode_natrue_label, gs1s_packagingmarkedlabelaccreditationcode_nyckelhalet,
    gs1s_packagingmarkedlabelaccreditationcode_oeko_tex_label, gs1s_packagingmarkedlabelaccreditationcode_official_eco_label_sun, gs1s_packagingmarkedlabelaccreditationcode_pefc, gs1s_packagingmarkedlabelaccreditationcode_protected_designation_of_origin,
    gs1s_packagingmarkedlabelaccreditationcode_protected_geographical_indication, gs1s_packagingmarkedlabelaccreditationcode_protected_harvest_certified, gs1s_packagingmarkedlabelaccreditationcode_quality_mark_ireland,
    gs1s_packagingmarkedlabelaccreditationcode_rainforest_alliance, gs1s_packagingmarkedlabelaccreditationcode_scharrelvlees, gs1s_packagingmarkedlabelaccreditationcode_soil_association_organic_symbol, gs1s_packagingmarkedlabelaccreditationcode_sustainable_palm_oil_rspo,
    gs1s_packagingmarkedlabelaccreditationcode_svanen, gs1s_packagingmarkedlabelaccreditationcode_swedish_seal_of_quality, gs1s_packagingmarkedlabelaccreditationcode_traditional_specialty_guaranteed, gs1s_packagingmarkedlabelaccreditationcode_tunnustatud_eesti_maitse,
    gs1s_packagingmarkedlabelaccreditationcode_tunnustatud_maitse, gs1s_packagingmarkedlabelaccreditationcode_uniquely_finnish, gs1s_packagingmarkedlabelaccreditationcode_usda, gs1s_packagingmarkedlabelaccreditationcode_utz_certified,
    gs1s_packagingmarkedlabelaccreditationcode_vaelg_fuldkorn_forst, gs1s_packagingmarkedlabelaccreditationcode_wwf_panda_label,
    gs1s_packagingmaterialdetails, gs1s_packagingmaterialtypecode,
    gs1s_packagingmaterialtypecode_ceramic, gs1s_packagingmaterialtypecode_cloth_or_fabric, gs1s_packagingmaterialtypecode_composite,
    gs1s_packagingmaterialtypecode_corrugated_board_double_wall, gs1s_packagingmaterialtypecode_corrugated_board_other,
    gs1s_packagingmaterialtypecode_corrugated_board_single_wall, gs1s_packagingmaterialtypecode_corrugated_board_triple_wall,
    gs1s_packagingmaterialtypecode_fibre_burlap, gs1s_packagingmaterialtypecode_fibre_cotton, gs1s_packagingmaterialtypecode_fibre_flax,
    gs1s_packagingmaterialtypecode_fibre_hemp, gs1s_packagingmaterialtypecode_fibre_jute, gs1s_packagingmaterialtypecode_fibre_other, gs1s_packagingmaterialtypecode_foam,
    gs1s_packagingmaterialtypecode_glass, gs1s_packagingmaterialtypecode_glass_coloured, gs1s_packagingmaterialtypecode_laminated_carton,
    gs1s_packagingmaterialtypecode_metal_aluminum, gs1s_packagingmaterialtypecode_metal_brass, gs1s_packagingmaterialtypecode_metal_iron,
    gs1s_packagingmaterialtypecode_metal_lead, gs1s_packagingmaterialtypecode_metal_other, gs1s_packagingmaterialtypecode_metal_stainless_steel,
    gs1s_packagingmaterialtypecode_metal_steel, gs1s_packagingmaterialtypecode_metal_tin, gs1s_packagingmaterialtypecode_mineral_calcium_carbonate,
    gs1s_packagingmaterialtypecode_mineral_other, gs1s_packagingmaterialtypecode_mineral_talc, gs1s_packagingmaterialtypecode_natural_rubber,
    gs1s_packagingmaterialtypecode_other, gs1s_packagingmaterialtypecode_paper_corrugated, gs1s_packagingmaterialtypecode_paper_molded_pulp,
    gs1s_packagingmaterialtypecode_paper_other, gs1s_packagingmaterialtypecode_paper_paper, gs1s_packagingmaterialtypecode_paper_paperboard,
    gs1s_packagingmaterialtypecode_paper_rayon, gs1s_packagingmaterialtypecode_plastic_bioplastic, gs1s_packagingmaterialtypecode_plastic_other,
    gs1s_packagingmaterialtypecode_plastic_thermoplastics, gs1s_packagingmaterialtypecode_polymer_cellulose_acetate, gs1s_packagingmaterialtypecode_polymer_epoxy,
    gs1s_packagingmaterialtypecode_polymer_eva, gs1s_packagingmaterialtypecode_polymer_evoh, gs1s_packagingmaterialtypecode_polymer_hdpe,
    gs1s_packagingmaterialtypecode_polymer_ldpe, gs1s_packagingmaterialtypecode_polymer_lldpe, gs1s_packagingmaterialtypecode_polymer_mdpe,
    gs1s_packagingmaterialtypecode_polymer_nylon, gs1s_packagingmaterialtypecode_polymer_other, gs1s_packagingmaterialtypecode_polymer_pan,
    gs1s_packagingmaterialtypecode_polymer_pc, gs1s_packagingmaterialtypecode_polymer_pcl, gs1s_packagingmaterialtypecode_polymer_pe,
    gs1s_packagingmaterialtypecode_polymer_pen, gs1s_packagingmaterialtypecode_polymer_pet, gs1s_packagingmaterialtypecode_polymer_pha,
    gs1s_packagingmaterialtypecode_polymer_pla, gs1s_packagingmaterialtypecode_polymer_pp, gs1s_packagingmaterialtypecode_polymer_ps,
    gs1s_packagingmaterialtypecode_polymer_pu, gs1s_packagingmaterialtypecode_polymer_pva, gs1s_packagingmaterialtypecode_polymer_pvc,
    gs1s_packagingmaterialtypecode_polymer_pvdc, gs1s_packagingmaterialtypecode_polymer_tps,
    gs1s_packagingrecyclingprocesstypecode,
    gs1s_packagingrecyclingprocesstypecode_compostable, gs1s_packagingrecyclingprocesstypecode_energy_recoverable, gs1s_packagingrecyclingprocesstypecode_recyclable, gs1s_packagingrecyclingprocesstypecode_reusable,
    gs1s_packagingrecyclingschemecode,
    gs1s_packagingrecyclingschemecode_alko, gs1s_packagingrecyclingschemecode_a_pullo, gs1s_packagingrecyclingschemecode_eko_pullo, gs1s_packagingrecyclingschemecode_palpa,
    gs1s_packagingshapecode,
    gs1s_packagingshapecode_bar, gs1s_packagingshapecode_coil, gs1s_packagingshapecode_cone, gs1s_packagingshapecode_cylindrical, gs1s_packagingshapecode_polygon,
    gs1s_packagingshapecode_rectangular, gs1s_packagingshapecode_spherical, gs1s_packagingshapecode_tablet, gs1s_packagingshapecode_unspecified,
    gs1s_paymentmethod,
    gs1s_paymentmethod_bankers_draft, gs1s_paymentmethod_bank_cheque, gs1s_paymentmethod_bank_giro, gs1s_paymentmethod_bookentry_credit, gs1s_paymentmethod_bookentry_debit,
    gs1s_paymentmethod_bop, gs1s_paymentmethod_cash, gs1s_paymentmethod_certified_cheque, gs1s_paymentmethod_cheque, gs1s_paymentmethod_credit_card,
    gs1s_paymentmethod_credit_card_amex, gs1s_paymentmethod_credit_card_diners_club, gs1s_paymentmethod_credit_card_discover, gs1s_paymentmethod_credit_card_mastercard,
    gs1s_paymentmethod_credit_card_visa, gs1s_paymentmethod_debit_card, gs1s_paymentmethod_debit_card_maestro, gs1s_paymentmethod_debit_card_mastercard,
    gs1s_paymentmethod_debit_card_visa, gs1s_paymentmethod_debit_card_visa_electron, gs1s_paymentmethod_electronic_credit_ach, gs1s_paymentmethod_electronic_debit_ach,
    gs1s_paymentmethod_fed_wire_non_repetitive, gs1s_paymentmethod_fed_wire_repetitive, gs1s_paymentmethod_international_wire, gs1s_paymentmethod_letter_of_credit,
    gs1s_paymentmethod_online_payment, gs1s_paymentmethod_online_payment_apple_pay, gs1s_paymentmethod_online_payment_google_wallet, gs1s_paymentmethod_online_payment_paypal,
    gs1s_paymentmethod_postgiro, gs1s_paymentmethod_wire_transfer_credit, gs1s_paymentmethod_wire_transfer_debit, gs1s_place, gs1s_postaladdress, gs1s_preparationtypecode,
    gs1s_preparationtypecode_as_drained, gs1s_preparationtypecode_bake, gs1s_preparationtypecode_barbecue, gs1s_preparationtypecode_blanch,
    gs1s_preparationtypecode_blind_bake, gs1s_preparationtypecode_boil, gs1s_preparationtypecode_braise, gs1s_preparationtypecode_broil, gs1s_preparationtypecode_deep_fry,
    gs1s_preparationtypecode_double_steam, gs1s_preparationtypecode_freeze, gs1s_preparationtypecode_fry, gs1s_preparationtypecode_griddle_fry, gs1s_preparationtypecode_grill,
    gs1s_preparationtypecode_heat_and_serve, gs1s_preparationtypecode_microwave, gs1s_preparationtypecode_pan_fry, gs1s_preparationtypecode_poach,
    gs1s_preparationtypecode_prepared, gs1s_preparationtypecode_pressure_cook, gs1s_preparationtypecode_pressure_fry, gs1s_preparationtypecode_ready_to_drink,
    gs1s_preparationtypecode_ready_to_eat, gs1s_preparationtypecode_reconstitute, gs1s_preparationtypecode_refrigerate, gs1s_preparationtypecode_roast,
    gs1s_preparationtypecode_rotisserie, gs1s_preparationtypecode_saute, gs1s_preparationtypecode_sear, gs1s_preparationtypecode_simmer, gs1s_preparationtypecode_smoke,
    gs1s_preparationtypecode_steam, gs1s_preparationtypecode_stew, gs1s_preparationtypecode_stir_fry, gs1s_preparationtypecode_thaw, gs1s_preparationtypecode_unprepared,
    gs1s_preparationtypecode_unspecified, gs1s_preservationtechniquecode,
    gs1s_preservationtechniquecode_acidification, gs1s_preservationtechniquecode_alcohol_curing, gs1s_preservationtechniquecode_attested_milk,
    gs1s_preservationtechniquecode_boiling, gs1s_preservationtechniquecode_brining, gs1s_preservationtechniquecode_canning, gs1s_preservationtechniquecode_conserve,
    gs1s_preservationtechniquecode_dehydration, gs1s_preservationtechniquecode_drying, gs1s_preservationtechniquecode_fermentation,
    gs1s_preservationtechniquecode_freeze_drying, gs1s_preservationtechniquecode_freezing, gs1s_preservationtechniquecode_high_temperature_treated_milk,
    gs1s_preservationtechniquecode_hot_smoke_curing, gs1s_preservationtechniquecode_ionisation, gs1s_preservationtechniquecode_irradiation,
    gs1s_preservationtechniquecode_pasteurisation, gs1s_preservationtechniquecode_quick_freezing, gs1s_preservationtechniquecode_salt_curing,
    gs1s_preservationtechniquecode_sous_vide, gs1s_preservationtechniquecode_sterilisation, gs1s_preservationtechniquecode_sugar_curing,
    gs1s_preservationtechniquecode_ultra_high_temperature, gs1s_preservationtechniquecode_under_modified_atmosphere, gs1s_preservationtechniquecode_vacuum_packed,
    gs1s_price, gs1s_pricespecification, gs1s_product, gs1s_productyielddetails, gs1s_productyieldtypecode,
    gs1s_productyieldtypecode_after_cooking, gs1s_productyieldtypecode_after_dilution, gs1s_productyieldtypecode_drained_weight, gs1s_productyieldtypecode_unspecified,
    gs1s_quantitativevalue, gs1s_referencedfiledetails, gs1s_referencedfiletypecode,
    gs1s_referencedfiletypecode_diet_certificate, gs1s_referencedfiletypecode_document, gs1s_referencedfiletypecode_group_characteristic_sheet,
    gs1s_referencedfiletypecode_logo, gs1s_referencedfiletypecode_marketing_information, gs1s_referencedfiletypecode_out_of_package_image,
    gs1s_referencedfiletypecode_planogram, gs1s_referencedfiletypecode_product_label_image, gs1s_referencedfiletypecode_safety_data_sheet,
    gs1s_referencedfiletypecode_safety_summary_sheet, gs1s_referencedfiletypecode_trade_item_description, gs1s_referencedfiletypecode_video,
    gs1s_referencedfiletypecode_warranty_information, gs1s_referencedfiletypecode_website, gs1s_referencedresource,
    gs1s_returnablepackagedepositdetails, gs1s_seafood, gs1s_seasonparametercode,
    gs1s_seasonparametercode_all_year, gs1s_seasonparametercode_autumn, gs1s_seasonparametercode_autumn_winter, gs1s_seasonparametercode_spring,
    gs1s_seasonparametercode_spring_summer, gs1s_seasonparametercode_summer, gs1s_seasonparametercode_winter,
    gs1s_securitymarking, gs1s_securitymarking_hologram, gs1s_securitymarking_microprinting,
    gs1s_securitymarking_uvink, gs1s_securitymarking_watermark, gs1s_sharpnessofcheesecode,
    gs1s_sharpnessofcheesecode_extra_extra_sharp, gs1s_sharpnessofcheesecode_extra_sharp, gs1s_sharpnessofcheesecode_mild, gs1s_sharpnessofcheesecode_regular,
    gs1s_sharpnessofcheesecode_sharp, gs1s_sharpnessofcheesecode_unclassified,
    gs1s_sizecodedetails, gs1s_sizedetails, gs1s_sizegroupcode,
    gs1s_sizegroupcode_boys, gs1s_sizegroupcode_girls, gs1s_sizegroupcode_infants, gs1s_sizegroupcode_juniors, gs1s_sizegroupcode_maternity, gs1s_sizegroupcode_mens,
    gs1s_sizegroupcode_mens_tall, gs1s_sizegroupcode_misses, gs1s_sizegroupcode_petite, gs1s_sizegroupcode_womens, gs1s_sizegroupcode_womens_tall,
    gs1s_sizesystemcode,
    gs1s_sizesystemcode_australia, gs1s_sizesystemcode_continental, gs1s_sizesystemcode_europe, gs1s_sizesystemcode_japan, gs1s_sizesystemcode_mexico,
    gs1s_sizesystemcode_uk, gs1s_sizesystemcode_us,
    gs1s_sizetypecode,
    gs1s_sizetypecode_back, gs1s_sizetypecode_chest_bust, gs1s_sizetypecode_collar, gs1s_sizetypecode_cup, gs1s_sizetypecode_hips, gs1s_sizetypecode_inseam,
    gs1s_sizetypecode_length, gs1s_sizetypecode_one_dimension, gs1s_sizetypecode_outside_leg, gs1s_sizetypecode_sleeve, gs1s_sizetypecode_waist, gs1s_sizetypecode_width,
    gs1s_sourceanimalcode,
    gs1s_sourceanimalcode_alligator, gs1s_sourceanimalcode_ass, gs1s_sourceanimalcode_bear, gs1s_sourceanimalcode_beef_cow, gs1s_sourceanimalcode_boar,
    gs1s_sourceanimalcode_buffalo, gs1s_sourceanimalcode_calf, gs1s_sourceanimalcode_camel, gs1s_sourceanimalcode_chicken, gs1s_sourceanimalcode_cockerel,
    gs1s_sourceanimalcode_cow, gs1s_sourceanimalcode_crocodile, gs1s_sourceanimalcode_deer, gs1s_sourceanimalcode_dog, gs1s_sourceanimalcode_duck,
    gs1s_sourceanimalcode_duckling, gs1s_sourceanimalcode_fish, gs1s_sourceanimalcode_fowl, gs1s_sourceanimalcode_frog, gs1s_sourceanimalcode_goat,
    gs1s_sourceanimalcode_goose, gs1s_sourceanimalcode_grouse, gs1s_sourceanimalcode_guineafowl, gs1s_sourceanimalcode_hare, gs1s_sourceanimalcode_horse,
    gs1s_sourceanimalcode_invertebrate, gs1s_sourceanimalcode_lamb, gs1s_sourceanimalcode_land_snail, gs1s_sourceanimalcode_milk_cow, gs1s_sourceanimalcode_moose,
    gs1s_sourceanimalcode_ostrich, gs1s_sourceanimalcode_other, gs1s_sourceanimalcode_partridge, gs1s_sourceanimalcode_pheasant, gs1s_sourceanimalcode_pigeon,
    gs1s_sourceanimalcode_pork, gs1s_sourceanimalcode_poussin, gs1s_sourceanimalcode_quail, gs1s_sourceanimalcode_rabbit, gs1s_sourceanimalcode_rat,
    gs1s_sourceanimalcode_reindeer, gs1s_sourceanimalcode_roe_deer, gs1s_sourceanimalcode_sheep, gs1s_sourceanimalcode_shellfish, gs1s_sourceanimalcode_snake,
    gs1s_sourceanimalcode_snipe, gs1s_sourceanimalcode_sparrow, gs1s_sourceanimalcode_thrush, gs1s_sourceanimalcode_turkey, gs1s_sourceanimalcode_turtle,
    gs1s_sourceanimalcode_woodcock, gs1s_sourceanimalcode_yak,
    gs1s_sportingactivitytypecode,
    gs1s_sportingactivitytypecode_american_football, gs1s_sportingactivitytypecode_archery, gs1s_sportingactivitytypecode_badminton, gs1s_sportingactivitytypecode_baseball,
    gs1s_sportingactivitytypecode_basketball, gs1s_sportingactivitytypecode_boxing, gs1s_sportingactivitytypecode_climbing, gs1s_sportingactivitytypecode_cricket,
    gs1s_sportingactivitytypecode_cycling, gs1s_sportingactivitytypecode_diving, gs1s_sportingactivitytypecode_equestrian, gs1s_sportingactivitytypecode_fencing,
    gs1s_sportingactivitytypecode_fishing, gs1s_sportingactivitytypecode_football, gs1s_sportingactivitytypecode_golf, gs1s_sportingactivitytypecode_gymnastics,
    gs1s_sportingactivitytypecode_hockey, gs1s_sportingactivitytypecode_ice_hockey, gs1s_sportingactivitytypecode_ice_skating, gs1s_sportingactivitytypecode_motor_cycling,
    gs1s_sportingactivitytypecode_rugby, gs1s_sportingactivitytypecode_running, gs1s_sportingactivitytypecode_skiing, gs1s_sportingactivitytypecode_squash,
    gs1s_sportingactivitytypecode_surfing, gs1s_sportingactivitytypecode_swimming, gs1s_sportingactivitytypecode_tennis, gs1s_sportingactivitytypecode_unclassified,
    gs1s_sportingactivitytypecode_unidentified,
    gs1s_targetconsumergendercode,
    gs1s_targetconsumergendercode_female, gs1s_targetconsumergendercode_male, gs1s_targetconsumergendercode_unisex,
    gs1s_targetmarketdetails, gs1s_textilematerial, gs1s_textilematerialdetails,
    gs1s_tradechannelcode, gs1s_tradechannelcode_instore_only, gs1s_tradechannelcode_omnichannel, gs1s_tradechannelcode_online_only, gs1s_tradeitem,
    gs1s_typecode, gs1s_uppertypecode,
    gs1s_uppertypecode_closed_toe_closed_back_open_instep, gs1s_uppertypecode_closed_toe_open_back, gs1s_uppertypecode_closed_toe_strap_back,
    gs1s_uppertypecode_fully_closed, gs1s_uppertypecode_open_toe_fully_closed_back, gs1s_uppertypecode_open_toe_open_back, gs1s_uppertypecode_open_toe_strap_back,
    gs1s_uppertypecode_unclassified, gs1s_warranty, gs1s_warrantypromise, gs1s_wearableproduct, gs1s_wearabletradeitem,

    // iCal
    ical_vevent, ical_vtimezone,

    // jsonld
    json_context, json_prefixdefinition, json_termdefinition,

    // ldp
    ldp_ascending,
    ldp_basiccontainer,
    ldp_container,
    ldp_descending,
    ldp_directcontainer,
    ldp_indirectcontainer,
    ldp_membersubject,
    ldp_nonrdfsource,
    ldp_page, ldp_pagesortcriterion, ldp_prefercontainment, ldp_preferemptycontainer, ldp_prefermembership, ldp_preferminimalcontainer,
    ldp_rdfsource, ldp_resource,

    // locn
    loc_address, loc_geometry,

    // media
    ma_agent, ma_audiotrack,
    ma_collection,
    ma_datatrack,
    ma_image,
    ma_location,
    ma_mediafragment, ma_mediaresource,
    ma_organisation,
    ma_person,
    ma_rating,
    ma_targetaudience, ma_track,
    ma_videotrack,

    // living standards microformats 1 reference
    mft_hcard, mf_vevent,

    // standard microformats v1 vocabulary
    mft_adr,
    mft_geo,
    mft_haggregate, mft_hatom, mft_haudio, mft_hcalendar, mft_hentry, mft_hlisting, mft_hmedia, mft_hnews, mft_hproduct, mft_hrecipe, mft_hresume, mft_hreview,

    // standard microformats v2 vocabulary
    mft2_hadr, mft2_hbreadcrumb, mft2_hcard, mft2_hcite, mft2_hentry, mft2_hevent, mft2_hfeed, mft2_hgeo, mft2_hitem, mft2_hlisting, mft2_hproduct, mft2_hrecipe, mft2_hresume,
        mft2_hreview, mft2_haggregate,

    // web annotation
    oa_annotation, oa_assessing, oa_autodirection,
    oa_bookmarking,
    oa_choice, oa_classifying, oa_commenting, oa_cssselector, oa_cssstyle,
    oa_datapositionselector, oa_describing, oa_direction,
    oa_editing,
    oa_fragmentselector,
    oa_highlighting,
    oa_httprequeststate,
    oa_identifying,
    oa_linking, oa_ltrdirection,
    oa_moderating, oa_motivation,
    oa_prefercontaineddescriptions, oa_prefercontainediris,
    oa_questioning,
    oa_rangeselector, oa_replying, oa_resourceselection, oa_rtldirection,
    oa_selector, oa_specificresource, oa_state, oa_style, oa_svgselector,
    oa_tagging, oa_textpositionselector, oa_textquoteselector, oa_textualbody, oa_timestate,
    oa_xpathselector,

    // open digital rights
    odrl_action, odrl_agreement, odrl_assertion, odrl_asset, odrl_assetcollection,
    odrl_conflictterm, odrl_constraint,
    odrl_duty,
    odrl_leftoperand, odrl_logicalconstraint,
    odrl_offer, odrl_operator,
    odrl_party, odrl_partycollection, odrl_permission, odrl_policy, odrl_privacy, odrl_prohibition,
    odrl_request, odrl_rightoperand, odrl_rule,
    odrl_set,
    odrl_ticket,

    odrl_accepttracking, odrl_adhocshare, odrl_aggregate, odrl_annotate, odrl_anonymize, odrl_append, odrl_appendto, odrl_archive, odrl_attachpolicy, odrl_attachsource,
        odrl_attribute, odrl_attribution,
    odrl_commercialize, odrl_commericaluse, odrl_compensate, odrl_concurrentuse, odrl_copy,
    odrl_delete, odrl_derivativeworks, odrl_derive, odrl_digitize, odrl_display, odrl_distribute, odrl_distribution,
    odrl_ensureexclusivity, odrl_execute, odrl_export, odrl_extract, odrl_extractchar, odrl_extractpage, odrl_extractword,
    odrl_give, odrl_grantuse,
    odrl_include, odrl_index, odrl_inform, odrl_install,
    odrl_lease, odrl_lend, odrl_license,
    odrl_modify, odrl_move,
    odrl_nextpolicy, odrl_notice,
    odrl_obtainconsent,
    odrl_pay, odrl_play, odrl_present, odrl_preview, odrl_print,
    odrl_read, odrl_reproduce, odrl_reproduction, odrl_reviewpolicy,
    odrl_secondaryuse, odrl_sell, odrl_share, odrl_sharealike, odrl_sharing, odrl_sourcecode, odrl_stream, odrl_synchronize,odrl_texttospeech, odrl_transfer,
        odrl_transform, odrl_translate,
    odrl_uninstall, odrl_use,
    odrl_watermark, odrl_write, odrl_writeto,

    odrl_eq,
    odrl_gt, odrl_gteq,
    odrl_haspart,
    odrl_isa, odrl_isallof, odrl_isanyof, odrl_isnoneof, odrl_ispartof,
    odrl_lt, odrl_lteq,
    odrl_neq,

    odrl_absoluteposition, odrl_absolutesize, odrl_absolutespatialposition, odrl_absolutetemporalposition,
    odrl_count,
    odrl_datetime, odrl_delayperiod, odrl_deliverychannel, odrl_device,
    odrl_elapsedtime, odrl_event,
    odrl_fileformat,
    odrl_industry,
    odrl_language,
    odrl_media, odrl_meteredtime,
    odrl_payamount, odrl_percentage, odrl_product, odrl_purpose,
    odrl_recipient, odrl_relativeposition, odrl_relativesize, odrl_relativespatialposition, odrl_relativetemporalposition, odrl_resolution,
    odrl_spatial, odrl_spatialcoordinates, odrl_system, odrl_systemdevice,
    odrl_timeinterval,
    odrl_unitofcount,
    odrl_version, odrl_virtuallocation,

    odrl_invalid, odrl_perm, odrl_prohibit,

    // org
    org_changeevent,
    org_formalorganisation,
    org_head,
    org_membership,
    org_organisation, org_organisationalcollaboration, org_organisationalunit,
    org_post,
    org_role,
    org_site,

    // owl
    owl_alldifferent, owl_alldisjointclasses, owl_alldisjointproperties, owl_annotation, owl_annotationproperty, owl_asymmetricproperty, owl_axiom,
    owl_class,
    owl_datarange, owl_datatypeproperty, owl_deprecatedclass, owl_deprecatedproperty,
    owl_functionalproperty,
    owl_inversefunctionalproperty, owl_irreflexiveproperty,
    owl_namedindividual, owl_negativepropertyassertion, owl_nothing,
    owl_objectproperty, owl_ontology, owl_ontologyproperty,
    owl_reflexiveproperty, owl_restriction,
    owl_symmetricproperty,
    owl_thing, owl_transitiveproperty,

    // prism controlled vocabulary
    pcv_descriptor,

    // poetry
    poetry_dialect, poetry_form, poetry_poem, poetry_period, poetry_stanza,

    // faux prism container
    prism_thing,

    // provincial
    prov_activity, prov_activityinfluence, prov_agent, prov_agentinfluence, prov_association, prov_attribution,
    prov_bundle,
    prov_collection, prov_communication,
    prov_delegation, prov_derivation,
    prov_emptycollection, prov_end, prov_entity, prov_entityinfluence,
    prov_generation,
    prov_influence, prov_instantaneousevent, prov_invalidation,
    prov_location,
    prov_organisation,
    prov_person, prov_plan, prov_primarysource,
    prov_quotation,
    prov_revision, prov_role,
    prov_softwareagent, prov_start,
    prov_usage,

    // ptr_content
    ptr_content, ptr_contentasbase64, ptr_contentastext, ptr_contentasxml,
    ptr_doctypedecl,

    // data cube
    qb_attachable, qb_attributeproperty,
    qb_codedproperty, qb_codelist, qb_componentproperty, qb_componentset, qb_componentspecification,
    qb_datastructuredefinition, qb_dimensionproperty, qb_dataset,
    qb_hierarchicalcodelist,
    qb_measureproperty,
    qb_observation, qb_observationgroup,
    qb_slice, qb_slicekey,

    // RDF
    rdf_alt, rdf_bag, rdf_compoundliteral, rdf_html, rdf_json, rdf_langstring, rdf_list, rdf_plainliteral, rdf_property, rdf_seq, rdf_statement, rdf_xmlliteral,

    // RDFg
    rdfg_graph,

    // RDFs
    rdfs_class, rdfs_container, rdfs_containermembershipproperty, rdfs_datatype, rdfs_literal, rdfs_resource,

    // Review Vocabulary
    rev_comment, rev_feedback, rev_review,

    // rif, so far as I can tell despite the missing turtle
    rif_iri, rif_local,

    // rdb to rdf
    rr_basetableorview, rr_blanknode,
    rr_defaultgraph,
    rr_graphmap,
    rr_iri,
    rr_join,
    rr_literal, rr_logicaltable,
    rr_objectmap,
    rr_predicatemap, rr_predicateobjectmap,
    rr_refobjectmap, rr_r2rmlview,
    rr_sql2008, rr_subjectmap,
    rr_triplesmap, rr_termmap,

    //schema.org
    sch_3dmodel,

    sch_abdomen, sch_aboutpage, sch_acceptaction, sch_accommodation, sch_accountingservice, sch_achieveaction, sch_action, sch_actionaccessspecification, sch_actionstatustype, sch_activationfee,
    sch_activateaction, sch_activeactionstatus, sch_activenotrecruiting, sch_addaction, sch_administrativearea, sch_adultentertainment, sch_adultorientatedenumeration, sch_advertisercontentarticle, sch_aerobicactivity, sch_aggregateoffer,
    sch_aggregaterating, sch_agreeaction, sch_airline, sch_airport, sch_albumrelease, sch_alcoholconsideration, sch_alignmentobject, sch_allergieshealthaspect, sch_allocateaction, sch_allwheeldriveconfiguration, sch_ampstory,
    sch_amradiochannel, sch_amusementpark, sch_anaerobicactivity, sch_anaesthesia, sch_analysisnewsarticle, sch_anatomicalstructure, sch_anatomicalsystem, sch_androidplatform, sch_animalshelter, sch_answer, sch_apartment,
    sch_apartmentcomplex, sch_apireference, sch_appearance, sch_appendaction, sch_applyaction, sch_approvedindication, sch_aquarium, sch_archivecomponent, sch_archiveorganisation, sch_arriveaction,
    sch_artery, sch_artgallery, sch_article, sch_askaction, sch_askpublicnewsarticle, sch_assessaction, sch_assignaction, sch_atlas, sch_attorney, sch_audience, sch_audiobook, sch_audiobookformat,
    sch_audioobject, sch_audioobjectsnapshot, sch_authenticcontent, sch_authoriseaction, sch_authoritativelegalvalue, sch_autobodyshop, sch_autodealer, sch_automatedteller, sch_automotivebusiness, sch_carpartsshop,
    sch_autorental, sch_autorepair, sch_autowash,

    sch_backgroundnewsarticle, sch_backorder, sch_bacteria, sch_bakery, sch_balance, sch_bankaccount, sch_bankorcreditunion, sch_barcode, sch_barorpub, sch_basicincome, sch_beach, sch_beautysalon,
    sch_bedandbreakfast, sch_beddetails, sch_bedtype, sch_befriendaction, sch_benefitshealthaspect, sch_bikeshop, sch_biochementity, sch_blog, sch_blogposting, sch_bloodtest, sch_boardingpolicytype, sch_boatreservation,
    sch_boatterminal, sch_boattrip, sch_bodymeasurementarm, sch_bodymeasurementbust, sch_bodymeasurementchest, sch_bodymeasurementfoot, sch_bodymeasurementhand, sch_bodymeasurementhead,
    sch_bodymeasurementheight, sch_bodymeasurementhips, sch_bodymeasurementinsideleg, sch_bodymeasurementneck, sch_bodymeasurementtypeenumeration, sch_bodymeasurementunderbust, sch_bodymeasurementwaist,
    sch_bodymeasurementweight, sch_bodyofwater, sch_bone, sch_book, sch_bookformattype, sch_bookmarkaction, sch_bookseries, sch_bookshop, sch_boolean, sch_borrowaction, sch_bowlingalley,
    sch_brainstructure, sch_brand, sch_breadcrumblist, sch_brewery, sch_bridge, sch_broadcastchannel, sch_broadcastevent, sch_broadcastfrequencyspecification, sch_broadcastrelease, sch_broadcastservice,
    sch_brokerageaccount, sch_buddhisttemple, sch_businessaudience, sch_businessentitytype, sch_businessevent, sch_businessfunction, sch_businesssupport, sch_busorcoach, sch_busreservation,
    sch_busstation, sch_busstop, sch_bustrip, sch_buyaction,

    sch_cableorsatelliteservice, sch_cafeorcoffeeshop, sch_campground, sch_campingpitch, sch_canal, sch_cancelaction, sch_car, sch_cardiovascular, sch_cardiovascularexam, sch_carusagetype, sch_caseseries,
    sch_casino, sch_cassetteformat, sch_categorycode, sch_categorycodeset, sch_catholicchurch, sch_causeshealthaspect, sch_cdcpmdrecord, sch_cdformat, sch_cemetery,
    sch_certification, sch_certificationactive, sch_certificationinactive, sch_certificationstatusenumeration, sch_chapter,
    sch_charitableincorporatedorganization, sch_checkaction, sch_checkinaction, sch_checkoutaction, sch_checkoutpage, sch_chemicalsubstance, sch_childcare, sch_childrensevent, sch_chooseaction, sch_church, sch_city, sch_townhall,
    sch_civicstructure, sch_claim, sch_claimreview, sch_class, sch_cleaningfee, sch_clinician, sch_clip, sch_clothesshop, sch_code, sch_cohortstudy, sch_collection, sch_collectionpage,
    sch_collegeoruniversity, sch_comedyclub, sch_comedyevent, sch_comiccoverart, sch_comicissue, sch_comicseries, sch_comicstory, sch_comment, sch_commentaction, sch_commentpermission,
    sch_communicateaction, sch_communityhealth, sch_compilationalbum, sch_completed, sch_completedactionstatus, sch_completedatafeed, sch_compoundpricespecification, sch_computerlanguage, sch_computershop,
    sch_confirmaction, sch_consortium, sch_constraintnode, sch_consumeaction, sch_contactpage, sch_contactpoint, sch_contactpointoption, sch_contagiousnesshealthaspect, sch_continent, sch_controlaction, sch_convenienceshop,
    sch_conversation, sch_cookaction, sch_coop, sch_corporation, sch_correctioncomment, sch_country, sch_course, sch_courseinstance, sch_courthouse, sch_coverart, sch_covidtestingfacility, sch_createaction,
    sch_creativework, sch_creativeworkseason, sch_creativeworkseries, sch_creditcard, sch_crematorium, sch_criticreview, sch_crosssectional, sch_cssselectortype, sch_ct, sch_currencyconversionservice,

    sch_damagedcondition, sch_danceevent, sch_dancegroup, sch_dangerousgoodconsideration, sch_datacatalogue, sch_datadownload, sch_datafeed, sch_datafeeditem, sch_datatype, sch_dataset, sch_date, sch_datedmoneyspecification, sch_datetime,
    sch_dayofweek, sch_dayspa, sch_ddxelement, sch_deactivateaction, sch_decontextualisedcontent, sch_defenceestablishment, sch_definedregion, sch_definedterm, sch_definedtermset, sch_definitivelegalvalue,
    sch_deleteaction, sch_deliverychargespecification, sch_deliveryevent, sch_deliverymethod, sch_deliverytimesettings, sch_demand, sch_demoalbum, sch_demogameavailability, sch_dentist, sch_dentistry, sch_departaction,
    sch_departmentstore, sch_depositaccount, sch_dermatology, sch_desktopwebplatform, sch_diabeticdiet, sch_diagnostic, sch_diagnosticlab, sch_diagnosticprocedure, sch_diet, sch_dietarysupplement, sch_dietnutrition,
    sch_digitalaudiotapeformat, sch_digitaldocument, sch_digitaldocumentpermission, sch_digitaldocumentpermissiontype, sch_digitalformat, sch_digitalplatformenumeration, sch_disabilitysupport, sch_disagreeaction, sch_discontinued,
    sch_discoveraction, sch_discussionforumposting, sch_dislikeaction, sch_distance, sch_distancefee, sch_distillery, sch_djmixalbum, sch_donateaction, sch_doseschedule, sch_doubleblindedtrial,
    sch_downloadaction, sch_downpayment, sch_drawaction, sch_drawing, sch_drinkaction, sch_drivewheelconfigurationvalue, sch_drivingschoolvehicleusage, sch_drug, sch_drugclass, sch_drugcost,
    sch_drugcostcategory, sch_druglegalstatus, sch_drugpregnancycategory, sch_drugprescriptionstatus, sch_drugstrength, sch_drycleaningorlaundry, sch_duration, sch_dvdformat,
    sch_dystopianhealthinsuranceplan, sch_dystopianhealthplancostsharingspecification, sch_dystopianhealthplanformulary, sch_dystopianhealthplannetwork,

    sch_ear, sch_eataction, sch_ebook, sch_editedorcroppedcontent, sch_educationaudience, sch_educationoccupationcredential, sch_educationoccupationprogramme, sch_educationorganisation,
    sch_educationevent, sch_effectivenesshealthaspect, sch_electrician, sch_electronicsshop, sch_elementaryschool, sch_emailmessage, sch_embassy, sch_emergency, sch_emergencyservice, sch_employeerole,
    sch_employeraggregaterating, sch_employerreview, sch_employmentagency, sch_endocrine, sch_endorseaction, sch_endorsementrating, sch_energy, sch_energyconsumptiondetails,
    sch_energyefficiencyenumeration, sch_energystarcertified, sch_enginespecification, sch_enrollingbyinvitation, sch_entertainmentbusiness, sch_entrypoint, sch_enumeration, sch_traditionalchinese,
    sch_episode, sch_eprelease, sch_euenergyefficiencycategorya, sch_euenergyefficiencycategorya1plus, sch_euenergyefficiencycategorya2plus, sch_euenergyefficiencycategorya3plus,
    sch_euenergyefficiencycategoryb, sch_euenergyefficiencycategoryc, sch_euenergyefficiencycategoryd, sch_euenergyefficiencycategorye, sch_euenergyefficiencycategoryf, sch_euenergyefficiencycategoryg,
    sch_euenergyefficiencyenumeration, sch_event, sch_eventattendancemodeenumeration, sch_eventcancelled, sch_eventmovedonline, sch_eventpostponed, sch_eventrescheduled, sch_eventreservation,
    sch_eventscheduled, sch_eventseries, sch_eventstatustype, sch_eventvenue, sch_evidencelevela, sch_evidencelevelb, sch_evidencelevelc, sch_examplemeasurementmethodenum, sch_exchangeratespecification,
    sch_exchangerefund, sch_exerciseaction, sch_exercisegym, sch_exerciseplan, sch_exhibitionevent, sch_eye,

    sch_failedactionstatus, sch_false, sch_faqpage, sch_fastfoodrestaurant, sch_fdacategorya, sch_fdacategoryb, sch_fdacategoryc, sch_fdacategoryd, sch_fdacategoryx, sch_fdanotevaluated, sch_female,
    sch_festival, sch_filmaction, sch_financialproduct, sch_financialservice, sch_findaction, sch_firestation, sch_flexibility, sch_flight, sch_flightreservation, sch_float, sch_floorplan, sch_florist,
    sch_fmradiochannel, sch_followaction, sch_foodestablishment, sch_foodestablishmentreservation, sch_foodevent, sch_foodservice, sch_fourwheeldriveconfiguration, sch_freereturn, sch_friday,
    sch_frontwheeldriveconfiguration, sch_fullrefund, sch_fullgameavailability, sch_fundingagency, sch_fundingscheme, sch_fungus, sch_furnitureshop,

    sch_game, sch_gameavailabilityenumeration, sch_gameplaymode, sch_gameserver, sch_gameserverstatus, sch_gardencentre, sch_petrolstation, sch_gastroenterologic, sch_gatedresidencecommunity, sch_gendertype, sch_generalcontractor,
    sch_gene, sch_genericwebplatform, sch_genetic, sch_genitourinary, sch_geocircle, sch_geocoordinates, sch_geoshape, sch_geospatialgeometry, sch_geriatric, sch_gettingaccesshealthaspect, sch_giveaction, sch_glutenfreediet,
    sch_golfcourse, sch_governmentbenefitstype, sch_governmentbuilding, sch_governmentoffice, sch_governmentorganisation, sch_governmentpermit, sch_governmentservice, sch_grant, sch_graphicnovel,
    sch_grocers, sch_groupboardingpolicy, sch_guide, sch_gynaecologic,

    sch_hackathon, sch_haematologic, sch_hairsalon, sch_halaldiet, sch_hardcover, sch_hardwareshop, sch_chiropractic, sch_head, sch_healthandbeautybusiness, sch_healthaspectenumeration, sch_healthcare,
    sch_healthcareconsideration, sch_healthclub, sch_healthtopiccontent, sch_hearingimpairedsupported, sch_highschool, sch_hindudiet, sch_hindutemple, sch_hobbyshop, sch_homeandconstructionbusiness, sch_householdgoodsshop, sch_hospital,
    sch_hostel, sch_hotel, sch_hotelroom, sch_house, sch_housepainter, sch_howitworkshealthaspect, sch_howorwherehealthaspect, sch_howto, sch_howtodirection, sch_howtoitem, sch_howtosection, sch_howtostep,
    sch_howtosupply, sch_howtotip, sch_howtotool, sch_hvacbusiness, sch_hypertoc, sch_hypertocentry,

    sch_icecreamshop, sch_ignoreaction, sch_imagegallery, sch_imageobject, sch_imageobjectsnapshot, sch_imagingtest, sch_individualphysician, sch_individualproduct, sch_infectious, sch_infectiousagentclass, sch_infectiousdisease, sch_inforce,
    sch_informaction, sch_ingredientshealthaspect, sch_insertaction, sch_installaction, sch_installment, sch_instock, sch_instoreonly, sch_insuranceagency, sch_intangible, sch_integer, sch_interactaction,
    sch_interactioncounter, sch_internationaltrial, sch_internetcafe, sch_investmentfund, sch_investmentordeposit, sch_inviteaction, sch_invoice, sch_invoiceprice, sch_iosplatform, sch_iptcdigitalsourceenumeration,
    sch_iptcalgorithmicmediadigitalsource, sch_iptcalgorithmicallyenhanceddigitalsource, sch_iptccompositecapturedigitalsource, sch_iptccompositesyntheticdigitalsource,
    sch_iptccompositewithtrainedalgorithmicmediadigitalsource, sch_iptcdatadrivenmediadigitalsource, sch_iptcdigitalartdigitalsource, sch_iptcdigitalcapturedigitalsource,
    sch_iptcminorhumaneditsdigitalsource, sch_iptcnegativefilmdigitalsource, sch_iptcpositivefilmdigitalsource, sch_iptcprintdigitalsource,
    sch_iptctrainedalgorithmicmediadigitalsource, sch_iptcvirtualrecordingdigitalsource, sch_itemavailability, sch_itemlist,
    sch_itemlistorderascending, sch_itemlistorderdescending, sch_itemlistordertype, sch_itemlistunordered, sch_itempage,

    sch_jewellers, sch_jobposting, sch_joinaction, sch_joint,

    sch_keepproduct, sch_kosherdiet,

    sch_laboratoryscience, sch_lakebodyofwater, sch_landform, sch_landmarksorhistoricalbuildings, sch_language, sch_laserdiscformat, sch_learningresource, sch_leaveaction, sch_lefthanddriving, sch_legalforcestatus,
    sch_legalservice, sch_legalvaluelevel, sch_legislation, sch_legislationobject, sch_legislativebuilding, sch_leisuretimeactivity, sch_lendaction, sch_library, sch_librarysystem, sch_lifestylemodification, sch_ligament,
    sch_likeaction, sch_limitedavailability, sch_limitedbyguaranteecharity, sch_linkrole, sch_offlicence, sch_listenaction, sch_listitem, sch_listprice, sch_literaryevent, sch_livealbum, sch_liveblogposting,
    sch_livingwithhealthaspect, sch_loanorcredit, sch_localbusiness, sch_locationfeaturespecification, sch_lockerdelivery, sch_locksmith, sch_lodgingbusiness, sch_lodgingreservation, sch_longitudinal, sch_loseaction,
    sch_lowcaloriediet, sch_lowfatdiet, sch_lowlactosediet, sch_lowsaltdiet, sch_lung, sch_lymphaticvessel,

    sch_homeopathic, sch_male, sch_manuscript, sch_map, sch_mapcategorytype, sch_marryaction, sch_mass, sch_mathsolver, sch_maximumdoseschedule, sch_maytreathealthaspect, sch_measurementmethodenum, sch_measurementtypeenumeration, sch_mediagallery,
    sch_mediamanipulationratingenumeration, sch_mediaobject, sch_mediareview, sch_mediareviewitem, sch_mediasubscription, sch_medicalaudience, sch_medicalaudiencetype, sch_medicalbusiness, sch_medicalcause, sch_medicalclinic, sch_medicalcode,
    sch_medicalcondition, sch_medicalconditionstage, sch_medicalcontraindication, sch_medicaldevice, sch_medicaldevicepurpose, sch_medicalentity, sch_medicalenumeration, sch_medicalevidencelevel, sch_medicalguideline,
    sch_medicalguidelinecontraindication, sch_medicalguidelinerecommendation, sch_medicalimagingtechnique, sch_medicalindication, sch_medicalintangible, sch_medicalobservationalstudy, sch_medicalobservationalstudydesign,
    sch_medicalorganisation, sch_medicalprocedure, sch_medicalproceduretype, sch_medicalresearcher, sch_medicalriskcalculator, sch_medicalriskestimator, sch_medicalriskfactor, sch_medicalriskscore, sch_medicalscholarlyarticle,
    sch_medicalsign, sch_medicalsignorsymptom, sch_medicalspeciality, sch_medicalstudy, sch_medicalstudystatus, sch_medicalsymptom, sch_medicaltest, sch_medicaltestpanel, sch_medicaltherapy, sch_medicaltrial,
    sch_medicaltrialdesign, sch_medicalwebpage, sch_medicinesystem, sch_meetingroom, sch_tailors, sch_menu, sch_menuitem, sch_menusection, sch_merchantreturnenumeration, sch_merchantreturnfinitereturnwindow,
    sch_merchantreturnnotpermitted, sch_merchantreturnpolicy, sch_merchantreturnpolicyseasonaloverride, sch_merchantreturnunlimitedwindow, sch_merchantreturnunspecified, sch_message, sch_middleschool, sch_midwifery, sch_minimumadvertisedprice,
    sch_misconceptionshealthaspect, sch_missingcontext, sch_mixedeventattendancemode, sch_mixtapealbum, sch_molecularentity, sch_mobileapplication, sch_mobilephoneshop, sch_mobilewebplatform, sch_monday, sch_monetaryamount, sch_monetaryamountdistribution,
    sch_monetarygrant, sch_moneytransfer, sch_mortgageloan, sch_mosque, sch_motel, sch_motorcycle, sch_motorcycledealer, sch_msrp, sch_motorcyclerepair, sch_motorisedbicycle, sch_mountain, sch_moveaction, sch_movie,
    sch_movieclip, sch_filmhireshop, sch_movieseries, sch_movietheatre, sch_removers, sch_mri, sch_multicellularparasite, sch_multicentretrial, sch_multiplayer, sch_muscle, sch_musculoskeletal, sch_musculoskeletalexam,
    sch_museum, sch_musical_bum, sch_musicalbumproductiontype, sch_musicalbumreleasetype, sch_musiccomposition, sch_musicevent, sch_musicgroup, sch_musicplaylist, sch_musicrecording, sch_musicrelease, sch_musicreleaseformattype,
    sch_musicshop, sch_musicvenue, sch_musicvideoobject,

    sch_nailsalon, sch_narcoticconsideration, sch_neck, sch_nerve, sch_neuro, sch_neurologic, sch_newcondition, sch_newsarticle, sch_newsmediaorganisation, sch_newspaper, sch_ngo, sch_nightclub, sch_nlnonprofittype, sch_noninvasiveprocedure,
    sch_nonprofit501a, sch_nonprofit501c1, sch_nonprofit501c10, sch_nonprofit501c11, sch_nonprofit501c12, sch_nonprofit501c13, sch_nonprofit501c14, sch_nonprofit501c15, sch_nonprofit501c16, sch_nonprofit501c17,
    sch_nonprofit501c18, sch_nonprofit501c19, sch_nonprofit501c2, sch_nonprofit501c20, sch_nonprofit501c21, sch_nonprofit501c22, sch_nonprofit501c23, sch_nonprofit501c24, sch_nonprofit501c25, sch_nonprofit501c26,
    sch_nonprofit501c27, sch_nonprofit501c28, sch_nonprofit501c3, sch_nonprofit501c4, sch_nonprofit501c5, sch_nonprofit501c6, sch_nonprofit501c7, sch_nonprofit501c8, sch_nonprofit501c9, sch_nonprofit501d, sch_nonprofit501e,
    sch_nonprofit501f, sch_nonprofit501k, sch_nonprofit501n, sch_nonprofit501q, sch_nonprofit527, sch_nonprofitanbi, sch_nonprofitsbbi, sch_nonprofittype, sch_nose, sch_notary, sch_notedigitaldocument, sch_notinforce,
    sch_notyetrecruiting, sch_number, sch_nursing, sch_nutritioninformation,

    sch_observation, sch_observational, sch_obstetric, sch_occupation, sch_occupationalactivity, sch_occupationalexperiencerequirements, sch_occupationaltherapy, sch_oceanbodyofwater, sch_offer, sch_offercatalogue,
    sch_offerforlease, sch_offerforpurchase, sch_offeritemcondition, sch_offershippingdetails, sch_officeshop, sch_officiallegalvalue, sch_offlineeventattendancemode, sch_offlinepermanently, sch_offlinetemporarily,
    sch_oncologic, sch_ondemandevent, sch_onetimepayments, sch_online, sch_onlinebusiness, sch_onlineeventattendancemode, sch_onlinefull, sch_onlineonly, sch_onlinestore, sch_onsitepickup, sch_openinghoursspecification, sch_opentrial, sch_opinionnewsarticle,
    sch_optician, sch_optometric, sch_order, sch_orderaction, sch_ordercancelled, sch_orderdelivered, sch_orderintransit, sch_orderitem, sch_orderpaymentdue, sch_orderpickupavailable, sch_orderproblem, sch_orderprocessing,
    sch_orderreturned, sch_orderstatus, sch_organisation, sch_organisationrole, sch_organiseaction, sch_originalmediacontent, sch_originalshippingfees, sch_osteopathic, sch_otc, sch_otolaryngologic, sch_outletstore,
    sch_outofstock, sch_overviewhealthaspect, sch_ownershipinfo,

    sch_paediatric, sch_paidleave, sch_paintaction, sch_painting, sch_palliativeprocedure, sch_paperback, sch_parceldelivery, sch_parcelservice, sch_parentalsupport, sch_parentaudience, sch_park, sch_parkingfacility, sch_parkingmap,
    sch_partiallyinforce, sch_pathology, sch_pathologytest, sch_patient, sch_patientexperiencehealthaspect, sch_pawnshop, sch_payaction, sch_paymentautomaticallyapplied, sch_paymentcard, sch_paymentchargespecification,
    sch_paymentcomplete, sch_paymentdeclined, sch_paymentdue, sch_paymentmethod, sch_paymentpastdue, sch_paymentservice, sch_paymentstatustype, sch_peopleaudience, sch_percutaneousprocedure, sch_performaction, sch_performancerole,
    sch_performingartstheatre, sch_performinggroup, sch_periodical, sch_permit, sch_person, sch_pet, sch_petshop, sch_pharmacy, sch_pharmacyspeciality, sch_photograph, sch_photographaction, sch_physicalactivity,
    sch_physicalactivitycategory, sch_physicalexam, sch_physicaltherapy, sch_physician, sch_physiciansoffice, sch_physiotherapy, sch_ayurvedic, sch_place, sch_placebocontrolledtrial, sch_placeofworship, sch_planaction, sch_plasticsurgery, sch_play,
    sch_playaction, sch_playgameaction, sch_playground, sch_plumber, sch_podcastepisode, sch_podcastseason, sch_podcastseries, sch_podiatric, sch_policestation, sch_politicalparty, sch_pond, sch_postaladdress,
    sch_postalcoderangespecification, sch_poster, sch_postoffice, sch_potentialactionstatus, sch_pregnancyhealthaspect, sch_preorder, sch_preorderaction, sch_prependaction, sch_presale, sch_preschool, sch_prescriptiononly,
    sch_presentationdigitaldocument, sch_preventionhealthaspect, sch_preventionindication, sch_pricecomponenttypeenumeration, sch_pricespecification, sch_pricetypeenumeration, sch_primarycare, sch_prion, sch_product,
    sch_productcollection, sch_productgroup, sch_productmodel, sch_productreturnenumeration, sch_productreturnfinitereturnwindow, sch_productreturnnotpermitted, sch_productreturnpolicy, sch_productreturnunlimitedwindow,
    sch_productreturnunspecified, sch_professionalservice, sch_profilepage, sch_prognosishealthaspect, sch_programmemembership, sch_project, sch_pronounceabletext, sch_property, sch_propertyvalue, sch_propertyvaluespecification,
    sch_protein, sch_protozoa, sch_psychiatric, sch_psychologicaltreatment, sch_publicationevent, sch_publicationissue, sch_publicationvolume, sch_publichealth, sch_publicholidays, sch_publicswimmingpool, sch_publictoilet,
    sch_pulmonary,

    sch_qapage, sch_qualitativevalue, sch_quantitativevalue, sch_quantitativevaluedistribution, sch_quantity, sch_question, sch_quiz, sch_quotation, sch_quoteaction,

    sch_radiationtherapy, sch_radiobroadcastservice, sch_radiochannel, sch_radioclip, sch_radioepisode, sch_radiography, sch_radioseason, sch_radioseries, sch_radiostation, sch_randomisedtrial, sch_rating, sch_reactaction, sch_readaction,
    sch_readpermission, sch_realestateagent, sch_realestatelisting, sch_rearwheeldriveconfiguration, sch_receiveaction, sch_recipe, sch_recommendation, sch_recommendeddoseschedule, sch_recruiting, sch_recyclingcentre, sch_reducedrelevanceforchildrenconsideration,
    sch_refundtypeenumeration, sch_refurbishedcondition, sch_registeraction, sch_registry, sch_reimbursementcap, sch_rejectaction, sch_relatedtopicshealthaspect, sch_remixalbum, sch_renal, sch_rentaction, sch_rentalcarreservation,
    sch_rentalvehicleusage, sch_repaymentspecification, sch_replaceaction, sch_replyaction, sch_report, sch_reportagenewsarticle, sch_reporteddoseschedule, sch_researchproject, sch_reservation, sch_reservationcancelled,
    sch_reservationconfirmed, sch_reservationhold, sch_reservationpackage, sch_reservationpending, sch_reservationstatustype, sch_reserveaction, sch_reservoir, sch_residence, sch_resort, sch_respiratorytherapy, sch_restaurant,
    sch_restockingfees, sch_restricteddiet, sch_resultsavailable, sch_resultsnotavailable, sch_resumeaction, sch_retail, sch_returnaction, sch_returnatkiosk, sch_returnbymail, sch_returnfeescustomerresponsibility, sch_returnfeesenumeration,
    sch_returninstore, sch_returnlabelcustomerresponsibility, sch_returnlabeldownloadandprint, sch_returnlabelinbox, sch_returnlabelsourceenumeration, sch_returnmethodenumeration, sch_returnshippingfees, sch_review, sch_reviewaction,
    sch_reviewnewsarticle, sch_rheumatologic, sch_righthanddriving, sch_risksorcomplicationshealthaspect, sch_riverbodyofwater, sch_role, sch_roofingcontractor, sch_room, sch_rsvpaction, sch_rsvpresponsemaybe, sch_rsvpresponseno,
    sch_rsvpresponsetype, sch_rsvpresponseyes, sch_rvpark,

    sch_safetyhealthaspect, sch_saleevent, sch_saleprice, sch_satireorparodycontent, sch_satiricalarticle, sch_saturday, sch_schedule, sch_scheduleaction, sch_scholarlyarticle, sch_school, sch_schooldistrict,
    sch_screeningevent, sch_screeninghealthaspect, sch_sculpture, sch_seabodyofwater, sch_searchaction, sch_searchrescueorganisation, sch_searchresultspage, sch_season, sch_seat, sch_seatingmap, sch_seedoctorhealthaspect, sch_seektoaction,
    sch_selfcarehealthaspect, sch_selfstorage, sch_sellaction, sch_sendaction, sch_series, sch_service, sch_servicechannel, sch_sexualcontentconsideration, sch_shareaction, sch_sheetmusic, sch_shippingdeliverytime, sch_shippingratesettings, sch_shoeshop,
    sch_shoppingcentre, sch_shortstory, sch_sideeffectshealthaspect, sch_singleblindedtrial, sch_singlecentretrial, sch_singlefamilyresidence, sch_singleplayer, sch_singlerelease, sch_sitenavigationelement,
    sch_sizegroupenumeration, sch_sizespecification, sch_sizesystemenumeration, sch_sizesystemimperial, sch_sizesystemmetric, sch_skin, sch_skiresort, sch_socialevent, sch_socialmediaposting, sch_softwareapplication,
    sch_softwaresourcecode, sch_soldout, sch_solvemathaction, sch_someproducts, sch_soundtrackalbum, sch_speakablespecification, sch_specialannouncement, sch_speciality, sch_speechpathology, sch_spokenwordalbum,
    sch_sportsshop, sch_sportsactivitylocation, sch_sportsclub, sch_srp, sch_sportsevent, sch_sportsorganisation, sch_sportsteam, sch_spreadsheetdigitaldocument, sch_stadiumorarena, sch_stagedcontent,
    sch_stageshealthaspect, sch_state, sch_statement, sch_statisticalpopulation, sch_statisticalvariable, sch_statusenumeration, sch_steeringpositionvalue, sch_store, sch_storecreditrefund, sch_strengthtraining, sch_structuredvalue, sch_studioalbum,
    sch_stupidtype, sch_subscribeaction, sch_subscription, sch_substance, sch_metrostation, sch_suite, sch_sunday, sch_superficialanatomy, sch_surgical, sch_surgicalprocedure, sch_suspendaction, sch_suspended,
    sch_syllabus, sch_symptomshealthaspect, sch_synagogue,

    sch_tobacconicotineconsideration, sch_table, sch_takeaction, sch_tattooparlour, sch_taxi, sch_taxireservation, sch_taxiservice, sch_taxistand, sch_taxivehicleusage, sch_taxon, sch_techarticle, sch_televisionchannel, sch_televisionstation, sch_tenniscomplex,
    sch_terminated, sch_text, sch_textdigitaldocument, sch_textobject, sch_theatreevent, sch_theatregroup, sch_therapeutic, sch_therapeuticprocedure, sch_thesis, sch_thing, sch_throat, sch_thursday, sch_ticket, sch_tieaction, sch_time,
    sch_tipaction, sch_tollfree, sch_touristattraction, sch_touristdestination, sch_touristinformationcentre, sch_touristtrip, sch_toxicologic, sch_toyshop, sch_trackaction, sch_tradeaction, sch_trainreservation,
    sch_trainstation, sch_traintrip, sch_transferaction, sch_transformedcontent, sch_transitmap, sch_travelaction, sch_travelagency, sch_treatmentindication, sch_treatmentshealthaspect, sch_trip, sch_tripleblindedtrial,
    sch_true, sch_tuesday, sch_tvclip, sch_tvepisode, sch_tvseason, sch_tvseries, sch_typeandquantitynode, sch_typeshealthaspect, sch_tyreshop,

    sch_uknonprofittype, sch_uktrust, sch_ultrasound, sch_unemploymentsupport, sch_unclassifiedadultconsideration, sch_unincorporatedassociationcharity, sch_unitpricespecification, sch_unofficiallegalvalue, sch_unregisteraction, sch_updateaction, sch_url,
    sch_urologic, sch_usageorschedulehealthaspect, sch_useaction, sch_usedcondition, sch_userblocks, sch_usercheckins, sch_usercomments, sch_userdownloads, sch_userinteraction, sch_userlikes, sch_userpagevisits, sch_userplays,
    sch_userplusones, sch_userreview, sch_usertweets, sch_usnonprofittype,

    sch_vacationrental, sch_vegandiet, sch_vegetariandiet, sch_vehicle, sch_vein, sch_venuemap, sch_vessel, sch_veterinarycare, sch_videogallery, sch_videogame, sch_videogameclip, sch_videogameseries, sch_videoobject,
    sch_videoobjectsnapshot, sch_viewaction, sch_vinylformat, sch_violenceconsideration, sch_virtuallocation, sch_virus, sch_visualartsevent, sch_visualartwork, sch_vitalsign, sch_volcano, sch_voteaction,

    sch_wantaction, sch_warrantypromise, sch_warrantyscope, sch_watchaction, sch_waterfall, sch_weaponconsideration, sch_wearablemeasurementtypeenumeration, sch_wearablemeasurementback, sch_wearablemeasurementchestorbust, sch_wearablemeasurementcollar,
    sch_wearablemeasurementcup, sch_wearablemeasurementheight, sch_wearablemeasurementhips, sch_wearablemeasurementinseam, sch_wearablemeasurementlength, sch_wearablemeasurementoutsideleg, sch_wearablemeasurementsleeve,
    sch_wearablemeasurementwaist, sch_wearablemeasurementwidth, sch_wearablesizegroupbig, sch_wearablesizegroupboys, sch_wearablesizegroupenumeration, sch_wearablesizegroupextrashort, sch_wearablesizegroupextratall,
    sch_wearablesizegroupgirls, sch_wearablesizegrouphusky, sch_wearablesizegroupinfants, sch_wearablesizegroupjuniors, sch_wearablesizegroupmaternity, sch_wearablesizegroupmens, sch_wearablesizegroupmisses,
    sch_wearablesizegrouppetite, sch_wearablesizegroupplus, sch_wearablesizegroupregular, sch_wearablesizegroupshort, sch_wearablesizegrouptall, sch_wearablesizegroupwomens, sch_wearablesizesystemau, sch_wearablesizesystembr,
    sch_wearablesizesystemcn, sch_wearablesizesystemcontinental, sch_wearablesizesystemde, sch_wearablesizesystemen13402, sch_wearablesizesystemenumeration, sch_wearablesizesystemeurope, sch_wearablesizesystemfr,
    sch_wearablesizesystemgs1, sch_wearablesizesystemit, sch_wearablesizesystemjp, sch_wearablesizesystemmx, sch_wearablesizesystemuk, sch_wearablesizesystemus, sch_wearaction, sch_webapi, sch_webapplication, sch_webcontent,
    sch_webpage, sch_webpageelement, sch_website, sch_wednesday, sch_westernconventional, sch_wholesale, sch_wholesalers, sch_winaction, sch_winery, sch_withdrawn, sch_workbasedprogramme, sch_workersunion, sch_wpadblock, sch_wpfooter, sch_wpheader,
    sch_wpsidebar, sch_writeaction, sch_writepermission,

    sch_xpathtype, sch_xray,

    sch_zoneboardingpolicy, sch_zoo,

    // sd
    sd_aggregate,
    sd_basicfederatedquery,
    sd_dataset, sd_dereferencesuris,
    sd_emptygraphs, sd_entailmentprofile, sd_entailmentregime,
    sd_feature, sd_function,
    sd_graph, sd_graphcollection,
    sd_language,
    sd_namedgraph,
    sd_requiresdataset,
    sd_service, sd_sparql10query, sd_sparql11query, sd_sparql11update,
    sd_uniondefaultgraph,

    // frost (sioc)
    sioc_community, sioc_container,
    sioc_forum,
    sioc_item,
    sioc_post,
    sioc_role,
    sioc_site, sioc_space,
    sioc_thread,
    sioc_user,
    sioc_usergroup,

    // skos
    skos_collection, skos_concept, skos_conceptscheme, skos_orderedcollection,

    // skosxl
    skosxl_label,

    // sosa
    sosa_actuation, sosa_actuator, sosa_actuatableproperty,
    sosa_featureofinterest,
    sosa_observableproperty, sosa_observation,
    sosa_platform, sosa_procedure,
    sosa_result,
    sosa_sample, sosa_sampler, sosa_sampling,
    sosa_sensor,

    // ssn
    ssn_deployment,
    ssn_input,
    ssn_output,
    ssn_property,
    ssn_stimulus, ssn_system,

    // time
    time_april, time_august,
    time_datetimedescription, time_datetimeinterval, time_dayofweek, time_december, time_duration, time_durationdescription,
    time_february,time_friday,
    time_generaldatetimedescription, time_generaldurationdescription,
    time_instant, time_interval,
    time_january, time_july, time_june,
    time_march, time_may, time_monday, time_monthofyear,
    time_november,
    time_october,
    time_position, time_properinterval, time_timezone,
    time_september,
    time_temporalduration, time_temporalentity, time_temporalposition, time_temporalunit, time_thursday, time_timeposition, time_trs, time_tuesday,
    time_saturday, time_sunday,
    time_unitday, time_unithour, time_unitminute, time_unitmonth, time_unitsecond, time_unitweek, time_unityear,
    time_wednesday,
    time_year,

    // data vocabulary
    v_breadcrumb,
    v_event,
    v_offer, v_offeraggregate, v_organisation,
    v_person, v_product,
    v_review, v_reviewaggregate,

    // vcard
    vcard_address, vcard_adrproperties, vcard_adrtypes,
    vcard_bbs,
    vcard_cacquaintance, vcard_cagent, vcard_car, vcard_cchild, vcard_ccolleague, vcard_ccontact, vcard_ccoresident, vcard_ccoworker, vcard_ccrush, vcard_cdate,
        vcard_cemergency, vcard_female, vcard_cfriend, vcard_cgender, vcard_cgroup, vcard_ckin, vcard_male, vcard_cme, vcard_cmet, vcard_cmuse, vcard_cneighbour,
        vcard_none, vcard_cother, vcard_cparent, vcard_csibling, vcard_cspouse, vcard_csweetheart, vcard_ctext, vcard_ctextphone, vcard_ctype, vcard_unknown,
    vcard_dom,
    vcard_email, vcard_emailtypes,
    vcard_fax,
    vcard_home,
    vcard_individual, vcard_internet, vcard_intl, vcard_isdn,
    vcard_label, vcard_location,
    vcard_mobile, vcard_modem, vcard_msg,
    vcard_name, vcard_nproperties,
    vcard_organisation, vcard_orgproperties,
    vcard_pager, vcard_parcel, vcard_pcs, vcard_postal, vcard_pref,
    vcard_relatedtype,
    vcard_tel, vcard_teltypes, vcard_telephonetype, vcard_tztypes,
    vcard_vcard, vcard_vcardtype, vcard_video, vcard_vkind, vcard_voice,
    vcard_work,
    vcard_x400,

    // void
    void_dataset, void_datasetdescription, void_linkset, void_technicalfeature,

    // wdr
    wdr_attributiontype, wdr_irisettype, wdr_querycontainstype,

    // wdrs
    wdrs_document, wdrs_processor,

    // Living Standard
    wwg_work,

    // XML Schema types
    xsd_anyatomictype, xsd_anysimpletype, xsd_anytype, xsd_anyuri,
    xsd_base64binary, xsd_boolean, xsd_byte,
    xsd_date, xsd_datetime, xsd_datetimeduration, xsd_datetimestamp, xsd_decimal, xsd_double, xsd_duration,
    xsd_entities, xsd_entity,
    xsd_float,
    xsd_gday, xsd_gmonth, xsd_gmonthday, xsd_gyear, xsd_gyearmonth,
    xsd_hexbinary,
    xsd_id, xsd_idref, xsd_idrefs, xsd_int, xsd_integer,
    xsd_language, xsd_long,
    xsd_name, xsd_ncname, xsd_negativeinteger, xsd_nmtoken, xsd_nmtokens, xsd_nonnegativeinteger, xsd_nonpositiveinteger, xsd_normalisedstring, xsd_notation,
    xsd_positiveinteger,
    xsd_qname,
    xsd_short, xsd_string,
    xsd_time, xsd_token,
    xsd_unsignedbyte, xsd_unsignedint, xsd_unsignedlong, xsd_unsignedshort,
    xsd_yearmonthduration,

    ont_illegal } e_ontology_type;

typedef enum
{   op_context,

    // adms
    admsp_identifier, admsp_included_asset, admsp_interoperability_level,
    admsp_last,
    admsp_next,
    admsp_prev,
    admsp_representation_technique,
    admsp_sample, admsp_ontology_agency, admsp_status, admsp_supported_schema,
    admsp_translation,
    admsp_version_notes,

    // activity streams etc.
    asp_accuracy, asp_actor, asp_altitude, asp_anyof, asp_attachment, asp_attachments, asp_attributedto, asp_audience, asp_author,
    asp_bcc, asp_bto,
    asp_cc, asp_closed, asp_content, asp_contentmap, asp_context, asp_current,
    asp_deleted, asp_describes, asp_displayname, asp_downstreamduplicates, asp_duration,
    asp_endtime,
    asp_first, asp_formertype,
    asp_generator,
    asp_height, asp_href, asp_hreflang,
    asp_icon, asp_id, asp_image, asp_inreplyto, asp_instrument, asp_items,
    asp_last, asp_latitude, asp_location, asp_longitude,
    asp_mediatype,
    asp_name, asp_namemap,
    asp_next,
    asp_object, asp_objecttype, asp_oneof, asp_ordereditems, asp_origin,
    asp_partof, asp_prev, asp_preview, asp_provider, asp_published,
    asp_radius, asp_rating, asp_rel, asp_relationship, asp_replies, asp_result,
    asp_startindex, asp_starttime, asp_subject, asp_summary, asp_summarymap,
    asp_tag, asp_tags, asp_target, asp_title, asp_to, asp_totalitems, asp_type,
    asp_units, asp_updated, asp_upstreamduplicates, asp_url,
    asp_verb,
    asp_width,

    // bfo
    bfo_bearer_of,
    bfo_concretises, bfo_concretises_always, bfo_concretises_sometimes, bfo_continuant_part_of, bfo_continuant_part_of_always, bfo_continuant_part_of_sometimes,
    bfo_disposition_of,
    bfo_environs, bfo_exists_at,
    bfo_first_instant_of, bfo_function_of,
    bfo_generically_depends_on, bfo_generically_depends_on_always, bfo_generically_depends_on_sometimes,
    bfo_has_continuant_part, bfo_has_continuant_part_always, bfo_has_continuant_part_sometimes, bfo_has_disposition, bfo_has_first_instant, bfo_has_function,
        bfo_has_history, bfo_has_last_instant, bfo_has_location, bfo_has_location_always, bfo_has_location_sometimes, bfo_has_material_basis,
        bfo_has_material_basis_always, bfo_has_material_basis_sometimes, bfo_has_member_part, bfo_has_member_part_always, bfo_has_member_part_sometimes,
        bfo_has_occurrent_part, bfo_has_participant, bfo_has_participant_always, bfo_has_participant_sometimes, bfo_has_proper_continuant_part,
        bfo_has_proper_continuant_part_always, bfo_has_proper_continuant_part_sometimes, bfo_has_proper_occurrent_part, bfo_has_proper_temporal_part,
        bfo_has_realisation, bfo_has_role, bfo_has_temporal_part, bfo_history_of,
    bfo_inheres_in, bfo_instance_of, bfo_is_carrier_of, bfo_is_carrier_of_always, bfo_is_carrier_of_sometimes, bfo_is_concretised_by, bfo_is_concretised_by_always,
        bfo_is_concretised_by_sometimes,
    bfo_last_instant_of, bfo_located_in, bfo_located_in_always, bfo_located_in_sometimes, bfo_location_of,
    bfo_material_basis_of, bfo_material_basis_of_always, bfo_material_basis_of_sometimes, bfo_material_part_of,
        bfo_member_part_of, bfo_member_part_of_always, bfo_member_part_of_sometimes,
    bfo_occupied_by, bfo_occupies_spatial_region, bfo_occupies_spatial_region_always, bfo_occupies_spatial_region_sometimes, bfo_occupies_spatiotemporal_region,
        bfo_occupies_temporal_region, bfo_occurrent_part_of, bfo_occurs_in,
    bfo_participates_in, bfo_participates_in_always, bfo_participates_in_sometimes, bfo_preceded_by, bfo_precedes, bfo_process_profile_of, bfo_proper_continuant_part_of,
        bfo_proper_continuant_part_of_always, bfo_proper_continuant_part_of_sometimes, bfo_proper_occurrent_part_of, bfo_proper_temporal_part_of,
    bfo_quality_of,
    bfo_realises, bfo_role_of,
    bfo_spatially_projects_onto, bfo_spatially_projects_onto_always, bfo_spatially_projects_onto_sometimes, bfo_specifically_depended_on_by, bfo_specifically_depends_on,
    bfo_temporal_part_of, bfo_temporally_projects_onto,

    // bibo
    bibo_abstract, bibo_affirmedby, bibo_annotates, bibo_argued, bibo_asin, bibo_authorlist,
    bibo_chapternumber, bibo_citedby, bibo_cites, bibo_coden, bibo_content, bibo_contributorlist, bibo_court,
    bibo_degree, bibo_direcor, bibo_distributor, bibo_doi,
    bibo_eanucc13, bibo_edition, bibo_editor, bibo_editorlist, bibo_eissn,
    bibo_gtin14,
    bibo_handle,
    bibo_identifier, bibo_interviewee, bibo_interviewer, bibo_isbn, bibo_isbn10, bibo_isbn13, bibo_issn, bibo_issuenumber, bibo_issuer,
    bibo_lccn, bibo_locator,
    bibo_number, bibo_numpages, bibo_numvolumes,
    bibo_oclcnum, bibo_organiser, bibo_owner,
    bibo_pageend, bibo_pages, bibo_pagestart, bibo_performer, bibo_pmid, bibo_prefixname, bibo_presentedat, bibo_presents, bibo_producer,
    bibo_recipient, bibo_reproducedin, bibo_reversedby, bibo_reviewof,
    bibo_section, bibo_shortdescription, bibo_shorttitle, bibo_sici, bibo_status, bibo_subsequentlegaldecision, bibo_suffixname,
    bibo_transcriptof, bibo_translationof, bibo_translator,
    bibo_upc, bibo_uri,
    bibo_volume,

    // biro
    biro_is_referenced_by, biro_references,

    // creative commons
    cc_attributionname, cc_attributionurl, cc_deprecatedon, cc_jurisdiction, cc_legalcode, cc_licence, cc_morepermissions, cc_permits, cc_prohibits, cc_requires,

    // cito
    cp_agrees_with, cp_cites, cp_cites_as_authority, cp_cites_as_data_source,
    cp_cites_as_evidence, cp_cites_as_metadata_document, cp_cites_as_potential_solution,
    cp_cites_as_recommended_reading, cp_cites_as_related, cp_cites_as_source_document,
    cp_cites_for_information, cp_compiles, cp_confirms, cp_contains_assertion_from, cp_corrects,
    cp_credits, cp_critiques, cp_derides, cp_describes, cp_disagrees_with, cp_discusses, cp_disputes,
    cp_documents, cp_extends, cp_gives_background_to, cp_gives_support_to,
    cp_has_citation_characterisation, cp_has_citation_creation_date, cp_has_citation_time_span,
    cp_has_cited_entity, cp_has_citing_entity, cp_has_coauthorship_citation_level, cp_has_reply_from,
    cp_includes_excerpt_from, cp_includes_quotation_from, cp_is_agreed_with_by,
    cp_is_cited_as_authority_by, cp_is_cited_as_data_source_by, cp_is_cited_as_evidence_by,
    cp_is_cited_as_metadata_document_by, cp_is_cited_as_potential_solution_by,
    cp_is_cited_as_recommended_reading_by, cp_is_cited_as_related_by,
    cp_is_cited_as_source_document_by, cp_is_cited_by, cp_is_cited_for_information_by,
    cp_is_compiled_by, cp_is_confirmed_by, cp_is_corrected_by, cp_is_credited_by, cp_is_critiqued_by,
    cp_is_derided_by, cp_is_described_by, cp_is_disagreed_with_by, cp_is_discussed_by,
    cp_is_disputed_by, cp_is_documented_by, cp_is_extended_by, cp_is_linked_to_by,
    cp_is_parodied_by, cp_is_plagiarized_by, cp_is_qualified_by, cp_is_refuted_by, cp_is_retracted_by,
    cp_is_reviewed_by, cp_is_ridiculed_by, cp_is_speculated_on_by, cp_is_supported_by,
    cp_is_updated_by, cp_likes, cp_links_to, cp_obtains_background_from, cp_obtains_support_from,
    cp_parodies, cp_plagiarises, cp_provides_assertion_for, cp_provides_conclusions_for,
    cp_provides_data_for, cp_provides_excerpt_for, cp_provides_method_for,
    cp_provides_quotation_for, cp_qualifies, cp_refutes, cp_replies_to, cp_retracts, cp_reviews,
    cp_ridicules, cp_shares_author_institution_with, cp_shares_author_with,
    cp_shares_funding_agency_with, cp_shares_journal_with, cp_shares_publication_venue_with,
    cp_speculates_on, cp_supports, cp_updates, cp_uses_conclusions_from, cp_uses_data_from,
    cp_uses_method_in,

    // content
    content_encoded, content_encoding, content_format, content_item, content_items, content_value,

    // camera raw
    crs2_autobightness, crs2_autocontrast, crs2_autoexposure, crs2_autoshadows,
    crs2_bluehue, crs2_bluesaturation, crs2_brightness,
    crs2_cameraprofile, crs2_chromaticaberrationb, crs2_chromaticaberrationr, crs2_colournoisereduction, crs2_contrast, crs2_cropangle,
        crs2_cropbottom, crs2_cropheight, crs2_cropleft, crs2_cropright, crs2_croptop, crs2_cropunits, crs2_cropwidth,
    crs2_exposure,
    crs2_greenhue, crs2_greensaturation,
    crs2_hascrop, crs2_hassettings,
    crs2_luminancesmoothing,
    crs2_rawfilename, crs2_redhue, crs2_redsaturation,
    crs2_saturation, crs2_shadows, crs2_shadowtint, crs2_sharpness,
    crs2_temperature, crs2_tint, crs2_tonecurve, crs2_tonecurvename,
    crs2_version, crs2_vignetteamount, crs2_vignettemidpoint,
    crs2_whitebalance,

    // common tag
    ctag_label, ctag_means, ctag_tagged, ctag_taggingdate,

    // contrary sausages vote wibble
    csvw_abouturl,
    csvw_base,
    csvw_column, csvw_columnreference, csvw_commentprefix,
    csvw_datatype, csvw_decimalchar, csvw_default, csvw_describes, csvw_delimiter, csvw_dialect, csvw_doublequote,
    csvw_encoding,
    csvw_foreignkey, csvw_format,
    csvw_groupchar,
    csvw_header, csvw_headerrowcount,
    csvw_lang, csvw_length, csvw_lineterminators,
    csvw_maxexclusive, csvw_maxinclusive, csvw_maxlength, csvw_minexclusive, csvw_mininclusive, csvw_minlength,
    csvw_name, csvw_note, csvw_null,
    csvw_ordered,
    csvw_pattern, csvw_primarykey, csvw_propertyurl,
    csvw_quotechar,
    csvw_reference, csvw_referencedrow, csvw_required, csvw_resource, csvw_row, csvw_rowtitle, csvw_rownum,
    csvw_scriptformat, csvw_schemareference, csvw_separator, csvw_skipblankrows, csvw_skipcolumns, csvw_skipinitialspace, csvw_skiprows, csvw_source, csvw_suppressoutput,
    csvw_table, csvw_tabledirection, csvw_tableschema, csvw_targetformat, csvw_transformations, csvw_textdirection, csvw_title, csvw_trim,
    csvw_url,
    csvw_valueurl, csvw_virtual,

    // data quality
    daq_computedon,
    daq_expecteddatatype,
    daq_hasdimension, daq_hasmetric, daq_hasobservation,
    daq_isestimate,
    daqp_metric,
    daq_requires,
    daq_value,

    // dublin core elements
    dc_contributor, dc_coverage, dc_creator, dc_date, dc_description, dc_format, dc_identifier, dc_language, dc_publisher, dc_relation, dc_rights, dc_source, dc_subject, dc_title, dc_type,

    // dublin core vocabulary description
    dcam_domainincludes, dcam_memberof, dcam_rangeincludes,

    // data catalogue
    dcat_accessurl, dcat_accessservice,
    dcat_beginning, dcat_bbox, dcat_bytesize,
    dcat_catalogue, dcat_centroid, dcat_compressformat, dcat_contactpoint,
    dcat_dataset, dcat_distribution, dcat_downloadurl,
    dcat_end, dcat_enddate, dcat_endpointurl, dcat_endpointdescription,
    dcat_format, dcat_frequency,
    dcat_geometry,
    dcat_hadrole, dcat_haspart, dcat_homepage,
    dcat_keyword,
    dcat_landingpage, dcat_listingdate,
    dcat_mediatype,
    dcat_packageformat, dcat_primarytopic,
    dcat_qualifiedrelation,
    dcat_record, dcat_relation,
    dcat_servesdataset, dcat_service, dcat_spatialresolutioninmeters, dcat_startdate,
    dcat_temporalresolution, dcat_theme, dcat_themetaxonomy,

    // dublin core terms
    dct_abstract, dct_accessrights, dct_accrualmethod, dct_accrualperiodicity, dct_accrualpolicy, dct_alternative, dct_audience, dct_available,
    dct_bibliographiccitation,
    dct_conformsto, dct_contributor, dct_coverage, dct_created, dct_creator,
    dct_date, dct_dateaccepted, dct_datecopyrighted, dct_datesubmitted, dct_description,
    dct_educationlevel, dct_extent,
    dct_format,
    dct_hasformat, dct_haspart, dct_hasversion,
    dct_identifier, dct_instructionalmethod, dct_isformatof, dct_ispartof, dct_isreferencedby, dct_isreplacedby, dct_isrequiredby, dct_issued, dct_isversionof,
    dct_language, dct_licence,
    dct_mediator, dct_medium, dct_modified,
    dct_provenance, dct_publisher,
    dct_references, dct_relation, dct_replaces, dct_requires, dct_rights, dct_rightsholder,
    dct_source, dct_spatial, dct_subject,
    dct_tableofcontents, dct_temporal, dct_title, dct_type,
    dct_valid,

    // ddi
    ddip_aggregation, ddip_analysis_unit,
    ddip_based_on,
    ddip_case_quantity, ddip_collection_mode, ddip_computation_base, ddip_concept, ddip_cumulative_percentage,
    ddip_data_file, ddip_ddi_file,
    ddip_end_date, ddip_external_documentation,
    ddip_frequency, ddip_funded_by,
    ddip_in_group, ddip_input_variable, ddip_instrument, ddip_invalid_cases, ddip_is_public, ddip_is_valid,
    ddip_kind_of_data,
    ddip_maximum, ddip_mean, ddip_median, ddip_minimum, ddip_mode,
    ddip_number_of_cases,
    ddip_percentage, ddip_product, ddip_purpose,
    ddip_question, ddip_question_text,
    ddip_representation, ddip_response_domain,
    ddip_standard_deviation, ddip_start_date, ddip_statistics_category, ddip_statistics_data_file, ddip_statistics_variable, ddip_subtitle,
    ddip_universe,
    ddip_valid_cases, ddip_variable,
    ddip_weighted_by, ddip_weighted_cumulative_percentage, ddip_weighted_frequency, ddip_weighted_invalid_cases, ddip_weighted_mean, ddip_weighted_median,
        ddip_weighted_mode, ddip_weighted_percentage, ddip_weighted_valid_cases,

    // doap
    doap_anonroot, doap_audience,
    doap_blog, doap_browse, doap_bugdatabase,
    doap_category, doap_created,
    doap_description, doap_developer, doap_developerforum, doap_documenter, doap_downloadmirror, doap_downloadpage,
    doap_filerelease,
    doap_helper, doap_homepage,
    doap_implements,
    doap_language, doap_licence, doap_location,
    doap_mailinglist, doap_maintainer, doap_module,
    doap_name,
    doap_oldhomepage, doap_os,
    doap_platform, doap_programminglanguage,
    doap_release, doap_hasrepository, doap_repositoryof, doap_revision,
    doap_screenshots, doap_serviceendpoint, doap_shortdesc, doap_supportforum,
    doap_tester, doap_translator,
    doap_vendor,
    doap_wiki,

    // dqv
    dqv_computedon,
    dqv_expecteddatatype,
    dqv_hasqualityannotation, dqv_hasqualitymeasurement, dqv_hasqualitymetadata,
    dqv_incategory, dqv_indimension, dqv_ismeasurementof,
    dqv_value,

    // duv
    duv_hasdistributor, duv_hasfeedback, duv_hasrating, duv_hasusage, duv_hasusagetool,
    duv_refersto,

    // earl
    earl_assertedby,
    earl_info,
    earl_mainassertor, earl_mode,
    earl_outcome,
    earl_pointer,
    earl_result,
    earl_subject,
    earl_test,

    // event
    ep_agent, ep_agentin,
    ep_factor, ep_factorof,
    ep_hasagent, ep_hasfactor, ep_hasliteralfactor, ep_hasproduct, ep_hassubevent,
    ep_isagentin, ep_isfactorof,
    ep_literalfactor,
    ep_place, ep_producedin, ep_product,
    ep_subevent,
    ep_time,

    // exif
    exif_aperaturevalue,
    exif_brightnessvalue,
    exif_cfapattern, exif_colourspace, exif_componentsconfiguration, exif_compressedbitsperpixel, exif_contrast, exif_customrendered,
    exif_datetimeoriginal, exif_devicesettingdescription, exif_digitalzoomratio,
    exif_exifimageheight, exif_exifimagewidth, exif_exifinteroperabilityoffset, exif_exifversion, exif_exposurebiasvalue,
        exif_exposuremode, exif_exposureindex, exif_exposureprogramme, exif_exposuretime,
    exif_filesource, exif_flash, exif_flashenergy, exif_flashpixversion, exif_fnumber, exif_focallength, exif_focallengthin35mmfilm,
        exif_focalplaneresolutionunit, exif_focalplanexresolution, exif_focalplaneyresolution,
    exif_gaincontrol, exif_gpsaltitude, exif_gpsaltituderef, exif_gpsareainformation, exif_gpsdatestamp, exif_gpsdestbearing, exif_gpsdestbearingref, exif_gpsdestdistance,
        exif_gpsdestdistanceref, exif_gpsdestlatitude, exif_gpsdestlatituderef, exif_gpsdestlongitude, exif_gpsdestlongituderef, exif_gpsdifferential,
        exif_gpsdop, exif_gpshpositioningerror, exif_gpslatitude, exif_gpslatituderef, exif_gpslongitude, exif_gpslongituderef, exif_gpsmapdatum, exif_gpsmeasuremode, exif_gpssatellites, exif_gpsspeed,
        exif_gpsspeedref, exif_gpssimgdirection, exif_gpssimgdirectionref, exif_gpsprocessingmethod, exif_gpsstatus, exif_gpstimestamp, exif_gpstrack, exif_gpstrackref,
        exif_gpsversionid,
    exif_imageuniqueid, exif_interoperabilityifdpointer, exif_interoperabilityindex, exif_isospeedrating,
    exif_lightsource,
    exif_makernote, exif_maxaperaturevalue, exif_meteringmode,
    exif_pixelxdimension, exif_pixelydimension,
    exif_oecf,
    exif_relatedsoundfile,
    exif_saturation, exif_scenecapturetype, exif_scenetype, exif_sensingmethod, exif_sharpness, exif_shutterspeedvalue, exif_spatialfrequencyresponse,
        exif_spectralsensitivity, exif_subjectarea, exif_subjectdistance, exif_subjectdistancerange, exif_subjectlocation, exif_subsectime, exif_subsecdigitised,
        exif_subsecoriginal,
    exif_usercomment,
    exif_whitebalance,

    // exifex
    exifex_acceleration,
    exifex_bodyserialnumber,
    exifex_cameraownername, exifex_cameraelevationangle, exifex_camerafirmware, exifex_circle, exifex_compositeimage,
    exifex_ellipse,
    exifex_gamma,
    exifex_humidity,
    exifex_imageeditingsoftware, exifex_imageeditor, exifex_imagetitle, exifex_interoperabilityindex, exifex_isospeed, exifex_isospeedlatitudeyyy, exifex_isospeedlatitudezzz,
    exifex_lensmake, exifex_lensmodel, exifex_lensserialnumber, exifex_lensspecification, exifex_line,
    exifex_metadataeditingsoftware, exifex_multiplepoints, 
    exifex_photographer, exifex_photographicsensitivity, exifex_polygon, exifex_pressure,
    exifex_offsettime, exifex_offsettimeoriginal, exifex_offsettimedigitised,
    exifex_rawdevelopingsoftware, exifex_recommendedexposureindex, exifex_rectangle,
    exifex_sensitivitytype, exifex_sourceexposuretimesofcompositeimage, exifex_sourceimagenumberofcompositeimage, exifex_standardoutputsensitivity, 
    exifex_temperature,
    exitex_uniqueimageid,
    exifex_waterdepth, exifex_whole,

    // fabio
    fbp_date_last_updated,
    fbp_has_acceptance_date, fbp_has_access_date, fbp_has_arxiv_identifier, fbp_has_character_count, fbp_has_coden, fbp_has_copyright_date, fbp_has_copyright_year,
        fbp_has_correction_date, fbp_has_creation_date, fbp_has_creator, fbp_has_date, fbp_has_date_collected, fbp_has_date_received, fbp_has_deadline, fbp_has_decision_date,
        fbp_has_deposit_date, fbp_has_discipline, fbp_has_edition, fbp_has_electronic_article_identifier, fbp_has_embargo_date, fbp_has_embargo_period,
        fbp_has_handle, fbp_has_identifier, fbp_has_issn_l,
        fbp_has_manifestation, fbp_has_national_library_of_medicine_journal_identifier, fbp_has_national_library_of_medicine_journal_title_abbreviation,
        fbp_has_number, fbp_has_page_count, fbp_has_page_range, fbp_has_patent_number, fbp_has_pii, fbp_has_place_of_publication, fbp_has_portrayal,
        fbp_has_preprint_dissemination_date, fbp_has_primary_subject_term, fbp_has_publication_year, fbp_has_pubmed_central_identifier, fbp_has_pubmed_identifier,
        fbp_has_representation, fbp_has_request_date, fbp_has_retraction_date, fbp_has_season, fbp_has_short_title, fbp_has_sici, fbp_has_standard_number,
        fbp_has_subject_term, fbp_has_subtitle, fbp_has_translated_subtitle, fbp_has_translated_title, fbp_has_url, fbp_has_volume_count,
    fbp_is_discipline_of, fbp_is_manifestation_of, fbp_is_portrayal_of, fbp_is_representation_of, fbp_is_scheme_of, fbp_is_stored_on,
    fbp_stores,
    fbp_uses_calendar,

    // foaf
    foaf_account, foaf_accountname, foaf_accountservicehomepage, foaf_age, foaf_aimchatid,
    foaf_basednear, foaf_birthday,
    foaf_currentproject,
    foaf_depiction, foaf_depicts, foaf_dnachecksum,
    foaf_familyname, foaf_firstname, foaf_focus, foaf_fundedby,
    foaf_geekcode, foaf_gender, foaf_givenname,
    foaf_holdsaccount, foaf_homepage,
    foaf_icqchatid, foaf_img, foaf_interest, foaf_isprimarytopicof,
    foaf_jabberid,
    foaf_knows,
    foaf_lastname, foaf_logo,
    foaf_made, foaf_maker, foaf_mbox, foaf_mboxsha1sum, foaf_member, foaf_membershipclass, foaf_msnchatid, foaf_myersbriggs,
    foaf_name, foaf_nick,
    foaf_openid,
    foaf_page, foaf_pastproject, foaf_phone, foaf_plan, foaf_primarytopic, foaf_publications,
    foaf_schoolhomepage, foaf_sha1, foaf_skypeid, foaf_status, foaf_surname,
    foaf_theme, foaf_thumbnail, foaf_tipjar, foaf_title, foaf_topic, foaf_topic_interest,
    foaf_weblog, foaf_workinfohomepage, foaf_workplacehomepage,
    foaf_yahoochatid,

    // frbr core
    fp_abridgement, fp_abridgementof, fp_adaption, fp_adaptionof, fp_alternative, fp_alternativeof, fp_arrangement, fp_arrangementof, fp_complement, fp_complementof,
    fp_creator, fp_creatorof, fp_embodiment, fp_embodimentof, fp_exemplar, fp_exemplarof, fp_imitation, fp_imitationof, fp_owner, fp_ownerof, fp_part,
    fp_partof, fp_producer, fp_producerof, fp_realisation, fp_realisationof, fp_realiser, fp_realiserof, fp_reconfiguration, fp_reconfigurationof,
    fp_relatedendeavour, fp_reproduction, fp_reproductionof, fp_responsibleentity, fp_responsibleentityof, fp_revision, fp_revisionof, fp_subject, fp_successor,
    fp_successorof, fp_summary, fp_summaryof, fp_supplement, fp_supplementof, fp_transformation, fp_transformationof, fp_translation, fp_translationof,

    // good relations
    gr_acceptedpaymentmethods, gr_addon, gr_advancebookingrequirement, gr_amountofgoods, gr_appliestodeliverymethod, gr_appliestopaymentmethod, gr_availabilityends, gr_availabilitystarts, gr_availableatorfrom,
        gr_availabledeliverymethods,
    gr_billingincrement,
    gr_category, gr_closes, gr_colour, gr_condition,
    gr_datatypeproductorserviceproperty, gr_deliveryleadtime, gr_depth, gr_description, gr_displayposition, gr_durationofwarrantyinmonths,
    gr_eligiblecustomertypes, gr_eligibleduration, gr_eligibleregions, gr_eligibletransactionvolume, gr_equal,
    gr_greater, gr_greaterorequal,
    gr_hasbrand, gr_hasbusinessfunction, gr_hascurrency, gr_hascurrencyvalue, gr_hasduns, gr_hasean_ucc_13, gr_haseligiblequantity, gr_hasgtin_14, gr_hasgtin_8, gr_hasgloballocationnumber, gr_hasisicv4,
        gr_hasinventorylevel, gr_hasmakeandmodel, gr_hasmanufacturer, gr_hasmaxcurrencyvalue, gr_hasmaxvalue, gr_hasmaxvaluefloat, gr_hasmaxvalueinteger, gr_hasmincurrencyvalue, gr_hasminvalue,
        gr_hasminvaluefloat, gr_hasminvalueinteger, gr_hasmpn, gr_hasnaics, gr_hasnext, gr_hasopeninghoursdayofweek, gr_hasopeninghoursspecification, gr_haspos, gr_hasprevious, gr_haspricespecification, gr_hasstockkeepingunit,
        gr_hasunitofmeasurement, gr_hasvalue, gr_hasvaluefloat, gr_hasvalueinteger, gr_haswarrantypromise, gr_haswarrantyscope, gr_height,
    gr_includes, gr_includesobject, gr_isaccessoryorsparepartfor, gr_isconsumablefor, gr_islistprice, gr_issimilarto, gr_isvariantof,
    gr_legalname, gr_lesser, gr_lesserorequal,
    gr_name, gr_nonequal,
    gr_offers, gr_opens, gr_owns,
    gr_predecessorof, gr_pricetype,
    gr_qualitativeproductorserviceproperty, gr_quantitativeproductorserviceproperty,
    gr_relatedwebservice,
    gr_seeks, gr_serialnumber, gr_successorof,
    gr_taxid, gr_typeofgoods,
    gr_validfrom, gr_validto, gr_valueaddedtaxincluded, gr_valuereference, gr_vatid,
    gr_weight, gr_width,

    // grddl
    grddlp_namespacetransformation, grddlp_profiletransformation, grddlp_result, grddlp_transformation, grddlp_transformationproperty,

    // gs1
    gs1p_acceptedpaymentmethod, gs1p_activityideas, gs1p_additionalorganizationidentificationtypevalue, gs1p_additionalproductclassification,
    gs1p_additionalproductclassificationcode, gs1p_additionalproductclassificationcodedescription, gs1p_additionalproductclassificationvalue,
    gs1p_additionalproductdescription, gs1p_additive, gs1p_additivelevelofcontainment, gs1p_additivename, gs1p_address, gs1p_addresscountry,
    gs1p_addresslocality, gs1p_addressregion, gs1p_afterhourscontact, gs1p_alcoholicbeveragesubregion, gs1p_allergeninfo, gs1p_allergenlevelofcontainmentcode,
    gs1p_allergenspecificationagency, gs1p_allergenspecificationname, gs1p_allergenstatement, gs1p_allergentype, gs1p_anatomicalform, gs1p_applicableto,
    gs1p_audiofile, gs1p_authenticity, gs1p_authenticitysecurityfeatureinstructions, gs1p_authenticitysecurityfeatureinstructionsurl,
    gs1p_authenticitysecurityfeatureregularexpression, gs1p_authenticitysecurityfeaturetype, gs1p_authenticitysecurityfeaturevalue, gs1p_availabilityends,
    gs1p_availabilitystarts, gs1p_availableatorfrom, gs1p_availablelanguage,
    gs1p_awardprize, gs1p_awardprizecode, gs1p_awardprizecountrycode, gs1p_awardprizedescription, gs1p_awardprizejury, gs1p_awardprizename, gs1p_awardprizeyear,
    gs1p_bestbeforedate, gs1p_beveragevintage, gs1p_biotinpernutrientbasis, gs1p_bonelessclaim, gs1p_brand, gs1p_brandhomepageclinical, gs1p_brandhomepagepatient,
    gs1p_brandname, gs1p_brandowner, gs1p_calciumpernutrientbasis, gs1p_carbohydratespernutrientbasis, gs1p_careersinfo, gs1p_catchzone, gs1p_certification,
    gs1p_certificationagency, gs1p_certificationinfo, gs1p_certificationstandard, gs1p_certificationvalue, gs1p_cheesefirmness, gs1p_cheesematurationperioddescription,
    gs1p_chloridepernutrientbasis, gs1p_cholesterolpernutrientbasis, gs1p_chromiumpernutrientbasis, gs1p_city, gs1p_clothingcut, gs1p_collartype, gs1p_colourcode,
    gs1p_colourcodelist, gs1p_colourcodevalue, gs1p_colourdescription, gs1p_consumerfirstavailabilitydatetime, gs1p_consumerhandlingstorage, gs1p_consumerhandlingstorageinfo,
    gs1p_consumerlifestage, gs1p_consumerpackagedisclaimer, gs1p_consumerproductvariant, gs1p_consumersafetyinformation, gs1p_consumersalescondition,
    gs1p_consumerstorageinstructions, gs1p_consumerusageinstructions, gs1p_contactpoint, gs1p_contacttitle, gs1p_contacttype, gs1p_conveniencelevelpercent,
    gs1p_copperpernutrientbasis, gs1p_countrycode, gs1p_countryofassembly, gs1p_countryoflastprocessing, gs1p_countryoforigin, gs1p_countryoforiginstatement,
    gs1p_countrysubdivisioncode, gs1p_countycode, gs1p_crossstreet, gs1p_customersupportcentre, gs1p_dailyvalueintakepercent, gs1p_defaultlink, gs1p_defaultlinkmulti,
    gs1p_department, gs1p_dependentproprietaryproduct, gs1p_descriptivesize, gs1p_dietcode, gs1p_diettype, gs1p_diettypedescription, gs1p_diettypesubcode,
    gs1p_discountrepeatspermultipleminimum, gs1p_discounttype, gs1p_drainedweight, gs1p_duedate, gs1p_durationofwarranty, gs1p_dutyfeetaxamount, gs1p_dutyfeetaxdescription,
    gs1p_dutyfeetaxrate, gs1p_eligiblequantity, gs1p_eligiblequantitymaximum, gs1p_eligiblequantityminimum, gs1p_eligibletradechannel, gs1p_email,
    gs1p_energyfromfatpernutrientbasis, gs1p_energypernutrientbasis, gs1p_epcis, gs1p_epil, gs1p_equivalentproduct, gs1p_eventsinfo, gs1p_exactdiscountamount,
    gs1p_exactdiscountpercentage, gs1p_exclusiondescription, gs1p_expirationdate, gs1p_expirationdatetime, gs1p_faqs, gs1p_fatinmilkcontent, gs1p_fatpernutrientbasis,
    gs1p_fatpercentageindrymatter, gs1p_faxnumber, gs1p_fibrepernutrientbasis, gs1p_filelanguagecode, gs1p_filepixelheight, gs1p_filepixelwidth, gs1p_firstfreezedate,
    gs1p_fishtype, gs1p_fluoridepernutrientbasis, gs1p_folicacidpernutrientbasis, gs1p_foodbeveragerefrigerationclaim, gs1p_foodbeveragetargetuse, gs1p_footwearfasteningtype,
    gs1p_footwearuppertype, gs1p_freshorseawaterfarmed, gs1p_functionalname, gs1p_geneticallymodifieddeclaration, gs1p_geo, gs1p_globallocationnumber, gs1p_gpccategorycode,
    gs1p_gpccategorydescription, gs1p_grossarea, gs1p_grossvolume, gs1p_grossweight, gs1p_growingmethod, gs1p_gtin, gs1p_handledby, gs1p_harvestdate, gs1p_harvestdateend,
    gs1p_harvestdatestart, gs1p_hasallergen, gs1p_hasbatchlotnumber, gs1p_hasretailers, gs1p_hasreturnablepackagedeposit, gs1p_hasserialnumber,
    gs1p_hasthirdpartycontrolledserialnumber, gs1p_healthclaimdescription, gs1p_homepage, gs1p_image,
    gs1p_includedaccessories, gs1p_ingredient, gs1p_ingredientcontentpercentage, gs1p_ingredientname, gs1p_ingredientofconcern, gs1p_ingredientsequence,
    gs1p_ingredientstatement, gs1p_ingredientsinfo, gs1p_inpackagedepth, gs1p_inpackagediameter, gs1p_inpackageheight,
    gs1p_inpackagewidth, gs1p_instructions, gs1p_instructionsforuse, gs1p_iodinepernutrientbasis, gs1p_ironpernutrientbasis, gs1p_irradiatedcode,
    gs1p_iscarbonated, gs1p_isdecaffeinated, gs1p_isfromconcentrate, gs1p_ishomogenised, gs1p_isinstant, gs1p_ismaternity, gs1p_isonlyavailablethroughretailer,
    gs1p_isonlywithmailinglistsignup, gs1p_isonlywithpaymentcard, gs1p_isonlywithretailerloyaltycard, gs1p_isonlywithretailerpaymentcard, gs1p_ispatterned,
    gs1p_ispittedstoned, gs1p_isproductrecalled, gs1p_ispromoterexclusiveoffer, gs1p_isrindedible, gs1p_isseedless, gs1p_isshelledpeeled, gs1p_issliced,
    gs1p_isthermal, gs1p_isvintage, gs1p_iswashedreadytoeat, gs1p_iswaterproof, gs1p_iswearableitemdisposable, gs1p_itemoffered, gs1p_juicecontentpercent, gs1p_jws,
    gs1p_latitude, gs1p_leavereview, gs1p_linktype, gs1p_location, gs1p_locationinfo, gs1p_logisticsinfo, gs1p_longitude, gs1p_magnesiumpernutrientbasis, gs1p_makesoffer,
    gs1p_manganesepernutrientbasis, gs1p_manufacturer, gs1p_manufacturerpreparationcode, gs1p_manufacturerswarranty, gs1p_manufacturingplant, gs1p_massperunitarea,
    gs1p_masterdata, gs1p_maturationmethod, gs1p_maxprice, gs1p_maximumdiscountamount, gs1p_maximumdiscountpercentage, gs1p_maximumoptimumconsumptiontemperature,
    gs1p_maximumqualifyingitems, gs1p_maximumqualifyingspend, gs1p_meatpoultrytype, gs1p_menuinfo, gs1p_minprice, gs1p_minimumdiscountamount, gs1p_minimumdiscountpercentage,
    gs1p_minimumfishcontent, gs1p_minimummeatpoultrycontent, gs1p_minimumoptimumconsumptiontemperature, gs1p_minimumqualifyingitems, gs1p_minimumqualifyingspend,
    gs1p_molybdenumpernutrientbasis, gs1p_monounsaturatedfatpernutrientbasis, gs1p_netarea, gs1p_netcontent, gs1p_netweight, gs1p_niacinpernutrientbasis,
    gs1p_numberofservingsperpackage, gs1p_numberofservingsperpackagemeasurementprecision, gs1p_numberofservingsrangedescription, gs1p_nutrientbasisquantity,
    gs1p_nutrientbasisquantitytype, gs1p_nutrientmeasurementprecision, gs1p_nutritionalclaim, gs1p_nutritionalclaimstatement, gs1p_nutritionalinfo, gs1p_offerdescription,
    gs1p_offerdiscount, gs1p_offerredemptiontype, gs1p_offerredemptionurl, gs1p_offerrestrictiondescription, gs1p_openinghoursinfo, gs1p_organicclaim, gs1p_organicclaimagency,
    gs1p_organicpercentclaim, gs1p_organisationname, gs1p_organisationrole,
    gs1p_originalcodevalue, gs1p_outofpackagedepth, gs1p_outofpackagediameter, gs1p_outofpackageheight,
    gs1p_outofpackagewidth, gs1p_packaging, gs1p_packagingdate, gs1p_packagingfeature, gs1p_packagingfunction, gs1p_packagingmarkeddietallergentype,
    gs1p_packagingmarkedfreefrom, gs1p_packagingmarkedlabelaccreditation, gs1p_packagingmaterial, gs1p_packagingmaterialcompositionquantity, gs1p_packagingmaterialthickness,
    gs1p_packagingmaterialtype, gs1p_packagingrecyclingprocesstype, gs1p_packagingrecyclingscheme, gs1p_packagingshape, gs1p_packagingtype,
    gs1p_pantothenicacidpernutrientbasis, gs1p_partyname, gs1p_paymentlink, gs1p_paymentterms, gs1p_percentageofalcoholbyvolume, gs1p_phosphoruspernutrientbasis, gs1p_pip,
    gs1p_poboxnumber, gs1p_polyolspernutrientbasis, gs1p_polyunsaturatedfatpernutrientbasis, gs1p_postofficeboxnumber, gs1p_postalcode, gs1p_potassiumpernutrientbasis, gs1p_preparationcode,
    gs1p_preparationconsumptionprecautions, gs1p_preparationinformation, gs1p_preparationinstructions, gs1p_preservationtechnique, gs1p_price, gs1p_pricecurrency,
    gs1p_pricespecification, gs1p_primaryalternateproduct, gs1p_productdescription, gs1p_productfeaturebenefit, gs1p_productformdescription, gs1p_productid,
    gs1p_productmarketingmessage, gs1p_productname, gs1p_productrange, gs1p_productsustainabilityinfo, gs1p_productyield, gs1p_productyieldtype,
    gs1p_productyieldvariationpercentage, gs1p_productiondate, gs1p_productiondatetime, gs1p_productionvariantdescription, gs1p_productionvarianteffectivedatetime,
    gs1p_promotion, gs1p_proteinpernutrientbasis, gs1p_provenancestatement, gs1p_provincestatecode, gs1p_purchasesuppliesoraccessories, gs1p_qualifyingbrandname, gs1p_qualifyinggpcs,
    gs1p_qualifyingproductcategorydescription, gs1p_qualifyingproductclassificationcode, gs1p_qualifyingproductgtins, gs1p_qualifyingsubbrandname, gs1p_quickstartguide,
    gs1p_recallstatus, gs1p_recipeinfo, gs1p_recipewebsite, gs1p_referencedfile, gs1p_referencedfileeffectiveenddatetime, gs1p_referencedfileeffectivestartdatetime, gs1p_referencedfilesize,
    gs1p_referencedfiletype, gs1p_referencedfileurl, gs1p_registerproduct, gs1p_registryentry, gs1p_regulatedproductname, gs1p_reheatingclaim, gs1p_relatedvideo,
    gs1p_replacedbyproduct, gs1p_replacedproduct, gs1p_responsibility, gs1p_returnablepackagedepositamount, gs1p_returnablepackagedepositregion, gs1p_review,
    gs1p_riboflavinpernutrientbasis, gs1p_safetyinfo, gs1p_saltpernutrientbasis, gs1p_saturatedfatpernutrientbasis, gs1p_scheduletime, gs1p_seasoncalendaryear,
    gs1p_seasonname, gs1p_seasonparameter, gs1p_seeker, gs1p_selectedproductsonly, gs1p_seleniumpernutrientbasis, gs1p_sellbydate, gs1p_seller, gs1p_serviceinfo,
    gs1p_servingsize, gs1p_servingsizedescription, gs1p_servingsuggestion, gs1p_sharpnessofcheese, gs1p_size, gs1p_sizecode, gs1p_sizecodelistcode, gs1p_sizecodevalue,
    gs1p_sizedimension, gs1p_sizegroup, gs1p_sizesystem, gs1p_sizetype, gs1p_smartlabel, gs1p_smpc, gs1p_socialmedia, gs1p_sodiumpernutrientbasis, gs1p_sourceanimal,
    gs1p_sportingactivitytype, gs1p_starchpernutrientbasis, gs1p_statisticinfo, gs1p_streetaddress, gs1p_streetaddress1, gs1p_streetaddress2, gs1p_streetaddress3,
    gs1p_styledescription, gs1p_subbrandname, gs1p_sugarspernutrientbasis,
    gs1p_supplierspecifiedminimumconsumerstoragedays, gs1p_support, gs1p_sustainabilityinfo, gs1p_targetconsumerage, gs1p_targetconsumergender, gs1p_targetmarket,
    gs1p_targetmarketcountries, gs1p_telephone, gs1p_textilematerial, gs1p_textilematerialcontent, gs1p_textilematerialdescription, gs1p_textilematerialpercentage,
    gs1p_textilematerialthreadcount, gs1p_textilematerialweight, gs1p_thiaminpernutrientbasis, gs1p_traceability, gs1p_transfatpernutrientbasis, gs1p_tutorial,
    gs1p_unitcode, gs1p_uppermaterialtype, gs1p_useragreement, gs1p_validfrom, gs1p_validto, gs1p_value, gs1p_variantdescription, gs1p_verificationservice,
    gs1p_vintner, gs1p_vitaminapernutrientbasis, gs1p_vitaminb12pernutrientbasis, gs1p_vitaminb6pernutrientbasis, gs1p_vitamincpernutrientbasis, gs1p_vitamindpernutrientbasis,
    gs1p_vitaminepernutrientbasis, gs1p_vitaminkpernutrientbasis, gs1p_warningcopydescription, gs1p_warranty, gs1p_warrantyscopedescription, gs1p_whatsinthebox, gs1p_yield,
    gs1p_zincpernutrientbasis,
        
    // iCal
    ical_action, ical_attendee,
    ical_byday, ical_bymonth,
    ical_caladdress, ical_calscale, ical_categories, ical_class, ical_cn, ical_comment, ical_component, ical_cutype,
    ical_date, ical_datetime, ical_daylight, ical_description, ical_dtend, ical_dstamp, ical_dtstart, ical_duration,
    ical_freq,
    ical_interval,
    ical_language, ical_location,
    ical_organiser,
    ical_partstat, ical_prodid,
    ical_related, ical_role, ical_rrule, ical_rsvp,
    ical_sequence, ical_standard, ical_summary,
    ical_transp, ical_trigger, ical_tzid, ical_tzname, ical_tzoffsetfrom, ical_tzoffsetto,
    ical_uid,
    ical_valarm, ical_version,

    // jsonld
    jsonld_base,
    jsonld_container, jsonld_context,
    jsonld_definition, jsonld_direction,
    jsonld_id, jsonld_import,
    jsonld_language,
    jsonld_nest,
    jsonld_prefix, jsonld_propagate, jsonld_protected,
    jsonld_reverse,
    jsonld_term, jsonld_type,
    jsonld_version, jsonld_vocab,

    // ldp
    ldp_constrainedby, ldp_contains,
    ldp_hasmemberrelation,
    ldp_inbox, ldp_insertedcontentrelation, ldp_ismemberrelationof,
    ldp_member, ldp_membershipresource,
    ldp_pagesequence, ldp_pagesortcollation, ldp_pagesortcriteria, ldp_pagesortorder, ldp_pagesortpredicate,

    // locn
    locn_address, locn_addressarea, locn_addressid, locn_adminunitlevel1, locn_adminunitlevel2,
    locn_fulladdress,
    locn_geographicname, locn_geometry,
    locn_location, locn_locatordesignator, locn_locatorname,
    locn_pobox, locn_postcode, locn_postname,
    locn_thoroughfare,

    // media resources
    ma_alternativetitle, ma_averagebitrate,
    ma_collectionname, ma_copyright, ma_createdin, ma_creationdate,
    ma_date, ma_depictsfictionallocation, ma_description, ma_duration,
    ma_editdate,
    ma_features, ma_fragmentname, ma_frameheight, ma_framerate, ma_framesizeunit, ma_framewidth,
    ma_hasaccessconditions, ma_hasaudiodescription, ma_hascaptioning, ma_haschapter, ma_hasclassification, ma_hasclassificationsystem, ma_hascompression,
        ma_hascontributedto, ma_hascontributor, ma_hascopyrightover, ma_hascreated, ma_hascreator, ma_hasformat, ma_hasfragment, ma_hasgenre, ma_haskeyword,
        ma_haslanguage, ma_haslocationcoordinatesystem, ma_hasmember, ma_hasnamedfragment, ma_haspermissions, ma_haspolicy, ma_haspublished, ma_haspublisher,
        ma_hasrating, ma_hasratingsystem, ma_hasrelatedimage, ma_hasrelatedlocation, ma_hasrelatedresource, ma_hassigning, ma_hassource, ma_hassubtitling,
        ma_hastargetaudience, ma_hastrack,
    ma_iscaptioningof, ma_ischapterof, ma_iscopyrightedby, ma_iscreationlocationof, ma_isfictionallocationdepictedin, ma_isfragmentof, ma_isimagerelatedto,
        ma_islocationrelatedto, ma_ismemberof, ma_isnamedfragmentof, ma_isprovidedby, ma_isratingof, ma_isrelatedto, ma_issigningof, ma_issourceof,
        ma_istargetaudienceof, ma_istrackof,
    ma_locationaltitude, ma_locationlatitude, ma_locationlongitude, ma_locationname, ma_locator,
    ma_mainoriginaltitle,
    ma_numberoftracks,
    ma_playsin, ma_provides,
    ma_ratingscalemax, ma_ratingscalemin, ma_ratingvalue, ma_recorddate, ma_releasedate,
    ma_samplingrate,
    ma_title, ma_trackname,

    // microformats.org
    mp_additional_name, mp_adr, mp_affliation, mp_agent, mp_album, mp_amount, mp_anniversary, mp_attach, mp_attendee, mp_author, mp_availability,
    mp_best, mp_bday, mp_bookmark, mp_brand,
    mp_categories, mp_category, mp_class, mp_comment, mp_contact, mp_contributor, mp_count, mp_country_name, mp_created, mp_currency,
    mp_description, mp_dateline, mp_dtend, mp_dtexpired, mp_dtlisted, mp_dtreviewed, mp_dtstart, mp_duration,
    mp_education, mp_email, mp_enclosure, mp_entry, mp_entry_content, mp_entry_summary, mp_entry_title, mp_exdate, mp_experience, mp_extended_address,
    mp_family_name, mp_feed_category, mp_fn,
    mp_gender_identity, mp_geo, mp_given_name,
    mp_h, mp_hentry, mp_honourific_prefix, mp_honourific_suffix,
    mp_identifier, mp_impp, mp_include, mp_info, mp_ingredient, mp_instructions, mp_item, mp_item_licence,
    mp_key, mp_kind,
    mp_label, mp_lang, mp_latitude, mp_last_modified, mp_licence, mp_listing, mp_listing_action, mp_lister, mp_locality, mp_location, mp_logo, mp_longitude,
    mp_mailer, mp_member, mp_method, mp_min,
    mp_n, mp_nickname, mp_note, mp_nutrition,
    mp_org, mp_organiser, mp_organisation_name, mp_organisation_unit,
    mp_partstat, mp_payment, mp_permalink, mp_photo, mp_player, mp_position, mp_post_office_box, mp_postal_code, mp_principles, mp_price, mp_publications, mp_published,
    mp_rating, mp_rdate, mp_region, mp_rel, mp_related, mp_rev, mp_review, mp_reviewer, mp_role, mp_rrule, mp_resources,
    mp_s, mp_sample, mp_self, mp_sequence, mp_sex, mp_skill, mp_sort_string, mp_source_org, mp_sound, mp_status, mp_street_address, mp_summary,
    mp_tag, mp_tags, mp_term, mp_tel, mp_title, mp_transp, mp_type, mp_tz,
    mp_uid, mp_updated, mp_url,
    mp_value, mp_value_title, mp_version, mp_votes,
    mp_worst,
    mp_yield,

    mp2_dt_accessed, mp2_dt_anniversary,
    mp2_dt_bday,
    mp2_dt_duration,
    mp2_dt_end, mp2_dt_expired,
    mp2_dt_listed,
    mp2_dt_published,
    mp2_dt_rev,
    mp2_dt_start,
    mp2_dt_updated,

    mp2_e_content,
    mp2_e_description,
    mp2_e_instructions,

    mp2_h_breadcrumb,
    mp2_h_entry,

    mp2_p_action, mp2_p_additional_name, mp2_p_adr, mp2_p_affiliation, mp2_p_altitude, mp2_p_attendee, mp2_p_author, mp2_p_average,
    mp2_p_best, mp2_p_brand,
    mp2_p_category, mp2_p_comment, mp2_p_contact, mp2_p_content, mp2_p_count, mp2_p_country_name,
    mp2_p_description, mp2_p_duration,
    mp2_p_education, mp2_p_entry, mp2_p_experience, mp2_p_extended_address,
    mp2_p_family_name,
    mp2_p_region,
    mp2_p_gender_identity, mp2_p_geo, mp2_p_given_name,
    mp2_p_honourific_prefix, mp2_p_honourific_suffix,
    mp2_p_ingredient, mp2_p_item,
    mp2_p_job_title,
    mp2_p_label, mp2_p_latitude, mp2_p_lister, mp2_p_locality, mp2_p_location, mp2_p_longitude,
    mp2_p_name, mp2_p_nickname, mp2_p_note, mp2_p_nutrition,
    mp2_p_org, mp2_p_organisation_name, mp2_p_organisation_unit,
    mp2_p_rating, mp2_p_review, mp2_p_post_office_box, mp2_p_postal_code, mp2_p_price, mp2_p_publication,
        mp2_p_read_of, mp2_p_role, mp2_p_rsvp,
    mp2_p_sex, mp2_p_size, mp2_p_skill, mp2_p_sort_string, mp2_p_street_address, mp2_p_summary,
    mp2_p_tel,
    mp2_p_tz,
    mp2_p_votes,
    mp2_p_worst,
    mp2_p_yield,

    mp2_u_audio,
    mp2_u_bookmark_of,
    mp2_u_email,
    mp2_u_featured,
    mp2_u_geo,
    mp2_u_identifier, mp2_u_impp, mp2_u_in_reply_to,
    mp2_u_like, mp2_u_like_of, mp2_u_listen_of, mp2_u_logo,
    mp2_u_key,
    mp2_u_photo,
    mp2_u_read_of, mp2_u_repost, mp2_u_repost_of,
    mp2_u_sound, mp2_u_syndication,
    mp2_u_translation_of,
    mp2_u_uid, mp2_u_url,
    mp2_u_video,
    mp2_u_watch_of,

    // web annotation
    oa_annotationservice,
    oa_bodyvalue,
    oa_cachedsource, oa_canonical,
    oa_end, oa_exact,
    oa_hasbody, oa_hasendselector, oa_haspurpose, oa_hasscope, oa_hasselector, oa_hassource, oa_hasstartselector, oa_hasstate, oa_hastarget,
    oa_motivatedby,
    oa_prefix, oa_processinglanguage,
    oa_refinedby, oa_renderedvia,
    oa_sourcedate, oa_sourcedateend, oa_sourcedatestart, oa_start, oa_styleclass, oa_styledby, oa_suffix,
    oa_textdirection,
    oa_via,

    // open graph
    og_article_author, og_article_expiration_time, og_article_modified_time, og_article_published_time, og_article_section, og_article_tag,
    og_audio, og_audio_album, og_audio_artist, og_audio_secure_url, og_audio_title, og_audio_type, og_audio_url,
    og_book_author, og_book_isbn, og_book_release_date, og_book_tag,
    og_country_name,
    og_description, og_determiner,
    og_email,
    og_fax_number,
    og_image, og_image_alt, og_image_height, og_image_secure_url, og_image_type, og_image_url, og_image_width,
    og_latitude, og_locale, og_locale_alternative, og_locality, og_longitude,
    og_music_album, og_music_album_disc, og_music_album_track, og_music_creator, og_music_duration, og_music_musician, og_music_release_date, og_music_song, og_music_song_disc, og_music_song_track,
    og_phone_number, og_postcode, og_profile_first_name, og_profile_gender, og_profile_last_name, og_profile_username,
    og_region, og_site_name, og_street_address,
    og_title, og_type,
    og_url,
    og_video, og_video_actor, og_video_actor_role, og_video_alt, og_video_director, og_video_duration, og_video_height, og_video_release_date, og_video_secure_url, og_video_series, og_video_tag, og_video_type, og_video_url,
        og_video_width, og_video_writer,

    // odrl
    odrlp_action, odrlp_and, odrlp_andsequence, odrlp_assignee, odrlp_assigneeof, odrlp_assigner, odrlp_assignerof, odrlp_attributedparty, odrlp_attributingparty,
    odrlp_compensatedparty, odrlp_compensatingparty, odrlp_conflict, odrlp_consentedparty, odrlp_consentingparty, odrlp_consequence, odrlp_constraint, odrlp_contractedparty, odrlp_contractingparty,
    odrlp_datatype, odrlp_duty,
    odrlp_failure, odrlp_function,
    odrlp_haspolicy,
    odrlp_implies, odrlp_includedin, odrlp_informedparty, odrlp_informingparty, odrlp_inheritfrom,
    odrlp_leftoperand,
    odrlp_obligation, odrlp_operand, odrlp_operator, odrlp_or, odrlp_output,
    odrlp_partof, odrlp_permission, odrlp_profile, odrlp_prohibition,
    odrlp_refinement, odrlp_relation, odrlp_remedy, odrlp_rightoperand, odrlp_rightoperandreference,
    odrlp_source, odrlp_status,
    odrlp_target, odrlp_trackedparty, odrlp_trackingparty,
    odrlp_uid, odrlp_unit,
    odrlp_xone,

    // org
    orgp_basedat,
    orgp_changedby, orgp_classification,
    orgp_hasmember, orgp_hasmembership, orgp_haspost, orgp_hasprimarysite, orgp_hasregisteredsite, orgp_hassite, orgp_hassuborganisation, orgp_hasunit, orgp_headof, orgp_heldby, orgp_holds,
    orgp_identifier,
    orgp_linkedto, orgp_location,
    orgp_member, orgp_memberduring, orgp_memberof,
    orgp_organisation, orgp_originalorganisation,
    orgp_postin, orgp_purpose,
    orgp_remuneration, orgp_reportsto, orgp_resultedfrom, orgp_resultingorganisation, orgp_role, orgp_roleproperty,
    orgp_siteaddress, orgp_siteof, orgp_suborganisationof,
    orgp_transitivesuborganisationof,
    orgp_unitof,

    // owl
    owl_allvaluesfrom, owl_annotatedproperty, owl_annotatedsource, owl_annotatedtarget, owl_assertionproperty,
    owl_backwardcompatiblewith, owl_bottomdataproperty, owl_bottomobjectproperty,
    owl_cardinality, owl_complementof,
    owl_datatypecomplementof, owl_deprecated, owl_differentfrom, owl_disjointunionof, owl_disjointwith, owl_distinctmembers,
    owl_equivalentclass, owl_equivalentproperty,
    owl_haskey, owl_hasself, owl_hasvalue,
    owl_imports, owl_incompatiblewith, owl_intersectionof, owl_inverseof,
    owl_maxcardinality, owl_maxqualifiedcardinality, owl_members, owl_mincardinality, owl_minqualifiedcardinality,
    owl_onclass, owl_ondatarange, owl_ondatatype, owl_oneof, owl_onproperties, owl_onproperty,
    owl_priorversion, owl_propertychainaxiom, owl_propertydisjointwith,
    owl_qualifiedcardinality,
    owl_sameas, owl_somevaluesfrom, owl_sourceindividual,
    owl_targetindividual, owl_targetvalue, owl_topdataproperty, owl_topobjectproperty,
    owl_unionof,
    owl_versioninfo, owl_versioniri,
    owl_withrestrictions,

    // prism aggregator
    pam_article, pam_caption, pam_credit, pam_media, pam_mediareference, pam_mediatitle, pam_message, pam_nonpublishedmediatitle,
        pam_refid, pam_status, pam_textdescription,

    // prism crafts
    pcm_craftcategory, pcm_craftsubcategory, pcm_crafttitle, pcm_mainmaterial, pcm_method, pcm_skilllevel, pcm_sourcetype, pcm_specialequipment,
        pcm_specialoccasion, pcm_totalcost, pcm_totaltime,

    // prism contract management
    pcmm_assetidref, pcmm_assetrelated,
    pcmm_changesnegotiated, pcmm_contractstatus, pcmm_contracttype, pcmm_contractversion,
    pcmm_expirationdate,
    pcmm_finalisationdate,
    pcmm_signatorcontactaddress, pcmm_signatorcontractemail, pcmm_signatorcontactidref, pcmm_signatorcontactphone, pcmm_staffcontactaddress, pcmm_staffcontactemail,
        pcmm_staffcontactidref, pcmm_staffcontactphone, pcmm_statusdate,
    pcmm_templateidref,
    pcmm_unioncontact, pcmm_usagerightssummaryidref,

    // prism controlled vocab
    pcv_broaderterm, pcv_code, pcv_definition, pcv_label, pcv_narrowerterm, pcv_relatedterm, pcv_synonym, pcv_vocabulary,

    // pdf
    pdf_keywords, pdf_pdfversion, pdf_producer, pdf_trapped,

    // photoshop
    photoshop_ancestorid, photoshop_authorsposition,
    photoshop_captionwriter, photoshop_category, photoshop_city, photoshop_colourmode, photoshop_country, photoshop_credit,
    photoshop_datecreated, photoshop_documentancestors,
    photoshop_headline, photoshop_history,
    photoshop_iccprofile, photoshop_instructions,
    photoshop_layername, photoshop_layertext,
    photoshop_source, photoshop_state, photoshop_supplementalcategories,
    photoshop_textlayers, photoshop_transmissionreference,
    photoshop_urgency,

    // prism online markup
    pim_academicfield, pim_event, pim_industry, pim_keyword, pim_link, pim_location, pim_object, pim_objecttitle, pim_organisation, pim_person,
        pim_profession, pim_quote, pim_sport, pim_ticker, pim_timeperiod,

    // poetry
    poetry_age, poetry_alludesto, poetry_containedinpoem, poetry_containspoem, poetry_content, poetry_hasform, poetry_hasstanza, poetry_indialect, poetry_ischorus, poetry_islaidout,
        poetry_keepsstrictform, poetry_lines, poetry_medium, poetry_metre, poetry_poet, poetry_refersto, poetry_region, poetry_rhymingscheme, poetry_subform,

    // prism image
    pmi_colour, pmi_contactinfo,
    pmi_displayname, pmi_distributorproductid,
    pmi_eventalias, pmi_eventend, pmi_eventstart, pmi_eventsubtype, pmi_eventtype,
    pmi_field, pmi_framing,
    pmi_location,
    pmi_make, pmi_manufacturer, pmi_model, pmi_modelyear,
    pmi_objectdescription, pmi_objectsubtype, pmi_objecttype, pmi_orientation,
    pmi_positiondescriptor, pmi_productid, pmi_productidtype,
    pmi_rating,
    pmi_season, pmi_sequencename, pmi_sequencenumber, pmi_sequencetotalnumber, pmi_setting, pmi_shootid, pmi_slideshowname, pmi_slideshownumber,
        pmi_slideshowtotalnumber,
    pmi_viewpoint, pmi_visualtechnique,

    // provincial
    pp_actedonbehalfof, pp_activity, pp_agent, pp_alternativeto, pp_atlocation, pp_attime,
    pp_endedattime, pp_entity,
    pp_generated, pp_generatedattime,
    pp_hadactivity, pp_hadgeneration, pp_hadmember, pp_hadplan, pp_hadprimarysource, pp_hadrole, pp_hadusage,
    pp_influenced, pp_influencer, pp_invalidated, pp_invalidatedattime,
    pp_qualifiedassociation, pp_qualifiedattribution, pp_qualifiedcommunication, pp_qualifieddelegation, pp_qualifiedderivation, pp_qualifiedend, pp_qualifiedgeneration, pp_qualifiedinfluence,
        pp_qualifiedinvalidation, pp_qualifiedprimarysource, pp_qualifiedquotation, pp_qualifiedrevision, pp_qualifiedstart, pp_qualifiedusage,
    pp_specialisationof, pp_startedattime,
    pp_used,
    pp_value,
    pp_wasassociatedwith, pp_wasattributedto, pp_wasderivedfrom, pp_wasendedby, pp_wasgeneratedby, pp_wasinfluencedby, pp_wasinformedby, pp_wasinvalidatedby, pp_wasquotedfrom, pp_wasrevisionof,
        pp_wasstartedby,

    // prism
    prism_academicfield, prism_aggregateissuenumber, prism_aggregationtype, prism_alternativetitle,
    prism_blogtitle, prism_blogurl, prism_bookedition, prism_bytecount,
    prism_category, prism_channel, prism_complianceprofile, prism_contentlength, prism_copyright, prism_copyrightyear, prism_corporateentity, prism_coverdate, prism_coverdisplaydate, prism_creationdate, prism_creationtime, 
    prism_datereceived, prism_device, prism_distributor, prism_doi,
    prism_edition, prism_eissn, prism_embargodate, prism_endingpage, prism_event, prism_expirationdate, prism_expirationtime,
    prism_genre,
    prism_hasalternative, prism_hascorrection, prism_hasformat, prism_haspart, prism_hastranslation, prism_hasversion,
    prism_industry, prism_isalternativefor, prism_isalternativeof, prism_isbasedon, prism_isbasisfor, prism_isbn, prism_iscorrectionof, prism_isformatof, prism_ispartof, prism_haspreviousversion, prism_isreferencedby,
        prism_isrequiredby, prism_issn, prism_issueidentifier, prism_issuename, prism_issueteaser, prism_issuetype, prism_istranslationof, prism_isversionof,
    prism_keyword, prism_killdate,
    prism_link, prism_location,
    prism_metadatacontainer, prism_modificationdate, prism_modificationtime,
    prism_nationalcataloguenumber, prism_number,
    prism_object, prism_objecttitle, prism_offsaledate, prism_onsaledate, prism_onsaleday, prism_organisation, prism_originplatform,
    prism_page, prism_pagecount, prism_pageprogressiondirection, prism_pagerange, prism_person, prism_platform, prism_productcode, prism_profession, prism_publicationdate, prism_publicationdisplaydate, prism_publicationname,
        prism_publicationtime, prism_publishingfrequency,
    prism_rating, prism_receptiondate, prism_receptiontime, prism_references, prism_releasetime, prism_requires, prism_rightsagent,
    prism_samplepagerange, prism_section, prism_sellingagency, prism_seriesnumber, prism_seriestitle, prism_sport, prism_startingpage, prism_subchannel1, prism_subchannel2, prism_subchannel3, prism_subchannel4,
        prism_subsection1, prism_subsection2, prism_subsection3, prism_subsection4, prism_subtitle, prism_supplementdisplayid, prism_supplementstartingpage, prism_supplementtitle,
    prism_teaser, prism_ticker, prism_timeperiod,
    prism_url, prism_uspsnumber,
    prism_versionidentifier, prism_volume,
    prism_wordcount,

    // prism_ad
    prism_ad_adidsystem, prism_ad_adposition, prism_ad_advertisedbrand, prism_ad_audiencetype, prism_ad_publishermaterialsid, prism_ad_sellersalesrepcontact,
        prism_ad_sellersalesrepemail, prism_ad_tabletadtype, prism_ad_targettedaudience, prism_ad_webtarget,

    // prism rights language
    prl_geography, prl_industry, prl_usage,

    // prism recipe
    prm_cookingequipment, prm_cookingmethod, prm_course, prm_cuisine,
    prm_dietaryneeds, prm_dishtype, prm_duration,
    prm_ingredientexclusion,
    prm_mainingrediant, prm_meal,
    prm_recipeendingpage, prm_recipepagerange, prm_recipesource, prm_recipestartingpage, prm_recipetitle,
    prm_servingsize, prm_skilllevel, prm_specialoccasion,
    prm_yield,

    // prism rights
    prs_action, prs_agreementlink, prs_assetlink,
    prs_constraint,
    prs_duty,
    prs_generalinfo,
    prs_party, prs_partyaddress, prs_partyemail, prs_partylink, prs_partyname, prs_partyphone, prs_permission, prs_prohibition,
    prs_rightsagent, prs_rightsowner,

    // psv
    psv_adbooking, psv_adidblk, psv_admaterials, psv_aggregationinfo, psv_articleinfo,
    psv_blogentryinfo, psv_bloginfo,
    psv_chapterinfo, psv_components, psv_componenttype, psv_content, psv_creators,
    psv_description,
    psv_idblk, psv_issueinfo,
    psv_meta, psv_metadata,
    psv_psv,
    psv_uniqueid, psv_usagerights,
    psv_websiteinfo, psv_whereused,

    // ptr
    ptr_bytes,
    ptr_characterencoding, ptr_chars,
    ptr_declaredencoding, ptr_doctypename, ptr_dtdecl,
    ptr_internalsubset,
    ptr_leadingmisc,
    ptr_publicid,
    ptr_rest,
    ptr_standalone, ptr_systemid,
    ptr_version,

    // prism usage rights
    pur_adultcontentwarning, pur_agreement,
    pur_copyright, pur_creditline,
    pur_embargodate, pur_exclusivityenddate, pur_expirationdate,
    pur_imagesizerestriction,
    pur_optionenddate,
    pur_permissions,
    pur_restrictions, pur_reuseprohibited, pur_rightsagent, pur_rightsowner,
    pur_usagefee,

    // data cube
    qbp_attribute,
    qbp_codelist, qbp_component, qbp_componentattachment, qbp_componentproperty, qbp_componentrequired, qbp_concept,
    qbp_dataset, qbp_dimension,
    qbp_hierarchyroot,
    qbp_measure, qbp_measuredimension, qbp_measuretype,
    qbp_observation, qbp_observationgroup, qbp_order,
    qbp_parentchildproperty,
    qbp_slice, qbp_slicekey, qbp_slicestructure, qbp_structure,

    // RDF
    rdf_description, rdf_direction, rdf_first, rdf_language, rdf_object, rdf_predicate, rdf_resource, rdf_rest, rdf_subject, rdf_type, rdf_value,

    // RDFg
    rdfg_equivalentgraph, rdfg_subgraphof,

    // RDFs
    rdfs_comment, rdfs_domain, rdfs_isdefinedby, rdfs_label, rdfs_member, rdfs_range, rdfs_seealso, rdfs_subclassof, rdfs_subpropertyof,

    // Review Vocabulary
    rev_commenter, rev_hascomment, rev_hasfeedback, rev_hasreview, rev_maxrating, rev_minrating, rev_positivevotes, rev_rating, rev_reviewer, rev_text, rev_totalvotes, rev_type,

    // rdb to rdf
    rrp_child, rrp_class, rrp_column, rrp_constant,
    rrp_datatype,
    rrp_graph, rrp_graphmap,
    rrp_inverseexpression,
    rrp_joincondition,
    rrp_language, rrp_logicaltable,
    rrp_object, rrp_objectmap,
    rrp_parent, rrp_parenttriplesmap, rrp_predicate, rrp_predicatemap, rrp_predicateobjectmap,
    rrp_sqlquery, rrp_sqlversion, rrp_subject, rrp_subjectmap,
    rrp_tablename, rrp_template, rrp_termtype,

    // schema.org
    sp_about, sp_abridged, sp_abstract, sp_accelerationtime, sp_acceptedanswer, sp_acceptedoffer, sp_acceptedpaymentmethod, sp_acceptsreservations, sp_accessibilityapi, sp_accessibilitycontrol,
    sp_accessibilityfeature, sp_accessibilityhazard, sp_accessibilitysummary, sp_accesscode, sp_accessmode, sp_accessmodesufficient, sp_accommodationcategory, sp_accommodationfloorplan, sp_accountableperson,
    sp_accountid, sp_accountminimuminflow, sp_accountoverdraftlimit, sp_acquiredfrom, sp_acquirelicensepage, sp_acrisscode, sp_action, sp_actionablefeedbackpolicy, sp_actionaccessibilityrequirement, sp_actionapplication,
    sp_actionoption, sp_actionplatform, sp_actionstatus, sp_activeingredient, sp_activityduration, sp_activityfrequency, sp_actor, sp_actors, sp_additionalname, sp_additionalnumberofguests, sp_additionalproperty, sp_additionaltype,
    sp_additionalvariable, sp_addon, sp_address, sp_addresscountry, sp_addresslocality, sp_addressregion, sp_administrationroute, sp_advancebookingrequirement, sp_adverseoutcome, sp_affectedby, sp_affiliation, sp_aftermedia,
    sp_agent, sp_agentinteractionstatistic, sp_aggregaterating, sp_aircraft, sp_album, sp_albums, sp_albumproductiontype, sp_albumrelease, sp_albumreleasetype, sp_alcoholwarning, sp_algorithm, sp_alignmenttype, sp_alternativename, sp_alternativeheadline,
    sp_alternativeof, sp_alumni, sp_alumniof, sp_amenityfeature, sp_amount, sp_amountofthisgood, sp_announcementlocation, sp_annualpercentagerate, sp_answercount, sp_answerexplanation, sp_antagonist, sp_appearance, sp_applicablecountry, sp_applicablelocation,
    sp_applicantcontact, sp_applicantlocationrequirements, sp_application, sp_applicationcategory, sp_applicationdeadline, sp_applicationstartdate, sp_applicationsubcategory, sp_applicationsuite, sp_appliestodeliverymethod,
    sp_appliestopaymentmethod, sp_area, sp_archivedat, sp_archiveheld, sp_areaserved, sp_arrivalairport, sp_arrivalboatterminal, sp_arrivalbusstop, sp_arrivalgate, sp_arrivalplatform, sp_arrivalstation, sp_arrivalterminal,
    sp_arrivaltime, sp_artedition, sp_arterialbranch, sp_artform, sp_articlebody, sp_articlesection, sp_artist, sp_artmedium, sp_artworksurface, sp_asin, sp_aspect, sp_assemblyversion, sp_assess, sp_assesses,
    sp_associatedanatomy, sp_associatedarticle, sp_associatedclaimreview, sp_associateddisease, sp_associatedmedia, sp_associatedmediareview, sp_associatedpathophysiology, sp_associatedreview, sp_athlete,
    sp_attendee, sp_attendees, sp_audience, sp_audiencetype, sp_audio, sp_auditdate, sp_authenticator, sp_author, sp_availability, sp_availabilityends, sp_availabilitystarts, sp_availableatorfrom, sp_availablechannel,
    sp_availabledeliverymethod, sp_availablefrom, sp_availablein, sp_availablelanguage, sp_availablelocation, sp_availableondevice, sp_availableservice, sp_availablestrength, sp_availabletest, sp_availableuntil,
    sp_award, sp_awards, sp_awayteam,

    sp_bankaccounttype, sp_background, sp_backstory, sp_basesalary, sp_bccrecipient, sp_bed, sp_beforemedia, sp_beneficiarybank, sp_benefits, sp_benefitssummaryurl, sp_bestrating, sp_billingaddress, sp_billingduration, sp_billingincrement,
    sp_billingperiod, sp_billingstart, sp_biocheminteraction, sp_biochemsimilarity, sp_biologicalrole, sp_biomechanicalclass, sp_birthdate, sp_birthplace, sp_bitrate, sp_blogpost, sp_blogposts, sp_bloodsupply, sp_boardinggroup,
    sp_boardingpolicy, sp_bodylocation, sp_bodytype, sp_bookedition, sp_bookformat, sp_bookingagent, sp_bookingtime, sp_borrower, sp_box, sp_branch, sp_branchcode, sp_branchof, sp_brand, sp_breadcrumb, sp_breastfeedingwarning, sp_broadcastaffiliateof, sp_broadcastchannelid,
    sp_broadcastdisplayname, sp_broadcaster, sp_broadcastfrequency, sp_broadcastfrequencyvalue, sp_broadcastofevent, sp_broadcastservicetier, sp_broadcastsignalmodulation, sp_broadcastsubchannel, sp_broadcasttimezone, sp_broker,
    sp_browserrequirements, sp_businessdays, sp_businessfunction, sp_busname, sp_busnumber, sp_buyer, sp_byartist, sp_byday, sp_bymonth, sp_bymonthday, sp_bymonthweek,

    sp_callsign, sp_calories, sp_candidate, sp_caption, sp_carbohydratecontent, sp_cargovolume, sp_carrierrequirements, sp_cashback, sp_catalogue, sp_cataloguenumber, sp_category, sp_cause, sp_causeof,
    sp_ccrecipient, sp_certificationidentification, sp_certificationstatus, sp_character, sp_characterattribute, sp_charactername, sp_cheatcode, sp_checkintime, sp_checkoutpageurltemplate, sp_checkouttime, sp_chemicalcomposition, sp_chemicalrole, sp_childmaxage,
    sp_childminage, sp_children, sp_childtaxon, sp_cholesterolcontent, sp_circle, sp_citation, sp_claiminterpreter, sp_claimreviewed, sp_clinicalpharamcology,
    sp_clipnumber, sp_closes, sp_coach, sp_code, sp_coderepository, sp_codesampletype, sp_codevalue, sp_codingsystem, sp_colleague, sp_colleagues, sp_collection, sp_collectionsize, sp_colour, sp_colourist, sp_colourswatch, sp_comment, sp_commentcount, sp_commenttext, sp_commenttime,
    sp_competencyrequired, sp_competitor, sp_composer, sp_comprisedof, sp_conditionsofaccess, sp_confirmationnumber, sp_connectedto, sp_constrainingproperty, sp_constraintproperty, sp_contactlesspayment, sp_contactoption, sp_contactpoint, sp_contactpoints, sp_contacttype,
    sp_containedin, sp_containedinplace, sp_containsplace, sp_containsseason, sp_contentlocation, sp_contentrating, sp_contentreferencetime, sp_contentsize, sp_contenttype, sp_contenturl, sp_contraindication, sp_contributor, sp_cookingmethod, sp_cooktime,
    sp_copyrightholder, sp_copyrightnotice, sp_copyrightyear, sp_correction, sp_correctionspolicy, sp_cost, sp_costcategory, sp_costcurrency, sp_costorigin, sp_costperunit, sp_countriesnotsupported, sp_countriessupported,
    sp_countryofassembly, sp_countryoflastprocessing, sp_countryoforigin, sp_course, sp_coursecode, sp_courselength,
    sp_coursemode, sp_coursepresequisites, sp_courseschedule, sp_courseworkload, sp_coverageendtime, sp_coveragestarttime, sp_creativeworkstatus, sp_creator, sp_credentialcategory, sp_creditedto, sp_credittext, sp_cssselector, sp_currenciesaccepted, sp_currency,
    sp_currentexchangerate, sp_customer, sp_cutofftime, sp_cvdcollectiondate, sp_cvdfacilitycounty, sp_cvdfacilityid, sp_cvdnumbeds, sp_cvdnumbedsocc, sp_cvdnumc19died, sp_cvdnumc19hopats, sp_cvdnumc19hosppats, sp_cvdnumc19mechventpats,
    sp_cvdnumc19ofmechventpats, sp_cvdnumc19overflowpats, sp_cvdnumicubeds, sp_cvdnumicubedsocc, sp_cvdnumtotbeds, sp_cvdnumvent,
    sp_customerremorsereturnfees, sp_customerremorsereturnlabelsource, sp_customerremorsereturnshippingfeesamount, sp_cvdnumventuse,

    sp_datafeedelement, sp_dataset, sp_datasettimeinterval, sp_datecreated, sp_datedeleted, sp_dateissued, sp_dateline, sp_datemodified, sp_dateposted, sp_datepublished, sp_dateread, sp_datereceived, sp_datesent,
    sp_datevehiclefirstregistered, sp_dayofweek, sp_deathdate, sp_deathplace, sp_defaultvalue, sp_deliveryaddress, sp_deliveryleadtime, sp_deliverymethod, sp_deliverystatus, sp_deliverytime, sp_department, sp_departureairport,
    sp_departureboatterminal, sp_departurebusstop, sp_departuregate, sp_departureplatform, sp_departurestation, sp_departureterminal, sp_departuretime, sp_dependencies, sp_depth, sp_description, sp_device, sp_diagnosis, sp_diagram, sp_diet,
    sp_dietfeatures, sp_differentialdiagnosis, sp_digitalsourcetype, sp_directapply, sp_director, sp_directors, sp_disambiguatingdescription, sp_discount, sp_discountcode, sp_discountcurrency, sp_discusses, sp_discussionurl, sp_diseasepreventioninfo, sp_diseasespreadstatistics,
    sp_dissolutiondate, sp_distance, sp_distinguishingsign, sp_distribution, sp_diversitypolicy, sp_diversitystaffingreport, sp_documentation, sp_doesnotship, sp_domainincludes, sp_domiciledmortgage, sp_doortime, sp_dosageform,
    sp_doseschedule, sp_doseunit, sp_dosevalue, sp_downloadurl, sp_downpayment, sp_downvotecount, sp_drainsto, sp_drivewheelconfiguration, sp_dropofflocation, sp_dropofftime, sp_drug, sp_drugclass, sp_drugunit, sp_duns,
    sp_duplicatetherapy, sp_duration, sp_durationofwarranty, sp_duringmedia,

    sp_earlyprepaymentpenalty, sp_editeidr, sp_editor, sp_educationalalignment, sp_educationalcredentialawarded, sp_educationalframework, sp_educationallevel, sp_educationalprogrammode, sp_educationalrole, sp_educationaluse,
    sp_educationcredentialawarded, sp_educationrequirements, sp_eduquestiontype, sp_elevation, sp_eligibilecustomertype, sp_eligibilitytoworkrequirement, sp_eligiblecustomertype, sp_eligibleduration, sp_eligiblequantity, sp_eligibleregion,
    sp_eligibletransactionvolume, sp_email, sp_embeddedtextcaption, sp_embedurl, sp_emmissionsco2, sp_employee, sp_employees, sp_employeroverview, sp_employmenttype, sp_employmentunit, sp_encodescreativework, sp_encodesbiochementity, sp_encoding,
    sp_encodings, sp_encodingformat, sp_encodingtype, sp_enddate, sp_endoffset, sp_endorsee, sp_endorsers, sp_endtime, sp_energyefficiencyscalemax, sp_energyefficiencyscalemin,
    sp_enginedisplacement, sp_enginepower, sp_enginetype, sp_entertainmentbusiness, sp_epidemiology, sp_episode, sp_episodes, sp_episodenumber, sp_equal, sp_error, sp_estimatedcost,
    sp_estimatedflightduration, sp_estimatedsalary, sp_estimatesriskof, sp_ethicspolicy, sp_event, sp_events, sp_eventattendancemode, sp_eventschedule, sp_eventstatus, sp_evidencelevel, sp_evidenceorigin, sp_exampleofwork, sp_exceptdate,
    sp_exchangeratespread, sp_executablelibraryname, sp_exercisecourse, sp_exerciseplan, sp_exerciserelateddiet, sp_exercisetype, sp_exifdata, sp_expectedarrivalfrom, sp_expectedarrivaluntil, sp_expectedprognosis, sp_expectsacceptanceof,
    sp_experiencerequirements, sp_experienceinplaceofeducation, sp_expires, sp_exportconsiderations, sp_expressedin,

    sp_familyname, sp_fatcontent, sp_faxnumber, sp_featurelist, sp_feesandcommissionsspecification, sp_fibrecontent, sp_fileformat, sp_filesize, sp_financialaideligible, sp_firstappearance, sp_firstperformance, sp_flightdistance,
    sp_flightnumber, sp_floorlevel, sp_floorlimit, sp_floorsize, sp_followee, sp_follows, sp_followup, sp_foodestablishment, sp_foodevent, sp_foodwarning, sp_founder, sp_founders, sp_foundingdate, sp_foundinglocation, sp_free, sp_freeshippingthreshold,
    sp_frequency, sp_fromlocation, sp_fuelcapacity, sp_fuelconsumption, sp_fuelefficiency, sp_fueltype, sp_funcionalclass, sp_function, sp_fundeditem, sp_funder, sp_funding,

    sp_game, sp_gameavailabilitytype, sp_gameedition, sp_gameitem, sp_gamelocation, sp_gameplatform, sp_gameserver, sp_gametip, sp_gender, sp_genre, sp_geo, sp_geocontains, sp_geocoveredby, sp_geocovers, sp_geocrosses, sp_geodisjoint, sp_geoequals,
    sp_geographicarea, sp_geointersects, sp_geomidpoint, sp_geooverlaps, sp_georadius, sp_geotouches, sp_geowithin, sp_gettingtestedinfo, sp_givenname, sp_globallocationnumber, sp_governmentbenefitsinfo, sp_graceperiod, sp_grantee,
    sp_greater, sp_greaterorequal, sp_gtin, sp_gtin12, sp_gtin13, sp_gtin14, sp_gtin8, sp_guideline, sp_guidelinedate, sp_guidelinesubject,

    sp_handlingtime, sp_hasadultconsideration, sp_hasbiochementitypart, sp_hasbiopolymersequence, sp_hasbroadcastchannel, sp_hascategorycode, sp_hascertification, sp_hascourse, sp_hascourseinstance, sp_hascredential, sp_hasdefinedterm,
    sp_hasdeliverymethod, sp_hasdigitaldocumentpermission, sp_hasdrivethroughservice, sp_hasenergyconsumptiondetails, sp_hasenergyefficiencycategory, sp_hashealthaspect, sp_hasmap, sp_hasmeasurement, sp_hasmenu,
    sp_hasmenuitem, sp_hasmenusection, sp_hasmerchantreturnpolicy, sp_hasmolecularfunction, sp_hasoccupation, sp_hasoffercatalogue, sp_haspart, sp_haspos, sp_hasproductreturnpolicy, sp_hasrepresentation, sp_hasvariant, sp_headline, sp_healthcarereportingdata, sp_healthcondition,
    sp_healthplancoinsuranceoption, sp_healthplancoinsurancerate, sp_healthplancopay, sp_healthplancopayoption, sp_healthplancostsharing, sp_healthplandrugoption, sp_healthplandrugtier, sp_healthplanid, sp_healthplanmarketingurl,
    sp_healthplannetworkid, sp_healthplannetworktier, sp_healthplanpharmacycategory, sp_height, sp_highprice, sp_hiringorganisation, sp_holdingarchive, sp_homelocation, sp_hometeam, sp_honourificprefix, sp_honourificsuffix,
    sp_hospitalaffiliation, sp_hostingorganisation, sp_hoursavailable, sp_howperformed, sp_httpmethod,

    sp_iatacode, sp_identifier, sp_identifyingexam, sp_identifyingtest, sp_illustrator, sp_image, sp_imagingtechnique, sp_inalbum, sp_inbroadcastlineup, sp_incentives, sp_incentivecompensation, sp_inchi, sp_inchikey, sp_includedcomposition,
    sp_includeddatacatalog, sp_includedinhealthinsuranceplan, sp_includedriskfactor, sp_includesattraction, sp_includeshealthplanformulary, sp_includeshealthplannetwork, sp_includesobject, sp_incodeset, sp_increasesriskof,
    sp_indefinedtermset, sp_indication, sp_industry, sp_ineligibleregion, sp_infectiousagent, sp_infectiousagentclass, sp_ingredients, sp_inker, sp_inlanguage, sp_inplaylist, sp_inproductgroupwithid, sp_insertion, sp_installurl,
    sp_instorereturnsoffered, sp_instructor, sp_instrument, sp_insupportof, sp_intensity, sp_interactingdrug, sp_interactioncount, sp_interactionservice, sp_interactionstatistic, sp_interactiontype, sp_interactivitytype, sp_interestrate,
    sp_interpretedasclaim, sp_inventorylevel, sp_inverseof, sp_isacceptingnewpatients, sp_isaccessibleforfree, sp_isaccessoryorsparepartfor, sp_isavailablegenerally, sp_isbasedon, sp_isbasedonurl, sp_isbn, sp_isconsumablefor,
    sp_isencodedbybiochementity, sp_isfamilyfriendly, sp_isgift, sp_isicv4, sp_isinvolvedinbiologicalprocess, sp_islocatedinsubcellularlocation, sp_islivebroadcast, sp_iso6523code, sp_ispartof, sp_ispartofbiochementity,
    sp_isplanforapartment, sp_isproprietary, sp_isrccode, sp_isrelatedto, sp_isresizable, sp_issimilarto, sp_issn, sp_issuedby, sp_issuedthrough, sp_issuenumber, sp_isunlabelledfallback, sp_isvariantof, sp_iswccode, sp_item,
    sp_itemcondition, sp_itemdefectreturnfees, sp_itemdefectreturnlabelsource, sp_itemdefectreturnshippingfeesamount, sp_itemlistelement, sp_itemlistorder, sp_itemlocation, sp_itemoffered, sp_itemreviewed, sp_itemshipped, sp_itinerary,
    sp_iupacname,

    sp_jobbenefits, sp_jobimmediatestart, sp_joblocation, sp_joblocationtype, sp_jobstartdate, sp_jobtitle, sp_jurisdiction,

    sp_keywords, sp_knownvehicledamages, sp_knows, sp_knowsabout, sp_knowslanguage,

    sp_labeldetails, sp_landlord, sp_language, sp_lastreviewed, sp_latitude, sp_layoutimage, sp_learningresourcetype, sp_leaselength, sp_legalname, sp_legalstatus, sp_legislationapplies, sp_legislationchanges,
    sp_legislationconsolidates, sp_legislationdate, sp_legislationdateversion, sp_legislationidentifier, sp_legislationjurisdiction, sp_legislationlegalforce, sp_legislationlegalvalue, sp_legislationpassedby,
    sp_legislationresponsible, sp_legislationtransposes, sp_legislationtype, sp_leicode, sp_lender, sp_lesser, sp_lesserorequal, sp_letterer, sp_license, sp_line, sp_linkrelationship, sp_liveblogupdate,
    sp_loanmortgagamandateamount, sp_loanpaymentamount, sp_loanpaymentfrequency, sp_loanrepaymentform, sp_loanterm, sp_loantype, sp_location, sp_locationcreated, sp_lodgingunitdescription, sp_lodgingunittype,
    sp_logo, sp_longitude, sp_loser, sp_lowprice, sp_lyricist, sp_lyrics,

    sp_maincontentofpage, sp_mainentity, sp_mainentityofpage, sp_maintainer, sp_makesoffer, sp_manufacturer, sp_map, sp_maps, sp_maptype, sp_marginoferror, sp_masthead, sp_material, sp_materialextent, sp_mathexpression,
    sp_maximumattendeecapacity, sp_maximumenrollment, sp_maximumintake, sp_maximumphysicalattendeecapacity, sp_maximumvirtualattendeecapacity, sp_maxprice, sp_maxvalue, sp_mealservice, sp_measuredproperty, sp_measuredvalue,
    sp_measurementdenominator, sp_measurementmethod, sp_measurementqualifier, sp_measurementtechnique, sp_mechanismofaction, sp_mediaauthenticitycategory, sp_mediaitemappearance, sp_median, sp_medicalaudience,
    sp_medicalspeciality, sp_medicinesystem, sp_meetsemissionstandard, sp_member, sp_memberof, sp_members, sp_membershipnumber, sp_membershippointsearned, sp_memoryrequirements, sp_mentions, sp_menu, sp_menuaddon,
    sp_merchant, sp_merchantreturndays, sp_merchantreturnlink, sp_messageattachment, sp_mileagefromodometer, sp_minimummonthlyrepaymentamount, sp_minimumpaymentdue, sp_minprice, sp_minvalue, sp_missioncoverageprioritiespolicy,
    sp_model, sp_modeldate, sp_modifiedtime, sp_molecularformula, sp_molecularweight, sp_monoistopicmolecularweight, sp_monthsofexperience, sp_mpn, sp_multiplevalues, sp_muscleaction, sp_musicalkey, sp_musicarrangement,
    sp_musicby, sp_musiccompositionform, sp_musicgroupmember, sp_musicreleaseformat,

    sp_naics, sp_name, sp_nationality, sp_naturalprogression, sp_negativenotes, sp_nerve, sp_nervemotor, sp_networth, sp_newupdatesandguidelines, sp_nextitem, sp_nobylinespolicy, sp_nonequal, sp_nonprofitstatus,
    sp_nonproprietaryname, sp_normalrange, sp_nsn, sp_numadults, sp_numberedposition, sp_numberofaccommodationunits, sp_numberofairbags, sp_numberofavailableaccommodationunits, sp_numberofaxles, sp_numberofbathroomstotal,
    sp_numberofbedrooms, sp_numberofbeds, sp_numberofcredits, sp_numberofdoors, sp_numberofemployees, sp_numberofepisodes, sp_numberofforwardgears, sp_numberoffullbathrooms, sp_numberofitems, sp_numberofloanpayments,
    sp_numberofpages, sp_numberofpartialbathrooms, sp_numberofplayers, sp_numberofpreviousowners, sp_numberofrooms, sp_numberofseasons, sp_numchildren, sp_numconstraints, sp_numtracks, sp_nutrition,

    sp_object, sp_observationdate, sp_observationperiod, sp_observednode, sp_ocaocode, sp_occupancy, sp_occupationalcategory, sp_occupationalcredentialawarded, sp_occupationlocation, sp_offercount, sp_offeredby, sp_offers,
    sp_offersprescriptionbymail, sp_openinghours, sp_openinghoursspecification, sp_opens, sp_operatingsystem, sp_oponent, sp_opponent, sp_orderdate, sp_orderdelivery, sp_ordereditem, sp_orderitemnumber, sp_orderitemstatus,
    sp_ordernumber, sp_orderquantity, sp_orderstatus, sp_organiser, sp_origin, sp_originaddress, sp_originalmediacontentdescription, sp_originalmedialink, sp_originatesfrom, sp_outcome, sp_overdosage, sp_overview, sp_ownedfrom,
    sp_ownedto, sp_ownershipfundinginfo, sp_owns,

    sp_pageend, sp_pagestart, sp_pagination, sp_parent, sp_parentitem, sp_parentorganisation, sp_parents, sp_parentservice, sp_parenttaxon, sp_participant, sp_partofepisode, sp_partofinvoice, sp_partoforder, sp_partofseason,
    sp_partofseries, sp_partofsystem, sp_partoftrip, sp_partoftvseries, sp_partysize, sp_passengerprioritystatus, sp_passengersequencenumber, sp_pathophysiology, sp_pattern, sp_payload, sp_paymentaccepted, sp_paymentdue,
    sp_paymentduedate, sp_paymentmethod, sp_paymentmethodid, sp_paymentstatus, sp_paymenturl, sp_penciler, sp_percentile10, sp_percentile25, sp_percentile75, sp_percentile90, sp_performer, sp_performers, sp_performerin,
    sp_performtime, sp_permissions, sp_permissiontype, sp_permitaudience, sp_permittedusage, sp_petsallowed, sp_phase, sp_phonetictext, sp_photo, sp_photos, sp_physicalrequirement, sp_physiologicalbenefits, sp_pickuplocation,
    sp_pickuptime, sp_playersonline, sp_playertype, sp_playmode, sp_polygon, sp_population, sp_populationtype, sp_potentialuse, sp_position, sp_positivenotes, sp_possiblecomplication, sp_possibletreatment,
    sp_postalcode, sp_postalcodebegin, sp_postalcodeend, sp_postalcodeprefix, sp_postalcoderange, sp_postofficeboxnumber, sp_postop, sp_potentialaction, sp_practicesat, sp_predecessorof, sp_pregnancycategory, sp_pregnancywarning, sp_preop,
    sp_preparation, sp_preptime, sp_prescribinginfo, sp_prescriptionstatus, sp_previousitem, sp_previousstartdate, sp_price, sp_pricecomponent, sp_pricecomponenttype, sp_pricecurrency, sp_pricerange, sp_pricespecification,
    sp_pricetype, sp_pricevaliduntil, sp_primaryimageofpage, sp_primaryprevention, sp_printcolumn, sp_printedition, sp_printpage, sp_printsection, sp_procedure, sp_proceduretype, sp_processingtime, sp_processorrequirements,
    sp_producer, sp_produces, sp_productgroupid, sp_productid, sp_productioncompany, sp_productiondate, sp_productreturndays, sp_productreturnlink, sp_productsupported, sp_proficiencylevel, sp_programmemembershipused,
    sp_programmename, sp_programminglanguage, sp_programmingmodel, sp_programprequisites, sp_programtype, sp_propertyid, sp_propriatryname, sp_proprietaryname, sp_proteincontent, sp_provider, sp_providermobility,
    sp_providesbroadcastservice, sp_providesservice, sp_publicaccess, sp_publication, sp_publicationtype, sp_publictransportclosuresinfo, sp_publishedby, sp_publishedon, sp_publisher, sp_publisherimprint, sp_publishingprinciples,
    sp_purchasedate, sp_purpose,

    sp_qualifications, sp_quarantineguidelines, sp_query, sp_quest, sp_question,

    sp_rangeincludes, sp_ratingcount, sp_ratingexplanation, sp_ratingvalue, sp_readby, sp_readonlyvalue, sp_realestateagent, sp_recipe, sp_recipecategory, sp_recipecuisine, sp_recipeingredient, sp_recipeinstructions, sp_recipeyield,
    sp_recipient, sp_recognisedby, sp_recognisingauthority, sp_recommendationstrength, sp_recommendedintake, sp_recordedas, sp_recordedat, sp_recordedin, sp_recordingof, sp_recordlabel, sp_recourseloan, sp_referencequantity,
    sp_referencesorder, sp_refundtype, sp_regiondrained, sp_regionsallowed, sp_relatedanatomy, sp_relatedcondition, sp_relateddrug, sp_relatedlink, sp_relatedstructure, sp_relatedtherapy, sp_relatedto, sp_releasedate, sp_releasedevent,
    sp_releasenotes, sp_releaseof, sp_relevantoccupation, sp_relevantspeciality, sp_remainingattendeecapacity, sp_renegotiableloan, sp_repeatcount, sp_repeatfrequency, sp_repetitions, sp_replacee, sp_replacer, sp_replytourl,
    sp_reportnumber, sp_representativeofpage, sp_requiredcollateral, sp_requiredgender, sp_requiredmaxage, sp_requiredminage, sp_requiredquantity, sp_requirements, sp_requiressubscription, sp_reservationfor, sp_reservationid, sp_reservationstatus,
    sp_reservedticket, sp_responsibilities, sp_restockingfee, sp_restperiods, sp_result, sp_resultcomment, sp_resultreview, sp_returnfees, sp_returnlabelsource, sp_returnmethod, sp_returnpolicycategory, sp_returnpolicycountry,
    sp_returnpolicyseasonaloverride, sp_returnshippingfeesamount, sp_review, sp_reviews, sp_reviewaspect, sp_reviewbody, sp_reviewcount, sp_reviewedby, sp_reviewrating,
    sp_riskfactor, sp_risks, sp_rolename, sp_roofload, sp_rsvpresponse, sp_runsto, sp_runtime, sp_runtimeplatform, sp_rxcui,

    sp_safetyconsideration, sp_salarycurrency, sp_salaryuponcompletion, sp_sameas, sp_sampletype, sp_saturatedfatcontent, sp_scheduledpaymentdate, sp_scheduledtime, sp_scheduletimezone, sp_schemaversion,
    sp_schoolclosuresinfo, sp_screencount, sp_screenshot, sp_sddatepublished, sp_sdlicence, sp_sdpublisher, sp_season, sp_seasons, sp_seasonnumber, sp_seatingcapacity, sp_seatingtype, sp_seatnumber, sp_seatrow,
    sp_seatsection, sp_secondaryprevention, sp_securityclearancerequirement, sp_securityscreening, sp_seeks, sp_seller, sp_sender, sp_sensoryclearancerequirement, sp_sensoryunit, sp_serialnumber,
    sp_seriousadverseoutcome, sp_serverstatus, sp_servescuisine, sp_servicearea, sp_serviceaudience, sp_servicelocation, sp_serviceoperator, sp_serviceoutput, sp_servicephone, sp_servicepostaladdress,
    sp_servicesmsnumber, sp_servicetype, sp_serviceurl, sp_servingsize, sp_sha256, sp_sharedcontent, sp_shippingdestination, sp_shippinglabel, sp_shippingorigin, sp_shippingrate,
    sp_shippingsettingslink, sp_sibling, sp_siblings, sp_signdetected, sp_significance, sp_significantlink, sp_significantlinks, sp_signorsymptom, sp_size, sp_sizegroup, sp_sizesystem, sp_skills, sp_sku, sp_slogan, sp_smiles, sp_smokingallowed, sp_sodiumcontent, sp_softwareaddon, sp_softwarehelp,
    sp_softwarerequirements, sp_softwareversion, sp_source, sp_sourcedfrom, sp_sourceorganisation, sp_spatial, sp_spatialcoverage, sp_speakable, sp_specialcommitments, sp_speciality, sp_specialopeninghoursspecification,
    sp_speechtotextmarkup, sp_speed, sp_spokenbycharacter, sp_sponsor, sp_sport, sp_sportsactivitylocation, sp_sportsevent, sp_sportsteam, sp_spouse, sp_stage, sp_stageasnumber, sp_starrating, sp_startdate, sp_startoffset,
    sp_starttime, sp_stattype, sp_status, sp_steeringposition, sp_step, sp_steps, sp_stepvalue, sp_storagerequirements, sp_streetaddress, sp_strengthunit, sp_strengthvalue, sp_structuralclass, sp_study, sp_studydesign, sp_studylocation, sp_studysubject,
    sp_stupidproperty, sp_subevent, sp_subevents, sp_subjectof, sp_suborganisation, sp_subreservation, sp_substagesuffix, sp_substructure, sp_subtitlelanguage, sp_subtrip, sp_subtype, sp_successorof, sp_sugarcontent, sp_suggestedage, sp_suggestedanswer,
    sp_suggestedgender, sp_suggestedmaxage, sp_suggestedmeasurement, sp_suggestedminage, sp_suitablefordiet, sp_superevent, sp_supersededby, sp_supply, sp_supplyto, sp_supportingdata, sp_syllabussections,

    sp_target, sp_targetcollection, sp_targetdescription, sp_targetname, sp_targetplatform, sp_targetpopulation, sp_targetproduct, sp_targeturl, sp_taxid, sp_taxonomicrange, sp_taxonrank, sp_teaches, sp_telephone, sp_temporal, sp_temporalcoverage, sp_termcode, sp_termduration,
    sp_termsofservice, sp_termsperyear, sp_text, sp_textvalue, sp_thumbnail, sp_thumbnailurl, sp_tickersymbol, sp_ticketedseat, sp_ticketnumber, sp_tickettoken, sp_timeofday, sp_timerequired, sp_timetocomplete, sp_tissuesample,
    sp_title, sp_titleeidr, sp_toccontinuation, sp_tocentry, sp_tolocation, sp_tongueweight, sp_tool, sp_torecipient, sp_torque, sp_totalhistoricalenrollment, sp_totaljobopenings, sp_totalpaymentdue, sp_totalprice, sp_totaltime, sp_tourbookingpage, sp_touristtype, sp_track, sp_tracks, sp_trackingnumber,
    sp_trackingurl, sp_trailer, sp_trailerweight, sp_trainingsalary, sp_trainname, sp_trainnumber, sp_transcript, sp_transfatcontent, sp_transittime, sp_transittimelabel, sp_translationofwork, sp_translator, sp_transmissionmethod,
    sp_travelbans, sp_trialdesign, sp_tributary, sp_triporigin, sp_typeofbed, sp_typeofgood, sp_typicalagerange, sp_typicalcreditsperterm, sp_typicaltest,

    sp_undername, sp_unitcode, sp_unittext, sp_unnamedsourcespolicy, sp_unsaturatedfatcontent, sp_uploaddate, sp_upvotecount, sp_url, sp_urltemplate, sp_usageinfo, sp_usedtodiagnose, sp_userinteractioncount, sp_usesdevice,
    sp_useshealthplanidstandard, sp_usnpi, sp_utterances,

    sp_validfor, sp_validfrom, sp_validin, sp_validto, sp_validuntil, sp_value, sp_valueaddedtaxincluded, sp_valuemaxlength, sp_valueminlength, sp_valuename, sp_valuepattern, sp_valuereference, sp_valuerequired,
    sp_variablemeasured, sp_variablesmeasured, sp_variantcover, sp_variesby, sp_vatid, sp_vehicleconfiguration, sp_vehicleengine, sp_vehicleidentificationnumber, sp_vehicleinteriorcolour, sp_vehicleinteriortype, sp_vehiclemodeldate,
    sp_vehicleseatingcapacity, sp_vehiclespecialusage, sp_vehicletransmission, sp_vendor, sp_verificationfactcheckingpolicy, sp_version, sp_video, sp_videoformat, sp_videoframesize, sp_videoquality, sp_volumenumber,

    sp_warning, sp_warranty, sp_warrantypromise, sp_warrantyscope, sp_webcheckintime, sp_webfeed, sp_weight, sp_weighttotal, sp_wheelbase, sp_width, sp_winner, sp_wordcount, sp_workexample, sp_workfeatured, sp_workhours, sp_workload, sp_worklocation,
    sp_workperformed, sp_workpresented, sp_worksfor, sp_worktranslation, sp_worstrating,

    sp_xpath,

    sp_yearbuilt, sp_yearlyrevenue, sp_yearsinoperation, sp_yield,

    // sd
    sdp_availablegraphs,
    sdp_defaultdataset, sdp_defaultentailmentregime, sdp_defaultgraph, sdp_defaultsupportedentailmentprofile,
    sdp_endpoint, sdp_entailmentregime, sdp_extensionaggregate, sdp_extensionfunction,
    sdp_feature,
    sdp_graph,
    sdp_inputformat,
    sdp_languageextension,
    sdp_name, sdp_namedgraph,
    sdp_propertyfeature,
    sdp_resultformat,
    sdp_supportedentailmentprofile, sdp_supportedlanguage,

    // sioc
    sioc_about, sioc_account_of, sioc_administrator_of, sioc_attachment, sioc_avatar,
    sioc_container_of, sioc_content, sioc_creator_of,
    sioc_email, sioc_email_sha1,
    sioc_feed, sioc_function_of,
    sioc_has_administrator, sioc_has_container, sioc_has_creator, sioc_has_function, sioc_has_host, sioc_has_member, sioc_has_moderator, sioc_has_modifier, sioc_has_owner, sioc_has_parent, sioc_has_reply, sioc_has_scope,
        sioc_has_space, sioc_has_subscriber, sioc_has_usergroup, sioc_host_of,
    sioc_id, sioc_ip_address,
    sioc_link, sioc_links_to,
    sioc_member_of, sioc_moderator_of, sioc_modifier_of,
    sioc_name, sioc_next_by_date, sioc_next_version, sioc_note, sioc_num_replies, sioc_num_views,
    sioc_owner_of,
    sioc_parent_of, sioc_previous_by_date, sioc_previous_version,
    sioc_related_to, sioc_reply_of,
    sioc_scope_of, sioc_sibling, sioc_space_of, sioc_subscriber_of,
    sioc_topic,
    sioc_usergroup_of,

    // skos
    skos_altlabel,
    skos_broadmatch, skos_broader, skos_broadertransitive,
    skos_changenote, skos_closematch,
    skos_definition,
    skos_editorialnote, skos_exactmatch, skos_example,
    skos_hastopconcept, skos_hiddenlabel, skos_historynote,
    skos_inscheme,
    skos_mappingrelation, skos_member, skos_memberlist,
    skos_narrowmatch, skos_narrower, skos_narrowertransitive, skos_notation, skos_note,
    skos_preflabel,
    skos_related, skos_relatedmatch,
    skos_scopenote, skos_semanticrelation,
    skos_topconceptof,

    // skosxl
    skosxl_altlabel, skosxl_hiddenlabel, skosxl_labelrelation, skosxl_literalform, skosxl_preflabel,

    // sosa
    sosa_actsonproperty,
    sosa_hasfeatureofinterest, sosa_hasresult, sosa_hassample, sosa_hassimpleresult,
    sosa_hosts,
    sosa_isacteduponby, sosa_isfeatureofinterest, sosa_ishostedby, sosa_isobservedby, sosa_isresultof, sosa_issampleof,
    sosa_madeactuation, sosa_madebyactuator, sosa_madebysampler, sosa_madebysensor, sosa_madeobservation, sosa_madesampling,
    sosa_observedproperty, sosa_observes,
    sosa_phenomenontime,
    sosa_resulttime,
    sosa_usedprocedure,

    // ssn
    ssn_deployedplatform, ssn_deployedsystem, ssn_detects,
    ssn_forproperty,
    ssn_hasdeployment, ssn_hasinput, ssn_hasoutput, ssn_hasproperty, ssn_hassubsystem,
    ssn_implements, ssn_indeployment, ssn_isimplementedby, ssn_ispropertyof, ssn_isproxyfor,
    ssn_wasoriginatedby,

    // adobe
    stdim_h, stdim_unit, stdim_w,
    stevt_action, stevt_changed, stevt_instanceid, stevt_parameters, stevt_softwareagent, stevt_when,
    stfnt_childfontfiles, stfnt_composite, stfnt_fontface, stfnt_fontfamily, stfnt_fontfilename, stfnt_fontname, stfnt_fonttype, stfnt_versionstring,
    stjob_id, stjob_name, stjob_url,
    stref_alternativepaths, stref_documentid, stref_filepath, stref_frompart, stref_instanceid, stref_lastmodifydate, stref_manager, stref_managervariant, 
        stref_manageto, stref_manageui, stref_maskmarkers, stref_partmapping, stref_renditionclass, stref_renditionparams, stref_topart, stref_versionid,
    stver_comments, stver_event, stver_modifier, stver_modifydate, stver_version,

    // tiff
    tiff_bitspersample,
    tiff_compression,
    tiff_imagelength, tiff_imagewidth,
    tiff_make, tiff_model,
    tiff_orientation,
    tiff_photometricinterpretation, tiff_planarconfiguration, tiff_primarychromaticities,
    tiff_referenceblackwhite, tiff_resolutionunit,
    tiff_samplesperpixel,
    tiff_transferfunction,
    tiff_whitepoint,
    tiff_xresolution,
    tiff_ycbrcrcoefficients, tiff_ycbrcrpositioning, tiff_ycbrcrsubsampling, tiff_yresolution,

    // time
    tp_after,
    tp_before,
    tp_day, tp_days, tp_dayofweek, tp_dayofyear,
    tp_generalday, tp_generalmonth, tp_generalyear,
    tp_hasbeginning, tp_hasdatetimedescription, tp_hasduration, tp_hasdurationdescription, tp_hasend, tp_hastrs, tp_hastemporalduration, tp_hastime, tp_hasxsduration, tp_hour, tp_hours,
    tp_indatetime, tp_intemporalposition, tp_intimeposition, tp_inxsddate, tp_inxsddatetime, tp_inxsddatetimestamp, tp_inxsdgyear, tp_inxsdgyearmonth, tp_inside, tp_intervalafter, tp_intervalbefore,
        tp_intervalcontains, tp_intervaldisjoint, tp_intervalduring, tp_intervalequals, tp_intervalfinishedby, tp_intervalfinishes, tp_intervalin, tp_intervalmeets, tp_intervalmetby,
        tp_intervaloverlappedby, tp_intervaloverlaps, tp_intervalstartedby, tp_intervalstarts,
    tp_minute, tp_minutes, tp_month, tp_monthofyear, tp_months,
    tp_nominalposition, tp_numericduration, tp_numericposition,
    tp_second, tp_seconds,
    tp_timezone,
    tp_week, tp_weeks,
    tp_year, tp_years,

    // data vocabulary
    v_acquaintance, v_address, v_adr, v_affiliation, v_availability,
    v_best, v_brand,
    v_category, v_child, v_condition, v_contact, v_count, v_countryname, v_currency,
    v_description, v_dtreviewed, v_duration,
    v_enddate, v_eventtype,
    v_fn, v_friend,
    v_geo,
    v_highprice,
    v_identifier, v_image, v_item, v_itemoffered, v_itemreviewed,
    v_latitude, v_locality, v_location, v_longitude, v_lowprice,
    v_name, v_nickname,
    v_offercount, v_offerdetails, v_offerurl, v_org,
    v_photo, v_postcode, v_price, v_pricevaliduntil,
    v_rating, v_region, v_reviewed, v_reviewer, v_role,
    v_seller, v_startdate, v_streetaddress, v_summary,
    v_title,
    v_url,
    v_votes,
    v_worst,

    // vann
    vann_changes, vann_example, vann_pnp, vann_pnu, vann_termgroup, vann_usagenote,

    // vcard
    vcard_additional_name, vcard_adr, vcard_agent, vcard_anniversary,
    vcard_bday,
    vcard_caladruri, vcard_caluri, vcard_category, vcard_categories, vcard_class, vcard_clientpidmap, vcard_country, vcard_country_name,
    vcard_pemail, vcard_extadd, vcard_extended_address,
    vcard_family, vcard_family_name, vcard_fburl, vcard_fn,
    vcard_gender, vcard_geo, vcard_given, vcard_given_name, vcard_group,
    vcard_hasadditionalname, vcard_hasaddress, vcard_hascalendarbusy, vcard_hascalendarrequest, vcard_hascalendarlink, vcard_hascategory, vcard_hascountryname, vcard_hasemail, vcard_hasfax,
        vcard_hasfn, vcard_hasfamilyname, vcard_hasgender, vcard_hasgeo, vcard_hasgivenname,
        vcard_hashonourificprefix, vcard_hashonourificsuffix, vcard_hasinstantmessage, vcard_haskey, vcard_haslanguage, vcard_haslocality, vcard_haslogo, vcard_hasmember,
        vcard_hasname, vcard_hasnickname, vcard_hasnote, vcard_hasorganisationname, vcard_hasorganisationunit, vcard_hasphoto, vcard_haspostcode, vcard_hasregion, vcard_hasrelated, vcard_hasrole, vcard_hasstreetaddress,
        vcard_hastelephone, vcard_hastitle, vcard_hasvalue, vcard_homeadr, vcard_hometel, vcard_honourific_prefix, vcard_honourific_suffix,
    vcard_impp,
    vcard_key, vcard_kind,
    vcard_labelp, vcard_lang, vcard_latitude, vcard_locality, vcard_logo, vcard_longitude,
    vcard_mailer, vcard_member, vcard_mobileemail, vcard_mobiletel,
    vcard_n, vcard_pname, vcard_nickname, vcard_note,
    vcard_other, vcard_org, vcard_organisation_name, vcard_organisation_unit, vcard_organisational_unit, vcard_orgname, vcard_orgunit,
    vcard_pcode, vcard_personalemail, vcard_phone, vcard_photo, vcard_pobox, vcard_post_office_box, vcard_postcode, vcard_ppref, vcard_prefix, vcard_prodid, vcard_profile,
    vcard_region, vcard_related, vcard_rev, vcard_role,
    vcard_sort_string, vcard_sound, vcard_source, vcard_street, vcard_street_address, vcard_suffix,
    vcard_title, vcard_type, vcard_tz,
    vcard_uid, vcard_unlabeledadr, vcard_unlabeledemail, vcard_unlabeledtel, vcard_url,
    vcard_value,
    vcard_workadr, vcard_workemail, vcard_worktel,
    vcard_xml,

    // void
    void_class, void_classes, void_classpartition,
    void_datadump, void_distinctobjects, void_distinctsubjects, void_documents,
    void_entities, void_exampleresource,
    void_feature,
    void_indataset,
    void_linkpredicate,
    void_objectstarget, void_opensearchdescription,
    void_properties, void_property, void_propertypartition,
    void_rootresource,
    void_sparqlendpoint, void_subjectstarget, void_subset,
    void_target, void_triples,
    void_urilookupendpoint, void_uriregexpattern, void_urispace,
    void_vocabulary,

    // wdr
    wdr_abouthosts,
    wdr_delimiter,
    wdr_excludeexactpaths, wdr_excludehosts, wdr_excludeiripattern, wdr_excludepathcontains, wdr_excludepathendswith, wdr_excludepathstartswith, wdr_excludequerycontains, wdr_excludeports, wdr_excluderesources, wdr_excludeschemes,
    wdr_includeexactpaths, wdr_includehosts, wdr_includeiripattern, wdr_includepathcontains, wdr_includepathendswith, wdr_includepathstartswith, wdr_includequerycontains, wdr_includeports, wdr_includeresources, wdr_includeschemes,

    // wdrs
    wdrs_authenticate,
    wdrs_certified, wdrs_certifiedby,
    wdrs_data_error, wdrs_describedby,
    wdrs_error_code,
    wdrs_hasiri,
    wdrs_issuedby,
    wdrs_logo,
    wdrs_matchesregex,
    wdrs_notknownto, wdrs_notmatchesregex,
    wdrs_proc_error,
    wdrs_sha1sum, wdrs_supportedby,
    wdrs_tag, wdrs_text,
    wdrs_validfrom, wdrs_validuntil,

    // whatwg
    wp_author, wp_license, wp_title, wp_work,

    // xhv
    xhv_alert, xhv_alertdialog, xhv_alternate, xhv_appendix, xhv_application, xhv_article,
    xhv_banner, xhv_bookmark, xhv_button,
    xhv_chapter, xhv_checkbox, xhv_cite, xhv_columnheader, xhv_combobox, xhv_complementary, xhv_contentinfo, xhv_contents, xhv_copyright,
    xhv_definition, xhv_dialog, xhv_directory, xhv_document,
    xhv_first, xhv_form,
    xhv_glossary, xhv_grid, xhv_gridcell, xhv_group,
    xhv_heading, xhv_help,
    xhv_icon, xhv_img, xhv_index, xhv_itsrules,
    xhv_last, xhv_license, xhv_link, xhv_list, xhv_listbox, xhv_listitem, xhv_log,
    xhv_main, xhv_marquee, xhv_math, xhv_menu, xhv_menubar, xhv_menuitem, xhv_menuitemcheckbox, xhv_menuitemradio, xhv_meta,
    xhv_navigation, xhv_next, xhv_note,
    xhv_option,
    xhv_p3pv1, xhv_presentation, xhv_prev, xhv_progressbar,
    xhv_radio, xhv_radiogroup, xhv_region, xhv_role, xhv_row, xhv_rowgroup, xhv_rowheader,
    xhv_scrollbar, xhv_search, xhv_section, xhv_separator, xhv_slider, xhv_spinbutton, xhv_start, xhv_status, xhv_stylesheet, xhv_subsection,
    xhv_tab, xhv_tablist, xhv_tabpanel, xhv_textbox, xhv_timer, xhv_toolbar, xhv_tooltip, xhv_top, xhv_tree, xhv_treegrid, xhv_treeitem,
    xhv_up,

    // adobe
    xmp_advisory, xmp_baseurl, xmp_createdate, xmp_creatortool, xmp_identifier, xmp_label, xmp_metadatadate, xmp_modifydate, xmp_nickname,
        xmp_rating, xmp_thumbnails,
    xmpbj_jobref,

    xmpdm_abspeakaudiofilepath, xmpdm_album, xmpdm_alttapename, xmpdm_alttimecode, xmpdm_artist, xmpdm_audiomoddate, xmpdm_audiochanneltype,
        xmpdm_audiocompressor, xmpdm_audiosamplerate, xmpdm_audiosampletype,
    xmpdm_beatspliceparams,
    xmpdm_cameraangle, xmpdm_cameralabel, xmpdm_cameramodel, xmpdm_cameramove, xmpdm_client, xmpdm_comment, xmpdm_composer, xmpdm_contributedmedia,
        xmpdm_copyright, xmpdm_cuepointparams, xmpdm_cuepointtype,
    xmpdm_director, xmpdm_directorphotography, xmpdm_discnumber, xmpdm_duration,
    xmpdm_engineer,
    xmpdm_filedatarate, xmpdm_frameoverlappingpercentage, xmpdm_framerate, xmpdm_framesize,
    xmpdm_genre, xmpdm_good,
    xmpdm_instrument, xmpdm_introtime,
    xmpdm_key,
    xmpdm_location, xmpdm_logcomment, xmpdm_loop, xmpdm_lyrics,
    xmpdm_managed, xmpdm_markers, xmpdm_metadatamoddate,
    xmpdm_name, xmpdm_numberofbeats,
    xmpdm_outcue,
    xmpdm_partofcompilation, xmpdm_path, xmpdm_probability, xmpdm_projectname, xmpdm_projectref, xmpdm_pulldown,
    xmpdm_quality,
    xmpdm_relativepeakaudiofilepath, xmpdm_relativetimestamp, xmpdm_releasedate, xmpdm_resampleparams, xmpdm_riseindecibel, xmpdm_riseintimeduration,
    xmpdm_scale, xmpdm_scaletype, xmpdm_scene, xmpdm_shotdate, xmpdm_shotday, xmpdm_shotlocation, xmpdm_shotname, xmpdm_shotnumber, xmpdm_shotsize,
        xmpdm_speaker, xmpdm_speakerplacement, xmpdm_starttime, xmpdm_starttimecode, xmpdm_stretchmode,
    xmpdm_takenumber, xmpdm_tapename, xmpdm_target, xmpdm_tempo, xmpdm_timeformat, xmpdm_timescaleparams, xmpdm_timesignature, xmpdm_timevalue,
        xmpdm_track, xmpdm_trackname, xmpdm_tracknumber, xmpdm_tracks, xmpdm_tracktype, xmpdm_type,
    xmpdm_usefilebeatsmarker,
    xmpdm_value, xmpdm_videoalphamode, xmpdm_videoalphapremultiplecolour, xmpdm_videoalphaunitistransparent, xmpdm_videocolourspace,
        xmpdm_videocompressor, xmpdm_videofieldorder, xmpdm_videoframerate, xmpdm_videoframesize, xmpdm_videomoddate, xmpdm_videopixeldepth,
        xmpdm_videopixelaspectratio,
    xmpdm_webstatement,

    xmpg_a, xmpg_b, xmpg_black, xmpg_blue, xmpg_cyan, xmpg_green, xmpg_l, xmpg_magenta, xmpg_mode, xmpg_red, xmpg_swatchname, xmpg_type, xmpg_yellow,
    xmpgimg_format, xmpgimg_height, xmpgimg_image, xmpgimg_weight,
    xmpi_scheme,
    xmpmm_derivedfrom, xmpmm_documentid, xmpmm_history, xmpmm_ingredients, xmpmm_instanceid, xmpmm_lasturl, xmpmm_managedfrom, xmpmm_manager,
        xmpmm_manageto, xmpmm_manageui, xmpmm_managervariant, xmpmm_originaldocumentid, xmpmm_pantry, xmpmm_renditionclass, xmpmm_renditionof,
        xmpmm_renditionparams, xmpmm_saveid, xmpmm_versionid, xmpmm_versions,
    xmpr_certificate, xmpr_marked, xmpr_owner, xmpr_usageterms, xmpr_webstatement,
    xmptpg_colourants, xmptpg_fonts, xmptpg_maxpagesize, xmptpg_npages, xmptpg_platenames,

    op_illegal } e_ontology_property;

typedef ::std::vector < e_ontology_property > vsp_t;

#define SCHEMES pt_rfc3986, pt_rfc3986_ignore, pt_geo, pt_local, pt_news, pt_tel, pt_urn
typedef enum { SCHEMES } e_scheme;

typedef enum { s_auto, s_no, s_yes } e_scrolling;
typedef enum { st_normal, st_multiset } e_settype;
typedef enum { es_undefined, es_catastrophic, es_abhorrent, es_error, es_warning, es_info, es_comment, es_debug, es_variable, es_structure, es_detail, es_splurge, es_all, es_silent, es_illegal } e_severity;
const e_severity last_severity = es_all;

typedef enum {  doc_unknown, doc_context, doc_html, doc_public, doc_system, doc_math, doc_rdf, doc_svg, doc_xhtml,
                doc_math1, doc_math2, doc_math3, doc_math4,
                doc_rdfa_1_0, doc_rdfa_1_1,
                doc_svg10, doc_svg11, doc_svg20, doc_svg21,
                doc_jan05, doc_html5,
                doc_xhtml2,
                doc_xhtml11,
                doc_xhtml10_basic, doc_xhtml10_strict, doc_xhtml10_loose, doc_xhtml10_frameset, doc_xhtml10_mobile,
                doc_xhtml10_strict_superseded, doc_xhtml10_loose_superseded, doc_xhtml10_frameset_superseded,
                doc_html401_strict, doc_html401_loose, doc_html401_frameset,
                doc_html401_strict_superseded, doc_html401_loose_superseded, doc_html401_frameset_superseded,
                doc_html400_strict, doc_html400_loose, doc_html400_frameset,
                doc_latin, doc_special, doc_symbols,
                doc_html32, doc_html30,
                doc_html20, doc_html20_strict, doc_html20_int, doc_html21, doc_html21_strict, doc_html22, doc_html1, doc_html_tags,
                doc_htmlplus, doc_sqopen, doc_sqclose,
                doc_compound_m, doc_compound_1_0, doc_compound_1_1 } e_sgml;
const e_sgml last_sgml = doc_compound_1_1;

typedef enum { sh_error, sh_no, sh_pages, sh_hard, sh_soft, sh_copy, sh_dedu, sh_report } e_shadow;
typedef enum { sh_ondefine, sh_onuse, sh_none, sh_inherit } e_shadowinherit;
typedef enum { sh_circle, sh_default, sh_poly, sh_rect } e_shape4;
typedef enum { s7_circ, s7_default, s7_poly, s7_rect } e_shape7;
typedef enum { sie_auto, sie_display, sie_outside_shape } e_css_shape_inside_e;
typedef enum { rcp_circle, rcp_poly, rcp_rect } e_shape_rcp;
typedef enum { sr_auto, sr_optimisespeed, sr_crispedges, sr_geometricprecision, sr_inherit } e_shape_rendering;
typedef enum { sh_embed, sh_replace } e_show;
typedef enum { siz_normal, siz_medium, siz_large, siz_huge } e_size3;
typedef enum { esi_inline_size, esi_size } e_size_inlinesize;
typedef enum { smei_start, smei_middle, smei_end, smei_inherit } e_smei;
typedef enum {  // mostly from SVG 1.1 17.1.4 Processing of IRI references
                se_any, se_glyph_alt, se_clippath, se_icc_profile, se_colour_profile, se_image_file, se_paint_server, se_filter, se_gradient, se_marker, se_mask, se_pattern,
                se_script, se_path, se_svg, se_animation, se_error } e_sought_category;
typedef enum { sp_block, sp_horz, sp_vert } e_spacer;
typedef enum { spa_auto, spa_exact } e_spacing;
typedef enum { sm_reflect, sm_repeat, sm_pad } e_spreadmethod;
typedef enum { ssi_comment, ssi_config, ssi_echo, ssi_elif, ssi_else, ssi_endif, ssi_exec, ssi_flastmod, ssi_fsize, ssi_if, ssi_include, ssi_printenv, ssi_set } e_ssi;
typedef enum { ssi_comparison_and, ssi_comparison_eq, ssi_comparison_ge, ssi_comparison_gt, ssi_comparison_le, ssi_comparison_lt, ssi_comparison_ne, ssi_comparison_or } e_ssi_comparison;
typedef enum { ssi_config_echomsg, ssi_config_errmsg, ssi_config_sizefmt, ssi_config_timefmt } e_ssi_config;
typedef enum { ssi_echo_decoding, ssi_echo_encoding, ssi_echo_var } e_ssi_echo;
typedef enum { ssi_encoding_base64, ssi_encoding_none, ssi_encoding_entity, ssi_encoding_url, ssi_encoding_urlencoded } e_ssi_encoding;
typedef enum { ssi_DATE_GMT, ssi_DATE_LOCAL, ssi_DOCUMENT_ARGS, ssi_DOCUMENT_NAME, ssi_DOCUMENT_PATH_INFO, ssi_DOCUMENT_URI, ssi_LAST_MODIFIED, ssi_QUERY_STRING_UNESCAPED, ssi_USER_NAME, ssi_error } e_ssi_env;
typedef enum { ssi_f_file, ssi_f_virtual } e_ssi_f;
typedef enum { ssi_include_file, ssi_include_onerror, ssi_include_virtual } e_ssi_include;
typedef enum { ssi_set_decoding, ssi_set_encoding, ssi_set_value, ssi_set_var } e_ssi_set;
typedef enum { ssi_size_abbrev, ssi_size_bytes } e_ssi_sizefmt;
typedef enum { st_init, st_scan, st_priority, st_file, st_folder, st_max } e_stage; // must be in processing order
typedef enum { se_start, se_end } e_startend;
typedef enum { s_unset, s_invalid, s_empty, s_good } e_status;
typedef enum { sp_end, sp_jump_both, sp_jump_end, sp_jump_none, sp_jump_start, sp_start } e_step_position;
typedef enum { stt_stitch, stt_nostitch } e_stitchtiles;
typedef enum { sc_keep, sc_discard } e_streamedcontents;
typedef enum { str_moderate, str_none, str_normal, str_reduced, str_strong } e_stress;
typedef enum { su_none, su_font_format, su_font_tech, su_selector } e_supports;
typedef enum { sov_visible, sov_hidden, sov_scroll, sov_auto, sov_inherit } e_svg_overflow;
typedef enum { spm_none, spm_dynamic, spm_animated, spm_secure_animated, spm_static, spm_secure_static } e_svg_processing_mode;
typedef enum { sa_none, sa_xmin_ymin, sa_xmid_ymin, sa_xmax_ymin, sa_xmin_ymid, sa_xmid_ymid, sa_xmax_ymid, sa_xmin_ymax, sa_xmid_ymax, sa_xmax_ymax } e_svg_align;
typedef enum { sbp_basic, sbp_full, sbp_none, sbp_tiny } e_svg_baseprofile;
typedef enum { sd_ltr, sd_rtl, sd_inherit } e_svg_direction;
typedef enum { sd2_ltr, sd2_rtl } e_svg_direction2;
typedef enum {  ds_inline, ds_block, ds_listitem, ds_runin, ds_compact, ds_marker, ds_table, ds_inlinetable, ds_tablerowgroup, ds_tableheadergroup,
                ds_tablefootergroup, ds_tablerow, ds_tablecolumngroup, ds_tablecolumn, ds_tablecell, ds_tablecaption, ds_none, ds_inherit } e_svg_display;
typedef enum {
    sf_org_w3c_svg, sf_org_w3c_svg_static, sf_org_w3c_svg_animation, sf_org_w3c_svg_dynamic, sf_org_w3c_svg_all,
    sf_org_w3c_dom_svg, sf_org_w3c_dom_svg_static, sf_org_w3c_dom_svg_animation, sf_org_w3c_dom_svg_dynamic, sf_org_w3c_dom_svg_all,
    sf_svg, sf_svgdom, sf_svgstatic, sf_svgdomstatic, sf_svganimation, sf_svgdomanimation, sf_svgdynamic, sf_svgdomdynamic, sf_coreattribute, sf_structure,
    sf_basicstructure, sf_containerattribute, sf_conditionalprocessing, sf_image, sf_style, sf_viewportattribute, sf_shape, sf_text, sf_basictext, sf_paintattribute, sf_basicpaintattribute,
    sf_opacityattribute, sf_graphicsattribute, sf_basicgraphicsattribute, sf_marker, sf_colourprofile, sf_gradient, sf_pattern, sf_clip, sf_basicclip, sf_mask, sf_filter, sf_basicfilter,
    sf_documenteventsattribute, sf_graphicaleventsattribute, sf_animationeventsattribute, sf_cursor, sf_hyperlinking, sf_xlinkattribute, sf_externalresourcesrequired, sf_view, sf_script,
    sf_animation, sf_font, sf_basicfont, sf_extensibility, sf_scripting,
    sf_svgstatic2, sf_svgstaticdom, sf_svganimated, sf_svginteractive, sf_svgall, sf_coreattribute2, sf_navigationattribute, sf_structure2,
    sf_conditionalprocessing2, sf_conditionalprocessingattribute2, sf_image2, sf_prefetch2, sf_discard2, sf_shape2, sf_text2, sf_paintattribute2,
    sf_opacityattribute2, sf_graphicsattribute2, sf_gradient2, sf_solidcolour2, sf_hyperlinking2, sf_xlinkattribute2, sf_externalresourcesrequired2,
    sf_scripting2, sf_handler2, sf_listener2, sf_timedanimation2, sf_animation2, sf_audio2, sf_video2, sf_font2, sf_extensibility2, sf_mediaattribute2,
    sf_textflow2, sf_transformedvideo2, sf_composedvideo2, sf_editabletextattribute2
 } e_svg_feature;

typedef enum { fsw_normal, fsw_bold, fsw_bolder, fsw_lighter, fsw_100, fsw_200, fsw_300, fsw_400, fsw_500, fsw_600, fsw_700, fsw_800, fsw_900, fsw_inherit } e_svg_fontweight;
typedef enum { fsf_normal, fsf_bold, fsf_100, fsf_200, fsf_300, fsf_400, fsf_500, fsf_600, fsf_700, fsf_800, fsf_900 } e_svg_fontweight_ff;
typedef enum { sfs_normal, sfs_italic, sfs_oblique, sfs_inherit } e_svg_fontstyle;
typedef enum {  fst_normal, fst_wider, fst_narrower, fst_ultracondensed, fst_extracondensed, fst_condensed, fst_semicondensed, fst_semiexpanded, fst_expanded, fst_extraexpanded,
                fst_ultraexpanded, fst_inherit, fst_all } e_svg_fontstretch;
typedef enum { fff_normal, fff_ultracondensed, fff_extracondensed, fff_condensed, fff_semicondensed, fff_semiexpanded, fff_expanded, fff_extraexpanded, fff_ultraexpanded } e_svg_fontstretch_ff;
typedef enum { fv_normal, fv_smallcaps, fv_inherit } e_svg_fontvariant;
typedef enum { fvf_normal, fvf_smallcaps } e_svg_fontvariant_ff;
typedef enum { sme_align, sme_stretch } e_svg_method;
typedef enum {  sm_colour, sm_colour_dodge, sm_colour_burn, sm_darken, sm_difference, sm_exclusion, sm_hard_light, sm_hue, sm_lighten, sm_luminosity, sm_multiply, sm_normal, sm_saturation,
                sm_screen, sm_soft_light } e_svg_mode;
typedef enum { sp_default, sp_capture } e_svg_phase;
typedef enum { sbo_all, abo_forwardonly } e_svg_playbackorder;
typedef enum { sri_absolute_colourmetric, sri_auto, sri_perceptual, sri_relative_colourmetric, sri_saturation } e_svg_rendering_intent;
typedef enum { siv_left, siv_right } e_svg_side;
typedef enum { stb_onload, stb_onstart } e_svg_timelinebegin;
typedef enum { tsz_discrete, tsz_gamma, tsz_identity, tsz_linear, tsz_table } e_svg_type;
typedef enum { su_object_bbox, su_userspace } e_svg_units;
typedef enum { sv_none, sv_1_0, sv_1_1, sv_1_2_tiny, sv_1_2_full, sv_2_0, sv_2_1 } e_svg_version;
constexpr e_svg_version last_svg = sv_2_1;
typedef enum { svg_none, svg_1_0, svg_1_1, svg_1_2_tiny, svg_1_2_full, svg_2_0 } e_svg_version_grand;
typedef enum { sb_canslip, sb_locked, sb_independent, sb_default } e_syncbehaviour;
typedef enum { sbd_canslip, sbd_locked, sbd_independent, sbd_inherit } e_syncbehaviourdefault;
typedef enum { mt_m, mt_t } e_m_t;
typedef enum { fr_void, fr_above, fr_below, fr_hsides, fr_lhs, fr_rhs, fr_vsides, fr_box, fr_border } e_tableframe;
typedef enum { tb_bottom, tb_top } e_tbalign;
typedef enum { etb_bottom, etb_inherit, etb_inline_end, etb_inline_start, etb_left, etb_right, etb_top } e_tblri;
typedef enum { tcb_top, tcb_centre, tcb_bottom } e_tcbalign;
typedef enum { sc_row, sc_col, sc_rowgroup, sc_colgroup } e_tdscope;
typedef enum { eto_above, eto_below, eto_twosided } e_tendstotype;
typedef enum { td_none, td_underline, td_overline, td_linethrough, td_blink, td_inherit } e_text_decoration;
typedef enum { tr_auto, tr_optimisespeed, tr_optimiselegibility, tr_geometricprecision, tr_inherit } e_text_rendering;
typedef enum { ac_false, ac_mixed, ac_true, ac_undefined  } e_tfmu;
typedef enum { tfa_auto, tfa_false, tfa_true } e_tfa;
typedef enum { tfi_false, tfi_true, tfi_inherit } e_tfi;
typedef enum { tfu_false, tfu_true, tfu_undefined } e_tfu;

typedef enum
{   tld_context,
    tld_aaa, tld_aarp, tld_abarth, tld_abb, tld_abbott, tld_abbvie, tld_abc, tld_abogado, tld_abudhabi, tld_ac, tld_academy,
        tld_accenture, tld_accountant, tld_accountants, tld_aco, tld_active, tld_actor, tld_ad, tld_ads, tld_adult, tld_ae, tld_aeg,
        tld_aero, tld_aetna, tld_af, tld_afl, tld_africa, tld_ag, tld_agakhan, tld_agency, tld_ai, tld_aig, tld_aigo,
        tld_airbus, tld_airforce, tld_airtel, tld_akdn, tld_al, tld_alfaromeo, tld_alibaba, tld_alipay, tld_allfinanz, tld_allstate,
        tld_ally, tld_alsace, tld_alstom, tld_am, tld_amazon, tld_americanexpress, tld_amex, tld_amica, tld_amsterdam,
        tld_analytics, tld_android, tld_anz, tld_ao, tld_aol, tld_apartments, tld_app, tld_apple, tld_aq, tld_aquarelle,
        tld_ar, tld_arab, tld_aramco, tld_archi, tld_army, tld_arpa, tld_art, tld_arte, tld_as, tld_asia, tld_associates,
        tld_at, tld_attorney, tld_au, tld_auction, tld_audi, tld_audible, tld_audio, tld_auspost, tld_author, tld_auto, tld_autos,
        tld_aw, tld_aws, tld_ax, tld_axa, tld_az, tld_azure,
    tld_ba, tld_baby, tld_baidu, tld_bananarepublic, tld_band, tld_bank, tld_bar, tld_barcelona, tld_barclaycard, tld_barclays,
        tld_barefoot, tld_bargains, tld_baseball, tld_basketball, tld_bauhaus, tld_bayern, tld_bazar, tld_bb, tld_bbc, tld_bbs,
        tld_bbt, tld_bbva, tld_bcg, tld_bcn, tld_bd, tld_be, tld_beauty, tld_beer, tld_bentley, tld_berlin, tld_best, tld_bestbuy, tld_bet,
        tld_bf, tld_bg, tld_bh, tld_bharti, tld_bi, tld_bible, tld_bid, tld_bike, tld_bing, tld_bingo, tld_bio, tld_bit, tld_biz, tld_bj,
        tld_black, tld_blackfriday, tld_blanco, tld_blockbuster, tld_blog, tld_bloomberg, tld_blue, tld_bm, tld_bms, tld_bmw, tld_bn, tld_bnl,
        tld_bnpparibas, tld_bo, tld_boehringer, tld_bom, tld_bond, tld_boo, tld_book, tld_booking, tld_boots, tld_bosch, tld_bostik,
        tld_boston, tld_bot, tld_boutique, tld_box, tld_bq, tld_br, tld_bradesco, tld_bridgestone, tld_broadway, tld_broker, tld_brother,
        tld_brussels, tld_bs, tld_bt, tld_bugatti, tld_build, tld_builders, tld_business, tld_buy, tld_buzz, tld_bw, tld_by, tld_bz, tld_bzh,
    tld_ca, tld_cab, tld_cafe, tld_cal, tld_call, tld_calvinklein, tld_cam, tld_camera, tld_camp, tld_cancerresearch, tld_canon, tld_capetown,
        tld_capital, tld_capitalone, tld_car, tld_caravan, tld_cards, tld_care, tld_career, tld_careers, tld_cars, tld_cartier, tld_casa,
        tld_case, tld_cash, tld_casino, tld_cat, tld_catering, tld_catholic, tld_cba, tld_cbn, tld_cbre, tld_cbs, tld_cc, tld_cd, tld_center,
        tld_ceo, tld_cern, tld_cf, tld_cfa, tld_cfd, tld_cg, tld_ch, tld_chan, tld_chanel, tld_channel, tld_charity, tld_chase,
        tld_chat, tld_cheap, tld_chintai, tld_christmas, tld_chrome, tld_chrysler, tld_church, tld_ci, tld_cipriani, tld_circle, tld_cisco,
        tld_citadel, tld_citi, tld_citic, tld_city, tld_ck, tld_cl, tld_claims, tld_cleaning, tld_click, tld_clinic, tld_clinique, tld_clothing,
        tld_cloud, tld_club, tld_clubmed, tld_cm, tld_cn, tld_co, tld_coach, tld_codes, tld_coffee, tld_coin, tld_college, tld_cologne, tld_com,
        tld_comcast, tld_commbank, tld_community, tld_company, tld_compare, tld_computer, tld_condos, tld_construction, tld_consulting,
        tld_contact, tld_contractors, tld_cooking, tld_cool, tld_coop, tld_corp, tld_corsica, tld_country, tld_coupon, tld_coupons, tld_courses,
        tld_cpa, tld_cr, tld_credit, tld_creditcard, tld_creditunion, tld_cricket, tld_crown, tld_crs, tld_cruise, tld_cruises, tld_crypto,
        tld_csc, tld_cu, tld_cuisinella, tld_cv, tld_cw, tld_cx, tld_cy, tld_cyb, tld_cymru, tld_cyou, tld_cz,
    tld_dabur, tld_dad, tld_dance, tld_data, tld_date, tld_dating, tld_datsun, tld_day, tld_de, tld_deal, tld_dealer, tld_deals, tld_degree,
        tld_delivery, tld_dell, tld_deloitte, tld_delta, tld_democrat, tld_dental, tld_dentist, tld_desi, tld_design, tld_dev, tld_dhl,
        tld_diamonds, tld_diet, tld_digital, tld_direct, tld_directory, tld_discount, tld_discover, tld_dish, tld_diy, tld_dj, tld_dk, tld_dm,
        tld_dnp, tld_do, tld_docs, tld_doctor, tld_dodge, tld_dog, tld_doha, tld_domains, tld_dot, tld_download, tld_drive, tld_dubai, tld_dunlop,
        tld_dupont, tld_durban, tld_dvag, tld_dyn, tld_dz,
    tld_earth, tld_eat, tld_ec, tld_eco, tld_edeka, tld_edu, tld_education, tld_ee, tld_eg, tld_eh, tld_email, tld_emc, tld_emerck,
        tld_energy, tld_engineer, tld_engineering, tld_enterprises, tld_entertainment, tld_epost, tld_epson, tld_equipment, tld_er, tld_ericsson,
        tld_erni, tld_es, tld_esq, tld_estate, tld_esurance, tld_et, tld_eth, tld_etisalat, tld_eu, tld_eurovision, tld_eus, tld_events,
        tld_everbank, tld_example, tld_exchange, tld_expert, tld_exposed, tld_express, tld_extraspace,
    tld_fage, tld_fail, tld_fairwinds, tld_faith, tld_family, tld_fan, tld_fans, tld_farm, tld_farmers, tld_fashion, tld_fast, tld_fedex,
        tld_feedback, tld_ferrari, tld_ferrero, tld_fi, tld_fiat, tld_fidelity, tld_film, tld_final, tld_finance, tld_financial,
        tld_fire, tld_firestone, tld_firmdale, tld_fish, tld_fishing, tld_fit, tld_fitness, tld_fj, tld_fk, tld_flickr, tld_flights, tld_flir,
        tld_florist, tld_flowers, tld_flsmidth, tld_fly, tld_fm, tld_fo, tld_foo, tld_food, tld_foodnetwork, tld_football, tld_ford, tld_forex,
        tld_forsale, tld_forum, tld_foundation, tld_fox, tld_fr, tld_free, tld_fresenius, tld_frl, tld_frogans, tld_frontdoor, tld_frontier,
        tld_fujitsu, tld_fujixerox, tld_fun, tld_fund, tld_fur, tld_furniture, tld_futbol, tld_fyi,
    tld_ga, tld_gal, tld_gallery, tld_gallo, tld_gallup, tld_game, tld_games, tld_gap, tld_garden, tld_gay, tld_gbiz, tld_gd, tld_gdn, tld_ge,
        tld_gea, tld_geek, tld_gent, tld_genting, tld_gf, tld_gg, tld_gh, tld_gi, tld_gift, tld_gifts, tld_gives, tld_giving, tld_gl, tld_glass,
        tld_gle, tld_global, tld_globo, tld_gm, tld_gmail, tld_gmbh, tld_gmo, tld_gmx, tld_gn, tld_godaddy, tld_gold,
        tld_goldpoint, tld_golf, tld_goodyear, tld_goog, tld_google, tld_gop, tld_gopher, tld_gov, tld_gp, tld_gq, tld_gr,
        tld_grainger, tld_graphics, tld_gratis, tld_green, tld_gripe, tld_grocery, tld_group, tld_gs, tld_gt, tld_gu, tld_guardian, tld_gucci,
        tld_guide, tld_guitars, tld_guru, tld_gw, tld_gy,
    tld_hair, tld_hamburg, tld_hangout, tld_haus,  tld_hbo, tld_hdfc, tld_hdfcbank, tld_health, tld_healthcare, tld_help,
        tld_helsinki, tld_here, tld_hermes, tld_hiphop, tld_hisamitsu, tld_hitachi, tld_hiv, tld_hk, tld_hkt, tld_hm, tld_hn, tld_hockey,
        tld_holdings, tld_holiday, tld_home, tld_homegoods, tld_homes, tld_homesense, tld_honda, tld_honeywell, tld_horse, tld_hospital, tld_host,
        tld_hosting, tld_hot, tld_hoteles, tld_hotels, tld_hotmail, tld_house, tld_how, tld_hr, tld_hsbc, tld_ht, tld_hu, tld_hughes, tld_hyatt,
        tld_hyundai,
    tld_ibm, tld_ice, tld_icu, tld_id, tld_ie, tld_ieee, tld_ifm, tld_ikano, tld_il, tld_im, tld_imdb, tld_immo, tld_immobilien, tld_in,
        tld_inc, tld_industries, tld_indy, tld_infiniti, tld_info, tld_ing, tld_ink, tld_institute, tld_insurance, tld_insure, tld_int, tld_intel,
        tld_international, tld_internet, tld_intuit, tld_intranet, tld_invalid, tld_investments, tld_io, tld_ipiranga, tld_iq, tld_ir, tld_irish, tld_is, tld_iselect,
        tld_ist, tld_istanbul, tld_it, tld_itau, tld_itv, tld_iveco,
    tld_jaguar, tld_java, tld_jcb, tld_jcp, tld_je, tld_jeep, tld_jetzt, tld_jewelry, tld_jm, tld_jo, tld_jobs, tld_joburg, tld_joy, tld_jp,
        tld_jpmorgan, tld_juegos, tld_juniper,
    tld_kaufen, tld_kddi, tld_ke, tld_kerryhotels, tld_kerrylogistics, tld_kerryproperties, tld_kfh, tld_kg, tld_kh, tld_ki, tld_kia,
        tld_kim, tld_kinder, tld_kindle, tld_kitchen, tld_kiwi, tld_km, tld_kn, tld_ko, tld_koeln, tld_komatsu, tld_kosher, tld_kp,
        tld_kpmg, tld_kpn, tld_kr, tld_krd, tld_kred, tld_ku, tld_kuokgroup, tld_kw, tld_ky, tld_kyoto, tld_kz,
    tld_la, tld_lacaixa, tld_ladbrokes, tld_lamborghini, tld_lan, tld_lancaster, tld_lancia, tld_lancome, tld_land, tld_landrover, tld_lanxess,
        tld_lasalle, tld_lat, tld_latrobe, tld_law, tld_lawyer, tld_lb, tld_lc, tld_lds, tld_lease, tld_leclerc, tld_legal, tld_lego,
        tld_lexus, tld_lgbt, tld_li, tld_liaison, tld_lib, tld_libre, tld_lidl, tld_life, tld_lifeinsurance, tld_lifestyle, tld_lighting,
        tld_like, tld_lilly, tld_limited, tld_limo, tld_lincoln, tld_linde, tld_link, tld_lipsy, tld_live, tld_living, tld_lixil, tld_lk,
        tld_loan, tld_loans, tld_local, tld_localhost, tld_locker, tld_locus, tld_lol, tld_london, tld_lotte, tld_lotto, tld_love, tld_lpl,
        tld_lplfinancial, tld_lr, tld_ls, tld_lt, tld_ltd, tld_ltda, tld_lu, tld_lundbeck, tld_lupin, tld_luxe, tld_luxury, tld_lv, tld_ly,
    tld_ma, tld_macys, tld_madrid, tld_maif, tld_maison, tld_makeup, tld_man, tld_management, tld_mango, tld_map, tld_market, tld_marketing,
        tld_markets, tld_marriott, tld_maserati, tld_mattel, tld_mba, tld_mc, tld_mckinsey, tld_md, tld_me, tld_med, tld_media, tld_meet,
        tld_melbourne, tld_meme, tld_memorial, tld_men, tld_menu, tld_metlife, tld_mg, tld_mh, tld_miami, tld_microsoft, tld_mil, tld_mini,
        tld_mint, tld_mit, tld_mitsubishi, tld_mk, tld_ml, tld_mlb, tld_mm, tld_mma, tld_mn, tld_mo, tld_mobi, tld_mobile, tld_mobily, tld_moda,
        tld_moe, tld_moi, tld_mom, tld_monash, tld_money, tld_monster, tld_mormon, tld_mortgage, tld_moscow, tld_moto, tld_motorcycles, tld_mov,
        tld_movie, tld_movistar, tld_mp, tld_mq, tld_mr, tld_ms, tld_msd, tld_mt, tld_mtn, tld_mtr, tld_mu, tld_museum, tld_music, tld_mutual,
        tld_mv, tld_mw, tld_mx, tld_my, tld_mz, tld_na,
    tld_nadex, tld_nagoya, tld_name, tld_nationwide, tld_natura, tld_navy, tld_nba, tld_nc, tld_ne, tld_nec, tld_neo, tld_net, tld_netflix,
        tld_network, tld_neustar, tld_new, tld_newholland, tld_news, tld_nexus, tld_nf, tld_nfl, tld_ng, tld_ngo, tld_nhk, tld_ni, tld_nico,
        tld_nike, tld_nikon, tld_ninja, tld_nissan, tld_nissay, tld_nl, tld_no, tld_nokia, tld_northwesternmutual, tld_norton, tld_now, tld_np,
        tld_nr, tld_nra, tld_nrw, tld_ntt, tld_nu, tld_null, tld_nyc, tld_nz,
    tld_o, tld_obi, tld_observer, tld_office, tld_okinawa, tld_om, tld_omega, tld_one, tld_ong, tld_onion, tld_onl, tld_online, tld_ooo,
        tld_open, tld_oracle, tld_orange, tld_org, tld_organic, tld_origins, tld_osaka, tld_oss, tld_otsuka, tld_ovh, tld_oz, tld_pa, tld_page,
    tld_panasonic, tld_paris, tld_parody, tld_partners, tld_parts, tld_party, tld_passagens, tld_pay, tld_pccw, tld_pe, tld_pet, tld_pf,
        tld_pfizer, tld_pg, tld_ph, tld_pharmacy, tld_philips, tld_phone, tld_photo, tld_photography, tld_photos, tld_physio, tld_piaget,
        tld_pics, tld_pictet, tld_pictures, tld_pid, tld_pin, tld_ping, tld_pink, tld_pioneer, tld_pirate, tld_pizza, tld_pk, tld_pl, tld_place,
        tld_play, tld_playstation, tld_plumbing, tld_plus, tld_pm, tld_pn, tld_pohl, tld_poker, tld_politie, tld_porn, tld_post, tld_pr,
        tld_praxi, tld_press, tld_prime, tld_private, tld_pro, tld_prod, tld_productions, tld_prof, tld_progressive, tld_promo, tld_properties,
        tld_property, tld_protection, tld_pru, tld_prudential, tld_ps, tld_pt, tld_pub, tld_pw, tld_pwc, tld_py,
    tld_qa, tld_qpon, tld_quebec, tld_quest, tld_qvc,
    tld_racing, tld_radio, tld_re, tld_read, tld_realestate, tld_realtor, tld_realty, tld_recipes, tld_red, tld_redstone, tld_rehab,
        tld_reise, tld_reisen, tld_reit, tld_reliance, tld_ren, tld_rent, tld_rentals, tld_repair, tld_report, tld_republican, tld_rest,
        tld_restaurant, tld_review, tld_reviews, tld_rexroth, tld_rich, tld_ricoh, tld_rio, tld_rip, tld_rm, tld_rmit, tld_ro, tld_rocher,
        tld_rocks, tld_rodeo, tld_rogers, tld_room, tld_rs, tld_rsvp, tld_ru, tld_rugby, tld_ruhr, tld_run, tld_rw, tld_rwe, tld_ryukyu,
    tld_sa, tld_saarland, tld_safe, tld_safety, tld_sakura, tld_sale, tld_salon, tld_samsung, tld_sandvik, tld_sandvikcoromant, tld_sanofi,
        tld_sap, tld_sarl, tld_save, tld_saxo, tld_sb, tld_sbi, tld_sbs, tld_sc, tld_sca, tld_scb, tld_schaeffler, tld_schmidt,
        tld_scholarships, tld_school, tld_schule, tld_schwarz, tld_science, tld_scjohnson, tld_scor, tld_scot, tld_sd, tld_se, tld_search,
        tld_seat, tld_secure, tld_security, tld_seek, tld_select, tld_sener, tld_services, tld_ses, tld_seven, tld_sew, tld_sex, tld_sexy,
        tld_sfr, tld_sg, tld_sh, tld_shangrila, tld_sharp, tld_shaw, tld_shell, tld_shiksha, tld_shoes, tld_shop, tld_shopping, tld_shouji,
        tld_show, tld_showtime, tld_shriram, tld_si, tld_silk, tld_sina, tld_singles, tld_site, tld_sk, tld_ski, tld_skin, tld_sky,
        tld_skype, tld_sl, tld_sling, tld_sm, tld_smart, tld_smile, tld_sn, tld_sncf, tld_so, tld_soccer, tld_social, tld_softbank,
        tld_software, tld_sohu, tld_solar, tld_solutions, tld_song, tld_sony, tld_soy, tld_spa, tld_space, tld_spiegel, tld_sport, tld_spot,
        tld_spreadbetting, tld_sr, tld_srl, tld_ss, tld_st, tld_stada, tld_staples, tld_star, tld_starhub, tld_statebank, tld_statefarm,
        tld_statoil, tld_stc, tld_stcgroup, tld_stockholm, tld_storage, tld_store, tld_stream, tld_studio, tld_study, tld_style, tld_su,
        tld_sucks, tld_supplies, tld_supply, tld_support, tld_surf, tld_surgery, tld_suzuki, tld_sv, tld_swatch, tld_swiftcover, tld_swiss,
        tld_sx, tld_sy, tld_sydney, tld_symantec, tld_systems, tld_sz,
    tld_taipei, tld_talk, tld_taobao, tld_target, tld_tatamotors, tld_tatar, tld_tattoo, tld_tax, tld_taxi, tld_tc, tld_td, tld_tdk, tld_te,
        tld_team, tld_tech, tld_technology, tld_tel, tld_telecity, tld_telefonica, tld_temasek, tld_tennis, tld_test, tld_teva, tld_tf, tld_tg,
        tld_th, tld_theater, tld_theatre, tld_ti, tld_tickets, tld_tienda, tld_tiffany, tld_tips, tld_tires, tld_tirol, tld_tj, tld_tjx, tld_tk,
        tld_tl, tld_tm, tld_tn, tld_to, tld_today, tld_tokyo, tld_tools, tld_top, tld_toray, tld_toshiba, tld_total, tld_tours, tld_town,
        tld_toyota, tld_toys, tld_tr, tld_trade, tld_trading, tld_training, tld_travel, tld_travelchannel, tld_travelers, tld_travelersinsurance,
        tld_trust, tld_tt, tld_tube, tld_tui, tld_tunes, tld_tushu, tld_tv, tld_tvs, tld_tw, tld_tz,
    tld_ua, tld_ubs, tld_uconnect, tld_ug, tld_uk, tld_unicom, tld_university, tld_uno, tld_uol, tld_ups, tld_us, tld_uu, tld_uy, tld_uz,
    tld_va, tld_vacations, tld_vanguard, tld_vc, tld_ve, tld_vegas, tld_ventures, tld_verisign, tld_versicherung, tld_vet, tld_vg, tld_vi,
        tld_viajes, tld_video, tld_vig, tld_viking, tld_villas, tld_vin, tld_vip, tld_virgin, tld_visa, tld_vision, tld_vista, tld_vistaprint,
        tld_vivo, tld_vlaanderen, tld_vm, tld_vn, tld_vodka, tld_volkswagen, tld_volvo, tld_vote, tld_voting, tld_voto, tld_voyage, tld_vu, tld_vuelos,
    tld_wales, tld_walmart, tld_walter, tld_wang, tld_wanggou, tld_watch, tld_watches, tld_weather, tld_weatherchannel, tld_webcam, tld_weber,
        tld_website, tld_wed, tld_wedding, tld_weibo, tld_weir, tld_wf, tld_whoswho, tld_wien, tld_wiki, tld_williamhill, tld_win, tld_windows,
        tld_wine, tld_winners, tld_wme, tld_wolterskluwer, tld_woodside, tld_work, tld_works, tld_world, tld_wow, tld_ws, tld_wtc, tld_wtf,
    tld_xbox, tld_xerox, tld_xfinity, tld_xihuan, tld_xin, tld_xxx, tld_xyz,
    tld_yachts, tld_yahoo, tld_yamaxun, tld_yandex, tld_ye, tld_yodobashi, tld_yoga, tld_yokohama, tld_you, tld_youtube, tld_yt,
    tld_za, tld_zappos, tld_zara, tld_zero, tld_zip, tld_zippo, tld_zm, tld_zone, tld_zuerich, tld_zw,
    tld_xn__11b4c3d, tld_xn__1ck2e1b, tld_xn__1qqw23a, tld_xn__30rr7y, tld_xn__3bst00m, tld_xn__3ds443g, tld_xn__3oq18vl8pn36a,
        tld_xn__42c2d9a, tld_xn__45q11c, tld_xn__4gbrim, tld_xn__54b7fta0cc, tld_xn__55qw42g, tld_xn__55qx5d, tld_xn__5su34j936bgsg,
        tld_xn__5tzm5g, tld_xn__6frz82g, tld_xn__6qq986b3xl, tld_xn__80adxhks, tld_xn__80aqecdr1a, tld_xn__80asehdb, tld_xn__80aswg,
        tld_xn__8y0a063a, tld_xn__9dbq2a, tld_xn__b4w605ferd, tld_xn__bck1b9a5dre4c, tld_xn__c1avg, tld_xn__c2br7g, tld_xn__cck2b3b,
        tld_xn__cg4bki, tld_xn__czr694b, tld_xn__czru2d, tld_xn__d1acj3b, tld_xn__eckvdtc9d, tld_xn__estv75g, tld_xn__fhbei, tld_xn__fiq228c5hs,
        tld_xn__fiq64b, tld_xn__flw351e, tld_xn__fzys8d69uvgm, tld_xn__g2xx48c, tld_xn__gckr3f0f, tld_xn__i1b6b1a6a2e, tld_xn__io0a7i,
        tld_xn__j1aef, tld_xn__jlq61u9w7b, tld_xn__kcrx77d1x4a, tld_xn__kput3i, tld_xn__mgba3a3ejt, tld_xn__mgbaakc7dvf, tld_xn__mgbab2bd,
        tld_xn__mgbb9fbpob, tld_xn__mgbca7dzdo, tld_xn__mgbi4ecexp, tld_xn__mk1bu44c, tld_xn__mxtq1m, tld_xn__ngbc5azd, tld_xn__ngbe9e0a,
        tld_xn__ngbrx, tld_xn__nqv7f, tld_xn__p1acf, tld_xn__q9jyb4c, tld_xn__qcka1pmc, tld_xn__rhqv96g, tld_xn__ses554g, tld_xn__t60b56a,
        tld_xn__tckwe, tld_xn__vermgensberater_ctb, tld_xn__vermgensberatung_pwb, tld_xn__w4r85el8fhu5dnra, tld_xn__w4rs40l, tld_xn__xhq521b,
        tld_xn__h2brj9c,
    tld_error } e_tld;

typedef enum { ta_translate, ta_scale, ta_rotate, ta_skewx, ta_skewy } e_transform_anim;
typedef enum { tb_geometric, tb_pinned, tb_pinned90, tb_pinned180, tb_pinned270 } e_transformbehaviour;
typedef enum { tr_nowt, tr_matrix, tr_ref, tr_translate, tr_translatex, tr_translatey, tr_scale, tr_scalex, tr_scaley, tr_rotate, tr_skew, tr_skewx, tr_skewy } e_transform_fn;
CONSTEXPR ::std::size_t max_transform_fn = static_cast < ::std::size_t > (tr_skewy);
typedef enum { tp_opaque, tp_transparent } e_transp;
typedef enum { tu_fractal_noise, tu_turbulence } e_turbulence_type;

// here's hoping future compilers will have a little more oomph. Still, given the current crop are hampered, I've no real choice but to ...
#define SSC_TYPES_0_9 \
    t_0_more, t_0_to_1, t_0_to_2, t_0_to_3, t_0_to_4, t_0_to_6, t_0_to_7, t_0_to_8, t_0_to_9, t_0_to_100, t_0_to_150, t_0_to_255, t_0_to_1000, \
    t_10, t_1_to_2, t_1_or_6, t_1_to_7, t_1_to_8, t_1_to_20, t_1_to_99, t_1_more, t_1_more_i, t_10_int, \
    t_2_to_3, t_2_to_4, t_2_or_6, t_2000_to_50000, t_2pt, t_2string, t_2x_integer, t_2x_unsigned, \
    t_3x_integer, t_3x_real, t_3x_unsigned, t_3x_urational, \
    t_4string, t_4string_ni, t_4x_0_to_6, t_4x_urational, t_4x_unsigned, \
    t_5x_unsigned
#define SSC_TYPES_0_9_MAX t_5x_unsigned

#define SSC_TYPES_A \
    t_a_b_c_d, t_a_v, t_abcfl, t_abfmt, t_about, t_absolute_url, t_accept, t_accrual_method, t_accrual_periodicity, t_accrual_policy, t_accumulate, \
        t_accumulate0, t_accumulate1, t_accumulate2, t_aces, t_acm, t_acn, t_acn_2, t_action, t_actiontype, t_actiontype2, t_additive, t_aesf, \
        t_aesfs, t_align, t_align2070, t_align3, t_aligndec, t_alignfig, t_alignment_baseline, t_alignplus, t_all_auto_none, t_all_none, t_allow_force, \
        t_alp, t_always_normal, t_angle, t_angle_0, t_angle_a, t_angle_ai, t_angle_ar, t_angle_ars, t_angle_i, t_angle_lrtb, t_angle_n, t_angle_p, \
        t_angular_colour_more, t_angular_colour_stop, t_anywhere_break_normal, t_arabicenum, t_arabic_form,  t_aria_autocomplete, t_aria_invalidity, \
        t_aria_live, t_aria_sort, t_arxiv, t_as, t_ass, t_as_units, t_at_pos, t_attr, t_attributename, t_attributetype, t_attr_unit, t_audio_level, \
        t_autocapitalise, t_auto_break, t_auto_contain, t_autocomplete, t_autocompletes, t_autocompletevaried, t_auto_contain_cover, t_auto_first_last, \
        t_auto_focus_scroll, t_auto_hidden_visible, t_auto_none, t_auto_manual_none, t_auto_merge_separate, t_auto_none_thin, t_auto_smooth, t_auto_stable
#define SSC_TYPES_A_MAX t_auto_stable

#define SSC_TYPES_B \
    t_b64, t_background, t_bandwidth, t_base, t_baseline_contain_none, t_baselineshift, t_bb, t_bcs, t_beginvalue, t_beginvalues, t_beginvaluelist, \
        t_behaviour, t_bens, t_benrs, t_bixy, t_bixys, t_blocking, t_block_inline, t_border, t_bool, t_bools, t_brs, t_buffered_rendering, t_button, \
    t_cache, t_cachekey, t_calcfn, t_calcmode, t_captionalign, t_capture, t_cc_permits, t_cc_prohibits, t_cc_requires, t_celnrs, t_cens, t_centre_space, \
        t_channelselector, t_char, t_charset, t_charsets, t_charspacing, t_cio, t_cipr, t_circle_ellipse, t_citype, t_class, t_clear, t_clear30, t_clip, \
        t_clip_path_rule, t_closed_open, t_closure, t_coden, t_colour, t_colour_a, t_colour_ci, t_colour_cii, t_colour_i, t_colour_ii, t_colour_interpolation
#define SSC_TYPES_B_MAX t_colour_interpolation

#define SSC_TYPES_C \
        t_colour_ni, t_colour_profile, t_colour_profile_name, t_colour_profile_name_or_uri, t_colour_rendering, t_colour_scheme, t_colour_schemes, \
        t_colour_schemes_n, t_colour_schemes_o, t_colour_space, t_colour_trans, t_colour_trans_i,  t_colour_v, t_colourfn, t_command, t_compact, t_comp_op, \
        t_composite_operator, t_compositing, t_conlit, t_conic_1, t_conic_2, t_connect, t_contain, t_contain_cover, t_contain_cover_sd, t_content_encoding, \
        t_content_encodings, t_content_type, t_context_menu, t_contents, t_controlslist, t_cookie, t_cookieid, t_cookies, t_coordinatesystem, t_coords, \
        t_corp, t_cors, t_country, t_cntype, t_create_parent, t_crossout, t_crs_tonecurvename, t_crs_whitebalance, t_cs, t_csp, t_csp_ancestor, \
        t_csp_directive, t_csp_keyword, t_csp_sauce, t_csp_source
#define SSC_TYPES_C_MAX t_csp_source

#define SSC_TYPES_CSS_A \
        t_css, \
            t_css_aaalri, t_css_aai, t_css_absolute_size, t_css_addsym, t_css_addsyms, t_css_align_content, t_css_align_items, t_css_align_items_a, \
                t_css_all, t_css_all_2, t_css_alpha, t_css_alpha_n, t_css_angular_colour_stop, t_css_angular_colour_stop_list, t_css_animation, \
                t_css_anim_base, t_css_anim_comp, t_css_anim_dir, t_css_anim_fill_mode, t_css_anim_name, t_css_anim_play_state, t_css_anim_range, \
                t_css_anim_range_2, t_css_anim_range_2s, t_css_anim_ranges, t_css_anim_rt, t_css_anim_timeline,  t_css_appearance, t_css_attr, \
                t_css_azimuth, t_css_azimuth_be, t_css_azimuth_e, t_css_azimuth_eb, t_css_azimuth_es, t_css_azimuth_lri
#define SSC_TYPES_CSS_A_MAX t_css_azimuth_lri

#define SSC_TYPES_CSS_B_1 \
            t_css_background, t_css_background_0, t_css_background_1, t_css_background_2, t_css_background_3, t_css_background_attachment, \
                t_css_background_attachment_3, t_css_background_attachments, t_css_background_boxes, t_css_background_position, \
                t_css_background_position_1, t_css_background_position_2, t_css_background_position_3, t_css_background_position_3s, \
                t_css_background_positions, t_css_background_repeat,  t_css_background_repeat_2, t_css_background_repeat_3, t_css_background_repeats, \
                t_css_background_size, t_css_background_sizes,  t_css_backval, t_css_base_palette, t_css_baseline_position, t_css_bespoke, \
                t_css_blend_mode, t_css_block_step, t_css_border_collapse, t_css_border_image, t_css_border_image_repeat, t_css_border_images_repeat
#define SSC_TYPES_CSS_B_1_MAX t_css_border_images_repeat

#define SSC_TYPES_CSS_B_2 \
                t_css_border_image_slice, t_css_border_image_src, t_css_border_measure, t_css_border_radius, t_css_border_spacing, t_css_border_spacing_2, \
                t_css_border_style, t_css_border_style_i, t_css_border_styles, t_css_border_styles_2, t_css_border_styles_l, t_css_border_width, \
                t_css_border_width_i, t_css_border_wsc, t_css_border_wsc_i, t_css_borders_measure, t_css_borders_measure_2, t_css_borders_measure_i, \
                t_css_borders_measure_l, t_css_box_alignitems, t_css_box_alignitems_ns, t_css_box_alignself, t_css_box_alignself_acs, \
                t_css_box_alignself_mess, t_css_box_content, t_css_box_content_n, t_css_box_justify, t_css_box_justify_n, t_css_box_justitems, \
                t_css_box_justitems_ns, t_css_box_justself, t_css_box_justself_ans, t_css_box_legacy, t_css_box_orient, t_css_box_overflow, \
                t_css_box_shadow, t_css_box_shadows, t_css_box_shadows_n, t_css_box_sizing, t_css_box_snap, t_css_break, t_css_break_box, t_css_break_inside
#define SSC_TYPES_CSS_B_2_MAX t_css_break_inside

#define SSC_TYPES_CSS_C_1 \
            t_css_caret, t_css_caret_shape, t_css_clear, t_css_clip_path, t_css_clip_path_box, t_css_clip_path_shape, t_css_coin1, t_css_coin2, \
                t_css_coin3, t_css_col, t_css_colour, t_css_colour_3, t_css_colour_4, t_css_colour_a, t_css_colour_interpolation, t_css_colour_percent, \
                t_css_colour_percent_n, t_css_colour_stop_list, t_css_cols, t_css_cols_2, t_css_cols_2_a, t_css_cols_l, t_css_column_fill, t_css_column_rule, \
                t_css_column_width, t_css_columns, t_css_composite, t_css_composites, t_css_contain, t_css_contain_e, t_css_contain_slp, t_css_container, \
                t_css_container_feature, t_css_container_name, t_css_container_type, t_css_content, t_css_content_3, t_css_content_3nn, t_css_content_base
#define SSC_TYPES_CSS_C_1_MAX t_css_content_base

 #define SSC_TYPES_CSS_C_2 \
               t_css_content_enum, t_css_content_fn, t_css_content_list, t_css_content_name, t_css_content_position, t_css_content_twice, t_css_content_x, \
                t_css_continue, t_css_control_break, \
                t_css_clip_coord_box, t_css_clip_coord_boxen, t_css_coord_box, t_css_coord_boxen, t_css_counter, t_css_counter_ii, t_css_counter_iin, \
                t_css_counter_set, t_css_counter_style, t_css_counter_style_name, t_css_counters, t_css_cross_fade, t_css_cross_fade_colour, t_css_cue, \
                t_css_cues, t_css_cursor, t_css_cursor_e, t_css_cursor_url, t_csvw_direction, t_curie, t_curie_safe, t_curies, t_currency, \
                t_current_colour_sz, t_cursor, t_cursor_f, t_cursor_i
#define SSC_TYPES_CSS_C_2_MAX t_cursor_i

#define SSC_TYPES_CSS_D_E \
           t_css_djs, t_css_djs_n, t_css_djss, t_css_display, t_css_display_1, t_css_display_3, t_css_display_box, t_css_display_flow, \
                t_css_display_inside, t_css_display_internal, t_css_display_legacy, t_css_display_listitem, t_css_display_outside, t_css_durations, \
            t_css_earnest, t_css_easing_fn, t_css_easing_fns, t_css_elevation, t_css_elevation_e, t_css_empty_cells
#define SSC_TYPES_CSS_D_E_MAX t_css_empty_cells

#define SSC_TYPES_CSS_F_1 \
            t_css_fca, t_css_feature_annotation, t_css_feature_character_variant, t_css_feature_historical_forms, t_css_feature_ornaments,  t_css_feature_swash, \
                t_css_feature_styleset, t_css_feature_stylistic, t_css_ffv, t_css_filter, t_css_filters, t_css_filters_n, t_css_flex, t_css_flex_basis, \
                t_css_flex_direction, t_css_flex_flow, t_css_flex_n, t_css_flex_wrap, t_css_float, t_css_float_fn, t_css_fn, t_css_fn_annotation, \
                t_css_fn_character_variant, t_css_fn_fit_content, t_css_fn_ornaments, t_css_fn_round_t, t_css_fn_styleset, t_css_fn_stylistic, \
                t_css_fn_swash, t_css_font, t_css_font_display, t_css_font_feature, t_css_font_feature_settings, t_css_font_feature_tag
#define SSC_TYPES_CSS_F_1_MAX t_css_font_feature_tag

#define SSC_TYPES_CSS_F_2 \
                t_css_font_feature_tags, t_css_font_families, t_css_font_format, t_css_font_kerning, t_css_font_named_instance, t_css_font_size, \
                t_css_font_size_4, t_css_font_size_adjust, t_css_font_size_adjust_e, t_css_font_stretch, t_css_font_style, t_css_font_style_2, \
                t_css_font_style_a, t_css_font_style_e, t_css_font_synthesis, t_css_font_synthesis_n, t_css_font_tech, t_css_font_techs, \
                t_css_font_variation, t_css_font_variation_settings, t_css_font_variation_tag, t_css_font_variation_tags, t_css_font_variant, \
                t_css_font_variant_4, t_css_font_weight, t_css_font_weight_4, t_css_font_weights, t_css_format, t_css_frame
#define SSC_TYPES_CSS_F_2_MAX t_css_frame

#define SSC_TYPES_CSS_G_I \
            t_css_gap, t_css_generic_family, t_css_gradient, t_css_grid, t_css_grid_auto_flow, t_css_grid_line, t_css_grid_lines, \
                t_css_grid_template, t_css_grid_templates, t_css_grid_track_size, t_css_grid_track_sizes, \
            t_css_hang_punct, t_css_hang_punct_n, t_css_hangs_punct, t_css_hll, t_css_hue, t_css_hue_interpolation, t_css_hue_n, \
            t_css_id, t_css_image, t_css_images, t_css_image_resolution, t_css_image_resolution_from, t_css_image_set, t_css_image_set_rhs, \
                t_css_image_processing, t_css_image_proc_e, t_css_initial_letter, t_css_initial_letter_align, t_css_initial_letter_align_bb, \
                t_css_initial_letter_n, t_css_initial_letter_wrap, t_css_initial_letter_wrap_e, t_css_inherit, t_css_inline_bem, t_css_inline_bem_1, \
                t_css_inline_bem_2, t_css_inline_bem_l, t_css_intrinsic, t_css_intrinsic_2, t_css_isolation
#define SSC_TYPES_CSS_G_I_MAX t_css_isolation

 #define SSC_TYPES_CSS_J_L \
           t_css_justify_content, \
            t_css_kbd_lhs, t_css_kdb_nav, t_css_kbd_rhs, \
            t_css_lang, t_css_langs, t_css_layout_box, t_css_length, t_css_length_2, t_css_length_3, t_css_length_4, t_css_length_a, t_css_length_a2, \
                t_css_length_abs,  t_css_length_abs_r, t_css_length_ai, t_css_length_amm, t_css_length_n, t_css_length_xtz, t_css_lengths, t_css_lengths_a, \
                t_css_lengths_a_l,  t_css_lengths_l, t_css_lengths_n, t_css_length_twice, t_css_line_break, t_css_line_clamp, t_css_line_clamp_n, \
                t_css_line_height, t_css_list_style, t_css_list_style_position, t_css_list_style_type, t_css_list_style_type_cs, t_css_local_url, \
                t_css_ls_val
#define SSC_TYPES_CSS_J_L_MAX t_css_ls_val

#define SSC_TYPES_CSS_M_N \
           t_css_margin_break, t_css_margin_trim, t_css_margin_trim_inner, t_css_margins_trim_inner, t_css_margins, t_css_margins_l, t_css_mark, \
                t_css_marks, t_css_marx, t_css_mask, t_css_mask_border, t_css_mask_border_mode, t_css_mask_border_outsets, \
                t_css_mask_border_repeat, t_css_mask_border_repeats, t_css_mask_border_slice, t_css_mask_border_width, \
                t_css_mask_border_widths, t_css_masking_mode, t_css_masking_modes, t_css_mask_ref, t_css_mask_refs, t_css_masks, \
            t_css_nth, t_css_nth_oe
#define SSC_TYPES_CSS_M_N_MAX t_css_nth_oe

#define SSC_TYPES_CSS_O_P \
            t_css_object_fit, t_css_offset, t_css_offset_path, t_css_offset_path_basic, t_css_offset_path_n, t_css_orientation, t_css_outline, \
                t_css_outline_i, t_css_outline_style, t_css_outlines, t_css_overflow, t_css_overflow_style, t_css_overflows, t_css_override_colour, \
                t_css_override_colours, \
            t_css_palette, t_css_palette_nld, t_css_paint_box, t_css_pause, t_css_pause_2, t_css_pause_3, t_css_pause_3_e, t_css_pause_i, \
                t_css_pauses, t_css_pitch, t_css_pitch_e, t_css_place_content, t_css_place_items, t_css_place_self, \
                t_css_play_during, t_css_play_during_mr, t_css_polar, t_css_position, t_css_position_a, t_css_property, \
            t_css_quotes, t_css_quotes_3
#define SSC_TYPES_CSS_O_P_MAX t_css_quotes_3

#define SSC_TYPES_CSS_R \
            t_css_range, t_css_range_a, t_css_ranges, t_css_radial_size, t_css_ray_size, t_css_rect, t_css_rect_ai, t_css_rect_fn, t_css_ref_annotation, \
                t_css_ref_character_variant, t_css_ref_historical_forms, t_css_ref_ornaments, t_css_ref_swash, t_css_ref_styleset, t_css_ref_stylistic, \
                t_css_relative_size, t_css_region_flow_into, t_css_region_flow_into_n, t_css_region_id, t_css_region_id_ni, t_css_resize, t_css_rgb_xyz, \
                t_css_rotate,t_css_rotate_angle, t_css_rotate_angles, t_css_rotate_xyz, t_css_ruby_pos, t_css_ruby_pos_in, t_css_ruby_pos_ins
#define SSC_TYPES_CSS_R_MAX t_css_ruby_pos_ins

#define SSC_TYPES_CSS_S \
            t_css_scale, t_css_scale_3, t_css_scrollbar_gutter,  t_css_self_position, t_css_shape_box, t_css_shape_fillrule, \
                t_css_shape_inside, t_css_shape_inside_box, t_css_shape_inside_boxen, t_css_shape_inside_e, t_css_shape_outside, \
                t_css_shape_position, t_css_shape_radius, t_css_size, t_css_size_3, t_css_size_e, t_css_size_es, t_css_sizing, t_css_speak, \
                t_css_speak_2, t_css_speak_3, t_css_speak_as, t_css_speak_as_2,  t_css_speak_as_3, t_css_speak_as_e, t_css_speak_header, \
                t_css_speak_punctuation, t_css_speech_rate, t_css_speech_rate_e, t_css_speech_rate_p, t_css_src, t_css_src_2, t_css_src_3, \
                t_css_speak_numeral, t_css_src_4, t_css_srcs, t_css_ss_align, t_css_ss_type, t_css_ss_type_e, t_css_ss_type_n, t_css_stroke_linejoin, \
                t_css_statement, t_css_stn, t_css_stn_n, t_css_str_set, t_css_str_sets, t_css_str_sets_n, t_css_sts, t_css_stss, t_css_sym, \
                t_css_system, t_css_system_e, t_css_system_fix, t_css_system_ext
#define SSC_TYPES_CSS_S_MAX t_css_system_ext

#define SSC_TYPES_CSS_T_1 \
            t_css_table_layout, t_css_tech, t_css_text_align, t_css_text_align_4, t_css_text_align_all, t_css_text_align_last, t_css_text_autospace, \
                t_css_text_autospaces, t_css_text_autospaces_na, t_css_text_combine_upright, t_css_text_combine_upright_d, t_css_text_decoration, \
                t_css_text_decorations, t_css_text_fade, t_css_text_indent, t_css_text_justify, t_css_text_justify_nc, t_css_text_orientation, \
                t_css_text_resize, t_css_text_resize_4, t_css_text_resizes, t_css_text_resizes_4, \
                t_css_text_shadow, t_css_text_spacing, t_css_text_spacing_nan, t_css_text_transform, t_css_text_transform_n, t_css_text_transform_3, \
                t_css_textdec_line, t_css_textdec_line_e, t_css_textdec_short, t_css_textdec_skip_space, t_css_textdec_style, t_css_textdec_thickness
#define SSC_TYPES_CSS_T_1_MAX t_css_textdec_thickness

#define SSC_TYPES_CSS_T_2 \
                t_css_textdec_underline, t_css_textdec_underline_lru, t_css_textdec_underline_offset, t_css_text_emphasis, t_css_textemph_pos, \
                t_css_textemph_shape, t_css_textemph_skip, t_css_textemph_style, t_css_textemph_substyle, t_css_texts_indent, t_css_text_wrap, t_css_transform, \
                t_css_transform_box, t_css_transform_origin, t_css_transform_origins, t_css_transform_n, t_css_transform_style, t_css_transforms, \
                t_css_translate, t_css_translate_n, t_css_track_list, t_css_track_list_auto, t_css_trans_prop, t_css_trans_prop_a, t_css_trans_prop_n, \
                t_css_trans_props, t_css_trans_props_n, t_css_transition, t_css_transitions, t_css_tst
#define SSC_TYPES_CSS_T_2_MAX t_css_tst

#define SSC_TYPES_CSS_U_Z \
            t_css_unicode_from_to, t_css_unicode_range, t_css_unicode_ranges, t_css_unicode_wildcard, t_css_url, t_css_user_select, \
            t_css_val_con, t_css_val_fn, t_css_val_fn_n, t_css_var, t_css_vbl_len, t_css_version, t_css_vertal, t_css_vertal_2, t_css_vertal_inline, \
                t_css_vertical_align, t_css_visual_box, t_css_voice_balance, t_css_voice_balance_e, t_css_voice, t_css_voice_age, t_css_voice_families, \
                t_css_voice_families_p, t_css_voice_family, t_css_voice_family_desc, t_css_voice_gender, t_css_voice_pitch, t_css_voice_volume, \
                t_css_volume, t_css_volume_e, t_css_vtn, t_css_vtn_n, t_css_vtn_splat, \
            t_css_wbd, t_css_wbe, t_css_wc, t_css_wc_e, t_css_wcs, t_css_wcs_a, t_css_whitespace, t_css_whitespace_2, t_css_whitespace_4, t_css_wide, \
                t_css_word_break, t_css_wrap_flow, t_css_ws_wsc, t_css_wsc, t_css_wsc_val, t_css_wst, t_css_wsts
#define SSC_TYPES_CSS_U_Z_MAX t_css_wsts

#define SSC_TYPES_D_E \
    t_d, t_dashes, t_data, t_dataformatas, t_datetime, t_datetime_absolute, t_datetime_local, t_datetime_4, t_datetime_5, t_day, t_decalign, \
        t_decibel, t_decoding, t_defaultaction, t_depth, t_determiner, t_device, t_dg, t_digits, t_dingbat, t_dir, t_direction, t_display, \
        t_display_align, t_display_none_parent, t_dnu, t_dominantbaseline, t_dosh, t_drop_raise, t_dsc, t_dss, t_dsss, t_dur, t_dur_repeat, \
        t_duration, t_duration_a, t_duration_media, t_dynamic_range, \
    t_e_w, t_economy_exact, t_edgemode, t_edi, t_edit, t_editable, t_effect, t_email, t_emails, t_empty, t_enable_background, t_enctype, t_end, \
        t_endvaluelist, t_ens, t_enterkeyhint, t_environment_blending, t_evt_action, t_exif_intind, t_existential, t_expected, t_exportpart
#define SSC_TYPES_D_E_MAX t_exportpart

#define SSC_TYPES_F \
    t_featurepolicy, t_ffls, t_figalign, t_filename, t_filesize, t_fill, t_fill_v, t_fillanim, t_filled_open, t_fill_opacity, t_fill_rule, t_fill_ve, \
        t_filter_in, t_filterres, t_first_last, t_fixedcolour, t_fixedpoint, t_fixed_zoom, t_fn, t_fnrs, t_fns, t_font, t_font_enum, t_font_family, t_font_families, \
        t_fontname, t_fontnia, t_fontnias, t_fontsize, t_fontsizeadjust, t_fontstretch, t_fontstretches, t_fontstyle, t_font_synthesis, \
        t_font_synthesis_n, t_fontweight, t_fontvariant, t_fontvariants, t_font_variant, t_font_variant_2, t_font_variant_2s, \
        t_font_variant_4, t_font_variant_alternatives, t_font_variant_caps, t_font_variant_east_asians, t_font_variant_east_asian, \
        t_font_variant_emoji, t_font_variant_ligature, t_font_variant_ligatures, t_font_variant_numeric, t_font_variant_numerics, \
        t_font_variant_position, t_forced_colours, t_form, t_format, t_formaturi, t_forrev, t_fr, t_frp, t_frame, t_frame4, t_framespacing, \
        t_frequency, t_frequency_abs, t_from, t_from_angle
#define SSC_TYPES_F_MAX t_from_angle

#define SSC_TYPES_G_H \
    t_gamut, t_gender, t_generic, t_glyphname, t_glyphnames, t_grid_normal, t_groupalign, \
    t_halign, t_hash_ref, t_hash_fn, t_height, t_hex, t_hidden, t_hidden_ex, t_hour, t_hslafn, t_hslfn, t_hslfn4, t_html, t_html_boolean, \
        t_httpequiv, t_hue, t_hue_n, t_hunit, t_hv, t_hwbfn
#define SSC_TYPES_G_H_MAX t_hwbfn

#define SSC_TYPES_I \
    t_icalfreq, t_icc, t_icccolour, t_id, t_identifier_url, t_idref, t_idrefs, t_illegal, t_image_rendering, t_imcastr, t_imgsizes, t_imgsizes_a, \
        t_importance, t_in, t_index, t_indentalign, t_indentalign2, t_indentshift2, t_infixlinebreakstyle, t_initialvisibility, t_inky, t_inlist, \
        t_inputaccept, t_inputmode, t_inputplus, t_inputtype, t_inputtype3, t_inputtype32, t_inputtype4, t_inputtype5, t_inset, t_integer, \
        t_integer_ai, t_integer_i, t_integer_is, t_integer_ln, t_integer_n, t_integer_nl, t_integer_oo, t_integer_or_percent, t_integers, t_integers_a, \
        t_intent, t_intent_app, t_intent_args, t_intent_conlit, t_intent_hint, t_intent_ref, t_inverted_colours, t_ip_address, t_is, t_isbn, \
        t_issn, t_itemid, t_itemprop, t_itemtype, t_itemref
#define SSC_TYPES_I_MAX t_itemref

#define SSC_TYPES_J_L \
    t_js_lang, t_js_lang_map, t_js_map, t_js_term, t_js_type, t_js_value, t_js_version, t_jtoken, t_just_date, t_just_time, \
    t_k_m_n, t_key, t_keygentype, t_keyspline, t_keysplines, t_keytimes, t_keytype, t_kind, \
    t_labfn, t_lang, t_lang_n, t_langq, t_langs, t_langqs, t_larnalign, t_layout, t_lchfn, t_lcralign, t_lcraligns, t_lcrnalign, \
        t_lcrd, t_lcrds, t_lcrdss, t_length, t_length_absolute, t_length_relative, t_lengthadjust, t_linear_colour_more, t_linear_colour_stop, \
        t_linear_colour_stops, t_linebreak, t_linebreakstyle, t_linecap, t_line_height, t_linejoin, t_linethickness, t_link, t_linkarg, t_linkargs, \
        t_linkitself, t_linkparam, t_links, t_listtype, t_literal, t_literal_or_not, t_lnr, t_loading, t_localfn, t_local_url, t_location, \
        t_longdivstyle, t_loop, t_loopie, t_lraalign, t_lralign, t_lrnalign, t_lrnialign, t_lspace, t_lrtb, t_ltr_rtl, t_lzz
#define SSC_TYPES_J_L_MAX t_lzz

#define SSC_TYPES_M_1 \
    t_m1_to_5, t_m100_to_100, t_m100_to_100r, t_m128_to_127, t_m150_to_150, \
    t_m4_to_4, \
    t_m50_to_100, \
    t_m_t, t_mah, t_mand_prox, t_manual_normal, t_margin_padding, t_marked_up, t_marker, t_markerunits, t_match_self_parent, t_mathalign, t_mathalign_n, \
        t_mathaligns, \
        t_mathclosure, t_mathfontstyle, t_mathfontweight, t_mathform, t_mathframe, t_mathlocation, t_mathmode, t_mathnotation, t_mathnotations, \
        t_mathoccurence, t_mathorder, t_mathoverflow, t_mathscope, t_mathside, t_mathsize, t_mathspace, t_mathspaceauto, t_mathspacefit
#define SSC_TYPES_M_1_MAX t_mathspacefit

#define SSC_TYPES_M_2 \
        t_mathspaceinfinity, t_mathvariant, t_mathvertauto, t_matrixtype, t_matrix_values, t_mb, t_measure, t_measure_2, t_measure_4, t_measure_a, \
        t_measure_ai, t_measure_i, t_measure_in, t_measure_ni, t_measure_or_more, t_measures, t_measures_a, t_measures_all, t_measures_i, \
        t_measures_l, t_media, t_media_display_mode, t_media_hover, t_media_inline, t_media_orientation, t_media_overflow, t_media_pointer, \
        t_media_prefers, t_media_prefers_2, t_media_scripting, t_meetslice, t_menuitem, t_menutype, t_metaname, t_method, \
        t_methodological, t_mf_availability, t_mf_category, t_mf_class, t_mf_identifier, t_mf_itemtype, t_mf_listing_action, t_mf_listing_actions, \
        t_mf_method, t_mf_reviewtype, t_mf_status, t_mime, t_mimelist, t_mimemodule, t_mimeq, t_mimeqs, t_mimestar, t_minute, t_mode, t_month, \
        t_monthday, t_morphology_operator, t_mql, t_mqls, t_musickey, t_myersbriggs
#define SSC_TYPES_M_2_MAX t_myersbriggs

#define SSC_TYPES_N_O \
    t_n_s, t_name, t_nameref, t_namespace, t_namedspace, t_nav_controls, t_navigation, t_negative, t_nit_macro, t_nit_section, t_none_objects, \
        t_none_wrap, t_normal, t_normal_spell, t_normal_stretch, t_not_0, t_not_empty, t_not_neg, t_not_pos, t_notation, t_notations, t_nsd, t_nsds, \
        t_nuf, t_num, \
    t_occurence, t_og, t_ogdet, t_ogtype, t_oklabfn, t_oklchfn, t_onetwo, t_onetwothree, t_onoff, t_ontology, t_opacity, t_open, t_operator, \
        t_order, t_orientation, t_origin, t_overflow, t_overlay, t_over_under
#define SSC_TYPES_N_O_MAX t_over_under

#define SSC_TYPES_P_1 \
    t_page_orientation, t_paint, t_paintkeyword, t_paint_order, t_pam_ccv, t_pam_status, t_panose1, t_part, t_pcmm_status, t_percent, t_percentish, \
        t_percent_flexible, t_percent_n, t_percents_nf, t_percents_flexible, t_percents_n, t_percent_or_not, t_phase, t_phase_x, t_pics, \
        t_plus_1_7, t_plusstyle, t_pointer_events, t_points, t_popover, t_popovertargetaction, t_position, t_position_lcrtcb, t_position_lcr_len, \
        t_position_lcrtcb_len, t_position_tcb_len, t_position_lr_len, t_position_lrtb_len, t_position_tb_len, t_positions, t_positive, t_positive_1_2, \
        t_positive_i, t_positive_n, t_pragma, t_prefix, t_preload, t_preload5, t_preserveaspectratio, t_preserveaspectratio10, t_preserveaspectratio12
#define SSC_TYPES_P_1_MAX t_preserveaspectratio12

#define SSC_TYPES_P_2 \
        t_pri_img_colour, t_pri_img_orientation, t_pri_img_season, t_pri_img_setting, t_pri_img_technique, t_pri_img_viewpoint, t_print, t_prism_ad_pos, \
        t_prism_ad_type, t_prism_ag_type, t_prism_audience_sector, t_prism_ccv, t_prism_class, t_prism_contenttype, t_prism_cvp, t_prism_fccv, \
        t_prism_genre, t_prism_icv, t_prism_issue_type, t_prism_pasv, t_prism_pcv, t_prism_pfv, t_prism_ptv, t_prism_rcv, t_prism_rcv_opt, \
        t_prism_role, t_prism_tablet_ad, t_prs_action, t_prs_duty, t_propagate, t_pseudo, t_pseudonamedspace, t_pt
#define SSC_TYPES_P_2_MAX t_pt

#define SSC_TYPES_Q_R \
    t_q, t_quote_style, \
    t_radial_1, t_radial_4, t_radial_ending, t_radial_size, t_rap, t_ratio, t_ratio_a, t_rational, t_rationals, t_rating, t_rdf_parsetype, t_rdfa_typeof, \
        t_real, t_real_1_2, t_real_1_up, t_real_ai, t_real_i, t_real_n, t_real_ni, t_real_percent, t_real_percent_n, t_real_perflex, t_reals, t_reals_1_up, \
        t_recipe_content, t_recipe_course, t_recipe_cuisine, t_recipe_dietary, t_recipe_dish, t_recipe_exclusion, t_recipe_kit, t_recipe_meal, \
        t_recipe_method, t_recipe_source, t_recipe_skill, t_recipe_special, t_recipe_time, t_rect_round, t_referrer, t_refresh, t_refx, t_refy, \
        t_regex, t_rel, t_rel_a, t_rel_avoid, t_rel_css, t_rel_illegal, t_rel_link, t_rel_obsolete, t_rendering_colour_space, t_rendering_in_tents, \
        t_repeatcount, t_resolution, t_restart, t_result, t_reveal_trans, t_rgbafn, t_rgbfn, t_role, t_roles, t_roman_dsc, t_root_url, t_rotate, \
        t_rotate_anim, t_rotate_upright, t_row_column, t_rowscols, t_rsvp, t_rules
#define SSC_TYPES_Q_R_MAX t_rules

#define SSC_TYPES_S \
    t_safe_unsafe, t_sandbox, t_sandboxen, t_scale_down, t_scan, t_scei, t_scope, t_script, t_scrolling, t_second, t_semitone, t_setback_offset, t_settype, \
        t_severity, t_sex, t_sgml, t_sha1, t_sha256, t_shadow, t_shape, t_shape3, t_shape4, t_shape7, t_shape_none_uri, t_shape_fn, t_shape_fn_circle, \
        t_shape_fn_ellipse, t_shape_fn_polygon, t_shape_uri, t_shape_rendering, t_shape_rcp, t_shadowinherit, t_short, t_side, t_size, t_size3, \
        t_size_inlinesize, t_sizes, t_sizex, t_slash, t_smei, t_snap, t_spacer, t_spacing, t_spreadmethod, t_srcset, t_ssi, t_ssi_comparison, t_ssi_config, \
        t_ssi_echo, t_ssi_encoding, t_ssi_env, t_ssi_f, t_ssi_include, t_ssi_set, t_ssi_sizefmt, t_start, t_startend, t_startends, t_step, t_step_position, \
        t_stitchtiles, t_streamedcontents, t_stress, t_stripe, t_style, t_supports,  t_sym, t_syncbehaviour, t_syncbehaviourdefault
#define SSC_TYPES_S_MAX t_syncbehaviourdefault

#define SSC_TYPES_SVG \
        t_svg_align, t_svg_baselineshift, t_svg_baseprofile, t_svg_clip, t_svg_colour_profile, t_svg_content, t_svg_direction, t_svg_display, \
            t_svg_duration, t_svg_feature, t_svg_features, t_svg_fontstretch, t_svg_fontstretch_ff, t_svg_fontstyle, t_svg_fontstyle_ff, t_svg_fontvariant, \
            t_svg_fontvariant_ff, t_svg_fontweight, t_svg_fontweight_ff, t_svg_fontweights, t_svg_host, t_svg_method, t_svg_mode, t_svg_name_iri, \
            t_svg_overflow, t_svg_phase, t_svg_playbackorder, t_svg_profile_name, t_svg_rendering_intent, t_svg_shape, t_svg_shapefn, t_svg_side, t_svg_src, \
            t_svg_svg, t_svg_time, t_svg_time_default, t_svg_time_inherit, t_svg_time_none, t_svg_timelinebegin, t_svg_transform, t_svg_two_profile, \
            t_svg_type, t_svg_units, t_svg_values, t_svg_version, t_svg_version_grand, t_svg_viewbox, t_svg_viewboxrect
#define SSC_TYPES_SVG_MAX t_svg_viewboxrect

#define SSC_TYPES_T \
    t_tableframe, t_tablevalues, t_target, t_tbalign, t_tblri, t_tcbalign, t_tdscope, t_tel, t_tendstotype, t_text, t_text_2, t_text_2n, t_text_a, \
        t_text_na, t_text_decoration, t_textoverflow, t_text_rendering, t_texts, t_texts_n, t_tfa, t_tfi, t_tfmu, t_tfn, t_tfu, t_tld, t_tokens, \
        t_to_lrtb, t_transform, t_transform_anim, t_transformbehaviour, t_transform_fn, t_transition_subtype, t_transition_type, t_transp, \
        t_transparentsz, t_truefalseempty, t_turbulence_type, t_type, t_type_fn, t_typeof, t_tz
#define SSC_TYPES_T_MAX t_tz

#define SSC_TYPES_U \
    t_ugeo, t_uid, t_under_ff, t_unicode_bidi, t_unit, t_unit_abs_len, t_unit_abs_per, t_unit_angle, t_unit_angle_per, t_unit_freq, t_unit_freq_per, \
        t_unit_rel_len, t_unit_rel_per, t_unit_res, t_unit_res_per, t_unit_time, t_unit_time_per, t_units, t_unsigned, t_unsigned_1_more, t_unsigned_1_more_a, \
        t_unsigned_byte, t_unsigned_short, t_unsigned_1_or_2, t_un_ex, t_unsigned_dosh, t_unsigned_n, t_unsigneds, t_uplr, t_urange, t_urational, t_urationals, \
        t_urifn, t_urifn_db, t_urifn_ni, t_urifn_str, t_urifn_xy, t_url, t_url_n, t_urls, t_urltemplate, t_user_modify
#define SSC_TYPES_U_MAX t_user_modify

#define SSC_TYPES_V_W \
    t_valign, t_valign3, t_valign_tmb, t_value, t_values, t_valuetype, t_valuetype2, t_vector_effect, t_vector_effect_12, t_vector_effect_2, \
        t_vector_effect_20, t_vector_effect_2s, t_version, t_vertical_align, t_vertical_align_enum, t_vgender, t_vid, t_viewportscreen, t_visibility, \
        t_visibility10, t_visibility11, t_vkind, t_vocab, t_vrel, t_vtt, t_vtype, t_vunit, t_vunits, \
    t_wanted, t_wallclock, t_week, t_whitespace, t_width, t_workertype, t_wrap, t_wrap3, t_writingmode, t_wxhs
 #define SSC_TYPES_V_W_MAX t_wxhs

#define SSC_TYPES_X_Z \
   t_x_content_type_options, t_x_dot_y, t_x_ua_compatible, t_xlinkactuate, t_xlinkactuate_onrequest, t_xlinkactuate_onload, t_xlinkshow, t_xlinkshow_a, \
        t_xlinkshow_e, t_xlinkshow_o, t_xlinktype, t_xmllink, t_xmlliteral, t_xmlns, t_xmlspace, t_xmlurl, t_xmpdm_audio_channel, t_xmpdm_audio_sample, \
        t_xmpdm_camera_angle, t_xmpdm_camera_move, t_xmpdm_pulldown, t_xmpdm_quality, t_xmpdm_scaletype, t_xmpdm_shotsize, t_xmpdm_stretchmode, \
        t_xmpdm_time_format, t_xmpdm_time_signature, t_xmpdm_type, t_xmpdm_video_alphamode, t_xmpdm_video_colourspace, t_xmpdm_video_fieldorder, \
        t_xmpdm_video_videoframerate, t_xmpdm_video_pixeldepth, \
        t_xmpg_type, t_xorder, t_xsdbool, \
    t_year, t_yearmonth, t_yesno, t_yesnoempty, \
    t_zero_or_one, t_zero_to_one, t_zero_to_ones, t_zoompan
#define SSC_TYPES_X_Z_MAX t_zoompan

#define SSC_TYPES   SSC_TYPES_0_9, SSC_TYPES_A, SSC_TYPES_B, SSC_TYPES_C, SSC_TYPES_CSS_A, SSC_TYPES_CSS_B_1, SSC_TYPES_CSS_B_2, SSC_TYPES_CSS_C_1, \
                    SSC_TYPES_CSS_C_2, SSC_TYPES_CSS_D_E, SSC_TYPES_CSS_F_1, SSC_TYPES_CSS_F_2, SSC_TYPES_CSS_G_I, SSC_TYPES_CSS_J_L, SSC_TYPES_CSS_M_N, \
                    SSC_TYPES_CSS_O_P, SSC_TYPES_CSS_R, SSC_TYPES_CSS_S, SSC_TYPES_CSS_T_1, SSC_TYPES_CSS_T_2, SSC_TYPES_CSS_U_Z, SSC_TYPES_D_E, SSC_TYPES_F, \
                    SSC_TYPES_G_H, SSC_TYPES_I, SSC_TYPES_J_L, SSC_TYPES_M_1, SSC_TYPES_M_2, SSC_TYPES_N_O, SSC_TYPES_P_1, SSC_TYPES_P_2, SSC_TYPES_Q_R, \
                    SSC_TYPES_S, SSC_TYPES_SVG, SSC_TYPES_T, SSC_TYPES_U, SSC_TYPES_V_W, SSC_TYPES_X_Z

typedef enum {
    t_unknown, SSC_TYPES, t_error } e_type;

typedef ::std::vector < e_type > vtype_t;

typedef enum { ub_bidioverride, ub_embed, ub_inherit, ub_isolate, ub_isolate_override, ub_normal, ub_plaintext } e_unicode_bidi;
typedef enum {  eu_cap, eu_ch, eu_cm, eu_cqb, eu_cqh, eu_cqi, eu_cqmin, eu_cqmax, eu_cqw, eu_db, eu_dpcm, eu_dpi, eu_dppx, eu_em, eu_ex,
                eu_ic, eu_in, eu_lh, eu_mm, eu_pc, eu_pt, eu_px, eu_q, eu_rem, eu_rlh, eu_vb, eu_vh, eu_vi, eu_vmin, eu_vmax, eu_vw } e_unit;
typedef enum { eua_cm, eus_in, eua_mm, eua_pc, eua_pt, eua_px, eua_q } e_unit_abs_len;
typedef enum { ean_deg, ean_grad, ean_rad, ean_turn } e_unit_angle;
typedef enum { euf_hz, euf_khz } e_unit_freq;
typedef enum { eur_em, eur_ex, eur_ch, eur_rem, eur_vh, eur_vmax, eur_vmin, eur_vw } e_unit_rel_len;
typedef enum { eur_dpcm, eur_dpi, eur_dppx } e_unit_res;
typedef enum { eut_ms, eur_s } e_unit_time;
typedef enum { w_en, w_pixels, w_relative } e_units;
typedef enum { di_down, di_left, di_right, di_up } e_uplr;
typedef enum { um_read_only, um_read_write, um_read_write_plaintext_only, um_write_only } e_user_modify;
typedef enum { va32_top, va32_middle, va32_bottom } e_valign_tmb;
typedef enum { va_top, va_middle, va_bottom, va_baseline } e_valign3;
typedef enum { vt_data, vt_object, vt_ref } e_valuetype;
typedef enum { v12_inherit, v12_none, v12_nonscalingstroke } e_vector_effect_12;
typedef enum { v2_fixedposition, v2_none, v2_nonrotation, v2_nonscalingstroke, v2_nonscalingsize } e_vector_effect_2;
typedef enum { eva_baseline, eva_sub, eva_super, eva_top, eva_text_top, eva_middle, eva_bottom, eva_text_bottom, eva_inherit } e_vertical_align_enum;
typedef enum { vs_viewport, vs_screen } e_viewportscreen;
typedef enum { vi0_visible, vi0_hidden, vi0_inherit } e_visibility10;
typedef enum { vi1_visible, vi1_hidden, vi1_collapse, vi1_inherit } e_visibility11;
typedef enum { vg_female, vg_male, vg_none, vg_other, vg_unknown } e_vgender;
typedef enum { vk_individual, vk_organisation, vk_group, vk_location } e_vkind;
typedef enum {  vr_acquaintance, vr_agent, vr_child, vr_colleague, vr_contact, vr_coresident, vr_coworker, vr_crush, vr_date,
                vr_emergency, vr_friend, vr_kin, vr_me, vr_met, vr_muse, vr_neighbor, vr_parent, vr_sibling, vr_spouse, vr_sweetheart } e_vrel;
typedef enum { vt_mobile, vt_fax, vt_pager, vt_sms, vt_textphone, vt_video, vt_voice } e_vtt;
typedef enum { vt_home, vt_work } e_vtype;
typedef enum { ws_normal, ws_pre, ws_nowrap, ws_pre_wrap, ws_break_spaces, ws_pre_line } e_whitespace;
typedef enum { wm_undefined, wm_addr, wm_link, wm_root } e_wm_status;
typedef enum { wt_classic, wt_module } e_workertype;
typedef enum { w_soft, w_hard } e_wrap;
typedef enum { w_horiz, w_vert } e_wrap3;
typedef enum { wm_lrtb, wm_rltb, wm_tbrl, wm_lr, wm_rl, wm_tb, wm_htb, wm_sideways_lr, wm_sideways_rl, wm_vrl, wm_vlr, wm_inherit } e_writingmode;
typedef enum { xls_new, xls_replace } e_xlinkshow_a;

typedef enum {  
    x_default,
    x_xhtml_1, x_xhtml_1_superseded, x_xhtml_11, x_xhtml_2, x_html,
    x_basic, x_bibo,
    x_cc, x_comments, x_crs, x_crs2,
    x_dbp, x_dbp_owl, x_dbr, x_dc, x_dc_terms, x_dt,
    x_ex, x_exsl,
    x_foaf,
    x_lxslt,
    x_mathml,
    x_owl,
    x_pam, x_pamp, x_pccm, x_pcm, x_pcv, x_pdf, x_photoshop, x_pim, x_pmi, x_prism, x_prism_ad, x_prl, x_prm, x_prs, x_psv, x_pur,
    x_rddl, x_rdf, x_rdfa, x_rdfs, x_rel, x_rng, x_rss,
    x_saxon, x_smil, x_soapenc11, x_soapenc12, x_stdim, x_stevt, x_stfnt, x_stjob, x_stref, x_stver, x_svg, x_syn,
    x_v, x_vcard1, x_vcard,
    x_wsdl11, x_wsdl12,
    x_xf, x_xhv, x_xi, x_xlink, x_xml, x_xmlevents, x_xmlns, x_xmp, x_xmpbj, x_xmpdm, x_xmpg, x_xmpgimg, x_xmpidq, x_xmpmm, x_xmprights, x_xmptpg, x_xsd, x_xslfo, x_xslt, x_xsi
} e_xmlns;

typedef enum { xs_default, xs_preserve } e_xmlspace;
typedef enum { xac_16channel, xac_51, xac_71, xac_mono, xac_other, xac_stereo } e_xmpdm_audio_channel;
typedef enum { xas_16int, xas_24int, xas_32int, xas_32float, xas_8int, xas_compressed, xas_other, xas_packed } e_xmpdm_audio_sample;
typedef enum { xca_birdseyeshot, xca_dutchangle, xca_eyelevel, xca_highangle, xca_lowangle, xca_overheadshot, xca_overtheshoulder, xca_pov, xca_reactionshot } e_xmpdm_camera_angle;
typedef enum {  xcm_aerial, xcm_boomdown, xcm_boomup, xcm_cranedown, xcm_craneup, xcm_dollyin, xcm_dollyout, xcm_panleft, xcm_panright,
                xcm_pedestaldown, xcm_pedestalup, xcm_tiltdown, xcm_tiltup, xcm_tracking, xcm_truckleft, xcm_truckright, xcm_zoomin, xcm_zoomout } e_xmpdm_camera_move;
typedef enum { xp_WSSWW, xp_SSWWW, xp_SWWWS, xp_WWWSS, xp_WWSSW, xp_WWWSW, xp_WWSWW, xp_WSWWW, xp_SWWWW, xp_WWWWS } e_xmpdm_pulldown;
typedef enum { xd_high, xd_low, xd_medium } e_xmpdm_quality;
typedef enum { xst_both, xst_major, xst_minor, xst_neither } e_xmpdm_scaletype;
typedef enum { xss_cu, xss_ecu, xss_ews, xss_mcu, xss_ms, xss_mws, xss_ws } e_xmpdm_shotsize;
typedef enum { xsm_beatsplice, xsm_fixedlength, xsm_hybrid, xsm_resample, xsm_timescale  } e_xmpdm_stretchmode;
typedef enum {  xtf_24timecode, xtf_23967timecode, xtf_2997droptimecode, xtf_2997nondroptimecode, xtf_25timecode, xtf_30timecode, xtf_50timecode,
                xtf_5994droptimecode, xtf_5994nondroptimecode, xtf_60timecode } e_xmpdm_time_format;
typedef enum { xts_24, xts_34, xts_44, xts_54, xts_74, xts_68, xts_98, xts_128, xts_other } e_xmpdm_time_signature;
typedef enum { xd_audio, xd_custom, xd_movie, xd_still } e_xmpdm_type;
typedef enum { xva_none, xva_premultiplied, xva_straight } e_xmpdm_video_alphamode;
typedef enum { xvc_ccir601, xvc_ccir709, xvc_srgb } e_xmpdm_video_colourspace;
typedef enum { xvf_lower, xvf_progressive, xvf_upper } e_xmpdm_video_fieldorder;
typedef enum { xvr_24, xvr_ntsc, xvr_pal } e_xmpdm_video_videoframerate;
typedef enum { xvp_16int, xvp_24int, xvp_32int, xvp_32float, xvp_8int, xvp_other } e_xmpdm_video_pixeldepth;
typedef enum { xt_process, xt_spot } e_xmpg_type;
typedef enum { or_document, or_list } e_xorder;
typedef enum { xb_0, xb_1, db_false, xd_true } e_xsdbool;
typedef enum { y_yes, y_no } e_yesno;
typedef enum { z_disable, z_magnify } e_zoompan;
