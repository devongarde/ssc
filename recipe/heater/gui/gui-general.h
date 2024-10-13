/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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

class general_t : public dialogue_t
{   wxBoxSizer* box_check_ = nullptr;
    wxBoxSizer* box_max_ = nullptr;
#ifndef NO_FRED
    wxBoxSizer* box_fred_ = nullptr;
    wxCheckBox* check_fred_ = nullptr;   
#endif // NO_FRED
    wxCheckBox* check_css_ = nullptr;   
    wxCheckBox* check_max_ = nullptr;   
    wxCheckBox* check_other_ = nullptr;   
    wxCheckBox* check_rdfa_ = nullptr;   
    wxCheckBox* check_vcs_ = nullptr;
    wxSpinCtrl* spin_max_ = nullptr;
#ifndef NO_FRED
    wxSpinCtrl* spin_fred_ = nullptr;
#endif // NO_FRED
    wxStaticLine* line_1_ = nullptr;
    wxStaticLine* line_2_ = nullptr;
    wxStaticLine* line_3_ = nullptr;
    wxStaticLine* line_4_ = nullptr;
    wxStaticLine* line_5_ = nullptr;
    wxStaticText* static_check_ = nullptr;   
    listedit_manager exclude_;
    bool css_ = false, other_ = false, rdfa_ = false, vcs_ = true;
#ifndef NO_FRED
    unsigned int fred_ = 1;
#endif // NO_FRED
    unsigned int max_ = def_max_file_size;
    void OnMax (wxCommandEvent& e);
    void enable_max (const bool b);
#ifndef NO_FRED
    void OnFred (wxCommandEvent& e);
    void enable_fred (const bool b);
#endif // NO_FRED
    DECLARE_CLASS (general_t)
    DECLARE_EVENT_TABLE ()
public:
    general_t () { }
    general_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    ~general_t () { }
    bool invalid () const noexcept { return exclude_.invalid () || check_vcs_ == nullptr || spin_max_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool css () const noexcept { return css_; }
    void css (const bool b) noexcept { css_ = b; }
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
    unsigned int max_file_size () const noexcept { return max_; }    
    void max_file_size (const unsigned int& m); };

#endif // WX
