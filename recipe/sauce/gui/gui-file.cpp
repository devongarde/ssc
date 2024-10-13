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
#include "gui/gui-file.h"

#define FILE_STYLE   DEF_STYLE
#define FILE_X       100
#define FILE_Y       100
#define FILE_WIDTH   300
#define FILE_HEIGHT  350

BEGIN_EVENT_TABLE (file_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, file_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (file_t, dialogue_t)

file_t :: file_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (FILE_X, FILE_Y), wxSize (FILE_WIDTH, FILE_HEIGHT))
{	Create (mummy, id, caption); } 

bool file_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (FILE_X, FILE_Y), wxSize (FILE_WIDTH, FILE_HEIGHT), FILE_STYLE)) return false;
	CreateControls ();
	return true; }

void file_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	stat_config_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Configuration directory:", wxDefaultPosition, wxDefaultSize, 0));
	if (stat_config_ != nullptr)
	{	stat_config_ -> Wrap (-1);
		box_ -> Add (stat_config_, 0, wxALL, 5); }

	dir_config_ = GSL_OWNER (wxGenericDirCtrl) (new wxGenericDirCtrl (this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL | wxSUNKEN_BORDER, wxEmptyString, 0));
	if (dir_config_ != nullptr)
	{	dir_config_ -> ShowHidden (false);
		box_ -> Add (dir_config_, 5, wxEXPAND | wxALL, 5); }
	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line_ != nullptr) box_ -> Add (line_, 0, wxEXPAND | wxALL, 5);

	box_persist_ =  GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_persist_ != nullptr)
	{	stat_persist_ =  GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Persist:", wxDefaultPosition, wxDefaultSize, 0));
		if (stat_persist_ != nullptr)
		{	stat_persist_ -> Wrap (-1);
			box_persist_ -> Add (stat_persist_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5); }
		pick_persist_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (this, wxID_ANY, wxEmptyString, "Select a file", "*.ssc", wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE));
		if (pick_persist_ != nullptr)
		{	box_persist_ -> Add (pick_persist_, 0, wxALL, 5);
			if (! out_.empty ()) pick_persist_ -> SetFileName (wxFileName (persist_.c_str ()));
			else try
			{	pick_persist_ -> SetFileName (wxFileName ((::boost::filesystem::current_path () / "www.ssc").c_str ())); }
			catch (...)
			{	pick_persist_ -> SetFileName (wxFileName ("www.ssc")); } }
		box_ -> Add (box_persist_, 1, wxEXPAND, 5); }

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void file_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("file"); }

bool file_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	if (! config_.empty ()) dir_config_ -> SetPath (config_.c_str ());
	else try
	{	dir_config_ -> SetPath (::boost::filesystem::current_path ().c_str ()); }
	catch (...)
#ifdef WIN32
	{	dir_config_ -> SetPath ("C:\\"); }
#else // WIN32
	{	dir_config_ -> SetPath ("~"); }
#endif // WIN32
	if (! persist_.empty ()) pick_persist_ -> SetFileName (wxFileName (persist_.c_str ()));
	else try
	{	pick_persist_ -> SetFileName (wxFileName ((::boost::filesystem::current_path () / "nits.ssc").c_str ())); }
	catch (...)
	{	pick_persist_ -> SetFileName (wxFileName ("nits.ssc")); }
	return true; }

bool file_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	config_ = ::std::string (dir_config_ -> GetPath ().c_str ());
	persist_ = ::std::string (pick_persist_ -> GetFileName ().GetFullPath ().c_str ());
	return true; }

#endif // WX
