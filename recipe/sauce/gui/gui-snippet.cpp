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
#include "gui/gui-app.h"
#include "gui/gui-snippet.h"

#define SNIPPET_STYLE   wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX
#define SNIPPET_X       100
#define SNIPPET_Y       100
#define SNIPPET_WIDTH   500
#define SNIPPET_HEIGHT  400

BEGIN_EVENT_TABLE (snippet_t, d1_t)
  EVT_BUTTON (wxID_HELP, snippet_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (snippet_t, d1_t)

snippet_t :: snippet_t (const ::std::string& s)
	: d1_t (wxPoint (SNIPPET_X, SNIPPET_Y), wxSize (SNIPPET_WIDTH, SNIPPET_HEIGHT)), snippet_ (s)
{ }

snippet_t :: snippet_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (SNIPPET_X, SNIPPET_Y), wxSize (SNIPPET_WIDTH, SNIPPET_HEIGHT))
{	Create (mummy, id, caption); } 

bool snippet_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SNIPPET_X, SNIPPET_Y), wxSize (SNIPPET_WIDTH, SNIPPET_HEIGHT), SNIPPET_STYLE)) return false;
	CreateControls ();
	return true; }

void snippet_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
 	stc_ = GSL_OWNER (wxStyledTextCtrl) (new wxStyledTextCtrl (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL | wxWANTS_CHARS, wxEmptyString));
	if (stc_ != nullptr) box_ -> Add (stc_, 7, wxEXPAND | wxALL, 5);
	d1_t :: CreateButtons ();
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void snippet_t :: OnHelpClick (wxCommandEvent& )
{	app -> help ("snippet"); }

bool snippet_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	stc_ -> SetValue (snippet_.c_str ());
	return true; }

bool snippet_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	snippet_ = stc_ -> GetValue ().c_str (); 
	return true; }

#endif // WX
