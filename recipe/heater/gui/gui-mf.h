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

#define MF_CAPTION "Microformats"

class mf_t : public dialogue_t
{   wxGridSizer* grid_ = nullptr;
    wxCheckBox* export_ = nullptr;
    wxCheckBox* verify_ = nullptr;
    wxCheckBox* v1_ = nullptr;
    wxCheckBox* v2_ = nullptr;
    bool exp_ = false, vfy_ = false, mf1_ = false, mf2_ = false;
    void OnVerify (wxCommandEvent& e);
    DECLARE_CLASS (corpus_t)
    DECLARE_EVENT_TABLE ()
public:
    mf_t () { }
    mf_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = MF_CAPTION);
    ~mf_t () { }
    bool invalid () const noexcept { return (grid_ == nullptr) || (export_ == nullptr) || (verify_ == nullptr) || (v1_ == nullptr) || (v2_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = MF_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();

    bool exp () const noexcept { return exp_; }
    void exp (const bool b) noexcept { exp_ = b; }
    bool verify () const noexcept { return vfy_; }
    void verify (const bool b) noexcept { vfy_ = b; }
    int version () const;
    void version (const int n); };

#endif // WX
