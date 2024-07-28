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
#include "gui/gui-math.h"

#define MATH_STYLE   DEF_STYLE
#define MATH_X       100
#define MATH_Y       100
#define MATH_WIDTH   300
#define MATH_HEIGHT  225

BEGIN_EVENT_TABLE (math_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, math_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (math_t, dialogue_t)

math_t :: math_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (MATH_X, MATH_Y), wxSize (MATH_WIDTH, MATH_HEIGHT))
{	Create (mummy, id, caption); } 

bool math_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (MATH_X, MATH_Y), wxSize (MATH_WIDTH, MATH_HEIGHT), MATH_STYLE)) return false;
	CreateControls ();
	return true; }

void math_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;
	wxArrayString stray;
	stray.Add ("none (derive from HTML version)");
	stray.Add ("MathML 1");
	stray.Add ("MathML 2");
	stray.Add ("MathML 3");
	stray.Add ("MathML 4 (June 2022 draft)");
	stray.Add ("MathML 4 core");

	list_ = GSL_OWNER (wxListBox) (new wxListBox (this, wxID_ANY, wxDefaultPosition, wxSize (140, 30), stray, wxLB_SINGLE));
	if (list_ != nullptr)
	{	list_ -> SetSelection (static_cast < int > (version_));
		box_ -> Add (list_, 6, wxEXPAND | wxALL, 5); }

	dialogue_t :: CreateButtons ();
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void math_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("mathml"); }

bool math_t :: TransferDataToWindow ()
{	if (list_ == nullptr) return false;
	list_ -> SetSelection (static_cast < int > (version_));
	return true; }

bool math_t :: TransferDataFromWindow ()
{	if (list_ == nullptr) return false;
	const int v = list_ -> GetSelection ();
	PRESUME (v <= math_core, __FILE__, __LINE__);
	version_ = static_cast < e_math_version > (v);
	return true; }

#endif // WX
