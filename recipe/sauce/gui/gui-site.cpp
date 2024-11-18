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

#define DEFAULT_CORPUS_FN	"corpus.xml"

#define SITE_STYLE   DEF_STYLE
#define SITE_X       100
#define SITE_Y       100
#define SITE_WIDTH   430
#define SITE_HEIGHT  360

BEGIN_EVENT_TABLE (site_t, d1_t)
  EVT_BUTTON (wxID_HELP, site_t::OnHelpClick)
  EVT_BUTTON (button_site_add, site_t::OnAdd)
  EVT_BUTTON (button_site_erase, site_t::OnErase)
  EVT_BUTTON (button_site_rename, site_t::OnRename)
  EVT_TEXT (button_site_rename, site_t::OnTap)
  EVT_LISTBOX (button_site_rename, site_t::OnExtension)
  EVT_LISTBOX_DCLICK (button_site_rename, site_t::OnImpatience)
  EVT_CHECKBOX (check_corpus_output, site_t::OnOutput)
  EVT_CHECKBOX (check_external, site_t::OnExternal)
  EVT_CHECKBOX (check_internal, site_t::OnInternal)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (site_t, d1_t)

site_t :: site_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT))
{	Create (mummy, id, caption); } 

bool site_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT), SITE_STYLE)) return false;
	CreateControls ();
	return true; }

void site_t :: create_controls (wxWindow *parent)
{	stat_default_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Default root " REPERTOIRE ": ", wxDefaultPosition, wxDefaultSize, 0));
	if (stat_default_ != nullptr)
	{	box_ -> Add (stat_default_, 0, wxEXPAND | wxALL, 5);
		dir_default_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl( parent, wxID_ANY, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
		if (dir_default_ !=  nullptr)
			box_ -> Add (dir_default_, 0, wxALL | wxEXPAND, 5); }

	domain_.construct (parent, box_, "Site domain/s:");

	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_ != nullptr)
	    box_ -> Add (line_, 0, wxEXPAND | wxALL, 5);

	grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (grid_ != nullptr)
	{	check_internal_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_internal, "Check links", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (check_internal_ != nullptr)
		{	grid_ -> Add (check_internal_, 0, wxALIGN_RIGHT | wxALL, 5);
	 		check_external_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_external, "Check external links", wxDefaultPosition, wxDefaultSize, 0));
			if (check_external_ != nullptr)
			{	grid_ -> Add (check_external_, 0, wxALL, 5);
	 			check_example_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Report example domains", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
				if (check_example_ != nullptr)
				{	grid_ -> Add (check_example_, 0, wxALIGN_RIGHT | wxALL, 5);
	 				check_forwarded_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Report fowards (301s)", wxDefaultPosition, wxDefaultSize, 0));
					if (check_forwarded_ != nullptr)
					{	grid_ -> Add (check_forwarded_, 0, wxALL, 5);
	 					check_local_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Report local domains", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
						if (check_local_ != nullptr)
						{	grid_ -> Add (check_local_, 0, wxALIGN_RIGHT | wxALL, 5);
	 						check_once_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Test an external link once", wxDefaultPosition, wxDefaultSize, 0));
							if (check_once_ != nullptr)
							{	grid_ -> Add (check_once_, 0, wxALL, 5);
	 							check_id_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Check crosslinked IDs", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
								if (check_id_ != nullptr)
								{	grid_ -> Add (check_id_, 0, wxALIGN_RIGHT | wxALL, 5); 
	 								check_revoke_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Test revocation", wxDefaultPosition, wxDefaultSize, 0));
									if (check_revoke_ != nullptr)
										grid_ -> Add (check_revoke_, 0, wxALL, 5); } } } } } } }
		box_ -> Add (grid_, 0, wxEXPAND, 5); }

    twixt_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (twixt_ != nullptr)
	    box_ -> Add (twixt_, 0, wxEXPAND | wxALL, 5);

    output_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_corpus_output, "output search engine corpus (XML)", wxDefaultPosition, wxDefaultSize, 0));
	if (output_ != nullptr)
	{	box_ -> Add (output_, 0, wxALL, 5);
		file_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (parent, wxID_ANY, "corpus.xml", "output XML to", "*.xml", wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT | wxFLP_SAVE | wxFLP_USE_TEXTCTRL));
		if (file_ != nullptr)
		{	file_ -> Enable (false);
			box_ -> Add (file_, 0, wxALL | wxEXPAND, 5); } }

	wot_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "acquire corpus data from content of:", wxDefaultPosition, wxDefaultSize, 0));
	if (wot_ != nullptr)
	{	wot_ -> Wrap (-1);
		box_ -> Add (wot_, 0, wxALL | wxALIGN_CENTRE_HORIZONTAL, 5); }

	const wxString stray [] = { "<article>", "<body>", "<main>" };
	grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 3, 0, 0));
	if (grid_ != nullptr)
	{	article_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "<article>", wxDefaultPosition, wxDefaultSize, 0));
		if (article_ != nullptr) grid_ -> Add (article_, 0, wxALL, 5);
		body_ = GSL_OWNER (wxCheckBox) (new wxCheckBox( parent, wxID_ANY, wxT("<body>"), wxDefaultPosition, wxDefaultSize, 0));
		if (body_ != nullptr) grid_ -> Add (body_, 0, wxALL, 5);
		main_ = GSL_OWNER (wxCheckBox) (new wxCheckBox( parent, wxID_ANY, wxT("<main>"), wxDefaultPosition, wxDefaultSize, 0));
		if (main_ != nullptr) grid_ -> Add (main_, 0, wxALL, 5);
		box_ -> Add (grid_, 0,  wxALL | wxALIGN_CENTRE_HORIZONTAL, 5); }

	base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
	    box_ -> Add (base_, 0, wxEXPAND | wxALL, 5); }

void site_t :: enable_corpus (const bool b)
{	file_ -> Enable (b);
	article_ -> Enable (b);
	body_ -> Enable (b);
	main_ -> Enable (b);
	wot_ -> Enable (b); }

void site_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void site_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("site"); }

void site_t :: OnAdd (wxCommandEvent& e)
{	domain_.OnAdd (e); }

void site_t :: OnExternal (wxCommandEvent& )
{	if (invalid ()) return;
	const bool e = check_external_ -> IsChecked ();
	check_forwarded_ -> Enable (e);
	check_once_ -> Enable (e);
	check_revoke_ -> Enable (e); }

void site_t :: OnErase (wxCommandEvent& e)
{	domain_.OnErase (e); }

void site_t :: OnExtension (wxCommandEvent& e)
{	domain_.OnText (e); }

void site_t :: OnImpatience (wxCommandEvent& e)
{	domain_.OnImpatience (e); }

void site_t :: OnInternal (wxCommandEvent& )
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

void site_t :: OnOutput (wxCommandEvent& )
{	if (invalid ()) return;
	PRESUME (file_ != nullptr, __FILE__, __LINE__);
	const bool outed = output_ -> IsChecked ();
	if (path_.empty () && outed)
	{	path_ = get_current_folder ();
		path_ /= DEFAULT_CORPUS_FN;
		wxFileName fn (path_.string ());
		file_ -> SetFileName (fn); }
	enable_corpus (outed); }

void site_t :: OnRename (wxCommandEvent& e)
{	domain_.OnRename (e); }

void site_t :: OnTap (wxCommandEvent& e)
{	domain_.OnTap (e); }

bool site_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	if (def_.empty ()) def_ = get_current_folder ();
	dir_default_ -> SetPath (def_.string ().c_str ());
	domain_.preload (site_);
    check_example_ -> Set3StateValue (example_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_external_ -> Set3StateValue (external_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_forwarded_ -> Set3StateValue (forwarded_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_id_ -> Set3StateValue (id_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_internal_ -> Set3StateValue (internal_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_local_ -> Set3StateValue (local_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_once_ -> Set3StateValue (once_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_revoke_ -> Set3StateValue (revoke_ ? wxCHK_UNCHECKED : wxCHK_CHECKED); // note reversal
	if (art_) article_ -> Set3StateValue (wxCHK_CHECKED);
	else article_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (bod_) body_ -> Set3StateValue (wxCHK_CHECKED);
	else body_ -> Set3StateValue (wxCHK_UNCHECKED);
	if (mai_) main_ -> Set3StateValue (wxCHK_CHECKED);
	else main_ -> Set3StateValue (wxCHK_UNCHECKED);
	const bool outed = output_ -> IsChecked ();
	wxFileName fn (path_.string ());
	file_ -> SetFileName (fn);
	enable_corpus (outed);
	return true; }

bool site_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	def_ = ::std::string (dir_default_ -> GetPath ().c_str ());
	site_ = domain_.acquire ();
    example_ = check_example_ -> IsChecked ();
    external_ = check_external_ -> IsChecked ();
    forwarded_ = check_forwarded_ -> IsChecked ();
    id_ = check_id_ -> IsChecked ();
    internal_ = check_internal_ -> IsChecked ();
    local_ = check_local_ -> IsChecked ();
    once_ = check_once_ -> IsChecked ();
    revoke_ = ! check_revoke_ -> IsChecked ();
	if (! output_ -> IsChecked ()) path_.clear ();
	else
	{	wxFileName fn (file_ -> GetFileName ());
		path_ = ::std::string (fn.GetName ().c_str ()); }
	art_ = article_ -> IsChecked ();
	bod_ = body_ -> IsChecked ();
	mai_ = main_ -> IsChecked ();
	return true; }

bool site_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
	create_box (mummy, pos, size);
	if (! create_panel_itself (mummy, id, pos, size, style)) return false;
	create_controls (panel_);
	if (invalid_panel ()) return false;
	panel_ -> SetSizer (box_);
	panel_ -> Layout ();
	box_ -> Fit (panel_);
	return true; }

void site_t :: load_from_context (const context_t& c)
{	site (c.site ());
    def (c.rootp ());
	example (c.example ());
    external (c.external ());
    forwarded (c.forwarded ());
    id (c.crosslinks ());
    inter (c.links ());
    local (c.local ());
    once (c.once ());
    revoke (c.revoke ());
 	folder (c.corpus ());
    article (c.article ());
    body (c.body ());
    main (c.main ()); }

void site_t :: save_to_context (context_t& c) const
{   c.site (site ());
    c.root (def ().string ());
    c.example (example ());
    c.external (external ());
    c.forwarded (forwarded ());
    c.crosslinks (id ());
    c.links (inter ());
    c.local (local ());
    c.once (once ());
    c.revoke (revoke ());
 	c.corpus (folder ());
    c.article (article ());
    c.body (body ());
    c.main (main ()); }

#endif // WX
