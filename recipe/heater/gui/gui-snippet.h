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

#define SNIPPET_CAPTION "Snippet"

class snippet_t : public dialogue_t
{   wxStyledTextCtrl* stc_ = nullptr;
    ::std::string snippet_;
    DECLARE_CLASS (snippet_t)
    DECLARE_EVENT_TABLE ()
public:
    explicit snippet_t (const ::std::string& s);
    snippet_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SNIPPET_CAPTION);
    bool invalid () const noexcept { return stc_ == nullptr; }
    void Init () noexcept { snippet_.clear (); }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SNIPPET_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void snippet (const ::std::string& s)
    {   snippet_ = s; }
    ::std::string snippet () const
    {   return snippet_; } };

#endif // WX
