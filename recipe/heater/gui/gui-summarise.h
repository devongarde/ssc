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

class summarise_t : public d1_t < wx_summary >
{   wxStaticLine* line_below_ = nullptr;
    wxStaticText* stat_config_ = nullptr;
    wxStaticText* stat_summary_ = nullptr;
    wxStaticText* stat_switches_ = nullptr;
    wxTextCtrl* text_config_ = nullptr;
    wxTextCtrl* text_summary_ = nullptr;
    wxTextCtrl* text_switches_ = nullptr;
    ::std::string config_, summary_, switches_;
    void texttext (wxWindow *parent, wxStaticText*& stat, wxTextCtrl*& ctrl, const ::std::string& con, const char* const burble);
    DECLARE_CLASS (summarise_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (summarise_t);
    explicit summarise_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    bool invalid () const noexcept { return text_switches_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = VALID_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow () { return (! invalid ()); }
    bool invalid_panel () const { return d1_t :: invalid_panel () || invalid (); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& ) const { }; };
#endif // WX
