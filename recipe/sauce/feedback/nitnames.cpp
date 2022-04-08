/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "feedback/nitnames.h"

typedef struct {
    e_nit nit_;
    const char* sz_; } nitname;

const nitname nitnames [] =
{   { nit_308, "308" },
    { nit_400, "400" },
    { nit_401, "401" },
    { nit_403, "403" },
    { nit_404, "404" },
    { nit_407, "407" },
    { nit_408, "408" },
    { nit_451, "451" },
    { nit_a_area, "a_area" },
    { nit_chocolate_teapot, "chocolate_teapot" },
    { nit_abbreviated_correctly, "abbreviated_correctly" },
    { nit_all, "all" },
    { nit_attribute_name_unexpected_character, "attribute_name_unexpected_character" },
    { nit_attribute_recognised, "attribute_recognised" },
    { nit_attribute_unrecognised, "attribute_unrecognised" },
    { nit_attribute_unrecognised_here, "attribute_unrecognised_here" },
    { nit_attributes_on_closure, "attributes_on_closure" },
    { nit_bad_char, "bad_char" },
    { nit_bad_colour, "bad_colour" },
    { nit_bad_datetime, "bad_datetime" },
    { nit_unrecognised_value, "unrecognised_value" },
    { nit_bad_id, "bad_id" },
    { nit_bad_money, "bad_money" },
    { nit_bad_port, "bad_port" },
    { nit_invalid_attribute_version, "invalid_attribute_version" },
    { nit_base_undefined, "base_undefined" },
    { nit_bespoke_element, "bespoke_element" },
    { nit_bizarre_character_code, "bizarre_character_code" },
    { nit_badtarget, "badtarget" },
    { nit_cannot_create_file, "cannot_create_file" },
    { nit_cannot_delete, "cannot_delete" },
    { nit_cannot_find_mention, "cannot_find_mention" },
    { nit_cannot_load_css, "cannot_load_css" },
    { nit_cannot_open, "cannot_open" },
    { nit_cannot_read, "cannot_read" },
    { nit_cannot_update, "cannot_update" },
    { nit_cannot_write, "cannot_write" },
    { nit_charset_missing, "charset_missing" },
    { nit_class_microformat_property, "class_microformat_property" },
    { nit_class_microformat_vocabulary, "class_microformat_vocabulary" },
    { nit_code_unrecognised_here, "code_unrecognised_here" },
    { nit_confusion, "confusion" },
    { nit_correct_spelling, "correct_spelling" },
    { nit_correctly_spelt, "correctly_spelt" },
    { nit_debug, "debug" },
    { nit_denary_too_long, "denary_too_long" },
    { nit_deprecated_attribute, "deprecated_attribute" },
    { nit_deprecated_element, "deprecated_element" },
    { nit_detail, "detail" },
    { nit_doctype_incomprehensible, "doctype_incomprehensible" },
    { nit_double_angular_open, "double_angular_open" },
    { nit_double_slash, "double_slash" },
    { nit_dubious_denary, "dubious_denary" },
    { nit_dubious_html, "dubious_html" },
    { nit_duplicate_microformat, "duplicate_microformat" },
    { nit_duplicate_rel, "duplicate_rel" },
    { nit_element_bizarre_base, "element_bizarre_base" },
    { nit_element_has_no_closure, "element_has_no_closure" },
    { nit_element_no_type, "element_no_type" },
    { nit_element_offsite_base, "element_offsite_base" },
    { nit_embedded_lingo, "embedded_lingo" },
    { nit_empty, "empty" },
    { nit_empty_character_code, "empty_character_code" },
    { nit_empty_denary_code, "empty_denary_code" },
    { nit_empty_hex_code, "empty_hex_code" },
    { nit_empty_host, "empty_host" },
    { nit_empty_ipv6, "empty_ipv6" },
    { nit_encode_ampersand, "encode_ampersand" },
    { nit_enquote_value, "enquote_value" },
    { nit_eof_in_comment, "eof_in_comment" },
    { nit_eof_in_element, "eof_in_element" },
    { nit_eof_in_script, "eof_in_script" },
    { nit_eof_in_ssi, "eof_in_ssi" },
    { nit_eof_in_string, "eof_in_string" },
    { nit_eof_unexpected, "eof_unexpected" },
    { nit_evermore, "evermore" },
    { nit_excluded_attribute, "excluded_attribute" },
    { nit_export_none, "export_none" },
    { nit_found_css_class, "found_css_class" },
    { nit_found_rel, "found_rel" },
    { nit_free, "free" },
    { nit_gather, "gather" },
    { nit_hcard_infer, "hcard_infer" },
    { nit_hex_code_version, "hex_code_version" },
    { nit_hex_too_long, "hex_too_long" },
    { nit_html_contradictory, "html_contradictory" },
    { nit_html_recognised, "html_recognised" },
    { nit_html_unknown_sgml, "html_unknown_sgml" },
    { nit_html_unrecognised, "html_unrecognised" },
    { nit_sq_bra_ket, "sq_bra_ket" },
    { nit_id_exists, "id_exists" },
    { nit_unknown_element, "unknown_element" },
    { nit_immeasurable, "immeasurable" },
    { nit_infinite_number, "infinite_number" },
    { nit_insufficient, "insufficient" },
    { nit_internal_parsing_error, "internal_parsing_error" },
    { nit_invalid_addendum, "invalid_addendum" },
    { nit_invalid_character_code, "invalid_character_code" },
    { nit_invalid_character_denary, "invalid_character_denary" },
    { nit_invalid_character_hex, "invalid_character_hex" },
    { nit_invalid_denary, "invalid_denary" },
    { nit_invalid_domain, "invalid_domain" },
    { nit_invalid_element_version, "invalid_element_version" },
    { nit_invalid_ipv4, "invalid_ipv4" },
    { nit_invalid_ipv6, "invalid_ipv6" },
    { nit_invalid_protocol, "invalid_protocol" },
    { nit_is_existential, "is_existential" },
    { nit_itemprop_name_charset_equiv, "itemprop_name_charset_equiv" },
    { nit_lingo, "lingo" },
    { nit_link, "link" },
    { nit_lonely_ampersand, "lonely_ampersand" },
    { nit_long_title, "long_title" },
    { nit_malformed_ipv6, "malformed_ipv6" },
    { nit_mf_found, "mf_found" },
    { nit_mime, "mime" },
    { nit_missing_attribute_name, "missing_attribute_name" },
    { nit_missing_close, "missing_close" },
    { nit_missing_close_quote, "missing_close_quote" },
    { nit_missing_open, "missing_open" },
    { nit_missing_set_value, "missing_set_value" },
    { nit_mixed_mess, "mixed_mess" },
    { nit_n_fn, "n_fn" },
    { nit_newline_in_string, "newline_in_string" },
    { nit_no_compound, "no_compound" },
    { nit_no_curl, "no_curl" },
    { nit_ends_in_xmp, "ends_in_xmp" },
    { nit_no_fn, "no_fn" },
    { nit_no_form, "no_form" },
    { nit_math, "math" },
    { nit_no_n, "no_n" },
    { nit_no_plausible_vocab, "no_plausible_vocab" },
    { nit_svg, "svg" },
    { nit_no_vocab, "no_vocab" },
    { nit_not_an_integer, "not_an_integer" },
    { nit_not_just_protocol, "not_just_protocol" },
    { nit_nuts, "nuts" },
    { nit_only_once, "only_once" },
    { nit_one_title, "one_title" },
    { nit_orphan, "orphan" },
    { nit_phone, "phone" },
    { nit_pos_piracy, "pos_piracy" },
    { nit_positive, "positive" },
    { nit_presume_html_1, "presume_html_1" },
    { nit_presume_html_tags, "presume_html_tags" },
    { nit_prop_set, "prop_set" },
    { nit_protocol, "protocol" },
    { nit_protocol_empty, "protocol_empty" },
    { nit_public_missing, "public_missing" },
    { nit_public_unexpected, "public_unexpected" },
    { nit_rejected, "rejected" },
    { nit_rel_found, "rel_found" },
    { nit_relative_path, "relative_path" },
    { nit_sex, "sex" },
    { nit_sibling, "sibling" },
    { nit_single_character, "single_character" },
    { nit_sizes, "sizes" },
    { nit_splurge, "splurge" },
    { nit_spotted_css_class, "spotted_css_class" },
    { nit_ssi, "ssi" },
    { nit_sterile, "sterile" },
    { nit_style_not_css, "style_not_css" },
    { nit_sunk, "sunk" },
    { nit_symbol_aleady_defined, "symbol_aleady_defined" },
    { nit_text_html_expected, "text_html_expected" },
    { nit_timezone, "timezone" },
    { nit_unadvised, "unadvised" },
    { nit_unexpected_closure, "unexpected_closure" },
    { nit_unexpected_doctype_content, "unexpected_doctype_content" },
    { nit_unimplemented, "unimplemented" },
    { nit_unknown, "unknown" },
    { nit_unknown_protocol, "unknown_protocol" },
    { nit_unknown_rel, "unknown_rel" },
    { nit_unrecognised_attribute, "unrecognised_attribute" },
    { nit_unrecognised_character_code, "unrecognised_character_code" },
    { nit_unrecognised_class, "unrecognised_class" },
    { nit_unrecognised_rel, "unrecognised_rel" },
    { nit_unsigned, "unsigned" },
    { nit_url_empty, "url_empty" },
    { nit_url_empty_password, "url_empty_password" },
    { nit_url_id_unfound, "url_id_unfound" },
    { nit_url_insecure_password, "url_insecure_password" },
    { nit_url_missing_at, "url_missing_at" },
    { nit_url_not_found, "url_not_found" },
    { nit_use_double_quote_code, "use_double_quote_code" },
    { nit_use_quote_code, "use_quote_code" },
    { nit_value_expected, "value_expected" },
    { nit_webmention, "webmention" },
    { nit_write_wrote, "write_wrote" },
    { nit_wrong_parent, "wrong_parent" },
    { nit_wrong_secret, "wrong_secret" },
    { nit_wrong_version, "wrong_version" },
    { nit_xhtml_recognised, "xhtml_recognised" },
    { nit_html_tags, "html_tags" },
    { nit_html_plus, "html_plus" },
    { nit_html_1_0, "html_1_0" },
    { nit_html_2_0, "html_2_0" },
    { nit_html_2_0s, "html_2_0s" },
    { nit_html_2_0i, "html_2_0i" },
    { nit_html_2_0l1, "html_2_0l1" },
    { nit_html_2_0l1s, "html_2_0l1s" },
    { nit_html_2_0l2, "html_2_0l2" },
    { nit_html_3_0, "html_3_0" },
    { nit_html_3_2, "html_3_2" },
    { nit_html_4_00, "html_4_00" },
    { nit_html_4_00s, "html_4_00s" },
    { nit_html_4_00f, "html_4_00f" },
    { nit_html_4_01, "html_4_01" },
    { nit_html_4_01s, "html_4_01s" },
    { nit_html_4_01f, "html_4_01f" },
    { nit_xhtml_1_0, "xhtml_1_0" },
    { nit_xhtml_1_1, "xhtml_1_1" },
    { nit_xhtml_2_0, "xhtml_2_0" },
    { nit_html_5_0, "html_5_0" },
    { nit_html_5_1, "html_5_1" },
    { nit_html_5_2, "html_5_2" },
    { nit_html_5_3, "html_5_3" },
    { nit_html_5_living, "html_5_living" },

    { nit_context, "context" },
    { nit_only_elements, "only_elements" },
    { nit_closure_not_xmp, "closure_not_xmp" },
    { nit_one_isindex, "one_isindex" },
    { nit_rel_requires_href, "rel_requires_href" },
    { nit_urn_undefined, "urn_undefined" },
    { nit_methods_undefined, "methods_undefined" },
    { nit_render, "render" },
    { nit_mosaic_crash, "mosaic_crash" },
    { nit_use_htmlplus, "use_htmlplus" },
    { nit_inserted_missing_closure, "inserted_missing_closure" },
    { nit_inserted_missing_parent, "inserted_missing_parent" },
    { nit_equiv_error, "equiv_error" },
    { nit_ignoring_extra_content, "ignoring_extra_content" },
    { nit_missing_content, "missing_content" },
    { nit_equiv_refresh, "equiv_refresh" },
    { nit_x_ua_compatible, "x_ua_compatible" },
    { nit_use_metaname, "use_metaname" },
    { nit_not_html2_level_1, "not_html2_level_1" },
    { nit_title_required, "title_required" },
    { nit_bad_border, "bad_border" },
    { nit_bad_ismap, "bad_ismap" },
    { nit_bad_compact, "bad_compact" },
    { nit_file_requires_enctype, "file_requires_enctype" },
    { nit_form_urlencoded, "form_urlencoded" },
    { nit_use_post, "use_post" },
    { nit_mime_list, "mime_list" },
    { nit_url_missing_username, "url_missing_username" },
    { nit_1_to_7, "1_to_7" },
    { nit_plus_1_7, "plus_1_7" },
    { nit_attribute_required, "attribute_required" },
    { nit_frameset_body, "frameset_body" },
    { nit_unknown_xml, "unknown_xml" },
    { nit_xhtml_missing_slash, "xhtml_missing_slash" },
    { nit_xhtml_element_lc, "xhtml_element_lc" },
    { nit_xhtml_quote_values, "xhtml_quote_values" },
    { nit_xhtml_attribute_lc, "xhtml_attribute_lc" },
    { nit_xhtml_existential_makework, "xhtml_existential_makework" },
    { nit_existential_value, "existential_value" },
    { nit_attribute_repeated, "attribute_repeated" },
    { nit_eof_in_cdata, "eof_in_cdata" },
    { nit_xhtml_cdata, "xhtml_cdata" },
    { nit_negative_dosh, "negative_dosh" },
    { nit_mf_empty, "mf_empty" },
    { nit_bad_rating, "bad_rating" },
    { nit_no_tel, "no_tel" },
    { nit_xhtml_css, "xhtml_css" },
    { nit_naughty_lang, "naughty_lang" },
    { nit_nahtch, "nahtch" },
    { nit_charset_redefined, "charset_redefined" },
    { nit_not_utf_8, "not_utf_8" },
    { nit_no_content, "no_content" },
    { nit_default_role, "default_role" },
    { nit_bad_role, "bad_role" },
    { nit_use_datetime, "use_datetime" },
    { nit_alt_title, "alt_title" },
    { nit_naughty_alt, "naughty_alt" },
    { nit_data_type, "data_type" },
    { nit_typemustmatch, "typemustmatch" },
    { nit_missing_dynamic, "missing_dynamic" },
    { nit_bad_meta_place, "bad_meta_place" },
    { nit_bad_ancestor, "bad_ancestor" },
    { nit_value_ol, "value_ol" },
    { nit_too_many_figcaption, "too_many_figcaption" },
    { nit_figcaption_middle, "figcaption_middle" },
    { nit_missing_case, "missing_case" },
    { nit_requires_html, "requires_html" },
    { nit_overallowed, "overallowed" },
    { nit_saucy_source, "saucy_source" },
    { nit_area_map_template, "area_map_template" },
    { nit_requires_href, "requires_href" },
    { nit_bad_aspect_ratio, "bad_aspect_ratio" },
    { nit_bad_2pt, "bad_2pt" },
    { nit_table_manners, "table_manners" },
    { nit_unreal, "unreal" },
    { nit_no_namespaces_left, "no_namespaces_left" },
    { nit_xmlns_namespace, "xmlns_namespace" },
    { nit_table_children, "table_children" },
    { nit_colgroup_children, "colgroup_children" },
    { nit_input_bad_mix, "input_bad_mix" },
    { nit_option_child, "option_child" },
    { nit_fieldset_legend, "fieldset_legend" },
    { nit_bad_noscript, "bad_noscript" },
    { nit_src_required, "src_required" },
    { nit_element_unconstructed, "element_unconstructed" },
    { nit_requires_xhtml, "requires_xhtml" },
    { nit_text_content, "text_content" },
    { nit_daft_rel_attr, "daft_rel_attr" },
    { nit_link_rel_off, "link_rel_off" },
    { nit_key, "key" },
    { nit_autofocus, "autofocus" },
    { nit_virtual_exception, "virtual_exception" },
    { nit_bad_parameter, "bad_parameter" },
    { nit_bad_path, "bad_path" },
    { nit_scan_failed, "scan_failed" },
    { nit_examine_failed, "examine_failed" },
    { nit_stage, "stage" },
    { nit_id_hidden, "id_hidden" },
    { nit_empty_link, "empty_link" },
    { nit_requires_itemscope, "requires_itemscope" },
    { nit_requires_itemtype, "requires_itemtype" },
    { nit_bad_itemprop, "bad_itemprop" },
    { nit_double_gin_and_tonic, "double_gin_and_tonic" },
    { nit_lang_xmllang, "lang_xmllang" },
    { nit_no_xmllang, "no_xmllang" },
    { nit_avoid_manifest, "avoid_manifest" },
    { nit_base_b4_lynx, "base_b4_lynx" },
    { nit_as_not_image, "as_not_image" },
    { nit_bad_srcset, "bad_srcset" },
    { nit_mq_syntax, "mq_syntax" },
    { nit_attempted_escape, "attempted_escape" },
    { nit_no_such_folder, "no_such_folder" },
    { nit_dinosaur, "dinosaur" },
    { nit_no_main_kids, "no_main_kids" },
    { nit_bad_descendant, "bad_descendant" },
    { nit_dl_div, "dl_div" },
    { nit_no_dd, "no_dd" },
    { nit_dl_ancestor, "dl_ancestor" },
    { nit_figcaption_first_last, "figcaption_first_last" },
    { nit_dt_dd, "dt_dd" },
    { nit_rfc_1867, "rfc_1867" },
    { nit_rfc_1942, "rfc_1942" },
    { nit_rfc_1980, "rfc_1980" },
    { nit_rfc_2070, "rfc_2070" },
    { nit_no_exec, "no_exec" },
    { nit_unknown_ssi, "unknown_ssi" },
    { nit_attribute_assignment, "attribute_assignment" },
    { nit_invalid_config, "invalid_config" },
    { nit_invalid_set, "invalid_set" },
    { nit_invalid_echo, "invalid_echo" },
    { nit_unsupported_code, "unsupported_code" },
    { nit_ssi_include_error, "ssi_include_error" },
    { nit_invalid_fsize, "invalid_fsize" },
    { nit_ssi_if, "ssi_if" },
    { nit_linechange, "linechange" },
    { nit_no_if, "no_if" },
    { nit_invalid_flastmod, "invalid_flastmod" },
    { nit_ssi_syntax, "ssi_syntax" },
    { nit_cannot_access, "cannot_access" },
    { nit_xhtml_enum_lc, "xhtml_enum_lc" },
    { nit_xhtml_hex_lc, "xhtml_hex_lc" },
    { nit_schema_url, "schema_url" },
    { nit_unrecognised_schema, "unrecognised_schema" },
    { nit_schema_domain, "schema_domain" },
    { nit_interactive, "interactive" },
    { nit_tabindex, "tabindex" },
    { nit_mix_ruby_non, "mix_ruby_non" },
    { nit_too_many_ruby, "too_many_ruby" },
    { nit_no_rp, "no_rp" },
    { nit_too_many_rp, "too_many_rp" },
    { nit_not_img, "not_img" },
    { nit_bad_iframe, "bad_iframe" },
    { nit_bad_embed, "bad_embed" },
    { nit_wild_attribute, "wild_attribute" },
    { nit_attribute_barred, "attribute_barred" },
    { nit_bad_object, "bad_object" },
    { nit_disordered_param, "disordered_param" },
    { nit_source_track, "source_track" },
    { nit_src_source, "src_source" },
    { nit_media_descendants, "media_descendants" },
    { nit_autoplay, "autoplay" },
    { nit_out_of_order, "out_of_order" },
    { nit_kind_media_srclang, "kind_media_srclang" },
    { nit_track_default, "track_default" },
    { nit_name_id, "name_id" },
    { nit_need_coords, "need_coords" },
    { nit_bad_coords, "bad_coords" },
    { nit_1000, "1000" },
    { nit_bad_header_id, "bad_header_id" },
    { nit_form_charset, "form_charset" },
    { nit_deprecated_value, "deprecated_value" },
    { nit_bad_for, "bad_for" },
    { nit_label_parentage, "label_parentage" },
    { nit_input_bad_aria, "input_bad_aria" },
    { nit_illegal_value, "illegal_value" },
    { nit_bad_email, "bad_email" },
    { nit_bang_path, "bang_path" },
    { nit_unacceptable, "unacceptable" },
    { nit_lonely_radio, "lonely_radio" },
    { nit_minmax, "minmax" },
    { nit_pattern, "pattern" },
    { nit_bad_datalist_id, "bad_datalist_id" },
    { nit_placeholder, "placeholder" },
    { nit_bad_form, "bad_form" },
    { nit_bad_select, "bad_select" },
    { nit_bad_datalist, "bad_datalist" },
    { nit_bad_option, "bad_option" },
    { nit_bad_textarea, "bad_textarea" },
    { nit_no_progress, "no_progress" },
    { nit_bad_meter, "bad_meter" },
    { nit_not_form, "not_form" },
    { nit_special_name, "special_name" },
    { nit_solo, "solo" },
    { nit_bad_autocomplete, "bad_autocomplete" },
    { nit_snafu, "snafu" },
    { nit_details_summary, "details_summary" },
    { nit_summary_header, "summary_header" },
    { nit_bad_dialogue, "bad_dialogue" },
    { nit_bad_contextmenu, "bad_contextmenu" },
    { nit_bad_script, "bad_script" },
    { nit_bad_itemid, "bad_itemid" },
    { nit_untidy_string, "untidy_string" },
    { nit_no_itemscope, "no_itemscope" },
    { nit_new_itemprop, "new_itemprop" },
    { nit_type_error, "type_error" },
    { nit_schema_property, "schema_property" },
    { nit_forgotten_name, "forgotten_name" },
    { nit_incompatible_itemtype, "incompatible_itemtype" },
    { nit_inlist, "inlist" },
    { nit_schema_hierarchy, "schema_org_hierarchy" },
    { nit_angle, "angle" },
    { nit_html, "html" },
    { nit_svg_version, "svg_version" },
    { nit_bad_rgb, "bad_rgb" },
    { nit_bad_frequency, "bad_frequency" },
    { nit_icc_colour, "icc_colour" },
    { nit_svg_ancestor, "svg_ancestor" },
    { nit_rdf, "rdf" },
    { nit_bad_namespace, "bad_namespace" },
    { nit_svg_rdf, "svg_rdf" },
    { nit_clipped, "clipped" },
    { nit_mf_infer, "mf_infer" },
    { nit_path_spec, "path_spec" },
    { nit_lighting, "lighting" },
    { nit_animatemotion, "animatemotion" },
    { nit_fontface, "fontface" },
    { nit_switch, "switch" },
    { nit_transform, "transform" },
    { nit_attribute_name, "attribute_name" },
    { nit_repeated_attribute, "repeated_attribute" },
    { nit_svg_xy, "svg_xy" },
    { nit_fontstyle, "fontstyle" },
    { nit_svg_math, "svg_math" },
    { nit_fontstretch, "fontstretch" },
    { nit_fontvariant, "fontvariant" },
    { nit_fontweight, "fontweight" },
    { nit_panose_1, "panose_1" },
    { nit_icarus, "icarus" },
    { nit_vector_effect, "vector_effect" },
    { nit_paint, "paint" },
    { nit_0_1, "0_1" },
    { nit_1_more, "1_more" },
    { nit_dashed, "dashed" },
    { nit_marker, "marker" },
    { nit_background, "background" },
    { nit_bad_result, "bad_result" },
    { nit_not_schema_property, "not_schema_property" },
    { nit_curses, "curses" },
    { nit_xlinktype, "xlinktype" },
    { nit_xlinkactuate, "xlinkactuate" },
    { nit_dur, "dur" },
    { nit_svg_values, "svg_values" },
    { nit_rotate, "rotate" },
    { nit_origin, "origin" },
    { nit_colour_matrix, "colour_matrix" },
    { nit_math_kids, "math_kids" },
    { nit_bad_hunit, "bad_hunit" },
    { nit_bad_vunit, "bad_vunit" },
    { nit_too_many, "too_many" },
    { nit_use_apply, "use_apply" },
    { nit_base, "base" },
    { nit_declare_first, "declare_first" },
    { nit_arg_count, "arg_count" },
    { nit_operator_required, "operator_required" },
    { nit_bad_bvar, "bad_bvar" },
    { nit_bad_doa, "bad_doa" },
    { nit_bad_piece, "bad_piece" },
    { nit_annotation, "annotation" },
    { nit_eof_in_annotation, "eof_in_annotation" },
    { nit_prefix_odd, "prefix_odd" },
    { nit_prefix_format, "prefix_format" },
    { nit_rdfa_redefine, "rdfa_redefine" },
    { nit_rdfa_confusion, "rdfa_confusion" },
    { nit_rdf_protocol, "rdf_protocol" },
    { nit_math_href, "math_href" },
    { nit_math_empty, "math_empty" },
    { nit_mglyph_alt_src, "mglyph_alt_src" },
    { nit_dir_rtl_ltr, "dir_rtl_ltr" },
    { nit_bad_linebreak, "bad_linebreak" },
    { nit_non_standard_value, "non_standard_value" },
    { nit_mscarries_last, "mscarries_last" },
    { nit_bad_bind, "bad_bind" },
    { nit_bad_share, "bad_share" },
    { nit_shadow, "shadow" },
    { nit_out_of_memory, "out_of_memory" },
    { nit_duplicate, "duplicate" },
    { nit_shadow_failed, "shadow_failed" },
    { nit_create_folder, "create_folder" },
    { nit_internal_file_error, "internal_file_error" },
    { nit_shadow_ignore, "shadow_ignore" },
    { nit_shadow_link, "shadow_link" },
    { nit_shadow_copy, "shadow_copy" },
    { nit_too_big, "too_big" },
    { nit_icu, "icu" },
    { nit_lang_redefined, "lang_redefined" },
    { nit_page_charset, "page_charset" },
    { nit_charset_mismatch, "charset_mismatch" },
    { nit_charset_used, "charset_used" },
    { nit_charset_invalid, "charset_invalid" },
    { nit_no_converters, "no_converters" },
    { nit_xhtml_superseded, "xhtml_superseded" },
    { nit_not_iso_8859_1, "not_iso_8859_1" },
    { nit_draft_html_5, "draft_html_5" },
    { nit_overriding_html, "overriding_html" },
    { nit_whatwg_class, "whatwg_class" },
    { nit_opening_file, "opening_file" },
    { nit_target, "target" },
    { nit_bad_mummy, "bad_mummy" },
    { nit_no_serviceworker, "no_serviceworker" },
    { nit_rel_head, "rel_head" },
    { nit_theme_colour, "theme_colour" },
    { nit_refresh_zero, "refresh_zero" },
    { nit_bad_csp_directive, "bad_csp_directive" },
    { nit_bad_number_once, "bad_number_once" },
    { nit_bad_csp_source, "bad_csp_source" },
    { nit_invalid_algorithm, "invalid_algorithm" },
    { nit_insufficient_content, "insufficient_content" },
    { nit_bad_q, "bad_q" },
    { nit_bad_cookie, "bad_cookie" },
    { nit_bad_cache, "bad_cache" },
    { nit_bad_link_pragma, "bad_link_pragma" },
    { nit_nocando, "nocando" },
    { nit_bad_root, "bad_root" },
    { nit_isnt, "isnt" },
    { nit_menu_type, "menu_type" },
    { nit_menu_child, "menu_child" },
    { nit_bad_dl, "bad_dl" },
    { nit_repeated_definition, "repeated_definition" },
    { nit_contradictory_expansion, "contradictory_expansion" },
    { nit_naughty_grave, "naughty_grave" },
    { nit_encode, "encode" },
    { nit_svg_data, "svg_data" },
    { nit_data, "data" },
    { nit_bad_wild, "bad_wild" },
    { nit_risky_filetype, "risky_filetype" },
    { nit_reputation, "reputation" },
    { nit_incompatible_mime, "incompatible_mime" },
    { nit_os_dependent, "os_dependent" },
    { nit_bad_usemap, "bad_usemap" },
    { nit_bad_type_attribute, "bad_type_attribute" },
    { nit_bad_pattern, "bad_pattern" },
    { nit_bad_command, "bad_command" },
    { nit_bad_datagrid, "bad_datagrid" },
    { nit_script, "script" },
    { nit_menubar, "menubar" },
    { nit_bad_card, "bad_card" },
    { nit_nest, "nest" },
    { nit_registration_mark, "registration_mark" },
    { nit_bad_ref, "bad_ref" },
    { nit_font, "font" },
    { nit_dashdash, "dashdash" },
    { nit_naked_grave, "naked_grave" },
    { nit_prototype, "prototype" },
    { nit_bad_property, "bad_property" },
    { nit_hour, "hour" },
    { nit_minute, "minute" },
    { nit_second, "second" },
    { nit_deprecated_schema, "deprecated_schema" },
    { nit_character_code, "character_code" },
    { nit_note, "note" },
    { nit_aria_position, "aria_position" },
    { nit_impure_mn, "impure_mn" },
    { nit_program_error, "program_error" },
    { nit_xhtml_5_0, "xhtml_5_0" },
    { nit_html_superseded, "html_superseded" },
    { nit_function, "function" },
    { nit_zero_to_one, "zero_to_one" },
    { nit_percent, "percent" },
    { nit_fontname, "fontname" },
    { nit_glyphname, "glyphname" },
    { nit_keytimes, "keytimes" },
    { nit_keysplines, "keysplines" },
    { nit_not_n, "not_n" },
    { nit_syntax, "syntax" },
    { nit_viewbox, "viewbox" },
    { nit_custom, "custom" },
    { nit_duplicate_namespace, "duplicate_namespace" },
    { nit_contradictory_namespace, "contradictory_namespace" },
    { nit_unrecognised_namespace, "unrecognised_namespace" },
    { nit_out_of_range, "out_of_range" },
    { nit_math_or_svg, "math_or_svg" },
    { nit_many_maybe, "many_maybe" },
    { nit_not_combine, "not_combine" },
    { nit_font_enum, "font_enum" },
    { nit_altglyphdef, "altglyphdef" },
    { nit_line_increment, "line_increment" },
    { nit_is_property, "is_property" },
    { nit_better_as_property, "better_as_property" },
    { nit_colour_profile, "colour_profile" },
    { nit_feconvolvematrix, "feconvolvematrix" },
    { nit_not_0, "not_0" },
    { nit_fecomponenttransfer, "fecomponenttransfer" },
    { nit_fecomposite, "fecomposite" },
    { nit_style_fixed, "style_fixed" },
    { nit_anim_simple_id, "anim_simple_id" },
    { nit_id_category, "id_category" },
    { nit_not_animatable, "not_animatable" },
    { nit_shadow_delete, "shadow_delete" },
    { nit_root_change, "root_change" },
    { nit_virtual_change, "virtual_change" },
    { nit_shadow_unnecessary, "shadow_unnecessary" },
    { nit_deleted_bad_file, "deleted_bad_file" },
    { nit_abandon, "abandon" },
    { nit_prefix_again, "prefix_again" },
    { nit_prefix_unknown, "prefix_unknown" },
    { nit_missing_id, "missing_id" },
    { nit_namespace_confusion, "namespace_confusion" },
    { nit_namespace_redefine, "namespace_redefine" },
    { nit_no_lang, "no_lang" },
    { nit_null_datatype, "null_datatype" },
    { nit_unknown_datatype, "unknown_datatype" },
    { nit_rdfa_version, "rdfa_version" },
    { nit_bad_sha, "bad_sha" },
    { nit_new_property, "new_property" },
    { nit_wwww, "wwww" },
    { nit_bad_vocab, "bad_vocab" },
    { nit_vocab_defined, "vocab_defined" },
    { nit_sarcasm, "sarcasm" },
    { nit_fe, "fe" },
    { nit_missing_double_quote, "missing_double_quote" },
    { nit_bad_media, "bad_media" },
    { nit_mb, "mb" },
    { nit_byte, "byte" },
    { nit_b64, "b64" },
    { nit_help, "help" },
    { nit_configuration, "configuration" },
    { nit_version, "version" },
    { nit_title, "title" },
    { nit_webaddr, "webaddr" },
    { nit_copyright, "copyright" },
    { nit_info, "info" },
    { nit_build, "build" },
    { nit_config_version, "config_version" },
    { nit_config_date, "config_date" },
    { nit_config_nit, "config_nit" },
    { nit_config_shadow, "config_shadow" },
    { nit_template_file, "template_file" },
    { nit_code_dtd, "code_dtd" },
    { nit_data_vocabulary, "data_vocabulary" },
    { nit_json_error, "json_error" },
    { nit_json_internal_error, "json_internal_error" },
    { nit_json_id, "json_id" },
    { nit_vocab, "vocab" },
    { nit_jsonld_context, "jsonld_context" },
    { nit_json_name, "json_name" },
    { nit_json_invalid_node, "json_invalid_node" },
    { nit_json_value_object, "json_value_object" },
    { nit_json_out_of_place, "json_out_of_place" },
    { nit_json_bad_term, "json_bad_term" },
    { nit_jsonld_type, "jsonld_type" },
    { nit_missing_schema, "missing_schema" },
    { nit_jsonld_format, "jsonld_format" },
    { nit_jsonld_mistype, "jsonld_mistype" },
    { nit_jsonld_encoding, "jsonld_encoding" },
    { nit_jsonld_map, "jsonld_map" },
    { nit_crap_spec, "crap_spec" },
    { nit_bad_uid, "bad_uid" },
    { nit_missing_property, "missing_property" },
    { nit_no_spell, "no_spell" },
    { nit_misspelt, "misspelt" },
    { nit_bad_list, "bad_list" },
    { nit_spell_lang, "spell_lang" },
    { nit_spell_perhaps, "spell_perhaps" },
    { nit_launch, "launch" },
    { nit_sent, "sent" },
    { nit_got, "got" },
    { nit_bad_dict, "bad_dict" },
    { nit_deprecated, "deprecated" },
    { nit_case, "case" },
    { nit_icu_barf, "icu_barf" },
    { nit_convert, "convert" },
    { nit_locale, "locale" },
    { nit_wtf, "wtf" },
    { nit_normalise, "normalise" },
    { nit_dictionary, "dictionary" },
    { nit_example, "example" },
    { nit_local, "local" },
    { nit_report, "report" },
    { nit_unknown_option, "unknown_option" },
    { nit_yea_nay, "yea_nay" },
    { nit_mf_version, "mf_version" },
    { nit_not_directory, "not_directory" },
    { nit_dubious_mention, "dubious_mention" },
    { nit_endpoint, "endpoint" },
    { nit_webmention_css, "webmention_css" },
    { nit_webmention_external, "webmention_external" },
    { nit_header_empty, "header_empty" },
    { nit_header_malformed, "header_malformed" },
    { nit_http_error, "http_error" },
    { nit_header_no_data, "header_no_data" },
    { nit_invalid_mention, "invalid_mention" },
    { nit_json_version, "json_version" },
    { nit_json_corrupt, "json_corrupt" },
    { nit_json_domain, "json_domain" },
    { nit_dialect, "dialect" },
    { nit_country, "country" },
    { nit_languages, "languages" },
    { nit_hidden, "hidden" },
    { nit_blocking, "blocking" },

    { nit_off, "" } };

typedef ::std::map < ::std::string, e_nit > nitmap;
typedef ::std::map < e_nit, ::std::string > timmap;

nitmap quick_nit;
timmap quick_tim;

void nits_init ()
{   if (! quick_nit.empty ()) return;
    ::std::size_t i;
    ::std::vector < bool > bitten;
    bitten.resize (nit_off);
    for (i = 0; gsl::at (nitnames, i).nit_ != nit_off; ++i)
    {   quick_nit.insert (::nitmap::value_type (gsl::at (nitnames, i).sz_, gsl::at (nitnames, i).nit_));
        quick_tim.insert (::timmap::value_type (gsl::at (nitnames, i).nit_, gsl::at (nitnames, i).sz_));
        bitten.at (gsl::at (nitnames, i).nit_) = true; }
    if (i < static_cast <::std::size_t> (nit_off))
    {   ::std::cerr << "WARNING: Only " << i << " of " << static_cast < ::std::size_t > (nit_off) << " feedback identifiers defined\nUndefined:";
        for (int x = 0; x < nit_off; ++x)
            if (! bitten.at (x))
                ::std::cerr << " " << x;
        ::std::cerr << "\n"; } }


e_nit lookup_code (const ::std::string& name)
{   nitmap::const_iterator i = quick_nit.find (name);
    if (i == quick_nit.cend ()) return nit_off;
    return i -> second; }

::std::string lookup_name (const e_nit en)
{   timmap::const_iterator i = quick_tim.find (en);
    if (i != quick_tim.end ()) return i -> second;
    return ::std::string (); }
