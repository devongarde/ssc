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
#include "feedback/nitpick.h"

#define NIT_CAPTION "Nitpicking..."

class nits_t : public d1_t < wx_nits >
{   wxBoxSizer* box_format_ = nullptr;
    wxBoxSizer* box_options_ = nullptr;
    wxBoxSizer* box_output_ = nullptr;
    wxBoxSizer* box_verbosity_ = nullptr;
    wxCheckBox* check_id_ = nullptr;
    wxCheckBox* check_repeat_ = nullptr;
    wxChoice* choice_format_ = nullptr;
    wxChoice* choice_verbosity_ = nullptr;
    wxFilePickerCtrl* file_output_ = nullptr;
    wxListBox* list_level_ = nullptr;
    wxRadioBox* radio_level_ = nullptr;
    wxStaticLine* line1_ = nullptr;
    wxStaticLine* line2_ = nullptr;
    wxStaticLine* line3_ = nullptr;
    wxStaticText* static_format_ = nullptr;   
    wxStaticText* static_output_ = nullptr;   
    wxStaticText* static_verbosity_ = nullptr;
    mns_t current_, stable_;
    bool id_ = false, repeat_ = false;
    ::boost::filesystem::path output_;
    e_severity verbosity_ = es_undefined;
    e_output_template nf_ = eot_html;
    DECLARE_CLASS (nits_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (nits_t);
    explicit nits_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = NIT_CAPTION);
    bool invalid () const noexcept { return box_verbosity_ == nullptr || file_output_ == nullptr || radio_level_ == nullptr || check_repeat_ == nullptr || choice_format_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = NIT_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void OnListLevel (wxCommandEvent& event);
    void OnNitFormat (wxCommandEvent& event);
    void OnRadioLevel (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || box_verbosity_ == nullptr || file_output_ == nullptr || radio_level_ == nullptr || check_repeat_ == nullptr; }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void enable_bespoke (const bool b);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    void format (const ::boost::filesystem::path& s);
    ::boost::filesystem::path format () const;
    bool id () const noexcept { return id_; }
    void id (const bool b) noexcept { id_ = b; }
    ::boost::filesystem::path output () const { return output_; }
    void output (const ::boost::filesystem::path& p) { output_ = p; }
    bool repeat () const noexcept { return repeat_; }
    void repeat (const bool b) noexcept { repeat_ = b; }
    mns_t severity () const { return stable_; }
    void severity (const mns_t& s) { stable_ = s; }
    e_severity verbosity () const noexcept { return verbosity_; }
    void verbosity (const e_severity v) noexcept { verbosity_ = v; } };
#endif // WX
