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
#include "main/context.h"
#include "gui/gui-dialogue.h"
#include "gui/gui-listedit.h"

#define GEN_CAPTION "general"

class general_t : public d1_t < wx_general >
{   wxBoxSizer* box_check_ = nullptr;
    wxBoxSizer* box_config_ = nullptr;
    wxBoxSizer* box_max_ = nullptr;
    wxBoxSizer* box_output_ = nullptr;
    wxBoxSizer* box_persist_ = nullptr;
#ifndef NO_FRED
    wxBoxSizer* box_fred_ = nullptr;
    wxCheckBox* check_fred_ = nullptr;   
#endif // NO_FRED
    wxCheckBox* check_class_ = nullptr;   
    wxCheckBox* check_max_ = nullptr;   
    wxCheckBox* check_other_ = nullptr;   
    wxCheckBox* check_persist_ = nullptr;   
    wxCheckBox* check_rdfa_ = nullptr;   
    wxCheckBox* check_vcs_ = nullptr;
    wxDirPickerCtrl* dir_config_ = nullptr;
    wxFilePickerCtrl* pick_persist_ = nullptr;
    wxSpinCtrl* spin_max_ = nullptr;
#ifndef NO_FRED
    wxSpinCtrl* spin_fred_ = nullptr;
#endif // NO_FRED
    wxStaticLine* line_1_ = nullptr;
    wxStaticLine* line_2_ = nullptr;
    wxStaticLine* line_3_ = nullptr;
    wxStaticLine* line_4_ = nullptr;
    wxStaticLine* line_5_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticLine* sl2_ = nullptr;
    wxStaticText* static_check_ = nullptr;
    wxStaticText* stat_config_ = nullptr;  
    wxStaticText* stat_persist_ = nullptr; 
    ::boost::filesystem::path config_, out_, persist_; 
    listedit_manager exclude_ = listedit_manager (button_general_add, button_general_erase, button_general_rename, file_general_name, list_general_ext, text_general_ext);
    bool class_ = false, other_ = false, rdfa_ = false, vcs_ = true;
#ifndef NO_FRED
    unsigned int fred_ = 1;
#endif // NO_FRED
    unsigned int max_ = def_max_file_size;
    void enable_max (const bool b);
#ifndef NO_FRED
    void enable_fred (const bool b);
#endif // NO_FRED
    void enable_persist (const bool b);
    DECLARE_CLASS (general_t)
    DECLARE_EVENT_TABLE ()
public:
    general_t () { }
    general_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    ~general_t () { }
    bool invalid () const noexcept { return exclude_.invalid () || check_vcs_ == nullptr || spin_max_ == nullptr || dir_config_ == nullptr || pick_persist_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    void CreateControls ();
#ifdef NO_FRED
    void OnFred (wxCommandEvent& ) constexpr { }
#else // NO_FRED
    void OnFred (wxCommandEvent& e);
#endif // NO_FRED
    void OnHelpClick (wxCommandEvent& event);
    void OnMax (wxCommandEvent& e);
    void OnPersist (wxCommandEvent& e);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool clss () const noexcept { return class_; }
    void clss (const bool b) noexcept { class_ = b; }
    bool other () const noexcept { return other_; }
    void other (const bool b) noexcept { other_ = b; }
    bool rdfa () const noexcept { return rdfa_; }
    void rdfa (const bool b) noexcept { rdfa_ = b; }
    bool vcs () const noexcept { return vcs_; }
    void vcs (const bool b) noexcept { vcs_ = b; }
#ifndef NO_FRED
    unsigned short fred () const noexcept { return GSL_NARROW_CAST < unsigned short > (fred_); }    
    void fred (const unsigned short& t);
#endif // NO_FRED
    void config (const ::boost::filesystem::path& c) { config_ = c; }
    ::boost::filesystem::path config () const { return config_; }
    void persist (const ::boost::filesystem::path& p) { persist_ = p; }
    ::boost::filesystem::path persist () const { return persist_; }
    unsigned int max_file_size () const noexcept { return max_; }    
    void max_file_size (const unsigned int& m); };

#endif // WX
