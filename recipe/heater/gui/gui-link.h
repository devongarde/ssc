/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
{   check_t example_check_, external_check_, forwarded_check_, id_check_, internal_check_, local_check_, once_check_, revoke_check_, special_check_;
    element_choice_t element_choice_;
    grid_t check_grid_;
    html_version_t from_html_, to_html_;
    label_text_t desc_text_;
    line_t l_;
    lingo_t lingo_;
    listedit_manager required_ = listedit_manager (button_req_add, button_req_erase, button_req_rename, file_req_name, list_req_ext, text_req_ext);
    text_drop_t < choice_t > type_choice_;
    bool example_ = false, external_ = false, forwarded_ = false, id_ = false, internal_ = false, local_ = false, once_ = false, revoke_ = false, special_ = false;
    ::std::string def_lang_ = "en";
    req_vt vreq_;
    int sel_ = -1;
    void fill_require (const int sel = 0);
    void select_require (const int sel = 0);
    void externaliser ();
    void internaliser ();
    required_t gather_require (int& sel);
    void sanitise ();
    DECLARE_CLASS (link_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (link_t);
    explicit link_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = LINK_CAPTION);
    bool invalid () const noexcept { return l_.invalid (); }
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
    const req_vt& required () const noexcept { return vreq_; }
    req_vt& required () noexcept { return vreq_; }
    void required (const req_vt& rq) noexcept { vreq_ = rq; }
    bool revoke () const noexcept { return revoke_; }
    void revoke (const bool b) noexcept { revoke_ = b; }
    bool special () const noexcept { return special_; }
    void special (const bool b) noexcept { special_ = b; } };
#endif // WX
