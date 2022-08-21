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
#include "attribute/avm.h"
#include "attribute/avm_data.h"
#include "main/context.h"

typedef ::std::multimap < e_attribute, hav_t* > avm_t;
typedef ::std::array < avm_t, elem_error > vavm_t;
vavm_t avm;

#ifdef _MSC_VER
#pragma warning ( push, 3)
// the MSC linter gets a bit silly here. it wants me to use a function to avoid the plain old C array access, and I see its point.
// the only problem is the function it insists I use doesn't actually bother to compile here. Not useful.
#pragma warning ( disable : 26446 26482 )
#endif // _MSC_VER

#define AVM_UNSAFE_INIT(X) \
    for (int index = 0; havt_##X [index].tag_ != elem_error; ++index) \
        avm.at (havt_##X [index].tag_).insert (avm_t::value_type (havt_##X [index].a_, &havt_##X [index]));

#define AVM_INIT(X) \
    for (int index = 0; havt_##X [index].tag_ != elem_error; ++index) \
    {   PRESUME (havt_##X [index].tag_ == elem_##X, __FILE__, __LINE__); \
        avm.at (havt_##X [index].tag_).insert (avm_t::value_type (havt_##X [index].a_, &havt_##X [index])); }

void avm_init (nitpick& )
{   extern hav_t    
        havt_a [], havt_abbr [], havt_abbrev [], havt_above [], havt_abs [], havt_abstract [], havt_acronym [], havt_access [], havt_action [], havt_added [], havt_addeventlistener [], havt_address [],
            havt_altglyph [], havt_altglyphdef [], havt_altglyphitem [], havt_and [], havt_animate [], havt_animatecolour [], havt_animatemotion [], havt_animatetransform [], havt_animation [], havt_annotation [],
            havt_annotation_xml [], havt_applet [], havt_apply [], havt_approx [], havt_arccos [], havt_arccosh [], havt_arccot [], havt_arccoth [], havt_arccsc [], havt_arccsch [], havt_arcsec [], havt_arcsech [],
            havt_arcsin [], havt_arcsinh [], havt_arctan [], havt_arctanh [], havt_area [], havt_arg [], havt_array [], havt_article [], havt_aside [], havt_audio [], havt_au [],
        havt_b [], havt_bb [], havt_banner [], havt_bar [], havt_base [], havt_basefont [], havt_bdi [], havt_bdo [], havt_below [], havt_bgsound [], havt_big [], havt_bind [], havt_blockquote [],
            havt_blockcode [], havt_body [], havt_box [], havt_bq [], havt_br [], havt_bt [], havt_button [], havt_bvar [], havt_byline [],
        havt_calendar [], havt_canvas [], havt_caption [], havt_card [], havt_cartesianproduct [], havt_cbytes [], havt_ceiling [], havt_cerror [], havt_changed [], havt_ci [], havt_circle [], havt_cite [],
            havt_clippath [], havt_cmd [], havt_cn [], havt_code [], havt_col [], havt_colgroup [], havt_colour_profile [], havt_command [], havt_commandset [], havt_complexes [], havt_compose [],
            havt_condition [], havt_comment [], havt_conjugate [], havt_content [], havt_cos [], havt_cosh [], havt_cot [], havt_coth [], havt_credit [], havt_cs [], havt_csc [], havt_csch [], havt_csymbol [],
            havt_curl [], havt_cursor [], havt_custom [],
        havt_data [], havt_datagrid [], havt_datalist [], havt_datatemplate [], havt_dd [], havt_ddot [], havt_declare [], havt_definition_src [], havt_defs [], havt_degree [], havt_del [], havt_desc [],
            havt_details [], havt_determinant [], havt_device [], havt_devicecolour [], havt_dfn [], havt_di [], havt_dialogue [], havt_diff [], havt_dir [], havt_discard [], havt_dispatchevent [], havt_div [],
            havt_divergence [], havt_divide [], havt_dl [], havt_domain [], havt_domainofapplication [], havt_dot [], havt_dt [],
        havt_element [], havt_elementdef [], havt_ellipse [], havt_em [], havt_embed [], havt_emptyset [], havt_eq [], havt_equivalent [], havt_eulergamma [], havt_event_source [], havt_eventsource [],
            havt_exists [], havt_exp [], havt_exponentiale [], havt_extensiondefs [],
        havt_factorial [], havt_factorof [], havt_false [], havt_feblend [], havt_fecolourmatrix [], havt_fecomponenttransfer [], havt_fecomposite [], havt_feconvolvematrix [], havt_fediffuselighting [],
            havt_fedisplacementmap [], havt_fedistantlight [], havt_fedropshadow [], havt_feflood [], havt_fefunca [], havt_fefuncb [], havt_fefuncg [], havt_fefuncr [], havt_fegaussianblur [], havt_feimage [],
            havt_femerge [], havt_femergenode [], havt_femorphology [], havt_feoffset [], havt_fepointlight [], havt_fespecularlighting [], havt_fespotlight [], havt_fetile [], havt_feturbulence [],
            havt_fieldset [], havt_fig [], havt_figcaption [], havt_figure [], havt_filter [], havt_flowdiv [], havt_flowimage [], havt_flowline [], havt_flowpara [], havt_flowref [], havt_flowregion [],
            havt_flowregionbreak [], havt_flowregionexclude [], havt_flowroot [], havt_flowspan [], havt_flowtref [], havt_floor [], havt_fn [], havt_font [], havt_font_face [], havt_font_face_format [],
            havt_font_face_name [], havt_font_face_src [], havt_font_face_uri [], havt_footer [], havt_footnote [], havt_forall [], havt_foreignobject [], havt_form [], havt_frame [], havt_frameset [],
        havt_g [], havt_gauge [], havt_gcd [], havt_geq [], havt_glyph [], havt_glyphref [], havt_grad [], havt_gt [],
        havt_h [], havt_handler [], havt_hat [], havt_head [], havt_header [], havt_hgroup [], havt_hint [], havt_hkern [], havt_hr [], havt_html [], havt_htmlplus [],
        havt_i [], havt_ident [], havt_iframe [], havt_ilayer [], havt_image [], havt_imaginary [], havt_imaginaryi [], havt_img [], havt_implies [], havt_in [], havt_infinity [], havt_input [],
            havt_ins [], havt_int [], havt_integers [], havt_intersect [], havt_interval [], havt_inverse [], havt_isindex [], havt_item [],
        havt_kbd [], havt_keygen [],
        havt_l [], havt_label [], havt_lambda [], havt_laplacian [], havt_layer [], havt_lcm [], havt_legend [], havt_leq [], havt_lh [], havt_li [], havt_limit [], havt_line [], havt_lineargradient [],
            havt_link [], havt_list [], havt_listener [], havt_listing [], havt_lit [], havt_ln [], havt_loc [], havt_log [], havt_logbase [], havt_lowlimit [], havt_lt [],
        havt_m [], havt_maction [], havt_maligngroup [], havt_malignmark [], havt_main [], havt_map [], havt_margin [], havt_mark [], havt_marker [], havt_marquee [], havt_mask [], havt_math [],
            havt_matrix [], havt_matrixrow [], havt_max [], havt_mean [], havt_median [], havt_menclose [], havt_menu [], havt_menubar [], havt_menuitem [], havt_menulabel [], havt_merror [], havt_meta [],
            havt_metadata [], havt_meter [], havt_mfenced [], havt_mfrac [], havt_mglyph [], havt_mh [], havt_mi [], havt_min [], havt_minus [], havt_missingglyph [], havt_mlabeledtr [], havt_mlongdiv [],
            havt_mmultiscripts [], havt_mn [], havt_mo [], havt_mode [], havt_moment [], havt_momentabout [], havt_mover [], havt_mpadded [], havt_mpath [], havt_mphantom [], havt_mprescripts [], havt_mroot [],
            havt_mrow [], havt_ms [], havt_mscarries [], havt_mscarry [], havt_msgroup [], havt_msline [], havt_mspace [], havt_msqrt [], havt_msrow [], havt_mstack [], havt_mstyle [], havt_msub [],
            havt_msubsup [], havt_msup [], havt_mtable [], havt_mtd [], havt_mtext [], havt_mtr [], havt_munder [], havt_munderover [],
        havt_naturalnumbers [], havt_nav [], havt_navigation [], havt_neq [], havt_nest [], havt_nextid [], havt_nl [], havt_noframes [], havt_none [], havt_noscript [], havt_not [], havt_note [], havt_notanumber [],
            havt_notin [], havt_notprsubset [], havt_notsubset [],
        havt_object [], havt_ol [], havt_optgroup [], havt_option [], havt_or [], havt_otherwise [], havt_outerproduct [], havt_output [], havt_overlay [],
        havt_p [], havt_page [], havt_pageset [], havt_param [], havt_partialdiff [], havt_path [], havt_pattern [], havt_person [], havt_pi [], havt_picture [], havt_piece [], havt_piecewise [],
            havt_plus [], havt_polygon [], havt_polyline [], havt_power [], havt_pre [], havt_prefetch [], havt_preventdefault [], havt_primes [], havt_product [], havt_progress [], havt_prototype [],
            havt_prsubset [],
        havt_q [], havt_quote [], havt_quotient [],
        havt_radialgradient [], havt_range [], havt_rationals [], havt_rb [], havt_real [], havt_reals [], havt_rect [], havt_refcontent [], havt_reln [], havt_rem [], havt_removed [], havt_removeeventlistener [],
            havt_render [], havt_root [], havt_rp [], havt_rt [], havt_rtc [], havt_ruby [], havt_rule [], havt_rdf_1 [], havt_rdf_2 [], havt_rdf_3 [], havt_rdf_4 [], havt_rdf_5 [], havt_rdf_6 [],
            havt_rdf_7 [], havt_rdf_8 [], havt_rdf_9 [], havt_rdf_about [], havt_rdf_abouteach [], havt_rdf_abouteachprefix [], havt_rdf_alt [], havt_rdf_bag [], havt_rdf_bagid [], havt_rdf_datatype [],
            havt_rdf_description [], havt_rdf_id [], havt_rdf_li [], havt_rdf_nodeid [], havt_rdf_parsetype [], havt_rdf_rdf [], havt_rdf_resource [], havt_rdf_seq [],
        havt_s [], havt_samp [], havt_scalarproduct [], havt_script [], havt_sdev [], havt_sec [], havt_sech [], havt_section [], havt_select [], havt_selector [], havt_semantics [], havt_sep [],
            havt_separator [], havt_set [], havt_setdiff [], havt_shadow [], havt_share [], havt_sidebar [], havt_sin [], havt_sinh [], havt_slot [], havt_small [], havt_solidcolour [], havt_source [],
            havt_span [], havt_spot [], havt_sqrt [], havt_stop [], havt_stoppropagation [], havt_strike [], havt_strong [], havt_style [], havt_sub [], havt_subset [], havt_sum [], havt_summary [],
            havt_sup [], havt_svg [], havt_switch [], havt_symbol [],
        havt_t [], havt_tab [], havt_tabbox [], havt_table [], havt_tan [], havt_tanh [], havt_tbody [], havt_tbreak [], havt_td [], havt_template [], havt_tendsto [], havt_text [], havt_textarea [],
            havt_textpath [], havt_tfoot [], havt_th [], havt_thead [], havt_tilde [], havt_time [], havt_times [], havt_title [], havt_tr [], havt_track [], havt_traitdef [], havt_transformer [],
            havt_transition [], havt_transpose [], havt_tref [], havt_true [], havt_tspan [], havt_tt [],
        havt_u [], havt_ul [], havt_union [], havt_uplimit [], havt_use [],
        havt_var [], havt_variance [], havt_veaffine [], havt_vec [], havt_vector [], havt_vectoreffect [], havt_vectorproduct [], havt_veexclude [], havt_vefill [], havt_vejoin [], havt_veintersect [],
            havt_vemarker [], havt_vepath [], havt_vepathref [], havt_vereverse [], havt_vesetback [], havt_vestroke [], havt_vestrokepath [], havt_veunion [], havt_video [], havt_view [], havt_vkern [],
        havt_wbr [],
        havt_xa [], havt_xmp [], havt_xor [];

    avm.fill (avm_t ());

    AVM_INIT (a);
    AVM_INIT (abbr);
    AVM_INIT (abbrev);
    AVM_INIT (above);
    AVM_INIT (abs);
    AVM_INIT (abstract);
    AVM_INIT (acronym);
    AVM_INIT (access);
    AVM_INIT (action);
    AVM_INIT (added);
    AVM_INIT (addeventlistener);
    AVM_INIT (address);
    AVM_INIT (altglyph);
    AVM_INIT (altglyphdef);
    AVM_INIT (altglyphitem);
    AVM_INIT (and);
    AVM_INIT (animate);
    AVM_INIT (animatecolour);
    AVM_INIT (animatemotion);
    AVM_INIT (animatetransform);
    AVM_INIT (animation);
    AVM_INIT (annotation);
    AVM_INIT (annotation_xml);
    AVM_INIT (applet);
    AVM_INIT (apply);
    AVM_INIT (approx);
    AVM_INIT (arccos);
    AVM_INIT (arccosh);
    AVM_INIT (arccot);
    AVM_INIT (arccoth);
    AVM_INIT (arccsc);
    AVM_INIT (arccsch);
    AVM_INIT (arcsec);
    AVM_INIT (arcsech);
    AVM_INIT (arcsin);
    AVM_INIT (arcsinh);
    AVM_INIT (arctan);
    AVM_INIT (arctanh);
    AVM_INIT (area);
    AVM_INIT (arg);
    AVM_INIT (array);
    AVM_INIT (article);
    AVM_INIT (aside);
    AVM_INIT (audio);
    AVM_INIT (au);
    AVM_INIT (b);
    AVM_INIT (bb);
    AVM_INIT (banner);
    AVM_INIT (bar);
    AVM_INIT (base);
    AVM_INIT (basefont);
    AVM_INIT (bdi);
    AVM_INIT (bdo);
    AVM_INIT (below);
    AVM_INIT (bgsound);
    AVM_INIT (big);
    AVM_INIT (bind);
    AVM_INIT (blockquote);
    AVM_INIT (blockcode);
    AVM_INIT (body);
    AVM_INIT (box);
    AVM_INIT (bq);
    AVM_INIT (br);
    AVM_INIT (bt);
    AVM_INIT (button);
    AVM_INIT (bvar);
    AVM_INIT (byline);
    AVM_INIT (calendar);
    AVM_INIT (canvas);
    AVM_INIT (caption);
    AVM_INIT (card);
    AVM_INIT (cartesianproduct);
    AVM_INIT (cbytes);
    AVM_INIT (ceiling);
    AVM_INIT (cerror);
    AVM_INIT (changed);
    AVM_INIT (ci);
    AVM_INIT (circle);
    AVM_INIT (cite);
    AVM_INIT (clippath);
    AVM_INIT (cmd);
    AVM_INIT (cn);
    AVM_INIT (code);
    AVM_INIT (col);
    AVM_INIT (colgroup);
    AVM_INIT (colour_profile);
    AVM_INIT (command);
    AVM_INIT (commandset);
    AVM_INIT (complexes);
    AVM_INIT (compose);
    AVM_INIT (condition);
    AVM_INIT (comment);
    AVM_INIT (conjugate);
    AVM_INIT (content);
    AVM_INIT (cos);
    AVM_INIT (cosh);
    AVM_INIT (cot);
    AVM_INIT (coth);
    AVM_INIT (credit);
    AVM_INIT (cs);
    AVM_INIT (csc);
    AVM_INIT (csch);
    AVM_INIT (csymbol);
    AVM_INIT (curl);
    AVM_INIT (cursor);
    AVM_INIT (custom);
    AVM_INIT (data);
    AVM_INIT (datagrid);
    AVM_INIT (datalist);
    AVM_INIT (datatemplate);
    AVM_INIT (dd);
    AVM_INIT (ddot);
    AVM_INIT (declare);
    AVM_INIT (definition_src);
    AVM_INIT (defs);
    AVM_INIT (degree);
    AVM_INIT (del);
    AVM_INIT (desc);
    AVM_INIT (details);
    AVM_INIT (determinant);
    AVM_INIT (device);
    AVM_INIT (devicecolour);
    AVM_INIT (dfn);
    AVM_INIT (di);
    AVM_INIT (dialogue);
    AVM_INIT (diff);
    AVM_INIT (dir);
    AVM_INIT (discard);
    AVM_INIT (dispatchevent);
    AVM_INIT (div);
    AVM_INIT (divergence);
    AVM_INIT (divide);
    AVM_INIT (dl);
    AVM_INIT (domain);
    AVM_INIT (domainofapplication);
    AVM_INIT (dot);
    AVM_INIT (dt);
    AVM_INIT (element);
    AVM_INIT (elementdef);
    AVM_INIT (ellipse);
    AVM_INIT (em);
    AVM_INIT (embed);
    AVM_INIT (emptyset);
    AVM_INIT (eq);
    AVM_INIT (equivalent);
    AVM_INIT (eulergamma);
    AVM_INIT (event_source);
    AVM_INIT (eventsource);
    AVM_INIT (exists);
    AVM_INIT (exp);
    AVM_INIT (exponentiale);
    AVM_INIT (extensiondefs);
    AVM_INIT (factorial);
    AVM_INIT (factorof);
    AVM_INIT (false);
    AVM_INIT (feblend);
    AVM_INIT (fecolourmatrix);
    AVM_INIT (fecomponenttransfer);
    AVM_INIT (fecomposite);
    AVM_INIT (feconvolvematrix);
    AVM_INIT (fediffuselighting);
    AVM_INIT (fedisplacementmap);
    AVM_INIT (fedistantlight);
    AVM_INIT (fedropshadow);
    AVM_INIT (feflood);
    AVM_INIT (fefunca);
    AVM_INIT (fefuncb);
    AVM_INIT (fefuncg);
    AVM_INIT (fefuncr);
    AVM_INIT (fegaussianblur);
    AVM_INIT (feimage);
    AVM_INIT (femerge);
    AVM_INIT (femergenode);
    AVM_INIT (femorphology);
    AVM_INIT (feoffset);
    AVM_INIT (fepointlight);
    AVM_INIT (fespecularlighting);
    AVM_INIT (fespotlight);
    AVM_INIT (fetile);
    AVM_INIT (feturbulence);
    AVM_INIT (fieldset);
    AVM_INIT (fig);
    AVM_INIT (figcaption);
    AVM_INIT (figure);
    AVM_INIT (filter);
    AVM_INIT (flowdiv);
    AVM_INIT (flowimage);
    AVM_INIT (flowline);
    AVM_INIT (flowpara);
    AVM_INIT (flowref);
    AVM_INIT (flowregion);
    AVM_INIT (flowregionbreak);
    AVM_INIT (flowregionexclude);
    AVM_INIT (flowroot);
    AVM_INIT (flowspan);
    AVM_INIT (flowtref);
    AVM_INIT (floor);
    AVM_INIT (fn);
    AVM_INIT (font);
    AVM_INIT (font_face);
    AVM_INIT (font_face_format);
    AVM_INIT (font_face_name);
    AVM_INIT (font_face_src);
    AVM_INIT (font_face_uri);
    AVM_INIT (footer);
    AVM_INIT (footnote);
    AVM_INIT (forall);
    AVM_INIT (foreignobject);
    AVM_INIT (form);
    AVM_INIT (frame);
    AVM_INIT (frameset);
    AVM_INIT (g);
    AVM_INIT (gauge);
    AVM_INIT (gcd);
    AVM_INIT (geq);
    AVM_INIT (glyph);
    AVM_INIT (glyphref);
    AVM_INIT (grad);
    AVM_INIT (gt);
    AVM_UNSAFE_INIT (h);
    AVM_INIT (handler);
    AVM_INIT (hat);
    AVM_INIT (head);
    AVM_INIT (header);
    AVM_INIT (hgroup);
    AVM_INIT (hint);
    AVM_INIT (hkern);
    AVM_INIT (hr);
    AVM_INIT (html);
    AVM_INIT (htmlplus);
    AVM_INIT (i);
    AVM_INIT (ident);
    AVM_INIT (iframe);
    AVM_INIT (ilayer);
    AVM_INIT (image);
    AVM_INIT (imaginary);
    AVM_INIT (imaginaryi);
    AVM_INIT (img);
    AVM_INIT (implies);
    AVM_INIT (in);
    AVM_INIT (infinity);
    AVM_INIT (input);
    AVM_INIT (ins);
    AVM_INIT (int);
    AVM_INIT (integers);
    AVM_INIT (intersect);
    AVM_INIT (interval);
    AVM_INIT (inverse);
    AVM_INIT (isindex);
    AVM_INIT (item);
    AVM_INIT (kbd);
    AVM_INIT (keygen);
    AVM_INIT (l);
    AVM_INIT (label);
    AVM_INIT (lambda);
    AVM_INIT (laplacian);
    AVM_INIT (layer);
    AVM_INIT (lcm);
    AVM_INIT (legend);
    AVM_INIT (leq);
    AVM_INIT (lh);
    AVM_INIT (li);
    AVM_INIT (limit);
    AVM_INIT (line);
    AVM_INIT (lineargradient);
    AVM_INIT (link);
    AVM_INIT (list);
    AVM_INIT (listener);
    AVM_INIT (listing);
    AVM_INIT (lit);
    AVM_INIT (ln);
    AVM_INIT (loc);
    AVM_INIT (log);
    AVM_INIT (logbase);
    AVM_INIT (lowlimit);
    AVM_INIT (lt);
    AVM_INIT (m);
    AVM_INIT (maction);
    AVM_INIT (maligngroup);
    AVM_INIT (malignmark);
    AVM_INIT (main);
    AVM_INIT (map);
    AVM_INIT (margin);
    AVM_INIT (mark);
    AVM_INIT (marker);
    AVM_INIT (marquee);
    AVM_INIT (mask);
    AVM_INIT (math);
    AVM_INIT (matrix);
    AVM_INIT (matrixrow);
    AVM_INIT (max);
    AVM_INIT (mean);
    AVM_INIT (median);
    AVM_INIT (menclose);
    AVM_INIT (menu);
    AVM_INIT (menubar);
    AVM_INIT (menuitem);
    AVM_INIT (menulabel);
    AVM_INIT (merror);
    AVM_INIT (meta);
    AVM_INIT (metadata);
    AVM_INIT (meter);
    AVM_INIT (mfenced);
    AVM_INIT (mfrac);
    AVM_INIT (mglyph);
    AVM_INIT (mh);
    AVM_INIT (mi);
    AVM_INIT (min);
    AVM_INIT (minus);
    AVM_INIT (missingglyph);
    AVM_INIT (mlabeledtr);
    AVM_INIT (mlongdiv);
    AVM_INIT (mmultiscripts);
    AVM_INIT (mn);
    AVM_INIT (mo);
    AVM_INIT (mode);
    AVM_INIT (moment);
    AVM_INIT (momentabout);
    AVM_INIT (mover);
    AVM_INIT (mpadded);
    AVM_INIT (mpath);
    AVM_INIT (mphantom);
    AVM_INIT (mprescripts);
    AVM_INIT (mroot);
    AVM_INIT (mrow);
    AVM_INIT (ms);
    AVM_INIT (mscarries);
    AVM_INIT (mscarry);
    AVM_INIT (msgroup);
    AVM_INIT (msline);
    AVM_INIT (mspace);
    AVM_INIT (msqrt);
    AVM_INIT (msrow);
    AVM_INIT (mstack);
    AVM_INIT (mstyle);
    AVM_INIT (msub);
    AVM_INIT (msubsup);
    AVM_INIT (msup);
    AVM_INIT (mtable);
    AVM_INIT (mtd);
    AVM_INIT (mtext);
    AVM_INIT (mtr);
    AVM_INIT (munder);
    AVM_INIT (munderover);
    AVM_INIT (naturalnumbers);
    AVM_INIT (nav);
    AVM_INIT (navigation);
    AVM_INIT (neq);
    AVM_INIT (nest);
    AVM_INIT (nextid);
    AVM_INIT (nl);
    AVM_INIT (noframes);
    AVM_INIT (none);
    AVM_INIT (noscript);
    AVM_INIT (not);
    AVM_INIT (note);
    AVM_INIT (notanumber);
    AVM_INIT (notin);
    AVM_INIT (notprsubset);
    AVM_INIT (notsubset);
    AVM_INIT (object);
    AVM_INIT (ol);
    AVM_INIT (optgroup);
    AVM_INIT (option);
    AVM_INIT (or);
    AVM_INIT (otherwise);
    AVM_INIT (outerproduct);
    AVM_INIT (output);
    AVM_INIT (overlay);
    AVM_INIT (p);
    AVM_INIT (page);
    AVM_INIT (pageset);
    AVM_INIT (param);
    AVM_INIT (partialdiff);
    AVM_INIT (path);
    AVM_INIT (pattern);
    AVM_INIT (person);
    AVM_INIT (pi);
    AVM_INIT (picture);
    AVM_INIT (piece);
    AVM_INIT (piecewise);
    AVM_INIT (plus);
    AVM_INIT (polygon);
    AVM_INIT (polyline);
    AVM_INIT (power);
    AVM_INIT (pre);
    AVM_INIT (prefetch);
    AVM_INIT (preventdefault);
    AVM_INIT (primes);
    AVM_INIT (product);
    AVM_INIT (progress);
    AVM_INIT (prototype);
    AVM_INIT (prsubset);
    AVM_INIT (q);
    AVM_INIT (quote);
    AVM_INIT (quotient);
    AVM_INIT (radialgradient);
    AVM_INIT (range);
    AVM_INIT (rationals);
    AVM_INIT (rb);
    AVM_INIT (real);
    AVM_INIT (reals);
    AVM_INIT (rect);
    AVM_INIT (refcontent);
    AVM_INIT (reln);
    AVM_INIT (rem);
    AVM_INIT (removed);
    AVM_INIT (removeeventlistener);
    AVM_INIT (render);
    AVM_INIT (root);
    AVM_INIT (rp);
    AVM_INIT (rt);
    AVM_INIT (rtc);
    AVM_INIT (ruby);
    AVM_INIT (rule);
    AVM_INIT (rdf_1);
    AVM_INIT (rdf_2);
    AVM_INIT (rdf_3);
    AVM_INIT (rdf_4);
    AVM_INIT (rdf_5);
    AVM_INIT (rdf_6);
    AVM_INIT (rdf_7);
    AVM_INIT (rdf_8);
    AVM_INIT (rdf_9);
    AVM_INIT (rdf_about);
    AVM_INIT (rdf_abouteach);
    AVM_INIT (rdf_abouteachprefix);
    AVM_INIT (rdf_alt);
    AVM_INIT (rdf_bag);
    AVM_INIT (rdf_bagid);
    AVM_INIT (rdf_datatype);
    AVM_INIT (rdf_description);
    AVM_INIT (rdf_id);
    AVM_INIT (rdf_li);
    AVM_INIT (rdf_nodeid);
    AVM_INIT (rdf_parsetype);
    AVM_INIT (rdf_rdf);
    AVM_INIT (rdf_resource);
    AVM_INIT (rdf_seq);
    AVM_INIT (s);
    AVM_INIT (samp);
    AVM_INIT (scalarproduct);
    AVM_INIT (script);
    AVM_INIT (sdev);
    AVM_INIT (sec);
    AVM_INIT (sech);
    AVM_INIT (section);
    AVM_INIT (select);
    AVM_INIT (selector);
    AVM_INIT (semantics);
    AVM_INIT (sep);
    AVM_INIT (separator);
    AVM_INIT (set);
    AVM_INIT (setdiff);
    AVM_INIT (shadow);
    AVM_INIT (share);
    AVM_INIT (sidebar);
    AVM_INIT (sin);
    AVM_INIT (sinh);
    AVM_INIT (slot);
    AVM_INIT (small);
    AVM_INIT (solidcolour);
    AVM_INIT (source);
    AVM_INIT (span);
    AVM_INIT (spot);
    AVM_INIT (sqrt);
    AVM_INIT (stop);
    AVM_INIT (stoppropagation);
    AVM_INIT (strike);
    AVM_INIT (strong);
    AVM_INIT (style);
    AVM_INIT (sub);
    AVM_INIT (subset);
    AVM_INIT (sum);
    AVM_INIT (summary);
    AVM_INIT (sup);
    AVM_INIT (svg);
    AVM_INIT (switch);
    AVM_INIT (symbol);
    AVM_INIT (t);
    AVM_INIT (tab);
    AVM_INIT (tabbox);
    AVM_INIT (table);
    AVM_INIT (tan);
    AVM_INIT (tanh);
    AVM_INIT (tbody);
    AVM_INIT (tbreak);
    AVM_INIT (td);
    AVM_INIT (template);
    AVM_INIT (tendsto);
    AVM_INIT (text);
    AVM_INIT (textarea);
    AVM_INIT (textpath);
    AVM_INIT (tfoot);
    AVM_INIT (th);
    AVM_INIT (thead);
    AVM_INIT (tilde);
    AVM_INIT (time);
    AVM_INIT (times);
    AVM_INIT (title);
    AVM_INIT (tr);
    AVM_INIT (track);
    AVM_INIT (traitdef);
    AVM_INIT (transformer);
    AVM_INIT (transition);
    AVM_INIT (transpose);
    AVM_INIT (tref);
    AVM_INIT (true);
    AVM_INIT (tspan);
    AVM_INIT (tt);
    AVM_INIT (u);
    AVM_INIT (ul);
    AVM_INIT (union);
    AVM_INIT (uplimit);
    AVM_INIT (use);
    AVM_INIT (var);
    AVM_INIT (variance);
    AVM_INIT (veaffine);
    AVM_INIT (vec);
    AVM_INIT (vector);
    AVM_INIT (vectoreffect);
    AVM_INIT (vectorproduct);
    AVM_INIT (veexclude);
    AVM_INIT (vefill);
    AVM_INIT (vejoin);
    AVM_INIT (veintersect);
    AVM_INIT (vemarker);
    AVM_INIT (vepath);
    AVM_INIT (vepathref);
    AVM_INIT (vereverse);
    AVM_INIT (vesetback);
    AVM_INIT (vestroke);
    AVM_INIT (vestrokepath);
    AVM_INIT (veunion);
    AVM_INIT (video);
    AVM_INIT (view);
    AVM_INIT (vkern);
    AVM_INIT (wbr);
    AVM_INIT (xa);
    AVM_INIT (xmp);
    AVM_INIT (xor); }

#ifdef _MSC_VER
#pragma warning (pop)
#endif

bool is_invalid_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (   avm_t::const_iterator i = avm.at (tag).find (a);
            (i != avm.at (tag).cend ()) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return false;
    for (   avm_t::const_iterator i = avm.at (elem_undefined).find (a);
            (i != avm.at (elem_undefined).cend ()) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second ->last_)) return false;
    return true; }

bool is_deprecated_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (   avm_t::const_iterator i = avm.at (tag).find (a);
            (i != avm.at (tag).cend ()) && (i -> second-> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.deprecated (v);
    for (   avm_t::const_iterator i = avm.at (elem_undefined).find (a);
            (i != avm.at (elem_undefined).cend ()) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.deprecated (v);
    return false; }

bool not_production_attribute (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && v.is_5 () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.at (tag).find (a);
                (i != avm.at (tag).cend ()) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.not_production ();
    return false; }

bool is_attribute_required (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.at (tag).find (a);
                (i != avm.at (tag).cend ()) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.required ();
    return false; }

bool is_attribute_rejected (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.at (tag).find (a);
                (i != avm.at (tag).cend ()) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.reject ();
    return false; }

#ifdef DEBUG
void avm_elem_crosscheck ()
{   void avm_class_crosscheck (const e_element e, const e_attribute a);
    if (context.tell (es_detail))
        for (int e = 0; e < elem_error; ++e)
            for (auto a : avm.at (e))
                avm_class_crosscheck (e, a.first); }
#endif // DEBUG
