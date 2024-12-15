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
#include "gui/gui-dialogue.h"
#include "gui/gui-listedit.h"

bool listedit_manager :: construct (wxWindow* parent, wxBoxSizer* box, const char* desc, const char* def, bool file, bool comma, bool line)
{	VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
	VERIFY_NOT_NULL (box, __FILE__, __LINE__); 
	VERIFY_NOT_NULL (desc, __FILE__, __LINE__);
	has_file_ = file;
	has_text_ = comma || ! has_file_;
	if (line)
	{	line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
		if (line_ != nullptr)
			box -> Add (line_, 0, wxEXPAND | wxALL, 5); }
	box_ext_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_ext_ != nullptr)
    {   box_ext_bloc_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
	    if (box_ext_bloc_ != nullptr)
        {   stat_ext_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, desc, wxDefaultPosition, wxDefaultSize, 0));
            if (stat_ext_ != nullptr)
            {   stat_ext_ -> Wrap (-1);
                box_ext_bloc_ -> Add (stat_ext_, 1, wxALL, 5); }
	        box_file_text_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	        if (box_file_text_ != nullptr)
			{	if (has_file_)
				{	filename_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (parent, file_id_, wxEmptyString, "Select a file", "*.*", wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_FILE_MUST_EXIST | wxFLP_OPEN));
					if (filename_ != nullptr)
					 	box_file_text_ -> Add (filename_, 1, wxALL, 5); }
				if (has_text_)
				{	text_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (parent, text_id_, wxEmptyString, wxDefaultPosition, wxSize (150, -1), 0));
					if (text_ != nullptr)
						box_file_text_ -> Add (text_, 1, wxALL, 5); }
	            box_ext_bloc_ -> Add (box_file_text_, 1, wxALIGN_CENTRE_HORIZONTAL, 5 ); }
	        box_ext_butt_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	        if (box_ext_butt_ != nullptr)
            {   add_ = GSL_OWNER (wxButton) (new wxButton (parent, add_id_, ADD_TEXT, wxDefaultPosition, wxSize (30, -1), 0));
                if (add_ != nullptr)
	            {   box_ext_butt_ -> Add (add_, 1, wxALL, 5);
					erase_ = GSL_OWNER (wxButton) (new wxButton (parent, erase_id_, REMOVE_TEXT, wxDefaultPosition, wxSize (30, -1), 0));
					if (erase_ != nullptr)
					{	box_ext_butt_ -> Add (erase_, 1, wxALL, 5);
						rename_ = GSL_OWNER (wxButton) (new wxButton (parent, rename_id_, RENAME_TEXT, wxDefaultPosition, wxSize (30, -1), 0));
						if (rename_ != nullptr)
							box_ext_butt_ -> Add (rename_, 1, wxALL, 5); } }
	            box_ext_bloc_ -> Add (box_ext_butt_, 1, wxALIGN_CENTRE_HORIZONTAL, 5 ); }
            box_ext_ -> Add (box_ext_bloc_, 1, wxALIGN_CENTRE_VERTICAL, 5 ); }
		list_ = GSL_OWNER (wxListBox) (new wxListBox (parent, list_id_, wxDefaultPosition, wxSize (100, 90), 0, NULL, 0));
        if (list_ != nullptr)
	    {   if (def != nullptr) list_ -> Append (def);
	        box_ext_ -> Add (list_, 2, wxALL, 5); }
	            box -> Add (box_ext_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }
	return ! invalid (); }

::std::string listedit_manager :: tiswot () const
{	PRESUME ((! has_file_) || (filename_ != nullptr), __FILE__, __LINE__);
 	PRESUME ((! has_text_) || (text_ != nullptr), __FILE__, __LINE__);
 	::std::string f, s, r;
	if (has_text_)
	{	s = ::std::string (text_ -> GetValue ().c_str ());
		if (! has_file_) r = s; }
	if (has_file_)
	{	f = ::std::string (filename_ -> GetFileName ().GetFullPath ().c_str ());
		if (! f.empty ()) 
			if (s.empty ()) r = f;
			else r = f + "," + s; }
	return r; }

void listedit_manager :: OnAdd (wxCommandEvent& )
{	const ::std::string s (tiswot ());
	if (! s.empty ())
	{   int n = list_ -> FindString (s.c_str (), true);
		if (n == wxNOT_FOUND)
		{	list_ -> Append (s.c_str ());
			n = list_ -> FindString (s.c_str (), true);
			list_ -> SetSelection (n);
			list_ -> EnsureVisible (n);
			fex (); } } }

void listedit_manager :: OnErase (wxCommandEvent& )
{	VERIFY_NOT_NULL (list_, __FILE__, __LINE__);
	const int l = list_ -> GetSelection ();
	if (l != wxNOT_FOUND)
	{	::std::string s (list_ -> GetString (l));
		list_ -> Delete (l);
		text_ -> SetValue (s.c_str ());
		fex (); } }

void listedit_manager :: OnRename (wxCommandEvent& )
{	const ::std::string s (tiswot ());
	if (! s.empty ())
	{   int n = list_ -> FindString (s.c_str (), true);
		if (n == wxNOT_FOUND)
		{	const int l = list_ -> GetSelection ();
			if (l != wxNOT_FOUND)
			{	list_ -> Delete (l);
				list_ -> Append (s.c_str ());
				n = list_ -> FindString (s.c_str (), true);
				list_ -> SetSelection (n);
				list_ -> EnsureVisible (n);
				fex (); } } } }

void listedit_manager :: OnTap (wxCommandEvent& e)
{	VERIFY_NOT_NULL (list_, __FILE__, __LINE__);
	const int l = list_ -> GetSelection ();
	if (l == wxNOT_FOUND) erase_ -> Disable ();
	else erase_ -> Enable ();
	OnText (e); }

void listedit_manager :: fex ()
{	PRESUME ((! has_file_) || (filename_ != nullptr), __FILE__, __LINE__);
 	PRESUME ((! has_text_) || (text_ != nullptr), __FILE__, __LINE__);
	VERIFY_NOT_NULL (list_, __FILE__, __LINE__);
	const int l = list_ -> GetSelection ();
	if (l == wxNOT_FOUND) erase_ -> Disable ();
	else erase_ -> Enable ();
 	const ::std::string r (tiswot ());
	if (r.empty ())
	{	add_ -> Disable ();
		rename_ -> Disable (); }
	else
	{	const int n = list_ -> FindString (r.c_str (), true);
		if (n == wxNOT_FOUND) add_ -> Enable ();
		else add_ -> Disable ();
		if ((l != wxNOT_FOUND) && ((l != n) || (n == wxNOT_FOUND))) rename_ -> Enable ();
		else rename_ -> Disable (); } }

bool listedit_manager :: invalid () const noexcept
{   if (has_file_ && (filename_ == nullptr)) return true;
    if (has_text_ && (text_ == nullptr)) return true;
    return (rename_ == nullptr) || (list_ == nullptr) || (stat_ext_ == nullptr); }

void listedit_manager :: OnText (wxCommandEvent& )
{	fex (); }

void listedit_manager :: OnFile (wxFileDirPickerEvent& )
{	fex (); }

void listedit_manager :: OnImpatience (wxCommandEvent& )
{	fex (); }

void listedit_manager :: enable (const bool e)
{	if (invalid ()) return;
	add_ -> Enable (e);	
	erase_ -> Enable (e);	
	list_ -> Enable (e);	
	rename_ -> Enable (e);
	stat_ext_ -> Enable (e);
	if (has_file_) filename_ -> Enable (e);	
	if (has_text_) text_ -> Enable (e);	
	if (e) fex (); }

void listedit_manager :: preload (const vstr_t& vs)
{	VERIFY_NOT_NULL (list_, __FILE__, __LINE__);
 	list_ -> Clear ();
	for (auto s : vs)
		list_ -> Append (s.c_str ());
	fex (); }

vstr_t listedit_manager :: acquire () const
{	VERIFY_NOT_NULL (list_, __FILE__, __LINE__);
 	vstr_t res;
	const unsigned int nx = list_ -> GetCount ();
	for (unsigned int i = 0; i < nx; ++i)
		res.push_back (::std::string (list_ -> GetString (i).c_str ()));
	return res; }

#endif // WX
