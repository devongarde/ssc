/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
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

#ifdef WX
#include "gui/gui-dialogue.h"
#include "symbol/nstr.h"

#define ONT_CAPTION "Ontology"

class ontology_t : public d1_t < wx_ontology >
{   wxBoxSizer* box_export_ = nullptr;
    wxBoxSizer* box_mf_export_ = nullptr;
    wxBoxSizer* box_version_ = nullptr;
    wxCheckBox* check_export_ = nullptr;
    wxCheckBox* check_pretty_ = nullptr;
    wxCheckBox* check_verify_ = nullptr;
    wxCheckBox* mf_export_ = nullptr;
    wxCheckBox* mf_pretty_ = nullptr;
    wxCheckBox* mf_verify_ = nullptr;
    wxCheckBox* mf_v1_ = nullptr;
    wxCheckBox* mf_v2_ = nullptr;
    wxChoice* choice_version_ = nullptr;
    wxDataViewColumn* column_description_ = nullptr;
    wxDataViewColumn* column_ontology_ = nullptr;
    wxDataViewColumn* column_range_ = nullptr;
    wxDataViewColumn* column_version_ = nullptr;
    wxDataViewListCtrl* data_ontology_ = nullptr;
    wxDirPickerCtrl* pick_export_ = nullptr;
    wxDirPickerCtrl* pick_mf_export_ = nullptr;
    wxGridSizer* mf_grid_ = nullptr;
    wxStaticLine* base_ = nullptr;
    wxStaticLine* line2_ = nullptr;
    wxStaticLine* line3_ = nullptr;
    wxStaticText* mf_text_ = nullptr;
    wxStaticText* static_version_ = nullptr;
    vstr_t vid_, vont_;
    vvstr_t versions_;
    bool export_ = false;
    bool ontological_ = false;
    bool pretty_ = false;
    bool stocked_ = false;
    bool verify_ = false;
    bool exp_ = false, mf1_ = false, mf2_ = false, prt_ = false, vfy_ = false;
    ::boost::filesystem::path path_;
    vsv_t vsv_;
    vint_t vov_;
    void general_enable (const bool e);
    void restock_ontology ();
    void mf_enable (const bool b);
    DECLARE_CLASS (ontology_t)
    DECLARE_EVENT_TABLE ()
public:
    ontology_t () { }
    ontology_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = ONT_CAPTION);
    ~ontology_t () { }
    bool invalid () const noexcept { return check_verify_ == nullptr || pick_export_ == nullptr || pick_mf_export_ == nullptr || column_version_ == nullptr || choice_version_ == nullptr || mf_pretty_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = ONT_CAPTION);
    void CreateControls ();
    void OnExport (wxCommandEvent& e);
    void OnHelpClick (wxCommandEvent& event);
    void OnMFExport (wxCommandEvent& e);
    void OnMFVerify (wxCommandEvent& e);
    void OnOntology (wxDataViewEvent& event);
    void OnVerify (wxCommandEvent& e);
    void OnVersion (wxCommandEvent& e);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || check_verify_ == nullptr || pick_export_ == nullptr || column_version_ == nullptr || choice_version_ == nullptr; }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool exp () const noexcept { return export_; }
    void exp (const bool b) noexcept { export_ = b; }
    ::boost::filesystem::path path () const { return path_; }
    void path (const ::boost::filesystem::path& p) { path_ = p; }
    bool md_pretty () const noexcept { return pretty_; }
    void md_pretty (const bool b) noexcept { pretty_ = b; }
    bool verify () const noexcept { return verify_; }
    void verify (const bool b) noexcept { verify_ = b; }
    vsv_t lvsv () const { return vsv_; }
    void lvsv (const vsv_t& v) { vsv_ = v; }
    bool mf_exp () const noexcept { return exp_; }
    void mf_exp (const bool b) noexcept { exp_ = b; }
    bool mf_pretty () const noexcept { return prt_; }
    void mf_pretty (const bool b) noexcept { prt_ = b; }
    bool mf_verify () const noexcept { return vfy_; }
    void mf_verify (const bool b) noexcept { vfy_ = b; }
    int mf_version () const;
    void mf_version (const int n); };
#endif // WX
