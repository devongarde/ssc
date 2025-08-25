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

#define SITE_CAPTION "Site"

class site_t : public d1_t < wx_site >
{   check_t relative_;
    check_or_text_t account_, username_;
    label_text_t description_;
    line_t base_, line_, mid_;
    text_folder_t default_;
    listedit_manager domain_ = listedit_manager (button_site_add, button_site_erase, button_site_rename, file_site_name, list_site_ext, text_site_ext);
    bool absolute_ = false;
    ::std::string acc_, desc_, user_;
    ::boost::filesystem::path def_;
    sstr_t site_;
    DECLARE_CLASS (site_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (site_t);
    explicit site_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    bool invalid () const noexcept { return base_.invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    void CreateControls ();
    void OnAccount (wxCommandEvent& event);
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    void OnRename (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    void OnText (wxCommandEvent& event);
    void OnUsername (wxCommandEvent& event);
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || invalid (); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void def (const ::boost::filesystem::path& d) { def_ = d; }
    const ::boost::filesystem::path& def () const { return def_; }
    void site (const sstr_t& s) { site_ = s; }
    const sstr_t& site () const { return site_; } };

#endif // WX
