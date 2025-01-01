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

#define VALID_CAPTION "Validation and Virtual"

class vv_t : public d1_t < wx_valid >
{   wxBoxSizer* box_for_ = nullptr;
    wxChoice* choice_for_ = nullptr;
    wxDirPickerCtrl* dir_ontology_ = nullptr;
    wxDirPickerCtrl* dir_folder_ = nullptr;
    wxDirPickerCtrl* dir_shadow_ = nullptr;
    wxGridSizer* grid_base_ = nullptr;
    wxGridSizer* grid_virt_ = nullptr;
    wxStaticLine* line_valid_ = nullptr;
    wxStaticText* stat_for_ = nullptr;
    wxStaticText* stat_ontology_ = nullptr;
    wxStaticText* stat_folder_ = nullptr;
    wxStaticText* stat_shadow_ = nullptr;
    listedit_manager val_ = listedit_manager (button_validation_add, button_validation_erase, button_validation_rename, file_validation_name, list_validation, text_validation);
    listedit_manager virt_ = listedit_manager (button_virtual_add, button_virtual_erase, button_virtual_rename, file_virtual_name, list_virtual, text_virtual);
    vstr_t virts_;
    vbp_t export_, phys_, shadow_;
    vvstr_t vvfix_, vvextra_;
    void populate ();
    void create_virtual_dir_controls (wxWindow *parent, wxGridSizer* grid, wxStaticText*& stat, wxDirPickerCtrl*& dir, const char* const stattxt);
    void en_virt ();
    DECLARE_CLASS (vv_t)
    DECLARE_EVENT_TABLE ()
public:
    vv_t () { }
    vv_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    ~vv_t () { }
    bool invalid () const noexcept { return virt_.invalid () || val_.invalid () || (choice_for_ == nullptr) || (dir_ontology_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    void CreateControls ();
    void OnChoice (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void OnValAdd (wxCommandEvent& event);
    void OnValErase (wxCommandEvent& event);
    void OnValRename (wxCommandEvent& event);
    void OnValSelect (wxCommandEvent& event);
    void OnValText (wxCommandEvent& event);
    void OnValImpatience (wxCommandEvent& event);
    void OnVirtAdd (wxCommandEvent& event);
    void OnVirtErase (wxCommandEvent& event);
    void OnVirtRename (wxCommandEvent& event);
    void OnVirtSelect (wxCommandEvent& event);
    void OnVirtText (wxCommandEvent& event);
    void OnVirtImpatience (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || (choice_for_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const; };

#endif // WX
