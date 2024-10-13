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
#include "gui/gui-site.h"

#define SITE_STYLE   DEF_STYLE
#define SITE_X       100
#define SITE_Y       100
#define SITE_WIDTH   430
#define SITE_HEIGHT  360

BEGIN_EVENT_TABLE (site_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, site_t::OnHelpClick)
  EVT_BUTTON (button_add, site_t::OnAdd)
  EVT_BUTTON (button_erase, site_t::OnErase)
  EVT_BUTTON (button_rename, site_t::OnRename)
  EVT_TEXT (button_rename, site_t::OnTap)
  EVT_LISTBOX (button_rename, site_t::OnExtension)
  EVT_LISTBOX_DCLICK (button_rename, site_t::OnImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (site_t, dialogue_t)

site_t :: site_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT))
{	Create (mummy, id, caption); } 

bool site_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT), SITE_STYLE)) return false;
	CreateControls ();
	return true; }

void site_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	domain_.construct (*this, "Domains:");

	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_ != nullptr)
	    box_ -> Add (line_, 0, wxEXPAND | wxALL, 5);

	stat_default_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Default directory:", wxDefaultPosition, wxDefaultSize, 0));
	if (stat_default_ != nullptr)
	{	stat_default_ -> Wrap (-1);
		box_ -> Add (stat_default_, 0, wxALL, 5); }

	dir_default_ = GSL_OWNER (wxGenericDirCtrl) (new wxGenericDirCtrl (this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL | wxSUNKEN_BORDER, wxEmptyString, 0));
	if (dir_default_ != nullptr)
	{	dir_default_ -> ShowHidden (false);
		box_ -> Add (dir_default_, 5, wxEXPAND | wxALL, 5); }

	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line_ != nullptr) box_ -> Add (line_, 0, wxEXPAND | wxALL, 5);

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void site_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("site"); }

void site_t :: OnAdd (wxCommandEvent& e)
{	domain_.OnAdd (e); }

void site_t :: OnErase (wxCommandEvent& e)
{	domain_.OnErase (e); }

void site_t :: OnRename (wxCommandEvent& e)
{	domain_.OnRename (e); }

void site_t :: OnTap (wxCommandEvent& e)
{	domain_.OnTap (e); }

void site_t :: OnExtension (wxCommandEvent& e)
{	domain_.OnText (e); }

void site_t :: OnImpatience (wxCommandEvent& e)
{	domain_.OnImpatience (e); }

bool site_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	dir_default_ -> SetPath (def_.string ().c_str ());
	domain_.preload (site_);
	return true; }

bool site_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	def_ = ::std::string (dir_default_ -> GetPath ().c_str ());
	site_ = domain_.acquire ();
	return true; }

#endif // WX
