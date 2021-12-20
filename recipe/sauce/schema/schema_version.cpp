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

struct sh_t
{   schema_version schema_;
    html_version html_; };

sh_t sh [] =  // latest first
{   { article_schema, html_rdf_1_0 },
    { as_schema, html_rdf_1_0_con },
    { bibo_schema, html_rdf_1_0 },
    { book_schema, html_rdf_1_0 },
    { creative_commons, html_cc },
    { content_schema, html_rdf_1_0 },
    { csvw_1_0, html_rdf_1_0_con },
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
    { jsonld_schema_1_0, html_jsonld_1_0 },
    { jsonld_schema_1_1, html_jsonld_1_1 },
    { linked_data_platform, html_rdf_1_0_con },
    { linked_data_platform, html_rdf_1_0_con },
    { licence_schema, html_rdf_1_0_con },
    { locn_schema, html_rdf_1_0_con },
    { media_resources, html_rdf_1_0_con },
    { mf_1, xhtml_1_0 },
    { mf_2, html_5_0 },
    { music_schema, html_rdf_1_0 },
    { web_annotation, html_rdf_1_0_con },
    { odrl_schema, html_rdf_1_0_con },
    { open_graph, html_rdf },
    { org_schema, html_rdf_1_0_con },
    { owl_1, html_rdf_1_0 },
    { owl_2, html_rdf_1_0_con },
    { profile_schema, html_rdf_1_0 },
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
    { vcard_schema, html_vcard },
    { video_schema, html_video },
    { void_schema, html_void },
    { wdr_schema, html_wdr },
    { wdrs_schema, html_wdrs },
    { website_schema, html_website },
    { whatwg_schema, html_whatwg },
    { xhv_schema, html_xhv },
    { xml_schema, html_xml },
    { xsd_1_0, html_xsd_1_0 },
    { xsd_1_1, html_xsd_1_1 },
    { error_schema, html_0 } };

typedef ::std::multimap < e_schema, sh_t* > mss_t;
mss_t mss;
::std::array < schema_version, s_error > va;


bool set_default_schema_version (const e_schema es, unsigned char mjr, unsigned char mnr)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (! is_valid_schema_version (es, mjr, mnr)) return false;
    va.at (es) = schema_version (es, mjr, mnr);
    return true; }

schema_version get_default_schema_version (const e_schema es)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    return corresponding_schema_version (es, context.html_ver ()); }

schema_version corresponding_schema_version (const e_schema es, const html_version& v)
{   PRESUME (es < s_error, __FILE__, __LINE__);
    if (! va [es].invalid ()) return va [es];
    PRESUME (! mss.empty (), __FILE__, __LINE__);
    for (mss_t::const_iterator i = mss.find (es); (i != mss.cend ()) && (i -> first == es); ++i)
    {   sh_t& x = *(i -> second);
        if (v >= x.html_)
            return x.schema_; }
    return error_schema; }


template < e_schema V > struct schema_detail
{   static bool is_this_valid (const unsigned char mjr, const unsigned char mnr)
    {   return (mjr == 1) && (mnr == 0); }
    static ::std::string name (const ::std::string s, const unsigned char mjr, const unsigned char mnr)
    {   ::std::string res (s);
        res += " v";
        res += ::boost::lexical_cast < ::std::string > (static_cast < int > (mjr));
        res += ".";
        res += ::boost::lexical_cast < ::std::string > (static_cast < int > (mnr));
        return res; }
    static schema_version from () { return schema_version (V, 1, 0); }
    static int count () { return 1; }
    static bool faux () { return false; }
    static schema_version to () { return schema_version (V, 1, 0); } };

template < > bool schema_detail < s_as > :: is_this_valid (const unsigned char mjr, const unsigned char )
{   return (mjr == 2) || (mjr == 0); }
template < > schema_version schema_detail < s_as > :: from () { return schema_version (s_as, 2, 0); }
template < > schema_version schema_detail < s_as > :: to () { return schema_version (s_as, 2, 0); }

template < > bool schema_detail < s_bibo > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   return (mjr == 1) && (mnr == 3); }
template < > schema_version schema_detail < s_bibo > :: from () { return schema_version (s_bibo, 1, 3); }
template < > schema_version schema_detail < s_bibo > :: to () { return schema_version (s_bibo, 1, 3); }

template < > bool schema_detail < s_dc > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_dc > :: from () { return schema_version (s_dc, 1, 0); }
template < > int schema_detail < s_dc > :: count () { return 2; }
template < > schema_version schema_detail < s_dc > :: to () { return schema_version (s_dc, 1, 1); }

template < > bool schema_detail < s_dcat > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_dcat > :: from () { return schema_version (s_dcat, 1, 0); }
template < > int schema_detail < s_dcat > :: count () { return 2; }
template < > schema_version schema_detail < s_dcat > :: to () { return schema_version (s_dcat, 2, 0); }

template < > bool schema_detail < s_dct > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_dct > :: from () { return schema_version (s_dct, 1, 0); }
template < > int schema_detail < s_dct > :: count () { return 2; }
template < > schema_version schema_detail < s_dct > :: to () { return schema_version (s_dct, 1, 1); }

template < > bool schema_detail < s_error > :: is_this_valid (const unsigned char , const unsigned char )
{   return false; }
template < > bool schema_detail < s_error > :: faux ()
{   return true; }

template < > bool schema_detail < s_faux > :: faux ()
{   return true; }

template < > bool schema_detail < s_foaf > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   return (mjr == 0) && (mnr < 100); }
template < > schema_version schema_detail < s_foaf > :: from () { return schema_version (s_foaf, 0, 1); }
template < > int schema_detail < s_foaf > :: count () { return 98; }
template < > schema_version schema_detail < s_foaf > :: to () { return schema_version (s_foaf, 0, 99); }

template < > bool schema_detail < s_jsonld > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mjr != 1) return false;
    return (mnr < 2); }
template < > schema_version schema_detail < s_jsonld > :: from () { return schema_version (s_jsonld, 1, 0); }
template < > int schema_detail < s_jsonld > :: count () { return 2; }
template < > schema_version schema_detail < s_jsonld > :: to () { return schema_version (s_jsonld, 1, 1); }

template < > bool schema_detail < s_microformats > :: is_this_valid (const unsigned char mjr, const unsigned char )
{   return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_microformats > :: from () { return schema_version (s_microformats, 1, 0); }
template < > int schema_detail < s_microformats > :: count () { return 255; }
template < > schema_version schema_detail < s_microformats > :: to () { return schema_version (s_microformats, 2, 255); }

template < > bool schema_detail < s_none > :: is_this_valid (const unsigned char , const unsigned char )
{   return false; }
template < > bool schema_detail < s_none > :: faux ()
{   return true; }

template < > bool schema_detail < s_owl > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mnr != 0) return false;
    return (mjr == 1) || (mjr == 2); }
template < > schema_version schema_detail < s_owl > :: from () { return schema_version (s_owl, 1, 0); }
template < > int schema_detail < s_owl > :: count () { return 2; }
template < > schema_version schema_detail < s_owl > :: to () { return schema_version (s_owl, 2, 0); }

template < > bool schema_detail < s_rdf > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > schema_version schema_detail < s_rdf > :: from () { return schema_version (s_rdf, 1, 0); }
template < > int schema_detail < s_rdf > :: count () { return 4; }
template < > schema_version schema_detail < s_rdf > :: to () { return schema_version (s_rdf, 1, 3); }

template < > bool schema_detail < s_rdfa > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if (mjr != 1) return false;
    return (mnr < 4); }
template < > schema_version schema_detail < s_rdfa > :: from () { return schema_version (s_rdfa, 1, 0); }
template < > int schema_detail < s_rdfa > :: count () { return 4; }
template < > schema_version schema_detail < s_rdfa > :: to () { return schema_version (s_rdfa, 1, 3); }

template < > bool schema_detail < s_schema > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
{   if ((mjr > schema_major_max) || (mjr < 2)) return false;
    switch (mjr)
    {   case 2 : return (mnr < 3);
        case 3 : return (mnr < 10);
        case 7 : return (mnr < 5);
        default : break; }
    return (mnr == 0); };
template < > schema_version schema_detail < s_schema > :: from () { return schema_version (s_schema, 2, 0); }
template < > int schema_detail < s_schema > :: count () { return 19; }
template < > schema_version schema_detail < s_schema > :: to () { return schema_version (s_schema, 13, 0); }

template < > bool schema_detail < s_xsd > :: is_this_valid (const unsigned char mjr, const unsigned char mnr)
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
    static bool is_valid (const e_schema es, const unsigned char mjr, const unsigned char mnr)
    {   if (es == V) return schema_detail < V > :: is_this_valid (mjr, mnr);
        return schemas < Vs... > :: is_valid (es, mjr, mnr); } };

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
    static bool is_valid (const e_schema , const unsigned char , const unsigned char )
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
{   return schemas < SCHEMAS > :: name (root (), mjr (), mnr ()); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_schema_version (const e_schema root, const unsigned char j, const unsigned char n) noexcept
{   return schemas < SCHEMAS > :: is_valid (root, j, n); }

bool is_valid_schema_version (const schema_version& sv) noexcept
{   return schemas < SCHEMAS > :: is_valid (sv.root (), sv.mjr (), sv.mnr ()); }

bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to) MSVC_NOEXCEPT
{   if (v.any_flags (SV_WILDCARD)) return true;
    return does_apply < version > (v, from, to); }
