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
#include "main/args.h"
#include "gui/gui-app.h"
#include "gui/gui-validation.h"

#define VALID_STYLE   DEF_STYLE
#define VALID_X       100
#define VALID_Y       100
#define VALID_WIDTH   400
#define VALID_HEIGHT  250

BEGIN_EVENT_TABLE (valid_t, d1_t)
  EVT_CHOICE (choice_validation_version, valid_t::OnChoice)
  EVT_BUTTON (wxID_HELP, valid_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (valid_t, d1_t)

//#define BASE_VALID ATTRIB, CHARSET, CLASS, COLOUR, COUNTRY, CURRENCY, ELEMENT, ELEMATTR, EXTENSION, FF, FV, HTTPEQUIV, LANG, METANAME, MIMETYPE, REL, SGML
#define BASE_VALID "Attribute", "Charset", "Class", "Colour", "Country Code", "Currency Code", "Element", "Element+Attribute", "Extension", "Font Feature", "Font Variation", "HttpEquiv Macro", \
	"Language Code", "Meta Name", "Mimetype", "REL", "SGML Schema"
#define BASE_COUNT 17

::std::vector < wxString > vld;	// the code presumes this won't be fiddled with whilst a dialogue is open

valid_t :: valid_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT))
{	Create (mummy, id, caption); } 

bool valid_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT), VALID_STYLE)) return false;
	CreateControls ();
	return true; }

void valid_t :: create_controls (wxWindow *parent)
{	check_microdata_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_spell, "HTML5 microdata", wxDefaultPosition, wxDefaultSize, 0));
	if (check_microdata_ != nullptr)
	{	box_ -> Add (check_microdata_, 0, wxALIGN_CENTER_HORIZONTAL, 5);
		line_microdata_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
			if (line_microdata_ != nullptr)
				box_ -> Add (line_microdata_, 0, wxEXPAND | wxALL, 5); }

	box_for_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));

	if (box_for_ != nullptr)
	{	stat_for_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Additional valid values for:", wxDefaultPosition, wxDefaultSize, 0));
		if (stat_for_ != nullptr)
		{	box_for_ -> Add (stat_for_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
			if (vld.empty ())
			{	vld.assign ( { BASE_VALID } );
				for (auto o : context.validation ())
				{	const ::std::string s (o.first);
					if (! s.empty ())
					{	const ::std::string::size_type pos = s.find ('.');
						if ((pos != ::std::string::npos) && (pos < s.length () - 1))
							 vld.push_back (s.substr (pos+1)); } }
				PRESUME ((vld.size () == context.validation ().size () + BASE_COUNT), __FILE__, __LINE__);
				::std::sort (vld.begin (), vld.end ()); }
			choice_for_ = GSL_OWNER (wxChoice) (new wxChoice (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, GSL_NARROW_CAST < int > (vld.size ()), vld.data (), 0));
			if (choice_for_ != nullptr)
			{	choice_for_ -> SetSelection (0);
				box_for_ -> Add (choice_for_, 0, wxALL, 5);
				box_ -> Add (box_for_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }

	val_.construct (parent, box_, "values");

	line_base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
		if (line_base_ != nullptr)
			box_ -> Add (line_base_, 0, wxEXPAND | wxALL, 5); }

void valid_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void valid_t :: populate ()
{   if (invalid ()) return;
    const int l = choice_for_ -> GetSelection ();
	if (l != wxNOT_FOUND)
	{	const e_css_version sel = GSL_NARROW_CAST < e_css_version > (l);
		if (sel < BASE_COUNT)
		{

		}
		else
		{

		} }
		

/*		if (sel != css_bespoke)
		{	v_.css_version (sel);
			for (unsigned int i = 0; i < c_bad; ++i)
				set_module (static_cast < e_css_module > (i)); } } }
*/
}


void valid_t :: OnChoice (wxCommandEvent& )
{	 }

void valid_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("validation"); }

bool valid_t :: TransferDataToWindow ()
{	if (invalid ()) return false;

	return true; }

bool valid_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	

	return true; }

bool valid_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
	create_box (mummy, pos, size);
	if (! create_panel_itself (mummy, id, pos, size, style)) return false;
	create_controls (panel_);
	if (invalid_panel ()) return false;
	panel_ -> SetSizer (box_);
	panel_ -> Layout ();
	box_ -> Fit (panel_);
	return true; }

void valid_t :: load_from_context (const context_t& )
{	/* to do */	}

void valid_t :: save_to_context (context_t& ) const
{	/* to do */	}

#endif // WX
