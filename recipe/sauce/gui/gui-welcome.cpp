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
#include "main/context.h"
#include "main/args.h"
#include "gui/gui-app.h"
#include "gui/gui-welcome.h"

#define VALID_STYLE   DEF_STYLE
#define VALID_X       100
#define VALID_Y       100
#define VALID_WIDTH   425
#define VALID_HEIGHT  550

BEGIN_EVENT_TABLE (welcome_t, d2_t)
  EVT_BUTTON (wxID_ABOUT, welcome_t::OnAboutClick)
  EVT_BUTTON (wxID_CANCEL, welcome_t::OnCancelClick)
  EVT_BUTTON (wxID_HELP, welcome_t::OnHelpClick)
  EVT_BUTTON (wxID_OK, welcome_t::OnOkClick)
  EVT_BUTTON (button_config, welcome_t::OnConfigClick)
  EVT_RADIOBUTTON (radio_root, welcome_t::OnClickRoot)	
  EVT_RADIOBUTTON (radio_snippet, welcome_t::OnClickSnippet)	
END_EVENT_TABLE ()

IMPLEMENT_CLASS (welcome_t, d2_t)

welcome_t :: welcome_t (wxWindow *mummy, const context_t& c, wxWindowID id, const wxString& caption)
	: d2_t (wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT)), c_ (c)
{	Create (mummy, id, caption);
	root_ = get_current_folder (); } 

bool welcome_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d2_t :: Create (mummy, id, caption, wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT), VALID_STYLE)) return false;
	CreateControls ();
	return true; }

void welcome_t :: CreateControls ()
{	if (interrogate < wxDialog > :: invalid ()) return;

	static_nitpickery_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Click your nitpickery lick...", wxDefaultPosition, wxDefaultSize, 0));
	if (static_nitpickery_ != nullptr)
	{	static_nitpickery_ -> Wrap (-1);
		box_ -> Add (static_nitpickery_, 0, wxEXPAND | wxALL, 5); }

	radio_root_ = GSL_OWNER (wxRadioButton) (new wxRadioButton (this, radio_root, "&Website root:", wxDefaultPosition, wxDefaultSize, wxRB_GROUP));
	if (radio_root_ != nullptr)
	{	dir_root_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (this, dir_root, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
		if (dir_root_ != nullptr)
		{	line_root_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
			if (line_root_ != nullptr)
			{	box_ -> Add (radio_root_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (dir_root_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (line_root_, 0, wxEXPAND | wxALL, 5); } } }

	radio_snippet_ = GSL_OWNER (wxRadioButton) (new wxRadioButton (this, radio_snippet, "&HTML snippet:", wxDefaultPosition, wxDefaultSize, 0));
	if (radio_snippet_ != nullptr)
	{	text_snippet_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (this, text_snippet, wxEmptyString, wxDefaultPosition, wxSize (360, 180), wxTE_MULTILINE | wxHSCROLL | wxVSCROLL | wxWANTS_CHARS));
		if (text_snippet_ != nullptr)
		{	line_snippet_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
			if (line_snippet_ != nullptr)
			{	box_ -> Add (radio_snippet_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (text_snippet_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (line_snippet_, 0, wxEXPAND | wxALL, 5); } } }

	static_config_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Standards:", wxDefaultPosition, wxDefaultSize, 0));
	if (static_config_ != nullptr)
	{	static_config_ -> Wrap (-1);
		text_summary_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (this, text_summary, wxEmptyString, wxDefaultPosition, wxSize (360, 60), wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP | wxTE_NO_VSCROLL));
		if (text_summary_ != nullptr)
		{	text_summary_ -> SetValue (c_.report (gr_summary));
			text_summary_ -> Enable (false);
			button_configure_ = GSL_OWNER (wxButton) (new wxButton (this, button_config, "&Modify...", wxDefaultPosition, wxDefaultSize, 0));
			if (button_configure_ != nullptr)
			{	box_ -> Add (static_config_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (text_summary_, 0, wxEXPAND | wxALL, 5);
				box_ -> Add (button_configure_, 0, wxALIGN_RIGHT | wxALL, 5); } } }

	line_base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line_base_ != nullptr)
		box_ -> Add (line_base_, 0, wxEXPAND | wxALL, 5);

	d2_t :: CreateButtons ();
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void welcome_t :: OnClickRoot (wxCommandEvent& )
{	if (invalid ()) return;
	rooted_ = true;
	text_snippet_ -> Enable (false);
	dir_root_ -> Enable (true); }

void welcome_t :: OnClickSnippet (wxCommandEvent& )
{	if (invalid ()) return;
	rooted_ = false;
	text_snippet_ -> Enable (true);
	dir_root_ -> Enable (false); }

void welcome_t :: OnConfigClick (wxCommandEvent& )
{	if (invalid ()) return;
    standard_t w (this, c_, gp_html);
    if (w.ShowModal () == wxID_OK)
	{	c_ = w.c ();
		text_summary_ -> SetValue (c_.report (gr_summary).c_str ()); } }

void welcome_t :: OnAboutClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("about"); }

void welcome_t :: OnCancelClick (wxCommandEvent& )
{	EndModal (wxID_CANCEL); }

void welcome_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("welcome"); }

void welcome_t :: OnOkClick (wxCommandEvent& )
{	TransferDataFromWindow ();
	if (snippet_.empty () && root_.empty ()) EndModal (wxID_CANCEL);
	else EndModal (wxID_OK); }

bool welcome_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	rooted_ = true;
	text_snippet_ -> Enable (false);
	dir_root_ -> SetPath (root_.c_str ());	
    text_snippet_ -> SetValue (snippet_.c_str ());
	return true; }

bool welcome_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	root_ = ::boost::filesystem::path (dir_root_ -> GetPath ().c_str ());	
	snippet_ = text_snippet_ -> GetValue ().c_str ();
#ifdef DEBUG
	cmd_.push_back (VERBOSE_SW);
	cmd_.push_back (INFO);
#endif // DEBUG
	cmd_.push_back (DFTHRD_SW);
	cmd_.push_back ("1");
	if (! rooted_)
	{	cmd_.push_back (FNCYSWTCH HTML SNIPPET);
		cmd_.push_back (snippet_); }

	// directory called .ssc  ... default datapath?
	//		if has config file, use that
	//      otherwise, root
	// other directory  ... root
	// file . CONF ... config file
	// file . PERSIST ... persist file; barf
	// file . SSC ... temporary filename; barf
	// otherwise root is just a single file

	else if (compare_no_case (DEFAULT_DATAPATH, root_.filename ().string ()))
	{	if (::boost::filesystem::exists (root_ / DEFAULT_CONFIG_FILE))
		{	cmd_.push_back (FILE_SW);
			cmd_.push_back (root_.string ()); }
		else	
		{	cmd_.push_back (ROOT_SW);
			cmd_.push_back (root_.string ()); } }
	else if (! root_.has_filename ())
	{	cmd_.push_back (ROOT_SW);
		cmd_.push_back (root_.string ()); }
	else if (compare_no_case (DEF_CONF_EXT, root_.extension ().string ()))
	{	cmd_.push_back (FILE_SW);
		cmd_.push_back (root_.string ()); }
	else if (compare_no_case (DEF_PERSIST_EXT, root_.extension ().string ()))
	{	return false; }
	else if (compare_no_case (DEF_TEMP_EXT, root_.extension ().string ()))
	 	return false;
	else 
	{	cmd_.push_back (ROOT_SW);
		cmd_.push_back (root_.string ()); }
	return true; }

void welcome_t :: set_default ()
{	c_.html_ver (html_default); }

#endif // WX
