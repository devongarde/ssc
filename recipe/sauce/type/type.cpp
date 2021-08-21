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
#include "type/type.h"

void types_init (nitpick& nits)
{   void charset_init (nitpick& nits);
    void class_init (nitpick& nits);
    void currency_init (nitpick& nits);
    void fixedcolour_init (nitpick& nits);
    void httpequiv_init (nitpick& nits);
    void lang_init (nitpick& nits);
    void metaname_init (nitpick& nits);
    void mime_init (nitpick& nits);
    void rel_init (nitpick& nits);
    void role_init (nitpick& nits);
    void sgml_init (nitpick& nits);
    void enum_init (nitpick& nits);

    charset_init (nits);
    class_init (nits);
    currency_init (nits);
    fixedcolour_init (nits);
    httpequiv_init (nits);
    lang_init (nits);
    metaname_init (nits);
    mime_init (nits);
    rel_init (nits);
    role_init (nits);
    sgml_init (nits);

    enum_init (nits); }

bool test_value (nitpick& nits, const html_version& v, const e_type t, const ::std::string& s)
{   // template recursion causes stack overflow on some systems :-(
#define TEST_VALUE(ENUM) case ENUM : return test_value < ENUM > (nits, v, s)
    switch (t)
    {   TEST_VALUE (t_unknown);
        TEST_VALUE (t_0_more);
        TEST_VALUE (t_1);
        TEST_VALUE (t_10);
        TEST_VALUE (t_1_to_7);
        TEST_VALUE (t_1_more);
        TEST_VALUE (t_1_more_i);
        TEST_VALUE (t_2pt);
        TEST_VALUE (t_abbreviated);
        TEST_VALUE (t_about);
        TEST_VALUE (t_absolute_url);
        TEST_VALUE (t_accept);
        TEST_VALUE (t_accesskey);
        TEST_VALUE (t_accrual_method);
        TEST_VALUE (t_accrual_periodicity);
        TEST_VALUE (t_accrual_policy);
        TEST_VALUE (t_accumulate);
        TEST_VALUE (t_accumulate0);
        TEST_VALUE (t_accumulate1);
        TEST_VALUE (t_accumulate2);
        TEST_VALUE (t_action);
        TEST_VALUE (t_actiontype);
        TEST_VALUE (t_actiontype2);
        TEST_VALUE (t_additive);
        TEST_VALUE (t_align);
        TEST_VALUE (t_align2070);
        TEST_VALUE (t_align3);
        TEST_VALUE (t_aligndec);
        TEST_VALUE (t_alignfig);
        TEST_VALUE (t_alignment_baseline);
        TEST_VALUE (t_alignplus);
        TEST_VALUE (t_angle);
        TEST_VALUE (t_angle_a);
        TEST_VALUE (t_angle_ai);
        TEST_VALUE (t_angle_i);
        TEST_VALUE (t_animate);
        TEST_VALUE (t_arabicenum);
        TEST_VALUE (t_arabic_form);
        TEST_VALUE (t_aria_autocomplete);
        TEST_VALUE (t_aria_invalidity);
        TEST_VALUE (t_aria_live);
        TEST_VALUE (t_aria_pressed);
        TEST_VALUE (t_aria_sort);
        TEST_VALUE (t_as);
        TEST_VALUE (t_attributename);
        TEST_VALUE (t_attributetype);
        TEST_VALUE (t_audio_level);
        TEST_VALUE (t_autocapitalise);
        TEST_VALUE (t_autocomplete);
        TEST_VALUE (t_autocompletes);
        TEST_VALUE (t_autocompletevaried);
        TEST_VALUE (t_b64);
        TEST_VALUE (t_background);
        TEST_VALUE (t_bandwidth);
        TEST_VALUE (t_base);
        TEST_VALUE (t_baselineshift);
        TEST_VALUE (t_bb);
        TEST_VALUE (t_beginarg);
        TEST_VALUE (t_beginfn);
        TEST_VALUE (t_beginvalue);
        TEST_VALUE (t_beginvalues);
        TEST_VALUE (t_beginvaluelist);
        TEST_VALUE (t_behaviour);
        TEST_VALUE (t_border);
        TEST_VALUE (t_bool);
        TEST_VALUE (t_bools);
        TEST_VALUE (t_buffered_rendering);
        TEST_VALUE (t_button);
        TEST_VALUE (t_byte);
        TEST_VALUE (t_cache);
        TEST_VALUE (t_cachekey);
        TEST_VALUE (t_caches);
        TEST_VALUE (t_calcmode);
        TEST_VALUE (t_captionalign);
        TEST_VALUE (t_capture);
        TEST_VALUE (t_cc_permits);
        TEST_VALUE (t_cc_prohibits);
        TEST_VALUE (t_cc_requires);
        TEST_VALUE (t_channelselector);
        TEST_VALUE (t_char);
        TEST_VALUE (t_charset);
        TEST_VALUE (t_charsets);
        TEST_VALUE (t_charspacing);
        TEST_VALUE (t_citype);
        TEST_VALUE (t_class);
        TEST_VALUE (t_clear);
        TEST_VALUE (t_clear30);
        TEST_VALUE (t_clip);
        TEST_VALUE (t_clip_path_rule);
        TEST_VALUE (t_closure);
        TEST_VALUE (t_colour);
        TEST_VALUE (t_colour_ci);
        TEST_VALUE (t_colour_cii);
        TEST_VALUE (t_colour_i);
        TEST_VALUE (t_colour_interpolation);
        TEST_VALUE (t_colour_ni);
        TEST_VALUE (t_colour_profile);
        TEST_VALUE (t_colour_profile_name);
        TEST_VALUE (t_colour_profile_name_or_uri);
        TEST_VALUE (t_colour_rendering);
        TEST_VALUE (t_colour_v);
        TEST_VALUE (t_command);
        TEST_VALUE (t_compact);
        TEST_VALUE (t_comp_op);
        TEST_VALUE (t_composite_operator);
        TEST_VALUE (t_compositing);
        TEST_VALUE (t_conditional);
        TEST_VALUE (t_connect);
        TEST_VALUE (t_content_encoding);
        TEST_VALUE (t_content_encodings);
        TEST_VALUE (t_content_type);
        TEST_VALUE (t_context_menu);
        TEST_VALUE (t_controlslist);
        TEST_VALUE (t_cookie);
        TEST_VALUE (t_cookieid);
        TEST_VALUE (t_cookies);
        TEST_VALUE (t_coordinatesystem);
        TEST_VALUE (t_coords);
        TEST_VALUE (t_corp);
        TEST_VALUE (t_cors);
        TEST_VALUE (t_cntype);
        TEST_VALUE (t_crossout);
        TEST_VALUE (t_css);
        TEST_VALUE (t_csp);
        TEST_VALUE (t_csp_ancestor);
        TEST_VALUE (t_csp_directive);
        TEST_VALUE (t_csp_keyword);
        TEST_VALUE (t_csp_sauce);
        TEST_VALUE (t_csp_source);
        TEST_VALUE (t_curie);
        TEST_VALUE (t_curie_safe);
        TEST_VALUE (t_curies);
        TEST_VALUE (t_currency);
        TEST_VALUE (t_cursor);
        TEST_VALUE (t_cursor_f);
        TEST_VALUE (t_cursor_i);
        TEST_VALUE (t_d);
        TEST_VALUE (t_dashes);
        TEST_VALUE (t_data);
        TEST_VALUE (t_dataformatas);
        TEST_VALUE (t_datetime);
        TEST_VALUE (t_datetime_absolute);
        TEST_VALUE (t_datetime_local);
        TEST_VALUE (t_datetime_4);
        TEST_VALUE (t_datetime_5);
        TEST_VALUE (t_day);
        TEST_VALUE (t_dcmitype);
        TEST_VALUE (t_decalign);
        TEST_VALUE (t_decoding);
        TEST_VALUE (t_defaultaction);
        TEST_VALUE (t_depth);
        TEST_VALUE (t_device);
        TEST_VALUE (t_dingbat);
        TEST_VALUE (t_dir);
        TEST_VALUE (t_direction);
        TEST_VALUE (t_display);
        TEST_VALUE (t_display_align);
        TEST_VALUE (t_dominantbaseline);
        TEST_VALUE (t_dosh);
        TEST_VALUE (t_dsc);
        TEST_VALUE (t_dsctv);
        TEST_VALUE (t_dur);
        TEST_VALUE (t_dur_repeat);
        TEST_VALUE (t_duration);
        TEST_VALUE (t_duration_media);
        TEST_VALUE (t_edgemode);
        TEST_VALUE (t_edi);
        TEST_VALUE (t_edit);
        TEST_VALUE (t_editable);
        TEST_VALUE (t_effect);
        TEST_VALUE (t_email);
        TEST_VALUE (t_emails);
        TEST_VALUE (t_enable_background);
        TEST_VALUE (t_enctype);
        TEST_VALUE (t_end);
        TEST_VALUE (t_endvaluelist);
        TEST_VALUE (t_enterkeyhint);
        TEST_VALUE (t_existential);
        TEST_VALUE (t_expected);
        TEST_VALUE (t_featurepolicy);
        TEST_VALUE (t_figalign);
        TEST_VALUE (t_filename);
        TEST_VALUE (t_filesize);
        TEST_VALUE (t_fill);
        TEST_VALUE (t_fillanim);
        TEST_VALUE (t_fill_opacity);
        TEST_VALUE (t_fill_rule);
        TEST_VALUE (t_fill_ve);
        TEST_VALUE (t_filter_in);
        TEST_VALUE (t_filterres);
        TEST_VALUE (t_fixedcolour);
        TEST_VALUE (t_fixedpoint);
        TEST_VALUE (t_focushighlight);
        TEST_VALUE (t_font);
        TEST_VALUE (t_font_enum);
        TEST_VALUE (t_font_family);
        TEST_VALUE (t_font_families);
        TEST_VALUE (t_fontname);
        TEST_VALUE (t_fontnia);
        TEST_VALUE (t_fontsize);
        TEST_VALUE (t_fontsizeadjust);
        TEST_VALUE (t_fontstretch);
        TEST_VALUE (t_fontstretches);
        TEST_VALUE (t_fontstyle);
        TEST_VALUE (t_fontweight);
        TEST_VALUE (t_fontvariant);
        TEST_VALUE (t_fontvariants);
        TEST_VALUE (t_font_variant);
        TEST_VALUE (t_font_variant_2);
        TEST_VALUE (t_font_variant_2s);
        TEST_VALUE (t_font_variant_caps);
        TEST_VALUE (t_font_variant_east_asians);
        TEST_VALUE (t_font_variant_east_asian);
        TEST_VALUE (t_font_variant_ligature);
        TEST_VALUE (t_font_variant_ligatures);
        TEST_VALUE (t_font_variant_numeric);
        TEST_VALUE (t_font_variant_numerics);
        TEST_VALUE (t_font_variant_position);
        TEST_VALUE (t_form);
        TEST_VALUE (t_format);
        TEST_VALUE (t_frame);
        TEST_VALUE (t_frame4);
        TEST_VALUE (t_framespacing);
        TEST_VALUE (t_frequency);
        TEST_VALUE (t_gender);
        TEST_VALUE (t_generic);
        TEST_VALUE (t_glyphname);
        TEST_VALUE (t_glyphnames);
        TEST_VALUE (t_groupalign);
        TEST_VALUE (t_halign);
        TEST_VALUE (t_hash_ref);
        TEST_VALUE (t_hash_fn);
        TEST_VALUE (t_height);
        TEST_VALUE (t_hex);
        TEST_VALUE (t_hour);
        TEST_VALUE (t_html);
        TEST_VALUE (t_html_boolean);
        TEST_VALUE (t_httpequiv);
        TEST_VALUE (t_hv);
        TEST_VALUE (t_hunit);
        TEST_VALUE (t_icc);
        TEST_VALUE (t_icccolour);
        TEST_VALUE (t_id);
        TEST_VALUE (t_identifier_url);
        TEST_VALUE (t_idref);
        TEST_VALUE (t_idrefs);
        TEST_VALUE (t_illegal);
        TEST_VALUE (t_image_rendering);
        TEST_VALUE (t_imcastr);
        TEST_VALUE (t_imgsizes);
        TEST_VALUE (t_importance);
        TEST_VALUE (t_in);
        TEST_VALUE (t_index);
        TEST_VALUE (t_indentalign);
        TEST_VALUE (t_indentalign2);
        TEST_VALUE (t_indentshift2);
        TEST_VALUE (t_infixlinebreakstyle);
        TEST_VALUE (t_initialvisibility);
        TEST_VALUE (t_inky);
        TEST_VALUE (t_inlist);
        TEST_VALUE (t_inputaccept);
        TEST_VALUE (t_inputmode);
        TEST_VALUE (t_inputplus);
        TEST_VALUE (t_inputtype);
        TEST_VALUE (t_inputtype3);
        TEST_VALUE (t_inputtype32);
        TEST_VALUE (t_inputtype4);
        TEST_VALUE (t_inputtype5);
        TEST_VALUE (t_integer);
        TEST_VALUE (t_is);
        TEST_VALUE (t_isbn);
        TEST_VALUE (t_issn);
        TEST_VALUE (t_itemid);
        TEST_VALUE (t_itemprop);
        TEST_VALUE (t_itemtype);
        TEST_VALUE (t_itemref);
        TEST_VALUE (t_just_date);
        TEST_VALUE (t_just_time);
        TEST_VALUE (t_key);
        TEST_VALUE (t_keygentype);
        TEST_VALUE (t_keyspline);
        TEST_VALUE (t_keysplines);
        TEST_VALUE (t_keytimes);
        TEST_VALUE (t_keytype);
        TEST_VALUE (t_kind);
        TEST_VALUE (t_lang);
        TEST_VALUE (t_langq);
        TEST_VALUE (t_langs);
        TEST_VALUE (t_langqs);
        TEST_VALUE (t_larnalign);
        TEST_VALUE (t_layout);
        TEST_VALUE (t_lcralign);
        TEST_VALUE (t_lcraligns);
        TEST_VALUE (t_lcrnalign);
        TEST_VALUE (t_lcrd);
        TEST_VALUE (t_lcrds);
        TEST_VALUE (t_lcrdss);
        TEST_VALUE (t_length);
        TEST_VALUE (t_length_absolute);
        TEST_VALUE (t_length_relative);
        TEST_VALUE (t_lengthadjust);
        TEST_VALUE (t_linebreak);
        TEST_VALUE (t_linebreakstyle);
        TEST_VALUE (t_linecap);
        TEST_VALUE (t_line_height);
        TEST_VALUE (t_linejoin);
        TEST_VALUE (t_linethickness);
        TEST_VALUE (t_link);
        TEST_VALUE (t_linkarg);
        TEST_VALUE (t_linkargs);
        TEST_VALUE (t_linkitself);
        TEST_VALUE (t_linkparam);
        TEST_VALUE (t_links);
        TEST_VALUE (t_listtype);
        TEST_VALUE (t_literal);
        TEST_VALUE (t_loading);
        TEST_VALUE (t_local_url);
        TEST_VALUE (t_location);
        TEST_VALUE (t_longdivstyle);
        TEST_VALUE (t_loop);
        TEST_VALUE (t_loopie);
        TEST_VALUE (t_lraalign);
        TEST_VALUE (t_lralign);
        TEST_VALUE (t_lspace);
        TEST_VALUE (t_mah);
        TEST_VALUE (t_marked_up);
        TEST_VALUE (t_marker);
        TEST_VALUE (t_markerunits);
        TEST_VALUE (t_mathalign);
        TEST_VALUE (t_mathalign_n);
        TEST_VALUE (t_mathaligns);
        TEST_VALUE (t_mathclosure);
        TEST_VALUE (t_mathdisplay);
        TEST_VALUE (t_mathfontstyle);
        TEST_VALUE (t_mathfontweight);
        TEST_VALUE (t_mathform);
        TEST_VALUE (t_mathframe);
        TEST_VALUE (t_mathlocation);
        TEST_VALUE (t_mathmode);
        TEST_VALUE (t_mathnotation);
        TEST_VALUE (t_mathnotations);
        TEST_VALUE (t_mathoccurence);
        TEST_VALUE (t_mathorder);
        TEST_VALUE (t_mathoverflow);
        TEST_VALUE (t_mathscope);
        TEST_VALUE (t_mathside);
        TEST_VALUE (t_mathsize);
        TEST_VALUE (t_mathspace);
        TEST_VALUE (t_mathspaceauto);
        TEST_VALUE (t_mathspacefit);
        TEST_VALUE (t_mathspaceinfinity);
        TEST_VALUE (t_mathvariant);
        TEST_VALUE (t_mathvertauto);
        TEST_VALUE (t_matrixtype);
        TEST_VALUE (t_matrix_values);
        TEST_VALUE (t_mb);
        TEST_VALUE (t_measure);
        TEST_VALUE (t_measure_a);
        TEST_VALUE (t_measure_ai);
        TEST_VALUE (t_measure_i);
        TEST_VALUE (t_measure_ni);
        TEST_VALUE (t_measure_or_more);
        TEST_VALUE (t_measures);
        TEST_VALUE (t_media);
        TEST_VALUE (t_mediafeature);
        TEST_VALUE (t_mediakeyword);
        TEST_VALUE (t_meetslice);
        TEST_VALUE (t_menuitem);
        TEST_VALUE (t_menutype);
        TEST_VALUE (t_metaname);
        TEST_VALUE (t_method);
        TEST_VALUE (t_methodological);
        TEST_VALUE (t_mf_availability);
        TEST_VALUE (t_mf_category);
        TEST_VALUE (t_mf_class);
        TEST_VALUE (t_mf_identifier);
        TEST_VALUE (t_mf_itemtype);
        TEST_VALUE (t_mf_listing_action);
        TEST_VALUE (t_mf_listing_actions);
        TEST_VALUE (t_mf_method);
        TEST_VALUE (t_mf_reviewtype);
        TEST_VALUE (t_mf_status);
        TEST_VALUE (t_mime);
        TEST_VALUE (t_mimelist);
        TEST_VALUE (t_mimemodule);
        TEST_VALUE (t_mimeq);
        TEST_VALUE (t_mimeqs);
        TEST_VALUE (t_mimestar);
        TEST_VALUE (t_minute);
        TEST_VALUE (t_mode);
        TEST_VALUE (t_month);
        TEST_VALUE (t_monthday);
        TEST_VALUE (t_morphology_operator);
        TEST_VALUE (t_mql);
        TEST_VALUE (t_mqls);
        TEST_VALUE (t_myersbriggs);
        TEST_VALUE (t_name);
        TEST_VALUE (t_nameref);
        TEST_VALUE (t_namespace);
        TEST_VALUE (t_namedspace);
        TEST_VALUE (t_navigation);
        TEST_VALUE (t_negative);
        TEST_VALUE (t_not_0);
        TEST_VALUE (t_not_empty);
        TEST_VALUE (t_not_neg);
        TEST_VALUE (t_not_pos);
        TEST_VALUE (t_notation);
        TEST_VALUE (t_notations);
        TEST_VALUE (t_nsd);
        TEST_VALUE (t_nsds);
        TEST_VALUE (t_num);
        TEST_VALUE (t_occurence);
        TEST_VALUE (t_ogtype);
        TEST_VALUE (t_onoff);
        TEST_VALUE (t_opacity);
        TEST_VALUE (t_open);
        TEST_VALUE (t_operator);
        TEST_VALUE (t_order);
        TEST_VALUE (t_orientation);
        TEST_VALUE (t_origin);
        TEST_VALUE (t_overflow);
        TEST_VALUE (t_overlay);
        TEST_VALUE (t_page_orientation);
        TEST_VALUE (t_paint);
        TEST_VALUE (t_paintkeyword);
        TEST_VALUE (t_paint_order);
        TEST_VALUE (t_panose1);
        TEST_VALUE (t_percent);
        TEST_VALUE (t_phase);
        TEST_VALUE (t_phase_x);
        TEST_VALUE (t_pics);
        TEST_VALUE (t_plus_1_7);
        TEST_VALUE (t_plusstyle);
        TEST_VALUE (t_pointer_events);
        TEST_VALUE (t_points);
        TEST_VALUE (t_positive);
        TEST_VALUE (t_positive_1_2);
        TEST_VALUE (t_pragma);
        TEST_VALUE (t_prefix);
        TEST_VALUE (t_preload);
        TEST_VALUE (t_preload5);
        TEST_VALUE (t_preserveaspectratio);
        TEST_VALUE (t_preserveaspectratio10);
        TEST_VALUE (t_preserveaspectratio12);
        TEST_VALUE (t_print);
        TEST_VALUE (t_propagate);
        TEST_VALUE (t_pseudo);
        TEST_VALUE (t_pseudonamedspace);
        TEST_VALUE (t_pt);
        TEST_VALUE (t_q);
        TEST_VALUE (t_rap);
        TEST_VALUE (t_rating);
        TEST_VALUE (t_rdf_parsetype);
        TEST_VALUE (t_rdfa_typeof);
        TEST_VALUE (t_real);
        TEST_VALUE (t_real_1_2);
        TEST_VALUE (t_real_ai);
        TEST_VALUE (t_real_i);
        TEST_VALUE (t_reals);
        TEST_VALUE (t_referrer);
        TEST_VALUE (t_refresh);
        TEST_VALUE (t_refx);
        TEST_VALUE (t_refy);
        TEST_VALUE (t_regex);
        TEST_VALUE (t_rel);
        TEST_VALUE (t_rel_a);
        TEST_VALUE (t_rel_avoid);
        TEST_VALUE (t_rel_css);
        TEST_VALUE (t_rel_illegal);
        TEST_VALUE (t_rel_link);
        TEST_VALUE (t_rel_obsolete);
        TEST_VALUE (t_rendering_colour_space);
        TEST_VALUE (t_rendering_in_tents);
        TEST_VALUE (t_repeatcount);
        TEST_VALUE (t_restart);
        TEST_VALUE (t_result);
        TEST_VALUE (t_reveal_trans);
        TEST_VALUE (t_role);
        TEST_VALUE (t_roles);
        TEST_VALUE (t_roman_dsc);
        TEST_VALUE (t_root_url);
        TEST_VALUE (t_rotate);
        TEST_VALUE (t_rotate_anim);
        TEST_VALUE (t_rowscols);
        TEST_VALUE (t_rsvp);
        TEST_VALUE (t_rules);
        TEST_VALUE (t_sandbox);
        TEST_VALUE (t_sandboxen);
        TEST_VALUE (t_scei);
        TEST_VALUE (t_schema);
        TEST_VALUE (t_schema_type);
        TEST_VALUE (t_scope);
        TEST_VALUE (t_script);
        TEST_VALUE (t_scrolling);
        TEST_VALUE (t_second);
        TEST_VALUE (t_setback_offset);
        TEST_VALUE (t_settype);
        TEST_VALUE (t_severity);
        TEST_VALUE (t_sex);
        TEST_VALUE (t_sgml);
        TEST_VALUE (t_sha256);
        TEST_VALUE (t_shadow);
        TEST_VALUE (t_shape);
        TEST_VALUE (t_shape3);
        TEST_VALUE (t_shape4);
        TEST_VALUE (t_shape7);
        TEST_VALUE (t_shape_none_uri);
        TEST_VALUE (t_shape_fn);
        TEST_VALUE (t_shape_fn_circle);
        TEST_VALUE (t_shape_fn_ellipse);
        TEST_VALUE (t_shape_fn_polygon);
        TEST_VALUE (t_shape_fn_circlesz);
        TEST_VALUE (t_shape_fn_ellipsesz);
        TEST_VALUE (t_shape_fn_polygonsz);
        TEST_VALUE (t_shape_uri);
        TEST_VALUE (t_shape_rendering);
        TEST_VALUE (t_shape_rcp);
        TEST_VALUE (t_shadowinherit);
        TEST_VALUE (t_short);
        TEST_VALUE (t_side);
        TEST_VALUE (t_size);
        TEST_VALUE (t_size3);
        TEST_VALUE (t_sizes);
        TEST_VALUE (t_sizex);
        TEST_VALUE (t_smei);
        TEST_VALUE (t_spacer);
        TEST_VALUE (t_spacing);
        TEST_VALUE (t_spreadmethod);
        TEST_VALUE (t_srcset);
        TEST_VALUE (t_ssi);
        TEST_VALUE (t_ssi_comparison);
        TEST_VALUE (t_ssi_config);
        TEST_VALUE (t_ssi_echo);
        TEST_VALUE (t_ssi_encoding);
        TEST_VALUE (t_ssi_env);
        TEST_VALUE (t_ssi_f);
        TEST_VALUE (t_start);
        TEST_VALUE (t_startend);
        TEST_VALUE (t_stitchtiles);
        TEST_VALUE (t_streamedcontents);
        TEST_VALUE (t_svg_feature);
        TEST_VALUE (t_ssi_include);
        TEST_VALUE (t_ssi_set);
        TEST_VALUE (t_ssi_sizefmt);
        TEST_VALUE (t_step);
        TEST_VALUE (t_style);
        TEST_VALUE (t_svg_align);
        TEST_VALUE (t_svg_baselineshift);
        TEST_VALUE (t_svg_baseprofile);
        TEST_VALUE (t_svg_clip);
        TEST_VALUE (t_svg_content);
        TEST_VALUE (t_svg_direction);
        TEST_VALUE (t_svg_direction2);
        TEST_VALUE (t_svg_display);
        TEST_VALUE (t_svg_duration);
        TEST_VALUE (t_svg_features);
        TEST_VALUE (t_svg_fontstretch);
        TEST_VALUE (t_svg_fontstretch_ff);
        TEST_VALUE (t_svg_fontstyle);
        TEST_VALUE (t_svg_fontstyle_ff);
        TEST_VALUE (t_svg_fontvariant);
        TEST_VALUE (t_svg_fontvariant_ff);
        TEST_VALUE (t_svg_fontweight);
        TEST_VALUE (t_svg_fontweight_ff);
        TEST_VALUE (t_svg_fontweights);
        TEST_VALUE (t_svg_host);
        TEST_VALUE (t_svg_method);
        TEST_VALUE (t_svg_mode);
        TEST_VALUE (t_svg_overflow);
        TEST_VALUE (t_svg_phase);
        TEST_VALUE (t_svg_playbackorder);
        TEST_VALUE (t_svg_shape);
        TEST_VALUE (t_svg_shapefn);
        TEST_VALUE (t_svg_side);
        TEST_VALUE (t_svg_svg);
        TEST_VALUE (t_svg_time);
        TEST_VALUE (t_svg_time_default);
        TEST_VALUE (t_svg_time_inherit);
        TEST_VALUE (t_svg_time_none);
        TEST_VALUE (t_svg_timelinebegin);
        TEST_VALUE (t_svg_transform);
        TEST_VALUE (t_svg_type);
        TEST_VALUE (t_svg_units);
        TEST_VALUE (t_svg_values);
        TEST_VALUE (t_svg_version);
        TEST_VALUE (t_svg_version_grand);
        TEST_VALUE (t_svg_viewbox);
        TEST_VALUE (t_svg_viewboxrect);
        TEST_VALUE (t_sym);
        TEST_VALUE (t_syncbehaviour);
        TEST_VALUE (t_syncbehaviourdefault);
        TEST_VALUE (t_tableframe);
        TEST_VALUE (t_tablevalues);
        TEST_VALUE (t_target);
        TEST_VALUE (t_tbalign);
        TEST_VALUE (t_tdscope);
        TEST_VALUE (t_tel);
        TEST_VALUE (t_tel_format);
        TEST_VALUE (t_tendstotype);
        TEST_VALUE (t_text);
        TEST_VALUE (t_text_decoration);
        TEST_VALUE (t_textoverflow);
        TEST_VALUE (t_text_rendering);
        TEST_VALUE (t_tfmu);
        TEST_VALUE (t_tfa);
        TEST_VALUE (t_tfi);
        TEST_VALUE (t_tfu);
        TEST_VALUE (t_tokens);
        TEST_VALUE (t_transform);
        TEST_VALUE (t_transform_anim);
        TEST_VALUE (t_transformbehaviour);
        TEST_VALUE (t_transform_fn);
        TEST_VALUE (t_transition_subtype);
        TEST_VALUE (t_transition_type);
        TEST_VALUE (t_transp);
        TEST_VALUE (t_truefalseempty);
        TEST_VALUE (t_turbulence_type);
        TEST_VALUE (t_type);
        TEST_VALUE (t_typeof);
        TEST_VALUE (t_tz);
        TEST_VALUE (t_ugeo);
        TEST_VALUE (t_unicode_bidi);
        TEST_VALUE (t_unit);
        TEST_VALUE (t_units);
        TEST_VALUE (t_unsigned);
        TEST_VALUE (t_unsigned_byte);
        TEST_VALUE (t_unsigned_short);
        TEST_VALUE (t_unsigned_1_or_2);
        TEST_VALUE (t_un_ex);
        TEST_VALUE (t_unsigned_dosh);
        TEST_VALUE (t_uplr);
        TEST_VALUE (t_urange);
        TEST_VALUE (t_urifn);
        TEST_VALUE (t_urifn_ni);
        TEST_VALUE (t_urisz);
        TEST_VALUE (t_url);
        TEST_VALUE (t_urls);
        TEST_VALUE (t_valign);
        TEST_VALUE (t_valign3);
        TEST_VALUE (t_valign_tmb);
        TEST_VALUE (t_value);
        TEST_VALUE (t_values);
        TEST_VALUE (t_valuetype);
        TEST_VALUE (t_valuetype2);
        TEST_VALUE (t_vector_effect);
        TEST_VALUE (t_vector_effect_12);
        TEST_VALUE (t_vector_effect_2);
        TEST_VALUE (t_vector_effect_20);
        TEST_VALUE (t_vector_effect_2s);
        TEST_VALUE (t_version);
        TEST_VALUE (t_vertical_align);
        TEST_VALUE (t_vertical_align_enum);
        TEST_VALUE (t_vid);
        TEST_VALUE (t_viewportscreen);
        TEST_VALUE (t_visibility);
        TEST_VALUE (t_visibility10);
        TEST_VALUE (t_visibility11);
        TEST_VALUE (t_vocab);
        TEST_VALUE (t_vunit);
        TEST_VALUE (t_vunits);
        TEST_VALUE (t_wanted);
        TEST_VALUE (t_wallclock);
        TEST_VALUE (t_week);
        TEST_VALUE (t_whitespace);
        TEST_VALUE (t_width);
        TEST_VALUE (t_workertype);
        TEST_VALUE (t_wrap);
        TEST_VALUE (t_wrap3);
        TEST_VALUE (t_writingmode);
        TEST_VALUE (t_wxhs);
        TEST_VALUE (t_x_content_type_options);
        TEST_VALUE (t_x_ua_compatible);
        TEST_VALUE (t_xlinkactuate);
        TEST_VALUE (t_xlinkactuate_onrequest);
        TEST_VALUE (t_xlinkactuate_onload);
        TEST_VALUE (t_xlinkshow);
        TEST_VALUE (t_xlinkshow_a);
        TEST_VALUE (t_xlinkshow_e);
        TEST_VALUE (t_xlinkshow_o);
        TEST_VALUE (t_xlinktype);
        TEST_VALUE (t_xmllink);
        TEST_VALUE (t_xmlliteral);
        TEST_VALUE (t_xmlns);
        TEST_VALUE (t_xmlspace);
        TEST_VALUE (t_xmlurl);
        TEST_VALUE (t_xorder);
        TEST_VALUE (t_xsdbool);
        TEST_VALUE (t_year);
        TEST_VALUE (t_yearmonth);
        TEST_VALUE (t_yesno);
        TEST_VALUE (t_yesnoempty);
        TEST_VALUE (t_zero_to_one);
        TEST_VALUE (t_zero_to_ones);
        TEST_VALUE (t_zoompan);
        default :   nits.pick (nit_type_error, es_catastrophic, ec_type, "type ", t, " missing from test_value");
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    break; }
    return false; }
