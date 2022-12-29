/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

struct sz_nullptr { CONSTEXPR static char const* sz () { return nullptr; } };

struct sz_EMPTY { CONSTEXPR static char const* sz () { return ""; } };
struct sz_0 { CONSTEXPR static char const* sz () { return "0"; } };
struct sz_1 { CONSTEXPR static char const* sz () { return "1"; } };
struct sz_1_0 { CONSTEXPR static char const* sz () { return "1.0"; } };
struct sz_1_1 { CONSTEXPR static char const* sz () { return "1.1"; } };
struct sz_1_2 { CONSTEXPR static char const* sz () { return "1.2"; } };
struct sz_2_0 { CONSTEXPR static char const* sz () { return "2.0"; } };
struct sz__blank { CONSTEXPR static char const* sz () { return "_blank"; } };
struct sz__parent { CONSTEXPR static char const* sz () { return "_parent"; } };
struct sz__self { CONSTEXPR static char const* sz () { return "_self"; } };
struct sz__top { CONSTEXPR static char const* sz () { return "_top"; } };
struct sz_a { CONSTEXPR static char const* sz () { return "A"; } };
struct sz_abbrev { CONSTEXPR static char const* sz () { return "abbrev"; } };
struct sz_above { CONSTEXPR static char const* sz () { return "above"; } };
struct sz_accesskey { CONSTEXPR static char const* sz () { return "accesskey"; } };
struct sz_active { CONSTEXPR static char const* sz () { return "active"; } };
struct sz_after { CONSTEXPR static char const* sz () { return "after"; } };
struct sz_all { CONSTEXPR static char const* sz () { return "all"; } };
struct sz_align { CONSTEXPR static char const* sz () { return "align"; } };
struct sz_alternate { CONSTEXPR static char const* sz () { return "alternate"; } };
struct sz_always { CONSTEXPR static char const* sz () { return "always"; } };
struct sz_anonymous { CONSTEXPR static char const* sz () { return "anonymous"; } };
struct sz_appointment { CONSTEXPR static char const* sz () { return "appointment"; } };
struct sz_app_urlencoded { CONSTEXPR static char const* sz () { return "application/x-www-form-urlencoded"; } };
struct sz_ascending { CONSTEXPR static char const* sz () { return "ascending"; } };
struct sz_assertive { CONSTEXPR static char const* sz () { return "assertive"; } };
struct sz_async { CONSTEXPR static char const* sz () { return "async"; } };
struct sz_auto { CONSTEXPR static char const* sz () { return "auto"; } };
struct sz_autoreverse { CONSTEXPR static char const* sz () { return "auto-reverse"; } };
struct sz_b { CONSTEXPR static char const* sz () { return "B"; } };
struct sz_baseline { CONSTEXPR static char const* sz () { return "baseline"; } };
struct sz_basic { CONSTEXPR static char const* sz () { return "basic"; } };
struct sz_before { CONSTEXPR static char const* sz () { return "before"; } };
struct sz_below { CONSTEXPR static char const* sz () { return "below"; } };
struct sz_bevel { CONSTEXPR static char const* sz () { return "bevel"; } };
struct sz_block { CONSTEXPR static char const* sz () { return "block"; } };
struct sz_bold { CONSTEXPR static char const* sz () { return "bold"; } };
struct sz_both { CONSTEXPR static char const* sz () { return "both"; } };
struct sz_bottom { CONSTEXPR static char const* sz () { return "bottom"; } };
struct sz_bubble { CONSTEXPR static char const* sz () { return "bubble"; } };
struct sz_butt { CONSTEXPR static char const* sz () { return "butt"; } };
struct sz_button { CONSTEXPR static char const* sz () { return "button"; } };
struct sz_bytes { CONSTEXPR static char const* sz () { return "bytes"; } };
struct sz_cancel { CONSTEXPR static char const* sz () { return "cancel"; } };
struct sz_cancelled { CONSTEXPR static char const* sz () { return "cancelled"; } };
struct sz_canslip { CONSTEXPR static char const* sz () { return "canSlip"; } };
struct sz_capture { CONSTEXPR static char const* sz () { return "capture"; } };
struct sz_capitalise { CONSTEXPR static char const* sz () { return "capitalize"; } };
struct sz_centre { CONSTEXPR static char const* sz () { return "center"; } };
struct sz_cc_attribution { CONSTEXPR static char const* sz () { return "cc:Attribution"; } };
struct sz_cc_commercialuse { CONSTEXPR static char const* sz () { return "cc:CommercialUse"; } };
struct sz_cc_derivativeworks { CONSTEXPR static char const* sz () { return "cc:DerivativeWorks"; } };
struct sz_cc_distribution { CONSTEXPR static char const* sz () { return "cc:Distribution"; } };
struct sz_cc_notice  { CONSTEXPR static char const* sz () { return "cc:Notice "; } };
struct sz_cc_reproduction { CONSTEXPR static char const* sz () { return "cc:Reproduction"; } };
struct sz_cc_sharealike { CONSTEXPR static char const* sz () { return "cc:ShareAlike"; } };
struct sz_cc_sourcecode { CONSTEXPR static char const* sz () { return "cc:SourceCode"; } };
struct sz_characters { CONSTEXPR static char const* sz () { return "characters"; } };
struct sz_checkbox { CONSTEXPR static char const* sz () { return "checkbox"; } };
struct sz_circle { CONSTEXPR static char const* sz () { return "circle"; } };
struct sz_changed { CONSTEXPR static char const* sz () { return "changed"; } };
struct sz_classic { CONSTEXPR static char const* sz () { return "classic"; } };
struct sz_closed { CONSTEXPR static char const* sz () { return "closed"; } };
struct sz_closedopen { CONSTEXPR static char const* sz () { return "closed-open"; } };
struct sz_col { CONSTEXPR static char const* sz () { return "col"; } };
struct sz_colgroup { CONSTEXPR static char const* sz () { return "colgroup"; } };
struct sz_collapse { CONSTEXPR static char const* sz () { return "collapse"; } };
struct sz_colon { CONSTEXPR static char const* sz () { return ":"; } };
struct sz_colondot { CONSTEXPR static char const* sz () { return ":."; } };
struct sz_colonspace { CONSTEXPR static char const* sz () { return ": "; } };
struct sz_comma { CONSTEXPR static char const* sz () { return ","; } };
struct sz_commaspace { CONSTEXPR static char const* sz () { return ", "; } };
struct sz_command { CONSTEXPR static char const* sz () { return "command"; } };
struct sz_compress { CONSTEXPR static char const* sz () { return "compress"; } };
struct sz_conference { CONSTEXPR static char const* sz () { return "conference"; } };
struct sz_confidential { CONSTEXPR static char const* sz () { return "confidential"; } };
struct sz_confirmed { CONSTEXPR static char const* sz () { return "confirmed"; } };
struct sz_context { CONSTEXPR static char const* sz () { return "context"; } };
struct sz_continue { CONSTEXPR static char const* sz () { return "continue"; } };
struct sz_cross_origin { CONSTEXPR static char const* sz () { return "cross-origin"; } };
struct sz_CSS { CONSTEXPR static char const* sz () { return "CSS"; } };
struct sz_currentcolour { CONSTEXPR static char const* sz () { return "currentColor"; } };
struct sz_dashed { CONSTEXPR static char const* sz () { return "dashed"; } };
struct sz_data { CONSTEXPR static char const* sz () { return "data"; } };
struct sz_decimal { CONSTEXPR static char const* sz () { return "decimal"; } };
struct sz_decimalpoint { CONSTEXPR static char const* sz () { return "decimalpoint"; } };
struct sz_decoding { CONSTEXPR static char const* sz () { return "decoding"; } };
struct sz_default { CONSTEXPR static char const* sz () { return "default"; } };
struct sz_defer { CONSTEXPR static char const* sz () { return "defer"; } };
struct sz_deflate { CONSTEXPR static char const* sz () { return "deflate"; } };
struct sz_deleted { CONSTEXPR static char const* sz () { return "deleted"; } };
struct sz_descending { CONSTEXPR static char const* sz () { return "descending"; } };
struct sz_dialog { CONSTEXPR static char const* sz () { return "dialog"; } };
struct sz_dilate { CONSTEXPR static char const* sz () { return "dilate"; } };
struct sz_disable { CONSTEXPR static char const* sz () { return "disable"; } };
struct sz_disc { CONSTEXPR static char const* sz () { return "disc"; } };
struct sz_discard { CONSTEXPR static char const* sz () { return "discard"; } };
struct sz_discrete { CONSTEXPR static char const* sz () { return "discrete"; } };
struct sz_display { CONSTEXPR static char const* sz () { return "display"; } };
struct sz_document { CONSTEXPR static char const* sz () { return "document"; } };
struct sz_down { CONSTEXPR static char const* sz () { return "down"; } };
struct sz_dsa { CONSTEXPR static char const* sz () { return "dsa"; } };
struct sz_dsssl { CONSTEXPR static char const* sz () { return "dsssl-lite"; } };
struct sz_duplicate { CONSTEXPR static char const* sz () { return "duplicate"; } };
struct sz_dynamic { CONSTEXPR static char const* sz () { return "dynamic"; } };
struct sz_eager { CONSTEXPR static char const* sz () { return "eager"; } };
struct sz_ec { CONSTEXPR static char const* sz () { return "ec"; } };
struct sz_echomsg { CONSTEXPR static char const* sz () { return "echomsg"; } };
struct sz_elide { CONSTEXPR static char const* sz () { return "elide"; } };
struct sz_ellipse { CONSTEXPR static char const* sz () { return "ellipse"; } };
struct sz_embed { CONSTEXPR static char const* sz () { return "embed"; } };
struct sz_en { CONSTEXPR static char const* sz () { return "en"; } };
struct sz_enable { CONSTEXPR static char const* sz () { return "enable"; } };
struct sz_end { CONSTEXPR static char const* sz () { return "end"; } };
struct sz_encoding { CONSTEXPR static char const* sz () { return "encoding"; } };
struct sz_environment { CONSTEXPR static char const* sz () { return "environment"; } };
struct sz_erode { CONSTEXPR static char const* sz () { return "erode"; } };
struct sz_errmsg { CONSTEXPR static char const* sz () { return "errmsg"; } };
struct sz_evenodd { CONSTEXPR static char const* sz () { return "evenodd"; } };
struct sz_exact { CONSTEXPR static char const* sz () { return "exact"; } };
struct sz_expo { CONSTEXPR static char const* sz () { return "expo"; } };
struct sz_false { CONSTEXPR static char const* sz () { return "false"; } };
struct sz_female { CONSTEXPR static char const* sz () { return "female"; } };
struct sz_file { CONSTEXPR static char const* sz () { return "file"; } };
struct sz_fill { CONSTEXPR static char const* sz () { return "fill"; } };
struct sz_fillpaint { CONSTEXPR static char const* sz () { return "fillPaint"; } };
struct sz_first_letter { CONSTEXPR static char const* sz () { return "first-letter"; } };
struct sz_first_line { CONSTEXPR static char const* sz () { return "first-line"; } };
struct sz_fit { CONSTEXPR static char const* sz () { return "fit"; } };
struct sz_fixed { CONSTEXPR static char const* sz () { return "fixed"; } };
struct sz_float { CONSTEXPR static char const* sz () { return "float"; } };
struct sz_forwardonly { CONSTEXPR static char const* sz () { return "forwardOnly"; } };
struct sz_freeze { CONSTEXPR static char const* sz () { return "freeze"; } };
struct sz_fs { CONSTEXPR static char const* sz () { return "fs"; } };
struct sz_full { CONSTEXPR static char const* sz () { return "full"; } };
struct sz_functionmodel { CONSTEXPR static char const* sz () { return "function-model"; } };
struct sz_g { CONSTEXPR static char const* sz () { return "G"; } };
struct sz_get { CONSTEXPR static char const* sz () { return "get"; } };
struct sz_gamma { CONSTEXPR static char const* sz () { return "gamma"; } };
struct sz_global { CONSTEXPR static char const* sz () { return "global"; } };
struct sz_grammar { CONSTEXPR static char const* sz () { return "grammar"; } };
struct sz_group { CONSTEXPR static char const* sz () { return "group"; } };
struct sz_gzip { CONSTEXPR static char const* sz () { return "gzip"; } };
struct sz_h { CONSTEXPR static char const* sz () { return "h"; } };
struct sz_hard { CONSTEXPR static char const* sz () { return "hard"; } };
struct sz_hash { CONSTEXPR static char const* sz () { return "#"; } };
struct sz_hidden { CONSTEXPR static char const* sz () { return "hidden"; } };
struct sz_high { CONSTEXPR static char const* sz () { return "high"; } };
struct sz_highlight { CONSTEXPR static char const* sz () { return "highlight"; } };
struct sz_home { CONSTEXPR static char const* sz () { return "home"; } };
struct sz_horiz { CONSTEXPR static char const* sz () { return "horiz"; } };
struct sz_horizontal { CONSTEXPR static char const* sz () { return "horizontal"; } };
struct sz_host { CONSTEXPR static char const* sz () { return "host"; } };
struct sz_html { CONSTEXPR static char const* sz () { return "html"; } };
struct sz_huge { CONSTEXPR static char const* sz () { return "huge"; } };
struct sz_hz { CONSTEXPR static char const* sz () { return "Hz"; } };
struct sz_identity { CONSTEXPR static char const* sz () { return "identity"; } };
struct sz_in_stock { CONSTEXPR static char const* sz () { return "in_stock"; } };
struct sz_important { CONSTEXPR static char const* sz () { return "important"; } };
struct sz_indefinite { CONSTEXPR static char const* sz () { return "indefinite"; } };
struct sz_independent { CONSTEXPR static char const* sz () { return "independent"; } };
struct sz_indentalign { CONSTEXPR static char const* sz () { return "indentalign"; } };
struct sz_indentshift { CONSTEXPR static char const* sz () { return "indentshift"; } };
struct sz_individual { CONSTEXPR static char const* sz () { return "individual"; } };
struct sz_infinity { CONSTEXPR static char const* sz () { return "infinity"; } };
struct sz_infixlinebreakstyle { CONSTEXPR static char const* sz () { return "infixlinebreakstyle"; } };
struct sz_infix { CONSTEXPR static char const* sz () { return "infix"; } };
struct sz_inherit { CONSTEXPR static char const* sz () { return "inherit"; } };
struct sz_initial { CONSTEXPR static char const* sz () { return "initial"; } };
struct sz_inline { CONSTEXPR static char const* sz () { return "inline"; } };
struct sz_inserted { CONSTEXPR static char const* sz () { return "inserted"; } };
struct sz_instore_only { CONSTEXPR static char const* sz () { return "instore_only"; } };
struct sz_interested { CONSTEXPR static char const* sz () { return "interested"; } };
struct sz_irrelevant { CONSTEXPR static char const* sz () { return "irrelevant"; } };
struct sz_isolated { CONSTEXPR static char const* sz () { return "isolated"; } };
struct sz_italic { CONSTEXPR static char const* sz () { return "italic"; } };
struct sz_json { CONSTEXPR static char const* sz () { return "json"; } };
struct sz_justify { CONSTEXPR static char const* sz () { return "justify"; } };
struct sz_keep { CONSTEXPR static char const* sz () { return "keep"; } };
struct sz_khz { CONSTEXPR static char const* sz () { return "kHz"; } };
struct sz_knockout { CONSTEXPR static char const* sz () { return "knockout"; } };
struct sz_large { CONSTEXPR static char const* sz () { return "large"; } };
struct sz_larger { CONSTEXPR static char const* sz () { return "larger"; } };
struct sz_lazy { CONSTEXPR static char const* sz () { return "lazy"; } };
struct sz_left { CONSTEXPR static char const* sz () { return "left"; } };
struct sz_leftoverlap { CONSTEXPR static char const* sz () { return "leftoverlap"; } };
struct sz_lexicographic { CONSTEXPR static char const* sz () { return "lexicographic"; } };
struct sz_linear { CONSTEXPR static char const* sz () { return "linear"; } };
struct sz_line { CONSTEXPR static char const* sz () { return "line"; } };
struct sz_list { CONSTEXPR static char const* sz () { return "list"; } };
struct sz_list_item { CONSTEXPR static char const* sz () { return "list-item"; } };
struct sz_local { CONSTEXPR static char const* sz () { return "local"; } };
struct sz_location { CONSTEXPR static char const* sz () { return "location"; } };
struct sz_locked { CONSTEXPR static char const* sz () { return "locked"; } };
struct sz_loose { CONSTEXPR static char const* sz () { return "loose"; } };
struct sz_low { CONSTEXPR static char const* sz () { return "low"; } };
struct sz_lowercase { CONSTEXPR static char const* sz () { return "lowercase"; } };
struct sz_ltr { CONSTEXPR static char const* sz () { return "ltr"; } };
struct sz_lro { CONSTEXPR static char const* sz () { return "lro"; } };
struct sz_magnify { CONSTEXPR static char const* sz () { return "magnify"; } };
struct sz_makeapp { CONSTEXPR static char const* sz () { return "makeapp"; } };
struct sz_male { CONSTEXPR static char const* sz () { return "male"; } };
struct sz_markers { CONSTEXPR static char const* sz () { return "markers"; } };
struct sz_maybe { CONSTEXPR static char const* sz () { return "maybe"; } };
struct sz_media { CONSTEXPR static char const* sz () { return "media"; } };
struct sz_medial { CONSTEXPR static char const* sz () { return "medial"; } };
struct sz_medium { CONSTEXPR static char const* sz () { return "medium"; } };
struct sz_meet { CONSTEXPR static char const* sz () { return "meet"; } };
struct sz_meeting { CONSTEXPR static char const* sz () { return "meeting"; } };
struct sz_metadata { CONSTEXPR static char const* sz () { return "metadata"; } };
struct sz_middle { CONSTEXPR static char const* sz () { return "middle"; } };
struct sz_miter { CONSTEXPR static char const* sz () { return "miter"; } };
struct sz_mixed { CONSTEXPR static char const* sz () { return "mixed"; } };
struct sz_module { CONSTEXPR static char const* sz () { return "module"; } };
struct sz_moved { CONSTEXPR static char const* sz () { return "moved"; } };
struct sz_ms { CONSTEXPR static char const* sz () { return "ms"; } };
struct sz_multipart_form_data { CONSTEXPR static char const* sz () { return "multipart/form-data"; } };
struct sz_multiset { CONSTEXPR static char const* sz () { return "multiset"; } };
struct sz_never { CONSTEXPR static char const* sz () { return "never"; } };
struct sz_new { CONSTEXPR static char const* sz () { return "new"; } };
struct sz_no { CONSTEXPR static char const* sz () { return "no"; } };
struct sz_no_repeat { CONSTEXPR static char const* sz () { return "no-repeat"; } };
struct sz_nodownload { CONSTEXPR static char const* sz () { return "nodownload"; } };
struct sz_nofullscreen { CONSTEXPR static char const* sz () { return "nofullscreen"; } };
struct sz_none { CONSTEXPR static char const* sz () { return "none"; } };
struct sz_nonscalingstroke { CONSTEXPR static char const* sz () { return "non-scaling-stroke"; } };
struct sz_nonzero { CONSTEXPR static char const* sz () { return "nonzero"; } };
struct sz_noremoteplayback { CONSTEXPR static char const* sz () { return "noremoteplayback"; } };
struct sz_normal { CONSTEXPR static char const* sz () { return "normal"; } };
struct sz_nosniff { CONSTEXPR static char const* sz () { return "nosniff"; } };
struct sz_nostitch { CONSTEXPR static char const* sz () { return "noStitch"; } };
struct sz_nowrap { CONSTEXPR static char const* sz () { return "nowrap"; } };
struct sz_numeric { CONSTEXPR static char const* sz () { return "numeric"; } };
struct sz_object { CONSTEXPR static char const* sz () { return "object"; } };
struct sz_object_bbox { CONSTEXPR static char const* sz () { return "object-bbox"; } };
struct sz_objectboundingbox { CONSTEXPR static char const* sz () { return "objectBoundingBox"; } };
struct sz_oblique { CONSTEXPR static char const* sz () { return "oblique"; } };
struct sz_off { CONSTEXPR static char const* sz () { return "off"; } };
struct sz_on { CONSTEXPR static char const* sz () { return "on"; } };
struct sz_onerror { CONSTEXPR static char const* sz () { return "onerror"; } };
struct sz_ondefine { CONSTEXPR static char const* sz () { return "onDefine"; } };
struct sz_onload { CONSTEXPR static char const* sz () { return "onLoad"; } };
struct sz_onrequest { CONSTEXPR static char const* sz () { return "onRequest"; } };
struct sz_onstart { CONSTEXPR static char const* sz () { return "onStart"; } };
struct sz_onuse { CONSTEXPR static char const* sz () { return "onUse"; } };
struct sz_opaque { CONSTEXPR static char const* sz () { return "opaque"; } };
struct sz_open { CONSTEXPR static char const* sz () { return "open"; } };
struct sz_openclosed { CONSTEXPR static char const* sz () { return "open-closed"; } };
struct sz_optimisespeed { CONSTEXPR static char const* sz () { return "optimizeSpeed"; } };
struct sz_optimisequality { CONSTEXPR static char const* sz () { return "optimizeQuality"; } };
struct sz_organisation { CONSTEXPR static char const* sz () { return "organization"; } };
struct sz_other { CONSTEXPR static char const* sz () { return "other"; } };
struct sz_out_of_stock { CONSTEXPR static char const* sz () { return "out_of_stock"; } };
struct sz_overlay { CONSTEXPR static char const* sz () { return "overlay"; } };
struct sz_paced { CONSTEXPR static char const* sz () { return "paced"; } };
struct sz_pad { CONSTEXPR static char const* sz () { return "pad"; } };
struct sz_perform { CONSTEXPR static char const* sz () { return "perform"; } };
struct sz_pixels { CONSTEXPR static char const* sz () { return "pixels"; } };
struct sz_plaintext { CONSTEXPR static char const* sz () { return "plaintext"; } };
struct sz_polite { CONSTEXPR static char const* sz () { return "polite"; } };
struct sz_poly { CONSTEXPR static char const* sz () { return "poly"; } };
struct sz_polygon { CONSTEXPR static char const* sz () { return "polygon"; } };
struct sz_popup { CONSTEXPR static char const* sz () { return "popup"; } };
struct sz_post { CONSTEXPR static char const* sz () { return "post"; } };
struct sz_postfix { CONSTEXPR static char const* sz () { return "postfix"; } };
struct sz_pre { CONSTEXPR static char const* sz () { return "pre"; } };
struct sz_prefix { CONSTEXPR static char const* sz () { return "prefix"; } };
struct sz_preorder { CONSTEXPR static char const* sz () { return "preorder"; } };
struct sz_preserve { CONSTEXPR static char const* sz () { return "preserve"; } };
struct sz_private { CONSTEXPR static char const* sz () { return "private"; } };
struct sz_public { CONSTEXPR static char const* sz () { return "public"; } };
struct sz_r { CONSTEXPR static char const* sz () { return "R"; } };
struct sz_radio { CONSTEXPR static char const* sz () { return "radio"; } };
struct sz_rect { CONSTEXPR static char const* sz () { return "rect"; } };
struct sz_ref { CONSTEXPR static char const* sz () { return "ref"; } };
struct sz_reflect { CONSTEXPR static char const* sz () { return "reflect"; } };
struct sz_refurbished { CONSTEXPR static char const* sz () { return "refurbished"; } };
struct sz_relative { CONSTEXPR static char const* sz () { return "relative"; } };
struct sz_relevant { CONSTEXPR static char const* sz () { return "relevant"; } };
struct sz_remove { CONSTEXPR static char const* sz () { return "remove"; } };
struct sz_render { CONSTEXPR static char const* sz () { return "render"; } };
struct sz_repeat { CONSTEXPR static char const* sz () { return "repeat"; } };
struct sz_repeat_x { CONSTEXPR static char const* sz () { return "repeat-x"; } };
struct sz_repeat_y { CONSTEXPR static char const* sz () { return "repeat-y"; } };
struct sz_replace { CONSTEXPR static char const* sz () { return "replace"; } };
struct sz_reset { CONSTEXPR static char const* sz () { return "reset"; } };
struct sz_right { CONSTEXPR static char const* sz () { return "right"; } };
struct sz_rightoverlap { CONSTEXPR static char const* sz () { return "rightoverlap"; } };
struct sz_round { CONSTEXPR static char const* sz () { return "round"; } };
struct sz_row { CONSTEXPR static char const* sz () { return "row"; } };
struct sz_rowgroup { CONSTEXPR static char const* sz () { return "rowgroup"; } };
struct sz_rs232 { CONSTEXPR static char const* sz () { return "rs232"; } };
struct sz_rsa { CONSTEXPR static char const* sz () { return "rsa"; } };
struct sz_rlo { CONSTEXPR static char const* sz () { return "rlo"; } };
struct sz_rtl { CONSTEXPR static char const* sz () { return "rtl"; } };
struct sz_s { CONSTEXPR static char const* sz () { return "s"; } };
struct sz_same_origin { CONSTEXPR static char const* sz () { return "same-origin"; } };
struct sz_same_site { CONSTEXPR static char const* sz () { return "same-site"; } };
struct sz_scale { CONSTEXPR static char const* sz () { return "scale"; } };
struct sz_scroll { CONSTEXPR static char const* sz () { return "scroll"; } };
struct sz_screen { CONSTEXPR static char const* sz () { return "screen"; } };
struct sz_self { CONSTEXPR static char const* sz () { return "self"; } };
struct sz_semicolon { CONSTEXPR static char const* sz () { return ";"; } };
struct sz_sentences { CONSTEXPR static char const* sz () { return "sentences"; } };
struct sz_silent { CONSTEXPR static char const* sz () { return "silent"; } };
struct sz_simple { CONSTEXPR static char const* sz () { return "simple"; } };
struct sz_sizefmt { CONSTEXPR static char const* sz () { return "sizefmt"; } };
struct sz_slice { CONSTEXPR static char const* sz () { return "slice"; } };
struct sz_slide { CONSTEXPR static char const* sz () { return "slide"; } };
struct sz_smallcaps { CONSTEXPR static char const* sz () { return "small-caps"; } };
struct sz_smaller { CONSTEXPR static char const* sz () { return "smaller"; } };
struct sz_soft { CONSTEXPR static char const* sz () { return "soft"; } };
struct sz_solid { CONSTEXPR static char const* sz () { return "solid"; } };
struct sz_space { CONSTEXPR static char const* sz () { return " "; } };
struct sz_space_comma { CONSTEXPR static char const* sz () { return " ,"; } };
struct sz_spaced { CONSTEXPR static char const* sz () { return "spaced"; } };
struct sz_spacing { CONSTEXPR static char const* sz () { return "spacing"; } };
struct sz_spacingandglyphs { CONSTEXPR static char const* sz () { return "spacingAndGlyphs"; } };
struct sz_spelling { CONSTEXPR static char const* sz () { return "spelling"; } };
struct sz_spline { CONSTEXPR static char const* sz () { return "spline"; } };
struct sz_square { CONSTEXPR static char const* sz () { return "square"; } };
struct sz_srgb { CONSTEXPR static char const* sz () { return "sRGB"; } };
struct sz_start { CONSTEXPR static char const* sz () { return "start"; } };
struct sz_static { CONSTEXPR static char const* sz () { return "static"; } };
struct sz_statusline { CONSTEXPR static char const* sz () { return "statusline"; } };
struct sz_stick { CONSTEXPR static char const* sz () { return "stick"; } };
struct sz_stitch { CONSTEXPR static char const* sz () { return "stitch"; } };
struct sz_stop { CONSTEXPR static char const* sz () { return "stop"; } };
struct sz_stretch { CONSTEXPR static char const* sz () { return "stretch"; } };
struct sz_stroke { CONSTEXPR static char const* sz () { return "stroke"; } };
struct sz_strokepaint { CONSTEXPR static char const* sz () { return "strokePaint"; } };
struct sz_strokewidth { CONSTEXPR static char const* sz () { return "strokeWidth"; } };
struct sz_structured_text { CONSTEXPR static char const* sz () { return "structured text"; } };
struct sz_sub { CONSTEXPR static char const* sz () { return "sub"; } };
struct sz_submit { CONSTEXPR static char const* sz () { return "submit"; } };
struct sz_sum { CONSTEXPR static char const* sz () { return "sum"; } };
struct sz_super { CONSTEXPR static char const* sz () { return "super"; } };
struct sz_svg { CONSTEXPR static char const* sz () { return "svg"; } };
struct sz_sync { CONSTEXPR static char const* sz () { return "sync"; } };
struct sz_table { CONSTEXPR static char const* sz () { return "table"; } };
struct sz_text { CONSTEXPR static char const* sz () { return "text"; } };
struct sz_text_plain { CONSTEXPR static char const* sz () { return "text/plain"; } };
struct sz_thick { CONSTEXPR static char const* sz () { return "thick"; } };
struct sz_thin { CONSTEXPR static char const* sz () { return "thin"; } };
struct sz_timefmt { CONSTEXPR static char const* sz () { return "timefmt"; } };
struct sz_tiny { CONSTEXPR static char const* sz () { return "tiny"; } };
struct sz_target { CONSTEXPR static char const* sz () { return "target"; } };
struct sz_tentative { CONSTEXPR static char const* sz () { return "tentative"; } };
struct sz_terminal { CONSTEXPR static char const* sz () { return "terminal"; } };
struct sz_tight { CONSTEXPR static char const* sz () { return "tight"; } };
struct sz_toggle { CONSTEXPR static char const* sz () { return "toggle"; } };
struct sz_toolbar { CONSTEXPR static char const* sz () { return "toolbar"; } };
struct sz_tooltip { CONSTEXPR static char const* sz () { return "tooltip"; } };
struct sz_top { CONSTEXPR static char const* sz () { return "top"; } };
struct sz_transparent { CONSTEXPR static char const* sz () { return "transparent"; } };
struct sz_triangle { CONSTEXPR static char const* sz () { return "triangle"; } };
struct sz_true { CONSTEXPR static char const* sz () { return "true"; } };
struct sz_truncate { CONSTEXPR static char const* sz () { return "truncate"; } };
struct sz_turbulence { CONSTEXPR static char const* sz () { return "turbulence"; } };
struct sz_twosided { CONSTEXPR static char const* sz () { return "two-sided"; } };
struct sz_undefined { CONSTEXPR static char const* sz () { return "undefined"; } };
struct sz_up { CONSTEXPR static char const* sz () { return "up"; } };
struct sz_uppercase { CONSTEXPR static char const* sz () { return "uppercase"; } };
struct sz_until_found { CONSTEXPR static char const* sz () { return "until-found"; } };
struct sz_url { CONSTEXPR static char const* sz () { return "url"; } };
struct sz_usb { CONSTEXPR static char const* sz () { return "usb"; } };
struct sz_use_credentials { CONSTEXPR static char const* sz () { return "use-credentials"; } };
struct sz_used { CONSTEXPR static char const* sz () { return "used"; } };
struct sz_user { CONSTEXPR static char const* sz () { return "user"; } };
struct sz_userspace { CONSTEXPR static char const* sz () { return "userspace"; } };
struct sz_userspaceonuse { CONSTEXPR static char const* sz () { return "userSpaceOnUse"; } };
struct sz_v { CONSTEXPR static char const* sz () { return "v"; } };
struct sz_value { CONSTEXPR static char const* sz () { return "value"; } };
struct sz_var { CONSTEXPR static char const* sz () { return "var"; } };
struct sz_vert { CONSTEXPR static char const* sz () { return "vert"; } };
struct sz_vertical { CONSTEXPR static char const* sz () { return "vertical"; } };
struct sz_viewport { CONSTEXPR static char const* sz () { return "viewport"; } };
struct sz_virtual { CONSTEXPR static char const* sz () { return "virtual"; } };
struct sz_visible { CONSTEXPR static char const* sz () { return "visible"; } };
struct sz_visited { CONSTEXPR static char const* sz () { return "visited"; } };
struct sz_w3c { CONSTEXPR static char const* sz () { return "w3c-style"; } };
struct sz_wallclock { CONSTEXPR static char const* sz () { return "wallclock"; } };
struct sz_whennotactive { CONSTEXPR static char const* sz () { return "whenNotActive"; } };
struct sz_whenstarted { CONSTEXPR static char const* sz () { return "whenStarted"; } };
struct sz_words { CONSTEXPR static char const* sz () { return "words"; } };
struct sz_work { CONSTEXPR static char const* sz () { return "work"; } };
struct sz_wrap { CONSTEXPR static char const* sz () { return "wrap"; } };
struct sz_XML { CONSTEXPR static char const* sz () { return "XML"; } };
struct sz_yes { CONSTEXPR static char const* sz () { return "yes"; } };
struct sz_zoom { CONSTEXPR static char const* sz () { return "zoom"; } };
