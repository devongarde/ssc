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
#include "enum/type_enum.h"
#include "utility/bitset.h"
#include "css/flags.h"
#include "gui/gui-app.h"
#include "gui/gui-css.h"

#define CSS_STYLE   DEF_STYLE
#define CSS_X       100
#define CSS_Y       100
#define CSS_WIDTH   400
#define CSS_HEIGHT  450

BEGIN_EVENT_TABLE (css_t, d1_t)
  EVT_BUTTON (wxID_HELP, css_t::OnHelpClick)
  EVT_CHOICE (choice_css_version, css_t::OnVersion)
  EVT_DATAVIEW_SELECTION_CHANGED (list_css_module, css_t::OnModule)
  EVT_RADIOBOX (radio_css_level, css_t::OnLevel)
  EVT_BUTTON (button_css_add, css_t::OnAdd)
  EVT_BUTTON (button_css_erase, css_t::OnErase)
  EVT_BUTTON (button_css_rename, css_t::OnRename)
  EVT_TEXT (text_css_ext, css_t::OnText)
  EVT_LISTBOX (list_css_ext, css_t::OnExtension)
  EVT_LISTBOX_DCLICK (list_css_ext, css_t::OnImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (css_t, d1_t)

#define CBSZ "off", "on", "1", "2", "3", "4", "5", "6"
const char* cbsz [] = { CBSZ };
typedef enum { rb_off, rb_on, rb_1, rb_2, rb_3, rb_4, rb_5, rb_6 } canable_butt;

css_t :: css_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (CSS_X, CSS_Y), wxSize (CSS_WIDTH, CSS_HEIGHT))
{	Create (mummy, id, caption); } 

bool css_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (CSS_X, CSS_Y), wxSize (CSS_WIDTH, CSS_HEIGHT), CSS_STYLE)) return false;
	CreateControls ();
	return true; }

void css_t :: create_controls (wxWindow *parent)
{	box_ver_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_ver_ != nullptr)
    {	box_ver_ -> Add (0, 0, 2, wxEXPAND, 5);
        stat_ver_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "CSS &version: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (stat_ver_ != nullptr)
		{	stat_ver_ -> Wrap (-1);
            box_ver_ -> Add (stat_ver_, 1, wxALIGN_CENTRE_VERTICAL, 5);
			version_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_css_version, wxDefaultPosition, wxSize (100, -1)));
			if (version_ != nullptr)
			{	version_ -> Append ("none");
				for (int n = 1; n <= css_version_max; ++n)
                {   ::std::string nm = type_master < t_css_version > :: base_name (static_cast < e_css_version > (n));
					if (nm == "2") nm = "2.1";
                    else if ((nm.length () > 1) && (nm.at (1) >= '0') && (nm.at (1) <= '9')) nm = ::std::string ("20") + nm;
					version_ -> Append (nm); }
				version_ -> SetSelection (ver_);
				box_ver_ -> Add (version_, 2, wxALIGN_CENTRE_VERTICAL, 5); } }
        box_ver_ -> Add (0, 0, 2, wxEXPAND, 5);
		box_ -> Add (box_ver_, 0, wxALIGN_CENTRE, 5); }

    module_ = GSL_OWNER (wxDataViewListCtrl) (new wxDataViewListCtrl (parent, list_css_module, wxDefaultPosition, wxDefaultSize, wxVSCROLL));
    if (module_ != nullptr)
	{   module_ -> SetMinSize (wxSize (-1, 150));
        col_mod_ = module_ -> AppendTextColumn ("Module", wxDATAVIEW_CELL_INERT, 250, static_cast <wxAlignment> (wxALIGN_RIGHT), wxDATAVIEW_COL_RESIZABLE);
	    col_ver_ = module_ -> AppendTextColumn ("Level", wxDATAVIEW_CELL_INERT, -1, static_cast <wxAlignment> (wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE);
        for (int n = 0; n < c_bad; ++n)
        {   wxVector < wxVariant > val;
			::std::string nim (type_master < t_css_module > :: name (static_cast < e_css_module > (n)));
			if (nim.empty ()) nim = ::boost::lexical_cast < ::std::string > (n) + " (missing description)";
			else
			{	const ::std::string::size_type pos = nim.find (':');
				if ((pos != ::std::string::npos) && (pos < (nim.length () - 1))) nim = nim.substr (pos+1); }
            val.push_back (nim);
            val.push_back (cbsz [0]);
            module_ -> AppendItem (val, n); }
	    box_ -> Add (module_, 0, wxALL | wxEXPAND, 5); }

	const wxString stray [] = { CBSZ };
	constexpr int count = sizeof (stray) / sizeof (wxString);
	caroline_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (parent, radio_css_level, "Module Level", wxDefaultPosition, wxDefaultSize, count, stray, 8, wxRA_SPECIFY_COLS));
    if (caroline_ != nullptr)
	{   caroline_ -> SetSelection (0);
	    box_ -> Add (caroline_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	sl1_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (sl1_ != nullptr)
	    box_ -> Add (sl1_, 0, wxEXPAND | wxALL, 5);

	homme_.construct (parent, box_, "File Extensions:", CSS_EXT);

	sl2_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (sl2_ != nullptr)
		box_ -> Add (sl2_, 0, wxEXPAND | wxALL, 5); }

void css_t :: CreateControls ()
{	PRESUME (invalid (), __FILE__, __LINE__);
	create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH);
	Disenable (); }

bool canable (const e_css_module m, const canable_butt radio)
{	const flags_t f (enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: flags (m));
	if (((f & MOD_UNSUPPORTED) == MOD_UNSUPPORTED) || ((f & MOD_FUTURE) == MOD_FUTURE)) return false;
	switch (radio)
	{	case rb_off : return true;
		case rb_on : return ((f & MOD_ON_OFF) == MOD_ON_OFF);
		case rb_1 : return ((f & MOD_LEVEL_1) == MOD_LEVEL_1);
		case rb_2 : return ((f & MOD_LEVEL_2) == MOD_LEVEL_2);
		case rb_3 : return ((f & MOD_LEVEL_3) == MOD_LEVEL_3);
		case rb_4 : return ((f & MOD_LEVEL_4) == MOD_LEVEL_4);
		case rb_5 : return ((f & MOD_LEVEL_5) == MOD_LEVEL_5);
		case rb_6 : return ((f & MOD_LEVEL_6) == MOD_LEVEL_6);
		default : break; }
	GRACEFUL_CRASH (__FILE__, __LINE__); }

bool can_mvsb (const flags_t f) 
{	if ((f & MOD_UNSUPPORTED) == MOD_UNSUPPORTED) return false;
	if ((f & MOD_FUTURE) == MOD_FUTURE) return false;
	return true; }

canable_butt mvsb (const int l, const flags_t f)
{	if (! can_mvsb (f)) return rb_off;
	switch (l)
	{	case 0 :
			break;
		case 1 :
			if ((f & MOD_ON_OFF) == MOD_ON_OFF)
				return rb_on;
			if ((f & MOD_LEVEL_1) == MOD_LEVEL_1)
				return rb_1;
			break;
		case 2 :
			if ((f & MOD_LEVEL_2) == MOD_LEVEL_2)
				return rb_2;
			break;
		case 3 :
			if ((f & MOD_LEVEL_1) == MOD_LEVEL_1)
				return rb_1;
			if ((f & MOD_LEVEL_3) == MOD_LEVEL_3)
				return rb_3;
			break;
		case 4 :
			if ((f & MOD_LEVEL_2) == MOD_LEVEL_2)
				return rb_2;
			if ((f & MOD_LEVEL_4) == MOD_LEVEL_4)
				return rb_4;
			break;
		case 5 :
			if (((f & MOD_LEVEL_1) == MOD_LEVEL_1) && ((f & MOD_LEVEL_3) == MOD_LEVEL_3))
				return rb_3;
			if ((f & MOD_LEVEL_5) == MOD_LEVEL_5)
				return rb_5;
			break;
		case 6 :
			if ((f & MOD_LEVEL_6) == MOD_LEVEL_6)
				return rb_6;
			break;
		default :
			GRACEFUL_CRASH (__FILE__, __LINE__);
			break; }
	return rb_off; }

::std::string mvs (const e_css_module m, const int l)
{	const flags_t f (enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: flags (m));
	if ((f & MOD_UNSUPPORTED) == MOD_UNSUPPORTED) return "-";
	if ((f & MOD_FUTURE) == MOD_FUTURE) return "future";
	switch (l)
	{	case 0 :
			break;
		case 1 :
			if ((f & MOD_ON_OFF) == MOD_ON_OFF)
				return "on";
			if ((f & MOD_LEVEL_1) == MOD_LEVEL_1)
				return "1";
			break;
		case 2 :
			if ((f & MOD_LEVEL_2) == MOD_LEVEL_2)
				return "2";
			break;
		case 3 :
			if ((f & MOD_LEVEL_1) == MOD_LEVEL_1)
				return "1";
			if ((f & MOD_LEVEL_3) == MOD_LEVEL_3)
				return "3";
			break;
		case 4 :
			if ((f & MOD_LEVEL_2) == MOD_LEVEL_2)
				return "2";
			if ((f & MOD_LEVEL_4) == MOD_LEVEL_4)
				return "4";
			break;
		case 5 :
			if (((f & MOD_LEVEL_1) == MOD_LEVEL_1) && ((f & MOD_LEVEL_3) == MOD_LEVEL_3))
				return "3";
			if ((f & MOD_LEVEL_5) == MOD_LEVEL_5)
				return "5";
			break;
		case 6 :
			if ((f & MOD_LEVEL_6) == MOD_LEVEL_6)
				return "6";
			break;
		default :
			GRACEFUL_CRASH (__FILE__, __LINE__);
			break; }
	return "off"; }

void css_t :: modulo_level ()
{	const e_css_version cv = v_.css_version ();
	switch (cv)
	{	case css_none :
			if (! v_.css_any_3_4_5_6 ())
			{	version_ -> SetSelection (css_none);
				return; }
			break;
		case css_bespoke :
			break;
		default :
			version_ -> SetSelection (cv);
			return; }
	for (int i = css_1; i <= css_version_max; ++i)
	{	html_version tmp;
		tmp.css_version (static_cast < e_css_version > (i));
		if (is_css_identical (v_, tmp))
		{	version_ -> SetSelection (static_cast < e_css_version > (i));	
			return; } }
	version_ -> SetSelection (css_bespoke); }

void css_t :: set_module (const e_css_module m)
{	const int l = v_.css_module (m);
	const ::std::string exptxt = mvs (m, l);
	wxVariant val;
	module_ -> GetValue (val, m, 1);
	const ::std::string silly (val.GetString ().c_str ());
	if (! compare_no_case (exptxt, silly))
	{	val = exptxt.c_str ();
		module_ -> SetValue (val, m, 1); } }

void css_t :: Disenable ()
{   if (invalid ()) return;
    const int l = version_ -> GetSelection ();
	if (l != wxNOT_FOUND)
	{	const e_css_version sel = GSL_NARROW_CAST < e_css_version > (l);
		if (sel != css_bespoke)
		{	v_.css_version (sel);
			for (unsigned int i = 0; i < c_bad; ++i)
				set_module (static_cast < e_css_module > (i)); } } }

void css_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("css"); }

void css_t :: OnVersion (wxCommandEvent& )
{	Disenable (); }

void css_t :: OnModule (wxDataViewEvent& )
{   if (invalid ()) return;
    const int l = module_ -> GetSelectedRow ();
	if (l == wxNOT_FOUND) caroline_ -> Enable (false);
	else
	{	const e_css_module m = GSL_NARROW_CAST < e_css_module > (l);
		const int lev = v_.css_module (m);
		const flags_t f (enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: flags (m));
		for (int i = 0; i <= rb_6; ++i)
		 	caroline_ -> Enable (i, canable (m, static_cast < canable_butt > (i)));
		if (can_mvsb (f))
			caroline_ -> SetSelection (mvsb (lev, f)); } }			

void css_t :: OnLevel (wxCommandEvent& )
{	if (invalid ()) return;
	const int l = module_ -> GetSelectedRow ();
	if (l != wxNOT_FOUND)
	{	const e_css_module m = GSL_NARROW_CAST < e_css_module > (l);
		const int lvl = caroline_ -> GetSelection ();
		switch (lvl)
		{	case rb_off :
				v_.css_module (m, 0);
				break;
			case rb_on :
			case rb_1 :
				v_.css_module (m, 3);
				break;
			case rb_2 :
			case rb_4 :
				v_.css_module (m, 4);
				break;
			case rb_3 :
				{	const flags_t f (enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: flags (m));
					if ((f & MOD_LEVEL_1) == MOD_LEVEL_1) v_.css_module (m, 5);
					else v_.css_module (m, 3); }
				break;	
			case rb_5 :
				v_.css_module (m, 5);
				break;
			case rb_6 :
				v_.css_module (m, 6);
				break;
			default :
				return; }
		set_module (m);
		modulo_level (); } }

void css_t :: OnAdd (wxCommandEvent& e)
{	homme_.OnAdd (e); }

void css_t :: OnErase (wxCommandEvent& e)
{	homme_.OnErase (e); }

void css_t :: OnRename (wxCommandEvent& e)
{	homme_.OnRename (e); }

void css_t :: OnText (wxCommandEvent& e)
{	homme_.OnText (e); }

void css_t :: OnExtension (wxCommandEvent& e)
{	homme_.OnTap (e); }

void css_t :: OnImpatience (wxCommandEvent& e)
{	homme_.OnImpatience (e); }

bool css_t :: TransferDataToWindow ()
{	VERIFY_NOT_NULL (caroline_, __FILE__, __LINE__);
	if (invalid ()) return false;
	v_ = trans_;
	ver_ = v_.css_version ();
	homme_.preload (css_ext_);
	modulo_level ();
	Disenable ();
	caroline_ -> Enable (false);
	return true; }

bool css_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	trans_ = v_;
	css_ext_ = homme_.acquire ();
	return true; }

bool css_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
	create_box (mummy, pos, size);
	if (! create_panel_itself (mummy, id, pos, size, style)) return false;
	create_controls (panel_);
	if (invalid_panel ()) return false;
	panel_ -> SetSizer (box_);
	panel_ -> Layout ();
	box_ -> Fit (panel_);
	return true; }

void css_t :: load_from_context (const context_t& c)
{	ext (c.css_extension ());
    version (c.html_ver ()); }

void css_t :: save_to_context (context_t& c) const
{	c.css_extension (ext ());
    c.html_ver (version ()); }

#endif // WX
