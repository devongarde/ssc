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
#include "gui/gui-ontology.h"

#define ONT_STYLE   DEF_STYLE
#define ONT_X       100
#define ONT_Y       100
#define ONT_WIDTH   500
#define ONT_HEIGHT  460

BEGIN_EVENT_TABLE (ontology_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, ontology_t::OnHelpClick)
  EVT_CHECKBOX (check_export, ontology_t::OnExport)
  EVT_CHECKBOX (check_verify, ontology_t::OnVerify)
  EVT_CHOICE (choice_version, ontology_t::OnVersion)
  EVT_DATAVIEW_SELECTION_CHANGED (list_ontology, ontology_t::OnOntology)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (ontology_t, dialogue_t)

#define VERSION_COLUMN	2

ontology_t :: ontology_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: dialogue_t (wxPoint (ONT_X, ONT_Y), wxSize (ONT_WIDTH, ONT_HEIGHT))
{	Create (mummy, id, caption); } 

bool ontology_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (ONT_X, ONT_Y), wxSize (ONT_WIDTH, ONT_HEIGHT), ONT_STYLE)) return false;
	CreateControls ();
	return true; }

void ontology_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	if (vsv_.empty ())
		vsv_ = vsv;
	if (vov_.empty ())
	 	vov_.resize (s_faux);
	if (vont_.empty ())
	{	vont_.resize (s_faux);
		vid_.resize (s_faux);
		for (int i = s_none + 1; i < s_faux; ++i)
		{   const e_ontology es = static_cast < e_ontology > (i);
			const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
			const ::std::string desc (ontology_names.get (es, ONTOLOGY_DESCRIPTION));
			if (desc.empty () || compare_no_case (naam, desc))
			{	vid_.at (i) = naam.c_str ();
				vont_.at (i) = "-"; }
			else 
			{	vid_.at (i) = naam.c_str ();
				vont_.at (i) = desc.c_str (); } } }
	if (versions_.empty ())
	{	versions_.resize (s_faux);
		for (vsv_t::const_iterator i = vsv_.cbegin (); i != vsv_.cend (); ++i)
		{	const e_ontology o = i -> root ();
			if (o < s_faux)
				versions_.at (o).push_back (i -> ver ()); } }

	check_verify_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_verify, "Verify known ontologies", wxDefaultPosition, wxDefaultSize, 0));
	if (check_verify_ != nullptr)
		box_ -> Add (check_verify_, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	line1_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line1_ != nullptr)
		box_ -> Add (line1_, 0, wxEXPAND | wxALL, 5);

	box_export_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_export_ != nullptr)
	{	check_export_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, check_export, "Export ontology data to", wxDefaultPosition, wxDefaultSize, 0));
		if (check_export_ != nullptr)
		{	box_export_ -> Add (check_export_, 0, wxALL, 5);
			pick_export_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (this, wxID_ANY, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
			if (pick_export_ != nullptr)
				box_export_ -> Add (pick_export_, 0, wxALL, 5);
				box_ -> Add (box_export_, 1, wxALIGN_CENTER_HORIZONTAL, 5); } }

	line2_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line2_ != nullptr)
		box_ -> Add (line2_, 0, wxEXPAND | wxALL, 5);

	data_ontology_ = GSL_OWNER (wxDataViewListCtrl) (new wxDataViewListCtrl (this, list_ontology, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE));
	if (data_ontology_ != nullptr)
	{	data_ontology_ -> SetMinSize (wxSize (-1, 250));
		column_ontology_ = data_ontology_ -> AppendTextColumn ("Name", wxDATAVIEW_CELL_INERT, 60, static_cast < wxAlignment > (wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
		if (column_ontology_ != nullptr)
		{	column_description_ = data_ontology_ -> AppendTextColumn ("Description", wxDATAVIEW_CELL_INERT, 250, static_cast < wxAlignment > (wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
			if (column_description_ != nullptr)
			{	column_range_ = data_ontology_ -> AppendTextColumn ("Version", wxDATAVIEW_CELL_INERT, 60, static_cast < wxAlignment > (wxALIGN_CENTRE_HORIZONTAL), wxDATAVIEW_COL_RESIZABLE);
				if (column_range_ != nullptr)
				{	column_version_ = data_ontology_ -> AppendTextColumn ("Range", wxDATAVIEW_CELL_INERT, 80, static_cast < wxAlignment > (wxALIGN_CENTRE_HORIZONTAL), wxDATAVIEW_COL_RESIZABLE);
					if (column_version_ != nullptr) box_ -> Add (data_ontology_, 0, wxALL | wxEXPAND, 5); } } } }

	box_version_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_version_ != nullptr)
	{	static_version_	= GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "Presume version:", wxDefaultPosition, wxDefaultSize, 0));
		if (static_version_ != nullptr)
		{	static_version_ -> Wrap (-1);
			box_version_ -> Add (static_version_, 0, wxALIGN_CENTER_VERTICAL, 5);
			wxString ont [] = { "-" };
			choice_version_ = GSL_OWNER (wxChoice) (new wxChoice (this, choice_version, wxDefaultPosition, wxSize (100, -1), 1, ont, 0));
			if (choice_version_ != nullptr)
			{	choice_version_ -> SetSelection (0);
				box_version_ -> Add (choice_version_, 0, wxALL, 5);
				box_ -> Add (box_version_, 1, wxALIGN_CENTER_HORIZONTAL, 5); } } }

	line3_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line3_ != nullptr)
		box_ -> Add (line3_, 0, wxEXPAND | wxALL, 5);

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void ontology_t :: general_enable (const bool e)
{	check_export_ -> Enable (e);
	choice_version_ -> Enable (e);
	data_ontology_ -> Enable (e);
	pick_export_ -> Enable (e);
	static_version_ -> Enable (e);
	if (e)
	{	pick_export_ -> Enable (check_export_ -> IsChecked ());
		choice_version_ -> Enable (ontological_);
		static_version_ -> Enable (ontological_); } }

void ontology_t :: OnExport (wxCommandEvent& )
{	if (invalid ()) return;
	const bool e = check_export_ -> IsChecked ();
	pick_export_ -> Enable (e); }

void ontology_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("ontology"); }

void ontology_t :: OnOntology (wxDataViewEvent& )
{   if (invalid ()) return;
	choice_version_ -> Clear ();
	const int l = data_ontology_ -> GetSelectedRow ();
	if (l == wxNOT_FOUND)
	 	choice_version_ -> Append ("");
	else
	{	const e_ontology o = static_cast < e_ontology > (l+1);
		if (versions_.at (o).empty ()) choice_version_ -> Append ("-");
		else if (versions_.at (o).size () == 1)
		{	const wxString val = data_ontology_ -> GetTextValue (l, VERSION_COLUMN);
			choice_version_ -> Append (val); }
		else
		{	const wxString val = data_ontology_ -> GetTextValue (l, VERSION_COLUMN);
			int sel = 0;
			for (int i = 0; i < versions_.at (o).size (); ++i)
			{	const wxString ver = versions_.at (o).at (i);
				if (ver == val) sel = i;
				choice_version_ -> Append (ver); }
			choice_version_ -> SetSelection (sel);
			choice_version_ -> Enable (true);
			static_version_ -> Enable (true);
			vov_.at (o) = sel;
			ontological_ = true;
			return; }
		vov_.at (o) = 0; }
	choice_version_ -> SetSelection (0); 
	choice_version_ -> Enable (false);
	static_version_ -> Enable (false);
	ontological_ = false; }

void ontology_t :: OnVerify (wxCommandEvent& )
{	if (invalid ()) return;
	general_enable (check_verify_ -> IsChecked ()); }

void ontology_t :: OnVersion (wxCommandEvent& )
{   if (invalid ()) return;
    const int v = choice_version_ -> GetSelection ();
	if (v != wxNOT_FOUND)
	{	wxString ver = choice_version_ -> GetString (v);
		const int o = data_ontology_ -> GetSelectedRow ();
		data_ontology_ -> SetTextValue (ver, o, VERSION_COLUMN); } }

bool ontology_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	check_export_ -> SetValue (export_);	
	check_verify_ -> SetValue (verify_);
	pick_export_ -> SetPath (path_.c_str ());	
	restock_ontology ();
	general_enable (verify_);	
	return true; }

bool ontology_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	export_ = check_export_ -> GetValue ();	
	verify_ = check_verify_ -> GetValue ();
	path_ = ::boost::filesystem::path (pick_export_ -> GetPath ().c_str ());	
	return true; }

void ontology_t :: restock_ontology ()
{	if (invalid ()) return;
	if (stocked_)
	{	data_ontology_ -> DeleteAllItems ();
		stocked_ = false; }
	for (int i = 1; i < s_faux; ++i)
	{	vov_.at (i) = -1;
		wxVector < wxVariant > item;
		item.push_back (vid_.at (i).c_str ());
		item.push_back (vont_.at (i).c_str ());
		if (versions_.at (i).empty ())
		{	item.push_back ("-");	
			item.push_back ("-"); }
		else
		{	::std::string vs = * (versions_.at (i).cbegin ());
			::std::string l;
			if (versions_.at (i).size () == 1) l = vs;
			else
			{	if (versions_.at (i).size () == 2) vs += ", ";
				else vs += " - ";
				const vstr_t& ffs = versions_.at (i);
				vstr_t::const_iterator ij = ffs.cend ();
				l = *(--ij);
				vs += l; }	
			item.push_back (l.c_str ());
			item.push_back (vs.c_str ());
			vov_.at (i) = GSL_NARROW_CAST < int > (versions_.at (i).size () - 1); }
		data_ontology_ -> AppendItem (item); }
	stocked_ = true; }

#endif // WX
