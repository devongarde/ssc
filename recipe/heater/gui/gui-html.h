/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#ifdef WX
#include "gui/gui-dialogue.h"
#include "parser/html_version.h"

#define HTML_CAPTION "HTML"

class html_t : public dialogue_t
{   wxCheckBox* sloven_ = nullptr;
    wxCheckBox* ssi_ = nullptr;
    wxCheckBox* safari_ = nullptr;
    wxCheckBox* ie_ = nullptr;
    wxCheckBox* rfc1867_ = nullptr;
    wxCheckBox* rfc1942_ = nullptr;
    wxCheckBox* rfc1980_ = nullptr;
    wxCheckBox* rfc2070_ = nullptr;
	wxChoice* version_ = nullptr;
	wxComboBox* lingo_ = nullptr;
	wxGridSizer* version_grid_ = nullptr;
    wxGridSizer* lingo_grid_ = nullptr;
    wxGridSizer* title_grid_ = nullptr;
    wxGridSizer* czech_grid_ = nullptr;
    wxRadioBox* doctype_ = nullptr;
	wxSpinCtrl* title_ = nullptr;
    wxStaticText* lingo_text_ = nullptr;
    wxStaticText* title_text_ = nullptr;
    wxStaticText* version_text_ = nullptr;
	bool b1867_ = false, b1942_ = false, b1980_ = false, b2070_ = false, bie_ = false, bsafari_ = false, bsloven_ = false, bssi_ = false;
	unsigned int max_ = MAX_IDEAL_TITLE_LENGTH;
	unsigned short dt_ = 0;
	unsigned short hv_ = 0;
    ::std::string lang_ = "en";
    DECLARE_CLASS (html_t)
    DECLARE_EVENT_TABLE ()
public:
    html_t () = default;
    html_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = HTML_CAPTION);
    ~html_t () = default;
    bool invalid () const noexcept { return (version_ == nullptr) || (lingo_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = HTML_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();

	html_version ver () const;
	void ver (const html_version& v);
	unsigned int title () const { return max_; }
	void title (const unsigned int l) { max_ = l; }
	unsigned short doctype () const { return dt_; }
	void doctype (const unsigned short l) { dt_ = l; }
    bool rfc1867 () const noexcept { return b1867_; }
    void rfc1867 (const bool b) noexcept { b1867_ = b; }
    bool rfc1942 () const noexcept { return b1942_; }
    void rfc1942 (const bool b) noexcept { b1942_ = b; }
    bool rfc1980 () const noexcept { return b1980_; }
    void rfc1980 (const bool b) noexcept { b1980_ = b; }
    bool rfc2070 () const noexcept { return b2070_; }
    void rfc2070 (const bool b) noexcept { b2070_ = b; }
    bool ie () const noexcept { return bie_; }
    void ie (const bool b) noexcept { bie_ = b; }
    ::std::string lingo () const noexcept { return lang_; }
    void lingo (const ::std::string& s) { if (! s.empty ()) lang_ = s; }
    bool sloven () const noexcept { return bsloven_; }
    void sloven (const bool b) noexcept { bsloven_ = b; }
    bool ssi () const noexcept { return bssi_; }
    void ssi (const bool b) noexcept { bssi_ = b; }
    bool safari () const noexcept { return bsafari_; }
    void safari (const bool b) noexcept { bsafari_ = b; } };

#endif // WX
