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
#include "gui/gui-spex.h"

#define WELCOME_CAPTION FULLNAME

class welcome_t : public d2_t
{   wxButton* button_configure_ = nullptr;
    wxDirPickerCtrl* dir_root_ = nullptr;
    wxRadioButton* radio_root_ = nullptr;
    wxRadioButton* radio_snippet_ = nullptr;
    wxStaticLine* line_base_ = nullptr;
    wxStaticLine* line_root_ = nullptr;
    wxStaticLine* line_snippet_ = nullptr;
    wxStaticLine* line_summary_ = nullptr;
    wxStaticText* static_nitpickery_ = nullptr;
    wxStaticText* static_title_ = nullptr;
    wxTextCtrl* text_snippet_ = nullptr;
    wxTextCtrl* text_summary_ = nullptr;
    context_t c_;
    ::boost::filesystem::path root_;
    ::std::string snippet_;
    vstr_t cmd_;
    bool rooted_ = true, write_continuity_ = false;
    void OnClickRoot (wxCommandEvent& event);
    void OnClickSnippet (wxCommandEvent& event);
    void OnAboutClick (wxCommandEvent& event);
    void OnCancelClick (wxCommandEvent& event);
    void OnConfigClick (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void OnOkClick (wxCommandEvent& event);
    DECLARE_CLASS (welcome_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (welcome_t);
    welcome_t (wxWindow *mummy, const context_t& c, wxWindowID id = wxID_ANY, const wxString& caption = WELCOME_CAPTION);
    bool invalid () const noexcept
    {   return (line_root_ == nullptr) || (line_snippet_ == nullptr) || (button_configure_ == nullptr) || d2_t :: invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = WELCOME_CAPTION);
    void CreateControls ();
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void set_default ();
    context_t& c () { return c_; }
    const context_t& c () const { return c_; }
    bool rooted () const { return rooted_; }
    const ::boost::filesystem::path& root () const { return root_; }
    void root (const ::boost::filesystem::path& r) { root_ = r; }
    const ::std::string& snippet () const { return snippet_; }
    void snippet (const ::std::string& s) { snippet_ = s; }
    ::boost::filesystem::path get_continuity () const;
    const vstr_t& cmd () const { return cmd_; } };
#endif // WX
