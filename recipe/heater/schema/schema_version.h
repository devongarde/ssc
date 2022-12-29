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

#define MAX_SCHEMA_ORG_MAJOR 15
#define MAX_SCHEMA_ORG_MINOR 0
#define MIN_SCHEMA_ORG_MAJOR 0
#define MIN_SCHEMA_ORG_MINOR 10
#define DEFAULT_SCHEMA_ORG_MAJOR MAX_SCHEMA_ORG_MAJOR
#define DEFAULT_SCHEMA_ORG_MINOR MAX_SCHEMA_ORG_MINOR
#define DEFAULT_SCHEMA_ORG_VERSION "15.0"

class html_version;
struct schema_version;
typedef ::std::set < e_schema > vsh_t;

schema_version corresponding_schema_version (const e_schema es, const html_version& v);
bool set_default_schema_version (const e_schema es, unsigned short mjr, unsigned short mnr);
schema_version get_default_schema_version (const e_schema es);
schema_version get_first_schema_version (const e_schema es) noexcept;
schema_version get_last_schema_version (const e_schema es) noexcept;
int get_schema_version_count (const e_schema es) noexcept;
bool is_faux_schema (const e_schema es) noexcept;
bool is_valid_schema_version (const e_schema root, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept;
bool is_schema_deprecated (const e_schema root, const unsigned short mjr, const unsigned short mnr, const flags_t flags) noexcept;

struct schema_version : public version
{   DEFAULT_CONSTRUCTORS (schema_version);
    schema_version (const unsigned short mjr, const unsigned short mnr, const flags_t sf = NOFLAGS) noexcept
        :   version (mjr, mnr, (static_cast < flags_t > (s_schema) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    { }
    schema_version (const e_schema root, const unsigned short mjr, const unsigned short mnr, const flags_t sf = NOFLAGS) noexcept
        :   version (mjr, mnr, (static_cast < flags_t > (root) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    { }
    schema_version (const html_version& v) noexcept;
    static void init (nitpick& nits);
    void reset () noexcept
    {   schema_version v; swap (v); }
    void reset (const schema_version& v) noexcept
    {   schema_version vv (v); swap (vv); }
    bool deprecated () const noexcept
    {   if ((flags () & SV_DEPRECATED) == SV_DEPRECATED) return true;
        return is_schema_deprecated (root (), mjr (), mnr (), flags ()); }
    bool is_not (const unsigned short mj, const unsigned short mn = USHRT_MAX) const noexcept
    {   if (unknown ()) return false;
        if (mj != mjr ()) return true;
        return ((mn != USHRT_MAX) && (mn != mnr ())); }
    bool is_not (const schema_version& v) const noexcept
    {   return is_not (v.mjr (), v.mnr ()); }
    bool invalid () const noexcept
    {   if (root () == s_error) return true;
        return ! is_valid_schema_version (root (), mjr (), mnr (), flags ()); }
    e_schema root () const noexcept
    {   return static_cast < e_schema > (flags () >> SV_ROOT_SHIFT); }
    ::std::string name () const;
    static ::std::string name (const e_schema es);
    ::std::string ver () const;
    ::std::string report () const; };

typedef ::std::vector < schema_version > vsv_t;

const schema_version default_schema (s_none, 0, 0);

const schema_version article_2012 (s_article, HTML_2012, 0);
const schema_version article_2014 (s_article, HTML_2014, 0);
const schema_version article_2018 (s_article, HTML_2018, 0);

const schema_version as_1_0 (s_as, 1, 0);
const schema_version as_2_0 (s_as, 2, 0);

const schema_version bibo_schema (s_bibo, 1, 3);

const schema_version book_2012 (s_book, HTML_2012, 0);
const schema_version book_2014 (s_book, HTML_2014, 0);
const schema_version book_2018 (s_book, HTML_2018, 0);

const schema_version content_schema (s_content, 1, 0);

const schema_version common_tag (s_ctag, 1, 0);

const schema_version creative_commons (s_cc, 1, 0);

const schema_version csvw_schema (s_csvw, 1, 0);

const schema_version daq_schema (s_daq, 1, 0);

const schema_version dbd_schema (s_dbd, 1, 0);
const schema_version dbo_schema (s_dbo, 1, 0);
const schema_version dbp_schema (s_dbp, 1, 0);
const schema_version dbp_owl_schema (s_dbp_owl, 1, 0);
const schema_version dbr_schema (s_dbr, 1, 0);

const schema_version data_catalogue_1 (s_dcat, 1, 0);
const schema_version data_catalogue_2 (s_dcat, 2, 0);

const schema_version described_by (s_describedby, 1, 0);

const schema_version data_quality (s_dqv, 1, 0);

const schema_version dc_1_0 (s_dc, 1, 0);
const schema_version dc_1_1 (s_dc, 1, 1);
const schema_version dcam (s_dcam, 1, 0);
const schema_version dcmi (s_dcmi, 1, 0);
const schema_version dublin_core_terms_1_0 (s_dct, 1, 0);
const schema_version dublin_core_terms_1_1 (s_dct, 1, 1);

const schema_version doap_schema (s_doap, 1, 0);

const schema_version duv_schema (s_duv, 1, 0);

const schema_version earl_schema (s_earl, 1, 0);

const schema_version error_schema (s_error, 0, 0);

const schema_version event_schema (s_event, 1, 0);

const schema_version faux_schema (s_faux, 1, 0);

const schema_version frbr_schema (s_frbr, 1, 0);

const schema_version foaf_schema (s_foaf, 0, 99);

const schema_version good_relations (s_gr, 1, 0);

const schema_version grddl_schema (s_grddl, 1, 0);

const schema_version gs1_10 (s_gs1, 1, 0);
const schema_version gs1_11 (s_gs1, 1, 1);
const schema_version gs1_12 (s_gs1, 1, 2);
const schema_version gs1_13 (s_gs1, 1, 3);
const schema_version gs1_14 (s_gs1, 1, 4);
const schema_version gs1_15 (s_gs1, 1, 5);
const schema_version gs1_151 (s_gs1, 1, 51);

const schema_version ical_schema (s_ical, 1, 0);

const schema_version icaltzd_schema (s_icaltzd, 1, 0);

const schema_version jsonld_schema_1_0 (s_jsonld, 1, 0);
const schema_version jsonld_schema_1_1 (s_jsonld, 1, 1);

const schema_version licence_schema (s_licence, 1, 0);

const schema_version linked_data_platform (s_ldp, 1, 0);

const schema_version locn_schema (s_locn, 1, 0);

const schema_version media_resources (s_ma, 1, 0);

const schema_version mf_1 (s_microformats, 1, 0);
const schema_version mf_2 (s_microformats, 2, 0);
const schema_version mf_all (s_microformats, 2, 0, SV_WILDCARD);

const schema_version music_2012 (s_music, HTML_2012, 0);
const schema_version music_2014 (s_music, HTML_2014, 0);
const schema_version music_2018 (s_music, HTML_2018, 0);

const schema_version web_annotation (s_oa, 1, 0);

const schema_version open_graph_2010 (s_og, HTML_2010, 0);
const schema_version open_graph_2012 (s_og, HTML_2012, 0);
const schema_version open_graph_2014 (s_og, HTML_2014, 0);
const schema_version open_graph_2018 (s_og, HTML_2018, 0);

const schema_version odrl_schema (s_odrl, 1, 0);

const schema_version org_schema (s_org, 1, 0);

const schema_version owl_1 (s_owl, 1, 0);
const schema_version owl_2 (s_owl, 2, 0);

const schema_version poetry_schema_1_0 (s_poetry, 1, 0);
const schema_version poetry_schema_1_1 (s_poetry, 1, 1);

const schema_version profile_2012 (s_profile, HTML_2012, 0);
const schema_version profile_2014 (s_profile, HTML_2014, 0);
const schema_version profile_2018 (s_profile, HTML_2018, 0);

const schema_version provincial (s_prov, 1, 0);

const schema_version ptr_schema (s_ptr, 1, 0);

const schema_version data_cube (s_qb, 1, 0);

const schema_version rdf_1_0_schema (s_rdf, 1, 0);
const schema_version rdf_1_1_1_schema (s_rdf, 1, 1);
const schema_version rdf_1_1_2_schema (s_rdf, 1, 2);
const schema_version rdf_1_1_3_schema (s_rdf, 1, 3);

const schema_version rdfa_1_0_schema (s_rdfa, 1, 0);
const schema_version rdfa_1_1_1_schema (s_rdfa, 1, 1);
const schema_version rdfa_1_1_2_schema (s_rdfa, 1, 2);
const schema_version rdfa_1_1_3_schema (s_rdfa, 1, 3);

const schema_version rdfg_schema (s_rdfg, 1, 0);

const schema_version rdfs_schema (s_rdfs, 1, 0);

const schema_version review_schema (s_rev, 1, 0);

const schema_version rif_schema (s_rif, 1, 0);

const schema_version role_schema (s_role, 1, 0);

const schema_version rr_schema (s_rr, 1, 0);

// schema versions before version 2.0 are not properly versioned IMHO.
// I've used (www.)schema.org and archive.org to get a rough set up as below.
// Versions before 0.91, dug up from archive.org are undocumented on schema.org
// (May 2022)), so I've assigned arbituary numbers which are liable to change
// should I find better documentation. Versions before June 2011 probably
// exist somewhere, but they're not under www.schema.org on archive.org.

const schema_version schema_0 (s_schema, 0, 1);
const schema_version schema_jun11 (s_schema, 0, 10);
const schema_version schema_jul11 (s_schema, 0, 15);
const schema_version schema_aug11 (s_schema, 0, 20);
const schema_version schema_sep11 (s_schema, 0, 25);
const schema_version schema_oct11 (s_schema, 0, 30);
const schema_version schema_nov11 (s_schema, 0, 35);
const schema_version schema_dec11 (s_schema, 0, 40);
const schema_version schema_jan12 (s_schema, 0, 45);
const schema_version schema_feb12 (s_schema, 0, 50);
const schema_version schema_mar12 (s_schema, 0, 55);
const schema_version schema_apr12 (s_schema, 0, 60);
const schema_version schema_0_91 (s_schema, 0, 91);
const schema_version schema_0_93 (s_schema, 0, 93);
const schema_version schema_0_94 (s_schema, 0, 94);
const schema_version schema_0_95 (s_schema, 0, 95);
const schema_version schema_0_96 (s_schema, 0, 96);
const schema_version schema_0_97 (s_schema, 0, 97);
const schema_version schema_0_98 (s_schema, 0, 98);
const schema_version schema_0_99 (s_schema, 0, 99);
const schema_version schema_1_0A (s_schema, 1, 0);
const schema_version schema_1_0B (s_schema, 1, 1);
const schema_version schema_1_0C (s_schema, 1, 2);
const schema_version schema_1_0D (s_schema, 1, 3);
const schema_version schema_1_0E (s_schema, 1, 4);
const schema_version schema_1_0F (s_schema, 1, 5);
const schema_version schema_1_1 (s_schema, 1, 10);
const schema_version schema_1_2 (s_schema, 1, 20);
const schema_version schema_1_3 (s_schema, 1, 30);
const schema_version schema_1_4 (s_schema, 1, 40);
const schema_version schema_1_5 (s_schema, 1, 50);
const schema_version schema_1_6 (s_schema, 1, 60);
const schema_version schema_1_7 (s_schema, 1, 70);
const schema_version schema_1_8 (s_schema, 1, 80);
const schema_version schema_1_9 (s_schema, 1, 90);
const schema_version schema_1_91 (s_schema, 1, 91);
const schema_version schema_1_92 (s_schema, 1, 92);
const schema_version schema_1_93 (s_schema, 1, 93);
const schema_version schema_2_0 (s_schema, 2, 0);
const schema_version schema_2_1 (s_schema, 2, 1);
const schema_version schema_2_2 (s_schema, 2, 2);
const schema_version schema_3_0 (s_schema, 3, 0);
const schema_version schema_3_1 (s_schema, 3, 1);
const schema_version schema_3_2 (s_schema, 3, 2);
const schema_version schema_3_3 (s_schema, 3, 3);
const schema_version schema_3_4 (s_schema, 3, 4);
const schema_version schema_3_5 (s_schema, 3, 5);
const schema_version schema_3_6 (s_schema, 3, 6);
const schema_version schema_3_7 (s_schema, 3, 7);
const schema_version schema_3_8 (s_schema, 3, 8);
const schema_version schema_3_9 (s_schema, 3, 9);
const schema_version schema_4 (s_schema, 4, 0);
const schema_version schema_5 (s_schema, 5, 0);
const schema_version schema_6 (s_schema, 6, 0);
const schema_version schema_7_00 (s_schema, 7, 0);
const schema_version schema_7_01 (s_schema, 7, 1);
const schema_version schema_7_02 (s_schema, 7, 2);
const schema_version schema_7_03 (s_schema, 7, 3);
const schema_version schema_7_04 (s_schema, 7, 4);
const schema_version schema_8 (s_schema, 8, 0);
const schema_version schema_9 (s_schema, 9, 0);
const schema_version schema_10 (s_schema, 10, 0);
const schema_version schema_11 (s_schema, 11, 0);
const schema_version schema_12 (s_schema, 12, 0);
const schema_version schema_13 (s_schema, 13, 0);
const schema_version schema_14 (s_schema, 14, 0);
const schema_version schema_15 (s_schema, 15, 0);
const schema_version schema_default (s_schema, DEFAULT_SCHEMA_ORG_MAJOR, DEFAULT_SCHEMA_ORG_MINOR);

const schema_version sd_schema (s_sd, 1, 0);

const schema_version sioc_schema (s_sioc, 1, 0);
const schema_version sioc_services (s_sioc_s, 1, 0);
const schema_version sioc_types (s_sioc_t, 1, 0);

const schema_version skos_schema (s_skos, 1, 0);
const schema_version skosxl_schema (s_skosxl, 1, 0);

const schema_version ssn_schema (s_ssn, 1, 0);

const schema_version sosa_schema (s_sosa, 1, 0);

const schema_version taxo_schema (s_taxo, 1, 0);

const schema_version time_schema (s_time, 1, 0);

const schema_version data_vocabulary (s_v, 1, 0);

const schema_version vann_1_0 (s_vann, 1, 0);
const schema_version vann_1_1 (s_vann, 1, 1);

const schema_version vcard_2001 (s_vcard, 1, 0);
const schema_version vcard_2006 (s_vcard, 2, 0);
const schema_version vcard_2010 (s_vcard, 3, 0);
const schema_version vcard_2014 (s_vcard, 4, 0);

const schema_version video_2012 (s_video, HTML_2012, 0);
const schema_version video_2014 (s_video, HTML_2014, 0);
const schema_version video_2018 (s_video, HTML_2018, 0);

const schema_version void_schema (s_void, 1, 0);

const schema_version wdr_schema (s_wdr, 1, 0);

const schema_version wdrs_schema (s_wdrs, 1, 0);

const schema_version website_2012 (s_website, HTML_2012, 0);
const schema_version website_2014 (s_website, HTML_2014, 0);
const schema_version website_2018 (s_website, HTML_2018, 0);

const schema_version whatwg_schema (s_whatwg, 1, 0);

const schema_version xhv_schema (s_xhv, 1, 0);

const schema_version xml_schema (s_xml, 1, 0);

const schema_version xsd_1_0 (s_xsd, 1, 0);
const schema_version xsd_1_1 (s_xsd, 1, 1);

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to);
bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to) MSVC_NOEXCEPT;

template < > inline bool does_apply < schema_version > (const schema_version& v, const schema_version& from, const schema_version& to) MSVC_NOEXCEPT
{   return does_schema_apply (v, from, to); }
