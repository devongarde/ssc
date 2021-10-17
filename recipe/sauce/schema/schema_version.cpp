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
#include "main/context.h"
#include "schema/schema_version.h"
#include "parser/html_version.h"
#include "symbol/nstr.h"

vsv_t vsv;

schema_version::schema_version (const html_version& v)
{   schema_version sv;
    set_mjr (v.mjr (), v.mnr ());
    if (! sv.invalid ()) swap (sv); }

void schema_version::init () // call after context construction
{   vsv.resize (schema_size);
// kitchen_sink
    vsv [s_none] = default_schema;
    vsv [s_article] = article_schema;
    vsv [s_as] = as_schema;
    vsv [s_bibo] = bibo_schema;
    vsv [s_book] = book_schema;
    vsv [s_cc] = creative_commons;
    vsv [s_content] = content_schema;
    vsv [s_csvw] = csvw_1_0;
    vsv [s_ctag] = common_tag;
    vsv [s_daq] = daq_schema;
    vsv [s_dc] = dc_1_1;
    vsv [s_dcam] = dcam;
    vsv [s_dcat] = data_catalogue_2;
    vsv [s_dcmi] = dcmi;
    vsv [s_dct] = dublin_core_terms;
    vsv [s_doap] = doap_schema;
    vsv [s_dqv] = data_quality;
    vsv [s_duv] = duv_schema;
    vsv [s_earl] = earl_schema;
    vsv [s_event] = event_schema;
    vsv [s_faux] = faux_schema;
    vsv [s_foaf] = foaf_schema;
    vsv [s_gr] = good_relations;
    vsv [s_grddl] = grddl_schema;
    vsv [s_ical] = ical_schema;
    vsv [s_icaltzd] = icaltzd_schema;
    vsv [s_jsonld] = jsonld_schema;
    vsv [s_ldp] = linked_data_platform;
    vsv [s_locn] = locn_schema;
    vsv [s_ma] = media_resources;
    vsv [s_microformats] = context.mf_ver ();
    vsv [s_music] = music_schema;
    vsv [s_oa] = web_annotation;
    vsv [s_og] = open_graph;
    vsv [s_odrl] = odrl_schema;
    vsv [s_org] = org_schema;
    vsv [s_owl] = owl_2;
    vsv [s_poetry] = poetry_schema;
    vsv [s_profile] = profile_schema;
    vsv [s_prov] = provincial;
    vsv [s_ptr] = ptr_schema;
    vsv [s_qb] = data_cube;
    vsv [s_rdf] = rdf_schema;
    vsv [s_rdfa] = rdfa_1_1_3;
    vsv [s_rdfg] = rdfg_schema;
    vsv [s_rdfs] = rdfs_schema;
    vsv [s_rev] = review_schema;
    vsv [s_rif] = rif_schema;
    vsv [s_rr] = rr_schema;
    vsv [s_schema] = context.schema_ver ();
    vsv [s_sd] = sd_schema;
    vsv [s_sioc] = sioc_schema;
    vsv [s_sioc_s] = sioc_services;
    vsv [s_sioc_t] = sioc_types;
    vsv [s_skos] = skos_schema;
    vsv [s_skosxl] = skosxl_schema;
    vsv [s_sosa] = sosa_schema;
    vsv [s_ssn] = ssn_schema;
    vsv [s_time] = time_schema;
    vsv [s_v] = data_vocabulary;
    vsv [s_vcard] = vcard_schema;
    vsv [s_video] = video_schema;
    vsv [s_void] = void_schema;
    vsv [s_wdr] = wdr_schema;
    vsv [s_wdrs] = wdrs_schema;
    vsv [s_website] = website_schema;
    vsv [s_whatwg] = whatwg_schema;
    vsv [s_xhv] = xhv_schema;
    vsv [s_xsd] = xsd_1_1; }

::std::string schema_version::report () const
{   ::std::ostringstream res;
    if (known ())
    {   e_schema r = root ();
        PRESUME (r < s_error, __FILE__, __LINE__);
        switch (r)
        {   case s_article :
                res << "open graph article";
                break;
            case s_as :
                res << "activity streams v2.0";
                break;
            case s_bibo :
                res << "bibliographic ontology";
                break;
            case s_book :
                res << "open graph book";
                break;
            case s_cc :
                res << "creative commons";
                break;
            case s_content :
                res << "content";
                break;
            case s_csvw :
                res << "CSVW";
                break;
           case s_ctag :
                res << "common tag";
                break;
            case s_daq :
                res << "dataset quality vocabulary";
                break;
            case s_dc :
                res << "dublin core";
                break;
            case s_dcam :
                res << "DCAM";
                break;
            case s_dcat :
                res << "data catalogue";
                break;
            case s_dcmi :
                res << "DCMI";
                break;
            case s_dct :
                res << "dublin core terms";
                break;
            case s_doap :
                res << "description of a project";
                break;
            case s_dqv :
                res << "data quality";
                break;
            case s_duv :
                res << "duv";
                break;
            case s_earl :
                res << "evaluation and report language";
                break;
            case s_event :
                res << "event";
                break;
            case s_faux :
                res << "faux schema";
                break;
            case s_foaf :
                res << "foaf v" << static_cast < int > (mjr ()) << "." << static_cast < int > (mnr ());
                break;
            case s_gr:
                res << "good relations";
                break;
            case s_grddl:
                res << "gleaning resource descriptions from dialects of languages";
                break;
            case s_ical:
                res << "ical";
                break;
            case s_icaltzd:
                res << "icaltzd";
                break;
            case s_jsonld :
                res << "jsonld";
                break;
            case s_ldp :
                res << "linked data platform";
                break;
            case s_ma :
                res << "media resources";
                break;
            case s_microformats :
                res << "microformats.org";
                if (! any_flags (SV_WILDCARD))
                    res << " v" << static_cast < int > (mjr ());
                break;
            case s_none :
                break;
            case s_oa :
                res << "web annotation";
                break;
            case s_og :
                res << "open graph";
                break;
            case s_odrl :
                res << "open digital rights";
                break;
            case s_org :
                res << "organisation";
                break;
            case s_owl :
                res << "owl";
                break;
            case s_poetry :
                res << "poetry";
                break;
            case s_profile :
                res << "open graph profile";
                break;
            case s_prov :
                res << "provenance";
                break;
            case s_ptr :
                res << "ptr content";
                break;
            case s_qb :
                res << "data cube";
                break;
            case s_rdf :
                res << "RDF";
                break;
            case s_rdfa :
                res << "RDFa v1.";
                if (mnr () == 0) res << "0";
                else res << "1." << static_cast < int > (mnr ());
                break;
            case s_rdfg :
                res << "RDF graph";
                break;
            case s_rdfs :
                res << "RDFs";
                break;
            case s_rev:
                res << "RDF review";
                break;
            case s_rif:
                res << "rule interchange format";
                break;
            case s_rr:
                res << "rr";
                break;
            case s_schema :
                res << "schema.org v";
                if (mjr () == 7)
                    res << static_cast < int > (mjr ()) << ".0" << static_cast < int > (mnr ());
                else res << static_cast < int > (mjr ()) << "." << static_cast < int > (mnr ());
                break;
            case s_sd :
                res << "sparql service description";
                break;
            case s_sioc :
                res << "semantically-interlinked online communities";
                break;
            case s_sioc_s :
                res << "semantically-interlinked online communities services";
                break;
            case s_sioc_t :
                res << "semantically-interlinked online communities types";
                break;
            case s_skos :
                res << "simple knowledge organisation system";
                break;
            case s_skosxl :
                res << "simple knowledge organisation system extension";
                break;
            case s_ssn :
                res << "semantic sensor network";
                break;
            case s_sosa :
                res << "sensor, observations, sample, actuator";
                break;
            case s_time :
                res << "time";
                break;
            case s_v :
                res << "data vocabulary";
                break;
            case s_vcard :
                res << "vcard v" << static_cast < int > (mjr ()) << ".0";
                break;
            case s_video :
                res << "open graph video";
                break;
            case s_void :
                res << "VoID";
                break;
             case s_wdr :
                res << "WDR (powder)";
                break;
             case s_wdrs :
                res << "WDRS";
                break;
            case s_website :
                res << "open graph website";
                break;
            case s_whatwg :
                res << "WhatWG";
                break;
            case s_xhv :
                res << "XHTML vocabulary";
                break;
            case s_xsd :
                res << "XML Schema Type";
                break;
            default :
                res << schema_names.get (r, SCHEMA_NAME);
                break; } }
    return res.str (); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_schema_version (const e_schema root, const unsigned char j, const unsigned char n)
{   switch (root)
    {   case s_article :
        case s_book :
        case s_cc :
        case s_content :
        case s_csvw :
        case s_ctag :
        case s_daq :
        case s_doap :
        case s_dqv :
        case s_duv :
        case s_earl :
        case s_event :
        case s_faux :
        case s_gr :
        case s_grddl :
        case s_ical :
        case s_icaltzd :
        case s_jsonld :
        case s_ldp :
        case s_locn :
        case s_ma :
        case s_music :
        case s_oa :
        case s_og :
        case s_odrl :
        case s_org :
        case s_poetry :
        case s_profile :
        case s_prov :
        case s_ptr :
        case s_qb :
        case s_rdf :
        case s_rdfg:
        case s_rdfs:
        case s_rev:
        case s_rif:
        case s_rr:
        case s_sd:
        case s_sioc:
        case s_sioc_s:
        case s_sioc_t:
        case s_skos:
        case s_skosxl:
        case s_sosa :
        case s_ssn :
        case s_time :
        case s_v :
        case s_vcard :
        case s_video :
        case s_void :
        case s_wdr :
        case s_wdrs :
        case s_website :
        case s_whatwg :
        case s_xhv :
            return ((j == 1) && (n == 0));
        case s_as :
            return ((j == 2) && (n == 0));
        case s_bibo :
            return ((j == 1) && (n == 3));
        case s_dcat :
        case s_microformats :
        case s_owl :
            if (n != 0) return false;
            return (j <= 2);
        case s_dc :
        case s_dcam :
        case s_dcmi  :
        case s_dct  :
        case s_xsd  :
            return ((j == 1) && (n < 2));
        case s_foaf :
            return ((j == 0) && (n < 100));
        case s_none :
            return true;
        case s_rdfa :
            if (j != 1) return false;
            return (n < 4);
        case s_schema :
            if ((j == 0) && (n == 0)) return true;
            if ((j > schema_major_max) || (j < 2)) return false;
            switch (j)
            {   case 2 : return n < 3;
                case 3 : return true;
                case 7 : return n < 5;
                default : return n == 0; }
        default :
            return false; } }

bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to)
{   if (v.any_flags (SV_WILDCARD)) return true;
    return does_apply < version > (v, from, to); }
