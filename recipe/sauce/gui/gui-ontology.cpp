/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

#include "main/standard.h"

#ifdef WX
#include "gui/gui-app.h"
#include "gui/gui-ontology.h"
#include "utility/filesystem.h"
#include "ontology/ontology_version.h"

#define ONT_STYLE   DEF_STYLE
#define ONT_X       100
#define ONT_Y       100
#define ONT_WIDTH   500
#define ONT_HEIGHT  460

BEGIN_EVENT_TABLE (ontology_t, d1_t)
  EVT_BUTTON (wxID_HELP, ontology_t::OnHelpClick)
  EVT_CHECKBOX (check_export, ontology_t::OnExport)
  EVT_CHECKBOX (check_verify, ontology_t::OnVerify)
  EVT_CHECKBOX (check_mf_export, ontology_t::OnMFExport)
  EVT_CHECKBOX (check_mf_verify, ontology_t::OnMFVerify)
  EVT_CHOICE (choice_ontology_version, ontology_t::OnVersion)
  EVT_DATAVIEW_SELECTION_CHANGED (list_ontology, ontology_t::OnOntology)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (ontology_t, d1_t)

#define VERSION_COLUMN	2

#define DPV_X_SH_2XX(XXX) \
    dpv_##XXX##_2_0, dpv_##XXX##_2_1, dpv_##XXX##_2_2, dpv_##XXX##_2_3
#define DPV_X_VSV80(XXX) \
    dpv_##XXX##_0_8_0, dpv_##XXX##_0_8_1, dpv_##XXX##_0_8_2, dpv_##XXX##_0_9, dpv_##XXX##_1_0
#define DPV_X_VSV50(XXX) \
    dpv_##XXX##_0_5, dpv_##XXX##_0_6, dpv_##XXX##_0_7, DPV_X_VSV80 (XXX)
#define DPV_X_VSV40(XXX) \
    dpv_##XXX##_0_4_0, dpv_##XXX##_0_4_1, dpv_##XXX##_0_4_2, DPV_X_VSV50 (XXX)
#define DPV_X_80_PLUS(XXX) \
    DPV_X_VSV80 (XXX), DPV_X_SH_2XX (XXX)
#define DPV_X_40_PLUS(XXX) \
    DPV_X_VSV40 (XXX), DPV_X_SH_2XX (XXX)
#define VSV_LIST \
    adms_1_0, adms_2_0, \
    article_2012, article_2014, article_2018, \
    as_1_0, as_2_0, \
    bfo_2020, bfo_2_0, \
    bibo_schema, \
    biro_schema, \
    book_2012, book_2014, book_2018, \
    cito_schema, \
    cnt_schema, \
    common_tag, \
    content_schema, \
    croissant_0_2, croissant_0_3, croissant_0_4, croissant_0_6, croissant_0_8, \
        croissant_1_0, croissant_1_1, croissant_1_2, croissant_1_3, croissant_1_4,  croissant_1_5, croissant_1_6, croissant_1_7, croissant_1_8, croissant_1_9, \
            croissant_1_10, croissant_1_11, croissant_1_12, croissant_1_13, croissant_1_14, croissant_1_15, croissant_1_16, croissant_1_17, croissant_1_18, croissant_1_19, \
            croissant_1_20, croissant_1_21, croissant_1_22,  \
        croissant_1_100, croissant_1_101, \
    creative_commons, \
    crs2_schema, \
    csvw_schema, \
    daq_schema, \
    data_catalogue_1, data_catalogue_2, data_catalogue_3, \
    data_cube, \
    data_quality, \
    data_vocabulary, \
    dbd_schema, \
    dbo_schema, \
    dbp_owl_schema, \
    dbp_schema, \
    dbr_schema, \
    dc_1_0, dc_1_1, \
    dcam, \
    dcmi, \
    described_by, \
    disco_schema, \
    doap_schema, \
    dpv_0_1, dpv_0_2, dpv_0_3, dpv_0_4_0, dpv_0_4_1, dpv_0_4_2, dpv_0_5, dpv_0_6, dpv_0_7, dpv_0_8_0, \
        dpv_0_8_1, dpv_0_8_2, dpv_0_9, dpv_1_0, dpv_2_0, dpv_2_1, dpv_2_2, dpv_2_3, dpv_2_4, \
    DPV_X_SH_2XX (ai), \
    DPV_X_SH_2XX (eu_aiact), \
    DPV_X_SH_2XX (eu_dga), \
    dpv_eu_ehds_2_1, \
    DPV_X_SH_2XX (eu_gdpr), \
    DPV_X_SH_2XX (eu_nis2), \
    DPV_X_SH_2XX (eu_rights), \
    DPV_X_VSV40 (gdpr), dpv_gdpr_0_3, dpv_gdpr_0_2, dpv_gdpr_0_1, \
    DPV_X_SH_2XX (just), \
    DPV_X_VSV50 (legal), \
    dpv_legal_at_2_1, \
    dpv_legal_be_2_1, \
    dpv_legal_bg_2_1, \
    dpv_legal_cy_2_1, \
    dpv_legal_cz_2_1, \
    DPV_X_SH_2XX (legal_de), \
    dpv_legal_dk_2_1, \
    dpv_legal_ee_2_1, \
    dpv_legal_es_2_1, \
    DPV_X_SH_2XX (legal_eu), \
    dpv_legal_fi_2_1, \
    dpv_legal_fr_2_1, \
    DPV_X_SH_2XX (legal_gb), \
    dpv_legal_gr_2_1, \
    dpv_legal_hr_2_1, \
    dpv_legal_hu_2_1, \
    DPV_X_SH_2XX (legal_ie), \
    DPV_X_SH_2XX (legal_in), \
    dpv_legal_is_2_1, \
    dpv_legal_it_2_1, \
    dpv_legal_li_2_1, \
    dpv_legal_lt_2_1, \
    dpv_legal_lu_2_1, \
    dpv_legal_lv_2_1, \
    dpv_legal_mt_2_1, \
    dpv_legal_nl_2_1, \
    dpv_legal_no_2_1, \
    dpv_legal_pl_2_1, \
    dpv_legal_pt_2_1, \
    dpv_legal_ro_2_1, \
    dpv_legal_se_2_1, \
    dpv_legal_sl_2_1, \
    dpv_legal_sk_2_1, \
    DPV_X_SH_2XX (legal_us), \
    DPV_X_SH_2XX (loc), \
    dpv_nace_schema, \
    dpv_p7012_2_1, \
    DPV_X_40_PLUS (pd), \
    DPV_X_VSV80 (rights), \
    DPV_X_80_PLUS (risk), \
    dpv_s_edu_2_1, \
    dpv_s_fin_2_1, \
    dpv_s_hth_2_1, \
    dpv_s_inf_2_1, \
    dpv_s_law_2_1, \
    dpv_s_ps_2_1, \
    DPV_X_80_PLUS (tech), \
    dublin_core_terms_1_0, dublin_core_terms_1_1, \
    duv_schema, \
    earl_schema, \
    error_schema, \
    event_schema, \
    example_schema, \
    exif_1_0, exif_1_1, exif_2_0, exif_2_1, exif_2_2, exif_2_21, exif_2_3, exif_2_31, exif_2_32, exif_3_0, \
    exifex_2_21, exifex_2_3, exifex_2_31, exifex_2_32, exifex_3_0, \
    fabio_schema, \
    faux_schema, \
    foaf_schema, \
    frbr_schema, \
    good_relations, \
    grddl_schema, \
    gs1_0, gs1_1, gs1_2, gs1_3, gs1_4, gs1_5, gs1_6, gs1_7, gs1_8, gs1_9, gs1_10, gs1_11, gs1_16, \
    ical_schema, \
    icaltzd_schema, \
    jsonld_ontology_1_0, jsonld_ontology_1_1, \
    licence_schema, \
    linked_data_platform, \
    locn_schema, \
    media_resources, \
    mf_1, mf_2, mf_all, \
    music_2012, music_2014, music_2018, \
    odrl_schema, \
    open_graph_2010, open_graph_2012, open_graph_2014, open_graph_2018, \
    org_schema, \
    owl_1, owl_2, \
    pam_1_3, pam_2_0, pam_3_0, \
    pamp_3_0, pamp_3_1, \
    pcm_3_1, \
    pcmm_3_0, pcmm_3_1, \
    pcv_1_0, pcv_2_0, \
    pdf_schema, \
    photoshop_schema, \
    pim_1_0, pim_1_2, pim_2_0, pim_3_0, pim_3_1, \
    pmi_3_0, pmi_3_1, \
    poetry_ontology_1_0, poetry_ontology_1_1, \
    prism_1_0, prism_1_1, prism_1_2, prism_1_3, prism_2_0, prism_2_1, prism_3_0, prism_3_1, \
    prism_ad_3_0, prism_ad_3_1, \
    prl_1_0, prl_1_2, prl_1_3, prl_2_0, prl_2_1, \
    prm_3_0, prm_3_1, \
    profile_2012, profile_2014, profile_2018, \
    provincial, \
    prs_3_1, \
    psv_1_0, \
    ptr_schema, \
    pur_2_1, pur_3_0, \
    rai_1_3, rai_1_4, rai_1_5, rai_1_6, rai_1_7, rai_1_8, rai_1_9, rai_1_10, rai_1_11, rai_1_12, rai_1_13, rai_1_14, rai_1_15, rai_1_16, rai_1_17, \
        rai_1_18, rai_1_19, rai_1_20, rai_1_21, rai_1_21, rai_1_100, \
    rdf_1_0_schema, rdf_1_1_1_schema, rdf_1_1_2_schema, rdf_1_1_3_schema, \
    rdfa_1_0_schema, rdfa_1_1_1_schema, rdfa_1_1_2_schema, rdfa_1_1_3_schema, \
    rdfg_schema, \
    rdfs_schema, \
    review_schema, \
    rif_schema, \
    role_schema, \
    rr_schema, \
    schema_jun11, schema_jul11, schema_aug11,  schema_sep11, schema_oct11, schema_nov11, schema_dec11, schema_jan12, schema_feb12, \
            schema_mar12, schema_apr12, \
        schema_0_91, schema_0_93, schema_0_94, schema_0_95, schema_0_96, schema_0_97, schema_0_98, schema_0_99, \
        schema_1_0A, schema_1_0B, schema_1_0C, schema_1_0D, schema_1_0E, schema_1_0F, \
        schema_1_1, schema_1_2, schema_1_3, schema_1_4, schema_1_5, schema_1_6, schema_1_7, schema_1_8, schema_1_9, schema_1_91, \
            schema_1_92, schema_1_93, \
        schema_2_0, schema_2_1, schema_2_2, schema_3_0, schema_3_1, schema_3_2, schema_3_3, schema_3_4, schema_3_5, schema_3_6, \
            schema_3_7, schema_3_8, schema_3_9, \
        schema_4, schema_5, schema_6, schema_7_00, schema_7_01, schema_7_02, schema_7_03, schema_7_04, schema_8, schema_9, \
        schema_10, schema_11, schema_11_01, schema_12, schema_13, schema_14, schema_15, schema_16, schema_17, schema_18, schema_19, \
        schema_20, schema_21, schema_22, schema_23, schema_24, schema_25, schema_26, schema_27, schema_27_01, schema_27_02, \
        schema_28_0, schema_28_1, schema_29_0, schema_29_1, schema_29_2, schema_29_3, schema_29_4, schema_29_5, schema_30_0, \
    sd_schema, \
    sioc_schema, \
    sioc_services, \
    sioc_types, \
    skos_schema, \
    skosxl_schema, \
    sosa_schema, \
    spdx_1_0, spdx_1_1, spdx_1_2, spdx_2_0, spdx_2_1, spdx_2_2, spdx_2_3, \
    spl_1_0, \
    ssn_schema, \
    svd_1_0, \
    svdu_1_0, \
    svl_1_0, \
    svpr_1_0, \
    svpu_1_0, \
    svr_1_0, \
    taxo_schema, \
    tiff_schema, \
    time_schema, \
    vann_1_0, vann_1_1, \
    vcard_2001, vcard_2006, vcard_2010, vcard_2014, \
    video_2012, video_2014, video_2018, \
    void_schema, \
    wdr_schema, \
    wdrs_schema, \
    web_annotation, \
    website_2012, website_2014, website_2018, \
    whatwg_schema, \
    wikidata_schema, \
    xhv_schema, \
    xml_schema, \
    xmp_bj, \
    xmp_dm, \
    xmp_g, \
    xmp_gimg, \
    xmp_idq, \
    xmp_mm, \
    xmp_rights, \
    xmp_schema, \
    xmp_stdim, \
    xmp_stevt, \
    xmp_stfnt, \
    xmp_stjob, \
    xmp_stref, \
    xmp_stver, \
    xmp_tpg, \
    xsd_1_0, xsd_1_1, \
    default_ontology

vsv_u ontology_t :: vsv_u_;

ontology_t :: ontology_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (ONT_X, ONT_Y), wxSize (ONT_WIDTH, ONT_HEIGHT))
{	init ();
    Create (mummy, id, caption); } 

void ontology_t :: init ()
{	if (vsv_u_.get () == nullptr)
        vsv_u_ = vsv_u (new vsv_t ({ VSV_LIST })); }

bool ontology_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (ONT_X, ONT_Y), wxSize (ONT_WIDTH, ONT_HEIGHT), ONT_STYLE)) return false;
    CreateControls ();
    return true; }

void ontology_t :: create_controls (wxWindow *parent)
{	const bool d (parent == this);
    if (vsv_.empty ())
        vsv_ = *vsv_u_;
    if (vov_.empty ())
        vov_.resize (s_faux);
    if (vont_.empty ())
    {	vont_.resize (s_faux);
        vid_.resize (s_faux);
        for (int i = s_none + 1; i < s_faux; ++i)
        {   const e_ontology es = static_cast < e_ontology > (i);
            const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
            const ::std::string desc (ontology_names.get (es, ONTOLOGY_DESCRIPTION));
            if (desc.empty () || compare_no_case (naam, desc))
            {	vid_.at (i) = naam.c_str ();
                vont_.at (i) = "-"; }
            else 
            {	vid_.at (i) = naam.c_str ();
                vont_.at (i) = desc.c_str (); } } }
    if (versions_.empty ())
    {	versions_.resize (s_faux);
        for (vsv_t::const_iterator i = vsv_.cbegin (); i != vsv_.cend (); ++i)
        {	const e_ontology o = i -> root ();
            if (o < s_faux)
                versions_.at (o).push_back (i -> ver ()); } }

    check_verify_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_verify, "Verify known &ontologies", wxDefaultPosition, wxDefaultSize, 0));
    if (check_verify_ != nullptr)
        box_ -> Add (check_verify_, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    data_ontology_ = GSL_OWNER (wxDataViewListCtrl) (new wxDataViewListCtrl (parent, list_ontology, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE));
    if (data_ontology_ != nullptr)
    {	data_ontology_ -> SetMinSize (wxSize (-1, 175));
        column_ontology_ = data_ontology_ -> AppendTextColumn ("Name", wxDATAVIEW_CELL_INERT, 60, static_cast < wxAlignment > (wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
        if (column_ontology_ != nullptr)
        {	column_description_ = data_ontology_ -> AppendTextColumn ("Description", wxDATAVIEW_CELL_INERT, d ? 250 : 130, static_cast < wxAlignment > (wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
            if (column_description_ != nullptr)
            {	column_range_ = data_ontology_ -> AppendTextColumn ("Version", wxDATAVIEW_CELL_INERT, 60, static_cast < wxAlignment > (wxALIGN_CENTRE_HORIZONTAL), wxDATAVIEW_COL_RESIZABLE);
                if (column_range_ != nullptr)
                {	column_version_ = data_ontology_ -> AppendTextColumn ("Range", wxDATAVIEW_CELL_INERT, 80, static_cast < wxAlignment > (wxALIGN_CENTRE_HORIZONTAL), wxDATAVIEW_COL_RESIZABLE);
                    if (column_version_ != nullptr) box_ -> Add (data_ontology_, 0, wxALL | wxEXPAND, 5); } } } }

    box_version_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_version_ != nullptr)
    {	static_version_	= GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Presume version:", wxDefaultPosition, wxDefaultSize, 0));
        if (static_version_ != nullptr)
        {	static_version_ -> Wrap (-1);
            box_version_ -> Add (static_version_, 0, wxALIGN_CENTER_VERTICAL, 5);
            wxString ont [] = { "-" };
            choice_version_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_ontology_version, wxDefaultPosition, wxSize (100, -1), 1, ont, 0));
            if (choice_version_ != nullptr)
            {	choice_version_ -> SetSelection (0);
                box_version_ -> Add (choice_version_, 0, wxALL, 5);
                box_ -> Add (box_version_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }

    line3_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line3_ != nullptr)
        box_ -> Add (line3_, 0, wxEXPAND | wxALL, 5);

    box_export_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_export_ != nullptr)
    {	check_export_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_export, "Export to", wxDefaultPosition, wxDefaultSize, 0));
        if (check_export_ != nullptr)
        {	box_export_ -> Add (check_export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5);
            pick_export_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (parent, wxID_ANY, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
            if (pick_export_ != nullptr)
                box_export_ -> Add (pick_export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5);
                check_pretty_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_verify, "Pretty export", wxDefaultPosition, wxDefaultSize, 0));
                    if (check_pretty_ != nullptr)
                    {	box_ -> Add (box_export_, 0, wxALIGN_CENTER_HORIZONTAL, 5);
                        box_ -> Add (check_pretty_, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5); } } }

    line2_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line2_ != nullptr)
        box_ -> Add (line2_, 0, wxEXPAND | wxALL, 5);

    mf_verify_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_mf_verify, "Verify &microformats", wxDefaultPosition, wxDefaultSize, 0));
    if (mf_verify_ != nullptr)
        box_ -> Add (mf_verify_, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    mf_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
    if (mf_grid_ != nullptr)
    {	mf_v1_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Version &1", wxDefaultPosition, wxDefaultSize, 0));
        if (mf_v1_ != nullptr)
        {	mf_grid_ -> Add (mf_v1_, 0, wxALIGN_RIGHT | wxALL, 5);
            mf_v2_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Version &2", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
            if (mf_v2_ != nullptr)
            {	mf_grid_ -> Add (mf_v2_, 0, wxALL, 5);
                mf_pretty_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Pretty export", wxDefaultPosition, wxDefaultSize, 0));
                if (mf_pretty_ != nullptr)
                {	mf_grid_ -> Add (mf_pretty_, 0, wxALL, 5);
                    box_ -> Add (mf_grid_, 0, wxEXPAND | wxALL, 5); } } } }

    box_mf_export_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_mf_export_ != nullptr)
    {	mf_export_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_mf_export, "Export to", wxDefaultPosition, wxDefaultSize, 0));
        if (mf_export_ != nullptr)
        {	box_mf_export_ -> Add (mf_export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5);
            pick_mf_export_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (parent, wxID_ANY, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
            if (pick_mf_export_ != nullptr)
                box_mf_export_ -> Add (pick_mf_export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5);
                box_ -> Add (box_mf_export_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } }

    base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
        box_ -> Add (base_, 0, wxEXPAND | wxALL, 5); }

void ontology_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void ontology_t :: general_enable (const bool e)
{	check_export_ -> Enable (e);
    choice_version_ -> Enable (e);
    data_ontology_ -> Enable (e);
    static_version_ -> Enable (e);
    const bool ex = e && check_export_ -> IsChecked ();
    pick_export_ -> Enable (ex);
    check_pretty_ -> Enable (ex); }

void ontology_t :: mf_enable (const bool b)
{	if (invalid ()) return;
    mf_export_ -> Enable (b);
    mf_v1_ -> Enable (b);
    mf_v2_ -> Enable (b);
    const bool ex = b && check_export_ -> IsChecked ();
    mf_pretty_ -> Enable (ex);
    pick_mf_export_ -> Enable (ex); }

void ontology_t :: OnExport (wxCommandEvent& )
{	if (invalid ()) return;
    const bool e = check_export_ -> IsChecked ();
    check_pretty_ -> Enable (e);
    pick_export_ -> Enable (e); }

void ontology_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_ontology); }

void ontology_t :: OnMFExport (wxCommandEvent& )
{	if (invalid ()) return;
    const bool e = mf_export_ -> IsChecked ();
    mf_pretty_ -> Enable (e);
    pick_mf_export_ -> Enable (e); }

void ontology_t :: OnMFVerify (wxCommandEvent& )
{	if (invalid ()) return;
    mf_enable (mf_verify_ -> IsChecked ()); }

void ontology_t :: OnOntology (wxDataViewEvent& )
{   if (invalid ()) return;
    choice_version_ -> Clear ();
    const int l = data_ontology_ -> GetSelectedRow ();
    if (l == wxNOT_FOUND)
        choice_version_ -> Append ("");
    else
    {	const e_ontology o = static_cast < e_ontology > (l+1);
        if (versions_.at (o).empty ()) choice_version_ -> Append ("-");
        else if (versions_.at (o).size () == 1)
        {	const wxString val = data_ontology_ -> GetTextValue (l, VERSION_COLUMN);
            choice_version_ -> Append (val); }
        else
        {	const wxString val = data_ontology_ -> GetTextValue (l, VERSION_COLUMN);
            ::std::size_t sel = 0;
            for (::std::size_t i = 0; i < versions_.at (o).size (); ++i)
            {	const wxString ver = versions_.at (o).at (i);
                if (ver == val) sel = i;
                choice_version_ -> Append (ver); }
            choice_version_ -> SetSelection (GSL_NARROW_CAST < int > (sel));
            choice_version_ -> Enable (true);
            static_version_ -> Enable (true);
            vov_.at (o) = GSL_NARROW_CAST < int > (sel);
            ontological_ = true;
            return; }
        vov_.at (o) = 0; }
    choice_version_ -> SetSelection (0); 
    choice_version_ -> Enable (false);
    static_version_ -> Enable (false);
    ontological_ = false; }

void ontology_t :: OnVerify (wxCommandEvent& )
{	if (invalid ()) return;
    general_enable (check_verify_ -> IsChecked ()); }

void ontology_t :: OnVersion (wxCommandEvent& )
{   if (invalid ()) return;
    const int v = choice_version_ -> GetSelection ();
    if (v != wxNOT_FOUND)
    {	wxString ver = choice_version_ -> GetString (v);
        const int o = data_ontology_ -> GetSelectedRow ();
        data_ontology_ -> SetTextValue (ver, o, VERSION_COLUMN); } }

bool ontology_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    check_export_ -> SetValue (export_);	
    check_pretty_ -> SetValue (pretty_);
    check_verify_ -> SetValue (verify_);
    if (path_.empty ()) path_ = get_working_directory ();
    pick_export_ -> SetPath (path_.c_str ());	
    restock_ontology ();
    general_enable (verify_);	
    mf_export_ -> SetValue (exp_);	
    mf_pretty_ -> SetValue (prt_);	
    mf_verify_ -> SetValue (vfy_);	
    mf_v1_ -> SetValue (mf1_);	
    mf_v2_ -> SetValue (mf2_);	
    mf_enable (mf_verify_ -> IsChecked ());
    return true; }

bool ontology_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    export_ = check_export_ -> GetValue ();	
    pretty_ = check_pretty_ -> GetValue ();
    verify_ = check_verify_ -> GetValue ();
    path_ = ::boost::filesystem::path (pick_export_ -> GetPath ().c_str ());	
    exp_ = mf_export_ -> GetValue ();	
    vfy_ = mf_verify_ -> GetValue ();	
    prt_ = mf_pretty_ -> GetValue ();	
    mf1_ = mf_v1_ -> GetValue ();	
    mf2_ = mf_v2_ -> GetValue ();	
    return true; }

void ontology_t :: restock_ontology ()
{	if (invalid ()) return;
    if (stocked_)
    {	data_ontology_ -> DeleteAllItems ();
        stocked_ = false; }
    for (int i = 1; i < s_faux; ++i)
    {	vov_.at (i) = -1;
        wxVector < wxVariant > item;
        item.push_back (vid_.at (i).c_str ());
        item.push_back (vont_.at (i).c_str ());
        if (versions_.at (i).empty ())
        {	item.push_back ("-");	
            item.push_back ("-"); }
        else
        {	::std::string vs = * (versions_.at (i).cbegin ());
            ::std::string l;
            if (versions_.at (i).size () == 1) l = vs;
            else
            {	if (versions_.at (i).size () == 2) vs += ", ";
                else vs += " - ";
                const vstr_t& ffs = versions_.at (i);
                vstr_t::const_iterator ij = ffs.cend ();
                l = *(--ij);
                vs += l; }	
            item.push_back (l.c_str ());
            item.push_back (vs.c_str ());
            vov_.at (i) = GSL_NARROW_CAST < int > (versions_.at (i).size () - 1); }
        data_ontology_ -> AppendItem (item); }
    stocked_ = true; }

int ontology_t :: mf_version () const
{	int res = 0;
    if (mf1_) res += 1;
    if (mf2_) res += 2;
    return res; }

void ontology_t :: mf_version (const int n)
{	switch (n)
    {	case 1 : mf1_ = true; mf2_ = false; break;	
        case 2 : mf1_ = false; mf2_ = true; break;	
        case 3 : mf1_ = true; mf2_ = true; break;	
        default : mf1_ = mf2_ = false; break; } }

bool ontology_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void ontology_t :: load_from_context (const context_t& c)
{	verify (c.ontology ());
    md_pretty (c.md_pretty ());
    exp (c.md_export ());
    path (c.export_root ());
    mf_version (c.mf_version ());
    mf_exp (c.mf_export ());
    mf_pretty (c.mf_pretty ());
    mf_verify (c.mf_verify ());
    lvsv (*vsv_u_); }

void ontology_t :: save_to_context (context_t& c) const
{   c.export_root (path ().string ());
    c.md_pretty (md_pretty ());
    c.md_export (exp ());
    c.ontology (verify ());
    c.mf_version (GSL_NARROW_CAST < const unsigned char > (mf_version () & 0x0F));
    c.mf_export (mf_exp ());
    c.mf_pretty (mf_pretty ());
    c.mf_verify (mf_verify ());
    *vsv_u_ = lvsv (); }

#endif // WX
