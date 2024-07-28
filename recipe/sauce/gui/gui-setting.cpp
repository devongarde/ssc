/*
ssc (static site checker)
File Info
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
#include "gui/gui-app.h"
#include "gui/gui-setting.h"
#include "main/options.h"

#define SET_STYLE   DEF_STYLE
#define SET_X       100
#define SET_Y       100
#define SET_WIDTH   500
#define SET_HEIGHT  500

BEGIN_EVENT_TABLE (setting_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, setting_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (setting_t, dialogue_t)

setting_t :: setting_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (SET_X, SET_Y), wxSize (SET_WIDTH, SET_HEIGHT))
{	Create (mummy, id, caption); } 

bool setting_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (SET_X, SET_Y), wxSize (SET_WIDTH, SET_HEIGHT), SET_STYLE)) return false;
	CreateControls ();
	return true; }

void setting_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	box_top_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_top_ != nullptr)
	{	const wxString choice [] = { "Configuration", "Corpus", "CSS", "General", "HTML", "Links", "MathML", "Microformats", "Nits", "Ontologies", "Shadow", "Site", "Spell", "Stats", "SVG", "Validation" };
		radio_pane_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (this, wxID_ANY, "Category", wxDefaultPosition, wxDefaultSize, sizeof (choice) / sizeof (wxString), choice, 1, wxRA_SPECIFY_COLS));
		if (radio_pane_ != nullptr)
		{	radio_pane_ -> SetSelection (0);
			box_top_ -> Add (radio_pane_, 0, wxALL, 5);
			line_vert_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL));
			if (line_vert_ != nullptr)
			{	box_top_ -> Add (line_vert_, 0, wxEXPAND | wxALL, 5);
				panel_ = GSL_OWNER (wxPanel) (new wxPanel (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL));
				if (panel_ != nullptr) box_top_ -> Add (panel_, 5, wxEXPAND, 5); } }
		box_ -> Add (box_top_, 12, wxALIGN_CENTER, 5); }

	line_horz_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line_horz_ != nullptr) box_ -> Add (line_horz_, 0, wxEXPAND | wxALL, 5);

	box_base_ = new wxBoxSizer (wxHORIZONTAL);
	if (box_base_ != nullptr)
	{	box_button_ = new wxBoxSizer (wxHORIZONTAL);
		if (box_button_ != nullptr)
		{	button_load_ = GSL_OWNER (wxButton) (new wxButton (this, button_load, "Load...", wxDefaultPosition, wxDefaultSize, 0));
			if (button_load_ != nullptr)
			{	box_button_ -> Add (button_load_, 0, wxALL, 5);
				button_save_ = GSL_OWNER (wxButton) (new wxButton (this, button_save, "Save...", wxDefaultPosition, wxDefaultSize, 0));
				if (button_save_ != nullptr)
				{	box_button_ -> Add (button_save_, 0, wxALL, 5);
					box_base_ -> Add (box_button_, 1, wxALIGN_CENTER, 5); } } }
		dialogue_t :: CreateButtons (1, box_base_);
		box_ -> Add (box_base_, 1, wxEXPAND, 5); }

	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void setting_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("config"); }

void setting_t :: OnLoad (wxCommandEvent& )
{	VERIFY_NOT_NULL (app, __FILE__, __LINE__);
	VERIFY_NOT_NULL (app -> frame (), __FILE__, __LINE__);
	app -> frame () -> load (); }

void setting_t :: OnSave (wxCommandEvent& )
{	VERIFY_NOT_NULL (app, __FILE__, __LINE__);
	VERIFY_NOT_NULL (app -> frame (), __FILE__, __LINE__);
	app -> frame () -> save_as (); }

bool setting_t :: TransferDataToWindow ()
{	//if (list_ == nullptr) return false;
	//list_ -> SetSelection (static_cast < int > (version_));
	return true; }

bool setting_t :: TransferDataFromWindow ()
{	//if (list_ == nullptr) return false;
	//const int v = list_ -> GetSelection ();
	//PRESUME (v <= math_core, __FILE__, __LINE__);
	//version_ = static_cast < e_math_version > (v);
	return true; }

#endif // WX
