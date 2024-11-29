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
#include "gui/gui-ctrls.h"

#define SSI_CAPTION "Server Side Includes"

class ssi_t : public d1_t < wx_ssi >
{   check_datetime_t now_, lastmod_;
    check_line_t process_;
    check_or_text_t exec_;
    line_t exec_line_, text_line_;
    label_text_t args_, echomsg_, errmsg_, query_, timefmt_, user_;
    DECLARE_CLASS (ssi_t)
    DECLARE_EVENT_TABLE ()
public:
    ssi_t () = default;
    ssi_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SSI_CAPTION);
    ~ssi_t () = default;
    bool invalid () const noexcept
    {   return process_.invalid () || text_line_.invalid () || exec_line_.invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SSI_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void OnExec (wxCommandEvent& e);
    void OnLastMod (wxCommandEvent& e);
    void OnNow (wxCommandEvent& e);
    void OnProcess (wxCommandEvent& e);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (nitpick& nits, context_t& c) const; };

#endif // WX
