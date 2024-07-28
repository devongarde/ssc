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
#include "gui/gui-svg.h"

#define SVG_STYLE   DEF_STYLE
#define SVG_X       100
#define SVG_Y       100
#define SVG_WIDTH   300
#define SVG_HEIGHT  225

BEGIN_EVENT_TABLE (svg_t, wxDialog)
  EVT_BUTTON (wxID_HELP, svg_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (svg_t, wxDialog)

svg_t :: svg_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (SVG_X, SVG_Y), wxSize (SVG_WIDTH, SVG_HEIGHT))
{	Create (mummy, id, caption); } 

bool svg_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (SVG_X, SVG_Y), wxSize (SVG_WIDTH, SVG_HEIGHT), SVG_STYLE)) return false;
	CreateControls ();
	return true; }

void svg_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	wxArrayString stray;
	stray.Add ("none (derive from HTML version)");
	stray.Add ("SVG 1.0");
	stray.Add ("SVG 1.1");
	stray.Add ("SVG 1.2 Tiny");
	stray.Add ("SVG 1.2 Full (May 2004 draft)");
	stray.Add ("SVG 2.0");
	stray.Add ("SVG 2.1 (April 2021 draft)");

	list_ = GSL_OWNER (wxListBox) (new wxListBox (this, wxID_ANY, wxDefaultPosition, wxSize (140, 30), stray, wxLB_SINGLE));
	if (list_ != nullptr)
	{	list_ -> SetSelection (static_cast < int > (version_));
		box_ -> Add (list_, 6, wxEXPAND | wxALL, 5); }

	dialogue_t :: CreateButtons ();
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void svg_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("svg"); }

bool svg_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	list_ -> SetSelection (static_cast < int > (version_));
	return true; }

bool svg_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	const int v = list_ -> GetSelection ();
	PRESUME (v <= sv_2_1, __FILE__, __LINE__);
	version_ = static_cast < e_svg_version > (v);
	return true; }

#endif // WX
