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
#include "gui/gui-listedit.h"

#define SITE_CAPTION "Site"

class site_t : public d1_t < wx_site >
{   wxCheckBox* article_ = nullptr;
    wxCheckBox* body_ = nullptr;
    wxCheckBox* check_example_ = nullptr;
    wxCheckBox* check_external_ = nullptr;
    wxCheckBox* check_forwarded_ = nullptr;
    wxCheckBox* check_id_ = nullptr;
    wxCheckBox* check_internal_ = nullptr;
    wxCheckBox* check_local_ = nullptr;
    wxCheckBox* check_once_ = nullptr;
    wxCheckBox* check_revoke_ = nullptr;
    wxCheckBox* check_special_ = nullptr;
    wxCheckBox* main_ = nullptr;
    wxCheckBox* output_ = nullptr;
    wxDirPickerCtrl* dir_default_ = nullptr;
    wxStaticText* stat_default_ = nullptr; 
    wxFilePickerCtrl* file_ = nullptr;
    wxGridSizer* grid_ = nullptr; 
    wxStaticLine* base_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticLine* twixt_ = nullptr;
    wxStaticText* wot_ = nullptr;  
    ::boost::filesystem::path path_;
    bool art_ = false, bod_ = false, mai_ = false;
    bool example_ = false, external_ = false, forwarded_ = false, id_ = false, internal_ = false, local_ = false, once_ = false, revoke_ = false, special_ = false;
    listedit_manager domain_ = listedit_manager (button_site_add, button_site_erase, button_site_rename, file_site_name, list_site_ext, text_site_ext);
    ::boost::filesystem::path def_;
    vstr_t site_;
    void enable_corpus (const bool b);
    DECLARE_CLASS (site_t)
    DECLARE_EVENT_TABLE ()
public:
    site_t () { }
    site_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    ~site_t () { }
    bool invalid () const noexcept { return domain_.invalid () || dir_default_ == nullptr || (panel_ == nullptr) || (grid_ == nullptr) || (check_id_ == nullptr) || (grid_ == nullptr) || (file_ == nullptr) || (article_ == nullptr) || (body_ == nullptr) || (main_ == nullptr);; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    void CreateControls ();
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnExternal (wxCommandEvent& e);
    void OnHelpClick (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    void OnInternal (wxCommandEvent& e);
    void OnOutput (wxCommandEvent& e);
    void OnRename (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || invalid (); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void def (const ::boost::filesystem::path& d) { def_ = d; }
    const ::boost::filesystem::path& def () const { return def_; }
    void site (const vstr_t& s) { site_ = s; }
    const vstr_t& site () const { return site_; }
    bool example () const noexcept { return example_; }
    void example (const bool b) noexcept { example_ = b; }
    bool external () const noexcept { return external_; }
    void external (const bool b) noexcept { external_ = b; }
    bool forwarded () const noexcept { return forwarded_; }
    void forwarded (const bool b) noexcept { forwarded_ = b; }
    bool id () const noexcept { return id_; }
    void id (const bool b) noexcept { id_ = b; }
    bool inter () const noexcept { return internal_; }
    void inter (const bool b) noexcept { internal_ = b; }
    bool local () const noexcept { return local_; }
    void local (const bool b) noexcept { local_ = b; }
    bool once () const noexcept { return once_; }
    void once (const bool b) noexcept { once_ = b; }
    bool revoke () const noexcept { return revoke_; }
    void revoke (const bool b) noexcept { revoke_ = b; }
    bool special () const noexcept { return special_; }
    void special (const bool b) noexcept { special_ = b; }
    ::boost::filesystem::path folder () const { return path_; }
    void folder (const ::boost::filesystem::path& p) { path_ = p; }
    bool article () const noexcept { return art_; }
    void article (const bool b) noexcept { art_ = b; }
    bool body () const noexcept { return bod_; }
    void body (const bool b) noexcept { bod_ = b; }
    bool main () const noexcept { return mai_; }
    void main (const bool b) noexcept { mai_ = b; } };
#endif // WX
