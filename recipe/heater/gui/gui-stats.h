/*                                                                 ,
ssc (static site checker)
File Info
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
#include "utility/bitset.h"
#include "gui/gui-dialogue.h"

#define STATS_CAPTION "Reports"

class report_t : public dialogue_t
{   typedef ::std::array < wxCheckBox*, rcb_max > ach_t;
    ach_t report_;
    wxButton* all_ = nullptr;
    wxButton* clear_ = nullptr; 
    wxButton* selected_ = nullptr; 
	wxFilePickerCtrl* export_ = nullptr;
    wxGridSizer* button_grid_ = nullptr;
	wxGridSizer* czech_grid_ = nullptr;
	wxGridSizer* export_grid_ = nullptr;
    wxStaticText* export_to_ = nullptr;
    aset_t rpt_;
    ::boost::filesystem::path dump_;    
    DECLARE_CLASS (report_t)
    DECLARE_EVENT_TABLE ()
public:
    report_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = STATS_CAPTION);
    bool invalid () const noexcept
    {   return (export_ == nullptr) || (clear_ == nullptr) || (czech_grid_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = STATS_CAPTION);
    void CreateControls ();
    void OnAll (wxCommandEvent& e);
    void OnClear (wxCommandEvent& e);
    void OnHelpClick (wxCommandEvent& event);
    void OnSelected (wxCommandEvent& e);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool report (const e_report r) const { return rpt_.at (r); }
    void report (const e_report r, const bool b) { rpt_.at (r) = b; }
    ::boost::filesystem::path dump () const { return dump_; }
    void dump (const ::boost::filesystem::path& p) { dump_ = p; } };

#endif // WX
