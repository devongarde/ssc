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
#include "webpage/required.h"

#define LINK_CAPTION "Links"

class link_t : public d1_t < wx_link >
{   wxCheckBox* check_example_ = nullptr;
    wxCheckBox* check_external_ = nullptr;
    wxCheckBox* check_forwarded_ = nullptr;
    wxCheckBox* check_id_ = nullptr;
    wxCheckBox* check_internal_ = nullptr;
    wxCheckBox* check_local_ = nullptr;
    wxCheckBox* check_once_ = nullptr;
    wxCheckBox* check_revoke_ = nullptr;
    wxCheckBox* check_special_ = nullptr;
    wxChoice* choice_from_ = nullptr;
    wxChoice* choice_lang_ = nullptr;
    wxChoice* choice_page_ = nullptr;
    wxChoice* choice_to_ = nullptr;
    wxGridSizer* grid_check_ = nullptr;
    wxGridSizer* grid_desc_ = nullptr;
    wxGridSizer* grid_req_ = nullptr; 
    wxStaticLine* line_ = nullptr;
    wxStaticText* static_desc_ = nullptr;
    wxStaticText* static_from_ = nullptr;
    wxStaticText* static_lang_ = nullptr;
    wxStaticText* static_page_ = nullptr;
    wxStaticText* static_to_ = nullptr;
    wxTextCtrl* text_desc_ = nullptr;
    bool example_ = false, external_ = false, forwarded_ = false, id_ = false, internal_ = false, local_ = false, once_ = false, revoke_ = false, special_ = false;
    listedit_manager required_ = listedit_manager (button_req_add, button_req_erase, button_req_rename, file_req_name, list_req_ext, text_req_ext);
    req_vt vreq_;
    DECLARE_CLASS (link_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (link_t);
    explicit link_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = LINK_CAPTION);
    bool invalid () const noexcept { return (panel_ == nullptr) || (grid_check_ == nullptr) || (grid_desc_ == nullptr) || (grid_req_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = LINK_CAPTION);
    void CreateControls ();
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnExternal (wxCommandEvent& e);
    void OnHelpClick (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    void OnInternal (wxCommandEvent& e);
    void OnRename (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    void OnText (wxCommandEvent& event);
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || invalid (); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
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
    void revoke (const bool b) noexcept { revoke_ = b; }
    bool special () const noexcept { return special_; }
    void special (const bool b) noexcept { special_ = b; } };
#endif // WX
