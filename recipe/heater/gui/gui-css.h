/*                                                                 ,
ssc (static site checker)
File Info
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
#include "gui/gui-listedit.h"

#define CSS_CAPTION "CSS"

class css_t : public dialogue_t
{   wxBoxSizer* box_pro_ = nullptr;   
    wxBoxSizer* box_ver_ = nullptr;
    wxCheckBox* mobile_profile_ = nullptr;
    wxCheckBox* print_profile_ = nullptr;
    wxCheckBox* tv_profile_ = nullptr;
    wxChoice* version_ = nullptr;
    wxDataViewColumn* col_mod_ = nullptr;
    wxDataViewColumn* col_ver_ = nullptr;
    wxDataViewListCtrl* module_ = nullptr;
    wxRadioBox* caroline_ = nullptr;  
    wxStaticLine* sl1_ = nullptr;
    wxStaticLine* sl2_ = nullptr;
    wxStaticText* stat_ver_ = nullptr; 
    listedit_manager homme_;
    int mod_selected_ = css_none;
    e_css_version ver_ = css_none;
    html_version v_, trans_;
    vstr_t css_ext_;
    void Disenable ();  
    void OnHelpClick (wxCommandEvent& event);
    void OnVersion (wxCommandEvent& event);
    void OnModule (wxDataViewEvent& event);
    void OnLevel (wxCommandEvent& event);
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnRename (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    void set_module (const e_css_module m);
    void modulo_level ();
    DECLARE_CLASS (css_t)
    DECLARE_EVENT_TABLE ()
public:
    css_t () { }
    css_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CSS_CAPTION);
    ~css_t () { }
    bool invalid () const noexcept { return (version_ == nullptr) || (caroline_ == nullptr) || (module_ == nullptr) || homme_.invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CSS_CAPTION);
    void CreateControls ();
    void version (const html_version& v) { trans_ = v; }
    html_version version () const { return trans_; }
    void ext (const vstr_t& vs) { css_ext_ = vs; }
    vstr_t ext () const { return css_ext_; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

#endif // WX
