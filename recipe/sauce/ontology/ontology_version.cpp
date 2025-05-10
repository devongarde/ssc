/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "ontology/ontology_version.h"
#include "parser/html_version.h"
#include "symbol/nstr.h"
#include "utility/common.h"

#define DPV_X_SH_221(XXX) \
    { dpv_##XXX##_2_1, html_dpv_2_1 }, \
    { dpv_##XXX##_2_0, html_dpv_2_0 }

#define DPV_X_SH_80(XXX) \
    { dpv_##XXX##_1_0, html_dpv_1 }, \
    { dpv_##XXX##_0_9, html_dpv_09 }, \
    { dpv_##XXX##_0_8_2, html_dpv_082 }, \
    { dpv_##XXX##_0_8_1, html_dpv_081 }, \
    { dpv_##XXX##_0_8_0, html_dpv_080 }

#define DPV_X_SH_50(XXX) \
    DPV_X_SH_80 (XXX), \
    { dpv_##XXX##_0_7, html_dpv_07 }, \
    { dpv_##XXX##_0_6, html_dpv_06 }, \
    { dpv_##XXX##_0_5, html_dpv_05 }

#define DPV_X_SH_40(XXX) \
    DPV_X_SH_50 (XXX), \
    { dpv_##XXX##_0_4_2, html_dpv_042 }, \
    { dpv_##XXX##_0_4_1, html_dpv_041 }, \
    { dpv_##XXX##_0_4_0, html_dpv_040 }

struct sh_t
{   ontology_version ontology_;
    html_version html_; };

sh_t sh [] =  // latest first
{   { adms_2_0, html_adms_2_0 },
    { adms_1_0, html_adms_1_0 },
    { article_2018, html_jan18 },
    { article_2014, html_jan14 },
    { article_2012, html_jan12 },
    { as_2_0, html_as_2_0 },
    { as_1_0, html_as_1_0 },
    { bfo_2020, html_nov21 },
    { bfo_2_0, html_jun15 },
    { bibo_schema, html_rdf_1_0 },
    { biro_schema, html_may13 },
    { book_2018, html_jan18 },
    { book_2014, html_jan14 },
    { book_2012, html_jan12 },
    { cito_schema, html_jan18 },
    { cnt_schema, html_rdf_1_0_con },
    { common_tag, html_rdf_1_0_con },
    { content_schema, html_rdf_1_0 },
    { creative_commons, html_cc },
    { croissant_1_100, html_croissant_1_100 },
    { croissant_1_17, html_croissant_1_17 },
    { croissant_1_16, html_croissant_1_16 },
    { croissant_1_15, html_croissant_1_15 },
    { croissant_1_14, html_croissant_1_14 },
    { croissant_1_13, html_croissant_1_13 },
    { croissant_1_12, html_croissant_1_12 },
    { croissant_1_11, html_croissant_1_11 },
    { croissant_1_10, html_croissant_1_10 },
    { croissant_1_9, html_croissant_1_9 },
    { croissant_1_8, html_croissant_1_8 },
    { croissant_1_7, html_croissant_1_7 },
    { croissant_1_6, html_croissant_1_6 },
    { croissant_1_5, html_croissant_1_5 },
    { croissant_1_4, html_croissant_1_4 },
    { croissant_1_3, html_croissant_1_3 },
    { croissant_1_2, html_croissant_1_2 },
    { croissant_1_1, html_croissant_1_1 },
    { croissant_1_0, html_croissant_1_0 },
    { croissant_0_8, html_croissant_0_8 },
    { croissant_0_6, html_croissant_0_6 },
    { croissant_0_4, html_croissant_0_4 },
    { croissant_0_3, html_croissant_0_3 },
    { croissant_0_2, html_croissant_0_2 },
    { crs2_schema, html_xmp },
    { csvw_schema, html_jan16 },
    { daq_schema, html_rdf_1_0_con },
    { dbd_schema, html_rdf_1_0_con },
    { dbo_schema, html_rdf_1_0_con },
    { dbp_schema, html_rdf_1_0_con },
    { dbp_owl_schema, html_rdf_1_0_con },
    { dbr_schema, html_rdf_1_0_con },
    { dc_1_1, html_dc_1_1 },
    { dc_1_0, html_dc_1_0 },
    { dcam, html_rdf_1_0_con },
    { dc_1_0, html_dc_1_0 },
    { dc_1_0, html_dc_1_0 },
    { data_catalogue_3, html_dcat_3 },
    { data_catalogue_2, html_rdf_1_0_con },
    { data_catalogue_1, html_rdf_1_0 },
    { dcmi, html_rdf_1_0_con },
    { dublin_core_terms_1_1, html_dcterms_1_1 },
    { dublin_core_terms_1_0, html_dcterms_1_0 },
    { disco_schema, html_rdf_1_0_con },
    { doap_schema, html_rdf_1_0 },
    { data_quality, html_rdf_1_0_con },
    { described_by, html_rdf_1_0 },
    { dpv_2_1, html_dpv_2_1},
    { dpv_2_0, html_dpv_2_0 },
    { dpv_1_0, html_dpv_1 },
    { dpv_0_9, html_dpv_09 },
    { dpv_0_8_2, html_dpv_082 },
    { dpv_0_8_1, html_dpv_081 },
    { dpv_0_8_0, html_dpv_080 },
    { dpv_0_7, html_dpv_07 },
    { dpv_0_6, html_dpv_06 },
    { dpv_0_5, html_dpv_05 },
    { dpv_0_4_2, html_dpv_042 },
    { dpv_0_4_1, html_dpv_041 },
    { dpv_0_4_0, html_dpv_040 },
    { dpv_0_3, html_dpv_03 },
    { dpv_0_2, html_dpv_02 },
    { dpv_0_1, html_dpv_01 },
    DPV_X_SH_221 (ai),
    DPV_X_SH_221 (eu_aiact),
    DPV_X_SH_221 (eu_dga),
     { dpv_eu_ehds_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (eu_gdpr),
    DPV_X_SH_221 (eu_nis2),
    DPV_X_SH_221 (eu_rights),
    DPV_X_SH_40 (gdpr),
    { dpv_gdpr_0_3, html_dpv_03 },
    { dpv_gdpr_0_2, html_dpv_02 },
    { dpv_gdpr_0_1, html_dpv_01 },
    DPV_X_SH_221 (just),
    DPV_X_SH_50 (legal),
    { dpv_legal_at_2_1, html_dpv_2_1 },
    { dpv_legal_be_2_1, html_dpv_2_1 },
    { dpv_legal_bg_2_1, html_dpv_2_1 },
    { dpv_legal_cy_2_1, html_dpv_2_1 },
    { dpv_legal_cz_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (legal_de),
    { dpv_legal_dk_2_1, html_dpv_2_1 },
    { dpv_legal_ee_2_1, html_dpv_2_1 },
    { dpv_legal_es_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (legal_eu),
    { dpv_legal_fi_2_1, html_dpv_2_1 },
    { dpv_legal_fr_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (legal_gb),
    { dpv_legal_gr_2_1, html_dpv_2_1 },
    { dpv_legal_hr_2_1, html_dpv_2_1 },
    { dpv_legal_hu_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (legal_ie),
    DPV_X_SH_221 (legal_in),
    { dpv_legal_is_2_1, html_dpv_2_1 },
    { dpv_legal_it_2_1, html_dpv_2_1 },
    { dpv_legal_li_2_1, html_dpv_2_1 },
    { dpv_legal_lt_2_1, html_dpv_2_1 },
    { dpv_legal_lu_2_1, html_dpv_2_1 },
    { dpv_legal_lv_2_1, html_dpv_2_1 },
    { dpv_legal_mt_2_1, html_dpv_2_1 },
    { dpv_legal_nl_2_1, html_dpv_2_1 },
    { dpv_legal_no_2_1, html_dpv_2_1 },
    { dpv_legal_pl_2_1, html_dpv_2_1 },
    { dpv_legal_pt_2_1, html_dpv_2_1 },
    { dpv_legal_ro_2_1, html_dpv_2_1 },
    { dpv_legal_se_2_1, html_dpv_2_1 },
    { dpv_legal_sl_2_1, html_dpv_2_1 },
    { dpv_legal_sk_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (legal_us),
    DPV_X_SH_221 (loc),
    { dpv_nace_schema, html_dpv_01 },
    { dpv_p7012_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (pd),
    DPV_X_SH_40 (pd),
    DPV_X_SH_80 (rights),
    { dpv_risk_2_0, html_dpv_2_0 },
    DPV_X_SH_80 (risk),
    { dpv_s_edu_2_1, html_dpv_2_1 },
    { dpv_s_fin_2_1, html_dpv_2_1 },
    { dpv_s_hth_2_1, html_dpv_2_1 },
    { dpv_s_inf_2_1, html_dpv_2_1 },
    { dpv_s_law_2_1, html_dpv_2_1 },
    { dpv_s_ps_2_1, html_dpv_2_1 },
    DPV_X_SH_221 (tech),
    DPV_X_SH_80 (tech),
    { duv_schema, html_rdf_1_0_con },
    { earl_schema, html_rdf_1_0_con },
    { event_schema, html_rdf_1_0_con },
    { example_schema, html_tags },
    { exif_3_0, html_exif_3_0 },
    { exif_2_32, html_exif_2_32 },
    { exif_2_31, html_exif_2_31 },
    { exif_2_3, html_exif_2_3 },
    { exif_2_21, html_exif_2_21 },
    { exif_2_2, html_exif_2_2 },
    { exif_2_1, html_exif_2_1 },
    { exif_2_0, html_exif_2_0 },
    { exif_1_1, html_exif_1_1 },
    { exif_1_0, html_exif_1_0 },
    { exifex_3_0, html_exifex_3_0 },
    { exifex_2_32, html_exifex_2_32 },
    { exifex_2_31, html_exifex_2_31 },
    { exifex_2_3, html_exifex_2_3 },
    { exifex_2_21, html_exifex_2_21 },
    { faux_schema, html_rdf_1_0 },
    { fabio_schema, html_jan19 },
    { foaf_schema, html_rdf_1_0 },
    { frbr_schema, xhtml_1_0 },
    { good_relations, html_rdf_1_0 },
    { grddl_schema, html_rdf_1_0_con },
    { gs1_10, html_gs10 },
    { gs1_11, html_gs11 },
    { gs1_12, html_gs12 },
    { gs1_13, html_gs13 },
    { gs1_14, html_gs14 },
    { gs1_15, html_gs15 },
    { gs1_151, html_gs151 },
    { ical_schema, html_rdf_1_0_con },
    { icaltzd_schema, html_rdf_1_0_con },
    { jsonld_ontology_1_1, html_jsonld_1_1 },
    { jsonld_ontology_1_0, html_jsonld_1_0 },
    { linked_data_platform, html_rdf_1_0_con },
    { licence_schema, html_rdf_1_0_con },
    { locn_schema, html_rdf_1_0_con },
    { media_resources, html_rdf_1_0_con },
    { mf_2, html_5_0 },
    { mf_1, xhtml_1_0 },
    { music_2018, html_jan18 },
    { music_2014, html_jan14 },
    { music_2012, html_jan12 },
    { web_annotation, html_rdf_1_0_con },
    { odrl_schema, html_rdf_1_0_con },
    { open_graph_2018, html_jan18 },
    { open_graph_2014, html_jan14 },
    { open_graph_2012, html_jan12 },
    { open_graph_2010, html_jan10 },
    { org_schema, html_rdf_1_0_con },
    { owl_2, html_rdf_1_0_con },
    { owl_1, html_rdf_1_0 },
    { org_schema, html_rdf_1_0_con },
    { pam_2_0, html_prism_2_0 },
    { pamp_3_0, html_prism_3_0 },
    { pamp_3_1, html_prism_3_1 },
    { pcm_3_1, html_prism_3_1 },
    { pcmm_3_0, html_prism_3_0 },
    { pcmm_3_1, html_prism_3_1 },
    { pcv_1_0, html_prism_1_0 },
    { pdf_schema, html_xmp },
    { photoshop_schema, html_xmp },
    { pim_3_1, html_prism_3_1 },
    { pim_3_0, html_prism_3_0 },
    { pim_2_0, html_prism_2_0 },
    { pim_1_2, html_prism_1_2 },
    { pim_1_0, html_prism_1_0 },
    { pmi_3_1, html_prism_3_1 },
    { pmi_3_0, html_prism_3_0 },
    { poetry_ontology_1_1, html_oct22 },
    { poetry_ontology_1_0, html_jan18 },
    { prism_3_1, html_prism_3_1 },
    { prism_3_0, html_prism_3_0 },
    { prism_2_1, html_prism_2_1 },
    { prism_2_0, html_prism_2_0 },
    { prism_1_3, html_prism_1_3 },
    { prism_1_2, html_prism_1_2 },
    { prism_1_1, html_prism_1_1 },
    { prism_1_0, html_prism_1_0 },
    { prism_ad_3_1, html_prism_3_1 },
    { prism_ad_3_0, html_prism_3_0 },
    { prl_2_1, html_prism_2_1 },
    { prl_2_0, html_prism_2_0 },
    { prl_1_3, html_prism_1_3 },
    { prl_1_2, html_prism_1_2 },
    { prl_1_0, html_prism_1_0 },
    { prm_3_1, html_prism_3_1 },
    { prm_3_0, html_prism_3_0 },
    { prs_3_1, html_prism_3_1 },
    { profile_2014, html_jan14 },
    { profile_2012, html_jan12 },
    { provincial, html_rdf_1_0_con },
    { psv_1_0, html_prism_1_0 },
    { ptr_schema, html_ptr },
    { pur_3_0, html_prism_3_0 },
    { pur_2_1, html_prism_2_1 },
    { data_cube, html_rdf_1_0_con },
    { rai_1_100, html_rai_1_100 },
    { rai_1_17, html_rai_1_17 },
    { rai_1_16, html_rai_1_16 },
    { rai_1_15, html_rai_1_15 },
    { rai_1_14, html_rai_1_14 },
    { rai_1_13, html_rai_1_13 },
    { rai_1_12, html_rai_1_12 },
    { rai_1_11, html_rai_1_11 },
    { rai_1_10, html_rai_1_10 },
    { rai_1_9, html_rai_1_9 },
    { rai_1_8, html_rai_1_8 },
    { rai_1_7, html_rai_1_7 },
    { rai_1_6, html_rai_1_6 },
    { rai_1_5, html_rai_1_5 },
    { rai_1_4, html_rai_1_4 },
    { rai_1_3, html_rai_1_3 },
    { rdf_1_1_3_schema, html_rdf_1_1_3 },
    { rdf_1_1_2_schema, html_rdf_1_1_2 },
    { rdf_1_1_1_schema, html_rdf_1_1_1 },
    { rdf_1_0_schema, html_rdf_1_0 },
    { rdfa_1_1_3_schema, html_rdfa_1_1_3 },
    { rdfa_1_1_2_schema, html_rdfa_1_1_2 },
    { rdfa_1_1_1_schema, html_rdfa_1_1_1 },
    { rdfa_1_0_schema, html_rdfa_1_0 },
    { rdfg_schema, html_rdfg },
    { rdfs_schema, html_rdfs },
    { review_schema, html_review },
    { rif_schema, html_rif },
    { role_schema, html_role },
    { rr_schema, html_rr },
    { schema_30_0, html_schema_30_0 },
    { schema_29_1, html_schema_29_1 },
    { schema_29_0, html_schema_29_0 },
    { schema_28_1, html_schema_28_1 },
    { schema_28_0, html_schema_28_0 },
    { schema_27_02, html_schema_27_02 },
    { schema_27_01, html_schema_27_01 },
    { schema_27, html_schema_27 },
    { schema_26, html_schema_26 },
    { schema_25, html_schema_25 },
    { schema_24, html_schema_24 },
    { schema_23, html_schema_23 },
    { schema_22, html_schema_22 },
    { schema_21, html_schema_21 },
    { schema_20, html_schema_20 },
    { schema_19, html_schema_19 },
    { schema_18, html_schema_18 },
    { schema_17, html_schema_17 },
    { schema_16, html_schema_16 },
    { schema_15, html_schema_15 },
    { schema_14, html_schema_14 },
    { schema_13, html_schema_13 },
    { schema_12, html_schema_12 },
    { schema_11_01, html_schema_11_01 },
    { schema_11, html_schema_11 },
    { schema_10, html_schema_10 },
    { schema_9, html_schema_9 },
    { schema_8, html_schema_8 },
    { schema_7_04, html_schema_7_04 },
    { schema_7_03, html_schema_7_03 },
    { schema_7_02, html_schema_7_02 },
    { schema_7_01, html_schema_7_01 },
    { schema_7_00, html_schema_7_00 },
    { schema_6, html_schema_6 },
    { schema_5, html_schema_5 },
    { schema_4, html_schema_4 },
    { schema_3_9, html_schema_3_9 },
    { schema_3_8, html_schema_3_8 },
    { schema_3_7, html_schema_3_7 },
    { schema_3_6, html_schema_3_6 },
    { schema_3_5, html_schema_3_5 },
    { schema_3_4, html_schema_3_4 },
    { schema_3_3, html_schema_3_3 },
    { schema_3_2, html_schema_3_2 },
    { schema_3_1, html_schema_3_1 },
    { schema_3_0, html_schema_3_0 },
    { schema_2_2, html_schema_2_2 },
    { schema_2_1, html_schema_2_1 },
    { schema_2_0, html_schema_2_0 },
    { schema_1_93, html_schema_1_93 },
    { schema_1_92, html_schema_1_92 },
    { schema_1_91, html_schema_1_91 },
    { schema_1_9, html_schema_1_9 },
    { schema_1_8, html_schema_1_8 },
    { schema_1_7, html_schema_1_7 },
    { schema_1_6, html_schema_1_6 },
    { schema_1_5, html_schema_1_5 },
    { schema_1_4, html_schema_1_4 },
    { schema_1_3, html_schema_1_3 },
    { schema_1_2, html_schema_1_2 },
    { schema_1_1, html_schema_1_1 },
    { schema_1_0F, html_schema_1_0F },
    { schema_1_0E, html_schema_1_0E },
    { schema_1_0D, html_schema_1_0D },
    { schema_1_0C, html_schema_1_0C },
    { schema_1_0B, html_schema_1_0B },
    { schema_1_0A, html_schema_1_0A },
    { schema_0_99, html_schema_0_99 },
    { schema_0_98, html_schema_0_98 },
    { schema_0_97, html_schema_0_97 },
    { schema_0_96, html_schema_0_96 },
    { schema_0_95, html_schema_0_95 },
    { schema_0_94, html_schema_0_94 },
    { schema_0_93, html_schema_0_93 },
    { schema_0_91, html_schema_0_91 },
    { schema_apr12, html_schema_apr12 },
    { schema_mar12, html_schema_mar12 },
    { schema_feb12, html_schema_feb12 },
    { schema_jan12, html_schema_jan12 },
    { schema_dec11, html_schema_dec11 },
    { schema_nov11, html_schema_nov11 },
    { schema_oct11, html_schema_oct11 },
    { schema_sep11, html_schema_sep11 },
    { schema_aug11, html_schema_aug11 },
    { schema_jul11, html_schema_jul11 },
    { schema_jun11, html_schema_jun11 },
    { schema_0, html_schema_0 },
    { sd_schema, html_sd },
    { sioc_schema, html_sioc },
    { sioc_services, html_sioc_s },
    { sioc_types, html_sioc_t },
    { skos_schema, html_skos },
    { skosxl_schema, html_skosxl },
    { ssn_schema, html_ssn },
    { sosa_schema, html_sosa },
    { spl_1_0, html_dec22 },
    { spdx_2_3, html_spdx_2_3 },
    { spdx_2_2, html_spdx_2_2 },
    { spdx_2_1, html_spdx_2_1 },
    { spdx_2_0, html_spdx_2_0 },
    { spdx_1_2, html_spdx_1_2 },
    { spdx_1_1, html_spdx_1_1 },
    { spdx_1_0, html_spdx_1_0 },
    { svd_1_0, html_dec22 },
    { svdu_1_0, html_dec22 },
    { svl_1_0, html_dec22 },
    { svpr_1_0, html_dec22 },
    { svpu_1_0, html_dec22 },
    { svr_1_0, html_dec22 },
    { xmp_stdim, html_xmp },
    { xmp_stevt, html_xmp },
    { xmp_stfnt, html_xmp },
    { xmp_stjob, html_xmp },
    { xmp_stref, html_xmp },
    { xmp_stver, html_xmp },
    { taxo_schema, html_taxo },
    { tiff_schema, html_tiff },
    { time_schema, html_time },
    { data_vocabulary, html_v },
    { vann_1_1, html_vann_1_1 },
    { vann_1_0, html_vann_1_0 },
    { vcard_2014, html_vcard_2014 },
    { vcard_2010, html_vcard_2010 },
    { vcard_2006, html_vcard_2006 },
    { vcard_2001, html_vcard_2001 },
    { video_2018, html_jan18 },
    { video_2014, html_jan14 },
    { video_2012, html_jan12 },
    { void_schema, html_void },
    { wdr_schema, html_wdr },
    { wdrs_schema, html_wdrs },
    { website_2018, html_jan18 },
    { website_2014, html_jan14 },
    { website_2012, html_jan12 },
    { whatwg_schema, html_whatwg },
    { wikidata_schema, html_wikidata },
    { xhv_schema, html_xhv },
    { xml_schema, html_xml },
    { xmp_schema, html_xmp },
    { xmp_bj, html_xmp },
    { xmp_dm, html_xmp },
    { xmp_g, html_xmp },
    { xmp_gimg, html_xmp },
    { xmp_idq, html_xmp },
    { xmp_mm, html_xmp },
    { xmp_rights, html_xmp },
    { xmp_tpg, html_xmp },
    { xsd_1_1, html_xsd_1_1 },
    { xsd_1_0, html_xsd_1_0 },
    { error_schema, html_0 } };

#define DPV_X_VSV221(XXX) \
    dpv_##XXX##_2_0, dpv_##XXX##_2_1

#define DPV_X_VSV80(XXX) \
    dpv_##XXX##_0_8_0, dpv_##XXX##_0_8_1, dpv_##XXX##_0_8_2, dpv_##XXX##_0_9, dpv_##XXX##_1_0

#define DPV_X_VSV50(XXX) \
    dpv_##XXX##_0_5, dpv_##XXX##_0_6, dpv_##XXX##_0_7, DPV_X_VSV80 (XXX)

#define DPV_X_VSV40(XXX) \
    dpv_##XXX##_0_4_0, dpv_##XXX##_0_4_1, dpv_##XXX##_0_4_2, DPV_X_VSV50 (XXX)

#define DPV_X_80_PLUS(XXX) \
    DPV_X_VSV80 (XXX), DPV_X_VSV221 (XXX)

#define DPV_X_40_PLUS(XXX) \
    DPV_X_VSV40 (XXX), DPV_X_VSV221 (XXX)

vsv_t vsv = {
    adms_1_0, adms_2_0,
    article_2012, article_2014, article_2018,
    as_1_0, as_2_0,
    bfo_2020, bfo_2_0,
    bibo_schema,
    biro_schema,
    book_2012, book_2014, book_2018,
    cito_schema,
    cnt_schema,
    common_tag,
    content_schema,
    croissant_0_2, croissant_0_3, croissant_0_4, croissant_0_6, croissant_0_8,
        croissant_1_0, croissant_1_1, croissant_1_2, croissant_1_3, croissant_1_4,  croissant_1_5, croissant_1_6, croissant_1_7, croissant_1_8, croissant_1_9,
            croissant_1_10, croissant_1_11, croissant_1_12, croissant_1_13, croissant_1_14, croissant_1_15, croissant_1_16, croissant_1_17,
        croissant_1_100,
    creative_commons,
    crs2_schema,
    csvw_schema,
    daq_schema,
    data_catalogue_1, data_catalogue_2, data_catalogue_3,
    data_cube,
    data_quality,
    data_vocabulary,
    dbd_schema,
    dbo_schema,
    dbp_owl_schema,
    dbp_schema,
    dbr_schema,
    dc_1_0, dc_1_1,
    dcam,
    dcmi,
    described_by,
    disco_schema,
    doap_schema,
    dpv_0_1, dpv_0_2, dpv_0_3, dpv_0_4_0, dpv_0_4_1, dpv_0_4_2, dpv_0_5, dpv_0_6, dpv_0_7, dpv_0_8_0,
        dpv_0_8_1, dpv_0_8_2, dpv_0_9, dpv_1_0, dpv_2_0, dpv_2_1,
    DPV_X_VSV221 (ai),
    DPV_X_VSV221 (eu_aiact),
    DPV_X_VSV221 (eu_dga),
    dpv_eu_ehds_2_1,
    DPV_X_VSV221 (eu_gdpr),
    DPV_X_VSV221 (eu_nis2),
    DPV_X_VSV221 (eu_rights),
    DPV_X_VSV40 (gdpr), dpv_gdpr_0_3, dpv_gdpr_0_2, dpv_gdpr_0_1,
    DPV_X_VSV221 (just),
    DPV_X_VSV50 (legal),
    dpv_legal_at_2_1,
    dpv_legal_be_2_1,
    dpv_legal_bg_2_1,
    dpv_legal_cy_2_1,
    dpv_legal_cz_2_1,
    DPV_X_VSV221 (legal_de),
    dpv_legal_dk_2_1,
    dpv_legal_ee_2_1,
    dpv_legal_es_2_1,
    DPV_X_VSV221 (legal_eu),
    dpv_legal_fi_2_1,
    dpv_legal_fr_2_1,
    DPV_X_VSV221 (legal_gb),
    dpv_legal_gr_2_1,
    dpv_legal_hr_2_1,
    dpv_legal_hu_2_1,
    DPV_X_VSV221 (legal_ie),
    DPV_X_VSV221 (legal_in),
    dpv_legal_is_2_1,
    dpv_legal_it_2_1,
    dpv_legal_li_2_1,
    dpv_legal_lt_2_1,
    dpv_legal_lu_2_1,
    dpv_legal_lv_2_1,
    dpv_legal_mt_2_1,
    dpv_legal_nl_2_1,
    dpv_legal_no_2_1,
    dpv_legal_pl_2_1,
    dpv_legal_pt_2_1,
    dpv_legal_ro_2_1,
    dpv_legal_se_2_1,
    dpv_legal_sl_2_1,
    dpv_legal_sk_2_1,
    DPV_X_VSV221 (legal_us),
    DPV_X_VSV221 (loc),
    dpv_nace_schema,
    dpv_p7012_2_1,
    DPV_X_40_PLUS (pd),
    DPV_X_VSV80 (rights),
    DPV_X_80_PLUS (risk),
    dpv_s_edu_2_1,
    dpv_s_fin_2_1,
    dpv_s_hth_2_1,
    dpv_s_inf_2_1,
    dpv_s_law_2_1,
    dpv_s_ps_2_1,
    DPV_X_80_PLUS (tech),
    dublin_core_terms_1_0, dublin_core_terms_1_1,
    duv_schema,
    earl_schema,
    error_schema,
    event_schema,
    example_schema,
    exif_1_0, exif_1_1, exif_2_0, exif_2_1, exif_2_2, exif_2_21, exif_2_3, exif_2_31, exif_2_32, exif_3_0,
    exifex_2_21, exifex_2_3, exifex_2_31, exifex_2_32, exifex_3_0,
    fabio_schema,
    faux_schema,
    foaf_schema,
    frbr_schema,
    good_relations,
    grddl_schema,
    gs1_10, gs1_11, gs1_12, gs1_13, gs1_14, gs1_15, gs1_151,
    ical_schema,
    icaltzd_schema,
    jsonld_ontology_1_0, jsonld_ontology_1_1,
    licence_schema,
    linked_data_platform,
    locn_schema,
    media_resources,
    mf_1, mf_2, mf_all,
    music_2012, music_2014, music_2018,
    odrl_schema,
    open_graph_2010, open_graph_2012, open_graph_2014, open_graph_2018,
    org_schema,
    owl_1, owl_2,
    pam_1_3, pam_2_0, pam_3_0,
    pamp_3_0, pamp_3_1,
    pcm_3_1,
    pcmm_3_0, pcmm_3_1,
    pcv_1_0, pcv_2_0,
    pdf_schema,
    photoshop_schema,
    pim_1_0, pim_1_2, pim_2_0, pim_3_0, pim_3_1,
    pmi_3_0, pmi_3_1,
    poetry_ontology_1_0, poetry_ontology_1_1,
    prism_1_0, prism_1_1, prism_1_2, prism_1_3, prism_2_0, prism_2_1, prism_3_0, prism_3_1,
    prism_ad_3_0, prism_ad_3_1,
    prl_1_0, prl_1_2, prl_1_3, prl_2_0, prl_2_1,
    prm_3_0, prm_3_1,
    profile_2012, profile_2014, profile_2018,
    provincial,
    prs_3_1,
    psv_1_0,
    ptr_schema,
    pur_2_1, pur_3_0,
    rai_1_3, rai_1_4, rai_1_5, rai_1_6, rai_1_7, rai_1_8, rai_1_9, rai_1_10, rai_1_11, rai_1_12, rai_1_13, rai_1_14, rai_1_15, rai_1_16, rai_1_17, rai_1_100,
    rdf_1_0_schema, rdf_1_1_1_schema, rdf_1_1_2_schema, rdf_1_1_3_schema,
    rdfa_1_0_schema, rdfa_1_1_1_schema, rdfa_1_1_2_schema, rdfa_1_1_3_schema,
    rdfg_schema,
    rdfs_schema,
    review_schema,
    rif_schema,
    role_schema,
    rr_schema,
    schema_jun11, schema_jul11, schema_aug11,  schema_sep11, schema_oct11, schema_nov11, schema_dec11, schema_jan12, schema_feb12,
            schema_mar12, schema_apr12,
        schema_0_91, schema_0_93, schema_0_94, schema_0_95, schema_0_96, schema_0_97, schema_0_98, schema_0_99,
        schema_1_0A, schema_1_0B, schema_1_0C, schema_1_0D, schema_1_0E, schema_1_0F,
        schema_1_1, schema_1_2, schema_1_3, schema_1_4, schema_1_5, schema_1_6, schema_1_7, schema_1_8, schema_1_9, schema_1_91,
            schema_1_92, schema_1_93,
        schema_2_0, schema_2_1, schema_2_2, schema_3_0, schema_3_1, schema_3_2, schema_3_3, schema_3_4, schema_3_5, schema_3_6,
            schema_3_7, schema_3_8, schema_3_9,
        schema_4, schema_5, schema_6, schema_7_00, schema_7_01, schema_7_02, schema_7_03, schema_7_04, schema_8, schema_9,
        schema_10, schema_11, schema_11_01, schema_12, schema_13, schema_14, schema_15, schema_16, schema_17, schema_18, schema_19,
        schema_20, schema_21, schema_22, schema_23, schema_24, schema_25, schema_26, schema_27, schema_27_01, schema_27_02,
        schema_28_0, schema_28_1, schema_29_0, schema_29_1, schema_30_0,
    sd_schema,
    sioc_schema,
    sioc_services,
    sioc_types,
    skos_schema,
    skosxl_schema,
    sosa_schema,
    spdx_1_0, spdx_1_1, spdx_1_2, spdx_2_0, spdx_2_1, spdx_2_2, spdx_2_3,
    spl_1_0,
    ssn_schema,
    svd_1_0,
    svdu_1_0,
    svl_1_0,
    svpr_1_0,
    svpu_1_0,
    svr_1_0,
    taxo_schema,
    tiff_schema,
    time_schema,
    vann_1_0, vann_1_1,
    vcard_2001, vcard_2006, vcard_2010, vcard_2014,
    video_2012, video_2014, video_2018,
    void_schema,
    wdr_schema,
    wdrs_schema,
    web_annotation,
    website_2012, website_2014, website_2018,
    whatwg_schema,
    wikidata_schema,
    xhv_schema,
    xml_schema,
    xmp_bj,
    xmp_dm,
    xmp_g,
    xmp_gimg,
    xmp_idq,
    xmp_mm,
    xmp_rights,
    xmp_schema,
    xmp_stdim,
    xmp_stevt,
    xmp_stfnt,
    xmp_stjob,
    xmp_stref,
    xmp_stver,
    xmp_tpg,
    xsd_1_0, xsd_1_1,
    default_ontology };

typedef ::std::multimap < e_ontology, sh_t* > mss_t;
mss_t mss;
::std::array < ontology_version, s_error > va;

bool set_default_ontology_version (const e_ontology es, unsigned short mjr, unsigned short mnr)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (! is_valid_ontology_version (es, mjr, mnr, NOFLAGS, NOFLAGS)) return false;
    va.at (es) = ontology_version (es, mjr, mnr);
    return true; }

ontology_version get_default_ontology_version (const e_ontology es)
{   return corresponding_ontology_version (es, context.html_ver ()); }

ontology_version corresponding_ontology_version (const e_ontology es, const html_version& v)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (es == s_none) return default_ontology;
    if (! va.at (es).invalid ()) return va.at (es);
    PRESUME (! mss.empty (), __FILE__, __LINE__);
    for (mss_t::const_iterator i = mss.find (es); (i != mss.cend ()) && (i -> first == es); ++i)
    {   sh_t& x = *(i -> second);
        if (v >= x.html_)
            return x.ontology_; }
    return error_schema; }

template < e_ontology V > struct ontology_detail
{   static bool is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
    {   return (mjr == 1) && (mnr == 0); }
    static ::std::string ver (const unsigned short mjr, const unsigned short mnr)
    {   ::std::string res;
        res += x_dot_y (mjr, mnr);
        return res; }
    static ::std::string name (const ::std::string s, const unsigned short mjr, const unsigned short mnr)
    {   ::std::string res (s);
        res += " v";
        res += ver (mjr, mnr);
        return res; }
    static ontology_version from () noexcept { return ontology_version (V, 1, 0); }
    static int count () noexcept { return 1; }
    static bool faux () noexcept { return false; }
    static bool is_this_deprecated (const unsigned short , const unsigned short , const flags_t , const flags_t ) noexcept
    {   return false; }
    static ontology_version to () noexcept { return ontology_version (V, 1, 0); } };

template < > bool ontology_detail < s_adms > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 2) || (mjr == 1); }
template < > ontology_version ontology_detail < s_adms > :: from () noexcept { return ontology_version (s_adms, 1, 0); }
template < > int ontology_detail < s_adms > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_adms > :: to () noexcept { return ontology_version (s_adms, 2, 0); }

template < > bool ontology_detail < s_article > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_article > :: from () noexcept { return ontology_version (s_article, HTML_2012, 0); }
template < > int ontology_detail < s_article > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_article > :: to () noexcept { return ontology_version (s_article, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_as > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 2) || (mjr == 1); }
template < > ontology_version ontology_detail < s_as > :: from () noexcept { return ontology_version (s_as, 1, 0); }
template < > int ontology_detail < s_as > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_as > :: to () noexcept { return ontology_version (s_as, 2, 0); }

template < > bool ontology_detail < s_bfo > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 2) return false;
    return (mnr == 0) || (mnr == 2); }
template < > ontology_version ontology_detail < s_bfo > :: from () noexcept { return ontology_version (s_bfo, 2, 0); }
template < > int ontology_detail < s_bfo > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_bfo > :: to () noexcept { return ontology_version (s_bfo, 2, 2); }

template < > bool ontology_detail < s_bibo > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 1) && (mnr == 3); }
template < > ontology_version ontology_detail < s_bibo > :: from () noexcept { return ontology_version (s_bibo, 1, 3); }
template < > ontology_version ontology_detail < s_bibo > :: to () noexcept { return ontology_version (s_bibo, 1, 3); }

template < > bool ontology_detail < s_biro > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 1) && (mnr == 1); }
template < > ontology_version ontology_detail < s_biro > :: from () noexcept { return ontology_version (s_biro, 1, 1); }
template < > ontology_version ontology_detail < s_biro > :: to () noexcept { return ontology_version (s_biro, 1, 1); }

template < > bool ontology_detail < s_book > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_book > :: from () noexcept { return ontology_version (s_book, HTML_2012, 0); }
template < > int ontology_detail < s_book > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_book > :: to () noexcept { return ontology_version (s_book, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_cito > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 8); }
template < > ontology_version ontology_detail < s_cito > :: from () noexcept { return ontology_version (s_cito, 2, 8); }
template < > ontology_version ontology_detail < s_cito > :: to () noexcept { return ontology_version (s_cito, 2, 8); }

template < > bool ontology_detail < s_croissant > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   switch (mjr)
    {   case 0 :
            switch (mnr)
            {   case 2 :
                case 3 :
                case 4 :
                case 6 :
                case 8 :
                    return true;
                default :
                    break; }
            break;
        case 1 :
            return (mnr <= MAX_MINOR_CROISSANT_1) || (mnr == 100);
        default :
            break; }
    return false; }
template < > ontology_version ontology_detail < s_croissant > :: from () noexcept { return ontology_version (s_croissant, 0, 2); }
template < > int ontology_detail < s_croissant > :: count () noexcept { return 24; }
template < > ontology_version ontology_detail < s_croissant > :: to () noexcept { return ontology_version (s_croissant, 1, 100); }

template < > bool ontology_detail < s_dc > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_dc > :: from () noexcept { return ontology_version (s_dc, 1, 0); }
template < > int ontology_detail < s_dc > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_dc > :: to () noexcept { return ontology_version (s_dc, 1, 1); }

template < > bool ontology_detail < s_dcat > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr >= 1) && (mjr <= 3); }
template < > ontology_version ontology_detail < s_dcat > :: from () noexcept { return ontology_version (s_dcat, 1, 0); }
template < > int ontology_detail < s_dcat > :: count () noexcept { return 3; }
template < > ontology_version ontology_detail < s_dcat > :: to () noexcept { return ontology_version (s_dcat, 3, 0); }

template < > bool ontology_detail < s_dct > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_dct > :: from () noexcept { return ontology_version (s_dct, 1, 0); }
template < > int ontology_detail < s_dct > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_dct > :: to () noexcept { return ontology_version (s_dct, 1, 1); }

bool is_dpv_valid (const unsigned short mjr, const unsigned short mnr, const unsigned short mm = 10, const unsigned mxmj = 2, const unsigned mxmn = 1, const flags_t oflags = NOFLAGS) noexcept
{   switch (mjr)
    {   case 2 : if ((mxmj >= 2) && (mnr == 0)) return ((oflags & OV_DPV_NOT_4020) == 0);
                 return (mjr <= mxmj) && (mnr <= mxmn);
        case 1 : return ((mxmj >= 1) && (mnr == 0) && ((oflags & OV_DPV_NOT_4020) == 0));
        case 0 :
            if (mnr < mm) break; 
            switch (mnr)
            {   case 10 :
                case 20 :
                case 30 : return true;
                case 40 :
                case 41 :
                case 42 :
                case 50 :
                case 60 :
                case 70 :
                case 80 :
                case 81 :
                case 82 :
                case 90 : return ((oflags & OV_DPV_NOT_4020) == 0);
                default : break; }
        default : break; }
    return false; }

#define DETAIL_DPV(ONT,MM,N,MX,MN) \
    template < > bool ontology_detail < ONT > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t oflags) noexcept \
    {   return is_dpv_valid (mjr, mnr, MM, MX, MN, oflags); } \
    template < > ontology_version ontology_detail < ONT > :: from () noexcept { return ontology_version (ONT, 0, MM); } \
    template < > int ontology_detail < ONT > :: count () noexcept { return N; } \
    template < > ontology_version ontology_detail < ONT > :: to () noexcept { return ontology_version (ONT, MX, 0); }

#define DETAIL_DPV2(ONT) \
    template < > bool ontology_detail < ONT > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t oflags) noexcept \
    {   if ((mjr == 2) && (mnr == 0)) return ((oflags & OV_DPV_NOT_4020) == 0); \
        return (mjr == 2) && (mnr < 2); } \
    template < > ontology_version ontology_detail < ONT > :: from () noexcept { return ontology_version (ONT, 2, 0); } \
    template < > int ontology_detail < ONT > :: count () noexcept { return 2; } \
    template < > ontology_version ontology_detail < ONT > :: to () noexcept { return ontology_version (ONT, 2, 1); }

#define DETAIL_DPV21(ONT) \
    template < > bool ontology_detail < ONT > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept \
    {   return (mjr == 2) && (mnr == 1); } \
    template < > ontology_version ontology_detail < ONT > :: from () noexcept { return ontology_version (ONT, 2, 1); } \
    template < > int ontology_detail < ONT > :: count () noexcept { return 1; } \
    template < > ontology_version ontology_detail < ONT > :: to () noexcept { return ontology_version (ONT, 2, 1); }

DETAIL_DPV (s_dpv, 10, 16, 2, 1)
DETAIL_DPV2 (s_dpv_ai);
DETAIL_DPV2 (s_dpv_eu_aiact);
DETAIL_DPV2 (s_dpv_eu_dga);
DETAIL_DPV21 (s_dpv_eu_ehds);
DETAIL_DPV2 (s_dpv_eu_gdpr);          
DETAIL_DPV2 (s_dpv_eu_nis2);          
DETAIL_DPV2 (s_dpv_eu_rights);          
DETAIL_DPV (s_dpv_gdpr, 10, 15, 1, 1)
DETAIL_DPV2 (s_dpv_just);
DETAIL_DPV (s_dpv_legal, 50, 9, 1, 1)
DETAIL_DPV21 (s_dpv_legal_at);
DETAIL_DPV21 (s_dpv_legal_be);
DETAIL_DPV21 (s_dpv_legal_bg);
DETAIL_DPV21 (s_dpv_legal_cy);
DETAIL_DPV21 (s_dpv_legal_cz);
DETAIL_DPV2 (s_dpv_legal_de);
DETAIL_DPV21 (s_dpv_legal_dk);
DETAIL_DPV21 (s_dpv_legal_ee);
DETAIL_DPV21 (s_dpv_legal_es);
DETAIL_DPV2 (s_dpv_legal_eu);
DETAIL_DPV21 (s_dpv_legal_fi);
DETAIL_DPV21 (s_dpv_legal_fr);
DETAIL_DPV2 (s_dpv_legal_gb);
DETAIL_DPV21 (s_dpv_legal_gr);
DETAIL_DPV21 (s_dpv_legal_hr);
DETAIL_DPV21 (s_dpv_legal_hu);
DETAIL_DPV21 (s_dpv_legal_ie);
DETAIL_DPV2 (s_dpv_legal_in);
DETAIL_DPV21 (s_dpv_legal_is);
DETAIL_DPV21 (s_dpv_legal_it);
DETAIL_DPV21 (s_dpv_legal_li);
DETAIL_DPV21 (s_dpv_legal_lt);
DETAIL_DPV21 (s_dpv_legal_lu);
DETAIL_DPV21 (s_dpv_legal_lv);
DETAIL_DPV21 (s_dpv_legal_mt);
DETAIL_DPV21 (s_dpv_legal_nl);
DETAIL_DPV21 (s_dpv_legal_no);
DETAIL_DPV21 (s_dpv_legal_pl);
DETAIL_DPV21 (s_dpv_legal_pt);
DETAIL_DPV21 (s_dpv_legal_ro);
DETAIL_DPV21 (s_dpv_legal_se);
DETAIL_DPV21 (s_dpv_legal_sl);
DETAIL_DPV21 (s_dpv_legal_sk);
DETAIL_DPV21 (s_dpv_legal_us);

template < > bool ontology_detail < s_dpv_nace > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr < 2) && is_dpv_valid (mjr, mnr); }
template < > ontology_version ontology_detail < s_dpv_nace > :: from () noexcept { return ontology_version (s_dpv_nace, 0, 10); }
template < > int ontology_detail < s_dpv_nace > :: count () noexcept { return 14; }
template < > ontology_version ontology_detail < s_dpv_nace > :: to () noexcept { return ontology_version (s_dpv_nace, 1, 0); }

DETAIL_DPV2 (s_dpv_loc);          
DETAIL_DPV (s_dpv_pd, 40, 12, 2, 1)
DETAIL_DPV21 (s_dpv_p7012);
DETAIL_DPV (s_dpv_rights, 80, 5, 1, 1)
DETAIL_DPV (s_dpv_risk, 80, 6, 2, 1)
DETAIL_DPV21 (s_dpv_s_edu);
DETAIL_DPV21 (s_dpv_s_fin);
DETAIL_DPV21 (s_dpv_s_hth);
DETAIL_DPV21 (s_dpv_s_inf);
DETAIL_DPV21 (s_dpv_s_law);
DETAIL_DPV21 (s_dpv_s_ps);
DETAIL_DPV (s_dpv_tech, 80, 6, 2, 1)

template < > bool ontology_detail < s_error > :: is_this_valid (const unsigned short , const unsigned short , const flags_t , const flags_t ) noexcept
{   return false; }
template < > bool ontology_detail < s_error > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_exif > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   switch (mjr)
    {   case 1 : return (mnr < 2);
        case 2 : break;
        case 3 : return (mnr == 0);
        default : return false; }
    switch (mnr)
    {   case 0 :
        case 10 :
        case 20 :
        case 21 :
        case 30 :
        case 31 :
        case 32 : return true;
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_exif > :: from () noexcept { return ontology_version (s_exif, 1, 0); }
template < > int ontology_detail < s_exif > :: count () noexcept { return 10; }
template < > ontology_version ontology_detail < s_exif > :: to () noexcept { return ontology_version (s_exif, 3, 0); }

template < > bool ontology_detail < s_exifex > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{  switch (mjr)
    {   case 2 : break;
        case 3 : return (mnr == 0);
        default : return false; }
    switch (mnr)
    {   case 21 :
        case 30 :
        case 31 :
        case 32 : return true;
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_exifex > :: from () noexcept { return ontology_version (s_exifex, 1, 0); }
template < > int ontology_detail < s_exifex > :: count () noexcept { return 5; }
template < > ontology_version ontology_detail < s_exifex > :: to () noexcept { return ontology_version (s_exifex, 3, 0); }

template < > bool ontology_detail < s_fabio > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 1); }
template < > ontology_version ontology_detail < s_fabio > :: from () noexcept { return ontology_version (s_fabio, 2, 8); }
template < > ontology_version ontology_detail < s_fabio > :: to () noexcept { return ontology_version (s_fabio, 2, 8); }

template < > bool ontology_detail < s_faux > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_foaf > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 0) && (mnr < 100); }
template < > ontology_version ontology_detail < s_foaf > :: from () noexcept { return ontology_version (s_foaf, 0, 1); }
template < > int ontology_detail < s_foaf > :: count () noexcept { return 98; }
template < > ontology_version ontology_detail < s_foaf > :: to () noexcept { return ontology_version (s_foaf, 0, 99); }

template < > bool ontology_detail < s_gs1 > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    if (mnr == 51) return true;
    if (mnr > 5) return false;
    return true; }
template < > ontology_version ontology_detail < s_gs1 > :: from () noexcept { return ontology_version (s_gs1, 1, 0); }
template < > int ontology_detail < s_gs1 > :: count () noexcept { return 7; }
template < > bool ontology_detail < s_gs1 > :: is_this_deprecated (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return ((mjr == 1) && (mnr == 0)); }
template < > ontology_version ontology_detail < s_gs1 > :: to () noexcept { return ontology_version (s_gs1, 1, 51); }

template < > bool ontology_detail < s_jsonld > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_jsonld > :: from () noexcept { return ontology_version (s_jsonld, 1, 0); }
template < > int ontology_detail < s_jsonld > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_jsonld > :: to () noexcept { return ontology_version (s_jsonld, 1, 1); }

template < > bool ontology_detail < s_microformats > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr == 1) || (mjr == 2); }
template < > ontology_version ontology_detail < s_microformats > :: from () noexcept { return ontology_version (s_microformats, 1, 0); }
template < > int ontology_detail < s_microformats > :: count () noexcept { return 255; }
template < > ontology_version ontology_detail < s_microformats > :: to () noexcept { return ontology_version (s_microformats, 2, 255); }

template < > bool ontology_detail < s_music > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_music > :: from () noexcept { return ontology_version (s_music, HTML_2012, 0); }
template < > int ontology_detail < s_music > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_music > :: to () noexcept { return ontology_version (s_music, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_none > :: is_this_valid (const unsigned short , const unsigned short , const flags_t , const flags_t ) noexcept
{   return false; }
template < > bool ontology_detail < s_none > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_og > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2010) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_og > :: from () noexcept { return ontology_version (s_og, HTML_2010, 0); }
template < > int ontology_detail < s_og > :: count () noexcept { return 5; }
template < > ontology_version ontology_detail < s_og > :: to () noexcept { return ontology_version (s_og, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_owl > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > ontology_version ontology_detail < s_owl > :: from () noexcept { return ontology_version (s_owl, 1, 0); }
template < > int ontology_detail < s_owl > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_owl > :: to () noexcept { return ontology_version (s_owl, 2, 0); }

template < > bool ontology_detail < s_pam > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 0); }
template < > ontology_version ontology_detail < s_pam > :: from () noexcept { return ontology_version (s_pam, 2, 0); }
template < > ontology_version ontology_detail < s_pam > :: to () noexcept { return ontology_version (s_pam, 2, 0); }

template < > bool ontology_detail < s_pamp > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pamp > :: from () noexcept { return ontology_version (s_pamp, 3, 0); }
template < > int ontology_detail < s_pamp > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_pamp > :: to () noexcept { return ontology_version (s_pamp, 3, 1); }

template < > bool ontology_detail < s_pcm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr == 1); }
template < > ontology_version ontology_detail < s_pcm > :: from () noexcept { return ontology_version (s_pcm, 3, 1); }
template < > ontology_version ontology_detail < s_pcm > :: to () noexcept { return ontology_version (s_pcm, 3, 1); }

template < > bool ontology_detail < s_pcmm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pcmm > :: from () noexcept { return ontology_version (s_pcmm, 3, 0); }
template < > int ontology_detail < s_pcmm > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_pcmm > :: to () noexcept { return ontology_version (s_pcmm, 3, 1); }

template < > bool ontology_detail < s_pim > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   switch (mjr)
    {   case 1 : return mnr < 4;
        case 2 :
        case 3 : return mnr < 2;
        default : return false; } }
template < > ontology_version ontology_detail < s_pim > :: from () noexcept { return ontology_version (s_pim, 1, 0); }
template < > int ontology_detail < s_pim > :: count () noexcept { return 5; }
template < > ontology_version ontology_detail < s_pim > :: to () noexcept { return ontology_version (s_pim, 3, 1); }

template < > bool ontology_detail < s_pmi > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pmi > :: from () noexcept { return ontology_version (s_pmi, 3, 0); }
template < > int ontology_detail < s_pmi > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_pmi > :: to () noexcept { return ontology_version (s_pmi, 3, 1); }

template < > bool ontology_detail < s_poetry > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr == 0) || (mnr == 1); }
template < > ontology_version ontology_detail < s_poetry > :: from () noexcept { return ontology_version (s_poetry, 1, 0); }
template < > int ontology_detail < s_poetry > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_poetry > :: to () noexcept { return ontology_version (s_poetry, 1, 1); }

template < > bool ontology_detail < s_prism > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   switch (mjr)
    {   case 1 : return mnr < 3;
        case 2 :
        case 3 : return mnr < 2;
        default : return false; } }
template < > ontology_version ontology_detail < s_prism > :: from () noexcept { return ontology_version (s_prism, 1, 0); }
template < > int ontology_detail < s_prism > :: count () noexcept { return 8; }
template < > ontology_version ontology_detail < s_prism > :: to () noexcept { return ontology_version (s_prism, 3, 1); }

template < > bool ontology_detail < s_prism_ad > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_prism_ad > :: from () noexcept { return ontology_version (s_prism_ad, 3, 0); }
template < > int ontology_detail < s_prism_ad > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_prism_ad > :: to () noexcept { return ontology_version (s_prism_ad, 3, 1); }

template < > bool ontology_detail < s_prl > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return ((mjr == 1) && (mnr < 4)) || ((mjr == 2) && (mnr < 2)); }
template < > ontology_version ontology_detail < s_prl > :: from () noexcept { return ontology_version (s_prl, 1, 0); }
template < > int ontology_detail < s_prl > :: count () noexcept { return 5; }
template < > ontology_version ontology_detail < s_prl > :: to () noexcept { return ontology_version (s_prl, 2, 1); }

template < > bool ontology_detail < s_prm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_prm > :: from () noexcept { return ontology_version (s_prm, 3, 0); }
template < > int ontology_detail < s_prm > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_prm > :: to () noexcept { return ontology_version (s_prm, 3, 1); }

template < > bool ontology_detail < s_profile > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_profile > :: from () noexcept { return ontology_version (s_profile, HTML_2012, 0, 0); }
template < > int ontology_detail < s_profile > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_profile > :: to () noexcept { return ontology_version (s_profile, HTML_LATEST_YEAR, 0, 0); }

template < > bool ontology_detail < s_prs > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 3) && (mnr == 1); }
template < > ontology_version ontology_detail < s_prs > :: from () noexcept { return ontology_version (s_prs, 3, 1); }
template < > ontology_version ontology_detail < s_prs > :: to () noexcept { return ontology_version (s_prs, 3, 1); }

template < > bool ontology_detail < s_pur > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t) noexcept
{   return ((mjr == 2) && (mnr == 1)) || ((mjr == 3) && (mnr < 2)); }
template < > ontology_version ontology_detail < s_pur > :: from () noexcept { return ontology_version (s_pur, 2, 1); }
template < > int ontology_detail < s_pur > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_pur > :: to () noexcept { return ontology_version (s_pur, 3, 1); }

template < > bool ontology_detail < s_rai > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    if ((mnr >= 3) && (mnr <= MAX_MINOR_CROISSANT_1)) return true;
    return (mnr == 100); }
template < > ontology_version ontology_detail < s_rai > :: from () noexcept { return ontology_version (s_rai, 1, 3); }
template < > int ontology_detail < s_rai > :: count () noexcept { return 17; }
template < > ontology_version ontology_detail < s_rai > :: to () noexcept { return ontology_version (s_rai, 1, 100); }

template < > bool ontology_detail < s_rdf > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t) noexcept
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > ontology_version ontology_detail < s_rdf > :: from () noexcept { return ontology_version (s_rdf, 1, 0); }
template < > int ontology_detail < s_rdf > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_rdf > :: to () noexcept { return ontology_version (s_rdf, 1, 3); }

template < > bool ontology_detail < s_rdfa > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t) noexcept
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > ontology_version ontology_detail < s_rdfa > :: from () noexcept { return ontology_version (s_rdfa, 1, 0); }
template < > int ontology_detail < s_rdfa > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_rdfa > :: to () noexcept { return ontology_version (s_rdfa, 1, 3); }

template < > bool ontology_detail < s_schema > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t oflags) noexcept
{   if (mjr > MAX_SCHEMA_ORG_MAJOR) return false;
    switch (mjr)
    {   case 0 : return (mnr > 0);
        case 1 : return true;
        case 2 :
        case 27 : return (mnr < 3);
        case 3 : break;
        case 7 : return (mnr < 5);
        case 11 :
        case 28 :
        case 29 : return (mnr < 2);
        default : return (mnr == 0); }
    switch (mnr)
    {   case 0 : return ((oflags & SV_NOT_30) == 0);
        case 1 : return ((oflags & SV_NOT_31) == 0);
        case 2 : return ((oflags & SV_NOT_32) == 0);
        case 3 : return ((oflags & SV_NOT_33) == 0);
        case 4 : return ((oflags & SV_NOT_34) == 0);
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 : return true;
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_schema > :: from () noexcept { return ontology_version (s_schema, MIN_SCHEMA_ORG_MAJOR, MIN_SCHEMA_ORG_MINOR); }
template < > int ontology_detail < s_schema > :: count () noexcept { return 86; }
template < > ontology_version ontology_detail < s_schema > :: to () noexcept { return ontology_version (s_schema, MAX_SCHEMA_ORG_MAJOR, MAX_SCHEMA_ORG_MINOR); }
template < > ::std::string ontology_detail < s_schema > :: ver (const unsigned short mjr, const unsigned short mnr)
{   switch (mjr)
    {   case 7 :
        case 11 :
        case 27 : return x_dot_oh_y (mjr, mnr);
        default : break; }
    return x_dot_y (mjr, mnr); }
template < > ::std::string ontology_detail < s_schema > :: name (const ::std::string s, const unsigned short mjr, const unsigned short mnr)
{   ::std::string res (s);
    res += " v";
    res += ver (mjr, mnr);
    return res; }

template < > bool ontology_detail < s_spdx > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{  switch (mjr)
    {   case 1 : return ((mnr >= 0) && (mnr <= 2));
        case 2 : return ((mnr >= 0) && (mnr <= 3));
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_spdx > :: from () noexcept { return ontology_version (s_exifex, 1, 0); }
template < > int ontology_detail < s_spdx > :: count () noexcept { return 7; }
template < > ontology_version ontology_detail < s_spdx > :: to () noexcept { return ontology_version (s_exifex, 2, 3); }

template < > bool ontology_detail < s_tiff > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   return (mjr == 6) && (mnr == 0); }
template < > ontology_version ontology_detail < s_tiff > :: from () noexcept { return ontology_version (s_tiff, 6, 0); }
template < > ontology_version ontology_detail < s_tiff > :: to () noexcept { return ontology_version (s_tiff, 6, 0); }

template < > bool ontology_detail < s_vann > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_vann > :: from () noexcept { return ontology_version (s_vann, 1, 0); }
template < > int ontology_detail < s_vann > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_vann > :: to () noexcept { return ontology_version (s_vann, 1, 1); }

template < > bool ontology_detail < s_vcard > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t f) noexcept
{   if (mnr != 0) return false;
    switch (mjr)
    {   case 1 :
        case 3 :
        case 4 : return true;
        case 2 : return (f & SV_VC_NOT2) == 0;
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_vcard > :: from () noexcept { return vcard_2001; }
template < > int ontology_detail < s_vcard > :: count () noexcept { return 4; }
template < > bool ontology_detail < s_vcard > :: is_this_deprecated (const unsigned short mjr, const unsigned short , const flags_t , const flags_t oflags) noexcept
    {   if ((oflags & SV_DEPRECATED) == SV_DEPRECATED) return true;
        return ((mjr == 4) && ((oflags & SV_VC_DEP4) == SV_VC_DEP4)); }
template < > ontology_version ontology_detail < s_vcard > :: to () noexcept { return vcard_2014; }

template < > bool ontology_detail < s_video > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_video > :: from () noexcept { return ontology_version (s_video, HTML_2012, 0, 0); }
template < > int ontology_detail < s_video > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_video > :: to () noexcept { return ontology_version (s_video, HTML_LATEST_YEAR, 0, 0); }

template < > bool ontology_detail < s_website > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_website > :: from () noexcept { return ontology_version (s_website, HTML_2012, 0, 0); }
template < > int ontology_detail < s_website > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_website > :: to () noexcept { return ontology_version (s_website, HTML_LATEST_YEAR, 0, 0); }

template < > bool ontology_detail < s_xsd > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t , const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_xsd > :: from () noexcept { return ontology_version (s_xsd, 1, 0, 0); }
template < > int ontology_detail < s_xsd > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_xsd > :: to () noexcept { return ontology_version (s_xsd, 1, 1, 0); }

template < e_ontology V, e_ontology... Vs > struct schemas : schemas < Vs... >
{   static ontology_version get_corresponding (const e_ontology es, const html_version& v)
    {   if (es == V) return corresponding_ontology_version (es, v);
        return schemas < Vs... > :: get_corresponding (es, v); }
    static ontology_version get_default (const e_ontology es)
    {   return get_corresponding (es, context.html_ver ()); }
    static ::std::string name (const e_ontology es)
    {   if (es == V) return ontology_names.get (V, ONTOLOGY_NAME);
        return schemas < Vs... > :: name (es); }
    static ::std::string name (const e_ontology es, const unsigned short mjr, const unsigned short mnr)
    {   if (es == V) return ontology_detail < V >::name (name (es), mjr, mnr);
        return schemas < Vs... > :: name (es, mjr, mnr); }
    static ::std::string ver (const e_ontology es, const unsigned short mjr, const unsigned short mnr)
    {   if (es == V) return ontology_detail < V >::ver (mjr, mnr);
        return schemas < Vs... > :: ver (es, mjr, mnr); }
    static ontology_version from (const e_ontology es) noexcept
    {   if (es == V) return ontology_detail < V > :: from ();
        return schemas < Vs... > :: from (es); }
    static ontology_version to (const e_ontology es) noexcept
    {   if (es == V) return ontology_detail < V > :: to ();
        return schemas < Vs... > :: to (es); }
    static int count (const e_ontology es) noexcept
    {   if (es == V) return ontology_detail < V > :: count ();
        return schemas < Vs... > :: count (es); }
    static bool faux (const e_ontology es) noexcept
    {   if (es == V) return ontology_detail < V > :: faux ();
        return schemas < Vs... > :: faux (es); }
    static bool is_this_deprecated (const e_ontology es, const unsigned short mjr, const unsigned short mnr, const flags_t flags, const flags_t oflags) noexcept
    {   if (es == V) return ontology_detail < V > :: is_this_deprecated (mjr, mnr, flags, oflags);
        return schemas < Vs... > :: is_this_deprecated (es, mjr, mnr, flags, oflags); }
    static bool is_valid (const e_ontology es, const unsigned short mjr, const unsigned short mnr, const flags_t flags, const flags_t oflags) noexcept
    {   if (es == V) return ontology_detail < V > :: is_this_valid (mjr, mnr, flags, oflags);
        return schemas < Vs... > :: is_valid (es, mjr, mnr, flags, oflags); } };

template < > struct schemas < s_error >
{   static ontology_version get_corresponding (const e_ontology , const html_version& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_ontology); }
    static ontology_version get_default (const e_ontology )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_ontology); }
    static ::std::string ver (const e_ontology , const unsigned short , const unsigned short )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return "*** NO SUCH SCHEMA "); }
    static ::std::string name (const e_ontology , const unsigned short , const unsigned short )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return "*** NO SUCH SCHEMA "); }
    static ::std::string name (const e_ontology )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return "*** NO SUCH SCHEMA "); }
    static ontology_version from (const e_ontology ) noexcept
    {   return error_schema; }
    static ontology_version to (const e_ontology ) noexcept
    {   return error_schema; }
    static int count (const e_ontology ) noexcept
    {   return 0; }
    static bool faux (const e_ontology ) noexcept
    {   return true; }
    static bool is_this_deprecated (const e_ontology , const unsigned short , const unsigned short , const flags_t , const flags_t ) noexcept
    {   return false; }
    static bool is_valid (const e_ontology , const unsigned short , const unsigned short , const flags_t , const flags_t ) noexcept
    {   return false; } };

ontology_version get_first_ontology_version (const e_ontology es) noexcept
{   return schemas < ONTOLOGIES > :: from (es); }
ontology_version get_last_ontology_version (const e_ontology es) noexcept
{   return schemas < ONTOLOGIES > :: to (es); }
int get_ontology_version_count (const e_ontology es) noexcept
{   return schemas < ONTOLOGIES > :: count (es); }
bool is_faux_schema (const e_ontology es) noexcept
{   return schemas < ONTOLOGIES > :: faux (es); }

ontology_version::ontology_version (const html_version& v)
{   ontology_version sv = corresponding_ontology_version (s_schema, v);
    ontology_version err (s_error, 0, 0);
    if (! sv.invalid ()) swap (sv); else swap (err); }

void ontology_version::init (nitpick& DEBUGONLY (nits))
{   PRESUME (mss.empty (), __FILE__, __LINE__);
    for (int i = 0; GSL_AT (sh, i).ontology_.root () != s_error; ++i)
        mss.insert (mss_t::value_type (GSL_AT (sh, i).ontology_.root (), &GSL_AT (sh, i)));
#ifdef _DEBUG
    for (int i = 1; i < s_error; ++i)
        if (mss.find (static_cast < e_ontology > (i)) == mss.cend ())
            nits.pick ( nit_missing_ontology, es_catastrophic, ec_schema,
                        "Corresponding HTML version for ontology ", i, " missing");
#endif
    for (int i = 0; i < s_error; ++i) GSL_AT (va, i) = error_schema; }

::std::string ontology_version::name (const e_ontology es)
{   if (is_faux_schema (es)) return "";
    return ontology_names.get (es, ONTOLOGY_NAME); }

::std::string ontology_version::name () const
{   return name (root ()); }

::std::string ontology_version::report () const
{   switch (root ())
    {   case s_none : return "(UNKNOWN SCHEMA)";
        case s_error : return "*** ERROR ***";
        default : break; }
    return schemas < ONTOLOGIES > :: name (root (), mjr (), mnr ()); }

::std::string ontology_version::ver () const
{   if (root () == s_none) return "0.0";
    return schemas < ONTOLOGIES > :: ver (root (), mjr (), mnr ()); }

bool overlap (const ontology_version& lhs_from, const ontology_version& lhs_to, const ontology_version& rhs_from, const ontology_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_ontology_version (const e_ontology root, const unsigned short j, const unsigned short n, const flags_t flags, const flags_t oflags) noexcept
{   return schemas < ONTOLOGIES > :: is_valid (root, j, n, flags, oflags); }

bool is_valid_ontology_version (const ontology_version& sv) noexcept
{   return schemas < ONTOLOGIES > :: is_valid (sv.root (), sv.mjr (), sv.mnr (), sv.flags (), sv.oflags ()); }

bool is_ontology_deprecated (const e_ontology root, const unsigned short mjr, const unsigned short mnr, const flags_t flags, const flags_t oflags) noexcept
{   return schemas < ONTOLOGIES > :: is_this_deprecated (root, mjr, mnr, flags, oflags); }

bool does_ontology_apply (const ontology_version& v, const ontology_version& from, const ontology_version& to) MSVC_NOEXCEPT
{   if (v.any_oflags (SV_WILDCARD)) return true;
    if (v.root () != from.root ()) return true;
    switch (v.root ())
    {   case s_faux :
        case s_example :
            return true;
        case s_none :
            return false;
        default :
            break; }
    return does_apply < version > (v, from, to); }
