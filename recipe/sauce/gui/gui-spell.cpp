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

// NOTE: need to load hunspell dictionaries into list box. Not built yet because it'll need testing
// and it can't be tested under windows.

#ifdef WX
#ifndef NOSPELL
#include "gui/gui-app.h"
#include "gui/gui-spell.h"
#include "spell/spell.h"

#define SPELL_STYLE   DEF_STYLE
#define SPELL_X       100
#define SPELL_Y       100
#define SPELL_WIDTH   425
#ifdef HUNDO
#define SPELL_HEIGHT  425
#else // HUNDO
#define SPELL_HEIGHT  320
#endif // HUNDO

BEGIN_EVENT_TABLE (spell_t, d1_t)
  EVT_BUTTON (wxID_HELP, spell_t::OnHelpClick)
  EVT_CHECKBOX (check_spell, spell_t::OnCheck)
  EVT_BUTTON (button_dict_add, spell_t::OnDictAdd)
  EVT_BUTTON (button_dict_erase, spell_t::OnDictErase)
  EVT_BUTTON (button_dict_rename, spell_t::OnDictRename)
  EVT_TEXT (text_dict_ext, spell_t::OnDictTap)
  EVT_LISTBOX (list_dict_ext, spell_t::OnDictExtension)
  EVT_LISTBOX_DCLICK (list_dict_ext, spell_t::OnDictImpatience)
  EVT_FILEPICKER_CHANGED (file_dict_name, spell_t::OnDictFileName)
#ifdef HUNDO
  EVT_BUTTON (button_hun_add, spell_t::OnHunAdd)
  EVT_BUTTON (button_hun_erase, spell_t::OnHunErase)
  EVT_FILEPICKER_CHANGED (file_hun_name, spell_t::OnHunFileName)
  EVT_BUTTON (button_hun_rename, spell_t::OnHunRename)
  EVT_TEXT (text_hun_ext, spell_t::OnHunTap)
  EVT_LISTBOX (list_hun_ext, spell_t::OnHunExtension)
  EVT_LISTBOX_DCLICK (list_hun_ext, spell_t::OnHunImpatience)
#endif // HUNDO
  EVT_BUTTON (button_word_add, spell_t::OnWordAdd)
  EVT_BUTTON (button_word_erase, spell_t::OnWordErase)
  EVT_BUTTON (button_word_rename, spell_t::OnWordRename)
  EVT_TEXT (text_word_ext, spell_t::OnWordTap)
  EVT_LISTBOX (list_word_ext, spell_t::OnWordExtension)
  EVT_LISTBOX_DCLICK (list_word_ext, spell_t::OnWordImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (spell_t, d1_t)

spell_t :: spell_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (SPELL_X, SPELL_Y), wxSize (SPELL_WIDTH, SPELL_HEIGHT))
{	Create (mummy, id, caption); } 

bool spell_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SPELL_X, SPELL_Y), wxSize (SPELL_WIDTH, SPELL_HEIGHT), SPELL_STYLE)) return false;
	CreateControls ();
	return true; }

void spell_t :: create_controls (wxWindow *parent)
{	box_check_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_check_ != nullptr)
	{	check_spell_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_spell, "Check spelling", wxDefaultPosition, wxDefaultSize, 0));
		if (check_spell_ != nullptr)
		{	box_check_ -> Add (check_spell_, 0, wxALL, 5);
			check_case_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Check casing", wxDefaultPosition, wxDefaultSize, 0));
			if (check_case_ != nullptr)
			{	box_check_ -> Add (check_case_, 0, wxALL, 5);
#ifndef NOICU
				check_icu_= GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Use ICU", wxDefaultPosition, wxDefaultSize, 0));
				if (check_icu_ != nullptr)
				{	box_check_ -> Add (check_icu_, 0, wxALL, 5);
#endif // NOICU
					box_ -> Add (box_check_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }
#ifndef NOICU
				}
#endif // NOICU

	dict_.construct (parent, box_, "Files of valid words:", "*.dict", true, false, true);
#ifdef HUNDO
	hun_.construct (parent, box_, "HUNSPELL dictionaries & languages:", "*.*", true, true, true);
#endif // HUNDO
	word_.construct (parent, box_, "Extra valid words:", "rumplestiltskin-on-toast", false, false, true);

	base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
	    box_ -> Add (base_, 0, wxEXPAND | wxALL, 5); }

void spell_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH);  }

void spell_t :: enable ()
{	const bool checked = check_spell_ -> IsChecked ();
	check_case_ -> Enable (checked);
#ifndef NOICU
	check_icu_ -> Enable (checked);
#endif // NOICU
	dict_.enable (checked);
#ifdef HUNDO
	hun_.enable (checked);
#endif // HUNDO
	word_.enable (checked); }

void spell_t :: OnCheck (wxCommandEvent& )
{	if (invalid ()) return;
	enable (); }

void spell_t :: OnDictAdd (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnAdd (e); }

void spell_t :: OnDictErase (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnErase (e); }

void spell_t :: OnDictFileName (wxFileDirPickerEvent& e)
{	if (invalid ()) return;
	dict_.OnFile (e); }

void spell_t :: OnDictRename (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnRename (e); }

void spell_t :: OnDictTap (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnTap (e); }

void spell_t :: OnDictExtension (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnText (e); }

void spell_t :: OnDictImpatience (wxCommandEvent& e)
{	if (invalid ()) return;
	dict_.OnImpatience (e); }

void spell_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("spell"); }

#ifdef HUNDO
void spell_t :: OnHunAdd (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnAdd (e); }

void spell_t :: OnHunErase (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnErase (e); }

void spell_t :: OnHunFileName (wxFileDirPickerEvent& e)
{	if (invalid ()) return;
	hun_.OnFile (e); }

void spell_t :: OnHunRename (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnRename (e); }

void spell_t :: OnHunTap (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnTap (e); }

void spell_t :: OnHunExtension (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnText (e); }

void spell_t :: OnHunImpatience (wxCommandEvent& e)
{	if (invalid ()) return;
	hun_.OnImpatience (e); }
#endif // HUNDO

void spell_t :: OnWordAdd (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnAdd (e); }

void spell_t :: OnWordErase (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnErase (e); }

void spell_t :: OnWordRename (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnRename (e); }

void spell_t :: OnWordTap (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnTap (e); }

void spell_t :: OnWordExtension (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnText (e); }

void spell_t :: OnWordImpatience (wxCommandEvent& e)
{	if (invalid ()) return;
	word_.OnImpatience (e); }

bool spell_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	check_case_ -> SetValue (case_);
#ifndef NOICU
	check_icu_ -> SetValue (icu_);
#endif // NOICU
	check_spell_ -> SetValue (check_);
	dict_.preload (dicts_);
#ifdef HUNDO
	hun_.preload (huns_);
#endif // HUNDO
	word_.preload (words_);
	enable ();
	return true; }

bool spell_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	case_ = check_case_ -> IsChecked ();
	check_ = check_spell_ -> IsChecked ();
#ifndef NOICU
	icu_ = check_icu_ -> IsChecked ();
#endif // NOICU
	dicts_ = dict_.acquire ();
#ifdef HUNDO
	huns_ = hun_.acquire ();
#endif // HUNDO
	words_ = word_.acquire ();
	return true; }

bool spell_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
	create_box (mummy, pos, size);
	if (! create_panel_itself (mummy, id, pos, size, style)) return false;
	create_controls (panel_);
	if (invalid_panel ()) return false;
	panel_ -> SetSizer (box_);
	panel_ -> Layout ();
	box_ -> Fit (panel_);
	return true; }

void spell_t :: load_from_context (const context_t& c)
{	
    cased (c.cased ());
    check (c.spell ());
    dict (get_spell_list ());
#ifndef NOICU
    icu (c.icu ());
#endif // NOICU
    word (c.spellings ());
}

void spell_t :: save_to_context (context_t& c) const
{   c.cased (cased ());
#ifndef NOICU
    c.icu (icu ());
#endif // NOICU
    c.spell (check ());
    c.spellings (word ());
    spell_reset ();
    nitpick nits;
    add_spell_list (nits, dict ()); }

#endif // NOSPELL
#endif // WX
