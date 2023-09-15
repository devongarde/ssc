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
#include "main/context.h"
#include "ontology/ontology_version.h"
#include "parser/html_version.h"
#include "symbol/nstr.h"
#include "utility/common.h"

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
    { content_schema, html_rdf_1_0 },
    { creative_commons, html_cc },
    { crs2_schema, html_xmp },
    { csvw_schema, html_jan16 },
    { common_tag, html_rdf_1_0_con },
    { daq_schema, html_rdf_1_0_con },
    { dbd_schema, html_rdf_1_0_con },
    { dbo_schema, html_rdf_1_0_con },
    { dbp_schema, html_rdf_1_0_con },
    { dbp_owl_schema, html_rdf_1_0_con },
    { dbr_schema, html_rdf_1_0_con },
    { dc_1_1, html_dc_1_1 },
    { dc_1_0, html_dc_1_0 },
    { dcam, html_rdf_1_0_con },
    { data_catalogue_1, html_rdf_1_0 },
    { data_catalogue_2, html_rdf_1_0_con },
    { dcmi, html_rdf_1_0_con },
    { dublin_core_terms_1_1, html_dcterms_1_1 },
    { dublin_core_terms_1_0, html_dcterms_1_0 },
    { disco_schema, html_rdf_1_0_con },
    { doap_schema, html_rdf_1_0 },
    { data_quality, html_rdf_1_0_con },
    { described_by, html_rdf_1_0 },
    { duv_schema, html_rdf_1_0_con },
    { earl_schema, html_rdf_1_0_con },
    { event_schema, html_rdf_1_0_con },
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
    { pcm_3_1, html_prism_3_1 },
    { pcmm_3_0, html_prism_3_0 },
    { pcv_1_0, html_prism_1_0 },
    { pdf_schema, html_xmp },
    { photoshop_schema, html_xmp },
    { pim_3_0, html_prism_3_0 },
    { pim_2_0, html_prism_2_0 },
    { pim_1_2, html_prism_1_2 },
    { pim_1_0, html_prism_1_0 },
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
    { prism_ad_3_0, html_prism_3_0 },
    { prl_2_0, html_prism_2_0 },
    { prl_1_0, html_prism_1_0 },
    { prm_3_0, html_prism_3_0 },
    { prs_3_1, html_prism_3_1 },
    { profile_2014, html_jan14 },
    { profile_2012, html_jan12 },
    { provincial, html_rdf_1_0_con },
    { psv_1_0, html_prism_1_0 },
    { ptr_schema, html_rdf_1_0_con },
    { pur_3_0, html_prism_3_0 },
    { pur_2_1, html_prism_2_1 },
    { data_cube, html_rdf_1_0_con },
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

typedef ::std::multimap < e_ontology, sh_t* > mss_t;
mss_t mss;
::std::array < ontology_version, s_error > va;

bool set_default_ontology_version (const e_ontology es, unsigned short mjr, unsigned short mnr)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (! is_valid_ontology_version (es, mjr, mnr, NOFLAGS)) return false;
    va.at (es) = ontology_version (es, mjr, mnr);
    return true; }

ontology_version get_default_ontology_version (const e_ontology es)
{   return corresponding_ontology_version (es, context.html_ver ()); }

ontology_version corresponding_ontology_version (const e_ontology es, const html_version& v)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (es == s_none) return default_schema;
    if (! va.at (es).invalid ()) return va.at (es);
    PRESUME (! mss.empty (), __FILE__, __LINE__);
    for (mss_t::const_iterator i = mss.find (es); (i != mss.cend ()) && (i -> first == es); ++i)
    {   sh_t& x = *(i -> second);
        if (v >= x.html_)
            return x.ontology_; }
    return error_schema; }

template < e_ontology V > struct ontology_detail
{   static bool is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
    {   return (mjr == 1) && (mnr == 0); }
    static ::std::string name (const ::std::string s, const unsigned short mjr, const unsigned short mnr)
    {   ::std::string res (s);
        res += " v";
        res += x_dot_y (mjr, mnr);
        return res; }
    static ontology_version from () noexcept { return ontology_version (V, 1, 0); }
    static int count () noexcept { return 1; }
    static bool faux () noexcept { return false; }
    static bool is_this_deprecated (const unsigned short , const unsigned short , const flags_t ) noexcept
    {   return false; }
    static ontology_version to () noexcept { return ontology_version (V, 1, 0); } };

template < > bool ontology_detail < s_adms > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 2) || (mjr == 1); }
template < > ontology_version ontology_detail < s_adms > :: from () noexcept { return ontology_version (s_adms, 1, 0); }
template < > int ontology_detail < s_adms > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_adms > :: to () noexcept { return ontology_version (s_adms, 2, 0); }

template < > bool ontology_detail < s_article > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_article > :: from () noexcept { return ontology_version (s_article, HTML_2012, 0); }
template < > int ontology_detail < s_article > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_article > :: to () noexcept { return ontology_version (s_article, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_as > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 2) || (mjr == 1); }
template < > ontology_version ontology_detail < s_as > :: from () noexcept { return ontology_version (s_as, 1, 0); }
template < > int ontology_detail < s_as > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_as > :: to () noexcept { return ontology_version (s_as, 2, 0); }

template < > bool ontology_detail < s_bfo > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 2) return false;
    return (mnr == 0) || (mnr == 2); }
template < > ontology_version ontology_detail < s_bfo > :: from () noexcept { return ontology_version (s_bfo, 2, 0); }
template < > int ontology_detail < s_bfo > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_bfo > :: to () noexcept { return ontology_version (s_bfo, 2, 2); }

template < > bool ontology_detail < s_bibo > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 1) && (mnr == 3); }
template < > ontology_version ontology_detail < s_bibo > :: from () noexcept { return ontology_version (s_bibo, 1, 3); }
template < > ontology_version ontology_detail < s_bibo > :: to () noexcept { return ontology_version (s_bibo, 1, 3); }

template < > bool ontology_detail < s_biro > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 1) && (mnr == 1); }
template < > ontology_version ontology_detail < s_biro > :: from () noexcept { return ontology_version (s_biro, 1, 1); }
template < > ontology_version ontology_detail < s_biro > :: to () noexcept { return ontology_version (s_biro, 1, 1); }

template < > bool ontology_detail < s_book > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_book > :: from () noexcept { return ontology_version (s_book, HTML_2012, 0); }
template < > int ontology_detail < s_book > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_book > :: to () noexcept { return ontology_version (s_book, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_cito > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 8); }
template < > ontology_version ontology_detail < s_cito > :: from () noexcept { return ontology_version (s_cito, 2, 8); }
template < > ontology_version ontology_detail < s_cito > :: to () noexcept { return ontology_version (s_cito, 2, 8); }

template < > bool ontology_detail < s_dc > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_dc > :: from () noexcept { return ontology_version (s_dc, 1, 0); }
template < > int ontology_detail < s_dc > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_dc > :: to () noexcept { return ontology_version (s_dc, 1, 1); }

template < > bool ontology_detail < s_dcat > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > ontology_version ontology_detail < s_dcat > :: from () noexcept { return ontology_version (s_dcat, 1, 0); }
template < > int ontology_detail < s_dcat > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_dcat > :: to () noexcept { return ontology_version (s_dcat, 2, 0); }

template < > bool ontology_detail < s_dct > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_dct > :: from () noexcept { return ontology_version (s_dct, 1, 0); }
template < > int ontology_detail < s_dct > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_dct > :: to () noexcept { return ontology_version (s_dct, 1, 1); }

template < > bool ontology_detail < s_error > :: is_this_valid (const unsigned short , const unsigned short , const flags_t ) noexcept
{   return false; }
template < > bool ontology_detail < s_error > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_exif > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr > MAX_SCHEMA_ORG_MAJOR) return false;
    switch (mjr)
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

template < > bool ontology_detail < s_exifex > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr > MAX_SCHEMA_ORG_MAJOR) return false;
    switch (mjr)
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

template < > bool ontology_detail < s_fabio > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 1); }
template < > ontology_version ontology_detail < s_fabio > :: from () noexcept { return ontology_version (s_fabio, 2, 8); }
template < > ontology_version ontology_detail < s_fabio > :: to () noexcept { return ontology_version (s_fabio, 2, 8); }

template < > bool ontology_detail < s_faux > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_foaf > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 0) && (mnr < 100); }
template < > ontology_version ontology_detail < s_foaf > :: from () noexcept { return ontology_version (s_foaf, 0, 1); }
template < > int ontology_detail < s_foaf > :: count () noexcept { return 98; }
template < > ontology_version ontology_detail < s_foaf > :: to () noexcept { return ontology_version (s_foaf, 0, 99); }

template < > bool ontology_detail < s_gs1 > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    if (mnr == 51) return true;
    if (mnr > 5) return false;
    return true; }
template < > ontology_version ontology_detail < s_gs1 > :: from () noexcept { return ontology_version (s_gs1, 1, 0); }
template < > int ontology_detail < s_gs1 > :: count () noexcept { return 7; }
template < > bool ontology_detail < s_gs1 > :: is_this_deprecated (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return ((mjr == 1) && (mnr == 0)); }
template < > ontology_version ontology_detail < s_gs1 > :: to () noexcept { return ontology_version (s_gs1, 1, 51); }

template < > bool ontology_detail < s_jsonld > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_jsonld > :: from () noexcept { return ontology_version (s_jsonld, 1, 0); }
template < > int ontology_detail < s_jsonld > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_jsonld > :: to () noexcept { return ontology_version (s_jsonld, 1, 1); }

template < > bool ontology_detail < s_microformats > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr == 1) || (mjr == 2); }
template < > ontology_version ontology_detail < s_microformats > :: from () noexcept { return ontology_version (s_microformats, 1, 0); }
template < > int ontology_detail < s_microformats > :: count () noexcept { return 255; }
template < > ontology_version ontology_detail < s_microformats > :: to () noexcept { return ontology_version (s_microformats, 2, 255); }

template < > bool ontology_detail < s_music > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_music > :: from () noexcept { return ontology_version (s_music, HTML_2012, 0); }
template < > int ontology_detail < s_music > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_music > :: to () noexcept { return ontology_version (s_music, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_none > :: is_this_valid (const unsigned short , const unsigned short , const flags_t ) noexcept
{   return false; }
template < > bool ontology_detail < s_none > :: faux () noexcept
{   return true; }

template < > bool ontology_detail < s_og > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2010) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_og > :: from () noexcept { return ontology_version (s_og, HTML_2010, 0); }
template < > int ontology_detail < s_og > :: count () noexcept { return 5; }
template < > ontology_version ontology_detail < s_og > :: to () noexcept { return ontology_version (s_og, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_owl > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > ontology_version ontology_detail < s_owl > :: from () noexcept { return ontology_version (s_owl, 1, 0); }
template < > int ontology_detail < s_owl > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_owl > :: to () noexcept { return ontology_version (s_owl, 2, 0); }

template < > bool ontology_detail < s_pam > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 2) && (mnr == 0); }
template < > ontology_version ontology_detail < s_pam > :: from () noexcept { return ontology_version (s_pam, 2, 0); }
template < > ontology_version ontology_detail < s_pam > :: to () noexcept { return ontology_version (s_pam, 2, 0); }

template < > bool ontology_detail < s_pamp > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pamp > :: from () noexcept { return ontology_version (s_pamp, 3, 0); }
template < > ontology_version ontology_detail < s_pamp > :: to () noexcept { return ontology_version (s_pamp, 3, 1); }

template < > bool ontology_detail < s_pcm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr == 1); }
template < > ontology_version ontology_detail < s_pcm > :: from () noexcept { return ontology_version (s_pcm, 3, 1); }
template < > ontology_version ontology_detail < s_pcm > :: to () noexcept { return ontology_version (s_pcm, 3, 1); }

template < > bool ontology_detail < s_pcmm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pcmm > :: from () noexcept { return ontology_version (s_pcmm, 3, 0); }
template < > ontology_version ontology_detail < s_pcmm > :: to () noexcept { return ontology_version (s_pcmm, 3, 1); }

template < > bool ontology_detail < s_pim > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   switch (mjr)
    {   case 1 : return mnr < 4;
        case 2 :
        case 3 : return mnr < 2;
        default : return false; } }
template < > ontology_version ontology_detail < s_pim > :: from () noexcept { return ontology_version (s_pim, 1, 0); }
template < > ontology_version ontology_detail < s_pim > :: to () noexcept { return ontology_version (s_pim, 3, 1); }

template < > bool ontology_detail < s_pmi > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_pmi > :: from () noexcept { return ontology_version (s_pmi, 3, 0); }
template < > ontology_version ontology_detail < s_pmi > :: to () noexcept { return ontology_version (s_pmi, 3, 1); }

template < > bool ontology_detail < s_poetry > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr == 0) || (mnr == 1); }
template < > ontology_version ontology_detail < s_poetry > :: from () noexcept { return ontology_version (s_poetry, 1, 0); }
template < > int ontology_detail < s_poetry > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_poetry > :: to () noexcept { return ontology_version (s_poetry, 1, 1); }

template < > bool ontology_detail < s_prism > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   switch (mjr)
    {   case 1 : return mnr < 3;
        case 2 :
        case 3 : return mnr < 2;
        default : return false; } }
template < > ontology_version ontology_detail < s_prism > :: from () noexcept { return ontology_version (s_prism, 1, 0); }
template < > ontology_version ontology_detail < s_prism > :: to () noexcept { return ontology_version (s_prism, 3, 1); }

template < > bool ontology_detail < s_prism_ad > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_prism_ad > :: from () noexcept { return ontology_version (s_prism_ad, 3, 0); }
template < > ontology_version ontology_detail < s_prism_ad > :: to () noexcept { return ontology_version (s_prism_ad, 3, 1); }

template < > bool ontology_detail < s_prl > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return ((mjr == 1) && (mnr < 4)) || ((mjr == 2) && (mnr < 2)); }
template < > ontology_version ontology_detail < s_prl > :: from () noexcept { return ontology_version (s_prl, 1, 0); }
template < > ontology_version ontology_detail < s_prl > :: to () noexcept { return ontology_version (s_prl, 2, 1); }

template < > bool ontology_detail < s_prm > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr < 2); }
template < > ontology_version ontology_detail < s_prm > :: from () noexcept { return ontology_version (s_prm, 3, 0); }
template < > ontology_version ontology_detail < s_prm > :: to () noexcept { return ontology_version (s_prm, 3, 1); }

template < > bool ontology_detail < s_profile > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_profile > :: from () noexcept { return ontology_version (s_profile, HTML_2012, 0); }
template < > int ontology_detail < s_profile > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_profile > :: to () noexcept { return ontology_version (s_profile, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_prs > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 3) && (mnr == 1); }
template < > ontology_version ontology_detail < s_prs > :: from () noexcept { return ontology_version (s_prs, 3, 1); }
template < > ontology_version ontology_detail < s_prs > :: to () noexcept { return ontology_version (s_prs, 3, 1); }

template < > bool ontology_detail < s_pur > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return ((mjr == 2) && (mnr == 1)) || ((mjr == 3) && (mnr < 2)); }
template < > ontology_version ontology_detail < s_pur > :: from () noexcept { return ontology_version (s_pur, 2, 1); }
template < > ontology_version ontology_detail < s_pur > :: to () noexcept { return ontology_version (s_pur, 3, 1); }

template < > bool ontology_detail < s_rdf > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > ontology_version ontology_detail < s_rdf > :: from () noexcept { return ontology_version (s_rdf, 1, 0); }
template < > int ontology_detail < s_rdf > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_rdf > :: to () noexcept { return ontology_version (s_rdf, 1, 3); }

template < > bool ontology_detail < s_rdfa > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > ontology_version ontology_detail < s_rdfa > :: from () noexcept { return ontology_version (s_rdfa, 1, 0); }
template < > int ontology_detail < s_rdfa > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_rdfa > :: to () noexcept { return ontology_version (s_rdfa, 1, 3); }

template < > bool ontology_detail < s_schema > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept
{   if (mjr > MAX_SCHEMA_ORG_MAJOR) return false;
    switch (mjr)
    {   case 0 : return (mnr > 0);
        case 1 : return true;
        case 2 : return (mnr < 3);
        case 3 : break;
        case 7 : return (mnr < 5);
        default : return (mnr == 0); }
    switch (mnr)
    {   case 0 : return ((flags & SV_NOT_30) == 0);
        case 1 : return ((flags & SV_NOT_31) == 0);
        case 2 : return ((flags & SV_NOT_32) == 0);
        case 3 : return ((flags & SV_NOT_33) == 0);
        case 4 : return ((flags & SV_NOT_34) == 0);
        case 5 :
        case 6 :
        case 7 :
        case 8 :
        case 9 : return true;
        default : break; }
    return false; }
template < > ontology_version ontology_detail < s_schema > :: from () noexcept { return ontology_version (s_schema, MIN_SCHEMA_ORG_MAJOR, MIN_SCHEMA_ORG_MINOR); }
template < > int ontology_detail < s_schema > :: count () noexcept { return 73; }
template < > ontology_version ontology_detail < s_schema > :: to () noexcept { return ontology_version (s_schema, MAX_SCHEMA_ORG_MAJOR, MAX_SCHEMA_ORG_MINOR); }

template < > bool ontology_detail < s_tiff > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   return (mjr == 6) && (mnr == 0); }
template < > ontology_version ontology_detail < s_tiff > :: from () noexcept { return ontology_version (s_tiff, 6, 0); }
template < > ontology_version ontology_detail < s_tiff > :: to () noexcept { return ontology_version (s_tiff, 6, 0); }

template < > bool ontology_detail < s_vann > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_vann > :: from () noexcept { return ontology_version (s_vann, 1, 0); }
template < > int ontology_detail < s_vann > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_vann > :: to () noexcept { return ontology_version (s_vann, 1, 1); }

template < > bool ontology_detail < s_vcard > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t f) noexcept
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
template < > bool ontology_detail < s_vcard > :: is_this_deprecated (const unsigned short mjr, const unsigned short , const flags_t flags) noexcept
    {   if ((flags & SV_DEPRECATED) == SV_DEPRECATED) return true;
        return ((mjr == 4) && ((flags & SV_VC_DEP4) == SV_VC_DEP4)); }
template < > ontology_version ontology_detail < s_vcard > :: to () noexcept { return vcard_2014; }

template < > bool ontology_detail < s_video > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_video > :: from () noexcept { return ontology_version (s_video, HTML_2012, 0); }
template < > int ontology_detail < s_video > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_video > :: to () noexcept { return ontology_version (s_video, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_website > :: is_this_valid (const unsigned short mjr, const unsigned short , const flags_t ) noexcept
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > ontology_version ontology_detail < s_website > :: from () noexcept { return ontology_version (s_website, HTML_2012, 0); }
template < > int ontology_detail < s_website > :: count () noexcept { return 4; }
template < > ontology_version ontology_detail < s_website > :: to () noexcept { return ontology_version (s_website, HTML_LATEST_YEAR, 0); }

template < > bool ontology_detail < s_xsd > :: is_this_valid (const unsigned short mjr, const unsigned short mnr, const flags_t ) noexcept
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > ontology_version ontology_detail < s_xsd > :: from () noexcept { return ontology_version (s_xsd, 1, 0); }
template < > int ontology_detail < s_xsd > :: count () noexcept { return 2; }
template < > ontology_version ontology_detail < s_xsd > :: to () noexcept { return ontology_version (s_xsd, 1, 1); }

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
    static bool is_this_deprecated (const e_ontology es, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept
    {   if (es == V) return ontology_detail < V > :: is_this_deprecated (mjr, mnr, flags);
        return schemas < Vs... > :: is_this_deprecated (es, mjr, mnr, flags); }
    static bool is_valid (const e_ontology es, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept
    {   if (es == V) return ontology_detail < V > :: is_this_valid (mjr, mnr, flags);
        return schemas < Vs... > :: is_valid (es, mjr, mnr, flags); } };

template < > struct schemas < s_error >
{   static ontology_version get_corresponding (const e_ontology , const html_version& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_schema); }
    static ontology_version get_default (const e_ontology )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_schema); }
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
    static bool is_this_deprecated (const e_ontology , const unsigned short , const unsigned short , const flags_t ) noexcept
    {   return false; }
    static bool is_valid (const e_ontology , const unsigned short , const unsigned short , const flags_t ) noexcept
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
            nits.pick (nit_missing_ontology, es_catastrophic, ec_schema, "Corresponding HTML version for schema ", i, " missing");
#endif
    for (int i = 0; i < s_error; ++i) GSL_AT (va, i) = error_schema; }

::std::string ontology_version::name (const e_ontology es)
{   if (is_faux_schema (es)) return "";
    return ontology_names.get (es, ONTOLOGY_NAME); }

::std::string ontology_version::name () const
{   return name (root ()); }

::std::string ontology_version::report () const
{   if (root () == s_none) return "(UNKNOWN SCHEMA)";
    return schemas < ONTOLOGIES > :: name (root (), mjr (), mnr ()); }

::std::string ontology_version::ver () const
{   if (root () == s_none) return "0.0";
    return x_dot_y_ish (mjr (), mnr ()); }

bool overlap (const ontology_version& lhs_from, const ontology_version& lhs_to, const ontology_version& rhs_from, const ontology_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_ontology_version (const e_ontology root, const unsigned short j, const unsigned short n, const flags_t flags) noexcept
{   return schemas < ONTOLOGIES > :: is_valid (root, j, n, flags); }

bool is_valid_ontology_version (const ontology_version& sv) noexcept
{   return schemas < ONTOLOGIES > :: is_valid (sv.root (), sv.mjr (), sv.mnr (), sv.flags ()); }

bool is_ontology_deprecated (const e_ontology root, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept
{   return schemas < ONTOLOGIES > :: is_this_deprecated (root, mjr, mnr, flags); }

bool does_ontology_apply (const ontology_version& v, const ontology_version& from, const ontology_version& to) MSVC_NOEXCEPT
{   if (v.any_flags (SV_WILDCARD)) return true;
    if (v.root () != from.root ()) return true;
    return does_apply < version > (v, from, to); }
