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
#include "gui/gui-whizz.h"

// Introducing Eddie & the Falcons
#define WIZZARD_STYLE   wxDEFAULT_DIALOG_STYLE
#define WIZZARD_X       100
#define WIZZARD_Y       100
#define WIZZARD_WIDTH   300
#define WIZZARD_HEIGHT  225

// it would be quite useful if the standard button IDs for wizards were documented somewhere
// wxID_ANY? That's ridiculous. (https://github.com/wxWidgets/wxWidgets/blob/master/samples/wizard/wizard.cpp)
BEGIN_EVENT_TABLE (whizz_t, whizzo_t)
  EVT_WIZARD_CANCEL (wxID_ANY, whizz_t::OnCancel)
  EVT_WIZARD_FINISHED (wxID_ANY, whizz_t::OnDone)
  EVT_WIZARD_HELP (wxID_ANY, whizz_t::OnHelpClick)
  EVT_WIZARD_PAGE_CHANGED (wxID_ANY, whizz_t::OnChanged)
  EVT_WIZARD_PAGE_CHANGING (wxID_ANY, whizz_t::OnChanging)
END_EVENT_TABLE ()

BEGIN_EVENT_TABLE (whizz_choice, whizz_ffs)
  EVT_RADIOBOX (radio_choice, whizz_choice::OnChoice)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (whizz_t, whizzo_t)

bool whizz_choice :: create_controls (whizz_t* wz, const char* sz)
{	if (whizz_page::create_controls (wz, sz))
	{	const wxString radio_text [] = { "Snippet of HTML", "Website Directory", };
		constexpr int radio_count = sizeof (radio_text) / sizeof (wxString);
		radio_choice_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (this, radio_choice, "What to nitpick", wxDefaultPosition, wxDefaultSize, radio_count, radio_text, 1, wxRA_SPECIFY_COLS));
		if (radio_choice_ != nullptr)
		{	radio_choice_ -> SetSelection (0);
			box_ -> Add (radio_choice_, 0, wxALL, 5);
			finish_create ();
			return true; } }
	return false; }

void whizz_choice :: arrange_page_order (whizz_t& wiz)
{	if (invalid ()) return;
	switch (radio_choice_ ->  GetSelection ())
	{	case 0 : // snippet
			wiz.end_ -> SetPrev (wiz.snippet_);
			SetNext (wiz.snippet_);
			rooted_ = false;
			break;
		case 1 : // dir
			wiz.end_ -> SetPrev (wiz.root_);
			SetNext (wiz.root_); // it would be useful if the wizard got round to noticing this 
			rooted_ = true;
			break;
		default : // WTF
			GRACEFUL_CRASH (__FILE__, __LINE__);
			break; } }

void whizz_choice :: OnChoice (wxCommandEvent& )
{	if (invalid ()) return;
	VERIFY_NOT_NULL (mummy_, __FILE__, __LINE__);
	arrange_page_order (*mummy_); }

bool whizz_root :: create_controls (whizz_t* wz, const char* sz)
{	if (whizz_page::create_controls (wz, sz))
	{	dir_root_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (this, wxID_ANY, wxEmptyString, "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
		if (dir_root_ != nullptr)
		{	box_ -> Add (dir_root_, 0, wxALL, 5);	
			finish_create ();
			return true; } }
	return false; }

bool whizz_snippet :: create_controls (whizz_t* wz, const char* sz)
{	if (whizz_page::create_controls (wz, sz))
	{	text_snippet_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize (360, 240), wxTE_MULTILINE | wxHSCROLL | wxVSCROLL | wxWANTS_CHARS));
		if (text_snippet_ != nullptr)
		{	box_-> Add (text_snippet_, 0, wxALL, 5 );
			finish_create ();
			return true; } }
	return false; }

whizz_t :: whizz_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: whizzo_t (wxPoint (WIZZARD_X, WIZZARD_Y))
{	Create (mummy, id, caption); } 

bool whizz_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	SetExtraStyle (wxWIZARD_EX_HELPBUTTON);
	if (! whizzo_t :: Create (mummy, id, caption, wxPoint (WIZZARD_X, WIZZARD_Y), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)) return false;
	muggle_ = false;
	CreateControls ();
	return true; }

void whizz_t :: CreateControls ()
{	if (muggle_) return;
	SetSizeHints (wxDefaultSize, wxDefaultSize);

	if (pagemaker < whizz_intro > :: create (intro_, *this, "Welcome to the " FULLNAME ", a website nitpicker. It can\nnitpick a website at source, or an HTML snippet. It reports any\nuntidinesses or horriditudes it finds."))
		if (pagemaker < whizz_choice > :: create (choice_, *this, "If you want to nitpick a snippet of HTML, select Snippet of HTML.\nIf you want to nitpick a website at source, select Website Directory."))
			if (pagemaker < whizz_snippet > :: create (snippet_, *this, "Enter an HTML snippet:"))
				if (pagemaker < whizz_root > :: create (root_, *this, "Where is the website root directory?"))
					pagemaker < whizz_end > :: create (end_, *this, "Click on Finish to nitpick...");

	if (invalid ()) return;

	intro_ -> SetNext (choice_);
	choice_ -> SetNext (snippet_);
	snippet_ -> SetNext (end_);
	root_ -> SetNext (end_);
	choice_ -> SetPrev (intro_);
	snippet_ -> SetPrev (choice_);
	root_ -> SetPrev (choice_);
	end_ -> SetPrev (snippet_);
	set_size ();

	GetPageAreaSizer () -> Add (intro_);
	GetPageAreaSizer () -> Add (choice_);
	GetPageAreaSizer () -> Add (snippet_);
	GetPageAreaSizer () -> Add (root_);
	GetPageAreaSizer () -> Add (end_); }

void whizz_t :: OnCancel (wxWizardEvent& )
{ }

void whizz_t :: OnChanged (wxWizardEvent& )
{ }

void whizz_t :: OnChanging (wxWizardEvent& )
{ }

void whizz_t :: OnDone (wxWizardEvent& )
{ }

void whizz_t :: OnHelpClick (wxWizardEvent& )
{	if (app != nullptr) app -> help ("wizzard"); /* rock and roll winter */ }

bool whizz_t :: run ()
{	return RunWizard (intro_); }

wxSize operator || (const wxSize& lhs, const wxSize& rhs)
{	wxSize res;
	res.SetHeight (::std::max (lhs.GetHeight (), rhs.GetHeight ()));
	res.SetWidth (::std::max (lhs.GetWidth (), rhs.GetWidth ()));
	return res; }

void whizz_t :: set_size ()
{	if (invalid ()) return;
	SetPageSize (	intro_ -> GetBestSize () || choice_ -> GetBestSize () || snippet_ -> GetBestSize () ||
					root_ -> GetBestSize () || end_ -> GetBestSize ()); }

bool whizz_t :: TransferDataToWindow ()
{	if (invalid ())  return false;

	return true; }

bool whizz_t :: TransferDataFromWindow ()
{	if (invalid ())  return false;

	return true; }

#endif // WX
