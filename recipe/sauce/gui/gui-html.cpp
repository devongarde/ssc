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
#include "gui/gui-html.h"

#define HTML_STYLE   DEF_STYLE
#define HTML_X       100
#define HTML_Y       100
#define HTML_WIDTH   600
#define HTML_HEIGHT  350

BEGIN_EVENT_TABLE (html_t, d1_t)
  EVT_BUTTON (wxID_HELP, html_t::OnHelpClick)
  EVT_CHOICE (choice_html_version, html_t::OnVersion)
  EVT_CHOICE (check_wx, html_t::OnWX)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (html_t, d1_t)

// edit this, edit enable () below
html_version selection_version [] = 
{	html_tags,
	html_1,
	html_plus,
	html_2,
	html_2_level_1,
	html_2_level_2,
	html_3_0,
	html_3_2,
	html_4_0,
	html_4_1,
	xhtml_1_0,
	xhtml_1_1,
	xhtml_2,
	html_5_0,
	html_5_1,
	html_5_2,
	html_5_3,
	html_jan05,
	html_jul05,
	html_jan06,
	html_jan07,
	html_jul07,
	html_jan08,
	html_jul08,
	html_jan09,
	html_jul09,
	html_jan10,
	html_jul10,
	html_jan11,
	html_jul11,
	html_jan12,
	html_jul12,
	html_jan13,
	html_may13,
	html_jul13,
	html_jan14,
	html_jan15,
	html_jun15,
	html_jan16,
	html_jul16,
	html_jan17,
	html_jul17,
	html_jan18,
	html_jul18,
	html_oct18,
	html_jan19,
	html_jul19,
	html_jan20,
	html_jul20,
	html_jan21,
	html_feb21,
	html_apr21,
	html_jul21,
	html_oct21,
	html_nov21,
	html_jan22,
	html_apr22,
	html_jul22,
	html_oct22,
	html_jan23,
	html_apr23,
	html_jul23,
	html_oct23,
	html_jan24,
	html_apr24,
	html_jul24,
    html_oct24 };
static constexpr int selection_count = sizeof (selection_version) / sizeof (html_version);

// https://stackoverflow.com/questions/3191664/list-of-all-locales-and-their-short-codes#3191729
const char* selection_lang [] = {
    "aa", "aa-DJ", "aa-ER", "aa-ET",
    "af", "af-ZA",
    "am", "am-ET",
    "an", "an-ES",
    "ar", "ar-AE", "ar-BH", "ar-DZ", "ar-EG", "ar-IN", "ar-IQ", "ar-JO", "ar-KW", "ar-LB", "ar-LY", "ar-MA", "ar-OM", "ar-QA", "ar-SA",
          "ar-SD", "ar-SY", "ar-TN", "ar-YE",
    "as", "as-IN",
    "ast", "ast-ES",
    "az", "az-AZ",
    "be", "be-BY",
    "bem", "bem-ZM",
    "ber", "ber-DZ", "ber-MA",
    "bg", "bg-BG",
    "bho", "bho-IN",
    "bn", "bn-BD", "bn-IN",
    "bo", "bo-CN", "bo-IN",
    "br", "br-FR",
    "brx", "brx-IN",
    "bs", "bs-BA",
    "byn", "byn-ER",
    "ca", "ca-AD", "ca-ES", "ca-FR", "ca-IT",
    "crh", "crh-UA",
    "cs", "cs-CZ",
    "csb", "csb-PL",
    "cv", "cv-RU",
    "cy", "cy-GB",
    "da", "da-DK",
    "de", "de-AT", "de-BE", "de-CH", "de-DE", "de-LU",
    "dv", "dv-MV",
    "dz", "dz-BT",
    "el", "el-CY", "el-GR",
    "en", "en-AG", "en-AU", "en-BW", "en-CA", "en-DK", "en-GB", "en-HK", "en-IE", "en-IN", "en-NG", "en-NZ", "en-PH", "en-SG", "en-US",
          "en-ZA", "en-ZM", "en-ZW",
    "es", "es-AR", "es-BO", "es-CL", "es-CO", "es-CR", "es-CU", "es-DO", "es-EC", "es-ES", "es-GT", "es-HN", "es-MX", "es-NI", "es-PA",
          "es-PE", "es-PR", "es-PY", "es-SV", "es-US", "es-UY", "es-VE",
    "et", "et-EE",
    "eu", "eu-ES",
    "fa", "fa-IR",
    "ff", "ff-SN",
    "fi", "fi-FI",
    "fil", "fil-PH",
    "fo", "fo-FO",
    "fr", "fr-BE", "fr-CA", "fr-CH", "fr-FR", "fr-LU",
    "fur", "fur-IT",
    "fy", "fy-DE", "fy-NL",
    "ga", "ga-IE",
    "gd", "gd-GB",
    "gez", "gez-ER", "gez-ET",
    "gl", "gl-ES",
    "gu", "gu-IN",
    "gv", "gv-GB",
    "ha", "ha-NG",
    "he", "he-IL",
    "hi", "hi-IN",
    "hne", "hne-IN",
    "hr", "hr-HR",
    "hsb", "hsb-DE",
    "ht", "ht-HT",
    "hu", "hu-HU",
    "hy", "hy-AM",
    "id", "id-ID",
    "ig", "ig-NG",
    "ik", "ik-CA",
    "is", "is-IS",
    "it", "it-CH", "it-IT",
    "iu", "iu-CA",
    "iw", "iw-IL",
    "ja", "ja-JP",
    "ka", "ka-GE",
    "kk", "kk-KZ",
    "kl", "kl-GL",
    "km", "km-KH",
    "kn", "kn-IN",
    "ko", "ko-KR",
    "kok", "kok-IN",
    "ks", "ks-IN",
    "ku", "ku-TR",
    "kw", "kw-GB",
    "ky", "ky-KG",
    "lb", "lb-LU",
    "lg", "lg-UG",
    "li", "li-BE", "li-NL",
    "lij", "lij-IT",
    "lo", "lo-LA",
    "lt", "lt-LT",
    "lv", "lv-LV",
    "mag", "mag-IN",
    "mai", "mai-IN",
    "mg", "mg-MG",
    "mhr", "mhr-RU",
    "mi", "mi-NZ",
    "mk", "mk-MK",
    "ml", "ml-IN",
    "mn", "mn-MN",
    "mr", "mr-IN",
    "ms", "ms-MY",
    "mt", "mt-MT",
    "my", "my-MM",
    "nan", "nan-TW",
    "nb", "nb-NO",
    "nds", "nds-DE", "nds-NL",
    "ne", "ne-NP",
    "nl", "nl-AW", "nl-BE", "nl-NL",
    "nn", "nn-NO",
    "nr", "nr-ZA",
    "nso", "nso-ZA",
    "oc", "oc-FR",
    "om", "om-ET", "om-KE",
    "or", "or-IN",
    "os", "os-RU",
    "pa", "pa-IN", "pa-PK",
    "pap", "pap-AN",
    "pl", "pl-PL",
    "ps", "ps-AF",
    "pt", "pt-BR", "pt-PT",
    "ro", "ro-RO",
    "ru", "ru-RU", "ru-UA",
    "rw", "rw-RW",
    "sa", "sa-IN",
    "sc", "sc-IT",
    "sd", "sd-IN",
    "se", "se-NO",
    "shs", "shs-CA",
    "si", "si-LK",
    "sid", "sid-ET",
    "sk", "sk-SK",
    "sl", "sl-SI",
    "so", "so-DJ", "so-ET", "so-KE", "so-SO",
    "sq", "sq-AL", "sq-MK",
    "sr", "sr-ME", "sr-RS",
    "ss", "ss-ZA",
    "st", "st-ZA",
    "sv", "sv-FI", "sv-SE",
    "sw", "sw-KE", "sw-TZ",
    "ta", "ta-IN", "ta-LK",
    "te", "te-IN",
    "tg", "tg-TJ",
    "th", "th-TH",
    "ti", "ti-ER", "ti-ET",
    "tig", "tig-ER",
    "tk", "tk-TM",
    "tl", "tl-PH",
    "tn", "tn-ZA",
    "tr", "tr-CY", "tr-TR",
    "ts", "ts-ZA",
    "tt", "tt-RU",
    "ug", "ug-CN",
    "uk", "uk-UA",
    "unm", "unm-US",
    "ur", "ur-IN", "ur-PK",
    "uz", "uz-UZ",
    "ve", "ve-ZA",
    "vi", "vi-VN",
    "wa", "wa-BE",
    "wae", "wae-CH",
    "wal", "wal-ET",
    "wo", "wo-SN",
    "xh", "xh-ZA",
    "yi", "yi-US",
    "yo", "yo-NG",
    "yue", "yue-HK",
    "zh", "zh-CN", "zh-HK", "zh-SG", "zh-TW",
    "zu", "zu-ZA",
    nullptr };

html_t :: html_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT)), hv_ (selection_count - 1)
{	Create (mummy, id, caption); } 

bool html_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT), HTML_STYLE)) return false;
	CreateControls ();
	return true; }

void html_t :: create_controls (wxWindow *parent)
{	bool rational = true;
	if (parent == this) rational = app -> frame () -> rational ();

	box_version_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_version_ != nullptr)
    {	version_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "&X/HTML version: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (version_text_ != nullptr)
		{	version_text_ -> Wrap (-1);
			version_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_html_version, wxDefaultPosition, wxDefaultSize));
			if (version_ != nullptr)
			{	for (int n = 0; n < selection_count; ++n)
					version_ -> Append (GSL_AT (selection_version, n).nice_name ());
				version_ -> SetSelection (selection_count-1);
				box_version_ -> Add (version_text_, 0, wxALIGN_CENTRE_VERTICAL, 5);
				box_version_ -> Add (version_, 0, wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (box_version_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	box_math_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_math_ != nullptr)
    {	math_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "&MathML version: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (math_text_ != nullptr)
		{	math_text_ -> Wrap (-1);
			wxArrayString stray;
			stray.Add ("none (derive from X/HTML)");
			stray.Add ("MathML 1");
			stray.Add ("MathML 2");
			stray.Add ("MathML 3");
			stray.Add ("MathML 4 (2020 draft)");
			stray.Add ("MathML 4 (2022 draft)");
			stray.Add ("MathML 4 core");
			math_choice_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_html_version, wxDefaultPosition, wxDefaultSize, stray));
			if (math_choice_ != nullptr)
			{	math_choice_ -> SetSelection (6);
				box_math_ -> Add (math_text_, 0, wxALIGN_CENTRE_VERTICAL, 5);
				box_math_ -> Add (math_choice_, 0, wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (box_math_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	box_svg_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_svg_ != nullptr)
    {	svg_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "S&VG version: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (svg_text_ != nullptr)
		{	svg_text_ -> Wrap (-1);
			wxArrayString stray;
			stray.Add ("none (derive from HTML version)");
			stray.Add ("SVG 1.0");
			stray.Add ("SVG 1.1");
			stray.Add ("SVG 1.2 Tiny");
			stray.Add ("SVG 1.2 Full (May 2004 draft)");
			stray.Add ("SVG 2.0");
			stray.Add ("SVG 2.1 (April 2021 draft)");
			svg_choice_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_html_version, wxDefaultPosition, wxDefaultSize, stray));
			if (svg_choice_ != nullptr)
			{	svg_choice_ -> SetSelection (6);
				box_svg_ -> Add (svg_text_, 0, wxALIGN_CENTRE_VERTICAL, 5);
				box_svg_ -> Add (svg_choice_, 0, wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (box_svg_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }
	
	version_line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (version_line_ != nullptr)
		box_ -> Add (version_line_, 0, wxEXPAND | wxALL, 5);

	const wxString stray [] = { "H&TML Tags", "HT&ML 1.0", "&default" };
	constexpr int count = sizeof (stray) / sizeof (wxString);
	doctype_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (parent, wxID_ANY, "if no <!DOCTYPE...>, presume", wxDefaultPosition, wxDefaultSize, count, stray, 1, wxRA_SPECIFY_ROWS));
	if (doctype_ != nullptr)
	{	doctype_ -> SetSelection (1);
		box_ -> Add (doctype_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	title_line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (title_line_ != nullptr)
		box_ -> Add (title_line_, 0, wxEXPAND | wxALL, 5);

	box_lingo_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_lingo_ != nullptr)
    {	lingo_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "default &language: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (lingo_text_ != nullptr) lingo_text_ -> Wrap (-1);
		lingo_ = GSL_OWNER (wxComboBox) (new wxComboBox (parent, wxID_ANY, lang_, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN | wxCB_SORT));
		if (lingo_ != nullptr)
		{	for (int n = 0; GSL_AT (selection_lang, n) != nullptr; ++n)
		        lingo_ -> Append (GSL_AT (selection_lang, n));
			box_lingo_ -> Add (lingo_text_, 0, wxALIGN_CENTRE_VERTICAL, 5);
			box_lingo_ -> Add (lingo_, 0, wxALIGN_CENTRE_VERTICAL, 5); }
		box_ -> Add (box_lingo_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	box_title_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_title_ != nullptr)
    {	title_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "<TITLE> less than (chars.):", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (title_text_ != nullptr)
		{	title_text_ -> Wrap (-1);
			title_ = GSL_OWNER (wxSpinCtrl) (new wxSpinCtrl (parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, max_, 20));
			if (title_ != nullptr)
			{	if (rational) title_ -> SetIncrement (-1); // down means down
                box_title_ -> Add (title_text_, 0, wxALIGN_CENTRE_VERTICAL, 5);
				box_title_ -> Add (title_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (box_title_, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }

	option_line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (option_line_ != nullptr)
		box_ -> Add (option_line_, 0, wxEXPAND | wxALL, 5);

	czech_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
    const long rg = (wxALL | wxALIGN_RIGHT);
    const long al = wxALIGN_RIGHT;
	if (czech_grid_ != nullptr)
	{	sloven_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("warn of inefficient HTML"), wxDefaultPosition, wxDefaultSize, al));
		if (sloven_ != nullptr) czech_grid_ -> Add (sloven_, 5, rg, 5);
		wx_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_wx, wxT("wxWidgets compatibility"), wxDefaultPosition, wxDefaultSize, 0));
		if (wx_ != nullptr) czech_grid_ -> Add (wx_, 0, wxALL, 5);
		ie_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("ignore IE oddities"), wxDefaultPosition, wxDefaultSize, al));
		if (ie_ != nullptr) czech_grid_ -> Add (ie_, 5, rg, 5);
		safari_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("ignore Sa&fari oddities"), wxDefaultPosition, wxDefaultSize, 0));
		if (safari_ != nullptr) czech_grid_ -> Add (safari_, 5, wxALL, 5);
		rfc1867_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("INPUT=FILE (RFC 1867)"), wxDefaultPosition, wxDefaultSize, al));
		if (rfc1867_ != nullptr) czech_grid_ -> Add (rfc1867_, 5, rg, 5);
		rfc1942_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("tables (RFC 1942)"), wxDefaultPosition, wxDefaultSize, 0));
		if (rfc1942_ != nullptr) czech_grid_ -> Add (rfc1942_, 5, wxALL, 5);
		rfc1980_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("image maps (RFC 1980)"), wxDefaultPosition, wxDefaultSize, al));
		if (rfc1980_ != nullptr) czech_grid_ -> Add (rfc1980_, 5, rg, 5);
		rfc2070_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, wxT("international (RFC 2070)"), wxDefaultPosition, wxDefaultSize, 0));
		if (rfc2070_ != nullptr) czech_grid_ -> Add (rfc2070_, 5, wxALL, 5);
		box_ -> Add (czech_grid_, 0, wxEXPAND, 5); }

	base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (base_ != nullptr)
		box_ -> Add (base_, 0, wxEXPAND | wxALL, 5); }


void html_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void html_t :: OnHelpClick (wxCommandEvent& )
{	app -> help ("HTML"); }

void html_t :: enable ()
{	bool h2 = false;
	bool ms = true;
	const bool nowx = ! wx_ -> IsChecked ();
	switch (version_ -> GetSelection ())
	{	case 0 :
		case 1 :
		case 6 :
		case 7 :
			ms = false;
			break;
		case 3 : //html_2
		case 4 : //html_2_level_1
		case 5 : //html_2_level_2
			h2 = true;
			ms = nowx;
			break;
		default :
			ms = nowx;
			h2 = false;
			break; }
	rfc1867_ -> Enable (h2);
	rfc1942_ -> Enable (h2);
	rfc1980_ -> Enable (h2);
	rfc2070_ -> Enable (h2);
	math_text_ -> Enable (ms);	
	math_choice_ -> Enable (ms);	
	svg_text_ -> Enable (ms);	
	svg_choice_ -> Enable (ms);	}

void html_t :: enable_wx (const bool b)
{	math_text_ -> Enable (b);	
	math_choice_ -> Enable (b);	
	svg_text_ -> Enable (b);	
	svg_choice_ -> Enable (b);	}

void html_t :: OnWX (wxCommandEvent& )
{	if (invalid ()) return;
	PRESUME (wx_ != nullptr, __FILE__, __LINE__);
	if (wx_ -> IsChecked ()) enable_wx (false);
	else switch (version_ -> GetSelection ())
	{	case 0 :
		case 1 :
		case 6 :
		case 7 :
			enable_wx (false);
			break;
		default :
			enable_wx (true);
			break; } }

void html_t :: OnVersion (wxCommandEvent& )
{	if (invalid ()) return;
	enable (); }

bool html_t :: TransferDataToWindow ()
{	if (invalid ()) return false;	
	if (doctype_ != nullptr)
		switch (dt_)
		{	case 0 :
			case 2 : doctype_ -> SetSelection (dt_); break;
			default : doctype_ -> SetSelection (1); break; }
	if (title_ != nullptr) title_ -> SetValue (max_);
	if (sloven_ != nullptr) sloven_ -> SetValue (bsloven_);
	if (ie_ != nullptr) ie_ -> SetValue (bie_);
	if (safari_ != nullptr) safari_ -> SetValue (bsafari_);
	if (rfc1867_ != nullptr) rfc1867_ -> SetValue (b1867_);
	if (rfc1942_ != nullptr) rfc1942_ -> SetValue (b1942_);
	if (rfc1980_ != nullptr) rfc1980_ -> SetValue (b1980_);
	if (rfc2070_ != nullptr) rfc2070_ -> SetValue (b2070_);
	if (wx_ != nullptr) wx_ -> SetValue (bwx_);
    if (lingo_ != nullptr)
    {   if (lang_.empty ()) lang_ = "en";
        if (lingo_ -> FindString (lang_.c_str ()) == wxNOT_FOUND)
            lingo_ -> Append (lang_.c_str ());
        lingo_ -> SetValue (lang_.c_str ()); }
	if (version_ != nullptr)
	{	if (hv_ >= selection_count) version_ -> SetSelection (selection_count - 1);
		else version_ -> SetSelection (hv_); }
	math_choice_ -> SetSelection (static_cast < int > (math_));
	svg_choice_ -> SetSelection (static_cast < int > (svg_));
	enable ();
	return true; }

bool html_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	if (doctype_ != nullptr)
	{	dt_ = GSL_NARROW_CAST < unsigned short > (doctype_ -> GetSelection ());
		if (dt_ > 2) dt_ = 1; }
	if (title_ != nullptr) max_ = title_ -> GetValue ();
	if (sloven_ != nullptr) bsloven_ = sloven_ -> GetValue ();
	if (ie_ != nullptr) bie_ = ie_ -> GetValue ();
	if (safari_ != nullptr) bsafari_ = safari_ -> GetValue ();
	if (rfc1867_ != nullptr) b1867_ = rfc1867_ -> GetValue ();
	if (rfc1942_ != nullptr) b1942_ = rfc1942_ -> GetValue ();
	if (rfc1980_ != nullptr) b1980_ = rfc1980_ -> GetValue ();
	if (rfc2070_ != nullptr) b2070_ = rfc2070_ -> GetValue ();
	if (wx_ != nullptr) bwx_ = wx_ -> GetValue ();
	if (version_ != nullptr) hv_ = GSL_NARROW_CAST < unsigned short > (version_ -> GetSelection ());
    if (lingo_ != nullptr) lang_ = lingo_ -> GetValue ();
	const int m = math_choice_ -> GetSelection ();
	PRESUME (m <= math_core, __FILE__, __LINE__);
	math_ = static_cast < e_math_version > (m);
	const int s = svg_choice_ -> GetSelection ();
	PRESUME (s <= sv_2_1, __FILE__, __LINE__);
	svg_ = static_cast < e_svg_version > (s);
	return true; }

html_version html_t :: ver () const
{	if (hv_ >= selection_count) return html_current;
	return GSL_AT (selection_version, hv_); }

void html_t :: ver (const html_version& v)
{	for (int n = 0; n < selection_count; ++n)
		if (GSL_AT (selection_version, n) == v)
		{	hv_ = GSL_NARROW_CAST < unsigned short > (n);
			return; }
	hv_ = selection_count - 1; }

bool html_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
	create_box (mummy, pos, size);
	if (! create_panel_itself (mummy, id, pos, size, style)) return false;
	create_controls (panel_);
	if (invalid_panel ()) return false;
	panel_ -> SetSizer (box_);
	panel_ -> Layout ();
	box_ -> Fit (panel_);
	return true; }

void html_t :: load_from_context (const context_t& c)
{   ie (c.ie ());
    rfc1867 (c.rfc_1867 ());
    rfc1942 (c.rfc_1942 ());
    rfc1980 (c.rfc_1980 ());
    rfc2070 (c.rfc_2070 ());
    safari (c.safari ());
    sloven (c.sloven ());
    title (GSL_NARROW_CAST < unsigned int > (c.title ()));
    ver (c.html_ver ());
    if (c.force_version ()) doctype (2);
    else if (c.presume_tags ()) doctype (0);
    else doctype (1);
    lingo (c.lang ()); 
    wx (c.wx ()); 
	math_version (c.math_version ()); 
	svg_version (c.svg_version ()); }

void html_t :: save_to_context (context_t& c) const
{   c.ie (ie ());
    c.rfc_1867 (rfc1867 ());
    c.rfc_1942 (rfc1942 ());
    c.rfc_1980 (rfc1980 ());
    c.rfc_2070 (rfc2070 ());
    c.safari (safari ());
    c.sloven (sloven ());
    c.title (title ());
    c.html_ver (ver ());
    c.lang (lingo ());
    c.wx (wx ());
    switch (doctype ())
    {   case 0 : c.force_version (false); c.presume_tags (true); break;
        case 2 : c.force_version (true); c.presume_tags (false); break;
        default : c.force_version (false); c.presume_tags (false); break; }
 	c.math_version (math_version ());
 	c.svg_version (svg_version ()); }

#endif // WX
