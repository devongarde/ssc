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
#include "gui/gui-html.h"

#define HTML_STYLE   DEF_STYLE
#define HTML_X       100
#define HTML_Y       100
#define HTML_WIDTH   600
#define HTML_HEIGHT  350

BEGIN_EVENT_TABLE (html_t, dialogue_t)
  EVT_BUTTON (wxID_HELP, html_t::OnHelpClick)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (html_t, dialogue_t)

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
	html_jul24 };
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
	: dialogue_t (wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT)), hv_ (selection_count - 1)
{	Create (mummy, id, caption); } 

bool html_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! dialogue_t :: Create (mummy, id, caption, wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT), HTML_STYLE)) return false;
	CreateControls ();
	return true; }

void html_t :: CreateControls ()
{	if (dialogue_t :: invalid ()) return;

	version_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (version_grid_ != nullptr)
    {	version_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "default &version:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (version_text_ != nullptr)
		{	version_text_ -> Wrap (-1);
			version_ = GSL_OWNER (wxChoice) (new wxChoice (this, choice_version, wxDefaultPosition, wxDefaultSize));
			if (version_ != nullptr)
			{	for (int n = 0; n < selection_count; ++n)
					version_ -> Append (GSL_AT (selection_version, n).nice_name ());
				version_ -> SetSelection (selection_count-1);
				version_grid_ -> Add (version_text_, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTRE_VERTICAL, 5);
				version_grid_ -> Add (version_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (version_grid_, 1, wxEXPAND, 5); }
	
	lingo_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (lingo_grid_ != nullptr)
    {	lingo_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "default &language:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (lingo_text_ != nullptr) lingo_text_ -> Wrap (-1);
		lingo_ = GSL_OWNER (wxComboBox) (new wxComboBox (this, wxID_ANY, lang_, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN | wxCB_SORT));
		if (lingo_ != nullptr)
		{	for (int n = 0; GSL_AT (selection_lang, n) != nullptr; ++n)
		        lingo_ -> Append (GSL_AT (selection_lang, n));
			lingo_grid_ -> Add (lingo_text_, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTRE_VERTICAL, 5);
			lingo_grid_ -> Add (lingo_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5); }
		box_ -> Add (lingo_grid_, 1, wxEXPAND, 5); }

	title_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (title_grid_ != nullptr)
    {	title_text_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, "warn if <TITLE> &text longer than (characters):", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (title_text_ != nullptr)
		{	title_text_ -> Wrap (-1);
			title_ = GSL_OWNER (wxSpinCtrl) (new wxSpinCtrl (this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, max_, 20));
			if (title_ != nullptr)
			{	if (app -> frame () -> rational ()) title_ -> SetIncrement (-1); // down means down
                title_grid_ -> Add (title_text_, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTRE_VERTICAL, 5);
				title_grid_ -> Add (title_, 0, wxALL | wxALIGN_CENTRE_VERTICAL, 5); } }
		box_ -> Add (title_grid_, 1, wxEXPAND, 5); }

	czech_grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
	if (czech_grid_ != nullptr)
	{	sloven_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("warn of inefficient or slo&venly HTML"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (sloven_ != nullptr) czech_grid_ -> Add (sloven_, 0, wxALL | wxALIGN_RIGHT, 5);
		ssi_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("&process Server Side Includes"), wxDefaultPosition, wxDefaultSize, 0));
		if (ssi_ != nullptr) czech_grid_ -> Add (ssi_, 0, wxALL, 5);
		ie_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("ignore Internet E&xplorer bizzaritudes"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (ie_ != nullptr) czech_grid_ -> Add (ie_, 0, wxALL | wxALIGN_RIGHT, 5);
		safari_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("ignore Sa&fari bizzaritudes"), wxDefaultPosition, wxDefaultSize, 0));
		if (safari_ != nullptr) czech_grid_ -> Add (safari_, 0, wxALL, 5);
		rfc1867_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("HTML 2.0: INPUT=FILE (RFC 1867)"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (rfc1867_ != nullptr) czech_grid_ -> Add (rfc1867_, 0, wxALL | wxALIGN_RIGHT, 5);
		rfc1942_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("HTML 2.0: tables (RFC 1942)"), wxDefaultPosition, wxDefaultSize, 0));
		if (rfc1942_ != nullptr) czech_grid_ -> Add (rfc1942_, 0, wxALL, 5);
		rfc1980_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("HTML 2.0: image maps (RFC 1980)"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
		if (rfc1980_ != nullptr) czech_grid_ -> Add (rfc1980_, 0, wxALL | wxALIGN_RIGHT, 5);
		rfc2070_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (this, wxID_ANY, wxT("HTML 2.0: internationalisation (RFC 2070)"), wxDefaultPosition, wxDefaultSize, 0));
		if (rfc2070_ != nullptr) czech_grid_ -> Add (rfc2070_, 0, wxALL, 5);
		box_ -> Add (czech_grid_, 1, wxEXPAND, 5); }

	const wxString stray [] = { "H&TML Tags", "HT&ML 1.0", "&default HTML version" };
	constexpr int count = sizeof (stray) / sizeof (wxString);
	doctype_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (this, wxID_ANY, "if no <!DOCTYPE...>, presume", wxDefaultPosition, wxDefaultSize, count, stray, 1, wxRA_SPECIFY_ROWS));
	if (doctype_ != nullptr)
	{	doctype_ -> SetSelection (1);
		box_ -> Add (doctype_, 1, wxALIGN_CENTRE_HORIZONTAL, 5); }

	dialogue_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void html_t :: OnHelpClick (wxCommandEvent& )
{	app -> help ("HTML"); }

bool html_t :: TransferDataToWindow ()
{	if (invalid ()) return false;	
	if (doctype_ != nullptr)
		switch (dt_)
		{	case 0 :
			case 2 : doctype_ -> SetSelection (dt_); break;
			default : doctype_ -> SetSelection (1); break; }
	if (title_ != nullptr) title_ -> SetValue (max_);
	if (ssi_ != nullptr) ssi_ -> SetValue (bssi_);
	if (sloven_ != nullptr) sloven_ -> SetValue (bsloven_);
	if (ie_ != nullptr) ie_ -> SetValue (bie_);
	if (safari_ != nullptr) safari_ -> SetValue (bsafari_);
	if (rfc1867_ != nullptr) rfc1867_ -> SetValue (b1867_);
	if (rfc1942_ != nullptr) rfc1942_ -> SetValue (b1942_);
	if (rfc1980_ != nullptr) rfc1980_ -> SetValue (b1980_);
	if (rfc2070_ != nullptr) rfc2070_ -> SetValue (b2070_);
    if (lingo_ != nullptr)
    {   if (lang_.empty ()) lang_ = "en";
        if (lingo_ -> FindString (lang_.c_str ()) == wxNOT_FOUND)
            lingo_ -> Append (lang_.c_str ());
        lingo_ -> SetValue (lang_.c_str ()); }
	if (version_ != nullptr)
	{	if (hv_ >= selection_count) version_ -> SetSelection (selection_count - 1);
		else version_ -> SetSelection (hv_); }
	return true; }

bool html_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
	if (doctype_ != nullptr)
	{	dt_ = GSL_NARROW_CAST < unsigned short > (doctype_ -> GetSelection ());
		if (dt_ > 2) dt_ = 1; }
	if (title_ != nullptr) max_ = title_ -> GetValue ();
	if (ssi_ != nullptr) bssi_ = ssi_ -> GetValue ();
	if (sloven_ != nullptr) bsloven_ = sloven_ -> GetValue ();
	if (ie_ != nullptr) bie_ = ie_ -> GetValue ();
	if (safari_ != nullptr) bsafari_ = safari_ -> GetValue ();
	if (rfc1867_ != nullptr) b1867_ = rfc1867_ -> GetValue ();
	if (rfc1942_ != nullptr) b1942_ = rfc1942_ -> GetValue ();
	if (rfc1980_ != nullptr) b1980_ = rfc1980_ -> GetValue ();
	if (rfc2070_ != nullptr) b2070_ = rfc2070_ -> GetValue ();
	if (version_ != nullptr) hv_ = GSL_NARROW_CAST < unsigned short > (version_ -> GetSelection ());
    if (lingo_ != nullptr) lang_ = lingo_ -> GetValue ();
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

#endif // WX
