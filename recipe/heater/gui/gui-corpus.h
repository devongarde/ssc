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

#define CORPUS_CAPTION "corpus"

class corpus_t : public dialogue_t
{   wxFilePickerCtrl* file_ = nullptr;
    wxGridSizer* grid_ = nullptr;
    wxCheckBox* article_ = nullptr;
    wxCheckBox* body_ = nullptr;
    wxCheckBox* main_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticLine* base_ = nullptr;
    wxStaticText* top_ = nullptr;  
    wxStaticText* text_ = nullptr;  
    ::boost::filesystem::path path_;
    bool art_ = false, bod_ = false, mai_ = false;
    DECLARE_CLASS (corpus_t)
    DECLARE_EVENT_TABLE ()
public:
    corpus_t () = default;
    corpus_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CORPUS_CAPTION);
    ~corpus_t () = default;
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CORPUS_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid () const { return (grid_ == nullptr) || (file_ == nullptr) || (article_ == nullptr) || (body_ == nullptr) || (main_ == nullptr); }
    ::boost::filesystem::path folder () const { return path_; }
    void folder (const ::boost::filesystem::path& p) { path_ = p; }
    bool article () const noexcept { return art_; }
    void article (const bool b) noexcept { art_ = b; }
    bool body () const noexcept { return bod_; }
    void body (const bool b) noexcept { bod_ = b; }
    bool main () const noexcept { return mai_; }
    void main (const bool b) noexcept { mai_ = b; } };

#endif // WX
