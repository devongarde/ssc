/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "gui/gui-ctrls.h"

#define CSS_CAPTION "CSS"

class css_t : public d1_t < wx_css >
{   wxDataViewColumn* col_mod_ = nullptr;
    wxDataViewColumn* col_ver_ = nullptr;
    wxDataViewListCtrl* module_ = nullptr;
//    wxStaticLine* sl1_ = nullptr;
//    wxStaticLine* sl2_ = nullptr;
    drop_box_t < css_version_t > drop_;
    line_t line1_, line2_;
    listedit_manager homme_ = listedit_manager (button_css_add, button_css_erase, button_css_rename, file_css_name, list_css_ext, text_css_ext);
    radio_t level_;
    e_css_version ver_ = css_none;
    html_version v_, trans_;
    vstr_t css_ext_;
    void Disenable ();  
    void OnHelpClick (wxCommandEvent& event);
    void set_module (const e_css_module m);
    void modulo_level ();
    DECLARE_CLASS (css_t)
    DECLARE_EVENT_TABLE ()
public:
    css_t () { }
    css_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CSS_CAPTION);
    ~css_t () { }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = CSS_CAPTION);
    void CreateControls ();
    bool invalid () const noexcept { return line2_.invalid (); }
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void OnVersion (wxCommandEvent& event);
    void OnModule (wxDataViewEvent& event);
    void OnLevel (wxCommandEvent& event);
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnRename (wxCommandEvent& event);
    void OnExtension (wxCommandEvent& event);
    void OnText (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    void version (const html_version& v) { trans_ = v; }
    html_version version () const { return trans_; }
    void ext (const vstr_t& vs) { css_ext_ = vs; }
    vstr_t ext () const { return css_ext_; } };
#endif // WX
