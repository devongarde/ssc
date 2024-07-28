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

#define LYNX_CAPTION "Links"

class lynx_t : public dialogue_t
{   wxCheckBox* check_example_ = nullptr;
    wxCheckBox* check_external_ = nullptr;
    wxCheckBox* check_forwarded_ = nullptr;
    wxCheckBox* check_id_ = nullptr;
    wxCheckBox* check_internal_ = nullptr;
    wxCheckBox* check_local_ = nullptr;
    wxCheckBox* check_once_ = nullptr;
    wxCheckBox* check_revoke_ = nullptr;
    wxGridSizer* grid_ = nullptr; 
    bool example_ = false, external_ = false, forwarded_ = false, id_ = false, internal_ = false, local_ = false, once_ = false, revoke_ = false;
    void OnExternal (wxCommandEvent& e);
    void OnInternal (wxCommandEvent& e);
    DECLARE_CLASS (lynx_t)
    DECLARE_EVENT_TABLE ()
public:
    lynx_t () { }
    lynx_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = LYNX_CAPTION);
    ~lynx_t () { }
    bool invalid () const noexcept { return dialogue_t :: invalid () || grid_ == nullptr || check_id_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = LYNX_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
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
    void revoke (const bool b) noexcept { revoke_ = b; } };

#endif // WX
