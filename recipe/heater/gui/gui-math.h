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

#define MATH_CAPTION "MathML"

class math_t : public dialogue_t
{   wxListBox* list_ = nullptr;
    e_math_version version_;
    DECLARE_CLASS (math_t)
    DECLARE_EVENT_TABLE ()
public:
    math_t () { }
    math_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = MATH_CAPTION);
    ~math_t () { }
    void Init () { version_ = math_none; }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = MATH_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void version (const e_math_version m)
    {   version_ = m; }
    e_math_version version () const
    {   return version_; } };

#endif // WX
