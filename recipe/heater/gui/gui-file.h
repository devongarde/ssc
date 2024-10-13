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

#define FILE_CAPTION "File"

class file_t : public dialogue_t
{   wxBoxSizer* box_output_ = nullptr;
    wxBoxSizer* box_persist_ = nullptr;
    wxFilePickerCtrl* pick_persist_ = nullptr;
    wxGenericDirCtrl* dir_config_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticText* stat_config_ = nullptr;  
    wxStaticText* stat_persist_ = nullptr; 
    ::boost::filesystem::path config_, out_, persist_; 
    DECLARE_CLASS (file_t)
    DECLARE_EVENT_TABLE ()
public:
    file_t () { }
    file_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = FILE_CAPTION);
    ~file_t () { }
    bool invalid () const noexcept { return pick_persist_ == nullptr || dir_config_ == nullptr; }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = FILE_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void config (const ::boost::filesystem::path& c) { config_ = c; }
    ::boost::filesystem::path config () const { return config_; }
    void persist (const ::boost::filesystem::path& p) { persist_ = p; }
    ::boost::filesystem::path persist () const { return persist_; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
