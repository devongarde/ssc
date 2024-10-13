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
#include "gui/gui-general.h"

#define GEN_STYLE   DEF_STYLE
#define GEN_X       100
#define GEN_Y       100
#define GEN_WIDTH   400
#define GEN_HEIGHT  360
#define MIN_FILE_SIZE 1024

BEGIN_EVENT_TABLE (general_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, general_t::OnHelpClick)
  EVT_CHECKBOX (check_file_size, general_t::OnMax)
#ifndef NO_FRED
  EVT_CHECKBOX (check_fred, general_t::OnFred)
#endif // NO_FRED
END_EVENT_TABLE ()

IMPLEMENT_CLASS (general_t, dialogue_t)

general_t :: general_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (GEN_X, GEN_Y), wxSize (GEN_WIDTH, GEN_HEIGHT))
{	Create (mummy, id, caption); } 

bool general_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (GEN_X, GEN_Y), wxSize (GEN_WIDTH, GEN_HEIGHT), GEN_STYLE)) return false;
	CreateControls ();
	return true; }

void general_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	const bool rational = app -> frame () -> rational ();
	
	box_check_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_check_ != nullptr)
	{	static_check_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "verify:", wxDefaultPosition, wxDefaultSize, 0));
		if (static_check_ != nullptr)
		{	static_check_ -> Wrap (-1);
			box_check_ -> Add (static_check_, 0, wxALL, 5);
			check_css_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "styled classes", wxDefaultPosition, wxDefaultSize, 0));
			if (check_css_ != nullptr)
			{	box_check_ -> Add (check_css_, 0, wxALL, 5 );
				check_other_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "every class", wxDefaultPosition, wxDefaultSize, 0));
				if (check_other_ != nullptr)
				{	box_check_ -> Add (check_other_, 0, wxALL, 5 );   
					check_rdfa_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "RDFa", wxDefaultPosition, wxDefaultSize, 0));
					if (check_rdfa_ != nullptr)
					 	box_check_ -> Add (check_rdfa_, 0, wxALL, 5 ); } } }
		box_ -> Add (box_check_, 0, wxALL, 5); }

	line_5_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_5_ != nullptr)
	    box_ -> Add (line_5_, 0, wxEXPAND | wxALL, 5);

	check_vcs_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "ignore version control files", wxDefaultPosition, wxDefaultSize, 0));
	if (check_vcs_ != nullptr)
	 	box_ -> Add (check_vcs_, 0, wxALL | wxALIGN_CENTRE_HORIZONTAL, 5 );

#ifndef NO_FRED
	line_1_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_1_ != nullptr)
	    box_ -> Add (line_1_, 0, wxEXPAND | wxALL, 5);

	box_fred_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_fred_ != nullptr)
	{	check_fred_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_fred, "limit threads to:", wxDefaultPosition, wxDefaultSize, 0));
		if (check_fred_ != nullptr)
		{	box_fred_ -> Add (check_fred_, 0, wxALIGN_CENTRE_VERTICAL, 5 );
			spin_fred_ = GSL_OWNER (wxSpinCtrl) (new wxSpinCtrl (this, spin_fred, "1", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, GSL_NARROW_CAST < int > (fred_t :: no_more_than ()), 0));
			if (spin_fred_ != nullptr)
			{	if (rational) spin_fred_ -> SetIncrement (-1); // hit down, the number goes down
			 	box_fred_ -> Add (spin_fred_, 0, wxALIGN_CENTRE_VERTICAL, 5); }
			box_ -> Add (box_fred_, 1, wxALIGN_CENTRE_HORIZONTAL, 5); } }
#endif // NO_FRED

	line_2_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_2_ != nullptr)
	    box_ -> Add (line_2_, 0, wxEXPAND | wxALL, 5);

	exclude_.construct (*this, "exclude these extensions:", "tmp");

	line_3_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_3_ != nullptr)
	    box_ -> Add (line_3_, 0, wxEXPAND | wxALL, 5);

	box_max_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_max_ != nullptr)
	{	check_max_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_file_size, "maximum file size (bytes):", wxDefaultPosition, wxDefaultSize, 0));
		if (check_max_ != nullptr)
		{	box_max_ -> Add (check_max_, 0, wxALIGN_CENTRE_VERTICAL, 5 );
			BOOST_STATIC_ASSERT (def_max_file_size >= MIN_FILE_SIZE);
			spin_max_ = GSL_OWNER (wxSpinCtrl) (new wxSpinCtrl (this, spin_file_size, "1024", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, MIN_FILE_SIZE, def_max_file_size, 0));
			if (spin_max_ != nullptr)
			{	if (rational) spin_max_ -> SetIncrement (-1); // hit down, the number goes down
			 	box_max_ -> Add (spin_max_, 0, wxALIGN_CENTRE_VERTICAL, 5); }
			box_ -> Add (box_max_, 1, wxALIGN_CENTRE_HORIZONTAL, 5); } }

	line_4_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_4_ != nullptr)
	    box_ -> Add (line_4_, 0, wxEXPAND | wxALL, 5);

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void general_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("general"); }

#ifndef NO_FRED
void general_t :: enable_fred (const bool b)
{	PRESUME (spin_fred_ != nullptr, __FILE__, __LINE__);
	spin_fred_ -> Enable (b);
	spin_fred_ -> Refresh (); }
#endif // NO_FRED

void general_t :: enable_max (const bool b)
{	PRESUME (spin_max_ != nullptr, __FILE__, __LINE__);
	spin_max_ -> Enable (b);
	spin_max_ -> Refresh (); }

void general_t :: OnMax (wxCommandEvent& )
{	if (invalid ()) return;
	PRESUME (check_max_ != nullptr, __FILE__, __LINE__);
	enable_max (check_max_ -> IsChecked ()); }

#ifndef NO_FRED
void general_t :: OnFred (wxCommandEvent& )
{	if (invalid ()) return;
	PRESUME (check_fred_ != nullptr, __FILE__, __LINE__);
	enable_fred (check_fred_ -> IsChecked ()); }
#endif // NO_FRED

bool general_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	if (css_) check_css_ -> Set3StateValue (wxCHK_CHECKED);
	else check_css_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (other_) check_other_ -> Set3StateValue (wxCHK_CHECKED);
	else check_other_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (rdfa_) check_rdfa_ -> Set3StateValue (wxCHK_CHECKED);
	else check_rdfa_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (vcs_) check_vcs_ -> Set3StateValue (wxCHK_CHECKED);
	else check_vcs_ -> Set3StateValue (wxCHK_UNCHECKED);
	spin_max_ -> SetValue (max_);
	if (max_ == 0)
	{	check_max_ -> Set3StateValue (wxCHK_UNCHECKED);
		spin_max_ -> Enable (false); }
	else
	{	check_max_ -> Set3StateValue (wxCHK_CHECKED);
		spin_max_ -> Enable (true); }
#ifndef NO_FRED
	spin_fred_ -> SetValue (fred_);
	if (fred_ == 0)
	{	check_fred_ -> Set3StateValue (wxCHK_UNCHECKED);
		spin_fred_ -> Enable (false); }
	else
	{	check_fred_ -> Set3StateValue (wxCHK_CHECKED);
		spin_fred_ -> Enable (true); }
#endif // NO_FRED
	return true; }

bool general_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	css_ = check_css_ -> IsChecked ();
	other_ = check_other_ -> IsChecked ();
	rdfa_ = check_rdfa_ -> IsChecked ();
	vcs_ = check_vcs_ -> IsChecked ();
	if (! check_max_ -> IsChecked ()) max_ = 0;
	else max_ = spin_max_ -> GetValue ();
#ifndef NO_FRED
	if (! check_fred_ -> IsChecked ()) fred_ = 0;
	else fred_ = spin_fred_ -> GetValue ();
#endif // NO_FRED
	return true; }

void general_t :: max_file_size (const unsigned int& m)
{   PRESUME (m >= MIN_FILE_SIZE, __FILE__, __LINE__);
	max_ = m; }    

#ifndef NO_FRED
void general_t :: fred (const unsigned short& t)
{   PRESUME (t <= fred_t :: no_more_than (), __FILE__, __LINE__);
    fred_ = t; }    
#endif // NO_FRED

#endif // WX
