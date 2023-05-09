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
#include "type/type.h"

struct enum_name_t {
    e_type t_;
    const char* name_; };

enum_name_t enum_name [] =
{   { t_0_more, "0 more" },
    { t_0_to_255, "0 to 255" },
    { t_10, "10" },
    { t_1_more, "1 more" },
    { t_1_more_i, "1 more i" },
    { t_1_to_20, "1 to 20" },
    { t_1_to_7, "1 to 7" },
    { t_1_to_99, "1 to 99" },
    { t_10_int, "10 int" },
    { t_2pt, "2pt" },
    { t_2string, "2 string" },
    { t_4string, "4 string" },
    { t_4string_ni, "4 string ni" },
    { t_about, "about" },
    { t_absolute_url, "absolute url" },
    { t_accept, "accept" },
    { t_accrual_method, "accrual method" },
    { t_accrual_periodicity, "accrual periodicity" },
    { t_accrual_policy, "accrual policy" },
    { t_accumulate, "accumulate" },
    { t_accumulate0, "accumulate 0" },
    { t_accumulate1, "accumulate 1" },
    { t_accumulate2, "accumulate 2" },
    { t_action, "action" },
    { t_actiontype, "action type" },
    { t_actiontype2, "action type 2" },
    { t_additive, "additive" },
    { t_align, "align" },
    { t_align2070, "align 2070" },
    { t_align3, "align 3" },
    { t_aligndec, "align dec" },
    { t_alignfig, "align fig" },
    { t_alignment_baseline, "alignment baseline" },
    { t_alignplus, "align plus" },
    { t_angle, "angle" },
    { t_angle_a, "angle a" },
    { t_angle_ai, "angle ai" },
    { t_angle_i, "angle i" },
    { t_angle_n, "angle n" },
    { t_arabic_form, "arabic form" },
    { t_arabicenum, "arabi enum" },
    { t_aria_autocomplete, "aria autocomplete" },
    { t_aria_invalidity, "aria invalidity" },
    { t_aria_live, "aria live" },
    { t_aria_sort, "aria sort" },
    { t_as, "as" },
    { t_as_units, "as units" },
    { t_attributename, "attribute name" },
    { t_attributetype, "attribute type" },
    { t_audio_level, "audio level" },
    { t_autocapitalise, "autocapitalise" },
    { t_autocomplete, "autocomplete" },
    { t_autocompletes, "autocompletes" },
    { t_autocompletevaried, "autocomplete varied" },
    { t_b64, "b64" },
    { t_background, "background" },
    { t_bandwidth, "bandwidth" },
    { t_base, "base" },
    { t_baselineshift, "baseline shift" },
    { t_bb, "bb" },
    { t_beginvalue, "begin value" },
    { t_beginvaluelist, "begin value list" },
    { t_beginvalues, "begin values" },
    { t_behaviour, "behaviour" },
    { t_blocking, "blocking" },
    { t_bool, "bool" },
    { t_bools, "bools" },
    { t_border, "border" },
    { t_buffered_rendering, "buffered rendering" },
    { t_button, "button" },
    { t_cache, "cache" },
    { t_cachekey, "cachekey" },
    { t_calcfn, "calcfn" },
    { t_calcmode, "calcmode" },
    { t_captionalign, "caption align" },
    { t_capture, "capture" },
    { t_cc_permits, "cc permits" },
    { t_cc_prohibits, "cc prohibits" },
    { t_cc_requires, "cc requires" },
    { t_channelselector, "channel selector" },
    { t_char, "char" },
    { t_charset, "charset" },
    { t_charsets, "charsets" },
    { t_charspacing, "char spacing" },
    { t_citype, "citype" },
    { t_class, "class" },
    { t_clear, "clear" },
    { t_clear30, "clear 30" },
    { t_clip, "clip" },
    { t_clip_path_rule, "clip path rule" },
    { t_closure, "closure" },
    { t_cntype, "cntype" },
    { t_colour, "colour" },
    { t_colour_a, "colour a" },
    { t_colour_ci, "colour ci" },
    { t_colour_cii, "colour cii" },
    { t_colour_i, "colour i" },
    { t_colour_ii, "colour ii" },
    { t_colour_interpolation, "colour interpolation" },
    { t_colour_ni, "colour ni" },
    { t_colour_profile, "colour profile" },
    { t_colour_profile_name, "colour profile name" },
    { t_colour_profile_name_or_uri, "colour profile name or uri" },
    { t_colour_rendering, "colour rendering" },
    { t_colour_scheme, "colour scheme" },
    { t_colour_trans, "colour trans" },
    { t_colour_trans_i, "colour trans i" },
    { t_colour_v, "colour v" },
    { t_command, "command" },
    { t_comp_op, "comp op" },
    { t_compact, "compact" },
    { t_composite_operator, "composite operator" },
    { t_compositing, "compositing" },
    { t_conlit, "conlit" },
    { t_connect, "connect" },
    { t_content_encoding, "content encoding" },
    { t_content_encodings, "content encodings" },
    { t_content_type, "content type" },
    { t_context_menu, "context menu" },
    { t_controlslist, "controls list" },
    { t_cookie, "cookie" },
    { t_cookieid, "cookie id" },
    { t_cookies, "cookies" },
    { t_coordinatesystem, "coordinate system" },
    { t_coords, "coords" },
    { t_corp, "corp" },
    { t_cors, "cors" },
    { t_country, "country" },
    { t_crossout, "crossout" },
    { t_csp, "csp" },
    { t_csp_ancestor, "csp ancestor" },
    { t_csp_directive, "csp directive" },
    { t_csp_keyword, "csp keyword" },
    { t_csp_sauce, "csp sauce" },
    { t_csp_source, "csp source" },
    { t_css, "CSS" },
    { t_css_aaalri, "CSS aaal ri" },
    { t_css_aai, "CSS aai" },
    { t_css_absolute_size, "CSS absolute size" },
    { t_css_all, "CSS all" },
    { t_css_all_2, "CSS all 2" },
    { t_css_alpha, "CSS alpha" },
    { t_css_alpha_n, "CSS alpha n" },
    { t_css_appearance, "CSS appearance" },
    { t_css_attr, "CSS attr" },
    { t_css_azimuth, "CSS azimuth" },
    { t_css_azimuth_be, "CSS azimuth be" },
    { t_css_azimuth_e, "CSS azimuth e" },
    { t_css_azimuth_eb, "CSS azimuth eb" },
    { t_css_azimuth_es, "CSS azimuth es" },
    { t_css_azimuth_lri, "CSS azimuth lri" },
    { t_css_background, "CSS background" },
    { t_css_background_attachment, "CSS background attachment" },
    { t_css_background_position, "CSS background position" },
    { t_css_background_repeat, "CSS background repeat" },
    { t_css_backval, "CSS backval" },
    { t_css_bespoke, "CSS bespoke" },
    { t_css_border_collapse, "CSS border collapse" },
    { t_css_border_measure, "CSS border measure" },
    { t_css_border_spacing, "CSS border spacing" },
    { t_css_border_spacing_2, "CSS border spacing 2" },
    { t_css_border_style, "CSS border style" },
    { t_css_border_style_i, "CSS border style i" },
    { t_css_border_styles, "CSS border styles" },
    { t_css_border_width, "CSS border width" },
    { t_css_border_width_i, "CSS border width i" },
    { t_css_border_wsc, "CSS border wsc" },
    { t_css_border_wsc_i, "CSS border wsc i" },
    { t_css_borders_measure, "CSS borders measure" },
    { t_css_borders_measure_i, "CSS borders measure i" },
    { t_css_box_sizing, "CSS box sizing" },
    { t_css_caret, "CSS caret" },
    { t_css_caret_shape, "CSS caret shape" },
    { t_css_clear, "CSS clear" },
    { t_css_coin1, "CSS coin 1" },
    { t_css_coin2, "CSS coin 2" },
    { t_css_coin3, "CSS coin 3" },
    { t_css_col, "CSS col" },
    { t_css_colour, "CSS colour" },
    { t_css_colour_3, "CSS colour 3" },
    { t_css_colour_4, "CSS colour 4" },
    { t_css_colour_a, "CSS colour auto" },
    { t_css_colour_interpolation, "CSS colour interpolation" },
    { t_css_content, "CSS content" },
    { t_css_content_base, "CSS content base" },
    { t_css_content_enum, "CSS content enum" },
    { t_css_content_fn, "CSS content fn" },
    { t_css_content_twice, "CSS content twice" },
    { t_css_counter, "CSS counter" },
    { t_css_counter_ii, "CSS counter ii" },
    { t_css_counter_iin, "CSS counter iin" },
    { t_css_counter_set, "CSS counter set" },
    { t_css_counters, "CSS counters" },
    { t_css_cue, "CSS cue" },
    { t_css_cues, "CSS cues" },
    { t_css_cursor, "CSS cursor" },
    { t_css_cursor_e, "CSS cursor e" },
    { t_css_cursor_url, "CSS cursor url" },
    { t_css_display, "CSS display" },
    { t_css_earnest, "CSS earnest" },
    { t_css_elevation, "CSS elevation" },
    { t_css_elevation_e, "CSS elevation e" },
    { t_css_empty_cells, "CSS empty cells" },
    { t_css_font, "CSS t_css_font" },
    { t_css_font_families, "CSS font families" },
    { t_css_font_size, "CSS font size" },
    { t_css_font_style, "CSS font style" },
    { t_css_font_style_e, "CSS font style e" },
    { t_css_font_weight, "CSS font weight" },
    { t_css_fn, "CSS fn" },
    { t_css_frame, "CSS frame" },
    { t_css_generic_family, "CSS generic family" },
    { t_css_hue, "CSS hue" },
    { t_css_hue_interpolation, "CSS hue interpolation" },
    { t_css_hue_n, "CSS hue n" },
    { t_css_id, "CSS id" },
    { t_css_image, "CSS image" },
    { t_css_inherit, "CSS inherit" },
    { t_css_kbd_lhs, "CSS kbd lhs" },
    { t_css_kdb_nav, "CSS kdb nav" },
    { t_css_kbd_rhs, "CSS kbd rhs" },
    { t_css_lang, "CSS lang" },
    { t_css_langs, "CSS langs" },
    { t_css_length, "CSS length" },
    { t_css_length_a, "CSS length a" },
    { t_css_length_ai, "CSS length ai" },
    { t_css_length_twice, "CSS length twice" },
    { t_css_line_height, "CSS line height" },
    { t_css_list_style, "CSS list style" },
    { t_css_list_style_position, "CSS list style position" },
    { t_css_list_style_type, "CSS list style type" },
    { t_css_local_url, "CSS local url" },
    { t_css_ls_val, "CSS ls val" },
    { t_css_margins, "CSS margins" },
    { t_css_mark, "CSS mark" },
    { t_css_marks, "CSS marks" },
    { t_css_marx, "CSS marx" },
    { t_css_nth, "CSS nth" },
    { t_css_nth_oe, "CSS nth odd/even" },
    { t_css_orientation, "CSS orientation" },
    { t_css_outline, "CSS outline" },
    { t_css_outline_i, "CSS outline i" },
    { t_css_outline_style, "CSS outline style" },
    { t_css_outlines, "CSS outlines" },
    { t_css_overflow, "CSS overflow" },
    { t_css_pause, "CSS pause" },
    { t_css_pause_i, "CSS pause i" },
    { t_css_pauses, "CSS pauses" },
    { t_css_pitch, "CSS pitch" },
    { t_css_pitch_e, "CSS pitch e" },
    { t_css_play_during, "CSS play during" },
    { t_css_play_during_mr, "CSS play during mr" },
    { t_css_polar, "CSS polar" },
    { t_css_position, "CSS position" },
    { t_css_property, "CSS property" },
    { t_css_rect, "CSS rect" },
    { t_css_rect_ai, "CSS rect ai" },
    { t_css_rect_fn, "CSS rect fn" },
    { t_css_relative_size, "CSS relative size" },
    { t_css_resize, "CSS resize" },
    { t_css_rgb_xyz, "CSS rgb xyz" },
    { t_css_size, "CSS size" },
    { t_css_spacing, "CSS spacing" },
    { t_css_speak, "CSS speak" },
    { t_css_speak_header, "CSS speak header" },
    { t_css_speak_numeral, "CSS speak numeral" },
    { t_css_speak_punctuation, "CSS speak punctuation" },
    { t_css_speech_rate, "CSS speech rate" },
    { t_css_speech_rate_e, "CSS speech rate e" },
    { t_css_src, "CSS src" },
    { t_css_statement, "CSS statement" },
    { t_css_table_layout, "CSS table layout" },
    { t_css_text_align, "CSS text align" },
    { t_css_text_decoration, "CSS text decoration" },
    { t_css_text_resize, "CSS text resize" },
    { t_css_text_shadow, "CSS text shadow" },
    { t_css_text_transform, "CSS text transform" },
    { t_css_url, "CSS url" },
    { t_css_user_select, "CSS user select" },
    { t_css_val_con, "CSS val con" },
    { t_css_val_fn, "CSS val fn" },
    { t_css_vertical_align, "CSS vertical align" },
    { t_css_voice_family, "CSS voice family" },
    { t_css_volume, "CSS volume" },
    { t_css_volume_e, "CSS volume e" },
    { t_css_whitespace, "CSS whitespace" },
    { t_css_wsc_val, "CSS wsc val" },
    { t_csvw_direction, "csvw direction" },
    { t_curie, "curie" },
    { t_curie_safe, "curie safe" },
    { t_curies, "curies" },
    { t_currency, "currency" },
    { t_current_colour_sz, "current colour sz" },
    { t_cursor, "cursor" },
    { t_cursor_f, "cursor f" },
    { t_cursor_i, "cursor i" },
    { t_d, "d" },
    { t_dashes, "dashes" },
    { t_data, "data" },
    { t_dataformatas, "data format as" },
    { t_datetime, "datetime" },
    { t_datetime_4, "datetime 4" },
    { t_datetime_5, "datetime 5" },
    { t_datetime_absolute, "datetime absolute" },
    { t_datetime_local, "datetime local" },
    { t_day, "day" },
    { t_decalign, "dec align" },
    { t_decoding, "decoding" },
    { t_defaultaction, "default action" },
    { t_depth, "depth" },
    { t_determiner, "determiner" },
    { t_device, "device" },
    { t_dingbat, "dingbat" },
    { t_dir, "dir" },
    { t_direction, "direction" },
    { t_display, "display" },
    { t_display_align, "display align" },
    { t_dominantbaseline, "dominant baseline" },
    { t_dosh, "dosh" },
    { t_dsc, "dsc" },
    { t_dur, "dur" },
    { t_dur_repeat, "dur repeat" },
    { t_duration, "duration" },
    { t_duration_media, "duration media" },
    { t_dynamic_range, "dynamic range" },
    { t_edgemode, "edge mode" },
    { t_edi, "edi" },
    { t_edit, "edit" },
    { t_editable, "editable" },
    { t_effect, "effect" },
    { t_email, "email" },
    { t_emails, "emails" },
    { t_enable_background, "enable background" },
    { t_enctype, "enc type" },
    { t_end, "end" },
    { t_endvaluelist, "end value list" },
    { t_enterkeyhint, "enter key hint" },
    { t_environment_blending, "environment blending" },
    { t_existential, "existential" },
    { t_expected, "expected" },
    { t_featurepolicy, "feature policy" },
    { t_figalign, "fig align" },
    { t_filename, "filename" },
    { t_filesize, "file size" },
    { t_fill, "fill" },
    { t_fill_opacity, "fill opacity" },
    { t_fill_rule, "fill rule" },
    { t_fill_ve, "fill ve" },
    { t_fillanim, "fill anim" },
    { t_filter_in, "filter in" },
    { t_filterres, "filter res" },
    { t_fixedcolour, "fixed colour" },
    { t_fixedpoint, "fixed point" },
    { t_focushighlight, "focu highlight" },
    { t_font, "font" },
    { t_font_enum, "font enum" },
    { t_font_families, "font families" },
    { t_font_family, "font family" },
    { t_font_variant, "font variant" },
    { t_font_variant_2, "font variant 2" },
    { t_font_variant_2s, "font variant 2s" },
    { t_font_variant_caps, "font variant caps" },
    { t_font_variant_east_asian, "font variant east asian" },
    { t_font_variant_east_asians, "font variant east asians" },
    { t_font_variant_ligature, "font variant ligature" },
    { t_font_variant_ligatures, "font variant ligatures" },
    { t_font_variant_numeric, "font variant numeric" },
    { t_font_variant_numerics, "font variant numerics" },
    { t_font_variant_position, "font variant position" },
    { t_fontname, "fontname" },
    { t_fontnia, "font nia" },
    { t_fontsize, "font size" },
    { t_fontsizeadjust, "font size adjust" },
    { t_fontstretch, "font stretch" },
    { t_fontstretches, "font stretches" },
    { t_fontstyle, "font style" },
    { t_fontvariant, "font variant" },
    { t_fontvariants, "font variants" },
    { t_fontweight, "font weight" },
    { t_forced_colours, "forced colours" },
    { t_form, "form" },
    { t_format, "format" },
    { t_formaturi, "format uri" },
    { t_frame, "frame" },
    { t_frame4, "frame 4" },
    { t_framespacing, "frame spacing" },
    { t_frequency, "frequency" },
    { t_gamut, "gamut" },
    { t_gender, "gender" },
    { t_generic, "generic" },
    { t_glyphname, "glyph name" },
    { t_glyphnames, "glyph names" },
    { t_groupalign, "group align" },
    { t_halign, "h align" },
    { t_hash_fn, "hash fn" },
    { t_hash_ref, "hash ref" },
    { t_height, "height" },
    { t_hex, "hex" },
    { t_hidden, "hidden" },
    { t_hidden_ex, "hidden ex" },
    { t_hour, "hour" },
    { t_hslafn, "hsla fn" },
    { t_hslfn, "hsl fn" },
    { t_hslfn4, "hsl fn 4" },
    { t_html, "html" },
    { t_html_boolean, "html boolean" },
    { t_httpequiv, "http equiv" },
    { t_hue, "hue" },
    { t_hue_n, "hue n" },
    { t_hunit, "hunit" },
    { t_hv, "hv" },
    { t_hwbfn, "hwb fn" },
    { t_labfn, "lab fn" },
    { t_lchfn, "lch fn" },
    { t_oklabfn, "oklab fn" },
    { t_oklchfn, "oklch fn" },
    { t_colourfn, "colour fn" },
    { t_icalfreq, "ical freq" },
    { t_icc, "icc" },
    { t_icccolour, "icc colour" },
    { t_id, "id" },
    { t_identifier_url, "identifier url" },
    { t_idref, "idref" },
    { t_idrefs, "idrefs" },
    { t_illegal, "illegal" },
    { t_image_rendering, "image rendering" },
    { t_imcastr, "imcastr" },
    { t_imgsizes, "img sizes" },
    { t_importance, "importance" },
    { t_in, "in" },
    { t_indentalign, "indent align" },
    { t_indentalign2, "indent align 2" },
    { t_indentshift2, "indent shift 2" },
    { t_index, "index" },
    { t_infixlinebreakstyle, "infix line break style" },
    { t_initialvisibility, "initial visibility" },
    { t_inky, "inky" },
    { t_inlist, "inlist" },
    { t_inputaccept, "input accept" },
    { t_inputmode, "input mode" },
    { t_inputplus, "input plus" },
    { t_inputtype, "input type" },
    { t_inputtype3, "input type 3" },
    { t_inputtype32, "input type 3/2" },
    { t_inputtype4, "input type4" },
    { t_inputtype5, "input type5" },
    { t_integer, "integer" },
    { t_integer_ai, "integer ai" },
    { t_integer_i, "integer i" },
    { t_integer_or_percent, "integer or percent" },
    { t_intent, "intent" },
    { t_intent_app, "intent app" },
    { t_intent_args, "intent args" },
    { t_intent_conlit, "intent conlit" },
    { t_intent_hint, "intent hint" },
    { t_intent_ref, "intent ref" },
    { t_inverted_colours, "inverted colours" },
    { t_ip_address, "ip address" },
    { t_is, "is" },
    { t_isbn, "isbn" },
    { t_issn, "issn" },
    { t_itemid, "item id" },
    { t_itemprop, "item prop" },
    { t_itemref, "item ref" },
    { t_itemtype, "item type" },
    { t_js_lang, "JS lang" },
    { t_js_lang_map, "JS lang map" },
    { t_js_map, "JS map" },
    { t_js_term, "JS term" },
    { t_js_type, "JS type" },
    { t_js_value, "JS value" },
    { t_js_version, "JS version" },
    { t_jtoken, "j token" },
    { t_just_date, "just date" },
    { t_just_time, "just time" },
    { t_key, "key" },
    { t_keygentype, "key gen type" },
    { t_keyspline, "key spline" },
    { t_keysplines, "key splines" },
    { t_keytimes, "key times" },
    { t_keytype, "key type" },
    { t_kind, "kind" },
    { t_lang, "lang" },
    { t_langq, "lang q" },
    { t_langqs, "lang qs" },
    { t_langs, "langs" },
    { t_larnalign, "larn align" },
    { t_layout, "layout" },
    { t_lcralign, "lcr align" },
    { t_lcraligns, "lcr aligns" },
    { t_lcrd, "lcrd" },
    { t_lcrds, "lcrds" },
    { t_lcrdss, "lcrdss" },
    { t_lcrnalign, "lcrn align" },
    { t_length, "length" },
    { t_length_absolute, "length absolute" },
    { t_length_relative, "length relative" },
    { t_lengthadjust, "length adjust" },
    { t_line_height, "line height" },
    { t_linebreak, "line break" },
    { t_linebreakstyle, "line break style" },
    { t_linecap, "line cap" },
    { t_linejoin, "line join" },
    { t_linethickness, "line thickness" },
    { t_link, "link" },
    { t_linkarg, "link arg" },
    { t_linkargs, "link args" },
    { t_linkitself, "link itself" },
    { t_linkparam, "lin kparam" },
    { t_links, "links" },
    { t_listtype, "list type" },
    { t_literal, "literal" },
    { t_loading, "loading" },
    { t_localfn, "local fn" },
    { t_local_url, "local url" },
    { t_location, "location" },
    { t_longdivstyle, "long div style" },
    { t_loop, "loop" },
    { t_loopie, "loopie" },
    { t_lraalign, "lra align" },
    { t_lralign, "lr align" },
    { t_lrnalign, "lrn align" },
    { t_lrnialign, "lrni align" },
    { t_lspace, "l space" },
    { t_ltr_rtl, "ltr rtl" },
    { t_mah, "mah" },
    { t_marked_up, "marked up" },
    { t_marker, "marker" },
    { t_markerunits, "marker units" },
    { t_mathalign, "math align" },
    { t_mathalign_n, "math align n" },
    { t_mathaligns, "math aligns" },
    { t_mathclosure, "math closure" },
    { t_mathdisplay, "math display" },
    { t_mathfontstyle, "math font style" },
    { t_mathfontweight, "math font weight" },
    { t_mathform, "math form" },
    { t_mathframe, "math frame" },
    { t_mathlocation, "math location" },
    { t_mathmode, "math mode" },
    { t_mathnotation, "math notation" },
    { t_mathnotations, "math notations" },
    { t_mathoccurence, "math occurence" },
    { t_mathorder, "math order" },
    { t_mathoverflow, "math overflow" },
    { t_mathscope, "math scope" },
    { t_mathside, "math side" },
    { t_mathsize, "math size" },
    { t_mathspace, "math space" },
    { t_mathspaceauto, "math space auto" },
    { t_mathspacefit, "math space fit" },
    { t_mathspaceinfinity, "math space infinity" },
    { t_mathvariant, "math variant" },
    { t_mathvertauto, "math vertauto" },
    { t_matrix_values, "matrix values" },
    { t_matrixtype, "matrix type" },
    { t_mb, "mb" },
    { t_measure, "measure" },
    { t_measure_4, "measure 4" },
    { t_measure_a, "measure a" },
    { t_measure_ai, "measure ai" },
    { t_measure_i, "measure i" },
    { t_measure_in, "measure in" },
    { t_measure_ni, "measure ni" },
    { t_measure_or_more, "measure or more" },
    { t_measures, "measures" },
    { t_measures_a, "measures a" },
    { t_measures_i, "measures i" },
    { t_media, "media" },
    { t_media_display_mode, "media display mode" },
    { t_media_hover, "media hover" },
    { t_media_inline, "media inline" },
    { t_media_orientation, "media orientation" },
    { t_media_overflow, "media overflow" },
    { t_media_pointer, "media pointer" },
    { t_media_prefers, "media prefers" },
    { t_media_prefers_2, "media prefers 2" },
    { t_media_scripting, "media scripting" },
    { t_media_update, "media update" },
    { t_meetslice, "meet slice" },
    { t_menuitem, "menu item" },
    { t_menutype, "menu type" },
    { t_metaname, "metaname" },
    { t_method, "method" },
    { t_methodological, "methodological" },
    { t_mf_availability, "mf availability" },
    { t_mf_category, "mf category" },
    { t_mf_class, "mf class" },
    { t_mf_identifier, "mf identifier" },
    { t_mf_itemtype, "mf itemtype" },
    { t_mf_listing_action, "mf listing action" },
    { t_mf_listing_actions, "mf listing actions" },
    { t_mf_method, "mf method" },
    { t_mf_reviewtype, "mf reviewtype" },
    { t_mf_status, "mf status" },
    { t_mime, "mime" },
    { t_mimelist, "mime list" },
    { t_mimemodule, "mime module" },
    { t_mimeq, "mime q" },
    { t_mimeqs, "mime qs" },
    { t_mimestar, "mime star" },
    { t_minute, "minute" },
    { t_mode, "mode" },
    { t_month, "month" },
    { t_monthday, "month day" },
    { t_morphology_operator, "morphology operator" },
    { t_mql, "mql" },
    { t_mqls, "mqls" },
    { t_myersbriggs, "pseudopsychology" },
    { t_name, "name" },
    { t_namedspace, "named space" },
    { t_nameref, "name ref" },
    { t_namespace, "name space" },
    { t_nav_controls, "nav controls" },
    { t_navigation, "navigation" },
    { t_negative, "negative" },
    { t_nit_macro, "nit macro" },
    { t_nit_section, "nit section" },
    { t_not_0, "not 0" },
    { t_not_empty, "not empty" },
    { t_not_neg, "not neg" },
    { t_not_pos, "not pos" },
    { t_notation, "notation" },
    { t_notations, "notations" },
    { t_nsd, "nsd" },
    { t_nsds, "nsds" },
    { t_nuf, "nuf" },
    { t_num, "num" },
    { t_occurence, "occurence" },
    { t_og, "og" },
    { t_ogdet, "og det" },
    { t_ogtype, "og type" },
    { t_onoff, "onoff" },
    { t_opacity, "opacity" },
    { t_open, "open" },
    { t_operator, "operator" },
    { t_order, "order" },
    { t_orientation, "orientation" },
    { t_origin, "origin" },
    { t_overflow, "overflow" },
    { t_overlay, "overlay" },
    { t_page_orientation, "page orientation" },
    { t_paint, "paint" },
    { t_paint_order, "paint order" },
    { t_paintkeyword, "paintkeyword" },
    { t_panose1, "panose1" },
    { t_percent, "percent" },
    { t_percent_flexible, "percent flexible" },
    { t_percent_n, "percent n" },
    { t_percent_or_not, "t_percent_or_not" },
    { t_phase, "phase" },
    { t_phase_x, "phase x" },
    { t_pics, "pics" },
    { t_plus_1_7, "plus 1 7" },
    { t_plusstyle, "plus style" },
    { t_pointer_events, "pointer events" },
    { t_points, "points" },
    { t_positive, "positive" },
    { t_positive_1_2, "positive 1 2" },
    { t_pragma, "pragma" },
    { t_prefix, "prefix" },
    { t_preload, "preload" },
    { t_preload5, "preload 5" },
    { t_preserveaspectratio, "preserve aspect ratio" },
    { t_preserveaspectratio10, "preserve aspect ratio 10" },
    { t_preserveaspectratio12, "preserve aspect ratio 12" },
    { t_print, "print" },
    { t_propagate, "propagate" },
    { t_pseudo, "pseudo" },
    { t_pseudonamedspace, "pseudo named space" },
    { t_pt, "pt" },
    { t_q, "q" },
    { t_quote_style, "quote style" },
    { t_rap, "rap" },
    { t_rating, "rating" },
    { t_rdf_parsetype, "rdf parse type" },
    { t_rdfa_typeof, "rdfa type of" },
    { t_real, "real" },
    { t_real_1_2, "real 1 2" },
    { t_real_ai, "real ai" },
    { t_real_i, "real i" },
    { t_real_ni, "real ni" },
    { t_reals, "reals" },
    { t_real_percent_n, "real % n" },
    { t_referrer, "referrer" },
    { t_refresh, "refresh" },
    { t_refx, "refx" },
    { t_refy, "refy" },
    { t_regex, "regex" },
    { t_rel, "rel" },
    { t_rel_a, "rel a" },
    { t_rel_avoid, "rel avoid" },
    { t_rel_css, "rel css" },
    { t_rel_illegal, "rel illegal" },
    { t_rel_link, "rel link" },
    { t_rel_obsolete, "rel obsolete" },
    { t_rendering_colour_space, "rendering colour space" },
    { t_rendering_in_tents, "rendering in tents" },
    { t_repeatcount, "repeat count" },
    { t_restart, "restart" },
    { t_result, "result" },
    { t_reveal_trans, "reveal trans" },
    { t_rgbafn, "rgba fn" },
    { t_rgbfn, "rgb fn" },
    { t_role, "role" },
    { t_roles, "roles" },
    { t_roman_dsc, "roman dsc" },
    { t_root_url, "root url" },
    { t_rotate, "rotate" },
    { t_rotate_anim, "rotate anim" },
    { t_rowscols, "rows cols" },
    { t_rsvp, "rsvp" },
    { t_rules, "rules" },
    { t_sandbox, "sandbox" },
    { t_sandboxen, "sandboxen" },
    { t_scan, "scan" },
    { t_scei, "scei" },
    { t_schema_type, "schema type" },
    { t_scope, "scope" },
    { t_script, "script" },
    { t_scrolling, "scrolling" },
    { t_second, "second" },
    { t_setback_offset, "setback offset" },
    { t_settype, "settype" },
    { t_severity, "severity" },
    { t_sex, "sex" },
    { t_sgml, "sgml" },
    { t_sha1, "sha1" },
    { t_sha256, "sha256" },
    { t_shadow, "shadow" },
    { t_shadowinherit, "shadow inherit" },
    { t_shape, "shape" },
    { t_shape3, "shape 3" },
    { t_shape4, "shape 4" },
    { t_shape7, "shape 7" },
    { t_shape_fn, "shape fn" },
    { t_shape_fn_circle, "shape fn circle" },
    { t_shape_fn_ellipse, "shape fn ellipse" },
    { t_shape_fn_polygon, "shape fn polygon" },
    { t_shape_none_uri, "shape none uri" },
    { t_shape_rcp, "shape rcp" },
    { t_shape_rendering, "shape rendering" },
    { t_shape_uri, "shape uri" },
    { t_short, "short" },
    { t_side, "side" },
    { t_size, "size" },
    { t_size3, "size 3" },
    { t_sizes, "sizes" },
    { t_sizex, "size x" },
    { t_smei, "smei" },
    { t_slash, "slash" },
    { t_spacer, "spacer" },
    { t_spacing, "spacing" },
    { t_spreadmethod, "spread method" },
    { t_srcset, "src set" },
    { t_ssi, "ssi" },
    { t_ssi_comparison, "ssi comparison" },
    { t_ssi_config, "ssi config" },
    { t_ssi_echo, "ssi echo" },
    { t_ssi_encoding, "ssi encoding" },
    { t_ssi_env, "ssi env" },
    { t_ssi_f, "ssi f" },
    { t_ssi_include, "ssi include" },
    { t_ssi_set, "ssi set" },
    { t_ssi_sizefmt, "ssi sizefmt" },
    { t_start, "start" },
    { t_startend, "startend" },
    { t_step, "step" },
    { t_stitchtiles, "stitch tiles" },
    { t_streamedcontents, "streamed contents" },
    { t_style, "style" },
    { t_svg_align, "SVG align" },
    { t_svg_baselineshift, "SVG baseline shift" },
    { t_svg_baseprofile, "SVG base profile" },
    { t_svg_clip, "SVG clip" },
    { t_svg_colour_profile, "SVG colour profile" },
    { t_svg_content, "SVG content" },
    { t_svg_direction, "SVG direction" },
    { t_svg_display, "SVG display" },
    { t_svg_duration, "SVG duration" },
    { t_svg_feature, "SVG feature" },
    { t_svg_features, "SVG features" },
    { t_svg_fontstretch, "SVG font stretch" },
    { t_svg_fontstretch_ff, "SVG font stretch ff" },
    { t_svg_fontstyle, "SVG font style" },
    { t_svg_fontstyle_ff, "SVG font style ff" },
    { t_svg_fontvariant, "SVG font variant" },
    { t_svg_fontvariant_ff, "SVG font variant ff" },
    { t_svg_fontweight, "SVG font weight" },
    { t_svg_fontweight_ff, "SVG font weight ff" },
    { t_svg_fontweights, "SVG font weights" },
    { t_svg_host, "SVG host" },
    { t_svg_method, "SVG method" },
    { t_svg_mode, "SVG mode" },
    { t_svg_name_iri, "SVG name iri" },
    { t_svg_overflow, "SVG overflow" },
    { t_svg_phase, "SVG phase" },
    { t_svg_playbackorder, "SVG playback order" },
    { t_svg_profile_name, "SVG profile name" },
    { t_svg_rendering_intent, "SVG rendering intent" },
    { t_svg_shape, "SVG shape" },
    { t_svg_shapefn, "SVG shape fn" },
    { t_svg_side, "SVG side" },
    { t_svg_src, "SVG src" },
    { t_svg_svg, "SVG svg" },
    { t_svg_time, "SVG time" },
    { t_svg_time_default, "SVG time default" },
    { t_svg_time_inherit, "SVG time inherit" },
    { t_svg_time_none, "SVG time none" },
    { t_svg_timelinebegin, "SVG timeline begin" },
    { t_svg_transform, "SVG transform" },
    { t_svg_two_profile, "SVG 2 profile" },
    { t_svg_type, "SVG type" },
    { t_svg_units, "SVG units" },
    { t_svg_values, "SVG values" },
    { t_svg_version, "SVG version" },
    { t_svg_version_grand, "SVG version grand" },
    { t_svg_viewbox, "SVG view box" },
    { t_svg_viewboxrect, "SVG view box rect" },
    { t_sym, "sym" },
    { t_syncbehaviour, "sync behaviour" },
    { t_syncbehaviourdefault, "sync behaviour default" },
    { t_tableframe, "table frame" },
    { t_tablevalues, "table values" },
    { t_target, "target" },
    { t_tbalign, "tb align" },
    { t_tblri, "tbl ri" },
    { t_tdscope, "td scope" },
    { t_tel, "tel" },
    { t_tendstotype, "tends to type" },
    { t_text, "text" },
    { t_text_decoration, "text decoration" },
    { t_text_rendering, "text rendering" },
    { t_textoverflow, "text overflow" },
    { t_tfa, "tfa" },
    { t_tfi, "tfi" },
    { t_tfmu, "tfmu" },
    { t_tfn, "tfn" },
    { t_tfu, "tfu" },
    { t_tokens, "tokens" },
    { t_transform, "transform" },
    { t_transform_anim, "transform anim" },
    { t_transform_fn, "transform fn" },
    { t_transformbehaviour, "transform behaviour" },
    { t_transition_subtype, "transition subtype" },
    { t_transition_type, "transition type" },
    { t_transp, "trans p" },
    { t_transparentsz, "transparent sz" },
    { t_truefalseempty, "true false empty" },
    { t_turbulence_type, "turbulence type" },
    { t_type, "type" },
    { t_typeof, "type of" },
    { t_tz, "tz" },
    { t_ugeo, "u geo" },
    { t_uid, "uid" },
    { t_un_ex, "un ex" },
    { t_unicode_bidi, "unicode bidi" },
    { t_unit, "unit" },
    { t_unit_abs_len, "unit_abs_len" },
    { t_unit_abs_per, "unit_abs_per" },
    { t_unit_angle, "unit_angle" },
    { t_unit_angle_per, "unit_angle_per" },
    { t_unit_freq, "unit_freq" },
    { t_unit_freq_per, "unit_freq_per" },
    { t_unit_rel_len, "unit_rel_len" },
    { t_unit_rel_per, "unit_rel_per" },
    { t_unit_res, "unit_res" },
    { t_unit_res_per, "unit_res_per" },
    { t_unit_time, "unit_time" },
    { t_unit_time_per, "unit_time_per" },
    { t_units, "units" },
    { t_unknown, "unknown" },
    { t_unsigned, "unsigned" },
    { t_unsigned_1_or_2, "unsigned 1 or 2" },
    { t_unsigned_byte, "unsigned byte" },
    { t_unsigned_dosh, "unsigned dosh" },
    { t_unsigned_short, "unsigned short" },
    { t_uplr, "uplr" },
    { t_urange, "u range" },
    { t_urifn, "uri fn" },
    { t_urifn_ni, "uri fn ni" },
    { t_urifn_xy, "uri fn xy" },
    { t_url, "url" },
    { t_urls, "urls" },
    { t_urltemplate, "url template" },
    { t_valign, "v align" },
    { t_valign3, "v align 3" },
    { t_valign_tmb, "v align tmb" },
    { t_value, "value" },
    { t_values, "values" },
    { t_valuetype, "value type" },
    { t_valuetype2, "value type 2" },
    { t_vector_effect, "vector effect" },
    { t_vector_effect_12, "vector effect 12" },
    { t_vector_effect_2, "vector effect 2" },
    { t_vector_effect_20, "vector effect 20" },
    { t_vector_effect_2s, "vector effect 2s" },
    { t_version, "version" },
    { t_vertical_align, "vertical align" },
    { t_vertical_align_enum, "vertical align enum" },
    { t_vgender, "v gender" },
    { t_vid, "v id" },
    { t_viewportscreen, "viewport screen" },
    { t_visibility, "visibility" },
    { t_visibility10, "visibility 10" },
    { t_visibility11, "visibility 11" },
    { t_vkind, "v kind" },
    { t_vocab, "vocab" },
    { t_vrel, "v rel" },
    { t_vtt, "vtt" },
    { t_vtype, "v type" },
    { t_vunit, "v unit" },
    { t_vunits, "v units" },
    { t_wallclock, "wall clock" },
    { t_wanted, "wanted" },
    { t_week, "week" },
    { t_whitespace, "whitespace" },
    { t_width, "width" },
    { t_workertype, "worker type" },
    { t_wrap, "wrap" },
    { t_wrap3, "wrap 3" },
    { t_writingmode, "writing mode" },
    { t_wxhs, "wxhs" },
    { t_x_content_type_options, "x content type options" },
    { t_x_ua_compatible, "x ua compatible" },
    { t_xlinkactuate, "x link actuate" },
    { t_xlinkactuate_onload, "x link actuate on load" },
    { t_xlinkactuate_onrequest, "x link actuate on request" },
    { t_xlinkshow, "x link show" },
    { t_xlinkshow_a, "x link show a" },
    { t_xlinkshow_e, "x link show e" },
    { t_xlinkshow_o, "x link show o" },
    { t_xlinktype, "x link type" },
    { t_xmllink, "xml link" },
    { t_xmlliteral, "xml literal" },
    { t_xmlns, "xmlns" },
    { t_xmlspace, "xml space" },
    { t_xmlurl, "xml url" },
    { t_xorder, " xorder" },
    { t_xsdbool, "xsd bool" },
    { t_year, "year" },
    { t_yearmonth, "year month" },
    { t_yesno, "yes no" },
    { t_yesnoempty, "yes no empty" },
    { t_zero_or_one, "zero or one" },
    { t_zero_to_one, "zero to one" },
    { t_zero_to_ones, "zero to ones" },
    { t_zoompan, "zoom pan" },

    { t_error, "error" } };

vstr_t vtn;

void type_name_init ()
{   vtn.resize (t_error);
    for (int i = 0; GSL_AT (enum_name, i).t_ != t_error; ++i)
        vtn.at (GSL_AT (enum_name, i).t_) = GSL_AT (enum_name, i).name_;
#ifdef DEBUG
    for (int i = 0; i < t_error; ++i)
        if (vtn.at (i).empty ())
            outstr.err ("Missing type name at ", ::boost::lexical_cast < ::std::string > (i), "\n");
#endif // DEBUG
}

::std::string type_name (const e_type e)
{   PRESUME (e <= t_error, __FILE__, __LINE__);
    PRESUME (! vtn.at (e).empty (), __FILE__, __LINE__);
    return vtn.at (e); }
