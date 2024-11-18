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
#include "gui/gui-css.h"
#include "gui/gui-frame.h"
#include "gui/gui-general.h"
#include "gui/gui-html.h"
#include "gui/gui-nits.h"
#include "gui/gui-ontology.h"
#include "gui/gui-shadow.h"
#include "gui/gui-site.h"
#include "gui/gui-snippet.h"
#include "gui/gui-spell.h"
#include "gui/gui-stats.h"
#ifdef DEBUG
#include "gui/gui-validation.h"
#endif // DEBUG

#define SPEX_CAPTION "Standards"

::std::string panel_naam (const int n);

class standard_t : public d3_t
{   wxChoicebook* choice_ = nullptr;

    context_t c_;
    css_t css_;
    general_t general_;
    html_t html_;
    nits_t nits_;
    ontology_t ontology_;
    shadow_t shadow_;
    site_t site_;
#ifndef NOSPELL
    spell_t spell_;
#endif // NOSPELL
    report_t stats_;
#ifdef DEBUG
    valid_t valid_;
#endif // DEBUG
    ::boost::filesystem::path conf_;
  
    void OnCancelClick (wxCommandEvent& event);
    void OnHelpClick (wxCommandEvent& event);
    void OnLoadClick (wxCommandEvent& event);
    void OnOkClick (wxCommandEvent& event);
    void OnSaveClick (wxCommandEvent& event);
    void OnSaveAsClick (wxCommandEvent& event);

    DECLARE_CLASS (standard_t)
    DECLARE_EVENT_TABLE ()
public:
    standard_t (wxWindow *mummy, const context_t& c, const e_gui_panel gp, wxWindowID id = wxID_ANY, const wxString& caption = SPEX_CAPTION);
    bool invalid () const { return choice_ == nullptr; }
    context_t& c () { return c_; }
    const context_t& c () const { return c_; }
    bool Create (wxWindow *mummy, const e_gui_panel gp, wxWindowID id = wxID_ANY, const wxString& caption = SPEX_CAPTION);
    void CreateControls (const e_gui_panel gp);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    e_gui_panel get_panel () const;
    void set_panel (const e_gui_panel gp);
    void load_from_context (const context_t& c) { c_ = c; }
    void save_to_context (context_t& c) const { c = c_; }

    void OnCSSVersion (wxCommandEvent& event) { css_.OnVersion (event); }
    void OnCSSModule (wxDataViewEvent& event) { css_.OnModule (event); }
    void OnCSSLevel (wxCommandEvent& event) { css_.OnLevel (event); }
    void OnCSSAdd (wxCommandEvent& event) { css_.OnAdd (event); }
    void OnCSSErase (wxCommandEvent& event) { css_.OnErase (event); }
    void OnCSSRename (wxCommandEvent& event) { css_.OnRename (event); }
    void OnCSSExtension (wxCommandEvent& event) { css_.OnExtension (event); }
    void OnCSSText (wxCommandEvent& event) { css_.OnText (event); }
    void OnCSSImpatience (wxCommandEvent& event) { css_.OnImpatience (event); }
#ifndef NO_FRED
    void OnGenFred (wxCommandEvent& event) { general_.OnFred (event); }
#endif // NO_FRED
    void OnGenMax (wxCommandEvent& event) { general_.OnMax (event); }
    void OnGenPersist (wxCommandEvent& event) { general_.OnPersist (event); }
    void OnHTMLVersion (wxCommandEvent& event) { html_.OnVersion (event); }
    void OnHTMLWX (wxCommandEvent& event) { html_.OnWX (event); }
    void OnNitsListLevel (wxCommandEvent& event) { nits_.OnListLevel (event); }
    void OnNitsRadioLevel (wxCommandEvent& event) { nits_.OnRadioLevel (event); }
    void OnOntologyExport (wxCommandEvent& e) { ontology_.OnExport (e); }
    void OnOntologyMFExport (wxCommandEvent& e) { ontology_.OnMFExport (e); }
    void OnOntologyMFVerify (wxCommandEvent& e) { ontology_.OnMFVerify (e); }
    void OnOntologyOntology (wxDataViewEvent& event) { ontology_.OnOntology (event); }
    void OnOntologyVerify (wxCommandEvent& e) { ontology_.OnVerify (e); }
    void OnOntologyVersion (wxCommandEvent& e) { ontology_.OnVersion (e); }
    void OnShadowIgnoreAdd (wxCommandEvent& event) { shadow_.OnIgnoreAdd (event); }
    void OnShadowIgnoreErase (wxCommandEvent& event) { shadow_.OnIgnoreErase (event); }
    void OnShadowIgnoreRename (wxCommandEvent& event) { shadow_.OnIgnoreRename (event); }
    void OnShadowIgnoreExtension (wxCommandEvent& event) { shadow_.OnIgnoreExtension (event); }
    void OnShadowIgnoreTap (wxCommandEvent& event) { shadow_.OnIgnoreTap (event); }
    void OnShadowIgnoreImpatience (wxCommandEvent& event) { shadow_.OnIgnoreImpatience (event); }
    void OnShadowShadow (wxCommandEvent& event) { shadow_.OnShadow (event); }
    void OnSiteAdd (wxCommandEvent& event) { site_.OnAdd (event); }
    void OnSiteErase (wxCommandEvent& event) { site_.OnErase (event); }
    void OnSiteExtension (wxCommandEvent& event) { site_.OnExtension (event); }
    void OnSiteExternal (wxCommandEvent& event) { site_.OnExternal (event); }
    void OnSiteImpatience (wxCommandEvent& event) { site_.OnImpatience (event); }
    void OnSiteInternal (wxCommandEvent& event) { site_.OnInternal (event); }
    void OnSiteOutput (wxCommandEvent& event) { site_.OnOutput (event); }
    void OnSiteRename (wxCommandEvent& event) { site_.OnRename (event); }
    void OnSiteTap (wxCommandEvent& event) { site_.OnTap (event); }
#ifndef NOSPELL
    void OnSpellCheck (wxCommandEvent& event) { spell_.OnCheck (event); }
    void OnSpellDictAdd (wxCommandEvent& event) { spell_.OnDictAdd (event); }
    void OnSpellDictErase (wxCommandEvent& event) { spell_.OnDictErase (event); }
    void OnSpellDictRename (wxCommandEvent& event) { spell_.OnDictRename (event); }
    void OnSpellDictExtension (wxCommandEvent& event) { spell_.OnDictExtension (event); }
    void OnSpellDictTap (wxCommandEvent& event) { spell_.OnDictTap (event); }
    void OnSpellDictImpatience (wxCommandEvent& event) { spell_.OnDictImpatience (event); }
    void OnSpellDictFileName (wxFileDirPickerEvent& event) { spell_.OnDictFileName (event); }
#ifdef HUNDO
    void OnSpellHunAdd (wxCommandEvent& event) { spell_.OnHunAdd (event); }
    void OnSpellHunErase (wxCommandEvent& event) { spell_.OnHunErase (event); }
    void OnSpellHunRename (wxCommandEvent& event) { spell_.OnHunRename (event); }
    void OnSpellHunExtension (wxCommandEvent& event) { spell_.OnHunExtension (event); }
    void OnSpellHunFileName (wxFileDirPickerEvent& event) { spell_.OnHunFileName (event); }
    void OnSpellHunImpatience (wxCommandEvent& event) { spell_.OnHunImpatience (event); }
    void OnSpellHunTap (wxCommandEvent& event) { spell_.OnHunTap (event); }
#endif // HUNDO
    void OnSpellWordAdd (wxCommandEvent& event) { spell_.OnWordAdd (event); }
    void OnSpellWordErase (wxCommandEvent& event) { spell_.OnWordErase (event); }
    void OnSpellWordRename (wxCommandEvent& event) { spell_.OnWordRename (event); }
    void OnSpellWordExtension (wxCommandEvent& event) { spell_.OnWordExtension (event); }
    void OnSpellWordTap (wxCommandEvent& event) { spell_.OnWordTap (event); }
    void OnSpellWordImpatience (wxCommandEvent& event) { spell_.OnWordImpatience (event); }
#endif // NOSPELL
#ifdef DEBUG
    void OnValidChoice (wxCommandEvent& event) { valid_.OnChoice (event); }
#endif // DEBUG
    void OnStatsAll (wxCommandEvent& event) { stats_.OnAll(event); }
    void OnStatsClear (wxCommandEvent& event) { stats_.OnClear (event); }
    void OnStatsExport (wxCommandEvent& event) { stats_.OnExport (event); }
    void OnStatsSelected (wxCommandEvent& event) { stats_.OnSelected (event); } };

#endif // WX
