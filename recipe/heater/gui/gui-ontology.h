/*                                                                 ,
ssc (static site checker)
File Info
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

class ontology_t : public dialogue_t
{   wxBoxSizer* box_export_ = nullptr;
    wxBoxSizer* box_version_ = nullptr;
    wxCheckBox* check_verify_ = nullptr;
    wxCheckBox* check_export_ = nullptr;
    wxChoice* choice_version_ = nullptr;
    wxDataViewColumn* column_description_ = nullptr;
    wxDataViewColumn* column_ontology_ = nullptr;
    wxDataViewColumn* column_range_ = nullptr;
    wxDataViewColumn* column_version_ = nullptr;
    wxDataViewListCtrl* data_ontology_ = nullptr;
    wxDirPickerCtrl* pick_export_ = nullptr;
    wxStaticLine* line1_ = nullptr;
    wxStaticLine* line2_ = nullptr;
    wxStaticLine* line3_ = nullptr;
    wxStaticText* static_version_ = nullptr;
    vstr_t vid_, vont_;
    vvstr_t versions_;
    bool export_ = false;
    bool ontological_ = false;
    bool stocked_ = false;
    bool verify_ = false;
    ::boost::filesystem::path path_;
    vsv_t vsv_;
    vint_t vov_;
    void general_enable (const bool e);
    void OnExport (wxCommandEvent& e);
    void OnHelpClick (wxCommandEvent& event);
    void OnOntology (wxDataViewEvent& event);
    void OnVerify (wxCommandEvent& e);
    void OnVersion (wxCommandEvent& e);
    void restock_ontology ();
    DECLARE_CLASS (ontology_t)
    DECLARE_EVENT_TABLE ()
public:
    ontology_t () { }
    ontology_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = ONT_CAPTION);
    ~ontology_t () { }
    bool invalid () const noexcept { return dialogue_t :: invalid () || check_verify_ == nullptr || pick_export_ == nullptr || column_version_ == nullptr || choice_version_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = ONT_CAPTION);
    void CreateControls ();
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool exp () const noexcept { return export_; }
    void exp (const bool b) noexcept { export_ = b; }
    ::boost::filesystem::path path () const { return path_; }
    void path (const ::boost::filesystem::path& p) { path_ = p; }
    bool verify () const noexcept { return verify_; }
    void verify (const bool b) noexcept { verify_ = b; }
    vsv_t lvsv () const { return vsv_; }
    void lvsv (const vsv_t& v) { vsv_ = v; } };

#endif // WX
