/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "main/context.h"
#include "gui/gui-app.h"
#include "gui/gui-summarise.h"

#define VALID_STYLE   DEF_STYLE
#define VALID_X       100
#define VALID_Y       100
#define VALID_WIDTH   400
#define VALID_HEIGHT  250

BEGIN_EVENT_TABLE (summarise_t, d1_t)
  EVT_BUTTON (wxID_HELP, summarise_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (summarise_t, d1_t)

summarise_t :: summarise_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT))
{	Create (mummy, id, caption); } 

bool summarise_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT), VALID_STYLE)) return false;
    CreateControls ();
    return true; }

void summarise_t :: texttext (wxWindow *parent, wxStaticText*& stat, wxTextCtrl*& ctrl, const ::std::string& con, const char* const burble)
{	stat = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, burble, wxDefaultPosition, wxDefaultSize, 0));
    if (stat != nullptr)
    {	stat -> Wrap (-1);
        ctrl = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize (360, 90), wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP));
        if (ctrl != nullptr)
        {	ctrl -> SetValue (con.c_str ());
            box_ -> Add (stat, 0, wxALL, 5);
            box_ -> Add (ctrl, 0, wxEXPAND | wxALL, 5); } } }

void summarise_t :: create_controls (wxWindow *parent)
{	texttext (parent, stat_summary_, text_summary_, summary_, "Summary:");
    texttext (parent, stat_config_, text_config_, config_, ".conf file:");
    texttext (parent, stat_switches_, text_switches_, switches_, "Switches:");

    line_below_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_below_ != nullptr)
        box_ -> Add (line_below_, 0, wxEXPAND | wxALL, 5); }

void summarise_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void summarise_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_summary); }

bool summarise_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

bool summarise_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    text_config_ -> SetValue (config_.c_str ());
    text_summary_ -> SetValue (summary_.c_str ());
    text_switches_ -> SetValue (switches_.c_str ());
    return true; }

void summarise_t :: load_from_context (const context_t& c)
{	config_ = c.report (gr_config, false);
    summary_ = c.report (gr_summary, false);
    switches_ = c.report (gr_switches, false); }

#endif // WX
