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
#include "utility/bitset.h"
#include "gui/gui-dialogue.h"

#define STATS_CAPTION "Reports"

class report_t : public d1_t < wx_stats >
{   typedef ::std::array < wxCheckBox*, rcb_max > ach_t;
    ach_t report_;
    wxButton* all_ = nullptr;
    wxButton* clear_ = nullptr; 
    wxButton* selected_ = nullptr; 
    wxCheckBox* check_export_ = nullptr; 
	wxFilePickerCtrl* export_ = nullptr;
    wxGridSizer* button_grid_ = nullptr;
	wxGridSizer* czech_grid_ = nullptr;
	wxGridSizer* export_grid_ = nullptr;
    wxStaticLine* base_ = nullptr;
    wxStaticText* export_to_ = nullptr;
    aset_t rpt_;
    ::boost::filesystem::path dump_;
    void enable (const bool b);    
    void set_dump ();
    DECLARE_CLASS (report_t)
    DECLARE_EVENT_TABLE ()
public:
    report_t () { }
    report_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = STATS_CAPTION);
    ~report_t () { }
    bool invalid () const noexcept
    {   return (export_ == nullptr) || (clear_ == nullptr) || (czech_grid_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = STATS_CAPTION);
    void CreateControls ();
    void OnAll (wxCommandEvent& e);
    void OnClear (wxCommandEvent& e);
    void OnExport (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void OnSelected (wxCommandEvent& e);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;

    bool report (const e_report r) const { return rpt_.at (r); }
    void report (const e_report r, const bool b) { rpt_.at (r) = b; }
    ::boost::filesystem::path dump () const { return dump_; }
    void dump (const ::boost::filesystem::path& p) { dump_ = p; } };

#endif // WX
