/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#define DEFAULT_SCHEMA_ORG_MAJOR 13
#define DEFAULT_SCHEMA_ORG_MINOR 0
#define DEFAULT_SCHEMA_ORG_VERSION "13"

const unsigned char schema_major_max = DEFAULT_SCHEMA_ORG_MAJOR;
class html_version;

bool is_valid_schema_version (const e_schema root, const unsigned char mjr, const unsigned char mnr);

struct schema_version : public version
{   schema_version () = default;
    schema_version (const unsigned char mjr, const unsigned char mnr, const flags_t sf = NOFLAGS)
        :   version (mjr, mnr, (static_cast < flags_t > (s_schema) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    {   PRESUME (! invalid (), __FILE__, __LINE__); }
    schema_version (const e_schema root, const unsigned char mjr, const unsigned char mnr, const flags_t sf = NOFLAGS)
        :   version (mjr, mnr, (static_cast < flags_t > (root) << SV_ROOT_SHIFT) | (sf & SV_FLAG_MASK))
    {   PRESUME (! invalid (), __FILE__, __LINE__); }
    schema_version (const schema_version& ) = default;
    schema_version (const html_version& v);
#ifndef NO_MOVE_CONSTRUCTOR
	schema_version (schema_version&& ) = default;
#endif // VS
	~schema_version () = default;
    schema_version& operator = (const schema_version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	schema_version& operator = (schema_version&&) = default;
#endif // VS
    static void init ();
    void reset ()
    {   schema_version v; swap (v); }
    void reset (const schema_version& v)
    {   schema_version vv (v); swap (vv); }
    bool unknown () const { return (mjr () == 0) && (mnr () == 0); }
    bool known () const { return ! unknown (); }
    bool deprecated () const { return ((flags () & SV_DEPRECATED) == SV_DEPRECATED); }
    bool is_not (const unsigned char mj, const unsigned char mn = 0xFF) const
    {   if (unknown ()) return false;
        if (mj != mjr ()) return true;
        return ((mn != 0xFF) && (mn != mnr ())); }
    bool is_not (const schema_version& v) const
    {   return is_not (v.mjr (), v.mnr ()); }
    bool invalid () const { return ! is_valid_schema_version (root (), mjr (), mnr ()); }
    e_schema root () const
    {   return static_cast < e_schema > (flags () >> SV_ROOT_SHIFT); }
    ::std::string report () const; };

typedef ::std::vector < schema_version > vsv_t;
extern vsv_t vsv;

const schema_version default_schema (s_none, 0, 0);

const schema_version article_schema (s_article, 1, 0);

const schema_version as_schema (s_as, 1, 0);

const schema_version book_schema (s_book, 1, 0);

const schema_version content_schema (s_content, 1, 0);

const schema_version common_tag (s_ctag, 1, 0);

const schema_version creative_commons (s_cc, 1, 0);

const schema_version csvw_1_0 (s_csvw, 1, 0);

const schema_version daq_schema (s_daq, 1, 0);

const schema_version data_catalogue_1 (s_dcat, 1, 0);
const schema_version data_catalogue_2 (s_dcat, 2, 0);

const schema_version data_quality (s_dqv, 1, 0);

const schema_version dc_1_0 (s_dc, 1, 0);
const schema_version dc_1_1 (s_dc, 1, 1);
const schema_version dcam (s_dcmi, 1, 0);
const schema_version dcmi (s_dcmi, 1, 0);
const schema_version dublin_core_terms (s_dct, 1, 0);

const schema_version doap_schema (s_doap, 1, 0);

const schema_version duv_schema (s_duv, 1, 0);

const schema_version earl_schema (s_earl, 1, 0);

const schema_version faux_schema (s_faux, 1, 0);

const schema_version foaf_schema (s_foaf, 0, 99);

const schema_version good_relations (s_gr, 1, 0);

const schema_version grddl_schema (s_grddl, 1, 0);

const schema_version ical_schema (s_ical, 1, 0);

const schema_version icaltzd_schema (s_icaltzd, 1, 0);

const schema_version jsonld_schema (s_jsonld, 1, 0);

const schema_version linked_data_platform (s_ldp, 1, 0);

const schema_version locn_schema (s_locn, 1, 0);

const schema_version media_resources (s_ma, 1, 0);

const schema_version mf_1 (s_microformats, 1, 0);
const schema_version mf_2 (s_microformats, 2, 0);
const schema_version mf_all (s_microformats, 2, 0, SV_WILDCARD);

const schema_version music_schema (s_music, 1, 0);

const schema_version web_annotation (s_oa, 1, 0);

const schema_version open_graph (s_og, 1, 0);

const schema_version odrl_schema (s_odrl, 1, 0);

const schema_version org_schema (s_org, 1, 0);

const schema_version owl_1 (s_owl, 1, 0);
const schema_version owl_2 (s_owl, 2, 0);

const schema_version poetry_schema (s_poetry, 1, 0);

const schema_version profile_schema (s_profile, 1, 0);

const schema_version provincial (s_prov, 1, 0);

const schema_version ptr_schema (s_ptr, 1, 0);

const schema_version data_cube (s_qb, 1, 0);

const schema_version rdf_schema (s_rdf, 1, 0);

const schema_version rdfa_1_0 (s_rdfa, 1, 0);
const schema_version rdfa_1_1_1 (s_rdfa, 1, 1);
const schema_version rdfa_1_1_2 (s_rdfa, 1, 2);
const schema_version rdfa_1_1_3 (s_rdfa, 1, 3);

const schema_version rdfg_schema (s_rdfg, 1, 0);

const schema_version rdfs_schema (s_rdfs, 1, 0);

const schema_version review_schema (s_rev, 1, 0);

const schema_version rif_schema (s_rif, 1, 0);

const schema_version rr_schema (s_rr, 1, 0);

const schema_version schema_0 (s_schema, 0, 0);
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
const schema_version schema_default (s_schema, DEFAULT_SCHEMA_ORG_MAJOR, DEFAULT_SCHEMA_ORG_MINOR);

const schema_version sd_schema (s_sd, 1, 0);

const schema_version sioc_schema (s_sioc, 1, 0);
const schema_version sioc_services (s_sioc_s, 1, 0);
const schema_version sioc_types (s_sioc_t, 1, 0);

const schema_version skos_schema (s_skos, 1, 0);
const schema_version skosxl_schema (s_skosxl, 1, 0);

const schema_version ssn_schema (s_ssn, 1, 0);

const schema_version sosa_schema (s_ssn, 1, 0);

const schema_version time_schema (s_time, 1, 0);

const schema_version vcard_schema (s_vcard, 1, 0);

const schema_version video_schema (s_video, 1, 0);

const schema_version void_schema (s_void, 1, 0);

const schema_version wdr_schema (s_wdr, 1, 0);

const schema_version wdrs_schema (s_wdrs, 1, 0);

const schema_version website_schema (s_website, 1, 0);

const schema_version whatwg_schema (s_whatwg, 1, 0);

const schema_version xhv_schema (s_xhv, 1, 0);

const schema_version xsd_1_0 (s_xsd, 1, 0);
const schema_version xsd_1_1 (s_xsd, 1, 1);

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to);
bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to);

template < > inline bool does_apply < schema_version > (const schema_version& v, const schema_version& from, const schema_version& to)
{   return does_schema_apply (v, from, to); }
