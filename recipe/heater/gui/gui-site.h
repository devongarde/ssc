/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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

#define SITE_CAPTION "Site"

class site_t : public dialogue_t
{   wxGenericDirCtrl* dir_default_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticText* stat_default_ = nullptr; 
    listedit_manager domain_;
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnRename (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    ::boost::filesystem::path def_;
    vstr_t site_;
    DECLARE_CLASS (site_t)
    DECLARE_EVENT_TABLE ()
public:
    site_t () { }
    site_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    ~site_t () { }
    bool invalid () const noexcept { return dialogue_t::invalid () || domain_.invalid () || dir_default_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SITE_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void def (const ::boost::filesystem::path& d) { def_ = d; }
    const ::boost::filesystem::path& def () const { return def_; }
    void site (const vstr_t& s) { site_ = s; }
    const vstr_t& site () const { return site_; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
