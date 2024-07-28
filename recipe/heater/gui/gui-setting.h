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

#define SETTING_CAPTION "Settings"

class setting_t : public dialogue_t
{   wxBoxSizer* box_base_ = nullptr;
    wxBoxSizer* box_button_ = nullptr;
    wxBoxSizer* box_top_ = nullptr;
    wxButton* button_load_ = nullptr;
    wxButton* button_save_ = nullptr;
    wxPanel* panel_ = nullptr;
    wxRadioBox* radio_pane_ = nullptr;
    wxStaticLine* line_horz_ = nullptr;
    wxStaticLine* line_vert_ = nullptr;
    context_t context_;
    DECLARE_CLASS (setting_t)
    DECLARE_EVENT_TABLE ()
public:
    setting_t () { }
    setting_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SETTING_CAPTION);
    ~setting_t () { }
    bool invalid () const { return dialogue_t :: invalid () || (panel_ == nullptr) || (button_save_ == nullptr); }
    void Init () { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SETTING_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void OnLoad (wxCommandEvent& event);
    void OnSave (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
