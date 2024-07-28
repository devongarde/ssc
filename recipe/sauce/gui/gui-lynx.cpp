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
#include "gui/gui-lynx.h"

#define LYNX_STYLE   DEF_STYLE
#define LYNX_X       100
#define LYNX_Y       100
#define LYNX_WIDTH   425
#define LYNX_HEIGHT  200

BEGIN_EVENT_TABLE (lynx_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, lynx_t::OnHelpClick)
  EVT_CHECKBOX (check_external, lynx_t::OnExternal)
  EVT_CHECKBOX (check_internal, lynx_t::OnInternal)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (lynx_t, dialogue_t)

lynx_t :: lynx_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (LYNX_X, LYNX_Y), wxSize (LYNX_WIDTH, LYNX_HEIGHT))
{	Create (mummy, id, caption); } 

bool lynx_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (LYNX_X, LYNX_Y), wxSize (LYNX_WIDTH, LYNX_HEIGHT), LYNX_STYLE)) return false;
	CreateControls ();
	return true; }

void lynx_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (grid_ != nullptr)
	{	check_internal_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_internal, "Check links", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (check_internal_ != nullptr)
		{	grid_ -> Add (check_internal_, 0, wxALIGN_RIGHT | wxALL, 5);
	 		check_external_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_external, "Check external links", wxDefaultPosition, wxDefaultSize, 0));
			if (check_external_ != nullptr)
			{	grid_ -> Add (check_external_, 0, wxALL, 5);
	 			check_example_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Report links to example.com etc.", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
				if (check_example_ != nullptr)
				{	grid_ -> Add (check_example_, 0, wxALIGN_RIGHT | wxALL, 5);
	 				check_forwarded_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Report fowards (301s)", wxDefaultPosition, wxDefaultSize, 0));
					if (check_forwarded_ != nullptr)
					{	grid_ -> Add (check_forwarded_, 0, wxALL, 5);
	 					check_local_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Report links to local domains", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
						if (check_local_ != nullptr)
						{	grid_ -> Add (check_local_, 0, wxALIGN_RIGHT | wxALL, 5);
	 						check_once_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Only test an external link once", wxDefaultPosition, wxDefaultSize, 0));
							if (check_once_ != nullptr)
							{	grid_ -> Add (check_once_, 0, wxALL, 5);
	 							check_id_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Check crosslinked IDs", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
								if (check_id_ != nullptr)
								{	grid_ -> Add (check_id_, 0, wxALIGN_RIGHT | wxALL, 5); 
	 								check_revoke_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, "Test certificate revocation", wxDefaultPosition, wxDefaultSize, 0));
									if (check_revoke_ != nullptr)
										grid_ -> Add (check_revoke_, 0, wxALL, 5); } } } } } } }
		box_ -> Add (grid_, 3, wxEXPAND, 5); }

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH);  }

void lynx_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("lynx"); }

void lynx_t :: OnExternal (wxCommandEvent& )
{	if (invalid ()) return;
	const bool e = check_external_ -> IsChecked ();
	check_forwarded_ -> Enable (e);
	check_once_ -> Enable (e);
	check_revoke_ -> Enable (e); }

void lynx_t :: OnInternal (wxCommandEvent& )
{	if (invalid ()) return;
	const bool e = check_internal_ -> IsChecked ();
	check_example_ -> Enable (e);
	check_id_ -> Enable (e);
	check_local_ -> Enable (e);
	check_external_ -> Enable (e);
	const bool f = check_external_ -> IsChecked ();
	check_forwarded_ -> Enable (f && e);
	check_once_ -> Enable (f && e);
	check_revoke_ -> Enable (f && e); }

bool lynx_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    check_example_ -> Set3StateValue (example_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_external_ -> Set3StateValue (external_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_forwarded_ -> Set3StateValue (forwarded_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_id_ -> Set3StateValue (id_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_internal_ -> Set3StateValue (internal_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_local_ -> Set3StateValue (local_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_once_ -> Set3StateValue (once_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_revoke_ -> Set3StateValue (revoke_ ? wxCHK_UNCHECKED : wxCHK_CHECKED); // note reversal
	return true; }

bool lynx_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    example_ = check_example_ -> IsChecked ();
    external_ = check_external_ -> IsChecked ();
    forwarded_ = check_forwarded_ -> IsChecked ();
    id_ = check_id_ -> IsChecked ();
    internal_ = check_internal_ -> IsChecked ();
    local_ = check_local_ -> IsChecked ();
    once_ = check_once_ -> IsChecked ();
    revoke_ = ! check_revoke_ -> IsChecked ();
	return true; }

#endif // WX
