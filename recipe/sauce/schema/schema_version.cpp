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
#include "main/context.h"
#include "schema/schema_version.h"
#include "parser/html_version.h"
#include "symbol/nstr.h"
#include "utility/common.h"

struct sh_t
{   schema_version schema_;
    html_version html_; };

sh_t sh [] =  // latest first
{   { article_2018, html_jan18 },
    { article_2014, html_jan14 },
    { article_2012, html_jan12 },
    { as_2_0, html_as_2_0 },
    { as_1_0, html_as_1_0 },
    { bibo_schema, html_rdf_1_0 },
    { book_2018, html_jan18 },
    { book_2014, html_jan14 },
    { book_2012, html_jan12 },
    { creative_commons, html_cc },
    { content_schema, html_rdf_1_0 },
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
    { doap_schema, html_rdf_1_0 },
    { data_quality, html_rdf_1_0_con },
    { described_by, html_rdf_1_0 },
    { duv_schema, html_rdf_1_0_con },
    { earl_schema, html_rdf_1_0_con },
    { event_schema, html_rdf_1_0_con },
    { faux_schema, html_rdf_1_0 },
    { foaf_schema, html_rdf_1_0 },
    { frbr_schema, xhtml_1_0 },
    { good_relations, html_rdf_1_0 },
    { grddl_schema, html_rdf_1_0_con },
    { ical_schema, html_rdf_1_0_con },
    { icaltzd_schema, html_rdf_1_0_con },
    { jsonld_schema_1_1, html_jsonld_1_1 },
    { jsonld_schema_1_0, html_jsonld_1_0 },
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
    { profile_2018, html_jan18 },
    { profile_2014, html_jan14 },
    { profile_2012, html_jan12 },
    { provincial, html_rdf_1_0_con },
    { poetry_schema, html_jan18 },
    { ptr_schema, html_rdf_1_0_con },
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
    { schema_0, html_schema_0 },
    { sd_schema, html_sd },
    { sioc_schema, html_sioc },
    { sioc_services, html_sioc_s },
    { sioc_types, html_sioc_t },
    { skos_schema, html_skos },
    { skosxl_schema, html_skosxl },
    { ssn_schema, html_ssn },
    { sosa_schema, html_sosa },
    { taxo_schema, html_taxo },
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
    { xsd_1_1, html_xsd_1_1 },
    { xsd_1_0, html_xsd_1_0 },
    { error_schema, html_0 } };

typedef ::std::multimap < e_schema, sh_t* > mss_t;
mss_t mss;
::std::array < schema_version, s_error > va;

bool set_default_schema_version (const e_schema es, unsigned char mjr, unsigned char mnr)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (! is_valid_schema_version (es, mjr, mnr, NOFLAGS)) return false;
    va.at (es) = schema_version (es, mjr, mnr);
    return true; }

schema_version get_default_schema_version (const e_schema es)
{   return corresponding_schema_version (es, context.html_ver ()); }

schema_version corresponding_schema_version (const e_schema es, const html_version& v)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (es == s_none) return default_schema;
    if (! va.at (es).invalid ()) return va.at (es);
    PRESUME (! mss.empty (), __FILE__, __LINE__);
    for (mss_t::const_iterator i = mss.find (es); (i != mss.cend ()) && (i -> first == es); ++i)
    {   sh_t& x = *(i -> second);
        if (v >= x.html_)
            return x.schema_; }
    return error_schema; }

template < e_schema V > struct schema_detail
{   static bool is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
    {   return (mjr == 1) && (mnr == 0); }
    static ::std::string name (const ::std::string s, const unsigned char mjr, const unsigned char mnr)
    {   ::std::string res (s);
        res += " v";
        res += x_dot_y (mjr, mnr);
        return res; }
    static schema_version from () { return schema_version (V, 1, 0); }
    static int count () { return 1; }
    static bool faux () { return false; }
    static bool is_this_deprecated (const unsigned char , const unsigned char , const flags_t )
    {   return false; }
    static schema_version to () { return schema_version (V, 1, 0); } };

template < > bool schema_detail < s_article > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_article > :: from () { return schema_version (s_article, HTML_2012, 0); }
template < > int schema_detail < s_article > :: count () { return 4; }
template < > schema_version schema_detail < s_article > :: to () { return schema_version (s_article, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_as > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mnr != 0) return false;
    return (mjr == 2) || (mjr == 1); }
template < > schema_version schema_detail < s_as > :: from () { return schema_version (s_as, 1, 0); }
template < > int schema_detail < s_as > :: count () { return 2; }
template < > schema_version schema_detail < s_as > :: to () { return schema_version (s_as, 2, 0); }

template < > bool schema_detail < s_bibo > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   return (mjr == 1) && (mnr == 3); }
template < > schema_version schema_detail < s_bibo > :: from () { return schema_version (s_bibo, 1, 3); }
template < > schema_version schema_detail < s_bibo > :: to () { return schema_version (s_bibo, 1, 3); }

template < > bool schema_detail < s_book > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_book > :: from () { return schema_version (s_book, HTML_2012, 0); }
template < > int schema_detail < s_book > :: count () { return 4; }
template < > schema_version schema_detail < s_book > :: to () { return schema_version (s_book, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_dc > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_dc > :: from () { return schema_version (s_dc, 1, 0); }
template < > int schema_detail < s_dc > :: count () { return 2; }
template < > schema_version schema_detail < s_dc > :: to () { return schema_version (s_dc, 1, 1); }

template < > bool schema_detail < s_dcat > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_dcat > :: from () { return schema_version (s_dcat, 1, 0); }
template < > int schema_detail < s_dcat > :: count () { return 2; }
template < > schema_version schema_detail < s_dcat > :: to () { return schema_version (s_dcat, 2, 0); }

template < > bool schema_detail < s_dct > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_dct > :: from () { return schema_version (s_dct, 1, 0); }
template < > int schema_detail < s_dct > :: count () { return 2; }
template < > schema_version schema_detail < s_dct > :: to () { return schema_version (s_dct, 1, 1); }

template < > bool schema_detail < s_error > :: is_this_valid (const unsigned char , const unsigned char , const flags_t )
{   return false; }
template < > bool schema_detail < s_error > :: faux ()
{   return true; }

template < > bool schema_detail < s_faux > :: faux ()
{   return true; }

template < > bool schema_detail < s_foaf > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   return (mjr == 0) && (mnr < 100); }
template < > schema_version schema_detail < s_foaf > :: from () { return schema_version (s_foaf, 0, 1); }
template < > int schema_detail < s_foaf > :: count () { return 98; }
template < > schema_version schema_detail < s_foaf > :: to () { return schema_version (s_foaf, 0, 99); }

template < > bool schema_detail < s_jsonld > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_jsonld > :: from () { return schema_version (s_jsonld, 1, 0); }
template < > int schema_detail < s_jsonld > :: count () { return 2; }
template < > schema_version schema_detail < s_jsonld > :: to () { return schema_version (s_jsonld, 1, 1); }

template < > bool schema_detail < s_microformats > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_microformats > :: from () { return schema_version (s_microformats, 1, 0); }
template < > int schema_detail < s_microformats > :: count () { return 255; }
template < > schema_version schema_detail < s_microformats > :: to () { return schema_version (s_microformats, 2, 255); }

template < > bool schema_detail < s_music > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_music > :: from () { return schema_version (s_music, HTML_2012, 0); }
template < > int schema_detail < s_music > :: count () { return 4; }
template < > schema_version schema_detail < s_music > :: to () { return schema_version (s_music, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_none > :: is_this_valid (const unsigned char , const unsigned char , const flags_t )
{   return false; }
template < > bool schema_detail < s_none > :: faux ()
{   return true; }

template < > bool schema_detail < s_og > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2010) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_og > :: from () { return schema_version (s_og, HTML_2010, 0); }
template < > int schema_detail < s_og > :: count () { return 5; }
template < > schema_version schema_detail < s_og > :: to () { return schema_version (s_og, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_owl > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_owl > :: from () { return schema_version (s_owl, 1, 0); }
template < > int schema_detail < s_owl > :: count () { return 2; }
template < > schema_version schema_detail < s_owl > :: to () { return schema_version (s_owl, 2, 0); }

template < > bool schema_detail < s_profile > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_profile > :: from () { return schema_version (s_profile, HTML_2012, 0); }
template < > int schema_detail < s_profile > :: count () { return 4; }
template < > schema_version schema_detail < s_profile > :: to () { return schema_version (s_profile, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_rdf > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > schema_version schema_detail < s_rdf > :: from () { return schema_version (s_rdf, 1, 0); }
template < > int schema_detail < s_rdf > :: count () { return 4; }
template < > schema_version schema_detail < s_rdf > :: to () { return schema_version (s_rdf, 1, 3); }

template < > bool schema_detail < s_rdfa > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > schema_version schema_detail < s_rdfa > :: from () { return schema_version (s_rdfa, 1, 0); }
template < > int schema_detail < s_rdfa > :: count () { return 4; }
template < > schema_version schema_detail < s_rdfa > :: to () { return schema_version (s_rdfa, 1, 3); }

template < > bool schema_detail < s_schema > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t flags)
{   if (mjr > schema_major_max) return false;
    switch (mjr)
    {   case 0 :
        case 1 : return false;
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
template < > schema_version schema_detail < s_schema > :: from () { return schema_version (s_schema, 2, 0); }
template < > int schema_detail < s_schema > :: count () { return 19; }
template < > schema_version schema_detail < s_schema > :: to () { return schema_version (s_schema, 13, 0); }

template < > bool schema_detail < s_vann > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_vann > :: from () { return schema_version (s_vann, 1, 0); }
template < > int schema_detail < s_vann > :: count () { return 2; }
template < > schema_version schema_detail < s_vann > :: to () { return schema_version (s_vann, 1, 1); }

template < > bool schema_detail < s_vcard > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t f)
{   if (mnr != 0) return false;
    switch (mjr)
    {   case 1 :
        case 3 :
        case 4 : return true;
        case 2 : return (f & SV_VC_NOT2) == 0;
        default : break; }
    return false; }
template < > schema_version schema_detail < s_vcard > :: from () { return vcard_2001; }
template < > int schema_detail < s_vcard > :: count () { return 4; }
template < > bool schema_detail < s_vcard > :: is_this_deprecated (const unsigned char mjr, const unsigned char , const flags_t flags)
    {   if ((flags & SV_DEPRECATED) == SV_DEPRECATED) return true;
        return ((mjr == 4) && ((flags & SV_VC_DEP4) == SV_VC_DEP4)); }
template < > schema_version schema_detail < s_vcard > :: to () { return vcard_2014; }

template < > bool schema_detail < s_video > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_video > :: from () { return schema_version (s_video, HTML_2012, 0); }
template < > int schema_detail < s_video > :: count () { return 4; }
template < > schema_version schema_detail < s_video > :: to () { return schema_version (s_video, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_website > :: is_this_valid (const unsigned char mjr, const unsigned char , const flags_t )
{   return (mjr >= HTML_2012) && (mjr <= HTML_LATEST_YEAR); }
template < > schema_version schema_detail < s_website > :: from () { return schema_version (s_website, HTML_2012, 0); }
template < > int schema_detail < s_website > :: count () { return 4; }
template < > schema_version schema_detail < s_website > :: to () { return schema_version (s_website, HTML_LATEST_YEAR, 0); }

template < > bool schema_detail < s_xsd > :: is_this_valid (const unsigned char mjr, const unsigned char mnr, const flags_t )
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_xsd > :: from () { return schema_version (s_xsd, 1, 0); }
template < > int schema_detail < s_xsd > :: count () { return 2; }
template < > schema_version schema_detail < s_xsd > :: to () { return schema_version (s_xsd, 1, 1); }

template < e_schema V, e_schema... Vs > struct schemas : schemas < Vs... >
{   static schema_version get_corresponding (const e_schema es, const html_version& v)
    {   if (es == V) return corresponding_schema_version (es, v);
        return schemas < Vs... > :: get_corresponding (es, v); }
    static schema_version get_default (const e_schema es)
    {   return get_corresponding (es, context.html_ver ()); }
    static ::std::string name (const e_schema es)
    {   if (es == V) return schema_names.get (V, SCHEMA_NAME);
        return schemas < Vs... > :: name (es); }
    static ::std::string name (const e_schema es, const unsigned char mjr, const unsigned char mnr)
    {   if (es == V) return schema_detail < V >::name (name (es), mjr, mnr);
        return schemas < Vs... > :: name (es, mjr, mnr); }
    static schema_version from (const e_schema es)
    {   if (es == V) return schema_detail < V > :: from ();
        return schemas < Vs... > :: from (es); }
    static schema_version to (const e_schema es)
    {   if (es == V) return schema_detail < V > :: to ();
        return schemas < Vs... > :: to (es); }
    static int count (const e_schema es)
    {   if (es == V) return schema_detail < V > :: count ();
        return schemas < Vs... > :: count (es); }
    static bool faux (const e_schema es)
    {   if (es == V) return schema_detail < V > :: faux ();
        return schemas < Vs... > :: faux (es); }
    static bool is_this_deprecated (const e_schema es, const unsigned char mjr, const unsigned char mnr, const flags_t flags)
    {   if (es == V) return schema_detail < V > :: is_this_deprecated (mjr, mnr, flags);
        return schemas < Vs... > :: is_this_deprecated (es, mjr, mnr, flags); }
    static bool is_valid (const e_schema es, const unsigned char mjr, const unsigned char mnr, const flags_t flags)
    {   if (es == V) return schema_detail < V > :: is_this_valid (mjr, mnr, flags);
        return schemas < Vs... > :: is_valid (es, mjr, mnr, flags); } };

template < > struct schemas < s_error >
{   static schema_version get_corresponding (const e_schema , const html_version& )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_schema); }
    static schema_version get_default (const e_schema )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return default_schema); }
    static ::std::string name (const e_schema , const unsigned char , const unsigned char )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return "*** NO SUCH SCHEMA "); }
    static ::std::string name (const e_schema )
    {   GRACEFUL_CRASH (__FILE__, __LINE__);
        UNREACHABLE (return "*** NO SUCH SCHEMA "); }
    static schema_version from (const e_schema )
    {   return error_schema; }
    static schema_version to (const e_schema )
    {   return error_schema; }
    static int count (const e_schema )
    {   return 0; }
    static bool faux (const e_schema )
    {   return true; }
    static bool is_this_deprecated (const e_schema , const unsigned char , const unsigned char , const flags_t )
    {   return false; }
    static bool is_valid (const e_schema , const unsigned char , const unsigned char , const flags_t )
    {   return false; } };

schema_version get_first_schema_version (const e_schema es)
{   return schemas < SCHEMAS > :: from (es); }
schema_version get_last_schema_version (const e_schema es)
{   return schemas < SCHEMAS > :: to (es); }
int get_schema_version_count (const e_schema es)
{   return schemas < SCHEMAS > :: count (es); }
bool is_faux_schema (const e_schema es)
{   return schemas < SCHEMAS > :: faux (es); }

schema_version::schema_version (const html_version& v) noexcept
{   schema_version sv = corresponding_schema_version (s_schema, v);
    schema_version err (s_error, 0, 0);
    if (! sv.invalid ()) swap (sv); else swap (err); }

void schema_version::init (nitpick& DEBUGONLY (nits))
{   PRESUME (mss.empty (), __FILE__, __LINE__);
    for (int i = 0; sh [i].schema_.root () != s_error; ++i)
        mss.insert (mss_t::value_type (sh [i].schema_.root (), &sh [i]));
#ifdef _DEBUG
    for (int i = 1; i < s_error; ++i)
        if (mss.find (static_cast < e_schema > (i)) == mss.cend ())
            nits.pick (nit_missing_schema, es_catastrophic, ec_schema, "Corresponding HTML version for schema ", i, " missing");
#endif
    for (int i = 0; i < s_error; ++i) va [i] = error_schema; }

::std::string schema_version::name (const e_schema es)
{   if (is_faux_schema (es)) return "";
    return schema_names.get (es, SCHEMA_NAME); }

::std::string schema_version::name () const
{   return name (root ()); }

::std::string schema_version::report () const
{   if (root () == s_none) return "(UNKNOWN SCHEMA)";
    return schemas < SCHEMAS > :: name (root (), mjr (), mnr ()); }

::std::string schema_version::ver () const
{   if (root () == s_none) return "0.0";
    return x_dot_y_ish (mjr (), mnr ()); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_schema_version (const e_schema root, const unsigned char j, const unsigned char n, const flags_t flags) noexcept
{   return schemas < SCHEMAS > :: is_valid (root, j, n, flags); }

bool is_valid_schema_version (const schema_version& sv) noexcept
{   return schemas < SCHEMAS > :: is_valid (sv.root (), sv.mjr (), sv.mnr (), sv.flags ()); }

bool is_schema_deprecated (const e_schema root, const unsigned char mjr, const unsigned char mnr, const flags_t flags) noexcept
{   return schemas < SCHEMAS > :: is_this_deprecated (root, mjr, mnr, flags); }

bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to) MSVC_NOEXCEPT
{   if (v.any_flags (SV_WILDCARD)) return true;
    return does_apply < version > (v, from, to); }
