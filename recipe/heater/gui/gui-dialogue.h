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

#define DEF_CAPTION "missing caption"
#define DEF_STYLE   wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX

template < typename SUPER > struct interrogate : SUPER
{   wxBoxSizer* box_ = nullptr;
    wxButton* cancel_ = nullptr;
    wxButton* help_ = nullptr;
    wxButton* ok_ = nullptr;
    wxPoint point_ = wxDefaultPosition;
    wxStdDialogButtonSizer* sbs_ = nullptr;
    wxWindow* mummy_ = nullptr;
    interrogate () = default;
    interrogate (const wxPoint& pos) : point_ (pos) { }
    ~interrogate () = default;
    bool invalid () const noexcept { return (box_ == nullptr) || (sbs_ == nullptr) || (cancel_ == nullptr); }
    void preCreate (wxWindow *mummy, const wxPoint& pos)
    {	mummy_ = mummy;
        if (point_ == wxDefaultPosition) point_ = pos; }
    void OnClose (const wxPoint point) noexcept
    {   point_ = point; } };

struct dialogue_t : interrogate < wxDialog >
{   wxSize size_ = wxDefaultSize;
    dialogue_t () = default;
    dialogue_t (const wxPoint& pos, const wxSize& size) : interrogate < wxDialog > (pos), size_ (size) { }
    ~dialogue_t () = default;
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = DEF_CAPTION,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const long style = DEF_STYLE);
    void CreateBox ()
    {	box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
	    if (box_ != nullptr)
	    {	sbs_ = GSL_OWNER (wxStdDialogButtonSizer) (new wxStdDialogButtonSizer ());
	        if (sbs_ != nullptr)
                cancel_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_CANCEL)); } }
    void CreateButtons (const int bs = 1, wxBoxSizer* box = nullptr)
    {	if (invalid ()) return;
	    sbs_ -> AddButton (cancel_);
	    help_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_HELP));
	    if (help_ != nullptr)
        {   sbs_ -> AddButton (help_);
	        ok_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_OK));
	        if (ok_ != nullptr)
            {   sbs_ -> AddButton (ok_);
	            sbs_ -> Realize ();
                if (box == nullptr) box_ -> Add (sbs_, bs, wxEXPAND, 1);
	            else box -> Add (sbs_, bs, wxEXPAND, 1); } } }
    void OnClose (const wxPoint point, const wxSize size) noexcept
    {   interrogate < wxDialog > :: OnClose (point);
        size_ = size; } };

struct whizzo_t : interrogate < wxWizard >
{   whizzo_t () = default;
    whizzo_t (const wxPoint& pos) : interrogate < wxWizard > (pos) { }
    ~whizzo_t () = default;
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = DEF_CAPTION,
        const wxPoint& pos = wxDefaultPosition, const long style = DEF_STYLE); };

#endif // WX
