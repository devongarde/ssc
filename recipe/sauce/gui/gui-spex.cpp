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

#ifdef WX
#include "gui/gui-app.h"
#include "gui/gui-spex.h"

#define DEF_CONF_EXT "conf"

#define SPEX_STYLE   DEF_STYLE
#define SPEX_X       100
#define SPEX_Y       100
#define SPEX_WIDTH   400
#define SPEX_HEIGHT  615

BEGIN_EVENT_TABLE (standard_t, wxDialog)
  EVT_BUTTON (wxID_SAVE, standard_t::OnSaveClick)
  EVT_BUTTON (wxID_SAVEAS, standard_t::OnSaveAsClick)
  EVT_BUTTON (wxID_OPEN, standard_t::OnLoadClick)
#ifndef NOSPELL
  EVT_BUTTON (button_dict_add, standard_t::OnSpellDictAdd)
#endif // NOSPELL
  EVT_BUTTON (wxID_HELP, standard_t::OnHelpClick)
  EVT_CHOICE (choice_css_version, standard_t::OnCSSVersion)
  EVT_DATAVIEW_SELECTION_CHANGED (list_css_module, standard_t::OnCSSModule)
  EVT_RADIOBOX (radio_css_level, standard_t::OnCSSLevel)
  EVT_BUTTON (button_css_add, standard_t::OnCSSAdd)
  EVT_BUTTON (button_css_erase, standard_t::OnCSSErase)
  EVT_BUTTON (button_css_rename, standard_t::OnCSSRename)
  EVT_TEXT (text_css_ext, standard_t::OnCSSText)
  EVT_LISTBOX (list_css_ext, standard_t::OnCSSExtension)
  EVT_LISTBOX_DCLICK (list_css_ext, standard_t::OnCSSImpatience)
#ifndef NO_FRED
  EVT_CHECKBOX (check_fred, standard_t::OnGenFred)
#endif // NO_FRED
  EVT_CHECKBOX (check_file_size, standard_t::OnGenMax)
  EVT_CHECKBOX (check_file_persist, standard_t::OnGenPersist)
  EVT_CHOICE (choice_html_version, standard_t::OnHTMLVersion)
  EVT_CHECKBOX (check_wx, standard_t::OnHTMLWX)
  EVT_LISTBOX (list_level, standard_t::OnNitsListLevel)
  EVT_CHOICE (choice_nit_format, standard_t::OnNitsFormat)
  EVT_RADIOBOX (radio_nits_level, standard_t::OnNitsRadioLevel)
  EVT_CHECKBOX (check_export, standard_t::OnOntologyExport)
  EVT_CHECKBOX (check_mf_export, standard_t::OnOntologyMFExport)
  EVT_CHECKBOX (check_mf_verify, standard_t::OnOntologyMFVerify)
  EVT_CHECKBOX (check_verify, standard_t::OnOntologyVerify)
  EVT_CHOICE (choice_ontology_version, standard_t::OnOntologyVersion)
  EVT_DATAVIEW_SELECTION_CHANGED (list_ontology, standard_t::OnOntologyOntology)
  EVT_CHECKBOX (check_site, standard_t::OnShadowShadow)
  EVT_BUTTON (button_shadow_add, standard_t::OnShadowIgnoreAdd)
  EVT_BUTTON (button_shadow_erase, standard_t::OnShadowIgnoreErase)
  EVT_BUTTON (button_shadow_rename, standard_t::OnShadowIgnoreRename)
  EVT_TEXT (text_shadow_ext, standard_t::OnShadowIgnoreTap)
  EVT_LISTBOX (list_shadow_ext, standard_t::OnShadowIgnoreExtension)
  EVT_LISTBOX_DCLICK (list_shadow_ext, standard_t::OnShadowIgnoreImpatience)
  EVT_BUTTON (button_site_add, standard_t::OnSiteAdd)
  EVT_BUTTON (button_site_erase, standard_t::OnSiteErase)
  EVT_CHECKBOX (check_external, standard_t::OnSiteExternal)
  EVT_LISTBOX (list_site_ext, standard_t::OnSiteExtension)
  EVT_LISTBOX_DCLICK (list_site_ext, standard_t::OnSiteImpatience)
  EVT_CHECKBOX (check_internal, standard_t::OnSiteInternal)
  EVT_CHECKBOX (check_corpus_output, standard_t::OnSiteOutput)
  EVT_BUTTON (button_site_rename, standard_t::OnSiteRename)
  EVT_TEXT (button_site_rename, standard_t::OnSiteTap)
#ifndef NOSPELL
  EVT_CHECKBOX (check_spell, standard_t::OnSpellCheck)
  EVT_BUTTON (button_dict_add, standard_t::OnSpellDictAdd)
  EVT_BUTTON (button_dict_erase, standard_t::OnSpellDictErase)
  EVT_BUTTON (button_dict_rename, standard_t::OnSpellDictRename)
  EVT_TEXT (text_dict_ext, standard_t::OnSpellDictTap)
  EVT_LISTBOX (list_dict_ext, standard_t::OnSpellDictExtension)
  EVT_LISTBOX_DCLICK (list_dict_ext, standard_t::OnSpellDictImpatience)
  EVT_FILEPICKER_CHANGED (file_dict_name, standard_t::OnSpellDictFileName)
#ifdef HUNDO
  EVT_BUTTON (button_hun_add, standard_t::OnSpellHunAdd)
  EVT_BUTTON (button_hun_erase, standard_t::OnSpellHunErase)
  EVT_FILEPICKER_CHANGED (file_hun_name, standard_t::OnSpellHunFileName)
  EVT_BUTTON (button_hun_rename, standard_t::OnSpellHunRename)
  EVT_TEXT (text_hun_ext, standard_t::OnSpellHunTap)
  EVT_LISTBOX (list_hun_ext, standard_t::OnSpellHunExtension)
  EVT_LISTBOX_DCLICK (list_hun_ext, standard_t::OnSpellHunImpatience)
#endif // HUNDO
  EVT_BUTTON (button_word_add, standard_t::OnSpellWordAdd)
  EVT_BUTTON (button_word_erase, standard_t::OnSpellWordErase)
  EVT_BUTTON (button_word_rename, standard_t::OnSpellWordRename)
  EVT_TEXT (text_word_ext, standard_t::OnSpellWordTap)
  EVT_LISTBOX (list_word_ext, standard_t::OnSpellWordExtension)
  EVT_LISTBOX_DCLICK (list_word_ext, standard_t::OnSpellWordImpatience)
#endif // NOSPELL
  EVT_CHECKBOX (check_ssi_exec, standard_t::OnSSIExec)
  EVT_CHECKBOX (check_ssi_lastmod, standard_t::OnSSILastMod)
  EVT_CHECKBOX (check_ssi_now, standard_t::OnSSINow)
  EVT_CHECKBOX (check_ssi_process, standard_t::OnSSIProcess)
  EVT_CHECKBOX (check_stats_export, standard_t::OnStatsExport)
  EVT_BUTTON (button_all, standard_t::OnStatsAll)
  EVT_BUTTON (button_clear, standard_t::OnStatsClear)
  EVT_CHECKBOX (check_stats_export, standard_t::OnStatsExport)
  EVT_BUTTON (button_selected, standard_t::OnStatsSelected)
  EVT_DIRPICKER_CHANGED (dir_ontology, standard_t::OnVVOntology)
  EVT_DIRPICKER_CHANGED (dir_physical, standard_t::OnVVPhys)
  EVT_DIRPICKER_CHANGED (dir_shadow, standard_t::OnVVShadow)
  EVT_CHOICE (choice_validation_version, standard_t::OnVVValChoice)
  EVT_BUTTON (button_validation_add, standard_t::OnVVValAdd)
  EVT_BUTTON (button_validation_erase, standard_t::OnVVValErase)
  EVT_BUTTON (button_validation_rename, standard_t::OnVVValRename)
  EVT_TEXT (text_validation, standard_t::OnVVValText)
  EVT_LISTBOX (list_validation, standard_t::OnVVValSelect)
  EVT_LISTBOX_DCLICK (list_validation, standard_t::OnVVValImpatience)
  EVT_BUTTON (button_virtual_add, standard_t::OnVVVirtAdd)
  EVT_BUTTON (button_virtual_erase, standard_t::OnVVVirtErase)
  EVT_BUTTON (button_virtual_rename, standard_t::OnVVVirtRename)
  EVT_TEXT (text_virtual, standard_t::OnVVVirtText)
  EVT_LISTBOX (list_virtual, standard_t::OnVVVirtSelect)
  EVT_LISTBOX_DCLICK (list_virtual, standard_t::OnVVVirtImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (standard_t, wxDialog)

template < class N, class... D > struct panel_name : public panel_name < D... >
{   static const ::std::string naam (const int n)
    {   if (n > 0) return panel_name < D... > :: naam (n-1);
        return N::name (); } };

template < class N > struct panel_name < N >
{   static const ::std::string naam (const int n)
    {   if (n > 0) return wx_default::sz ();
        return N::name (); } };

::std::string panel_naam (const int n)
{   return panel_name < css_t, general_t, html_t, nits_t, ontology_t, shadow_t, site_t,
#ifndef NOSPELL
                        spell_t,
#endif // NOSPELL
                        summarise_t, vv_t,
                        report_t > :: naam (n); }

standard_t :: standard_t (wxWindow *mummy, const context_t& c, const e_gui_panel gp, wxWindowID id, const wxString& caption)
    : d3_t (wxPoint (SPEX_X, SPEX_Y), wxSize (SPEX_WIDTH, SPEX_HEIGHT)), c_ (c)
{	Create (mummy, gp, id, caption); } 

bool standard_t :: Create (wxWindow *mummy, const e_gui_panel gp, wxWindowID id, const wxString& caption)
{	if (! d3_t :: Create (mummy, id, caption, wxPoint (SPEX_X, SPEX_Y), wxSize (SPEX_WIDTH, SPEX_HEIGHT), SPEX_STYLE)) return false;
    CreateControls (gp);
    return true; }

void standard_t :: CreateControls (const e_gui_panel gp)
{	if (interrogate < wxDialog > :: invalid ()) return;
    choice_ = GSL_OWNER (wxChoicebook) (new wxChoicebook (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT));
    if (choice_ != nullptr) // if this order changes, update e_gui_panel
    {	if (summary_.create_panel (choice_, panel_statistics, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (summary_.panel (), "summary", false); 
        if (html_.create_panel (choice_, panel_html, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (html_.panel (), "HTML, XHTML, MathML, SVG", false); 
        if (css_.create_panel (choice_, panel_css, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (css_.panel (), "CSS", false); 
        if (site_.create_panel (choice_, panel_site, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (site_.panel (), "root, link, search corpus", false); 
        if (general_.create_panel (choice_, panel_general, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (general_.panel (), "bits / bobs", false); 
        if (nits_.create_panel (choice_, panel_nits, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (nits_.panel (), "errors, warnings, nitpicking", false); 
        if (ontology_.create_panel (choice_, panel_ontology, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (ontology_.panel (), "machine readable content", false); 
        if (shadow_.create_panel (choice_, panel_shadow, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (shadow_.panel (), "shadow, deduplicate, resolve", false); 
#ifndef NOSPELL
        if (spell_.create_panel (choice_, panel_spell, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (spell_.panel (), "spelling", false); 
#endif // NOSPELL
        if (ssi_.create_panel (choice_, panel_ssi, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (ssi_.panel (), "server side includes", false); 
        if (stats_.create_panel (choice_, panel_statistics, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (stats_.panel (), "statistics, reports", false); 
        if (vv_.create_panel (choice_, panel_validation, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL))
            choice_ -> AddPage (vv_.panel (), "validation, virtual", false);
        box_ -> Add (choice_, 12, wxEXPAND | wxALL, 5); }
    d3_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH);
    set_panel (gp); }

void standard_t :: OnCancelClick (wxCommandEvent& )
{	EndModal (wxID_CANCEL); }

void standard_t :: OnHelpClick (wxCommandEvent& )
{	if (invalid ()) return;
    if (app == nullptr) return;
    const int sel = choice_ -> GetSelection ();
    switch (sel) // decided requiring that two enums, the Create function, and content.hhc, all correspond, was too risky
    {   case gp_summary : app -> help (hp_summary); break;
        case gp_html : app -> help (hp_HTML); break;
        case gp_css : app -> help (hp_css); break;
        case gp_gen : app -> help (hp_general); break;
        case gp_bits : app -> help (hp_bobs); break;
        case gp_nits : app -> help (hp_nits); break;
        case gp_data : app -> help (hp_ontology); break;
        case gp_shadow : app -> help (hp_shadow); break;
#ifndef NOSPELL
        case gp_spell : app -> help (hp_spell); break;
#endif // NOSPELL
        case gp_ssi : app -> help (hp_ssi); break;
        case gp_stats : app -> help (hp_stats); break;
        case gp_validation : app -> help (hp_validation); break;
        default : break; } }

void standard_t :: OnLoadClick (wxCommandEvent& )
{	app_t::load_conf (this, c_, conf_); }

void standard_t :: OnOkClick (wxCommandEvent& )
{	TransferDataFromWindow ();
    EndModal (wxID_OK); }

void standard_t :: OnSaveClick (wxCommandEvent& )
{	if (conf_.empty ()) app_t::save_conf_as (this, c_, conf_);
    else app_t::save_conf (this, c_, conf_); }

void standard_t :: OnSaveAsClick (wxCommandEvent& )
{	app_t::save_conf_as (this, c_, conf_); }

bool standard_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    css_.load_from_context (c_);
    general_.load_from_context (c_);
    html_.load_from_context (c_);
    nits_.load_from_context (c_);
    ontology_.load_from_context (c_);
    shadow_.load_from_context (c_);
    site_.load_from_context (c_);
#ifndef NOSPELL
    spell_.load_from_context (c_);
#endif // NOSPELL
    ssi_.load_from_context (c_);
    stats_.load_from_context (c_);
    summary_.load_from_context (c_);
    vv_.load_from_context (c_);
    return  css_.TransferDataToWindow () &&
            general_.TransferDataToWindow () &&
            html_.TransferDataToWindow () &&
            nits_.TransferDataToWindow () &&
            ontology_.TransferDataToWindow () &&
            shadow_.TransferDataToWindow () &&
            site_.TransferDataToWindow () &&
#ifndef NOSPELL
            spell_.TransferDataToWindow () &&
#endif // NOSPELL
            stats_.TransferDataToWindow () &&
            summary_.TransferDataToWindow () &&
            vv_.TransferDataToWindow () &&
            ssi_.TransferDataToWindow (); }

bool standard_t :: TransferDataFromWindow ()
{	if (	invalid () ||
            ! css_.TransferDataFromWindow () ||
            ! general_.TransferDataFromWindow () ||
            ! html_.TransferDataFromWindow () ||
            ! nits_.TransferDataFromWindow () ||
            ! ontology_.TransferDataFromWindow () ||
            ! shadow_.TransferDataFromWindow () ||
            ! site_.TransferDataFromWindow () ||
#ifndef NOSPELL
            ! spell_.TransferDataFromWindow () ||
#endif // NOSPELL
            ! stats_.TransferDataFromWindow () ||
            ! summary_.TransferDataFromWindow () ||
            ! vv_.TransferDataFromWindow () ||
            ! ssi_.TransferDataFromWindow ())
        return false;
    nitpick nits;
    css_.save_to_context (c_);
    general_.save_to_context (c_);
    html_.save_to_context (c_);
    nits_.save_to_context (c_);
    ontology_.save_to_context (c_);
    shadow_.save_to_context (c_);
    site_.save_to_context (c_);
#ifndef NOSPELL
    spell_.save_to_context (c_);
#endif // NOSPELL
    ssi_.save_to_context (nits, c_);
    stats_.save_to_context (c_);
    summary_.save_to_context (c_);
    vv_.save_to_context (c_);
    if (! nits.empty ())
        app_t::nits_msgbox (nullptr, "SSI values", nits, es_info);
    return true; }

::std::string andl (const ::std::string z, const ::std::string& s)
{	if (s.empty () || z.empty ()) return s;
    return ::std::string (", ") + s; }

e_gui_panel standard_t :: get_panel () const
{	if (invalid ()) return gp_html;
    return static_cast < e_gui_panel > (choice_ -> GetSelection ()); }

void standard_t :: set_panel (const e_gui_panel gp)
{	if (invalid ()) return;
    if (gp == gp_validation) vv_.yer_actual (site_.folder (), shadow_.shadow (), ontology_.path ());
    choice_ -> SetSelection (gp); }

#endif // WX
