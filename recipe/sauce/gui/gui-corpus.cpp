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
#include "gui/gui-corpus.h"

#define CORPUS_STYLE   DEF_STYLE
#define CORPUS_X       100
#define CORPUS_Y       100
#define CORPUS_WIDTH   300
#define CORPUS_HEIGHT  220

BEGIN_EVENT_TABLE (corpus_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, corpus_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (corpus_t, dialogue_t)

corpus_t :: corpus_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (CORPUS_X, CORPUS_Y), wxSize (CORPUS_WIDTH, CORPUS_HEIGHT))
{	Create (mummy, id, caption); } 

bool corpus_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (CORPUS_X, CORPUS_Y), wxSize (CORPUS_WIDTH, CORPUS_HEIGHT), CORPUS_STYLE)) return false;
	CreateControls ();
	return true; }

void corpus_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;
	PRESUME (invalid (), __FILE__, __LINE__);

	top_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "acquire corpus data from content of:", wxDefaultPosition, wxDefaultSize, 0));
	if (top_ != nullptr)
	{	top_ -> Wrap (-1);
		box_ -> Add (top_, 0, wxALL | wxALIGN_CENTRE_HORIZONTAL, 5); }

	const wxString stray [] = { "<article>", "<body>", "<main>" };
	grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 3, 0, 0));
	if (grid_ != nullptr)
	{	article_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "<article>", wxDefaultPosition, wxDefaultSize, 0));
		if (article_ != nullptr) grid_ -> Add (article_, 0, wxALL, 5);
		body_ = GSL_OWNER (wxCheckBox) (new wxCheckBox( this, wxID_ANY, wxT("<body>"), wxDefaultPosition, wxDefaultSize, 0));
		if (body_ != nullptr) grid_ -> Add (body_, 0, wxALL, 5);
		main_ = GSL_OWNER (wxCheckBox) (new wxCheckBox( this, wxID_ANY, wxT("<main>"), wxDefaultPosition, wxDefaultSize, 0));
		if (main_ != nullptr) grid_ -> Add (main_, 0, wxALL, 5);
		box_ -> Add (grid_, 0,  wxALL | wxALIGN_CENTRE_HORIZONTAL, 5); }

	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_ != nullptr)
	    box_ -> Add (line_, 0, wxEXPAND | wxALL, 5);

	text_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "output corpus XML to:", wxDefaultPosition, wxDefaultSize, 0));
	if (text_ != nullptr)
	{	text_ -> Wrap (-1);
		box_ -> Add (text_, 0, wxALL | wxALIGN_CENTRE_HORIZONTAL, 5); }

	file_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (this, wxID_ANY, "corpus.xml", "output XML to", "*.xml", wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT | wxFLP_SAVE | wxFLP_USE_TEXTCTRL));
	if (file_ != nullptr) box_ -> Add (file_, 0, wxALL | wxALIGN_CENTRE_HORIZONTAL, 5);

	base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
	    box_ -> Add (base_, 0, wxEXPAND | wxALL, 5);

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void corpus_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("corpus"); }

bool corpus_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	if (art_) article_ -> Set3StateValue (wxCHK_CHECKED);
	else article_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (bod_) body_ -> Set3StateValue (wxCHK_CHECKED);
	else body_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (mai_) main_ -> Set3StateValue (wxCHK_CHECKED);
	else main_ -> Set3StateValue (wxCHK_UNCHECKED);
	wxFileName fn (path_.string ());
	file_ -> SetFileName (fn);
	return true; }

bool corpus_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	wxFileName fn (file_ -> GetFileName ());
	path_ = ::std::string (fn.GetName ().c_str ());
	art_ = article_ -> IsChecked ();
	bod_ = body_ -> IsChecked ();
	mai_ = main_ -> IsChecked ();
	return true; }

#endif // WX
