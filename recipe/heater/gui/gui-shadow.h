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

#define SHADOW_CAPTION "Shadow"

class shadow_t : public d1_t < wx_shadow >
{   wxBoxSizer* box_cache_ = nullptr;
    wxBoxSizer* box_comment_ = nullptr;
    wxBoxSizer* box_strat_ = nullptr;
    wxBoxSizer* box_site_ = nullptr;
    wxCheckBox* check_change_ = nullptr;
    wxCheckBox* check_keep_ = nullptr;
    wxCheckBox* check_site_ = nullptr;
    wxCheckBox* check_ssi_ = nullptr;
    wxCheckBox* check_time_ = nullptr;
    wxCheckBox* check_whitespace_ = nullptr;
    wxChoice* choice_strat_ = nullptr;
    wxDirPickerCtrl* dir_site_ = nullptr;
    wxFilePickerCtrl* file_cache_ = nullptr;
    wxGridSizer* grid_check_ = nullptr;
    wxStaticLine* line_base_ = nullptr;
    wxStaticLine* line_cache_ = nullptr;
    wxStaticLine* line_check_ = nullptr;
    wxStaticLine* line_comment_ = nullptr;
    wxStaticLine* line_site_ = nullptr;
    wxStaticText* stat_cache_ = nullptr;
    wxStaticText* stat_comment_ = nullptr;
    wxStaticText* stat_site_ = nullptr;
    wxStaticText* stat_strat_ = nullptr;
    wxTextCtrl* text_comment_ = nullptr;
    listedit_manager ignore_ = listedit_manager (button_shadow_add, button_shadow_erase, button_shadow_rename, file_shadow_name, list_shadow_ext, text_shadow_ext);
    int strat_count_ = 0;
    bool change_ = false, keep_ = false, site_ = false, ssi_ = false, time_ = false, whitespace_ = false; 
    ::boost::filesystem::path cache_, shadow_;
    e_copy strat_ = c_none;
    vstr_t ext_;
    ::std::string comment_; 
    void enable (); 
    DECLARE_CLASS (shadow_t)
    DECLARE_EVENT_TABLE ()
public:
    shadow_t () { }
    shadow_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SHADOW_CAPTION);
    ~shadow_t () { }
    bool invalid () const noexcept { return ignore_.invalid () || (choice_strat_ == nullptr) || (dir_site_ == nullptr) || (check_ssi_ == nullptr) || (text_comment_ == nullptr) || (file_cache_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SHADOW_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void OnIgnoreAdd (wxCommandEvent& event);
    void OnIgnoreErase (wxCommandEvent& event);
    void OnIgnoreRename (wxCommandEvent& event);
    void OnIgnoreExtension (wxCommandEvent& event);
    void OnIgnoreTap (wxCommandEvent& event);
    void OnIgnoreImpatience (wxCommandEvent& event);
    void OnShadow (wxCommandEvent& event);
    bool invalid_panel () const { return d1_t :: invalid_panel () || invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;

    ::boost::filesystem::path cache () const { return cache_; }
    void cache (const ::boost::filesystem::path& p) { cache_ = p; }
    bool change () const noexcept { return change_; }
    void change (const bool b) noexcept { change_ = b; }
    ::std::string comment () const { return comment_; }
    void comment (const ::std::string& s) { comment_ = s; }
    vstr_t ignore () const { return ext_; }
    void ignore (const vstr_t& v) { ext_ = v; }
    bool keep () const noexcept { return keep_; }
    void keep (const bool b) noexcept { keep_ = b; }
    ::boost::filesystem::path shadow () const { return shadow_; }
    void shadow (const ::boost::filesystem::path& p) { shadow_ = p; }
    bool site () const noexcept { return site_; }
    void site (const bool b) noexcept { site_ = b; }
    bool ssi () const noexcept { return ssi_; }
    void ssi (const bool b) noexcept { ssi_ = b; }
    e_copy strategy () const noexcept { return strat_; }
    void strategy (const e_copy c) noexcept { strat_ = c; }
    bool time () const noexcept { return time_; }
    void time (const bool b) noexcept { time_ = b; }
    bool whitespace () const noexcept { return whitespace_; }
    void whitespace (const bool b) noexcept { whitespace_ = b; }

    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
