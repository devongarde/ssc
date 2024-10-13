/*
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#include "gui/gui-mf.h"

#define MF_STYLE   DEF_STYLE
#define MF_X       100
#define MF_Y       100
#define MF_WIDTH   275
#define MF_HEIGHT  150

BEGIN_EVENT_TABLE (mf_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, mf_t::OnHelpClick)
  EVT_CHECKBOX (check_verify, mf_t::OnVerify)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (mf_t, dialogue_t)

mf_t :: mf_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (MF_X, MF_Y), wxSize (MF_WIDTH, MF_HEIGHT))
{	Create (mummy, id, caption); } 

bool mf_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (MF_X, MF_Y), wxSize (MF_WIDTH, MF_HEIGHT), MF_STYLE)) return false;
	CreateControls ();
	return true; }

void mf_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;
 	grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (grid_ != nullptr)
	{	verify_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_verify, "&Verify", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (verify_ != nullptr) grid_ -> Add (verify_, 0, wxALIGN_RIGHT | wxALL, 5);
		export_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "E&xport", wxDefaultPosition, wxDefaultSize, 0));
		if (export_ != nullptr) grid_ -> Add (export_, 0, wxALL, 5);
		v1_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Version &1", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (v1_ != nullptr) grid_ -> Add (v1_, 0, wxALIGN_RIGHT | wxALL, 5);
		v2_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Version &2", wxDefaultPosition, wxDefaultSize, 0));
		if (v2_ != nullptr) grid_ -> Add (v2_, 0, wxALL, 5);
		box_ -> Add (grid_, 2, wxEXPAND | wxALL, 5); }

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void mf_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("mf"); }

bool mf_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	export_ -> SetValue (exp_);	
	verify_ -> SetValue (vfy_);	
	v1_ -> SetValue (mf1_);	
	v2_ -> SetValue (mf2_);	
	return true; }

bool mf_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	exp_ = export_ -> GetValue ();	
	vfy_ = verify_ -> GetValue ();	
	mf1_ = v1_ -> GetValue ();	
	mf2_ = v2_ -> GetValue ();	
	return true; }

int mf_t :: version () const
{	int res = 0;
	if (mf1_) res += 1;
	if (mf2_) res += 2;
	return res; }

void mf_t :: version (const int n)
{	switch (n)
	{	case 1 : mf1_ = true; mf2_ = false; break;	
		case 2 : mf1_ = false; mf2_ = true; break;	
		case 3 : mf1_ = true; mf2_ = true; break;	
		default : mf1_ = mf2_ = false; break; } }

void mf_t :: OnVerify (wxCommandEvent& )
{	if (invalid ()) return;
	const bool e = verify_ -> IsChecked ();
	export_ -> Enable (e);
	v1_ -> Enable (e);
	v2_ -> Enable (e); }

#endif // WX
