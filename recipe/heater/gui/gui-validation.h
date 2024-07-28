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
#include "gui/gui-listedit.h"

#define VALID_CAPTION "Validation"

class valid_t : public dialogue_t
{   wxBoxSizer* box_for_ = nullptr;
    wxCheckBox* check_microdata_ = nullptr;
    wxChoice* choice_for_ = nullptr;
    wxStaticLine* line_microdata_ = nullptr;
    wxStaticLine* line_base_ = nullptr;
    wxStaticText* stat_for_ = nullptr;
    listedit_manager val_;
    vstr_t vcategories_;
    vvstr_t vvals_;
    void OnChoice (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void populate ();
    DECLARE_CLASS (valid_t)
    DECLARE_EVENT_TABLE ()
public:
    valid_t () { }
    valid_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    ~valid_t () { }
    bool invalid () const noexcept { return val_.invalid () || (choice_for_ == nullptr) || (check_microdata_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    void CreateControls ();
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
