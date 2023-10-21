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
#include "main/version.h"

#define SV_NOT_30       0x00000001
#define SV_NOT_31       0x00000002
#define SV_NOT_32       0x00000004
#define SV_NOT_33       0x00000008
#define SV_NOT_34       0x00000010
#define SV_NOT_3034     0x0000001F
#define SV_NOT_3134     0x0000001E

#define SV_DEP20        0x00010000
#define SV_DEP21        0x00020000
#define SV_DEP30        0x00040000
#define SV_DEP31        0x00080000
#define SV_DEP32        0x00100000
#define SV_DEP33        0x00200000
#define SV_DEP34        0x00400000
#define SV_DEPRECATED   0x00800000

#define SV_WILDCARD     0x80000000

#define SV_DEP_3034     ( SV_DEP30 | SV_DEP31 | SV_DEP32 | SV_DEP33 | SV_DEP34 )
#define SV_FLAG_MASK    0xFFFFFFFF
#define SV_ROOT_SHIFT   32

#define SV_VC_NOT2      0x00000100
#define SV_VC_DEP4      0x00000400

#define MAX_SCHEMA_ORG_MAJOR 23
#define MAX_SCHEMA_ORG_MINOR 0
#define MIN_SCHEMA_ORG_MAJOR 0
#define MIN_SCHEMA_ORG_MINOR 10
#define DEFAULT_SCHEMA_ORG_MAJOR 22
#define DEFAULT_SCHEMA_ORG_MINOR 0
#define DEFAULT_SCHEMA_ORG_VERSION "23.0"

class html_version;
struct ontology_version;
typedef ::std::set < e_ontology > vsh_t;

ontology_version corresponding_ontology_version (const e_ontology es, const html_version& v);
bool set_default_ontology_version (const e_ontology es, unsigned short mjr, unsigned short mnr);
ontology_version get_default_ontology_version (const e_ontology es);
ontology_version get_first_ontology_version (const e_ontology es) noexcept;
ontology_version get_last_ontology_version (const e_ontology es) noexcept;
int get_ontology_version_count (const e_ontology es) noexcept;
bool is_faux_schema (const e_ontology es) noexcept;
bool is_valid_ontology_version (const e_ontology root, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept;
bool is_ontology_deprecated (const e_ontology root, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept;

struct ontology_version : public version
{   DEFAULT_CONSTRUCTORS (ontology_version);
    ontology_version (const unsigned short mjr, const unsigned short mnr, const flags_t sf = NOFLAGS) noexcept
        :   version (mjr, mnr, (static_cast < flags_t > (s_schema) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    { }
    ontology_version (const e_ontology root, const unsigned short mjr, const unsigned short mnr, const flags_t sf = NOFLAGS) noexcept
        :   version (mjr, mnr, (static_cast < flags_t > (root) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    { }
    ontology_version (const html_version& v);
    static void init (nitpick& nits);
    void reset () noexcept
    {   ontology_version v; swap (v); }
    void reset (const ontology_version& v) noexcept
    {   ontology_version vv (v); swap (vv); }
    bool deprecated () const noexcept
    {   if ((flags () & SV_DEPRECATED) == SV_DEPRECATED) return true;
        return is_ontology_deprecated (root (), mjr (), mnr (), flags ()); }
    bool is_not (const unsigned short mj, const unsigned short mn = USHRT_MAX) const noexcept
    {   if (unknown ()) return false;
        if (mj != mjr ()) return true;
        return ((mn != USHRT_MAX) && (mn != mnr ())); }
    bool is_not (const ontology_version& v) const noexcept
    {   return is_not (v.mjr (), v.mnr ()); }
    bool invalid () const noexcept
    {   if (root () == s_error) return true;
        return ! is_valid_ontology_version (root (), mjr (), mnr (), flags ()); }
    e_ontology root () const noexcept
    {   return static_cast < e_ontology > (flags () >> SV_ROOT_SHIFT); }
    ::std::string name () const;
    static ::std::string name (const e_ontology es);
    ::std::string ver () const;
    ::std::string report () const; };

typedef ::std::vector < ontology_version > vsv_t;

const ontology_version default_schema (s_none, 0, 0);

const ontology_version adms_1_0 (s_adms, 1, 0);
const ontology_version adms_2_0 (s_adms, 2, 0);

const ontology_version article_2012 (s_article, HTML_2012, 0);
const ontology_version article_2014 (s_article, HTML_2014, 0);
const ontology_version article_2018 (s_article, HTML_2018, 0);

const ontology_version as_1_0 (s_as, 1, 0);
const ontology_version as_2_0 (s_as, 2, 0);

const ontology_version bfo_2_0 (s_bfo, 2, 0);
const ontology_version bfo_2020 (s_bfo, 2, 2);

const ontology_version bibo_schema (s_bibo, 1, 3);

const ontology_version biro_schema (s_biro, 1, 1);

const ontology_version book_2012 (s_book, HTML_2012, 0);
const ontology_version book_2014 (s_book, HTML_2014, 0);
const ontology_version book_2018 (s_book, HTML_2018, 0);

const ontology_version cito_schema (s_cito, 2, 8);

const ontology_version content_schema (s_content, 1, 0);

const ontology_version common_tag (s_ctag, 1, 0);

const ontology_version creative_commons (s_cc, 1, 0);

const ontology_version crs2_schema (s_crs2, 1, 0);

const ontology_version csvw_schema (s_csvw, 1, 0);

const ontology_version daq_schema (s_daq, 1, 0);

const ontology_version dbd_schema (s_dbd, 1, 0);
const ontology_version dbo_schema (s_dbo, 1, 0);
const ontology_version dbp_schema (s_dbp, 1, 0);
const ontology_version dbp_owl_schema (s_dbp_owl, 1, 0);
const ontology_version dbr_schema (s_dbr, 1, 0);

const ontology_version data_catalogue_1 (s_dcat, 1, 0);
const ontology_version data_catalogue_2 (s_dcat, 2, 0);

const ontology_version described_by (s_describedby, 1, 0);

const ontology_version data_quality (s_dqv, 1, 0);

const ontology_version dc_1_0 (s_dc, 1, 0);
const ontology_version dc_1_1 (s_dc, 1, 1);
const ontology_version dcam (s_dcam, 1, 0);
const ontology_version dcmi (s_dcmi, 1, 0);
const ontology_version dublin_core_terms_1_0 (s_dct, 1, 0);
const ontology_version dublin_core_terms_1_1 (s_dct, 1, 1);

const ontology_version disco_schema (s_ddi, 1, 0);

const ontology_version doap_schema (s_doap, 1, 0);

const ontology_version duv_schema (s_duv, 1, 0);

const ontology_version earl_schema (s_earl, 1, 0);

const ontology_version error_schema (s_error, 0, 0);

const ontology_version event_schema (s_event, 1, 0);

const ontology_version exif_1_0 (s_exif, 1, 0);
const ontology_version exif_1_1 (s_exif, 1, 1);
const ontology_version exif_2_0 (s_exif, 2, 0);
const ontology_version exif_2_1 (s_exif, 2, 10);
const ontology_version exif_2_2 (s_exif, 2, 20);
const ontology_version exif_2_21 (s_exif, 2, 21);
const ontology_version exif_2_3 (s_exif, 2, 30);
const ontology_version exif_2_31 (s_exif, 2, 31);
const ontology_version exif_2_32 (s_exif, 2, 32);
const ontology_version exif_3_0 (s_exif, 3, 0);

const ontology_version exifex_2_21 (s_exifex, 2, 21);
const ontology_version exifex_2_3 (s_exifex, 2, 30);
const ontology_version exifex_2_31 (s_exifex, 2, 31);
const ontology_version exifex_2_32 (s_exifex, 2, 32);
const ontology_version exifex_3_0 (s_exifex, 3, 0);

const ontology_version fabio_schema (s_fabio, 2, 1);

const ontology_version faux_schema (s_faux, 1, 0);

const ontology_version frbr_schema (s_frbr, 1, 0);

const ontology_version foaf_schema (s_foaf, 0, 99);

const ontology_version good_relations (s_gr, 1, 0);

const ontology_version grddl_schema (s_grddl, 1, 0);

const ontology_version gs1_10 (s_gs1, 1, 0);
const ontology_version gs1_11 (s_gs1, 1, 1);
const ontology_version gs1_12 (s_gs1, 1, 2);
const ontology_version gs1_13 (s_gs1, 1, 3);
const ontology_version gs1_14 (s_gs1, 1, 4);
const ontology_version gs1_15 (s_gs1, 1, 5);
const ontology_version gs1_151 (s_gs1, 1, 51);

const ontology_version ical_schema (s_ical, 1, 0);

const ontology_version icaltzd_schema (s_icaltzd, 1, 0);

const ontology_version jsonld_ontology_1_0 (s_jsonld, 1, 0);
const ontology_version jsonld_ontology_1_1 (s_jsonld, 1, 1);

const ontology_version licence_schema (s_licence, 1, 0);

const ontology_version linked_data_platform (s_ldp, 1, 0);

const ontology_version locn_schema (s_locn, 1, 0);

const ontology_version media_resources (s_ma, 1, 0);

const ontology_version mf_1 (s_microformats, 1, 0);
const ontology_version mf_2 (s_microformats, 2, 0);
const ontology_version mf_all (s_microformats, 2, 0, SV_WILDCARD);

const ontology_version music_2012 (s_music, HTML_2012, 0);
const ontology_version music_2014 (s_music, HTML_2014, 0);
const ontology_version music_2018 (s_music, HTML_2018, 0);

const ontology_version web_annotation (s_oa, 1, 0);

const ontology_version open_graph_2010 (s_og, HTML_2010, 0);
const ontology_version open_graph_2012 (s_og, HTML_2012, 0);
const ontology_version open_graph_2014 (s_og, HTML_2014, 0);
const ontology_version open_graph_2018 (s_og, HTML_2018, 0);

const ontology_version odrl_schema (s_odrl, 1, 0);

const ontology_version org_schema (s_org, 1, 0);

const ontology_version owl_1 (s_owl, 1, 0);
const ontology_version owl_2 (s_owl, 2, 0);

const ontology_version pam_1_3 (s_pam, 1, 3);
const ontology_version pam_2_0 (s_pam, 2, 0);
const ontology_version pam_3_0 (s_pam, 3, 0);

const ontology_version pamp_3_0 (s_pamp, 3, 0);

const ontology_version pcm_3_1 (s_pcm, 3, 1);

const ontology_version pcmm_3_0 (s_pcmm, 3, 0);

const ontology_version pcv_1_0 (s_pcv, 1, 0);
const ontology_version pcv_2_0 (s_pcv, 1, 0);

const ontology_version pdf_schema (s_pdf, 1, 0);
const ontology_version photoshop_schema (s_photoshop, 1, 0);

const ontology_version pim_3_0 (s_pim, 3, 0);
const ontology_version pim_2_0 (s_pim, 2, 0);
const ontology_version pim_1_2 (s_pim, 1, 2);
const ontology_version pim_1_0 (s_pim, 1, 0);

const ontology_version pmi_3_0 (s_pmi, 3, 0);

const ontology_version poetry_ontology_1_0 (s_poetry, 1, 0);
const ontology_version poetry_ontology_1_1 (s_poetry, 1, 1);

const ontology_version prism_1_0 (s_prism, 1, 0);
const ontology_version prism_1_1 (s_prism, 1, 1);
const ontology_version prism_1_2 (s_prism, 1, 2);
const ontology_version prism_1_3 (s_prism, 1, 3);
const ontology_version prism_2_0 (s_prism, 2, 0);
const ontology_version prism_2_1 (s_prism, 2, 1);
const ontology_version prism_3_0 (s_prism, 3, 0);
const ontology_version prism_3_1 (s_prism, 3, 1);

const ontology_version prism_ad_3_0 (s_prism_ad, 3, 0);

const ontology_version prl_1_0 (s_prl, 1, 0);
const ontology_version prl_2_0 (s_prl, 2, 0);

const ontology_version prm_3_0 (s_prm, 3, 0);

const ontology_version profile_2012 (s_profile, HTML_2012, 0);
const ontology_version profile_2014 (s_profile, HTML_2014, 0);
const ontology_version profile_2018 (s_profile, HTML_2018, 0);

const ontology_version provincial (s_prov, 1, 0);

const ontology_version prs_3_1 (s_prs, 3, 1);

const ontology_version psv_1_0 (s_psv, 1, 0);

const ontology_version ptr_schema (s_ptr, 1, 0);

const ontology_version pur_3_0 (s_pur, 3, 0);
const ontology_version pur_2_1 (s_pur, 2, 1);

const ontology_version data_cube (s_qb, 1, 0);

const ontology_version rdf_1_0_schema (s_rdf, 1, 0);
const ontology_version rdf_1_1_1_schema (s_rdf, 1, 1);
const ontology_version rdf_1_1_2_schema (s_rdf, 1, 2);
const ontology_version rdf_1_1_3_schema (s_rdf, 1, 3);

const ontology_version rdfa_1_0_schema (s_rdfa, 1, 0);
const ontology_version rdfa_1_1_1_schema (s_rdfa, 1, 1);
const ontology_version rdfa_1_1_2_schema (s_rdfa, 1, 2);
const ontology_version rdfa_1_1_3_schema (s_rdfa, 1, 3);

const ontology_version rdfg_schema (s_rdfg, 1, 0);

const ontology_version rdfs_schema (s_rdfs, 1, 0);

const ontology_version review_schema (s_rev, 1, 0);

const ontology_version rif_schema (s_rif, 1, 0);

const ontology_version role_schema (s_role, 1, 0);

const ontology_version rr_schema (s_rr, 1, 0);

// schema versions before version 2.0 are not properly versioned IMHO.
// I've used (www.)schema.org and archive.org to get a rough set up as below.
// Versions before 0.91, dug up from archive.org are undocumented on schema.org
// (May 2022)), so I've assigned arbituary numbers which are liable to change
// should I find better documentation. Versions before June 2011 probably
// exist somewhere, but they're not under www.schema.org on archive.org.

const ontology_version schema_0 (s_schema, 0, 1);
const ontology_version schema_jun11 (s_schema, 0, 10);
const ontology_version schema_jul11 (s_schema, 0, 15);
const ontology_version schema_aug11 (s_schema, 0, 20);
const ontology_version schema_sep11 (s_schema, 0, 25);
const ontology_version schema_oct11 (s_schema, 0, 30);
const ontology_version schema_nov11 (s_schema, 0, 35);
const ontology_version schema_dec11 (s_schema, 0, 40);
const ontology_version schema_jan12 (s_schema, 0, 45);
const ontology_version schema_feb12 (s_schema, 0, 50);
const ontology_version schema_mar12 (s_schema, 0, 55);
const ontology_version schema_apr12 (s_schema, 0, 60);
const ontology_version schema_0_91 (s_schema, 0, 91);
const ontology_version schema_0_93 (s_schema, 0, 93);
const ontology_version schema_0_94 (s_schema, 0, 94);
const ontology_version schema_0_95 (s_schema, 0, 95);
const ontology_version schema_0_96 (s_schema, 0, 96);
const ontology_version schema_0_97 (s_schema, 0, 97);
const ontology_version schema_0_98 (s_schema, 0, 98);
const ontology_version schema_0_99 (s_schema, 0, 99);
const ontology_version schema_1_0A (s_schema, 1, 0);
const ontology_version schema_1_0B (s_schema, 1, 1);
const ontology_version schema_1_0C (s_schema, 1, 2);
const ontology_version schema_1_0D (s_schema, 1, 3);
const ontology_version schema_1_0E (s_schema, 1, 4);
const ontology_version schema_1_0F (s_schema, 1, 5);
const ontology_version schema_1_1 (s_schema, 1, 10);
const ontology_version schema_1_2 (s_schema, 1, 20);
const ontology_version schema_1_3 (s_schema, 1, 30);
const ontology_version schema_1_4 (s_schema, 1, 40);
const ontology_version schema_1_5 (s_schema, 1, 50);
const ontology_version schema_1_6 (s_schema, 1, 60);
const ontology_version schema_1_7 (s_schema, 1, 70);
const ontology_version schema_1_8 (s_schema, 1, 80);
const ontology_version schema_1_9 (s_schema, 1, 90);
const ontology_version schema_1_91 (s_schema, 1, 91);
const ontology_version schema_1_92 (s_schema, 1, 92);
const ontology_version schema_1_93 (s_schema, 1, 93);
const ontology_version schema_2_0 (s_schema, 2, 0);
const ontology_version schema_2_1 (s_schema, 2, 1);
const ontology_version schema_2_2 (s_schema, 2, 2);
const ontology_version schema_3_0 (s_schema, 3, 0);
const ontology_version schema_3_1 (s_schema, 3, 1);
const ontology_version schema_3_2 (s_schema, 3, 2);
const ontology_version schema_3_3 (s_schema, 3, 3);
const ontology_version schema_3_4 (s_schema, 3, 4);
const ontology_version schema_3_5 (s_schema, 3, 5);
const ontology_version schema_3_6 (s_schema, 3, 6);
const ontology_version schema_3_7 (s_schema, 3, 7);
const ontology_version schema_3_8 (s_schema, 3, 8);
const ontology_version schema_3_9 (s_schema, 3, 9);
const ontology_version schema_4 (s_schema, 4, 0);
const ontology_version schema_5 (s_schema, 5, 0);
const ontology_version schema_6 (s_schema, 6, 0);
const ontology_version schema_7_00 (s_schema, 7, 0);
const ontology_version schema_7_01 (s_schema, 7, 1);
const ontology_version schema_7_02 (s_schema, 7, 2);
const ontology_version schema_7_03 (s_schema, 7, 3);
const ontology_version schema_7_04 (s_schema, 7, 4);
const ontology_version schema_8 (s_schema, 8, 0);
const ontology_version schema_9 (s_schema, 9, 0);
const ontology_version schema_10 (s_schema, 10, 0);
const ontology_version schema_11 (s_schema, 11, 0);
const ontology_version schema_12 (s_schema, 12, 0);
const ontology_version schema_13 (s_schema, 13, 0);
const ontology_version schema_14 (s_schema, 14, 0);
const ontology_version schema_15 (s_schema, 15, 0);
const ontology_version schema_16 (s_schema, 16, 0);
const ontology_version schema_17 (s_schema, 17, 0);
const ontology_version schema_18 (s_schema, 18, 0);
const ontology_version schema_19 (s_schema, 19, 0);
const ontology_version schema_20 (s_schema, 20, 0);
const ontology_version schema_21 (s_schema, 21, 0);
const ontology_version schema_22 (s_schema, 22, 0);
const ontology_version schema_23 (s_schema, 23, 0);
const ontology_version schema_default (s_schema, DEFAULT_SCHEMA_ORG_MAJOR, DEFAULT_SCHEMA_ORG_MINOR);

const ontology_version sd_schema (s_sd, 1, 0);

const ontology_version sioc_schema (s_sioc, 1, 0);
const ontology_version sioc_services (s_sioc_s, 1, 0);
const ontology_version sioc_types (s_sioc_t, 1, 0);

const ontology_version skos_schema (s_skos, 1, 0);
const ontology_version skosxl_schema (s_skosxl, 1, 0);

const ontology_version ssn_schema (s_ssn, 1, 0);

const ontology_version sosa_schema (s_sosa, 1, 0);

const ontology_version xmp_stdim (s_stdim, 1, 0);
const ontology_version xmp_stevt (s_stevt, 1, 0);
const ontology_version xmp_stfnt (s_stfnt, 1, 0);
const ontology_version xmp_stjob (s_stjob, 1, 0);
const ontology_version xmp_stref (s_stref, 1, 0);
const ontology_version xmp_stver (s_stver, 1, 0);

const ontology_version taxo_schema (s_taxo, 1, 0);

const ontology_version tiff_schema (s_tiff, 6, 0);

const ontology_version time_schema (s_time, 1, 0);

const ontology_version data_vocabulary (s_v, 1, 0);

const ontology_version vann_1_0 (s_vann, 1, 0);
const ontology_version vann_1_1 (s_vann, 1, 1);

const ontology_version vcard_2001 (s_vcard, 1, 0);
const ontology_version vcard_2006 (s_vcard, 2, 0);
const ontology_version vcard_2010 (s_vcard, 3, 0);
const ontology_version vcard_2014 (s_vcard, 4, 0);

const ontology_version video_2012 (s_video, HTML_2012, 0);
const ontology_version video_2014 (s_video, HTML_2014, 0);
const ontology_version video_2018 (s_video, HTML_2018, 0);

const ontology_version void_schema (s_void, 1, 0);

const ontology_version wdr_schema (s_wdr, 1, 0);

const ontology_version wdrs_schema (s_wdrs, 1, 0);

const ontology_version website_2012 (s_website, HTML_2012, 0);
const ontology_version website_2014 (s_website, HTML_2014, 0);
const ontology_version website_2018 (s_website, HTML_2018, 0);

const ontology_version whatwg_schema (s_whatwg, 1, 0);

const ontology_version xhv_schema (s_xhv, 1, 0);

const ontology_version xml_schema (s_xml, 1, 0);

const ontology_version xmp_schema (s_xmp, 1, 0);
const ontology_version xmp_bj (s_xmpbj, 1, 0);
const ontology_version xmp_dm (s_xmpdm, 1, 0);
const ontology_version xmp_g (s_xmpg, 1, 0);
const ontology_version xmp_gimg (s_xmpgimg, 1, 0);
const ontology_version xmp_idq (s_xmpidq, 1, 0);
const ontology_version xmp_mm (s_xmpmm, 1, 0);
const ontology_version xmp_rights (s_xmprights, 1, 0);
const ontology_version xmp_tpg (s_xmptpg, 1, 0);

const ontology_version xsd_1_0 (s_xsd, 1, 0);
const ontology_version xsd_1_1 (s_xsd, 1, 1);

bool overlap (const ontology_version& lhs_from, const ontology_version& lhs_to, const ontology_version& rhs_from, const ontology_version& rhs_to);
bool does_ontology_apply (const ontology_version& v, const ontology_version& from, const ontology_version& to) MSVC_NOEXCEPT;

template < > inline bool does_apply < ontology_version > (const ontology_version& v, const ontology_version& from, const ontology_version& to) MSVC_NOEXCEPT
{   return does_ontology_apply (v, from, to); }
