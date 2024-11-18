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
#include "main/abort.h"
#include "main/output.h"
#include "main/context.h"
#include "feedback/nitpick.h"
#include "main/ssc.h"
#ifndef NOSPELL
#include "spell/spell.h"
#endif // NOSPELL
#include "gui/gui-app.h"
#include "gui/gui-css.h"
#include "gui/gui-frame.h"
#include "gui/gui-general.h"
#include "gui/gui-html.h"
#include "gui/gui-icon.h"
#include "gui/gui-nits.h"
#include "gui/gui-ontology.h"
#include "gui/gui-shadow.h"
#include "gui/gui-site.h"
#include "gui/gui-snippet.h"
#include "gui/gui-spell.h"
#include "gui/gui-stats.h"
#include "gui/gui-validation.h"

BEGIN_EVENT_TABLE (frame_t, wxFrame)
    EVT_FIND (wxID_ANY, frame_t::Find)
    EVT_FIND_NEXT (wxID_ANY, frame_t::Next)
    EVT_MENU (wxID_ABOUT, frame_t::OnAbout)
    EVT_MENU (wxID_COPY, frame_t::OnCopy)
    EVT_MENU (menu_conf_open, frame_t::OnConfigOpen)
    EVT_MENU (menu_conf_save, frame_t::OnConfigSave)
    EVT_MENU (menu_conf_save_as, frame_t::OnConfigSaveAs)
    EVT_MENU (menu_css, frame_t::OnCSS)
    EVT_UPDATE_UI (wxID_COPY, frame_t::OnUpdateCopy)
    EVT_MENU (menu_spin, frame_t::OnSpin)
    EVT_MENU (wxID_EXIT, frame_t::OnExit)
    EVT_MENU (wxID_FIND, frame_t::OnFind)
    EVT_FIND_CLOSE(wxID_ANY, frame_t::OnFindClose)
    EVT_MENU (menu_general, frame_t::OnGeneral)
    EVT_MENU (menu_help, frame_t::OnHelp)
    EVT_MENU (menu_html, frame_t::OnHTML)
    EVT_MENU (menu_next, frame_t::OnNext)
    EVT_MENU (menu_nits, frame_t::OnNits)
    EVT_MENU (wxID_PREVIEW, frame_t::OnPreview)
    EVT_MENU (wxID_PRINT, frame_t::OnPrint)
    EVT_MENU (menu_prior, frame_t::OnPrior)
    EVT_MENU (menu_print_setup, frame_t::OnPrintSetup)
    EVT_MENU (menu_ontology, frame_t::OnOntology)
    EVT_MENU (menu_root, frame_t::OnRoot)
    EVT_MENU (wxID_SAVE, frame_t::OnFileSave)
    EVT_MENU (wxID_SAVEAS, frame_t::OnFileSaveAs)
    EVT_MENU (wxID_SELECTALL, frame_t::OnSelectAll)
    EVT_MENU (menu_shadow, frame_t::OnShadow)
    EVT_MENU (menu_site, frame_t::OnSite)
    EVT_MENU (menu_snippet, frame_t::OnSnippet)
#ifndef NOSPELL
    EVT_MENU (menu_spell, frame_t::OnSpell)
#endif // NOSPELL
    EVT_MENU (menu_stats, frame_t::OnStats)
    EVT_SIZE (frame_t::OnSize)
    EVT_UPDATE_UI (wxID_SELECTALL, frame_t::OnUpdateSelectAll)
#ifdef DEBUG
    EVT_MENU (menu_validation, frame_t::OnValidation)
#endif // DEBUG
END_EVENT_TABLE ()

frame_t::frame_t (const wxPoint& pt, const wxSize& sz, const context_t& c)
    : wxFrame (nullptr, wxID_ANY, FULLNAME, pt, sz, wxDEFAULT_FRAME_STYLE), context_ (c)
{   SetIcon (teapot ());
    SetMenuBar (bar_.gimme ());
    CreateStatusBar ();
    wxFileSystem::AddHandler (new wxZipFSHandler);
    output_ = GSL_OWNER (output_t) (new output_t (this));
    print_ = GSL_OWNER (wxHtmlEasyPrinting) (new wxHtmlEasyPrinting (FULLNAME, this));
    if (print_ != nullptr) print_ -> SetFooter ("<hr>Page @PAGENUM@ of @PAGESCNT@", wxPAGE_ALL);
    SetStatusText (FORMALNAME " says 'er ... what?'"); }

frame_t::~frame_t ()
{   delete print_; }

void frame_t :: append (const ::std::string& text)
{   if ((! shush_) && (output_ != nullptr)) output_ -> append (text); }

void frame_t :: clear ()
{   if (output_ != nullptr) output_ -> clear (); }

void frame_t :: status (const ::std::string& s)
{    SetStatusText (s.c_str ()); }

bool frame_t::process_config (const nitpick& nits, const ::boost::filesystem::path& fn)
{   if (! nits.empty ())
        wxMessageBox (wxString (nits.review ()));
    if (nits.worst () > es_error)
    {   new_config_ = true;
        config_ = fn;
        return true; }
    return false; }

void frame_t :: load ()
{   app_t::load_conf (this, context_, config_); }

void frame_t :: save ()
{   app_t::save_conf (this, context_, config_); }

void frame_t :: save_as ()
{   app_t::save_conf_as (this, context_, config_); }

void frame_t :: Find (wxFindDialogEvent& e)
{   if ((find_ != nullptr) && (find_data_!= nullptr))
    {   const ::std::string wot (e.GetFindString ().c_str ());
        const int fussitudes = e.GetFlags ();
        if (output_ != nullptr) output_ -> Find (wot, fussitudes);
        OnFindClose (e); } }

void frame_t :: Next (wxFindDialogEvent& e)
{   if (find_data_!= nullptr)
    {   const ::std::string wot (e.GetFindString ().c_str ());
        const int fussitudes = e.GetFlags ();
        if (output_ != nullptr) output_ -> Find (wot, fussitudes); } }

void frame_t :: OnAbout (wxCommandEvent& )
{   if (app != nullptr) app -> help ("about"); }

void frame_t :: OnConfigOpen (wxCommandEvent& )
{   load (); }

void frame_t :: OnConfigSave (wxCommandEvent& )
{   save (); }

void frame_t :: OnConfigSaveAs (wxCommandEvent& )
{   save_as (); }
 
void frame_t :: OnCopy (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnCopy (e); }

void frame_t :: OnCSS (wxCommandEvent& )
{   on (gp_css); }

void frame_t :: OnExit (wxCommandEvent& )
{   if (find_ != nullptr)
    {   find_ -> Destroy ();
        find_ = nullptr; }
    delete find_data_;
    find_data_ = nullptr;
    Close (true); }

void frame_t :: OnFileSave (wxCommandEvent& )
{   if (output_ != nullptr) output_ -> FileSave (this); }

void frame_t :: OnFileSaveAs (wxCommandEvent& )
{   if (output_ != nullptr) output_ -> FileSaveAs (this); }
 
void frame_t :: OnFind (wxCommandEvent& )
{   if (find_ == nullptr)
    {   if (find_data_ == nullptr)
        {   find_data_ = GSL_OWNER (wxFindReplaceData) (new wxFindReplaceData (0));
            if (find_data_ == nullptr) return;
            find_data_ -> SetFlags (wxFR_DOWN | wxFR_MATCHCASE); }
        find_ = GSL_OWNER (wxFindReplaceDialog)
                (new wxFindReplaceDialog (this, find_data_, "find text", 0));
        if (find_ != nullptr) find_ -> Show (true); } }

void frame_t :: OnFindClose (wxFindDialogEvent& )
{   if (find_ != nullptr)
    {   find_ -> Destroy ();
        find_ = nullptr; } }

void frame_t :: on (const e_gui_panel gp)
{   standard_t g (this, context_, gp);
    if (g.ShowModal () == wxID_OK)
    {   g.save_to_context (context_); } }

void frame_t :: OnGeneral (wxCommandEvent& )
{   on (gp_gen); }

void frame_t :: OnHelp (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnHelp (e); }

void frame_t :: OnHTML (wxCommandEvent& )
{   on (gp_html); }

void frame_t :: OnLoad (wxCommandEvent& )
{   load (); }

void frame_t :: OnNext (wxCommandEvent& e)
{   if (find_data_ == nullptr) OnFind (e);
    else if (output_ != nullptr) output_ -> Next (); }

void frame_t :: OnNits (wxCommandEvent& )
{   on (gp_nits); }

void frame_t :: OnOntology (wxCommandEvent& )
{   on (gp_data); }

void frame_t :: OnPreview (wxCommandEvent& )
{   if ((output_ != nullptr) && (print_ != nullptr))
        output_ -> Preview (print_); }

void frame_t :: OnPrint (wxCommandEvent& )
{   if ((output_ != nullptr) && (print_ != nullptr))
        output_ -> Print (print_); }

void frame_t :: OnPrior (wxCommandEvent& e)
{   if (find_data_ == nullptr) OnFind (e);
    else if (output_ != nullptr) output_ -> Prior (); }

void frame_t :: OnPrintSetup (wxCommandEvent& )
{   if (print_ != nullptr) print_ -> PageSetup (); }

void frame_t :: OnRoot (wxCommandEvent& )
{   wxDirDialog dir (this, "select site root", root_.c_str ());
    if (dir.ShowModal () == wxID_OK)
    {   new_site_ = true;
        root_ = ::std::string (dir.GetPath ().c_str ()); } }

void frame_t :: OnSelectAll (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnSelectAll (e); }

void frame_t :: OnShadow (wxCommandEvent& )
{   on (gp_shadow); }

void frame_t :: OnSite (wxCommandEvent& )
{   on (gp_gen); }

void frame_t :: OnSize (wxSizeEvent &event)
{   event.Skip(); }

#ifndef NOSPELL
void frame_t :: OnSpell (wxCommandEvent& )
{   on (gp_spell); }
#endif // NOSPELL

void frame_t :: OnSnippet (wxCommandEvent& )
{   snippet_t s (this);
    s.snippet (snippet_);
    if (s.ShowModal () == wxID_OK)   
    {   snippet_ = s.snippet ();
        new_snippet_ = ! snippet_.empty (); } }

void frame_t :: OnStats (wxCommandEvent& )
{   on (gp_stats); }

void frame_t :: OnUpdateCopy (wxUpdateUIEvent& e)
{   if (output_ != nullptr) output_ -> OnUpdateCopy (e); }

void frame_t :: OnUpdateSelectAll (wxUpdateUIEvent& e)
{   if (output_ != nullptr) output_ -> OnUpdateSelectAll (e); }

#ifdef DEBUG
void frame_t :: OnValidation (wxCommandEvent& )
{   on (gp_validation); }
#endif // DEBUG

void frame_t :: OnSpin (wxCommandEvent& )
{   rational_ = bar_.config () -> IsChecked (menu_spin); }

#endif // WX
