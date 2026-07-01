/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"

#ifdef WX
#include "type/type.h"
#include "gui/gui-app.h"
#include "gui/gui-stats.h"
#include "utility/filesystem.h"

#define DEFAULT_STATS_EXT ".txt"
#define DEFAULT_STATS_FN  PROG DEFAULT_STATS_EXT

#define STATS_STYLE   DEF_STYLE
#define STATS_X       100
#define STATS_Y       100
#define STATS_WIDTH   600
#define STATS_HEIGHT  425

BEGIN_EVENT_TABLE (report_t, d1_t)
  EVT_BUTTON (button_all, report_t::OnAll)
  EVT_BUTTON (button_clear, report_t::OnClear)
  EVT_CHECKBOX (check_stats_export, report_t::OnExport)
  EVT_BUTTON (wxID_HELP, report_t::OnHelpClick)
  EVT_BUTTON (button_selected, report_t::OnSelected)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (report_t, d1_t)

report_t :: report_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (STATS_X, STATS_Y), wxSize (STATS_WIDTH, STATS_HEIGHT))
{	Create (mummy, id, caption); } 

bool report_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (STATS_X, STATS_Y), wxSize (STATS_WIDTH, STATS_HEIGHT), STATS_STYLE)) return false;
    CreateControls ();
    return true; }

void report_t :: create_controls (wxWindow *parent)
{	for (ach_t::iterator i = report_.begin (); i != report_.end (); ++i) *i = nullptr; 
    for (aset_t::iterator i = rpt_.begin (); i != rpt_.end (); ++i) *i = false;

    czech_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
    if (czech_grid_ != nullptr)
    {	int n = 0;
        for (ach_t::iterator i = report_.begin (); i != report_.end (); ++i)
        {	const ::std::string naam (type_master < t_report > :: base_name (static_cast < e_report > (n)));
            if (naam.empty ()) break;
            if (n++ % 2 == 0)
            {	*i = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, naam, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                if (*i == nullptr) break;
                czech_grid_ -> Add (*i, 0, wxALL | wxALIGN_RIGHT, 5); }
            else
            {	*i = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, naam, wxDefaultPosition, wxDefaultSize, 0));
                if (*i == nullptr) break;
                czech_grid_ -> Add (*i, 0, wxALL, 5); } }
        box_ -> Add (czech_grid_, 0, wxEXPAND, 5); }

    button_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 3, 0, 0));
    if (button_grid_ != nullptr)
    {	all_ = GSL_OWNER (wxButton) (new wxButton (parent, button_all, wxT("&All"), wxDefaultPosition, wxDefaultSize, 0));
        if (all_ != nullptr)
        {	button_grid_ -> Add (all_, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 5);
            selected_ = GSL_OWNER (wxButton) (new wxButton( parent, button_selected, wxT("C&ommon"), wxDefaultPosition, wxDefaultSize, 0));
            if (selected_ != nullptr)
            {	button_grid_ -> Add (selected_, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 5);
                clear_ = GSL_OWNER (wxButton) (new wxButton( parent, button_clear, wxT("C&lear"), wxDefaultPosition, wxDefaultSize, 0));
                if (clear_ != nullptr)
                {	button_grid_ -> Add (clear_, 0, wxALIGN_CENTRE_HORIZONTAL | wxALL, 5);
                    box_ -> Add (button_grid_, 0, wxEXPAND, 5); } } } }

    export_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 3, 0, 0));
    if (export_grid_ != nullptr)
    {	check_export_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_stats_export, "E&xport", wxDefaultPosition, wxDefaultSize, 0));
        if (check_export_ != nullptr)
        {	export_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (parent, wxID_ANY, DEFAULT_STATS_FN, "Output reports to", "*" DEFAULT_STATS_EXT, wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT | wxFLP_SAVE | wxFLP_USE_TEXTCTRL));
            if (export_ != nullptr)
            {	export_grid_ -> Add (check_export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5);
                export_grid_ -> Add (export_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5); } }
        box_ -> Add (export_grid_, 0, wxEXPAND, 5); }

    base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
        box_ -> Add (base_, 0, wxEXPAND | wxALL, 5); }

void report_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    PRESUME (invalid (), __FILE__, __LINE__);
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH);  }

void report_t :: OnAll (wxCommandEvent& )
{	for (auto i : report_)
        if (i != nullptr)
            i -> SetValue (true); }

void report_t :: OnClear (wxCommandEvent& )
{	for (auto i : report_)
        if (i != nullptr)
            i -> SetValue (false); }

void report_t :: set_dump ()
{	if (dump_.empty ())
    {	dump_ = get_working_directory ();
        dump_ /= DEFAULT_STATS_FN;
        wxFileName fn (dump_.string ());
        export_ -> SetFileName (fn); } }

void report_t :: OnExport (wxCommandEvent& )
{	if (invalid ()) return;	
    const bool exed = check_export_ -> IsChecked ();
    if (exed) set_dump ();
    enable (exed); }

void report_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_stats); }

void report_t :: OnSelected (wxCommandEvent& e)
{	OnClear (e);
    if (report_.at (rcb_error) != nullptr) report_.at (rcb_error) -> SetValue (true);
    if (report_.at (rcb_file) != nullptr) report_.at (rcb_file) -> SetValue (true);
    if (report_.at (rcb_summary) != nullptr) report_.at (rcb_summary) -> SetValue (true); }

bool report_t :: TransferDataToWindow ()
{	if (invalid ()) return false;	
    int n = 0;
    for (ach_t::const_iterator i = report_.begin (); i != report_.end (); ++i, ++n)
        if (*i != nullptr)
            (*i) -> SetValue (rpt_.at (n));	
    if (export_ != nullptr)
    {	set_dump ();
        wxFileName fn (dump_.string ());
        export_ -> SetFileName (fn); }
    return true; }

bool report_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    int n = 0;
    for (ach_t::const_iterator i = report_.begin (); i != report_.end (); ++i, ++n)
        if (*i != nullptr)
            rpt_.at (n) = (*i) -> GetValue ();	
    if (export_ != nullptr)
    {	wxFileName fn (export_ -> GetFileName ());
        dump_ = ::std::string (fn.GetName ().c_str ()); }
    return true; }

bool report_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void report_t :: enable (const bool b)
{	if (invalid ()) return;	
    for (auto i : report_)
    {   VERIFY_NOT_NULL (i, __FILE__, __LINE__);
        i -> Enable (b); }
    export_ -> Enable (b); }

void report_t :: load_from_context (const context_t& c)
{	for (int i = 0; i < rcb_max; ++i)
    {   const e_report r = GSL_NARROW_CAST < e_report > (i);
        report (r, c.stats_report (r)); }
    dump (c.stats ()); }

void report_t :: save_to_context (context_t& c) const
{   for (int i = 0; i < rcb_max; ++i)
    {   const e_report r = GSL_NARROW_CAST < e_report > (i);
        c.stats_report (r, report (r)); }
    c.stats (dump ().string ()); }
#endif // WX
